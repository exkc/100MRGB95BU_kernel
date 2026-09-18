/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  util function for TE
 *
 *  @author	Kyungseok Hyun(ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-06-27
 *  @note		Additional information.
 */

#include <linux/ctype.h>
#include <lg1k/te/buffer.h>

#include "te_impl.h"

#define rb_wait_for_event(rb, cond, timeout)				\
({									\
	int __res;							\
	switch (timeout) {						\
	case 0:								\
		READ_ONCE(rb->error);					\
		__res = 0;						\
		break;							\
	case TE_BUF_INFINITE_TIMEOUT:					\
		__res = wait_event_interruptible(rb->wq, cond);		\
		break;							\
	default:							\
		__res = wait_event_interruptible_timeout(rb->wq,	\
				cond, msecs_to_jiffies(timeout));	\
		if (__res == 0)						\
			__res = -ETIME;					\
		break;							\
	}								\
	__res;								\
})

#define rb_wait_for_wevent(rb, cond, timeout) 			\
({								\
	int __res;						\
	if (timeout != 0 && 					\
	    ((rb->flags & TE_BUF_FLAG_NO_EVENT) ||		\
	     (rb->flags & TE_BUF_FLAG_UPLOAD_MODULE)))		\
		__res = -EINVAL;				\
	else							\
		__res = rb_wait_for_event(rb, cond, timeout);	\
	__res;							\
})

#define rb_wait_for_revent(rb, cond, timeout) 			\
({								\
	int __res;						\
	if (timeout != 0 && 					\
	    ((rb->flags & TE_BUF_FLAG_NO_EVENT) ||		\
	     !(rb->flags & TE_BUF_FLAG_UPLOAD_MODULE)))		\
		__res = -EINVAL;				\
	else							\
		__res = rb_wait_for_event(rb, cond, timeout);	\
	__res;							\
})


#define rb_send_event(rb)	wake_up_interruptible(&rb->wq)

struct pkt_hdr {
	u32 size;
};
#define PKTBUF_HDR_SIZE	sizeof(struct pkt_hdr)

struct pkt_info {
	u32 idx;
	u32 size;
};

struct pktbuf_info {
	u32 size;
	u32 widx;
	u32 ridx;
	struct pkt_info pkt[0];
};

/*************************************
       COMMON FUNCTIONS START
 *************************************/
static void __rbuf_init(struct te_rb *rb, void *data, u32 len, u32 flags)
{
	rb->data = data;
	rb->size = len;
	rb->widx = rb->ridx = 0;
	rb->error = 0;
	rb->flags = flags;
	init_waitqueue_head(&rb->wq);

	memset(rb->callback, 0, sizeof(rb->callback));
}

static void __rbuf_set_callback(struct te_rb *rb, enum te_buf_owner owner,
				te_buf_callback_func_t func, void *arg)
{
	struct te_buf_callback *cb = &rb->callback[owner];

	cb->func = func;
	cb->arg = arg;
}

static inline void __rbuf_callback(struct te_rb *rb, enum te_buf_owner owner,
				   u32 idx)
{
	struct te_buf_callback *cb = &rb->callback[owner];
	if (cb->func)
		cb->func(cb->arg, idx);
}

static void __rbuf_reset(struct te_rb *rb)
{
	if (rb->flags & TE_BUF_FLAG_MANUAL_IDX) {
		__rbuf_callback(rb, TE_BUF_PRODUCER, TE_BUF_IDX_RESET);
		__rbuf_callback(rb, TE_BUF_CONSUMER, TE_BUF_IDX_RESET);
	} else {
		__rbuf_callback(rb, TE_BUF_PRODUCER, 0);
		smp_store_release(&rb->widx, 0);
		__rbuf_callback(rb, TE_BUF_CONSUMER, 0);
		smp_store_release(&rb->ridx, 0);
	}

	rb->error = 0;
}

static inline u32 __rbuf_idx_add(struct te_rb *rb, u32 idx, u32 len)
{
	idx += len;
	if (idx >= rb->size)
		idx -= rb->size;

	return idx;
}

static inline u32 __rbuf_diff_idx(struct te_rb *rb, u32 idx, u32 next_idx)
{
	return (next_idx < idx) ? rb->size - idx + next_idx : next_idx - idx;
}

static inline bool __rbuf_is_invalid_data(struct te_rb *rb, const void *data)
{
	const u8 *a = data;

	if (a < rb->data || a >= (rb->data + rb->size))
		return true;

	return false;
}

/**
 * __rbuf_get_idx2 - Get two indices and length that include the len of data
 *
 * sidx + offset = start position
 * len2 = 0 if start postion + len is not wrap-arounded
 * No idx2 parameter because *idx2 is always 0 evenif *len2 is not 0
 *
 */
static void __rbuf_get_idx2(struct te_rb *rb, u32 sidx, u32 offset, u32 len,
			    u32 *idx1, u32 *len1, u32 *len2)
{
	if (offset)
		sidx = __rbuf_idx_add(rb, sidx, offset);

	*idx1 = sidx;
	if ((sidx + len) > rb->size) {
		*len1 = rb->size - sidx;
		*len2 = len - *len1;
	} else {
		*len1 = len;
		*len2 = 0;
	}
}


/**
 * __rbuf_get_split_buf - Get @struct te_split_buffer at idx + offset
 *
 * if the length of data is wrap-arounded, buf->b[1].data will be set else
 * will be NULL.
 */
static void __rbuf_get_split_buf(struct te_rb *rb, u32 sidx, u32 offset,
				 u32 len, struct te_split_buffer *buf)
{
	if (offset)
		sidx = __rbuf_idx_add(rb, sidx, offset);

	buf->b[0].data = rb->data + sidx;
	if ((sidx + len) > rb->size) {
		buf->b[0].size = rb->size - sidx;
		buf->b[1].data = rb->data;
		buf->b[1].size = len - buf->b[0].size;
	} else {
		buf->b[0].size = len;
		buf->b[1].data = NULL;
		buf->b[1].size = 0;
	}

	buf->size = len;
}

static inline void __rbuf_raise_event(struct te_rb *rb)
{
	if (!(rb->flags & TE_BUF_FLAG_NO_EVENT))
		rb_send_event(rb);
}

/* === PRODUCER === */

/**
 * __rbuf_continuous_free_size - Get continuous free space size in ring buffer
 *
 * NOTE: *size2 is 0 if free buffer is not wrap-arounded
 */
static void __rbuf_continuous_free_size(struct te_rb *rb,
					u32 *size1, u32 *size2)
{
	u32 widx = rb->widx;
	u32 ridx = READ_ONCE(rb->ridx);

	if (ridx > widx) {
		*size1 = ridx - widx - 1;
		*size2 = 0;
	} else {
		if (ridx == 0) {
			*size1 = rb->size - widx - 1;
			*size2 = 0;
		} else {
			*size1 = rb->size - widx;
			*size2 = ridx - 1;
		}
	}
}

static u32 __rbuf_free_size(struct te_rb *rb)
{
	u32 size;
	u32 widx = rb->widx;
	u32 ridx = READ_ONCE(rb->ridx);

	if (ridx > widx)
		size = ridx - widx - 1;
	else
		size = ridx + rb->size - widx - 1;

	return size;
}

static int __rbuf_write_condition(struct te_rb *rb)
{
	if (READ_ONCE(rb->error))
		return -EIO;

	return __rbuf_free_size(rb);
}

static inline void __rbuf_write_callback(struct te_rb *rb, u32 widx)
{
	__rbuf_callback(rb, TE_BUF_PRODUCER, widx);
}

static inline void __rbuf_raise_wevent(struct te_rb *rb)
{
	if (!(rb->flags & TE_BUF_FLAG_NO_EVENT) &&
	    !(rb->flags & TE_BUF_FLAG_UPLOAD_MODULE))
		rb_send_event(rb);
}

static inline void __rbuf_write_done(struct te_rb *rb, u32 widx)
{
	smp_store_release(&rb->widx, widx);
	__rbuf_write_callback(rb, widx);
	__rbuf_raise_wevent(rb);
}

/**
 * __rbuf_idx_write - Write data in ringbuffer at widx
 *
 * Note: this does NOT check free buffer and does NOT update widx
 *
 * Return: next widx
 */
static u32 __rbuf_idx_write(struct te_rb *rb, u32 widx, const void *buf,
			    u32 len)
{
	const u8 *data = buf;
	u32 split;

	split = (widx + len >= rb->size) ? rb->size - widx : 0;
	if (split) {
		memcpy(rb->data + widx, data, split);
		data += split;
		len -= split;
		widx = 0;
	}

	if (len)
		memcpy(rb->data + widx, data, len);

	return widx + len;
}

/**
 * __rbuf_idx_write_user - Write the user space @buf to the ringbuffer at widx
 *
 * Note: this does NOT check free buffer and does NOT update widx
 *
 * Return: next widx on success, -EFAULT if copy_from_user fails
 */
static int __rbuf_idx_write_user(struct te_rb *rb, u32 widx,
				 const void __user *buf, u32 len)
{
	const u8 __user *data = buf;
	u32 split;

	split = (widx + len >= rb->size) ? rb->size - widx : 0;
	if (split) {
		if (copy_from_user(rb->data + widx, data, split))
			return -EFAULT;

		data += split;
		len -= split;
		widx = 0;
	}

	if (len) {
		if (copy_from_user(rb->data + widx, data, len))
			return -EFAULT;
	}

	return widx + len;
}

static u32 __rbuf_idx_write2(struct te_rb *rb, u32 widx,
			     const void *buf1, u32 len1,
			     const void *buf2, u32 len2)
{
	if (len1)
		widx = __rbuf_idx_write(rb, widx, buf1, len1);
	if (len2)
		widx = __rbuf_idx_write(rb, widx, buf2, len2);

	return widx;
}

/*
 * Write data in ringbuffer at widx and update widx
 * Note: this does NOT check free buffer
 *
 */
static void __rbuf_raw_write(struct te_rb *rb, const void *buf, u32 len)
{
	u32 widx = rb->widx;

	widx = __rbuf_idx_write(rb, widx, buf, len);

	__rbuf_write_done(rb, widx);
}

/**
 * __rbuf_raw_write_user - Write a length of user pointer @buf into the buffer
 *
 * It does NOT check free buffer and always writes length of buffer
 *
 * Return: @len on success, or -EFAULT if copy_to_user failed
 */
static int __rbuf_raw_write_user(struct te_rb *rb, const void __user *buf,
				 u32 len)
{
	int widx = rb->widx;

	widx = __rbuf_idx_write_user(rb, widx, buf, len);
	if (widx < 0)
		return widx;

	__rbuf_write_done(rb, widx);

	return len;
}

static void __rbuf_raw_write2(struct te_rb *rb, const void *buf1, u32 len1,
			      const void *buf2, u32 len2)
{
	u32 widx = rb->widx;

	widx = __rbuf_idx_write2(rb, widx, buf1, len1, buf2, len2);

	__rbuf_write_done(rb, widx);
}

/*
 * move widx to the pos of widx + length that is considered wraparound
 * Note: this does NOT check free buffer
 */
static void __rbuf_raw_write_skip(struct te_rb *rb, u32 len)
{
	u32 widx = rb->widx;

	widx = __rbuf_idx_add(rb, widx, len);

	__rbuf_write_done(rb, widx);
}

static inline void __rbuf_set_error(struct te_rb *rb, int err)
{
	smp_store_release(&rb->error, err);
	__rbuf_raise_event(rb);
}

/* === CONSUMER === */
static u32 __rbuf_avail_size(struct te_rb *rb)
{
	u32 size;
	u32 widx = smp_load_acquire(&rb->widx);
	u32 ridx = rb->ridx;

	if (widx >= ridx)
		size = widx - ridx;
	else
		size = widx + rb->size - ridx;

	return size;
}

static int __rbuf_read_condition(struct te_rb *rb)
{
	if (READ_ONCE(rb->error))
		return -EIO;

	return __rbuf_avail_size(rb);
}

static inline void __rbuf_read_callback(struct te_rb *rb, u32 ridx)
{
	__rbuf_callback(rb, TE_BUF_CONSUMER, ridx);
}

static inline void __rbuf_raise_revent(struct te_rb *rb)
{
	if (!(rb->flags & TE_BUF_FLAG_NO_EVENT) &&
	    (rb->flags & TE_BUF_FLAG_UPLOAD_MODULE))
		rb_send_event(rb);
}

static inline void __rbuf_read_done(struct te_rb *rb, u32 ridx)
{
	smp_store_release(&rb->ridx, ridx);
	__rbuf_read_callback(rb, ridx);
	__rbuf_raise_revent(rb);
}

/*
 * __rbuf_idx_read - Read lenth of data in the ringbuffer at ridx
 *
 * It does NOT check available buffer and does NOT update ridx
 *
 * Return: next ridx
 */
static u32 __rbuf_idx_read(struct te_rb *rb, u32 ridx, void *buf, u32 len)
{
	u8 *data = buf;
	u32 split;

	split = (ridx + len >= rb->size) ? rb->size - ridx : 0;
	if (split > 0) {
		memcpy(data, rb->data + ridx, split);
		data += split;
		len -= split;
		ridx = 0;
	}

	if (len)
		memcpy(data, rb->data + ridx, len);

	return ridx + len;
}

static void __rbuf_raw_read(struct te_rb *rb, void *buf, u32 len)
{
	u32 ridx = rb->ridx;

	ridx = __rbuf_idx_read(rb, ridx, buf, len);

	__rbuf_read_done(rb, ridx);
}

static void __rbuf_raw_read_skip(struct te_rb *rb, u32 len)
{
	u32 ridx = rb->ridx;

	ridx = __rbuf_idx_add(rb, ridx, len);

	__rbuf_read_done(rb, ridx);
}

/**
 * __rbuf_idx_read_user - Reads a buffer at ridx into user pointer @buf
 *
 * It does NOT check available buffer and always reads length of buffer
 *
 * Return: next ridx on success, or -EFAULT if copy_to_user failed
 */
static int __rbuf_idx_read_user(struct te_rb *rb, u32 ridx, void __user *buf,
				u32 len)
{
	u8 __user *data = buf;
	u32 split;

	split = (ridx + len >= rb->size) ? rb->size - ridx : 0;
	if (split > 0) {
		if (copy_to_user(data, rb->data + ridx, split))
			return -EFAULT;

		data += split;
		len -= split;
		ridx = 0;
	}

	if (len) {
		if (copy_to_user(data, rb->data + ridx, len))
			return -EFAULT;
	}

	return ridx + len;
}

/**
 * __rbuf_raw_read_user - Reads a length of buffer into user pointer @buf
 *
 * It does NOT check available buffer and always reads length of buffer
 *
 * Return: @len on success, or -EFAULT if copy_to_user failed
 */
static int __rbuf_raw_read_user(struct te_rb *rb, void __user *buf, u32 len)
{
	int ridx = rb->ridx;

	ridx = __rbuf_idx_read_user(rb, ridx, buf, len);
	if (ridx < 0)
		return ridx;

	__rbuf_read_done(rb, ridx);

	return len;
}

static void __rbuf_flush(struct te_rb *rb)
{
	if (rb->flags & TE_BUF_FLAG_MANUAL_IDX)
		__rbuf_read_callback(rb, TE_BUF_IDX_FLUSH);
	else {
		u32 idx = smp_load_acquire(&rb->widx);
		__rbuf_read_callback(rb, idx);
		smp_store_release(&rb->ridx, idx);
	}
	rb->error = 0;
}

/*************************************
       COMMON FUNCTIONS END
 *************************************/

/*************************************
         RING BUFFER START
 *************************************/
void te_ringbuf_init(struct te_ringbuf *rbuf, void *data, u32 len, u32 flags)
{
	__rbuf_init(&rbuf->rb, data, len, flags);
}

void te_ringbuf_reset(struct te_ringbuf *rbuf)
{
	__rbuf_reset(&rbuf->rb);
}

void te_ringbuf_set_write_callback(struct te_ringbuf *rbuf,
				   te_buf_callback_func_t func, void *arg)
{
	__rbuf_set_callback(&rbuf->rb, TE_BUF_PRODUCER, func, arg);
}

void te_ringbuf_set_read_callback(struct te_ringbuf *rbuf,
				  te_buf_callback_func_t func, void *arg)
{
	__rbuf_set_callback(&rbuf->rb, TE_BUF_CONSUMER, func, arg);
}

/*
 * === PRODUCER ===
 */

u32 te_ringbuf_free_size(struct te_ringbuf *rbuf)
{
	return __rbuf_free_size(&rbuf->rb);
}

void te_ringbuf_raw_write(struct te_ringbuf *rbuf, const void *buf, u32 len)
{
	__rbuf_raw_write(&rbuf->rb, buf, len);
}

void te_ringbuf_raw_write2(struct te_ringbuf *rbuf, const void *buf1,
			   u32 len1, const void *buf2, u32 len2)
{
	__rbuf_raw_write2(&rbuf->rb, buf1, len1, buf2, len2);
}

/**
 * te_ringbuf_cwrite - write a @buf into the ringbuffer after checking free size
 *
 * It checks free size is more than @len if not, it returns -ENOBUFS
 *
 * Return: 0 on success, -ENOBUFS if no sufficient free buffer to write
 */
int te_ringbuf_cwrite(struct te_ringbuf *rbuf, const void *buf, u32 len)
{
	u32 free_size = __rbuf_free_size(&rbuf->rb);

	if (free_size < len)
		return -ENOBUFS;

	__rbuf_raw_write(&rbuf->rb, buf, len);

	return 0;
}

/**
 * te_ringbuf_cwrite2 - write @buf1 and @buf2 into the ringbuffer after checking
 * free size
 *
 * It checks free size is more than @len1 + @len2 if not, it returns -ENOBUFS
 *
 * Return: 0 on success, -ENOBUFS if no sufficient free buffer to write
 */
int te_ringbuf_cwrite2(struct te_ringbuf *rbuf, const void *buf1, u32 len1,
		       const void *buf2, u32 len2)
{
	u32 free_size = __rbuf_free_size(&rbuf->rb);
	u32 len = len1 + len2;

	if (free_size < len)
		return -ENOBUFS;

	__rbuf_raw_write2(&rbuf->rb, buf1, len1, buf2, len2);

	return 0;
}

/**
 * te_ringbuf_set_widx - set widx in ringbuf
 *
 * CAUTION: It should update widx evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if widx invalid,
 * -EOVERFLOW if overflow happens(widx overtakes ridx)
 */
int te_ringbuf_set_widx(struct te_ringbuf *rbuf, u32 widx)
{
	int ret;
	struct te_rb *rb = &rbuf->rb;
	u32 len;

	if (rb->widx == widx)
		return 0;

	if (widx >= rb->size)
		return -EINVAL;

	len = __rbuf_diff_idx(rb, rb->widx, widx);
	if (len > __rbuf_free_size(rb))
		ret = -EOVERFLOW;
	else
		ret = 0;

	__rbuf_write_done(rb, widx);

	return ret ? ret : len;
}

/**
 * te_ringbuf_write_user_timeout - write a user pointer @buf into the buffer
 * @timeout - timeout in ms, TE_BUF_INFINITE_TIMEOUT for infinite waiting
 *
 * Return: number of bytes written on success,
 * -EINVAL if input parameter is invalid
 * -EFAULT if copy_to_user() fails,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO if the buffer has an error
 */
int te_ringbuf_write_user_timeout(struct te_ringbuf *rbuf,
				  const void __user *buf, u32 len,
				  unsigned long timeout)
{
	int rc;
	u32 free;
	struct te_rb *rb = &rbuf->rb;

	rc = rb_wait_for_revent(rb, __rbuf_write_condition(rb), timeout);
	if (rc < 0)
		return rc;

	if (rb->error)
		return -EIO;

	free = __rbuf_free_size(rb);
	if (!free)
		return 0;

	if (free > len)
		free = len;

	return __rbuf_raw_write_user(rb, buf, free);
}

int te_ringbuf_io_write(struct te_ringbuf *rbuf, const void __user *buf,
			u32 len, bool non_blocking)
{
	int ret = 0, wsize = 0;
	unsigned long timeout;

	if (non_blocking) {
		if (!__rbuf_write_condition(&rbuf->rb))
			return -EWOULDBLOCK;
		timeout = 0;
	} else {
		timeout = TE_BUF_INFINITE_TIMEOUT;
	}

	while (len) {
		ret = te_ringbuf_write_user_timeout(rbuf, buf, len, timeout);
		if (ret < 0)
			break;

		wsize += ret;
		if (non_blocking)
			break;

		len -= ret;
		buf += ret;
	}

	return (wsize) ? wsize : ret;
}

void te_ringbuf_set_error(struct te_ringbuf *rbuf, int err)
{
	__rbuf_set_error(&rbuf->rb, err);
}

/*
 * === CONSUMER ===
 */
u32 te_ringbuf_avail_size(struct te_ringbuf *rbuf)
{
	return __rbuf_avail_size(&rbuf->rb);
}

/**
 * te_ringbuf_set_ridx - set ridx in ringbuffer
 *
 * CAUTION: It should update ridx evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if ridx is invalid,
 * -EOVERFLOW if overflow happens(ridx overtakes widx)
 */
int te_ringbuf_set_ridx(struct te_ringbuf *rbuf, u32 ridx)
{
	int ret;
	struct te_rb *rb = &rbuf->rb;
	u32 len;

	if (rb->ridx == ridx)
		return 0;

	if (ridx >= rb->size)
		return -EINVAL;

	len = __rbuf_diff_idx(rb, rb->ridx, ridx);
	if (len > __rbuf_avail_size(rb))
		ret = -EOVERFLOW;
	else
		ret = 0;

	__rbuf_read_done(rb, ridx);

	return ret ? ret : len;
}

/**
 * te_ringbuf_get_ridx - get ridx + offset in the ring buffer
 *
 */
void te_ringbuf_get_ridx(struct te_ringbuf *rbuf, u32 offset, u32 *idx)
{
	struct te_rb *rb = &rbuf->rb;
	u32 ridx = rb->ridx;

	if (offset)
		ridx = __rbuf_idx_add(rb, ridx, offset);

	*idx = ridx;
}

/**
 * te_ringbuf_raw_peek - Peek length of data at offset in the ring buffer
 *
 * It does NOT update the ridx in the ring buffer
 */
void te_ringbuf_raw_peek(struct te_ringbuf *rbuf, u32 offset, void *buf,
			 u32 len)
{
	struct te_rb *rb = &rbuf->rb;
	u32 ridx = rb->ridx;

	if (offset)
		ridx = __rbuf_idx_add(rb, ridx, offset);

	__rbuf_idx_read(rb, ridx, buf, len);
}

/**
 * te_ringbuf_peek - Peek length of data at offset in the ring buffer
 *
 * It does NOT update the ridx in the ring buffer
 *
 * Return: 0 on success, or -ENODATA if no available size
 */
int te_ringbuf_peek(struct te_ringbuf *rbuf, u32 offset, void *buf, u32 len)
{
	u32 size;

	size = __rbuf_avail_size(&rbuf->rb);
	if (size < (offset + len))
		return -ENODATA;

	te_ringbuf_raw_peek(rbuf, offset, buf, len);

	return 0;
}

/**
 * te_ringbuf_read_skip - set ridx in ringbuffer
 *
 * Return: 0 on success, or -ENODATA if no available size
 */
int te_ringbuf_read_skip(struct te_ringbuf *rbuf, u32 len)
{
	u32 size, ridx;
	struct te_rb *rb = &rbuf->rb;

	size = __rbuf_avail_size(rb);
	if (size < len)
		return -ENODATA;

	ridx = __rbuf_idx_add(rb, rb->ridx, len);

	__rbuf_read_done(rb, ridx);
	return 0;
}

void te_ringbuf_raw_read(struct te_ringbuf *rbuf, void *buf, u32 len)
{
	return __rbuf_raw_read(&rbuf->rb, buf, len);
}

/**
 * te_ringbuf_read - Reads a ring buffer into @buf
 *
 * Return: read size on success
 */
int te_ringbuf_read(struct te_ringbuf *rbuf, void *buf, u32 len)
{
	u32 avail;

	avail = __rbuf_avail_size(&rbuf->rb);
	if (!avail)
		return 0;

	if (avail > len)
		avail = len;

	__rbuf_raw_read(&rbuf->rb, buf, avail);

	return avail;
}

/**
 * __ringbuf_get_buf2 - Get available buffer and length at idx + offset
 */
static void __ringbuf_get_buf2(struct te_ringbuf *rbuf, u32 idx, u32 offset,
			       u32 len, void **buf1, u32 *len1,
			       void **buf2, u32 *len2)
{
	struct te_rb *rb = &rbuf->rb;
	u32 idx1;

	__rbuf_get_idx2(rb, idx, offset, len, &idx1, len1, len2);

	*buf1 = rb->data + idx1;
	if (*len2)
		*buf2 = rb->data;
	else
		*buf2 = NULL;
}

/**
 * te_ringbuf_raw_get_rbuf2 - Get buffer pointer at ridx in the ring buffer
 *
 * Note: if buffer is not wrap-arounded, *buf2 = NULL and *len2 = 0
 */
void te_ringbuf_raw_get_rbuf2(struct te_ringbuf *rbuf, u32 offset, u32 len,
			      void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	u32 ridx = rbuf->rb.ridx;

	__ringbuf_get_buf2(rbuf, ridx, offset, len, buf1, len1, buf2, len2);
}

/**
 * te_ringbuf_raw_read_user - Reads a length of buffer into user pointer @buf
 *
 * Return: @len on success, or -EFAULT if copy_to_user failed
 */
int te_ringbuf_raw_read_user(struct te_ringbuf *rbuf, void __user *buf, u32 len)
{
	return __rbuf_raw_read_user(&rbuf->rb, buf, len);
}

/**
 * te_ringbuf_read_user_timeout - Reads a buffer into a user pointer @buf
 * @timeout - timeout in ms, TE_BUF_INFINITE_TIMEOUT for infinite waiting
 *
 * It starts from the last read position(@rb->ridx) and
 * reads up to @len bytes or till it reaches the available size
 *
 * Return: number of bytes read on success,
 * -EINVAL if input parameter is invalid
 * -EFAULT if copy_to_user is failed,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO : if rbuf has error
 */
int te_ringbuf_read_user_timeout(struct te_ringbuf *rbuf, void __user *buf,
				 u32 len, unsigned long timeout)
{
	int rc;
	u32 avail;
	struct te_rb *rb = &rbuf->rb;

	rc = rb_wait_for_wevent(rb, __rbuf_read_condition(rb), timeout);
	if (rc < 0)
		return rc;

	if (rb->error)
		return -EIO;

	avail = __rbuf_avail_size(rb);
	if (!avail)
		return 0;

	if (avail > len)
		avail = len;

	return __rbuf_raw_read_user(rb, buf, avail);
}

int te_ringbuf_io_read(struct te_ringbuf *rbuf, void __user *buf, u32 len,
		       bool non_blocking)
{
	int ret = 0, read_size = 0;
	struct te_rb *rb = &rbuf->rb;
	unsigned long timeout;

	if (non_blocking) {
		if (!__rbuf_read_condition(rb))
			return -EWOULDBLOCK;
		timeout = 0;
	} else {
		timeout = TE_BUF_INFINITE_TIMEOUT;
	}

	while (len) {
		ret = te_ringbuf_read_user_timeout(rbuf, buf, len, timeout);
		if (ret < 0)
			break;

		read_size += ret;

		if (non_blocking)
			break;

		len -= ret;
		buf += ret;
	}

	return (read_size) ? read_size : ret;
}

void te_ringbuf_flush(struct te_ringbuf *rbuf)
{
	__rbuf_flush(&rbuf->rb);
}

/*************************************
         RING BUFFER END
 *************************************/

/*************************************
         PACKET BUFFER START
 *************************************/

/**
 * te_pktbuf_init - Initialize packet buffer
 * @pkt_size:
 *	average packet size for allocating internal buffer. It is ignored
 *	if TE_BUF_FLAG_INNER_PKTINFO flag is set
 * @flags:
 *	TE_BUF_FLAG_LINEAR_BUFFER - single packet is in linear buffer
 *	TE_BUF_FLAG_INNER_PKTINFO - not use packet info memory
 *	TE_BUF_FLAG_NO_EVENT - not raise event when data is read or written
 *
 * Return: 0 on success, -ENOMEM or -EINVAL on error
 */
int te_pktbuf_init(struct te_pktbuf *pbuf, void *data, u32 len, u32 pkt_size,
		   u32 flags)
{
	if (flags & TE_BUF_FLAG_INNER_PKTINFO) {
		/* can't use TE_BUF_FLAG_LINEAR_BUFFER with _INNER_PKTINFO */
		if (flags & TE_BUF_FLAG_LINEAR_BUFFER)
			return -EINVAL;

		pbuf->info = NULL;
	} else {
		u32 count;
		struct pktbuf_info *info;

		if (pkt_size < 32)
			pkt_size = 32;

		if (len < 2 * pkt_size)
			return -EINVAL;

		count = (len - 1) / pkt_size + 1;
		info = vmalloc(sizeof(*info) + count * sizeof(struct pkt_info));
		if (!info)
			return -ENOMEM;

		info->size = count;
		info->widx = info->ridx = 0;

		pbuf->info = info;
	}
	__rbuf_init(&pbuf->rb, data, len, flags);

	return 0;
}

/**
 * te_pktbuf_release - Release packet buffer
 *
 * It frees allocated packet info buffer
 */
void te_pktbuf_release(struct te_pktbuf *pbuf)
{
	if (pbuf->info) {
		vfree(pbuf->info);
		pbuf->info = NULL;
	}
}

static void __pktbuf_info_reset(struct pktbuf_info *info)
{
	smp_store_release(&info->widx, 0);
	smp_store_release(&info->ridx, 0);
}

void te_pktbuf_reset(struct te_pktbuf *pbuf)
{
	struct te_rb *rb = &pbuf->rb;

	if (pbuf->info)
		__pktbuf_info_reset(pbuf->info);

	__rbuf_reset(rb);
}

void te_pktbuf_set_write_callback(struct te_pktbuf *pbuf,
				  te_buf_callback_func_t func,
				  void *arg)
{
	__rbuf_set_callback(&pbuf->rb, TE_BUF_PRODUCER, func, arg);
}

void te_pktbuf_set_read_callback(struct te_pktbuf *pbuf,
				 te_buf_callback_func_t func,
				 void *arg)
{
	__rbuf_set_callback(&pbuf->rb, TE_BUF_CONSUMER, func, arg);
}

/* === PRODUCER === */

/**
 * __pktbuf_continuous_free_size - Checks and gets continous free sizes
 *
 * Return: 0 on success, -ENOBUFS if not enough free buffer
 */
static inline int __pktbuf_continuous_free_size(struct te_pktbuf *pbuf,
						u32 wsize, u32 *size1,
						u32 *size2)
{
	u32 free1, free2;

	__rbuf_continuous_free_size(&pbuf->rb, &free1, &free2);

	if (size1)
		*size1 = free1;
	if (size2)
		*size2 = free2;

	if (free1 < wsize && free2 < wsize)
		return -ENOBUFS;

	return 0;
}

static u32 __pktbuf_info_free_size(struct pktbuf_info *bi)
{
	u32 size;
	u32 widx = bi->widx;
	u32 ridx = READ_ONCE(bi->ridx);

	if (ridx > widx)
		size = ridx - widx - 1;
	else
		size = ridx + bi->size - widx - 1;

	return size;
}

static void __pktbuf_info_raw_write(struct pktbuf_info *bi, u32 widx, u32 size)
{
	u32 idx = bi->widx;
	struct pkt_info *pi = &bi->pkt[idx];

	pi->idx = widx;
	pi->size = size;

	idx += 1;
	if (idx >= bi->size)
		idx = 0;

	smp_store_release(&bi->widx, idx);
}

/**
 * __pktbuf_avail_widx - Gets available widx to write length of data
 * @len: length of data to write
 *
 * It checks free buffer of packet info and data, especially if flags have
 * TE_BUF_FLAG_LINEAR_BUFFER it checks continuous free buffer
 *
 * Return: widx on success, -ENOBUFS if no free buffer
 */
static int __pktbuf_avail_widx(struct te_pktbuf *pbuf, u32 len)
{
	int rc;
	struct te_rb *rb = &pbuf->rb;
	u32 free_size;
	u32 widx;

	if (!__pktbuf_info_free_size(pbuf->info))
		return -ENOBUFS;

	if (rb->flags & TE_BUF_FLAG_LINEAR_BUFFER) {
		rc = __pktbuf_continuous_free_size(pbuf, len, &free_size, NULL);
		if (rc)
			return rc;

		if (free_size < len)
			widx = 0;
		else
			widx = rb->widx;
	} else {
		free_size = __rbuf_free_size(rb);

		if (free_size < len)
			return -ENOBUFS;

		widx = rb->widx;
	}

	return widx;
}

static int __pktbuf_outer_write2(struct te_pktbuf *pbuf, const void *pkt1,
				 u32 len1, const void *pkt2, u32 len2)
{
	int widx;
	u32 next_widx;
	struct te_rb *rb = &pbuf->rb;
	u32 len = len1 + len2;

	widx = __pktbuf_avail_widx(pbuf, len);
	if (widx < 0)
		return widx;

	next_widx = __rbuf_idx_write2(rb, widx, pkt1, len1, pkt2, len2);

	__pktbuf_info_raw_write(pbuf->info, widx, len);

	__rbuf_write_done(rb, next_widx);

	return len;
}

static int __pktbuf_inner_write2(struct te_pktbuf *pbuf, const void *pkt1,
				 u32 len1, const void *pkt2, u32 len2)
{
	u32 free_size, widx;
	struct pkt_hdr hdr;
	struct te_rb *rb = &pbuf->rb;
	u32 len = len1 + len2;

	free_size = __rbuf_free_size(rb);
	if (free_size < (len + PKTBUF_HDR_SIZE))
		return -ENOBUFS;

	hdr.size = len;
	widx = __rbuf_idx_write(rb, rb->widx, &hdr, PKTBUF_HDR_SIZE);
	widx = __rbuf_idx_write2(rb, widx, pkt1, len1, pkt2, len2);

	__rbuf_write_done(rb, widx);

	return len;
}

/**
 * te_pktbuf_packet_write2 - Write a separated packet into the packet buffer
 *
 * Return: number of bytes written on success, or
 * -ENOBUFS if no sufficient free buffer to write
 */
int te_pktbuf_packet_write2(struct te_pktbuf *pbuf, const void *pkt1, u32 len1,
			    const void *pkt2, u32 len2)
{
	if (pbuf->info)
		return __pktbuf_outer_write2(pbuf, pkt1, len1, pkt2, len2);
	else
		return __pktbuf_inner_write2(pbuf, pkt1, len1, pkt2, len2);
}

/**
 * te_pktbuf_packet_write - Write a packet into the packet buffer
 *
 * Return: number of bytes written on success, or
 * -ENOBUFS if no sufficient free buffer to write
 */
int te_pktbuf_packet_write(struct te_pktbuf *pbuf, const void *pkt, u32 len)
{
	return te_pktbuf_packet_write2(pbuf, pkt, len, NULL, 0);
}

/**
 * te_pktbuf_get_wbuf2 - Get the buffer pointer and length to write a packet
 * in the packet buffer
 *
 * It sets available buffer pointer and length to write a @len of signle packet
 * into the packet buffer. If rb->flags has TE_BUF_FLAG_LINEAR_BUFFER,
 * it is guaranteed @len1 is more than packet size(@len).
 * *buf2 = NULL and *len2 = 0 if buffer is not wrap-arounded
 *
 * Return: 0 on success, -ENOBUFS if no free space to write @len of packet,
 * -EPERM if flags has TE_BUF_FLAG_INNER_PKTINFO.
 */
int te_pktbuf_get_wbuf2(struct te_pktbuf *pbuf, u32 len,
			void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	struct te_rb *rb = &pbuf->rb;
	u32 free1, free2;

	if (!pbuf->info)
		return -EPERM;

	if (!__pktbuf_info_free_size(pbuf->info))
		return -ENOBUFS;

	__rbuf_continuous_free_size(rb, &free1, &free2);

	if (rb->flags & TE_BUF_FLAG_LINEAR_BUFFER) {
		if (free1 < len && free2 < len)
			return -ENOBUFS;

		if (free1 < len) {
			*buf1 = rb->data;
			*len1 = free2;
		} else {
			*buf1 = rb->data + rb->widx;
			*len1 = free1;
		}
		*buf2 = NULL;
		*len2 = 0;
	} else {
		if ((free1 + free2) < len)
			return -ENOBUFS;

		*buf1 = rb->data + rb->widx;
		*len1 = free1;

		if (free2 > 0) {
			*buf2 = rb->data;
		} else {
			*buf2 = NULL;
		}
		*len2 = free2;
	}

	return 0;
}

/**
 * te_pktbuf_get_cont_wbuf - Get the continuous buffer in the packet buffer
 *
 * Only supported if rb->flags has TE_BUF_FLAG_LINEAR_BUFFER
 * It sets available buffer pointer to write a @len of signle packet
 * into the packet buffer.
 *
 * Return: 0 on success,
 * -EPERM if rb->flags does not have TE_BUF_FLAG_LINEAR_BUFFER or
 * it has TE_BUF_FLAG_INNER_PKTINFO,
 * -ENOBUFS if no free space to write @len of packet or no free space for info.
 */
int te_pktbuf_get_cont_wbuf(struct te_pktbuf *pbuf, u32 len, void **buf)
{
	struct te_rb *rb = &pbuf->rb;
	u32 free1, free2;

	if (!pbuf->info)
		return -EPERM;

	if (!(rb->flags & TE_BUF_FLAG_LINEAR_BUFFER))
		return -EPERM;

	if (!__pktbuf_info_free_size(pbuf->info))
		return -ENOBUFS;

	__rbuf_continuous_free_size(rb, &free1, &free2);

	if (free1 < len && free2 < len)
		return -ENOBUFS;

	if (free1 < len) {
		*buf = rb->data;
	} else {
		*buf = rb->data + rb->widx;
	}

	return 0;
}

static int __pktbuf_add_packet(struct te_pktbuf *pbuf, u32 sidx, u32 eidx)
{
	u32 len;
	struct te_rb *rb = &pbuf->rb;

	if (sidx >= rb->size || eidx >= rb->size)
		return -EINVAL;

	if (!__pktbuf_info_free_size(pbuf->info)) { /* packet info free size */
		return -ENOBUFS;
	}

	len = __rbuf_diff_idx(rb, sidx, eidx);
	if (!(rb->flags & TE_BUF_FLAG_MANUAL_IDX)) {
		u32 free_size = __rbuf_free_size(rb);
		u32 len2 = __rbuf_diff_idx(rb, rb->widx, eidx);
		if (len2 < len ||	/* overlapped */
		    len2 > free_size) {	/* overflow */
			return -ENOBUFS;
		}
	}

	__pktbuf_info_raw_write(pbuf->info, sidx, len);

	__rbuf_write_done(rb, eidx);

	return 0;
}

/*
 * te_pktbuf_add_packet - Add a packet info when the packet was already written
 * @packet: buffer pointer in packet buffer
 *
 * It is almost the same as skip function in other buffer, but this writes
 * a packet info also.
 *
 * Return: 0 on success,
 * -EPERM if flags has TE_BUF_FLAG_INNER_PKTINFO,
 * -EINVAL if packet buffer is invalid,
 * -ENOBUFS if packet info buffer has no free space
 */
int te_pktbuf_add_packet(struct te_pktbuf *pbuf, void *packet, u32 len)
{
	struct te_rb *rb = &pbuf->rb;
	u8 *data = packet;
	u32 sidx, eidx;

	if (!pbuf->info)
		return -EPERM;

	if (__rbuf_is_invalid_data(rb, packet)) {
		return -EINVAL;
	}

	sidx = (u32)(data - rb->data);
	eidx = __rbuf_idx_add(rb, sidx, len);

	return __pktbuf_add_packet(pbuf, sidx, eidx);
}

/**
 * te_pktbuf_add_packet_idx - Add packet info based on index written by h/w
 * @sidx: start index of packet in the buffer
 * @eidx: end index of packet in the buffer
 *
 * This function only adds the packet information, so data must be written
 * before this is called. It's usefull to bind this buffer to h/w buffer and
 * register callback functions likes below:
 *  1. te_hwbuf_init - init h/w buffer
 *  2. te_pktbuf_init with registerd h/w buffer(same buffer)
 *  3. add write callback to h/w buffer, so when callback function called,
 *     call add packet(this function) to update information.
 *  4. add read callback to packet buffer, so when consumer read data from
 *     packet buffer then update h/w buffer(te_hwbuf_set_ridx).
 *
 * Return: 0 on success, or negative value if failed
 */
int te_pktbuf_add_packet_idx(struct te_pktbuf *pbuf, u32 sidx, u32 eidx)
{
	if (!pbuf->info)
		return -EPERM;

	return __pktbuf_add_packet(pbuf, sidx, eidx);
}

void te_pktbuf_set_error(struct te_pktbuf *pbuf, int err)
{
	__rbuf_set_error(&pbuf->rb, err);
}

u32 te_pktbuf_free_size(struct te_pktbuf *pbuf)
{
	struct te_rb *rb = &pbuf->rb;
	u32 free;

	if (pbuf->info) {
		if (!__pktbuf_info_free_size(pbuf->info))
			return 0; //no space

		if (rb->flags & TE_BUF_FLAG_LINEAR_BUFFER) {
			u32 free2;
			__rbuf_continuous_free_size(&pbuf->rb, &free, &free2);
			return (free > free2) ? free : free2;
		} else {
			return __rbuf_free_size(rb);
		}
	} else {
		free = __rbuf_free_size(rb);
		if (free < PKTBUF_HDR_SIZE)
			return 0;

		return free - PKTBUF_HDR_SIZE;
	}
}

/* === CONSUMER === */

static void __pktbuf_info_flush(struct pktbuf_info *bi)
{
	u32 idx = smp_load_acquire(&bi->widx);
	smp_store_release(&bi->ridx, idx);
}

/**
 * __pktbuf_info_get_pkt - Get the next packet info
 *
 * It does NOT check available packet info buffer so it must be checked before
 * calling this function
 */
static inline struct pkt_info *__pktbuf_info_get_pkt(struct pktbuf_info *bi)
{
	return &bi->pkt[bi->ridx];
}

/**
 * __pktbuf_info_dispose_pkt - Dispose of a next packet info
 *
 * It does NOT check available packet info buffer
 */
static inline void __pktbuf_info_dispose_pkt(struct pktbuf_info *bi)
{
	u32 idx = bi->ridx;

	idx += 1;
	if (idx >= bi->size)
		idx = 0;

	smp_store_release(&bi->ridx, idx);
}

/**
 * __pktbuf_info_avail_packet - Get the available packet count
 */
static inline u32 __pktbuf_info_avail_packet(struct pktbuf_info *bi)
{
	u32 size;
	u32 widx = smp_load_acquire(&bi->widx);
	u32 ridx = bi->ridx;

	if (widx >= ridx)
		size = widx - ridx;
	else
		size = widx + bi->size - ridx;

	return size;
}

static int __pktbuf_condition(struct te_pktbuf *pbuf)
{
	struct te_rb *rb = &pbuf->rb;

	if (READ_ONCE(rb->error))
		return -EIO;

	if (pbuf->info)
		return __pktbuf_info_avail_packet(pbuf->info);
	else
		return __rbuf_avail_size(rb);
}

/**
 * te_pktbuf_avail_size - Get the total size of packets
 *
 * It adds up all packets size
 *
 * Return: number of bytes can be read on success,
 * 0 if no available packet,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_avail_size(struct te_pktbuf *pbuf)
{
	int size = 0;

	if (pbuf->info) {
		struct pkt_info *pi;
		struct pktbuf_info *bi = pbuf->info;
		u32 widx = smp_load_acquire(&bi->widx);
		u32 ridx = bi->ridx;

		while (ridx != widx) {
			pi = &bi->pkt[ridx];
			size += pi->size;
			ridx += 1;
			if (ridx >= bi->size)
				ridx = 0;
		}
	} else {
		u32 avail;
		struct pkt_hdr hdr;
		struct te_rb *rb = &pbuf->rb;
		u32 ridx = rb->ridx;
		int res = 0;

		avail = __rbuf_avail_size(rb);
		while (avail) {
			if (avail < PKTBUF_HDR_SIZE) {
				res = -ESTRPIPE;
				break;
			}

			ridx = __rbuf_idx_read(rb, ridx, &hdr, PKTBUF_HDR_SIZE);
			avail -= PKTBUF_HDR_SIZE;
			if (avail < hdr.size) {
				res = -ESTRPIPE;
				break;
			}

			ridx = __rbuf_idx_add(rb, ridx, hdr.size);

			size += hdr.size;
			avail -= hdr.size;
		}

		if (size == 0)
			size = res;
	}

	return size;
}

/**
 * te_pktbuf_next_packet_size - Get the next packet size
 *
 * Return: number of bytes can be read on success,
 * 0 if no available packet,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_next_packet_size(struct te_pktbuf *pbuf)
{
	if (pbuf->info) {
		struct pkt_info *pi;

		if (!__pktbuf_info_avail_packet(pbuf->info))
			return 0;

		pi = __pktbuf_info_get_pkt(pbuf->info);

		return pi->size;
	} else {
		u32 avail;
		struct pkt_hdr hdr;
		struct te_rb *rb = &pbuf->rb;

		avail = __rbuf_avail_size(rb);
		if (!avail)
			return 0;

		if (avail < PKTBUF_HDR_SIZE)
			return -ESTRPIPE;

		__rbuf_idx_read(rb, rb->ridx, &hdr, PKTBUF_HDR_SIZE);
		avail -= PKTBUF_HDR_SIZE;
		if (avail < hdr.size)
			return -ESTRPIPE;

		return hdr.size;
	}
}

/**
 * te_pktbuf_avail_packet - Get the available packet count
 *
 * Return: number of packets can be read on success,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_avail_packet(struct te_pktbuf *pbuf)
{
	int count = 0;

	if (pbuf->info) {
		count = __pktbuf_info_avail_packet(pbuf->info);
	} else {
		u32 avail;
		struct pkt_hdr hdr;
		struct te_rb *rb = &pbuf->rb;
		u32 ridx = rb->ridx;
		int res = 0;

		avail = __rbuf_avail_size(rb);
		while (avail) {
			if (avail < PKTBUF_HDR_SIZE) {
				res = -ESTRPIPE;
				break;
			}

			ridx = __rbuf_idx_read(rb, ridx, &hdr, PKTBUF_HDR_SIZE);
			avail -= PKTBUF_HDR_SIZE;
			if (avail < hdr.size) {
				res = -ESTRPIPE;
				break;
			}

			ridx = __rbuf_idx_add(rb, ridx, hdr.size);

			count++;
			avail -= hdr.size;
		}

		if (count == 0)
			count = res;
	}

	return count;
}

static int __pktbuf_outer_packet_read(struct te_pktbuf *pbuf, void *buf,
				      u32 len)
{
	struct te_rb *rb = &pbuf->rb;
	struct pktbuf_info *bi = pbuf->info;
	struct pkt_info *pi;
	u32 ridx;

	if (READ_ONCE(rb->error))
		return -EIO;

	if (!__pktbuf_info_avail_packet(bi))
		return -ENODATA;

	pi = __pktbuf_info_get_pkt(bi);
	if (len < pi->size)
		return -ENOBUFS;	// or -EINVAL

	ridx = __rbuf_idx_read(rb, pi->idx, buf, pi->size);

	__rbuf_read_done(rb, ridx);
	__pktbuf_info_dispose_pkt(bi);

	return pi->size;
}

static int __pktbuf_inner_packet_read(struct te_pktbuf *pbuf, void *buf,
				      u32 len)
{
	u32 avail, ridx;
	struct pkt_hdr hdr;
	struct te_rb *rb = &pbuf->rb;

	if (READ_ONCE(rb->error))
		return -EIO;

	avail = __rbuf_avail_size(rb);
	if (!avail)
		return -ENODATA;

	if (avail < PKTBUF_HDR_SIZE)
		return -ESTRPIPE;

	ridx = __rbuf_idx_read(rb, rb->ridx, &hdr, PKTBUF_HDR_SIZE);
	avail -= PKTBUF_HDR_SIZE;
	if (avail < hdr.size)
		return -ESTRPIPE;

	if (len < hdr.size)
		return -ENOBUFS;

	ridx = __rbuf_idx_read(rb, ridx, buf, hdr.size);

	__rbuf_read_done(rb, ridx);

	return hdr.size;
}

/**
 * te_pktbuf_packet_read - Read only one packet in the packet buffer
 *
 * Return: the packet size on success,
 * -EIO if packet buffer has an error,
 * -ENODATA if no packet in the packet buffer,
 * -ENOBUFS when the @buf is not sufficient,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_packet_read(struct te_pktbuf *pbuf, void *buf, u32 len)
{
	if (pbuf->info)
		return __pktbuf_outer_packet_read(pbuf, buf, len);
	else
		return __pktbuf_inner_packet_read(pbuf, buf, len);
}

static int __pktbuf_outer_packet_read_user(struct te_pktbuf *pbuf,
					   void __user *buf, u32 len)
{
	struct te_rb *rb = &pbuf->rb;
	struct pktbuf_info *bi = pbuf->info;
	struct pkt_info *pi;
	int ridx;

	if (READ_ONCE(rb->error))
		return -EIO;

	if (!__pktbuf_info_avail_packet(bi))
		return -ENODATA;

	pi = __pktbuf_info_get_pkt(bi);
	if (len < pi->size)
		return -ENOBUFS;

	ridx = __rbuf_idx_read_user(rb, pi->idx, buf, pi->size);
	if (ridx < 0)
		return ridx;

	__rbuf_read_done(rb, ridx);
	__pktbuf_info_dispose_pkt(bi);

	return pi->size;
}

static int __pktbuf_inner_packet_read_user(struct te_pktbuf *pbuf,
					   void __user *buf, u32 len)
{
	u32 avail;
	int ridx;
	struct pkt_hdr hdr;
	struct te_rb *rb = &pbuf->rb;

	if (READ_ONCE(rb->error))
		return -EIO;

	avail = __rbuf_avail_size(rb);
	if (!avail)
		return -ENODATA;

	if (avail < PKTBUF_HDR_SIZE)
		return -ESTRPIPE;

	ridx = __rbuf_idx_read(rb, rb->ridx, &hdr, PKTBUF_HDR_SIZE);
	avail -= PKTBUF_HDR_SIZE;
	if (avail < hdr.size)
		return -ESTRPIPE;

	if (len < hdr.size)
		return -ENOBUFS;

	ridx = __rbuf_idx_read_user(rb, ridx, buf, hdr.size);
	if (ridx < 0)
		return ridx;

	__rbuf_read_done(rb, ridx);

	return hdr.size;
}

/**
 * te_pktbuf_packet_read_user - Read only one packet in the packet buffer
 *
 * Return: the packet size on success,
 * -EIO if packet buffer has an error,
 * -ENODATA if no packet in the packet buffer,
 * -ENOBUFS when the @buf is not sufficient,
 * -ESTRPIPE if the packet buffer has broken,
 * -EFAULT if copy_to_user() fails
 */
int te_pktbuf_packet_read_user(struct te_pktbuf *pbuf,
			       void __user *buf, u32 len)
{
	if (pbuf->info)
		return __pktbuf_outer_packet_read_user(pbuf, buf, len);
	else
		return __pktbuf_inner_packet_read_user(pbuf, buf, len);
}

static int __pktbuf_outer_read_user(struct te_pktbuf *pbuf, void __user *buf,
				    u32 len)
{
	int ret = 0;
	int ridx, n;
	struct te_rb *rb = &pbuf->rb;
	struct pktbuf_info *bi = pbuf->info;
	struct pkt_info *pi;
	u32 todo = len;

	n = __pktbuf_info_avail_packet(bi);
	while (n--) {
		pi = __pktbuf_info_get_pkt(bi);
		if (todo < pi->size)
			break;

		ridx = __rbuf_idx_read_user(rb, pi->idx, buf, pi->size);
		if (ridx < 0) {
			ret = ridx;
			break;
		}

		__rbuf_read_done(rb, ridx);
		__pktbuf_info_dispose_pkt(bi);

		buf += pi->size;
		todo -= pi->size;
	}

	return (len - todo) ? (len - todo) : ret;
}

static int __pktbuf_inner_read_user(struct te_pktbuf *pbuf, void __user *buf,
				    u32 len)
{
	int ret = 0;
	u32 avail;
	int ridx;
	struct pkt_hdr hdr;
	struct te_rb *rb = &pbuf->rb;
	u32 todo = len;

	avail = __rbuf_avail_size(rb);
	while (avail) {
		if (avail < PKTBUF_HDR_SIZE) {
			ret = -ESTRPIPE;
			break;
		}

		ridx = __rbuf_idx_read(rb, rb->ridx, &hdr, PKTBUF_HDR_SIZE);
		avail -= PKTBUF_HDR_SIZE;
		if (avail < hdr.size) {
			ret = -ESTRPIPE;
			break;
		}

		if (todo < hdr.size)
			break;

		ridx = __rbuf_idx_read_user(rb, ridx, buf, hdr.size);
		if (ridx < 0) {
			ret = ridx;
			break;
		}

		__rbuf_read_done(rb, ridx);

		avail -= hdr.size;
		buf += hdr.size;
		todo -= hdr.size;
	}

	return (len - todo) ? (len - todo) : ret;
}

/**
 * te_pktbuf_read_user_timeout - Reads packets into a user pointer @buf
 * @timeout - timeout in ms, TE_BUF_INFINITE_TIMEOUT for infinite waiting
 *
 * Return: number of bytes read on success,
 * -EINVAL if input parameter is invalid
 * -EFAULT if copy_to_user is failed,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal,
 * -EIO if rbuf has an error,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_read_user_timeout(struct te_pktbuf *pbuf, void __user *buf,
				u32 len, unsigned long timeout)
{
	int rc;
	struct te_rb *rb = &pbuf->rb;

	rc = rb_wait_for_wevent(rb, __pktbuf_condition(pbuf), timeout);
	if (rc < 0)
		return rc;

	if (rb->error)
		return -EIO;

	if (pbuf->info)
		return __pktbuf_outer_read_user(pbuf, buf, len);
	else
		return __pktbuf_inner_read_user(pbuf, buf, len);
}

/**
 * te_pktbuf_io_read - Reads packets into a user pointer from read() syscall
 *
 * Return: number of bytes read on success,
 * -EWOULDBLOCK if @non_blocking is true and no available data in the buffer
 * -EINVAL if the buffer is not supported for input parameters,
 * -EFAULT if copy_to_user is failed,
 * -ERESTARTSYS if it was interrupted by a signal,
 * -EIO if rbuf has an error,
 * -ESTRPIPE if the packet buffer has broken.
 */
int te_pktbuf_io_read(struct te_pktbuf *pbuf, void __user *buf, u32 len,
		      bool non_blocking)
{
	int ret = 0, read_size = 0;
	unsigned long timeout;

	if (non_blocking) {
		if (!__pktbuf_condition(pbuf))
			return -EWOULDBLOCK;
		timeout = 0;
	} else {
		timeout = TE_BUF_INFINITE_TIMEOUT;
	}

	while (len) {
		ret = te_pktbuf_read_user_timeout(pbuf, buf, len, timeout);
		if (ret < 0)
			break;

		read_size += ret;

		if (non_blocking)
			break;

		len -= ret;
		buf += ret;
	}

	return (read_size) ? read_size : ret;
}

void te_pktbuf_flush(struct te_pktbuf *pbuf)
{
	struct te_rb *rb = &pbuf->rb;

	if (pbuf->info)
		__pktbuf_info_flush(pbuf->info);
	__rbuf_flush(rb);
}

/*************************************
         PACKET BUFFER END
 *************************************/

/*************************************
         MESSAGE BUFFER START
 *************************************/

int te_msgbuf_init(struct te_msgbuf *mbuf, u32 msize, u32 count, u32 flags)
{
	void *data;
	u32 len;

	if (!msize || !count)
		return -EINVAL;

	len = msize * (count + 1);
	data = vmalloc(len);
	if (!data)
		return -ENOMEM;

	__rbuf_init(&mbuf->rb, data, len, flags);

	mbuf->msize = msize;
	mbuf->count = count;

	return 0;
}

void te_msgbuf_release(struct te_msgbuf *mbuf)
{
	vfree(mbuf->rb.data);
}

void te_msgbuf_reset(struct te_msgbuf *mbuf)
{
	__rbuf_reset(&mbuf->rb);
}

u32 te_msgbuf_count(struct te_msgbuf *mbuf)
{
	return mbuf->count;
}
/* ==== PRODUCER ==== */

/**
 * te_msgbuf_free_count - Get free message buffer count
 */
u32 te_msgbuf_free_count(struct te_msgbuf *mbuf)
{
	u32 size = __rbuf_free_size(&mbuf->rb);

	return (u32)(size / mbuf->msize);
}

void te_msgbuf_set_error(struct te_msgbuf *mbuf, int err)
{
	__rbuf_set_error(&mbuf->rb, err);
}

static inline void __msgbuf_raw_write(struct te_msgbuf *mbuf, const void *msg,
				      u32 count)
{
	__rbuf_raw_write(&mbuf->rb, msg, mbuf->msize * count);
}

void te_msgbuf_raw_write(struct te_msgbuf *mbuf, const void *msg, u32 count)
{
	__msgbuf_raw_write(mbuf, msg, count);
}

/**
 * te_msgbuf_raw_get_wbuf - Get message pointer at widx + pos in the msg buffer
 *
 * It is useful to write the data directly if you want zero copy about message
 * It does NOT update the wdix in the message buffer
 */
void te_msgbuf_raw_get_wbuf(struct te_msgbuf *mbuf, u32 pos, void **msg)
{
	struct te_rb *rb = &mbuf->rb;
	u32 widx = rb->widx;

	if (pos)
		widx = __rbuf_idx_add(rb, widx, mbuf->msize * pos);

	*msg = rb->data + widx;
}

/**
 * te_msgbuf_raw_write_skip - Move widx of message buffer
 *
 * It is used if the data was already written using te_msgbuf_raw_get_wbuf
 */
void te_msgbuf_raw_write_skip(struct te_msgbuf *mbuf, u32 count)
{
	if (!count)
		return;

	__rbuf_raw_write_skip(&mbuf->rb, mbuf->msize * count);
}

/**
 * te_msgbuf_cwrite - Write @msg into the msg buffer after checking free size
 *
 * Return: 0 on success, -ENOBUFS if no free sufficient space
 */
int te_msgbuf_cwrite(struct te_msgbuf *mbuf, const void *msg, u32 count)
{
	u32 free_count = te_msgbuf_free_count(mbuf);

	if (free_count < count)
		return -ENOBUFS;

	__msgbuf_raw_write(mbuf, msg, count);

	return 0;
}

/* === CONSUMER === */
static inline u32 __msgbuf_avail_count(struct te_msgbuf *mbuf)
{
	return (u32)(__rbuf_avail_size(&mbuf->rb) / mbuf->msize);
}

static int __msgbuf_read_condition(struct te_msgbuf *mbuf)
{
	int error = READ_ONCE(mbuf->rb.error);

	if (error)
		return error;

	return __msgbuf_avail_count(mbuf);
}

u32 te_msgbuf_avail_count(struct te_msgbuf *mbuf)
{
	return __msgbuf_avail_count(mbuf);
}

void te_msgbuf_flush(struct te_msgbuf *mbuf)
{
	__rbuf_flush(&mbuf->rb);
}

void te_msgbuf_raw_read(struct te_msgbuf *mbuf, void *msg, u32 count)
{
	return __rbuf_raw_read(&mbuf->rb, msg, mbuf->msize * count);
}

/**
 * te_msgbuf_raw_get_rbuf - Get message pointer at ridx + pos in the msg buffer
 *
 * It does NOT update the rdix in the message buffer
 */
void te_msgbuf_raw_get_rbuf(struct te_msgbuf *mbuf, u32 pos, void **msg)
{
	struct te_rb *rb = &mbuf->rb;
	u32 ridx = rb->ridx;

	if (pos)
		ridx = __rbuf_idx_add(rb, ridx, mbuf->msize * pos);

	*msg = rb->data + ridx;
}

void te_msgbuf_raw_read_skip(struct te_msgbuf *mbuf, u32 count)
{
	if (!count)
		return;

	__rbuf_raw_read_skip(&mbuf->rb, mbuf->msize * count);
}

int te_msgbuf_read(struct te_msgbuf *mbuf, void *msg, u32 count)
{
	u32 avail_count = te_msgbuf_avail_count(mbuf);
	u32 rcount = min(avail_count, count);

	if (rcount)
		te_msgbuf_raw_read(mbuf, msg, rcount);

	return rcount;
}



/**
 * __msgbuf_wait_wevent - Wait for writing event
 *
 * Return: number of message in buffer on success,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO if mbuf has an error
 */
static int __msgbuf_wait_wevent(struct te_msgbuf *mbuf, unsigned long timeout)
{
	int ret;
	struct te_rb *rb = &mbuf->rb;

	ret = rb_wait_for_wevent(rb, __msgbuf_read_condition(mbuf), timeout);
	if (ret < 0)
		return ret;

	if (rb->error)
		return -EIO;

	return __msgbuf_avail_count(mbuf);
}

/**
 * te_msgbuf_wait_wevent - Wait for writing event
 *
 * Return: number of message in buffer on success,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO if mbuf has an error
 */
int te_msgbuf_wait_wevent(struct te_msgbuf *mbuf, unsigned long timeout)
{
	return __msgbuf_wait_wevent(mbuf, timeout);
}

int te_msgbuf_read_user(struct te_msgbuf *mbuf, void __user *buf, u32 count)
{
	u32 avail_count = __msgbuf_avail_count(mbuf);
	u32 rcount = min(avail_count, count);

	if (rcount)
		__rbuf_raw_read_user(&mbuf->rb, buf, mbuf->msize * rcount);

	return rcount;
}

int te_msgbuf_read_user_timeout(struct te_msgbuf *mbuf, void __user *buf,
				u32 count, int timeout)
{
	int ret;

	ret = __msgbuf_wait_wevent(mbuf, timeout);
	if (ret <= 0)
		return ret;

	return te_msgbuf_read_user(mbuf, buf, count);
}

/*************************************
         MESSAGE BUFFER END
 *************************************/

/*************************************
     H/W(DEVICE) BUFFER START
 *************************************/

/**
 * te_hwbuf_init - Initialize hw(physical memory) buffer
 * @addr: allocated physical address
 * @unit_size: unit size for event trigger
 * @flags:
 *	TE_BUF_FLAG_VMAP - map physical address to uncached memory
 *	TE_BUF_FLAG_VMAP_CACHED - map phsycial address to cached memory
 *	TE_BUF_FLAG_NO_EVENT - not raise event when data is read or written
 *
 * Return: 0 on success, -ENOMEM if vmap failed
 */
int te_hwbuf_init(struct te_hwbuf *hbuf, phys_addr_t addr, u32 len,
		  u32 unit_size, u32 flags)
{
	int ret;
	void *data = NULL;

	if (flags & TE_BUF_FLAG_VMAP) {
		data = te_vmap(addr, len, false);
		if (!data)
			return -ENOMEM;
	} else if (flags & TE_BUF_FLAG_VMAP_CACHED) {
		ret = te_cache_map_init(&hbuf->cache_map, addr, len);
		if (ret)
			return ret;

		data = hbuf->cache_map.vaddr;
	}

	__rbuf_init(&hbuf->rb, data, len, flags);

	hbuf->addr = addr;
	hbuf->unit_size = unit_size;
	hbuf->wrap_buf = NULL;

	return 0;
}

/**
 * te_hwbuf_vmap - Map phsycial memory to control directly
 *
 * It maps physcial memories if the hwbuffer is initialized without
 * TE_BUF_FLAG_VMAP and TE_BUF_FLAG_VMAP_CACHED and it's useful to control
 * memory directly.
 *
 * Return: 0 on success, -EBUSY if already mapped, -ENOMEM if vmap faield
 */
int te_hwbuf_vmap(struct te_hwbuf *hbuf, bool cached)
{
	struct te_rb *rb = &hbuf->rb;

	if (rb->data)
		return -EBUSY;

	rb->data = te_vmap(hbuf->addr, rb->size, cached);
	if (!rb->data)
		return -ENOMEM;

	return 0;
}

/**
 * te_hwbuf_vunmap - Unmap the memroy which is mapped using te_hwbuf_vmap
 */
void te_hwbuf_vunmap(struct te_hwbuf *hbuf)
{
	struct te_rb *rb = &hbuf->rb;

	if (!rb->data)
		return;

	if (rb->flags & (TE_BUF_FLAG_VMAP | TE_BUF_FLAG_VMAP_CACHED))
		return;

	te_vunmap(rb->data);
	rb->data = NULL;
}

/**
 * te_hwbuf_release - Release h/w buffer
 *
 * It will release resources that are mapped or allocated memories.
 * If te_hwbuf_init called with _VMAP flags or vmap directly
 * than must call this function others not needed.
 */
void te_hwbuf_release(struct te_hwbuf *hbuf)
{
	struct te_rb *rb = &hbuf->rb;

	if (hbuf->wrap_buf) {
		vfree(hbuf->wrap_buf);
	}

	if (rb->flags & TE_BUF_FLAG_VMAP_CACHED) {
		te_cache_map_release(&hbuf->cache_map);
	} else if (rb->data) {
		te_vunmap(rb->data);
	}
}

static void __hwbuf_cache_sync_area(struct te_hwbuf *hbuf, u32 sidx, u32 size,
				    enum te_data_direction dir)
{
	struct te_rb *rb = &hbuf->rb;

	if ((sidx + size) <= rb->size) {
		te_cache_map_sync(&hbuf->cache_map, sidx, size, dir);
	} else {
		u32 sz1 = rb->size - sidx;
		u32 sz2 = size - sz1;

		te_cache_map_sync(&hbuf->cache_map, sidx, sz1, dir);
		te_cache_map_sync(&hbuf->cache_map, 0, sz2, dir);
	}
}

static void __hwbuf_cache_sync_range(struct te_hwbuf *hbuf, u32 sidx, u32 eidx,
				     enum te_data_direction dir)
{
	struct te_rb *rb = &hbuf->rb;
	u32 len;

	if (sidx > eidx) {
		len = rb->size - sidx;
		te_cache_map_sync(&hbuf->cache_map, sidx, len, dir);

		sidx = 0;
		len = eidx;
	} else {
		len = eidx - sidx;
	}

	if (len) {
		te_cache_map_sync(&hbuf->cache_map, sidx, len, dir);
	}
}

static void __hwbuf_cache_inval(struct te_hwbuf *hbuf, u32 sidx, u32 eidx)
{
	__hwbuf_cache_sync_range(hbuf, sidx, eidx, TE_DATA_FROM_DEVICE);
}

static void __hwbuf_cache_clean(struct te_hwbuf *hbuf, u32 sidx, u32 eidx)
{
	__hwbuf_cache_sync_range(hbuf, sidx, eidx, TE_DATA_TO_DEVICE);
}

void te_hwbuf_reset(struct te_hwbuf *hbuf)
{
	__rbuf_reset(&hbuf->rb);
}

void te_hwbuf_get_info(struct te_hwbuf *hbuf, struct te_hwbuf_info *info)
{
	info->addr = hbuf->addr;
	info->size = hbuf->rb.size;
	info->unit_size = hbuf->unit_size;
	info->widx = READ_ONCE(hbuf->rb.widx);
	info->ridx = READ_ONCE(hbuf->rb.ridx);
}

static inline bool __hwbuf_is_invalid_addr(struct te_hwbuf *hbuf,
					   phys_addr_t addr)
{
	if (addr < hbuf->addr || addr >= (hbuf->addr + hbuf->rb.size))
		return true;

	return false;
}

bool te_hwbuf_is_invalid_paddr(struct te_hwbuf *hbuf, phys_addr_t addr)
{
	return __hwbuf_is_invalid_addr(hbuf, addr);
}

/*
 * te_hwbuf_paddr_to_idx - Convert physical address to butffer index
 *
 * Return: 0 if success, -EINVAl if addr or offset is invalid
 */
int te_hwbuf_paddr_to_idx(struct te_hwbuf *hbuf, phys_addr_t addr, u32 *idx)
{
	struct te_rb *rb = &hbuf->rb;
	phys_addr_t aidx = addr - hbuf->addr;

	if (aidx >= rb->size)
		return -EINVAL;

	*idx = (u32)aidx;

	return 0;
}

int te_hwbuf_idx_to_paddr(struct te_hwbuf *hbuf, u32 idx, phys_addr_t *addr)
{
	struct te_rb *rb = &hbuf->rb;

	if (idx >= rb->size)
		return -EINVAL;

	*addr = hbuf->addr + idx;

	return 0;
}

void te_hwbuf_set_read_callback(struct te_hwbuf *hbuf,
				te_buf_callback_func_t func, void *arg)
{
	__rbuf_set_callback(&hbuf->rb, TE_BUF_CONSUMER, func, arg);
}

void te_hwbuf_set_write_callback(struct te_hwbuf *hbuf,
				 te_buf_callback_func_t func, void *arg)
{
	__rbuf_set_callback(&hbuf->rb, TE_BUF_PRODUCER, func, arg);
}

/**
 * __hwbuf_get_buf2 - Get available buffer and length at idx + offset
 */
static void __hwbuf_get_buf2(struct te_hwbuf *hbuf, u32 idx, u32 offset,
			     u32 len, void **buf1, u32 *len1,
			     void **buf2, u32 *len2)
{
	struct te_rb *rb = &hbuf->rb;
	u32 idx1;

	__rbuf_get_idx2(rb, idx, offset, len, &idx1, len1, len2);

	*buf1 = rb->data + idx1;
	if (*len2)
		*buf2 = rb->data;
	else
		*buf2 = NULL;
}


/**
 * te_hwbuf_cache_sync - Sync the length of cache data from idx of hwbuffer
 *
 * Return: 0 on success, -EINVAL if idx or len is invalid
 */
int te_hwbuf_cache_sync(struct te_hwbuf *hbuf, u32 idx, u32 len,
			enum te_data_direction dir)
{
	struct te_rb *rb = &hbuf->rb;

	if (!(rb->flags & TE_BUF_FLAG_VMAP_CACHED))
		return 0;

	if (idx >= rb->size || len > rb->size)
		return -EINVAL;

	__hwbuf_cache_sync_area(hbuf, idx, len, dir);

	return 0;
}

/**
 * te_hwbuf_get_paddr_buf2 - Get buffer pointer with phys addr and length
 * in the the hw buffer
 *
 * Return: 0 on success, -EIVAL if addr is invald
 */
int te_hwbuf_get_paddr_buf2(struct te_hwbuf *hbuf,
			    phys_addr_t addr, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	u32 idx;

	idx = (u32)(addr - hbuf->addr);
	if (idx >= hbuf->rb.size)
		return -EINVAL;

	__hwbuf_get_buf2(hbuf, idx, offset, len, buf1, len1, buf2, len2);

	return 0;
}

/* ==== PRODUCER ==== */
u32 te_hwbuf_free_size(struct te_hwbuf *hbuf)
{
	return __rbuf_free_size(&hbuf->rb);
}

/**
 * te_hwbuf_set_widx - set widx in hwbuffer
 *
 * CAUTION: It should update widx evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if widx is invalid,
 * -EOVERFLOW if overflow happens(widx overtakes ridx)
 */
int te_hwbuf_set_widx(struct te_hwbuf *hbuf, u32 widx)
{
	int ret;
	struct te_rb *rb = &hbuf->rb;
	u32 len;

	if (rb->widx == widx)
		return 0;

	if (widx >= rb->size)
		return -EINVAL;

	len = __rbuf_diff_idx(rb, rb->widx, widx);
	if (len > __rbuf_free_size(rb))
		ret = -EOVERFLOW;
	else
		ret = 0;

	if (rb->flags & TE_BUF_FLAG_VMAP_CACHED) {
		if (rb->flags & TE_BUF_FLAG_UPLOAD_MODULE)
			__hwbuf_cache_clean(hbuf, rb->widx, widx);
		else
			__hwbuf_cache_inval(hbuf, rb->widx, widx);
	}

	__rbuf_write_done(rb, widx);

	return ret ? ret : len;
}

/**
 * te_hwbuf_set_wptr - set wptr in hwbuffer
 *
 * CAUTION: It should update widx evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if wptr is invalid address,
 * -EOVERFLOW if overflow happens(wptr overtakes rptr)
 */
int te_hwbuf_set_wptr(struct te_hwbuf *hbuf, phys_addr_t wptr)
{
	phys_addr_t widx;

	widx = wptr - hbuf->addr;
	if (widx >= hbuf->rb.size)
		return -EINVAL;

	return te_hwbuf_set_widx(hbuf, (u32)widx);
}

/**
 * te_hwbuf_cwrite - Write a @buf into the hw buffer after checking free size
 *
 * It checks free size is more than @len if not, it returns -ENOBUFS
 *
 * Return: 0 on success, -ENOBUFS if no sufficient free buffer to write
 */
int te_hwbuf_cwrite(struct te_hwbuf *hbuf, const void *buf, u32 len)
{
	struct te_rb *rb = &hbuf->rb;
	u32 free_size = __rbuf_free_size(rb);
	u32 widx = rb->widx;
	u32 next_idx;

	if (free_size < len)
		return -ENOBUFS;

	next_idx = __rbuf_idx_write(rb, widx, buf, len);
	if (rb->flags & TE_BUF_FLAG_VMAP_CACHED)
		__hwbuf_cache_clean(hbuf, widx, next_idx);

	__rbuf_write_done(rb, next_idx);

	return 0;
}

/**
 * te_hwbuf_cwrite2 - Write two buffers into the hw buffer after checking
 * free size
 *
 * It checks free size is more than @len1 + @len2 if not, it returns -ENOBUFS
 *
 * Return: 0 on success, -ENOBUFS if no sufficient free buffer to write
 */
int te_hwbuf_cwrite2(struct te_hwbuf *hbuf, const void *buf1, u32 len1,
		     const void *buf2, u32 len2)
{
	struct te_rb *rb = &hbuf->rb;
	u32 free_size = __rbuf_free_size(rb);
	u32 len = len1 + len2;
	u32 widx = rb->widx;
	u32 next_idx;

	if (free_size < len)
		return -ENOBUFS;

	next_idx = __rbuf_idx_write2(rb, widx, buf1, len1, buf2, len2);
	if (rb->flags & TE_BUF_FLAG_VMAP_CACHED)
		__hwbuf_cache_clean(hbuf, widx, next_idx);

	__rbuf_write_done(rb, next_idx);

	return len;
}

void te_hwbuf_set_error(struct te_hwbuf *hbuf, int err)
{
	__rbuf_set_error(&hbuf->rb, err);
}

static int __hwbuf_write_condition(struct te_hwbuf *hbuf)
{
	u32 size;
	struct te_rb *rb = &hbuf->rb;

	if (READ_ONCE(rb->error))
		return -EIO;

	size = __rbuf_free_size(rb);
	if (hbuf->unit_size && size < hbuf->unit_size)
		return 0;

	return size;
}

/**
 * __hwbuf_raw_write_user - write a user pointer @buf into the hw buffer
 *
 * Return: 0 on success, -EFAULT if copy_from_user() fails
 */
static int __hwbuf_raw_write_user(struct te_hwbuf *hbuf,
				  const void __user *buf, u32 len)
{
	int next_idx;
	struct te_rb *rb = &hbuf->rb;
	u32 widx = rb->widx;

	next_idx = __rbuf_idx_write_user(rb, widx, buf, len);
	if (next_idx < 0)
		return next_idx;

	if (rb->flags & TE_BUF_FLAG_VMAP_CACHED) {
		__hwbuf_cache_clean(hbuf, widx, next_idx);
	}

	__rbuf_write_done(rb, next_idx);

	return 0;
}

/**
 * __hwbuf_write_user - write a user pointer @buf into the hw buffer
 *
 * It starts from the last write position(@rb->widx) and
 * writes up to @len bytes or till it reaches the free size
 *
 * Return: number of bytes written on success,
 * -EFAULT if copy_from_user() fails
 */
static int __hwbuf_write_user(struct te_hwbuf *hbuf, const void __user *buf,
			      u32 len)
{
	int rc;
	struct te_rb *rb = &hbuf->rb;
	u32 size;

	size = __rbuf_free_size(rb);
	if (!size)
		return 0;

	if (size < len)
		len = size;

	rc = __hwbuf_raw_write_user(hbuf, buf, len);
	if (rc)
		return rc;

	return len;
}

/**
 * te_hwbuf_cwrite_user - write a user pointer @buf into the hw buffer after
 * checking free size
 *
 * It checks free size is more than @len if not, it returns -ENOBUFS
 *
 * Return: 0 on success,
 * -ENOBUFS if no sufficient free buffer to write
 * -EFAULT if copy_from_user() fails
 */
int te_hwbuf_cwrite_user(struct te_hwbuf *hbuf, const void __user *buf, u32 len)
{
	struct te_rb *rb = &hbuf->rb;
	u32 free_size = __rbuf_free_size(rb);

	if (free_size < len)
		return -ENOBUFS;

	return __hwbuf_raw_write_user(hbuf, buf, len);
}

/**
 * te_hwbuf_write_user_timeout - write a user pointer @buf into the hw buffer
 * @timeout - timeout in ms, TE_BUF_INFINITE_TIMEOUT for infinite waiting
 *
 * Return: number of bytes written on success,
 * -EINVAL if input parameter is invalid
 * -EFAULT if copy_to_user() fails,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO if hbuf has an error
 */
int te_hwbuf_write_user_timeout(struct te_hwbuf *hbuf, const void __user *buf,
				u32 len, unsigned long timeout)
{
	int rc;
	struct te_rb *rb = &hbuf->rb;

	rc = rb_wait_for_revent(rb, __hwbuf_write_condition(hbuf), timeout);
	if (rc < 0)
		return rc;

	if (rb->error)
		return -EIO;

	return __hwbuf_write_user(hbuf, buf, len);
}

int te_hwbuf_io_write(struct te_hwbuf *hbuf, const void __user *buf,
		      u32 len, bool non_blocking)
{
	int ret = 0, wsize = 0;
	unsigned long timeout;

	if (non_blocking) {
		if (!__hwbuf_write_condition(hbuf))
			return -EWOULDBLOCK;
		timeout = 0;
	} else {
		timeout = TE_BUF_INFINITE_TIMEOUT;
	}

	while (len) {
		ret = te_hwbuf_write_user_timeout(hbuf, buf, len, timeout);
		if (ret < 0)
			break;

		wsize += ret;
		if (non_blocking)
			break;

		len -= ret;
		buf += ret;
	}

	return (wsize) ? wsize : ret;
}


/**
 * te_hwbuf_raw_get_wbuf2 - Get buffer pointer at widx in the hw buffer
 *
 * Note: *buf2 = NULL and *len2 = 0 if buffer is not wrap-arounded
 */
void te_hwbuf_raw_get_wbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	u32 widx = hbuf->rb.widx;
	__hwbuf_get_buf2(hbuf, widx, offset, len, buf1, len1, buf2, len2);
}

