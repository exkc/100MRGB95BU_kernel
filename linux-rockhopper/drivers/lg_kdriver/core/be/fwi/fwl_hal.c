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
 *  fw loader hal driver file for BE device
 *
 *  author		dj911.kim
 *  version		1.0
 *  date		2014.06.02
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
//#include <asm/uaccess.h>
#include <linux/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_def.h"

#include "m17/be/fwi/be_fwl_hw_m17.h"
#include "o18/be/fwi/be_fwl_hw_o18.h"
#include "m19/be/fwi/be_fwl_hw_m19.h"
#include "o20/be/fwi/be_fwl_hw_o20.h"
#include "e60/be/fwi/be_fwl_hw_e60.h"
#include "o22/be/fwi/be_fwl_hw_o22.h"
#include "m23/be/fwi/be_fwl_hw_m23.h"
#include "o24/be/fwi/be_fwl_hw_o24.h"
#include "o26/be/fwi/be_fwl_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int (*pfnInitializeFWL)(void);
	int (*pfnCloseFWL)(void);
	BE_FWL_HAL_FW_FILE_T * (*pfnFwBinInfoFWL)(UINT8 ucIndex);
	BE_FWL_HAL_FW_T * (*pfnFwHeaderInfoFWL)(UINT8 ucIndex);
	UINT32 (*pfnFwDownloadFWL)(UINT8 ucIndex, UINT8 *pucBuff, UINT32 ulSize, BOOLEAN bIsMcuFw);
	BOOLEAN (*pfnMcuIsAliveFWL)(void);
	UINT32 (*pfnGetFwMemBaseSizeFWL)(UINT8 ucIndex);
	int (*pfnFrcFwInitFWL)(void);
	int (*pfnWcgFwInitFWL)(UINT32 u32FwBaseAddr);
	int (*pfnLedFwInitFWL)(UINT32 u32FwBaseAddr);
	int (*pfnHdrFwInitFWL)(UINT32 u32FwBaseAddr);
	int (*pfnProcHandler)(int proc_id, void* m, void* data);
} BE_FWL_HW_FUNCTION_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static BE_FWL_HW_FUNCTION_T gstBeFwlHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_FWL_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&gstBeFwlHwFunction,0,sizeof(BE_FWL_HW_FUNCTION_T));

	if(0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to O26 A0\n");
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_O26_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_O26_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_O26_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_O26_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_O26_WcgFwInit;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_O26_ProcHandler;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to O24 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_O24_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_O24_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_O24_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_O24_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_O24_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_O24_ProcHandler;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to M23 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_M23_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_M23_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_M23_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_M23_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_M23_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_M23_ProcHandler;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to O22 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_O22_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_O22_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_O22_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_O22_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_O22_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_O22_ProcHandler;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to E60 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_E60_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_E60_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_E60_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_E60_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_E60_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_E60_ProcHandler;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to O20 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_O20_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_O20_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_O20_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_O20_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_O20_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_O20_ProcHandler;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to M19 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_M19_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_M19_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_M19_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_M19_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_M19_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= BE_FWL_HW_M19_LedFwInit;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_M19_ProcHandler;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to O18 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_O18_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_O18_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_O18_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_O18_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_O18_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_O18_ProcHandler;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE FWL chip revision is set to M17 A0\n");
		gstBeFwlHwFunction.pfnInitializeFWL 			= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= BE_FWL_HW_M17_GetFwHeaderInfo;
		gstBeFwlHwFunction.pfnFwDownloadFWL 		= BE_FWL_HW_M17_FW_Download;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL 		= BE_FWL_HW_M17_MCUisAlive;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= BE_FWL_HW_M17_GetFwMemBaseSize;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= BE_FWL_HW_M17_WcgFwInit;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= BE_FWL_HW_M17_LedFwInit;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= BE_FWL_HW_M17_ProcHandler;
	}
#endif
	else
	{
		BE_ERROR("BE FWL ERROR! Unknown chip revision at BE FWL module\n");
		gstBeFwlHwFunction.pfnInitializeFWL				= NULL;
		gstBeFwlHwFunction.pfnCloseFWL				= NULL;
		gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
		gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= NULL;
		gstBeFwlHwFunction.pfnFwDownloadFWL			= NULL;
		gstBeFwlHwFunction.pfnMcuIsAliveFWL			= NULL;
		gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= NULL;
		gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnWcgFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
		gstBeFwlHwFunction.pfnProcHandler			= NULL;
		ret = RET_ERROR;
	}

	if(gstBeFwlHwFunction.pfnInitializeFWL)
	{
		ret = gstBeFwlHwFunction.pfnInitializeFWL();
	}

	return ret;
}

