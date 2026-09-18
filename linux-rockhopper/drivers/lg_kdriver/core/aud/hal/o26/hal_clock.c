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
 *  audio clock hal driver
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

#include "hal/o26/regs.h"
#include "hal/reg_util.h"
#include "hal/hal_clock.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define CLOCK_48KHZ             0x0369D2D5
#define CLOCK_44_1KHZ           0x0322D34D
#define CLOCK_32KHZ             0x02468C8E

/* define O26A0 DTO_A Clock Step Value. */
#define CLOCK_STEP_48KHZ        0x4A9
#define CLOCK_STEP_44_1KHZ      0x4A9
#define CLOCK_STEP_32KHZ        0x4A9

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_hal_clock,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_hal_clock,fmt,##args)
#define info(fmt,args...)   logm_info(aud_hal_clock,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_hal_clock,fmt,##args)
#define error(fmt,args...)  logm_error(aud_hal_clock,fmt,##args)

#define DTO_OUT_DISABLED 1

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
logm_define (aud_hal_clock, log_level_noti);

#ifndef CHIP_TYPE_FPGA
static unsigned int gSpeakerSampleRate = 48000;
static unsigned int gSpdifSampleRate = 48000;
static unsigned int gArcSampleRate = 48000;
static unsigned int gArcChannel = 2;
static unsigned int gSpeakerDtoRate = CLOCK_CENTER;
static unsigned int gSpdifDtoRate = CLOCK_CENTER;
static unsigned int gArcDtoRate = CLOCK_CENTER;
#endif

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/

/*==============================================================================
    Implementation Group
==============================================================================*/
#ifdef CHIP_TYPE_FPGA
int aud_hal_clock_init (void)
{
    // fpga_test0
    AUD_REG_RdFL (PERI_CTRL, fpga_test0);
    AUD_REG_WrFd (PERI_CTRL, fpga_test0, fpga_test_reg0_31, 1); // 0:fs256clk = 12.288MHz, 1:adj_fs256clk selected
    AUD_REG_WrFd (PERI_CTRL, fpga_test0, fpga_test_reg0_1, 1);  // 0:external GSTCC(Integ FPGA), 1:internal GSTCC(UNIT FPGA)
    AUD_REG_WrFL (PERI_CTRL, fpga_test0);

    // fpga_test1
    AUD_REG_RdFL (PERI_CTRL, fpga_test1);
    AUD_REG_WrFd (PERI_CTRL, fpga_test1, fpga_test_reg1_0_15, 0x36);    // adj_fs256clk = 6.144MHz/(value+1) = 6.144/(55) = 112KHz
    AUD_REG_WrFL (PERI_CTRL, fpga_test1);

    return 0;
}

void aud_hal_clock_exit (void)
{
}

int aud_hal_set_speaker_sample_rate (unsigned int sample_rate)
{
    return 0;
}

int aud_hal_set_speaker_channel (unsigned int channel)
{
    return 0;
}

int aud_hal_set_speaker_dto_rate (unsigned int dto_rate)
{
    return CLOCK_CENTER;
}

unsigned int aud_hal_get_speaker_fcw (void)
{
    return CLOCK_CENTER;
}

int aud_hal_set_spdif_sample_rate (unsigned int sample_rate)
{
    return 0;
}

int aud_hal_set_spdif_channel (unsigned int channel)
{
    return 0;
}

int aud_hal_set_spdif_dto_rate (unsigned int dto_rate)
{
    return CLOCK_CENTER;
}

unsigned int aud_hal_get_spdif_fcw (void)
{
    return CLOCK_CENTER;
}

int aud_hal_set_arc_sample_rate (unsigned int sample_rate)
{
    return 0;
}

int aud_hal_set_arc_channel (unsigned int channel)
{
    return 0;
}

int aud_hal_set_arc_dto_rate (unsigned int dto_rate)
{
    return CLOCK_CENTER;
}

unsigned int aud_hal_get_arc_fcw (void)
{
    return CLOCK_CENTER;
}

