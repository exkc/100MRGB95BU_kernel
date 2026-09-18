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
#define	DDR0_CLK			1308	/* 1308 MHz */
#define	DDR1_CLK			1056	/* 1056 MHz */

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
    volatile void* bus_reg[QOS_IDX_MAX];	// ioremapped bus register
}
LGBUS_CHIP_CTX_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
----------------------------------------------------------------------------------------*/
extern lgbus_m16p_mpro_func_t	lgbus_m16p_mpro_func;

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
{"CPU_M0",		{{{0xC9823110,0xC9823114},{0xC9823120,0xC9823124},{0x00000000,0x00000000}},	{{0xC9823130,0xC9823134},{0xC9823138,0xC982313C},{0x00000000,0x00000000}}}},
{"GPU",			{{{0xC9823310,0xC9823314},{0xC9823320,0xC9823324},{0x00000000,0x00000000}},	{{0xC9823330,0xC9823334},{0xC9823338,0xC982333C},{0x00000000,0x00000000}}}},
{"GFX_M0",		{{{0xC9823510,0xC9823514},{0xC9823520,0xC9823524},{0x00000000,0x00000000}},	{{0xC9823530,0xC9823534},{0xC9823538,0xC982353C},{0x00000000,0x00000000}}}},
{"VENC_TE",		{{{0xC9823910,0xC9823914},{0xC9823920,0xC9823924},{0x00000000,0x00000000}},	{{0xC9823930,0xC9823934},{0xC9823938,0xC982393C},{0x00000000,0x00000000}}}},
{"AUD",			{{{0xC9823B10,0xC9823B14},{0xC9823B20,0xC9823B24},{0x00000000,0x00000000}},	{{0xC9823B30,0xC9823B34},{0xC9823B38,0xC9823B3C},{0x00000000,0x00000000}}}},
{"VDEC0_M0",	{{{0xC9823D10,0xC9823D14},{0xC9823D20,0xC9823D24},{0x00000000,0x00000000}},	{{0xC9823D30,0xC9823D34},{0xC9823D38,0xC9823D3C},{0x00000000,0x00000000}}}},
{"VDEC0_M1",	{{{0xC9823F10,0xC9823F14},{0xC9823F20,0xC9823F24},{0x00000000,0x00000000}},	{{0xC9823F30,0xC9823F34},{0xC9823F38,0xC9823F3C},{0x00000000,0x00000000}}}},
{"VDEC1_M0",	{{{0xC9824110,0xC9824114},{0xC9824120,0xC9824124},{0x00000000,0x00000000}},	{{0xC9824130,0xC9824134},{0xC9824138,0xC982413C},{0x00000000,0x00000000}}}},
{"VDEC1_M1",	{{{0xC9824310,0xC9824314},{0xC9824320,0xC9824324},{0x00000000,0x00000000}},	{{0xC9824330,0xC9824334},{0xC9824338,0xC982433C},{0x00000000,0x00000000}}}},
{"MCU",			{{{0xC9824510,0xC9824514},{0xC9824520,0xC9824524},{0x00000000,0x00000000}},	{{0xC9824530,0xC9824534},{0xC9824538,0xC982453C},{0x00000000,0x00000000}}}},
{"CCO",			{{{0x00000000,0xC9824714},{0x00000000,0xC9824724},{0x00000000,0x00000000}},	{{0x00000000,0xC9824734},{0x00000000,0xC982473C},{0x00000000,0x00000000}}}},
{"FMC_M0",		{{{0xC9824910,0xC9824914},{0xC9824920,0xC9824924},{0x00000000,0x00000000}},	{{0xC9824930,0xC9824934},{0xC9824938,0xC982493C},{0x00000000,0x00000000}}}},
{"FMC_M1",		{{{0xC9824B10,0xC9824B14},{0xC9824B20,0xC9824B24},{0x00000000,0x00000000}},	{{0xC9824B30,0xC9824B34},{0xC9824B38,0xC9824B3C},{0x00000000,0x00000000}}}},
{"TCON",		{{{0xC9824D10,0xC9824D14},{0xC9824D20,0xC9824D24},{0x00000000,0x00000000}},	{{0xC9824D30,0xC9824D34},{0xC9824D38,0xC9824D3C},{0x00000000,0x00000000}}}},
{"CPU_M1",		{{{0xC9824F10,0xC9824F14},{0xC9824F20,0xC9824F24},{0x00000000,0x00000000}},	{{0xC9824F30,0xC9824F34},{0xC9824F38,0xC9824F3C},{0x00000000,0x00000000}}}},
{"ME0",			{{{0xC9820510,0xC9820514},{0xC9820520,0xC9820524},{0x00000000,0x00000000}},	{{0xC9820530,0xC9820534},{0xC9820538,0xC982053C},{0x00000000,0x00000000}}}},
{"ME1",			{{{0xC9820710,0xC9820714},{0xC9820720,0xC9820724},{0x00000000,0x00000000}},	{{0xC9820730,0xC9820734},{0xC9820738,0xC982073C},{0x00000000,0x00000000}}}},
{"CVD",			{{{0xC9102110,0xC9102114},{0xC9102120,0xC9102124},{0x00000000,0x00000000}},	{{0xC9102130,0xC9102134},{0xC9102138,0xC910213C},{0x00000000,0x00000000}}}},
{"SRE",			{{{0xC9102310,0x00000000},{0xC9102320,0x00000000},{0x00000000,0x00000000}},	{{0xC9102330,0x00000000},{0xC9102338,0x00000000},{0x00000000,0x00000000}}}},
{"VDM0",		{{{0x00000000,0xC9102314},{0x00000000,0xC9102324},{0x00000000,0x00000000}},	{{0x00000000,0xC9102334},{0x00000000,0xC910233C},{0x00000000,0x00000000}}}},
{"VDM1",		{{{0x00000000,0xC9102514},{0x00000000,0xC9102524},{0x00000000,0x00000000}},	{{0x00000000,0xC9102534},{0x00000000,0xC910253C},{0x00000000,0x00000000}}}},
{"SMX0",		{{{0xC9102710,0xC9102714},{0xC9102720,0xC9102724},{0x00000000,0x00000000}},	{{0xC9102730,0xC9102734},{0xC9102738,0xC910273C},{0x00000000,0x00000000}}}},
{"SMX1",		{{{0xC9102910,0xC9102914},{0xC9102920,0xC9102924},{0x00000000,0x00000000}},	{{0xC9102930,0xC9102934},{0xC9102938,0xC910293C},{0x00000000,0x00000000}}}},
{"ND0",			{{{0xC9102B10,0xC9102B14},{0xC9102B20,0xC9102B24},{0x00000000,0x00000000}},	{{0xC9102B30,0xC9102B34},{0xC9102B38,0xC9102B3C},{0x00000000,0x00000000}}}},
{"GSC0",		{{{0x00000000,0xC9102D14},{0x00000000,0xC9102D24},{0x00000000,0x00000000}},	{{0x00000000,0xC9102D34},{0x00000000,0xC9102D3C},{0x00000000,0x00000000}}}},
{"GSC1",		{{{0x00000000,0xC9102F14},{0x00000000,0xC9102F24},{0x00000000,0x00000000}},	{{0x00000000,0xC9102F34},{0x00000000,0xC9102F3C},{0x00000000,0x00000000}}}},
{"FMS0",		{{{0xC9103110,0xC9103114},{0xC9103120,0xC9103124},{0x00000000,0x00000000}},	{{0xC9103130,0xC9103134},{0xC9103138,0xC910313C},{0x00000000,0x00000000}}}},
{"DBB",			{{{0xC9103510,0xC9103514},{0xC9103520,0xC9103524},{0x00000000,0x00000000}},	{{0xC9103530,0xC9103534},{0xC9103538,0xC910353C},{0x00000000,0x00000000}}}},
{"VENC",		{{{0xC9103B10,0xC9103B14},{0xC9103B20,0xC9103B24},{0x00000000,0x00000000}},	{{0xC9103B30,0xC9103B34},{0xC9103B38,0xC9103B3C},{0x00000000,0x00000000}}}},

