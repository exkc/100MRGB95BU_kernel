/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or 
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of 
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
	GNU General Public License for more details.
*/ 


/** @file
 *
 *	hal for physical ipc.
 *
 *	author		
 *	version		1.0
 *	date		
 *	note		
 *
 *	@addtogroup 
 *	@{
 */

/*------------------------------------------------------------------------------
	Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	File Inclusions
------------------------------------------------------------------------------*/
#include "os_util.h"
#include "base_device.h"

#include "de_model.h"
#include "de_kapi.h"
#include "de_ver_def.h"
#include "de_def.h"
#include "de_hal_def.h"
#include "pe_drv.h"

#include "mcu/de_int_def.h"
#include "mcu/de_ipc_def.h"
#include "ipc_phys_hal.h"
#ifdef USE_KDRV_CODES_FOR_M17
#include "m17/de/de_reg_m17.h"
#include "m17/de/de_ipc_m17.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M19
#include "m19/de/de_reg_m19.h"
#include "m19/de/de_ipc_m19.h"
#endif
#ifdef USE_KDRV_CODES_FOR_L18
#include "l18/de/de_reg_l18.h"
#include "l18/de/de_ipc_l18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O18
#include "o18/de/de_reg_o18.h"
#include "o18/de/de_ipc_o18.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O20
#include "o20/de/de_reg_o20.h"
#include "o20/de/de_ipc_o20.h"
#endif
#ifdef USE_KDRV_CODES_FOR_E60
#include "e60/de/de_reg_e60.h"
#include "e60/de/de_ipc_e60.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O22
#include "o22/de/de_reg_o22.h"
#include "o22/de/de_ipc_o22.h"
#endif
#ifdef USE_KDRV_CODES_FOR_M23
#include "m23/de/de_reg_m23.h"
#include "m23/de/de_ipc_m23.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O24
#include "o24/de/de_reg_o24.h"
#include "o24/de/de_ipc_o24.h"
#endif
#ifdef USE_KDRV_CODES_FOR_O26
#include "o26/de/de_reg_o26.h"
#include "o26/de/de_ipc_o26.h"
#endif

/*------------------------------------------------------------------------------
	Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Macro Definitions
------------------------------------------------------------------------------*/
#define CHECK_REG_NULL(fp) {if(fp == NULL || g_chip_id < 0)\
							{DE_ERROR("%s is null\n",#fp); \
							return RET_ERROR;}}
#define GET_ID() g_chip_id

/*------------------------------------------------------------------------------
	Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	global Functions  
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	global Variables
------------------------------------------------------------------------------*/
static int g_chip_id = 0;
ipc_reg_cb_t gp_ipc_reg;

/*------------------------------------------------------------------------------
	Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
	Static Variables
------------------------------------------------------------------------------*/

/*==============================================================================
	Implementation Group
==============================================================================*/

int ipc_phys_hal_init(void)
{
	int ret = RET_OK;

	memset(&gp_ipc_reg, 0, sizeof(ipc_reg_cb_t));

#ifdef USE_KDRV_CODES_FOR_O18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O18) ) {
		g_chip_id = 3;
		gp_ipc_reg.get_irq_num           = DE_REG_O18_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status   = DE_IPC_O18_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_O18_ClearStatus;
		gp_ipc_reg.clear_wdg_status      = DE_WDG_O18_WakeUpReg;
		gp_ipc_reg.wakeup_ipc            = DE_IPC_O18_WakeUpReg;
		gp_ipc_reg.init_ipc              = DE_IPC_O18_Init;
		gp_ipc_reg.free_ipc              = DE_IPC_O18_Free;
		gp_ipc_reg.check_irq4vsync       = DE_REG_O18_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt        = DE_REG_O18_InitInterrupt;
		gp_ipc_reg.get_mute_status       = DE_REG_O18_CheckMuteStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_L18
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) {
		g_chip_id = 2;
		gp_ipc_reg.get_irq_num           = NULL; //DE_REG_L18_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status   = NULL; //DE_IPC_L18_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = NULL; //DE_IPC_L18_ClearStatus;
		gp_ipc_reg.clear_wdg_status      = NULL; //DE_WDG_L18_WakeUpReg;
		gp_ipc_reg.wakeup_ipc            = DE_IPC_L18_WakeUpReg;
		gp_ipc_reg.init_ipc              = DE_IPC_L18_Init;
		gp_ipc_reg.free_ipc              = DE_IPC_L18_Free;
		gp_ipc_reg.check_irq4vsync       = NULL;	//DE_REG_L18_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt        = DE_REG_L18_InitInterrupt;
	} else
#endif

