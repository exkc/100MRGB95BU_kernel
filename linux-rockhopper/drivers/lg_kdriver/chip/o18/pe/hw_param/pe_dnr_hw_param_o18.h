/*
 * SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
 * Copyright(c) 2013 by LG Electronics Inc.
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

/** @file pe_dnr_hw_param_o18.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_DNR_HW_PARAM_O18_H_
#define	_PE_DNR_HW_PARAM_O18_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

#include "pe_dnr_l_hd_i_default_o18.h"
#include "pe_dnr_l_hd_p_default_o18.h"
#include "pe_dnr_l_sd_default_o18.h"
#include "pe_dnr_l_ud_default_o18.h"
#include "pe_led_dnr_l_ud_default_o18.h"
#include "pe_led_dnr_l_hd_default_o18.h"
#include "pe_led_dnr_l_sd_default_o18.h"

#include "pe_sqm_dnr_init_o18.h"
#include "pe_sqm_dct_init_o18.h"


#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Macro Definitions
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    Type Definitions
----------------------------------------------------------------------------*/
/**
 *	dnr hw param reg type
 */
 
typedef struct {
	PE_O18_DNR_MAX_CTRL_T                             dnr_max_ctrl;	//0x0094
	PE_O18_DNR_DBAR_CTRL_T                            dnr_dbar_ctrl;	//0x0098
	PE_O18_MNR_CTRL_0_T                               mnr_ctrl_0;	//0x00A0
	PE_O18_MNR_CTRL_1_T                               mnr_ctrl_1;	//0x00A4
	PE_O18_MNR_CTRL_2_T                               mnr_ctrl_2;	//0x00A8
	PE_O18_MNR_CTRL_3_T                               mnr_ctrl_3;	//0x00AC
	PE_O18_MNR_CTRL_4_T                               mnr_ctrl_4;	//0x00B0
	PE_O18_MNR_CTRL_5_T                               mnr_ctrl_5;	//0x00B4
	PE_O18_DETAIL_CTRL_T                              detail_ctrl;	//0x00B8
	PE_O18_DC_BNR_CTRL_0_T                            dc_bnr_ctrl_0;	//0x00BC
	PE_O18_DC_BNR_CTRL_1_T                            dc_bnr_ctrl_1;	//0x00C0
	PE_O18_DC_BNR_CTRL_2_T                            dc_bnr_ctrl_2;	//0x00C4
	PE_O18_DC_BNR_CTRL_3_T                            dc_bnr_ctrl_3;	//0x00C8
	PE_O18_DC_BNR_CTRL_4_T                            dc_bnr_ctrl_4;	//0x00CC
	PE_O18_DC_BNR_CTRL_5_T                            dc_bnr_ctrl_5;	//0x00D0
	PE_O18_AC_BNR_CTRL_0_T                            ac_bnr_ctrl_0;	//0x00D4
	PE_O18_AC_BNR_CTRL_1_T                            ac_bnr_ctrl_1;	//0x00D8
	PE_O18_AC_BNR_CTRL_2_T                            ac_bnr_ctrl_2;	//0x00DC
	PE_O18_AC_BNR_CTRL_3_T                            ac_bnr_ctrl_3;	//0x00E4
	PE_O18_AC_BNR_CTRL_4_T                            ac_bnr_ctrl_4;	//0x00E8
	PE_O18_AC_BNR_CTRL_5_T                            ac_bnr_ctrl_5;	//0x00F0
	PE_O18_AC_BNR_CTRL_6_T                            ac_bnr_ctrl_6;	//0x00F4
	PE_O18_AC_BNR_CTRL_7_T                            ac_bnr_ctrl_7;	//0x00F8
	PE_O18_AC_BNR_CTRL_8_T                            ac_bnr_ctrl_8;	//0x0100
	PE_O18_AC_BNR_CTRL_9_T                            ac_bnr_ctrl_9;	//0x0104
	PE_O18_AC_BNR_CTRL_10_T                           ac_bnr_ctrl_10;	//0x0108
	PE_O18_AC_BNR_CTRL_11_T                           ac_bnr_ctrl_11;	//0x010C
	PE_O18_AC_BNR_CTRL_12_T                           ac_bnr_ctrl_12;	//0x0110
	PE_O18_SC_BNR_CTRL_0_T                            sc_bnr_ctrl_0;	//0x016C
	PE_O18_SC_BNR_CTRL_1_T                            sc_bnr_ctrl_1;	//0x0170
	PE_O18_SC_BNR_CTRL_2_T                            sc_bnr_ctrl_2;	//0x0174
	PE_O18_SC_BNR_CTRL_3_T                            sc_bnr_ctrl_3;	//0x0178
	PE_O18_SC_BNR_CTRL_4_T                            sc_bnr_ctrl_4;	//0x017C
	PE_O18_SC_BNR_CTRL_5_T                            sc_bnr_ctrl_5;	//0x0180
	PE_O18_SC_BNR_CTRL_6_T                            sc_bnr_ctrl_6;	//0x0184
	PE_O18_TEXTURE_CTRL_0_T                           texture_ctrl_0;	//0x018C
	PE_O18_AC_BNR_CTRL_13_T                           ac_bnr_ctrl_13;	//0x019C
	PE_O18_AC_BNR_CTRL_14_T                           ac_bnr_ctrl_14;	//0x01A0
	PE_O18_DC_BNR_CTRL_6_T                            dc_bnr_ctrl_6;	//0x01A4
	PE_O18_DC_BNR_CTRL_7_T                            dc_bnr_ctrl_7;	//0x01A8
	PE_O18_AC_BNR_15_T                                ac_bnr_15;	//0x0230
	PE_O18_AC_BNR_16_T                                ac_bnr_16;	//0x0234
	PE_O18_REG_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0264
	PE_O18_REG_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0268
	PE_O18_REG_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x026C
	PE_O18_REG_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0270
	PE_O18_REG_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0274
	PE_O18_REG_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0278
	PE_O18_REG_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x027C
	PE_O18_REG_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0280
	PE_O18_REG_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0284
	PE_O18_REG_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0288
	PE_O18_REG_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x028C
	PE_O18_REG_DC_BNR_CTRL_8_T                        reg_dc_bnr_ctrl_8;	//0x0290
	PE_O18_REG_DC_BNR_CTRL_9_T                        reg_dc_bnr_ctrl_9;	//0x0294
	PE_O18_REG_DC_BNR_CTRL_10_T                       reg_dc_bnr_ctrl_10;	//0x0298
	PE_O18_REG_DC_BNR_CTRL_11_T                       reg_dc_bnr_ctrl_11;	//0x029C
	PE_O18_REG_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x02A0
	PE_O18_REG_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x02A4
	PE_O18_REG_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x02A8
	PE_O18_REG_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x02AC
	PE_O18_REG_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x02B0
	PE_O18_REG_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x02B4
	PE_O18_REG_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x02B8
	PE_O18_REG_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x02BC
	PE_O18_REG_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x02C0
	PE_O18_REG_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x02C4
	PE_O18_REG_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x02C8
	PE_O18_REG_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x02CC
	PE_O18_REG_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x02D0
	PE_O18_REG_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x02D4
	PE_O18_REG_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x02D8
	PE_O18_REG_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x02DC
	PE_O18_REG_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x02E0
	PE_O18_REG_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x02E4
	PE_O18_REG_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x02E8
	PE_O18_REG_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x02EC
	PE_O18_REG_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x02F0
	PE_O18_REG_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x02F4
	PE_O18_REG_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x02F8
	PE_O18_REG_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x02FC
	PE_O18_REG_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x0300
	PE_O18_REG_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x0304
	PE_O18_REG_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x0308
	PE_O18_REG_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x030C
	PE_O18_REG_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x0310
	PE_O18_REG_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x0314
	PE_O18_REG_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x0318
	PE_O18_REG_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x031C
	PE_O18_REG_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0320
	PE_O18_REG_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x0324
	PE_O18_REG_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x0328
	PE_O18_REG_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x032C
	PE_O18_REG_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0330
	PE_O18_REG_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x0334
	PE_O18_REG_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x0338
	PE_O18_REG_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x033C
	PE_O18_REG_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0340
	PE_O18_REG_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x0344
	PE_O18_REG_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x0348
	PE_O18_REG_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x034C
	PE_O18_REG_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0350
	PE_O18_REG_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x0354
	PE_O18_REG_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x0358
	PE_O18_REG_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x035C
	PE_O18_REG_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0360
	PE_O18_REG_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x0364
	PE_O18_REG_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x0368
	PE_O18_REG_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x036C
	PE_O18_REG_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0370
	PE_O18_REG_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x0374
	PE_O18_REG_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x0378
	PE_O18_REG_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x037C
	PE_O18_REG_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x0380
	PE_O18_REG_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x0384
	PE_O18_REG_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x0388
	PE_O18_REG_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x038C
	PE_O18_REG_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x0390
	PE_O18_REG_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x0394
	PE_O18_REG_DC_BNR_CTRL_12_T                       reg_dc_bnr_ctrl_12;	//0x0398
	PE_O18_REG_DC_BNR_CTRL_13_T                       reg_dc_bnr_ctrl_13;	//0x039C
	PE_O18_REG_DC_BNR_CTRL_14_T                       reg_dc_bnr_ctrl_14;	//0x03A0
	PE_O18_REG_DC_BNR_CTRL_15_T                       reg_dc_bnr_ctrl_15;	//0x03A4
	PE_O18_REG_MNR_CTRL_6_T                           reg_mnr_ctrl_6;	//0x03A8
	PE_O18_REG_MNR_CTRL_7_T                           reg_mnr_ctrl_7;	//0x03AC
	PE_O18_REG_MNR_CTRL_8_T                           reg_mnr_ctrl_8;	//0x03B0
	PE_O18_REG_MNR_CTRL_9_T                           reg_mnr_ctrl_9;	//0x03B4
	PE_O18_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0x03B8
	PE_O18_REG_PSV_CTRL_0_T                           reg_psv_ctrl_0;	//0x03C4
	PE_O18_REG_PSV_CTRL_1_T                           reg_psv_ctrl_1;	//0x03C8
	PE_O18_REG_PSV_CTRL_2_T                           reg_psv_ctrl_2;	//0x03CC
	PE_O18_REG_PSV_CTRL_3_T                           reg_psv_ctrl_3;	//0x03D0
	PE_O18_REG_PSV_CTRL_4_T                           reg_psv_ctrl_4;	//0x03D4
	PE_O18_REG_PSV_CTRL_5_T                           reg_psv_ctrl_5;	//0x03D8
	PE_O18_REG_PSV_CTRL_6_T                           reg_psv_ctrl_6;	//0x03DC
	PE_O18_REG_PSV_CTRL_7_T                           reg_psv_ctrl_7;	//0x03E0
	PE_O18_REG_PSV_CTRL_8_T                           reg_psv_ctrl_8;	//0x03E4
	PE_O18_REG_PSV_CTRL_9_T                           reg_psv_ctrl_9;	//0x03E8
	PE_O18_REG_PSV_CTRL_10_T                          reg_psv_ctrl_10;	//0x03EC
	PE_O18_REG_PSV_CTRL_11_T                          reg_psv_ctrl_11;	//0x03F0
	PE_O18_REG_PSV_CTRL_12_T                          reg_psv_ctrl_12;	//0x03F4
	PE_O18_REG_PSV_CTRL_13_T                          reg_psv_ctrl_13;	//0x03F8
	
}PE_DNR_HW_PARAM_REG_O18_T;

