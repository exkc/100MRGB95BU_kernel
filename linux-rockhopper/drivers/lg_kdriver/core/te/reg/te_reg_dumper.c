/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  dumper register access API
 *
 *  @author	Ilkyu Kim ( ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-08-23
 *  @note		Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"
#include "te_reg_dumper.h"

#define NUM_DUMPER_CHANNEL	4

#define CHECK_CHANNEL(ch)	\
  CHECK_PARAM((ch) >= NUM_DUMPER_CHANNEL, "invalid channel(%d)\n", ch)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_DUMPER_MASK)) {	\
		log_noti("@DUMPER_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_DUMPER_MASK)) {	\
		log_noti("~DUMPER_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_DUMPER_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@DUMPER_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_DUMPER_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~DUMPER_REG : %s(" fmt ")", __func__, ##args);\
	}								\
} while(0)

#define LEGACY_FUNC(func, ...)						\
do {									\
	if (legacy_func) {						\
		if (legacy_func->func) 					\
			return legacy_func->func(__VA_ARGS__);		\
		return -EINVAL;						\
	}								\
} while(0)

#define LEGACY_HAL_ATSC3(func, ...)					\
do {									\
	if (use_legacy) {						\
		if (legacy_atsc3.func) 					\
			return legacy_atsc3.func(__VA_ARGS__);		\
		return -EINVAL;						\
	}								\
} while(0)

#define LEGACY_HAL_ARIB2(func, ...)					\
do {									\
	if (use_legacy) {						\
		if (legacy_arib2.func) 					\
			return legacy_arib2.func(__VA_ARGS__);		\
		return -EINVAL;						\
	}								\
} while(0)


typedef struct {
	int (*SetIntrEnable)(u32 val, bool en);
	int (*GetIntrStatus)(u32 *val);
	int (*ClearIntr)(u32 val);

	int (*SetChannelMode)(u8 ch, enum te_reg_dumper_mode mode);
	int (*SetChannelEnable)(u8 ch, bool en);
	int (*SetLatchEnable)(u8 ch, bool en);
	int (*SetTimeSource)(u8 ch, u8 src);

	int (*SetDataBuffer)(u8 ch, u32 sptr, u32 eptr);
	int (*GetDataWptr)(u8 ch, u32 *wptr);
	int (*SetDataRptr)(u8 ch, u32 rptr);

	int (*SetMetaBuffer)(u8 ch, u32 sptr, u32 eptr);
	int (*GetMetaWptr)(u8 ch, u32 *wptr);
	int (*SetMetaRptr)(u8 ch, u32 rptr);

	int (*SetDataFullLevel)(u8 ch, u32 level);
	int (*SetDataUnitBufferSize)(u8 ch, u32 size);
	int (*SetMetaFullLevel)(u8 ch, u32 level);
	int (*SetMetaUnitBufferSize)(u8 ch, u32 size);

	int (*SetGmauAwUser)(u8 val);
} LEGACY_FUNC_T;

struct legacy_hal_atsc3 {
	int (*SetDemodType)(u8 ch, enum te_reg_atsc3_demod_type type);
	int (*SetDecoderLayer)(u8 ch, enum te_reg_atsc3_layer layer);
	int (*SetPLPFilter)(u8 ch, bool en, u8 id);
	int (*GetTimeStamp)(u8 ch, struct te_reg_atsc3_timestamp *ts);
};

struct legacy_hal_arib2 {
	int (*SetNTPConf)(u8 ch, bool len_check, bool swreset);
	int (*SetNTPSrcAddress)(u8 ch, u32 *val, u32 *mask);
	int (*SetNTPDstAddress)(u8 ch, u32 *val, u32 *mask);
	int (*SetUDPPortValue)(u8 ch, u32 src, u32 dst);
	int (*SetUDPPortMask)(u8 ch, u32 src, u32 dst);
	int (*GetNTPInfo)(u8 ch, struct te_reg_arib2_ntp_info *info);
};



static enum te_reg_engine_mode engine_mode;
static bool use_legacy;
static const LEGACY_FUNC_T *legacy_func;

static DEFINE_SPINLOCK(dumper_reg_lock);

static const LEGACY_FUNC_T legacy_func_atsc3 = {
	.SetIntrEnable = TE_REG_ATSC3_SetIntrEnable,
	.GetIntrStatus = TE_REG_ATSC3_GetIntrStatus,
	.ClearIntr = TE_REG_ATSC3_ClearIntr,

	.SetChannelMode = TE_REG_ATSC3_SetChannelMode,
	.SetChannelEnable = TE_REG_ATSC3_SetChannelEnable,
	.SetLatchEnable = TE_REG_ATSC3_SetTimestampLatchEnable,
	.SetTimeSource = TE_REG_ATSC3_SetTimeSource,

	.SetDataBuffer = TE_REG_ATSC3_SetDataBuffer,
	.GetDataWptr = TE_REG_ATSC3_GetDataWptr,
	.SetDataRptr = TE_REG_ATSC3_SetDataRptr,
	.SetMetaBuffer = TE_REG_ATSC3_SetMetaBuffer,
	.GetMetaWptr = TE_REG_ATSC3_GetMetaWptr,
	.SetMetaRptr = TE_REG_ATSC3_SetMetaRptr,
	.SetDataFullLevel = TE_REG_ATSC3_SetDataAlmostFullLevel,
	.SetDataUnitBufferSize = TE_REG_ATSC3_SetDataUnitBufferSize,
	.SetMetaFullLevel = TE_REG_ATSC3_SetMetaAlmostFullLevel,
	.SetMetaUnitBufferSize = TE_REG_ATSC3_SetMetaUnitBufferSize,
	.SetGmauAwUser = TE_REG_ATSC3_SetGmauAwUser,
};

static const LEGACY_FUNC_T legacy_func_arib2 = {
	.SetIntrEnable = TE_REG_ARIB2_SetIntrEnable,
	.GetIntrStatus = TE_REG_ARIB2_GetIntrStatus,
	.ClearIntr = TE_REG_ARIB2_ClearIntr,

	.SetChannelMode = TE_REG_ARIB2_SetChannelMode,
	.SetChannelEnable = TE_REG_ARIB2_SetChannelEnable,
	.SetLatchEnable = TE_REG_ARIB2_SetLatchEnable,
	.SetTimeSource = TE_REG_ARIB2_SetTimeSource,

	.SetDataBuffer = TE_REG_ARIB2_SetDataBuffer,
	.GetDataWptr = TE_REG_ARIB2_GetDataWptr,
	.SetDataRptr = TE_REG_ARIB2_SetDataRptr,
	.SetMetaBuffer = TE_REG_ARIB2_SetMetaBuffer,
	.GetMetaWptr = TE_REG_ARIB2_GetMetaWptr,
	.SetMetaRptr = TE_REG_ARIB2_SetMetaRptr,
	.SetDataFullLevel = TE_REG_ARIB2_SetDataFullLevel,
	.SetDataUnitBufferSize = TE_REG_ARIB2_SetDataUnitBufferSize,
	.SetMetaFullLevel = TE_REG_ARIB2_SetMetaFullLevel,
	.SetMetaUnitBufferSize = TE_REG_ARIB2_SetMetaUnitBufferSize,
	.SetGmauAwUser = TE_REG_ARIB2_SetGmauAwUser,
};

static const struct legacy_hal_atsc3 legacy_atsc3 = {
	.SetDemodType = TE_REG_ATSC3_SetDemodType,
	.SetDecoderLayer = TE_REG_ATSC3_SetDecoderLayer,
	.SetPLPFilter = TE_REG_ATSC3_SetPLPFilter,
	.GetTimeStamp = TE_REG_ATSC3_GetTimeStamp,
};

static const struct legacy_hal_arib2 legacy_arib2 = {
	.SetNTPConf = TE_REG_ARIB2_SetNTPConf,
	.SetNTPSrcAddress = TE_REG_ARIB2_SetNTPSrcAddress,
	.SetNTPDstAddress = TE_REG_ARIB2_SetNTPDstAddress,
	.SetUDPPortValue = TE_REG_ARIB2_SetUDPPortValue,
	.SetUDPPortMask = TE_REG_ARIB2_SetUDPPortMask,
	.GetNTPInfo = TE_REG_ARIB2_GetNTPInfo,
};

int te_reg_dumper_init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O18:
	case LX_CHIP_M19:
		TE_REG_ATSC3_Init();
		TE_REG_ARIB2_init();
		use_legacy = true;
		legacy_func = &legacy_func_atsc3;
		break;
	default: // O20 ~
		use_legacy = false;
		break;
	}

	engine_mode = ENGINE_MODE_ATSC3;

	return 0;
}

