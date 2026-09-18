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
 *  main configuration file for PE device
 *
 *  author		justine.jeong
 *  version		1.0
 *  date		2012.02.07
 *  note		Additional information.
 *
 *  @addtogroup BE
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/seq_file.h>

#include "os_util.h"
#include "base_device.h"
#include "debug_util.h"

#include "pe_cfg.h"
#include "pe_def.h"
#include "pe_hal.h"

#ifdef INCLUDE_O26_CHIP_KDRV
#include "pe_inf_o26.h"
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
#include "pe_inf_o24.h"
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#include "pe_inf_m23.h"
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
#include "pe_inf_o22.h"
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
struct pe_hal_ctx
{
	int (*get_status)(UINT32 *p_data, UINT32 count);
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
static struct pe_hal_ctx _g_pe_hal_ctx;

/*========================================================================================
	Implementation Group
========================================================================================*/
int pe_hal_init(void)
{
	memset(&_g_pe_hal_ctx,0,sizeof(_g_pe_hal_ctx));

	if (0) { }
	#ifdef INCLUDE_O26_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O26)
	{
		_g_pe_hal_ctx.get_status = PE_INF_O26_GetStatus;
	}
	#endif
	#ifdef INCLUDE_O24_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O24)
	{
		_g_pe_hal_ctx.get_status = PE_INF_O24_GetStatus;
	}
	#endif
	#ifdef INCLUDE_M23_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_M23)
	{
		_g_pe_hal_ctx.get_status = PE_INF_M23_GetStatus;
	}
	#endif
	#ifdef INCLUDE_O22_CHIP_KDRV
	else if (lx_chip() == LX_CHIP_O22)
	{
		_g_pe_hal_ctx.get_status = PE_INF_O22_GetStatus;
	}
	#endif
	else
	{
		PE_PRINT_NOTI("not support (chip:0x%x)\n", lx_chip());
	}

	return 0;
}

int pe_hal_get_status(UINT32 *p_data, UINT32 count)
{
	if (!_g_pe_hal_ctx.get_status)	return -10;

	return _g_pe_hal_ctx.get_status(p_data,count);
}

