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
 *  @author	Kyungseok Hyun ( ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2016-02-02
 *  @note		Additional information.
 */

#include "te_impl.h"

#include "ipc_core.h"
#include "ipc_mcu.h"

#define GET_IPC_OF_TYPE(type)				\
({							\
	struct ipc *_ipc_ = get_func_owner(type);	\
	if (!_ipc_)					\
		return -EINVAL;				\
	_ipc_;						\
})

#define GET_ATSC3_FLT_TYPE(type) (type & 0xF0)

#define to_mcu_addr(type, addr)		ipc_cpu_to_mcu_addr(ipc, type, addr)
#define to_mcu_cached_addr(addr)	to_mcu_addr(IPC_MEM_CACHED, addr)
#define to_mcu_uncached_addr(addr)	to_mcu_addr(IPC_MEM_UNCACHED, addr)
#define to_mcu_user_addr(addr)		to_mcu_addr(IPC_MEM_USER, addr)

#define to_cpu_addr(type, addr)		ipc_mcu_to_cpu_addr(ipc, type, addr)
#define to_cpu_cached_addr(addr)	to_cpu_addr(IPC_MEM_CACHED, addr)
#define to_cpu_uncached_addr(addr)	to_cpu_addr(IPC_MEM_UNCACHED, addr)
#define to_cpu_user_addr(addr)		to_cpu_addr(IPC_MEM_USER, addr)

static struct ipc *func_owner[IPC_FUNC_TYPE_MAX];

int _TE_IPC_SetFuncOwner(enum ipc_func_type type, struct ipc *ipc)
{
	if (type < IPC_FUNC_TYPE_MAX) {
		func_owner[type] = ipc;
		return 0;
	}

	return -EPERM;
}

static struct ipc *get_func_owner(enum ipc_func_type type)
{
	if (type < IPC_FUNC_TYPE_MAX)
		return func_owner[type];

	return NULL;
}

static int ipc_msg_status_init_done(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_STATUS_INIT_DONE_T *m = (void *)msg->payload;

	if (m->status != IPC_RET_OK) {
		log_error("%s: initialize error(%d)\n", ipc->name, m->status);
		// TODO: what to do ???
		return 0;
	}

	spin_lock(&ipc->spinlock);
	if (ipc->state != IPC_STATE_DISABLED) {
		ipc->state = IPC_STATE_READY;
		ipc->fw_ver = ipc->reg_read(ipc, IPC_REG_OFFSET_FW_VERSION);
		ipc->ipc_ver = ipc->reg_read(ipc, IPC_REG_OFFSET_IPC_VERSION);
	} else {
		log_mcu("%s: Received init msg but disabled", ipc->name);
	}

	if (ipc->init_callback.func)
		ipc->init_callback.func(&ipc->mcu_num, ipc->init_callback.arg);

	spin_unlock(&ipc->spinlock);

	log_mcu("%s: FW Ver[0x%x] Init Done", ipc->name, ipc->fw_ver);

	return 0;
}

static int ipc_msg_status_error(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_STATUS_ERROR_T *m = (IPC_MSG_STATUS_ERROR_T *)msg->payload;

	log_error("%s: critical error(%d)\n", ipc->name, m->type);

	// TODO: add callback handler & recover mcu f/w

	return 0;
}

int te_ipc_register_init_done_callback(struct ipc *ipc, ipc_msg_callback_t cb,
				       void *arg)
{
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->init_callback.func = cb;
	ipc->init_callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

/*------------------------------------------------------------------------------
 *   DEBUG Group
 *----------------------------------------------------------------------------*/
int te_ipc_write_data(const void *data, u32 size)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_WRITE_DATA, data, size);
}

int te_ipc_get_authority(enum ipc_authority_module m)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_GET_AUTH, &m, sizeof(m));
}

static int check_uncached_accessiblity(struct ipc *ipc, u32 sptr, u32 eptr)
{
#define MEM256_ALIGN_MASK 0xF0000000
	u32 slot_size;

	if (!ipc->slot_expand) { // Legacy slot (need align check)
		if ((sptr & MEM256_ALIGN_MASK) != (eptr & MEM256_ALIGN_MASK))
			return -EFAULT;
		slot_size = MCU_LEGACY_SRAM_SLOT_SIZE;
	} else {
		slot_size = MCU_SRAM_SLOT_SIZE;
	}

	if (sptr >= ipc->mem_addr && eptr <= (ipc->mem_addr + slot_size))
		return 1;
	else
		return 0;
}

int TE_IPC_StartInputDump(u8 ch, IPC_ADAP_DEBUG_DUMP_INFO_T *info)
{
	IPC_MSG_DEBUG_DUMP_START_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	IPC_BUF_STATUS_T *status;
	u32 buf_start, buf_end;
	u32 paddr;
	struct ipc_data_dump *dump;
	int rc;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];
	CHECK_ERROR(dump->enabled, return -EINVAL, "[%d] already started", ch);

	paddr = te_mem_alloc(ipc->ipc_mem_ctx, sizeof(IPC_BUF_STATUS_T),
			     "dump.status");
	CHECK_ERROR(!paddr, return -ENOMEM, "ipc mem alloc failed");

	status = IPC_PA_TO_VA(ipc, paddr);

	buf_start = info->saddr;
	buf_end = info->eaddr;
	rc = check_uncached_accessiblity(ipc, buf_start, buf_end);
	CHECK_ERROR(rc < 0, goto error, "access fail 0x%08x - 0x%08x",
					buf_start, buf_end);

	if (rc) {
		dump->mem_user_addr = 0;

		msg.buf_saddr = to_mcu_uncached_addr(buf_start);
		msg.buf_eaddr = to_mcu_uncached_addr(buf_end);
	} else {
		if (ipc->mem_user_addr) {
			log_error("already use user memory area !\n");
			rc = -EBUSY;
			goto error;
		}
		dump->mem_user_addr = buf_start;
		/* change ram base */
		ipc->set_user_addr(ipc, buf_start, buf_end - buf_start);

		msg.buf_saddr = to_mcu_user_addr(buf_start);
		msg.buf_eaddr = to_mcu_user_addr(buf_end);
	}

	msg.ch = ch;
	msg.reserved = 0;	// for backward compatibiliy

	if (ipc->ipc_ver >= 1) {	// support clock src/res after ver.1
		msg.use_timestamp = info->use_timestamp;
		msg.clock_src = info->clock_src;
	} else {
		msg.use_timestamp = (info->use_timestamp) ? 1 : 0;	// precision is not supported
		//clock_src: the field is reserved in old version but handled it anyway
		msg.clock_src = IPC_DUMP_CLK_GSTCC1;
	}

	msg.unit_size = info->unit_size;
	msg.status_addr = to_mcu_uncached_addr(paddr);

	/* initialize status buffer */
	status->waddr = msg.buf_saddr;
	status->raddr = msg.buf_saddr;
	status->pkt_cnt = 0;
	status->ovf_cnt = 0;

	if (info->type == IPC_DUMP_TYPE_FE_MAIN) {
		dump->type = IPC_DUMP_TYPE_FE_MAIN;
		rc = _TE_IPC_Send(ipc, IPC_TYPE_TS_MAIN_DUMP_START, &msg,
				  sizeof(msg));
	} else if(info->type == IPC_DUMP_TYPE_FE_ISR) {
		dump->type = IPC_DUMP_TYPE_FE_ISR;
		rc = _TE_IPC_Send(ipc, IPC_TYPE_TS_ISR_DUMP_START, &msg,
				  sizeof(msg));
	} else {
		dump->type = IPC_DUMP_TYPE_BE;
		rc = _TE_IPC_Send(ipc, IPC_TYPE_FILTER_DUMP_START, &msg,
				  sizeof(msg));

	}
	CHECK_ERROR(rc != 0, goto error, "failed _TE_IPC_Send");

	if (dump->mem_user_addr) {
		ipc->mem_user_addr = dump->mem_user_addr;
	}
	dump->status = status;
	dump->enabled = TRUE;

	log_noti("Started input dump - buffer(0x%08x~0x%08x)\n", buf_start,
		 buf_end);

	return rc;

