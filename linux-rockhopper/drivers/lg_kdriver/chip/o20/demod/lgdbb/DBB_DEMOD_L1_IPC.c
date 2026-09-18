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
 *	demod circular buff for communication with mcu
 *
 *	@author 	samin.ryu
 *	@version	1.1
 *	@date		2019-05-28
 *	@note		modified for LGDBB
 */

#define DEMOD_TAG "[L1,IPC] "

#include <DBB_DEMOD_typedefs.h>
#include <demod_util.h>

#include "DBB_DEMOD_L1_IPC.h"
#include "DBB_DEMOD_L1_Properties.h"
#include "DBB_DEMOD_L1_Commands.h"

#include "DBB_DEMOD_L1_API.h"

#include "DBB_DEMOD_L1_IPC_Prototypes.h"
#include "DBB_DEMOD_L1_Commands_Prototypes.h"
#include "DBB_DEMOD_L1_Properties_Functions.h"

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

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <afxwin.h>

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
#endif

static int 	_ipc_enable = FALSE;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_XTENSA)

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(DEMOD_CONFIG_POLL)
static struct task_struct *
			_ipc_polling_thread = NULL;
#else
static int	_ipc_irq = -1;
#endif

static unsigned long irq_flags;

static int _DEMOD_L1_Lock_Handler(LX_DEMOD_L1_Context* core)
{
	spin_lock_irqsave(&core->ipc->message.lock, irq_flags);
	return NO_DEMOD_ERROR;
}

static int _DEMOD_L1_Unlock_Handler(LX_DEMOD_L1_Context* core)
{
	spin_unlock_irqrestore(&core->ipc->message.lock, irq_flags);
	return NO_DEMOD_ERROR;
}

#if defined(DEMOD_CONFIG_POLL)
static int _DBB_DEMOD_L1_IPC_POLL_Handler(void * data) {
	int prv_en = -1;
	unsigned int count = 0;

	DEMOD_DEBUG("start\n");

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
			DEMOD_L1_IPC_Handler((LX_DEMOD_L1_Context *)data);
		}
	}
	return NO_DEMOD_ERROR;
}

static int _DBB_DEMOD_L1_IPC_POLL_Start(LX_DEMOD_L1_Context * core)
{
	DEMOD_INFO("Poll start, flag %s -> true\n", ((_ipc_enable == TRUE) ? "true" : "false"));

	if (_ipc_enable == FALSE) {
		_ipc_enable = TRUE;
	}

	return 0;
}

static int _DBB_DEMOD_L1_IPC_POLL_Stop(LX_DEMOD_L1_Context * core)
{
	DEMOD_INFO("Poll stop, flag %s -> false\n", ((_ipc_enable == TRUE) ? "true" : "false"));

	if (_ipc_polling_thread != NULL) {

	}

	return 0;
}
#endif

static irqreturn_t _DBB_DEMOD_L1_IPC_IRQ_Handler (int irq, void * dev_id, struct pt_regs * regs) {
	DEMOD_DEBUG("triggerd irq %d\n", irq);

	DEMOD_L1_IPC_Handler((LX_DEMOD_L1_Context *)dev_id);

	return IRQ_HANDLED;
}
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
CEvent* pEvent = NULL;
CWinThread * pPollThread = NULL;
static int 	_poll_enable = FALSE;
//CMutex mutex_cbuf_ram(FALSE, "cbuf_ram");
static MUTEX_LOCK_T _mutex_handler;

static int _DEMOD_L1_Lock_Handler(LX_DEMOD_L1_Context* core)
{
	return DEMOD_L0_MUTEX_LOCK("handler", &_mutex_handler);
	return NO_DEMOD_ERROR;
}

static int _DEMOD_L1_Unlock_Handler(LX_DEMOD_L1_Context* core)
{
	return DEMOD_L0_MUTEX_UNLOCK("handler", &_mutex_handler);
	return NO_DEMOD_ERROR;
}

