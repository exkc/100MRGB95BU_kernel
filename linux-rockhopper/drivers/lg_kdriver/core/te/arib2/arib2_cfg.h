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
 *  main configuration file for arib2 device
 *	arib2 device will teach you how to make device driver with new platform.
 *
 *  author		yeonju.lee
 *  version		1.0
 *  date		2017.11.21
 *  note		Additional information.
 *
 *  @addtogroup
 *	@{
 */

#ifndef	_ARIB2_CFG_H_
#define	_ARIB2_CFG_H_

#include <linux/types.h>

#ifdef INCLUDE_O18_CHIP_KDRV
#define SUPPORT_SWTLV_FUNC
#endif

struct arib2_config {
	u8 swtlv;		/* use sw tlv. m16++/m16p3:0, o18:1 */
	u8 num_ch;		/* number of channels */
	u8 num_tlvf;		/* number of tlv(si) filters */
	u8 num_ipf;		/* number of ip filters */
	u8 num_mmt_pidf;	/* number of mmt_pid filters */
	u8 num_mmt_sif;		/* number of mmt_si filters */
	u8 num_mmt_avf;		/* number of mmt_av filters */
};

struct arib2_config *arib2_get_config(void);

#endif				/* ARIB2_CFG_H_ */

/** @} */
