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
 *  ipc hal file for BE device
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

#include "be_def.h"
#include "fwi/ipc_hal.h"
#include "m17/be/fwi/be_ipc_hw_m17.h"
#include "o18/be/fwi/be_ipc_hw_o18.h"
#include "m19/be/fwi/be_ipc_hw_m19.h"
#include "o20/be/fwi/be_ipc_hw_o20.h"
#include "e60/be/fwi/be_ipc_hw_e60.h"
#include "o22/be/fwi/be_ipc_hw_o22.h"
#include "m23/be/fwi/be_ipc_hw_m23.h"
#include "o24/be/fwi/be_ipc_hw_o24.h"

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
	int (*pfnInitializeIPC)(void **pIPCBuffToMCU, void **pIPCBuffFrMCU);
	int (*pfnCloseIPC)(void **pIPCBuffToMCU, void **pIPCBuffFrMCU);
} BE_IPC_HW_FUNCTION_T;

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
static BE_IPC_HW_FUNCTION_T gstBeIpcHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * @callgraph
 * @callergraph
 *
 * @brief initialize ipc register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_IPC_HAL_Init(void **pIPCBuffToMCU, void **pIPCBuffFrMCU)
{
	int ret = RET_OK;

	memset(&gstBeIpcHwFunction,0,sizeof(BE_IPC_HW_FUNCTION_T));

	if(0)
	{

	}
#ifdef INCLUDE_O24_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to O24 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 	= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to M23 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		else if( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0) )
		{
			BE_PRINT("BE IPC chip revision is set to O22 A0\n");
			gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
			gstBeIpcHwFunction.pfnCloseIPC			= NULL;
		}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to E60 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to O20 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M19, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to M19 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( O18, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to O18 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= NULL;
		gstBeIpcHwFunction.pfnCloseIPC			= NULL;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if( lx_chip_rev( ) >= LX_CHIP_REV( M17, A0) )
	{
		BE_PRINT("BE IPC chip revision is set to M17 A0\n");
		gstBeIpcHwFunction.pfnInitializeIPC 		= BE_IPC_HW_M17_Init;
		gstBeIpcHwFunction.pfnCloseIPC			= BE_IPC_HW_M17_Close;
	}
#endif
	else
	{
		BE_PRINT("BE IPC : not support\n");
		gstBeIpcHwFunction.pfnInitializeIPC = NULL;
		gstBeIpcHwFunction.pfnCloseIPC      = NULL;
		ret = RET_OK;
	}

	if(gstBeIpcHwFunction.pfnInitializeIPC)
	{
		ret = gstBeIpcHwFunction.pfnInitializeIPC(pIPCBuffToMCU, pIPCBuffFrMCU);
	}

	return ret;
}

/**
 * @callgraph
 * @callergraph
 *
 * @brief free ipc register
 *
 * @return RET_OK(0) if success, none zero for otherwise
 */
int BE_IPC_HAL_Close(void **pIPCBuffToMCU, void **pIPCBuffFrMCU)
{
	int ret = RET_OK;

	if(gstBeIpcHwFunction.pfnCloseIPC)
	{
		ret = gstBeIpcHwFunction.pfnCloseIPC(pIPCBuffToMCU, pIPCBuffFrMCU);
	}

	gstBeIpcHwFunction.pfnInitializeIPC			= NULL;
	gstBeIpcHwFunction.pfnCloseIPC			= NULL;

	return ret;
}