void aud_hal_switch_spdif_clock (bool onoff)
{
}
#else
int aud_hal_clock_init (void)
{
    //Initialize clock registers.
    //clock setting for E-ARC block
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_HDMI, crg_hdmi005);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_HDMI, crg_hdmi005, reg_hdmirx_prt2_earc_aud_clk_sel, 2);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_HDMI, crg_hdmi005);

    AUD_REG_Wr (EARC_PHY, reg0x5, 0x1); // USER_APHY_PLL_FORCE

    AUD_REG_Wr   (EARC_PHY, reg0x51, 0x4);  // USER_APHY_FRPLL_ICP [7:4] FIN_SEL[3] ICP_G[2] LPF_ON[1] IN_DIVRSTB[0]
    AUD_REG_Wr   (EARC_PHY, reg0x52, 0x1);  // USER_APHY_FRPLL_M [5:0] 1
    AUD_REG_Wr   (EARC_PHY, reg0x53, 0x00); // USER_APHY_FRPLL_DIVINT [8] 0
    AUD_REG_Wr   (EARC_PHY, reg0x54, 0x2E); // USER_APHY_FRPLL_DIVINT [7:0] 2E

    AUD_REG_Wr   (EARC_PHY, reg0x57, 0xC7); // USER_APHY_FRPLL_FCW[23:16]   C7
    AUD_REG_Wr   (EARC_PHY, reg0x58, 0x10); // USER_APHY_FRPLL_FCW[15:8]   10
    AUD_REG_Wr   (EARC_PHY, reg0x59, 0xCA); // USER_APHY_FRPLL_FCW[7:0]   CA

    AUD_REG_Wr   (EARC_PHY, reg0x60, 0x00); // [2] USER_APHY_FRPLL_OUTDIV[8]
    AUD_REG_Wr   (EARC_PHY, reg0x61, 0x26); // USER_APHY_FRPLL_OUTDIV[7:0] 26

    //CRG_TOP earcpll disable
    AUD_REG_Wr   (EARC_PHY, reg0x70, 0x1);  // USER_FRPLL_PDB_FORCE 0 : not force 1 : force
    AUD_REG_Wr   (EARC_PHY, reg0x71, 0x0);  // USER_FRPLL_PDB_FORCE_VALUE // off

    //clock setting for APLL block
    /*-----------------------------------------------------------------------------------------
	0xCC6A_2000    apll_frpll_00 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, apll_frpll_00);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_out_div, 0x82);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_icp, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_fin_sel, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_dsm_limit, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_auto_freq, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_dsmon, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_divint, 0x3F);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_wakeup_bypass, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_fout2_en, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_lpf_on, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_00, reg_apll_frpll_in_divsel, 0x0);
    CTOP_CTRL_O26Ax_WrFL (TRG_CTRL, apll_frpll_00);

    /*-----------------------------------------------------------------------------------------
	0xCC6A_2004    apll_frpll_01 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, apll_frpll_01);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_fcw, 0xE5C91D);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_m, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_syncon, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_fout_en, 0x1);
    CTOP_CTRL_O26Ax_WrFL (TRG_CTRL, apll_frpll_01);

    /*-----------------------------------------------------------------------------------------
	0xCC6A_2008    apll_frpll_02 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, apll_frpll_02);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_02, reg_apll_frpll_icp_g, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_02, reg_apll_frpll_in_divrstb, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_02, reg_apll_frpll_a, 0x3f);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_02, reg_apll_frpll_frequp, 0x0);
    CTOP_CTRL_O26Ax_WrFL (TRG_CTRL, apll_frpll_02);

#ifndef SUPPORT_SOUNDBAR
    //clock DCO value setting for aad/btsc block
    /*-----------------------------------------------------------------------------------------
	0xCC9E_4014    mip_adc05 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc00);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_sel_sif, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_adc_icon, 0x4);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_icp, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_autofreq, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_adc_refsel, 0x1); //AAD ADC reference voltage selection to 1.2V (b0 -> b1)(2019.07.23), dooyeoun.kim
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_icp_g, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_pdb, 0x0);        //AAD ADC  power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_outsel, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_bias_pdb, 0x0);   //AAD ADC BIAS power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_lpf_on, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_sel_clkinv, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_apll_frequp, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_decm, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc00);
    //CTOP_CTRL_O26Ax_Wr01 (CTOP_SYN_DBB, mip_adc05, reg_dbb__admd_a_gc, 0x0);

    /*-----------------------------------------------------------------------------------------
	    0xCC9E_4004    mip_adc01 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc01);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc01, reg_admd_apll_insel, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc01, reg_admd_apll_cken, 0x7);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc01, reg_admd_apll_lockf, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc01, reg_admd_apll_wakebypass, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc01, reg_admd_apll_od_en, 0x1);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc01);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_4004    mip_adc02 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc02);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc02, reg_admd_apll_odpost, 0x23);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc02, reg_admd_apll_divint, 0x180);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc02, reg_admd_apll_lockc, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc02, reg_admd_apll_syncon, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc02);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_4008    mip_adc03 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc03);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc03, reg_admd_apll_pdb, 0x0);     //AAD PLL power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc03, reg_admd_apll_m, 0x19);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc03);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_4008    mip_adc04 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc04);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc04, reg_admd_apll_odpre, 0x19);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc04);

    //delay before sw reset control
    udelay (100);

    //delay 200ns before set syncon 1.
    udelay (100);

    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc00);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_pdb, 0x1);        //AAD ADC  power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc00, reg_admd_a_bias_pdb, 0x1);   //AAD ADC BIAS power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc00);

    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ADMD_MIP, mip_adc03);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ADMD_MIP, mip_adc03, reg_admd_apll_pdb, 0x1);     //AAD PLL power down (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ADMD_MIP, mip_adc03);
#endif

    // O26 : 0: apll, 1: apll 2: frpll(EARC), 3:dto0, 4:dto1, 5:dto2
    //Register Setting for AUDIO CLK

    // CTOP SYN Setting
    // 0:925Mhz(wo/ SS), 1: 800Mhz(w/ SS)
    CTOP_CTRL_O26Ax_RdFL (BND_CTRL_AUD, aud_syn_02);
    CTOP_CTRL_O26Ax_Wr01 (BND_CTRL_AUD, aud_syn_02, reg_audio_dto0_sel, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (BND_CTRL_AUD, aud_syn_02, reg_audio_dto1_sel, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (BND_CTRL_AUD, aud_syn_02, reg_audio_dto2_sel, 0x0);
    CTOP_CTRL_O26Ax_WrFL (BND_CTRL_AUD, aud_syn_02);

    // MAIN_CLK
#if defined(SUPPORT_SOUNDBAR) || defined(SUPPORT_SLT)
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud026);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud026);
#else
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud026);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x5);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud026);
#endif
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud027);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud027, reg_sel5_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud027);

    // PC_CLK
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud016);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud016, reg_sel0_aclk_div, 0x5);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud016);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud017);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud017, reg_sel0_aclk_src, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud017);

    // SPDIF_CLK
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud018);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud018, reg_sel1_aclk_div, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud018);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud019);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud019, reg_sel1_aclk_src, 0x3);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud019);

    // EARC_CLK
#ifdef SUPPORT_SOUNDBAR
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud020);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud020, reg_sel2_aclk_div, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud020);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud021);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud021, reg_sel2_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud021);
#else
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud020);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud020, reg_sel2_aclk_div, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud020);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud021);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud021, reg_sel2_aclk_src, 0x2);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud021);
#endif

    // HP_CLK
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud022);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud022, reg_sel3_aclk_div, 0x5);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud022);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud023);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud023, reg_sel3_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud023);

    // PDM_CLK
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud024);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud024, reg_sel4_aclk_div, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud024);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud025);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud025, reg_sel4_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud025);

    // pdl_div_sel
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud015);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud015, reg_aud__pdm_div_sel, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud015);

    // mclk_auad
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud028);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud028, reg_sel6_aclk_div, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud028);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud029);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud029, reg_sel6_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud029);

    // mclk2_clk0
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud030);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud030, reg_sel7_aclk_div, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud030);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud031);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud031, reg_sel7_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud031);

    // mclk2_clk1
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud032);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud032, reg_sel8_aclk_div, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud032);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud033);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud033, reg_sel8_aclk_src, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud033);

    // CTOP SYN Setting
    CTOP_CTRL_O26Ax_RdFL (MIP_DIG_CTRL, bmc_syn_0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_DIG_CTRL, bmc_syn_0, reg_aclk_mux_mip_dig_inv_sel, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_DIG_CTRL, bmc_syn_0, reg_mclk0_inv_sel, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_DIG_CTRL, bmc_syn_0);

    //DTO Seting for AUDIO CLK Generation
    //Setting A-DTO 0 clock
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud003);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud003, reg_adto0_add_value_pos, CLOCK_48KHZ);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud003);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud004);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud004, reg_adto0_err_value_pos, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud004);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud005);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud005, reg_adto0_swrst_adto, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud005);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud006);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud006, reg_adto0_sync_update, 1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud006);

    //Setting A-DTO 1 clock
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud007);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud007, reg_adto1_add_value_pos, CLOCK_48KHZ);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud007);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud008);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud008, reg_adto1_err_value_pos, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud008);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud009);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud009, reg_adto1_swrst_adto, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud009);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud010);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud010, reg_adto1_sync_update, 1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud010);

    //Setting A-DTO 2 clock for WOV Control.    // for pdm
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud011);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud011, reg_adto2_add_value_pos, 0xFBA8826);   // 24.576 MHz
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud011);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud012);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud012, reg_adto2_err_value_pos, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud012);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud013);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud013, reg_adto2_swrst_adto, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud013);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud014);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud014, reg_adto2_sync_update, 1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud014);

    //Enable D-DTO clock for CTOP Control for toggle.
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud014);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud014, reg_adto2_sync_update, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud014);
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud010);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud010, reg_adto1_sync_update, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud010);

    //Enable D-DTO clock for CTOP Control for toggle.
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud014);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud014, reg_adto2_sync_update, 0x1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud014);
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud010);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud010, reg_adto1_sync_update, 0x1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud010);

    //CRG_TOP apll enable
    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, crg_top_00);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, crg_top_00, reg_apll_pll_pdb_ctrl, 0x1);
    CTOP_CTRL_O26Ax_WrFL (TRG_CTRL, crg_top_00);

    //LNX2 Clock
    // disable LNX2 Core clock
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2002);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2002, reg_lnx2_core_clk_gate_en, 1);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2002);

    // 800Mhz : 0, 600Mhz : 1, 400Mhz : 2
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2004);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2004, reg_lnx2_core_clk_sel, 0);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2004);

    // Enable LNX2 Core clock
    CTOP_CTRL_O26Ax_RdFL (SCRG_CTRL_LNX2, crg_lnx2002);
    CTOP_CTRL_O26Ax_Wr01 (SCRG_CTRL_LNX2, crg_lnx2002, reg_lnx2_core_clk_gate_en, 0);
    CTOP_CTRL_O26Ax_WrFL (SCRG_CTRL_LNX2, crg_lnx2002);

    //delay before sw reset control
    udelay (100);

    //SW reset setting for mixed-IP block
    CTOP_CTRL_O26Ax_RdFL (MIP_DIG_CTRL, bmc_syn_2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_DIG_CTRL, bmc_syn_2, reg_swrst_auad, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_DIG_CTRL, bmc_syn_2);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud009);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud009, reg_adto1_swrst_adto, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud009);
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud013);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud013, reg_adto2_swrst_adto, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud013);

    CTOP_CTRL_O26Ax_RdFL (MIP_DIG_CTRL, bmc_syn_2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_DIG_CTRL, bmc_syn_2, reg_swrst_auda_f256fs_clk0, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_DIG_CTRL, bmc_syn_2, reg_swrst_auda_f256fs_clk1, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_DIG_CTRL, bmc_syn_2);

    // fix QEVENTTWEN-22666 HT-E6750W audio output late 30 ~ 60 sec. 0xc930e4a4 [24,20,16,12] bit
    // fix in O26 SoC(http://jira.lge.com/issue/browse/SCDCR-7893)
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc04);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc04, reg_pad_iec958out__ds0, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc04, reg_pad_iec958out__ds1, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc04, reg_pad_iec958out__ds2, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc04, reg_pad_iec958out__ds3, 0x0);
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc04);

#ifdef SUPPORT_SOUNDBAR
    // for uart2 enable for temporal
    CTOP_CTRL_O26Ax_RdFL (IOMUX_CTRL_DPE, pad_dpe64);
    //(MODE4): main_uart_txd2 / None
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_DPE, pad_dpe64, reg_pad_spi_cs1_mux_sel, 0x4);   // 0x4 15:12
    //(MODE4): None / main_uart_rxd2
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_DPE, pad_dpe64, reg_pad_spi_di1_mux_sel, 0x4);   // 0x4 11:8
    CTOP_CTRL_O26Ax_WrFL (IOMUX_CTRL_DPE, pad_dpe64);

    CTOP_CTRL_O26Ax_RdFL (CPU_BND_CTRL_WOC, mem6);
    //4'd2  : cpu0
    CTOP_CTRL_O26Ax_Wr01 (CPU_BND_CTRL_WOC, mem6, reg_main_uart_sel0, 0x2);   // 0x4 11:8
    //4'd0  : micom0
    CTOP_CTRL_O26Ax_Wr01 (CPU_BND_CTRL_WOC, mem6, reg_main_uart_sel1, 0x0);   // 0x4 7:4
    //4'd4  : cpu2
    CTOP_CTRL_O26Ax_Wr01 (CPU_BND_CTRL_WOC, mem6, reg_main_uart_sel2, 0x4);   // 0x4 3:0
    CTOP_CTRL_O26Ax_WrFL (CPU_BND_CTRL_WOC, mem6);

    noti ("uart2 enable done\n");
#endif

    noti ("init done\n");
    return 0;
}

void aud_hal_clock_exit (void)
{
}

static int _aud_adjust_dto_rate (unsigned int dto_rate, unsigned int ref)
{
    unsigned int before = dto_rate;

    /* Check a DTO_A Tap Max. and Min Value. */
    if (dto_rate >= CLOCK_MAX)
    {
        dto_rate = CLOCK_MAX;
    }
    else if (dto_rate >= TABLE_HIGH_TO_LOW)
    {
        /* Check a previous value to decrease speedly. */
        if (dto_rate < ref)
        {
            dto_rate -= CLOCK_HIGH;
        }
    }
    else if (dto_rate <= CLOCK_MIN)
    {
        dto_rate = CLOCK_MIN;
    }
    else if (dto_rate <= TABLE_LOW_TO_HIGH)
    {
        /* Check a previous value to decrease speedly. */
        if (dto_rate > ref)
        {
            dto_rate += CLOCK_LOW;
        }
    }

    info ("before: %d after %d", before, dto_rate);

    return dto_rate;
}

