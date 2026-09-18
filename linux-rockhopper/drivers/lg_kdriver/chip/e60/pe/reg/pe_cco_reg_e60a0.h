#ifndef _PE_CCO_REG_E60A0_H_
#define _PE_CCO_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC902E500 RW
	UINT32 load_time                        :1;	//0 //0' : load at vdpulse	'1' : load when reg. write
	UINT32 load_enable                      :1;	//1 //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //0' : auto load:  load when reg. write	'1' : manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_E60_PE1_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E504 RW
	UINT32 width                            :13;	//12:0	//width
	UINT32 resvd0                           :3;
	UINT32 height                           :13;	//28:16	//height
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E508 RW
	UINT32 tpg_position                     :1;	//0 //0 := pe1 input	1  =  pe1 output
	UINT32 reg_pe1_cg_disable               :1;	//1 //clock gating disable
	UINT32 pe1_detour                       :1;	//2 //0': pe1 pass-through	'1': pe1 detour
	UINT32 resvd0                           :5;
	UINT32 vdpulse_pos                      :12;	//19:8	//vdpulse position for register loading
	UINT32 resvd1                           :4;
	UINT32 master_en                        :1;	//24 //PE1 master enable
	UINT32 resvd2                           :7;
	};
}PE_E60_PE1_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E50C RO
	UINT32 vcnt                             :13;	//12:0	//vertical line count
	UINT32 va_pe1_in                        :1;	//13 //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//14 //Vertical Active at PE1 output
	UINT32 resvd0                           :1;
	UINT32 vcnt2                            :13;	//28:16	//vertical line number
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E510 RW
	UINT32 r_to_cnt                         :12;	//11:0	//apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_E60_PE1_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E520 RW
	UINT32 reg_s_status_0					   : 8 ;  //  7: 0
	UINT32 reg_s_status_1					   : 8 ;  // 15: 8
	UINT32 reg_s_apl_0 					       : 8 ;  // 23:16
	UINT32 reg_fmd_en_0					       : 1 ;  //	24
	UINT32 reg_fmd_en_1					       : 1 ;  //	25
	UINT32 reg_tnr_auto_en 				       : 1 ;  //	26
	UINT32 cl_filter_en_stat				   : 1 ;  //	27
	UINT32 clc_detection_en_stat			   : 1 ;  //	28
	UINT32 reg_color_filter_status 		       : 2 ;  // 30:29
	UINT32 reg_shp_fw_en					   : 1 ;  //	31
	};
}PE_E60_CC_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E524 RW
	UINT32 reg_histo_fw_en                    : 1;  //     0
	UINT32 reg_drc_dc_mode                    : 2;  //  2: 1
	UINT32 reg_drc_dc_bypass                  : 1;  //     3
	UINT32 reg_drc_dc_sc_cnt                  : 4;  //  7: 4
	UINT32 pre_121_blur_en                    : 1;  //     8
	UINT32 pre_median_en                      : 1;  //     9
	UINT32 tnr_sc_measure_en                  : 1;  //    10
	UINT32 reg_is_oled                        : 1;  //    11
	UINT32 reserved                           : 2;  // 13:12     reserved
	UINT32 reg_hdr_effect                     : 2;  // 15:14
	UINT32 tnr_sc_measure_th                  : 16;  // 31:16
	};
}PE_E60_CC_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E528 RW
	UINT32 reg_src_info					   : 6 ;  //  5: 0
	UINT32 reg_src_freeze				   : 1 ;  //	 6
	UINT32 reserved				           : 1 ;  //	 7
	UINT32 ndskip  				           : 1 ;  //	 8
	UINT32 output_4k_mode   	           : 1 ;  //	 9 : 8k:0x0, 4k:0x1
	};
}PE_E60_CC_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E52C RW
	UINT32 reg_nt_lvl					   : 8 ;  //  7: 0
	UINT32 reg_s_status					   : 8 ;  // 15: 8
	UINT32 reg_s_apl					   : 8 ;  // 23:16
	};
}PE_E60_CC_PE1_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E530 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_CC_PE1_FSW_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E534 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_CC_PE1_FSW_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E538 RW
	UINT32 tdata0                           :32;
	};
}PE_E60_CC_PE1_FSW_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E53C RW
	UINT32 tdata0                           :32;
	};
}PE_E60_CC_PE1_FSW_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E550 RW
	UINT32 tpg_enable                       :1;	//0 //TPG Enable
	UINT32 pattern_type                     :2;	//2:1	//Test Pattern Type	'00 := ColorPatch	'01 = Gradation
	UINT32 resvd0                           :1;
	UINT32 blend_alpha                      :4;	//7:4	//TPG Blend Alpha	0x0 ~ 0xF = SolidPattern ~ BypassBackgroundPicture
	UINT32 resvd1                           :8;
	UINT32 blt_size_x                       :13;	//28:16	//Pattern Blt Size X (1920d=>0x780)
	UINT32 resvd2                           :3;
	};
}PE_E60_PE1_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E554 RW
	UINT32 gradation_stride                 :7;	//6:0	//Gradation Stride
	UINT32 gradation_direction              :1;	//7 //Gradation Direction	'0 = Vertical Gradation	'1 := Horizontal Gradation
	UINT32 gradation_bar_0_en               :1;	//8 //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_1_en               :1;	//9 //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_2_en               :1;	//10 //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_3_en               :1;	//11 //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 resvd0                           :4;
	UINT32 blt_size_y                       :13;	//28:16	//Pattern Blt Size Y (1080d=>0x438)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E558 RW
	UINT32 patch_0_en                       :1;	//0 //Enable Ctrl for each Patch
	UINT32 patch_1_en                       :1;	//1 //Enable Ctrl for each Patch
	UINT32 patch_2_en                       :1;	//2 //Enable Ctrl for each Patch
	UINT32 patch_3_en                       :1;	//3 //Enable Ctrl for each Patch
	UINT32 patch_4_en                       :1;	//4 //Enable Ctrl for each Patch
	UINT32 patch_5_en                       :1;	//5 //Enable Ctrl for each Patch
	UINT32 patch_6_en                       :1;	//6 //Enable Ctrl for each Patch
	UINT32 patch_7_en                       :1;	//7 //Enable Ctrl for each Patch
	UINT32 patch_8_en                       :1;	//8 //Enable Ctrl for each Patch
	UINT32 patch_9_en                       :1;	//9 //Enable Ctrl for each Patch
	UINT32 patch_10_en                      :1;	//10 //Enable Ctrl for each Patch
	UINT32 patch_11_en                      :1;	//11 //Enable Ctrl for each Patch
	UINT32 patch_12_en                      :1;	//12 //Enable Ctrl for each Patch
	UINT32 patch_13_en                      :1;	//13 //Enable Ctrl for each Patch
	UINT32 patch_14_en                      :1;	//14 //Enable Ctrl for each Patch
	UINT32 patch_15_en                      :1;	//15 //Enable Ctrl for each Patch
	UINT32 resvd                            :16;
	};
}PE_E60_PE1_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E55C RW
	UINT32 patch_0_inout_sel                :1;	//0 //select inside/outside coloring for each Patch
	UINT32 patch_1_inout_sel                :1;	//1 //select inside/outside coloring for each Patch
	UINT32 patch_2_inout_sel                :1;	//2 //select inside/outside coloring for each Patch
	UINT32 patch_3_inout_sel                :1;	//3 //select inside/outside coloring for each Patch
	UINT32 patch_4_inout_sel                :1;	//4 //select inside/outside coloring for each Patch
	UINT32 patch_5_inout_sel                :1;	//5 //select inside/outside coloring for each Patch
	UINT32 patch_6_inout_sel                :1;	//6 //select inside/outside coloring for each Patch
	UINT32 patch_7_inout_sel                :1;	//7 //select inside/outside coloring for each Patch
	UINT32 patch_8_inout_sel                :1;	//8 //select inside/outside coloring for each Patch
	UINT32 patch_9_inout_sel                :1;	//9 //select inside/outside coloring for each Patch
	UINT32 patch_10_inout_sel               :1;	//10 //select inside/outside coloring for each Patch
	UINT32 patch_11_inout_sel               :1;	//11 //select inside/outside coloring for each Patch
	UINT32 patch_12_inout_sel               :1;	//12 //select inside/outside coloring for each Patch
	UINT32 patch_13_inout_sel               :1;	//13 //select inside/outside coloring for each Patch
	UINT32 patch_14_inout_sel               :1;	//14 //select inside/outside coloring for each Patch
	UINT32 patch_15_inout_sel               :1;	//15 //select inside/outside coloring for each Patch
	UINT32 resvd                            :16;
	};
}PE_E60_PE1_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E560 RW
	UINT32 bg_color_r                       :10;	//9:0	//outside color with RGB
	UINT32 bg_color_b                       :10;	//19:10	//
	UINT32 bg_color_g                       :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E564 WO
	UINT32 tpg_indir_addr                   :7;	//6:0	//TPG Indirect Address	0x00 ~ 0x0F = Patch Color	0x20 ~ 0x2F = Patch Start Position	0x40 ~ 0x4F = Patch End Position	0x60 ~ 0x63 = Gradation Start Color	0x64 ~ 0x67 = Gradation Step Color (signed)	0x68 ~ 0x6A = Gradation Region Size
	UINT32 resvd0                           :5;
	UINT32 tpg_indir_ai_en                  :1;	//12 //TPG Indirect Addressing Ctrl, AI Enable
	UINT32 resvd1                           :19;
	};
}PE_E60_PE1_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E568 WO
	UINT32 tpg_indir_data                   :32;	//31:0	//TPG Indirect Access Data (Write Enable Triggered)	 When Addr is...	 0x00 ~ 0x0F = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x20 ~ 0x4F = (28:16):X_position, (12:0):Y_position	 0x60 ~ 0x67 = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x68 ~ 0x6A = (12:0):position
	};
}PE_E60_PE1_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E570 RW
	UINT32 apl_win_ctrl_x0_0                :13;	//12:0	//apl_win_ctrl_x0 for ch0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_0                :13;	//28:16	//apl_win_ctrl_y0 for ch0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E574 RW
	UINT32 apl_win_ctrl_x1_0                :13;	//12:0	//1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_0                :13;	//28:16	//1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E578 RW
	UINT32 apl_position                     :2;	//1:0	//00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :2;
	UINT32 reg_apl_enable                   :1;	//4 //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :3;
	UINT32 act_win_mode                     :1;	//8 //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd2                           :7; //15:9
	UINT32 dummy                            :2; //17:16
	UINT32 resvd3                           :14;//31:18
	};
}PE_E60_PE1_APL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E57C RW
	UINT32 apl_win_ctrl_x0_1                :13;	//12:0	//apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_1                :13;	//28:16	//apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E580 RW
	UINT32 apl_win_ctrl_x1_1                :13;	//12:0	//1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_1                :13;	//28:16	//1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E584 RW
	UINT32 apl_win_ctrl_x0_2                :13;	//12:0	//apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_2                :13;	//28:16	//apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E588 RW
	UINT32 apl_win_ctrl_x1_2                :13;	//12:0	//1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_2                :13;	//28:16	//1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E58C RW
	UINT32 apl_win_ctrl_x0_3                :13;	//12:0	//apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_3                :13;	//28:16	//apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E590 RW
	UINT32 apl_win_ctrl_x1_3                :13;	//12:0	//1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_3                :13;	//28:16	//1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_APL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5B4 RO
	UINT32 apl_cb                           :10;	//9:0	//APL Cb/B
	UINT32 apl_yg                           :10;	//19:10	//APL Y/G
	UINT32 apl_cr                           :10;	//29:20	//APL Cr/R
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5B8 RO
	UINT32 apl_cb_other_side                :10;	//9:0	//apl_cb(outside of apl_win)
	UINT32 apl_yg_other_side                :10;	//19:10	//apl_yg(outside of apl_win)
	UINT32 apl_cr_other_side                :10;	//29:20	//apl_cr(outside of apl_win)
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_APL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5C0 RW
	UINT32 r_2x3_coef1                      :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef0                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5C4 RW
	UINT32 r_2x3_coef3a                     :15;	//14:0	//when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef2                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5C8 RW
	UINT32 r_2x3_coef5a                     :15;	//14:0	//when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4a                     :15;	//30:16	//when ( cb <= reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5CC RW
	UINT32 r_2x3_coef7a                     :15;	//14:0	//when ( cr <= reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6a                     :15;	//30:16	//when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5D0 RW
	UINT32 r_2x3_ofst0                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_2x3_coef8a                     :15;	//30:16	//when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5D4 RW
	UINT32 r_2x3_ofst2                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst1                      :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_BT20_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5D8 RW
	UINT32 r_2x3_ofst3                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst4                      :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_BT20_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5DC RW
	UINT32 r_2x3_en                         :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 r_degamma_en                     :1;	//4 //
	UINT32 resvd1                           :3;
	UINT32 r_1x3_en                         :1;	//8 //
	UINT32 resvd2                           :7;
	UINT32 r_2x3_ofst5                      :11;	//26:16	//
	UINT32 resvd3                           :5;
	};
}PE_E60_PE1_BT20_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5E0 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 decontour_en                     :1;	//1 //enable decontour
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"01" : 8 bit mode	others : bypass
	UINT32 resvd                            :2;
	UINT32 decontour_gain_r                 :8;	//15:8	//decontour gain for red
	UINT32 decontour_gain_g                 :8;	//23:16	//decontour gain for blue
	UINT32 decontour_gain_b                 :8;	//31:24	//decontour gain for green
	};
}PE_E60_PE1_BT20_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5E4 RW
	UINT32 r_2x3_coef3b                     :15;	//14:0	//when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 reg_csc_cb_th                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_BT20_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5E8 RW
	UINT32 r_2x3_coef5b                     :15;	//14:0	//when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4b                     :15;	//30:16	//when ( cb > reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5EC RW
	UINT32 r_2x3_coef7b                     :15;	//14:0	//when ( cr > reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6b                     :15;	//30:16	//when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5F0 RW
	UINT32 reg_csc_cr_th                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 r_2x3_coef8b                     :15;	//30:16	//when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5F4 RW
	UINT32 r_1x3_coef1                      :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef0                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5F8 RW
	UINT32 r_1x3_coef3                      :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef2                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E5FC RW
	UINT32 r_1x3_coef5                      :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef4                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E600 RW
	UINT32 r_1x3_coef7                      :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef6                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E604 RW
	UINT32 resvd0                           :16;
	UINT32 r_1x3_coef8                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_BT20_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E608 RW
	UINT32 r_1x3_ofst1                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst0                      :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_BT20_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E60C RW
	UINT32 r_1x3_ofst3                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst2                      :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_BT20_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E610 RW
	UINT32 r_1x3_ofst5                      :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst4                      :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_BT20_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E614 RW
	UINT32 r_1x3_dbg_en                     :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 r_1x3_dbg_ugy                    :4;	//7:4	//underflowed bit gy upper 4 bit
	UINT32 r_1x3_dbg_ucb                    :4;	//11:8	//underflowed bit cb upper 4 bit
	UINT32 r_1x3_dbg_ucr                    :4;	//15:12	//underflowed bit cr upper 4 bit
	UINT32 r_1x3_dbg_ogy                    :4;	//19:16	//overflowed bit gy upper 4 bit
	UINT32 r_1x3_dbg_ocb                    :4;	//23:20	//overflowed bit cb upper 4 bit
	UINT32 r_1x3_dbg_obr                    :4;	//27:24	//overflowed bit cr upper 4 bit
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_BT20_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E618 RO
	UINT32 r_1x3_over_count_0               :16;	//15:0	//overflow count status for ch 0
	UINT32 r_1x3_under_count_0              :16;	//31:16	//underflow count status for ch 0
	};
}PE_E60_PE1_BT20_CTRL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E61C RO
	UINT32 r_1x3_over_count_1               :16;	//15:0	//overflow count status
	UINT32 r_1x3_under_count_1              :16;	//31:16	//underflow count status
	};
}PE_E60_PE1_BT20_CTRL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E620 RO
	UINT32 r_1x3_over_count_2               :16;	//15:0	//overflow count status
	UINT32 r_1x3_under_count_2              :16;	//31:16	//underflow count status
	};
}PE_E60_PE1_BT20_CTRL_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E624 RO
	UINT32 r_1x3_over_count_3               :16;	//15:0	//overflow count status
	UINT32 r_1x3_under_count_3              :16;	//31:16	//underflow count status
	};
}PE_E60_PE1_BT20_CTRL_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E640 RW
	UINT32 win0_en                          :1;	//0 //1 =  select only window0 as active area
	UINT32 win1_en                          :1;	//1 //1 =  select only window1 as active area
	UINT32 win01_en                         :1;	//2 //1 =  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//6 //0 := use inside of selected area by win0 and win1	1 =  use the otherside of selected area by win0 and win1
	UINT32 win_en                           :1;	//7 //0 := active area = full screen	1 = active area = specifed by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//12:8	//border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//14:13	//border width
	UINT32 bdr_en                           :1;	//15 //border enable
	UINT32 cr5                              :5;	//20:16	//border color : cr5
	UINT32 cb5                              :5;	//25:21	//border color : cb5
	UINT32 yy6                              :6;	//31:26	//border color : yy6
	};
}PE_E60_PE1_WIN2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E644 RW
	UINT32 win_w0_x0_0                      :13;	//12:0	//win_w0_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_0                      :13;	//28:16	//win_w0_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E648 RW
	UINT32 win_w0_x1_0                      :13;	//12:0	//win_w0_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_0                      :13;	//28:16	//win_w0_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E64C RW
	UINT32 win_w1_x0_0                      :13;	//12:0	//win_w1_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_0                      :13;	//28:16	//win_w1_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E650 RW
	UINT32 win_w1_x1_0                      :13;	//12:0	//win_w1_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_0                      :13;	//28:16	//win_w1_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E654 RW
	UINT32 win_w0_x0_1                      :13;	//12:0	//win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_1                      :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E658 RW
	UINT32 win_w0_x1_1                      :13;	//12:0	//win_w0_x1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_1                      :13;	//28:16	//win_w0_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E65C RW
	UINT32 win_w1_x0_1                      :13;	//12:0	//win_w1_x0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_1                      :13;	//28:16	//win_w1_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E660 RW
	UINT32 win_w1_x1_1                      :13;	//12:0	//win_w1_x1
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_1                      :13;	//28:16	//win_w1_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E664 RW
	UINT32 win_w0_x0_2                      :13;	//12:0	//win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_2                      :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E668 RW
	UINT32 win_w0_x1_2                      :13;	//12:0	//win_w0_x1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_2                      :13;	//28:16	//win_w0_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E66C RW
	UINT32 win_w1_x0_2                      :13;	//12:0	//win_w1_x0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_2                      :13;	//28:16	//win_w1_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E670 RW
	UINT32 win_w1_x1_2                      :13;	//12:0	//win_w1_x1
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_2                      :13;	//28:16	//win_w1_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E674 RW
	UINT32 win_w0_x0_3                      :13;	//12:0	//win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_3                      :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E678 RW
	UINT32 win_w0_x1_3                      :13;	//12:0	//win_w0_x1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_3                      :13;	//28:16	//win_w0_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E67C RW
	UINT32 win_w1_x0_3                      :13;	//12:0	//win_w1_x0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_3                      :13;	//28:16	//win_w1_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E680 RW
	UINT32 win_w1_x1_3                      :13;	//12:0	//win_w1_x1
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_3                      :13;	//28:16	//win_w1_y1
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_WIN2_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6D0 RW
	UINT32 cen_detour                       :1;	//0 //cen_detour	'0' : normal path	'1' : CEN detour
	UINT32 dse_mode                         :1;	//1 //0:parallel, 1:serial(DSE->CEN)
	UINT32 select_hsv                       :1;	//2 //reg_select_hsv 	HSV total gain의 적용 여부	'1' : HSV total gain을 원본 HSV와 합산하여 적용	'0' : 원본 HSV를 그대로 사용
	UINT32 select_rgb                       :1;	//3 //reg_select_RGB 	RGB total gain의 적용 여부	'1' : RGB total gain을 원본 RGB와 합산하여 적용	'0' : 원본 RGB을 그대로 사용
	UINT32 resvd0                           :1;
	UINT32 vsp_sel                          :1;	//5 //reg_vsp_sel	'0' : HSL region	'1' : HSV region
	UINT32 resvd1                           :1;
	UINT32 reg_cen_bypass                   :1;	//7 //reg_cen_bypass : Color Enhance block의 on/off 	'0' : CEN 적용 하지 않음 입력 RGB가 출력 RGB로 bypass	'1' : CEN 적용 됨
	UINT32 reg_cen_debug_mode               :1;	//8 //reg_cen_debug_mode	'0' : CR을 각각의 색으로 채색	'1' : Debugging Color의 PIXEL_GAIN 값을 Gray level로 표현
	UINT32 resvd2                           :1;
	UINT32 core_1st__gain_disable           :1;	//10 //1st Region core gain disable	1st Region core의 gain을 disable	'0' : Gain 적용	'1' : Gain 미적용
	UINT32 core_2nd_gain_disable            :1;	//11 //2nd core gain disable	2nd core의 gain을 disable	'0' : Gain 적용	'1' : Gain 미적용
	UINT32 resvd3                           :1;
	UINT32 debugging_mode_core              :2;	//14:13	//Debugging modeCore	Debugging mode의 적용 Core	'01' : 1st Core의 Debugging mode가 적용	'10' : 2nd Core의 Debugging mode가 적용	others : 1st core의 Debugging mode가 적용(show_color_region0, show_color_region1 으로 선택된 영역에 한해서)
	UINT32 resvd4                           :1;
	UINT32 demo_mode                        :8;	//23:16	//Demo Mode	'0111 1000' => 0x78	Algorithm 적용 영상과 원본영상의 경계 위치를 control	전체 화면 크기 / 16 : (ex) 1920 => 0x780 => reg_cen_ctrl0(23:16) = 0x78	화면의 좌측은 원본화면, 우측은 적용화면이며 커질 수록 원본 화면의 영역이 넓어짐
	UINT32 resvd5                           :7;
	UINT32 win_control_mode                 :1;	//31 //'0' : window control enabled	 '1' : win mode is always disabled
	};
}PE_E60_PE1_CEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6D4 RW
	UINT32 show_color_region0               :1;	//0 //Region 0을 Region_debug_color0 로 채색
	UINT32 show_color_region1               :1;	//1 //Region 1을 Region_debug_color1 로 채색
	UINT32 show_color_region2               :1;	//2 //Region 2을 Region_debug_color2 로 채색
	UINT32 show_color_region3               :1;	//3 //Region 3을 Region_debug_color3 로 채색
	UINT32 show_color_region4               :1;	//4 //Region 4을 Region_debug_color4 로 채색
	UINT32 show_color_region5               :1;	//5 //Region 5을 Region_debug_color5 로 채색
	UINT32 show_color_region6               :1;	//6 //Region 6을 Region_debug_color6 로 채색
	UINT32 show_color_region7               :1;	//7 //Region 7을 Region_debug_color7 로 채색
	UINT32 show_color_region8               :1;	//8 //Region 8을 Region_debug_color8 로 채색
	UINT32 show_color_region9               :1;	//9 //Region 9을 Region_debug_color9 로 채색
	UINT32 show_color_region10              :1;	//10 //Region 10을 Region_debug_color10 로 채색
	UINT32 show_color_region11              :1;	//11 //Region 11을 Region_debug_color11 로 채색
	UINT32 show_color_region12              :1;	//12 //Region 12을 Region_debug_color12 로 채색
	UINT32 show_color_region13              :1;	//13 //Region 13을 Region_debug_color13 로 채색
	UINT32 show_color_region14              :1;	//14 //Region 14을 Region_debug_color14 로 채색
	UINT32 show_color_region15              :1;	//15 //Region 15을 Region_debug_color15 로 채색
	UINT32 color_region_en0                 :1;	//16 //Region 0 enable
	UINT32 color_region_en1                 :1;	//17 //Region 1 enable
	UINT32 color_region_en2                 :1;	//18 //Region 2 enable
	UINT32 color_region_en3                 :1;	//19 //Region 3 enable
	UINT32 color_region_en4                 :1;	//20 //Region 4 enable
	UINT32 color_region_en5                 :1;	//21 //Region 5 enable
	UINT32 color_region_en6                 :1;	//22 //Region 6 enable
	UINT32 color_region_en7                 :1;	//23 //Region 7 enable
	UINT32 color_region_en8                 :1;	//24 //Region 8 enable
	UINT32 color_region_en9                 :1;	//25 //Region 9 enable
	UINT32 color_region_en10                :1;	//26 //Region 10 enable
	UINT32 color_region_en11                :1;	//27 //Region 11 enable
	UINT32 color_region_en12                :1;	//28 //Region 12 enable
	UINT32 color_region_en13                :1;	//29 //Region 13 enable
	UINT32 color_region_en14                :1;	//30 //Region 14 enable
	UINT32 color_region_en15                :1;	//31 //Region 15 enable
	};
}PE_E60_PE1_CEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6D8 RW
	UINT32 ihsv_sgain                       :8;	//7:0	//reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//15:8	//reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
}PE_E60_PE1_CEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6DC RW
	UINT32 ihsv_hoffset                     :8;	//7:0	//reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//15:8	//reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//23:16	//reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_CEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6E0 RW
	UINT32 reg_master_gain_cr0              :8;	//7:0	//Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//15:8	//Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//23:16	//Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//31:24	//Color region 3 master gain
	};
}PE_E60_PE1_CEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6E4 RW
	UINT32 reg_master_gain_cr4              :8;	//7:0	//Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//15:8	//Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//23:16	//Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//31:24	//Color region 7 master gain
	};
}PE_E60_PE1_CEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6E8 RW
	UINT32 reg_master_gain_cr8              :8;	//7:0	//Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//15:8	//Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//23:16	//Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//31:24	//Color region 11 master gain
	};
}PE_E60_PE1_CEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E6EC RW
	UINT32 reg_master_gain_cr12             :8;	//7:0	//Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//15:8	//Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//23:16	//Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//31:24	//Color region 15 master gain
	};
}PE_E60_PE1_CEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E700 WO
	UINT32 hif_cen_address                  :8;	//7:0	//hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//10:8	//reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//12 //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//14 //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//15 //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
}PE_E60_PE1_CEN_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E704 RO
	UINT32 hif_cen_y_wdata                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CEN_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E708 WO
	UINT32 hif_cen_delta_address            :5;	//4:0	//hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//12 //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//15 //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
}PE_E60_PE1_CEN_DELTA_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E70C RO
	UINT32 hif_cen_vr_data                  :8;	//7:0	//Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//15:8	//Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//23:16	//Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_CEN_DELTA_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E720 RW
	UINT32 dynamic_contrast_en              :1;	//0 //0' : disable	'1' : enable
	UINT32 hist_bin_mode                    :2;	//2:1	//00' : 32 bin mode	others : 16 bin mode
	UINT32 hist_clear                       :1;	//3 //Debugging purpose, force deleting for histogram memory.	'1' : clear
	UINT32 window01_enable                  :1;	//4 //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1' : window0 area only
	UINT32 window1_enable                   :1;	//6 //1' : window1 area only
	UINT32 window_acquire                   :1;	//7 //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//8 //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//9 //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//10 //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//11 //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//12 //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//13 //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//14 //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//15 //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//16 //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//17 //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//18 //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//19 //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//20 //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//21 //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//22 //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//23 //1' : enable Color Region 15 selection
	UINT32 dce_domain_sel                   :1;	//24 //0' : KTD/QTD(default)(K only)	'1' : YC (Y only)
	UINT32 resvd0                           :1;
	UINT32 window_mode_enable               :1;	//26 //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//27 //0' : selected area by window0, window1	'1' : otherside
	UINT32 histogram_mode                   :2;	//29:28	//00' : Own side's histogram data use	'01' : Other side's histogram data use	'10' : Average between Own and Other side's histogram data use
	UINT32 resvd1                           :2;
	};
}PE_E60_PE1_DCE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E724 RW
	UINT32 chroma_comp_color_region_gain    :8;	//7:0	//default : "128" ( 1 ~ 255(1~400%))
	UINT32 resvd0                           :8;
	UINT32 color_region_gain                :8;	//23:16	//default : "128" ( 1 ~ 255(1~400%)) (forbidden 0 value))
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_DCE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E728 RW
	UINT32 color_region_en                  :1;	//0 //Color region apply for DCE Y
	UINT32 color_debug_en                   :1;	//1 //Debug mode for Color region
	UINT32 resvd0                           :2;
	UINT32 y_grad_gain                      :2;	//5:4	//Gradient of Y signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd1                           :2;
	UINT32 cb_grad_gain                     :2;	//9:8	//Gradient of Cb signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd2                           :2;
	UINT32 cr_grad_gain                     :2;	//13:12	//Gradient of Cr signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd3                           :18;
	};
}PE_E60_PE1_DCE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E72C RW
	UINT32 y_range_min                      :10;	//9:0	//default : 480
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//25:16	//default : 720
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E730 RW
	UINT32 cb_range_min                     :10;	//9:0	//default : 612
	UINT32 resvd0                           :6;
	UINT32 cb_range_max                     :10;	//25:16	//default : 692
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E734 RW
	UINT32 cr_range_min                     :10;	//9:0	//default : 308
	UINT32 resvd0                           :6;
	UINT32 cr_range_max                     :10;	//25:16	//default : 508
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E738 RW
	UINT32 hif_dyc_address                  :5;	//4:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dce_load                     :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dce_ai                       :1;	//12 //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dce_enable                   :1;	//15 //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_E60_PE1_DCE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E73C RO
	UINT32 hif_dyc_wdata_y                  :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x                  :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E740 RW
	UINT32 hif_dyc_wdata_y_32nd             :10;	//9:0	//Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//25:16	//X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E744 RW
	UINT32 resvd0                           :1;
	UINT32 dce_ktd_csc_sel                  :1;	//1 //0' : KTD(default)	'1' : QTD
	UINT32 resvd1                           :30;
	};
}PE_E60_PE1_DCE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E748 RW
	UINT32 hif_hist_address                 :7;	//6:0	//"0"   : 0th bin	"1'   : 1st bin	…	"127" : 127st bin
	UINT32 resvd0                           :5;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//18:16	//"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//28 //auto increment enable
	UINT32 hif_mask                         :1;	//29 //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_E60_PE1_DCE_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E74C RO
	UINT32 hist_status0                     :25;	//24:0	//(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_E60_PE1_DCE_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E750 RO
	UINT32 hist_status1                     :29;	//28:0	//when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_E60_PE1_DCE_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E754 RW
	UINT32 dce_cb_gain2                     :10;	//9:0	//gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//25:16	//gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//28 //enable
	UINT32 resvd2                           :3;
	};
}PE_E60_PE1_DCE_CHR_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E758 RW
	UINT32 dce_chr_alpha2                   :10;	//9:0	//alpha(0~512), y_dce_in < y_dce_out : 0 means no gain
	UINT32 resvd0                           :6;
	UINT32 dce_chr_alpha1                   :10;	//25:16	//alpha(0~512), y_dce_in >= y_dce_out : 0 means no gain
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CHR_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E75C RW
	UINT32 dce_cr_gain2                     :10;	//9:0	//gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//25:16	//gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DCE_CHR_GAIN2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E770 RW
	UINT32 dynamic_saturation_en            :1;	//0 //0' : disable	'1' : enable
	UINT32 window_mode_enable               :1;	//1 //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//2 //0' : selected area by window0, window1	'1' : otherside
	UINT32 resvd0                           :1;
	UINT32 window01_enable                  :1;	//4 //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1' : window0 area only
	UINT32 window1_enable                   :1;	//6 //1' : window1 area only
	UINT32 window_acquire                   :1;	//7 //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//8 //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//9 //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//10 //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//11 //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//12 //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//13 //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//14 //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//15 //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//16 //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//17 //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//18 //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//19 //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//20 //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//21 //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//22 //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//23 //1' : enable Color Region 15 selection
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_DSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E774 RW
	UINT32 reg_dse_cr_mode_sel              :1;	//0 //0': use CEN color region gain, '1': use YH color region gain
	UINT32 reg_yh_cr_en                     :1;	//1 //Color region(YH) apply for DSE
	UINT32 reg_yh_debug                     :1;	//2 //Debug mode for Color region(YH)
	UINT32 resvd0                           :1;
	UINT32 r_dse_y_grad                     :2;	//5:4	//Gradient of Y signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd1                           :2;
	UINT32 r_dse_h_grad                     :2;	//9:8	//Gradient of H signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd2                           :14;
	UINT32 color_region_gain                :8;	//31:24	//default : "128" (200%, 1 ~ 255(1~400%)) (forbidden 0 value))
	};
}PE_E60_PE1_DSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E778 RW
	UINT32 hif_dse_wdata_y_32nd             :10;	//9:0	//Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//25:16	//X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E77C RW
	UINT32 hif_dse_address                  :5;	//4:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//12 //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//15 //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_E60_PE1_DSE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E780 RO
	UINT32 hif_dse_wdata_y                  :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DSE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E784 RW
	UINT32 y_range_min                      :10;	//9:0	//default : 568
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//25:16	//default : 650
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E788 RW
	UINT32 h_range_min                      :10;	//9:0	//default : 38
	UINT32 resvd0                           :6;
	UINT32 h_range_max                      :10;	//25:16	//default : 97
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_DSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E78C RW
	UINT32 reg_y_region_pt0_y               :8;	//7:0	//
	UINT32 reg_y_region_pt0_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E790 RW
	UINT32 reg_y_region_pt1_y               :8;	//7:0	//
	UINT32 reg_y_region_pt1_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E794 RW
	UINT32 reg_y_region_pt2_y               :8;	//7:0	//
	UINT32 reg_y_region_pt2_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E798 RW
	UINT32 reg_y_region_pt3_y               :8;	//7:0	//
	UINT32 reg_y_region_pt3_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E79C RW
	UINT32 reg_y_region_pt4_y               :8;	//7:0	//
	UINT32 reg_y_region_pt4_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7A0 RW
	UINT32 reg_y_region_pt5_y               :8;	//7:0	//
	UINT32 reg_y_region_pt5_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7A4 RW
	UINT32 reg_y_region_pt6_y               :8;	//7:0	//
	UINT32 reg_y_region_pt6_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7A8 RW
	UINT32 reg_y_region_pt7_y               :8;	//7:0	//
	UINT32 reg_y_region_pt7_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_Y_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7AC RW
	UINT32 reg_h_region_pt0_y               :8;	//7:0	//
	UINT32 reg_h_region_pt0_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7B0 RW
	UINT32 reg_h_region_pt1_y               :8;	//7:0	//
	UINT32 reg_h_region_pt1_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7B4 RW
	UINT32 reg_h_region_pt2_y               :8;	//7:0	//
	UINT32 reg_h_region_pt2_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7B8 RW
	UINT32 reg_h_region_pt3_y               :8;	//7:0	//
	UINT32 reg_h_region_pt3_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7BC RW
	UINT32 reg_h_region_pt4_y               :8;	//7:0	//
	UINT32 reg_h_region_pt4_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7C0 RW
	UINT32 reg_h_region_pt5_y               :8;	//7:0	//
	UINT32 reg_h_region_pt5_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7C4 RW
	UINT32 reg_h_region_pt6_y               :8;	//7:0	//
	UINT32 reg_h_region_pt6_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7C8 RW
	UINT32 reg_h_region_pt7_y               :8;	//7:0	//
	UINT32 reg_h_region_pt7_x               :10;	//17:8	//
	UINT32 resvd                            :14;
	};
}PE_E60_PE_DSE_H_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7E0 RW
	UINT32 reg_drc_en                       :1;	//0 //drc enable	'0' : disable	'1' : enable
	UINT32 reg_drc_cg_disable               :1;	//1 //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_rgb_sel                  :2;	//9:8	//"00" : luminance	"01" : MAX(r,g,b)	others : AVG(r,g,b)
	UINT32 resvd1                           :2;
	UINT32 reg_drc_gm_mode                  :3;	//14:12	//gamma lut enable	"01" : enable	others : disable
	UINT32 resvd2                           :1;
	UINT32 reg_drc_lk_blf_apf               :1;	//16 //use bypass spatial filter coefficient for debugging	'0' : disable 	'1' : enable
	UINT32 resvd3                           :11;
	UINT32 reg_dbg_disp_blf                 :1;	//28 //display blf image for debuging	'0' : disable	'1' : enable
	UINT32 reg_dbg_disp_lcont               :1;	//29 //display local contrast image for debugging	'0' : disable	'1' : enable
	UINT32 resvd4                           :2;
	};
}PE_E60_PE1_DRC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7E4 RW
	UINT32 reg_drc_gm_rw_sel                :1;	//0 //selecet a,b gamma lut for register r/w	'0' : a gamma lut 	'1' : b gamma lut
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//4 //selecet a,b gamma lut for operation	'0' : b gamma lut 	'1' : a gamma lut
	UINT32 resvd1                           :11;
	UINT32 reg_drc_gm_forced_sel            :1;	//16 //anytime rw_sel, op_sel transition
	UINT32 reg_drc_gm_protected_sel         :1;	//17 //Do not allow rw_sel, op_sel transition only in de active
	UINT32 resvd2                           :14;
	};
}PE_E60_PE1_DRC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7E8 RW
	UINT32 reg_drc_bnh                      :7;	//6:0	//horizontal block size (min : 4, max : 96)
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bnv                      :6;	//21:16	//vertical block size (min : 3, max : 54)
	UINT32 resvd1                           :10;
	};
}PE_E60_PE1_DRC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7EC RW
	UINT32 reg_drc_bsh                      :9;	//8:0	//
	UINT32 resvd0                           :7;
	UINT32 reg_drc_bsv                      :9;	//24:16	//
	UINT32 resvd1                           :7;
	};
}PE_E60_PE1_DRC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7F0 RW
	UINT32 reg_drc_gm_apl2                  :10;	//9:0	//apl for gamma lut 2
	UINT32 reg_drc_gm_apl1                  :10;	//19:10	//apl for gamma lut 1
	UINT32 reg_drc_gm_apl0                  :10;	//29:20	//apl for gamma lut 0
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7F4 RW
	UINT32 reg_drc_gm_apl5                  :10;	//9:0	//apl for gamma lut 5
	UINT32 reg_drc_gm_apl4                  :10;	//19:10	//apl for gamma lut 4
	UINT32 reg_drc_gm_apl3                  :10;	//29:20	//apl for gamma lut 3
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E7F8 RW
	UINT32 reg_drc_blf_wei_cen              :8;	//7:0	//center pixel weight for blf
	UINT32 resvd                            :24;
	};
}PE_E60_PE1_DRC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E830 RW
	UINT32 reg_drc_lut_addr_clr             :1;	//0 //lut address clear
	UINT32 resvd0                           :3;
	UINT32 reg_drc_hfc_rd_sel               :1;	//4 //blf h filter coefficient read select
	UINT32 resvd1                           :3;
	UINT32 reg_drc_vfc_rd_sel               :1;	//8 //blf v filter coefficient read select
	UINT32 resvd2                           :23;
	};
}PE_E60_PE1_DRC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E834 WO
	UINT32 reg_drc_lk_blf_hfc_data          :10;	//9:0	//blf h filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E838 WO
	UINT32 reg_drc_lk_blf_vfc_data          :10;	//9:0	//blf v filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E83C RW
	UINT32 reg_drc_hfc_rdata                :10;	//9:0	//RD[9:0]reg_drc_hfc_rdata: blf h filter coefficient read data	WR  [0]reg_drc_hfc_re : blf h filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E840 RW
	UINT32 reg_drc_vfc_rdata                :10;	//9:0	//RD[9:0]reg_drc_vfc_rdata : blf v filter coefficient read data	WR  [0]reg_drc_vfc_re : blf v filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E844 WO
	UINT32 reg_drc_blf_wei_wdata            :10;	//9:0	//blf photometric weight write data
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E848 RW
	UINT32 reg_drc_blf_wei_rdata            :10;	//9:0	//RD[9:0]reg_drc_blf_wei_rdata : blf photometric weight read data	WR  [0]reg_drc_blf_wei_re : blf photometric weight read enable
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E84C WO
	UINT32 reg_drc_gm_wdata                 :30;	//29:0	//gamma lut write data	[29:20] -> gamma lut 0	[19:10] -> gamma lut 1	[ 9: 0] -> gamma lut 2
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E850 RW
	UINT32 reg_drc_gm_rdata                 :30;	//29:0	//RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 0,[19:10] -> gamma lut 1,[ 9: 0] -> gamma lut 2	WR [1:0]reg_drc_gm_re : gamma lut 0, 1, 2 read enable ("01")
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E854 WO
	UINT32 reg_drc_gm_wdata                 :30;	//29:0	//gamma lut write data	[29:20] -> gamma lut 3	[19:10] -> gamma lut 4	[ 9: 0] -> gamma lut 5
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E858 RW
	UINT32 reg_drc_gm_rdata                 :30;	//29:0	//RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 3,[19:10] -> gamma lut 4,[ 9: 0] -> gamma lut 5	WR [1:0]reg_drc_gm_re : gamma lut 3, 4, 5 read enable ("10")
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DRC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E864 RW
	UINT32 reg_drc_bl_apl_raddr_h           :7;	//6:0	//block apl read H address
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bl_apl_raddr_v           :6;	//21:16	//block apl read V address
	UINT32 resvd1                           :10;
	};
}PE_E60_PE1_DRC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E868 RO
	UINT32 reg_drc_bl_apl_rdata             :10;	//9:0	//block apl read data
	UINT32 resvd                            :22;
	};
}PE_E60_PE1_DRC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E86C RO
	UINT32 reg_drc_gm_rw_sel                :1;	//0 //Read rw_sel
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//4 //Read op_sel
	UINT32 resvd1                           :27;
	};
}PE_E60_PE1_DRC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E880 RW
	UINT32 reg_pic_rptr_man                 :2;	//1:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_pic_rptr_man_en              :1;	//3 //
	UINT32 reg_pic_wptr_man                 :2;	//5:4	//
	UINT32 resvd1                           :1;
	UINT32 reg_pic_wptr_man_en              :1;	//7 //
	UINT32 reg_pic_data_man                 :2;	//9:8	//0: test data off	1: 128	2: gradient	3: horizontal box
	UINT32 reg_pic_rptr_on                  :1;	//10 //
	UINT32 reg_pic_wptr_on                  :1;	//11 //
	UINT32 reg_pic_wd_man                   :4;	//15:12	//16배, {reg_pic_wd_man,4'd0}
	UINT32 reg_pic_wd_man_on                :1;	//16 //
	UINT32 reg_pic_rd_lsb_man               :2;	//18:17	//0 : [1:0] = 0	1 : [1:0] = 3	2 : [1:0] = [3:2]	3 : [1:0] = [9:8]
	UINT32 reg_ro_buf_wrcnt                 :10;	//28:19	//
	UINT32 reg_ro_buf_wrsel                 :1;	//29 //
	UINT32 disp_clk_cg_on                   :1;	//30:30	//Logo L7 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//31:31	//Logo L7 de_clk clock gating
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E884 RW
	UINT32 reg_in_hoffset                   :13;	//12:0	//input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//28:16	//input window offset
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E888 RW
	UINT32 reg_in_hactive                   :13;	//12:0	//input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//28:16	//input window active size
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E88C RW
	UINT32 reg_in_hsize                     :13;	//12:0	//input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//28:16	//input source total size
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E890 RW
	UINT32 reg_out_pic_width                :13;	//12:0	//width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//28:16	//height(4320)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E894 RW
	UINT32 reg_phase_off_h                  :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_v                  :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :2;
	UINT32 reg_vsc_1to2_last_sel            :1;	//27:27	//0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//28:28	//0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//29:29	//'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//31:30	//'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E898 RW
	UINT32 reg_numerator_h                  :13;	//12:0	//120=4x30
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//28:16	//17
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E89C RW
	UINT32 reg_denominator_h                :13;	//12:0	//(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//28:16	//(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8A0 RW
	UINT32 win0_en                          :1;	//0:0	//1:  select only window0 as active area
	UINT32 win1_en                          :1;	//1:1	//1:  select only window1 as active area
	UINT32 win01_en                         :1;	//2:2	//1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//12:8	//border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//14:13	//border width
	UINT32 bdr_en                           :1;	//15:15	//border enable
	UINT32 cr5                              :5;	//20:16	//border color : cr5
	UINT32 cb5                              :5;	//25:21	//border color : cb5
	UINT32 yy6                              :6;	//31:26	//border color : yy6
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8A4 RW
	UINT32 win_w0_x0                        :13;	//12:0	//win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8A8 RW
	UINT32 win_w0_x1                        :13;	//12:0	//win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//28:16	//win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8AC RW
	UINT32 reg_out_hoffset                  :13;	//12:0	//output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//15:13	//4p hoffset
	UINT32 reg_out_voffset                  :13;	//28:16	//output window offset
	UINT32 resvd                            :3;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8B0 RW
	UINT32 reg_out_hactive                  :13;	//12:0	//output window active size : (1920=7680/4p)
	UINT32 reg_out_havg_4x_mode             :3;	//15:13	//0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//28:16	//output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//29:29	//0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//31:30	//0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8B4 RW
	UINT32 reg_logo_blend_alpha_l7_delay    :8;	//7:0	//16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 51 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blend_alpha_l3_delay    :8;	//15:8	//16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 51 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blned_alpha_c5_delay    :5;	//20:16	//csr_gain delay : default 16, 0(-16T)~16(0T for logo_blend_top)~31(15T)
	UINT32 resvd                            :11;
	};
}PE_E60_PE1_LOGO_L7SC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8B8 RW
	UINT32 mif_r_logo_gain_line_inc         :2;	//1:0	//
	UINT32 mif_r_logo_gain_pf_flag_en       :1;	//2:2	//
	UINT32 mif_r_logo_gain_manual_en        :1;	//3:3	//
	UINT32 mif_r_logo_gain_en               :1;	//4:4	//
	UINT32 mif_r_logo_vreverse              :1;	//5:5	//
	UINT32 resvd0                           :2;
	UINT32 logo_l3sc_out_sel                :2;	//9:8	//0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	UINT32 resvd1                           :6;
	UINT32 mif_r_logo_gain_voffset          :9;	//24:16	//MRD V offset
	UINT32 resvd2                           :5;
	UINT32 disp_clk_cg_on                   :1;	//30:30	//Logo L3 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//31:31	//Logo L3 de_clk clock gating
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8BC RW
	UINT32 reg_in_hoffset                   :13;	//12:0	//input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//28:16	//input window offset
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8C0 RW
	UINT32 reg_in_hactive                   :13;	//12:0	//input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//28:16	//input window active size
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8C4 RW
	UINT32 reg_in_hsize                     :13;	//12:0	//input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//28:16	//input source total size
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8C8 RW
	UINT32 reg_out_pic_width                :13;	//12:0	//width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//28:16	//height(4320)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8CC RW
	UINT32 reg_phase_off_h                  :9;	//8:0	//vertical offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd0                           :7;
	UINT32 reg_phase_off_v                  :9;	//24:16	//horizontal offset of initial pixel position	(signed value)  	min  : -255	max  : +255
	UINT32 resvd1                           :2;
	UINT32 reg_vsc_1to2_last_sel            :1;	//27:27	//0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//28:28	//0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//29:29	//'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//31:30	//'0' : normal-auto	     '1' : manual-set
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8D0 RW
	UINT32 reg_numerator_h                  :13;	//12:0	//1920=480x4
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//28:16	//270
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8D4 RW
	UINT32 reg_denominator_h                :13;	//12:0	//(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//28:16	//(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8D8 RW
	UINT32 win0_en                          :1;	//0:0	//1:  select only window0 as active area
	UINT32 win1_en                          :1;	//1:1	//1:  select only window1 as active area
	UINT32 win01_en                         :1;	//2:2	//1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//6:6	//0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//7:7	//0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//12:8	//border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//14:13	//border width
	UINT32 bdr_en                           :1;	//15:15	//border enable
	UINT32 cr5                              :5;	//20:16	//border color : cr5
	UINT32 cb5                              :5;	//25:21	//border color : cb5
	UINT32 yy6                              :6;	//31:26	//border color : yy6
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8DC RW
	UINT32 win_w0_x0                        :13;	//12:0	//win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//28:16	//win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8E0 RW
	UINT32 win_w0_x1                        :13;	//12:0	//win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//28:16	//win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8E4 RW
	UINT32 reg_out_hoffset                  :13;	//12:0	//output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//15:13	//4p hoffset
	UINT32 reg_out_voffset                  :13;	//28:16	//output window offset
	UINT32 resvd                            :3;
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8E8 RW
	UINT32 reg_out_hactive                  :13;	//12:0	//output window active size : 1920(7680/4)
	UINT32 reg_out_havg_4x_mode             :3;	//15:13	//0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//28:16	//output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//29:29	//0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//31:30	//0 : logo_l7sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_E60_PE1_LOGO_L3SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8EC RO
	UINT32 ibuf_logo_gain_vcnt              :9;	//8:0	//
	UINT32 resvd                            :23;
	};
}PE_E60_PE1_LOGO_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8F0 RO
	UINT32 current_out_line                 :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_LOGO_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8F4 RO
	UINT32 ibuf_logo_gain_vcnt              :9;	//8:0	//
	UINT32 resvd                            :23;
	};
}PE_E60_PE1_LOGO_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E8F8 RO
	UINT32 current_out_line                 :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_LOGO_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E910 RW
	UINT32 pcc_eotf_en                      :1;	//0 //
	UINT32 pcc_eotf_bit_extection_mode      :2;	//2:1	//
	UINT32 resvd0                           :2;
	UINT32 pcc_oetf_en                      :1;	//5 //
	UINT32 resvd1                           :2;
	UINT32 reg_pcc_en                       :1;	//8 //
	UINT32 resvd2                           :3;
	UINT32 reg_dither_en                    :1;	//12 //
	UINT32 resvd3                           :3;
	UINT32 reg_dither_temporal_en           :1;	//16 //
	UINT32 resvd4                           :3;
	UINT32 reg_sat_lut_in_mux               :1;	//20 //Saturatio alpha LUT input 0:pcc_input, 1:pcc_output
	UINT32 reg_l3d_in_mux                   :1;	//21 //3DLUT input 0:pcc_output, 1:pcc_input
	UINT32 reg_sat_blend_in_mux             :1;	//22 //Saturatio alpha blend input 0:pcc_output, 1:pcc_input
	UINT32 resvd5                           :9;
	};
}PE_E60_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E914 RW
	UINT32 reg_pcc_coef0                    :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E918 RW
	UINT32 reg_pcc_coef2                    :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E91C RW
	UINT32 reg_pcc_coef4                    :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E920 RW
	UINT32 reg_pcc_coef6                    :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E924 RW
	UINT32 reg_pcc_coef8                    :15;	//14:0	//
	UINT32 resvd                            :17;
	};
}PE_E60_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E928 RW
	UINT32 reg_sat_x3_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E92C RW
	UINT32 reg_sat_x1_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E930 RW
	UINT32 reg_sat_y3_i                     :8;	//7:0	//
	UINT32 reg_sat_y2_i                     :8;	//15:8	//
	UINT32 reg_sat_y1_i                     :8;	//23:16	//
	UINT32 reg_sat_y0_i                     :8;	//31:24	//
	};
}PE_E60_PE1_PCC_COEF7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E934 RW
	UINT32 oetf_addr                        :11;	//10:0	//indirect address
	UINT32 resvd0                           :1;
	UINT32 oetf_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//27 //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//29:28	//0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_E60_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E938 RW
	UINT32 oetf_lut_data_o                  :12;	//11:0	//12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//27:16	//12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E93C RW
	UINT32 eotf_wdata                       :15;	//14:0	//lut write data
	UINT32 resvd0                           :1;
	UINT32 eotf_waddr                       :10;	//25:16	//lut write address
	UINT32 resvd1                           :2;
	UINT32 eotf_we                          :3;	//30:28	//"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}PE_E60_PE1_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E940 RW/RO
	UINT32 eotf_lut_wr_done                 :1;	//0 //"1" : lut write done
	UINT32 resvd0                           :3;
	UINT32 eotf_lut_wr_status               :1;	//4 //lut write status
	UINT32 resvd1                           :27;
	};
}PE_E60_PE1_EOTF_WDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E944 RW/RO
	UINT32 eotf_rdata                       :15;	//14:0	//lut read data
	UINT32 resvd0                           :1;
	UINT32 eotf_raddr                       :10;	//25:16	//lut read address
	UINT32 resvd1                           :2;
	UINT32 eotf_re                          :3;	//30:28	//"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 eotf_rdata_sel                   :1;	//31 //lut read data sel 0:even, 1:odd
	};
}PE_E60_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E950 RW
	UINT32 ll_lut_addr                      :7;	//6:0	//indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//8 //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//12 //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_E60_PE1_LLLUT_E_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E954 RW
	UINT32 ll_lut_dat_rcr                   :10;	//9:0	//Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//19:10	//Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//29:20	//Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_LLLUT_E_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E958 RW
	UINT32 ll_lut_addr                      :7;	//6:0	//indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//8 //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//12 //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_E60_PE1_LLLUT_O_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E95C RW
	UINT32 ll_lut_dat_rcr                   :10;	//9:0	//Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//19:10	//Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//29:20	//Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_LLLUT_O_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E960 RW
	UINT32 reg_llctrl_enable                :1;	//0 //low level control enable
	UINT32 reg_llpcc_en                     :1;	//1 //PCC for low level control Enable
	UINT32 reg_llab_inp_sel                 :1;	//2 //low level alpha input sel 0:RGB2Y output, 1:max(RGB)
	UINT32 resvd0                           :5;
	UINT32 reg_hue_prsv_en                  :1;	//8 //hue preserving enable for low level alpha blending
	UINT32 reg_sat_prsv_en                  :1;	//9 //saturatione preserving enable for low level alpha blending
	UINT32 reg_hsp_en                       :1;	//10 //hue and saturatione preserving enable for low level alpha blending
	UINT32 resvd1                           :1;
	UINT32 reg_hue_prsv_cg_disable          :1;	//12 //clock gating disable
	UINT32 resvd2                           :19;
	};
}PE_E60_PE1_LLCORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E964 RW
	UINT32 reg_llpcc_coef0                  :15;	//14:0	//PCC10 Coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef1                  :15;	//30:16	//PCC10 Coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E968 RW
	UINT32 reg_llpcc_coef2                  :15;	//14:0	//PCC10 Coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef3                  :15;	//30:16	//PCC10 Coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E96C RW
	UINT32 reg_llpcc_coef4                  :15;	//14:0	//PCC10 Coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef5                  :15;	//30:16	//PCC10 Coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E970 RW
	UINT32 reg_llpcc_coef6                  :15;	//14:0	//PCC10 Coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef7                  :15;	//30:16	//PCC10 Coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E974 RW
	UINT32 reg_llpcc_coef8                  :15;	//14:0	//PCC10 Coefficient 8
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef0            :15;	//30:16	//alpha blendling RGB -> Y coef0
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E978 RW
	UINT32 reg_alpha_ii_yy_coef1            :15;	//14:0	//alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef2            :15;	//30:16	//alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_LLCORE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E97C RW
	UINT32 reg_llab_lut_y0                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x0                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E980 RW
	UINT32 reg_llab_lut_y1                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x1                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E984 RW
	UINT32 reg_llab_lut_y2                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x2                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E988 RW
	UINT32 reg_llab_lut_y3                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x3                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E98C RW
	UINT32 reg_llab_lut_y4                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x4                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E990 RW
	UINT32 reg_llab_lut_y5                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x5                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LLCORE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902E994 RW
	UINT32 reg_hue_prsv_ratio               :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_sat_prsv_ratio               :8;	//23:16	//
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_LLCORE_CTRL_13_T;


