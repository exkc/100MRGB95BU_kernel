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
 *	BE LED module control Drivers linux module
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_be
 *	@{
 */

#ifndef  BE_LED_HW_O18_INC
#define  BE_LED_HW_O18_INC
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
int BE_LED_HW_O18_Initialize(void);
int BE_LED_HW_O18_Close(void);
int BE_LED_HW_O18_Resume(void);

int BE_LED_HW_O18_Set_Mode(LX_BE_LED_MODE_T *pstParams);
int BE_LED_HW_O18_Control(LX_BE_LED_CONTROL_T *pstParams);
int BE_LED_HW_O18_Get_Apl(LX_BE_LED_APL_T *pstParams);
int BE_LED_HW_O18_Set_ClippingValue(UINT32 u32Param);
int BE_LED_HW_O18_Get_RegInfo(LX_BE_LED_REG_INFO_T *pstParams);

int BE_WCG_HW_O18_Calculate_FWLutSize(LX_BE_WCG_CALC_FW_LUT_SIZE_T *pstParams);
int BE_WCG_HW_O18_Get_FWLut(LX_BE_WCG_FW_LUT_T *pstParams);
int BE_WCG_HW_O18_Set_Mode(LX_BE_WCG_MODE_T *pstParams);
int BE_WCG_HW_O18_Control(LX_BE_WCG_CONTROL_T *pstParams);

int BE_PQ_HW_O18_Set_Pcc(LX_BE_PQ_PCC_T *pstParams);
int BE_PQ_HW_O18_Set_Gamma(BOOLEAN bParam);
int BE_PQ_HW_O18_Set_DeGamma(BOOLEAN bParam);
int BE_PQ_HW_O18_Set_PccGamma(LX_BE_PQ_PCC_GAMMA_T *pstParams);
int BE_PQ_HW_O18_Set_PccMuxBlend(LX_BE_PQ_PCC_MUX_BLEND_T *pstParams);

int BE_PQ_HW_O18_Set_LuminenceBoost(LX_BE_PQ_LUT_T *pstParams);

int BE_LED_HW_O18_ProcHandler(BE_LED_PROC_ID_T proc_id, struct seq_file* m, void* data);

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/

#endif   /* ----- #ifndef BE_LED_HW_O18_INC  ----- */
/**  @} */
