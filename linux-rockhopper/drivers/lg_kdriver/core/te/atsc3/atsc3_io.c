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
 *  atsc3 device driver
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date		2016-03-09
 *  @note		Additional information.
 */
#include <lg1k/te/io.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/ipc.h>
#include "atsc3_impl.h"

#define INPUT_DUMP_TIMER_INTERVAL	20	/* msec */
#define INPUT_DUMP_WARNING_RATE		50	/* remain size warning ratio */
#define INPUT_DUMP_WARNING_INTERVAL	1000	/* msec */
#define INPUT_MONITOR_INTERVAL		500	/* msec */

#define LGC_SYNC_LEN		4
#define LGC_SYNC_BYTE		0x5A
#define LGC_SYNC_FIND_SIZE	1024

#define BB_HEADER_SIZE		4
#define MAX_BB_FRAME_SIZE	7020
#define MIN_BB_FRAME_SIZE	249

#define LGC_HEADER_LEN_A	8
#define LGC_HEADER_LEN_B	17
#define LGC_HEADER_LEN_C	9
#define META_SIZE		16

#define GET_INPUT_PORT_TYPE(p)		((p)&0xF0)

#define TRACE_ENTER(fmt,args...)	log_io("@%s(" fmt ")", __F__, ##args)
#define TRACE_EXIT(fmt,args...)		log_io("~%s(" fmt ")", __F__, ##args)

struct atsc3_packet_stats {
	enum lx_te_input_port port;

	u32 pkt_count;		/* all packets including err_pkt. */
	u32 err_pkt_count;	/* bb-frame error */
	u32 overflow_count;	/* number of full interrupt */
	u32 packet_len;
	u32 time_pkt_count;
	u64 total_length;
};

struct atsc3_bb_msg {
	u8 hdr[BB_HEADER_SIZE];
	u32 idx;
};

static DEFINE_MUTEX(io_mutex);

static const char *get_input_dump_state_str(enum atsc3_dump_state state)
{
	switch (state) {
	case INPUT_DUMP_IDLE:
		return "IDLE";
	case INPUT_DUMP_RUNNING:
		return "RUNNING";
	case INPUT_DUMP_SUSPEND:
		return "SUSPENDED";
	default:
		return "UNKNOWN";
	}
}

static u8 get_lgc_hdr_size(enum lx_atsc3_demod_type type)
{
	switch (type) {
	case LX_ATSC3_DEMOD_TYPE_A:
		return LGC_HEADER_LEN_A;
	case LX_ATSC3_DEMOD_TYPE_B:
		return LGC_HEADER_LEN_A;
	case LX_ATSC3_DEMOD_TYPE_C:
		return LGC_HEADER_LEN_B;
	case LX_ATSC3_DEMOD_TYPE_D:
		return LGC_HEADER_LEN_C;
	default:
		return LGC_HEADER_LEN_B;
	}
}

/* timer start */
static void process_input_data(struct atsc3_input_dump *dump)
{
	mod_timer(&dump->timer, jiffies + dump->timer_interval);

	if (dump->flags & ATSC3_DUMP_FLAG_WORKQUEUE) {
		queue_work(system_wq, &dump->work);
	} else {
		u32 wptr;
		int rc;

		te_reg_dumper_get_meta_wptr(dump->ch, &wptr);
		rc = te_hwbuf_set_wptr(dump->meta, wptr);
		if (rc == -EOVERFLOW) {
			te_hwbuf_set_error(dump->meta, -ENOBUFS);
		}
		te_reg_dumper_get_data_wptr(dump->ch, &wptr);
		rc = te_hwbuf_set_wptr(dump->data, wptr);
		if (rc == -EOVERFLOW) {
			te_hwbuf_set_error(dump->data, -ENOBUFS);
		}
	}
}

static void __input_dump_timer(struct atsc3_input_dump *dump)
{
	unsigned long flag;

	spin_lock_irqsave(&dump->spinlock, flag);

	if (dump->state == INPUT_DUMP_RUNNING) {
		process_input_data(dump);
	}

	spin_unlock_irqrestore(&dump->spinlock, flag);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void input_dump_timer(struct timer_list *t)
{
	struct atsc3_input_dump *dump = from_timer(dump, t, timer);
	__input_dump_timer(dump);
}
#else
static void input_dump_timer(unsigned long data)
{
	struct atsc3_input_dump *dump = (struct atsc3_input_dump *)data;
	__input_dump_timer(dump);
}
#endif

static void start_input_dump_timer(struct atsc3_input_dump *dump)
{
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
	timer_setup(&dump->timer, input_dump_timer, 0);
#else
	setup_timer(&dump->timer, input_dump_timer, (unsigned long)dump);
#endif
	dump->timer.expires = jiffies + dump->timer_interval;
	add_timer(&dump->timer);
}
/* timer end */

static void stop_input_dump_device(struct atsc3_input_dump *dump)
{
	del_timer(&dump->timer);

	te_hwbuf_set_read_callback(dump->data, NULL, NULL);
	te_hwbuf_set_read_callback(dump->meta, NULL, NULL);

	te_reg_dumper_set_intr_enable(dump->intr, false);
	te_reg_dumper_set_channel_enable(dump->ch, false);
}

static void dump_data_read_callback(void *arg, u32 idx)
{
	struct atsc3_input_dump *dump = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dump->data, idx, &ptr);
	te_reg_dumper_set_data_rptr(dump->ch, (u32)ptr);
}

static void dump_meta_read_callback(void *arg, u32 idx)
{
	struct atsc3_input_dump *dump = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dump->meta, idx, &ptr);
	te_reg_dumper_set_meta_rptr(dump->ch, (u32)ptr);
}

static int start_input_dump_device(struct atsc3_input_dump *d)
{
	u32 intr;
	u32 addr, size, unit_size, full_level;
	u8 ch = d->ch;
	int ret;

	ret = te_reg_atsc3_set_decoder_layer(ch, d->layer);
	CHECK_ERROR(ret, return ret, "set_decoder_layer(%d,%d)", ch, d->layer);

	ret = te_reg_dumper_set_channel_mode(ch, d->mode);
	CHECK_ERROR(ret, return ret, "set_channel_mode(%d,%d)", ch, d->mode);

	ret = te_reg_atsc3_set_plp_filter(ch, false, 0);
	CHECK_ERROR(ret, return ret, "set_plp_filter(%d)", ch);

	te_hwbuf_reset(d->data);
	te_hwbuf_reset(d->meta);

	/* data */
	addr = (u32)te_hwbuf_addr(d->data);
	size = te_hwbuf_size(d->data);
	if (size > (0xFFFFFFFF / 100))
		d->warn_bufsize = (size / 100) * INPUT_DUMP_WARNING_RATE;
	else
		d->warn_bufsize = (size * INPUT_DUMP_WARNING_RATE) / 100;
	d->warn_interval = INPUT_DUMP_WARNING_INTERVAL;
	d->warn_time = 0;

	unit_size = te_hwbuf_unit_size(d->data);
	if (unit_size) {
		intr = ((DUMPER_INTR_DATA_AL_FULL_CH0 << ch) |
			(DUMPER_INTR_DATA_UNIT_BUF_CH0 << ch));
		full_level = unit_size * 2;
	} else {
		intr = (DUMPER_INTR_DATA_AL_FULL_CH0 << ch);
		full_level = 64 * 1024;
	}

	te_reg_dumper_set_data_buf(ch, addr, addr + size);
	te_reg_dumper_set_data_rptr(ch, addr);
	te_reg_dumper_set_data_unitbuf_size(ch, unit_size);
	te_reg_dumper_set_data_almostfull_level(ch, full_level);

	/* meta */
	addr = (u32)te_hwbuf_addr(d->meta);
	size = te_hwbuf_size(d->meta);
	unit_size = te_hwbuf_unit_size(d->meta);
	if (unit_size) {
		intr |= ((DUMPER_INTR_META_UNIT_BUF_CH0 << ch) |
			 (DUMPER_INTR_META_AL_FULL_CH0 << ch));
		full_level = unit_size * 2;
	} else {
		full_level = META_SIZE * 16;
	}
	te_reg_dumper_set_meta_buf(ch, addr, addr + size);
	te_reg_dumper_set_meta_rptr(ch, addr);
	te_reg_dumper_set_meta_unitbuf_size(ch, unit_size);
	te_reg_dumper_set_meta_almostfull_level(ch, full_level);

	te_hwbuf_set_read_callback(d->data, dump_data_read_callback, d);
	te_hwbuf_set_read_callback(d->meta, dump_meta_read_callback, d);

	ret = te_reg_dumper_set_channel_enable(ch, true);
	CHECK_ERROR(ret != 0,, "Error in set channel enable[%d]", ret);

	te_reg_dumper_set_intr_enable(intr, true);

	start_input_dump_timer(d);

	d->intr = intr;

	return 0;
}

