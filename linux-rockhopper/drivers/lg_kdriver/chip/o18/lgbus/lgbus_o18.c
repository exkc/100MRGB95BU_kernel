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
#define	DDR_CLK				1320					// 1320 MHz
#define	REG_WR_RETRY_CNT	100
#define	APB_FAIL_ADDR		0xC9861404

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
	volatile void*		apb_fail_reg;
    volatile void*		bus_reg[QOS_IDX_MAX];		// ioremapped bus register
}
LGBUS_CHIP_CTX_T;

/*----------------------------------------------------------------------------------------
  External Function Prototype Declarations
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
  External Variables
----------------------------------------------------------------------------------------*/
extern lgbus_o18_mpro_func_t	lgbus_o18_mpro_func;

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
//              ----------------------ORG---------------------------------------        -----------------------DUMMY--------------------------------------
// 		   		  LBUS.WR    LBUS.RD    GBUS.WR    GBUS.RD                                LBUS.WR    LBUS.RD    GBUS.WR    GBUS.RD
//              ----------------------------------------------------------------        ------------------------------------------------------------------
{"CPU_M", {{{0xC9860810,0xC9860814},{0xC9860A10,0xC9860A14},{0xC9860C10,0xC9860C14}},{{0x00000000,0x00000000},{0x00000000,0x00000000},{0x00000000,0x00000000}}}},
{"GFX", {{{0xC9861110,0xC9861114},{0xC9861120,0xC9861124},{0xC9861190,0xC9861194}},{{0xC9861130,0xC9861134},{0xC9861138,0xC986113C},{0xC98611A0,0xC98611A4}}}},
{"AUD", {{{0xC9861310,0xC9861314},{0xC9861320,0xC9861324},{0xC9861390,0xC9861394}},{{0xC9861330,0xC9861334},{0xC9861338,0xC986133C},{0xC98613A0,0xC98613A4}}}},
{"TCON", {{{0xC9861510,0xC9861514},{0xC9861520,0xC9861524},{0xC9861590,0xC9861594}},{{0xC9861530,0xC9861534},{0xC9861538,0xC986153C},{0xC98615A0,0xC98615A4}}}},
{"TIV", {{{0xC9861710,0xC9861714},{0xC9861720,0xC9861724},{0xC9861790,0xC9861794}},{{0xC9861730,0xC9861734},{0xC9861738,0xC986173C},{0xC98617A0,0xC98617A4}}}},
{"VDEC0_M0", {{{0xC9861910,0xC9861914},{0xC9861920,0xC9861924},{0xC9861990,0xC9861994}},{{0xC9861930,0xC9861934},{0xC9861938,0xC986193C},{0xC98619A0,0xC98619A4}}}},
{"VDEC0_M1", {{{0xC9861B10,0xC9861B14},{0xC9861B20,0xC9861B24},{0xC9861B90,0xC9861B94}},{{0xC9861B30,0xC9861B34},{0xC9861B38,0xC9861B3C},{0xC9861BA0,0xC9861BA4}}}},
{"VDEC1_M0", {{{0xC9861D10,0xC9861D14},{0xC9861D20,0xC9861D24},{0xC9861D90,0xC9861D94}},{{0xC9861D30,0xC9861D34},{0xC9861D38,0xC9861D3C},{0xC9861DA0,0xC9861DA4}}}},
{"VDEC1_M1", {{{0xC9861F10,0xC9861F14},{0xC9861F20,0xC9861F24},{0xC9861F90,0xC9861F94}},{{0xC9861F30,0xC9861F34},{0xC9861F38,0xC9861F3C},{0xC9861FA0,0xC9861FA4}}}},
{"FMS", {{{0xC9862110,0xC9862114},{0xC9862120,0xC9862124},{0xC9862190,0xC9862194}},{{0xC9862130,0xC9862134},{0xC9862138,0xC986213C},{0xC98621A0,0xC98621A4}}}},
{"ME0", {{{0xC9862310,0xC9862314},{0xC9862320,0xC9862324},{0xC9862390,0xC9862394}},{{0xC9862330,0xC9862334},{0xC9862338,0xC986233C},{0xC98623A0,0xC98623A4}}}},
{"SSD", {{{0xC9862510,0xC9862514},{0xC9862520,0xC9862524},{0xC9862590,0xC9862594}},{{0xC9862530,0xC9862534},{0xC9862538,0xC986253C},{0xC98625A0,0xC98625A4}}}},
{"ME1", {{{0xC9862710,0xC9862714},{0xC9862720,0xC9862724},{0xC9862790,0xC9862794}},{{0xC9862730,0xC9862734},{0xC9862738,0xC986273C},{0xC98627A0,0xC98627A4}}}},
{"MCU", {{{0xC9862910,0xC9862914},{0xC9862920,0xC9862924},{0xC9862990,0xC9862994}},{{0xC9862930,0xC9862934},{0xC9862938,0xC986293C},{0xC98629A0,0xC98629A4}}}},
{"GPU", {{{0xC9862B10,0xC9862B14},{0xC9862B20,0xC9862B24},{0xC9862B90,0xC9862B94}},{{0xC9862B30,0xC9862B34},{0xC9862B38,0xC9862B3C},{0xC9862BA0,0xC9862BA4}}}},
{"FMC0", {{{0xC9862D10,0xC9862D14},{0xC9862D20,0xC9862D24},{0xC9862D90,0xC9862D94}},{{0xC9862D30,0xC9862D34},{0xC9862D38,0xC9862D3C},{0xC9862DA0,0xC9862DA4}}}},
{"FMC1", {{{0xC9862F10,0xC9862F14},{0xC9862F20,0xC9862F24},{0xC9862F90,0xC9862F94}},{{0xC9862F30,0xC9862F34},{0xC9862F38,0xC9862F3C},{0xC9862FA0,0xC9862FA4}}}},
{"FMC2", {{{0x00000000,0xC9863114},{0x00000000,0xC9863124},{0x00000000,0xC9863194}},{{0x00000000,0xC9863134},{0x00000000,0xC986313C},{0x00000000,0xC98631A4}}}},
{"FMC3", {{{0x00000000,0xC9863314},{0x00000000,0xC9863324},{0x00000000,0xC9863394}},{{0x00000000,0xC9863334},{0x00000000,0xC986333C},{0x00000000,0xC98633A4}}}},
{"CCO", {{{0x00000000,0xC9863514},{0x00000000,0xC9863524},{0x00000000,0xC9863594}},{{0x00000000,0xC9863534},{0x00000000,0xC986353C},{0x00000000,0xC98635A4}}}},
{"GSC0", {{{0x00000000,0xC9863714},{0x00000000,0xC9863724},{0x00000000,0xC9863794}},{{0x00000000,0xC9863734},{0x00000000,0xC986373C},{0x00000000,0xC98637A4}}}},
{"GSC1", {{{0x00000000,0xC9863914},{0x00000000,0xC9863924},{0x00000000,0xC9863994}},{{0x00000000,0xC9863934},{0x00000000,0xC986393C},{0x00000000,0xC98639A4}}}},
{"VDM0", {{{0x00000000,0xC97F1114},{0x00000000,0xC97F1124},{0x00000000,0xC97F1194}},{{0x00000000,0xC97F1134},{0x00000000,0xC97F113C},{0x00000000,0xC97F11A4}}}},
{"SRE_VDM1", {{{0xC97F1310,0xC97F1314},{0xC97F1320,0xC97F1324},{0xC97F1390,0xC97F1394}},{{0xC97F1330,0xC97F1334},{0xC97F1338,0xC97F133C},{0xC97F13A0,0xC97F13A4}}}},
{"SMX0", {{{0xC97F1510,0xC97F1514},{0xC97F1520,0xC97F1524},{0xC97F1590,0xC97F1594}},{{0xC97F1530,0xC97F1534},{0xC97F1538,0xC97F153C},{0xC97F15A0,0xC97F15A4}}}},
{"SMX1", {{{0xC97F1710,0xC97F1714},{0xC97F1720,0xC97F1724},{0xC97F1790,0xC97F1794}},{{0xC97F1730,0xC97F1734},{0xC97F1738,0xC97F173C},{0xC97F17A0,0xC97F17A4}}}},
{"SMX2", {{{0xC97F1910,0xC97F1914},{0xC97F1920,0xC97F1924},{0xC97F1990,0xC97F1994}},{{0xC97F1930,0xC97F1934},{0xC97F1938,0xC97F193C},{0xC97F19A0,0xC97F19A4}}}},
{"SMX3", {{{0xC97F1B10,0xC97F1B14},{0xC97F1B20,0xC97F1B24},{0xC97F1B90,0xC97F1B94}},{{0xC97F1B30,0xC97F1B34},{0xC97F1B38,0xC97F1B3C},{0xC97F1BA0,0xC97F1BA4}}}},
{"ND0", {{{0xC97F2110,0xC97F2114},{0xC97F2120,0xC97F2124},{0xC97F2190,0xC97F2194}},{{0xC97F2130,0xC97F2134},{0xC97F2138,0xC97F213C},{0xC97F21A0,0xC97F21A4}}}},
{"ND1", {{{0xC97F2310,0xC97F2314},{0xC97F2320,0xC97F2324},{0xC97F2390,0xC97F2394}},{{0xC97F2330,0xC97F2334},{0xC97F2338,0xC97F233C},{0xC97F23A0,0xC97F23A4}}}},
{"CVD", {{{0xC97F2510,0xC97F2514},{0xC97F2520,0xC97F2524},{0xC97F2590,0xC97F2594}},{{0xC97F2530,0xC97F2534},{0xC97F2538,0xC97F253C},{0xC97F25A0,0xC97F25A4}}}},
{"DBB", {{{0xC97F2710,0xC97F2714},{0xC97F2720,0xC97F2724},{0xC97F2790,0xC97F2794}},{{0xC97F2730,0xC97F2734},{0xC97F2738,0xC97F273C},{0xC97F27A0,0xC97F27A4}}}},
{"cpu_core", {{{0xC7FF1310,0xC7FF1314},{0xC7FF1320,0xC7FF1324},{0xC7FF1390,0xC7FF1394}},{{0xC7FF1330,0xC7FF1334},{0xC7FF1338,0xC7FF133C},{0xC7FF13A0,0xC7FF13A4}}}},
{"peri_axi", {{{0xC7FF1510,0xC7FF1514},{0xC7FF1520,0xC7FF1524},{0xC7FF1590,0xC7FF1594}},{{0xC7FF1530,0xC7FF1534},{0xC7FF1538,0xC7FF153C},{0xC7FF15A0,0xC7FF15A4}}}},
{"peri_ahb", {{{0xC7FF1710,0xC7FF1714},{0xC7FF1720,0xC7FF1724},{0xC7FF1790,0xC7FF1794}},{{0xC7FF1730,0xC7FF1734},{0xC7FF1738,0xC7FF173C},{0xC7FF17A0,0xC7FF17A4}}}},

