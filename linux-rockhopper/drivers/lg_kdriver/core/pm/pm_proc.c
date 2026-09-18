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
 *  date			2014.07.18
 *  note			Additional information.
 *
 *  @addtogroup lg1210_pm
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
#include "pm_drv.h"
#include "proc_util.h"
#include "debug_util.h"

#ifdef INCLUDE_O26_CHIP_KDRV
#include "../../chip/o26/pm/pm_o26common.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "../../chip/o24/pm/pm_o24common.h"
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#include "../../chip/m23/pm/pm_m23common.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "../../chip/o22/pm/pm_o22common.h"
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
#include "../../chip/e60/pm/pm_e60common.h"
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
#include "../../chip/o20/pm/pm_o20common.h"
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
#include "../../chip/m19/pm/pm_m19common.h"
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
#include "../../chip/o18/pm/pm_o18common.h"
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
#include "../../chip/m17/pm/pm_m17common.h"
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
pms_proc_t *pms_proc = NULL;

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

/*========================================================================================
	Implementation Group
========================================================================================*/

/**
 * read_proc implementation of pm device
 *
*/

int     _PM_ReadProcFunction(   UINT32 procId, char* buffer );
int _PM_WriteProcFunction( UINT32 procId, char* command );
void PM_PROC_Init (void);
void PM_PROC_Cleanup (void);

int	_PM_ReadProcFunction(	UINT32 procId, char* buffer )
{
	return 0;
}

/**
 * write_proc implementation of pm device
 *
*/
int _PM_WriteProcFunction( UINT32 procId, char* command )
{
	return strlen(command);
}

/**
 * initialize proc utility for pm device
 *
 * @see PM_Init
*/
void PM_PROC_Init (void)
{
	if(0){}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O26) )
	{
		pms_proc = get_o26_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O24) )
	{
		pms_proc = get_o24_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M23) )
	{
		pms_proc = get_m23_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) )
	{
		pms_proc = get_o22_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) )
	{
		pms_proc = get_e60_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) )
	{
		pms_proc = get_o20_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M19) )
	{
		pms_proc = get_m19_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O18) )
	{
		pms_proc = get_o18_pm_proc();
		pms_proc->init();
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if (!LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) )
	{
		pms_proc = get_m17_pm_proc();
		pms_proc->init();
	}
#endif
}

/**
 * cleanup proc utility for pm device
 *
 * @see PM_Cleanup
*/
void PM_PROC_Cleanup (void)
{
	if (pms_proc)
		pms_proc->cleanup();
}

/** @} */

