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
 *  atsc3 filter driver
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	0.1
 *  @date		2016-03-14
 *  @note		Additional information.
 */

#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "atsc3_impl.h"

#define MAX_FILTER_CALLBACK		256

#define PLP_META_SIZE	(4*1024)
#define PLP_DATA_SIZE	(256*1024)
#define PLP_BB_SIZE	(524*1024)	/* BB(8K) + {ALP HEADER(512)+ALP PAYLOAD(64K)}*8 */

#define IS_INVALID_BUFFER_ADDR(addr, buffer) \
	((addr) < (buffer)->start || (addr) >= (buffer)->end)

#define GET_FLT_TYPE(type) (type & 0xF0)

enum {
	OVERFLOW_OK = 0,
	OVERFLOW_ERR_SMALLBUF = 1,
	OVERFLOW_ERR_OVERLAPS = 2,
};

typedef struct linksignal_filter {
	u8 used;
	u8 ch;
	u16 idx;		/* hw index */
	LX_ATSC3_PATTERN_T filter;	/* filter_value, filter_mask, filter_notequal */
	u16 flags;		/* currently used for oneshot */
	u8 ignore_dup;
	u8 request_num;		/* ipc requested num */

	struct list_head list;

	LX_ATSC3_BUFFER_T buffer;
	void *priv;
	void *owner;		/* check owner channel node */

	u8 plpid_val;
	u8 plpid_mask;
	u8 plpid_noteq;

	u8 ovf_status;
	u32 ovf_cnt;
} LINKSIGNAL_FILTER_T;

typedef struct ip_filter {
	u8 used;
	u8 ch;
	u16 idx;		/* hw index */
	u8 src_ip[4];
	u8 dst_ip[4];

	struct list_head list;

	LX_ATSC3_BUFFER_T buffer;
	void *owner;		/* check owner channel node */
} IP_FILTER_T;

typedef struct {
	u32 tsi;		/* tsi not equal will be ignored right now */

	/* Optional Information for AV gathering */
	u32 init_toi;
	u32 num_start;

	LX_ATSC3_PAYLOAD_INFO_T *payload;	/* payload info */
	u8 payload_num;		/* number of payload */
} ROUTE_INFO_T;

typedef struct {
	u16 packet_id;
	LX_ATSC3_PATTERN_T table;
	LX_ATSC3_PATTERN_T content;
} MMT_INFO_T;

typedef struct {
	u8 plpid_val;
	u8 plpid_mask;
	u8 plpid_noteq;
} LLS_INFO_T;

typedef struct udp_filter {
	u8 used;
	u8 ch;
	u16 idx;
	u8 request_num;
	IP_FILTER_T *ip_filter;

	u16 dst_port;
	LX_ATSC3_BUFFER_T buffer;

	LX_ATSC3_PATTERN_T pattern;
	u16 flags;		/* oneshot */
	u8 ignore_dup;
	struct list_head list;
	void *priv;
	void *owner;		/* check owner channel node */

	LX_ATSC3_UDPF_TYPE_T type;
	u8 ovf_status;
	u32 ovf_cnt;
	u32 err_cnt;

	union {
		ROUTE_INFO_T route;
		LLS_INFO_T lls;
		MMT_INFO_T mmt;
	};
} UDP_FILTER_T;

struct atsc3_filter_callback {
	struct atsc3_channel *channel;
	IPC_MSG_ATSC3_DATA_T data;	// from ipc.h
};

static DEFINE_MUTEX(filter_lock);

static int enable_filter_device(struct atsc3_dev_filter *dev);
static int open_channel_device(struct atsc3_channel *channel);


static const char *ipc_atsc3_filter_type_str(IPC_ATSC3_FILTER_TYPE_T type)
{
	const struct te_val_str list[] = {
		{IPC_ATSC3_FILTER_TYPE_PLP, "PLP"},
		{IPC_ATSC3_FILTER_TYPE_LKS, "LINKSIGNAL"},
		{IPC_ATSC3_FILTER_TYPE_IP, "IP"},
		{IPC_ATSC3_FILTER_TYPE_UDP_LLS, "LLS"},
		{IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ, "ROUTE OBJ"},
		{IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS, "ROUTE SLS"},
		{IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV, "ROUTE AV"},
		{IPC_ATSC3_FILTER_TYPE_UDP_MMT_SIGNAL, "MMT SIGNAL"},
		{IPC_ATSC3_FILTER_TYPE_UDP_MMT_AV, "MMT AV"},
	};

	return find_match_string(list, type, "INVALID");
}

static void *get_free_filter(struct atsc3_device *dev, int type)
{
	int i;
	struct atsc3_dev_filter *fdev = &dev->filter;

	switch (type) {
	case LX_ATSC3_FILTER_TYPE_LINKSIGNAL:
		for (i = 0; i < fdev->num_linksignalf; i++) {
			LINKSIGNAL_FILTER_T *f = &fdev->linksignalf[i];
			if (!f->used) {
				memset(f, 0, sizeof(*f));
				f->idx = i;
				return f;
			}
		}
		break;

	case LX_ATSC3_FILTER_TYPE_IP:
		for (i = 0; i < fdev->num_ipf; i++) {
			IP_FILTER_T *f = &fdev->ipf[i];
			if (!f->used) {
				memset(f, 0, sizeof(*f));
				f->idx = i;
				return f;
			}
		}
		break;

	case LX_ATSC3_FILTER_TYPE_UDP:
		for (i = 0; i < fdev->num_udpf; i++) {
			UDP_FILTER_T *f = &fdev->udpf[i];
			if (!f->used) {
				memset(f, 0, sizeof(*f));
				f->idx = i;
				return f;
			}
		}
		break;

	default:
		break;
	}
	return NULL;
}

static void *get_filter_from_idx(struct atsc3_channel *channel,
				 u8 type, u16 idx)
{
	if (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		LINKSIGNAL_FILTER_T *f;
		list_for_each_entry(f, &channel->filter.linksignal_head, list) {
			if (f->idx == idx)
				return f;
		}
	} else if (type == LX_ATSC3_FILTER_TYPE_IP) {
		IP_FILTER_T *f;
		list_for_each_entry(f, &channel->filter.ip_head, list) {
			if (f->idx == idx)
				return f;
		}
	} else if (type == LX_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *f;
		list_for_each_entry(f, &channel->filter.udp_head, list) {
			if (f->idx == idx)
				return f;
		}
	}

	return NULL;
}

static void CopyUDPInfo(LX_ATSC3_NOTIFY_FILTER_T *noti_filter,
			void *payload, UDP_FILTER_T *f)
{
	if (f->type == LX_ATSC3_UDPF_TYPE_LLS) {
		/* Nothing to do */
	} else if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT) {
		LX_ATSC3_ROUTE_INFO_T *route = &noti_filter->route;
		IPC_ATSC3_UDP_ROUTE_OBJ_DATA_PAYLOAD_T *ipc = payload;

		if (ipc->err_indicator) {
			log_filter("error detected in MCU idx[%d]", f->idx);
			f->err_cnt++;
		}

		route->toi = ipc->toi;
	} else if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_AV) {
		LX_ATSC3_ROUTE_INFO_T *route = &noti_filter->route;
		IPC_ATSC3_UDP_ROUTE_AV_DATA_PAYLOAD_T *ipc = payload;

		/* common */
		route->mode = ipc->mode;
		route->toi = ipc->toi;

		memset(&route->flag, 0, sizeof(route->flag));

		/* optional */
		if (ipc->mode == IPC_DATA_ROUTE_MDE_MODE) {
			route->object_len = ipc->object_len;
			if (ipc->flags & IPC_ROUTE_FLAG_SCT_H) {
				route->sct.hi = ipc->sct_high;
				route->flag.sct_h = 1;
			}
			if (ipc->flags & IPC_ROUTE_FLAG_SCT_L) {
				route->sct.lo = ipc->sct_low;
				route->flag.sct_l = 1;
			}
			if (ipc->flags & IPC_ROUTE_FLAG_PT_H) {
				route->pt.hi = ipc->pt_high;
				route->flag.pt_h = 1;
			}
			if (ipc->flags & IPC_ROUTE_FLAG_PT_L) {
				route->pt.lo = ipc->pt_low;
				route->flag.pt_l = 1;
			}
		} else if (ipc->mode == IPC_DATA_ROUTE_OBJ_MODE) {
			// Nothing to do
		}
	} else if (f->type == LX_ATSC3_UDPF_TYPE_MMT_SIGNAL) {
		/* Nothing to do */
	} else if (f->type == LX_ATSC3_UDPF_TYPE_MMT_AV) {
		LX_ATSC3_MMT_INFO_T *mmt = &noti_filter->mmt;
		IPC_ATSC3_UDP_MMT_AV_DATA_PAYLOAD_T *ipc = payload;

		mmt->timestamp = ipc->timestamp;
		mmt->rap_flag = ipc->rap;
		mmt->mpu_fragment_type = ipc->mpu_type;
		mmt->mpu_sequence_number = ipc->mpu_seq_num;
		mmt->du_header.movie_fragment_sequence_number
		    = ipc->mov_frag_seq_num;
		mmt->du_header.sample_number = ipc->sample_number;
		mmt->du_header.offset = ipc->offset;
		mmt->du_header.priority = ipc->priority;
		mmt->du_header.dep_counter = ipc->dep_counter;
	}
}

static int check_data_validation(LX_ATSC3_BUFFER_T *buffer, u32 saddr,
				 u32 eaddr)
{
	/* check data validation */
	if (saddr == eaddr ||	/* empty */
	    IS_INVALID_BUFFER_ADDR(saddr, buffer) ||
	    IS_INVALID_BUFFER_ADDR(eaddr, buffer)) {
		log_error("invalid address(%08x--%08x), buffer(%08x--%08x)\n",
			  saddr, eaddr, buffer->start, buffer->end);
		return -EINVAL;
	}

	return 0;
}

static int linksignal_callback_work(struct atsc3_channel *channel,
				    IPC_MSG_ATSC3_DATA_T *data)
{
	LX_ATSC3_NOTIFY_DATA_T noti_param;
	LX_ATSC3_NOTIFY_FILTER_T *noti_filter;
	LINKSIGNAL_FILTER_T *f;
	LX_ATSC3_FLT_TYPE_T type;
	LX_ATSC3_LINKSIGNAL_INFO_T *linksignal;
	IPC_ATSC3_LKS_DATA_PAYLOAD_T *payload;
	u32 saddr, eaddr;
	int ret;

	type = LX_ATSC3_FILTER_TYPE_LINKSIGNAL;

	f = get_filter_from_idx(channel, type, data->info.flt_idx);
	CHECK_ERROR(!f, return -EINVAL, "unused filter index(%d)",
		    data->info.flt_idx);

	if (f->request_num != data->info.req_num) {
		log_warning("not matched request f_num(%d):callback(%d)\n",
			    f->request_num, data->info.req_num);
		return -EINVAL;
	}

	payload = &(data->lks);
	saddr = payload->data_saddr;
	eaddr = payload->data_eaddr;

	ret = check_data_validation(&f->buffer, saddr, eaddr);
	CHECK_ERROR(ret, return ret, "invalid data");

	/* make notify data */
	noti_param.type = LX_ATSC3_NOTIFY_LINKSIGNAL_FILTER;

	/* Common information */
	noti_filter = &noti_param.filter;
	noti_filter->ch = channel->num;
	noti_filter->index = f->idx;
	noti_filter->rptr = saddr;
	noti_filter->wptr = eaddr;
	noti_filter->status = LX_ATSC3_FLT_STATE_DATAREADY;
	noti_filter->msec = te_get_ms_tick();
	noti_filter->priv = f->priv;

	linksignal = &noti_filter->linksignal;
	linksignal->version = payload->ver;
	linksignal->type = payload->type;
	linksignal->type_extension = payload->type_ext;
	linksignal->format = payload->fmt;
	linksignal->encoding = payload->enc;

	ret = atsc3_add_message(channel->dev, &noti_param);

	return ret;
}