{"PORT0", {{{0xC9864010,0xC9864014},{0xC9864410,0xC9864414},{0xC9864810,0xC9864814}},{{0xC9864020,0xC9864024},{0xC9864420,0xC9864424},{0xC9864820,0xC9864824}}}},
{"PORT1", {{{0xC9864110,0xC9864114},{0xC9864510,0xC9864514},{0xC9864910,0xC9864914}},{{0xC9864120,0xC9864124},{0xC9864520,0xC9864524},{0xC9864920,0xC9864924}}}},
{"PORT2", {{{0xC9864210,0xC9864214},{0xC9864610,0xC9864614},{0xC9864A10,0xC9864A14}},{{0xC9864220,0xC9864224},{0xC9864620,0xC9864624},{0xC9864A20,0xC9864A24}}}},
{"PORT3", {{{0xC9864310,0xC9864314},{0xC9864710,0xC9864714},{0xC9864B10,0xC9864B14}},{{0xC9864320,0xC9864324},{0xC9864720,0xC9864724},{0xC9864B20,0xC9864B24}}}},
};

static LGBUS_CHIP_CTX_T lgbus_chip_ctx;
static LGBUS_HW_CFG_T	lgbus_chip_cfg =
{
	.rf_timer_init	= 0x20,
	.irq_num		= 103,

	.ddr_num		= 3,
	.ip_num			= 35,
	.port_num		= 4,

	.bus_reg_base	= {0xC9860000, 0xC97F0000, 0xC7FF1000 },	// LBUS, GBUS, CPU
	.freq			= {396, 396, 528},							// LBUS, GBUS, CPU
};