static struct atsc3_input_dump *start_input_dump(struct atsc3_channel *channel,
						 struct atsc3_dump_cfg *cfg)
{
	int ret;
	struct atsc3_input_dump *d;

	log_noti("%s(ch=%u,flags=0x%x,addr=0x%08x++0x%x,unit=0x%x,layer=%d)\n",
		 __func__, channel->num, cfg->flags,
		 (u32)te_hwbuf_addr(cfg->data), te_hwbuf_size(cfg->data),
		 te_hwbuf_unit_size(cfg->data), cfg->layer);

	d = &channel->dump;
	if (d->state != INPUT_DUMP_IDLE) {
		log_error("dump[%d] is running", d->ch);
		return NULL;
	}

	d->layer = cfg->layer;
	d->mode = cfg->mode;
	d->flags = cfg->flags;
	d->data = cfg->data;
	d->meta = cfg->meta;
	d->timer_interval = msecs_to_jiffies(INPUT_DUMP_TIMER_INTERVAL);

	ret = start_input_dump_device(d);
	CHECK_ERROR(ret, return NULL, "Err in start_input_dump_device");

	memset(&channel->stats, 0, sizeof(channel->stats));

	d->state = INPUT_DUMP_RUNNING;

	return d;
}

static int stop_input_dump(struct atsc3_input_dump *dump)
{
	unsigned long flag;

	log_noti("%s(ch:%d,%s)", __func__, dump->ch,
		 get_input_dump_state_str(dump->state));

	if (dump->state == INPUT_DUMP_RUNNING) {
		log_noti("dump is RUNNING");
		mutex_lock(&dump->mutex);

		log_noti("acquire spin_lock ");
		spin_lock_irqsave(&dump->spinlock, flag);
		dump->state = INPUT_DUMP_IDLE;
		spin_unlock_irqrestore(&dump->spinlock, flag);
		log_noti("restore spin_lock");

		cancel_work_sync(&dump->work);
		log_noti("cancel_work_sync done");

		stop_input_dump_device(dump);
		te_hwbuf_set_error(dump->data, -ESHUTDOWN);

		mutex_unlock(&dump->mutex);
	}
	log_noti("%s done", __func__);

	return 0;
}

static int release_atsc3_data(struct atsc3_data *data)
{
	mutex_lock(&data->mutex);
	if (data->start == false) {
		log_error("not started");
		mutex_unlock(&data->mutex);
		return -EIO;
	}

	te_msgbuf_set_error(&data->msgbuf, -ESHUTDOWN);
	te_msgbuf_release(&data->msgbuf);
	data->start = false;
	mutex_unlock(&data->mutex);

	return 0;
}

static int init_atsc3_data(struct atsc3_channel *channel, struct te_hwbuf *hbuf)
{
	struct atsc3_data *data = &channel->data;
	u32 size;
	int max_msg_count, ret;

	CHECK_ERROR(data->start, return -EIO, "already started");

	log_noti("%s(%u)", __func__, channel->num);

	size = te_hwbuf_size(hbuf);

	//The average bb size was assumed to be 1KB. (MIN:249,MAX:7020)
	max_msg_count = size / 1024;

	/* do not set TE_BUF_FLAG_NO_EVENT flag.
	   in order to be called the atsc3_wait_data
	   when set error @release_atsc3_data */
	ret = te_msgbuf_init(&data->msgbuf, sizeof(struct atsc3_bb_msg),
			     max_msg_count, 0);
	CHECK_ERROR(ret < 0, return ret, "Error in te_msgbuf_init");


	data->found_sync = false;
	data->start = true;
	data->last_read_time = 0;

	return 0;
}

unsigned int atsc3_wait_data(struct atsc3_channel *channel, struct file *file,
			     struct poll_table_struct *wait)
{
	struct te_msgbuf *msgbuf;
	unsigned int mask = 0;

	if (channel->data.start == false) {
		log_debug("dump is stopped");
		return POLLERR;
	}

	msgbuf = &channel->data.msgbuf;

	poll_wait(file, te_msgbuf_wq(msgbuf), wait);

	if (te_msgbuf_error(msgbuf)) {
		/* not set POLLERR here
		   for process error handling at atsc3_read_data. */
		mask |= (POLLIN | POLLRDNORM | POLLPRI);
	} else if (te_msgbuf_avail_count(msgbuf)) {
		mask |= (POLLIN | POLLRDNORM | POLLPRI);
	}

	return mask;
}

static int copy_bb_msg(struct atsc3_bb_msg *bbf, struct te_hwbuf *hbuf,
		       char __user *buf, size_t user_size)
{
	u32 bb_size = TE_GET16(&bbf->hdr[2]);
	int ret;

	if (BB_HEADER_SIZE + bb_size > user_size)
		return 0;

	ret = copy_to_user(buf, bbf->hdr, BB_HEADER_SIZE);
	if (ret) {
		log_error("copy_to_user failed");
		return -EFAULT;
	}
	buf += BB_HEADER_SIZE;

	ret = te_hwbuf_read_user_idx(hbuf, buf, bbf->idx, bb_size);
	if (ret < 0) {
		log_error("te_hwbuf_read_user failed(%d)", ret);
		return -EFAULT;
	}

	return BB_HEADER_SIZE + ret;
}

ssize_t atsc3_read_data(struct atsc3_channel *channel, char __user *buf,
			size_t size)
{
	struct atsc3_data *atsc3_data = &channel->data;
	struct atsc3_input_dump *dump = &channel->dump;

	struct te_msgbuf *msgbuf = &atsc3_data->msgbuf;
	struct atsc3_bb_msg *bbf;
	int ret, i, n, r_size;

	mutex_lock(&atsc3_data->mutex);
	if (!atsc3_data->start) {
		ret = -EIO;
		goto exit;
	}

	if (te_hwbuf_error(dump->data)) {
		u32 v = DUMPER_INTR_DATA_AL_FULL_CH0;
		log_error("ch%u overflow detected. flush now", channel->num);

		te_hwbuf_flush(dump->data);
		te_ringbuf_flush(&dump->rbuf);
		te_msgbuf_flush(msgbuf);

		te_reg_dumper_clear_intr(v << channel->num);
		te_reg_dumper_set_intr_enable((v << channel->num), true);
		ret = -EIO;
		goto exit;
	}

	r_size = 0;
	n = te_msgbuf_avail_count(msgbuf);
	for (i = 0; i < n; i++) {
		te_msgbuf_raw_get_rbuf(msgbuf, 0, (void **)&bbf);
		ret = copy_bb_msg(bbf, dump->data, buf, size - r_size);
		if (ret == 0) {
			break;
		} else if (ret < 0) {
			goto exit;
		}
		te_msgbuf_raw_read_skip(msgbuf, 1);
		buf += ret;
		r_size += ret;
	}
	atsc3_data->last_read_time = te_get_us_tick();

	ret = r_size;
exit:
	mutex_unlock(&atsc3_data->mutex);
	return ret;
}

struct atsc3_input_dump *atsc3_start_input_dump(struct atsc3_channel *channel,
						struct atsc3_dump_cfg *cfg)
{
	struct te_ringbuf *rbuf = &channel->dump.rbuf;
	struct atsc3_input_dump *dump;
	void *data, *buf;
	u32 size;
	int ret;