static int udp_callback_work(struct atsc3_channel *channel,
			     IPC_MSG_ATSC3_DATA_T *data)
{
	LX_ATSC3_NOTIFY_DATA_T noti_param;
	LX_ATSC3_NOTIFY_FILTER_T *noti_filter;
	UDP_FILTER_T *f;
	IPC_ATSC3_UDP_DATA_INFO_T *info;
	u32 saddr, eaddr;
	u8 type;
	int ret;

	type = LX_ATSC3_FILTER_TYPE_UDP;

	f = get_filter_from_idx(channel, type, data->info.flt_idx);
	CHECK_ERROR(!f, return -EINVAL, "unused filter index(%d)",
		    data->info.flt_idx);

	if (f->request_num != data->info.req_num) {
		log_warning("not matched request f_num(%d):callback(%d)\n",
			    f->request_num, data->info.req_num);
		return -EINVAL;
	}

	info = (IPC_ATSC3_UDP_DATA_INFO_T *)data->data_payload;
	saddr = info->data_saddr;
	eaddr = info->data_eaddr;

	ret = check_data_validation(&f->buffer, saddr, eaddr);
	CHECK_ERROR(ret != 0, return ret, "invalid data");

	/* make notify data */
	noti_param.type = LX_ATSC3_NOTIFY_UDP_FILTER;

	/* Common information */
	noti_filter = &noti_param.filter;
	noti_filter->ch = channel->num;
	noti_filter->index = f->idx;
	noti_filter->status = LX_ATSC3_FLT_STATE_DATAREADY;
	noti_filter->rptr = saddr;
	noti_filter->wptr = eaddr;
	noti_filter->msec = te_get_ms_tick();
	noti_filter->priv = f->priv;

	CopyUDPInfo(noti_filter, data->data_payload, f);

	ret = atsc3_add_message(channel->dev, &noti_param);

	return ret;
}

static void PrintOverflowFilterInfo(UDP_FILTER_T *f)
{
	IP_FILTER_T *ip_f = f->ip_filter;

	log_error("--> ch[%d] src:%d.%d.%d.%d dst:%d.%d.%d.%d port:%d", f->ch,
		  ip_f->src_ip[0], ip_f->src_ip[1], ip_f->src_ip[2],
		  ip_f->src_ip[3], ip_f->dst_ip[0], ip_f->dst_ip[1],
		  ip_f->dst_ip[2], ip_f->dst_ip[3], f->dst_port);
	log_error("--> type[%d] V[0x%08x] M[0x%08x] N[0x%08x]", f->type,
		  f->pattern.value, f->pattern.mask, f->pattern.noteq);
	if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT
	    || f->type == LX_ATSC3_UDPF_TYPE_ROUTE_AV) {
		log_error("--> ROUTE tsi[%d]", f->route.tsi);
	} else if (f->type == LX_ATSC3_UDPF_TYPE_MMT_SIGNAL
		   || f->type == LX_ATSC3_UDPF_TYPE_MMT_AV) {
		log_error("--> MMT packet_id[%d]", f->mmt.packet_id);
	}

	return;
}

static int filter_overflow_callback_work(struct atsc3_channel *channel,
					 IPC_MSG_ATSC3_DATA_INFO_T *info)
{
	LX_ATSC3_BUFFER_T *buf;

	if (GET_FLT_TYPE(info->type) == IPC_ATSC3_FILTER_TYPE_LKS) {
		LINKSIGNAL_FILTER_T *f;
		IPC_ATSC3_LKS_STATUS_T ipc_status;

		f = get_filter_from_idx(channel,
					LX_ATSC3_FILTER_TYPE_LINKSIGNAL,
					info->flt_idx);
		CHECK_ERROR(!f, return -EINVAL, "unused filter index(%d)",
			    info->flt_idx);

		buf = &f->buffer;

		TE_IPC_GetATSC3FilterStatus(f->idx, IPC_ATSC3_FILTER_TYPE_LKS,
					    (void *)&ipc_status);

		log_error("MCU Overflow detected: LINKSIGNAL[%d]",
			  info->flt_idx);
		log_error("--> ch[%d] V[0x%08x] M[0x%08x] N[0x%08x]", f->ch,
			  f->filter.value, f->filter.mask, f->filter.noteq);
		log_error("--> [w:0x%08x, r:0x%08x, s:0x%08x, e:0x%08x]",
			  ipc_status.gpb_wptr, ipc_status.gpb_rptr, buf->start,
			  buf->end);

		f->ovf_status =
		    (info->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR) ?
		    OVERFLOW_ERR_OVERLAPS : OVERFLOW_ERR_SMALLBUF;
		f->ovf_cnt++;

		atsc3_add_msg_status(channel->dev,
				     LX_ATSC3_NOTIFY_LINKSIGNAL_FILTER, f->idx,
				     LX_ATSC3_FLT_STATE_OVERFLOW);
	} else if (GET_FLT_TYPE(info->type) == IPC_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *f;
		IPC_ATSC3_UDP_STATUS_T ipc_status;

		f = get_filter_from_idx(channel, LX_ATSC3_FILTER_TYPE_UDP,
					info->flt_idx);
		CHECK_ERROR(!f, return -EINVAL, "unused filter index(%d)",
			    info->flt_idx);

		buf = &f->buffer;

		TE_IPC_GetATSC3FilterStatus(f->idx, IPC_ATSC3_FILTER_TYPE_UDP,
					    (void *)&ipc_status);

		log_error("MCU Overflow detected: UDP[%d]", info->flt_idx);
		PrintOverflowFilterInfo(f);
		log_error("--> [w:0x%08x, r:0x%08x, s:0x%08x, e:0x%08x]",
			  ipc_status.gpb_wptr, ipc_status.gpb_rptr, buf->start,
			  buf->end);

		f->ovf_status =
		    (info->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR) ?
		    OVERFLOW_ERR_OVERLAPS : OVERFLOW_ERR_SMALLBUF;
		f->ovf_cnt++;

		atsc3_add_msg_status(channel->dev, LX_ATSC3_NOTIFY_UDP_FILTER,
				     f->idx, LX_ATSC3_FLT_STATE_OVERFLOW);
	} else {
		log_error("Invalid type[%d]", info->type);
		return -EINVAL;
	}

	return 0;
}

static void process_filter_callback(struct atsc3_filter_callback *cb)
{
	struct atsc3_channel *channel = cb->channel;
	IPC_MSG_ATSC3_DATA_INFO_T *info = &cb->data.info;

	log_debug("ch:%d type:0x%02x req_num:%d flt_idx:%d status:%d\n",
		  info->ch, info->type, info->req_num,
		  info->flt_idx, info->status);

	switch (info->status) {
	case IPC_DATA_STATUS_OK:
		switch (GET_FLT_TYPE(info->type)) {
		case IPC_ATSC3_FILTER_TYPE_LKS:
			linksignal_callback_work(channel, &cb->data);
			break;
		case IPC_ATSC3_FILTER_TYPE_UDP:
			udp_callback_work(channel, &cb->data);
			break;
		default:
			log_warning("invalid filter type [0x%02x]\n",
				    info->type);
			break;
		}
		break;

	case IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR:
	case IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF:
		filter_overflow_callback_work(channel, info);
		break;
	default:
		log_warning("invalid callback status(%d)\n", info->status);
		break;
	}
}

static void filter_callback_work(struct work_struct *work)
{
	struct atsc3_filter_callback *cb;
	struct atsc3_dev_filter *fdev;

	fdev = container_of(work, struct atsc3_dev_filter, callback_work);

	while (te_msgbuf_avail_count(&fdev->callback_buf)) {

		te_msgbuf_raw_get_rbuf(&fdev->callback_buf, 0, (void **)&cb);

		mutex_lock(&filter_lock);
		process_filter_callback(cb);
		mutex_unlock(&filter_lock);

		te_msgbuf_raw_read_skip(&fdev->callback_buf, 1);
	}
}