#ifdef USE_KDRV_CODES_FOR_M17
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) ) {
		g_chip_id = 1;
		gp_ipc_reg.get_irq_num           = DE_REG_M17_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status   = DE_IPC_M17_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_M17_ClearStatus;
		gp_ipc_reg.clear_wdg_status      = DE_WDG_M17_WakeUpReg;
		gp_ipc_reg.wakeup_ipc            = DE_IPC_M17_WakeUpReg;
		gp_ipc_reg.init_ipc              = DE_IPC_M17_Init;
		gp_ipc_reg.free_ipc              = DE_IPC_M17_Free;
		gp_ipc_reg.check_irq4vsync       = DE_REG_M17_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt        = DE_REG_M17_InitInterrupt;
		gp_ipc_reg.get_mute_status       = DE_REG_M17_CheckMuteStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M19
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) ) {
		g_chip_id = 1;
		gp_ipc_reg.get_irq_num           = DE_REG_M19_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status   = DE_IPC_M19_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_M19_ClearStatus;
		gp_ipc_reg.clear_wdg_status      = DE_WDG_M19_WakeUpReg;
		gp_ipc_reg.wakeup_ipc            = DE_IPC_M19_WakeUpReg;
		gp_ipc_reg.init_ipc              = DE_IPC_M19_Init;
		gp_ipc_reg.free_ipc              = DE_IPC_M19_Free;
		gp_ipc_reg.check_irq4vsync       = DE_REG_M19_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt        = DE_REG_M19_InitInterrupt;
		gp_ipc_reg.get_mute_status       = DE_REG_M19_CheckMuteStatus;
		gp_ipc_reg.get_fw_status         = DE_REG_M19_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O20
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) ) {
		g_chip_id = 4;
		gp_ipc_reg.get_irq_num			 = DE_REG_O20_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_O20_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_O20_ClearStatus;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_O20_WakeUpReg;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_O20_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_O20_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_O20_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_O20_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_O20_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_O20_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_O20_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_E60
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) {
		g_chip_id = 4;
		gp_ipc_reg.get_irq_num			 = DE_REG_E60_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_E60_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_E60_ClearStatus;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_E60_WakeUpReg;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_E60_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_E60_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_E60_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_E60_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_E60_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_E60_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_E60_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O22
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) {
		g_chip_id = 5;
		gp_ipc_reg.get_irq_num			 = DE_REG_O22_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_O22_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_O22_ClearStatus;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_O22_WakeUpReg;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_O22_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_O22_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_O22_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_O22_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_O22_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_O22_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_O22_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_M23
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) ) {
		g_chip_id = 6;
		gp_ipc_reg.get_irq_num			 = DE_REG_M23_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_M23_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_M23_ClearStatus;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_M23_WakeUpReg;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_M23_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_M23_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_M23_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_M23_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_M23_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_M23_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_M23_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O24
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) ) {
		g_chip_id = 7;
		gp_ipc_reg.get_irq_num			 = DE_REG_O24_GetIrqNum;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_O24_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_O24_ClearStatus;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_O24_WakeUpReg;
		gp_ipc_reg.cleanup_status		 = DE_IPC_O24_CleanupStatus;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_O24_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_O24_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_O24_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_O24_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_O24_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_O24_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_O24_CheckFwStatus;
	} else
#endif
#ifdef USE_KDRV_CODES_FOR_O26
	if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) ) {
		g_chip_id = 8;
		gp_ipc_reg.get_irq_num			 = DE_REG_O26_GetIrqNum;
		gp_ipc_reg.get_irq_num_ex		 = DE_REG_O26_GetIrqNum_ex;
		gp_ipc_reg.get_ipc_intr_status	 = DE_IPC_O26_GetStatusReg;
		gp_ipc_reg.clear_ipc_intr_status = DE_IPC_O26_ClearStatus;
		gp_ipc_reg.clear_ipc_intr_status2= DE_IPC_O26_ClearStatus2;
		gp_ipc_reg.clear_ipc_intr_status3= DE_IPC_O26_ClearStatus3;
		gp_ipc_reg.clear_wdg_status 	 = DE_WDG_O26_WakeUpReg;
		gp_ipc_reg.cleanup_status		 = DE_IPC_O26_CleanupStatus;
		gp_ipc_reg.wakeup_ipc			 = DE_IPC_O26_WakeUpReg;
		gp_ipc_reg.init_ipc 			 = DE_IPC_O26_Init;
		gp_ipc_reg.free_ipc 			 = DE_IPC_O26_Free;
		gp_ipc_reg.check_irq4vsync		 = DE_REG_O26_CheckIrq4Vsync;
		gp_ipc_reg.init_interrupt		 = DE_REG_O26_InitInterrupt;
		gp_ipc_reg.get_mute_status		 = DE_REG_O26_CheckMuteStatus;
		gp_ipc_reg.get_fw_status		 = DE_REG_O26_CheckFwStatus;
		gp_ipc_reg.ctop_intr			 = DE_IPC_O26_ctop_intr;
	} else
