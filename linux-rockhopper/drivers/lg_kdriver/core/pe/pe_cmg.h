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

/** @file pe_cmg.h
 *
 *  driver header for picture enhance color management. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_CMG_H_
#define	_PE_CMG_H_

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

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_CMG_RegisterCbFunc(void);
int PE_CMG_Init(PE_CFG_CTRL_T *pstParams);
int PE_CMG_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);
int PE_CMG_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize);

int PE_CMG_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_CMG_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_CMG_SetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_GetCenEnable(LX_PE_CMG_ENABLE_T *pstParams);
int PE_CMG_SetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_GetCenRegionEnable(LX_PE_CMG_REGION_ENABLE_T *pstParams);
int PE_CMG_SetCenRegion2(void *pstParams);
int PE_CMG_SetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_GetCenRegion(LX_PE_CMG_REGION_T *pstParams);
int PE_CMG_SetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_GetCenRegionCtrl(LX_PE_CMG_REGION_CTRL_T *pstParams);
int PE_CMG_SetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
int PE_CMG_GetCenGlobalCtrl(LX_PE_CMG_GLOBAL_CTRL_T *pstParams);
int PE_CMG_SetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_GetCenColorCtrl(LX_PE_CMG_COLOR_CTRL_T *pstParams);
int PE_CMG_SetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_GetClearWhiteCtrl(LX_PE_CMG_CW_CTRL_T *pstParams);
int PE_CMG_SetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_GetClearWhiteGainCtrl(LX_PE_CMG_CW_GAIN_CTRL_T *pstParams);
int PE_CMG_SetSaturationGainLUT(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams);
int PE_CMG_GetSaturationGainLUT(LX_PE_CMG_SAT_GAIN_LUT_T *pstParams);
int PE_CMG_SetExtInnerPattern(LX_PE_CMG_EXT_PATTERN_INFO_T *pstParams);
int PE_CMG_SetClearWhiteTableCtrl(LX_PE_CMG_CW_TABLE_CTRL_T *pstParams);
int PE_CMG_SetVspccCtrl(LX_PE_CMG_VSPCC_CTRL_T *pstParams);
int PE_CMG_SetVspccCtrl2(void *pstParams);
int PE_CMG_SetDseCtrl(void *pstParams);
int PE_CMG_GetDseCtrl(void *pstParams);
int PE_CMG_SetCenRegionAll(LX_PE_CMG_REGION_ALL_T *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_CMG_H_ */
