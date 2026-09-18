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
 *  main driver implementation for ucom device.
 *	ucom device will teach you how to make device driver with new platform.
 *
 *  author		jun.kong
 *  version		1.0
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_ucom
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
#include "ucom_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#ifdef INCLUDE_O26_CHIP_KDRV
#include "../../chip/o26/ucom/ucom_o26_common.h"
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/ucom/ucom_o24_common.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "../../chip/o22/ucom/ucom_o22_common.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "../../chip/e60/ucom/ucom_e60_common.h"
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
#include "../../chip/o20/ucom/ucom_o20_common.h"
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
ucom_proc_t *ucom_proc = NULL;

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

void UCOM_PROC_Init (void);
void UCOM_PROC_Cleanup (void);
/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * initialize proc utility for ucom device
 *
 * @see UCOM_Init
*/
void UCOM_PROC_Init (void)
{
	if (0)
	{
	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
	{
		ucom_proc = get_o26_ucom_proc();
		ucom_proc->init();
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
	{
		ucom_proc = get_o24_ucom_proc();
		ucom_proc->init();
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
	{
		ucom_proc = get_o22_ucom_proc();
		ucom_proc->init();
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		ucom_proc = get_e60_ucom_proc();
		ucom_proc->init();
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		ucom_proc = get_o20_ucom_proc();
		ucom_proc->init();
	}
#endif

}

/**
 * cleanup proc utility for ucom device
 *
 * @see UCOM_Cleanup
*/
void UCOM_PROC_Cleanup (void)
{
	if (ucom_proc)
		ucom_proc->cleanup();
}

/** @} */

