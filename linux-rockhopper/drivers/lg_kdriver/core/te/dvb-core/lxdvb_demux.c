/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.c - DVB demultiplexer device
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *		      for convergence integrated media GmbH
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

/** @file
 *
 *  TE(Transport Engine) Driver for linux dvb(DEMUX)
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-01-26
 *  @note		Additional information.
 */

#include <linux/sched.h>
#include <linux/spinlock.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/ioctl.h>
#include <linux/wait.h>
#include <linux/uaccess.h>
#include <linux/crc32.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/sizes.h>
#include <linux/swab.h>

#include <lg1k/te/io.h>

#include "os_util.h"	// lx_chip()
#include "lxdvb_impl.h"
#include "lxdvb_demux.h"
#include "te_dvb_demux_kapi.h"
#include "te_nagra_kapi.h"
#include "lxdvb_nagra.h"

static int debug;
module_param_named(lxdvb_demux_debug, debug, int, 0644);

static int max_log_cnt = 3;
module_param_named(lxdvb_demux_log_cnt, max_log_cnt, int, 0644);

static int usb_ci_delay = 400; // 400 ms
module_param_named(lxdvb_demux_usb_ci_delay, usb_ci_delay, int, 0644);

#define dprintk(fmt, args...) \
	do { if (debug) log_noti(fmt, ##args); } while(0)

#define log_flt_err(f, fmt, args...) \
	log_error("dmx[%d] idx[%d] pid[0x%04x] - " fmt, (f)->channel->idx, \
		  (f)->idx, (f)->pid_filter->pid, ##args)

#define log_add_error(f, fmt, args...)					\
	do {								\
		if ((f)->errors < max_log_cnt)				\
			log_flt_err(f, fmt, ##args);			\
		(f)->errors++;						\
		if ((f)->errors == max_log_cnt)				\
			log_flt_err(f, "disable error message");	\
	} while (0)


#define TSH_FILTER_CHECK_INTERVAL	100	/* ms */

#define SCRMB_STATUS_NOT_DETECTED	-1
#define SCRMB_STATUS_SCRAMBLED		1
#define SCRMB_STATUS_CLEAR		0

#define is_dmx_pes_type_pcr(t)	\
	((t) == DMX_PES_PCR0 || (t) == DMX_PES_PCR1 || \
	 (t) == DMX_PES_PCR2 || (t) == DMX_PES_PCR3)

#define is_dmx_pes_type_video(t)	\
	((t) == DMX_PES_VIDEO0 || (t) == DMX_PES_VIDEO1 || \
	 (t) == DMX_PES_VIDEO2 || (t) == DMX_PES_VIDEO3)

#define is_pidf_dest_vdec(d) \
	((d) >= LX_SDEC_PFLT_DEST_VDEC0 && (d) <= LX_SDEC_PFLT_DEST_VDEC3)

#define is_pidf_dest_adec(d) \
	((d) >= LX_SDEC_PFLT_DEST_ADEC0 && (d) <= LX_SDEC_PFLT_DEST_ADEC1)

#define is_pidf_dest_av(d) \
	(is_pidf_dest_vdec(d) || is_pidf_dest_adec(d))

#define _IOC_RW		(_IOC_READ | _IOC_WRITE)

enum tsh_filter_bits {
	TSH_FILTER_DONE = 0,
	TSH_FILTER_NO_RUNNER,
	TSH_FILTER_WAKEUP,
	TSH_FILTER_SHOULD_STOP,
};

#define MAX_DEBUG_FILTER_PID	8
struct debug_filter_callback {
	bool enable;
	struct mutex mutex;
	struct lxdvb_dmx_channel *channel; // null = all channels
	int num_pid;	// 0 = all pids
	u16 pid[MAX_DEBUG_FILTER_PID];
	u32 count;
};

struct dmx_lge_control_param {
	u32 id;
	const char *name;
	u32 size;
	u32 dir;
};

static struct debug_filter_callback debug_callback;
static inline struct debug_filter_callback *get_debug_filter_callback(void)
{
	return &debug_callback;
}
#ifndef DMX_COUNTRY_UNKNOWN
#define DMX_COUNTRY_UNKNOWN	0xff
#endif

#ifndef DMX_PLATFORM_UNKNOWN
#define DMX_PLATFORM_UNKNOWN	0xff
#endif

#define SIZE_OF_EXT_SOURCE	sizeof(struct dmx_ext_source)
#define SIZE_OF_DSC_PID		sizeof(struct dmx_ext_dscrmb_pid)
#define SIZE_OF_DSC_KEY		sizeof(struct dmx_ext_dscrmb_key)
#define SIZE_OF_NAGRA_ALGO	sizeof(struct dmx_ext_nagra_algo)
#define SIZE_OF_NAGRA_KEY	sizeof(struct dmx_ext_nagra_key)
#define SIZE_OF_NAGRA_NONCE	sizeof(struct dmx_ext_nagra_nonce)
#define SIZE_OF_NAGRA_STATE	sizeof(struct dmx_ext_nagra_state)

#ifdef USE_FIXEDMEM_STATUS
#define SIZE_OF_DATA_NOTI	0
#else
#define SIZE_OF_DATA_NOTI	164
#endif //USE_FIXEDMEM_STATUS

#define SIZE_OF_XCAS_NOTI	128

//FIXME: should be moved to new xcas/ecp command
#define DMX_EXT_CID_SEND_DATA DMX_EXT_CID_DRV_VER
#define DMX_EXT_CID_SEND_XCAS_DATA DMX_EXT_CID_CHIP_ID

static const struct dmx_lge_control_param dmx_lge_control_params[] = {
	{DMX_EXT_CID_PLATFORM, "platform", 0, _IOC_RW},
	{DMX_EXT_CID_COUNTRY, "country", 0, _IOC_RW},
	{DMX_EXT_CID_MODEL_NO, "model_no", 0, _IOC_WRITE},
	{DMX_EXT_CID_PORT_NUM, "port_num", 0, _IOC_READ},
	{DMX_EXT_CID_AFIFO, "afifo", 0, _IOC_WRITE},
	{DMX_EXT_CID_INPUTSOURCE, "inputsource", SIZE_OF_EXT_SOURCE, _IOC_RW},
	{DMX_EXT_CID_PCR_ONOFF, "pcr_onoff", 0, _IOC_RW},
	{DMX_EXT_CID_REQUEST_SCRMB, "req_scrm", 0, _IOC_RW},
	{DMX_EXT_CID_CANCEL_SCRMB, "cancel_scrm", 0, _IOC_WRITE},
	{DMX_EXT_CID_CHECK_SCRMB, "check_scrm", 0, _IOC_READ},
	{DMX_EXT_CID_DSCRMB_TYPE, "dsc_type", 0, _IOC_RW},
	{DMX_EXT_CID_DSCRMB_PID, "dsc_pid", SIZE_OF_DSC_PID, _IOC_WRITE},
	{DMX_EXT_CID_DSCRMB_KEY, "dsc_key", SIZE_OF_DSC_KEY, _IOC_RW},
	{DMX_EXT_CID_ADD_PID, "add_pid", 0, _IOC_WRITE},
	{DMX_EXT_CID_SEND_DATA, "send_data", SIZE_OF_DATA_NOTI, _IOC_WRITE},
	{DMX_EXT_CID_SDT_PORT_INFO, "sdt_port", 0, _IOC_RW},
	{DMX_EXT_CID_NUMBER_OF_TUNERS, "num_of_tuner", 0, _IOC_RW},
	{DMX_EXT_CID_SEND_XCAS_DATA, "xcas_data", SIZE_OF_XCAS_NOTI, _IOC_WRITE},
	{DMX_EXT_CID_AVSYNC_MODE, "avsync_mode", 0, _IOC_WRITE},

	{DMX_EXT_CID_NAGRA_ALGO, "nagra_algo", SIZE_OF_NAGRA_ALGO, _IOC_WRITE},
	{DMX_EXT_CID_NAGRA_KEY, "nagra_key", SIZE_OF_NAGRA_KEY, _IOC_WRITE},
	{DMX_EXT_CID_NAGRA_GET_STATUS, "nagra_status", 0, _IOC_READ},
	{DMX_EXT_CID_NAGRA_GET_NONCE, "nagra_nonce", SIZE_OF_NAGRA_NONCE, _IOC_READ},
	{DMX_EXT_CID_NAGRA_SET_STATE, "nagra_state", SIZE_OF_NAGRA_STATE, _IOC_WRITE},
};

static const struct te_val_str platform_list[] = {
	{DMX_PLATFORM_ATSC, "ATSC"},
	{DMX_PLATFORM_DVB, "DVB"},
	{DMX_PLATFORM_ISDB, "ISDB"},
	{DMX_PLATFORM_COMMERCIAL, "COMMERCIAL"},
	{DMX_PLATFORM_UNKNOWN, "UNKNOWN"},
};

static const struct te_val_str country_list[] = {
	{DMX_COUNTRY_KR, "KR"},
	{DMX_COUNTRY_US, "US"},
	{DMX_COUNTRY_EU, "EU"},
	{DMX_COUNTRY_CN, "CN"},
	{DMX_COUNTRY_MA, "MA"},
	{DMX_COUNTRY_JP, "JP"},
	{DMX_COUNTRY_COLUMBIA, "COLUMBIA"},
	{DMX_COUNTRY_UNKNOWN, "UNKNOWN"},
};

static const struct te_val_str src_type_list[] = {
	{DMX_EXT_SRC_TYPE_IN_DEMOD, "IN_DEMOD"},
	{DMX_EXT_SRC_TYPE_EXT_DEMOD, "EXT_DEMOD"},
	{DMX_EXT_SRC_TYPE_CI, "CI"},
	{DMX_EXT_SRC_TYPE_CIP, "CIP"},
	{DMX_EXT_SRC_TYPE_MEM, "MEM"},
	{DMX_EXT_SRC_TYPE_NULL, "None"},
	{DMX_EXT_SRC_TYPE_USB_CI, "USB_CI"},
	{DMX_EXT_SRC_TYPE_IPTV, "IPTV"},
};

static const struct te_val_str port_type_list[] = {
	{DMX_EXT_PORT_TYPE_SERIAL, "Serial"},
	{DMX_EXT_PORT_TYPE_PARALLEL, "Parallel"},
};

static const struct te_val_str filter_state_list[] = {
	{DEMUX_FILTER_STATE_FREE, "FREE"},
	{DEMUX_FILTER_STATE_ALLOCATED, "ALLOCATED"},
	{DEMUX_FILTER_STATE_SET, "SET"},
	{DEMUX_FILTER_STATE_GO, "GO"},
	{DEMUX_FILTER_STATE_DONE, "DONE"},
	{DEMUX_FILTER_STATE_TIMEDOUT, "TIMEDOUT"},
	{DEMUX_FILTER_STATE_ERROR, "ERROR"},
};

static const struct te_val_str dmx_out_list[] = {
	{DMX_OUT_DECODER, "DECODER"},
	{DMX_OUT_TAP, "TAP"},
	{DMX_OUT_TS_TAP, "TS_TAP"},
	{DMX_OUT_TSDEMUX_TAP, "TSDEMUX_TAP"},
};

static const struct te_val_str pes_type_list[] = {
	{DMX_PES_AUDIO0, "AUDIO0"},
	{DMX_PES_VIDEO0, "VIDEO0"},
	{DMX_PES_TELETEXT0, "TTX0"},
	{DMX_PES_SUBTITLE0, "SUBT0"},
	{DMX_PES_PCR0, "PCR0"},

	{DMX_PES_AUDIO1, "AUDIO1"},
	{DMX_PES_VIDEO1, "VIDEO1"},
	{DMX_PES_TELETEXT1, "TTX1"},
	{DMX_PES_SUBTITLE1, "SUBT1"},
	{DMX_PES_PCR1, "PCR1"},

	{DMX_PES_AUDIO2, "AUDIO2"},
	{DMX_PES_VIDEO2, "VIDEO2"},
	{DMX_PES_TELETEXT2, "TTX2"},
	{DMX_PES_SUBTITLE2, "SUBT2"},
	{DMX_PES_PCR2, "PCR2"},

	{DMX_PES_AUDIO3, "AUDIO3"},
	{DMX_PES_VIDEO3, "VIDEO3"},
	{DMX_PES_TELETEXT3, "TTX3"},
	{DMX_PES_SUBTITLE3, "SUBT3"},
	{DMX_PES_PCR3, "PCR3"},

	{DMX_PES_OTHER, "OTHER"},
};

static const struct te_val_str filter_type_list[] = {
	{DEMUX_FILTER_TYPE_NONE, "NONE"},
	{DEMUX_FILTER_TYPE_SEC, "SECTION"},
	{DEMUX_FILTER_TYPE_PES, "PES"},
	{DEMUX_FILTER_TYPE_TEMI, "TEMI"},
};

static const struct te_val_str dmx_desc_type_list[] = {
	{DMX_EXT_DSCRMB_TYPE_NONE, "NONE"},
	{DMX_EXT_DSCRMB_TYPE_BCAS, "BCAS"},
	{DMX_EXT_DSCRMB_TYPE_CI_AES, "CI_AES"},
	{DMX_EXT_DSCRMB_TYPE_CI_DES, "CI_DES"},
	{DMX_EXT_DSCRMB_TYPE_PVR, "PVR"},
	{DMX_EXT_DSCRMB_TYPE_CI_AES_ECP, "CI_AES_ECP"},
	{DMX_EXT_DSCRMB_TYPE_CI_DES_ECP, "CI_DES_ECP"},
	{DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2, "EMB_CSA_V2"},
	{DMX_EXT_DSCRMB_TYPE_EMB_CSA_V3, "EMB_CSA_V3"},
	{DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS, "EMB_AES_ATIS"},
};

static const struct te_val_str dmx_desc_key_type_list[] = {
	{DMX_EXT_DSCRMB_KEY_TYPE_EVEN, "EVEN_KEY"},
	{DMX_EXT_DSCRMB_KEY_TYPE_ODD, "ODD_KEY"},
	{DMX_EXT_DSCRMB_KEY_TYPE_EVEN_ODD, "EVEN_ODD"},
	{DMX_EXT_DSCRMB_KEY_TYPE_EVENIV, "EVEN_IV"},
	{DMX_EXT_DSCRMB_KEY_TYPE_ODDIV, "ODD_IV"},
	{DMX_EXT_DSCRMB_KEY_TYPE_CBC, "CBC"},
	{DMX_EXT_DSCRMB_KEY_TYPE_SYSKEY, "SYS"},
	{DMX_EXT_DSCRMB_KEY_TYPE_PVRKEY, "PVR"},
};

static const char *invalid_str = "INVALID";

const char *lxdvb_demux_platform_str(enum dmx_platform platform)
{
	return find_match_string(platform_list, platform, invalid_str);
}

const char *lxdvb_demux_country_str(enum dmx_country country)
{
	return find_match_string(country_list, country, invalid_str);
}

const char *lxdvb_demux_output_str(enum dmx_output output)
{
	return find_match_string(dmx_out_list, output, invalid_str);
}

const char *lxdvb_demux_pes_type_str(enum dmx_ts_pes type)
{
	return find_match_string(pes_type_list, type, invalid_str);
}

const char *lxdvb_demux_src_type_str(enum dmx_src_type type)
{
	return find_match_string(src_type_list, type, invalid_str);
}

const char *lxdvb_demux_port_type_str(enum dmx_ext_port_type type)
{
	return find_match_string(port_type_list, type, invalid_str);
}

const char *lxdvb_demux_filter_state_str(enum lxdvb_dmx_filter_state state)
{
	return find_match_string(filter_state_list, state, invalid_str);
}

const char *lxdvb_demux_filter_type_str(enum lxdvb_dmx_filter_type type)
{
	return find_match_string(filter_type_list, type, invalid_str);
}

static const char *demux_desc_type_str(enum dmx_ext_dscrmb_type type)
{
	return find_match_string(dmx_desc_type_list, type, invalid_str);
}

static const char *demux_desc_key_type_str(enum dmx_ext_dscrmb_key_type type)
{
	return find_match_string(dmx_desc_key_type_list, type, invalid_str);
}

static const struct dmx_lge_control_param *get_dmx_lge_control_param(u32 id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dmx_lge_control_params); i++) {
		if (dmx_lge_control_params[i].id == id)
			return &dmx_lge_control_params[i];
	}

	return NULL;
}

/* input configurations */

static int dmx_ext_get_inputsource(struct lxdvb_dmx_channel *channel,
				   struct dmx_ext_source *params)
{
	*params = channel->input_params;
	return 0;
}

static int dmx_ext_source_to_input_cfg(struct lxdvb_dmx_channel *channel,
				       struct dmx_ext_source *param,
				       struct dmx_input_cfg *cfg)
{
	switch (param->input_src_type) {
	case DMX_EXT_SRC_TYPE_IN_DEMOD:
		if (param->input_port_num > 0)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_TPI_IN_DEMOD0;
		break;
	case DMX_EXT_SRC_TYPE_EXT_DEMOD:
		if (param->input_port_num > 2)
			return -EINVAL;

		cfg->port = LX_TE_INPUT_PORT_TPI_EXT_INPUT0 +
			    param->input_port_num;
		break;
	case DMX_EXT_SRC_TYPE_CI:
		if (param->input_port_num > 0)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_TPI_CI_OUTPUT;
		break;
	case DMX_EXT_SRC_TYPE_CIP:
		if (param->input_port_num > 2)
			return -EINVAL;
		cfg->port = LX_TE_INPUT_PORT_CIPLUS_DEMUX0 +
			    param->input_port_num;
		break;
	case DMX_EXT_SRC_TYPE_MEM:
	case DMX_EXT_SRC_TYPE_USB_CI:
		if (channel->dvr_idx < 0)
			cfg->port = LX_TE_INPUT_PORT_NONE;
		else
			cfg->port = LX_TE_INPUT_PORT_DVR0 + channel->dvr_idx;
		break;
	case DMX_EXT_SRC_TYPE_NULL:
		cfg->port = LX_TE_INPUT_PORT_NONE;
		break;
	default:
		return -EINVAL;
	}

	cfg->mode = (param->input_port_type == DMX_EXT_PORT_TYPE_SERIAL) ?
	    LX_TE_INPUT_MODE_SERIAL : LX_TE_INPUT_MODE_PARALLEL;

	return 0;
}

static int config_input(struct lxdvb_dmx_channel *channel,
			struct dmx_input_cfg *param)
{
	int ret;
	struct lx_sdec_channel_input_cfg cfg;

	cfg.port = param->port;
	cfg.enable = (param->port == LX_TE_INPUT_PORT_NONE) ? false : true;
	cfg.reset = false;

	if (te_get_input_port_type(param->port) == LX_TE_INPUT_PORT_TPI) {
		LX_TE_TPI_CFG_T tpi_cfg;

		tpi_cfg.stream_type = LX_TE_STREAM_MPEG2TS;
		tpi_cfg.mode = param->mode;

		tpi_cfg.sync_type = LX_TE_SYNC_SYNC_BYTE;
		tpi_cfg.s2p_sync_type = LX_TE_SYNC_SYNC_BYTE;
		tpi_cfg.num_of_sync_found = 3;
		tpi_cfg.num_of_sync_drop = 3;

		ret = te_config_tpi(channel->dmx->tdev, param->port, &tpi_cfg);
		if (ret < 0) {
			log_error("te_config_tpi failed(%d)", ret);
			return ret;
		}

		if (ret == 1) {
			cfg.reset = true;
		}
	}

	ret = sdec_config_channel_input(channel->dev, &cfg);
	if (ret) {
		log_error("sdec_config_channel_input failed(%d)", ret);
		return ret;
	}

	return 0;
}

static int dmx_ext_set_inputsource(struct lxdvb_dmx_channel *channel,
				   struct dmx_ext_source *params)
{
	int ret;
	struct dmx_input_cfg cfg;

	log_noti("%s(%d,%s,%d,%s)\n", __func__, channel->idx,
		 lxdvb_demux_src_type_str(params->input_src_type),
		 params->input_port_num,
		 lxdvb_demux_port_type_str(params->input_port_type));

	if (params->input_src_type == DMX_EXT_SRC_TYPE_IPTV) {
		log_warning("src (IPTV) is considered as MEM");
		params->input_src_type = DMX_EXT_SRC_TYPE_MEM;
	}

	ret = dmx_ext_source_to_input_cfg(channel, params, &cfg);
	CHECK_ERROR(ret, return ret, "dmx_ext_source_to_input_cfg failed");

	ret = config_input(channel, &cfg);
	CHECK_ERROR(ret, return ret, "config_input failed");

	/* save all informations */
	channel->input_cfg = cfg;
	channel->input_params = *params;

	return 0;
}

/* DVR related function */
int lxdvb_demux_set_dvr_idx(struct lxdvb_dmx_channel *channel, int idx)
{
	struct dmx_ext_source *params = &channel->input_params;
	struct dmx_input_cfg *cfg = &channel->input_cfg;

	if (mutex_lock_interruptible(&channel->dmx->mutex))
		return -ERESTARTSYS;

	if ((params->input_src_type == DMX_EXT_SRC_TYPE_MEM ||
	    params->input_src_type == DMX_EXT_SRC_TYPE_USB_CI) &&
	    channel->dvr_idx != idx) {
		if (idx < 0) {
			if (cfg->port != LX_TE_INPUT_PORT_NONE) {
				cfg->port = LX_TE_INPUT_PORT_NONE;
				config_input(channel, cfg);
			}
		} else {
			cfg->port = LX_TE_INPUT_PORT_DVR0 + idx;
			config_input(channel, cfg);
		}
	}
	channel->dvr_idx = idx;

	mutex_unlock(&channel->dmx->mutex);

	return 0;
}

int lxdvb_demux_check_usb_ci_recording(struct lxdvb_dmx_channel *channel,
				       bool *detect_usb)
{
	struct lxdvb_demux *dmx = channel->dmx;
	struct dmx_ext_source *params = &channel->input_params;

	*detect_usb = false;

	if (mutex_lock_interruptible(&dmx->mutex))
		return -ERESTARTSYS;

	if (params->input_src_type == DMX_EXT_SRC_TYPE_USB_CI)
		*detect_usb = true;

	mutex_unlock(&channel->dmx->mutex);
	return 0;
}

int lxdvb_demux_set_usb_ci_mode(struct lxdvb_dmx_channel *channel, bool en)
{
	struct lxdvb_demux *dmx = channel->dmx;
	int rc = 0;

	log_noti("usb_ci_mode(DVR): %s", (en) ? "true" : "false");

	if (mutex_lock_interruptible(&dmx->mutex))
		return -ERESTARTSYS;

	channel->usb_ci.enabled = en;

	if (channel->pcr.enabled) {
		if (en)
			sdec_set_pcr_delay(channel->dev, usb_ci_delay);
		else
			sdec_set_pcr_delay(channel->dev, 0);
	}

	mutex_unlock(&channel->dmx->mutex);
	return rc;
}

static int dmx_ext_set_pcr_onoff(struct lxdvb_dmx_channel *channel, int on)
{
	int ret;
	enum lx_sdec_pcr_cmd cmd;
	struct dmx_pcr *pcr = &channel->pcr;
	struct dmx_pcr *orig_pcr = NULL;
	u8 idx = channel->idx;

	if (!pcr->filter) {
		log_error("PCR not set");
		return -EINVAL;
	}

	if (pcr->is_virtual) {
		orig_pcr = pcr; // backup

		channel = pcr->sdt_channel;
		pcr = &channel->pcr;
		log_noti("[%d]USB_CI_PCR(idx:%d)", idx, channel->idx);
	}

	cmd = on ? LX_SDEC_PCR_CMD_ENABLE : LX_SDEC_PCR_CMD_DISABLE;
	ret = sdec_set_pcr_recovery(channel->dev, cmd);
	if (ret) {
		log_error("sdec_set_pcr_recovery failed(%d)", ret);
		return ret;
	}
	pcr->enabled = on ? true : false;
	if (orig_pcr)
		orig_pcr->enabled = pcr->enabled;

	idx = channel->idx;
	log_noti("[%d]PCR control - %s", idx, pcr->enabled ? "ON" : "OFF");

	return 0;
}

static int dmx_ext_get_pcr_onoff(struct lxdvb_dmx_channel *channel, s64 *on)
{
	struct dmx_pcr *pcr = &channel->pcr;

	if (pcr->is_virtual)
		pcr = &pcr->sdt_channel->pcr;

	*on = pcr->enabled ? 1 : 0;

	return 0;
}

/* demux pid filter */

static int alloc_dmx_pid_filter(struct lxdvb_dmx_channel *channel, u16 pid,
				struct dmx_pid_filter **filter)
{
	int ret;
	struct dmx_pid_filter *f;
	struct lxdvb_demux *dmx = channel->dmx;

	f = list_first_entry_or_null(&dmx->free_pid_filters,
				     struct dmx_pid_filter, entry);
	if (!f) {
		log_error("no free pid filter\n");
		ret = -EBUSY;
		goto exit;
	}

	ret = sdec_alloc_pid_filter(channel->dev, pid, &f->dev);
	if (ret) {
		log_error("sdec_alloc_pid_filter failed\n");
		goto exit;
	}

	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	f->channel = channel;
	f->pid = pid;
	INIT_LIST_HEAD(&f->dvb_filters);

	list_move_tail(&f->entry, &channel->pid_filters);

	*filter = f;

exit:
	return ret;
}

static struct dmx_pid_filter *get_dmx_pid_filter(struct lxdvb_dmx_channel
						 *channel, u16 pid)
{
	struct dmx_pid_filter *f;

	list_for_each_entry (f, &channel->pid_filters, entry) {
		if (f->pid == pid)
			return f;
	}

	return NULL;
}


static int dmx_desc_disable_all_pid(struct lxdvb_dmx_channel *channel)
{
	struct lxdvb_dmx_filter *df;
	struct dmx_pid_filter *pf;


	list_for_each_entry (pf, &channel->pid_filters, entry) {
		list_for_each_entry (df, &pf->dvb_filters, pid_filter_entry) {
			df->desc_enable = false;
			df->xcas_desc_enable = false;
			df->nagra_desc_enable = false; //FIXME
		}
	}

	return 0;
}

int lxdvb_demux_desc_disable_all_pid(struct lxdvb_dmx_channel *channel)
{
	return dmx_desc_disable_all_pid(channel);
}

// use for change usb_ci stcc
static void change_av_stcc_idx(struct dmx_pid_filter *pidf)
{
	struct lxdvb_dmx_channel *channel = pidf->channel;
	u32 mask = pidf->dest_mask;

	if (mask & LX_SDEC_PFLT_DEST_MASK(VDEC0) ||
	    mask & LX_SDEC_PFLT_DEST_MASK(VDEC1) ||
	    mask & LX_SDEC_PFLT_DEST_MASK(ADEC0) ||
	    mask & LX_SDEC_PFLT_DEST_MASK(ADEC1)) {
		if (channel->pcr.is_virtual)
			sdec_change_stcc_dest(channel->sdt->dev, mask);
		else
			sdec_change_stcc_dest(channel->dev, mask);
	}
}

static int set_dmx_pid_filter(struct dmx_pid_filter *f)
{
	int ret;
	struct lxdvb_dmx_filter *dvb_filter;
	enum lx_sdec_payload_type payload_type;
	u32 dest_mask;
	struct lxdvb_dmx_channel *channel = f->channel;

	payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
	dest_mask = 0;

	list_for_each_entry (dvb_filter, &f->dvb_filters, pid_filter_entry) {
		if (dvb_filter->payload_type != LX_SDEC_PAYLOAD_UNKNOWN &&
		    payload_type != LX_SDEC_PAYLOAD_UNKNOWN &&
		    dvb_filter->payload_type != payload_type) {
			log_error("not matched payload_type in filter list");
			return -EINVAL;
		}

		if (payload_type == LX_SDEC_PAYLOAD_UNKNOWN)
			payload_type = dvb_filter->payload_type;

		dest_mask |= (0x1 << dvb_filter->dest);
	}

	ret = sdec_set_pid_filter(f->dev, payload_type, dest_mask);
	CHECK_ERROR(ret, return ret, "sdec_set_pid_filter failed");

	f->payload_type = payload_type;
	f->dest_mask = dest_mask;
	f->state = DEMUX_FILTER_STATE_SET;

	/* change stcc dest if it is av pidf */
	if (channel->pcr.is_virtual)
		change_av_stcc_idx(f);

	return 0;
}

static void free_dmx_pid_filter(struct dmx_pid_filter *f)
{
	struct lxdvb_demux *dmx = f->channel->dmx;

	if (!list_empty(&f->dvb_filters)) {
		log_warning("exist dvb dmx filters\n");
	}

	sdec_free_pid_filter(f->dev);

	f->state = DEMUX_FILTER_STATE_FREE;
	list_move_tail(&f->entry, &dmx->free_pid_filters);
}

/* dmx stream filter functions */
static int alloc_dmx_stream_filter(struct lxdvb_dmx_channel *channel,
				   enum lx_sdec_stream_type stream_type,
				   struct dmx_pid_filter *pidf,
				   struct dmx_stream_filter **filter)
{
	int ret;
	struct dmx_stream_filter *f;
	struct lxdvb_demux *dmx = channel->dmx;

	f = list_first_entry_or_null(&dmx->free_stream_filters,
				     struct dmx_stream_filter, entry);
	if (!f) {
		log_error("no free stream filter\n");
		ret = -EBUSY;
		goto err_nofilter;
	}

	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	f->stream_type = stream_type;
	f->pid_filter = pidf;
	f->channel = channel;
	f->dev = NULL;
	f->errors = 0;
	f->received = 0;

	list_move_tail(&f->entry, &channel->stream_filters);

	*filter = f;

	return 0;

err_nofilter:
	return ret;
}

static int alloc_dmx_temi_filter(struct lxdvb_dmx_channel *channel,
				 struct dmx_pid_filter *pidf,
				 struct dmx_temi_filter **filter)
{
	int ret;
	struct dmx_temi_filter *f;
	struct lxdvb_demux *dmx = channel->dmx;

	f = list_first_entry_or_null(&dmx->free_temi_filters,
				     struct dmx_temi_filter, entry);
	if (!f) {
		log_error("no free temi filter\n");
		ret = -EBUSY;
		goto err_alloc;
	}

	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	f->pid_filter = pidf;
	f->channel = channel;
	f->dev =  NULL;
	f->received = 0;
	f->errors = 0;

	list_move_tail(&f->entry, &channel->temi_filters);

	*filter = f;
	return 0;

err_alloc:
	return ret;
}

static bool check_dmx_section_swfilter(struct dmx_section_swfilter *f,
				       struct te_split_buffer *sbuf)
{
	int i, x, s = 0;
	u8 xor, noteq = 0;
	u8 *buf;
	u32 len;

	for (i = 0, x = 0; i < DMX_SWFILTER_SIZE; i++, x++) {
		if (s == 0) {
			buf = sbuf->b[0].data;
			len = sbuf->b[0].size;
			s = 1;
		}

		if (x >= len) {
			if (s == 2 || sbuf->b[1].size == 0)
				break;

			buf = sbuf->b[1].data;
			len = sbuf->b[1].size;
			x = 0;
			s = 2;
		}

		xor = f->value[i] ^ buf[x];
		if (f->equal_mode[i] & xor)
			return false;

		noteq |= f->noteq_mode[i] & xor;
	}

	if (f->do_noteq && !noteq)
		return false;

	return true;
}

static bool check_dmx_section_crc(struct te_split_buffer *sbuf)
{
	struct te_buffer *b0, *b1;
	u32 crc_val = ~0;

	if (sbuf->size < 3)
		return false;

	b0 = &sbuf->b[0];
	b1 = &sbuf->b[1];

	crc_val = crc32_be(crc_val, b0->data, b0->size);
	if (b1->size)
		crc_val = crc32_be(crc_val, b1->data, b1->size);

	if (crc_val) {
		log_filter("check crc failed");
		return false;
	}

	return true;
}

static void make_dmx_split_buffer(struct te_split_buffer *sbuf,
				  struct te_hwbuf *hbuf, u32 sidx, u32 eidx)
{
	sbuf->b[0].data = (u8*)te_hwbuf_data(hbuf) + sidx;
	if (sidx < eidx) {
		sbuf->b[0].size = eidx - sidx;
		sbuf->b[1].data = NULL;
		sbuf->b[1].size = 0;
	} else {
		sbuf->b[0].size = te_hwbuf_size(hbuf) - sidx;
		sbuf->b[1].data = te_hwbuf_data(hbuf);
		sbuf->b[1].size = eidx;
	}
	sbuf->size = sbuf->b[0].size + sbuf->b[1].size;
}

static int dmx_temi_filter_callback(struct sdec_temi_filter *dev,
				    u64 pts, u8 *buf, u16 len,
				    void *priv)
{
	int ret;
	struct dmx_temi_filter *f = priv;

	if (f->dev != dev) {
		return -EINVAL;
	}

	if (f->state != DEMUX_FILTER_STATE_GO) {
		return 0;
	}

	f->received++;

	ret = te_pktbuf_packet_write2(&f->pbuf, &pts, 8, buf, len);
	if (ret < 0) {
		log_add_error(f, "te_pktbuf_packet_write2 failed(%d)", ret);
		goto err_write;
	}

	if (f->oneshot)
		f->state = DEMUX_FILTER_STATE_DONE;

	return 0;

err_write:
	return ret;
}

static bool __debug_stream_filter_matched(struct debug_filter_callback *d,
					  struct dmx_stream_filter *f)
{
	int i;
	u16 pid;

	if (!d->enable)
		return false;

	if (d->channel && d->channel != f->channel)
		return false;

	if (d->num_pid) {
		pid = f->pid_filter->pid;
		for (i = 0; i < d->num_pid; i++) {
			if (d->pid[i] == pid)
				return true;
		}
		return false;
	}

	return true;
}

#ifdef DEBUG_DMX_BUFFER
static void debug_check_stream_filter_buffer(struct dmx_stream_filter *f)
{
	u32 used, free, total;

#define DMX_BUF_WARNING_LEVEL	60 // display log if over 60% of buffer used

	/* This function's buffer owner is producer */
	total = te_pktbuf_size(&f->pbuf);
	free = te_pktbuf_free_size(&f->pbuf);
	used = total - free;
	if (used > f->max_used_size) {
		u32 r = used * 100 / total;
		if (r > DMX_BUF_WARNING_LEVEL) {
			log_noti(TE_COLOR_RED "[%d:%d 0x%04x] %u%% %u/%u"
				 TE_COLOR_NONE, (f)->channel->idx, (f)->idx,
				 f->pid_filter->pid, r, used, total);
		}
		f->max_used_size = used;
	}

#ifndef USE_DMX_FILTER_DIRECT_BUFFER
	total = te_hwbuf_size(&f->hbuf);
	free = te_hwbuf_free_size(&f->hbuf);
	used = total - free;
	if (used > f->max_used_dev_size) {
		u32 r = used * 100 / total;
		if (r > DMX_BUF_WARNING_LEVEL) {
			log_noti(TE_COLOR_RED
				 "DEV [%d:%d 0x%04x] %u%% %u/%u" TE_COLOR_NONE,
				 (f)->channel->idx, (f)->idx,
				 f->pid_filter->pid, r, used, total);
		}
		f->max_used_dev_size = used;
	}
#endif
}
#endif

static void debug_stream_filter_callback(struct dmx_stream_filter *f,
					 u32 sidx, u32 eidx)
{
	u32 len;
	struct debug_filter_callback *d = get_debug_filter_callback();

#ifdef DEBUG_DMX_BUFFER
	debug_check_stream_filter_buffer(f);
#endif

	/* Check enable state without mutex, because debug_filter_callback
	 * is almost disabled, and callback function is called very often */
	if (!d->enable)
		return;

	mutex_lock(&d->mutex);

	if (!__debug_stream_filter_matched(d, f)) {
		mutex_unlock(&d->mutex);
		return;
	}

	len = te_hwbuf_diff_idx(&f->hbuf, sidx, eidx);

#define STREAM_CB_FMT "%6d-%s DMX:%d IDX:%-3d PID:0x%04x "

	if (f->stream_type == LX_SDEC_STREAM_TYPE_SECTION) {
		u8 *tid = te_hwbuf_data(&f->hbuf) + sidx;
		log_noti(STREAM_CB_FMT "TID:0x%02x LEN:%-4d COUNT:%lu\n",
			 d->count, "SEC", f->channel->idx, f->idx,
			 f->pid_filter->pid, *tid, len, f->received);
	} else {
		log_noti(STREAM_CB_FMT "LEN:%-5d COUNT:%lu\n",
			 d->count, sdec_stream_type_str(f->stream_type),
			 f->channel->idx, f->idx,
			 f->pid_filter->pid, len, f->received);
	}
	d->count++;

	mutex_unlock(&d->mutex);
}

/**
 * dmx_stream_filter_callback - callback function of sdec stream filter
 *
 * It is synchronized with dvb_dmx_stop, so @struct dmx_stream_filter
 * is guaranteed
 */
#ifdef USE_DMX_FILTER_DIRECT_BUFFER
static int dmx_stream_filter_callback(struct sdec_stream_filter *dev,
				      enum sdec_filter_status status, u32 sidx,
				      u32 eidx, void *priv)
{
	int ret;
	bool passed;
	struct dmx_stream_filter *f = priv;

	if (f->dev != dev) {
		return -EINVAL;
	}

	if (f->state != DEMUX_FILTER_STATE_GO) {
		return 0;
	}

	if (status != SDEC_FILTER_STATUS_OK) {
		if (te_pktbuf_avail_packet(&f->pbuf) == 0) {
			te_hwbuf_set_ridx(&f->hbuf, eidx);
		}
		return 0;
	}

	if (f->swfilter || f->check_crc) {
		struct te_split_buffer sbuf;

		make_dmx_split_buffer(&sbuf, &f->hbuf, sidx, eidx);

		if (f->swfilter) {
			passed = check_dmx_section_swfilter(f->swfilter, &sbuf);
			if (!passed)
				return -EAGAIN;
		}

		if (f->check_crc) {
			passed = check_dmx_section_crc(&sbuf);
			if (!passed)
				return -EAGAIN;
		}
	}
	f->received++;

	ret = te_pktbuf_add_packet_idx(&f->pbuf, sidx, eidx);
	if (ret) {
		log_add_error(f, "te_pktbuf_add_packet_idx failed(%d)", ret);
		return ret;
	}

	debug_stream_filter_callback(f, sidx, eidx);

	if (f->oneshot) {
		f->state = DEMUX_FILTER_STATE_DONE;
		return -ECANCELED;
	}

	return 0;
}
#else
static int dmx_stream_filter_callback(struct sdec_stream_filter *dev,
				      enum sdec_filter_status status, u32 sidx,
				      u32 eidx, void *priv)
{
	int ret;
	bool passed;
	struct te_split_buffer sbuf;
	struct dmx_stream_filter *f = priv;

	if (f->dev != dev)
		return -EINVAL;

	if (status != SDEC_FILTER_STATUS_OK) {
		ret = 0;
		goto exit;
	}

	if (f->state != DEMUX_FILTER_STATE_GO) {
		ret = 0;
		goto exit;
	}

	make_dmx_split_buffer(&sbuf, &f->hbuf, sidx, eidx);

	if (f->swfilter) {
		passed = check_dmx_section_swfilter(f->swfilter, &sbuf);
		if (!passed) {
			ret = -EAGAIN;
			goto exit;
		}
	}

	if (f->check_crc) {
		passed = check_dmx_section_crc(&sbuf);
		if (!passed) {
			log_add_error(f, "crc error");
			ret = -EAGAIN;
			goto exit;
		}
	}

	f->received++;

	ret = te_pktbuf_packet_write2(&f->pbuf, sbuf.b[0].data, sbuf.b[0].size,
				      sbuf.b[1].data, sbuf.b[1].size);
	if (ret < 0) {
		log_add_error(f, "te_pktbuf_packet_write2 failed(%d)", ret);
		goto exit;
	}

	debug_stream_filter_callback(f, sidx, eidx);

	if (f->oneshot) {
		f->state = DEMUX_FILTER_STATE_DONE;
		ret = -ECANCELED;
		goto exit;
	}

	ret = 0;
exit:
	te_hwbuf_set_ridx(&f->hbuf, eidx);

	return ret;
}
#endif

static int request_dmx_stream_filter(struct dmx_stream_filter *f,
				     struct lx_sdec_filter_pattern *pattern)
{
	int ret;
	struct sdec_stream_filter_param param;

	param.stream_type = f->stream_type;
	param.pidf = f->pid_filter->dev;
	param.hbuf = &f->hbuf;
	param.pattern = pattern;
	param.callback = dmx_stream_filter_callback;
	param.flags = 0;
	if (!f->check_crc)
		param.flags |= LX_SDEC_SFLT_FLAG_NO_CRC_CHECK;
#ifdef USE_DMX_SDEC_ONESHOT_MODE
	if (f->oneshot)
		param.flags |= LX_SDEC_SFLT_FLAG_ONESHOT;
#endif
	param.priv = f;

	ret = sdec_request_stream_filter(f->channel->dev, &param, &f->dev);
	CHECK_ERROR(ret, return ret, "sdec_request_stream_filter failed");

	f->state = DEMUX_FILTER_STATE_GO;

	return 0;
}

static int cancel_dmx_stream_filter(struct dmx_stream_filter *f)
{
	if (!f->dev)
		return -EINVAL;

	sdec_cancel_stream_filter(f->dev);
	f->state = DEMUX_FILTER_STATE_ALLOCATED;

	return 0;
}

static void free_dmx_stream_filter(struct dmx_stream_filter *f)
{
	struct lxdvb_demux *dmx = f->channel->dmx;

	f->state = DEMUX_FILTER_STATE_FREE;
	list_move_tail(&f->entry, &dmx->free_stream_filters);
}

static void free_dmx_temi_filter(struct dmx_temi_filter *f)
{
	struct lxdvb_demux *dmx = f->channel->dmx;

	f->state = DEMUX_FILTER_STATE_FREE;
	list_move_tail(&f->entry, &dmx->free_temi_filters);
}

static int dvb_dmx_set_buffer_size(struct lxdvb_dmx_filter *filter,
				   unsigned long size)
{
	if (!size)
		return -EINVAL;

	if (filter->state >= DEMUX_FILTER_STATE_GO)
		return -EBUSY;

	filter->buf_size = size;

	return 0;
}

/**
 * __cancel_dvb_filter_pid - Cancel pid filter of dvb filter
 *
 * It removes the dvb filter entry from the pid filter list and set h/w pid
 * filter again with remaind dvb filters. If the pid filter has no dvb filter
 * entry, it will be freed.
 */
static void __cancel_dvb_filter_pid(struct lxdvb_dmx_filter *f)
{
	struct dmx_pid_filter *pidf = f->pid_filter;

	list_del(&f->pid_filter_entry);

	if (list_empty(&pidf->dvb_filters)) {
		free_dmx_pid_filter(pidf);
	} else {
		set_dmx_pid_filter(pidf);
	}
	f->pid_filter = NULL;
}

static int __dmx_set_desc_pid_enable(struct lxdvb_dmx_filter *f, bool enable)
{
	struct list_head *dvb_list;
	struct lxdvb_dmx_filter *dmxf;
	struct lxdvb_dmx_channel *channel = f->channel;
	struct lx_sdec_desc_pid param;
	int num, rc;

	if (f->state < DEMUX_FILTER_STATE_GO) {
		log_error("pid filter is not started(%s)",
			  lxdvb_demux_filter_state_str(f->state));
		return -EIO;
	}

	if (!f->pid_filter) {
		log_error("pidf is not set(pid:0x%x(%s),enable:%d state:%s)",
			  f->pid, sdec_pid_filter_dest_str(f->dest),
			  enable, lxdvb_demux_filter_state_str(f->state));
		return -EIO;
	}

	dvb_list = &f->pid_filter->dvb_filters;
	num = 0;
	list_for_each_entry (dmxf, dvb_list, pid_filter_entry) {
		if (dmxf->desc_enable)
			num++;
	}

	if (enable) {
		if (num == 0) {
			param.mode = LX_SDEC_DESC_PID_ENABLE;
			param.pid = f->pid;
			rc = sdec_set_descrambler_pid(channel->dev, &param);
			CHECK_ERROR(rc, return rc, "set desc pid failed");
		}
	} else {
		if (num == 1) {
			param.mode = LX_SDEC_DESC_PID_DISABLE;
			param.pid = f->pid;
			rc = sdec_set_descrambler_pid(channel->dev, &param);
			CHECK_ERROR(rc, return rc, "set desc pid failed");
		}
	}
	f->desc_enable = enable;

	return 0;
}

static void cancel_xcas_desc_key(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *channel = f->channel;

	sdec_desc_cancel_xcas_pid(channel->dev, f->pid);
	f->xcas_desc_enable = false;
}

static int cancel_dvb_desc_pid(struct lxdvb_dmx_filter *f)
{
	if (f->channel->desc_mode != LX_SDEC_DESC_MODE_CHANNEL_PID &&
	    f->channel->desc_mode != LX_SDEC_DESC_MODE_PID)
		return 0;

	if (f->desc_enable)
		__dmx_set_desc_pid_enable(f, false);

	if (f->xcas_desc_enable)
		cancel_xcas_desc_key(f);

	if (f->nagra_desc_enable) { //FIXME
		dmx_nagra_cancel_desc_pid(f);
	}

	return 0;
}

static int dest_matched_dmx_filter_count(struct lxdvb_dmx_channel *channel,
					 enum lx_sdec_pid_filter_dest dest)
{
	int i;
	struct lxdvb_dmx_filter *f;
	int count = 0;

	for (i = 0; i < channel->num_filter; i++) {
		f = &channel->filter[i];
		if (f->state == DEMUX_FILTER_STATE_GO && f->dest == dest) {
			count++;
		}
	}

	return count;
}

static int dest_matched_all_dmx_filter_count(struct lxdvb_dmx_channel *channel,
					     enum lx_sdec_pid_filter_dest dest)
{
	int i;
	struct lxdvb_dmx_channel *c;
	struct lxdvb_demux *dmx = channel->dmx;
	int count = 0;

	for (i = 0; i < dmx->num_channel; i++) {
		c = &dmx->channels[i];
		count += dest_matched_dmx_filter_count(c, dest);
	}

	return count;
}

static int set_dvb_filter_pid(struct lxdvb_dmx_filter *f)
{
	int ret;
	struct dmx_pid_filter *pidf;
	struct lxdvb_dmx_channel *channel = f->channel;

	CHECK_ERROR(f->pid_filter, return -EBUSY, "already set");

	if (f->stream_type == LX_SDEC_STREAM_TYPE_NONE &&
	    f->dest != LX_SDEC_PFLT_DEST_TSHEADER) { //Prevent verbose scr check
		log_noti("%s(%d,0x%04x,%s)", __func__, channel->idx,
			 f->pid, sdec_pid_filter_dest_str(f->dest));
	} else {
		log_filter("%s(%d,0x%04x,%s)", __func__, channel->idx,
			   f->pid, sdec_stream_type_str(f->stream_type));
	}

	pidf = get_dmx_pid_filter(channel, f->pid);
	if (!pidf) {
		ret = alloc_dmx_pid_filter(channel, f->pid, &pidf);
		CHECK_ERROR(ret, return ret, "alloc_dmx_pid_filter failed");
	} else {
		if (f->payload_type != LX_SDEC_PAYLOAD_UNKNOWN &&
		    pidf->payload_type != LX_SDEC_PAYLOAD_UNKNOWN &&
		    f->payload_type != pidf->payload_type) {
			log_error("payload_type new(%d) != current(%d) "
				  "- pid 0x%04x",
				  f->payload_type, pidf->payload_type, f->pid);
			return -EINVAL;
		}
	}

	/* add this dvb filter to the pid filter list */
	list_add_tail(&f->pid_filter_entry, &pidf->dvb_filters);
	f->pid_filter = pidf;

	if (is_pidf_dest_av(f->dest) && !(f->flags & DEMUX_FILTER_FLAG_CHILD) &&
	    dest_matched_all_dmx_filter_count(channel, f->dest)) {
		log_error("already set dest(%s)\n",
			  sdec_pid_filter_dest_str(f->dest));
		ret = -EBUSY;
		goto err_set_filter;
	}

	ret = set_dmx_pid_filter(pidf);
	if (ret) {
		log_error("set_dmx_pid_filter failed");
		goto err_set_filter;
	}

	return 0;

err_set_filter:
	/* The filter was already added to pid filter list in this stage.
	 * __cancel_dvb_filter_pid will remove this filter from the list
	 * and free pid filter if no filters in the list */
	__cancel_dvb_filter_pid(f);

	return ret;
}

static int cancel_dvb_filter_pid(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *channel = f->channel;

	CHECK_ERROR(!f->pid_filter, return -EINVAL, "pid filter not set");

	if (f->stream_type == LX_SDEC_STREAM_TYPE_NONE &&
	    f->dest != LX_SDEC_PFLT_DEST_TSHEADER) {
		log_noti("%s(%d,0x%04x,%s)", __func__, channel->idx,
			 f->pid, sdec_pid_filter_dest_str(f->dest));
	} else {
		log_filter("%s(%d,0x%04x,%s)", __func__, channel->idx,
			   f->pid, sdec_stream_type_str(f->stream_type));
	}

	cancel_dvb_desc_pid(f);
	__cancel_dvb_filter_pid(f);

	return 0;
}

static int set_virtual_pcr_pid(struct lxdvb_dmx_channel *channel,
			       struct dmx_pcr *pcr,
			       struct lxdvb_dmx_filter *f)
{
	int rc;
	struct lxdvb_dmx_channel *sdt_channel;
	struct dmx_pcr *sdt_pcr;
	struct dmx_pid_filter *pidf;

	sdt_channel = channel->sdt;
	sdt_pcr = &sdt_channel->pcr;

	log_noti("USB_CI_PCR(idx:%d)", sdt_channel->idx);

	/* Check for already registered pcr in new channel */
	if (sdt_channel->pcr.filter) {
		log_error("already set pcr pid(0x%x)",
			  sdt_channel->pcr.filter->pid);
		return -EBUSY;
	}

	/* add some delay for USB CI path */
	rc = sdec_set_pcr_delay(sdt_channel->dev, usb_ci_delay);
	if (rc) {
		log_error("sdec_set_pcr_delay(%d) failed(%d)", usb_ci_delay,
			  rc);
		return rc;
	}

	/* convert to actual one */
	rc = sdec_set_pcr_pid(sdt_channel->dev, f->pid, true);
	if (rc) {
		log_error("sdec_set_pcr_pid failed(%d)", rc);
		return rc;
	}

	sdt_pcr->filter = f;
	sdt_pcr->enabled = true;

	/* virtual pcr setting */
	pcr->is_virtual = true; //mark as virtual pcr
	pcr->sdt_channel = sdt_channel;
	pcr->enabled = true;
	pcr->filter = f;

	/* audio/video pid check for stcc change */
	list_for_each_entry (pidf, &channel->pid_filters, entry) {
		change_av_stcc_idx(pidf);
	}

	return 0;
}

static int set_dvb_filter_pcr_pid(struct lxdvb_dmx_filter *f)
{
	int rc;
	struct lxdvb_dmx_channel *channel = f->channel;
	struct dmx_pcr *pcr = &channel->pcr;
	struct dmx_ext_source *input_params = &channel->input_params;

	log_noti("%s(%d,0x%04x)", __func__, channel->idx, f->pid);

	if (pcr->filter) {
		log_error("already set pcr pid(0x%x)", pcr->filter->pid);
		return -EBUSY;
	}

	if (input_params->input_src_type == DMX_EXT_SRC_TYPE_USB_CI) {
		if (channel->sdt && channel != channel->sdt) {
			return set_virtual_pcr_pid(channel, pcr, f);
		} else if (channel == channel->sdt) {
			log_warning("same SDT channel; use legacy one");
		} else {
			log_warning("not set SDT INFO; use legacy one");
		}
	} else if (input_params->input_src_type == DMX_EXT_SRC_TYPE_MEM) {
		if (channel->usb_ci.enabled)
			sdec_set_pcr_delay(channel->dev, usb_ci_delay);
	}

	rc = sdec_set_pcr_pid(channel->dev, f->pid, true);
	if (rc) {
		log_error("sdec_set_pcr_pid failed(%d)", rc);
		return rc;
	}

	pcr->filter = f;
	pcr->enabled = true;

	return 0;
}

static void cancel_virtual_pcr_pid(struct lxdvb_dmx_channel *channel,
				   struct dmx_pcr *pcr,
				   struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *sdt_channel = channel->pcr.sdt_channel;
	struct dmx_pcr *sdt_pcr = &sdt_channel->pcr;
	struct dmx_pid_filter *pidf;

	/* cancel actual one */
	log_noti("USB_CI_PCR(idx:%d)", sdt_channel->idx);
	if (sdt_pcr->filter != f) {
		log_error("diff with current pcr(0x%04x)",
			  sdt_pcr->filter->pid);
	}

	sdec_cancel_pcr_pid(sdt_channel->dev);

	/* recover usb ci delay to normal */
	sdec_set_pcr_delay(sdt_channel->dev, 0);

	sdt_pcr->filter = NULL;
	sdt_pcr->enabled = false;

	/* release virtual setting */
	pcr->is_virtual = false;
	pcr->sdt_channel = NULL;
	pcr->enabled = false;
	pcr->filter = NULL;

	/* audio/video pid check for stcc change */
	list_for_each_entry (pidf, &channel->pid_filters, entry) {
		change_av_stcc_idx(pidf);
	}
}

static void cancel_dvb_filter_pcr_pid(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *channel = f->channel;
	struct dmx_pcr *pcr = &channel->pcr;

	log_noti("%s(%d,0x%04x)", __func__, channel->idx, f->pid);

	if (pcr->is_virtual) //USB_CI mode
		return cancel_virtual_pcr_pid(channel, pcr, f);

	if (pcr->filter) {
		if (pcr->filter != f) {
			log_error("diff with current pcr(0x%04x)",
				  pcr->filter->pid);
		}

		sdec_cancel_pcr_pid(channel->dev);

		/* recover delay to normal */
		sdec_set_pcr_delay(channel->dev, 0);

		pcr->filter = NULL;
		pcr->enabled = false;
	}
}


/**
 * convert_filter_pattern - Convert dvb demux filter value to sdec pattern
 *
 * sdec section filter not use 2nd byte of input stream but dvb demux filter
 * not use both 2nd and 3rd bytes likes below,
 * |0|1|2|3|4|5|6|7|8|9| = section data
 * |0|X|1|2|3|4|5|6|7|8| = sdec section filter
 * |0|X|X|1|2|3|4|5|6|7| = dvb demux filter
 */
static void convert_filter_pattern(u8 *dvb, u8 *dev)
{
	int i, j;

	for (i = 0, j = 0; i < LX_SDEC_FILTER_SIZE; i++) {
		if (i != 1 && j < DMX_FILTER_SIZE)
			dev[i] = dvb[j++];
		else
			dev[i] = 0;
	}
}

/**
 * make_dev_filter_pattern - Make a section filter pattern with dvb demux filter
 */
static void make_dev_filter_pattern(struct lx_sdec_filter_pattern *pattern,
				    struct dmx_filter *param)
{
	convert_filter_pattern(param->filter, pattern->value);
	convert_filter_pattern(param->mask, pattern->mask);
	convert_filter_pattern(param->mode, pattern->noteq);
}

/**
 * add_dmx_section_swfilter - Add a section s/w filter if the requested dvb
 * filter size is over max sdec(device) filter size
 */
static void add_dmx_section_swfilter(struct dmx_stream_filter *f,
				     struct dmx_filter *param)
{
#if DMX_FILTER_SIZE > (LX_SDEC_FILTER_SIZE - 1)
	int i, x, do_noteq;
	struct dmx_section_swfilter *swf;

	for (i = (LX_SDEC_FILTER_SIZE - 1); i < DMX_FILTER_SIZE; i++) {
		if (param->mask[i])
			break;
	}

	if (i == DMX_FILTER_SIZE)
		return;

	swf = kmalloc(sizeof(*swf), GFP_KERNEL);
	CHECK_ERROR(!swf, return, "no mem");

	do_noteq = 0;
	for (i = 0, x = 0; i < DMX_SWFILTER_SIZE; i++) {
		if (i == 1 || i == 2) {	/* dvb filter not use 2nd & 3rd field */
			swf->value[i] = 0;
			swf->equal_mode[i] = 0;
			swf->noteq_mode[i] = 0;
		} else {
			swf->value[i] = param->filter[x];
			swf->equal_mode[i] = param->mask[x] & ~param->mode[x];
			swf->noteq_mode[i] = param->mask[x] & param->mode[x];
			do_noteq |= swf->noteq_mode[i];
			x++;
		}
	}
	swf->do_noteq = do_noteq ? 1 : 0;

	f->swfilter = swf;
#endif
}

static void remove_dmx_section_swfilter(struct dmx_stream_filter *f)
{
	if (f->swfilter) {
		kfree(f->swfilter);
		f->swfilter = NULL;
	}
}

#ifdef USE_DMX_FILTER_DIRECT_BUFFER
static void stream_filter_packet_read_callback(void *arg, u32 idx)
{
	struct dmx_stream_filter *f = arg;

	te_hwbuf_set_ridx(&f->hbuf, idx);
}

static int alloc_dmx_stream_filter_buffer(struct lxdvb_dmx_channel *channel,
					  struct dmx_stream_filter *f, u32 size)
{
	int ret;
	te_phys_addr_t addr;
	u32 pkt_size;

	addr = te_mem_alloc(channel->dmx->mem, size, "dvb_dmx");
	CHECK_ERROR(!addr, return -ENOMEM, "no dev mem");

	ret = te_hwbuf_init(&f->hbuf, addr, size, 0, TE_BUF_FLAG_VMAP_CACHED);
	if (ret) {
		log_error("te_hwbuf_init failed(%d)", ret);
		goto err_hwbuf;
	}

	switch (f->stream_type) {
	case LX_SDEC_STREAM_TYPE_SECTION:
		pkt_size = 128;	/* packet count = 256 if buffer size = 32KB */
		break;
	case LX_SDEC_STREAM_TYPE_PES:
		pkt_size = 1024; /* packet count = 256 if buffer size = 256KB */
		break;
	case LX_SDEC_STREAM_TYPE_RAWTS:
		pkt_size = 188;
		break;
	default:
		pkt_size = 32;
		break;
	}

	ret = te_pktbuf_init(&f->pbuf, te_hwbuf_data(&f->hbuf), size,
			     pkt_size, 0);
	if (ret) {
		log_error("te_pktbuf_init failed(%d)", ret);
		goto err_pktbuf;
	}

	te_pktbuf_set_read_callback(&f->pbuf,
				    stream_filter_packet_read_callback,
				    f);

	return 0;

err_pktbuf:
	te_hwbuf_release(&f->hbuf);
err_hwbuf:
	te_mem_free(channel->dmx->mem, addr);

	return ret;
}

static void free_dmx_stream_filter_buffer(struct lxdvb_dmx_channel *channel,
					  struct dmx_stream_filter *f)
{
	te_phys_addr_t addr = (te_phys_addr_t)te_hwbuf_addr(&f->hbuf);

	te_pktbuf_release(&f->pbuf);
	te_hwbuf_release(&f->hbuf);
	te_mem_free(channel->dmx->mem, addr);
}
#else
static int alloc_dmx_stream_filter_buffer(struct lxdvb_dmx_channel *channel,
					  struct dmx_stream_filter *f, u32 size)
{
	int ret;
	te_phys_addr_t addr;
	u32 hwbuf_size;
	void *data;

	data = vmalloc(size);
	CHECK_ERROR(!data, return -ENOMEM, "vmalloc failed");

	ret = te_pktbuf_init(&f->pbuf, data, size, 0,
			     TE_BUF_FLAG_INNER_PKTINFO);
	if (ret) {
		log_error("te_pktbuf_init failed(%d)", ret);
		goto err_pktbuf;
	}

	// TODO: optimize hw buffer size
	switch (f->stream_type) {
	case LX_SDEC_STREAM_TYPE_SECTION:
		if (f->oneshot) {
			/* max section size is 4096 and max free size of
			 * ringbuffer is (total_size - 1) so buffer size must
			 * be over 4096 + 1 */
			hwbuf_size = SZ_8K;
		} else {
			hwbuf_size = size >> 1;
		}
		break;
	case LX_SDEC_STREAM_TYPE_PES:
		hwbuf_size = SZ_128K;
		break;
	case LX_SDEC_STREAM_TYPE_RAWTS:
	default:
		hwbuf_size = size;
		break;
	}

	addr = te_mem_alloc(channel->dmx->mem, hwbuf_size, "dvb_dmx");
	if (!addr) {
		log_error("te_mem_alloc failed\n");
		ret = -ENOMEM;
		goto err_mem_alloc;
	}

	ret = te_hwbuf_init(&f->hbuf, addr, hwbuf_size, 0,
			    TE_BUF_FLAG_NO_EVENT | TE_BUF_FLAG_VMAP_CACHED);
	if (ret) {
		log_error("te_hwbuf_init failed(%d)", ret);
		goto err_hwbuf;
	}

	return 0;

err_hwbuf:
	te_mem_free(channel->dmx->mem, addr);
err_mem_alloc:
	te_pktbuf_release(&f->pbuf);
err_pktbuf:
	vfree(data);

	return ret;
}

static void free_dmx_stream_filter_buffer(struct lxdvb_dmx_channel *channel,
					  struct dmx_stream_filter *f)
{
	te_phys_addr_t addr = (te_phys_addr_t)te_hwbuf_addr(&f->hbuf);
	void *data = te_pktbuf_data(&f->pbuf);

	te_hwbuf_release(&f->hbuf);
	te_mem_free(channel->dmx->mem, addr);

	te_pktbuf_release(&f->pbuf);
	vfree(data);
}
#endif

static void dvb_dmx_filter_timeout(void *arg)
{
	struct lxdvb_dmx_filter *f = arg;

	mutex_lock(&f->mutex);
	if (f->state == DEMUX_FILTER_STATE_GO) {
		log_debug("dvb_dmx_filter_timeout");

		te_pktbuf_set_error(f->pbuf, -ETIME);

		f->state = DEMUX_FILTER_STATE_TIMEDOUT;
	}
	mutex_unlock(&f->mutex);
}

static int request_dvb_filter_stream(struct lxdvb_dmx_filter *f)
{
	int ret;
	struct dmx_stream_filter *streamf;
	struct lx_sdec_filter_pattern pattern;
	struct lxdvb_dmx_channel *channel = f->channel;
	u32 alloc_size, timeout;

	CHECK_ERROR(f->stream_filter, return -EBUSY, "already started");
	CHECK_ERROR(!f->pid_filter, return -EINVAL, "no pid filter");

	log_filter("pid=0x%x idx=%d", f->pid, f->idx);

	ret = alloc_dmx_stream_filter(channel, f->stream_type, f->pid_filter,
				      &streamf);
	CHECK_ERROR(ret, return ret, "alloc_dmx_stream_filter failed");

	if (f->stream_type == LX_SDEC_STREAM_TYPE_SECTION) {
		struct dmx_sct_filter_params *p = &f->params.sec;

		make_dev_filter_pattern(&pattern, &p->filter);
		add_dmx_section_swfilter(streamf, &p->filter);

		streamf->check_crc = (p->flags & DMX_CHECK_CRC) ? true : false;
		streamf->oneshot = (p->flags & DMX_ONESHOT) ? true : false;

		/* allocation size comes from hal */
		if (streamf->oneshot)
			alloc_size = SZ_8K;
		else
			alloc_size = ALIGN(f->buf_size * 3, SZ_32K);

		timeout = p->timeout;
	} else {
		streamf->check_crc = false;
		streamf->oneshot = false;

		if (f->buf_size < SZ_256K)
			alloc_size = SZ_256K;
		else
			alloc_size = ALIGN(f->buf_size, SZ_32K);

		timeout = 0;
	}

	if (alloc_size > SZ_512K)
		alloc_size = SZ_512K;

	ret = alloc_dmx_stream_filter_buffer(channel, streamf, alloc_size);
	CHECK_ERROR(ret, goto err_alloc, "alloc_buffer failed");

	ret = request_dmx_stream_filter(streamf, &pattern);
	CHECK_ERROR(ret, goto err_req, "request_dmx_stream_filter failed");

#ifdef DEBUG_DMX_BUFFER
	streamf->max_used_size = 0;
	streamf->max_used_dev_size = 0;
#endif
	if (timeout) {
		streamf->timer = te_add_oneshot_timer(channel->dmx->tdev,
						      timeout,
						      dvb_dmx_filter_timeout,
						      f);
	}
	f->pbuf = &streamf->pbuf;
	f->stream_filter = streamf;

	return 0;

err_req:
	free_dmx_stream_filter_buffer(channel, streamf);
err_alloc:
	remove_dmx_section_swfilter(streamf);
	free_dmx_stream_filter(streamf);

	return ret;
}

static int cancel_dvb_filter_stream(struct lxdvb_dmx_filter *f)
{
	struct lxdvb_dmx_channel *channel = f->channel;
	struct dmx_stream_filter *streamf = f->stream_filter;

	CHECK_ERROR(!streamf, return -EINVAL, "no stream filter");

	log_filter("pid=0x%x idx=%d", f->pid, f->idx);

	cancel_dmx_stream_filter(streamf);
	if (streamf->timer) {
		te_del_timer(streamf->timer);
		streamf->timer = NULL;
	}

	free_dmx_stream_filter_buffer(channel, streamf);
	remove_dmx_section_swfilter(streamf);
	free_dmx_stream_filter(streamf);

	f->pbuf = NULL;
	f->stream_filter = NULL;

	return 0;
}

static int alloc_temi_filter_buffer(struct lxdvb_dmx_channel *channel,
				    struct dmx_temi_filter *f, u32 size)
{
	void *data;
	int ret;

	data = vmalloc(size);
	CHECK_ERROR(!data, return -ENOMEM, "vmalloc failed");

	ret = te_pktbuf_init(&f->pbuf, data, size, 0,
			     TE_BUF_FLAG_INNER_PKTINFO);
	if (ret) {
		log_error("pkt buffer alloc failed");
		goto err_pktbuf;
	}

	return 0;

err_pktbuf:
	vfree(data);
	return ret;
}

static void free_temi_filter_buffer(struct dmx_temi_filter *f)
{
	u8 *data = te_pktbuf_data(&f->pbuf);

	te_pktbuf_release(&f->pbuf);
	vfree(data);
}

static int request_temi_filter(struct dmx_temi_filter *f,
			       struct sdec_temi_filter_pattern *pattern)
{
	struct sdec_temi_filter_param param;
	int ret;

	param.pid = f->pid_filter->pid;
	param.pattern = pattern;
	param.callback = dmx_temi_filter_callback;
	param.flags = 0;
	if (f->oneshot)
		param.flags |= LX_SDEC_SFLT_FLAG_ONESHOT;
	param.priv = f;

	ret = sdec_request_temi_filter(f->channel->dev, &param, &f->dev);
	CHECK_ERROR(ret, return ret, "sdec_request_temi_filter failed");

	f->state = DEMUX_FILTER_STATE_GO;
	return 0;
}

static int request_dvb_temi_filter(struct lxdvb_dmx_filter *f)
{
	struct dmx_temi_filter *temif;
	struct lxdvb_dmx_channel *channel = f->channel;
	struct sdec_temi_filter_pattern pattern;
	struct dmx_sct_filter_params *p = &f->params.sec;
	u32 alloc_size;
	int ret;

	CHECK_ERROR(f->temi_filter, return -EBUSY, "already started");
	CHECK_ERROR(!f->pid_filter, return -EINVAL, "no pid filter");

	log_filter("pid = 0x%04x", f->pid);

	ret = alloc_dmx_temi_filter(channel, f->pid_filter, &temif);
	if (ret) {
		log_error("alloc_dmx_stream filter_failed %d", ret);
		return ret;
	}

	pattern.val = p->filter.filter[0];
	pattern.mask = p->filter.mask[0];
	pattern.noteq = p->filter.mode[0];

	temif->oneshot = (p->flags & DMX_ONESHOT) ? true : false;

	if (f->buf_size < SZ_32K)
		alloc_size = SZ_32K;
	else if (f->buf_size > SZ_256K)
		alloc_size = SZ_256K;
	else
		alloc_size = ALIGN(f->buf_size, SZ_4K);

	ret = alloc_temi_filter_buffer(channel, temif, alloc_size);
	CHECK_ERROR(ret, goto err_alloc, "alloc_buffer failed");

	ret = request_temi_filter(temif, &pattern);
	CHECK_ERROR(ret, goto err_req, "request_temi_filter failed");

	if (p->timeout) {
		temif->timer = te_add_oneshot_timer(channel->dmx->tdev,
						    p->timeout,
						    dvb_dmx_filter_timeout,
						    f);
	}

	f->pbuf = &temif->pbuf;
	f->temi_filter = temif;

	return 0;

err_req:
	free_temi_filter_buffer(temif);
err_alloc:
	free_dmx_temi_filter(temif);
	return ret;
}

static int cancel_temi_filter(struct dmx_temi_filter *f)
{
	if (!f->dev)
		return -EINVAL;

	sdec_cancel_temi_filter(f->dev);
	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	return 0;
}

static int cancel_dvb_temi_filter(struct lxdvb_dmx_filter *f)
{
	struct dmx_temi_filter *temif = f->temi_filter;

	CHECK_ERROR(!temif, return -EINVAL, "no stream filter");

	log_filter("pid=0x%x", f->pid);

	cancel_temi_filter(temif);

	if (temif->timer) {
		te_del_timer(temif->timer);
		temif->timer = NULL;
	}

	free_temi_filter_buffer(temif);
	free_dmx_temi_filter(temif);

	f->pbuf = NULL;
	f->temi_filter = NULL;

	return 0;
}

static int alloc_dvb_dmx_filter(struct lxdvb_dmx_channel *channel,
				struct lxdvb_dmx_filter **filter)
{
	int i;
	struct lxdvb_dmx_filter *f;

	for (i = 0; i < channel->num_filter; i++) {
		f = &channel->filter[i];
		if (f->state == DEMUX_FILTER_STATE_FREE)
			break;
	}

	if (i == channel->num_filter)
		return -EBUSY;

	f->desc_enable = false;
	f->xcas_desc_enable = false;
	f->nagra_desc_enable = false;
	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	f->type = DEMUX_FILTER_TYPE_NONE;
	f->channel = channel;
	f->flags = 0;
	f->pid_filter = NULL;
	f->stream_filter = NULL;
	f->temi_filter = NULL;
	f->child = NULL;
	f->buf_size = SZ_4K;
	f->pbuf = NULL;
	f->read_size = 0;

	*filter = f;

	return 0;
}

static void free_dvb_dmx_filter(struct lxdvb_dmx_filter *filter)
{
	if (filter->state > DEMUX_FILTER_STATE_SET)
		log_warning("filter not stopped");

	filter->state = DEMUX_FILTER_STATE_FREE;
}

static int set_dvb_dmx_filter_attr_decoder(struct lxdvb_dmx_filter *filter,
					   struct dmx_pes_filter_params *params)
{
	filter->stream_type = LX_SDEC_STREAM_TYPE_NONE;

	if (is_dmx_pes_type_pcr(params->pes_type)) {
		filter->payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
		filter->dest = LX_SDEC_PFLT_DEST_STC;
	} else if (params->pes_type == DMX_PES_OTHER) {
		filter->payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
		filter->dest = LX_SDEC_PFLT_DEST_NONE;
	} else {
		filter->payload_type = LX_SDEC_PAYLOAD_PES;
		switch (params->pes_type) {
		case DMX_PES_VIDEO0:
			filter->dest = LX_SDEC_PFLT_DEST_VDEC0;
			break;
		case DMX_PES_VIDEO1:
			filter->dest = LX_SDEC_PFLT_DEST_VDEC1;
			break;
		case DMX_PES_VIDEO2:
			filter->dest = LX_SDEC_PFLT_DEST_VDEC2;
			break;
		case DMX_PES_VIDEO3:
			filter->dest = LX_SDEC_PFLT_DEST_VDEC3;
			break;
		case DMX_PES_AUDIO0:
			filter->dest = LX_SDEC_PFLT_DEST_ADEC0;
			break;
		case DMX_PES_AUDIO1:
			filter->dest = LX_SDEC_PFLT_DEST_ADEC1;
			break;
		default:
			log_error("not supported pes_type(%d) for DECODER\n",
				  params->pes_type);
			return -EOPNOTSUPP;
		}
	}

	return 0;
}

static int set_dvb_filter_attr(struct lxdvb_dmx_filter *f)
{
	int ret;

	if (f->type == DEMUX_FILTER_TYPE_SEC) {
		f->payload_type = LX_SDEC_PAYLOAD_SECTION;
		f->stream_type = LX_SDEC_STREAM_TYPE_SECTION;
		f->dest = LX_SDEC_PFLT_DEST_BUFFER;
		f->pid = f->params.sec.pid;
	} else if (f->type == DEMUX_FILTER_TYPE_TEMI) {
		f->payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
		f->stream_type = LX_SDEC_STREAM_TYPE_NONE;
		f->dest = LX_SDEC_PFLT_DEST_TEMI;
		f->pid = f->params.sec.pid;
	} else {
		struct dmx_pes_filter_params *params = &f->params.pes;

		switch (params->output) {
		case DMX_OUT_DECODER:
			ret = set_dvb_dmx_filter_attr_decoder(f, params);
			if (ret)
				return ret;
			break;
		case DMX_OUT_TAP:	/* Output going to a memory buffer */
			f->stream_type = LX_SDEC_STREAM_TYPE_PES;
			f->payload_type = LX_SDEC_PAYLOAD_PES;
			f->dest = LX_SDEC_PFLT_DEST_BUFFER;
			break;
		case DMX_OUT_TS_TAP:	/* Output multiplexed into a new TS  */
			f->stream_type = LX_SDEC_STREAM_TYPE_NONE;
			f->payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
			f->dest = LX_SDEC_PFLT_DEST_DVR;
			break;
		case DMX_OUT_TSDEMUX_TAP:	/* Like TS_TAP but retrieved from the DMX device */
			log_error("not supported DMX_OUT_TSDEMUX_TAP\n");
			return -EOPNOTSUPP;
		default:
			log_error("invalid output(%d)\n", params->output);
			return -EINVAL;
		}
		f->pid = params->pid;
	}

	return 0;
}

static int dmx_ext_set_add_pid(struct lxdvb_dmx_filter *f, u16 pid)
{
	int rc;
	struct lxdvb_dmx_filter *child;

	CHECK_PARAM(!f, "no parent filter");
	CHECK_PARAM(f->state < DEMUX_FILTER_STATE_GO, "parent not started");
	CHECK_PARAM(f->child, "pid already added");
	CHECK_PARAM(pid >= NULL_PACKET_PID, "invalid pid(0x%x)", pid);

	if (!is_pidf_dest_vdec(f->dest)) {
		log_error("parent filter dest is not vdec\n");
		return -EINVAL;
	}

	rc = alloc_dvb_dmx_filter(f->channel, &child);
	CHECK_ERROR(rc, return rc, "no avaiable filter");

	/* set params value just for debugging */
	child->params.pes = f->params.pes;
	child->params.pes.pid = pid;

	child->type = f->type;
	child->pid = pid;
	child->dest = f->dest;
	child->payload_type = f->payload_type;
	child->stream_type = f->stream_type;
	child->flags |= DEMUX_FILTER_FLAG_CHILD;

	rc = set_dvb_filter_pid(child);
	if (rc) {
		log_error("set_dvb_filter_pid failed(%d)", rc);
		free_dvb_dmx_filter(child);
		return rc;
	}
	child->state = DEMUX_FILTER_STATE_GO;
	f->child = child;

	return 0;
}

/* scrambled status checker */
#define get_channel_of_tsh_filter_sched(sched) \
	container_of(sched, struct lxdvb_dmx_channel, tsh_filter_sched)

static void make_dvb_filter_of_tsh_filter(struct lxdvb_dmx_filter *dvb_filter,
					  struct dmx_tsh_filter *f)
{
	struct dmx_pes_filter_params *params = &dvb_filter->params.pes;

	/* set params value just for debugging */
	params->pid = f->pid;
	params->input = DMX_IN_FRONTEND;	/* ignored */
	params->output = DMX_OUT_DECODER;
	params->pes_type = DMX_PES_OTHER;

	dvb_filter->state = DEMUX_FILTER_STATE_SET;
	dvb_filter->type = DEMUX_FILTER_TYPE_PES;
	dvb_filter->pid = f->pid;
	dvb_filter->dest = LX_SDEC_PFLT_DEST_TSHEADER;
	dvb_filter->payload_type = LX_SDEC_PAYLOAD_UNKNOWN;
	dvb_filter->stream_type = LX_SDEC_STREAM_TYPE_NONE;
}


/**
 * This functions is called after mutex_lock(&filter_mutex) from sdec_filter.c
 * so DO NOT call the sdec function or use mutex here to avoid dead lock
 */
static int tsh_filter_sdec_callback(struct sdec_tsh_filter *f,
				    enum sdec_filter_status status,
				    u32 data, void *priv)
{
	struct dmx_tsh_filter_scheduler *sched = priv;

	 /* No need mutex or lock here, because sched->runner is only changed
	  * after cancel_sched_tsh_filter is called but this function call
	  * sdec_cancel_tsh_filter that use filter_mutex in sdec_filter.c,
	  * so it is guaranteed sched->runner is not changed during executing
	  * this function.
	  */
	memcpy(sched->data, &data, sizeof(sched->data));

	set_bit(TSH_FILTER_DONE, &sched->flags);
	wake_up(&sched->wq);

	return 0;
}

static int request_sched_tsh_filter(struct dmx_tsh_filter_scheduler *sched)
{
	int ret;
	struct sdec_tsh_filter_param param;
	struct lxdvb_dmx_channel *channel;

	param.pid = sched->runner->pid;
	param.callback = tsh_filter_sdec_callback;
	param.priv = sched;

	channel = get_channel_of_tsh_filter_sched(sched);

	ret = sdec_request_tsh_filter(channel->dev, &param, &sched->dev);
	CHECK_ERROR(ret, return ret, "sdec_request_tsh_filter failed");

	return 0;
}

static int cancel_sched_tsh_filter(struct dmx_tsh_filter_scheduler *sched)
{
	int ret;

	ret = sdec_cancel_tsh_filter(sched->dev);
	CHECK_ERROR(ret, return ret, "sdec_cancel_tsh_filter failed");

	return 0;
}

static void schedule_tsh_filter(struct dmx_tsh_filter_scheduler *sched)
{
	int ret;
	struct dmx_tsh_filter *f;

	if (test_bit(TSH_FILTER_WAKEUP, &sched->flags)) {
		clear_bit(TSH_FILTER_WAKEUP, &sched->flags);
		complete(&sched->woken);
	}

	if (sched->runner) {
		f = sched->runner;
		if (f->state == DEMUX_FILTER_STATE_GO) {
			if (test_bit(TSH_FILTER_DONE, &sched->flags)) {
				memcpy(f->data, sched->data, sizeof(f->data));
				f->done = 1;
				f->state = DEMUX_FILTER_STATE_DONE;
			}
		}

		/* f->state is changed from GO to others when the filter data
		 * is received in above code or USER calls free_tsh_filter */
		if (f->state != DEMUX_FILTER_STATE_GO) {
			cancel_sched_tsh_filter(sched);
			clear_bit(TSH_FILTER_DONE, &sched->flags);
			set_bit(TSH_FILTER_NO_RUNNER, &sched->flags);
			sched->runner = NULL;
		}
	}

	/* If there is no filter in the wait list, we will not change or
	 * stop the current running filter */
	if (list_empty(&sched->wait_list))
		return;

	/* In this case, sched->runner is the current running filter which did
	 * not receive the data for the TSH_FILTER_CHECK_INTERVAL time and
	 * it will be added at the end of the wait list to run again */
	if (sched->runner) {
		cancel_sched_tsh_filter(sched);
		list_add_tail(&sched->runner->node, &sched->wait_list);
	}

	do {
		/* Next filter to switch the running filter */
		f = list_first_entry(&sched->wait_list,
				     struct dmx_tsh_filter, node);

		/* The next filter is removed from the wait list
		 * and set as a runner */
		list_del(&f->node);
		sched->runner = f;
		ret = request_sched_tsh_filter(sched);
		if (ret) {
			log_error("request_sched_tsh_filter failed");
			set_bit(TSH_FILTER_NO_RUNNER, &sched->flags);
			sched->runner = NULL;
			f->state = DEMUX_FILTER_STATE_ERROR;
		} else {
			clear_bit(TSH_FILTER_NO_RUNNER, &sched->flags);
			break;
		}
	} while (!list_empty(&sched->wait_list));
}

static int tsh_filter_sched_condition(struct dmx_tsh_filter_scheduler *sched)
{
	if (test_bit(TSH_FILTER_DONE, &sched->flags) ||
	    test_bit(TSH_FILTER_WAKEUP, &sched->flags) ||
	    test_bit(TSH_FILTER_SHOULD_STOP, &sched->flags))
		return 1;

	return 0;
}

static void tsh_filter_sched_wait(struct dmx_tsh_filter_scheduler *sched)
{
	if (test_bit(TSH_FILTER_NO_RUNNER, &sched->flags)) {
		dprintk("%s - no runner\n", __func__);
		wait_event(sched->wq, tsh_filter_sched_condition(sched));
	} else {
		wait_event_timeout(sched->wq,
				   tsh_filter_sched_condition(sched),
				   msecs_to_jiffies(TSH_FILTER_CHECK_INTERVAL));
	}

	/* sleep until kthread_stop is called */
	if (test_bit(TSH_FILTER_SHOULD_STOP, &sched->flags)) {
		/* The schedule() function is not safe from kthread_stop()
		 * deadlock if this function is called after kthread_stop */
		schedule_timeout_interruptible(msecs_to_jiffies(50));
	}
}

static int tsh_filter_thread(void *data)
{
	struct dmx_tsh_filter_scheduler *sched = data;
	bool frozen;

	log_tsh("%s - start\n", __func__);

	set_freezable();

	while (!kthread_freezable_should_stop(&frozen)) {
		mutex_lock(&sched->mutex);
		schedule_tsh_filter(sched);
		mutex_unlock(&sched->mutex);

		tsh_filter_sched_wait(sched);
	}

	log_tsh("%s - stop\n", __func__);

	return 0;
}

static int set_tsh_filter_pid(struct dmx_tsh_filter *f)
{
	int ret;
	struct lxdvb_dmx_channel *channel;

	channel = get_channel_of_tsh_filter_sched(f->sched);
	ret = alloc_dvb_dmx_filter(channel, &f->dvb_filter);
	if (ret) {
		log_error("alloc_dvb_dmx_filter failed(%d)", ret);
		return ret;
	}

	make_dvb_filter_of_tsh_filter(f->dvb_filter, f);

	ret = set_dvb_filter_pid(f->dvb_filter);
	if (ret) {
		log_error("set_dvb_filter_pid failed(%d)", ret);
		free_dvb_dmx_filter(f->dvb_filter);
		return ret;
	}

	return 0;
}

static void cancel_tsh_filter_pid(struct dmx_tsh_filter *f)
{
	cancel_dvb_filter_pid(f->dvb_filter);
	free_dvb_dmx_filter(f->dvb_filter);
}

static int start_tsh_filter(struct dmx_tsh_filter *f)
{
	int ret;
	struct lxdvb_dmx_channel *channel;
	struct dmx_tsh_filter_scheduler *sched = f->sched;

	ret = set_tsh_filter_pid(f);
	if (ret) {
		log_error("set_tsh_filter_pid failed(%d)", ret);
		return ret;
	}

	mutex_lock(&sched->mutex);

	log_tsh("%s(0x%04x)", __func__, f->pid);

	if (sched->users == 0) {
		sched->flags = 0; /* clear all flags */
		channel = get_channel_of_tsh_filter_sched(sched);
		sched->thread = kthread_run(tsh_filter_thread, sched,
					    "tsh_filter[%d]", channel->idx);
		if (IS_ERR(sched->thread)) {
			log_error("can't create kthread\n");
			ret = PTR_ERR(sched->thread);
			sched->thread = NULL;
		}
	} else {
		/* TSH_FILTER_NO_RUNNER bit means there is no runner in
		 * scheduler, and it may wait for the event in
		 * tsh_filter_sched_wait function */
		if (test_bit(TSH_FILTER_NO_RUNNER, &sched->flags)) {
			set_bit(TSH_FILTER_WAKEUP, &sched->flags);
			wake_up(&sched->wq);
		}
	}

	if (!ret) {
		f->state = DEMUX_FILTER_STATE_GO;
		list_add_tail(&f->node, &sched->wait_list);
		sched->users++;
	}
	mutex_unlock(&sched->mutex);

	if (ret) {
		cancel_tsh_filter_pid(f);
		return ret;
	}

	return 0;
}

static void stop_tsh_filter(struct dmx_tsh_filter *f)
{
	struct dmx_tsh_filter_scheduler *sched = f->sched;
	struct task_struct *thread = NULL;

	if (f->state < DEMUX_FILTER_STATE_GO)
		return;

	mutex_lock(&sched->mutex);

	log_tsh("%s(0x%04x)", __func__, f->pid);

	if (sched->runner == f) {
		f->state = DEMUX_FILTER_STATE_ALLOCATED;
		set_bit(TSH_FILTER_WAKEUP, &sched->flags);
		wake_up(&sched->wq);
		reinit_completion(&sched->woken);
		mutex_unlock(&sched->mutex);

		wait_for_completion(&sched->woken);

		mutex_lock(&sched->mutex);
	} else {
		if (f->state == DEMUX_FILTER_STATE_GO)
			list_del(&f->node);

		f->state = DEMUX_FILTER_STATE_ALLOCATED;
	}
	sched->users--;

	if (sched->users == 0) {
		/* thread must be out of the mutex, almost in wait event
		 *
		 */
		set_bit(TSH_FILTER_SHOULD_STOP, &sched->flags);
		wake_up(&sched->wq);

		thread = sched->thread;
	}

	mutex_unlock(&sched->mutex);

	/* start and stop functions are protected in upper layer and
	 * kthread_stop should be called after mutex_unlock to avoid dead lock.
	 * Even if thread is in sleep mode, it will be woken up by kthread_stop
	 * because this function call wake_up_process */
	if (thread)
		kthread_stop(thread);

	cancel_tsh_filter_pid(f);
}

static int alloc_tsh_filter(struct lxdvb_dmx_channel *channel, u16 pid,
			    struct dmx_tsh_filter **filter)
{
	struct dmx_tsh_filter *f = NULL;
	int i;

	for (i = 0; i < channel->num_tsh_filter; i++) {
		if (channel->tsh_filter[i].state == DEMUX_FILTER_STATE_FREE) {
			f = &channel->tsh_filter[i];
			break;
		}
	}

	if (!f)
		return -EBUSY;

	f->state = DEMUX_FILTER_STATE_ALLOCATED;
	f->sched = &channel->tsh_filter_sched;
	f->pid = pid;
	f->done = 0;

	*filter = f;

	return 0;
}

static void free_tsh_filter(struct dmx_tsh_filter *f)
{
	stop_tsh_filter(f);
	f->state = DEMUX_FILTER_STATE_FREE;
}

static int dmx_ext_set_request_scrambled(struct lxdvb_dmx_fh *fh, u16 pid)
{
	int ret;
	struct dmx_tsh_filter *f = fh->tsh_filter;

	if (f) {
		log_error("already requested - pid=0x%x", f->pid);
		return -EBUSY;
	}

	ret = alloc_tsh_filter(fh->channel, pid, &f);
	CHECK_ERROR(ret, goto err_alloc, "alloc_tsh_filter failed");

	ret = start_tsh_filter(f);
	CHECK_ERROR(ret < 0, goto err_start, "start_tsh_filter failed");

	fh->tsh_filter = f;

	return 0;

err_start:
	free_tsh_filter(f);
err_alloc:

	return ret;
}

static int dmx_ext_set_cancel_scrambled(struct lxdvb_dmx_fh *fh)
{
	struct dmx_tsh_filter *f = fh->tsh_filter;

	if (!f) {
		log_warning("not requested scrambled check");
		return -EINVAL;
	}

	free_tsh_filter(f);
	fh->tsh_filter = NULL;

	return 0;
}

static int dmx_ext_get_check_scrambled(struct lxdvb_dmx_fh *fh, s64 *status)
{
	struct dmx_tsh_filter *f = fh->tsh_filter;

	if (!f) {
		log_warning("not requested scrambled check");
		return -EINVAL;
	}

	if (f->done) {
		u8 tsc = (f->data[3] >> 6) & 0x3;
		*status = tsc ? SCRMB_STATUS_SCRAMBLED : SCRMB_STATUS_CLEAR;
	} else {
		*status = SCRMB_STATUS_NOT_DETECTED;
	}

	return 0;
}

static int dmx_ext_get_request_scrambled(struct lxdvb_dmx_fh *fh, s64 *pid)
{
	struct dmx_tsh_filter *f = fh->tsh_filter;

	if (!f) {
		log_warning("not requested scrambled check");
		return -EINVAL;
	}

	*pid = f->pid;

	return 0;
}

/* descrambler */
static int dmx_ext_set_desc_type(struct lxdvb_dmx_channel *channel,
				 enum dmx_ext_dscrmb_type type)
{
	int rc;
	struct lx_sdec_desc_config param = {0};
	enum lxdvb_dmx_desc_algo_mode algo_mode = DEMUX_ALGO_LEGACY;

	log_noti("%s(type:%s)", __func__, demux_desc_type_str(type));

	param.cas_mode = LX_SDEC_DESC_CAS_NORMAL;

	switch (type) {
	case DMX_EXT_DSCRMB_TYPE_BCAS:
		param.cas_type = LX_SDEC_MULTI2;
		param.blk_mode = LX_SDEC_CBC;
		param.res_mode = LX_SDEC_OFB;
		param.key_size = LX_SDEC_KEY_256BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_CHANNEL_PID;
		break;

	case DMX_EXT_DSCRMB_TYPE_CI_AES_ECP:
	case DMX_EXT_DSCRMB_TYPE_CI_AES:
		if (type == DMX_EXT_DSCRMB_TYPE_CI_AES_ECP) {
			algo_mode = DEMUX_ALGO_ECP;
			param.cas_mode = LX_SDEC_DESC_CAS_ECP;
		}

		param.cas_type = LX_SDEC_AES;
		param.blk_mode = LX_SDEC_CBC;
		param.res_mode = LX_SDEC_CLEAR;
		param.key_size = LX_SDEC_KEY_128BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_CHANNEL;
		break;
	case DMX_EXT_DSCRMB_TYPE_CI_DES_ECP:
	case DMX_EXT_DSCRMB_TYPE_CI_DES:
		if (type == DMX_EXT_DSCRMB_TYPE_CI_DES_ECP) {
			algo_mode = DEMUX_ALGO_ECP;
			param.cas_mode = LX_SDEC_DESC_CAS_ECP;
		}

		param.cas_type = LX_SDEC_DES;
		param.blk_mode = LX_SDEC_ECB;
		param.res_mode = LX_SDEC_CLEAR;
		param.key_size = LX_SDEC_KEY_64BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_CHANNEL;
		break;

	case DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS:
		if (channel->desc_type == type) // preventing pid clear
			return 0;

		algo_mode = DEMUX_ALGO_XCAS;
		param.cas_mode = LX_SDEC_DESC_CAS_XCAS;

		param.cas_type = LX_SDEC_AES;
		param.blk_mode = LX_SDEC_CBC;
		param.res_mode = LX_SDEC_OFB;
		param.key_size = LX_SDEC_KEY_128BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_PID;
		break;
	case DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2:
		if (channel->desc_type == type) //preventing pid clear
			return 0;

		algo_mode = DEMUX_ALGO_XCAS;
		param.cas_mode = LX_SDEC_DESC_CAS_XCAS;

		param.cas_type = LX_SDEC_CSA;
		param.blk_mode = LX_SDEC_CBC;
		param.res_mode = LX_SDEC_CLEAR;
		param.key_size = LX_SDEC_KEY_64BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_PID;
		break;
	case DMX_EXT_DSCRMB_TYPE_PVR:
	case DMX_EXT_DSCRMB_TYPE_EMB_CSA_V3:
		log_error("Not supported type - %d", type);
		return -EINVAL;
	case DMX_EXT_DSCRMB_TYPE_NONE:
		param.cas_type = LX_SDEC_BYPASS;
		/* will be ignored */
		param.blk_mode = LX_SDEC_ECB;
		param.res_mode = LX_SDEC_CLEAR;
		param.key_size = LX_SDEC_KEY_64BIT;
		param.desc_mode = LX_SDEC_DESC_MODE_CHANNEL;
		break;
	default:
		log_error("invalid type(%d)", type);
		return -EINVAL;
	}

	if (channel->desc_mode == LX_SDEC_DESC_MODE_CHANNEL_PID ||
	    channel->desc_mode == LX_SDEC_DESC_MODE_PID)
		dmx_desc_disable_all_pid(channel);

	rc = sdec_init_descrambler(channel->dev, &param);
	CHECK_ERROR(rc, return rc, "sdec_init_descrambler failed(%d)", rc);

	channel->desc_type = type;
	channel->desc_mode = param.desc_mode;
	channel->algo_mode = algo_mode;

	return 0;
}

static int dmx_ext_set_desc_pid(struct lxdvb_dmx_fh *fh,
				struct dmx_ext_dscrmb_pid *pid)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_dmx_filter *f;
	enum lx_sdec_desc_mode desc_mode = channel->desc_mode;
	bool enable;

	log_desc("%s(ch:%d,0x%x,%d)", __func__, channel->idx, pid->pid,
		 pid->bEnable);

	if (desc_mode != LX_SDEC_DESC_MODE_CHANNEL_PID &&
	    desc_mode != LX_SDEC_DESC_MODE_PID) {
		log_error("wrong mode(%d) for set_desc_pid", desc_mode);
		return -EIO;
	}

	f = fh->filter;
	if (!f) {
		log_error("dmx filter is not allocated(0x%02x)", pid->pid);
		return -EIO;
	}

	if (f->pid != pid->pid) {
		log_error("pid is not matched (0x%02x:0x%02x)",
			  f->pid, pid->pid);
		return -EIO;
	}

	enable = pid->bEnable ? true : false;
	if (f->desc_enable == enable) {
		log_debug("duplicated operation-(pid:0x%02x:%d)",
			  f->pid, pid->bEnable);
		return 0;
	}
	if (enable && desc_mode == LX_SDEC_DESC_MODE_PID) {
		log_error("pid mode does not suppport enable desc");
		return -EIO;
	}

	__dmx_set_desc_pid_enable(f, enable);

	return 0;
}

#define KEY_SIZE_64BIT	8
#define KEY_SIZE_128BIT	16
#define KEY_SIZE_256BIT	32
static int set_bcas_desc_key(struct lxdvb_dmx_fh *fh,
			     struct dmx_ext_dscrmb_key *key)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lx_sdec_desc_key param;
	u8 value[32];
	void __user *user_ptr;
	enum dmx_ext_dscrmb_key_type t;
	int rc, s;

	s = key->key_size;
	t = key->key_type;
	user_ptr = te_ioctl_get_user_ptr(key->key);
	rc = copy_from_user(value, user_ptr, s);
	CHECK_ERROR(rc, return -EFAULT, "copy_from_user failed");

	memset(&param, 0, sizeof(param));
	param.location = LX_SDEC_KEY_FROM_MSG;
	param.size = s;
	param.pidf_id = LX_SDEC_ALL_PID_FILTER;

	switch (t) {
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN:
		if (s != KEY_SIZE_64BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_EVEN;
		memcpy(param.key, value, param.size);
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODD:
		if (s != KEY_SIZE_64BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_ODD;
		memcpy(param.key, value, param.size);
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN_ODD:
		if (s != KEY_SIZE_128BIT)
			goto inval_param;

		param.size = KEY_SIZE_64BIT;
		param.type = LX_SDEC_KEY_TYPE_ODD;
		memcpy(param.key, &value[0], KEY_SIZE_64BIT);

		rc = sdec_set_descrambler_key(channel->dev, &param);
		CHECK_ERROR(rc, return rc, "sdec_set_descrambler_key failed");

		param.type = LX_SDEC_KEY_TYPE_EVEN;
		memcpy(param.key, &value[KEY_SIZE_64BIT], KEY_SIZE_64BIT);
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_EVENIV:
		if (s != KEY_SIZE_64BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_EVEN_IV;
		memcpy(param.key, value, param.size);
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODDIV:
		if (s != KEY_SIZE_64BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_ODD_IV;
		memcpy(param.key, value, param.size);
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_CBC:
		if (s != KEY_SIZE_64BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_ODD_IV;
		memcpy(param.key, value, param.size);

		rc = sdec_set_descrambler_key(channel->dev, &param);
		CHECK_ERROR(rc, return rc, "sdec_set_descrambler_key failed");

		param.type = LX_SDEC_KEY_TYPE_EVEN_IV;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_SYSKEY:
		if (s != KEY_SIZE_256BIT)
			goto inval_param;

		param.type = LX_SDEC_KEY_TYPE_MULTI2;
		memcpy(param.key, value, param.size);
		break;
	default:
		goto inval_param;
	}

	rc = sdec_set_descrambler_key(channel->dev, &param);
	CHECK_ERROR(rc, return rc, "sdec_set_descrambler_key failed");

	if (channel->desc_mode == LX_SDEC_DESC_MODE_PID) {
		if (param.pidf_id != LX_SDEC_ALL_PID_FILTER)
			fh->filter->desc_enable = true;
	}

	return 0;

inval_param:
	log_error("invalid parameter. type:%s(%d), size(%d)",
		  demux_desc_key_type_str(t), t, s);
	return -EINVAL;
}

static int set_ci_desc_key(struct lxdvb_dmx_fh *fh,
			   struct dmx_ext_dscrmb_key *key)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lx_sdec_desc_key param;
	u8 value[32];
	void __user *user_ptr;
	int rc, s;

	s = key->key_size;
	if (s != KEY_SIZE_64BIT && s != KEY_SIZE_128BIT)
		goto inval_param;

	user_ptr = te_ioctl_get_user_ptr(key->key);
	rc = copy_from_user(value, user_ptr, s);
	CHECK_ERROR(rc, return -EFAULT, "copy_from_user failed");

	memset(&param, 0, sizeof(param));
	param.location = LX_SDEC_KEY_FROM_MSG;
	param.size = key->key_size;
	param.pidf_id = LX_SDEC_ALL_PID_FILTER;

	memcpy(param.key, value, s);

	switch (key->key_type) {
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN:
		param.type = LX_SDEC_KEY_TYPE_EVEN;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODD:
		param.type = LX_SDEC_KEY_TYPE_ODD;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_EVENIV:
		param.type = LX_SDEC_KEY_TYPE_EVEN_IV;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODDIV:
		param.type = LX_SDEC_KEY_TYPE_ODD_IV;
		break;
	default:
		goto inval_param;
	}
	rc = sdec_set_descrambler_key(channel->dev, &param);
	CHECK_ERROR(rc, return rc, "sdec_set_descrambler_key failed");

	return 0;

inval_param:
	log_error("invalid parameter. type:%s(%d), size(%d)",
		  demux_desc_key_type_str(key->key_type), key->key_type, s);
	return -EINVAL;
}

static int set_data_desc_key(struct lxdvb_dmx_fh *fh,
			    struct dmx_ext_dscrmb_key *key)
{
	void *data = NULL;
	struct lxdvb_dmx_channel *channel = fh->channel;
	enum lx_sdec_cas_type cas_type;
	enum lx_sdec_desc_key_type key_type;
	bool use_ioctl_data = false;
	void __user *user_ptr;
	int rc, s;

	s = key->key_size;
	if (s != SIZE_OF_DATA_NOTI)
		goto inval_param;
	if (s)
		use_ioctl_data = true;

	if (use_ioctl_data) {
		CHECK_ERROR(key->key == NULL, return -EINVAL, "Null Data");

		data = kmalloc(s, GFP_KERNEL);
		CHECK_ERROR(!data, return -ENOMEM, "Out of memory");

		user_ptr = te_ioctl_get_user_ptr(key->key);
		rc = copy_from_user(data, user_ptr, s);
		CHECK_ERROR(rc, goto error, "copy_from_user failed - %d", rc);
	}

	switch(channel->desc_type) {
	case DMX_EXT_DSCRMB_TYPE_CI_DES_ECP:
		cas_type = LX_SDEC_DES;
		break;
	case DMX_EXT_DSCRMB_TYPE_CI_AES_ECP:
		cas_type = LX_SDEC_AES;
		break;
	default:
		goto inval_param;
	}

	switch (key->key_type) {
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN:
		key_type = LX_SDEC_KEY_TYPE_EVEN;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODD:
		key_type = LX_SDEC_KEY_TYPE_ODD;
		break;
	default:
		goto inval_param;
	}

	/* send the information to sdec */
	rc = sdec_filter_noti_data_info(channel->dev, data, false);
	CHECK_ERROR(rc, , "sdec_filter_noti_data_info failed %d", rc);

	rc = sdec_desc_noti_data_info(channel->dev, cas_type, key_type, data,
				      true);
	CHECK_ERROR(rc, goto error, "sdec_desc_noti_key failed %d", rc);

	if (use_ioctl_data) {
		rc = copy_to_user(user_ptr, data, s);
		CHECK_ERROR(rc, goto error, "copy_to_user failed %d", rc);

		kfree(data);
	}

	return 0;

inval_param:
	log_error("invalid parameter. type:%s(%d), size(%d)",
		  demux_desc_key_type_str(key->key_type), key->key_type, s);
	rc = -EINVAL;
error:
	if (data)
		kfree(data);
	return rc;
}

static int check_xcas_input_validation(struct lxdvb_dmx_fh *fh,
				       struct dmx_ext_dscrmb_key *key)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	enum lx_sdec_desc_mode desc_mode = channel->desc_mode;
	struct lxdvb_dmx_filter *f = fh->filter;
	struct lxdvb_dmx_filter *dmxf;
	struct list_head *dvb_list;

	if (desc_mode != LX_SDEC_DESC_MODE_CHANNEL_PID &&
	    desc_mode != LX_SDEC_DESC_MODE_PID) {
		log_error("wrong mode(%d)", desc_mode);
		return -EIO;
	}

	if (!key->key) {
		log_error("Null data");
		return -EINVAL;
	}

	if (!key->key_size) {
		log_error("zero key size");
		return -EINVAL;
	}

	if (!f) {
		log_error("dmx filter not allocated");
		return -EFAULT;
	}

	dvb_list = &f->pid_filter->dvb_filters;
	list_for_each_entry (dmxf, dvb_list, pid_filter_entry) {
		if (f != dmxf && dmxf->xcas_desc_enable) {
			log_error("pid 0x%04x already has keys by other fh",
				  f->pid);
			return -EBUSY;
		}
	}

	return 0;
}

static int set_xcas_desc_key(struct lxdvb_dmx_fh *fh,
			     struct dmx_ext_dscrmb_key *key)
{
	void *data = NULL;
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_dmx_filter *f;
	struct sdec_send_noti_param p;
	int rc;
	void __user *user_ptr;

	rc = check_xcas_input_validation(fh, key);
	if (rc)
		return rc;

	f = fh->filter;

	data = kmalloc(key->key_size, GFP_KERNEL);
	CHECK_ERROR(!data, return -ENOMEM, "Out of Memory");

	user_ptr = te_ioctl_get_user_ptr(key->key);
	rc = copy_from_user(data, user_ptr, key->key_size);
	CHECK_ERROR(rc, goto error, "copy_from_user failed - %d", rc);

	// Only MCU0 need this information
	switch(channel->desc_type) {
	case DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS:
		p.cas = LX_SDEC_AES;
		break;
	case DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2:
		p.cas = LX_SDEC_CSA;
		break;
	default:
		goto inval_param;
	}

	switch (key->key_type) {
	case DMX_EXT_DSCRMB_KEY_TYPE_EVEN:
		p.key = LX_SDEC_KEY_TYPE_EVEN;
		break;
	case DMX_EXT_DSCRMB_KEY_TYPE_ODD:
		p.key = LX_SDEC_KEY_TYPE_ODD;
		break;
	default:
		goto inval_param;
	}

	p.command_type = SDEC_SEND_TYPE_KEY;
	p.len = key->key_size;
	p.pid = f->pid;
	p.data = data;

	/* No need to update MCU1 (section filter) */

	rc = sdec_desc_noti_xcas_data(channel->dev, &p);
	CHECK_ERROR(rc, goto error, "sdec_desc_noti_xcas_data failed %d", rc);

	rc = copy_to_user(user_ptr, data, p.len);
	CHECK_ERROR(rc, goto error, "copy_to_user failed %d", rc);

	key->key_size = p.len;
	kfree(data);

	f->xcas_desc_enable = true;

	return 0;

inval_param:
	log_error("invalid parameter. type:%s(%d)",
		  demux_desc_key_type_str(key->key_type), key->key_type);
	rc = -EINVAL;
error:
	if (data)
		kfree(data);
	return rc;
}

static int dmx_ext_set_desc_key(struct lxdvb_dmx_fh *fh,
				struct dmx_ext_dscrmb_key *key)
{
	enum dmx_ext_dscrmb_type type = fh->channel->desc_type;
	int rc;

	log_desc("%s(type:%s,key_type:%s,size:%d)", __func__,
		 demux_desc_type_str(type),
		 demux_desc_key_type_str(key->key_type), key->key_size);

	if (type == DMX_EXT_DSCRMB_TYPE_NONE) {
		log_error("desc_type is not selected; Use "
			  "DMX_EXT_CID_DSCRMB_TYPE first");
		return -EFAULT;
	}

	if (type == DMX_EXT_DSCRMB_TYPE_CI_AES_ECP ||
	    type == DMX_EXT_DSCRMB_TYPE_CI_DES_ECP) {
		return set_data_desc_key(fh, key);
	} else if (type == DMX_EXT_DSCRMB_TYPE_EMB_AES_ATIS ||
		   type == DMX_EXT_DSCRMB_TYPE_EMB_CSA_V2) {
		return set_xcas_desc_key(fh, key);
	}

	CHECK_PARAM(key->key_size > KEY_SIZE_256BIT,
		    "invalid key_size(%d) type:%s, key_type:%s",
		    key->key_size, demux_desc_type_str(type),
		    demux_desc_key_type_str(key->key_type));

	if (type == DMX_EXT_DSCRMB_TYPE_BCAS) {
		rc = set_bcas_desc_key(fh, key);
	} else {
		rc = set_ci_desc_key(fh, key);
	}

	return rc;
}

static int dmx_ext_set_xcas_data(struct lxdvb_dmx_channel *channel, void *data,
				 u32 *len)
{
	struct sdec_send_noti_param p;
	int rc;

	CHECK_ERROR(!data, return -EFAULT, "Null data");
	CHECK_ERROR(*len == 0, return -EINVAL, "zero length");

	p.command_type = SDEC_SEND_TYPE_PVR_PES;
	p.len = *len;
	p.data = data;

	rc = sdec_filter_noti_xcas_data(channel->dev, &p);
	CHECK_ERROR(rc, , "sdec_filtr_noti_xcas_data failed %d", rc);

	rc = sdec_desc_noti_xcas_data(channel->dev, &p);
	CHECK_ERROR(rc, return rc, "sdec_desc_noti_xcas failed %d", rc);

	*len = p.len; // length should be modified by mcu
	return 0;
}

static int dmx_ext_set_data_info(struct lxdvb_dmx_channel *channel, void *data,
				 u32 *len)
{
	int rc;

	if (*len != SIZE_OF_DATA_NOTI) {
		log_error("wrong length: %d", *len);
		return -EINVAL;
	}

	/* send the information to sdec */
	rc = sdec_filter_noti_data_info(channel->dev, data, true);
	CHECK_ERROR(rc, , "noti failed (filter)");

	rc = sdec_desc_noti_data_info(channel->dev, 0, 0, data, false);
	CHECK_ERROR(rc, return rc, "noti failed (desc)");

	return 0;
}

static int dmx_ext_set_usb_pcr_channel(struct lxdvb_dmx_fh *fh,
				       u8 idx)
{
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_demux *dmx = channel->dmx;

	if (idx >= dmx->num_channel) {
		log_error("[%d]invalid channel selection[%d]",
			  channel->idx, idx);
		return -EINVAL;
	}

	channel->sdt = &dmx->channels[idx]; // register for channel

	log_noti("%s(dmx:%d sdt:%d)", __func__, channel->idx, idx);
	return 0;
}

static int dmx_ext_get_usb_pcr_channel(struct lxdvb_dmx_channel *channel,
				       s64 *idx)
{
	if (channel->sdt) {
		*idx = channel->sdt->idx;
	} else {
		*idx = -1;
	}

	return 0;
}

/* dvb demux ioctl functions */
static int dvb_dmx_stop(struct lxdvb_dmx_filter *filter)
{
	if (filter->state < DEMUX_FILTER_STATE_GO)
		return 0;

	if (filter->dest == LX_SDEC_PFLT_DEST_STC) {
		struct te_config *cfg = te_get_config();
		cancel_dvb_filter_pcr_pid(filter);
		if (cfg->no_stcc_bug) {
			cancel_dvb_filter_pid(filter);
		}
	} else {
		if (filter->type == DEMUX_FILTER_TYPE_TEMI) {
			cancel_dvb_temi_filter(filter);
		} else if (filter->stream_type != LX_SDEC_STREAM_TYPE_NONE) {
			cancel_dvb_filter_stream(filter);
		}
		cancel_dvb_filter_pid(filter);
		if (filter->child) {
			cancel_dvb_filter_pid(filter->child);
			free_dvb_dmx_filter(filter->child);
			filter->child = NULL;
		}
	}
	filter->state = DEMUX_FILTER_STATE_SET;

	return 0;
}

static int dvb_dmx_start(struct lxdvb_dmx_filter *filter)
{
	int ret;

	if (filter->state < DEMUX_FILTER_STATE_SET)
		return -EINVAL;

	if (filter->state >= DEMUX_FILTER_STATE_GO)
		dvb_dmx_stop(filter);

	ret = set_dvb_filter_attr(filter);
	if (ret) {
		log_error("set_dvb_filter_attr failed(%d)", ret);
		return ret;
	}

	if (filter->dest == LX_SDEC_PFLT_DEST_STC) {
		struct te_config *cfg = te_get_config();
		if (cfg->no_stcc_bug) {
			ret = set_dvb_filter_pid(filter);
			if (ret) {
				log_error("set_dvb_filter_pid failed(%d)", ret);
				return ret;
			}
		}
		ret = set_dvb_filter_pcr_pid(filter);
		if (ret) {
			log_error("set_dvb_filter_pcr_pid failed(%d)", ret);
			return ret;
		}
	} else {
		ret = set_dvb_filter_pid(filter);
		if (ret) {
			log_error("set_dvb_filter_pid failed(%d)", ret);
			return ret;
		}

		if (filter->type == DEMUX_FILTER_TYPE_TEMI) {
			ret = request_dvb_temi_filter(filter);
			if (ret) {
				log_error("request_dvb_temi_filter failed");
				__cancel_dvb_filter_pid(filter);
				return ret;
			}
		} else if (filter->stream_type != LX_SDEC_STREAM_TYPE_NONE) {
			ret = request_dvb_filter_stream(filter);
			if (ret) {
				log_error("request_dvb_filter_stream failed");
				__cancel_dvb_filter_pid(filter);
				return ret;
			}
		}
	}
	filter->state = DEMUX_FILTER_STATE_GO;

	return 0;
}

static int demux_open(struct inode *inode, struct file *file)
{
	struct dvb_device *dvbdev = file->private_data;
	struct lxdvb_dmx_channel *channel = dvbdev->priv;
	struct lxdvb_demux *dmx = channel->dmx;
	struct te_device *tdev = dmx->tdev;
	struct lxdvb_dmx_fh *fh;

	fh = kzalloc(sizeof(*fh), GFP_KERNEL);
	if (!fh)
		return -ENOMEM;

	if (mutex_lock_interruptible(&dmx->mutex)) {
		kfree(fh);
		return -ERESTARTSYS;
	}

	if (channel->exit) {
		kfree(fh);
		mutex_unlock(&dmx->mutex);
		return -ENODEV;
	}

	fh->channel = channel;

	// TODO: add extra open functions if necessary

	file->private_data = fh;

	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DEMUX);
	dvbdev->users++;

	log_trace("demux_open - fh(%p) users(%d)\n", fh, dvbdev->users);

	mutex_unlock(&dmx->mutex);

	return 0;
}

static int demux_filter_free(struct lxdvb_dmx_filter *filter)
{
	mutex_lock(&filter->mutex);

	if (filter->state >= DEMUX_FILTER_STATE_GO)
		dvb_dmx_stop(filter);

	free_dvb_dmx_filter(filter);

	mutex_unlock(&filter->mutex);

	return 0;
}

static int dvb_dmx_set_filter(struct lxdvb_dmx_filter *filter,
			      struct dmx_sct_filter_params *params)
{
	log_filter("%s(0x%04x,flags=%02x,timeout=%d)\n",
		   __func__, params->pid, params->flags, params->timeout);

	dvb_dmx_stop(filter);

	filter->type = DEMUX_FILTER_TYPE_SEC;

	memcpy(&filter->params, params, sizeof(struct dmx_sct_filter_params));

	filter->state = DEMUX_FILTER_STATE_SET;

	if (params->flags & DMX_IMMEDIATE_START)
		return dvb_dmx_start(filter);

	return 0;
}

static int dvb_dmx_set_pes_filter(struct lxdvb_dmx_filter *filter,
				  struct dmx_pes_filter_params *params)
{
	dvb_dmx_stop(filter);

	if ((unsigned int)params->pes_type > DMX_PES_OTHER)
		return -EINVAL;

	filter->type = DEMUX_FILTER_TYPE_PES;

	memcpy(&filter->params, params, sizeof(struct dmx_pes_filter_params));

	filter->state = DEMUX_FILTER_STATE_SET;

	if (params->flags & DMX_IMMEDIATE_START)
		return dvb_dmx_start(filter);

	return 0;
}

static int dvb_dmx_set_temi_filter(struct lxdvb_dmx_filter *filter,
				   struct dmx_sct_filter_params *params)
{
	log_filter("%s(0x%04x,flags=%02x,timeout=%d)\n",
		   __func__, params->pid, params->flags, params->timeout);

	dvb_dmx_stop(filter);

	filter->type = DEMUX_FILTER_TYPE_TEMI;

	memcpy(&filter->params, params, sizeof(struct dmx_sct_filter_params));

	filter->state = DEMUX_FILTER_STATE_SET;

	if (params->flags & DMX_IMMEDIATE_START)
		return dvb_dmx_start(filter);

	return 0;
}

static int dvb_dmx_get_virtual_stc(struct lxdvb_dmx_channel *channel,
				   struct dmx_stc *stc)
{
	int ret;
	struct lx_sdec_clk_value value;
	struct lxdvb_dmx_channel *sdt_channel = channel->sdt;

	ret = sdec_get_stc(sdt_channel->dev, &value);
	if (ret) {
		log_error("sdec_get_stc failed(%d)", ret);
		return ret;
	}

	stc->num = channel->idx;
	stc->base = 1;
	stc->stc = (u64)value.base_32 << 32 | value.base_31_0;

	log_debug("[%d] stc:0x%llx", stc->num, stc->stc);
	return 0;
}

static int dvb_dmx_get_stc(struct lxdvb_dmx_channel *channel,
			   struct dmx_stc *stc)
{
	int ret;
	struct lx_sdec_clk_value value;

	if (channel->pcr.is_virtual)
		return dvb_dmx_get_virtual_stc(channel, stc);

	ret = sdec_get_stc(channel->dev, &value);
	if (ret) {
		log_error("sdec_get_stc failed(%d)", ret);
		return ret;
	}
	stc->num = channel->idx;
	stc->base = 1;
	stc->stc = (u64)value.base_32 << 32 | value.base_31_0;

	log_debug("[%d] stc:0x%llx", stc->num, stc->stc);
	return 0;
}

static int dvb_dmx_set_control(struct lxdvb_dmx_fh *fh,
			       struct dmx_ext_control *control)
{
	int ret = 0;
	struct lxdvb_dmx_channel *channel = fh->channel;
	enum dmx_country country;
	u8 num_of_tuner;

	switch (control->id) {
	case DMX_EXT_CID_PLATFORM:
		channel->dmx->param.platform = control->value64;
		break;

	case DMX_EXT_CID_NUMBER_OF_TUNERS:
		num_of_tuner = (u8)control->value64;
		log_noti("NUM_OF_TUNER:%d", num_of_tuner);

		if (num_of_tuner == channel->dmx->param.num_of_tuner) {
			break;
		}

		if (num_of_tuner == 3) {
			sdec_set_input_mux(channel->dmx->sdev,
					   TE_INPUT_MUX_3_SERIAL);
		}
		channel->dmx->param.num_of_tuner = num_of_tuner;
		break;

	case DMX_EXT_CID_COUNTRY:
		country = control->value64;
		log_noti("COUNTRY:%s", lxdvb_demux_country_str(country));

		if (country == channel->dmx->param.country) {
			break;
		}

		if (country == DMX_COUNTRY_JP) {
			sdec_set_input_mux(channel->dmx->sdev,
					   TE_INPUT_MUX_3_SERIAL);
		}
		channel->dmx->param.country = country;
		break;

	case DMX_EXT_CID_MODEL_NO:
		channel->dmx->param.model_no = (u32)control->value64;
		break;

	case DMX_EXT_CID_AFIFO:
		// do nothing
		break;

	case DMX_EXT_CID_INPUTSOURCE:
		ret = dmx_ext_set_inputsource(channel,
					      (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_PCR_ONOFF:
		ret = dmx_ext_set_pcr_onoff(channel, (int)control->value64);
		break;

	case DMX_EXT_CID_REQUEST_SCRMB:
		ret = dmx_ext_set_request_scrambled(fh, (u16)control->value64);
		break;

	case DMX_EXT_CID_CANCEL_SCRMB:
		ret = dmx_ext_set_cancel_scrambled(fh);
		break;

	case DMX_EXT_CID_DSCRMB_TYPE:
		ret = dmx_ext_set_desc_type(channel, (u32)control->value64);
		break;

	case DMX_EXT_CID_DSCRMB_PID:
		ret = dmx_ext_set_desc_pid(fh, (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_DSCRMB_KEY:
		ret = dmx_ext_set_desc_key(fh, (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_ADD_PID:
		ret = dmx_ext_set_add_pid(fh->filter, (u16)control->value64);
		break;
	case DMX_EXT_CID_SEND_DATA:
		ret = dmx_ext_set_data_info(channel, control->ptr,
					    &control->size);
		break;
	case DMX_EXT_CID_SEND_XCAS_DATA:
		ret = dmx_ext_set_xcas_data(channel, control->ptr,
					    &control->size);
		break;
	case DMX_EXT_CID_SDT_PORT_INFO:
		ret = dmx_ext_set_usb_pcr_channel(fh,
						  (u8)control->value64);
		break;
	case DMX_EXT_CID_AVSYNC_MODE:
		log_error("not support avsync_mode");
		ret = -ENOTTY;
		break;

	/* Nagra Extension (Test) */
	case DMX_EXT_CID_NAGRA_ALGO:
		ret = dmx_nagra_set_desc_type(channel,
					      (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_NAGRA_KEY:
		ret = dmx_nagra_set_desc_key(fh,
					     (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_NAGRA_SET_STATE:
		ret = dmx_nagra_set_state(fh, (void __force *)control->ptr);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int dvb_dmx_get_control(struct lxdvb_dmx_fh *fh,
			       struct dmx_ext_control *control)
{
	int ret = 0;
	struct lxdvb_dmx_channel *channel = fh->channel;

	switch (control->id) {
	case DMX_EXT_CID_PLATFORM:
		control->value64 = channel->dmx->param.platform;
		break;

	case DMX_EXT_CID_COUNTRY:
		control->value64 = channel->dmx->param.country;
		break;

	case DMX_EXT_CID_NUMBER_OF_TUNERS:
		control->value64 = channel->dmx->param.num_of_tuner;
		break;

	case DMX_EXT_CID_CHIP_ID:
		ret = -EPERM;
		break;

	case DMX_EXT_CID_PORT_NUM:
		control->value64 = channel->dmx->num_channel;
		break;

	case DMX_EXT_CID_INPUTSOURCE:
		ret = dmx_ext_get_inputsource(channel,
					      (void __force *)control->ptr);
		break;

	case DMX_EXT_CID_CHECK_SCRMB:
		ret = dmx_ext_get_check_scrambled(fh, &control->value64);
		break;

	case DMX_EXT_CID_PCR_ONOFF:
		ret = dmx_ext_get_pcr_onoff(channel, &control->value64);
		break;

	case DMX_EXT_CID_REQUEST_SCRMB:
		ret = dmx_ext_get_request_scrambled(fh, &control->value64);
		break;

	case DMX_EXT_CID_DSCRMB_TYPE:
		control->value64 = channel->desc_type;
		break;
	case DMX_EXT_CID_DSCRMB_PID:
		break;
	case DMX_EXT_CID_SDT_PORT_INFO:
		ret = dmx_ext_get_usb_pcr_channel(channel,
						  &control->value64);
		break;

	case DMX_EXT_CID_NAGRA_GET_STATUS:
		ret = dmx_nagra_get_desc_key_inserted(fh, &control->value64);
		break;

	case DMX_EXT_CID_NAGRA_GET_NONCE:
		ret = dmx_nagra_get_nonce(fh, (void __force *)control->ptr);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}

static ssize_t demux_read(struct file *file, char __user *buf,
			  size_t count, loff_t *ppos)
{
	struct lxdvb_dmx_fh *fh = file->private_data;
	struct lxdvb_dmx_filter *filter = fh->filter;
	int ret;

	if (!filter)
		return 0;

	if (mutex_lock_interruptible(&filter->mutex))
		return -ERESTARTSYS;

	if (filter->pbuf) {
		ret = te_pktbuf_io_read(filter->pbuf, buf, count,
					file->f_flags & O_NONBLOCK);
		if (ret == -EIO || ret == -ESTRPIPE) {
			int err = te_pktbuf_error(filter->pbuf);
			if (err)
				ret = err;
			te_pktbuf_flush(filter->pbuf);
		} else if (ret > 0) {
			filter->read_size += ret;
		}
	} else {
		ret = 0;
	}

	mutex_unlock(&filter->mutex);

	return ret;
}

static int get_kapi_user_ptr(void *priv, unsigned int cmd, void *arg,
			     struct te_ioctl_ptr_param *param)
{
	return 0;
}

static int demux_get_user_ptr(void *priv, unsigned int cmd, void *arg,
			      struct te_ioctl_ptr_param *param)
{
	int dir;
	struct dmx_ext_control *p;
	const struct dmx_lge_control_param *c;

	if (_IOC_TYPE(cmd) == TE_DVB_DEMUX_MAGIC)
		return get_kapi_user_ptr(priv, cmd, arg, param);

	switch (cmd) {
	case DMX_EXT_S_CTL:
	case DMX_EXT_G_CTL:
		p = arg;
		c = get_dmx_lge_control_param(p->id);
		if (p->id == DMX_EXT_CID_SEND_DATA ||
		    p->id == DMX_EXT_CID_DSCRMB_KEY ||
		    p->id == DMX_EXT_CID_SEND_XCAS_DATA) {
			dir = _IOC_RW;
		} else {
			dir = (cmd == DMX_EXT_S_CTL) ? _IOC_WRITE : _IOC_READ;
		}

		if (!c) {
			log_error("invalid dmx_ext_control id(%u)\n", p->id);
			return -EINVAL;
		}

		if (c->size != p->size) {
			log_error("size %u != %u of dmx_ext_control(%s)\n",
				  p->size, c->size, c->name);
			return -EINVAL;
		}

		if (!(c->dir & dir)) {
			log_error("invalid command of dmx_ext_control(%s)\n",
				  c->name);
			return -EINVAL;
		}

		if (p->size > 0) {
			param->user_ptr = te_ioctl_get_user_ptr(p->ptr);
			param->kernel_ptr = (void **)&p->ptr;
			param->size = p->size;
			param->dir = dir;
		}
		break;

	default:
		break;
	}

	return 0;
}

static int demux_do_ioctl_filter(struct lxdvb_dmx_fh *fh,
				 unsigned int cmd, void *parg)
{
	int ret;
	struct lxdvb_dmx_filter *filter;

	if (!fh->filter) {
		ret = alloc_dvb_dmx_filter(fh->channel, &fh->filter);
		if (ret) {
			log_error("no avaiable filter\n");
			return ret;
		}
	}
	filter = fh->filter;

	if (mutex_lock_interruptible(&filter->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case DMX_START:
		ret = dvb_dmx_start(filter);
		break;

	case DMX_STOP:
		ret = dvb_dmx_stop(filter);
		break;

	case DMX_SET_FILTER:
		ret = dvb_dmx_set_filter(filter, parg);
		break;

	case DMX_SET_PES_FILTER:
		ret = dvb_dmx_set_pes_filter(filter, parg);
		break;

	case DMX_SET_BUFFER_SIZE:
		ret = dvb_dmx_set_buffer_size(filter, (unsigned long)parg);
		break;

	case DMX_SET_TEMI_FILTER:
		ret = dvb_dmx_set_temi_filter(filter, parg);
		break;
	default:
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&filter->mutex);

	return ret;
}
/* will be removed. */
static int dmx_kapi_set_prokey(struct lxdvb_dmx_channel *channel,
			       struct te_dvb_demux_prokey_info *key)
{
	log_error("not supported (deprecated)");
	return -EPERM;
}

static int dmx_kapi_set_channel_input(struct lxdvb_dmx_channel *channel,
				      struct te_dvb_demux_channel_input *param)
{
	int ret;
	struct lx_sdec_channel_input_cfg cfg;

	log_noti("%s(%d,%s,%d)\n", __func__, channel->idx,
		 te_input_port_to_str(param->port), param->reset);

	cfg.port = param->port;
	cfg.enable = (param->port == LX_TE_INPUT_PORT_NONE) ? false : true;
	cfg.reset = param->reset;

	ret = sdec_config_channel_input(channel->dev, &cfg);
	if (ret) {
		log_error("sdec_config_channel_input failed(%d)", ret);
		return ret;
	}

#if 0	// TODO: enable if necessary
	if (te_get_input_port_type(cfg->port) == LX_TE_INPUT_PORT_DVR) {
		channel->dvr_idx = cfg->port - LX_TE_INPUT_PORT_DVR0;
	}
#endif
	channel->input_cfg.port = param->port;

	return 0;
}

static int dmx_kapi_get_stc(struct lxdvb_dmx_channel *channel,
			    struct te_dvb_demux_get_time *param)
{
	int ret;
	struct lx_sdec_clk_value value;
	u64 us;

	ret = sdec_debug_get_stc_systime(channel->dev, &value, &us);
	if (ret) {
		log_error("sdec_debug_get_stc_systime failed(%d)", ret);
		return ret;
	}
	param->stc = (u64)value.base_32 << 32 | value.base_31_0;
	param->systime = us;

	return 0;
}

static int dmx_kapi_get_gstc(struct lxdvb_dmx_channel *channel,
			     struct te_dvb_demux_get_time *param)
{
	int ret;
	struct lx_sdec_clk_value value;
	u64 us;

	ret = sdec_debug_get_gstc_systime(channel->dev, param->idx, &value,
					  &us);
	if (ret) {
		log_error("sdec_debug_get_gstc_systime failed(%d)", ret);
		return ret;
	}
	param->stc = (u64)value.base_32 << 32 | value.base_31_0;
	param->systime = us;

	return 0;
}

static int demux_do_kapi_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_dmx_fh *fh = priv;
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_demux *dmx = channel->dmx;
	int ret;

	if (mutex_lock_interruptible(&dmx->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case TE_DVB_DEMUX_SET_PROTECTKEY:
		ret = dmx_kapi_set_prokey(channel, parg);
		break;
	case TE_DVB_DEMUX_SET_CHANNEL_INPUT:
		ret = dmx_kapi_set_channel_input(channel, parg);
		break;
	case TE_DVB_DEMUX_GET_STC:
		ret = dmx_kapi_get_stc(channel, parg);
		break;
	case TE_DVB_DEMUX_GET_GSTC:
		ret = dmx_kapi_get_gstc(channel, parg);
		break;
	case TE_DVB_DEMUX_STC_ENABLE:
		ret = sdec_debug_stcc_enable(channel->dev, true);
		break;
	case TE_DVB_DEMUX_STC_DISABLE:
		ret = sdec_debug_stcc_enable(channel->dev, false);
		break;
	default:
		log_error("invalid command[0x%08x]. magic=0x%02X, num=%d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd));
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&dmx->mutex);
	return ret;
}

static int demux_do_ioctl(void *priv, unsigned int cmd, void *parg)
{
	struct lxdvb_dmx_fh *fh = priv;
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_demux *dmx = channel->dmx;
	int ret;

	if (_IOC_TYPE(cmd) == TE_DVB_DEMUX_MAGIC)
		return demux_do_kapi_ioctl(priv, cmd, parg);

	if (mutex_lock_interruptible(&dmx->mutex))
		return -ERESTARTSYS;

	switch (cmd) {
	case DMX_START:
	case DMX_STOP:
	case DMX_SET_FILTER:
	case DMX_SET_PES_FILTER:
	case DMX_SET_BUFFER_SIZE:
	case DMX_SET_TEMI_FILTER:
		ret = demux_do_ioctl_filter(fh, cmd, parg);
		break;

	case DMX_GET_PES_PIDS:
		ret = -EINVAL;
		break;

	case DMX_GET_STC:
		ret = dvb_dmx_get_stc(channel, parg);
		break;

	case DMX_ADD_PID:
		ret = -EINVAL;
		break;

	case DMX_REMOVE_PID:
		ret = -EINVAL;
		break;

	case DMX_EXT_S_CTL:
		ret = dvb_dmx_set_control(fh, parg);
		break;

	case DMX_EXT_G_CTL:
		ret = dvb_dmx_get_control(fh, parg);
		break;

	default:
		ret = -ENOTTY;
		break;
	}

	mutex_unlock(&dmx->mutex);

	if (ret < 0) {
		log_error("command[0x%08x]. magic=0x%02X, num=%d - error %d",
			   cmd, _IOC_TYPE(cmd), _IOC_NR(cmd), ret);
	}

	return ret;
}

static long demux_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	return te_ioctl_usercopy(cmd, arg, demux_do_ioctl, demux_get_user_ptr,
				 file->private_data);
}

static unsigned int demux_poll(struct file *file,
			       struct poll_table_struct *wait)
{
	struct lxdvb_dmx_fh *fh = file->private_data;
	struct lxdvb_dmx_filter *filter = fh->filter;
	unsigned int mask = 0;

	if (fh->channel->exit)
		return POLLERR;

	if (!filter || !filter->pbuf)
		return POLLERR;

	poll_wait(file, te_pktbuf_wq(filter->pbuf), wait);

	if (te_pktbuf_error(filter->pbuf)) {
		// not set POLLERR here to process error handling at dmx_read
		mask |= (POLLIN | POLLRDNORM | POLLPRI); // | POLLERR);
	} else {
		if (filter->state >= DEMUX_FILTER_STATE_GO &&
		    te_pktbuf_next_packet_size(filter->pbuf) != 0) {
			mask |= (POLLIN | POLLRDNORM | POLLPRI);
		}
	}

	return mask;
}

static int demux_release(struct inode *inode, struct file *file)
{
	struct lxdvb_dmx_fh *fh = file->private_data;
	struct lxdvb_dmx_channel *channel = fh->channel;
	struct lxdvb_demux *dmx = channel->dmx;
	struct te_device *tdev = dmx->tdev;
	int ret = 0;

	log_trace("demux_release - fh(%p)\n", fh);

	mutex_lock(&dmx->mutex);

	if (fh->filter) {
		demux_filter_free(fh->filter);
	}

	if (fh->tsh_filter) {
		free_tsh_filter(fh->tsh_filter);
	}

	kfree(fh);

	// TODO: MODIFY IT
	channel->dvbdev->users--;
	if (channel->dvbdev->users == 0 && channel->exit) {
		mutex_unlock(&dmx->mutex);
		wake_up(&channel->dvbdev->wait_queue);
	} else {
		mutex_unlock(&dmx->mutex);
	}

	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DEMUX);
	return ret;
}

static int resume_demux_filter(struct lxdvb_demux *dmx)
{
	int i, j;
	struct lxdvb_dmx_channel *channel;
	struct lxdvb_dmx_filter *f;

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		for (j = 0; j < channel->num_filter; j++) {
			f = &channel->filter[j];
			f->desc_enable = false;
			f->xcas_desc_enable = false;
			if (f->state != DEMUX_FILTER_STATE_GO)
				continue;

			if (f->pbuf) {
				te_pktbuf_reset(f->pbuf);
			}
		}
	}

	return 0;
}

static int resume_demux_desc(struct lxdvb_demux *dmx)
{
	int i;
	struct lxdvb_dmx_channel *c;

	for (i = 0; i < dmx->num_channel; i++) {
		c = &dmx->channels[i];
		/* Reset descrambler type for Embedded CAS control */
		if (c->algo_mode == DEMUX_ALGO_NAGRA) {
			return dmx_nagra_resume_desc_type(c, c->desc_type);
		} else if (c->algo_mode == DEMUX_ALGO_XCAS) {
			enum dmx_ext_dscrmb_type dtype = c->desc_type;

			log_warning("[%d] EMB type[%d] detected; reinitialize",
				    c->idx, dtype);

			/* reset desc type as NONE for rerunning it */
			c->desc_type = DMX_EXT_DSCRMB_TYPE_NONE;
			dmx_ext_set_desc_type(c, dtype);
		} else {
			dmx_ext_set_desc_type(c, c->desc_type);
		}
	}

	return 0;
}

/* DEBUG Functions */
#define dprintf(fmt, args...)	seq_printf(m, fmt, ##args)
#define dprintf1(fmt, args...)	dprintf("     " fmt, ##args)

enum {
	DEBUG_ID_CALLBACK = 0,
};

enum debug_status {
	DEBUG_STATUS_PARAM = 0,
	DEBUG_STATUS_INPUT,
	DEBUG_STATUS_DVBFILTER,
	DEBUG_STATUS_PID,
	DEBUG_STATUS_PCR,
	DEBUG_STATUS_TSHEADER,
	DEBUG_STATUS_MAX
};

#define SHOW_MASK_PARAM		(0x1 << DEBUG_STATUS_PARAM)
#define SHOW_MASK_INPUT		(0x1 << DEBUG_STATUS_INPUT)
#define SHOW_MASK_DVBFILTER	(0x1 << DEBUG_STATUS_DVBFILTER)
#define SHOW_MASK_PID		(0x1 << DEBUG_STATUS_PID)
#define SHOW_MASK_PCR		(0x1 << DEBUG_STATUS_PCR)
#define SHOW_MASK_TSHEADER	(0x1 << DEBUG_STATUS_TSHEADER)
#define SHOW_MASK_ALL		0xFFFF

#define FLT_ITM_FMT	"%-9s "

static void show_filter_buffer_status(struct lxdvb_dmx_filter *f,
				      struct seq_file *m)
{
	u32 size;

	if (f->pbuf)
		size = te_buf_size(f->pbuf);
	else
		size = 0;

	dprintf1(FLT_ITM_FMT, "BUFFER");
	dprintf("%uKB(%u) ALLOC[%uKB] ", (f->buf_size / SZ_1K), f->buf_size,
		size / SZ_1K);

#ifdef USE_DMX_FILTER_DIRECT_BUFFER
	dprintf("\n");
#else
	if (f->stream_filter) {
		size = te_buf_size(&f->stream_filter->hbuf);
		dprintf("DEV[%uKB]\n", size / SZ_1K);
	} else {
		dprintf("\n");
	}
#endif

#ifdef DEBUG_DMX_BUFFER
	if (f->stream_filter) {
		u32 a, r;
		struct dmx_stream_filter *streamf = f->stream_filter;

		dprintf1(FLT_ITM_FMT, "MAX_USED");

		size = te_buf_size(&streamf->pbuf);
		a = streamf->max_used_size;
		r = a * 100 / size;
		dprintf("%u(%uKB,%u%%) ", a, a / SZ_1K, r);

#ifdef USE_DMX_FILTER_DIRECT_BUFFER
		dprintf("\n");
#else
		size = te_buf_size(&streamf->hbuf);
		a = streamf->max_used_dev_size;
		r = a * 100 / size;
		dprintf("DEV:%u(%uKB,%u%%)\n", a, a / SZ_1K, r);
#endif
	}
#endif

	if (f->pbuf) {
		dprintf1(FLT_ITM_FMT, "READ");
		dprintf("%uKB(%u)\n", (f->read_size / SZ_1K), f->read_size);
	}
}

static void show_pes_filter_status(struct lxdvb_dmx_filter *f,
				   struct seq_file *m)
{
	struct dmx_pes_filter_params *p = &f->params.pes;

	dprintf1(FLT_ITM_FMT, "IN");
	dprintf("%s\n", p->input == DMX_IN_FRONTEND ? "FE":"DVR");
	dprintf1(FLT_ITM_FMT, "OUT");
	dprintf("%s\n", lxdvb_demux_output_str(p->output));
	dprintf1(FLT_ITM_FMT, "FLAGS");
	if (p->flags & DMX_IMMEDIATE_START)
		dprintf("IMMEDIATE ");
	dprintf("\n");

	show_filter_buffer_status(f, m);

	dprintf1(FLT_ITM_FMT, "PES_TYPE");
	dprintf("%s\n", lxdvb_demux_pes_type_str(p->pes_type));
}

static void show_sec_filter_status(struct lxdvb_dmx_filter *f,
				   struct seq_file *m)
{
	struct dmx_sct_filter_params *p = &f->params.sec;
	struct dmx_filter *dmxfilter = &p->filter;

	dprintf1(FLT_ITM_FMT "%d\n", "TIMEOUT", p->timeout);
	dprintf1(FLT_ITM_FMT, "FLAGS");
	if (p->flags & DMX_IMMEDIATE_START)
		dprintf("IMMEDIATE ");
	if (p->flags & DMX_CHECK_CRC)
		dprintf("CRC ");
	if (p->flags & DMX_ONESHOT)
		dprintf("ONESHOT ");
	dprintf("\n");

	show_filter_buffer_status(f, m);

	dprintf1(FLT_ITM_FMT, "FILTER");
	dprintf("%016llX %016llX\n", TE_GET64(&dmxfilter->filter[0]),
		TE_GET64(&dmxfilter->filter[8]));
	dprintf1(FLT_ITM_FMT, "MASK");
	dprintf("%016llX %016llX\n", TE_GET64(&dmxfilter->mask[0]),
		TE_GET64(&dmxfilter->mask[8]));
	dprintf1(FLT_ITM_FMT, "MODE");
	dprintf("%016llX %016llX\n", TE_GET64(&dmxfilter->mode[0]),
		TE_GET64(&dmxfilter->mode[8]));
}

static void show_temi_filter_status(struct lxdvb_dmx_filter *f,
				    struct seq_file *m)
{
	struct dmx_sct_filter_params *p = &f->params.sec;
	struct dmx_filter *dmxfilter = &p->filter;

	dprintf1(FLT_ITM_FMT "%d\n", "TIMEOUT", p->timeout);
	dprintf1(FLT_ITM_FMT, "FLAGS");
	if (p->flags & DMX_IMMEDIATE_START)
		dprintf("IMMEDIATE ");
	if (p->flags & DMX_ONESHOT)
		dprintf("ONESHOT ");
	dprintf("\n");

	show_filter_buffer_status(f, m);

	dprintf1(FLT_ITM_FMT, "FILTER");
	dprintf("%02X\n", dmxfilter->filter[0]);
	dprintf1(FLT_ITM_FMT, "MASK");
	dprintf("%02X\n", dmxfilter->mask[0]);
	dprintf1(FLT_ITM_FMT, "MODE");
	dprintf("%02X\n", dmxfilter->mode[0]);
}

static void show_pidf_dests(u32 mask, struct seq_file *m)
{
#define dprint_dest(__name, __str)				\
	do {							\
		if (mask & LX_SDEC_PFLT_DEST_MASK(__name))	\
			dprintf(__str);				\
	} while (0)

	dprint_dest(VDEC0, "VD0 ");
	dprint_dest(VDEC1, "VD1 ");
	dprint_dest(VDEC2, "VD2 ");
	dprint_dest(VDEC3, "VD3 ");

	dprint_dest(ADEC0, "AD0 ");
	dprint_dest(ADEC1, "AD1 ");
	dprint_dest(ADEC2, "AD2 ");
	dprint_dest(ADEC3, "AD3 ");

	dprint_dest(DVR0, "DN0 ");
	dprint_dest(DVR1, "DN1 ");
	dprint_dest(DVR2, "DN2 ");
	dprint_dest(DVR3, "DN3 ");

	dprint_dest(STC, "STC ");
	dprint_dest(BUFFER, "BUF ");
	dprint_dest(TEMI, "TEM ");
	dprint_dest(TSHEADER, "TSH ");
}

static void show_channel_tsh_filter(struct lxdvb_dmx_channel *channel,
				    struct seq_file *m)
{
	int i;
	struct dmx_tsh_filter *f;
	struct dmx_tsh_filter_scheduler *sched = &channel->tsh_filter_sched;
	bool has_filter = false;

	mutex_lock(&sched->mutex);
	for (i = 0; i < channel->num_tsh_filter; i++) {
		f = &channel->tsh_filter[i];
		if (f->state == DEMUX_FILTER_STATE_FREE)
			continue;

		if (!has_filter) {
			dprintf("DEMUX[%d]\n", channel->idx);
			dprintf("%3s %6s %9s  %8s\n", "NUM", "PID",
				 "STATE", "DATA");
			has_filter = true;
		}

		dprintf("%3d 0x%04x ", f->idx, f->pid);
		dprintf("%9s", lxdvb_demux_filter_state_str(f->state));
		if (f == sched->runner)
			dprintf("* ");
		else
			dprintf("  ");

		if (f->done) {
			dprintf("%08x\n", TE_GET32(&f->data[0]));
		} else {
			dprintf("%8s\n", "N/A");
		}
	}
	mutex_unlock(&sched->mutex);
}

static void debug_show_tsh_filter(struct lxdvb_demux *dmx, struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_channel *channel;

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		show_channel_tsh_filter(channel, m);
	}
}

static void debug_show_pcr(struct lxdvb_demux *dmx, struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_channel *channel;
	struct dmx_pcr *pcr;
	bool is_virtual;

	dprintf("NUM EN    PID\n");

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		pcr = &channel->pcr;
		is_virtual = pcr->is_virtual;

		if (is_virtual) {
			channel = pcr->sdt_channel;
			pcr = &channel->pcr;
		}

		dprintf("%3d %2s ", channel->idx, pcr->enabled ? "O" : "X");
		if (pcr->filter) {
			dprintf("0x%04x", pcr->filter->pid);
		} else {
			dprintf("%6s", "NONE");
		}

		if (is_virtual)
			dprintf("[VIRTUAL]\n");
		else
			dprintf("\n");
	}
}

static void debug_show_pid_filter(struct lxdvb_demux *dmx, struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_channel *channel;
	struct dmx_pid_filter *pidf;

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];

		if (list_empty(&channel->pid_filters))
			continue;

		dprintf("DEMUX[%d]\n", channel->idx);
		dprintf1("NUM     PID  DEST\n");
		list_for_each_entry (pidf, &channel->pid_filters, entry) {
			dprintf1("%3d  0x%04x   ", pidf->idx, pidf->pid);
			show_pidf_dests(pidf->dest_mask, m);
			dprintf("\n");
		}
	}
}


static void show_channel_dvb_filter(struct lxdvb_dmx_channel *channel,
				    struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_filter *f;
	bool has_filter = false;
#define DVB_FILTER_LINE_STR "------------------------------------------------"

	for (i = 0; i < channel->num_filter; i++) {
		f = &channel->filter[i];
		if (f->state == DEMUX_FILTER_STATE_FREE)
			continue;

		if (!has_filter) {
			dprintf(DVB_FILTER_LINE_STR "\n");
			dprintf("DEMUX[%d]\n", channel->idx);
			dprintf(DVB_FILTER_LINE_STR "\n");
			has_filter = true;
		} else {
			dprintf("\n");
		}

		dprintf("[%02d] %-7s\n", f->idx,
			lxdvb_demux_filter_type_str(f->type));
		dprintf1(FLT_ITM_FMT "0x%04x ", "PID", f->pid);
		if (f->pid_filter) {
			dprintf("[%02d]", f->pid_filter->idx);
			if (f->desc_enable)
				dprintf(TE_COLOR_RED " DESC" TE_COLOR_NONE);
			else if (f->xcas_desc_enable)
				dprintf(TE_COLOR_RED " XCAS" TE_COLOR_NONE);
			else if (f->nagra_desc_enable) //FIXME
				dprintf(TE_COLOR_RED " NGRA" TE_COLOR_NONE);
		}
		dprintf("\n");

		dprintf1(FLT_ITM_FMT "%s\n", "STATE",
			 lxdvb_demux_filter_state_str(f->state));

		if (f->type == DEMUX_FILTER_TYPE_PES) {
			show_pes_filter_status(f, m);
		} else if (f->type == DEMUX_FILTER_TYPE_SEC) {
			show_sec_filter_status(f, m);
		} else if (f->type == DEMUX_FILTER_TYPE_TEMI) {
			show_temi_filter_status(f, m);
		}

		if (f->stream_filter) {
			dprintf1("%-9s ", "RECV");
			dprintf("%lu\n", f->stream_filter->received);
		} else if (f->temi_filter) {
			dprintf1("%-9s ", "RECV");
			dprintf("%lu\n", f->temi_filter->received);
		}

		/* Additional Information */
		if (f->child) {
			dprintf1(FLT_ITM_FMT "0x%04x [%02d]\n", "CHILD",
				 f->child->pid, f->child->idx);
		}
	}
}

static void debug_show_dvb_filter(struct lxdvb_demux *dmx, struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_channel *channel;

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		show_channel_dvb_filter(channel, m);
	}
}

static void debug_show_input(struct lxdvb_demux *dmx, struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_channel *channel;
	struct dmx_ext_source *param;
	enum te_reg_tpi_port tpi;

	dprintf("%3s %9s %8s %9s %7s %13s %10s\n", "NUM", "SRC_TYPE",
		"PORT_NUM", "PORT_TYPE", "DVR_IDX", "TE_INPUT_PORT", "TPI");

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		param = &channel->input_params;
		tpi = te_input_port_to_reg_tpi_port(channel->input_cfg.port);

		dprintf("%3d %9s %8d %9s %7d %13s %10s\n", i,
			lxdvb_demux_src_type_str(param->input_src_type),
			param->input_port_num,
			lxdvb_demux_port_type_str(param->input_port_type),
			channel->dvr_idx,
			te_input_port_to_str(channel->input_cfg.port),
			te_reg_tpi_port_to_str(tpi));
	}
}

static void debug_show_params(struct lxdvb_demux *dmx, struct seq_file *m)
{
	struct lxdvb_dmx_param *p = &dmx->param;

#define dprint_param(title, fmt, args...) \
	dprintf("%-13s " fmt "\n", title ":", ##args)

	dprint_param("PLATFORM", "%s", lxdvb_demux_platform_str(p->platform));
	dprint_param("COUNTRY", "%s", lxdvb_demux_country_str(p->country));
	dprint_param("MODEL_NO", "%d", p->model_no);
	dprint_param("NUM_OF_TUNER", "%d", p->num_of_tuner);
}


static int show_status(struct lxdvb_demux *dmx, struct seq_file *m,
		       enum debug_status s, bool title)
{
#define TITLE_LINE_STR "======================================================"
#define dprint_title(fmt, args...)			\
	do {						\
		if (title) {				\
			dprintf(TITLE_LINE_STR "\n");	\
			dprintf(fmt "\n", ##args);	\
			dprintf(TITLE_LINE_STR "\n");	\
		}					\
	} while(0)
	int rc = 0;

	mutex_lock(&dmx->mutex);

	switch (s) {
	case DEBUG_STATUS_PARAM:
		dprint_title("PARAMETERS");
		debug_show_params(dmx, m);
		break;
	case DEBUG_STATUS_INPUT:
		dprint_title("DEMUX INPUT STATUS");
		debug_show_input(dmx, m);
		break;
	case DEBUG_STATUS_DVBFILTER:
		dprint_title("DVB FILTER STATUS");
		debug_show_dvb_filter(dmx, m);
		break;
	case DEBUG_STATUS_PID:
		dprint_title("PID FILTER STATUS");
		debug_show_pid_filter(dmx, m);
		break;
	case DEBUG_STATUS_PCR:
		dprint_title("PCR STATUS");
		debug_show_pcr(dmx, m);
		break;
	case DEBUG_STATUS_TSHEADER:
		dprint_title("TS HEADER FILTER STATUS");
		debug_show_tsh_filter(dmx, m);
		break;
	default:
		rc = -EINVAL;
	}

	mutex_unlock(&dmx->mutex);

	return rc;
}

static int debug_show_status(struct te_debug_item *item, struct seq_file *m)
{
	int i, rc, cnt;
	unsigned long n;
	struct lxdvb_demux *dmx = item->private;
	unsigned long mask = item->flags;

	n = hweight_long(mask);
	if (!n)
		return 0;

	if (n == 1) {
		return show_status(dmx, m, __ffs(mask), false);
	}

	cnt = 0;
	for (i = 0; i < DEBUG_STATUS_MAX; i++) {
		if (mask & (0x1 << i)) {
			if (cnt)
				dprintf("\n");

			rc = show_status(dmx, m, i, true);
			if (!rc)
				cnt++;
		}
	}

	return 0;
}


static int debug_channel_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
//	struct lxdvb_dmx_channel *channel = item->private;

	switch (item->flags) {

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_channel_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
//	struct lxdvb_dmx_channel *channel = item->private;

	switch (item->flags) {

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static void debug_show_filter_callback(struct lxdvb_demux *dmx,
				       struct seq_file *m)
{
	struct debug_filter_callback *d = get_debug_filter_callback();

	mutex_lock(&d->mutex);
	dprintf("state: %s\n", d->enable ? "enabled" : "disabled");
	if (d->enable) {
		dprintf("demux: ");
		if (d->channel)
			dprintf("%d\n", d->channel->idx);
		else
			dprintf("all\n");

		dprintf("pid: ");
		if (d->num_pid) {
			int i;
			for (i = 0; i < d->num_pid; i++) {
				if (i)
					dprintf(", ");
				dprintf("0x%04x", d->pid[i]);
			}
			dprintf("\n");
		} else {
			dprintf("all\n");
		}
	}
	mutex_unlock(&d->mutex);
}

static int debug_filter_callback_command(struct lxdvb_demux *dmx,
					 struct debug_filter_callback *d,
					 int argc, char **argv)
{
	int ret, i;
	u32 idx;
	char *v, *tok;

	if (!strcmp(argv[0], "0")) {
		d->enable = false;
		return 0;
	}

	// disable and reset debug filter callback
	d->enable = false;
	d->channel = NULL;
	d->num_pid = 0;
	d->count = 0;

	i = 0;
	while (++i < argc) {
		if (!strcmp(argv[i], "-dmx")) {
			v = argv[++i]; // null added to the end from argv_split
			if (!v)
				return -EINVAL;

			ret = kstrtou32(v, 0, &idx);
			if (ret)
				return ret;

			if (idx >= dmx->num_channel)
				return -EINVAL;

			d->channel = &dmx->channels[idx];
		} else if (!strcmp(argv[i], "-pid")) {
			v = argv[++i]; // null added to the end from argv_split
			if (!v)
				return -EINVAL;

			while ((tok = strsep(&v, ","))) {
				if (d->num_pid >= MAX_DEBUG_FILTER_PID)
					break;

				ret = kstrtou16(tok, 0, &d->pid[d->num_pid]);
				if (ret)
					return ret;

				d->num_pid++;
			}
		} else {
			return -EINVAL;
		}
	}
	d->enable = true;

	return 0;
}

static int debug_set_filter_callback(struct lxdvb_demux *dmx, char *str)
{
	int ret, argc;
	char **argv;
	struct debug_filter_callback *d = get_debug_filter_callback();

	argv = argv_split(GFP_KERNEL, str, &argc);
	if (!argv)
		return -ENOMEM;

	if (argc > 0 && (!strcmp(argv[0], "0") || !strcmp(argv[0], "1"))) {
		mutex_lock(&d->mutex);
		ret = debug_filter_callback_command(dmx, d, argc, argv);
		mutex_unlock(&d->mutex);
	} else {
		ret = -EINVAL;
	}
	argv_free(argv);

	return ret;
}

static int debug_show(struct te_debug_item *item, struct seq_file *m)
{
	int ret = 0;
	struct lxdvb_demux *dmx = item->private;

	switch (item->flags) {
	case DEBUG_ID_CALLBACK:
		debug_show_filter_callback(dmx, m);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_write(struct te_debug_item *item, char *str)
{
	int ret = 0;
	struct lxdvb_demux *dmx = item->private;

	switch (item->flags) {
	case DEBUG_ID_CALLBACK:
		ret = debug_set_filter_callback(dmx, str);
		break;

	default:
		ret = -EPERM;
		break;
	}

	return ret;
}

static int debug_show_help(struct te_debug_item *item, struct seq_file *m)
{
	dprintf("callback\n");
	dprintf1("display filter callback\n");
	dprintf1("usage: [0|1] <options...>\n");
	dprintf1("  -dmx n: demux index[none:all demux channel]\n");
	dprintf1("  -pid xx,...: specified pids[none:all pid]\n");

	return 0;
}

static const struct te_debug_simple_ops debug_channel_ops = {
	.show = debug_channel_show,
	.write = debug_channel_write,
};

static const struct te_debug_item_info debug_channel_list[] = {
	DBGITM_SIM("dummy", &debug_channel_ops, 0),
};

static void init_channel_debug(struct lxdvb_demux *dmx,
			       struct lxdvb_dmx_channel *channel)
{
	char name[8];
	snprintf(name, sizeof(name), "%u", channel->idx);

	channel->debug_dir = te_debug_create_dir(name, dmx->debug_dir);
	if (!channel->debug_dir) {
		log_error("Err in te_debug_create_dir\n");
		return;
	}

	debug_create_item_files(debug_channel_list, channel,
				channel->debug_dir);

	return;
}

/* webos linuxtv proc */
static void proc_show_pes_filter_status(struct lxdvb_dmx_channel *channel,
					struct seq_file *m)
{
	int i;
	struct lxdvb_dmx_filter *f;
	struct dmx_pes_filter_params *p;

	for (i = 0; i < channel->num_filter; i++) {
		f = &channel->filter[i];
		if (f->state == DEMUX_FILTER_STATE_FREE)
			continue;

		if (f->type != DEMUX_FILTER_TYPE_PES)
			continue;

		p = &f->params.pes;

		dprintf("[%d] [%02d] 0x%04x %9s %11s %6s\n",
			channel->idx, f->idx, f->pid,
			lxdvb_demux_filter_state_str(f->state),
			lxdvb_demux_output_str(p->output),
			lxdvb_demux_pes_type_str(p->pes_type));
	}
}

static int proc_show_status(struct lxdvb_proc_item *item, struct seq_file *m)
{
	int i;
	struct lxdvb_demux *dmx = item->private;
	struct lxdvb_dmx_channel *channel;

	dprintf("1.PES filter status\n");
	dprintf("%3s %4s %6s %9s %11s %6s\n",
		"CH", "IDX", "PID", "STATE", "OUTPUT", "TYPE");

	mutex_lock(&dmx->mutex);

	for (i = 0; i < dmx->num_channel; i++) {
		channel = &dmx->channels[i];
		proc_show_pes_filter_status(channel, m);
	}

	mutex_unlock(&dmx->mutex);

	return 0;
}

static struct lxdvb_proc_item_info proc_list[] = {
	LXDVB_PROC_ITEM_SHOW("status", proc_show_status, 0),
};


static const struct te_debug_simple_ops debug_ops = {
	.show = debug_show,
	.write = debug_write,
};

static const struct te_debug_item_info debug_list[] = {
	DBGITM_SHOW("param", debug_show_status, SHOW_MASK_PARAM),
	DBGITM_SHOW("io", debug_show_status, SHOW_MASK_INPUT),
	DBGITM_SHOW("filter", debug_show_status, SHOW_MASK_DVBFILTER),
	DBGITM_SHOW("pid", debug_show_status, SHOW_MASK_PID),
	DBGITM_SHOW("pcr", debug_show_status, SHOW_MASK_PCR),
	DBGITM_SHOW("tsh", debug_show_status, SHOW_MASK_TSHEADER),
	DBGITM_SHOW("status", debug_show_status, SHOW_MASK_ALL),
	DBGITM_SIM("callback", &debug_ops, DEBUG_ID_CALLBACK),
	DBGITM_SHOW("help", debug_show_help, 0),
};

static void init_debug_filter_callback(struct lxdvb_demux *dmx)
{
	struct debug_filter_callback *d = get_debug_filter_callback();

	d->enable = false;
	mutex_init(&d->mutex);
}

static void init_debug(struct lxdvb_device *dev, struct lxdvb_demux *dmx)
{
	int i;

	init_debug_filter_callback(dmx);

	dmx->debug_dir = te_debug_create_dir("demux", dev->debug_dir);
	if (!dmx->debug_dir) {
		log_error("Err in te_debug_create_dir\n");
		return;
	}

	debug_create_item_files(debug_list, dmx, dmx->debug_dir);

	for (i = 0; i < dmx->num_channel; i++) {
		init_channel_debug(dmx, &dmx->channels[i]);
	}

	// webos linuxtv proc files
	dmx->proc_dir = lxdvb_proc_create_dir("dvb_demux", NULL);
	CHECK_ERROR(!dmx->proc_dir, return, "lxdvb_proc_create_dir failed");

	lxdvb_proc_create_files(proc_list, dmx, dmx->proc_dir);
}


/* lxdvb driver functions */

static const struct file_operations demux_fops = {
	.owner = THIS_MODULE,
	.read = demux_read,
	.unlocked_ioctl = demux_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = demux_ioctl,
#endif
	.open = demux_open,
	.release = demux_release,
	.poll = demux_poll,
	.llseek = default_llseek,
};

static const struct dvb_device demux_dvbdev = {
	.priv = NULL,
	.writers = 1,
#if defined(CONFIG_MEDIA_CONTROLLER_DVB)
	.name = "dvb-demux",
#endif
	.fops = &demux_fops,
};

static int init_tsh_filter_sched(struct dmx_tsh_filter_scheduler *sched)
{
	mutex_init(&sched->mutex);
	sched->users = 0;
	sched->runner = NULL;
	sched->flags = 0;
	init_waitqueue_head(&sched->wq);
	init_completion(&sched->woken);
	INIT_LIST_HEAD(&sched->wait_list);

	return 0;
}

static void release_tsh_filter_sched(struct dmx_tsh_filter_scheduler *sched)
{
	// TODO:
}

static int init_demux_channel(struct lxdvb_device *dev,
			      struct lxdvb_dmx_channel *channel)
{
	int i, ret;
	struct lxdvb_dmx_filter *filter;
	struct dmx_tsh_filter *tsh_filter;

	channel->num_filter = DEMUX_MAX_FILTER;
	channel->filter = vmalloc(channel->num_filter *
				  sizeof(struct lxdvb_dmx_filter));
	if (!channel->filter)
		return -ENOMEM;

	channel->num_tsh_filter = TSHEADER_MAX_FILTER;
	channel->tsh_filter = vmalloc(channel->num_tsh_filter *
				     sizeof(struct dmx_tsh_filter));
	if (!channel->tsh_filter) {
		ret = -ENOMEM;
		goto err_tsh_alloc;
	}

	channel->input_cfg.port = LX_TE_INPUT_PORT_NONE;
	channel->input_params.input_src_type = DMX_EXT_SRC_TYPE_NULL;
	channel->dvr_idx = -1;
	channel->algo_mode = DEMUX_ALGO_LEGACY;

	for (i = 0; i < channel->num_filter; i++) {
		filter = &channel->filter[i];
		filter->idx = i;
		filter->state = DEMUX_FILTER_STATE_FREE;
		filter->channel = channel;
		mutex_init(&filter->mutex);
	}
	for (i = 0; i < channel->num_tsh_filter; i++) {
		tsh_filter = &channel->tsh_filter[i];
		tsh_filter->idx = i;
		tsh_filter->state = DEMUX_FILTER_STATE_FREE;
	}

	ret = init_tsh_filter_sched(&channel->tsh_filter_sched);
	if (ret) {
		log_error("init_tsh_filter_sched failed(%d)", ret);
		goto err_tsheader;
	}

	INIT_LIST_HEAD(&channel->pid_filters);
	INIT_LIST_HEAD(&channel->stream_filters);
	INIT_LIST_HEAD(&channel->temi_filters);

	ret = dvb_register_device(&dev->adapter, &channel->dvbdev,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
				  &demux_dvbdev, channel, DVB_DEVICE_DEMUX, 0);
#else
				  &demux_dvbdev, channel, DVB_DEVICE_DEMUX);
#endif
	if (ret) {
		log_error("dvb_register_device failed\n");
		goto err_dvbreg;
	}

	return 0;

err_dvbreg:
	release_tsh_filter_sched(&channel->tsh_filter_sched);
err_tsheader:
	vfree(channel->tsh_filter);
err_tsh_alloc:
	vfree(channel->filter);

	return ret;
}

static void release_demux_channel(struct lxdvb_dmx_channel *channel)
{
	struct lxdvb_demux *dmx = channel->dmx;

	mutex_lock(&dmx->mutex);
	channel->exit = 1;
	mutex_unlock(&dmx->mutex);

	if (channel->dvbdev->users > 0) {
		wait_event(channel->dvbdev->wait_queue,
			   channel->dvbdev->users == 0);
	}

	release_tsh_filter_sched(&channel->tsh_filter_sched);

	dvb_unregister_device(channel->dvbdev);

	vfree(channel->tsh_filter);
	vfree(channel->filter);
}

static int init_demux_filter(struct lxdvb_demux *dmx)
{
	int i;

	dmx->pid_filters = vzalloc(dmx->num_pid_filter *
				   sizeof(struct dmx_pid_filter));
	if (!dmx->pid_filters)
		return -ENOMEM;

	dmx->stream_filters = vzalloc(dmx->num_stream_filter *
				      sizeof(struct dmx_stream_filter));
	if (!dmx->stream_filters) {
		vfree(dmx->pid_filters);
		return -ENOMEM;
	}

	if (dmx->num_temi_filter) {
		dmx->temi_filters = vzalloc(dmx->num_temi_filter *
					    sizeof(struct dmx_temi_filter));
		if (!dmx->temi_filters) {
			vfree(dmx->stream_filters);
			vfree(dmx->pid_filters);
			return -ENOMEM;
		}
	}

	INIT_LIST_HEAD(&dmx->free_pid_filters);
	for (i = 0; i < dmx->num_pid_filter; i++) {
		struct dmx_pid_filter *f = &dmx->pid_filters[i];
		f->state = DEMUX_FILTER_STATE_FREE;
		f->idx = i;
		list_add_tail(&f->entry, &dmx->free_pid_filters);
	}

	INIT_LIST_HEAD(&dmx->free_stream_filters);
	for (i = 0; i < dmx->num_stream_filter; i++) {
		struct dmx_stream_filter *f = &dmx->stream_filters[i];
		f->state = DEMUX_FILTER_STATE_FREE;
		f->idx = i;
		list_add_tail(&f->entry, &dmx->free_stream_filters);
	}

	INIT_LIST_HEAD(&dmx->free_temi_filters);
	for (i = 0; i < dmx->num_temi_filter; i++) {
		struct dmx_temi_filter *f = &dmx->temi_filters[i];
		f->state = DEMUX_FILTER_STATE_FREE;
		f->idx = i;
		list_add_tail(&f->entry, &dmx->free_temi_filters);
	}

	return 0;
}

static void release_demux_filter(struct lxdvb_demux *dmx)
{
	if (dmx->temi_filters)
		vfree(dmx->temi_filters);
	vfree(dmx->stream_filters);
	vfree(dmx->pid_filters);
}

static int dev_init(struct lxdvb_device *dev)
{
	int i, j, ret;
	struct lxdvb_demux *dmx;
	struct lxdvb_dmx_channel *channel;
	struct lx_sdec_chip_cfg cfg;
	struct te_device *tdev = get_te_device(dev);
	struct sdec_device *sdev = sdec_get_device(tdev);
	u8 num_channel;

	if (!sdev) {
		log_error("sdec device not exist\n");
		return -ENODEV;
	}

	sdec_get_chip_config(sdev, &cfg);
	num_channel = cfg.num_channel - cfg.num_sub_channel;

	dmx = devm_kzalloc(&dev->pdev->dev,
			   sizeof(*dmx) +
			   num_channel * sizeof(struct lxdvb_dmx_channel),
			   GFP_KERNEL);
	if (!dmx)
		return -ENOMEM;

	dmx->sdev = sdev;
	dmx->tdev = tdev;
	dmx->num_channel = num_channel;
	dmx->num_pid_filter = cfg.num_pid_filter;
	dmx->num_stream_filter = cfg.num_stream_filter;
	dmx->num_temi_filter = cfg.num_temi_filter;
	dmx->param.country = DMX_COUNTRY_UNKNOWN;
	dmx->param.platform = DMX_PLATFORM_UNKNOWN;
	dmx->param.num_of_tuner = 0;
	mutex_init(&dmx->mutex);

	dmx->mem = te_mem_open(TE_MEM_SDEC_NAME);
	if (!dmx->mem) {
		log_error("te_mem_open failed\n");
		ret = -EIO;
		goto err_mem;
	}

	ret = init_demux_filter(dmx);
	if (ret) {
		log_error("init_demux_filter failed\n");
		goto err_filter;
	}

	for (i = 0; i < num_channel; i++) {
		channel = &dmx->channels[i];
		channel->idx = i;
		channel->dmx = dmx;
		channel->dev = sdec_get_channel(sdev, i);
		ret = init_demux_channel(dev, channel);
		if (ret) {
			log_error("init_demux_channel failed\n");
			for (j = 0; j < i; j++) {
				release_demux_channel(&dmx->channels[j]);
			}
			goto err_channel;
		}
	}
	dev->dmx = dmx;

	init_debug(dev, dmx);

	return 0;

err_channel:
	release_demux_filter(dmx);
err_filter:
	te_mem_close(dmx->mem);
err_mem:
	devm_kfree(&dev->pdev->dev, dmx);

	return ret;
}

static void dev_release(struct lxdvb_device *dev)
{
	int i;
	struct lxdvb_demux *dmx = dev->dmx;

	for (i = 0; i < dmx->num_channel; i++)
		release_demux_channel(&dmx->channels[i]);

	release_demux_filter(dmx);

	dev->dmx = NULL;
}

static int dev_suspend(struct lxdvb_device *dev)
{
	struct te_device *tdev = get_te_device(dev);
	te_clockgate_acquire_clock(tdev, TE_DEVICE_TYPE_DVB_DEMUX);
	return 0;
}

static int dev_resume(struct lxdvb_device *dev)
{
	struct lxdvb_demux *dmx = dev->dmx;
	struct te_device *tdev = get_te_device(dev);

	resume_demux_filter(dmx);
	resume_demux_desc(dmx);
	te_clockgate_release_clock(tdev, TE_DEVICE_TYPE_DVB_DEMUX);
	return 0;
}

const struct lxdvb_sub_driver lxdvb_demux_driver = {
	.name = "lxdvb_demux",
	.init = dev_init,
	.release = dev_release,
	.suspend = dev_suspend,
	.resume = dev_resume,
};