error:
	te_mem_free(ipc->ipc_mem_ctx, paddr);

	return rc;
}

int TE_IPC_StopInputDump(u8 ch)
{
	IPC_MSG_DEBUG_DUMP_STOP_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	struct ipc_data_dump *dump;
	u32 paddr;
	int rc;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];
	CHECK_ERROR(!dump->enabled, return -EINVAL, "not enabled");

	msg.ch = ch;
	if (dump->type == IPC_DUMP_TYPE_FE_MAIN) {
		rc = _TE_IPC_Send(ipc, IPC_TYPE_TS_MAIN_DUMP_STOP, &msg,
				  sizeof(msg));
	} else if (dump->type == IPC_DUMP_TYPE_FE_ISR) {
		rc = _TE_IPC_Send(ipc, IPC_TYPE_TS_ISR_DUMP_STOP, &msg,
				  sizeof(msg));
	} else if (dump->type == IPC_DUMP_TYPE_BE) {
		rc = _TE_IPC_Send(ipc, IPC_TYPE_FILTER_DUMP_STOP, &msg,
				  sizeof(msg));
	}

	paddr = IPC_VA_TO_PA(ipc, dump->status);
	te_mem_free(ipc->ipc_mem_ctx, paddr);

	if (dump->mem_user_addr) {
		ipc->mem_user_addr = 0;
	}
	dump->enabled = FALSE;
	dump->status = NULL;

	return rc;
}

int TE_IPC_SetInputDumpRptr(u8 ch, u32 rptr)
{
	IPC_BUF_STATUS_T *status;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	struct ipc_data_dump *dump;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];
	CHECK_ERROR(!dump->enabled, return -EINVAL, "not enabled");

	status = dump->status;
	status->raddr = to_mcu_user_addr(rptr);

	return 0;
}

int TE_IPC_GetInputDumpWptr(u8 ch, u32 *wptr)
{
	IPC_BUF_STATUS_T *status;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	struct ipc_data_dump *dump;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];
	CHECK_ERROR(!dump->enabled, return -EINVAL, "not enabled");

	status = dump->status;
	*wptr = to_cpu_user_addr(status->waddr);

	return 0;
}

int TE_IPC_GetInputDumpBufStatus(u8 ch, IPC_BUF_STATUS_T *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	struct ipc_data_dump *dump;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];
	CHECK_ERROR(!dump->enabled, return -EINVAL, "not enabled");

	memcpy(status, dump->status, sizeof(*status));

	status->waddr = to_cpu_user_addr(status->waddr);
	status->raddr = to_cpu_user_addr(status->raddr);

	return 0;
}

int TE_IPC_RegisterDumpUpdateCallback(u8 ch, ipc_msg_callback_t callback,
				      void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	unsigned long flag;
	struct ipc_data_dump *dump;

	CHECK_PARAM(ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", ch);

	dump = &ipc->input_dump[ch];

	spin_lock_irqsave(&ipc->spinlock, flag);
	dump->callback.func = callback;
	dump->callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

static int ipc_msg_debug_dump_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_DUMP_DATA_T *m = (IPC_MSG_DUMP_DATA_T *)msg->payload;
	struct ipc_data_dump *dump;

	CHECK_PARAM(m->ch >= MAX_IPC_INPUT_DUMP, "invalid ch[%d]", m->ch);

	dump = &ipc->input_dump[m->ch];
	spin_lock(&ipc->spinlock);
	if (dump->enabled && dump->callback.func) {
		/* change mcu addr to cpu addr */
		if (dump->mem_user_addr) {
			m->buf_wptr = to_cpu_user_addr(m->buf_wptr);
		} else {
			m->buf_wptr = to_cpu_uncached_addr(m->buf_wptr);
		}
		dump->callback.func(m, dump->callback.arg);
	}
	spin_unlock(&ipc->spinlock);

	return 0;
}

static int ipc_msg_debug_log_msg(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_DEBUG_LOG_MSG_T *l = (IPC_MSG_DEBUG_LOG_MSG_T *)msg->payload;
	char *str = (char *)l->str;

	log_mcu("%s:: %s", ipc->name, str);

	return 0;
}

static int ipc_msg_debug_uart(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_DEBUG_UART_T *m = (IPC_MSG_DEBUG_UART_T *)msg->payload;

	if (m->use == 0) {
		TE_REG_SelectUart(TE_UART_CPU);
	} else {
		if (ipc->mcu_num == 0)
			TE_REG_SelectUart(TE_UART_MCU0);
		else
			TE_REG_SelectUart(TE_UART_MCU1);
	}

	return 0;
}

int te_ipc_enable_demod(u8 en)
{
	IPC_MSG_DEBUG_ENABLE_DEMOD_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DEMOD);

	msg.en = (en) ? 1 : 0;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_ENABLE_DEMOD, &msg,
			    sizeof(msg));
}

