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
 *  audio codec hal driver
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
#include "logm.h"

#include "hal/hal_codec.h"
#include "hal/o26/regs.h"

/*------------------------------------------------------------------------------
    Constant Definitions
------------------------------------------------------------------------------*/
#define RESET_DELAY             (100)

/*------------------------------------------------------------------------------
    Macro Definitions
------------------------------------------------------------------------------*/
#define trace(fmt,args...)  logm_trace(aud_hal_codec,fmt,##args)
#define debug(fmt,args...)  logm_debug(aud_hal_codec,fmt,##args)
#define info(fmt,args...)   logm_info(aud_hal_codec,fmt,##args)
#define noti(fmt,args...)   logm_noti(aud_hal_codec,fmt,##args)
#define error(fmt,args...)  logm_error(aud_hal_codec,fmt,##args)

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
logm_define (aud_hal_codec, log_level_noti);

/*------------------------------------------------------------------------------
    Static Function Prototypes Declarations
------------------------------------------------------------------------------*/
#ifndef CHIP_TYPE_FPGA
static void _start_codec (void);
#endif

/*------------------------------------------------------------------------------
    Static Variables
------------------------------------------------------------------------------*/

/*==============================================================================
    Implementation Group
==============================================================================*/
#ifdef CHIP_TYPE_FPGA
int aud_hal_codec_init (void)
{
    return 0;
}

void aud_hal_codec_exit (void)
{
}

