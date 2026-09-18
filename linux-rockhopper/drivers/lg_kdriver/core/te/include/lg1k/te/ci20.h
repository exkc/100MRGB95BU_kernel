/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  CI2.0 API header for linux dvb_delivery
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date	2020-08-05
 *  @note	Additional information.
 */

#ifndef _LG1K_TE_CI20_H_
#define _LG1K_TE_CI20_H_

struct ci20_dump_cfg {
	struct te_hwbuf *data;
};

struct ci20_device;
struct ci20_channel;
struct ci20_input_dump;

struct ci20_device *ci20_get_device(struct te_device *dev);
struct ci20_channel *ci20_get_channel(struct ci20_device *dev, u8 num);
int ci20_config_channel_input(struct ci20_channel *channel,
			      enum lx_te_input_port port,
			      bool reset, bool enable);
struct ci20_input_dump *ci20_start_input_dump(struct ci20_channel *channel,
					      struct ci20_dump_cfg *cfg);
int ci20_stop_input_dump(struct ci20_input_dump *dump);
ssize_t ci20_read_data(struct ci20_channel *channel, char __user *buf,
		       size_t size);
unsigned int ci20_wait_data(struct ci20_channel *channel, struct file *file,
			    struct poll_table_struct *wait);
int ci20_module_init(void);
void ci20_module_exit(void);

#endif				//_LG1K_TE_CI20_H_
