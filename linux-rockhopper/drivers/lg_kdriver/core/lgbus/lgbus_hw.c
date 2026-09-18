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
 *  main configuration file for lgbus device
 *
 *  author		raxis.lim (raxis.lim@lge.com)
 *  version		1.0
 *  date		2018.09.05
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
#include <linux/kernel.h>   /**< lgbus_debug() */
#include <linux/slab.h>     /**< kmalloc() */
#include <linux/fs.h>       /**< everything\ldots{} */
#include <linux/types.h>    /**< size_t */
#include <linux/fcntl.h>    /**< O_ACCMODE */
#include <asm/uaccess.h>
#include <linux/ioport.h>
#include <asm/io.h>

#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/sched.h>

#include <linux/delay.h>
#include <linux/vmalloc.h>

#include <linux/seq_file.h>

#include "os_util.h"
#include "lgbus_drv.h"
#include "lgbus_hw.h"

/*----------------------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------------------*/
#define	seq_print_separator(m)	seq_printf(m,"----------------------------------------------------------\n")

/*----------------------------------------------------------------------------------------
	Type Definitions
----------------------------------------------------------------------------------------*/
typedef struct
{
    LGBUS_HW_FUNC_T*	func;
	volatile UINT32		bus_reg[QOS_IDX_MAX];

	UINT32				opt;				// option

#define LGBUS_PMT_STATUS_INIT_DONE       0x0001
#define LGBUS_PMT_STATUS_IRQ_ENABLED     0x0002
#define LGBUS_PMT_STATUS_MONITORING      0x0004
	UINT32				pmt_status;			// status
	UINT32				pmt_status_sav;		// saved status for instant boot

	UINT32				pmt_cnt;			// monitoring count

	struct semaphore	pmt_sem;			// semaphore for synchronization
}
LGBUS_CXT_T;

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
static void LGBUS_HW_StartMonitor(void);
static void LGBUS_HW_StopMonitor(void);

/*----------------------------------------------------------------------------------------
	Static Variables
----------------------------------------------------------------------------------------*/
static LGBUS_HW_CFG_T	hw_cfg;
static LGBUS_CXT_T 		lgbus_ctx;

static const char* ddr_label[DDR_NUM_MAX] = { "M0", "M1", "M2" };

/*========================================================================================
	Implementation Group
========================================================================================*/
int LGBUS_HW_Init(void)
{
	LGBUS_HW_FUNC_T *func = NULL;

	switch(lx_chip())
	{
#ifdef INCLUDE_M17_CHIP_KDRV
		case LX_CHIP_M17: func = LGBUS_M17_Init(); break;
#endif
#ifdef INCLUDE_L18_CHIP_KDRV
		case LX_CHIP_L18F: func = LGBUS_L18_Init(); break;
#endif
#ifdef INCLUDE_O18_CHIP_KDRV
		case LX_CHIP_O18: func = LGBUS_O18_Init(); break;
#endif
#ifdef INCLUDE_M19_CHIP_KDRV
		case LX_CHIP_M19: func = LGBUS_M19_Init(); break;
#endif
#ifdef INCLUDE_O20_CHIP_KDRV
		case LX_CHIP_O20: func = LGBUS_O20_Init(); break;
#endif
#ifdef INCLUDE_E60_CHIP_KDRV
		case LX_CHIP_E60: func = LGBUS_E60_Init(); break;
#endif
#ifdef INCLUDE_O22_CHIP_KDRV
		case LX_CHIP_O22: func = LGBUS_O22_Init(); break;
#endif
#ifdef INCLUDE_M23_CHIP_KDRV
		case LX_CHIP_M23: func = LGBUS_M23_Init(); break;
#endif
#ifdef INCLUDE_O24_CHIP_KDRV
		case LX_CHIP_O24: func = LGBUS_O24_Init(); break;
#endif
#ifdef INCLUDE_O26_CHIP_KDRV
		case LX_CHIP_O26: func = LGBUS_O26_Init(); break;
#endif

		default: LGBUS_ERROR("unknown chip 0x%x\n", lx_chip_rev() );
	}

	LGBUS_CHECK_CODE(!func, return RET_ERROR, "hw_func NULL\n");
	LGBUS_CHECK_CODE(!func->do_config, return RET_ERROR, "hw_func.do_config NULL\n");
	LGBUS_CHECK_CODE(!func->do_init, return RET_ERROR, "hw_func.do_init NULL\n");

	/* configure HW configuration & do actual initialization */
	LGBUS_CHECK_CODE(RET_OK!=func->do_config(&hw_cfg), return RET_ERROR, "hw_func.do_config fail\n");
	LGBUS_CHECK_CODE(RET_OK!=func->do_init(), return RET_ERROR, "hw_func.do_init fail\n");

	/* initialize lgbus context */
	memset(&lgbus_ctx, 0x0, sizeof(LGBUS_CXT_T));
	lgbus_ctx.func = func;
	lgbus_ctx.opt  = LGBUS_HW_OPT_PMT_BW_ORG;
	lgbus_ctx.opt  |= LGBUS_HW_OPT_PMT_BW_DUMMY;
	lgbus_ctx.opt  |= LGBUS_HW_OPT_PMT_SYNC;

	return 0;
}

