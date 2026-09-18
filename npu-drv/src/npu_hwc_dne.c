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
 *  npu hw control (DNE)
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2022.04.13
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
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/timer.h>

#include "proc_util.h"
#include "debug_util.h"

#include "logm.h"

#include "npu_drv.h"
#include "npu_hwc_dne.h"

#include "o22/O22-A0_REG_DNE0.h"
#include "o22/O22-A0_REG_DNE1.h"
#include "o22/O22-A0_REG_DNE_CTRL.h"
#include "o22/O22-A0_REG_DNE_VERI.h"
#include "o22/O22-A0_REG_DNE_MON.h"
#include "o22/O22-A0_REG_DNE_MIF0.h"
#include "o22/O22-A0_REG_DNE_MIF1.h"
#include "o22/scrg_ctrl_dne_o22a0_reg.h"
#if 1 //byKDM__Temporary Use
#include "o22/O22-A0_REG_MCU.h"
#endif

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define NOT_DBG_PRINT
//#define CHANGE_600MHZ
//#define STATUS_SHARE_REG
#define TEMP_SKIP //Common_reg_check_plz

#define NPU_MAX_INST 1
#define DUAL_CORE_IDX 0

#define APB_DNE_CTRL_BASE            0xCC880000   //( 0xCC880000, 0xCC8800FC)
#define APB_DNE_MON_BASE             0xCC880100   //( 0xCC880100, 0xCC8801FC)
#define APB_DNE_VERI_BASE            0xCC880200   //( 0xCC880200, 0xCC88020C)
#define APB_DNE0_BASE                0xCC880300   //( 0xCC880300, 0xCC88094C)
#define APB_DNE1_BASE                0xCC881200   //( 0xCC881200, 0xCC88184C)
#define APB_DNE_MIF0_BASE            0xCC882100   //( 0xCC882100, 0xCC8822BC)
#define APB_DNE_MIF1_BASE            0xCC882700   //( 0xCC882700, 0xCC8828BC)

#ifndef TEMP_SKIP //byKDM__Temporary Use
#define APB_MCU_BASE                 0xCC080000   //( 0xCC080000, 0xCC0800F8)
#endif
#ifdef CHANGE_600MHZ
#define DNE_IPW_TOP_BASE            0xCC890000
#endif
#define DNE_CLK_600MHZ		0x00000000
#define DNE_CLK_400MHZ		0x00000111

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

typedef struct {
    UINT32 program;
	UINT32 parameter;
	UINT32 feature;
	UINT32 input;
	UINT32 output;
} DNE_STRIDE_T;

static DNE_STRIDE_T *stride;

static unsigned int open_cnt = 0;
struct mutex _dne_device_lock;

#ifdef STATUS_SHARE_REG
UINT32 run_inst_cnt = 0;
UINT32 dne_run_cnt = 0;
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
#ifndef TEMP_SKIP //byKDM__Temporary Use
typedef struct {
	REG_MCU_T *hw_reg;
	REG_MCU_T *shdw_reg;
} NPU_REG_MCU_T;
#endif
#ifdef CHANGE_600MHZ
typedef struct {
	SCRG_CTRL_DNE_REG_O22A0_T *hw_reg;
	SCRG_CTRL_DNE_REG_O22A0_T *shdw_reg;
} NPU_REG_CTOP_T;
#endif

typedef struct {
	REG_DNE_CTRL_T *hw_reg;
	REG_DNE_CTRL_T *shdw_reg;
} NPU_REG_CTRL_T;

typedef struct {
	REG_DNE_MON_T *hw_reg;
	REG_DNE_MON_T *shdw_reg;
} NPU_REG_MON_T;

typedef struct {
	REG_DNE_VERI_T *hw_reg;
	REG_DNE_VERI_T *shdw_reg;
} NPU_REG_VERI_T;

typedef struct {
	REG_DNE0_T *hw_reg;
	REG_DNE0_T *shdw_reg;
} NPU_REG_DNE0_T;

typedef struct {
	REG_DNE1_T *hw_reg;
	REG_DNE1_T *shdw_reg;
} NPU_REG_DNE1_T;

typedef struct {
	REG_DNE_MIF0_T *hw_reg;
	REG_DNE_MIF0_T *shdw_reg;
} NPU_REG_MIF0_T;

typedef struct {
	REG_DNE_MIF1_T *hw_reg;
	REG_DNE_MIF1_T *shdw_reg;
} NPU_REG_MIF1_T;

