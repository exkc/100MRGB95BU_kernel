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
#include "te_reg_dumper.h"

#define CHECK_CHANNEL(ch)	\
  CHECK_PARAM((ch) > 3, "invalid channel(%d)\n", ch)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_ATSC3_MASK)) {		\
		log_noti("@ATSC3_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_ATSC3_MASK)) {		\
		log_noti("~ATSC3_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_ATSC3_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@ATSC3_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_ATSC3_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~ATSC3_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define HAL_FUNC(func, ...)					\
do {								\
	if (hal) {						\
		if(hal->func) 					\
			return hal->func(__VA_ARGS__);		\
		return -EPERM;					\
	}							\
} while(0)

struct atsc3_hal {
	int (*ATSC3_SetDemodType)(enum te_reg_atsc3_demod_type type);
	int (*ATSC3_SetChannelEnable)(u8 ch, u8 en);
	int (*ATSC3_SetDecoderLayer)(u8 ch, enum te_reg_atsc3_layer layer);
	int (*ATSC3_SetPLPFilter)(u8 ch, u8 en, u8 id);

	int (*ATSC3_SetMetaBuffer)(u8 ch, u32 sptr, u32 eptr);
	int (*ATSC3_GetMetaWptr)(u8 ch, u32 *wptr);
	int (*ATSC3_SetMetaRptr)(u8 ch, u32 rptr);
	int (*ATSC3_SetMetaUnitBufferSize)(u8 ch, u32 size);
	int (*ATSC3_SetMetaAlmostFullLevel)(u8 ch, u32 size);

	int (*ATSC3_SetDataBuffer)(u8 ch, u32 sptr, u32 eptr);
	int (*ATSC3_GetDataWptr)(u8 ch, u32 *wptr);
	int (*ATSC3_SetDataRptr)(u8 ch, u32 rptr);
	int (*ATSC3_SetDataUnitBufferSize)(u8 ch, u32 size);
	int (*ATSC3_SetDataAlmostFullLevel)(u8 ch, u32 size);

	int (*ATSC3_GetTimeStamp)(struct te_reg_atsc3_timestamp *timestamp);

	int (*ATSC3_SetIntrEnable)(u32 val, bool en);
	int (*ATSC3_GetIntrStatus)(u32 *val);
	int (*ATSC3_ClearIntr)(u32 val);

	int (*ATSC3_SetTimeSource)(u8 ch, u8 src);
	int (*ATSC3_SetGmauAwUser)(u8 val);
	int (*ATSC3_SetTimestampLatchEnable)(u8 ch, u8 en);
};

typedef struct {
	u8 version;
	u8 num_timesrc;
} A3_REG_CFG_T;

static const A3_REG_CFG_T a3_cfg_o18 = {
	.version = 0,
	.num_timesrc = 2,
};

static const A3_REG_CFG_T a3_cfg_m16p3 = {
	.version = 1,
	.num_timesrc = 4,
};

static const struct atsc3_hal *hal;
static const struct atsc3_hal dummy_hal;

static DEFINE_SPINLOCK(atsc3_reg_lock);

static const A3_REG_CFG_T *a3_reg_cfg;

int TE_REG_ATSC3_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_M19:
		a3_reg_cfg = &a3_cfg_m16p3;
		break;
	case LX_CHIP_O18:
		a3_reg_cfg = &a3_cfg_o18;
		break;
	default: // O20 ~
		hal = &dummy_hal;
		break;
	}

	return 0;
}

static int GetDemodRevisionIndex(enum te_reg_atsc3_demod_type type)
{
	int idx;

	switch (type) {
	case ATSC3_DEMOD_TYPE_A:
		idx = 0;
		break;
	case ATSC3_DEMOD_TYPE_B:
		idx = 1;
		break;
	case ATSC3_DEMOD_TYPE_C:
		idx = 2;
		break;
	default:
		idx = -1;
		break;
	}
	return idx;
}

