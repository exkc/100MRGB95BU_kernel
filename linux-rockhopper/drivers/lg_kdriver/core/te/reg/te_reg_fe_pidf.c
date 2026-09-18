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

#define CHECK_CHANNEL(ch) \
  CHECK_PARAM((ch)>=pidf_reg_cfg->num_ch, "invalid channel(%d)\n", ch)

#define CHECK_NORMAL_CHANNEL(ch) \
  CHECK_PARAM((ch)>=pidf_reg_cfg->num_normal_ch, "invalid channel(%d)\n", ch)

#define CHECK_PIDF_IDX(idx) \
  CHECK_PARAM((idx)>=pidf_reg_cfg->num_pidf, "invalid idx(%d)\n", idx)

#define CHECK_SUBPIDF_IDX(idx) \
  CHECK_PARAM((idx)>=pidf_reg_cfg->num_sub_pidf, "invalid idx(%d)\n", idx)

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

	u16 num_pidf;
	u8 num_sub_pidf;
} PIDF_CFG_T;


/*
 * PIDF META EXTENSION for s/w extension
 * we define 2bit meta value as below
 */
#define PIDF_METAEXT_TEMI_EN	(0x1 << 0)
#define PIDF_METAEXT_MCU0_ONLY	(0x1 << 1)


static DEFINE_SPINLOCK(fe_pidf_reg_lock);

static const PIDF_CFG_T pidf_cfg_normal = {
	.version = 1,
	.num_ch = 6,
	.num_normal_ch = 4,

	.num_pidf = 256,
	.num_sub_pidf = 2,
};

/* O18, M16P3 */
static const PIDF_CFG_T pidf_cfg_y19 = {
	.version = 0,
	.num_ch = 6,
	.num_normal_ch = 4,

	.num_pidf = 256,
	.num_sub_pidf = 2,
};

static const PIDF_CFG_T *pidf_reg_cfg;

/*========================================================================================
  Implementation Group
  ========================================================================================*/

int TE_REG_FE_PIDF_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O18:
	case LX_CHIP_M19:
		pidf_reg_cfg = &pidf_cfg_y19;
		break;
	default: // O20 ~
		pidf_reg_cfg = &pidf_cfg_normal;
		break;
	}

	return 0;
}

int TE_REG_GetChannelPktCount(u8 ch, u32 *val)
{
	unsigned long flag;
	int idx;

	CHECK_CHANNEL(ch);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	if (ch < pidf_reg_cfg->num_normal_ch) {
		idx = ch;
		FE_PIDF_RdFL(pidf_ch[idx].packet_count);
		FE_PIDF_Rd(pidf_ch[idx].packet_count, *val);
	} else {
		idx = ch - pidf_reg_cfg->num_normal_ch;
		FE_PIDF_RdFL(pidf_sub_ch[idx].packet_count);
		FE_PIDF_Rd(pidf_sub_ch[idx].packet_count, *val);
	}

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	TRACE_EXIT("ch=%d,*val=0x%x", ch, *val);

	return 0;
}

int TE_REG_SetChannelDownloadIdx(u8 ch, u8 idx)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);
	CHECK_PARAM((idx) >= 2, "invalid idx(%d)\n", idx);

	TRACE_ENTER("ch=%d,idx=%d", ch, idx);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_ch[ch].conf);
	FE_PIDF_Wr01(pidf_ch[ch].conf, dnload_idx, idx);
	FE_PIDF_WrFL(pidf_ch[ch].conf);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

static int GetPesTypeIdx(enum te_reg_pidf_type type)
{
	int idx;

	switch (type) {
	case PIDF_TYPE_AUDIO:
		idx = 0;
		break;
	case PIDF_TYPE_VIDEO:
		idx = 1;
		break;
	case PIDF_TYPE_SECTION:
		idx = 2;
		break;
	case PIDF_TYPE_DATA:
	case PIDF_TYPE_TSHEADER:
		idx = 3;
		break;
	case PIDF_TYPE_PIE:
		idx = 1;
		break;		//Same as video
	default:
		idx = -1;
		break;
	}

	return idx;
}

static int GetPesType(u8 idx)
{
	int type;

	switch (idx) {
	case 0:
		type = PIDF_TYPE_AUDIO;
		break;
	case 1:
		type = PIDF_TYPE_VIDEO;
		break;
	case 2:
		type = PIDF_TYPE_SECTION;
		break;
	case 3:
		type = PIDF_TYPE_DATA;
		break;
	default:
		type = PIDF_TYPE_DATA;
		break;
	}

	return type;
}

