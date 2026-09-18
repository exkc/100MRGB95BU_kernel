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

/** @file pe_cmn.c
 *
 *  driver for picture enhance common functions.
 *  ( used only within kdriver )
 *
 *	@author		Seung-Jun, Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note
 *	@date		2011.06.11
 *	@see
 */

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "debug_util.h"

#include "pe_def.h"
#include "pe_reg.h"
#include "pe_etc.h"
#include "pe_spd.h"
#include "pe_cmn.h"
#include "pe_etc_hw.h"
#include "pe_cmn_hw.h"

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/
#define PE_CMN_DBG_PRINT(fmt, args...)	\
	if (_g_cmn_trace)\
	{\
		printk("[%x,%x][%s,%d] "fmt, \
			PE_CHIP_VER, g_pe_kdrv_ver_mask, __F__, __L__, ##args);\
	}

/*----------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------*/
typedef struct
{
	int (*hw_init)(PE_CFG_CTRL_T *pstParams);
	int (*ipc_open)(void);
	int (*ipc_close)(void);
	int (*create_pic_task)(void);
	int (*stop_pic_task)(void);
	int (*spd_module)(void);
	int (*resume_module)(UINT32 stParams);
	int (*get_mem_info)(unsigned int *base, unsigned int *size);
	int (*fwi_init)(PE_CFG_CTRL_T *pstParams);
	int (*set_default)(LX_PE_DEFAULT_SETTINGS_T *pstParams);
	int (*get_default)(LX_PE_DEFAULT_SETTINGS_T *pstParams);
	int (*set_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*get_debug)(LX_PE_DBG_SETTINGS_T *pstParams);
	int (*set_contrast)(void *pstParams);
	int (*get_contrast)(void *pstParams);
	int (*set_brightness)(void *pstParams);
	int (*get_brightness)(void *pstParams);
	int (*set_saturation)(LX_PE_CMN_SATURATION_T *pstParams);
	int (*get_saturation)(LX_PE_CMN_SATURATION_T *pstParams);
	int (*set_hue)(LX_PE_CMN_HUE_T *pstParams);
	int (*get_hue)(LX_PE_CMN_HUE_T *pstParams);
	int (*set_level_ctrl)(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
	int (*get_level_ctrl)(LX_PE_CMN_LEVEL_CTRL_T *pstParams);
	int (*set_vcp_level_ctrl)(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
	int (*get_vcp_level_ctrl)(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
	int (*set_bypass_blocks)(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams);
	int (*get_lgsr_mem_info)(void *pstParams);
	int (*set_lgsr_srsqm)(UINT32 pstParams);
	int (*set_lgsr_run_tra)(UINT32 pstParams);
	int (*set_lgsr_halt_tra)(UINT32 pstParams);
	int (*set_lgsr_crop_pos)(UINT32 *pstParams);
	int (*set_lgsr_done_ddr)(UINT32 pstParams);
	int (*set_lgsr_user_ready)(UINT32 pstParams);
	int (*set_lgsr_vaild_run)(UINT32 pstParams);
	int (*set_lgsr_demo_mode)(UINT32 pstParams);
	int (*set_lgsr_ui_onoff)(UINT32 pstParams);
	int (*set_lgsr_accl_srsqm)(UINT32 pstParams);
	int (*set_lgsr_accl_tra)(UINT32 pstParams);
	int (*set_lgsr_get_status)(void);
	int (*get_lgsr_lnestatus)(UINT32 *pstParams);
	int (*get_lgsr_trastatus)(UINT32 *pstParams);
	int (*set_vcp_sat_ctrl)(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams);
}
PE_CMN_CB_FUNC_T;

/*----------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Functions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------*/
UINT32 g_pe_kdrv_ver_mask = 0x0;	//default 0x0
LX_DE_IPC_SYSTEM_INFO_T g_pe_lgsr_mem_info;


/*----------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------*/
static PE_CMN_CB_FUNC_T _g_pe_cmn_cb_fn;
static UINT32 _g_cmn_trace=0x0;	//default should be off.
static PE_CMN_SETTINGS_T _g_pe_cmn_info;

/*============================================================================
	Implementation Group
============================================================================*/
/**
 * check chip rev
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_CheckChipRev(void)
{
	/************** cfg kdrv ver **************/
	g_pe_kdrv_ver_mask = \
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M17, A0), LX_CHIP_REV(M17, B0), \
		PE_KDRV_VER_BIT_M17AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M17, B0), LX_CHIP_REV(M17, C0), \
		PE_KDRV_VER_BIT_M17BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M17, C0), LX_CHIP_REV(M17, D0), \
		PE_KDRV_VER_BIT_M17CX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M19, A0), LX_CHIP_REV(M19, B0), \
		PE_KDRV_VER_BIT_M19AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M19, B0), LX_CHIP_REV(M19, C0), \
		PE_KDRV_VER_BIT_M19BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O18, A0), LX_CHIP_REV(O18, B0), \
		PE_KDRV_VER_BIT_O18AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O18, B0), LX_CHIP_REV(O18, C0), \
		PE_KDRV_VER_BIT_O18BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O20, A0), LX_CHIP_REV(O20, B0), \
		PE_KDRV_VER_BIT_O20AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O20, B0), LX_CHIP_REV(O20, C0), \
		PE_KDRV_VER_BIT_O20BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(E60, A0), LX_CHIP_REV(E60, B0), \
		PE_KDRV_VER_BIT_E60AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(E60, B0), LX_CHIP_REV(E60, C0), \
		PE_KDRV_VER_BIT_E60BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(E60, C0), LX_CHIP_REV(E60, D0), \
		PE_KDRV_VER_BIT_E60CX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O22, A0), LX_CHIP_REV(O22, B0), \
		PE_KDRV_VER_BIT_O22AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O22, B0), LX_CHIP_REV(O22, C0), \
		PE_KDRV_VER_BIT_O22BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M23, A0), LX_CHIP_REV(M23, B0), \
		PE_KDRV_VER_BIT_M23AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(M23, B0), LX_CHIP_REV(M23, C0), \
		PE_KDRV_VER_BIT_M23BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O24, A0), LX_CHIP_REV(O24, B0), \
		PE_KDRV_VER_BIT_O24AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O24, B0), LX_CHIP_REV(O24, C0), \
		PE_KDRV_VER_BIT_O24BX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O26, A0), LX_CHIP_REV(O26, B0), \
		PE_KDRV_VER_BIT_O26AX)|\
		PE_KDRV_CHK_VER_BIT(LX_CHIP_REV(O26, B0), LX_CHIP_REV(O26, C0), \
		PE_KDRV_VER_BIT_O26BX);
	/******************************************/
	return RET_OK;
}
/**
 * register call back functions
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_RegisterCbFunc(void)
{
	int ret = RET_OK;

	memset(&_g_pe_cmn_cb_fn, 0, sizeof(PE_CMN_CB_FUNC_T));
	do{
		#ifdef USE_PE_KDRV_CODES_FOR_O26
		if (PE_KDRV_VER_O26)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_O26_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_O26_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_O26_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_O26_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_O26_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_O26_SuspendModule;
			_g_pe_cmn_cb_fn.resume_module		= PE_CMN_HW_O26_ResumeModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_O26_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_O26_GetMemInfo;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_O26_SetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_O26_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_O26_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_O26_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_O26_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_O26_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_O26_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_O26_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_O26_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_O26_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_O26_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_O26_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_O26_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_O26_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info	= PE_LGSR_HW_O26_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_O26_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra	= PE_LGSR_HW_O26_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra	= PE_LGSR_HW_O26_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos	= PE_LGSR_HW_O26_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr	= PE_LGSR_HW_O26_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_O26_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_O26_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_O26_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff		= PE_LGSR_HW_O26_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm 	= PE_LGSR_HW_O26_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   	= PE_LGSR_HW_O26_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status 	= PE_LGSR_HW_O26_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  	= PE_LGSR_HW_O26_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  	= PE_LGSR_HW_O26_GetTraStatus;
			_g_pe_cmn_cb_fn.set_vcp_sat_ctrl	    = PE_CMN_HW_O26_SetVcpSaturationCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O24
		if (PE_KDRV_VER_O24)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_O24_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_O24_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_O24_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_O24_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_O24_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_O24_SuspendModule;
			_g_pe_cmn_cb_fn.resume_module		= PE_CMN_HW_O24_ResumeModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_O24_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_O24_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_O24_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= NULL;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_O24_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_O24_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_O24_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_O24_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_O24_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_O24_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_O24_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_O24_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_O24_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_O24_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_O24_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_O24_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_O24_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info	= PE_LGSR_HW_O24_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_O24_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra	= PE_LGSR_HW_O24_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra	= PE_LGSR_HW_O24_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos	= PE_LGSR_HW_O24_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr	= PE_LGSR_HW_O24_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_O24_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_O24_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_O24_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff		= PE_LGSR_HW_O24_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm 	= PE_LGSR_HW_O24_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   	= PE_LGSR_HW_O24_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status 	= PE_LGSR_HW_O24_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  	= PE_LGSR_HW_O24_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  	= PE_LGSR_HW_O24_GetTraStatus;
			_g_pe_cmn_cb_fn.set_vcp_sat_ctrl	    = PE_CMN_HW_O24_SetVcpSaturationCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M23
		if (PE_KDRV_VER_M23)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_M23_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_M23_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_M23_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_M23_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_M23_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_M23_SuspendModule;
			_g_pe_cmn_cb_fn.resume_module		= PE_CMN_HW_M23_ResumeModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_M23_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_M23_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_M23_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= NULL;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_M23_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_M23_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_M23_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_M23_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_M23_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_M23_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_M23_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_M23_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_M23_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_M23_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_M23_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_M23_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_M23_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info		= PE_LGSR_HW_M23_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_M23_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra		= PE_LGSR_HW_M23_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra		= PE_LGSR_HW_M23_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos		= PE_LGSR_HW_M23_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr		= PE_LGSR_HW_M23_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_M23_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_M23_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_M23_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff		= PE_LGSR_HW_M23_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm 	= PE_LGSR_HW_M23_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   	= PE_LGSR_HW_M23_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status 	= PE_LGSR_HW_M23_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  	= PE_LGSR_HW_M23_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  	= PE_LGSR_HW_M23_GetTraStatus;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O22
		if (PE_KDRV_VER_O22)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_O22_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_O22_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_O22_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_O22_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_O22_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_O22_SuspendModule;
			_g_pe_cmn_cb_fn.resume_module		= PE_CMN_HW_O22_ResumeModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_O22_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_O22_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_O22_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= NULL;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_O22_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_O22_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_O22_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_O22_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_O22_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_O22_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_O22_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_O22_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_O22_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_O22_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_O22_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_O22_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_O22_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info	= PE_LGSR_HW_O22_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_O22_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra	= PE_LGSR_HW_O22_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra	= PE_LGSR_HW_O22_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos	= PE_LGSR_HW_O22_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr	= PE_LGSR_HW_O22_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_O22_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_O22_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_O22_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff		= PE_LGSR_HW_O22_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm 	= PE_LGSR_HW_O22_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   	= PE_LGSR_HW_O22_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status 	= PE_LGSR_HW_O22_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  	= PE_LGSR_HW_O22_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  	= PE_LGSR_HW_O22_GetTraStatus;
			_g_pe_cmn_cb_fn.set_vcp_sat_ctrl	    = PE_CMN_HW_O22_SetVcpSaturationCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_E60
		if (PE_KDRV_VER_E60)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_E60_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_E60_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_E60_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_E60_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_E60_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_E60_SuspendModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_E60_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_E60_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_E60_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= NULL;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_E60_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_E60_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_E60_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_E60_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_E60_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_E60_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_E60_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_E60_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_E60_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_E60_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	    = PE_CMN_HW_E60_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_E60_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_E60_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info		= PE_LGSR_HW_E60_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_E60_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra		= PE_LGSR_HW_E60_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra		= PE_LGSR_HW_E60_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos		= PE_LGSR_HW_E60_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr		= PE_LGSR_HW_E60_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_E60_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_E60_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_E60_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff		= PE_LGSR_HW_E60_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm 	= PE_LGSR_HW_E60_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   	= PE_LGSR_HW_E60_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status 	= PE_LGSR_HW_E60_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  	= PE_LGSR_HW_E60_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  	= PE_LGSR_HW_E60_GetTraStatus;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O20
		if (PE_KDRV_VER_O20)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_O20_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_O20_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_O20_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_O20_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_O20_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_O20_SuspendModule;
			_g_pe_cmn_cb_fn.resume_module		= PE_CMN_HW_O20_ResumeModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_O20_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_O20_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_O20_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= PE_CMN_HW_O20_GetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_O20_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_O20_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_O20_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_O20_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_O20_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_O20_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_O20_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_O20_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_O20_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_O20_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_O20_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_O20_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_O20_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_lgsr_mem_info	= PE_LGSR_HW_O20_GetMemInfo;
			_g_pe_cmn_cb_fn.set_lgsr_srsqm	    = PE_LGSR_HW_O20_SetSrSQM;
			_g_pe_cmn_cb_fn.set_lgsr_run_tra	= PE_LGSR_HW_O20_RunTRA;
			_g_pe_cmn_cb_fn.set_lgsr_halt_tra	= PE_LGSR_HW_O20_HaltTRA;
			_g_pe_cmn_cb_fn.set_lgsr_crop_pos	= PE_LGSR_HW_O20_SetCropSize;
			_g_pe_cmn_cb_fn.set_lgsr_done_ddr	= PE_LGSR_HW_O20_DoneDownloadDdr;
			_g_pe_cmn_cb_fn.set_lgsr_user_ready	= PE_LGSR_HW_O20_UserReady;
			_g_pe_cmn_cb_fn.set_lgsr_vaild_run	= PE_LGSR_HW_O20_ValidRun;
			_g_pe_cmn_cb_fn.set_lgsr_demo_mode	= PE_LGSR_HW_O20_DemoMode;
			_g_pe_cmn_cb_fn.set_lgsr_ui_onoff	= PE_LGSR_HW_O20_UIOnoff;
			_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm = PE_LGSR_HW_O20_AccelModeSrSqm;
			_g_pe_cmn_cb_fn.set_lgsr_accl_tra   = PE_LGSR_HW_O20_AccelModeTRA;
			_g_pe_cmn_cb_fn.set_lgsr_get_status = PE_LGSR_HW_O20_PrintLGSRStatus;
			_g_pe_cmn_cb_fn.get_lgsr_lnestatus  = PE_LGSR_HW_O20_GetLneStatus;
			_g_pe_cmn_cb_fn.get_lgsr_trastatus  = PE_LGSR_HW_O20_GetTraStatus;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_O18
		if (PE_KDRV_VER_O18)
		{
			_g_pe_cmn_cb_fn.hw_init 			= PE_CMN_HW_O18_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_O18_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_O18_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task 	= PE_TSK_O18_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_O18_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_O18_SuspendModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_O18_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_O18_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default 		= NULL;
			_g_pe_cmn_cb_fn.get_default 		= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_O18_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= PE_CMN_HW_O18_GetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_O18_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_O18_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_O18_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_O18_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_O18_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_O18_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue 			= PE_CMN_HW_O18_SetHue;
			_g_pe_cmn_cb_fn.get_hue 			= PE_CMN_HW_O18_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_O18_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_O18_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_O18_SetBypassBlock;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_O18_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_O18_GetVcpLevelCtrl;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M17
		if (PE_KDRV_VER_M17CX)
		{
			_g_pe_cmn_cb_fn.hw_init				= PE_CMN_HW_M17C0_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_M17C0_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_M17C0_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task		= PE_TSK_M17C0_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_M17C0_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_M17C0_SuspendModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_M17C0_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= NULL;
			_g_pe_cmn_cb_fn.set_default			= NULL;
			_g_pe_cmn_cb_fn.get_default			= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_M17C0_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= PE_CMN_HW_M17C0_GetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_M17C0_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_M17C0_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_M17C0_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_M17C0_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_M17C0_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_M17C0_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue				= PE_CMN_HW_M17C0_SetHue;
			_g_pe_cmn_cb_fn.get_hue				= PE_CMN_HW_M17C0_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_M17C0_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_M17C0_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_M17C0_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_M17C0_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_M17C0_SetBypassBlock;
		}
		else if (PE_KDRV_VER_M17BX || PE_KDRV_VER_M17AX)
		{
			_g_pe_cmn_cb_fn.hw_init				= PE_CMN_HW_M17_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_M17_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_M17_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task		= PE_TSK_M17_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_M17_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_M17_SuspendModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_M17_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= NULL;
			_g_pe_cmn_cb_fn.set_default			= NULL;
			_g_pe_cmn_cb_fn.get_default			= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_M17_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= PE_CMN_HW_M17_GetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_M17_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_M17_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_M17_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_M17_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_M17_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_M17_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue				= PE_CMN_HW_M17_SetHue;
			_g_pe_cmn_cb_fn.get_hue				= PE_CMN_HW_M17_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_M17_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_M17_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_M17_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_M17_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_M17_SetBypassBlock;
		}
		else
		#endif
		#ifdef USE_PE_KDRV_CODES_FOR_M19
		if (PE_KDRV_VER_M19)
		{
			_g_pe_cmn_cb_fn.hw_init				= PE_CMN_HW_M19_Init;
			_g_pe_cmn_cb_fn.ipc_open			= PE_FWI_M19_IPC_Open;
			_g_pe_cmn_cb_fn.ipc_close			= PE_FWI_M19_IPC_Close;
			_g_pe_cmn_cb_fn.create_pic_task		= PE_TSK_M19_CreatePicTask;
			_g_pe_cmn_cb_fn.stop_pic_task		= PE_TSK_M19_StopPicTask;
			_g_pe_cmn_cb_fn.spd_module			= PE_CMN_HW_M19_SuspendModule;
			_g_pe_cmn_cb_fn.fwi_init			= PE_FWI_M19_Init;
			_g_pe_cmn_cb_fn.get_mem_info		= PE_CMN_HW_M19_GetMemInfo;
			_g_pe_cmn_cb_fn.set_default			= NULL;
			_g_pe_cmn_cb_fn.get_default			= NULL;
			_g_pe_cmn_cb_fn.set_debug			= PE_CMN_HW_M19_SetDebugSettings;
			_g_pe_cmn_cb_fn.get_debug			= PE_CMN_HW_M19_GetDebugSettings;
			_g_pe_cmn_cb_fn.set_contrast		= PE_CMN_HW_M19_SetContrast;
			_g_pe_cmn_cb_fn.get_contrast		= PE_CMN_HW_M19_GetContrast;
			_g_pe_cmn_cb_fn.set_brightness		= PE_CMN_HW_M19_SetBrightness;
			_g_pe_cmn_cb_fn.get_brightness		= PE_CMN_HW_M19_GetBrightness;
			_g_pe_cmn_cb_fn.set_saturation		= PE_CMN_HW_M19_SetSaturation;
			_g_pe_cmn_cb_fn.get_saturation		= PE_CMN_HW_M19_GetSaturation;
			_g_pe_cmn_cb_fn.set_hue				= PE_CMN_HW_M19_SetHue;
			_g_pe_cmn_cb_fn.get_hue				= PE_CMN_HW_M19_GetHue;
			_g_pe_cmn_cb_fn.set_level_ctrl		= PE_CMN_HW_M19_SetLevelCtrl;
			_g_pe_cmn_cb_fn.get_level_ctrl		= PE_CMN_HW_M19_GetLevelCtrl;
			_g_pe_cmn_cb_fn.set_vcp_level_ctrl	= PE_CMN_HW_M19_SetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.get_vcp_level_ctrl	= PE_CMN_HW_M19_GetVcpLevelCtrl;
			_g_pe_cmn_cb_fn.set_bypass_blocks	= PE_CMN_HW_M19_SetBypassBlock;
		}
		else
		#endif
		{
			PE_PRINT_ERROR("[%x,%x] kdrv chip ver is wrong.\n", \
				PE_CHIP_VER, g_pe_kdrv_ver_mask);
			ret = RET_ERROR;
		}
	}while (0);
	return ret;
}
/**
 * open picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_OpenPicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_cmn_cb_fn.ipc_open)
		{
			ret = _g_pe_cmn_cb_fn.ipc_open();
			PE_CHECK_CODE(ret, break, "ipc_open() error.\n");
		}
		if(_g_pe_cmn_cb_fn.create_pic_task)
		{
			ret = _g_pe_cmn_cb_fn.create_pic_task();
			PE_CHECK_CODE(ret, break, "create_pic_task() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * close picture enhance module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_ClosePicEnhanceModule(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_cmn_cb_fn.stop_pic_task)
		{
			ret = _g_pe_cmn_cb_fn.stop_pic_task();
			PE_CHECK_CODE(ret, break, "stop_pic_task() error.\n");
		}
		if(_g_pe_cmn_cb_fn.ipc_close)
		{
			ret = _g_pe_cmn_cb_fn.ipc_close();
			PE_CHECK_CODE(ret, break, "ipc_close() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * suspend module
 *
 * @param   void
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SuspendModule(void)
{
	int ret = RET_OK;
	do{
		if(_g_pe_cmn_cb_fn.spd_module)
		{
			ret = _g_pe_cmn_cb_fn.spd_module();
			PE_CHECK_CODE(ret, break, "spd_module() error.\n");
		}
	}while (0);
	return ret;
}
int PE_CMN_ResumeModule(UINT32 stParams)
{
	int ret = RET_OK;
	do{
		if(_g_pe_cmn_cb_fn.resume_module)
		{
			ret = _g_pe_cmn_cb_fn.resume_module(stParams);
			PE_CHECK_CODE(ret, break, "spd_module() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get memory info
 *
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author	sj.youm@lge.com
 */
