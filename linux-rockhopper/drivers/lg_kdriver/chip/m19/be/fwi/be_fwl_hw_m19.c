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
 *  fw loader reg driver file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2016.05.03
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_proc.h"

#include "be_kapi.h"
#include "be_def.h"
#include "be_cfg.h"
#include "ipc_def_m19.h"
#include "ipc_drv.h"
#include "be_fwl_hw_m19.h"

#include "ipc_cmd_header.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern BOOLEAN _BE_WCG_M19_IsHwComplete(void);
extern void _BE_WCG_M19_InitModeInfo(void);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/
extern BE_MEM_CFG_T *gpBeMem;

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_FWL_HAL_FW_T gHeader_Firmware_M19A0[BE_FW_DWLD_TYPE_MAXNUM] =
	{
#if CONFIG_LX_M19_CHIP_FIRMWARE
		{ BE_FW_DWLD_TYPE_FRC, 0, NULL, TRUE },
		{ BE_FW_DWLD_TYPE_WCG, 0, NULL, FALSE },
		{ BE_FW_DWLD_TYPE_LED, 0, NULL, FALSE },
		{ BE_FW_DWLD_TYPE_HDR, 0, NULL, FALSE }
#else
		{ BE_FW_DWLD_TYPE_FRC, 0, NULL, TRUE },
		{ BE_FW_DWLD_TYPE_WCG, 0, NULL, FALSE },
		{ BE_FW_DWLD_TYPE_LED, 0, NULL, FALSE },
		{ BE_FW_DWLD_TYPE_HDR, 0, NULL, FALSE }
#endif
	};

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/
BE_FWL_HAL_FW_T *BE_FWL_HW_M19_GetFwHeaderInfo(UINT8 ucIndex)
{
	if (ucIndex >= BE_FW_DWLD_TYPE_MAXNUM)
	{
		BE_ERROR("BE_FWL_HW  ERROR! ucIndex(0x%x) is invalid!\n", ucIndex);
		return NULL;
	}

	return &gHeader_Firmware_M19A0[ucIndex];
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief download BE firmware
 *
 * @param ucIndex [IN] index information for new firmware
 * @param pucBuff [IN] pointer information for new firmware
 * @param ulSize [IN] size information for new firmware
 * @param bIsMcuFw [IN] boolean information for MCU firmware or not
 *
 * @return FW base address if success, NULL for otherwise
 */
UINT32 BE_FWL_HW_M19_FW_Download(UINT8 ucIndex, UINT8 *pucBuff, UINT32 ulSize, BOOLEAN bIsMcuFw)
{
	int ret = RET_OK;
	BE_CH_MEM_T *pFwMem = NULL;
	char *lpAddr = NULL;
	UINT32 align = 0;

	do {
		CHECK_NULL(pucBuff);
		CHECK_NULL(ulSize);
		if(ucIndex >= BE_CH_MEM_DOWNLOAD_FW_MAX)
		{
			BREAK_WRONG(ucIndex);
		}

		pFwMem = (BE_CH_MEM_T *) &gpBeMem->fw[ucIndex];
		CHECK_NULL(pFwMem);
		CHECK_NULL(pFwMem->fw_base);

		if (ucIndex == BE_FW_DWLD_TYPE_WCG)
		{
			if (!_BE_WCG_M19_IsHwComplete())
			{
				BE_PRINT("%s: wait & retry! - return 0x1\n", __F__);
				ret = RET_TRY_AGAIN;
				break;
			}

			if (pFwMem->fw_base & 0xF)
			{
				align = (0x10 - (pFwMem->fw_base & 0xF));
			}
		}

		if ((ulSize + align) > pFwMem->fw_size) BREAK_WRONG(ulSize);

		lpAddr = (char *)vmap_phys(pFwMem->fw_base, pFwMem->fw_size);
		CHECK_NULL(lpAddr);

		lpAddr += align;
		memcpy(lpAddr, pucBuff, ulSize);

		wmb();

		vunmap_phys(lpAddr);
	} while(0);

	return ret == RET_OK ? pFwMem->fw_base : (ret == RET_TRY_AGAIN ? 0x1 : 0x0);
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mcu is alive
 *
 * @param void
 *
 * @return TRUE if mcu run, FALSE for otherwise
 */
BOOLEAN BE_FWL_HW_M19_MCUisAlive(void)
{
	BOOLEAN isFwRun = FALSE;

	isFwRun = TRUE;

	return isFwRun;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief return firmware memory base size
 *
 * @param ucIndex [IN] index information for the firmware
 *
 * @return firmware memory base size if success, 0 for otherwise
 */
UINT32 BE_FWL_HW_M19_GetFwMemBaseSize(UINT8 ucIndex)
{
	int ret = RET_OK;

	do {
		if(ucIndex >= BE_CH_MEM_DOWNLOAD_FW_MAX)
		{
			BREAK_WRONG(ucIndex);
			break;
		}
	} while(0);

	return ret == RET_OK ? gpBeMem->fw[ucIndex].fw_size : (UINT32)0;
}

int BE_FWL_HW_M19_WcgFwInit(UINT32 u32FwBaseAddr)
{
	int ret = RET_OK;

	do{
		BE_IPC_WCG_LOAD_LUT_T fwWcgLoadLutParam;

		_BE_WCG_M19_InitModeInfo();
		
		fwWcgLoadLutParam.bWCGLutLoad = TRUE;
		if (u32FwBaseAddr & 0xF)
		{
			u32FwBaseAddr += (0x10 - (u32FwBaseAddr & 0xF));
		}
		fwWcgLoadLutParam.uBaseAddr = u32FwBaseAddr; 
		ret = BE_KIPC_SetData(DPPB_PACK_CMD(BE_WCG_LOAD_LUT), &fwWcgLoadLutParam, sizeof(BE_IPC_WCG_LOAD_LUT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_FWL_HW_M19_LedFwInit(UINT32 u32FwBaseAddr)
{
	int ret = RET_OK;

	do{
		BE_IPC_LED_LOAD_LUT_T fwLedLoadLutParam;

		fwLedLoadLutParam.uLEDLutLoad = TRUE;
		ret = BE_KIPC_SetData(DPPB_PACK_CMD(BE_LED_LOAD_LUT), &fwLedLoadLutParam, sizeof(BE_IPC_LED_LOAD_LUT_T));
		if(ret) BREAK_WRONG(ret);
	} while(0);

	return ret;
}

int BE_FWL_HW_M19_ProcHandler(int proc_id, void* m, void* data)
{
	struct seq_file* ptrParam;
	ptrParam = (struct seq_file*)m;

	switch(proc_id)
	{
		case BE_FWI_PROC_ID_DETAIL_INFO:
		{

		}
		break;

		default: break;
	}

	return RET_OK;
}


