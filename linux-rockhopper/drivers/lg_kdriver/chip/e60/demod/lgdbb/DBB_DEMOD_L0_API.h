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

/*****************************************************************************
**
**  Name:DBB_DEMOD_L0_API.h
**
**  Description:    .
**
**  Functions
**  Implemented:
**
**  References:
**
**  Exports:
**
**  Dependencies:
**
**
**  Revision History:
**
**     Date        Author          Description
**  -------------------------------------------------------------------------
**   20-01-2016  Jeongpil Yun    Initial draft.
**
*****************************************************************************/

#ifndef _DBB_DEMOD_L0_API_H_
#define _DBB_DEMOD_L0_API_H_

#include <DBB_DEMOD_typedefs.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
typedef char mutex_t;
typedef int tid_t;
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
typedef OS_SEM_T mutex_t;
typedef long tid_t;
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <afxmt.h>

typedef CRITICAL_SECTION * mutex_t;
typedef DWORD tid_t;
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
typedef char mutex_t;
typedef int tid_t;
#endif

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef struct _system_lock_t {
	mutex_t mtx;
	int cnt;		// lock count
	tid_t tid;		// lock thread id
} MUTEX_LOCK_T;

typedef enum {
	LX_DEMOD_L0_IF_SOC	= 0,
	LX_DEMOD_L0_IF_EXT	= 1,
} LX_DEMOD_L0_IF;

typedef struct LX_DEMOD_L0_Context
{
	/* mutual context */
	MUTEX_LOCK_T mutex_lock;

	/* i2c parameter */
	UINT8	i2c_slv_addr;
	UINT8	i2c_idx_size;
	UINT8	i2c_indirect;
	UINT32  i2c_handle;

	UINT8	fw_type:2;	/* 0: INV, 1: TER, 2: SAT, 3: DDR */
	UINT8	fw_skip:1;	/* 1: FW load skip */
	UINT8	fw_done:1;

	UINT8	chip_if:1;	/* 0: SOC(APB), 1: EXT(I2C) */
	UINT8 	chip_ver;
	UINT8 	chip_rev;
} LX_DEMOD_L0_Context;

UINT32 DEMOD_L0_system_wait (int time_ms);

UINT32 DEMOD_L0_system_time (void);
UINT32 DEMOD_L0_CalcSpendTime(UINT32 start_time);

UINT64 DEMOD_L0_SystemClock (void);
UINT64 DEMOD_L0_CalcSpendClock(UINT64 start_clock, UINT32 *pspend_ms, UINT32 *pspend_us);
UINT64 DEMOD_L0_CalcSpendClockfrom(UINT64 start_clock, UINT64 current_clock, UINT32 *pspend_ms, UINT32 *pspend_us);

int DEMOD_L0_MUTEX_LOCK(char * name, MUTEX_LOCK_T * mutex);
int DEMOD_L0_MUTEX_UNLOCK(char * name, MUTEX_LOCK_T * mutex);
int DEMOD_L0_LockDevice (LX_DEMOD_L0_Context* chip);
int DEMOD_L0_UnlockDevice (LX_DEMOD_L0_Context* chip);
int DEMOD_L0_InitDevice (LX_DEMOD_L0_Context* chip);
int DEMOD_L0_Lock_CommDevice(LX_DEMOD_L0_Context* chip);
int DEMOD_L0_Unlock_CommDevice(LX_DEMOD_L0_Context* chip);

int DEMOD_L0_Init (LX_DEMOD_L0_Context* chip); /* initialize the Layer 0 DLL. It sets the layer 0 context parameters to startup values. It must be called first. It is automatically called by the Layer 1 init function.*/
int DEMOD_L0_SetAddress (LX_DEMOD_L0_Context* chip, UINT32 add, UINT8 addSize) ;

int DEMOD_L0_I2C_Read (LX_DEMOD_L0_Context*  chip, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);
int DEMOD_L0_I2C_Write (LX_DEMOD_L0_Context* chip,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);

int DEMOD_L0_ReadCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void *pucDataBuffer);
int DEMOD_L0_ReadCommandBytes (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void *pucDataBuffer);
int DEMOD_L0_WriteCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void *pucDataBuffer);
int DEMOD_L0_WriteCommandBytes (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void *pucDataBuffer);

void DEMOD_L0_WordToByte (UINT32 wordData, UINT8 *wrData);

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _DBB_DEMOD_L0_API_H_*/

