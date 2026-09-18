/*
 * SoC Center, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2025 by LG Electronics Inc.
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
 *  @author	Ilkyu Kim
 *  @version	1.0
 *  @date	2025-04-04
 *  @note	Additional information.
 */

#include <lg1k/te/mcu.h>

#include "te_impl.h"

#include "ipc_mcu.h"
#include "ipc_core.h"

#define INITIAL_LOGMASK		(1 << IPC_LOG_LEVEL_ERROR)

#define FILTER_RECV_MSG_COUNT	160	/* 256 * 160 = 40KB */

#ifdef TE_EMULATOR
#define reg_write(addr, val)	TE_EMUL_RegWrite((u32)(addr), val)
#define reg_read(addr)				\
({						\
	u32 _v_;				\
	TE_EMUL_RegRead((u32)(addr), &_v_);	\
	_v_;					\
})
#else
#define reg_write(addr, val)	__raw_writel(val, addr)
#define reg_read(addr)		__raw_readl(addr)
#endif

#define mcu_reg_write(ipc,ofs,val)	reg_write((ipc)->reg_base+(ofs),val)
#define mcu_reg_read(ipc,ofs)		reg_read((ipc)->reg_base+(ofs))

#define IPC_SET_ADDR_OFFSET(ipc,va,pa) \
  do{ (ipc)->ipc_mem_offset = (ptrdiff_t)(va) - (ptrdiff_t)(pa); } while(0)

#define GET_IPC_REG_ADDR(ipc, offset) \
  ((ipc)->reg_base + MCU_REG_OFFSET_IPC + (offset))

struct ipc_mcu_cfg {
	u32 ipc_mem_size;
	u8 num_func_type;
	const enum ipc_func_type *func_types;
};

struct ipc_queue_reg {
	u32 addr;
	u32 size;
	volatile u32 head;
	volatile u32 tail;
};

static const enum ipc_func_type legacy_mcu0_func_types[] = {	// ~ M16++/O18
	IPC_FUNC_TYPE_TS,
	IPC_FUNC_TYPE_DESC,
	IPC_FUNC_TYPE_CIP,
	IPC_FUNC_TYPE_ATSC3,
};

static const enum ipc_func_type mcu0_func_types[] = {
	IPC_FUNC_TYPE_TS,
	IPC_FUNC_TYPE_DESC,
	IPC_FUNC_TYPE_CIP,
	IPC_FUNC_TYPE_ATSC3,
	IPC_FUNC_TYPE_ARIB2,
	IPC_FUNC_TYPE_CLOCK,
};

static const enum ipc_func_type mcu1_func_types[] = {
	IPC_FUNC_TYPE_FILTER,
};

static const enum ipc_func_type uni_mcu_func_types[] = {
	IPC_FUNC_TYPE_TS,
	IPC_FUNC_TYPE_FILTER,
	IPC_FUNC_TYPE_DESC,
	IPC_FUNC_TYPE_CIP,
	IPC_FUNC_TYPE_ATSC3,
	IPC_FUNC_TYPE_DEMOD,
};

static const struct ipc_mcu_cfg mcu0_cfg_o18 = {
	.ipc_mem_size = 0x10000,	/* 64KB */

	.num_func_type = ARRAY_SIZE(legacy_mcu0_func_types),
	.func_types = legacy_mcu0_func_types,
};

static const struct ipc_mcu_cfg mcu0_cfg_normal = {
	.ipc_mem_size = 0x10000,	/* 64KB */

	.num_func_type = ARRAY_SIZE(mcu0_func_types),
	.func_types = mcu0_func_types,
};

static const struct ipc_mcu_cfg mcu1_cfg_normal = {
	.ipc_mem_size = 0x10000,	/* 64KB */

	.num_func_type = ARRAY_SIZE(mcu1_func_types),
	.func_types = mcu1_func_types,
};

/* unified mcu */
static const struct ipc_mcu_cfg uni_mcu_cfg_normal = {
	.ipc_mem_size = 0x18000,	/* 96KB */

	.num_func_type = ARRAY_SIZE(uni_mcu_func_types),
	.func_types = uni_mcu_func_types,
};

static void ipc_reg_write(struct ipc *ipc, u32 offset, u32 val)
{
	mcu_reg_write(ipc, offset + MCU_REG_OFFSET_IPC, val);
}