/*------------------------------------------------------------------------------
 *   FILTER Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RequestStreamFilter(u8 ch, const IPC_ADAP_FILTER_REQUEST_T *m)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	IPC_MSG_FILTER_REQUEST_T msg;
	volatile IPC_FILTER_STATUS_T *s;
	int rc;

	memset(&msg, 0, sizeof(msg));

	s = &ipc->filter.status[m->flt_idx];
	if (s->state != IPC_FILTER_STATE_IDLE)
		return -EBUSY;	//Check for mcu status

	msg.ch = ch;
	msg.gpb_saddr = to_mcu_uncached_addr(m->gpb_saddr);
	msg.gpb_eaddr = to_mcu_uncached_addr(m->gpb_eaddr);
	msg.flt_idx = m->flt_idx;
	msg.req_num = m->req_num;
	msg.pid = m->pid;
	msg.crc = m->crc;
	msg.one_shot = m->one_shot;
	msg.type = m->type;

	if (m->type == IPC_FILTER_REQUEST_SECTION) {
		memcpy(msg.value, m->value, sizeof(msg.value));
		memcpy(msg.mask, m->mask, sizeof(msg.mask));
		memcpy(msg.noteq, m->noteq, sizeof(msg.noteq));
	}

	s->gpb_rptr = msg.gpb_saddr;

	rc = _TE_IPC_Send(ipc, IPC_TYPE_FILTER_REQUEST, &msg, sizeof(msg));
	if (rc == -ETIME) {	//TIMEOUT recheck
		if (s->state == IPC_FILTER_STATE_RUNNING &&
		    s->req_num == msg.req_num) {
			log_warning("timeout but filter[%d] is running\n",
				    m->flt_idx);
			rc = 0;
		}
	}

	return rc;
}

int TE_IPC_CancelStreamFilter(u8 ch, u8 idx)
{
	int rc;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	IPC_MSG_FILTER_CANCEL_T msg;

	msg.ch = ch;
	msg.flt_idx = idx;

	rc = _TE_IPC_Send(ipc, IPC_TYPE_FILTER_CANCEL, &msg, sizeof(msg));
	if (rc == -ETIME) {	//TIMEOUT recheck
		volatile IPC_FILTER_STATUS_T *s;
		s = &ipc->filter.status[msg.flt_idx];

		if (s->state == IPC_FILTER_STATE_IDLE) {
			log_warning("timeout but filter[%d] is idle\n",
				    msg.flt_idx);
			rc = 0;
		}
	}

	return rc;
}

int TE_IPC_GetStreamFilterStatus(u16 idx, IPC_FILTER_STATUS_T *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	IPC_FILTER_STATUS_T *s;

	CHECK_PARAM(idx >= IPC_FILTER_COUNT, "over max filter idx(%d)", idx);
	CHECK_NULL_PARAM(status);

	s = &ipc->filter.status[idx];
	memcpy(status, s, sizeof(*s));

	return 0;
}

int TE_IPC_SetStreamFilterRptr(u16 idx, u32 ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	volatile IPC_FILTER_STATUS_T *s;

	CHECK_PARAM(idx >= IPC_FILTER_COUNT, "over max filter idx(%d)", idx);

	s = &ipc->filter.status[idx];
	s->gpb_rptr = to_mcu_uncached_addr(ptr);

	wmb();			//memory barrier for sync

	return 0;
}

int TE_IPC_GetStreamFilterWptr(u16 idx, u32 *ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	volatile IPC_FILTER_STATUS_T *s;

	CHECK_PARAM(idx >= IPC_FILTER_COUNT, "over max filter idx(%d)", idx);

	s = &ipc->filter.status[idx];
	*ptr = to_cpu_uncached_addr(s->gpb_wptr);

	return 0;
}

int TE_IPC_RegisterStreamFilterCallback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->filter.callback.func = callback;
	ipc->filter.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

static int ipc_msg_filter_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_FILTER_DATA_T *m = (IPC_MSG_FILTER_DATA_T *)msg->payload;
	struct ipc_callback *cb = &ipc->filter.callback;

	spin_lock(&ipc->spinlock);
	if (cb->func) {
		m->data_saddr = to_cpu_uncached_addr(m->data_saddr);
		m->data_eaddr = to_cpu_uncached_addr(m->data_eaddr);

		cb->func(m, cb->arg);
	}
	spin_unlock(&ipc->spinlock);

	return 0;
}

int te_ipc_request_temi_filter(u8 ch, IPC_ADAP_FILTER_REQUEST_T *f)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	IPC_MSG_TEMI_REQUEST_T msg;

	//TODO: consider status management

	msg.ch = ch;
	msg.idx = f->flt_idx;
	msg.req_num = f->req_num;
	msg.pid = f->pid;
	msg.gpb_saddr = to_mcu_uncached_addr(f->gpb_saddr);
	msg.gpb_eaddr = to_mcu_uncached_addr(f->gpb_eaddr);
	msg.unit_size = f->unit_size;

	return _TE_IPC_Send(ipc, IPC_TYPE_TEMI_REQUEST, &msg, sizeof(msg));
}

int te_ipc_cancel_temi_filter(u8 ch, u8 idx)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	IPC_MSG_TEMI_CANCEL_T msg;

	//TODO: consider status management
	//
	msg.ch = ch;
	msg.idx = idx;

	return _TE_IPC_Send(ipc, IPC_TYPE_TEMI_CANCEL, &msg, sizeof(msg));
}

int te_ipc_register_temi_callback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->temi.callback.func = callback;
	ipc->temi.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

static int ipc_msg_temi_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_TEMI_DATA_T *m = (IPC_MSG_TEMI_DATA_T *)msg->payload;
	struct ipc_callback *cb = &ipc->temi.callback;

	spin_lock(&ipc->spinlock);
	if (cb->func) {
		m->data_saddr = to_cpu_uncached_addr(m->data_saddr);
		m->data_eaddr = to_cpu_uncached_addr(m->data_eaddr);

		cb->func(m, cb->arg);
	}
	spin_unlock(&ipc->spinlock);

	return 0;
}

int te_ipc_send_filter_data(IPC_MSG_FILTER_SEND_DATA_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);

	return _TE_IPC_Send(ipc, IPC_TYPE_FILTER_SEND_DATA, msg,
			    sizeof(*msg));
}

int te_ipc_send_filter_xcas_data(IPC_MSG_FILTER_SEND_DATA_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_FILTER);

	return _TE_IPC_Send(ipc, IPC_TYPE_FILTER_XCAS_SEND_DATA, msg,
			    sizeof(*msg));
}

/*------------------------------------------------------------------------------
 *   TS Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RequestTsHeader(IPC_MSG_TS_HEADER_REQUEST_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	return _TE_IPC_Send(ipc, IPC_TYPE_TS_HEADER_REQUEST, msg, sizeof(*msg));
}

int TE_IPC_CancelTsHeader(IPC_MSG_TS_HEADER_CANCEL_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	return _TE_IPC_Send(ipc, IPC_TYPE_TS_HEADER_CANCEL, msg, sizeof(*msg));
}

int TE_IPC_RegisterTsHeaderCallback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->ts.header_callback.func = callback;
	ipc->ts.header_callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int TE_IPC_ChannelReset(u8 ch)
{
	IPC_MSG_TS_CH_RESET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	msg.ch = ch;

	return _TE_IPC_Send(ipc, IPC_TYPE_TS_CH_RESET, &msg, sizeof(msg));
}

int TE_IPC_GetChannelStatus(u8 ch, IPC_TS_CH_STATUS_T *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_TS);

	CHECK_PARAM(ch >= IPC_TS_CH_COUNT, "ch over max");

	memcpy(status, ipc->ts.ch_status + (ch * IPC_TS_CH_STATUS_SIZE),
	       sizeof(*status));

	return 0;
}

const char *TE_IPC_GetOverflowBufTypeStr(IPC_OVERFLOW_BUF_TYPE_T type)
{
	switch (type) {
	case IPC_OVERFLOW_TS_BUF:
		return "Input TS Buffer";
	case IPC_OVERFLOW_CLEAR_TS_BUF:
		return "Clear TS Buffer";
	case IPC_OVERFLOW_INTERNAL_TS_BUF:
		return "Internal TS Buffer";
	default:
		return "Unknown Type";
	}
}

static int ipc_msg_ts_header_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_TS_HEADER_DATA_T *m = (IPC_MSG_TS_HEADER_DATA_T *)msg->payload;

	spin_lock(&ipc->spinlock);
	if (ipc->ts.header_callback.func) {
		ipc->ts.header_callback.func(m, ipc->ts.header_callback.arg);
	}
	spin_unlock(&ipc->spinlock);

	return 0;
}

static int ipc_msg_ts_overflow(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_TS_OVERFLOW_T *m = (IPC_MSG_TS_OVERFLOW_T *)msg->payload;

	log_noti("CH[%d] - %s overflow count: %d\n",
		 m->ch, TE_IPC_GetOverflowBufTypeStr(m->type), m->cnt);

	return 0;
}

int te_ipc_set_predef_addr(struct ipc *ipc, u8 slot_num, u32 addr, u32 size)
{
	return ipc->set_predef_addr(ipc, slot_num, addr, size);
}

int te_ipc_enable_stcc(u8 idx, u8 en)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_ENABLE;
	msg.value = (en) ? 1 : 0;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_get_stcc(u8 idx, u32 *stcc_32, u32 *stcc_31_0)
{
	u32 val;

	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	val = ipc->reg_read(ipc, IPC_REG_OFFSET_STCC0 + idx * 0x4);
	*stcc_32 = (val & 0x80000000UL) ? 1 : 0;
	*stcc_31_0 = val << 1;

	return 0;
}

int te_ipc_set_stcc(u8 idx, u32 stcc_32, u32 stcc_31_0)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_COUNTER;
	msg.value = (stcc_31_0 >> 1) + ((stcc_32 & 0x1) << 31);

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_reset_stcc(u8 idx)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_RESET;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_set_stcc_freq(u8 idx, u32 freq)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_FREQ;
	msg.value = freq;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_set_stcc_copy_enable(u8 idx)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_COPY;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_set_stcc_source(u8 idx, enum pes_dest_type type)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_STCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_STC;
	msg.idx = idx;

	switch(type) {
	case IPC_CLK_PES_DEST_VD0:
	case IPC_CLK_PES_DEST_VD1:
		msg.mode = IPC_CLK_SET_MODE_VDEC;
		msg.value = (type == IPC_CLK_PES_DEST_VD0) ? 0 : 1;
		break;

	case IPC_CLK_PES_DEST_AD0:
	case IPC_CLK_PES_DEST_AD1:
		msg.mode = IPC_CLK_SET_MODE_ADEC;
		msg.value = (type == IPC_CLK_PES_DEST_AD0) ? 0 : 1;
		break;
	default:
		log_error("unknown type:%d", type);
		return -EINVAL;
	}

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_get_gstcc(u8 idx, u32 *gstcc_32, u32 *gstcc_31_0)
{
	u32 val;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_GSTCC_NUM, "invalid idx[%d]", idx);

	val = ipc->reg_read(ipc, IPC_REG_OFFSET_GSTCC0 + idx * 0x4);
	*gstcc_32 = (val & 0x80000000UL) ? 1 : 0;
	*gstcc_31_0 = val << 1;

	return 0;
}

int te_ipc_set_gstcc(u8 idx, u32 gstcc_32, u32 gstcc_31_0)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_GSTCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_GSTC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_COUNTER;
	msg.value = (gstcc_31_0 >> 1) + ((gstcc_32 & 0x1) << 31);

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_reset_gstcc(u8 idx)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_GSTCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_GSTC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_RESET;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_enable_gstcc(u8 idx, u8 en)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_GSTCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_GSTC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_ENABLE;
	msg.value = (en) ? 1 : 0;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_set_gstcc_freq(u8 idx, u32 freq)
{
	IPC_MSG_CLK_SET_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	CHECK_PARAM(idx >= MAX_IPC_GSTCC_NUM, "invalid idx[%d]", idx);

	msg.type = IPC_CLK_TYPE_GSTC;
	msg.idx = idx;
	msg.mode = IPC_CLK_SET_MODE_FREQ;
	msg.value = freq;

	return _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_SET_CLOCK, &msg, sizeof(msg));
}

int te_ipc_request_pcr_pid(u8 ch, u16 pid)
{
	IPC_MSG_TS_PCR_REQUEST_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);

	msg.ch = ch;
	msg.pid = pid;

	return _TE_IPC_Send(ipc, IPC_TYPE_TS_PCR_REQUEST, &msg, sizeof(msg));
}

int te_ipc_cancel_pcr_pid(u8 ch)
{
	IPC_MSG_TS_PCR_CANCEL_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);

	msg.ch = ch;

	return _TE_IPC_Send(ipc, IPC_TYPE_TS_PCR_REQUEST, &msg, sizeof(msg));
}

static int ipc_msg_pcr_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_TS_PCR_DATA_T *m = (IPC_MSG_TS_PCR_DATA_T *)msg->payload;
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);

	if (ipc->ts.pcr_callback.func)
		ipc->ts.pcr_callback.func(m, ipc->ts.pcr_callback.arg);

	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int te_ipc_register_pcr_callback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CLOCK);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->ts.pcr_callback.func = callback;
	ipc->ts.pcr_callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int te_ipc_get_main_perf_status(struct ipc *ipc, IPC_MAIN_PERF_TYPE_T type,
				IPC_DEBUG_MAIN_PERF_T *status)
{
	IPC_DEBUG_MAIN_PERF_T *s = ipc->mcu_perf_status;

	CHECK_PARAM(type >= IPC_MAIN_PERF_TYPE_MAX, "invalid type(%d)", type);
	CHECK_NULL_PARAM(status);

	*status = s[type];

	return 0;
}

/*------------------------------------------------------------------------------
 *   DSC Group
 *----------------------------------------------------------------------------*/
