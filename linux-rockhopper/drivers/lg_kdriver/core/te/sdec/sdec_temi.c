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
 *  sdec driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date	2019-05-31
 *  @note	Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "sdec_impl.h"


#define TS_PACKET_SIZE		188

#define TEMI_BUFFER_SIZE	(TS_PACKET_SIZE * 512)
#define TEMI_UNIT_SIZE		(TS_PACKET_SIZE * 10)
#define TEMI_OVERFLOW_SIZE	(TEMI_UNIT_SIZE * 3)

#define TEMI_PES_LEN		14

#define log_ferr(f,fmt,args...) \
  log_error("CH[%d] IDX[%d] - " fmt, (f)->channel->num, (f)->idx, ##args)

enum temi_state {
	TEMI_STATE_FREE = 0,
	TEMI_STATE_READY,
	TEMI_STATE_GO,
	TEMI_STATE_DONE,
};

#define MAX_TIMELINE_DESC_CNT	4
#define MAX_TIMELINE_DESC_SIZE	64

struct timeline_descriptor {
	u8 buf[MAX_TIMELINE_DESC_SIZE];
	u8 len;
};

struct temi_pes {
	u8 buf[TEMI_PES_LEN];
	u8 offset;
};

struct temi_data {
	enum temi_state state;
	struct timeline_descriptor desc[MAX_TIMELINE_DESC_CNT];
	u32 desc_count;
	struct temi_pes pes;
	u64 pts;
};

struct temi_dev {
	enum temi_state state;
	struct sdec_channel *channel;
	u8 idx;			/* hw index */
	u8 req_num;
	u16 pid;

	spinlock_t lock;
	struct mutex mutex;
	struct work_struct cb_work;

	struct te_hwbuf hbuf; /* TS packet buffer for mcu */
	struct temi_data *data;

	/* List of struct sdec_temi_filter to process data */
	struct list_head filters;

	/* List entry in struct sdec_temi_channel::dev_list */
	struct list_head list;

	u32 errors;
};

struct sdec_temi_filter {
	enum temi_state state;
	struct sdec_channel *channel;
	u16 idx;
	u16 pid;

	struct temi_dev *dev;
	/* List entry in struct temi_dev::filters */
	struct list_head dev_entry;

	/* List entry in struct sdec_filter_channel::temi_list */
	struct list_head list;

	void *priv;
	bool oneshot;
	u32 count;
	struct sdec_temi_filter_pattern pattern;
	sdec_temi_filter_callback_t callback;
};


struct temi_callback {
	struct sdec_channel *channel;
	IPC_MSG_TEMI_DATA_T temi;
};


#define get_dev_temi_from_channel(c)	(&(c)->dev->temi)


static int max_log_cnt = 5;
module_param_named(sdec_temi_log_cnt, max_log_cnt, int, 0644);

static DEFINE_MUTEX(temi_mutex);

static const char *temi_state_str(enum temi_state state)
{
	const struct te_val_str list[] = {
		{TEMI_STATE_FREE, "FREE"},
		{TEMI_STATE_READY, "READY"},
		{TEMI_STATE_GO, "GO"},
		{TEMI_STATE_DONE, "DONE"},
	};

	return find_match_string(list, state, "INVALID");
}

static void reset_temi_data(struct temi_data *data)
{
	data->desc_count = 0;
	data->state = TEMI_STATE_FREE;
}

static int ipc_request_temi_filter(struct temi_dev *dev)
{
	int ret;
	u32 addr, size;
	IPC_ADAP_FILTER_REQUEST_T req;

#ifdef CONFIG_PHYS_ADDR_T_64BIT
	if (te_hwbuf_addr(&dev->hbuf) > U32_MAX) {
		log_error("addr(%llx) over 32bit\n", te_hwbuf_addr(&dev->hbuf));
		return -EINVAL;
	}
	addr = (u32)te_hwbuf_addr(&dev->hbuf);
#else
	addr = te_hwbuf_addr(&dev->hbuf);
#endif
	size = te_hwbuf_size(&dev->hbuf);

	memset(&req, 0, sizeof(req));

	req.flt_idx = dev->idx;
	req.req_num = dev->req_num;
	req.pid = dev->pid;
	req.gpb_saddr = addr;
	req.gpb_eaddr = (addr + size);
	req.unit_size = TEMI_UNIT_SIZE;

	ret = te_ipc_request_temi_filter(dev->channel->num, &req);
	if (ret < 0) {
		log_error("te_ipc_request_temi failed[%d]", ret);
		return ret;
	}

	return 0;
}

static struct temi_dev *temi_dev_alloc(struct sdec_channel *channel, u16 pid)
{
	int i;
	struct temi_dev *dev;
	struct sdec_dev_temi *tdev = get_dev_temi_from_channel(channel);

	for (i = 0; i < tdev->num_dev; i++) {
		dev = &tdev->dev[i];
		if (dev->state == TEMI_STATE_FREE)
			break;
	}

	if (i == tdev->num_dev) {
		log_error("CH[%d] - no free temi device\n", channel->num);
		return NULL;
	}

	dev->channel = channel;
	dev->idx = i;
	dev->req_num = channel->temi.seq_num++;
	dev->pid = pid;
	dev->errors = 0;
	dev->state = TEMI_STATE_READY;

	INIT_LIST_HEAD(&dev->filters);

	list_add_tail(&dev->list, &channel->temi.dev_list);

	return dev;
}

static struct temi_dev *temi_dev_get_from_pid(struct sdec_channel *channel,
					      u16 pid)
{
	struct temi_dev *dev;

	list_for_each_entry(dev, &channel->temi.dev_list, list) {
		if (dev->pid == pid)
			return dev;
	}

	return NULL;
}

static int temi_dev_request(struct temi_dev *dev)
{
	int ret;
	te_phys_addr_t addr;
	u32 size = TEMI_BUFFER_SIZE;
	struct sdec_dev_temi *tdev = get_dev_temi_from_channel(dev->channel);

	if (dev->state == TEMI_STATE_GO) {
		log_error("temi dev(%d) is busy\n", dev->idx);
		return -EBUSY;
	}

	/* mem open & alloc for mcu use */
	addr = te_mem_alloc(tdev->mem, size, "temi_buffer");
	if (!addr) {
		ret = -EIO;
		goto err_alloc_buf;
	}

	dev->data = vmalloc(sizeof(*dev->data));
	if (!dev->data) {
		ret = -ENOMEM;
		goto err_alloc_temi;
	}

	reset_temi_data(dev->data);

	ret = te_hwbuf_init(&dev->hbuf, addr, size, 0,
			    TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP_CACHED);
	if (ret) {
		log_error("te_hwbuf_init failed(%d)", ret);
		goto err_hwbuf;
	}

	ret = ipc_request_temi_filter(dev);
	if (ret) {
		log_error("ipc_request_temi_filter failed(%d)", ret);
		goto err_request;
	}
	dev->state = TEMI_STATE_GO;

	return 0;

err_request:
	te_hwbuf_release(&dev->hbuf);
err_hwbuf:
	vfree(dev->data);
err_alloc_temi:
	te_mem_free(tdev->mem, addr);
err_alloc_buf:
	return ret;
}

static int temi_dev_cancel(struct temi_dev *dev)
{
	int ret;
	te_phys_addr_t addr;
	unsigned long flags;
	struct sdec_dev_temi *tdev = get_dev_temi_from_channel(dev->channel);

	if (dev->state != TEMI_STATE_GO)
		return 0;

	ret = te_ipc_cancel_temi_filter(dev->channel->num, dev->idx);
	if (ret) {
		log_error("te_ipc_cancel_temi_filter(%d,%d) failed(%d)",
			  dev->channel->num, dev->idx, ret);
	}

	// add spinlock to sync with ipc callback
	spin_lock_irqsave(&dev->lock, flags);
	dev->state = TEMI_STATE_DONE;
	spin_unlock_irqrestore(&dev->lock, flags);

	addr = (te_phys_addr_t)te_hwbuf_addr(&dev->hbuf);

	/* free memory resources */
	te_hwbuf_release(&dev->hbuf);
	vfree(dev->data);
	te_mem_free(tdev->mem, addr);

	return 0;
}

static void temi_dev_free(struct temi_dev *dev)
{
	if (dev->state == TEMI_STATE_GO)
		temi_dev_cancel(dev);

	list_del(&dev->list);
	dev->state = TEMI_STATE_FREE;
}

static int temi_dev_add_filter(struct sdec_temi_filter *f)
{
	int ret;
	struct temi_dev *dev;
	struct sdec_channel *channel = f->channel;

	dev = temi_dev_get_from_pid(channel, f->pid);
	if (!dev) {
		dev = temi_dev_alloc(channel, f->pid);
		if (!dev)
			return -EBUSY;

		ret = temi_dev_request(dev);
		if (ret) {
			temi_dev_free(dev);
			return ret;
		}
	}

	f->dev = dev;

	// sync with callback work
	mutex_lock(&dev->mutex);
	list_add_tail(&f->dev_entry, &dev->filters);
	mutex_unlock(&dev->mutex);

	return 0;
}

static void temi_dev_remove_filter(struct sdec_temi_filter *f)
{
	struct temi_dev *dev = f->dev;

	// remove filter from temi device

	// sync with callback work
	mutex_lock(&dev->mutex);
	list_del(&f->dev_entry);
	mutex_unlock(&dev->mutex);

	f->dev = NULL;

	// free temi_dev if no filter
	if (list_empty(&dev->filters)) {
		temi_dev_free(dev);
	}
}

static struct sdec_temi_filter *alloc_temi_filter(struct sdec_channel *channel)
{
	int i;
	struct sdec_temi_filter *f;
	struct sdec_dev_temi *tdev = get_dev_temi_from_channel(channel);

	for (i = 0; i < tdev->num_filter; i++) {
		f = &tdev->filter[i];
		if (f->state == TEMI_STATE_FREE)
			break;
	}

	if (i == tdev->num_filter) {
		log_error("CH[%d] - no free temi filter\n", channel->num);
		return NULL;
	}

	f->channel = channel;
	f->idx = i;
	f->state = TEMI_STATE_READY;
	f->count = 0;

	list_add_tail(&f->list, &channel->temi.filter_list);

	return f;
}

static int request_temi_filter(struct sdec_temi_filter *f,
			       struct sdec_temi_filter_param *param)
{
	int ret;

	log_temi("request_temi_filter(%d,%d,0x%4x)\n",
		 f->channel->num, f->idx, param->pid);

	f->pid = param->pid;

	f->priv = param->priv;
	f->oneshot = (param->flags & LX_SDEC_SFLT_FLAG_ONESHOT) ? true : false;
	f->pattern = *param->pattern;
	f->callback = param->callback;

	ret = temi_dev_add_filter(f);
	if (ret) {
		log_error("temi_dev_add_filter failed");
		return ret;
	}

	f->state = TEMI_STATE_GO;

	return 0;
}

static void cancel_temi_filter(struct sdec_temi_filter *f)
{
	if (f->state != TEMI_STATE_GO)
		return;

	temi_dev_remove_filter(f);

	f->state = TEMI_STATE_DONE;
}

static void free_temi_filter(struct sdec_temi_filter *f)
{
	cancel_temi_filter(f);

	list_del(&f->list);
	f->state = TEMI_STATE_FREE;
}



int sdec_request_temi_filter(struct sdec_channel *channel,
			     struct sdec_temi_filter_param *param,
			     struct sdec_temi_filter **filter)
{
	int ret;
	struct sdec_temi_filter *f;

	mutex_lock(&temi_mutex);

	f = alloc_temi_filter(channel);
	if (!f) {
		ret = -EBUSY;
		log_error("alloc_temi_filter failed");
		goto err_alloc;
	}

	ret = request_temi_filter(f, param);
	if (ret) {
		log_error("request_temi_filter failed(%d)", ret);
		goto err_req;
	}

	mutex_unlock(&temi_mutex);

	*filter = f;

	return 0;

err_req:
	free_temi_filter(f);
err_alloc:
	mutex_unlock(&temi_mutex);

	return ret;
}

int sdec_cancel_temi_filter(struct sdec_temi_filter *filter)
{
	mutex_lock(&temi_mutex);
	free_temi_filter(filter);
	mutex_unlock(&temi_mutex);

	return 0;
}

/* in isr */
static int ipc_temi_callback(void *msg, void *arg)
{
	int ret;
	u32 size;
	struct sdec_dev_temi *tdev = arg;
	IPC_MSG_TEMI_DATA_T *data = msg;
	bool overflow = false;
	struct temi_dev *dev;

	if (data->idx >= tdev->num_dev) {
		log_warning("invalid idx(%d)\n", data->idx);
		return -EINVAL;
	}

	dev = &tdev->dev[data->idx];

	spin_lock(&dev->lock);

	if (dev->state != TEMI_STATE_GO)
		goto exit;

	if (dev->req_num != data->req_num)
		goto exit;

	ret = te_hwbuf_set_wptr(&dev->hbuf, data->data_eaddr);
	if (ret == -EOVERFLOW) {
		overflow = true;
	} else if (ret < 0) {
		log_ferr(dev, "invalid addr(%08x) buffer(%08x--%08x)",
			 data->data_eaddr, (u32)te_hwbuf_addr(&dev->hbuf),
			 (u32)te_hwbuf_eaddr(&dev->hbuf));
		goto exit;
	} else {
		size = te_hwbuf_free_size(&dev->hbuf);
		if (size < TEMI_OVERFLOW_SIZE)
			overflow = true;
	}

	if (overflow) {
		te_hwbuf_set_error(&dev->hbuf, -ENOBUFS);
	}

	queue_work(system_freezable_wq, &dev->cb_work);

exit:
	spin_unlock(&dev->lock);

	return 0;
}

static bool temi_timeline_match(struct sdec_temi_filter *f, u8 tid)
{
	struct sdec_temi_filter_pattern *p = &f->pattern;
	u8 eqmask, noteqmask;
	u8 xor;

	eqmask = (p->mask) & (~p->noteq);
	noteqmask = (p->mask) & (p->noteq);
	xor = p->val ^ tid;

	if (xor & eqmask)
		return false;

	if (noteqmask && !(xor & noteqmask))
		return false;

	return true;
}


#define LTW_FLAG_BIT				(0x1 << 7)
#define PIECEWISE_RATE_FLAG_BIT			(0x1 << 6)
#define SEAMLESS_SPLICE_FLAG_BIT		(0x1 << 5)
#define AF_DESCRIPTOR_NOT_PRESENT_FLAG_BIT	(0x1 << 4)

/* Parse Adaptation Field Extension for TEMI */
static void parse_af_extension(struct temi_data *data, u8 *b, u8 size)
{
	u8 flags, tag;
	int len, remained;
	struct timeline_descriptor *desc;

	if (data->desc_count == MAX_TIMELINE_DESC_CNT) {
		log_error("over max %d temi found, skip", data->desc_count);
		return;
	}

	// length(1) + flag(1) = 2bytes
	if (size < 2) {
		log_temi("short input size(%d)\n", size);
		return;
	}

	len = b[0];
	if (len == 0 || len >= size) {
		log_temi("invalid length(%d)\n", len);
		return;
	}

	flags = b[1];
	b += 2;
	remained = len - 1;

	if (flags & AF_DESCRIPTOR_NOT_PRESENT_FLAG_BIT)
		return; // no af_descriptor

	len = 0;
	if (flags & LTW_FLAG_BIT)
		len += 2;

	if (flags & PIECEWISE_RATE_FLAG_BIT)
		len += 3;

	if (flags & SEAMLESS_SPLICE_FLAG_BIT)
		len += 5;

	if (len >= remained) {
		return;
	}
	b += len;
	remained -= len;

	while (remained > 1 && data->desc_count < MAX_TIMELINE_DESC_CNT) {
		tag = b[0];
		len = b[1] + 2;	// 2 = tag(1) and length(1) field

		if (len > remained) {//overflow
			log_error("len:%d exceeds max:%d", len, remained);
			return;
		}

		if (tag == 0x04) {	// Timeline Descriptor
			if (len < 5) {
				log_temi("short timeline length(%d)\n", len);
				goto next;
			}

		#ifdef DUMP_DESCRIPTOR
			log_noti("temi_timeline_descriptor\n");
			te_hex_dump(b, len, 1);
		#endif

			if (len > MAX_TIMELINE_DESC_SIZE) {
				log_temi("too huge len:%d", len);
				goto next;
			}

			desc = &data->desc[data->desc_count];
			memcpy(desc->buf, b, len);
			desc->len = len;
			data->desc_count++;
		}

next:
		b += len;
		remained -= len;
	}

	if (data->desc_count) {
		if (data->state == TEMI_STATE_FREE)
			data->state = TEMI_STATE_READY;

		log_temi("%d temi founded", data->desc_count);
	}
}


#define PCR_FLAG_BIT				(0x1 << 4)
#define OPCR_FLAG_BIT				(0x1 << 3)
#define SPLICING_POINT_FLAG_BIT			(0x1 << 2)
#define TRANSPORT_PRIVATE_DATA_FLAG_BIT		(0x1 << 1)
#define ADAPTATION_FIELD_EXTENSION_FLAG_BIT	(0x1 << 0)

/**
 * parse_adaptation_field - Parse adaptation field
 * @maxlen: max number of bytes follwing the adapation_field_length field
 *
 */
static void parse_adaptation_field(struct temi_data *data, u8 *b, u8 maxlen)
{
	u8 flags, len;
	int remained;

	len = b[0];
	if (len > maxlen) {
		log_error("adapatation field length(%d) over max(%d)",
			  len, maxlen);
		return;
	}

	if (!len)
		return;

	flags = b[1];
	b += 2;
	remained = len - 1;

	if (!(flags & ADAPTATION_FIELD_EXTENSION_FLAG_BIT))
		return; //no adataption field extension

	len = 0;
	if (flags & PCR_FLAG_BIT)
		len += 6;
	if (flags & OPCR_FLAG_BIT)
		len += 6;
	if (flags & SPLICING_POINT_FLAG_BIT)
		len += 1;

	if (flags & TRANSPORT_PRIVATE_DATA_FLAG_BIT) {
		// Check remained length to read transport_private_data_length
		if (len >= remained) {
			return;
		}
		b += len;
		remained -= len;

		len = 1 + b[0];
	}

	if (len >= remained) {
		return;
	}

	b += len;
	remained -= len;

	// adapation field extension flag is already checked
	parse_af_extension(data, b, remained);
}


#define STREAM_ID_PRGRAM_MAP		0xBC
#define STREAM_ID_PADDING_STREAM	0xBE
#define STREAM_ID_PRIVATE_STREAM_2	0xBF
#define STREAM_ID_ECM_STREAM		0xF0
#define STREAM_ID_EMM_STREAM		0xF1
#define STREAM_ID_DSMCC_STREAM		0xF2
#define STREAM_ID_ITU_T_H222_TYPE_E	0xF8
#define STREAM_ID_PROGRAM_STREAM_DIR	0xFF

static u8 invalid_stream_ids[] = {
	STREAM_ID_PRGRAM_MAP,
	STREAM_ID_PADDING_STREAM,
	STREAM_ID_PRIVATE_STREAM_2,
	STREAM_ID_ECM_STREAM,
	STREAM_ID_EMM_STREAM,
	STREAM_ID_DSMCC_STREAM,
	STREAM_ID_ITU_T_H222_TYPE_E,
	STREAM_ID_PROGRAM_STREAM_DIR,
};

static bool is_invalid_stream_id(u8 stream_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(invalid_stream_ids); i++) {
		if (stream_id == invalid_stream_ids[i])
			return true;
	}

	return false;
}

