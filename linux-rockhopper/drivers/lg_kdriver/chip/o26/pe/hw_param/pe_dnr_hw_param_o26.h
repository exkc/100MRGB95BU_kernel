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

/** @file pe_dnr_hw_param_o26.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_DNR_HW_PARAM_O26_H_
#define	_PE_DNR_HW_PARAM_O26_H_

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
#define PE_DNR_O26F22_OSD_DEC_TABLE_NUM (124)
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
#ifdef PE_HW_O26_BRINGUP
	PE_O26_DNR0_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCC290594
	PE_O26_DNR0_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCC2905A0
	PE_O26_DNR0_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCC2905A4
	PE_O26_DNR0_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCC2905A8
	PE_O26_DNR0_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCC2905AC
	PE_O26_DNR0_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCC2905B0
	PE_O26_DNR0_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCC2905B4
	PE_O26_DNR0_DETAIL_CTRL_T                                  detail_ctrl;	//0xCC2905B8
	PE_O26_DNR0_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCC2905BC
	PE_O26_DNR0_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCC2905C0
	PE_O26_DNR0_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCC2905C4
	PE_O26_DNR0_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCC2905C8
	PE_O26_DNR0_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCC2905CC
	PE_O26_DNR0_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCC2905D0
	PE_O26_DNR0_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCC2905D4
	PE_O26_DNR0_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCC2905D8
	PE_O26_DNR0_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCC2905DC
	PE_O26_DNR0_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCC2905E4
	PE_O26_DNR0_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCC2905E8
	PE_O26_DNR0_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCC2905F0
	PE_O26_DNR0_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCC2905F4
	PE_O26_DNR0_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCC2905F8
	PE_O26_DNR0_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCC290600
	PE_O26_DNR0_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCC290604
	PE_O26_DNR0_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCC290608
	PE_O26_DNR0_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCC29060C
	PE_O26_DNR0_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCC290610
	PE_O26_DNR0_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCC290638
	PE_O26_DNR0_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCC29063C
	PE_O26_DNR0_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCC290640
	PE_O26_DNR0_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCC29066C
	PE_O26_DNR0_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCC290670
	PE_O26_DNR0_DEC_LOWAPL_0_T                               dec_lowapl_0;	//0xCC290674
	PE_O26_DNR0_DEC_LOWAPL_1_T                               dec_lowapl_1;	//0xCC290678
	PE_O26_DNR0_DEC_LOWAPL_2_T                               dec_lowapl_2;	//0xCC29067C
	PE_O26_DNR0_DEC_LOWAPL_3_T                               dec_lowapl_3;	//0xCC290680
	PE_O26_DNR0_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCC290684
	PE_O26_DNR0_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCC290688
	PE_O26_DNR0_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCC29068C
	PE_O26_DNR0_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCC290690
	PE_O26_DNR0_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCC290694
	PE_O26_DNR0_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCC290698
	PE_O26_DNR0_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCC29069C
	PE_O26_DNR0_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCC2906A0
	PE_O26_DNR0_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCC2906A4
	PE_O26_DNR0_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCC2906A8
	PE_O26_DNR0_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCC2906AC
	PE_O26_DNR0_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCC2906B0
	PE_O26_DNR0_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCC2906B4
	PE_O26_DNR0_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCC2906B8
	PE_O26_DNR0_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCC2906BC
	PE_O26_DNR0_AC_BNR_15_T                                      ac_bnr_15;	//0xCC290730
	PE_O26_DNR0_AC_BNR_16_T                                      ac_bnr_16;	//0xCC290734
	PE_O26_DNR0_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCC290764
	PE_O26_DNR0_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCC290768
	PE_O26_DNR0_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCC29076C
	PE_O26_DNR0_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCC290770
	PE_O26_DNR0_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCC290774
	PE_O26_DNR0_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCC290778
	PE_O26_DNR0_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCC29077C
	PE_O26_DNR0_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCC290780
	PE_O26_DNR0_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCC290784
	PE_O26_DNR0_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCC290788
	PE_O26_DNR0_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCC29078C
	PE_O26_DNR0_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCC290790
	PE_O26_DNR0_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCC290794
	PE_O26_DNR0_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCC290798
	PE_O26_DNR0_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCC29079C
	PE_O26_DNR0_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCC2907A8
	PE_O26_DNR0_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCC2907AC
	PE_O26_DNR0_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCC2907B0
	PE_O26_DNR0_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCC2907B4
	PE_O26_DNR0_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCC2907B8
	PE_O26_DNR0_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCC2907BC
	PE_O26_DNR0_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCC2907C0
	PE_O26_DNR0_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCC2907C4
	PE_O26_DNR0_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCC2907C8
	PE_O26_DNR0_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCC2907CC
	PE_O26_DNR0_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCC2907D0
	PE_O26_DNR0_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCC2907D4
	PE_O26_DNR0_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCC2907D8
	PE_O26_DNR0_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCC2907DC
	PE_O26_DNR0_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCC2907E0
	PE_O26_DNR0_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCC2907E4
	PE_O26_DNR0_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCC2907E8
	PE_O26_DNR0_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCC2907EC
	PE_O26_DNR0_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCC2907F0
	PE_O26_DNR0_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCC2907F4
	PE_O26_DNR0_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCC2907F8
	PE_O26_DNR0_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCC2907FC
	PE_O26_DNR0_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCC290800
	PE_O26_DNR0_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCC290804
	PE_O26_DNR0_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCC290808
	PE_O26_DNR0_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCC29080C
	PE_O26_DNR0_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCC290810
	PE_O26_DNR0_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCC290814
	PE_O26_DNR0_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCC290818
	PE_O26_DNR0_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCC29081C
	PE_O26_DNR0_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCC290820
	PE_O26_DNR0_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCC290824
	PE_O26_DNR0_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCC290828
	PE_O26_DNR0_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCC29082C
	PE_O26_DNR0_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCC290830
	PE_O26_DNR0_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCC290834
	PE_O26_DNR0_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCC290838
	PE_O26_DNR0_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCC29083C
	PE_O26_DNR0_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCC290840
	PE_O26_DNR0_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCC290844
	PE_O26_DNR0_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCC290848
	PE_O26_DNR0_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCC29084C
	PE_O26_DNR0_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCC290850
	PE_O26_DNR0_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCC290854
	PE_O26_DNR0_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCC290858
	PE_O26_DNR0_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCC29085C
	PE_O26_DNR0_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCC290860
	PE_O26_DNR0_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCC290864
	PE_O26_DNR0_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCC290868
	PE_O26_DNR0_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCC29086C
	PE_O26_DNR0_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCC290870
	PE_O26_DNR0_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCC290874
	PE_O26_DNR0_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCC290878
	PE_O26_DNR0_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCC29087C
	PE_O26_DNR0_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCC290880
	PE_O26_DNR0_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCC290884
	PE_O26_DNR0_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCC290888
	PE_O26_DNR0_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCC29088C
	PE_O26_DNR0_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCC290890
	PE_O26_DNR0_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCC290894
	PE_O26_DNR0_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCC290898
	PE_O26_DNR0_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCC29089C
	PE_O26_DNR0_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCC2908A0
	PE_O26_DNR0_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCC2908A4
	PE_O26_DNR0_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCC2908A8
	PE_O26_DNR0_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCC2908AC
	PE_O26_DNR0_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCC2908B0
	PE_O26_DNR0_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCC2908B4
	PE_O26_DNR0_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCC2908B8
	PE_O26_DNR0_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCC2908BC
	PE_O26_DNR0_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCC2908C0
	PE_O26_DNR0_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCC2908C4
	PE_O26_DNR0_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCC2908C8
	PE_O26_DNR0_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCC2908CC
	PE_O26_DNR0_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCC2908D0
	PE_O26_DNR0_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCC2908D4
	PE_O26_DNR0_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCC2908D8
	PE_O26_DNR0_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCC2908DC
	PE_O26_DNR0_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCC2908E0
	PE_O26_DNR0_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCC2908E4
	PE_O26_DNR0_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCC2908E8
	PE_O26_DNR0_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCC2908EC
	PE_O26_DNR0_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCC2908F0
	PE_O26_DNR0_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC2908F4
	PE_O26_DNR0_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC2908F8
	PE_O26_DNR0_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC2908FC
	PE_O26_DNR0_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC290900
	PE_O26_DNR0_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC290904
	PE_O26_DNR0_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC290908
	PE_O26_DNR0_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC29090C
	PE_O26_DNR0_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC290910
	PE_O26_DNR0_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC290914
	PE_O26_DNR0_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC290918
	PE_O26_DNR0_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC29091C
	PE_O26_DNR0_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC290920
	PE_O26_DNR0_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC290924
	PE_O26_DNR0_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC290928
	PE_O26_DNR0_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC29092C
	PE_O26_DNR0_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC290930
	PE_O26_DNR0_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC290934
	PE_O26_DNR0_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC290938
	PE_O26_DNR0_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC29093C
	PE_O26_DNR0_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC290940
	PE_O26_DNR0_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC290944
	PE_O26_DNR0_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC290948
	PE_O26_DNR0_REG_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xCC29094C
	PE_O26_DNR0_REG_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xCC290950
	PE_O26_DNR0_REG_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xCC290954
	PE_O26_DNR0_REG_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xCC290958
	PE_O26_DNR0_REG_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xCC29095C
	PE_O26_DNR0_REG_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xCC290960
	PE_O26_DNR0_REG_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xCC290964
	PE_O26_DNR0_REG_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xCC29097C
	PE_O26_DNR0_REG_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xCC290980
	PE_O26_DNR0_REG_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xCC290984
	PE_O26_DNR0_REG_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xCC290988
	PE_O26_DNR0_REG_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xCC29098C
	PE_O26_DNR0_REG_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xCC290990
	PE_O26_DNR0_REG_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xCC290994
	PE_O26_DNR0_REG_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xCC290998
	PE_O26_DNR0_REG_DECON_CTRL_120_T                    reg_decon_ctrl_120;	//0xCC29099C
	PE_O26_DNR0_REG_DECON_CTRL_121_T                    reg_decon_ctrl_121;	//0xCC2909A0
	PE_O26_DNR0_REG_DECON_CTRL_122_T                    reg_decon_ctrl_122;	//0xCC2909A4
	PE_O26_DNR0_REG_DECON_CTRL_123_T                    reg_decon_ctrl_123;	//0xCC2909A8
	PE_O26_DNR0_REG_DECON_CTRL_124_T                    reg_decon_ctrl_124;	//0xCC2909AC
	PE_O26_DNR0_REG_DECON_CTRL_125_T                    reg_decon_ctrl_125;	//0xCC2909B0
	PE_O26_DNR0_REG_DECON_CTRL_126_T                    reg_decon_ctrl_126;	//0xCC2909B4
	PE_O26_DNR0_REG_DECON_CTRL_127_T                    reg_decon_ctrl_127;	//0xCC2909B8
	PE_O26_DNR0_REG_DECON_CTRL_128_T                    reg_decon_ctrl_128;	//0xCC2909BC
	PE_O26_DNR0_REG_DECON_CTRL_129_T                    reg_decon_ctrl_129;	//0xCC2909C0
	PE_O26_DNR0_REG_DECON_CTRL_130_T                    reg_decon_ctrl_130;	//0xCC2909C4
	PE_O26_DNR0_REG_DECON_CTRL_131_T                    reg_decon_ctrl_131;	//0xCC2909C8
	PE_O26_DNR0_REG_DECON_CTRL_132_T                    reg_decon_ctrl_132;	//0xCC2909CC
	PE_O26_DNR0_REG_DECON_CTRL_133_T                    reg_decon_ctrl_133;	//0xCC2909D0
	PE_O26_DNR0_REG_DECON_CTRL_134_T                    reg_decon_ctrl_134;	//0xCC2909D4
	PE_O26_DNR0_REG_DECON_CTRL_135_T                    reg_decon_ctrl_135;	//0xCC2909D8
	PE_O26_DNR0_REG_DECON_CTRL_136_T                    reg_decon_ctrl_136;	//0xCC2909DC
	PE_O26_DNR0_REG_DECON_CTRL_137_T                    reg_decon_ctrl_137;	//0xCC2909E0
	PE_O26_DNR0_REG_DECON_CTRL_138_T                    reg_decon_ctrl_138;	//0xCC2909E4
	PE_O26_DNR0_REG_DECON_CTRL_139_T                    reg_decon_ctrl_139;	//0xCC2909E8
	PE_O26_DNR0_REG_DECON_CTRL_140_T                    reg_decon_ctrl_140;	//0xCC2909EC
	PE_O26_DNR0_REG_DECON_CTRL_141_T                    reg_decon_ctrl_141;	//0xCC2909F0
	PE_O26_DNR0_REG_DECON_CTRL_142_T                    reg_decon_ctrl_142;	//0xCC2909F4
	PE_O26_DNR0_REG_DECON_CTRL_143_T                    reg_decon_ctrl_143;	//0xCC2909F8
	PE_O26_DNR0_REG_DECON_CTRL_144_T                    reg_decon_ctrl_144;	//0xCC2909FC
	PE_O26_DNR0_REG_DECON_CTRL_145_T                    reg_decon_ctrl_145;	//0xCC290A00
	PE_O26_DNR0_REG_DECON_CTRL_146_T                    reg_decon_ctrl_146;	//0xCC290A04
	PE_O26_DNR0_REG_DECON_CTRL_147_T                    reg_decon_ctrl_147;	//0xCC290A08
	PE_O26_DNR0_REG_DECON_CTRL_148_T                    reg_decon_ctrl_148;	//0xCC290A0C
	PE_O26_DNR0_REG_DECON_CTRL_149_T                    reg_decon_ctrl_149;	//0xCC290A10
	PE_O26_DNR0_REG_DECON_CTRL_150_T                    reg_decon_ctrl_150;	//0xCC290A14
	PE_O26_DNR0_REG_DECON_CTRL_151_T                    reg_decon_ctrl_151;	//0xCC290A18
	PE_O26_DNR0_REG_DECON_CTRL_152_T                    reg_decon_ctrl_152;	//0xCC290A1C
	PE_O26_DNR0_REG_DECON_CTRL_153_T                    reg_decon_ctrl_153;	//0xCC290A20
	PE_O26_DNR0_REG_DECON_CTRL_154_T                    reg_decon_ctrl_154;	//0xCC290A24
	PE_O26_DNR0_REG_DECON_CTRL_155_T                    reg_decon_ctrl_155;	//0xCC290A28
	PE_O26_DNR0_REG_DECON_CTRL_156_T                    reg_decon_ctrl_156;	//0xCC290A2C
	PE_O26_DNR0_REG_DECON_CTRL_157_T                    reg_decon_ctrl_157;	//0xCC290A30
	PE_O26_DNR0_REG_DECON_CTRL_158_T                    reg_decon_ctrl_158;	//0xCC290A34
	PE_O26_DNR0_REG_DECON_CTRL_159_T                    reg_decon_ctrl_159;	//0xCC290A38
	PE_O26_DNR0_REG_DECON_CTRL_160_T                    reg_decon_ctrl_160;	//0xCC290A3C
	PE_O26_DNR0_REG_DECON_CTRL_161_T                    reg_decon_ctrl_161;	//0xCC290A40
	PE_O26_DNR0_REG_DECON_CTRL_162_T                    reg_decon_ctrl_162;	//0xCC290A44
	PE_O26_DNR0_REG_DECON_CTRL_163_T                    reg_decon_ctrl_163;	//0xCC290A48
	PE_O26_DNR0_REG_DECON_CTRL_164_T                    reg_decon_ctrl_164;	//0xCC290A4C
	PE_O26_DNR0_REG_DECON_CTRL_165_T                    reg_decon_ctrl_165;	//0xCC290A50
	PE_O26_DNR0_REG_DECON_CTRL_166_T                    reg_decon_ctrl_166;	//0xCC290A54
	PE_O26_DNR0_REG_DECON_CTRL_167_T                    reg_decon_ctrl_167;	//0xCC290A58
	PE_O26_DNR0_REG_DECON_CTRL_168_T                    reg_decon_ctrl_168;	//0xCC290A5C
	PE_O26_DNR0_REG_DECON_CTRL_169_T                    reg_decon_ctrl_169;	//0xCC290A60
	PE_O26_DNR0_REG_DECON_CTRL_170_T                    reg_decon_ctrl_170;	//0xCC290A64
	PE_O26_DNR0_REG_DECON_CTRL_171_T                    reg_decon_ctrl_171;	//0xCC290A68
	PE_O26_DNR0_REG_DECON_CTRL_172_T                    reg_decon_ctrl_172;	//0xCC290A6C
	PE_O26_DNR0_REG_DECON_CTRL_173_T                    reg_decon_ctrl_173;	//0xCC290A70
	PE_O26_DNR0_REG_DECON_CTRL_174_T                    reg_decon_ctrl_174;	//0xCC290A74
	PE_O26_DNR0_REG_DECON_CTRL_175_T                    reg_decon_ctrl_175;	//0xCC290A78
	PE_O26_DNR0_REG_DECON_CTRL_176_T                    reg_decon_ctrl_176;	//0xCC290A7C
	PE_O26_DNR0_REG_DECON_CTRL_177_T                    reg_decon_ctrl_177;	//0xCC290A80
	PE_O26_DNR0_REG_DECON_CTRL_178_T                    reg_decon_ctrl_178;	//0xCC290A84
	PE_O26_DNR0_REG_DECON_CTRL_179_T                    reg_decon_ctrl_179;	//0xCC290A88
	PE_O26_DNR0_REG_DECON_CTRL_180_T                    reg_decon_ctrl_180;	//0xCC290A8C
	PE_O26_DNR0_REG_DECON_CTRL_181_T                    reg_decon_ctrl_181;	//0xCC290A90
	PE_O26_DNR0_REG_DECON_CTRL_182_T                    reg_decon_ctrl_182;	//0xCC290A94
#ifdef PE_HW_O26_REG_SMR_CTRL_00
	PE_O26_DNR0_REG_SMR_CTRL_00_T                          reg_smr_ctrl_00;	//0xCC290B00
#endif
	PE_O26_DNR0_REG_SMR_CTRL_01_T                          reg_smr_ctrl_01;	//0xCC290B04
	PE_O26_DNR0_REG_SMR_CTRL_02_T                          reg_smr_ctrl_02;	//0xCC290B08
	PE_O26_DNR0_REG_SMR_CTRL_03_T                          reg_smr_ctrl_03;	//0xCC290B0C
	PE_O26_DNR0_REG_SMR_CTRL_04_T                          reg_smr_ctrl_04;	//0xCC290B10
	PE_O26_DNR0_REG_SMR_CTRL_05_T                          reg_smr_ctrl_05;	//0xCC290B14
	PE_O26_DNR0_REG_SMR_CTRL_06_T                          reg_smr_ctrl_06;	//0xCC290B18
	PE_O26_DNR0_REG_SMR_CTRL_07_T                          reg_smr_ctrl_07;	//0xCC290B1C
	PE_O26_DNR0_REG_SMR_CTRL_08_T                          reg_smr_ctrl_08;	//0xCC290B20
	PE_O26_DNR0_REG_SMR_CTRL_09_T                          reg_smr_ctrl_09;	//0xCC290B24
	PE_O26_DNR0_REG_SMR_CTRL_10_T                          reg_smr_ctrl_10;	//0xCC290B28
	PE_O26_DNR0_REG_SMR_CTRL_11_T                          reg_smr_ctrl_11;	//0xCC290B2C
	PE_O26_DNR0_REG_SMR_CTRL_12_T                          reg_smr_ctrl_12;	//0xCC290B30
	PE_O26_DNR0_REG_SMR_CTRL_13_T                          reg_smr_ctrl_13;	//0xCC290B34
	PE_O26_DNR0_REG_SMR_CTRL_14_T                          reg_smr_ctrl_14;	//0xCC290B38
	PE_O26_DNR0_REG_SMR_CTRL_15_T                          reg_smr_ctrl_15;	//0xCC290B3C
	PE_O26_DNR0_REG_SMR_CTRL_16_T                          reg_smr_ctrl_16;	//0xCC290B40
	PE_O26_DNR0_REG_SMR_CTRL_17_T                          reg_smr_ctrl_17;	//0xCC290B44
	PE_O26_DNR0_REG_SMR_CTRL_18_T                          reg_smr_ctrl_18;	//0xCC290B48
	PE_O26_DNR0_REG_SMR_CTRL_19_T                          reg_smr_ctrl_19;	//0xCC290B4C
	PE_O26_DNR0_REG_SMR_CTRL_20_T                          reg_smr_ctrl_20;	//0xCC290B50
	PE_O26_DNR0_REG_SMR_CTRL_21_T                          reg_smr_ctrl_21;	//0xCC290B54
	PE_O26_DNR0_REG_SMR_CTRL_22_T                          reg_smr_ctrl_22;	//0xCC290B58
	PE_O26_DNR0_REG_SMR_CTRL_23_T                          reg_smr_ctrl_23;	//0xCC290B5C
	#endif
}PE_DNR_HW_PARAM_REG_O26_T;

/**
 *	dnr2nd hw param reg type
 */
 