static u32 ipc_reg_read(struct ipc *ipc, u32 offset)
{
	return mcu_reg_read(ipc, offset + MCU_REG_OFFSET_IPC);
}

/* alloc ioremmaped(virtual) ipc memory */
static void *ipc_alloc_memory(struct ipc *ipc, const char *name, u32 size)
{
	u32 paddr;

	paddr = te_mem_alloc_user(ipc->ipc_mem_ctx, size, name, 0x10);
	if (!paddr)
		return NULL;

	return IPC_PA_TO_VA(ipc, paddr);
}

static void init_msg_queue(struct ipc *ipc, enum ipc_queue_type type)
{
	struct ipc_queue *q;
	u32 count;
	struct ipc_queue_reg *reg;
	const char *name;
	void *addr;
	u32 offset;

	switch (type) {
	case IPC_QUEUE_TYPE_SEND:
		q = &ipc->send_queue;
		offset = IPC_REG_OFFSET_CPU_SEND_QUEUE;
		name = "send_queue";
		break;

	case IPC_QUEUE_TYPE_RECV0:
		q = &ipc->recv_queue[0];
		offset = IPC_REG_OFFSET_MCU_SEND_QUEUE0;
		name = "recv_queue[0]";
		break;

	case IPC_QUEUE_TYPE_RECV1:
		q = &ipc->recv_queue[1];
		offset = IPC_REG_OFFSET_MCU_SEND_QUEUE1;
		name = "recv_queue[1]";
		break;

	default:
		return;
	}
	count = ipc->queue_count[type];

	reg = (struct ipc_queue_reg __force *)GET_IPC_REG_ADDR(ipc, offset);

	addr = ipc_alloc_memory(ipc, name, count * IPC_MAX_MSG_SIZE);
	CHECK_ERROR(!addr, return, "can't alloc ipc memory");

	q->data = addr;
	q->count = count;
	q->msg_size = IPC_MAX_MSG_SIZE;
	q->head = &reg->head;
	q->tail = &reg->tail;
}

static void set_status_register(struct ipc *ipc, u32 offset, void *vaddr)
{
	u32 paddr, mcu_addr;

	paddr = IPC_VA_TO_PA(ipc, vaddr);
	mcu_addr = ipc_cpu_to_mcu_addr(ipc, IPC_MEM_UNCACHED, paddr);

	ipc_reg_write(ipc, offset, mcu_addr);
}

static void init_msg_queue_register(struct ipc *ipc, enum ipc_queue_type type)
{
	struct ipc_queue *q;
	u32 paddr;
	struct ipc_queue_reg *reg;
	u32 offset;

	switch (type) {
	case IPC_QUEUE_TYPE_SEND:
		q = &ipc->send_queue;
		offset = IPC_REG_OFFSET_CPU_SEND_QUEUE;
		break;

	case IPC_QUEUE_TYPE_RECV0:
		q = &ipc->recv_queue[0];
		offset = IPC_REG_OFFSET_MCU_SEND_QUEUE0;
		break;

	case IPC_QUEUE_TYPE_RECV1:
		q = &ipc->recv_queue[1];
		offset = IPC_REG_OFFSET_MCU_SEND_QUEUE1;
		break;

	default:
		return;
	}

	reg = (struct ipc_queue_reg __force *)GET_IPC_REG_ADDR(ipc, offset);

	/* configure ipc register */
	paddr = IPC_VA_TO_PA(ipc, q->data);
	reg->addr = ipc_cpu_to_mcu_addr(ipc, IPC_MEM_UNCACHED, paddr);
	reg->size = q->count;
	reg->head = reg->tail = 0;

	q->seqnum = 0;
}