	log_noti("%s(%u)", __func__, channel->num);

	buf = kmalloc(LGC_SYNC_FIND_SIZE, GFP_KERNEL);
	if (!buf) {
		log_error("no memory");
		return NULL;
	}
	data = te_hwbuf_data(cfg->data);
	size = te_hwbuf_size(cfg->data);

	mutex_lock(&io_mutex);
	te_ringbuf_init(rbuf, data, size, 0);

	ret = init_atsc3_data(channel, cfg->data);
	if (ret)
		goto err_init;

	dump = start_input_dump(channel, cfg);
	if (!dump)
		goto err_start;

	dump->lgc_buf = buf;
	dump->lgc_buf_size = LGC_SYNC_FIND_SIZE;

	mutex_unlock(&io_mutex);

	return dump;

err_start:
	release_atsc3_data(&channel->data);
err_init:
	kfree(buf);
	mutex_unlock(&io_mutex);

	return NULL;

}

int atsc3_stop_input_dump(struct atsc3_input_dump *dump)
{
	struct atsc3_channel *channel;
	int rc;

	channel = container_of(dump, struct atsc3_channel, dump);

	mutex_lock(&io_mutex);
	rc = stop_input_dump(dump);

	release_atsc3_data(&channel->data);
	kfree(dump->lgc_buf);
	mutex_unlock(&io_mutex);

	return rc;
}

static int suspend_input_dump(struct atsc3_input_dump *dump)
{
	unsigned long flag;

	if (dump->state == INPUT_DUMP_RUNNING) {
		mutex_lock(&dump->mutex);
		spin_lock_irqsave(&dump->spinlock, flag);
		dump->state = INPUT_DUMP_SUSPEND;
		spin_unlock_irqrestore(&dump->spinlock, flag);

		stop_input_dump_device(dump);
		mutex_unlock(&dump->mutex);

		log_noti("Suspend [%d] dump dev", dump->ch);
	}

	return 0;
}

static int resume_input_dump(struct atsc3_input_dump *dump)
{
	struct atsc3_channel *channel;
	int ret = 0;

	if (dump->state == INPUT_DUMP_SUSPEND) {
		log_noti("%s(ch=%d,flags=0x%x,size=0x%x,unit_size=0x%x)\n",
			 __func__, dump->ch, dump->flags,
			 te_hwbuf_size(dump->data),
			 te_hwbuf_unit_size(dump->data));

		mutex_lock(&dump->mutex);

		channel = container_of(dump, struct atsc3_channel, dump);
		if (channel->data.start) {
			te_ringbuf_reset(&dump->rbuf);
			te_msgbuf_reset(&channel->data.msgbuf);
		}

		/* Use saved dev information */
		ret = start_input_dump_device(dump);
		if (ret) {
			log_error("Error in start_input_dump_device(resume)\n");
			stop_input_dump_device(dump);
			dump->state = INPUT_DUMP_IDLE;
		} else {
			dump->state = INPUT_DUMP_RUNNING;
		}

		mutex_unlock(&dump->mutex);
	}

	return ret;
}

static int find_syncbyte(u8 *buf, int size, int hdr_size)
{
	int i, pos, skipped;
	bool found;

	pos = 0;
	skipped = 0;

	while (size - pos >= hdr_size) {
		found = true;
		for (i = 0; i < LGC_SYNC_LEN; i++) {
			pos = skipped + LGC_SYNC_LEN - i - 1;
			if (buf[pos] != LGC_SYNC_BYTE) {
				found = false;
				pos += 1;
				skipped = pos;
				break;
			}
		}
		if (found) {
			return skipped;
		}
	}

	return -1;
}

static u32 get_lgc_pkt_size(struct atsc3_channel *channel, u8 *lgc, u32 *frame)
{
	u32 f, padding;
	u8 lgc_hdr_size = channel->lgc_hdr_size;

	f = TE_GET16(&lgc[5]);

	padding = (lgc_hdr_size + f) % 188;
	if (padding)
		padding = 188 - padding;

	*frame = f;
	return lgc_hdr_size + f + padding;
}

static int add_bb_msg(struct atsc3_channel *channel, u8 *buf)
{
	struct atsc3_bb_msg *bbf;
	struct te_msgbuf *msgbuf;
	int hdr_size;
	u32 idx;

	msgbuf = &channel->data.msgbuf;
	if (!te_msgbuf_free_count(msgbuf)) {
		log_error("no available msgbuf");
		return -ENOMEM;
	}

	hdr_size = channel->lgc_hdr_size;
	/* ringbuf ridx is at the syncbyte */
	te_ringbuf_get_ridx(&channel->dump.rbuf, hdr_size, &idx);
	te_msgbuf_raw_get_wbuf(msgbuf, 0, (void **)&bbf);

	bbf->hdr[0] = buf[4] & 0x3f; // PLP ID
	bbf->hdr[1] = buf[7]; // CC
	bbf->hdr[2] = buf[5]; // LEN[0:1]
	bbf->hdr[3] = buf[6];
	bbf->idx = idx;

	te_msgbuf_raw_write_skip(msgbuf, 1);
	return 0;
}

static void process_lgc_stream(struct atsc3_channel *channel)
{
	struct atsc3_input_dump *d = &channel->dump;
	struct atsc3_stats *stats = &channel->stats;
	struct te_ringbuf *rbuf;
	u8 *buf;
	u32 avail_size, buf_size, pkt_size, frame_size;
	u8 hdr_size;
	int ret, herror;

	hdr_size = channel->lgc_hdr_size;
	rbuf = &d->rbuf;
	avail_size = te_ringbuf_avail_size(rbuf);

	while (avail_size > MAX_BB_FRAME_SIZE) {
		if (d->state != INPUT_DUMP_RUNNING)
			return;

		herror = te_hwbuf_error(d->data);
		if (herror) {
			/* for wake up poll_wait */
			te_msgbuf_set_error(&channel->data.msgbuf, -EIO);
			break;
		}

		buf = d->lgc_buf;
		if (channel->data.found_sync == true)
			buf_size = hdr_size * 2;
		else
			buf_size = d->lgc_buf_size;

		te_ringbuf_raw_peek(rbuf, 0, buf, buf_size);
		ret = find_syncbyte(buf, buf_size, hdr_size);
		if (ret < 0) {
			log_noti("(ch:%u)can't find syncbyte", channel->num);
			channel->data.found_sync = false;
			pkt_size = buf_size - hdr_size + LGC_SYNC_LEN;
			goto next;
		} else if (ret > 0) {
			if (channel->data.found_sync)
				log_noti("(ch:%u)skip %dbytes to find sync",
					 channel->num, ret);
			te_ringbuf_read_skip(rbuf, ret);
			avail_size -= ret;
			buf = &buf[ret];
			buf_size -= ret;
		}
		channel->data.found_sync = true;

		pkt_size = get_lgc_pkt_size(channel, buf, &frame_size);
		if (avail_size < pkt_size) {
			log_debug("(ch:%u)need more data. avail:0x%x,pkt:0x%x",
				  channel->num, avail_size, pkt_size);
			break;
		}

		if ((buf[4] & 0xC0) == 0xC0) {
			log_debug("(ch:%u)skip ERROR packet", channel->num);
			stats->err_pkt_count++;
			goto next;
		}

		if (channel->skip_timepkt && (buf[8] & 0x80) == 0x80) {
			log_debug("(ch:%u)skip TIME packet", channel->num);
			stats->time_pkt_count++;
			goto next;
		}

		if (frame_size < MIN_BB_FRAME_SIZE ||
		    frame_size > MAX_BB_FRAME_SIZE) {
			log_warning("(ch:%u)invalid bb size(%d).%d<=size<=%d",
				    channel->num, frame_size,
				    MIN_BB_FRAME_SIZE, MAX_BB_FRAME_SIZE);
			channel->stats.err_pkt_count++;
		}

		ret = add_bb_msg(channel, buf);
		if (ret) {
			//todo consider behavior.
			//te_msgbuf_flush? break? or don't check and write msg?
		}
next:
		if (channel->data.found_sync != false) {
			stats->pkt_count++;
			stats->total_pkt_len += pkt_size;
		}
		te_ringbuf_read_skip(rbuf, pkt_size);
		avail_size -= pkt_size;
	}
}

