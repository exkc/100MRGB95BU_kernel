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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  Linux proc interface for gpio device.
 *	gpio device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_gpio
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
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>


#include "gpio_drv.h"
#include "gpio_core.h"
#include "os_util.h"
#include "proc_util.h"
#include "debug_util.h"

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
	PROC_ID_SW_CFG,
	PROC_ID_COMMAND,
	PROC_ID_DEBUGPIN,
	PROC_ID_DIRECTION,
	PROC_ID_VALUE,
	PROC_ID_STATUS,
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
static void _GPIO_PrintStatus(struct seq_file *m, void* data);

OS_PROC_SEQRD_DEFINE_EX(gpio_status_proc_fops, _GPIO_PrintStatus,NULL)

int isExistFile(struct seq_file *m, int pin);
static void _GPIO_PrintStatus(struct seq_file *m, void* data);
int	_GPIO_ReadProcFunction(	UINT32 procId, char* buffer );
int _GPIO_WriteProcFunction( UINT32 procId, char* command );
void	GPIO_PROC_Init (void);
void	GPIO_PROC_Cleanup (void);

static OS_PROC_DESC_TABLE_T	_g_gpio_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "sw_cfg",		PROC_ID_SW_CFG	, OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND	, OS_PROC_FLAG_WRITE },
	{ "debugpin",	PROC_ID_DEBUGPIN			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "direction",	PROC_ID_DIRECTION			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "val",	PROC_ID_VALUE			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "status",        		    PROC_ID_STATUS,     OS_PROC_FLAG_SEQRD, (void*)&gpio_status_proc_fops },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * read_proc implementation of gpio device
 *
*/
int isExistFile(struct seq_file *m, int pin) {
	struct file *fp;
	char fname[100];

#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)
#else
	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);
#endif

	snprintf(fname,48,"/sys/class/gpio/gpio%d/value",pin);
	fp = filp_open(fname, O_RDONLY, 0);

	if (IS_ERR(fp)) {
			return 1;
	}
	else {
			//printk("open success\n");
			filp_close(fp, NULL);  /* filp_close(filp, current->files) ?  */
			/* restore kernel memory setting */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(6,12,0)
#else
			set_fs(old_fs);
#endif
			return 0;
	}
}

static void _GPIO_PrintStatus(struct seq_file *m, void* data)
{
	int i= 0, ret =0;

	seq_printf( m, "-------------------------------------- \n");
	seq_printf( m, "     PIN NO     DIRECTION     VALUE \n");
	seq_printf( m, "-------------------------------------- \n");
	for( i = 0 ; i < 144 ; i++)
	{
		ret =isExistFile(m,i);
		if( ret == 0)
		{
		debugpindir = _GPIO_GetModeEx(debugpin);
			debugpindir = _GPIO_GetValueEx(debugpin);
			seq_printf( m, "     %3d          %s          %d \n",i,(_GPIO_GetModeEx(i))?"OUT":" IN",_GPIO_GetValueEx(i));
		}
	}
	seq_printf( m, "-------------------------------------- \n");

	//seq_printf( m, "governor: %s\n", pm_m17_gov->get_gov_str(pm_m17_gov->get_gov()) );
}

int	_GPIO_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf( buffer,48, "%s\n", "ingyu.yang (ingyu.yang@lge.com)" );
		}
		break;

		case PROC_ID_SW_CFG:
		{
			ret = snprintf( buffer, 48, "0x%x\n", lx_gpio_cfg());
		}
		break;

		case PROC_ID_DEBUGPIN:
		{
			ret = snprintf( buffer,48, "DEBUG PIN: %d\n", debugpin );
		}
		break;

		case PROC_ID_DIRECTION:
		{
			debugpindir = _GPIO_GetModeEx(debugpin);
			ret = snprintf( buffer,48, "%d\n", debugpindir );
		}
		break;

		case PROC_ID_VALUE:
		{
			debugpinval = _GPIO_GetValueEx(debugpin);
			ret = snprintf( buffer,48, "%d\n", debugpinval );
		}
		break;

		case PROC_ID_STATUS:
		{
			debugpinval = _GPIO_GetValueEx(debugpin);
			ret = snprintf( buffer,48, "%d\n", debugpinval );
		}
		break;

		default:
		{
			ret = snprintf( buffer,48, "%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

/**
 * write_proc implementation of gpio device
 *
*/
int _GPIO_WriteProcFunction( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_COMMAND:
		{
			printk("command string : %s\n", command );
		}
		break;
		case PROC_ID_DEBUGPIN:
		{
			input_n = sscanf(command,"%u\n", &input_value);
			debugpin = input_value;
		}
		break;

		case PROC_ID_DIRECTION:
		{
			input_n = sscanf(command,"%u\n", &input_value);
			debugpindir = input_value;
		}
		break;

		case PROC_ID_VALUE:
		{
			input_n = sscanf(command,"%u\n", &input_value);
			debugpinval = input_value;
		}

		default:
		{
			/* do nothing */
		}
		break;
	}

	return strlen(command);
}

/**
 * initialize proc utility for gpio device
 *
 * @see GPIO_Init
*/
void	GPIO_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( GPIO_MODULE, _g_gpio_device_proc_table,
											_GPIO_ReadProcFunction,
											_GPIO_WriteProcFunction );
}

/**
 * cleanup proc utility for gpio device
 *
 * @see GPIO_Cleanup
*/
void	GPIO_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( GPIO_MODULE );
}

/** @} */

