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

#define INVALID_INDEX	0xFFFFFFFF

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_TOP_MASK)) {		\
		log_noti("@TOP_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_TOP_MASK)) {		\
		log_noti("~TOP_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_TOP_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@TOP_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_TOP_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~TOP_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

enum dco_type {
	DCO_TYPE_LEGACY = 0,
	DCO_TYPE_FRPLL,
	DCO_TYPE_NONE,
};

typedef struct {
	u8 version;
	u8 num_ch;
	u8 num_normal_ch;
	u8 num_engine_ch;
	enum dco_type dco_type;

	u8 num_channel_src;
	const struct te_type_conv *channel_src;

	u8 num_upready_src;
	const struct te_type_conv *upready_src;

	u8 num_engine_src;
	const struct te_type_conv *engine_src;
} TOP_CFG_T;

static const struct te_type_conv src_channel_list[] = {
	{CH_SRC_TPI_INT_DEMOD, 0},
	{CH_SRC_TPI_EXT_DEMOD0, 1},
	{CH_SRC_TPI_EXT_DEMOD1, 2},
	{CH_SRC_TPI_CAM_LOOP_BACK, 3},
	{CH_SRC_TPI_CAM_INPUT, 4},
	{CH_SRC_UPLOAD0, 5},
	{CH_SRC_UPLOAD1, 6},
	{CH_SRC_CIP_DEMUX0, 7},
	{CH_SRC_CIP_DEMUX1, 8},
	{CH_SRC_CIP_DEMUX2, 9},
	{CH_SRC_AUDIO_PES0, 11},
	{CH_SRC_AUDIO_PES1, 12},
	{CH_SRC_VIDEO_PES0, 13},
	{CH_SRC_VIDEO_PES1, 14},
	{CH_SRC_DISABLE, 15},
};

static const struct te_type_conv src_upready_list[] = {
	{UPLOAD_READY_SRC_TSBUF0, 0},
	{UPLOAD_READY_SRC_TSBUF1, 1},
	{UPLOAD_READY_SRC_TSBUF2, 2},
	{UPLOAD_READY_SRC_TSBUF3, 3},
	{UPLOAD_READY_SRC_SUB_TSBUF0, 4},
	{UPLOAD_READY_SRC_SUB_TSBUF1, 5},
	{UPLOAD_READY_SRC_TPO_BUF, 6},
	{UPLOAD_READY_SRC_A3_CH0, 7},
	{UPLOAD_READY_SRC_A3_CH1, 8},
	{UPLOAD_READY_SRC_A3_CH2, 9},
	{UPLOAD_READY_SRC_A3_CH3, 10},
	{UPLOAD_READY_ALWAYS, 11},
};

static const struct te_type_conv src_engine_list[] = {	/* ATSC3.0/ARIB2.0 */
	{CH_SRC_TPI_INT_DEMOD, 0},
	{CH_SRC_TPI_EXT_DEMOD0, 1},
	{CH_SRC_TPI_EXT_DEMOD1, 2},
	{CH_SRC_TPI_CAM_LOOP_BACK, 3},
	{CH_SRC_TPI_CAM_INPUT, 4},
	{CH_SRC_UPLOAD0, 5},
	{CH_SRC_UPLOAD1, 6},
	{CH_SRC_DISABLE, 7},
};

/* O18 */
static const TOP_CFG_T top_cfg_y18 = {
	.version = 2,		//includes a3 channel
	.num_ch = 6,
	.num_normal_ch = 4,
	.num_engine_ch = 4,
	.dco_type = DCO_TYPE_LEGACY,

	.num_channel_src = ARRAY_SIZE(src_channel_list),
	.channel_src = src_channel_list,

	.num_upready_src = ARRAY_SIZE(src_upready_list),
	.upready_src = src_upready_list,

	.num_engine_src = ARRAY_SIZE(src_engine_list),
	.engine_src = src_engine_list,
};

static const TOP_CFG_T top_cfg_y19 = {
	.version = 3,		//+ Engine mode (ATSC3 / ARIB2)
	.num_ch = 6,
	.num_normal_ch = 4,
	.num_engine_ch = 4,
	.dco_type = DCO_TYPE_LEGACY,

	.num_channel_src = ARRAY_SIZE(src_channel_list),
	.channel_src = src_channel_list,

	.num_upready_src = ARRAY_SIZE(src_upready_list),
	.upready_src = src_upready_list,

	.num_engine_src = ARRAY_SIZE(src_engine_list),
	.engine_src = src_engine_list,
};

/* ~ 020 */
static const TOP_CFG_T top_cfg_y20 = {
	.version = 4,		//
	.num_ch = 6,
	.num_normal_ch = 4,
	.num_engine_ch = 4,
	.dco_type = DCO_TYPE_FRPLL,

	.num_channel_src = ARRAY_SIZE(src_channel_list),
	.channel_src = src_channel_list,

	.num_upready_src = ARRAY_SIZE(src_upready_list),
	.upready_src = src_upready_list,

	.num_engine_src = ARRAY_SIZE(src_engine_list),
	.engine_src = src_engine_list,
};

/* E60 ~ */
static const TOP_CFG_T top_cfg_normal = {
	.version = 4,		//
	.num_ch = 6,
	.num_normal_ch = 4,
	.num_engine_ch = 4,
	.dco_type = DCO_TYPE_NONE,

	.num_channel_src = ARRAY_SIZE(src_channel_list),
	.channel_src = src_channel_list,

	.num_upready_src = ARRAY_SIZE(src_upready_list),
	.upready_src = src_upready_list,

	.num_engine_src = ARRAY_SIZE(src_engine_list),
	.engine_src = src_engine_list,
};

static const TOP_CFG_T *top_cfg;

static DEFINE_SPINLOCK(top_reg_lock);

int TE_REG_TOP_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O20:
		top_cfg = &top_cfg_y20;
		break;
	case LX_CHIP_M19:
		top_cfg = &top_cfg_y19;
		break;
	case LX_CHIP_O18:
		top_cfg = &top_cfg_y18;
		break;
	default: // E60 ~
		top_cfg = &top_cfg_normal;
		break;
	}

	return 0;
};