int LGBUS_HW_Resume(void)
{
	LGBUS_CHECK_CODE(!lgbus_ctx.func, return RET_ERROR, "hw_func NULL\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_resume, return RET_ERROR, "hw_func.do_resume NULL\n");

	/* call HW resume first */
	LGBUS_CHECK_CODE(RET_OK!=lgbus_ctx.func->do_resume(), return RET_ERROR, "hw_func.do_resume fail\n");

	/* restore the previous state based on the saved pmt_status */
    if (lgbus_ctx.pmt_status_sav & LGBUS_PMT_STATUS_INIT_DONE)
	{
		LGBUS_HW_Open();
	}

#if 0
	if(lgbus_ctx.pmt_status_sav & LGBUS_PMT_STATUS_MONITORING)
    {
		LGBUS_HW_StartMonitor();
    }
#endif

	return RET_OK;
}

int LGBUS_HW_Suspend(void)
{
	LGBUS_CHECK_CODE(!lgbus_ctx.func, return RET_ERROR, "hw_func NULL\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_suspend, return RET_ERROR, "hw_func.do_suspend NULL\n");

	/* save the last pmt_status to restore status during next resume */
	lgbus_ctx.pmt_status_sav = lgbus_ctx.pmt_status;

	/* close device before entering suspend mode */
	LGBUS_HW_Close();

	/* call HW resume last */
	LGBUS_CHECK_CODE(RET_OK!=lgbus_ctx.func->do_suspend(), return RET_ERROR, "hw_func.do_suspend fail\n");

	return RET_OK;
}


void LGBUS_HW_Cleanup(void)
{
	int	ret = RET_ERROR;

	if(lgbus_ctx.func && lgbus_ctx.func->do_close)
	{
		ret = lgbus_ctx.func->do_close();
		LGBUS_CHECK_CODE(RET_OK!=ret, /* nop */, "lgbus HW close fail\n");
	}

	if(lgbus_ctx.func && lgbus_ctx.func->do_cleanup)
	{
		lgbus_ctx.func->do_cleanup();
	}
}

static void LGBUS_HW_StartMonitor(void)
{
	LGBUS_NOTI("lgbus monitor start..\n");

	if (!(lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_MONITORING))
	{
		lgbus_ctx.pmt_status |= LGBUS_PMT_STATUS_MONITORING;
	}
}

static void LGBUS_HW_StopMonitor(void)
{
	LGBUS_DEBUG("lgbus monitor stop..\n");

	if (lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_MONITORING )
	{
		lgbus_ctx.pmt_status &= ~LGBUS_PMT_STATUS_MONITORING;
	}
}

LGBUS_HW_OPT_T	LGBUS_HW_GetOption(void)
{
	return lgbus_ctx.opt;
}

void LGBUS_HW_SetOption(LGBUS_HW_OPT_T opts)
{
	lgbus_ctx.opt = opts;
}

static irqreturn_t LGBUS_HW_IRQHandler(int irq, void *dev)
{
	if (lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_MONITORING)
	{
        if(down_trylock(&lgbus_ctx.pmt_sem)!=0)
        {
            LGBUS_DEBUG("+ lgbus isr : waking up user\n");

			lgbus_ctx.pmt_cnt++;
            up(&lgbus_ctx.pmt_sem);
        }
    }

	// notify BUS interrupt to chip driver. chip driver should do intr_clear
	if(lgbus_ctx.func && lgbus_ctx.func->do_hwcmd)
	{
    	LGBUS_CHECK_CODE(RET_OK!=lgbus_ctx.func->do_hwcmd(LGBUS_HW_CMD_INTR_HANDLER, NULL),
 				goto func_exit, "hw_cmd(INTR_HANDLER) fail\n");
	}

func_exit:
    return IRQ_HANDLED;
}

int LGBUS_HW_Open(void)
{
	int	i;
	LGBUS_HW_DATA_T tmr_data;
	int ret = RET_ERROR;

	LGBUS_CHECK_CODE(!lgbus_ctx.func, return RET_ERROR, "hw_func null\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_open, return RET_ERROR, "hw_func.do_open null\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_hwcmd, return RET_ERROR, "hw_func.do_hwcmd null\n");

	LGBUS_NOTI("+ lgbus open.. max_bw = %4d %4d %4d MB/s\n", hw_cfg.max_bw[0], hw_cfg.max_bw[1], hw_cfg.max_bw[2]);

	if (!(lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_INIT_DONE))
	{
		ret = lgbus_ctx.func->do_open();
		LGBUS_CHECK_CODE(RET_OK!=ret, goto func_exit, "hw_func.do_open fail\n");

		//lgbus_ctx.bus_reg[QOS_IDX_LBUS] = (unsigned long)ioremap((unsigned long)hw_cfg.bus_reg_base[QOS_IDX_LBUS], 0x200);
		//lgbus_ctx.bus_reg[QOS_IDX_GBUS] = (unsigned long)ioremap((unsigned long)hw_cfg.bus_reg_base[QOS_IDX_GBUS], 0x200);
		//lgbus_ctx.bus_reg[QOS_IDX_CCI]  = (unsigned long)ioremap((unsigned long)hw_cfg.bus_reg_base[QOS_IDX_CCI],  0x200);

		/* qos_settmr for ASIC */
		for(i=0; i<QOS_IDX_MAX; i++)
		{
			tmr_data.gen[i] = hw_cfg.freq[i] * __MHZ;
		}

		ret = lgbus_ctx.func->do_hwcmd(LGBUS_HW_CMD_TIMER_INIT, &tmr_data);
		LGBUS_CHECK_CODE(RET_OK!=ret, goto func_exit, "hwcmd(TIMER_INIT) fail\n");

		/* start interrupt */
		ret = lgbus_ctx.func->do_hwcmd(LGBUS_HW_CMD_INTR_ENABLE, NULL);

		/* do PQE perfomance init */
		ret = lgbus_ctx.func->do_hwcmd(LGBUS_HW_CMD_PQE_PERF_INIT, NULL);
		LGBUS_CHECK_CODE(RET_OK!=ret, goto func_exit, "hwcmd(PQE_PERF_INIT) fail\n");

		lgbus_ctx.pmt_status |= LGBUS_PMT_STATUS_INIT_DONE;
	}

	/* initialize synchronization sema */
	sema_init(&lgbus_ctx.pmt_sem, 1);

	if (!(lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_IRQ_ENABLED))
	{
		if (hw_cfg.irq_num)
		{
			LGBUS_CHECK_CODE(request_irq(hw_cfg.irq_num, LGBUS_HW_IRQHandler,
							IRQF_SHARED | IRQF_TRIGGER_HIGH, "lgbus", (void*)&lgbus_ctx),
							goto func_exit, "lgbus request_irq FAIL\n");

  			lgbus_ctx.pmt_status |= LGBUS_PMT_STATUS_IRQ_ENABLED;
		}
	}

	down(&lgbus_ctx.pmt_sem);

	/* start BW monitor automatically */
	LGBUS_HW_StartMonitor();

	ret = RET_OK;
func_exit:
	return ret;
}

int LGBUS_HW_Close(void)
{
	int	ret = RET_ERROR;

	LGBUS_CHECK_CODE(!lgbus_ctx.func, return RET_ERROR, "hw_func null\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_close, return RET_ERROR, "hw_func.do_open null\n");
	LGBUS_CHECK_CODE(!lgbus_ctx.func->do_hwcmd, return RET_ERROR, "hw_func.do_hwcmd null\n");

	LGBUS_HW_StopMonitor();

	/* stop interrupt handler */
    if (lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_IRQ_ENABLED)
    {
		ret = lgbus_ctx.func->do_hwcmd(LGBUS_HW_CMD_INTR_DISABLE, NULL);
		LGBUS_CHECK_CODE(RET_OK!=ret, /* nop */, "hw_cmd.intr_disable fail\n");

        free_irq(hw_cfg.irq_num, (void*)&lgbus_ctx);
        lgbus_ctx.pmt_status &= ~LGBUS_PMT_STATUS_IRQ_ENABLED;
    }

	/* release resources */
    if (lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_INIT_DONE)
	{
//		iounmap((volatile void *)lgbus_ctx.bus_reg[QOS_IDX_LBUS]);
//		iounmap((volatile void *)lgbus_ctx.bus_reg[QOS_IDX_GBUS]);
//		iounmap((volatile void *)lgbus_ctx.bus_reg[QOS_IDX_CCI]);

		lgbus_ctx.pmt_status &= ~LGBUS_PMT_STATUS_INIT_DONE;
	}

	ret = lgbus_ctx.func->do_close();
	LGBUS_CHECK_CODE(RET_OK!=ret, /* nop */, "lgbus HW close fail\n");

	return ret;
}

/*========================================================================================
	Implementation Group (PROC debugger)
========================================================================================*/
void LGBUS_HW_PrintStatus(struct seq_file* m)
{
	int	i;
	seq_printf(m, "pmt.status: %s\n", (lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_MONITORING)? "on":"off");
	seq_printf(m, "pmt.count: %d\n", lgbus_ctx.pmt_cnt);
	seq_printf(m, "ddr_num: %d\n", hw_cfg.ddr_num);

	for (i=0; i<hw_cfg.ddr_num; i++)
	{
		seq_printf(m, "ddr%d.max_bw: %d MB/s\n", i, hw_cfg.max_bw[i]);
	}
	seq_printf(m, "\n");
}

void LGBUS_HW_PrintPMTInfo(struct seq_file* m)
{
	int	i, j;
	UINT32	val;
	UINT32	bw_total[DDR_NUM_MAX][RW_NUM_MAX];

	if(!(lgbus_ctx.pmt_status & LGBUS_PMT_STATUS_MONITORING))
	{
		seq_printf(m, "invalid status\n"); return;
	}

	if (lgbus_ctx.opt & LGBUS_HW_OPT_PMT_SYNC)
	{
		down(&lgbus_ctx.pmt_sem);
	}

	memset(bw_total, 0x0, sizeof(UINT32)*DDR_NUM_MAX*RW_NUM_MAX);

	// draw label
	seq_print_separator(m);
	seq_printf(m, "%8s ", "LABEL");
	for (i=0; i<hw_cfg.ddr_num*RW_NUM_MAX; i++)
	{
		seq_printf(m, "%3s.%s  ", ddr_label[i/RW_NUM_MAX], (i%RW_NUM_MAX)?"RD":"WR");
	}
	seq_printf(m, "\n");
	seq_print_separator(m);

	/* scan all PMT(IP) data */
	for (i=0; i< hw_cfg.ip_num + hw_cfg.port_num; i++)
	{
		const LGBUS_PMT_ITEM_DESC_T* desc = &hw_cfg.pmt_desc[i];

		if(i==hw_cfg.ip_num)
		{
			seq_print_separator(m);
		}

		seq_printf(m, "%8s ", desc->label);

		for (j=0; j<hw_cfg.ddr_num; j++)
		{
			UINT32 wr_bw = 0;
			UINT32 rd_bw = 0;

			val = 0;
			if (desc->bw.org[j][0] && lgbus_ctx.opt & LGBUS_HW_OPT_PMT_BW_ORG)	// check org_pkt.wr
			{
				OS_RdReg( desc->bw.org[j][0], &val); wr_bw += (val<<2);
			}

			val = 0;
			if (desc->bw.org[j][1] && lgbus_ctx.opt & LGBUS_HW_OPT_PMT_BW_ORG)	// check org_pkt.rd
			{
				OS_RdReg( desc->bw.org[j][1], &val); rd_bw += (val<<2);
			}

			val = 0;
			if (desc->bw.dmy[j][0] && lgbus_ctx.opt & LGBUS_HW_OPT_PMT_BW_DUMMY)// check dummy_pkt.wr
			{
				OS_RdReg( desc->bw.dmy[j][0], &val); wr_bw += val;
			}

			val = 0;
			if (desc->bw.dmy[j][1] && lgbus_ctx.opt & LGBUS_HW_OPT_PMT_BW_DUMMY)// check dummy_pkt.rd
			{
				OS_RdReg( desc->bw.dmy[j][1], &val); rd_bw += val;
			}

			/* bw_total  should be sume of BW by PORT not by each IP */
			if(!strncmp(desc->label,"PORT",4))
			{
				bw_total[j][0] += wr_bw; bw_total[j][1] += rd_bw;
			}

			seq_printf(m, "%4d.%d  ", wr_bw/__MHZ, (wr_bw%__MHZ)/__100KHZ);
			seq_printf(m, "%4d.%d  ", rd_bw/__MHZ, (rd_bw%__MHZ)/__100KHZ);
		}
		seq_printf(m, "\n");
	}

	seq_print_separator(m);

	seq_printf(m, "%8s ", "TOTAL");
	for (j=0; j<hw_cfg.ddr_num; j++)
	{
		val = bw_total[j][0];
		seq_printf(m, "%4d.%d  ", val/__MHZ, (val%__MHZ)/__100KHZ);

		val = bw_total[j][1];
		seq_printf(m, "%4d.%d  ", val/__MHZ, (val%__MHZ)/__100KHZ);
	}
	seq_printf(m,"\n");
	seq_print_separator(m);
}

/** @} */