/**
 * te_hwbuf_get_wbuf2 - Get buffer pointer at widx in the hw buffer
 *
 * Note: *buf2 = NULL and *len2 = 0 if buffer is not wrap-arounded
 *
 * Return: 0 on success, -ENOBUFS if no free space
 */
int te_hwbuf_get_wbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
		       void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	if (__rbuf_free_size(&hbuf->rb) < (offset + len))
		return -ENOBUFS;

	te_hwbuf_raw_get_wbuf2(hbuf, offset, len, buf1, len1, buf2, len2);

	return 0;
}

/* === CONSUMER === */

static int __hwbuf_read_condition(struct te_hwbuf *hbuf)
{
	u32 size;
	struct te_rb *rb = &hbuf->rb;

	if (READ_ONCE(rb->error))
		return -EIO;

	size = __rbuf_avail_size(rb);
	if (hbuf->unit_size && size < hbuf->unit_size)
		return 0;

	return size;
}

/**
 * te_hwbuf_read_condition - check condition to read buffer
 *
 * Return: number of bytes to read or -EIO if hbuf has an error
 */
int te_hwbuf_read_condition(struct te_hwbuf *hbuf)
{
	return __hwbuf_read_condition(hbuf);
}

/**
 * te_hwbuf_wait_wevent - Wait for writing event
 *
 * Return: number of bytes to read in buffer on success,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO if hbuf has an error
 */
