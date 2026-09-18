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

#ifndef _SYS_IMPL_H
#define _SYS_IMPL_H

/*----------------------------------------------------------------------------------------
    Control Constants
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C"
{
#endif /* __cplusplus */

#include "os_util.h"
#include "sys_drv.h"
#include "sys_bwm.h"

/*----------------------------------------------------------------------------------------
    Constant Definitions
----------------------------------------------------------------------------------------*/
#define BWM_TEXT_MAX    16

/*----------------------------------------------------------------------------------------
    Macro Definitions
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------------------*/
struct bwm_ctx;

struct bwm_chip_drv
{
    void (*do_init)(void);
    void (*do_config)(struct bwm_ctx* ctx);
    void (*do_proc)(struct bwm_ctx* ctx, char* command, struct seq_file* m);
};

struct bwm_ctx
{
    struct
    {
        char input_src[BWM_TEXT_MAX];           // hdmi, ...., none
        LX_DIMENSION_T input_win;
        unsigned int input_rate;;

        char hdr_type[BWM_TEXT_MAX];
    }
    pqe;

    struct
    {
        int dummy; // future use
    }
    vdec;

    struct
    {
        int dummy; // future use
    }
    audio;

    struct
    {
        char tune[BWM_TEXT_MAX];
    }
    demod;

    struct
    {
        bool configured;
    }
    status;

    struct bwm_chip_drv chip_drv;
};

/*----------------------------------------------------------------------------------------
    Extern Function Prototype Declaration
----------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
    Extern Variables
----------------------------------------------------------------------------------------*/


#ifdef  __cplusplus
}
#endif /* __cplusplus */

#endif /* _SYS_DRV_H_ */

/** @} */