int PE_CMN_GetMemInfo(unsigned int *base, unsigned int *size)
{
	int ret = RET_OK;
	do{
		if(_g_pe_cmn_cb_fn.get_mem_info)
		{
			ret = _g_pe_cmn_cb_fn.get_mem_info(base,size);
			PE_CHECK_CODE(ret, break, "get_mem_info() error.\n");
		}
		else
		{
			ret = RET_ERROR;
		}
	}while (0);
	return ret;
}

/**
 * init common module
 *
 * @param   *pstParams [in] PE_CFG_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_Init(PE_CFG_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		PE_CMN_DBG_PRINT("init global values.\n");
		memset0(_g_pe_cmn_info);
		if(_g_pe_cmn_cb_fn.fwi_init)
		{
			ret = _g_pe_cmn_cb_fn.fwi_init(pstParams);
			PE_CHECK_CODE(ret, break, "fwi_init() error.\n");
		}
		if(_g_pe_cmn_cb_fn.hw_init)
		{
			ret = _g_pe_cmn_cb_fn.hw_init(pstParams);
			PE_CHECK_CODE(ret, break, "hw_init() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * standard function of cmn setting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#ifdef PE_KDRV_USE_SPD_FUNC
#define PE_CMN_SET_FSDP(_struct, _func, _sdp)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), \
				break, "[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			ret = PE_SPD_COPY_FROM_USER(_sdp, (void *)&param, (void *)p_rcv, datasize);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s error.\n", __F__, __L__, #_sdp);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_CMN_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break
#endif

#define PE_CMN_SET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, \
				"[%s,%d] %s() error.\n", __F__, __L__, #_func);\
			PE_CMN_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch(functype)
	{
		#ifdef PE_KDRV_USE_SPD_FUNC
		PE_CMN_SET_FSDP(LX_PE_CMN_CONTRAST_T,		PE_CMN_SetContrast,			PE_SUSPEND_CMN_SETCONTRAST);
		PE_CMN_SET_FSDP(LX_PE_CMN_BRIGHTNESS_T,		PE_CMN_SetBrightness,		PE_SUSPEND_CMN_SETBRIGHTNESS);
		PE_CMN_SET_FSDP(LX_PE_CMN_SATURATION_T,		PE_CMN_SetSaturation,		PE_SUSPEND_CMN_SETSATURATION);
		PE_CMN_SET_FSDP(LX_PE_CMN_HUE_T,			PE_CMN_SetHue,				PE_SUSPEND_CMN_SETHUE);
		PE_CMN_SET_FSDP(LX_PE_DEFAULT_SETTINGS_T,	PE_CMN_SetDefaultSettings,	PE_SUSPEND_CMN_SETDEFAULT);
		#else
		PE_CMN_SET_FUNC(LX_PE_CMN_CONTRAST_T,		PE_CMN_SetContrast);
		PE_CMN_SET_FUNC(LX_PE_CMN_BRIGHTNESS_T,		PE_CMN_SetBrightness);
		PE_CMN_SET_FUNC(LX_PE_CMN_SATURATION_T,		PE_CMN_SetSaturation);
		PE_CMN_SET_FUNC(LX_PE_CMN_HUE_T,			PE_CMN_SetHue);
		PE_CMN_SET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CMN_SetDefaultSettings);
		#endif
		PE_CMN_SET_FUNC(LX_PE_CMN_LEVEL_CTRL_T,		PE_CMN_SetLevelCtrl);
		PE_CMN_SET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMN_SetDebugSettings);
		PE_CMN_SET_FUNC(LX_PE_CMN_VCP_LEVEL_CTRL_T,	PE_CMN_SetVcpLevelCtrl);
		PE_CMN_SET_FUNC(LX_PE_CMN_BYPASS_BLOCKS_T,	PE_CMN_SetBypassBlocks);
		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}

/**
 * standard function of cmn getting
 *
 * @param   data [in/out] unsigned int
 * @param   functype [in] unsigned int
 * @param   datasize [in] unsigned int
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetFunction(unsigned int *data, unsigned int functype, unsigned int datasize)
{
	int ret = RET_ERROR;

#define PE_CMN_GET_FUNC(_struct, _func)	\
	case PE_ITEM_PKTFUNC(_struct):\
	{\
		_struct *p_rcv, param;\
		do{\
			PE_CMN_DBG_PRINT("S %s\n", #_struct);\
			PE_CHECK_CODE(datasize!=sizeof(_struct), break, \
				"[%s,%d] size mismatch.\n", __F__, __L__);\
			p_rcv = (_struct *)data;\
			memcpy(&param, p_rcv, datasize);\
			ret = _func(&param);\
			PE_CHECK_CODE(ret, break, "[%s,%d] %s() error.\n", \
				__F__, __L__, #_func);\
			memcpy(p_rcv, &param, datasize);\
			PE_CMN_DBG_PRINT("E %s\n", #_struct);\
		}while (0);\
	}\
	break

	/* data null check */
	PE_CHECK_CODE(!data, return RET_ERROR, \
		"[%s,%d] data is null.\n", __F__, __L__);
	switch(functype)
	{
		PE_CMN_GET_FUNC(LX_PE_CMN_CONTRAST_T,		PE_CMN_GetContrast);
		PE_CMN_GET_FUNC(LX_PE_CMN_BRIGHTNESS_T,		PE_CMN_GetBrightness);
		PE_CMN_GET_FUNC(LX_PE_CMN_SATURATION_T,		PE_CMN_GetSaturation);
		PE_CMN_GET_FUNC(LX_PE_CMN_HUE_T,			PE_CMN_GetHue);
		PE_CMN_GET_FUNC(LX_PE_CMN_LEVEL_CTRL_T,		PE_CMN_GetLevelCtrl);
		PE_CMN_GET_FUNC(LX_PE_DEFAULT_SETTINGS_T,	PE_CMN_GetDefaultSettings);
		PE_CMN_GET_FUNC(LX_PE_DBG_SETTINGS_T,		PE_CMN_GetDebugSettings);
		PE_CMN_GET_FUNC(LX_PE_CMN_VCP_LEVEL_CTRL_T,	PE_CMN_GetVcpLevelCtrl);
		default:
		{
			PE_PRINT_ERROR("functype(%d) default case.\n", functype);
			ret = RET_ERROR;
		}
		break;
	}
	return ret;
}
/**
 * set cmn fmt default settings
 *
 * @param   *pstParams [in] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	PE_CMN_SETTINGS_T *pInfo = NULL;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		pInfo=&_g_pe_cmn_info;	/* to avoid warning(unused variable) */
		PE_CMN_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
		if (PE_CHECK_WIN0(pstParams->win_id))
		{
			memcpy(&(pInfo->dflt[LX_PE_WIN_0]), pstParams, sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		if (PE_CHECK_WIN1(pstParams->win_id))
		{
			memcpy(&(pInfo->dflt[LX_PE_WIN_1]), pstParams, sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
	}while (0);
	return ret;
}
/**
 * get cmn fmt default settings
 *
 * @param   *pstParams [in/out] LX_PE_DEFAULT_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetDefaultSettings(LX_PE_DEFAULT_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	LX_PE_WIN_ID win_id;
	PE_CMN_SETTINGS_T *pInfo = &_g_pe_cmn_info;
	do{
		CHECK_KNULL(pstParams);
		PE_CHECK_WINID(pstParams->win_id);
		win_id = PE_GET_CHECKED_WINID(pstParams->win_id);
		if (PE_CHECK_WIN0(win_id))
		{
			memcpy(pstParams, &(pInfo->dflt[LX_PE_WIN_0]), sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		if (PE_CHECK_WIN1(win_id))
		{
			memcpy(pstParams, &(pInfo->dflt[LX_PE_WIN_1]), sizeof(LX_PE_DEFAULT_SETTINGS_T));
		}
		PE_CMN_DBG_PRINT("[win id:%d]\n", pstParams->win_id);
	}while (0);
	return ret;
}
/**
 * set cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		/* set print level */
		if (pstParams->type&LX_PE_DBG_LV)
		{
			_g_cmn_trace = (pstParams->print_lvl & \
				(0x1<<PE_ITEM_PKTMODL(CMN)))? 0x1:0x0;
		}
		if(_g_pe_cmn_cb_fn.set_debug)
		{
			ret = _g_pe_cmn_cb_fn.set_debug(pstParams);
			PE_CHECK_CODE(ret, break, "set_debug() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get cmn debug settings
 *
 * @param   *pstParams [in] LX_PE_DBG_SETTINGS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetDebugSettings(LX_PE_DBG_SETTINGS_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_debug)
		{
			ret = _g_pe_cmn_cb_fn.get_debug(pstParams);
			PE_CHECK_CODE(ret, break, "get_debug() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set contrast
 *
 * @param   *pstParams [in] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetContrast(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_contrast)
		{
			ret = _g_pe_cmn_cb_fn.set_contrast(pstParams);
			PE_CHECK_CODE(ret, break, "set_contrast() error.\n");
		}
	}while (0);
	return ret;
}

/**
 * get contrast
 *
 * @param   *pstParams [in/out] LX_PE_CMN_CONTRAST_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetContrast(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_contrast)
		{
			ret = _g_pe_cmn_cb_fn.get_contrast(pstParams);
			PE_CHECK_CODE(ret, break, "get_contrast() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set brightness
 *
 * @param   *pstParams [in] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetBrightness(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_brightness)
		{
			ret = _g_pe_cmn_cb_fn.set_brightness(pstParams);
			PE_CHECK_CODE(ret, break, "set_brightness() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get brightness
 *
 * @param   *pstParams [in/out] LX_PE_CMN_BRIGHTNESS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetBrightness(void *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_brightness)
		{
			ret = _g_pe_cmn_cb_fn.get_brightness(pstParams);
			PE_CHECK_CODE(ret, break, "get_brightness() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set saturation
 *
 * @param   *pstParams [in] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_saturation)
		{
			ret = _g_pe_cmn_cb_fn.set_saturation(pstParams);
			PE_CHECK_CODE(ret, break, "set_saturation() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get saturation
 *
 * @param   *pstParams [in/out] LX_PE_CMN_SATURATION_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetSaturation(LX_PE_CMN_SATURATION_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_saturation)
		{
			ret = _g_pe_cmn_cb_fn.get_saturation(pstParams);
			PE_CHECK_CODE(ret, break, "get_saturation() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set hue
 *
 * @param   *pstParams [in] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_hue)
		{
			ret = _g_pe_cmn_cb_fn.set_hue(pstParams);
			PE_CHECK_CODE(ret, break, "set_hue() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get hue
 *
 * @param   *pstParams [in/out] LX_PE_CMN_HUE_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetHue(LX_PE_CMN_HUE_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_hue)
		{
			ret = _g_pe_cmn_cb_fn.get_hue(pstParams);
			PE_CHECK_CODE(ret, break, "get_hue() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set level control
 *
 * @param   *pstParams [in] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_level_ctrl)
		{
			ret = _g_pe_cmn_cb_fn.set_level_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_level_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetLevelCtrl(LX_PE_CMN_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_level_ctrl)
		{
			ret = _g_pe_cmn_cb_fn.get_level_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_level_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set vcp level control
 *
 * @param   *pstParams [in] LX_PE_CMN_VCP_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_vcp_level_ctrl)
		{
			ret = _g_pe_cmn_cb_fn.set_vcp_level_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_vcp_level_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * get vcp level control
 *
 * @param   *pstParams [in/out] LX_PE_CMN_VCP_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_GetVcpLevelCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_vcp_level_ctrl)
		{
			ret = _g_pe_cmn_cb_fn.get_vcp_level_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "get_vcp_level_ctrl() error.\n");
		}
	}while (0);
	return ret;
}
/**
 * set bypass blocks
 *
 * @param   *pstParams [in] LX_PE_CMN_BYPASS_BLOCKS_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetBypassBlocks(LX_PE_CMN_BYPASS_BLOCKS_T *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_bypass_blocks)
		{
			ret = _g_pe_cmn_cb_fn.set_bypass_blocks(pstParams);
			PE_CHECK_CODE(ret, break, "set_bypass_blocks() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_GetMemInfo(void *pstParams)
{
	int ret = RET_OK;
	do {
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.get_lgsr_mem_info)
		{
			ret = _g_pe_cmn_cb_fn.get_lgsr_mem_info(pstParams);
			PE_CHECK_CODE(ret, break, "get_lgsr_mem_info() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_DoneDownloadDdr(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_done_ddr)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_done_ddr(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_done_ddr() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_SetSrSQM(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_srsqm)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_srsqm(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_srsqm() error.\n");
		}
	} while (0);
	return ret;
}

/**
 */
int PE_LGSR_RunTRA(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_run_tra)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_run_tra(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_run_tra() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_HaltTRA(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_halt_tra)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_halt_tra(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_halt_tra() error.\n");
		}
	} while (0);
	return ret;
}

/**
 */
int PE_LGSR_CropPosition(UINT32 *pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_crop_pos)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_crop_pos(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_crop_pos() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_UserReady(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_user_ready)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_user_ready(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_user_ready() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_ValidRun(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_vaild_run)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_vaild_run(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_vaild_run() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_Demomode(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_demo_mode)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_demo_mode(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_demo_mode() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_UIOnoff(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_ui_onoff)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_ui_onoff(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_ui_onoff() error.\n");
		}
	} while (0);
	return ret;
}

/**
 */
int PE_LGSR_AcclSrsqm(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_accl_srsqm)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_accl_srsqm(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_accl_srsqm() error.\n");
		}
	} while (0);
	return ret;
}

/**
 */
int PE_LGSR_AcclTra(UINT32 pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_accl_tra)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_accl_tra(pstParams);
			PE_CHECK_CODE(ret, break, "set_lgsr_accl_tra() error.\n");
		}
	} while (0);
	return ret;
}

