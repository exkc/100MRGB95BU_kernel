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
 *  @date		2016-02-02
 *  @note		Additional information.
 */

#ifndef _IPC_H_
#define _IPC_H_

#include <lg1k/te/ipc.h>

#include "te_impl.h"

#define MAX_IPC_NAME		16
#define MAX_RECV_QUEUE		2
#define MAX_IPC_INPUT_DUMP	6

#define MAX_IPC_STCC_NUM	4
#define MAX_IPC_GSTCC_NUM	2

#define IPC_PA_TO_VA(ipc, pa)	(void*)((uintptr_t)(pa) + (ipc)->ipc_mem_offset)
#define IPC_VA_TO_PA(ipc, va)	(u32)((uintptr_t)(va) - (ipc)->ipc_mem_offset)

enum ipc_state {
	IPC_STATE_DISABLED = 0,
	IPC_STATE_ENABLED,
	IPC_STATE_READY,
};

enum ipc_func_type {
	IPC_FUNC_TYPE_TS = 0,
	IPC_FUNC_TYPE_FILTER,
	IPC_FUNC_TYPE_DESC,
	IPC_FUNC_TYPE_CIP,
	IPC_FUNC_TYPE_ATSC3,
	IPC_FUNC_TYPE_ARIB2,
	IPC_FUNC_TYPE_CLOCK, //O22A0 workaround
	IPC_FUNC_TYPE_DEMOD, // unified only
	IPC_FUNC_TYPE_MAX,
};

enum ipc_mem_type {
	IPC_MEM_CACHED = 0,
	IPC_MEM_UNCACHED,
	IPC_MEM_USER,
	IPC_MEM_PREDEF0,
	IPC_MEM_PREDEF1,
	IPC_MEM_PREDEF2,
	IPC_MEM_TYPE_MAX
};

struct ipc_status {
	u8 ready;
	u32 fw_ver;
	u32 ipc_ver;

	u32 send_msg_count;
	u32 recv_msg_count;
	u32 timeout_count;

	u32 send_queue_overflow;
	u32 recv_queue_overflow[MAX_RECV_QUEUE];
	u32 mcu_int_queue_overflow;
};

enum ipc_queue_type {
	IPC_QUEUE_TYPE_SEND = 0,
	IPC_QUEUE_TYPE_RECV0,
	IPC_QUEUE_TYPE_RECV1,
	IPC_QUEUE_TYPE_MAX
};

struct ipc_queue {
	u8 *data;
	u16 seqnum;
	u32 count;		/* max msg count */
	u32 msg_size;		/* max msg size in bytes */
	volatile u32 *head;
	volatile u32 *tail;
};

struct ipc_callback {
	ipc_msg_callback_t func;
	void *arg;
};

struct ipc_data_dump {
	u8 enabled;
	enum ipc_dump_type type;
	u32 mem_user_addr;
	IPC_BUF_STATUS_T *status;
	struct ipc_callback callback;
};

struct ipc_data_filter {
	IPC_FILTER_STATUS_T *status;
	struct ipc_callback callback;
};

struct ipc_data_ts {
	u8 *ch_status;
	struct ipc_callback header_callback;
	struct ipc_callback pcr_callback;
};

struct ipc_data_atsc3_status {
	u8 *ch;
	u8 *plp;
	u8 *lks;
	u8 *ip;
	u8 *udp;
};

struct ipc_data_arib2_status {
	u8 *ch;
	u8 *tlv_si;
	u8 *ip;
	u8 *mmt_pid;
	u8 *mmt_si;
	u8 *mmt_av;
};

struct ipc_data_cip {
	u8 *up_buf;
	u8 *dn_buf;
	struct ipc_callback callback;
};

struct ipc_data_atsc3 {
	struct ipc_data_atsc3_status status;
	struct ipc_callback callback;
};

struct ipc_data_arib2 {
	struct ipc_data_arib2_status status;
	struct ipc_callback callback;
};

struct ipc_data_dsc {
	struct ipc_callback callback;
};

struct ipc_sram_slot_info {
	u32 mem_offset; // memory offset for address change
	u32 reg_offset; // register offset to notify base address
};

struct ipc {
	char name[MAX_IPC_NAME];
	u8 mcu_num;
	volatile enum ipc_state state;

	spinlock_t spinlock;
	struct mutex mutex;

	u32 chip;		/* chip revision for mcu */
	u32 fw_ver;
	u32 ipc_ver;

