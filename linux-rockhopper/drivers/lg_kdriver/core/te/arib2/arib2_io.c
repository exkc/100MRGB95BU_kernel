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
 *  arib2 driver
 *
 *  @author	Yeonju Lee (yeonju.lee@lge.com)
 *  @version	1.0
 *  @date	2017-11-21
 *  @note	Additional information.
 */

#include <linux/delay.h>
#include <lg1k/te/io.h>
#include <lg1k/te/dump.h>
#include <lg1k/te/ipc.h>

#include "hma_alloc.h"

#include "arib2_impl.h"

#define INPUT_DUMP_TIMER_INTERVAL	20 	/* msec */
#define INPUT_DUMP_WARNING_SIZE		50	/* 50% */
#define INPUT_DUMP_WARNING_INTERVAL	1000	/* msec */
#define META_SIZE			16

#define TLV_TIMESTAMP_SIZE		4
#define TLV_HDR_SIZE			4
#define TLV_HDR_W_TIME			(TLV_TIMESTAMP_SIZE+TLV_HDR_SIZE)

#define TLV_SYNCBYTE			0x7F
#define TLV_MAX_DATA_SIZE		5049

#define TLV_PACKET_OVERFLOW_RATE	90
#define TLV_PACKET_WARNIG_INTERVAL	1000	/* 1 seconds */


struct channel_input_status {
	LX_TE_INPUT_PORT_T input_port;
	u64 total_length;
	u32 pkt_count;		/* all tlv packets including err_pkt */
	u32 err_pkt_count;	/* tlv sync lost or length error */
	u32 overflow_count;	/* packet buffer overflow count */
};

#define swtlv_to_arib2_channel(swtlv) \
	container_of(swtlv, struct arib2_channel, swtlv)

static void debug_raw_callback(struct arib2_channel *channel,
			       struct te_hwbuf *hbuf, u32 paddr, u32 size);

static DEFINE_MUTEX(io_mutex);
static DEFINE_MUTEX(debug_mutex);

/*--------------------------- DUMP START --------------------------------*/
static const char *get_input_dump_state_str(enum arib2_dump_state state)
{
	switch (state) {
	case INPUT_DUMP_STATE_IDLE:
		return "IDLE";
	case INPUT_DUMP_STATE_RUNNING:
		return "RUNNING";
	case INPUT_DUMP_STATE_SUSPEND:
		return "SUSPENDED";
	default:
		return "UNKNOWN";
	}
}

static void data_read_callback(void *arg, u32 idx)
{
	struct arib2_input_dump *dev = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dev->data, idx, &ptr);
	te_reg_dumper_set_data_rptr(dev->ch, (u32)ptr);
}

static void meta_read_callback(void *arg, u32 idx)
{
	struct arib2_input_dump *dev = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(dev->meta, idx, &ptr);
	te_reg_dumper_set_meta_rptr(dev->ch, (u32)ptr);
}

static void pktbuf_read_callback(void *arg, u32 idx)
{
	struct te_hwbuf *hbuf;
	struct arib2_input_dump *dev = arg;

	hbuf = dev->data;

	if (unlikely(idx == TE_BUF_IDX_FLUSH)) {
		u32 v = DUMPER_INTR_DATA_AL_FULL_CH0;
		log_error("ch%d overflow detected. flush now", dev->ch);
		te_hwbuf_flush(hbuf);
		te_reg_dumper_clear_intr(v << dev->ch);
		te_reg_dumper_set_intr_enable((v << dev->ch), true);
	} else if (unlikely(idx == TE_BUF_IDX_RESET)) {
		te_hwbuf_reset(hbuf);
	} else {
		te_hwbuf_set_ridx(hbuf, idx);
	}
}

static void release_pkt_data(struct arib2_channel *channel)
{
	struct arib2_data *arib2_data = &channel->data;
	void *addr;

	mutex_lock(&arib2_data->mutex);
	if (!arib2_data->start) {
		log_noti("already stopped");
		mutex_unlock(&arib2_data->mutex);
		return;
	}

	addr = te_pktbuf_data(&arib2_data->pbuf);

	te_pktbuf_set_error(&arib2_data->pbuf, -ESHUTDOWN);
	te_pktbuf_release(&arib2_data->pbuf);

	arib2_data->buf = NULL;
	arib2_data->start = false;

	mutex_unlock(&arib2_data->mutex);

	return;
}

static int init_pkt_data(struct arib2_channel *channel, struct te_hwbuf *hbuf,
			 u32 flag)
{
	struct arib2_data *arib2_data = &channel->data;
	void *pkt_buf;
	u32 size;
	int ret;
#define TLV_PACKET_OVERFLOW_RATE	90
#define TLV_PACKET_WARNIG_INTERVAL	1000	/* 1 seconds */

	log_noti("%s(%u)", __func__, channel->num);

	CHECK_ERROR(arib2_data->start, return -EIO, "already started");

	pkt_buf = te_hwbuf_data(hbuf);
	size = te_hwbuf_size(hbuf);

	ret = te_pktbuf_init(&arib2_data->pbuf, pkt_buf, size, 1024, flag);
	CHECK_ERROR(ret < 0, return ret, "Error in te_pktbuf_init");

	arib2_data->warn_bufsize = (size * TLV_PACKET_OVERFLOW_RATE) / 100;
	arib2_data->warn_time = 0;
	arib2_data->warn_interval = TLV_PACKET_WARNIG_INTERVAL;
	arib2_data->buf = pkt_buf;
	arib2_data->start = true;
	arib2_data->last_read_time = 0;

	te_pktbuf_set_read_callback(&channel->data.pbuf, pktbuf_read_callback,
				    &channel->dump);
	return 0;
}

