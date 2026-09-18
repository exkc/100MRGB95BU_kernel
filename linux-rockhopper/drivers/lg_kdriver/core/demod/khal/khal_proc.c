/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file
 *
 *  proc utility for khal_demod device.
 *
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

//#include "sys_regs.h"
#include "demod_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "demod_impl.h"
#if defined(DEMOD_CONFIG_LGDBB_IPC)
#include "demod_util.h"
#endif
#include "demod_module.h"
#include "demod_hw.h"

#include "demod_khal.h"
#include "khal_proc.h"


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_USAGE	= 0,
	PROC_ID_INIT,
	PROC_ID_MAX,
};

#define MAX_VALUE	0xFFFFFFFF
#define MAX_ADDRESS	0xFFFFFFFF
/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T	_khal_demod_proc_table[] =
{
	{ "usage",			PROC_ID_USAGE,		OS_PROC_FLAG_READ},
	{ "init",			PROC_ID_INIT,		OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE},
	{ NULL, 			PROC_ID_MAX,		0}
};

/*----------------------------------------------------------------------------------------
	Static Function Implementation
----------------------------------------------------------------------------------------*/
static int _khal_demod_read_proc (UINT32 procId, char* buffer)
{
	int ret = 0;

	DEMOD_NOTI("procId %u\n", procId);

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_USAGE:
			ret += sprintf(buffer + ret, 
					"* khal demod\n"
					"  - init\n"
				      );
			break;
		case PROC_ID_INIT:
			ret += sprintf(buffer + ret, 
					"* kahl init usage\n"
					"  - echo n > /proc/lg/demod/khal/init\n"
					"  - n value\n"
					"	1: VQI SW Init\n"
					"	2: DVB SW Init\n"
					"	3: VQI_DTMB SW Init\n"
					"	4: ATSC3 SW Init\n"
				      );
			break;
		default:
			break;
	}

	return ret;
}

static int _khal_demod_write_proc (UINT32 procId, char* command)
{
	int arg1;

	DEMOD_NOTI("procId %u, command %s\n", procId, command);

	switch(procId) 	{
		case PROC_ID_INIT:
			sscanf(command, " %d", &arg1);
			switch(arg1) {
				case 1:
					KHAL_DEMOD_VQI_Initialize();
					break;
				case 2:
					KHAL_DEMOD_DVB_Initialize();
					break;
				case 3:
					KHAL_DEMOD_VQI_DTMB_Initialize();
					break;
				case 4:
					KHAL_DEMOD_ATSC3_Initialize();
					break;
				case 0:
				default:
					DEMOD_WARN("invalid arg1 %u\n", arg1);
					break;
			}
			break;
		default:
			DEMOD_WARN("N/I procId\n");
			break;
	}

	return strlen(command);
}

/*========================================================================================
	Implementation Group
========================================================================================*/
void	khal_demod_proc_init(void)
{
	OS_PROC_CreateEntryEx("demod_khal", _khal_demod_proc_table,
					_khal_demod_read_proc,
					_khal_demod_write_proc);
}

void	khal_demod_proc_cleanup(void)
{
	OS_PROC_RemoveEntry("demod_khal");
}

/** @} */