struct npu_hw_work
{
    struct work_struct work;
    struct completion done;
    bool run_wait;
    bool data_img;
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
#ifndef TEMP_SKIP //byKDM__Temporary Use
static NPU_REG_MCU_T npu_reg_mcu[NPU_MAX_INST];
#endif
#ifdef CHANGE_600MHZ
static NPU_REG_CTOP_T npu_reg_ctop[NPU_MAX_INST];
#endif
static NPU_REG_CTRL_T npu_reg_ctrl[NPU_MAX_INST];
static NPU_REG_MON_T  npu_reg_mon[NPU_MAX_INST];
static NPU_REG_VERI_T npu_reg_veri[NPU_MAX_INST];
static NPU_REG_DNE0_T npu_reg_dne0[NPU_MAX_INST];
static NPU_REG_DNE1_T npu_reg_dne1[NPU_MAX_INST];
static NPU_REG_MIF0_T npu_reg_mif0[NPU_MAX_INST];
static NPU_REG_MIF1_T npu_reg_mif1[NPU_MAX_INST];

static struct npu_hw_work _npu_hw_work;

/*==============================================================================
    Implementation Group
==============================================================================*/
#ifdef STATUS_SHARE_REG
static UINT32 _get_mcu_count(void)
{
    UINT32 val;

	NPU_REG_Rd_Sync(npu_reg_veri[0], run_cnt);
    NPU_REG_Rd01(npu_reg_veri[0], run_cnt,updateCnt,val);

	return val;
}

static UINT32 _get_mcu_status(void)
{
    UINT32 val;

	NPU_REG_Rd_Sync(npu_reg_veri[0], run_cnt);
    NPU_REG_Rd01(npu_reg_veri[0], run_cnt,statusOfMcu,val);

	return val;
}

static UINT32 _get_mcu_response(void)
{
    UINT32 val;

	NPU_REG_Rd_Sync(npu_reg_veri[0], run_cnt);
    NPU_REG_Rd01(npu_reg_veri[0], run_cnt,response2Cpu,val);

	return val;
}

static void _set_drv_count(UINT32 val)
{
	NPU_REG_Rd_Sync(npu_reg_veri[0], run_dne);
    NPU_REG_Wr01(npu_reg_veri[0], run_dne, updateCnt, val);
	NPU_REG_Wr(npu_reg_veri[0], run_dne);
}

static void _set_drv_status(UINT32 val)
{
	NPU_REG_Rd_Sync(npu_reg_veri[0], run_dne);
    NPU_REG_Wr01(npu_reg_veri[0], run_dne, statusOfCpu, val);
	NPU_REG_Wr(npu_reg_veri[0], run_dne);
}

static void _set_drv_request(UINT32 val)
{
	NPU_REG_Rd_Sync(npu_reg_veri[0], run_dne);
    NPU_REG_Wr01(npu_reg_veri[0], run_dne, request2Mcu, val);
	NPU_REG_Wr(npu_reg_veri[0], run_dne);
}

static int _mcu_status_monitor(void)
{
	UINT32 timeout = jiffies + msecs_to_jiffies(100);

	while (_get_mcu_response()) {
		if(time_after(jiffies, timeout)) {
			return -1;
		}
		else
			msleep(25);
	}

	return 0;
}

static void _ctrl_run_status(void)
{
	UINT32 prev = 0;
    UINT32 val;

	_set_drv_request(0xAAAA);

	prev = _get_mcu_count();
	if(_mcu_status_monitor())
	{
		if(prev == _get_mcu_count())
			error("mcu system didn't response!!!\n");
	}
	_set_drv_status(0x1);

    NPU_REG_Rd_Sync(npu_reg_veri[0], run_dne);
    debug("%s[0x%X] done\n", __func__, NPU_REG_Rd(npu_reg_veri[0],run_dne));
}

static void _ctrl_idle_status(void)
{
    UINT32 val;

	_set_drv_request(0x5BD0);
	_set_drv_status(0x5555);

    NPU_REG_Rd_Sync(npu_reg_veri[0], run_dne);
    debug("%s[0x%X] done\n", __func__, NPU_REG_Rd(npu_reg_veri[0],run_dne));
}

static void _ctrl_update_cnt(void)
{
	_set_drv_count(dne_run_cnt++);
}
#endif

static void _npu_ctrl_reset(void)
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
    info("%s done\n", __func__);
}

static int _dne_set_init_param(struct npu_prepare_param *param)
{
    int i, gap = 0;
    UINT32 phy_base;
    volatile UINT32 *io_base;

    info("%s\n", __func__);

    phy_base = APB_DNE_CTRL_BASE;

    io_base = ioremap(phy_base, 0x28C0);
    if (!io_base) {
        error ("base_addr ioremap() failed.\n");
        return -1;
    }

    for(i=0; i<param->reg_num; i++)
    {
        debug("param->reg_info[%d] [0x%X:0x%X] \n", i, param->reg_info[i].address, param->reg_info[i].value);
        gap = param->reg_info[i].address - phy_base;
        *(volatile UINT32 *)((void *)io_base+gap) = param->reg_info[i].value;
    }

    if(io_base) {
        iounmap(io_base);
    }

#ifndef NOT_DBG_PRINT
    debug("dne_ctrl_340 setting\n");
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_340);
    NPU_REG_Wr_Sync(npu_reg_dne0[0], dne_ctrl_340, 0xffffffff);
    NPU_REG_Wr(npu_reg_dne0[0], dne_ctrl_340);

    debug("dne_ctrl_396 setting\n");
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_396);
    NPU_REG_Wr01(npu_reg_dne0[0], dne_ctrl_396,dbg_capture_en, 3);
    NPU_REG_Wr(npu_reg_dne0[0], dne_ctrl_396);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_396);

/*
    debug("_dne_set_init_param[DNE0] [0x%X]\n", APB_DNE0_BASE);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_000);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_040);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_041);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_042);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_043);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_044);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_045);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_047);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_048);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_050);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_051);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_052);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_053);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_054);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_055);
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_056);

    debug("_dne_set_init_param[DNE1] [0x%X]\n", APB_DNE1_BASE);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_000);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_040);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_041);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_042);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_043);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_044);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_045);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_047);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_048);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_050);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_051);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_052);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_053);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_054);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_055);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_056);
*/
#endif

    return 0;
}

static int _dne_set_stride_info(unsigned int str_num, unsigned int *str_info)
{
    info("%s\n", __func__);

    if(str_num != (sizeof(DNE_STRIDE_T)/sizeof(unsigned int)))
    {
        error("stride_info size mismatch!!! (%d)]\n", str_num);
    }

    stride = (DNE_STRIDE_T *)str_info;

#ifndef NOT_DBG_PRINT
    int i = 0;

    for(i=0; i<str_num; i++)
    {
        debug("param->stride_num[%d] = %d \n", i, str_info[i]);
    }

    info("%s [%d | %d | %d | %d | %d]\n", __func__,
        stride->program, stride->parameter, stride->feature, stride->input, stride->output);
#endif

    return 0;
}

