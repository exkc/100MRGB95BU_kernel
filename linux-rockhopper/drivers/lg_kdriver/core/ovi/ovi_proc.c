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



/** @file
 *
 *  Linux proc interface for ovi device.
 *	ovi device will teach you how to make device driver with new platform.
 *
 *  author		dj911.kim@lge.com
 *  version		1.0
 *  date		2012.09.09
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
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
#include "ovi_drv.h"
#include "ovi_hal.h"
#include "ovi_cfg.h"
#include "proc_util.h"
#include "debug_util.h"
#include <linux/seq_file.h>

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
enum {
	PROC_ID_AUTHOR	= 0,
	PROC_ID_COMMAND,
	PROC_ID_CC_COUNT,
	PROC_ID_STATUS,
	PROC_ID_PATTERN,
	PROC_ID_DEBUG_FUNCTION,
	PROC_ID_MAX,
};

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
static void _OVI_PROC_PrintStatus(struct seq_file *m, void* data);
static void _OVI_PROC_FunctionTest(char* command);

OS_PROC_SEQRD_DEFINE_EX(ovi_status_proc_fops, _OVI_PROC_PrintStatus, NULL)

void	OVI_PROC_Init (void);
void	OVI_PROC_Cleanup (void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static OS_PROC_DESC_TABLE_T	_g_ovi_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "cc_count",	PROC_ID_CC_COUNT, OS_PROC_FLAG_READ },
	{ "status",		PROC_ID_STATUS,	  OS_PROC_FLAG_SEQRD, (void*)&ovi_status_proc_fops },
	{ "pat",		PROC_ID_PATTERN , OS_PROC_FLAG_WRITE },
	{ "dbg_func",	PROC_ID_DEBUG_FUNCTION , OS_PROC_FLAG_WRITE },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of ovi device
 *
*/
static int	_OVI_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret = 0;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer, 50, "%s\n", "dj911.kim@lge.com" );
		}
		break;

		case PROC_ID_CC_COUNT:
		{
		}
		break;

		default:
		{
			ret = snprintf( buffer, 50, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

/*
 * write_proc implementation of ovi device
 *
*/
static int _OVI_WriteProcFunction( UINT32 procId, char* command )
{
	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );			

			OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_DEBUG, NULL, (void *)command);
		}
		break;
		case PROC_ID_PATTERN:
		{
			int val;
			printk("command string : %s\n", command );
			sscanf(command, "%d", &val);
			OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_DRAW_PATTERN, NULL, (void *)&val);
		}
		break;
		case PROC_ID_DEBUG_FUNCTION:
		{
			printk("command string : %s\n", command );
	
			_OVI_PROC_FunctionTest(command);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

/** print OVI kdriver status
 *
 */
static void _OVI_PROC_PrintStatus(struct seq_file *m, void* data)
{
	OVI_HAL_ProcHandler(OVI_HAL_PROC_ID_DETAIL_INFO, m, data);
}

static void _OVI_PROC_FunctionTest(char* command)
{
	char funcName[30];
	int tId;

	sscanf(command, "%s %d", funcName, &tId);

	if (!strncmp(funcName, "channelpower", 12)) {
		printk("	OVI_HAL_SetChannelPower() = %d \n", OVI_HAL_SetChannelPower(tId));
	}
}

/**
 * initialize proc utility for ovi device
 *
 * @see OVI_Init
*/
void	OVI_PROC_Init (void)
{
	OS_PROC_CreateEntryEx  ( OVI_MODULE,   _g_ovi_device_proc_table,
											_OVI_ReadProcFunction,
											_OVI_WriteProcFunction );
}

/**
 * cleanup proc utility for ovi device
 *
 * @see OVI_Cleanup
*/
void	OVI_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( OVI_MODULE );
}

/** @} */

