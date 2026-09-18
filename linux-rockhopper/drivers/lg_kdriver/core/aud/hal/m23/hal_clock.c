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

#include "hal/hal_clock.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define CLOCK_48KHZ             0x03EEA209
#define CLOCK_44_1KHZ           0x039CD812
#define CLOCK_32KHZ             0x029F16B1


/* define M23A0 DTO_A Clock Step Value. */
#define CLOCK_STEP_48KHZ        0x55E
#define CLOCK_STEP_44_1KHZ      0x55E
#define CLOCK_STEP_32KHZ        0x55E

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

void aud_hal_switch_spdif_clock (bool onoff)
{
}
#else
int aud_hal_clock_init (void)
{
    //FRPLL_EARC Clock
    CTOP_CTRL_M23Ax_RdFL (MIP_CTRL_EARC, mip_earc00);
    CTOP_CTRL_M23Ax_Wr01 (MIP_CTRL_EARC, mip_earc00, reg_hdmi_earc_crg_clk_rst_sel, 0x1);
    CTOP_CTRL_M23Ax_WrFL (MIP_CTRL_EARC, mip_earc00);

    CTOP_CTRL_M23Ax_RdFL (SCRG_CTRL_HDMI, crg_hdmi05);
    CTOP_CTRL_M23Ax_Wr01 (SCRG_CTRL_HDMI, crg_hdmi05, reg_hdmirx_prt2_earc_aud_clk_sel, 0x2);
    CTOP_CTRL_M23Ax_WrFL (SCRG_CTRL_HDMI, crg_hdmi05);

    // 0: ctop reg control 1: aud reg control
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, fcw_mux_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, fcw_mux_00, reg_earcpll_fcw_mux_sel, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, fcw_mux_00);

    //AUD_PLL FCW selection
    // 0: ctop reg control 1: aud reg control
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, fcw_mux_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, fcw_mux_00, reg_apll_fcw_mux_sel, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, fcw_mux_00);

    //Initialize clock registers.
    //clock setting for E-ARC block
    /*-----------------------------------------------------------------------------------------
		0xCC92_202C    earcpll_frpll_00 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_out_div, 0x1FE);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_icp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_fin_sel, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_dsm_limit, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_auto_freq, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_dsmon, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_divint, 0x3E);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_wakeup_bypass, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_fout2_en, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_lpf_on, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_in_divsel, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_00);

    /*-----------------------------------------------------------------------------------------
    0xCC92_2030    earcpll_frpll_01 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fcw, 0xAB367A);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_m, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_syncon, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fout_en, 0x1);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_01);

    /*-----------------------------------------------------------------------------------------
    0xCC92_2014    earcpll_frpll_02 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_02);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_icp_g, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_in_divrstb, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_a, 0x3F);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_frequp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_out_div2, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_out_div3, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_lock, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_02);

    //CRG_TOP earcpll disable
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, crg_top_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, crg_top_00, reg_earcpll_pll_pdb_ctrl, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, crg_top_00);

    //clock setting for APLL block
    /*-----------------------------------------------------------------------------------------
	0xCC92_201C    apll_frpll_00 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, apll_frpll_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_out_div, 0x82);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_icp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_fin_sel, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_dsm_limit, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_auto_freq, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_dsmon, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_divint, 0x3F);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_wakeup_bypass, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_fout2_en, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_lpf_on, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_00, reg_apll_frpll_in_divsel, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, apll_frpll_00);

    /*-----------------------------------------------------------------------------------------
	0xCC92_2020    apll_frpll_01 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, apll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_fcw, 0xE5C91D);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_m, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_syncon, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_fout_en, 0x1);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, apll_frpll_01);

    /*-----------------------------------------------------------------------------------------
	0xCC92_202C    apll_frpll_02 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, apll_frpll_02);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_02, reg_apll_frpll_icp_g, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_02, reg_apll_frpll_in_divrstb, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_02, reg_apll_frpll_a, 0x3f);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_02, reg_apll_frpll_frequp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_02, reg_apll_frpll_lock, 0x0);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, apll_frpll_02);

    //clock DCO value setting for aad/btsc block
    /*-----------------------------------------------------------------------------------------
	0xCA83_3010    mip_adc05 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc00);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_sel_sif, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_adc_icon, 0x4);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_icp, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_autofreq, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_adc_refsel, 0x1);     //AAD ADC reference voltage selection to 1.2V (b0 -> b1)(2019.07.23), dooyeoun.kim
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_icp_g, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_pdb, 0x0);    //AAD ADC  power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_outsel, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_bias_pdb, 0x0);       //AAD ADC BIAS power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_lpf_on, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_sel_clkinv, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_apll_frequp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_decm, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc00);
    //CTOP_CTRL_M23Ax_Wr01 (CTOP_SYN_DBB, mip_adc05, reg_dbb__admd_a_gc, 0x0);

    /*-----------------------------------------------------------------------------------------
	    0xC615_5004444    mip_adc01 ''
	-----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc01);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc01, reg_admd_apll_insel, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc01, reg_admd_apll_cken, 0x7);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc01, reg_admd_apll_lockf, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc01, reg_admd_apll_wakebypass, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc01, reg_admd_apll_od_en, 0x1);
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc01);

    /*-----------------------------------------------------------------------------------------
        0xC615_5008    mip_adc02 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc02);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_apll_odpost, 0x23);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_apll_divint, 0x180);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_apll_lockc, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc02, reg_admd_apll_syncon, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc02);

    /*-----------------------------------------------------------------------------------------
        0xC615_500C    mip_adc03 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc03, reg_admd_apll_pdb, 0x0); //AAD PLL power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc03, reg_admd_apll_m, 0x19);
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc03);

    /*-----------------------------------------------------------------------------------------
        0xC615_5010    mip_adc04 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc04);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc04, reg_admd_apll_odpre, 0x19);
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc04);

    //delay before sw reset control
    udelay (100);

    //delay 200ns before set syncon 1.
    udelay (100);

    // not to set pdb, set syncon 1.
//    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
//    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_syncon, 0x1);
//    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_01);

    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc00);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_pdb, 0x1);    //AAD ADC  power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc00, reg_admd_a_bias_pdb, 0x1);       //AAD ADC BIAS power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc00);

    CTOP_CTRL_M23Ax_RdFL (MIP_ADC_CTRL_BMC, mip_adc03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ADC_CTRL_BMC, mip_adc03, reg_admd_apll_pdb, 0x1); //AAD PLL power down (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_WrFL (MIP_ADC_CTRL_BMC, mip_adc03);


    // M23 : 0: dto1, 1: dto2,    4: apll(a),  5: apll(b), 6: earc, 7: dto0
    //Register Setting for AUDIO CLK
    // aud_main_clk : apll(a)
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud16);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud16, reg_sel0_aclk_div, 0x5);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud16);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud17);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud17, reg_sel0_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud17);

    // aud_spdif_clk : dto0
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud18);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud18, reg_sel1_aclk_div, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud18);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud19);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud19, reg_sel1_aclk_src, 0x7);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud19);

    // aud_arc_clk : earc_pll
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud20);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud20, reg_sel2_aclk_div, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud20);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud21);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud21, reg_sel2_aclk_src, 0x6);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud21);

    // aud_hdp_clk : apll(a)
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud22);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud22, reg_sel3_aclk_div, 0x5);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud22);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud23);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud23, reg_sel3_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud23);

    // pdm_clk
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud24);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud24, reg_sel4_aclk_div, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud24);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud25);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud25, reg_sel4_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud25);

    // pdl_div_sel
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud15);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud15, reg_aud__pdm_div_sel, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud15);

    // pdl_clk sel mux (24.576MHz)
    CTOP_CTRL_M23Ax_RdFL (SCRG_CTRL_PDM, crg_pdm04);
    CTOP_CTRL_M23Ax_Wr01 (SCRG_CTRL_PDM, crg_pdm04, reg_pdm_pdm_clk_sel, 0x1);
    CTOP_CTRL_M23Ax_WrFL (SCRG_CTRL_PDM, crg_pdm04);

    // mlckb_auad
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud26);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud26, reg_sel5_aclk_div, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud26);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud27);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud27, reg_sel5_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud27);

    // mclk2_clk0
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud28);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud28, reg_sel6_aclk_div, 0x5);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud28);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud29);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud29, reg_sel6_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud29);

    // mclk2_clk1
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud30);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud30, reg_sel7_aclk_div, 0x5);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud30);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud31);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud31, reg_sel7_aclk_src, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud31);

    // CTOP SYN Setting
    CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_0);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_0, reg_sel_inv_aclk_mux_mip_dig, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_0, reg_sel_inv_mclk0, 0x0);
    CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_0);

    //DTO Seting for AUDIO CLK Generation
    //Setting A-DTO 0 clock
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud03);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud03, reg_adto0_add_value_pos, CLOCK_48KHZ);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud03);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud04);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud04, reg_adto0_err_value_pos, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud04);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud05);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud05, reg_adto0_swrst_adto, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud05);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud06);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud06, reg_adto0_sync_update, 1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud06);

    //Setting A-DTO 1 clock
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud07);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud07, reg_adto1_add_value_pos, CLOCK_48KHZ);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud07);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud08);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud08, reg_adto1_err_value_pos, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud08);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud09);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud09, reg_adto1_swrst_adto, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud09);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud10);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud10, reg_adto1_sync_update, 1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud10);

    //Setting A-DTO 2 clock for WOV Control.    // for pdm
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud11);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud11, reg_adto2_add_value_pos, 0xFBA8826);   // 24.576 MHz
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud11);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud12);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud12, reg_adto2_err_value_pos, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud12);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud13);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud13, reg_adto2_swrst_adto, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud13);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud14);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud14, reg_adto2_sync_update, 1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud14);

    //Enable D-DTO clock for CTOP Control for toggle.
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud14);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud14, reg_adto2_sync_update, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud14);
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud10);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud10, reg_adto1_sync_update, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud10);

    //Enable D-DTO clock for CTOP Control for toggle.
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud14);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud14, reg_adto2_sync_update, 0x1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud14);
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud10);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud10, reg_adto1_sync_update, 0x1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud10);

    //CRG_TOP apll enable
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, crg_top_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, crg_top_00, reg_apll_pll_pdb_ctrl, 0x1);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, crg_top_00);

    //delay before sw reset control
    udelay (100);

    //SW reset setting for mixed-IP block
    CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auad, 0x0);
    CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud09);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud09, reg_adto1_swrst_adto, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud09);
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud13);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud13, reg_adto2_swrst_adto, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud13);

    CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auda_f256fs_clk0, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auda_f256fs_clk1, 0x0);
    CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

    // fix QEVENTTWEN-22666 HT-E6750W audio output late 30 ~ 60 sec. 0xc930e4a4 [24,20,16,12] bit
    CTOP_CTRL_M23Ax_RdFL (IOMUX_CTRL_VD1, pad_vd103);
    CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd103, reg_pad_iec958out__ds0, 0x0);      // 0x1 24
    CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd103, reg_pad_iec958out__ds1, 0x1);      // 0x0 20
    CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd103, reg_pad_iec958out__ds2, 0x0);      // 0x0 16
    CTOP_CTRL_M23Ax_Wr01 (IOMUX_CTRL_VD1, pad_vd103, reg_pad_iec958out__ds3, 0x1);      // 0x0 12
    CTOP_CTRL_M23Ax_WrFL (IOMUX_CTRL_VD1, pad_vd103);

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
    unsigned int divint;
    unsigned int fcw;
    unsigned int out_div;
    unsigned int step;
    unsigned int icp;
    unsigned int icp_g;
};

static struct frpll_fout_settings frpll_fout_table[] = {
    /* *INDENT-OFF* */
    {48000,   0x3E,   0xAB367A,   0x1FE,  0x5591, 0x0, 0x1},
    {44100,   0x39,   0x93B3A6,   0x1FE,  0x5591, 0x0, 0x1},
    {32000,   0x29,   0xC779A6,   0x1FE,  0x5591, 0x0, 0x1},
    {192000,  0x3F,   0xE5C91D,   0x82,   0x15D0, 0x0, 0x1},
    {176400,  0x40,   0x1FFB48,   0x8E,   0x17D4, 0x0, 0x1},
    {128000,  0x40,   0x39ABF3,   0xC4,   0x20E3, 0x0, 0x1},
    {96000,   0x3E,   0x6C4C59,   0xFE,   0x2A9E, 0x0, 0x1},
    {88200,   0x40,   0x93964A,   0x11E,  0x3028, 0x0, 0x1},
    {64000,   0x40,   0x8D8EC9,   0x18A,  0x421B, 0x0, 0x1},
    /* *INDENT-ON* */
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