/* timer start */
static void process_input_data(struct arib2_input_dump *dump)
{
	mod_timer(&dump->timer, jiffies + dump->timer_interval);

	if (dump->flags & ARIB2_DUMP_FLAG_WORKQUEUE) {
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

static void __input_dump_timer(struct arib2_input_dump *dump)
{
	unsigned long flag;

	spin_lock_irqsave(&dump->spinlock, flag);

	if (dump->state == INPUT_DUMP_STATE_RUNNING) {
		process_input_data(dump);
	}

	spin_unlock_irqrestore(&dump->spinlock, flag);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void input_dump_timer(struct timer_list *t)
{
	struct arib2_input_dump *dump = from_timer(dump, t, timer);
	__input_dump_timer(dump);
}
#else
static void input_dump_timer(unsigned long data)
{
	struct arib2_input_dump *dump = (struct arib2_input_dump *)data;
	__input_dump_timer(dump);
}
#endif

static void start_input_dump_timer(struct arib2_input_dump *dump)
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

static void stop_input_dump_dev(struct arib2_input_dump *dev)
{
	int rc;

	del_timer(&dev->timer);

	te_reg_dumper_set_intr_enable(dev->intr, false);

	rc = te_reg_dumper_set_channel_enable(dev->ch, false);
	CHECK_ERROR(rc,, "Err in te_reg_dumper_set_channel_enable");

	te_hwbuf_set_read_callback(dev->data, NULL, dev);
	te_hwbuf_set_read_callback(dev->meta, NULL, dev);
}

static int stop_input_dump(struct arib2_input_dump *dev)
{
	unsigned long flag;
	CHECK_NULL_PARAM(dev);

	log_noti("%s(ch:%d,%s)", __func__, dev->ch,
		 get_input_dump_state_str(dev->state));

	CHECK_ERROR(dev->state != INPUT_DUMP_STATE_RUNNING, return -EINVAL,
		    "already stopped");

	spin_lock_irqsave(&dev->spinlock, flag);
	dev->state = INPUT_DUMP_STATE_IDLE;
	spin_unlock_irqrestore(&dev->spinlock, flag);

	log_noti("cancel_work_sync start");
	cancel_work_sync(&dev->work);
	stop_input_dump_dev(dev);

	log_noti("%s done", __func__);

	return 0;
}

static void start_input_dump_dev(struct arib2_input_dump *dev)
{
	u32 intr;
	u8 ch = dev->ch;
	u32 addr, size, unit_size;
	int rc;

	te_hwbuf_reset(dev->data);
	te_hwbuf_reset(dev->meta);

	addr = (u32)te_hwbuf_addr(dev->data);
	size = te_hwbuf_size(dev->data);
	unit_size = te_hwbuf_unit_size(dev->data);
	intr = (DUMPER_INTR_DATA_AL_FULL_CH0 << ch);
	if (unit_size) {
		intr |= (DUMPER_INTR_DATA_UNIT_BUF_CH0 << ch);
	}

	if (size > (0xFFFFFFFF / 100))
		dev->warning_size = (size / 100) * INPUT_DUMP_WARNING_SIZE;
	else
		dev->warning_size = (size * INPUT_DUMP_WARNING_SIZE) / 100;
	dev->warn_interval = INPUT_DUMP_WARNING_INTERVAL;
	dev->warn_time = 0;

	te_reg_dumper_set_data_buf(ch, addr, addr + size);
	te_reg_dumper_set_data_rptr(ch, addr);
	te_reg_dumper_set_data_unitbuf_size(ch, unit_size);
	te_reg_dumper_set_data_almostfull_level(ch, TLV_MAX_DATA_SIZE * 2);

	addr = (u32)te_hwbuf_addr(dev->meta);
	size = te_hwbuf_size(dev->meta);
	unit_size = te_hwbuf_unit_size(dev->meta);
	if (unit_size) {
		intr |= ((DUMPER_INTR_META_UNIT_BUF_CH0 << ch) |
			 (DUMPER_INTR_META_AL_FULL_CH0 << ch));
	}

	te_reg_dumper_set_meta_buf(ch, addr, addr + size);
	te_reg_dumper_set_meta_rptr(ch, addr);
	te_reg_dumper_set_meta_unitbuf_size(ch, unit_size);
	te_reg_dumper_set_meta_almostfull_level(ch, META_SIZE);

	te_hwbuf_set_read_callback(dev->data, data_read_callback, dev);
	te_hwbuf_set_read_callback(dev->meta, meta_read_callback, dev);

	te_reg_dumper_set_channel_mode(ch, dev->mode);

	rc = te_reg_dumper_set_channel_enable(ch, true);
	CHECK_ERROR(rc,, "Err in te_reg_dumper_set_channel_enable(%d)", ch);

	te_reg_dumper_set_intr_enable(intr, true);

	start_input_dump_timer(dev);

	dev->intr = intr;
}


static struct arib2_input_dump *start_input_dump(struct arib2_channel *channel,
						 struct arib2_dump_cfg *cfg)
{
	struct arib2_input_dump *dump;

	log_noti("%s(%u)", __func__, channel->num);

	dump = &channel->dump;

	CHECK_ERROR(dump->state != INPUT_DUMP_STATE_IDLE, return NULL,
		    "already started");

	dump->flags = cfg->flags;
	dump->data = cfg->data;
	dump->meta = cfg->meta;
	dump->mode = cfg->mode;
	dump->timer_interval = msecs_to_jiffies(INPUT_DUMP_TIMER_INTERVAL);

	start_input_dump_dev(dump);

	dump->state = INPUT_DUMP_STATE_RUNNING;

	return dump;
}

static void reset_input_dump(struct arib2_channel *channel)
{
	struct arib2_input_dump *dev = &channel->dump;
	struct arib2_data *arib2_data;

	if (dev->state != INPUT_DUMP_STATE_RUNNING)
		return;

	log_noti("%s(%u)", __func__, channel->num);

	arib2_data = &channel->data;

	te_pktbuf_set_error(&arib2_data->pbuf, -ESHUTDOWN);

	stop_input_dump(dev);

	te_pktbuf_reset(&arib2_data->pbuf);

	start_input_dump_dev(dev);

	dev->state = INPUT_DUMP_STATE_RUNNING;
}

/*--------------------------- DUMP END --------------------------------*/

static void get_channel_input_status(struct arib2_channel *channel,
				     struct channel_input_status *status)
{
	struct arib2_data_stat *stat = &channel->data.stat;

	status->input_port = channel->input_port;
	status->total_length = stat->total_length;
	status->pkt_count = stat->packet_count;
	status->overflow_count = stat->overflow_count;
	status->err_pkt_count = stat->err_packet_count;
}

/*--------------------------- MONITOR START --------------------------------*/

static void control_input_monitor(struct arib2_channel *channel, bool enable)
{
	struct arib2_input_monitor *m;
	enum te_reg_tpi_port tpi;

	m = &channel->monitor;

	m->enable = enable;
	if (enable) {
		m->ready = false;
		tpi = te_input_port_to_reg_tpi_port(channel->input_port);
		snprintf(m->name, sizeof(m->name), "[CH_%u] %s/%s",
			 channel->num,
			 te_input_port_to_str(channel->input_port),
			 te_reg_tpi_port_to_str(tpi));
	}
}

static void detect_input_change(struct arib2_input_monitor *m,
				struct channel_input_status *status)
{
#define MAX_MESSAGE_COUNT	10
#define log_packet(fmt, args...) log_noti("%s - " fmt, m->name, ##args)

	if (m->pkt_count == status->pkt_count) {
		if (!m->no_input) {
			log_packet("NO INPUT PACKET");
			m->no_input = true;
		}
		return;
	}

	if (m->no_input) {
		log_packet("recover input packet");
		m->no_input = false;
	}

	if (m->overflow_count != status->overflow_count ||
	    m->err_pkt_count != status->err_pkt_count) {
		if (m->message_count < MAX_MESSAGE_COUNT) {
			log_packet("pkt:%u(%u/%u) err:%u(%u/%u) ovf:%u(%u/%u)",
				   status->pkt_count - m->pkt_count,
				   m->pkt_count, status->pkt_count,
				   status->err_pkt_count - m->err_pkt_count,
				   m->err_pkt_count, status->err_pkt_count,
				   status->overflow_count - m->overflow_count,
				   m->overflow_count, status->overflow_count);
			m->message_count++;
			if (m->message_count == MAX_MESSAGE_COUNT) {
				log_packet("disable packet monitor message");
			}
		}
	} else {
		if (m->message_count > 0) {
			if (m->message_count == MAX_MESSAGE_COUNT) {
				log_packet("re-enable packet monitor message");
				m->message_count = 0;
			} else {
				m->message_count--;
			}
		}
	}
}

static void check_channel_input_staus(struct arib2_input_monitor *m,
				      struct channel_input_status *status)
{
	if (m->ready) {
		detect_input_change(m, status);
	} else {
		/* change ready status after getting status */
		m->ready = true;
		m->no_input = false;
		m->message_count = 0;
	}

	m->pkt_count = status->pkt_count;
	m->err_pkt_count = status->err_pkt_count;
	m->overflow_count = status->overflow_count;
}

static void input_monitor(void *arg)
{
	struct channel_input_status status;
	struct arib2_channel *channel;
	struct arib2_device *dev = arg;
	int i;

	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		if (!channel->monitor.enable || !channel->data.start)
			continue;

		get_channel_input_status(channel, &status);

		check_channel_input_staus(&channel->monitor, &status);
	}
	mutex_unlock(&io_mutex);
}

static int init_input_monitor(struct arib2_device *dev)
{
	int i;
	struct arib2_input_monitor *m;
	struct te_timer *timer;
	struct te_device *tdev = get_te_device(dev);
#define INPUT_MONITOR_INTERVAL		500	/* 500ms */

	for (i = 0; i < dev->num_channel; i++) {
		m = &dev->channels[i].monitor;
		m->enable = false;
	}

	timer = te_add_timer(tdev, INPUT_MONITOR_INTERVAL, input_monitor, dev);
	CHECK_ERROR(!timer, return -EIO, "Error in te_add_timer");

	dev->monitor_timer = timer;

	return 0;
}

/*--------------------------- MONITOR END --------------------------------*/

/*--------------------------- SWTLV START--------------------------------*/
#ifdef SUPPORT_SWTLV_FUNC
static void swtlv_debug_raw_callback(struct arib2_swtlv *swtlv, u32 size);
static int swtlv_config_channel_input(struct arib2_channel *channel,
				      LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg);

void arib2_swtlv_register_data_callback(struct arib2_channel *channel,
					swtlv_cb_func_t func, void *arg)
{
	struct swtlv_callback *c;

	c = &channel->swtlv.callback;

	mutex_lock(&c->mutex);

	c->func = func;
	c->arg = arg;

	mutex_unlock(&c->mutex);
}

static int _swtlv_find_sync(u8 *buf, u32 offset)
{
	int i;

	if (offset == 0)
		offset = 4;
	for (i = offset; i < 192; i++) {
		if (buf[i] == TLV_SYNCBYTE)
			return i;
	}
	return 0;
}

/**
 * Get next_sync_pos, next_sync_offset, and jump length.
 *
 * @param	swtlv		[in/out]
 * @param	rptr		[in]
 * @param	wptr		[in]
 * @param	skip		[out]
 * @return	0		- sync byte(0x7F) is in the next position.
 *		-ENODATA	- need more sdec data to get next position.
 *		-EIO		- sync byte(0x7F) is not in the next position.
 */

static int swtlv_get_next_sync_pos(struct arib2_swtlv *swtlv, u32 offset,
				   u32 avail_size, u32 *skip)
{
	u8 hdr[4];
	int x, y, z;
	u8 *buf;
	u8 sync_offset;
	struct swtlv_input_dump *dump = &swtlv->dump;
	u32 jump, length;
	struct te_hwbuf *hbuf = &dump->hbuf;

	sync_offset = swtlv->sync_offset;

	if (sync_offset > 188) {
		u8 s1, s2;

		if ((offset + 192) >= avail_size)
			return -ENODATA;

		s1 = 192 - sync_offset;
		s2 = 4 - s1;
		te_hwbuf_raw_peek(hbuf, offset + sync_offset, &hdr[0], s1);
		te_hwbuf_raw_peek(hbuf, offset + 192 + 4, &hdr[s1], s2);
	} else {
		te_hwbuf_raw_peek(hbuf, offset + sync_offset, &hdr[0], 4);
	}

	length = TE_GET16(&hdr[2]);

	if (length > TLV_MAX_DATA_SIZE) {
		log_debug("over the max length. (0x%04x)", length);
		return -EIO;
	}

	swtlv->tlv_size = length;
	length += TLV_HDR_SIZE;

	/* jump: buf[0] ~ next_sync */
	x = 192 - sync_offset;
	if (length < x) {
		jump = 0;
		sync_offset = sync_offset + length;
	} else {
		length -= x;
		y = (length / 188) + 1;
		z = length % 188;

		jump = 192 * y;
		sync_offset = 4 + z;
	}

	// TODO: distinguish waiting for the data from the get next sync pos
	if ((offset + jump) >= avail_size)
		return -ENODATA;

	*skip = jump;

	te_hwbuf_raw_get_cont_rbuf(hbuf, offset + jump, 1, (void **)&buf);
	if (buf[sync_offset] != TLV_SYNCBYTE) {
		log_debug("can't find next sync."
			  "jump:0x%x offset:0x%x sync_offset:%d value:0x%02x\n",
			  jump, offset, sync_offset, buf[sync_offset]);
		return -EIO;
	}
	swtlv->next_sync_offset = sync_offset;

	return 0;
}

static int swtlv_detect_sync(struct arib2_swtlv *swtlv, u32 *offset,
			     u32 avail_size)
{
	u8 *buf;
	u8 find_cnt;
	u32 jump;
	u32 ofs = *offset;
	struct te_hwbuf *hbuf = &swtlv->dump.hbuf;
	int ret = 0;
#define NUM_OF_SYNC_CHECK		3

	find_cnt = swtlv->find_cnt;

	while (1) {
		if (ofs >= avail_size) {
			ret = -ENODATA;
			break;
		}

		te_hwbuf_raw_get_cont_rbuf(hbuf, ofs, 192, (void **)&buf);

		if (find_cnt == 0) {
			swtlv->sync_offset =
			    _swtlv_find_sync(buf, swtlv->next_sync_offset);
		} else {
			swtlv->sync_offset = swtlv->next_sync_offset;
		}

		if (swtlv->sync_offset == 0) {
			/* couldn't found. reset find count */
			if (find_cnt)
				log_debug("sync lost. find_cnt reset(%d)",
					  find_cnt);

			find_cnt = 0;
			swtlv->next_sync_offset = 0;

			ofs += 192;
			continue;
		}

		/* give current and get jump size for next pos */
		ret = swtlv_get_next_sync_pos(swtlv, ofs, avail_size, &jump);
		if (ret == 0) {
			/* found next sync, do not jump */
			find_cnt++;
			if (find_cnt >= NUM_OF_SYNC_CHECK)
				break;
			ofs += jump;
		} else {
			if (ret == -ENODATA) {
				break;
			} else {
				/* fail to found sync at the next sync position */
				log_debug("sync lost. "
					  "find_cnt(%d) sync_offset:0x%x",
					  find_cnt, swtlv->sync_offset);

				swtlv->next_sync_offset =
				    (swtlv->sync_offset + 1) % 192;
				if (swtlv->next_sync_offset == 0) {
					swtlv->next_sync_offset = 4;
					ofs += 192;
				}
				find_cnt = 0;
			}
			break;	// TODO: break evenif not NODATA ?
		}
	}

	swtlv->find_cnt = find_cnt;
	*offset = ofs;

	return ret;
}

static void swtlv_process_tlv_packet(struct arib2_swtlv *swtlv, u32 timestamp,
				     u8 *pkt, u32 pkt_size)
{
	mutex_lock(&swtlv->callback.mutex);
	if (swtlv->callback.func) {
		swtlv->callback.func(swtlv->callback.arg, timestamp, pkt,
				     pkt_size);
	}
	mutex_unlock(&swtlv->callback.mutex);
}

static int swtlv_process_data(struct arib2_swtlv *swtlv, u32 *offset,
			      u32 avail_size)
{
	u8 *buf, *pkt;
	u32 sync_offset, remained, wsize, woffset, pkt_size, timestamp;
	struct te_pktbuf *pbuf;
	u32 jump;
	int ret;
	u32 ofs = *offset;
	struct te_hwbuf *hbuf = &swtlv->dump.hbuf;
	struct arib2_data *arib2_data = swtlv->data;

	/* find next sync byte position */
	ret = swtlv_get_next_sync_pos(swtlv, ofs, avail_size, &jump);
	if (ret == -ENODATA)
		return ret;

	if (ret == -EIO) {
		log_debug("Lost tlv sync - tlv_size:0x%x", swtlv->tlv_size);

		swtlv->find_cnt = 0;
		swtlv->next_sync_offset = (swtlv->sync_offset + 1) % 192;
		if (swtlv->next_sync_offset == 0) {
			swtlv->next_sync_offset = 4;	/* skip timestmap */
			ofs += 192;
			*offset = ofs;
		}
		arib2_data->stat.err_packet_count++;
		arib2_data->stat.packet_count++;

		return ret;
	}

	te_hwbuf_raw_get_cont_rbuf(hbuf, ofs, 192, (void **)&buf);
	sync_offset = swtlv->sync_offset;
	pkt_size = TLV_HDR_SIZE + swtlv->tlv_size;
	remained = pkt_size;

	mutex_lock(&arib2_data->mutex);

	pbuf = &arib2_data->pbuf;

	//consider wsize is less than 192?
	if (arib2_data->start) {
		ret = te_pktbuf_get_cont_wbuf(pbuf, remained, (void **)&pkt);
		if (ret < 0) {
			arib2_data->stat.overflow_count++;
			/*
			   user packet buffer overflow.
			   need pcr recovery and the other function.
			 */
			pkt = swtlv->pkt_buf;
		}
	} else {
		pkt = swtlv->pkt_buf;
	}

	timestamp = TE_GET32(buf);

	wsize = (sync_offset + remained > 192) ? (192 - sync_offset) : remained;
	memcpy(pkt, &buf[sync_offset], wsize);

	if (sync_offset + wsize == 192) {
		ofs += 192;
	}
	remained -= wsize;
	woffset = wsize;

	while (remained) {
		te_hwbuf_raw_get_cont_rbuf(hbuf, ofs, 192, (void **)&buf);

		wsize = MIN(remained, 188);
		memcpy(&pkt[woffset], buf + 4, wsize);

		if (wsize == 188)
			ofs += 192;

		remained -= wsize;
		woffset += wsize;
	}

	swtlv_process_tlv_packet(swtlv, timestamp, pkt, pkt_size);
	if (pkt != swtlv->pkt_buf) {
		te_pktbuf_add_packet(pbuf, pkt, pkt_size);
	}
	arib2_data->stat.packet_count++;
	arib2_data->stat.total_length += pkt_size;

	mutex_unlock(&arib2_data->mutex);

	swtlv->sync_offset = swtlv->next_sync_offset;

	*offset = ofs;

	return 0;
}

static int swtlv_process_input_stream(struct arib2_swtlv *swtlv)
{
	int ret = 0;
	u32 offset, avail_size;
	struct te_hwbuf *hbuf = &swtlv->dump.hbuf;

	offset = 0;
	avail_size = te_hwbuf_avail_size(hbuf);

	while (swtlv->status == SWTLV_STATUS_RUNNING) {
		if (te_hwbuf_error(hbuf)) {
			te_hwbuf_flush(hbuf);

			// TODO: make reset swtlv input dump
			swtlv->sync = false;
			swtlv->find_cnt = 0;
			swtlv->next_sync_offset = 0;

			break;
		}

		if (swtlv->sync == false) {
			/* find the third sync position */
			ret = swtlv_detect_sync(swtlv, &offset, avail_size);
			if (ret == 0)
				swtlv->sync = true;
		}

		if (swtlv->sync == true) {
			ret = swtlv_process_data(swtlv, &offset, avail_size);
			if (ret == -EIO)
				swtlv->sync = false;
		}

		if (offset) {
			swtlv_debug_raw_callback(swtlv, offset);
			te_hwbuf_read_skip(hbuf, offset);
			avail_size -= offset;
			offset = 0;
		}

		if (ret == -ENODATA)
			break;
	}
	return ret;
}

/* swtlv isr */
static int swtlv_input_ts_dump_callback(void *data, void *arg)
{
	int rc;
	u32 new_wptr;
	struct arib2_swtlv *swtlv;
	IPC_MSG_DEBUG_DUMP_DATA_T *msg = data;
	struct swtlv_input_dump *dump = arg;
	unsigned long flag;

	/*      sdec dump is protected by ipc->spin_lock.
	   when stop, it frees dump->hbuf after dump callback is null */

	new_wptr = msg->buf_wptr;
	if (te_hwbuf_is_invalid_paddr(&dump->hbuf, new_wptr)) {
		log_error("ptr %08x is out of range", new_wptr);
		return -EINVAL;
	}

	if (msg->status == IPC_DATA_STATUS_OK) {
		/* Buffer allocation warning */
		u32 free_size = te_hwbuf_free_size(&dump->hbuf);
		if (free_size <= dump->warning_size) {
			u32 elapsed =
			    jiffies_to_msecs(jiffies - dump->warn_time);
			if (elapsed >= dump->warn_interval) {
				log_warning
				    ("buffer almost full(free=%d,total=%d)",
				     free_size, te_hwbuf_size(&dump->hbuf));
				dump->warn_time = jiffies;
			}
		}

		rc = te_hwbuf_set_wptr(&dump->hbuf, new_wptr);
		CHECK_ERROR(rc < 0,, "Error in te_hwbuf_set_wptr(0x%x)",
			    new_wptr);
	} else if (msg->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR
		   || msg->status == IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF) {
		log_error("buffer overflow(status=%d", msg->status);
		te_hwbuf_set_error(&dump->hbuf, -ENOBUFS);
	} else {
		log_warning("Unknown status type[%d]", msg->status);
		return -EINVAL;
	}

	swtlv = container_of(dump, struct arib2_swtlv, dump);
	spin_lock_irqsave(&swtlv->spinlock, flag);
	if (swtlv->status == SWTLV_STATUS_RUNNING)
		queue_work(system_wq, &swtlv->work);
	spin_unlock_irqrestore(&swtlv->spinlock, flag);

	return 0;
}

static void swtlv_read_callback(void *arg, u32 idx)
{
	struct swtlv_input_dump *dump = arg;
	phys_addr_t ptr;

	te_hwbuf_idx_to_paddr(&dump->hbuf, idx, &ptr);
	TE_IPC_SetInputDumpRptr(dump->ch, (u32)ptr);
}

static int swtlv_start_input_dump(struct arib2_swtlv *swtlv)
{
	IPC_ADAP_DEBUG_DUMP_INFO_T info;
	struct swtlv_input_dump *dump = &swtlv->dump;
	u32 paddr, size;
	u32 flags;
	u8 ch = dump->ch;
	int rc;

	log_noti("%s(%d)", __func__, ch);

	TE_IPC_RegisterDumpUpdateCallback(ch, swtlv_input_ts_dump_callback,
					  dump);

	size = 192 * 45 * 1024;	//8.43M
	paddr =
	    (u32)hma_alloc_user(TE_MEM_SHARED_NAME, size, 4096, "sdec_dump");
	CHECK_ERROR(!paddr, goto err_alloc, "no hma memory");

	/* Register message info, except buf status addr */
	info.type = IPC_DUMP_TYPE_FE_MAIN;
	info.use_timestamp = IPC_TIMESTAMP_90KHZ_PRECISION;
	info.clock_src = IPC_DUMP_CLK_GSTCC0;	//for timestamp
	info.unit_size = 192 * 1024;
	info.saddr = paddr;
	info.eaddr = paddr + size;

	flags = TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP_CACHED;

	rc = te_hwbuf_init(&dump->hbuf, paddr, size, 192 * 1024, flags);
	CHECK_ERROR(rc < 0, goto err_hwbuf, "Error in te_hwbuf_init");

	te_hwbuf_set_read_callback(&dump->hbuf, swtlv_read_callback, dump);

	if (size > (0xFFFFFFFF / 100))
		dump->warning_size = (size / 100) * INPUT_DUMP_WARNING_SIZE;
	else
		dump->warning_size = (size * INPUT_DUMP_WARNING_SIZE) / 100;
	dump->warn_interval = INPUT_DUMP_WARNING_INTERVAL;
	dump->warn_time = 0;

	rc = TE_IPC_StartInputDump(ch, &info);
	CHECK_ERROR(rc != 0, goto err_start,
		    "Error(%d) in TE_IPC_StartInputDump", rc);

	swtlv->sync = false;
	swtlv->find_cnt = 0;
	swtlv->next_sync_offset = 0;

	return 0;

err_start:
	te_hwbuf_release(&dump->hbuf);
err_hwbuf:
	hma_free(TE_MEM_SHARED_NAME, paddr);
err_alloc:
	TE_IPC_RegisterDumpUpdateCallback(ch, NULL, NULL);

	return -EIO;
}

static void swtlv_stop_input_dump(struct arib2_swtlv *swtlv)
{
	struct swtlv_input_dump *dump = &swtlv->dump;
	phys_addr_t paddr;
	int ret;

	TE_IPC_RegisterDumpUpdateCallback(dump->ch, NULL, NULL);

	ret = TE_IPC_StopInputDump(dump->ch);
	CHECK_ERROR(ret != 0 && ret != -ERESTARTSYS,,
		    "Error(%d) in TE_IPC_StopInputDump", ret);

	paddr = te_hwbuf_addr(&dump->hbuf);
	hma_free(TE_MEM_SHARED_NAME, paddr);
	te_hwbuf_release(&dump->hbuf);
}

static void swtlv_data_callback_work(struct work_struct *work)
{
	struct arib2_swtlv *swtlv;
	swtlv = container_of(work, struct arib2_swtlv, work);

	swtlv_process_input_stream(swtlv);
}

static int swtlv_start(struct arib2_swtlv *swtlv)
{
	int ret;

	if (swtlv->status == SWTLV_STATUS_RUNNING)
		return 0;

	swtlv->pkt_buf = vmalloc(TLV_HDR_W_TIME + TLV_MAX_DATA_SIZE);
	CHECK_ERROR(swtlv->pkt_buf == NULL, return -ENOMEM, "no memory");

	ret = swtlv_start_input_dump(swtlv);
	CHECK_ERROR(ret != 0, goto error, "Error in swtlv_start_input_dump");

	swtlv->status = SWTLV_STATUS_RUNNING;

	return 0;

error:
	vfree(swtlv->pkt_buf);
	swtlv->pkt_buf = NULL;

	return -EIO;
}

static void swtlv_stop(struct arib2_swtlv *swtlv)
{
	unsigned long flag;

	if (swtlv->status != SWTLV_STATUS_RUNNING)
		return;

	spin_lock_irqsave(&swtlv->spinlock, flag);
	swtlv->status = SWTLV_STATUS_IDLE;
	spin_unlock_irqrestore(&swtlv->spinlock, flag);

	/* stop sdec dump after work is finished. for nolock */
	flush_work(&swtlv->work);
	swtlv_stop_input_dump(swtlv);

	if (swtlv->pkt_buf) {
		vfree(swtlv->pkt_buf);
		swtlv->pkt_buf = NULL;
	}
}

static void swtlv_release_ioc_pkt_data(struct arib2_channel *channel,
				       struct arib2_dump_fh *df)
{
	struct arib2_data *arib2_data = &channel->data;
	void *addr;

	mutex_lock(&arib2_data->mutex);
	if (arib2_data->start == false) {
		log_noti("already stopped");
		mutex_unlock(&arib2_data->mutex);
		return;
	}

	addr = te_pktbuf_data(&arib2_data->pbuf);

	te_pktbuf_release(&arib2_data->pbuf);

	vfree(addr);

	arib2_data->buf = NULL;
	arib2_data->start = false;

	mutex_unlock(&arib2_data->mutex);

	return;
}

static int swtlv_init_ioc_pkt_data(struct arib2_channel *channel,
				   struct arib2_dump_fh *df)
{
	void *data;
	int rc;
	u32 flag, size;
	struct arib2_data *arib2_data = &channel->data;

#define TLV_PACKET_BUF_SIZE		(12*1024*1024)

	CHECK_ERROR(arib2_data->start, return -EIO, "already started");

	size = TLV_PACKET_BUF_SIZE;
	data = vmalloc(size);
	CHECK_ERROR(!data, return -ENOMEM, "no memory");

	flag = TE_BUF_FLAG_LINEAR_BUFFER;

	rc = te_pktbuf_init(&arib2_data->pbuf, data, size, 1024, flag);
	CHECK_ERROR(rc < 0, goto err_pkt_init, "Error in te_pktbuf_init");

	arib2_data->warn_bufsize = (size * TLV_PACKET_OVERFLOW_RATE) / 100;
	arib2_data->warn_time = 0;
	arib2_data->warn_interval = TLV_PACKET_WARNIG_INTERVAL;
	arib2_data->buf = data;

	arib2_data->start = true;

	df->swtlv = &channel->swtlv;

	return 0;

err_pkt_init:
	vfree(data);

	return -EIO;
}

static void swtlv_init(struct arib2_channel *channel)
{
	struct arib2_swtlv *swtlv = &channel->swtlv;
#define SWTLV_DUMP_CH			3

	swtlv->dump.ch = SWTLV_DUMP_CH;

	INIT_WORK(&swtlv->work, swtlv_data_callback_work);
	mutex_init(&swtlv->callback.mutex);
	spin_lock_init(&swtlv->spinlock);

	swtlv->data = &channel->data;
	swtlv->status = SWTLV_STATUS_IDLE;
}

static int swtlv_resume(struct arib2_device *dev)
{
	LX_ARIB2_CHANNEL_INPUT_CFG_T cfg;
	struct arib2_channel *channel;
	int i;

	log_noti("%s", __func__);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		cfg.port = channel->input_port;
		if (cfg.port != LX_TE_INPUT_PORT_NONE) {
			cfg.reset = true;
			cfg.enable = true;
			swtlv_config_channel_input(channel, &cfg);
		}
	}
	return 0;
}

static int swtlv_suspend(struct arib2_device *dev)
{
	struct arib2_channel *channel;
	struct arib2_swtlv *swtlv;
	unsigned long flag;
	int i, rc = 0;

	log_noti("%s", __func__);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		swtlv = &channel->swtlv;

		if (swtlv->status == SWTLV_STATUS_RUNNING) {
			swtlv_stop(swtlv);

			rc = TE_REG_SetChannelSource(swtlv->dump.ch,
						     CH_SRC_DISABLE);
			CHECK_ERROR(rc != 0, return rc,
				    "Error(%d) in TE_REG_SetChannelSource", rc);

			/* no lock for monitor.
			   when suspend called, timer is no running */
			control_input_monitor(channel, false);

			spin_lock_irqsave(&swtlv->spinlock, flag);
			swtlv->status = SWTLV_STATUS_SUSPEND;
			spin_unlock_irqrestore(&swtlv->spinlock, flag);
		}
	}
	return rc;
}

