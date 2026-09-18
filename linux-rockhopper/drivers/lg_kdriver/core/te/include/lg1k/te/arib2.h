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
 *  @date	2018-10-12
 *  @note	Additional information.
 */

#ifndef	_LG1K_TE_ARIB2_H_
#define	_LG1K_TE_ARIB2_H_

#include <lg1k/te/te.h>
#include <lg1k/te/buffer.h>
#include <linux/poll.h>
#include "te_arib2_kapi.h"

struct arib2_dump_cfg {
	enum te_reg_dumper_mode mode;
	struct te_hwbuf *data;
	struct te_hwbuf *meta;
	u32 flags;
};

struct arib2_device;
struct arib2_channel;
struct arib2_input_dump;

struct arib2_device *arib2_get_device(struct te_device *dev);
struct arib2_channel *arib2_get_channel(struct arib2_device *dev, u8 num);

int arib2_config_channel_input(struct arib2_channel *channel,
			       LX_ARIB2_CHANNEL_INPUT_CFG_T *cfg);

int arib2_set_time(struct arib2_channel *channel, struct lx_arib2_time *param);
int arib2_get_time(struct arib2_channel *channel, struct lx_arib2_time *param);
int arib2_set_clock_recovery(struct arib2_channel *channel,
			     enum lx_arib2_clock_recovery param);

struct arib2_input_dump *arib2_start_input_dump(struct arib2_channel *channel,
						struct arib2_dump_cfg *cfg);
int arib2_stop_input_dump(struct arib2_input_dump *dev);
ssize_t arib2_read_data(struct arib2_channel *channel, char __user *data, size_t size);
unsigned int arib2_wait_data(struct arib2_channel *channel,
			     struct file *file, struct poll_table_struct *wait);
unsigned int arib2_wait_clock(struct arib2_channel *channel, struct file *file,
			      struct poll_table_struct *wait);

#define ARIB2_DUMP_FLAG_WORKQUEUE	(0x1 << 0)

#endif				/* _LG1K_TE_ARIB2_H_ */