static int aud_tune_apll (unsigned int sample_rate, unsigned int dto_rate)
{
    unsigned int dto_clock;
    struct frpll_fout_settings *pSettings = NULL;

    // we use 6.144 MHz as 1/4 of 24.576 MHz
    pSettings = _aud_get_frpll_fout_settings (sample_rate * 4);

    dto_clock = pSettings->fcw + (dto_rate - CLOCK_CENTER) * pSettings->step * 4;
    info ("before: %x", CTOP_CTRL_M23Ax_Rd (CRG_TOP_CTRL, apll_frpll_01));
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, apll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_fcw, dto_clock);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, apll_frpll_01);

    info ("sample_rate = %dHz, dto_rate = %d, dto_clock = %d\n", sample_rate, dto_rate, dto_clock);

    return 0;
}

int aud_hal_set_speaker_sample_rate (unsigned int sample_rate)
{
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud22);

    if (sample_rate == 96000)
        CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud16, reg_sel0_aclk_div, 0x4);   // 0:bypass
    else
        CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud16, reg_sel0_aclk_div, 0x5);   // 0:1/2, 4 : Enable

    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud16);

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

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, apll_frpll_01);
    CTOP_CTRL_M23Ax_Rd01 (CRG_TOP_CTRL, apll_frpll_01, reg_apll_frpll_fcw, dto_clock);

    info ("fcw 0x%x\n", dto_clock);

    return dto_clock;
}