/* isr callback */
static int ipc_filter_callback(void *msg, void *arg)
{
	struct atsc3_channel *channel;
	struct atsc3_dev_filter *fdev;
	struct atsc3_filter_callback *callback;
	IPC_MSG_ATSC3_DATA_T *data = msg;
	struct atsc3_device *dev = arg;

	channel = atsc3_get_channel(dev, data->info.ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", data->info.ch);

	fdev = &dev->filter;
	if (!te_msgbuf_free_count(&fdev->callback_buf)) {
		log_error("no avaiable callback buffer\n");
		return -ENOMEM;
	}

	te_msgbuf_raw_get_wbuf(&fdev->callback_buf, 0, (void **)&callback);

	callback->channel = channel;
	callback->data = *data;

	te_msgbuf_raw_write_skip(&fdev->callback_buf, 1);

	queue_work(system_freezable_wq, &fdev->callback_work);

	return 0;
}

static int reset_filter_callback_work(struct atsc3_dev_filter *fdev)
{
	int count;
	struct te_msgbuf *mbuf = &fdev->callback_buf;

	count = te_msgbuf_avail_count(mbuf);
	te_msgbuf_reset(mbuf);

	if (count)
		log_noti("removed %d filter callbacks\n", count);

	return count;
}

static int LINKSIGNAL_Recovery(struct atsc3_device *dev, LINKSIGNAL_FILTER_T *f)
{
	IPC_ATSC3_LKS_REQ_PAYLOAD_T payload;
	u32 len;
	int ret;

	memset(&payload, 0, sizeof(payload));

	payload.req_num = f->request_num;	// is it necessary?
	payload.gpb_saddr = f->buffer.start;
	payload.gpb_eaddr = f->buffer.end;
	payload.filter_value = f->filter.value;
	payload.filter_mask = f->filter.mask;
	payload.filter_noteq = f->filter.noteq;
	payload.plpid_value = f->plpid_val;
	payload.plpid_mask = f->plpid_mask;
	payload.plpid_noteq = f->plpid_noteq;

	if (f->flags & LX_ATSC3_FLT_FLAG_ONESHOT)
		payload.oneshot = true;
	else
		payload.oneshot = false;

	len = sizeof(IPC_ATSC3_LKS_REQ_PAYLOAD_T);

	ret = TE_IPC_RequestATSC3Filter(f->ch, IPC_ATSC3_FILTER_TYPE_LKS,
					f->idx, len, &payload);
	CHECK_ERROR(ret < 0,, "Error(%d) in TE_IPC_RequestATSC3Filter", ret);

	return 0;
}

static int IP_Recovery(struct atsc3_device *dev, IP_FILTER_T *f)
{
	IPC_ATSC3_IP_REQ_PAYLOAD_T payload;
	u32 len;
	int ret;

	memset(&payload, 0, sizeof(payload));

	//ipc_req.ctrl.ch               = f->ch;
	payload.ipbuf_saddr = f->buffer.start;
	payload.ipbuf_eaddr = f->buffer.end;
	memcpy(payload.src_ip, f->src_ip, sizeof(f->src_ip));
	memcpy(payload.dst_ip, f->dst_ip, sizeof(f->dst_ip));

	len = sizeof(IPC_ATSC3_IP_REQ_PAYLOAD_T);

	ret = TE_IPC_RequestATSC3Filter(f->ch, IPC_ATSC3_FILTER_TYPE_IP,
					f->idx, len, &payload);
	CHECK_ERROR(ret < 0,, "Error(%d) in TE_IPC_RequestATSC3Filter", ret);

	return 0;
}

static int UDP_MakeROUTEInfo(struct atsc3_device *dev,
			     IPC_ATSC3_UDP_ROUTE_REQ_INFO_T *info,
			     LX_ATSC3_PAYLOAD_INFO_T *ptr, u8 payload_num,
			     u32 tsi, u8 ignore_dup)
{
	int i;
	te_phys_addr_t paddr = 0;
	IPC_ATSC3_UDP_CP_INFO_T *vmap_data;
	u32 ipc_size = payload_num * sizeof(IPC_ATSC3_UDP_CP_INFO_T);

	info->tsi = tsi;
	info->ignore_dup = ignore_dup;
	info->cp_num = payload_num;

	if (payload_num) {
		/* alloc srcflow mem */
		paddr = te_mem_alloc(dev->filter.mem, ipc_size,
				     "atsc3_srcflow");
		CHECK_ERROR(paddr == 0, goto error, "can't alloc memory");

		vmap_data = te_vmap(paddr, ipc_size, false);
		CHECK_ERROR(vmap_data == NULL, goto error, "vmap_phys fail");

		for (i = 0; i < payload_num; i++) {
			vmap_data[i].cp = ptr[i].code_point;
			vmap_data[i].fec_payload_id = ptr[i].fec_payload_id;
		}
		te_vunmap(vmap_data);

		info->cp_addr = paddr;	//Register for ipc msg and free
	}

	return 0;

 error:
	if (paddr)
		te_mem_free(dev->filter.mem, paddr);

	return -EIO;
}

static int UDP_Recovery(struct atsc3_device *dev, UDP_FILTER_T *f)
{
	IPC_ATSC3_UDP_REQ_INFO_T info;
	int ret;
	u32 len;
	u32 ipc_srcflow_paddr = 0;	//temporal space for ipc send
	IPC_ATSC3_FILTER_TYPE_T type;

	memset(&info, 0, sizeof(info));	//set to zero

	info.req_num = f->request_num;
	info.ip_idx = f->ip_filter->idx;
	info.dst_port = f->dst_port;
	info.gpb_saddr = f->buffer.start;
	info.gpb_eaddr = f->buffer.end;

	if (f->flags & LX_ATSC3_FLT_FLAG_ONESHOT)
		info.oneshot = true;
	else
		info.oneshot = false;

	if (f->type == LX_ATSC3_UDPF_TYPE_LLS) {
		IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));

		type = IPC_ATSC3_FILTER_TYPE_UDP_LLS;

		payload.info = info;
		payload.filter_value = f->pattern.value;
		payload.filter_mask = f->pattern.mask;
		payload.filter_noteq = f->pattern.noteq;
		payload.plpid_value = f->lls.plpid_val;
		payload.plpid_mask = f->lls.plpid_mask;
		payload.plpid_noteq = f->lls.plpid_noteq;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(f->ch, type, f->idx, len,
						&payload);
		CHECK_ERROR(ret < 0,, "Err in TE_IPC_RequestATSC3Filter");
	} else if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT ||
		   f->type == LX_ATSC3_UDPF_TYPE_ROUTE_SLS) {
		IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T payload;
		IPC_ATSC3_UDP_ROUTE_REQ_INFO_T *r_info = &(payload.route_info);	//ROUTE IPC msg

		memset(&payload, 0, sizeof(payload));	//set to zero

		if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT)	//check filter type
			type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ;
		else
			type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS;

		/* Common UDP value */
		payload.info = info;

		/* f has srcflow pointer */

		/* ROUTE common information: including ipc_srcflow pointer */
		/* r_info->cp_addr should be freed after this function */
		ret = UDP_MakeROUTEInfo(dev, r_info, f->route.payload,
					f->route.payload_num,
					f->route.tsi, f->ignore_dup);
		CHECK_ERROR(ret < 0, goto error, "Error in MakeROUTEInfo");

		ipc_srcflow_paddr = r_info->cp_addr;	//for free process

		/* ROUTE Object specific value */
		payload.toi_value = f->pattern.value;
		payload.toi_mask = f->pattern.mask;
		payload.toi_noteq = f->pattern.noteq;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(f->ch, type, f->idx, len,
						&payload);
		CHECK_ERROR(ret < 0,,
			    "Error(%d) in TE_IPC_RequestATSC3Filter", ret);
	} else if (f->type == LX_ATSC3_UDPF_TYPE_ROUTE_AV) {
		IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T payload;
		IPC_ATSC3_UDP_ROUTE_REQ_INFO_T *r_info = &(payload.route_info);	//ROUTE IPC msg
		IPC_ATSC3_FILTER_TYPE_T type;

		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV;

		/* Common UDP value */
		payload.info = info;

		/* f has srcflow pointer */

		/* ROUTE common information: including ipc_srcflow pointer */
		/* r_info->cp_addr should be freed after this function */
		ret = UDP_MakeROUTEInfo(dev, r_info, f->route.payload,
					f->route.payload_num,
					f->route.tsi, f->ignore_dup);
		CHECK_ERROR(ret < 0, goto error, "Error in MakeROUTEInfo");

		ipc_srcflow_paddr = r_info->cp_addr;	//for free process

		/* ROUTE AV specific value */
		payload.init_toi = f->route.init_toi;
		payload.num_start = f->route.num_start;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(f->ch, type, f->idx, len,
						&payload);
		CHECK_ERROR(ret < 0,, "Err in TE_IPC_RequestATSC3Filter");

	} else if (f->type == LX_ATSC3_UDPF_TYPE_MMT_SIGNAL) {
		IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_MMT_SIGNAL;

		payload.info = info;
		payload.packet_id = f->mmt.packet_id;
		payload.msg_value = f->pattern.value;
		payload.msg_mask = f->pattern.mask;
		payload.msg_noteq = f->pattern.noteq;
		payload.table_value = f->mmt.table.value;
		payload.table_mask = f->mmt.table.mask;
		payload.table_noteq = f->mmt.table.noteq;
		payload.content_value = f->mmt.content.value;
		payload.content_mask = f->mmt.content.mask;
		payload.content_noteq = f->mmt.content.noteq;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(f->ch, type, f->idx, len,
						&payload);
		CHECK_ERROR(ret < 0,, "Err in TE_IPC_RequestATSC3Filter");
	} else if (f->type == LX_ATSC3_UDPF_TYPE_MMT_AV) {
		IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_MMT_AV;

		payload.info = info;
		payload.packet_id = f->mmt.packet_id;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(f->ch, type, f->idx, len,
						&payload);
		CHECK_ERROR(ret < 0,, "Err in TE_IPC_RequestATSC3Filter");
	} else {
		log_error("invalid filter type(%d)\n", f->type);
		return -EINVAL;
	}

	if (ipc_srcflow_paddr)
		te_mem_free(dev->filter.mem, ipc_srcflow_paddr);

	return 0;

 error:
	if (ipc_srcflow_paddr)
		te_mem_free(dev->filter.mem, ipc_srcflow_paddr);

	return -EIO;
}

static int recovery_filter(struct atsc3_device *dev)
{
	struct atsc3_channel *channel;
	struct atsc3_filter_channel *filter;
	LINKSIGNAL_FILTER_T *linksignalf;
	IP_FILTER_T *ipf;
	UDP_FILTER_T *udpf;
	int i;
	int ret;
	u32 en_channels = 0;
	u32 link_cnt = 0, ip_cnt = 0, udp_cnt = 0;

	if (dev->filter.enable) {
		ret = enable_filter_device(&dev->filter);
		CHECK_ERROR(ret, return ret, "enable_filter_device failed");
	}

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		filter = &channel->filter;

		if (!filter->enable)
			continue;

		en_channels++;

		ret = open_channel_device(channel);
		CHECK_ERROR(ret, return ret, "open_channel_device failed");

		list_for_each_entry(linksignalf, &filter->linksignal_head, list) {
			LINKSIGNAL_Recovery(dev, linksignalf);
			link_cnt++;
		}
		list_for_each_entry(ipf, &filter->ip_head, list) {
			IP_Recovery(dev, ipf);
			ip_cnt++;
		}
		list_for_each_entry(udpf, &filter->udp_head, list) {
			UDP_Recovery(dev, udpf);
			udp_cnt++;
		}
	}

	if (en_channels) {
		log_noti("%d channels filter enabled\n", en_channels);
		log_noti("link[%d] ip[%d] udp[%d] filters are recovered\n",
			 link_cnt, ip_cnt, udp_cnt);
	}

	return 0;
}

static int mcu_recovery_pre_callback(void *arg)
{
	mutex_lock(&filter_lock);

	return 0;
}

static int mcu_recovery_post_callback(void *arg)
{
	int ret;
	struct atsc3_device *dev = arg;

	ret = recovery_filter(dev);
	mutex_unlock(&filter_lock);

	return ret;
}

/**
 * Allocate unused filter and add into list
 */
static void *alloc_filter(struct atsc3_channel *channel, int type, void *param)
{
	if (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		LINKSIGNAL_FILTER_T *f;

		f = get_free_filter(channel->dev, type);
		CHECK_ERROR(!f, return NULL,
			    "no empty linksignal filter slot!!! \n");

		f->used = true;
		f->ch = channel->num;
		f->flags = 0x00;

		list_add_tail(&f->list, &channel->filter.linksignal_head);

		return f;
	} else if (type == LX_ATSC3_FILTER_TYPE_IP) {
		IP_FILTER_T *f;
		LX_ATSC3_FLT_IP_REQ_T *req = param;

		list_for_each_entry(f, &channel->filter.ip_head, list) {
			if (TE_GET32(f->src_ip) == TE_GET32(req->src_ip)
			    && TE_GET32(f->dst_ip) == TE_GET32(req->dst_ip)) {
				log_error
				    ("same ip pair is exit in idx[src: 0x%08x, dst: 0x%08x, idx: %d]\n",
				     TE_GET32(f->src_ip), TE_GET32(f->dst_ip),
				     f->idx);
				return NULL;
			}
		}
		f = get_free_filter(channel->dev, type);
		CHECK_ERROR(!f, return NULL, "no empty ip filter slot!!! \n");

		f->used = true;
		f->ch = channel->num;
		memcpy(f->src_ip, req->src_ip, IPC_MAX_IP_LEN);
		memcpy(f->dst_ip, req->dst_ip, IPC_MAX_IP_LEN);

		list_add_tail(&f->list, &channel->filter.ip_head);

		return f;
	} else if (type == LX_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *f;

		f = get_free_filter(channel->dev, type);
		CHECK_ERROR(!f, return NULL, "no empty udp filter slot!!! \n");

		f->used = true;
		f->ch = channel->num;
		f->flags = 0x00;

		list_add_tail(&f->list, &channel->filter.udp_head);

		return f;
	}

	return NULL;
}