typedef union {
	UINT32 udata32;
	struct {						//0xC902F000 RW
	UINT32 enable                           :1;	//0 //
	UINT32 graycolor_enable                 :1;	//1 //
	UINT32 color_only_enable                :1;	//2 //
	UINT32 cb_info                          :1;	//3 //
	UINT32 cr_info                          :1;	//4 //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_en                      :1;	//6 //
	UINT32 resvd1                           :1;
	UINT32 center_position                  :8;	//15:8	//center position for contrast control(Y domain)
	UINT32 contrast                         :10;	//25:16	//contrast control(Y domain)
	UINT32 resvd2                           :2;
	UINT32 reg_vspyc_debug                  :3;	//30:28	//1,2:object_gain, 3: saturation_alpha, others:vsp_yc_out
	UINT32 resvd3                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F004 RW
	UINT32 saturation_target                :8;	//7:0	//
	UINT32 saturation                       :8;	//15:8	//
	UINT32 brightness                       :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F008 RW
	UINT32 r_yc2rgb_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F00C RW
	UINT32 r_yc2rgb_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F010 RW
	UINT32 r_yc2rgb_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F014 RW
	UINT32 r_yc2rgb_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F018 RW
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSPYC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F01C RW
	UINT32 r_yc2rgb_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_VSPYC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F020 RW
	UINT32 r_yc2rgb_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_VSPYC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F024 RW
	UINT32 r_yc2rgb_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst4                   :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSPYC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F030 RW
	UINT32 resvd0                           :4;
	UINT32 reg_crgn_objt_sel                :2;	//5:4	//0:multi(objt,crgn) 1:max(objt,crgn), 2:crgn, 3:objt
	UINT32 resvd1                           :2;
	UINT32 reg_yy_vv_sel                    :1;	//8 //0:Y, 1:V
	UINT32 reg_hsv_hsl_sel                  :1;	//9 //0:HSL, 1:HSV
	UINT32 reg_hsv_sat_sel                  :1;	//10 //0:(max(rgb)-min(rgb))/max(rgb), 1:max(rgb)-min(rgb)
	UINT32 resvd2                           :1;
	UINT32 reg_clock_gating_disable         :1;	//12 //
	UINT32 resvd3                           :19;
	};
}PE_E60_PE1_VSP_CC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F044 RW
	UINT32 reg_vspyc_tap_mode               :1;	//0 //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_vspyc_repeat_en              :1;	//4 //1:repeat(interpolation off)
	UINT32 resvd1                           :27;
	};
}PE_E60_PE1_VSP_CC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F050 RW
	UINT32 reg_crgn_hue_gain_y0             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F054 RW
	UINT32 reg_crgn_hue_gain_y1             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F058 RW
	UINT32 reg_crgn_hue_gain_y2             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F05C RW
	UINT32 reg_crgn_hue_gain_y3             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F060 RW
	UINT32 reg_crgn_hue_gain_y4             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F064 RW
	UINT32 reg_crgn_hue_gain_y5             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F068 RW
	UINT32 reg_crgn_hue_gain_y6             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F06C RW
	UINT32 reg_crgn_hue_gain_y7             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F070 RW
	UINT32 reg_crgn_sat_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x0             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x1             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F074 RW
	UINT32 reg_crgn_sat_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x2             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x3             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F078 RW
	UINT32 reg_crgn_sat_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x4             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x5             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F07C RW
	UINT32 reg_crgn_sat_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x6             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x7             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F080 RW
	UINT32 reg_crgn_val_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x0             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x1             :8;	//31:24	//
	};
}PE_E60_PE1_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F084 RW
	UINT32 reg_crgn_val_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x2             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x3             :8;	//31:24	//
	};
}PE_E60_PE1_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F088 RW
	UINT32 reg_crgn_val_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x4             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x5             :8;	//31:24	//
	};
}PE_E60_PE1_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F08C RO
	UINT32 reg_crgn_val_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x6             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x7             :8;	//31:24	//
	};
}PE_E60_PE1_VSP_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0A0 RW
	UINT32 enable_debug_mode                :1;	//0 //Enable debug mode
	UINT32 status_enable                    :1;	//1 //APL
	UINT32 debug_mode                       :1;	//2 //0' : status read(APL)	'1' : yc control
	UINT32 resvd0                           :17;
	UINT32 show_apl                         :1;	//20 //show apl( y, rgb, r,g,b)
	UINT32 resvd1                           :11;
	};
}PE_E60_PE1_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0A4 RW
	UINT32 yc_debug_en                      :1;	//0 //
	UINT32 force_yy_enable                  :1;	//1 //forcing Y data enable
	UINT32 force_cb_enable                  :1;	//2 //forcing Cb data enable
	UINT32 force_cr_enable                  :1;	//3 //forcing Cr data enable
	UINT32 yc_debug_mode_sel                :3;	//6:4	//"000" : normal	"001" : show Y only(grayscale)	"010" : show CbCr only	"011" : show Cb data at Y channel	"100" : show Cr data at Y channel	others : normal
	UINT32 resvd                            :25;
	};
}PE_E60_PE1_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0A8 RW
	UINT32 force_yy                         :10;	//9:0	//
	UINT32 force_cb                         :10;	//19:10	//forcing Cb data
	UINT32 force_cr                         :10;	//29:20	//forcing Cr data
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_DEBUG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0B0 RW
	UINT32 reg_cw_en                        :1;	//0 //
	UINT32 reg_cw_gain_sel                  :1;	//1 //0:external(from CEN) cr_gain, 1:internal cr_gain
	UINT32 resvd0                           :1;
	UINT32 reg_clock_gating_disable         :1;	//3 //
	UINT32 reg_cw_debug_view                :2;	//5:4	//0 := normal output	1 = final gain (R/G/B separate)	2 = cr_gain
	UINT32 resvd1                           :2;
	UINT32 reg_hsv_hsl_sel                  :1;	//8 //0:HSL, 1:HSV
	UINT32 reg_hsv_sat_sel                  :1;	//9 //0:(max(rgb)-min(rgb))/max(rgb), 1:max(rgb)-min(rgb)
	UINT32 resvd2                           :22;
	};
}PE_E60_PE1_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0B4 RW
	UINT32 user_ctrl_g_gain                 :8;	//7:0	//User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//15:8	//User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//23:16	//User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_CW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0B8 RW
	UINT32 color_region0_sel                :1;	//0 //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//1 //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//2 //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//3 //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//4 //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//5 //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//6 //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//7 //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//8 //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//9 //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//10 //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//11 //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//12 //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//13 //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//14 //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//15 //1' : enable Color Region 15 selection
	UINT32 color_region_gain                :8;	//23:16	//default : "64"( 0 ~ 255(1~400%))
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0C0 RW
	UINT32 reg_crgn_hue_gain_y0             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0C4 RW
	UINT32 reg_crgn_hue_gain_y1             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0C8 RW
	UINT32 reg_crgn_hue_gain_y2             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0CC RW
	UINT32 reg_crgn_hue_gain_y3             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0D0 RW
	UINT32 reg_crgn_hue_gain_y4             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0D4 RW
	UINT32 reg_crgn_hue_gain_y5             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0D8 RW
	UINT32 reg_crgn_hue_gain_y6             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0DC RW
	UINT32 reg_crgn_hue_gain_y7             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_CW_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0E0 RW
	UINT32 reg_crgn_sat_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x0             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x1             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_CW_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0E4 RW
	UINT32 reg_crgn_sat_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x2             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x3             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_CW_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0E8 RW
	UINT32 reg_crgn_sat_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x4             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x5             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_CW_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0EC RW
	UINT32 reg_crgn_sat_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x6             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x7             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_CW_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0F0 RW
	UINT32 reg_crgn_val_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x0             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x1             :8;	//31:24	//
	};
}PE_E60_PE1_CW_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0F4 RW
	UINT32 reg_crgn_val_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x2             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x3             :8;	//31:24	//
	};
}PE_E60_PE1_CW_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0F8 RW
	UINT32 reg_crgn_val_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x4             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x5             :8;	//31:24	//
	};
}PE_E60_PE1_CW_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F0FC RW
	UINT32 reg_crgn_val_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x6             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x7             :8;	//31:24	//
	};
}PE_E60_PE1_CW_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F110 RW
	UINT32 display_height                   :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 display_width                    :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LBLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F114 RW
	UINT32 reg_block_size_v                 :8;	//7:0	//
	UINT32 reg_block_size_h                 :8;	//15:8	//
	UINT32 reg_block_no_v                   :6;	//21:16	//
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//29:24	//
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//31 //
	};
}PE_E60_PE1_LBLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F118 RW
	UINT32 reg_last_block_size_v            :8;	//7:0	//
	UINT32 reg_last_block_size_h            :8;	//15:8	//
	UINT32 resvd                            :16;
	};
}PE_E60_PE1_LBLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F120 RW
	UINT32 reg_logo_blend_en                :1;	//0 //
	UINT32 reg_logo_blend_l7_disable        :1;	//1 //
	UINT32 reg_logo_blend_l3_disable        :1;	//2 //
	UINT32 reg_logo_blend_c5_disable        :1;	//3 //
	UINT32 reg_logo_master_gain             :8;	//11:4	//
	UINT32 reg_logo_debug_sel               :4;	//15:12	//0:debug_off, 1:c5_crnt_map, 2:l7_logo_map, 3:l3_logo_map, 4:region_gain, 5:boundary_gain, 6:merged_contrast_gain, 7:luma_drop_image, 8:merged_drop_gain, 9:l6_blur_image, A:merged_saturation_gain, B:saturation_gain, C:saturation_control_gain, others:debug_off
	UINT32 reg_region_gain_en               :1;	//16 //
	UINT32 resvd                            :3;
	UINT32 reg_logo_map_out_sel             :3;	//22:20	//0:max(merged contrast/drop/saturation gain), 1:l7_logo_map, 2:l3_logo_map, 3:c5_crnt_map, 4:merged_contrast_gain, 5:merged_drop_gain, 6:merged_saturation_gain, 7:max(merged drop/saturation_gain), others:max(merged contrast/drop/saturation gain)
	UINT32 reg_bound_proc_en                :1;	//23 //
	UINT32 reg_region_bnd_gain              :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F124 RW
	UINT32 resvd                            :1;
	UINT32 bound_proc_logocheck             :1;	//1 //
	UINT32 bound_proc_gain                  :8;	//9:2	//
	UINT32 bound_proc_range_x               :11;	//20:10	//
	UINT32 bound_proc_range_y               :11;	//31:21	//
	};
}PE_E60_PE1_LOGO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F128 RW
	UINT32 boundary_position_x0             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 boundary_position_x1             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F12C RW
	UINT32 boundary_position_y0             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 boundary_position_y1             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F130 RW
	UINT32 reg_region_bnd_x0                :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F134 RW
	UINT32 reg_region_bnd_y0                :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F138 RW
	UINT32 reg_region_position_x1           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F13C RW
	UINT32 reg_region_position_x3           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F140 RW
	UINT32 reg_region_position_x5           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F144 RW
	UINT32 reg_region_position_x7           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F148 RW
	UINT32 reg_region_position_y1           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F14C RW
	UINT32 reg_region_position_y3           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F150 RW
	UINT32 reg_region_position_y5           :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F154 RW
	UINT32 reg_region_gain_11               :8;	//7:0	//
	UINT32 reg_region_gain_21               :8;	//15:8	//
	UINT32 reg_region_gain_31               :8;	//23:16	//
	UINT32 reg_region_gain_41               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F158 RW
	UINT32 reg_region_gain_51               :8;	//7:0	//
	UINT32 reg_region_gain_61               :8;	//15:8	//
	UINT32 reg_region_gain_71               :8;	//23:16	//
	UINT32 reg_region_gain_81               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F15C RW
	UINT32 reg_region_gain_12               :8;	//7:0	//
	UINT32 reg_region_gain_22               :8;	//15:8	//
	UINT32 reg_region_gain_32               :8;	//23:16	//
	UINT32 reg_region_gain_42               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F160 RW
	UINT32 reg_region_gain_52               :8;	//7:0	//
	UINT32 reg_region_gain_62               :8;	//15:8	//
	UINT32 reg_region_gain_72               :8;	//23:16	//
	UINT32 reg_region_gain_82               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F164 RW
	UINT32 reg_region_gain_13               :8;	//7:0	//
	UINT32 reg_region_gain_23               :8;	//15:8	//
	UINT32 reg_region_gain_33               :8;	//23:16	//
	UINT32 reg_region_gain_43               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F168 RW
	UINT32 reg_region_gain_53               :8;	//7:0	//
	UINT32 reg_region_gain_63               :8;	//15:8	//
	UINT32 reg_region_gain_73               :8;	//23:16	//
	UINT32 reg_region_gain_83               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F16C RW
	UINT32 reg_region_gain_14               :8;	//7:0	//
	UINT32 reg_region_gain_24               :8;	//15:8	//
	UINT32 reg_region_gain_34               :8;	//23:16	//
	UINT32 reg_region_gain_44               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F170 RW
	UINT32 reg_region_gain_54               :8;	//7:0	//
	UINT32 reg_region_gain_64               :8;	//15:8	//
	UINT32 reg_region_gain_74               :8;	//23:16	//
	UINT32 reg_region_gain_84               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F174 RW
	UINT32 reg_region_gain_15               :8;	//7:0	//
	UINT32 reg_region_gain_25               :8;	//15:8	//
	UINT32 reg_region_gain_35               :8;	//23:16	//
	UINT32 reg_region_gain_45               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F178 RW
	UINT32 reg_region_gain_55               :8;	//7:0	//
	UINT32 reg_region_gain_65               :8;	//15:8	//
	UINT32 reg_region_gain_75               :8;	//23:16	//
	UINT32 reg_region_gain_85               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F17C RW
	UINT32 reg_region_gain_16               :8;	//7:0	//
	UINT32 reg_region_gain_26               :8;	//15:8	//
	UINT32 reg_region_gain_36               :8;	//23:16	//
	UINT32 reg_region_gain_46               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F180 RW
	UINT32 reg_region_gain_56               :8;	//7:0	//
	UINT32 reg_region_gain_66               :8;	//15:8	//
	UINT32 reg_region_gain_76               :8;	//23:16	//
	UINT32 reg_region_gain_86               :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F184 RW
	UINT32 reg_sat_x3_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F188 RW
	UINT32 reg_sat_x1_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F18C RW
	UINT32 reg_sat_y3_i                     :8;	//7:0	//
	UINT32 reg_sat_y2_i                     :8;	//15:8	//
	UINT32 reg_sat_y1_i                     :8;	//23:16	//
	UINT32 reg_sat_y0_i                     :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F190 RW
	UINT32 reg_drop_x7_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F194 RW
	UINT32 reg_drop_x5_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F198 RW
	UINT32 reg_drop_x3_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F19C RW
	UINT32 reg_drop_x1_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1A0 RW
	UINT32 reg_drop_y7_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1A4 RW
	UINT32 reg_drop_y5_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1A8 RW
	UINT32 reg_drop_y3_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1AC RW
	UINT32 reg_drop_y1_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1B0 RW
	UINT32 reg_sat_scon_x3_i                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x2_i                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1B4 RW
	UINT32 reg_sat_scon_x1_i                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x0_i                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1B8 RW
	UINT32 reg_sat_scon_y3_i                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y2_i                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1BC RW
	UINT32 reg_sat_scon_y1_i                :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y0_i                :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_LOGO_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1C0 RW
	UINT32 reg_l7_gain_drop                 :8;	//7:0	//
	UINT32 reg_l7_gain_w_contrast           :8;	//15:8	//white(bright) contrast gain(input level < output level)
	UINT32 reg_l7_gain_b_contrast           :8;	//23:16	//black(dark) contrast gain(input level > output level)
	UINT32 reg_l7_gain_saturation           :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1C4 RW
	UINT32 reg_l3_gain_drop                 :8;	//7:0	//
	UINT32 reg_l3_gain_w_contrast           :8;	//15:8	//white(bright) contrast gain(input level < output level)
	UINT32 reg_l3_gain_b_contrast           :8;	//23:16	//black(dark) contrast gain(input level > output level)
	UINT32 reg_l3_gain_saturation           :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1C8 RW
	UINT32 reg_c5_gain_drop                 :8;	//7:0	//
	UINT32 reg_c5_gain_w_contrast           :8;	//15:8	//white(bright) contrast gain(input level < output level)
	UINT32 reg_c5_gain_b_contrast           :8;	//23:16	//black(dark) contrast gain(input level > output level)
	UINT32 reg_c5_gain_saturation           :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1CC RW
	UINT32 reg_pxl_x0_0                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//15 //disable LOGO inside window
	UINT32 reg_pxl_y0_0                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//31 //disable LOGO outside window
	};
}PE_E60_PE1_LOGO_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1D0 RW
	UINT32 reg_pxl_width_0                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1D4 RW
	UINT32 reg_merge_contrast_l7l3          :10;	//9:0	//
	UINT32 reg_merge_contrast_l7l3c5        :10;	//19:10	//
	UINT32 reg_merge_drop_l7l3              :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_LOGO_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1D8 RW
	UINT32 reg_merge_drop_l7l3c5            :10;	//9:0	//
	UINT32 reg_merge_saturation_l7l3        :10;	//19:10	//
	UINT32 reg_merge_saturation_l7l3c5      :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_LOGO_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1DC RW
	UINT32 reg_pxl_x0_1                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//15 //disable LOGO inside window
	UINT32 reg_pxl_y0_1                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//31 //disable LOGO outside window
	};
}PE_E60_PE1_LOGO_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1E0 RW
	UINT32 reg_pxl_width_1                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1E4 RW
	UINT32 reg_pxl_x0_2                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_2             :1;	//15 //disable LOGO inside window
	UINT32 reg_pxl_y0_2                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_2            :1;	//31 //disable LOGO outside window
	};
}PE_E60_PE1_LOGO_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1E8 RW
	UINT32 reg_pxl_width_2                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_2                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1EC RW
	UINT32 reg_pxl_x0_3                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_3             :1;	//15 //disable LOGO inside window
	UINT32 reg_pxl_y0_3                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_3            :1;	//31 //disable LOGO outside window
	};
}PE_E60_PE1_LOGO_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1F0 RW
	UINT32 reg_pxl_width_3                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_3                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_LOGO_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1F4 RW
	UINT32 reg_txt_x3_i                     :8;	//7:0	//texture gain LUT
	UINT32 reg_txt_x2_i                     :8;	//15:8	//
	UINT32 reg_txt_x1_i                     :8;	//23:16	//
	UINT32 reg_txt_x0_i                     :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1F8 RW
	UINT32 reg_txt_y3_i                     :8;	//7:0	//
	UINT32 reg_txt_y2_i                     :8;	//15:8	//
	UINT32 reg_txt_y1_i                     :8;	//23:16	//
	UINT32 reg_txt_y0_i                     :8;	//31:24	//
	};
}PE_E60_PE1_LOGO_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F1FC RW
	UINT32 reg_region_gain_contrast         :8;	//7:0	//1.0 = 128
	UINT32 reg_region_gain_drop             :8;	//15:8	//
	UINT32 reg_region_gain_saturation       :8;	//23:16	//
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_LOGO_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F200 RW
	UINT32 reg_logo_tap_mode                :1;	//0 //0:2tap, 1:4tap
	UINT32 resvd0                           :3;
	UINT32 reg_logo_repeat_en               :1;	//4 //
	UINT32 resvd1                           :27;
	};
}PE_E60_PE1_LOGO_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F220 RW
	UINT32 reg_gsr_blend_en                 :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//7:4	//0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//25:16	//
	UINT32 resvd2                           :6;
	};
}PE_E60_PE1_GSR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F224 RW
	UINT32 reg_curr_peak_level              :10;	//9:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_crnt_resol_sel               :4;	//15:12	//left shift bit size, 0:8b, 1:7b, 2:6b, 3:5b, 4:4b, 5:3b, 6:2b, 7:1b, 8:0b
	UINT32 reg_wg_ratio                     :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_GSR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F228 RW
	UINT32 reg_wb_ratio                     :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_PE1_GSR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F22C RW
	UINT32 reg_w_crnt_wgt                   :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_GSR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F230 RW
	UINT32 reg_b_crnt_wgt                   :12;	//11:0	//
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//27:16	//
	UINT32 resvd1                           :4;
	};
}PE_E60_PE1_GSR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F234 RW
	UINT32 reg_crnt_lut_y00                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x00                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F238 RW
	UINT32 reg_crnt_lut_y01                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x01                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F23C RW
	UINT32 reg_crnt_lut_y02                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x02                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F240 RW
	UINT32 reg_crnt_lut_y03                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x03                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F244 RW
	UINT32 reg_crnt_lut_y04                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x04                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F248 RW
	UINT32 reg_crnt_lut_y05                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x05                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F24C RW
	UINT32 reg_crnt_lut_y06                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x06                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F250 RW
	UINT32 reg_crnt_lut_y07                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x07                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F254 RW
	UINT32 reg_crnt_lut_y08                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x08                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F258 RW
	UINT32 reg_crnt_lut_y09                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x09                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F25C RW
	UINT32 reg_crnt_lut_y10                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x10                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F260 RW
	UINT32 reg_crnt_lut_y11                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x11                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F264 RW
	UINT32 reg_crnt_lut_y12                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x12                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F268 RW
	UINT32 reg_crnt_lut_y13                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x13                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F26C RW
	UINT32 reg_crnt_lut_y14                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x14                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F270 RW
	UINT32 reg_crnt_lut_y15                 :16;	//15:0	//
	UINT32 reg_crnt_lut_x15                 :10;	//25:16	//
	UINT32 resvd                            :6;
	};
}PE_E60_PE1_GSR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F274 RW
	UINT32 reg_crnt_x3_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x2_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F278 RW
	UINT32 reg_crnt_x1_i                    :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x0_i                    :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F27C RW
	UINT32 reg_crnt_y3_i                    :8;	//7:0	//
	UINT32 reg_crnt_y2_i                    :8;	//15:8	//
	UINT32 reg_crnt_y1_i                    :8;	//23:16	//
	UINT32 reg_crnt_y0_i                    :8;	//31:24	//
	};
}PE_E60_PE1_GSR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F280 RW
	UINT32 reg_value_x3_i                   :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_value_x2_i                   :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F284 RW
	UINT32 reg_value_x1_i                   :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_value_x0_i                   :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F288 RW
	UINT32 reg_value_y3_i                   :8;	//7:0	//
	UINT32 reg_value_y2_i                   :8;	//15:8	//
	UINT32 reg_value_y1_i                   :8;	//23:16	//
	UINT32 reg_value_y0_i                   :8;	//31:24	//
	};
}PE_E60_PE1_GSR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F28C RW
	UINT32 reg_sat_x3_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F290 RW
	UINT32 reg_sat_x1_i                     :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
}PE_E60_PE1_GSR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F294 RW
	UINT32 reg_sat_y3_i                     :8;	//7:0	//
	UINT32 reg_sat_y2_i                     :8;	//15:8	//
	UINT32 reg_sat_y1_i                     :8;	//23:16	//
	UINT32 reg_sat_y0_i                     :8;	//31:24	//
	};
}PE_E60_PE1_GSR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F298 RW
	UINT32 reg_pxl_x0_0                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//15 //disable GSR inside window
	UINT32 reg_pxl_y0_0                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//31 //disable GSR outside window
	};
}PE_E60_PE1_GSR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F29C RW
	UINT32 reg_pxl_width_0                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_GSR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2A0 RW
	UINT32 reg_pxl_x0_1                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//15 //disable GSR inside window
	UINT32 reg_pxl_y0_1                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//31 //disable GSR outside window
	};
}PE_E60_PE1_GSR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2A4 RW
	UINT32 reg_pxl_width_1                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_GSR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2A8 RW
	UINT32 reg_pxl_x0_2                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_2             :1;	//15 //disable GSR inside window
	UINT32 reg_pxl_y0_2                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_2            :1;	//31 //disable GSR outside window
	};
}PE_E60_PE1_GSR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2AC RW
	UINT32 reg_pxl_width_2                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_2                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_GSR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2B0 RW
	UINT32 reg_pxl_x0_3                     :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_3             :1;	//15 //disable GSR inside window
	UINT32 reg_pxl_y0_3                     :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_3            :1;	//31 //disable GSR outside window
	};
}PE_E60_PE1_GSR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2B4 RW
	UINT32 reg_pxl_width_3                  :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_3                 :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_GSR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2E0 RW
	UINT32 pxl_rep_xpos_0                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2E4 RW
	UINT32 pxl_rep_width_0                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2E8 RW
	UINT32 pxl_rep_value_g                  :10;	//9:0	//g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//19:10	//b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//29:20	//r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2EC RW
	UINT32 pxl_rep_value_g                  :10;	//9:0	//g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//19:10	//b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//29:20	//r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_MUTE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2F0 RW
	UINT32 reg_col_fil_g_valid              :1;	//0 //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//1 //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//2 //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//3 //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//4 //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//5 //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_E60_PE1_MUTE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2F4 RW
	UINT32 pxl_rep_xpos_0                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2F8 RW
	UINT32 pxl_rep_width_0                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F2FC RW
	UINT32 pxl_rep_value_g                  :10;	//9:0	//g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//19:10	//b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//29:20	//r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F300 RW
	UINT32 pxl_rep_value_g                  :10;	//9:0	//g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//19:10	//b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//29:20	//r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_E60_PE1_MUTE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F304 RW
	UINT32 reg_col_fil_g_valid              :1;	//0 //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//1 //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//2 //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//3 //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//4 //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//5 //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_E60_PE1_MUTE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F308 RW
	UINT32 mux3d_en                         :1;	//0 //Mux 3D on/off	'0' = off	'1' = on
	UINT32 resvd0                           :3;
	UINT32 reg_out_mux                      :2;	//5:4	//output select	'00' = blend	'01' = R	'10' = L	'11' = line by line
	UINT32 start_parity                     :1;	//6 //start parity	'0' : start with Left	'1' : start with Right
	UINT32 resvd1                           :9;
	UINT32 alpha1_gain                      :8;	//23:16	//gain for L, R channel blend	255 : L output ~ 0 : R output
	UINT32 alpha0_gain                      :8;	//31:24	//gain for Back Ground Color and Blended Data	255 : BG Color output ~ 0 : Data output
	};
}PE_E60_PE1_MUTE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F30C RW
	UINT32 x0_0                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_0              :1;	//15 //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_0              :1;	//31 //L channel (vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F310 RW
	UINT32 x1_0                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F314 RW
	UINT32 x0_0                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_0              :1;	//15 //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_0              :1;	//31 //(vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F318 RW
	UINT32 x1_0                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F31C RW
	UINT32 bg_color_r                       :8;	//7:0	//8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//15:8	//8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//23:16	//8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}PE_E60_PE1_MUTE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F320 RW
	UINT32 pxl_rep_xpos_1                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F324 RW
	UINT32 pxl_rep_width_1                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F328 RW
	UINT32 pxl_rep_xpos_1                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F32C RW
	UINT32 pxl_rep_width_1                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F330 RW
	UINT32 x0_1                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_1              :1;	//15 //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_1              :1;	//31 //L channel (vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F334 RW
	UINT32 x1_1                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F338 RW
	UINT32 x0_1                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_1              :1;	//15 //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_1              :1;	//31 //(vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F33C RW
	UINT32 x1_1                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F340 RW
	UINT32 pxl_rep_xpos_2                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_2                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_2                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_2                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F344 RW
	UINT32 pxl_rep_width_2                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_2                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F348 RW
	UINT32 pxl_rep_xpos_2                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_2                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_2                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_2                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F34C RW
	UINT32 pxl_rep_width_2                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_2                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F350 RW
	UINT32 x0_2                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_2              :1;	//15 //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_2                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_2              :1;	//31 //L channel (vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F354 RW
	UINT32 x1_2                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_2                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F358 RW
	UINT32 x0_2                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_2              :1;	//15 //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_2                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_2              :1;	//31 //(vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F35C RW
	UINT32 x1_2                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_2                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F360 RW
	UINT32 pxl_rep_xpos_3                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_3                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_3                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_3                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F364 RW
	UINT32 pxl_rep_width_3                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_3                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F368 RW
	UINT32 pxl_rep_xpos_3                   :13;	//12:0	//x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_3                   :13;	//28:16	//y position for pixel replacement
	UINT32 pxl_rep_in_3                     :1;	//29 //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_3                    :1;	//30 //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_E60_PE1_MUTE_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F36C RW
	UINT32 pxl_rep_width_3                  :13;	//12:0	//width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_3                 :13;	//28:16	//height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F370 RW
	UINT32 x0_3                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_3              :1;	//15 //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_3                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_3              :1;	//31 //L channel (vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F374 RW
	UINT32 x1_3                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_3                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F378 RW
	UINT32 x0_3                             :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_3              :1;	//15 //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_3                             :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_3              :1;	//31 //(vertical) window mode enable
	};
}PE_E60_PE1_MUTE_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F37C RW
	UINT32 x1_3                             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 y1_3                             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MUTE_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F410 RW
	UINT32 reg_textgain_en                  :1;	//0 //
	UINT32 reg_bodygain_en                  :1;	//1 //
	UINT32 reg_headgain_en                  :1;	//2 //
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :1;	//4 //0:max, 1:sum
	UINT32 reg_head_body_sel                :1;	//5 //0:max, 1:sum
	UINT32 resvd1                           :2;
	UINT32 reg_text_master_gain             :8;	//15:8	//
	UINT32 reg_body_master_gain             :8;	//23:16	//
	UINT32 reg_head_master_gain             :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F414 RW
	UINT32 reg_headgain_y1_i                :8;	//7:0	//head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//15:8	//
	UINT32 reg_headgain_y0_i                :8;	//23:16	//
	UINT32 reg_headgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F418 RW
	UINT32 reg_headgain_y3_i                :8;	//7:0	//
	UINT32 reg_headgain_x3_i                :8;	//15:8	//
	UINT32 reg_headgain_y2_i                :8;	//23:16	//
	UINT32 reg_headgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F41C RW
	UINT32 reg_bodygain_y1_i                :8;	//7:0	//body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//15:8	//
	UINT32 reg_bodygain_y0_i                :8;	//23:16	//
	UINT32 reg_bodygain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F420 RW
	UINT32 reg_bodygain_y3_i                :8;	//7:0	//
	UINT32 reg_bodygain_x3_i                :8;	//15:8	//
	UINT32 reg_bodygain_y2_i                :8;	//23:16	//
	UINT32 reg_bodygain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F424 RW
	UINT32 reg_textgain_y1_i                :8;	//7:0	//texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//15:8	//
	UINT32 reg_textgain_y0_i                :8;	//23:16	//
	UINT32 reg_textgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F428 RW
	UINT32 reg_textgain_y3_i                :8;	//7:0	//
	UINT32 reg_textgain_x3_i                :8;	//15:8	//
	UINT32 reg_textgain_y2_i                :8;	//23:16	//
	UINT32 reg_textgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F42C RW
	UINT32 reg_pxl_x0                       :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//15 //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//31 //disable merge_gain outside window
	};
}PE_E60_PE1_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F430 RW
	UINT32 reg_pxl_width                    :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F434 RW
	UINT32 reg_win_in_objt_gain             :8;	//7:0	//inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//23:16	//outside window gain
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F438 RW
	UINT32 reg_textgain_en                  :1;	//0 //
	UINT32 reg_bodygain_en                  :1;	//1 //
	UINT32 reg_headgain_en                  :1;	//2 //
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :1;	//4 //0:max, 1:sum
	UINT32 reg_head_body_sel                :1;	//5 //0:max, 1:sum
	UINT32 resvd1                           :2;
	UINT32 reg_text_master_gain             :8;	//15:8	//
	UINT32 reg_body_master_gain             :8;	//23:16	//
	UINT32 reg_head_master_gain             :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F43C RW
	UINT32 reg_headgain_y1_i                :8;	//7:0	//head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//15:8	//
	UINT32 reg_headgain_y0_i                :8;	//23:16	//
	UINT32 reg_headgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F440 RW
	UINT32 reg_headgain_y3_i                :8;	//7:0	//
	UINT32 reg_headgain_x3_i                :8;	//15:8	//
	UINT32 reg_headgain_y2_i                :8;	//23:16	//
	UINT32 reg_headgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F444 RW
	UINT32 reg_bodygain_y1_i                :8;	//7:0	//body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//15:8	//
	UINT32 reg_bodygain_y0_i                :8;	//23:16	//
	UINT32 reg_bodygain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F448 RW
	UINT32 reg_bodygain_y3_i                :8;	//7:0	//
	UINT32 reg_bodygain_x3_i                :8;	//15:8	//
	UINT32 reg_bodygain_y2_i                :8;	//23:16	//
	UINT32 reg_bodygain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F44C RW
	UINT32 reg_textgain_y1_i                :8;	//7:0	//texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//15:8	//
	UINT32 reg_textgain_y0_i                :8;	//23:16	//
	UINT32 reg_textgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F450 RW
	UINT32 reg_textgain_y3_i                :8;	//7:0	//
	UINT32 reg_textgain_x3_i                :8;	//15:8	//
	UINT32 reg_textgain_y2_i                :8;	//23:16	//
	UINT32 reg_textgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F454 RW
	UINT32 reg_pxl_x0                       :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//15 //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//31 //disable merge_gain outside window
	};
}PE_E60_PE1_MERGE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F458 RW
	UINT32 reg_pxl_width                    :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MERGE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F45C RW
	UINT32 reg_win_in_objt_gain             :8;	//7:0	//inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//23:16	//outside window gain
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_MERGE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F460 RW
	UINT32 reg_textgain_en                  :1;	//0 //
	UINT32 reg_bodygain_en                  :1;	//1 //
	UINT32 reg_headgain_en                  :1;	//2 //
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :1;	//4 //0:max, 1:sum
	UINT32 reg_head_body_sel                :1;	//5 //0:max, 1:sum
	UINT32 resvd1                           :2;
	UINT32 reg_text_master_gain             :8;	//15:8	//
	UINT32 reg_body_master_gain             :8;	//23:16	//
	UINT32 reg_head_master_gain             :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F464 RW
	UINT32 reg_headgain_y1_i                :8;	//7:0	//head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//15:8	//
	UINT32 reg_headgain_y0_i                :8;	//23:16	//
	UINT32 reg_headgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F468 RW
	UINT32 reg_headgain_y3_i                :8;	//7:0	//
	UINT32 reg_headgain_x3_i                :8;	//15:8	//
	UINT32 reg_headgain_y2_i                :8;	//23:16	//
	UINT32 reg_headgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F46C RW
	UINT32 reg_bodygain_y1_i                :8;	//7:0	//body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//15:8	//
	UINT32 reg_bodygain_y0_i                :8;	//23:16	//
	UINT32 reg_bodygain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F470 RW
	UINT32 reg_bodygain_y3_i                :8;	//7:0	//
	UINT32 reg_bodygain_x3_i                :8;	//15:8	//
	UINT32 reg_bodygain_y2_i                :8;	//23:16	//
	UINT32 reg_bodygain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F474 RW
	UINT32 reg_textgain_y1_i                :8;	//7:0	//texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//15:8	//
	UINT32 reg_textgain_y0_i                :8;	//23:16	//
	UINT32 reg_textgain_x0_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F478 RW
	UINT32 reg_textgain_y3_i                :8;	//7:0	//
	UINT32 reg_textgain_x3_i                :8;	//15:8	//
	UINT32 reg_textgain_y2_i                :8;	//23:16	//
	UINT32 reg_textgain_x2_i                :8;	//31:24	//
	};
}PE_E60_PE1_MERGE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F47C RW
	UINT32 reg_pxl_x0                       :13;	//12:0	//
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//15 //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//28:16	//
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//31 //disable merge_gain outside window
	};
}PE_E60_PE1_MERGE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F480 RW
	UINT32 reg_pxl_width                    :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_PE1_MERGE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC902F484 RW
	UINT32 reg_win_in_objt_gain             :8;	//7:0	//inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//23:16	//outside window gain
	UINT32 resvd1                           :8;
	};
}PE_E60_PE1_MERGE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030300 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030304 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030308 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903030C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030310 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030314 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030318 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903031C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030320 RW 0x0000_0000
	UINT32 reg_sys_veri_8                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030324 RW 0x0000_0000
	UINT32 reg_sys_veri_9                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030328 RW 0x0000_0000
	UINT32 reg_sys_veri_10                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903032C RW 0x0000_0000
	UINT32 reg_sys_veri_11                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030330 RW 0x0000_0000
	UINT32 reg_sys_veri_12                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030334 RW 0x0000_0000
	UINT32 reg_sys_veri_13                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030338 RW 0x0000_0000
	UINT32 reg_sys_veri_14                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903033C RW 0x0000_0000
	UINT32 reg_sys_veri_15                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030340 RW 0x0000_0000
	UINT32 reg_sys_veri_16                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030344 RW 0x0000_0000
	UINT32 reg_sys_veri_17                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030348 RW 0x0000_0000
	UINT32 reg_sys_veri_18                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903034C RW 0x0000_0000
	UINT32 reg_sys_veri_19                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_19_T;


