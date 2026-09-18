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

/** @file pe_nrd_hw_o26.h
 *
 *  driver header for picture enhance noise reduction. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.03.15
 *	@see
 */

#ifndef	_PE_NRD_HW_O26_H_
#define	_PE_NRD_HW_O26_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_o26.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* apply tnr high gain */
#define PE_NRD_HW_O26_APPLY_TNR_HIGH_GAIN_OFF	(0x0)
#define PE_NRD_HW_O26_APPLY_TNR_HIGH_GAIN__ON	(0x1)
#define PE_NRD_HW_O26_TNR_HIGH_GAIN				(0xc0)
#define PE_NRD_HW_O26_MA_MOTION_ATV_TH			(7)
#define PE_NRD_HW_O26_SAT_STATUS_TH_DEL			(3)
#define PE_NRD_HW_O26_SAT_STATUS_ATV_TH			(197)
#define PE_NRD_HW_O26_SAT_STATUS_ATV_HIGH_TH	(PE_NRD_HW_O26_SAT_STATUS_ATV_TH+PE_NRD_HW_O26_SAT_STATUS_TH_DEL)
#define PE_NRD_HW_O26_SAT_STATUS_ATV_LOW_TH		(PE_NRD_HW_O26_SAT_STATUS_ATV_TH-PE_NRD_HW_O26_SAT_STATUS_TH_DEL)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_O26_TNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_TNR_SD)?    	"PE_NRD_O26_TNR_SD":\
		((_x)==PE_NRD_O26_TNR_HD_I)?    "PE_NRD_O26_TNR_HD_I":\
		((_x)==PE_NRD_O26_TNR_HD_P)?    "PE_NRD_O26_TNR_HD_P":\
		((_x)==PE_NRD_O26_TNR_UD)?      "PE_NRD_O26_TNR_UD":\
		((_x)==PE_NRD_O26_TNR_8K)?      "PE_NRD_O26_TNR_8K":\
		"PE_NRD_O26_TNR_NUM")

#define PE_NRD_HW_O26_TNR2ND_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_TNR2ND_SD)?	  	"PE_NRD_O26_TNR2ND_SD":\
		((_x)==PE_NRD_O26_TNR2ND_HD_I)?		"PE_NRD_O26_TNR2ND_HD_I":\
		((_x)==PE_NRD_O26_TNR2ND_HD_P)?		"PE_NRD_O26_TNR2ND_HD_P":\
		((_x)==PE_NRD_O26_TNR2ND_UD)?		"PE_NRD_O26_TNR2ND_UD":\
		((_x)==PE_NRD_O26_TNR2ND_HFR)?		"PE_NRD_O26_TNR2ND_HFR":\
		"PE_NRD_O26_TNR2ND_NUM")

	/* tnr lut (tnl) */
#define PE_NRD_HW_O26_TNL_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_TNL_HD)?  "PE_NRD_O26_TNL_HD":\
		((_x)==PE_NRD_O26_TNL_SD)?  "PE_NRD_O26_TNL_SD":\
		((_x)==PE_NRD_O26_TNL_UHD)?  "PE_NRD_O26_TNL_UHD":\
		"PE_NRD_O26_TNL_NUM")

	/* tnr lut (tnl) */
#define PE_NRD_HW_O26_TNL2ND_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_TNL2ND_HD)?	"PE_NRD_O26_TNL2ND_HD":\
		((_x)==PE_NRD_O26_TNL2ND_SD)?	"PE_NRD_O26_TNL2ND_SD":\
		((_x)==PE_NRD_O26_TNL2ND_UHD)?  "PE_NRD_O26_TNL2ND_UHD":\
		((_x)==PE_NRD_O26_TNL2ND_HFR)?	"PE_NRD_O26_TNL2ND_HFR":\
		"PE_NRD_O26_TNL_NUM")
	
#define PE_NRD_HW_O26_DNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_DNR_SD)? 	   "PE_NRD_O26_DNR_SD":\
		((_x)==PE_NRD_O26_DNR_HD_I)? 	   "PE_NRD_O26_DNR_HD_I":\
		((_x)==PE_NRD_O26_DNR_HD_P)? 	   "PE_NRD_O26_DNR_HD_P":\
		((_x)==PE_NRD_O26_DNR_UD)? 	   	   "PE_NRD_O26_DRN_UD":\
		((_x)==PE_NRD_O26_DNR_SD_DTV)? 	   "PE_NRD_O26_DNR_SD_DTV":\
		((_x)==PE_NRD_O26_DNR_8K)? 	   	   "PE_NRD_O26_DRN_8K":\
		"PE_NRD_O26_DNR_NUM")