struct frpll_fout_settings
{
    unsigned int sample_rate;
    unsigned int channel;
    unsigned int m;
    unsigned int divint;
    unsigned int fcw;
    unsigned int out_div;
    unsigned int step;
    unsigned int icp;
    unsigned int icp_g;
};

static struct frpll_fout_settings frpll_fout_table[] = {
    /* *INDENT-OFF* */
    /* TODO */
    {48000,   0x2,  0x1,    0x3E,   0xAB367A,   0x1FE,  0x5591, 0x0, 0x1},
    {44100,   0x2,  0x1,    0x39,   0x93B3A6,   0x1FE,  0x5591, 0x0, 0x1},
    {32000,   0x2,  0x1,    0x29,   0xC779A6,   0x1FE,  0x5591, 0x0, 0x1},
    {192000,  0x2,  0x1,    0x3F,   0xE5C91D,   0x82,   0x15D0, 0x0, 0x1},
    {176400,  0x2,  0x1,    0x40,   0x1FFB48,   0x8E,   0x17D4, 0x0, 0x1},
    {128000,  0x2,  0x1,    0x40,   0x39ABF3,   0xC4,   0x20E3, 0x0, 0x1},
    {96000,   0x2,  0x1,    0x3E,   0x6C4C59,   0xFE,   0x2A9E, 0x0, 0x1},
    {88200,   0x2,  0x1,    0x40,   0x93964A,   0x11E,  0x3028, 0x0, 0x1},
    {64000,   0x2,  0x1,    0x40,   0x8D8EC9,   0x18A,  0x421B, 0x0, 0x1},
    /* *INDENT-O0N* */
};

