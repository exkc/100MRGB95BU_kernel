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

/** @file pe_hdr_hw_e60.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_HDR_HW_E60_H_
#define	_PE_HDR_HW_E60_H_

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
#define PE_HDR_HW_E60_TM_LUT_STEP	16
#define PE_HDR_HW_E60_TM_LUT_MAX	33
#define PE_HDR_HW_E60_YG_LUT_MAX	33
#define PE_HDR_HW_E60_HST_BIN_NUM	128
#define PE_HDR_HW_E60_LL_LUT_MAX	128

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
typedef enum
{
	PE_HDR_HW_E60_INFO_MENU_DISPLAY = 0,	///< menu display
	PE_HDR_HW_E60_INFO_MENU_RD_INF0,		///< get info0
	PE_HDR_HW_E60_INFO_MENU_RD_INF1,		///< get info1
	PE_HDR_HW_E60_INFO_MENU_RD_INF2,		///< get info2
	PE_HDR_HW_E60_INFO_MENU_RD_INF3,		///< get info3
	PE_HDR_HW_E60_INFO_MENU_RD_INF4,		///< get info4
	PE_HDR_HW_E60_INFO_MENU_MAX				///< max num
}
PE_HDR_HW_E60_CSC_MENU;

typedef struct
{
	UINT32 hdr_co0[PE_NUM_OF_CSC_COEF];			///< hdr csc coef 0
	UINT32 hdr_of0[PE_NUM_OF_CSC_OFST];			///< hdr csc ofst 0
	UINT32 hdr_co1[PE_NUM_OF_CSC_COEF];			///< hdr csc coef 1
	UINT32 hdr_of1[PE_NUM_OF_CSC_OFST];			///< hdr csc ofst 1
	UINT32 hdr_co2[PE_NUM_OF_CSC_COEF];			///< hdr csc coef 2
	UINT32 hdr_of2[PE_NUM_OF_CSC_OFST];			///< hdr csc ofst 2
	UINT32 hdr_co3[PE_NUM_OF_CSC_COEF];			///< hdr csc coef 3
	UINT32 hdr_of3[PE_NUM_OF_CSC_OFST];			///< hdr csc ofst 3
	UINT32 hdr_co4[PE_NUM_OF_CSC_COEF];			///< hdr csc coef 4
	UINT32 hdr_of4[PE_NUM_OF_CSC_OFST];			///< hdr csc ofst 4
	LX_PE_HDR_CSC_T pre_csc[2];					///< pre csc
	UINT32 pre_hdr_type[2];						///< pre hdr type
	UINT32 cur_hdr_type[2];						///< cur hdr type
	LX_PE_HDR_MODE_INFO_T md_inf[LX_PE_WIN_NUM];///< mode info
	UINT32 reg_hue_prsv_en;						///< reg_hue_prsv_en
	UINT32 reg_sat_prsv_en;						///< reg_sat_prsv_en
	UINT32 reg_hue_prsv_ratio;					///< reg_hue_prsv_ratio
	UINT32 reg_sat_prsv_ratio;					///< reg_sat_prsv_ratio
	UINT32 lgain_lut[8];						///< lgain_lut
	UINT32 sgain_lut[8];						///< sgain_lut
}
PE_HDR_HW_E60_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_HDR_HW_E60_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams);
int PE_HDR_HW_E60_Init(PE_CFG_CTRL_T *pstParams);
int PE_HDR_HW_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_HDR_HW_E60_SetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_HW_E60_GetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_HW_E60_SetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_HW_E60_GetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_HW_E60_SetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_HW_E60_GetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_HW_E60_GetInfo(LX_PE_HDR_INFO_T *pstParams);
int PE_HDR_HW_E60_GetGeneralInfo(LX_PE_ETC_TBL_T *pstParams);
int PE_HDR_HW_E60_GetCscInfo(LX_PE_ETC_TBL_T *pstParams);
int PE_HDR_HW_E60_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams);
int PE_HDR_HW_E60_SetCscMode(PE_TSK_E60_CFG_T *pCfg);
int PE_HDR_HW_E60_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_HW_E60_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_HW_E60_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_HW_E60_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_HW_E60_Set3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_HW_E60_Get3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_HW_E60_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_HW_E60_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_HW_E60_SetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_HW_E60_GetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_HW_E60_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams);
int PE_HDR_HW_E60_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams);
int PE_HDR_HW_E60_SetPattern(void *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_HDR_HW_E60_H_ */
