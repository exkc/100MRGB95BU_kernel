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
**  Name:DBB_DEMOD_L0_Connection.c
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

#define DEMOD_TAG "[L0] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L0_API.h"
#include "DBB_DEMOD_L0_Regmap.h"

#include "DBB_DEMOD_L0_CBUF.h"

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#pragma message ("demod platform for xtensa mcu")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)

#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
#endif

#include "demod_impl.h"
static DEFINE_SPINLOCK(spinlock);

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#pragma message ("demod platform for win32 GUI")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sysinfoapi.h>
#include <LG_IIC_Interface.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#pragma message ("demod platform for ext demod (tu)")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tu_ext_drivers.h"
#endif

//#define DEBUG_MUTEX

int DEMOD_L0_MUTEX_LOCK(char * name, MUTEX_LOCK_T * mutex)
{
	int retry = 10;
	int ret = RET_OK;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64 start_clock;
	UINT64 spend_clock;
	UINT32 spend_us;
	UINT32 spend_ms;
	
	start_clock = DEMOD_L0_SystemClock();
#endif

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - try lock %s, tid %lu, prv %lu(%d) try\n", name, GetCurrentThreadId(), mutex->tid, mutex->cnt);
#endif

	do {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		ret = OS_LockMutex(&mutex->mtx);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		//while(!mutex->mtx->Lock()) {
		//	DEMOD_L0_system_wait(1);
		//}
		while (!TryEnterCriticalSection(mutex->mtx)) {
			DEMOD_L0_system_wait(1);
		}

		if (mutex->cnt > 0) {
			DEMOD_WARN("%s: %s lock duplicated, cur tid %lu, prv tid %lu, cnt %d\n", __FUNCTION__, name, GetCurrentThreadId(), mutex->tid, mutex->cnt);
		}

		mutex->tid = GetCurrentThreadId();
		mutex->cnt++;
		ret = RET_OK;

		//pthread_mutex_lock(&chip->mutex);
		//ret = RET_OK;
#else
		ret = RET_OK;
#endif
	} while ((ret != RET_OK) && retry--);

	if (ret != RET_OK) {
#if defined(DEMOD_SPEND_TIME_CHECK)
		spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
		DEMOD_ERROR("failed OS_LockMutex with %d, spend %3u.%03ums, retry %d\n", ret, spend_ms, spend_us, retry);
#else
		DEMOD_ERROR("failed OS_LockMutex with %d, retry %d\n", ret, retry);
#endif
		return ret;
	}

//	DEMOD_INFO("OS_LockMutex with %d, spend %u, retry %d\n", ret, spend_time, retry);
#if defined(DEBUG_MUTEX)
#if defined(DEMOD_SPEND_TIME_CHECK)
	DEMOD_INFO("\t\t\t\t - locked %s, tid %lu(%d), spend %u.%ums\n", name, mutex->tid, mutex->cnt, spend_ms, spend_us);
#else
	DEMOD_INFO("\t\t\t\t - locked %s, tid %lu(%d)\n", name, mutex->tid, mutex->cnt);
#endif
#endif
	return ret;
}

int DEMOD_L0_MUTEX_UNLOCK (char * name, MUTEX_LOCK_T * mutex)
{
	int ret = 0;

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - try unlock %s, tid %lu, prv %lu(%d) try\n", name, GetCurrentThreadId(), mutex->tid, mutex->cnt);
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	OS_UnlockMutex(&mutex->mtx);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)

	mutex->cnt--;
	if (mutex->cnt > 0) {
		DEMOD_WARN("%s: %s lock count invalid, cur tid %lu, prv tid %lu, cnt %d\n", __FUNCTION__, name, GetCurrentThreadId(), mutex->tid, mutex->cnt);
	}
	mutex->tid = 0;
	//while(!mutex->mtx->Unlock()) {
	//	DEMOD_L0_system_wait(1);
	//}
	LeaveCriticalSection(mutex->mtx);
	
	//pthread_mutex_unlock(&chip->mutex);
#else
#endif
	
