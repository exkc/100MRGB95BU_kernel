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

#ifndef _LXDVB_DELIVERY_H_
#define _LXDVB_DELIVERY_H_

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <media/dvbdev.h>
#else
#include "dvbdev.h"
#endif

#include <linux/dvbv5-ext/dvbv5-ext-delivery.h>

enum delivery_dump_state {
	DELIVERY_DUMP_STATE_IDLE = 0,
	DELIVERY_DUMP_STATE_RUNNING,
};

struct delivery_dump_dev {
	u8 ch;
	volatile enum delivery_dump_state state;
	uint32_t timeout;

	struct te_mem_ctx *mem;
	struct te_hwbuf data;
	struct te_hwbuf meta;

	bool use_meta;

	void *dev;
	//monitor
};

struct delivery_input_cfg {
	enum lx_te_input_port port;
	enum lx_te_input_mode mode;
};

struct delivery_debug_dump {
	bool running;
	struct mutex mutex;
	struct te_hwbuf *buf;
};

struct lxdvb_delivery_channel {
	u8 idx;
//	bool exit;	//check necessary
	const struct dvb_function *func;
	struct lxdvb_delivery *delivery;
	struct dvb_device *dvbdev;
	struct delivery_dump_dev dump;

	struct mutex mutex;
	struct delivery_input_cfg input_cfg;
	struct delivery_ext_source input_params;
	bool clock_recovery;

	struct te_debug_dir *debug_dir;
	struct delivery_debug_dump debug_dump;
	void *dev;
	u64 user_read_size;
};

struct lxdvb_delivery {
	enum delivery_ext_mode mode;
	int demod_type;
	struct te_device *tdev;
	struct te_mem_ctx *mem;

	void *dev;
	struct te_debug_dir *debug_dir;
	u8 num_channel;
	struct lxdvb_delivery_channel channels[0];
};

struct lxdvb_delivery_fh {
	struct lxdvb_delivery *delivery;
	struct lxdvb_delivery_channel *channel;
	enum delivery_ext_mode mode;
	enum delivery_ext_event event;
};

#endif				/* _LXDVB_DELIVERY_H_ */
