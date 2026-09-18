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
 *  npu hw control (emulator)
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
#include <linux/timer.h>
#include <asm/io.h>

#include "proc_util.h"
#include "debug_util.h"

#include "logm.h"

#include "npu_drv.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace (npu_hwc_emul, fmt, ##args)
#define debug(fmt,args...)  logm_debug (npu_hwc_emul, fmt, ##args)
#define info(fmt,args...)   logm_info (npu_hwc_emul, fmt, ##args)
#define noti(fmt,args...)   logm_noti (npu_hwc_emul, fmt, ##args)
#define warn(fmt,args...)   logm_warning (npu_hwc_emul, fmt, ##args)
#define error(fmt,args...)  logm_error (npu_hwc_emul, fmt, ##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
struct timer_list work_timer;

struct npu_hw_intr
{
	unsigned int intr_en_set;
	unsigned int intr_clr;

};
struct npu_hw_work
{
    struct npu_hw_intr reg_intr;
    struct delayed_work work;
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
logm_define (npu_hwc_emul, log_level_debug);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _npu_hwc_module_init(void);
static void _npu_hwc_module_exit(void);
static int _npu_hwc_init(struct npu_hw *hw);
static int _npu_hwc_reset(struct npu_hw *hw, unsigned int idx);
static int _npu_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param);
static int _npu_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param);
static int _npu_hwc_release(struct npu_hw *hw);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static struct npu_hw_work _npu_hw_work;
static struct npu_hw _npu_hw = {
    .name = "emul",
    .init = _npu_hwc_init,
    .reset = _npu_hwc_reset,
    .prepare = _npu_hwc_prepare,
    .run = _npu_hwc_run,
    .release = _npu_hwc_release,
    .private = (void *) &_npu_hw_work,
};

/*==============================================================================
    Implementation Group
==============================================================================*/

static void npu_hw_emul(void)
{
    if (_npu_hw_work.reg_intr.intr_clr == 0x0)
    {
        _npu_hw_work.reg_intr.intr_clr = 0x1;
    }
}

static void work_timer_callback(struct timer_list *timer)
{
	debug("work_timer_callback called \n");
	npu_hw_emul();
}

static void _npu_ctrl_reset(void)
{
    _npu_hw_work.reg_intr.intr_clr = 0x0;
    info("ctrl_reset done\n");
}

static int _dne_set_init_param(struct npu_prepare_param *param)
{
    int i = 0;

    debug ("_dne_set_init_param\n");

    for(i=0; i<param->reg_num; i++)
    {
        debug("hwc_prepare->reg_info[%d] [0x%X:0x%X] \n", i, param->reg_info[i].address, param->reg_info[i].value);
    }

    return 0;
}

static void _npu_ctrl_init(void)
{
    _npu_hw_work.reg_intr.intr_en_set = 0x0;
    _npu_hw_work.reg_intr.intr_clr = 0x0;
    info("ctrl_init done\n");
}

static void _npu_ctrl_interrupt_enable(bool enable)
{
    if (enable)
    {
		_npu_hw_work.reg_intr.intr_en_set = 0x1;
    }
    else
    {
        _npu_hw_work.reg_intr.intr_en_set = 0x0;
    }
}

static bool _npu_ctrl_get_interrupt_status(void)
{
    if (_npu_hw_work.reg_intr.intr_clr == 0x1)
    {
        info("[_npu_ctrl_get_interrupt_status] interrupted!!!!\n");

        return true;
    }

    return false;
}

static void _npu_ctrl_clear_interrupt(void)
{
	_npu_hw_work.reg_intr.intr_clr = 0x0;
}

static void _npu_ctrl_set_program(phys_addr_t addr)
{
    info("Set Program : 0x%lx\n", addr);
}

static void _npu_ctrl_set_weight(phys_addr_t addr)
{
    info("Set Weight : 0x%lx\n", addr);
}

static void _npu_ctrl_set_feature(phys_addr_t addr)
{
    info("Set Feature : 0x%lx\n", addr);
}

static void _npu_ctrl_set_input(phys_addr_t addr)
{
    info("Set Input : 0x%lx\n", addr);
}

static void _npu_ctrl_set_output(phys_addr_t addr)
{
    info("Set Output : 0x%lx\n", addr);
}

