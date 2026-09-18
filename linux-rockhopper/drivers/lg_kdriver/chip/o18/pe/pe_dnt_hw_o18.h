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

/** @file pe_dnt_hw_o18.h
 *
 *  driver header for picture enhance deinterlacer. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.04.12
 *	@see
 */

#ifndef	_PE_DNT_HW_O18_H_
#define	_PE_DNT_HW_O18_H_

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#include "pe_kapi.h"
#include "pe_tsk_o18.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_HW_O18_TNR_DBG_OFF	0x0
#define PE_DNT_HW_O18_TNR_DBG__ON	0x1
#define PE_DNT_HW_O18_CLC_OFF		0x0
#define PE_DNT_HW_O18_CLC__ON		0x1
#define PE_DNT_HW_O18_FMD_OFF		0x0
#define PE_DNT_HW_O18_FMD__ON		0x1
#define PE_DNT_HW_O18_TAVA_OFF		0x0
#define PE_DNT_HW_O18_TAVA__ON		0x1
#define PE_DNT_HW_O18_VFY_OFF		0x0
#define PE_DNT_HW_O18_VFY__ON		0x1
/* vfilter enable protection */
#define PE_DNT_HW_O18_VFY_EN_PROTECT_OFF	0x0
#define PE_DNT_HW_O18_VFT_EN_PROTECT__ON	0x1
/* vfilter hmc protect min, max th enable protection(pt) */
#define PE_DNT_HW_O18_VFY_MIN_MAX_PT_OFF	0x0
#define PE_DNT_HW_O18_VFT_MIN_MAX_PT__ON	0x1

/**	20131108, sj.youm,
*	define for set game mode by fw and clc,fmd on,off
*   this is valid for PE_HW_O18A_USE_REG_CTRL defined.
*/
#define PE_DNT_HW_O18A_SET_GAME_MODE_BY_FW

/**	20131220, sj.youm,
*	define for set use tnr mode by fw
*   this is valid for PE_HW_O18A_USE_REG_CTRL defined.
*/
#define PE_DNT_HW_O18A_SET_USE_TNR_M_BY_FW

/**	20140104, sj.youm,
*	define for force vfilter y min,max protection on drv
*	(because th_min,max are not controled by fw at all)
*   this is valid for PE_HW_O18A_USE_REG_CTRL defined.
*/
#define PE_DNT_HW_O18A_FORCE_VFY_MIN_MAX_PT

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
#define PE_DNT_HW_O18_IPC_FMT_TO_STR(_x)		(\
	((_x)==PE_DNT_O18_IPC_HD)? \
	"PE_DNT_O18_IPC_HD":\
	((_x)==PE_DNT_O18_IPC_SD)? \
	"PE_DNT_O18_IPC_SD":\
	((_x)==PE_DNT_O18_IPC_ATV)? \
	"PE_DNT_O18_IPC_ATV":\
	((_x)==PE_DNT_O18_IPC_DTV_SD)? \
	"PE_DNT_O18_IPC_DTV_SD":\
	((_x)==PE_DNT_O18_IPC_DTV_HD)? \
	"PE_DNT_O18_IPC_DTV_HD":\
	((_x)==PE_DNT_O18_IPC_VR_360)? \
	"PE_DNT_O18_IPC_VR_360":\
	((_x)==PE_DNT_O18_IPC_AV)? \
	"PE_DNT_O18_IPC_AV":\
	"PE_DNT_O18_IPC_NUM")

#define PE_DNT_HW_O18_CLC_FMT_TO_STR(_x)		(\
	((_x)==PE_DNT_O18_CLC_SD_50)? \
	"PE_DNT_O18_CLC_SD_50":\
	((_x)==PE_DNT_O18_CLC_SD_60)? \
	"PE_DNT_O18_CLC_SD_60":\
	((_x)==PE_DNT_O18_CLC_HD)? \
	"PE_DNT_O18_CLC_HD":\
	((_x)==PE_DNT_O18_CLC_PC)? \
	"PE_DNT_O18_CLC_PC":\
	((_x)==PE_DNT_O18_CLC_VR_360)? \
	"PE_DNT_O18_CLC_VR_360":\
	"PE_DNT_O18_CLC_NUM")

