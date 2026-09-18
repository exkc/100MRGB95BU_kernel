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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-06-27
 *  @note		see Documentation/circular-buffers.txt
 */

#ifndef	_LG1K_TE_BUFFER_H_
#define	_LG1K_TE_BUFFER_H_

#include <linux/types.h>
#include <linux/wait.h>
#include <linux/bitops.h>

#include "util.h"

/**
 * DOC: TE BUFFER API
 *
 * TE BUFFER provides a number of features that can be used to control buffer
 * TODO: add descriptions
 *
 * Returns:
 *	-ENOBUFS: no sufficient free space to write
 *	-ENODATA: no avaiable data to read
 *	-EOVERFLOW: overflow happens and already set
 *	-EINVAL: invalid input parameter
 *	-EIO: buffer has an error
 *
 * Buffer Error:
 *	-ENOBUFS: buffer overflow
 *	-ESHUTDOWN: no more use or stopped
 *	-ETIME: timer expired
 *
 * Error Handling:
 *	if the buffer has an error, it returns -EIO in read functions and user
 *	have to flush the buffer or clear error using set_error function
 *	In upload module, how to control ?
 *
 *
 * Naming Rules:
 *  ~_reset: resets widx,ridx and error to initail state
 *  ~_flush: sets ridx to widx and resets error
 *  ~_raw_~: not check buffer status
 *  ~_get_~: gets buffer pointer at widx/ridx in the buffer
 *  ~_cread,~cwrite: write/read whole length of data after checking buffer
 *  ~_io_read,~_io_write: sys call read/write function
 *  ~_write2,~read2: use separated two buffers for input parameters
 *  ~_skip: updates index, data must be written or read before calling it
 */

/**
 * TE_BUF_FLAG - flags to set the buffer attribute
 *
 * TE_BUF_FLAG_NO_EVENT:
 *	not raise event when data is read or written
 * TE_BUF_FLAG_UPLOAD_MODULE:
 *	raise event when reading data, and so on.
 * TE_BUF_FLAG_MANUAL_IDX:
 *	index controlled on manual, it depends on buffer type
 * TE_BUF_FLAG_LINEAR_BUFFER:
 *	only used in packet buffer and signle packet uses linear buffer
 * TE_BUF_FLAG_INNER_PKTINFO:
 *	adds a packet info to the buffer with a packet.
 *	normal packet buffer allocates memory to store the packet information,
 *	it is useful to use h/w buffer as a packet buffer directly, but this
 *	another memory for information makes a dependency as if buffer overflow
 *	happens if no avaialbe packet information memory evenif	enough buffer
 *	space exists.
 * TE_BUF_FLAG_VMAP:
 * TE_BUF_FLAG_VMAP_CACHED:
 *	only used in h/w buffer and mapped physical address
 */
#define TE_BUF_FLAG_NO_EVENT		BIT(0)
#define TE_BUF_FLAG_UPLOAD_MODULE	BIT(1)
#define TE_BUF_FLAG_MANUAL_IDX		BIT(5)
#define TE_BUF_FLAG_LINEAR_BUFFER	BIT(10)
#define TE_BUF_FLAG_INNER_PKTINFO	BIT(11)
#define TE_BUF_FLAG_VMAP		BIT(20)
#define TE_BUF_FLAG_VMAP_CACHED		BIT(21)

#define TE_BUF_INFINITE_TIMEOUT		ULONG_MAX

#define TE_BUF_IDX_RESET		((u32)-1)
#define TE_BUF_IDX_FLUSH		((u32)-2)

enum te_buf_owner {
	TE_BUF_PRODUCER = 0,
	TE_BUF_CONSUMER,
	TE_BUF_OWNER_MAX,
};

typedef void (*te_buf_callback_func_t)(void *arg, u32 idx);
struct te_buf_callback {
	te_buf_callback_func_t func;
	void *arg;
};

