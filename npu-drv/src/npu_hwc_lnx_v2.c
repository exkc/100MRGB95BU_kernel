/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2022 by LG Electronics Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

/** @file
 *
 *  npu hw control (LNX)
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2023.04.19
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <linux/completion.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/delay.h>

#include "proc_util.h"
#include "debug_util.h"
#include "pqe_pm_drv.h"

#include "logm.h"

#include "npu_drv.h"
#include "npu_hwc_lnx.h"
#include "npu_hwc_lnx_v2.h"

#include "o26/O26-A0_REG_LNX0_HCR.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
//#define _DBG_PRINT
#define CPU_IRQ
//#define LNX2_SUPPORT

#ifdef LNX2_SUPPORT
#define NPU_MAX_INST 3
#else
#define NPU_MAX_INST 2
#endif

#define APB_LNX0_HCR_BASE           0xCC540000
#define APB_LNX0_CCRL_DSSCR_BASE    0xCC541000
#define APB_LNX0_HCR_HOST_BASE      0xCC54E000
#define APB_LNX1_HCR_BASE           0xCC5A0000
#define APB_LNX1_CCRL_DSSCR_BASE    0xCC5A1000
#define APB_LNX1_HCR_HOST_BASE      0xCC5AE000
#ifdef LNX2_SUPPORT
#define APB_LNX2_HCR_BASE           0xCC5E0000
#define APB_LNX2_CCRL_DSSCR_BASE    0xCC5E1000
#define APB_LNX2_HCR_HOST_BASE      0xCC5EE000
#endif

#define SCRG_CTRL_LNX0  (0xCC550000)
#define SCRG_CTRL_LNX1  (0xCC5B0000)
#define CRG_LNX02       (0x008)
#define CRG_LNX03       (0x00C)
#define SOFT_RST_LNX0_CORE_N            (1<<4)
#define SOFT_RST_LNX0_AXI_FLUSH_N       (1<<2)
#define SOFT_RST_LNX0_APB_ASYNC_N       (1<<5)
#define LNX_HCR_HOST_AXI_FLUSH_EN       (0x000)
#define LNX_HCR_HOST_AXI_FLUSH_DONE     (0x004)
#define RV_OFFSET   (0x1000)

#define NPU_REG_Rd(_reg, _r)	*((UINT32 *)(&(_reg.shdw_reg->_r)))
#define NPU_REG_Wr(_reg, _r) {	\
    ((_reg.hw_reg->_r) = (_reg.shdw_reg->_r)); \
    /*logm_info(npu_hwc_mod,"[REG_Wr] REG[0x%X] = 0x%X\n",*/  \
    /*(UINT32)(&(_reg.hw_reg->_r))-(UINT32)(_reg.hw_reg), *((UINT32 *)(&(_reg.hw_reg->_r))));*/ \
}
#define NPU_REG_Rd_Sync(_reg, _r) {	\
    ((_reg.shdw_reg->_r) = (_reg.hw_reg->_r)); \
    /*logm_info(npu_hwc_mod,"[REG_Rd] REG[0x%X] = 0x%X\n",*/  \
    /*(UINT32)(&(_reg.hw_reg->_r))-(UINT32)(_reg.hw_reg), *((UINT32 *)(&(_reg.hw_reg->_r))));*/ \
}
#define NPU_REG_Wr_Sync(_reg, _r, _v) ((NPU_REG_Rd(_reg, _r)) = ((UINT32)(_v)))

#define NPU_REG_Rd01(_reg, _r, _f01, _v01)	((_v01) = (_reg.shdw_reg->_r._f01))
#define NPU_REG_Wr01(_reg, _r, _f01, _v01)	((_reg.shdw_reg->_r._f01) = (_v01))

#ifdef CPU_IRQ
#define NPU_LNX0_IRQ	(32+142)
#define NPU_LNX1_IRQ	(32+143)
#ifdef LNX2_SUPPORT
#define NPU_LNX2_IRQ	(32+144)
#endif
#endif

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace (npu_hwc_mod, fmt, ##args)
#define debug(fmt,args...)  logm_debug (npu_hwc_mod, fmt, ##args)
#define info(fmt,args...)   logm_info (npu_hwc_mod, fmt, ##args)
#define noti(fmt,args...)   logm_noti (npu_hwc_mod, fmt, ##args)
#define warn(fmt,args...)   logm_warning (npu_hwc_mod, fmt, ##args)
#define error(fmt,args...)  logm_error (npu_hwc_mod, fmt, ##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef struct {
	LNX0_HCR_REG_T *hw_reg;
	LNX0_HCR_REG_T *shdw_reg;
} NPU_REG_LNX0_HCR_T;

typedef struct {
	LNX0_HCR_REG_T *hw_reg;
	LNX0_HCR_REG_T *shdw_reg;
} NPU_REG_LNX1_HCR_T;

struct npu_hw_work
{
    unsigned int core_idx;
    struct work_struct work;
    struct completion done;
    bool run_wait;
};

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static NPU_REG_LNX0_HCR_T npu_reg_hcr[NPU_MAX_INST];
static struct npu_hw_work _npu_hw_work;
#ifdef _DBG_PRINT
static volatile UINT32 *lnx_io_base[NPU_MAX_INST];
#endif

#ifdef CPU_IRQ
struct lnxirq_desc
{
    const char *name;
    int dspnum;
    int irqnum;
    bool done;
};

static struct lnxirq_desc lnxirqs[] = {
    {"lnx0", 0, NPU_LNX0_IRQ, false},
    {"lnx1", 1, NPU_LNX1_IRQ, false},
#ifdef LNX2_SUPPORT
    {"lnx2", 2, NPU_LNX2_IRQ, false},
#endif
};

static wait_queue_head_t _intr_wait;
#endif

static STATE_INDEX_T _state_idx[NPU_MAX_INST];
static struct mutex _lnx_device_lock;

#if 1 //byDM__temporary
static unsigned int _open_cnt = 0;
static bool _recovery[NPU_MAX_INST];
static unsigned int _run_cnt[NPU_MAX_INST];
#endif

