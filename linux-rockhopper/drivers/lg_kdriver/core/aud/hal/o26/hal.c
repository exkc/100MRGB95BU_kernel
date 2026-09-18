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
 *  audio hal driver
 *
 *  author      Youngwoo Jin ( youngwoo.jin@lge.com )
 *  version     1.0
 *  date        2020.08.13
 *
 */

/*------------------------------------------------------------------------------
    Control Constants
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    File Inclusions
------------------------------------------------------------------------------*/
#include <linux/kernel.h>
#include <linux/delay.h>
#include "os_util.h"

#ifndef CHIP_TYPE_FPGA
#include "sys_regs.h"
#endif
#include "fwload_wov.h"
#include "logm.h"

#include "hal/hal.h"
#include "hal/hal_bc.h"
#include "hal/hal_clock.h"
#include "hal/hal_codec.h"
#include "hal/hal_output.h"
#include "hal/o26/regs.h"
#include "common/ipc_reg_offs.h"
#include "ipc_regs.h"
#include "dsp_control.h"
#include "hma_alloc.h"
#include "proc.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define PERI_CTRL_REG_BASE  (0xF2810000)
#define IPC_REG_BASE        (0xF2830000)
#define DSP_CTRL_REG_BASE   (0xF2820000)
#define EARC_PHY_REG_BASE   (0xC8750000)

#define NUMBER_OF_DSP       (3)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(ahal,fmt,##args)
#define debug(fmt,args...)  logm_debug(ahal,fmt,##args)
#define info(fmt,args...)   logm_info(ahal,fmt,##args)
#define noti(fmt,args...)   logm_noti(ahal,fmt,##args)
#define error(fmt,args...)  logm_error(ahal,fmt,##args)

/*------------------------------------------------------------------------------
    Type Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Function Prototype Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    External Variables
------------------------------------------------------------------------------*/
extern bool aud_disable_aad;

/*------------------------------------------------------------------------------
    global Variables
------------------------------------------------------------------------------*/
logm_define (ahal, log_level_noti);
struct aud_regs g_aud_regs;

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
static void _init (void);

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/

/*==============================================================================
    Implementation Group
==============================================================================*/

int aud_hal_initHW (void)
{
    int ret;

    _init ();

    ret = aud_hal_clock_init ();
    if (ret)
    {
        return ret;
    }

    ret = aud_hal_codec_init ();
    if (ret)
    {
        return ret;
    }

    ret = aud_hal_output_init_earc ();
    if (ret)
    {
        return ret;
    }

    ret = aud_hal_bc_init ();
    if (ret)
    {
        return ret;
    }

    return 0;
}

int aud_hal_init (void)
{
    int ret;

    ret = AUD_REG_INIT (PERI_CTRL, PERI_CTRL_REG_BASE);
    if (ret)
    {
        error ("register init fail PERI_CTRL_REG %p %p\n", AUD_REG_PHYS (PERI_CTRL),
            AUD_REG_SHDW (PERI_CTRL));

        AUD_REG_DEINIT (PERI_CTRL);
        return ret;
    }

    ret = AUD_REG_INIT (IPC, IPC_REG_BASE);
    if (ret)
    {
        error ("register init fail IPC_REG %p %p\n", AUD_REG_PHYS (IPC), AUD_REG_SHDW (IPC));

        AUD_REG_DEINIT (IPC);
        return ret;
    }

    ret = AUD_REG_INIT (DSP_CTRL, DSP_CTRL_REG_BASE);
    if (ret)
    {
        error ("register init fail DSP_CTRL_REG %p %p\n", AUD_REG_PHYS (DSP_CTRL),
            AUD_REG_SHDW (DSP_CTRL));

        AUD_REG_DEINIT (DSP_CTRL);
        return ret;
    }

    ret = AUD_REG_INIT (EARC_PHY, EARC_PHY_REG_BASE);
    if (ret)
    {
        error ("register init fail DSP_CTRL_REG %p %p\n", AUD_REG_PHYS (EARC_PHY),
            AUD_REG_SHDW (EARC_PHY));

        AUD_REG_DEINIT (EARC_PHY);
        return ret;
    }

    ret = aud_hal_output_init ();
    if (ret)
    {
        return ret;
    }

    aud_hal_initHW ();

    return 0;
}

void aud_hal_exit (void)
{
    AUD_REG_Wr (PERI_CTRL, aud_int0_en, 0);
    AUD_REG_Wr (PERI_CTRL, aud_int1_en, 0);
    AUD_REG_Wr (PERI_CTRL, aud_int2_en, 0);
    AUD_REG_Wr (PERI_CTRL, aud_int3_en, 0);
#if 0
    aud_hal_bc_exit ();
    aud_hal_clock_exit ();
    aud_hal_codec_exit ();
    aud_hal_output_exit ();

    AUD_REG_DEINIT (IPC);
    AUD_REG_DEINIT (PERI_CTRL);
    AUD_REG_DEINIT (DSP_CTRL);
#endif
}

int aud_hal_get_number_of_dsp (void)
{
    return NUM_OF_DSP;
}

bool aud_hal_is_soundbar (void)
{
#ifdef SUPPORT_SOUNDBAR
    return true;
#else
    return false;
#endif
}

bool aud_hal_dts_supported (void)
{
    return true;
}

struct area
{
    const char *name;
    int size;
    phys_addr_t _start;         /* physical address */
    unsigned int start;         /* physical address */
};

static void _aud_hal_swap_area (struct area *a, struct area *b)
{
    struct area temp = *a;
    *a = *b;
    *b = temp;
}

