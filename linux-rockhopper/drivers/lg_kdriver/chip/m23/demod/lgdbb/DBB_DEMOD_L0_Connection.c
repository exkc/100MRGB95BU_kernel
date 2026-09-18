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

#include <DBB_DEMOD_L0_API.h>
#include <DBB_DEMOD_L0_Regmap.h>

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#pragma message ("demod platform for xtensa mcu")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dsa_fw.h>

#include <ipc/demod_mem.h>
#include <ipc/demod_debug.h>
#include <main_ipc.h>

#include <demod_main.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)

#include <linux/kthread.h>
#include <linux/delay.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
#include <linux/sched/clock.h>
#endif

#include "demod_impl.h"
#include <demod_util.h>

#if (DEMOD_COMM == DEMOD_COMM_APB)
#pragma message ("demod platform for kdrv + apb")

#include <linux/spinlock.h>
static DEFINE_SPINLOCK(spinlock);
#elif (DEMOD_COMM == DEMOD_COMM_FPGA)
#pragma message ("demod platform for kdrv + comm fpga")
#elif (DEMOD_COMM == DEMOD_COMM_I2C)
#pragma message ("demod platform for kdrv + comm i2c")
#elif (DEMOD_COMM == DEMOD_COMM_UNKNOWN)
#pragma message ("demod platform for kdrv + comm unknown")
#else
#pragma message ("demod platform for kdrv + comm not defined")
#endif

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#pragma message ("demod platform for win32 GUI")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sysinfoapi.h>
#include "LG_COMM.h"

#include <demod_util.h>
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#pragma message ("demod platform for ext demod (tu)")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tu_ext_drivers.h"
#include <demod_util.h>
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#define GET_TID()	(current->pid)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#define GET_TID()	(GetCurrentThreadId())
#else
#define GET_TID()	(0)
#endif

//#define DEBUG_MUTEX
#if defined(DEBUG_MUTEX) && !defined(DEMOD_SPEND_TIME_CHECK)
#define DEMOD_SPEND_TIME_CHECK
#endif

int DEMOD_L0_MUTEX_LOCK (MUTEX_LOCK_T * mutex, const char * path, int line)
{
	int retry = 10;
	int ret = NO_DEMOD_ERROR;

	char * file = strrchr(path, '/');

	UINT32 spend_us = 0;
	UINT32 spend_ms = 0;

	int check_cnt = 0;

#if defined(DEMOD_SPEND_TIME_CHECK)
	UINT64 start_clock;
	UINT64 spend_clock;
	
	start_clock = DEMOD_L0_SystemClock();
#endif

	if(mutex->cnt != 0) {
		DEMOD_INFO("lock wait (%s)" ", cnt %d, cur tid %d, %s:%d, req tid %d, %s:%d\n",
						mutex->name,
						mutex->cnt, mutex->owner.tid, mutex->owner.file, mutex->owner.line,
						GET_TID(), file, line);
		check_cnt = mutex->cnt;
	}

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - try lock %s, cnt %d, cur tid %d, req tid %d\n", mutex->name, mutex->cnt, mutex->owner.tid, GET_TID());
#endif

	do {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		ret = mutex_lock_interruptible(&mutex->mtx);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		while (!TryEnterCriticalSection(mutex->mtx)) {
			DEMOD_L0_system_wait(1);
		}

		if (mutex->cnt > 0) {
			DEMOD_WARN("%s: %s lock duplicated, cnt %d, cur tid %d, req tid %d\n", __FUNCTION__, mutex->name, mutex->cnt, mutex->owner.tid, GET_TID());
		}
		ret = NO_DEMOD_ERROR;
#else
		ret = NO_DEMOD_ERROR;
#endif
	} while ((ret != NO_DEMOD_ERROR) && retry--);

#if defined(DEMOD_SPEND_TIME_CHECK)
	spend_clock = DEMOD_L0_CalcSpendClock(start_clock, &spend_ms, &spend_us);
#endif


	if (check_cnt) {
		DEMOD_INFO("wait done, spend %3u.%03ums" ", cnt %d->%d, cur pid %d, %s:%d, req pid %d, %s:%d\n", spend_ms, spend_us,
							check_cnt, mutex->cnt,	mutex->owner.tid, mutex->owner.file, mutex->owner.line,
							GET_TID(), file, line);
	}

	if (NO_DEMOD_ERROR != ret) {
		DEMOD_ERROR("lock failed (%s), ret %d, retry %d, spend %3u.%03ums, "
					"cnt %d, cur tid %d, %s:%d, req tid %d, %s:%d\n",
					mutex->name, ret, retry, spend_ms, spend_us,
					mutex->cnt, mutex->owner.tid, mutex->owner.file, mutex->owner.line,
					GET_TID(), file, line);

		dump_stack();
		return ret;
	}

	if(mutex->cnt != 0) {
		DEMOD_ERROR("lock invalid cnt (%s), "
					"cnt %d, cur tid %d, %s:%d, req tid %d, %s:%d\n",
					mutex->name,
					mutex->cnt, mutex->owner.tid, mutex->owner.file, mutex->owner.line,
					GET_TID(), file, line);
		dump_stack();
	}

	mutex->owner.tid = GET_TID();
	mutex->owner.file = file;
	mutex->owner.line = line;
	mutex->cnt++;

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - locked %s, cnt %d, cur tid %d, req tid %d, spend %u.%ums\n", mutex->name, mutex->cnt, mutex->owner.tid, GET_TID(), spend_ms, spend_us);
#endif

	return ret;
}

