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
 *	demod ipc for o20
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-01-03
 *	@note
 */
#define DEMOD_TAG "[CHIP.IPC] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L2_Common_API.h"

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>		/* printk() */
#include <linux/types.h>		/* size_t */

#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/spinlock.h>

#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "demod_module.h"

#include "demod_common_o22.h"
#include "demod_ipc_o22.h"

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <WinSock2.h>
#include <afxwin.h>

extern LX_DEMOD_L2_Context * DEMOD_GetContext (void);
#define DEMOD_O22_GetContext DEMOD_GetContext

#include "demod_common_gui.h"
#include "demod_ipc_o22.h"

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#endif

static int 	_ipc_enable = -1;

static int _DEMOD_O22_IPC_Handler (LX_DEMOD_L2_Context * frontend);

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)

/******************************************************************
 * IPC handler using polling thread 
 ******************************************************************/
#if defined(DEMOD_CONFIG_POLL)
static struct task_struct *
			_ipc_poll_thread = NULL;

static int _DEMOD_O22_IPC_POLL_Handler(void * data) {
	int prv_en = -1;
	unsigned int count = 0;

	DEMOD_DEBUG("start ipc_handler on polling thread\n");

	while (!kthread_should_stop()) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_timeout(1);	// linux ticks 100Hz. so, schedule_timeout(1) means 10ms.

		if (prv_en == _ipc_enable) {
			if ((count++ % 1000) == 0) {
				/* maybe doing below code per 10sec */
				DEMOD_PRINT("count %u, state prv %d, cur %d, cur %llu, %lu %lu %lu\n",
					count, prv_en, _ipc_enable, get_jiffies_64(), msecs_to_jiffies(1), msecs_to_jiffies(10), msecs_to_jiffies(100));
			}
		} else {
			DEMOD_DEBUG("state changed %d -> %d\n", prv_en, _ipc_enable);
			prv_en = _ipc_enable;
			count = 0;
		}

		if (_ipc_enable == TRUE) {
			_DEMOD_O22_IPC_Handler((LX_DEMOD_L2_Context *)data);
		}
	}
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable)
{
	DEMOD_INFO("IPC polling %s\n", ((enable == TRUE) ? "enable" : "disable"));
	if (enable) {
	} else {
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	int err = NO_DEMOD_ERROR;

	_DEMOD_O22_IPC_Handler_Enable(frontend, FALSE);

	_ipc_poll_thread = kthread_run(_DEMOD_O22_IPC_POLL_Handler, (void *)frontend, "demod_ipc_poll");

	if (_ipc_poll_thread == NULL) {
		DEMOD_ERROR("failed create polling thread %d\n", _ipc_poll_thread);
		err = -ENOMEM;
	}

	return NO_DEMOD_ERROR;
}

#else	// not defined DEMOD_CONFIG_POLL
/******************************************************************
 * IPC handler using interrupt handler
 ******************************************************************/

static int	_ipc_irq = -1;

static irqreturn_t _DEMOD_O22_IPC_INTR_Handler (int irq, void * dev_id, struct pt_regs * regs) {
	DEMOD_DEBUG("triggerd irq %d\n", irq);

	if (_ipc_enable == TRUE) {
		_DEMOD_O22_IPC_Handler((LX_DEMOD_L2_Context *)dev_id);
	}

	return IRQ_HANDLED;
}

static int _DEMOD_O22_IPC_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable)
{
	if (_ipc_irq < 0) {
		return -ERROR_DEMOD_IPC;
	}

	DEMOD_NOTI("IPC INTR %s\n", ((enable == TRUE) ? "enable" : "disable"));
	if (TRUE == enable) {
		enable_irq(_ipc_irq);
	} else {
		disable_irq(_ipc_irq);
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	int err = NO_DEMOD_ERROR;

	if (_ipc_irq < 0) {
		_ipc_irq = O22_IRQ_INTR_DBB_CPU;

		/* request_irq from mcu */
		err = request_irq(_ipc_irq , (irq_handler_t)_DEMOD_O22_IPC_INTR_Handler, IRQF_TRIGGER_HIGH, "demod_ipc", (void *)frontend);
		disable_irq(_ipc_irq);

		if (err) {
			DEMOD_ERROR("error (%d) whilre request_irq (%d)\n", err, _ipc_irq);
			free_irq(_ipc_irq, NULL);
			return err;
		}

		DEMOD_DEBUG("request_irq done\n");
	}

	return NO_DEMOD_ERROR;
}

#endif	// DEMOD_CONFIG_POLL

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
/******************************************************************
 * IPC handler using polling thread on WIN32 (C/C++)
 ******************************************************************/

CWinThread * _ipc_poll_thread = NULL;
static int 	_ipc_poll_enable = FALSE;

static UINT _DEMOD_O22_IPC_GUI_POLL_Handler(LPVOID pParam) {
	DEMOD_INFO("POLL start, tid %lu\n", GetCurrentThreadId());

	while (_ipc_poll_enable == TRUE) {
		if (_ipc_enable == TRUE) {
			_DEMOD_O22_IPC_Handler((LX_DEMOD_L2_Context *)pParam);
		}
		DEMOD_L0_system_wait(5);
	}

	DEMOD_INFO("POLL exit\n");
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable) {
	DEMOD_INFO("IPC polling %s\n", ((enable == TRUE) ? "enable" : "disable"));
	if (enable) {
	} else {
		if (_ipc_poll_thread != NULL) {
			HANDLE tHandle = _ipc_poll_thread->m_hThread;
			
			DEMOD_L0_LockDevice(frontend->demod->chip);	// L1_Process 종료되는것을 기다리기 위해 Lock_Device 수행
			_ipc_poll_enable = FALSE;
			WaitForSingleObject(tHandle, INFINITE);
			DEMOD_INFO("POLL terminated\n");
			_ipc_poll_thread = NULL;
			DEMOD_L0_UnlockDevice(frontend->demod->chip);
		}
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	if (_ipc_poll_enable == FALSE) {
		_DEMOD_O22_IPC_Handler_Enable(frontend, FALSE);
		_ipc_poll_enable = TRUE;
		
		if (_ipc_poll_thread == NULL) {
			_ipc_poll_thread = AfxBeginThread(_DEMOD_O22_IPC_GUI_POLL_Handler, frontend);
		}
	}

	return NO_DEMOD_ERROR;
}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
/******************************************************************
 * IPC handler is Not Implemented for PLATFORM_EXT
 ******************************************************************/
static int _DEMOD_O22_IPC_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable) {
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	return NO_DEMOD_ERROR;
}

#endif


static int _DEMOD_O22_IPC_DMsg_Reader(LX_DEMOD_L2_Context * frontend) {
	int retc = NO_DEMOD_ERROR;
	static char tmpbuf[MESSAGE_BMAX];

	CBUF_H bufh;

	LX_DEMOD_L1_IPC * ipc = frontend->demod->ipc;

	retc = DEMOD_L0_CBUF_Read(&ipc->dbg, &bufh, &tmpbuf[COMMAND_BSIZ]);
	if (retc != NO_DEMOD_ERROR) {
		ipc->status.mdbg_fail_cnt++;
	
		DEMOD_ERROR("mcu to dbg cbuf read failed with 0x%02X, fail_cnt %u / %u\n", -retc, ipc->status.mdbg_fail_cnt, ipc->status.mdbg_fail_cnt + ipc->status.mdbg_cnt);
		return -ERROR_DEMOD_IPC;
	}
	ipc->status.mdbg_cnt++;
	memcpy(&tmpbuf[0], &bufh, COMMAND_BSIZ);
	
	DEMOD_L1_IPC_Parser(frontend->demod, &bufh, tmpbuf, COMMAND_BSIZ + bufh.len);

	return NO_DEMOD_ERROR;
}

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && !defined(DEMOD_CONFIG_POLL)
#define DEMOD_IPC_DMSG_POLLING
#endif

#if defined(DEMOD_IPC_DMSG_POLLING)
/******************************************************************
 * pollling thread for debuging log from DEMOD MCU
******************************************************************/
static struct task_struct *
					_ipc_dmsg_thread = NULL;
wait_queue_head_t	_ipc_dmsg_wait;

static int _DEMOD_O22_IPC_DMsg_Handler(void * data) {
	int retc = NO_DEMOD_ERROR;

	LX_DEMOD_L2_Context * frontend = (LX_DEMOD_L2_Context *)data;
	LX_DEMOD_L1_IPC * ipc = frontend->demod->ipc;

	DEMOD_INFO("start, _ipc_enable %s\n", (TRUE == _ipc_enable) ? "en" : "dis");

	while (!kthread_should_stop()) {
		if (FALSE == _ipc_enable) {
			/* wait until _ipc_enable == TRUE */
			retc = wait_event_interruptible_timeout(_ipc_dmsg_wait, (TRUE == _ipc_enable), msecs_to_jiffies(1000));
			if (TRUE == _ipc_enable)
				DEMOD_INFO("_ipc_enable false -> true, DMsg Handler enabled\n");
			else
				DEMOD_PRINT("_ipc_enable still false, wait...\n");
			continue;
		}

		if (TRUE == _ipc_enable) {
			retc = wait_event_interruptible_timeout(_ipc_dmsg_wait, (FALSE == _ipc_enable) || (DEMOD_L0_CBUF_Used(&ipc->dbg) > 0), msecs_to_jiffies(100));
			if (FALSE == _ipc_enable) {
				DEMOD_INFO("_ipc_enable true -> false, DMsg Handler disabled\n");
				continue;
			}

			while (DEMOD_L0_CBUF_Used(&ipc->dbg) > 0) {
				if (NO_DEMOD_ERROR != _DEMOD_O22_IPC_DMsg_Reader(frontend))
					break;
			}
		}
	}

	DEMOD_INFO("exit\n");
	
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_DMsg_Handler_Wakeup(void) {
	wake_up_interruptible(&_ipc_dmsg_wait);
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_DMsg_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	int err = NO_DEMOD_ERROR;

	init_waitqueue_head(&_ipc_dmsg_wait);
	_ipc_dmsg_thread = kthread_run(_DEMOD_O22_IPC_DMsg_Handler, (void *)frontend, "demod_ipc_msg_poll");

	if (NULL == _ipc_dmsg_thread) {
		DEMOD_ERROR("failed create polling thread\n");
		err = -ENOMEM;
	}

	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_DMsg_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable)
{
	if (_ipc_enable != enable) {
		DEMOD_PRINT("IPC DMsg polling thread set %s\n", ((enable == TRUE) ? "enable" : "disable"));
		if (enable) {
			_ipc_enable = TRUE;
			wake_up_interruptible(&_ipc_dmsg_wait);
		} else {
			_ipc_enable = FALSE;
			wake_up_interruptible(&_ipc_dmsg_wait);
		}
	}

	return NO_DEMOD_ERROR;
}

#else
static int _DEMOD_O22_IPC_DMsg_Handler_Wakeup(void) {
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_DMsg_Handler_Init(LX_DEMOD_L2_Context * frontend) {
	return NO_DEMOD_ERROR;
}

static int _DEMOD_O22_IPC_DMsg_Handler_Enable(LX_DEMOD_L2_Context * frontend, int enable)
{
	return NO_DEMOD_ERROR;
}

#endif



int DEMOD_O22_IPC_Send (UINT32 type, UINT32 seq, char *ptr, UINT32 len) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();
	return DEMOD_L1_IPC_Send(frontend->demod, type, seq, ptr, len);
}

int DEMOD_O22_IPC_Status(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();
	int dbgidx = 0;

	dbgidx += sprintf(pDbglog + dbgidx, "ipc handler: %s, ", (_ipc_enable == TRUE ? "enabled" : "disabled"));
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && !defined(DEMOD_CONFIG_POLL)
	dbgidx += sprintf(pDbglog + dbgidx, "isr with irq %d\n", _ipc_irq);
#else
	dbgidx += sprintf(pDbglog + dbgidx, "polling with kthread\n");
#endif

	dbgidx += DEMOD_L1_IPC_Status(frontend->demod, pDbglog + dbgidx);

	*pDbgidx = dbgidx;
	return RET_OK;
}

int DEMOD_O22_IPC_Dump(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();
	int dbgidx = 0;

	dbgidx += DEMOD_L1_IPC_Dump(frontend->demod, pDbglog + dbgidx);

	*pDbgidx = dbgidx;
	return RET_OK;
}

int DEMOD_O22_IPC_Reset(void) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();

	return DEMOD_L1_IPC_Reset(frontend->demod);
}

int DEMOD_O22_IPC_Enable(int enable) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();

	if (_ipc_enable != enable) {
		_DEMOD_O22_IPC_Handler_Enable(frontend, enable);
		_DEMOD_O22_IPC_DMsg_Handler_Enable(frontend, enable);
	}

	_ipc_enable = enable;

	return RET_OK;
}