static void _dne_set_mif_mask(UINT32 id, BOOLEAN mask)
{
    info("%s [%d:%d]\n", __func__, id, mask);
	if(id == 0)
	{
	    debug("%s [0x%X]\n", __func__, APB_DNE_MIF0_BASE);
		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_prg_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_prg_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_prg_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght0_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght1_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght1_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr2_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr2_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr0_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr1_mb_req);
		NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr1_mb_req);
	}
	else
	{
	    debug("%s [0x%X]\n", __func__, APB_DNE_MIF1_BASE);
		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_prg_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_prg_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_prg_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght0_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght1_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght1_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr2_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr2_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr2_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr0_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr0_mb_req);

		NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr1_mb_req);
		NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_mb_req, req_msk_f_on, mask);
		NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr1_mb_req);

	}
}

#if 0 //Not Used
static void _dne_set_obdd_param(void)
{
	const UINT32 layer_num				= 49;

	info("%s (layer_num = %d)\n", __func__, layer_num);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_000);
	NPU_REG_Wr01(npu_reg_dne0[0], dne_ctrl_000, layer_num, layer_num);
	NPU_REG_Wr(npu_reg_dne0[0], dne_ctrl_000);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_000);
	NPU_REG_Wr01(npu_reg_dne1[0], dne_ctrl_000, layer_num, layer_num);
	NPU_REG_Wr(npu_reg_dne1[0], dne_ctrl_000);
}

static void _dne_set_api_param(void)
{
	const UINT32 layer_num				= 14;

	info("%s (layer_num = %d)\n", __func__, layer_num);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_000);
	NPU_REG_Wr01(npu_reg_dne0[0], dne_ctrl_000, layer_num, layer_num);
	NPU_REG_Wr(npu_reg_dne0[0], dne_ctrl_000);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_000);
	NPU_REG_Wr01(npu_reg_dne1[0], dne_ctrl_000, layer_num, layer_num);
	NPU_REG_Wr(npu_reg_dne1[0], dne_ctrl_000);
}
#endif

static void _npu_ctrl_init(void)
{
#ifndef TEMP_SKIP  //400MHz
	//_write_reg(CTOP_DNECLK_ADDR, DNE_CLK_400MHZ);
	NPU_REG_Rd_Sync(npu_reg_ctop[0], crg_dne04);
	debug("[SET_400MHZ] npu_reg_ctop:crg_dne04 = 0x%X\n", NPU_REG_Rd(npu_reg_ctop[0],crg_dne04));
    if(NPU_REG_Rd(npu_reg_ctop[0],crg_dne04) != DNE_CLK_400MHZ) {
        NPU_REG_Wr_Sync(npu_reg_ctop[0], crg_dne04, DNE_CLK_400MHZ);
        NPU_REG_Wr(npu_reg_ctop[0], crg_dne04);
	    noti("[SET_400MHZ] npu_reg_ctop:crg_dne04 = 0x%X\n", NPU_REG_Rd(npu_reg_ctop[0],crg_dne04));
    }
#endif
#ifdef CHANGE_600MHZ
	//_write_reg(CTOP_DNECLK_ADDR, DNE_CLK_400MHZ);
	NPU_REG_Rd_Sync(npu_reg_ctop[0], crg_dne04);
	debug("[CHANGE_600MHZ] npu_reg_ctop:crg_dne04 = 0x%X\n", NPU_REG_Rd(npu_reg_ctop[0],crg_dne04));
    if(NPU_REG_Rd(npu_reg_ctop[0],crg_dne04) != DNE_CLK_600MHZ) {
        NPU_REG_Wr_Sync(npu_reg_ctop[0], crg_dne04, DNE_CLK_600MHZ);
        NPU_REG_Wr(npu_reg_ctop[0], crg_dne04);
	    noti("[CHANGE_600MHZ] npu_reg_ctop:crg_dne04 = 0x%X\n", NPU_REG_Rd(npu_reg_ctop[0],crg_dne04));
    }
#endif

	_dne_set_mif_mask(0, FALSE);
	_dne_set_mif_mask(1, FALSE);
	//_dne_set_obdd_param();

	NPU_REG_Rd_Sync(npu_reg_mon[0], ctrl_crc_num_16);
	debug("npu_reg_mon:ctrl_crc_num_16 = 0x%X\n", NPU_REG_Rd(npu_reg_mon[0],ctrl_crc_num_16));
    if(NPU_REG_Rd(npu_reg_mon[0],ctrl_crc_num_16) != 0xffffffff) {
        NPU_REG_Wr_Sync(npu_reg_mon[0], ctrl_crc_num_16, 0xffffffff);
        NPU_REG_Wr(npu_reg_mon[0], ctrl_crc_num_16);
    }

    info ("%s done\n", __func__);
}

static void _npu_ctrl_interrupt_enable(bool enable)
{
	BOOLEAN mask;

	mask = (enable)?0:1;

#if 0 //byKDM__Check plz.
    info("_npu_ctrl_interrupt_enable [0x%X]\n", APB_DNE_CTRL_BASE);
	NPU_REG_Rd_Sync(npu_reg_ctrl[0], ctrl_pic_end);
	NPU_REG_Wr01(npu_reg_ctrl[0], ctrl_pic_end, g0_pic_end_en, enable);
	NPU_REG_Wr01(npu_reg_ctrl[0], ctrl_pic_end, g4_pic_end_en, enable);
	NPU_REG_Wr(npu_reg_ctrl[0], ctrl_pic_end);

	NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_mask);
	NPU_REG_Wr01(npu_reg_ctrl[0], intr_mask, mask_g0_pic_end, mask);
	NPU_REG_Wr01(npu_reg_ctrl[0], intr_mask, mask_g4_pic_end, mask);
	NPU_REG_Wr(npu_reg_ctrl[0], intr_mask);

	NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_reg);
	NPU_REG_Wr01(npu_reg_ctrl[0], intr_reg, intr_g0_pic_end, mask);
	NPU_REG_Wr01(npu_reg_ctrl[0], intr_reg, intr_g4_pic_end, mask);
	NPU_REG_Wr(npu_reg_ctrl[0], intr_reg);

