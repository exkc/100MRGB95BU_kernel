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
 *  date			2016.04.29
 *  note			Additional information.
 *
 *  @addtogroup lg1313_pm
 */

/*----------------------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------
	File Inclusions
----------------------------------------------------------------------------------------*/
#include <linux/io.h>
#include <linux/mutex.h>
#include "os_util.h"

#include "pm_o18common.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef PM_DEBUG_PRINT_ENABLE
//#define PM_DEBUG_PRINT_ENABLE
#ifdef PM_DEBUG_PRINT_ENABLE
#define PM_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define PM_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif

#define VDEC0_BASE 0xC9C701C0
#define VDEC1_BASE 0xC9C711C0


/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
static DEFINE_SPINLOCK(g_o18_pm_cg_lock);

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
	global Functions
---------------------------------------------------------------------------------------*/

// Clock Gating
LX_PM_CLOCKGATING_T o18_pms_clockgating;

typedef struct PM_O18_CGINFO_t
{
	unsigned int module;
	unsigned int sub;
	unsigned int sub_max;
	unsigned int base;
	unsigned int clkbit;
	unsigned int clkbit2;
}
PM_O18_CGINFO_T;




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

static int o18_GetCGInfo(PM_O18_CGINFO_T *cginfo)
{
	int ret = 0;

	cginfo->clkbit2 = 0x80000000;

	if (cginfo->module == PM_VDEC)
	{
		if (cginfo->sub == PM_VDEC0_G1) {
			cginfo->base = VDEC0_BASE;
			cginfo->clkbit = 2;
		} else if (cginfo->sub == PM_VDEC0_HEVC) {
			cginfo->base = VDEC0_BASE;
			cginfo->clkbit = 6;
		} else if (cginfo->sub == PM_VDEC1_G1) {
			cginfo->base = VDEC1_BASE;
			cginfo->clkbit = 2;
		} else if (cginfo->sub == PM_VDEC1_HEVC) {
			cginfo->base = VDEC1_BASE;
			cginfo->clkbit = 1;
			cginfo->clkbit2 = 2;
		} else {
			ret = -1;
		}
	} else {
		ret = -1;
	}

	return ret;
}