#ifndef BRINGUP
static int lnx_pqe_pm_cb(int action)
{
	noti("(%d) start\n",action);

	if (action == PQE_PM_DEVICE_SUSPEND_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_SUSPEND) {
		/* ipc masking on after fw suspend */
		//ipc_hal_ready_to_use(0);//see vsc_suspend

		/* stop intr handler after fw suspend */
		//DE_INT_StopHandler(1);//see vsc_suspend

		//DE_NOTI("suspend : ipc masking on, handler off\n");
	}
	else if (action == PQE_PM_DEVICE_SUSPEND_COMPLETED) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME_PREPARE) {
		//TODO:
	}
	else if (action == PQE_PM_DEVICE_RESUME) {
		/* restart intr handler before fw resume */
		//DE_INT_StopHandler(0);//see vsc_resume

		/* ipc masking off before fw resume */
		//ipc_hal_ready_to_use(1);//see vsc_resume

		//DE_NOTI("resume : handler on, ipc masking off\n");
	}
	else if (action == PQE_PM_DEVICE_RESUME_COMPLETED) {
		//TODO:
	}

	noti("(%d) end\n",action);
	return 0;
}

static struct pqe_pm_config lnx_pqe_pm_cfg = {
	.name = "npu0",
	.opt = PQE_PM_OPT_NONE,
	.order = 30,
	.callback = lnx_pqe_pm_cb,
};

static int lnx_pqe_pm_id;
#endif
/*==============================================================================
    Implementation Group
==============================================================================*/
static void _npu_ctrl_reset(unsigned int idx)
{
/*
    int i = 0;

    debug("npu_reg_ctrl reset[%d]\n", sizeof(REG_DNE_CTRL_T));
    for(i=0; i < sizeof(REG_DNE_CTRL_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_ctrl[0].hw_reg+i) = 0;
    }

    debug("npu_reg_mon reset[%d]\n", sizeof(REG_DNE_MON_T));
    for(i=0; i < sizeof(REG_DNE_MON_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_mon[0].hw_reg+i) = 0;
    }

    debug("npu_reg_dne0 reset[%d]\n", sizeof(REG_DNE0_T));
    for(i=0; i < sizeof(REG_DNE0_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_dne0[0].hw_reg+i) = 0;
    }
    debug("npu_reg_dne1 reset[%d]\n", sizeof(REG_DNE1_T));
    for(i=0; i < sizeof(REG_DNE1_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_dne1[0].hw_reg+i) = 0;
    }

    debug("npu_reg_mif0 reset[%d]\n", sizeof(REG_DNE_MIF0_T));
    for(i=0; i < sizeof(REG_DNE_MIF0_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_mif0[0].hw_reg+i) = 0;
    }

    debug("npu_reg_mif1 reset[%d]\n", sizeof(REG_DNE_MIF1_T));
    for(i=0; i < sizeof (REG_DNE_MIF1_T); i+=4)
    {
        *(volatile UINT32 *)((void *)npu_reg_mif1[0].hw_reg+i) = 0;
    }
*/
    info("[%d] %s done\n", idx, __func__);
}

static void _process_clockgate(unsigned int core_idx, bool is_suspended)
{
    UINT32 crg_phy_base;
    volatile unsigned int* crg_io_base;

    return;

    if(core_idx == core_1)
    {
        crg_phy_base = SCRG_CTRL_LNX1;
    }
    else if(core_idx == core_0)
    {
        crg_phy_base = SCRG_CTRL_LNX0;
    }
    else
    {
        error("core_idx error.\n");
        return;
    }

    crg_io_base = (unsigned int*)ioremap(crg_phy_base, 16);
    if (!crg_io_base) {
        error ("crg_io_base ioremap() failed.\n");
        return;
    }

    if(is_suspended)
    {
        if(crg_io_base[CRG_LNX02/4] != 0x4)
            crg_io_base[CRG_LNX02/4] = 0x4;
    }
    else
    {
        if(crg_io_base[CRG_LNX02/4] != 0x0)
            crg_io_base[CRG_LNX02/4] = 0x0;
    }

    noti("[%d] clock gating[%d](0x%X) done\n", core_idx, is_suspended, crg_io_base[CRG_LNX02/4]);

    if(crg_io_base) {
        iounmap(crg_io_base);
    }
}

static int _npu_set_init_param(unsigned int idx, struct npu_prepare_param *param)
{
    info("[%d] %s\n", idx, __func__);

    //LNX0 hcr_axi_rd_outstanding
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_axi_rd_outstanding);
#ifdef _DBG_PRINT
    debug("%s lnx_hcr_axi_rd_outstanding[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_axi_rd_outstanding));
#endif
    NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_axi_rd_outstanding, LNX_HCR_AXI_RD_OUTSTANDING, 0x2);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_axi_rd_outstanding);
#ifdef _DBG_PRINT
    debug("%s lnx_hcr_axi_rd_outstanding[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_axi_rd_outstanding));
    debug("%s lnx_hcr_axi_rd_outstanding[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x28));
#endif

    //LNX0 hcr_axi_wr_outstanding
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_axi_wr_outstanding);
#ifdef _DBG_PRINT
    debug("%s lnx_hcr_axi_wr_outstanding[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_axi_wr_outstanding));
#endif
    NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_axi_wr_outstanding, LNX_HCR_AXI_WR_OUTSTANDING, 0x2);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_axi_wr_outstanding);