typedef struct {
#ifdef PE_HW_O26_BRINGUP
	PE_O26_DNR1_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCC2C0594
	PE_O26_DNR1_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCC2C05A0
	PE_O26_DNR1_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCC2C05A4
	PE_O26_DNR1_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCC2C05A8
	PE_O26_DNR1_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCC2C05AC
	PE_O26_DNR1_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCC2C05B0
	PE_O26_DNR1_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCC2C05B4
	PE_O26_DNR1_DETAIL_CTRL_T                                  detail_ctrl;	//0xCC2C05B8
	PE_O26_DNR1_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCC2C05BC
	PE_O26_DNR1_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCC2C05C0
	PE_O26_DNR1_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCC2C05C4
	PE_O26_DNR1_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCC2C05C8
	PE_O26_DNR1_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCC2C05CC
	PE_O26_DNR1_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCC2C05D0
	PE_O26_DNR1_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCC2C05D4
	PE_O26_DNR1_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCC2C05D8
	PE_O26_DNR1_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCC2C05DC
	PE_O26_DNR1_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCC2C05E4
	PE_O26_DNR1_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCC2C05E8
	PE_O26_DNR1_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCC2C05F0
	PE_O26_DNR1_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCC2C05F4
	PE_O26_DNR1_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCC2C05F8
	PE_O26_DNR1_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCC2C0600
	PE_O26_DNR1_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCC2C0604
	PE_O26_DNR1_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCC2C0608
	PE_O26_DNR1_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCC2C060C
	PE_O26_DNR1_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCC2C0610
	PE_O26_DNR1_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCC2C0638
	PE_O26_DNR1_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCC2C063C
	PE_O26_DNR1_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCC2C0640
	PE_O26_DNR1_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCC2C066C
	PE_O26_DNR1_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCC2C0670
	PE_O26_DNR1_SC_BNR_CTRL_2_T                              sc_bnr_ctrl_2;	//0xCC2C0674
	PE_O26_DNR1_SC_BNR_CTRL_3_T                              sc_bnr_ctrl_3;	//0xCC2C0678
	PE_O26_DNR1_SC_BNR_CTRL_4_T                              sc_bnr_ctrl_4;	//0xCC2C067C
	PE_O26_DNR1_SC_BNR_CTRL_5_T                              sc_bnr_ctrl_5;	//0xCC2C0680
	PE_O26_DNR1_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCC2C0684
	PE_O26_DNR1_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCC2C0688
	PE_O26_DNR1_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCC2C068C
	PE_O26_DNR1_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCC2C0690
	PE_O26_DNR1_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCC2C0694
	PE_O26_DNR1_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCC2C0698
	PE_O26_DNR1_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCC2C069C
	PE_O26_DNR1_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCC2C06A0
	PE_O26_DNR1_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCC2C06A4
	PE_O26_DNR1_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCC2C06A8
	PE_O26_DNR1_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCC2C06AC
	PE_O26_DNR1_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCC2C06B0
	PE_O26_DNR1_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCC2C06B4
	PE_O26_DNR1_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCC2C06B8
	PE_O26_DNR1_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCC2C06BC
	PE_O26_DNR1_AC_BNR_15_T                                      ac_bnr_15;	//0xCC2C0730
	PE_O26_DNR1_AC_BNR_16_T                                      ac_bnr_16;	//0xCC2C0734
	PE_O26_DNR1_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCC2C0764
	PE_O26_DNR1_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCC2C0768
	PE_O26_DNR1_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCC2C076C
	PE_O26_DNR1_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCC2C0770
	PE_O26_DNR1_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCC2C0774
	PE_O26_DNR1_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCC2C0778
	PE_O26_DNR1_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCC2C077C
	PE_O26_DNR1_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCC2C0780
	PE_O26_DNR1_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCC2C0784
	PE_O26_DNR1_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCC2C0788
	PE_O26_DNR1_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCC2C078C
	PE_O26_DNR1_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCC2C0790
	PE_O26_DNR1_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCC2C0794
	PE_O26_DNR1_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCC2C0798
	PE_O26_DNR1_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCC2C079C
	PE_O26_DNR1_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCC2C07A8
	PE_O26_DNR1_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCC2C07AC
	PE_O26_DNR1_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCC2C07B0
	PE_O26_DNR1_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCC2C07B4
	PE_O26_DNR1_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCC2C07B8
	PE_O26_DNR1_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCC2C07BC
	PE_O26_DNR1_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCC2C07C0
	PE_O26_DNR1_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCC2C07C4
	PE_O26_DNR1_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCC2C07C8
	PE_O26_DNR1_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCC2C07CC
	PE_O26_DNR1_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCC2C07D0
	PE_O26_DNR1_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCC2C07D4
	PE_O26_DNR1_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCC2C07D8
	PE_O26_DNR1_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCC2C07DC
	PE_O26_DNR1_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCC2C07E0
	PE_O26_DNR1_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCC2C07E4
	PE_O26_DNR1_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCC2C07E8
	PE_O26_DNR1_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCC2C07EC
	PE_O26_DNR1_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCC2C07F0
	PE_O26_DNR1_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCC2C07F4
	PE_O26_DNR1_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCC2C07F8
	PE_O26_DNR1_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCC2C07FC
	PE_O26_DNR1_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCC2C0800
	PE_O26_DNR1_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCC2C0804
	PE_O26_DNR1_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCC2C0808
	PE_O26_DNR1_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCC2C080C
	PE_O26_DNR1_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCC2C0810
	PE_O26_DNR1_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCC2C0814
	PE_O26_DNR1_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCC2C0818
	PE_O26_DNR1_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCC2C081C
	PE_O26_DNR1_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCC2C0820
	PE_O26_DNR1_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCC2C0824
	PE_O26_DNR1_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCC2C0828
	PE_O26_DNR1_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCC2C082C
	PE_O26_DNR1_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCC2C0830
	PE_O26_DNR1_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCC2C0834
	PE_O26_DNR1_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCC2C0838
	PE_O26_DNR1_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCC2C083C
	PE_O26_DNR1_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCC2C0840
	PE_O26_DNR1_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCC2C0844
	PE_O26_DNR1_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCC2C0848
	PE_O26_DNR1_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCC2C084C
	PE_O26_DNR1_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCC2C0850
	PE_O26_DNR1_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCC2C0854
	PE_O26_DNR1_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCC2C0858
	PE_O26_DNR1_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCC2C085C
	PE_O26_DNR1_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCC2C0860
	PE_O26_DNR1_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCC2C0864
	PE_O26_DNR1_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCC2C0868
	PE_O26_DNR1_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCC2C086C
	PE_O26_DNR1_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCC2C0870
	PE_O26_DNR1_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCC2C0874
	PE_O26_DNR1_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCC2C0878
	PE_O26_DNR1_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCC2C087C
	PE_O26_DNR1_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCC2C0880
	PE_O26_DNR1_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCC2C0884
	PE_O26_DNR1_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCC2C0888
	PE_O26_DNR1_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCC2C088C
	PE_O26_DNR1_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCC2C0890
	PE_O26_DNR1_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCC2C0894
	PE_O26_DNR1_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCC2C0898
	PE_O26_DNR1_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCC2C089C
	PE_O26_DNR1_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCC2C08A0
	PE_O26_DNR1_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCC2C08A4
	PE_O26_DNR1_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCC2C08A8
	PE_O26_DNR1_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCC2C08AC
	PE_O26_DNR1_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCC2C08B0
	PE_O26_DNR1_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCC2C08B4
	PE_O26_DNR1_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCC2C08B8
	PE_O26_DNR1_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCC2C08BC
	PE_O26_DNR1_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCC2C08C0
	PE_O26_DNR1_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCC2C08C4
	PE_O26_DNR1_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCC2C08C8
	PE_O26_DNR1_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCC2C08CC
	PE_O26_DNR1_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCC2C08D0
	PE_O26_DNR1_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCC2C08D4
	PE_O26_DNR1_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCC2C08D8
	PE_O26_DNR1_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCC2C08DC
	PE_O26_DNR1_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCC2C08E0
	PE_O26_DNR1_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCC2C08E4
	PE_O26_DNR1_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCC2C08E8
	PE_O26_DNR1_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCC2C08EC
	PE_O26_DNR1_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCC2C08F0
	PE_O26_DNR1_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCC2C08F4
	PE_O26_DNR1_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCC2C08F8
	PE_O26_DNR1_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCC2C08FC
	PE_O26_DNR1_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCC2C0900
	PE_O26_DNR1_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCC2C0904
	PE_O26_DNR1_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCC2C0908
	PE_O26_DNR1_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCC2C090C
	PE_O26_DNR1_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCC2C0910
	PE_O26_DNR1_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCC2C0914
	PE_O26_DNR1_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCC2C0918
	PE_O26_DNR1_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCC2C091C
	PE_O26_DNR1_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCC2C0920
	PE_O26_DNR1_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCC2C0924
	PE_O26_DNR1_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCC2C0928
	PE_O26_DNR1_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCC2C092C
	PE_O26_DNR1_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCC2C0930
	PE_O26_DNR1_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCC2C0934
	PE_O26_DNR1_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCC2C0938
	PE_O26_DNR1_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCC2C093C
	PE_O26_DNR1_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCC2C0940
	PE_O26_DNR1_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCC2C0944
	PE_O26_DNR1_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCC2C0948
	#endif
}PE_DNR2ND_HW_PARAM_REG_O26_T;


