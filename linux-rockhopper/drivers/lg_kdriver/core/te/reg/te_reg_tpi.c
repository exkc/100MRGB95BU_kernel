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

#define CHECK_TPI_IDX(idx,tpi)	\
  CHECK_PARAM((idx) < 0, "invalid tpi(%d)\n", tpi)

#define CHECK_CIP_INPUT_IDX(idx) \
  CHECK_PARAM((idx) >= tpi_reg_cfg->num_cip_input, "invalid port(%d)\n", idx)

#define TRACE_ENTER(fmt,args...)					\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_TPI_MASK)) {		\
		log_noti("@TPI_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_EXIT(fmt,args...)						\
do { 									\
	if (unlikely(g_te_reg_log_mask & REG_LOG_TPI_MASK)) {		\
		log_noti("~TPI_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_ENTER(fmt,args...)				\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_TPI_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("@TPI_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

#define TRACE_VERBOSE_EXIT(fmt,args...)					\
do { 									\
	if (unlikely((g_te_reg_log_mask & REG_LOG_TPI_MASK) &&	\
		     (g_te_reg_log_mask & REG_LOG_VERBOSE_MASK))) {	\
		log_noti("~TPI_REG : %s(" fmt ")", __func__, ##args);	\
	}								\
} while(0)

typedef struct {
	u8 version;
	u8 num_cip_input;
	u8 num_tpi;
	const struct te_type_conv *tpi_list;
} TPI_REG_CFG_T;

static const struct te_type_conv tpi_list_normal[] = {
	{TPI_INT_DEMOD, 0},
	{TPI_EXT_DEMOD0, 1},
	{TPI_EXT_DEMOD1, 2},
	{TPI_CAM_LOOP_BACK, 3},
	{TPI_CAM_INPUT, 4},
	{TPI_DISABLE, 5},
};

/* > M16P3 */
static const TPI_REG_CFG_T tpi_cfg_normal = {
	.version = 1,		//Add stream_type
	.num_cip_input = 3,

	.num_tpi = ARRAY_SIZE(tpi_list_normal),
	.tpi_list = tpi_list_normal,
};

/* O18, M16++ */
static const TPI_REG_CFG_T tpi_cfg_o18 = {
	.version = 0,
	.num_cip_input = 3,

	.num_tpi = ARRAY_SIZE(tpi_list_normal),
	.tpi_list = tpi_list_normal,
};

static const TPI_REG_CFG_T *tpi_reg_cfg;

static DEFINE_SPINLOCK(tpi_reg_lock);

int TE_REG_TPI_Init(void)
{
	switch (lx_chip()) {
	case LX_CHIP_O18:
		tpi_reg_cfg = &tpi_cfg_o18;
		break;
	default: // M16P3 ~
		tpi_reg_cfg = &tpi_cfg_normal;
		break;
	}

	return 0;
}

static int get_tpi_idx(enum te_reg_tpi_port tpi)
{
	const struct te_type_conv *l = tpi_reg_cfg->tpi_list;
	u32 n = tpi_reg_cfg->num_tpi;

	return te_convert_to_type1(l, n, tpi, -1);
}

static int get_ciinput_tpi_idx(enum te_reg_tpi_port tpi)
{
	if (tpi != TPI_CAM_INPUT &&
	    tpi != TPI_CAM_LOOP_BACK && tpi != TPI_DISABLE) {
		return -1;
	}

	return get_tpi_idx(tpi);
}

static enum te_reg_tpi_port get_tpi_from_idx(u8 idx)
{
	const struct te_type_conv *l = tpi_reg_cfg->tpi_list;
	u32 n = tpi_reg_cfg->num_tpi;

	return te_convert_to_type0(l, n, idx, TPI_DISABLE);
}

static void set_tpi_legacy(int idx, struct te_reg_tpi_conf *conf)
{
	u32 v;

	TPI_RdFL(tpi_conf[idx]);

	switch (conf->s2p_sync_mode) {	//s2p only
	case TPI_SYNC_SYNCBYTE:
		v = 0;
		break;
	case TPI_SYNC_SOP:
		v = 1;
		break;
	case TPI_SYNC_SOP_FIRSTBIT:
		v = 2;
		break;
	case TPI_SYNC_VALIDONLY:
	default:
		v = 3;
		break;
	}
	TPI_Wr01(tpi_conf[idx], stp_synctype, v);

	v = (conf->input_mode == TPI_CONF_INPUT_SERIAL) ? 1 : 0;
	TPI_Wr01(tpi_conf[idx], is_serial, v);
	TPI_Wr01(tpi_conf[idx], tpi_en, (conf->enable) ? 1 : 0);

	TPI_WrFL(tpi_conf[idx]);

	/* SetInputPortSync */
	switch (conf->sync_mode) {
	case TPI_SYNC_SOP:
		v = 0;
		break;
	case TPI_SYNC_SYNCBYTE:
		v = 1;
		break;
	case TPI_SYNC_VALIDONLY:
		v = 2;
		break;
	case TPI_SYNC_SOP_SYNCBYTE:
		v = 3;
		break;
	default:
		v = 0;
		break;		/* SOP */
	}

	TPI_RdFL(tpi_port[idx].sync);
	TPI_Wr01(tpi_port[idx].sync, synctype, v);
	TPI_Wr01(tpi_port[idx].sync, num_drop, conf->num_drop);
	TPI_Wr01(tpi_port[idx].sync, num_found, conf->num_found);
	TPI_WrFL(tpi_port[idx].sync);

	/* Reset Input Port */
	TPI_RdFL(tpi_port[idx].sync);
	TPI_Wr01(tpi_port[idx].sync, swreset, 0x1);
	TPI_WrFL(tpi_port[idx].sync);

	/* SetInputPortTeiConf */
	TPI_RdFL(tpi_port[idx].tei);
	TPI_Wr01(tpi_port[idx].tei, tei_enable, 0);	//Turn Off and On (MPEG2 TS)
	TPI_WrFL(tpi_port[idx].tei);

	if (conf->stream_type == TPI_CONF_STREAM_TS) {
		TPI_Wr01(tpi_port[idx].tei, tei_enable, 1);
		TPI_WrFL(tpi_port[idx].tei);
	}
}

static void set_tpi(int idx, struct te_reg_tpi_conf *conf)
{
	u32 v;

	TPI_RdFL(tpi_conf[idx]);
	TPI_RdFL(tpi_port[idx].sync);	//use tpi_sync for parallel and reet

	TPI_Wr01(tpi_conf[idx], tpi_en, 0);	//Disable First
	TPI_Wr01(tpi_port[idx].sync, swreset, 1);	// Reset Sync

	v = (conf->input_mode == TPI_CONF_INPUT_SERIAL) ? 1 : 0;
	TPI_Wr01(tpi_conf[idx], is_serial, v);

	/* Stream Type & Sync Type */
	switch (conf->stream_type) {
	case TPI_CONF_STREAM_TS:
	case TPI_CONF_STREAM_ATSC3:
		TPI_Wr01(tpi_conf[idx], stream_type, 0);
		TPI_Wr01(tpi_port[idx].sync, bypass_sync, 0);
		if (conf->input_mode == TPI_CONF_INPUT_SERIAL) {
			switch (conf->s2p_sync_mode) {	//s2p only
			case TPI_SYNC_SYNCBYTE:
				v = 0;
				break;
			case TPI_SYNC_SOP:
				v = 1;
				break;
			case TPI_SYNC_SOP_FIRSTBIT:
				v = 2;
				break;
			default:
				v = 2;
				break;
			}
			TPI_Wr01(tpi_conf[idx], stp_synctype, v);
		} else {
			switch (conf->sync_mode) {	//parallel sync
			case TPI_SYNC_SOP:
				v = 0;
				break;
			case TPI_SYNC_VALIDONLY:
				v = 2;
				break;
			case TPI_SYNC_SOP_SYNCBYTE:
				v = 3;
				break;
			case TPI_SYNC_SYNCBYTE:
			default:
				v = 1;
				break;
			}
			TPI_Wr01(tpi_port[idx].sync, synctype, v);
		}

		TPI_Wr01(tpi_port[idx].sync, zero_len_flt_en, 0);
		TPI_Wr01(tpi_port[idx].sync, null_type_flt_en, 0);
		break;

	case TPI_CONF_STREAM_ARIB2:
		TPI_Wr01(tpi_conf[idx], stream_type, 1);
		TPI_Wr01(tpi_port[idx].sync, bypass_sync, 0);
		v = (conf->input_mode == TPI_CONF_INPUT_SERIAL) ?
		    conf->s2p_sync_mode : conf->sync_mode;
		switch (v) {
		case TPI_SYNC_SOP:
			v = 0;
			break;
		case TPI_SYNC_MAGIC:
			v = 1;
			break;
		case TPI_SYNC_SOP_MAGIC:
			v = 2;
			break;
		default:
			v = 0;
			break;
		}

		TPI_Wr01(tpi_conf[idx], tlv_synctype, v);
		TPI_Wr01(tpi_port[idx].sync, zero_len_flt_en, 1);
		TPI_Wr01(tpi_port[idx].sync, null_type_flt_en, 0);
		break;

	case TPI_CONF_STREAM_BYPASS:
		TPI_Wr01(tpi_port[idx].sync, bypass_sync, 1);
		if (conf->input_mode == TPI_CONF_INPUT_SERIAL) {
			switch (conf->s2p_sync_mode) {
			case TPI_SYNC_VALIDONLY:
				v = 0;
				break;
			case TPI_SYNC_SOP:
				v = 1;
				break;
			case TPI_SYNC_MAGIC:
				v = 2;
				break;
			case TPI_SYNC_SOP_MAGIC:
				v = 3;
				break;
			default:
				v = 0;
				break;
			}
			TPI_Wr01(tpi_conf[idx], bp_synctype, v);
		}
		break;

	default:
		break;
	}

	TPI_Wr01(tpi_port[idx].sync, num_drop, conf->num_drop);
	TPI_Wr01(tpi_port[idx].sync, num_found, conf->num_found);

	/* Setting Adjust and Reset */
	TPI_WrFL(tpi_conf[idx]);
	TPI_WrFL(tpi_port[idx].sync);

	/* Reenable */
	if (conf->enable) {
		TPI_RdFL(tpi_conf[idx]);
		TPI_Wr01(tpi_conf[idx], tpi_en, 1);
		TPI_WrFL(tpi_conf[idx]);
	}

	/* SetInputPortTeiConf */
	TPI_RdFL(tpi_port[idx].tei);
	TPI_Wr01(tpi_port[idx].tei, tei_enable, 0);	//Turn Off and On (MPEG2 TS)
	TPI_WrFL(tpi_port[idx].tei);

	if (conf->stream_type == TPI_CONF_STREAM_TS) {
		TPI_Wr01(tpi_port[idx].tei, tei_enable, 1);
		TPI_WrFL(tpi_port[idx].tei);
	}

}

int TE_REG_SetTpiConf(enum te_reg_tpi_port port, struct te_reg_tpi_conf *conf)
{
	unsigned long flag;
	int idx;

	idx = get_tpi_idx(port);
	CHECK_TPI_IDX(idx, port);
	CHECK_PARAM(conf->stream_type > TPI_CONF_STREAM_BYPASS,
		    "invalid stream_type[%d]", conf->stream_type);

	TRACE_ENTER("idx=%d,en=%d,stream=%d,input_mode=%d,"
		    "sync_mode=%d,found=%d,drop=%d",
		    idx, conf->enable, conf->stream_type, conf->input_mode,
		    conf->sync_mode, conf->num_found, conf->num_drop);

	/* Num Drop & Found */
	if (conf->num_drop > 3)
		conf->num_drop = 3;
	if (conf->num_found > 3)
		conf->num_found = 3;

	spin_lock_irqsave(&tpi_reg_lock, flag);

	if (tpi_reg_cfg->version >= 1) {	//M16P3 ~
		set_tpi(idx, conf);
	} else {		// LEGACY
		set_tpi_legacy(idx, conf);
	}

	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	return 0;
}

int TE_REG_SetTpiEnable(enum te_reg_tpi_port port, bool en)
{
	unsigned long flag;
	int idx;

	idx = get_tpi_idx(port);
	CHECK_TPI_IDX(idx, port);

	TRACE_ENTER("enable=%d", en);

	spin_lock_irqsave(&tpi_reg_lock, flag);

	TPI_RdFL(tpi_conf[idx]);
	TPI_Wr01(tpi_conf[idx], tpi_en, (en) ? 1 : 0);
	TPI_WrFL(tpi_conf[idx]);

	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	return 0;
}

static void get_tpi_status_legacy(int idx, struct te_reg_tpi_status *s)
{
	u32 v;

	s->stream_type = TPI_CONF_STREAM_TS;

	TPI_Rd01(tpi_conf[idx], stp_synctype, v);
	switch (v) {
	case 0:
		s->s2p_mode = TPI_SYNC_SYNCBYTE;
		break;
	case 1:
		s->s2p_mode = TPI_SYNC_SOP;
		break;
	case 2:
		s->s2p_mode = TPI_SYNC_SOP_FIRSTBIT;
		break;
	case 3:
	default:
		s->s2p_mode = TPI_SYNC_VALIDONLY;
		break;
	}

	TPI_Rd01(tpi_port[idx].sync, synctype, v);
	switch (v) {
	case 0:
		s->sync_type = TPI_SYNC_SOP;
		break;
	case 1:
		s->sync_type = TPI_SYNC_SYNCBYTE;
		break;
	case 2:
		s->sync_type = TPI_SYNC_VALIDONLY;
		break;
	case 3:
	default:
		s->sync_type = TPI_SYNC_SOP_SYNCBYTE;
		break;
	}

	TPI_Rd01(tpi_port[idx].mon, sync_drop_mon, s->sync_drop);
}

static void get_tpi_status(int idx, struct te_reg_tpi_status *s)
{
	u32 v;

	TPI_Rd01(tpi_port[idx].sync, bypass_sync, v);
	if (v) {		/* bypass mode */
		s->stream_type = TPI_CONF_STREAM_BYPASS;
		s->sync_type = TPI_SYNC_BYPASS;
		TPI_Rd01(tpi_conf[idx], bp_synctype, v);
		switch (v) {
		case 0:
			s->s2p_mode = TPI_SYNC_VALIDONLY;
			break;
		case 1:
			s->s2p_mode = TPI_SYNC_SOP;
			break;
		case 2:
			s->s2p_mode = TPI_SYNC_MAGIC;
			break;
		case 3:
			s->s2p_mode = TPI_SYNC_SOP_MAGIC;
			break;
		default:
			s->s2p_mode = TPI_SYNC_VALIDONLY;
			break;
		}
		s->sync_drop = 0;	//always zero

		return;
	}

	TPI_Rd01(tpi_conf[idx], stream_type, v);
	s->stream_type = (v) ? TPI_CONF_STREAM_ARIB2 : TPI_CONF_STREAM_TS;

	if (s->stream_type == TPI_CONF_STREAM_ARIB2) {
		TPI_Rd01(tpi_conf[idx], tlv_synctype, v);
		switch (v) {
		case 0:
			s->sync_type = TPI_SYNC_SOP;
			break;
		case 1:
			s->sync_type = TPI_SYNC_MAGIC;
			break;
		case 2:
			s->sync_type = TPI_SYNC_SOP_MAGIC;
			break;
		default:
			s->sync_type = TPI_SYNC_SOP;
			break;
		}

		if (s->input_mode == TPI_CONF_INPUT_SERIAL) {
			TPI_Rd01(tpi_port[idx].mon, stlv_drop, s->sync_drop);
		} else {
			TPI_Rd01(tpi_port[idx].mon, tlv_drop, s->sync_drop);
		}
	} else {
		if (s->input_mode == TPI_CONF_INPUT_SERIAL) {
			TPI_Rd01(tpi_conf[idx], stp_synctype, v);
			switch (v) {
			case 0:
				s->sync_type = TPI_SYNC_SYNCBYTE;
				break;
			case 1:
				s->sync_type = TPI_SYNC_SOP;
				break;
			case 2:
				s->sync_type = TPI_SYNC_SOP_FIRSTBIT;
				break;
			default:
				s->sync_type = TPI_SYNC_SYNCBYTE;
				break;
			}

			TPI_Rd01(tpi_port[idx].mon, s_sync_drop_mon,
				 s->sync_drop);
		} else {
			TPI_Rd01(tpi_port[idx].sync, synctype, v);
			switch (v) {
			case 0:
				s->sync_type = TPI_SYNC_SOP;
				break;
			case 1:
				s->sync_type = TPI_SYNC_SYNCBYTE;
				break;
			case 2:
				s->sync_type = TPI_SYNC_VALIDONLY;
				break;
			case 3:
			default:
				s->sync_type = TPI_SYNC_SOP_SYNCBYTE;
				break;
			}

			TPI_Rd01(tpi_port[idx].mon, sync_drop_mon,
				 s->sync_drop);
		}
	}
	s->s2p_mode = s->sync_type;	/* only one sync module */
}

int TE_REG_GetTpiStatus(enum te_reg_tpi_port port,
			struct te_reg_tpi_status *status)
{
	u32 v;
	unsigned long flag;
	int idx;

	idx = get_tpi_idx(port);
	CHECK_TPI_IDX(idx, port);

	spin_lock_irqsave(&tpi_reg_lock, flag);

	/* CAUTION : fifo full & sync drop field is auto cleared after read access */
	TPI_RdFL(tpi_conf[idx]);
	TPI_RdFL(tpi_port[idx].sync);
	TPI_RdFL(tpi_port[idx].mon);
	TPI_RdFL(tpi_port[idx].tei);
	TPI_RdFL(tpi_port[idx].packet);

	TPI_Rd(tpi_conf[idx], status->reg_value[0]);
	TPI_Rd(tpi_port[idx].sync, status->reg_value[1]);
	TPI_Rd(tpi_port[idx].mon, status->reg_value[2]);

	TPI_Rd01(tpi_conf[idx], tpi_en, v);
	status->enable = v;

	TPI_Rd01(tpi_conf[idx], is_serial, v);
	status->input_mode =
	    (v) ? TPI_CONF_INPUT_SERIAL : TPI_CONF_INPUT_PARALLEL;

	TPI_Rd01(tpi_conf[idx], fifo_full, v);
	status->fifo_full = (v) ? true : false;

	if (tpi_reg_cfg->version > 0) {	/* M16P3 ~ */
		get_tpi_status(idx, status);
	} else {
		get_tpi_status_legacy(idx, status);
	}

	TPI_Rd01(tpi_port[idx].sync, num_found, status->num_of_sync_found);
	TPI_Rd01(tpi_port[idx].sync, num_drop, status->num_of_sync_drop);

	TPI_Rd01(tpi_port[idx].packet, sync_tp_counter, status->pkt_count);

	TPI_Rd01(tpi_port[idx].tei, tei_cnt, status->tei_count);
	TPI_Rd01(tpi_port[idx].tei, tei_enable, status->tei_enable);

	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	TRACE_EXIT("idx=%d,en=%d,input_mode=%d,sync_type=%d",
		   idx, status->enable, status->input_mode, status->sync_type);

	return 0;
}

int TE_REG_SetCiplusInput(u8 idx, enum te_reg_tpi_port port)
{
	int tpi_idx;
	unsigned long flag;

	CHECK_CIP_INPUT_IDX(idx);

	TRACE_ENTER("idx=%d,port=%d", idx, port);

	tpi_idx = get_tpi_idx(port);
	CHECK_TPI_IDX(tpi_idx, port);

	spin_lock_irqsave(&tpi_reg_lock, flag);
	TPI_RdFL(cip_sel[idx]);
	TPI_Wr01(cip_sel[idx], tpi, tpi_idx);
	TPI_WrFL(cip_sel[idx]);
	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	return 0;
}

int TE_REG_GetCiplusInput(u8 idx, enum te_reg_tpi_port *port)
{
	u8 tpi_idx;
	unsigned long flag;

	CHECK_CIP_INPUT_IDX(idx);

	spin_lock_irqsave(&tpi_reg_lock, flag);
	TPI_RdFL(cip_sel[idx]);
	TPI_Rd01(cip_sel[idx], tpi, tpi_idx);
	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	*port = get_tpi_from_idx(tpi_idx);

	TRACE_EXIT("idx=%d,*tpi=%d", idx, *port);

	return 0;
}

int TE_REG_SetCiInputTpi(enum te_reg_tpi_port port)
{
	int tpi_idx;
	unsigned long flag;

	tpi_idx = get_ciinput_tpi_idx(port);
	CHECK_TPI_IDX(tpi_idx, port);

	spin_lock_irqsave(&tpi_reg_lock, flag);
	TPI_RdFL(cin_sel);
	TPI_Wr01(cin_sel, tpi, tpi_idx);
	TPI_WrFL(cin_sel);
	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	return 0;
}

int TE_REG_GetCiInputTpi(enum te_reg_tpi_port *port)
{
	u8 tpi_idx;
	unsigned long flag;

	spin_lock_irqsave(&tpi_reg_lock, flag);
	TPI_RdFL(cin_sel);
	TPI_Rd01(cin_sel, tpi, tpi_idx);
	spin_unlock_irqrestore(&tpi_reg_lock, flag);

	*port = get_tpi_from_idx(tpi_idx);

	TRACE_EXIT("*tpi=%d", *port);

	return 0;
}