#ifdef _DBG_PRINT
    debug("%s lnx_hcr_axi_wr_outstanding[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_axi_wr_outstanding));
    debug("%s lnx_hcr_axi_wr_outstanding[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x2C));
#endif

    info("%s hcr_axi_rd/wr_outstanding done", __func__);

    return 0;
}

#ifdef _DBG_PRINT
static void _monitor_hidden_register(unsigned int idx)
{
	info("%s \n", __func__);

    // LNX0 layer_number in riscv 2 core
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr10);
    debug("%s lnx_hcr_gpr10[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr10));
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr11);
    debug("%s lnx_hcr_gpr11[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr11));

    //debug("%s riscv core0 PC val [0x%X] \n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x808));
    //debug("%s riscv core1 PC val [0x%X] \n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x80C));
}
#endif

static void _process_axi_flush(unsigned int idx)
{
    UINT32 hcr_phy_base;
    volatile unsigned int* hcr_io_base;

    if(idx == core_1)
    {
        hcr_phy_base = APB_LNX1_HCR_HOST_BASE;
    }
    else if(idx == core_0)
    {
        hcr_phy_base = APB_LNX0_HCR_HOST_BASE;
    }
    else
    {
        error("idx error.\n");
        return;
    }

    hcr_io_base = (unsigned int*)ioremap(hcr_phy_base, 0x800);
    if (!hcr_io_base) {
        error ("hcr_io_base ioremap() failed.\n");
        return;
    }

// LNX0/1_HCR_HOST_REG
    //iowrite32 (LNX2_HCR_HOST+LNX_HCR_HOST_AXI_FLUSH_EN, OxF);
    hcr_io_base[LNX_HCR_HOST_AXI_FLUSH_EN/4] = 0xd;

    noti("[%d] AXI Flush enable\n", idx);

    if(hcr_io_base) {
        iounmap(hcr_io_base);
    }
}

static void _process_core_reset(unsigned int idx)
{
    UINT32 hcr_phy_base, crg_phy_base;
    volatile unsigned int* hcr_io_base;
    volatile unsigned int* crg_io_base;

    if(idx == core_1)
    {
        hcr_phy_base = APB_LNX1_HCR_HOST_BASE;
        crg_phy_base = SCRG_CTRL_LNX1;
    }
    else if(idx == core_0)
    {
        hcr_phy_base = APB_LNX0_HCR_HOST_BASE;
        crg_phy_base = SCRG_CTRL_LNX0;
    }
    else
    {
        error("idx error.\n");
        return;
    }

    hcr_io_base = (unsigned int*)ioremap(hcr_phy_base, 0x800);
    if (!hcr_io_base) {
        error ("hcr_io_base ioremap() failed.\n");
        return;
    }
    crg_io_base = (unsigned int*)ioremap(crg_phy_base, 16);
    if (!crg_io_base) {
        error ("crg_io_base ioremap() failed.\n");
        return;
    }

// LNX0/1_HCR_HOST_REG

    if((hcr_io_base[LNX_HCR_HOST_AXI_FLUSH_DONE/4] & 0xD) != 0xD)
    {
        error("[%d] LNX_HCR_HOST_AXI_FLUSH_DONE failed.\n", idx);
        _state_idx[idx] = DISABLE;
        return;
    }

    // LNX CRG Reset Assert (core S axi flush) (axi flush for axi asvnc)
    //iowrite32 (SCRG_CTRL_LNX2+CRG_LNX23, ioread32 (SCRG_CTRL_LNX2+CRG_LNX23) | (SOFT_RST_LNX2_CORE_N | SOFT_RST_LNX2_AXI_FLUSH_N)); // ioread32 -> iowrite32
     crg_io_base[CRG_LNX03/4] = crg_io_base[CRG_LNX03/4] | (SOFT_RST_LNX0_CORE_N);

     //ioread32(SCRG_CTRL_LNX2+CRG_LNX23): // Code to Prevent APB settina Reversal
     (void)crg_io_base[CRG_LNX03/4];

     // AXI Flush Disable
     //iowrite32(LNX2_HCR_HOST+LNX_HCR_HOST_AXI_FLUSH_EN, 0x0) ;
     hcr_io_base[LNX_HCR_HOST_AXI_FLUSH_EN/4] = 0x00;
     (void)hcr_io_base[LNX_HCR_HOST_AXI_FLUSH_EN/4];

     //iowrite32 (SCRG_CTRL_LNX2+CRG_LNX23, ioread32 (SCRG_CTRL_LNX2+CRG_LNX23) | (SOFT_RST_LNX2_APB_N)) ; // ioread32 -> iowrite32
     crg_io_base[CRG_LNX03/4] = crg_io_base[CRG_LNX03/4] | SOFT_RST_LNX0_APB_ASYNC_N;

     // LNX CRG Reset Release
     //iowrite32 (SCRG_CTRL_LNX2+CRG_LNX23, ioread32 (SCRG CTRL LNX2+CRG LNX23) & ~(SOFT_RST_LNX2_CORE_N | SOFT_RST_LNX2_AXI_FLUSH_N | SOFT_RST_LNX2_APB_N)); // ioread32 -> iowrite32
     crg_io_base[CRG_LNX03/4] = crg_io_base[CRG_LNX03/4] & ~(SOFT_RST_LNX0_CORE_N | SOFT_RST_LNX0_APB_ASYNC_N);

     //ioread32(SCRG_CTRL_LNX2+CRG_LNX23): // Code to Prevent APB settina Reversal
     (void)crg_io_base[CRG_LNX03/4];

    _state_idx[idx] = RECOVERY;

    noti("[%d] core reset done\n", idx);

    if(hcr_io_base) {
        iounmap(hcr_io_base);
    }
    if(crg_io_base) {
        iounmap(crg_io_base);
    }
}

static void _print_debug_register(unsigned int idx)
{
    UINT32 phy_base;
    volatile UINT32 *io_base;
    int i = 0;

    if(idx == core_1)
        phy_base = APB_LNX1_HCR_BASE;
    else if(idx == core_0)
        phy_base = APB_LNX0_HCR_BASE;
    else
    {
        error("idx error.\n");
        return;
    }

    io_base = ioremap(phy_base, 0x2000);
    if (!io_base) {
        error ("io_base ioremap() failed.\n");
        return;
    }

    warn("----------------------------\n");

// LNX0/1_REG_HCR.hex
    for(i=0; i <= 20; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }
    for(i=32; i <= 60; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }

    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 64,
            *(volatile UINT32 *)((void *)io_base+64));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 72,
            *(volatile UINT32 *)((void *)io_base+72));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 76,
            *(volatile UINT32 *)((void *)io_base+76));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 80,
            *(volatile UINT32 *)((void *)io_base+80));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 84,
            *(volatile UINT32 *)((void *)io_base+84));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 88,
            *(volatile UINT32 *)((void *)io_base+88));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 92,
            *(volatile UINT32 *)((void *)io_base+92));

    for(i=96; i <= 132; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }
    for(i=144; i <= 148; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }
    for(i=256; i <= 380; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }

    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 2044,
            *(volatile UINT32 *)((void *)io_base+2044));

    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 0x1000,
                *(volatile UINT32 *)((void *)(io_base+(0x1000/4))));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 0x1008,
                *(volatile UINT32 *)((void *)(io_base+(0x1008/4))));
    warn("LNX_%d REG[0x%X] = 0x%X \n", idx, 0x100c,
                *(volatile UINT32 *)((void *)(io_base+(0x100c/4))));