int DEMOD_L0_MUTEX_UNLOCK (MUTEX_LOCK_T * mutex, const char * path, int line)
{
	char * file = strrchr(path, '/');

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - try unlock %s, cnt %d, cur tid %d, req tid %d\n", mutex->name, mutex->cnt, mutex->owner.tid, GET_TID());
#endif

	mutex->cnt--;

	if(mutex->cnt != 0) {
		DEMOD_ERROR("unlock invalid cnt (%s), "
					"cnt %d, cur tid %d, %s:%d, req tid %d, %s:%d\n",
					mutex->name,
					mutex->cnt, mutex->owner.tid, mutex->owner.file, mutex->owner.line,
					GET_TID(), file, line);
		dump_stack();
		return ERROR_DEMOD_OS_LOCK;
	}


	mutex->owner.tid = 0;
	mutex->owner.file = NULL;
	mutex->owner.line = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
    mutex_unlock(&mutex->mtx);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	//while(!mutex->mtx->Unlock()) {
	//	DEMOD_L0_system_wait(1);
	//}
	LeaveCriticalSection(mutex->mtx);
	//pthread_mutex_unlock(&chip->mutex);
#else
#endif

#if defined(DEBUG_MUTEX)
	DEMOD_INFO("\t\t\t\t - unlocked %s, cnt %d, cur tid %d, req tid %d\n", mutex->name, mutex->cnt, mutex->owner.tid, GET_TID());
#endif

	return NO_DEMOD_ERROR;
}

int DEMOD_L0_MUTEX_INIT (char * name, MUTEX_LOCK_T * mutex) {
	memset(mutex, 0, sizeof(MUTEX_LOCK_T));
	mutex->name = name;
	mutex_init(&mutex->mtx);

	return NO_DEMOD_ERROR;
}

#if (DEMOD_COMM == DEMOD_COMM_FPGA)
MUTEX_LOCK_T _mutex_comm;
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
static UINT32 * _ddr_dbg_buff = NULL;
static UINT32 _ddr_dbg_size = 0;