/**
 *	led dnr hw param reg type
 */
 
typedef struct {
	PE_O18_REG_LED_DECON_CTRL_0_T                         reg_decon_ctrl_0;	//0x0004
	PE_O18_REG_LED_DECON_CTRL_1_T                         reg_decon_ctrl_1;	//0x0008
	PE_O18_REG_LED_DECON_CTRL_2_T                         reg_decon_ctrl_2;	//0x000C
	PE_O18_REG_LED_DECON_CTRL_3_T                         reg_decon_ctrl_3;	//0x0010
	PE_O18_REG_LED_DECON_CTRL_4_T                         reg_decon_ctrl_4;	//0x0014
	PE_O18_REG_LED_DECON_CTRL_5_T                         reg_decon_ctrl_5;	//0x0018
	PE_O18_REG_LED_DECON_CTRL_6_T                         reg_decon_ctrl_6;	//0x001C
	PE_O18_REG_LED_DECON_CTRL_7_T                         reg_decon_ctrl_7;	//0x0020
	PE_O18_REG_LED_DECON_CTRL_8_T                         reg_decon_ctrl_8;	//0x0024
	PE_O18_REG_LED_DECON_CTRL_9_T                         reg_decon_ctrl_9;	//0x0028
	PE_O18_REG_LED_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0x002C
	PE_O18_REG_LED_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0x0030
	PE_O18_REG_LED_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0x0034
	PE_O18_REG_LED_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0x0038
	PE_O18_REG_LED_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0x003C
	PE_O18_REG_LED_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0x0040
	PE_O18_REG_LED_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0x0044
	PE_O18_REG_LED_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0x0048
	PE_O18_REG_LED_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0x004C
	PE_O18_REG_LED_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0x0050
	PE_O18_REG_LED_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0x0054
	PE_O18_REG_LED_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0x0058
	PE_O18_REG_LED_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0x005C
	PE_O18_REG_LED_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0x0060
	PE_O18_REG_LED_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0x00BC
	PE_O18_REG_LED_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0x00C0
	PE_O18_REG_LED_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0x00C4
	PE_O18_REG_LED_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0x00C8
	PE_O18_REG_LED_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0x00CC
	PE_O18_REG_LED_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0x00D0
	PE_O18_REG_LED_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0x00D4
	PE_O18_REG_LED_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0x00D8
	PE_O18_REG_LED_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0x00DC
	PE_O18_REG_LED_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0x00E0
	PE_O18_REG_LED_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0x00E4
	PE_O18_REG_LED_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0x00E8
	PE_O18_REG_LED_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0x00EC
	PE_O18_REG_LED_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0x00F0
	PE_O18_REG_LED_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0x00F4
	PE_O18_REG_LED_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0x00F8
	PE_O18_REG_LED_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0x00FC
	PE_O18_REG_LED_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0x0100
	PE_O18_REG_LED_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0x0104
	PE_O18_REG_LED_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0x0108
	PE_O18_REG_LED_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0x010C
	PE_O18_REG_LED_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0x0110
	PE_O18_REG_LED_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0x0114
	PE_O18_REG_LED_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0x0118
	PE_O18_REG_LED_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0x011C
	PE_O18_REG_LED_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0x0120
	PE_O18_REG_LED_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0x0124
	PE_O18_REG_LED_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0x0128
	PE_O18_REG_LED_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0x012C
	PE_O18_REG_LED_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0x0130
	PE_O18_REG_LED_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0x0134
	PE_O18_REG_LED_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0x0138
	PE_O18_REG_LED_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0x013C
	PE_O18_REG_LED_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0x0140
	PE_O18_REG_LED_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0x0144
	PE_O18_REG_LED_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0x0148
	PE_O18_REG_LED_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0x014C
	PE_O18_REG_LED_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0x0150
	PE_O18_REG_LED_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0x0154
	PE_O18_REG_LED_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0x0158
	PE_O18_REG_LED_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0x015C
	PE_O18_REG_LED_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0x0160
	PE_O18_REG_LED_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0x0164
	PE_O18_REG_LED_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0x0168
	PE_O18_REG_LED_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0x016C
	PE_O18_REG_LED_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0x0170
	PE_O18_REG_LED_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0x0174
	PE_O18_REG_LED_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0x0178
	PE_O18_REG_LED_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0x017C
}PE_LED_DNR_HW_PARAM_REG_O18_T;

/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O18_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O18_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O18_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O18_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_O18_T;
/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_O18_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_O18_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_O18_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_O18_T *data;
	} reg_data;
} PE_LED_DNR_HW_PARAM_DATA_O18_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNR_HW_PARAM_O18_H_ */