static int free_filter(struct atsc3_channel *channel, int type, void *filter)
{
	int ret;

	if (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		LINKSIGNAL_FILTER_T *f = filter;

		f->used = false;
		f->owner = NULL;	//Release owner
		list_del(&f->list);

		return 0;
	} else if (type == LX_ATSC3_FILTER_TYPE_IP) {
		struct atsc3_dev_filter *fdev = &channel->dev->filter;
		IP_FILTER_T *f = filter;

		if (f->buffer.start) {
			ret = te_mem_free(fdev->mem, f->buffer.start);
			CHECK_ERROR(ret < 0,, "Error in te_mem_free");
		}

		f->used = false;
		f->owner = NULL;	//Release owner
		list_del(&f->list);

		return 0;
	} else if (type == LX_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *f = filter;

		if ((f->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT ||
		     f->type == LX_ATSC3_UDPF_TYPE_ROUTE_AV) &&
		    f->route.payload != NULL) {
			kfree(f->route.payload);
			f->route.payload = NULL;
		}

		f->used = false;
		f->owner = NULL;	//Release owner
		list_del(&f->list);

		return 0;
	}

	log_error("unknown type(%d)\n", type);

	return -EINVAL;
}

/**
 * enable_filter_device - Enable atsc3 filter in MCU
 *
 * MCU support only one filter type(ATSC3 or ARIB2), and no way to disable it.
 */
static int enable_filter_device(struct atsc3_dev_filter *dev)
{
	struct atsc3_config *cfg = atsc3_get_config();
	int ret;

	if (!cfg->use_engine_sel) { // engine_selector has been deprecated
		ret = te_ipc_enable_atsc3_filter();
	} else {
		/* we can select engine type just one time */
		ret = TE_IPC_SetEngineType(IPC_STATUS_ENGINE_ATSC3);
	}

	return ret;
}

static int open_channel_device(struct atsc3_channel *channel)
{
	int ret;
	IPC_ADAP_ATSC3_CHBUF_INFO_T msg;
	struct atsc3_filter_buffer *buf = &channel->filter.buffer;

	msg.metabuf_saddr = buf->metabuf_saddr;
	msg.metabuf_eaddr = buf->metabuf_eaddr;
	msg.databuf_saddr = buf->databuf_saddr;
	msg.databuf_eaddr = buf->databuf_eaddr;
	msg.bbbuf_saddr = buf->bbbuf_saddr;
	msg.bbbuf_eaddr = buf->bbbuf_eaddr;

	ret = TE_IPC_OpenATSC3Channel(channel->num, &msg);
	CHECK_ERROR(ret, return ret, "TE_IPC_OpenATSC3Channel failed");

	return 0;
}

static int close_channel_device(struct atsc3_channel *channel)
{
	int ret;

	ret = TE_IPC_CloseATSC3Channel(channel->num);
	CHECK_ERROR(ret, return ret, "TE_IPC_CloseATSC3Channel failed");

	return ret;
}

static int enable_channel(struct atsc3_channel *channel)
{
	int ret;
	struct atsc3_dev_filter *fdev = &channel->dev->filter;
	struct atsc3_filter_channel *filter = &channel->filter;
	u32 meta_addr, data_addr, bb_addr;

	if (filter->enable) {
		log_error("filter channel(%d) already enabled\n", channel->num);
		return -EINVAL;
	}

	if (!fdev->enable) {
		ret = enable_filter_device(fdev);
		CHECK_ERROR(ret, return ret, "enable_filter_device failed");

		fdev->enable = true;
	}

	meta_addr = te_mem_alloc(fdev->mem, PLP_META_SIZE, "atsc3_plp_meta");
	CHECK_ERROR(!meta_addr, goto err_meta_mem, "can't alloc memory\n");

	data_addr = te_mem_alloc(fdev->mem, PLP_DATA_SIZE, "atsc3_plp_data");
	CHECK_ERROR(!data_addr, goto err_data_mem, "can't alloc memory\n");

	bb_addr = te_mem_alloc(fdev->mem, PLP_BB_SIZE, "atsc3_plp_bb");
	CHECK_ERROR(!bb_addr, goto err_bb_mem, "can't alloc memory\n");

	filter->buffer.metabuf_saddr = meta_addr;
	filter->buffer.metabuf_eaddr = meta_addr + PLP_META_SIZE;
	filter->buffer.databuf_saddr = data_addr;
	filter->buffer.databuf_eaddr = data_addr + PLP_DATA_SIZE;
	filter->buffer.bbbuf_saddr = bb_addr;
	filter->buffer.bbbuf_eaddr = bb_addr + PLP_BB_SIZE;

	ret = open_channel_device(channel);
	CHECK_ERROR(ret, goto err_open, "open_channel_device failed(%d)", ret);

	filter->enable = true;

	atsc3_io_set_channel_enable(channel, true);

	log_filter("allocated memory meta:[%08x--%08x] data:[%08x--%08x]",
		   meta_addr, meta_addr + PLP_META_SIZE, data_addr,
		   data_addr + PLP_DATA_SIZE);

	return 0;

err_open:
	te_mem_free(fdev->mem, bb_addr);
err_bb_mem:
	te_mem_free(fdev->mem, data_addr);
err_data_mem:
	te_mem_free(fdev->mem, meta_addr);
err_meta_mem:

	return -EIO;
}

static int disable_channel(struct atsc3_channel *channel)
{
	int ret;
	struct atsc3_filter_channel *filter = &channel->filter;
	struct atsc3_filter_buffer *buf = &filter->buffer;
	struct atsc3_dev_filter *fdev = &channel->dev->filter;

	if (!filter->enable) {
		log_error("filter channel(%d) not enabled\n", channel->num);
		return -EINVAL;
	}

	atsc3_io_set_channel_enable(channel, false);

	ret = close_channel_device(channel);
	CHECK_ERROR(ret,, "Error(%d) in close_channel_device", ret);

	ret = te_mem_free(fdev->mem, buf->metabuf_saddr);
	CHECK_ERROR(ret < 0,, "Error(%d) in te_mem_free(META)", ret);

	buf->metabuf_saddr = 0;
	buf->metabuf_eaddr = 0;

	ret = te_mem_free(fdev->mem, buf->databuf_saddr);
	CHECK_ERROR(ret < 0,, "Error(%d) in te_mem_free(DATA)", ret);

	buf->databuf_saddr = 0;
	buf->databuf_eaddr = 0;

	ret = te_mem_free(fdev->mem, buf->bbbuf_saddr);
	CHECK_ERROR(ret < 0,, "Error(%d) in te_mem_free(BB)", ret);

	buf->bbbuf_saddr = 0;
	buf->bbbuf_eaddr = 0;

	filter->enable = false;

	log_filter("deallocated meta and data memory");

	return 0;
}

static int check_filter_paddr_range(struct atsc3_fh *fh, u32 addr, u32 size)
{
	struct te_mem_ctx *mem, *temp_mem = NULL;
	int rc;

	if (fh->mem) {
		mem = fh->mem;
	} else {
		temp_mem = te_mem_open(ATSC3_MEM_NAME);
		if (!temp_mem)
			return -EIO;
		mem = temp_mem;
	}

	rc = te_mem_check_paddr_range(mem, addr, size);

	if (temp_mem)
		te_mem_close(temp_mem);

	return rc;
}

static LINKSIGNAL_FILTER_T *LINKSIGNAL_Request(struct atsc3_channel *channel,
					       void *priv,
					       LX_ATSC3_FLT_LINKSIGNAL_REQ_T
					       *req)
{
	LINKSIGNAL_FILTER_T *f = NULL;
	IPC_ATSC3_LKS_REQ_PAYLOAD_T payload;
	struct atsc3_filter_channel *ctrl = &(channel->filter);
	u32 len;
	int ret;

	ret = check_filter_paddr_range(priv, req->buf.addr, req->buf.size);
	if (ret)
		return NULL;

	f = alloc_filter(channel, LX_ATSC3_FILTER_TYPE_LINKSIGNAL, req);
	CHECK_ERROR(!f, goto error, "fail to alloc ipf");

	memset(&payload, 0, sizeof(payload));	//set to zero

	/* making message payload */
	payload.req_num = ctrl->linksignal_req_num;
	payload.gpb_saddr = req->buf.addr;
	payload.gpb_eaddr = req->buf.addr + req->buf.size;
	payload.filter_value = req->pattern.value;
	payload.filter_mask = req->pattern.mask;
	payload.filter_noteq = req->pattern.noteq;
	payload.plpid_value = req->plpid_val;
	payload.plpid_mask = req->plpid_mask;
	payload.plpid_noteq = req->plpid_noteq;

	if (req->flags & LX_ATSC3_FLT_FLAG_ONESHOT)
		payload.oneshot = true;
	else
		payload.oneshot = false;

	/* payload length */
	len = sizeof(IPC_ATSC3_LKS_REQ_PAYLOAD_T);

	/* request to mcu */
	ret = TE_IPC_RequestATSC3Filter(channel->num, IPC_ATSC3_FILTER_TYPE_LKS,
					f->idx, len, &payload);
	CHECK_ERROR(ret < 0, goto error,
		    "Error(%d) in TE_IPC_RequestATSC3Filter", ret);

	/* save requested info */
	f->request_num = ctrl->linksignal_req_num;
	f->buffer.start = req->buf.addr;
	f->buffer.end = req->buf.addr + req->buf.size;
	f->buffer.rptr = req->buf.addr;
	f->buffer.wptr = req->buf.addr;
	f->flags = req->flags;
	f->priv = req->priv;
	f->filter = req->pattern;
	f->plpid_val = req->plpid_val;
	f->plpid_mask = req->plpid_mask;
	f->plpid_noteq = req->plpid_noteq;

	f->owner = priv;	//owner marking

	ctrl->linksignal_req_num++;

	log_filter("allocated memory(idx: %d): [0x%08x ~ 0x%08x]",
		   f->idx, req->buf.addr, req->buf.addr + req->buf.size);
	return f;

 error:
	if (f)
		free_filter(channel, LX_ATSC3_FILTER_TYPE_LINKSIGNAL, f);

	return NULL;
}

static IP_FILTER_T *IP_Request(struct atsc3_channel *channel,
			       void *priv, LX_ATSC3_FLT_IP_REQ_T *req)
{
	IP_FILTER_T *f;
	struct atsc3_dev_filter *fdev = &channel->dev->filter;
	IPC_ATSC3_IP_REQ_PAYLOAD_T payload;
	u32 mem_addr;
	int ret;
	u32 len;
#define IP_BUF_SIZE		(256*1024)

	f = alloc_filter(channel, LX_ATSC3_FILTER_TYPE_IP, req);
	CHECK_ERROR(!f, return NULL, "fail to alloc ipf");

	mem_addr = te_mem_alloc(fdev->mem, IP_BUF_SIZE, "atsc3_ip");
	CHECK_ERROR(!mem_addr, goto error, "can't alloc memory\n");

	memset(&payload, 0, sizeof(payload));	//set to zero

	/* making message payload */
	memcpy(payload.src_ip, req->src_ip, IPC_MAX_IP_LEN);
	memcpy(payload.dst_ip, req->dst_ip, IPC_MAX_IP_LEN);

	/* set gpb */
	payload.ipbuf_saddr = mem_addr;
	payload.ipbuf_eaddr = mem_addr + IP_BUF_SIZE;

	/* payload length */
	len = sizeof(IPC_ATSC3_IP_REQ_PAYLOAD_T);

	/* request to mcu */
	ret = TE_IPC_RequestATSC3Filter(channel->num, IPC_ATSC3_FILTER_TYPE_IP,
					f->idx, len, &payload);
	CHECK_ERROR(ret < 0, goto error,
		    "Error(%d) in TE_IPC_RequestATSC3Filter", ret);

	/* save requested info */
	f->buffer.start = mem_addr;
	f->buffer.end = mem_addr + IP_BUF_SIZE;
	f->buffer.rptr = f->buffer.start;
	f->buffer.wptr = f->buffer.start;
	f->owner = priv;	//owner marking

	log_filter("allocated memory(idx: %d): [0x%08x ~ 0x%08x]",
		   f->idx, mem_addr, mem_addr + IP_BUF_SIZE);
	return f;

 error:
	if (mem_addr) {
		te_mem_free(fdev->mem, mem_addr);
		f->buffer.start = 0;
	}
	if (f)
		free_filter(channel, LX_ATSC3_FILTER_TYPE_IP, f);

	return NULL;
}