#define PE_NRD_HW_O26_PSP_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_PSP_SD)? 	   "PE_NRD_O26_PSP_SD":\
		((_x)==PE_NRD_O26_PSP_HD)? 	   "PE_NRD_O26_PSP_HD":\
		((_x)==PE_NRD_O26_PSP_UD)? 	   "PE_NRD_O26_PSP_UD":\
		"PE_NRD_O26_DNR_NUM")

	
#define PE_NRD_HW_O26_IFC_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_IFC_ATV_NTSC)?  	"PE_NRD_O26_IFC_ATV_NTSC":\
		((_x)==PE_NRD_O26_IFC_PC)? 	   		"PE_NRD_O26_IFC_PC":\
		((_x)==PE_NRD_O26_IFC_VR_360)? 	   	"PE_NRD_O26_IFC_VR_360":\
		"PE_NRD_O26_IFC_NUM")
	
#define PE_NRD_HW_O26_TBL_IDX_TO_STR(_x)		(\
		((_x)==PE_NRD_HW_O26_TBL_IDX_TNR)? "TNR":\
		((_x)==PE_NRD_HW_O26_TBL_IDX_TNL)? "TNL":\
		((_x)==PE_NRD_HW_O26_TBL_IDX_DNR)? "DNR":\
		((_x)==PE_NRD_HW_O26_TBL_IDX_PSP)? "PSP":\
		((_x)==PE_NRD_HW_O26_TBL_IDX_IFC)? "IFC":\
		((_x)==PE_NRD_HW_O26_TBL_IDX_CCO)? "CCO":\
		"NUM")

#define PE_NRD_HW_O26_CCO_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_O26_CCO_SD)?		   "PE_NRD_O26_CCO_SD":\
		((_x)==PE_NRD_O26_CCO_HD)?		   "PE_NRD_O26_CCO_HD":\
		((_x)==PE_NRD_O26_CCO_UD)?		   "PE_NRD_O26_CCO_UD":\
		((_x)==PE_NRD_O26_CCO_8K)?		   "PE_NRD_O26_CCO_8K":\
		"PE_NRD_O26_CCO_NUM")

/**
 *	pe table index enumeration(for O26X)
 */
typedef enum
{
	PE_NRD_HW_O26_TBL_IDX_TNR = 0,		///< tnr
	PE_NRD_HW_O26_TBL_IDX_TNL,			///< tnr lut (tnl)
	PE_NRD_HW_O26_TBL_IDX_DNR,			///< dnr
	PE_NRD_HW_O26_TBL_IDX_PSP,			///< dnr psp
	PE_NRD_HW_O26_TBL_IDX_IFC,			///< ifc
	PE_NRD_HW_O26_TBL_IDX_CCO,			///< cco dct
	PE_NRD_HW_O26_TBL_IDX_NUM			///< max num
}
PE_NRD_HW_O26_TBL_IDX;

/**
 *	pe read default reg menu enumeration(for O26X)
 */
