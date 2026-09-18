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

/** @file pe_dcm_hw_m23.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DCM_HW_M23_H_
#define	_PE_DCM_HW_M23_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_m23.h"

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
#define PE_DCM_HW_M23_LUT_STEP				16
#define PE_DCM_HW_M23_LUT_MAX				33

#define PE_DCM_HW_M23_SAT_STATUS_TH			220

#define PE_DCM_HW_M23_SAT_STATUS_TH_DEL		3
#define PE_DCM_HW_M23_SAT_STATUS_DTV_TH		192
#define PE_DCM_HW_M23_SAT_STATUS_ATV_TH		185

#define PE_DCM_HW_M23_SAT_STATUS_DTV_HIGH_TH	(PE_DCM_HW_M23_SAT_STATUS_DTV_TH+PE_DCM_HW_M23_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_M23_SAT_STATUS_DTV_LOW_TH		(PE_DCM_HW_M23_SAT_STATUS_DTV_TH-PE_DCM_HW_M23_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_M23_SAT_STATUS_ATV_HIGH_TH	(PE_DCM_HW_M23_SAT_STATUS_ATV_TH+PE_DCM_HW_M23_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_M23_SAT_STATUS_ATV_LOW_TH		(PE_DCM_HW_M23_SAT_STATUS_ATV_TH-PE_DCM_HW_M23_SAT_STATUS_TH_DEL)

#define PE_DCM_HW_M23_BLUR_ORG_VAL			0xf

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe dcm module settings type
 */
typedef struct
{
	UINT32 cur_blur_gain;		///< current blur gain
	UINT32 pre_blur_gain;		///< previous blur gain
	UINT32 pre_dse_lut[(PE_DCM_HW_M23_LUT_MAX-1)];	///<previous dse lut
	UINT32 cur_pic_mode;
	UINT32 is_external_chip;		///< 60Hz or 120Hz model, 0:60Hz, 1:120Hz
}
PE_DCM_HW_M23_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_DCM_HW_M23_Init(PE_CFG_CTRL_T *pstParams);
int PE_DCM_HW_M23_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_DCM_HW_M23_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_M23_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_M23_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_HW_M23_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_HW_M23_DownloadDrcDb(void);
int PE_DCM_HW_M23_SetDseCtrl(void *pstParams);
int PE_DCM_HW_M23_GetDseCtrl(void *pstParams);
int PE_DCM_HW_M23_DownloadDrcCurvDbInit(void);
int PE_DCM_HW_M23_DownloadDrcCurvDb(void *pstParams);
int PE_DCM_HW_M23_SetDrcParam(void *pstParams);
int PE_DCM_HW_M23_SetDrcCurv(void *pstParams);
int PE_DCM_HW_M23_GetDrcParam(void *pstParams);
int PE_DCM_HW_M23_SetDtmLut(void *pstParams);
int PE_DCM_HW_M23_GetDtmLut(void *pstParams);
int PE_DCM_HW_M23_SetAccelDceLut(void);
int PE_DCM_HW_M23_SetDseCtrl2(void *pstParams);
int PE_DCM_HW_M23_GetDseCtrl2(void *pstParams);
int PE_DCM_HW_M23_SetDceLut2(void *pstParams);
int PE_DCM_HW_M23_SetDrcParam2(void *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DCM_HW_M23_H_ */