static void init_registers(struct ipc *ipc)
{
	u32 offset;

	/* clear ipc registers */
	memset_io(ipc->reg_base + MCU_REG_OFFSET_IPC, 0, MCU_REG_SIZE_IPC);

	/* clear ipc memory area */
	memset(ipc->ipc_mem_base, 0, ipc->ipc_mem_size);

	/* set chip version */
	ipc_reg_write(ipc, IPC_REG_OFFSET_CHIP_VERSION, ipc->chip);

	/* set ipc version */
	ipc_reg_write(ipc, IPC_REG_OFFSET_CPU_IPC_VERSION, IPC_VERSION);

	/* initialize send/recv msg queue register */
	init_msg_queue_register(ipc, IPC_QUEUE_TYPE_SEND);
	init_msg_queue_register(ipc, IPC_QUEUE_TYPE_RECV0);
	init_msg_queue_register(ipc, IPC_QUEUE_TYPE_RECV1);

	/* set status registers */
	if (ipc->func[IPC_FUNC_TYPE_TS]) {
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_SDEC_CH,
				    ipc->ts.ch_status);
	}

	if (ipc->func[IPC_FUNC_TYPE_FILTER]) {
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_SDEC_FILTER,
				    ipc->filter.status);
		ipc_reg_write(ipc, IPC_REG_OFFSET_DESC_PROMEM_BASE,
			      ipc->promem_addr);
	}

	if (ipc->func[IPC_FUNC_TYPE_ATSC3]) {
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ATSC3_CH,
				    ipc->atsc3.status.ch);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ATSC3_PLP,
				    ipc->atsc3.status.plp);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ATSC3_ALP,
				    ipc->atsc3.status.lks);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ATSC3_IP,
				    ipc->atsc3.status.ip);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ATSC3_UDP,
				    ipc->atsc3.status.udp);
	}

	if (ipc->func[IPC_FUNC_TYPE_ARIB2]) {
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_CH,
				    ipc->arib2.status.ch);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_TLV,
				    ipc->arib2.status.tlv_si);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_IP,
				    ipc->arib2.status.ip);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_MMT_PID,
				    ipc->arib2.status.mmt_pid);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_MMT_SI,
				    ipc->arib2.status.mmt_si);
		set_status_register(ipc, IPC_REG_OFFSET_STATUS_ARIB2_MMT_AV,
				    ipc->arib2.status.mmt_av);
	}

	if (ipc->func[IPC_FUNC_TYPE_DESC]) {
		ipc_reg_write(ipc, IPC_REG_OFFSET_DESC_PROMEM_BASE,
			      ipc->promem_addr);
	}

	set_status_register(ipc, IPC_REG_OFFSET_MAIN_PERF,
			    ipc->mcu_perf_status);

	/* set log mask */
	ipc_reg_write(ipc, IPC_REG_OFFSET_LOGMASK,
		      (0xFFFF << 16) | INITIAL_LOGMASK);

	/* set mcu registers */
	offset = ipc->slot[IPC_MEM_CACHED].reg_offset;
	mcu_reg_write(ipc, offset, ipc->mem_addr);
	offset = ipc->slot[IPC_MEM_UNCACHED].reg_offset;
	mcu_reg_write(ipc, offset, ipc->mem_addr);
}

static void irq_enable(struct ipc *ipc)
{
	mcu_reg_write(ipc, MCU_REG_OFFSET_E_INTR_EN, MCU_INTR_IPC_MASK);
}

static void irq_disable(struct ipc *ipc)
{
	mcu_reg_write(ipc, MCU_REG_OFFSET_E_INTR_EN, 0);
}

static int ipc_set_user_addr(struct ipc *ipc, u32 addr, u32 size)
{
	struct ipc_sram_slot_info *slot = &ipc->slot[IPC_MEM_USER];

	slot->mem_offset = MCU_DATA_USER_ADDR - addr;
	mcu_reg_write(ipc, slot->reg_offset, addr);

	return 0;
}

static int ipc_set_predef_addr(struct ipc *ipc, u8 num, u32 addr, u32 size)
{
	enum ipc_mem_type type = IPC_MEM_PREDEF0 + num;
	struct ipc_sram_slot_info *slot;
	u32 mcu_addr;

	if (!ipc->slot_expand)
		return -EFAULT;

	if (type >= IPC_MEM_TYPE_MAX)
		return -EINVAL;

	switch (type) {
	case IPC_MEM_PREDEF0:
		mcu_addr = MCU_DATA_PREDEF0_ADDR;
		break;
	case IPC_MEM_PREDEF1:
		mcu_addr = MCU_DATA_PREDEF1_ADDR;
		break;
	case IPC_MEM_PREDEF2:
	default:
		mcu_addr = MCU_DATA_PREDEF2_ADDR;
		break;
	}

	slot = &ipc->slot[type];
	slot->mem_offset = mcu_addr - addr;
	mcu_reg_write(ipc, slot->reg_offset, addr);

	return 0;
}