int TE_IPC_SetCipherMode(IPC_MSG_DSC_ALGO_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_ALGO, msg, sizeof(*msg));
}

int TE_IPC_SetCipherKey(IPC_MSG_DSC_KEY_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_KEY, msg, sizeof(*msg));
}

int te_ipc_send_dsc_data(IPC_MSG_DSC_SEND_DATA_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_SEND_DATA, msg, sizeof(*msg));
}

int te_ipc_send_xcas_data(IPC_MSG_DSC_XCAS_DATA_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_XCAS_SEND_DATA, msg,
			    sizeof(*msg));
}

int te_ipc_cancel_xcas_pid(IPC_MSG_DSC_XCAS_CANCEL_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_XCAS_CANCEL_PID, msg,
			    sizeof(*msg));
}

int te_ipc_register_dsc_callback(ipc_msg_callback_t cb, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->dsc.callback.func = cb;
	ipc->dsc.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int te_ipc_set_nagra_key(IPC_MSG_DSC_NAGRA_KMSG_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_NAGRA_KMSG, msg,
			    sizeof(*msg));
}

int te_ipc_cancel_nagra_pid(struct pid_cancel *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_NAGRA_PID_CANCEL, msg,
			    sizeof(*msg));
}

int te_ipc_get_nagra_nonce(IPC_MSG_DSC_NAGRA_REQUEST_NONCE_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_NAGRA_REQUEST_NONCE, msg,
			    sizeof(*msg));
}

static int ipc_msg_dsc_return_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	if (ipc->dsc.callback.func)
		ipc->dsc.callback.func(msg->payload, ipc->dsc.callback.arg);
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int te_ipc_set_nagra_state(IPC_MSG_DSC_NAGRA_SET_STATE_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_DESC);

	return _TE_IPC_Send(ipc, IPC_TYPE_DSC_NAGRA_SET_STATE, msg,
			    sizeof(*msg));
}

/*------------------------------------------------------------------------------
 *   CIP Group
 *----------------------------------------------------------------------------*/