#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - unlocked %s, cur tid %lu, count (%d) try\n", name, GetCurrentThreadId(), mutex->cnt);
#endif
	return ret;
}

//static MUTEX_LOCK_T _mutex_demod;
/** lock demod device */

int DEMOD_L0_LockDevice (LX_DEMOD_L0_Context* chip)
{
	return DEMOD_L0_MUTEX_LOCK("demod", &chip->mutex_lock);
}

/** unlock demod device */
int DEMOD_L0_UnlockDevice (LX_DEMOD_L0_Context* chip)
{
	return DEMOD_L0_MUTEX_UNLOCK("demod", &chip->mutex_lock);
}

#if (DEMOD_COMM == DEMOD_COMM_FPGA)
static MUTEX_LOCK_T _mutex_comm;

int DEMOD_L0_Lock_CommDevice(LX_DEMOD_L0_Context* chip)
{
	return DEMOD_L0_MUTEX_LOCK("comm", &_mutex_comm);
}

int DEMOD_L0_Unlock_CommDevice(LX_DEMOD_L0_Context* chip)
{
	return DEMOD_L0_MUTEX_UNLOCK("comm", &_mutex_comm);
}
#else
int DEMOD_L0_Lock_CommDevice(LX_DEMOD_L0_Context* chip)
{
	return NO_DEMOD_ERROR;
}

int DEMOD_L0_Unlock_CommDevice(LX_DEMOD_L0_Context* chip)
{
	return NO_DEMOD_ERROR;
}
#endif

int DEMOD_L0_InitDevice (LX_DEMOD_L0_Context* chip)
{
	
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	OS_InitMutex(&chip->mutex_lock.mtx, OS_SEM_ATTR_DEFAULT);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	//chip->mutex_lock.mtx = new CMutex(FALSE, "demod");
	chip->mutex_lock.mtx = new CRITICAL_SECTION();
	InitializeCriticalSection(chip->mutex_lock.mtx);
	chip->mutex_lock.cnt = 0;
	chip->mutex_lock.tid = 0;

#if (DEMOD_COMM == DEMOD_COMM_FPGA)
	//_mutex_comm.mtx = new CMutex(FALSE, "comm");
	_mutex_comm.mtx = new CRITICAL_SECTION();
	InitializeCriticalSection(_mutex_comm.mtx);
	_mutex_comm.cnt = 0;
	_mutex_comm.tid = 0;
#endif
//	pthread_mutex_init(&chip->mutex, NULL);
#else
#endif
	
	return NO_DEMOD_ERROR;
}

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#define dump_stack
#endif