static int swtlv_config_channel_input(struct arib2_channel *channel,
				      LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg)
{
	int rc;
	enum te_reg_channel_src src;
	u8 ch;
	struct arib2_swtlv *swtlv;

	log_noti("ch %u, port: %s -> %s, enable: %d, reset: %d",
		 channel->num, te_input_port_to_str(channel->input_port),
		 te_input_port_to_str(cfg->port), cfg->enable, cfg->reset);

	swtlv = &channel->swtlv;
	ch = swtlv->dump.ch;

	src = te_input_port_to_reg_ch_src(cfg->port);
	CHECK_PARAM(src == CH_SRC_INVALID, "Invalid input port:[%x]",
		    cfg->port);

	if (cfg->enable) {
		rc = TE_REG_SetPidfBypass(ch, PIDF_BYPASS_TYPE_192BYTE);
		CHECK_ERROR(rc != 0, return rc,
			    "Error in TE_REG_SetPidfBypass(%d)", ch);

		if (cfg->reset || channel->input_port != cfg->port) {
			/* reset input port if input source is changed */
			TE_REG_SetChannelSource(ch, CH_SRC_DISABLE);
			TE_REG_ResetPidFilter(ch);
			TE_IPC_ChannelReset(ch);

			swtlv_stop(swtlv);

			channel->input_port = cfg->port;
		}
		TE_REG_SetChannelSource(ch, src);

		swtlv_start(swtlv);

		control_input_monitor(channel, true);
	} else {
		swtlv_stop(swtlv);

		/* disable input port */
		TE_REG_SetChannelSource(ch, CH_SRC_DISABLE);

		channel->input_port = LX_TE_INPUT_PORT_NONE;

		control_input_monitor(channel, false);
	}

	return 0;
}
#else
void arib2_swtlv_register_data_callback(struct arib2_channel *channel,
					swtlv_cb_func_t func, void *arg)
{
}
static inline int swtlv_suspend(struct arib2_device *dev)
{
	return 0;
}
static inline int swtlv_resume(struct arib2_device *dev)
{
	return 0;
}
static inline int swtlv_init_ioc_pkt_data(struct arib2_channel *channel,
					  struct arib2_dump_fh *df)
{
	return 0;
}
static inline void swtlv_release_ioc_pkt_data(struct arib2_channel *channel,
					      struct arib2_dump_fh *df)
{
}
static inline int swtlv_config_channel_input(struct arib2_channel *channel,
					     LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg)
{
	return 0;
}
static inline void swtlv_init(struct arib2_channel *channel)
{
}
#endif
/*--------------------------- SWTLV END --------------------------------*/