int TE_IPC_StartCIPLUSUpload(u8 ch, u32 saddr, u32 eaddr,
			     u32 unit_size, u8 lts_id)
{
	IPC_MSG_CIP_IP_START_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;
	u32 paddr;

	CHECK_PARAM(ch >= IPC_CIPLUS_UP_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.up_buf + ch * IPC_CIP_CH_BUF_SIZE);
	/* If still use status_addr to send msg */
	paddr = IPC_VA_TO_PA(ipc, status);

	/* message info */
	msg.ch = ch;
	msg.dir = IPC_CIP_DIR_UPSTREAM;
	msg.lts_id = lts_id;
	msg.unit_size = unit_size;
	msg.buf_saddr = to_mcu_uncached_addr(saddr);
	msg.buf_eaddr = to_mcu_uncached_addr(eaddr);
	msg.status_addr = to_mcu_uncached_addr(paddr);

	/* status initialization */
	status->waddr = msg.buf_saddr;
	status->raddr = msg.buf_saddr;
	status->pkt_cnt = 0;
	status->ovf_cnt = 0;

	return _TE_IPC_Send(ipc, IPC_TYPE_CIP_IP_START, &msg, sizeof(msg));
}

int TE_IPC_StopCIPLUSUpload(u8 ch)
{
	IPC_MSG_CIP_IP_STOP_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);

	CHECK_PARAM(ch >= IPC_CIPLUS_UP_CH_COUNT, "over max channel(%d)", ch);
	msg.ch = ch;
	msg.dir = IPC_CIP_DIR_UPSTREAM;

	return _TE_IPC_Send(ipc, IPC_TYPE_CIP_IP_STOP, &msg, sizeof(msg));
}

int TE_IPC_GetCIPLUSUploadRptr(u8 ch, u32 *ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_UP_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.up_buf + ch * IPC_CIP_CH_BUF_SIZE);
	*ptr = to_cpu_uncached_addr(status->raddr);

	return 0;
}

int TE_IPC_UpdateCIPLUSUploadWptr(u8 ch, u32 ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_UP_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.up_buf + ch * IPC_CIP_CH_BUF_SIZE);
	status->waddr = to_mcu_uncached_addr(ptr);

	return 0;
}

int TE_IPC_GetCIPLUSUploadStatus(u8 ch, u32 *rptr, u32 *wptr, u32 *pkt_cnt,
				 u32 *ovf_cnt)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_UP_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.up_buf + ch * IPC_CIP_CH_BUF_SIZE);

	*rptr = status->raddr;
	*wptr = status->waddr;
	*pkt_cnt = status->pkt_cnt;
	*ovf_cnt = status->ovf_cnt;

	return 0;
}

int TE_IPC_StartCIPLUSDownload(u8 ch, u32 saddr, u32 eaddr,
			       u32 unit_size, u8 lts_id)
{
	IPC_MSG_CIP_IP_START_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;
	u32 paddr;

	CHECK_PARAM(ch >= IPC_CIPLUS_DN_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.dn_buf + ch * IPC_CIP_CH_BUF_SIZE);
	/* If still use status_addr to send msg */
	paddr = IPC_VA_TO_PA(ipc, status);

	/* message info */
	msg.ch = ch;
	msg.dir = IPC_CIP_DIR_DNSTREAM;
	msg.lts_id = lts_id;
	msg.unit_size = unit_size;
	msg.buf_saddr = to_mcu_uncached_addr(saddr);
	msg.buf_eaddr = to_mcu_uncached_addr(eaddr);
	msg.status_addr = to_mcu_uncached_addr(paddr);

	/* status initialization */
	status->waddr = msg.buf_saddr;
	status->raddr = msg.buf_saddr;
	status->pkt_cnt = 0;
	status->ovf_cnt = 0;

	return _TE_IPC_Send(ipc, IPC_TYPE_CIP_IP_START, &msg, sizeof(msg));
}

int TE_IPC_StopCIPLUSDownload(u8 ch)
{
	IPC_MSG_CIP_IP_STOP_T msg;
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);

	CHECK_PARAM(ch >= IPC_CIPLUS_DN_CH_COUNT, "over max channel(%d)", ch);
	msg.ch = ch;
	msg.dir = IPC_CIP_DIR_DNSTREAM;

	return _TE_IPC_Send(ipc, IPC_TYPE_CIP_IP_STOP, &msg, sizeof(msg));
}

int TE_IPC_GetCIPLUSDownloadWptr(u8 ch, u32 *ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_DN_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.dn_buf + ch * IPC_CIP_CH_BUF_SIZE);

	*ptr = to_cpu_uncached_addr(status->waddr);

	return 0;
}

int TE_IPC_UpdateCIPLUSDownloadRptr(u8 ch, u32 ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_DN_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.dn_buf + ch * IPC_CIP_CH_BUF_SIZE);
	status->raddr = to_mcu_uncached_addr(ptr);

	return 0;
}

int TE_IPC_GetCIPLUSDownloadStatus(u8 ch, u32 *rptr, u32 *wptr,
				   u32 *pkt_cnt, u32 *ovf_cnt)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	IPC_BUF_STATUS_T *status;

	CHECK_PARAM(ch >= IPC_CIPLUS_DN_CH_COUNT, "over max channel(%d)", ch);

	status = (void *)(ipc->cip.dn_buf + ch * IPC_CIP_CH_BUF_SIZE);

	*rptr = status->raddr;
	*wptr = status->waddr;
	*pkt_cnt = status->pkt_cnt;
	*ovf_cnt = status->ovf_cnt;

	return 0;
}

int TE_IPC_RegisterCIPLUSDataCallback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_CIP);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->cip.callback.func = callback;
	ipc->cip.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

static int ipc_msg_cip_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_CIP_IP_DATA_T *m = (IPC_MSG_CIP_IP_DATA_T *)msg->payload;
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	if (ipc->cip.callback.func) {
		m->buf_addr = to_cpu_uncached_addr(m->buf_addr);
		ipc->cip.callback.func(m, ipc->cip.callback.arg);
	}
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

/*------------------------------------------------------------------------------
 *   ATSC3.0 Group
 *----------------------------------------------------------------------------*/