static struct frpll_fout_settings *_aud_get_frpll_fout_settings (unsigned int sample_rate)
{
    int i;

    for (i = 0; i < sizeof (frpll_fout_table) / sizeof (frpll_fout_table[0]); i++)
    {
        if (frpll_fout_table[i].sample_rate == sample_rate)
            return &frpll_fout_table[i];
    }

    return &frpll_fout_table[0];
}

static struct frpll_fout_settings earc_frpll_fout_table[] = {
    /* *INDENT-OFF* */
    /* 2 Channel : 1x MODE (Range: +/- 52Hz) */
    {48000,   0x2,  0x1,  0x2E,   0xC710CA,   0x26,  0x010000, 0x0, 0x1},
    {44100,   0x2,  0x1,  0x2A,   0x9A176F,   0x26,  0x010000, 0x0, 0x1},
    {32000,   0x2,  0x1,  0x1F,   0x84B5DC,   0x26,  0x010000, 0x0, 0x1},
    {192000,  0x2,  0x3,  0xB0,   0xC9EECB,   0x0C,  0x010000, 0x1, 0x1},
    {176400,  0x2,  0x3,  0xA2,   0x47ECFE,   0x0C,  0x010000, 0x1, 0x1},
    {128000,  0x2,  0x3,  0x89,   0x809D4A,   0x0E,  0x010000, 0x1, 0x1},
    {96000,   0x2,  0x2,  0x62,   0x374BC5,   0x14,  0x010000, 0x0, 0x1},
    {88200,   0x2,  0x2,  0x5A,   0x446739,   0x14,  0x010000, 0x0, 0x1},
    {64000,   0x2,  0x2,  0x34,   0xB71759,   0x10,  0x010000, 0x2, 0x1},
    /* 8 Channel 4x MODE (Range: +/- 43Hz)*/
    {48000,   0x8,  0x1,  0x27,   0x495181,   0x08,  0x010000, 0x0, 0x1},
    {44100,   0x8,  0x1,  0x24,   0x81C2E0,   0x08,  0x010000, 0x0, 0x1},
    {32000,   0x8,  0x1,  0x1A,   0xDB8BAC,   0x08,  0x010000, 0x0, 0x1},
    {192000,  0x8,  0x3,  0x75,   0xDBF487,   0x02,  0x010000, 0x1, 0x1},
    {176400,  0x8,  0x3,  0x6C,   0x8548A9,   0x02,  0x010000, 0x1, 0x1},
    {128000,  0x8,  0x3,  0x4E,   0x92A306,   0x02,  0x010000, 0x0, 0x1},
    {96000,   0x8,  0x2,  0x4E,   0x92A306,   0x04,  0x010000, 0x0, 0x1},
    {88200,   0x8,  0x3,  0x6C,   0x8548A9,   0x04,  0x010000, 0x1, 0x1},
    {64000,   0x8,  0x3,  0x4E,   0x92A306,   0x04,  0x010000, 0x0, 0x1},
    /* *INDENT-ON* */
};

