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

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include <lg1k/te/mcu.h>
#include <lg1k/te/ipc.h>

#include "arib2_impl.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/
/* Short Cuts */
static u8 num_tlvf;		/* number of tlv(si) filters */
static u8 num_ipf;		/* number of ip filters */
static u8 num_mmt_pidf;	/* number of mmt_pid filters */
static u8 num_mmt_sif;	/* number of mmt_si filters */
static u8 num_mmt_avf;	/* number of mmt_av filters */

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

#define IS_INVALID_BUFFER_ADDR(addr, buffer) \
	((addr) < (buffer)->start || (addr) >= (buffer)->end)

#define GET_FLT_TYPE(type) (type & 0xF0)

#define STATUS_PRINT(__seq_file,fmt,args...)	\
{											\
	if(__seq_file)							\
	{										\
		seq_printf(__seq_file,fmt,##args);	\
	} else {								\
		log_noti(fmt,##args);				\
	}										\
}


/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/
typedef struct
{
	u32				start;
	u32				end;
	u32				rptr;
	u32				wptr;
} BUF_TYPE_T;

typedef struct
{
	u8				used;
	u8				ch;
	u8				idx;
	u8				req_num;

	u16				flags;

	BUF_TYPE_T			buffer;
	LX_ARIB2_FLT_PATTERN_T	pattern;

	void				*priv;
	void				*owner;
	struct list_head	list;

	u8				ovf_status;
	u32				ovf_cnt;

} TLV_SI_FILTER_T;

typedef struct
{
	u8				used;
	u8				ch;
	u8				idx;
	u16				packet_id;

	BUF_TYPE_T			buffer; //MCU uses
	void				*owner;
	struct list_head	list;

} MMT_PID_FILTER_T;

typedef struct
{
	u8				used;
	u8				ch;
	u8				idx;
	u8				req_num;

	u16				flags;
	u16				message_id;

	BUF_TYPE_T			buffer;
	MMT_PID_FILTER_T	*mmt_pid_f;
	LX_ARIB2_FLT_PATTERN_T	pattern;

	void				*priv;
	void				*owner;
	struct list_head	list;

	u8				ovf_status;
	u32				ovf_cnt;

} MMT_SI_FILTER_T;

typedef struct
{
	u8				used;
	u8				ch;
	u8				idx;
	u8				req_num;

//	u16				flags; //TODO: Check necessity

	BUF_TYPE_T			buffer;
	MMT_PID_FILTER_T	*mmt_pid_f;

	void				*priv; //TODO: Check necessity
	void				*owner;
	struct list_head	list;

	u8				ovf_status;
	u32				ovf_cnt;

} MMT_AV_FILTER_T;

typedef struct
{
	struct list_head		list;
	IPC_MSG_ARIB2_DATA_T	data_msg;
} ARIB2_FILTER_CALLBACK_T;

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   global Functions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   global Variables
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Static Function Prototypes Declarations
 *---------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
 *   Static Variables
 *---------------------------------------------------------------------------------------*/

static DEFINE_MUTEX(filter_lock);

static struct te_mem_ctx	*filter_mm;
static TLV_SI_FILTER_T		*tlv_si_filters;
static MMT_PID_FILTER_T		*mmt_pid_filters;
static MMT_SI_FILTER_T		*mmt_si_filters;
static MMT_AV_FILTER_T		*mmt_av_filters;

#define filter_workqueue(channel)	(channel)->dev->workqueue

 /*========================================================================================
	 Implementation Group
 ========================================================================================*/
#if 0
static const char* GetOverflowStatusStr(UINT8 status)
{
	switch(status)
	{
		case IPC_DATA_STATUS_OK:						return "OK";
		case IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF:	return "ERR_SMALLBUF";
		case IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR:		return "ERR_OVERLAPS";
		default:										return "UNKNOWN";
	}
}
#endif

static const char* GetFilterTypeStr(u8 type)
{
	switch(type)
	{
		case IPC_ARIB2_FILTER_TYPE_TLV_SI:				return "TLV SI";
		case IPC_ARIB2_FILTER_TYPE_MMT_SI:				return "MMT SI";
		case IPC_ARIB2_FILTER_TYPE_MMT_AV:				return "MMT AV";
		case IPC_ARIB2_FILTER_TYPE_MMT_PID:				return "MMT PID";
		default:										return "UNKNOWN";
	}
}

static void* GetFilterWithIdx(struct arib2_channel_filter *ctrl, LX_ARIB2_FLT_TYPE_T type, u8 idx)
{
	switch(type)
	{
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f;

			list_for_each_entry(f, &ctrl->tlv_si_head, list)
			{
				if(f->idx == idx) return f;
			}
			break;
		}

		case LX_ARIB2_FILTER_TYPE_MMT_PID:
		{
			MMT_PID_FILTER_T *f;

			list_for_each_entry(f, &ctrl->mmt_pid_head, list)
			{
				if(f->idx == idx) return f;
			}
			break;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f;

			list_for_each_entry(f, &ctrl->mmt_si_head, list)
			{
				if(f->idx == idx) return f;
			}
			break;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f;

			list_for_each_entry(f, &ctrl->mmt_av_head, list)
			{
				if(f->idx == idx) return f;
			}
			break;
		}
		default:
			break;
	}

	return NULL;
}

static int CheckBufferValidation(u32 saddr, u32 eaddr, BUF_TYPE_T *buf)
{
	/* check data validation */
	if(saddr == eaddr) //empty
	{
		log_error("invalid address(EMPTY)(%08x--%08x), buffer(%08x--%08x)",
					saddr, eaddr, buf->start, buf->end);
		return -EFAULT;


	}
	else if(IS_INVALID_BUFFER_ADDR(saddr, buf) ||
			IS_INVALID_BUFFER_ADDR(eaddr, buf))
	{
		log_error("invalid address(RANGE OUT)(%08x--%08x), buffer(%08x--%08x)",
					saddr, eaddr, buf->start, buf->end);
		return -EFAULT;
	}

	return 0;
}

static int filter_receive_callback_work(struct arib2_channel_filter *ctrl, IPC_MSG_ARIB2_DATA_T *data)
{
	LX_ARIB2_NOTIFY_TYPE_T noti_type;
	LX_ARIB2_NOTIFY_DATA_T noti_param;
	LX_ARIB2_NOTIFY_FILTER_T *noti_filter;
	struct arib2_channel *channel;
	u32 saddr, eaddr;
	u8 flt_idx, flt_req_num;
	BUF_TYPE_T *flt_buf;
	void* flt_priv;
	int rc;

	/* Get Filter Information */
	switch(data->info.type)
	{
		case IPC_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_TLV_SI;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_TLV_SI, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused TLV SI filter index(%d)", data->info.flt_idx);

			flt_idx = f->idx;
			flt_priv = f->priv;
			flt_req_num = f->req_num;
			flt_buf = &f->buffer;
			break;
		}

		case IPC_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_MMT_SI;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_SI, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused MMT SI filter index(%d)", data->info.flt_idx);

			flt_idx = f->idx;
			flt_priv = f->priv;
			flt_req_num = f->req_num;
			flt_buf = &f->buffer;
			break;
		}

		case IPC_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_MMT_AV;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_AV, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused MMT AV filter index(%d)", data->info.flt_idx);

			flt_idx = f->idx;
			flt_priv = f->priv;
			flt_req_num = f->req_num;
			flt_buf = &f->buffer;
			break;
		}

		default:
		{
			log_error("invalid datatype[0x%02x]", data->info.type);
			return -EINVAL;
		}
	}

	/* Request num check */
	if(flt_req_num != data->info.req_num)
	{
		log_warning("not matched request type:%s f_num(%d): cb(%d)",
						GetFilterTypeStr(data->info.type), flt_req_num, data->info.req_num);
		return -EPERM;
	}

	channel = container_of(ctrl, struct arib2_channel, filter);

	saddr = data->info.data_saddr;
	eaddr = data->info.data_eaddr;

	rc = CheckBufferValidation(saddr, eaddr, flt_buf);
	CHECK_ERROR(rc != 0, return rc, "invalidate buffer");

	/* Make notify data */
	noti_param.type	= noti_type;

	noti_filter		= &noti_param.filter;
	noti_filter->ch	= channel->num;
	noti_filter->idx = flt_idx;
	noti_filter->rptr = saddr;
	noti_filter->wptr = eaddr;
	noti_filter->status = LX_ARIB2_FLT_STATE_DATAREADY;
	noti_filter->msec = te_get_ms_tick();
	noti_filter->priv = flt_priv;

	/* Additional Information for MMT AV filter */
	if(noti_type == LX_ARIB2_NOTIFY_MMT_AV)
	{
		LX_ARIB2_MMT_AV_INFO_T *info = &noti_filter->mmt_av;

		info->rap_f			= data->mmt_av.rap_f;
		info->timed			= data->mmt_av.timed;
		info->mpu_seq_num	= data->mmt_av.mpu_seq_number;
		info->item_id		= data->mmt_av.item_id;
		info->scr_ctrl		= data->mmt_av.scr_ctrl;

		memcpy(info->scr_init_counter, data->mmt_av.scr_init_counter, sizeof(u8) * 16);
	}

	rc = arib2_add_noti(channel->dev, &noti_param);

	return rc;
}

