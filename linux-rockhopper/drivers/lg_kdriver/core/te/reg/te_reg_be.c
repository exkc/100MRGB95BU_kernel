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
	CHECK_ERROR(idx >= 2, return -EINVAL, "invalid idx(%d)\n", idx)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_BE_MASK)) {		\
		log_noti("@BE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_BE_MASK)) {		\
		log_noti("~BE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_BE_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@BE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_BE_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~BE_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

typedef struct {
	u8 version;
} BE_CFG_T;

static DEFINE_SPINLOCK(be_reg_lock);

/* +security enhanced, download mode */
static const BE_CFG_T be_cfg_normal = {
	.version = 2,
};

/* +FE_PIDF enable */
static const BE_CFG_T stcc_cfg_y21 = {
	.version = 1,
};

static const BE_CFG_T stcc_cfg_y18 = {
	.version = 0,
};

static const BE_CFG_T *be_reg_cfg;

int TE_REG_BE_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O18:
		be_reg_cfg = &stcc_cfg_y18;
		break;
	case LX_CHIP_O20:
	case LX_CHIP_M19:
	case LX_CHIP_E60:
		be_reg_cfg = &stcc_cfg_y21;
		break;
	case LX_CHIP_O22:
	default:
		be_reg_cfg = &be_cfg_normal;
		break;
	}
	return 0;
}

static int GetAxiEndianIdx(enum te_reg_endian type)
{
	int idx;

	switch (type) {
	case BE_AXI_BIG_ENDIAN:
		idx = 0;
		break;
	case BE_AXI_LITTLE_ENDIAN:
		idx = 1;
		break;
	default:
		idx = -1;
		break;
	}

	return idx;
}