typedef enum
{
	PE_NRD_HW_O26_RD_MENU_DISP = 0,	///< menu display
	PE_NRD_HW_O26_RD_TNR1_DISP,		///< tnr1 display
	PE_NRD_HW_O26_RD_TNR1_DFLT,		///< tnr1 default
	PE_NRD_HW_O26_RD_TNR1_USER,		///< tnr1 user
	PE_NRD_HW_O26_RD_TNR1_MASK,		///< tnr1 mask
	PE_NRD_HW_O26_RD_TNR1_DATA,		///< tnr1 data
	PE_NRD_HW_O26_RD_TNR2_DISP,		///< tnr2 display
	PE_NRD_HW_O26_RD_TNR2_DFLT,		///< tnr2 default
	PE_NRD_HW_O26_RD_TNR2_USER,		///< tnr2 user
	PE_NRD_HW_O26_RD_TNR2_MASK,		///< tnr2 mask
	PE_NRD_HW_O26_RD_TNR2_DATA,		///< tnr2 data
	PE_NRD_HW_O26_RD_TNR3_DISP,		///< tnr3 display
	PE_NRD_HW_O26_RD_TNR3_DFLT,		///< tnr3 default
	PE_NRD_HW_O26_RD_TNR3_USER,		///< tnr3 user
	PE_NRD_HW_O26_RD_TNR3_MASK,		///< tnr3 mask
	PE_NRD_HW_O26_RD_TNR3_DATA,		///< tnr3 data
	PE_NRD_HW_O26_RD_DNR1_DISP,		///< dnr1 display
	PE_NRD_HW_O26_RD_DNR1_DFLT,		///< dnr1 default
	PE_NRD_HW_O26_RD_DNR1_USER,		///< dnr1 user
	PE_NRD_HW_O26_RD_DNR1_MASK,		///< dnr1 mask
	PE_NRD_HW_O26_RD_DNR1_DATA,		///< dnr1 data
	PE_NRD_HW_O26_RD_DNR2_DISP,		///< dnr2 display
	PE_NRD_HW_O26_RD_DNR2_DFLT,		///< dnr2 default
	PE_NRD_HW_O26_RD_DNR2_USER,		///< dnr2 user
	PE_NRD_HW_O26_RD_DNR2_MASK,		///< dnr2 mask
	PE_NRD_HW_O26_RD_DNR2_DATA,		///< dnr2 data
	PE_NRD_HW_O26_RD_CCO1_DISP,		///< cco1 display
	PE_NRD_HW_O26_RD_CCO1_DFLT,		///< cco1 default
	PE_NRD_HW_O26_RD_CCO1_USER,		///< cco1 user
	PE_NRD_HW_O26_RD_CCO1_MASK,		///< cco1 mask
	PE_NRD_HW_O26_RD_CCO1_DATA,		///< cco1 data
	PE_NRD_HW_O26_RD_TNR1_MLUT,		///< tnr1 main lut
	PE_NRD_HW_O26_RD_TNL1_DFLT,		///< tnr lut1 (tnl) default
	PE_NRD_HW_O26_RD_TNL1_USER,		///< tnr lut1 (tnl) user
	PE_NRD_HW_O26_RD_TNL1_MASK,		///< tnr lut1 (tnl) mask
	PE_NRD_HW_O26_RD_TNL1_DATA,		///< tnr lut1 (tnl) data
	PE_NRD_HW_O26_RD_TNR2_MLUT,		///< tnr2 main lut
	PE_NRD_HW_O26_RD_TNL2_DFLT,		///< tnr lut2 (tnl) default
	PE_NRD_HW_O26_RD_TNL2_USER,		///< tnr lut2 (tnl) user
	PE_NRD_HW_O26_RD_TNL2_MASK,		///< tnr lut2 (tnl) mask
	PE_NRD_HW_O26_RD_TNL2_DATA,		///< tnr lut2 (tnl) data
	PE_NRD_HW_O26_RD_TNR3_MLUT,		///< tnr3 main lut
	PE_NRD_HW_O26_RD_TNL3_DFLT,		///< tnr lut3 (tnl) default
	PE_NRD_HW_O26_RD_TNL3_USER,		///< tnr lut3 (tnl) user
	PE_NRD_HW_O26_RD_TNL3_MASK,		///< tnr lut3 (tnl) mask
	PE_NRD_HW_O26_RD_TNL3_DATA,		///< tnr lut3 (tnl) data
	PE_NRD_HW_O26_RD_MENU_MAX			///< max num
}
PE_NRD_HW_O26_RD_DFLT_MENU;

