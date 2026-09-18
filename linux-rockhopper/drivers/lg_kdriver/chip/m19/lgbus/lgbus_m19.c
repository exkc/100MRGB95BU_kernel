/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2016 by LG Electronics Inc.
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
 *  main configuration file for lgbus device
 *	lgbus device will teach you how to make device driver with new platform.
 *
 *  author		raxis.lim@lge.com
 *  version		1.0
 *  date		2015.04.22
 *  note		Additional information.
 *
 *  @addtogroup lg115x_lgbus
 *	@{
 */


/*----------------------------------------------------------------------------------------
  Control Constants
  ----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  File Inclusions
  ----------------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>	/**< lgbus_debug() */
#include <linux/slab.h> 	/**< kmalloc() */
#include <linux/fs.h> 		/**< everything\ldots{} */
#include <linux/types.h> 	/**< size_t */
#include <linux/fcntl.h>	/**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>	/**< For request_region, check_region etc */
#include <asm/io.h>			/**< For ioremap_nocache */

#include <linux/interrupt.h>/** irqreturn_t */
#include <linux/irq.h>		/** platform interrupt */
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/sched.h>

#include <linux/delay.h>
#include <linux/vmalloc.h>

#include "os_util.h"
#include "sys_regs.h"

#include "lgbus_drv.h"
#include "lgbus_hw.h"

/*----------------------------------------------------------------------------------------
  Constant Definitions
----------------------------------------------------------------------------------------*/
#define	DDR0_CLK			1308	/* 1308 MHz -- FIXME */
#define	DDR1_CLK			1308	/* 1308 MHz -- FIXME */

/*----------------------------------------------------------------------------------------
  Macro Definitions
----------------------------------------------------------------------------------------*/
#define REG_OFF_INTR_EN     0x14
#define REG_OFF_INTR_CLR    0x1C

/*----------------------------------------------------------------------------------------
  Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    volatile void*		bus_reg[QOS_IDX_MAX];		// ioremapped bus register
}
LGBUS_CHIP_CTX_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
----------------------------------------------------------------------------------------*/
extern lgbus_m19_mpro_func_t	lgbus_m19_mpro_func;

/*----------------------------------------------------------------------------------------
  global Variables
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  Static Function Prototypes Declarations
----------------------------------------------------------------------------------------*/
static int lgbus_open(void);
static int lgbus_close(void);

/*----------------------------------------------------------------------------------------
  Static Variables
----------------------------------------------------------------------------------------*/
static const LGBUS_PMT_ITEM_DESC_T pmt_chip_desc[] =
{
//              ----------------------ORG---------------------------------------   -----------------------DUMMY--------------------------------------
// 		   		  LBUS.WR    LBUS.RD    GBUS.WR    GBUS.RD                            LBUS.WR    LBUS.RD    GBUS.WR    GBUS.RD
//              ----------------------------------------------------------------   ------------------------------------------------------------------
{"CPU_M0",		{{{0xC9820810,0xC9820814},{0xC9820A10,0xC9820A14},{0x00000000,0x00000000}},{{0xC9820820,0xC9820824},{0xC9820A20,0xC9820A24},{0x00000000,0x00000000}}}},
{"GPU",			{{{0xC9822110,0xC9822114},{0xC9822120,0xC9822124},{0x00000000,0x00000000}},{{0xC9822130,0xC9822134},{0xC9822138,0xC982213C},{0x00000000,0x00000000}}}},
{"GFX",			{{{0xC9822310,0xC9822314},{0xC9822320,0xC9822324},{0x00000000,0x00000000}},{{0xC9822330,0xC9822334},{0xC9822338,0xC982233C},{0x00000000,0x00000000}}}},
{"TI",			{{{0xC9822510,0xC9822514},{0xC9822520,0xC9822524},{0x00000000,0x00000000}},{{0xC9822530,0xC9822534},{0xC9822538,0xC982253C},{0x00000000,0x00000000}}}},
{"AUD",			{{{0xC9822710,0xC9822714},{0xC9822720,0xC9822724},{0x00000000,0x00000000}},{{0xC9822730,0xC9822734},{0xC9822738,0xC982273C},{0x00000000,0x00000000}}}},
{"VDEC0_M0",	{{{0xC9822910,0xC9822914},{0xC9822920,0xC9822924},{0x00000000,0x00000000}},{{0xC9822930,0xC9822934},{0xC9822938,0xC982293C},{0x00000000,0x00000000}}}},
{"VDEC0_M1",	{{{0xC9822B10,0xC9822B14},{0xC9822B20,0xC9822B24},{0x00000000,0x00000000}},{{0xC9822B30,0xC9822B34},{0xC9822B38,0xC9822B3C},{0x00000000,0x00000000}}}},
{"VDEC1_M0",	{{{0xC9822D10,0xC9822D14},{0xC9822D20,0xC9822D24},{0x00000000,0x00000000}},{{0xC9822D30,0xC9822D34},{0xC9822D38,0xC9822D3C},{0x00000000,0x00000000}}}},
{"VDEC1_M1",	{{{0xC9822F10,0xC9822F14},{0xC9822F20,0xC9822F24},{0x00000000,0x00000000}},{{0xC9822F30,0xC9822F34},{0xC9822F38,0xC9822F3C},{0x00000000,0x00000000}}}},
{"MCU",			{{{0xC9823110,0xC9823114},{0xC9823120,0xC9823124},{0x00000000,0x00000000}},{{0xC9823130,0xC9823134},{0xC9823138,0xC982313C},{0x00000000,0x00000000}}}},
{"CCO",			{{{0x00000000,0xC9823314},{0x00000000,0xC9823324},{0x00000000,0x00000000}},{{0x00000000,0xC9823334},{0x00000000,0xC982333C},{0x00000000,0x00000000}}}},
{"FMC0",		{{{0xC9823510,0xC9823514},{0xC9823520,0xC9823524},{0x00000000,0x00000000}},{{0xC9823530,0xC9823534},{0xC9823538,0xC982353C},{0x00000000,0x00000000}}}},
{"FMC1",		{{{0xC9823710,0xC9823714},{0xC9823720,0xC9823724},{0x00000000,0x00000000}},{{0xC9823730,0xC9823734},{0xC9823738,0xC982373C},{0x00000000,0x00000000}}}},
{"TCON",		{{{0xC9823910,0xC9823914},{0xC9823920,0xC9823924},{0x00000000,0x00000000}},{{0xC9823930,0xC9823934},{0xC9823938,0xC982393C},{0x00000000,0x00000000}}}},
{"ME0",			{{{0xC9823B10,0xC9823B14},{0xC9823B20,0xC9823B24},{0x00000000,0x00000000}},{{0xC9823B30,0xC9823B34},{0xC9823B38,0xC9823B3C},{0x00000000,0x00000000}}}},
{"FMS0",		{{{0xC9823D10,0xC9823D14},{0xC9823D20,0xC9823D24},{0x00000000,0x00000000}},{{0xC9823D30,0xC9823D34},{0xC9823D38,0xC9823D3C},{0x00000000,0x00000000}}}},
{"CVI",			{{{0xC9101110,0xC9101114},{0xC9101120,0xC9101124},{0x00000000,0x00000000}},{{0xC9101130,0xC9101134},{0xC9101138,0xC910113C},{0x00000000,0x00000000}}}},
{"SRE_VDM0",	{{{0xC9101310,0xC9101314},{0xC9101320,0xC9101324},{0x00000000,0x00000000}},{{0xC9101330,0xC9101334},{0xC9101338,0xC910133C},{0x00000000,0x00000000}}}},
{"VDM1",		{{{0x00000000,0xC9101514},{0x00000000,0xC9101524},{0x00000000,0x00000000}},{{0x00000000,0xC9101534},{0x00000000,0xC910153C},{0x00000000,0x00000000}}}},
{"SMX0",		{{{0xC9101710,0xC9101714},{0xC9101720,0xC9101724},{0x00000000,0x00000000}},{{0xC9101730,0xC9101734},{0xC9101738,0xC910173C},{0x00000000,0x00000000}}}},
{"SMX1",		{{{0xC9101910,0xC9101914},{0xC9101920,0xC9101924},{0x00000000,0x00000000}},{{0xC9101930,0xC9101934},{0xC9101938,0xC910193C},{0x00000000,0x00000000}}}},
{"ND0",			{{{0xC9101B10,0xC9101B14},{0xC9101B20,0xC9101B24},{0x00000000,0x00000000}},{{0xC9101B30,0xC9101B34},{0xC9101B38,0xC9101B3C},{0x00000000,0x00000000}}}},
{"ND1",			{{{0xC9101D10,0xC9101D14},{0xC9101D20,0xC9101D24},{0x00000000,0x00000000}},{{0xC9101D30,0xC9101D34},{0xC9101D38,0xC9101D3C},{0x00000000,0x00000000}}}},
{"GSC0",		{{{0x00000000,0xC9102114},{0x00000000,0xC9102124},{0x00000000,0x00000000}},{{0x00000000,0xC9102134},{0x00000000,0xC910213C},{0x00000000,0x00000000}}}},
{"GSC1",		{{{0x00000000,0xC9102314},{0x00000000,0xC9102324},{0x00000000,0x00000000}},{{0x00000000,0xC9102334},{0x00000000,0xC910233C},{0x00000000,0x00000000}}}},
{"ME1",			{{{0xC9102510,0xC9102514},{0xC9102520,0xC9102524},{0x00000000,0x00000000}},{{0xC9102530,0xC9102534},{0xC9102538,0xC910253C},{0x00000000,0x00000000}}}},
{"DBB",			{{{0xC9102710,0xC9102714},{0xC9102720,0xC9102724},{0x00000000,0x00000000}},{{0xC9102730,0xC9102734},{0xC9102738,0xC910273C},{0x00000000,0x00000000}}}},
{"VENC",		{{{0xC9102910,0xC9102914},{0xC9102920,0xC9102924},{0x00000000,0x00000000}},{{0xC9102930,0xC9102934},{0xC9102938,0xC910293C},{0x00000000,0x00000000}}}},

{"PORT0",		{{{0xC9821010,0xC9821014},{0xC9821810,0xC9821814},{0x00000000,0x00000000}},{{0xC9821020,0xC9821024},{0xC9821820,0xC9821824},{0x00000000,0x00000000}}}},
{"PORT1",		{{{0xC9821210,0xC9821214},{0xC9821A10,0xC9821A14},{0x00000000,0x00000000}},{{0xC9821220,0xC9821224},{0xC9821A20,0xC9821A24},{0x00000000,0x00000000}}}},
{"PORT2",		{{{0xC9821410,0xC9821414},{0xC9821C10,0xC9821C14},{0x00000000,0x00000000}},{{0xC9821420,0xC9821424},{0xC9821C20,0xC9821C24},{0x00000000,0x00000000}}}},
{"PORT3",		{{{0xC9821610,0xC9821614},{0xC9821E10,0xC9821E14},{0x00000000,0x00000000}},{{0xC9821620,0xC9821624},{0xC9821E20,0xC9821E24},{0x00000000,0x00000000}}}},


};

static LGBUS_CHIP_CTX_T lgbus_chip_ctx;
static LGBUS_HW_CFG_T	lgbus_chip_cfg =
{
	.rf_timer_init	= 0x20,
	.irq_num		= 139,	// {139,121}

	.ddr_num		= 2,
	.ip_num			= 28,
	.port_num		= 4,

	.bus_reg_base	= {0xC9820000, 0xC9100000, 0xC9231000 },	// LBUS, GBUS, CPU
	.freq			= {396, 396, 528},							// LBUS, GBUS, CPU
};

/*========================================================================================
    Implementation Group
========================================================================================*/

static int lgbus_config(LGBUS_HW_CFG_T* cfg)
{
	// collect system info & calcuate some variables
	lgbus_chip_cfg.max_bw[0] = DDR0_CLK * 2 * 4;
	lgbus_chip_cfg.max_bw[1] = DDR1_CLK * 2 * 4;

	lgbus_chip_cfg.pmt_desc = pmt_chip_desc;

	memcpy(cfg, &lgbus_chip_cfg, sizeof(LGBUS_HW_CFG_T));

	return RET_OK;
}

static int lgbus_init(void)
{
	memset(&lgbus_chip_ctx, 0x0, sizeof(LGBUS_CHIP_CTX_T));

	lgbus_m19_mpro_func.init();

	return RET_OK;
}

static int lgbus_cleanup(void)
{
	lgbus_m19_mpro_func.cleanup();

	return RET_OK;
}

static int lgbus_open(void)
{
	int	i;

	for (i=0; i<QOS_IDX_MAX; i++)
	{
		if(lgbus_chip_ctx.bus_reg[i]==0x0)
		{
   			lgbus_chip_ctx.bus_reg[i] = (volatile void*)ioremap(lgbus_chip_cfg.bus_reg_base[i], 0x200);
		}
	}

	return RET_OK;
}

static int lgbus_close(void)
{
	int	i;

	for (i=0; i<QOS_IDX_MAX; i++)
	{
		if(lgbus_chip_ctx.bus_reg[i])
		{
			iounmap((volatile void *)lgbus_chip_ctx.bus_reg[i]);
			lgbus_chip_ctx.bus_reg[i] = 0x0;
		}
	}

	return RET_OK;
}
static int lgbus_resume(void)
{
	int ret = lgbus_m19_mpro_func.resume();
	LGBUS_CHECK_CODE(ret != RET_OK, return RET_ERROR, "lgbus_mpro resume FAIL\n");;

	return RET_OK;
}

static int lgbus_suspend(void)
{
	lgbus_m19_mpro_func.suspend();

	return RET_OK;
}

/* general HW command execution */
static int lgbus_hwcmd(LGBUS_HW_CMD_ID_T cmdId, LGBUS_HW_DATA_T* data)
{
	int	i;

	switch(cmdId)
	{
		case LGBUS_HW_CMD_TIMER_INIT:
		{
			for(i=0; i<QOS_IDX_MAX; i++)
			{
				LGBUS_WrFL(lgbus_chip_ctx.bus_reg[i] + lgbus_chip_cfg.rf_timer_init, data->gen[i]);
			}
		}
		break;

		case LGBUS_HW_CMD_PQE_PERF_INIT:
		{
			/* do nothing */
		}
		break;

		case LGBUS_HW_CMD_INTR_ENABLE:
		{
			LGBUS_WrFL(lgbus_chip_ctx.bus_reg[QOS_IDX_LBUS] + REG_OFF_INTR_EN, 0x1);
		}
		break;

		case LGBUS_HW_CMD_INTR_DISABLE:
		{
			LGBUS_WrFL(lgbus_chip_ctx.bus_reg[QOS_IDX_LBUS] + REG_OFF_INTR_EN, 0x0);
		}
		break;

		case LGBUS_HW_CMD_INTR_HANDLER:
		{
			/* do nothing except intr clear */
			LGBUS_WrFL(lgbus_chip_ctx.bus_reg[QOS_IDX_LBUS] + REG_OFF_INTR_CLR, 0x1);
		}
		break;

		default:
		{
			/* do nothing */
		}
		break;
	}

	return RET_OK;
}

static void lgbus_proc(LGBUS_HW_PROC_ID_T id, struct seq_file* m, LGBUS_HW_DATA_T* data)
{

	return;
}

/*========================================================================================
    Implementation Group (LGBUS M16 DESC)
========================================================================================*/
static LGBUS_HW_FUNC_T m19_lgbus_hw_func =
{
	.do_config		= lgbus_config,
	.do_init		= lgbus_init,
	.do_cleanup		= lgbus_cleanup,
	.do_open		= lgbus_open,
	.do_close		= lgbus_close,
	.do_resume 		= lgbus_resume,
	.do_suspend 	= lgbus_suspend,

	.do_hwcmd		= lgbus_hwcmd,
	.do_proc		= lgbus_proc,
};

LGBUS_HW_FUNC_T* LGBUS_M19_Init(void)
{
	return &m19_lgbus_hw_func;
}