int TE_REG_ATSC3_SetDemodType(u8 ch, enum te_reg_atsc3_demod_type type)
{
	unsigned long flag;
	int idx;

	HAL_FUNC(ATSC3_SetDemodType, type);

	TRACE_ENTER("ch=%d,type=%d", ch, type);

	idx = GetDemodRevisionIndex(type);
	CHECK_PARAM(idx < 0, "invalid demod type(%d)", type);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].conf);
	ATSC3_Wr01(a3_conf_ch[ch].conf, lgd_sel, idx);
	ATSC3_Wr01(a3_conf_ch[ch].conf, swreset, 1);
	ATSC3_WrFL(a3_conf_ch[ch].conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);
	return 0;
}

int TE_REG_ATSC3_SetChannelMode(u8 ch, enum te_reg_dumper_mode mode)
{
	switch (mode) {
	case DUMPER_MODE_RAW:
	case DUMPER_MODE_PVR:
	case DUMPER_MODE_LGC:
		return 0;
	default:
		return -EINVAL;
	}
}

int TE_REG_ATSC3_SetChannelEnable(u8 ch, bool en)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetChannelEnable, ch, en);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=%d", ch, en);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

// TODO: know sequence
	ATSC3_RdFL(a3_conf_ch[ch].conf);
	if (en) {
		ATSC3_Wr01(a3_conf_ch[ch].conf, swreset, 1);
		ATSC3_WrFL(a3_conf_ch[ch].conf);
	}

	ATSC3_Wr01(a3_conf_ch[ch].conf, enable, en ? 1 : 0);
	ATSC3_WrFL(a3_conf_ch[ch].conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

static int GetDecoderLayerIndex(enum te_reg_atsc3_layer layer)
{
	int idx;

	switch (layer) {
	case ATSC3_DECODER_LAYER_BYPASS:
	case ATSC3_DECODER_LAYER_LGC:
		idx = 0;
		break;
	case ATSC3_DECODER_LAYER_BB:
		idx = 1;
		break;
	case ATSC3_DECODER_LAYER_BB_PLP:
		idx = 2;
		break;
	case ATSC3_DECODER_LAYER_TIME_LGC:
		idx = 3;
		break;
	default:
		idx = -1;
		break;
	}

	return idx;
}

int TE_REG_ATSC3_SetDecoderLayer(u8 ch, enum te_reg_atsc3_layer layer)
{
	unsigned long flag;
	int idx;

	HAL_FUNC(ATSC3_SetDecoderLayer, ch, layer);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,layer=%d", ch, layer);

	idx = GetDecoderLayerIndex(layer);
	CHECK_PARAM(idx < 0, "invalid layer(%d)", layer);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].conf);
	ATSC3_Wr01(a3_conf_ch[ch].conf, layer_sel, idx);
	ATSC3_WrFL(a3_conf_ch[ch].conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetPLPFilter(u8 ch, bool en, u8 id)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetPLPFilter, ch, en, id);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=%d,id=%d", ch, en, id);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].conf);
	ATSC3_Wr01(a3_conf_ch[ch].conf, plp_flt_en, en ? 1 : 0);
	ATSC3_Wr01(a3_conf_ch[ch].conf, ref_plp_id, id);
	ATSC3_WrFL(a3_conf_ch[ch].conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetMetaBuffer(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetMetaBuffer, ch, sptr, eptr);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,sptr=0x%x,eptr=0x%x", ch, sptr, eptr);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].meta_sptr, sptr);
	ATSC3_Wr(a3_conf_ch[ch].meta_eptr, eptr);
	ATSC3_WrFL(a3_conf_ch[ch].meta_sptr);
	ATSC3_WrFL(a3_conf_ch[ch].meta_eptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_GetMetaWptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_GetMetaWptr, ch, wptr);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].meta_wptr);
	ATSC3_Rd(a3_conf_ch[ch].meta_wptr, *wptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	TRACE_EXIT("ch=%d,*wptr=0x%x", ch, *wptr);

	return 0;
}