int TE_REG_SetPidFilter(u8 idx, struct te_reg_pidf_conf *conf)
{
	unsigned long flag;
	int v;

	CHECK_PIDF_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d,pid=0x%04x,ch=%d,"
		    "type=%d,out_en=%d,out_idx=%d,dn_en=%d",
		    idx, conf->en, conf->pid, conf->ch, conf->type,
		    conf->out_en, conf->out_idx, conf->dn_en);

	v = GetPesTypeIdx(conf->type);
	CHECK_PARAM(v < 0, "Invalid Type[%d]", conf->type);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_Wr01(pidf_conf[idx], pidf_val, (conf->en) ? 1 : 0);
	FE_PIDF_Wr01(pidf_conf[idx], ref_pid, conf->pid);
	FE_PIDF_Wr01(pidf_conf[idx], meta_chan, conf->ch);
	FE_PIDF_Wr01(pidf_conf[idx], meta_type, v);
	FE_PIDF_Wr01(pidf_conf[idx], meta_out_en, (conf->out_en) ? 1 : 0);
	FE_PIDF_Wr01(pidf_conf[idx], meta_out_idx, conf->out_idx);
	FE_PIDF_Wr01(pidf_conf[idx], meta_dn_en, (conf->dn_en) ? 1 : 0);
	if (pidf_reg_cfg->version >= 1) {
		u8 meta_ext = 0;

		if (conf->temi_en)
			meta_ext |= PIDF_METAEXT_TEMI_EN;

		if (conf->type == PIDF_TYPE_TSHEADER)
			meta_ext |= PIDF_METAEXT_MCU0_ONLY;

		FE_PIDF_Wr01(pidf_conf[idx], meta_ext, meta_ext);
	}
	FE_PIDF_WrFL(pidf_conf[idx]);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_SetSubPidFilter(u8 idx, struct te_reg_pidf_conf *conf)
{
	unsigned long flag;

	CHECK_SUBPIDF_IDX(idx);

	TRACE_ENTER("idx=%d,en=%d,pid=0x%04x", idx, conf->en, conf->pid);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_Wr01(pidf_sub_ch[idx].conf, pidf_val, (conf->en) ? 1 : 0);
	FE_PIDF_Wr01(pidf_sub_ch[idx].conf, ref_pid, conf->pid);
	if (pidf_reg_cfg->version >= 1) {
		u8 meta_ext = 0;

		if (conf->temi_en)
			meta_ext |= PIDF_METAEXT_TEMI_EN;
		if (conf->type == PIDF_TYPE_TSHEADER)
			meta_ext |= PIDF_METAEXT_MCU0_ONLY;

		FE_PIDF_Wr01(pidf_sub_ch[idx].conf, meta_ext, meta_ext);
	}
	FE_PIDF_WrFL(pidf_sub_ch[idx].conf);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_ClearPidFilter(u8 idx)
{
	struct te_reg_pidf_conf pidf_conf;

	TRACE_ENTER("idx=%d", idx);

	memset(&pidf_conf, 0x0, sizeof(struct te_reg_pidf_conf));	//All set to zero

	return TE_REG_SetPidFilter(idx, &pidf_conf);
}

int TE_REG_EnablePidFilter(u8 idx)
{
	unsigned long flag;

	TRACE_ENTER("idx=%d", idx);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_conf[idx]);
	FE_PIDF_Wr01(pidf_conf[idx], pidf_val, 1);
	FE_PIDF_WrFL(pidf_conf[idx]);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_DisablePidFilter(u8 idx)
{
	unsigned long flag;

	TRACE_ENTER("idx=%d", idx);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_conf[idx]);
	FE_PIDF_Wr01(pidf_conf[idx], pidf_val, 0);
	FE_PIDF_WrFL(pidf_conf[idx]);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_GetPidFilter(u8 idx, struct te_reg_pidf_status *s)
{
	unsigned long flag;
	u32 v;
	u8 pes_idx, meta_ext;

	CHECK_PIDF_IDX(idx);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_conf[idx]);
	FE_PIDF_Rd(pidf_conf[idx], s->val);

	FE_PIDF_Rd01(pidf_conf[idx], pidf_val, v);
	s->en = v ? true : false;
	FE_PIDF_Rd01(pidf_conf[idx], ref_pid, s->pid);
	FE_PIDF_Rd01(pidf_conf[idx], meta_chan, s->ch);

	FE_PIDF_Rd01(pidf_conf[idx], meta_type, pes_idx);
	s->type = GetPesType(pes_idx);

	if (pidf_reg_cfg->version >= 1) {
		FE_PIDF_Rd01(pidf_conf[idx], meta_ext, meta_ext);
		s->temi_en = (meta_ext & PIDF_METAEXT_TEMI_EN) ? true : false;
		if (meta_ext & PIDF_METAEXT_MCU0_ONLY)
			s->type = PIDF_TYPE_TSHEADER;
	} else {
		s->temi_en = false;
	}

	FE_PIDF_Rd01(pidf_conf[idx], meta_out_en, v);
	s->out_en = v ? true : false;
	FE_PIDF_Rd01(pidf_conf[idx], meta_out_idx, s->out_idx);
	FE_PIDF_Rd01(pidf_conf[idx], meta_dn_en, v);
	s->dn_en = v ? true : false;
	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	TRACE_EXIT("idx=%d,en=%d,pid=0x%04x,ch=%d,"
		   "type=%d,out_en=%d,out_idx=%d,dn_en=%d",
		   idx, s->en, s->pid, s->ch, s->type, s->out_en, s->out_idx,
		   s->dn_en);

	return 0;
}

