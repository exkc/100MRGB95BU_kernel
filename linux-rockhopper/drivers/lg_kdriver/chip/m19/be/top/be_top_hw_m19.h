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
 *	BE TOP module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

#ifndef  BE_TOP_HW_M19_INC
#define  BE_TOP_HW_M19_INC
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
int BE_TOP_HW_M19_Initialize(void);
int BE_TOP_HW_M19_Close(void);
int BE_TOP_HW_M19_Resume(void);
int BE_TOP_HW_M19_SetBypass(LX_BE_BLOCK_BYPASS_T *pstParams);
int BE_TOP_HW_M19_Toggle3DLR(LX_BE_3D_LR_T *pstParams);
int BE_TOP_HW_M19_Set3DConvergence(LX_BE_3D_CONVERGENCE_T *pstParams);
int BE_TOP_HW_M19_SetBlackBar(LX_BE_BLACK_BAR_T *pstParams);
int BE_TOP_HW_M19_SetRealCinema(LX_BE_REAL_CINEMA_T *pstParams);
int BE_TOP_HW_M19_SetOrbit(LX_BE_ORBIT_T *pstParams);
int BE_TOP_HW_M19_SetLagParam(UINT32 bParam);
int BE_TOP_HW_M19_SetLagPatternParam(LX_BE_INPUT_LAG_PATTERN_T *pstParams);
int BE_TOP_HW_M19_SetLSRParam(LX_BE_LSR_T *pstParams);
int BE_TOP_HW_M19_SetGSR(LX_BE_GSR_T *pstParams);
int BE_TOP_HW_M19_GetGSRStatus(BOOLEAN *pbParam);
int BE_TOP_HW_M19_GetOSDAlphaAPL(LX_BE_LUT_T *pstParams);
int BE_TOP_HW_M19_SetOSDRGBLevel(LX_BE_OSD_RGB_LEVEL_T *pstParams);
int BE_TOP_HW_M19_SetDebugDisplay(LX_BE_DEBUG_DISPLAY_T *pstParams);
int BE_TOP_HW_M19_ProcHandler(BE_TOP_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_TOP_HW_M19_INC  ----- */
/**  @} */