static void data_callback_work(struct work_struct *work)
{
	int rc;
	struct atsc3_input_dump *dump;
	struct atsc3_channel *channel;
	u32 free_size, size, ptr, idx;

	channel = container_of(work, struct atsc3_channel, dump.work);
	dump = &channel->dump;
	if (dump->state != INPUT_DUMP_RUNNING)
		return;

	free_size = te_hwbuf_free_size(dump->data);
	if (free_size < dump->warn_bufsize) {
		u32 elapsed = jiffies_to_msecs(jiffies - dump->warn_time);

		if (elapsed >= dump->warn_interval) {
			u64 time = channel->data.last_read_time;
			u32 nsec = do_div(time, USEC_PER_SEC);

			size = te_hwbuf_size(dump->data);
			log_warning("(ch:%u)almost full(0x%x(%d%%))-%llu.%06u",
				    channel->num, free_size,
				    (free_size * 100) / size, time, nsec);

			dump->warn_time = jiffies;
		}
	}

	te_reg_dumper_get_data_wptr(dump->ch, &ptr);
	rc = te_hwbuf_set_wptr(dump->data, ptr);
	if (rc == -EOVERFLOW) {
		te_hwbuf_set_error(dump->data, -ENOBUFS);
		te_ringbuf_set_error(&dump->rbuf, -ENOBUFS);
	}
	rc = te_hwbuf_paddr_to_idx(dump->data, ptr, &idx);
	if (rc)
		te_hwbuf_set_error(dump->data, -EINVAL);

	rc = te_ringbuf_set_widx(&dump->rbuf, idx);
	if (rc == -EOVERFLOW)
		te_ringbuf_set_error(&dump->rbuf, -ENOBUFS);

	process_lgc_stream(channel);
}

static void irq_handler(struct atsc3_device *dev, u8 i, u32 val)
{
	struct atsc3_channel *channel;
	struct atsc3_input_dump *dump;
	u32 v;

#define CHANNEL_INTR_BITS(i)	\
	((DUMPER_INTR_META_WRITE_CH0<<(i)) |	\
	 (DUMPER_INTR_META_UNIT_BUF_CH0<<(i)) |	\
	 (DUMPER_INTR_META_AL_FULL_CH0<<(i)) |	\
	 (DUMPER_INTR_DATA_UNIT_BUF_CH0<<(i)) |	\
	 (DUMPER_INTR_DATA_AL_FULL_CH0<<(i)))

	if (!(val & CHANNEL_INTR_BITS(i)))
		return;

	channel = atsc3_get_channel(dev, i);
	if (!channel)
		return;

#ifdef DEBUG_ISR_LOG
	/* META */
	if (val & (DUMPER_INTR_META_WRITE_CH0 << i)) {
		log_noti("CH[%d] META IRQ\n", i);
	}

	/* META UNIT BUFFER */
	if (val & (DUMPER_INTR_META_UNIT_BUF_CH0 << i)) {
		log_noti("CH[%d] META UNIT BUFFER IRQ\n", i);
	}

	/* DATA UNIT BUFFER */
	if (val & (DUMPER_INTR_DATA_UNIT_BUF_CH0 << i)) {
		log_noti("CH[%d] DATA UNIT BUFFER IRQ\n", i);
	}
#endif
	v = DUMPER_INTR_META_AL_FULL_CH0;
	/* META ALMOST FULL */
	if (val & (v << i)) {
		te_reg_dumper_set_intr_enable((v << i), false);
		log_noti("CH[%d] META ALMOST FULL IRQ\n", i);
	}

	v = DUMPER_INTR_DATA_AL_FULL_CH0;
	/* DATA ALMOST FULL */
	if (val & (v << i)) {
		u64 time = channel->data.last_read_time;
		u32 nsec = do_div(time, USEC_PER_SEC);

		te_reg_dumper_set_intr_enable((v << i), false);

		log_noti("CH[%d] DATA ALMOST FULL IRQ(%llu.%06usec)\n",
			 i, time, nsec);
	}

	dump = &channel->dump;

	spin_lock(&dump->spinlock);

	if (dump->state == INPUT_DUMP_RUNNING) {
		if (val & (DUMPER_INTR_META_AL_FULL_CH0 << i)) {
			te_hwbuf_set_error(dump->meta, -ENOBUFS);
		}

		if (val & (DUMPER_INTR_DATA_AL_FULL_CH0 << i)) {
			te_hwbuf_set_error(dump->data, -ENOBUFS);
			channel->stats.overflow_count++;

			if (dump->flags & ATSC3_DUMP_FLAG_WORKQUEUE)
				te_ringbuf_set_error(&dump->rbuf, -ENOBUFS);
		}
		process_input_data(dump);
	}

	spin_unlock(&dump->spinlock);
}

int atsc3_io_irq_handler(struct atsc3_device *dev, u32 val)
{
	int i;

	for (i = 0; i < 4; i++) {
		irq_handler(dev, i, val);
	}

	return 0;
}

static void reset_input_monitor(struct atsc3_input_monitor *m)
{
	enum te_reg_tpi_port tpi;

	if (m->input != LX_TE_INPUT_PORT_NONE && m->channel_enable)
		m->enable = true;
	else
		m->enable = false;

	if (m->enable) {
		m->pkt_count = 0;
		m->err_pkt_count = 0;
		m->ready = false;
		tpi = te_input_port_to_reg_tpi_port(m->input);
		snprintf(m->name, sizeof(m->name), "[CH_%d] %s/%s", m->ch,
			 te_input_port_to_str(m->input),
			 te_reg_tpi_port_to_str(tpi));
	}
}

static void update_input_monitor(struct atsc3_channel *channel)
{
	struct atsc3_input_monitor *m = &channel->monitor;

	mutex_lock(&m->mutex);
	m->input = channel->input_port;
	reset_input_monitor(m);
	mutex_unlock(&m->mutex);
}

int atsc3_io_set_channel_enable(struct atsc3_channel *channel, bool enable)
{
	struct atsc3_input_monitor *m = &channel->monitor;

	mutex_lock(&m->mutex);
	m->channel_enable = enable;
	reset_input_monitor(m);
	mutex_unlock(&m->mutex);

	return 0;
}

static int set_demod_type(u8 ch, LX_ATSC3_DEMOD_TYPE_T type)
{
	int ret;
	enum te_reg_atsc3_demod_type v;

	switch (type) {
	case LX_ATSC3_DEMOD_TYPE_A:
	case LX_ATSC3_DEMOD_TYPE_B:
		v = ATSC3_DEMOD_TYPE_A;
		break;
	case LX_ATSC3_DEMOD_TYPE_C:
		v = ATSC3_DEMOD_TYPE_B;
		break;
	case LX_ATSC3_DEMOD_TYPE_D:
		v = ATSC3_DEMOD_TYPE_C;
		break;
	default:
		log_error("not supported demod type(%d)\n", type);
		return -EINVAL;
	}
	/*
	   TODO: when enable chanenl, send demod_type value to mcu.
	   mcu will set 'lgd_sel' to register.
	 */
	ret = te_reg_atsc3_set_demod_type(ch, v);

	return ret;
}

int atsc3_set_demod_type(struct atsc3_channel *channel,
			 enum lx_atsc3_demod_type type)
{
	int i, ret = 0;
	int num_channel = channel->dev->num_channel;

	mutex_lock(&io_mutex);
	for (i = 0; i < num_channel; i++) {
		if (channel->demod_type == type)
			continue;

		ret = set_demod_type(channel->num, type);
		CHECK_ERROR(ret, goto exit, "error in set_demod_type(%d)", i);

		channel->demod_type = type;
		channel->lgc_hdr_size = get_lgc_hdr_size(type);
		channel->skip_timepkt = (type == LX_ATSC3_DEMOD_TYPE_D ?
					 true : false);
	}
exit:
	mutex_unlock(&io_mutex);