int BE_FWL_HAL_Close(void)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnCloseFWL)
	{
		ret = gstBeFwlHwFunction.pfnCloseFWL();
	}

	gstBeFwlHwFunction.pfnInitializeFWL				= NULL;
	gstBeFwlHwFunction.pfnCloseFWL				= NULL;
	gstBeFwlHwFunction.pfnFwBinInfoFWL			= NULL;
	gstBeFwlHwFunction.pfnFwHeaderInfoFWL		= NULL;
	gstBeFwlHwFunction.pfnFwDownloadFWL			= NULL;
	gstBeFwlHwFunction.pfnMcuIsAliveFWL			= NULL;
	gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL	= NULL;
	gstBeFwlHwFunction.pfnFrcFwInitFWL			= NULL;
	gstBeFwlHwFunction.pfnWcgFwInitFWL			= NULL;
	gstBeFwlHwFunction.pfnLedFwInitFWL			= NULL;
	gstBeFwlHwFunction.pfnHdrFwInitFWL			= NULL;
	gstBeFwlHwFunction.pfnProcHandler			= NULL;

	return ret;
}

BE_FWL_HAL_FW_FILE_T *BE_FWL_HAL_FwBinInfo(UINT8 ucIndex)
{
	if(gstBeFwlHwFunction.pfnFwBinInfoFWL)
	{
		return gstBeFwlHwFunction.pfnFwBinInfoFWL(ucIndex);
	}
	else
	{
		BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
		return NULL;
	}
}

BE_FWL_HAL_FW_T *BE_FWL_HAL_GetFwHeaderInfo(UINT8 ucIndex)
{
	if(gstBeFwlHwFunction.pfnFwHeaderInfoFWL)
	{
		return gstBeFwlHwFunction.pfnFwHeaderInfoFWL(ucIndex);
	}
	else
	{
		BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
		return NULL;
	}
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief download BE firmware in hal layer
 *
 * @param pstParams [IN] pointer, size information for new firmware
 *
 * @return FW base address if success, NULL for otherwise
 */
UINT32 BE_FWL_HAL_FwDownload(BE_FWL_HAL_FW_T* pstParams)
{
	if(gstBeFwlHwFunction.pfnFwDownloadFWL)
	{
		return gstBeFwlHwFunction.pfnFwDownloadFWL(pstParams->index, pstParams->pBuffer, pstParams->size, pstParams->isMcuFw);
	}
	else
	{
		BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
		return 0x0;
	}
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief check mcu is alive in hal layer
 *
 * @param void
 *
 * @return TRUE if mcu run, FALSE for otherwise
 */
BOOLEAN BE_FWL_HAL_McuIsAlive(void)
{
	if(gstBeFwlHwFunction.pfnMcuIsAliveFWL)
	{
		return gstBeFwlHwFunction.pfnMcuIsAliveFWL();
	}
	else
	{
		BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
		return FALSE;
	}
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief return firmware memory base size in hal layer
 *
 * @param ucIndex [IN] index information for the firmware
 *
 * @return firmware memory base size if success, 0 for otherwise
 */
UINT32 BE_FWL_HAL_GetFwMemBaseSize(UINT8 ucIndex)
{
	if(gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL)
	{
		return gstBeFwlHwFunction.pfnGetFwMemBaseSizeFWL(ucIndex);
	}
	else
	{
		BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
		return 0;
	}
}

int BE_FWL_HAL_FrcFwInit(void)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnFrcFwInitFWL)
	{
		ret = gstBeFwlHwFunction.pfnFrcFwInitFWL();
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FWL_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_FWL_HAL_WcgFwInit(UINT32 u32FwBaseAddr)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnWcgFwInitFWL)
	{
		ret = gstBeFwlHwFunction.pfnWcgFwInitFWL(u32FwBaseAddr);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FWL_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_FWL_HAL_LedFwInit(UINT32 u32FwBaseAddr)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnLedFwInitFWL)
	{
		ret = gstBeFwlHwFunction.pfnLedFwInitFWL(u32FwBaseAddr);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FWL_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_FWL_HAL_HdrFwInit(UINT32 u32FwBaseAddr)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnHdrFwInitFWL)
	{
		ret = gstBeFwlHwFunction.pfnHdrFwInitFWL(u32FwBaseAddr);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FWL_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_FWL_HAL_ProcHandler(BE_FWI_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if(gstBeFwlHwFunction.pfnProcHandler)
	{
		ret = gstBeFwlHwFunction.pfnProcHandler(proc_id, m, data);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FWL_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FWL_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