static void irq_handler(struct arib2_channel *channel, u32 val)
{
	struct arib2_input_dump *dump;
	u8 ch = channel->num;
	u32 data_full, meta_full;
#define CHANNEL_INTR_BITS(i)				\
	((DUMPER_INTR_META_WRITE_CH0<<(i))	|	\
	(DUMPER_INTR_META_AL_FULL_CH0<<(i))	|	\
	(DUMPER_INTR_DATA_UNIT_BUF_CH0<<(i))	|	\
	(DUMPER_INTR_DATA_AL_FULL_CH0<<(i)))

	if (!(val & CHANNEL_INTR_BITS(ch)))
		return;

	data_full = DUMPER_INTR_DATA_AL_FULL_CH0;
	meta_full = DUMPER_INTR_META_AL_FULL_CH0;

	if (val & (meta_full << ch)) {
		te_reg_dumper_set_intr_enable((meta_full << ch), false);
		log_noti("CH[%d] META ALMOST FULL IRQ\n", ch);
	}

	if (val & (data_full << ch)) {
		u64 time = channel->data.last_read_time;
		u32 nsec = do_div(time, USEC_PER_SEC);

		te_reg_dumper_set_intr_enable((data_full << ch), false);
		log_noti("CH[%d] DATA ALMOST FULL IRQ(%llu.%06usec)\n",
			 ch, time, nsec);
	}

	dump = &channel->dump;

	spin_lock(&dump->spinlock);
	if (dump->state == INPUT_DUMP_STATE_RUNNING) {
		if (val & (meta_full << ch)) {
			te_hwbuf_set_error(dump->meta, -ENOBUFS);
		}

		if (val & (data_full << ch)) {
			channel->data.stat.overflow_count++;
			te_hwbuf_set_error(dump->data, -ENOBUFS);
		}
		process_input_data(dump);
	}
	spin_unlock(&dump->spinlock);

}

