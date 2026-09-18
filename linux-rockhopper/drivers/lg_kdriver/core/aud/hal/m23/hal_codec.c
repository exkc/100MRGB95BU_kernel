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
    //Set a ADC IP, DAC IP.(HP output).
    /*-----------------------------------------------------------------------------------------
        0xC615_4000    mip_acodec00 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec00);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_ic_vcom, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_ic_vbuf, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_ic_bgr, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_ft_mode, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_cnt_rdiv, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_aud_ccont, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_chop_freq_scf, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_chop_freq_d2s, 0X2);      //Audio DAC Chopping Frequency Control (2:0.768MHz) (b01 -> b10)(2019.05.28)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_chop_en, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_pdb_clk, 0x0);    //Audio DAC Clockgen Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_scfr, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_scfl, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_refpr, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_refpl, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_refr, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_refl, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_d2sr, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_ic_d2sl, 0X2);
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec00);

    /*-----------------------------------------------------------------------------------------
        0xC615_4004    mip_acodec01 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec01);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_pdb_dac, 0x0);    //Audio DAC Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_vcont_refp, 0x4);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_chop_en_scf, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_chop_en_refp, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_chop_en_ref, 0x1);        //Audio DAC Chopping Enable(b0 -> b1)(2019.05.28)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_chop_en_d2s, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_aud_vcom_cont, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_aud_sel_vref_out, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_aud_res, 0x4);
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec01);

    /*-----------------------------------------------------------------------------------------
        0xC615_4008    mip_acodec02 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec02);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec02, reg_aud_pdb_bias, 0x0);    //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec02, reg_reserve_in2, 0x0);
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec02);

    /*-----------------------------------------------------------------------------------------
        0xC615_400C    mip_acodec03 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_pga_gcont, 0x6);  //Audio ADC PGA Gain Control from 000 to 111 in 2.5dB step (b101 -> b110)(2019.06.11)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_ic_quant, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_sel_pga, 0x3);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_adc_pdb, 0x0);    //Audio ADC DSM Power Down Control
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_pga_ref_pdb, 0x0);        //Audio ADC PGA REF buffer Power Down Control
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_refp_pdb, 0x0);   //Test : Audio ADC REFP Power Down Control
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_pga_pdb, 0x0);    //Audio ADC PGA Power Down Control
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);

    /*-----------------------------------------------------------------------------------------
        0xC615_4010    mip_acodec04 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec04);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ch1_sel, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_refp_en, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_en_int_pga, 0x0); //Audio ADC PGA COMMON internal ref buffer connection (b1 -> b0)(2019.06.11)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_pga_chop_en, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ic_pga, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ic_int1, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ic_ref, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_sdm_chop_en, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ic_int2, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec04, reg_auad_ic_refp, 0X2);
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec04);

    /*-----------------------------------------------------------------------------------------
        0xC615_4014    mip_acodec05 ''
    -----------------------------------------------------------------------------------------*/
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec05);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_chen_amp, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_en_ext, 0x1);     // Improve M23 ACODEC HP Path THD (0x0 -> 0x1) (2022.06.29)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_chen_cmfb, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_ch2_sel, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_sel_refp, 0X2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_reserve_in1, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_ch_out_enb, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_refn_en, 0x1);    //Audio ADC REFN Enable (0: external 1: internal VSS) (b0 -> b1)(2019.06.11)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_en_int, 0x0);     // Improve M23 ACODEC HP Path THD (0x1 -> 0x0) (2022.06.29)
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_refp_ch_en, 0x0);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_div_sel_sdm, 0x2);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_vcont_refp, 0x5);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_ref_chop_en, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_en_ext_pga, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_d_inv_enb, 0x1);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_mclk_en, 0x1);
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec05);

    /*-----------------------------------------------------------------------------
        0xCA83_2038 LG1152_AUDIO_17
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_17);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_17, cont, 0x0);    // I2S format selection
    ACE_REG_M23Ax_Wr01 (lg1152_audio_17, pol_con, 0x2); // I2S polarity control
    ACE_REG_M23Ax_WrFL (lg1152_audio_17);

    /*-----------------------------------------------------------------------------
        0xCA83_203C LG1152_AUDIO_18
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_18);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, twos_com, 0x1);        // Audio ADC two's complement data stream
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, dig_sel, 0x0); // 2bit digital filter out selection
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, testl, 0x0);   // Left channel(normal mode : low, test mode: high)
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, testr, 0x0);   // Right channel(normal mode : low, test mode: high)
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, testinl, 0x0); // For test : Left channel
    ACE_REG_M23Ax_Wr01 (lg1152_audio_18, testinr, 0x0); // For test : Right channel
    ACE_REG_M23Ax_WrFL (lg1152_audio_18);

    /*-----------------------------------------------------------------------------
        0xCA83_2040 LG1152_AUDIO_19
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_19);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_19, ladc_vol_con, 0x00);   // line adc volume control(youngjae83.jung, 2020-04-27)
    ACE_REG_M23Ax_WrFL (lg1152_audio_19);

    /*-----------------------------------------------------------------------------
        0xCA83_2044 LG1152_AUDIO_20
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_20);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_20, ladc_rate_cont, 0x08); // line adc volume change rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_20);

    /*-----------------------------------------------------------------------------
        0xCA83_2048 LG1152_AUDIO_21
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_21);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_21, ladc_rate_cont_mute, 0x8);     // line adc mute rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_21);

    /*-----------------------------------------------------------------------------
        0xCA83_204C LG1152_AUDIO_22
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_22);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_22, ladc_mute_ena, 0x1);   // line adc mute control
    ACE_REG_M23Ax_WrFL (lg1152_audio_22);

    /*-----------------------------------------------------------------------------
        0xCA83_2050 LG1152_AUDIO_23
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_23);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_23, codec_loop_back, 0x0); // line adc codec loop back test
    ACE_REG_M23Ax_WrFL (lg1152_audio_23);

    /*-----------------------------------------------------------------------------
        0xCA83_2054 LG1152_AUDIO_24
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_24);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_24, f64fs_clk_sel, 0x0);   // clock selection (0: invert f64fs_clk , 1: f64fs_clk)
    ACE_REG_M23Ax_WrFL (lg1152_audio_24);

    /*-----------------------------------------------------------------------------
        0xCA83_2000 LG1152_AUDIO_03
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_03);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_03, mutec, 0x3);   // For test
    ACE_REG_M23Ax_Wr01 (lg1152_audio_03, dem0, 0x0);    // Initial 0
    ACE_REG_M23Ax_WrFL (lg1152_audio_03);

    /*-----------------------------------------------------------------------------
        0xCA83_2004 LG1152_AUDIO_04
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_04);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_04, out_dwa_on, 0x1);      // DAC output type select : Improve M23 ACODEC HP Path THD (0x0 -> 0x1) (2022.06.29)
    ACE_REG_M23Ax_Wr01 (lg1152_audio_04, dif0, 0x2);    // Initial 0 -> 2(vision.kim)
    ACE_REG_M23Ax_Wr01 (lg1152_audio_04, dif1, 0x0);    // Initial 0 -> open
    ACE_REG_M23Ax_Wr01 (lg1152_audio_04, test0, 0x0);   // For test
    ACE_REG_M23Ax_WrFL (lg1152_audio_04);

    /*-----------------------------------------------------------------------------
        0xCA83_2008 LG1152_AUDIO_05
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_05);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_05, test1, 0x0);   // For test
    ACE_REG_M23Ax_Wr01 (lg1152_audio_05, sgm_zero_sel, 0x0);    // Initial 0
    ACE_REG_M23Ax_Wr01 (lg1152_audio_05, out_sel, 0x0); // for selecting output bit
    ACE_REG_M23Ax_WrFL (lg1152_audio_05);

    /*-----------------------------------------------------------------------------
        0xCA83_200C LG1152_AUDIO_06
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x0);    // line dac ch0 volume control
    //ACE_REG_M23Ax_Wr01(lg1152_audio_06, dac0_vol_con, 0x3000);// Boost +12dB for Maximum Output Swing(sunsik.woo@lge.com, 2016-05-17)
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    /*-----------------------------------------------------------------------------
        0xCA83_2010 LG1152_AUDIO_07
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_07);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_07, dac0_rate_cont, 0x8);  // line dac ch0 volume change rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_07);

    /*-----------------------------------------------------------------------------
        0xCA83_2014 LG1152_AUDIO_08
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_08);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_08, dac0_rate_cont_mute, 0x1);     // line dac ch0 mute rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_08);

    /*-----------------------------------------------------------------------------
        0xCA83_2018 LG1152_AUDIO_09
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_09);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_09, dac0_mute_ena, 0x1);   // line dac ch0 mute control
    ACE_REG_M23Ax_Wr01 (lg1152_audio_09, dac0_pop_dc_on_control, 0x1);  // line dac ch0 soft starter start control
    ACE_REG_M23Ax_Wr01 (lg1152_audio_09, dac0_dc_setup_byps, 0x0);      // line dac ch0 soft start rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_09);

    /*-----------------------------------------------------------------------------
        0xCA83_201C LG1152_AUDIO_10
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_10);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_10, dac0_pop_con_rate, 0x8);       // line dac ch0 gain control signal
    ACE_REG_M23Ax_WrFL (lg1152_audio_10);

    /*-----------------------------------------------------------------------------
        0xCA83_2034 LG1152_AUDIO_16
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_16);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_16, dac_pop_invert, 0x1);  // dac pop invert
    ACE_REG_M23Ax_Wr01 (lg1152_audio_16, dac_sclk_invert, 0x0); // dac sclk invert
    ACE_REG_M23Ax_Wr01 (lg1152_audio_16, dac_lrn_invert, 0x0);  // dac lrn invert
    ACE_REG_M23Ax_WrFL (lg1152_audio_16);

    /*-----------------------------------------------------------------------------
        0xCA83_2058 LG1152_AUDIO_25
    -----------------------------------------------------------------------------*/
    ACE_REG_M23Ax_RdFL (lg1152_audio_25);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_25, dac0_dc_setup_cont_from_rtop, 0x1);    // line dac ch0 soft start rate control
    ACE_REG_M23Ax_WrFL (lg1152_audio_25);

    //SW workaround code for DAC Mute Off using Volume Setting.(0x3FF -> 0x002 -> 0x001 -> 0x000), 2017.07.04
    ACE_REG_M23Ax_RdFL (lg1152_audio_09);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_09, dac0_mute_ena, 0x0);   // 1 bit : Line DAC CH0 Mute Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_09);

    _start_codec ();

    return 0;
}