//#else
	_write_reg(gpREG_DNE_CTRL->ctrl_pic_end.g0_pic_end_en, enable);
	_write_reg(gpREG_DNE_CTRL->ctrl_pic_end.g4_pic_end_en, enable);
	_write_reg(gpREG_DNE_CTRL->intr_mask.mask_g0_pic_end, mask);
	_write_reg(gpREG_DNE_CTRL->intr_mask.mask_g4_pic_end, mask);
	_write_reg(gpREG_DNE_CTRL->intr_reg.intr_g0_pic_end, mask);
	_write_reg(gpREG_DNE_CTRL->intr_reg.intr_g4_pic_end, mask);
#endif

#ifndef TEMP_SKIP
    if(mask)
    {
        info("_npu_ctrl_interrupt_enable\n");
        //REG_DNE_CTRL_INTR_MUX
        NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_mux);
        NPU_REG_Wr_Sync(npu_reg_ctrl[0], intr_mux, 0xffffffff);
        NPU_REG_Wr(npu_reg_ctrl[0], intr_mux);

        //REG_MCU_INTR_CPU_FLAG_EN
        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_mcu_flag);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_mcu_flag_en);
        NPU_REG_Wr01(npu_reg_mcu[0], intr_mcu_flag_en, dne_mcu_intr_mcu_en, 0);
        NPU_REG_Wr(npu_reg_mcu[0], intr_mcu_flag_en);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_cpu_flag);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_cpu_flag_en);
        NPU_REG_Wr01(npu_reg_mcu[0], intr_cpu_flag_en, dne_mcu_intr_cpu_en, 1);
        NPU_REG_Wr(npu_reg_mcu[0], intr_cpu_flag_en);
    }
    else
    {
        info("_npu_ctrl_interrupt_disable\n");
        //REG_DNE_CTRL_INTR_MUX
        NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_mux);
        NPU_REG_Wr_Sync(npu_reg_ctrl[0], intr_mux, 0x0);
        NPU_REG_Wr(npu_reg_ctrl[0], intr_mux);

        //REG_MCU_INTR_CPU_FLAG_EN
        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_mcu_flag);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_mcu_flag_en);
        NPU_REG_Wr01(npu_reg_mcu[0], intr_mcu_flag_en, dne_mcu_intr_mcu_en, 1);
        NPU_REG_Wr(npu_reg_mcu[0], intr_mcu_flag_en);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_cpu_flag);

        NPU_REG_Rd_Sync(npu_reg_mcu[0], intr_cpu_flag_en);
        NPU_REG_Wr01(npu_reg_mcu[0], intr_cpu_flag_en, dne_mcu_intr_cpu_en, 0);
        NPU_REG_Wr(npu_reg_mcu[0], intr_cpu_flag_en);
    }
#else
    if(mask)
        debug("_npu_ctrl_interrupt_enable[SKIP]\n");
    else
        debug("_npu_ctrl_interrupt_disable[SKIP]\n");
#endif
}

static bool _npu_ctrl_get_interrupt_status(void)
{
	unsigned int irq_status = 0;
    UINT32 val;

	NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_reg);

#if 0
    debug("_npu_ctrl_get_interrupt_status [0x%x]\n", NPU_REG_Rd(npu_reg_ctrl[0], intr_reg));

	NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_210);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_210,dne_init_end_status,val);
	debug("[DBG]npu_reg_dne0:dne_init_end_status = 0x%X\n", val);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_210,dne_init_rise_count,val);
	debug("[DBG]npu_reg_dne0:dne_init_rise_count = 0x%X\n", val);
#endif

    NPU_REG_Rd01(npu_reg_ctrl[0], intr_reg,intr_g0_pic_end,val);
	if(val == 1)
	{
		irq_status = irq_status | 0x1;
		debug("[%s] DNE0 END\n", __func__);
	}

    NPU_REG_Rd01(npu_reg_ctrl[0], intr_reg,intr_g4_pic_end,val);
	if(val == 1)
	{
		irq_status = irq_status | 0x2;
		debug("[%s] DNE1 END\n", __func__);
	}

	if((irq_status & 0x3) == 3)
	{
		info("[%s] interrupted!!!!\n", __func__);
		return true;
	}

	return false;
}

static void _npu_ctrl_clear_interrupt(void)
{
    NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_reg);

    NPU_REG_Wr01(npu_reg_ctrl[0], intr_reg,intr_g0_pic_end, 1);
    NPU_REG_Wr01(npu_reg_ctrl[0], intr_reg,intr_g4_pic_end, 1);
	NPU_REG_Wr(npu_reg_ctrl[0], intr_reg);

#ifndef NOT_DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_reg);
    debug("%s done[0x%x]\n", __func__, NPU_REG_Rd(npu_reg_ctrl[0], intr_reg));
    NPU_REG_Rd_Sync(npu_reg_ctrl[0], intr_reg);
    debug("%s done![0x%x]\n", __func__, NPU_REG_Rd(npu_reg_ctrl[0], intr_reg));
#else
    debug("%s done\n", __func__);
#endif
}

static void _npu_ctrl_set_program(phys_addr_t addr)
{
    info("%s : 0x%llX (%d)\n", __func__, addr, stride->program);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_prg_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_prg_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_prg_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_prg_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_prg_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_prg_cmd_stride, cmd_stride, stride->program);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_prg_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_prg_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_prg_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_prg_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_prg_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_prg_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_prg_cmd_stride, cmd_stride, stride->program);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_prg_cmd_stride);
}

static void _npu_ctrl_set_weight(phys_addr_t addr)
{
	info("%s : 0x%llX (%d)\n", __func__, addr, stride->parameter);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght0_cmd_stride, cmd_stride, stride->parameter);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_wght1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_wght1_cmd_stride, cmd_stride, stride->parameter);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_wght1_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght0_cmd_stride, cmd_stride, stride->parameter);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_wght1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_wght1_cmd_stride, cmd_stride, stride->parameter);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_wght1_cmd_stride);
}