int TE_IPC_RegisterATSC3FilterCallback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->atsc3.callback.func = callback;
	ipc->atsc3.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int TE_IPC_RequestATSC3Filter(u8 ch, IPC_ATSC3_FILTER_TYPE_T type, u8 idx,
			      u8 payload_len, void *payload)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	IPC_MSG_ATSC3_FLT_REQ_T msg;
	u32 msg_len = payload_len + sizeof(IPC_ATSC3_FLT_REQ_INFO_T);	// + FLT HEADER length
	u8 flt_type = GET_ATSC3_FLT_TYPE(type);
	int rc;

	/* Convert CPU adress to MCU address (including cp_ptr address in ROUTE) */
	if (flt_type == IPC_ATSC3_FILTER_TYPE_LKS) {
		IPC_ATSC3_LKS_REQ_PAYLOAD_T *p = payload;
		volatile IPC_ATSC3_LKS_STATUS_T *s;

		p->gpb_saddr = to_mcu_uncached_addr(p->gpb_saddr);
		p->gpb_eaddr = to_mcu_uncached_addr(p->gpb_eaddr);

		s = (void *)(ipc->atsc3.status.lks +
			     idx * IPC_ATSC3_LKS_STATUS_SIZE);
		s->gpb_rptr = p->gpb_saddr;
	} else if (flt_type == IPC_ATSC3_FILTER_TYPE_IP) {
		IPC_ATSC3_IP_REQ_PAYLOAD_T *p = payload;

		p->ipbuf_saddr = to_mcu_cached_addr(p->ipbuf_saddr);
		p->ipbuf_eaddr = to_mcu_cached_addr(p->ipbuf_eaddr);
	} else if (flt_type == IPC_ATSC3_FILTER_TYPE_UDP) {
		IPC_ATSC3_UDP_REQ_INFO_T *p = payload;	// header
		volatile IPC_ATSC3_UDP_STATUS_T *s;

		p->gpb_saddr = to_mcu_uncached_addr(p->gpb_saddr);
		p->gpb_eaddr = to_mcu_uncached_addr(p->gpb_eaddr);

		if (type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_OBJ ||
		    type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_SLS) {
			IPC_ATSC3_UDP_ROUTE_OBJ_REQ_PAYLOAD_T *obj = payload;
			if (obj->route_info.cp_num) {
				obj->route_info.cp_addr =
				    to_mcu_uncached_addr(obj->
							 route_info.cp_addr);
			}
		} else if (type == IPC_ATSC3_FILTER_TYPE_UDP_ROUTE_AV) {
			IPC_ATSC3_UDP_ROUTE_AV_REQ_PAYLOAD_T *av = payload;
			if (av->route_info.cp_num) {
				av->route_info.cp_addr =
				    to_mcu_uncached_addr(av->
							 route_info.cp_addr);
			}
		}

		s = (void *)(ipc->atsc3.status.udp +
			     idx * IPC_ATSC3_UDP_STATUS_SIZE);
		s->gpb_rptr = p->gpb_saddr;
	} else {
		log_error("Unknown filter type[%d]", type);
		return -EINVAL;
	}

	memset(&msg, 0, sizeof(msg));

	/* Make request message by given information */
	msg.info.ch = ch;
	msg.info.type = type;
	msg.info.flt_idx = idx;
	memcpy(msg.req_payload, payload, payload_len);

	rc = _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_FILTER_REQUEST, &msg, msg_len);

	return rc;
}

int TE_IPC_CancelATSC3Filter(IPC_MSG_ATSC3_FLT_CANCEL_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);

	return _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_FILTER_CANCEL, msg,
			    sizeof(*msg));
}

int TE_IPC_OpenATSC3Channel(u8 ch, IPC_ADAP_ATSC3_CHBUF_INFO_T *m)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	IPC_MSG_ATSC3_CH_OPEN_T msg;

	//FIXME : Send LGDemod Type to MCU
	msg.ch = ch;
	msg.metabuf_saddr = to_mcu_uncached_addr(m->metabuf_saddr);
	msg.metabuf_eaddr = to_mcu_uncached_addr(m->metabuf_eaddr);
	msg.databuf_saddr = to_mcu_cached_addr(m->databuf_saddr);
	msg.databuf_eaddr = to_mcu_cached_addr(m->databuf_eaddr);
	msg.bbbuf_saddr = to_mcu_cached_addr(m->bbbuf_saddr);
	msg.bbbuf_eaddr = to_mcu_cached_addr(m->bbbuf_eaddr);

	return _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_CH_OPEN, &msg, sizeof(msg));
}

int TE_IPC_CloseATSC3Channel(u8 ch)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	IPC_MSG_ATSC3_CH_CLOSE_T msg;

	msg.ch = ch;

	return _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_CH_CLOSE, &msg, sizeof(msg));
}

int TE_IPC_GetATSC3FilterStatus(u16 idx, u8 type, void *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	struct ipc_data_atsc3_status *a3;

	CHECK_NULL_PARAM(status);

	a3 = &(ipc->atsc3.status);

	if (type == IPC_ATSC3_FILTER_TYPE_PLP) {
		IPC_ATSC3_PLP_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_PLP_COUNT,
			    "PLP:over max filter idx(%d)", idx);

		s = (void *)(a3->plp + idx * IPC_ATSC3_PLP_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));
	} else if (type == IPC_ATSC3_FILTER_TYPE_LKS) {
		IPC_ATSC3_LKS_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_LKS_COUNT,
			    "LKS:over max filter idx(%d)", idx);

		s = (void *)(a3->lks + idx * IPC_ATSC3_LKS_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_uncached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_uncached_addr(s->gpb_rptr);
	} else if (type == IPC_ATSC3_FILTER_TYPE_IP) {
		IPC_ATSC3_IP_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_IP_COUNT,
			    "IP:over max filter idx(%d)", idx);

		s = (void *)(a3->ip + idx * IPC_ATSC3_IP_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_cached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_cached_addr(s->gpb_rptr);
	} else if (type == IPC_ATSC3_FILTER_TYPE_UDP) {
		IPC_ATSC3_UDP_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_UDP_COUNT,
			    "UDP:over max filter idx(%d)", idx);

		s = (void *)(a3->udp + idx * IPC_ATSC3_UDP_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_uncached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_uncached_addr(s->gpb_rptr);
	} else {
		log_error("Invalid type[%d]", type);
		return -EINVAL;
	}

	return 0;
}

int TE_IPC_GetATSC3ChannelStatus(u8 ch, IPC_ATSC3_CH_STATUS_T *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	struct ipc_data_atsc3_status *a3;
	IPC_ATSC3_CH_STATUS_T *s;

	CHECK_NULL_PARAM(status);

	a3 = &(ipc->atsc3.status);

	s = (IPC_ATSC3_CH_STATUS_T *)(a3->ch + ch * IPC_ATSC3_CH_STATUS_SIZE);
	memcpy(status, s, sizeof(*s));

	return 0;
}

//Not yet used
int TE_IPC_ControlATSC3(IPC_MSG_ATSC3_CONTROL_T *msg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);

	return _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_CONTROL, msg, sizeof(*msg));
}

int TE_IPC_SetATSC3FilterRptr(u16 idx, u8 type, u32 ptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	struct ipc_data_atsc3_status *a3;

	a3 = &(ipc->atsc3.status);

	if (type == IPC_ATSC3_FILTER_TYPE_LKS) {
		volatile IPC_ATSC3_LKS_STATUS_T *s;

		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_LKS_COUNT,
			    "LKS:over max filter idx(%d)", idx);

		s = (void *)(a3->lks + idx * IPC_ATSC3_LKS_STATUS_SIZE);
		s->gpb_rptr = to_mcu_uncached_addr(ptr);
	} else if (type == IPC_ATSC3_FILTER_TYPE_UDP) {
		volatile IPC_ATSC3_UDP_STATUS_T *s;

		CHECK_PARAM(idx >= IPC_ATSC3_FILTER_UDP_COUNT,
			    "UDP:over max filter idx(%d)", idx);

		s = (void *)(a3->udp + idx * IPC_ATSC3_UDP_STATUS_SIZE);
		s->gpb_rptr = to_mcu_uncached_addr(ptr);
	} else {
		log_error("Invalid type[%d]", type);
		return -EINVAL;
	}

	wmb();			//memory barrier for sync

	return 0;
}

static int ipc_msg_atsc3_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_ATSC3_DATA_T *m = (IPC_MSG_ATSC3_DATA_T *)msg->payload;
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	if (ipc->atsc3.callback.func) {
		u8 type = GET_ATSC3_FLT_TYPE(m->info.type);
		if (type == IPC_ATSC3_FILTER_TYPE_LKS) {
			m->lks.data_saddr =
			    to_cpu_uncached_addr(m->lks.data_saddr);
			m->lks.data_eaddr =
			    to_cpu_uncached_addr(m->lks.data_eaddr);
		} else if (type == IPC_ATSC3_FILTER_TYPE_UDP) {
			IPC_ATSC3_UDP_DATA_INFO_T *info;
			info = (IPC_ATSC3_UDP_DATA_INFO_T *)m->data_payload;

			info->data_saddr =
			    to_cpu_uncached_addr(info->data_saddr);
			info->data_eaddr =
			    to_cpu_uncached_addr(info->data_eaddr);
		}

		ipc->atsc3.callback.func(m, ipc->atsc3.callback.arg);
	}
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

