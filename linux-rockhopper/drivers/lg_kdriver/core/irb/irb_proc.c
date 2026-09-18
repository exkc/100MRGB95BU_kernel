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
 *  main driver implementation for irb device.
 *	irb device will teach you how to make device driver with new platform.
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_irb
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
#include "irb_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#ifdef INCLUDE_O20_CHIP_KDRV
#include "../../chip/o20/irb/irb_o20common.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "../../chip/e60/irb/irb_e60common.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "../../chip/o22/irb/irb_o22common.h"
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#include "../../chip/m23/irb/irb_m23common.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/irb/irb_o24common.h"
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
#include "../../chip/o26/irb/irb_o26common.h"
#endif

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
irbs_proc_t *irbs_proc = NULL;

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
int _IRB_ReadProcFunction(  UINT32 procId, char* buffer );
int _IRB_WriteProcFunction( UINT32 procId, char* command );
void IRB_PROC_Init (void);
void IRB_PROC_Cleanup (void);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * read_proc implementation of irb device
 *
*/
int	_IRB_ReadProcFunction(	UINT32 procId, char* buffer )
{
	return 0;
}

/**
 * write_proc implementation of irb device
 *
*/
int _IRB_WriteProcFunction( UINT32 procId, char* command )
{
	return strlen(command);
}

/**
 * initialize proc utility for irb device
 *
 * @see IRB_Init
*/
void IRB_PROC_Init (void)
{
	if(0){}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
	{
		irbs_proc = get_o26_irb_proc();
		irbs_proc->init();
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
	{
		irbs_proc = get_o24_irb_proc();
		irbs_proc->init();
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) )
	{
		irbs_proc = get_m23_irb_proc();
		irbs_proc->init();
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
	{
		irbs_proc = get_o22_irb_proc();
		irbs_proc->init();
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		irbs_proc = get_e60_irb_proc();
		irbs_proc->init();
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		irbs_proc = get_o20_irb_proc();
		irbs_proc->init();
	}
#endif

}

/**
 * cleanup proc utility for irb device
 *
 * @see IRB_Cleanup
*/
void IRB_PROC_Cleanup (void)
{
	if (irbs_proc)
		irbs_proc->cleanup();
}

/** @} */

