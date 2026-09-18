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
 *  audio output hal driver
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

#ifndef CHIP_TYPE_FPGA
#include "sys_regs.h"
#endif
#include "os_util.h"
#include "logm.h"

#include "hal/reg_util.h"
#include "hal/hal_output.h"
#include "hal/m23/regs.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_hal_output,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_hal_output,fmt,##args)
#define info(fmt,args...)   logm_info(aud_hal_output,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_hal_output,fmt,##args)
#define error(fmt,args...)  logm_error(aud_hal_output,fmt,##args)

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
logm_define (aud_hal_output, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
#ifndef CHIP_TYPE_FPGA
#define EARC_LINK0_REG_BASE          0xC47D3900
#define EARC_LINK0_REG_SIZE          0x100

#define EARC_LINK_REG_BASE          0xC47D4000
#define EARC_LINK_REG_SIZE          0x1000

#define EARC_INT_REG_BASE           0xC47D5300
#define EARC_INT_REG_SIZE           0x1000

#define EARC_PHY_REG_BASE           0xC4B40000
#define EARC_PHY_REG_SIZE           0x1000

static volatile unsigned int *earc_link_reg;
static volatile unsigned int *earc_link0_reg;
static volatile unsigned int *earc_int_reg;
static volatile unsigned int *earc_phy_reg;

#define EARC_LINK0_RD(offset)             *(volatile unsigned int *)((void *)earc_link0_reg + offset)
#define EARC_LINK0_WR(offset,value)       EARC_LINK0_RD(offset) = (value)
#define EARC_LINK_RD(offset)             *(volatile unsigned int *)((void *)earc_link_reg + offset)
#define EARC_LINK_WR(offset,value)       EARC_LINK_RD(offset) = (value)
#define EARC_INT_RD(offset)             *(volatile unsigned int *)((void *)earc_int_reg + offset)
#define EARC_INT_WR(offset,value)       EARC_INT_RD(offset) = (value)
#define EARC_PHY_RD(offset)              *(volatile unsigned int *)((void *)earc_phy_reg + offset)
#define EARC_PHY_WR(offset,value)        EARC_PHY_RD(offset) = (value)

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/
static bool gAudHalEarcOn = false;
static unsigned int gEarcIec958csd0 = 0x00000000;
static unsigned int gEarcIec958csd1 = 0x00000000;
static unsigned int gEarcIec958csd4 = 0x00000000;
static unsigned int gEarcDmacConfig0 = 0x00008010;      // I2S 24bits, SPDIF IF(up to 8 ch)
static unsigned int gEarcDmacConfig1 = 0x00010001;      // phy differential driver enable, phy biphase clock enable
static unsigned int gEarcPllBpClk = 0x60;
static unsigned int gEarcOutputFormat = 0;
static unsigned int gEarcOutputSamplingFreq = 48000;
static unsigned int gEarcChannel = 2;
static unsigned int gEarcAcmod = 2;

static int audio_compressed_layout = 0; // 0:compressed layout A, 1:compressed layout B
module_param (audio_compressed_layout, int, 0644);
#endif

/*==============================================================================
    Implementation Group
==============================================================================*/
#ifdef CHIP_TYPE_FPGA
int aud_hal_output_init (void)
{
    return 0;
}

void aud_hal_output_exit (void)
{
}

void aud_hal_output_set_number_of_i2s (int number)
{
}

int aud_hal_output_optic_light_on (bool on)
{
    AUD_REG_RdFL (PERI_CTRL, aud_spdifout_sel);
    AUD_REG_WrFd (PERI_CTRL, aud_spdifout_sel, spdifoutsel_dsp, on << 1);
    AUD_REG_WrFL (PERI_CTRL, aud_spdifout_sel);

    noti ("onptic light %d.\n", on);
    return 0;
}

void audio_hal_earc_set_on (bool on)
{
}

void audio_hal_earc_set_scms (unsigned int scms)
{
}

void audio_hal_earc_set_category_code (unsigned int category_code)
{
}

void audio_hal_earc_set_output_format (enum audio_hal_output_format output_format,
    unsigned int sampling_freq)
{
}

void audio_hal_earc_set_mute (bool on)
{
}

void audio_hal_earc_set_audio_mode (unsigned int audio_mode)
{
}

void audio_hal_earc_set_channel (unsigned int channel, unsigned int acmod)
{
}

void audio_hal_earc_clear_interrupt (unsigned int int_status)
{
}

void audio_hal_spdif_start (bool on)
{
}

void audio_hal_hp_start (bool on)
{
}

int aud_hal_output_init_earc (void)
{
    return 0;
}

void audio_hal_arc_start (bool on)
{
}

void audio_hal_speaker_start (bool on)
{
}

#else
static irqreturn_t audio_hal_earc_irq (int num, void *arg)
{
    unsigned int status = 0;

    /* Get ISR Status */
    status = EARC_INT_RD (0x000);

    if (!status)
    {
        error ("earc int status : %08x\n", status);
        return IRQ_NONE;
    }
    status &= 0x7;

    /* Clear ISR */
    EARC_INT_WR (0x008, status);

    audio_hal_earc_clear_interrupt (status);

    return IRQ_HANDLED;
}

int aud_hal_output_init_earc (void)
{
    unsigned int earc_user_pdb = 0;

    earc_user_pdb = EARC_PHY_RD (0x004);
    if (earc_user_pdb != 0x11)
    {
        EARC_PHY_WR (0x004, 0x00);      // USER_PDB, USER_APHY_DMAC_DRV_8PHASE_EN
        EARC_PHY_WR (0x004, 0x11);      // USER_PDB, USER_APHY_DMAC_DRV_8PHASE_EN

        noti ("earc_user_pdb : %x\n", earc_user_pdb);
    }

    noti ("set registers for earc is complete\n");
    return 0;
}

int aud_hal_output_init (void)
{
    int ret;

    earc_link_reg = (volatile unsigned int *) ioremap (EARC_LINK_REG_BASE, EARC_LINK_REG_SIZE);
    if (!earc_link_reg)
    {
        error ("earc_link_reg is not ioremaped.\n");
        return -EIO;
    }

    earc_link0_reg = (volatile unsigned int *) ioremap (EARC_LINK0_REG_BASE, EARC_LINK0_REG_SIZE);
    if (!earc_link0_reg)
    {
        error ("earc_link0_reg is not ioremaped.\n");
        return -EIO;
    }

    earc_int_reg = (volatile unsigned int *) ioremap (EARC_INT_REG_BASE, EARC_INT_REG_SIZE);
    if (!earc_int_reg)
    {
        error ("earc_int_reg is not ioremaped.\n");
        return -EIO;
    }

    earc_phy_reg = (volatile unsigned int *) ioremap (EARC_PHY_REG_BASE, EARC_PHY_REG_SIZE);
    if (!earc_phy_reg)
    {
        error ("earc_phy_reg is not ioremaped.\n");
        return -EIO;
    }

    aud_hal_output_init_earc ();

    ret =
        request_irq (M23_IRQ_INTR_HDMIRX_PRT2_EARC_CPU, audio_hal_earc_irq, IRQF_TRIGGER_NONE,
        "eARC", NULL);
    if (ret < 0)
        error ("request_irq() failed for eARC\n");
    noti ("ioremap is complete for earc.\n");
    return 0;
}

void aud_hal_output_exit (void)
{
    free_irq (M23_IRQ_INTR_HDMIRX_PRT2_EARC_CPU, NULL);

    if (earc_link_reg)
    {
        iounmap (earc_link_reg);
        earc_link_reg = NULL;
    }

    if (earc_link0_reg)
    {
        iounmap (earc_link0_reg);
        earc_link0_reg = NULL;
    }

    if (earc_int_reg)
    {
        iounmap (earc_int_reg);
        earc_int_reg = NULL;
    }

    if (earc_phy_reg)
    {
        iounmap (earc_phy_reg);
        earc_phy_reg = NULL;
    }
    noti ("iounmap is complete for earc.\n");
}

void aud_hal_output_set_number_of_i2s (int number)
{
    if (number >= 1)
    {
        CTOP_CTRL_M23Ax_RdFL (IOMUX_CTRL_VD1, pad_vd166);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrck_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_dacsck_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrch_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_WrFL (IOMUX_CTRL_VD1, pad_vd166);
    }

    if (number >= 2)
    {
        CTOP_CTRL_M23Ax_RdFL (IOMUX_CTRL_VD1, pad_vd166);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_dacslrch_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_WrFL (IOMUX_CTRL_VD1, pad_vd166);
    }

    if (number == 0)
    {
        AUD_REG_RdFL (PERI_CTRL, ocma);
        AUD_REG_WrFd (PERI_CTRL, ocma, dack_mask, 0);
        AUD_REG_WrFL (PERI_CTRL, ocma);
    }
    else
    {
        AUD_REG_RdFL (PERI_CTRL, ocma);
        AUD_REG_WrFd (PERI_CTRL, ocma, dack_mask, 1);
        AUD_REG_WrFL (PERI_CTRL, ocma);
    }

    noti ("M23 I2S Number(%d)\n", number);
}

int aud_hal_output_optic_light_on (bool on)
{
    AUD_REG_RdFL (PERI_CTRL, aud_spdifout_sel);
    AUD_REG_WrFd (PERI_CTRL, aud_spdifout_sel, spdifoutsel_dsp, on << 1);
    AUD_REG_WrFL (PERI_CTRL, aud_spdifout_sel);

    noti ("onptic light %d.\n", on);
    return 0;
}

static void audio_hal_earc_monitor_lock (void)
{
    int frpll_lock = 0, earc_phy_lock = 0;
    signed long jiffies_start = jiffies;
    int count = 0;

    do
    {
        CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_02);
        CTOP_CTRL_M23Ax_Rd01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_lock, frpll_lock);
        earc_phy_lock = EARC_PHY_RD (0x05C);
        earc_phy_lock &= 0x10;
        if (frpll_lock && !earc_phy_lock)
        {
            EARC_PHY_WR (0x054, 0x12);  // BPCLOCK_EN low
            usleep_range (200, 200);
            EARC_PHY_WR (0x054, 0x10);  // BPCLOCK_EN link control
        }
        else
        {
            if (frpll_lock && earc_phy_lock)
                break;
        }
        count++;
        usleep_range (100, 100);
    }
    while (jiffies_to_msecs (jiffies - jiffies_start) < 100);

    if (!frpll_lock || !earc_phy_lock)
        error ("[%d] frpll_lock:%x, earc_phy_lock:%x\n", count, frpll_lock, earc_phy_lock);
    else
        info ("[%d] frpll_lock:%x, earc_phy_lock:%x\n", count, frpll_lock, earc_phy_lock);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void audio_hal_earc_sending_differential_signal (struct timer_list *unused)
{
    EARC_PHY_WR (0x05C, 0x00);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 0 : controlled by link
    //EARC_PHY_WR (0x058, 0x30);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    debug ("Start Sending.\n");
}

