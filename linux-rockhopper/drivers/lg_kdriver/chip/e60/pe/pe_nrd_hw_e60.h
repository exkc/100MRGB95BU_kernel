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

/** @file pe_nrd_hw_e60.h
 *
 *  driver header for picture enhance noise reduction. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.03.15
 *	@see
 */

#ifndef	_PE_NRD_HW_E60_H_
#define	_PE_NRD_HW_E60_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_e60.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* apply tnr high gain */
#define PE_NRD_HW_E60_APPLY_TNR_HIGH_GAIN_OFF	(0x0)
#define PE_NRD_HW_E60_APPLY_TNR_HIGH_GAIN__ON	(0x1)
#define PE_NRD_HW_E60_TNR_HIGH_GAIN				(0xc0)
#define PE_NRD_HW_E60_MA_MOTION_ATV_TH			(7)
#define PE_NRD_HW_E60_SAT_STATUS_TH_DEL			(3)
#define PE_NRD_HW_E60_SAT_STATUS_ATV_TH			(197)
#define PE_NRD_HW_E60_SAT_STATUS_ATV_HIGH_TH	(PE_NRD_HW_E60_SAT_STATUS_ATV_TH+PE_NRD_HW_E60_SAT_STATUS_TH_DEL)
#define PE_NRD_HW_E60_SAT_STATUS_ATV_LOW_TH		(PE_NRD_HW_E60_SAT_STATUS_ATV_TH-PE_NRD_HW_E60_SAT_STATUS_TH_DEL)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_E60_TNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_TNR_SD)?    	"PE_NRD_E60_TNR_SD":\
		((_x)==PE_NRD_E60_TNR_HD_I)?    "PE_NRD_E60_TNR_HD_I":\
		((_x)==PE_NRD_E60_TNR_HD_P)?    "PE_NRD_E60_TNR_HD_P":\
		((_x)==PE_NRD_E60_TNR_UD)?      "PE_NRD_E60_TNR_UD":\
		((_x)==PE_NRD_E60_TNR_8K)?      "PE_NRD_E60_TNR_8K":\
		"PE_NRD_E60_TNR_NUM")

#define PE_NRD_HW_E60_TNR2ND_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_TNR2ND_SD)?	  	"PE_NRD_E60_TNR2ND_SD":\
		((_x)==PE_NRD_E60_TNR2ND_HD_I)?		"PE_NRD_E60_TNR2ND_HD_I":\
		((_x)==PE_NRD_E60_TNR2ND_HD_P)?		"PE_NRD_E60_TNR2ND_HD_P":\
		((_x)==PE_NRD_E60_TNR2ND_UD)?		"PE_NRD_E60_TNR2ND_UD":\
		"PE_NRD_E60_TNR2ND_NUM")

	/* tnr lut (tnl) */
#define PE_NRD_HW_E60_TNL_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_TNL_HD)?  "PE_NRD_E60_TNL_HD":\
		((_x)==PE_NRD_E60_TNL_SD)?  "PE_NRD_E60_TNL_SD":\
		((_x)==PE_NRD_E60_TNL_UHD)?  "PE_NRD_E60_TNL_UHD":\
		"PE_NRD_E60_TNL_NUM")
	
#define PE_NRD_HW_E60_DNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_DNR_SD)? 	   "PE_NRD_E60_DNR_SD":\
		((_x)==PE_NRD_E60_DNR_HD_I)? 	   "PE_NRD_E60_DNR_HD_I":\
		((_x)==PE_NRD_E60_DNR_HD_P)? 	   "PE_NRD_E60_DNR_HD_P":\
		((_x)==PE_NRD_E60_DNR_UD)? 	   	   "PE_NRD_E60_DRN_UD":\
		((_x)==PE_NRD_E60_DNR_SD_DTV)? 	   "PE_NRD_E60_DNR_SD_DTV":\
		((_x)==PE_NRD_E60_DNR_8K)? 	   	   "PE_NRD_E60_DRN_8K":\
		"PE_NRD_E60_DNR_NUM")

#define PE_NRD_HW_E60_PSP_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_PSP_SD)? 	   "PE_NRD_E60_PSP_SD":\
		((_x)==PE_NRD_E60_PSP_HD)? 	   "PE_NRD_E60_PSP_HD":\
		((_x)==PE_NRD_E60_PSP_UD)? 	   "PE_NRD_E60_PSP_UD":\
		"PE_NRD_E60_DNR_NUM")

	