int te_hwbuf_wait_wevent(struct te_hwbuf *hbuf, unsigned long timeout)
{
	int ret;
	struct te_rb *rb = &hbuf->rb;

	ret = rb_wait_for_wevent(rb, __hwbuf_read_condition(hbuf), timeout);
	if (ret < 0)
		return ret;

	if (rb->error)
		return -EIO;

	return te_hwbuf_avail_size(hbuf);
}

/**
 * te_hwbuf_set_ridx - set ridx in hwbuffer
 *
 * CAUTION: It should update ridx evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if ridx is invalid,
 * -EOVERFLOW if overflow happens(ridx overtakes widx)
 */
int te_hwbuf_set_ridx(struct te_hwbuf *hbuf, u32 ridx)
{
	int ret;
	struct te_rb *rb = &hbuf->rb;
	u32 len;

	if (rb->ridx == ridx)
		return 0;

	if (ridx >= rb->size)
		return -EINVAL;

	len = __rbuf_diff_idx(rb, rb->ridx, ridx);
	if (len > __rbuf_avail_size(rb))
		ret = -EOVERFLOW;
	else
		ret = 0;

	__rbuf_read_done(rb, ridx);

	return ret ? ret : len;
}

/**
 * te_hwbuf_set_rptr - set rptr in hwbuffer
 *
 * CAUTION: It should update rptr evenif buffer overflow happens
 *
 * Return: number of skip bytes on success,
 * -EINVAL if rptr is invalid,
 * -EOVERFLOW if overflow happens(rptr overtakes wptr)
 */