int TE_REG_ATSC3_SetMetaRptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetMetaRptr, ch, rptr);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,rptr=0x%x", ch, rptr);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].meta_rptr, rptr);
	ATSC3_WrFL(a3_conf_ch[ch].meta_rptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetMetaUnitBufferSize(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetMetaUnitBufferSize, ch, size);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=%u", ch, size);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].meta_unit_buffer, size);
	ATSC3_WrFL(a3_conf_ch[ch].meta_unit_buffer);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetMetaAlmostFullLevel(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetMetaAlmostFullLevel, ch, size);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=%u", ch, size);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].meta_flevel, size);
	ATSC3_WrFL(a3_conf_ch[ch].meta_flevel);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetDataBuffer(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetDataBuffer, ch, sptr, eptr);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,sptr=0x%x,eptr=0x%x", ch, sptr, eptr);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].data_sptr, sptr);
	ATSC3_Wr(a3_conf_ch[ch].data_eptr, eptr);
	ATSC3_WrFL(a3_conf_ch[ch].data_sptr);
	ATSC3_WrFL(a3_conf_ch[ch].data_eptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_GetDataWptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_GetDataWptr, ch, wptr);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].data_wptr);
	ATSC3_Rd(a3_conf_ch[ch].data_wptr, *wptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	TRACE_VERBOSE_EXIT("ch=%d,*wptr=0x%x", ch, *wptr);

	return 0;
}

int TE_REG_ATSC3_SetDataRptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetDataRptr, ch, rptr);

	CHECK_CHANNEL(ch);

	TRACE_VERBOSE_ENTER("ch=%d,rptr=0x%x", ch, rptr);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].data_rptr, rptr);
	ATSC3_WrFL(a3_conf_ch[ch].data_rptr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetDataUnitBufferSize(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetDataUnitBufferSize, ch, size);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=%u", ch, size);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].data_unit_buffer, size);
	ATSC3_WrFL(a3_conf_ch[ch].data_unit_buffer);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetDataAlmostFullLevel(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetDataAlmostFullLevel, ch, size);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=%u", ch, size);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(a3_conf_ch[ch].data_flevel, size);
	ATSC3_WrFL(a3_conf_ch[ch].data_flevel);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_GetTimeStamp(u8 ch, struct te_reg_atsc3_timestamp *timestamp)
{
	unsigned long flag;
	u32 v;

	HAL_FUNC(ATSC3_GetTimeStamp, timestamp);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].tmode);
	ATSC3_RdFL(a3_conf_ch[ch].tdata_sec);
	ATSC3_RdFL(a3_conf_ch[ch].tdata_fsec);

	ATSC3_Rd01(a3_conf_ch[ch].tmode, timestamp_mode, v);
	switch (v) {
	case 1:
		timestamp->mode = ATSC3_TIMESTAMP_SEC_MSEC;
		break;
	case 2:
		timestamp->mode = ATSC3_TIMESTAMP_SEC_MSEC_USEC;
		break;
	case 3:
		timestamp->mode = ATSC3_TIMESTAMP_SEC_MSEC_USEC_NSEC;
		break;
	default:
		timestamp->mode = ATSC3_TIMESTAMP_NONE;
		break;
	}

	ATSC3_Rd(a3_conf_ch[ch].tdata_sec, timestamp->sec);
	ATSC3_Rd01(a3_conf_ch[ch].tdata_fsec, msec, timestamp->msec);
	ATSC3_Rd01(a3_conf_ch[ch].tdata_fsec, usec, timestamp->usec);
	ATSC3_Rd01(a3_conf_ch[ch].tdata_fsec, nsec, timestamp->nsec);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

#if 0				/* dummy data is 0 */
	if (timestamp->mode < 3) {
		timestamp->nsec = 0;
		if (timestamp->mode < 2) {
			timestamp->usec = 0;
			if (timestamp->mode < 1) {
				timestamp->msec = 0;
				timestamp->sec = 0;
			}
		}
	}
#endif

	return 0;
}