static DEFINE_TIMER (_gHoldingTimer, audio_hal_earc_sending_differential_signal);
#else
static void audio_hal_earc_sending_differential_signal (unsigned long arg)
{
    EARC_PHY_WR (0x05C, 0x00);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 0 : controlled by link
    //EARC_PHY_WR (0x058, 0x30);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    debug ("Start Sending.\n");
}

static DEFINE_TIMER (_gHoldingTimer, audio_hal_earc_sending_differential_signal, 0, 0);
#endif

static void audio_hal_earc_holding_differential_signal (void)
{
    /* holding time more than 100ms */
    EARC_PHY_WR (0x05C, 0x02);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 2 : force to low
    //EARC_PHY_WR (0x058, 0x32);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    mod_timer (&_gHoldingTimer, jiffies + msecs_to_jiffies (150));
    debug ("Stop Sending.\n");
}

// for SONY eARC devices compatibiltiy
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void audio_hal_earc_holding_noise_signal (struct timer_list *unused)
{
    EARC_PHY_WR (0x05C, 0x00);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 0 : controlled by link
    EARC_PHY_WR (0x058, 0x30);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    debug ("Start Sending.\n");
}

static DEFINE_TIMER (_gNoiseTimer, audio_hal_earc_holding_noise_signal);
#else
static void audio_hal_earc_holding_noise_signal (unsigned long arg)
{
    EARC_PHY_WR (0x05C, 0x00);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 0 : controlled by link
    EARC_PHY_WR (0x058, 0x30);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    debug ("Start Sending.\n");
}