int te_hwbuf_set_rptr(struct te_hwbuf *hbuf, phys_addr_t rptr)
{
	phys_addr_t ridx;

	ridx = rptr - hbuf->addr;
	if (ridx >= hbuf->rb.size)
		return -EINVAL;

	return te_hwbuf_set_ridx(hbuf, (u32)ridx);
}

/**
 * te_hwbuf_raw_peek - Peek length of data at offset in the hw buffer
 *
 * It does NOT update the ridx in the hw buffer
 */
void te_hwbuf_raw_peek(struct te_hwbuf *hbuf, u32 offset, void *buf, u32 len)
{
	struct te_rb *rb = &hbuf->rb;
	u32 ridx = rb->ridx;

	if (offset)
		ridx = __rbuf_idx_add(rb, ridx, offset);

	__rbuf_idx_read(rb, ridx, buf, len);
}

/**
 * te_hwbuf_peek - Peek length of data at offset in the hw buffer
 *
 * It does NOT update the ridx in the hw buffer
 *
 * Return: 0 on success, or -ENODATA if no available size
 */
int te_hwbuf_peek(struct te_hwbuf *hbuf, u32 offset, void *buf, u32 len)
{
	u32 size;

	size = __rbuf_avail_size(&hbuf->rb);
	if (size < (offset + len))
		return -ENODATA;

	te_hwbuf_raw_peek(hbuf, offset, buf, len);

	return 0;
}

