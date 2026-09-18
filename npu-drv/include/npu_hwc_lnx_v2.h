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
 *  npu hwc lnx header
 */

#ifndef _NPU_HWC_LNX_V2_H
#define _NPU_HWC_LNX_V2_H

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/types.h>
/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
#ifndef LX_CHIP_O26 // TODO: remove
#define LX_CHIP_O26						0x29
#endif
/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
int lnx_v2_hwc_crg_init(void);
void lnx_v2_hwc_crg_exit(void);

int lnx_v2_hwc_init(struct npu_hw *hw);
int lnx_v2_hwc_reset(struct npu_hw *hw, unsigned int idx);
int lnx_v2_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param);
int lnx_v2_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param);
int lnx_v2_hwc_release(struct npu_hw *hw);
int lnx_v2_hwc_pmctrl(struct npu_hw *hw, bool is_suspended);

#endif /* _NPU_HWC_LNX_V2_H */