static DEFINE_TIMER (_gNoiseTimer, audio_hal_earc_holding_noise_signal, 0, 0);
#endif

static void audio_hal_earc_sending_noise_signal (void)
{
    /* holding time more than 100ms */
    EARC_PHY_WR (0x05C, 0x00);  // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE : 2 : force to low
    EARC_PHY_WR (0x058, 0x32);  // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE
    mod_timer (&_gNoiseTimer, jiffies + msecs_to_jiffies (150));
    debug ("Stop Sending.\n");
}

void audio_hal_earc_set_on (bool on)
{
    if (on == ON)
    {
        if (lx_chip_rev () >= LX_CHIP_REV (O20, B0))
            EARC_PHY_WR (0x008, 0x43);  // DMAC Driver Current Control (default : 0x43)
        else
            EARC_PHY_WR (0x008, 0x63);  // DMAC Driver Current Control (default : 0x43)

        EARC_PHY_WR (0x06C, 0x00);
        //EARC_PHY_WR (0x05C, 0x02);      // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE /
        EARC_PHY_WR (0x004, 0x11);
        EARC_PHY_WR (0x04C, 0x00);
        //EARC_PHY_WR (0x010, 0xC5);      // ODT(ARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
        EARC_PHY_WR (0x014, 0x00);
        EARC_PHY_WR (0x030, gEarcPllBpClk);

        EARC_PHY_WR (0x150, 0x03);      // DMAC Slew Control
        //EARC_PHY_WR (0x05C, 0x00);      // MONITOR_DMAC_BIPHASE_CLK_UP USER_DMAC_DRV_EN_FORCE /

        EARC_LINK0_WR (0x000, gEarcIec958csd0);
        EARC_LINK0_WR (0x004, gEarcIec958csd1);
        EARC_LINK0_WR (0x008, 0x00000000);
        EARC_LINK0_WR (0x00C, 0x00000000);
        EARC_LINK0_WR (0x010, gEarcIec958csd4);
        EARC_LINK0_WR (0x014, 0x00000000);

        EARC_LINK_WR (0x010, gEarcIec958csd0);
        EARC_LINK_WR (0x014, gEarcIec958csd1);
        EARC_LINK_WR (0x018, 0x00000000);
        EARC_LINK_WR (0x01C, 0x00000000);
        EARC_LINK_WR (0x020, gEarcIec958csd4);
        EARC_LINK_WR (0x024, 0x00000000);

        EARC_LINK_WR (0x004, gEarcDmacConfig0);
        EARC_LINK_WR (0x008, gEarcDmacConfig1);
        EARC_LINK_WR (0x00C, 0x00000000);       // dmac audio data off fifo reset ??
        EARC_LINK_WR (0x00C, 0x00000001);

        //EARC_PHY_WR (0x010, 0xC5);       // ODT(ARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
        //EARC_PHY_WR (0x040, 0x01);
    }
    else
    {
        EARC_LINK_WR (0x004, gEarcDmacConfig0);
        EARC_LINK_WR (0x008, gEarcDmacConfig1);
        EARC_LINK_WR (0x00C, 0x00000000);       // dmac audio data en

        EARC_PHY_WR (0x008, 0x43);      // DMAC Driver Current Control (default : 0x43)
        //EARC_PHY_WR (0x010, 0xB1);       // ODT(ARC MODE), PLL_AUTO_RSTB_OFF,PLL_RSTB
        //EARC_PHY_WR (0x040, 0x02);       // USER_EARC_ARC_SEL(0:earc 2:arc)
    }

    {
        EARC_PHY_WR (0x034, 0x01);      // USER_HDMI_AUD_CLK_SEL(1:extern)
        EARC_PHY_WR (0x038, 0x2f);      // USER_AUD_SPDIF_DATA_SEL(1:aoc 2:extern) USER_AUD_EXTERN_SPDIF_DATA_CTRL
        EARC_PHY_WR (0x03C, 0x2f);      // USER_AUD_I2S_DATA_SEL(1:aoc 2:extern) USER_AUD_EXTERN_I2S_DATA_CTRL

        EARC_PHY_WR (0x050, 0x00);      // USER_DMAC_BP_MODE USER_DMAC_FEM_IN_SE
        //EARC_PHY_WR (0x054, 0x10);      // USER_DMAC_FEM_MODE  USER_DMAC_BIPHASE_PHY_CLK_EN_FORCE
        EARC_PHY_WR (0x058, 0x30);      // USER_DMAC_PHY_CLK_UP_WAIT  USER_DMAC_BIPHASE_PHY_CLK_UP_FORCE

        audio_hal_earc_monitor_lock ();
    }

    // Set eARC TX Interrupt Mask.
    {
        unsigned int earcIntMask = 0;

        earcIntMask = EARC_INT_RD (0x004);

        if (on == ON)
            earcIntMask |= 0x7;
        else
            earcIntMask &= ~(0x7);

        EARC_INT_WR (0x004, earcIntMask);
    }

    // for SONY eARC devices compatibiltiy eARC Off -> On
    if ((gAudHalEarcOn == OFF) && (on == ON))
        audio_hal_earc_sending_noise_signal ();
    else
        audio_hal_earc_holding_differential_signal ();

    gAudHalEarcOn = on;

    noti ("eARC On : %d\n", on);

    return;
}

