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
/*
 * @file
 *
 *
 *  author		hankyung.yu (hankyung.yu@lge.com)
 *  version		1.0
 *  date		2017.08.03
 *  note		Additional information.
 *              Synopsys MMC/SDHCI Controller
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
#include <linux/platform_device.h>

#include <asm/uaccess.h>
#include <linux/poll.h>
#include "os_util.h"
#include "base_device.h"
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/cpu.h>
#include <linux/io.h>

#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel_stat.h>
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/suspend.h>

#include <linux/tick.h>
#include <trace/events/power.h>

#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>

#include <emmc_drv.h>


/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/
#undef EMMC_DEBUG_PRINT_ENABLE
#ifdef EMMC_DEBUG_PRINT_ENABLE
#define EMMC_DEBUG_PRINT(fmt, args...)		do {printk(fmt, ##args);} while (0)
#else
#define EMMC_DEBUG_PRINT(fmt, args...)		do{}while(0)
#endif

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#ifdef INCLUDE_O22_CHIP_KDRV
#define EMMC_O22_TOP_BASE 				0xc8042000
#define EMMC_O22_BASE					0xc8040000
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
#define EMMC_M23_TOP_BASE				0xC4742000
#define EMMC_M23_BASE					0xc4740000
#endif

#define EMMC_VENDOR1_BASE			0x100
#define _MSHC_CTRL_R				0x8
#define _MMC_CTRL_R					0x2c
#define _AT_CTRL_R					0x40
#define _AT_STAT_R					0x44

#define EMMC_CMDQ_BASE				0x200
#define EMMC_VENDOR2_BASE			0x300
#define _PHY_CNFG					0x00
#define _SDCLKDL_CNFG				0x1c
#define _SMPLDL_CNFG				0x20
#define _DLL_CTRL_CNFG 				0x24
#define _DLL_DLCNFG_OFFST_MSTTSTDC	0x28
#define _DLL_STAT_BTCNFG 			0x2c

#define CLOCK_NOT_INVERT			0
#define CLOCK_INVERT				1

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	External Function Prototype Declarations
----------------------------------------------------------------------------------------*/
extern void EMMC_HexView(char *addr, unsigned int size, unsigned int address);

/*----------------------------------------------------------------------------------------
	External Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	global Functions
---------------------------------------------------------------------------------------*/

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
static phys_addr_t SynGetEmmcBase(void)
{
#ifdef INCLUDE_O22_CHIP_KDRV
	if ( lx_chip() == LX_CHIP_O22 )
		return  EMMC_O22_BASE;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	if ( lx_chip() == LX_CHIP_M23 )
		return  EMMC_M23_BASE;
#endif

	return 0;
}

static phys_addr_t SynGetEmmcTopBase(void)
{
#ifdef INCLUDE_O22_CHIP_KDRV
	if ( lx_chip() == LX_CHIP_O22 )
		return  EMMC_O22_TOP_BASE;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
	if ( lx_chip() == LX_CHIP_M23 )
		return  EMMC_M23_TOP_BASE;
#endif

	return 0;
}


static unsigned int SynGetEmmcIntap(void)
{
	unsigned int reg;
	unsigned int intap;
	void __iomem *emmc_base = NULL;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_base = ioremap(SynGetEmmcBase(), 0x400);
	if (emmc_base == NULL)
		return 0;

	intap = readl(emmc_base + EMMC_VENDOR1_BASE + _AT_STAT_R) & 0x7f;
	reg = readl(emmc_base + EMMC_VENDOR2_BASE + _SMPLDL_CNFG) & 0x1f;
	if (reg == 0x19)
		intap += 128;

	iounmap(emmc_base);

	return intap;
}

static unsigned int SynSetEmmcIntap(unsigned int intab)
{
	void __iomem *emmc_base = NULL;
	unsigned int delayconfig = 0x18;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_base = ioremap(SynGetEmmcBase(), 256);
	if (emmc_base == NULL)
		return 0;

	/* Setup RX delay line
	  enable S/W tune & enable Tune Clk Stop */
	writel(0x00010010, emmc_base + EMMC_VENDOR1_BASE + _AT_CTRL_R);

	if (intab >= 128) {
		intab = intab - 128;
		delayconfig = 0x19;
	}

	/* set RX delay code to 2 */
	writel(intab, emmc_base + EMMC_VENDOR1_BASE + _AT_STAT_R);

	/* through delayline &	input config 2 */
	writel(delayconfig, emmc_base + EMMC_VENDOR2_BASE + _SMPLDL_CNFG);

	iounmap(emmc_base);

	return 0;
}

