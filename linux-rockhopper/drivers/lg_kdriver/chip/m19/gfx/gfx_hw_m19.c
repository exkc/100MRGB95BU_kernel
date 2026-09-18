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

/** @file
 *
 *	GFX hw control
 *
 *  author      raxis.lim (raxis.lim@lge.com)
 *  version     1.0
 *  date
 *  note        Additional information.
 *
 *  @addtogroup lg1150_gfx
 *  @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "gfx_impl.h"

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
static	void CPC_InitClk(void)
{

}

/*========================================================================================
	Implementation Group
========================================================================================*/
int GFX_M19_InitHW(void)
{
	CPC_InitClk();
	return RET_OK;
}

int	GFX_M19_ShutdownHW(void)
{
	return RET_OK;
}

void	GFX_M19_InitScaler(void)
{

}

int GFX_M19_RunFlushCommand(void)
{
	return RET_OK;
}

int GFX_M19_RunStartCommand(void)
{
	return RET_OK;
}

int GFX_M19_PauseCommand(void)
{
	return RET_OK;
}

int GFX_M19_ResumeCommand(void)
{
	return RET_OK;
}

int GFX_M19_SwResetCommand(void)
{
	return RET_OK;
}

int GFX_M19_StopCommand(void)
{
	return RET_OK;
}

void GFX_M19_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue)
{
	queue->status[0] = 0;
	queue->status[1] = 0;
	queue->status[2] = 0;
}

BOOLEAN GFX_M19_IsGfxIdle(void)
{
	return TRUE;
}

void GFX_M19_GetOperationStatus(GFX_CMD_OP_T *operate)
{

}

void GFX_M19_SetOperationStatus(GFX_CMD_OP_T *operate)
{

}

void GFX_M19_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port)
{

}

void GFX_M19_SetInputConfigure(GFX_PORT_CONFIGURE_T *port)
{

}

void GFX_M19_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{

}

void GFX_M19_SetBlendingOut(GFX_ENUM_OUT_T type)
{

}

void GFX_M19_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{

}

void GFX_M19_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{

}

void GFX_M19_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{

}

void GFX_M19_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler)
{

}

void GFX_M19_SetInterruptMode(UINT32 uiMode)
{
	/* do nothing */
}

/* what is it ? */
void GFX_M19_SetAckMode(UINT32 *mode)
{

}

/* what is it ? */
void GFX_M19_GetAckMode(UINT32 *mode)
{
	*mode = 0;
}

int GFX_M19_SetCLUT(int port, int size , UINT32 *data)
{
	return RET_OK;
}

void GFX_M19_SetCommandDelayReg(UINT16 delay)
{

}

UINT16 GFX_M19_GetCommandDelayReg(void)
{
	return 0x0;
}

void GFX_M19_DumpRegister(void)
{

}

int GFX_M19_RunSuspend(void)
{
	return RET_OK;
}

int GFX_M19_RunResume(void)
{
	CPC_InitClk();
	return RET_OK;
}

int GFX_M19_ClkCheck(void)
{
	return TRUE;
}

int GFX_M19_RunClkOffCommand(void)
{
	return RET_OK;
}

int GFX_M19_RunClkOnCommand(void)
{
	return RET_OK;
}

/** @} */

