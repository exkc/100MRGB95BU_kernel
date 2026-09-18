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
 *  main configuration file for gpio device
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
#include <linux/kernel.h>

#include "gpio_kapi.h"
#include "os_util.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

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
static  UINT32  g_gpio_sw_cfg = LX_GPIO_CFG_NONE;	/* default config */

/*========================================================================================
	Implementation Group
========================================================================================*/

void    GPIO_CFG_Init(void);
UINT32	lx_gpio_cfg(void);

void    GPIO_CFG_Init(void)
{
    // TODO: fix your default g_gpio_sw_cfg;
	switch(lx_chip())
	{
		case LX_CHIP_O26:
		case LX_CHIP_O24:
		case LX_CHIP_M23:
		case LX_CHIP_O22:
		case LX_CHIP_E60:
		case LX_CHIP_O20:
		case LX_CHIP_M19:
		case LX_CHIP_O18:
				g_gpio_sw_cfg = LX_GPIO_CFG_NONE;
				break;
		case LX_CHIP_M17:
			if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
			{
				g_gpio_sw_cfg = LX_GPIO_CFG_NONE;
			}
			else
			{
				g_gpio_sw_cfg = LX_GPIO_CFG_LEGACY_MODE;
			}
		break;
		case LX_CHIP_L18:	g_gpio_sw_cfg = LX_GPIO_CFG_LEGACY_MODE; break;
		default:			g_gpio_sw_cfg = LX_GPIO_CFG_LEGACY_MODE; break;
	}

	// parse user-defined configuration
	{
		char    optstr[80];

		if (RET_OK == OS_ScanKernelCmdline("use_legacy_gpio=%s", optstr))
		{
			if		(optstr[0] == '1')	{ g_gpio_sw_cfg |= LX_GPIO_CFG_LEGACY_MODE; }
			else if	(optstr[0] == '0')	{ g_gpio_sw_cfg &= ~LX_GPIO_CFG_LEGACY_MODE;}
			else						{ /* keep current config */ }
		}
	}

	printk("+ GPIO.SW_CFG = 0x%08x\n", g_gpio_sw_cfg);
}

UINT32	lx_gpio_cfg(void)
{
	return g_gpio_sw_cfg;
}

/** @} */