static int _DEMOD_DDR_Init(void) {
	UINT32 base = DDR_INFO_START - DDR_ADDR_START;
	UINT32 size = DDR_INFO_END - DDR_INFO_START + 4;

	if (NULL != _ddr_dbg_buff) {
		DEMOD_INFO("already init\n");
		return NO_DEMOD_ERROR;
	}

	if ((base + size) > gMemCfgDEMOD_FW.memory_size) {
		DEMOD_ERROR("don't have enough ddr memory, size %u, need %u\n", gMemCfgDEMOD_FW.memory_size, (base + size));
		return -ERROR_DEMOD_FAULT;
	}
	_ddr_dbg_buff = (UINT32 *)vmap_phys(gMemCfgDEMOD_FW.memory_base + base, size);
	_ddr_dbg_size = size;

	DEMOD_NOTI("allocated debug buff @DDR, size %u, locate %p\n", _ddr_dbg_size, _ddr_dbg_buff);

	return NO_DEMOD_ERROR;
}

static int _DEMOD_DDR_Read(UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer) {
	UINT32 addr = Addr & 0x0000FFFF;

	int retc = NO_DEMOD_ERROR;

	if (NULL == _ddr_dbg_buff) {
		retc = _DEMOD_DDR_Init();
		DEMOD_NOTI("DEMOD_DDR_Init done with %d\n", retc);
		if (NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("error with %d\n", retc);
			return retc;
		}
	}

	memcpy(pucDataBuffer, (_ddr_dbg_buff) + (addr >> 2), iNbBytes);

	return NO_DEMOD_ERROR;
}

static int _DEMOD_DDR_Write(UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer) {
	UINT32 addr = Addr & 0x0000FFFF;

	int retc = NO_DEMOD_ERROR;
	if (NULL == _ddr_dbg_buff) {
		retc = _DEMOD_DDR_Init();
		DEMOD_NOTI("DEMOD_DDR_Init done with %d\n", retc);
		if (NO_DEMOD_ERROR != retc) {
			DEMOD_ERROR("error with %d\n", retc);
			return retc;
		}
	}

	memcpy((_ddr_dbg_buff) + (addr >> 2), pucDataBuffer, iNbBytes);

	return NO_DEMOD_ERROR;
}
#endif

int DEMOD_L0_InitDevice (LX_DEMOD_L0_Context* chip)
{
	
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	DEMOD_L0_MUTEX_INIT("demod", &chip->mutex_lock);
#if (DEMOD_COMM == DEMOD_COMM_FPGA)
	DEMOD_L0_MUTEX_INIT("comm", &_mutex_comm);
#endif	
	_DEMOD_DDR_Init();

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

	sysTime =  (UINT32)(curtime.QuadPart / (freq.QuadPart / 1000000));
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
		*pspend_ms = (UINT32)(spend_clock / 1000);
		*pspend_us = spend_clock % 1000;
	}
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	DEMOD_DEBUG("start %u, current %llu, spend %llu, UINT_MAX %u, jf %lu, %llu, ct %u\n", start_clock, current_clock, spend_clock, UINT_MAX, jiffies, get_jiffies_64(), DEMOD_L0_SystemClock());
#endif
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
	(chip)->i2c_base		= 0;
//	(chip)->i2c_handle		= 0;

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
  _DEMOD_L0_Get_I2C_Address function
  Use:        static function (local file scope) for translate address to i2c address
  Parameters: chip, a pointer to the Layer 0 context.
              32bit memroy address
  Returns:    i2c address
************************************************************************************************************************/
static inline int _DEMOD_L0_I2C_Read_NoLock (LX_DEMOD_L0_Context*  chip, UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);
static inline int _DEMOD_L0_I2C_Write_NoLock (LX_DEMOD_L0_Context* chip,  UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer);

