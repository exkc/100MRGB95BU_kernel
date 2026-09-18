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

#define CHECK_CHANNEL(ch)	\
  CHECK_PARAM((ch)>=tsbuf_reg_cfg->num_ch, "invalid channel(%d)\n", ch)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_FE_MASK)) {		\
		log_noti("@FE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_FE_MASK)) {		\
		log_noti("~FE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_FE_MASK) &&		\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@FE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_FE_MASK) &&		\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~FE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

typedef struct {
	u8 version;
	u8 num_ch;
	u8 num_normal_ch;
} TSBUF_CFG_T;

/* M16+ ~ */
static const TSBUF_CFG_T tsbuf_cfg_normal = {
	.version = 0,
	.num_ch = 6,
	.num_normal_ch = 4,
};

static const TSBUF_CFG_T *tsbuf_reg_cfg;

static DEFINE_SPINLOCK(fe_tsbuf_reg_lock);

int TE_REG_FE_TSBUF_Init(void)
{
	tsbuf_reg_cfg = &tsbuf_cfg_normal;

	return 0;
}

int TE_REG_GetChannelInputBufferWptr(u8 ch, u32 *wptr)
{
	unsigned long flag;
	int idx;
	u32 val;

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&fe_tsbuf_reg_lock, flag);

	if (ch < 4) {
		idx = ch;

		FE_TSBUF_RdFL(tsbuf_ch[idx].mon);
		FE_TSBUF_Rd01(tsbuf_ch[idx].mon, wptr, val);
	} else {
		idx = ch - 4;

		FE_TSBUF_RdFL(tsbuf_sub_ch[idx].mon);
		FE_TSBUF_Rd01(tsbuf_sub_ch[idx].mon, wptr, val);
	}

	spin_unlock_irqrestore(&fe_tsbuf_reg_lock, flag);

	*wptr = val;
	TRACE_EXIT("ch=%d wptr = 0x%02x", ch, *wptr);

	return 0;
}

int TE_REG_ResetChannelInputBuffer(u8 ch)
{
	unsigned long flag;
	int idx;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	spin_lock_irqsave(&fe_tsbuf_reg_lock, flag);

	if (ch <= tsbuf_reg_cfg->num_normal_ch) {
		idx = ch;

		FE_TSBUF_RdFL(tsbuf_ch[idx].conf);
		FE_TSBUF_Wr01(tsbuf_ch[idx].conf, swreset, 1);
		FE_TSBUF_WrFL(tsbuf_ch[idx].conf);
	} else {
		idx = ch - tsbuf_reg_cfg->num_normal_ch;

		FE_TSBUF_RdFL(tsbuf_sub_ch[idx].conf);
		FE_TSBUF_Wr01(tsbuf_sub_ch[idx].conf, swreset, 1);
		FE_TSBUF_WrFL(tsbuf_sub_ch[idx].conf);
	}

	spin_unlock_irqrestore(&fe_tsbuf_reg_lock, flag);

	return 0;
}

static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, TSBUF_PACKET_INTR_CH0},
	{0x1 << 1, TSBUF_PACKET_INTR_CH1},
	{0x1 << 2, TSBUF_PACKET_INTR_CH2},
	{0x1 << 3, TSBUF_PACKET_INTR_CH3},
	{0x1 << 4, TSBUF_PACKET_INTR_SUB_CH0},
	{0x1 << 5, TSBUF_PACKET_INTR_SUB_CH1},
	{0x1 << 6, TSBUF_FULL_INTR_CH0},
	{0x1 << 7, TSBUF_FULL_INTR_CH1},
	{0x1 << 8, TSBUF_FULL_INTR_CH2},
	{0x1 << 9, TSBUF_FULL_INTR_CH3},
	{0x1 << 10, TSBUF_FULL_INTR_SUB_CH0},
	{0x1 << 11, TSBUF_FULL_INTR_SUB_CH1},
	{0x1 << 12, TSBUF_OVERFLOW_INTR_CH0},
	{0x1 << 13, TSBUF_OVERFLOW_INTR_CH1},
	{0x1 << 14, TSBUF_OVERFLOW_INTR_CH2},
	{0x1 << 15, TSBUF_OVERFLOW_INTR_CH3},
	{0x1 << 16, TSBUF_OVERFLOW_INTR_SUB_CH0},
	{0x1 << 17, TSBUF_OVERFLOW_INTR_SUB_CH1},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

int TE_REG_SetTsBufIntrEnable(u32 val, bool en)
{
	u32 v, bits;
	unsigned long flag;

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	if (!val)
		return 0;

	bits = GetIntrRegBits(val);
	spin_lock_irqsave(&fe_tsbuf_reg_lock, flag);

	FE_TSBUF_RdFL(tsbuf_intr_en_cpu);
	FE_TSBUF_Rd(tsbuf_intr_en_cpu, v);

	if (en)
		v |= bits;
	else
		v &= ~bits;

	FE_TSBUF_Wr(tsbuf_intr_en_cpu, v);
	FE_TSBUF_WrFL(tsbuf_intr_en_cpu);

	spin_unlock_irqrestore(&fe_tsbuf_reg_lock, flag);

	return 0;
}

int TE_REG_GetTsBufIntrStatus(u32 *val)
{
	u32 bits;
	unsigned long flag;

	spin_lock_irqsave(&fe_tsbuf_reg_lock, flag);

	FE_TSBUF_RdFL(tsbuf_intr_stat_cpu);
	FE_TSBUF_Rd(tsbuf_intr_stat_cpu, bits);

	spin_unlock_irqrestore(&fe_tsbuf_reg_lock, flag);

	*val = GetIntrValue(bits);

	TRACE_EXIT("val=0x%x", *val);

	return 0;
}

int TE_REG_ClearTsBufIntr(u32 val)
{
	u32 bits;
	unsigned long flag;

	TRACE_ENTER("val=0x%x", val);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&fe_tsbuf_reg_lock, flag);

	FE_TSBUF_Wr(tsbuf_intr_clr_cpu, bits);
	FE_TSBUF_WrFL(tsbuf_intr_clr_cpu);

	spin_unlock_irqrestore(&fe_tsbuf_reg_lock, flag);

	return 0;
}

