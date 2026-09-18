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
 *  TE I/O driver
 *
 *  @author	Ilkyu Kim
 *  @version	1.1
 *  @date	2025-07-25
 *  @note	Additional information.
 */

#include "te_impl.h"
#include <lg1k/te/ion.h>
#include <lg1k/te/ci.h>

#define INPUT_MONITOR_INTERVAL		500	/* msec */
#define INPUT_LOG_INTERVAL		10000	/* msec */

static DEFINE_MUTEX(io_mutex);

static unsigned int te_monitor_log_cnt = 10;
module_param(te_monitor_log_cnt, uint, 0644);

static unsigned int te_ciout_tei_warn_threshold = 2;
module_param(te_ciout_tei_warn_threshold, uint, 0644);

static unsigned int te_ciout_tei_err_limit = 6; // 6 * INTERVAL = 3 secs
module_param(te_ciout_tei_err_limit, uint, 0644);

static unsigned int te_ciout_nopkt_warn_threshold = 10;
module_param(te_ciout_nopkt_warn_threshold, uint, 0644);

static unsigned int te_ciout_nopkt_err_limit = 16; // 16 * INTERVAL = 8 secs
module_param(te_ciout_nopkt_err_limit, uint, 0644);

/* type conversion */
/* preset structure (add list for HW separation) */

enum te_io_conv_type {
	CONV_TYPE_SRC_TO_REG_TPI = 0,
	CONV_TYPE_SRC_TO_REG_CI,
	CONV_TYPE_PORT_TO_REG_TPI,
	CONV_TYPE_PORT_TO_REG_CH_SRC,
	MAX_IO_CONV_TYPE
};

struct te_io_conv {
	u32 num;
	const struct te_type_conv *conv;
};

#define __IO_CONV(a) { ARRAY_SIZE(a), a}

static const struct te_io_conv *conv_cfg;

/* LX_TE_INPUT_SRC_T <=> enum te_reg_tpi_port */
static const struct te_type_conv type_input_src_and_reg_tpi_normal[] = {
	{LX_TE_INPUT_SRC_IN_DEMOD0, TPI_INT_DEMOD},
	{LX_TE_INPUT_SRC_EXT_INPUT0, TPI_EXT_DEMOD0},
	{LX_TE_INPUT_SRC_EXT_INPUT1, TPI_EXT_DEMOD1},
	{LX_TE_INPUT_SRC_EXT_INPUT2, TPI_CAM_INPUT},
	{LX_TE_INPUT_SRC_CI_INPUT, TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_SRC_CI_OUTPUT, TPI_CAM_INPUT},
	{LX_TE_INPUT_SRC_NONE, TPI_DISABLE},
};

static const struct te_type_conv type_input_src_and_reg_tpi_swapped[] = {
	{LX_TE_INPUT_SRC_IN_DEMOD0, TPI_INT_DEMOD},
	{LX_TE_INPUT_SRC_EXT_INPUT0, TPI_EXT_DEMOD1},
	{LX_TE_INPUT_SRC_EXT_INPUT1, TPI_EXT_DEMOD0},
	{LX_TE_INPUT_SRC_EXT_INPUT2, TPI_CAM_INPUT},
	{LX_TE_INPUT_SRC_CI_INPUT, TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_SRC_CI_OUTPUT, TPI_CAM_INPUT},
	{LX_TE_INPUT_SRC_NONE, TPI_DISABLE},
};

enum te_reg_tpi_port te_input_src_to_reg_tpi_port(LX_TE_INPUT_SRC_T src)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_SRC_TO_REG_TPI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type1(l, n, src, TPI_INVALID);
}

LX_TE_INPUT_SRC_T te_reg_tpi_port_to_input_src(enum te_reg_tpi_port port)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_SRC_TO_REG_TPI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type0(l, n, port, LX_TE_INPUT_SRC_NONE);
}

/* LX_TE_INPUT_SRC_T <=> enum te_reg_ci_input */
static const struct te_type_conv type_input_src_and_reg_ci_normal[] = {
	{LX_TE_INPUT_SRC_IN_DEMOD0, CI_INPUT_SRC_IN_DEMOD},
	{LX_TE_INPUT_SRC_EXT_INPUT0, CI_INPUT_SRC_EXT_INPUT0},
	{LX_TE_INPUT_SRC_EXT_INPUT1, CI_INPUT_SRC_EXT_INPUT1},
	{LX_TE_INPUT_SRC_TE, CI_INPUT_SRC_TE},
	{LX_TE_INPUT_SRC_NONE, CI_INPUT_SRC_NONE},
};

static const struct te_type_conv type_input_src_and_reg_ci_swapped[] = {
	{LX_TE_INPUT_SRC_IN_DEMOD0, CI_INPUT_SRC_IN_DEMOD},
	{LX_TE_INPUT_SRC_EXT_INPUT0, CI_INPUT_SRC_EXT_INPUT1},
	{LX_TE_INPUT_SRC_EXT_INPUT1, CI_INPUT_SRC_EXT_INPUT0},
	{LX_TE_INPUT_SRC_TE, CI_INPUT_SRC_TE},
	{LX_TE_INPUT_SRC_NONE, CI_INPUT_SRC_NONE},
};

enum te_reg_ci_input te_input_src_to_reg_ci_input(LX_TE_INPUT_SRC_T src)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_SRC_TO_REG_CI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type1(l, n, src, CI_INPUT_SRC_INVALID);
}

LX_TE_INPUT_SRC_T te_reg_ci_input_to_input_src(enum te_reg_ci_input input)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_SRC_TO_REG_CI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type0(l, n, input, LX_TE_INPUT_SRC_NONE);
}

/* LX_TE_INPUT_PORT_T <=> enum te_reg_tpi_port */
static const struct te_type_conv type_input_port_and_reg_tpi_normal[] = {
	{LX_TE_INPUT_PORT_TPI_IN_DEMOD0, TPI_INT_DEMOD},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT0, TPI_EXT_DEMOD0},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT1, TPI_EXT_DEMOD1},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT2, TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_TPI_CI_INPUT, TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_PORT_TPI_CI_OUTPUT, TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_NONE, TPI_DISABLE},
};

static const struct te_type_conv type_input_port_and_reg_tpi_swapped[] = {
	{LX_TE_INPUT_PORT_TPI_IN_DEMOD0, TPI_INT_DEMOD},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT0, TPI_EXT_DEMOD1},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT1, TPI_EXT_DEMOD0},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT2, TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_TPI_CI_INPUT, TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_PORT_TPI_CI_OUTPUT, TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_NONE, TPI_DISABLE},
};

enum te_reg_tpi_port te_input_port_to_reg_tpi_port(LX_TE_INPUT_PORT_T port)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_PORT_TO_REG_TPI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type1(l, n, port, TPI_INVALID);
}

LX_TE_INPUT_PORT_T te_reg_tpi_port_to_input_port(enum te_reg_tpi_port port)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_PORT_TO_REG_TPI];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type0(l, n, port, LX_TE_INPUT_PORT_INVALID);
}

/* LX_TE_INPUT_PORT_T <=> enum te_reg_channel_src */
static const struct te_type_conv type_input_port_and_reg_ch_src_normal[] = {
	{LX_TE_INPUT_PORT_TPI_IN_DEMOD0, CH_SRC_TPI_INT_DEMOD},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT0, CH_SRC_TPI_EXT_DEMOD0},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT1, CH_SRC_TPI_EXT_DEMOD1},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT2, CH_SRC_TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_TPI_CI_INPUT, CH_SRC_TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_PORT_TPI_CI_OUTPUT, CH_SRC_TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_DVR0, CH_SRC_UPLOAD0},
	{LX_TE_INPUT_PORT_DVR1, CH_SRC_UPLOAD1},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX0, CH_SRC_CIP_DEMUX0},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX1, CH_SRC_CIP_DEMUX1},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX2, CH_SRC_CIP_DEMUX2},
	{LX_TE_INPUT_PORT_AUDIO0, CH_SRC_AUDIO_PES0},
	{LX_TE_INPUT_PORT_AUDIO1, CH_SRC_AUDIO_PES1},
	{LX_TE_INPUT_PORT_VIDEO0, CH_SRC_VIDEO_PES0},
	{LX_TE_INPUT_PORT_VIDEO1, CH_SRC_VIDEO_PES1},
	{LX_TE_INPUT_PORT_NONE, CH_SRC_DISABLE},
};