void audio_hal_earc_set_scms (unsigned int scms)
{
    unsigned int iec958csd0;

    iec958csd0 = gEarcIec958csd0;

    // bit 2 : CP-bit
    // bit 15 : L-bit
    if (scms == 0)              //copy free
    {
        iec958csd0 |= (0x1 << 2);       // set bit 2 (CP)
        iec958csd0 &= ~(0x1 << 15);     // clear bit 15 (L)
    }
    else if (scms == 2)         //copy once
    {
        iec958csd0 &= ~(0x1 << 2);      // clear bit 2
        iec958csd0 &= ~(0x1 << 15);     // clear bit 15 (L)
    }
    else if (scms == 3 || scms == 1)    //copy no more copy never
    {
        iec958csd0 &= ~(0x1 << 2);      // clear bit 2
        iec958csd0 |= (0x1 << 15);      // set bit 15 (L)
    }

    EARC_LINK0_WR (0x000, iec958csd0);
    EARC_LINK_WR (0x010, iec958csd0);
    EARC_LINK0_WR (0x014, 0x0);
    EARC_LINK_WR (0x024, 0x0);

    gEarcIec958csd0 = iec958csd0;

    info ("eARC SCMS : 0x%x\n", scms);
}

void audio_hal_earc_set_category_code (unsigned int category_code)
{
    unsigned int iec958csd0;

    iec958csd0 = gEarcIec958csd0;
    iec958csd0 &= ~(0xFF << 8);
    iec958csd0 |= ((category_code & 0xFF) << 8);
    EARC_LINK0_WR (0x000, iec958csd0);
    EARC_LINK_WR (0x010, iec958csd0);
    EARC_LINK0_WR (0x014, 0x0);
    EARC_LINK_WR (0x024, 0x0);
    gEarcIec958csd0 = iec958csd0;

    info ("eARC category_code : 0x%x\n", category_code);
}

static void audio_hal_earc_set_pll_bp_clock (unsigned int sampling_freq)
{
    unsigned int earc_pll_bp_clk = 0;

    earc_pll_bp_clk = EARC_PHY_RD (0x030);
    earc_pll_bp_clk &= ~(0xF << 4);
    if (sampling_freq == 32000)
        earc_pll_bp_clk |= (0x0 << 4);
    else if (sampling_freq == 64000)
        earc_pll_bp_clk |= (0x1 << 4);
    else if (sampling_freq == 128000)
        earc_pll_bp_clk |= (0x2 << 4);
    else if (sampling_freq == 44100)
        earc_pll_bp_clk |= (0x3 << 4);
    else if (sampling_freq == 88200)
        earc_pll_bp_clk |= (0x4 << 4);
    else if (sampling_freq == 176400)
        earc_pll_bp_clk |= (0x5 << 4);
    else if (sampling_freq == 48000)
        earc_pll_bp_clk |= (0x6 << 4);
    else if (sampling_freq == 96000)
        earc_pll_bp_clk |= (0x7 << 4);
    else if (sampling_freq == 192000)
        earc_pll_bp_clk |= (0x8 << 4);
    else
    {
        error ("sampling freq(%d) is invalid.\n", sampling_freq);
        earc_pll_bp_clk |= (0x6 << 4);
        sampling_freq = 48000;
    }
    EARC_PHY_WR (0x030, earc_pll_bp_clk);
    gEarcPllBpClk = earc_pll_bp_clk;
}

static unsigned int audio_hal_earc_get_dmac_sampling_bit (unsigned int sampling_freq)
{
    unsigned int sampling_bit = 0;

    switch (sampling_freq)
    {
        case 32000:
            sampling_bit = 0x0;
            break;
        case 44100:
            sampling_bit = 0x1;
            break;
        case 48000:
            sampling_bit = 0x2;
            break;
        case 64000:
            sampling_bit = 0x3;
            break;
        case 88200:
            sampling_bit = 0x8;
            break;
        case 96000:
            sampling_bit = 0x9;
            break;
        case 128000:
            sampling_bit = 0xa;
            break;
        case 176400:
            sampling_bit = 0xb;
            break;
        case 192000:
            sampling_bit = 0xc;
            break;
        default:
            sampling_bit = 0x2;
            break;
    }

    return sampling_bit;
}

/*
   refer to HDMISpecification2.1-final.pdf
   9.2 Supported Audio Rates
   Table 9-2:Allowed Values for channel status bit 24 to 27, 30, and 31
*/
static unsigned int audio_hal_earc_get_sampling_bit (unsigned int sampling_freq)
{
    unsigned int sampling_bit = 0;

    if (audio_compressed_layout == 1)
        sampling_freq *= 4;
    else
    {
        if ((gEarcChannel == 8) || (gEarcChannel == 6))
            sampling_freq *= 4;
    }

    switch (sampling_freq)
    {
        case 32000:
            sampling_bit = 0x3;
            break;
        case 64000:
            sampling_bit = 0xb;
            break;
        case 128000:
            sampling_bit = 0x8b;
            break;
        case 256000:
            sampling_bit = 0x4b;
            break;
        case 512000:
            sampling_bit = 0xcb;
            break;
        case 1024000:
            sampling_bit = 0xc5;
            break;
        case 22050:
            sampling_bit = 0x4;
            break;
        case 44100:
            sampling_bit = 0x0;
            break;
        case 88200:
            sampling_bit = 0x8;
            break;
        case 176400:
            sampling_bit = 0xc;
            break;
        case 352800:
            sampling_bit = 0xd;
            break;
        case 705600:
            sampling_bit = 0x8d;
            break;
        case 1411200:
            sampling_bit = 0x4d;
            break;
        case 24000:
            sampling_bit = 0x6;
            break;
        case 48000:
            sampling_bit = 0x2;
            break;
        case 96000:
            sampling_bit = 0xa;
            break;
        case 192000:
            sampling_bit = 0xe;
            break;
        case 384000:
            sampling_bit = 0x5;
            break;
        case 768000:
            sampling_bit = 0x9;
            break;
        case 1536000:
            sampling_bit = 0x45;
            break;
        default:
            sampling_bit = 0x2;
            break;
    }

    return sampling_bit;
}

