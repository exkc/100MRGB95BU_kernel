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

/** @file pe_cmg_hw_o22.h
 *
 *  driver header for picture enhance color management. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2012.04.17
 *	@see		
 */

#ifndef	_PE_CMG_HW_O22_H_
#define	_PE_CMG_HW_O22_H_

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
#define PE_CMG_HW_O22_LUT_MAX				33
#define PE_CMG_HW_O22_LUT_STEP				16
#define PE_CMG_HW_O22_LUT_MAX				33

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct {
	struct delayed_work dlyWork;
	LX_PE_CMG_REGION_T cmg_region_ctrl;
} PE_CMG_HW_O22_DLY_CEN_LUT_T;

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
	PE_CMG_HW_O22_DLY_CEN_LUT_T delayed_cmg_lut[LX_PE_CMG_REGION_NUM];
	UINT32 dynamic_cm_ui;
	UINT32 pre_cen_bypass;
	UINT32 year_option; ///< o22n:23, o22:22, others 0;
}
PE_CMG_HW_O22_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMG_HW_O22_Init(PE_CFG_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMG_HW_O22_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_HW_O22_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_HW_O22_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_HW_O22_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_HW_O22_SetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_O22_GetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_HW_O22_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_O22_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_HW_O22_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_HW_O22_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_HW_O22_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *pstParams);
int PE_CMG_HW_O22_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams);
int PE_CMG_HW_O22_SetDseCtrl(void *pstParams);
int PE_CMG_HW_O22_GetDseCtrl(void *pstParams);
int PE_CMG_HW_O22_SetTargetSat(void);
int PE_CMG_HW_O22_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams);
int PE_CMG_HW_O22_SetCenBypass(void);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMG_HW_O22_H_ */

