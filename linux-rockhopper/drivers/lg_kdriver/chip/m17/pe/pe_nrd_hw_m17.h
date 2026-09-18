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

/** @file pe_nrd_hw_m17.h
 *
 *  driver header for picture enhance noise reduction. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.03.15
 *	@see
 */

#ifndef	_PE_NRD_HW_M17_H_
#define	_PE_NRD_HW_M17_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_m17.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
/* apply tnr high gain */
#define PE_NRD_HW_M17_APPLY_TNR_HIGH_GAIN_OFF	(0x0)
#define PE_NRD_HW_M17_APPLY_TNR_HIGH_GAIN__ON	(0x1)
#define PE_NRD_HW_M17_TNR_HIGH_GAIN				(0xc0)
#define PE_NRD_HW_M17_MA_MOTION_ATV_TH			(7)
#define PE_NRD_HW_M17_SAT_STATUS_TH_DEL			(3)
#define PE_NRD_HW_M17_SAT_STATUS_ATV_TH			(197)
#define PE_NRD_HW_M17_SAT_STATUS_ATV_HIGH_TH	(PE_NRD_HW_M17_SAT_STATUS_ATV_TH+PE_NRD_HW_M17_SAT_STATUS_TH_DEL)
#define PE_NRD_HW_M17_SAT_STATUS_ATV_LOW_TH		(PE_NRD_HW_M17_SAT_STATUS_ATV_TH-PE_NRD_HW_M17_SAT_STATUS_TH_DEL)

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define PE_NRD_HW_M17_TNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_M17_TNR_SD_I)?    "PE_NRD_M17_TNR_SD_I":\
		((_x)==PE_NRD_M17_TNR_SD_P)?    "PE_NRD_M17_TNR_SD_P":\
		((_x)==PE_NRD_M17_TNR_HD_I)?    "PE_NRD_M17_TNR_HD_I":\
		((_x)==PE_NRD_M17_TNR_HD_P)?    "PE_NRD_M17_TNR_HD_P":\
		((_x)==PE_NRD_M17_TNR_UD)?      "PE_NRD_M17_TNR_UD":\
		((_x)==PE_NRD_M17_TNR_SECAM)?   "PE_NRD_M17_TNR_SECAM":\
		((_x)==PE_NRD_M17_TNR_ATV)?   	"PE_NRD_M17_TNR_ATV":\
		((_x)==PE_NRD_M17_TNR_HD_FILE)?   	"PE_NRD_M17_TNR_HD_FILE":\
		((_x)==PE_NRD_M17_TNR_VR_360)?   	"PE_NRD_M17_TNR_VR_360":\
		"PE_NRD_M17_TNR_NUM")
	
	/* tnr lut (tnl) */
#define PE_NRD_HW_M17_TNL_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_M17_TNL_HD)?  "PE_NRD_M17_TNL_HD":\
		((_x)==PE_NRD_M17_TNL_SD)?  "PE_NRD_M17_TNL_SD":\
		((_x)==PE_NRD_M17_TNL_UHD)?  "PE_NRD_M17_TNL_UHD":\
		"PE_NRD_M17_TNL_NUM")
	
#define PE_NRD_HW_M17_DNR_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_M17_DNR_SD_I)? 	   "PE_NRD_M17_DNR_SD_I":\
		((_x)==PE_NRD_M17_DNR_SD_P)? 	   "PE_NRD_M17_DNR_SD_P":\
		((_x)==PE_NRD_M17_DNR_HD_I)? 	   "PE_NRD_M17_DNR_HD_I":\
		((_x)==PE_NRD_M17_DNR_HD_P)? 	   "PE_NRD_M17_DNR_HD_P":\
		((_x)==PE_NRD_M17_DNR_UD)? 	   	   "PE_NRD_M17_DRN_UD":\
		((_x)==PE_NRD_M17_DNR_ATV)? 	   "PE_NRD_M17_DRN_ATV":\
		((_x)==PE_NRD_M17_DNR_SD_DTV)? 	   "PE_NRD_M17_DNR_SD_DTV":\
		((_x)==PE_NRD_M17_DNR_HD_DTV)? 	   "PE_NRD_M17_DNR_HD_DTV":\
		((_x)==PE_NRD_M17_DNR_AV)?			"PE_NRD_M17_DNR_AV":\
		((_x)==PE_NRD_M17_DNR_VR_360)? 	   "PE_NRD_M17_DNR_VR_360":\
		"PE_NRD_M17_DNR_NUM")
	
