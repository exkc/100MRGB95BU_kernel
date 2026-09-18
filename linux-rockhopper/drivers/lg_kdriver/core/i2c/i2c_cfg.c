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
 *  main configuration file for i2c device
 *	i2c device will teach you how to make device driver with new platform.
 *
 *  author		ingyu.yang (ingyu.yang@lge.com)
 *  				jun.kong (jun.kong@lge.com)
 *  version		1.0
 *  date		2009.12.30
 *  note		Additional information.
 *
 *  @addtogroup lg1150_i2c
 *	@{
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/interrupt.h>

#include "i2c_cfg.h"
#include "i2c_kapi.h"
#include "i2c_regs.h"
#include "os_util.h"


#ifndef __O20_LINUX_PLATFORM_H__
#ifdef INCLUDE_O20_CHIP_KDRV
	#include "../../chip/o20/os/linux_platform.h"
	#include "../../chip/o20/os/linux_irqs.h"
#endif
#endif

#ifndef __E60_LINUX_PLATFORM_H__
#ifdef INCLUDE_E60_CHIP_KDRV
	#include "../../chip/e60/os/linux_platform.h"
	#include "../../chip/e60/os/linux_irqs.h"
#endif
#endif
#ifndef __O22_LINUX_PLATFORM_H__
#ifdef INCLUDE_O22_CHIP_KDRV
	#include "../../chip/o22/os/linux_platform.h"
	#include "../../chip/o22/os/linux_irqs.h"
#endif
#endif

#ifndef __M23_LINUX_PLATFORM_H__
#ifdef INCLUDE_M23_CHIP_KDRV
	#include "../../chip/m23/os/linux_platform.h"
	#include "../../chip/m23/os/linux_irqs.h"
#endif
#endif

#ifndef __O24_LINUX_PLATFORM_H__
#ifdef INCLUDE_O24_CHIP_KDRV
	#include "../../chip/o24/os/linux_platform.h"
	#include "../../chip/o24/os/linux_irqs.h"
#endif
#endif

#ifndef __O26_LINUX_PLATFORM_H__
#ifdef INCLUDE_O26_CHIP_KDRV
	#include "../../chip/o26/os/linux_platform.h"
	#include "../../chip/o26/os/linux_irqs.h"
#endif
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

#ifdef INCLUDE_M19_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapM19Ax[] =
{
	{M19_I2C0_BASE,         M19_IRQ_I2C0},
	{M19_I2C1_BASE,         M19_IRQ_I2C1},
	{M19_I2C2_BASE,         M19_IRQ_I2C2},
	{M19_I2C3_BASE,         M19_IRQ_I2C3},
	{M19_I2C4_BASE,         M19_IRQ_I2C4},
	{M19_I2C5_BASE,         M19_IRQ_I2C5},
	{M19_I2C6_BASE,         M19_IRQ_I2C6},
	{M19_I2C7_BASE,         M19_IRQ_I2C7},
	{M19_I2C8_BASE,         M19_IRQ_I2C8},
	{M19_I2C9_BASE,         M19_IRQ_I2C9}
};
#endif
#ifdef INCLUDE_M17_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapM17Ax[] =
{
	{M17_I2C0_BASE,         M17_IRQ_I2C0},
	{M17_I2C1_BASE,         M17_IRQ_I2C1},
	{M17_I2C2_BASE,         M17_IRQ_I2C2},
	{M17_I2C3_BASE,         M17_IRQ_I2C3},
	{M17_I2C4_BASE,         M17_IRQ_I2C4},
	{M17_I2C5_BASE,         M17_IRQ_I2C5},
	{M17_I2C6_BASE,         M17_IRQ_I2C6},
	{M17_I2C7_BASE,         M17_IRQ_I2C7},
	{M17_I2C8_BASE,         M17_IRQ_I2C8},
	{M17_I2C9_BASE,         M17_IRQ_I2C9}
};
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapL18Ax[] =
{
	{L18_I2C0_BASE,         L18_IRQ_I2C0},
	{L18_I2C1_BASE,         L18_IRQ_I2C1},
	{L18_I2C2_BASE,         L18_IRQ_I2C2},
	{L18_I2C3_BASE,         L18_IRQ_I2C3},
	{L18_I2C4_BASE,         L18_IRQ_I2C4},
	{L18_I2C5_BASE,         L18_IRQ_I2C5},
	{L18_I2C6_BASE,         L18_IRQ_I2C6},
	{L18_I2C7_BASE,         L18_IRQ_I2C7},
	{L18_I2C8_BASE,         L18_IRQ_I2C8},
	{L18_I2C9_BASE,         L18_IRQ_I2C9}
};
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapO18Ax[] =
{
	{O18_I2C0_BASE,         O18_IRQ_I2C0},
	{O18_I2C1_BASE,         O18_IRQ_I2C1},
	{O18_I2C2_BASE,         O18_IRQ_I2C2},
	{O18_I2C3_BASE,         O18_IRQ_I2C3},
	{O18_I2C4_BASE,         O18_IRQ_I2C4},
	{O18_I2C5_BASE,         O18_IRQ_I2C5},
	{O18_I2C6_BASE,         O18_IRQ_I2C6},
	{O18_I2C7_BASE,         O18_IRQ_I2C7},
	{O18_I2C8_BASE,         O18_IRQ_I2C8},
	{O18_I2C9_BASE,         O18_IRQ_I2C9}
};
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapO20Ax[] =
{
	{O20_I2C0_BASE,         O20_IRQ_I2C0},
	{O20_I2C1_BASE,         O20_IRQ_I2C1},
	{O20_I2C2_BASE,         O20_IRQ_I2C2},
	{O20_I2C3_BASE,         O20_IRQ_I2C3},
	{O20_I2C4_BASE,         O20_IRQ_I2C4},
	{O20_I2C5_BASE,         O20_IRQ_I2C5},
	{O20_I2C6_BASE,         O20_IRQ_I2C6},
	{O20_I2C7_BASE,         O20_IRQ_I2C7},
	{O20_I2C8_BASE,         O20_IRQ_I2C8},
	{O20_I2C9_BASE,         O20_IRQ_I2C9}
};
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapE60Ax[] =
{
	{E60_I2C0_BASE,         E60_IRQ_I2C0},
	{E60_I2C1_BASE,         E60_IRQ_I2C1},
	{E60_I2C2_BASE,         E60_IRQ_I2C2},
	{E60_I2C3_BASE,         E60_IRQ_I2C3},
	{E60_I2C4_BASE,         E60_IRQ_I2C4},
	{E60_I2C5_BASE,         E60_IRQ_I2C5},
	{E60_I2C6_BASE,         E60_IRQ_I2C6},
	{E60_I2C7_BASE,         E60_IRQ_I2C7},
	{E60_I2C8_BASE,         E60_IRQ_I2C8},
	{E60_I2C9_BASE,         E60_IRQ_I2C9}
};
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapO22Ax[] =
{
	{O22_I2C0_BASE,         O22_IRQ_I2C0},
	{O22_I2C1_BASE,         O22_IRQ_I2C1},
	{O22_I2C2_BASE,         O22_IRQ_I2C2},
	{O22_I2C3_BASE,         O22_IRQ_I2C3},
	{O22_I2C4_BASE,         O22_IRQ_I2C4},
	{O22_I2C5_BASE,         O22_IRQ_I2C5},
	{O22_I2C6_BASE,         O22_IRQ_I2C6},
	{O22_I2C7_BASE,         O22_IRQ_I2C7},
	{O22_I2C8_BASE,         O22_IRQ_I2C8},
	{O22_I2C9_BASE,         O22_IRQ_I2C9}
};
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
static LX_I2C_HW_MAP_T _stI2cHwMapM23Ax[] =
{
	{M23_I2C0_BASE,         M23_IRQ_I2C0},
	{M23_I2C1_BASE,         M23_IRQ_I2C1},
	{M23_I2C2_BASE,         M23_IRQ_I2C2},
	{M23_I2C3_BASE,         M23_IRQ_I2C3},
	{M23_I2C4_BASE,         M23_IRQ_I2C4},
	{M23_I2C5_BASE,         M23_IRQ_I2C5},
	{M23_I2C6_BASE,         M23_IRQ_I2C6},
	{M23_I2C7_BASE,         M23_IRQ_I2C7},
	{M23_I2C8_BASE,         M23_IRQ_I2C8},
	{M23_I2C9_BASE,         M23_IRQ_I2C9}
};
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
#ifndef O24_I2C0_BASE
	#define O24_PERI_BASE           (0xfe000000)
	#define O24_I2C0_BASE           (O24_PERI_BASE+0x300000)
	#define O24_I2C1_BASE           (O24_PERI_BASE+0x400000)
	#define O24_I2C2_BASE           (O24_PERI_BASE+0x500000)
	#define O24_I2C3_BASE           (O24_PERI_BASE+0x600000)
	#define O24_SPI0_BASE           (O24_PERI_BASE+0x800000)
	#define O24_SPI1_BASE           (O24_PERI_BASE+0x900000)

	#define	O24_I2C_BASE            (0xf9000000)
	#define O24_I2C4_BASE           (O24_I2C_BASE+0x000000)
	#define O24_I2C5_BASE           (O24_I2C_BASE+0x100000)
	#define O24_I2C6_BASE           (O24_I2C_BASE+0x200000)
	#define O24_I2C7_BASE           (O24_I2C_BASE+0x300000)
	#define O24_I2C8_BASE           (O24_I2C_BASE+0x400000)
	#define O24_I2C9_BASE           (O24_I2C_BASE+0x500000)

	#define O24_IRQ_GIC_START       32
	#define O24_IRQ_I2C0            (O24_IRQ_GIC_START+26)
	#define O24_IRQ_I2C1            (O24_IRQ_GIC_START+27)
	#define O24_IRQ_I2C2            (O24_IRQ_GIC_START+28)
	#define O24_IRQ_I2C3            (O24_IRQ_GIC_START+29)
	#define O24_IRQ_I2C4            (O24_IRQ_GIC_START+30)
	#define O24_IRQ_I2C5            (O24_IRQ_GIC_START+31)
	#define O24_IRQ_I2C6            (O24_IRQ_GIC_START+32)
	#define O24_IRQ_I2C7            (O24_IRQ_GIC_START+33)
	#define O24_IRQ_I2C8            (O24_IRQ_GIC_START+34)
	#define O24_IRQ_I2C9            (O24_IRQ_GIC_START+35)
#endif
static LX_I2C_HW_MAP_T _stI2cHwMapO24Ax[] =
{
	{O24_I2C0_BASE,         O24_IRQ_I2C0},
	{O24_I2C1_BASE,         O24_IRQ_I2C1},
	{O24_I2C2_BASE,         O24_IRQ_I2C2},
	{O24_I2C3_BASE,         O24_IRQ_I2C3},
	{O24_I2C4_BASE,         O24_IRQ_I2C4},
	{O24_I2C5_BASE,         O24_IRQ_I2C5},
	{O24_I2C6_BASE,         O24_IRQ_I2C6},
	{O24_I2C7_BASE,         O24_IRQ_I2C7},
	{O24_I2C8_BASE,         O24_IRQ_I2C8},
	{O24_I2C9_BASE,         O24_IRQ_I2C9}
};
#endif

#ifdef INCLUDE_O26_CHIP_KDRV
#ifndef O26_I2C0_BASE
	#define O26_PERI_BASE           (0xfe000000)
	#define O26_I2C0_BASE           (O26_PERI_BASE+0x300000)
	#define O26_I2C1_BASE           (O26_PERI_BASE+0x400000)
	#define O26_I2C2_BASE           (O26_PERI_BASE+0x500000)
	#define O26_I2C3_BASE           (O26_PERI_BASE+0x600000)
	#define O26_SPI0_BASE           (O26_PERI_BASE+0x800000)
	#define O26_SPI1_BASE           (O26_PERI_BASE+0x900000)

	#define	O26_I2C_BASE            (0xf9000000)
	#define O26_I2C4_BASE           (O26_I2C_BASE+0x000000)
	#define O26_I2C5_BASE           (O26_I2C_BASE+0x100000)
	#define O26_I2C6_BASE           (O26_I2C_BASE+0x200000)
	#define O26_I2C7_BASE           (O26_I2C_BASE+0x300000)
	#define O26_I2C8_BASE           (O26_I2C_BASE+0x400000)
	#define O26_I2C9_BASE           (O26_I2C_BASE+0x500000)

	#define O26_IRQ_GIC_START       32
	#define O26_IRQ_I2C0            (O26_IRQ_GIC_START+26)
	#define O26_IRQ_I2C1            (O26_IRQ_GIC_START+27)
	#define O26_IRQ_I2C2            (O26_IRQ_GIC_START+28)
	#define O26_IRQ_I2C3            (O26_IRQ_GIC_START+29)
	#define O26_IRQ_I2C4            (O26_IRQ_GIC_START+30)
	#define O26_IRQ_I2C5            (O26_IRQ_GIC_START+31)
	#define O26_IRQ_I2C6            (O26_IRQ_GIC_START+32)
	#define O26_IRQ_I2C7            (O26_IRQ_GIC_START+33)
	#define O26_IRQ_I2C8            (O26_IRQ_GIC_START+34)
	#define O26_IRQ_I2C9            (O26_IRQ_GIC_START+35)
#endif
static LX_I2C_HW_MAP_T _stI2cHwMapO26Ax[] =
{
	{O26_I2C0_BASE,         O26_IRQ_I2C0},
	{O26_I2C1_BASE,         O26_IRQ_I2C1},
	{O26_I2C2_BASE,         O26_IRQ_I2C2},
	{O26_I2C3_BASE,         O26_IRQ_I2C3},
	{O26_I2C4_BASE,         O26_IRQ_I2C4},
	{O26_I2C5_BASE,         O26_IRQ_I2C5},
	{O26_I2C6_BASE,         O26_IRQ_I2C6},
	{O26_I2C7_BASE,         O26_IRQ_I2C7},
	{O26_I2C8_BASE,         O26_IRQ_I2C8},
	{O26_I2C9_BASE,         O26_IRQ_I2C9}
};
#endif



static LX_I2C_CFG_T _stI2cDefaultConfigs[] =
{
// caution: new chip should be added on bottom index
#ifdef INCLUDE_M17_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(M17,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_M17,
		.hw_map 			= _stI2cHwMapM17Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_L18_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(L18,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_L18,
		.hw_map 			= _stI2cHwMapL18Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_O18_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(O18,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_O18,
		.hw_map 			= _stI2cHwMapO18Ax,
		.max_gpio_devices	= 4,
	},
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(M19,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_M19,
		.hw_map 			= _stI2cHwMapM19Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_O20_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(O20,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_O20,
		.hw_map 			= _stI2cHwMapO20Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_E60_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(E60,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_E60,
		.hw_map 			= _stI2cHwMapE60Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_O22_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(O22,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_O22,
		.hw_map 			= _stI2cHwMapO22Ax,
		.max_gpio_devices	= 4,
	},
#endif

#ifdef INCLUDE_M23_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(M23,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_M23,
		.hw_map 			= _stI2cHwMapM23Ax,
		.max_gpio_devices	= 0,
	},
#endif

#ifdef INCLUDE_O24_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(O24,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_O24,
		.hw_map 			= _stI2cHwMapO24Ax,
		.max_gpio_devices	= 0,
	},
#endif

#ifdef INCLUDE_O26_CHIP_KDRV
	{
		.chip				= LX_CHIP_REV(O26,A0),
		.num_hw_devices 	= 10,
		.clock_freq 		= I2C_CLOCK_FREQUENCY_O26,
		.hw_map 			= _stI2cHwMapO26Ax,
		.max_gpio_devices	= 0,
	},
#endif

};


static	UINT32	g_i2c_sw_cfg = LX_I2C_CFG_NONE;	/* default config */

void	I2C_CFG_Init(void);
/*========================================================================================
	Implementation Group
========================================================================================*/
LX_I2C_CFG_T* I2C_GetConfig(void)
{
	int i;
	LX_I2C_CFG_T* config = NULL;
	UINT32 chip = lx_chip_rev();

	for(i=0; i < sizeof(_stI2cDefaultConfigs)/sizeof(LX_I2C_CFG_T); i++)
	{
		if(chip >= _stI2cDefaultConfigs[i].chip)
		{
			config = &_stI2cDefaultConfigs[i];
		}
		else
		{
			break;
		}
	}

	return config;
}

void	I2C_CFG_Init(void)
{
	// TODO: fix your default g_i2c_sw_cfg;
    switch(lx_chip())
    {
        case LX_CHIP_M19:
        case LX_CHIP_O18:
        case LX_CHIP_O20:
        case LX_CHIP_E60:
        case LX_CHIP_O22:
        case LX_CHIP_M23:
        case LX_CHIP_O24:
        case LX_CHIP_O26:
			g_i2c_sw_cfg = LX_I2C_CFG_NONE;	break;
        case LX_CHIP_M17:
			if(lx_chip_rev() >= LX_CHIP_REV(M17,C0))
			{
				g_i2c_sw_cfg = LX_I2C_CFG_NONE;
			}
			else
			{
				g_i2c_sw_cfg = LX_I2C_CFG_LEGACY_MODE;
			}
		break;

		case LX_CHIP_L18:	g_i2c_sw_cfg = LX_I2C_CFG_LEGACY_MODE; break;
        default:            g_i2c_sw_cfg = LX_I2C_CFG_LEGACY_MODE; break;
    }

	// parse user-defined configuration
	{
		char	optstr[80];

		if (RET_OK == OS_ScanKernelCmdline("use_legacy_i2c=%s", optstr))
		{
			if		(optstr[0] == '1') 	{ g_i2c_sw_cfg |= LX_I2C_CFG_LEGACY_MODE; }
			else if	(optstr[0] == '0')	{ g_i2c_sw_cfg &= ~LX_I2C_CFG_LEGACY_MODE;}
			else						{ /* keep current config */ }
		}
	}

	printk("+ I2C.SW_CFG = 0x%08x\n", g_i2c_sw_cfg);
}

UINT32   lx_i2c_cfg(void)
{
	return g_i2c_sw_cfg;
}

/** @} */

