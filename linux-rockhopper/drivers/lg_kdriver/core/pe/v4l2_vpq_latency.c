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

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/seq_file.h>

#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-event.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-v4l2.h>
#include "linux/v4l2-ext/v4l2-ext-panel.h"
#include "linux/v4l2-ext/v4l2-ext-picturequality.h"

#include "os_util.h"
#include "debug_util.h"
#include "pe_def.h"
#include "pe_kwrap.h"
#include "v4l2_vpq_pe.h"
#include "v4l2_vpq_hdr.h"
#include "vpq_hwrap_hdr.h"

#include "v4l2_vpq_latency.h"
#include "v4l2_vsc_event.h"
#include "ovi_kapi.h"
//#include "../de/vp_kwrap.h"
#include "ovi_hal.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
// static UINT32 _gVideoLatency = 0;
static UINT32 _g_vpq_latency_dbg_value = 0;
static UINT32 _g_vpq_latency_dbg_set = 0;

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifndef V4L2_CID_EXT_VPQ_VIDEO_LATENCY
#define V4L2_CID_EXT_VPQ_VIDEO_LATENCY (V4L2_CID_EXT_VPQ_BASE + 37)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
static UINT32 _gPanelType = 0;
static UINT32 _gInputSrc = 0;
static UINT32 _gScanType = 0;
static UINT32 _gVfreq = 0;
static UINT32 _gLowdelayMode = 0;
static UINT32 _gPreLatency = 0;