static void ipc_enable(struct ipc *ipc)
{
	mutex_lock(&ipc->mutex);
	if (ipc->state == IPC_STATE_DISABLED) {
		init_registers(ipc);
		ipc->state = IPC_STATE_ENABLED;
		irq_enable(ipc);
	}
	mutex_unlock(&ipc->mutex);
}

static void ipc_disable(struct ipc *ipc)
{
	unsigned long flag;

	mutex_lock(&ipc->mutex);
	spin_lock_irqsave(&ipc->spinlock, flag);
	if (ipc->state != IPC_STATE_DISABLED) {
		irq_disable(ipc);
		ipc->state = IPC_STATE_DISABLED;
	}
	spin_unlock_irqrestore(&ipc->spinlock, flag);
	mutex_unlock(&ipc->mutex);
}

static int ipc_irq_status(struct ipc *ipc)
{
	u32 status;

	status = mcu_reg_read(ipc, MCU_REG_OFFSET_E_INTR_ST);

	return (status & MCU_INTR_IPC_MASK) ? 1 : 0;
}

static void ipc_irq_clear(struct ipc *ipc)
{
	mcu_reg_write(ipc, MCU_REG_OFFSET_E_INTR_CL, MCU_INTR_IPC_MASK);
}

static void ipc_irq_send(struct ipc *ipc)
{
	mcu_reg_write(ipc, MCU_REG_OFFSET_INTR2MCU_EV, MCU_EV_IPC_MASK);
}

static int ipc_check_alive(struct ipc *ipc)
{
	int rc;

	mutex_lock(&ipc->mutex);
	if (ipc->state == IPC_STATE_READY) {
		IPC_MSG_STATUS_PING_T msg;

		msg.type = IPC_STATUS_PING_ALIVE;

		rc = _TE_IPC_Send(ipc, IPC_TYPE_STATUS_PING, &msg, sizeof(msg));
	} else {
		rc = -EIO;
	}
	mutex_unlock(&ipc->mutex);

	return rc;
}

static int ipc_set_logmask(struct ipc *ipc, UINT16 module_mask, UINT16 value)
{
	int rc;
	IPC_MSG_DEBUG_LOG_MASK_T msg;

	msg.module = module_mask;
	msg.value = value;

	rc = _TE_IPC_Send(ipc, IPC_TYPE_DEBUG_LOG_MASK, &msg, sizeof(msg));
	if (!rc) {
		int i;

		for (i = 0; i < IPC_LOG_MODULE_MAX; i++) {
			if (module_mask & (1 << i)) {
				ipc->logmask[i] = value;
			}
		}
	}

	return rc;
}

static void release_memory(struct ipc *ipc)
{
	if (ipc->ipc_mem_ctx) {
		te_mem_close(ipc->ipc_mem_ctx);
		te_mem_unregister(ipc->ipc_mem_name);
		vunmap_phys(ipc->ipc_mem_base);

		te_mem_close(ipc->mcu_mem_ctx);

		ipc->ipc_mem_ctx = NULL;
	}
}