int TE_REG_SetBeAxiEndian(enum te_reg_endian wr, enum te_reg_endian rd)
{
	int wr_type, rd_type;
	unsigned long flag;

	TRACE_ENTER("wr=%d,rd=%d", wr, rd);

	wr_type = GetAxiEndianIdx(wr);
	rd_type = GetAxiEndianIdx(rd);

	CHECK_PARAM(wr_type < 0, "invalid wr_endian(%d)", wr);
	CHECK_PARAM(rd_type < 0, "invalid rd_endian(%d)", rd);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_conf);
	BE_Wr01(be_conf, wmif_endian, wr_type);
	BE_Wr01(be_conf, rmif_endian, rd_type);
	BE_WrFL(be_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetDownloadTimeStampMode(enum te_reg_timestamp mode)
{
	TRACE_ENTER("mode=%d", mode);

	CHECK_PARAM(mode != TIMESTAMP_MODE_32BITS, "not supported mode(%d)",
		    mode);

	return 0;
}

int TE_REG_SetHwPieEnable(bool en)
{
	unsigned long flag;

	TRACE_ENTER("en=%d", en);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_conf);
	BE_Wr01(be_conf, hw_pie_en, en);
	BE_WrFL(be_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetHwDownloadEnable(bool en)
{
	unsigned long flag;

	TRACE_ENTER("en=%d", en);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_conf);
	BE_Wr01(be_conf, hw_dn_en, en);
	BE_WrFL(be_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

// Check Hardware Download Enable
int TE_REG_GetHwDownloadEnable(bool *en)
{
	unsigned long flag;
	u32 v;

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_conf);
	BE_Rd01(be_conf, hw_dn_en, v);
	*en = v ? true : false;

	spin_unlock_irqrestore(&be_reg_lock, flag);

	TRACE_EXIT("*en=%d", *en);

	return 0;
}

int TE_REG_SetDownloadBuffer(u8 idx, u32 start, u32 end)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,start=0x%08x,end=0x%08x", idx, start, end);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_Wr(be_tp_buff[idx].start_addr, start);
	BE_Wr(be_tp_buff[idx].end_addr, end);

	BE_WrFL(be_tp_buff[idx].start_addr);
	BE_WrFL(be_tp_buff[idx].end_addr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_GetDownloadWptr(u8 idx, u32 *wptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_tp_buff[idx].wptr);
	BE_Rd(be_tp_buff[idx].wptr, *wptr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	TRACE_VERBOSE_EXIT("idx=%d,*wptr=0x%08x", idx, *wptr);

	return 0;
}

int TE_REG_SetDownloadRptr(u8 idx, u32 rptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_VERBOSE_ENTER("idx=%d,rpt=0x%08x", idx, rptr);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_Wr(be_tp_buff[idx].rptr, rptr);
	BE_WrFL(be_tp_buff[idx].rptr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetDownloadSegmentSize(u8 idx, u32 size)
{
	unsigned long flag;

	TRACE_ENTER("size=%d", size);

	spin_lock_irqsave(&be_reg_lock, flag);

	size >>= 10;		/* 1KB unit */
	BE_RdFL(be_dn_buf_seg_size);
	if (idx == 0) {
		BE_Wr01(be_dn_buf_seg_size, dn0_buf_segment_size, (u16)size);
	} else {
		BE_Wr01(be_dn_buf_seg_size, dn1_buf_segment_size, (u16)size);
	}
	BE_WrFL(be_dn_buf_seg_size);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetPieBuffer(u8 idx, u32 start, u32 end)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,start=0x%08x,end=0x%08x", idx, start, end);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_Wr(be_pie_buff[idx].start_addr, start);
	BE_Wr(be_pie_buff[idx].end_addr, end);

	BE_WrFL(be_pie_buff[idx].start_addr);
	BE_WrFL(be_pie_buff[idx].end_addr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_GetPieWptr(u8 idx, u32 *wptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_pie_buff[idx].wptr);
	BE_Rd(be_pie_buff[idx].wptr, *wptr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	TRACE_VERBOSE_EXIT("idx=%d,*wptr=0x%08x", idx, *wptr);

	return 0;
}

int TE_REG_SetPieRptr(u8 idx, u32 rptr)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_VERBOSE_ENTER("idx=%d,rpt=0x%08x", idx, rptr);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_Wr(be_pie_buff[idx].rptr, rptr);
	BE_WrFL(be_pie_buff[idx].rptr);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetPieDetect(u8 idx, u8 num, u32 mask, u32 val, bool en)
{
	u32 v;
	unsigned long flag;

	CHECK_IDX(idx);
	CHECK_PARAM(num >= 4, "invalid num(%d)", num);

	TRACE_ENTER("idx=%d,num=%d,mask=0x%x,val=0x%x,en=%d",
		    idx, num, mask, val, en);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_pie_conf);
	if (idx == 0)
		BE_Rd01(be_pie_conf, dn0_pie_mask_en, v);
	else
		BE_Rd01(be_pie_conf, dn1_pie_mask_en, v);

	if (en) {
		BE_Wr(be_pie_det[idx].value[num], val);
		BE_Wr(be_pie_det[idx].mask[num], mask);

		BE_WrFL(be_pie_det[idx].value[num]);
		BE_WrFL(be_pie_det[idx].mask[num]);

		v |= (0x1 << num);
	} else {
		v &= ~(0x1 << num);
	}

	if (idx == 0)
		BE_Wr01(be_pie_conf, dn0_pie_mask_en, v);
	else
		BE_Wr01(be_pie_conf, dn1_pie_mask_en, v);
	BE_WrFL(be_pie_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_DisablePieDetect(u8 idx)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d", idx);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_pie_conf);
	if (idx == 0) {
		BE_Wr01(be_pie_conf, dn0_pie_mask_en, 0);
	} else {
		BE_Wr01(be_pie_conf, dn1_pie_mask_en, 0);
	}
	BE_WrFL(be_pie_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetPiePid(u8 idx, u16 pid)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,pid=0x%04x", idx, pid);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_pie_pid_conf);
	if (idx == 0) {
		BE_Wr01(be_pie_pid_conf, dn0_pie_pid_filter, pid);
	} else {
		BE_Wr01(be_pie_pid_conf, dn1_pie_pid_filter, pid);
	}
	BE_WrFL(be_pie_pid_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_SetDownloadMode(u8 idx, enum te_reg_download_mode mode)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,mode=%d", idx, mode);

	if (be_reg_cfg->version < 2) {
		if (mode != DOWNLOAD_MODE_192BYTE)
			return -EPERM;
		return 0;
	}

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(download_mode);
	if (idx == 0) {
		BE_Wr01(download_mode, download_mode_dn0, mode);
	} else {
		BE_Wr01(download_mode, download_mode_dn1, mode);
	}
	BE_WrFL(download_mode);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}


static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, BE_INTR_SEGMENT_DN0},
	{0x1 << 1, BE_INTR_SEGMENT_DN1},
	{0x1 << 2, BE_INTR_BE_DONE},
	{0x1 << 3, BE_INTR_CLEAR_TSBUFFER},
	{0x1 << 4, BE_INTR_PIE_DETECT},
	{0x1 << 5, BE_INTR_CLEAR_TSBUFFER_FULL},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

/* be_ext_intr is different with M16A0, but it can be used since the function directly writes
 * register value (without access entries) */
int TE_REG_SetBeIntrEnable(u32 val, bool en)
{
	u32 v, bits;
	unsigned long flag;

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_ext_intr_en);
	BE_Rd(be_ext_intr_en, v);
	if (en)
		v |= bits;
	else
		v &= ~bits;
	BE_Wr(be_ext_intr_en, v);
	BE_WrFL(be_ext_intr_en);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

int TE_REG_GetBeIntrStatus(u32 *val)
{
	u32 bits;
	unsigned long flag;

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_ext_intr_st);
	BE_Rd(be_ext_intr_st, bits);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	*val = GetIntrValue(bits);

	return 0;
}

int TE_REG_ClearBeIntr(u32 val)
{
	u32 bits;
	unsigned long flag;

	TRACE_ENTER("val=0x%x", val);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_Wr(be_ext_intr_cl, bits);
	BE_WrFL(be_ext_intr_cl);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	return 0;
}

//Move from FE
int TE_REG_SetChannelDownloadEnable(u8 idx, u8 dn_src, bool en)
{
	unsigned long flag;

	CHECK_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d", idx, en);

	spin_lock_irqsave(&be_reg_lock, flag);

	BE_RdFL(be_pie_conf);
	if (idx == 0)
		BE_Wr01(be_pie_conf, dn0_dvr_en, en ? 1 : 0);
	else
		BE_Wr01(be_pie_conf, dn1_dvr_en, en ? 1 : 0);

	BE_WrFL(be_pie_conf);

	spin_unlock_irqrestore(&be_reg_lock, flag);

	if (be_reg_cfg->version >= 1) {
		/* Enable PIDF Download to fix dn_index problem */
		TE_REG_EnablePIDFDownload(dn_src, en);
	}

	return 0;
}