#define PE_NRD_HW_M17_IFC_FMT_TO_STR(_x)		(\
		((_x)==PE_NRD_M17_IFC_ATV_NTSC)?  	"PE_NRD_M17_IFC_ATV_NTSC":\
		((_x)==PE_NRD_M17_IFC_PC)? 	   		"PE_NRD_M17_IFC_PC":\
		((_x)==PE_NRD_M17_IFC_VR_360)? 	   	"PE_NRD_M17_IFC_VR_360":\
		"PE_NRD_M17_IFC_NUM")
	
#define PE_NRD_HW_M17_TBL_IDX_TO_STR(_x)		(\
		((_x)==PE_NRD_HW_M17_TBL_IDX_TNR)? "TNR":\
		((_x)==PE_NRD_HW_M17_TBL_IDX_TNL)? "TNL":\
		((_x)==PE_NRD_HW_M17_TBL_IDX_DNR)? "DNR":\
		((_x)==PE_NRD_HW_M17_TBL_IDX_IFC)? "IFC":\
		"NUM")
/**
 *	pe table index enumeration(for M17X)
 */
typedef enum
{
	PE_NRD_HW_M17_TBL_IDX_TNR = 0,		///< tnr
	PE_NRD_HW_M17_TBL_IDX_TNL,			///< tnr lut (tnl)
	PE_NRD_HW_M17_TBL_IDX_DNR,			///< dnr
	PE_NRD_HW_M17_TBL_IDX_IFC,			///< ifc
	PE_NRD_HW_M17_TBL_IDX_NUM			///< max num
}
PE_NRD_HW_M17_TBL_IDX;

/**
 *	pe read default reg menu enumeration(for M17X)
 */
typedef enum
{
	PE_NRD_HW_M17_RD_MENU_DISP = 0,	///< menu display
	PE_NRD_HW_M17_RD_TNR1_DISP,		///< tnr1 display
	PE_NRD_HW_M17_RD_TNR1_DFLT,		///< tnr1 default
	PE_NRD_HW_M17_RD_TNR1_USER,		///< tnr1 user
	PE_NRD_HW_M17_RD_TNR1_MASK,		///< tnr1 mask
	PE_NRD_HW_M17_RD_TNR1_DATA,		///< tnr1 data
	PE_NRD_HW_M17_RD_DNR1_DISP,		///< dnr1 display
	PE_NRD_HW_M17_RD_DNR1_DFLT,		///< dnr1 default
	PE_NRD_HW_M17_RD_DNR1_USER,		///< dnr1 user
	PE_NRD_HW_M17_RD_DNR1_MASK,		///< dnr1 mask
	PE_NRD_HW_M17_RD_DNR1_DATA,		///< dnr1 data
	PE_NRD_HW_M17_RD_IFC1_DISP,		///< ifc1 display
	PE_NRD_HW_M17_RD_IFC1_DFLT,		///< ifc1 default
	PE_NRD_HW_M17_RD_IFC1_USER,		///< ifc1 user
	PE_NRD_HW_M17_RD_IFC1_MASK,		///< ifc1 mask
	PE_NRD_HW_M17_RD_IFC1_DATA,		///< ifc1 data
	PE_NRD_HW_M17_RD_TNR1_MLUT,		///< tnr1 main lut
	PE_NRD_HW_M17_RD_TNL1_DFLT,		///< tnr lut1 (tnl) default
	PE_NRD_HW_M17_RD_TNL1_USER,		///< tnr lut1 (tnl) user
	PE_NRD_HW_M17_RD_TNL1_MASK,		///< tnr lut1 (tnl) mask
	PE_NRD_HW_M17_RD_TNL1_DATA,		///< tnr lut1 (tnl) data
	PE_NRD_HW_M17_RD_MENU_MAX			///< max num
}
PE_NRD_HW_M17_RD_DFLT_MENU;

/**
 *	pe nrd tnr fmt(for M17X)
 */