/**
 *	led dnr hw param reg type
 */
 
typedef struct {
#ifdef PE_HW_O26_BRINGUP
	PE_O26_CCO_DECON_CTRL_0_T                       reg_decon_ctrl_0;	//0xCC862104
	PE_O26_CCO_DECON_CTRL_1_T                       reg_decon_ctrl_1;	//0xCC862108
	PE_O26_CCO_DECON_CTRL_2_T                       reg_decon_ctrl_2;	//0xCC86210C
	PE_O26_CCO_DECON_CTRL_3_T                       reg_decon_ctrl_3;	//0xCC862110
	PE_O26_CCO_DECON_CTRL_4_T                       reg_decon_ctrl_4;	//0xCC862114
	PE_O26_CCO_DECON_CTRL_5_T                       reg_decon_ctrl_5;	//0xCC862118
	PE_O26_CCO_DECON_CTRL_6_T                       reg_decon_ctrl_6;	//0xCC86211C
	PE_O26_CCO_DECON_CTRL_7_T                       reg_decon_ctrl_7;	//0xCC862120
	PE_O26_CCO_DECON_CTRL_8_T                       reg_decon_ctrl_8;	//0xCC862124
	PE_O26_CCO_DECON_CTRL_9_T                       reg_decon_ctrl_9;	//0xCC862128
	PE_O26_CCO_DECON_CTRL_10_T                     reg_decon_ctrl_10;	//0xCC86212C
	PE_O26_CCO_DECON_CTRL_11_T                     reg_decon_ctrl_11;	//0xCC862130
	PE_O26_CCO_DECON_CTRL_12_T                     reg_decon_ctrl_12;	//0xCC862134
	PE_O26_CCO_DECON_CTRL_13_T                     reg_decon_ctrl_13;	//0xCC862138
	PE_O26_CCO_DECON_CTRL_14_T                     reg_decon_ctrl_14;	//0xCC86213C
	PE_O26_CCO_DECON_CTRL_15_T                     reg_decon_ctrl_15;	//0xCC862140
	PE_O26_CCO_DECON_CTRL_16_T                     reg_decon_ctrl_16;	//0xCC862144
	PE_O26_CCO_DECON_CTRL_17_T                     reg_decon_ctrl_17;	//0xCC862148
	PE_O26_CCO_DECON_CTRL_18_T                     reg_decon_ctrl_18;	//0xCC86214C
	PE_O26_CCO_DECON_CTRL_19_T                     reg_decon_ctrl_19;	//0xCC862150
	PE_O26_CCO_DECON_CTRL_20_T                     reg_decon_ctrl_20;	//0xCC862154
	PE_O26_CCO_DECON_CTRL_21_T                     reg_decon_ctrl_21;	//0xCC862158
	PE_O26_CCO_DECON_CTRL_22_T                     reg_decon_ctrl_22;	//0xCC86215C
	PE_O26_CCO_DECON_CTRL_23_T                     reg_decon_ctrl_23;	//0xCC862160
	PE_O26_CCO_DECON_CTRL_24_T                     reg_decon_ctrl_24;	//0xCC8621BC
	PE_O26_CCO_DECON_CTRL_25_T                     reg_decon_ctrl_25;	//0xCC8621C0
	PE_O26_CCO_DECON_CTRL_26_T                     reg_decon_ctrl_26;	//0xCC8621C4
	PE_O26_CCO_DECON_CTRL_27_T                     reg_decon_ctrl_27;	//0xCC8621C8
	PE_O26_CCO_DECON_CTRL_28_T                     reg_decon_ctrl_28;	//0xCC8621CC
	PE_O26_CCO_DECON_CTRL_29_T                     reg_decon_ctrl_29;	//0xCC8621D0
	PE_O26_CCO_DECON_CTRL_30_T                     reg_decon_ctrl_30;	//0xCC8621D4
	PE_O26_CCO_DECON_CTRL_31_T                     reg_decon_ctrl_31;	//0xCC8621D8
	PE_O26_CCO_DECON_CTRL_32_T                     reg_decon_ctrl_32;	//0xCC8621DC
	PE_O26_CCO_DECON_CTRL_33_T                     reg_decon_ctrl_33;	//0xCC8621E0
	PE_O26_CCO_DECON_CTRL_34_T                     reg_decon_ctrl_34;	//0xCC8621E4
	PE_O26_CCO_DECON_CTRL_35_T                     reg_decon_ctrl_35;	//0xCC8621E8
	PE_O26_CCO_DECON_CTRL_36_T                     reg_decon_ctrl_36;	//0xCC8621EC
	PE_O26_CCO_DECON_CTRL_37_T                     reg_decon_ctrl_37;	//0xCC8621F0
	PE_O26_CCO_DECON_CTRL_38_T                     reg_decon_ctrl_38;	//0xCC8621F4
	PE_O26_CCO_DECON_CTRL_39_T                     reg_decon_ctrl_39;	//0xCC8621F8
	PE_O26_CCO_DECON_CTRL_40_T                     reg_decon_ctrl_40;	//0xCC8621FC
	PE_O26_CCO_DECON_CTRL_41_T                     reg_decon_ctrl_41;	//0xCC862200
	PE_O26_CCO_DECON_CTRL_42_T                     reg_decon_ctrl_42;	//0xCC862204
	PE_O26_CCO_DECON_CTRL_43_T                     reg_decon_ctrl_43;	//0xCC862208
	PE_O26_CCO_DECON_CTRL_44_T                     reg_decon_ctrl_44;	//0xCC86220C
	PE_O26_CCO_DECON_CTRL_45_T                     reg_decon_ctrl_45;	//0xCC862210
	PE_O26_CCO_DECON_CTRL_46_T                     reg_decon_ctrl_46;	//0xCC862214
	PE_O26_CCO_DECON_CTRL_47_T                     reg_decon_ctrl_47;	//0xCC862218
	PE_O26_CCO_DECON_CTRL_48_T                     reg_decon_ctrl_48;	//0xCC86221C
	PE_O26_CCO_DECON_CTRL_49_T                     reg_decon_ctrl_49;	//0xCC862220
	PE_O26_CCO_DECON_CTRL_50_T                     reg_decon_ctrl_50;	//0xCC862224
	PE_O26_CCO_DECON_CTRL_51_T                     reg_decon_ctrl_51;	//0xCC862228
	PE_O26_CCO_DECON_CTRL_52_T                     reg_decon_ctrl_52;	//0xCC86222C
	PE_O26_CCO_DECON_CTRL_53_T                     reg_decon_ctrl_53;	//0xCC862230
	PE_O26_CCO_DECON_CTRL_54_T                     reg_decon_ctrl_54;	//0xCC862234
	PE_O26_CCO_DECON_CTRL_55_T                     reg_decon_ctrl_55;	//0xCC862238
	PE_O26_CCO_DECON_CTRL_56_T                     reg_decon_ctrl_56;	//0xCC86223C
	PE_O26_CCO_DECON_CTRL_57_T                     reg_decon_ctrl_57;	//0xCC862240
	PE_O26_CCO_DECON_CTRL_58_T                     reg_decon_ctrl_58;	//0xCC862244
	PE_O26_CCO_DECON_CTRL_59_T                     reg_decon_ctrl_59;	//0xCC862248
	PE_O26_CCO_DECON_CTRL_60_T                     reg_decon_ctrl_60;	//0xCC86224C
	PE_O26_CCO_DECON_CTRL_61_T                     reg_decon_ctrl_61;	//0xCC862250
	PE_O26_CCO_DECON_CTRL_62_T                     reg_decon_ctrl_62;	//0xCC862254
	PE_O26_CCO_DECON_CTRL_63_T                     reg_decon_ctrl_63;	//0xCC862258
	PE_O26_CCO_DECON_CTRL_64_T                     reg_decon_ctrl_64;	//0xCC86225C
	PE_O26_CCO_DECON_CTRL_65_T                     reg_decon_ctrl_65;	//0xCC862260
	PE_O26_CCO_DECON_CTRL_66_T                     reg_decon_ctrl_66;	//0xCC862264
	PE_O26_CCO_DECON_CTRL_67_T                     reg_decon_ctrl_67;	//0xCC862268
	PE_O26_CCO_DECON_CTRL_68_T                     reg_decon_ctrl_68;	//0xCC86226C
	PE_O26_CCO_DECON_CTRL_69_T                     reg_decon_ctrl_69;	//0xCC862270
	PE_O26_CCO_DECON_CTRL_70_T                     reg_decon_ctrl_70;	//0xCC862274
	PE_O26_CCO_DECON_CTRL_71_T                     reg_decon_ctrl_71;	//0xCC862278
	PE_O26_CCO_DECON_CTRL_72_T                     reg_decon_ctrl_72;	//0xCC86227C
	PE_O26_CCO_DECON_CTRL_73_T                     reg_decon_ctrl_73;	//0xCC862280
	PE_O26_CCO_DECON_CTRL_74_T                     reg_decon_ctrl_74;	//0xCC862284
	PE_O26_CCO_DECON_CTRL_75_T                     reg_decon_ctrl_75;	//0xCC862288
	PE_O26_CCO_DECON_CTRL_76_T                     reg_decon_ctrl_76;	//0xCC86228C
	PE_O26_CCO_DECON_CTRL_77_T                     reg_decon_ctrl_77;	//0xCC862290
	PE_O26_CCO_DECON_CTRL_78_T                     reg_decon_ctrl_78;	//0xCC862294
	PE_O26_CCO_DECON_CTRL_79_T                     reg_decon_ctrl_79;	//0xCC862298
	PE_O26_CCO_DECON_CTRL_80_T                     reg_decon_ctrl_80;	//0xCC86229C
	PE_O26_CCO_DECON_CTRL_81_T                     reg_decon_ctrl_81;	//0xCC8622A0
	PE_O26_CCO_DECON_CTRL_82_T                     reg_decon_ctrl_82;	//0xCC8622A4
	PE_O26_CCO_DECON_CTRL_83_T                     reg_decon_ctrl_83;	//0xCC8622A8
	PE_O26_CCO_DECON_CTRL_84_T                     reg_decon_ctrl_84;	//0xCC8622AC
	PE_O26_CCO_DECON_CTRL_85_T                     reg_decon_ctrl_85;	//0xCC8622B0
	PE_O26_CCO_DECON_CTRL_86_T                     reg_decon_ctrl_86;	//0xCC8622B4
	PE_O26_CCO_DECON_CTRL_87_T                     reg_decon_ctrl_87;	//0xCC8622B8
	PE_O26_CCO_DECON_CTRL_88_T                     reg_decon_ctrl_88;	//0xCC8622BC
	PE_O26_CCO_DECON_CTRL_89_T                     reg_decon_ctrl_89;	//0xCC8622C0
	PE_O26_CCO_DECON_CTRL_90_T                     reg_decon_ctrl_90;	//0xCC8622C4
	PE_O26_CCO_DECON_CTRL_91_T                     reg_decon_ctrl_91;	//0xCC8622C8
	PE_O26_CCO_DECON_CTRL_92_T                     reg_decon_ctrl_92;	//0xCC8622CC
	PE_O26_CCO_DECON_CTRL_93_T                     reg_decon_ctrl_93;	//0xCC8622D0
	PE_O26_CCO_DECON_CTRL_94_T                     reg_decon_ctrl_94;	//0xCC8622D4
	PE_O26_CCO_DECON_CTRL_95_T                     reg_decon_ctrl_95;	//0xCC8622D8
	PE_O26_CCO_DECON_CTRL_96_T                     reg_decon_ctrl_96;	//0xCC8622DC
	PE_O26_CCO_DECON_CTRL_97_T                     reg_decon_ctrl_97;	//0xCC8622E0
	PE_O26_CCO_DECON_CTRL_98_T                     reg_decon_ctrl_98;	//0xCC8622E4
	PE_O26_CCO_DECON_CTRL_99_T                     reg_decon_ctrl_99;	//0xCC8622E8
	PE_O26_CCO_DECON_CTRL_100_T                   reg_decon_ctrl_100;	//0xCC8622EC
	PE_O26_CCO_DECON_CTRL_101_T                   reg_decon_ctrl_101;	//0xCC8622F0
	PE_O26_CCO_DECON_CTRL_102_T                   reg_decon_ctrl_102;	//0xCC8622F4
	PE_O26_CCO_DECON_CTRL_103_T                   reg_decon_ctrl_103;	//0xCC8622F8
	PE_O26_CCO_DECON_CTRL_104_T                   reg_decon_ctrl_104;	//0xCC8622FC
	PE_O26_CCO_DECON_CTRL_105_T                   reg_decon_ctrl_105;	//0xCC882200
	PE_O26_CCO_DECON_CTRL_106_T                   reg_decon_ctrl_106;	//0xCC882204
	PE_O26_CCO_DECON_CTRL_107_T                   reg_decon_ctrl_107;	//0xCC882208
	PE_O26_CCO_DECON_CTRL_108_T                   reg_decon_ctrl_108;	//0xCC88220C
	PE_O26_CCO_DECON_CTRL_109_T                   reg_decon_ctrl_109;	//0xCC882210
#endif
}PE_CCO_DNR_HW_PARAM_REG_O26_T;

/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_O26_T;

/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR2ND_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR2ND_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR2ND_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR2ND_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_DNR2ND_HW_PARAM_DATA_O26_T;

/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CCO_DNR_HW_PARAM_REG_O26_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CCO_DNR_HW_PARAM_REG_O26_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CCO_DNR_HW_PARAM_REG_O26_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CCO_DNR_HW_PARAM_REG_O26_T *data;
	} reg_data;
} PE_CCO_DNR_HW_PARAM_DATA_O26_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNR_HW_PARAM_O26_H_ */