/**
 *	pe nrd tnr fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_TNR_SD = 0,			///< sd i
	PE_NRD_O26_TNR_HD_I,			///< hd i
	PE_NRD_O26_TNR_HD_P,			///< hd p
	PE_NRD_O26_TNR_UD,				///< ud
	PE_NRD_O26_TNR_8K,				///< 8k
	PE_NRD_O26_TNR_NUM				///< max num
}
PE_NRD_HW_O26_TNR_FMT;

/**
 *	pe nrd tnr2nd fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_TNR2ND_SD = 0,			///< sd i
	PE_NRD_O26_TNR2ND_HD_I,			///< hd i
	PE_NRD_O26_TNR2ND_HD_P,			///< hd p
	PE_NRD_O26_TNR2ND_UD,				///< ud
	PE_NRD_O26_TNR2ND_HFR,				///< ud
	PE_NRD_O26_TNR2ND_NUM				///< max num
}
PE_NRD_HW_O26_TNR2ND_FMT;


/**
 *	pe nrd tnr lut (tnl) fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_TNL_HD = 0,			///< hd
	PE_NRD_O26_TNL_SD,				///< sd
	PE_NRD_O26_TNL_UHD,				///< uhd
	PE_NRD_O26_TNL_CAM_HD,			///< dtv camera
	PE_NRD_O26_TNL_NUM				///< max num
}
PE_NRD_HW_O26_TNL_FMT;

/**
 *	pe nrd tnr2nd lut (tnl) fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_TNL2ND_HD = 0,			///< hd
	PE_NRD_O26_TNL2ND_SD,				///< sd
	PE_NRD_O26_TNL2ND_UHD,				///< uhd
	PE_NRD_O26_TNL2ND_CAM_HD,			///< dtv camera
	PE_NRD_O26_TNL2ND_HFR,			///< hfr
	PE_NRD_O26_TNL2ND_NUM				///< max num
}
PE_NRD_HW_O26_TNL2ND_FMT;


/**
 *	pe nrd dnr fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_DNR_SD,		///< sd
	PE_NRD_O26_DNR_HD_I,		///< hd
	PE_NRD_O26_DNR_HD_P,		///< hd
	PE_NRD_O26_DNR_UD,			///< ud
	PE_NRD_O26_DNR_SD_DTV,		///< sd dtv
	PE_NRD_O26_DNR_8K,			///< 8k
	PE_NRD_O26_DNR_HFR,
	PE_NRD_O26_DNR_NUM			///< max num
}
PE_NRD_HW_O26_DNR_FMT;

/**
 *	pe nrd psp fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_PSP_SD,		///< sd
	PE_NRD_O26_PSP_HD,		///< hd
	PE_NRD_O26_PSP_UD,			///< ud
	PE_NRD_O26_PSP_NUM			///< max num
}
PE_NRD_HW_O26_PSP_FMT;

/**
 *	pe nrd ifc fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_IFC_ATV_NTSC = 0,	///< atv ntsc
	PE_NRD_O26_IFC_PC,				///< pc(off)
	PE_NRD_O26_IFC_VR_360,				///< pc(off)
	PE_NRD_O26_IFC_NUM				///< max num
}
PE_NRD_HW_O26_IFC_FMT;

/**
 *	pe nrd cco dnr fmt(for O26X)
 */
typedef enum
{
	PE_NRD_O26_CCO_SD,		///< ud
	PE_NRD_O26_CCO_HD,		///< ud
	PE_NRD_O26_CCO_UD,		///< ud
	PE_NRD_O26_CCO_8K,		///< 8k
	PE_NRD_O26_CCO_NUM		///< max num
}
PE_NRD_HW_O26_CCO_FMT;

/**
 *	pe nrd module settings type
 */