static bool get_pts_from_pes(u8 *b, u64 *pts)
{
	u8 flags; //pts_dts_flag
	u8 v; //temp use
	u8 marker[3];
	u32 v_32_30, v_29_15, v_14_0;

	if (b[0] != 0 || b[1] != 0 || b[2] != 1) {
		log_debug("start_code_prefix wrong: 0x%02x%02x%02x",
			  b[0], b[1], b[2]);
		return false;
	}

	if (is_invalid_stream_id(b[3])) {
		log_debug("no PTS in this id :0x%02x", b[3]);
		return false;
	}

	if ( ((b[6] & 0xC0) >> 6) != 0x02) {
		log_debug("not '10' 0x%02x", b[6]);
		return false;
	}

	flags = (b[7] & 0xC0) >> 6;
	if (flags != 0x2 && flags != 0x3) {
		log_debug("(DEBUG) no pts");
		return false;
	}

	v = (b[9] & 0xF0) >> 4;
	if (v != flags) {
		log_debug("different flags v:0x%02x flags:0x%02x",
			  v, flags);
		return false;
	}

	v_32_30 = (b[9] & 0x0E) >> 1;
	marker[0] = (b[9] & 0x01);
	v_29_15 = (b[10] << 7) | ((b[11] & 0xFE) >> 1);
	marker[1] = (b[11] & 0x01);
	v_14_0 = (b[12] << 7) | ((b[13] & 0xFE) >> 1);
	marker[2] = (b[13] & 0x01);

	if (!(marker[0] || marker[1] || marker[2])) {
		log_debug("invalid marker[%d,%d,%d]",
			  marker[0], marker[1], marker[2]);
		return false;
	}

	*pts = (u64)v_32_30 << 30 | v_29_15 << 15 | v_14_0;

	return true;
}

