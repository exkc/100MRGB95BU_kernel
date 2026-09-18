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
 *  @date	2015-02-09
 *  @note	Additional information.
 */

#include "te_impl.h"
#include "te_reg_ctrl.h"

#define CHECK_NORMAL_CHANNEL(ch) \
  CHECK_PARAM((ch)>=stcc_cfg->num_ch, "invalid channel(%d)\n", ch)

#define CHECK_GSTCC_IDX(idx) \
  CHECK_PARAM((idx)>=stcc_cfg->num_gstcc, "invalid idx(%d)\n", idx)

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
	u8 num_gstcc;

	/* 1: clock counter increased during reading
	 * 2: added atomic operation but read the previous latched value */
	u8 fixup_stcc_read;
	u8 fixup_gstcc_read;
	u8 no_clock; // O22 A0 clock workaround
} STCC_CFG_T;

static DEFINE_SPINLOCK(fe_stcc_reg_lock);

/* O18 */
static STCC_CFG_T stcc_cfg_y18 = {
	.version = 1,
	.num_ch = 4,
	.num_gstcc = 2,
	.fixup_stcc_read = 1,
	.fixup_gstcc_read = 1,
};

/* M16P3 */
static STCC_CFG_T stcc_cfg_y19 = {
	.version = 2,
	.num_ch = 4,
	.num_gstcc = 4,
	.fixup_stcc_read = 1,
	.fixup_gstcc_read = 1,
};

/* O20, E60 */
static STCC_CFG_T stcc_cfg_y21 = {
	.version = 2,
	.num_ch = 4,
	.num_gstcc = 4,
	.fixup_stcc_read = 1,
	.fixup_gstcc_read = 2, /* atomic read added in gstcc but has bug */
};

/* >= O22 */
static STCC_CFG_T stcc_cfg_normal = {
	.version = 3,
	.num_ch = 4,
	.num_gstcc = 4,
};

static STCC_CFG_T *stcc_cfg;

/*========================================================================================
 * Implementation Group
 *========================================================================================*/

int TE_REG_FE_STCC_Init(void)
{
	struct te_config *chip_cfg = te_get_config();

	switch (lx_chip()) {
	case LX_CHIP_O18:
		stcc_cfg = &stcc_cfg_y18;
		break;
	case LX_CHIP_M19: // M16P3
		stcc_cfg = &stcc_cfg_y19;
		break;
	case LX_CHIP_O20:
	case LX_CHIP_E60:
		stcc_cfg = &stcc_cfg_y21;
		break;
	case LX_CHIP_O22:
	default: // O22 ~
		stcc_cfg = &stcc_cfg_normal;
		if (chip_cfg->no_stcc_bug) {
			stcc_cfg->no_clock = 1;
			log_error("STCC - No clock provided");
		}
		break;
	}

	return 0;
}