static const struct te_type_conv type_input_port_and_reg_ch_src_swapped[] = {
	{LX_TE_INPUT_PORT_TPI_IN_DEMOD0, CH_SRC_TPI_INT_DEMOD},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT0, CH_SRC_TPI_EXT_DEMOD1},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT1, CH_SRC_TPI_EXT_DEMOD0},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT2, CH_SRC_TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_TPI_CI_INPUT, CH_SRC_TPI_CAM_LOOP_BACK},
	{LX_TE_INPUT_PORT_TPI_CI_OUTPUT, CH_SRC_TPI_CAM_INPUT},
	{LX_TE_INPUT_PORT_DVR0, CH_SRC_UPLOAD0},
	{LX_TE_INPUT_PORT_DVR1, CH_SRC_UPLOAD1},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX0, CH_SRC_CIP_DEMUX0},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX1, CH_SRC_CIP_DEMUX1},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX2, CH_SRC_CIP_DEMUX2},
	{LX_TE_INPUT_PORT_AUDIO0, CH_SRC_AUDIO_PES0},
	{LX_TE_INPUT_PORT_AUDIO1, CH_SRC_AUDIO_PES1},
	{LX_TE_INPUT_PORT_VIDEO0, CH_SRC_VIDEO_PES0},
	{LX_TE_INPUT_PORT_VIDEO1, CH_SRC_VIDEO_PES1},
	{LX_TE_INPUT_PORT_NONE, CH_SRC_DISABLE},
};

enum te_reg_channel_src te_input_port_to_reg_ch_src(LX_TE_INPUT_PORT_T port)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_PORT_TO_REG_CH_SRC];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type1(l, n, port, CH_SRC_INVALID);
}

LX_TE_INPUT_PORT_T te_reg_ch_src_to_input_port(enum te_reg_channel_src src)
{
	const struct te_io_conv *cfg = &conv_cfg[CONV_TYPE_PORT_TO_REG_CH_SRC];
	const struct te_type_conv *l = cfg->conv;
	u32 n = cfg->num;

	return te_convert_to_type0(l, n, src, LX_TE_INPUT_PORT_INVALID);
}

/* LX_TE_SYNC_TYPE_T <=> enum te_reg_tpi_sync */
static const struct te_type_conv type_sync_type_and_reg_tpi_sync_normal[] = {
	{LX_TE_SYNC_SYNC_BYTE, TPI_SYNC_SYNCBYTE},
	{LX_TE_SYNC_SOP, TPI_SYNC_SOP},
	{LX_TE_SYNC_SOP_FIRSTBIT, TPI_SYNC_SOP_FIRSTBIT},
	{LX_TE_SYNC_VALIDONLY, TPI_SYNC_VALIDONLY},
	{LX_TE_SYNC_SOP_SYNCBYTE, TPI_SYNC_SOP_SYNCBYTE},
	{LX_TE_SYNC_MAGIC, TPI_SYNC_MAGIC},
	{LX_TE_SYNC_SOP_MAGIC, TPI_SYNC_SOP_MAGIC},
	{LX_TE_SYNC_BYPASS, TPI_SYNC_BYPASS},
};

enum te_reg_tpi_sync te_sync_type_to_reg_tpi_sync(LX_TE_SYNC_TYPE_T type)
{
	const struct te_type_conv *l = type_sync_type_and_reg_tpi_sync_normal;
	u32 n = ARRAY_SIZE(type_sync_type_and_reg_tpi_sync_normal);

	return te_convert_to_type1(l, n, type, TPI_SYNC_BYPASS);
}

LX_TE_SYNC_TYPE_T te_reg_tpi_sync_to_sync_type(enum te_reg_tpi_sync sync)
{
	const struct te_type_conv *l = type_sync_type_and_reg_tpi_sync_normal;
	u32 n = ARRAY_SIZE(type_sync_type_and_reg_tpi_sync_normal);

	return te_convert_to_type0(l, n, sync, LX_TE_SYNC_BYPASS);
}

/* type <=> string conversion functions */

static const struct te_val_str input_src_str_normal[] = {
	{LX_TE_INPUT_SRC_NONE, "None"},
	{LX_TE_INPUT_SRC_IN_DEMOD0, "IN_DEMOD0"},
	{LX_TE_INPUT_SRC_EXT_INPUT0, "EXT_INPUT0"},
	{LX_TE_INPUT_SRC_EXT_INPUT1, "EXT_INPUT1"},
	{LX_TE_INPUT_SRC_EXT_INPUT2, "EXT_INPUT2"},
	{LX_TE_INPUT_SRC_CI_INPUT, "CI_INPUT"},
	{LX_TE_INPUT_SRC_CI_OUTPUT, "CI_OUTPUT"},
	{LX_TE_INPUT_SRC_TE, "TE"},
	{LX_TE_INPUT_SRC_IP0, "IP0"},
	{LX_TE_INPUT_SRC_IP1, "IP1"},
};

const char *te_input_source_to_str(LX_TE_INPUT_SRC_T src)
{
	const struct te_val_str *l = input_src_str_normal;
	u32 n = ARRAY_SIZE(input_src_str_normal);

	return te_find_match_string(l, n, src, "Invalid");
}

LX_TE_INPUT_SRC_T te_str_to_input_source(const char *str)
{
	const struct te_val_str *l = input_src_str_normal;
	u32 n = ARRAY_SIZE(input_src_str_normal);

	return te_find_match_value(l, n, str, LX_TE_INPUT_SRC_NONE);
}

static const struct te_val_str input_mode_str_normal[] = {
	{LX_TE_IO_MODE_NONE, "None"},
	{LX_TE_IO_MODE_SERIAL, "Serial"},
	{LX_TE_IO_MODE_PARALLEL, "Parallel"},
};

const char *te_input_mode_to_str(LX_TE_INPUT_MODE_T mode)
{
	const struct te_val_str *l = input_mode_str_normal;
	u32 n = ARRAY_SIZE(input_mode_str_normal);

	return te_find_match_string(l, n, mode, "Invalid");
}

LX_TE_INPUT_MODE_T te_str_to_input_mode(const char *str)
{
	const struct te_val_str *l = input_mode_str_normal;
	u32 n = ARRAY_SIZE(input_mode_str_normal);

	return te_find_match_value(l, n, str, LX_TE_IO_MODE_MAX);
}

static const struct te_val_str input_port_str_normal[] = {
	{LX_TE_INPUT_PORT_NONE, "None"},
	{LX_TE_INPUT_PORT_TPI_IN_DEMOD0, "IN_DEMOD0"},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT0, "EXT_INPUT0"},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT1, "EXT_INPUT1"},
	{LX_TE_INPUT_PORT_TPI_EXT_INPUT2, "EXT_INPUT2"},
	{LX_TE_INPUT_PORT_TPI_CI_INPUT, "CI_INPUT"},
	{LX_TE_INPUT_PORT_TPI_CI_OUTPUT, "CI_OUTPUT"},
	{LX_TE_INPUT_PORT_DVR0, "DVR0"},
	{LX_TE_INPUT_PORT_DVR1, "DVR1"},
	{LX_TE_INPUT_PORT_CI, "CI"},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX0, "CIPLUS_DEMUX0"},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX1, "CIPLUS_DEMUX1"},
	{LX_TE_INPUT_PORT_CIPLUS_DEMUX2, "CIPLUS_DEMXU2"},
	{LX_TE_INPUT_PORT_CIPLUS_IN0, "CIPLUS_IN0"},
	{LX_TE_INPUT_PORT_CIPLUS_IN1, "CIPLUS_IN1"},
	{LX_TE_INPUT_PORT_CIPLUS_IN2, "CIPLUS_IN2"},
	{LX_TE_INPUT_PORT_AUDIO0, "AUDIO0"},
	{LX_TE_INPUT_PORT_AUDIO1, "AUDIO1"},
	{LX_TE_INPUT_PORT_VIDEO0, "VIDEO0"},
	{LX_TE_INPUT_PORT_VIDEO1, "VIDEO1"},
	{LX_TE_INPUT_PORT_BYPASS, "BYPASS"},
};

