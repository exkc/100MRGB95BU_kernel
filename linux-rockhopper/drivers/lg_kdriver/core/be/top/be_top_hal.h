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
 *  BE TOP module
 *
 *  author      dj911.kim@lge.com
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg115x_be
 *  @{
 */

#ifndef _BE_TOP_HAL_H_
#define _BE_TOP_HAL_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "be_kapi.h"
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

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int BE_TOP_HAL_PreInit(void);
int BE_TOP_HAL_Init(void);
int BE_TOP_HAL_Close(void);
int BE_TOP_HAL_Resume(void);

int BE_TOP_HAL_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams);
int BE_TOP_HAL_Toggle3DLR(LX_BE_3D_LR_T *pstParams);
int BE_TOP_HAL_Set3DConvergence(LX_BE_3D_CONVERGENCE_T *pstParams);
int BE_TOP_HAL_SetBlackBar(LX_BE_BLACK_BAR_T *pstParams);
int BE_TOP_HAL_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams);
int BE_TOP_HAL_SetRealCinema(LX_BE_REAL_CINEMA_T *pstParams);
int BE_TOP_HAL_SetOrbit(LX_BE_ORBIT_T *pstParams);
int BE_TOP_HAL_SetLSR(BOOLEAN bParam);
int BE_TOP_HAL_SetInputLagTest(UINT32 bParam);
int BE_TOP_HAL_SetInputLagPattern(LX_BE_INPUT_LAG_PATTERN_T *pstParams);
int BE_TOP_HAL_SetLSRParam(LX_BE_LSR_T *pstParams);
int BE_TOP_HAL_SetGSR(LX_BE_GSR_T *pstParams);
int BE_TOP_HAL_SetGSR2(LX_BE_GSR_T *pstParams);
int BE_TOP_HAL_GetGSRStatus(BOOLEAN *pbParam);
int BE_TOP_HAL_GetGSRStressCount(UINT32 *pu32Param);
int BE_TOP_HAL_SetCPC(UINT32 u32Param);
int BE_TOP_HAL_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams);
int BE_TOP_HAL_SetIrrAdaptedLum(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_GetIrrResult(UINT32 *pu32Param);
int BE_TOP_HAL_GetIrrStatus(LX_BE_IRR_STATUS_T *pstParams);
int BE_TOP_HAL_SetIrrData(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_GetIrrData(LX_BE_IRR_READ_T *pstParams);
int BE_TOP_HAL_SetTPCParam(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_GetTPCStatus(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_GetAplForTpc(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_SetOledAplCtrlParam(LX_BE_LUT_T *pstParams);
int BE_TOP_HAL_SetDispMode(LX_BE_DISP_MODE_T *pstParams);
int BE_TOP_HAL_SetVideoVReverse(BOOLEAN bParam);
int BE_TOP_HAL_SetFRCStatus(UINT32 u32Param);
int BE_TOP_HAL_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams);
int BE_TOP_HAL_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams);
int BE_TOP_HAL_SetPmMode(UINT32 u32Param);
int BE_TOP_HAL_SetOaplMaxWeight(int Param);
int BE_TOP_HAL_Get_PatternInfo(void *pParam, UINT32 *size);
int BE_TOP_HAL_SetDClock(UINT32 *pstParams);
int BE_TOP_HAL_GetDispApl(UINT32 *pstParams);
int BE_TOP_HAL_SetGenlock(LX_BE_SET_GENLOCK_T *pstParams);
int BE_TOP_HAL_SetPcce(LX_BE_IPC_PCCE_T *pstParams);
int BE_TOP_HAL_SetOutputTiming(LX_OVI_TCON_OUTPUT_TIMING_T *pstParams);
int BE_TOP_HAL_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _BE_TOP_HAL_H_ */

/** @} */