int TE_REG_SetStccSource(enum te_reg_pes_dest dest, u8 src)
{
	int ret;
	unsigned long flag;

	TRACE_ENTER("dest=%d,src=%d", dest, src);
	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	ret = 0;

	if (stcc_cfg->version >= 2) {
		FE_STCC_RdFL(stcc_out_sel);
		switch (dest) {
		case PES_DEST_VIDEO0:
			FE_STCC_Wr01(stcc_out_sel, vid0_stcc_sel, src);
			break;
		case PES_DEST_VIDEO1:
			FE_STCC_Wr01(stcc_out_sel, vid1_stcc_sel, src);
			break;
		case PES_DEST_AUDIO0:
			FE_STCC_Wr01(stcc_out_sel, aud0_stcc_sel, src);
			break;
		case PES_DEST_AUDIO1:
			FE_STCC_Wr01(stcc_out_sel, aud1_stcc_sel, src);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		FE_STCC_WrFL(stcc_out_sel);
	} else {
		FE_STCC_Y18_RdFL(stcc_out_sel);
		switch (dest) {
		case PES_DEST_VIDEO0:
			FE_STCC_Y18_Wr01(stcc_out_sel, vid0_stcc_sel, src);
			break;
		case PES_DEST_VIDEO1:
			FE_STCC_Y18_Wr01(stcc_out_sel, vid1_stcc_sel, src);
			break;
		case PES_DEST_AUDIO0:
			FE_STCC_Y18_Wr01(stcc_out_sel, aud0_stcc_sel, src);
			break;
		case PES_DEST_AUDIO1:
			FE_STCC_Y18_Wr01(stcc_out_sel, aud1_stcc_sel, src);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		FE_STCC_Y18_WrFL(stcc_out_sel);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return ret;
}

int TE_REG_SetPcrPid(u8 ch, u16 pid, bool en)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,pid=0x%x,en=%d", ch, pid, en);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version == 0) {
		FE_STCC_Y18_RdFL(stcc_ch[ch].conf);
		FE_STCC_Y18_Wr01(stcc_ch[ch].conf, pcr_pid_val, (en) ? 1 : 0);
		FE_STCC_Y18_Wr01(stcc_ch[ch].conf, pcr_pid, pid);
		FE_STCC_Y18_WrFL(stcc_ch[ch].conf);
	} else if (stcc_cfg->version == 1) {
		FE_STCC_Y18_RdFL(stcc_pcr_pid[ch]);
		FE_STCC_Y18_Wr01(stcc_pcr_pid[ch], pcr_pid_val, (en) ? 1 : 0);
		FE_STCC_Y18_Wr01(stcc_pcr_pid[ch], pcr_pid, pid);
		FE_STCC_Y18_WrFL(stcc_pcr_pid[ch]);
	} else {
		FE_STCC_RdFL(stcc_pcr_pid[ch]);
		FE_STCC_Wr01(stcc_pcr_pid[ch], pcr_pid_val, (en) ? 1 : 0);
		FE_STCC_Wr01(stcc_pcr_pid[ch], pcr_pid, pid);
		FE_STCC_WrFL(stcc_pcr_pid[ch]);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_EnableStcc(u8 ch, bool en)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,en=0x%x", ch, en);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].conf);
	FE_STCC_Wr01(stcc_ch[ch].conf, stcc_en, en ? 1 : 0);
	FE_STCC_WrFL(stcc_ch[ch].conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStccMain(u8 ch, bool main)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,main=0x%x", ch, main);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].conf);
	FE_STCC_Wr01(stcc_ch[ch].conf, main, main ? 1 : 0);
	FE_STCC_WrFL(stcc_ch[ch].conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStccSubMode(u8 ch, enum te_reg_pcr_mode pcr_mode)
{
	unsigned long flag;
	u8 v;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,pcr_mode=%d", ch, pcr_mode);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	switch (pcr_mode) {
	case PCR_MODE_AUTORATE:
		v = 0;
		break;

	case PCR_MODE_MANUAL:
		v = 1;
		break;

	case PCR_MODE_GSTCCMODE:
		v = 2;
		break;

	default:		//Not support ALWAYSCOPY
		log_error("Not supported pcr_mode [%d]", pcr_mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].sub_rctrl);
	FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_stcc_mode, v);
	FE_STCC_WrFL(stcc_ch[ch].sub_rctrl);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStccSubPcrUnitStep(u8 ch, int step)
{
	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,step=%d", ch, step);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	FE_STCC_RdFL(stcc_ch[ch].sub_rctrl);
	if (step == 0) {
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_rate_ctrl, 0x0);
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_unit_step, 0x0);
	} else if (step > 0) {
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_rate_ctrl, 0x1);
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_unit_step, step);
	} else {		// (step < 0)
		step = step * (-1);
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_rate_ctrl, 0x2);
		FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, sub_unit_step, step);
	}

	/* Reset rate control counter to adjust the new value immediately */
	FE_STCC_Wr01(stcc_ch[ch].sub_rctrl, rate_ctrl_cnt_init, 0x1);
	FE_STCC_WrFL(stcc_ch[ch].sub_rctrl);

	return 0;
}