struct te_rb {
	u8 *data;
	u32 size;
	u32 widx;
	u32 ridx;
	int error;		/* errno.h */
	unsigned long flags;	/* TE_BUF_FLAG_XXX */
	wait_queue_head_t wq;
	struct te_buf_callback callback[TE_BUF_OWNER_MAX];
};

struct te_buffer {
	u8 *data;
	u32 size;
};

struct te_split_buffer {
	u32 size;
	struct te_buffer b[2];
};


#define te_buf_data(b)	((b)->rb.data)
#define te_buf_size(b)	((b)->rb.size)
#define te_buf_error(b)	READ_ONCE((b)->rb.error)
#define te_buf_wq(b)	(&(b)->rb.wq)

static inline u32 __rb_diff_idx(struct te_rb *rb, u32 idx1, u32 idx2)
{
	return (idx2 < idx1) ? rb->size - idx1 + idx2 : idx2 - idx1;
}

/*************************************
         RING BUFFER
 *************************************/
struct te_ringbuf {
	struct te_rb rb;
};

void te_ringbuf_init(struct te_ringbuf *rbuf, void *data, u32 len, u32 flags);
void te_ringbuf_reset(struct te_ringbuf *rbuf);

void te_ringbuf_set_write_callback(struct te_ringbuf *rbuf,
				   te_buf_callback_func_t func, void *arg);
void te_ringbuf_set_read_callback(struct te_ringbuf *rbuf,
				  te_buf_callback_func_t func, void *arg);

#define te_ringbuf_data(b)	te_buf_data(b)
#define te_ringbuf_size(b)	te_buf_size(b)
#define te_ringbuf_error(b)	te_buf_error(b)
#define te_ringbuf_wq(b)	te_buf_wq(b)
#define te_ringbuf_ridx(b)	(READ_ONCE((b)->rb.ridx))
#define te_ringbuf_widx(b)	(READ_ONCE((b)->rb.widx))

/* ==== PRODUCER ==== */
u32 te_ringbuf_free_size(struct te_ringbuf *rbuf);
void te_ringbuf_set_error(struct te_ringbuf *rbuf, int err);

void te_ringbuf_raw_write(struct te_ringbuf *rbuf, const void *buf, u32 len);
void te_ringbuf_raw_write2(struct te_ringbuf *rbuf, const void *buf1,
			   u32 len1, const void *buf2, u32 len2);

int te_ringbuf_cwrite(struct te_ringbuf *rbuf, const void *buf, u32 len);
int te_ringbuf_cwrite2(struct te_ringbuf *rbuf, const void *buf1, u32 len1,
		       const void *buf2, u32 len2);
int te_ringbuf_set_widx(struct te_ringbuf *rbuf, u32 widx);

int te_ringbuf_write_user_timeout(struct te_ringbuf *rbuf,
				  const void __user *buf, u32 len,
				  unsigned long timeout);
int te_ringbuf_io_write(struct te_ringbuf *rbuf, const void __user *buf,
			u32 len, bool non_blocking);

/* ==== CONSUMER ==== */
u32 te_ringbuf_avail_size(struct te_ringbuf *rbuf);
int te_ringbuf_set_ridx(struct te_ringbuf *rbuf, u32 ridx);
void te_ringbuf_get_ridx(struct te_ringbuf *rbuf, u32 offset, u32 *idx);
void te_ringbuf_raw_peek(struct te_ringbuf *rbuf, u32 offset, void *buf,
			 u32 len);
int te_ringbuf_peek(struct te_ringbuf *rbuf, u32 offset, void *buf, u32 len);
void te_ringbuf_flush(struct te_ringbuf *rbuf);

void te_ringbuf_raw_read(struct te_ringbuf *rbuf, void *buf, u32 len);
int te_ringbuf_read(struct te_ringbuf *rbuf, void *buf, u32 len);
int te_ringbuf_read_skip(struct te_ringbuf *rbuf, u32 len);

void te_ringbuf_raw_get_rbuf2(struct te_ringbuf *rbuf, u32 offset, u32 len,
			      void **buf1, u32 *len1, void **buf2, u32 *len2);