static const char* mcu_filter_status_str(u8 status)
{
	switch(status)
	{
		case 0:	return "IDLE";
		case 1: return "WORKING";
		case 2: return "WAIT_CANCEL";
		default: return "UNKNOWN";
	}
}

static void display_filter_status(IPC_ARIB2_FILTER_TYPE_T type, u8 idx)
{
	switch (type) {
	case IPC_ARIB2_FILTER_TYPE_TLV_SI: {
		IPC_ARIB2_TLV_SI_FILTER_STATUS_T s;

		TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_TLV_SI, &s);
		if (!s.status)
			break;

		log_noti("[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
				 idx, mcu_filter_status_str(s.status), s.request_num, s.overflow_cnt);
		log_noti("W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
		break;
	}
	case IPC_ARIB2_FILTER_TYPE_MMT_SI: {
		IPC_ARIB2_MMT_SI_FILTER_STATUS_T s;

		TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_MMT_SI, &s);
		if (!s.status)
			break;

		log_noti("[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
				idx, mcu_filter_status_str(s.status), s.request_num, s.overflow);
		log_noti("W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
		break;
	}
	case IPC_ARIB2_FILTER_TYPE_MMT_AV: {
		IPC_ARIB2_MMT_AV_FILTER_STATUS_T s;

		TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_MMT_AV, &s);
		if (!s.status)
			break;

		log_noti("[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
				idx, mcu_filter_status_str(s.status), s.request_num, s.overflow);
		log_noti("W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
		break;
	}
	default:
		break;
	}
}




static int filter_overflow_callback_work(struct arib2_channel_filter *ctrl, IPC_MSG_ARIB2_DATA_T *data)
{
	LX_ARIB2_NOTIFY_TYPE_T noti_type;
	u8 flt_ch, flt_idx;
	struct arib2_channel *channel;

	/* Get Filter Information */
	switch(data->info.type)
	{
		case IPC_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_TLV_SI;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_TLV_SI, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused TLV SI filter index(%d)", data->info.flt_idx);

			/* update overflow summary */
			f->ovf_cnt++;
			f->ovf_status = data->info.status;

			flt_ch = f->ch;
			flt_idx = f->idx;
			break;
		}
		case IPC_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_MMT_SI;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_SI, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused MMT SI filter index(%d)", data->info.flt_idx);

			/* update overflow summary */
			f->ovf_cnt++;
			f->ovf_status = data->info.status;

			flt_ch = f->ch;
			flt_idx = f->idx;
			break;
		}
		case IPC_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f;

			noti_type = LX_ARIB2_NOTIFY_MMT_AV;
			f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_AV, data->info.flt_idx);
			CHECK_ERROR(!f, return -EINVAL, "unused MMT AV filter index(%d)", data->info.flt_idx);

			/* update overflow summary */
			f->ovf_cnt++;
			f->ovf_status = data->info.status;

			flt_ch = f->ch;
			flt_idx = f->idx;
			break;
		}
		default:
		{
			log_error("invalid datatype[0x%02x]", data->info.type);
			return -EINVAL;
		}
	}
	/* Print filter information */
	display_filter_status(data->info.type, flt_idx);

	channel = container_of(ctrl, struct arib2_channel, filter);

	arib2_add_noti_status(channel->dev, noti_type, flt_idx, LX_ARIB2_FLT_STATE_OVERFLOW);

	return 0;
}

static void filter_callback_work(struct work_struct *work)
{
	struct arib2_channel_filter *ctrl;
	ARIB2_FILTER_CALLBACK_T *callback;
	IPC_MSG_ARIB2_DATA_INFO_T *info;
	unsigned long flag;

	ctrl = container_of(work, struct arib2_channel_filter, callback_work);

	while(1)
	{
		spin_lock_irqsave(&ctrl->callback_lock, flag);

		callback = list_first_entry_or_null(&ctrl->callback_head, ARIB2_FILTER_CALLBACK_T, list);
		if(callback) list_del(&callback->list); /* remove from the head */

		spin_unlock_irqrestore(&ctrl->callback_lock, flag);
		if(!callback) break;

		mutex_lock(&filter_lock);

		info = &(callback->data_msg.info);
		log_debug("DEBUG: ch:%d type:%02x(%s) req_num:%d flt_idx:%d status:%d",
					info->ch, info->type, GetFilterTypeStr(info->type),
					info->req_num, info->flt_idx, info->status);

		if(info->status == IPC_DATA_STATUS_OK)
		{
			filter_receive_callback_work(ctrl, &callback->data_msg);
		}
		else if(info->status == IPC_DATA_STATUS_OVERFLOW_NOT_ENOUGH_BUF ||
				info->status == IPC_DATA_STATUS_OVERFLOW_OVERLAPS_PTR)
		{
			filter_overflow_callback_work(ctrl, &callback->data_msg);
		}

		mutex_unlock(&filter_lock);

		kfree(callback);
	}
}

/* callback (in isr) */
static int ipc_receive_callback(void *msg, void *arg)
{
	struct arib2_channel *channel;
	struct arib2_channel_filter *ctrl;
	ARIB2_FILTER_CALLBACK_T * callback;
	IPC_MSG_ARIB2_DATA_T *data = msg;
	struct arib2_device *dev = arg;

	channel = arib2_get_channel(dev, data->info.ch);
	CHECK_ERROR(!channel, return -EINVAL, "invalid ch(%d)", data->info.ch);

	ctrl = &channel->filter;

	callback = kmalloc(sizeof(ARIB2_FILTER_CALLBACK_T), GFP_ATOMIC);
	CHECK_ERROR(!callback, return -ENOMEM, "kmalloc() failed");

	callback->data_msg = *data;

	spin_lock(&ctrl->callback_lock);
	list_add_tail(&callback->list, &ctrl->callback_head);
	spin_unlock(&ctrl->callback_lock);

	queue_work(system_freezable_wq, &ctrl->callback_work);

	return 0;
}