#define PE_NRD_HW_E60_IFC_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_IFC_ATV_NTSC)?  	"PE_NRD_E60_IFC_ATV_NTSC":\
		((_x)==PE_NRD_E60_IFC_PC)? 	   		"PE_NRD_E60_IFC_PC":\
		((_x)==PE_NRD_E60_IFC_VR_360)? 	   	"PE_NRD_E60_IFC_VR_360":\
		"PE_NRD_E60_IFC_NUM")
	
#define PE_NRD_HW_E60_TBL_IDX_TO_STR(_x)		(\
		((_x)==PE_NRD_HW_E60_TBL_IDX_TNR)? "TNR":\
		((_x)==PE_NRD_HW_E60_TBL_IDX_TNL)? "TNL":\
		((_x)==PE_NRD_HW_E60_TBL_IDX_DNR)? "DNR":\
		((_x)==PE_NRD_HW_E60_TBL_IDX_PSP)? "PSP":\
		((_x)==PE_NRD_HW_E60_TBL_IDX_IFC)? "IFC":\
		((_x)==PE_NRD_HW_E60_TBL_IDX_LED)? "LED":\
		"NUM")

#define PE_NRD_HW_E60_LED_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_E60_LED_SD)?		   "PE_NRD_E60_LED_SD":\
		((_x)==PE_NRD_E60_LED_HD)?		   "PE_NRD_E60_LED_HD":\
		((_x)==PE_NRD_E60_LED_UD)?		   "PE_NRD_E60_LED_UD":\
		((_x)==PE_NRD_E60_LED_8K)?		   "PE_NRD_E60_LED_8K":\
		"PE_NRD_E60_LED_NUM")

/**
 *	pe table index enumeration(for E60X)
 */
typedef enum
{
	PE_NRD_HW_E60_TBL_IDX_TNR = 0,		///< tnr
	PE_NRD_HW_E60_TBL_IDX_TNL,			///< tnr lut (tnl)
	PE_NRD_HW_E60_TBL_IDX_DNR,			///< dnr
	PE_NRD_HW_E60_TBL_IDX_PSP,			///< dnr psp
	PE_NRD_HW_E60_TBL_IDX_IFC,			///< ifc
	PE_NRD_HW_E60_TBL_IDX_LED,			///< led dnr
	PE_NRD_HW_E60_TBL_IDX_NUM			///< max num
}
PE_NRD_HW_E60_TBL_IDX;

/**
 *	pe read default reg menu enumeration(for E60X)
 */
typedef enum
{
	PE_NRD_HW_E60_RD_MENU_DISP = 0,	///< menu display
	PE_NRD_HW_E60_RD_TNR1_DISP,		///< tnr1 display
	PE_NRD_HW_E60_RD_TNR1_DFLT,		///< tnr1 default
	PE_NRD_HW_E60_RD_TNR1_USER,		///< tnr1 user
	PE_NRD_HW_E60_RD_TNR1_MASK,		///< tnr1 mask
	PE_NRD_HW_E60_RD_TNR1_DATA,		///< tnr1 data
	PE_NRD_HW_E60_RD_TNR2_DISP,		///< tnr2 display
	PE_NRD_HW_E60_RD_TNR2_DFLT,		///< tnr2 default
	PE_NRD_HW_E60_RD_TNR2_USER,		///< tnr2 user
	PE_NRD_HW_E60_RD_TNR2_MASK,		///< tnr2 mask
	PE_NRD_HW_E60_RD_TNR2_DATA,		///< tnr2 data
	PE_NRD_HW_E60_RD_DNR1_DISP,		///< dnr1 display
	PE_NRD_HW_E60_RD_DNR1_DFLT,		///< dnr1 default
	PE_NRD_HW_E60_RD_DNR1_USER,		///< dnr1 user
	PE_NRD_HW_E60_RD_DNR1_MASK,		///< dnr1 mask
	PE_NRD_HW_E60_RD_DNR1_DATA,		///< dnr1 data
	PE_NRD_HW_E60_RD_PSP1_DISP,		///< psp display
	PE_NRD_HW_E60_RD_PSP1_DFLT,		///< psp default
	PE_NRD_HW_E60_RD_PSP1_USER,		///< psp user
	PE_NRD_HW_E60_RD_PSP1_MASK,		///< psp mask
	PE_NRD_HW_E60_RD_PSP1_DATA,		///< psp data
	//PE_NRD_HW_E60_RD_IFC1_DISP,		///< ifc1 display
	//PE_NRD_HW_E60_RD_IFC1_DFLT,		///< ifc1 default
	//PE_NRD_HW_E60_RD_IFC1_USER,		///< ifc1 user
	//PE_NRD_HW_E60_RD_IFC1_MASK,		///< ifc1 mask
	//PE_NRD_HW_E60_RD_IFC1_DATA,		///< ifc1 data
	PE_NRD_HW_E60_RD_LED1_DISP,		///< led1 display
	PE_NRD_HW_E60_RD_LED1_DFLT,		///< led1 default
	PE_NRD_HW_E60_RD_LED1_USER,		///< led1 user
	PE_NRD_HW_E60_RD_LED1_MASK,		///< led1 mask
	PE_NRD_HW_E60_RD_LED1_DATA,		///< led1 data
	PE_NRD_HW_E60_RD_TNR1_MLUT,		///< tnr1 main lut
	PE_NRD_HW_E60_RD_TNL1_DFLT,		///< tnr lut1 (tnl) default
	PE_NRD_HW_E60_RD_TNL1_USER,		///< tnr lut1 (tnl) user
	PE_NRD_HW_E60_RD_TNL1_MASK,		///< tnr lut1 (tnl) mask
	PE_NRD_HW_E60_RD_TNL1_DATA,		///< tnr lut1 (tnl) data
	PE_NRD_HW_E60_RD_MENU_MAX			///< max num
}
PE_NRD_HW_E60_RD_DFLT_MENU;