static struct frpll_fout_settings *_aud_get_earc_frpll_fout_settings (unsigned int sample_rate, unsigned int channel)
{
    int i;

    for (i = 0; i < sizeof (earc_frpll_fout_table) / sizeof (earc_frpll_fout_table[0]); i++)
    {
        if ((earc_frpll_fout_table[i].sample_rate == sample_rate) && (earc_frpll_fout_table[i].channel == channel))
            return &earc_frpll_fout_table[i];
    }

    return &earc_frpll_fout_table[0];
}

static int aud_tune_apll (unsigned int sample_rate, unsigned int dto_rate)
{
    unsigned int dto_clock;
    struct frpll_fout_settings *pSettings = NULL;

    // we use 6.144 MHz as 1/4 of 24.576 MHz
    if (sample_rate == 96000)
    {
        pSettings = _aud_get_frpll_fout_settings (sample_rate * 2);
        dto_clock = pSettings->fcw + (dto_rate - CLOCK_CENTER) * pSettings->step * 2;
    }
    else
    {
        pSettings = _aud_get_frpll_fout_settings (sample_rate * 4);
        dto_clock = pSettings->fcw + (dto_rate - CLOCK_CENTER) * pSettings->step * 4;
    }
    info ("before: %x", CTOP_CTRL_O26Ax_Rd (TRG_CTRL, apll_frpll_01));
    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, apll_frpll_01);
    CTOP_CTRL_O26Ax_Wr01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_fcw, dto_clock);
    CTOP_CTRL_O26Ax_WrFL (TRG_CTRL, apll_frpll_01);

    info ("sample_rate = %dHz, dto_rate = %d, dto_clock = %d\n", sample_rate, dto_rate, dto_clock);

    return 0;
}

