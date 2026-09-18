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
 *  audio ipc hal driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2021.02.09
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/kernel.h>

#include "logm.h"
#include "hal/o26/regs.h"
#include "hal/hal_ipc.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_hal_ipc,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_hal_ipc,fmt,##args)
#define info(fmt,args...)   logm_info(aud_hal_ipc,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_hal_ipc,fmt,##args)
#define error(fmt,args...)  logm_error(aud_hal_ipc,fmt,##args)

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
logm_define (aud_hal_ipc, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/

/*==============================================================================
    Implementation Group
==============================================================================*/

unsigned int aud_hal_ipc_read (unsigned int offset)
{
    return AUD_REG_Rd (IPC, ipc[offset / 4]);
}

void aud_hal_ipc_write (unsigned int offset, unsigned int value)
{
    AUD_REG_Wr (IPC, ipc[offset / 4], value);
}
