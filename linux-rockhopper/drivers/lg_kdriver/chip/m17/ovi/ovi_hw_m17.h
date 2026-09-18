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
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

#ifndef  OVI_HW_M17_INC
#define  OVI_HW_M17_INC
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
int OVI_HW_M17_Initialize(void);
int OVI_HW_M17_Close(void);
int OVI_HW_M17_Resume(void);
int OVI_HW_M17_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_M17_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HW_M17_SetCombination(UINT32 param);
int OVI_HW_M17_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HW_M17_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams);
int OVI_HW_M17_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams);
int OVI_HW_M17_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams);
int OVI_HW_M17_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_M17_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HW_M17_SetColorTempEnable(BOOLEAN bParam);
int OVI_HW_M17_SetGammaEnable(BOOLEAN bParam);
int OVI_HW_M17_SetDitherEnable(BOOLEAN bParam);
int OVI_HW_M17_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HW_M17_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HW_M17_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HW_M17_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HW_M17_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams);
int OVI_HW_M17_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_M17_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam);
int OVI_HW_M17_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams);
int OVI_HW_M17_SetTconReverse(BOOLEAN bParam);
int OVI_HW_M17_SetLvdsReverse(BOOLEAN bParam);
int OVI_HW_M17_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HW_M17_SetChannelPower(BOOLEAN bParam);
int OVI_HW_M17_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HW_M17_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HW_M17_SetLvdsBlack(BOOLEAN bParam);
int OVI_HW_M17_SetClock(BOOLEAN bParam);
int OVI_HW_M17_SetEpiDataScramble(BOOLEAN bParam);
int OVI_HW_M17_SetAdvanced10bit(BOOLEAN bParam);
int OVI_HW_M17_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
int OVI_HW_M17_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
int OVI_HW_M17_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_M17_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_M17_INC  ----- */
/**  @} */

