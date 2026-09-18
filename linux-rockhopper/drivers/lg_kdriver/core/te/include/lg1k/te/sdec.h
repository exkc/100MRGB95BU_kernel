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
 *  TE(Transport Engine) Driver
 *
 *  @author	Kyungseok Hyun (ks.hyun@lge.com)
 *  @version	1.0
 *  @date		2018-10-12
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_SDEC_H_
#define	_LG1K_TE_SDEC_H_

#include <lg1k/te/te.h>
#include <lg1k/te/buffer.h>

#include "te_sdec_kapi.h"

#define NULL_PACKET_PID		0x1FFF
//#define USE_FIXEDMEM_STATUS

struct sdec_device;
struct sdec_channel;
struct sdec_pid_filter;
struct sdec_stream_filter;
struct sdec_temi_filter;
struct sdec_tsh_filter;

enum sdec_filter_status {
	SDEC_FILTER_STATUS_OK = 0,
	SDEC_FILTER_STATUS_OVERFLOW,
	SDEC_FILTER_STATUS_NO_BUF,	/* single packet over total buf size */
};

enum sdec_send_command_type {
	SDEC_SEND_TYPE_KEY = 0,
	SDEC_SEND_TYPE_PVR_PES,
	SDEC_SEND_TYPE_MAX,
};

typedef int (*sdec_stream_filter_callback_t)(struct sdec_stream_filter *f,
					     enum sdec_filter_status status,
					     u32 sidx, u32 eidx, void *priv);

typedef int (*sdec_tsh_filter_callback_t)(struct sdec_tsh_filter *f,
					  enum sdec_filter_status status,
					  u32 data, void *priv);

typedef int (*sdec_temi_filter_callback_t)(struct sdec_temi_filter *f,
					   u64 pts, u8 *buf, u16 len,
					   void *priv);
/**
 * struct sdec_stream_filter_param - Structure for requesting the stream filter
 *
 * @stream_type: section, pes or rawts
 * @pidf:	pid filter will be connected to the stream filter
 * @hbuf:	h/w buffer filtered data will be stored
 * @pattern:	pointer to filter pattern only used if stream_type is section
 * @callback:	callback function to be called when the data is received
 * @priv:	private data as a callback function parameter
 */
struct sdec_stream_filter_param {
	enum lx_sdec_stream_type stream_type;
	struct sdec_pid_filter *pidf;
	struct te_hwbuf *hbuf;
	struct lx_sdec_filter_pattern *pattern;
	sdec_stream_filter_callback_t callback;
	u32 flags;
	void *priv;
};

struct sdec_tsh_filter_param {
	u16 pid;
	sdec_tsh_filter_callback_t callback;
	void *priv;
};

struct sdec_temi_filter_pattern {
	u8 val;
	u8 mask;
	u8 noteq;
};

struct sdec_temi_filter_param {
	u16 pid;
	struct sdec_temi_filter_pattern *pattern;
	sdec_temi_filter_callback_t callback;
	u32 flags;
	void *priv;
};

struct sdec_send_noti_param {
	enum sdec_send_command_type command_type;
	enum lx_sdec_cas_type cas;
	enum lx_sdec_desc_key_type key;
	u16 pid;
	void *data;
	u32 len;
};

struct sdec_desc_nagra_key_param {
	enum lx_sdec_desc_key_type key_type;
	enum lx_sdec_desc_mode desc_mode;
	u8 key_len;
	u8 iv_len;
	u16 pid;
	bool key_encrypted;
	bool iv_encrypted;
	u8 *data;
	u8 *iv;
	u8 *comm_iv;
};

struct sdec_device *sdec_get_device(struct te_device *dev);
struct sdec_channel *sdec_get_channel(struct sdec_device *dev, u8 num);

int sdec_get_chip_config(struct sdec_device *dev, struct lx_sdec_chip_cfg *cfg);
int sdec_get_channel_capability(struct sdec_channel *channel,
				struct lx_sdec_cap *cap);