#define PE_DNT_HW_O18_VFY_FMT_TO_STR(_x)		(\
	((_x)==PE_DNT_O18_VFY_HD_I)? \
	"PE_DNT_O18_VFY_HD_I":\
	((_x)==PE_DNT_O18_VFY_HD_P)? \
	"PE_DNT_O18_VFY_HD_P":\
	((_x)==PE_DNT_O18_VFY_SD)? \
	"PE_DNT_O18_VFY_SD":\
	((_x)==PE_DNT_O18_VFY_3D)? \
	"PE_DNT_O18_VFY_3D":\
	((_x)==PE_DNT_O18_VFY_DTV_SD)? \
	"PE_DNT_O18_VFY_DTV_SD":\
	((_x)==PE_DNT_O18_VFY_UHD)? \
	"PE_DNT_O18_VFY_UHD":\
	((_x)==PE_DNT_O18_VFY_UHD_HDMI_420)? \
	"PE_DNT_O18_VFY_UHD_HDMI_420":\
	((_x)==PE_DNT_O18_VFY_DTV_HD_I)? \
	"PE_DNT_O18_VFY_DTV_HD_I":\
	((_x)==PE_DNT_O18_VFY_VR_360)? \
	"PE_DNT_O18_VFY_VR_360":\
	"PE_DNT_O18_VFY_NUM")

#define PE_DNT_HW_O18_TBL_IDX_TO_STR(_x)		(\
	((_x)==PE_DNT_HW_O18_TBL_IDX_IPC)? "IPC":\
	((_x)==PE_DNT_HW_O18_TBL_IDX_CLC)? "CLC":\
	((_x)==PE_DNT_HW_O18_TBL_IDX_VFY)? "VFY":\
	"NUM")

/**
 *	pe table index enumeration(for O18X)
 */
typedef enum
{
	PE_DNT_HW_O18_TBL_IDX_IPC = 0, 	///< ipc
	PE_DNT_HW_O18_TBL_IDX_CLC, 		///< clc
	PE_DNT_HW_O18_TBL_IDX_VFY, 		///< vfy
	PE_DNT_HW_O18_TBL_IDX_NUM			///< max num
}
PE_DNT_HW_O18_TBL_IDX;

/**
 *	pe read default reg menu enumeration(for O18X)
 */
typedef enum
{
	PE_DNT_HW_O18_RD_MENU_DISP = 0,	///< menu display
	PE_DNT_HW_O18_RD_IPC1_DISP,		///< ipc1 display
	PE_DNT_HW_O18_RD_IPC2_DISP,		///< ipc2 display
	PE_DNT_HW_O18_RD_IPC1_DFLT,		///< ipc1 default
	PE_DNT_HW_O18_RD_IPC1_USER,		///< ipc1 user
	PE_DNT_HW_O18_RD_IPC1_MASK,		///< ipc1 mask
	PE_DNT_HW_O18_RD_IPC1_DATA,		///< ipc1 data
	PE_DNT_HW_O18_RD_CLC1_DISP,		///< clc1 display
	PE_DNT_HW_O18_RD_CLC1_DFLT,		///< clc1 default
	PE_DNT_HW_O18_RD_CLC1_USER,		///< clc1 user
	PE_DNT_HW_O18_RD_CLC1_MASK,		///< clc1 mask
	PE_DNT_HW_O18_RD_CLC1_DATA,		///< clc1 data
	PE_DNT_HW_O18_RD_VFY1_DISP,		///< vfy1 display
	PE_DNT_HW_O18_RD_VFY2_DISP,		///< vfy2 display
	PE_DNT_HW_O18_RD_VFY1_DFLT,		///< vfy1 default
	PE_DNT_HW_O18_RD_VFY1_USER,		///< vfy1 user
	PE_DNT_HW_O18_RD_VFY1_MASK,		///< vfy1 mask
	PE_DNT_HW_O18_RD_VFY1_DATA,		///< vfy1 data
	PE_DNT_HW_O18_RD_MENU_MAX			///< max num
}
PE_DNT_HW_O18_RD_DFLT_MENU;

