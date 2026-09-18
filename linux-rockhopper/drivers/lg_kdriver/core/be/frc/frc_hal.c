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
 *  frc hal file for BE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date			2012.03.16
 *  note			Additional information.
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
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_kapi.h"
#include "frc_hal.h"
#include "m17/be/frc/be_frc_hw_m17.h"
#include "o18/be/frc/be_frc_hw_o18.h"
#include "m19/be/frc/be_frc_hw_m19.h"
#include "o20/be/frc/be_frc_hw_o20.h"
#include "e60/be/frc/be_frc_hw_e60.h"
#include "o22/be/frc/be_frc_hw_o22.h"
#include "m23/be/frc/be_frc_hw_m23.h"
#include "o24/be/frc/be_frc_hw_o24.h"
#include "o26/be/frc/be_frc_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct BE_FRC_DRV_CHIP
{
	int	(*pfnInitializeFRC) (void);
	int	(*pfnCloseFRC) (void);
	int	(*pfnResumeFRC) (void);
	int	(*pfnControlMemcFRC) (LX_BE_FRC_MEMC_MODE_T *pstParams);
	int	(*pfnSetDemoModeFRC) (LX_BE_FRC_DEMO_MODE_T *pstParams);
	int	(*pfnSetDebugBoxFRC) (LX_BE_FRC_ENABLE_DEBUG_BOX_T *pstParams);
	int	(*pfnSetBypassMemcRegFRC) (LX_BE_FRC_MEMC_BYPASS_REGION_T *pstParams);
	int	(*pfnSetYUV444ModeFRC) (LX_BE_FRC_COLOR_YUV444_T *pstParams);
	int	(*pfnSetLowDelayFRC) (LX_BE_FRC_LOW_DELAY_T *pstParams);
	int	(*pfnSetMotionProFRC) (LX_BE_FRC_MOTION_PRO_T *pstParams);
	int	(*pfnGetFirmwareVerFRC) (LX_BE_FRC_VERSION_T *pstParams);
	int	(*pfnForceFrameRateFRC) (LX_BE_FRC_FRAME_RATE_T *pstParams);
	int	(*pfnSetFreezeFRC) (LX_BE_FRC_FREEZE_T *pstParams);
	int (*pfnUpdateFrameDelay) (LX_BE_LOW_DELAY_T *pstParams);
	int	(*pfnSetConfigFRC) (LX_BE_FRC_CFG_T *pstParams);
	int (*pfnProcHandler) (BE_FRC_PROC_ID_T proc_id, struct seq_file* m, void* data);
	int	(*pfnRunCommand) (LX_BE_FRC_CMD_T *pstParams);
} BE_FRC_HW_FUNCTION_T;

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/
BE_FRC_HW_FUNCTION_T gstBeFrcHwFunction;

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

int BE_FRC_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&gstBeFrcHwFunction,0,sizeof(BE_FRC_HW_FUNCTION_T));

	if (0)
	{
	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to O26 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_O26_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_O26_Close;
		gstBeFrcHwFunction.pfnResumeFRC 			= BE_FRC_HW_O26_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_O26_ControlMemc;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_O26_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_O26_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_O26_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_O26_RunCommand;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to O24 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_O24_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_O24_Close;
		gstBeFrcHwFunction.pfnResumeFRC 			= BE_FRC_HW_O24_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_O24_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_O24_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_O24_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_O24_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_O24_RunCommand;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to M23 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_M23_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_M23_Close;
		gstBeFrcHwFunction.pfnResumeFRC 			= BE_FRC_HW_M23_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_M23_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_M23_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_M23_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_M23_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_M23_RunCommand;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to O22 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_O22_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_O22_Close;
		gstBeFrcHwFunction.pfnResumeFRC 			= BE_FRC_HW_O22_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_O22_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_O22_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_O22_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_O22_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_O22_RunCommand;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to E60 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_E60_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_E60_Close;
		gstBeFrcHwFunction.pfnResumeFRC 			= BE_FRC_HW_E60_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_E60_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_E60_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_E60_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_E60_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_E60_RunCommand;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to O20 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_O20_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_O20_Close;
		gstBeFrcHwFunction.pfnResumeFRC				= BE_FRC_HW_O20_MemcResume;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_O20_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_O20_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_O20_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_O20_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_O20_RunCommand;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to M19 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_M19_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_M19_Close;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_M19_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_M19_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_M19_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_M19_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_M19_RunCommand;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to O18 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_O18_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_O18_Close;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_O18_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_O18_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_O18_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_O18_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_O18_RunCommand;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE FRC chip revision is set to M17 A0\n");
		gstBeFrcHwFunction.pfnInitializeFRC 		= BE_FRC_HW_M17_Initialize;
		gstBeFrcHwFunction.pfnCloseFRC				= BE_FRC_HW_M17_Close;
		gstBeFrcHwFunction.pfnControlMemcFRC		= BE_FRC_HW_M17_ControlMemc;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC		= NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC	= NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC		= NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC		= BE_FRC_HW_M17_SetMemcLowDelay;
		gstBeFrcHwFunction.pfnSetMotionProFRC		= BE_FRC_HW_M17_SetMemcMotionPro;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC 	= NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC 	= NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC			= NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= BE_FRC_HW_M17_ProcHandler;
		gstBeFrcHwFunction.pfnRunCommand			= BE_FRC_HW_M17_RunCommand;
	}