/*------------------------------------------------------------------------------
 *   ARIB2 Group
 *----------------------------------------------------------------------------*/

int TE_IPC_RegisterARIB2FilterCallback(ipc_msg_callback_t callback, void *arg)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);
	ipc->arib2.callback.func = callback;
	ipc->arib2.callback.arg = arg;
	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int TE_IPC_OpenARIB2Channel(u8 ch, IPC_ADAP_ARIB2_CHBUF_INFO_T *info)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	IPC_MSG_ARIB2_CH_OPEN_T msg;

	msg.ch = ch;
	msg.meta_buf_saddr = to_mcu_uncached_addr(info->meta_saddr);
	msg.meta_buf_eaddr = to_mcu_uncached_addr(info->meta_eaddr);
	msg.data_buf_saddr = to_mcu_uncached_addr(info->data_saddr);
	msg.data_buf_eaddr = to_mcu_uncached_addr(info->data_eaddr);
	msg.temp_buf_saddr = to_mcu_uncached_addr(info->temp_saddr);
	msg.temp_buf_eaddr = to_mcu_uncached_addr(info->temp_eaddr);

	return _TE_IPC_Send(ipc, IPC_TYPE_ARIB2_CH_OPEN, &msg, sizeof(msg));
}

int TE_IPC_CloseARIB2Channel(u8 ch)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	IPC_MSG_ARIB2_CH_CLOSE_T msg;

	msg.ch = ch;

	return _TE_IPC_Send(ipc, IPC_TYPE_ARIB2_CH_CLOSE, &msg, sizeof(msg));
}

int TE_IPC_RequestARIB2Filter(u8 ch, u8 type, u8 idx, void *payload)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	IPC_MSG_ARIB2_FLT_REQ_T msg;
	u8 payload_len;
	u32 msg_len;

	if (type == IPC_ARIB2_FILTER_TYPE_TLV_SI) {
		IPC_ARIB2_TLV_SIGNAL_REQ_PAYLOAD_T *p = payload;
		volatile IPC_ARIB2_TLV_SI_FILTER_STATUS_T *s;

		p->gpb_saddr = to_mcu_uncached_addr(p->gpb_saddr);
		p->gpb_eaddr = to_mcu_uncached_addr(p->gpb_eaddr);

		s = (void *)(ipc->arib2.status.tlv_si +
			     idx * IPC_ARIB2_TLV_SI_FILTER_STATUS_SIZE);
		s->gpb_rptr = p->gpb_saddr;

		payload_len = sizeof(*p);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_PID) {
		IPC_ARIB2_MMT_PID_REQ_PAYLOAD_T *p = payload;

		p->seg_buf_saddr = to_mcu_cached_addr(p->seg_buf_saddr);
		p->seg_buf_eaddr = to_mcu_cached_addr(p->seg_buf_eaddr);

		payload_len = sizeof(*p);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_SI) {
		IPC_ARIB2_MMT_SIGNAL_REQ_PAYLOAD_T *p = payload;
		volatile IPC_ARIB2_MMT_SI_FILTER_STATUS_T *s;

		p->gpb_saddr = to_mcu_uncached_addr(p->gpb_saddr);
		p->gpb_eaddr = to_mcu_uncached_addr(p->gpb_eaddr);

		s = (void *)(ipc->arib2.status.mmt_si +
			     idx * IPC_ARIB2_MMT_SI_FILTER_STATUS_SIZE);
		s->gpb_rptr = p->gpb_saddr;

		payload_len = sizeof(*p);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_AV) {
		IPC_ARIB2_MMT_AV_REQ_PAYLOAD_T *p = payload;
		volatile IPC_ARIB2_MMT_AV_FILTER_STATUS_T *s;

		p->gpb_saddr = to_mcu_uncached_addr(p->gpb_saddr);
		p->gpb_eaddr = to_mcu_uncached_addr(p->gpb_eaddr);

		s = (void *)(ipc->arib2.status.mmt_av +
			     idx * IPC_ARIB2_MMT_AV_FILTER_STATUS_SIZE);
		s->gpb_rptr = p->gpb_saddr;

		payload_len = sizeof(*p);
	} else {
		log_error("Unknown filter type[%d]", type);
		return -EINVAL;
	}

	msg_len = payload_len + sizeof(IPC_ARIB2_FLT_REQ_INFO_T);
	memset(&msg, 0, sizeof(msg));

	/* Make request message by given information */

	msg.info.ch = ch;
	msg.info.type = type;
	msg.info.flt_idx = idx;
	memcpy(msg.req_payload, payload, payload_len);

	return _TE_IPC_Send(ipc, IPC_TYPE_ARIB2_FILTER_REQUEST, &msg, msg_len);
}

int TE_IPC_CancelARIB2Filter(u8 ch, u8 type, u8 idx)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	IPC_MSG_ARIB2_FLT_CANCEL_T msg;

	msg.ch = ch;
	msg.type = type;
	msg.flt_idx = idx;

	return _TE_IPC_Send(ipc, IPC_TYPE_ARIB2_FILTER_CANCEL, &msg,
			    sizeof(msg));
}

int TE_IPC_SetARIB2FilterRptr(u8 idx, u8 type, u32 rptr)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	struct ipc_data_arib2_status *arib2 = &(ipc->arib2.status);

	if (type == IPC_ARIB2_FILTER_TYPE_TLV_SI) {
		volatile IPC_ARIB2_TLV_SI_FILTER_STATUS_T *s;

		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_TLV_COUNT,
			    "TLV:over max filter idx(%d)", idx);

		s = (void *)(arib2->tlv_si +
			     idx * IPC_ARIB2_TLV_SI_FILTER_STATUS_SIZE);
		s->gpb_rptr = to_mcu_uncached_addr(rptr);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_SI) {
		volatile IPC_ARIB2_MMT_SI_FILTER_STATUS_T *s;

		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_MMT_SI_COUNT,
			    "MMT_SI:over max filter idx(%d)", idx);

		s = (void *)(arib2->mmt_si +
			     idx * IPC_ARIB2_MMT_SI_FILTER_STATUS_SIZE);
		s->gpb_rptr = to_mcu_uncached_addr(rptr);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_AV) {
		volatile IPC_ARIB2_MMT_AV_FILTER_STATUS_T *s;

		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_MMT_AV_COUNT,
			    "MMT_AV:over max filter idx(%d)", idx);

		s = (void *)(arib2->mmt_av +
			     idx * IPC_ARIB2_MMT_AV_FILTER_STATUS_SIZE);
		s->gpb_rptr = to_mcu_uncached_addr(rptr);
	} else {
		log_error("invalid type[%d]", type);
		return -EINVAL;
	}

	wmb();			//memory barrier for sync

	return 0;
}

