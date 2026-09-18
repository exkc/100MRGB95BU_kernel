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

#define DEMOD_TAG "[L1.IPC] "

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

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV) && !defined(DEMOD_CONFIG_POLL)
/* IPC on interrupt handler */
static unsigned long irq_flags;

static int _DEMOD_L1_Lock_RespQueue(LX_DEMOD_L1_Context* core)
{
	spin_lock_irqsave(&core->ipc->message.lock, irq_flags);
	return NO_DEMOD_ERROR;
}

static int _DEMOD_L1_Unlock_RespQueue(LX_DEMOD_L1_Context* core)
{
	spin_unlock_irqrestore(&core->ipc->message.lock, irq_flags);
	return NO_DEMOD_ERROR;
}
#else
/* IPC on polling thread */
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
CEvent* pEvent = NULL;
#endif

static MUTEX_LOCK_T _mutex_handler;

static int _DEMOD_L1_Lock_RespQueue(LX_DEMOD_L1_Context* core)
{
	return DEMOD_L0_MUTEX_LOCK("handler", &_mutex_handler);
	return NO_DEMOD_ERROR;
}

static int _DEMOD_L1_Unlock_RespQueue(LX_DEMOD_L1_Context* core)
{
	return DEMOD_L0_MUTEX_UNLOCK("handler", &_mutex_handler);
	return NO_DEMOD_ERROR;
}
#endif