	return ret;
}

static int ioc_set_demod_type(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_DEMOD_TYPE_T type = *(LX_ATSC3_DEMOD_TYPE_T *)arg;
	struct atsc3_device *dev = fh->dev;
	int ret, i;

	log_noti("Set Demod Type : %d\n", type);

	for (i = 0; i < dev->num_channel; i++) {
		struct atsc3_channel *channel = &dev->channels[i];

		if (channel->demod_type == type)
			continue;

		ret = set_demod_type(i, type);
		CHECK_ERROR(ret, return ret, "Error in set_demod_type(%d)", i);

		channel->demod_type = type;
	}

	return 0;
}

static int check_dump_paddr_range(u32 paddr, u32 size)
{
	struct te_mem_ctx *ctx;
	int rc;

	// search te_shared memory
	ctx = te_mem_open(TE_MEM_SHARED_NAME);
	if (!ctx) // possible?
		return -EFAULT;

	rc = te_mem_check_paddr_range(ctx, paddr, size);

	te_mem_close(ctx);
	return rc;
}

static int ioc_start_input_dump(struct atsc3_fh *fh, void *arg)
{
	int ret;
	struct atsc3_channel *channel = fh->channel;
	LX_ATSC3_DUMP_CFG_T *param = arg;
	struct atsc3_dump_fh *df;
	struct atsc3_dump_cfg cfg;

	CHECK_PARAM(fh->dump, "already started");

	ret = check_dump_paddr_range(param->data.addr, param->data.size);
	if (ret)
		return ret;

	ret = check_dump_paddr_range(param->meta.addr, param->meta.size);
	if (ret)
		return ret;

	df = kmalloc(sizeof(*df), GFP_KERNEL);
	CHECK_ERROR(!df, return -ENOMEM, "no mem");

	te_hwbuf_init(&df->data, param->data.addr, param->data.size,
		      param->data.unit_size, 0);
	te_hwbuf_init(&df->meta, param->meta.addr, param->meta.size,
		      param->meta.unit_size, 0);

	// TODO: param->port ???

	switch (param->layer) {
	case LX_ATSC3_DECODER_LAYER_BB:
		cfg.layer = ATSC3_DECODER_LAYER_BB;
		cfg.mode = DUMPER_MODE_LGC;
		break;
	case LX_ATSC3_DECODER_LAYER_BB_PLP:
		cfg.layer = ATSC3_DECODER_LAYER_BB_PLP;
		cfg.mode = DUMPER_MODE_LGC;
		break;
	case LX_ATSC3_DECODER_LAYER_TIME_LGC:
		cfg.layer = ATSC3_DECODER_LAYER_TIME_LGC;
		cfg.mode = DUMPER_MODE_PVR;
		break;
	case LX_ATSC3_DECODER_LAYER_LGC:
		cfg.layer = ATSC3_DECODER_LAYER_BYPASS;
		cfg.mode = DUMPER_MODE_RAW;
		break;
	default:
		log_error("invalid layer(%d)\n", param->layer);
		ret = -EINVAL;
		goto error;
	}

	cfg.data = &df->data;
	cfg.meta = &df->meta;
	cfg.flags = 0;

	if (fh->fixup_channel) {
		/* O20 A0 bug fix:
		 * LGC time latch module runs only if wmif mode is LGC,
		 * but input stream dump starts with RAW mode.
		 * To fixup this, we set wmif mode as LGC and use another
		 * channel for input stream dump.
		 */

		ret = te_reg_atsc3_set_decoder_layer(fh->channel->num,
						     ATSC3_DECODER_LAYER_LGC);
		CHECK_ERROR(ret, goto error, "set_decoder_layer(%u, LGC)",
			    fh->channel->num);

		ret = te_reg_dumper_set_channel_mode(fh->channel->num,
						     DUMPER_MODE_LGC);
		if (ret) {
			log_error("Err in te_reg_dumper_set_channel_mode(%u)",
				  fh->channel->num);
			goto error;
		}
		channel = fh->fixup_channel;
	} else {
		channel = fh->channel;
	}
	df->dump = start_input_dump(channel, &cfg);
	if (!df->dump) {
		log_error("Error in start_input_dump\n");
		ret = -EIO;
		goto error;
	}
	fh->dump = df;

	return 0;

error:
	kfree(df);

	return ret;
}

static int ioc_stop_input_dump(struct atsc3_fh *fh, void *arg)
{
	int ret;
	struct atsc3_dump_fh *df = fh->dump;

	CHECK_ERROR(!df, return -EINVAL, "not started");

	ret = stop_input_dump(df->dump);
	kfree(df);
	fh->dump = NULL;

	return ret;
}

static int ioc_get_input_dump_info(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_DUMP_INFO_T *param = arg;
	LX_ATSC3_DUMP_BUF_PTR_T *wptr = param->wptr;
	struct atsc3_dump_fh *df = fh->dump;
	struct atsc3_input_dump *dump;
	unsigned long timeout;
	int ret;

	/* CAUTION: this function has no lock in ioctl
	 * so need io_mutex to get input_dump
	 */
	mutex_lock(&io_mutex);
	if (df)
		dump = df->dump;
	else
		dump = NULL;
	mutex_unlock(&io_mutex);

	CHECK_ERROR(!dump, return -EINVAL, "not started");

	mutex_lock(&dump->mutex);

	if (dump->state != INPUT_DUMP_RUNNING) {
		log_error("state is not running ch[%d]", dump->ch);
		ret = -EFAULT;
		goto error;
	}

	if (param->timeout == LX_ATSC3_INFINITE_WAIT)
		timeout = TE_BUF_INFINITE_TIMEOUT;
	else
		timeout = param->timeout;

	ret = te_hwbuf_wait_wevent(dump->data, timeout);
	if (ret < 0 && ret != -ETIME) {
		if (ret == -EIO) {
			log_error("CH[%d] BUFFER OVERFLOW\n", dump->ch);
			te_hwbuf_flush(dump->data);	/* remove error condition */
		} else if (ret != -ERESTARTSYS) {
			log_error("Error[%d] in te_hwbuf_wait_wevent", ret);
		}
		goto error;
	}
	wptr->data = (u32)te_hwbuf_wptr(dump->data);

	/* if no unit_buf_size than read from h/w */
	te_reg_dumper_get_meta_wptr(dump->ch, &wptr->meta);

	mutex_unlock(&dump->mutex);

	return 0;

error:
	mutex_unlock(&dump->mutex);

	return ret;
}

static int ioc_set_input_dump_rptr(struct atsc3_fh *fh, void *arg)
{
	int ret;
	LX_ATSC3_DUMP_BUF_PTR_T *param = arg;
	struct atsc3_dump_fh *df = fh->dump;
	struct atsc3_input_dump *dump;

	CHECK_ERROR(!df, return -EINVAL, "not started");

	dump = df->dump;
	mutex_lock(&dump->mutex);
	if (dump->state != INPUT_DUMP_RUNNING) {
		log_error("state is not running ch[%d]", dump->ch);
		ret = -EFAULT;
		goto error;
	}

	if (param->data) {
		ret = te_hwbuf_set_rptr(dump->data, param->data);
		CHECK_ERROR(ret < 0, goto error,
			    "Error in te_hwbuf_set_rptr(0x%08x)", param->data);
	}

	if (param->meta) {
		ret = te_hwbuf_set_rptr(dump->meta, param->meta);
		CHECK_ERROR(ret < 0, goto error,
			    "Error in te_hwbuf_set_rptr(0x%08x)", param->meta);
	}
	mutex_unlock(&dump->mutex);

	return 0;

error:
	mutex_unlock(&dump->mutex);

	return ret;
}