int gIs8KModel = 0;
int gIs144HzModel = 0;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
int v4l2_vpq_latency_set_debug(UINT32 value);
UINT32 v4l2_vpq_latency_get_debug(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
LX_OVI_HW_DISPLAY_INFO_T hwOpt;

/*========================================================================================
	Implementation Group
========================================================================================*/

/*========================================================================================
	Staic Function Implementation Group
========================================================================================*/
void v4l2_vpq_update_panelType(UINT32 panel_type)
{
	_gPanelType = panel_type;
	PE_PRINT_NOTI("LATENCY inputSrc panelType: %d", _gPanelType);
	return;
}

void v4l2_vpq_update_inputSrc(UINT32 input_src)
{
	_gInputSrc = input_src;
	PE_PRINT_NOTI("LATENCY inputSrc inputSrc: %d", _gInputSrc);
	return;
}

void v4l2_vpq_update_scanType(UINT32 scan_type)
{
	_gScanType = scan_type;
	PE_PRINT_NOTI("LATENCY inputSrc Scantype: %d", _gScanType);
	return;
}

void v4l2_vpq_update_vFreq(UINT32 v_freq)
{
	_gVfreq = v_freq;
	PE_PRINT_NOTI("LATENCY inputSrc Vfreq: %d", _gVfreq);
	return;
}

void v4l2_vpq_update_lowDelay(UINT32 lowdelay)
{
	_gLowdelayMode = lowdelay;	
	PE_PRINT_NOTI("LATENCY inputSrc lowDelay: %d", _gLowdelayMode);
	return;
}

int v4l2_vpq_vidioc_g_ctrl_latency(struct file *file, void *__fh, struct v4l2_control *ctrl)
{
	int ret = 0;
	if (!file || !__fh || !ctrl)
	{
		PE_PRINT_ERROR("null\n");
		return -EINVAL;
	}
	switch (ctrl->id) {
		case V4L2_CID_EXT_VPQ_VIDEO_LATENCY:
		{
			if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
				_gPanelType = V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ;
			}
			else{ // ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ) 
				_gPanelType = V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ; 
			}

			if(_gPanelType == V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ)
			{
				if(_gLowdelayMode == 1) // LowDelay Mode
				{
					if(_gInputSrc == SRC_INPUT_HDMI)
					{
						if(_gVfreq > 1100) //120p
						{
							ctrl->value = 17;
						}
						else if(_gVfreq > 800) //100p
						{
							ctrl->value = 17;
						}
						else if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 50;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 50;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
						}
						else //24
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_INTERLACED)
							{
								ctrl->value = 66;
							}
						}
						else
						{
							ctrl->value = 66;
						}
					}
				}
				else // Normal Mode
				{
					if(_gInputSrc == SRC_INPUT_HDMI)
					{
						if(_gVfreq > 1100) //120p
						{
							ctrl->value = 42;
						}
						else if(_gVfreq > 800) //100p
						{
							ctrl->value = 43;
						}
						else if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 83;
							}
							else
							{
								ctrl->value = 116;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 86;
							}
							else
							{
								ctrl->value = 123;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 132;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 146;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 150;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 83;
							}
							else
							{
								ctrl->value = 116;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 86;
							}
							else
							{
								ctrl->value = 123;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 132;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 146;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 150;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
							else
							{
								ctrl->value = 100;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
							else
							{
								ctrl->value = 103;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
						}
						else //24
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
						}
					}
					if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_INTERLACED)
							{
								ctrl->value = 116;
							}
						}
						else
						{
							ctrl->value = 123;
						}
					}
				}
			}
			else	//V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ
			{
				if(_gLowdelayMode == 1) // LowDelay Mode
				{
					if(_gInputSrc == SRC_INPUT_HDMI)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 33;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 50;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
							else
							{
								ctrl->value = 50;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}
						}
						else //24
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 17;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_INTERLACED)
							{
								ctrl->value = 66;
							}
						}
						else
						{
							ctrl->value = 66;
						}
					}
				}
				else // Normal Mode
				{
					if(_gInputSrc == SRC_INPUT_HDMI)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 83;
							}
							else
							{
								ctrl->value = 116;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 86;
							}
							else
							{
								ctrl->value = 123;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 132;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 146;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 150;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 83;
							}
							else
							{
								ctrl->value = 116;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 86;
							}
							else
							{
								ctrl->value = 123;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 132;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 146;
							}
						}
						else
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 150;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
							else
							{
								ctrl->value = 100;
							}
						}
						else if(_gVfreq > 400) //50
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
							else
							{
								ctrl->value = 103;
							}
						}
						else if(_gVfreq > 275) //30
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
						}
						else if(_gVfreq > 245) //25
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}
						}
						else //24
						{
							if(_gScanType == VP_PROGRESSIVE)
							{
								ctrl->value = 66;
							}							
						}
					}
					if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
					{
						if(_gVfreq > 550) //60
						{
							if(_gScanType == VP_INTERLACED)
							{
								ctrl->value = 116;
							}
						}
						else
						{
							ctrl->value = 123;
						}
					}
				}
			}			
			PE_PRINT_NOTI("Panel:%d, Input:%d, Scan:%d, Vfreq:%d, Lowdelay:%d --> latency:%d ms\n",\
				_gPanelType,_gInputSrc,_gScanType,_gVfreq,_gLowdelayMode,ctrl->value);
		}break;
		default:
			PE_PRINT_ERROR("invalid id(0x%x)\n",ctrl->id);
			ret = -EINVAL;
			break;
	}
	return ret;
}

