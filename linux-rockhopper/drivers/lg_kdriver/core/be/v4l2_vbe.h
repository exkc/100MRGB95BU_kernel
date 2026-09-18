/*
    SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
    Copyright(c) 2020 by LG Electronics Inc.

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    version 2 as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
*/

/** @file v4l2_vbe.h
 *
 *  It is the header file for controling v4l2 BE driver.
 *
 *  @author juhwan.park
 *  @version 1.0
 *  @date  2018.10.12
 *  @see
 */

#ifndef _V4L2_VBE_H
#define _V4L2_VBE_H

#include "linux/v4l2-ext/v4l2-ext-renderer.h"
#include "be_kapi.h"

typedef struct
{
	UINT32					pd_en;		///< pull down enable, 0:off,1:auto
	UINT32					pd_stat;	///< pull down state
	LX_BE_FRC_CFG_T			cfg;		///< cfg
	LX_BE_FRC_MEMC_MODE_T	memc;		///< memc
	LX_BE_FRC_LOW_DELAY_T	lowDelay;	///< lowDelay Mode
	LX_BE_FRC_MOTION_PRO_T	motionPro;	///< motionPro Mode
}
BE_FRC_INFO_T;

char *vbe_ctrl_id_to_str(int id);
int v4l2_vbe_device_init(void);
int v4l2_vbe_set_latency_pattern(BOOLEAN flag, UINT8 win, struct v4l2_ext_vsc_latency_pattern_info *p);
int vbe_sync_handler(void);
int vbe_noti_chg_clk_wait(void);
int vbe_noti_chg_clk_done(unsigned int clk);

#endif  /* _V4L2_VBE_H */