static int config_channel_input(struct atsc3_channel *channel,
				LX_ATSC3_CHANNEL_INPUT_CFG_T *cfg)
{
	int ret;
	enum te_reg_channel_src src;

	log_noti("ch %u, port: %s -> %s, enable: %d, reset: %d\n",
		 channel->num, te_input_port_to_str(channel->input_port),
		 te_input_port_to_str(cfg->port), cfg->enable, cfg->reset);

	src = te_input_port_to_reg_ch_src(cfg->port);
	if (src == CH_SRC_INVALID) {
		log_error("Invalid input port:[%d]", cfg->port);
		return -EINVAL;
	}

	log_noti("atsc3_src: %s", te_ch_src_type_to_str(src));

	if (cfg->enable) {
		if (cfg->reset || channel->input_port != cfg->port) {
			/* reset input port if input source is changed */

			TE_REG_SetEngineChannelSource(channel->num,
						      CH_SRC_DISABLE);

			// add input dump reset - refer to arib2
			// add wmif reset if enabled

			/*
			   TODO: sync with mcu when input port is changed. consider sw, hw delivery
			 */
		}

		ret = TE_REG_SetEngineChannelSource(channel->num, src);
		CHECK_ERROR(ret, return ret,
			    "Err in TE_REG_SetEngineChannelSource");

		channel->input_port = cfg->port;
	} else {
		/* disable input port */
		TE_REG_SetEngineChannelSource(channel->num, CH_SRC_DISABLE);

		channel->input_port = LX_TE_INPUT_PORT_NONE;
	}
	update_input_monitor(channel);

	return 0;
}

int atsc3_config_channel_input(struct atsc3_channel *channel,
			       LX_ATSC3_CHANNEL_INPUT_CFG_T *cfg)
{
	int ret;

	mutex_lock(&io_mutex);
	ret = config_channel_input(channel, cfg);
	mutex_unlock(&io_mutex);

	return ret;
}

static int ioc_config_channel_input(struct atsc3_fh *fh, void *arg)
{
	int ret;
	LX_ATSC3_CHANNEL_INPUT_CFG_T *cfg = arg;

	ret = config_channel_input(fh->channel, cfg);
	if (!ret && fh->fixup_channel) {
		ret = config_channel_input(fh->fixup_channel, cfg);
	}

	return ret;
}

static int get_packet_stats(struct atsc3_channel *channel,
			    struct atsc3_packet_stats *status)
{
	int ret;
	LX_TE_INPUT_PORT_T port;
	IPC_ATSC3_CH_STATUS_T ipc_s;
	enum te_reg_channel_src src;

	ret = TE_REG_GetEngineChannelSource(channel->num, &src);
	CHECK_ERROR(ret, return ret, "Err in TE_REG_GetEngineChannelSource");

	port = te_reg_ch_src_to_input_port(src);
	if (port != channel->input_port) {
		log_warning
		    ("ch[%u] different input_port: reg[%d][%s] ctrl[%s]\n",
		     channel->num, src, te_input_port_to_str(port),
		     te_input_port_to_str(channel->input_port));
	}

	status->port = port;

	if (channel->data.start) {
		status->pkt_count = channel->stats.pkt_count;
		status->err_pkt_count = channel->stats.err_pkt_count;
		status->packet_len = 1;
		status->total_length = channel->stats.total_pkt_len;
	} else {
		TE_IPC_GetATSC3ChannelStatus(channel->num, &ipc_s);

		status->pkt_count = ipc_s.packet_cnt;
		status->err_pkt_count = ipc_s.err_packet_cnt;
		status->packet_len = ipc_s.packet_len;
		status->total_length = status->pkt_count * status->packet_len;
	}

	return 0;
}

static int ioc_get_channel_input_status(struct atsc3_fh *fh, void *arg)
{
	int ret;
	LX_ATSC3_CHANNEL_STATUS_T *param = arg;
	struct atsc3_packet_stats s;

	memset(&s, 0, sizeof(s));
	ret = get_packet_stats(fh->channel, &s);

	param->port = s.port;
	param->enable = s.port == LX_TE_INPUT_PORT_NONE ? false : true;
	param->packet_cnt = s.pkt_count;
	param->err_packet_cnt = s.err_pkt_count;
	param->packet_len = s.packet_len;
	param->time = (u32)te_get_ms_tick();

	return ret;
}

static int dump_start(struct te_dump_device *dev, struct te_dump_handle *h,
		      struct te_dump_cfg *cfg)
{
	int ret;
	struct atsc3_input_dump *dump;
	enum te_dumper_mode dumper;
	struct atsc3_dump_cfg param;
	struct atsc3_device *adev = dev->private;
	struct atsc3_channel *channel = atsc3_get_channel(adev, cfg->ch);

	CHECK_PARAM(!channel, "invalid channel[%d]", cfg->ch);

	dumper = te_dumper_get_mode(get_te_device(adev));
	if (dumper != TE_DUMPER_MODE_ATSC3) {
		log_error("not atsc3 dumper mode\n");
		return -EPERM;
	}

	mutex_lock(&io_mutex);

	if (cfg->port != LX_TE_INPUT_PORT_BYPASS) {
		LX_ATSC3_CHANNEL_INPUT_CFG_T input_cfg;

		input_cfg.port = cfg->port;
		if (cfg->port == LX_TE_INPUT_PORT_NONE) {
			input_cfg.enable = false;
			input_cfg.reset = false;
		} else {
			input_cfg.enable = true;
			input_cfg.reset = true;
		}

		ret = config_channel_input(channel, &input_cfg);
		CHECK_ERROR(ret, goto exit,
			    "Error in config_channel_input(%d)", cfg->ch);
	}

	param.layer = cfg->atsc3.layer;
	param.mode = cfg->atsc3.mode;
	param.data = cfg->data;
	param.meta = cfg->meta;
	param.flags = cfg->flags;

	dump = start_input_dump(channel, &param);
	if (!dump) {
		ret = -EIO;
		goto exit;
	}

	h->dev_handle = dump;
	ret = 0;

exit:
	mutex_unlock(&io_mutex);

	return ret;
}

static void dump_stop(struct te_dump_device *dev, struct te_dump_handle *h)
{
	if (h->dev_handle) {
		mutex_lock(&io_mutex);
		stop_input_dump(h->dev_handle);
		mutex_unlock(&io_mutex);
		h->dev_handle = NULL;
	}
}

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_ATSC3,
	.start = dump_start,
	.stop = dump_stop,
};

static int init_input_dump(struct atsc3_device *dev)
{
	int ret, i;
	struct atsc3_channel *channel;
	struct atsc3_input_dump *dump;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		dump = &channel->dump;

		dump->ch = channel->num;
		dump->state = INPUT_DUMP_IDLE;
		spin_lock_init(&dump->spinlock);
		mutex_init(&dump->mutex);
		INIT_WORK(&dump->work, data_callback_work);
	}

	dump_device.private = dev;
	ret = te_dump_register_device(&dump_device);
	CHECK_ERROR(ret, return ret, "Error in te_dump_register_device");

	return 0;
}

static void detect_input_change(struct atsc3_input_monitor *m,
				struct atsc3_packet_stats *stats)
{
#define MAX_MESSAGE_COUNT	10
#define log_monitor(fmt, args...) log_noti("%s - " fmt, m->name, ##args)

	if (m->pkt_count == stats->pkt_count) {
		if (!m->no_input) {
			log_monitor("NO INPUT PACKET");
			m->no_input = true;
		}
		return;
	}

	if (m->no_input) {
		log_monitor("recover input packet");
		m->no_input = false;
	}

	if (m->overflow_count != stats->overflow_count ||
	    m->err_pkt_count != stats->err_pkt_count) {

		if (m->message_count == MAX_MESSAGE_COUNT)	// disabled
			return;

		log_monitor("pkt:%u(%u/%u) err:%u(%u/%u) ovf:%u(%u/%u)",
			    stats->pkt_count - m->pkt_count,
			    m->pkt_count, stats->pkt_count,
			    stats->err_pkt_count - m->err_pkt_count,
			    m->err_pkt_count, stats->err_pkt_count,
			    stats->overflow_count - m->overflow_count,
			    m->overflow_count, stats->overflow_count);

		m->message_count++;
		if (m->message_count == MAX_MESSAGE_COUNT) {
			log_monitor("disable packet monitor message");
		}
	} else {
		if (m->message_count == 0)
			return;

		if (m->message_count == MAX_MESSAGE_COUNT) {
			log_monitor("re-enable packet monitor message");
			m->message_count = 0;
		} else {
			m->message_count--;
		}
	}
}