UINT32 v4l2_vpq_event_latency(void)
{
	int ret = 0;
	UINT32 value = 0;
	UINT32 temp = 0;
#ifdef BUILD_FEATURE_y29_board
	temp = 29;
#elif defined BUILD_FEATURE_y28_board
	temp = 28;
#elif defined BUILD_FEATURE_y27_board
	temp = 27;
#elif defined BUILD_FEATURE_y26_board
	temp = 26;
#elif defined BUILD_FEATURE_y25_board
	temp = 25;
#elif defined BUILD_FEATURE_y24_board
	temp = 24;
#elif defined BUILD_FEATURE_y23_board
	temp = 23;
#elif defined BUILD_FEATURE_y22_board
	temp = 22;
#endif
#if 0
	/* Check Year : o22n2/o24->24, o22n->23, o22->22, others->0  */
	if(RET_OK==OS_ScanKernelCmdline("pqe.year=%d",&temp))
	{
		year_option = temp;
	}
#endif
	if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) ){
		_gPanelType = V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ;
	}
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) ){
		_gPanelType = V4L2_EXT_VBE_PANEL_FRAMERATE_120HZ; 
	}

	#ifdef INCLUDE_KDRV_BE
	OVI_HAL_GetHWDisplayOption(&hwOpt);
	if(hwOpt.frcChipType > LX_OVI_FRC_CHIP_INTERNAL) {
		if (hwOpt.frcChipType == LX_OVI_FRC_CHIP_UD_BE_KLD) {
			gIs8KModel = 0;
		} else {
			gIs8KModel = 1;
		}
	}
	else
	{
		gIs8KModel = 0;
	}

	if(hwOpt.panelFramerate == LX_OVI_PANEL_FRAMERATE_144Hz)
	{
		gIs144HzModel = 1;
	}
	else
	{
		gIs144HzModel = 0;
	}
	#endif

	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23))
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 4;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 4;
					}
					else
					{
						value = 60;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 62;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 60;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 21;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 50;
					}
				}
				else
				{
					value = 60;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 67;
					}
					else
					{
						value = 100;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 80;
					}
					else
					{
						value = 120;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 83;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 113;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 67;
					}
					else
					{
						value = 100;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 80;
					}
					else
					{
						value = 120;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 83;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 113;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 100;
					}
				}
				else
				{
					value = 120;
				}
			}
		}
	}
	else if((!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22)) && gIs8KModel == 1 && temp <= 23) //O22+F22
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 0;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 0;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 8;
					}
					else
					{
						value = 67;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 10;
					}
					else
					{
						value = 80;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 8;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 10;
				}
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 20;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 21;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 67;
					}
				}
				else
				{
					value = 80;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 68;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 80;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 108;
					}
					else
					{
						value = 142;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 130;
					}
					else
					{
						value = 170;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 109;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 130;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 126;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 59;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 70;
				}
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 92;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 140;
					}
					else
					{
						value = 140;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 99;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 70;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 63;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 140;
					}
				}
				else
				{
					value = 160;
				}
			}
		}
	}
	else if((!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22)) && gIs8KModel == 1 && temp >= 24) //O22n2+F22
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 0;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 0;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 8;
					}
					else
					{
						value = 67;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 10;
					}
					else
					{
						value = 80;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 8;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 10;
				}
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 20;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 21;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 67;
					}
				}
				else
				{
					value = 80;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI || _gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 68;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 80;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 116;
					}
					else
					{
						value = 150;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 148;
					}
					else
					{
						value = 185;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 120;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 130;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 132;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 59;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 70;
				}
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 95;
					}
					else
					{
						value = 158;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 128;
					}
					else
					{
						value = 165;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 99;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 70;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 63;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 140;
					}
				}
				else
				{
					value = 160;
				}
			}
		}
	}
	else if((!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22)) && gIs8KModel == 0 && gIs144HzModel ==0) //O22
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 8;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 10;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 53;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 66;
					}
				}
				else
				{
					value = 73;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 42;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 53;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 75;
					}
					else
					{
						value = 108;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 78;
					}
					else
					{
						value = 115;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 125;
					}
				}
				else
				{
					value = 135;
				}
			}
		}
	}
	else if((!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22)) && gIs8KModel ==0 && gIs144HzModel ==1) //O22 144Hz
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 8;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 10;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 53;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 66;
					}
				}
				else
				{
					value = 73;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 42;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 53;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 75;
					}
					else
					{
						value = 108;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 78;
					}
					else
					{
						value = 131;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 125;
					}
				}
				else
				{
					value = 135;
				}
			}
		}
	}
	else if(!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24)) //O24 144Hz
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 8;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 10;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 53;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 66;
					}
				}
				else
				{
					value = 73;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 1100) //120p
				{
					value = 42;
				}
				else if(_gVfreq > 800) //100p
				{
					value = 53;
				}
				else if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 182;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 75;
					}
					else
					{
						value = 108;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 78;
					}
					else
					{
						value = 115;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 125;
					}
				}
				else
				{
					value = 135;
				}
			}
		}
	}
	else	//V4L2_EXT_VBE_PANEL_FRAMERATE_60HZ
	{
		if(_gLowdelayMode == 1) // LowDelay Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 66;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 20;
					}
					else
					{
						value = 73;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 33;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 40;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 42;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 50;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
					else
					{
						value = 53;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 17;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 66;
					}
				}
				else
				{
					value = 73;
				}
			}
		}
		else // Normal Mode
		{
			if(_gInputSrc == SRC_INPUT_HDMI)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 125;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_YPBPR || _gInputSrc == SRC_INPUT_VGA)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
					else
					{
						value = 125;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
					else
					{
						value = 135;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 124;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 138;
					}
				}
				else
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 142;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_DTV || _gInputSrc ==SRC_INPUT_MVI || _gInputSrc == SRC_INPUT_JPG)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 75;
					}
					else
					{
						value = 108;
					}
				}
				else if(_gVfreq > 400) //50
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 78;
					}
					else
					{
						value = 115;
					}
				}
				else if(_gVfreq > 275) //30
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 91;
					}
				}
				else if(_gVfreq > 245) //25
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 98;
					}
				}
				else //24
				{
					if(_gScanType == VP_PROGRESSIVE)
					{
						value = 100;
					}
				}
			}
			if(_gInputSrc == SRC_INPUT_ATV || _gInputSrc == SRC_INPUT_CVBS || _gInputSrc ==  SRC_INPUT_SCART || _gInputSrc == SRC_INPUT_SCART_RGB_BYPASS)
			{
				if(_gVfreq > 550) //60
				{
					if(_gScanType == VP_INTERLACED)
					{
						value = 125;
					}
				}
				else
				{
					value = 135;
				}
			}
		}
	}
	PE_PRINT_LATENCY("Panel:%d, Input:%d, Scan:%d, Vfreq:%d, Lowdelay:%d, 144HzModel: %d--> latency:%d ms\n",\
		_gPanelType,_gInputSrc,_gScanType,_gVfreq,_gLowdelayMode, gIs144HzModel, value);

	if(_gVfreq != 0)
	{
		if(_gPreLatency != value)
		{
			ret = value;
			_gPreLatency = value;
			PE_PRINT_NOTI("Panel:%d, Input:%d, Scan:%d, Vfreq:%d, Lowdelay:%d, 144HzModel: %d, 8K: %d, year_option: %d--> latency:%d ms\n",\
		_gPanelType,_gInputSrc,_gScanType,_gVfreq,_gLowdelayMode, gIs144HzModel, gIs8KModel, temp, value);
		}
 	}
	else
	{
		ret = 0;
	}

	if(_g_vpq_latency_dbg_set == 1)
	{
		ret = _g_vpq_latency_dbg_value;
		PE_PRINT_NOTI("Panel:%d, Input:%d, Scan:%d, Vfreq:%d, Lowdelay:%d, 144HzModel: %d--> latency:%d ms\n",\
		_gPanelType,_gInputSrc,_gScanType,_gVfreq,_gLowdelayMode, gIs144HzModel, value);
		_g_vpq_latency_dbg_set = 0;
	}
 	return ret;
}

int v4l2_vpq_latency_set_debug(UINT32 value)
{
	_g_vpq_latency_dbg_value =  value;
	_g_vpq_latency_dbg_set = 1;

	return 0;
}

UINT32 v4l2_vpq_latency_get_debug(void)
{
	return _g_vpq_latency_dbg_value;
}

