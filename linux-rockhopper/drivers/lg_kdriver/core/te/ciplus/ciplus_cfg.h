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
 *  @date		2015-02-27
 *  @note		Additional information.
 */

#ifndef	_CIPLUS_CFG_H_
#define	_CIPLUS_CFG_H_

#include <linux/types.h>

struct ciplus_config {
	u8 num_dev;		/* number of devices */
	u8 num_ch;		/* number of demuxes */
	u8 num_pidf;

	u8 use_cinport;		/* M16+ introduces cinport for ciplus only */
	u8 use_pktcnt;		/* L18F introduces pkt_cnt for precise bitrate */
};

struct ciplus_config *ciplus_get_config(void);

#endif				/* _CIPLUS_CFG_H_ */

/** @} */