static void process_dev_filters(struct temi_dev *dev)
{
	int i, ret;
	struct timeline_descriptor *desc;
	struct sdec_temi_filter *f;
	struct temi_data *data = dev->data;

	if (list_empty(&dev->filters))
		return;

	for (i = 0; i < data->desc_count; i++) {
		desc = &data->desc[i];
		log_debug("(DEBUG) temi len[%d] = %d, pts = 0x%09llx",
			  i, desc->len, data->pts);

		list_for_each_entry(f, &dev->filters, dev_entry) {
			if (f->oneshot && f->count > 0)
			     continue;

			if (!temi_timeline_match(f, desc->buf[4]))
				continue;

			ret = f->callback(f, data->pts, desc->buf, desc->len,
					  f->priv);
			if (ret)
				log_temi("temi[%d] - callback error[%d]\n",
					 f->idx, ret);
			else
				f->count++;
		}
	}
}

#define AFC_PAYLOAD_BIT 0x1
#define AFC_ADAPATION_BIT 0x2

static void parse_packet(struct temi_dev *dev, u8 *packet)
{
	u8 afc, afl, maxlen;
	int pos, wsize;
	struct temi_data *data = dev->data;

	if (packet[0] != 0x47) {
		log_temi("no sync byte(0x%02x)", packet[0]);
		return;
	}

	afc = ((packet[3] & 0x30) >> 4);
	maxlen = (afc & AFC_PAYLOAD_BIT) ? 182 : 183;

	// Need syncbyte & PID filter check?
	if (afc & AFC_ADAPATION_BIT)
		parse_adaptation_field(data, packet + 4, maxlen);

	if (!(afc & AFC_PAYLOAD_BIT)) //no payload
		return;

	if (data->state == TEMI_STATE_FREE)
		return;

	if (packet[1] & 0x40) { // Check pusi
		data->pes.offset = 0;
		if (data->state != TEMI_STATE_READY) {
			log_temi("pusi duplicated do it again");
		}
		data->state = TEMI_STATE_GO;
	}

	if (data->state != TEMI_STATE_GO)
		return;

	if (afc & AFC_ADAPATION_BIT) {
		afl = packet[4];
		if (afl > 182) {
			log_error("invalid afl %u", afl);
			return;
		}
		pos = 4 + afl + 1;
	} else {
		pos = 4;
	}

	wsize = MIN(TS_PACKET_SIZE - pos, TEMI_PES_LEN - data->pes.offset);
	memcpy(data->pes.buf + data->pes.offset, packet + pos, wsize);

	data->pes.offset += wsize;
	if (data->pes.offset < TEMI_PES_LEN)
		return;

	if (!get_pts_from_pes(data->pes.buf, &data->pts)) {
		data->state = TEMI_STATE_READY; // find pts again
		return;
	}

	process_dev_filters(dev);

	reset_temi_data(data);
}

