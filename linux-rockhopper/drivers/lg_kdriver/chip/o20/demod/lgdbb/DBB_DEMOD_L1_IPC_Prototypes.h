/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013-2019 by LG Electronics Inc.
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


/*  @file
 *
 *	demod mcu ipc
 *
 *	@author 	samin.ryu
 *	@version	1.1
 *	@date		2019-05-28
 *	@note		modified for LGDBB
 */

#ifndef __DBB_DEMOD_L1_IPC_PROTO__
#define __DBB_DEMOD_L1_IPC_PROTO__

int DEMOD_L1_IPC_Send (LX_DEMOD_L1_Context * core, UINT32 typ, UINT32 seq, char *ptr, int len);
int DEMOD_L1_IPC_Send_Count (LX_DEMOD_L1_Context * core);

int DEMOD_L1_IPC_Send_GetState(LX_DEMOD_L1_Context * core, int * pstate);
int DEMOD_L1_IPC_Send_GetDebug(LX_DEMOD_L1_Context * core, UINT32 * pdebug);

int DEMOD_L1_IPC_Recv (LX_DEMOD_L1_Context * core, UINT32 *ptyp,  UINT32 *pseq, char *pdst);
int DEMOD_L1_IPC_Recv_Count (LX_DEMOD_L1_Context * core);

int DEMOD_L1_IPC_Recv_GetState(LX_DEMOD_L1_Context * core, UINT32 * pstate);
int DEMOD_L1_IPC_Recv_GetDebug(LX_DEMOD_L1_Context * core, UINT32 * pdebug);

int DEMOD_L1_IPC_Wait (LX_DEMOD_L1_Context * core, int retry);	// if retry == 0, max wait time is 100ms
int DEMOD_L1_IPC_Wait_Cancel(LX_DEMOD_L1_Context * core);

int DEMOD_L1_IPC_Reset (LX_DEMOD_L1_Context * core);
int DEMOD_L1_IPC_Enable (LX_DEMOD_L1_Context * core, int enable);
int DEMOD_L1_IPC_Clear (LX_DEMOD_L1_Context * core);

int DEMOD_L1_IPC_Handler (LX_DEMOD_L1_Context * core);

int DEMOD_L1_IPC_Status_Fifo(LX_DEMOD_L1_Context * core, char * dbglog);
int DEMOD_L1_IPC_Status (LX_DEMOD_L1_Context * core, char * dbglog);
int DEMOD_L1_IPC_Dump (LX_DEMOD_L1_Context * core, char * dbglog);

int DEMOD_L1_IPC_Init (LX_DEMOD_L1_Context * core);

#endif //__DBB_DEMOD_L1_IPC_PROTO__

