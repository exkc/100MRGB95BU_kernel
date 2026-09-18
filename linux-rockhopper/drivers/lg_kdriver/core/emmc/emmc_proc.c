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
/*
 * @file
 *
 *  main driver implementation for pm device.
 *	pm device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2015.07.17
 *  note			Additional information.
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
#include "os_util.h"
#include "base_device.h"
#include "proc_util.h"
#include "debug_util.h"
#include "emmc_drv.h"

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
	PROC_ID_INTAP,
	PROC_ID_OUTTAP,
	PROC_ID_DS,
	PROC_ID_CNTR_DUMP,
	PROC_ID_TOP_TUMP,
	PROC_ID_MAX,
};

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
emmc_func_t* get_emmc_func(void);

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
static OS_PROC_DESC_TABLE_T _g_emmc_device_proc_table[] =
{
	{ "intap",					PROC_ID_INTAP			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "outtap", 				PROC_ID_OUTTAP			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "driverstrength", 		PROC_ID_DS				, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "cntr_dump", 				PROC_ID_CNTR_DUMP		, OS_PROC_FLAG_READ },
	{ "top_dump", 				PROC_ID_TOP_TUMP		, OS_PROC_FLAG_READ },
	{ NULL, 					PROC_ID_MAX 			, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/

static int	emmc_read_proc(UINT32 procId, char* buffer )
{
	int	ret = 0 ;
	emmc_func_t *emmc_func = NULL;

	emmc_func = get_emmc_func();

	switch( procId ) {
		case PROC_ID_INTAP:
			ret = sprintf( buffer, "%u\n", emmc_func->GetEmmcIntap());
			break;
		case PROC_ID_OUTTAP:
			ret = sprintf( buffer, "%u\n", emmc_func->GetEmmcOuttap());
			break;
		case PROC_ID_DS:
			ret = sprintf( buffer, "%u\n", emmc_func->GetEmmcHostDS());
			break;
		case PROC_ID_CNTR_DUMP:
			emmc_func->CntrRegDump();
			break;
		case PROC_ID_TOP_TUMP:
			emmc_func->TopRegDump();
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

static int emmc_write_proc( UINT32 procId, char* command )
{
	unsigned int input_value;
	unsigned int input_n;
	int ret = 0;
	emmc_func_t *emmc_func = NULL;

	emmc_func = get_emmc_func();


	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_INTAP:
			input_n = sscanf(command,"%u\n", &input_value);
			ret = emmc_func->SetEmmcIntap(input_value);
			break;
		case PROC_ID_OUTTAP:
			input_n = sscanf(command,"%u\n", &input_value);
			ret = emmc_func->SetEmmcOuttap(input_value);
			break;
		case PROC_ID_DS:
			input_n = sscanf(command,"%u\n", &input_value);
			ret = emmc_func->SetEmmcHostDS(input_value);
			break;
		default:
			ret = -1;
			break;
	}

	return strlen(command);
}

void EMMC_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( EMMC_MODULE, _g_emmc_device_proc_table,
										emmc_read_proc,
										emmc_write_proc );
}

void EMMC_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( EMMC_MODULE );
}

/** @} */