int TE_REG_ResetStcc(u8 ch)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].conf);
	FE_STCC_Wr01(stcc_ch[ch].conf, stcc_swreset, 1);	/* auto clear */
	FE_STCC_WrFL(stcc_ch[ch].conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStccEnableCopy(u8 ch)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].conf);
	FE_STCC_Wr01(stcc_ch[ch].conf, copy_en, 1);
	FE_STCC_WrFL(stcc_ch[ch].conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStccLatchEnable(u8 ch, bool en)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	TRACE_VERBOSE_ENTER("ch=%d,en=%d", ch, en);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].conf);
	FE_STCC_Wr01(stcc_ch[ch].conf, latch_en, (en) ? 1 : 0);
	FE_STCC_WrFL(stcc_ch[ch].conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetPcrJitter(u8 ch, bool detection, u32 jitter)
{
	unsigned long flag;
	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,detection=%d,jitter=%d", ch, detection, jitter);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(stcc_ch[ch].jitter);
	FE_STCC_Wr01(stcc_ch[ch].jitter, auto_discont_en, (detection) ? 1 : 0);
	FE_STCC_Wr01(stcc_ch[ch].jitter, max_jitter, jitter);
	FE_STCC_WrFL(stcc_ch[ch].jitter);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetStcc(u8 ch, u32 base_32, u32 base_31_0)
{
	unsigned long flag;
	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("ch=%d,base_32=0x%x,base_31_0=0x%x", ch, base_32,
		    base_31_0);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	/* stcc counter reigster is separated into two registers, so
	 * one register would be changed while writing another register.
	 * It means the atomic operation is necessary to access this register.
	 * H/W is ready to fix this problem as below:
	 *  Writing the stcc_ext register is just saving the value into
	 *  the internal register, and applied to h/w when stcc_base register
	 *  is written */
	FE_STCC_RdFL(stcc_ch[ch].cur_stcc_ext);
	FE_STCC_Wr01(stcc_ch[ch].cur_stcc_ext, hif_stcc_base_32, base_32);
	FE_STCC_Wr01(stcc_ch[ch].cur_stcc_ext, hif_stcc_ext, 0);
	FE_STCC_WrFL(stcc_ch[ch].cur_stcc_ext);

	FE_STCC_Wr(stcc_ch[ch].cur_stcc_base, base_31_0);
	FE_STCC_WrFL(stcc_ch[ch].cur_stcc_base);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_GetLiveStcc(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	if (stcc_cfg->no_clock) {
		*base_32 = 0;
		*base_31_0 = 0;
		*ext = 0;
		return -ENODEV;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	/* stcc counter reigster is separated into two registers, so
	 * one register would be changed while reading another register.
	 * It means the atomic operation is necessary to access this register.
	 * H/W is ready to fix this problem as below:
	 *  When reading stcc_ext register, stcc_base register is also loaded
	 *  into the internal register, and reading stcc_base register returns
	 *  this internal register value */
	FE_STCC_RdFL(stcc_ch[ch].cur_stcc_ext);
	FE_STCC_Rd01(stcc_ch[ch].cur_stcc_ext, hif_stcc_base_32, *base_32);
	FE_STCC_Rd01(stcc_ch[ch].cur_stcc_ext, hif_stcc_ext, *ext);

	FE_STCC_RdFL(stcc_ch[ch].cur_stcc_base);
	FE_STCC_Rd(stcc_ch[ch].cur_stcc_base, *base_31_0);

	if (stcc_cfg->fixup_stcc_read == 1) {	/* not support atomic operation */
		u32 b, e;

		FE_STCC_RdFL(stcc_ch[ch].cur_stcc_ext);
		FE_STCC_Rd01(stcc_ch[ch].cur_stcc_ext, hif_stcc_base_32, b);
		FE_STCC_Rd01(stcc_ch[ch].cur_stcc_ext, hif_stcc_ext, e);

		/* Read again base_31_0 register if base_32 register is
		 * changed, it means wraparound occurs. */
		if (b != *base_32) {
			FE_STCC_RdFL(stcc_ch[ch].cur_stcc_base);
			FE_STCC_Rd(stcc_ch[ch].cur_stcc_base, *base_31_0);
			*base_32 = b;
			*ext = e;
		}
	} else if (stcc_cfg->fixup_stcc_read == 2) {
		/* Read base32 register again, because it returns
		 * the preivous latched value  */
		FE_STCC_RdFL(stcc_ch[ch].cur_stcc_ext);
		FE_STCC_Rd01(stcc_ch[ch].cur_stcc_ext, hif_stcc_base_32, *base_32);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	TRACE_VERBOSE_EXIT("ch=%d,*base_32=0x%x,*base_31_0=0x%x,*ext=0x%x",
			   ch, *base_32, *base_31_0, *ext);

	return 0;
}

int TE_REG_GetLatchedStcc(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext)
{
	CHECK_NORMAL_CHANNEL(ch);

	if (stcc_cfg->no_clock) {
		*base_32 = 0;
		*base_31_0 = 0;
		*ext = 0;
		return -ENODEV;
	}

	FE_STCC_RdFL(stcc_ch[ch].latched_stcc_base);
	FE_STCC_Rd(stcc_ch[ch].latched_stcc_base, *base_31_0);

	FE_STCC_RdFL(stcc_ch[ch].latched_stcc_ext);
	FE_STCC_Rd01(stcc_ch[ch].latched_stcc_ext, latched_stcc_base_32,
		     *base_32);
	FE_STCC_Rd01(stcc_ch[ch].latched_stcc_ext, latched_stcc_ext, *ext);

	TRACE_VERBOSE_EXIT("ch=%d,*base_32=0x%x,*base_31_0=0x%x,*ext=0x%x",
			   ch, *base_32, *base_31_0, *ext);

	return 0;
}

int TE_REG_GetLatchedPcr(u8 ch, u32 *base_32, u32 *base_31_0, u32 *ext)
{
	CHECK_NORMAL_CHANNEL(ch);

	if (stcc_cfg->no_clock) {
		*base_32 = 0;
		*base_31_0 = 0;
		*ext = 0;
		return -ENODEV;
	}

	FE_STCC_RdFL(stcc_ch[ch].latched_pcr_base);
	FE_STCC_Rd(stcc_ch[ch].latched_pcr_base, *base_31_0);

	FE_STCC_RdFL(stcc_ch[ch].latched_pcr_ext);
	FE_STCC_Rd01(stcc_ch[ch].latched_pcr_ext, latched_pcr_base_32,
		     *base_32);
	FE_STCC_Rd01(stcc_ch[ch].latched_pcr_ext, latched_pcr_ext, *ext);

	TRACE_VERBOSE_EXIT("ch=%d,*base_32=0x%x,*base_31_0=0x%x,*ext=0x%x",
			   ch, *base_32, *base_31_0, *ext);

	return 0;
}

int TE_REG_ResetGstcc(u8 idx)
{
	unsigned long flag;

	CHECK_GSTCC_IDX(idx);

	TRACE_ENTER("idx=%d", idx);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);
	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_conf);
		FE_STCC_Wr01(gstcc[idx].gstcc_conf, gstcc_swreset, 1);
		FE_STCC_WrFL(gstcc[idx].gstcc_conf);
	} else {
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_conf);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_conf, gstcc_swreset, 1);
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_conf);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetGstccConf(u8 idx, u8 ext_incr, u32 ext_unit, u8 en)
{
	unsigned long flag;

	CHECK_GSTCC_IDX(idx);

	TRACE_ENTER("idx=%d,ext_incr=%d,ext_unit=%d,en=%d",
		    idx, ext_incr, ext_unit, en);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);
	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_conf);
		FE_STCC_Wr01(gstcc[idx].gstcc_conf, gstcc_en, (en) ? 1 : 0);
		FE_STCC_Wr01(gstcc[idx].gstcc_conf, gstcc_ext_incr, ext_incr);
		FE_STCC_Wr01(gstcc[idx].gstcc_conf, gstcc_ext_unit, ext_unit);
		FE_STCC_WrFL(gstcc[idx].gstcc_conf);
	} else {
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_conf);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_conf, gstcc_en, (en) ? 1 : 0);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_conf, gstcc_ext_incr, ext_incr);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_conf, gstcc_ext_unit, ext_unit);
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_conf);
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