int te_ringbuf_raw_read_user(struct te_ringbuf *rbuf, void __user *buf,
			     u32 len);
int te_ringbuf_read_user_timeout(struct te_ringbuf *rbuf, void __user *buf,
				 u32 len, unsigned long timeout);
int te_ringbuf_io_read(struct te_ringbuf *rbuf, void __user *buf, u32 len,
		       bool non_blocking);

/*************************************
         PACKET BUFFER
 *************************************/
struct te_pktbuf {
	struct te_rb rb;
	void *info;
};

int te_pktbuf_init(struct te_pktbuf *pbuf, void *data, u32 len,
		   u32 pkt_size, u32 flags);
void te_pktbuf_release(struct te_pktbuf *pbuf);
void te_pktbuf_reset(struct te_pktbuf *pbuf);

void te_pktbuf_set_write_callback(struct te_pktbuf *pbuf,
				  te_buf_callback_func_t func,
				  void *arg);
void te_pktbuf_set_read_callback(struct te_pktbuf *pbuf,
				 te_buf_callback_func_t func,
				 void *arg);

#define te_pktbuf_data(pbuf)	te_buf_data(pbuf)
#define te_pktbuf_size(pbuf)	te_buf_size(pbuf)
#define te_pktbuf_error(pbuf)	te_buf_error(pbuf)
#define te_pktbuf_wq(pbuf)	te_buf_wq(pbuf)

/* ==== PRODUCER ==== */
u32 te_pktbuf_free_size(struct te_pktbuf *pbuf);
void te_pktbuf_set_error(struct te_pktbuf *pbuf, int err);

int te_pktbuf_packet_write(struct te_pktbuf *pbuf, const void *pkt, u32 len);
int te_pktbuf_packet_write2(struct te_pktbuf *pbuf, const void *pkt1, u32 len1,
			    const void *pkt2, u32 len2);

int te_pktbuf_get_wbuf2(struct te_pktbuf *pbuf, u32 len,
			void **buf1, u32 *len1, void **buf2, u32 *len2);
int te_pktbuf_get_cont_wbuf(struct te_pktbuf *pbuf, u32 len, void **buf);

int te_pktbuf_add_packet(struct te_pktbuf *pbuf, void *packet, u32 len);
int te_pktbuf_add_packet_idx(struct te_pktbuf *pbuf, u32 sidx, u32 eidx);


/* ==== CONSUMER ==== */
int te_pktbuf_avail_size(struct te_pktbuf *pbuf);
void te_pktbuf_flush(struct te_pktbuf *pbuf);
int te_pktbuf_avail_packet(struct te_pktbuf *pbuf);
int te_pktbuf_next_packet_size(struct te_pktbuf *pbuf);

int te_pktbuf_packet_read(struct te_pktbuf *pbuf, void *buf, u32 len);
int te_pktbuf_packet_read_user(struct te_pktbuf *pbuf,
			       void __user *buf, u32 len);

int te_pktbuf_read_user_timeout(struct te_pktbuf *pbuf, void __user *buf,
				u32 len, unsigned long timeout);
int te_pktbuf_io_read(struct te_pktbuf *pbuf, void __user *buf, u32 len,
		      bool non_blocking);


/*************************************
         MESSAGE BUFFER
 *************************************/
struct te_msgbuf {
	struct te_rb rb;
	u32 msize;		/* message size */
	u32 count;
};

int te_msgbuf_init(struct te_msgbuf *mbuf, u32 msg_size, u32 count, u32 flags);
void te_msgbuf_release(struct te_msgbuf *mbuf);
void te_msgbuf_reset(struct te_msgbuf *mbuf);
u32 te_msgbuf_count(struct te_msgbuf *mbuf);

#define te_msgbuf_error(b)	te_buf_error(b)
#define te_msgbuf_wq(b)		te_buf_wq(b)

/* ==== PRODUCER ==== */
u32 te_msgbuf_free_count(struct te_msgbuf *mbuf);
void te_msgbuf_set_error(struct te_msgbuf *mbuf, int err);