static int ARIB2_ResetFilterCallbackWork(struct arib2_channel *channel)
{
	unsigned long flag;
	struct arib2_channel_filter *ctrl = &channel->filter;
	ARIB2_FILTER_CALLBACK_T *cb;
	int count = 0;

	spin_lock_irqsave(&ctrl->callback_lock, flag);
	while(1)
	{
		cb = list_first_entry_or_null(&ctrl->callback_head, ARIB2_FILTER_CALLBACK_T, list);
		if(!cb) break;

		list_del(&cb->list);
		kfree(cb);
		count++;
	}

	spin_unlock_irqrestore(&ctrl->callback_lock, flag);

	if(count) log_noti("ch[%u] removed %d callbacks", channel->num, count);

	return count;
}

static void* GetARIB2FreeFilter(LX_ARIB2_FLT_TYPE_T type)
{
	int i;

	switch(type)
	{
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f;
			for(i=0; i<num_tlvf; i++)
			{
				f = &tlv_si_filters[i];
				if(!f->used)
				{
					memset((void*)f, 0, sizeof(*f));
					f->idx = i;
					return f;
				}
			}
			break;
		}

		case LX_ARIB2_FILTER_TYPE_MMT_PID:
		{
			MMT_PID_FILTER_T *f;
			for(i=0; i<num_mmt_pidf; i++)
			{
				f = &mmt_pid_filters[i];
				if(!f->used)
				{
					memset((void*)f, 0, sizeof(*f));
					f->idx = i;
					return f;
				}
			}
			break;
		}

		case LX_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f;
			for(i=0; i<num_mmt_sif; i++)
			{
				f = &mmt_si_filters[i];
				if(!f->used)
				{
					memset((void*)f, 0, sizeof(*f));
					f->idx = i;
					return f;
				}
			}
			break;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f;
			for(i=0; i<num_mmt_avf; i++)
			{
				f = &mmt_av_filters[i];
				if(!f->used)
				{
					memset((void*)f, 0, sizeof(*f));
					f->idx = i;
					return f;
				}
			}
			break;
		}
		default:
			return NULL;

	}

	return NULL;
}

static void* FILTER_Alloc(u8 ch, LX_ARIB2_FLT_TYPE_T type, struct arib2_channel_filter *ctrl,
							void *param)
{
	switch(type)
	{
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f;

			f = GetARIB2FreeFilter(type);
			CHECK_ERROR(!f, return NULL, "no empty slot (TLV_SI)");

			f->used = true;
			f->ch = ch;
			f->flags = 0;
			list_add_tail(&f->list, &ctrl->tlv_si_head);

			return f;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_PID:
		{
			MMT_PID_FILTER_T *f;

			f = GetARIB2FreeFilter(type);
			CHECK_ERROR(!f, return NULL, "no empty slot (MMT_PID)");

			f->used = true;
			f->ch = ch;
			list_add_tail(&f->list, &ctrl->mmt_pid_head);

			return f;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f;

			f = GetARIB2FreeFilter(type);
			CHECK_ERROR(!f, return NULL, "no empty slot (MMT_SI)");

			f->used = true;
			f->ch = ch;
			f->flags = 0;
			list_add_tail(&f->list, &ctrl->mmt_si_head);

			return f;
		}

		case LX_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f;

			f = GetARIB2FreeFilter(type);
			CHECK_ERROR(!f, return NULL, "no empty slot (MMT_SI)");

			f->used = true;
			f->ch = ch;
			//f->flags = 0;
			list_add_tail(&f->list, &ctrl->mmt_av_head);

			return f;
		}
		default:
			return NULL;
	}
}

