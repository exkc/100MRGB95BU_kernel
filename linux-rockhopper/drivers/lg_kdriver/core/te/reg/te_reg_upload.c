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
 *  @date		2015-02-09
 *  @note		Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"

#define CHECK_IDX(idx)	\
  CHECK_PARAM(idx >= 2, "invalid idx(%d)\n", idx)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_UPLOAD_MASK)) {	\
		log_noti("@UPLOAD_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_UPLOAD_MASK)) {	\
		log_noti("~UPLOAD_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_UPLOAD_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@UPLOAD_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_UPLOAD_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~UPLOAD_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

struct up_reg_cfg {
	bool tp2tlv;
};

/* < O20 */
static const struct up_reg_cfg up_cfg_legacy = {
	.tp2tlv = false,
};

/* >= O20 */
static const struct up_reg_cfg up_cfg_normal = {
	.tp2tlv = true,
};


static const struct up_reg_cfg *up_cfg;

static spinlock_t upload_reg_lock[2] = {
	__SPIN_LOCK_UNLOCKED(upload_reg_lock[0]),
	__SPIN_LOCK_UNLOCKED(upload_reg_lock[1]),
};

int TE_REG_UPLOAD_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O18:
	case LX_CHIP_M19:
		up_cfg = &up_cfg_legacy;
		break;
	default: // O20 ~
		up_cfg = &up_cfg_normal;
		break;
	}

	return 0;
}

