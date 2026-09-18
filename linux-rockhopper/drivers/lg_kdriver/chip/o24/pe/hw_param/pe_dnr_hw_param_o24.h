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

/** @file pe_dnr_hw_param_o24.h
 *
 *  hw header for picture enhance. ( used only within kdriver )
 *	
 *	@author		Seung-Jun,Youm(sj.youm@lge.com)
 *	@version	0.1
 *	@note		
 *	@date		2013.04.28
 *	@see		
 */

#ifndef	_PE_DNR_HW_PARAM_O24_H_
#define	_PE_DNR_HW_PARAM_O24_H_

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
#define PE_DNR_O24F22_OSD_DEC_TABLE_NUM (124)
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
#ifndef PE_HW_O24_BRINGUP
	PE_O24_DNR_DNR_MAX_CTRL_T                                dnr_max_ctrl;	//0xCCC60594
	PE_O24_DNR_MNR_CTRL_0_T                                    mnr_ctrl_0;	//0xCCC605A0
	PE_O24_DNR_MNR_CTRL_1_T                                    mnr_ctrl_1;	//0xCCC605A4
	PE_O24_DNR_MNR_CTRL_2_T                                    mnr_ctrl_2;	//0xCCC605A8
	PE_O24_DNR_MNR_CTRL_3_T                                    mnr_ctrl_3;	//0xCCC605AC
	PE_O24_DNR_MNR_CTRL_4_T                                    mnr_ctrl_4;	//0xCCC605B0
	PE_O24_DNR_MNR_CTRL_5_T                                    mnr_ctrl_5;	//0xCCC605B4
	PE_O24_DNR_DETAIL_CTRL_T                                  detail_ctrl;	//0xCCC605B8
	PE_O24_DNR_DC_BNR_CTRL_0_T                              dc_bnr_ctrl_0;	//0xCCC605BC
	PE_O24_DNR_DC_BNR_CTRL_1_T                              dc_bnr_ctrl_1;	//0xCCC605C0
	PE_O24_DNR_DC_BNR_CTRL_2_T                              dc_bnr_ctrl_2;	//0xCCC605C4
	PE_O24_DNR_DC_BNR_CTRL_3_T                              dc_bnr_ctrl_3;	//0xCCC605C8
	PE_O24_DNR_DC_BNR_CTRL_4_T                              dc_bnr_ctrl_4;	//0xCCC605CC
	PE_O24_DNR_DC_BNR_CTRL_5_T                              dc_bnr_ctrl_5;	//0xCCC605D0
	PE_O24_DNR_AC_BNR_CTRL_0_T                              ac_bnr_ctrl_0;	//0xCCC605D4
	PE_O24_DNR_AC_BNR_CTRL_1_T                              ac_bnr_ctrl_1;	//0xCCC605D8
	PE_O24_DNR_AC_BNR_CTRL_2_T                              ac_bnr_ctrl_2;	//0xCCC605DC
	PE_O24_DNR_AC_BNR_CTRL_3_T                              ac_bnr_ctrl_3;	//0xCCC605E4
	PE_O24_DNR_AC_BNR_CTRL_4_T                              ac_bnr_ctrl_4;	//0xCCC605E8
	PE_O24_DNR_AC_BNR_CTRL_5_T                              ac_bnr_ctrl_5;	//0xCCC605F0
	PE_O24_DNR_AC_BNR_CTRL_6_T                              ac_bnr_ctrl_6;	//0xCCC605F4
	PE_O24_DNR_AC_BNR_CTRL_7_T                              ac_bnr_ctrl_7;	//0xCCC605F8
	PE_O24_DNR_AC_BNR_CTRL_8_T                              ac_bnr_ctrl_8;	//0xCCC60600
	PE_O24_DNR_AC_BNR_CTRL_9_T                              ac_bnr_ctrl_9;	//0xCCC60604
	PE_O24_DNR_AC_BNR_CTRL_10_T                            ac_bnr_ctrl_10;	//0xCCC60608
	PE_O24_DNR_AC_BNR_CTRL_11_T                            ac_bnr_ctrl_11;	//0xCCC6060C
	PE_O24_DNR_AC_BNR_CTRL_12_T                            ac_bnr_ctrl_12;	//0xCCC60610
	PE_O24_DNR_ELLIPSE_CTRL_0_T                            ellipse_ctrl_0;	//0xCCC60638
	PE_O24_DNR_ELLIPSE_CTRL_1_T                            ellipse_ctrl_1;	//0xCCC6063C
	PE_O24_DNR_ELLIPSE_CTRL_2_T                            ellipse_ctrl_2;	//0xCCC60640
	PE_O24_DNR_ELLIPSE_CTRL_3_T                            ellipse_ctrl_3;	//0xCCC6066C
	PE_O24_DNR_ELLIPSE_CTRL_4_T                            ellipse_ctrl_4;	//0xCCC60670
	PE_O24_DNR0_DEC_LOWAPL_0_T                               dec_lowapl_0;	//0xCCC60674
	PE_O24_DNR0_DEC_LOWAPL_1_T                               dec_lowapl_1;	//0xCCC60678
	PE_O24_DNR0_DEC_LOWAPL_2_T                               dec_lowapl_2;	//0xCCC6067C
	PE_O24_DNR0_DEC_LOWAPL_3_T                               dec_lowapl_3;	//0xCCC60680
	PE_O24_DNR_ELLIPSE_CTRL_5_T                            ellipse_ctrl_5;	//0xCCC60684
	PE_O24_DNR_C_PRE_BLUR_CTRL_0_T                      c_pre_blur_ctrl_0;	//0xCCC60688
	PE_O24_DNR_ELLIPSE_CTRL_6_T                            ellipse_ctrl_6;	//0xCCC6068C
	PE_O24_DNR_ELLIPSE_CTRL_7_T                            ellipse_ctrl_7;	//0xCCC60690
	PE_O24_DNR_ELLIPSE_CTRL_8_T                            ellipse_ctrl_8;	//0xCCC60694
	PE_O24_DNR_ELLIPSE_CTRL_9_T                            ellipse_ctrl_9;	//0xCCC60698
	PE_O24_DNR_AC_BNR_CTRL_13_T                            ac_bnr_ctrl_13;	//0xCCC6069C
	PE_O24_DNR_AC_BNR_CTRL_14_T                            ac_bnr_ctrl_14;	//0xCCC606A0
	PE_O24_DNR_DC_BNR_CTRL_6_T                              dc_bnr_ctrl_6;	//0xCCC606A4
	PE_O24_DNR_DC_BNR_CTRL_7_T                              dc_bnr_ctrl_7;	//0xCCC606A8
	PE_O24_DNR_SQM_CTRL_0_T                                    sqm_ctrl_0;	//0xCCC606AC
	PE_O24_DNR_SQM_CTRL_1_T                                    sqm_ctrl_1;	//0xCCC606B0
	PE_O24_DNR_SQM_CTRL_2_T                                    sqm_ctrl_2;	//0xCCC606B4
	PE_O24_DNR_SQM_CTRL_3_T                                    sqm_ctrl_3;	//0xCCC606B8
	PE_O24_DNR_SQM_CTRL_4_T                                    sqm_ctrl_4;	//0xCCC606BC
	PE_O24_DNR_AC_BNR_15_T                                      ac_bnr_15;	//0xCCC60730
	PE_O24_DNR_AC_BNR_16_T                                      ac_bnr_16;	//0xCCC60734
	PE_O24_DNR_REG_DECON_CTRL_0_T                        reg_decon_ctrl_0;	//0xCCC60764
	PE_O24_DNR_REG_DECON_CTRL_1_T                        reg_decon_ctrl_1;	//0xCCC60768
	PE_O24_DNR_REG_DECON_CTRL_2_T                        reg_decon_ctrl_2;	//0xCCC6076C
	PE_O24_DNR_REG_DECON_CTRL_3_T                        reg_decon_ctrl_3;	//0xCCC60770
	PE_O24_DNR_REG_DECON_CTRL_4_T                        reg_decon_ctrl_4;	//0xCCC60774
	PE_O24_DNR_REG_DECON_CTRL_5_T                        reg_decon_ctrl_5;	//0xCCC60778
	PE_O24_DNR_REG_DECON_CTRL_6_T                        reg_decon_ctrl_6;	//0xCCC6077C
	PE_O24_DNR_REG_DECON_CTRL_7_T                        reg_decon_ctrl_7;	//0xCCC60780
	PE_O24_DNR_REG_DECON_CTRL_8_T                        reg_decon_ctrl_8;	//0xCCC60784
	PE_O24_DNR_REG_DECON_CTRL_9_T                        reg_decon_ctrl_9;	//0xCCC60788
	PE_O24_DNR_REG_DECON_CTRL_10_T                      reg_decon_ctrl_10;	//0xCCC6078C
	PE_O24_DNR_REG_DC_BNR_CTRL_8_T                      reg_dc_bnr_ctrl_8;	//0xCCC60790
	PE_O24_DNR_REG_DC_BNR_CTRL_9_T                      reg_dc_bnr_ctrl_9;	//0xCCC60794
	PE_O24_DNR_REG_DC_BNR_CTRL_10_T                    reg_dc_bnr_ctrl_10;	//0xCCC60798
	PE_O24_DNR_REG_DC_BNR_CTRL_11_T                    reg_dc_bnr_ctrl_11;	//0xCCC6079C
	PE_O24_DNR_REG_MNR_CTRL_6_T                            reg_mnr_ctrl_6;	//0xCCC607A8
	PE_O24_DNR_REG_MNR_CTRL_7_T                            reg_mnr_ctrl_7;	//0xCCC607AC
	PE_O24_DNR_REG_MNR_CTRL_8_T                            reg_mnr_ctrl_8;	//0xCCC607B0
	PE_O24_DNR_REG_MNR_CTRL_9_T                            reg_mnr_ctrl_9;	//0xCCC607B4
	PE_O24_DNR_REG_MNR_CTRL_10_T                          reg_mnr_ctrl_10;	//0xCCC607B8
	PE_O24_DNR_REG_MNR_CTRL_11_T                          reg_mnr_ctrl_11;	//0xCCC607BC
	PE_O24_DNR_REG_MNR_CTRL_12_T                          reg_mnr_ctrl_12;	//0xCCC607C0
	PE_O24_DNR0_REG_DECON_CTRL_11_T                      reg_decon_ctrl_11;	//0xCCC607C4
	PE_O24_DNR0_REG_DECON_CTRL_12_T                      reg_decon_ctrl_12;	//0xCCC607C8
	PE_O24_DNR0_REG_DECON_CTRL_13_T                      reg_decon_ctrl_13;	//0xCCC607CC
	PE_O24_DNR0_REG_DECON_CTRL_14_T                      reg_decon_ctrl_14;	//0xCCC607D0
	PE_O24_DNR0_REG_DECON_CTRL_15_T                      reg_decon_ctrl_15;	//0xCCC607D4
	PE_O24_DNR0_REG_DECON_CTRL_16_T                      reg_decon_ctrl_16;	//0xCCC607D8
	PE_O24_DNR0_REG_DECON_CTRL_17_T                      reg_decon_ctrl_17;	//0xCCC607DC
	PE_O24_DNR0_REG_DECON_CTRL_18_T                      reg_decon_ctrl_18;	//0xCCC607E0
	PE_O24_DNR0_REG_DECON_CTRL_19_T                      reg_decon_ctrl_19;	//0xCCC607E4
	PE_O24_DNR0_REG_DECON_CTRL_20_T                      reg_decon_ctrl_20;	//0xCCC607E8
	PE_O24_DNR0_REG_DECON_CTRL_21_T                      reg_decon_ctrl_21;	//0xCCC607EC
	PE_O24_DNR0_REG_DECON_CTRL_22_T                      reg_decon_ctrl_22;	//0xCCC607F0
	PE_O24_DNR0_REG_DECON_CTRL_23_T                      reg_decon_ctrl_23;	//0xCCC607F4
	PE_O24_DNR0_REG_DECON_CTRL_24_T                      reg_decon_ctrl_24;	//0xCCC607F8
	PE_O24_DNR0_REG_DECON_CTRL_25_T                      reg_decon_ctrl_25;	//0xCCC607FC
	PE_O24_DNR0_REG_DECON_CTRL_26_T                      reg_decon_ctrl_26;	//0xCCC60800
	PE_O24_DNR0_REG_DECON_CTRL_27_T                      reg_decon_ctrl_27;	//0xCCC60804
	PE_O24_DNR0_REG_DECON_CTRL_28_T                      reg_decon_ctrl_28;	//0xCCC60808
	PE_O24_DNR0_REG_DECON_CTRL_29_T                      reg_decon_ctrl_29;	//0xCCC6080C
	PE_O24_DNR0_REG_DECON_CTRL_30_T                      reg_decon_ctrl_30;	//0xCCC60810
	PE_O24_DNR0_REG_DECON_CTRL_31_T                      reg_decon_ctrl_31;	//0xCCC60814
	PE_O24_DNR0_REG_DECON_CTRL_32_T                      reg_decon_ctrl_32;	//0xCCC60818
	PE_O24_DNR0_REG_DECON_CTRL_33_T                      reg_decon_ctrl_33;	//0xCCC6081C
	PE_O24_DNR0_REG_DECON_CTRL_34_T                      reg_decon_ctrl_34;	//0xCCC60820
	PE_O24_DNR0_REG_DECON_CTRL_35_T                      reg_decon_ctrl_35;	//0xCCC60824
	PE_O24_DNR0_REG_DECON_CTRL_36_T                      reg_decon_ctrl_36;	//0xCCC60828
	PE_O24_DNR0_REG_DECON_CTRL_37_T                      reg_decon_ctrl_37;	//0xCCC6082C
	PE_O24_DNR0_REG_DECON_CTRL_38_T                      reg_decon_ctrl_38;	//0xCCC60830
	PE_O24_DNR0_REG_DECON_CTRL_39_T                      reg_decon_ctrl_39;	//0xCCC60834
	PE_O24_DNR0_REG_DECON_CTRL_40_T                      reg_decon_ctrl_40;	//0xCCC60838
	PE_O24_DNR0_REG_DECON_CTRL_41_T                      reg_decon_ctrl_41;	//0xCCC6083C
	PE_O24_DNR0_REG_DECON_CTRL_42_T                      reg_decon_ctrl_42;	//0xCCC60840
	PE_O24_DNR0_REG_DECON_CTRL_43_T                      reg_decon_ctrl_43;	//0xCCC60844
	PE_O24_DNR0_REG_DECON_CTRL_44_T                      reg_decon_ctrl_44;	//0xCCC60848
	PE_O24_DNR0_REG_DECON_CTRL_45_T                      reg_decon_ctrl_45;	//0xCCC6084C
	PE_O24_DNR0_REG_DECON_CTRL_46_T                      reg_decon_ctrl_46;	//0xCCC60850
	PE_O24_DNR0_REG_DECON_CTRL_47_T                      reg_decon_ctrl_47;	//0xCCC60854
	PE_O24_DNR0_REG_DECON_CTRL_48_T                      reg_decon_ctrl_48;	//0xCCC60858
	PE_O24_DNR0_REG_DECON_CTRL_49_T                      reg_decon_ctrl_49;	//0xCCC6085C
	PE_O24_DNR0_REG_DECON_CTRL_50_T                      reg_decon_ctrl_50;	//0xCCC60860
	PE_O24_DNR0_REG_DECON_CTRL_51_T                      reg_decon_ctrl_51;	//0xCCC60864
	PE_O24_DNR0_REG_DECON_CTRL_52_T                      reg_decon_ctrl_52;	//0xCCC60868
	PE_O24_DNR0_REG_DECON_CTRL_53_T                      reg_decon_ctrl_53;	//0xCCC6086C
	PE_O24_DNR0_REG_DECON_CTRL_54_T                      reg_decon_ctrl_54;	//0xCCC60870
	PE_O24_DNR0_REG_DECON_CTRL_55_T                      reg_decon_ctrl_55;	//0xCCC60874
	PE_O24_DNR0_REG_DECON_CTRL_56_T                      reg_decon_ctrl_56;	//0xCCC60878
	PE_O24_DNR0_REG_DECON_CTRL_57_T                      reg_decon_ctrl_57;	//0xCCC6087C
	PE_O24_DNR0_REG_DECON_CTRL_58_T                      reg_decon_ctrl_58;	//0xCCC60880
	PE_O24_DNR0_REG_DECON_CTRL_59_T                      reg_decon_ctrl_59;	//0xCCC60884
	PE_O24_DNR0_REG_DECON_CTRL_60_T                      reg_decon_ctrl_60;	//0xCCC60888
	PE_O24_DNR0_REG_DECON_CTRL_61_T                      reg_decon_ctrl_61;	//0xCCC6088C
	PE_O24_DNR0_REG_DECON_CTRL_62_T                      reg_decon_ctrl_62;	//0xCCC60890
	PE_O24_DNR0_REG_DECON_CTRL_63_T                      reg_decon_ctrl_63;	//0xCCC60894
	PE_O24_DNR0_REG_DC_BNR_CTRL_12_T                    reg_dc_bnr_ctrl_12;	//0xCCC60898
	PE_O24_DNR0_REG_DC_BNR_CTRL_13_T                    reg_dc_bnr_ctrl_13;	//0xCCC6089C
	PE_O24_DNR0_REG_DC_BNR_CTRL_14_T                    reg_dc_bnr_ctrl_14;	//0xCCC608A0
	PE_O24_DNR0_REG_DC_BNR_CTRL_15_T                    reg_dc_bnr_ctrl_15;	//0xCCC608A4
	PE_O24_DNR0_REG_DECON_CTRL_64_T                      reg_decon_ctrl_64;	//0xCCC608A8
	PE_O24_DNR0_REG_DECON_CTRL_65_T                      reg_decon_ctrl_65;	//0xCCC608AC
	PE_O24_DNR0_REG_DECON_CTRL_66_T                      reg_decon_ctrl_66;	//0xCCC608B0
	PE_O24_DNR0_REG_DECON_CTRL_67_T                      reg_decon_ctrl_67;	//0xCCC608B4
	PE_O24_DNR0_REG_DECON_CTRL_68_T                      reg_decon_ctrl_68;	//0xCCC608B8
	PE_O24_DNR0_REG_DECON_CTRL_69_T                      reg_decon_ctrl_69;	//0xCCC608BC
	PE_O24_DNR0_REG_DECON_CTRL_70_T                      reg_decon_ctrl_70;	//0xCCC608C0
	PE_O24_DNR0_REG_DECON_CTRL_71_T                      reg_decon_ctrl_71;	//0xCCC608C4
	PE_O24_DNR0_REG_DECON_CTRL_72_T                      reg_decon_ctrl_72;	//0xCCC608C8
	PE_O24_DNR0_REG_DECON_CTRL_73_T                      reg_decon_ctrl_73;	//0xCCC608CC
	PE_O24_DNR0_REG_DECON_CTRL_74_T                      reg_decon_ctrl_74;	//0xCCC608D0
	PE_O24_DNR0_REG_DECON_CTRL_75_T                      reg_decon_ctrl_75;	//0xCCC608D4
	PE_O24_DNR0_REG_DECON_CTRL_76_T                      reg_decon_ctrl_76;	//0xCCC608D8
	PE_O24_DNR0_REG_DECON_CTRL_77_T                      reg_decon_ctrl_77;	//0xCCC608DC
	PE_O24_DNR0_REG_DECON_CTRL_78_T                      reg_decon_ctrl_78;	//0xCCC608E0
	PE_O24_DNR0_REG_DECON_CTRL_79_T                      reg_decon_ctrl_79;	//0xCCC608E4
	PE_O24_DNR0_REG_DECON_CTRL_80_T                      reg_decon_ctrl_80;	//0xCCC608E8
	PE_O24_DNR0_REG_DECON_CTRL_81_T                      reg_decon_ctrl_81;	//0xCCC608EC
	PE_O24_DNR0_REG_DECON_CTRL_82_T                      reg_decon_ctrl_82;	//0xCCC608F0
	PE_O24_DNR0_REG_DECON_CTRL_83_T                      reg_decon_ctrl_83;	//0xCCC608F4
	PE_O24_DNR0_REG_DECON_CTRL_84_T                      reg_decon_ctrl_84;	//0xCCC608F8
	PE_O24_DNR0_REG_DECON_CTRL_85_T                      reg_decon_ctrl_85;	//0xCCC608FC
	PE_O24_DNR0_REG_DECON_CTRL_86_T                      reg_decon_ctrl_86;	//0xCCC60900
	PE_O24_DNR0_REG_DECON_CTRL_87_T                      reg_decon_ctrl_87;	//0xCCC60904
	PE_O24_DNR0_REG_DECON_CTRL_88_T                      reg_decon_ctrl_88;	//0xCCC60908
	PE_O24_DNR0_REG_DECON_CTRL_89_T                      reg_decon_ctrl_89;	//0xCCC6090C
	PE_O24_DNR0_REG_DECON_CTRL_90_T                      reg_decon_ctrl_90;	//0xCCC60910
	PE_O24_DNR0_REG_DECON_CTRL_91_T                      reg_decon_ctrl_91;	//0xCCC60914
	PE_O24_DNR0_REG_DECON_CTRL_92_T                      reg_decon_ctrl_92;	//0xCCC60918
	PE_O24_DNR0_REG_DECON_CTRL_93_T                      reg_decon_ctrl_93;	//0xCCC6091C
	PE_O24_DNR0_REG_DECON_CTRL_94_T                      reg_decon_ctrl_94;	//0xCCC60920
	PE_O24_DNR0_REG_DECON_CTRL_95_T                      reg_decon_ctrl_95;	//0xCCC60924
	PE_O24_DNR0_REG_DECON_CTRL_96_T                      reg_decon_ctrl_96;	//0xCCC60928
	PE_O24_DNR0_REG_DECON_CTRL_97_T                      reg_decon_ctrl_97;	//0xCCC6092C
	PE_O24_DNR0_REG_DECON_CTRL_98_T                      reg_decon_ctrl_98;	//0xCCC60930
	PE_O24_DNR0_REG_DECON_CTRL_99_T                      reg_decon_ctrl_99;	//0xCCC60934
	PE_O24_DNR0_REG_DECON_CTRL_100_T                    reg_decon_ctrl_100;	//0xCCC60938
	PE_O24_DNR0_REG_DECON_CTRL_101_T                    reg_decon_ctrl_101;	//0xCCC6093C
	PE_O24_DNR0_REG_DECON_CTRL_102_T                    reg_decon_ctrl_102;	//0xCCC60940
	PE_O24_DNR0_REG_DECON_CTRL_103_T                    reg_decon_ctrl_103;	//0xCCC60944
	PE_O24_DNR0_REG_DECON_CTRL_104_T                    reg_decon_ctrl_104;	//0xCCC60948
	PE_O24_DNR0_REG_DECON_CTRL_105_T                    reg_decon_ctrl_105;	//0xCCC6094C
	PE_O24_DNR0_REG_DECON_CTRL_106_T                    reg_decon_ctrl_106;	//0xCCC60950
	PE_O24_DNR0_REG_DECON_CTRL_107_T                    reg_decon_ctrl_107;	//0xCCC60954
	PE_O24_DNR0_REG_DECON_CTRL_108_T                    reg_decon_ctrl_108;	//0xCCC60958
	PE_O24_DNR0_REG_DECON_CTRL_109_T                    reg_decon_ctrl_109;	//0xCCC6095C
	PE_O24_DNR0_REG_DECON_CTRL_110_T                    reg_decon_ctrl_110;	//0xCCC60960
	PE_O24_DNR0_REG_DECON_CTRL_111_T                    reg_decon_ctrl_111;	//0xCCC60964
	PE_O24_DNR0_REG_DECON_CTRL_112_T                    reg_decon_ctrl_112;	//0xCCC6097C
	PE_O24_DNR0_REG_DECON_CTRL_113_T                    reg_decon_ctrl_113;	//0xCCC60980
	PE_O24_DNR0_REG_DECON_CTRL_114_T                    reg_decon_ctrl_114;	//0xCCC60984
	PE_O24_DNR0_REG_DECON_CTRL_115_T                    reg_decon_ctrl_115;	//0xCCC60988
	PE_O24_DNR0_REG_DECON_CTRL_116_T                    reg_decon_ctrl_116;	//0xCCC6098C
	PE_O24_DNR0_REG_DECON_CTRL_117_T                    reg_decon_ctrl_117;	//0xCCC60990
	PE_O24_DNR0_REG_DECON_CTRL_118_T                    reg_decon_ctrl_118;	//0xCCC60994
	PE_O24_DNR0_REG_DECON_CTRL_119_T                    reg_decon_ctrl_119;	//0xCCC60998
	PE_O24_DNR0_REG_DECON_CTRL_120_T                    reg_decon_ctrl_120;	//0xCCC6099C
	PE_O24_DNR0_REG_DECON_CTRL_121_T                    reg_decon_ctrl_121;	//0xCCC609A0
	PE_O24_DNR0_REG_DECON_CTRL_122_T                    reg_decon_ctrl_122;	//0xCCC609A4
	PE_O24_DNR0_REG_DECON_CTRL_123_T                    reg_decon_ctrl_123;	//0xCCC609A8
	PE_O24_DNR0_REG_DECON_CTRL_124_T                    reg_decon_ctrl_124;	//0xCCC609AC
	PE_O24_DNR0_REG_DECON_CTRL_125_T                    reg_decon_ctrl_125;	//0xCCC609B0
	PE_O24_DNR0_REG_DECON_CTRL_126_T                    reg_decon_ctrl_126;	//0xCCC609B4
	PE_O24_DNR0_REG_DECON_CTRL_127_T                    reg_decon_ctrl_127;	//0xCCC609B8
	PE_O24_DNR0_REG_DECON_CTRL_128_T                    reg_decon_ctrl_128;	//0xCCC609BC
	PE_O24_DNR0_REG_DECON_CTRL_129_T                    reg_decon_ctrl_129;	//0xCCC609C0
	PE_O24_DNR0_REG_DECON_CTRL_130_T                    reg_decon_ctrl_130;	//0xCCC609C4
	PE_O24_DNR0_REG_DECON_CTRL_131_T                    reg_decon_ctrl_131;	//0xCCC609C8
	PE_O24_DNR0_REG_DECON_CTRL_132_T                    reg_decon_ctrl_132;	//0xCCC609CC
	PE_O24_DNR0_REG_DECON_CTRL_133_T                    reg_decon_ctrl_133;	//0xCCC609D0
	PE_O24_DNR0_REG_DECON_CTRL_134_T                    reg_decon_ctrl_134;	//0xCCC609D4
	PE_O24_DNR0_REG_DECON_CTRL_135_T                    reg_decon_ctrl_135;	//0xCCC609D8
	PE_O24_DNR0_REG_DECON_CTRL_136_T                    reg_decon_ctrl_136;	//0xCCC609DC
	PE_O24_DNR0_REG_DECON_CTRL_137_T                    reg_decon_ctrl_137;	//0xCCC609E0
	PE_O24_DNR0_REG_DECON_CTRL_138_T                    reg_decon_ctrl_138;	//0xCCC609E4
	PE_O24_DNR0_REG_DECON_CTRL_139_T                    reg_decon_ctrl_139;	//0xCCC609E8
	PE_O24_DNR0_REG_DECON_CTRL_140_T                    reg_decon_ctrl_140;	//0xCCC609EC
	PE_O24_DNR0_REG_DECON_CTRL_141_T                    reg_decon_ctrl_141;	//0xCCC609F0
	PE_O24_DNR0_REG_DECON_CTRL_142_T                    reg_decon_ctrl_142;	//0xCCC609F4
	PE_O24_DNR0_REG_DECON_CTRL_143_T                    reg_decon_ctrl_143;	//0xCCC609F8
	PE_O24_DNR0_REG_DECON_CTRL_144_T                    reg_decon_ctrl_144;	//0xCCC609FC
	PE_O24_DNR0_REG_DECON_CTRL_145_T                    reg_decon_ctrl_145;	//0xCCC60A00
	PE_O24_DNR0_REG_DECON_CTRL_146_T                    reg_decon_ctrl_146;	//0xCCC60A04
	PE_O24_DNR0_REG_DECON_CTRL_147_T                    reg_decon_ctrl_147;	//0xCCC60A08
	PE_O24_DNR0_REG_DECON_CTRL_148_T                    reg_decon_ctrl_148;	//0xCCC60A0C
	PE_O24_DNR0_REG_DECON_CTRL_149_T                    reg_decon_ctrl_149;	//0xCCC60A10
	PE_O24_DNR0_REG_DECON_CTRL_150_T                    reg_decon_ctrl_150;	//0xCCC60A14
	PE_O24_DNR0_REG_DECON_CTRL_151_T                    reg_decon_ctrl_151;	//0xCCC60A18
	PE_O24_DNR0_REG_DECON_CTRL_152_T                    reg_decon_ctrl_152;	//0xCCC60A1C
	PE_O24_DNR0_REG_DECON_CTRL_153_T                    reg_decon_ctrl_153;	//0xCCC60A20
	PE_O24_DNR0_REG_DECON_CTRL_154_T                    reg_decon_ctrl_154;	//0xCCC60A24
	PE_O24_DNR0_REG_DECON_CTRL_155_T                    reg_decon_ctrl_155;	//0xCCC60A28
	PE_O24_DNR0_REG_DECON_CTRL_156_T                    reg_decon_ctrl_156;	//0xCCC60A2C
	PE_O24_DNR0_REG_DECON_CTRL_157_T                    reg_decon_ctrl_157;	//0xCCC60A30
	PE_O24_DNR0_REG_DECON_CTRL_158_T                    reg_decon_ctrl_158;	//0xCCC60A34
	PE_O24_DNR0_REG_DECON_CTRL_159_T                    reg_decon_ctrl_159;	//0xCCC60A38
	PE_O24_DNR0_REG_DECON_CTRL_160_T                    reg_decon_ctrl_160;	//0xCCC60A3C
	PE_O24_DNR0_REG_DECON_CTRL_161_T                    reg_decon_ctrl_161;	//0xCCC60A40
	PE_O24_DNR0_REG_DECON_CTRL_162_T                    reg_decon_ctrl_162;	//0xCCC60A44
	PE_O24_DNR0_REG_DECON_CTRL_163_T                    reg_decon_ctrl_163;	//0xCCC60A48
	PE_O24_DNR0_REG_DECON_CTRL_164_T                    reg_decon_ctrl_164;	//0xCCC60A4C
	PE_O24_DNR0_REG_DECON_CTRL_165_T                    reg_decon_ctrl_165;	//0xCCC60A50
	PE_O24_DNR0_REG_DECON_CTRL_166_T                    reg_decon_ctrl_166;	//0xCCC60A54
	PE_O24_DNR0_REG_DECON_CTRL_167_T                    reg_decon_ctrl_167;	//0xCCC60A58
	PE_O24_DNR0_REG_DECON_CTRL_168_T                    reg_decon_ctrl_168;	//0xCCC60A5C
	PE_O24_DNR0_REG_DECON_CTRL_169_T                    reg_decon_ctrl_169;	//0xCCC60A60
	PE_O24_DNR0_REG_DECON_CTRL_170_T                    reg_decon_ctrl_170;	//0xCCC60A64
	PE_O24_DNR0_REG_DECON_CTRL_171_T                    reg_decon_ctrl_171;	//0xCCC60A68
	PE_O24_DNR0_REG_DECON_CTRL_172_T                    reg_decon_ctrl_172;	//0xCCC60A6C
	PE_O24_DNR0_REG_DECON_CTRL_173_T                    reg_decon_ctrl_173;	//0xCCC60A70
	PE_O24_DNR0_REG_DECON_CTRL_174_T                    reg_decon_ctrl_174;	//0xCCC60A74
	PE_O24_DNR0_REG_DECON_CTRL_175_T                    reg_decon_ctrl_175;	//0xCCC60A78
	PE_O24_DNR0_REG_DECON_CTRL_176_T                    reg_decon_ctrl_176;	//0xCCC60A7C
	PE_O24_DNR0_REG_DECON_CTRL_177_T                    reg_decon_ctrl_177;	//0xCCC60A80
	PE_O24_DNR0_REG_DECON_CTRL_178_T                    reg_decon_ctrl_178;	//0xCCC60A84
	PE_O24_DNR0_REG_DECON_CTRL_179_T                    reg_decon_ctrl_179;	//0xCCC60A88
	PE_O24_DNR0_REG_DECON_CTRL_180_T                    reg_decon_ctrl_180;	//0xCCC60A8C
	PE_O24_DNR0_REG_DECON_CTRL_181_T                    reg_decon_ctrl_181;	//0xCCC60A90
	PE_O24_DNR0_REG_DECON_CTRL_182_T                    reg_decon_ctrl_182;	//0xCCC60A94
	#endif
}PE_DNR_HW_PARAM_REG_O24_T;