#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && defined(DEMOD_FW_RECOVERY)
extern int DEMOD_O22_FW_Error_Handler (int errcode);
#endif

static int _DEMOD_O22_IPC_Handler (LX_DEMOD_L2_Context * frontend) {
	int retc = NO_DEMOD_ERROR;
	int retry = 0;

	static char tmpbuf[MESSAGE_BMAX];
	CBUF_H bufh;

	LX_DEMOD_L1_IPC * ipc = frontend->demod->ipc;

#if defined(DEMOD_FW_RECOVERY)
	static UINT32 prv_error_flag = 0;
	UINT32 error_flag;
	UINT32 reset_flag;
#endif

	if (ipc->init_done == 0) {
		DEMOD_ERROR("not yet initialized IPC\n");
		return -ERROR_DEMOD_FW_INIT;
	}

	ipc->status.intr_cnt++;

#if defined(DEMOD_FW_RECOVERY)
	DEMOD_L0_Lock_CommDevice(frontend->demod->chip);
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock(frontend->demod->chip, REG_ERROR_FLAG, 4, &error_flag)) {
		DEMOD_ERROR("failed read REG_ERROR_FLAG\n");
	}
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock(frontend->demod->chip, REG_RESET_FLAG, 4, &reset_flag)) {
		DEMOD_ERROR("failed read REG_RESET_FLAG\n");
	}
	DEMOD_L0_Unlock_CommDevice(frontend->demod->chip);

	//DEMOD_ERROR("error_flag %u, reset_flag %u\n", error_flag, reset_flag);
	//printk("DEMOD err %x, rst %x\n", error_flag, reset_flag);

	if ((error_flag != 0) || (reset_flag != 0)) {
		if (error_flag != 0 && prv_error_flag != error_flag) {
			switch(error_flag) {
				case CMD_TYPE_ERROR_TIMEOUT:
					DEMOD_MCU_ERROR("fw watchdog occurred! adc off\n");
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && defined(DEMOD_FW_RECOVERY)
					DEMOD_O22_FW_Error_Handler(CMD_TYPE_ERROR_TIMEOUT);
#endif
					break;
				case CMD_TYPE_ERROR_FWRESET:
					DEMOD_MCU_ERROR("fw watchdog occurred! need fw reset\n");
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && defined(DEMOD_FW_RECOVERY)
					DEMOD_O22_FW_Error_Handler(CMD_TYPE_ERROR_FWRESET);
#endif
					break;
				default:
					break;
			}
			prv_error_flag = error_flag;
		} else {
			DEMOD_MCU_DEBUG("prv 0x%04x, err 0x%04x, rst 0x%08x\n", prv_error_flag, error_flag, reset_flag);
		}
	}
