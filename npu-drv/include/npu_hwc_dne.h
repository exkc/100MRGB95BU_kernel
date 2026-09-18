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
 *  npu hwc dne header
 *
 *  author      Dongmin Kwon (dongmin.kwon@lge.com)
 *  version     0.1
 *  date        2023.05.19
 *
 */

#ifndef _NPU_HWC_DNE_H
#define _NPU_HWC_DNE_H

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

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/
int dne_hwc_crg_init(void);
void dne_hwc_crg_exit(void);

int dne_hwc_init(struct npu_hw *hw);
int dne_hwc_reset(struct npu_hw *hw, unsigned int idx);
int dne_hwc_prepare(struct npu_hw *hw, unsigned int idx, struct npu_prepare_param *param);
int dne_hwc_run(struct npu_hw *hw, unsigned int idx, struct npu_run_param *param);
int dne_hwc_release(struct npu_hw *hw);
int dne_hwc_pmctrl(struct npu_hw *hw, bool is_suspended);

#endif /* _NPU_HWC_DNE_H */