static void audio_hal_earc_set_es_mode (unsigned int sampling_freq)
{
    unsigned int sampling_bit = 0;
    unsigned int iec958csd0 = 0;
    unsigned int iec958csd1 = 0;
    unsigned int iec958csd4 = 0;
    unsigned int earc_dmac_config0 = 0;
    unsigned int earc_dmac_config1 = 0;
#if 0
    unsigned int earc_pll_bp_clk = 0;
#endif
    // Disable eARC TX DMAC audio datapath.
    EARC_LINK_WR (0x00C, 0x0);

    // Config eARC TX DMAC audio mode
    earc_dmac_config0 = gEarcDmacConfig0;
    earc_dmac_config0 |= 1 << 28;
    //earc_dmac_config0 |= 1 << 25;
    //earc_dmac_config0 |= 1 << 24;
    //earc_dmac_config0 |= 1 << 20;
    //earc_dmac_config0 |= 1 << 16;
    earc_dmac_config0 &= ~(1 << 8);     // EARCTX_DMAC_AUDIO_SOURCE_LAYOUT_QST
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
        earc_dmac_config0 |= (1 << 8);  // 0:2-channel, 1:8-Channel
    earc_dmac_config0 &= ~(7);  // EARCTX_DMAC_AUDIO_MODE_QST   0:2-channel L-PCM, 6:Compressed Layout A, 7:Compressed Layout B
    if (audio_compressed_layout == 1)
    {
        earc_dmac_config0 |= 1 << 8;    // audio source layout 0 : 2-channel, 1 : 8-channel
        earc_dmac_config0 |= 7; // compressed layout B
    }
    else
        earc_dmac_config0 |= 6; // compressed layout A
    EARC_LINK_WR (0x004, earc_dmac_config0);
    gEarcDmacConfig0 = earc_dmac_config0;

    earc_dmac_config1 = gEarcDmacConfig1;
    earc_dmac_config1 &= ~(0xF << 8);
    sampling_bit = audio_hal_earc_get_dmac_sampling_bit (sampling_freq);
    earc_dmac_config1 |= (sampling_bit << 8);
    earc_dmac_config1 &= ~(0x1);        // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 0: disable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    earc_dmac_config1 |= 0x1;   // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 1:enable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    gEarcDmacConfig1 = earc_dmac_config1;

    iec958csd0 = gEarcIec958csd0;
    iec958csd0 |= (0x1 << 1);   // 0:pcm, 1:es
    iec958csd0 &= ~(0x7 << 3);
    iec958csd0 &= ~(0xF << 20);
    iec958csd0 &= ~(0xCF << 24);        // 24-27, 30, 31
    sampling_bit = audio_hal_earc_get_sampling_bit (sampling_freq);
    iec958csd0 |= sampling_bit << 24;
    EARC_LINK0_WR (0x000, iec958csd0);
    EARC_LINK_WR (0x010, iec958csd0);
    gEarcIec958csd0 = iec958csd0;

    // compressed layout A/B
    iec958csd1 = gEarcIec958csd1;
    iec958csd1 &= ~(0xF << 12); // 0: compressed layout A, 7:compressed layout B
    if (audio_compressed_layout == 1)
        iec958csd1 |= 0x7 << 12;        // 0: compressed layout A, 7:compressed layout B
    EARC_LINK0_WR (0x004, iec958csd1);
    EARC_LINK_WR (0x014, iec958csd1);
    gEarcIec958csd1 = iec958csd1;

    iec958csd4 = gEarcIec958csd4;
    iec958csd4 &= ~(0xFF << 8);
    EARC_LINK0_WR (0x010, iec958csd4);
    EARC_LINK_WR (0x020, iec958csd4);
    gEarcIec958csd4 = iec958csd4;

    EARC_LINK0_WR (0x014, 0x0);
    EARC_LINK_WR (0x024, 0x0);

#if 0
    earc_pll_bp_clk = EARC_PHY_RD (0x030);
    if (audio_compressed_layout == 1)
    {
        earc_pll_bp_clk |= 0x1; // 0:2-channel , 1:8-channel
    }
    EARC_PHY_WR (0x030, earc_pll_bp_clk);
    gEarcPllBpClk = earc_pll_bp_clk;
#endif
    // Enable eARC TX DMAC audio datapath.
    if (gAudHalEarcOn)
        EARC_LINK_WR (0x00C, 0x1);
}

