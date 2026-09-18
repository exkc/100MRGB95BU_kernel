/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file pe_cmg_hw_m23.h
 *
 *  driver header for picture enhance color management. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.17
 *	@see		
 */

#ifndef	_PE_CMG_HW_M23_H_
#define	_PE_CMG_HW_M23_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_CMG_HW_M23_LUT_MAX				33
#define PE_CMG_HW_M23_LUT_STEP				16
#define PE_CMG_HW_M23_LUT_MAX				33

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	struct delayed_work dlyWork;
	LX_PE_CMG_REGION_T cmg_region_ctrl;
} PE_CMG_HW_M23_DLY_CEN_LUT_T;

/**
 *	pe cmg settings type
 */
typedef struct
{
	LX_PE_CMG_REGION_T		rgn_set[LX_PE_CMG_REGION_NUM];	///< region
	LX_PE_CMG_REGION_CTRL_T	rgn_ctrl[LX_PE_CMG_REGION_NUM];	///< region ctrl
	LX_PE_CMG_GLOBAL_CTRL_T	gbl_ctrl;						///< global ctrl
	UINT32 org_target_sat; /// < target saturation
	UINT32 pre_target_sat; /// < pre target saturation
	PE_CMG_HW_M23_DLY_CEN_LUT_T delayed_cmg_lut[LX_PE_CMG_REGION_NUM];
}
PE_CMG_HW_M23_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMG_HW_M23_Init(PE_CFG_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMG_HW_M23_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_HW_M23_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_HW_M23_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_HW_M23_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_HW_M23_SetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_M23_GetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_M23_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_M23_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_HW_M23_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_HW_M23_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_HW_M23_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *pstParams);
int PE_CMG_HW_M23_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams);
int PE_CMG_HW_M23_SetDseCtrl(void *pstParams);
int PE_CMG_HW_M23_GetDseCtrl(void *pstParams);
int PE_CMG_HW_M23_SetTargetSat(void);
int PE_CMG_HW_M23_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMG_HW_M23_H_ */

