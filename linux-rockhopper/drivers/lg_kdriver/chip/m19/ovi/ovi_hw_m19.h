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

#ifndef  OVI_HW_M19_INC
#define  OVI_HW_M19_INC
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
int OVI_HW_M19_Initialize(void);
int OVI_HW_M19_Close(void);
int OVI_HW_M19_EarlyResume(void);
int OVI_HW_M19_Resume(void);
int OVI_HW_M19_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_M19_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HW_M19_SetCombination(UINT32 param);
int OVI_HW_M19_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HW_M19_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams);
int OVI_HW_M19_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams);
int OVI_HW_M19_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams);
int OVI_HW_M19_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_M19_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HW_M19_SetColorTempEnable(BOOLEAN bParam);
int OVI_HW_M19_SetGammaEnable(BOOLEAN bParam);
int OVI_HW_M19_SetDitherEnable(BOOLEAN bParam);
int OVI_HW_M19_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HW_M19_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HW_M19_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HW_M19_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HW_M19_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams);
int OVI_HW_M19_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HW_M19_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam);
int OVI_HW_M19_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams);
int OVI_HW_M19_SetTconReverse(BOOLEAN bParam);
int OVI_HW_M19_SetLvdsReverse(BOOLEAN bParam);
int OVI_HW_M19_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HW_M19_SetChannelPower(BOOLEAN bParam);
int OVI_HW_M19_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HW_M19_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HW_M19_SetLvdsBlack(BOOLEAN bParam);
int OVI_HW_M19_SetClock(BOOLEAN bParam);
int OVI_HW_M19_SetEpiDataScramble(BOOLEAN bParam);
int OVI_HW_M19_SetAdvanced10bit(BOOLEAN bParam);
int OVI_HW_M19_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
int OVI_HW_M19_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
int OVI_HW_M19_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HW_M19_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef OVI_HW_M19_INC  ----- */
/**  @} */