#ifdef    __cplusplus
extern "C" {
#endif /* __cplusplus */

/************************************************************************************************************************
  NAME: DEMOD_L0_system_wait
  DESCRIPTION:	Delay for time_ms (milliseconds)
  Parameter:  time in milliseconds
  Porting:		Replace with embedded system delay function
  Returns:		nothing
************************************************************************************************************************/
UINT32 DEMOD_L0_system_wait (int wait_ms)
{
	// add a delay of time_ms based on you embedded system delay
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	usleep_range(wait_ms*1000,(wait_ms+1)*1000);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	Sleep(wait_ms);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
	// for external demod in LG DTV platform.
	return (UINT32)TU_DELAY_MS(wait_ms);
#else
#endif

	return NO_DEMOD_ERROR;
}

/************************************************************************************************************************
  DEMOD_L0_system_time function
  Use:        current system time retrieval function
              Used to retrieve the current system time in milliseconds
  Returns:    The current system time in milliseconds
  Porting:    Needs to use the final system call
************************************************************************************************************************/

UINT32 DEMOD_L0_system_time (void)
{
	UINT32 sysTime = 0;
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	sysTime = (UINT32)jiffies_to_msecs(jiffies);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	LARGE_INTEGER curtime;
	QueryPerformanceCounter(&curtime);

	sysTime =  curtime.QuadPart / (freq.QuadPart / 1000000);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
	// for external demod in LG DTV platform.
	sysTime = (UINT32)TU_CURRENT_TIME();
#else
#endif

	return sysTime;
}

UINT32 DEMOD_L0_CalcSpendTime(UINT32 start_time) {
	UINT32 current_time = DEMOD_L0_system_time();
	UINT32 spend_time = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	if (current_time >= start_time) {
		spend_time = current_time - start_time;
	} else {
		spend_time = current_time + (UINT_MAX - start_time);
	}

	DEMOD_DEBUG("start %u, current %u, spend %u, UINT_MAX %u, jf %lu, %llu, ct %u\n", start_time, current_time, spend_time, UINT_MAX, jiffies, get_jiffies_64(), DEMOD_L0_SystemClock());
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	if (current_time >= start_time) {
		spend_time = current_time - start_time;
	} else {
		spend_time = current_time + (UINT_MAX - start_time);
	}

	DEMOD_DEBUG("start %u, current %u, spend %u, UINT_MAX %u\n", start_time, current_time, spend_time, UINT_MAX);
#endif
	return spend_time;
}

UINT64 DEMOD_L0_SystemClock (void)
{
	UINT64 clockTime = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	clockTime = sched_clock();
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	LARGE_INTEGER curtime;
	QueryPerformanceCounter(&curtime);
	clockTime = curtime.QuadPart;
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
	// for external demod in LG DTV platform.
	clockTime = TU_CURRENT_TIME();
#else
#endif

	return clockTime;
}

UINT64 DEMOD_L0_CalcSpendClockfrom(UINT64 start_clock, UINT64 current_clock, UINT32 *pspend_ms, UINT32 *pspend_us) {
	UINT64 spend_clock = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	if (current_clock >= start_clock) {
		spend_clock = current_clock - start_clock;
	} else {
		spend_clock = current_clock + (U64_MAX - start_clock);
	}

	if (pspend_ms != NULL && pspend_us != NULL) {
		*pspend_ms = div_u64_rem(spend_clock, 1000000, pspend_us);
		*pspend_us /= 1000;
	}
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	if (current_clock >= start_clock) {
		spend_clock = current_clock - start_clock;
	} else {
		spend_clock = current_clock + (ULLONG_MAX - start_clock);
	}
	spend_clock = spend_clock / (freq.QuadPart / 1000000);

	if (pspend_ms != NULL && pspend_us != NULL) {
		*pspend_ms = spend_clock / 1000;
		*pspend_us = spend_clock % 1000;
	}
#endif

	DEMOD_DEBUG("start %u, current %u, spend %u, UINT_MAX %u, jf %lu, %llu, ct %u\n", start_time, current_time, spend_time, UINT_MAX, jiffies, get_jiffies_64(), DEMOD_L0_SystemClock());
	return spend_clock;
}

UINT64 DEMOD_L0_CalcSpendClock(UINT64 start_clock, UINT32 *pspend_ms, UINT32 *pspend_us) {
	UINT64 current_clock = DEMOD_L0_SystemClock();
	UINT64 spend_clock = 0;

	spend_clock = DEMOD_L0_CalcSpendClockfrom(start_clock, current_clock, pspend_ms, pspend_us);
	return spend_clock;
}


/************************************************************************************************************************
  DEMOD_L0_Init function
  Use:        layer 0 initialization function
              Used to set the layer 0 context parameters to startup values.
              It must be called first and once per Layer 1 instance (i.e. once for the tuner and once for the demodulator).
              It is automatically called by the Layer 1 init function.
  Parameters: mustReadWithoutStop has been added to manage the case when some components do not allow a stop in a 'read'.
              i2c usually allows 'write 0xc8 0x01 0x02' followed by 'read 0xc9 1' to read the UINT8 at index 0x0102.
              This should return the same data as 'read 0xc8 0x01 0x02 1'.
              If this is not allowed, set mustReadWithoutStop at 1.
              NB: at the date of writing, this behavior has only been detected in the RDA5812 satellite tuner.
  Returns:    void
  Porting:    If some members of the LX_DEMOD_L0_Context structure are removed, they need to be removed from here too
************************************************************************************************************************/
int DEMOD_L0_Init (LX_DEMOD_L0_Context* chip)
{
	(chip)->i2c_slv_addr	= 0;
	(chip)->i2c_idx_size	= 0;

	(chip)->fw_done		= 0;
	(chip)->fw_type		= 0;
	(chip)->chip_if		= 0;
	(chip)->chip_ver	= 0;
	(chip)->chip_rev	= 0;

	return NO_DEMOD_ERROR;
}

/************************************************************************************************************************
  DEMOD_L0_SetAddress function
  Use:        function to set the device address
              Used to set the I2C address of the component.
              It must be called only once at startup per Layer 1 instance, as the addresses are not expected to change over time.
  Returns:    1 if OK, 0 otherwise
************************************************************************************************************************/
int DEMOD_L0_SetAddress (LX_DEMOD_L0_Context* chip, UINT32 add, UINT8 addSize)
{
 	(chip)->i2c_slv_addr   	= (UINT8)add;
  	(chip)->i2c_idx_size	= addSize;

	return NO_DEMOD_ERROR;
}

/************************************************************************************************************************
  DEMOD_I2C_Read function
  Use:        lowest layer read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: chip, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first UINT8 to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c read function
************************************************************************************************************************/
int DEMOD_L0_I2C_Read (LX_DEMOD_L0_Context*  chip, UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
	int ret = 0;

	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	ret = DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer);
	if (ret != RET_OK) {
		DEMOD_PRINT("[API,L0] DEMOD_I2C_Read - retry with %u\n", ret);
		ret = DEMOD_I2C_Read(Addr, iNbBytes, pucDataBuffer);
		if (ret != RET_OK) {
			DEMOD_ERROR("[API,L0] DEMOD_I2C_Read - fail with %u\n", ret);
			return -ERROR_DEMOD_READ;
		}
	}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	ret = LG_IIC_ReadType2HS((chip->i2c_slv_addr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);
    return (ret == iNbBytes ? NO_DEMOD_ERROR : ERROR_DEMOD_READ);
	//return NO_DEMOD_ERROR;

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
	// for external demod in LG DTV platform.
	if (TU_RET_OK != TU_I2C_Read(chip->i2c_handle, chip->i2c_idx_size, subAddr, iNbBytes, pucDataBuffer)) {
		TU_PRINT(PRN_CRI, "[API,L0] FAIL, TU_I2C_Read H[0x%0x] - retry !!!\n", chip->i2c_handle);

		if (TU_RET_OK != TU_I2C_Read(chip->i2c_handle, chip->i2c_idx_size, subAddr, iNbBytes, pucDataBuffer)) {
	  		TU_PRINT(PRN_CRI, "[API,L0] FAIL, TU_I2C_Read H[0x%0x] !!!\n", chip->i2c_handle);
			return -ERROR_DEMOD_READ;
		}
	}
#endif

	return  NO_DEMOD_ERROR;
}

void DEMOD_L0_WordToByte (UINT32 wordData, UINT8 *wrData)
{
	wrData[0] = wordData 		 & 0xff;
	wrData[1] = (wordData >> 8   ) & 0xff;
	wrData[2] = (wordData >> 16 ) & 0xff;
	wrData[3] = (wordData >> 24 ) & 0xff;
}

/************************************************************************************************************************
  DEMOD_I2C_Write function
  Use:        lowest layer write function
              Used to write a given number of bytes from the Layer 1 instance.
  Parameters: chip, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first UINT8 to write.
              iNbBytes, the number of bytes to write.
              *pbtDataBuffer, a pointer to a buffer containing the bytes to write.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c write function
************************************************************************************************************************/
int DEMOD_L0_I2C_Write (LX_DEMOD_L0_Context* chip,  UINT16 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	UINT8 subAddr[2];
	int ret = 0;

	subAddr[0] = (UINT8)((Addr >> 8) & 0xFF);
	subAddr[1] = (UINT8)(Addr & 0xFF);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	ret = DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer);
	if (ret != RET_OK) {
		DEMOD_PRINT("[API,L0] DEMOD_I2C_Write - retry with %u\n", ret);
		ret = DEMOD_I2C_Write(Addr, iNbBytes, pucDataBuffer);
		if (ret != RET_OK) {
			DEMOD_ERROR("[API,L0] DEMOD_I2C_Write - fail with %u\n", ret);
			return -ERROR_DEMOD_READ;
		}
	}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	ret = LG_IIC_WriteType2HS((chip->i2c_slv_addr)>>1, subAddr[0], subAddr[1], iNbBytes, pucDataBuffer);
	return (ret == TRUE ? NO_DEMOD_ERROR : ERROR_DEMOD_WRITE);
	//return NO_DEMOD_ERROR;

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
	// for external demod in LG DTV platform.
	if (TU_RET_OK != TU_I2C_Write(chip->i2c_handle, chip->i2c_idx_size, subAddr,  iNbBytes, pucDataBuffer)) {
		TU_PRINT(PRN_CRI, "[API,L0] FAIL, TU_I2C_Write H[0x%0x] - retry !!!\n", chip->i2c_handle);

		if (TU_RET_OK != TU_I2C_Write(chip->i2c_handle, chip->i2c_idx_size, subAddr, iNbBytes, pucDataBuffer)) {
			TU_PRINT(PRN_CRI, "[API,L0] FAIL, TU_I2C_Write H[0x%0x] !!!\n", chip->i2c_handle);
			return -ERROR_DEMOD_WRITE;
		}
	}
#endif

	return NO_DEMOD_ERROR;
}