static int FILTER_Free(LX_ARIB2_FLT_TYPE_T type, void *filter)
{
	int rc;

	switch(type)
	{
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
		{
			TLV_SI_FILTER_T *f = filter;

			f->used = false;
			f->owner = NULL; //release owner
			list_del(&f->list);

			return 0;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_PID:
		{
			MMT_PID_FILTER_T *f = filter;

			if(f->buffer.start)
			{
				rc = te_mem_free(filter_mm, f->buffer.start);
				CHECK_ERROR(rc < 0, , "Error in te_mem_free");
			}

			f->used = false;
			f->owner = NULL; //release owner
			list_del(&f->list);

			return 0;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_SI:
		{
			MMT_SI_FILTER_T *f = filter;

			f->used = false;
			f->owner = NULL; //release owner
			list_del(&f->list);

			return 0;
		}
		case LX_ARIB2_FILTER_TYPE_MMT_AV:
		{
			MMT_AV_FILTER_T *f = filter;

			f->used = false;
			f->owner = NULL; //release owner
			list_del(&f->list);

			return 0;
		}
		default:
			log_error("unknown type(%d)", type);
			return -EINVAL;
	}
}

static int FILTER_Cancel(struct arib2_channel *channel, LX_ARIB2_FLT_TYPE_T type, u8 idx)
{

	struct arib2_channel_filter *ctrl;
	u8 ipc_flt_type;
	void *f;
	int rc;

	ctrl = &(channel->filter);
	CHECK_ERROR(!ctrl, return -EINVAL, "null filter ctrl (ch[%d])", channel->num);

	f = GetFilterWithIdx(ctrl, type, idx);
	CHECK_ERROR(!f, return -EINVAL, "not matched filter(idx:%d)", idx);

	switch(type)
	{
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
			ipc_flt_type = IPC_ARIB2_FILTER_TYPE_TLV_SI;
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_PID:
			ipc_flt_type = IPC_ARIB2_FILTER_TYPE_MMT_PID;
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_SI:
			ipc_flt_type = IPC_ARIB2_FILTER_TYPE_MMT_SI;
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_AV:
			ipc_flt_type = IPC_ARIB2_FILTER_TYPE_MMT_AV;
			break;
		default:
		{
			log_error("unknown kapi filter type(%d)", type);
			return -EINVAL;
		}
	}

	/* request to mcu */
	rc = TE_IPC_CancelARIB2Filter(channel->num, ipc_flt_type, idx);
	CHECK_ERROR(rc, , "Error(%d) in TE_IPC_CancelARIB2Filter", rc);

	rc = FILTER_Free(type, f);
	CHECK_ERROR(rc, ,"Error(%d) in Filter_Free", rc);

	/* Delete msg in notify queue */
	if(type == LX_ARIB2_FILTER_TYPE_TLV_SI ||
		type == LX_ARIB2_FILTER_TYPE_MMT_SI ||
		type == LX_ARIB2_FILTER_TYPE_MMT_AV)
	{
		LX_ARIB2_NOTIFY_TYPE_T noti_type;

		switch(type)
		{
			case LX_ARIB2_FILTER_TYPE_TLV_SI: noti_type = LX_ARIB2_NOTIFY_TLV_SI; break;
			case LX_ARIB2_FILTER_TYPE_MMT_SI: noti_type = LX_ARIB2_NOTIFY_MMT_SI; break;
			case LX_ARIB2_FILTER_TYPE_MMT_AV: noti_type = LX_ARIB2_NOTIFY_MMT_AV; break;
			default: noti_type = LX_ARIB2_NOTIFY_MMT_SI; break; //remains for reduce warn msg
		}

		arib2_add_noti_status(channel->dev, noti_type, idx, LX_ARIB2_FLT_STATE_DELETED);
	}

	return 0;
}

static int TLVSIGNAL_Recovery(TLV_SI_FILTER_T *f)
{
	int rc;
	IPC_ARIB2_TLV_SIGNAL_REQ_PAYLOAD_T payload;

	memset(&payload, 0, sizeof(payload));

	payload.req_num		= f->req_num;
	payload.gpb_saddr	= f->buffer.start;
	payload.gpb_eaddr	= f->buffer.end;
	memcpy(payload.value, f->pattern.value, sizeof(payload.value));
	memcpy(payload.mask, f->pattern.mask, sizeof(payload.mask));
	memcpy(payload.noteq, f->pattern.noteq, sizeof(payload.noteq));

	if(f->flags & LX_ARIB2_FLT_FLAG_ONESHOT)
		payload.one_shot = true;
	else
		payload.one_shot = false;

	rc = TE_IPC_RequestARIB2Filter(f->ch, IPC_ARIB2_FILTER_TYPE_TLV_SI, f->idx, &payload);
	CHECK_ERROR(rc < 0, , "Error(%d) in TE_IPC_RequestARIB2Filter (Recovery)", rc);

	return 0;
}

static int MMTPID_Recovery(MMT_PID_FILTER_T *f)
{
	int rc;
	IPC_ARIB2_MMT_PID_REQ_PAYLOAD_T payload;

	memset(&payload, 0, sizeof(payload));
	payload.packet_id = f->packet_id;
	payload.seg_buf_saddr = f->buffer.start;
	payload.seg_buf_eaddr = f->buffer.end;

	rc = TE_IPC_RequestARIB2Filter(f->ch, IPC_ARIB2_FILTER_TYPE_MMT_PID, f->idx, &payload);
	CHECK_ERROR(rc < 0, , "Error(%d) in TE_IPC_RequestARIB2Filter (Recovery)", rc);

	return 0;
}

static int MMTSIGNAL_Recovery(MMT_SI_FILTER_T *f)
{
	int rc;
	IPC_ARIB2_MMT_SIGNAL_REQ_PAYLOAD_T payload;

	memset(&payload, 0, sizeof(payload));

	payload.req_num		= f->req_num;
	payload.gpb_saddr	= f->buffer.start;
	payload.gpb_eaddr	= f->buffer.end;
	payload.message_id	= f->message_id;
	payload.pidf_idx	= f->mmt_pid_f->idx;
	memcpy(payload.value, f->pattern.value, sizeof(payload.value));
	memcpy(payload.mask, f->pattern.mask, sizeof(payload.mask));
	memcpy(payload.noteq, f->pattern.noteq, sizeof(payload.noteq));

	if(f->flags & LX_ARIB2_FLT_FLAG_ONESHOT)
		payload.one_shot = true;
	else
		payload.one_shot = false;

	rc = TE_IPC_RequestARIB2Filter(f->ch, IPC_ARIB2_FILTER_TYPE_MMT_SI, f->idx, &payload);
	CHECK_ERROR(rc < 0, , "Error(%d) in TE_IPC_RequestARIB2Filter (Recovery)", rc);

	return 0;
}

static int MMTAV_Recovery(MMT_AV_FILTER_T *f)
{
	int rc;
	IPC_ARIB2_MMT_AV_REQ_PAYLOAD_T payload;

	memset(&payload, 0, sizeof(payload));

	payload.req_num		= f->req_num;
	payload.gpb_saddr	= f->buffer.start;
	payload.gpb_eaddr	= f->buffer.end;
	payload.pidf_idx	= f->mmt_pid_f->idx;

	rc = TE_IPC_RequestARIB2Filter(f->ch, IPC_ARIB2_FILTER_TYPE_MMT_AV, f->idx, &payload);
	CHECK_ERROR(rc < 0, , "Error(%d) in TE_IPC_RequestARIB2Filter", rc);

	return 0;
}

static int ARIB2_RecoverAllFilters(struct arib2_device *dev)
{
	struct arib2_channel *channel;
	struct arib2_channel_filter *ctrl;
	TLV_SI_FILTER_T *tlvf;
	MMT_PID_FILTER_T *mmtpidf;
	MMT_SI_FILTER_T *mmtsif;
	MMT_AV_FILTER_T *mmtavf;
	int i;
	u32 tlv_cnt = 0, mmt_pid_cnt = 0, mmt_si_cnt = 0, mmt_av_cnt = 0;

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		/* TODO: check enable channel ? */
		ctrl = &channel->filter;

		list_for_each_entry(tlvf, &ctrl->tlv_si_head, list)
		{
			TLVSIGNAL_Recovery(tlvf);
			tlv_cnt++;
		}

		list_for_each_entry(mmtpidf, &ctrl->mmt_pid_head, list)
		{
			MMTPID_Recovery(mmtpidf);
			mmt_pid_cnt++;
		}

		list_for_each_entry(mmtsif, &ctrl->mmt_si_head, list)
		{
			MMTSIGNAL_Recovery(mmtsif);
			mmt_si_cnt++;
		}

		list_for_each_entry(mmtavf, &ctrl->mmt_av_head, list)
		{
			MMTAV_Recovery(mmtavf);
			mmt_av_cnt++;
		}
	}

	log_noti("tlv_si[%d] mmt_pid[%d] mmt_si[%d] mmt_av[%d] filters are recoverd",
				tlv_cnt, mmt_pid_cnt, mmt_si_cnt, mmt_av_cnt);

	return 0;
}

static int mcu_recovery_pre_callback(void * arg)
{
	mutex_lock(&filter_lock);
	return 0;
}

static int mcu_recovery_post_callback(void * arg)
{
	int ret;

	ret = ARIB2_RecoverAllFilters(arg);
	mutex_unlock(&filter_lock);

	return ret;
}

static int check_filter_paddr_range(struct arib2_fh *fh, u32 addr, u32 size)
{
	struct te_mem_ctx *mem, *temp_mem = NULL;
	int rc;

	if (fh->mem) {
		mem = fh->mem;
	} else {
		temp_mem = te_mem_open(ARIB2_MEM_NAME);
		if (!temp_mem)
			return -EIO;
		mem = temp_mem;
	}

	rc = te_mem_check_paddr_range(mem, addr, size);

	if (temp_mem)
		te_mem_close(temp_mem);

	return rc;
}

static TLV_SI_FILTER_T* TLVSIGNAL_Request(struct arib2_channel *channel, void *priv,
											LX_ARIB2_FLT_TLVSI_REQ_T *req)
{
	TLV_SI_FILTER_T *f = NULL;
	struct arib2_channel_filter *ctrl = &channel->filter;
	IPC_ARIB2_TLV_SIGNAL_REQ_PAYLOAD_T payload;
	int rc;

	rc = check_filter_paddr_range(priv, req->buf.addr, req->buf.size);
	if (rc)
		return NULL;

	f = FILTER_Alloc(channel->num, LX_ARIB2_FILTER_TYPE_TLV_SI, ctrl, req);
	CHECK_ERROR(!f, goto error, "fail to alloc tlv_si filter");

	memset(&payload, 0, sizeof(payload));

	/* Copy payload information */
	payload.req_num		= ctrl->tlv_si_req_num;
	payload.gpb_saddr	= req->buf.addr;
	payload.gpb_eaddr	= req->buf.addr + req->buf.size;
	memcpy(payload.value, req->pattern.value, sizeof(payload.value));
	memcpy(payload.mask, req->pattern.mask, sizeof(payload.mask));
	memcpy(payload.noteq, req->pattern.noteq, sizeof(payload.noteq));

	if(req->flags & LX_ARIB2_FLT_FLAG_ONESHOT)
		payload.one_shot = true;
	else
		payload.one_shot = false;

	/* request to mcu */
	rc = TE_IPC_RequestARIB2Filter(channel->num, IPC_ARIB2_FILTER_TYPE_TLV_SI, f->idx, &payload);
	CHECK_ERROR(rc < 0, goto error, "Error(%d) in TE_IPC_RequestARIB2Filter", rc);

	/* save requested info */
	f->req_num		= ctrl->tlv_si_req_num++;
	f->buffer.start = req->buf.addr;
	f->buffer.end	= req->buf.addr + req->buf.size;
	f->buffer.rptr	= f->buffer.start;
	f->buffer.wptr	= f->buffer.start;
	f->pattern		= req->pattern;
	f->flags		= req->flags;
	f->priv			= req->priv;

	f->owner		= priv;

	log_filter("allocated memory(idx:%d) [0x%08x - 0x%08x]", f->idx, f->buffer.start, f->buffer.end);
	return f;

error:
	if(f)
		FILTER_Free(LX_ARIB2_FILTER_TYPE_TLV_SI, f);

	return NULL;

}

static MMT_PID_FILTER_T* MMTPID_Request(struct arib2_channel *channel, void *priv,
										LX_ARIB2_FLT_MMTPID_REQ_T *req)
{
	MMT_PID_FILTER_T *f = NULL;
	struct arib2_channel_filter *ctrl = &channel->filter;
	IPC_ARIB2_MMT_PID_REQ_PAYLOAD_T payload;
	u32 mem_addr;
	int rc;
#define MMT_PID_BUF_SIZE	(256*1024)	/*FIXME: not fixed */

	f = FILTER_Alloc(channel->num, LX_ARIB2_FILTER_TYPE_MMT_PID, ctrl, req);
	CHECK_ERROR(!f, return NULL, "fail to alloc mmt_pid");

	/* Alloc segmentation Buffer for MCU */
	mem_addr = te_mem_alloc(filter_mm, MMT_PID_BUF_SIZE, "arib2_mmt_pid");
	CHECK_ERROR(!mem_addr, goto error, "can't alloc memory");

	memset(&payload, 0, sizeof(payload));
	payload.packet_id = req->packet_id;
	payload.seg_buf_saddr = mem_addr;
	payload.seg_buf_eaddr = mem_addr + MMT_PID_BUF_SIZE;

	/* request to mcu */
	rc = TE_IPC_RequestARIB2Filter(channel->num, IPC_ARIB2_FILTER_TYPE_MMT_PID, f->idx, &payload);
	CHECK_ERROR(rc < 0, goto error, "Error(%d) in TE_IPC_RequestARIB2Filter", rc);

	/* save requested info */
	f->packet_id	= req->packet_id;
	f->buffer.start = mem_addr;
	f->buffer.end 	= mem_addr + MMT_PID_BUF_SIZE;
	f->buffer.rptr	= f->buffer.start;
	f->buffer.wptr	= f->buffer.start;
	f->owner		= priv; //owner marking

	log_filter("allocated memory(idx: %d): [0x%08x ~ 0x%08x]",
				f->idx, f->buffer.start, f->buffer.end);

	return f;

error:
	if(mem_addr)
	{
		te_mem_free(filter_mm, mem_addr);
		f->buffer.start = 0;
	}
	if(f)
		FILTER_Free(LX_ARIB2_FILTER_TYPE_MMT_PID, f);

	return NULL;

}

static MMT_SI_FILTER_T* MMTSIGNAL_Request(struct arib2_channel *channel, void *priv,
										LX_ARIB2_FLT_MMTSI_REQ_T *req)
{
	MMT_SI_FILTER_T *f;
	MMT_PID_FILTER_T *pid_f;
	struct arib2_channel_filter *ctrl = &channel->filter;
	IPC_ARIB2_MMT_SIGNAL_REQ_PAYLOAD_T payload;
	int rc;

	rc = check_filter_paddr_range(priv, req->buf.addr, req->buf.size);
	if (rc)
		return NULL;

	/* Upper layer check */
	pid_f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_PID, req->pidf_idx);
	CHECK_ERROR(!pid_f, return NULL, "not allocated pid filter(idx:%d)", req->pidf_idx);

	/* Filter Alloc */
	f = FILTER_Alloc(channel->num, LX_ARIB2_FILTER_TYPE_MMT_SI, ctrl, req);
	CHECK_ERROR(!f, goto error, "fail to alloc mmt_si filter");

	memset(&payload, 0, sizeof(payload));

	/* Copy payload information */
	payload.req_num		= ctrl->mmt_si_req_num;
	payload.gpb_saddr	= req->buf.addr;
	payload.gpb_eaddr	= req->buf.addr + req->buf.size;
	payload.message_id	= req->message_id;
	payload.pidf_idx	= req->pidf_idx;
	memcpy(payload.value, req->pattern.value, sizeof(payload.value));
	memcpy(payload.mask, req->pattern.mask, sizeof(payload.mask));
	memcpy(payload.noteq, req->pattern.noteq, sizeof(payload.noteq));

	if(req->flags & LX_ARIB2_FLT_FLAG_ONESHOT)
		payload.one_shot = true;
	else
		payload.one_shot = false;

	/* request to mcu */
	rc = TE_IPC_RequestARIB2Filter(channel->num, IPC_ARIB2_FILTER_TYPE_MMT_SI, f->idx, &payload);
	CHECK_ERROR(rc < 0, goto error, "Error(%d) in TE_IPC_RequestARIB2Filter", rc);

	/* save requested info */
	f->req_num		= ctrl->mmt_si_req_num++;
	f->buffer.start = req->buf.addr;
	f->buffer.end	= req->buf.addr + req->buf.size;
	f->buffer.rptr	= f->buffer.start;
	f->buffer.wptr	= f->buffer.start;
	f->pattern		= req->pattern;
	f->flags		= req->flags;
	f->priv			= req->priv;
	f->mmt_pid_f	= pid_f;
	f->message_id	= req->message_id;

	f->owner		= priv;

	log_filter("allocated memory(idx:%d) [0x%08x - 0x%08x]", f->idx, f->buffer.start, f->buffer.end);
	return f;

error:
	if(f)
		FILTER_Free(LX_ARIB2_FILTER_TYPE_MMT_SI, f);

	return NULL;
}