/*========================================================================================
    Implementation Group
========================================================================================*/
static void lgbus_reg_wr(volatile void* addr, UINT32 value, UINT32 paddr)
{
   int i;
   UINT32 apb_fail_value;

   if((paddr >> 16) != 0xC97F)
   {
       LGBUS_WrFL(addr, value);
   }
   else
   {
       for(i = 0; i<REG_WR_RETRY_CNT; i++)
       {
           LGBUS_WrFL(addr, value);
           if(value == LGBUS_RdFL(addr)) break;		// good !
       }

       if(i == REG_WR_RETRY_CNT)
       {
           apb_fail_value = LGBUS_RdFL(lgbus_chip_ctx.apb_fail_reg);
           apb_fail_value &= 0x0000FFFF;           	//init [31:16]
           apb_fail_value |= (paddr << 16);			//address [31:16]
           LGBUS_WrFL(lgbus_chip_ctx.apb_fail_reg, apb_fail_value);

           LGBUS_ERROR("O18 reg_wr error(reg: 0x%08x, curr_val: 0x%08x)\n\n", paddr, LGBUS_RdFL(addr));
       }
   }
}

static int lgbus_config(LGBUS_HW_CFG_T* cfg)
{
	// collect system info & calcuate some variables
	lgbus_chip_cfg.max_bw[0] = DDR_CLK * 2 * 4;
	lgbus_chip_cfg.max_bw[1] = DDR_CLK * 2 * 4;
	lgbus_chip_cfg.max_bw[2] = DDR_CLK * 2 * 4;

	lgbus_chip_cfg.pmt_desc = pmt_chip_desc;

	memcpy(cfg, &lgbus_chip_cfg, sizeof(LGBUS_HW_CFG_T));

	return RET_OK;
}