/************************************************************************************************************************
  DEMOD_L0_ReadCommandBytes function
  Use:        'command mode' bytes reading function
              Used to read a given number of bytes from the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the i2c_idx_size is always 0 and the index is always 0x00
  Parameters: chip, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to read.
              *pucDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
************************************************************************************************************************/
int DEMOD_L0_ReadCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;

	int alen = (iNbBytes + 3) & ~0x3;
	int i;

#if (DEMOD_COMM == DEMOD_COMM_APB)
	/* APB access */
	unsigned long flags;

	UINT32 word = 0;
	UINT32 addr = 0;

	if (Addr >= 0xf000) 
	{
		DEMOD_WARN("[API,L0] have to fix req addr %04x -> %04X\n", Addr, (Addr - 0x9c00));
		Addr = Addr - 0x9c00;
	}

	if (Addr < 0x5300 || Addr > 0x54FF) {
		DEMOD_ERROR("[API,L0] invalid Addr 0x%04X\n", Addr);
		dump_stack();
		return ERROR_DEMOD_INVALID;
	}

	spin_lock_irqsave(&spinlock, flags);
	for (i = 0; i < alen; i += 4) {
		addr = (Addr + i) - 0x5300;

		if (addr > 0x200) {
			DEMOD_ERROR("[API,L0] invalid addr 0x%04X\n", addr);
			dump_stack();
			spin_unlock_irqrestore(&spinlock, flags);
			return ERROR_DEMOD_INVALID;
		}

		err = DEMOD_APB_Read(addr, &word);

		if (err != NO_DEMOD_ERROR) {
			DEMOD_ERROR("[API,L0] failed read Addr 0x%04x, i 0x%02x => 0x%04x => 0x%04x\n", Addr, i, Addr + i, addr);
			break;
		} else if ((i + 4) <= iNbBytes) {
			memcpy(pucDataBuffer + i, &word, 4);
		} else {
			memcpy(pucDataBuffer + i, &word, (i + 4) - iNbBytes);
		}
	}
	spin_unlock_irqrestore(&spinlock, flags);