int te_hwbuf_read_skip(struct te_hwbuf *hbuf, u32 len)
{
	u32 size, ridx;
	struct te_rb *rb = &hbuf->rb;

	size = __rbuf_avail_size(rb);
	if (size < len)
		return -ENODATA;

	ridx = __rbuf_idx_add(rb, rb->ridx, len);

	__rbuf_read_done(rb, ridx);

	return 0;
}

void te_hwbuf_raw_read(struct te_hwbuf *hbuf, void *buf, u32 len)
{
	u32 next_idx;
	struct te_rb *rb = &hbuf->rb;

	next_idx = __rbuf_idx_read(rb, rb->ridx, buf, len);

	__rbuf_read_done(rb, next_idx);
}

int te_hwbuf_read(struct te_hwbuf *hbuf, void *buf, u32 len)
{
	u32 size;
	struct te_rb *rb = &hbuf->rb;

	size = __rbuf_avail_size(rb);
	if (!size)
		return 0;

	if (size > len)
		size = len;

	te_hwbuf_raw_read(hbuf, buf, size);

	return size;
}

static int __hwbuf_read_user(struct te_hwbuf *hbuf, void __user *buf, u32 len)
{
	int next_idx;
	u32 size;
	struct te_rb *rb = &hbuf->rb;

	size = __rbuf_avail_size(rb);
	if (!size)
		return 0;

	if (size > len)
		size = len;

	next_idx = __rbuf_idx_read_user(rb, rb->ridx, buf, size);
	if (next_idx < 0)
		return next_idx;

	__rbuf_read_done(rb, next_idx);

	return size;
}