int aud_hal_codec_set_adc_port_number (unsigned int number)
{
    return 0;
}
#else
int aud_hal_codec_init (void)
{
#ifndef SUPPORT_SOUNDBAR
    //Set a ADC IP, DAC IP.(HP output).
    /*-----------------------------------------------------------------------------------------
        0xCC9E_3000    mip_acodec00 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec00);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_ic_vcom, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_ic_vbuf, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_ic_bgr, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_ft_mode, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_cnt_rdiv, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_aud_ccont, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_chop_freq_scf, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_chop_freq_d2s, 0X2);  //Audio DAC Chopping Frequency Control (2:0.768MHz) (b01 -> b10)(2019.05.28)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_chop_en, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_pdb_clk, 0x0);        //Audio DAC Clockgen Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_scfr, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_scfl, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_refpr, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_refpl, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_refr, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_refl, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_d2sr, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_ic_d2sl, 0X2);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec00);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_3004    mip_acodec01 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec01);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_pdb_dac, 0x0);        //Audio DAC Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_vcont_refp, 0x4);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_chop_en_scf, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_chop_en_refp, 0x0);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_chop_en_ref, 0x1);    //Audio DAC Chopping Enable(b0 -> b1)(2019.05.28)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_chop_en_d2s, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_aud_vcom_cont, 0X2);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_aud_sel_vref_out, 0x1);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_aud_res, 0x4);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec01);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_3008    mip_acodec02 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec02);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec02, reg_aud_pdb_bias, 0x0);        //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec02, reg_reserve_in2, 0x0);
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec02);

    /*-----------------------------------------------------------------------------------------
        0xCC9E_300C    mip_acodec03 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec03);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_quant, 0X2);       //Audio ADC QUANT Current Control
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_refp, 0x2);        //Audio ADC REEP
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_int2, 0x2);        //Audio ADC DSM Power Down Control
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_ref, 0x2);         //Audio ADC PGA REF buffer Power Down Control
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_int1, 0x2);        //Test : Audio ADC REFP Power Down Control
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec03, reg_auad_ic_pga, 0x2);         //Audio ADC PGA Power Down Control
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec03);

    /*-----------------------------------------------------------------------------
        0xC613_0000 LG1152_AUDIO_03
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_03);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_03, mutec, 0x3);   // For test
    ACE_REG_O26Ax_Wr01 (lg1152_audio_03, dem0, 0x0);    // Initial 0
    ACE_REG_O26Ax_WrFL (lg1152_audio_03);

    /*-----------------------------------------------------------------------------
        0xC613_0004 LG1152_AUDIO_04
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_04);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_04, out_dwa_on, 0x1);      // DAC output type select : Improve o26 ACODEC HP Path THD (0x0 -> 0x1) (2022.06.29)
    ACE_REG_O26Ax_Wr01 (lg1152_audio_04, dif0, 0x2);    // Initial 0 -> 2(vision.kim)
    ACE_REG_O26Ax_Wr01 (lg1152_audio_04, dif1, 0x0);    // Initial 0 -> open
    ACE_REG_O26Ax_Wr01 (lg1152_audio_04, test0, 0x0);   // For test
    ACE_REG_O26Ax_WrFL (lg1152_audio_04);

    /*-----------------------------------------------------------------------------
        0xC613_0008 LG1152_AUDIO_05
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_05);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_05, test1, 0x0);   // For test
    ACE_REG_O26Ax_Wr01 (lg1152_audio_05, sgm_zero_sel, 0x0);    // Initial 0
    ACE_REG_O26Ax_Wr01 (lg1152_audio_05, out_sel, 0x0); // for selecting output bit
    ACE_REG_O26Ax_WrFL (lg1152_audio_05);

    /*-----------------------------------------------------------------------------
        0xC613_000C LG1152_AUDIO_06
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x0);    // line dac ch0 volume control
    //ACE_REG_O26Ax_Wr01(lg1152_audio_06, dac0_vol_con, 0x3000);// Boost +12dB for Maximum Output Swing(sunsik.woo@lge.com, 2016-05-17)
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    /*-----------------------------------------------------------------------------
        0xC613_0010 LG1152_AUDIO_07
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_07);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_07, dac0_rate_cont, 0x8);  // line dac ch0 volume change rate control
    ACE_REG_O26Ax_WrFL (lg1152_audio_07);

    /*-----------------------------------------------------------------------------
        0xC613_0014 LG1152_AUDIO_08
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_08);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_08, dac0_rate_cont_mute, 0x1);     // line dac ch0 mute rate control
    ACE_REG_O26Ax_WrFL (lg1152_audio_08);

    /*-----------------------------------------------------------------------------
        0xC613_0018 LG1152_AUDIO_09
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_09);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_09, dac0_mute_ena, 0x1);   // line dac ch0 mute control
    ACE_REG_O26Ax_Wr01 (lg1152_audio_09, dac0_pop_dc_on_control, 0x1);  // line dac ch0 soft starter start control
    ACE_REG_O26Ax_Wr01 (lg1152_audio_09, dac0_dc_setup_byps, 0x0);      // line dac ch0 soft start rate control
    ACE_REG_O26Ax_WrFL (lg1152_audio_09);

    /*-----------------------------------------------------------------------------
        0xC613_001C LG1152_AUDIO_10
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_10);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_10, dac0_pop_con_rate, 0x8);       // line dac ch0 gain control signal
    ACE_REG_O26Ax_WrFL (lg1152_audio_10);

    /*-----------------------------------------------------------------------------
        0xC613_0034 LG1152_AUDIO_16
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_16);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_16, dac_pop_invert, 0x1);  // dac pop invert
    ACE_REG_O26Ax_Wr01 (lg1152_audio_16, dac_sclk_invert, 0x0); // dac sclk invert
    ACE_REG_O26Ax_Wr01 (lg1152_audio_16, dac_lrn_invert, 0x0);  // dac lrn invert
    ACE_REG_O26Ax_WrFL (lg1152_audio_16);

    /*-----------------------------------------------------------------------------
        0xC613_0058 LG1152_AUDIO_25
    -----------------------------------------------------------------------------*/
    ACE_REG_O26Ax_RdFL (lg1152_audio_25);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_25, dac0_dc_setup_cont_from_rtop, 0x1);    // line dac ch0 soft start rate control
    ACE_REG_O26Ax_WrFL (lg1152_audio_25);

    //SW workaround code for DAC Mute Off using Volume Setting.(0x3FF -> 0x002 -> 0x001 -> 0x000), 2017.07.04
    ACE_REG_O26Ax_RdFL (lg1152_audio_09);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_09, dac0_mute_ena, 0x0);   // 1 bit : Line DAC CH0 Mute Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_09);
#endif