#elif (DEMOD_COMM == DEMOD_COMM_FPGA)
	/* I2C access */
	UINT8 Addr_Msb, Addr_Lsb;
	UINT16 i2cAddr;

	if ((chip->fw_done == 1) && (Addr >= 0xf000)) 	{
		Addr = Addr - 0x9c00;
	}

	i2cAddr = Addr;

	Addr_Msb = ((i2cAddr >> 10) & 0x3f) | (chip->i2c_indirect << 6);
	Addr_Lsb = ((i2cAddr >> 2) & 0xff);

	i2cAddr = ((Addr_Msb << 8) | Addr_Lsb);

	//DEMOD_INFO("[API,L0] %lu, req addr 0x%08x, len %d, msb %02x, lsb %02x, result addr 0x%08x, len %d\n",
		//GetCurrentThreadId(), Addr, iNbBytes, Addr_Msb, Addr_Lsb, i2cAddr, alen);

	for (i = 0; i < (alen >> 2); i++) {
		//err = DEMOD_L0_I2C_Read (chip, i2cAddr + i, 4, (UINT8 *)pucDataBuffer + (i << 2));
		err |= DEMOD_L0_I2C_Read (chip, i2cAddr + i, 4, (UINT8 *)pucDataBuffer + (i << 2));
	}

	//err = DEMOD_L0_I2C_Read (chip, i2cAddr, alen, (UINT8 *)pucDataBuffer);
	
	if (err != NO_DEMOD_ERROR)
		DEMOD_ERROR("[API,L0] %lu, failed I2C_Read Addr 0x%04x, i2c Addr 0x%04x\n", GetCurrentThreadId(), Addr, i2cAddr);

