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
 *  CIPLUS Driver
 *
 *  @author	Ilkyu Kim (ilkyu.kim@lge.com)
 *  @version	1.0
 *  @date		2015-06-03
 *  @note		Additional information.
 */

#ifndef	_LG1K_TE_CIPLUS_H_
#define	_LG1K_TE_CIPLUS_H_

#include <lg1k/te/te.h>
#include <lg1k/te/buffer.h>
#include <lg1k/te/mem.h>
#include "te_kapi.h"

/* not visible */
struct ciplus_device;
struct ciplus_channel;
struct ciplus_ipd_dev;
struct ciplus_pidf;

struct ciplus_device *ciplus_get_device(struct te_device *dev);
int ciplus_get_channel_info(struct ciplus_device *dev,
			    int *num_ch, int *num_pidf);
struct ciplus_channel *ciplus_get_channel(struct ciplus_device *dev, u8 idx);
struct te_mem_ctx *ciplus_get_mem_ctx(struct ciplus_device *dev);

int ciplus_set_input(struct ciplus_channel *channel,
		     enum lx_te_input_port port, bool ip_play, bool en);
void ciplus_get_input(struct ciplus_channel *channel,
		      enum lx_te_input_port *port, bool *ip_play, bool *en);
int ciplus_start_upload(struct ciplus_channel *channel,
			struct te_hwbuf *buf, struct ciplus_ipd_dev **pdev);
void ciplus_stop_upload(struct ciplus_channel *channel,
			struct ciplus_ipd_dev *dev);
int ciplus_start_download(struct ciplus_channel *channel,
			  struct te_hwbuf *buf, struct ciplus_ipd_dev **pdev);
void ciplus_stop_download(struct ciplus_channel *channel,
			  struct ciplus_ipd_dev *dev);
void ciplus_set_hostplayer(struct ciplus_channel *channel, bool host_player);
void ciplus_get_hostplayer(struct ciplus_channel *channel, bool *host_player);
int ciplus_set_pid(struct ciplus_channel *channel, u16 pid,
		   struct ciplus_pidf **pfilter);
void ciplus_free_pid(struct ciplus_channel *channel,
		     struct ciplus_pidf *filter);
int ciplus_get_outputrates(struct ciplus_channel *channel, s64 *rates);
int ciplus_set_debug_mode(struct ciplus_device *dev, bool mode);
void ciplus_get_debug_mode(struct ciplus_device *dev, bool *mode);

#endif				/* _LG1K_TE_CIPLUS_H_ */