static UINT _DBB_DEMOD_L1_IPC_POLL(LPVOID pParam) {
	LX_DEMOD_L1_Context * core = (LX_DEMOD_L1_Context *)pParam;

	DEMOD_INFO("POLL start, tid %lu\n", GetCurrentThreadId());

	while (_poll_enable == TRUE) {
		DEMOD_L0_system_wait(5);
		DEMOD_L1_IPC_Handler(core);
	}

	DEMOD_INFO("POLL exit\n");
	return 0;
}

static int _DBB_DEMOD_L1_IPC_POLL_Start(LX_DEMOD_L1_Context * core)
{
	DEMOD_INFO("Poll start, flag %s -> true\n", ((_poll_enable == TRUE) ? "true" : "false"));

	if (_poll_enable == FALSE) {
		_poll_enable = TRUE;

		
		if (pPollThread == NULL) {
			pPollThread = AfxBeginThread(_DBB_DEMOD_L1_IPC_POLL, core);
		}
	}

	return 0;
}

static int _DBB_DEMOD_L1_IPC_POLL_Stop(LX_DEMOD_L1_Context * core)
{
	DEMOD_INFO("Poll stop, flag %s -> false\n", ((_poll_enable == TRUE) ? "true" : "false"));

	if (pPollThread != NULL) {
		HANDLE tHandle = pPollThread->m_hThread;
		
		DEMOD_L0_LockDevice(core->chip);	// L1_Process 종료되는것을 기다리기 위해 Lock_Device 수행
		_poll_enable = FALSE;
		WaitForSingleObject(tHandle, INFINITE);
		DEMOD_INFO("POLL terminated\n");
		pPollThread = NULL;
		DEMOD_L0_UnlockDevice(core->chip);
	}

	return 0;
}

#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_EXT)
static int _DEMOD_L1_Lock_Handler(LX_DEMOD_L1_Context* core)
{
	return NO_DEMOD_ERROR;
}

static int _DEMOD_L1_Unlock_Handler(LX_DEMOD_L1_Context* core)
{
	return NO_DEMOD_ERROR;
}

#endif

int DEMOD_L1_IPC_Send(LX_DEMOD_L1_Context * core, UINT32 typ, UINT32 seq, char *ptr, int len) {
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L0_CBUF_Write(&core->ipc->tx, typ, seq, ptr, len);
	wmb();

	if (retc == NO_DEMOD_ERROR) {
		core->ipc->status.send_cnt++;
		DEMOD_DEBUG("send len %d, type 0x%04x, payloads %d, %s, retc 0x%02X\n", COMMAND_BSIZ + len, typ, len, (len > 0 ? dbb_debug_byte_to_hexstr(ptr, len) : "null"), -retc);
	} else {
		core->ipc->status.send_fail_cnt++;
		DEMOD_ERROR("DEMOD_L0_CBUF_Write error with retc 0x%02X, send_fail_cnt %u\n", -retc, core->ipc->status.send_fail_cnt);
	}
	return retc;
}

int DEMOD_L1_IPC_Send_Count(LX_DEMOD_L1_Context * core) {
	int retc = DEMOD_L0_CBUF_Used(&core->ipc->tx);
	
	if (retc < 0) {
		DEMOD_ERROR("DEMOD_L0_CBUF_Used error with ec 0x%02X\n", -retc);
		retc = 0;
	}

	return retc;
}

int DEMOD_L1_IPC_Send_GetState(LX_DEMOD_L1_Context * core, int * pstate) {
	int ret = DEMOD_L0_CBUF_GetState(&core->ipc->tx, (cbuf_state *)pstate);

	rmb();
	return ret;
}