// TODO: check hw fixed or not.
int TE_REG_GetGstcc(u8 idx, u32 *base_32, u32 *base_31_0, u32 *ext)
{
	unsigned long flag;
	CHECK_GSTCC_IDX(idx);

	if (stcc_cfg->no_clock) {
		*base_32 = 0;
		*base_31_0 = 0;
		*ext = 0;
		return -ENODEV;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);
	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_ext);
		FE_STCC_Rd01(gstcc[idx].gstcc_ext, gstcc_base_32, *base_32);
		FE_STCC_Rd01(gstcc[idx].gstcc_ext, gstcc_ext, *ext);

		FE_STCC_RdFL(gstcc[idx].gstcc_base);
		FE_STCC_Rd(gstcc[idx].gstcc_base, *base_31_0);
	} else {

		/* Read gstcc_ext register first to guarantee atomic operation.
		 * Refer to TE_REG_GetLiveStcc */
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_ext);
		FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_base_32, *base_32);
		FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_ext, *ext);

		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_base);
		FE_STCC_Y21_Rd(gstcc[idx].gstcc_base, *base_31_0);

		if (stcc_cfg->fixup_gstcc_read == 1) {	/* not support atomic operation */
			u32 b, e;

			FE_STCC_Y21_RdFL(gstcc[idx].gstcc_ext);
			FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_base_32, b);
			FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_ext, e);

			/* Read again base_31_0 register if base_32 register is
			 * changed, it means wraparound occurs. */
			if (b != *base_32) {
				FE_STCC_Y21_RdFL(gstcc[idx].gstcc_base);
				FE_STCC_Y21_Rd(gstcc[idx].gstcc_base, *base_31_0);
				*base_32 = b;
				*ext = e;
			}
		} else if (stcc_cfg->fixup_gstcc_read == 2) {
			u32 b, e, l;
			/* Read base32 register again, because it returns
			 * the preivous latched value  */
			FE_STCC_Y21_RdFL(gstcc[idx].gstcc_ext);
			FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_base_32, *base_32);
			FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_ext, e);

			/* Atomic operation is not guaranteed becuase MCU also read
			 * this register.
			 * We have to check base_32 value again to confirm this value */
			FE_STCC_Y21_RdFL(gstcc[idx].gstcc_base);
			FE_STCC_Y21_Rd(gstcc[idx].gstcc_base, l);

			FE_STCC_Y21_RdFL(gstcc[idx].gstcc_ext);
			FE_STCC_Y21_Rd01(gstcc[idx].gstcc_ext, gstcc_base_32, b);
			if (b != *base_32) {
				*base_32 = b;
				*base_31_0 = l;
				*ext = e;
			}
		}
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	TRACE_VERBOSE_EXIT("idx=%d,*base_32=0x%x,*base_31_0=0x%x,*ext=0x%x",
			   idx, *base_32, *base_31_0, *ext);

	return 0;
}