/**
 * te_hwbuf_read_user_idx - Reads a buffer into a user pointer @buf
 *
 * Return: number of bytes read on success,
 * -ENODATA if available size is less than @len
 * -EFAULT if copy_to_user is failed,
 */
int te_hwbuf_read_user_idx(struct te_hwbuf *hbuf, void __user *buf, u32 idx,
			   u32 len)
{
	struct te_rb *rb = &hbuf->rb;
	int next_idx;
	u32 size;

	size = __rbuf_avail_size(rb);
	if (!size)
		return 0;

	if (size < len)
		return -ENODATA;

	next_idx = __rbuf_idx_read_user(rb, idx, buf, len);
	if (next_idx < 0)
		return next_idx;

	__rbuf_read_done(rb, next_idx);

	return len;
}

/**
 * te_hwbuf_read_user_timeout - Reads a buffer into a user pointer @buf
 * @timeout - timeout in ms, TE_BUF_INFINITE_TIMEOUT for infinite waiting
 *
 * Return: number of bytes read on success,
 * -EINVAL if input parameter is invalid
 * -EFAULT if copy_to_user is failed,
 * -ETIME if @timeout elapsed,
 * -ERESTARTSYS if it was interrupted by a signal or
 * -EIO : if hbuf has error
 */
int te_hwbuf_read_user_timeout(struct te_hwbuf *hbuf, void __user *buf,
			       u32 len, unsigned long timeout)
{
	int rc;
	struct te_rb *rb = &hbuf->rb;

	rc = rb_wait_for_wevent(rb, __hwbuf_read_condition(hbuf), timeout);
	if (rc < 0)
		return rc;

	if (rb->error)
		return -EIO;

	return __hwbuf_read_user(hbuf, buf, len);
}