// LNX0/1_REG_DSSCR.hex
    for(i=2048; i <= 2064; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }
    for(i=2080; i <= 2124; i+=4)
    {
        warn("LNX_%d REG[0x%X] = 0x%X \n", idx, i,
                *(volatile UINT32 *)((void *)io_base+i));
    }

    warn("----------------------------\n");

    if(io_base) {
        iounmap(io_base);
    }
}

static void _npu_ctrl_interrupt_enable(unsigned int core_idx, bool enable)
{
	BOOLEAN mask;

	mask = (enable)?0:1;

    if(mask)
    {
        info("[core%d] _npu_ctrl_run_enable\n", core_idx);
        //LNX Interrupt Enable
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_en_set);
        NPU_REG_Wr_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_en_set, 0x1);
        NPU_REG_Wr(npu_reg_hcr[core_idx], lnx_hcr_intr_en_set);
#ifdef _DBG_PRINT
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_en);
        debug("%s lnx_hcr_intr_en[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[core_idx], lnx_hcr_intr_en));
        debug("%s lnx_hcr_intr_en[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base+0x40));
#endif

        //LNX Interrupt Selelct [0x2:CPU, 0x1:MCU, 0x3:CPU&MCU]
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_sel);
        NPU_REG_Wr01(npu_reg_hcr[core_idx], lnx_hcr_intr_sel, hcr_intr_sel, 0x2);
        NPU_REG_Wr(npu_reg_hcr[core_idx], lnx_hcr_intr_sel);
#ifdef _DBG_PRINT
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_sel);
        debug("%s lnx_hcr_intr_sel[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[core_idx], lnx_hcr_intr_sel));
        debug("%s lnx_hcr_intr_sel[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base+0x4C));
#endif
    }
    else
    {
        info("[core%d] _npu_ctrl_interrupt_disable\n", core_idx);
        //LNX Interrupt Disable
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_dis_set);
        NPU_REG_Wr_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_dis_set, 0x1);
        NPU_REG_Wr(npu_reg_hcr[core_idx], lnx_hcr_intr_dis_set);
#ifdef _DBG_PRINT
        NPU_REG_Rd_Sync(npu_reg_hcr[core_idx], lnx_hcr_intr_en);
        debug("%s lnx_hcr_intr_en[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[core_idx], lnx_hcr_intr_en));
        debug("%s lnx_hcr_intr_en[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[core_idx]+0x40));
#endif
    }
}

#ifndef CPU_IRQ
static bool _npu_ctrl_get_interrupt_status(unsigned int idx)
{
    UINT32 val;

    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_intr_status);
    NPU_REG_Rd01(npu_reg_hcr[idx], lnx_hcr_intr_status,LNX_HCR_INTR_STATUS,val);
    if(val == 0x1)
    {
		info("[%s] interrupted!!!!\n", __func__);
		return true;
    }

    return false;
}
#endif

static void _npu_ctrl_clear_interrupt(unsigned int idx)
{
    info("_npu_ctrl_clear_interrupt\n");

    //LNX Interrupt Clear
    NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_intr_clr, hcr_intr_clr, 0x00000001);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_intr_clr);

#ifdef _DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_intr_clr);
    debug("%s done[0x%x]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_intr_clr));
#else
    debug("%s done\n", __func__);
#endif
}

static void _npu_ctrl_set_program(unsigned int idx, phys_addr_t phys_addr)
{
	//CORE DDR Base Address
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_ddr_base);
	//NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_core_ddr_base, LNX_HCR_CORE_DDR_BASE, phys_addr);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_ddr_base, phys_addr);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_ddr_base);
#ifdef _DBG_PRINT
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_ddr_base);
    debug("%s CORE DDR Base Address[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_core_ddr_base));
    debug("%s CORE DDR Base Address[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]));
#endif

	//program base address
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr1);
	//NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_gpr1, LNX_HCR_GPR1, phys_addr);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr1, phys_addr);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr1);
#ifdef _DBG_PRINT
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr1);
    debug("%s program base address[0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr1));
    debug("%s program Base Address[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x104));
#endif

    // From the O26 chip onwards, the RV offset value is fixed at 0x1000
    //core_rv0
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_rv0);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_rv0, phys_addr + RV_OFFSET);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_rv0);

    //core_rv1
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_rv1);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_rv1, phys_addr + RV_OFFSET);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_rv1);
}

static void _npu_ctrl_set_weight(unsigned int idx, phys_addr_t addr)
{
	info("%s : 0x%llX\n", __func__, addr);

	//LNX0
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr0);
	//NPU_REG_Wr01(npu_reg_hcr[0], lnx_hcr_gpr0, LNX_HCR_GPR0, addr);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr0, addr);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr0);
#ifdef _DBG_PRINT
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr0);
    debug("%s _npu_ctrl_set_weight [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr0));
    debug("%s _npu_ctrl_set_weight[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x100));
#endif
}

static void _npu_ctrl_set_feature(unsigned int idx, phys_addr_t addr)
{
	info("%s : 0x%llX\n", __func__, addr);

	//LNX0
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr4);
	//NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_gpr4, LNX_HCR_GPR4, addr);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr4, addr);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr4);
#ifdef _DBG_PRINT
	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr4);
    debug("%s _npu_ctrl_set_feature [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr4));
    debug("%s _npu_ctrl_set_feature[Direct][0x%X]\n", __func__, *(volatile UINT32 *)((void *)lnx_io_base[idx]+0x110));
#endif
}

