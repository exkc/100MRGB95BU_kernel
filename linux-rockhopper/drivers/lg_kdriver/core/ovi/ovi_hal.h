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
 *  OVI module
 *
 *  author      dj911.kim@lge.com
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg115x_ovi
 *  @{
 */

#ifndef _OVI_HW_H_
#define _OVI_HW_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/
#ifndef TO_STR
#define TO_STR(x)	#x
#endif

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	OVI_HAL_PROC_ID_DETAIL_INFO,
	OVI_HAL_PROC_ID_DISP_OUTPUT_INFO,
	OVI_HAL_PROC_ID_MIRROR_VERTICAL_INFO,
	OVI_HAL_PROC_ID_DEBUG,
	OVI_HAL_PROC_ID_DRAW_PATTERN,
	OVI_HAL_PROC_ID_MAX
}
OVI_HAL_PROC_ID_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int OVI_HAL_PreInit(void);
int OVI_HAL_Init(void);
int OVI_HAL_Suspend(void);
int OVI_HAL_EarlyResume(void);
int OVI_HAL_Resume(void);
int OVI_HAL_SetDisplayOption(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HAL_SetBypass(LX_OVI_TCON_BYPASS_T *pstParams);
int OVI_HAL_SetCombination(UINT32 param);
int OVI_HAL_SetSpreadSpectrum(LX_OVI_SPREAD_SPECTRUM_T *pstParams);
int OVI_HAL_SetMcuCommand(LX_OVI_TCON_MCU_CMD_T *pstParams);
int OVI_HAL_UpdateFirmware(LX_OVI_TCON_FW_DWLD_T *pstParams);
int OVI_HAL_GetFirmwareVersion(LX_OVI_TCON_FW_VER_T *pstParams);
int OVI_HAL_SetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HAL_SetLodLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HAL_SetPodLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HAL_SetFrameOdcEnable(BOOLEAN bParam);
int OVI_HAL_SetColorTempEnable(BOOLEAN bParam);
int OVI_HAL_SetGammaEnable(BOOLEAN bParam);
int OVI_HAL_SetDitherEnable(BOOLEAN bParam);
int OVI_HAL_SetLineOdcMode(LX_OVI_TCON_LINEOD_MODE_T *pstParams);
int OVI_HAL_SetDitherMode(LX_OVI_TCON_DITHER_T enParam);
int OVI_HAL_SetColorTemp(LX_OVI_TCON_COLOR_TEMP_T *pstParams);
int OVI_HAL_SetMultiWindow_Gamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams);
int OVI_HAL_GetMultiWindow_Gamut(LX_OVI_MULTIWIN_GAMUT_T *pstParams);
int OVI_HAL_SetGamma(LX_OVI_TCON_GAMMA_T *pstParams);
int OVI_HAL_SetGammaRGBW(LX_OVI_TCON_GAMMA_RGBW_T *pstParams);
int OVI_HAL_GetOdLut(LX_OVI_TCON_OD_DWLD_T *pstParams);
int OVI_HAL_SetMleMode(LX_OVI_TCON_MLE_MODE_T enParam);
int OVI_HAL_SetTscic(LX_OVI_TCON_TSCIC_T *pstParams);
int OVI_HAL_SetDemura(LX_OVI_TCON_DEMURA_T *pstParams);
int OVI_HAL_SetTconHReverse(BOOLEAN bParam);
int OVI_HAL_SetLvdsHReverse(BOOLEAN bParam);
int OVI_HAL_SetPatternGenerator(LX_OVI_TCON_PATTERN_GEN_T *pstParams);
int OVI_HAL_SetChannelPower(BOOLEAN bParam);
int OVI_HAL_SetLvdsFormat(LX_OVI_LVDS_OUT_STD_T enParam);
int OVI_HAL_SetLvdsBitDepth(LX_OVI_BIT_DEPTH_T enParam);
int OVI_HAL_SetLvdsBlack(BOOLEAN bParam);
int OVI_HAL_SetClock(BOOLEAN bParam);
int OVI_HAL_SetEpiDataScramble(BOOLEAN bParam);
int OVI_HAL_SetAdvanced10bit(BOOLEAN bParam);
int OVI_HAL_SetVCOMPatternData(LX_OVI_TCON_VCOM_PAT_DATA_T *pstParam);
int OVI_HAL_SetVCOMPatternCtrl(LX_OVI_TCON_VCOM_PAT_CTRL_T enParam);
int OVI_HAL_SetDispOutputMode(LX_OVI_DISP_OUTPUT_MODE_T enParam);
int OVI_HAL_DisplayResume(LX_OVI_DISPLAY_INFO_T *pstParams);
int OVI_HAL_SetPempItune(LX_OVI_DISP_PEMP_ITUNE_DATA_T *pstParams);
int OVI_HAL_GetLockStatus(BOOLEAN *pbParam);
int OVI_HAL_GetHWDisplayOption(LX_OVI_HW_DISPLAY_INFO_T *pstParams);
int OVI_HAL_SetPmMode(UINT32 u32Param);
int OVI_HAL_UpdateChipInfoHeader(void);
int OVI_HAL_SetPCLRC(LX_OVI_PCLRC_LUT_T *pstParams);
int OVI_HAL_SetDispOutMute(UINT32 u32Param);
int OVI_HAL_SetDClock(UINT32 *pstParams);
int OVI_HAL_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams);
int OVI_HAL_GetStatus(UINT32 *pstParams);
int OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_T proc_id, struct seq_file* m, void* data);
int ovi_hal_clk_ctrl(struct ovi_clk_ctrl *p_ctrl);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _OVI_HW_H_ */

/** @} */