static void _npu_ctrl_run_enable(bool enable)
{
    info("run enable [%d]\n", enable);
}

static void _npu_hwc_work(struct work_struct *work)
{
    struct npu_hw_work *npu_hw_work =
        container_of ((struct delayed_work *) work, struct npu_hw_work, work);

    trace("check done : %d\n", _npu_ctrl_get_interrupt_status());

    if(_npu_ctrl_get_interrupt_status())
    {
        _npu_ctrl_clear_interrupt();

        complete_all (&npu_hw_work->done);
    }
    else if(npu_hw_work->run_wait)
    {
        schedule_delayed_work(&npu_hw_work->work, msecs_to_jiffies (5));
    }
}

static int _npu_hwc_init(struct npu_hw *hw)
{
    info("[%s] init", hw->name);

    _npu_ctrl_reset();
    _npu_ctrl_init();
    _npu_ctrl_interrupt_enable(false);

    /* initialization */
    timer_setup(&work_timer, work_timer_callback, 0);

    info("[%s] init done\n", hw->name);

    return 0;
}

static int _npu_hwc_reset(struct npu_hw *hw, unsigned int idx)
{
    info("[%s] reset\n", hw->name);

    _npu_ctrl_reset();

    info("[%s] reset done\n", hw->name);

    return 0;
}

static int _npu_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param)
{
    int i, size, gap = 0;
    volatile UINT32 *reg_addr;

    debug ("[%s] prepare\n", hw->name);

    if(param->program.phys_addr)
        _npu_ctrl_set_program(param->program.phys_addr);
    else {
        error("[%s] prepare(program) fail\n", hw->name);
        return -1;
    }

    if(param->weight.phys_addr)
        _npu_ctrl_set_weight(param->weight.phys_addr);
    else {
        error("[%s] prepare(weight) fail\n", hw->name);
        return -1;
    }

    if(param->feature.phys_addr)
        _npu_ctrl_set_feature(param->feature.phys_addr);
    else {
        error("[%s] prepare(feature) fail\n", hw->name);
        return -1;
    }

    if(_dne_set_init_param(param) != 0) {
        error ("[%s] _dne_set_init_param() failed.\n", hw->name);
        return -1;
    }

    return 0;
}

static int _npu_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param)
{
    struct npu_hw_work *npu_hw_work = (struct npu_hw_work *) hw->private;

    info("[%s] run\n", hw->name);

    _npu_ctrl_set_input(param->input.phys_addr);
	_npu_ctrl_set_output(param->output.phys_addr);
    _npu_ctrl_run_enable(true);

    if(mod_timer(&work_timer, msecs_to_jiffies(30)))
    {
        error("mod_timer: Timer firing failed\n");
    }

    INIT_DELAYED_WORK(&npu_hw_work->work, _npu_hwc_work);
    init_completion(&npu_hw_work->done);
    npu_hw_work->run_wait = true;

    schedule_delayed_work(&npu_hw_work->work, msecs_to_jiffies (5));

    trace("[%s] wait complete\n", hw->name);

    if(wait_for_completion_interruptible_timeout(&npu_hw_work->done, msecs_to_jiffies (1000)) <= 0)
    {
        error("[%s] run fail\n", hw->name);

        npu_hw_work->run_wait = false;
        return -1;
    }

    debug("[%s] run done\n", hw->name);

    return 0;
}

static int _npu_hwc_release(struct npu_hw *hw)
{
    info ("[%s] release", hw->name);

    _npu_ctrl_reset();
    _npu_ctrl_interrupt_enable(true);

	del_timer(&work_timer);

    info("[%s] release done\n", hw->name);

    return 0;
}

/**
 * initialize pqe lne device.
*/
static int __init _npu_hwc_module_init(void)
{
    noti("initialize NPU HWC EMUL module\n");

    return npu_hw_register (&_npu_hw);
}

/**
 * cleanup pqe lne device.
*/
static void __exit _npu_hwc_module_exit(void)
{
    noti("exit NPU HWC EMUL module\n");

    return;
}

module_init (_npu_hwc_module_init);
module_exit (_npu_hwc_module_exit);

MODULE_AUTHOR ("LGE");
MODULE_DESCRIPTION ("LG NPU HW EMUL Control");
MODULE_LICENSE ("GPL");