static UDP_FILTER_T *UDP_Request(struct atsc3_channel *channel,
				 void *priv, LX_ATSC3_FLT_UDP_REQ_T *req)
{
	struct atsc3_filter_channel *ctrl = &(channel->filter);
	IPC_ATSC3_UDP_REQ_INFO_T info;	//for common handling
	LX_ATSC3_PAYLOAD_INFO_T *cp_ptr = NULL;	//code pointer address
	u32 ipc_srcflow_paddr = 0;	//temporal space for ipc send
	IPC_ATSC3_FILTER_TYPE_T type;
	UDP_FILTER_T *f;
	IP_FILTER_T *ipf;
	u32 len;
	int ret;

	ret = check_filter_paddr_range(priv, req->buf.addr, req->buf.size);
	if (ret)
		return NULL;

	ipf = get_filter_from_idx(channel, LX_ATSC3_FILTER_TYPE_IP,
				  req->up_idx);
	CHECK_ERROR(!ipf, return NULL, "not allocated ip filter(%d)",
		    req->up_idx);

	f = alloc_filter(channel, LX_ATSC3_FILTER_TYPE_UDP, req);
	CHECK_ERROR(!f, return NULL, "can't alloc udp filter");

	memset(&info, 0, sizeof(info));	//set to zero

	info.req_num = ctrl->udp_req_num;
	info.ip_idx = req->up_idx;
	info.dst_port = req->dst_port;
	info.gpb_saddr = req->buf.addr;
	info.gpb_eaddr = req->buf.addr + req->buf.size;

	if (req->flags & LX_ATSC3_FLT_FLAG_ONESHOT)
		info.oneshot = true;
	else
		info.oneshot = false;

	if (req->type == LX_ATSC3_UDPF_TYPE_LLS) {
		IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_LLS;

		/* Common UDP value */
		payload.info = info;

		/* LKS specific value */
		payload.filter_value = req->pattern.value;
		payload.filter_mask = req->pattern.mask;
		payload.filter_noteq = req->pattern.noteq;
		payload.plpid_value = req->lls.plpid_val;
		payload.plpid_mask = req->lls.plpid_mask;
		payload.plpid_noteq = req->lls.plpid_noteq;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_LLS_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(channel->num, type,
						f->idx, len, &payload);
		CHECK_ERROR(ret < 0, goto error,
			    "Err in TE_IPC_RequestATSC3Filter");

		f->pattern = req->pattern;
		f->lls.plpid_val = req->lls.plpid_val;
		f->lls.plpid_mask = req->lls.plpid_mask;
		f->lls.plpid_noteq = req->lls.plpid_noteq;
	} else if (req->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT ||
		   req->type == LX_ATSC3_UDPF_TYPE_ROUTE_SLS) {
		IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T payload;
		IPC_ATSC3_UDP_ROUTE_REQ_INFO_T *r_info = &(payload.route_info);	//ROUTE IPC msg
		LX_ATSC3_ROUTE_REQ_T *r_req = &(req->route);	//ROUTE request
		LX_ATSC3_PAYLOAD_INFO_T __user *user_payload =
		    te_ioctl_get_user_ptr(r_req->payload);

		memset(&payload, 0, sizeof(payload));	//set to zero

		if (req->type == LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT)	//check filter type
			type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ;
		else
			type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS;

		/* Common UDP value */
		payload.info = info;

		/* cp_ptr copy from user */
		if (r_req->payload_num) {
			u32 user_size = r_req->payload_num * sizeof(*cp_ptr);

			/* alloc srcflow mem */
			cp_ptr = kmalloc(user_size, GFP_KERNEL);
			CHECK_ERROR(cp_ptr == NULL, goto error,
				    "can't alloc memory");

			if (copy_from_user(cp_ptr, (void __user *)user_payload,
					   user_size)) {
				log_error("copy_from_user fail");
				goto error;
			}
		}

		/* ROUTE common information: including ipc_srcflow pointer */
		/* r_info->cp_addr should be freed after this function */
		ret = UDP_MakeROUTEInfo(channel->dev, r_info, cp_ptr,
					r_req->payload_num, r_req->tsi,
					r_req->ignore_dup);
		CHECK_ERROR(ret < 0, goto error, "Error in MakeROUTEInfo");

		ipc_srcflow_paddr = r_info->cp_addr;	//for free process

		/* ROUTE Object specific value */
		payload.toi_value = req->pattern.value;
		payload.toi_mask = req->pattern.mask;
		payload.toi_noteq = req->pattern.noteq;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(channel->num, type,
						f->idx, len, &payload);
		CHECK_ERROR(ret < 0, goto error,
			    "Err in TE_IPC_RequestATSC3Filter");

		/* Register filter info */
		f->pattern = req->pattern;
		f->route.payload_num = r_req->payload_num;
		f->route.payload = cp_ptr;
		f->route.tsi = r_req->tsi;
		f->ignore_dup = r_req->ignore_dup;	//for EFDT
	} else if (req->type == LX_ATSC3_UDPF_TYPE_ROUTE_AV) {
		IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T payload;
		IPC_ATSC3_UDP_ROUTE_REQ_INFO_T *r_info = &(payload.route_info);	//ROUTE IPC msg
		LX_ATSC3_ROUTE_REQ_T *r_req = &(req->route);	//ROUTE request
		LX_ATSC3_PAYLOAD_INFO_T __user *user_payload =
		    te_ioctl_get_user_ptr(r_req->payload);

		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV;

		/* Common UDP value */
		payload.info = info;

		/* cp_ptr copy from user */
		if (r_req->payload_num) {
			u32 user_size = r_req->payload_num * sizeof(*cp_ptr);

			/* alloc srcflow mem */
			cp_ptr = kmalloc(user_size, GFP_KERNEL);
			CHECK_ERROR(cp_ptr == NULL, goto error,
				    "can't alloc memory");

			if (copy_from_user(cp_ptr, (void __user *)user_payload,
					   user_size)) {
				log_error("copy_from_user fail");
				goto error;
			}
		}

		/* ROUTE common information: including ipc_srcflow pointer */
		/* r_info->cp_addr should be freed after this function */
		ret = UDP_MakeROUTEInfo(channel->dev, r_info, cp_ptr,
					r_req->payload_num, r_req->tsi,
					r_req->ignore_dup);
		CHECK_ERROR(ret < 0, goto error, "Error in MakeROUTEInfo");

		ipc_srcflow_paddr = r_info->cp_addr;	//for free process

		/* ROUTE AV specific value */
		payload.init_toi = r_req->av.init_toi;
		payload.num_start = r_req->av.num_start;

		/* payload length */
		len = sizeof(IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(channel->num, type,
						f->idx, len, &payload);
		CHECK_ERROR(ret < 0, goto error,
			    "Err in TE_IPC_RequestATSC3Filter");

		/* Register filter info */
		f->route.init_toi = r_req->av.init_toi;
		f->route.num_start = r_req->av.num_start;
		f->route.payload_num = r_req->payload_num;
		f->route.payload = cp_ptr;
		f->route.tsi = r_req->tsi;
		f->ignore_dup = r_req->ignore_dup;	//for EFDT
	} else if (req->type == LX_ATSC3_UDPF_TYPE_MMT_SIGNAL) {
		IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_MMT_SIGNAL;

		payload.info = info;
		payload.packet_id = req->mmt.packet_id;
		payload.msg_value = req->pattern.value;
		payload.msg_mask = req->pattern.mask;
		payload.msg_noteq = req->pattern.noteq;
		payload.table_value = req->mmt.table.value;
		payload.table_mask = req->mmt.table.mask;
		payload.table_noteq = req->mmt.table.noteq;
		payload.content_value = req->mmt.content.value;
		payload.content_mask = req->mmt.content.mask;
		payload.content_noteq = req->mmt.content.noteq;

		len = sizeof(IPC_ATSC3_UDP_MMT_SIGNAL_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(channel->num, type,
						f->idx, len, &payload);
		CHECK_ERROR(ret < 0, goto error,
			    "Err in TE_IPC_RequestATSC3Filter");

		f->mmt.packet_id = req->mmt.packet_id;
		f->pattern = req->pattern;
		f->mmt.table = req->mmt.table;
		f->mmt.content = req->mmt.content;
	} else if (req->type == LX_ATSC3_UDPF_TYPE_MMT_AV) {
		IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T payload;
		memset(&payload, 0, sizeof(payload));	//set to zero

		type = IPC_ATSC3_FILTER_TYPE_UDP_MMT_AV;

		payload.info = info;
		payload.packet_id = req->mmt.packet_id;

		len = sizeof(IPC_ATSC3_UDP_MMT_AV_REQ_PAYLOAD_T);

		ret = TE_IPC_RequestATSC3Filter(channel->num, type,
						f->idx, len, &payload);
		CHECK_ERROR(ret < 0, goto error,
			    "Err in TE_IPC_RequestATSC3Filter");

		f->mmt.packet_id = req->mmt.packet_id;
	} else {
		log_error("invalid filter type(%d)\n", req->type);
		goto error;
	}

	/* save requested info */
	f->ch = channel->num;
	f->request_num = ctrl->udp_req_num;
	f->ip_filter = ipf;
	f->dst_port = req->dst_port;

	f->buffer.start = req->buf.addr;
	f->buffer.end = req->buf.addr + req->buf.size;
	f->buffer.rptr = req->buf.addr;
	f->buffer.wptr = req->buf.addr;

	f->flags = req->flags;
	f->priv = req->priv;
	f->type = req->type;
	f->owner = priv;	//owner marking

	ctrl->udp_req_num++;

	if (ipc_srcflow_paddr) {	//Free ipc temporal space
		te_mem_free(channel->dev->filter.mem, ipc_srcflow_paddr);
	}
	return f;

 error:
	if (cp_ptr)
		kfree(cp_ptr);

	if (ipc_srcflow_paddr)	//Free ipc temporal space
		te_mem_free(channel->dev->filter.mem, ipc_srcflow_paddr);

	if (f)
		free_filter(channel, LX_ATSC3_FILTER_TYPE_UDP, f);

	return NULL;

}

static int ioc_request_filter(struct atsc3_fh *fh, void *arg)
{
	struct atsc3_channel *channel = fh->channel;
	LX_ATSC3_FLT_REQUEST_PARAM_T *param = arg;
	struct atsc3_filter_channel *filter;
	bool first_channel = false;
	u8 ch;
	int ret, idx;

	ch = channel->num;
	filter = &channel->filter;

	if (!filter->enable) {	// filter channel should be opened first
		ret = enable_channel(channel);
		CHECK_ERROR(ret, return ret, "Err in enable_channel[%d]", ch);

		first_channel = true;
	}

	if (param->type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		LINKSIGNAL_FILTER_T *f;
		f = LINKSIGNAL_Request(channel, fh, param->linksignal);
		CHECK_ERROR(!f, goto error, "Error in LINKSIGNALF Request");

		idx = f->idx;
	} else if (param->type == LX_ATSC3_FILTER_TYPE_IP) {
		IP_FILTER_T *f;
		f = IP_Request(channel, fh, param->ip);
		CHECK_ERROR(!f, goto error, "Error in IPF Request");

		idx = f->idx;
	} else if (param->type == LX_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *f;
		f = UDP_Request(channel, fh, param->udp);
		CHECK_ERROR(!f, goto error, "Error in UDPF Request");

		idx = f->idx;
	} else {
		log_error("Request filter type error(%d)", param->type);
		goto error;
	}

	return idx;

 error:
	if (first_channel)
		disable_channel(channel);

	return -EIO;
}

static int GetFilterStatus(void *filter, LX_ATSC3_FLT_TYPE_T type, void *status)
{
	if (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		IPC_ATSC3_LKS_STATUS_T ipc_status;
		LX_ATSC3_FLT_LINKSIGNAL_STATUS_T *s = status;
		LINKSIGNAL_FILTER_T *f = filter;

		s->filter = f->filter;
		s->flags = f->flags;

		TE_IPC_GetATSC3FilterStatus(f->idx, IPC_ATSC3_FILTER_TYPE_LKS,
					    (void *)&ipc_status);
		s->req_num = ipc_status.request_num;
		s->ovf_cnt = ipc_status.overflow;

		//TODO: Check wptr initialization (IPC as well)
		if (ipc_status.gpb_wptr)
			f->buffer.wptr = ipc_status.gpb_wptr;	//Update Wptr
		s->buffer = f->buffer;
	} else if (type == LX_ATSC3_FILTER_TYPE_IP) {
		IPC_ATSC3_IP_STATUS_T ipc_status;
		LX_ATSC3_FLT_IP_STATUS_T *s = status;
		IP_FILTER_T *f = filter;

		s->buffer = f->buffer;

		memcpy(s->src_ip, f->src_ip, 4);
		memcpy(s->dst_ip, f->dst_ip, 4);

		TE_IPC_GetATSC3FilterStatus(f->idx, IPC_ATSC3_FILTER_TYPE_IP,
					    (void *)&ipc_status);
		s->req_num = 0x0;	//not used
	} else if (type == LX_ATSC3_FILTER_TYPE_UDP) {
		IPC_ATSC3_UDP_STATUS_T ipc_status;
		LX_ATSC3_FLT_UDP_STATUS_T *s = status;
		UDP_FILTER_T *f = filter;

		s->up_idx = f->ip_filter->idx;
		s->flags = f->flags;
		s->dst_port = f->dst_port;
		s->pattern = f->pattern;

		TE_IPC_GetATSC3FilterStatus(f->idx, IPC_ATSC3_FILTER_TYPE_UDP,
					    (void *)&ipc_status);

		s->req_num = ipc_status.request_num;
		s->is_mde = ipc_status.is_mde;
		s->ovf_cnt = ipc_status.overflow;
		s->type = f->type;

		//TODO: Check wptr initialization (IPC as well)
		if (ipc_status.gpb_wptr)
			f->buffer.wptr = ipc_status.gpb_wptr;	//Update Wptr
		s->buffer = f->buffer;

		switch (f->type) {
		case LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT:
			s->route.tsi = f->route.tsi;
			s->route.ignore_dup = f->ignore_dup;
			break;
		case LX_ATSC3_UDPF_TYPE_ROUTE_AV:
			s->route.tsi = f->route.tsi;
			s->route.init_toi = f->route.init_toi;
			s->route.num_start = f->route.num_start;
			break;
		case LX_ATSC3_UDPF_TYPE_MMT_SIGNAL:
			s->mmt.packet_id = f->mmt.packet_id;
			s->mmt.table = f->mmt.table;
			s->mmt.content = f->mmt.content;
			break;
		case LX_ATSC3_UDPF_TYPE_MMT_AV:
			s->mmt.packet_id = f->mmt.packet_id;
			break;
		case LX_ATSC3_UDPF_TYPE_LLS:
		default:
			break;
		}
	} else {
		return -EINVAL;
	}

	return 0;
}

static int ioc_get_filter_status(struct atsc3_fh *fh, void *arg)
{
	struct atsc3_channel *channel = fh->channel;
	LX_ATSC3_FLT_STATUS_PARAM_T *param = arg;
	void *f;
	int ret;

	f = get_filter_from_idx(channel, param->type, param->idx);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(type: %d, idx: %d)",
		    param->type, param->idx);

	ret = GetFilterStatus(f, param->type, param->status);

	return ret;
}

static int FILTER_Cancel(struct atsc3_channel *channel, u8 type, u8 idx)
{
	struct atsc3_filter_channel *ctrl;
	IPC_MSG_ATSC3_FLT_CANCEL_T msg;
	void *f;
	int ret;

	ctrl = &(channel->filter);
	CHECK_ERROR(!ctrl, return -EINVAL, "invalid ch(%d)", channel->num);

	f = get_filter_from_idx(channel, type, idx);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(%d)", idx);

	memset(&msg, 0, sizeof(msg));	//make zero

	switch (type) {
	case LX_ATSC3_FILTER_TYPE_LINKSIGNAL:
		msg.type = IPC_ATSC3_FILTER_TYPE_LKS;
		break;
	case LX_ATSC3_FILTER_TYPE_IP:
		msg.type = IPC_ATSC3_FILTER_TYPE_IP;
		break;
	case LX_ATSC3_FILTER_TYPE_UDP:
		msg.type = IPC_ATSC3_FILTER_TYPE_UDP;
		break;
	default:
		log_error("unknown type(%d)", type);
		return -EINVAL;
	}

	msg.ch = channel->num;
	msg.flt_idx = idx;

	/* request to mcu */
	ret = TE_IPC_CancelATSC3Filter(&msg);
	CHECK_ERROR(ret < 0,, "Error(%d) in TE_IPC_CancelFilter", ret);

	ret = free_filter(channel, type, f);
	CHECK_ERROR(ret < 0,, "Error(%d) in free_filter", ret);

	/* delete msg in notify queue */
	if (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL
	    || type == LX_ATSC3_FILTER_TYPE_UDP) {
		LX_ATSC3_NOTIFY_TYPE_T noti_type;

		noti_type = (type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) ?
		    LX_ATSC3_NOTIFY_LINKSIGNAL_FILTER :
		    LX_ATSC3_NOTIFY_UDP_FILTER;

		atsc3_add_msg_status(channel->dev, noti_type, idx,
				     LX_ATSC3_FLT_STATE_DELETED);
	}

	if (list_empty(&ctrl->linksignal_head) == true
	    && list_empty(&ctrl->ip_head) == true) {
		ret = disable_channel(channel);
		CHECK_ERROR(ret != 0,, "Error in disable_channel[%d]", ret);
	}

	return 0;
}

static int ioc_cancel_filter(struct atsc3_fh *fh, void *arg)
{
	LX_ATSC3_FLT_CANCEL_PARAM_T *param = arg;

	return FILTER_Cancel(fh->channel, param->type, param->idx);
}

static int ioc_set_rptr(struct atsc3_fh *fh, void *arg)
{
	int ret;
	struct atsc3_channel *channel = fh->channel;
	LX_ATSC3_FLT_SET_RPTR_T *param = arg;
	void *f;
	u8 *ovf_status = NULL;
	u8 type;
	u32 rptr;

	f = get_filter_from_idx(channel, param->type, param->idx);
	CHECK_ERROR(!f, return -EINVAL, "no matched filter(type:%d, idx:%d)",
		    param->type, param->idx);

	rptr = param->rptr;

	if (param->type == LX_ATSC3_FILTER_TYPE_LINKSIGNAL) {
		LINKSIGNAL_FILTER_T *linksignal = f;

		type = IPC_ATSC3_FILTER_TYPE_LKS;
		linksignal->buffer.rptr = rptr;
		ovf_status = &linksignal->ovf_status;
	} else if (param->type == LX_ATSC3_FILTER_TYPE_UDP) {
		UDP_FILTER_T *udp = f;

		type = IPC_ATSC3_FILTER_TYPE_UDP;
		udp->buffer.rptr = rptr;
		ovf_status = &udp->ovf_status;
	} else {
		log_error("Invalid type [%d]", param->type);
		return -EINVAL;
	}

	ret = TE_IPC_SetATSC3FilterRptr(param->idx, type, rptr);
	CHECK_ERROR(ret < 0,, "Error(%d) in TE_IPC_SetATSC3Rptr", ret);

	if (ovf_status != NULL && *ovf_status == OVERFLOW_ERR_OVERLAPS) {
		*ovf_status = OVERFLOW_OK;
	}

	return ret;
}

/* DEBUG Functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

static const char *overflow_status_str(u8 status)
{
	switch (status) {
	case OVERFLOW_OK:
		return "OK";
	case OVERFLOW_ERR_SMALLBUF:
		return "ERR_SMALLBUF";
	case OVERFLOW_ERR_OVERLAPS:
		return "ERR_OVERLAPS";
	default:
		return "UNKNOWN";
	}
}

static void show_linksignal_filter_status(struct seq_file *m,
					  LINKSIGNAL_FILTER_T *f)
{
	u32 size = f->buffer.end - f->buffer.start;

	dprintf("[%03d]   CH[%d]\n", f->idx, f->ch);

	dprintf("\tVALUE\t\t[%08x]\n", f->filter.value);
	dprintf("\tMASK\t\t[%08x]\n", f->filter.mask);
	dprintf("\tNOT EQUAL\t[%08x]\n", f->filter.noteq);
	dprintf("\tREQ_NUM\t\t[%d]\n", f->request_num);
	dprintf("\tFLAGS\t\t[%s]\n", (f->flags & LX_ATSC3_FLT_FLAG_ONESHOT) ?
		"ONE_SHOT" : "CONTINUOUS");

	dprintf("\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n",
		f->buffer.start, f->buffer.end, size >> 10);
	dprintf("\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
		f->buffer.wptr, f->buffer.rptr,
		((f->buffer.wptr + size - f->buffer.rptr) % size) >> 10);
	dprintf("\tOVERFLOW\tSTATUS[%s] CNT[%d]\n",
		overflow_status_str(f->ovf_status), f->ovf_cnt);

	dprintf("\n");
}

static void show_ip_filter_status(struct seq_file *m, IP_FILTER_T *ipf)
{
	u32 size = ipf->buffer.end - ipf->buffer.start;

	dprintf("[%03d]   CH[%d]\n", ipf->idx, ipf->ch);

	dprintf("\tSRC IP\t\t%d.%d.%d.%d\n",
		ipf->src_ip[0], ipf->src_ip[1], ipf->src_ip[2], ipf->src_ip[3]);
	dprintf("\tDST IP\t\t%d.%d.%d.%d\n", ipf->dst_ip[0],
		ipf->dst_ip[1], ipf->dst_ip[2], ipf->dst_ip[3]);

	dprintf("\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n",
		ipf->buffer.start, ipf->buffer.end, size >> 10);
	dprintf("\n");
}

static void show_udp_filter_status(struct seq_file *m, UDP_FILTER_T *f)
{
	u32 size = f->buffer.end - f->buffer.start;
	int i;

	dprintf("[%03d]   CH[%d]\n", f->idx, f->ch);

	dprintf("\tIPF IDX\t\t[%02d]\n", f->ip_filter->idx);

	dprintf("\tREQ_NUM\t\t[%d]\n", f->request_num);
	dprintf("\tFLAGS\t\t[%s]\n", (f->flags & LX_ATSC3_FLT_FLAG_ONESHOT) ?
		"ONE_SHOT" : "CONTINUOUS");
	dprintf("\tDST PORT\t[%d]\n", f->dst_port);

	dprintf("\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n",
		f->buffer.start, f->buffer.end, size >> 10);
	dprintf("\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
		f->buffer.wptr, f->buffer.rptr,
		((f->buffer.wptr + size - f->buffer.rptr) % size) >> 10);
	dprintf("\tOVERFLOW\tSTATUS[%s] CNT[%d]\n",
		overflow_status_str(f->ovf_status), f->ovf_cnt);

	switch (f->type) {
	case LX_ATSC3_UDPF_TYPE_LLS:
		dprintf("\tFILTER TYPE\t[LLS]\n");
		dprintf("\tVALUE\t\t[%08x]\n", f->pattern.value);
		dprintf("\tMASKE\t\t[%08x]\n", f->pattern.mask);
		dprintf("\tNOT EQUAL\t[%08x]\n", f->pattern.noteq);
		break;

	case LX_ATSC3_UDPF_TYPE_ROUTE_OBJECT:
	case LX_ATSC3_UDPF_TYPE_ROUTE_SLS:
		dprintf("\tFILTER TYPE\t[ROUTE OBJ]\n");
		dprintf("\tIGNORE DUP\t[%s]\n", (f->ignore_dup) ? "YES" : "NO");
		dprintf("\tTSI\t\t[%d]\n", f->route.tsi);
		dprintf("\tTOI VALUE\t[0x%08x]\n", f->pattern.value);
		dprintf("\tTOI MASK\t[0x%08x]\n", f->pattern.mask);
		dprintf("\tTOI NOTEQ\t[0x%08x]\n", f->pattern.noteq);
		dprintf("\tPAYLOAD NUM\t[%d]\n", f->route.payload_num);
		for (i = 0; i < f->route.payload_num; i++) {
			if (i == 0)
				dprintf("\tPAYLOAD INFO");
			else
				dprintf("\t\t");
			dprintf("\t[%03d] CP[%d], FEC[%d]\n",
				i, f->route.payload[i].code_point,
				f->route.payload[i].fec_payload_id);
		}
		break;

	case LX_ATSC3_UDPF_TYPE_ROUTE_AV:
		dprintf("\tFILTER TYPE\t[ROUTE AV]\n");
		dprintf("\tTSI\t\t[%d]\n", f->route.tsi);
		dprintf("\tINIT TOI\t[%d]\n", f->route.init_toi);
		dprintf("\tNUM START\t[%d]\n", f->route.num_start);
		dprintf("\tPAYLOAD NUM\t[%d]\n", f->route.payload_num);
		for (i = 0; i < f->route.payload_num; i++) {
			if (i == 0)
				dprintf("\tPAYLOAD INFO");
			else
				dprintf("\t\t");
			dprintf("\t[%03d] CP[%d], FEC[%d]\n",
				i, f->route.payload[i].code_point,
				f->route.payload[i].fec_payload_id);
		}
		break;

	case LX_ATSC3_UDPF_TYPE_MMT_SIGNAL:
		dprintf("\tFILTER TYPE\t[MMT SLS]\n");
		dprintf("\tPACKET ID\t[%d]\n", f->mmt.packet_id);

		dprintf("\tMSG VALUE\t[%08x]\n", f->pattern.value);
		dprintf("\tMSG MASK\t[%08x]\n", f->pattern.mask);
		dprintf("\tMSG NOT_EQ\t[%08x]\n", f->pattern.noteq);

		dprintf("\tTABLE VALUE\t[%08x]\n", f->mmt.table.value);
		dprintf("\tTABLE MASK\t[%08x]\n", f->mmt.table.mask);
		dprintf("\tTABLE NOT_EQ\t[%08x]\n", f->mmt.table.noteq);

		dprintf("\tCONTENT VALUE\t[%08x]\n", f->mmt.content.value);
		dprintf("\tCONTENT MASK\t[%08x]\n", f->mmt.content.mask);
		dprintf("\tCONTENT NOT_EQ\t[%08x]\n", f->mmt.content.noteq);
		break;

	case LX_ATSC3_UDPF_TYPE_MMT_AV:
		dprintf("\tFILTER TYPE\t[MMT AV]\n");
		dprintf("\tPACKET ID\t[%d]\n", f->mmt.packet_id);
		break;

	case LX_ATSC3_UDPF_TYPE_MAX:
	default:
		dprintf("Invalid UDP Filter Type[%d]", f->type);
		break;
	}
	dprintf("\n");
}

static int debug_show_filter_status(struct atsc3_device *dev,
				    struct seq_file *m)
{
	int i;
	struct atsc3_channel *channel;
	struct atsc3_filter_channel *filter;
	struct atsc3_filter_buffer *buf;
	struct atsc3_dev_filter *fdev = &dev->filter;
	int num_enable_channels = 0;

	dprintf("Filter Status\n");

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		filter = &channel->filter;

		dprintf("CH [%d]", channel->num);
		if (!filter->enable) {
			dprintf("\tDisabled\n");
			continue;
		}
		num_enable_channels++;

		buf = &filter->buffer;
		dprintf("\tMETA\t\t[0x%08x--0x%x] %dKB\n",
			buf->metabuf_saddr, buf->metabuf_eaddr,
			(buf->metabuf_eaddr - buf->metabuf_saddr) >> 10);
		dprintf("\tDATA\t\t[0x%08x--0x%x] %dKB\n",
			buf->databuf_saddr, buf->databuf_eaddr,
			(buf->databuf_eaddr - buf->databuf_saddr) >> 10);
		dprintf("\tBB\t\t[0x%08x--0x%x] %dKB\n",
			buf->bbbuf_saddr, buf->bbbuf_eaddr,
			(buf->bbbuf_eaddr - buf->bbbuf_saddr) >> 10);
		dprintf("\n");
	}

	if (!num_enable_channels)
		return 0;

	dprintf("\nLINKSIGNAL Filter\n");
	for (i = 0; i < fdev->num_linksignalf; i++) {
		LINKSIGNAL_FILTER_T *f = &fdev->linksignalf[i];
		if (f->used)
			show_linksignal_filter_status(m, f);
	}

	dprintf("\nIP Filter\n");
	for (i = 0; i < fdev->num_ipf; i++) {
		IP_FILTER_T *f = &fdev->ipf[i];
		if (f->used)
			show_ip_filter_status(m, f);
	}

	dprintf("\nUDP Filter\n");
	for (i = 0; i < fdev->num_udpf; i++) {
		UDP_FILTER_T *f = &fdev->udpf[i];
		if (f->used)
			show_udp_filter_status(m, f);
	}

	return 0;
}

static const char *mcu_filter_status_str(u8 status)
{
	switch (status) {
	case 0:
		return "IDLE";
	case 1:
		return "WORKING";
	case 2:
		return "WAIT_CANCEL";
	default:
		return "UNKNOWN";
	}
}

static void show_mcu_filter_status(struct seq_file *m, u8 type, u8 idx)
{
#define IF_ERR_DISPLAY(v,title) \
do{ if (v) dprintf(TE_COLOR_RED"\t" title "[%u]\n" TE_COLOR_NONE, v); } while(0)

	if (type == IPC_ATSC3_FILTER_TYPE_PLP) {
		IPC_ATSC3_PLP_STATUS_T s;

		TE_IPC_GetATSC3FilterStatus(idx, type, &s);
		if (s.status == 0)
			return;

		dprintf("[%03d]   STATUS[%s] PLP_ID[%d] PKT[%u]\n",
			idx, mcu_filter_status_str(s.status),
			s.plp_id, s.packet_cnt);

		IF_ERR_DISPLAY(s.cc_err_cnt, "CC_ERR");
		IF_ERR_DISPLAY(s.extmode_err_cnt, "EXTMOD_ERR");
		IF_ERR_DISPLAY(s.pointer_err_cnt, "PTR_ERR");
		IF_ERR_DISPLAY(s.alp_header_err_cnt, "ALP_HDR_ERR");
	} else if (type == IPC_ATSC3_FILTER_TYPE_LKS) {
		IPC_ATSC3_LKS_STATUS_T s;

		TE_IPC_GetATSC3FilterStatus(idx, type, &s);
		if (s.status == 0)
			return;

		dprintf("[%03d]   STATUS[%s] REQ[%d] ", idx,
			mcu_filter_status_str(s.status), s.request_num);
		dprintf("W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);

		IF_ERR_DISPLAY(s.overflow, "OVF");
	} else if (type == IPC_ATSC3_FILTER_TYPE_IP) {
		IPC_ATSC3_IP_STATUS_T s;

		TE_IPC_GetATSC3FilterStatus(idx, type, &s);
		if (s.status == 0)
			return;

		dprintf("[%03d]   STATUS[%s] PKT[%u]\n", idx,
			mcu_filter_status_str(s.status), s.packet_cnt);

		IF_ERR_DISPLAY(s.vers4_err, "VERS4_ERR");
		IF_ERR_DISPLAY(s.not_udp, "NOT_UDP");
		IF_ERR_DISPLAY(s.hdr_len_err, "HDR_LEN");
		IF_ERR_DISPLAY(s.hdr_len_mismatch, "HDR_LEN_MISMATCH");
		IF_ERR_DISPLAY(s.frag_offset_err, "FRAG_OFFSET");
		IF_ERR_DISPLAY(s.frag_buf_ovf, "FRAG_BUF_OVF");
		IF_ERR_DISPLAY(s.chksum_err, "CHECKSUM_ERR");
	} else if (type == IPC_ATSC3_FILTER_TYPE_UDP) {
		IPC_ATSC3_UDP_STATUS_T s;

		TE_IPC_GetATSC3FilterStatus(idx, type, &s);
		if (s.status == 0)
			return;

		dprintf("[%03d]   STATUS[%s] REQ[%d] [%s] ",
			idx, mcu_filter_status_str(s.status),
			s.request_num,
			ipc_atsc3_filter_type_str(s.filter_type));

		dprintf("W[0x%08x] R[0x%08x] ", s.gpb_wptr, s.gpb_rptr);

		if (s.filter_type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ ||
		    s.filter_type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS ||
		    s.filter_type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV) {
			IPC_ATSC3_UDP_ROUTE_ERR_CNT_T *e = &s.route;

			dprintf("%s\n", (s.is_mde) ? "[MDE]" : "");
			IF_ERR_DISPLAY(s.overflow, "OVF");
			IF_ERR_DISPLAY(e->vers1_err, "VERS1_ERR");
			IF_ERR_DISPLAY(e->protocol_err, "PROTOCOL");
			IF_ERR_DISPLAY(e->flag_err, "FLAG");
			IF_ERR_DISPLAY(e->multi_objlen, "MULTI_OBJLEN");
			IF_ERR_DISPLAY(e->multi_sct, "MULTI_SCT");
			IF_ERR_DISPLAY(e->multi_prestime, "MULTI_PRES_TIME");
			IF_ERR_DISPLAY(e->no_ofs_len, "NO_OFFSET_LEN");
			IF_ERR_DISPLAY(e->unknown_obj, "UNKNOWN_OBJ");
			IF_ERR_DISPLAY(e->no_ofs_gathering, "NO_OFS_GATHERING");
			IF_ERR_DISPLAY(e->jump_next_toi, "JUMP_NEXT_TOI");
			IF_ERR_DISPLAY(e->ofs_rewind, "OFFSET_REWIND");
			IF_ERR_DISPLAY(e->skip_byte, "SKIP_BYTE");
			IF_ERR_DISPLAY(e->object_rollback, "OBJ_ROLLBACK");
		} else if (s.filter_type == IPC_ATSC3_FILTER_TYPE_UDP_MMT_SIGNAL
			   || s.filter_type ==
			   IPC_ATSC3_FILTER_TYPE_UDP_MMT_AV) {
			IPC_ATSC3_UDP_MMT_ERR_CNT_T *e = &s.mmt;

			IF_ERR_DISPLAY(s.overflow, "OVF");
			IF_ERR_DISPLAY(e->vers1_err, "VERS1_ERR");
			IF_ERR_DISPLAY(e->fec_protect_err, "FEC_PROTECT");
			IF_ERR_DISPLAY(e->seqnum_discnt, "SEQ_NUM_DISCNT");
			IF_ERR_DISPLAY(e->non_timed, "NON_TIMED");
			IF_ERR_DISPLAY(e->file_type_err, "FILE_TYPE");
			IF_ERR_DISPLAY(e->frag_discnt, "FRAG_DISCNT");
		} else if (s.filter_type == IPC_ATSC3_FILTER_TYPE_UDP_LLS) {
			IPC_ATSC3_UDP_LLS_ERR_CNT_T *e = &s.lls;

			IF_ERR_DISPLAY(s.overflow, "OVF");
			IF_ERR_DISPLAY(e->old_lls_cnt, "OLD_LLS_CNT");
		} else {
			dprintf("UNKNOWN TYPE[%x]\n", s.filter_type);
		}
	} else {
		dprintf("Filter type error[0x%02x]\n", type);
	}
}

static int debug_show_mcu_filter_status(struct atsc3_device *dev,
					struct seq_file *m)
{
	int i, ret;
	struct atsc3_channel *channel;
	struct atsc3_filter_channel *filter;
	IPC_ATSC3_CH_STATUS_T ch_status;
	struct atsc3_dev_filter *fdev = &dev->filter;
	int num_enable_channels = 0;

	dprintf("MCU Filter Status\n");
	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];
		filter = &channel->filter;
		dprintf("CH[%d] : ", channel->num);
		if (!filter->enable) {
			dprintf("Disabled\n");
			continue;
		}
		num_enable_channels++;

		ret = TE_IPC_GetATSC3ChannelStatus(i, &ch_status);
		if (ret) {
			dprintf("can't read status register\n");
			continue;
		}
		dprintf("PKT[%u] ERR[%u]\n",
			ch_status.packet_cnt, ch_status.err_packet_cnt);
	}

	if (!num_enable_channels)
		return 0;

	dprintf("\n[PLP]\n");
	for (i = 0; i < fdev->num_plpf; i++) {
		show_mcu_filter_status(m, IPC_ATSC3_FILTER_TYPE_PLP, i);
	}
	dprintf("\n[LKS]\n");
	for (i = 0; i < fdev->num_linksignalf; i++) {
		show_mcu_filter_status(m, IPC_ATSC3_FILTER_TYPE_LKS, i);
	}
	dprintf("\n[IP]\n");
	for (i = 0; i < fdev->num_linksignalf; i++) {
		show_mcu_filter_status(m, IPC_ATSC3_FILTER_TYPE_IP, i);
	}
	dprintf("\n[UDP]\n");
	for (i = 0; i < fdev->num_udpf; i++) {
		show_mcu_filter_status(m, IPC_ATSC3_FILTER_TYPE_UDP, i);
	}
	dprintf("\n");

	return 0;
}

static void init_debug(struct atsc3_device *dev)
{
	atsc3_debug_register_status_show(dev, ATSC3_DEBUG_STATUS_FILTER,
					 debug_show_filter_status);
	atsc3_debug_register_status_show(dev, ATSC3_DEBUG_STATUS_MCU_FILTER,
					 debug_show_mcu_filter_status);
}

/* atsc3 sub driver */

static int filter_dev_ioctl_param(void *priv, unsigned int cmd, void *arg,
				  struct te_ioctl_ptr_param *param)
{
	int ret = 0;

	if (cmd == ATSC3_IOC_FLT_REQUEST) {
		LX_ATSC3_FLT_REQUEST_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->filter);
		param->kernel_ptr = (void **)&p->filter;
		param->dir = _IOC_WRITE;

		switch (p->type) {
		case LX_ATSC3_FILTER_TYPE_LINKSIGNAL:
			param->size = sizeof(LX_ATSC3_FLT_LINKSIGNAL_REQ_T);
			break;
		case LX_ATSC3_FILTER_TYPE_IP:
			param->size = sizeof(LX_ATSC3_FLT_IP_REQ_T);
			break;
		case LX_ATSC3_FILTER_TYPE_UDP:
			param->size = sizeof(LX_ATSC3_FLT_UDP_REQ_T);
			break;
		default:
			ret = -EINVAL;
		}
	} else if (cmd == ATSC3_IOC_FLT_GET_STATUS) {
		LX_ATSC3_FLT_STATUS_PARAM_T *p = arg;

		param->user_ptr = te_ioctl_get_user_ptr(p->status);
		param->kernel_ptr = (void **)&p->status;
		param->dir = _IOC_READ;

		switch (p->type) {
		case LX_ATSC3_FILTER_TYPE_LINKSIGNAL:
			param->size = sizeof(LX_ATSC3_FLT_LINKSIGNAL_STATUS_T);
			break;
		case LX_ATSC3_FILTER_TYPE_IP:
			param->size = sizeof(LX_ATSC3_FLT_IP_STATUS_T);
			break;
		case LX_ATSC3_FILTER_TYPE_UDP:
			param->size = sizeof(LX_ATSC3_FLT_UDP_STATUS_T);
			break;
		default:
			ret = -EINVAL;
			break;
		}
	}

	return ret;
}