int aud_hal_set_speaker_sample_rate (unsigned int sample_rate)
{
#ifdef SUPPORT_SOUNDBAR
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud026);
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud020);
    unsigned int swreset_bit = 0;

    if (sample_rate == 96000)
    {
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x4);   // 0:1/2, 4 : Enable
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud020, reg_sel2_aclk_div, 0x4);
    }
    else
    {
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x5);   // 0:1/2, 4 : Enable
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud020, reg_sel2_aclk_div, 0x5);
    }

    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud026);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud020);

    if (gSpeakerDtoRate != sample_rate)
    {
        usleep_range (10, 10);
        swreset_bit = AUD_REG_Rd (PERI_CTRL, aud_swreset);
        swreset_bit &= ~(0x3F8);
        AUD_REG_Wr (PERI_CTRL, aud_swreset, swreset_bit);
        swreset_bit |= 0x3F8;
        AUD_REG_Wr (PERI_CTRL, aud_swreset, swreset_bit);
    }
#else
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud026);

    if (sample_rate == 96000)
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x4);   // 0:1/2, 4 : Enable
    else
        CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud026, reg_sel5_aclk_div, 0x5);   // 0:1/2, 4 : Enable

    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud026);
#endif

    gSpeakerSampleRate = sample_rate;

    info ("sample_rate %d Hz", sample_rate);

    return 0;
}

int aud_hal_set_speaker_channel (unsigned int channel)
{
    return 0;
}