int DEMOD_L1_IPC_Recv(LX_DEMOD_L1_Context * core, UINT32 *ptyp, UINT32 * pseq, char *pdst) {
	static char tmpbuf[MESSAGE_BMAX];
	int ret;
	int len;

	CBUF_H head;

	ret = DEMOD_L1_IPC_Recv_Count(core);

	if (ret == 0) {
		DEMOD_ERROR("recv is empty\n");
		return -ERROR_DEMOD_IPC_EMPTY;
	}

	_DEMOD_L1_Lock_Handler(core);
	len = kfifo_out(&core->ipc->message.fifo, tmpbuf, MESSAGE_BMAX);
	_DEMOD_L1_Unlock_Handler(core);

	if (len >= COMMAND_BSIZ) {
		memcpy(&head, &tmpbuf[0], sizeof(CBUF_H));

		*ptyp = head.typ;
		*pseq = head.seq;

		if (head.len > 0) {
			if (head.len <= PAYLOAD_BMAX)
				memcpy(pdst, &tmpbuf[COMMAND_BSIZ], head.len);
			else
				DEMOD_ERROR("invalid head typ 0x%02X, len %u\n", head.typ, head.len);
		}
	} else {
		core->ipc->status.recv_fail_cnt++;
		DEMOD_ERROR("invalid read length from _msg_fifo: %d, read_fail_cnt %u\n", len, core->ipc->status.recv_fail_cnt);
		return -ERROR_DEMOD_IPC_FALUT;
	}

	*ptyp = head.typ;
	core->ipc->status.recv_cnt++;

	DEMOD_DEBUG("recv len %d, type 0x%04x, payloads %d, %s\n", len, *ptyp, head.len, (head.len > 0 ? DEMOD_BYTE_TO_HEXSTR(pdst, head.len) : "null"));
	return head.len;
}

int DEMOD_L1_IPC_Recv_Count(LX_DEMOD_L1_Context * core) {
	return kfifo_len(&core->ipc->message.fifo);
}

int DEMOD_L1_IPC_Recv_GetState(LX_DEMOD_L1_Context * core, UINT32 * pstate) {
	int ret = DEMOD_L0_CBUF_GetState(&core->ipc->rx, (cbuf_state *)pstate);
	rmb();
	return ret;
}

int DEMOD_L1_IPC_Wait(LX_DEMOD_L1_Context * core, int retry) {
	int ret = NO_DEMOD_ERROR;

	do {
		DEMOD_DEBUG("wait until (recv count(%d) > 0) and (retry(%d) > 0)\n", DEMOD_L1_IPC_Recv_Count(), retry);
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		ret = wait_event_interruptible_timeout(core->ipc->message.wait, (DEMOD_L1_IPC_Recv_Count(core) > 0), msecs_to_jiffies(100));
		//if (DEMOD_L1_IPC_Recv_Count(core) <= 0) {
		//	DEMOD_L0_system_wait(1);
		//}
			
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		//Sleep(100);
		if (pEvent != NULL) {
			WaitForSingleObject(pEvent->m_hObject, 500);
		} else {
			fprintf(stderr, "CEvent is null\n");
		}
#else
		ret = 0;
#endif
		
		if ((ret > 0) && (DEMOD_L1_IPC_Recv_Count(core) > 0)) {
			break;
		}
		core->ipc->status.tout_cnt++;
		if (ret < 0) {
			DEMOD_WARN("wait cancelled by signal, retc 0x%02X\n", -ret);
		}
	} while(retry-- > 0);

	DEMOD_DEBUG("wait done with (recv count(%d)), retry(%d) and retc 0x%02X\n", DEMOD_L1_IPC_Recv_Count(), retry, -ret);
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Wait_Cancel(LX_DEMOD_L1_Context * core) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	wake_up_interruptible(&core->ipc->message.wait);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)

#else

#endif
	
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Status_Fifo(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;
	dbgidx += SPRINTF(dbglog + dbgidx, "fifo %8u, kfifo %u/%u", core->ipc->status.fifo_cnt, kfifo_len(&core->ipc->message.fifo), kfifo_size(&core->ipc->message.fifo));

	return dbgidx;
}