#ifdef SUPPORT_SOUNDBAR
    // earc input
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch3_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch3 (1'b1) 1: gp5_in[7] (gp5_out[7])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch2_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch2 (1'b1) 1: gp5_in[6] (gp5_out[6])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch1_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch1 (1'b1) 1: gp5_in[5] (gp5_out[5])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch0_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch0 (1'b1) 1: gp5_in[4] (gp5_out[4])
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc64);

    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc65);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_dacsck_mux_sel, 0x2);      // 2: i2s_aud_dacsck/i2s_aud_extsck
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_daclrck_mux_sel, 0x2);     // 2: i2s_aud_daclrck/i2s_aud_extplrck
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc65);

    AUD_REG_RdFL (PERI_CTRL, aud_mon_sel);
    AUD_REG_WrFd (PERI_CTRL, aud_mon_sel, aud_mon_sel_3, 1);    // 0 : dacsck / daclrck pad oen enable (default), 1 : disable
    AUD_REG_WrFd (PERI_CTRL, aud_mon_sel, aud_mon_sel_2, 0);    // 0 : AEC sck/lrck <- external dacsck/daclrck (pad), 1 : <- internal dacsck/daclrck (default)
    AUD_REG_WrFL (PERI_CTRL, aud_mon_sel);

    // i2s input
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_pcmi3lrck_mux_sel, 0x0);  // 0: i2s_aud_pcmi3lrck (1'b1) 1: gp6_in[0] (gp6_out[0])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_pcmi3sck_mux_sel, 0x0);   // 0: i2s_aud_pcmi3sck (1'b1) 1: gp6_in[1] (gp6_out[1])
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc64);

    CTOP_CTRL_O26Ax_RdFL (IOMUX_CTRL_DPE, pad_dpe65);
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_DPE, pad_dpe65, reg_pad_edp_hpd1_mux_sel, 0x2);    // 0 : None/edptx_sink_hpd1, 1 : gp5_out[3]/gp5_in[3], 2 : None/i2s_aud_pcmi3lrch0 3, 4, 5 : None
    CTOP_CTRL_O26Ax_WrFL (IOMUX_CTRL_DPE, pad_dpe65);

    CTOP_CTRL_O26Ax_RdFL (IOMUX_CTRL_AUD, pad_aud65);
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio15_mux_sel, 0x3);  // 0: gp1_in[5] (gp1_out[5]), 3: i2s_aud_pcmi3lrch2 (1'b1)
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio14_mux_sel, 0x3);  // 0: gp1_in[4] (gp1_out[4]), 3: i2s_aud_pcmi3lrch1 (1'b1)
    CTOP_CTRL_O26Ax_WrFL (IOMUX_CTRL_AUD, pad_aud65);
#endif

    _start_codec ();

    return 0;
}

void aud_hal_codec_exit (void)
{
}

int aud_hal_codec_set_adc_port_number (unsigned int number)
{
//Not Support  for O26 ADC Port.
    error ("NO ADC Port = %d!!!!!\n", number);
    return 0;
}