static void _npu_ctrl_set_input(unsigned int idx, struct npu_buffer *buf, int num)
{
	phys_addr_t addr0 = 0;
	phys_addr_t addr1 = 0;

	if(num == 2)
	{
		addr0 = buf[0].phys_addr;
		addr1 = buf[1].phys_addr;
	}
	else
	{
		addr0 = buf[0].phys_addr;
		addr1 = buf[0].phys_addr;
	}

    info("%s phys_addr : 0x%llX 0x%llX\n", __func__, addr0, addr1);

	if(addr0 == 0 || addr1 == 0 )
	{
        error("Set Input : NOT setting input buffer\n");
		return;
	}

	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr2);
	NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_gpr2, LNX_HCR_GPR2, addr0);
    //NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr2, addr0);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr2);
#ifdef _DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr2);
    debug("%s _npu_ctrl_set_input(gpr2) [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr2));
#endif

	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr5);
	NPU_REG_Wr01(npu_reg_hcr[idx], lnx_hcr_gpr5, LNX_HCR_GPR5, addr1);
    //NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr5, addr1);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr5);
#ifdef _DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr5);
    debug("%s _npu_ctrl_set_input(gpr5) [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr5));
#endif
}

static void _npu_ctrl_set_output(unsigned int idx, phys_addr_t addr)
{
	info("[%d] %s : 0x%llX\n", idx, __func__, addr);

	NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr3);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr3, addr);
	NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr3);
#ifdef _DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr3);
    debug("%s _npu_ctrl_set_output [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr3));
#endif
}

static void _npu_ctrl_run_enable(unsigned int idx, bool enable)
{
    UINT32 val;

    val = (enable)? 1:0;

    if(val)
    {
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr10);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr10, 0xcafe);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr10);

        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr11);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr11, 0xcafe);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr11);

        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr12);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr12, 0xcafe);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr12);

        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr13);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_gpr13, 0xcafe);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_gpr13);

        info("[%d] _npu_ctrl_run_enable\n", idx);
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_start_set);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_start_set, 0x77);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_start_set);
#ifdef _DBG_PRINT
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_start_set);
        debug("%s [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_core_start_set));
#endif
    }
    else
    {
        info("[%d] _npu_ctrl_run_disable\n", idx);
    }

}

__maybe_unused static void _npu_ctrl_set_idle(unsigned int idx)
{
    UINT32 phy_base;
    volatile UINT32 *io_base;
    UINT32 val;

    if(idx == core_1)
        phy_base = APB_LNX1_HCR_BASE;
    else if(idx == core_0)
        phy_base = APB_LNX0_HCR_BASE;
    else
    {
        error("core_idx error.\n");
        return;
    }

    io_base = ioremap(phy_base, 0x900);
    if (!io_base)
    {
        error ("io_base ioremap() failed.\n");
        return;
    }

    if(idx == core_1)
    {
        volatile UINT32 *volatile_ptr = (volatile UINT32 *)((void *)io_base + 0x80C);
        val = *volatile_ptr;
    }
    else if(idx == core_0)
    {
        volatile UINT32 *volatile_ptr = (volatile UINT32 *)((void *)io_base + 0x808);
        val = *volatile_ptr;
    }

    info("core_%d IDLE check : 0x%X\n", idx, val);
    if((val < 0x10000)||(val > 0x10FFF))
    {
        noti("core_%d is not IDLE(0x%X), will core_reset\n", idx, val);
        _process_core_reset(idx);
    }

    if(io_base)
    {
        iounmap(io_base);
    }
}

static void _npu_ctrl_set_protected_mode(unsigned int idx, bool enable)
{
    UINT32 val;

    val = (enable)? 1:0;

    if(val)
    {
        info("[%d] _npu_ctrl_protected_mode_enable\n", idx);
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_protmode);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_protmode, 0x1);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_protmode);
#ifdef _DBG_PRINT
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_protmode);
        debug("%s [0x%X]\n", __func__, NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_core_protmode));
#endif
    }
    else
    {
        info("[%d] _npu_ctrl_protected_mode_disable\n", idx);
        NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_protmode);
        NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_protmode, 0x0);
        NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_protmode);
    }

}

#ifndef CPU_IRQ
static void _npu_hwc_work(struct work_struct *work)
{
    unsigned int idx;
    struct npu_hw_work *npu_hw_work =
    container_of ((struct work_struct *) work, struct npu_hw_work, work);
    idx = npu_hw_work->core_idx;

    if(_npu_ctrl_get_interrupt_status(idx))
    {
        _npu_ctrl_clear_interrupt(idx);
        complete_all (&npu_hw_work->done);
    }
    else if(npu_hw_work->run_wait)
    {
        schedule_work(&npu_hw_work->work);
    }
}
#endif

int lnx_v2_hwc_init(struct npu_hw *hw)
{
    int i = 0;
    info("[npu%s] %s", hw->name,  __func__);

    mutex_lock(&_lnx_device_lock);
    hw->private = (void *) &_npu_hw_work;

    if(!_open_cnt)
    {
        _process_clockgate(core_0, false);
        _process_clockgate(core_1, false);
#ifdef _DBG_PRINT
        UINT32 phy_base;

        phy_base = APB_LNX0_HCR_BASE;
        lnx_io_base[core_0] = ioremap(phy_base, 0x800);
        if (!lnx_io_base[core_0]) {
            error ("lnx_io_base[0] ioremap() failed.\n");
            mutex_unlock(&_lnx_device_lock);
            return -1;
        }

        phy_base = APB_LNX1_HCR_BASE;
        lnx_io_base[core_1] = ioremap(phy_base, 0x800);
        if (!lnx_io_base[core_1]) {
            error ("lnx_io_base[1] ioremap() failed.\n");
            mutex_unlock(&_lnx_device_lock);
            return -1;
        }
#endif
        _npu_ctrl_interrupt_enable(core_0, false);
        _npu_ctrl_interrupt_enable(core_1, false);

#ifdef CPU_IRQ
        init_waitqueue_head(&_intr_wait);
#endif
        for(i=0; i<NPU_MAX_INST; i++)
        {
            _run_cnt[i] = 0;
            _state_idx[i] = NORMAL;
            _recovery[i] = false;
        }
    }
    _open_cnt++;

    info("[%s] init::%d done\n", hw->name, _open_cnt);
    mutex_unlock(&_lnx_device_lock);

    return 0;
}