static enum te_reg_pidf_bypass_type idx_to_pidf_bypass_type(u8 index)
{
	enum te_reg_pidf_bypass_type mode;

	switch (index) {
	case 1:
		mode = PIDF_BYPASS_TYPE_188BYTE;
		break;
	case 2:
		mode = PIDF_BYPASS_TYPE_192BYTE;
		break;
	default:
		mode = PIDF_BYPASS_DISABLE;
		break;
	}

	return mode;
}

int TE_REG_GetSubPidFilter(u8 idx, struct te_reg_pidf_status *s)
{
	u32 val;
	unsigned long flag;

	CHECK_SUBPIDF_IDX(idx);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_sub_ch[idx].conf);
	FE_PIDF_Rd(pidf_sub_ch[idx], s->val);

	FE_PIDF_Rd01(pidf_sub_ch[idx].conf, pidf_val, val);
	s->en = val ? true : false;
	FE_PIDF_Rd01(pidf_sub_ch[idx].conf, pidf_bypass, val);
	s->bypass_mode = idx_to_pidf_bypass_type(val);
	FE_PIDF_Rd01(pidf_sub_ch[idx].conf, ref_pid, s->pid);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	TRACE_EXIT("idx=%d,en=%d,pid=0x%04x", idx, s->en, s->pid);

	return 0;
}

static int pidf_bypass_type_to_idx(enum te_reg_pidf_bypass_type type)
{
	int idx;

	switch (type) {
	case PIDF_BYPASS_DISABLE:
		idx = 0;
		break;
	case PIDF_BYPASS_TYPE_188BYTE:
		idx = 1;
		break;
	case PIDF_BYPASS_TYPE_192BYTE:
		idx = 2;
		break;
	default:
		idx = -1;
		break;
	}

	return idx;
}

int TE_REG_SetSubpidfBypass(u8 idx, enum te_reg_pidf_bypass_type type)
{
	unsigned long flag;
	int type_idx;

	CHECK_SUBPIDF_IDX(idx);

	type_idx = pidf_bypass_type_to_idx(type);
	CHECK_PARAM(type_idx < 0, "Invalid type[%d]", type);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_sub_ch[idx].conf);
	FE_PIDF_Wr01(pidf_sub_ch[idx].conf, pidf_bypass, type_idx);
	FE_PIDF_WrFL(pidf_sub_ch[idx].conf);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_SetPidfBypass(u8 ch, enum te_reg_pidf_bypass_type type)
{
	unsigned long flag;
	int type_idx;

	CHECK_NORMAL_CHANNEL(ch);

	type_idx = pidf_bypass_type_to_idx(type);
	CHECK_PARAM(type_idx < 0, "Invalid type[%d]", type);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_ch[ch].conf);
	FE_PIDF_Wr01(pidf_ch[ch].conf, bypass_en, type_idx);
	FE_PIDF_WrFL(pidf_ch[ch].conf);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

int TE_REG_ResetPidFilter(u8 ch)
{
	unsigned long flag;
	u8 idx;

	CHECK_CHANNEL(ch);

	TRACE_ENTER("ch=%d", ch);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	if (ch < pidf_reg_cfg->num_normal_ch) {
		idx = ch;

		FE_PIDF_RdFL(pidf_ch[idx].conf);
		FE_PIDF_Wr01(pidf_ch[idx].conf, swreset, 1);
		FE_PIDF_WrFL(pidf_ch[idx].conf);
	} else {
		idx = ch - pidf_reg_cfg->num_normal_ch;

		FE_PIDF_RdFL(pidf_sub_ch[idx].conf);
		FE_PIDF_Wr01(pidf_sub_ch[idx].conf, swreset, 1);
		FE_PIDF_WrFL(pidf_sub_ch[idx].conf);
	}

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}

//M16P3 ~
int TE_REG_EnablePIDFDownload(u8 ch, bool en)
{
	unsigned long flag;

	CHECK_NORMAL_CHANNEL(ch);

	spin_lock_irqsave(&fe_pidf_reg_lock, flag);

	FE_PIDF_RdFL(pidf_ch[ch].conf);
	FE_PIDF_Wr01(pidf_ch[ch].conf, dnload_en, (en) ? 1 : 0);
	FE_PIDF_WrFL(pidf_ch[ch].conf);

	spin_unlock_irqrestore(&fe_pidf_reg_lock, flag);

	return 0;
}
