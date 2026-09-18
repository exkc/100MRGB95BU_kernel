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

/** @file pe_dcm_hw_o20.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_DCM_HW_O20_H_
#define	_PE_DCM_HW_O20_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_o20.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/* 2060531, sj.youm, use dce lut on sync */
#undef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define PE_DCM_HW_O20_LUT_STEP				16
#define PE_DCM_HW_O20_LUT_MAX				33

#define PE_DCM_HW_O20_SAT_STATUS_TH			220

#define PE_DCM_HW_O20_SAT_STATUS_TH_DEL		3
#define PE_DCM_HW_O20_SAT_STATUS_DTV_TH		192
#define PE_DCM_HW_O20_SAT_STATUS_ATV_TH		185

#define PE_DCM_HW_O20_SAT_STATUS_DTV_HIGH_TH	(PE_DCM_HW_O20_SAT_STATUS_DTV_TH+PE_DCM_HW_O20_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_O20_SAT_STATUS_DTV_LOW_TH		(PE_DCM_HW_O20_SAT_STATUS_DTV_TH-PE_DCM_HW_O20_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_O20_SAT_STATUS_ATV_HIGH_TH	(PE_DCM_HW_O20_SAT_STATUS_ATV_TH+PE_DCM_HW_O20_SAT_STATUS_TH_DEL)
#define PE_DCM_HW_O20_SAT_STATUS_ATV_LOW_TH		(PE_DCM_HW_O20_SAT_STATUS_ATV_TH-PE_DCM_HW_O20_SAT_STATUS_TH_DEL)

#define PE_DCM_HW_O20_BLUR_ORG_VAL			0xf

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
	UINT32 pre_dse_lut[(PE_DCM_HW_O20_LUT_MAX-1)];	///<previous dse lut
	#ifdef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC
	UINT32 dce_lut_off;							///< dce_lut_off
	UINT32 dce_lut_num;							///< dce_lut_num
	UINT32 dce_lut_cnt;							///< dce_lut_cnt
	UINT32 dce_lut0[PE_DCM_HW_O20_LUT_STEP];	///<dce lut0
	UINT32 dce_lut1[PE_DCM_HW_O20_LUT_STEP];	///<dce lut1
	#endif
}
PE_DCM_HW_O20_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_DCM_HW_O20_Init(PE_CFG_CTRL_T *pstParams);
int PE_DCM_HW_O20_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_DCM_HW_O20_SetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_HW_O20_GetDceConfig(LX_PE_DCM_DCE_CONF_T *pstParams);
int PE_DCM_HW_O20_SetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_O20_GetDceLut(LX_PE_DCM_DCE_LUT_T *pstParams);
int PE_DCM_HW_O20_SetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_HW_O20_GetDseLut(LX_PE_DCM_DSE_LUT_T *pstParams);
int PE_DCM_HW_O20_SetDceSmoothCtrl(void *pstParams);
int PE_DCM_HW_O20_GetDceSmoothCtrl(void *pstParams);
int PE_DCM_HW_O20_SetBlurGain(PE_TSK_O20_CFG_T *pCfg);
int PE_DCM_HW_O20_SetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_HW_O20_GetDceBlendingCtrl(LX_PE_DCM_BLENDING_T *pstParams);
int PE_DCM_HW_O20_SetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_HW_O20_GetDceDrcMode(LX_PE_DCM_DRC_MODE_T *pstParams);
int PE_DCM_HW_O20_DownloadDrcDb(void);
int PE_DCM_HW_O20_SetDseCtrl(void *pstParams);
int PE_DCM_HW_O20_GetDseCtrl(void *pstParams);
#ifdef PE_DCM_HW_O20_SET_DCE_LUT_ON_SYNC
int PE_DCM_HW_O20_SetDceLutOnSync(PE_TSK_O20_CFG_T *pCfg);
#endif
int PE_DCM_HW_O20_DownloadDrcCurvDbInit(void);
int PE_DCM_HW_O20_DownloadDrcCurvDb(void *pstParams);
int PE_DCM_HW_O20_SetDrcParam(void *pstParams);
int PE_DCM_HW_O20_SetDrcCurv(void *pstParams);
int PE_DCM_HW_O20_GetDrcParam(void *pstParams);
int PE_DCM_HW_O20_SetObcParam(void *pstParams);
int PE_DCM_HW_O20_GetObcParam(void *pstParams);
int PE_DCM_HW_O20_GetObcData(void *pstParams);
int PE_DCM_HW_O20_SetDtmLut(void *pstParams);
int PE_DCM_HW_O20_GetDtmLut(void *pstParams);
int PE_DCM_HW_F20_DownloadDrcDb(void);
int PE_DCM_HW_F20_DownloadDrcCurvDbInit(void);
int PE_DCM_HW_F20_DownloadDrcCurvDb(void *pstParams);
int PE_DCM_HW_O20_SetAccelDceLut(void);
int PE_DCM_HW_O20_SetDseCtrl2(void *pstParams);
int PE_DCM_HW_O20_GetDseCtrl2(void *pstParams);
int PE_DCM_HW_O20_SetDceLut2(void *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DCM_HW_O20_H_ */