int lnx_v2_hwc_reset(struct npu_hw *hw, unsigned int idx)
{
    info("[npu%s] %s[%d]\n", hw->name, __func__, idx);

    _npu_ctrl_reset(idx);

    info("[npu%s] %s[%d] done\n", hw->name, __func__, idx);

    return 0;
}

int lnx_v2_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param)
{
    info("[npu%s][%d] %s\n", hw->name, idx, __func__);

    if((_state_idx[idx] == ABNORMAL)||(_state_idx[idx] == DISABLE))
    {
        _process_core_reset(idx);

        if(_state_idx[idx] == DISABLE)
        {
            warn("LNX status = disable");
            return 0;
        }
    }

    if((param->affinity >= 0)&&(param->affinity != idx))
    {
        error("[npu%s] affinity is different[%d : %d]\n", hw->name, idx, param->affinity);
        return -1;
    }

     _npu_ctrl_set_protected_mode(idx, param->enable_prot);

#ifdef _DBG_PRINT
    _monitor_hidden_register(idx);
#endif

    if(_npu_set_init_param(idx, param) != 0) {
        error ("[npu%s][core%d] _dne_set_init_param() failed.\n", hw->name, idx);
        return -1;
    }

#ifdef _DBG_PRINT
        _monitor_hidden_register(idx);
#endif

    if(param->program.phys_addr)
        _npu_ctrl_set_program(idx, param->program.phys_addr);
    else {
        error("[npu%s][core%d] prepare(program) fail\n", hw->name, idx);
        return -1;
    }

#ifdef _DBG_PRINT
        _monitor_hidden_register(idx);
#endif

    if(param->weight.phys_addr)
        _npu_ctrl_set_weight(idx, param->weight.phys_addr);
    else {
        error("[npu%s][core%d] prepare(weight) fail\n", hw->name, idx);
        return -1;
    }

#ifdef _DBG_PRINT
        _monitor_hidden_register(idx);
#endif

    if(param->feature.phys_addr)
        _npu_ctrl_set_feature(idx, param->feature.phys_addr);
    else {
        noti("[npu%s][core%d] no feautre buffer used\n", hw->name, idx);
    }

#ifdef _DBG_PRINT
        _monitor_hidden_register(idx);
#endif

    info("[npu%s] %s done\n", hw->name, __func__);

    return 0;
}

static void _make_reg_dump(unsigned int idx)
{
    char *argv[] = { "/bin/sh", "-c", "cat /proc/npu/npu_device_capability > /var/log/lnx_reg_dump.log", NULL };
    char *envp[] = { "HOME=/", "PATH=/sbin:/bin:/usr/sbin:/usr/bin", NULL };
    int ret;

    ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    if (ret != 0) {
        error("_make_reg_dump error %d\n", ret);
    }
}

// TODO: enable when o26 transformer model is released.
__maybe_unused static void _npu_ctrl_set_ddr_base(unsigned int idx, struct npu_run_param *param)
{
    phys_addr_t min_addr;
    int i;

    min_addr = param->output.phys_addr;

    /* check minimum address */
    for (i=0; i<param->number_of_input; i++) {
        if (param->input[i].phys_addr < min_addr) {
            min_addr = param->input[i].phys_addr;
        }
    }

    if (param->program->phys_addr < min_addr) {
        min_addr = param->program->phys_addr;
    }

    if (param->weight->phys_addr < min_addr) {
        min_addr = param->weight->phys_addr;
    }

    if (param->feature->phys_addr < min_addr) {
        min_addr = param->feature->phys_addr;
    }

    info("[%d] min_addr 0x%llX\n", idx, min_addr);

    //CORE DDR Base Address
    NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_core_ddr_base);
    NPU_REG_Wr_Sync(npu_reg_hcr[idx], lnx_hcr_core_ddr_base, min_addr);
    NPU_REG_Wr(npu_reg_hcr[idx], lnx_hcr_core_ddr_base);
}

int lnx_v2_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param)
{
#ifndef CPU_IRQ
    struct npu_hw_work *npu_hw_work = (struct npu_hw_work *) hw->private;
#endif
    int ret = -1;

    info("[npu%s] %s[%d]\n", hw->name, __func__, idx);

    param->npu_latency = 0;

    if(_state_idx[idx] != DISABLE)
    {
        _npu_ctrl_set_input(idx, param->input, param->number_of_input);
        _npu_ctrl_set_output(idx, param->output.phys_addr);
    #if 0   // TODO: enable when o26 transformer model is released.
        /* set minimum address to ddr base for o26 */
        _npu_ctrl_set_ddr_base(idx, param);
    #endif

#ifdef _DBG_PRINT
        _monitor_hidden_register(idx);
#endif

        _npu_ctrl_clear_interrupt(idx);
    }

#ifdef CPU_IRQ
    if(_state_idx[idx] == DISABLE)
    {
        lnxirqs[idx].done = false;

        if(!ret)
            noti("[npu%s][core%d] %s no access!!\n", hw->name, idx, __func__);
    }
    else
    {
        unsigned long long start_usec = 0, end_usec = 0;
        unsigned int gpr28 = 0, gpr29 = 0;

        start_usec = ktime_get_real_ns() / NSEC_PER_USEC;
        _npu_ctrl_interrupt_enable(idx, false);

        if(lnxirqs[idx].done == false)
        {
            _npu_ctrl_run_enable(idx, true);

            // TODO: fpga check timeout
            if(wait_event_interruptible_timeout(_intr_wait,
                    (lnxirqs[idx].done == true), msecs_to_jiffies(10000)) <= 0)
            {
                _make_reg_dump(idx);
                error("[npu%s][core%d] run fail(%d)\n", hw->name, idx, _run_cnt[idx]);
                if(_recovery[idx])
                {
                    _print_debug_register(idx);
                    _recovery[idx] = false;
                }
                if(_state_idx[idx] == NORMAL)
                {
                    _process_axi_flush(idx);
                    _state_idx[idx] = ABNORMAL;
                }
            }
            else
            {
                ret = 0;
                if(!_recovery[idx])
                    _recovery[idx] = true;
                if(_state_idx[idx] == RECOVERY)
                {
                    warn("%s RECOVERY[%d] SUCCESS!! \n", __func__, idx);
                }
                if(_state_idx[idx] != NORMAL)
                    _state_idx[idx] = NORMAL;

                if (_run_cnt[idx]< UINT_MAX)
                {
                    _run_cnt[idx]++;
                }
                else
                {
                    error("%s Handle error: _run_cnt[idx]is too large", __func__);
                }
                info("%s lnxirqs[%d].done \n", __func__, idx);
            }
            end_usec = ktime_get_real_ns() / NSEC_PER_USEC;
            info("[npu%s][core%d] %s === h/w kernel time %llu usec\n", hw->name, idx, __func__, end_usec - start_usec);

            NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr28);
            gpr28 = NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr28);
            NPU_REG_Rd_Sync(npu_reg_hcr[idx], lnx_hcr_gpr29);
            gpr29 = NPU_REG_Rd(npu_reg_hcr[idx], lnx_hcr_gpr29);

            info("[npu%s][core%d] === h/w counter time gpr28 %d, gpr29 %d\n", hw->name, idx, gpr28, gpr29);
        }
        else
        {
            error("%s lnxirqs[%d] status check!!\n", __func__, idx);
        }

        _npu_ctrl_set_protected_mode(idx, false);
        _npu_ctrl_run_enable(idx, false);
        lnxirqs[idx].done = false;

        if(!ret)
            info("[npu%s][core%d] %s done\n", hw->name, idx, __func__);
        else
            error("[npu%s][core%d] %s error\n", hw->name, idx, __func__);
    }

    return ret;
