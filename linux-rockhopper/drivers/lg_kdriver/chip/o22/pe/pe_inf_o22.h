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

/** @file pe_inf_o22.h
 *
 *  information management for picture enhance. ( used only within kdriver )
 *
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2012.05.02
 *	@see
 */

#ifndef	_PE_INF_O22_H_
#define	_PE_INF_O22_H_

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
#define PE_INF_HW_O22_BACKUP_TRACE(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_INF_O22_SetTraceDataBuf(0,_trace_buf);\
	}

#define PE_INF_HW_O22_BACKUP_TRACE_DB(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_INF_O22_SetTraceDataBuf(1,_trace_buf);\
	}

#define PE_INF_HW_O22_BACKUP_CHPI0(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		PE_PRINT_NOTI(_fmt, ##args);\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_INF_O22_SetTraceDataBuf(2,_trace_buf);\
	}

#define PE_INF_HW_O22_BACKUP_CHPI1(_fmt, args...)	\
	{\
		char _trace_buf[PE_TRACE_STR_SIZE];\
		PE_PRINT_NOTI(_fmt, ##args);\
		snprintf(_trace_buf, PE_TRACE_STR_SIZE, _fmt, ##args);\
		PE_INF_O22_SetTraceDataBuf(3,_trace_buf);\
	}

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
/**
 *	pe read general info menu enumeration
 */
typedef enum
{
	PE_INF_HW_O22_GINFO_DISPLAY = 0,			///< menu display
	PE_INF_HW_O22_GINFO__KDRV_INFO,				///< kdrv info
	PE_INF_HW_O22_GINFO_DDR_H_PHYS,				///< ddr header phys
	PE_INF_HW_O22_GINFO_DDR_H_SHDW,				///< ddr header shdw
	PE_INF_HW_O22_GINFO_LGSR_DDR_H_PHYS,		///< lgsrddr header phys
	PE_INF_HW_O22_GINFO_LGSR_DDR_H_SHDW,		///< lgsrddr header shdw
	PE_INF_HW_O22_GINFO_CHIP_INFO,				///< chip info
	PE_INF_HW_O22_GINFO_O22F22_DDR_H_PHYS,			///< ddr header phys
	PE_INF_HW_O22_GINFO_O22F22_DDR_H_SHDW,			///< ddr header shdw
	PE_INF_HW_O22_GINFO_O22F22_LGSR_DDR_H_PHYS,		///< lgsrddr header phys
	PE_INF_HW_O22_GINFO_O22F22_LGSR_DDR_H_SHDW,		///< lgsrddr header shdw
	PE_INF_HW_O22_GINFO_MAX						///< max num
}
PE_INF_HW_O22_GINFO_MENU;

/**
 *	pe read default reg menu enumeration
 */
typedef enum
{
	PE_INF_HW_O22_M_DISPLAY = 0,			///< menu display
	PE_INF_HW_O22_M_CVA_TPG___TYPE,		///< pattern_type
	PE_INF_HW_O22_M_CVA_TPG__C_S_C,		///< pattern_csc
	PE_INF_HW_O22_M_CVA_TPG_DETAIL,		///< pattern_detail
	PE_INF_HW_O22_M_CVB_TPG___TYPE,		///< pattern_type
	PE_INF_HW_O22_M_CVB_TPG__C_S_C,		///< pattern_csc
	PE_INF_HW_O22_M_CVB_TPG_DETAIL,		///< pattern_detail
	PE_INF_HW_O22_M_CVC_TPG___TYPE,		///< pattern_type
	PE_INF_HW_O22_M_CVC_TPG__C_S_C,		///< pattern_csc
	PE_INF_HW_O22_M_CVC_TPG_DETAIL,		///< pattern_detail
	PE_INF_HW_O22_M_ND1_DETOUR_ENB,		///< detour_enable
	PE_INF_HW_O22_M_DNR_DETOUR_ENB,		///< detour_enable
	PE_INF_HW_O22_M_ND1_TNR_ENABLE,		///< tnr enable
	PE_INF_HW_O22_M_ND1_IPC_Y_MODE,		///< cr_luma_mode
	PE_INF_HW_O22_M_ND1_IPC_C_MODE,		///< cr_chroma_mode
	PE_INF_HW_O22_M_ND1_FMD_ENABLE,		///< film mode enable
	PE_INF_HW_O22_M_ND1_CLC_FLT_EN,		///< clc filter enable
	PE_INF_HW_O22_M_G0Y_BILIN_ENBL,		///< bilinear enable
	PE_INF_HW_O22_M_G1Y_BILIN_ENBL,		///< bilinear enable
	PE_INF_HW_O22_M_G0C_BILIN_ENBL,		///< bilinear enable
	PE_INF_HW_O22_M_G1C_BILIN_ENBL,		///< bilinear enable
	PE_INF_HW_O22_M_SRE_SHP_BYPASS,		///< detour_enable
	PE_INF_HW_O22_M_SRE_GSC_BILINE,		///< bilinear enable
	PE_INF_HW_O22_M_SHP_____BYPASS,			///< detour_enable
	PE_INF_HW_O22_M_CE_MASTER_ENBL,		///< detour_enable
	PE_INF_HW_O22_M_CE_MUTE_L_ENBL,		///< mute L pxl_rep0_in
	PE_INF_HW_O22_M_CE_MUTE_L_COLR,		///< mute L pxl_rep0_value
	PE_INF_HW_O22_M_CE_MUTE_R_ENBL,		///< mute R pxl_rep1_in
	PE_INF_HW_O22_M_CE_MUTE_R_COLR,		///< mute R pxl_rep1_value
	PE_INF_HW_O22_M_CO_MASTER_ENBL,		///< detour_enable
	PE_INF_HW_O22_M_CO_MUTE_L_ENBL,		///< mute L pxl_rep0_in
	PE_INF_HW_O22_M_CO_MUTE_L_COLR,		///< mute L pxl_rep0_value
	PE_INF_HW_O22_M_CO_MUTE_R_ENBL,		///< mute R pxl_rep1_in
	PE_INF_HW_O22_M_CO_MUTE_R_COLR,		///< mute R pxl_rep1_value
	PE_INF_HW_O22_M_MAX					///< max num
}
PE_INF_HW_O22_MONITOR_MENU;

/**
 *	pe read read pixel menu enumeration
 */
typedef enum
{
	PE_INF_HW_O22_RD_PXL_DISPLAY = 0,		///< menu display
	PE_INF_HW_O22_RD_PXL_WCP_HOR_POS,		///< wcp horizontal position
	PE_INF_HW_O22_RD_PXL_WCP_VER_POS,		///< wcp vertical position
	PE_INF_HW_O22_RD_PXL_WCP_MARK_EN,		///< wcp mark enable
	PE_INF_HW_O22_RD_PXL_WCP_PXL_E_Y,		///< wcp pixel even y
	PE_INF_HW_O22_RD_PXL_WCP_PXL_E_B,		///< wcp pixel even cb
	PE_INF_HW_O22_RD_PXL_WCP_PXL_E_R,		///< wcp pixel even cr
	PE_INF_HW_O22_RD_PXL_WCP_PXL_O_Y,		///< wcp pixel odd y
	PE_INF_HW_O22_RD_PXL_WCP_PXL_O_B,		///< wcp pixel odd cb
	PE_INF_HW_O22_RD_PXL_WCP_PXL_O_R,		///< wcp pixel odd cr
	PE_INF_HW_O22_RD_PXL_LED_HOR_POS,		///< led horizontal position
	PE_INF_HW_O22_RD_PXL_LED_VER_POS,		///< led vertical position
	PE_INF_HW_O22_RD_PXL_LED_MARK_EN,		///< led mark enable
	PE_INF_HW_O22_RD_PXL_LED_PIXEL_R,		///< led pixel red
	PE_INF_HW_O22_RD_PXL_LED_PIXEL_G,		///< led pixel green
	PE_INF_HW_O22_RD_PXL_LED_PIXEL_B,		///< led pixel blue
	PE_INF_HW_O22_RD_MAX					///< max num
}
PE_INF_HW_O22_RD_PXL_MENU;

/**
 *	PE_INF_O22_CHPI_APB
 */
typedef enum
{
	PE_INF_O22_CHPI_APB_NONE      = 0x00000000,
	PE_INF_O22_CHPI_APB_CMN0      = 0x00000001,
	PE_INF_O22_CHPI_APB_CEN0      = 0x00000002,
	PE_INF_O22_CHPI_APB_CEN1      = 0x00000004,
	PE_INF_O22_CHPI_APB_CW0       = 0x00000008,
	PE_INF_O22_CHPI_APB_VSP0      = 0x00000010,
	PE_INF_O22_CHPI_APB_DSE0      = 0x00000020,
	PE_INF_O22_CHPI_APB_DCE0      = 0x00000040,
	PE_INF_O22_CHPI_APB_DTM0      = 0x00000080,
	PE_INF_O22_CHPI_APB_LLL0      = 0x00000100,
	PE_INF_O22_CHPI_APB_FSW0      = 0x00000200,
	PE_INF_O22_CHPI_APB_TM        = 0x01000000,
	PE_INF_O22_CHPI_APB_YG        = 0x02000000,
	PE_INF_O22_CHPI_APB_H_LUT     = (PE_INF_O22_CHPI_APB_TM|PE_INF_O22_CHPI_APB_YG),
	PE_INF_O22_CHPI_APB_HS        = 0x10000000,
	PE_INF_O22_CHPI_APB_PCC       = 0x20000000,
	PE_INF_O22_CHPI_APB_MAX       = 0xffffffff
}
PE_INF_O22_CHPI_APB;

/**
 *	PE_INF_O22_CHPI_TBL
 */
typedef enum
{
	PE_INF_O22_CHPI_TBL_NONE      = 0x00000000,
	PE_INF_O22_CHPI_TBL_CCO       = 0x00000001,
	PE_INF_O22_CHPI_TBL_OBC       = 0x00000002,
	PE_INF_O22_CHPI_TBL_OBE       = 0x00000004,
	PE_INF_O22_CHPI_TBL_AMG       = 0x00000008,
	PE_INF_O22_CHPI_TBL_RES       = 0x00000010,
	PE_INF_O22_CHPI_TBL_CTI       = 0x00000020,
	PE_INF_O22_CHPI_TBL_TNR       = 0x00000040,
	PE_INF_O22_CHPI_TBL_DNR       = 0x00000080,
	PE_INF_O22_CHPI_TBL_OSD       = 0x00000100,
	PE_INF_O22_CHPI_TBL_SQM0      = 0x00000200,
	PE_INF_O22_CHPI_TBL_SQM1      = 0x00000400,
	PE_INF_O22_CHPI_TBL_SQM2      = 0x00000800,
	PE_INF_O22_CHPI_TBL_SQM3      = 0x00001000,
	PE_INF_O22_CHPI_TBL_SQM4      = 0x00002000,
	PE_INF_O22_CHPI_TBL_USR0      = 0x00004000,
	PE_INF_O22_CHPI_TBL_USR1      = 0x00008000,
	PE_INF_O22_CHPI_TBL_USR2      = 0x00010000,
	PE_INF_O22_CHPI_TBL_DRC       = 0x00020000,
	PE_INF_O22_CHPI_TBL_OBEC      = 0x00040000,
	PE_INF_O22_CHPI_TBL_MAX       = 0xffffffff
}
PE_INF_O22_CHPI_TBL;

/**
 *	pe control inf
 */
typedef struct
{
	UINT32 pe0_src_h;		///< pe input horizontal size
	UINT32 pe0_src_v;		///< pe input vertical size
	UINT32 i_sc_type;		///< pe input scan type(nd), 1:p, 0:i
	UINT32 u_i_win_h_ofst;	///< user in window horizontal offset
	UINT32 u_i_win_v_ofst;	///< user in window vertical offset
	UINT32 u_i_win_h_size;	///< user in window horizontal size
	UINT32 u_i_win_v_size;	///< user in window vertical size
	UINT32 u_o_win_h_ofst;	///< user out window horizontal offset
	UINT32 u_o_win_v_ofst;	///< user out window vertical offset
	UINT32 u_o_win_h_size;	///< user out window horizontal size
	UINT32 u_o_win_v_size;	///< user out window vertical size
	UINT32 i_c_format;		///< input color format(nd), 0x6:444,0x5:422, else 420
	UINT32 sat_status;		///< saturation status
	UINT32 mute_on;			///< mute on, 1:on, 0:off
	UINT32 hv_same;			///< ctrl0 is_split_mode, ctrl1 is_resize, 1:yes,
	UINT32 pxl_rp_st;		///< pixel replace state, 0x0~0x2:off,r,g,b
	UINT32 is_src_frz;		///< src_freeze_state, 0x1:freeze,0x0:normal
	UINT32 fw_src;			///< fw_src, 0x0:fw off, 0x1:fw on, 0x2~ :see reg menual
	UINT32 vcp_mute_on;		///< vcp block mute on, 1:on, 0:off for multiview
	UINT32 is_ndskip;		///< nd block skip
	UINT32 panel_resolution;///< 0:ud, 1:FHD, 2:1366x768, 3:1280x720, 4:720x480
}
PE_INF_O22_CTRL_T;

/**
 *	pe inf settings type
 */
typedef struct
{
	LX_PE_INF_DISPLAY_T disp_info[LX_PE_WIN_NUM];		///< display info
	PE_INF_O22_CTRL_T ctrl_info[LX_PE_WIN_NUM];			///< control info
}
PE_INF_O22_SETTINGS_T;

/*----------------------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------------------*/
int PE_INF_O22_Init(PE_CFG_CTRL_T *pstParams);
int PE_INF_O22_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams);
int PE_INF_O22_SetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
int PE_INF_O22_GetDisplayInfo(LX_PE_INF_DISPLAY_T *pstParams);
int PE_INF_O22_CheckSclInfo(void);
int PE_INF_O22_GetCurInfSettings(PE_INF_O22_SETTINGS_T *pstParams);
int PE_INF_O22_GetCurDispInfSettings(UINT32 wid, LX_PE_INF_DISPLAY_T *pstParams);
int PE_INF_O22_GetCurCtrlInfSettings(UINT32 wid, PE_INF_O22_CTRL_T *pstParams);
int PE_INF_O22_GetCurModeInfSettings(UINT32 wid, LX_PE_INF_OP_MODE_T *pstParams);
int PE_INF_O22_GetLevelInfo(LX_PE_INF_LEVEL_T *pstParams);
int PE_INF_O22_SetMiscTbl(LX_PE_ETC_TBL_T *pstParams);
int PE_INF_O22_GetMiscTbl(LX_PE_ETC_TBL_T *pstParams);
int PE_INF_O22_SetTraceDataBuf(UINT32 type, char *data);
int PE_INF_O22_SetTracePacketData(LX_PE_PKT_T *pstParams);
int PE_INF_O22_GetCurDdrTopHeader(void *pstParams);
int PE_INF_O22_GetCurDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type);
int PE_INF_O22_GetCurLgsrDdrTopHeader(void *pstParams);
int PE_INF_O22_GetCurLgsrDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type);
int PE_INF_O22F22_GetCurDdrTopHeader(void *pstParams);
int PE_INF_O22F22_GetCurDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type);
int PE_INF_O22F22_GetCurLgsrDdrTopHeader(void *pstParams);
int PE_INF_O22F22_GetCurLgsrDdrSecHeader(void *top_h, void *pstParams, UINT32 sec_type);
int PE_INF_O22_IncChipInfoApbCount(UINT32 type);
int PE_INF_O22_IncChipInfoTblCount(UINT32 type);
int PE_INF_O22_GetStatus(UINT32 *p_data, UINT32 count);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_INF_O22_H_ */