const char *te_input_port_to_str(LX_TE_INPUT_PORT_T port)
{
	const struct te_val_str *l = input_port_str_normal;
	u32 n = ARRAY_SIZE(input_port_str_normal);

	return te_find_match_string(l, n, port, "Invalid");
}

LX_TE_INPUT_PORT_T te_str_to_input_port(const char *str)
{
	const struct te_val_str *l = input_port_str_normal;
	u32 n = ARRAY_SIZE(input_port_str_normal);

	return te_find_match_value(l, n, str, LX_TE_INPUT_PORT_INVALID);
}

static const struct te_val_str reg_tpi_port_str_normal[] = {
	{TPI_INT_DEMOD, "IN_DEMOD0"},
	{TPI_EXT_DEMOD0, "EXT_INPUT0"},
	{TPI_EXT_DEMOD1, "EXT_INPUT1"},
	{TPI_EXT_DEMOD2, "EXT_INPUT2"},
	{TPI_CAM_LOOP_BACK, "CI_INPUT"},
	{TPI_CAM_INPUT, "CI_OUTPUT"},
	{TPI_DISABLE, "DISABLE"},
	{TPI_INVALID, "INVALID"},
};

const char *te_reg_tpi_port_to_str(enum te_reg_tpi_port port)
{
	const struct te_val_str *l = reg_tpi_port_str_normal;
	u32 n = ARRAY_SIZE(reg_tpi_port_str_normal);

	return te_find_match_string(l, n, port, "Invalid");
}

static const struct te_val_str stream_type_str_normal[] = {
	{LX_TE_STREAM_UNKNOWN, "None"},
	{LX_TE_STREAM_MPEG2TS, "TS"},
	{LX_TE_STREAM_ATSC3, "ATSC3"},
	{LX_TE_STREAM_ARIB2, "ARIB2"},
	{LX_TE_STREAM_BYPASS, "BYPASS"},
};

const char *te_stream_type_to_str(LX_TE_STREAM_TYPE_T type)
{
	const struct te_val_str *l = stream_type_str_normal;
	u32 n = ARRAY_SIZE(stream_type_str_normal);

	return te_find_match_string(l, n, type, "Invalid");
}

LX_TE_STREAM_TYPE_T te_str_to_stream_type(const char *str)
{
	const struct te_val_str *l = stream_type_str_normal;
	u32 n = ARRAY_SIZE(stream_type_str_normal);

	return te_find_match_value(l, n, str, LX_TE_STREAM_MAX);
}

static const struct te_val_str sync_type_str_normal[] = {
	{LX_TE_SYNC_SYNCBYTE, "SYNCBYTE"},
	{LX_TE_SYNC_SOP, "SOP"},
	{LX_TE_SYNC_SOP_FIRSTBIT, "SOP_FIRSTBIT"},
	{LX_TE_SYNC_VALIDONLY, "VALID"},
	{LX_TE_SYNC_SOP_SYNCBYTE, "SOP_SYNCBYTE"},
	{LX_TE_SYNC_MAGIC, "MAGIC"},
	{LX_TE_SYNC_SOP_MAGIC, "SOP_MAGIC"},
	{LX_TE_SYNC_BYPASS, "BYPASS"},
};

const char *te_sync_type_to_str(LX_TE_SYNC_TYPE_T type)
{
	const struct te_val_str *l = sync_type_str_normal;
	u32 n = ARRAY_SIZE(sync_type_str_normal);

	return te_find_match_string(l, n, type, "Invalid");
}

LX_TE_SYNC_TYPE_T te_str_to_sync_type(const char *str)
{
	const struct te_val_str *l = sync_type_str_normal;
	u32 n = ARRAY_SIZE(sync_type_str_normal);

	return te_find_match_value(l, n, str, LX_TE_SYNC_MAX);
}

static const struct te_val_str sync_type_short_str_normal[] = {
	{LX_TE_SYNC_SYNCBYTE, "SBYTE"},
	{LX_TE_SYNC_SOP, "SOP"},
	{LX_TE_SYNC_SOP_FIRSTBIT, "SOP1B"},
	{LX_TE_SYNC_VALIDONLY, "VALID"},
	{LX_TE_SYNC_SOP_SYNCBYTE, "SOP&B"},
	{LX_TE_SYNC_MAGIC, "MAGIC"},
	{LX_TE_SYNC_SOP_MAGIC, "SOP&M"},
	{LX_TE_SYNC_BYPASS, "BPASS"},
};

const char *te_sync_type_to_short_str(LX_TE_SYNC_TYPE_T type)
{
	const struct te_val_str *l = sync_type_short_str_normal;
	u32 n = ARRAY_SIZE(sync_type_short_str_normal);

	return te_find_match_string(l, n, type, "INV");
}

static const struct te_val_str ci_src_type_list_normal[] = {
	{CI_INPUT_SRC_NONE, "NONE"},
	{CI_INPUT_SRC_IN_DEMOD, "IN_DEMOD0"},
	{CI_INPUT_SRC_EXT_INPUT0, "EXT_INPUT0"},
	{CI_INPUT_SRC_EXT_INPUT1, "EXT_INPUT1"},
	{CI_INPUT_SRC_TE, "TE"},
	{CI_INPUT_SRC_INVALID, "INVALID"},
};

const char *te_ci_src_type_to_str(enum te_reg_ci_input src)
{
	const struct te_val_str *l = ci_src_type_list_normal;
	u32 n = ARRAY_SIZE(ci_src_type_list_normal);

	return te_find_match_string(l, n, src, "INVALID");
}

static const struct te_val_str ch_src_type_list_normal[] = {
	{CH_SRC_DISABLE, "DISABLE"},
	{CH_SRC_TPI_INT_DEMOD, "IN_DEMOD0"},
	{CH_SRC_TPI_EXT_DEMOD0, "EXT_INPUT0"},
	{CH_SRC_TPI_EXT_DEMOD1, "EXT_INPUT1"},
	{CH_SRC_TPI_EXT_DEMOD2, "EXT_INPUT2"},
	{CH_SRC_TPI_CAM_LOOP_BACK, "CI_INPUT"},
	{CH_SRC_TPI_CAM_INPUT, "CI_OUTPUT"},
	{CH_SRC_UPLOAD0, "UPLOAD0"},
	{CH_SRC_UPLOAD1, "UPLOAD1"},
	{CH_SRC_CIP_DEMUX0, "CIP_DEMUX0"},
	{CH_SRC_CIP_DEMUX1, "CIP_DEMUX1"},
	{CH_SRC_CIP_DEMUX2, "CIP_DEMUX2"},
	{CH_SRC_AUDIO_PES0, "ADEC0"},
	{CH_SRC_AUDIO_PES1, "ADEC1"},
	{CH_SRC_VIDEO_PES0, "VDEC0"},
	{CH_SRC_VIDEO_PES1, "VDEC1"},
	{CH_SRC_LGDEMOD, "LGDEMOD"},
	{CH_SRC_INVALID, "INVALID"},
};

