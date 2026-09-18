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
 *  proc utility for template device.
 *
 *  author		author
 *  version     1.0
 *  date        20xx.xx.xx
 *
 *  @addtogroup lg115x_template
 *  @{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"
#include "proc_util.h"
#include "template_impl.h"
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
	PROC_ID_RW_TEST		= 0,	/* proc read & write test */
	PROC_ID_SEQ_RW_TEST	= 1,	/* sequential read & write test */
	/* TODO: add your own proc id */
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

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
OS_PROC_SEQRW_DEFINE_EX(template_seq_rw_test_fops, _TEMPLATE_SeqReadTestFunc, _TEMPLATE_SeqWriteTestFunc)

static OS_PROC_DESC_TABLE_T _g_template_device_proc_table[] =
{
	{ "rw_test",		PROC_ID_RW_TEST, 		OS_PROC_FLAG_READ|OS_PROC_FLAG_WRITE},
	{ "seq_rw_test",	PROC_ID_SEQ_RW_TEST,	OS_PROC_FLAG_SEQRW, (void*)&template_seq_rw_test_fops},
	/* TODO: add your own proc description */
	{ NULL,				PROC_ID_MAX,			0 }

};

/*----------------------------------------------------------------------------------------
	Static Function Implementation
----------------------------------------------------------------------------------------*/
static int	_TEMPLATE_SimpleReadProcHandler(UINT32 procId, char* buffer)
{
	int		ret;

	switch(procId)
	{
		case PROC_ID_RW_TEST:
		{
			ret = sprintf( buffer, "%s\n", "<usage> echo string > rw_test");
		}
		break;

		default:
		{
			ret = sprintf( buffer, "%s(%d)\n", "unimplemented proc", procId);
		}
	}

	return ret;
}

static int _TEMPLATE_SimpleWriteProcHandler(UINT32 procId, char* cmdbuf)
{
	switch(procId)
	{
		case PROC_ID_RW_TEST:
		{
			TEMPLATE_WARN("input = (%s)\n", cmdbuf);
		}
		break;

		default: /* do nothing */ break;
	}

	return strlen(cmdbuf);
}

static void	_TEMPLATE_SeqReadTestFunc(struct seq_file *m)
{
	int	i;
	for (i=0;i<5;i++) seq_printf(m, "test line %d\n", i);
}

static ssize_t _TEMPLATE_SeqWriteTestFunc(struct file *file, const char __user *buf, size_t size, loff_t *off)
{
	char cmdbuf[64];

	if(size==0) return 0;

	TEMPLATE_CHECK_WARN(*off!=0, return RET_ERROR, "multi write not supported\n");
	TEMPLATE_CHECK_WARN(size>sizeof(cmdbuf)-1, return RET_ERROR, "user buf is too long\n");

	TEMPLATE_CHECK_WARN(copy_from_user(cmdbuf, buf, size)>0, return RET_ERROR, "copy error\n");
	cmdbuf[size-1]= 0;

	TEMPLATE_WARN("input = (%s)\n", cmdbuf);

	return size;
}

/*========================================================================================
	Implementation Group
========================================================================================*/
void	TEMPLATE_PROC_Init (void)
{
	OS_PROC_CreateEntryEx(TEMPLATE_MODULE, _g_template_device_proc_table, _TEMPLATE_SimpleReadProcHandler, _TEMPLATE_SimpleWriteProcHandler);
}

void	TEMPLATE_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry(TEMPLATE_MODULE);
}

/** @} */