static int filter_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	const struct atsc3_ioctl_info ioctls[] = {
		IOC_INFO(ATSC3_IOC_FLT_REQUEST, ioc_request_filter),
		IOC_INFO(ATSC3_IOC_FLT_CANCEL, ioc_cancel_filter),
		IOC_INFO(ATSC3_IOC_FLT_GET_STATUS, ioc_get_filter_status),
		IOC_INFO(ATSC3_IOC_FLT_SET_RPTR, ioc_set_rptr),
	};

	return atsc3_do_ioctl(priv, cmd, arg, filter_lock, ioctls);
}

static void filter_dev_close(struct atsc3_fh *fh)
{
	LINKSIGNAL_FILTER_T *linksignalf, *linksignalf_next;
	IP_FILTER_T *ipf, *ipf_next;
	UDP_FILTER_T *udpf, *udpf_next;
	struct atsc3_channel *channel = fh->channel;
	struct atsc3_filter_channel *ctrl;
	int ret;

	if (!channel)
		return;

	ctrl = &channel->filter;

	mutex_lock(&filter_lock);

	list_for_each_entry_safe(udpf, udpf_next, &ctrl->udp_head, list) {
		if (udpf->owner == fh) {
			log_error("UDP[%d] is still running (Force stop)",
				  udpf->idx);

			ret = FILTER_Cancel(channel, LX_ATSC3_FILTER_TYPE_UDP,
					    udpf->idx);
			CHECK_ERROR(ret < 0,, "Err in FILTER_Cancel");
		}
	}

	list_for_each_entry_safe(ipf, ipf_next, &ctrl->ip_head, list) {
		if (ipf->owner == fh) {
			log_error("IP[%d] is still running (Force stop)",
				  ipf->idx);

			ret = FILTER_Cancel(channel, LX_ATSC3_FILTER_TYPE_IP,
					    ipf->idx);
			CHECK_ERROR(ret < 0,, "Err in FILTER_Cancel");
		}
	}

	list_for_each_entry_safe(linksignalf, linksignalf_next, &ctrl->ip_head,
				 list) {
		if (linksignalf->owner == fh) {
			log_error("LINKSIG[%d] is still running (Force stop)",
				  linksignalf->idx);

			ret = FILTER_Cancel(channel,
					    LX_ATSC3_FILTER_TYPE_LINKSIGNAL,
					    linksignalf->idx);
			CHECK_ERROR(ret < 0,, "Err in FILTER_Cancel");
		}
	}

	mutex_unlock(&filter_lock);
}

