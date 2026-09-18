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

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>		/* printk() */
#include <linux/types.h>		/* size_t */

#include "os_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#include "lgdbb/DBB_DEMOD_L2_Common_API.h"

#include "demod_common_o20.h"
#include "demod_ipc_o20.h"

static int 	_ipc_enable = FALSE;
#if defined(DEMOD_CONFIG_POLL)
static struct task_struct *
			_ipc_polling_thread = NULL;
#else
static int	_ipc_irq = -1;
#endif

int DEMOD_O20_IPC_Send (UINT32 type, UINT32 seq, char *ptr, UINT32 len) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();
	return DEMOD_L1_IPC_Send(frontend->demod, type, seq, ptr, len);
}

int DEMOD_O20_IPC_Status(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();
	int dbgidx = 0;

	dbgidx += sprintf(pDbglog + dbgidx, "ipc handler: %s, ", (_ipc_enable == TRUE ? "enabled" : "disabled"));
#if defined(DEMOD_CONFIG_POLL)
	dbgidx += sprintf(pDbglog + dbgidx, "polling with kthread\n");
#else
	dbgidx += sprintf(pDbglog + dbgidx, "isr with irq %d\n", _ipc_irq);
#endif

	dbgidx += DEMOD_L1_IPC_Status(frontend->demod, pDbglog + dbgidx);

	*pDbgidx = dbgidx;
	return RET_OK;
}

int DEMOD_O20_IPC_Dump(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();
	int dbgidx = 0;

	dbgidx += DEMOD_L1_IPC_Dump(frontend->demod, pDbglog + dbgidx);

	*pDbgidx = dbgidx;
	return RET_OK;
}

int DEMOD_O20_IPC_Reset(void) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();

	return DEMOD_L1_IPC_Reset(frontend->demod);
}

int DEMOD_O20_IPC_Enable(int enable) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();

	return DEMOD_L1_IPC_Enable(frontend->demod, enable);
}

int DEMOD_O20_IPC_Init(void) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();

	return 	DEMOD_L1_IPC_Init(frontend->demod);
}