static void _npu_ctrl_set_feature(phys_addr_t addr, bool data_img)
{
	info("%s : 0x%llX (%d)\n", __func__, addr, stride->feature);

    if(data_img) {
		debug("Set Input : IMG data set\n");

		//DNE0
		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr, cmd_saddr, addr);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr, cmd_saddr, addr);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);

		NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
		NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr, cmd_saddr, addr);
		NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
    }

	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr2_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr2_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr1_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr2_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr2_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr2_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr2_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr2_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr2_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr2_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_cmd_stride, cmd_stride, stride->feature);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr1_cmd_stride);
}

static void _npu_ctrl_set_input(struct npu_buffer *buf, int num, bool data_img)
{
#if 1 //byDM
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

	info("%s : 0x%llX 0x%llX (%d)\n", __func__, addr0, addr1, stride->input);

	if(addr0 == 0 || addr1 == 0 )
	{
        error("Set Input : NOT setting input buffer\n");
		return;
	}

    if(!data_img) {
        debug("Set Input : NON-IMG data set\n");
        //DNE0
        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr, cmd_saddr, addr0);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);

        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr, cmd_saddr, addr0);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);

        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr, cmd_saddr, addr0);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
    }

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr, cmd_saddr, addr0);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr, cmd_saddr, addr1);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr, cmd_saddr, addr0);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr, cmd_saddr, addr1);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride);
#else
    if(!data_img) {
        debug("Set Input : NON-IMG data set\n");
        //DNE0
        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr, cmd_saddr, addr);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_1_cmd_saddr);

        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr, cmd_saddr, addr);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_1_cmd_saddr);

        NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
        NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr, cmd_saddr, addr);
        NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr2_cmd_saddr);
    }

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif0[0], r_dne0_iftr1_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_cmd_saddr);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr0_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride, cmd_stride, stride->input);
	NPU_REG_Wr(npu_reg_mif1[0], r_dne1_iftr1_cmd_stride);
#endif
}

static void _npu_ctrl_set_output(phys_addr_t addr)
{
	info("%s : 0x%llX (%d)\n", __func__, addr, stride->output);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_stride, cmd_stride, stride->output);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_stride, cmd_stride, stride->output);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_stride);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_stride, cmd_stride, stride->output);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_stride);

	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_stride);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_stride, cmd_stride_mod, 1);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_stride, cmd_stride, stride->output);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_stride);

	//DNE0
	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr0_1_cmd_saddr);
	NPU_REG_Rd_Sync(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif0[0], w_dne0_oftr1_1_cmd_saddr);

	//DNE1
	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr0_1_cmd_saddr);
	NPU_REG_Rd_Sync(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_saddr);
	NPU_REG_Wr01(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_saddr, cmd_saddr, addr);
	NPU_REG_Wr(npu_reg_mif1[0], w_dne1_oftr1_1_cmd_saddr);
}

static void _npu_ctrl_run_enable(bool enable)
{
	UINT32 val;

	val = (enable)? 1:0;

    if(val)
    {
        info("_npu_ctrl_run_enable\n");
    }
    else
    {
        info("_npu_ctrl_run_disable\n");
    }

	//REG_TOP_PicInit
	NPU_REG_Rd_Sync(npu_reg_ctrl[0], pic_init);
	NPU_REG_Wr01(npu_reg_ctrl[0], pic_init, g0_pic_init, val);
	NPU_REG_Wr01(npu_reg_ctrl[0], pic_init, g4_pic_init, val);
	NPU_REG_Wr(npu_reg_ctrl[0], pic_init);

	//REG_TOP_PicStart
	NPU_REG_Rd_Sync(npu_reg_ctrl[0], pic_start);
	NPU_REG_Wr01(npu_reg_ctrl[0], pic_start, g0_pic_start, val);
	NPU_REG_Wr01(npu_reg_ctrl[0], pic_start, g4_pic_start, val);
	NPU_REG_Wr(npu_reg_ctrl[0], pic_start);

}

static void _npu_hwc_work(struct work_struct *work)
{
    struct npu_hw_work *npu_hw_work =
    container_of ((struct work_struct *) work, struct npu_hw_work, work);

    if(_npu_ctrl_get_interrupt_status())
    {
        _npu_ctrl_clear_interrupt();
        complete_all (&npu_hw_work->done);
    }
    else if(npu_hw_work->run_wait)
    {
        schedule_work(&npu_hw_work->work);
    }
}

int dne_hwc_init(struct npu_hw *hw)
{
    info("[%s] %s", hw->name, __func__);

    mutex_lock(&_dne_device_lock);
    hw->private = (void *) &_npu_hw_work;

#ifdef STATUS_SHARE_REG
    run_inst_cnt++;
    if(run_inst_cnt == 1)
        _ctrl_run_status();
#endif

    if(!open_cnt)
    {
        _npu_ctrl_init();
        _npu_ctrl_interrupt_enable(false);
    }
    open_cnt++;

#ifndef NOT_DBG_PRINT
    NPU_REG_Rd_Sync(npu_reg_mon[0], ctrl_crc_num_16);
    debug("npu_reg_mon:ctrl_crc_num_16 = 0x%X\n", NPU_REG_Rd(npu_reg_mon[0],ctrl_crc_num_16));
    if(NPU_REG_Rd(npu_reg_mon[0],ctrl_crc_num_16) != 0xffffffff) {
        NPU_REG_Wr_Sync(npu_reg_mon[0], ctrl_crc_num_16, 0xffffffff);
        NPU_REG_Wr(npu_reg_mon[0], ctrl_crc_num_16);
    }
#endif

    info("[%s] init::%d done\n", hw->name, open_cnt);
    mutex_unlock(&_dne_device_lock);

    return 0;
}