{"PORT0",		{{{0xC9822010,0xC9822014},{0xC9822810,0xC9822814},{0x00000000,0x00000000}},	{{0xC9822020,0xC9822024},{0xC9822820,0xC9822824},{0x00000000,0x00000000}}}},
{"PORT1",		{{{0xC9822210,0xC9822214},{0xC9822A10,0xC9822A14},{0x00000000,0x00000000}},	{{0xC9822220,0xC9822224},{0xC9822A20,0xC9822A24},{0x00000000,0x00000000}}}},
{"PORT2",		{{{0xC9822410,0xC9822414},{0xC9822C10,0xC9822C14},{0x00000000,0x00000000}},	{{0xC9822420,0xC9822424},{0xC9822C20,0xC9822C24},{0x00000000,0x00000000}}}},
{"PORT3",		{{{0xC9822610,0xC9822614},{0xC9822E10,0xC9822E14},{0x00000000,0x00000000}},	{{0xC9822620,0xC9822624},{0xC9822E20,0xC9822E24},{0x00000000,0x00000000}}}},

};

static LGBUS_CHIP_CTX_T lgbus_chip_ctx;
static LGBUS_HW_CFG_T	lgbus_chip_cfg =
{
	.rf_timer_init	= 0x20,
	.irq_num		= 122,

	.ddr_num		= 2,
	.ip_num			= 29,
	.port_num		= 4,

	.bus_reg_base	= {0xC9820000, 0xC9100000, 0xC9231600 },	// LBUS, GBUS, CPU
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

	lgbus_m16p_mpro_func.init();

	return RET_OK;
}

