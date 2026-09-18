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
 *  BE reg driver file for BE device
 *
 *  author		won.hur
 *  version		1.0
 *  date		2012.04.18
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
#include <asm/io.h>

#include "os_util.h"
#include "be_dbg.h"

#include "be_reg.h"
#include "be_kapi.h"
#include "m17/be/reg/be_reg_hw_m17.h"
#include "o18/be/reg/be_reg_hw_o18.h"
#include "m19/be/reg/be_reg_hw_m19.h"
#include "o20/be/reg/be_reg_hw_o20.h"
#include "e60/be/reg/be_reg_hw_e60.h"
#include "o22/be/reg/be_reg_hw_o22.h"
#include "m23/be/reg/be_reg_hw_m23.h"
#include "o24/be/reg/be_reg_hw_o24.h"
#include "o26/be/reg/be_reg_hw_o26.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
	int (*pfnInitializeREG)(void);
	int (*pfnCloseREG)(void);
	int (*pfnReadREG)(BE_REG_RW_TYPE_T type, void *addr, UINT32 *data);
	int (*pfnWriteREG)(BE_REG_RW_TYPE_T type, void *addr, UINT32 data);
} BE_REG_HW_FUNCTION_T;

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
static BE_REG_HW_FUNCTION_T gstBeRegHwFunction;

/*========================================================================================
	Implementation Group
========================================================================================*/
int BE_REG_Init(void)
{
	int ret = RET_OK;

	memset(&gstBeRegHwFunction,0,sizeof(BE_REG_HW_FUNCTION_T));

	if (0)
	{

	}
#ifdef INCLUDE_O26_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O26, A0))
	{
		BE_PRINT("BE REG chip revision is set to O26 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_O26_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_O26_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_O26_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_O26_Write;
	}
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O24, A0))
	{
		BE_PRINT("BE REG chip revision is set to O24 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_O24_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_O24_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_O24_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_O24_Write;
	}
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( M23, A0))
	{
		BE_PRINT("BE REG chip revision is set to M23 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_M23_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_M23_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_M23_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_M23_Write;
	}
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O22, A0))
	{
		BE_PRINT("BE REG chip revision is set to O22 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_O22_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_O22_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_O22_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_O22_Write;
	}
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( E60, A0))
	{
		BE_PRINT("BE REG chip revision is set to E60 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_E60_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_E60_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_E60_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_E60_Write;
	}
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
	else if ( lx_chip_rev( ) >= LX_CHIP_REV( O20, A0))
	{
		BE_PRINT("BE REG chip revision is set to O20 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_O20_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_O20_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_O20_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_O20_Write;
	}
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV( M19, A0))
	{
		BE_PRINT("BE REG chip revision is set to M19 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_M19_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_M19_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_M19_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_M19_Write;
	}
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV( O18, A0))
	{
		BE_PRINT("BE REG chip revision is set to O18 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_O18_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_O18_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_O18_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_O18_Write;
	}
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
	else if (lx_chip_rev() >= LX_CHIP_REV( M17, A0))
	{
		BE_PRINT("BE REG chip revision is set to M17 A0\n");
		gstBeRegHwFunction.pfnInitializeREG = BE_REG_HW_M17_Initialize;
		gstBeRegHwFunction.pfnCloseREG		= BE_REG_HW_M17_Close;
		gstBeRegHwFunction.pfnReadREG		= BE_REG_HW_M17_Read;
		gstBeRegHwFunction.pfnWriteREG		= BE_REG_HW_M17_Write;
	}
#endif
	else
	{
		BE_ERROR("BE REG ERROR! Unknown chip revision at BE REG module\n");
		gstBeRegHwFunction.pfnInitializeREG	= NULL;
		gstBeRegHwFunction.pfnCloseREG		= NULL;
		gstBeRegHwFunction.pfnReadREG		= NULL;
		gstBeRegHwFunction.pfnWriteREG		= NULL;

		ret = RET_ERROR;
	}

	if (gstBeRegHwFunction.pfnInitializeREG)
	{
		ret = gstBeRegHwFunction.pfnInitializeREG();
	}

	return ret;
}

int BE_REG_Close(void)
{
	int ret = RET_OK;

	if(gstBeRegHwFunction.pfnCloseREG)
	{
		ret = gstBeRegHwFunction.pfnCloseREG();
	}

	gstBeRegHwFunction.pfnInitializeREG	= NULL;
	gstBeRegHwFunction.pfnCloseREG		= NULL;
	gstBeRegHwFunction.pfnReadREG		= NULL;
	gstBeRegHwFunction.pfnWriteREG		= NULL;

	return ret;
}

int BE_REG_RegAccess(UINT32 arg)
{
	int ret = RET_ERROR;
	BE_REG_RW_T reg_addr_data_t;

	if ( copy_from_user(&reg_addr_data_t, (void __user *)(uintptr_t)arg, sizeof(BE_REG_RW_T)))
	{
		return -EFAULT;
	}

	BE_DEBUG("BE_REG_RegAccess(%d, %d, 0x%08x, 0x%08x) is called. \n", reg_addr_data_t.type, reg_addr_data_t.isRead, reg_addr_data_t.addr, reg_addr_data_t.data);

	if (reg_addr_data_t.isRead)
	{
        if (gstBeRegHwFunction.pfnReadREG)
        {
            ret = gstBeRegHwFunction.pfnReadREG(reg_addr_data_t.type, (void*)(uintptr_t)reg_addr_data_t.addr, &reg_addr_data_t.data);
            if (ret == RET_OK)
            {
                ret = copy_to_user((void __user *)(uintptr_t)arg, &reg_addr_data_t, sizeof(BE_REG_RW_T));
            }
        }
	}
	else
	{
        if (gstBeRegHwFunction.pfnWriteREG)
        {
            ret = gstBeRegHwFunction.pfnWriteREG(reg_addr_data_t.type, (void*)(uintptr_t)reg_addr_data_t.addr, reg_addr_data_t.data);
        }
	}

	return ret;
}