static int ipc_msg_arib2_data(struct ipc *ipc, IPC_MSG_T *msg)
{
	IPC_MSG_ARIB2_DATA_T *m = (IPC_MSG_ARIB2_DATA_T *)msg->payload;
	unsigned long flag;

	spin_lock_irqsave(&ipc->spinlock, flag);

	if (ipc->arib2.callback.func) {
		IPC_MSG_ARIB2_DATA_INFO_T *info = &m->info;

		info->data_saddr = to_cpu_uncached_addr(info->data_saddr);
		info->data_eaddr = to_cpu_uncached_addr(info->data_eaddr);

		ipc->arib2.callback.func(m, ipc->arib2.callback.arg);
	}

	spin_unlock_irqrestore(&ipc->spinlock, flag);

	return 0;
}

int TE_IPC_GetARIB2ChannelStatus(u8 ch, IPC_ARIB2_CH_STATUS_T *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	struct ipc_data_arib2_status *arib2;
	IPC_ARIB2_CH_STATUS_T *s;

	CHECK_NULL_PARAM(status);

	arib2 = &(ipc->arib2.status);

	s = (void *)(arib2->ch + ch * IPC_ARIB2_CH_STATUS_SIZE);
	memcpy(status, s, sizeof(*s));

	return 0;
}

int TE_IPC_GetARIB2FilterStatus(u8 idx, u8 type, void *status)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ARIB2);
	struct ipc_data_arib2_status *arib2;

	CHECK_NULL_PARAM(status);

	arib2 = &ipc->arib2.status;

	if (type == IPC_ARIB2_FILTER_TYPE_TLV_SI) {
		IPC_ARIB2_TLV_SI_FILTER_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_TLV_COUNT,
			    "TLV: over max filter idx(%d)", idx);

		s = (void *)(arib2->tlv_si +
			     idx * IPC_ARIB2_TLV_SI_FILTER_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_uncached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_uncached_addr(s->gpb_rptr);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_PID) {
		IPC_ARIB2_MMT_PID_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_MMT_PID_COUNT,
			    "MMT_PID: over max filter idx(%d)", idx);

		s = (void *)(arib2->mmt_pid +
			     idx * IPC_ARIB2_MMT_PID_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_SI) {
		IPC_ARIB2_MMT_SI_FILTER_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_MMT_SI_COUNT,
			    "MMT_SI: over max filter idx(%d)", idx);

		s = (void *)(arib2->mmt_si +
			     idx * IPC_ARIB2_MMT_SI_FILTER_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_uncached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_uncached_addr(s->gpb_rptr);
	} else if (type == IPC_ARIB2_FILTER_TYPE_MMT_AV) {
		IPC_ARIB2_MMT_AV_FILTER_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_MMT_AV_COUNT,
			    "MMT_AV: over max filter idx(%d)", idx);

		s = (void *)(arib2->mmt_av +
			     idx * IPC_ARIB2_MMT_AV_FILTER_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));

		/* Convert mem addr to cpu based */
		s = status;
		s->gpb_wptr = to_cpu_uncached_addr(s->gpb_wptr);
		s->gpb_rptr = to_cpu_uncached_addr(s->gpb_rptr);
	} else if (type == IPC_ARIB2_FILTER_TYPE_IP) {
		IPC_ARIB2_IP_STATUS_T *s;
		CHECK_PARAM(idx >= IPC_ARIB2_FILTER_IP_COUNT,
			    "IP: over max filter idx(%d)", idx);

		s = (void *)(arib2->ip + idx * IPC_ARIB2_IP_STATUS_SIZE);
		memcpy(status, s, sizeof(*s));
	} else {
		log_error("ivalid type[%d]", type);
		return -EINVAL;
	}

	return 0;

}

//M23: Deprecated
int TE_IPC_SetEngineType(IPC_STATUS_ENGINE_TYPE_T type)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);
	IPC_MSG_STATUS_ENGINE_SEL_T msg;

	msg.type = type;

	return _TE_IPC_Send(ipc, IPC_TYPE_STATUS_ENGINE_SEL, &msg,
			    sizeof(msg));
}

int te_ipc_enable_atsc3_filter(void)
{
	struct ipc *ipc = GET_IPC_OF_TYPE(IPC_FUNC_TYPE_ATSC3);

	return _TE_IPC_Send(ipc, IPC_TYPE_ATSC3_ENABLE, NULL, 0);
}

/*------------------------------------------------------------------------------
 *   Removed
 *----------------------------------------------------------------------------*/

int TE_IPC_StartDownload(u8 ch, u32 buf_start, u32 buf_end, u32 unit_size)
{
	return -EPERM;
}

int TE_IPC_StopDownload(u8 ch)
{
	return -EPERM;
}

int TE_IPC_RegisterDownloadCallback(u8 ch, ipc_msg_callback_t callback,
				    void *arg)
{
	return -EPERM;
}

int TE_IPC_GetDownloadWptr(u8 ch, u32 *ptr)
{
	return -EPERM;
}

/*------------------------------------------------------------------------------
 *   IPC Receive - isr function
 *----------------------------------------------------------------------------*/
int _TE_IPC_Recv(struct ipc *ipc, IPC_MSG_T *msg)
{
	int rc;
	IPC_MSG_HEADER_T *h;

	h = &msg->header;
	switch (h->type) {
		/* STATUS */
	case IPC_TYPE_STATUS_INIT_DONE:
		rc = ipc_msg_status_init_done(ipc, msg);
		break;

	case IPC_TYPE_STATUS_ERROR:
		rc = ipc_msg_status_error(ipc, msg);
		break;

		/* DEBUG */
	case IPC_TYPE_DEBUG_LOG_MSG:
		rc = ipc_msg_debug_log_msg(ipc, msg);
		break;
	case IPC_TYPE_FILTER_DUMP_DATA:
	case IPC_TYPE_TS_DUMP_DATA:
		rc = ipc_msg_debug_dump_data(ipc, msg);
		break;

	case IPC_TYPE_DEBUG_UART:
		rc = ipc_msg_debug_uart(ipc, msg);
		break;

		/* FILTER */
	case IPC_TYPE_FILTER_DATA:
		rc = ipc_msg_filter_data(ipc, msg);
		break;

	case IPC_TYPE_TEMI_DATA:
		rc = ipc_msg_temi_data(ipc, msg);
		break;

		/* TS */
	case IPC_TYPE_TS_HEADER_DATA:
		rc = ipc_msg_ts_header_data(ipc, msg);
		break;
	case IPC_TYPE_TS_OVERFLOW:
		rc = ipc_msg_ts_overflow(ipc, msg);
		break;

		/* Descrambler */
	case IPC_TYPE_DSC_RETURN_DATA:
		rc = ipc_msg_dsc_return_data(ipc, msg);
		break;

		/* CI+1.4 */
	case IPC_TYPE_CIP_IP_DATA:
		rc = ipc_msg_cip_data(ipc, msg);
		break;

		/* ATSC3.0 */
	case IPC_TYPE_ATSC3_DATA:
		rc = ipc_msg_atsc3_data(ipc, msg);
		break;

		/* ATSC3.0 */
	case IPC_TYPE_ARIB2_DATA:
		rc = ipc_msg_arib2_data(ipc, msg);
		break;

		/* PCR WA */
	case IPC_TYPE_TS_PCR_DATA:
		rc = ipc_msg_pcr_data(ipc, msg);
		break;

	default:
		log_error("unknown type:%04x\n", h->type);
		rc = -EINVAL;
		break;
	}

	return rc;

}