static void check_channel_input_status(struct atsc3_input_monitor *m,
				       struct atsc3_packet_stats *stats)
{
	if (m->ready) {
		detect_input_change(m, stats);
	} else {
		/* change ready status after getting status */
		m->ready = true;
		m->no_input = false;
		m->message_count = 0;
	}
	m->pkt_count = stats->pkt_count;
	m->err_pkt_count= stats->err_pkt_count;
	m->overflow_count = stats->overflow_count;
}

static void input_monitor_timer(void *arg)
{
	int i;
	struct atsc3_device *dev = arg;
	struct atsc3_packet_stats stats;
	IPC_ATSC3_CH_STATUS_T ipc_status;
	struct atsc3_input_monitor *m;
	struct atsc3_stats *s;

	for (i = 0; i < dev->num_channel; i++) {
		m = &dev->channels[i].monitor;

		mutex_lock(&m->mutex);
		if (m->enable) {
			s = &dev->channels[i].stats;
			if (dev->channels[i].data.start) {
				stats.pkt_count = s->pkt_count;
				stats.err_pkt_count = s->err_pkt_count;
				stats.overflow_count = s->overflow_count;
				stats.time_pkt_count = s->time_pkt_count;
			} else {
				TE_IPC_GetATSC3ChannelStatus(i, &ipc_status);

				stats.pkt_count = ipc_status.packet_cnt;
				stats.err_pkt_count = ipc_status.err_packet_cnt;
				stats.overflow_count = s->overflow_count;
				stats.time_pkt_count = 0;
			}
			check_channel_input_status(m, &stats);
		}
		mutex_unlock(&m->mutex);
	}
}

static int init_input_monitor(struct atsc3_device *dev)
{
	int i;
	struct atsc3_input_monitor *m;
	struct te_timer *timer;
	struct te_device *tdev = get_te_device(dev);

	for (i = 0; i < dev->num_channel; i++) {
		m = &dev->channels[i].monitor;
		m->ch = i;
		mutex_init(&m->mutex);
	}

	timer = te_add_timer(tdev, INPUT_MONITOR_INTERVAL, input_monitor_timer,
			     dev);
	CHECK_ERROR(!timer, return -EIO, "Error in te_add_timer");

	dev->monitor_timer = timer;

	return 0;
}

/* debug functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("    " fmt, ##args)

enum {
	DEBUG_ID_DEMOD_TYPE = 0,
	DEBUG_ID_INPUT_DUMP,
	DEBUG_ID_CHANNEL_INPUT,
	DEBUG_ID_MAX,
};

static u32 input_mtime = 500;	/* ms unit */

static int debug_show_input_status(struct atsc3_device *dev, struct seq_file *m)
{
	struct lx_te_tpi_status *tpi_status;
	struct atsc3_packet_stats *ch_status;

	struct atsc3_channel *channel;
	struct te_io_cfg *io_cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);
	int i;
	u32 mtime = input_mtime;

	CHECK_ERROR(io_cfg->version < 2, return -EINVAL,
		    "does not support LGDEMOD type anymore");

	ch_status = kcalloc(dev->num_channel, sizeof(*ch_status), GFP_KERNEL);
	if (!ch_status) {
		return -ENOMEM;
	}

	tpi_status = te_debug_get_tpi_status(tdev);
	if (IS_ERR(tpi_status)) {
		kfree(ch_status);
		return PTR_ERR(tpi_status);
	}

	/* save prev channel status */
	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		get_packet_stats(channel, &ch_status[i]);
	}
	mutex_unlock(&io_mutex);

	msleep(mtime);

	dprintf("Channel Input Status\n");
	dprintf("%3s %12s %12s   %5s %17s %12s\n",
		"Num", "Port", "TPI", "Demod", "Packet", "Speed");

	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		char *rate;
		u32 len;
		struct atsc3_packet_stats *s1 = &ch_status[i];
		struct atsc3_packet_stats s2;
		enum te_reg_tpi_port tpi;

		channel = &dev->channels[i];

		get_packet_stats(channel, &s2);

		len = (u32)(s2.total_length - s1->total_length);
		rate = get_bitrate_str(len, 1, mtime);
		tpi = te_input_port_to_reg_tpi_port(s2.port);

		dprintf("[%u] %12s %12s   %5d %08x/%08x %12s\n", channel->num,
			te_input_port_to_str(s2.port),
			te_reg_tpi_port_to_str(tpi), channel->demod_type,
			s1->pkt_count, s2.pkt_count, rate);
	}
	mutex_unlock(&io_mutex);
	kfree(ch_status);
	dprintf("\n");

	dprintf("TPI Port Status\n");
	te_debug_show_tpi_status(tdev, m, tpi_status);
	te_debug_free_tpi_status(tpi_status);

	return 0;
}

static void debug_show_channel_dump(struct atsc3_channel *channel,
				    struct seq_file *m)
{
	struct timespec64 ts;
	struct atsc3_input_dump *d = &channel->dump;
	enum atsc3_dump_state state = d->state;
	struct atsc3_stats *stats = &channel->stats;
	u32 size, avail, free;

#define dump_printf(t, fmt, args...) dprintf("    %-8s" fmt "\n", t, ##args)
#define dump_printf1(t, fmt, args...) dprintf1("    %-8s" fmt "\n", t, ##args)

	mutex_lock(&io_mutex);

	dprintf("CH[%u] - %s", channel->num, get_input_dump_state_str(state));
	if (state != INPUT_DUMP_RUNNING) {
		dprintf("\n");
		mutex_unlock(&io_mutex);
		return;
	}

	ktime_get_ts64(&ts);
	dprintf(" (%llu.%06usec)\n", ts.tv_sec, (u32)(ts.tv_nsec / 1000));


	dump_printf("LAYER", "%s", te_reg_atsc3_layer_to_str(d->layer));
	dump_printf("MODE", "%s", te_reg_dumper_mode_to_str(d->mode));
	dump_printf("PORT", "%s", te_input_port_to_str(d->port));
	dump_printf("ERROR/OVF/TIME", "  %d/%d/%d", stats->err_pkt_count,
		    stats->overflow_count, stats->time_pkt_count);

	size = te_hwbuf_size(d->data);
	avail = te_hwbuf_avail_size(d->data);
	free = te_hwbuf_free_size(d->data);

	dprintf1("HWBUF\n");
	dump_printf1("RANGE", "0x%08x-0x%08x (%s)", (u32)te_hwbuf_addr(d->data),
		     (u32)te_hwbuf_addr(d->data) + size,
		     te_get_readable_size(size));

	dump_printf1("PTR", "0x%08x-0x%08x (%s,%d%%)",
		     (u32)te_hwbuf_rptr(d->data), (u32)te_hwbuf_wptr(d->data),
		     te_get_readable_size(avail), (avail * 100) / size);

	if (channel->data.start) {
		struct te_msgbuf *mbuf;
		struct te_ringbuf *rbuf;

		rbuf = &d->rbuf;
		size = te_ringbuf_size(rbuf);
		avail = te_ringbuf_avail_size(rbuf);
		free = te_ringbuf_free_size(rbuf);

		dprintf1("RINGBUF\n");
		dump_printf1("RANGE", "%p-%p (%s,%d%%)",
			     te_ringbuf_data(rbuf),
			     te_ringbuf_data(rbuf) + size,
			     te_get_readable_size(size), (avail * 100) / size);

		dump_printf1("IDX", "0x%08x-0x%08x (%s,%d%%)",
			     te_ringbuf_ridx(rbuf), te_ringbuf_widx(rbuf),
			     te_get_readable_size(avail), (avail * 100) / size);

		mbuf = &channel->data.msgbuf;
		avail = te_msgbuf_avail_count(mbuf);
		size = te_msgbuf_count(mbuf);
		dprintf1("MSGBUF\n");
		dump_printf1("COUNT", "%d/%d (%d%%)", avail, size,
			     (avail * 100) / size);
	}

