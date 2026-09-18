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

/** @file pe_hdr_hw_m19.h
 *
 *  driver header for picture enhance dynamic contrast module functions. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2011.06.11
 *	@see		
 */

#ifndef	_PE_HDR_HW_M19_H_
#define	_PE_HDR_HW_M19_H_

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
#define PE_HDR_HW_M19_TM_LUT_STEP	16
#define PE_HDR_HW_M19_TM_LUT_MAX	33
#define PE_HDR_HW_M19_YG_LUT_MAX	33
#define PE_HDR_HW_M19_HST_BIN_NUM	32

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe read hdr csc info menu enumeration
 */
typedef enum
{
	PE_HDR_HW_M19_CSC_DISPLAY = 0,		///< menu display
	PE_HDR_HW_M19_CSC_RD_INF0,			///< get info0
	PE_HDR_HW_M19_CSC_RD_INF1,			///< get info1
	PE_HDR_HW_M19_CSC_RD_INF2,			///< get info2
	PE_HDR_HW_M19_CSC_RD_INF3,			///< get info3
	PE_HDR_HW_M19_CSC_MAX				///< max num
}
PE_HDR_HW_M19_CSC_MENU;

/**
 *	pe hdr csc type enumeration
 */
typedef enum
{
	PE_HDR_HW_M19_CSC_SDR_Y601 = 0,		///< SDR_Y601
	PE_HDR_HW_M19_CSC_SDR_Y709,			///< SDR_Y709
	PE_HDR_HW_M19_CSC_SDR_2020,			///< SDR_2020
	PE_HDR_HW_M19_CSC_HDR_Y601,			///< HDR_Y601
	PE_HDR_HW_M19_CSC_HDR_Y709,			///< HDR_Y709
	PE_HDR_HW_M19_CSC_HDR_2020,			///< HDR_2020
	PE_HDR_HW_M19_CSC_S2H_Y601,			///< S2H_Y601
	PE_HDR_HW_M19_CSC_S2H_Y709,			///< S2H_Y709
	PE_HDR_HW_M19_CSC_S2H_2020,			///< S2H_2020
	PE_HDR_HW_M19_CSC_NUM				///< max num
}
PE_HDR_HW_M19_CSC_TYPE;

/**
 *	pe hdr module settings type
 */
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
	LX_PE_HDR_CSC_T pre_csc[2];					///< pre csc
	UINT32 pre_hdr_type[2];						///< pre hdr type
	UINT32 cur_hdr_type[2];						///< cur hdr type
	UINT32 db_base[50];							///< db base, see PE_HDR_DDR_M19_ITEM
	UINT32 db_size[50];							///< db size, see PE_HDR_DDR_M19_ITEM
	UINT32 alloc_size;							///< alloc_size
	LX_PE_HDR_MODE_INFO_T md_inf[LX_PE_WIN_NUM];///< mode info
	UINT32 yg_lut_en[2];						///< yg lut enable
	UINT32 yg_lut[2][PE_HDR_HW_M19_YG_LUT_MAX];	///< yg lut
	UINT32 yg_orgsel[2];						///< yg_orgsel
	UINT32 gamma045_enable[2];					///< gamma045_enable
	UINT32 dither_en[2];						///< dither_en
	UINT32 reg_hue_prsv_en[2];					///< reg_hue_prsv_en
	UINT32 reg_sat_prsv_en[2];					///< reg_sat_prsv_en
	UINT32 reg_hue_prsv_ratio[2];				///< reg_hue_prsv_ratio
	UINT32 reg_sat_prsv_ratio[2];				///< reg_sat_prsv_ratio
	UINT32 reg_out_sgain_sel[2];				///< reg_out_sgain_sel
	UINT32 reg_out_lgain_sel[2];				///< reg_out_lgain_sel
	UINT32 reg_inp_s_sel[2];					///< reg_inp_s_sel
	UINT32 reg_inp_l_sel[2];					///< reg_inp_l_sel
	UINT32 lgain_lut[2][8];						///< lgain_lut
	UINT32 sgain_lut[2][8];						///< sgain_lut
}
PE_HDR_HW_M19_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_HDR_HW_M19_GetTraceDataBuf(LX_PE_ETC_TBL_T *pstParams);
int PE_HDR_HW_M19_Init(PE_CFG_CTRL_T *pstParams);
int PE_HDR_HW_M19_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_HDR_HW_M19_SetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_HW_M19_GetTonemapLut(LX_PE_HDR_TONEMAP_LUT_T *pstParams);
int PE_HDR_HW_M19_SetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_HW_M19_GetYgainLut(LX_PE_HDR_YGAIN_LUT_T *pstParams);
int PE_HDR_HW_M19_SetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_HW_M19_GetCsc(LX_PE_HDR_CSC_T *pstParams);
int PE_HDR_HW_M19_GetInfo(LX_PE_HDR_INFO_T *pstParams);
int PE_HDR_HW_M19_GetCscInfo(LX_PE_ETC_TBL_T *pstParams);
int PE_HDR_HW_M19_GetHistoInfo(LX_PE_HDR_HISTO_INFO_T *pstParams);
int PE_HDR_HW_M19_SetCscMode(PE_TSK_M19_CFG_T *pCfg);
int PE_HDR_HW_M19_SetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_HW_M19_GetEotfLut(LX_PE_HDR_EOTF_LUT_T *pstParams);
int PE_HDR_HW_M19_SetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_HW_M19_GetOetfLut(LX_PE_HDR_OETF_LUT_T *pstParams);
int PE_HDR_HW_M19_Set3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_HW_M19_Get3dLutInfo(LX_PE_HDR_3D_LUT_INFO_T *pstParams);
int PE_HDR_HW_M19_SetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_HW_M19_GetModeInfo(LX_PE_HDR_MODE_INFO_T *pstParams);
int PE_HDR_HW_M19_SetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_HW_M19_GetGammaEn(LX_PE_HDR_GAMMA_EN_T *pstParams);
int PE_HDR_HW_M19_SetColorCorrect(LX_PE_HDR_CCR_T *pstParams);
int PE_HDR_HW_M19_GetColorCorrect(LX_PE_HDR_CCR_T *pstParams);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_HDR_HW_M19_H_ */