void te_msgbuf_raw_write(struct te_msgbuf *mbuf, const void *msg, u32 count);
void te_msgbuf_raw_get_wbuf(struct te_msgbuf *mbuf, u32 pos, void **msg);
void te_msgbuf_raw_write_skip(struct te_msgbuf *mbuf, u32 count);

int te_msgbuf_cwrite(struct te_msgbuf *mbuf, const void *msg, u32 count);

/* ==== CONSUMER ==== */
u32 te_msgbuf_avail_count(struct te_msgbuf *mbuf);
void te_msgbuf_flush(struct te_msgbuf *mbuf);

void te_msgbuf_raw_read(struct te_msgbuf *mbuf, void *msg, u32 count);
void te_msgbuf_raw_get_rbuf(struct te_msgbuf *mbuf, u32 pos, void **msg);
void te_msgbuf_raw_read_skip(struct te_msgbuf *mbuf, u32 count);

int te_msgbuf_read(struct te_msgbuf *mbuf, void *msg, u32 count);
int te_msgbuf_read_user(struct te_msgbuf *mbuf, void __user *buf, u32 count);
int te_msgbuf_read_user_timeout(struct te_msgbuf *mbuf, void __user *buf,
				u32 count, int timeout);

int te_msgbuf_wait_wevent(struct te_msgbuf *mbuf, unsigned long timeout);

/*************************************
     H/W(Physical Memory) BUFFER
 *************************************/
struct te_hwbuf {
	struct te_rb rb;
	phys_addr_t addr;
	u32 unit_size;
	struct te_cache_map cache_map;
	void *wrap_buf;
};

struct te_hwbuf_info {
	phys_addr_t addr;
	u32 size;
	u32 unit_size;
	u32 widx;
	u32 ridx;
	void *data;
};

int te_hwbuf_init(struct te_hwbuf *hbuf, phys_addr_t addr, u32 len,
		  u32 unit_size, u32 flags);

void te_hwbuf_reset(struct te_hwbuf *hbuf);

int te_hwbuf_vmap(struct te_hwbuf *hbuf, bool cached);
void te_hwbuf_vunmap(struct te_hwbuf *hbuf);

void te_hwbuf_release(struct te_hwbuf *hbuf);

bool te_hwbuf_is_invalid_paddr(struct te_hwbuf *hbuf, phys_addr_t addr);

int te_hwbuf_paddr_to_idx(struct te_hwbuf *hbuf, phys_addr_t addr, u32 *idx);
int te_hwbuf_idx_to_paddr(struct te_hwbuf *hbuf, u32 idx, phys_addr_t *addr);

int te_hwbuf_cache_sync(struct te_hwbuf *hbuf, u32 idx, u32 len,
			enum te_data_direction dir);

void te_hwbuf_set_read_callback(struct te_hwbuf *hbuf,
				te_buf_callback_func_t func, void *arg);
void te_hwbuf_set_write_callback(struct te_hwbuf *hbuf,
				 te_buf_callback_func_t func, void *arg);

void te_hwbuf_get_info(struct te_hwbuf *hbuf, struct te_hwbuf_info *info);

int te_hwbuf_get_paddr_buf2(struct te_hwbuf *hbuf,
			    phys_addr_t addr, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2);

#define te_hwbuf_data(b)	te_buf_data(b)
#define te_hwbuf_size(b)	te_buf_size(b)
#define te_hwbuf_error(b)	te_buf_error(b)
#define te_hwbuf_wq(b)		te_buf_wq(b)
#define te_hwbuf_addr(b)	((b)->addr)
#define te_hwbuf_eaddr(b)	((b)->addr + (b)->rb.size)
#define te_hwbuf_unit_size(b)	((b)->unit_size)
#define te_hwbuf_wptr(b)	((b)->addr + READ_ONCE((b)->rb.widx))
#define te_hwbuf_rptr(b)	((b)->addr + READ_ONCE((b)->rb.ridx))
#define te_hwbuf_diff_idx(b, idx1, idx2) __rb_diff_idx(&(b)->rb, idx1, idx2)