static int filter_dev_suspend(struct atsc3_device *dev)
{
	/* disconnect filter callback */
	TE_IPC_RegisterATSC3FilterCallback(NULL, NULL);

	/* remove remained callback works */
	reset_filter_callback_work(&dev->filter);

	return 0;
}

static int filter_dev_resume(struct atsc3_device *dev)
{
	int ret;

	/* reconnect filter callback */
	TE_IPC_RegisterATSC3FilterCallback(ipc_filter_callback, dev);

	ret = recovery_filter(dev);

	return ret;
}

static int filter_dev_init(struct atsc3_device *dev)
{
	int i, ret;
	struct atsc3_dev_filter *fdev = &dev->filter;

	fdev->num_plpf = dev->cfg->num_plpf;
	fdev->num_linksignalf = dev->cfg->num_linksignalf;
	fdev->num_ipf = dev->cfg->num_ipf;
	fdev->num_udpf = dev->cfg->num_udpf;

	fdev->linksignalf =
	    vzalloc(fdev->num_linksignalf * sizeof(LINKSIGNAL_FILTER_T));
	CHECK_ERROR(!fdev->linksignalf, return -ENOMEM, "can't alloc memory");

	fdev->ipf = vzalloc(fdev->num_ipf * sizeof(IP_FILTER_T));
	CHECK_ERROR(!fdev->num_ipf, return -ENOMEM, "can't alloc memory");

	fdev->udpf = vzalloc(fdev->num_udpf * sizeof(UDP_FILTER_T));
	CHECK_ERROR(!fdev->udpf, return -ENOMEM, "can't alloc memory");

	fdev->mem = te_mem_open(ATSC3_MEM_NAME);
	CHECK_ERROR(!fdev->mem, return -EIO, "can't open mem");

	/* filter callback */
	ret = te_msgbuf_init(&fdev->callback_buf,
			     sizeof(struct atsc3_filter_callback),
			     MAX_FILTER_CALLBACK, TE_BUF_FLAG_NO_EVENT);
	CHECK_ERROR(ret, return ret, "Err in te_msgbuf_init");

	INIT_WORK(&fdev->callback_work, filter_callback_work);

	for (i = 0; i < dev->num_channel; i++) {
		struct atsc3_filter_channel *f = &dev->channels[i].filter;

		INIT_LIST_HEAD(&f->linksignal_head);
		INIT_LIST_HEAD(&f->ip_head);
		INIT_LIST_HEAD(&f->udp_head);

		f->linksignal_req_num = 0;
		f->udp_req_num = 0;
	}

	TE_IPC_RegisterATSC3FilterCallback(ipc_filter_callback, dev);
	te_mcu_register_rcallback(get_te_device(dev),
				  TE_MCU_FUNC_TYPE_ATSC3,
				  mcu_recovery_pre_callback,
				  mcu_recovery_post_callback, dev);

	init_debug(dev);

	return 0;
}

static void filter_dev_release(struct atsc3_device *dev)
{

}

static const struct atsc3_ioctl ioctl_filter = {
	.magic = ATSC3_IOC_FLT_MAGIC,
	.func = filter_dev_ioctl,
	.get_user_param = filter_dev_ioctl_param,
};

const struct atsc3_sub_driver atsc3_filter_driver = {
	.name = "atsc3_filter",
	.init = filter_dev_init,
	.release = filter_dev_release,
	.suspend = filter_dev_suspend,
	.resume = filter_dev_resume,

	.close = filter_dev_close,
	.ioctl = &ioctl_filter,
};