static int process_packets(struct temi_dev *dev, u8 *packet, u32 size)
{
	if (!size)
		return 0;

	if ((size % TS_PACKET_SIZE)) {
		return -EIO;
	}

	while (size) {
		parse_packet(dev, packet);

		packet += TS_PACKET_SIZE;
		size -= TS_PACKET_SIZE;
	}

	return 0;
}

static void temi_dev_callback_work(struct work_struct *work)
{
	int i, err;
	u32 size;
	struct te_split_buffer sb;
	struct temi_dev *dev = container_of(work, struct temi_dev, cb_work);

	mutex_lock(&dev->mutex);

	if (dev->state != TEMI_STATE_GO) {
		mutex_unlock(&dev->mutex);
		return;
	}

	err = te_hwbuf_error(&dev->hbuf);
	if (err) {
		te_hwbuf_flush(&dev->hbuf);
		dev->errors++;
		if (dev->errors < max_log_cnt) {
			log_ferr(dev, "buffer error(%d) - flush", err);
		}
		goto exit;
	}

	size = te_hwbuf_avail_size(&dev->hbuf);
	if (!size)
		goto exit;

	te_hwbuf_raw_get_split_rbuf(&dev->hbuf, size, &sb);

	for (i = 0; i < 2; i++) {
		struct te_buffer *b = &sb.b[i];
		process_packets(dev, b->data, b->size);
	}

	te_hwbuf_read_skip(&dev->hbuf, size);

exit:
	mutex_unlock(&dev->mutex);
}