#else
    _npu_ctrl_run_enable(idx, true);

    npu_hw_work->core_idx = idx;
    INIT_WORK(&npu_hw_work->work, _npu_hwc_work);
    init_completion(&npu_hw_work->done);
    npu_hw_work->run_wait = true;

    schedule_work(&npu_hw_work->work);

    trace("[npu%s] wait complete\n", hw->name);

    if(wait_for_completion_interruptible_timeout(&npu_hw_work->done, msecs_to_jiffies(2000)) <= 0)
    {
        error("[npu%s] run fail\n", hw->name);

        _npu_ctrl_run_enable(idx, false);
        cancel_work_sync(&npu_hw_work->work);

        npu_hw_work->run_wait = false;
        return -1;
    }

    _npu_ctrl_run_enable(idx, false);

    info("[npu%s] %s done\n", hw->name, __func__);

    return 0;
#endif
}

int lnx_v2_hwc_release(struct npu_hw *hw)
{
    int i = 0;

    info("[npu%s] %s", hw->name, __func__);

    mutex_lock(&_lnx_device_lock);
    if(--_open_cnt == 0)
    {
        _npu_ctrl_reset(core_0);
        _npu_ctrl_reset(core_1);
        _npu_ctrl_interrupt_enable(core_0, true);
        _npu_ctrl_interrupt_enable(core_1, true);

        wake_up_interruptible(&_intr_wait);

        for(i=0; i<NPU_MAX_INST; i++)
        {
            _run_cnt[i] = 0;
            _state_idx[i] = NORMAL;
            _recovery[i] = false;
        }
    }

    info("[%s] release::%d done\n", hw->name, _open_cnt);
    mutex_unlock(&_lnx_device_lock);

    return 0;
}

int lnx_v2_hwc_pmctrl(struct npu_hw *hw, bool is_suspended)
{
#if 0	// TODO: fpga check
    if(is_suspended)
    {
        _npu_ctrl_set_idle(core_0);
        _npu_ctrl_set_idle(core_1);
    }

    _process_clockgate(core_0, is_suspended);
    _process_clockgate(core_1, is_suspended);

    if(is_suspended)
        pqe_pm_request_suspend(lnx_pqe_pm_id);
    else
        pqe_pm_request_resume(lnx_pqe_pm_id);

#endif
    return 0;
}

static void _npu_hwc_all_clear(void)
{
    info("%s\n", __func__);

	if(npu_reg_hcr[core_0].hw_reg)
	{
		iounmap (npu_reg_hcr[core_0].hw_reg);
		kfree((void *)npu_reg_hcr[core_0].shdw_reg);
	}

	if(npu_reg_hcr[core_1].hw_reg)
	{
		iounmap (npu_reg_hcr[core_1].hw_reg);
		kfree((void *)npu_reg_hcr[core_1].shdw_reg);
	}

#ifdef LNX2_SUPPORT
	if(npu_reg_hcr[core_2].hw_reg)
	{
		iounmap (npu_reg_hcr[core_2].hw_reg);
		kfree((void *)npu_reg_hcr[core_2].shdw_reg);
	}
#endif

#ifdef _DBG_PRINT
    if(lnx_io_base[core_0]) {
        iounmap(lnx_io_base[core_0]);
    }
    if(lnx_io_base[core_1]) {
        iounmap(lnx_io_base[core_1]);
    }
#endif
}

static volatile UINT32 *tz_status[4];
static volatile UINT32 *tz_clear[4];
static volatile UINT32 *iommu_ctrl_tbu1_id_control;

static irqreturn_t _tz_isr(int irq, void *dev)
{
    struct lnxirq_desc *desc = dev;

    *tz_clear[desc->dspnum] = 1;

    debug("%s irq[%d] tz[%d]\n", __func__, irq, desc->dspnum);

    debug("tz_status[%d] %x\n", desc->dspnum, *tz_status[desc->dspnum]);

    return IRQ_HANDLED;
}

static irqreturn_t _tbu_isr(int irq, void *dev)
{
    struct lnxirq_desc *desc = dev;

    noti("%s irq[%d] tbu [%d]\n", __func__, irq, desc->dspnum);

    return IRQ_HANDLED;
}

#ifdef CPU_IRQ
static irqreturn_t _npu_isr(int irq, void *dev)
{
    struct lnxirq_desc *desc = dev;

    debug("%s irq[%d] dspnum[%d]\n", __func__, irq, desc->dspnum);

    if(lnxirqs[desc->dspnum].done == false)
    {
        _npu_ctrl_clear_interrupt(desc->dspnum);
        lnxirqs[desc->dspnum].done = true;
        wake_up_interruptible(&_intr_wait);
    }

    return IRQ_HANDLED;
}
#endif