typedef struct
{
	LX_PE_NRD_TNR1_CMN_T tnr0_cmn;				///< tnr common
	LX_PE_NRD_TNR2ND2_CMN_T tnr1_cmn;			///< tnr common
	LX_PE_NRD_TNR2ND2_CMN_T tnr2_cmn;			///< tnr common
	UINT32 use_manual_sc;						///< use tnr manual sc en
	UINT32 tnr_sc_en_user;						///< tnr_sc_en_user
	UINT32 tnr_sc_en_mask;						///< tnr_sc_en_mask
	UINT32 tnr_pv_smooth_en_user;				///< tnr_pv_smooth_en_user
	UINT32 tnr_pv_smooth_en_mask;				///< tnr_pv_smooth_en_mask
	UINT32 dnr_max_en0_user;					///< reg_dnr_max_enable user
	UINT32 dnr_max_en0_mask;					///< reg_dnr_max_enable mask
	UINT32 bnr_ac_h_en0_user;					///< bnr_ac_h_en0 user
	UINT32 bnr_ac_h_en0_mask;					///< bnr_ac_h_en0 mask
	UINT32 cur_tnr_auto_enable;					///< current tnr auto enable
	UINT32 cur_tnr_master_gain;					///< current tnr_master_gain
	PE_NRD_HW_O26_TNR_FMT tnr0a_fmt;			///< previous tnr fmt
	PE_NRD_HW_O26_TNL_FMT tnl0a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_O26_DNR_FMT dnr0a_fmt;			///< previous dnr fmt
	PE_NRD_HW_O26_TNR2ND_FMT tnr1a_fmt;			///< previous tnr fmt
	PE_NRD_HW_O26_TNL2ND_FMT tnl1a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_O26_DNR_FMT dnr1a_fmt;			///< previous dnr fmt
	PE_NRD_HW_O26_TNR2ND_FMT tnr2a_fmt;			///< previous tnr fmt
	PE_NRD_HW_O26_TNL2ND_FMT tnl2a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_O26_CCO_FMT cco0a_fmt;			///< previous cco fmt
	UINT32 is_external_chip;		            ///< 60Hz or 120Hz model, 0:60Hz, 1:120Hz
	UINT32 pre_forcing_decon_only;		        ///< pre_forcing_decon_only
	UINT32 pre_smr_master_en_yy;
	UINT32 pre_smr_master_en_cc;
}
PE_NRD_HW_O26_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_NRD_HW_O26_Init(PE_CFG_CTRL_T *pstParams);
int PE_NRD_HW_O26_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_NRD_HW_O26_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_NRD_HW_O26_RdDefault(LX_PE_ETC_TBL_T *pstParams);
int PE_NRD_HW_O26_SetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetDnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_GetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcnt2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcnt2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetCCODcntCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetCCODcntCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetCCODcntDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_GetCCODcntDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_GetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_GetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_GetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr3rdCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr3rdDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnrSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnr3rdSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetDnrDcnt2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetCCODcntSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnrMode(PE_TSK_O26_CFG_T *pCfg);
//int PE_NRD_HW_O26_SetDnrMode(PE_TSK_O26_CFG_T *pCfg);
//int PE_NRD_HW_O26_SetIfcMode(PE_TSK_O26_CFG_T *pCfg);
int PE_NRD_HW_O26_DownloadTnrDb(void);
int PE_NRD_HW_O26_DownloadTnr2ndDb(void);
int PE_NRD_HW_O26_DownloadTnr3rdDb(void);
int PE_NRD_HW_O26_DownloadDnrInitDb(void);
int PE_NRD_HW_O26_DownloadDnr2ndInitDb(void);
int PE_NRD_HW_O26_DownloadDnrDcntInitDb(void);
int PE_NRD_HW_O26_DownloadDnrDcnt2ndInitDb(void);
int PE_NRD_HW_O26_DownloadCCODcntInitDb(void);
int PE_NRD_HW_O26_DownloadTnrSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadTnr2ndSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadTnr3rdSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadDnrSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadDnr2ndSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadDnrDcntSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadDnrDcnt2ndSqmCmnInitDb(void);
int PE_NRD_HW_O26_DownloadCCODcntSqmCmnInitDb(void);
int PE_NRD_HW_O26_GetTnrUserDb(void *pstParams);
int PE_NRD_HW_O26_GetTnr2ndUserDb(void *pstParams);
int PE_NRD_HW_O26_GetTnr3rdUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnr2ndUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcntUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcnt2ndUserDb(void *pstParams);
int PE_NRD_HW_O26_GetCCODcntUserDb(void *pstParams);
int PE_NRD_HW_O26_GetTnrSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetTnr2ndSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetTnr3rdSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnr2ndSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcntSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetDnrDcnt2ndSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26_GetCCODcntSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_O26F22_DownloadTnrDb(void);
#if 1
int PE_NRD_HW_O26F22_DownloadTnrSqmCmnInitDb(void);
int PE_NRD_HW_O26F22_DownloadDnrInitDb(void);
int PE_NRD_HW_O26F22_DownloadDnrSqmCmnInitDb(void);
int PE_NRD_HW_O26F22_DownloadDnrDcntInitDb(void);
int PE_NRD_HW_O26F22_DownloadLedDcntInitDb(void);
int PE_NRD_HW_O26F22_DownloadDnrDcntSqmCmnInitDb(void);
int PE_NRD_HW_O26F22_DownloadLedDcntSqmCmnInitDb(void);
#endif
int PE_NRD_HW_O26F22_SetTnrCmnAllCtrl(void *pstParams);
int PE_NRD_HW_O26F22_SetDnrCmnAllCtrl(void *pstParams);
int PE_NRD_HW_O26F22_SetDnrDcntCmnAllCtrl(void *pstParams);
//int PE_NRD_HW_O26_SetDnr2ndCmnCtrl(void *pstParams);
//int PE_NRD_HW_O26_SetDnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_O26_SetTnrFaceCtrl(void *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_O26_H_ */