static int init_memory(struct ipc *ipc)
{
	int rc;

	ipc->mcu_mem_ctx = te_mem_open(MCU_MEM_NAME);
	CHECK_ERROR(!ipc->mcu_mem_ctx, return -ENOMEM, "can't open mcu mm");

	snprintf(ipc->ipc_mem_name, MAX_IPC_NAME, "te_ipc_%u", ipc->mcu_num);

	ipc->ipc_mem_addr = te_mem_alloc(ipc->mcu_mem_ctx, ipc->ipc_mem_size,
					 ipc->ipc_mem_name);
	CHECK_ERROR(!ipc->ipc_mem_addr, goto error_alloc,
		    "can't alloc mcu memory\n");

	ipc->ipc_mem_base = vmap_phys(ipc->ipc_mem_addr, ipc->ipc_mem_size);
	CHECK_ERROR(!ipc->ipc_mem_base, goto error_vmap, "vmap_phys fail");

	rc = te_mem_register(ipc->ipc_mem_name, ipc->ipc_mem_addr,
			     ipc->ipc_mem_size, TE_MEM_TYPE_HMA);
	CHECK_ERROR(rc, goto error_register,
		    "Error in te_mem_register(%s)", ipc->ipc_mem_name);

	ipc->ipc_mem_ctx = te_mem_open(ipc->ipc_mem_name);
	CHECK_ERROR(!ipc->ipc_mem_ctx, goto error_open,
		    "Error in te_mem_open(%s)", ipc->ipc_mem_name);

	IPC_SET_ADDR_OFFSET(ipc, ipc->ipc_mem_base, ipc->ipc_mem_addr);

	return 0;

 error_open:
	te_mem_unregister(ipc->ipc_mem_name);
 error_register:
	vunmap_phys(ipc->ipc_mem_base);
 error_vmap:
 error_alloc:
	te_mem_close(ipc->mcu_mem_ctx);

	return -EIO;
}

static void ipc_release(struct ipc *ipc)
{
	release_memory(ipc);
}