void aud_hal_codec_exit (void)
{
}

int aud_hal_codec_set_adc_port_number (unsigned int number)
{
//M23 ADC Port number is only 1.
    if (number == 1)
    {
        ACE_REG_M23Ax_RdFL (lg1152_audio_22);
        ACE_REG_M23Ax_Wr01 (lg1152_audio_22, ladc_mute_ena, 1);
        ACE_REG_M23Ax_WrFL (lg1152_audio_22);

        /* Wait for pop-noise supression */
        udelay (RESET_DELAY);

        CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
        CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auad, 0x1);
        CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

        udelay (RESET_DELAY);

        /* Set a ADC port number */
        CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec05);
        CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec05, reg_auad_ch2_sel, number + 1); // Audio ADC Channel Selection
        CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec05);

        //workaround for not to mute off command(volume change) : 2013.02.02
        ACE_REG_M23Ax_RdFL (lg1152_audio_19);
        ACE_REG_M23Ax_Wr01 (lg1152_audio_19, ladc_vol_con, 0x01);       // line adc volume control(youngjae83.jung, 2019-06-11)
        ACE_REG_M23Ax_WrFL (lg1152_audio_19);

        udelay (RESET_DELAY);

        CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
        CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auad, 0x0);
        CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

        udelay (RESET_DELAY);

        ACE_REG_M23Ax_RdFL (lg1152_audio_22);
        ACE_REG_M23Ax_Wr01 (lg1152_audio_22, ladc_mute_ena, 0);
        ACE_REG_M23Ax_WrFL (lg1152_audio_22);

        /* To protect mute off timing : 2013.02.04 */
        usleep_range (RESET_DELAY * 30, RESET_DELAY * 31);      /* 30ms ~ 31ms */

        //workaround for not to mute off command(volume change) : 2013.02.02
        ACE_REG_M23Ax_RdFL (lg1152_audio_19);
        ACE_REG_M23Ax_Wr01 (lg1152_audio_19, ladc_vol_con, 0x00);       // line adc volume control(youngjae83.jung, 2019-06-11)
        ACE_REG_M23Ax_WrFL (lg1152_audio_19);
    }
    else
    {
//To Protect Hum Noise, ADC output is muted if ADC Port Number is not 1.
        ACE_REG_M23Ax_RdFL (lg1152_audio_22);
        ACE_REG_M23Ax_Wr01 (lg1152_audio_22, ladc_mute_ena, 1);
        ACE_REG_M23Ax_WrFL (lg1152_audio_22);

        noti ("ADC Mute ON(ADC Port = %d)\n", number);
        return RET_ERROR;
    }

    info ("ADC Port = %d\n", number);
    return 0;
}