/* io */
int sdec_config_channel_input(struct sdec_channel *channel,
			      struct lx_sdec_channel_input_cfg *cfg);
int sdec_set_input_mux(struct sdec_device *dev, enum te_reg_input_mux type);

/* pid and stream filters */
int sdec_alloc_pid_filter(struct sdec_channel *channel, u16 pid,
			  struct sdec_pid_filter **filter);
int sdec_set_pid_filter(struct sdec_pid_filter *filter,
			enum lx_sdec_payload_type payload_type, u32 dest_mask);
int sdec_free_pid_filter(struct sdec_pid_filter *filter);

int sdec_request_stream_filter(struct sdec_channel *channel,
			       struct sdec_stream_filter_param *param,
			       struct sdec_stream_filter **filter);
int sdec_cancel_stream_filter(struct sdec_stream_filter *filter);

int sdec_request_tsh_filter(struct sdec_channel *channel,
			    struct sdec_tsh_filter_param *param,
			    struct sdec_tsh_filter **filter);
int sdec_cancel_tsh_filter(struct sdec_tsh_filter *filter);
int sdec_request_temi_filter(struct sdec_channel *channel,
			     struct sdec_temi_filter_param *param,
			     struct sdec_temi_filter **filter);
int sdec_cancel_temi_filter(struct sdec_temi_filter *filter);
int sdec_filter_noti_data_info(struct sdec_channel *channel, void *msg,
			       bool is_filter);
int sdec_filter_noti_xcas_data(struct sdec_channel *channel,
			       struct sdec_send_noti_param *param);

/* clock */
int sdec_set_pcr_pid(struct sdec_channel *channel, u16 pid, bool is_main);
int sdec_cancel_pcr_pid(struct sdec_channel *channel);
int sdec_set_pcr_recovery(struct sdec_channel *channel,
			  enum lx_sdec_pcr_cmd cmd);
int sdec_get_stc(struct sdec_channel *channel, struct lx_sdec_clk_value *value);
int sdec_debug_stcc_enable(struct sdec_channel *channel, bool en);
int sdec_debug_get_stc_systime(struct sdec_channel *channel,
			       struct lx_sdec_clk_value *value,
			       u64 *ktime_us);
int sdec_debug_get_gstc_systime(struct sdec_channel *channel, u8 idx,
			        struct lx_sdec_clk_value *value,
			        u64 *ktime_us);
int sdec_change_stcc_dest(struct sdec_channel *channel, u32 mask);
int sdec_set_pcr_delay(struct sdec_channel *channel, u32 delay);

/* descrambler */
int sdec_init_descrambler(struct sdec_channel *channel,
			  struct lx_sdec_desc_config *cfg);
int sdec_set_descrambler_key(struct sdec_channel *channel,
			     struct lx_sdec_desc_key *param);
int sdec_set_descrambler_pid(struct sdec_channel *channel,
			     struct lx_sdec_desc_pid *param);
int sdec_desc_noti_data_info(struct sdec_channel *channel,
			     enum lx_sdec_cas_type cas_type,
			     enum lx_sdec_desc_key_type key_type,
			     void *data,
			     bool is_dsc);
int sdec_desc_noti_xcas_data(struct sdec_channel *channel,
			      struct sdec_send_noti_param *param);
int sdec_desc_cancel_xcas_pid(struct sdec_channel *channel, u16 pid);
int sdec_desc_set_nagra_key(struct sdec_channel *channel,
			    struct sdec_desc_nagra_key_param *param);
int sdec_desc_cancel_nagra_pid(struct sdec_channel *channel, u16 pid);
int sdec_desc_get_nagra_nonce(struct sdec_channel *channel, u8 *nonce);
int sdec_desc_set_nagra_state(struct sdec_channel *channel, u8 *data, u8 *iv);

/* helper */
const char *sdec_pid_filter_dest_str(enum lx_sdec_pid_filter_dest dest);
const char *sdec_stream_type_str(enum lx_sdec_stream_type type);



#endif				/* _LG1K_TE_SDEC_H_ */