/**
 */
int PE_LGSR_PrintStatus(void)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.set_lgsr_get_status)
		{
			ret = _g_pe_cmn_cb_fn.set_lgsr_get_status();
			PE_CHECK_CODE(ret, break, "set_lgsr_get_status() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_GetLneStatus(UINT32 *pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.get_lgsr_lnestatus)
		{
			ret = _g_pe_cmn_cb_fn.get_lgsr_lnestatus(pstParams);
			PE_CHECK_CODE(ret, break, "get_lgsr_lnestatus() error.\n");
		}
	} while (0);
	return ret;
}
/**
 */
int PE_LGSR_GetTraStatus(UINT32 *pstParams)
{
	int ret = RET_OK;
	do {
		if(_g_pe_cmn_cb_fn.get_lgsr_trastatus)
		{
			ret = _g_pe_cmn_cb_fn.get_lgsr_trastatus(pstParams);
			PE_CHECK_CODE(ret, break, "get_lgsr_trastatus() error.\n");
		}
	} while (0);
	return ret;
}

int PE_CMN_CheckDoubleSetting(LX_PE_WIN_ID id, \
				UINT32 *chk, void *prev, void *cur, UINT32 size)
{
	void *p_pre_val=NULL;
	void *p_cur_val=NULL;
	UINT32 valid_wid = 0xff;
	UINT32 i=0, set=0, set_flag=0;
	do {
		PE_CHECK_CODE(!chk, break, "[%s,%d]chk is null.\n", __F__, __L__);
		PE_CHECK_CODE(!prev, break, "[%s,%d]prev is null.\n", __F__, __L__);
		PE_CHECK_CODE(!cur, break, "[%s,%d]cur is null.\n", __F__, __L__);
		p_cur_val=cur;
		for (i=0;i<LX_PE_WIN_ALL;i++)
		{
			set = 0;
			if ((id==i)||(id==LX_PE_WIN_ALL))
			{
				p_pre_val = prev + (size*i);
				if ((*chk)&(0x1<<i))
				{
					/* if init is not zero and
					* both pre and cur val are not same */
					if (memcmp(p_pre_val, p_cur_val, size)!=0)
						set = 1;
				}
				else
				{
					/* if init is zero */
					(*chk)|=(0x1<<i);
					set = 1;
				}
				if (set>0)
				{
					memcpy(p_pre_val, p_cur_val, size);
				}
				set_flag |= set;
			}
		}
		valid_wid = set_flag? id:0xff;
	}while (0);
	return valid_wid;
}

/**
 * set vcp saturation control
 *
 * @param   *pstParams [in] LX_PE_CMN_VCP_LEVEL_CTRL_T
 * @return  OK if success, ERROR otherwise.
 * @see
 * @author
 */
int PE_CMN_SetVcpSaturationCtrl(LX_PE_CMN_VCP_LEVEL_CTRL_T *pstParams)
{
	int ret = RET_OK;
	do{
		CHECK_KNULL(pstParams);
		if(_g_pe_cmn_cb_fn.set_vcp_sat_ctrl)
		{
			ret = _g_pe_cmn_cb_fn.set_vcp_sat_ctrl(pstParams);
			PE_CHECK_CODE(ret, break, "set_vcp_sat_ctrl() error.\n");
		}
	}while (0);
	return ret;
}

