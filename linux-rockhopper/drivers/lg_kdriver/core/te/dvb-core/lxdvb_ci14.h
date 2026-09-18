/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
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
 *  CI Driver for linux dvb_ca(DEMUX&CA)
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2018-02-09
 *  @note		Additional information.
 */

/* Original Copyright */
/*
 * dvb_ca.h: generic DVB functions for EN50221 CA interfaces
 *
 * Copyright (C) 2004 Andrew de Quincey
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 */

#ifndef _LXDVB_CI14_H_
#define _LXDVB_CI14_H_

#include <linux/version.h>
#include <linux/dvb/ca.h>
#include <linux/dvbv5-ext/dvbv5-ext-ca.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/ciplus.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>

#else
#include "dvbdev.h"

#endif
struct lxdvb_ci14_fh;
struct lxdvb_ci14_pidf;

struct lxdvb_ci14_channel {
	struct dvb_device *dvbdev;

	u8 idx;
	u8 num_pidf;

	struct lxdvb_ci14 *ci14;
	struct ciplus_channel *dev;

	struct lxdvb_ci14_pidf *pidf;

	struct mutex mutex;
	bool exit;
};

struct lxdvb_ci14 {		//public information
	struct mutex mutex; //TODO: need?
	spinlock_t spinlock;

	struct te_debug_entry *debug_dir;
	struct list_head debug_list;

	struct te_device *tdev;
	struct ciplus_device *dev;

	u32 num_channel;
	struct lxdvb_ci14_channel channels[0];
};

struct lxdvb_ci14_up_fh {
	struct te_hwbuf buf;
	struct te_mem_ctx *mem_ctx;
	struct ciplus_ipd_dev* ip_dev;
};

struct lxdvb_ci14_dn_fh {
	struct te_hwbuf buf;
	struct te_mem_ctx *mem_ctx;
	struct ciplus_ipd_dev* ip_dev;
};

/* Private CI+1.4 information separate info for each opens */
struct lxdvb_ci14_fh {
	struct lxdvb_ci14_channel *channel;
	struct lxdvb_ci14_up_fh *up;
	struct lxdvb_ci14_dn_fh *dn;

	/* list of all pid filter set by this handle */
	struct list_head pid_filters;
};

struct lxdvb_ci14_pidf {
	bool used;
	u16 pid;
	struct ciplus_pidf *filter;
	struct list_head list;
};

#endif				//_LXDVB_CI14_H_