int DEMOD_L1_IPC_Send(LX_DEMOD_L1_Context * core, UINT32 typ, UINT32 seq, char *ptr, int len) {
	int retc = NO_DEMOD_ERROR;

	retc = DEMOD_L0_CBUF_Write(&core->ipc->tx, typ, seq, ptr, len);
	wmb();

	if (retc == NO_DEMOD_ERROR) {
		core->ipc->status.send_cnt++;
		DEMOD_DEBUG("send len %d, type 0x%04x, payloads %d, %s, retc 0x%02X\n", COMMAND_BSIZ + len, typ, len, (len > 0 ? DEMOD_BYTE_TO_HEXSTR(ptr, len) : "null"), -retc);
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

int DEMOD_L1_IPC_Send_Sync(LX_DEMOD_L1_Context * core, UINT32 typ, UINT32 seq, char *ptr, int len) {
	int ret = NO_DEMOD_ERROR;
	int retry = 0;

	retry = 10;
	do {
		ret = DEMOD_L1_IPC_Send (core, typ, seq, ptr, len);

		if ((NO_DEMOD_ERROR != ret) && (retry-- > 0))
			DEMOD_L0_system_wait(1);
		else
			break;
	} while (1);
	if (ret != NO_DEMOD_ERROR) {
		DEMOD_INFO("send typ 0x%04X, seq %d, fail, ret %d\n", typ, seq, -ret);
		return ret;
	}

#if defined(PLATFORM_FPGA)
	retry = 1000;
#else
	retry = 100;
#endif

	do {
		ret = DEMOD_L1_IPC_Send_Count(core);
		if ((ret > 0) && (retry-- > 0))
			DEMOD_L0_system_wait(1);
		else
			break;
	} while (1);
	if (ret > 0) {
		DEMOD_INFO("send typ 0x%04X, seq %d, timeout %d, ret %d\n", typ, seq, retry, ret);
		return -ERROR_DEMOD_IPC_TIMEOUT;
	}

	DEMOD_DEBUG("send typ 0x%04X, seq %d, done\n", seq, typ);
	return ret;

}

int DEMOD_L1_IPC_Recv(LX_DEMOD_L1_Context * core, UINT32 *ptyp, UINT32 * pseq, char *pdst) {
//	static char tmpbuf[MESSAGE_BMAX];
	int ret;

	CBUF_RAM_H ramh;

	ret = DEMOD_L1_IPC_Recv_Count(core);

	if (ret == 0) {
		DEMOD_ERROR("recv is empty\n");
		return -ERROR_DEMOD_IPC_EMPTY;
	}

	_DEMOD_L1_Lock_RespQueue(core);
	ret = DEMOD_L0_CBUF_RAM_Read(&core->ipc->message.fifo, &ramh, pdst);
	_DEMOD_L1_Unlock_RespQueue(core);

	if (ret == RET_OK) {
		*ptyp = ramh.typ;
		*pseq = ramh.seq;
	} else {
		core->ipc->status.recv_fail_cnt++;
		DEMOD_ERROR("invalid read length from _msg_fifo:retc 0x%02X, read_fail_cnt %u\n", -ret, core->ipc->status.recv_fail_cnt);
		return -ERROR_DEMOD_IPC_FALUT;
	}

	core->ipc->status.recv_cnt++;

	DEMOD_DEBUG("recv retc 0x%02X, type 0x%04x, payloads %d, %s\n", -ret, *ptyp, ramh.len, (ramh.len > 0 ? DEMOD_BYTE_TO_HEXSTR(pdst, ramh.len) : "null"));
	return ramh.len;
}

int DEMOD_L1_IPC_Recv_Count(LX_DEMOD_L1_Context * core) {
	int ret = DEMOD_L0_CBUF_RAM_Used(&core->ipc->message.fifo);
	return ret;
}

int DEMOD_L1_IPC_Recv_GetState(LX_DEMOD_L1_Context * core, UINT32 * pstate) {
	int ret = DEMOD_L0_CBUF_GetState(&core->ipc->rx, (cbuf_state *)pstate);
	rmb();
	return ret;
}

int DEMOD_L1_IPC_Wait(LX_DEMOD_L1_Context * core, int retry) {
	int ret = NO_DEMOD_ERROR;

	do {
		if (core->fw_state != DEMOD_FW_STATE_RUN) {
			DEMOD_ERROR("FW state changed %d\n", core->fw_state);
			return -ERROR_DEMOD_FW_NOT_READY;
		}

		DEMOD_DEBUG("wait until (recv count(%d) > 0) and (retry(%d) > 0)\n", DEMOD_L1_IPC_Recv_Count(core), retry);
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
		ret = wait_event_interruptible_timeout(core->ipc->message.wait, (DEMOD_L1_IPC_Recv_Count(core) > 0), msecs_to_jiffies(100));
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

	DEMOD_DEBUG("wait done with (recv count(%d)), retry(%d) and retc 0x%02X\n", DEMOD_L1_IPC_Recv_Count(core), retry, -ret);
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Wait_Cancel(LX_DEMOD_L1_Context * core) {
#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	wake_up_interruptible(&core->ipc->message.wait);
#elif (DEMOD_PLATFORM == DEMOD_PLATFORM_GUI)
	pEvent->PulseEvent();
#endif	
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Status_Fifo(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;
	dbgidx += SPRINTF(dbglog + dbgidx, "\tfifo   %8u, mesg %8u, fifo   %8u / %u\n", core->ipc->status.fifo_cnt, core->ipc->status.mesg_cnt, DEMOD_L0_CBUF_RAM_Used(&core->ipc->message.fifo), core->ipc->message.fifo.size);

	return dbgidx;
}

int DEMOD_L1_IPC_Status(LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\n\tIPC ON\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\tCBUF TX:  \t");
	dbgidx += DEMOD_L0_CBUF_Status(&core->ipc->tx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tCBUF RX:  \t");
	dbgidx += DEMOD_L0_CBUF_Status(&core->ipc->rx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tCBUF DBG: \t");
	dbgidx += DEMOD_L0_CBUF_Status(&core->ipc->dbg, dbglog + dbgidx);

	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\tintr   %8u, fail %8u, tout   %8u\n", 
		core->ipc->status.intr_cnt, core->ipc->status.intr_fail_cnt, core->ipc->status.tout_cnt);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tcb.apb %8u, fail %8u, cb.ddr %8u, fail %8u\n", 
		core->ipc->status.mdrv_cnt, core->ipc->status.mdrv_fail_cnt, core->ipc->status.mdbg_cnt, core->ipc->status.mdbg_fail_cnt);

	dbgidx += SPRINTF(dbglog + dbgidx, "\tsend   %8u, fail %8u, recv   %8u, fail %8u\n", core->ipc->status.send_cnt, core->ipc->status.send_fail_cnt, core->ipc->status.recv_cnt, core->ipc->status.recv_fail_cnt);
	dbgidx += SPRINTF(dbglog + dbgidx, "\tfifo   %8u, mesg %8u, fifo   %8u / %u\n", core->ipc->status.fifo_cnt, core->ipc->status.mesg_cnt, DEMOD_L0_CBUF_RAM_Used(&core->ipc->message.fifo), core->ipc->message.fifo.size);

	return dbgidx;
}

int DEMOD_L1_IPC_Dump (LX_DEMOD_L1_Context * core, char * dbglog) {
	int dbgidx = 0;

	dbgidx += SPRINTF(dbglog + dbgidx, "DEMOD_L1_IPC :\tIPC ON\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\nCBUF TX\n");
	dbgidx += DEMOD_L0_CBUF_Show(&core->ipc->tx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\nCBUF RX\n");
	dbgidx += DEMOD_L0_CBUF_Show(&core->ipc->rx, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");
	dbgidx += SPRINTF(dbglog + dbgidx, "\nCBUF DBG\n");
	dbgidx += DEMOD_L0_CBUF_Show(&core->ipc->dbg, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n\n");

	dbgidx += DEMOD_L1_Process_Dump(core, dbglog + dbgidx);
	dbgidx += SPRINTF(dbglog + dbgidx, "\n");

	return dbgidx;
}

int DEMOD_L1_IPC_Reset(LX_DEMOD_L1_Context * core) {
	UINT32 wtemp;

	DEMOD_L0_CBUF_Reset(&core->ipc->tx);
	DEMOD_L0_CBUF_Reset(&core->ipc->rx);
	DEMOD_L0_CBUF_Reset(&core->ipc->dbg);

	DEMOD_L0_CBUF_Clear(&core->ipc->tx);
	DEMOD_L0_CBUF_Clear(&core->ipc->rx);
	DEMOD_L0_CBUF_Clear(&core->ipc->dbg);

	wtemp = DEMOD_MAGIC_CODE;

	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes(core->chip, REG_FW_STATE, 4, &wtemp))
		return -ERROR_DEMOD_WRITE;

	_DEMOD_L1_Lock_RespQueue(core);
	DEMOD_L0_CBUF_RAM_Reset(&core->ipc->message.fifo);
	_DEMOD_L1_Unlock_RespQueue(core);

	memset(&core->ipc->status, 0, sizeof(LX_DEMOD_L1_IPC_Status));

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
	src &= 0xFFFFFF7F;
	if(NO_DEMOD_ERROR != DEMOD_L0_WriteCommandBytes_NoLock(core->chip, REG_INT_SRC, 4, &src)) {
		DEMOD_L0_Unlock_CommDevice(core->chip);
		return -ERROR_DEMOD_WRITE;
	}

	DEMOD_L0_Unlock_CommDevice(core->chip);
	return NO_DEMOD_ERROR;
}

int DEMOD_L1_IPC_Parser (LX_DEMOD_L1_Context * core, CBUF_H * bufh, char * recvbuf, int len) {
	int retc = NO_DEMOD_ERROR;

	char * msg = recvbuf + COMMAND_BSIZ;
	CBUF_RAM_H ramh;

	if (CMD_MAJOR_TYPE(bufh->typ) == CMD_MAJOR_TYPE_API) {
		DEMOD_DEBUG("recv %02X, %3u, %3u\n", bufh->typ, bufh->seq, bufh->len);
		ramh.typ = bufh->typ;
		ramh.seq = bufh->seq;
		ramh.len = bufh->len;

		core->ipc->status.fifo_cnt++;

		_DEMOD_L1_Lock_RespQueue(core);
		retc = DEMOD_L0_CBUF_RAM_Write(&core->ipc->message.fifo, &ramh, msg);
		_DEMOD_L1_Unlock_RespQueue(core);

	} else {
		core->ipc->status.mesg_cnt++;
		switch (bufh->typ) {
		case CMD_TYPE_SYSTEM_INIT:
				DEMOD_MCU_PRINT("MCU Init: %s\n", (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
			break;
		case CMD_TYPE_SYSTEM_READY:
			DEMOD_MCU_PRINT("MCU Ready: %s\n", (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
			break;
		case CMD_TYPE_SYSTEM_START:
			DEMOD_MCU_PRINT("MCU Start: %s\n", (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
			break;
		case CMD_TYPE_SYSTEM_STOP:
			DEMOD_MCU_PRINT("MCU Stop: %s\n", (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
			break;
		case CMD_TYPE_SYSTEM_ALIVE:
			{
				static unsigned int alive_check = 0;
				unsigned int spend_check = 0;
//				unsigned int dump[4];

				if (alive_check > 0)
					spend_check = DEMOD_L0_CalcSpendTime(alive_check);

				DEMOD_MCU_DEBUG("MCU alive: period %u, %s\n", spend_check, (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
				alive_check = DEMOD_L0_system_time();
			}
			break;
		case CMD_TYPE_SYSTEM_REPORT:
			DEMOD_MCU_ERROR("MCU report: %s\n", (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
			break;
		case CMD_TYPE_ERROR:
		case CMD_TYPE_ERROR_INVALID:
		case CMD_TYPE_ERROR_TIMEOUT:
		case CMD_TYPE_ERROR_FAULT:
		case CMD_TYPE_ERROR_HW:
		case CMD_TYPE_ERROR_IPC:
			DEMOD_MCU_ERROR("MCU error: ec x%02X, %s\n", bufh->typ & 0xFF, (bufh->len > 0 ? DEMOD_BYTE_TO_CHARSTR(msg, bufh->len) : "null"));
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

		case CMD_TYPE_PRINT_MSG:
			DEMOD_MCU_PRINT("MCU PRINT: %s\n", DEMOD_BYTE_TO_CHARSTR(msg, bufh->len));
			break;
		case CMD_TYPE_DEBUG_MSG:
			DEMOD_MCU_DEBUG("MCU DEBUG: %s\n", DEMOD_BYTE_TO_CHARSTR(msg, bufh->len));
			break;
		case CMD_TYPE_DEBUG_MSG_HEX:
			DEMOD_MCU_DEBUG("MCU HEX: %s\n", DEMOD_BYTE_TO_HEXSTR(msg, bufh->len));
			break;
		case CMD_TYPE_ECHO_APB:
		case CMD_TYPE_ECHO_DDR:
			DEMOD_MCU_PRINT("ECHO: %04X,#%u,%u, %s\n", bufh->typ, bufh->seq, bufh->len, DEMOD_BYTE_TO_CHARSTR(msg, bufh->len));
			break;
		default:
			break;
		}
	}

	return retc;
}

static char _cbuf_ram_buff[1024];

int DEMOD_L1_IPC_Init(LX_DEMOD_L1_Context * core) {
	int err = NO_DEMOD_ERROR;
	
	DEMOD_INFO("%s\n", __FUNCTION__);

	DEMOD_L0_CBUF_Init(&core->ipc->tx, REG_KDRV_TO_MCU_HEAD, REG_KDRV_TO_MCU_TAIL, REG_KDRV_TO_MCU_STATE, REG_KDRV_TO_MCU_BASE, DEMOD_KDRV_TO_MCU_SIZE);
	DEMOD_L0_CBUF_Init(&core->ipc->rx, REG_MCU_TO_KDRV_HEAD, REG_MCU_TO_KDRV_TAIL, REG_MCU_TO_KDRV_STATE, REG_MCU_TO_KDRV_BASE, DEMOD_MCU_TO_KDRV_SIZE);

	core->ipc->tx.chip = (void *)core->chip;
	core->ipc->rx.chip = (void *)core->chip;

	core->ipc->message.fifo.base = (UINT32 *)&_cbuf_ram_buff[0];
	core->ipc->message.fifo.size = sizeof(_cbuf_ram_buff);

	DEMOD_L0_CBUF_RAM_Reset(&core->ipc->message.fifo);

	DEMOD_L0_CBUF_Init(&core->ipc->dbg, DDR_MCU_TO_DBG_HEAD, DDR_MCU_TO_DBG_TAIL, DDR_MCU_TO_DBG_STATE, DDR_MCU_TO_DBG_BASE, DEMOD_MCU_TO_DBG_SIZE);
	core->ipc->dbg.chip = (void *)core->chip;

#if (DEMOD_PLATFORM == DEMOD_PLATFORM_KDRV)
	init_waitqueue_head(&core->ipc->message.wait);

#if defined(DEMOD_CONFIG_POLL)
	OS_InitMutex(&_mutex_handler.mtx, OS_SEM_ATTR_DEFAULT);
	_mutex_handler.cnt = 0;
	_mutex_handler.tid = 0;	
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