static int lgbus_cleanup(void)
{
	lgbus_m16p_mpro_func.cleanup();

	return RET_OK;
}

static int lgbus_open(void)
{
	int	i;

	for (i=0; i<QOS_IDX_MAX; i++)
	{
		if(lgbus_chip_ctx.bus_reg[i]==0x0)
		{
   			lgbus_chip_ctx.bus_reg[i] = ioremap(lgbus_chip_cfg.bus_reg_base[i], 0x200);
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
	int ret = lgbus_m16p_mpro_func.resume();
	LGBUS_CHECK_CODE(ret != RET_OK, return RET_ERROR, "lgbus_mpro resume FAIL\n");;

	return RET_OK;
}

static int lgbus_suspend(void)
{
	lgbus_m16p_mpro_func.suspend();

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
			#define	SRE_BASE	0xC900A2E4
			#define	VCP_BASE	0xC900C09C
			#define	FMS_BASE	0xC90330E4
			#define	FMC_BASE	0xC90370E4
			UINT32 value;

			OS_RdReg(SRE_BASE, &value);
			value &= 0x88FFFFFF;		//init
			value |= 0x55000000;		//[30:28] 0x5, [26:24] 0x5
			OS_WrReg(SRE_BASE, value);

			OS_WrReg(VCP_BASE, 0x80F051E0);
			OS_WrReg(VCP_BASE + 0xF0, 0x80F051E0);

			OS_RdReg(FMS_BASE, &value);
			value &= 0x88FFFFFF;		//[30:28] 0x0, [26:24] 0x0
			OS_WrReg(FMS_BASE, value);

			OS_RdReg(FMC_BASE, &value);
			value &= 0x88FFFFFF;		//[30:28] 0x0, [26:24] 0x0
			OS_WrReg(FMC_BASE, value);
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
static LGBUS_HW_FUNC_T m17_lgbus_hw_func =
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

LGBUS_HW_FUNC_T* LGBUS_M17_Init(void)
{
	return &m17_lgbus_hw_func;
}
