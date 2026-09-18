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
 *  main driver implementation for micom device.
 *	micom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1210_micom
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
#include <linux/delay.h>
#include <asm/uaccess.h>
#include "os_util.h"
#include "base_device.h"
#include "ucom_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#include "ucom_m23_common.h"

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
	PROC_ID_UCOM_STATUS = 0,
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
//static ucom_m23_gov_t* ucom_m23_gov = NULL;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

static ucom_m23_func_t * ucom_func;
static ucom_driver_t* ucom_drv;


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

static OS_PROC_DESC_TABLE_T	_g_ucom_m23_device_proc_table[] =
{
	{ "status",				PROC_ID_UCOM_STATUS			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 				PROC_ID_MAX					, 0 }
};



/*========================================================================================
	Implementation Group
========================================================================================*/


/**
 * read_proc implementation of micom device
 *
*/


int	m23_read_proc(UINT32 procId, char* buffer );
int m23_write_proc( UINT32 procId, char* command );
void m23_ucom_proc_init (void);
void m23_ucom_proc_cleanup (void);

int	m23_read_proc(UINT32 procId, char* buffer )
{
	int	status=0,ret = 0 ;

	switch( procId )
	{
		case PROC_ID_UCOM_STATUS:
		{
			printk("status 0:cold 3:hot 7:unknown\n");
			status = ucom_func->getstatus();
			ret = snprintf( buffer,48, "%d\n", status);
		}
		break;

		default:
		{
			ret = snprintf( buffer,48,"%s(%d)\n", "unimplemented read proc", procId );
		}
		break;
	}

	return ret;
}
extern unsigned int ucom_gpionum;


int m23_write_proc( UINT32 procId, char* command )
{
	int ret = 0;
	switch( procId ) {

		case PROC_ID_UCOM_STATUS:

			break;


		default:
			ret = -1;
			break;
	}


	return strlen(command);;

}


/**
 * write_proc implementation of micom device
 *
*/





/**
 * initialize proc utility for micom device
 *
 * @see UCOM_Init
*/
void m23_ucom_proc_init (void)
{
	ucom_func	= get_m23_ucom_func();
	ucom_drv =  get_m23_ucom_driver();


	OS_PROC_CreateEntryEx ( UCOM_MODULE, _g_ucom_m23_device_proc_table,
										m23_read_proc,
										m23_write_proc );

}
/**
 * cleanup proc utility for micom device
 *
 * @see UCOM_Cleanup
*/
void m23_ucom_proc_cleanup (void)
{
	OS_PROC_RemoveEntry( UCOM_MODULE );
}

static ucom_proc_t m23_proc_func =
{
	.init = m23_ucom_proc_init,
	.cleanup = m23_ucom_proc_cleanup,
};

ucom_proc_t* get_m23_ucom_proc(void)
{
	return &m23_proc_func;
}

