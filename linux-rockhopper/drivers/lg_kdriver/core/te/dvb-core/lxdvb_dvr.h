/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2018 by LG Electronics Inc.
 *
 * Parts of this file were based on sources as follows:
 *
 * dmxdev.h
 *
 * Copyright (C) 2000 Ralph Metzler & Marcus Metzler
 *                    for convergence integrated media GmbH
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

#ifndef _LXDVB_DVR_H_
#define _LXDVB_DVR_H_

#include <linux/types.h>
#include <linux/spinlock.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/dvb/dmx.h>
#include <linux/dvbv5-ext/dvbv5-ext-pvr.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>
#else
#include "dvbdev.h"
#endif

#include <lg1k/te/debug.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/pvr.h>

enum lxdvb_dvr_state {
	LXDVB_DVR_STATE_IDLE = 0,
	LXDVB_DVR_STATE_OPEN,
	LXDVB_DVR_STATE_START,
};

typedef int (*lxdvb_dvr_callback_t)(const u8 *buf1, size_t len1,
				    const u8 *buf2, size_t len2, void *priv);

/**
 * struct lxdvb_dvr_fh - file handle for dvr device
 *
 */
struct lxdvb_dvr_fh {
	struct lxdvb_dvr_channel *channel;
	struct lxdvb_dvr_up *up;
	struct lxdvb_dvr_dn *dn;
};

struct dvr_debug_dump {
	bool running;
	struct mutex mutex;
	struct te_hwbuf *buf;
};
struct lxdvb_dvr_up {
	u32 dst;
	enum lxdvb_dvr_state state;
	struct pvr_up *dev;
	struct te_mem_ctx *mem;
	struct te_hwbuf hbuf;
	int speed;
	int writing;
	u32 wsize;
	u32 pkt_len;

	struct dvr_debug_dump dump;

	struct mutex mutex;
	spinlock_t lock;
	bool usb_ci_mode;
};

struct lxdvb_dvr_dn {
	u32 src;
	bool valid;
	enum lxdvb_dvr_state state;
	struct pvr_dn *dev;
	struct te_mem_ctx *mem;
	struct te_hwbuf hbuf;
	u32 rsize;
	u32 pkt_len;
	struct dvr_debug_dump dump;
	int reading;

	struct mutex mutex;
	spinlock_t lock;
	bool usb_ci_mode;
};

struct lxdvb_dvr_channel {
	u8 idx;
	struct lxdvb_dvr *dvr;
	struct dvb_device *dvbdev;
	struct lxdvb_dvr_up up;
	struct lxdvb_dvr_dn dn;
	struct lxdvb_dmx_channel *dmx;
};

struct lxdvb_dvr {
	bool exit;
	struct te_debug_dir *debug_dir;
	struct lxdvb_proc_dir *proc_dir;
	struct pvr_device *pvr_dev;

	u8 num_channel;
	struct te_device *tdev;
	struct te_mem_ctx *mem[2];	/*mem[0]:pvr, mem[1]:te_shared */

	struct lxdvb_dvr_channel channels[0];
};

#endif				/* _LXDVB_DVR_H_ */