#elif (DEMOD_COMM == DEMOD_COMM_I2C)
	/* I2C access */
	UINT8 Addr_Msb, Addr_Lsb;
	UINT16 i2cAddr;

	if ((chip->fw_done == 1) && (Addr >= 0xf000)) 	{
		Addr = Addr - 0x9c00;
	}

	i2cAddr = Addr;
	if (Addr >= 0x5300 && Addr < 0x5500) {
		i2cAddr = Addr - 0x5300;
	}

	Addr_Msb = ((i2cAddr >> 10) & 0x3f) | (chip->i2c_indirect << 6);
	Addr_Lsb = ((i2cAddr >> 2) & 0xff);

	i2cAddr = ((Addr_Msb << 8) | Addr_Lsb);

	DEMOD_DEBUG("[API,L0] req addr 0x%08x, len %d, msb %02x, lsb %02x, result addr 0x%08x, len %d\n",
		Addr, iNbBytes, Addr_Msb, Addr_Lsb, i2cAddr, alen);

	err = DEMOD_L0_I2C_Read (chip, i2cAddr, alen, (UINT8 *)pucDataBuffer);
	if (err != NO_DEMOD_ERROR)
		DEMOD_ERROR("[API,L0] failed I2C_Read Addr 0x%04x, i2c Addr 0x%04x\n", Addr, i2cAddr);
#else
	DEMOD_ERROR("DEMOD_COMM is not defined");
#endif

	return err;
}

int DEMOD_L0_ReadCommandBytes (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;

	DEMOD_L0_Lock_CommDevice(chip);
	err = DEMOD_L0_ReadCommandBytes_NoLock(chip, Addr, iNbBytes, pucDataBuffer);
	DEMOD_L0_Unlock_CommDevice(chip);

	return err;
}

/************************************************************************************************************************
  DEMOD_L0_WriteCommandBytes function
  Use:        'command mode' bytes writing function
              Used to write a given number of bytes to the Layer 1 instance in 'command mode'.
  Comment:    The 'command mode' is a specific mode where the i2c_idx_size is always 0 and the index is always 0x00
  Parameters: comm, a pointer to the Layer 0 context.
              iNbBytes, the number of bytes to write.
              *pucDataBuffer, a pointer to a buffer containing the bytes.
  Returns:    the number of bytes written.
************************************************************************************************************************/
int DEMOD_L0_WriteCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;
	int alen = (iNbBytes + 3) & ~0x3;