static UINT16 _DEMOD_L0_Get_I2C_Address(LX_DEMOD_L0_Context*  chip, UINT32 Addr)
{
	UINT32 base = Addr & 0xFFFF0000;
	UINT32 addr = Addr & 0x0000FFFF;

	UINT16 i2caddr = 0;

	if (DEMOD_CHIP_ID == chip->i2c_slv_addr) {
		if (base == DEMOD_APB_BASE) {
			if (addr >= 0xF000) {
				DEMOD_WARN("addr translated 0x%04X => 0x%04X\n", addr, addr - 0x9c00);
				addr = addr - 0x9c00;
			}
			i2caddr = (0x0000) | ((addr >> 2) & 0x3FFF);
		} else {
			if (base != chip->i2c_base) {
				_DEMOD_L0_I2C_Write_NoLock(chip, DEMOD_APB_BASE + REG_I2C_HBASE, 4, (UINT8 *)&base);
				DEMOD_INFO("base changed 0x%08x->0x%08x\n", chip->i2c_base, base);
				chip->i2c_base = base;
				DEMOD_L0_system_wait(5);
			}
			i2caddr = (0xC000) | ((addr >> 2) & 0x3FFF);
		}
	} else {
		i2caddr = Addr & 0xFFFF;
	}

	return i2caddr;
}

