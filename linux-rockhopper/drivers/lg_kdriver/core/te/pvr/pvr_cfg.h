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
 *  main configuration file for pvr device
 *	pvr device will teach you how to make device driver with new platform.
 *
 *  author		kyungbin.pak
 *  version		1.0
 *  date		2010.02.05
 *  note		Additional information.
 *
 *  @addtogroup lg1150_pvr
 *	@{
 */

#ifndef	_PVR_CFG_H_
#define	_PVR_CFG_H_

#include <linux/types.h>

struct pvr_config {
	u8 num_dn;		/* number of download device */
	u8 num_up;		/* number of upload device */
	u8 swap_dn_timestamp;   /* little endian timestamp in M16A0 */
	u8 fixup_index_error;   /* index offset error in M16A0 */
	u8 no_pie;		/* no picture index extraction or not use */
	u8 fix_up_timestamp;    /* fix upload timestamp (M16, M16P Ax) */
	bool use_shared_mem;	/* true: O22 ~ */
	bool no_download_support; /* HD model does not support download */
};

struct pvr_config *pvr_get_config(void);

#endif				/* _PVR_CFG_H_ */

/** @} */
