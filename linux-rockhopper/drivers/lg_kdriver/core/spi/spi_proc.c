
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


#include "spi_drv.h"
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
	PROC_ID_SPIW	= 0,
	PROC_ID_SPIR,
	PROC_ID_SPIMAX,
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
static OS_PROC_DESC_TABLE_T	_g_spi_device_proc_table[] =
{
	{ "spiw",		PROC_ID_SPIW  , OS_PROC_FLAG_WRITE },
	{ "spir",		PROC_ID_SPIR	, OS_PROC_FLAG_READ },
	{ NULL, 		PROC_ID_SPIMAX		, 0 }
};

/*========================================================================================
	Implementation Group
========================================================================================*/
#define  INPUT_SIZE 256

int	_SPI_WriteProcFunction(	UINT32 procId, char* command )
{
	int	ret = 0,count = 0,parse = 0;
	char input[INPUT_SIZE];
	char *token,*sav_tok;
	//UINT32 addr[5],value[5], ;
	UINT32 addr=0,value=0,num=0,ch=0;
	unsigned char buf[500] = {0,};
    unsigned int Addr  = 0xd0000004;

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


	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_SPIW:
		{
			token = simple_strtok(input, " ",&sav_tok);
			while (token != NULL)
			{
				if (sscanf(token, "%x", &addr) == 1)
				{
					token = simple_strtok(NULL, " ", &sav_tok);
					if (token != NULL && sscanf(token, "%x", &value) == 1) {
						//printk("Received addr: 0x%x, value: 0x%x\n", addr[count], value[count]);
						token = simple_strtok(NULL, " ", &sav_tok);
						if (token != NULL && sscanf(token, "%x", &num) == 1) {
							token = simple_strtok(NULL, " ", &sav_tok);
							if (token != NULL && sscanf(token, "%x", &ch) == 1) {
								printk("addr: 0x%x, value: 0x%x num %d ch %d\n", addr, value,num,ch);
								parse = 1;
							}
							token = simple_strtok(NULL, " ",&sav_tok);
							if(token == NULL)
							{
								parse = 2;
							}
						}
					}
				} else {
					parse = 3;
				 	break;
				}

				if(parse)
				{
					spi_config (ch, 0 ,2000000);
					buf[0] = (addr & 0xff000000)>>24;
					buf[1] = (addr & 0x00ff0000)>>16;
					buf[2] = (addr & 0x0000ff00)>>8;
					buf[3] = (addr & 0x000000ff)>>0 ;
					buf[4] = (value & 0xff000000)>>24;
					buf[5] = (value & 0x00ff0000)>>16;
					buf[6] = (value & 0x0000ff00)>>8;
					buf[7] = (value & 0x000000ff)>>0 ;
					ret = spi_send ( ch,buf, num, 0);
					printk("spiw %d ch %d addr %8x [%x][%x][%x][%x] [%x][%x][%x][%x])\n",parse,ch,Addr, buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7] );
					break;
				}

			}

		}
		break;

		case PROC_ID_SPIR:
		{
			token = simple_strtok(input, " ",&sav_tok);
			while (token != NULL)
			{
				if (sscanf(token, "%x", &addr) == 1)
				{
					token = simple_strtok(NULL, " ", &sav_tok);
					if (token != NULL && sscanf(token, "%x", &value) == 1) {
						//printk("Received addr: 0x%x, value: 0x%x\n", addr[count], value[count]);
						token = simple_strtok(NULL, " ", &sav_tok);
						if (token != NULL && sscanf(token, "%x", &num) == 1) {
							token = simple_strtok(NULL, " ", &sav_tok);
							if (token != NULL && sscanf(token, "%x", &ch) == 1) {
								printk("addr: 0x%x, value: 0x%x num %d ch %d\n", addr, value,num,ch);
								parse = 1;
							}
							token = simple_strtok(NULL, " ",&sav_tok);
							if(token == NULL)
							{
								parse = 2;
							}
						}
					}
				} else {
					parse = 3;
				 	break;
				}

				if(parse)
				{
					printk("spir \n");
					spi_config (ch, 0 ,2000000);
					buf[0] = (addr & 0xff000000)>>24;
					buf[1] = (addr & 0x00ff0000)>>16;
					buf[2] = (addr & 0x0000ff00)>>8;
					buf[3] = (addr & 0x000000ff)>>0 ;
					ret = spi_send ( ch,buf, num, 4);
					printk("spir %d ch %d addr %8x [%x][%x][%x][%x] [%x][%x][%x][%x])\n",parse,ch,addr, buf[0],buf[1],buf[2],buf[3],buf[4],buf[5],buf[6],buf[7] );
					break;
				}
			}

		}
		break;

		default:
		{
		}
		break;
	}

	return strlen(command);;
}

int _SPI_ReadProcFunction( UINT32 procId, char* command )
{

	/* TODO: add your proc_write implementation */
	switch( procId )
	{
		case PROC_ID_SPIR:
		case PROC_ID_SPIW:
		{
			//input_n = sscanf(command,"%u\n", &input_value);
			//debugpinval = input_value;
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

/*
 * initialize proc utility for gpio device
 *
 * @see GPIO_Init
*/
void	SPI_PROC_Init (void)
{
	OS_PROC_CreateEntryEx ( SPI_MODULE, _g_spi_device_proc_table,
											_SPI_ReadProcFunction,
											_SPI_WriteProcFunction );
}

/**
 * cleanup proc utility for gpio device
 *
 * @see GPIO_Cleanup
*/
void	SPI_PROC_Cleanup (void)
{
	OS_PROC_RemoveEntry( SPI_MODULE );
}