int te_reg_dumper_set_init_value(void)
{
	if (use_legacy) {
		/* only set ATSC3 in M16P3 */
		TE_REG_ATSC3_SetGmauAwUser(0xF);
	} else {
		te_reg_dumper_set_gmau_awuser(0xF);	// TODO: CHECK IT !
	}

	return 0;
}

int te_reg_dumper_set_engine(enum te_reg_engine_mode mode)
{
	unsigned long flag;
	int ret, ch;

	CHECK_PARAM(mode >= ENGINE_MODE_MAX, "invalid mode[%d]", mode);

	TRACE_ENTER("mode=%d", mode);

	if (use_legacy) {
		if (mode == ENGINE_MODE_CI20) {
			log_error("Not Supported environments!(CI20)");
			return -ENODEV;
		}

		spin_lock_irqsave(&dumper_reg_lock, flag);

		ret = TE_REG_SetEngineMode(mode);
		if (ret) {
			log_error("Err in TE_REG_SetEngineMode\n");
		} else {
			if (mode == ENGINE_MODE_ATSC3) {
				legacy_func = &legacy_func_atsc3;
			} else {
				legacy_func = &legacy_func_arib2;
			}
			engine_mode = mode;
		}
		spin_unlock_irqrestore(&dumper_reg_lock, flag);

		return 0;
	}

	spin_lock_irqsave(&dumper_reg_lock, flag);

	for (ch = 0; ch < NUM_DUMPER_CHANNEL; ch++) {
		if (mode == ENGINE_MODE_ATSC3) {
			/* ENGINE:ATSC3 */
			DUMPER_RdFL(ch_conf[ch].time_latch_conf);
			DUMPER_Wr01(ch_conf[ch].time_latch_conf, engine_sel, 0);
			DUMPER_WrFL(ch_conf[ch].time_latch_conf);
		} else if (mode == ENGINE_MODE_ARIB2) {
			/* ENGINE:ARIB2 */
			DUMPER_RdFL(ch_conf[ch].time_latch_conf);
			DUMPER_Wr01(ch_conf[ch].time_latch_conf, engine_sel, 1);
			DUMPER_WrFL(ch_conf[ch].time_latch_conf);

			/* layer: BYPASS */
			DUMPER_RdFL(ch_conf[ch].a3_conf);
			DUMPER_Wr01(ch_conf[ch].a3_conf, layer_sel, 0);
			DUMPER_WrFL(ch_conf[ch].a3_conf);
		} else if (mode == ENGINE_MODE_CI20) {
			/* ENGINE:ARIB2 (not use), TIME_LATCH: disable */
			DUMPER_RdFL(ch_conf[ch].time_latch_conf);
			DUMPER_Wr01(ch_conf[ch].time_latch_conf, engine_sel, 1);
			DUMPER_Wr01(ch_conf[ch].time_latch_conf,
				    time_latch_en, 0);
			DUMPER_WrFL(ch_conf[ch].time_latch_conf);

			/* layer: BYPASS, plp: disable */
			DUMPER_RdFL(ch_conf[ch].a3_conf);
			DUMPER_Wr01(ch_conf[ch].a3_conf, layer_sel, 0);
			DUMPER_WrFL(ch_conf[ch].a3_conf);

			/* dumper mode: RAW */
			DUMPER_RdFL(ch_conf[ch].wmif_conf);
			DUMPER_Wr01(ch_conf[ch].wmif_conf, mode, 1);
			DUMPER_WrFL(ch_conf[ch].wmif_conf);
		}
	}

	engine_mode = mode;

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_get_engine(enum te_reg_engine_mode *mode)
{
	if (use_legacy) {
		TE_REG_GetEngineMode(mode);
	} else {
		*mode = engine_mode;
	}

	TRACE_EXIT("*mode=%d", *mode);

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

static u32 get_intr_regbits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 get_intr_val(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

int te_reg_dumper_set_intr_enable(u32 val, bool en)
{
	u32 v, bits;
	unsigned long flag;

	LEGACY_FUNC(SetIntrEnable, val, en);

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	if (!val)
		return 0;

	bits = get_intr_regbits(val);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(intr_cpu_en);
	DUMPER_Rd(intr_cpu_en, v);

	if (en)
		v |= bits;
	else
		v &= ~bits;

	DUMPER_Wr(intr_cpu_en, v);
	DUMPER_WrFL(intr_cpu_en);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_get_intr_status(u32 *val)
{
	u32 bits;
	unsigned long flag;

	LEGACY_FUNC(GetIntrStatus, val);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(intr_cpu_st);
	DUMPER_Rd(intr_cpu_st, bits);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	*val = get_intr_val(bits);

	return 0;
}

int te_reg_dumper_clear_intr(u32 val)
{
	u32 bits;
	unsigned long flag;

	LEGACY_FUNC(ClearIntr, val);

	TRACE_ENTER("val=0x%x", val);

	bits = get_intr_regbits(val);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(intr_cpu_clr, bits);
	DUMPER_WrFL(intr_cpu_clr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_latch_enable(u8 ch, bool en)
{
	unsigned long flag;

	LEGACY_FUNC(SetLatchEnable, ch, en);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=%d", ch, en);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].time_latch_conf);
	DUMPER_Wr01(ch_conf[ch].time_latch_conf, time_latch_en, en ? 1 : 0);
	DUMPER_WrFL(ch_conf[ch].time_latch_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_data_buf(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	LEGACY_FUNC(SetDataBuffer, ch, sptr, eptr);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,sptr=%08x,eptr=%08x", ch, sptr, eptr);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].dbuf_sptr, sptr);
	DUMPER_Wr(ch_conf[ch].dbuf_eptr, eptr);
	DUMPER_WrFL(ch_conf[ch].dbuf_sptr);
	DUMPER_WrFL(ch_conf[ch].dbuf_eptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_get_data_wptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	LEGACY_FUNC(GetDataWptr, ch, wptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].dbuf_wptr);
	DUMPER_Rd(ch_conf[ch].dbuf_wptr, *wptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	TRACE_VERBOSE_EXIT("ch=%d,*wptr=%08x", ch, *wptr);

	return 0;
}

int te_reg_dumper_set_data_rptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	LEGACY_FUNC(SetDataRptr, ch, rptr);
	CHECK_CHANNEL(ch);

	TRACE_VERBOSE_ENTER("ch=%d,rptr=%08x", ch, rptr);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].dbuf_rptr, rptr);
	DUMPER_WrFL(ch_conf[ch].dbuf_rptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_meta_buf(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	LEGACY_FUNC(SetMetaBuffer, ch, sptr, eptr);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,sptr=%08x,eptr=%08x", ch, sptr, eptr);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].mbuf_sptr, sptr);
	DUMPER_Wr(ch_conf[ch].mbuf_eptr, eptr);
	DUMPER_WrFL(ch_conf[ch].mbuf_sptr);
	DUMPER_WrFL(ch_conf[ch].mbuf_eptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_get_meta_wptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	LEGACY_FUNC(GetMetaWptr, ch, wptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].mbuf_wptr);
	DUMPER_Rd(ch_conf[ch].mbuf_wptr, *wptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	TRACE_VERBOSE_EXIT("ch=%d,*wptr=%08x", ch, *wptr);

	return 0;
}

int te_reg_dumper_set_meta_rptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	LEGACY_FUNC(SetMetaRptr, ch, rptr);
	CHECK_CHANNEL(ch);

	TRACE_VERBOSE_ENTER("ch=%d,rptr=%08x", ch, rptr);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].mbuf_wptr, rptr);
	DUMPER_WrFL(ch_conf[ch].mbuf_wptr);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_data_almostfull_level(u8 ch, u32 level)
{
	unsigned long flag;

	LEGACY_FUNC(SetDataFullLevel, ch, level);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,level=0x%08x", ch, level);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].dbuf_flevel, level);
	DUMPER_WrFL(ch_conf[ch].dbuf_flevel);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_data_unitbuf_size(u8 ch, u32 size)
{
	unsigned long flag;

	LEGACY_FUNC(SetDataUnitBufferSize, ch, size);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=0x%08x", ch, size);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].dbuf_usize, size);
	DUMPER_WrFL(ch_conf[ch].dbuf_usize);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_meta_almostfull_level(u8 ch, u32 level)
{
	unsigned long flag;

	LEGACY_FUNC(SetMetaFullLevel, ch, level);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,level=0x%08x", ch, level);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].mbuf_flevel, level);
	DUMPER_WrFL(ch_conf[ch].mbuf_flevel);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_meta_unitbuf_size(u8 ch, u32 size)
{
	unsigned long flag;

	LEGACY_FUNC(SetMetaUnitBufferSize, ch, size);
	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,size=0x%08x", ch, size);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].mbuf_usize, size);
	DUMPER_WrFL(ch_conf[ch].mbuf_usize);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_channel_mode(u8 ch, enum te_reg_dumper_mode mode)
{
	unsigned long flag;
	u32 v;

	LEGACY_FUNC(SetChannelMode, ch, mode);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,mode=%d", ch, mode);

	switch (mode) {
	case DUMPER_MODE_TLV:
		v = 0;
		break;
	case DUMPER_MODE_RAW:
		v = 1;
		break;
	case DUMPER_MODE_PVR:
		v = 2;
		break;
	case DUMPER_MODE_LGC:
		v = 3;
		break;
	default:
		log_error("invalid mode(%d)\n", mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].wmif_conf);
	DUMPER_Wr01(ch_conf[ch].wmif_conf, mode, v);
	DUMPER_WrFL(ch_conf[ch].wmif_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_channel_enable(u8 ch, bool en)
{
	u32 v;
	long timeout = 1000;	/* 1000us */

	LEGACY_FUNC(SetChannelEnable, ch, en);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=%d", ch, en);

	/* Wmif Enable Sequence to syncrhonize a packet
	 * 1. disable wmif
	 * 2. reset wmif
	 * 3. reset a3 proc
	 * 4. enable wmif
	 */
	DUMPER_RdFL(ch_conf[ch].wmif_conf);
	DUMPER_Wr01(ch_conf[ch].wmif_conf, enable, 0);
	DUMPER_Wr01(ch_conf[ch].wmif_conf, swreset, 1);
	DUMPER_WrFL(ch_conf[ch].wmif_conf);

	/* wait for the wmif reset ack */
	while (1) {
		DUMPER_RdFL(ch_conf[ch].wmif_conf);
		DUMPER_Rd01(ch_conf[ch].wmif_conf, swreset, v);
		if (!v)
			break;

		if (timeout <= 0) {
			log_error("ch[%d] - wmif reset timeout\n", ch);
			break;
		}
		udelay(10);
		timeout -= 10;
	}

	DUMPER_RdFL(ch_conf[ch].a3_conf);
	DUMPER_Wr01(ch_conf[ch].a3_conf, swreset, 1);
	DUMPER_WrFL(ch_conf[ch].a3_conf);

	if (en) {
		DUMPER_RdFL(ch_conf[ch].wmif_conf);
		DUMPER_Wr01(ch_conf[ch].wmif_conf, enable, 1);
		DUMPER_WrFL(ch_conf[ch].wmif_conf);
	}

	return 0;
}

int te_reg_dumper_get_channel_status(u8 ch, struct te_reg_dumper_status *s)
{
	u32 v;

	if (use_legacy)
		return -ENODEV;

	CHECK_CHANNEL(ch);

	DUMPER_RdFL(ch_conf[ch].wmif_conf);
	DUMPER_Rd01(ch_conf[ch].wmif_conf, enable, v);
	s->enable = v ? true : false;

	DUMPER_Rd01(ch_conf[ch].wmif_conf, mode, v);
	switch (v) {
	case 0:
		s->mode = DUMPER_MODE_TLV;
		break;
	case 1:
		s->mode = DUMPER_MODE_RAW;
		break;
	case 2:
		s->mode = DUMPER_MODE_PVR;
		break;
	case 3:
		s->mode = DUMPER_MODE_LGC;
		break;
	default:
		s->mode = DUMPER_MODE_DISABLE;
		break;
	}

	return 0;
}

int te_reg_dumper_set_time_src(u8 ch, u8 src)
{
	LEGACY_FUNC(SetTimeSource, ch, src);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	return TE_REG_SetGstccLatchSource(ch, src);
}

int te_reg_dumper_set_gmau_awuser(u8 val)
{
	unsigned long flag;

	LEGACY_FUNC(SetGmauAwUser, val);

	TRACE_ENTER("val=%d", val);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(gmau_conf);
	DUMPER_Wr01(gmau_conf, aw_user, val);
	DUMPER_WrFL(gmau_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_dumper_set_packet_monitor(u8 ch, struct te_reg_dumper_pkt_mon *conf)
{
	u32 val;

	CHECK_CHANNEL(ch);

	if (use_legacy)
		return -ENODEV;

	DUMPER_RdFL(ch_conf[ch].packet_cnt_conf);
	DUMPER_Wr01(ch_conf[ch].packet_cnt_conf, cnt_reset, 1);
	DUMPER_WrFL(ch_conf[ch].packet_cnt_conf);

	val = conf->enable ? 0 : 1;
	DUMPER_Wr01(ch_conf[ch].packet_cnt_conf, cnt_reset, val);
	val = conf->sop_mode ? 1 : 0;
	DUMPER_Wr01(ch_conf[ch].packet_cnt_conf, cnt_mode, val);
	DUMPER_Wr01(ch_conf[ch].packet_cnt_conf, unit_byte, conf->unit_byte);
	DUMPER_WrFL(ch_conf[ch].packet_cnt_conf);

	return 0;
}

int te_reg_dumper_get_packet_count(u8 ch, u32 *val)
{
	CHECK_CHANNEL(ch);

	if (use_legacy)
		return -ENODEV;

	DUMPER_RdFL(ch_conf[ch].packet_cnt);
	DUMPER_Rd(ch_conf[ch].packet_cnt, *val);

	return 0;
}

/*****************************
 * ATSC 3.0 Specific Functions
 *****************************/
static int get_demod_rev_idx(u32 type)
{
	int idx;

	switch (type) {
	case ATSC3_DEMOD_TYPE_B:
		idx = 0;
		break;
	case ATSC3_DEMOD_TYPE_C:
		idx = 1;
		break;
	default:
		idx = -1;
		break;
	}
	return idx;
}

int te_reg_atsc3_set_demod_type(u8 ch, enum te_reg_atsc3_demod_type type)
{
	unsigned long flag;
	int idx;

	LEGACY_HAL_ATSC3(SetDemodType, ch, type);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,type=%d", ch, type);

	idx = get_demod_rev_idx(type);
	CHECK_PARAM(idx < 0, "invalid demod type(%d)", type);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].a3_conf);
	DUMPER_Wr01(ch_conf[ch].a3_conf, lgc_vers, idx);
	DUMPER_Wr01(ch_conf[ch].a3_conf, swreset, 1);
	DUMPER_WrFL(ch_conf[ch].a3_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

static int get_decoder_layer_idx(u8 layer)
{
	int idx;

	switch (layer) {
	case ATSC3_DECODER_LAYER_BYPASS:
		idx = 0;
		break;
	case ATSC3_DECODER_LAYER_LGC:
	case ATSC3_DECODER_LAYER_TIME_LGC:
		idx = 1;
		break;
	case ATSC3_DECODER_LAYER_BB:
		idx = 2;
		break;
	case ATSC3_DECODER_LAYER_BB_PLP:
		idx = 3;
		break;
	default:
		idx = -1;
		break;
	}

	return idx;
}

int te_reg_atsc3_set_decoder_layer(u8 ch, enum te_reg_atsc3_layer layer)
{
	unsigned long flag;
	int idx;

	LEGACY_HAL_ATSC3(SetDecoderLayer, ch, layer);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,layer=%d", ch, layer);

	idx = get_decoder_layer_idx(layer);
	CHECK_PARAM(idx < 0, "invalid layer(%d)", layer);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].a3_conf);
	DUMPER_Wr01(ch_conf[ch].a3_conf, layer_sel, idx);
	DUMPER_WrFL(ch_conf[ch].a3_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_atsc3_set_plp_filter(u8 ch, bool en, u8 id)
{
	unsigned long flag;

	LEGACY_HAL_ATSC3(SetPLPFilter, ch, en, id);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=%d,id=%d", ch, en, id);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].a3_conf);
	DUMPER_Wr01(ch_conf[ch].a3_conf, plp_flt_en, en ? 1 : 0);
	DUMPER_Wr01(ch_conf[ch].a3_conf, ref_plp_id, id);
	DUMPER_WrFL(ch_conf[ch].a3_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_atsc3_get_timestamp(u8 ch, struct te_reg_atsc3_timestamp *ts)
{
	unsigned long flag;
	u32 v;

	LEGACY_HAL_ATSC3(GetTimeStamp, ch, ts);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].tmode);
	DUMPER_RdFL(ch_conf[ch].tdata_sec);
	DUMPER_RdFL(ch_conf[ch].tdata_fsec);

	DUMPER_Rd01(ch_conf[ch].tmode, timestamp_mode, v);
	switch (v) {
	case 1:
		ts->mode = ATSC3_TIMESTAMP_SEC_MSEC;
		break;
	case 2:
		ts->mode = ATSC3_TIMESTAMP_SEC_MSEC_USEC;
		break;
	case 3:
		ts->mode = ATSC3_TIMESTAMP_SEC_MSEC_USEC_NSEC;
		break;
	default:
		ts->mode = ATSC3_TIMESTAMP_NONE;
		break;
	}

	DUMPER_Rd(ch_conf[ch].tdata_sec, ts->sec);
	DUMPER_Rd01(ch_conf[ch].tdata_fsec, msec, ts->msec);
	DUMPER_Rd01(ch_conf[ch].tdata_fsec, usec, ts->usec);
	DUMPER_Rd01(ch_conf[ch].tdata_fsec, nsec, ts->nsec);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

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

	TRACE_VERBOSE_EXIT("ch=%d,mode=%d,sec=%d,msec=%d,usec=%d,nsec=%d",
			    ch, ts->mode, ts->sec, ts->msec,
			    ts->usec, ts->nsec);

	return 0;
}




/*****************************
 * ARIB2.0 Specific Functions
 *****************************/
int te_reg_arib2_set_ntp_conf(u8 ch, bool len_check, bool swreset)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(SetNTPConf, ch, len_check, swreset);

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d,len_check=%d,swreset=%d", ch, len_check, swreset);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].ntp_conf);
	DUMPER_Wr01(ch_conf[ch].ntp_conf, swreset, (swreset) ? 1 : 0);
	DUMPER_Wr01(ch_conf[ch].ntp_conf, len_check,
		    (len_check) ? 1 : 0);
	DUMPER_WrFL(ch_conf[ch].ntp_conf);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_arib2_set_ntp_src_addr(u8 ch, u32 *val, u32 *mask)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(SetNTPSrcAddress, ch, val, mask);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].ip_src_v_31_0, val[3]);
	DUMPER_Wr(ch_conf[ch].ip_src_v_63_32, val[2]);
	DUMPER_Wr(ch_conf[ch].ip_src_v_95_64, val[1]);
	DUMPER_Wr(ch_conf[ch].ip_src_v_127_96, val[0]);

	DUMPER_WrFL(ch_conf[ch].ip_src_v_31_0);
	DUMPER_WrFL(ch_conf[ch].ip_src_v_63_32);
	DUMPER_WrFL(ch_conf[ch].ip_src_v_95_64);
	DUMPER_WrFL(ch_conf[ch].ip_src_v_127_96);

	DUMPER_Wr(ch_conf[ch].ip_src_m_31_0, mask[3]);
	DUMPER_Wr(ch_conf[ch].ip_src_m_63_32, mask[2]);
	DUMPER_Wr(ch_conf[ch].ip_src_m_95_64, mask[1]);
	DUMPER_Wr(ch_conf[ch].ip_src_m_127_96, mask[0]);

	DUMPER_WrFL(ch_conf[ch].ip_src_m_31_0);
	DUMPER_WrFL(ch_conf[ch].ip_src_m_63_32);
	DUMPER_WrFL(ch_conf[ch].ip_src_m_95_64);
	DUMPER_WrFL(ch_conf[ch].ip_src_m_127_96);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_arib2_set_ntp_dst_addr(u8 ch, u32 *val, u32 *mask)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(SetNTPDstAddress, ch, val, mask);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_Wr(ch_conf[ch].ip_dst_v_31_0, val[3]);
	DUMPER_Wr(ch_conf[ch].ip_dst_v_63_32, val[2]);
	DUMPER_Wr(ch_conf[ch].ip_dst_v_95_64, val[1]);
	DUMPER_Wr(ch_conf[ch].ip_dst_v_127_96, val[0]);

	DUMPER_WrFL(ch_conf[ch].ip_dst_v_31_0);
	DUMPER_WrFL(ch_conf[ch].ip_dst_v_63_32);
	DUMPER_WrFL(ch_conf[ch].ip_dst_v_95_64);
	DUMPER_WrFL(ch_conf[ch].ip_dst_v_127_96);

	DUMPER_Wr(ch_conf[ch].ip_dst_m_31_0, mask[3]);
	DUMPER_Wr(ch_conf[ch].ip_dst_m_63_32, mask[2]);
	DUMPER_Wr(ch_conf[ch].ip_dst_m_95_64, mask[1]);
	DUMPER_Wr(ch_conf[ch].ip_dst_m_127_96, mask[0]);

	DUMPER_WrFL(ch_conf[ch].ip_dst_m_31_0);
	DUMPER_WrFL(ch_conf[ch].ip_dst_m_63_32);
	DUMPER_WrFL(ch_conf[ch].ip_dst_m_95_64);
	DUMPER_WrFL(ch_conf[ch].ip_dst_m_127_96);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_arib2_set_udp_port_val(u8 ch, u32 src, u32 dst)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(SetUDPPortValue, ch, src, dst);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].udp_port_v);
	DUMPER_Wr01(ch_conf[ch].udp_port_v, src, src);
	DUMPER_Wr01(ch_conf[ch].udp_port_v, dst, dst);
	DUMPER_WrFL(ch_conf[ch].udp_port_v);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_arib2_set_udp_port_mask(u8 ch, u32 src, u32 dst)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(SetUDPPortMask, ch, src, dst);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].udp_port_m);
	DUMPER_Wr01(ch_conf[ch].udp_port_m, src, src);
	DUMPER_Wr01(ch_conf[ch].udp_port_m, dst, dst);
	DUMPER_WrFL(ch_conf[ch].udp_port_m);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

int te_reg_arib2_get_ntp_info(u8 ch, struct te_reg_arib2_ntp_info *info)
{
	unsigned long flag;

	LEGACY_HAL_ARIB2(GetNTPInfo, ch, info);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&dumper_reg_lock, flag);

	DUMPER_RdFL(ch_conf[ch].ntp_info);
	DUMPER_Rd01(ch_conf[ch].ntp_info, ntp_li, info->leap_indicator);
	DUMPER_Rd01(ch_conf[ch].ntp_info, ntp_vers, info->version);
	DUMPER_Rd01(ch_conf[ch].ntp_info, ntp_mode, info->mode);
	DUMPER_Rd01(ch_conf[ch].ntp_info, ntp_poll, info->poll);
	DUMPER_Rd01(ch_conf[ch].ntp_info, ntp_precision,
		    info->precision);

	DUMPER_RdFL(ch_conf[ch].ntp_time_63_32);
	DUMPER_Rd(ch_conf[ch].ntp_time_63_32, info->sec);

	DUMPER_RdFL(ch_conf[ch].ntp_time_31_0);
	DUMPER_Rd(ch_conf[ch].ntp_time_31_0, info->fraction);

	spin_unlock_irqrestore(&dumper_reg_lock, flag);

	return 0;
}

/* string functions */
static const struct te_val_str dumper_mode_str[] = {
	{DUMPER_MODE_TLV, "TLV"},
	{DUMPER_MODE_RAW, "RAW"},
	{DUMPER_MODE_PVR, "PVR"},
	{DUMPER_MODE_LGC, "LGC"},
	{DUMPER_MODE_DISABLE, "DISABLE"},
};

const char *te_reg_dumper_mode_to_str(enum te_reg_dumper_mode mode)
{
	return find_match_string(dumper_mode_str, mode, "Invalid");
}

static const struct te_val_str atsc3_layer_str[] = {
	{ATSC3_DECODER_LAYER_BYPASS, "BYPASS"},
	{ATSC3_DECODER_LAYER_LGC, "LGC"},
	{ATSC3_DECODER_LAYER_BB, "BB"},
	{ATSC3_DECODER_LAYER_TIME_LGC, "TIME_LGC"},
};

const char *te_reg_atsc3_layer_to_str(enum te_reg_atsc3_layer layer)
{
	return find_match_string(atsc3_layer_str, layer, "Invalid");
}