static MMT_AV_FILTER_T* MMTAV_Request(struct arib2_channel *channel, void *priv,
									LX_ARIB2_FLT_MMTAV_REQ_T *req)
{
	MMT_AV_FILTER_T *f;
	MMT_PID_FILTER_T *pid_f;
	struct arib2_channel_filter *ctrl = &channel->filter;
	IPC_ARIB2_MMT_AV_REQ_PAYLOAD_T payload;
	int rc;

	rc = check_filter_paddr_range(priv, req->buf.addr, req->buf.size);
	if (rc)
		return NULL;

	/* Upper layer check */
	pid_f = GetFilterWithIdx(ctrl, LX_ARIB2_FILTER_TYPE_MMT_PID, req->pidf_idx);
	CHECK_ERROR(!pid_f, return NULL, "not allocated pid filter(idx:%d)", req->pidf_idx);

	/* Filter Alloc */
	f = FILTER_Alloc(channel->num, LX_ARIB2_FILTER_TYPE_MMT_AV, ctrl, req);
	CHECK_ERROR(!f, goto error, "fail to alloc mmt_av filter");

	/* Copy payload information */
	payload.req_num		= ctrl->mmt_av_req_num;
	payload.gpb_saddr	= req->buf.addr;
	payload.gpb_eaddr	= req->buf.addr + req->buf.size;
	payload.pidf_idx	= req->pidf_idx;

	rc = TE_IPC_RequestARIB2Filter(channel->num, IPC_ARIB2_FILTER_TYPE_MMT_AV, f->idx, &payload);
	CHECK_ERROR(rc < 0, goto error, "Error(%d) in TE_IPC_RequestARIB2Filter", rc);

	memset(&payload, 0, sizeof(payload));

	/* save requested info */
	f->req_num		= ctrl->mmt_av_req_num++;
	f->buffer.start = req->buf.addr;
	f->buffer.end	= req->buf.addr + req->buf.size;
	f->buffer.rptr	= f->buffer.start;
	f->buffer.wptr	= f->buffer.start;
	//f->flags		= req->flags; //TODO: Check necessity
	f->priv			= req->priv; //TODO: Check necessity
	f->mmt_pid_f	= pid_f;

	f->owner		= priv;

	log_filter("allocated memory(idx:%d) [0x%08x - 0x%08x]", f->idx, f->buffer.start, f->buffer.end);
	return f;

error:
	if(f)
		FILTER_Free(LX_ARIB2_FILTER_TYPE_MMT_AV, f);

	return NULL;
}