/**
 *	pe nrd tnr fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_TNR_SD = 0,			///< sd i
	PE_NRD_E60_TNR_HD_I,			///< hd i
	PE_NRD_E60_TNR_HD_P,			///< hd p
	PE_NRD_E60_TNR_UD,				///< ud
	PE_NRD_E60_TNR_8K,				///< 8k
	PE_NRD_E60_TNR_NUM				///< max num
}
PE_NRD_HW_E60_TNR_FMT;

/**
 *	pe nrd tnr fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_TNR2ND_SD = 0,			///< sd i
	PE_NRD_E60_TNR2ND_HD_I,			///< hd i
	PE_NRD_E60_TNR2ND_HD_P,			///< hd p
	PE_NRD_E60_TNR2ND_UD,				///< ud
	PE_NRD_E60_TNR2ND_NUM				///< max num
}
PE_NRD_HW_E60_TNR2ND_FMT;


/**
 *	pe nrd tnr lut (tnl) fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_TNL_HD = 0,			///< hd
	PE_NRD_E60_TNL_SD,				///< sd
	PE_NRD_E60_TNL_UHD,				///< uhd
	PE_NRD_E60_TNL_CAM_HD,			///< dtv camera
	PE_NRD_E60_TNL_NUM				///< max num
}
PE_NRD_HW_E60_TNL_FMT;

/**
 *	pe nrd dnr fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_DNR_SD,		///< sd
	PE_NRD_E60_DNR_HD_I,		///< hd
	PE_NRD_E60_DNR_HD_P,		///< hd
	PE_NRD_E60_DNR_UD,			///< ud
	PE_NRD_E60_DNR_SD_DTV,		///< sd dtv
	PE_NRD_E60_DNR_8K,			///< 8k
	PE_NRD_E60_DNR_NUM			///< max num
}
PE_NRD_HW_E60_DNR_FMT;

/**
 *	pe nrd psp fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_PSP_SD,		///< sd
	PE_NRD_E60_PSP_HD,		///< hd
	PE_NRD_E60_PSP_UD,			///< ud
	PE_NRD_E60_PSP_NUM			///< max num
}
PE_NRD_HW_E60_PSP_FMT;

/**
 *	pe nrd ifc fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_IFC_ATV_NTSC = 0,	///< atv ntsc
	PE_NRD_E60_IFC_PC,				///< pc(off)
	PE_NRD_E60_IFC_VR_360,				///< pc(off)
	PE_NRD_E60_IFC_NUM				///< max num
}
PE_NRD_HW_E60_IFC_FMT;

/**
 *	pe nrd dnr fmt(for E60X)
 */
typedef enum
{
	PE_NRD_E60_LED_SD,		///< ud
	PE_NRD_E60_LED_HD,		///< ud
	PE_NRD_E60_LED_UD,		///< ud
	PE_NRD_E60_LED_8K,		///< 8k
	PE_NRD_E60_LED_NUM		///< max num
}
PE_NRD_HW_E60_LED_FMT;

/**
 *	pe nrd module settings type
 */