static const struct reg_bit_type_conv intr_bit_type[] = {
	{0x1 << 0, TOP_INTR_TSBUF},
	{0x1 << 1, TOP_INTR_STCC},
	{0x1 << 2, TOP_INTR_UPLOAD0},
	{0x1 << 3, TOP_INTR_UPLOAD1},
	{0x1 << 4, TOP_INTR_DSC0},
	{0x1 << 5, TOP_INTR_BE},
	{0x1 << 6, TOP_INTR_CIPLUS},
	{0x1 << 7, TOP_INTR_A3},
	{0x1 << 7, TOP_INTR_DUMPER},
	{0x1 << 12, TOP_INTR_ARIB2},
	{0x1 << 13, TOP_INTR_DSC1},
};

static u32 GetIntrRegBits(u32 val)
{
	return reg_type_to_bits(intr_bit_type, val);
}

static u32 GetIntrValue(u32 bits)
{
	return reg_bits_to_type(intr_bit_type, bits);
}

int TE_REG_SetIntrEnable(u32 val, bool en)
{
	unsigned long flag;
	u32 v;
	u32 bits;

	TRACE_ENTER("val=0x%x,en=%d", val, en);

	bits = GetIntrRegBits(val);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(intr_en);
	TOP_Rd(intr_en, v);
	if (en)
		v |= bits;
	else
		v &= ~bits;
	TOP_Wr(intr_en, v);
	TOP_WrFL(intr_en);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_ClearIntr(u32 val)
{
	u32 bits;

	TRACE_ENTER("val=0x%x", val);

	bits = GetIntrRegBits(val);

	TOP_Wr(intr_clr, bits);
	TOP_WrFL(intr_clr);

	return 0;
}

int TE_REG_GetIntrStatus(u32 *val)
{
	u32 bits;

	TOP_RdFL(intr_stat);
	TOP_Rd(intr_stat, bits);

	*val = GetIntrValue(bits);

	return 0;
}

static u32 get_sdec_source_idx(enum te_reg_channel_src src)
{
	const struct te_type_conv *l = top_cfg->channel_src;
	u32 n = top_cfg->num_channel_src;

	return te_convert_to_type1(l, n, src, INVALID_INDEX);
}

static enum te_reg_channel_src get_sdec_source_from_idx(u8 idx)
{
	const struct te_type_conv *l = top_cfg->channel_src;
	u32 n = top_cfg->num_channel_src;

	return te_convert_to_type0(l, n, idx, CH_SRC_DISABLE);
}

static u32 get_engine_source_idx(enum te_reg_channel_src src)
{
	const struct te_type_conv *l = top_cfg->engine_src;
	u32 n = top_cfg->num_engine_src;

	return te_convert_to_type1(l, n, src, INVALID_INDEX);
}

static enum te_reg_channel_src get_engine_source_from_idx(u8 idx)
{
	const struct te_type_conv *l = top_cfg->engine_src;
	u32 n = top_cfg->num_engine_src;

	return te_convert_to_type0(l, n, idx, CH_SRC_DISABLE);
}

static u32 GetUploadReadySourceIdx(enum te_reg_upload_ready_src src)
{
	const struct te_type_conv *l = top_cfg->upready_src;
	u32 n = top_cfg->num_upready_src;

	return te_convert_to_type1(l, n, src, INVALID_INDEX);
}

int TE_REG_SetChannelSource(u8 ch, enum te_reg_channel_src src)
{
	unsigned long flag;
	u32 v;

	CHECK_PARAM(ch >= top_cfg->num_ch, "invalid channel(%d)\n", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	v = get_sdec_source_idx(src);
	CHECK_PARAM(v == INVALID_INDEX, "invalid src(%d)\n", src);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(chan_sel);

	if (ch < top_cfg->num_normal_ch) {
		switch (ch) {
		case 0:
			TOP_Wr01(chan_sel, chan0_sel, v);
			break;
		case 1:
			TOP_Wr01(chan_sel, chan1_sel, v);
			break;
		case 2:
			TOP_Wr01(chan_sel, chan2_sel, v);
			break;
		case 3:
			TOP_Wr01(chan_sel, chan3_sel, v);
			break;
		default:
			break;
		}
	} else {		/* sub channel */
		ch -= top_cfg->num_normal_ch;
		switch (ch) {
		case 0:
			TOP_Wr01(chan_sel, sub_chan0_sel, v);
			break;
		case 1:
			TOP_Wr01(chan_sel, sub_chan1_sel, v);
			break;
		default:
			break;
		}
	}
	TOP_WrFL(chan_sel);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_GetChannelSource(u8 ch, enum te_reg_channel_src *src)
{
	unsigned long flag;
	u8 idx;

	CHECK_PARAM(ch >= top_cfg->num_ch, "invalid channel(%d)\n", ch);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(chan_sel);
	if (ch < top_cfg->num_normal_ch) {
		switch (ch) {
		case 0:
			TOP_Rd01(chan_sel, chan0_sel, idx);
			break;
		case 1:
			TOP_Rd01(chan_sel, chan1_sel, idx);
			break;
		case 2:
			TOP_Rd01(chan_sel, chan2_sel, idx);
			break;
		case 3:
			TOP_Rd01(chan_sel, chan3_sel, idx);
			break;
		default:
			idx = 0xFF;
			break;
		}
	} else {		/* sub channel */
		ch -= top_cfg->num_normal_ch;
		switch (ch) {
		case 0:
			TOP_Rd01(chan_sel, sub_chan0_sel, idx);
			break;
		case 1:
			TOP_Rd01(chan_sel, sub_chan1_sel, idx);
			break;
		default:
			idx = 0xFF;
			break;
		}
	}
	spin_unlock_irqrestore(&top_reg_lock, flag);

	*src = get_sdec_source_from_idx(idx);

	TRACE_EXIT("ch=%d,*src=%d", ch, *src);

	return 0;
}

int TE_REG_SetUploadReadySel(u8 idx, enum te_reg_upload_ready_src src)
{
	unsigned long flag;
	u32 v;

	CHECK_PARAM(idx >= 2, "invalid idx(%d)\n", idx);

	TRACE_ENTER("idx=%d,src=%d", idx, src);

	v = GetUploadReadySourceIdx(src);
	CHECK_PARAM(v == INVALID_INDEX, "invalid src(%d)\n", src);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(chan_sel);
	switch (idx) {
	case 0:
		TOP_Wr01(chan_sel, upload0_rdy_sel, v);
		break;
	case 1:
		TOP_Wr01(chan_sel, upload1_rdy_sel, v);
		break;
	default:
		break;
	}
	TOP_WrFL(chan_sel);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_SetOutputPort(enum te_reg_channel_src src, enum te_reg_tpo_mode mode,
			 bool clk_inv, bool en)
{
	unsigned long flag;
	u32 v;

	TRACE_ENTER("src=%d,mode=%d,clk_inv=%d,en=%d", src, mode, clk_inv, en);

	v = get_sdec_source_idx(src);
	CHECK_PARAM(v == INVALID_INDEX, "invalid src(%d)\n", src);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_Wr(tpo_conf, 0);	/* clear register */
	TOP_Wr01(tpo_conf, tpo_swreset, 1);	/* soft reset, not auto cleard */
	TOP_WrFL(tpo_conf);

	TOP_Wr01(tpo_conf, tpo_swreset, 0);	/* soft reset, not auto cleard */
	TOP_Wr01(tpo_conf, stpo_sel, v);
	TOP_Wr01(tpo_conf, tpo_mode, (mode == TPO_FORMAT_PARALLEL) ? 1 : 0);
	TOP_Wr01(tpo_conf, tpo_clk_inv, clk_inv ? 1 : 0);
	TOP_Wr01(tpo_conf, tpo_en, en ? 1 : 0);
	TOP_WrFL(tpo_conf);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

static u32 freq_to_fcw(u32 freq, u32 input_clock)
{
#define DCO_COEF		8388608	/* 2^23 */
	u32 fcw;
	u64 v;

	v = (u64)freq * DCO_COEF;
	do_div(v, input_clock);
	fcw = (u32)v;

	return fcw;
}

static void write_stc_references(void)
{
	u32 real_32, real_31_0;
	u32 ref_32, ref_31_0;

	TOP_RdFL(dco_stcc_mon32);
	TOP_RdFL(dco_stcc_mon31_0);
	TOP_Rd01(dco_stcc_mon32, stcc_real_32, real_32);
	TOP_Rd01(dco_stcc_mon31_0, stcc_real_31_0, real_31_0);

	ref_31_0 = real_31_0 + 0x10;
	if (ref_31_0 < real_31_0) {	/* wrap around */
		ref_32 = (real_32) ? 0 : 1;
	} else {
		ref_32 = real_32;
	}

	TOP_Wr(dco_ref32, ref_32);
	TOP_Wr(dco_ref31_0, ref_31_0);
	TOP_WrFL(dco_ref32);
	TOP_WrFL(dco_ref31_0);
}

static int set_legacy_fcw(u32 freq, u32 input_clock)
{
	unsigned long flag;
	u32 val;

	val = freq_to_fcw(freq, input_clock);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_Wr(dco_fcw_ctrl, val);
	TOP_WrFL(dco_fcw_ctrl);

	write_stc_references();

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

static void get_pll_dco(u32 freq, u32 clock, u32 *divint, u32 *din)
{
//TODO: check constant value
#define DCO_PLL_REF 1
#define DCO_PLL_OUTDIV 60
#define DCO_PLL_COEF 16777216 /* 2^24 */
	u64 v, v2;
	u32 mclock = clock / (1000 * 1000); //Mhz

	v = (u64)freq * 2 * (DCO_PLL_REF * DCO_PLL_OUTDIV);
	do_div(v, mclock);
	v2 = v;

	do_div(v, (1000 * 1000));
	*divint = (u32)v;

	v2 = (v2 - (v * 1000 * 1000)) * DCO_PLL_COEF;
	do_div(v2, (1000 * 1000));

	*din = (u32)v2;
}


int TE_REG_SetDcoFcw(u32 freq, u32 input_clock)
{
	unsigned long flag;
	u32 divint, din;

	TRACE_ENTER("freq=%u", freq);

	if (top_cfg->dco_type == DCO_TYPE_NONE) {
		log_warning("DCO removed; freq:%u base:%u", freq, input_clock);
		return -ENODEV;
	} else if (top_cfg->dco_type == DCO_TYPE_LEGACY) {
		return set_legacy_fcw(freq, input_clock);
	}

	get_pll_dco(freq, input_clock, &divint, &din);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_Wr(dco_divint_ctrl, divint);
	TOP_WrFL(dco_divint_ctrl);

	TOP_Wr(dco_fcw_ctrl, din);
	TOP_WrFL(dco_fcw_ctrl);

	write_stc_references();

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_SetUartMux(u32 val)
{
	unsigned long flag;

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(uart);
	TOP_Wr01(uart, uart_sel, val);
	TOP_WrFL(uart);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_SetEngineChannelSource(u8 ch, enum te_reg_channel_src src)
{
	unsigned long flag;
	u32 v;

	CHECK_PARAM(ch >= top_cfg->num_engine_ch, "invalid ch(%d)", ch);

	TRACE_ENTER("ch=%d,src=%d", ch, src);

	if (top_cfg->version < 2) {
		return 0;	//ignore channel setting
	}

	v = get_engine_source_idx(src);
	CHECK_PARAM(v == INVALID_INDEX, "invalid src(%d)\n", src);

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(engine_chan_sel);
	switch (ch) {
	case 0:
		TOP_Wr01(engine_chan_sel, ch0_sel, v);
		break;
	case 1:
		TOP_Wr01(engine_chan_sel, ch1_sel, v);
		break;
	case 2:
		TOP_Wr01(engine_chan_sel, ch2_sel, v);
		break;
	case 3:
		TOP_Wr01(engine_chan_sel, ch3_sel, v);
		break;
	default:
		break;
	}
	TOP_WrFL(engine_chan_sel);

	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int TE_REG_GetEngineChannelSource(u8 ch, enum te_reg_channel_src *src)
{
	unsigned long flag;
	u8 idx;

	CHECK_PARAM(ch >= top_cfg->num_engine_ch, "invalid ch(%d)", ch);

	TRACE_EXIT("ch=%d,*src=%d", ch, *src);

	if (top_cfg->version < 2) {
		*src = CH_SRC_LGDEMOD;	/* only for m16+ */

		return 0;
	}

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(engine_chan_sel);
	switch (ch) {
	case 0:
		TOP_Rd01(engine_chan_sel, ch0_sel, idx);
		break;
	case 1:
		TOP_Rd01(engine_chan_sel, ch1_sel, idx);
		break;
	case 2:
		TOP_Rd01(engine_chan_sel, ch2_sel, idx);
		break;
	case 3:
		TOP_Rd01(engine_chan_sel, ch3_sel, idx);
		break;
	default:
		idx = 0xFF;
		break;
	}

	spin_unlock_irqrestore(&top_reg_lock, flag);

	*src = get_engine_source_from_idx(idx);

	TRACE_EXIT("ch=%d,*src=%d", ch, *src);

	return 0;
}

int TE_REG_SetEngineMode(enum te_reg_engine_mode mode)
{
	unsigned long flag;

	CHECK_PARAM(mode >= ENGINE_MODE_MAX, "invalid mode(%d)", mode);

	TRACE_ENTER("mode=%d", mode);

	if (top_cfg->version < 3) {
		return 0;	//not support engine mode
	}

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(engine_sel);
	switch (mode) {
	case ENGINE_MODE_ATSC3:
		TOP_Wr01(engine_sel, engine_sel, 0);
		break;
	case ENGINE_MODE_ARIB2:
		TOP_Wr01(engine_sel, engine_sel, 1);
		break;
	default:
		break;
	}
	TOP_WrFL(engine_sel);

	spin_unlock_irqrestore(&top_reg_lock, flag);
	return 0;
}

int TE_REG_GetEngineMode(enum te_reg_engine_mode *mode)
{
	unsigned long flag;
	u32 val;

	if (top_cfg->version < 3) {
		*mode = ENGINE_MODE_ATSC3;
		return 0;
	}

	spin_lock_irqsave(&top_reg_lock, flag);
	TOP_RdFL(engine_sel);
	TOP_Rd01(engine_sel, engine_sel, val);
	*mode = (val == 1) ? ENGINE_MODE_ARIB2 : ENGINE_MODE_ATSC3;
	spin_unlock_irqrestore(&top_reg_lock, flag);

	TRACE_EXIT("*mode=%d", *mode);

	return 0;
}

int te_reg_set_ci_input(enum te_reg_ci_input src)
{
	unsigned long flag;
	u32 v;

	if (top_cfg->version < 4) {
		return -EPERM;
	}

	TRACE_ENTER("src=%d", src);

	switch (src) {
	case CI_INPUT_SRC_TE:
		v = 0;
		break;
	case CI_INPUT_SRC_IN_DEMOD:
		v = 1;
		break;
	case CI_INPUT_SRC_EXT_INPUT0:
		v = 2;
		break;
	case CI_INPUT_SRC_EXT_INPUT1:
		v = 3;
		break;
	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&top_reg_lock, flag);
	TOP_RdFL(tp_iomux_sel);
	TOP_Wr01(tp_iomux_sel, tpo_outmux_sel, v);
	TOP_WrFL(tp_iomux_sel);
	spin_unlock_irqrestore(&top_reg_lock, flag);

	return 0;
}

int te_reg_get_ci_input(enum te_reg_ci_input *src)
{
	unsigned long flag;
	u8 val;

	if (top_cfg->version < 4) {
		return -EPERM;
	}

	spin_lock_irqsave(&top_reg_lock, flag);

	TOP_RdFL(tp_iomux_sel);
	TOP_Rd01(tp_iomux_sel, tpo_outmux_sel, val);

	switch (val) {
	case 0:
		*src = CI_INPUT_SRC_TE;
		break;
	case 1:
		*src = CI_INPUT_SRC_IN_DEMOD;
		break;
	case 2:
		*src = CI_INPUT_SRC_EXT_INPUT0;
		break;
	case 3:
		*src = CI_INPUT_SRC_EXT_INPUT1;
		break;
	default:
		*src = CI_INPUT_SRC_NONE;
		break;
	}

	spin_unlock_irqrestore(&top_reg_lock, flag);

	TRACE_EXIT("*src=%d", *src);
	return 0;
}

/* string functions */
static const struct te_val_str channel_src_str[] = {
	{CH_SRC_DISABLE, "DISABLE"},
	{CH_SRC_TPI_INT_DEMOD, "IN_DEMOD0"},
	{CH_SRC_TPI_EXT_DEMOD0, "EXT_DEMOD0"},
	{CH_SRC_TPI_EXT_DEMOD1, "EXT_DEMOD1"},
	{CH_SRC_TPI_EXT_DEMOD2, "EXT_DEMOD2"},
	{CH_SRC_TPI_CAM_LOOP_BACK, "CAM_LOOPBACK"},
	{CH_SRC_TPI_CAM_INPUT, "CAM_INPUT"},
	{CH_SRC_UPLOAD0, "UPLOAD0"},
	{CH_SRC_UPLOAD1, "UPLOAD1"},
	{CH_SRC_CIP_DEMUX0, "CIP_DEMUX0"},
	{CH_SRC_CIP_DEMUX1, "CIP_DEMUX1"},
	{CH_SRC_CIP_DEMUX2, "CIP_DEMUX2"},
	{CH_SRC_AUDIO_PES0, "AUD_PES0"},
	{CH_SRC_AUDIO_PES1, "AUD_PES1"},
	{CH_SRC_VIDEO_PES0, "VID_PES0"},
	{CH_SRC_VIDEO_PES1, "VID_PES1"},
};

const char *te_reg_channel_src_to_str(enum te_reg_channel_src src)
{
	return find_match_string(channel_src_str, src, "Invalid");
}
