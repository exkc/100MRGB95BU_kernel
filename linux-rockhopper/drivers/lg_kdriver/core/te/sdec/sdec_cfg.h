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
 *  main configuration file for sdec device
 *  sdec device will teach you how to make device driver with new platform.
 *
 *  @author	Jihoon Lee ( gaius.lee@lge.com)
 *  @author	Jinhwan Bae ( jinhwan.bae@lge.com) - modifier
 *  @version	1.0
 *  @date		2010-03-30
 *  @note		Additional information.
 */

#ifndef	_SDEC_CFG_H_
#define	_SDEC_CFG_H_

#include "te_sdec_kapi.h"

struct sdec_channel_info {
	u8 num_pidf;		///< number of pid filter in this channel
	u8 num_secf;		///< number of section filter in this channel
	u8 is_sub_channel;	///< this channel is sub channel
	u8 sub_ch_num;		/* sub channel number */
};

struct sdec_config {
	u8 num_channel;		/* number of channels */
	u8 num_sub_channel;	/* number of sub channels */
	u8 num_vdec_out;	/* number of vdec output port */
	u8 num_adec_out;	/* number of adec output port */
	u16 num_pid_filter;	/* number of pid filter */
	u16 num_stream_filter;	/* number of stream filter */
	u16 num_temi_filter;

	bool fixup_pcr_latch_bug;

	u8 input_dump_channel;	/* channel for input dump */
	LX_SDEC_DUMP_TIMESRC_T default_dump_clk;	/* default clock source for dump timestamp */

	struct sdec_channel_info *ch_info;	/* channel information */
};

struct sdec_config *sdec_get_config(void);

#endif				/* _SDEC_CFG_H_ */

/** @} */
