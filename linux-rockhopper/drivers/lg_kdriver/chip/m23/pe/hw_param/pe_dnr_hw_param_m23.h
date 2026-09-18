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

/** @file pe_dnr_hw_param_m23.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_DNR_HW_PARAM_M23_H_
#define	_PE_DNR_HW_PARAM_M23_H_

/*----------------------------------------------------------------------------
	Control Constants
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
    File Inclusions
----------------------------------------------------------------------------*/
#include "pe_reg.h"

#ifdef	__cplusplus
extern "C"
{
#endif /* __cplusplus */

/*----------------------------------------------------------------------------
	Constant Definitions
----------------------------------------------------------------------------*/
#define PE_DNR_M23F22_OSD_DEC_TABLE_NUM (124)
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
#ifdef PE_HW_M23_BRINGUP
	PE_M23_DNR_MAX_CTRL_T                             dnr_max_ctrl;				//0xC9018594
	PE_M23_ND0_VERI_SYS_VERI_0_T                      mnr_ctrl_0;				//mnr_ctrl_0 0xC90185A0 --> sys_veri_0 0xCC801100
	PE_M23_MNR_CTRL_1_T                               mnr_ctrl_1;				//0xC90185A4
	PE_M23_MNR_CTRL_2_T                               mnr_ctrl_2;				//0xC90185A8
	PE_M23_ND0_VERI_SYS_VERI_1_T                      mnr_ctrl_3;				//mnr_ctrl_3 0xC90185AC --> sys_veri_1 0xCC801104
	PE_M23_MNR_CTRL_4_T                               mnr_ctrl_4;				//0xC90185B0
	PE_M23_MNR_CTRL_5_T                               mnr_ctrl_5;				//0xC90185B4
	PE_M23_DETAIL_CTRL_T                              detail_ctrl;				//0xC90185B8
	PE_M23_DC_BNR_CTRL_0_T                            dc_bnr_ctrl_0;			//0xC90185BC
	PE_M23_DC_BNR_CTRL_1_T                            dc_bnr_ctrl_1;			//0xC90185C0
	PE_M23_DC_BNR_CTRL_2_T                            dc_bnr_ctrl_2;			//0xC90185C4
	PE_M23_DC_BNR_CTRL_3_T                            dc_bnr_ctrl_3;			//0xC90185C8
	PE_M23_DC_BNR_CTRL_4_T                            dc_bnr_ctrl_4;			//0xC90185CC
	PE_M23_DC_BNR_CTRL_5_T                            dc_bnr_ctrl_5;			//0xC90185D0
	PE_M23_AC_BNR_CTRL_0_T                            ac_bnr_ctrl_0;			//0xC90185D4
	PE_M23_AC_BNR_CTRL_1_T                            ac_bnr_ctrl_1;			//0xC90185D8
	PE_M23_AC_BNR_CTRL_2_T                            ac_bnr_ctrl_2;			//0xC90185DC
	PE_M23_AC_BNR_CTRL_3_T                            ac_bnr_ctrl_3;			//0xC90185E4
	PE_M23_AC_BNR_CTRL_4_T                            ac_bnr_ctrl_4;			//0xC90185E8
	PE_M23_AC_BNR_CTRL_5_T                            ac_bnr_ctrl_5;			//0xC90185F0
	PE_M23_AC_BNR_CTRL_6_T                            ac_bnr_ctrl_6;			//0xC90185F4
	PE_M23_AC_BNR_CTRL_7_T                            ac_bnr_ctrl_7;			//0xC90185F8
	PE_M23_AC_BNR_CTRL_8_T                            ac_bnr_ctrl_8;			//0xC9018600
	PE_M23_AC_BNR_CTRL_9_T                            ac_bnr_ctrl_9;			//0xC9018604
	PE_M23_AC_BNR_CTRL_10_T                           ac_bnr_ctrl_10;			//0xC9018608
	PE_M23_ND0_VERI_SYS_VERI_2_T                      mnr_ctrl_11;			    //reg_mnr_ctrl_11 0xC901860C --> sys_veri_3 0xCC801108
	PE_M23_ND0_VERI_SYS_VERI_3_T                      mnr_ctrl_12;			    //reg_mnr_ctrl_12 0xC9018610 --> sys_veri_4 0xCC80110C
	PE_M23_ELLIPSE_CTRL_0_T                           ellipse_ctrl_0;			//0xCC800638
	PE_M23_ELLIPSE_CTRL_1_T                           ellipse_ctrl_1;			//0xCC80063C
	PE_M23_ELLIPSE_CTRL_2_T                           ellipse_ctrl_2;			//0xCC800640
	PE_M23_ELLIPSE_CTRL_3_T                           ellipse_ctrl_3;			//0xCC80066C
	PE_M23_ELLIPSE_CTRL_4_T                           ellipse_ctrl_4;			//0xCC800670
	PE_M23_SC_BNR_CTRL_2_T                            sc_bnr_ctrl_2;			//0xC9018674
	PE_M23_SC_BNR_CTRL_3_T                            sc_bnr_ctrl_3;			//0xC9018678
	PE_M23_SC_BNR_CTRL_4_T                            sc_bnr_ctrl_4;			//0xC901867C
	PE_M23_SC_BNR_CTRL_5_T                            sc_bnr_ctrl_5;			//0xC9018680
	PE_M23_ELLIPSE_CTRL_5_T                           ellipse_ctrl_5;			//0xCC800684
	PE_M23_C_PRE_BLUR_CTRL_0_T                        c_pre_blur_ctrl_0;	    //0xCC800688
	PE_M23_ELLIPSE_CTRL_6_T                           ellipse_ctrl_6;			//0xCC80068C
	PE_M23_ELLIPSE_CTRL_7_T                           ellipse_ctrl_7;	        //0xCC800690
	PE_M23_ELLIPSE_CTRL_8_T                           ellipse_ctrl_8;			//0xCC800694
	PE_M23_ELLIPSE_CTRL_9_T                           ellipse_ctrl_9;			//0xCC800698
	PE_M23_AC_BNR_CTRL_13_T                           ac_bnr_ctrl_13;			//0xC901869C
	PE_M23_AC_BNR_CTRL_14_T                           ac_bnr_ctrl_14;			//0xC90186A0
	PE_M23_DC_BNR_CTRL_6_T                            dc_bnr_ctrl_6;			//0xC90186A4
	PE_M23_DC_BNR_CTRL_7_T                            dc_bnr_ctrl_7;			//0xC90186A8
	PE_M23_SQM_CTRL_0_T                               sqm_ctrl_0;				//0xC90186AC
	PE_M23_SQM_CTRL_1_T                               sqm_ctrl_1;				//0xC90186B0
	PE_M23_SQM_CTRL_2_T                               sqm_ctrl_2;				//0xC90186B4
	PE_M23_SQM_CTRL_3_T                               sqm_ctrl_3;				//0xC90186B8
	PE_M23_SQM_CTRL_4_T                               sqm_ctrl_4;				//0xC90186BC
	PE_M23_AC_BNR_15_T                                ac_bnr_15;				//0xC9018730
	PE_M23_AC_BNR_16_T                                ac_bnr_16;				//0xC9018734
	PE_M23_DECON_CTRL_0_T                         reg_decon_ctrl_0;		//0xC9018764
	PE_M23_DECON_CTRL_1_T                         reg_decon_ctrl_1;		//0xC9018768
	PE_M23_DECON_CTRL_2_T                         reg_decon_ctrl_2;		//0xC901876C
	PE_M23_DECON_CTRL_3_T                         reg_decon_ctrl_3;		//0xC9018770
	PE_M23_DECON_CTRL_4_T                         reg_decon_ctrl_4;		//0xC9018774
	PE_M23_DECON_CTRL_5_T                         reg_decon_ctrl_5;		//0xC9018778
	PE_M23_DECON_CTRL_6_T                         reg_decon_ctrl_6;		//0xC901877C
	PE_M23_DECON_CTRL_7_T                         reg_decon_ctrl_7;		//0xC9018780
	PE_M23_DECON_CTRL_8_T                         reg_decon_ctrl_8;		//0xC9018784
	PE_M23_DECON_CTRL_9_T                         reg_decon_ctrl_9;		//0xC9018788
	PE_M23_DECON_CTRL_10_T                        reg_decon_ctrl_10;	//0xC901878C
	PE_M23_DC_BNR_CTRL_8_T                        reg_dc_bnr_ctrl_8;	//0xC9018790
	PE_M23_DC_BNR_CTRL_9_T                        reg_dc_bnr_ctrl_9;	//0xC9018794
	PE_M23_DC_BNR_CTRL_10_T                       reg_dc_bnr_ctrl_10;	//0xC9018798
	PE_M23_DC_BNR_CTRL_11_T                       reg_dc_bnr_ctrl_11;	//0xC901879C
	PE_M23_MNR_CTRL_6_T                           reg_mnr_ctrl_6;			//0xC90187A8
	PE_M23_MNR_CTRL_7_T                           reg_mnr_ctrl_7;			//0xC90187AC
	PE_M23_MNR_CTRL_8_T                           reg_mnr_ctrl_8;			//0xC90187B0
	PE_M23_MNR_CTRL_9_T                           reg_mnr_ctrl_9;			//0xC90187B4
	PE_M23_MNR_CTRL_10_T                          reg_mnr_ctrl_10;		//0xC90187B8
	PE_M23_MNR_CTRL_11_T                          reg_mnr_ctrl_11;		//0xC90187BC
	PE_M23_MNR_CTRL_12_T                          reg_mnr_ctrl_12;		//0xC90187C0
	PE_M23_DECON_CTRL_11_T                        reg_decon_ctrl_11;	//0xC90187C4
	PE_M23_DECON_CTRL_12_T                        reg_decon_ctrl_12;	//0xC90187C8
	PE_M23_DECON_CTRL_13_T                        reg_decon_ctrl_13;	//0xC90187CC
	PE_M23_DECON_CTRL_14_T                        reg_decon_ctrl_14;	//0xC90187D0
	PE_M23_DECON_CTRL_15_T                        reg_decon_ctrl_15;	//0xC90187D4
	PE_M23_DECON_CTRL_16_T                        reg_decon_ctrl_16;	//0xC90187D8
	PE_M23_DECON_CTRL_17_T                        reg_decon_ctrl_17;	//0xC90187DC
	PE_M23_DECON_CTRL_18_T                        reg_decon_ctrl_18;	//0xC90187E0
	PE_M23_DECON_CTRL_19_T                        reg_decon_ctrl_19;	//0xC90187E4
	PE_M23_DECON_CTRL_20_T                        reg_decon_ctrl_20;	//0xC90187E8
	PE_M23_DECON_CTRL_21_T                        reg_decon_ctrl_21;	//0xC90187EC
	PE_M23_DECON_CTRL_22_T                        reg_decon_ctrl_22;	//0xC90187F0
	PE_M23_DECON_CTRL_23_T                        reg_decon_ctrl_23;	//0xC90187F4
	PE_M23_DECON_CTRL_24_T                        reg_decon_ctrl_24;	//0xC90187F8
	PE_M23_DECON_CTRL_25_T                        reg_decon_ctrl_25;	//0xC90187FC
	PE_M23_DECON_CTRL_26_T                        reg_decon_ctrl_26;	//0xC9018800
	PE_M23_DECON_CTRL_27_T                        reg_decon_ctrl_27;	//0xC9018804
	PE_M23_DECON_CTRL_28_T                        reg_decon_ctrl_28;	//0xC9018808
	PE_M23_DECON_CTRL_29_T                        reg_decon_ctrl_29;	//0xC901880C
	PE_M23_DECON_CTRL_30_T                        reg_decon_ctrl_30;	//0xC9018810
	PE_M23_DECON_CTRL_31_T                        reg_decon_ctrl_31;	//0xC9018814
	PE_M23_DECON_CTRL_32_T                        reg_decon_ctrl_32;	//0xC9018818
	PE_M23_DECON_CTRL_33_T                        reg_decon_ctrl_33;	//0xC901881C
	PE_M23_DECON_CTRL_34_T                        reg_decon_ctrl_34;	//0xC9018820
	PE_M23_DECON_CTRL_35_T                        reg_decon_ctrl_35;	//0xC9018824
	PE_M23_DECON_CTRL_36_T                        reg_decon_ctrl_36;	//0xC9018828
	PE_M23_DECON_CTRL_37_T                        reg_decon_ctrl_37;	//0xC901882C
	PE_M23_DECON_CTRL_38_T                        reg_decon_ctrl_38;	//0xC9018830
	PE_M23_DECON_CTRL_39_T                        reg_decon_ctrl_39;	//0xC9018834
	PE_M23_DECON_CTRL_40_T                        reg_decon_ctrl_40;	//0xC9018838
	PE_M23_DECON_CTRL_41_T                        reg_decon_ctrl_41;	//0xC901883C
	PE_M23_DECON_CTRL_42_T                        reg_decon_ctrl_42;	//0xC9018840
	PE_M23_DECON_CTRL_43_T                        reg_decon_ctrl_43;	//0xC9018844
	PE_M23_DECON_CTRL_44_T                        reg_decon_ctrl_44;	//0xC9018848
	PE_M23_DECON_CTRL_45_T                        reg_decon_ctrl_45;	//0xC901884C
	PE_M23_DECON_CTRL_46_T                        reg_decon_ctrl_46;	//0xC9018850
	PE_M23_DECON_CTRL_47_T                        reg_decon_ctrl_47;	//0xC9018854
	PE_M23_DECON_CTRL_48_T                        reg_decon_ctrl_48;	//0xC9018858
	PE_M23_DECON_CTRL_49_T                        reg_decon_ctrl_49;	//0xC901885C
	PE_M23_DECON_CTRL_50_T                        reg_decon_ctrl_50;	//0xC9018860
	PE_M23_DECON_CTRL_51_T                        reg_decon_ctrl_51;	//0xC9018864
	PE_M23_DECON_CTRL_52_T                        reg_decon_ctrl_52;	//0xC9018868
	PE_M23_DECON_CTRL_53_T                        reg_decon_ctrl_53;	//0xC901886C
	PE_M23_DECON_CTRL_54_T                        reg_decon_ctrl_54;	//0xC9018870
	PE_M23_DECON_CTRL_55_T                        reg_decon_ctrl_55;	//0xC9018874
	PE_M23_DECON_CTRL_56_T                        reg_decon_ctrl_56;	//0xC9018878
	PE_M23_DECON_CTRL_57_T                        reg_decon_ctrl_57;	//0xC901887C
	PE_M23_DECON_CTRL_58_T                        reg_decon_ctrl_58;	//0xC9018880
	PE_M23_DECON_CTRL_59_T                        reg_decon_ctrl_59;	//0xC9018884
	PE_M23_DECON_CTRL_60_T                        reg_decon_ctrl_60;	//0xC9018888
	PE_M23_DECON_CTRL_61_T                        reg_decon_ctrl_61;	//0xC901888C
	PE_M23_DECON_CTRL_62_T                        reg_decon_ctrl_62;	//0xC9018890
	PE_M23_DECON_CTRL_63_T                        reg_decon_ctrl_63;	//0xC9018894
	PE_M23_DC_BNR_CTRL_12_T                       reg_dc_bnr_ctrl_12;	//0xC9018898
	PE_M23_DC_BNR_CTRL_13_T                       reg_dc_bnr_ctrl_13;	//0xC901889C
	PE_M23_DC_BNR_CTRL_14_T                       reg_dc_bnr_ctrl_14;	//0xC90188A0
	PE_M23_DC_BNR_CTRL_15_T                       reg_dc_bnr_ctrl_15;	//0xC90188A4
	PE_M23_DECON_CTRL_64_T                        reg_decon_ctrl_64;	//0xC90188A8
	PE_M23_DECON_CTRL_65_T                        reg_decon_ctrl_65;	//0xC90188AC
	PE_M23_DECON_CTRL_66_T                        reg_decon_ctrl_66;	//0xC90188B0
	PE_M23_DECON_CTRL_67_T                        reg_decon_ctrl_67;	//0xC90188B4
	PE_M23_DECON_CTRL_68_T                        reg_decon_ctrl_68;	//0xC90188B8
	PE_M23_DECON_CTRL_69_T                        reg_decon_ctrl_69;	//0xC90188BC
	PE_M23_DECON_CTRL_70_T                        reg_decon_ctrl_70;	//0xC90188C0
	PE_M23_DECON_CTRL_71_T                        reg_decon_ctrl_71;	//0xC90188C4
	PE_M23_DECON_CTRL_72_T                        reg_decon_ctrl_72;	//0xC90188C8
	PE_M23_DECON_CTRL_73_T                        reg_decon_ctrl_73;	//0xC90188CC
	PE_M23_DECON_CTRL_74_T                        reg_decon_ctrl_74;	//0xC90188D0
	PE_M23_DECON_CTRL_75_T                        reg_decon_ctrl_75;	//0xC90188D4
	PE_M23_DECON_CTRL_76_T                        reg_decon_ctrl_76;	//0xC90188D8
	PE_M23_DECON_CTRL_77_T                        reg_decon_ctrl_77;	//0xC90188DC
	PE_M23_DECON_CTRL_78_T                        reg_decon_ctrl_78;	//0xC90188E0
	PE_M23_DECON_CTRL_79_T                        reg_decon_ctrl_79;	//0xC90188E4
	PE_M23_DECON_CTRL_80_T                        reg_decon_ctrl_80;	//0xC90188E8
	PE_M23_DECON_CTRL_81_T                        reg_decon_ctrl_81;	//0xC90188EC
	PE_M23_DECON_CTRL_82_T                        reg_decon_ctrl_82;	//0xC90188F0
	PE_M23_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC8008F4
	PE_M23_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC8008F8
	PE_M23_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC8008FC
	PE_M23_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC800900
	PE_M23_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC800904
	PE_M23_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC800908
	PE_M23_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC80090C
	PE_M23_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC800910
	PE_M23_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC800914
	PE_M23_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC800918
	PE_M23_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC80091C
	PE_M23_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC800920
	PE_M23_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC800924
	PE_M23_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC800928
	PE_M23_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC80092C
	PE_M23_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC800930
	PE_M23_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC800934
	PE_M23_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC800938
	PE_M23_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC80093C
	PE_M23_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC800940
	PE_M23_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC800944
	PE_M23_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC800948
	PE_M23_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xCC80094C
	PE_M23_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xCC800950
	PE_M23_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xCC800954
	PE_M23_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xCC800958
	PE_M23_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xCC80095C
	PE_M23_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xCC800960
	PE_M23_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xCC800964
	PE_M23_MNR_CTRL_13_T                                  mnr_ctrl_13;	//0xCC800968
	PE_M23_MNR_CTRL_14_T                                  mnr_ctrl_14;	//0xCC80096C
	PE_M23_MNR_CTRL_15_T                                  mnr_ctrl_15;	//0xCC800970
	PE_M23_MNR_CTRL_16_T                                  mnr_ctrl_16;	//0xCC800974
	PE_M23_MNR_CTRL_17_T                                  mnr_ctrl_17;	//0xCC800978
	PE_M23_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xCC80097C
	PE_M23_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xCC800980
	PE_M23_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xCC800984
	PE_M23_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xCC800988
	PE_M23_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xCC80098C
	PE_M23_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xCC800990
	PE_M23_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xCC800994
	PE_M23_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xCC800998
	#endif
}PE_DNR_HW_PARAM_REG_M23_T;