int aud_hal_set_speaker_dto_rate (unsigned int dto_rate)
{
    unsigned int dto_clock = CLOCK_48KHZ;
    unsigned int dtoRate = _aud_adjust_dto_rate (dto_rate, gSpeakerDtoRate);

    debug ("%d Hz\n", gSpeakerSampleRate);

    aud_tune_apll (gSpeakerSampleRate, dtoRate);

    gSpeakerDtoRate = dto_rate;

    info ("dto_rate %d, dto_clock 0x%x\n", dto_rate, dto_clock);

    return dtoRate;
}

unsigned int aud_hal_get_speaker_fcw (void)
{
    unsigned int dto_clock;

    CTOP_CTRL_O26Ax_RdFL (TRG_CTRL, apll_frpll_01);
    CTOP_CTRL_O26Ax_Rd01 (TRG_CTRL, apll_frpll_01, reg_apll_frpll_fcw, dto_clock);

    info ("fcw 0x%x\n", dto_clock);

    return dto_clock;
}

static int aud_set_earc_frpll (unsigned int sample_rate)
{
    struct frpll_fout_settings *pSettings = NULL;
    unsigned int temp_reg =  0;

    pSettings = _aud_get_earc_frpll_fout_settings (sample_rate, gArcChannel);

    AUD_REG_Wr   (EARC_PHY, reg0x70, 0x1);  // USER_FRPLL_PDB_FORCE 0 : not force 1 : force
    AUD_REG_Wr   (EARC_PHY, reg0x71, 0x0);  // USER_FRPLL_PDB_FORCE_VALUE 0 : FRPLL off, 1 : FRPLL on

    temp_reg = AUD_REG_Rd   (EARC_PHY, reg0x60); // USER_APHY_FRPLL_OUT_DIV8
    temp_reg &= ~(0x1 << 2);
    temp_reg |= (((pSettings->out_div >> 8) & 0x1) << 2);
    AUD_REG_Wr   (EARC_PHY, reg0x60, temp_reg);
    AUD_REG_Wr   (EARC_PHY, reg0x61, pSettings->out_div & 0xFF); // USER_APHY_FRPLL_OUT_DIV7_0

    temp_reg = AUD_REG_Rd   (EARC_PHY, reg0x51); // USER_APHY_FRPLL_ICP
    temp_reg &= ~(0xF << 4);
    temp_reg |= ((pSettings->icp) << 4);
    AUD_REG_Wr   (EARC_PHY, reg0x51, temp_reg);

    AUD_REG_Wr   (EARC_PHY, reg0x52, pSettings->m); // USER_APHY_FRPLL_M

    AUD_REG_Wr   (EARC_PHY, reg0x53, (pSettings->divint >> 8) & 0x1); // USER_APHY_FRPLL_DIVINT8
    AUD_REG_Wr   (EARC_PHY, reg0x54, pSettings->divint & 0xFF); // USER_APHY_FRPLL_DIVINT7_0

    AUD_REG_Wr   (EARC_PHY, reg0x57, pSettings->fcw >> 16 & 0xFF); // USER_APHY_FRPLL_FCW23_16
    AUD_REG_Wr   (EARC_PHY, reg0x58, pSettings->fcw >> 8 & 0xFF);  // USER_APHY_FRPLL_FCW15_8
    AUD_REG_Wr   (EARC_PHY, reg0x59, pSettings->fcw & 0xFF);       // USER_APHY_FRPLL_FCW17_0

    AUD_REG_Wr   (EARC_PHY, reg0x71, 0x1);    // USER_FRPLL_PDB_FORCE_VALUE 1 : FRPLL on

    info ("sample_rate %d Hz divint(%x) fcw(%x) outdiv(%x)\n", sample_rate,
        pSettings->divint, pSettings->fcw, pSettings->out_div);

    return RET_OK;
}

static int aud_tune_earc_frpll (unsigned int sample_rate, unsigned int dto_rate)
{
    unsigned int dto_clock;
    struct frpll_fout_settings *pSettings = NULL;

    pSettings = _aud_get_earc_frpll_fout_settings (sample_rate, gArcChannel);

    dto_clock = pSettings->fcw + (dto_rate - CLOCK_CENTER) * pSettings->step;

    //Setting E-ARC Audio PLL clock for CTOP Control.
    AUD_REG_Wr   (EARC_PHY, reg0x57, dto_clock >> 16 & 0xFF); // USER_APHY_FRPLL_FCW23_16
    AUD_REG_Wr   (EARC_PHY, reg0x58, dto_clock >> 8 & 0xFF);  // USER_APHY_FRPLL_FCW15_8
    AUD_REG_Wr   (EARC_PHY, reg0x59, dto_clock & 0xFF);       // USER_APHY_FRPLL_FCW17_0

    info ("sample_rate %d Hz, dto_rate %d, dto_clock 0x%x\n", sample_rate, dto_rate, dto_clock);

    return dto_rate;
}