static unsigned int SynGetEmmcOuttap(void)
{
	unsigned int reg;

	void __iomem *emmc_base = NULL;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_base = ioremap(SynGetEmmcBase(), 256);
	if (emmc_base == NULL)
		return 0;

	reg = readl(emmc_base + EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	reg = (reg >> 16) & 0x7f;

	iounmap(emmc_base);

	return reg;
}

static void out_phase(unsigned int invert)
{
	unsigned int reg = 0;
	void __iomem *emmc_top = NULL;

	if (SynGetEmmcTopBase() == 0)
		return;

	emmc_top = ioremap(SynGetEmmcTopBase(), 256);
	if (emmc_top == NULL)
		return;

#define TOP_CLOCK_CONTROL 0x18

	/* not inverting gated cclk_tx applied to EMMC */
	if (invert == CLOCK_NOT_INVERT)
		reg = 0x1;

	writel(reg, emmc_top + TOP_CLOCK_CONTROL);

	iounmap(emmc_top);
}

static unsigned int SynSetEmmcOuttap(unsigned int outtap)
{
	unsigned int reg;
	void __iomem *emmc_base = NULL;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_base = ioremap(SynGetEmmcBase(), 256);
	if (emmc_base == NULL)
		return 0;

	/* setup TX delay line */
	writel(0x00001000, emmc_base + EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	reg = (outtap << 16) + 0x1000;
	writel(reg, emmc_base + EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	reg = (outtap << 16);
	writel(reg, emmc_base + EMMC_VENDOR2_BASE + _SDCLKDL_CNFG);

	iounmap(emmc_base);

	/* not inverting gated cclk_tx applied to EMMC */
	out_phase(CLOCK_NOT_INVERT);

	return 0;
}

static unsigned int SynGetEmmcHostDS(void)
{
	unsigned int reg;
	void __iomem *emmc_base = NULL;

    unsigned int dwc_ds[16] = {0x3, 0x0, 0x0, 0x0, 0x2,
								0x0, 0x0, 0x0, 0x0, 0x0,
								0x0, 0x4, 0x0, 0x0, 0x1, 0x0};

    unsigned int ds_conv[5] = {50, 33, 66, 100, 40};

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_base = ioremap(SynGetEmmcBase(), 256);
	if (emmc_base == NULL)
		return 0;

	reg = readl(emmc_base + EMMC_VENDOR2_BASE + _PHY_CNFG);
	reg &= 0x00f00000;
	reg = reg >> 20;

	iounmap(emmc_base);

	return ds_conv[dwc_ds[reg]];
}

static unsigned int SynSetEmmcHostDS(unsigned int ds)
{
	unsigned int reg;
	void __iomem *emmc_base = NULL;

    unsigned int jedec_ds[5] = {50, 33, 66, 100, 40};
    unsigned int conv_ds[5] = {8, 14, 4, 0, 11};
    unsigned int value;
    unsigned int i;

	if (SynGetEmmcBase() == 0)
		return 0;

    for (i=0; i<5; i++) {
        if (jedec_ds[i] == ds) {
            value = conv_ds[i];
            break;
        }
    }

	emmc_base = ioremap(SynGetEmmcBase(), 256);
	if (emmc_base == NULL)
		return 0;

	reg = readl(emmc_base + EMMC_VENDOR2_BASE + _PHY_CNFG);
	reg &= 0xff00ffff;
	reg |= ((ds << 16) + (ds << 20));
	writel(reg, emmc_base + EMMC_VENDOR2_BASE + _PHY_CNFG);

	iounmap(emmc_base);

	return 0;
}

static unsigned int SynTopRegDump(void)
{
#define TOP_SIZE 0x80

	unsigned int buff[TOP_SIZE/4];
	int i;

	void __iomem *emmc_top_base = NULL;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_top_base = ioremap(SynGetEmmcBase(), TOP_SIZE);
	if (emmc_top_base == NULL)
		return 0;

	for (i=0; i<(TOP_SIZE/4); i++)
		buff[i] = readl(emmc_top_base + (i*4));

	EMMC_HexView((char *)buff, TOP_SIZE, (unsigned int)SynGetEmmcTopBase());

	iounmap(emmc_top_base);

	return 0;
}

static unsigned int SynCntrRegDump(void)
{
#define DUMP_SIZE 0x400

	unsigned int buff[DUMP_SIZE/4];
	int i;

	void __iomem *emmc_cntr_base = NULL;

	if (SynGetEmmcBase() == 0)
		return 0;

	emmc_cntr_base = ioremap(SynGetEmmcBase(), DUMP_SIZE);
	if (emmc_cntr_base == NULL)
		return 0;

	for (i=0; i<(DUMP_SIZE/4); i++)
		buff[i] = readl(emmc_cntr_base + (i*4));

	EMMC_HexView((char *)buff, DUMP_SIZE, (unsigned int)SynGetEmmcBase());

	iounmap(emmc_cntr_base);

	return 0;
}

static emmc_func_t emmc_func =
{
	.GetEmmcIntap = SynGetEmmcIntap,
	.SetEmmcIntap = SynSetEmmcIntap,
	.GetEmmcOuttap = SynGetEmmcOuttap,
	.SetEmmcOuttap = SynSetEmmcOuttap,
	.GetEmmcHostDS = SynGetEmmcHostDS,
	.SetEmmcHostDS = SynSetEmmcHostDS,
	.TopRegDump = SynTopRegDump,
	.CntrRegDump = SynCntrRegDump,
};

emmc_func_t* get_emmc_func(void)
{
    return &emmc_func;
}