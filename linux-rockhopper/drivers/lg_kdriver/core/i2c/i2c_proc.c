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
 *  Linux proc interface for i2c device.
 *	i2c device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_i2c
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
#include "i2c_drv.h"
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
	PROC_ID_DEBUGCH,
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
static OS_PROC_DESC_TABLE_T	_g_i2c_device_proc_table[] =
{
	{ "author",		PROC_ID_AUTHOR  , OS_PROC_FLAG_READ },
	{ "sw_cfg",		PROC_ID_SW_CFG  , OS_PROC_FLAG_READ },
	{ "command",	PROC_ID_COMMAND , OS_PROC_FLAG_WRITE },
	{ "debugch",	PROC_ID_DEBUGCH			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 		PROC_ID_MAX		, 0 }
};

void	I2C_PROC_Init (void);
void	I2C_PROC_Cleanup (void);
/*========================================================================================
	Implementation Group
========================================================================================*/

/*
 * read_proc implementation of i2c device
 *
*/
static int	_I2C_ReadProcFunction(	UINT32 procId, char* buffer )
{
	int		ret;

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_AUTHOR:
		{
			ret = snprintf(buffer,48, "%s\n", "ingyu.yang (ingyu.yang@lge.com)" );
		}
		break;

		case PROC_ID_SW_CFG:
		{
			ret = snprintf(buffer,48, "0x%x\n", lx_i2c_cfg() );
		}
		break;

		case PROC_ID_DEBUGCH:
		{
			ret = snprintf( buffer,48, "DEBUG_CH[15:8]_DEVNO[7:0]:%x\n", debug_ch_devno );
		}
		break;

		default:
		{
			ret = snprintf( buffer,48,"%s(%d)\n", "unimplemented read proc", procId );
		}
	}

	return ret;
}

/*
 * write_proc implementation of i2c device
 *
*/
static int _I2C_WriteProcFunction( UINT32 procId, char* command )
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
		case PROC_ID_DEBUGCH:
		{
			input_n = sscanf(command,"%x\n", &input_value);
			debug_ch_devno = input_value;
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

/**
 * initialize proc utility for i2c device
 *
 * @see I2C_Init
*/
void	I2C_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( I2C_MODULE, _g_i2c_device_proc_table,
											_I2C_ReadProcFunction,
											_I2C_WriteProcFunction );
}

/**
 * cleanup proc utility for i2c device
 *
 * @see I2C_Cleanup
*/
void	I2C_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( I2C_MODULE );
}

/** @} */