void arib2_io_irq_handler(struct arib2_device *dev, u32 val)
{
	int i;

	for (i = 0; i < dev->num_channel; i++)
		irq_handler(&dev->channels[i], val);

}

/*--------------------------- IOCTL START --------------------------------*/

static int config_channel_input(struct arib2_channel *channel,
				LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg)
{
	u8 ch;
	enum te_reg_channel_src src;

	log_noti("ch %u, port: %s -> %s, enable: %d, reset: %d",
		 channel->num, te_input_port_to_str(channel->input_port),
		 te_input_port_to_str(cfg->port), cfg->enable, cfg->reset);

	ch = channel->num;
	src = te_input_port_to_reg_ch_src(cfg->port);
	if (src == CH_SRC_INVALID) {
		log_error("Invalid input port:[%d]\n", cfg->port);
		return -EINVAL;
	}

	log_noti("arib2_src: %s", te_ch_src_type_to_str(src));

	if (cfg->enable) {
		if (cfg->reset || channel->input_port != cfg->port) {
			/* reset input port if input source is changed */
			TE_REG_SetEngineChannelSource(ch, CH_SRC_DISABLE);

			reset_input_dump(channel);

			channel->input_port = cfg->port;
		}

		TE_REG_SetEngineChannelSource(ch, src);

		control_input_monitor(channel, true);

	} else {
		/* disable input port */
		TE_REG_SetEngineChannelSource(ch, CH_SRC_DISABLE);

		channel->input_port = LX_TE_INPUT_PORT_NONE;

		control_input_monitor(channel, false);
	}

	return 0;
}

int arib2_config_channel_input(struct arib2_channel *channel,
			       LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg)
{
	int ret;

	mutex_lock(&io_mutex);
	ret = config_channel_input(channel, cfg);
	mutex_unlock(&io_mutex);

	return ret;
}

unsigned int arib2_wait_data(struct arib2_channel *channel,
			     struct file *file, struct poll_table_struct *wait)
{
	struct te_pktbuf *pbuf;
	struct arib2_data *arib2_data;
	int size;
	unsigned int mask = 0;

	arib2_data = &channel->data;

	if (arib2_data->start == false) {
		log_debug("dump is stopped");
		return POLLERR;
	}
	pbuf = &arib2_data->pbuf;

	poll_wait(file, te_pktbuf_wq(pbuf), wait);
	if (te_pktbuf_error(pbuf)) {
		/* not set POLLERR here
		   for process error handling at arib2_read_data. */
		mask |= (POLLIN | POLLRDNORM | POLLPRI);
	} else {
		size = te_pktbuf_next_packet_size(pbuf);
		if (size > 0) {
			mask |= (POLLIN | POLLRDNORM | POLLPRI);
		}
	}

	return mask;
}

