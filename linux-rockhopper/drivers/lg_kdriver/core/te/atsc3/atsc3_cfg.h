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
 *  atsc3 device driver
 *
 *  author		yeonju.lee
 *  version		1.0
 *  date		2016.02.29
 *  note		Additional information.
 *
 *	@{
 */

#ifndef	_ATSC3_CFG_H_
#define	_ATSC3_CFG_H_

#include <linux/types.h>

struct atsc3_config {
	u8 num_ch;		/* number of channels */
	u8 num_plpf;		/* number of plp filter in this channel */
	u8 num_linksignalf;	/* number of linksignal filter in this channel */
	u8 num_ipf;		/* number of ip filter in this channel */
	u8 num_udpf;		/* number of upd filter in this channel */
	bool fixup_dumper;	/* RAW mode not support time latch */
	bool use_engine_sel;	/* engine selector is deprecated (since M23) */
};

struct atsc3_config *atsc3_get_config(void);

#endif				/* _ATSC3_CFG_H_ */

/** @} */