static void audio_hal_earc_set_pcm_mode (unsigned int sampling_freq)
{
    unsigned int sampling_bit = 0;
    unsigned int iec958csd0 = 0;
    unsigned int iec958csd1 = 0;
    unsigned int iec958csd4 = 0;
    unsigned int earc_dmac_config0 = 0;
    unsigned int earc_dmac_config1 = 0;
#if 0
    unsigned int earc_pll_bp_clk = 0;
#endif
    // Disable eARC TX DMAC audio datapath.
    EARC_LINK_WR (0x00C, 0x0);

    // Config eARC TX DMAC audio mode
    earc_dmac_config0 = gEarcDmacConfig0;
    earc_dmac_config0 &= ~(1 << 28);    // EARCTX_DMAC_ECC_CUV_SWAP_QST
    //earc_dmac_config0 &= ~(1 << 25);  // EARCTX_DMAC_ECC_OUTPUT_BITORDER_QST
    //earc_dmac_config0 &= ~(1 << 24);  // EARCTX_DMAC_ECC_CALC_BITORDER_QST
    //earc_dmac_config0 &= ~(3 << 20);  // EARCTX_DMAC_COMP_B_VBIT_OVR_VALUE_QST
    //earc_dmac_config0 &= ~(1 << 16);    // EARCTX_DMAC_I2S_BPCUV_EN_QST
    earc_dmac_config0 &= ~(1 << 8);     // EARCTX_DMAC_AUDIO_SOURCE_LAYOUT_QST
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
        earc_dmac_config0 |= (1 << 8);  // 0:2-channel, 1:8-Channel
    earc_dmac_config0 &= ~(7);  // EARCTX_DMAC_AUDIO_MODE_QST   0:2-channel L-PCM, 6:Compressed Layout A, 7:Compressed Layout B
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
        earc_dmac_config0 |= (1);       // 0:2-channel, 1:8-Channel
    EARC_LINK_WR (0x004, earc_dmac_config0);
    gEarcDmacConfig0 = earc_dmac_config0;

    earc_dmac_config1 = gEarcDmacConfig1;
    earc_dmac_config1 &= ~(0xF << 8);
    sampling_bit = audio_hal_earc_get_dmac_sampling_bit (sampling_freq);
    earc_dmac_config1 |= (sampling_bit << 8);
    earc_dmac_config1 &= ~(0x1);        // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 0: disable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    earc_dmac_config1 |= 0x1;   // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 1:enable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    gEarcDmacConfig1 = earc_dmac_config1;

    iec958csd0 = gEarcIec958csd0;
    iec958csd0 &= ~(0x7 << 3);
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
        iec958csd0 |= (0x4 << 3);
    iec958csd0 &= ~(0xF << 20);
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
    {
        if ((gEarcAcmod == 0) || (gEarcAcmod == 2))
            iec958csd0 |= (0x2 << 20);
        else if (gEarcAcmod == 7)
            iec958csd0 |= (0x6 << 20);
        else
            iec958csd0 |= (0x8 << 20);
    }
    else
        iec958csd0 |= (0x2 << 20);
    iec958csd0 &= ~(0x1 << 1);
    iec958csd0 &= ~(0xCF << 24);        // 24-27, 30, 31
    sampling_bit = audio_hal_earc_get_sampling_bit (sampling_freq);
    iec958csd0 |= sampling_bit << 24;   // set bit 0-3(24-27 bit0011000)
    EARC_LINK0_WR (0x000, iec958csd0);
    EARC_LINK_WR (0x010, iec958csd0);
    gEarcIec958csd0 = iec958csd0;

    // compressed layout A/B
    iec958csd1 = gEarcIec958csd1;
    iec958csd1 &= ~(0xF << 12); // 0: compressed layout A, 7:compressed layout B
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
        iec958csd1 |= (0x7 << 12);      // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
    else if (gEarcChannel == 16)
        iec958csd1 |= (0xB << 12);      // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
    else if (gEarcChannel == 32)
        iec958csd1 |= (0x3 << 12);      // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
    EARC_LINK0_WR (0x004, iec958csd1);
    EARC_LINK_WR (0x014, iec958csd1);
    gEarcIec958csd1 = iec958csd1;

    iec958csd4 = gEarcIec958csd4;
    iec958csd4 &= ~(0xFF << 8);
    if ((gEarcChannel == 8) || (gEarcChannel == 6))
    {
        if ((gEarcAcmod == 0) || (gEarcAcmod == 2))
            iec958csd4 |= (0x0 << 8);
        else if (gEarcAcmod == 7)
            iec958csd4 |= (0x0B << 8);
        else
            iec958csd4 |= (0x13 << 8);
    }
    EARC_LINK0_WR (0x010, iec958csd4);
    EARC_LINK_WR (0x020, iec958csd4);
    gEarcIec958csd4 = iec958csd4;

    EARC_LINK0_WR (0x014, 0x0);
    EARC_LINK_WR (0x024, 0x0);
#if 0
    earc_pll_bp_clk = EARC_PHY_RD (0x030);
    earc_pll_bp_clk &= ~(0x1);  // 0:2-channel , 1:8-channel
    EARC_PHY_WR (0x030, earc_pll_bp_clk);
    gEarcPllBpClk = earc_pll_bp_clk;
#endif
    // Enable eARC TX DMAC audio datapath.
    if (gAudHalEarcOn)
        EARC_LINK_WR (0x00C, 0x1);
}

void audio_hal_earc_set_output_format (enum audio_hal_output_format output_format,
    unsigned int sampling_freq)
{
    gEarcOutputFormat = output_format;
    gEarcOutputSamplingFreq = sampling_freq;

    if (output_format == AUDIO_HAL_OUTPUT_PCM)
        audio_hal_earc_set_pcm_mode (sampling_freq);
    else
        audio_hal_earc_set_es_mode (sampling_freq);

    audio_hal_earc_set_pll_bp_clock (sampling_freq);

    audio_hal_earc_monitor_lock ();

    noti ("eARC Output Format : %d, %d\n", output_format, sampling_freq);
}

void audio_hal_earc_set_mute (bool on)
{
    unsigned int iec958csd4 = 0;

    // Assert Channel Status Mute bit.
    iec958csd4 = gEarcIec958csd4;
    if (on)
        iec958csd4 |= 1 << 18;
    else
        iec958csd4 &= ~(1 << 18);

    EARC_LINK0_WR (0x010, iec958csd4);
    EARC_LINK_WR (0x020, iec958csd4);
    gEarcIec958csd4 = iec958csd4;
    EARC_LINK0_WR (0x014, 0);
    EARC_LINK_WR (0x024, 0);

    noti ("eARC Mute : %d\n", on);
}

