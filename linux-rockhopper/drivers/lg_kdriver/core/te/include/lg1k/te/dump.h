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
 *  @date		2018-07-09
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_DUMP_H_
#define	_LG1K_TE_DUMP_H_

#include <linux/types.h>

#include <lg1k/te/buffer.h>
#include <lg1k/te/reg.h>

#include "te_sdec_kapi.h"
#include "te_atsc3_kapi.h"
#include "te_arib2_kapi.h"


enum te_dump_module {
	TE_DUMP_MODULE_NONE = 0,
	TE_DUMP_MODULE_SDEC,
	TE_DUMP_MODULE_ATSC3,
	TE_DUMP_MODULE_ARIB2,
	TE_DUMP_MODULE_CIPLUS,
	TE_DUMP_MODULE_DMX,
	TE_DUMP_MODULE_DVR,
	TE_DUMP_MODULE_CA,
	TE_DUMP_MODULE_DELIVERY,
};

enum te_dump_mode {
	TE_DUMP_MODE_INPUT = 0,	/* normal input dump. */
	TE_DUMP_MODE_RAW,	/* dump during packet processing */
	TE_DUMP_MODE_USER,	/* dump @ read syscall */
	TE_DUMP_MODE_MAX,
};

enum te_dump_layer {
	TE_DUMP_LAYER_FE_ISR = 0,
	TE_DUMP_LAYER_FE_MAIN,
	TE_DUMP_LAYER_BE,
};

struct te_dump_sdec_cfg {
	bool pid_bypass;
	enum te_dump_layer layer;
	LX_SDEC_DUMP_TIMESRC_T clk_src;
	LX_SDEC_DUMP_TIMERES_T clk_res;
};

struct te_dump_atsc3_cfg {
	enum te_reg_atsc3_layer layer;
	enum te_reg_dumper_mode mode;
};

struct te_dump_arib2_cfg {
	enum te_reg_dumper_mode mode;
};

struct te_dump_ciplus_cfg {
	u8 syncbyte;
};

enum te_dump_dvr_module {
	TE_DUMP_DVR_UP = 0,
	TE_DUMP_DVR_DN,
};

struct te_dump_dvr_cfg {
	enum te_dump_dvr_module module;
};

struct te_dump_cfg {
	u8 ch;
	LX_TE_INPUT_PORT_T port;
	enum te_dump_mode mode;
	struct te_hwbuf *data;
	struct te_hwbuf *meta;
	u32 flags;

	union {
		struct te_dump_sdec_cfg sdec;
		struct te_dump_atsc3_cfg atsc3;
		struct te_dump_arib2_cfg arib2;
		struct te_dump_ciplus_cfg ci14;
		struct te_dump_dvr_cfg dvr;
	};
};

struct te_dump_handle {
	void *dev_handle;
};

struct te_dump_device {
	enum te_dump_module module;
	int (*start)(struct te_dump_device *dev, struct te_dump_handle *h,
		     struct te_dump_cfg *cfg);
	void (*stop)(struct te_dump_device *dev, struct te_dump_handle *h);

	void *private;

	struct list_head list;
};

int te_dump_register_device(struct te_dump_device *dev);

#endif				/* _LG1K_TE_DUMP_H_ */

/** @} */