int dne_hwc_reset(struct npu_hw *hw, unsigned int idx)
{
    info("[%s] %s\n", hw->name, __func__);

    if(idx > DUAL_CORE_IDX)
    {
        error("DNE only support Dual Core Mode\n");
        return -1;
    }

    _npu_ctrl_reset();

    info("[%s] %s done\n", hw->name, __func__);

    return 0;
}

int dne_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param)
{
    struct npu_hw_work *npu_hw_work = (struct npu_hw_work *) hw->private;

    info("[%s] %s\n", hw->name, __func__);

    if(idx > DUAL_CORE_IDX)
    {
        error("DNE only support Dual Core Mode\n");
        return -1;
    }

    if(param->reg_num)
    {
        if(_dne_set_init_param(param) != 0)
        {
            error ("[%s] _dne_set_init_param() failed.\n", hw->name);
            return -1;
        }
    }
    else
    {
        info("[%s] _dne_set_init_param no_setting\n", hw->name);
    }

    if(param->stride_num)
    {
        _dne_set_stride_info(param->stride_num, param->stride_info);
    }
    else
    {
        info("[%s] _dne_set_stride_info no_setting\n", hw->name);
    }

    if(param->program.phys_addr)
        _npu_ctrl_set_program(param->program.phys_addr);
    else
    {
        error("[%s] prepare(program) fail\n", hw->name);
        return -1;
    }

    if(param->weight.phys_addr)
        _npu_ctrl_set_weight(param->weight.phys_addr);
    else
    {
        error("[%s] prepare(weight) fail\n", hw->name);
        return -1;
    }

    debug("[%s] prepare img_data[%s]\n", hw->name, param->data_img? "TRUE":"FALSE");
    npu_hw_work->data_img = param->data_img;

    if(param->feature.phys_addr)
        _npu_ctrl_set_feature(param->feature.phys_addr, npu_hw_work->data_img);
    else
    {
        error("[%s] prepare(feature) fail\n", hw->name);
        return -1;
    }

    info("[%s] %s done\n", hw->name, __func__);

    return 0;
}

int dne_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param)
{
    struct npu_hw_work *npu_hw_work = (struct npu_hw_work *) hw->private;
    UINT32 val;

    info("[%s] %s\n", hw->name, __func__);

    if(idx > DUAL_CORE_IDX)
    {
        error("DNE only support Dual Core Mode\n");
        return -1;
    }

    param->npu_latency = 0;
#ifndef NOT_DBG_PRINT //compare layer_num/layer_cnt (expected the same value)
	NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_000);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_000,layer_num, val);
	debug("[DBG]npu_reg_dne0:dne_ctrl_000 = 0x%X\n", val);
	NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_000);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_000,layer_num, val);
	debug("[DBG]npu_reg_dne1:dne_ctrl_000 = 0x%X\n", val);
#endif
    _npu_ctrl_set_input(param->input, param->number_of_input, npu_hw_work->data_img);
	_npu_ctrl_set_output(param->output.phys_addr);
    _npu_ctrl_run_enable(true);

    INIT_WORK(&npu_hw_work->work, _npu_hwc_work);
    init_completion(&npu_hw_work->done);
    npu_hw_work->run_wait = true;

    schedule_work(&npu_hw_work->work);

    trace("[%s] wait complete\n", hw->name);

    if(wait_for_completion_interruptible_timeout(&npu_hw_work->done, msecs_to_jiffies (1000)) <= 0)
    {
        error("[%s] run fail\n", hw->name);

        _npu_ctrl_run_enable(false);
        cancel_work_sync(&npu_hw_work->work);

        npu_hw_work->run_wait = false;
        return -1;
    }

    //dne processing cycle
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_209);
    val = NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_209);
#ifndef CHANGE_600MHZ
    param->npu_latency = val*25/10000000;
    info("[400MHZ] DNE_process_time [ %d ms][ %d ns]\n", param->npu_latency, val*25/10); //400MHZ
#else
    param->npu_latency = val*16/10000000;
    info("[600MHZ] DNE_process_time [ %d ms][ %d ns]\n", param->npu_latency, val*16/10); //600MHZ