const char *te_ch_src_type_to_str(enum te_reg_channel_src src)
{
	const struct te_val_str *l = ch_src_type_list_normal;
	u32 n = ARRAY_SIZE(ch_src_type_list_normal);

	return te_find_match_string(l, n, src, "INVALID");
}

static const struct te_io_conv te_io_conv_cfg_normal[MAX_IO_CONV_TYPE] = {
	[CONV_TYPE_SRC_TO_REG_TPI] =
		__IO_CONV(type_input_src_and_reg_tpi_normal),
	[CONV_TYPE_SRC_TO_REG_CI] =
		__IO_CONV(type_input_src_and_reg_ci_normal),
	[CONV_TYPE_PORT_TO_REG_TPI] =
		__IO_CONV(type_input_port_and_reg_tpi_normal),
	[CONV_TYPE_PORT_TO_REG_CH_SRC] =
		__IO_CONV(type_input_port_and_reg_ch_src_normal)
};

static const struct te_io_conv te_io_conv_cfg_swapped[MAX_IO_CONV_TYPE] = {
	[CONV_TYPE_SRC_TO_REG_TPI] =
		__IO_CONV(type_input_src_and_reg_tpi_swapped),
	[CONV_TYPE_SRC_TO_REG_CI] =
		__IO_CONV(type_input_src_and_reg_ci_swapped),
	[CONV_TYPE_PORT_TO_REG_TPI] =
		__IO_CONV(type_input_port_and_reg_tpi_swapped),
	[CONV_TYPE_PORT_TO_REG_CH_SRC] =
		__IO_CONV(type_input_port_and_reg_ch_src_swapped)
};

/************ end of helper functions *********************/

static struct te_dev_tpi *get_dev_tpi(struct te_device *dev,
				      enum te_reg_tpi_port port)
{
	if (port < MAX_TPI_PORT_NUM) {
		return &dev->tpi[port];
	}

	return NULL;
}

static int get_tpi_status(struct te_device *dev, enum te_reg_tpi_port port,
			  struct lx_te_tpi_status *status)
{
	int ret;
	struct te_dev_tpi *tpi;
	struct te_reg_tpi_status s;

	tpi = get_dev_tpi(dev, port);
	CHECK_PARAM(!tpi, "Not valid TPI(0x%x)", port);

	ret = TE_REG_GetTpiStatus(tpi->port, &s);
	CHECK_ERROR(ret, return ret, "Error in TE_REG_GetTpiStatus");

	if (s.stream_type == TPI_CONF_STREAM_ARIB2)
		status->stream_type = LX_TE_STREAM_ARIB2;
	else
		status->stream_type = tpi->cfg.stream_type;

	status->mode = (s.input_mode == TPI_CONF_INPUT_SERIAL) ?
			LX_TE_INPUT_MODE_SERIAL : LX_TE_INPUT_MODE_PARALLEL;

	status->sync_type = te_reg_tpi_sync_to_sync_type(s.sync_type);
	status->s2p_sync_type = te_reg_tpi_sync_to_sync_type(s.s2p_mode);

	status->enable = s.enable;
	status->sync_drop = s.sync_drop;
	status->num_of_sync_found = s.num_of_sync_found;
	status->num_of_sync_drop = s.num_of_sync_drop;
	status->pkt_count = s.pkt_count;
	status->tei_count = s.tei_count;

	status->reg_value[0] = s.reg_value[0];
	status->reg_value[1] = s.reg_value[1];
	status->reg_value[2] = s.reg_value[2];

	status->time = (u32)te_get_ms_tick();

	return 0;
}

static void check_input_packet(struct te_tpi_monitor *m,
			       struct lx_te_tpi_status *s)
{
	bool is_error;
	u32 elapsed;

#define log_packet(fmt, args...) \
	log_noti("%s(%s) - " fmt, m->name, \
		 te_stream_type_to_str(s->stream_type), ##args)

	if (m->pkt_count == s->pkt_count) {
		elapsed = jiffies_to_msecs(jiffies - m->warn_time);

		log_debug("DEBUG: %d", m->first_check);
		if (!m->first_check || !m->no_input_count ||
		    elapsed >= INPUT_LOG_INTERVAL) {
			log_packet("no input packet #%u(pkt:%u)",
				   m->no_input_count, m->pkt_count);

			m->no_input_count++;
			m->warn_time = jiffies;
		}

		if (!m->first_check)
			m->first_check = true;

		return;
	}

	is_error = false;

	if (m->no_input_count || !m->first_check) {
		log_debug("DEBUG: %d", m->first_check);

		log_packet("recover input packet(%u)", m->no_input_count);

		m->no_input_count = 0;
		m->input_msg_count = 0;
		m->first_check = true;
	}

	/* Sync Drop Monitor */
	if (s->sync_drop) {
		if (m->input_msg_count < te_monitor_log_cnt) {
			log_packet("sync drop detected");
		}
		is_error = true;
	}

	/* Packet Error Monitor (MPEG2TS Only) */
	if (s->stream_type == LX_TE_STREAM_MPEG2TS &&
	    m->tei_count != s->tei_count) {
		if (m->input_msg_count < te_monitor_log_cnt) {
			log_packet("pkt:%u(%u/%u) tei:%u(%u/%u)",
				   s->pkt_count - m->pkt_count,
				   m->pkt_count, s->pkt_count,
				   s->tei_count - m->tei_count,
				   m->tei_count, s->tei_count);
		}
		is_error = true;
	}

	/* Print out input status priodically */
	elapsed = jiffies_to_msecs(jiffies - m->print_time);
	if (elapsed >= INPUT_LOG_INTERVAL) {
		if (s->stream_type == LX_TE_STREAM_MPEG2TS) {
			log_packet("(NORMAL)pkt:%u(%u/%u) tei:%u(%u/%u)",
				   s->pkt_count - m->pkt_count,
				   m->pkt_count, s->pkt_count,
				   s->tei_count - m->tei_count,
				   m->tei_count, s->tei_count);

		} else {
			log_packet("(NORMAL)pkt:%u(%u/%u)",
				   s->pkt_count - m->pkt_count,
				   m->pkt_count, s->pkt_count);
		}
		m->print_time = jiffies;
	}

	/* Control verbose message */
	if (is_error) {
		if (m->input_msg_count < te_monitor_log_cnt) {
			m->input_msg_count++;
			if (m->input_msg_count == te_monitor_log_cnt) {
				log_packet("disable packet monitor message");
			}
		}
	} else {
		if (m->input_msg_count > 0) {
			if (m->input_msg_count == te_monitor_log_cnt) {
				log_packet("reenable packet monitor message");
				m->input_msg_count = 0;
			} else {
				m->input_msg_count--;
			}
		}
	}
}

static void check_input_status(struct te_tpi_monitor *m,
			       struct lx_te_tpi_status *status)
{
	log_debug("(DEBUG)%s ready[%d] cnt[%d] sync_drop[%d] no_input_cnt[%d]",
		  m->name, m->ready, status->pkt_count, status->sync_drop,
		  m->no_input_count);

	if (m->ready) {
		check_input_packet(m, status);
	} else {
		m->ready = true;	/* change to ready status after getting status */
		m->first_check = false;
		m->no_input_count = 0;
		m->input_msg_count = 0;
		m->warn_time = 0;
		m->print_time = 0;
	}

	m->pkt_count = status->pkt_count;
	m->tei_count = status->tei_count;
}

enum te_ion_tpi {
	ION_TPI_CAMIN = 0,
	ION_TPI_CAMOUT
};

static void get_ci_ion_pkt_status(struct te_dev_ion *ion,
				  struct te_tpi_monitor *monitor,
				  struct lx_te_tpi_status *status,
				  enum te_ion_tpi name)
{
	struct te_dev_ion_pkt_monitor *s;

