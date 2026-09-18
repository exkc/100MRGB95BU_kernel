/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2016 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/** @file
 *
 *  Brief description.
 *  Detailed description starts here.
 *
 *  @author		
 *  @version	1.0
 *  @date		
 *  @note		Additional information.
 */

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
#if 0 
typedef enum
{
 	NORMAL_MODE,
	GAME_MODE,
	MODE_NUM_MAX
} VPQ_GAMEMODE_T;

typedef enum 
{
	PANEL_FRAMERATE_60HZ,
	PANEL_FRAMERATE_120HZ,
	PANEL_FRAMERATE_MAX
} VPQ_PANEL_FRAMERATE_T;

typedef enum
{
	VPQ_INPUT_HDMI,
	VPQ_INPUT_COMP,
	VPQ_INPUT_DTV_USB,
	VPQ_INPUT_ATV_CVBS,
	VPQ_HWRAP_INPUT_MAX		///< max num
} VPQ_INPUT_t;		// HAL_VPQ_INPUT_T

typedef enum
{
	VPQ_INTERLACED,		///< interlaced scan
	VPQ_PROGRESSIVE,	///< progressive scan
	VPQ_SCAN_TYPE_MAX		///< max num
} VPQ_SCAN_TYPE_t;		// HAL_VPQ_INPUT_T

typedef enum
{
	vFreq120,
	vFreq100,
	vFreq60,
	vFreq50,
	vFreq30,
	vFreq25,
	vFreq24,
	VPQ_V_FREQ_MAX		///< max num
} VPQ_V_FREQ_t;		// HAL_VPQ_INPUT_T
#endif

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#ifndef _V4L2_VPQ_LATENCY_H
#define _V4L2_VPQ_LATENCY_H

#include <media/v4l2-ctrls.h>

extern int v4l2_vpq_vidioc_g_ctrl_latency(struct file *file, void *__fh, struct v4l2_control *ctrl);
extern UINT32 v4l2_vpq_event_latency(void);
extern void v4l2_vpq_update_panelType(UINT32 panel_type);
extern void v4l2_vpq_update_inputSrc(UINT32 input_src);
extern void v4l2_vpq_update_scanType(UINT32 scan_type);
extern void v4l2_vpq_update_vFreq(UINT32 v_freq);
extern void v4l2_vpq_update_lowDelay(UINT32 lowdelay);

#endif  /* _V4L2_VPQ_LATENCY_H */