#define TZ0_IRQ	(32+169)
#define TZ1_IRQ	(32+170)
#define TZ2_IRQ	(32+171)
#define TZ3_IRQ	(32+172)

static struct lnxirq_desc tzirqs[] = {
    {"tz0", 0, TZ0_IRQ, false},
    {"tz1", 1, TZ1_IRQ, false},
    {"tz2", 2, TZ2_IRQ, false},
    {"tz3", 3, TZ3_IRQ, false},
};

#define TBU_IRQ	(32+121)

static struct lnxirq_desc tbuirqs[] = {
    {"tbu0", 0, TBU_IRQ, false},
    {"tbu1", 1, TBU_IRQ+1, false},
    {"tbu2", 2, TBU_IRQ+2, false},
    // {"tbu3", 3, TBU_IRQ+3, false},
    // {"tbu4", 4, TBU_IRQ+4, false},
    // {"tbu5", 5, TBU_IRQ+5, false},
};

/**
 * initialize LNX CRG rigster.
*/
int lnx_v2_hwc_crg_init(void)
{
    int i;
    noti("initialize LNX CRG rigster\n");

    mutex_init(&_lnx_device_lock);

#ifdef CPU_IRQ
    for(i = 0; i < ARRAY_SIZE(lnxirqs); i++)
    {
        if(request_irq(lnxirqs[i].irqnum, (irq_handler_t) _npu_isr, IRQF_TRIGGER_HIGH | IRQF_SHARED,
                    lnxirqs[i].name, &lnxirqs[i]) < 0) {
            error("[%s] request_irq()failed. irq:%s\n", __func__, lnxirqs[i].name);
            return -1;
        }
        noti("[%s] request_irq %s done.\n",  __func__, lnxirqs[i].name);
    }
#endif

    for(i = 0; i < ARRAY_SIZE(tzirqs); i++)
    {
        if(request_irq(tzirqs[i].irqnum, (irq_handler_t) _tz_isr, IRQF_TRIGGER_HIGH | IRQF_SHARED,
                    tzirqs[i].name, &tzirqs[i]) < 0) {
            error("[%s] request_irq()failed. irq:%s\n", __func__, tzirqs[i].name);
            return -1;
        }
        noti("[%s] tz request_irq %s done.\n",  __func__, tzirqs[i].name);
    }

    for(i = 0; i < ARRAY_SIZE(tbuirqs); i++)
    {
        if(request_irq(tbuirqs[i].irqnum, (irq_handler_t) _tbu_isr, IRQF_TRIGGER_HIGH | IRQF_SHARED,
                    tbuirqs[i].name, &tbuirqs[i]) < 0) {
            error("[%s] request_irq()failed. irq:%s\n", __func__, tbuirqs[i].name);
            return -1;
        }
        noti("[%s] tbu request_irq %s done.\n",  __func__, tbuirqs[i].name);
    }

    tz_status[0] = ioremap(0xC4910010, 4);
    tz_status[1] = ioremap(0xC4911010, 4);
    tz_status[2] = ioremap(0xC4912010, 4);
    tz_status[3] = ioremap(0xC4913010, 4);

    tz_clear[0] = ioremap(0xC4910014, 4);
    tz_clear[1] = ioremap(0xC4911014, 4);
    tz_clear[2] = ioremap(0xC4912014, 4);
    tz_clear[3] = ioremap(0xC4913014, 4);

    iommu_ctrl_tbu1_id_control = ioremap(0xF5A00010, 4);
    if (!iommu_ctrl_tbu1_id_control) {
        error("iommu_ctrl_tbu1_id_control remap fail\n");
		return -EFAULT;
    }

    // TODO: bit check
    /*
    tbu1_id_control ( tbu1 : lnx1 )
    [24]      : ssid_vld ( sub stream ID valid )
    default value : 0
    [23:16] : ssid ( sub stream ID )
    default value : 1
    [7:0]     : sid ( stream ID )
    default value : 1
    */
    *iommu_ctrl_tbu1_id_control = 0;
    iounmap(iommu_ctrl_tbu1_id_control);

    //LNX0
	npu_reg_hcr[core_0].hw_reg = (LNX0_HCR_REG_T *) ioremap(APB_LNX0_HCR_BASE, sizeof(LNX0_HCR_REG_T));
	if(!npu_reg_hcr[core_0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_hcr[core_0].shdw_reg = (LNX0_HCR_REG_T *)kzalloc(sizeof(LNX0_HCR_REG_T), GFP_KERNEL);

    //LNX1  -- same format of LNX0_HCR_REG_T / LNX1_HCR_REG_T, if the format is different, it must fix!!
	npu_reg_hcr[core_1].hw_reg = (LNX0_HCR_REG_T *) ioremap(APB_LNX1_HCR_BASE, sizeof (LNX0_HCR_REG_T));
	if(!npu_reg_hcr[core_1].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_hcr[core_1].shdw_reg = (LNX0_HCR_REG_T *)kzalloc(sizeof(LNX0_HCR_REG_T), GFP_KERNEL);

#ifdef LNX2_SUPPORT
    //LNX2
	npu_reg_hcr[core_2].hw_reg = (LNX2_HCR_REG_T *) ioremap(APB_LNX2_HCR_BASE, sizeof (LNX2_HCR_REG_T));
	if(!npu_reg_hcr[core_2].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_hcr[core_2].shdw_reg = (LNX2_HCR_REG_T *)kzalloc(sizeof(LNX2_HCR_REG_T), GFP_KERNEL);
#endif

#ifndef BRINGUP
    lnx_pqe_pm_id = pqe_pm_register(&lnx_pqe_pm_cfg);
#endif

    return 0;
}

/**
 * cleanup LNX module.
*/
void lnx_v2_hwc_crg_exit(void)
{
    noti("exit LNX CRG rigster\n");

    mutex_destroy(&_lnx_device_lock);

    _npu_hwc_all_clear();

#ifndef BRINGUP
    pqe_pm_unregister(lnx_pqe_pm_id);
#endif

    return;
}