static int aud_set_earc_frpll (unsigned int sample_rate)
{
    struct frpll_fout_settings *pSettings = NULL;

    pSettings = _aud_get_frpll_fout_settings (sample_rate);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, crg_top_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, crg_top_00, reg_earcpll_pll_pdb_ctrl, 0);       //Analog & Digital power down
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, crg_top_00);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_out_div,
        pSettings->out_div);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_icp, pSettings->icp);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_00, reg_earcpll_frpll_divint,
        pSettings->divint);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_00);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_02);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_02, reg_earcpll_frpll_icp_g,
        pSettings->icp_g);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_02);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fcw, pSettings->fcw);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fout_en, 0x1);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_01);

    udelay (1);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, crg_top_00);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, crg_top_00, reg_earcpll_pll_pdb_ctrl, 1);       //Analog & Digital power down
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, crg_top_00);

    udelay (1);

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_syncon, 0x1);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_01);

    udelay (100);

    info ("sample_rate %d Hz divint(%x) fcw(%x) outdiv(%x)\n", sample_rate,
        pSettings->divint, pSettings->fcw, pSettings->out_div);

    return RET_OK;
}

static int aud_tune_earc_frpll (unsigned int sample_rate, unsigned int dto_rate)
{
    unsigned int dto_clock;
    struct frpll_fout_settings *pSettings = NULL;

    pSettings = _aud_get_frpll_fout_settings (sample_rate);

    dto_clock = pSettings->fcw + (dto_rate - CLOCK_CENTER) * pSettings->step;

    //Setting E-ARC Audio PLL clock for CTOP Control.
    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
    CTOP_CTRL_M23Ax_Wr01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fcw, dto_clock);
    CTOP_CTRL_M23Ax_WrFL (CRG_TOP_CTRL, earcpll_frpll_01);

    udelay (10);

    info ("sample_rate %d Hz, dto_rate %d, dto_clock 0x%x\n", sample_rate, dto_rate, dto_clock);

    return dto_rate;
}