void audio_hal_earc_set_audio_mode (unsigned int audio_mode)
{
    unsigned int iec958csd1 = 0;
    unsigned int earc_dmac_config0 = 0;

    // Config eARC TX DMAC audio mode
    earc_dmac_config0 = gEarcDmacConfig0;
    earc_dmac_config0 &= ~(7);  // EARCTX_DMAC_AUDIO_MODE_QST   0:2-channel L-PCM, 6:Compressed Layout A, 7:Compressed Layout B
    earc_dmac_config0 |= audio_mode;
    EARC_LINK_WR (0x004, earc_dmac_config0);
    gEarcDmacConfig0 = earc_dmac_config0;

    // compressed layout A/B
    iec958csd1 = gEarcIec958csd1;
    iec958csd1 &= ~(0xF << 12); // 0: compressed layout A, 7:compressed layout B
    if (audio_mode == 7)
        iec958csd1 |= (0x7 << 12);      // 0: compressed layout A, 7:compressed layout B
    EARC_LINK0_WR (0x004, iec958csd1);
    EARC_LINK_WR (0x014, iec958csd1);
    gEarcIec958csd1 = iec958csd1;

    EARC_LINK0_WR (0x014, 0);
    EARC_LINK_WR (0x024, 0x0);

    audio_hal_earc_monitor_lock ();

    noti ("eARC config : am(%d)\n", audio_mode);
}

void audio_hal_earc_set_channel (unsigned int channel, unsigned int acmod)
{
    unsigned int iec958csd0 = 0;
    unsigned int iec958csd1 = 0;
    unsigned int iec958csd4 = 0;
    unsigned int earc_dmac_config0 = 0;
    unsigned int earc_dmac_config1 = 0;
    unsigned int earc_pll_bp_clk = 0;
    unsigned int sampling_bit = 0;

    gEarcChannel = channel;
    gEarcAcmod = acmod;

    EARC_LINK_WR (0x00C, 0x00000000);   // dmac audio data en

    // Config eARC TX DMAC audio mode
    earc_dmac_config0 = gEarcDmacConfig0;
    earc_dmac_config0 &= ~(1 << 8);     // EARCTX_DMAC_AUDIO_SOURCE_LAYOUT_QST
    if ((channel == 8) || (channel == 6))
        earc_dmac_config0 |= (1 << 8);  // 0:2-channel, 1:8-Channel
    earc_dmac_config0 &= ~(0x7);        // EARCTX_DMAC_AUDIO_MODE_QST
    if (gEarcOutputFormat == 0)
    {
        if ((channel == 8) || (channel == 6))
            earc_dmac_config0 |= (1);   // 0:2-channel, 1:8-Channel
    }
    else
    {
        if (audio_compressed_layout == 1)
        {
            earc_dmac_config0 |= 1 << 8;        // audio source layout 0 : 2-channel, 1 : 8-channel
            earc_dmac_config0 |= 7;     // compressed layout B
        }
        else
            earc_dmac_config0 |= 6;     // compressed layout A
    }
    EARC_LINK_WR (0x004, earc_dmac_config0);
    gEarcDmacConfig0 = earc_dmac_config0;

    earc_dmac_config1 = gEarcDmacConfig1;
    earc_dmac_config1 &= ~(0xf << 12);
    if ((channel == 8) || (channel == 6))
    {
        if ((acmod == 0) || (acmod == 2))
            earc_dmac_config1 |= (0x0 << 12);   // 0:2, 2:6, 3:8, 4:12, 5:16, 6:32
        else if (acmod == 7)
            earc_dmac_config1 |= (0x2 << 12);   // 0:2, 2:6, 3:8, 4:12, 5:16, 6:32
        else
            earc_dmac_config1 |= (0x3 << 12);   // 0:2, 2:6, 3:8, 4:12, 5:16, 6:32
    }
    earc_dmac_config1 &= ~(0x1);        // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 0: disable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    earc_dmac_config1 |= 0x1;   // EARCTX_DMAC_PHY_BIPHASE_CLK_EN 1:enable
    EARC_LINK_WR (0x008, earc_dmac_config1);
    gEarcDmacConfig1 = earc_dmac_config1;

    iec958csd0 = gEarcIec958csd0;
    iec958csd0 &= ~(0x7 << 3);
    if (gEarcOutputFormat == 0)
    {
        if ((channel == 8) || (channel == 6))
            iec958csd0 |= (0x4 << 3);
    }
    iec958csd0 &= ~(0xF << 20);
    if (gEarcOutputFormat == 0)
    {
        if ((channel == 8) || (channel == 6))
        {
            if ((acmod == 0) || (acmod == 2))
                iec958csd0 |= (0x2 << 20);
            else if (acmod == 7)
                iec958csd0 |= (0x6 << 20);
            else
                iec958csd0 |= (0x8 << 20);
        }
        else
            iec958csd0 |= (0x2 << 20);
    }
    iec958csd0 &= ~(0xCF << 24);        // 24-27, 30, 31
    sampling_bit = audio_hal_earc_get_sampling_bit (gEarcOutputSamplingFreq);
    iec958csd0 |= sampling_bit << 24;   // set bit 0-3(24-27 bit0011000)
    EARC_LINK0_WR (0x000, iec958csd0);
    EARC_LINK_WR (0x010, iec958csd0);
    gEarcIec958csd0 = iec958csd0;
    iec958csd1 = gEarcIec958csd1;
    iec958csd1 &= ~(0xF << 12);
    if (gEarcOutputFormat == 0)
    {
        if ((channel == 8) || (channel == 6))
            iec958csd1 |= (0x7 << 12);  // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
        else if (channel == 16)
            iec958csd1 |= (0xB << 12);  // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
        else if (channel == 32)
            iec958csd1 |= (0x3 << 12);  // 0x0: 0x2, 7:8, 0xB:16, 0x3:32
    }
    else
    {
        if (audio_compressed_layout == 1)
            iec958csd1 |= (0x7 << 12);  // 0: compressed layout A, 7:compressed layout B
    }
    EARC_LINK0_WR (0x004, iec958csd1);
    EARC_LINK_WR (0x014, iec958csd1);
    gEarcIec958csd1 = iec958csd1;
    iec958csd4 = gEarcIec958csd4;
    iec958csd4 &= ~(0xFF << 8);
    if (gEarcOutputFormat == 0)
    {
        if ((channel == 8) || (channel == 6))
        {
            if ((acmod == 0) || (acmod == 2))
                iec958csd4 |= (0x0 << 8);
            else if (acmod == 7)
                iec958csd4 |= (0x0B << 8);
            else
                iec958csd4 |= (0x13 << 8);
        }
    }
    EARC_LINK0_WR (0x010, iec958csd4);
    EARC_LINK_WR (0x020, iec958csd4);
    gEarcIec958csd4 = iec958csd4;
    EARC_LINK0_WR (0x014, 0x0);
    EARC_LINK_WR (0x024, 0x0);

    earc_pll_bp_clk = EARC_PHY_RD (0x030);
    earc_pll_bp_clk &= ~(0x1);  // 0:2-channel , 1:8-channel
    if ((channel == 8) || (channel == 6))
        earc_pll_bp_clk |= 0x1; // 0:2-channel , 1:8-channel
    EARC_PHY_WR (0x030, earc_pll_bp_clk);
    gEarcPllBpClk = earc_pll_bp_clk;

    audio_hal_earc_monitor_lock ();

    noti ("eARC channel : (ch)%d, acmod : %d\n", channel, acmod);
    debug ("eARC dmac config: %08x, %08x\n", earc_dmac_config0, earc_dmac_config1);
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,4,0)
static void audio_hal_earc_enable_dmac (struct timer_list *unused)
{
    // Enable eARC TX DMAC audio datapath.
    if (gAudHalEarcOn)
    {
        EARC_LINK_WR (0x00C, 0x1);
        debug ("Enable DMAC.\n");
    }
}