int te_hwbuf_io_read(struct te_hwbuf *hbuf, void __user *buf, u32 len,
		     bool non_blocking)
{
	int ret = 0, read_size = 0;
	unsigned long timeout;

	if (non_blocking) {
		if (!__hwbuf_read_condition(hbuf))
			return -EWOULDBLOCK;
		timeout = 0;
	} else {
		timeout = TE_BUF_INFINITE_TIMEOUT;
	}

	while (len) {
		ret = te_hwbuf_read_user_timeout(hbuf, buf, len, timeout);
		if (ret < 0)
			break;

		read_size += ret;

		if (non_blocking)
			break;

		len -= ret;
		buf += ret;
	}

	return (read_size) ? read_size : ret;
}

u32 te_hwbuf_avail_size(struct te_hwbuf *hbuf)
{
	return __rbuf_avail_size(&hbuf->rb);
}

void te_hwbuf_flush(struct te_hwbuf *hbuf)
{
	__rbuf_flush(&hbuf->rb);
}

static int __hwbuf_get_cont_rbuf(struct te_hwbuf *hbuf, u32 idx,
				 u32 offset, u32 len, void **buf)
{
	struct te_rb *rb = &hbuf->rb;

	if (offset)
		idx = __rbuf_idx_add(rb, idx, offset);

	if ((idx + len) > rb->size) {
		if (hbuf->wrap_buf)
			vfree(hbuf->wrap_buf);

		hbuf->wrap_buf = vmalloc(len);
		if (!hbuf->wrap_buf)
			return -ENOMEM;

		__rbuf_idx_read(rb, idx, hbuf->wrap_buf, len);
		*buf = hbuf->wrap_buf;
	} else
		*buf = rb->data + idx;

	return 0;
}