static void process_input_stream(struct arib2_channel *channel)
{
	struct arib2_input_dump *d;
	struct te_pktbuf *pbuf;
	struct te_hwbuf *m_hbuf, *d_hbuf;
	u8 *hdr;
	u32 tlv_len;
	u32 p;
	int rc;

	d = &channel->dump;
	d_hbuf = d->data;
	m_hbuf = d->meta;

	pbuf = &channel->data.pbuf;

	while (te_hwbuf_avail_size(m_hbuf)) {
		if (d->state != INPUT_DUMP_STATE_RUNNING)
			return;

		te_hwbuf_raw_peek(m_hbuf, 0, (void *)&p, 4);
		rc = te_hwbuf_error(d_hbuf); /* err is set in irq_handler */
		if (rc) {
			/* if hwbuffer overflowed, pktbuffer must be overflowed.
			   always set error becuase it needs to wake up poll_wait */
			te_pktbuf_set_error(pbuf, -ENOBUFS);

			tlv_len = 0;
			goto next;
		}

		te_hwbuf_get_paddr_cont_rbuf(d_hbuf, p, TLV_TIMESTAMP_SIZE,
					     TLV_HDR_SIZE, (void **)&hdr);
		if (hdr[0] != TLV_SYNCBYTE) {
			log_debug("(ch:%u)[syncbyte error] %08x",
				  channel->num, *(u32 *)hdr);
			channel->data.stat.err_packet_count++;

			tlv_len = 0;
			goto next;
		}

		tlv_len = TE_GET16(&hdr[2]) + TLV_HDR_SIZE;
		if (tlv_len > TLV_MAX_DATA_SIZE) {
			log_debug("(ch:%u)[length error] %08x",
				  channel->num, *(u32 *)hdr);
			channel->data.stat.err_packet_count++;
			goto next;
		}

		debug_raw_callback(channel, d_hbuf, p,
				   TLV_TIMESTAMP_SIZE + tlv_len);
		te_pktbuf_add_packet(pbuf, hdr, tlv_len);
next:
		te_hwbuf_read_skip(m_hbuf, META_SIZE);

		channel->data.stat.packet_count++;
		channel->data.stat.total_length += tlv_len;
	}
}