static DEFINE_TIMER (_gEnableDmacTimer, audio_hal_earc_enable_dmac);
#else
static void audio_hal_earc_enable_dmac (unsigned long arg)
{
    // Enable eARC TX DMAC audio datapath.
    if (gAudHalEarcOn)
    {
        EARC_LINK_WR (0x00C, 0x1);
        debug ("Enable DMAC.\n");
    }
}

static DEFINE_TIMER (_gEnableDmacTimer, audio_hal_earc_enable_dmac, 0, 0);
#endif

void audio_hal_earc_clear_interrupt (unsigned int int_status)
{
    if (int_status & 0x2)
    {
        // Disable eARC TX DMAC audio datapath.
        EARC_LINK_WR (0x00C, 0x0);

        // Enable eARC TX DMAC audio datapath.
        mod_timer (&_gEnableDmacTimer, jiffies + msecs_to_jiffies (1));
    }
    debug ("eARC Int status: %08x\n", int_status);
}

void audio_hal_earc_set (void)
{
    audio_hal_earc_set_pll_bp_clock (gEarcOutputSamplingFreq);
    audio_hal_earc_set_on (gAudHalEarcOn);
}

void audio_hal_speaker_start (bool on)
{
    if (on == false)
    {
        //SPK I2S enable
        CTOP_CTRL_M23Ax_RdFL (IOMUX_CTRL_VD1, pad_vd166);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrck_mux_sel, 0x1);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_dacsck_mux_sel, 0x1);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrch_mux_sel, 0x1);
        CTOP_CTRL_M23Ax_WrFL (IOMUX_CTRL_VD1, pad_vd166);

        AUD_REG_Wr (PERI_CTRL, pcmoutcmda, (on) ? 1 : 0);
        AUD_REG_WrFL (PERI_CTRL, pcmoutcmda);
        AUD_REG_Wr (PERI_CTRL, pcmstarta, (on) ? 1 : 0);
        AUD_REG_WrFL (PERI_CTRL, pcmstarta);
    }
    else
    {
        //SPK I2S enable
        CTOP_CTRL_M23Ax_RdFL (IOMUX_CTRL_VD1, pad_vd166);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrck_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_dacsck_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd166, reg_pad_daclrch_mux_sel, 0x0);
        CTOP_CTRL_M23Ax_WrFL (IOMUX_CTRL_VD1, pad_vd166);
    }
}

void audio_hal_hp_start (bool on)
{
    AUD_REG_Wr (PERI_CTRL, pcmsuboutcmda, (on) ? 1 : 0);
    AUD_REG_WrFL (PERI_CTRL, pcmsuboutcmda);
    AUD_REG_Wr (PERI_CTRL, pcmsubstarta, (on) ? 1 : 0);
    AUD_REG_WrFL (PERI_CTRL, pcmsubstarta);
}

void audio_hal_spdif_start (bool on)
{
    AUD_REG_Wr (PERI_CTRL, iec0starta, (on) ? 1 : 0);
    AUD_REG_WrFL (PERI_CTRL, iec0starta);
}

void audio_hal_arc_start (bool on)
{
    AUD_REG_RdFL (PERI_CTRL, earc_s_ctrla);
    AUD_REG_WrFd (PERI_CTRL, earc_s_ctrla, earc_spdif_out, (on) ? 1 : 0);
    AUD_REG_WrFL (PERI_CTRL, earc_s_ctrla);
    AUD_REG_RdFL (PERI_CTRL, earc_s_starta);
    AUD_REG_WrFd (PERI_CTRL, earc_s_starta, earc_spdif_start, (on) ? 1 : 0);
    AUD_REG_WrFL (PERI_CTRL, earc_s_starta);
}
#endif