static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, DUMPER_INTR_META_WRITE_CH0},
	{0x1 << 1, DUMPER_INTR_META_WRITE_CH1},
	{0x1 << 2, DUMPER_INTR_META_WRITE_CH2},
	{0x1 << 3, DUMPER_INTR_META_WRITE_CH3},
	{0x1 << 4, DUMPER_INTR_META_UNIT_BUF_CH0},
	{0x1 << 5, DUMPER_INTR_META_UNIT_BUF_CH1},
	{0x1 << 6, DUMPER_INTR_META_UNIT_BUF_CH2},
	{0x1 << 7, DUMPER_INTR_META_UNIT_BUF_CH3},
	{0x1 << 8, DUMPER_INTR_META_AL_FULL_CH0},
	{0x1 << 9, DUMPER_INTR_META_AL_FULL_CH1},
	{0x1 << 10, DUMPER_INTR_META_AL_FULL_CH2},
	{0x1 << 11, DUMPER_INTR_META_AL_FULL_CH3},
	{0x1 << 12, DUMPER_INTR_DATA_UNIT_BUF_CH0},
	{0x1 << 13, DUMPER_INTR_DATA_UNIT_BUF_CH1},
	{0x1 << 14, DUMPER_INTR_DATA_UNIT_BUF_CH2},
	{0x1 << 15, DUMPER_INTR_DATA_UNIT_BUF_CH3},
	{0x1 << 16, DUMPER_INTR_DATA_AL_FULL_CH0},
	{0x1 << 17, DUMPER_INTR_DATA_AL_FULL_CH1},
	{0x1 << 18, DUMPER_INTR_DATA_AL_FULL_CH2},
	{0x1 << 19, DUMPER_INTR_DATA_AL_FULL_CH3},
	{0x1 << 20, DUMPER_INTR_TIMESTAMP_CH0},
	{0x1 << 21, DUMPER_INTR_TIMESTAMP_CH1},
	{0x1 << 22, DUMPER_INTR_TIMESTAMP_CH2},
	{0x1 << 23, DUMPER_INTR_TIMESTAMP_CH3},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

int TE_REG_ATSC3_SetIntrEnable(u32 val, bool en)
{
	u32 v, bits;
	unsigned long flag;

	HAL_FUNC(ATSC3_SetIntrEnable, val, en);

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	if (!val)
		return 0;

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(intr_cpu_en);
	ATSC3_Rd(intr_cpu_en, v);
	if (en)
		v |= bits;
	else
		v &= ~bits;
	ATSC3_Wr(intr_cpu_en, v);
	ATSC3_WrFL(intr_cpu_en);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_GetIntrStatus(u32 *val)
{
	u32 bits;
	unsigned long flag;

	HAL_FUNC(ATSC3_GetIntrStatus, val);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(intr_cpu_st);
	ATSC3_Rd(intr_cpu_st, bits);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	*val = GetIntrValue(bits);

	return 0;
}

int TE_REG_ATSC3_ClearIntr(u32 val)
{
	u32 bits;
	unsigned long flag;

	HAL_FUNC(ATSC3_ClearIntr, val);

	TRACE_ENTER("val=0x%x", val);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_Wr(intr_cpu_clr, bits);
	ATSC3_WrFL(intr_cpu_clr);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetTimeSource(u8 ch, u8 src)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetTimeSource, ch, src);
	if (a3_reg_cfg->version >= 1) {
		return TE_REG_SetGstccLatchSource(ch, src);
	}

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	CHECK_CHANNEL(ch);
	CHECK_PARAM(src >= a3_reg_cfg->num_timesrc, "invalid timesrc[%d]", src);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(time_src_sel);
	switch (src) {
	case 0:
		ATSC3_Wr01(time_src_sel, ts_sel0, ch);
		break;
	case 1:
		ATSC3_Wr01(time_src_sel, ts_sel1, ch);
		break;
	default:
		break;
	}
	ATSC3_WrFL(time_src_sel);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

int TE_REG_ATSC3_SetGmauAwUser(u8 val)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetGmauAwUser, val);

	TRACE_ENTER("val=%d", val);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(gmau_conf);
	ATSC3_Wr01(gmau_conf, aw_user, val);
	ATSC3_WrFL(gmau_conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}

//Function: M16P3 ~
int TE_REG_ATSC3_SetTimestampLatchEnable(u8 ch, bool en)
{
	unsigned long flag;

	HAL_FUNC(ATSC3_SetTimestampLatchEnable, ch, en);

	TRACE_ENTER("ch=%d en=%d", ch, en);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&atsc3_reg_lock, flag);

	ATSC3_RdFL(a3_conf_ch[ch].conf);
	ATSC3_Wr01(a3_conf_ch[ch].conf, ts_latch_en, (en) ? 1 : 0);
	ATSC3_WrFL(a3_conf_ch[ch].conf);

	spin_unlock_irqrestore(&atsc3_reg_lock, flag);

	return 0;
}