#endif
	{
		g_chip_id = -1;
		ret = RET_ERROR;
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Get interrupt status for IPC
 *
 * @param ipcType [IN] interrupt type for IPC which is happend 
 *                      from either MCU or CPU
 * @param pStatus [OUT] interrupt status for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_GetIntrStatus(	UINT32 mcu_id,           \
								VIDEO_IPC_TYPE_T ipcType,\
								UINT32 *pStatus)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.get_ipc_intr_status);
	ret = gp_ipc_reg.get_ipc_intr_status(mcu_id, ipcType, pStatus);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_ClearIPCStatus(UINT32 mcu_id, VIDEO_IPC_TYPE_T ipcType, UINT32 *pStatus)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.clear_ipc_intr_status);
	ret = gp_ipc_reg.clear_ipc_intr_status(mcu_id, ipcType, pStatus);

	return ret;
}

int ipc_phys_hal_ClearIPCStatus2(UINT32 type)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.clear_ipc_intr_status2);
	ret = gp_ipc_reg.clear_ipc_intr_status2(type);

	return ret;
}

int ipc_phys_hal_ClearIPCStatus3(UINT32 type)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.clear_ipc_intr_status3);
	ret = gp_ipc_reg.clear_ipc_intr_status3(type);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for watch dog
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_ClearWDGStatus(UINT32 mcu_id)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.clear_wdg_status);
	ret = gp_ipc_reg.clear_wdg_status(mcu_id, FALSE);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief cleanup status of CPU for IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_cleanup_ipc_status(UINT32 mcu_id)
{
	int ret = RET_OK;

	if (gp_ipc_reg.cleanup_status) {
		ret = gp_ipc_reg.cleanup_status(mcu_id);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Notify that a CTOP_INTERRUPT has occurred on the MCU.
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_CTOPIntr()
{
	int ret = RET_OK;

	if (gp_ipc_reg.ctop_intr)
	{
		ret = gp_ipc_reg.ctop_intr();
	}
	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make IPC interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_WakeUpIPC(UINT32 mcu_id)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.wakeup_ipc);
	ret = gp_ipc_reg.wakeup_ipc(mcu_id, VIDEO_IPC_MCU, TRUE);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialze IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_IPCInit(UINT32 mcu_id, void **pBuffToMCU, void **pBuffFrMCU)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.init_ipc);
	ret = gp_ipc_reg.init_ipc(mcu_id, pBuffToMCU, pBuffFrMCU);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief uninitialze IPC
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
BOOLEAN ipc_phys_hal_IPCFree(void **pBuffToMCU, void **pBuffFrMCU)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.free_ipc);
	ret = gp_ipc_reg.free_ipc(pBuffToMCU, pBuffFrMCU);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get irq number
 *
 * @param fr_rate [IN] value of Frame rate of Display
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_GetIrqNum(UINT32 mcu_id, UINT32 *ipc_irq_num, UINT32 *sync_irq_num)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.get_irq_num);
	ret = gp_ipc_reg.get_irq_num(mcu_id, ipc_irq_num, sync_irq_num);

	return ret;
}

int ipc_phys_hal_GetIrqNum_ex(UINT32 *irq_num, UINT32 num)
{
	int ret = RET_OK;

	if (gp_ipc_reg.get_irq_num_ex) {
		ret = gp_ipc_reg.get_irq_num_ex(irq_num, num);
	}
	else {
		DE_NOTI("not support\n");
		ret = RET_ERROR;
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief init interrupt
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_InitInterrupt(UINT32 mcu_id, BOOLEAN intr_en)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.init_interrupt);
	ret = gp_ipc_reg.init_interrupt(mcu_id, intr_en);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief Clear Inerrupt status of CPU for DMA
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
BOOLEAN ipc_phys_hal_CheckIrq4Vsync(UINT32 mcu_id)
{
	BOOLEAN vsyncIrq = 0;

	CHECK_REG_NULL(gp_ipc_reg.check_irq4vsync);
	vsyncIrq = gp_ipc_reg.check_irq4vsync(mcu_id);

	return vsyncIrq;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief make AMZ(seamless mode) interrupt of MCU be happen
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_WakeUpSeamless(UINT32 mcu_id)
{
	int ret = RET_OK;

	CHECK_REG_NULL(gp_ipc_reg.wakeup_ipc);
	ret = gp_ipc_reg.wakeup_ipc(mcu_id, VIDEO_AMZ_MCU, TRUE);

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mute status
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_CheckMute(UINT32 win_id, UINT32 *mute_status)
{
	int ret = RET_OK;

#ifdef INCLUDE_KDRV_PE
	if(0 == PE_IsInit())	return ret;//if pe reg is not ready, return.

	CHECK_REG_NULL(gp_ipc_reg.get_mute_status);
	ret = gp_ipc_reg.get_mute_status(win_id, mute_status);
#endif

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mute status
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int ipc_phys_hal_CheckFwStatus(UINT32 win_id, void *status)
{
	int ret = RET_OK;

#ifdef INCLUDE_KDRV_PE
	if(0 == PE_IsInit())	return ret;//if pe reg is not ready, return.

	CHECK_REG_NULL(gp_ipc_reg.get_fw_status);
	ret = gp_ipc_reg.get_fw_status(win_id, status);
#endif

	return ret;
}

