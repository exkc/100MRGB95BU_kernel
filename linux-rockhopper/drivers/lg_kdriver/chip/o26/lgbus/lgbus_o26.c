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
#define	DDR_CLK				1850					// 1850 MHz
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
extern lgbus_o26_mpro_func_t	lgbus_o26_mpro_func;

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
	/* not implemented */
};

static LGBUS_CHIP_CTX_T lgbus_chip_ctx;
static LGBUS_HW_CFG_T	lgbus_chip_cfg =
{
	.rf_timer_init	= 0x20,
//	.irq_num		= 103,
	.irq_num		= 0,	/* not implemented */

//	.ddr_num		= 3,
//	.ip_num			= 35,
//	.port_num		= 4,
	.ddr_num		= 0,	/* not implemented */
	.ip_num			= 0,	/* not implemented */
	.port_num		= 0,	/* not implemented */

	.bus_reg_base	= {0xC9860000, 0xC97F0000, 0xC7FF1000 },	// LBUS, GBUS, CPU
	.freq			= {396, 396, 528},							// LBUS, GBUS, CPU
};

/*========================================================================================
    Implementation Group
========================================================================================*/
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

	lgbus_o26_mpro_func.init();

	return RET_OK;
}

static int lgbus_cleanup(void)
{
	lgbus_o26_mpro_func.cleanup();

	return RET_OK;
}

static int lgbus_open(void)
{
	return RET_OK;
}

static int lgbus_close(void)
{
	return RET_OK;
}
static int lgbus_resume(void)
{
	int ret = lgbus_o26_mpro_func.resume();
	LGBUS_CHECK_CODE(ret != RET_OK, return RET_ERROR, "lgbus_mpro resume FAIL\n");
	return RET_OK;
}

static int lgbus_suspend(void)
{
	lgbus_o26_mpro_func.suspend();

	return RET_OK;
}

/* general HW command execution */
static int lgbus_hwcmd(LGBUS_HW_CMD_ID_T cmdId, LGBUS_HW_DATA_T* data)
{
	switch(cmdId)
	{
		case LGBUS_HW_CMD_TIMER_INIT:
		{
			//LGBUS_NOTI("not implemented\n");
		}
		break;

		case LGBUS_HW_CMD_PQE_PERF_INIT:
		{
			/* do nothing */
		}
		break;

		case LGBUS_HW_CMD_INTR_ENABLE:
		{
			//LGBUS_NOTI("not implemented\n");
		}
		break;

		case LGBUS_HW_CMD_INTR_DISABLE:
		{
			//LGBUS_NOTI("not implemented\n");
		}
		break;

		case LGBUS_HW_CMD_INTR_HANDLER:
		{
			//LGBUS_NOTI("not implemented\n");
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
    Implementation Group (LGBUS O26 DESC)
========================================================================================*/
static LGBUS_HW_FUNC_T o26_lgbus_hw_func =
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

LGBUS_HW_FUNC_T* LGBUS_O26_Init(void)
{
	return &o26_lgbus_hw_func;
}
