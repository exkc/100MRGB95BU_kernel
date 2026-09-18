/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

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
 *	BE TOP module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

#ifndef  BE_TOP_HW_O20_INC
#define  BE_TOP_HW_O20_INC
/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "be_kapi.h"

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
int BE_TOP_HW_O20_Initialize(void);
int BE_TOP_HW_O20_Close(void);
int BE_TOP_HW_O20_Resume(void);
int BE_TOP_HW_O20_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams);
int BE_TOP_HW_O20_SetOrbit(LX_BE_ORBIT_T *pstParams);
int BE_TOP_HW_O20_SetLSRParam(LX_BE_LSR_T *pstParams);
int BE_TOP_HW_O20_SetLagParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams);
int BE_TOP_HW_O20_SetGSR(LX_BE_GSR_T *pstParams);
int BE_TOP_HW_O20_SetGSR2(LX_BE_GSR_T *pstParams);
int BE_TOP_HW_O20_GetGSRStatus(BOOLEAN *pbParam);
int BE_TOP_HW_O20_GetGSRStressCount(UINT32 *pu32Param);
int BE_TOP_HW_O20_SetCPC(UINT32 u32Param);
int BE_TOP_HW_O20_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams);
int BE_TOP_HW_O20_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams);
int BE_TOP_HW_O20_SetDispMode(LX_BE_DISP_MODE_T *pstParams);
int BE_TOP_HW_O20_SetVideoVReverse(BOOLEAN bParam);
int BE_TOP_HW_O20_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams);
int BE_TOP_HW_O20_SetFRCStatus(UINT32 u32Param);
int BE_TOP_HW_O20_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams);
int BE_TOP_HW_O20_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams);
int BE_TOP_HW_O20_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);
int BE_TOP_HW_O20_SetPmMode(UINT32 u32Param);
int BE_TOP_HW_O20_GetPatternInfo(void *pParam, UINT32 *size);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_TOP_HW_O20_INC  ----- */
/**  @} */