int aud_hal_set_spdif_sample_rate (unsigned int sample_rate)
{
    //SPDIF(fs21clk)
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud018);

    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud018, reg_sel1_aclk_div, 0x0);       // 0:bypass

    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud018);

    gSpdifSampleRate = sample_rate;

    aud_hal_set_spdif_dto_rate (CLOCK_CENTER);

    info ("sample_rate %d Hz", sample_rate);

    return 0;
}

int aud_hal_set_spdif_channel (unsigned int channel)
{
    return 0;
}

int aud_hal_set_spdif_dto_rate (unsigned int dto_rate)
{
    int dtoRate = _aud_adjust_dto_rate (dto_rate, gSpdifDtoRate);
    unsigned int dto_clock;

    debug ("%d Hz.\n", gSpdifSampleRate);

    /* Compute a New DTO_A Clock Value for 48KHz. */
    if (gSpdifSampleRate == 48000)
        dto_clock = CLOCK_48KHZ + (dtoRate - CLOCK_CENTER) * CLOCK_STEP_48KHZ;
    else if (gSpdifSampleRate == 44100)
        dto_clock = CLOCK_44_1KHZ + (dtoRate - CLOCK_CENTER) * CLOCK_STEP_44_1KHZ;
    else if (gSpdifSampleRate == 32000)
        dto_clock = CLOCK_32KHZ + (dtoRate - CLOCK_CENTER) * CLOCK_STEP_32KHZ;
    else
    {
        error ("sample_rete %d Hz\n", gSpdifSampleRate);

        /* Compute a New DTO_A Clock Value for 48KHz. */
        dto_clock = CLOCK_48KHZ + (dtoRate - CLOCK_CENTER) * CLOCK_STEP_48KHZ;
    }

    //Setting A-DTO 0 clock for WOV Control.
    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud003);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud003, reg_adto0_add_value_pos, dto_clock);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud003);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud004);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud004, reg_adto0_err_value_pos, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud004);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud006);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud006, reg_adto0_sync_update, 0);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud006);

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud006);
    CTOP_CTRL_O26Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud006, reg_adto0_sync_update, 1);
    CTOP_CTRL_O26Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud006);

    info ("dto_rate %d, dto_clock 0x%x\n", dto_rate, dto_clock);

    //Save current SPDIF DTO Rate
    gSpdifDtoRate = dtoRate;

    //MIXED_IP_AUDIO_SetDTORate (LX_AUD_MASTER_OUTPUT_SPDIF, dtoRate,
    //    DTO_FORCE_CNT_NOT_CLEAR);

    return dtoRate;
}

unsigned int aud_hal_get_spdif_fcw (void)
{
    unsigned int dto_clock;

    CTOP_CTRL_O26Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud003);
    CTOP_CTRL_O26Ax_Rd01 (MCRG_CTRL_AUD, crg_main_aud003, reg_adto0_add_value_pos, dto_clock);

    info ("fcw 0x%x\n", dto_clock);

    return dto_clock;
}

int aud_hal_set_arc_sample_rate (unsigned int sample_rate)
{
    aud_set_earc_frpll (sample_rate);

    gArcSampleRate = sample_rate;

    info ("sample_rate %d Hz.\n", sample_rate);

    return 0;
}

int aud_hal_set_arc_channel (unsigned int channel)
{
    gArcChannel = channel;

    info ("channel %d Hz.\n", channel);

    return 0;
}

int aud_hal_set_arc_dto_rate (unsigned int dto_rate)
{
    int dtoRate = _aud_adjust_dto_rate (dto_rate, gArcDtoRate);

    aud_tune_earc_frpll (gArcSampleRate, dtoRate);

    gArcDtoRate = dtoRate;

    //MIXED_IP_AUDIO_SetDTORate (LX_AUD_MASTER_OUTPUT_ARC, dtoRate, DTO_FORCE_CNT_NOT_CLEAR);
    info ("dto_rate %d.\n", dto_rate);

    return dtoRate;
}

unsigned int aud_hal_get_arc_fcw (void)
{
    // remove reg_earcpll_frpll_fcw in O26
    return CLOCK_CENTER;
}

void aud_hal_switch_spdif_clock (bool onoff)
{
}
#endif