#ifdef SUPPORT_SOUNDBAR
int aud_hal_codec_set_i2s_input (void)
{
    // earc input
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch3_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch3 (1'b1) 1: gp5_in[7] (gp5_out[7])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch2_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch2 (1'b1) 1: gp5_in[6] (gp5_out[6])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch1_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch1 (1'b1) 1: gp5_in[5] (gp5_out[5])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_aec_lrch0_mux_sel, 0x0);   // 0: i2s_aud_amp_daclrch0 (1'b1) 1: gp5_in[4] (gp5_out[4])
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc64);

    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc65);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_dacsck_mux_sel, 0x2);      // 2: i2s_aud_dacsck/i2s_aud_extsck
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc65, reg_pad_daclrck_mux_sel, 0x2);     // 2: i2s_aud_daclrck/i2s_aud_extplrck
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc65);

    AUD_REG_RdFL (PERI_CTRL, aud_mon_sel);
    AUD_REG_WrFd (PERI_CTRL, aud_mon_sel, aud_mon_sel_3, 1);    // 0 : dacsck / daclrck pad oen enable (default), 1 : disable
    AUD_REG_WrFd (PERI_CTRL, aud_mon_sel, aud_mon_sel_2, 0);    // 0 : AEC sck/lrck <- external dacsck/daclrck (pad), 1 : <- internal dacsck/daclrck (default)
    AUD_REG_WrFL (PERI_CTRL, aud_mon_sel);

    // i2s input
    CTOP_CTRL_O26Ax_RdFL (CPU_IOMUX_CTRL_WOC, pad_woc64);
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_pcmi3lrck_mux_sel, 0x0);  // 0: i2s_aud_pcmi3lrck (1'b1) 1: gp6_in[0] (gp6_out[0])
    CTOP_CTRL_O26Ax_Wr01 (CPU_IOMUX_CTRL_WOC, pad_woc64, reg_pad_pcmi3sck_mux_sel, 0x0);   // 0: i2s_aud_pcmi3sck (1'b1) 1: gp6_in[1] (gp6_out[1])
    CTOP_CTRL_O26Ax_WrFL (CPU_IOMUX_CTRL_WOC, pad_woc64);

    CTOP_CTRL_O26Ax_RdFL (IOMUX_CTRL_DPE, pad_dpe65);
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_DPE, pad_dpe65, reg_pad_edp_hpd1_mux_sel, 0x2);    // 0 : None/edptx_sink_hpd1, 1 : gp5_out[3]/gp5_in[3], 2 : None/i2s_aud_pcmi3lrch0 3, 4, 5 : None
    CTOP_CTRL_O26Ax_WrFL (IOMUX_CTRL_DPE, pad_dpe65);

    CTOP_CTRL_O26Ax_RdFL (IOMUX_CTRL_AUD, pad_aud65);
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio15_mux_sel, 0x3);  // 0: gp1_in[5] (gp1_out[5]), 3: i2s_aud_pcmi3lrch2 (1'b1)
    CTOP_CTRL_O26Ax_Wr01 (IOMUX_CTRL_AUD, pad_aud65, reg_pad_gpio14_mux_sel, 0x3);  // 0: gp1_in[4] (gp1_out[4]), 3: i2s_aud_pcmi3lrch1 (1'b1)
    CTOP_CTRL_O26Ax_WrFL (IOMUX_CTRL_AUD, pad_aud65);

    noti ("I2S PCMI3/AEC Port\n");
    return 0;
}
#endif

static void _start_codec (void)
{
#ifndef SUPPORT_SOUNDBAR
    //Set a ADC for Power On.
    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec01);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec01, reg_auda_pdb_dac, 0x1);        //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec01);

    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec00);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec00, reg_auda_pdb_clk, 0x1);        //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec00);

    CTOP_CTRL_O26Ax_RdFL (MIP_CTRL_ACODEC, mip_acodec02);
    CTOP_CTRL_O26Ax_Wr01 (MIP_CTRL_ACODEC, mip_acodec02, reg_aud_pdb_bias, 0x1);        //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_O26Ax_WrFL (MIP_CTRL_ACODEC, mip_acodec02);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    //O26 AUAD delete ?
    //SW workaround code for DAC Mute Off using Volume Setting.(0x3FF -> 0x002 -> 0x001 -> 0x000), 2017.07.04
    //CTOP_CTRL_O26Ax_RdFL (BND_CTRL_LNX0, bnd_lnx0_2);
    //CTOP_CTRL_O26Ax_Wr01 (BND_CTRL_LNX0, bnd_lnx0_2, reg_swrst_auda_f256fs_clk0, 0x1);  //audio codec : dac 0
    //CTOP_CTRL_O26Ax_WrFL (BND_CTRL_LNX0, bnd_lnx0_2);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x3FF);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    //O26 AUAD delete ?
    //CTOP_CTRL_O26Ax_RdFL (BND_CTRL_LNX0, bnd_lnx0_2);
    //CTOP_CTRL_O26Ax_Wr01 (BND_CTRL_LNX0, bnd_lnx0_2, reg_swrst_auda_f256fs_clk0, 0x0);  //audio codec : dac 0
    //CTOP_CTRL_O26Ax_WrFL (BND_CTRL_LNX0, bnd_lnx0_2);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x004);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x003);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x002);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x001);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_O26Ax_RdFL (lg1152_audio_06);
    ACE_REG_O26Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x000);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_O26Ax_WrFL (lg1152_audio_06);
#endif
}
#endif