static int lgbus_init(void)
{
	memset(&lgbus_chip_ctx, 0x0, sizeof(LGBUS_CHIP_CTX_T));

	lgbus_o18_mpro_func.init();

	return RET_OK;
}

static int lgbus_cleanup(void)
{
	lgbus_o18_mpro_func.cleanup();

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

	if(lgbus_chip_ctx.apb_fail_reg==0x0)
	{
   		lgbus_chip_ctx.apb_fail_reg = ioremap(APB_FAIL_ADDR, sizeof(UINT32));
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

	if(lgbus_chip_ctx.apb_fail_reg)
	{
		iounmap((volatile void *)lgbus_chip_ctx.apb_fail_reg);
		lgbus_chip_ctx.apb_fail_reg = 0x0;
	}

	return RET_OK;
}
static int lgbus_resume(void)
{
	int ret = lgbus_o18_mpro_func.resume();
	LGBUS_CHECK_CODE(ret != RET_OK, return RET_ERROR, "lgbus_mpro resume FAIL\n");;

	return RET_OK;
}

static int lgbus_suspend(void)
{
	lgbus_o18_mpro_func.suspend();

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
				lgbus_reg_wr(lgbus_chip_ctx.bus_reg[i] + lgbus_chip_cfg.rf_timer_init, data->gen[i],
						lgbus_chip_cfg.bus_reg_base[i] + lgbus_chip_cfg.rf_timer_init );
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
static LGBUS_HW_FUNC_T o18_lgbus_hw_func =
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

LGBUS_HW_FUNC_T* LGBUS_O18_Init(void)
{
	return &o18_lgbus_hw_func;
}