/**
 * te_hwbuf_raw_get_cont_rbuf - Get the continuous buffer pointer at
 * ridx + offset in the hw buffer
 *
 * If the length of the data in the buffer is not continuous, it will allocate
 * a new buffer to make the consecutive space which has wrap around data.
 *
 * Return: 0 on success, or -ENOMEM if no memory.
 */
int te_hwbuf_raw_get_cont_rbuf(struct te_hwbuf *hbuf, u32 offset, u32 len,
			       void **buf)
{
	return __hwbuf_get_cont_rbuf(hbuf, hbuf->rb.ridx, offset, len, buf);
}

/**
 * te_hwbuf_get_cont_rbuf - Get the continuous buffer pointer at ridx + offset
 * in the hw buffer
 *
 * If the length of the data in the buffer is not continuous, it will allocate
 * a new buffer to make the consecutive space which has wrap around data.
 *
 * Return: 0 on success, or -ENODATA if offset + len is over avail size,
 * -ENOMEM if no memory.
 */
int te_hwbuf_get_cont_rbuf(struct te_hwbuf *hbuf, u32 offset, u32 len,
			   void **buf)
{
	if (__rbuf_avail_size(&hbuf->rb) < (offset + len))
		return -ENODATA;

	return te_hwbuf_raw_get_cont_rbuf(hbuf, offset, len, buf);
}

/**
 * te_hwbuf_get_paddr_cont_rbuf - Get continuous buffer pointer at phys addr in
 * the hw buffer
 *
 * Note: It will allocate buffer if the length of data is not continuous
 *  in hw buffer so call te_hwbuffer_free_data after using it
 *
 * Return: 0 if success, -EIVAL if ptr is invald or -ENOMEM.
 */
int te_hwbuf_get_paddr_cont_rbuf(struct te_hwbuf *hbuf, phys_addr_t addr,
				 u32 offset, u32 len, void **buf)
{
	u32 idx;

	idx = (u32)(addr - hbuf->addr);
	if (idx >= hbuf->rb.size)
		return -EINVAL;

	return __hwbuf_get_cont_rbuf(hbuf, idx, offset, len, buf);
}


/**
 * te_hwbuf_raw_get_rbuf2 - Get buffer pointer at ridx in the hw buffer
 *
 * DEPRECATED. Use te_hwbuf_raw_get_split_rbuf instead.
 * Note: *buf2 = NULL and *len2 = 0 if buffer is not wrap-arounded
 */
void te_hwbuf_raw_get_rbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	u32 ridx = hbuf->rb.ridx;
	__hwbuf_get_buf2(hbuf, ridx, offset, len, buf1, len1, buf2, len2);
}

/**
 * te_hwbuf_raw_get_split_rbuf - Get the buffer pointer of the available data
 *
 * Same as te_hwbuf_raw_get_rbuf2 but argument is @struct te_split_buffer
 */
void te_hwbuf_raw_get_split_rbuf(struct te_hwbuf *hbuf, u32 len,
				 struct te_split_buffer *buf)
{
	struct te_rb *rb = &hbuf->rb;
	__rbuf_get_split_buf(rb, rb->ridx, 0, len, buf);
}


/**
 * te_hwbuf_get_rbuf2 - Get buffer pointer at ridx in the hw buffer
 *
 * DEPRECATED. Use te_hwbuf_get_split_rbuf instead.
 * Note: *buf2 = NULL and *len2 = 0 if buffer is not wrap-arounded
 *
 * Return: 0 on success, -ENODATA if no available size
 */
int te_hwbuf_get_rbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
		       void **buf1, u32 *len1, void **buf2, u32 *len2)
{
	if (__rbuf_avail_size(&hbuf->rb) < (offset + len))
		return -ENODATA;

	te_hwbuf_raw_get_rbuf2(hbuf, offset, len, buf1, len1, buf2, len2);
	return 0;
}


/**
 * te_hwbuf_get_split_rbuf - Get the buffer pointer of the available data
 *
 * Return: 0 on success, -ENODATA if available size is less than @len
 */
int te_hwbuf_get_split_rbuf(struct te_hwbuf *hbuf, u32 len,
			    struct te_split_buffer *buf)
{
	if (__rbuf_avail_size(&hbuf->rb) < len)
		return -ENODATA;

	te_hwbuf_raw_get_split_rbuf(hbuf, len, buf);

	return 0;
}

/*************************************
     H/W(DEVICE) BUFFER END
 *************************************/