typedef enum
{
	PE_NRD_M17_TNR_SD_I = 0,			///< sd i
	PE_NRD_M17_TNR_SD_P,			///< sd p
	PE_NRD_M17_TNR_HD_I,			///< hd i
	PE_NRD_M17_TNR_HD_P,			///< hd p
	PE_NRD_M17_TNR_UD,				///< ud
	PE_NRD_M17_TNR_SECAM,			///< av secam
	PE_NRD_M17_TNR_ATV,				///< atv
	PE_NRD_M17_TNR_HD_FILE,			///< hd file
	PE_NRD_M17_TNR_VR_360,			///< vr 360
	PE_NRD_M17_TNR_NUM				///< max num
}
PE_NRD_HW_M17_TNR_FMT;

/**
 *	pe nrd tnr lut (tnl) fmt(for M17X)
 */
typedef enum
{
	PE_NRD_M17_TNL_HD = 0,			///< hd
	PE_NRD_M17_TNL_SD,				///< sd
	PE_NRD_M17_TNL_UHD,				///< uhd
	PE_NRD_M17_TNL_CAM_HD,			///< dtv camera
	PE_NRD_M17_TNL_NUM				///< max num
}
PE_NRD_HW_M17_TNL_FMT;

/**
 *	pe nrd dnr fmt(for M17X)
 */
typedef enum
{
	PE_NRD_M17_DNR_SD_I,		///< sd
	PE_NRD_M17_DNR_SD_P,		///< sd
	PE_NRD_M17_DNR_HD_I,		///< hd
	PE_NRD_M17_DNR_HD_P,		///< hd
	PE_NRD_M17_DNR_UD,			///< ud
	PE_NRD_M17_DNR_ATV,			///< atv
	PE_NRD_M17_DNR_SD_DTV,		///< dtv sd
	PE_NRD_M17_DNR_HD_DTV,		///< dtv hd
	PE_NRD_M17_DNR_AV,			///< av
	PE_NRD_M17_DNR_VR_360,		///< vr 360
	PE_NRD_M17_DNR_NUM			///< max num
}
PE_NRD_HW_M17_DNR_FMT;

/**
 *	pe nrd ifc fmt(for M17X)
 */
typedef enum
{
	PE_NRD_M17_IFC_ATV_NTSC = 0,	///< atv ntsc
	PE_NRD_M17_IFC_PC,				///< pc(off)
	PE_NRD_M17_IFC_VR_360,				///< pc(off)
	PE_NRD_M17_IFC_NUM				///< max num
}
PE_NRD_HW_M17_IFC_FMT;


/**
 *	pe nrd module settings type
 */
typedef struct
{
	LX_PE_NRD_TNR7_CMN_T tnr_cmn;				///< tnr common
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
	PE_NRD_HW_M17_TNR_FMT tnr0a_fmt;			///< previous tnr fmt
	PE_NRD_HW_M17_TNL_FMT tnl0a_fmt;			///< previous tnr lut (tnl) fmt
	PE_NRD_HW_M17_DNR_FMT dnr0a_fmt;			///< previous dnr fmt
	PE_NRD_HW_M17_IFC_FMT ifc0a_fmt;			///< previous ifc fmt
}
PE_NRD_HW_M17_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_NRD_HW_M17_Init(PE_CFG_CTRL_T *pstParams);
int PE_NRD_HW_M17_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_NRD_HW_M17_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_NRD_HW_M17_RdDefault(LX_PE_ETC_TBL_T *pstParams);
int PE_NRD_HW_M17_SetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_M17_GetDnrCmnCtrl(void *pstParams);
int PE_NRD_HW_M17_SetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_M17_GetDnrDetailCtrl(void *pstParams);
int PE_NRD_HW_M17_SetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_M17_GetTnrCmnCtrl(void *pstParams);
int PE_NRD_HW_M17_SetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_M17_GetTnrDetailCtrl(void *pstParams);
int PE_NRD_HW_M17_SetTnrMode(PE_TSK_M17_CFG_T *pCfg);
int PE_NRD_HW_M17_SetDnrMode(PE_TSK_M17_CFG_T *pCfg);
int PE_NRD_HW_M17_SetIfcMode(PE_TSK_M17_CFG_T *pCfg);
int PE_NRD_HW_M17_DownloadTnrDb(void);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_NRD_HW_M17_H_ */