int o18_clock_on(PM_O18_CGINFO_T cginfo)
{
	void __iomem *pms_clock_gating_base = NULL;
	volatile unsigned int reg;
	unsigned long flags;

	pms_clock_gating_base = ioremap(cginfo.base, 4096);

	spin_lock_irqsave(&g_o18_pm_cg_lock, flags);

	// clock first when power on
	PM_DEBUG_PRINT("O18 ON CG 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
	reg = readl(pms_clock_gating_base);
	reg = reg & ~(1 << cginfo.clkbit);
	writel(reg, pms_clock_gating_base);
	PM_DEBUG_PRINT("O18 ON CG 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
	if (cginfo.clkbit2 != 0x80000000)
	{
		PM_DEBUG_PRINT("O18 ON CG2 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
		reg = readl(pms_clock_gating_base);
		reg = reg & ~(1 << cginfo.clkbit2);
		writel(reg, pms_clock_gating_base);
		PM_DEBUG_PRINT("O18 ON CG2 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
	}

	spin_unlock_irqrestore(&g_o18_pm_cg_lock, flags);

	iounmap(pms_clock_gating_base);

	return 0;

}

int o18_clock_off(PM_O18_CGINFO_T cginfo)
{
	void __iomem *pms_clock_gating_base = NULL;
	volatile unsigned int reg;
	unsigned long flags;

	pms_clock_gating_base = ioremap(cginfo.base, 4096);

	spin_lock_irqsave(&g_o18_pm_cg_lock, flags);

	// clk late when power down
	PM_DEBUG_PRINT("O18 OFF CG 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
	reg = readl(pms_clock_gating_base);
	reg = reg | (1 << cginfo.clkbit);
	writel(reg, pms_clock_gating_base);
	PM_DEBUG_PRINT("O18 OFF CG 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));

	if (cginfo.clkbit2 != 0x80000000)
	{
		PM_DEBUG_PRINT("O18 OFF CG2 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
		reg = readl(pms_clock_gating_base);
		reg = reg | (1 << cginfo.clkbit2);
		writel(reg, pms_clock_gating_base);
		PM_DEBUG_PRINT("O18 OFF CG2 0x%X : 0x%X\n",cginfo.base,readl(pms_clock_gating_base));
	}

	spin_unlock_irqrestore(&g_o18_pm_cg_lock, flags);

	iounmap(pms_clock_gating_base);

	return 0;
}

int o18_set_clock_gating(unsigned int module, unsigned int sub, unsigned int state)
{
	PM_O18_CGINFO_T cginfo;
	int ret;

	if (( lx_chip_rev() & 0xFFFFFF00) != (LX_CHIP_REV(O18,A0) & 0xFFFFFF00))
		return 0;

	if ((module == PM_NULL) || (module > PM_MAX))
		return -1;

	PM_DEBUG_PRINT("Set Module %u\n",module);
	PM_DEBUG_PRINT("Set Sub 0x%X\n",sub);

	cginfo.module = module;
	cginfo.sub = sub;
	ret = o18_GetCGInfo(&cginfo);
	if (ret < 0)
		return -2;

	PM_DEBUG_PRINT("Set reg 0x%X, cginfo.clkbit %u\n", cginfo.base, cginfo.clkbit);

	if (state == PM_CLK_ON) // POWER ON
		o18_clock_on(cginfo);
	else
		o18_clock_off(cginfo);

	return 0;
}

int o18_get_clock_gating(unsigned int module, unsigned int sub, unsigned int *state)
{
	void __iomem *pms_clock_gating_base = NULL;
	PM_O18_CGINFO_T cginfo;
	volatile unsigned int reg;
	int ret;
	unsigned long flags;
	unsigned int st = 0;

	if (( lx_chip_rev() & 0xFFFFFF00) != (LX_CHIP_REV(O18,A0) & 0xFFFFFF00))
		return 0;

	if ((module == PM_NULL) || (module > PM_MAX))
		return -1;

	PM_DEBUG_PRINT("Get Module %u\n", module);
	PM_DEBUG_PRINT("Get SubModule %u\n", sub);

	cginfo.module = module;
	cginfo.sub = sub;

	ret = o18_GetCGInfo(&cginfo);
	if (ret < 0)
		return -1;

	pms_clock_gating_base = ioremap(cginfo.base, 4096);

	spin_lock_irqsave(&g_o18_pm_cg_lock, flags);

	reg = readl(pms_clock_gating_base);

	PM_DEBUG_PRINT("Get reg 0x%X - 0x%X, cginfo.clkbit %u\n",cginfo.base, reg, cginfo.clkbit);

	if (reg & (1 << cginfo.clkbit))
		st = 1;

	PM_DEBUG_PRINT("Get st 0x%X\n",st);

	*state = st;

	spin_unlock_irqrestore(&g_o18_pm_cg_lock, flags);

	iounmap(pms_clock_gating_base);

	return 0;
}


/**
 * ioctl handler for pm device.
 *
 *
 * note: if you have some critial data, you should protect them using semaphore or spin lock.
 */
int o18_pm_ioctl_cg (unsigned int cmd, unsigned long arg)
{
	int ret = 0;
	int result = 0;

	switch (cmd)
	{
		case PM_SET_CLOCK_GATING:
			result = copy_from_user((void *)&o18_pms_clockgating, (void __user *)arg, sizeof(o18_pms_clockgating));
			if (result) {
				PM_ERROR("PM_SET_CLOCK_GATING - CONFIG DATA COPY FAIL\n");
				break;
			}

			o18_set_clock_gating(o18_pms_clockgating.module, o18_pms_clockgating.sub, o18_pms_clockgating.state);
			break;
		case PM_GET_CLOCK_GATING:
			result = copy_from_user((void *)&o18_pms_clockgating, (void __user *)arg, sizeof(o18_pms_clockgating));
			if (result) {
				PM_ERROR("PM_GET_CLOCK_GATING - CONFIG DATA COPY FAIL - FROM USER\n");
				break;
			}

			o18_get_clock_gating(o18_pms_clockgating.module, o18_pms_clockgating.sub, &o18_pms_clockgating.state);

			ret = copy_to_user((void __user*)(arg), (void *)(&o18_pms_clockgating), sizeof(o18_pms_clockgating));
			if (ret)
				PM_ERROR("CONFIG DATA COPY FAIL\n");
			if (result)
				PM_ERROR("PM_GET_CLOCK_GATING - CONFIG DATA COPY FAIL - TO USER\n");
			break;
		default:
			ret = -1;
			break;
	}

    return ret;
}

static pms_o18_cg_t o18_pm_cg =
{
	.ioctl = o18_pm_ioctl_cg,
};

pms_o18_cg_t* get_o18_pm_cg(void)
{
	return &o18_pm_cg;
}