static void _aud_hal_sort_hma_area (struct area areas[], int n_areas)
{
    int i, j;
    for (i = 0; i < n_areas - 1; i++)
    {
        for (j = 0; j < n_areas - i - 1; j++)
        {
            if (areas[j].start > areas[j + 1].start)
                _aud_hal_swap_area (&areas[j], &areas[j + 1]);
        }
    }
}

int aud_hal_set_axi_gk (void)
{
    int i, ret, n_array;

    struct area areas[] = {
        /* *INDENT-OFF* */
        { "base", .start = 0},              // 0
        { "audio_lnx", },
#if defined(CHIP_TYPE_FPGA)
        { "audio_buffer0", },
#else
        { "audio_s_mem", },
        { "audio_ns_mem", },
        { "debug0", },
#endif
        { "end", .start = 0xFFFFFFFF},      // ~ LAST
        /* *INDENT-ON* */
    };

    // end is not include..
    n_array = ARRAY_SIZE (areas) - 1;

    // get hma info
    for (i = 1; i < n_array; i++)
    {
        struct area *a = areas + i;

        ret = hma_pool_info (a->name, &a->_start, &a->size);
        if (ret == 0 && a->_start && a->size)
        {
            a->start = (unsigned int) a->_start;
            noti ("%s\t0x%x\t0x%x\n", a->name, a->start, a->size);
        }
        else
        {
            error ("no mem for %s\n", a->name);
            return -1;
        }
    }

    // sort by start address
    _aud_hal_sort_hma_area (areas, n_array);

    // set area into axi gate keeper
    for (i = 0; i < n_array; i++)
    {
        unsigned int s, e;

        // start address
        s = areas[i].start + areas[i].size;

        // end address
        e = areas[i + 1].start - 1;

        noti ("axi_gk_set_range %08x %08x 1", s, e);

        if (s < e)
            aud_call_funcs (3, "axi_gk_set_range %x %x 1", s, e);
    }

    return 0;
}

aud_bus_addr_t aud_hal_phys_to_aud_bus (phys_addr_t address)
{
#ifndef CHIP_TYPE_FPGA
    return fwloadwov_wovbus_addr (address);
#else
    return address;
#endif
}

int aud_hal_set_adc_port_number (unsigned int number)
{
    return aud_hal_codec_set_adc_port_number (number);
}

unsigned int aud_hal_get_dsp_pc (unsigned int dsp_num)
{
    unsigned int pc = 0;

    switch (dsp_num)
    {
        case 0:
            pc = AUD_REG_Rd (DSP_CTRL, dsp0_debugpc);
            break;

        case 1:
            pc = AUD_REG_Rd (DSP_CTRL, dsp1_pdebugpc);
            break;

        case 2:
            pc = AUD_REG_Rd (DSP_CTRL, dsp2_pdebugpc);
            break;

        case 3:
            pc = AUD_REG_Rd (DSP_CTRL, dsp3_pdebugpc);
            break;

        default:
            break;
    }

    return pc;
}

unsigned int aud_hal_get_gstc (void)
{
    unsigned int gstc = 0;

    gstc = AUD_REG_RdFL (PERI_CTRL, aud_gstcc0lreg);

    trace ("gstc = 0x%04x\n", gstc);
    return gstc;
}

EXPORT_SYMBOL (aud_hal_get_gstc);

bool aud_hal_secure_loading_supported (void)
{
    return true;
}

unsigned long long aud_hal_get_gstc_33bits (void)
{
    unsigned int gstch = 0;
    unsigned int gstcl = 0;
    unsigned long long gstc = 0;

    gstcl = AUD_REG_RdFL (PERI_CTRL, aud_gstcc0lreg);
    gstch = AUD_REG_RdFL (PERI_CTRL, aud_gstcc0hreg);
    gstc = ((unsigned long long) gstch << 32) + (unsigned long long) gstcl;

    trace ("gstc = 0x%llx\n", gstc);
    return gstc;
}

static void _init (void)
{
    noti ("reset & init hardware.\n");

#ifndef CHIP_TYPE_FPGA
    //SPK I2S enable
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_daclrch_mux_sel, 0x2);
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc65);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_daclrck_mux_sel, 0x2);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_dacsck_mux_sel, 0x2);
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc65);
#endif
    AUD_REG_Wr (PERI_CTRL, aud_gstccenable, 0);

    /* release reset aud */
    info ("release audio reset\n");

    /* release all SWRESET except dsp */
    AUD_REG_RdFL (PERI_CTRL, aud_swreset);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp3dreset, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp2dreset, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp3bresetout, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp3ocdresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp2bresetout, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp2ocdresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aad_i2s_resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aad_tresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp1dreset, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp0dreset, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, hmr3spdifresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, hmr2spdifresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, hmr1spdifresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, hmr0spdifresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aadferesetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aadapbresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aadresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp1bresetout, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp0bresetout, 0);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp1ocdresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, dsp0ocdresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs26resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs25resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs24resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs23resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs21resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs20resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, fs22resetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aversetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, apbresetout, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_swreset, aresetout, 1);
    AUD_REG_WrFL (PERI_CTRL, aud_swreset);

    AUD_REG_RdFL (PERI_CTRL, aud_gstccenable);
    AUD_REG_WrFd (PERI_CTRL, aud_gstccenable, gstcc0_enable, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_gstccenable, gstcc1_enable, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_gstccenable, gstcc2_enable, 1);
    AUD_REG_WrFd (PERI_CTRL, aud_gstccenable, gstcc3_enable, 1);
    AUD_REG_WrFL (PERI_CTRL, aud_gstccenable);

    noti ("done.\n");
}
