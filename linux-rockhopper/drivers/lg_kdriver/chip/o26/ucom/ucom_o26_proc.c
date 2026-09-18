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

#include "ucom_o26_common.h"

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
	PROC_ID_UCOM_SPI_R = 1,
	PROC_ID_UCOM_SPI_W = 2,
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
//static ucom_o26_gov_t* ucom_o26_gov = NULL;


/*----------------------------------------------------------------------------------------
	Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/

static ucom_o26_func_t * ucom_func;
static ucom_driver_t* ucom_drv;


/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

static OS_PROC_DESC_TABLE_T	_g_ucom_o26_device_proc_table[] =
{
	{ "status",				PROC_ID_UCOM_STATUS			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "spir",				PROC_ID_UCOM_SPI_R			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ "spiw",				PROC_ID_UCOM_SPI_W			, OS_PROC_FLAG_READ | OS_PROC_FLAG_WRITE  },
	{ NULL, 				PROC_ID_MAX					, 0 }
};



/*========================================================================================
	Implementation Group
========================================================================================*/


/**
 * read_proc implementation of micom device
 *
*/

int	o26_read_proc(UINT32 procId, char* buffer );
int o26_write_proc( UINT32 procId, char* command );
void o26_ucom_proc_init (void);
void o26_ucom_proc_cleanup (void);

int	o26_read_proc(UINT32 procId, char* buffer )
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
		case PROC_ID_UCOM_SPI_W:
		case PROC_ID_UCOM_SPI_R:
		break;

		default:
		{
			ret = snprintf( buffer,48,"%s(%d)\n", "unimplemented read proc", procId );
		}
		break;
	}
	printk("not implemented[%d] \n",ret);

	return ret;
}
extern unsigned int ucom_gpionum;

#define  INPUT_SIZE 256
int o26_write_proc( UINT32 procId, char* command )
{
	int	ret = 0,count = 0,parse = 0, i = 0;
	char input[INPUT_SIZE];
	char *token,*sav_tok;
	UINT32 addr[5]={0,};
	UINT32 value[5]={0,};

	if(command == NULL)
	{
		return -1;
	}

	count = strlen(command);
	if(count >= INPUT_SIZE)
	{
		count = INPUT_SIZE - 1;
	}
	else if (count < 0)
	{
		return -1;
	}

	memcpy(input,command, count);
	input[count] = '\0';

	count = 0;
	switch( procId ) {

		case PROC_ID_UCOM_STATUS:
			break;
		case PROC_ID_UCOM_SPI_W:
			{
				token = simple_strtok(input, " ",&sav_tok);
				while (token != NULL) {
					if (sscanf(token, "%x", &addr[count]) == 1) {
						token = simple_strtok(NULL, " ", &sav_tok);
						if (token != NULL && sscanf(token, "%x", &value[count]) == 1) {
							//printk("Received addr: 0x%x, value: 0x%x\n", addr[count], value[count]);
						}
						token = simple_strtok(NULL, " ",&sav_tok); // Move to the next address
						if(token == NULL)
							parse = 1;
						count++;
					} else {
						parse = 1;
						break;
					}
				}
			}
			printk("Waddr[%8x] value[%8x] [%d] [%d]\n",addr[0],value[0],parse,count);
			if(parse)
			{
				ret = o26_ucom_spi_write((UINT8 *)addr,(UINT8 *)value,count);
				if(ret)
					printk("check spi write[%d]\n",ret);
			}
			break;

		case PROC_ID_UCOM_SPI_R:
		{
			token = simple_strtok(input, " ",&sav_tok);
			while (token != NULL) {
				if (sscanf(token, "%x", &addr[count]) == 1) {
					token = simple_strtok(NULL, " ", &sav_tok);
					if (token != NULL && sscanf(token, "%x", &value[count]) == 1) {
						//printk("Received addr: 0x%x, value: 0x%x\n", addr[count], value[count]);
					}
					token = simple_strtok(NULL, " ",&sav_tok); // Move to the next address
					if(token == NULL)
						parse = 1;
					count++;
				} else {
					parse = 1;
				}
			}
			if(parse)
			{
				ret = o26_ucom_spi_read((UINT8 *)addr,(UINT8 *)value,count);
				if(!ret)
				{
					for( i = 0 ; i < count ;i++)
					{
						printk("Raddr[%8x] value[%8x]\n",addr[i],value[i]);
					}
				}
				else
					printk("check spi read[%d] \n",ret);
			}
			break;
		}

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
void o26_ucom_proc_init (void)
{
	ucom_func	= get_o26_ucom_func();
	ucom_drv =  get_o26_ucom_driver();


	OS_PROC_CreateEntryEx ( UCOM_MODULE, _g_ucom_o26_device_proc_table,
										o26_read_proc,
										o26_write_proc );

}
/**
 * cleanup proc utility for micom device
 *
 * @see UCOM_Cleanup
*/
void o26_ucom_proc_cleanup (void)
{
	OS_PROC_RemoveEntry( UCOM_MODULE );
}

static ucom_proc_t o26_proc_func =
{
	.init = o26_ucom_proc_init,
	.cleanup = o26_ucom_proc_cleanup,
};

ucom_proc_t* get_o26_ucom_proc(void)
{
	return &o26_proc_func;
}