/************************************************************************************************************************
  DEMOD_L0_I2C_Read function
  Use:        lowest layer read function
              Used to read a given number of bytes from the Layer 1 instance.
  Parameters: chip, a pointer to the Layer 0 context.
              iI2CIndex, the index of the first UINT8 to read.
              iNbBytes, the number of bytes to read.
              *pbtDataBuffer, a pointer to a buffer used to store the bytes.
  Returns:    the number of bytes read.
  Porting:    If a single connection mode is allowed, the entire switch can be replaced by a call to the final i2c read function
************************************************************************************************************************/
static inline int _DEMOD_L0_I2C_Read_NoLock (LX_DEMOD_L0_Context*  chip, UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{

	int ret = NO_DEMOD_ERROR;
	int retry = 10;
	UINT16 i2caddr = 0;

	i2caddr = _DEMOD_L0_Get_I2C_Address(chip, Addr);

	do {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		//ret = DEMOD_I2C_Read(i2caddr, iNbBytes, pucDataBuffer);
		ret = DEMOD_I2C_Raw_Read((chip->i2c_slv_addr) >> 1, i2caddr, iNbBytes, pucDataBuffer);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		ret = CLGCOMM::USB_I2C_Read((chip->i2c_slv_addr) >> 1, i2caddr, iNbBytes, pucDataBuffer);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
		DEMOD_ERROR("TODO: have to implement\n");
		ret = NO_DEMOD_ERROR;
#endif
		if (NO_DEMOD_ERROR != ret) {
			DEMOD_WARN("I2C read fail, @0x%04x, %u => ret %d, retry %d\n", Addr, iNbBytes, ret, retry);
		}
		if (*(UINT32 *)pucDataBuffer == 0xdeadcafe) {
			DEMOD_WARN("I2C read fail, @0x%04x, %u => ret %d, retry %d, %s\n", Addr, iNbBytes, ret, retry, DEMOD_BYTE_TO_HEXSTR((char *)pucDataBuffer, iNbBytes));
			ret = -ERROR_DEMOD_READ;
		}
	} while ((NO_DEMOD_ERROR != ret) && (retry--));

	return ret;
}

int DEMOD_L0_I2C_Read (LX_DEMOD_L0_Context*  chip, UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{

	int ret = NO_DEMOD_ERROR;
	int retry = 10;
	UINT16 i2caddr = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)	
	DEMOD_I2C_Raw_Lock();
#endif

	_DEMOD_L0_I2C_Read_NoLock(chip, Addr, iNbBytes, pucDataBuffer);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	DEMOD_I2C_Raw_Unlock();
#endif
	return ret;
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
static inline int _DEMOD_L0_I2C_Write_NoLock (LX_DEMOD_L0_Context* chip,  UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	int ret = NO_DEMOD_ERROR;
	int retry = 10;
	UINT16 i2caddr = 0;

	i2caddr = _DEMOD_L0_Get_I2C_Address(chip, Addr);

//	if (chip->i2c_slv_addr == 0xE0) {
//		DEMOD_NOTI("I2C_RPT_CTRL write Addr 0x%08x, i2caddr 0x%04x, len %u, %02x\n", Addr, i2caddr, iNbBytes, *pucDataBuffer);
//	}
	
	do {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		//ret = DEMOD_I2C_Write(i2caddr, iNbBytes, pucDataBuffer);
		ret = DEMOD_I2C_Raw_Write((chip->i2c_slv_addr) >> 1, i2caddr, iNbBytes, pucDataBuffer);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		ret = CLGCOMM::USB_I2C_Write((chip->i2c_slv_addr) >> 1, i2caddr, iNbBytes, pucDataBuffer);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
		DEMOD_ERROR("TODO: have to implement\n");
		ret = NO_DEMOD_ERROR;
#endif
	} while ((NO_DEMOD_ERROR != ret) && (retry--));

	return ret;
}

int DEMOD_L0_I2C_Write (LX_DEMOD_L0_Context* chip,  UINT32 Addr, UINT8 iNbBytes, UINT8 *pucDataBuffer)
{
	int ret = NO_DEMOD_ERROR;
	int retry = 10;
	UINT16 i2caddr = 0;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	DEMOD_I2C_Raw_Lock();
#endif
	_DEMOD_L0_I2C_Write_NoLock(chip, Addr, iNbBytes, pucDataBuffer);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	DEMOD_I2C_Raw_Unlock();
#endif
	return ret;
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
int DEMOD_L0_ReadCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT32 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;

	int alen = (iNbBytes + 3) & ~0x3;
	int i;
	int base = Addr & 0xFFFF0000;
	int addr = Addr & 0x0000FFFF;

	/* check base address */
	if (base == 0) {
		base = DEMOD_APB_BASE;
	} else if (base == DEMOD_APB_BASE) {
	} else if ((base >= DDR_ADDR_START) && (base <= DDR_ADDR_END)) {
	} else {
		DEMOD_ERROR("Invalid address 0x%08x\n", Addr);
		return -ERROR_DEMOD_INVALID;
	}

#if (DEMOD_COMM == DEMOD_COMM_APB)
	/* APB access */
	unsigned long flags;


	spin_lock_irqsave(&spinlock, flags);
	if (base == DEMOD_APB_BASE) {
		for (i = 0; i < alen; i += 4) {
			UINT32 taddr = (addr + i) - DEMOD_REGMAP_BASE;
			UINT32 wdata = 0;

			if (taddr > DEMOD_REGMAP_SIZE) {
				DEMOD_ERROR("invalid addr translate 0x%08x->0x%04X\n", Addr, taddr);
				dump_stack();
				spin_unlock_irqrestore(&spinlock, flags);
				return ERROR_DEMOD_INVALID;
			}

			err = DEMOD_APB_Read(taddr, &wdata);
			//DEMOD_INFO("apb read, addr x%08x, data x%08x\n", addr + i, wdata);
			if (err != NO_DEMOD_ERROR) {
				DEMOD_ERROR("failed read addr 0x%04x, i 0x%02x => 0x%04x => 0x%04x\n", addr, i, addr + i, taddr);
				break;
			} else if ((i + 4) <= iNbBytes) {
				memcpy(pucDataBuffer + i, &wdata, 4);
			} else {
				memcpy(pucDataBuffer + i, &wdata, (i + 4) - iNbBytes);
			}
		}
	} else {
		//memcpy(pucDataBuffer, base | addr, iNbBytes);
		_DEMOD_DDR_Read(Addr, iNbBytes, pucDataBuffer);
	}
	spin_unlock_irqrestore(&spinlock, flags);

#elif (DEMOD_COMM == DEMOD_COMM_FPGA) || (DEMOD_COMM == DEMOD_COMM_I2C)
	DEMOD_DEBUG("req 0x%08x, %d => %d\n", base | addr, iNbBytes, alen);
#if defined(OLD_I2C_READ)
	for (i = 0; i < alen; i += 4) {
		err |= DEMOD_L0_I2C_Read (chip, base | addr + i, 4, (UINT8 *)pucDataBuffer + i);
	}
#else
	err = DEMOD_L0_I2C_Read (chip, base | addr, alen, (UINT8 *)pucDataBuffer);
#endif
	if (err != NO_DEMOD_ERROR)
		DEMOD_ERROR("failed I2C_Read Addr 0x%04x with %d\n", base | addr, err);
#else
	DEMOD_ERROR("DEMOD_COMM is not defined");
#endif

	return err;
}

int DEMOD_L0_ReadCommandBytes (LX_DEMOD_L0_Context* chip, UINT32 Addr, UINT16 iNbBytes, void * pucDataBuffer)
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
int DEMOD_L0_WriteCommandBytes_NoLock (LX_DEMOD_L0_Context* chip, UINT32 Addr, UINT16 iNbBytes, void * pucDataBuffer)
{
	int err = NO_DEMOD_ERROR;
	int alen = (iNbBytes + 3) & ~0x3;
	int i;
	int base = Addr & 0xFFFF0000;
	int addr = Addr & 0x0000FFFF;

	if (base == 0x00000000) {
		base = DEMOD_APB_BASE;
	} else if (base == DEMOD_APB_BASE) {
	} else if ((base >= DDR_ADDR_START) && (base <= DDR_ADDR_END)) {
	} else {
		DEMOD_ERROR("Invalid base address 0x%08x\n", Addr);
		return -ERROR_DEMOD_INVALID;
	}

#if (DEMOD_COMM == DEMOD_COMM_APB)
	/* APB access */
	unsigned long flags;

	UINT32 wdata = 0;
	UINT32 taddr = 0;

	spin_lock_irqsave(&spinlock, flags);
	if (base == DEMOD_APB_BASE) {
		for (i = 0; i < alen; i += 4)
		{
			taddr = (addr + i) - DEMOD_REGMAP_BASE;

			if (taddr > DEMOD_REGMAP_SIZE) {
				DEMOD_ERROR("invalid addr 0x%04X\n", taddr);
				dump_stack();
				spin_unlock_irqrestore(&spinlock, flags);
				return ERROR_DEMOD_INVALID;
			}

			//DEMOD_INFO("apb write, addr x%08x, data x%08x\n", addr + i, *((UINT32 *)(pucDataBuffer + i)));
			err = DEMOD_APB_Write(taddr, (UINT32 *)(pucDataBuffer + i));
			if (err != NO_DEMOD_ERROR) {
				DEMOD_ERROR("failed write Addr 0x%04x, i 0x%02x => 0x%04x => 0x%04x\n", addr, i, addr + i, taddr);
				break;
			}
		}
	} else {
		//memcpy(base | addr, pucDataBuffer, iNbBytes);
		_DEMOD_DDR_Write(base | addr, iNbBytes, pucDataBuffer);
	}
	spin_unlock_irqrestore(&spinlock, flags);
#elif (DEMOD_COMM == DEMOD_COMM_FPGA) || (DEMOD_COMM == DEMOD_COMM_I2C)
	DEMOD_DEBUG("req 0x%08x, %d => %d\n", base | addr, iNbBytes, alen);
	err = DEMOD_L0_I2C_Write (chip,  base | addr, alen, (UINT8 *)pucDataBuffer);

	if (NO_DEMOD_ERROR != err) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		DEMOD_ERROR("%lu, failed L0_I2C_Write Addr 0x%04x with err %d\n", GetCurrentThreadId(), base | addr, err);
#else
		DEMOD_ERROR("failed L0_I2C_Write Addr 0x%04x with err %d\n", base | addr, err);
#endif
	}
#else
	DEMOD_ERROR("DEMOD_COMM is not defined");
#endif

	return err;
}

int DEMOD_L0_WriteCommandBytes (LX_DEMOD_L0_Context* chip, UINT32 Addr, UINT16 iNbBytes, void * pucDataBuffer)
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

