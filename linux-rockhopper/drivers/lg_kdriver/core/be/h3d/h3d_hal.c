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
 *  date		2012.03.16
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
#include <linux/delay.h>

#include "os_util.h"
#include "be_dbg.h"
#include "be_def.h"

#include "be_kapi.h"
#include "h3d_hal.h"

#include "m17/be/h3d/be_h3d_hw_m17.h"
#include "m19/be/h3d/be_h3d_hw_m19.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct BE_H3D_DRV_CHIP
{
	int	(*BE_H3D_HWSetMode)(LX_BE_H3D_MODE_T *pstParams);
	int	(*BE_H3D_HWGetMode)(LX_BE_H3D_MODE_T *pstParams);
	int	(*BE_H3D_HWT3CDepthLevel)(LX_BE_H3D_T3C_DEPTH_LEVEL_T *pstParams);
	int	(*BE_H3D_HWA3CDepthLevel)(LX_BE_H3D_A3C_DEPTH_LEVEL_T *pstParams);
	int	(*BE_H3D_HWA3CAutoConvergence)(LX_BE_H3D_A3C_AUTOCONVERGENCE_T *pstParams);
	int	(*BE_H3D_HWSetTridFmT)(LX_BE_TRIDTV_FMT_CTRL_T *pstParams);
	int	(*BE_H3D_HWProcHandler)(BE_H3D_PROC_ID_T proc_id, struct seq_file* m, void* data);

} BE_H3D_HW_FUNCTION_T;

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

/*========================================================================================
	Implementation Group
========================================================================================*/

BE_H3D_HW_FUNCTION_T stBeH3DHwFunction;

int BE_H3D_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&stBeH3DHwFunction,0,sizeof(BE_H3D_HW_FUNCTION_T));

	if (0)
	{

	}
#ifdef INCLUDE_O24_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
		{
			BE_PRINT("BE H3D chip revision is set to O24 A0\n");
			stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
			stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
			stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
			stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
		}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to M23 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			BE_PRINT("BE H3D chip revision is set to O22 A0\n");
			stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
			stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
			stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
			stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
			stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
		}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to E60 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to O20 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to M19 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to O18 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		NULL;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE H3D chip revision is set to M17 A0\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode				=		BE_H3D_HW_M17_Set_Mode;
		stBeH3DHwFunction.BE_H3D_HWGetMode				=		BE_H3D_HW_M17_Get_Mode;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel			=		BE_H3D_HW_M17_T3C_Depth_Level;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel			=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT				=		BE_H3D_HW_M17_Set_TridFmt;
		stBeH3DHwFunction.BE_H3D_HWProcHandler				=		BE_H3D_HW_M17_ProcHandler;
	}
#endif
	else
	{
		BE_PRINT("BE H3D : not support\n");
		stBeH3DHwFunction.BE_H3D_HWSetMode		 		=		NULL;
		stBeH3DHwFunction.BE_H3D_HWGetMode 				=		NULL;
		stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel	 	=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel	 	=		NULL;
		stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence	=		NULL;
		stBeH3DHwFunction.BE_H3D_HWSetTridFmT 			= 		NULL;
		stBeH3DHwFunction.BE_H3D_HWProcHandler			=		NULL;
		ret = RET_OK;
	}

	return ret;
}

int BE_H3D_HAL_Set_Mode(LX_BE_H3D_MODE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWSetMode == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_H3D_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_H3D_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWSetMode(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_Get_Mode(LX_BE_H3D_MODE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWGetMode == NULL)
	{
		pstParams->bA3CMode = FALSE;
		pstParams->bT3CMode = FALSE;
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWGetMode(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_T3C_Depth_Level(LX_BE_H3D_T3C_DEPTH_LEVEL_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_H3D_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_H3D_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWT3CDepthLevel(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_A3C_Depth_Level(LX_BE_H3D_A3C_DEPTH_LEVEL_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_H3D_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_H3D_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWA3CDepthLevel(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_A3C_AutoConvergence(LX_BE_H3D_A3C_AUTOCONVERGENCE_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_H3D_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_H3D_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWA3CAutoConvergence(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_Set_Trid_Fmt(LX_BE_TRIDTV_FMT_CTRL_T *pstParams)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWSetTridFmT == NULL)
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_H3D_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_H3D_HAL  WARNING! This function is not supported!\n");
		}
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWSetTridFmT(pstParams);
	}

	return ret;
}

int BE_H3D_HAL_ProcHandler(BE_H3D_PROC_ID_T proc_id, struct seq_file* m, void* data)
{
	int ret = RET_OK;

	if(stBeH3DHwFunction.BE_H3D_HWProcHandler == NULL)
	{
		ret = RET_ERROR;
	}
	else
	{
		ret  = stBeH3DHwFunction.BE_H3D_HWProcHandler(proc_id, m, data);
	}

	return ret;
}

