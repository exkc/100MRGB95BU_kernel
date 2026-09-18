/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

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
 *	OVI module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

#ifndef  OVI_HW_O18_INC
#define  OVI_HW_O18_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/
int OVI_HW_O18_Initialize(void);
int OVI_HW_O18_Close(void);
int OVI_HW_O18_Resume(void);
int OVI_HW_O18_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O18_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HW_O18_SetCombination(UINT32 param);
int OVI_HW_O18_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HW_O18_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O18_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HW_O18_SetColorTempEnable(BOOLEAN bParam);
int OVI_HW_O18_SetGammaEnable(BOOLEAN bParam);
int OVI_HW_O18_SetDitherEnable(BOOLEAN bParam);
int OVI_HW_O18_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HW_O18_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HW_O18_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HW_O18_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HW_O18_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_O18_SetTconReverse(BOOLEAN bParam);
int OVI_HW_O18_SetLvdsReverse(BOOLEAN bParam);
int OVI_HW_O18_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HW_O18_SetChannelPower(BOOLEAN bParam);
int OVI_HW_O18_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HW_O18_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HW_O18_SetLvdsBlack(BOOLEAN bParam);
int OVI_HW_O18_SetClock(BOOLEAN bParam);
int OVI_HW_O18_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam);
int OVI_HW_O18_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_O18_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_O18_INC  ----- */
/**  @} */