static void data_callback_work(struct work_struct *work)
{
	int rc;
	struct arib2_input_dump *dump;
	struct arib2_channel *channel;
	u32 ptr, free_size, size;

	channel = container_of(work, struct arib2_channel, dump.work);
	dump = &channel->dump;
	if (dump->state != INPUT_DUMP_STATE_RUNNING)
		return;

	free_size = te_hwbuf_free_size(dump->data);
	if (free_size < dump->warning_size) {
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

	te_reg_dumper_get_meta_wptr(dump->ch, &ptr);
	rc = te_hwbuf_set_wptr(dump->meta, ptr);
	if (rc == -EOVERFLOW)
		te_hwbuf_set_error(dump->meta, -ENOBUFS);

	te_reg_dumper_get_data_wptr(dump->ch, &ptr);
	rc = te_hwbuf_set_wptr(dump->data, ptr);
	if (rc == -EOVERFLOW)
		te_hwbuf_set_error(dump->data, -ENOBUFS);

	process_input_stream(channel);
}

struct arib2_input_dump *arib2_start_input_dump(struct arib2_channel *channel,
						struct arib2_dump_cfg *cfg)
{
	struct arib2_input_dump *dump;
	int ret;

	log_noti("%s(%u)", __func__, channel->num);

	mutex_lock(&io_mutex);

	ret = init_pkt_data(channel, cfg->data, TE_BUF_FLAG_MANUAL_IDX);
	if (ret) {
		log_error("init_pkt_data failed");
		goto error;
	}
	dump = start_input_dump(channel, cfg);

	mutex_unlock(&io_mutex);

	return dump;
error:
	mutex_unlock(&io_mutex);

	return NULL;
}

int arib2_stop_input_dump(struct arib2_input_dump *dev)
{
	struct arib2_channel *channel;
	int rc;

	channel = container_of(dev, struct arib2_channel, dump);

	mutex_lock(&io_mutex);

	rc = stop_input_dump(dev);
	release_pkt_data(channel);

	mutex_unlock(&io_mutex);

	return rc;
}

static void release_ioc_inputdump_data(struct arib2_channel *channel,
				       struct arib2_dump_fh *df)
{
	phys_addr_t addr;

	addr = te_hwbuf_addr(&df->data);
	te_hwbuf_release(&df->data);
	hma_free(TE_MEM_SHARED_NAME, addr);

	addr = te_hwbuf_addr(&df->meta);
	te_hwbuf_release(&df->meta);
	hma_free(TE_MEM_SHARED_NAME, addr);

}

static int init_ioc_inputdump_data(struct arib2_dump_fh *df)
{
	phys_addr_t data, meta;
	int rc;
	int size, unit_size, flag;

#define DATA_SIZE_PER_META		1024

#define INPUT_DUMP_DATA_SIZE		(12*1024*1024)
#define INPUT_DUMP_DATA_UNIT_SIZE	(384*1024)
#define INPUT_DUMP_META_SIZE		((INPUT_DUMP_DATA_SIZE/DATA_SIZE_PER_META) * META_SIZE)
#define INPUT_DUMP_META_UNIT_SIZE	0

	flag = TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP_CACHED;
	size = INPUT_DUMP_DATA_SIZE;
	unit_size = INPUT_DUMP_DATA_UNIT_SIZE;
	if (unit_size != 0 && size % unit_size)
		size = (size / unit_size) * unit_size;

	data = hma_alloc_user(TE_MEM_SHARED_NAME, size, 4096, "arib2_data");
	CHECK_ERROR(!data, return -ENOMEM, "hma_alloc fail");

	rc = te_hwbuf_init(&df->data, data, size, unit_size, flag);
	CHECK_ERROR(rc < 0, goto err_data_init, "Error in te_hwbuf_init");

	flag = TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP;
	size = INPUT_DUMP_META_SIZE;
	unit_size = INPUT_DUMP_META_UNIT_SIZE;
	if (unit_size != 0 && size % unit_size)
		size = (size / unit_size) * unit_size;

	meta = hma_alloc_user(TE_MEM_SHARED_NAME, size, 4096, "arib2_meta");
	CHECK_ERROR(!meta, goto err_meta_alloc, "hma_alloc fail");

	rc = te_hwbuf_init(&df->meta, meta, size, unit_size, flag);
	CHECK_ERROR(rc < 0, goto err_meta_init, "Error in te_hwbuf_init");

	return 0;

err_meta_init:
	hma_free(TE_MEM_SHARED_NAME, meta);
err_meta_alloc:
	te_hwbuf_release(&df->data);
err_data_init:
	hma_free(TE_MEM_SHARED_NAME, data);

	return -EIO;
}

//TODO: rename
static void _ioc_stop_input_dump(struct arib2_fh *fh)
{
	struct arib2_dump_fh *df = fh->dump;
	struct arib2_channel *channel;

	if (df) {
		channel = fh->channel;

		if (fh->dev->use_swtlv) {
			swtlv_release_ioc_pkt_data(channel, df);
		} else {
			stop_input_dump(df->input_dump);

			release_ioc_inputdump_data(channel, df);
			release_pkt_data(channel);
		}
		fh->dump = NULL;
		kfree(df);
	}
}

static int ioc_config_channel_input(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg = arg;
	int ret;

	if (fh->dev->use_swtlv) {
		ret = swtlv_config_channel_input(fh->channel, cfg);
		CHECK_ERROR(ret, return ret,
			    "Error in swtlv_config_channel_input");
	} else {
		ret = config_channel_input(fh->channel, cfg);
		CHECK_ERROR(ret, return ret, "Error in config_channel_input");
	}

	return 0;
}

static int ioc_set_timeout(struct arib2_fh *fh, void *arg)
{
	u32 timeout = *(u32 *)arg;

	fh->channel->data.timeout = timeout;	// TODO: adjust to all device node?

	return 0;
}

static int ioc_start_input_dump(struct arib2_fh *fh, void *arg)
{
	struct arib2_dump_fh *df = NULL;
	struct arib2_channel *channel = fh->channel;
	int ret;

	log_noti("%s", __func__);

	CHECK_PARAM(fh->dump, "input dump is already started");

	df = kzalloc(sizeof(*df), GFP_KERNEL);
	CHECK_ERROR(!df, return -ENOMEM, "no memory");

	if (fh->dev->use_swtlv) {
		ret = swtlv_init_ioc_pkt_data(channel, df);
		CHECK_ERROR(ret != 0, goto err_init,
			    "Error in swtlv_init_inputdump_data");

	} else {
		struct arib2_dump_cfg cfg;

		ret = init_ioc_inputdump_data(df);
		CHECK_ERROR(ret != 0, goto err_init,
			    "Error in init_ioc_inputdump_data");

		ret = init_pkt_data(channel, &df->data, TE_BUF_FLAG_MANUAL_IDX);
		CHECK_ERROR(ret != 0, goto err_pkt_init,
			    "Error in init_pkt_data");

		cfg.mode = DUMPER_MODE_TLV;
		cfg.data = &df->data;
		cfg.meta = &df->meta;
		cfg.flags = ARIB2_DUMP_FLAG_WORKQUEUE;

		df->input_dump = start_input_dump(channel, &cfg);
		CHECK_ERROR(!df->input_dump, goto err_start,
			    "Error in start_input_dump");
	}

	fh->dump = df;

	return 0;

err_start:
	release_pkt_data(channel);
err_pkt_init:
	release_ioc_inputdump_data(channel, df);
err_init:
	kfree(df);

	return ret;
}

static int ioc_stop_input_dump(struct arib2_fh *fh, void *arg)
{
	log_noti("%s", __func__);

	CHECK_ERROR(!fh->dump, return -EINVAL, "InputDump is not started");

	_ioc_stop_input_dump(fh);

	return 0;
}

/*--------------------------- IOCTL END --------------------------------------*/

/*--------------------------- DEBUG START ------------------------------------*/

#define dprintf(fmt, args...) seq_printf(m, fmt, ##args)

static u32 debug_input_mtime = 500;	/* ms unit - measuring time */

enum {
	DEBUG_ID_INPUT = 0,
	DEBUG_IO_ID_DUMP,
};

#ifdef SUPPORT_SWTLV_FUNC
static void swtlv_debug_raw_callback(struct arib2_swtlv *swtlv, u32 size)
{
	struct arib2_debug_dump *dump;
	struct arib2_channel *channel = swtlv_to_arib2_channel(swtlv);

	dump = &channel->debug_dump[TE_DUMP_MODE_RAW];

	mutex_lock(&debug_mutex);
	if (dump->running && te_hwbuf_error(dump->buf) == 0) {
		int rc;
		void *buf[2];
		u32 len[2];

		te_hwbuf_raw_get_rbuf2(&swtlv->dump.hbuf, 0, size,
				       &buf[0], &len[0], &buf[1], &len[1]);

		rc = te_hwbuf_cwrite2(dump->buf, buf[0], len[0],
				      buf[1], len[1]);
		if (rc < 0) {
			te_hwbuf_set_error(dump->buf, rc);
		}
	}
	mutex_unlock(&debug_mutex);
}
#endif

static void debug_raw_callback(struct arib2_channel *channel,
			       struct te_hwbuf *hbuf, u32 paddr, u32 size)
{
	struct arib2_debug_dump *dump;

	dump = &channel->debug_dump[TE_DUMP_MODE_RAW];

	mutex_lock(&debug_mutex);

	if (dump->running && te_hwbuf_error(dump->buf) == 0) {
		int rc;
		void *buf[2];
		u32 len[2];

		te_hwbuf_get_paddr_buf2(hbuf, paddr, 0, size, &buf[0],
					&len[0], &buf[1], &len[1]);

		rc = te_hwbuf_cwrite2(dump->buf, buf[0], len[0],
				      buf[1], len[1]);
		if (rc < 0) {
			te_hwbuf_set_error(dump->buf, rc);
		}
	}
	mutex_unlock(&debug_mutex);
}

void arib2_debug_user_read_callback(struct arib2_channel *channel,
				    void __user *data, u32 size)
{
	struct arib2_debug_dump *dump = &channel->debug_dump[TE_DUMP_MODE_USER];

	mutex_lock(&debug_mutex);
	if (dump->running) {
		int rc;
		rc = te_hwbuf_cwrite_user(dump->buf, data, size);

		if (rc < 0)
			te_hwbuf_set_error(dump->buf, rc);
	}
	mutex_unlock(&debug_mutex);
}

static int debug_dump_start(struct te_dump_device *dev,
			    struct te_dump_handle *h, struct te_dump_cfg *cfg)
{
	int rc;
	struct arib2_device *adev = dev->private;
	LX_ARIB2_CHANNEL_INPUT_CFG_T channel_cfg;
	struct arib2_debug_dump *dump;
	enum te_dumper_mode dumper;
	enum te_dump_mode mode = cfg->mode;
	struct arib2_channel *channel = arib2_get_channel(adev, cfg->ch);

	CHECK_PARAM(!channel, "invalid channel(%d)", cfg->ch);
	CHECK_PARAM(mode >= TE_DUMP_MODE_MAX, "invalid mode(%d)", mode);

	log_noti("%s (mode:%d) ", __func__, mode);

	dumper = te_dumper_get_mode(get_te_device(adev));
	if (dumper != TE_DUMPER_MODE_ARIB2) {
		log_error("not arib2 dumper mode\n");
		return -EPERM;
	}

	dump = &channel->debug_dump[mode];

	mutex_lock(&io_mutex);

	if (dump->running) {
		log_error("already running");
		rc = -EBUSY;
		goto exit;
	}

	if (adev->use_swtlv) {
		/* Channel Configuration */
		if (mode == TE_DUMP_MODE_INPUT &&
		    cfg->port != LX_TE_INPUT_PORT_BYPASS) {

			channel_cfg.port = cfg->port;

			if (cfg->port == LX_TE_INPUT_PORT_NONE) {
				channel_cfg.reset = false;
				channel_cfg.enable = false;
			} else {
				channel_cfg.reset = true;
				channel_cfg.enable = true;
			}
			rc = swtlv_config_channel_input(channel, &channel_cfg);
			CHECK_ERROR(rc != 0, goto exit,
				    "Error on config channel input[%u]",
				    channel->num);
		}
	} else {
		if (mode == TE_DUMP_MODE_INPUT &&
		    cfg->port != LX_TE_INPUT_PORT_BYPASS) {
			channel_cfg.port = cfg->port;

			if (cfg->port == LX_TE_INPUT_PORT_NONE) {
				channel_cfg.reset = false;
				channel_cfg.enable = false;
			} else {
				channel_cfg.reset = true;
				channel_cfg.enable = true;
			}

			/* Channel Configuration */
			rc = config_channel_input(channel, &channel_cfg);
			CHECK_ERROR(rc, goto exit,
				    "Error on config channel input[%u]",
				    channel->num);
		}

		// TODO: make a function
		if (mode == TE_DUMP_MODE_INPUT) {
			struct arib2_dump_cfg param;

			param.mode = cfg->arib2.mode;
			param.data = cfg->data;
			param.meta = cfg->meta;
			param.flags = 0;

			dump->dev = start_input_dump(channel, &param);
			if (!dump->dev) {
				log_error("Err in start_input_dump");
				rc = -EIO;
				goto exit;
			}
		}
	}

	dump->buf = cfg->data;
	dump->running = true;

	h->dev_handle = dump;

	rc = 0;

exit:
	mutex_unlock(&io_mutex);

	return rc;
}

static void debug_dump_stop(struct te_dump_device *dev,
			    struct te_dump_handle *h)
{
	if (h->dev_handle) {

		struct arib2_device *adev = dev->private;
		struct arib2_debug_dump *dump = h->dev_handle;

		log_noti("%s(mode:%d)", __func__, dump->mode);

		mutex_lock(&debug_mutex);
		dump->running = false;
		mutex_unlock(&debug_mutex);

		mutex_lock(&io_mutex);
		if (!adev->use_swtlv && dump->mode == TE_DUMP_MODE_INPUT) {
			stop_input_dump(dump->dev);
		}
		mutex_unlock(&io_mutex);
	}
}

static int debug_show_input_status(struct arib2_device *dev, struct seq_file *m)
{
	struct channel_input_status *status;
	struct te_dumper_status *dumper_status = NULL;
	struct arib2_channel *channel;
	struct te_io_cfg *io_cfg = te_get_io_config();
	struct te_device *tdev = get_te_device(dev);
	u32 mtime = debug_input_mtime;
	int i;

	status = kcalloc(dev->num_channel, sizeof(*status), GFP_KERNEL);
	if (!status)
		return -ENOMEM;

	for (i = 0; i < dev->num_channel; i++)
		get_channel_input_status(&dev->channels[i], &status[i]);

	if (io_cfg->num_dumper) {
		dumper_status = te_debug_get_dumper_status(tdev);
		if (IS_ERR(dumper_status)) {
			kfree(status);
			return PTR_ERR(dumper_status);
		}
	}

	msleep(mtime);

	dprintf("Channel Input Status\n");
	dprintf("%3s %12s %12s   %8s %8s %17s %12s\n",
		"Num", "Port", "TPI", "Overflow", "SyncErr", "Packet", "Speed");

	mutex_lock(&io_mutex);
	for (i = 0; i < dev->num_channel; i++) {
		struct channel_input_status s;
		u32 len;
		char *rate;
		enum te_reg_tpi_port tpi;

		channel = &dev->channels[i];

		get_channel_input_status(channel, &s);

		len = (u32)(s.total_length - status[i].total_length);
		rate = get_bitrate_str(len, 1, mtime);
		tpi = te_input_port_to_reg_tpi_port(channel->input_port);

		dprintf("[%d] %12s %12s   %08x %08x %08x/%08x %s\n", i,
			te_input_port_to_str(channel->input_port),
			te_reg_tpi_port_to_str(tpi),
			s.overflow_count, s.err_pkt_count,
			s.pkt_count, status[i].pkt_count, rate);
	}
	mutex_unlock(&io_mutex);
	kfree(status);

	if (io_cfg->num_dumper) {
		dprintf("\n");
		dprintf("Dumper Status\n");
		te_debug_show_dumper_status(tdev, m, dumper_status);
		te_debug_free_dumper_status(dumper_status);
	}

	return 0;
}

static void debug_show_hwbuffer_info(struct te_hwbuf *hbuf, struct seq_file *m)
{
	u32 data, size, avail;

	data = (u32)te_hwbuf_addr(hbuf);
	size = te_hwbuf_size(hbuf);
	avail = te_hwbuf_avail_size(hbuf);

	dprintf("    HWBUF  [%08x++0%x]:%s ", data, size,
		te_get_readable_size(size));
	dprintf("(AVAIL:%s)\n", te_get_readable_size(avail));
}

static void debug_show_pktbuffer_info(struct te_pktbuf *pbuf,
				      struct seq_file *m)
{
	void *data;
	u32 size;
	int avail;

	data = te_pktbuf_data(pbuf);
	size = te_pktbuf_size(pbuf);
	dprintf("    PKTBUF [%p++0%x]:%s ", data, size,
		te_get_readable_size(size));

	avail = te_pktbuf_avail_packet(pbuf);
	if (avail < 0) {
		dprintf("(AVAIL: error - %d)\n", avail);
	} else {
		dprintf("(AVAIL:%s)\n", te_get_readable_size(avail));
	}
}

static void debug_show_channel_dump(struct arib2_channel *channel,
				    struct seq_file *m)
{
	struct te_hwbuf *hbuf;
	struct arib2_data *arib2_data = &channel->data;
	struct te_pktbuf *pbuf = &arib2_data->pbuf;

	mutex_lock(&io_mutex);
	if (channel->dev->use_swtlv) {
		struct arib2_swtlv *swtlv = &channel->swtlv;

		dprintf("[%u] %s(sync:%s)\n", channel->num,
			(swtlv->status == SWTLV_STATUS_IDLE) ? "IDLE" :
			(swtlv->status == SWTLV_STATUS_RUNNING ?
			 "RUNNING" : "SUSPEND"),
			(swtlv->sync == false ? "LOST" : "FOUND"));

		if (swtlv->status != SWTLV_STATUS_RUNNING)
			goto exit;

		hbuf = &swtlv->dump.hbuf;
	} else {
		struct arib2_input_dump *d = &channel->dump;

		dprintf("[%u] %s\n", channel->num,
			(d->state == INPUT_DUMP_STATE_IDLE) ? "IDLE" :
			(d->state == INPUT_DUMP_STATE_RUNNING ?
			 "RUNNING" : "SUSPEND"));

		if (d->state != INPUT_DUMP_STATE_RUNNING)
			goto exit;

		hbuf = d->data;
	}
	dprintf("TOTAL: %d, ERROR: %d, OVERFLOW:%d\n",
		arib2_data->stat.packet_count,
		arib2_data->stat.err_packet_count,
		arib2_data->stat.overflow_count);

	debug_show_hwbuffer_info(hbuf, m);
	debug_show_pktbuffer_info(pbuf, m);

exit:
	mutex_unlock(&io_mutex);
}

static int debug_show_dump_status(struct arib2_device *dev, struct seq_file *m)
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

static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct arib2_channel *channel = item->private;

	switch (item->flags) {
	case DEBUG_ID_INPUT:
		mutex_lock(&io_mutex);
		dprintf("%s\n", te_input_port_to_str(channel->input_port));
		mutex_unlock(&io_mutex);
		break;

	case DEBUG_IO_ID_DUMP:
		debug_show_channel_dump(channel, m);
		break;
	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_set_channel_input(struct arib2_channel *channel, char *name)
{
	int ret;
	struct lx_arib2_channel_input_cfg cfg;

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

static int debug_channel_write(struct te_debug_item *item, char *str)
{
	int ret;
	struct arib2_channel *channel = item->private;

	switch (item->flags) {
	case DEBUG_ID_INPUT:
		ret = debug_set_channel_input(channel, str);
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
	DBGITM_NUM("mtime", &debug_input_mtime),
};

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM_R("dump", &debug_channel_ops, DEBUG_IO_ID_DUMP),
	DBGITM_SIM("input", &debug_channel_ops, DEBUG_ID_INPUT),
};

static struct te_dump_device dump_device = {
	.module = TE_DUMP_MODULE_ARIB2,
	.start = debug_dump_start,
	.stop = debug_dump_stop,
};

static int init_debug(struct arib2_device *dev)
{
	int i, rc;

	dump_device.private = dev;
	rc = te_dump_register_device(&dump_device);
	CHECK_ERROR(rc < 0, return rc, "Error in te_dump_register_device");

	rc = debug_create_item_files(debug_list, dev, dev->debug.dir);
	CHECK_ERROR(rc < 0, return rc, "Err in debug_create_item_files");

	for (i = 0; i < dev->num_channel; i++) {
		struct arib2_channel *c = &dev->channels[i];
		debug_create_item_files(debug_channel_list, c, c->debug_dir);
	}

	arib2_debug_register_status_show(dev, ARIB2_DEBUG_STATUS_INPUT,
					 debug_show_input_status);
	arib2_debug_register_status_show(dev, ARIB2_DEBUG_STATUS_DUMP,
					 debug_show_dump_status);

	return rc;
}

static void release_debug(struct arib2_device *dev)
{

}

/*--------------------------- DEBUG END --------------------------------------*/

static int io_suspend(struct arib2_device *dev)
{
	struct arib2_channel *channel;
	struct arib2_input_dump *dump;
	unsigned long flag;
	int i;

	log_noti("%s", __func__);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		dump = &channel->dump;
		if (dump->state == INPUT_DUMP_STATE_RUNNING) {
			spin_lock_irqsave(&dump->spinlock, flag);
			dump->state = INPUT_DUMP_STATE_SUSPEND;
			spin_unlock_irqrestore(&dump->spinlock, flag);
			stop_input_dump_dev(dump);
		}
	}
	return 0;
}

static int resume_input_dump(struct arib2_input_dump *dump)
{
	log_noti("%s", __func__);

	start_input_dump_dev(dump);

	dump->state = INPUT_DUMP_STATE_RUNNING;

	return 0;
}

static int io_resume(struct arib2_device *dev)
{
	struct arib2_channel *channel;
	struct arib2_input_dump *dump;
	LX_ARIB2_CHANNEL_INPUT_CFG_T cfg;
	int rc, i;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		cfg.port = channel->input_port;

		if (cfg.port != LX_TE_INPUT_PORT_NONE) {
			cfg.enable = true;
			cfg.reset = true;

			rc = config_channel_input(channel, &cfg);
			CHECK_ERROR(rc != 0,,
				    "Error(%d) in config_channel_input", rc);
		}

		dump = &channel->dump;
		if (dump->state == INPUT_DUMP_STATE_SUSPEND)
			resume_input_dump(dump);
	}

	return 0;
}

static void init_input_dump(struct arib2_channel *channel)
{
	struct arib2_input_dump *dump = &channel->dump;

	INIT_WORK(&dump->work, data_callback_work);
	spin_lock_init(&dump->spinlock);

	dump->ch = channel->num;
	dump->state = INPUT_DUMP_STATE_IDLE;
}

static void init_debug_dump(struct arib2_channel *channel)
{
	int i;

	for (i = 0; i < TE_DUMP_MODE_MAX; i++) {
		channel->debug_dump[i].mode = i;
	}
}

static const struct arib2_ioctl_info ioctls[] = {
	IOC_INFO(ARIB2_IOC_CFG_CHANNEL_INPUT, ioc_config_channel_input),
	IOC_INFO(ARIB2_IOC_SET_TIMEOUT, ioc_set_timeout),
	IOC_INFO(ARIB2_IOC_DUMP_START, ioc_start_input_dump),
	IOC_INFO(ARIB2_IOC_DUMP_STOP, ioc_stop_input_dump),
};

static int io_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	return arib2_do_ioctl(priv, cmd, arg, io_mutex, ioctls);
}