static void _start_codec (void)
{
    //Set a ADC for Power On.
    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_pga_ref_pdb, 0x1);        //Audio ADC PGA REF buffer Power Down Control
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);

    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec01);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec01, reg_auda_pdb_dac, 0x1);    //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec01);

    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec00);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec00, reg_auda_pdb_clk, 0x1);    //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec00);

    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_adc_pdb, 0x1);    //Audio ADC DSM Power Down Control
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);

    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec03, reg_auad_pga_pdb, 0x1);    //Audio ADC PGA Power Down Control
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec03);

    CTOP_CTRL_M23Ax_RdFL (MIP_ACODEC_CTRL_BMC, mip_acodec02);
    CTOP_CTRL_M23Ax_Wr01 (MIP_ACODEC_CTRL_BMC, mip_acodec02, reg_aud_pdb_bias, 0x1);    //Audio Bias Power Down Control (0: power down, 1: power on)
    CTOP_CTRL_M23Ax_WrFL (MIP_ACODEC_CTRL_BMC, mip_acodec02);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    //SW workaround code for DAC Mute Off using Volume Setting.(0x3FF -> 0x002 -> 0x001 -> 0x000), 2017.07.04
    CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auda_f256fs_clk0, 0x1);    //audio codec : dac 0
    CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x3FF);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    CTOP_CTRL_M23Ax_RdFL (BND_CTRL_BMC, bnd_bmc_2);
    CTOP_CTRL_M23Ax_Wr01 (BND_CTRL_BMC, bnd_bmc_2, reg_swrst_auda_f256fs_clk0, 0x0);    //audio codec : dac 0
    CTOP_CTRL_M23Ax_WrFL (BND_CTRL_BMC, bnd_bmc_2);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x004);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x003);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x002);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x001);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);

    //add delay for clock setting
    udelay (RESET_DELAY * 2);

    ACE_REG_M23Ax_RdFL (lg1152_audio_06);
    ACE_REG_M23Ax_Wr01 (lg1152_audio_06, dac0_vol_con, 0x000);  // 14 bit : Line DAC CH1 Volume Control
    ACE_REG_M23Ax_WrFL (lg1152_audio_06);
}
#endif
