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
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#include "os_util.h"
#include "emmc_drv.h"
#include "sys_regs.h"
#include "sys_io.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#if 0
#define EMMC_CORE_DEBUG(format, args...)	PM_ERROR(format, ##args)
#else
#define EMMC_CORE_DEBUG(format, args...)	do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	UINT8	direction;
	UINT8	data;
} PM_EMMC_DATA_T;

typedef struct EMMC_DEV
{
	OS_SEM_T	lock;
} EMMC_DEV_T;


/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
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

/*************************************************************************
* Set Pinmux
*************************************************************************/
int EMMC_DevInit(void)
{
	return 0;
}

int EMMC_DevResume(void)
{
	return 0;
}

int EMMC_DevSuspend(void)
{
	return 0;
}

void EMMC_HexView(char *addr, unsigned int size, unsigned int address)
{
	unsigned int i;
	unsigned int offset;

	printk("=======================================================\n");

	for (i=0; i<(size/16); i++)
	{
		offset = (i*16);
		printk("0x%08x : %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x %02x%02x%02x%02x",
			address + offset,
			addr[offset+3], addr[offset+2], addr[offset+1], addr[offset],
			addr[offset+7], addr[offset+6], addr[offset+5], addr[offset+4],
            addr[offset+11], addr[offset+10], addr[offset+9], addr[offset+8],
			addr[offset+15], addr[offset+14], addr[offset+13], addr[offset+12]);
	}

	printk("=======================================================\n");
}

/** @} */