	s = (name == ION_TPI_CAMIN) ? &ion->ci_in : &ion->ci_out;
	s->pkt_incr = 0;
	s->tei_incr = 0;
	s->ready = monitor->ready;

	if (!monitor->ready)
		return;

	s->pkt_incr = status->pkt_count - monitor->pkt_count;
	s->tei_incr = status->tei_count - monitor->tei_count;
}

static void reset_ci_ion_check_cnt(struct te_dev_ion *ion)
{
	ion->tei_abnormal_cnt = 0;
	ion->no_packet_cnt = 0;
}

static void check_tei_abnormal(struct te_device *dev, struct te_dev_ion *ion)
{
	struct te_dev_ion_pkt_monitor *in, *out;
	int rc;

	in = &ion->ci_in;
	out = &ion->ci_out;

	if (in->tei_incr < out->tei_incr) { // error detection case (out tei)
		ion->tei_abnormal_cnt++;
	} else {
		ion->tei_abnormal_cnt = 0;
	}

	if (te_ciout_tei_warn_threshold &&
	    ion->tei_abnormal_cnt >= te_ciout_tei_warn_threshold) {
		log_warning("tei abnormal count:%u", ion->tei_abnormal_cnt);

	}

	if (te_ciout_tei_err_limit &&
	    ion->tei_abnormal_cnt >= te_ciout_tei_err_limit) {
		log_error("try to reset ion1!");
		rc = ion_ci_reset_tp(dev);
		if (rc)
			log_error("error in ion_ci_reset_tp %d", rc);

		reset_ci_ion_check_cnt(ion);
	}
}

static void check_pkt_abnormal(struct te_device *dev, struct te_dev_ion *ion)
{
	struct ci_device *ci_dev = ci_get_device(dev);
	struct te_dev_ion_pkt_monitor *out;
	enum cam_ready_status s;
	int rc;

	out = &ion->ci_out;

	if (!ci_dev)
		return;
	if (!out->ready || out->pkt_incr) { // normal operation; nothing to do
		ion->no_packet_cnt = 0;
		return;
	}

	ci_get_slot_status(ci_dev, &s);

	if (s == CAM_READY_SUCCESS) {
		ion->no_packet_cnt++;
	} else {
		ion->no_packet_cnt = 0;
	}

	if (te_ciout_nopkt_warn_threshold &&
	    ion->no_packet_cnt >= te_ciout_nopkt_warn_threshold) {
		log_warning("no_packet abnormal count:%u", ion->no_packet_cnt);

	}

	if (te_ciout_nopkt_err_limit &&
	    ion->no_packet_cnt >= te_ciout_nopkt_err_limit) {
		log_error("try to reset ion1!");
		rc = ion_ci_reset_tp(dev);
		if (rc)
			log_error("error in ion_ci_reset_tp %d", rc);

		reset_ci_ion_check_cnt(ion);
	}
}

static void check_ci_ion_healthy(struct te_device *dev)
{
	struct te_dev_ion *ion = &dev->ion;
	struct te_dev_ion_pkt_monitor *in, *out;

	in = &ion->ci_in;
	out = &ion->ci_out;

	log_debug("in pkt:%u tei:%u / out pkt:%u tei:%u", in->pkt_incr,
		  in->tei_incr, out->pkt_incr, out->tei_incr);

	if (!in->pkt_incr) { //no input from source (skip)
		reset_ci_ion_check_cnt(ion);
		return;
	}

	/* No Packet Abnormal Detection */
	check_pkt_abnormal(dev, ion);

	if (!out->pkt_incr)
		return;

	/* TEI Abnormal Detection */
	check_tei_abnormal(dev, ion);
}

static void input_monitor(void *arg)
{
	int i, rc;
	struct te_device *dev = arg;
	struct te_tpi_monitor *m;
	struct lx_te_tpi_status status;
	struct te_config *te_cfg = te_get_config();
	struct te_dev_tpi *tpi;

	mutex_lock(&io_mutex);

	/* TPI */
	for (i = 0; i < MAX_TPI_NUM; i++) {
		tpi = &dev->tpi[i];
		m = &tpi->monitor;

		if (!m->enable)
			continue;

		rc = get_tpi_status(dev, i, &status);
		if (rc)
			continue;

		if (te_cfg->use_ion && dev->ci_src_tpi) {
			if (dev->ci_src_tpi == tpi) {
				get_ci_ion_pkt_status(&dev->ion, m, &status,
						      ION_TPI_CAMIN);
			} else if (tpi->port == TPI_CAM_INPUT) {
				get_ci_ion_pkt_status(&dev->ion, m, &status,
						      ION_TPI_CAMOUT);
			}
		}

		check_input_status(m, &status);
	}

	if (te_cfg->use_ion && dev->ci_src_tpi)
		check_ci_ion_healthy(dev);

	mutex_unlock(&io_mutex);
}

static int control_input_monitor(struct te_tpi_monitor *m, bool en)
{
	if (m) {
		m->enable = en;
		m->ready = false;
	}

	return 0;
}

static int init_input_monitor(struct te_device *dev)
{
	struct te_timer *timer;

	timer = te_add_timer(dev, INPUT_MONITOR_INTERVAL, input_monitor, dev);
	CHECK_ERROR(!timer, return -EIO, "Error in te_add_timer");

	dev->tpi_timer = timer;

	return 0;
}

int te_get_tpi_status(struct te_device *dev, LX_TE_INPUT_PORT_T port,
		      LX_TE_TPI_STATUS_T *status)
{
	int rc;
	enum te_reg_tpi_port tpi_port;

	tpi_port = te_input_port_to_reg_tpi_port(port);
	CHECK_PARAM(tpi_port == TPI_INVALID, "Not valid port(0x%x)", port);

	mutex_lock(&io_mutex);
	rc = get_tpi_status(dev, tpi_port, status);
	mutex_unlock(&io_mutex);

	return rc;
}

static int config_ion_io(struct te_device *dev, enum te_reg_tpi_port port,
			 enum te_reg_tpi_type stream_type,
			 enum te_reg_tpi_mode input_mode)
{
	u8 ext_num;
	bool parallel = false;
	int rc;

	// only cares two ext tpis (0/1)
	if (port != TPI_EXT_DEMOD0 && port != TPI_EXT_DEMOD1)
		return 0;

	ext_num = (port == TPI_EXT_DEMOD0) ? 0 : 1;
	if (input_mode == TPI_CONF_INPUT_PARALLEL)
		parallel = true;

	switch (stream_type) {
	case TPI_CONF_STREAM_ARIB2:
		rc = ion_io_set_tlv(dev, ext_num, parallel);
		break;
	case TPI_CONF_STREAM_ATSC3:
		rc = ion_io_set_lgc(dev, ext_num, parallel);
		break;
	case TPI_CONF_STREAM_TS:
	default:
		rc = ion_io_set_tp(dev, ext_num, parallel);
		break;
	}

	if (rc) {
		log_error("set ion conf [%d] failed %d", stream_type, rc);
		return rc;
	}

