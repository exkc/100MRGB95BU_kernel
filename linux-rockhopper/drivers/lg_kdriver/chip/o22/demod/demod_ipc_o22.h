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
 *	demod o20 ipc
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-05-28
 *	@note
 */

#ifndef __DEMOD_O22_IPC__
#define __DEMOD_O22_IPC__

#define DEMOD_FW_RECOVERY

int DEMOD_O22_IPC_Handler (void);

int DEMOD_O22_IPC_Send (UINT32 typ, UINT32 seq, char *ptr, UINT32 len);

int DEMOD_O22_IPC_Status(char * pDbglog, int * pDbgidx);
int DEMOD_O22_IPC_Dump(char * pDbglog, int * pDbgidx);

int DEMOD_O22_IPC_Reset (void);
int DEMOD_O22_IPC_Enable (int enable);

int DEMOD_O22_IPC_Init (void);

#endif //__DBB_DEMOD_L1_IPC__