#endif
	else
	{
		BE_ERROR("BE FRC ERROR! Unknown chip revision at BE FRC module\n");
		gstBeFrcHwFunction.pfnInitializeFRC				=		NULL;
		gstBeFrcHwFunction.pfnCloseFRC				=		NULL;
		gstBeFrcHwFunction.pfnControlMemcFRC			=		NULL;
		gstBeFrcHwFunction.pfnSetDemoModeFRC		=		NULL;
		gstBeFrcHwFunction.pfnSetDebugBoxFRC			=		NULL;
		gstBeFrcHwFunction.pfnSetBypassMemcRegFRC 	=		NULL;
		gstBeFrcHwFunction.pfnSetYUV444ModeFRC	 	=		NULL;
		gstBeFrcHwFunction.pfnSetLowDelayFRC			=		NULL;
		gstBeFrcHwFunction.pfnGetFirmwareVerFRC	 	=		NULL;
		gstBeFrcHwFunction.pfnForceFrameRateFRC	 	=		NULL;
		gstBeFrcHwFunction.pfnSetFreezeFRC		 	=		NULL;
		gstBeFrcHwFunction.pfnUpdateFrameDelay		= NULL;
		gstBeFrcHwFunction.pfnSetConfigFRC			= NULL;
		gstBeFrcHwFunction.pfnProcHandler			= NULL;
		gstBeFrcHwFunction.pfnRunCommand			= NULL;
		return RET_ERROR;
	}

	if (gstBeFrcHwFunction.pfnInitializeFRC)
	{
		ret = gstBeFrcHwFunction.pfnInitializeFRC();
	}

	return ret;
}

int BE_FRC_HAL_Close(void)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnCloseFRC)
	{
		ret = gstBeFrcHwFunction.pfnCloseFRC();
	}

	gstBeFrcHwFunction.pfnInitializeFRC		 		=		NULL;
	gstBeFrcHwFunction.pfnCloseFRC				=		NULL;
	gstBeFrcHwFunction.pfnControlMemcFRC			=		NULL;
	gstBeFrcHwFunction.pfnSetDemoModeFRC		=		NULL;
	gstBeFrcHwFunction.pfnSetDebugBoxFRC			=		NULL;
	gstBeFrcHwFunction.pfnSetBypassMemcRegFRC 	=		NULL;
	gstBeFrcHwFunction.pfnSetYUV444ModeFRC	 	=		NULL;
	gstBeFrcHwFunction.pfnSetLowDelayFRC			=		NULL;
	gstBeFrcHwFunction.pfnGetFirmwareVerFRC	 	=		NULL;
	gstBeFrcHwFunction.pfnForceFrameRateFRC	 	=		NULL;
	gstBeFrcHwFunction.pfnProcHandler			= NULL;

	return ret;
}

int BE_FRC_HAL_Resume(void)
{
	int ret = RET_OK;

	if(gstBeFrcHwFunction.pfnResumeFRC)
	{
		ret = gstBeFrcHwFunction.pfnResumeFRC();
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_TOP_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_TOP_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_FRC_HAL_ControlMemc(LX_BE_FRC_MEMC_MODE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnControlMemcFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnControlMemcFRC(pstParams);
	}
	
	return ret;
}

int BE_FRC_HAL_Set_Demo_Mode(LX_BE_FRC_DEMO_MODE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetDemoModeFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetDemoModeFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_Debug_Box(LX_BE_FRC_ENABLE_DEBUG_BOX_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetDebugBoxFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetDebugBoxFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_Bypass_Memc_Reg(LX_BE_FRC_MEMC_BYPASS_REGION_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetBypassMemcRegFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetBypassMemcRegFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_YUV_444_Mode(LX_BE_FRC_COLOR_YUV444_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetYUV444ModeFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetYUV444ModeFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_Low_Delay(LX_BE_FRC_LOW_DELAY_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetLowDelayFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetLowDelayFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_Motion_Pro(LX_BE_FRC_MOTION_PRO_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetMotionProFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetMotionProFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Get_Firmware_Ver(LX_BE_FRC_VERSION_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnGetFirmwareVerFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnGetFirmwareVerFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Force_Frame_Rate(LX_BE_FRC_FRAME_RATE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnForceFrameRateFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnForceFrameRateFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Set_Freeze(LX_BE_FRC_FREEZE_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetFreezeFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetFreezeFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_Update_FrameDelay(LX_BE_LOW_DELAY_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnUpdateFrameDelay == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnUpdateFrameDelay(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_SetConfig(LX_BE_FRC_CFG_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnSetConfigFRC == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnSetConfigFRC(pstParams);
	}

	return ret;
}

int BE_FRC_HAL_ProcHandler(BE_FRC_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnProcHandler == NULL)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret = gstBeFrcHwFunction.pfnProcHandler(proc_id, m, data);
	}

	return ret;
}

int BE_FRC_HAL_RunCommand(LX_BE_FRC_CMD_T *pstParams)
{
	int ret = RET_OK;

	if (gstBeFrcHwFunction.pfnRunCommand == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_FRC_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_FRC_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = gstBeFrcHwFunction.pfnRunCommand(pstParams);
	}

	return ret;
}