#endif

    //CRC Register Check
    debug(" CRC Register Check!!\n");
    debug("Start: Get_CRC_DNE0.\n");
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_pres_pic_init);
    debug("DNE_MON, info_stamp0_pres_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_pres_pic_init));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_pres_pic_start);
    debug("DNE_MON, info_stamp0_pres_pic_start     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_pres_pic_start));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_pres_pic_end);
    debug("DNE_MON, info_stamp0_pres_pic_end     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_pres_pic_end));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_prev_pic_init);
    debug("DNE_MON, info_stamp0_prev_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_prev_pic_init));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_prev_pic_start);
    debug("DNE_MON, info_stamp0_prev_pic_start     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_prev_pic_start));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp0_prev_pic_end);
    debug("DNE_MON, info_stamp0_prev_pic_end     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp0_prev_pic_end));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_pres_pic_init);
    debug("DNE_MON, info_stamp1_pres_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_pres_pic_init));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_pres_pic_start);
    debug("DNE_MON, info_stamp1_pres_pic_start     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_pres_pic_start));

    debug("Start: Get_CRC_DNE1.\n");
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_pres_pic_end);
    debug("DNE_MON, info_stamp1_pres_pic_end     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_pres_pic_end));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_prev_pic_init);
    debug("DNE_MON, info_stamp1_prev_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_prev_pic_init));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_prev_pic_start);
    debug("DNE_MON, info_stamp1_prev_pic_start     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_prev_pic_start));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp1_prev_pic_end);
    debug("DNE_MON, info_stamp1_prev_pic_end     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp1_prev_pic_end));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp2_pres_pic_init);
    debug("DNE_MON, info_stamp2_pres_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp2_pres_pic_init));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp2_pres_pic_start);
    debug("DNE_MON, info_stamp2_pres_pic_start     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp2_pres_pic_start));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp2_pres_pic_end);
    debug("DNE_MON, info_stamp2_pres_pic_end     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp2_pres_pic_end));
    NPU_REG_Rd_Sync(npu_reg_mon[0], info_stamp2_prev_pic_init);
    debug("DNE_MON, info_stamp2_prev_pic_init     ) = 0x%8X\n", NPU_REG_Rd(npu_reg_mon[0], info_stamp2_prev_pic_init));

#ifndef NOT_DBG_PRINT
    //Binary Data Check (1:weg, 3: input)
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_397);
    debug("[KDM] dne_ctrl_397 = 0x%X\n", NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_397));
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_398);
    debug("[KDM] dne_ctrl_398 = 0x%X\n", NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_398));
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_399);
    debug("[KDM] dne_ctrl_399 = 0x%X\n", NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_399));
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_400);
    debug("[KDM] dne_ctrl_400 = 0x%X\n", NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_400));
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_401);
    debug("[KDM] dne_ctrl_401 = 0x%X\n", NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_401));

	//compare layer_num/layer_cnt (expected the same value)
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_011);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_011,layer_cnt, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_011 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_011);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_011,layer_cnt, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_011 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_012);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_012,layer_cnt_swbrd, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_012 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_012);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_012,layer_cnt_swbrd, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_012 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_013);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_013,layer_cnt_dw, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_013 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_013);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_013,layer_cnt_dw, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_013 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_014);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_014,layer_cnt_ofmlfu, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_014 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_014);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_014,layer_cnt_ofmlfu, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_014 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_015);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_015,layer_cnt_upload, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_015 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_015);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_015,layer_cnt_upload, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_015 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_016);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_016,state_cnt, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_016 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_016);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_016,state_cnt, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_016 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_017);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_017,dne1_state_end, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_017 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_017);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_017,dne1_state_end, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_017 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_018);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_018,dne1_state_req, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_018 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_018);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_018,dne1_state_req, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_018 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_019);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_019,dne1_layer_cnt_mif, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_019 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_019);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_019,dne1_layer_cnt_mif, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_019 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_020);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_020,dne1_layer_cnt_swbrd, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_020 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_020);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_020,dne1_layer_cnt_swbrd, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_020 = 0x%X\n", val);

    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_021);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_021,dne1_layer_cnt_dw, val);
    debug("[DBG]npu_reg_dne0:dne_ctrl_021 = 0x%X\n", val);
    NPU_REG_Rd_Sync(npu_reg_dne1[0], dne_ctrl_021);
    NPU_REG_Rd01(npu_reg_dne1[0], dne_ctrl_021,dne1_layer_cnt_dw, val);
    debug("[DBG]npu_reg_dne1:dne_ctrl_021 = 0x%X\n", val);

    //pic_end
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_024);
    val = NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_024);
    debug("[DBG]npu_reg_dne0:dne_ctrl_024 = 0x%X\n", val);

    //pic_end_mdf
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_025);
    val = NPU_REG_Rd(npu_reg_dne0[0],dne_ctrl_025);
    debug("[DBG]npu_reg_dne0:dne_ctrl_025 = 0x%X\n", val);

	// CHECK pic_end by dne_init_end_status/dne_init_rise_count
    NPU_REG_Rd_Sync(npu_reg_dne0[0], dne_ctrl_210);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_210,dne_init_end_status,val);
    debug("[DBG]npu_reg_dne0:dne_init_end_status = 0x%X\n", val);
    NPU_REG_Rd01(npu_reg_dne0[0], dne_ctrl_210,dne_init_rise_count,val);
    debug("[DBG]npu_reg_dne0:dne_init_rise_count = 0x%X\n", val);
#endif

    _npu_ctrl_run_enable(false);

#ifdef STATUS_SHARE_REG
    _ctrl_update_cnt();
#endif

    info("[%s] %s done\n", hw->name, __func__);

    return 0;
}

int dne_hwc_release(struct npu_hw *hw)
{
    info("[%s] %s", hw->name, __func__);

    mutex_lock(&_dne_device_lock);
    if(--open_cnt == 0)
    {
        _npu_ctrl_reset();
        _npu_ctrl_interrupt_enable(true);
    }

#ifdef STATUS_SHARE_REG
    --run_inst_cnt;
    if(!run_inst_cnt)
    {
        _ctrl_idle_status();
        dne_run_cnt = 0;
    }
#endif

    info("[%s] release::%d done\n", hw->name, open_cnt);
    mutex_unlock(&_dne_device_lock);

    return 0;
}

int dne_hwc_pmctrl(struct npu_hw *hw, bool is_suspended)
{
    info("[npu%s] %s:%d", hw->name, __func__, is_suspended);

    if(is_suspended)
        debug("[%s] pm_request_suspend\n", hw->name);
    else
        debug("[%s] pm_request_resume\n", hw->name);

    return 0;
}