static int temi_recovery(struct sdec_dev_temi *tdev)
{
	int i, count, ret;
	struct temi_dev *d;

	count = 0;
	for (i = 0; i < tdev->num_dev; i++) {
		d = &tdev->dev[i];
		if (d->state == TEMI_STATE_FREE)
			continue;

		reset_temi_data(d->data);
		te_hwbuf_reset(&d->hbuf);
		ret = ipc_request_temi_filter(d);
		if (ret) {
			log_warning("Err ipc_request_temi_filter(%d,%d)\n",
				    d->channel->num, d->idx);
		}
		count++;
	}

	if (count)
		log_noti("%d temi recovered\n", count);

	return 0;
}

static int mcu_recovery_pre_callback(void *arg)
{
	mutex_lock(&temi_mutex);

	return 0;
}

static int mcu_recovery_post_callback(void *arg)
{
	int rc;
	struct sdec_dev_temi *tdev = arg;

	rc = temi_recovery(tdev);

	mutex_unlock(&temi_mutex);

	return rc;
}

/* debug functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("      " fmt, ##args)

static int debug_show_temi(struct sdec_device *dev, struct seq_file *m)
{
	int i;
	struct te_hwbuf_info hinfo;
	struct sdec_dev_temi *tdev = &dev->temi;

	mutex_lock(&temi_mutex);

	dprintf("TEMI DEVICE STATUS\n");
	for (i = 0; i < tdev->num_dev; i++) {
		struct temi_dev *d = &tdev->dev[i];

		if (d->state == TEMI_STATE_FREE)
			continue;

		dprintf("[%02d] CH[%d] %s\n", i, d->channel->num,
			temi_state_str(d->state));

		dprintf1("PID\t\t0x%04x\n", d->pid);

		te_hwbuf_get_info(&d->hbuf, &hinfo);
		dprintf1("BUF_RANGE\t\t[0x%08x--0x%x] %dKB\n", (u32)hinfo.addr,
			 (u32)(hinfo.addr + hinfo.size), hinfo.size >> 10);
		dprintf1("BUF_IDX\t\tWIDX[0x%x] RIDX[0x%x]\n",
			 hinfo.widx, hinfo.ridx);
		dprintf1("ERRORS\t\t%u\n", d->errors);
		dprintf("\n");
	}

	dprintf("TEMI FILTER STATUS\n");
	for (i = 0; i < tdev->num_filter; i++) {
		struct sdec_temi_filter *f = &tdev->filter[i];

		if (f->state == TEMI_STATE_FREE)
			continue;

		dprintf("[%02d] CH[%d] %s\n", i, f->channel->num,
			temi_state_str(f->state));

		dprintf1("PID\t\t0x%04x\n", f->pid);
		if (f->state == TEMI_STATE_GO)
			dprintf1("DEVICE\t\t%d\n", f->dev->idx);
		dprintf1("COUNT\t\t%u\n", f->count);
		dprintf1("PATTERN\t\t0x%02x 0x%02x 0x%02x\n",
			 f->pattern.val, f->pattern.mask, f->pattern.noteq);
	}

	mutex_unlock(&temi_mutex);

	return 0;
}


static int init_temi_dev(struct sdec_dev_temi *tdev)
{
	int i;
	struct temi_dev *dev;

	tdev->dev = vmalloc(tdev->num_dev * sizeof(struct temi_dev));
	CHECK_ERROR(!tdev->dev, return -ENOMEM, "no memory");

	for (i = 0; i < tdev->num_dev; i++) {
		dev = &tdev->dev[i];

		dev->state = TEMI_STATE_FREE;
		dev->idx = i;

		mutex_init(&dev->mutex);
		spin_lock_init(&dev->lock);
		INIT_WORK(&dev->cb_work, temi_dev_callback_work);
	}

	return 0;
}

static void release_temi_dev(struct sdec_dev_temi *tdev)
{
	vfree(tdev->dev);
}

static int init_temi_filter(struct sdec_dev_temi *tdev)
{
	tdev->filter = vzalloc(tdev->num_filter *
			       sizeof(struct sdec_temi_filter));
	CHECK_ERROR(!tdev->filter, return -ENOMEM, "no memory");

	return 0;
}

static void release_temi_filter(struct sdec_dev_temi *tdev)
{
	vfree(tdev->filter);
}

static void init_debug(struct sdec_device *dev)
{
	sdec_debug_register_status_show(dev, SDEC_DEBUG_STATUS_TEMI,
					debug_show_temi);
}

static int dev_suspend(struct sdec_device *dev)
{
	te_ipc_register_temi_callback(NULL, NULL);

	return 0;
}

static int dev_resume(struct sdec_device *dev)
{
	struct sdec_dev_temi *tdev = &dev->temi;

	if (!tdev->num_dev)
		return 0;

	te_ipc_register_temi_callback(ipc_temi_callback, tdev);

	temi_recovery(tdev);

	return 0;
}

static int dev_init(struct sdec_device *dev)
{
	int i, ret = -ENOMEM;
	struct sdec_dev_temi *tdev = &dev->temi;

	/* cfg->num_temi_filter = number of temi filter devices */
	tdev->num_dev = dev->cfg->num_temi_filter;
	if (tdev->num_dev)
		tdev->num_filter = tdev->num_dev;	// + 16;
	else
		tdev->num_filter = 0;

	if (!tdev->num_dev)
		return 0;

	tdev->mem = te_mem_open(TE_MEM_SDEC_NAME);
	CHECK_ERROR(!tdev->mem, return -ENOMEM, "fail to open mem");

	ret = init_temi_dev(tdev);
	CHECK_ERROR(!tdev->mem, goto err_dev, "init_temi_dev failed");

	ret = init_temi_filter(tdev);
	CHECK_ERROR(!tdev->mem, goto err_filter, "init_temi_filter failed");

	for (i = 0; i < dev->num_channel; i++) {
		struct sdec_temi_channel *t = &dev->channels[i].temi;

		INIT_LIST_HEAD(&t->dev_list);
		INIT_LIST_HEAD(&t->filter_list);
		t->seq_num = 0;
	}

	te_ipc_register_temi_callback(ipc_temi_callback, tdev);

	te_mcu_register_rcallback(get_te_device(dev),
				  TE_MCU_FUNC_TYPE_FILTER,
				  mcu_recovery_pre_callback,
				  mcu_recovery_post_callback, tdev);

	init_debug(dev);

	return 0;

err_filter:
	release_temi_dev(tdev);
err_dev:
	te_mem_close(tdev->mem);

	return ret;
}

static void dev_release(struct sdec_device *dev)
{
	struct sdec_dev_temi *tdev = &dev->temi;

	if (!tdev->num_dev)
		return;

	release_temi_filter(tdev);
	release_temi_dev(tdev);
	te_mem_close(tdev->mem);
}

const struct sdec_sub_driver sdec_temi_driver = {
	.name = "sdec_temi",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};