int TE_REG_SetGstcc(u8 idx, u32 base_32, u32 base_31_0, u32 ext)
{
	unsigned long flag;
	CHECK_GSTCC_IDX(idx);

	TRACE_ENTER("idx=%d,base_32=0x%x,base_31_0=0x%x,ext=0x%x",
		    idx, base_32, base_31_0, ext);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 3) {
		/* Write gstcc_ext register first to guarantee atomic operation.
		 * Refer to TE_REG_SetStcc */
		FE_STCC_RdFL(gstcc[idx].gstcc_ext);
		FE_STCC_Wr01(gstcc[idx].gstcc_ext, gstcc_base_32, base_32);
		FE_STCC_Wr01(gstcc[idx].gstcc_ext, gstcc_ext, ext);
		FE_STCC_WrFL(gstcc[idx].gstcc_ext);	/* keep this value till write access to gstcc_base[31:0] */

		FE_STCC_Wr(gstcc[idx].gstcc_base, base_31_0);
		FE_STCC_WrFL(gstcc[idx].gstcc_base);
	} else {
		/* Write gstcc_ext register first to guarantee atomic operation.
		 * Refer to TE_REG_SetStcc */
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_ext);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_ext, gstcc_base_32, base_32);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_ext, gstcc_ext, ext);
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_ext);	/* keep this value till write access to gstcc_base[31:0] */

		FE_STCC_Y21_Wr(gstcc[idx].gstcc_base, base_31_0);
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_base);
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetGstccMode(u8 idx, enum te_reg_gstcc_mode mode)
{
	unsigned long flag;
	u8 val1;

	CHECK_GSTCC_IDX(idx);

	TRACE_ENTER("idx=%d,mode=%d", idx, mode);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	switch (mode) {
	case GSTCC_MODE_EXTINCR:
		val1 = 0;
		break;

	case GSTCC_MODE_UNITSTEP:
		val1 = 1;
		break;

	default:		//Not support ALWAYSCOPY
		log_error("Not supported gstcc_mode [%d]", mode);
		return -EINVAL;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);
	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_rctrl);
		FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, ctrl_mode, val1);
		FE_STCC_WrFL(gstcc[idx].gstcc_rctrl);
	} else {
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_rctrl);
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, ctrl_mode, val1);
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_rctrl);
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_SetGstccUnitStep(u8 idx, int step)
{
	unsigned long flag;

	CHECK_GSTCC_IDX(idx);

	TRACE_ENTER("idx=%d,step=%d", idx, step);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_rctrl);
		if (step == 0) {
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x0);
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, unit_step, 0x0);
		} else if (step > 0) {
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x1);
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, unit_step, step);
		} else			// (step < 0)
		{
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x2);
			FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, unit_step, -step);
		}
		FE_STCC_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl_cnt_init, 0x1);	//Reset Counter
		FE_STCC_WrFL(gstcc[idx].gstcc_rctrl);

	} else {
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_rctrl);
		if (step == 0) {
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x0);
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, unit_step, 0x0);
		} else if (step > 0) {
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x1);
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, unit_step, step);
		} else			// (step < 0)
		{
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl, 0x2);
			FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, unit_step, -step);
		}
		FE_STCC_Y21_Wr01(gstcc[idx].gstcc_rctrl, rate_ctrl_cnt_init, 0x1);	//Reset Counter
		FE_STCC_Y21_WrFL(gstcc[idx].gstcc_rctrl);
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_GetLatchedGstcc(u8 idx, u32 *base_32, u32 *base_31_0, u32 *ext)
{
	unsigned long flag;

	CHECK_GSTCC_IDX(idx);

	if (stcc_cfg->no_clock) {
		*base_32 = 0;
		*base_31_0 = 0;
		*ext = 0;
		return -ENODEV;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 3) {
		FE_STCC_RdFL(gstcc[idx].gstcc_latched_base);
		FE_STCC_Rd(gstcc[idx].gstcc_latched_base, *base_31_0);

		FE_STCC_RdFL(gstcc[idx].gstcc_latched_ext);
		FE_STCC_Rd01(gstcc[idx].gstcc_latched_ext, gstcc_base_32, *base_32);
		FE_STCC_Rd01(gstcc[idx].gstcc_latched_ext, gstcc_ext, *ext);

	} else {
		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_latched_base);
		FE_STCC_Y21_Rd(gstcc[idx].gstcc_latched_base, *base_31_0);

		FE_STCC_Y21_RdFL(gstcc[idx].gstcc_latched_ext);
		FE_STCC_Y21_Rd01(gstcc[idx].gstcc_latched_ext, gstcc_base_32, *base_32);
		FE_STCC_Y21_Rd01(gstcc[idx].gstcc_latched_ext, gstcc_ext, *ext);
	}
	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	TRACE_VERBOSE_EXIT("idx=%d,*base_32=0x%x,*base_31_0=0x%x,*ext=0x%x",
			   idx, *base_32, *base_31_0, *ext);

	return 0;
}