static void _npu_hwc_all_clear(void)
{
    info("%s\n", __func__);

#ifndef TEMP_SKIP //byKDM__Temporary Use
	if (npu_reg_mcu[0].hw_reg)
	{
		iounmap (npu_reg_mcu[0].hw_reg);
		kfree((void *)npu_reg_mcu[0].shdw_reg);
	}
#endif
#ifdef CHANGE_600MHZ
	if (npu_reg_ctop[0].hw_reg)
	{
		iounmap (npu_reg_ctop[0].hw_reg);
		kfree((void *)npu_reg_ctop[0].shdw_reg);
	}
#endif

	if (npu_reg_ctrl[0].hw_reg)
	{
		iounmap (npu_reg_ctrl[0].hw_reg);
		kfree((void *)npu_reg_ctrl[0].shdw_reg);
	}

	if (npu_reg_mon[0].hw_reg)
	{
		iounmap (npu_reg_mon[0].hw_reg);
		kfree((void *)npu_reg_mon[0].shdw_reg);
	}

	if (npu_reg_veri[0].hw_reg)
	{
		iounmap (npu_reg_veri[0].hw_reg);
		kfree((void *)npu_reg_veri[0].shdw_reg);
	}

	if (npu_reg_dne0[0].hw_reg)
	{
		iounmap (npu_reg_dne0[0].hw_reg);
		kfree((void *)npu_reg_dne0[0].shdw_reg);
	}

	if (npu_reg_dne1[0].hw_reg)
	{
		iounmap (npu_reg_dne1[0].hw_reg);
		kfree((void *)npu_reg_dne1[0].shdw_reg);
	}

	if (npu_reg_mif0[0].hw_reg)
	{
		iounmap (npu_reg_mif0[0].hw_reg);
		kfree((void *)npu_reg_mif0[0].shdw_reg);
	}

	if (npu_reg_mif1[0].hw_reg)
	{
		iounmap (npu_reg_mif1[0].hw_reg);
		kfree((void *)npu_reg_mif1[0].shdw_reg);
	}
}

/**
 * initialize DNE CRG rigster.
*/
int dne_hwc_crg_init(void)
{
    noti("initialize DNE CRG rigster\n");

    mutex_init(&_dne_device_lock);
#ifndef TEMP_SKIP //byKDM__Temporary Use
	npu_reg_mcu[0].hw_reg = (NPU_REG_MCU_T *) ioremap(APB_MCU_BASE,
                            sizeof(NPU_REG_MCU_T));
	if(!npu_reg_mcu[0].hw_reg)
	{
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_mcu[0].shdw_reg = (NPU_REG_MCU_T *)kzalloc(sizeof(NPU_REG_MCU_T),
	                            GFP_KERNEL);
#endif
#ifdef CHANGE_600MHZ
    npu_reg_ctop[0].hw_reg = (NPU_REG_CTOP_T *) ioremap (DNE_IPW_TOP_BASE,
                            sizeof(NPU_REG_CTOP_T));
	if(!npu_reg_ctop[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_ctop[0].shdw_reg = (NPU_REG_CTOP_T *)kzalloc(sizeof(NPU_REG_CTOP_T),
	                            GFP_KERNEL);
#endif
	npu_reg_ctrl[0].hw_reg = (REG_DNE_CTRL_T *) ioremap(APB_DNE_CTRL_BASE, sizeof (REG_DNE_CTRL_T));
	if(!npu_reg_ctrl[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("ctrl remap fail\n");
		return -EFAULT;
	}
	npu_reg_ctrl[0].shdw_reg = (REG_DNE_CTRL_T *)kzalloc(sizeof(REG_DNE_CTRL_T), GFP_KERNEL);

	npu_reg_mon[0].hw_reg =
			(REG_DNE_MON_T *) ioremap(APB_DNE_MON_BASE, sizeof (REG_DNE_MON_T));
	if(!npu_reg_mon[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("mon remap fail\n");
		return -EFAULT;
	}
	npu_reg_mon[0].shdw_reg = (REG_DNE_MON_T *)kzalloc(sizeof(REG_DNE_MON_T), GFP_KERNEL);

	npu_reg_veri[0].hw_reg =
			(REG_DNE_VERI_T *) ioremap(APB_DNE_VERI_BASE, sizeof (REG_DNE_VERI_T));
	if(!npu_reg_veri[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("veri remap fail\n");
		return -EFAULT;
	}
	npu_reg_veri[0].shdw_reg = (REG_DNE_VERI_T *)kzalloc(sizeof(REG_DNE_VERI_T), GFP_KERNEL);

	npu_reg_dne0[0].hw_reg =
			(REG_DNE0_T *) ioremap(APB_DNE0_BASE, sizeof (REG_DNE0_T));
	if(!npu_reg_dne0[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("dne0 remap fail\n");
		return -EFAULT;
	}
	npu_reg_dne0[0].shdw_reg = (REG_DNE0_T *)kzalloc(sizeof(REG_DNE0_T), GFP_KERNEL);

	npu_reg_dne1[0].hw_reg =
			(REG_DNE1_T *) ioremap (APB_DNE1_BASE, sizeof (REG_DNE1_T));
	if(!npu_reg_dne1[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("dne1 remap fail\n");
		return -EFAULT;
	}
	npu_reg_dne1[0].shdw_reg = (REG_DNE1_T *)kzalloc(sizeof(REG_DNE1_T), GFP_KERNEL);

	npu_reg_mif0[0].hw_reg =
			(REG_DNE_MIF0_T *) ioremap(APB_DNE_MIF0_BASE, sizeof (REG_DNE_MIF0_T));
	if(!npu_reg_mif0[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("mif0 remap fail\n");
		return -EFAULT;
	}
	npu_reg_mif0[0].shdw_reg = (REG_DNE_MIF0_T *)kzalloc(sizeof(REG_DNE_MIF0_T), GFP_KERNEL);

	npu_reg_mif1[0].hw_reg =
			(REG_DNE_MIF1_T *) ioremap(APB_DNE_MIF1_BASE, sizeof (REG_DNE_MIF1_T));
	if(!npu_reg_mif1[0].hw_reg)
	{
	    _npu_hwc_all_clear();
		error("mif1 remap fail\n");
		return -EFAULT;
	}
	npu_reg_mif1[0].shdw_reg = (REG_DNE_MIF1_T *)kzalloc(sizeof(REG_DNE_MIF1_T), GFP_KERNEL);

    return 0;
}

/**
 * cleanup DNE module.
*/
void dne_hwc_crg_exit(void)
{
    noti("exit DNE CRG rigster\n");

    mutex_destroy(&_dne_device_lock);

    _npu_hwc_all_clear();

    return;
}