int aud_hal_set_spdif_sample_rate (unsigned int sample_rate)
{
    //SPDIF(fs21clk)
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud18);

    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud18, reg_sel1_aclk_div, 0x0);       // 0:bypass

    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud18);

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
    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud03);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud03, reg_adto0_add_value_pos, dto_clock);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud03);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud04);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud04, reg_adto0_err_value_pos, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud04);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud06);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud06, reg_adto0_sync_update, 0);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud06);

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud06);
    CTOP_CTRL_M23Ax_Wr01 (MCRG_CTRL_AUD, crg_main_aud06, reg_adto0_sync_update, 1);
    CTOP_CTRL_M23Ax_WrFL (MCRG_CTRL_AUD, crg_main_aud06);

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

    CTOP_CTRL_M23Ax_RdFL (MCRG_CTRL_AUD, crg_main_aud03);
    CTOP_CTRL_M23Ax_Rd01 (MCRG_CTRL_AUD, crg_main_aud03, reg_adto0_add_value_pos, dto_clock);

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
    unsigned int dto_clock;

    CTOP_CTRL_M23Ax_RdFL (CRG_TOP_CTRL, earcpll_frpll_01);
    CTOP_CTRL_M23Ax_Rd01 (CRG_TOP_CTRL, earcpll_frpll_01, reg_earcpll_frpll_fcw, dto_clock);

    info ("fcw 0x%x\n", dto_clock);

    return dto_clock;
}

void aud_hal_switch_spdif_clock (bool onoff)
{
}
#endif