typedef union {
	UINT32 udata32;
	struct {						//0xC9030350 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030354 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030358 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903035C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030360 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030364 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030368 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903036C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_E60_CCO1_SYS_VERI_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030370 RW 0x0000_0000
	UINT32 reg_sys_veri_28                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030374 RW 0x0000_0000
	UINT32 reg_sys_veri_29                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030378 RW 0x0000_0000
	UINT32 reg_sys_veri_30                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903037C RW 0x0000_0000
	UINT32 reg_sys_veri_31                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030380 RW 0x0000_0000
	UINT32 reg_sys_veri_32                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030384 RW 0x0000_0000
	UINT32 reg_sys_veri_33                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9030388 RW 0x0000_0000
	UINT32 reg_sys_veri_34                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC903038C RW 0x0000_0000
	UINT32 reg_sys_veri_35                  :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_E60_CCO1_SYS_VERI_35_T;

typedef struct {
	PE_E60_PE1_TOP_CTRL_00_T                            pe1_top_ctrl_00;	//0xC902E500
	PE_E60_PE1_TOP_CTRL_01_T                            pe1_top_ctrl_01;	//0xC902E504
	PE_E60_PE1_TOP_CTRL_02_T                            pe1_top_ctrl_02;	//0xC902E508
	PE_E60_PE1_TOP_CTRL_03_T                            pe1_top_ctrl_03;	//0xC902E50C
	PE_E60_PE1_TOP_CTRL_04_T                            pe1_top_ctrl_04;	//0xC902E510
	UINT32                                                    reserved0;	//0xC902E514
	UINT32                                                    reserved1;	//0xC902E518
	UINT32                                                    reserved2;	//0xC902E51C
	PE_E60_CC_PE1_FSW_CTRL_00_T                            pe1_fsw_ctrl_00;	//0xC902E520
	PE_E60_CC_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xC902E524
	PE_E60_CC_PE1_FSW_CTRL_02_T                            pe1_fsw_ctrl_02;	//0xC902E528
	PE_E60_CC_PE1_FSW_CTRL_03_T                            pe1_fsw_ctrl_03;	//0xC902E52C
	PE_E60_CC_PE1_FSW_CTRL_04_T                            pe1_fsw_ctrl_04;	//0xC902E530
	PE_E60_CC_PE1_FSW_CTRL_05_T                            pe1_fsw_ctrl_05;	//0xC902E534
	PE_E60_CC_PE1_FSW_CTRL_06_T                            pe1_fsw_ctrl_06;	//0xC902E538
	PE_E60_CC_PE1_FSW_CTRL_07_T                            pe1_fsw_ctrl_07;	//0xC902E53C
	UINT32                                                    reserved3;	//0xC902E540
	UINT32                                                    reserved4;	//0xC902E544
	UINT32                                                    reserved5;	//0xC902E548
	UINT32                                                    reserved6;	//0xC902E54C
	PE_E60_PE1_TPG_CTRL_00_T                            pe1_tpg_ctrl_00;	//0xC902E550
	PE_E60_PE1_TPG_CTRL_01_T                            pe1_tpg_ctrl_01;	//0xC902E554
	PE_E60_PE1_TPG_CTRL_02_T                            pe1_tpg_ctrl_02;	//0xC902E558
	PE_E60_PE1_TPG_CTRL_03_T                            pe1_tpg_ctrl_03;	//0xC902E55C
	PE_E60_PE1_TPG_CTRL_04_T                            pe1_tpg_ctrl_04;	//0xC902E560
	PE_E60_PE1_TPG_IA_CTRL_T                            pe1_tpg_ia_ctrl;	//0xC902E564
	PE_E60_PE1_TPG_IA_DATA_T                            pe1_tpg_ia_data;	//0xC902E568
	UINT32                                                    reserved7;	//0xC902E56C
	PE_E60_PE1_APL_CTRL_00_T                            pe1_apl_ctrl_00;	//0xC902E570
	PE_E60_PE1_APL_CTRL_01_T                            pe1_apl_ctrl_01;	//0xC902E574
	PE_E60_PE1_APL_CTRL_02_T                            pe1_apl_ctrl_02;	//0xC902E578
	PE_E60_PE1_APL_CTRL_03_T                            pe1_apl_ctrl_03;	//0xC902E57C
	PE_E60_PE1_APL_CTRL_04_T                            pe1_apl_ctrl_04;	//0xC902E580
	PE_E60_PE1_APL_CTRL_05_T                            pe1_apl_ctrl_05;	//0xC902E584
	PE_E60_PE1_APL_CTRL_06_T                            pe1_apl_ctrl_06;	//0xC902E588
	PE_E60_PE1_APL_CTRL_07_T                            pe1_apl_ctrl_07;	//0xC902E58C
	PE_E60_PE1_APL_CTRL_08_T                            pe1_apl_ctrl_08;	//0xC902E590
	UINT32                                                    reserved8;	//0xC902E594
	UINT32                                                    reserved9;	//0xC902E598
	UINT32                                                   reserved10;	//0xC902E59C
	UINT32                                                   reserved11;	//0xC902E5A0
	UINT32                                                   reserved12;	//0xC902E5A4
	UINT32                                                   reserved13;	//0xC902E5A8
	UINT32                                                   reserved14;	//0xC902E5AC
	UINT32                                                   reserved15;	//0xC902E5B0
	PE_E60_PE1_APL_STAT_00_T                            pe1_apl_stat_00;	//0xC902E5B4
	PE_E60_PE1_APL_STAT_01_T                            pe1_apl_stat_01;	//0xC902E5B8
	UINT32                                                   reserved16;	//0xC902E5BC
	PE_E60_PE1_BT20_CTRL_00_T                          pe1_bt20_ctrl_00;	//0xC902E5C0
	PE_E60_PE1_BT20_CTRL_01_T                          pe1_bt20_ctrl_01;	//0xC902E5C4
	PE_E60_PE1_BT20_CTRL_02_T                          pe1_bt20_ctrl_02;	//0xC902E5C8
	PE_E60_PE1_BT20_CTRL_03_T                          pe1_bt20_ctrl_03;	//0xC902E5CC
	PE_E60_PE1_BT20_CTRL_04_T                          pe1_bt20_ctrl_04;	//0xC902E5D0
	PE_E60_PE1_BT20_CTRL_05_T                          pe1_bt20_ctrl_05;	//0xC902E5D4
	PE_E60_PE1_BT20_CTRL_06_T                          pe1_bt20_ctrl_06;	//0xC902E5D8
	PE_E60_PE1_BT20_CTRL_07_T                          pe1_bt20_ctrl_07;	//0xC902E5DC
	PE_E60_PE1_BT20_CTRL_08_T                          pe1_bt20_ctrl_08;	//0xC902E5E0
	PE_E60_PE1_BT20_CTRL_09_T                          pe1_bt20_ctrl_09;	//0xC902E5E4
	PE_E60_PE1_BT20_CTRL_10_T                          pe1_bt20_ctrl_10;	//0xC902E5E8
	PE_E60_PE1_BT20_CTRL_11_T                          pe1_bt20_ctrl_11;	//0xC902E5EC
	PE_E60_PE1_BT20_CTRL_12_T                          pe1_bt20_ctrl_12;	//0xC902E5F0
	PE_E60_PE1_BT20_CTRL_13_T                          pe1_bt20_ctrl_13;	//0xC902E5F4
	PE_E60_PE1_BT20_CTRL_14_T                          pe1_bt20_ctrl_14;	//0xC902E5F8
	PE_E60_PE1_BT20_CTRL_15_T                          pe1_bt20_ctrl_15;	//0xC902E5FC
	PE_E60_PE1_BT20_CTRL_16_T                          pe1_bt20_ctrl_16;	//0xC902E600
	PE_E60_PE1_BT20_CTRL_17_T                          pe1_bt20_ctrl_17;	//0xC902E604
	PE_E60_PE1_BT20_CTRL_18_T                          pe1_bt20_ctrl_18;	//0xC902E608
	PE_E60_PE1_BT20_CTRL_19_T                          pe1_bt20_ctrl_19;	//0xC902E60C
	PE_E60_PE1_BT20_CTRL_20_T                          pe1_bt20_ctrl_20;	//0xC902E610
	PE_E60_PE1_BT20_CTRL_21_T                          pe1_bt20_ctrl_21;	//0xC902E614
	PE_E60_PE1_BT20_CTRL_STAT_00_T                pe1_bt20_ctrl_stat_00;	//0xC902E618
	PE_E60_PE1_BT20_CTRL_STAT_01_T                pe1_bt20_ctrl_stat_01;	//0xC902E61C
	PE_E60_PE1_BT20_CTRL_STAT_02_T                pe1_bt20_ctrl_stat_02;	//0xC902E620
	PE_E60_PE1_BT20_CTRL_STAT_03_T                pe1_bt20_ctrl_stat_03;	//0xC902E624
	UINT32                                                   reserved17;	//0xC902E628
	UINT32                                                   reserved18;	//0xC902E62C
	UINT32                                                   reserved19;	//0xC902E630
	UINT32                                                   reserved20;	//0xC902E634
	UINT32                                                   reserved21;	//0xC902E638
	UINT32                                                   reserved22;	//0xC902E63C
	PE_E60_PE1_WIN2_CTRL_00_T                          pe1_win2_ctrl_00;	//0xC902E640
	PE_E60_PE1_WIN2_CTRL_01_T                          pe1_win2_ctrl_01;	//0xC902E644
	PE_E60_PE1_WIN2_CTRL_02_T                          pe1_win2_ctrl_02;	//0xC902E648
	PE_E60_PE1_WIN2_CTRL_03_T                          pe1_win2_ctrl_03;	//0xC902E64C
	PE_E60_PE1_WIN2_CTRL_04_T                          pe1_win2_ctrl_04;	//0xC902E650
	PE_E60_PE1_WIN2_CTRL_05_T                          pe1_win2_ctrl_05;	//0xC902E654
	PE_E60_PE1_WIN2_CTRL_06_T                          pe1_win2_ctrl_06;	//0xC902E658
	PE_E60_PE1_WIN2_CTRL_07_T                          pe1_win2_ctrl_07;	//0xC902E65C
	PE_E60_PE1_WIN2_CTRL_08_T                          pe1_win2_ctrl_08;	//0xC902E660
	PE_E60_PE1_WIN2_CTRL_09_T                          pe1_win2_ctrl_09;	//0xC902E664
	PE_E60_PE1_WIN2_CTRL_10_T                          pe1_win2_ctrl_10;	//0xC902E668
	PE_E60_PE1_WIN2_CTRL_11_T                          pe1_win2_ctrl_11;	//0xC902E66C
	PE_E60_PE1_WIN2_CTRL_12_T                          pe1_win2_ctrl_12;	//0xC902E670
	PE_E60_PE1_WIN2_CTRL_13_T                          pe1_win2_ctrl_13;	//0xC902E674
	PE_E60_PE1_WIN2_CTRL_14_T                          pe1_win2_ctrl_14;	//0xC902E678
	PE_E60_PE1_WIN2_CTRL_15_T                          pe1_win2_ctrl_15;	//0xC902E67C
	PE_E60_PE1_WIN2_CTRL_16_T                          pe1_win2_ctrl_16;	//0xC902E680
	UINT32                                                   reserved23;	//0xC902E684
	UINT32                                                   reserved24;	//0xC902E688
	UINT32                                                   reserved25;	//0xC902E68C
	UINT32                                                   reserved26;	//0xC902E690
	UINT32                                                   reserved27;	//0xC902E694
	UINT32                                                   reserved28;	//0xC902E698
	UINT32                                                   reserved29;	//0xC902E69C
	UINT32                                                   reserved30;	//0xC902E6A0
	UINT32                                                   reserved31;	//0xC902E6A4
	UINT32                                                   reserved32;	//0xC902E6A8
	UINT32                                                   reserved33;	//0xC902E6AC
	UINT32                                                   reserved34;	//0xC902E6B0
	UINT32                                                   reserved35;	//0xC902E6B4
	UINT32                                                   reserved36;	//0xC902E6B8
	UINT32                                                   reserved37;	//0xC902E6BC
	UINT32                                                   reserved38;	//0xC902E6C0
	UINT32                                                   reserved39;	//0xC902E6C4
	UINT32                                                   reserved40;	//0xC902E6C8
	UINT32                                                   reserved41;	//0xC902E6CC
	PE_E60_PE1_CEN_CTRL_00_T                            pe1_cen_ctrl_00;	//0xC902E6D0
	PE_E60_PE1_CEN_CTRL_01_T                            pe1_cen_ctrl_01;	//0xC902E6D4
	PE_E60_PE1_CEN_CTRL_02_T                            pe1_cen_ctrl_02;	//0xC902E6D8
	PE_E60_PE1_CEN_CTRL_03_T                            pe1_cen_ctrl_03;	//0xC902E6DC
	PE_E60_PE1_CEN_CTRL_04_T                            pe1_cen_ctrl_04;	//0xC902E6E0
	PE_E60_PE1_CEN_CTRL_05_T                            pe1_cen_ctrl_05;	//0xC902E6E4
	PE_E60_PE1_CEN_CTRL_06_T                            pe1_cen_ctrl_06;	//0xC902E6E8
	PE_E60_PE1_CEN_CTRL_07_T                            pe1_cen_ctrl_07;	//0xC902E6EC
	UINT32                                                   reserved42;	//0xC902E6F0
	UINT32                                                   reserved43;	//0xC902E6F4
	UINT32                                                   reserved44;	//0xC902E6F8
	UINT32                                                   reserved45;	//0xC902E6FC
	PE_E60_PE1_CEN_IA_CTRL_T                            pe1_cen_ia_ctrl;	//0xC902E700
	PE_E60_PE1_CEN_IA_DATA_T                            pe1_cen_ia_data;	//0xC902E704
	PE_E60_PE1_CEN_DELTA_IA_CTRL_T                pe1_cen_delta_ia_ctrl;	//0xC902E708
	PE_E60_PE1_CEN_DELTA_IA_DATA_T                pe1_cen_delta_ia_data;	//0xC902E70C
	UINT32                                                   reserved46;	//0xC902E710
	UINT32                                                   reserved47;	//0xC902E714
	UINT32                                                   reserved48;	//0xC902E718
	UINT32                                                   reserved49;	//0xC902E71C
	PE_E60_PE1_DCE_CTRL_00_T                            pe1_dce_ctrl_00;	//0xC902E720
	PE_E60_PE1_DCE_CTRL_01_T                            pe1_dce_ctrl_01;	//0xC902E724
	PE_E60_PE1_DCE_CTRL_02_T                            pe1_dce_ctrl_02;	//0xC902E728
	PE_E60_PE1_DCE_CTRL_03_T                            pe1_dce_ctrl_03;	//0xC902E72C
	PE_E60_PE1_DCE_CTRL_04_T                            pe1_dce_ctrl_04;	//0xC902E730
	PE_E60_PE1_DCE_CTRL_05_T                            pe1_dce_ctrl_05;	//0xC902E734
	PE_E60_PE1_DCE_IA_CTRL_T                            pe1_dce_ia_ctrl;	//0xC902E738
	PE_E60_PE1_DCE_IA_DATA_T                            pe1_dce_ia_data;	//0xC902E73C
	PE_E60_PE1_DCE_CTRL_08_T                            pe1_dce_ctrl_08;	//0xC902E740
	PE_E60_PE1_DCE_CTRL_09_T                            pe1_dce_ctrl_09;	//0xC902E744
	PE_E60_PE1_DCE_HIST_IA_CTRL_T                  pe1_dce_hist_ia_ctrl;	//0xC902E748
	PE_E60_PE1_DCE_HIST_IA_DATA1_T                pe1_dce_hist_ia_data1;	//0xC902E74C
	PE_E60_PE1_DCE_HIST_IA_DATA2_T                pe1_dce_hist_ia_data2;	//0xC902E750
	PE_E60_PE1_DCE_CHR_GAIN_T                          pe1_dce_chr_gain;	//0xC902E754
	PE_E60_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0xC902E758
	PE_E60_PE1_DCE_CHR_GAIN2_T                        pe1_dce_chr_gain2;	//0xC902E75C
	UINT32                                                   reserved50;	//0xC902E760
	UINT32                                                   reserved51;	//0xC902E764
	UINT32                                                   reserved52;	//0xC902E768
	UINT32                                                   reserved53;	//0xC902E76C
	PE_E60_PE1_DSE_CTRL_00_T                            pe1_dse_ctrl_00;	//0xC902E770
	PE_E60_PE1_DSE_CTRL_01_T                            pe1_dse_ctrl_01;	//0xC902E774
	PE_E60_PE1_DSE_CTRL_02_T                            pe1_dse_ctrl_02;	//0xC902E778
	PE_E60_PE1_DSE_IA_CTRL_T                            pe1_dse_ia_ctrl;	//0xC902E77C
	PE_E60_PE1_DSE_IA_DATA_T                            pe1_dse_ia_data;	//0xC902E780
	PE_E60_PE1_DSE_CTRL_03_T                            pe1_dse_ctrl_03;	//0xC902E784
	PE_E60_PE1_DSE_CTRL_04_T                            pe1_dse_ctrl_04;	//0xC902E788
	PE_E60_PE_DSE_Y_REGION_PT0_T                    pe_dse_y_region_pt0;	//0xC902E78C
	PE_E60_PE_DSE_Y_REGION_PT1_T                    pe_dse_y_region_pt1;	//0xC902E790
	PE_E60_PE_DSE_Y_REGION_PT2_T                    pe_dse_y_region_pt2;	//0xC902E794
	PE_E60_PE_DSE_Y_REGION_PT3_T                    pe_dse_y_region_pt3;	//0xC902E798
	PE_E60_PE_DSE_Y_REGION_PT4_T                    pe_dse_y_region_pt4;	//0xC902E79C
	PE_E60_PE_DSE_Y_REGION_PT5_T                    pe_dse_y_region_pt5;	//0xC902E7A0
	PE_E60_PE_DSE_Y_REGION_PT6_T                    pe_dse_y_region_pt6;	//0xC902E7A4
	PE_E60_PE_DSE_Y_REGION_PT7_T                    pe_dse_y_region_pt7;	//0xC902E7A8
	PE_E60_PE_DSE_H_REGION_PT0_T                    pe_dse_h_region_pt0;	//0xC902E7AC
	PE_E60_PE_DSE_H_REGION_PT1_T                    pe_dse_h_region_pt1;	//0xC902E7B0
	PE_E60_PE_DSE_H_REGION_PT2_T                    pe_dse_h_region_pt2;	//0xC902E7B4
	PE_E60_PE_DSE_H_REGION_PT3_T                    pe_dse_h_region_pt3;	//0xC902E7B8
	PE_E60_PE_DSE_H_REGION_PT4_T                    pe_dse_h_region_pt4;	//0xC902E7BC
	PE_E60_PE_DSE_H_REGION_PT5_T                    pe_dse_h_region_pt5;	//0xC902E7C0
	PE_E60_PE_DSE_H_REGION_PT6_T                    pe_dse_h_region_pt6;	//0xC902E7C4
	PE_E60_PE_DSE_H_REGION_PT7_T                    pe_dse_h_region_pt7;	//0xC902E7C8
	UINT32                                                   reserved54;	//0xC902E7CC
	UINT32                                                   reserved55;	//0xC902E7D0
	UINT32                                                   reserved56;	//0xC902E7D4
	UINT32                                                   reserved57;	//0xC902E7D8
	UINT32                                                   reserved58;	//0xC902E7DC
	PE_E60_PE1_DRC_CTRL_00_T                            pe1_drc_ctrl_00;	//0xC902E7E0
	PE_E60_PE1_DRC_CTRL_01_T                            pe1_drc_ctrl_01;	//0xC902E7E4
	PE_E60_PE1_DRC_CTRL_02_T                            pe1_drc_ctrl_02;	//0xC902E7E8
	PE_E60_PE1_DRC_CTRL_03_T                            pe1_drc_ctrl_03;	//0xC902E7EC
	PE_E60_PE1_DRC_CTRL_04_T                            pe1_drc_ctrl_04;	//0xC902E7F0
	PE_E60_PE1_DRC_CTRL_05_T                            pe1_drc_ctrl_05;	//0xC902E7F4
	PE_E60_PE1_DRC_CTRL_06_T                            pe1_drc_ctrl_06;	//0xC902E7F8
	UINT32                                                   reserved59;	//0xC902E7FC
	UINT32                                                   reserved60;	//0xC902E800
	UINT32                                                   reserved61;	//0xC902E804
	UINT32                                                   reserved62;	//0xC902E808
	UINT32                                                   reserved63;	//0xC902E80C
	UINT32                                                   reserved64;	//0xC902E810
	UINT32                                                   reserved65;	//0xC902E814
	UINT32                                                   reserved66;	//0xC902E818
	UINT32                                                   reserved67;	//0xC902E81C
	UINT32                                                   reserved68;	//0xC902E820
	UINT32                                                   reserved69;	//0xC902E824
	UINT32                                                   reserved70;	//0xC902E828
	UINT32                                                   reserved71;	//0xC902E82C
	PE_E60_PE1_DRC_CTRL_20_T                            pe1_drc_ctrl_20;	//0xC902E830
	PE_E60_PE1_DRC_CTRL_21_T                            pe1_drc_ctrl_21;	//0xC902E834
	PE_E60_PE1_DRC_CTRL_22_T                            pe1_drc_ctrl_22;	//0xC902E838
	PE_E60_PE1_DRC_CTRL_23_T                            pe1_drc_ctrl_23;	//0xC902E83C
	PE_E60_PE1_DRC_CTRL_24_T                            pe1_drc_ctrl_24;	//0xC902E840
	PE_E60_PE1_DRC_CTRL_25_T                            pe1_drc_ctrl_25;	//0xC902E844
	PE_E60_PE1_DRC_CTRL_26_T                            pe1_drc_ctrl_26;	//0xC902E848
	PE_E60_PE1_DRC_CTRL_27_T                            pe1_drc_ctrl_27;	//0xC902E84C
	PE_E60_PE1_DRC_CTRL_28_T                            pe1_drc_ctrl_28;	//0xC902E850
	PE_E60_PE1_DRC_CTRL_29_T                            pe1_drc_ctrl_29;	//0xC902E854
	PE_E60_PE1_DRC_CTRL_30_T                            pe1_drc_ctrl_30;	//0xC902E858
	UINT32                                                   reserved72;	//0xC902E85C
	UINT32                                                   reserved73;	//0xC902E860
	PE_E60_PE1_DRC_CTRL_33_T                            pe1_drc_ctrl_33;	//0xC902E864
	PE_E60_PE1_DRC_CTRL_34_T                            pe1_drc_ctrl_34;	//0xC902E868
	PE_E60_PE1_DRC_CTRL_35_T                            pe1_drc_ctrl_35;	//0xC902E86C
	UINT32                                                   reserved74;	//0xC902E870
	UINT32                                                   reserved75;	//0xC902E874
	UINT32                                                   reserved76;	//0xC902E878
	UINT32                                                   reserved77;	//0xC902E87C
	PE_E60_PE1_LOGO_L7SC_CTRL_00_T                pe1_logo_l7sc_ctrl_00;	//0xC902E880
	PE_E60_PE1_LOGO_L7SC_CTRL_01_T                pe1_logo_l7sc_ctrl_01;	//0xC902E884
	PE_E60_PE1_LOGO_L7SC_CTRL_02_T                pe1_logo_l7sc_ctrl_02;	//0xC902E888
	PE_E60_PE1_LOGO_L7SC_CTRL_03_T                pe1_logo_l7sc_ctrl_03;	//0xC902E88C
	PE_E60_PE1_LOGO_L7SC_CTRL_04_T                pe1_logo_l7sc_ctrl_04;	//0xC902E890
	PE_E60_PE1_LOGO_L7SC_CTRL_05_T                pe1_logo_l7sc_ctrl_05;	//0xC902E894
	PE_E60_PE1_LOGO_L7SC_CTRL_06_T                pe1_logo_l7sc_ctrl_06;	//0xC902E898
	PE_E60_PE1_LOGO_L7SC_CTRL_07_T                pe1_logo_l7sc_ctrl_07;	//0xC902E89C
	PE_E60_PE1_LOGO_L7SC_CTRL_08_T                pe1_logo_l7sc_ctrl_08;	//0xC902E8A0
	PE_E60_PE1_LOGO_L7SC_CTRL_09_T                pe1_logo_l7sc_ctrl_09;	//0xC902E8A4
	PE_E60_PE1_LOGO_L7SC_CTRL_10_T                pe1_logo_l7sc_ctrl_10;	//0xC902E8A8
	PE_E60_PE1_LOGO_L7SC_CTRL_11_T                pe1_logo_l7sc_ctrl_11;	//0xC902E8AC
	PE_E60_PE1_LOGO_L7SC_CTRL_12_T                pe1_logo_l7sc_ctrl_12;	//0xC902E8B0
	PE_E60_PE1_LOGO_L7SC_CTRL_13_T                pe1_logo_l7sc_ctrl_13;	//0xC902E8B4
	PE_E60_PE1_LOGO_L3SC_CTRL_00_T                pe1_logo_l3sc_ctrl_00;	//0xC902E8B8
	PE_E60_PE1_LOGO_L3SC_CTRL_01_T                pe1_logo_l3sc_ctrl_01;	//0xC902E8BC
	PE_E60_PE1_LOGO_L3SC_CTRL_02_T                pe1_logo_l3sc_ctrl_02;	//0xC902E8C0
	PE_E60_PE1_LOGO_L3SC_CTRL_03_T                pe1_logo_l3sc_ctrl_03;	//0xC902E8C4
	PE_E60_PE1_LOGO_L3SC_CTRL_04_T                pe1_logo_l3sc_ctrl_04;	//0xC902E8C8
	PE_E60_PE1_LOGO_L3SC_CTRL_05_T                pe1_logo_l3sc_ctrl_05;	//0xC902E8CC
	PE_E60_PE1_LOGO_L3SC_CTRL_06_T                pe1_logo_l3sc_ctrl_06;	//0xC902E8D0
	PE_E60_PE1_LOGO_L3SC_CTRL_07_T                pe1_logo_l3sc_ctrl_07;	//0xC902E8D4
	PE_E60_PE1_LOGO_L3SC_CTRL_08_T                pe1_logo_l3sc_ctrl_08;	//0xC902E8D8
	PE_E60_PE1_LOGO_L3SC_CTRL_09_T                pe1_logo_l3sc_ctrl_09;	//0xC902E8DC
	PE_E60_PE1_LOGO_L3SC_CTRL_10_T                pe1_logo_l3sc_ctrl_10;	//0xC902E8E0
	PE_E60_PE1_LOGO_L3SC_CTRL_11_T                pe1_logo_l3sc_ctrl_11;	//0xC902E8E4
	PE_E60_PE1_LOGO_L3SC_CTRL_12_T                pe1_logo_l3sc_ctrl_12;	//0xC902E8E8
	PE_E60_PE1_LOGO_STAT_00_T                          pe1_logo_stat_00;	//0xC902E8EC
	PE_E60_PE1_LOGO_STAT_01_T                          pe1_logo_stat_01;	//0xC902E8F0
	PE_E60_PE1_LOGO_STAT_02_T                          pe1_logo_stat_02;	//0xC902E8F4
	PE_E60_PE1_LOGO_STAT_03_T                          pe1_logo_stat_03;	//0xC902E8F8
	UINT32                                                   reserved78;	//0xC902E8FC
	UINT32                                                   reserved79;	//0xC902E900
	UINT32                                                   reserved80;	//0xC902E904
	UINT32                                                   reserved81;	//0xC902E908
	UINT32                                                   reserved82;	//0xC902E90C
	PE_E60_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xC902E910
	PE_E60_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xC902E914
	PE_E60_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xC902E918
	PE_E60_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xC902E91C
	PE_E60_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xC902E920
	PE_E60_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xC902E924
	PE_E60_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xC902E928
	PE_E60_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xC902E92C
	PE_E60_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xC902E930
	PE_E60_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xC902E934
	PE_E60_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xC902E938
	PE_E60_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xC902E93C
	PE_E60_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xC902E940
	PE_E60_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xC902E944
	UINT32                                                   reserved83;	//0xC902E948
	UINT32                                                   reserved84;	//0xC902E94C
	PE_E60_PE1_LLLUT_E_IA_CTRL_T                    pe1_lllut_e_ia_ctrl;	//0xC902E950
	PE_E60_PE1_LLLUT_E_IA_DATA_T                    pe1_lllut_e_ia_data;	//0xC902E954
	PE_E60_PE1_LLLUT_O_IA_CTRL_T                    pe1_lllut_o_ia_ctrl;	//0xC902E958
	PE_E60_PE1_LLLUT_O_IA_DATA_T                    pe1_lllut_o_ia_data;	//0xC902E95C
	PE_E60_PE1_LLCORE_CTRL_00_T                      pe1_llcore_ctrl_00;	//0xC902E960
	PE_E60_PE1_LLCORE_CTRL_01_T                      pe1_llcore_ctrl_01;	//0xC902E964
	PE_E60_PE1_LLCORE_CTRL_02_T                      pe1_llcore_ctrl_02;	//0xC902E968
	PE_E60_PE1_LLCORE_CTRL_03_T                      pe1_llcore_ctrl_03;	//0xC902E96C
	PE_E60_PE1_LLCORE_CTRL_04_T                      pe1_llcore_ctrl_04;	//0xC902E970
	PE_E60_PE1_LLCORE_CTRL_05_T                      pe1_llcore_ctrl_05;	//0xC902E974
	PE_E60_PE1_LLCORE_CTRL_06_T                      pe1_llcore_ctrl_06;	//0xC902E978
	PE_E60_PE1_LLCORE_CTRL_07_T                      pe1_llcore_ctrl_07;	//0xC902E97C
	PE_E60_PE1_LLCORE_CTRL_08_T                      pe1_llcore_ctrl_08;	//0xC902E980
	PE_E60_PE1_LLCORE_CTRL_09_T                      pe1_llcore_ctrl_09;	//0xC902E984
	PE_E60_PE1_LLCORE_CTRL_10_T                      pe1_llcore_ctrl_10;	//0xC902E988
	PE_E60_PE1_LLCORE_CTRL_11_T                      pe1_llcore_ctrl_11;	//0xC902E98C
	PE_E60_PE1_LLCORE_CTRL_12_T                      pe1_llcore_ctrl_12;	//0xC902E990
	PE_E60_PE1_LLCORE_CTRL_13_T                      pe1_llcore_ctrl_13;	//0xC902E994
}PE_CC_PE1_REG_E60_T;

typedef struct {
	PE_E60_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xC902F000
	PE_E60_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xC902F004
	PE_E60_PE1_VSPYC_CTRL_02_T                       pe1_vspyc_ctrl_02;	//0xC902F008
	PE_E60_PE1_VSPYC_CTRL_03_T                       pe1_vspyc_ctrl_03;	//0xC902F00C
	PE_E60_PE1_VSPYC_CTRL_04_T                       pe1_vspyc_ctrl_04;	//0xC902F010
	PE_E60_PE1_VSPYC_CTRL_05_T                       pe1_vspyc_ctrl_05;	//0xC902F014
	PE_E60_PE1_VSPYC_CTRL_06_T                       pe1_vspyc_ctrl_06;	//0xC902F018
	PE_E60_PE1_VSPYC_CTRL_07_T                       pe1_vspyc_ctrl_07;	//0xC902F01C
	PE_E60_PE1_VSPYC_CTRL_08_T                       pe1_vspyc_ctrl_08;	//0xC902F020
	PE_E60_PE1_VSPYC_CTRL_09_T                       pe1_vspyc_ctrl_09;	//0xC902F024
	UINT32                                                    reserved0;	//0xC902F028
	UINT32                                                    reserved1;	//0xC902F02C
	PE_E60_PE1_VSP_CC_CTRL_00_T                     pe1_vsp_cc_ctrl_00;	//0xC902F030
	UINT32                                                    reserved2;	//0xC902F034
	UINT32                                                    reserved3;	//0xC902F038
	UINT32                                                    reserved4;	//0xC902F03C
	UINT32                                                    reserved5;	//0xC902F040
	PE_E60_PE1_VSP_CC_CTRL_05_T                     pe1_vsp_cc_ctrl_05;	//0xC902F044
	UINT32                                                    reserved6;	//0xC902F048
	UINT32                                                    reserved7;	//0xC902F04C
	PE_E60_PE1_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xC902F050
	PE_E60_PE1_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xC902F054
	PE_E60_PE1_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xC902F058
	PE_E60_PE1_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xC902F05C
	PE_E60_PE1_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xC902F060
	PE_E60_PE1_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xC902F064
	PE_E60_PE1_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xC902F068
	PE_E60_PE1_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xC902F06C
	PE_E60_PE1_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xC902F070
	PE_E60_PE1_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xC902F074
	PE_E60_PE1_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xC902F078
	PE_E60_PE1_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xC902F07C
	PE_E60_PE1_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xC902F080
	PE_E60_PE1_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xC902F084
	PE_E60_PE1_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xC902F088
	PE_E60_PE1_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xC902F08C
	UINT32                                                    reserved8;	//0xC902F090
	UINT32                                                    reserved9;	//0xC902F094
	UINT32                                                   reserved10;	//0xC902F098
	UINT32                                                   reserved11;	//0xC902F09C
	PE_E60_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xC902F0A0
	PE_E60_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xC902F0A4
	PE_E60_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xC902F0A8
	UINT32                                                   reserved12;	//0xC902F0AC
	PE_E60_PE1_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xC902F0B0
	PE_E60_PE1_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xC902F0B4
	PE_E60_PE1_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xC902F0B8
	UINT32                                                   reserved13;	//0xC902F0BC
	PE_E60_PE1_CW_CRGN_CTRL_00_T                   pe1_cw_crgn_ctrl_00;	//0xC902F0C0
	PE_E60_PE1_CW_CRGN_CTRL_01_T                   pe1_cw_crgn_ctrl_01;	//0xC902F0C4
	PE_E60_PE1_CW_CRGN_CTRL_02_T                   pe1_cw_crgn_ctrl_02;	//0xC902F0C8
	PE_E60_PE1_CW_CRGN_CTRL_03_T                   pe1_cw_crgn_ctrl_03;	//0xC902F0CC
	PE_E60_PE1_CW_CRGN_CTRL_04_T                   pe1_cw_crgn_ctrl_04;	//0xC902F0D0
	PE_E60_PE1_CW_CRGN_CTRL_05_T                   pe1_cw_crgn_ctrl_05;	//0xC902F0D4
	PE_E60_PE1_CW_CRGN_CTRL_06_T                   pe1_cw_crgn_ctrl_06;	//0xC902F0D8
	PE_E60_PE1_CW_CRGN_CTRL_07_T                   pe1_cw_crgn_ctrl_07;	//0xC902F0DC
	PE_E60_PE1_CW_CRGN_CTRL_08_T                   pe1_cw_crgn_ctrl_08;	//0xC902F0E0
	PE_E60_PE1_CW_CRGN_CTRL_09_T                   pe1_cw_crgn_ctrl_09;	//0xC902F0E4
	PE_E60_PE1_CW_CRGN_CTRL_10_T                   pe1_cw_crgn_ctrl_10;	//0xC902F0E8
	PE_E60_PE1_CW_CRGN_CTRL_11_T                   pe1_cw_crgn_ctrl_11;	//0xC902F0EC
	PE_E60_PE1_CW_CRGN_CTRL_12_T                   pe1_cw_crgn_ctrl_12;	//0xC902F0F0
	PE_E60_PE1_CW_CRGN_CTRL_13_T                   pe1_cw_crgn_ctrl_13;	//0xC902F0F4
	PE_E60_PE1_CW_CRGN_CTRL_14_T                   pe1_cw_crgn_ctrl_14;	//0xC902F0F8
	PE_E60_PE1_CW_CRGN_CTRL_15_T                   pe1_cw_crgn_ctrl_15;	//0xC902F0FC
	UINT32                                                   reserved14;	//0xC902F100
	UINT32                                                   reserved15;	//0xC902F104
	UINT32                                                   reserved16;	//0xC902F108
	UINT32                                                   reserved17;	//0xC902F10C
	PE_E60_PE1_LBLUR_CTRL_00_T                       pe1_lblur_ctrl_00;	//0xC902F110
	PE_E60_PE1_LBLUR_CTRL_01_T                       pe1_lblur_ctrl_01;	//0xC902F114
	PE_E60_PE1_LBLUR_CTRL_02_T                       pe1_lblur_ctrl_02;	//0xC902F118
	UINT32                                                   reserved18;	//0xC902F11C
	PE_E60_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0xC902F120
	PE_E60_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0xC902F124
	PE_E60_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0xC902F128
	PE_E60_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0xC902F12C
	PE_E60_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0xC902F130
	PE_E60_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0xC902F134
	PE_E60_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0xC902F138
	PE_E60_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0xC902F13C
	PE_E60_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0xC902F140
	PE_E60_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0xC902F144
	PE_E60_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0xC902F148
	PE_E60_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0xC902F14C
	PE_E60_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0xC902F150
	PE_E60_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0xC902F154
	PE_E60_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0xC902F158
	PE_E60_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0xC902F15C
	PE_E60_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0xC902F160
	PE_E60_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0xC902F164
	PE_E60_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0xC902F168
	PE_E60_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0xC902F16C
	PE_E60_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0xC902F170
	PE_E60_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0xC902F174
	PE_E60_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0xC902F178
	PE_E60_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0xC902F17C
	PE_E60_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0xC902F180
	PE_E60_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0xC902F184
	PE_E60_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0xC902F188
	PE_E60_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0xC902F18C
	PE_E60_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0xC902F190
	PE_E60_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0xC902F194
	PE_E60_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0xC902F198
	PE_E60_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0xC902F19C
	PE_E60_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0xC902F1A0
	PE_E60_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0xC902F1A4
	PE_E60_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0xC902F1A8
	PE_E60_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0xC902F1AC
	PE_E60_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0xC902F1B0
	PE_E60_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0xC902F1B4
	PE_E60_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0xC902F1B8
	PE_E60_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0xC902F1BC
	PE_E60_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0xC902F1C0
	PE_E60_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0xC902F1C4
	PE_E60_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0xC902F1C8
	PE_E60_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0xC902F1CC
	PE_E60_PE1_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0xC902F1D0
	PE_E60_PE1_LOGO_CTRL_45_T                         pe1_logo_ctrl_45;	//0xC902F1D4
	PE_E60_PE1_LOGO_CTRL_46_T                         pe1_logo_ctrl_46;	//0xC902F1D8
	PE_E60_PE1_LOGO_CTRL_47_T                         pe1_logo_ctrl_47;	//0xC902F1DC
	PE_E60_PE1_LOGO_CTRL_48_T                         pe1_logo_ctrl_48;	//0xC902F1E0
	PE_E60_PE1_LOGO_CTRL_49_T                         pe1_logo_ctrl_49;	//0xC902F1E4
	PE_E60_PE1_LOGO_CTRL_50_T                         pe1_logo_ctrl_50;	//0xC902F1E8
	PE_E60_PE1_LOGO_CTRL_51_T                         pe1_logo_ctrl_51;	//0xC902F1EC
	PE_E60_PE1_LOGO_CTRL_52_T                         pe1_logo_ctrl_52;	//0xC902F1F0
	PE_E60_PE1_LOGO_CTRL_53_T                         pe1_logo_ctrl_53;	//0xC902F1F4
	PE_E60_PE1_LOGO_CTRL_54_T                         pe1_logo_ctrl_54;	//0xC902F1F8
	PE_E60_PE1_LOGO_CTRL_55_T                         pe1_logo_ctrl_55;	//0xC902F1FC
	PE_E60_PE1_LOGO_CTRL_56_T                         pe1_logo_ctrl_56;	//0xC902F200
	UINT32                                                   reserved19;	//0xC902F204
	UINT32                                                   reserved20;	//0xC902F208
	UINT32                                                   reserved21;	//0xC902F20C
	UINT32                                                   reserved22;	//0xC902F210
	UINT32                                                   reserved23;	//0xC902F214
	UINT32                                                   reserved24;	//0xC902F218
	UINT32                                                   reserved25;	//0xC902F21C
	PE_E60_PE1_GSR_CTRL_00_T                           pe1_gsr_ctrl_00;	//0xC902F220
	PE_E60_PE1_GSR_CTRL_01_T                           pe1_gsr_ctrl_01;	//0xC902F224
	PE_E60_PE1_GSR_CTRL_02_T                           pe1_gsr_ctrl_02;	//0xC902F228
	PE_E60_PE1_GSR_CTRL_03_T                           pe1_gsr_ctrl_03;	//0xC902F22C
	PE_E60_PE1_GSR_CTRL_04_T                           pe1_gsr_ctrl_04;	//0xC902F230
	PE_E60_PE1_GSR_CTRL_05_T                           pe1_gsr_ctrl_05;	//0xC902F234
	PE_E60_PE1_GSR_CTRL_06_T                           pe1_gsr_ctrl_06;	//0xC902F238
	PE_E60_PE1_GSR_CTRL_07_T                           pe1_gsr_ctrl_07;	//0xC902F23C
	PE_E60_PE1_GSR_CTRL_08_T                           pe1_gsr_ctrl_08;	//0xC902F240
	PE_E60_PE1_GSR_CTRL_09_T                           pe1_gsr_ctrl_09;	//0xC902F244
	PE_E60_PE1_GSR_CTRL_10_T                           pe1_gsr_ctrl_10;	//0xC902F248
	PE_E60_PE1_GSR_CTRL_11_T                           pe1_gsr_ctrl_11;	//0xC902F24C
	PE_E60_PE1_GSR_CTRL_12_T                           pe1_gsr_ctrl_12;	//0xC902F250
	PE_E60_PE1_GSR_CTRL_13_T                           pe1_gsr_ctrl_13;	//0xC902F254
	PE_E60_PE1_GSR_CTRL_14_T                           pe1_gsr_ctrl_14;	//0xC902F258
	PE_E60_PE1_GSR_CTRL_15_T                           pe1_gsr_ctrl_15;	//0xC902F25C
	PE_E60_PE1_GSR_CTRL_16_T                           pe1_gsr_ctrl_16;	//0xC902F260
	PE_E60_PE1_GSR_CTRL_17_T                           pe1_gsr_ctrl_17;	//0xC902F264
	PE_E60_PE1_GSR_CTRL_18_T                           pe1_gsr_ctrl_18;	//0xC902F268
	PE_E60_PE1_GSR_CTRL_19_T                           pe1_gsr_ctrl_19;	//0xC902F26C
	PE_E60_PE1_GSR_CTRL_20_T                           pe1_gsr_ctrl_20;	//0xC902F270
	PE_E60_PE1_GSR_CTRL_21_T                           pe1_gsr_ctrl_21;	//0xC902F274
	PE_E60_PE1_GSR_CTRL_22_T                           pe1_gsr_ctrl_22;	//0xC902F278
	PE_E60_PE1_GSR_CTRL_23_T                           pe1_gsr_ctrl_23;	//0xC902F27C
	PE_E60_PE1_GSR_CTRL_24_T                           pe1_gsr_ctrl_24;	//0xC902F280
	PE_E60_PE1_GSR_CTRL_25_T                           pe1_gsr_ctrl_25;	//0xC902F284
	PE_E60_PE1_GSR_CTRL_26_T                           pe1_gsr_ctrl_26;	//0xC902F288
	PE_E60_PE1_GSR_CTRL_27_T                           pe1_gsr_ctrl_27;	//0xC902F28C
	PE_E60_PE1_GSR_CTRL_28_T                           pe1_gsr_ctrl_28;	//0xC902F290
	PE_E60_PE1_GSR_CTRL_29_T                           pe1_gsr_ctrl_29;	//0xC902F294
	PE_E60_PE1_GSR_CTRL_30_T                           pe1_gsr_ctrl_30;	//0xC902F298
	PE_E60_PE1_GSR_CTRL_31_T                           pe1_gsr_ctrl_31;	//0xC902F29C
	PE_E60_PE1_GSR_CTRL_32_T                           pe1_gsr_ctrl_32;	//0xC902F2A0
	PE_E60_PE1_GSR_CTRL_33_T                           pe1_gsr_ctrl_33;	//0xC902F2A4
	PE_E60_PE1_GSR_CTRL_34_T                           pe1_gsr_ctrl_34;	//0xC902F2A8
	PE_E60_PE1_GSR_CTRL_35_T                           pe1_gsr_ctrl_35;	//0xC902F2AC
	PE_E60_PE1_GSR_CTRL_36_T                           pe1_gsr_ctrl_36;	//0xC902F2B0
	PE_E60_PE1_GSR_CTRL_37_T                           pe1_gsr_ctrl_37;	//0xC902F2B4
	UINT32                                                   reserved26;	//0xC902F2B8
	UINT32                                                   reserved27;	//0xC902F2BC
	UINT32                                                   reserved28;	//0xC902F2C0
	UINT32                                                   reserved29;	//0xC902F2C4
	UINT32                                                   reserved30;	//0xC902F2C8
	UINT32                                                   reserved31;	//0xC902F2CC
	UINT32                                                   reserved32;	//0xC902F2D0
	UINT32                                                   reserved33;	//0xC902F2D4
	UINT32                                                   reserved34;	//0xC902F2D8
	UINT32                                                   reserved35;	//0xC902F2DC
	PE_E60_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xC902F2E0
	PE_E60_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xC902F2E4
	PE_E60_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xC902F2E8
	PE_E60_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xC902F2EC
	PE_E60_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xC902F2F0
	PE_E60_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xC902F2F4
	PE_E60_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xC902F2F8
	PE_E60_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xC902F2FC
	PE_E60_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xC902F300
	PE_E60_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xC902F304
	PE_E60_PE1_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xC902F308
	PE_E60_PE1_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xC902F30C
	PE_E60_PE1_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xC902F310
	PE_E60_PE1_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xC902F314
	PE_E60_PE1_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xC902F318
	PE_E60_PE1_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xC902F31C
	PE_E60_PE1_MUTE_CTRL_16_T                         pe1_mute_ctrl_16;	//0xC902F320
	PE_E60_PE1_MUTE_CTRL_17_T                         pe1_mute_ctrl_17;	//0xC902F324
	PE_E60_PE1_MUTE_CTRL_18_T                         pe1_mute_ctrl_18;	//0xC902F328
	PE_E60_PE1_MUTE_CTRL_19_T                         pe1_mute_ctrl_19;	//0xC902F32C
	PE_E60_PE1_MUTE_CTRL_20_T                         pe1_mute_ctrl_20;	//0xC902F330
	PE_E60_PE1_MUTE_CTRL_21_T                         pe1_mute_ctrl_21;	//0xC902F334
	PE_E60_PE1_MUTE_CTRL_22_T                         pe1_mute_ctrl_22;	//0xC902F338
	PE_E60_PE1_MUTE_CTRL_23_T                         pe1_mute_ctrl_23;	//0xC902F33C
	PE_E60_PE1_MUTE_CTRL_24_T                         pe1_mute_ctrl_24;	//0xC902F340
	PE_E60_PE1_MUTE_CTRL_25_T                         pe1_mute_ctrl_25;	//0xC902F344
	PE_E60_PE1_MUTE_CTRL_26_T                         pe1_mute_ctrl_26;	//0xC902F348
	PE_E60_PE1_MUTE_CTRL_27_T                         pe1_mute_ctrl_27;	//0xC902F34C
	PE_E60_PE1_MUTE_CTRL_28_T                         pe1_mute_ctrl_28;	//0xC902F350
	PE_E60_PE1_MUTE_CTRL_29_T                         pe1_mute_ctrl_29;	//0xC902F354
	PE_E60_PE1_MUTE_CTRL_30_T                         pe1_mute_ctrl_30;	//0xC902F358
	PE_E60_PE1_MUTE_CTRL_31_T                         pe1_mute_ctrl_31;	//0xC902F35C
	PE_E60_PE1_MUTE_CTRL_32_T                         pe1_mute_ctrl_32;	//0xC902F360
	PE_E60_PE1_MUTE_CTRL_33_T                         pe1_mute_ctrl_33;	//0xC902F364
	PE_E60_PE1_MUTE_CTRL_34_T                         pe1_mute_ctrl_34;	//0xC902F368
	PE_E60_PE1_MUTE_CTRL_35_T                         pe1_mute_ctrl_35;	//0xC902F36C
	PE_E60_PE1_MUTE_CTRL_36_T                         pe1_mute_ctrl_36;	//0xC902F370
	PE_E60_PE1_MUTE_CTRL_37_T                         pe1_mute_ctrl_37;	//0xC902F374
	PE_E60_PE1_MUTE_CTRL_38_T                         pe1_mute_ctrl_38;	//0xC902F378
	PE_E60_PE1_MUTE_CTRL_39_T                         pe1_mute_ctrl_39;	//0xC902F37C
	UINT32                                                   reserved36;	//0xC902F380
	UINT32                                                   reserved37;	//0xC902F384
	UINT32                                                   reserved38;	//0xC902F388
	UINT32                                                   reserved39;	//0xC902F38C
	UINT32                                                   reserved40;	//0xC902F390
	UINT32                                                   reserved41;	//0xC902F394
	UINT32                                                   reserved42;	//0xC902F398
	UINT32                                                   reserved43;	//0xC902F39C
	UINT32                                                   reserved44;	//0xC902F3A0
	UINT32                                                   reserved45;	//0xC902F3A4
	UINT32                                                   reserved46;	//0xC902F3A8
	UINT32                                                   reserved47;	//0xC902F3AC
	UINT32                                                   reserved48;	//0xC902F3B0
	UINT32                                                   reserved49;	//0xC902F3B4
	UINT32                                                   reserved50;	//0xC902F3B8
	UINT32                                                   reserved51;	//0xC902F3BC
	UINT32                                                   reserved52;	//0xC902F3C0
	UINT32                                                   reserved53;	//0xC902F3C4
	UINT32                                                   reserved54;	//0xC902F3C8
	UINT32                                                   reserved55;	//0xC902F3CC
	UINT32                                                   reserved56;	//0xC902F3D0
	UINT32                                                   reserved57;	//0xC902F3D4
	UINT32                                                   reserved58;	//0xC902F3D8
	UINT32                                                   reserved59;	//0xC902F3DC
	UINT32                                                   reserved60;	//0xC902F3E0
	UINT32                                                   reserved61;	//0xC902F3E4
	UINT32                                                   reserved62;	//0xC902F3E8
	UINT32                                                   reserved63;	//0xC902F3EC
	UINT32                                                   reserved64;	//0xC902F3F0
	UINT32                                                   reserved65;	//0xC902F3F4
	UINT32                                                   reserved66;	//0xC902F3F8
	UINT32                                                   reserved67;	//0xC902F3FC
	UINT32                                                   reserved68;	//0xC902F400
	UINT32                                                   reserved69;	//0xC902F404
	UINT32                                                   reserved70;	//0xC902F408
	UINT32                                                   reserved71;	//0xC902F40C
	PE_E60_PE1_MERGE_CTRL_00_T                       pe1_merge_ctrl_00;	//0xC902F410
	PE_E60_PE1_MERGE_CTRL_01_T                       pe1_merge_ctrl_01;	//0xC902F414
	PE_E60_PE1_MERGE_CTRL_02_T                       pe1_merge_ctrl_02;	//0xC902F418
	PE_E60_PE1_MERGE_CTRL_03_T                       pe1_merge_ctrl_03;	//0xC902F41C
	PE_E60_PE1_MERGE_CTRL_04_T                       pe1_merge_ctrl_04;	//0xC902F420
	PE_E60_PE1_MERGE_CTRL_05_T                       pe1_merge_ctrl_05;	//0xC902F424
	PE_E60_PE1_MERGE_CTRL_06_T                       pe1_merge_ctrl_06;	//0xC902F428
	PE_E60_PE1_MERGE_CTRL_07_T                       pe1_merge_ctrl_07;	//0xC902F42C
	PE_E60_PE1_MERGE_CTRL_08_T                       pe1_merge_ctrl_08;	//0xC902F430
	PE_E60_PE1_MERGE_CTRL_09_T                       pe1_merge_ctrl_09;	//0xC902F434
	PE_E60_PE1_MERGE_CTRL_10_T                       pe1_merge_ctrl_10;	//0xC902F438
	PE_E60_PE1_MERGE_CTRL_11_T                       pe1_merge_ctrl_11;	//0xC902F43C
	PE_E60_PE1_MERGE_CTRL_12_T                       pe1_merge_ctrl_12;	//0xC902F440
	PE_E60_PE1_MERGE_CTRL_13_T                       pe1_merge_ctrl_13;	//0xC902F444
	PE_E60_PE1_MERGE_CTRL_14_T                       pe1_merge_ctrl_14;	//0xC902F448
	PE_E60_PE1_MERGE_CTRL_15_T                       pe1_merge_ctrl_15;	//0xC902F44C
	PE_E60_PE1_MERGE_CTRL_16_T                       pe1_merge_ctrl_16;	//0xC902F450
	PE_E60_PE1_MERGE_CTRL_17_T                       pe1_merge_ctrl_17;	//0xC902F454
	PE_E60_PE1_MERGE_CTRL_18_T                       pe1_merge_ctrl_18;	//0xC902F458
	PE_E60_PE1_MERGE_CTRL_19_T                       pe1_merge_ctrl_19;	//0xC902F45C
	PE_E60_PE1_MERGE_CTRL_20_T                       pe1_merge_ctrl_20;	//0xC902F460
	PE_E60_PE1_MERGE_CTRL_21_T                       pe1_merge_ctrl_21;	//0xC902F464
	PE_E60_PE1_MERGE_CTRL_22_T                       pe1_merge_ctrl_22;	//0xC902F468
	PE_E60_PE1_MERGE_CTRL_23_T                       pe1_merge_ctrl_23;	//0xC902F46C
	PE_E60_PE1_MERGE_CTRL_24_T                       pe1_merge_ctrl_24;	//0xC902F470
	PE_E60_PE1_MERGE_CTRL_25_T                       pe1_merge_ctrl_25;	//0xC902F474
	PE_E60_PE1_MERGE_CTRL_26_T                       pe1_merge_ctrl_26;	//0xC902F478
	PE_E60_PE1_MERGE_CTRL_27_T                       pe1_merge_ctrl_27;	//0xC902F47C
	PE_E60_PE1_MERGE_CTRL_28_T                       pe1_merge_ctrl_28;	//0xC902F480
	PE_E60_PE1_MERGE_CTRL_29_T                       pe1_merge_ctrl_29;	//0xC902F484
}PE_CC2_PE1_REG_E60_T;


typedef struct {
	PE_E60_CCO1_SYS_VERI_0_T                               sys_veri_0;	//0xC9030300
	PE_E60_CCO1_SYS_VERI_1_T                               sys_veri_1;	//0xC9030304
	PE_E60_CCO1_SYS_VERI_2_T                               sys_veri_2;	//0xC9030308
	PE_E60_CCO1_SYS_VERI_3_T                               sys_veri_3;	//0xC903030C
	PE_E60_CCO1_SYS_VERI_4_T                               sys_veri_4;	//0xC9030310
	PE_E60_CCO1_SYS_VERI_5_T                               sys_veri_5;	//0xC9030314
	PE_E60_CCO1_SYS_VERI_6_T                               sys_veri_6;	//0xC9030318
	PE_E60_CCO1_SYS_VERI_7_T                               sys_veri_7;	//0xC903031C
	PE_E60_CCO1_SYS_VERI_8_T                               sys_veri_8;	//0xC9030320
	PE_E60_CCO1_SYS_VERI_9_T                               sys_veri_9;	//0xC9030324
	PE_E60_CCO1_SYS_VERI_10_T                             sys_veri_10;	//0xC9030328
	PE_E60_CCO1_SYS_VERI_11_T                             sys_veri_11;	//0xC903032C
	PE_E60_CCO1_SYS_VERI_12_T                             sys_veri_12;	//0xC9030330
	PE_E60_CCO1_SYS_VERI_13_T                             sys_veri_13;	//0xC9030334
	PE_E60_CCO1_SYS_VERI_14_T                             sys_veri_14;	//0xC9030338
	PE_E60_CCO1_SYS_VERI_15_T                             sys_veri_15;	//0xC903033C
	PE_E60_CCO1_SYS_VERI_16_T                             sys_veri_16;	//0xC9030340
	PE_E60_CCO1_SYS_VERI_17_T                             sys_veri_17;	//0xC9030344
	PE_E60_CCO1_SYS_VERI_18_T                             sys_veri_18;	//0xC9030348
	PE_E60_CCO1_SYS_VERI_19_T                             sys_veri_19;	//0xC903034C
	PE_E60_CCO1_SYS_VERI_20_T                             sys_veri_20;	//0xC9030350
	PE_E60_CCO1_SYS_VERI_21_T                             sys_veri_21;	//0xC9030354
	PE_E60_CCO1_SYS_VERI_22_T                             sys_veri_22;	//0xC9030358
	PE_E60_CCO1_SYS_VERI_23_T                             sys_veri_23;	//0xC903035C
	PE_E60_CCO1_SYS_VERI_24_T                             sys_veri_24;	//0xC9030360
	PE_E60_CCO1_SYS_VERI_25_T                             sys_veri_25;	//0xC9030364
	PE_E60_CCO1_SYS_VERI_26_T                             sys_veri_26;	//0xC9030368
	PE_E60_CCO1_SYS_VERI_27_T                             sys_veri_27;	//0xC903036C
	PE_E60_CCO1_SYS_VERI_28_T                             sys_veri_28;	//0xC9030370
	PE_E60_CCO1_SYS_VERI_29_T                             sys_veri_29;	//0xC9030374
	PE_E60_CCO1_SYS_VERI_30_T                             sys_veri_30;	//0xC9030378
	PE_E60_CCO1_SYS_VERI_31_T                             sys_veri_31;	//0xC903037C
	PE_E60_CCO1_SYS_VERI_32_T                             sys_veri_32;	//0xC9030380
	PE_E60_CCO1_SYS_VERI_33_T                             sys_veri_33;	//0xC9030384
	PE_E60_CCO1_SYS_VERI_34_T                             sys_veri_34;	//0xC9030388
	PE_E60_CCO1_SYS_VERI_35_T                             sys_veri_35;	//0xC903038C
}PE_CCO1_VERI_REG_E60_T;


#endif