#if (DEMOD_COMM == DEMOD_COMM_APB)
	/* APB access */
	unsigned long flags;
	int i;

	UINT32 addr = 0;

	if (Addr >= 0xf000) {
		DEMOD_WARN("[API,L0] have to fix req addr %04x -> %04X\n", Addr, (Addr - 0x9c00));
		Addr = Addr - 0x9c00;
	}

	if (Addr < 0x5300 || Addr > 0x54FF) {
		DEMOD_ERROR("[API,L0] invalid Addr 0x%04X\n", Addr);
		dump_stack();
		return ERROR_DEMOD_INVALID;
	}

	spin_lock_irqsave(&spinlock, flags);
	for (i = 0; i < alen; i += 4)
	{
		addr = (Addr + i) - 0x5300;

		if (addr > 0x200) {
			DEMOD_ERROR("[API,L0] invalid addr 0x%04X\n", addr);
			dump_stack();
			spin_unlock_irqrestore(&spinlock, flags);
			return ERROR_DEMOD_INVALID;
		}

		err = DEMOD_APB_Write(addr, (UINT32 *)(pucDataBuffer + i));
		if (err != NO_DEMOD_ERROR) {
			DEMOD_ERROR("[API,L0] failed write Addr 0x%04x, i 0x%02x => 0x%04x => 0x%04x\n", Addr, i, Addr + i, addr);
			break;
		}
	}
	spin_unlock_irqrestore(&spinlock, flags);
#elif (DEMOD_COMM == DEMOD_COMM_FPGA)
	/* I2C access */
	UINT8 Addr_Msb, Addr_Lsb;
	UINT16 i2cAddr;

	if ((chip->fw_done == 1) && (Addr >= 0xf000)) 	{
		Addr = Addr - 0x9c00;
	}

	i2cAddr = Addr;

	Addr_Msb = (((i2cAddr >> 10) & 0x3f) | (chip->i2c_indirect << 6));
	Addr_Lsb = (i2cAddr >> 2);

	i2cAddr = ((Addr_Msb << 8) | Addr_Lsb);

	err = DEMOD_L0_I2C_Write (chip, i2cAddr, alen, (UINT8 *)pucDataBuffer);

	if (err != NO_DEMOD_ERROR)
		DEMOD_ERROR("[API,L0] %lu, failed L0_I2C_Write Addr 0x%04x, i2c Addr 0x%04x\n", GetCurrentThreadId(), Addr, i2cAddr);

#elif (DEMOD_COMM == DEMOD_COMM_I2C)
	/* I2C access */
	UINT8 Addr_Msb, Addr_Lsb;
	UINT16 i2cAddr;

	if ((chip->fw_done == 1) && (Addr >= 0xf000)) 	{
		Addr = Addr - 0x9c00;
	}

/*
	i2cAddr = Addr - 0x5300;

	Addr_Msb = ((i2cAddr >> 10) & 0x3f) | (chip->i2c_indirect << 6);
	Addr_Lsb = ((i2cAddr >> 2) & 0xff);
*/
	Addr_Msb = (((Addr >> 10) & 0x3f) | (chip->i2c_indirect << 6));
	Addr_Lsb = (Addr >> 2);

	i2cAddr = ((Addr_Msb << 8) | Addr_Lsb);


	DEMOD_DEBUG("[API,L0] req addr 0x%08x, len %d, msb %02x, lsb %02x, result addr 0x%08x, len %d\n",
		Addr, iNbBytes, Addr_Msb, Addr_Lsb, i2cAddr, alen);

/*
	err = DEMOD_L0_I2C_Write (chip, i2cAddr, alen, (UINT8 *)pucDataBuffer);
	if (err != NO_DEMOD_ERROR)
		DEMOD_ERROR("[API,L0] failed L0_I2C_Write Addr 0x%04x, i2c Addr 0x%04x\n", Addr, i2cAddr);
*/
	return DEMOD_L0_I2C_Write(chip, i2cAddr, iNbBytes, (UINT8 *)pucDataBuffer);
#else
	DEMOD_ERROR("DEMOD_COMM is not defined");
#endif

	return err;
}

int DEMOD_L0_WriteCommandBytes (LX_DEMOD_L0_Context* chip, UINT16 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;

	DEMOD_L0_Lock_CommDevice(chip);
	err = DEMOD_L0_WriteCommandBytes_NoLock(chip, Addr, iNbBytes, pucDataBuffer);
	DEMOD_L0_Unlock_CommDevice(chip);
	return err;
}

#ifdef    __cplusplus
}
#endif /* __cplusplus */