	mutex_unlock(&io_mutex);
}

static int debug_show_dump_status(struct atsc3_device *dev, struct seq_file *m)
{
	int i;

	dprintf("Input Dump Status\n");
	for (i = 0; i < dev->num_channel; i++) {
		if (i)
			dprintf("\n");
		debug_show_channel_dump(&dev->channels[i], m);
	}

	return 0;
}

static int debug_set_channel_input(struct atsc3_channel *channel, char *name)
{
	int ret;
	struct lx_atsc3_channel_input_cfg cfg;

	cfg.port = te_str_to_input_port(name);
	if (cfg.port == LX_TE_INPUT_PORT_INVALID)
		return -EINVAL;

	if (cfg.port == LX_TE_INPUT_PORT_NONE) {
		cfg.enable = false;
		cfg.reset = false;
	} else {
		cfg.enable = true;
		cfg.reset = false;
	}

	mutex_lock(&io_mutex);
	ret = config_channel_input(channel, &cfg);
	mutex_unlock(&io_mutex);

	return ret;
}

static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct atsc3_channel *channel = item->private;

	switch (item->flags) {
	case DEBUG_ID_DEMOD_TYPE:
		mutex_lock(&io_mutex);
		dprintf("%d\n", channel->demod_type);
		mutex_unlock(&io_mutex);
		break;

	case DEBUG_ID_INPUT_DUMP:
		debug_show_channel_dump(channel, m);
		break;

	case DEBUG_ID_CHANNEL_INPUT:
		mutex_lock(&io_mutex);
		dprintf("%s\n", te_input_port_to_str(channel->input_port));
		mutex_unlock(&io_mutex);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_channel_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	u32 type;
	struct atsc3_channel *channel = item->private;

	switch (item->flags) {
	case DEBUG_ID_CHANNEL_INPUT:
		ret = debug_set_channel_input(channel, str);
		break;

	case DEBUG_ID_DEMOD_TYPE:
		type = simple_strtoul(str, NULL, 0);
		mutex_lock(&io_mutex);
		ret = set_demod_type(channel->num, type);
		if (!ret) {
			channel->demod_type = type;
			channel->lgc_hdr_size = get_lgc_hdr_size(type);
		}
		mutex_unlock(&io_mutex);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_channel_ops = {
	.show = debug_channel_show,
	.write = debug_channel_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_NUM("input_mtime", &input_mtime),
};

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM("input", &debug_channel_ops, DEBUG_ID_CHANNEL_INPUT),
	DBGITM_SIM("demod_type", &debug_channel_ops, DEBUG_ID_DEMOD_TYPE),
	DBGITM_SIM_R("dump", &debug_channel_ops, DEBUG_ID_INPUT_DUMP),
};

static void init_debug(struct atsc3_device *dev)
{
	int i;

	debug_create_item_files(debug_list, dev, dev->debug.dir);

	for (i = 0; i < dev->num_channel; i++) {
		struct atsc3_channel *c = &dev->channels[i];
		debug_create_item_files(debug_channel_list, c, c->debug_dir);
	}

	atsc3_debug_register_status_show(dev, ATSC3_DEBUG_STATUS_INPUT,
					 debug_show_input_status);
	atsc3_debug_register_status_show(dev, ATSC3_DEBUG_STATUS_DUMP,
					 debug_show_dump_status);
}

/* atsc3 sub driver */
static int io_dev_ioctl_param(void *priv, unsigned int cmd, void *arg,
			      struct te_ioctl_ptr_param *param)
{
	if (cmd == ATSC3_IOC_CH_DUMP_GET_INFO) {
		LX_ATSC3_DUMP_INFO_T *p = arg;
		param->user_ptr = te_ioctl_get_user_ptr(p->wptr);
		param->kernel_ptr = (void **)&p->wptr;
		param->size = sizeof(*p->wptr);
		param->dir = _IOC_READ;
	}

	return 0;
}

static const struct atsc3_ioctl_info ioctls[] = {
	IOC_INFO(ATSC3_IOC_CFG_CHANNEL_INPUT, ioc_config_channel_input),
	IOC_INFO(ATSC3_IOC_CHANNEL_INPUT_STATUS, ioc_get_channel_input_status),
	IOC_INFO_DEV(ATSC3_IOC_SET_DEMOD_TYPE, ioc_set_demod_type),
	IOC_INFO(ATSC3_IOC_CH_DUMP_START, ioc_start_input_dump),
	IOC_INFO(ATSC3_IOC_CH_DUMP_STOP, ioc_stop_input_dump),
	IOC_INFO_NOLOCK(ATSC3_IOC_CH_DUMP_GET_INFO, ioc_get_input_dump_info),
	IOC_INFO(ATSC3_IOC_CH_DUMP_SET_RPTR, ioc_set_input_dump_rptr),
};

static int io_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return atsc3_do_ioctl(priv, cmd, arg, io_mutex, ioctls);
}

static void io_dev_close(struct atsc3_fh *fh)
{
	struct atsc3_dump_fh *df = fh->dump;

	if (!df)
		return;

	mutex_lock(&io_mutex);
	log_noti("Input dump[%d] is still running (Force stop)", df->dump->ch);
	stop_input_dump(df->dump);
	mutex_unlock(&io_mutex);

	kfree(df);
}

static int io_dev_suspend(struct atsc3_device *dev)
{
	int i;
	struct atsc3_input_dump *dump;

	/* Suspend Input Dump */
	for (i = 0; i < dev->num_channel; i++) {
		dump = &dev->channels[i].dump;
		suspend_input_dump(dump);	//SUSPEND
	}

	return 0;
}

static int io_dev_resume(struct atsc3_device *dev)
{
	struct atsc3_channel *channel;
	int ret, i;
	LX_ATSC3_CHANNEL_INPUT_CFG_T cfg;

	/* remove remained callback works */
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		cfg.port = channel->input_port;
		if (cfg.port != LX_TE_INPUT_PORT_NONE) {
			cfg.enable = true;
			cfg.reset = true;

			ret = config_channel_input(channel, &cfg);
			if (ret)
				log_error("Err in config_channel_input(%u)",
					  channel->num);
		}

		ret = set_demod_type(channel->num, channel->demod_type);
		if (ret)
			log_error("Err in set_demod_type(%u)", channel->num);

		/* Recover Dump work */
		resume_input_dump(&channel->dump);
	}

	return 0;
}

static int io_dev_init(struct atsc3_device *dev)
{
	struct atsc3_channel *channel;
	int ret, i;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		//TODO: Check actual demod type
		set_demod_type(i, LX_ATSC3_DEMOD_TYPE_C);
		channel->demod_type = LX_ATSC3_DEMOD_TYPE_C;
		channel->lgc_hdr_size = get_lgc_hdr_size(channel->demod_type);

		mutex_init(&channel->data.mutex);
	}
	ret = init_input_dump(dev);
	CHECK_ERROR(ret, return ret, "Error in init_input_dump");

	ret = init_input_monitor(dev);
	CHECK_ERROR(ret, return ret, "Error in init_input_monitor");

	init_debug(dev);

	return 0;
}

static void io_dev_release(struct atsc3_device *dev)
{
	te_del_timer(dev->monitor_timer);
}

static const struct atsc3_ioctl ioctl_io = {
	.magic = ATSC3_IOC_IO_MAGIC,
	.func = io_dev_ioctl,
	.get_user_param = io_dev_ioctl_param,
};

const struct atsc3_sub_driver atsc3_io_driver = {
	.name = "atsc3_io",
	.init = io_dev_init,
	.release = io_dev_release,
	.suspend = io_dev_suspend,
	.resume = io_dev_resume,

	.close = io_dev_close,
	.ioctl = &ioctl_io,
};
