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
 *  author      hwanwook.lee@lge.com
 *  version     1.0
 *  date
 *  note        Additional information.
 *
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
int GFX_E60_InitHW(void)
{
	CPC_InitClk();
	return RET_OK;
}

int	GFX_E60_ShutdownHW(void)
{
	return RET_OK;
}

void	GFX_E60_InitScaler(void)
{

}

int GFX_E60_RunFlushCommand(void)
{
	return RET_OK;
}

int GFX_E60_RunStartCommand(void)
{
	return RET_OK;
}

int GFX_E60_PauseCommand(void)
{
	return RET_OK;
}

int GFX_E60_ResumeCommand(void)
{
	return RET_OK;
}

int GFX_E60_SwResetCommand(void)
{
	return RET_OK;
}

int GFX_E60_StopCommand(void)
{
	return RET_OK;
}

void GFX_E60_GetComQueueStatus(GFX_CMD_QUEUE_CTRL_T *queue)
{
	queue->status[0] = 0;
	queue->status[1] = 0;
	queue->status[2] = 0;
}

BOOLEAN GFX_E60_IsGfxIdle(void)
{
	return TRUE;
}

void GFX_E60_GetOperationStatus(GFX_CMD_OP_T *operate)
{

}

void GFX_E60_SetOperationStatus(GFX_CMD_OP_T *operate)
{

}

void GFX_E60_GetInputConfigure(int iPort, GFX_PORT_CONFIGURE_T *port)
{

}

void GFX_E60_SetInputConfigure(GFX_PORT_CONFIGURE_T *port)
{

}

void GFX_E60_GetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{

}

void GFX_E60_SetBlendingOut(GFX_ENUM_OUT_T type)
{

}

void GFX_E60_SetBlendConfigure( GFX_BLEND_CONFIGURE_T *blend)
{

}

void GFX_E60_GetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{

}

void GFX_E60_SetOutputConfigure(GFX_OUT_CONFIGURE_T *port)
{

}

void GFX_E60_SetScalerConfigure(GFX_SCALER_CONFIGURE_T* scaler)
{

}

void GFX_E60_SetInterruptMode(UINT32 uiMode)
{
	/* do nothing */
}

/* what is it ? */
void GFX_E60_SetAckMode(UINT32 *mode)
{

}

/* what is it ? */
void GFX_E60_GetAckMode(UINT32 *mode)
{
	*mode = 0;
}

int GFX_E60_SetCLUT(int port, int size , UINT32 *data)
{
	return RET_OK;
}

void GFX_E60_SetCommandDelayReg(UINT16 delay)
{

}

UINT16 GFX_E60_GetCommandDelayReg(void)
{
	return 0x0;
}

void GFX_E60_DumpRegister(void)
{

}

int GFX_E60_RunSuspend(void)
{
	return RET_OK;
}

int GFX_E60_RunResume(void)
{
	CPC_InitClk();
	return RET_OK;
}

int GFX_E60_ClkCheck(void)
{
	return TRUE;
}

int GFX_E60_RunClkOffCommand(void)
{
	return RET_OK;
}

int GFX_E60_RunClkOnCommand(void)
{
	return RET_OK;
}

/** @} */