static int ioc_request_filter(struct arib2_fh *fh, void *arg)
{
	struct arib2_channel *channel = fh->channel;
	LX_ARIB2_FLT_REQUEST_PARAM_T	*param = arg;
	struct arib2_channel_filter				*ctrl;
	int idx;

	ctrl = &channel->filter;
	CHECK_ERROR(!ctrl, return -EINVAL, "invalid ch(%d)", channel->num);

	/* TODO: check enable channel pattern */

	switch (param->type) {
	case LX_ARIB2_FILTER_TYPE_TLV_SI: {
		TLV_SI_FILTER_T *f;
		f = TLVSIGNAL_Request(channel, fh, param->tlv_si);
		CHECK_ERROR(!f, return -EPERM, "Error in TLVSIGNAL_Request");

		idx = f->idx;
		break;
	}
	case LX_ARIB2_FILTER_TYPE_MMT_PID: {
		MMT_PID_FILTER_T *f;
		f = MMTPID_Request(channel, fh, param->mmt_pid);
		CHECK_ERROR(!f, return -EPERM, "Error in MMTPID_Request");

		idx = f->idx;
		break;
	}
	case LX_ARIB2_FILTER_TYPE_MMT_SI: {
		MMT_SI_FILTER_T *f;
		f= MMTSIGNAL_Request(channel, fh, param->mmt_si);
		CHECK_ERROR(!f, return -EPERM, "Error in MMTPID_Request");

		idx = f->idx;
		break;
	}
	case LX_ARIB2_FILTER_TYPE_MMT_AV: {
		MMT_AV_FILTER_T *f;
		f = MMTAV_Request(channel, fh, param->mmt_av);
		CHECK_ERROR(!f, return -EPERM, "Error in MMTAV_Request");

		idx = f->idx;
		break;
	}
	default:
		log_error("invalid type(%d)", param->type);
		idx = -1;
		break;
	}

	return idx;
}

static int ioc_cancel_filter(struct arib2_fh *fh, void *arg)
{
	LX_ARIB2_FLT_CANCEL_T *param = arg;

	return FILTER_Cancel(fh->channel, param->type, param->idx);
}

#if 0
/*----------------------------------------------------------------------------------------
 *   Proc Functions
 *---------------------------------------------------------------------------------------*/
/* Show Driver Filter Status */
static void TLVSIGNAL_FilterStatus(struct seq_file *m, TLV_SI_FILTER_T *f)
{
	LX_ARIB2_FLT_PATTERN_T *p = &f->pattern;
	UINT32 size = f->buffer.end - f->buffer.start;
	UINT32 used = (f->buffer.wptr + size - f->buffer.rptr) % size;

	seq_printf(m, "[%03d]	CH[%d]\n", f->idx, f->ch);

	seq_printf(m, "\tVALUE\t\t[%08x %08x]\n", TE_GET32(&p->value[0]), TE_GET32(&p->value[4]));
	seq_printf(m, "\tMASK\t\t[%08x %08x]\n", TE_GET32(&p->mask[0]), TE_GET32(&p->mask[4]));
	seq_printf(m, "\tNOT EQUAL\t\t[%08x %08x]\n", TE_GET32(&p->noteq[0]), TE_GET32(&p->noteq[4]));
	seq_printf(m, "\tREQ_NUM\t\t[%d]\n", f->req_num);
	seq_printf(m, "\tFLAGS\t\t[%s]\n",
					(f->flags & LX_ARIB2_FLT_FLAG_ONESHOT) ? "ONE_SHOT" : "CONTINUOUS");

	seq_printf(m, "\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n", f->buffer.start, f->buffer.end, size>>10);
	seq_printf(m, "\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
					f->buffer.wptr, f->buffer.rptr, used>>10);

	seq_printf(m, "\tOVERFLOW\tCNT[%d] ", f->ovf_cnt);
	if(f->ovf_cnt)
		seq_printf(m, "LAST STATUS[%s]\n", GetOverflowStatusStr(f->ovf_status));
	else seq_printf(m, "\n");

	seq_printf(m, "\n");
}

static void MMTPID_FilterStatus(struct seq_file *m, MMT_PID_FILTER_T *f)
{
	UINT32 size = f->buffer.end - f->buffer.start;
	UINT32 used = (f->buffer.wptr + size - f->buffer.rptr) % size;

	seq_printf(m, "[%03d]	CH[%d]\n", f->idx, f->ch);
	seq_printf(m, "\tPID[0x%04x]\n", f->packet_id);

	seq_printf(m, "\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n", f->buffer.start, f->buffer.end, size>>10);
	seq_printf(m, "\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
					f->buffer.wptr, f->buffer.rptr, used>>10);
	seq_printf(m, "\n");
}

static void MMTSIGNAL_FilterStatus(struct seq_file *m, MMT_SI_FILTER_T *f)
{
	LX_ARIB2_FLT_PATTERN_T *p = &f->pattern;
	UINT32 size = f->buffer.end - f->buffer.start;
	UINT32 used = (f->buffer.wptr + size - f->buffer.rptr) % size;

	seq_printf(m, "[%03d]	CH[%d]\n", f->idx, f->ch);
	seq_printf(m, "\tPID[0x%04x]\n", f->mmt_pid_f->packet_id);
	seq_printf(m, "\tMESSAGE ID[0x%04x]\n", f->message_id);

	seq_printf(m, "\tVALUE\t\t[%08x %08x]\n", TE_GET32(&p->value[0]), TE_GET32(&p->value[4]));
	seq_printf(m, "\tMASK\t\t[%08x %08x]\n", TE_GET32(&p->mask[0]), TE_GET32(&p->mask[4]));
	seq_printf(m, "\tNOT EQUAL\t\t[%08x %08x]\n", TE_GET32(&p->noteq[0]), TE_GET32(&p->noteq[4]));
	seq_printf(m, "\tREQ_NUM\t\t[%d]\n", f->req_num);
	seq_printf(m, "\tFLAGS\t\t[%s]\n",
					(f->flags & LX_ARIB2_FLT_FLAG_ONESHOT) ? "ONE_SHOT" : "CONTINUOUS");

	seq_printf(m, "\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n", f->buffer.start, f->buffer.end, size>>10);
	seq_printf(m, "\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
					f->buffer.wptr, f->buffer.rptr, used>>10);

	seq_printf(m, "\tOVERFLOW\tCNT[%d] ", f->ovf_cnt);
	if(f->ovf_cnt)
		seq_printf(m, "LAST STATUS[%s]\n", GetOverflowStatusStr(f->ovf_status));
	else seq_printf(m, "\n");

	seq_printf(m, "\n");
}

