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

#ifndef	_LG1K_TE_ATSC3_H_
#define	_LG1K_TE_ATSC3_H_

#include <lg1k/te/te.h>
#include <linux/poll.h>

#include "te_atsc3_kapi.h"

struct atsc3_dump_cfg {
	enum te_reg_atsc3_layer layer;
	enum te_reg_dumper_mode mode;
	struct te_hwbuf *data;
	struct te_hwbuf *meta;
	u32 flags;
};


struct atsc3_device;
struct atsc3_channel;
struct atsc3_config;

struct atsc3_device *atsc3_get_device(struct te_device *dev);
struct atsc3_channel *atsc3_get_channel(struct atsc3_device *dev, u8 num);

int atsc3_get_chip_config(struct atsc3_device *dev,
			  struct lx_atsc3_chip_cfg *cfg);

int atsc3_config_channel_input(struct atsc3_channel *channel,
			       struct lx_atsc3_channel_input_cfg *cfg);
int atsc3_io_set_channel_enable(struct atsc3_channel *channel, bool enable);

int atsc3_set_system_time_info(struct atsc3_channel *channel,
			       struct lx_atsc3_system_time_info * param);
int atsc3_set_time(struct atsc3_channel *channel, struct lx_atsc3_time *param);
int atsc3_get_time(struct atsc3_channel *channel, struct lx_atsc3_time *param);
int atsc3_set_clock_recovery(struct atsc3_channel *channel,
			     enum lx_atsc3_clock_recovery param);

int atsc3_set_demod_type(struct atsc3_channel *channel,
			 enum lx_atsc3_demod_type type);

struct atsc3_input_dump *atsc3_start_input_dump(struct atsc3_channel *channel,
						struct atsc3_dump_cfg *cfg);
int atsc3_stop_input_dump(struct atsc3_input_dump *dump);
ssize_t atsc3_read_data(struct atsc3_channel *channel, char __user *data, size_t size);
unsigned int atsc3_wait_data(struct atsc3_channel *channel, struct file *file,
			     struct poll_table_struct *wait);
unsigned int atsc3_wait_clock(struct atsc3_channel *channel, struct file *file,
			      struct poll_table_struct *wait);

void ATSC3_CLOCK_SetTimeInfo(u64 timeinfo, u32 diff_usec);
int atsc3_set_debug_adjust_clock(struct atsc3_channel *channel, int *table,
				 u32 size);

#define ATSC3_DUMP_FLAG_WORKQUEUE	(0x1 << 0)

#endif				/* _LG1K_TE_ATSC3_H_ */