	u16 logmask[IPC_LOG_MODULE_MAX];
	/* configurable values */
	int irq_num;
	u8 __iomem *reg_base;	/* mcu reg base(ioremap) */
	u32 mem_addr;		/* base memory phys address - MCU:0x6000000 & 0x80000000 */
	u32 mem_user_addr;
	struct ipc_sram_slot_info slot[IPC_MEM_TYPE_MAX]; /* To convert addr(cpu/mcu) */
	bool slot_expand;
	u8 num_slot;

	u32 ipc_mem_size;
	u8 func[IPC_FUNC_TYPE_MAX];	/* supported functions */

	u32 promem_addr;

	/* mandotory functions */
	void (*reg_write)(struct ipc *ipc, u32 offset, u32 val);
	u32 (*reg_read)(struct ipc *ipc, u32 offset);

	void (*enable)(struct ipc *ipc);
	void (*disable)(struct ipc *ipc);

	int (*irq_status)(struct ipc *ipc);
	void (*irq_clear)(struct ipc *ipc);
	void (*irq_send)(struct ipc *ipc);

	int (*set_user_addr)(struct ipc *ipc, u32 addr, u32 size);
	int (*check_alive)(struct ipc *ipc);

	int (*set_logmask)(struct ipc *ipc, u16 module_mask, u16 value);
	int (*set_predef_addr)(struct ipc *ipc, u8 num, u32 addr, u32 size);

	/* ipc memory */
	struct te_mem_ctx *mcu_mem_ctx;	/* To allocate ipc totoal memory */
	char ipc_mem_name[MAX_IPC_NAME];
	u32 ipc_mem_addr;	/* allocated physical memory address for whole ipc */
	void *ipc_mem_base;	/* ioremapped(vmap) ipc_mem_addr */
	struct te_mem_ctx *ipc_mem_ctx;	/* memory allocator for each ipc data */
	ptrdiff_t ipc_mem_offset;	/* To translate virtual/phsical address */

	u32 queue_count[IPC_QUEUE_TYPE_MAX];
	struct ipc_queue send_queue;
	struct ipc_queue recv_queue[MAX_RECV_QUEUE];

	void *mcu_perf_status;

	/* ipc function data */
	struct ipc_data_ts ts;
	struct ipc_data_dump input_dump[MAX_IPC_INPUT_DUMP];
	struct ipc_data_atsc3 atsc3;
	struct ipc_data_filter filter;
	struct ipc_data_filter temi;
	struct ipc_data_cip cip;
	struct ipc_data_arib2 arib2;
	struct ipc_data_dsc dsc;

	/* Init done callback */
	struct ipc_callback init_callback;
};

// TODO: Check offset expansion
static inline u32 ipc_cpu_to_mcu_addr(struct ipc *ipc,
				      enum ipc_mem_type type, u32 addr)
{
	return (addr + ipc->slot[type].mem_offset);
}

static inline u32 ipc_mcu_to_cpu_addr(struct ipc *ipc,
				      enum ipc_mem_type type, u32 addr)
{
	return (addr - ipc->slot[type].mem_offset);
}

/* ipc.c */
int _TE_IPC_SetFuncOwner(enum ipc_func_type type, struct ipc *ipc);
int _TE_IPC_Recv(struct ipc *ipc, IPC_MSG_T *msg);
int te_ipc_register_init_done_callback(struct ipc *ipc, ipc_msg_callback_t cb,
				       void *arg);
int te_ipc_set_predef_addr(struct ipc *ipc, u8 slot_num, u32 addr, u32 size);
int te_ipc_get_main_perf_status(struct ipc *ipc, IPC_MAIN_PERF_TYPE_T type,
				IPC_DEBUG_MAIN_PERF_T *status);

/* ipc_mcu.c */
struct ipc *te_mcu_create_ipc(u8 num);

/* ipc_core.c */
int _TE_IPC_Enable(struct ipc *ipc);
int _TE_IPC_Disable(struct ipc *ipc);

int _TE_IPC_CheckReady(struct ipc *ipc);
int _TE_IPC_CheckAlive(struct ipc *ipc);
int _TE_IPC_GetStatus(struct ipc *ipc, struct ipc_status *status);

int _TE_IPC_SetLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask);
int _TE_IPC_EnableLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask);
int _TE_IPC_DisableLogMask(struct ipc *ipc, u16 module_mask, u16 level_mask);

int _TE_IPC_SetLogLevel(struct ipc *ipc, u8 module, u16 level_mask);
int _TE_IPC_GetLogLevel(struct ipc *ipc, u8 module, u16 *level_mask);

int _TE_IPC_SetConsoleEnable(struct ipc *ipc, bool enable);

#endif				/* _IPC_H_ */
