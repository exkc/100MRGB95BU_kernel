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

#include <lg1k/te/reg.h>

#include "te_impl.h"
#include "te_reg_ctrl.h"
#include "te_reg_dumper.h"

#define CHECK_CHANNEL(ch)	\
  CHECK_PARAM((ch) > 3, "invalid channel(%d)\n", ch)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_ARIB2_MASK)) {		\
		log_noti("@ARIB2_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_ARIB2_MASK)) {		\
		log_noti("~ARIB2_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_ARIB2_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@ARIB2_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_ARIB2_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~ARIB2_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
}

#define HAL_FUNC(func, ...)					\
do {								\
	if (hal) {						\
		if(hal->func)				 	\
			return hal->func(__VA_ARGS__);		\
		return -EPERM;					\
	}							\
} while(0)

struct arib2_hal {
	int (*SetIntrEnable)(u32 val, bool en);
	int (*GetIntrStatus)(u32 *val);
	int (*ClearIntr)(u32 val);

	int (*SetChannelMode)(u8 ch, enum te_reg_dumper_mode mode);
	int (*SetChannelEnable)(u8 ch, bool en);
	int (*SetLatchEnable)(u8 ch, bool en);
	int (*SetNTPConf)(u8 ch, bool len_check, bool swreset);
	int (*SetNTPSrcAddress)(u8 ch, u32 *val, u32 *mask);
	int (*SetNTPDstAddress)(u8 ch, u32 *val, u32 *mask);
	int (*SetUDPPortValue)(u8 ch, u32 src, u32 dst);
	int (*SetUDPPortMask)(u8 ch, u32 src, u32 dst);

	int (*GetNTPInfo)(u8 ch, struct te_reg_arib2_ntp_info *info);
	int (*GetNTPTime)(u8 ch, u32 *sec, u32 *fraction);

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
};

typedef struct {
	u8 version;
} ARIB2_REG_CFG_T;

static DEFINE_SPINLOCK(arib2_reg_lock);

static const ARIB2_REG_CFG_T *arib2_reg_cfg;

static const ARIB2_REG_CFG_T arib2_cfg_m16p3 = {
	.version = 1,
};

static const struct arib2_hal *hal;
static const struct arib2_hal dummy_hal;

int TE_REG_ARIB2_init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_M19:
		arib2_reg_cfg = &arib2_cfg_m16p3;
		break;
	default: // O18 ~
		hal = &dummy_hal;
		break;
	}

	return 0;
}

static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, DUMPER_INTR_META_WRITE_CH0},
	{0x1 << 1, DUMPER_INTR_META_WRITE_CH1},
	{0x1 << 2, DUMPER_INTR_META_WRITE_CH2},
	{0x1 << 3, DUMPER_INTR_META_UNIT_BUF_CH0},
	{0x1 << 4, DUMPER_INTR_META_UNIT_BUF_CH1},
	{0x1 << 5, DUMPER_INTR_META_UNIT_BUF_CH2},
	{0x1 << 6, DUMPER_INTR_META_AL_FULL_CH0},
	{0x1 << 7, DUMPER_INTR_META_AL_FULL_CH1},
	{0x1 << 8, DUMPER_INTR_META_AL_FULL_CH2},
	{0x1 << 9, DUMPER_INTR_DATA_UNIT_BUF_CH0},
	{0x1 << 10, DUMPER_INTR_DATA_UNIT_BUF_CH1},
	{0x1 << 11, DUMPER_INTR_DATA_UNIT_BUF_CH2},
	{0x1 << 12, DUMPER_INTR_DATA_AL_FULL_CH0},
	{0x1 << 13, DUMPER_INTR_DATA_AL_FULL_CH1},
	{0x1 << 14, DUMPER_INTR_DATA_AL_FULL_CH2},
	{0x1 << 15, DUMPER_INTR_TIMESTAMP_CH0},
	{0x1 << 16, DUMPER_INTR_TIMESTAMP_CH1},
	{0x1 << 17, DUMPER_INTR_TIMESTAMP_CH2},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