/**
 *	led dnr hw param reg type
 */
 
typedef struct {

	PE_CCO_DECON_CTRL_0_T                       reg_decon_ctrl_0;	//0xCC862104
	PE_CCO_DECON_CTRL_1_T                       reg_decon_ctrl_1;	//0xCC862108
	PE_CCO_DECON_CTRL_2_T                       reg_decon_ctrl_2;	//0xCC86210C
	PE_CCO_DECON_CTRL_3_T                       reg_decon_ctrl_3;	//0xCC862110
	PE_CCO_DECON_CTRL_4_T                       reg_decon_ctrl_4;	//0xCC862114
	PE_CCO_DECON_CTRL_5_T                       reg_decon_ctrl_5;	//0xCC862118
	PE_CCO_DECON_CTRL_6_T                       reg_decon_ctrl_6;	//0xCC86211C
	PE_CCO_DECON_CTRL_7_T                       reg_decon_ctrl_7;	//0xCC862120
	PE_CCO_DECON_CTRL_8_T                       reg_decon_ctrl_8;	//0xCC862124
	PE_CCO_DECON_CTRL_9_T                       reg_decon_ctrl_9;	//0xCC862128
	PE_CCO_DECON_CTRL_10_T                     reg_decon_ctrl_10;	//0xCC86212C
	PE_CCO_DECON_CTRL_11_T                     reg_decon_ctrl_11;	//0xCC862130
	PE_CCO_DECON_CTRL_12_T                     reg_decon_ctrl_12;	//0xCC862134
	PE_CCO_DECON_CTRL_13_T                     reg_decon_ctrl_13;	//0xCC862138
	PE_CCO_DECON_CTRL_14_T                     reg_decon_ctrl_14;	//0xCC86213C
	PE_CCO_DECON_CTRL_15_T                     reg_decon_ctrl_15;	//0xCC862140
	PE_CCO_DECON_CTRL_16_T                     reg_decon_ctrl_16;	//0xCC862144
	PE_CCO_DECON_CTRL_17_T                     reg_decon_ctrl_17;	//0xCC862148
	PE_CCO_DECON_CTRL_18_T                     reg_decon_ctrl_18;	//0xCC86214C
	PE_CCO_DECON_CTRL_19_T                     reg_decon_ctrl_19;	//0xCC862150
	PE_CCO_DECON_CTRL_20_T                     reg_decon_ctrl_20;	//0xCC862154
	PE_CCO_DECON_CTRL_21_T                     reg_decon_ctrl_21;	//0xCC862158
	PE_CCO_DECON_CTRL_22_T                     reg_decon_ctrl_22;	//0xCC86215C
	PE_CCO_DECON_CTRL_23_T                     reg_decon_ctrl_23;	//0xCC862160
	PE_CCO_DECON_CTRL_24_T                     reg_decon_ctrl_24;	//0xCC8621BC
	PE_CCO_DECON_CTRL_25_T                     reg_decon_ctrl_25;	//0xCC8621C0
	PE_CCO_DECON_CTRL_26_T                     reg_decon_ctrl_26;	//0xCC8621C4
	PE_CCO_DECON_CTRL_27_T                     reg_decon_ctrl_27;	//0xCC8621C8
	PE_CCO_DECON_CTRL_28_T                     reg_decon_ctrl_28;	//0xCC8621CC
	PE_CCO_DECON_CTRL_29_T                     reg_decon_ctrl_29;	//0xCC8621D0
	PE_CCO_DECON_CTRL_30_T                     reg_decon_ctrl_30;	//0xCC8621D4
	PE_CCO_DECON_CTRL_31_T                     reg_decon_ctrl_31;	//0xCC8621D8
	PE_CCO_DECON_CTRL_32_T                     reg_decon_ctrl_32;	//0xCC8621DC
	PE_CCO_DECON_CTRL_33_T                     reg_decon_ctrl_33;	//0xCC8621E0
	PE_CCO_DECON_CTRL_34_T                     reg_decon_ctrl_34;	//0xCC8621E4
	PE_CCO_DECON_CTRL_35_T                     reg_decon_ctrl_35;	//0xCC8621E8
	PE_CCO_DECON_CTRL_36_T                     reg_decon_ctrl_36;	//0xCC8621EC
	PE_CCO_DECON_CTRL_37_T                     reg_decon_ctrl_37;	//0xCC8621F0
	PE_CCO_DECON_CTRL_38_T                     reg_decon_ctrl_38;	//0xCC8621F4
	PE_CCO_DECON_CTRL_39_T                     reg_decon_ctrl_39;	//0xCC8621F8
	PE_CCO_DECON_CTRL_40_T                     reg_decon_ctrl_40;	//0xCC8621FC
	PE_CCO_DECON_CTRL_41_T                     reg_decon_ctrl_41;	//0xCC862200
	PE_CCO_DECON_CTRL_42_T                     reg_decon_ctrl_42;	//0xCC862204
	PE_CCO_DECON_CTRL_43_T                     reg_decon_ctrl_43;	//0xCC862208
	PE_CCO_DECON_CTRL_44_T                     reg_decon_ctrl_44;	//0xCC86220C
	PE_CCO_DECON_CTRL_45_T                     reg_decon_ctrl_45;	//0xCC862210
	PE_CCO_DECON_CTRL_46_T                     reg_decon_ctrl_46;	//0xCC862214
	PE_CCO_DECON_CTRL_47_T                     reg_decon_ctrl_47;	//0xCC862218
	PE_CCO_DECON_CTRL_48_T                     reg_decon_ctrl_48;	//0xCC86221C
	PE_CCO_DECON_CTRL_49_T                     reg_decon_ctrl_49;	//0xCC862220
	PE_CCO_DECON_CTRL_50_T                     reg_decon_ctrl_50;	//0xCC862224
	PE_CCO_DECON_CTRL_51_T                     reg_decon_ctrl_51;	//0xCC862228
	PE_CCO_DECON_CTRL_52_T                     reg_decon_ctrl_52;	//0xCC86222C
	PE_CCO_DECON_CTRL_53_T                     reg_decon_ctrl_53;	//0xCC862230
	PE_CCO_DECON_CTRL_54_T                     reg_decon_ctrl_54;	//0xCC862234
	PE_CCO_DECON_CTRL_55_T                     reg_decon_ctrl_55;	//0xCC862238
	PE_CCO_DECON_CTRL_56_T                     reg_decon_ctrl_56;	//0xCC86223C
	PE_CCO_DECON_CTRL_57_T                     reg_decon_ctrl_57;	//0xCC862240
	PE_CCO_DECON_CTRL_58_T                     reg_decon_ctrl_58;	//0xCC862244
	PE_CCO_DECON_CTRL_59_T                     reg_decon_ctrl_59;	//0xCC862248
	PE_CCO_DECON_CTRL_60_T                     reg_decon_ctrl_60;	//0xCC86224C
	PE_CCO_DECON_CTRL_61_T                     reg_decon_ctrl_61;	//0xCC862250
	PE_CCO_DECON_CTRL_62_T                     reg_decon_ctrl_62;	//0xCC862254
	PE_CCO_DECON_CTRL_63_T                     reg_decon_ctrl_63;	//0xCC862258
	PE_CCO_DECON_CTRL_64_T                     reg_decon_ctrl_64;	//0xCC86225C
	PE_CCO_DECON_CTRL_65_T                     reg_decon_ctrl_65;	//0xCC862260
	PE_CCO_DECON_CTRL_66_T                     reg_decon_ctrl_66;	//0xCC862264
	PE_CCO_DECON_CTRL_67_T                     reg_decon_ctrl_67;	//0xCC862268
	PE_CCO_DECON_CTRL_68_T                     reg_decon_ctrl_68;	//0xCC86226C
	PE_CCO_DECON_CTRL_69_T                     reg_decon_ctrl_69;	//0xCC862270
	PE_CCO_DECON_CTRL_70_T                     reg_decon_ctrl_70;	//0xCC862274
	PE_CCO_DECON_CTRL_71_T                     reg_decon_ctrl_71;	//0xCC862278
	PE_CCO_DECON_CTRL_72_T                     reg_decon_ctrl_72;	//0xCC86227C
	PE_CCO_DECON_CTRL_73_T                     reg_decon_ctrl_73;	//0xCC862280
	PE_CCO_DECON_CTRL_74_T                     reg_decon_ctrl_74;	//0xCC862284
	PE_CCO_DECON_CTRL_75_T                     reg_decon_ctrl_75;	//0xCC862288
	PE_CCO_DECON_CTRL_76_T                     reg_decon_ctrl_76;	//0xCC86228C
	PE_CCO_DECON_CTRL_77_T                     reg_decon_ctrl_77;	//0xCC862290
	PE_CCO_DECON_CTRL_78_T                     reg_decon_ctrl_78;	//0xCC862294
	PE_CCO_DECON_CTRL_79_T                     reg_decon_ctrl_79;	//0xCC862298
	PE_CCO_DECON_CTRL_80_T                     reg_decon_ctrl_80;	//0xCC86229C
	PE_CCO_DECON_CTRL_81_T                     reg_decon_ctrl_81;	//0xCC8622A0
	PE_CCO_DECON_CTRL_82_T                     reg_decon_ctrl_82;	//0xCC8622A4
	PE_CCO_DECON_CTRL_83_T                     reg_decon_ctrl_83;	//0xCC8622A8
	PE_CCO_DECON_CTRL_84_T                     reg_decon_ctrl_84;	//0xCC8622AC
	PE_CCO_DECON_CTRL_85_T                     reg_decon_ctrl_85;	//0xCC8622B0
	PE_CCO_DECON_CTRL_86_T                     reg_decon_ctrl_86;	//0xCC8622B4
	PE_CCO_DECON_CTRL_87_T                     reg_decon_ctrl_87;	//0xCC8622B8
	PE_CCO_DECON_CTRL_88_T                     reg_decon_ctrl_88;	//0xCC8622BC
	PE_CCO_DECON_CTRL_89_T                     reg_decon_ctrl_89;	//0xCC8622C0
	PE_CCO_DECON_CTRL_90_T                     reg_decon_ctrl_90;	//0xCC8622C4
	PE_CCO_DECON_CTRL_91_T                     reg_decon_ctrl_91;	//0xCC8622C8
	PE_CCO_DECON_CTRL_92_T                     reg_decon_ctrl_92;	//0xCC8622CC
	PE_CCO_DECON_CTRL_93_T                     reg_decon_ctrl_93;	//0xCC8622D0
	PE_CCO_DECON_CTRL_94_T                     reg_decon_ctrl_94;	//0xCC8622D4
	PE_CCO_DECON_CTRL_95_T                     reg_decon_ctrl_95;	//0xCC8622D8
	PE_CCO_DECON_CTRL_96_T                     reg_decon_ctrl_96;	//0xCC8622DC
	PE_CCO_DECON_CTRL_97_T                     reg_decon_ctrl_97;	//0xCC8622E0
	PE_CCO_DECON_CTRL_98_T                     reg_decon_ctrl_98;	//0xCC8622E4
	PE_CCO_DECON_CTRL_99_T                     reg_decon_ctrl_99;	//0xCC8622E8
	PE_CCO_DECON_CTRL_100_T                   reg_decon_ctrl_100;	//0xCC8622EC
	PE_CCO_DECON_CTRL_101_T                   reg_decon_ctrl_101;	//0xCC8622F0
	PE_CCO_DECON_CTRL_102_T                   reg_decon_ctrl_102;	//0xCC8622F4
	PE_CCO_DECON_CTRL_103_T                   reg_decon_ctrl_103;	//0xCC8622F8
	PE_CCO_DECON_CTRL_104_T                   reg_decon_ctrl_104;	//0xCC8622FC
}PE_CCO_DNR_HW_PARAM_REG_O24_T;


/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O24_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O24_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_DNR_HW_PARAM_REG_O24_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_DNR_HW_PARAM_REG_O24_T *data;
	} reg_data;
} PE_DNR_HW_PARAM_DATA_O24_T;
/**
 *	dnr hw param data type
 */
typedef struct {
	union {
		UINT32			*addr;
		PE_CCO_DNR_HW_PARAM_REG_O24_T *data;
	} reg_dflt;

	union {
		UINT32			 *addr;
		PE_CCO_DNR_HW_PARAM_REG_O24_T *data;
	} reg_user;

	union {
		UINT32			*addr;
		PE_CCO_DNR_HW_PARAM_REG_O24_T *data;
	} reg_mask;

	union {
		UINT32			 *addr;
		PE_CCO_DNR_HW_PARAM_REG_O24_T *data;
	} reg_data;
} PE_CCO_DNR_HW_PARAM_DATA_O24_T;


/*----------------------------------------------------------------------------
	Extern Function Prototype Declaration
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
	Extern Variables
----------------------------------------------------------------------------*/

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* _PE_DNR_HW_PARAM_O24_H_ */