	return 0;
}

static int config_tpi(struct te_device *dev, enum te_reg_tpi_port port,
		      LX_TE_TPI_CFG_T *param)
{
	struct te_reg_tpi_conf conf;
	struct te_dev_tpi *tpi;
	struct te_config *te_cfg = te_get_config();
	int ret;

	log_noti("%s(%s,%s,%s,%s)\n", __func__,
		 te_reg_tpi_port_to_str(port),
		 te_stream_type_to_str(param->stream_type),
		 te_input_mode_to_str(param->mode),
		 (param->mode == LX_TE_IO_MODE_PARALLEL) ?
		 te_sync_type_to_str(param->sync_type) :
		 te_sync_type_to_str(param->s2p_sync_type));

	tpi = get_dev_tpi(dev, port);
	CHECK_PARAM(!tpi, "Not valid TPI(%d)", port);

	if (tpi->cfg.stream_type == param->stream_type &&
	    tpi->cfg.mode == param->mode &&
	    tpi->cfg.sync_type == param->sync_type &&
	    tpi->cfg.s2p_sync_type == param->s2p_sync_type &&
	    tpi->cfg.num_of_sync_drop == param->num_of_sync_drop &&
	    tpi->cfg.num_of_sync_found == param->num_of_sync_found)
		return 0;

	conf.enable = (param->mode == LX_TE_IO_MODE_NONE) ? false : true;
	conf.input_mode = (param->mode == LX_TE_IO_MODE_SERIAL) ?
	    TPI_CONF_INPUT_SERIAL : TPI_CONF_INPUT_PARALLEL;

	switch (param->stream_type) {
	case LX_TE_STREAM_ARIB2:
		conf.stream_type = TPI_CONF_STREAM_ARIB2;
		break;
	case LX_TE_STREAM_ATSC3:
		conf.stream_type = TPI_CONF_STREAM_ATSC3;
		break;
	case LX_TE_STREAM_BYPASS:
		conf.stream_type = TPI_CONF_STREAM_BYPASS;
		break;
	case LX_TE_STREAM_MPEG2TS:
	default:
		conf.stream_type = TPI_CONF_STREAM_TS;
		break;
	}

	conf.sync_mode = te_sync_type_to_reg_tpi_sync(param->sync_type);
	conf.s2p_sync_mode = te_sync_type_to_reg_tpi_sync(param->s2p_sync_type);

	conf.num_drop = param->num_of_sync_drop;
	conf.num_found = param->num_of_sync_found;

	if (te_cfg->use_ion) {
		ret = config_ion_io(dev, port, conf.stream_type,
				    conf.input_mode);
		if (ret)
			log_error("config_ion_io failed %d", ret);
	}

	ret = TE_REG_SetTpiConf(tpi->port, &conf);
	CHECK_ERROR(ret, return ret, "Error in TE_REG_SetTpiConf");

	tpi->cfg = *param;	/* save current parameters */

	control_input_monitor(&tpi->monitor, conf.enable);

	return 1;		/* RESET */
}

static int set_ciplus_input(struct te_device *dev, u8 idx,
			    enum te_reg_tpi_port port)
{
	int ret;

	CHECK_PARAM(idx >= MAX_CIPLUS_INPUT_PORT_NUM, "invalid idx(%d)", idx);

	if (dev->ciplus_input[idx] != port) {
		ret = TE_REG_SetCiplusInput(idx, port);
		CHECK_ERROR(ret != 0, return ret,
			    "Error in TE_REG_SetCIPInputTPI");

		dev->ciplus_input[idx] = port;
	}

	return 0;
}

static int set_ci_input(struct te_device *dev, u8 idx,
			enum te_reg_tpi_port port)
{
	int ret;

	CHECK_PARAM(idx != 0, "invalid idx(%d)", idx);

	if (dev->ci_input != port) {
		ret = TE_REG_SetCiInputTpi(port);
		CHECK_ERROR(ret != 0, return ret,
			    "Error in TE_REG_SetCIInputTPI");

		dev->ci_input = port;
	}

	return 0;
}

/**
 * te_config_tpi - Configure the TPI port with parameters
 *
 * Return: 1 if the tpi was configured as a new value and the caller will
 * have to reset the channel input, 0 on success without changes, else
 * negative value on error.
 */
int te_config_tpi(struct te_device *dev, enum lx_te_input_port port,
		  struct lx_te_tpi_cfg *param)
{
	int ret;
	enum te_reg_tpi_port tpi_port;

	tpi_port = te_input_port_to_reg_tpi_port(port);
	CHECK_PARAM(tpi_port == TPI_INVALID, "Invalid input port(%s)",
		    te_input_port_to_str(port));

	mutex_lock(&io_mutex);
	ret = config_tpi(dev, tpi_port, param);
	mutex_unlock(&io_mutex);

	CHECK_ERROR(ret < 0, return ret, "Error in config_tpi");

