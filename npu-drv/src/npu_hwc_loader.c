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
 *  lg npu hw control loader
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2023.05.19
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/module.h>
#include <asm/io.h>

#include "base_types.h"
#include "os_util.h"
#include "logm.h"

#include "npu_drv.h"
#include "npu_hwc_dne.h"
#include "npu_hwc_lnx.h"
#include "npu_hwc_lnx_v2.h"
#include "npu_hwc_loader.h"
/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
logm_define (npu_hwc_mod, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static int _npu_hwc_wrap_init(struct npu_hw *hw);
static int _npu_hwc_wrap_reset(struct npu_hw *hw, unsigned int idx);
static int _npu_hwc_wrap_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param);
static int _npu_hwc_wrap_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param);
static int _npu_hwc_wrap_release(struct npu_hw *hw);
static int _npu_hwc_wrap_pmctrl(struct npu_hw *hw, bool is_suspended);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static unsigned int chip_info = 0x0;

static struct npu_hw _npu_hw = {
    .name = "0",
    .init = _npu_hwc_wrap_init,
    .reset = _npu_hwc_wrap_reset,
    .prepare = _npu_hwc_wrap_prepare,
    .run = _npu_hwc_wrap_run,
    .release = _npu_hwc_wrap_release,
    .pmctrl = _npu_hwc_wrap_pmctrl,
    .private = NULL,
};

/*==============================================================================
    Implementation Group
==============================================================================*/
static int _npu_hwc_wrap_init(struct npu_hw *hw)
{
    int ret = 0;
    info("[npu%s] %s", hw->name, __func__);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("[npu%s] %s (LNX)\n", hw->name, __func__);
            ret = lnx_v2_hwc_init(hw);
            if(!ret)
                ret = LX_CHIP_O26;
            break;

        case LX_CHIP_O24:
            debug("[npu%s] %s (LNX)\n", hw->name, __func__);
            ret = lnx_hwc_init(hw);
            if(!ret)
                ret = LX_CHIP_O24;
            break;

        case LX_CHIP_O22:
            debug("[npu%s] %s (DNE)\n", hw->name, __func__);
            ret = dne_hwc_init(hw);
            if(!ret)
                ret = LX_CHIP_O22;
            break;

        default:
            error("[npu%s] %s error\n", hw->name, __func__);
            return -1;
    }
    info("[npu%s] %s done\n", hw->name, __func__);

    return ret;
}

static int _npu_hwc_wrap_reset(struct npu_hw *hw, unsigned int idx)
{
    int ret = 0;
    info("[npu%s] %s[%d]", hw->name, __func__, idx);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_v2_hwc_reset(hw, idx);
            break;

        case LX_CHIP_O24:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_hwc_reset(hw, idx);
            break;

        case LX_CHIP_O22:
            debug("[npu%s] %s (DNE)\n", hw->name, __func__);
            ret = dne_hwc_reset(hw, idx);
            break;

        default:
            error("[npu%s] %s error\n", hw->name, __func__);
            return -1;
    }

    info("[npu%s] %s done\n", hw->name, __func__);

    return ret;
}

static int _npu_hwc_wrap_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param)
{
    int ret = 0;
    info("[npu%s] %s", hw->name, __func__);

    switch(chip_info)
    {
    case LX_CHIP_O26:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_v2_hwc_prepare(hw, idx, param);
            break;

        case LX_CHIP_O24:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_hwc_prepare(hw, idx, param);
            break;

        case LX_CHIP_O22:
            debug("[npu%s] %s (DNE)\n", hw->name, __func__);
            ret = dne_hwc_prepare(hw, idx, param);
            break;

        default:
            error("[npu%s] %s error\n", hw->name, __func__);
            return -1;
    }

    info("[npu%s] %s done\n", hw->name, __func__);

    return ret;
}

static int _npu_hwc_wrap_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param)
{
    int ret = 0;
    info("[npu%s] %s", hw->name, __func__);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_v2_hwc_run(hw, idx, param);
            break;

        case LX_CHIP_O24:
            debug("[npu%s] %s (LNX_%d)\n", hw->name, __func__, idx);
            ret = lnx_hwc_run(hw, idx, param);
            break;

        case LX_CHIP_O22:
            debug("[npu%s] %s (DNE)\n", hw->name, __func__);
            ret = dne_hwc_run(hw, idx, param);
            break;

        default:
            error("[npu%s] %s error\n", hw->name, __func__);
            return -1;
    }

    info("[npu%s] %s done\n", hw->name, __func__);

    return ret;
}

static int _npu_hwc_wrap_release(struct npu_hw *hw)
{
    int ret = 0;
    info("[npu%s] %s", hw->name, __func__);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("[npu%s] %s (LNX)\n", hw->name, __func__);
            ret = lnx_v2_hwc_release(hw);
            break;

        case LX_CHIP_O24:
            debug("[npu%s] %s (LNX)\n", hw->name, __func__);
            ret = lnx_hwc_release(hw);
            break;

        case LX_CHIP_O22:
            debug("[npu%s] %s (DNE)\n", hw->name, __func__);
            ret = dne_hwc_release(hw);
            break;

        default:
            error("[npu%s] %s error\n", hw->name, __func__);
            return -1;
    }

    info("[npu%s] %s done\n", hw->name, __func__);

    return ret;
}

static int _npu_hwc_wrap_pmctrl(struct npu_hw *hw, bool is_suspended)
{
    int ret = 0;
    info("[npu%s] %s:%d", hw->name, __func__, is_suspended);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("pmctrl NPU HWC LNX module\n");
            ret = lnx_v2_hwc_pmctrl(hw, is_suspended);
            break;

        case LX_CHIP_O24:
            debug("pmctrl NPU HWC LNX module\n");
            ret = lnx_hwc_pmctrl(hw, is_suspended);
            break;

        case LX_CHIP_O22:
            debug("pmctrl NPU HWC DNE module\n");
            ret = dne_hwc_pmctrl(hw, is_suspended);
            break;
    }

    return ret;
}

static void _npu_hwc_wrap_all_clear(void)
{
    info("%s\n", __func__);

    switch(chip_info)
    {
        case LX_CHIP_O26:
            debug("exit NPU HWC LNX module\n");
            lnx_v2_hwc_crg_exit();
            break;

        case LX_CHIP_O24:
            debug("exit NPU HWC LNX module\n");
            lnx_hwc_crg_exit();
            break;

        case LX_CHIP_O22:
            debug("exit NPU HWC DNE module\n");
            dne_hwc_crg_exit();
            break;
    }
}

/**
 * initialize npu module module.
*/
#ifdef USE_IOMMU
int npu_hwc_module_init(struct platform_device *pdev)
#else
int npu_hwc_module_init(void)
#endif
{
    chip_info = lx_chip();

    switch(chip_info)
    {
        case LX_CHIP_O26:
            noti("initialize NPU HWC(LNX) module\n");
            if(lnx_v2_hwc_crg_init())
                return -1;
            break;

        case LX_CHIP_O24:
            noti("initialize NPU HWC(LNX) module\n");
            if(lnx_hwc_crg_init())
                return -1;
            break;

        case LX_CHIP_O22:
            noti("initialize NPU HWC(DNE) module\n");
            if(dne_hwc_crg_init())
                return -1;
            break;
    }

#ifdef USE_IOMMU
    return npu_hw_register(pdev, &_npu_hw);
#else
    return npu_hw_register(&_npu_hw);
#endif
}


/**
 * cleanup npu hwc module.
*/
void npu_hwc_module_exit(void)
{
    noti("exit NPU HWC module\n");

    _npu_hwc_wrap_all_clear();

    return;
}