static void MMTAV_FilterStatus(struct seq_file *m, MMT_AV_FILTER_T *f)
{
	UINT32 size = f->buffer.end - f->buffer.start;
	UINT32 used = (f->buffer.wptr + size - f->buffer.rptr) % size;

	seq_printf(m, "[%03d]	CH[%d]\n", f->idx, f->ch);
	seq_printf(m, "\tPID[0x%04x]\n", f->mmt_pid_f->packet_id);

	seq_printf(m, "\tREQ_NUM\t\t[%d]\n", f->req_num);
	//seq_printf(m, "\tFLAGS\t\t[%s]\n",
	//				(f->flags & LX_ARIB2_FLT_FLAG_ONESHOT) ? "ONE_SHOT" : "CONTINUOUS");

	seq_printf(m, "\tBUF_RANGE\t[0x%08x--0x%08x] %dKB\n", f->buffer.start, f->buffer.end, size>>10);
	seq_printf(m, "\tBUF_PTR\t\t[w:0x%08x, r:0x%08x] USED: %dKB\n",
					f->buffer.wptr, f->buffer.rptr, used>>10);

	seq_printf(m, "\tOVERFLOW\tCNT[%d] ", f->ovf_cnt);
	if(f->ovf_cnt)
		seq_printf(m, "LAST STATUS[%s]\n", GetOverflowStatusStr(f->ovf_status));
	else seq_printf(m, "\n");

	seq_printf(m, "\n");
}

static void PROC_ShowDrvFilterStatus(struct seq_file *m)
{
	struct arib2_device *dev = ARIB2_GetDevice();
	struct arib2_channel *channel;
	struct arib2_channel_filter *ctrl;
	int i;

	seq_printf(m, "TLV_SI Filter\n");
	for(i=0; i<dev->num_channel; i++)
	{
		TLV_SI_FILTER_T *f;

		channel = ARIB2_GetChCtrl(i);
		if(!channel || channel->used == false) continue;

		ctrl = &channel->filter;

		list_for_each_entry(f, &ctrl->tlv_si_head, list)
		{
			TLVSIGNAL_FilterStatus(m, f);
		}
	}

	seq_printf(m, "MMT_PID Filter\n");
	for(i=0; i<dev->num_channel; i++)
	{
		MMT_PID_FILTER_T *f;

		channel = ARIB2_GetChCtrl(i);
		if(!channel || channel->used == false) continue;

		ctrl = &channel->filter;

		list_for_each_entry(f, &ctrl->mmt_pid_head, list)
		{
			MMTPID_FilterStatus(m, f);
		}
	}

	seq_printf(m, "MMT_SI Filter\n");
	for(i=0; i<dev->num_channel; i++)
	{
		MMT_SI_FILTER_T *f;

		channel = ARIB2_GetChCtrl(i);
		if(!channel || channel->used == false) continue;

		ctrl = &channel->filter;

		list_for_each_entry(f, &ctrl->mmt_si_head, list)
		{
			MMTSIGNAL_FilterStatus(m, f);
		}
	}

	seq_printf(m, "MMT_AV Filter\n");
	for(i=0; i<dev->num_channel; i++)
	{
		MMT_AV_FILTER_T *f;

		channel = ARIB2_GetChCtrl(i);
		if(!channel || channel->used == false) continue;

		ctrl = &channel->filter;

		list_for_each_entry(f, &ctrl->mmt_av_head, list)
		{
			MMTAV_FilterStatus(m, f);
		}
	}
}

static void MCU_TLVSI_Status(struct seq_file *m, u8 idx)
{
	IPC_ARIB2_TLV_SI_FILTER_STATUS_T s;

	TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_TLV_SI, &s);
	if(!s.status) return;

	STATUS_PRINT(m, "[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
					idx, mcu_filter_status_str(s.status), s.request_num, s.overflow_cnt);
	STATUS_PRINT(m, "W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
}

static void MCU_IP_Status(struct seq_file *m, u8 idx)
{
	IPC_ARIB2_IP_STATUS_T s;
	int i;

	TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_IP, &s);
	if(!s.status) return;

	seq_printf(m, "[%03d]   STATUS[%s] CID[%u]\n", idx, mcu_filter_status_str(s.status), s.cid);
	seq_printf(m, "PKT_CNT[%u] ERR_CNT[%u] CID_CHG_CNT[%u] IP_CHG_CNT[%u] SN_ERR[%u]\n",
					s.packet_cnt, s.err_packet_cnt, s.cid_chg_cnt, s.ip_chg_cnt, s.sn_err_cnt);
	seq_printf(m, "src_addr \t");
	for(i=0; i<4; i++)
	{
		seq_printf(m, "%8x", TE_GET32(&s.src_addr[i*4]));
		if(i == 3) seq_printf(m, "\tport[%u]\n", s.src_port);
		else seq_printf(m, ":");
	}

	seq_printf(m, "dst_addr \t");
	for(i=0; i<4; i++)
	{
		seq_printf(m, "%8x", TE_GET32(&s.dst_addr[i*4]));
		if(i == 3) seq_printf(m, "\tport[%u]\n", s.dst_port);
		else seq_printf(m, ":");
	}
}

static void MCU_MMTPID_Status(struct seq_file *m, u8 idx)
{
	IPC_ARIB2_MMT_PID_STATUS_T s;

	TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_MMT_PID, &s);
	if(!s.status) return;

	seq_printf(m, "[%03d]   STATUS[%s]\n", idx, mcu_filter_status_str(s.status));
	seq_printf(m, "PKT_CNT[%u] ERR_CNT[%u]\n", s.packet_cnt, s.err_packet_cnt);
}

static void MCU_MMTSI_Status(struct seq_file *m, u8 idx)
{
	IPC_ARIB2_MMT_SI_FILTER_STATUS_T s;

	TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_MMT_SI, &s);
	if(!s.status) return;

	STATUS_PRINT(m, "[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
					idx, mcu_filter_status_str(s.status), s.request_num, s.overflow);
	STATUS_PRINT(m, "W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
}

static void MCU_MMTAV_Status(struct seq_file *m, u8 idx)
{
	IPC_ARIB2_MMT_AV_FILTER_STATUS_T s;

	TE_IPC_GetARIB2FilterStatus(idx, IPC_ARIB2_FILTER_TYPE_MMT_AV, &s);
	if(!s.status) return;

	STATUS_PRINT(m, "[%03d]   STATUS[%s] REQ_NUM[%u] OVF_CNT[%u]\n",
					idx, mcu_filter_status_str(s.status), s.request_num, s.overflow);
	STATUS_PRINT(m, "W[0x%08x] R[0x%08x]\n", s.gpb_wptr, s.gpb_rptr);
}

static void PROC_ShowMCUFilterStatus(struct seq_file *m)
{
	struct arib2_device *dev = ARIB2_GetDevice();
	struct arib2_channel *channel;
	int i, rc;

	seq_printf(m, "[CH]\n");
	for(i=0; i<dev->num_channel; i++)
	{
		IPC_ARIB2_CH_STATUS_T s;

		channel = ARIB2_GetChCtrl(i);
		if(!channel || channel->used == false) continue;

		rc = TE_IPC_GetARIB2ChannelStatus(i, &s);
		CHECK_ERROR(!rc, continue, "error in TE_IPC_GetARIB2ChannelStatus[%d]", i);

		seq_printf(m, "[%03d] STATUS[%u] PKT[%u] ERR[%u]\n",
						i, s.status, s.packet_cnt, s.err_packet_cnt);
	}

	seq_printf(m, "\n[TLV SI]\n");
	for(i=0; i<num_tlvf; i++)
	{
		MCU_TLVSI_Status(m, i);
	}

	seq_printf(m, "[IP]\n");
	for(i=0; i<num_ipf; i++)
	{
		MCU_IP_Status(m, i);
	}

	seq_printf(m, "[MMT PID]\n");
	for(i=0; i<num_mmt_pidf; i++)
	{
		MCU_MMTPID_Status(m, i);
	}

	seq_printf(m, "[MMT SI]\n");
	for(i=0; i<num_mmt_sif; i++)
	{
		MCU_MMTSI_Status(m, i);
	}

	seq_printf(m, "[MMT AV]\n");
	for(i=0; i<num_mmt_avf; i++)
	{
		MCU_MMTAV_Status(m, i);
	}
}