static int io_dev_init(struct arib2_device *dev)
{
	int ret, i;
	struct arib2_channel *channel;

	log_noti("%s", __func__);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		mutex_init(&channel->data.mutex);
		channel->data.timeout = 0;	/* default timeout: NO WAIT */

		if (dev->use_swtlv) {
			swtlv_init(channel);
		} else {
			init_input_dump(channel);
		}

		init_debug_dump(channel);
	}
	ret = init_input_monitor(dev);
	CHECK_ERROR(ret, return ret, "Error in init_input_monitor");

	ret = init_debug(dev);
	CHECK_ERROR(ret, return ret, "Error in init_debug");

	return 0;
}

static void io_dev_release(struct arib2_device *dev)
{
	log_noti("%s", __func__);

	release_debug(dev);

	te_del_timer(dev->monitor_timer);
}

static void io_dev_close(struct arib2_fh *fh)
{
	log_noti("%s", __func__);

	if (!fh->channel)
		return;

	_ioc_stop_input_dump(fh);
}

static int io_dev_suspend(struct arib2_device *dev)
{
	int ret;

	if (dev->use_swtlv)
		ret = swtlv_suspend(dev);
	else
		ret = io_suspend(dev);

	return ret;
}

static int io_dev_resume(struct arib2_device *dev)
{
	int ret;

	if (dev->use_swtlv)
		ret = swtlv_resume(dev);
	else
		ret = io_resume(dev);

	return ret;
}

static const struct arib2_ioctl ioctl_io = {
	.magic = ARIB2_IOC_IO_MAGIC,
	.func = io_dev_ioctl,
};

const struct arib2_sub_driver arib2_io_driver = {
	.name = "arib2_io",
	.init = io_dev_init,
	.release = io_dev_release,
	.suspend = io_dev_suspend,
	.resume = io_dev_resume,

	.close = io_dev_close,
	.ioctl = &ioctl_io,
};
