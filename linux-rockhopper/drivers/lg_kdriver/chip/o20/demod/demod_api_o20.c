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
 *	demod O20 api
 *
 *	@author 	samin.ryu
 *	@version	1.0
 *	@date		2019-06-13
 *	@note
 */

#define DEMOD_TAG "[CHIP.API] "

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

int DEMOD_O20_API_Suspend (void) {
	LX_DEMOD_L2_Context * frontend = NULL;

	frontend = DEMOD_O20_GetContext();

	DEMOD_INFO("set fw_type invalid to entering suspend\n");

#if defined(DEMOD_CHIP_NAME_o20)
	frontend->demod->chip->fw_type = DEMOD_FW_TYPE_INV;
#endif

	return RET_OK;
}

int DEMOD_O20_API_Status(char * pDbglog, int * pDbgidx) {

	LX_DEMOD_L2_Context * frontend = NULL;

	frontend = DEMOD_O20_GetContext();

	*pDbgidx = DEMOD_L1_API_Status(frontend->demod, pDbglog);

	return RET_OK;
}

int DEMOD_O20_API_Dump(char * pDbglog, int * pDbgidx) {
	LX_DEMOD_L2_Context * frontend = DEMOD_O20_GetContext();

	*pDbgidx = DEMOD_L1_API_Dump(frontend->demod, pDbglog);
	
	return RET_OK;
}