int TE_REG_ARIB2_SetIntrEnable(u32 val, bool en)
{
	u32 v, bits;
	unsigned long flag;

	HAL_FUNC(SetIntrEnable, val, en);
	TRACE_ENTER("val=0x%x,en=%d", val, en);

	if (!val)
		return 0;

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(intr_cpu_en);
	ARIB2_Rd(intr_cpu_en, v);

	if (en)
		v |= bits;
	else
		v &= ~bits;

	ARIB2_Wr(intr_cpu_en, v);
	ARIB2_WrFL(intr_cpu_en);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_GetIntrStatus(u32 *val)
{
	u32 bits;
	unsigned long flag;

	HAL_FUNC(GetIntrStatus, val);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(intr_cpu_st);
	ARIB2_Rd(intr_cpu_st, bits);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	*val = GetIntrValue(bits);

	return 0;
}

int TE_REG_ARIB2_ClearIntr(u32 val)
{
	u32 bits;
	unsigned long flag;

	HAL_FUNC(ClearIntr, val);
	TRACE_ENTER("val=0x%x", val);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(intr_cpu_clr, bits);
	ARIB2_WrFL(intr_cpu_clr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetLatchEnable(u8 ch, bool en)
{
	unsigned long flag;

	HAL_FUNC(SetLatchEnable, ch, en);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].ntp_conf);
	ARIB2_Wr01(arib_ch_conf[ch].ntp_conf, latch_en, en ? 1 : 0);
	ARIB2_WrFL(arib_ch_conf[ch].ntp_conf);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetNTPConf(u8 ch, bool len_check, bool swreset)
{
	unsigned long flag;

	HAL_FUNC(SetNTPConf, ch, len_check, swreset);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].ntp_conf);
	ARIB2_Wr01(arib_ch_conf[ch].ntp_conf, swreset, (swreset) ? 1 : 0);
	ARIB2_Wr01(arib_ch_conf[ch].ntp_conf, len_check, (len_check) ? 1 : 0);
	ARIB2_WrFL(arib_ch_conf[ch].ntp_conf);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetNTPSrcAddress(u8 ch, u32 *val, u32 *mask)
{
	unsigned long flag;

	HAL_FUNC(SetNTPSrcAddress, ch, val, mask);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].ip_src_v_31_0, val[3]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_v_63_32, val[2]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_v_95_64, val[1]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_v_127_96, val[0]);

	ARIB2_WrFL(arib_ch_conf[ch].ip_src_v_31_0);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_v_63_32);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_v_95_64);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_v_127_96);

	ARIB2_Wr(arib_ch_conf[ch].ip_src_m_31_0, mask[3]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_m_63_32, mask[2]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_m_95_64, mask[1]);
	ARIB2_Wr(arib_ch_conf[ch].ip_src_m_127_96, mask[0]);

	ARIB2_WrFL(arib_ch_conf[ch].ip_src_m_31_0);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_m_63_32);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_m_95_64);
	ARIB2_WrFL(arib_ch_conf[ch].ip_src_m_127_96);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetNTPDstAddress(u8 ch, u32 *val, u32 *mask)
{
	unsigned long flag;

	HAL_FUNC(SetNTPDstAddress, ch, val, mask);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].ip_dst_v_31_0, val[3]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_v_63_32, val[2]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_v_95_64, val[1]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_v_127_96, val[0]);

	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_v_31_0);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_v_63_32);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_v_95_64);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_v_127_96);

	ARIB2_Wr(arib_ch_conf[ch].ip_dst_m_31_0, mask[3]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_m_63_32, mask[2]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_m_95_64, mask[1]);
	ARIB2_Wr(arib_ch_conf[ch].ip_dst_m_127_96, mask[0]);

	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_m_31_0);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_m_63_32);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_m_95_64);
	ARIB2_WrFL(arib_ch_conf[ch].ip_dst_m_127_96);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetUDPPortValue(u8 ch, u32 src, u32 dst)
{
	unsigned long flag;

	HAL_FUNC(SetUDPPortValue, ch, src, dst);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].udp_port_v);
	ARIB2_Wr01(arib_ch_conf[ch].udp_port_v, src, src);
	ARIB2_Wr01(arib_ch_conf[ch].udp_port_v, dst, dst);
	ARIB2_WrFL(arib_ch_conf[ch].udp_port_v);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetUDPPortMask(u8 ch, u32 src, u32 dst)
{
	unsigned long flag;

	HAL_FUNC(SetUDPPortMask, ch, src, dst);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].udp_port_m);
	ARIB2_Wr01(arib_ch_conf[ch].udp_port_m, src, src);
	ARIB2_Wr01(arib_ch_conf[ch].udp_port_m, dst, dst);
	ARIB2_WrFL(arib_ch_conf[ch].udp_port_m);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_GetNTPInfo(u8 ch, struct te_reg_arib2_ntp_info *info)
{
	unsigned long flag;

	HAL_FUNC(GetNTPInfo, ch, info);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].ntp_info);
	ARIB2_Rd01(arib_ch_conf[ch].ntp_info, ntp_li, info->leap_indicator);
	ARIB2_Rd01(arib_ch_conf[ch].ntp_info, ntp_vers, info->version);
	ARIB2_Rd01(arib_ch_conf[ch].ntp_info, ntp_mode, info->mode);
	ARIB2_Rd01(arib_ch_conf[ch].ntp_info, ntp_poll, info->poll);
	ARIB2_Rd01(arib_ch_conf[ch].ntp_info, ntp_precision, info->precision);

	ARIB2_RdFL(arib_ch_conf[ch].ntp_time_63_32);
	ARIB2_Rd(arib_ch_conf[ch].ntp_time_63_32, info->sec);

	ARIB2_RdFL(arib_ch_conf[ch].ntp_time_31_0);
	ARIB2_Rd(arib_ch_conf[ch].ntp_time_31_0, info->fraction);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetChannelMode(u8 ch, enum te_reg_dumper_mode mode)
{
	unsigned long flag;
	u32 v;

	HAL_FUNC(SetChannelMode, ch, mode);

	CHECK_CHANNEL(ch);

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
	case DUMPER_MODE_DISABLE:
		v = 3;
		break;
	default:
		log_error("invalid mode(%d)\n", mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].wmif_conf);
	ARIB2_Wr01(arib_ch_conf[ch].wmif_conf, mode, v);
	ARIB2_WrFL(arib_ch_conf[ch].wmif_conf);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetChannelEnable(u8 ch, bool en)
{
	unsigned long flag;

	HAL_FUNC(SetChannelEnable, ch, en);

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].wmif_conf);
	if (en)
		ARIB2_Wr01(arib_ch_conf[ch].wmif_conf, swreset, 1);
	ARIB2_Wr01(arib_ch_conf[ch].wmif_conf, enable, en ? 1 : 0);
	ARIB2_WrFL(arib_ch_conf[ch].wmif_conf);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetDataBuffer(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	HAL_FUNC(SetDataBuffer, ch, sptr, eptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].dbuf_sptr, sptr);
	ARIB2_Wr(arib_ch_conf[ch].dbuf_eptr, eptr);
	ARIB2_WrFL(arib_ch_conf[ch].dbuf_sptr);
	ARIB2_WrFL(arib_ch_conf[ch].dbuf_eptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_GetDataWptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	HAL_FUNC(GetDataWptr, ch, wptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].dbuf_wptr);
	ARIB2_Rd(arib_ch_conf[ch].dbuf_wptr, *wptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetDataRptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	HAL_FUNC(SetDataRptr, ch, rptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].dbuf_rptr, rptr);
	ARIB2_WrFL(arib_ch_conf[ch].dbuf_rptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetMetaBuffer(u8 ch, u32 sptr, u32 eptr)
{
	unsigned long flag;

	HAL_FUNC(SetMetaBuffer, ch, sptr, eptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].mbuf_sptr, sptr);
	ARIB2_Wr(arib_ch_conf[ch].mbuf_eptr, eptr);
	ARIB2_WrFL(arib_ch_conf[ch].mbuf_sptr);
	ARIB2_WrFL(arib_ch_conf[ch].mbuf_eptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_GetMetaWptr(u8 ch, u32 *wptr)
{
	unsigned long flag;

	HAL_FUNC(GetMetaWptr, ch, wptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(arib_ch_conf[ch].mbuf_wptr);
	ARIB2_Rd(arib_ch_conf[ch].mbuf_wptr, *wptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetMetaRptr(u8 ch, u32 rptr)
{
	unsigned long flag;

	HAL_FUNC(SetMetaRptr, ch, rptr);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].mbuf_wptr, rptr);
	ARIB2_WrFL(arib_ch_conf[ch].mbuf_wptr);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetDataFullLevel(u8 ch, u32 level)
{
	unsigned long flag;

	HAL_FUNC(SetDataFullLevel, ch, level);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].dbuf_flevel, level);
	ARIB2_WrFL(arib_ch_conf[ch].dbuf_flevel);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetDataUnitBufferSize(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(SetDataUnitBufferSize, ch, size);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].dbuf_usize, size);
	ARIB2_WrFL(arib_ch_conf[ch].dbuf_usize);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetMetaFullLevel(u8 ch, u32 level)
{
	unsigned long flag;

	HAL_FUNC(SetMetaFullLevel, ch, level);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].mbuf_flevel, level);
	ARIB2_WrFL(arib_ch_conf[ch].mbuf_flevel);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetMetaUnitBufferSize(u8 ch, u32 size)
{
	unsigned long flag;

	HAL_FUNC(SetMetaUnitBufferSize, ch, size);
	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_Wr(arib_ch_conf[ch].mbuf_usize, size);
	ARIB2_WrFL(arib_ch_conf[ch].mbuf_usize);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetGmauAwUser(u8 val)
{
	unsigned long flag;

	HAL_FUNC(SetGmauAwUser, val);

	TRACE_ENTER("val=%d", val);

	spin_lock_irqsave(&arib2_reg_lock, flag);

	ARIB2_RdFL(gmau_conf);
	ARIB2_Wr01(gmau_conf, aw_user, val);
	ARIB2_WrFL(gmau_conf);

	spin_unlock_irqrestore(&arib2_reg_lock, flag);

	return 0;
}

int TE_REG_ARIB2_SetTimeSource(u8 ch, u8 idx)
{
	return TE_REG_SetGstccLatchSource(ch, idx);
}
