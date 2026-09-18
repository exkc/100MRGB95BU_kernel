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
 *  interrupt hal file for BE device
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

#include "os_util.h"
#include "be_dbg.h"

#include "be_kapi.h"
#include "be_def.h"
#include "be_cfg.h"
#include "int_hal.h"
#include "m17/be/fwi/be_int_hw_m17.h"
#include "o18/be/fwi/be_int_hw_o18.h"
#include "m19/be/fwi/be_int_hw_m19.h"
#include "o20/be/fwi/be_int_hw_o20.h"
#include "e60/be/fwi/be_int_hw_e60.h"
#include "o22/be/fwi/be_int_hw_o22.h"
#include "m23/be/fwi/be_int_hw_m23.h"
#include "o24/be/fwi/be_int_hw_o24.h"

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
	int (*pfnInitializeINT)(void);
	int (*pfnCloseINT)(void);
	int (*pfnGetIrqNumINT)(UINT32 *beIrq0, UINT32 *beIrq1);
	int (*pfnIntrEnableINT)(void);
	int (*pfnGetStatusINT)(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus);
	int (*pfnClearStatusINT)(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus);
	int (*pfnWakeUpRegINT)(BE_INT_DIR_TYPE_T intrDir, BOOLEAN turnon);
} BE_INT_HW_FUNCTION_T;

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
static BE_INT_HW_FUNCTION_T gstBeIntHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize interrupt register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_INT_HAL_Init(void)
{
	int ret = RET_OK;

	memset(&gstBeIntHwFunction,0,sizeof(BE_INT_HW_FUNCTION_T));

	if(0)
	{

	}
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE INT chip revision is set to O24 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 	= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT	= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE INT chip revision is set to M23 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT		= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			BE_PRINT("BE INT chip revision is set to O22 A0\n");
			gstBeIntHwFunction.pfnInitializeINT 		= NULL;
			gstBeIntHwFunction.pfnCloseINT			= NULL;
			gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
			gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
			gstBeIntHwFunction.pfnGetStatusINT		= NULL;
			gstBeIntHwFunction.pfnClearStatusINT		= NULL;
			gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
		}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE INT chip revision is set to E60 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT		= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE INT chip revision is set to O20 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT		= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE INT chip revision is set to M19 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT		= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE INT chip revision is set to O18 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT 	= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT		= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE INT chip revision is set to M17 A0\n");
		gstBeIntHwFunction.pfnInitializeINT 		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= BE_INT_HW_M17_GetIrqNum;
		gstBeIntHwFunction.pfnIntrEnableINT 	= BE_INT_HW_M17_IntrEnable;
		gstBeIntHwFunction.pfnGetStatusINT		= BE_INT_HW_M17_GetStatus;
		gstBeIntHwFunction.pfnClearStatusINT		= BE_INT_HW_M17_ClearStatus;
		gstBeIntHwFunction.pfnWakeUpRegINT		= BE_INT_HW_M17_WakeUpReg;
	}
#endif
	else
	{
		BE_PRINT("BE INT : not support\n");
		gstBeIntHwFunction.pfnInitializeINT		= NULL;
		gstBeIntHwFunction.pfnCloseINT			= NULL;
		gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
		gstBeIntHwFunction.pfnIntrEnableINT		= NULL;
		gstBeIntHwFunction.pfnGetStatusINT		= NULL;
		gstBeIntHwFunction.pfnClearStatusINT	= NULL;
		gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;
		ret = RET_OK;
	}

	if(gstBeIntHwFunction.pfnInitializeINT)
	{
		ret = gstBeIntHwFunction.pfnInitializeINT();
	}

	return ret;
}

int BE_INT_HAL_Close(void)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnCloseINT)
	{
		ret = gstBeIntHwFunction.pfnCloseINT();
	}

	gstBeIntHwFunction.pfnInitializeINT			= NULL;
	gstBeIntHwFunction.pfnCloseINT			= NULL;
	gstBeIntHwFunction.pfnGetIrqNumINT		= NULL;
	gstBeIntHwFunction.pfnIntrEnableINT		= NULL;
	gstBeIntHwFunction.pfnGetStatusINT		= NULL;
	gstBeIntHwFunction.pfnClearStatusINT		= NULL;
	gstBeIntHwFunction.pfnWakeUpRegINT		= NULL;

	return ret;
}

int BE_INT_HAL_GetIrqNum(UINT32 *beIrq0, UINT32 *beIrq1)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnGetIrqNumINT)
	{
		ret = gstBeIntHwFunction.pfnGetIrqNumINT(beIrq0, beIrq1);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_INT_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

int BE_INT_HAL_IntrEnable(void)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnIntrEnableINT)
	{
		ret = gstBeIntHwFunction.pfnIntrEnableINT();
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_INT_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief get interrupt status
 *
 * @param intType [IN] interrupt type (hw interrupt/sw interrupt)
 * @param pIntrStatus [OUT] status  of hwi/swi
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_INT_HAL_GetStatus(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnGetStatusINT)
	{
		ret = gstBeIntHwFunction.pfnGetStatusINT(intrType, pIntrStatus);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_INT_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief clear interrupt status
 *
 * @param intrType [IN] interrupt type (hw interrupt/sw interrupt)
 * @param pIntrStatus [IN] status  of hwi/swi
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_INT_HAL_ClearStatus(BE_INT_TYPE_T intrType, UINT32 *pIntrStatus)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnClearStatusINT)
	{
		ret = gstBeIntHwFunction.pfnClearStatusINT(intrType, pIntrStatus);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_INT_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief wakeup interrupt to cpu/mcu
 *
 * @param intrDir [IN] direction of interrupt
 * @param turnIn [IN] turn on/off
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_INT_HAL_WakeUpReg(BE_INT_DIR_TYPE_T intrDir, BOOLEAN turnon)
{
	int ret = RET_OK;

	if(gstBeIntHwFunction.pfnWakeUpRegINT)
	{
		ret = gstBeIntHwFunction.pfnWakeUpRegINT(intrDir, turnon);
	}
	else
	{
		if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_ERROR)
		{
			BE_ERROR("BE_INT_HAL  ERROR! This function is not supported!\n");
			ret = RET_ERROR;
		}
		else if (gHalFuncSupportDbgLevel == BE_DBG_LEVEL_WARN)
		{
			BE_ERROR("BE_INT_HAL  WARNING! This function is not supported!\n");
		}
	}

	return ret;
}