/**
 *	pe dnt ipc fmt(for O18X)
 */
typedef enum
{
	PE_DNT_O18_IPC_HD, 			///< hd
	PE_DNT_O18_IPC_SD, 			///< sd
	PE_DNT_O18_IPC_ATV,			///< atv
	PE_DNT_O18_IPC_DTV_SD,		///< dtv sd
	PE_DNT_O18_IPC_DTV_HD,		///< dtv hd
	PE_DNT_O18_IPC_VR_360,		///< vr 360
	PE_DNT_O18_IPC_AV,		///< vr 360
	PE_DNT_O18_IPC_NUM 			///< max num
}
PE_DNT_HW_O18_IPC_FMT;
/**
 *	pe dnt clc fmt(for O18X)
 */
typedef enum
{
	PE_DNT_O18_CLC_SD_50 = 0,	///< sd 50hz
	PE_DNT_O18_CLC_SD_60, 		///< sd 60hz
	PE_DNT_O18_CLC_HD, 			///< hd
	PE_DNT_O18_CLC_PC,			///< pc(clc off)
	PE_DNT_O18_CLC_VR_360, 		///< vr 360
	PE_DNT_O18_CLC_NUM 			///< max num
}
PE_DNT_HW_O18_CLC_FMT;
/**
 *	pe dnt v filter y fmt(for O18X)
 */
typedef enum
{
	PE_DNT_O18_VFY_HD_I, 		///< hd
	PE_DNT_O18_VFY_HD_P, 		///< hd
	PE_DNT_O18_VFY_SD, 			///< sd
	PE_DNT_O18_VFY_3D, 			///< 3d
	PE_DNT_O18_VFY_DTV_SD, 		///< dtv_sd
	PE_DNT_O18_VFY_UHD, 		///< uhd
	PE_DNT_O18_VFY_UHD_HDMI_420,///< uhd hdmi
	PE_DNT_O18_VFY_DTV_HD_I, 	///< dtv hd i
	PE_DNT_O18_VFY_VR_360, 		///< vr 360
	PE_DNT_O18_VFY_NUM 			///< max num
}
PE_DNT_HW_O18_VFY_FMT;

/**
 *	pe dnt module settings type
 */
typedef struct
{
	PE_DNT_HW_O18_IPC_FMT ipc0a_fmt;	///< previous nd1 ipc0a fmt for m16a
	PE_DNT_HW_O18_VFY_FMT vfy0a_fmt;	///< previous dnr vfy0a_fmt for m16a
	PE_DNT_HW_O18_CLC_FMT clc0a_fmt;	///< previous nd1 clc0a_fmt for m16a
	UINT32 force_cbcr_enb;				///< force_cbcr_enable
	UINT32 force_y_max_th;				///< force_y_max_th
	UINT32 is_8k;
}
PE_DNT_HW_O18_SETTINGS_T;


/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/
int PE_DNT_HW_O18_Init(PE_CFG_CTRL_T *pstParams);
int PE_DNT_HW_O18_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_DNT_HW_O18_SetDefault(LX_PE_DEFAULT_SETTINGS_T *pstParams);
int PE_DNT_HW_O18_RdDefault(LX_PE_ETC_TBL_T *pstParams);
int PE_DNT_HW_O18_SetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
int PE_DNT_HW_O18_GetFilmMode(LX_PE_DNT_FILMMODE_T *pstParams);
int PE_DNT_HW_O18_SetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
int PE_DNT_HW_O18_GetLowDelayMode(LX_PE_DNT_LD_MODE_T *pstParams);
int PE_DNT_HW_O18_SetClcMode(PE_TSK_O18_CFG_T *pCfg);
int PE_DNT_HW_O18_GetCurDntSettings(PE_DNT_HW_O18_SETTINGS_T *pstParams);
int PE_DNT_HW_O18_SetVfyMode(PE_TSK_O18_CFG_T *pCfg);
int PE_DNT_HW_O18_SetIpcMode(PE_TSK_O18_CFG_T *pCfg);

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNT_HW_O18_H_ */