typedef struct
{
	LX_PE_NRD_TNR1_CMN_T tnr0_cmn;				///< tnr common
	LX_PE_NRD_TNR1_CMN_T tnr1_cmn;				///< tnr common
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
	PE_NRD_HW_E60_TNR_FMT tnr0a_fmt;			///< previous tnr fmt
	PE_NRD_HW_E60_TNL_FMT tnl0a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_E60_DNR_FMT dnr0a_fmt;			///< previous dnr fmt
	PE_NRD_HW_E60_PSP_FMT psp0a_fmt;			///< previous dnr fmt
	PE_NRD_HW_E60_TNR2ND_FMT tnr1a_fmt;			///< previous tnr fmt
	PE_NRD_HW_E60_TNL_FMT tnl1a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_E60_LED_FMT led0a_fmt;			///< previous led fmt
	UINT32 is_external_chip;		            ///< 60Hz or 120Hz model, 0:60Hz, 1:120Hz
}
PE_NRD_HW_E60_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_NRD_HW_E60_Init(PE_CFG_CTRL_T *pstParams);
int PE_NRD_HW_E60_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_NRD_HW_E60_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_NRD_HW_E60_RdDefault(LX_PE_ETC_TBL_T *pstParams);
int PE_NRD_HW_E60_SetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_GetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_GetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_SetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_GetDnrDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_GetDnrDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_SetLedDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_GetLedDcntCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetLedDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_GetLedDcntDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_GetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_GetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_GetTnr2ndCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_GetTnr2ndDetailCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnrSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnr2ndSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetDnrSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetDnrDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetLedDcntSqmCmnCtrl(void *pstParams);
int PE_NRD_HW_E60_SetTnrMode(PE_TSK_E60_CFG_T *pCfg);
//int PE_NRD_HW_E60_SetDnrMode(PE_TSK_E60_CFG_T *pCfg);
//int PE_NRD_HW_E60_SetIfcMode(PE_TSK_E60_CFG_T *pCfg);
int PE_NRD_HW_E60_DownloadTnrDb(void);
int PE_NRD_HW_E60_DownloadTnr2ndDb(void);
int PE_NRD_HW_E60_DownloadDnrInitDb(void);
int PE_NRD_HW_E60_DownloadDnrDcntInitDb(void);
int PE_NRD_HW_E60_DownloadLedDcntInitDb(void);
int PE_NRD_HW_E60_DownloadTnrSqmCmnInitDb(void);
int PE_NRD_HW_E60_DownloadTnr2ndSqmCmnInitDb(void);
int PE_NRD_HW_E60_DownloadDnrSqmCmnInitDb(void);
int PE_NRD_HW_E60_DownloadDnrDcntSqmCmnInitDb(void);
int PE_NRD_HW_E60_DownloadLedDcntSqmCmnInitDb(void);
int PE_NRD_HW_E60_GetTnrUserDb(void *pstParams);
int PE_NRD_HW_E60_GetTnr2ndUserDb(void *pstParams);
int PE_NRD_HW_E60_GetDnrUserDb(void *pstParams);
int PE_NRD_HW_E60_GetDnrDcntUserDb(void *pstParams);
int PE_NRD_HW_E60_GetLedDcntUserDb(void *pstParams);
int PE_NRD_HW_E60_GetTnrSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_E60_GetTnr2ndSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_E60_GetDnrSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_E60_GetDnrDcntSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_E60_GetLedDcntSqmCmnUserDb(void *pstParams);
int PE_NRD_HW_E60F20_DownloadTnrDb(void);
#if 1
int PE_NRD_HW_E60F20_DownloadTnrSqmCmnInitDb(void);
int PE_NRD_HW_E60F20_DownloadDnrInitDb(void);
int PE_NRD_HW_E60F20_DownloadDnrSqmCmnInitDb(void);
int PE_NRD_HW_E60F20_DownloadDnrDcntInitDb(void);
int PE_NRD_HW_E60F20_DownloadLedDcntInitDb(void);
int PE_NRD_HW_E60F20_DownloadDnrDcntSqmCmnInitDb(void);
int PE_NRD_HW_E60F20_DownloadLedDcntSqmCmnInitDb(void);
#endif
int PE_NRD_HW_E60F20_SetTnrCmnAllCtrl(void *pstParams);
int PE_NRD_HW_E60F20_SetDnrCmnAllCtrl(void *pstParams);
int PE_NRD_HW_E60F20_SetDnrDcntCmnAllCtrl(void *pstParams);
/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_E60_H_ */