/* ==== PRODUCER ==== */
u32 te_hwbuf_free_size(struct te_hwbuf *hbuf);
void te_hwbuf_set_error(struct te_hwbuf *hbuf, int err);

int te_hwbuf_set_widx(struct te_hwbuf *hbuf, u32 widx);
int te_hwbuf_set_wptr(struct te_hwbuf *hbuf, phys_addr_t wptr);

int te_hwbuf_cwrite(struct te_hwbuf *hbuf, const void *buf, u32 len);
int te_hwbuf_cwrite2(struct te_hwbuf *hbuf, const void *buf1, u32 len1,
		     const void *buf2, u32 len2);

int te_hwbuf_cwrite_user(struct te_hwbuf *hbuf,
			 const void __user *buf, u32 len);

int te_hwbuf_write_user_timeout(struct te_hwbuf *hbuf,
				const void __user *buf, u32 len,
				unsigned long timeout);
int te_hwbuf_io_write(struct te_hwbuf *hbuf, const void __user *buf,
		      u32 len, bool non_blocking);

void te_hwbuf_raw_get_wbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2);
int te_hwbuf_get_wbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
		       void **buf1, u32 *len1, void **buf2, u32 *len2);

/* ==== CONSUMER ==== */
u32 te_hwbuf_avail_size(struct te_hwbuf *hbuf);
void te_hwbuf_flush(struct te_hwbuf *hbuf);

int te_hwbuf_wait_wevent(struct te_hwbuf *hbuf, unsigned long timeout);


int te_hwbuf_set_ridx(struct te_hwbuf *hbuf, u32 ridx);
int te_hwbuf_set_rptr(struct te_hwbuf *hbuf, phys_addr_t rptr);

void te_hwbuf_raw_peek(struct te_hwbuf *hbuf, u32 offset, void *buf, u32 len);
int te_hwbuf_peek(struct te_hwbuf *hbuf, u32 offset, void *buf, u32 len);

int te_hwbuf_read_skip(struct te_hwbuf *hbuf, u32 len);

void te_hwbuf_raw_read(struct te_hwbuf *hbuf, void *buf, u32 len);

int te_hwbuf_read(struct te_hwbuf *hbuf, void *buf, u32 len);
int te_hwbuf_read_user_idx(struct te_hwbuf *hbuf, void __user *buf, u32 idx,
			   u32 len);
int te_hwbuf_read_user_timeout(struct te_hwbuf *hbuf, void __user *buf, u32 len,
			       unsigned long timeout);
int te_hwbuf_io_read(struct te_hwbuf *hbuf, void __user *buf, u32 len,
		     bool non_blocking);

int te_hwbuf_read_condition(struct te_hwbuf *hbuf);

int te_hwbuf_raw_get_cont_rbuf(struct te_hwbuf *hbuf, u32 offset, u32 len,
			       void **buf);
int te_hwbuf_get_cont_rbuf(struct te_hwbuf *hbuf, u32 offset, u32 len,
			   void **buf);
int te_hwbuf_get_paddr_cont_rbuf(struct te_hwbuf *hbuf, phys_addr_t addr,
				 u32 offset, u32 len, void **buf);

void te_hwbuf_raw_get_rbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
			    void **buf1, u32 *len1, void **buf2, u32 *len2);
int te_hwbuf_get_rbuf2(struct te_hwbuf *hbuf, u32 offset, u32 len,
		       void **buf1, u32 *len1, void **buf2, u32 *len2);

void te_hwbuf_raw_get_split_rbuf(struct te_hwbuf *hbuf, u32 len,
				 struct te_split_buffer *buf);
int te_hwbuf_get_split_rbuf(struct te_hwbuf *hbuf, u32 len,
			    struct te_split_buffer *buf);

#endif				/* _LG1K_TE_BUFFER_H_ */

/** @} */