/**
 *	led dnr hw param reg type
 */
 
typedef struct {
#ifndef PE_HW_M23_BRINGUP
	PE_M23_REG_LED_DECON_CTRL_0_T                   reg_led_decon_ctrl_0;	//0xCC403804
	PE_M23_REG_LED_DECON_CTRL_1_T                   reg_led_decon_ctrl_1;	//0xCC403808
	PE_M23_REG_LED_DECON_CTRL_2_T                   reg_led_decon_ctrl_2;	//0xCC40380C
	PE_M23_REG_LED_DECON_CTRL_3_T                   reg_led_decon_ctrl_3;	//0xCC403810
	PE_M23_REG_LED_DECON_CTRL_4_T                   reg_led_decon_ctrl_4;	//0xCC403814
	PE_M23_REG_LED_DECON_CTRL_5_T                   reg_led_decon_ctrl_5;	//0xCC403818
	PE_M23_REG_LED_DECON_CTRL_6_T                   reg_led_decon_ctrl_6;	//0xCC40381C
	PE_M23_REG_LED_DECON_CTRL_7_T                   reg_led_decon_ctrl_7;	//0xCC403820
	PE_M23_REG_LED_DECON_CTRL_8_T                   reg_led_decon_ctrl_8;	//0xCC403824
	PE_M23_REG_LED_DECON_CTRL_9_T                   reg_led_decon_ctrl_9;	//0xCC403828
	PE_M23_REG_LED_DECON_CTRL_10_T                 reg_led_decon_ctrl_10;	//0xCC40382C
	PE_M23_REG_LED_DECON_CTRL_11_T                 reg_led_decon_ctrl_11;	//0xCC403830
	PE_M23_REG_LED_DECON_CTRL_12_T                 reg_led_decon_ctrl_12;	//0xCC403834
	PE_M23_REG_LED_DECON_CTRL_13_T                 reg_led_decon_ctrl_13;	//0xCC403838
	PE_M23_REG_LED_DECON_CTRL_14_T                 reg_led_decon_ctrl_14;	//0xCC40383C
	PE_M23_REG_LED_DECON_CTRL_15_T                 reg_led_decon_ctrl_15;	//0xCC403840
	PE_M23_REG_LED_DECON_CTRL_16_T                 reg_led_decon_ctrl_16;	//0xCC403844
	PE_M23_REG_LED_DECON_CTRL_17_T                 reg_led_decon_ctrl_17;	//0xCC403848
#endif
}PE_LED_DNR_HW_PARAM_REG_M23_T;


/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_M23_T;
/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_M23_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_M23_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_LED_DNR_HW_PARAM_REG_M23_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_LED_DNR_HW_PARAM_REG_M23_T *data;
	} reg_data;
} PE_LED_DNR_HW_PARAM_DATA_M23_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNR_HW_PARAM_M23_H_ */