int TE_REG_SetUploadAutoCopyEn(u8 idx, bool en)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d", idx, en);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, auto_copy_en, (en) ? 1 : 0);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadTrickMode(u8 idx, enum te_reg_up_trick_mode mode)
{
	unsigned long flag;
	u32 v;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,mode=%d", idx, mode);

	switch (mode) {
	case UPLOAD_TRICK_MODE_NORMAL:
		v = 0;
		break;
	case UPLOAD_TRICK_MODE_2X:
		v = 1;
		break;
	case UPLOAD_TRICK_MODE_1DIV2:
		v = 2;
		break;
	case UPLOAD_TRICK_MODE_1DIV4:
		v = 3;
		break;
	default:
		log_error("not supported mode(%d)", mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, trick_mode, v);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadWaitMode(u8 idx, enum te_reg_up_wait_mode mode)
{
	unsigned long flag;
	u32 v;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,mode=%d", idx, mode);

	switch (mode) {
	case UPLOAD_WAIT_MODE_WAIT_CYCLE:
		v = 0;
		break;
	case UPLOAD_WAIT_MODE_TSD:
		v = 1;
		break;
	case UPLOAD_WAIT_MODE_TIMESTAMP:
		v = 2;
		break;
	default:
		log_error("not supported mode(%d)\n", mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, wait_mode, v);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadPacketType(u8 idx, enum te_reg_up_pkt_type type)
{
	unsigned long flag;
	u32 v;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,type=%d", idx, type);

	switch (type) {
	case UPLOAD_PKT_TYPE_188BYTE:
		v = 0;
		break;
	case UPLOAD_PKT_TYPE_192BYTE:
		v = 1;
		break;
	default:
		log_error("not supported type(%d)\n", type);
		return -EINVAL;
	}

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, data_type, v);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_ResetUpload(u8 idx)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d", idx);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, swreset0, 1);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadEnable(u8 idx, bool en)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d", idx, en);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, enable, (en) ? 1 : 0);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadPause(u8 idx, bool en)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d", idx, en);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_conf);
	UPLOAD_Wr01(idx, up_conf, pause, (en) ? 1 : 0);
	UPLOAD_WrFL(idx, up_conf);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadMaxJitter(u8 idx, u32 val)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,val=%d", idx, val);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_Wr(idx, up_max_jitter, val);
	UPLOAD_WrFL(idx, up_max_jitter);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadWaitCycle(u8 idx, u32 val)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,val=%d", idx, val);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_Wr(idx, up_wait_cycle, val);
	UPLOAD_WrFL(idx, up_wait_cycle);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadBuffer(u8 idx, u32 start, u32 end)
{
	unsigned long flag;

	CHECK_IDX(idx);

	CHECK_PARAM((start & 0xF), "start addr(%08x) not aligned to 16", start);
	CHECK_PARAM((end & 0xF), "end addr(%08x) not aligned to 16", end);

	TRACE_ENTER("idx=%d,start=0x%08x,end=0x%08x", idx, start, end);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_Wr(idx, up_start_ptr, start);
	UPLOAD_Wr(idx, up_end_ptr, end);

	UPLOAD_WrFL(idx, up_start_ptr);
	UPLOAD_WrFL(idx, up_end_ptr);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_SetUploadWptr(u8 idx, u32 wptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_VERBOSE_ENTER("idx=%d,wptr=0x%08x", idx, wptr);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_Wr(idx, up_write_ptr, wptr);
	UPLOAD_WrFL(idx, up_write_ptr);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_GetUploadRptr(u8 idx, u32 *rptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_read_ptr);
	UPLOAD_Rd(idx, up_read_ptr, *rptr);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	TRACE_VERBOSE_EXIT("idx=%d,*rptr=0x%08x", idx, *rptr);

	return 0;
}

int te_reg_upload_set_tlv_mode(u8 idx, u8 syncbyte, u8 mask)
{
	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,syncbyte=0x%x,mask=0x%x", idx, syncbyte, mask);

	if (!up_cfg->tp2tlv)
		return 0;

	UPLOAD_RdFL(idx, up_tp2tlv_conf);
	UPLOAD_Wr01(idx, up_tp2tlv_conf, sb_value, syncbyte);
	UPLOAD_Wr01(idx, up_tp2tlv_conf, sb_mask, mask);
	UPLOAD_WrFL(idx, up_tp2tlv_conf);

	return 0;
}

int te_reg_upload_set_tlv_enable(u8 idx, bool en)
{
	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,enable=%d", idx, en);

	if (!up_cfg->tp2tlv) {
		if (en)
			return -EPERM;

		return 0;
	}

	UPLOAD_RdFL(idx, up_tp2tlv_conf);
	UPLOAD_Wr01(idx, up_tp2tlv_conf, en, (en) ? 1 : 0);
	UPLOAD_WrFL(idx, up_tp2tlv_conf);

	return 0;
}

static u32 GetIntrRegBits(u32 val)
{
	u32 bits;

	bits = 0;
	if (val & UPLOAD_INTR_EMPTY)
		bits |= (0x1 << 0);

	return bits;
}

static u32 GetIntrValue(u32 bits)
{
	u32 val;

	val = 0;
	if (bits & (0x1 << 0))
		val |= UPLOAD_INTR_EMPTY;

	return val;
}

int TE_REG_SetUploadIntrEnable(u8 idx, u32 val, bool en)
{
	u32 v;
	u32 bits;
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,val=%d,en=%d", idx, val, en);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_intr_en_cpu);
	UPLOAD_Rd(idx, up_intr_en_cpu, v);
	if (en)
		v |= bits;
	else
		v &= ~bits;
	UPLOAD_Wr(idx, up_intr_en_cpu, v);
	UPLOAD_WrFL(idx, up_intr_en_cpu);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}

int TE_REG_GetUploadIntrStatus(u8 idx, u32 *val)
{
	u32 bits;
	unsigned long flag;

	CHECK_IDX(idx);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_RdFL(idx, up_intr_stat_cpu);
	UPLOAD_Rd(idx, up_intr_stat_cpu, bits);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	*val = GetIntrValue(bits);

	return 0;
}

int TE_REG_ClearUploadIntr(u8 idx, u32 val)
{
	u32 bits;
	unsigned long flag;

	CHECK_IDX(idx);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&upload_reg_lock[idx], flag);

	UPLOAD_Wr(idx, up_intr_clr_cpu, bits);
	UPLOAD_WrFL(idx, up_intr_clr_cpu);

	spin_unlock_irqrestore(&upload_reg_lock[idx], flag);

	return 0;
}
