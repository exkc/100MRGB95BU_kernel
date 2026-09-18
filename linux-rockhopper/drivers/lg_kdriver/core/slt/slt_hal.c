/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */


/** @file
 *
 *  main configuration file for slt device
 *
 *  @author		wunseo.yeo@lge.com
 *  @version	1.0
 *  @date		2014.08
 *
 *  @addtogroup lg115x_slt
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include "os_util.h"

#include "slt_drv.h"
#include "slt_hal.h"
#include "slt_hw.h"


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
	SLT_HW_FUNC_T *func;
} SLT_HAL_T;


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
static SLT_HAL_T hal;

/*========================================================================================
	Implementation Group
========================================================================================*/

int SLT_HAL_Init(void)
{
	SLT_HW_FUNC_T *func = NULL;

	if(0){}
#ifdef INCLUDE_O22_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O22) ) func = SLT_O22_Init();
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_E60) ) func = SLT_E60_Init();
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O20) ) func = SLT_O20_Init();
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_O18) ) func = SLT_O18_Init();
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_L18) ) func = SLT_L18_Init();
#endif

#ifdef INCLUDE_M17_CHIP_KDRV
	else if ( !LX_COMP_CHIP(lx_chip_rev(), LX_CHIP_M17) ) func = SLT_M17_Init();
#endif

	else SLT_ERROR("Not supported chip 0x%x\n", lx_chip_rev() );

	if(func == NULL)
		return -1;

	if(func->init() < 0)
		return -1;

	hal.func = func;

	return 0;
}

void SLT_HAL_Cleanup(void)
{
	if(hal.func && hal.func->cleanup)
		return hal.func->cleanup();
}

int SLT_HAL_Open(void)
{
	if(hal.func && hal.func->open)
		return hal.func->open();

	return -1;
}
EXPORT_SYMBOL(SLT_HAL_Open);

int SLT_HAL_Close(void)
{
	if(hal.func && hal.func->close)
		return hal.func->close();
	return -1;
}
EXPORT_SYMBOL(SLT_HAL_Close);

void SLT_HAL_SetTestMode( LX_SLT_TEST_MODE_E *mode )
{
	if(hal.func && hal.func->set_testmode)
		hal.func->set_testmode(mode);
	return;
}
EXPORT_SYMBOL(SLT_HAL_SetTestMode);

void SLT_HAL_IntrEnable( void )
{
	if(hal.func && hal.func->intr_enable)
		hal.func->intr_enable();
	return;
}
EXPORT_SYMBOL(SLT_HAL_IntrEnable);

void SLT_HAL_IntrDisable( void )
{
	if(hal.func && hal.func->intr_disable)
		hal.func->intr_disable();
	return;
}
EXPORT_SYMBOL(SLT_HAL_IntrDisable);

int SLT_HAL_GetRefCrc(LX_SLT_CRC_DATA_T *data)
{
	if(hal.func && hal.func->get_ref_crc)
		return hal.func->get_ref_crc(data);
	return -1;
}
EXPORT_SYMBOL(SLT_HAL_GetRefCrc);


/** @} */