void ARIB2_PROC_ShowFilter(struct seq_file *m, FILTER_PROC_TYPE_T type)
{
	ARIB2_CFG_T *chip_cfg = ARIB2_GetConfig();

	if(chip_cfg->swtlv) //Not supported in swtlv
	{
		seq_printf(m, "%s Status Not Supported (swtlv)\n", (type == FILTER_PROC_DRV_STATUS) ?
					"Driver" : "MCU");
		return;
	}

	switch(type)
	{
		case FILTER_PROC_DRV_STATUS:
			PROC_ShowDrvFilterStatus(m);
			break;

		case FILTER_PROC_MCU_STATUS:
			PROC_ShowMCUFilterStatus(m);
			break;

		default:
			seq_printf(m, "invalid_type\n");
			break;
	}
}

//init debug, ...
static void init_debug(struct arib2_device *dev)
{

}
#endif


static int filter_dev_ioctl_param(void *priv, unsigned int cmd, void *arg,
								  struct te_ioctl_ptr_param *param)
{
	int ret = 0;

	switch (cmd) {
	case ARIB2_IOC_FLT_REQUEST: {
		LX_ARIB2_FLT_REQUEST_PARAM_T *p = arg;

		param->user_ptr		= te_ioctl_get_user_ptr(p->filter);
		param->kernel_ptr	= (void**)&p->filter;
		param->dir			= _IOC_WRITE;

		switch (p->type) {
		case LX_ARIB2_FILTER_TYPE_TLV_SI:
			param->size = sizeof(LX_ARIB2_FLT_TLVSI_REQ_T);
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_PID:
			param->size = sizeof(LX_ARIB2_FLT_MMTPID_REQ_T);
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_SI:
			param->size = sizeof(LX_ARIB2_FILTER_TYPE_MMT_SI);
			break;
		case LX_ARIB2_FILTER_TYPE_MMT_AV:
			param->size = sizeof(LX_ARIB2_FILTER_TYPE_MMT_AV);
			break;
		default:
			ret = -1;
		}
		break;
	}
	//TODO: Get Status
	default:
		break;
	}

	return ret;
}

static int filter_dev_ioctl(void *priv, unsigned int cmd, void *arg)
{
	struct arib2_fh *fh = priv;
	const struct arib2_ioctl_info ioctls[] = {
		IOC_INFO(ARIB2_IOC_FLT_REQUEST,	ioc_request_filter),
		IOC_INFO(ARIB2_IOC_FLT_CANCEL, ioc_cancel_filter),
		//IOC_INFO(ARIB2_IOC_FLT_GET_STATUS, IOCTL_GetFilterStatus),
		//TODO: implement?
	};

	if (fh->dev->use_swtlv) {
		log_error("Not Supported in SWTLV mode");
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
					cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		return -EPERM; //Operation not permitted
	}

	return arib2_do_ioctl(priv, cmd, arg, filter_lock, ioctls);
}

static int filter_dev_resume(struct arib2_device *dev)
{
	int ret;

	if (dev->use_swtlv) //Not supported in swtlv
		return 0;

	log_noti("ARIB2_FILTER_Resume");

	/* reconnect filter callback */
	TE_IPC_RegisterARIB2FilterCallback(ipc_receive_callback, dev);

	ret = ARIB2_RecoverAllFilters(dev);

	return ret;
}

static int filter_dev_suspend(struct arib2_device *dev)
{
	int i;
	struct arib2_channel *channel;

	if (dev->use_swtlv) //Not supported in swtlv
		return 0;

	/* disconnect callback */
	TE_IPC_RegisterARIB2FilterCallback(NULL, NULL);

	for (i = 0; i < dev->num_channel; i++) {
		channel = &dev->channels[i];

		/* remove callback works */
		ARIB2_ResetFilterCallbackWork(channel);
	}

	return 0;
}

static int filter_dev_init(struct arib2_device *dev)
{
	struct arib2_channel_filter *ctrl;
	int i;

	if (dev->use_swtlv) //Not supported in swtlv
		return 0;

	num_tlvf		= dev->cfg->num_tlvf;
	num_ipf			= dev->cfg->num_ipf;
	num_mmt_pidf	= dev->cfg->num_mmt_pidf;
	num_mmt_sif		= dev->cfg->num_mmt_sif;
	num_mmt_avf		= dev->cfg->num_mmt_avf;

	tlv_si_filters = kcalloc(num_tlvf, sizeof(TLV_SI_FILTER_T), GFP_KERNEL);
	CHECK_ERROR(tlv_si_filters == NULL, return -ENOMEM, "can't alloc memory");

	mmt_pid_filters = kcalloc(num_mmt_pidf, sizeof(MMT_PID_FILTER_T), GFP_KERNEL);
	CHECK_ERROR(mmt_pid_filters == NULL, return -ENOMEM, "can't alloc memory");

	mmt_si_filters = kcalloc(num_mmt_sif, sizeof(MMT_SI_FILTER_T), GFP_KERNEL);
	CHECK_ERROR(mmt_si_filters == NULL, return -ENOMEM, "can't alloc memory");

	mmt_av_filters = kcalloc(num_mmt_avf, sizeof(MMT_AV_FILTER_T), GFP_KERNEL);
	CHECK_ERROR(mmt_av_filters == NULL, return -ENOMEM, "can't alloc memory");

	filter_mm = te_mem_open(ARIB2_MEM_NAME);
	CHECK_ERROR(filter_mm == NULL, return -ENOMEM, "can't open mm");

	for (i = 0; i < dev->num_channel; i++) {
		ctrl = &dev->channels[i].filter;
		CHECK_ERROR(!ctrl, return -EFAULT, "invalid ch(%d)", i);

		INIT_LIST_HEAD(&ctrl->tlv_si_head);
		INIT_LIST_HEAD(&ctrl->mmt_pid_head);
		INIT_LIST_HEAD(&ctrl->mmt_si_head);
		INIT_LIST_HEAD(&ctrl->mmt_av_head);

		ctrl->tlv_si_req_num = 0;
		//ctrl->mmt_pid_req_num = 0;
		ctrl->mmt_si_req_num = 0;
		ctrl->mmt_av_req_num = 0;

		/* filter callback */
		INIT_LIST_HEAD(&ctrl->callback_head);
		spin_lock_init(&ctrl->callback_lock);
		INIT_WORK(&ctrl->callback_work, filter_callback_work);
	}

	TE_IPC_RegisterARIB2FilterCallback(ipc_receive_callback, dev);

	/* For MCU abnormal recovery */
	te_mcu_register_rcallback(get_te_device(dev), TE_MCU_FUNC_TYPE_ARIB2,
							  mcu_recovery_pre_callback,
							  mcu_recovery_post_callback, dev);

	return 0;
}

static void filter_dev_release(struct arib2_device *dev)
{

}

static const struct arib2_ioctl ioctl_filter = {
	.magic = ARIB2_IOC_CLK_MAGIC,
	.func = filter_dev_ioctl,
	.get_user_param = filter_dev_ioctl_param,
};

const struct arib2_sub_driver arib2_filter_driver = {
	.name = "arib2_filter",
	.init = filter_dev_init,
	.release = filter_dev_release,
	.suspend = filter_dev_suspend,
	.resume = filter_dev_resume,

	.ioctl = &ioctl_filter,
};