	return ret;
}

int te_connect_input_port(struct te_device *dev, LX_TE_INPUT_PORT_T port,
			  LX_TE_INPUT_PORT_T src)
{
	int ret, idx;
	enum lx_te_input_port type;
	enum te_reg_tpi_port tpi_port;

	tpi_port = te_input_port_to_reg_tpi_port(src);
	CHECK_PARAM(tpi_port == TPI_INVALID, "Invalid input port(%s)",
		    te_input_port_to_str(src));

	type = te_get_input_port_type(port);

	mutex_lock(&io_mutex);
	if (type == LX_TE_INPUT_PORT_CI) {
		log_noti("%s(ci,%s)", __func__,
			 te_reg_tpi_port_to_str(tpi_port));
		idx = port - LX_TE_INPUT_PORT_CI;
		ret = set_ci_input(dev, idx, tpi_port);
	} else if (type == LX_TE_INPUT_PORT_CIPLUS_IN) {
		idx = port - LX_TE_INPUT_PORT_CIPLUS_IN0;
		log_noti("%s(cip%d,%s)", __func__, idx,
			 te_reg_tpi_port_to_str(tpi_port));
		ret = set_ciplus_input(dev, idx, tpi_port);
	} else {
		log_error("Can't connect port(%s) to port(%s)\n",
			  te_input_port_to_str(src),
			  te_input_port_to_str(port));
		ret = -EINVAL;
	}
	mutex_unlock(&io_mutex);

	return ret;
}

int te_set_engine_mode(struct te_device *dev, LX_TE_STREAM_TYPE_T stream_type)
{
	int ret;
	enum te_dumper_mode mode;

	if (stream_type == LX_TE_STREAM_ATSC3) {
		mode = TE_DUMPER_MODE_ATSC3;
	} else if (stream_type == LX_TE_STREAM_ARIB2) {
		mode = TE_DUMPER_MODE_ARIB2;
	} else if (stream_type == LX_TE_STREAM_MPEG2TS) {
		mode = TE_DUMPER_MODE_CI20;
	} else {
		log_error("Invalid stream_type[%d]", stream_type);
		return -EINVAL;
	}

	mutex_lock(&io_mutex);
	ret = te_dumper_set_mode(dev, mode);
	mutex_unlock(&io_mutex);

	return ret;
}

LX_TE_STREAM_TYPE_T te_get_engine_mode(struct te_device *dev)
{
	enum te_dumper_mode mode;
	LX_TE_STREAM_TYPE_T stream_type;

	mutex_lock(&io_mutex);
	mode = te_dumper_get_mode(dev);
	mutex_unlock(&io_mutex);

	switch (mode) {
	case TE_DUMPER_MODE_ARIB2:
		stream_type = LX_TE_STREAM_ARIB2;
		break;
	case TE_DUMPER_MODE_ATSC3:
		stream_type = LX_TE_STREAM_ATSC3;
		break;
	default:
		stream_type = LX_TE_STREAM_UNKNOWN;
		break;
	}

	return stream_type;
}

/**
 * te_notify_ci_src_port - Notify to TE_IO what TPI ci input source connected
 *
 * When the ioctl calls, it waits for wall clock from inputs for specific
 * timeouts, returns immediately when the clock is delivered
 *
 * dev: pointer for te_device
 * src: input source enum which connected to CICAM
 *
 * Returns: 0 if success, -EINVAL if the tpi is not valid
 */
int te_notify_ci_src_port(struct te_device *dev, enum lx_te_input_src src)
{
	enum te_reg_tpi_port port;
	struct te_dev_tpi *tpi;

	if (src == LX_TE_INPUT_SRC_TE) {
		tpi = NULL; // not connected
	} else {
		port = te_input_src_to_reg_tpi_port(src);
		tpi = get_dev_tpi(dev, port);
	}

	mutex_lock(&io_mutex);

	dev->ci_src_tpi = tpi;

	mutex_unlock(&io_mutex);

	return 0;
}

static void invalidate_tpi_cfg(LX_TE_TPI_CFG_T *cfg)
{
	cfg->stream_type = LX_TE_STREAM_UNKNOWN;
	cfg->mode = LX_TE_IO_MODE_NONE;
	cfg->sync_type = LX_TE_SYNC_MAX;
	cfg->s2p_sync_type = LX_TE_SYNC_MAX;
	cfg->num_of_sync_found = 0xff;
	cfg->num_of_sync_drop = 0xff;
}

static void init_hw(struct te_device *dev)
{
	int i;
	enum te_reg_tpi_port port;
	struct te_config *te_cfg = te_get_config();
	struct te_io_cfg *cfg = te_get_io_config();

	if (te_cfg->use_ion)
		ion_io_hw_init(dev);

	for (i = 0; i < cfg->num_tpi_input; i++) {
		port = te_input_port_to_reg_tpi_port(cfg->tpi_info[i]);

		TE_REG_SetTpiEnable(port, false);
	}

	for (i = 0; i < cfg->num_ciplus_input; i++) {
		TE_REG_SetCiplusInput(i, TPI_DISABLE);
	}

	/* Open CI_IN port as default */
	TE_REG_SetCiInputTpi(TPI_CAM_INPUT);
}

/*----------------------------------------------------------------------------------------
 *   Debug Functions
 *---------------------------------------------------------------------------------------*/

#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)

enum {
	DEBUG_INPUT_ID_STATUS = 0,
	DEBUG_INPUT_ID_CONFIG,
	DEBUG_INPUT_ID_ENGINE,
};

static u32 proc_input_mtime = 500;	/* ms unit - measuring time */

static int debug_set_input_config(struct te_device *dev, char *command)
{
	char *tok, *last_tok;
	const char *delim = ",\r\n";
	LX_TE_TPI_CFG_T cfg;
	LX_TE_INPUT_PORT_T port;

	port = LX_TE_INPUT_PORT_NONE;

	memset(&cfg, 0, sizeof(cfg));
	cfg.stream_type = LX_TE_STREAM_MPEG2TS;
	cfg.mode = LX_TE_INPUT_MODE_PARALLEL;

	/* default value depends on stream_type */
	cfg.sync_type = LX_TE_SYNC_MAX;
	cfg.num_of_sync_found = 0xFF;
	cfg.num_of_sync_drop = 0xFF;

	last_tok = command;
	while ((tok = strsep(&last_tok, delim))) {
		char *name, *value;

		name = tok;
		value = strchr(tok, '=');
		if (!value)
			return -EINVAL;
		*value++ = 0;

		if (!strcasecmp("port", name))
			port = te_str_to_input_port(value);
		else if (!strcasecmp("stream_type", name)) {
			cfg.stream_type = te_str_to_stream_type(value);
			if (cfg.stream_type == LX_TE_STREAM_MAX) {
				printk("invalid stream_type(%s)\n", value);
				return -EINVAL;
			}
		} else if (!strcasecmp("mode", name)) {
			cfg.mode = te_str_to_input_mode(value);
			if (cfg.mode == LX_TE_IO_MODE_MAX) {
				printk("invalid mode(%s)\n", name);
				return -EINVAL;
			}
		} else if (!strcasecmp("sync_type", name)) {
			cfg.sync_type = te_str_to_sync_type(value);
			cfg.s2p_sync_type = cfg.sync_type;
			if (cfg.sync_type == LX_TE_SYNC_MAX) {
				printk("invalid mode(%s)\n", name);
				return -EINVAL;
			}
		} else if (!strcasecmp("num_sync_found", name)) {
			cfg.num_of_sync_found =
			    simple_strtoul(value, (char **)NULL, 0);
		} else if (!strcasecmp("num_sync_drop", name)) {
			cfg.num_of_sync_drop =
			    simple_strtoul(value, (char **)NULL, 0);
		} else {
			printk("invalid param '%s'\n", name);
			return -EINVAL;
		}
	}

	if (te_get_input_port_type(port) != LX_TE_INPUT_PORT_TPI &&
	    port != LX_TE_INPUT_PORT_NONE) {
		printk("invalid TPI port(%s)\n", te_input_port_to_str(port));
		return -EINVAL;
	}

	/* set default value if not given */
	if (cfg.sync_type == LX_TE_SYNC_MAX) {
		cfg.sync_type = (cfg.stream_type == LX_TE_STREAM_MPEG2TS) ?
		    LX_TE_SYNC_SYNC_BYTE : LX_TE_SYNC_SOP;
	}

	if (cfg.num_of_sync_found == 0xFF) {
		cfg.num_of_sync_found =
		    (cfg.stream_type == LX_TE_STREAM_MPEG2TS) ? 3 : 0;
	}

	if (cfg.num_of_sync_drop == 0xFF) {
		cfg.num_of_sync_drop =
		    (cfg.stream_type == LX_TE_STREAM_MPEG2TS) ? 3 : 0;
	}

	return te_config_tpi(dev, port, &cfg);
}

static void debug_show_input_config(struct seq_file *m)
{
	int i;
	const char *s;
	struct te_io_cfg *cfg = te_get_io_config();
	const char *title_fmt = "%14s : ";

	dprintf(title_fmt, "*port");
	for (i = 0; i < cfg->num_tpi_input; i++) {
		s = te_input_port_to_str(cfg->tpi_info[i]);
		if (i == 0)
			dprintf("%s", s);
		else
			dprintf(", %s", s);
	}
	dprintf("\n");

	dprintf(title_fmt, "stream_type");
	for (i = 0; i < LX_TE_STREAM_MAX; i++) {
		s = te_stream_type_to_str(i);
		if (i)
			dprintf(", ");
		if (i == LX_TE_STREAM_MPEG2TS)
			dprintf("*");
		dprintf("%s", s);
	}
	dprintf("\n");

	dprintf(title_fmt, "mode");
	for (i = 0; i < LX_TE_IO_MODE_MAX; i++) {
		s = te_input_mode_to_str(i);
		if (i)
			dprintf(", ");
		if (i == LX_TE_IO_MODE_PARALLEL)
			dprintf("*");
		dprintf("%s", s);
	}
	dprintf("\n");

	dprintf(title_fmt, "sync_type");
	for (i = 0; i < LX_TE_SYNC_MAX; i++) {
		s = te_sync_type_to_str(i);
		if (i)
			dprintf(", ");
		dprintf("%s", s);
	}
	dprintf("\n");

	dprintf(title_fmt, "num_sync_found");
	dprintf("0 ~ 3\n");
	dprintf(title_fmt, "num_sync_drop");
	dprintf("0 ~ 3\n\n");

	dprintf
	    ("ex> echo port=in_demod0,stream_type=arib2,sync_type=sop > config\n");
}

/**
 * te_debug_get_tpi_status - Allocate memory and get status for all tpi
 *
 * It allocates memory for all tpi port and gets the current status.
 * And you must call @te_debug_free_tpi_status to free allocated memory
 *
 * Return: allocated @struct lx_te_tpi_status on success, or ERR_PTR on error
 */
struct lx_te_tpi_status *te_debug_get_tpi_status(struct te_device *dev)
{
	int i;
	struct te_io_cfg *cfg = te_get_io_config();
	struct lx_te_tpi_status *s;

	s = kcalloc(cfg->num_tpi_input, sizeof(*s), GFP_KERNEL);
	if (!s)
		return ERR_PTR(-ENOMEM);

	for (i = 0; i < cfg->num_tpi_input; i++) {
		te_get_tpi_status(dev, cfg->tpi_info[i], &s[i]);
	}