#endif

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	retry = 3;

	do {
		retc = DEMOD_L1_IPC_Clear(frontend->demod);
		if (retc != NO_DEMOD_ERROR) {
			ipc->status.intr_fail_cnt++;
			DEMOD_ERROR("interrupt register clear failed with %d, intr_fail_cnt %u\n", retc, ipc->status.intr_fail_cnt);
		}
	} while (retry-- > 0 && retc != NO_DEMOD_ERROR);
#endif

	while (DEMOD_L0_CBUF_Used(&ipc->rx) > 0) {
		retc = DEMOD_L0_CBUF_Read(&ipc->rx, &bufh, &tmpbuf[COMMAND_BSIZ]);
		if (retc != NO_DEMOD_ERROR) {
			ipc->status.mdrv_fail_cnt++;

			DEMOD_ERROR("mcu to kdrv cbuf read failed with 0x%02X, fail_cnt %u / %u\n", -retc, ipc->status.mdrv_fail_cnt, ipc->status.mdrv_fail_cnt + ipc->status.mdrv_cnt);
			break;
		}
		ipc->status.mdrv_cnt++;
		memcpy(&tmpbuf[0], &bufh, COMMAND_BSIZ);

		DEMOD_L1_IPC_Parser(frontend->demod, &bufh, tmpbuf, COMMAND_BSIZ + bufh.len);
	}

	if (DEMOD_L1_IPC_Recv_Count(frontend->demod) > 0) {
		DEMOD_L1_IPC_Wait_Cancel(frontend->demod);
	}

#if defined(DEMOD_IPC_DMSG_POLLING)
	_DEMOD_O22_IPC_DMsg_Handler_Wakeup();
#else
	while (DEMOD_L0_CBUF_Used(&ipc->dbg) > 0) {
		if (NO_DEMOD_ERROR != _DEMOD_O22_IPC_DMsg_Reader(frontend))
			break;
	}
#endif

	return NO_DEMOD_ERROR;
}

int DEMOD_O22_IPC_Init(void) {
	int err = NO_DEMOD_ERROR;
	LX_DEMOD_L2_Context * frontend = DEMOD_O22_GetContext();

	_ipc_enable = FALSE;

	err = DEMOD_L1_IPC_Init(frontend->demod);
	if (NO_DEMOD_ERROR != err) {
		DEMOD_ERROR("DEMOD_L1_IPC_Init failed with %d\n", err);
		return err;
	}

	_DEMOD_O22_IPC_Handler_Init(frontend);
	_DEMOD_O22_IPC_DMsg_Handler_Init(frontend);

	return NO_DEMOD_ERROR;
}