static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, FE_STCC_INTR_CH0_PCR},
	{0x1 << 1, FE_STCC_INTR_CH1_PCR},
	{0x1 << 2, FE_STCC_INTR_CH2_PCR},
	{0x1 << 3, FE_STCC_INTR_CH3_PCR},
	{0x1 << 4, FE_STCC_INTR_CH0_DISCONT},
	{0x1 << 5, FE_STCC_INTR_CH1_DISCONT},
	{0x1 << 6, FE_STCC_INTR_CH2_DISCONT},
	{0x1 << 7, FE_STCC_INTR_CH3_DISCONT},
	{0x1 << 8, FE_STCC_INTR_GTIMER0},
	{0x1 << 9, FE_STCC_INTR_GTIMER1},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

/* Although M16A0/B0 entry is differ,
 * below codes can be used since it direct writes value in the register (do not see the entry) */
//TODO: Consider rename it if other fe intr should be enabled
int TE_REG_SetFeIntrEnable(u32 val, bool en)
{
	unsigned long flag;
	u32 v, bits;

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 2) {
		FE_STCC_RdFL(stcc_intr_en_cpu);
		FE_STCC_Rd(stcc_intr_en_cpu, v);
		if (en)
			v |= bits;
		else
			v &= ~bits;
		FE_STCC_Wr(stcc_intr_en_cpu, v);
		FE_STCC_WrFL(stcc_intr_en_cpu);
	} else {
		FE_STCC_Y18_RdFL(stcc_intr_en_cpu);
		FE_STCC_Y18_Rd(stcc_intr_en_cpu, v);
		if (en)
			v |= bits;
		else
			v &= ~bits;
		FE_STCC_Y18_Wr(stcc_intr_en_cpu, v);
		FE_STCC_Y18_WrFL(stcc_intr_en_cpu);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

int TE_REG_GetFeIntrStatus(u32 *val)
{
	unsigned long flag;
	u32 bits;

	if (stcc_cfg->no_clock) {
		*val = 0;
		return -ENODEV;
	}

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 2) {
		FE_STCC_RdFL(stcc_intr_stat_cpu);
		FE_STCC_Rd(stcc_intr_stat_cpu, bits);
	} else {
		FE_STCC_Y18_RdFL(stcc_intr_stat_cpu);
		FE_STCC_Y18_Rd(stcc_intr_stat_cpu, bits);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	*val = GetIntrValue(bits);

	return 0;
}

int TE_REG_ClearFeIntr(u32 val)
{
	unsigned long flag;
	u32 bits;

	TRACE_ENTER("val=0x%x", val);

	if (stcc_cfg->no_clock)
		return -ENODEV;

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	if (stcc_cfg->version >= 2) {
		FE_STCC_Wr(stcc_intr_clr_cpu, bits);
		FE_STCC_WrFL(stcc_intr_clr_cpu);
	} else {
		FE_STCC_Y18_Wr(stcc_intr_clr_cpu, bits);
		FE_STCC_Y18_WrFL(stcc_intr_clr_cpu);
	}

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

// ~O18 : TODO: remove
int TE_REG_SetA3LatchEnable(u8 ch, u8 idx, bool en)
{
	unsigned long flag;

	if (stcc_cfg->version >= 2) {
		return te_reg_dumper_set_latch_enable(ch, en);
	}

	TRACE_ENTER("idx=0x%x,en=0x%x", idx, en);
	//CHECK_NORMAL_CHANNEL(ch); //do not need ch
	CHECK_GSTCC_IDX(idx);

	if (stcc_cfg->no_clock) // maybe meaningless
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);

	FE_STCC_RdFL(gstcc[idx].gstcc_conf);
	FE_STCC_Wr01(gstcc[idx].gstcc_conf, a3_latch_en, (en) ? 1 : 0);
	FE_STCC_WrFL(gstcc[idx].gstcc_conf);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}

//M16P3 ~
int TE_REG_SetGstccLatchSource(u8 ch, u8 idx)
{
	unsigned long flag;

	CHECK_GSTCC_IDX(idx);
	CHECK_NORMAL_CHANNEL(ch);

	TRACE_ENTER("idx=0x%x,ch=0x%x", idx, ch);

	if (stcc_cfg->version < 2)	//not support (arib2 swtlv)
		return 0;

	if (stcc_cfg->no_clock)
		return -ENODEV;

	spin_lock_irqsave(&fe_stcc_reg_lock, flag);
	FE_STCC_RdFL(gstcc_latch_sel);
	switch (idx) {
	case 0:
		FE_STCC_Wr01(gstcc_latch_sel, src_core_sel0, ch);
		break;
	case 1:
		FE_STCC_Wr01(gstcc_latch_sel, src_core_sel1, ch);
		break;
	case 2:
		FE_STCC_Wr01(gstcc_latch_sel, src_core_sel2, ch);
		break;
	case 3:
		FE_STCC_Wr01(gstcc_latch_sel, src_core_sel3, ch);
		break;
	default:
		break;
	}
	FE_STCC_WrFL(gstcc_latch_sel);

	spin_unlock_irqrestore(&fe_stcc_reg_lock, flag);

	return 0;
}