int DEMOD_L1_IPC_Status(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

#if defined(DEMOD_CONFIG_IPC)
	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\n\tIPC ON\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\tCBUF TX\n\t\t");
	dbgidx += DEMOD_L0_CBUF_Status(&core->ipc->tx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tCBUF RX\n\t\t");
	dbgidx += DEMOD_L0_CBUF_Status(&core->ipc->rx, dbglog + dbgidx);
#else
	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\n\tIPC OFF\n");
#endif

	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\tintr %8u, fail %8u, tout %8u\n", core->ipc->status.intr_cnt, core->ipc->status.intr_fail_cnt, core->ipc->status.tout_cnt);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tsend %8u, fail %8u, recv %8u, fail %8u\n", core->ipc->status.send_cnt, core->ipc->status.send_fail_cnt, core->ipc->status.recv_cnt, core->ipc->status.recv_fail_cnt);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tfifo %8u, mesg %8u, kfifo%8u / %u\n", core->ipc->status.fifo_cnt, core->ipc->status.mesg_cnt, kfifo_len(&core->ipc->message.fifo), kfifo_size(&core->ipc->message.fifo));

	return dbgidx;
}

int DEMOD_L1_IPC_Dump (LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

#if defined(DEMOD_CONFIG_IPC)
	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\tIPC ON\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\nCBUF TX\n");
	dbgidx += DEMOD_L0_CBUF_Show(&core->ipc->tx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\nCBUF RX\n");
	dbgidx += DEMOD_L0_CBUF_Show(&core->ipc->rx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n\n");

	dbgidx += DEMOD_L1_Process_Dump(core, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
#else
	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\tIPC OFF\n");
#endif

	return dbgidx;
}

int DEMOD_L1_IPC_Reset(LX_DEMOD_L1_Context * core) {
	UINT32 wtemp;

	DEMOD_L0_CBUF_Reset(&core->ipc->tx);
	DEMOD_L0_CBUF_Reset(&core->ipc->rx);

	DEMOD_L0_CBUF_Clear(&core->ipc->tx);
	DEMOD_L0_CBUF_Clear(&core->ipc->rx);
	wtemp = DEMOD_MAGIC_CODE;

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_STATE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	_DEMOD_L1_Lock_Handler(core);
	kfifo_reset(&core->ipc->message.fifo);
	_DEMOD_L1_Unlock_Handler(core);

	memset(&core->ipc->status, 0, sizeof(LX_DEMOD_L1_IPC_Status));

	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Enable (LX_DEMOD_L1_Context * core, int enable) {
	DEMOD_INFO("IPC Enable %d->%d\n", _ipc_enable, enable);

	if (_ipc_enable != enable) {
		if (enable == TRUE) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(DEMOD_CONFIG_POLL)
			_DBB_DEMOD_L1_IPC_POLL_Start(core);
#else
			enable_irq(_ipc_irq);
#endif
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		_DBB_DEMOD_L1_IPC_POLL_Start(core);
#endif
		} else {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
#if defined(DEMOD_CONFIG_POLL)
			_DBB_DEMOD_L1_IPC_POLL_Stop(core);
#else
			disable_irq(_ipc_irq);
#endif
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		_DBB_DEMOD_L1_IPC_POLL_Stop(core);
#endif
		}
	}

	_ipc_enable = enable;
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Clear (LX_DEMOD_L1_Context * core) {
	UINT32 src;

	DEMOD_L0_Lock_CommDevice(core->chip);
	if(NO_DEMOD_ERROR != DEMOD_L0_ReadCommandBytes_NoLock(core->chip, REG_INT_SRC, 4, &src)) {
		DEMOD_L0_Unlock_CommDevice(core->chip);
		return -ERROR_DEMOD_READ;
	}

	/* clear MCU->CPU interrupt souce flag */
	src &= 0x7F;
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(core->chip, REG_INT_SRC, 4, &src)) {
		DEMOD_L0_Unlock_CommDevice(core->chip);
		return -ERROR_DEMOD_WRITE;
	}

	DEMOD_L0_Unlock_CommDevice(core->chip);
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Handler (LX_DEMOD_L1_Context * core) {
	int retc = NO_DEMOD_ERROR;
	int retry = 0;

	static char tmpbuf[MESSAGE_BMAX];
	char * msg = &tmpbuf[COMMAND_BSIZ];

	CBUF_H bufh;

	if (core->ipc->init_done == 0) {
		DEMOD_ERROR("not yet initialized IPC\n");
		return -ERROR_DEMOD_FW_INIT;
	}

	core->ipc->status.intr_cnt++;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	retry = 3;

	do {
		retc = DEMOD_L1_IPC_Clear(core);
		if (retc != NO_DEMOD_ERROR) {
			core->ipc->status.intr_fail_cnt++;
			DEMOD_ERROR("interrupt register clear failed with %d, intr_fail_cnt %u\n", retc, core->ipc->status.intr_fail_cnt);
		}
	} while (retry-- > 0 && retc != NO_DEMOD_ERROR);
#endif

	while (DEMOD_L0_CBUF_Used(&core->ipc->rx) > 0) {
		retc = DEMOD_L0_CBUF_Read(&core->ipc->rx, &bufh, &tmpbuf[COMMAND_BSIZ]);
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		rmb();
#endif

		if (retc != NO_DEMOD_ERROR) {
			core->ipc->status.intr_fail_cnt++;

			DEMOD_ERROR("mcu to kdrv cbuf read failed with 0x%02X, fail_cnt %u\n", -retc, core->ipc->status.intr_fail_cnt);
			break;
		}

		memcpy(&tmpbuf[0], &bufh, COMMAND_BSIZ);

		if (CMD_MAJOR_TYPE(bufh.typ) == CMD_MAJOR_TYPE_API) {
			//DEMOD_DEBUG("recv %02X, %3u, %3u\n", bufh.typ, bufh.seq, bufh.len);

			core->ipc->status.fifo_cnt++;

			_DEMOD_L1_Lock_Handler(core);
			kfifo_in(&core->ipc->message.fifo, tmpbuf, bufh.len + COMMAND_BSIZ);
			_DEMOD_L1_Unlock_Handler(core);

		} else {
			core->ipc->status.mesg_cnt++;
			switch (bufh.typ) {
			case CMD_TYPE_SYSTEM_INIT:
					DEMOD_MCU_PRINT("MCU Init: %s\n", (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_SYSTEM_READY:
				DEMOD_MCU_PRINT("MCU Ready: %s\n", (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_SYSTEM_START:
				DEMOD_MCU_PRINT("MCU Start: %s\n", (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_SYSTEM_STOP:
				DEMOD_MCU_PRINT("MCU Stop: %s\n", (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_SYSTEM_ALIVE:
				{
					static unsigned int alive_check = 0;
					unsigned int spend_check = 0;
					//unsigned int dump[4];

					if (alive_check > 0)
						spend_check = DEMOD_L0_CalcSpendTime(alive_check);

					DEMOD_MCU_PRINT("\t\t\t\t\t\t\tMCU alive: period %u, %s\n", spend_check, (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
					alive_check = DEMOD_L0_system_time();

					//DEMOD_L0_ReadCommandBytes(core->chip, 0x54D0, 16, dump);
					//DEMOD_MCU_PRINT("check %u,%u,%u,%u\n", dump[0], dump[1], dump[2], dump[3]);
				}
				break;
			case CMD_TYPE_SYSTEM_REPORT:
				DEMOD_MCU_PRINT("MCU report: %s\n", (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_ERROR:
			case CMD_TYPE_ERROR_INVALID:
			case CMD_TYPE_ERROR_TIMEOUT:
			case CMD_TYPE_ERROR_FAULT:
			case CMD_TYPE_ERROR_HW:
			case CMD_TYPE_ERROR_IPC:
				DEMOD_MCU_ERROR("MCU error: ec x%02X, %s\n", bufh.typ & 0xFF, (bufh.len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh.len) : "null"));
				break;
			case CMD_TYPE_DEBUG_ON:
				DEMOD_MCU_PRINT("MCU REQ UART ON\n");
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
				DEMOD_Set_UART(TRUE);
#endif
				break;
			case CMD_TYPE_DEBUG_OFF:
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
				DEMOD_Set_UART(FALSE);
#endif
				DEMOD_MCU_PRINT("MCU REQ UART OFF\n");
				break;

			case CMD_TYPE_DEBUG_MSG:
				DEMOD_MCU_PRINT("MCU DBG: %s\n", DEMOD_BYTE_TO_CHARSTR(msg, bufh.len));
				break;
			case CMD_TYPE_DEBUG_MSG_HEX:
				DEMOD_MCU_PRINT("MCU HEX: %s\n", DEMOD_BYTE_TO_CHARSTR(msg, bufh.len));
				break;

			default:
				break;
			}
		}
	}
	//DEMOD_L0_UnlockDevice(core->chip);

	if (kfifo_len(&core->ipc->message.fifo) > 0) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		wake_up_interruptible(&core->ipc->message.wait);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
		pEvent->PulseEvent();
#endif
	}

	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Init(LX_DEMOD_L1_Context * core) {
	int err = NO_DEMOD_ERROR;
	
	DEMOD_INFO("%s\n", __FUNCTION__);

	DEMOD_L0_CBUF_Init(&core->ipc->tx, REG_KDRV_TO_MCU_HEAD, REG_KDRV_TO_MCU_TAIL, REG_KDRV_TO_MCU_STATE, REG_KDRV_TO_MCU_COUNT, REG_KDRV_TO_MCU_BASE, DEMOD_KDRV_TO_MCU_SIZE);
	DEMOD_L0_CBUF_Init(&core->ipc->rx, REG_MCU_TO_KDRV_HEAD, REG_MCU_TO_KDRV_TAIL, REG_MCU_TO_KDRV_STATE, REG_MCU_TO_KDRV_COUNT, REG_MCU_TO_KDRV_BASE, DEMOD_MCU_TO_KDRV_SIZE);

	core->ipc->tx.chip = (void *)core->chip;
	core->ipc->rx.chip = (void *)core->chip;

	INIT_KFIFO(core->ipc->message.fifo);

	_ipc_enable = FALSE;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	init_waitqueue_head(&core->ipc->message.wait);

#if defined(DEMOD_CONFIG_POLL)
	_ipc_polling_thread = kthread_run(_DBB_DEMOD_L1_IPC_POLL_Handler, (void *)core, "demod_ipc_polling");

	if (_ipc_polling_thread == NULL) {
		DEMOD_ERROR("failed create polling thread %d\n", _ipc_polling_thread);
		err = -ENOMEM;
	}
	DEMOD_DEBUG("kthread_run done\n");
#else

	if (_ipc_irq < 0) {
#if defined(DEMOD_CHIP_NAME_o20)
		_ipc_irq = O20_IRQ_INTR_TCON_CRC;
#else
		DEMOD_ERROR("not support platform\n");
		return RET_ERROR;;
#endif

		/* request_irq from mcu */
		err = request_irq(_ipc_irq , (irq_handler_t)_DBB_DEMOD_L1_IPC_IRQ_Handler, IRQF_TRIGGER_HIGH, "demod_ipc", (void *)core);

		if (err) {
			DEMOD_ERROR("error (%d) whilre request_irq (%d)\n", err, _ipc_irq);
			free_irq(_ipc_irq, NULL);
			return err;
		}

		disable_irq(_ipc_irq);
		DEMOD_DEBUG("request_irq done\n");
	}
#endif
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	pEvent = new CEvent(FALSE, FALSE);
	//_mutex_handler.mtx = new CMutex(FALSE, "handler");

	_mutex_handler.mtx = new CRITICAL_SECTION();
	InitializeCriticalSection(_mutex_handler.mtx);
	_mutex_handler.cnt = 0;
	_mutex_handler.tid = 0;

#endif
	
	core->ipc->init_done = 1;
	return err;
}

