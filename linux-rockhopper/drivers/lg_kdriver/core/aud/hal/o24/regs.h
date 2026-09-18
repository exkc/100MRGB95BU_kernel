/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2020 by LG Electronics Inc.
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
 *  interface header for audio registers
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

#ifndef _REGS_H_
#define _REGS_H_

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/init.h>
#include <linux/types.h>

#include "hal/reg_util.h"
#include "hal/o24/peri_ctrl_reg.h"
#include "hal/o24/dsp_ctrl_reg.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/
typedef struct {
    uint32_t ipc[0x440];
} IPC_REG;

struct aud_reg {
    PERI_CTRL_REG *PERI_CTRL;
    IPC_REG *IPC;
    DSP_CTRL_REG *DSP_CTRL;
};

struct aud_regs {
    struct aud_reg shdw;
    struct aud_reg phys;
};

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

#endif  /* _REGS_H_ */