static int ipc_init(struct ipc *ipc)
{
	int rc, i;
	u32 size;

	spin_lock_init(&ipc->spinlock);
	mutex_init(&ipc->mutex);

	rc = init_memory(ipc);
	CHECK_ERROR(rc, goto error, "Error in init_memory");

	/* initialize send/recv msg queue */
	init_msg_queue(ipc, IPC_QUEUE_TYPE_SEND);
	init_msg_queue(ipc, IPC_QUEUE_TYPE_RECV0);
	init_msg_queue(ipc, IPC_QUEUE_TYPE_RECV1);

	/* initialize log mask */
	for (i = 0; i < IPC_LOG_MODULE_MAX; i++)
		ipc->logmask[i] = INITIAL_LOGMASK;

#define ALLOC_STATUS_MEM(s, size)		\
do {						\
	(s) = ipc_alloc_memory(ipc, #s, size);	\
	if (!(s)) {				\
		log_error("can't alloc " #s);	\
		goto error; 			\
	}					\
} while(0)

	if (ipc->func[IPC_FUNC_TYPE_TS]) {
		struct ipc_data_ts *ts = &ipc->ts;

		size = IPC_TS_CH_STATUS_SIZE * IPC_TS_CH_COUNT;
		ALLOC_STATUS_MEM(ts->ch_status, size);
	}

	if (ipc->func[IPC_FUNC_TYPE_FILTER]) {
		struct ipc_data_filter *filter = &ipc->filter;

		size = sizeof(IPC_FILTER_STATUS_T) * IPC_FILTER_COUNT;
		ALLOC_STATUS_MEM(filter->status, size);
	}

	if (ipc->func[IPC_FUNC_TYPE_DESC]) {

	}

	if (ipc->func[IPC_FUNC_TYPE_CIP]) {
		struct ipc_data_cip *cip = &ipc->cip;

		size = IPC_CIP_CH_BUF_SIZE * IPC_CIPLUS_UP_CH_COUNT;
		ALLOC_STATUS_MEM(cip->up_buf, size);

		size = IPC_CIP_CH_BUF_SIZE * IPC_CIPLUS_DN_CH_COUNT;
		ALLOC_STATUS_MEM(cip->dn_buf, size);
	}

	if (ipc->func[IPC_FUNC_TYPE_ATSC3]) {
		struct ipc_data_atsc3 *atsc3 = &ipc->atsc3;

		size = IPC_ATSC3_CH_STATUS_SIZE * IPC_ATSC3_FILTER_CH_COUNT;
		ALLOC_STATUS_MEM(atsc3->status.ch, size);

		size = IPC_ATSC3_PLP_STATUS_SIZE * IPC_ATSC3_FILTER_PLP_COUNT;
		ALLOC_STATUS_MEM(atsc3->status.plp, size);

		size = IPC_ATSC3_IP_STATUS_SIZE * IPC_ATSC3_FILTER_IP_COUNT;
		ALLOC_STATUS_MEM(atsc3->status.ip, size);

		size = IPC_ATSC3_LKS_STATUS_SIZE * IPC_ATSC3_FILTER_LKS_COUNT;
		ALLOC_STATUS_MEM(atsc3->status.lks, size);

		size = IPC_ATSC3_UDP_STATUS_SIZE * IPC_ATSC3_FILTER_UDP_COUNT;
		ALLOC_STATUS_MEM(atsc3->status.udp, size);
	}

	if (ipc->func[IPC_FUNC_TYPE_ARIB2]) {
		struct ipc_data_arib2 *arib2 = &ipc->arib2;

		size = IPC_ARIB2_CH_STATUS_SIZE * IPC_ARIB2_FILTER_CH_COUNT;
		ALLOC_STATUS_MEM(arib2->status.ch, size);

		size = IPC_ARIB2_TLV_SI_FILTER_STATUS_SIZE *
		    IPC_ARIB2_FILTER_TLV_COUNT;
		ALLOC_STATUS_MEM(arib2->status.tlv_si, size);

		size = IPC_ARIB2_IP_STATUS_SIZE * IPC_ARIB2_FILTER_IP_COUNT;
		ALLOC_STATUS_MEM(arib2->status.ip, size);

		size = IPC_ARIB2_MMT_PID_STATUS_SIZE *
		    IPC_ARIB2_FILTER_MMT_PID_COUNT;
		ALLOC_STATUS_MEM(arib2->status.mmt_pid, size);

		size = IPC_ARIB2_MMT_SI_FILTER_STATUS_SIZE *
		    IPC_ARIB2_FILTER_MMT_SI_COUNT;
		ALLOC_STATUS_MEM(arib2->status.mmt_si, size);

		size = IPC_ARIB2_MMT_AV_FILTER_STATUS_SIZE *
		    IPC_ARIB2_FILTER_MMT_AV_COUNT;
		ALLOC_STATUS_MEM(arib2->status.mmt_av, size);
	}

	size = sizeof(IPC_DEBUG_MAIN_PERF_T) * IPC_MAIN_PERF_TYPE_MAX;
	ALLOC_STATUS_MEM(ipc->mcu_perf_status, size);

	return 0;

 error:
	ipc_release(ipc);

	return -EIO;
}

static int init_config(struct ipc *ipc, u8 num)
{
	int i;
	LX_TE_BLOCK_T block;
	struct te_config *chip_cfg = te_get_config();
	struct te_mem_region_info *mem_info;
	const struct ipc_mcu_cfg *ipc_cfg;
	u32 cached, uncached, user;

	CHECK_PARAM(num >= chip_cfg->num_mcu, "invalid mcu num[%d]\n", num);

	mem_info = te_get_mem_region_info(TE_MEM_TOTAL);

	ipc->irq_num = chip_cfg->mcu_irq_num[num];

	block = (num == 1) ? LX_TE_BLOCK_MCU1 : LX_TE_BLOCK_MCU0;
	ipc->reg_base = TE_REG_GetBaseAddr(block);

	ipc->mem_addr = mem_info->addr;

	if (lx_chip_rev() >= LX_CHIP_REV(O22, A0)) {
		ipc->num_slot = 6;
		cached = MCU_REG_OFFSET_SRAM_OFFSET_0;
		uncached = MCU_REG_OFFSET_SRAM_OFFSET_2;
		user = MCU_REG_OFFSET_SRAM_OFFSET_4;
		ipc->slot_expand = true;
	} else {
		ipc->num_slot = 3;
		cached = MCU_REG_OFFSET_SRAM_OFFSET_0;
		uncached = MCU_REG_OFFSET_SRAM_OFFSET_1;
		user = MCU_REG_OFFSET_SRAM_OFFSET_2;
		ipc->slot_expand = false;
	}

	ipc->slot[IPC_MEM_CACHED].mem_offset =
		(u32)(MCU_DATA_CACHED_ADDR - ipc->mem_addr);
	ipc->slot[IPC_MEM_UNCACHED].mem_offset =
		(u32)(MCU_DATA_UNCACHED_ADDR - ipc->mem_addr);
	ipc->slot[IPC_MEM_CACHED].reg_offset = cached;
	ipc->slot[IPC_MEM_UNCACHED].reg_offset = uncached;
	ipc->slot[IPC_MEM_USER].reg_offset = user;
	if (ipc->slot_expand) {
		ipc->slot[IPC_MEM_PREDEF0].reg_offset =
			MCU_REG_OFFSET_SRAM_OFFSET_1;
		ipc->slot[IPC_MEM_PREDEF1].reg_offset =
			MCU_REG_OFFSET_SRAM_OFFSET_3;
		ipc->slot[IPC_MEM_PREDEF2].reg_offset =
			MCU_REG_OFFSET_SRAM_OFFSET_5;
	}

	/* make ipc chip revision for mcu */
	switch (lx_chip()) {
	case LX_CHIP_E60:
		ipc->chip = IPC_CHIP_E60;
		break;
	case LX_CHIP_O20:
		ipc->chip = IPC_CHIP_O20;
		break;
	case LX_CHIP_O22:
		ipc->chip = IPC_CHIP_O22;
		break;
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		ipc->chip = IPC_CHIP_M23;
		break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	case LX_CHIP_O24:
		ipc->chip = IPC_CHIP_O24;
		break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
	case LX_CHIP_O26:
		ipc->chip = IPC_CHIP_O26;
		break;
#endif
	default:
		panic("not defined chip!0x%x\n", lx_chip());
	}

	ipc->chip |= (lx_chip_rev() & 0xFF);

	if (chip_cfg->num_mcu == 1) {
		ipc_cfg = &uni_mcu_cfg_normal;
	} else {
		if (num == 1) { //MCU1 - normal
			ipc_cfg = &mcu1_cfg_normal;
		} else { //MCU0
			if (lx_chip() == LX_CHIP_O18)
				ipc_cfg = &mcu0_cfg_o18;
			else // O20 ~
				ipc_cfg = &mcu0_cfg_normal;
		}
	}

	ipc->ipc_mem_size = ipc_cfg->ipc_mem_size;

	/* set supported functions */
	for (i = 0; i < ipc_cfg->num_func_type; i++) {
		ipc->func[ipc_cfg->func_types[i]] = true;
	}

	ipc->queue_count[IPC_QUEUE_TYPE_SEND] = IPC_MSG_SEND_MSG_COUNT;
	ipc->queue_count[IPC_QUEUE_TYPE_RECV0] = IPC_MSG_RECV_MSG_COUNT;
	ipc->queue_count[IPC_QUEUE_TYPE_RECV1] = IPC_MSG_RECV_MSG_COUNT;

	if (ipc->func[IPC_FUNC_TYPE_FILTER]) {
		ipc->queue_count[IPC_QUEUE_TYPE_RECV0] = FILTER_RECV_MSG_COUNT;
	}

	return 0;
}

struct ipc *te_mcu_create_ipc(u8 num)
{
	int rc, i;
	struct ipc *ipc;

	ipc = _TE_IPC_Create();
	CHECK_ERROR(!ipc, goto error, "Error in _TE_IPC_Create");

	/* init configurable values */
	rc = init_config(ipc, num);
	CHECK_ERROR(rc, goto error, "Error in init_config");

	ipc->mcu_num = num;
	snprintf(ipc->name, MAX_IPC_NAME, "TE_MCU[%u]", num);

	rc = ipc_init(ipc);
	CHECK_ERROR(rc, goto error, "Error in ipc_init");

	ipc->reg_write = ipc_reg_write;
	ipc->reg_read = ipc_reg_read;

	ipc->enable = ipc_enable;
	ipc->disable = ipc_disable;

	ipc->irq_status = ipc_irq_status;
	ipc->irq_clear = ipc_irq_clear;
	ipc->irq_send = ipc_irq_send;

	ipc->set_user_addr = ipc_set_user_addr;
	ipc->check_alive = ipc_check_alive;
	ipc->set_predef_addr = ipc_set_predef_addr;

	ipc->set_logmask = ipc_set_logmask;

	rc = _TE_IPC_Init(ipc);
	CHECK_ERROR(rc, goto error, "Error in TE_IPC_Init");

	/* register ipc handle to to ipc function */
	for (i = 0; i < IPC_FUNC_TYPE_MAX; i++) {
		if (ipc->func[i])
			_TE_IPC_SetFuncOwner(i, ipc);
	}

	return ipc;

 error:
	if (ipc) {
		ipc_release(ipc);
		_TE_IPC_Destroy(ipc);
	}

	return NULL;
}
