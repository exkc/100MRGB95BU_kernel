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

#ifndef __DBB_DEMOD_L1_IPC__
#define __DBB_DEMOD_L1_IPC__

#if !defined(__DEMOD_MCU_IPC__)
#include "DBB_DEMOD_L0_API.h"
#include "DBB_DEMOD_L0_CBUF.h"
#include "DBB_DEMOD_L0_CBUF_RAM.h"
#endif

#define DEMOD_L1_IPC_DUMP_MAX	0x400	/* 1024 */

#define COMMAND_BSIZ			(int)(sizeof(CBUF_H))
#define	COMMAND_WSIZ			(COMMAND_BSIZ >> 2)

#define PAYLOAD_BMAX			(128)
#define PAYLOAD_WMAX			(PAYLOAD_BMAX >> 2)

#define MESSAGE_BMAX			(COMMAND_BSIZ + PAYLOAD_BMAX)
#define MESSAGE_WMAX			(MESSAGE_BMAX >> 2)

/* command : common */
#define CMD_TYPE(major, minor)		((major << 8) | (minor & 0xFF))
#define CMD_MAJOR_TYPE(type)		((type >> 8) & 0xFF)
#define CMD_MINOR_TYPE(type)		(type & 0xFF)

#define CMD_MAJOR_TYPE_DEBUG		0xDB

#define CMD_TYPE_DEBUG_OFF		CMD_TYPE(CMD_MAJOR_TYPE_DEBUG, 0xD0)
#define CMD_TYPE_DEBUG_ON		CMD_TYPE(CMD_MAJOR_TYPE_DEBUG, 0xD1)
#define CMD_TYPE_DEBUG_MSG		CMD_TYPE(CMD_MAJOR_TYPE_DEBUG, 0x80)
#define CMD_TYPE_DEBUG_MSG_HEX		CMD_TYPE(CMD_MAJOR_TYPE_DEBUG, 0x81)
#define CMD_TYPE_PRINT_MSG		CMD_TYPE(CMD_MAJOR_TYPE_DEBUG, 0x82)


#define CMD_MAJOR_TYPE_SYSTEM		0x10
#define CMD_TYPE_SYSTEM_CHECK		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x80)
#define CMD_TYPE_SYSTEM_REPORT		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x81)
#define CMD_TYPE_SYSTEM_ALIVE		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x8F)


#define CMD_TYPE_SYSTEM_INIT		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x11)
#define CMD_TYPE_SYSTEM_READY		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x12)
#define CMD_TYPE_SYSTEM_START		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x13)
#define CMD_TYPE_SYSTEM_STOP		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x14)
#define CMD_TYPE_SYSTEM_UART_ON		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x15)
#define CMD_TYPE_SYSTEM_UART_OFF	CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x16)
#define CMD_TYPE_SYSTEM_HEX_ON		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x17)
#define CMD_TYPE_SYSTEM_HEX_OFF		CMD_TYPE(CMD_MAJOR_TYPE_SYSTEM, 0x18)

#define CMD_MAJOR_TYPE_TEST			0xC0
#define CMD_TYPE_TEST_CHECK			CMD_TYPE(CMD_MAJOR_TYPE_TEST, 0x00)
#define CMD_TYPE_TEST_TIMEOUT		CMD_TYPE(CMD_MAJOR_TYPE_TEST, 0x70)
#define CMD_TYPE_TEST_FTIMEOUT		CMD_TYPE(CMD_MAJOR_TYPE_TEST, 0x71)

#define CMD_MAJOR_TYPE_ERROR		0xEE
#define CMD_TYPE_ERROR				CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x00)
#define CMD_TYPE_ERROR_INVALID		CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x01)
#define CMD_TYPE_ERROR_TIMEOUT		CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x02)
#define CMD_TYPE_ERROR_FWRESET		CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x03)
#define CMD_TYPE_ERROR_FAULT		CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x04)
#define CMD_TYPE_ERROR_HW			CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x10)
#define CMD_TYPE_ERROR_IPC			CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0x40)
#define CMD_TYPE_ERROR_DEBUG		CMD_TYPE(CMD_MAJOR_TYPE_ERROR, 0xDD)

#define CMD_MAJOR_TYPE_ECHO			0xEC
#define CMD_TYPE_ECHO_APB			CMD_TYPE(CMD_MAJOR_TYPE_ECHO, 0x01)
#define CMD_TYPE_ECHO_DDR			CMD_TYPE(CMD_MAJOR_TYPE_ECHO, 0x02)

#define CMD_MAJOR_TYPE_API		0x00

#if !defined(__DEMOD_MCU_IPC__)
typedef struct demod_ipc_status {
	unsigned int send_cnt;			// kdrv to mcu
	unsigned int send_fail_cnt;
	unsigned int recv_cnt;			// api recv via cbuf_ram
	unsigned int recv_fail_cnt;
	unsigned int tout_cnt;			// time out
	unsigned int intr_cnt;
	unsigned int intr_fail_cnt;
	unsigned int mdrv_cnt;			// mcu to kdrv
	unsigned int mdrv_fail_cnt;
	unsigned int mdbg_cnt;			// mcu to dbg
	unsigned int mdbg_fail_cnt;
	unsigned int mesg_cnt;			// recv mcu message count (include debug message)
	unsigned int fifo_cnt;			// recv api count
} LX_DEMOD_L1_IPC_Status;


typedef struct msg_fifo_struct {
	CBUF_RAM_T					fifo;
#ifdef __KERNEL__
	spinlock_t					lock;
	wait_queue_head_t			wait;
#else
	MUTEX_LOCK_T				lock;
#endif
} LX_DEMOD_L1_IPC_Message;

typedef struct {
	LX_DEMOD_L1_IPC_Status	status;
	LX_DEMOD_L1_IPC_Message	message;

	CBUF_T	tx;
	CBUF_T	rx;
	CBUF_T	dbg;

	UINT8	init_done;
} LX_DEMOD_L1_IPC;
#endif
#endif //__DBB_DEMOD_L1_IPC__