	return s;
}

/**
 * te_debug_show_tpi_status - Show tpi status throw @struct seq_file
 * @old: previous tpi status from @te_debug_get_tpi_status
 */
void te_debug_show_tpi_status(struct te_device *dev, struct seq_file *m,
			      struct lx_te_tpi_status *old)
{
	int i;
	struct lx_te_tpi_status s;
	enum lx_te_sync_type sync_type;
	char *rate;
	struct te_io_cfg *cfg = te_get_io_config();

	dprintf("%3s %12s %2s %6s %8s %5s %8s %17s %12s\n", "Num",
		"TPI", "En", "Type", "Mode", "Sync", "TEI", "Packet", "Speed");

	for (i = 0; i < cfg->num_tpi_input; i++) {
		te_get_tpi_status(dev, cfg->tpi_info[i], &s);
		sync_type = (s.mode == LX_TE_INPUT_MODE_SERIAL) ?
			    s.sync_type : s.s2p_sync_type;

		dprintf("[%d] %12s  %c %6s %8s %5s %08x ", i,
			te_input_port_to_str(cfg->tpi_info[i]),
			s.enable ? 'O' : 'X',
			te_stream_type_to_str(s.stream_type),
			te_input_mode_to_str(s.mode),
			te_sync_type_to_short_str(sync_type),
			s.tei_count);

		/* compare and print */
		if (s.stream_type == LX_TE_STREAM_ARIB2) {
			rate = "N/A";
		} else {
			u32 pkt_count = s.pkt_count - old[i].pkt_count;
			u32 elapsed = s.time - old[i].time;
			rate = get_bitrate_str(pkt_count, 188, elapsed);
		}
		dprintf("%08x/%08x %12s\n", old[i].pkt_count, s.pkt_count,
			rate);
	}
}

void te_debug_free_tpi_status(struct lx_te_tpi_status *status)
{
	kfree(status);
}

static int debug_show_input_status(struct te_device *dev, struct seq_file *m)
{
	struct lx_te_tpi_status *status;

	status = te_debug_get_tpi_status(dev);
	if (IS_ERR(status))
		return PTR_ERR(status);

	msleep(proc_input_mtime);

	te_debug_show_tpi_status(dev, m, status);

	te_debug_free_tpi_status(status);

	return 0;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	u32 val;
	struct te_device *dev = item->private;
	int ret = 0;

	switch (item->flags) {
	case DEBUG_INPUT_ID_STATUS:
		ret = debug_show_input_status(dev, m);
		break;

	case DEBUG_INPUT_ID_CONFIG:
		debug_show_input_config(m);
		break;

	case DEBUG_INPUT_ID_ENGINE:
		val = te_get_engine_mode(dev);
		dprintf("%s\n", te_stream_type_to_str(val));
		break;

	default:
		ret = -EPERM;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	u32 val;
	struct te_device *dev = item->private;
	int ret = 0;

	switch (item->flags) {
	case DEBUG_INPUT_ID_CONFIG:
		ret = debug_set_input_config(dev, str);
		break;

	case DEBUG_INPUT_ID_ENGINE:
		val = te_str_to_stream_type(str);
		if (val == LX_TE_STREAM_MAX)
			ret = -EINVAL;
		else
			ret = te_set_engine_mode(dev, val);
		break;

	default:
		ret = -EPERM;
	}

	return ret;
}

static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_input_list[] = {
	DBGITM_SIM_R("status", &debug_ops, DEBUG_INPUT_ID_STATUS),
	DBGITM_NUM("mtime", &proc_input_mtime),
	DBGITM_SIM("config", &debug_ops, DEBUG_INPUT_ID_CONFIG),
	DBGITM_SIM("engine", &debug_ops, DEBUG_INPUT_ID_ENGINE),
};

static int init_debug(struct te_device *dev)
{
	int ret;
	struct te_dev_io *io = &dev->io;

	io->debug_dir = te_debug_create_dir("input", dev->debug.dir);
	CHECK_ERROR(!io->debug_dir, return -EIO, "Err in te_debug_create_dir");

	ret = debug_create_item_files(debug_input_list, dev, io->debug_dir);
	CHECK_ERROR(ret, return ret, "Err in debug_create_item_files");

	return ret;
}

/* te sub driver */

static int io_dev_init(struct te_device *dev)
{
	int i, rc;
	struct te_tpi_monitor *ms;
	struct te_config *te_cfg = te_get_config();

	switch (lx_chip()) {
#ifdef INCLUDE_M23_CHIP_KDRV
	case LX_CHIP_M23:
		conv_cfg = te_io_conv_cfg_swapped;
		break;
#endif
	default:
		conv_cfg = te_io_conv_cfg_normal;
		break;
	}

	if (te_cfg->use_ion) {
		rc = ion_init_device(dev);
		if (rc) {
			log_error("ion_init_device failed %d", rc);
		}
	}

	init_hw(dev);

	for (i = 0; i < MAX_TPI_PORT_NUM; i++) {
		struct te_dev_tpi *c = &dev->tpi[i];
		c->port = i;
		invalidate_tpi_cfg(&c->cfg);

		/* monitor initialize */
		ms = &c->monitor;
		snprintf(ms->name, sizeof(ms->name), "%s",
			 te_reg_tpi_port_to_str(i));

		control_input_monitor(ms, false);	//Disable Monitor first
	}

	for (i = 0; i < MAX_CIPLUS_INPUT_PORT_NUM; i++) {
		dev->ciplus_input[i] = TPI_INVALID;
	}
	dev->ci_input = TPI_CAM_INPUT;

	rc = init_input_monitor(dev);
	CHECK_ERROR(rc != 0,, "Error in init_input_monitor");

	rc = init_debug(dev);
	CHECK_ERROR(rc != 0,, "Error in init_debug");

	return rc;
}

static void io_dev_release(struct te_device *dev)
{
	struct te_config *te_cfg = te_get_config();

	if (te_cfg->use_ion) {
		ion_release_device(dev);
	}
}

static int io_dev_suspend(struct te_device *dev)
{
	int i;
	struct te_suspend_data *data = dev->data;

	mutex_lock(&io_mutex);

	/* Store currnet status & invalid settings */
	for (i = 0; i < MAX_TPI_PORT_NUM; i++) {
		struct te_dev_tpi *tpi = &dev->tpi[i];
		data->tpi[i] = tpi->cfg;
		invalidate_tpi_cfg(&tpi->cfg);

		control_input_monitor(&tpi->monitor, false);	//Disable Monitor on suspend
	}

	for (i = 0; i < MAX_CIPLUS_INPUT_PORT_NUM; i++) {
		data->ciplus_input[i] = dev->ciplus_input[i];
		dev->ciplus_input[i] = TPI_INVALID;
	}

	data->ci_input = dev->ci_input;
	dev->ci_input = TPI_INVALID;

	mutex_unlock(&io_mutex);

	return 0;
}

static int io_dev_resume(struct te_device *dev)
{
	int i;
	struct te_suspend_data *data = dev->data;

	mutex_lock(&io_mutex);

	init_hw(dev);

	for (i = 0; i < MAX_TPI_PORT_NUM; i++) {
		LX_TE_TPI_CFG_T *c = &data->tpi[i];
		if (c->stream_type != LX_TE_STREAM_UNKNOWN) {
			config_tpi(dev, i, c);
		}
	}

	for (i = 0; i < MAX_CIPLUS_INPUT_PORT_NUM; i++) {
		if (data->ciplus_input[i] != TPI_INVALID) {
			set_ciplus_input(dev, i, data->ciplus_input[i]);
		}
	}

	if (data->ci_input != TPI_INVALID) {
		set_ci_input(dev, 0, data->ci_input);
	}

	mutex_unlock(&io_mutex);

	return 0;
}

const struct te_sub_driver te_io_driver = {
	.name = "te_io",
	.init = io_dev_init,
	.release = io_dev_release,
	.suspend = io_dev_suspend,
	.resume = io_dev_resume,
};
