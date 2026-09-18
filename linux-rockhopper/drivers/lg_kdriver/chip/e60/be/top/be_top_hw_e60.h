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

#ifndef  BE_TOP_HW_E60_INC
#define  BE_TOP_HW_E60_INC
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
int BE_TOP_HW_E60_Initialize(void);
int BE_TOP_HW_E60_Close(void);
int BE_TOP_HW_E60_Resume(void);
int BE_TOP_HW_E60_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams);
int BE_TOP_HW_E60_SetOrbit(LX_BE_ORBIT_T *pstParams);
int BE_TOP_HW_E60_SetLSRParam(LX_BE_LSR_T *pstParams);
int BE_TOP_HW_E60_SetLagParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams);
int BE_TOP_HW_E60_SetGSR(LX_BE_GSR_T *pstParams);
int BE_TOP_HW_E60_SetGSR2(LX_BE_GSR_T *pstParams);
int BE_TOP_HW_E60_GetGSRStatus(BOOLEAN *pbParam);
int BE_TOP_HW_E60_GetGSRStressCount(UINT32 *pu32Param);
int BE_TOP_HW_E60_SetCPC(UINT32 u32Param);
int BE_TOP_HW_E60_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams);
int BE_TOP_HW_E60_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams);
int BE_TOP_HW_E60_SetDispMode(LX_BE_DISP_MODE_T *pstParams);
int BE_TOP_HW_E60_SetVideoVReverse(BOOLEAN bParam);
int BE_TOP_HW_E60_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams);
int BE_TOP_HW_E60_SetFRCStatus(UINT32 u32Param);
int BE_TOP_HW_E60_InformFBDEVStatus(LX_BE_FBDEV_STATUS_T *pstParams);
int BE_TOP_HW_E60_GetFWOSDStatus(LX_BE_FW_OSD_STATUS_T *pstParams);
int BE_TOP_HW_E60_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_TOP_HW_E60_INC  ----- */
/**  @} */

