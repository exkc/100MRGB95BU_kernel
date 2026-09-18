#ifndef _PE_CCO_REG_M23A0_H_
#define _PE_CCO_REG_M23A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1000 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0' : load at vdpulse	'1' : load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0' : auto load:  load when reg. write	'1' : manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_M23_CC_PE1_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1004 RW 0x10E0_0780
	UINT32 width                            :13;	//(12:0,NA,0x780) //width
	UINT32 resvd0                           :3;
	UINT32 height                           :13;	//(28:16,NA,0x10E0) //height
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1008 RW 0x0100_0A01
	UINT32 tpg_position                     :1;	//(0,NA,0x1) //0 := pe1 input	1  =  pe1 output
	UINT32 reg_pe1_cg_disable               :1;	//(1,NA,0x0) //clock gating disable
	UINT32 pe1_detour                       :1;	//(2,NA,0x0) //0': pe1 pass-through	'1': pe1 detour
	UINT32 resvd0                           :5;
	UINT32 vdpulse_pos                      :12;	//(19:8,NA,0xA) //vdpulse position for register loading
	UINT32 resvd1                           :4;
	UINT32 master_en                        :1;	//(24,NA,0x1) //PE1 master enable
	UINT32 resvd2                           :7;
	};
}PE_M23_CC_PE1_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B100C RO 0x0000_0000
	UINT32 vcnt                             :13;	//(12:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(13,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(14,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :1;
	UINT32 vcnt2                            :13;	//(28:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1010 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_M23_CC_PE1_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1020 RW 0x0000_0000
	UINT32 reg_s_status_0                   :8;	//7:0	//S status at L(3D)/main(2D) for TPD
	UINT32 reg_s_status_1                   :8;	//15:8	//S status at R(3D)/sub(2D) for TPD
	UINT32 reg_s_apl_0                      :8;	//23:16	//S APL at at L(3D)/main(2D) for TPD
	UINT32 reg_fmd_en_0                     :1;	//24	//filmmode enable L
	UINT32 reg_fmd_en_1                     :1;	//25	//filmmode enable R
	UINT32 reg_tnr_auto_en                  :1;	//26	//tnr auto enable
	UINT32 cl_filter_en_stat                :1;	//27	//CL filter enable status
	UINT32 clc_detection_en_stat            :1;	//28	//CL/CC detection enable status
	UINT32 reg_color_filter_status          :2;	//30:29	//"Color Filter status'0 : UI Color filter off(normal video) 1: R channel Only(Color filter on) 2: G channel Only(Color filter on) 3: B channel Only(Color filter on)
	UINT32 reg_shp_fw_en                    :1;	//31	//fw sharpness algorithm enable
	};
}PE_M23_CC_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1024 RW 0x0000_0000
	UINT32 reg_histo_fw_en                  :1;	//0		//store mode for HDR DRC
	UINT32 reg_drc_dc_mode                  :2;	//2:1	//DC bypass flag for HDR DRC
	UINT32 reg_drc_dc_bypass                :1;	//3		//DC scene change flag for HDR DRC
	UINT32 reg_drc_dc_sc_cnt                :4;	//7:4	//fw sharpness algorithm enable
	UINT32 pre_121_blur_en                  :1;	//8		//fw histo info enable
	UINT32 pre_median_en                    :1;	//9		//store mode for HDR DRC
	UINT32 tnr_sc_measure_en                :1;	//10	//DC bypass flag for HDR DRC
	UINT32 reg_is_oled                      :1;	//11	//DC scene change flag for HDR DRC
	UINT32 motion_reg                       :2;	//13:12
	UINT32 reg_hdr_effect 					:2; //15:14	// picture mode for drc lut
	UINT32 tnr_sc_measure_th                :16;//31:16	//fw sharpness algorithm enable
	};
}PE_M23_CC_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1028 RW 0x0000_0000
	UINT32 reg_src_info                     :5;	//4:0	//Video Source Information	 2 : default/transition period	 3 : AV NTSC	 4 : AV PAL	 5 : HDMI_SD_i/p	 6 : HDMI_576_i/p	 7 : HDMI_HD_i	 8 : HDMI_HD_p	 9 : DTV_480_i	10 : DTV_576_i	11 : DTV_576_p	12 : DTV_HD_i	13 : DTV_HD_p	14 : RF_NTSC	15 : RF_PAL	16 : RF_PAL_M	17 : COMPONENT_1080_i	18 : COMPONENT_1080_p	19 : COMPONENT_480_i	20 : COMPONENT_480_p	21 : COMPONENT_576_i	22 : COMPONENT_576_p	23 : AV_SECAM	24 : RF_SECAM	25 : AV_ NTSC_443	26 : RF_NTSC_443	27 : AV_PAL_60	28 : SCART_RGB	29 : N.A.(abnormal) input	30 : NO SIG.
	UINT32 reg_src_freeze                   :1;	//5 //src freeze toggle '0' : normal '1' : freeze
	UINT32 reg_gsr_cpc_enable               :1;	//6 //gsr cpc enable
	UINT32 resvd                            :25;
	};
}PE_M23_CC_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B102C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_CC_PE1_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1030 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_CC_PE1_FSW_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1034 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_CC_PE1_FSW_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1038 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_CC_PE1_FSW_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B103C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_M23_CC_PE1_FSW_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1050 RW 0x03C0_0000
	UINT32 tpg_enable                       :1;	//(0,NA,0x0) //TPG Enable
	UINT32 pattern_type                     :2;	//(2:1,NA,0x0) //Test Pattern Type	'00 := ColorPatch	'01 = Gradation
	UINT32 resvd0                           :1;
	UINT32 blend_alpha                      :4;	//(7:4,NA,0x0) //TPG Blend Alpha	0x0 ~ 0xF = SolidPattern ~ BypassBackgroundPicture
	UINT32 resvd1                           :8;
	UINT32 blt_size_x                       :13;	//(28:16,NA,0x3C0) //Pattern Blt Size X (1920d=>0x780)
	UINT32 resvd2                           :3;
	};
}PE_M23_CC_PE1_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1054 RW 0x10E0_0FA0
	UINT32 gradation_stride                 :7;	//(6:0,NA,0x20) //Gradation Stride
	UINT32 gradation_direction              :1;	//(7,NA,0x1) //Gradation Direction	'0 = Vertical Gradation	'1 := Horizontal Gradation
	UINT32 gradation_bar_0_en               :1;	//(8,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_1_en               :1;	//(9,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_2_en               :1;	//(10,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_3_en               :1;	//(11,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 resvd0                           :4;
	UINT32 blt_size_y                       :13;	//(28:16,NA,0x10E0) //Pattern Blt Size Y (1080d=>0x438)
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1058 RW 0x0000_FFFF
	UINT32 patch_0_en                       :1;	//(0,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_1_en                       :1;	//(1,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_2_en                       :1;	//(2,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_3_en                       :1;	//(3,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_4_en                       :1;	//(4,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_5_en                       :1;	//(5,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_6_en                       :1;	//(6,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_7_en                       :1;	//(7,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_8_en                       :1;	//(8,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_9_en                       :1;	//(9,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_10_en                      :1;	//(10,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_11_en                      :1;	//(11,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_12_en                      :1;	//(12,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_13_en                      :1;	//(13,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_14_en                      :1;	//(14,NA,0x1) //Enable Ctrl for each Patch
	UINT32 patch_15_en                      :1;	//(15,NA,0x1) //Enable Ctrl for each Patch
	UINT32 resvd                            :16;
	};
}PE_M23_CC_PE1_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B105C RW 0x0000_0000
	UINT32 patch_0_inout_sel                :1;	//(0,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_1_inout_sel                :1;	//(1,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_2_inout_sel                :1;	//(2,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_3_inout_sel                :1;	//(3,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_4_inout_sel                :1;	//(4,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_5_inout_sel                :1;	//(5,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_6_inout_sel                :1;	//(6,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_7_inout_sel                :1;	//(7,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_8_inout_sel                :1;	//(8,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_9_inout_sel                :1;	//(9,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_10_inout_sel               :1;	//(10,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_11_inout_sel               :1;	//(11,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_12_inout_sel               :1;	//(12,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_13_inout_sel               :1;	//(13,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_14_inout_sel               :1;	//(14,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 patch_15_inout_sel               :1;	//(15,NA,0x0) //select inside/outside coloring for each Patch
	UINT32 resvd                            :16;
	};
}PE_M23_CC_PE1_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1060 RW 0x0000_0000
	UINT32 bg_color_r                       :10;	//(9:0,NA,0x0) //outside color with RGB
	UINT32 bg_color_b                       :10;	//(19:10,NA,0x0) //
	UINT32 bg_color_g                       :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1064 WO 0x0000_0000
	UINT32 tpg_indir_addr                   :7;	//(6:0,NA,0x00) //TPG Indirect Address	0x00 ~ 0x0F = Patch Color	0x20 ~ 0x2F = Patch Start Position	0x40 ~ 0x4F = Patch End Position	0x60 ~ 0x63 = Gradation Start Color	0x64 ~ 0x67 = Gradation Step Color (signed)	0x68 ~ 0x6A = Gradation Region Size
	UINT32 resvd0                           :5;
	UINT32 tpg_indir_ai_en                  :1;	//(12,NA,0x0) //TPG Indirect Addressing Ctrl, AI Enable
	UINT32 resvd1                           :19;
	};
}PE_M23_CC_PE1_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1068 WO 0x0000_0000
	UINT32 tpg_indir_data                   :32;	//(31:0,NA,0x0) //TPG Indirect Access Data (Write Enable Triggered)	 When Addr is...	 0x00 ~ 0x0F = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x20 ~ 0x4F = (28:16):X_position, (12:0):Y_position	 0x60 ~ 0x67 = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x68 ~ 0x6A = (12:0):position
	};
}PE_M23_CC_PE1_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1070 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_0                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0 for ch0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_0                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0 for ch0
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1074 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_0                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_0                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_APL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1078 RW 0x0000_0000
	UINT32 apl_position                     :2;	//(1:0,NA,0x0) //00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :2;
	UINT32 reg_apl_enable                   :1;	//(4,NA,0x1) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :3;
	UINT32 act_win_mode                     :1;	//(8,NA,0x0) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd2                           :23;
	};
}PE_M23_CC_PE1_APL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10B4 RO 0x0000_0000
	UINT32 apl_cb                           :10;	//(9:0,NA,0x0) //APL Cb/B
	UINT32 apl_yg                           :10;	//(19:10,NA,0x0) //APL Y/G
	UINT32 apl_cr                           :10;	//(29:20,NA,0x0) //APL Cr/R
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10B8 RO 0x0000_0000
	UINT32 apl_cb_other_side                :10;	//(9:0,NA,0x0) //apl_cb(outside of apl_win)
	UINT32 apl_yg_other_side                :10;	//(19:10,NA,0x0) //apl_yg(outside of apl_win)
	UINT32 apl_cr_other_side                :10;	//(29:20,NA,0x0) //apl_cr(outside of apl_win)
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_APL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10DC RW 0x0000_0100
	UINT32 resvd0                           :8;
	UINT32 r_1x3_en                         :1;	//(8,NA,0x1) //
	UINT32 resvd1                           :23;
	};
}PE_M23_CC_PE1_BT20_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10E0 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0,NA,0x0) //enable dither
	UINT32 decontour_en                     :1;	//(1,NA,0x0) //enable decontour
	UINT32 dither_random_freeze_en          :1;	//(2,NA,0x0) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3,NA,0x0) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,NA,0x0) //"01" : 8 bit mode	others : bypass
	UINT32 resvd                            :2;
	UINT32 decontour_gain_r                 :8;	//(15:8,NA,0x00) //decontour gain for red
	UINT32 decontour_gain_g                 :8;	//(23:16,NA,0x00) //decontour gain for blue
	UINT32 decontour_gain_b                 :8;	//(31:24,NA,0x00) //decontour gain for green
	};
}PE_M23_CC_PE1_BT20_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10F4 RW 0x12A0_7C98
	UINT32 r_1x3_coef1                      :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef0                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_BT20_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10F8 RW 0x7775_12A0
	UINT32 r_1x3_coef3                      :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef2                      :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_BT20_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B10FC RW 0x21D7_0000
	UINT32 r_1x3_coef5                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef4                      :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_BT20_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1100 RW 0x12A0_0000
	UINT32 r_1x3_coef7                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef6                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_BT20_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1104 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_1x3_coef8                      :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_BT20_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1108 RW 0x07C0_0600
	UINT32 r_1x3_ofst1                      :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst0                      :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_M23_CC_PE1_BT20_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B110C RW 0x0600_0000
	UINT32 r_1x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst2                      :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_M23_CC_PE1_BT20_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1110 RW 0x0000_0000
	UINT32 r_1x3_ofst5                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_M23_CC_PE1_BT20_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1114 RW 0x0000_0000
	UINT32 r_1x3_dbg_en                     :1;	//(0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 r_1x3_dbg_ugy                    :4;	//(7:4,NA,0x00) //underflowed bit gy upper 4 bit
	UINT32 r_1x3_dbg_ucb                    :4;	//(11:8,NA,0x00) //underflowed bit cb upper 4 bit
	UINT32 r_1x3_dbg_ucr                    :4;	//(15:12,NA,0x00) //underflowed bit cr upper 4 bit
	UINT32 r_1x3_dbg_ogy                    :4;	//(19:16,NA,0x00) //overflowed bit gy upper 4 bit
	UINT32 r_1x3_dbg_ocb                    :4;	//(23:20,NA,0x00) //overflowed bit cb upper 4 bit
	UINT32 r_1x3_dbg_obr                    :4;	//(27:24,NA,0x00) //overflowed bit cr upper 4 bit
	UINT32 resvd1                           :4;
	};
}PE_M23_CC_PE1_BT20_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1118 RO 0x0000_0000
	UINT32 r_1x3_over_count_0               :16;	//(15:0,NA,0x0) //overflow count status for ch 0
	UINT32 r_1x3_under_count_0              :16;	//(31:16,NA,0x0) //underflow count status for ch 0
	};
}PE_M23_CC_PE1_BT20_CTRL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B111C RO 0x0000_0000
	UINT32 r_1x3_over_count_1               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_1              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_M23_CC_PE1_BT20_CTRL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1120 RO 0x0000_0000
	UINT32 r_1x3_over_count_2               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_2              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_M23_CC_PE1_BT20_CTRL_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1124 RO 0x0000_0000
	UINT32 r_1x3_over_count_3               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_3              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_M23_CC_PE1_BT20_CTRL_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1140 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0,NA,0x0) //1 =  select only window0 as active area
	UINT32 win1_en                          :1;	//(1,NA,0x0) //1 =  select only window1 as active area
	UINT32 win01_en                         :1;	//(2,NA,0x0) //1 =  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//(6,NA,0x0) //0 := use inside of selected area by win0 and win1	1 =  use the otherside of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7,NA,0x0) //0 := active area = full screen	1 = active area = specifed by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_M23_CC_PE1_WIN2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1144 RW 0x0000_0000
	UINT32 win_w0_x0_0                      :13;	//(12:0,NA,0x000) //win_w0_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_0                      :13;	//(28:16,NA,0x000) //win_w0_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_WIN2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1148 RW 0x0437_03BF
	UINT32 win_w0_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w0_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_0                      :13;	//(28:16,NA,0x437) //win_w0_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_WIN2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B114C RW 0x0000_0000
	UINT32 win_w1_x0_0                      :13;	//(12:0,NA,0x000) //win_w1_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_0                      :13;	//(28:16,NA,0x000) //win_w1_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_WIN2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1150 RW 0x0437_03BF
	UINT32 win_w1_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w1_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_0                      :13;	//(28:16,NA,0x437) //win_w1_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_M23_CC_PE1_WIN2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11D0 RW 0x0000_002C
	UINT32 cen_detour                       :1;	//(0,NA,0x0) //cen_detour	'0' : normal path	'1' : CEN detour
	UINT32 dse_mode                         :1;	//(1,NA,0x0) //0:parallel, 1:serial(DSE->CEN)
	UINT32 select_hsv                       :1;	//(2,NA,0x1) //reg_select_hsv 	HSV total gain의 적용 여부	'1' : HSV total gain을 원본 HSV와 합산하여 적용	'0' : 원본 HSV를 그대로 사용
	UINT32 select_rgb                       :1;	//(3,NA,0x1) //reg_select_RGB 	RGB total gain의 적용 여부	'1' : RGB total gain을 원본 RGB와 합산하여 적용	'0' : 원본 RGB을 그대로 사용
	UINT32 resvd0                           :1;
	UINT32 vsp_sel                          :1;	//(5,NA,0x1) //reg_vsp_sel	'0' : HSL region	'1' : HSV region
	UINT32 resvd1                           :1;
	UINT32 reg_cen_bypass                   :1;	//(7,NA,0x0) //reg_cen_bypass : Color Enhance block의 on/off 	'0' : CEN 적용 하지 않음 입력 RGB가 출력 RGB로 bypass	'1' : CEN 적용 됨
	UINT32 reg_cen_debug_mode               :1;	//(8,NA,0x0) //reg_cen_debug_mode	'0' : CR을 각각의 색으로 채색	'1' : Debugging Color의 PIXEL_GAIN 값을 Gray level로 표현
	UINT32 resvd2                           :1;
	UINT32 core_1st__gain_disable           :1;	//(10,NA,0x0) //1st Region core gain disable	1st Region core의 gain을 disable	'0' : Gain 적용	'1' : Gain 미적용
	UINT32 core_2nd_gain_disable            :1;	//(11,NA,0x0) //2nd core gain disable	2nd core의 gain을 disable	'0' : Gain 적용	'1' : Gain 미적용
	UINT32 resvd3                           :1;
	UINT32 debugging_mode_core              :2;	//(14:13,NA,0x0) //Debugging modeCore	Debugging mode의 적용 Core	'01' : 1st Core의 Debugging mode가 적용	'10' : 2nd Core의 Debugging mode가 적용	others : 1st core의 Debugging mode가 적용(show_color_region0, show_color_region1 으로 선택된 영역에 한해서)
	UINT32 resvd4                           :1;
	UINT32 demo_mode                        :8;	//(23:16,NA,0x0) //Demo Mode	'0111 1000' => 0x78	Algorithm 적용 영상과 원본영상의 경계 위치를 control	전체 화면 크기 / 16 : (ex) 1920 => 0x780 => reg_cen_ctrl0(23:16) = 0x78	화면의 좌측은 원본화면, 우측은 적용화면이며 커질 수록 원본 화면의 영역이 넓어짐
	UINT32 resvd5                           :7;
	UINT32 win_control_mode                 :1;	//(31,NA,0x0) //'0' : window control enabled	 '1' : win mode is always disabled
	};
}PE_M23_CC_PE1_CEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11D4 RW 0xFFFF_0000
	UINT32 show_color_region0               :1;	//(0,NA,0x00) //Region 0을 Region_debug_color0 로 채색
	UINT32 show_color_region1               :1;	//(1,NA,0x00) //Region 1을 Region_debug_color1 로 채색
	UINT32 show_color_region2               :1;	//(2,NA,0x00) //Region 2을 Region_debug_color2 로 채색
	UINT32 show_color_region3               :1;	//(3,NA,0x00) //Region 3을 Region_debug_color3 로 채색
	UINT32 show_color_region4               :1;	//(4,NA,0x00) //Region 4을 Region_debug_color4 로 채색
	UINT32 show_color_region5               :1;	//(5,NA,0x00) //Region 5을 Region_debug_color5 로 채색
	UINT32 show_color_region6               :1;	//(6,NA,0x00) //Region 6을 Region_debug_color6 로 채색
	UINT32 show_color_region7               :1;	//(7,NA,0x00) //Region 7을 Region_debug_color7 로 채색
	UINT32 show_color_region8               :1;	//(8,NA,0x00) //Region 8을 Region_debug_color8 로 채색
	UINT32 show_color_region9               :1;	//(9,NA,0x00) //Region 9을 Region_debug_color9 로 채색
	UINT32 show_color_region10              :1;	//(10,NA,0x00) //Region 10을 Region_debug_color10 로 채색
	UINT32 show_color_region11              :1;	//(11,NA,0x00) //Region 11을 Region_debug_color11 로 채색
	UINT32 show_color_region12              :1;	//(12,NA,0x00) //Region 12을 Region_debug_color12 로 채색
	UINT32 show_color_region13              :1;	//(13,NA,0x00) //Region 13을 Region_debug_color13 로 채색
	UINT32 show_color_region14              :1;	//(14,NA,0x00) //Region 14을 Region_debug_color14 로 채색
	UINT32 show_color_region15              :1;	//(15,NA,0x00) //Region 15을 Region_debug_color15 로 채색
	UINT32 color_region_en0                 :1;	//(16,NA,0x1) //Region 0 enable
	UINT32 color_region_en1                 :1;	//(17,NA,0x1) //Region 1 enable
	UINT32 color_region_en2                 :1;	//(18,NA,0x1) //Region 2 enable
	UINT32 color_region_en3                 :1;	//(19,NA,0x1) //Region 3 enable
	UINT32 color_region_en4                 :1;	//(20,NA,0x1) //Region 4 enable
	UINT32 color_region_en5                 :1;	//(21,NA,0x1) //Region 5 enable
	UINT32 color_region_en6                 :1;	//(22,NA,0x1) //Region 6 enable
	UINT32 color_region_en7                 :1;	//(23,NA,0x1) //Region 7 enable
	UINT32 color_region_en8                 :1;	//(24,NA,0x1) //Region 8 enable
	UINT32 color_region_en9                 :1;	//(25,NA,0x1) //Region 9 enable
	UINT32 color_region_en10                :1;	//(26,NA,0x1) //Region 10 enable
	UINT32 color_region_en11                :1;	//(27,NA,0x1) //Region 11 enable
	UINT32 color_region_en12                :1;	//(28,NA,0x1) //Region 12 enable
	UINT32 color_region_en13                :1;	//(29,NA,0x1) //Region 13 enable
	UINT32 color_region_en14                :1;	//(30,NA,0x1) //Region 14 enable
	UINT32 color_region_en15                :1;	//(31,NA,0x1) //Region 15 enable
	};
}PE_M23_CC_PE1_CEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11D8 RW 0x0000_8080
	UINT32 ihsv_sgain                       :8;	//(7:0,NA,0x80) //reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//(15:8,NA,0x80) //reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
}PE_M23_CC_PE1_CEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11DC RW 0x0080_8080
	UINT32 ihsv_hoffset                     :8;	//(7:0,NA,0x80) //reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//(15:8,NA,0x80) //reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//(23:16,NA,0x80) //reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
}PE_M23_CC_PE1_CEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11E0 RW 0x8080_8080
	UINT32 reg_master_gain_cr0              :8;	//(7:0,NA,0x80) //Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//(15:8,NA,0x80) //Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//(23:16,NA,0x80) //Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//(31:24,NA,0x80) //Color region 3 master gain
	};
}PE_M23_CC_PE1_CEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11E4 RW 0x8080_8080
	UINT32 reg_master_gain_cr4              :8;	//(7:0,NA,0x80) //Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//(15:8,NA,0x80) //Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//(23:16,NA,0x80) //Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//(31:24,NA,0x80) //Color region 7 master gain
	};
}PE_M23_CC_PE1_CEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11E8 RW 0x8080_8080
	UINT32 reg_master_gain_cr8              :8;	//(7:0,NA,0x80) //Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//(15:8,NA,0x80) //Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//(23:16,NA,0x80) //Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//(31:24,NA,0x80) //Color region 11 master gain
	};
}PE_M23_CC_PE1_CEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11EC RW 0x8080_8080
	UINT32 reg_master_gain_cr12             :8;	//(7:0,NA,0x80) //Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//(15:8,NA,0x80) //Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//(23:16,NA,0x80) //Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//(31:24,NA,0x80) //Color region 15 master gain
	};
}PE_M23_CC_PE1_CEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B11F8 RW/RO 0x0000_0000
	UINT32 cen_lut_update                   :1;	//(0,NA,0x0) //cen lut update en
	UINT32 resvd0                           :3;
	UINT32 cen_lut_direct                   :1;	//(4,NA,0x0) //cen lut direct access
	UINT32 resvd1                           :3;
	UINT32 cen_lut_trig_sel                 :1;	//(8,NA,0x0) //0:vs_rs 1:vs_fl
	UINT32 resvd2                           :1;
	UINT32 cen_lut_wstart                   :1;	//(10,NA,0x0) //write start flag for lut cpy protection
	UINT32 cen_lut_wend                     :1;	//(11,NA,0x0) //write end flag for lut cpy protection
	UINT32 cen_lut_status                   :2;	//(13:12,NA,0x0) //
	UINT32 cen_lut_conflict                 :1;	//(14,NA,0x0) //
	UINT32 resvd3                           :17;
	};
}PE_M23_CC_PE1_CEN_UPD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1200 WO 0x0000_0000
	UINT32 hif_cen_address                  :8;	//(7:0,NA,0x00) //hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//(10:8,NA,0x0) //reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//(14,NA,0x0) //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//(15,NA,0x0) //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
}PE_M23_CC_PE1_CEN_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1204 RO 0x0000_0000
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_CEN_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1208 WO 0x0000_0000
	UINT32 hif_cen_delta_address            :5;	//(4:0,NA,0x00) //hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//(15,NA,0x0) //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
}PE_M23_CC_PE1_CEN_DELTA_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B120C RO 0x0000_0000
	UINT32 hif_cen_vr_data                  :8;	//(7:0,NA,0x000) //Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//(15:8,NA,0x000) //Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//(23:16,NA,0x000) //Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
}PE_M23_CC_PE1_CEN_DELTA_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1220 RW 0x0000_0000
	UINT32 dynamic_contrast_en              :1;	//(0,NA,0x0) //0' : disable	'1' : enable
	UINT32 hist_bin_mode                    :2;	//(2:1,NA,0x0) //00' : 32 bin mode	others : 16 bin mode
	UINT32 hist_clear                       :1;	//(3,NA,0x0) //Debugging purpose, force deleting for histogram memory.	'1' : clear
	UINT32 window01_enable                  :1;	//(4,NA,0x0) //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,NA,0x0) //1' : window0 area only
	UINT32 window1_enable                   :1;	//(6,NA,0x0) //1' : window1 area only
	UINT32 window_acquire                   :1;	//(7,NA,0x0) //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//(8,NA,0x0) //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//(9,NA,0x0) //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//(10,NA,0x0) //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//(11,NA,0x0) //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//(12,NA,0x0) //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//(13,NA,0x0) //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//(14,NA,0x0) //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//(15,NA,0x0) //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//(16,NA,0x0) //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//(17,NA,0x0) //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//(18,NA,0x0) //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//(19,NA,0x0) //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//(20,NA,0x0) //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//(21,NA,0x0) //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//(22,NA,0x0) //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//(23,NA,0x0) //1' : enable Color Region 15 selection
	UINT32 dce_domain_sel                   :1;	//(24,NA,0x0) //0' : KTD/QTD(default)(K only)	'1' : YC (Y only)
	UINT32 resvd0                           :1;
	UINT32 window_mode_enable               :1;	//(26,NA,0x0) //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//(27,NA,0x0) //0' : selected area by window0, window1	'1' : otherside
	UINT32 histogram_mode                   :2;	//(29:28,NA,0x0) //00' : Own side's histogram data use	'01' : Other side's histogram data use	'10' : Average between Own and Other side's histogram data use
	UINT32 resvd1                           :2;
	};
}PE_M23_CC_PE1_DCE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1224 RW 0x0080_001A
	UINT32 chroma_comp_color_region_gain    :8;	//(7:0,NA,0x1A) //default : "128" ( 1 ~ 255(1~400%))
	UINT32 resvd0                           :8;
	UINT32 color_region_gain                :8;	//(23:16,NA,0x80) //default : "128" ( 1 ~ 255(1~400%)) (forbidden 0 value))
	UINT32 resvd1                           :8;
	};
}PE_M23_CC_PE1_DCE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1228 RW 0x0000_0000
	UINT32 color_region_en                  :1;	//(0,NA,0x0) //Color region apply for DCE Y
	UINT32 color_debug_en                   :1;	//(1,NA,0x0) //Debug mode for Color region
	UINT32 resvd0                           :2;
	UINT32 y_grad_gain                      :2;	//(5:4,NA,0x0) //Gradient of Y signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd1                           :2;
	UINT32 cb_grad_gain                     :2;	//(9:8,NA,0x0) //Gradient of Cb signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd2                           :2;
	UINT32 cr_grad_gain                     :2;	//(13:12,NA,0x0) //Gradient of Cr signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd3                           :18;
	};
}PE_M23_CC_PE1_DCE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B122C RW 0x02D0_01E0
	UINT32 y_range_min                      :10;	//(9:0,NA,0x01E0) //default : 480
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x02D0) //default : 720
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1230 RW 0x02B4_0264
	UINT32 cb_range_min                     :10;	//(9:0,NA,0x0264) //default : 612
	UINT32 resvd0                           :6;
	UINT32 cb_range_max                     :10;	//(25:16,NA,0x02B4) //default : 692
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1234 RW 0x01FC_0134
	UINT32 cr_range_min                     :10;	//(9:0,NA,0x0134) //default : 308
	UINT32 resvd0                           :6;
	UINT32 cr_range_max                     :10;	//(25:16,NA,0x01FC) //default : 508
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1238 RW 0x0000_8000
	UINT32 hif_dyc_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dce_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dce_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dce_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_CC_PE1_DCE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B123C RO 0x0000_0000
	UINT32 hif_dyc_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1240 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1244 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 dce_ktd_csc_sel                  :1;	//(1,NA,0x0) //0' : KTD(default)	'1' : QTD
	UINT32 resvd1                           :30;
	};
}PE_M23_CC_PE1_DCE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1248 RW 0x0000_8000
	UINT32 hif_hist_address                 :7;	//(6:0,NA,0x00) //"0"   : 0th bin	"1'   : 1st bin	…	"127" : 127st bin
	UINT32 resvd0                           :5;
	UINT32 hif_hist_ai                      :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//(15,NA,0x1) //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//(18:16,NA,0x0) //"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//(28,NA,0x0) //auto increment enable
	UINT32 hif_mask                         :1;	//(29,NA,0x0) //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_M23_CC_PE1_DCE_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B124C RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_M23_CC_PE1_DCE_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1250 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_M23_CC_PE1_DCE_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1254 RW 0x0200_0200
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_M23_CC_PE1_DCE_CHR_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1258 RW 0x0200_0200
	UINT32 dce_chr_alpha2                   :10;	//(9:0,NA,0x200) //alpha(0~512), y_dce_in < y_dce_out : 0 means no gain
	UINT32 resvd0                           :6;
	UINT32 dce_chr_alpha1                   :10;	//(25:16,NA,0x200) //alpha(0~512), y_dce_in >= y_dce_out : 0 means no gain
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CHR_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B125C RW 0x0200_0200
	UINT32 dce_cr_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DCE_CHR_GAIN2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1270 RW 0x0000_0000
	UINT32 dynamic_saturation_en            :1;	//(0,NA,0x0) //0' : disable	'1' : enable
	UINT32 window_mode_enable               :1;	//(1,NA,0x0) //1' : window mode enable
	UINT32 window_inout_sel                 :1;	//(2,NA,0x0) //0' : selected area by window0, window1	'1' : otherside
	UINT32 resvd0                           :1;
	UINT32 window01_enable                  :1;	//(4,NA,0x0) //1' : window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,NA,0x0) //1' : window0 area only
	UINT32 window1_enable                   :1;	//(6,NA,0x0) //1' : window1 area only
	UINT32 window_acquire                   :1;	//(7,NA,0x0) //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 color_region0_sel                :1;	//(8,NA,0x0) //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//(9,NA,0x0) //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//(10,NA,0x0) //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//(11,NA,0x0) //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//(12,NA,0x0) //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//(13,NA,0x0) //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//(14,NA,0x0) //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//(15,NA,0x0) //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//(16,NA,0x0) //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//(17,NA,0x0) //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//(18,NA,0x0) //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//(19,NA,0x0) //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//(20,NA,0x0) //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//(21,NA,0x0) //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//(22,NA,0x0) //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//(23,NA,0x0) //1' : enable Color Region 15 selection
	UINT32 resvd1                           :8;
	};
}PE_M23_CC_PE1_DSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1274 RW 0x8000_0301
	UINT32 reg_dse_cr_mode_sel              :1;	//(0,NA,0x1) //0': use CEN color region gain, '1': use YH color region gain
	UINT32 reg_yh_cr_en                     :1;	//(1,NA,0x0) //Color region(YH) apply for DSE
	UINT32 reg_yh_debug                     :1;	//(2,NA,0x0) //Debug mode for Color region(YH)
	UINT32 resvd0                           :1;
	UINT32 r_dse_y_grad                     :2;	//(5:4,NA,0x0) //Gradient of Y signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd1                           :2;
	UINT32 r_dse_h_grad                     :2;	//(9:8,NA,0x3) //Gradient of H signal	00 : 128 to 0	01 : 64 to 0	10 : 32 to 0	11 : 16 to 0
	UINT32 resvd2                           :14;
	UINT32 color_region_gain                :8;	//(31:24,NA,0x80) //default : "128" (200%, 1 ~ 255(1~400%)) (forbidden 0 value))
	};
}PE_M23_CC_PE1_DSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1278 RW 0x03FF_03FF
	UINT32 hif_dse_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B127C RW 0x0000_8000
	UINT32 hif_dse_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_CC_PE1_DSE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1280 RO 0x0000_0000
	UINT32 hif_dse_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DSE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1284 RW 0x028A_0238
	UINT32 y_range_min                      :10;	//(9:0,NA,0x0238) //default : 568
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x028A) //default : 650
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1288 RW 0x0061_0026
	UINT32 h_range_min                      :10;	//(9:0,NA,0x0026) //default : 38
	UINT32 resvd0                           :6;
	UINT32 h_range_max                      :10;	//(25:16,NA,0x0061) //default : 97
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B128C RW 0x0000_3C00
	UINT32 reg_y_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt0_x               :10;	//(17:8,NA,0x3C) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1290 RW 0x0000_C88C
	UINT32 reg_y_region_pt1_y               :8;	//(7:0,NA,0x8C) //
	UINT32 reg_y_region_pt1_x               :10;	//(17:8,NA,0xC8) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1294 RW 0x0001_40FF
	UINT32 reg_y_region_pt2_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt2_x               :10;	//(17:8,NA,0x140) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1298 RW 0x0001_90FF
	UINT32 reg_y_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt3_x               :10;	//(17:8,NA,0x190) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B129C RW 0x0002_BCFF
	UINT32 reg_y_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt4_x               :10;	//(17:8,NA,0x2BC) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12A0 RW 0x0003_4878
	UINT32 reg_y_region_pt5_y               :8;	//(7:0,NA,0x78) //
	UINT32 reg_y_region_pt5_x               :10;	//(17:8,NA,0x348) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12A4 RW 0x0003_703C
	UINT32 reg_y_region_pt6_y               :8;	//(7:0,NA,0x3C) //
	UINT32 reg_y_region_pt6_x               :10;	//(17:8,NA,0x370) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12A8 RW 0x0003_9800
	UINT32 reg_y_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt7_x               :10;	//(17:8,NA,0x398) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_Y_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12AC RW 0x0001_F100
	UINT32 reg_h_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt0_x               :10;	//(17:8,NA,0x1F1) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12B0 RW 0x0002_00BE
	UINT32 reg_h_region_pt1_y               :8;	//(7:0,NA,0xBE) //
	UINT32 reg_h_region_pt1_x               :10;	//(17:8,NA,0x200) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12B4 RW 0x0002_0DF0
	UINT32 reg_h_region_pt2_y               :8;	//(7:0,NA,0xF0) //
	UINT32 reg_h_region_pt2_x               :10;	//(17:8,NA,0x20D) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12B8 RW 0x0002_14FF
	UINT32 reg_h_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt3_x               :10;	//(17:8,NA,0x214) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12BC RW 0x0002_28FF
	UINT32 reg_h_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt4_x               :10;	//(17:8,NA,0x228) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12C0 RW 0x0002_30FF
	UINT32 reg_h_region_pt5_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt5_x               :10;	//(17:8,NA,0x230) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12C4 RW 0x0002_3FA0
	UINT32 reg_h_region_pt6_y               :8;	//(7:0,NA,0xA0) //
	UINT32 reg_h_region_pt6_x               :10;	//(17:8,NA,0x23F) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12C8 RW 0x0002_4000
	UINT32 reg_h_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt7_x               :10;	//(17:8,NA,0x240) //
	UINT32 resvd                            :14;
	};
}PE_M23_CC_PE_DSE_H_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12E0 RW 0x0010_0100
	UINT32 reg_drc_en                       :1;	//(0,NA,0x0) //drc enable	'0' : disable	'1' : enable
	UINT32 reg_drc_cg_disable               :1;	//(1,NA,0x0) //
	UINT32 reg_drc_txt_dly                  :2;	//(3:2,NA,0x0) //
	UINT32 reg_drc_txt_gain_en              :1;	//(4,NA,0x0) //texture,apl gaining en
	UINT32 resvd0                           :3;
	UINT32 reg_drc_rgb_sel                  :2;	//(9:8,NA,0x1) //"00" : luminance	"01" : MAX(r,g,b)	others : AVG(r,g,b)
	UINT32 resvd1                           :2;
	UINT32 reg_drc_gm_mode                  :3;	//(14:12,NA,0x0) //gamma lut enable	"01" : enable	others : disable
	UINT32 resvd2                           :1;
	UINT32 reg_drc_lk_blf_apf               :1;	//(16,NA,0x0) //use bypass spatial filter coefficient for debugging	'0' : disable 	'1' : enable
	UINT32 resvd3                           :3;
	UINT32 reg_dbg_disp_apl_gain            :1;	//(20,NA,0x0) //display apl gain for debuging	'0' : disable	'1' : enable
	UINT32 resvd4                           :3;
	UINT32 reg_dbg_apl_gain_sel             :2;	//(25:24,NA,0x0) //0:selected 1:dark 2:bright
	UINT32 resvd5                           :2;
	UINT32 reg_dbg_disp_blf                 :1;	//(28,NA,0x0) //display blf image for debuging	'0' : disable	'1' : enable
	UINT32 reg_dbg_disp_lcont               :1;	//(29,NA,0x0) //display local contrast image for debugging	'0' : disable	'1' : enable
	UINT32 reg_dbg_disp_texture             :1;	//(30,NA,0x0) //texture gain image for debugging (must set reg_dbg_disp_blf to 1)	'0' : disable	'1' : enable
	UINT32 resvd6                           :1;
	};
}PE_M23_CC_PE1_DRC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12E4 RW 0x0000_0001
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x1) //selecet a,b gamma lut for register r/w	'0' : a gamma lut 	'1' : b gamma lut
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //selecet a,b gamma lut for operation	'0' : b gamma lut 	'1' : a gamma lut
	UINT32 resvd1                           :11;
	UINT32 reg_drc_gm_forced_sel            :1;	//(16,NA,0x0) //anytime rw_sel, op_sel transition
	UINT32 reg_drc_gm_protected_sel         :1;	//(17,NA,0x0) //Do not allow rw_sel, op_sel transition only in de active
	UINT32 resvd2                           :14;
	};
}PE_M23_CC_PE1_DRC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12E8 RW 0x0036_0060
	UINT32 reg_drc_bnh                      :7;	//(6:0,NA,0x60) //horizontal block size (min : 4, max : 96)
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bnv                      :6;	//(21:16,NA,0x36) //vertical block size (min : 3, max : 54)
	UINT32 resvd1                           :10;
	};
}PE_M23_CC_PE1_DRC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12EC RW 0x0050_0050
	UINT32 reg_drc_bsh                      :9;	//(8:0,NA,0x50) //
	UINT32 resvd0                           :7;
	UINT32 reg_drc_bsv                      :9;	//(24:16,NA,0x50) //
	UINT32 resvd1                           :7;
	};
}PE_M23_CC_PE1_DRC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12F0 RW 0x0321_912C
	UINT32 reg_drc_gm_apl2                  :10;	//(9:0,NA,0x12C) //apl for gamma lut 2
	UINT32 reg_drc_gm_apl1                  :10;	//(19:10,NA,0x64) //apl for gamma lut 1
	UINT32 reg_drc_gm_apl0                  :10;	//(29:20,NA,0x32) //apl for gamma lut 0
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12F4 RW 0x1F4A_F3B6
	UINT32 reg_drc_gm_apl5                  :10;	//(9:0,NA,0x3B6) //apl for gamma lut 5
	UINT32 reg_drc_gm_apl4                  :10;	//(19:10,NA,0x2BC) //apl for gamma lut 4
	UINT32 reg_drc_gm_apl3                  :10;	//(29:20,NA,0x1F4) //apl for gamma lut 3
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12F8 RW 0x0000_0030
	UINT32 reg_drc_blf_wei_cen              :8;	//(7:0,NA,0x30) //center pixel weight for blf
	UINT32 resvd                            :24;
	};
}PE_M23_CC_PE1_DRC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B12FC RW 0x00000000
	UINT32 reg_drc_apl_lut_x1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x0               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DRC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1300 RW 0x00000000
	UINT32 reg_drc_apl_lut_x3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x2               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_DRC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1304 RW 0x00000000
	UINT32 reg_drc_apl_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_apl_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_apl_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_apl_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1308 RW 0x00000000
	UINT32 reg_drc_txt_lut_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B130C RW 0x00000000
	UINT32 reg_drc_txt_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1310 RW 0x00000000
	UINT32 reg_drc_dark_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1314 RW 0x00000000
	UINT32 reg_drc_dark_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1318 RW 0x00000000
	UINT32 reg_drc_bright_lut_x3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_x2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_x1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_x0            :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B131C RW 0x00000000
	UINT32 reg_drc_bright_lut_y3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_y2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_y1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_y0            :8;	//(31:24,NA,0x0) //
	};
}PE_M23_CC_PE1_DRC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1330 RW 0x0000_0000
	UINT32 reg_drc_lut_addr_clr             :1;	//(0,NA,0x0) //lut address clear
	UINT32 resvd0                           :3;
	UINT32 reg_drc_hfc_rd_sel               :1;	//(4,NA,0x0) //blf h filter coefficient read select
	UINT32 resvd1                           :3;
	UINT32 reg_drc_vfc_rd_sel               :1;	//(8,NA,0x0) //blf v filter coefficient read select
	UINT32 resvd2                           :23;
	};
}PE_M23_CC_PE1_DRC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1334 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_hfc_data          :10;	//(9:0,NA,0x0) //blf h filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1338 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_vfc_data          :10;	//(9:0,NA,0x0) //blf v filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B133C RW 0x0000_0000
	UINT32 reg_drc_hfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_hfc_rdata: blf h filter coefficient read data	WR  [0]reg_drc_hfc_re : blf h filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1340 RW 0x0000_0000
	UINT32 reg_drc_vfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_vfc_rdata : blf v filter coefficient read data	WR  [0]reg_drc_vfc_re : blf v filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1344 WO 0x0000_0000
	UINT32 reg_drc_blf_wei_wdata            :10;	//(9:0,NA,0x0) //blf photometric weight write data
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1348 RW 0x0000_0000
	UINT32 reg_drc_blf_wei_rdata            :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_blf_wei_rdata : blf photometric weight read data	WR  [0]reg_drc_blf_wei_re : blf photometric weight read enable
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B134C WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 0	[19:10] -> gamma lut 1	[ 9: 0] -> gamma lut 2
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1350 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 0,[19:10] -> gamma lut 1,[ 9: 0] -> gamma lut 2	WR [1:0]reg_drc_gm_re : gamma lut 0, 1, 2 read enable ("01")
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1354 WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 3	[19:10] -> gamma lut 4	[ 9: 0] -> gamma lut 5
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1358 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 3,[19:10] -> gamma lut 4,[ 9: 0] -> gamma lut 5	WR [1:0]reg_drc_gm_re : gamma lut 3, 4, 5 read enable ("10")
	UINT32 resvd                            :2;
	};
}PE_M23_CC_PE1_DRC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1364 RW 0x0000_0000
	UINT32 reg_drc_bl_apl_raddr_h           :7;	//(6:0,NA,0x0) //block apl read H address
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bl_apl_raddr_v           :6;	//(21:16,NA,0x0) //block apl read V address
	UINT32 resvd1                           :10;
	};
}PE_M23_CC_PE1_DRC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1368 RO 0x0000_0000
	UINT32 reg_drc_bl_apl_rdata             :10;	//(9:0,NA,0x0) //block apl read data
	UINT32 resvd                            :22;
	};
}PE_M23_CC_PE1_DRC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B136C RO 0x0000_0000
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x0) //Read rw_sel
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //Read op_sel
	UINT32 resvd1                           :27;
	};
}PE_M23_CC_PE1_DRC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1410 RW 0x0000_0000
	UINT32 pcc_eotf_en                      :1;	//(0,NA,0x0) //
	UINT32 pcc_eotf_bit_extection_mode      :2;	//(2:1,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 pcc_oetf_en                      :1;	//(5,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_pcc_en                       :1;	//(8,NA,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_dither_en                    :1;	//(12,NA,0x0) //
	UINT32 resvd3                           :3;
	UINT32 reg_dither_temporal_en           :1;	//(16,NA,0x0) //
	UINT32 resvd4                           :3;
	UINT32 reg_sat_lut_in_mux               :1;	//(20,NA,0x0) //Saturatio alpha LUT input 0:pcc_input, 1:pcc_output
	UINT32 reg_l3d_in_mux                   :1;	//(21,NA,0x0) //3DLUT input 0:pcc_output, 1:pcc_input
	UINT32 reg_sat_blend_in_mux             :1;	//(22,NA,0x0) //Saturatio alpha blend input 0:pcc_output, 1:pcc_input
	UINT32 resvd5                           :9;
	};
}PE_M23_CC_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}PE_M23_CC_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}PE_M23_CC_PE1_PCC_COEF7_T;

typedef struct {
	PE_M23_CC_PE1_TOP_CTRL_00_T                            pe1_top_ctrl_00;	//0xCC4B1000
	PE_M23_CC_PE1_TOP_CTRL_01_T                            pe1_top_ctrl_01;	//0xCC4B1004
	PE_M23_CC_PE1_TOP_CTRL_02_T                            pe1_top_ctrl_02;	//0xCC4B1008
	PE_M23_CC_PE1_TOP_CTRL_03_T                            pe1_top_ctrl_03;	//0xCC4B100C
	PE_M23_CC_PE1_TOP_CTRL_04_T                            pe1_top_ctrl_04;	//0xCC4B1010
	UINT32                                                    reserved0;	//0xCC4B1014
	UINT32                                                    reserved1;	//0xCC4B1018
	UINT32                                                    reserved2;	//0xCC4B101C
	PE_M23_CC_PE1_FSW_CTRL_00_T                            pe1_fsw_ctrl_00;	//0xCC4B1020
	PE_M23_CC_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xCC4B1024
	PE_M23_CC_PE1_FSW_CTRL_02_T                            pe1_fsw_ctrl_02;	//0xCC4B1028
	PE_M23_CC_PE1_FSW_CTRL_03_T                            pe1_fsw_ctrl_03;	//0xCC4B102C
	PE_M23_CC_PE1_FSW_CTRL_04_T                            pe1_fsw_ctrl_04;	//0xCC4B1030
	PE_M23_CC_PE1_FSW_CTRL_05_T                            pe1_fsw_ctrl_05;	//0xCC4B1034
	PE_M23_CC_PE1_FSW_CTRL_06_T                            pe1_fsw_ctrl_06;	//0xCC4B1038
	PE_M23_CC_PE1_FSW_CTRL_07_T                            pe1_fsw_ctrl_07;	//0xCC4B103C
	UINT32                                                    reserved3;	//0xCC4B1040
	UINT32                                                    reserved4;	//0xCC4B1044
	UINT32                                                    reserved5;	//0xCC4B1048
	UINT32                                                    reserved6;	//0xCC4B104C
	PE_M23_CC_PE1_TPG_CTRL_00_T                            pe1_tpg_ctrl_00;	//0xCC4B1050
	PE_M23_CC_PE1_TPG_CTRL_01_T                            pe1_tpg_ctrl_01;	//0xCC4B1054
	PE_M23_CC_PE1_TPG_CTRL_02_T                            pe1_tpg_ctrl_02;	//0xCC4B1058
	PE_M23_CC_PE1_TPG_CTRL_03_T                            pe1_tpg_ctrl_03;	//0xCC4B105C
	PE_M23_CC_PE1_TPG_CTRL_04_T                            pe1_tpg_ctrl_04;	//0xCC4B1060
	PE_M23_CC_PE1_TPG_IA_CTRL_T                            pe1_tpg_ia_ctrl;	//0xCC4B1064
	PE_M23_CC_PE1_TPG_IA_DATA_T                            pe1_tpg_ia_data;	//0xCC4B1068
	UINT32                                                    reserved7;	//0xCC4B106C
	PE_M23_CC_PE1_APL_CTRL_00_T                            pe1_apl_ctrl_00;	//0xCC4B1070
	PE_M23_CC_PE1_APL_CTRL_01_T                            pe1_apl_ctrl_01;	//0xCC4B1074
	PE_M23_CC_PE1_APL_CTRL_02_T                            pe1_apl_ctrl_02;	//0xCC4B1078
	UINT32                                                    reserved8;	//0xCC4B107C
	UINT32                                                    reserved9;	//0xCC4B1080
	UINT32                                                   reserved10;	//0xCC4B1084
	UINT32                                                   reserved11;	//0xCC4B1088
	UINT32                                                   reserved12;	//0xCC4B108C
	UINT32                                                   reserved13;	//0xCC4B1090
	UINT32                                                   reserved14;	//0xCC4B1094
	UINT32                                                   reserved15;	//0xCC4B1098
	UINT32                                                   reserved16;	//0xCC4B109C
	UINT32                                                   reserved17;	//0xCC4B10A0
	UINT32                                                   reserved18;	//0xCC4B10A4
	UINT32                                                   reserved19;	//0xCC4B10A8
	UINT32                                                   reserved20;	//0xCC4B10AC
	UINT32                                                   reserved21;	//0xCC4B10B0
	PE_M23_CC_PE1_APL_STAT_00_T                            pe1_apl_stat_00;	//0xCC4B10B4
	PE_M23_CC_PE1_APL_STAT_01_T                            pe1_apl_stat_01;	//0xCC4B10B8
	UINT32                                                   reserved22;	//0xCC4B10BC
	UINT32                                                   reserved23;	//0xCC4B10C0
	UINT32                                                   reserved24;	//0xCC4B10C4
	UINT32                                                   reserved25;	//0xCC4B10C8
	UINT32                                                   reserved26;	//0xCC4B10CC
	UINT32                                                   reserved27;	//0xCC4B10D0
	UINT32                                                   reserved28;	//0xCC4B10D4
	UINT32                                                   reserved29;	//0xCC4B10D8
	PE_M23_CC_PE1_BT20_CTRL_07_T                          pe1_bt20_ctrl_07;	//0xCC4B10DC
	PE_M23_CC_PE1_BT20_CTRL_08_T                          pe1_bt20_ctrl_08;	//0xCC4B10E0
	UINT32                                                   reserved30;	//0xCC4B10E4
	UINT32                                                   reserved31;	//0xCC4B10E8
	UINT32                                                   reserved32;	//0xCC4B10EC
	UINT32                                                   reserved33;	//0xCC4B10F0
	PE_M23_CC_PE1_BT20_CTRL_13_T                          pe1_bt20_ctrl_13;	//0xCC4B10F4
	PE_M23_CC_PE1_BT20_CTRL_14_T                          pe1_bt20_ctrl_14;	//0xCC4B10F8
	PE_M23_CC_PE1_BT20_CTRL_15_T                          pe1_bt20_ctrl_15;	//0xCC4B10FC
	PE_M23_CC_PE1_BT20_CTRL_16_T                          pe1_bt20_ctrl_16;	//0xCC4B1100
	PE_M23_CC_PE1_BT20_CTRL_17_T                          pe1_bt20_ctrl_17;	//0xCC4B1104
	PE_M23_CC_PE1_BT20_CTRL_18_T                          pe1_bt20_ctrl_18;	//0xCC4B1108
	PE_M23_CC_PE1_BT20_CTRL_19_T                          pe1_bt20_ctrl_19;	//0xCC4B110C
	PE_M23_CC_PE1_BT20_CTRL_20_T                          pe1_bt20_ctrl_20;	//0xCC4B1110
	PE_M23_CC_PE1_BT20_CTRL_21_T                          pe1_bt20_ctrl_21;	//0xCC4B1114
	PE_M23_CC_PE1_BT20_CTRL_STAT_00_T                pe1_bt20_ctrl_stat_00;	//0xCC4B1118
	PE_M23_CC_PE1_BT20_CTRL_STAT_01_T                pe1_bt20_ctrl_stat_01;	//0xCC4B111C
	PE_M23_CC_PE1_BT20_CTRL_STAT_02_T                pe1_bt20_ctrl_stat_02;	//0xCC4B1120
	PE_M23_CC_PE1_BT20_CTRL_STAT_03_T                pe1_bt20_ctrl_stat_03;	//0xCC4B1124
	UINT32                                                   reserved34;	//0xCC4B1128
	UINT32                                                   reserved35;	//0xCC4B112C
	UINT32                                                   reserved36;	//0xCC4B1130
	UINT32                                                   reserved37;	//0xCC4B1134
	UINT32                                                   reserved38;	//0xCC4B1138
	UINT32                                                   reserved39;	//0xCC4B113C
	PE_M23_CC_PE1_WIN2_CTRL_00_T                          pe1_win2_ctrl_00;	//0xCC4B1140
	PE_M23_CC_PE1_WIN2_CTRL_01_T                          pe1_win2_ctrl_01;	//0xCC4B1144
	PE_M23_CC_PE1_WIN2_CTRL_02_T                          pe1_win2_ctrl_02;	//0xCC4B1148
	PE_M23_CC_PE1_WIN2_CTRL_03_T                          pe1_win2_ctrl_03;	//0xCC4B114C
	PE_M23_CC_PE1_WIN2_CTRL_04_T                          pe1_win2_ctrl_04;	//0xCC4B1150
	UINT32                                                   reserved40;	//0xCC4B1154
	UINT32                                                   reserved41;	//0xCC4B1158
	UINT32                                                   reserved42;	//0xCC4B115C
	UINT32                                                   reserved43;	//0xCC4B1160
	UINT32                                                   reserved44;	//0xCC4B1164
	UINT32                                                   reserved45;	//0xCC4B1168
	UINT32                                                   reserved46;	//0xCC4B116C
	UINT32                                                   reserved47;	//0xCC4B1170
	UINT32                                                   reserved48;	//0xCC4B1174
	UINT32                                                   reserved49;	//0xCC4B1178
	UINT32                                                   reserved50;	//0xCC4B117C
	UINT32                                                   reserved51;	//0xCC4B1180
	UINT32                                                   reserved52;	//0xCC4B1184
	UINT32                                                   reserved53;	//0xCC4B1188
	UINT32                                                   reserved54;	//0xCC4B118C
	UINT32                                                   reserved55;	//0xCC4B1190
	UINT32                                                   reserved56;	//0xCC4B1194
	UINT32                                                   reserved57;	//0xCC4B1198
	UINT32                                                   reserved58;	//0xCC4B119C
	UINT32                                                   reserved59;	//0xCC4B11A0
	UINT32                                                   reserved60;	//0xCC4B11A4
	UINT32                                                   reserved61;	//0xCC4B11A8
	UINT32                                                   reserved62;	//0xCC4B11AC
	UINT32                                                   reserved63;	//0xCC4B11B0
	UINT32                                                   reserved64;	//0xCC4B11B4
	UINT32                                                   reserved65;	//0xCC4B11B8
	UINT32                                                   reserved66;	//0xCC4B11BC
	UINT32                                                   reserved67;	//0xCC4B11C0
	UINT32                                                   reserved68;	//0xCC4B11C4
	UINT32                                                   reserved69;	//0xCC4B11C8
	UINT32                                                   reserved70;	//0xCC4B11CC
	PE_M23_CC_PE1_CEN_CTRL_00_T                            pe1_cen_ctrl_00;	//0xCC4B11D0
	PE_M23_CC_PE1_CEN_CTRL_01_T                            pe1_cen_ctrl_01;	//0xCC4B11D4
	PE_M23_CC_PE1_CEN_CTRL_02_T                            pe1_cen_ctrl_02;	//0xCC4B11D8
	PE_M23_CC_PE1_CEN_CTRL_03_T                            pe1_cen_ctrl_03;	//0xCC4B11DC
	PE_M23_CC_PE1_CEN_CTRL_04_T                            pe1_cen_ctrl_04;	//0xCC4B11E0
	PE_M23_CC_PE1_CEN_CTRL_05_T                            pe1_cen_ctrl_05;	//0xCC4B11E4
	PE_M23_CC_PE1_CEN_CTRL_06_T                            pe1_cen_ctrl_06;	//0xCC4B11E8
	PE_M23_CC_PE1_CEN_CTRL_07_T                            pe1_cen_ctrl_07;	//0xCC4B11EC
	UINT32                                                   reserved71;	//0xCC4B11F0
	UINT32                                                   reserved72;	//0xCC4B11F4
	PE_M23_CC_PE1_CEN_UPD_CTRL_T                          pe1_cen_upd_ctrl;	//0xCC4B11F8
	UINT32                                                   reserved73;	//0xCC4B11FC
	PE_M23_CC_PE1_CEN_IA_CTRL_T                            pe1_cen_ia_ctrl;	//0xCC4B1200
	PE_M23_CC_PE1_CEN_IA_DATA_T                            pe1_cen_ia_data;	//0xCC4B1204
	PE_M23_CC_PE1_CEN_DELTA_IA_CTRL_T                pe1_cen_delta_ia_ctrl;	//0xCC4B1208
	PE_M23_CC_PE1_CEN_DELTA_IA_DATA_T                pe1_cen_delta_ia_data;	//0xCC4B120C
	UINT32                                                   reserved74;	//0xCC4B1210
	UINT32                                                   reserved75;	//0xCC4B1214
	UINT32                                                   reserved76;	//0xCC4B1218
	UINT32                                                   reserved77;	//0xCC4B121C
	PE_M23_CC_PE1_DCE_CTRL_00_T                            pe1_dce_ctrl_00;	//0xCC4B1220
	PE_M23_CC_PE1_DCE_CTRL_01_T                            pe1_dce_ctrl_01;	//0xCC4B1224
	PE_M23_CC_PE1_DCE_CTRL_02_T                            pe1_dce_ctrl_02;	//0xCC4B1228
	PE_M23_CC_PE1_DCE_CTRL_03_T                            pe1_dce_ctrl_03;	//0xCC4B122C
	PE_M23_CC_PE1_DCE_CTRL_04_T                            pe1_dce_ctrl_04;	//0xCC4B1230
	PE_M23_CC_PE1_DCE_CTRL_05_T                            pe1_dce_ctrl_05;	//0xCC4B1234
	PE_M23_CC_PE1_DCE_IA_CTRL_T                            pe1_dce_ia_ctrl;	//0xCC4B1238
	PE_M23_CC_PE1_DCE_IA_DATA_T                            pe1_dce_ia_data;	//0xCC4B123C
	PE_M23_CC_PE1_DCE_CTRL_08_T                            pe1_dce_ctrl_08;	//0xCC4B1240
	PE_M23_CC_PE1_DCE_CTRL_09_T                            pe1_dce_ctrl_09;	//0xCC4B1244
	PE_M23_CC_PE1_DCE_HIST_IA_CTRL_T                  pe1_dce_hist_ia_ctrl;	//0xCC4B1248
	PE_M23_CC_PE1_DCE_HIST_IA_DATA1_T                pe1_dce_hist_ia_data1;	//0xCC4B124C
	PE_M23_CC_PE1_DCE_HIST_IA_DATA2_T                pe1_dce_hist_ia_data2;	//0xCC4B1250
	PE_M23_CC_PE1_DCE_CHR_GAIN_T                          pe1_dce_chr_gain;	//0xCC4B1254
	PE_M23_CC_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0xCC4B1258
	PE_M23_CC_PE1_DCE_CHR_GAIN2_T                        pe1_dce_chr_gain2;	//0xCC4B125C
	UINT32                                                   reserved78;	//0xCC4B1260
	UINT32                                                   reserved79;	//0xCC4B1264
	UINT32                                                   reserved80;	//0xCC4B1268
	UINT32                                                   reserved81;	//0xCC4B126C
	PE_M23_CC_PE1_DSE_CTRL_00_T                            pe1_dse_ctrl_00;	//0xCC4B1270
	PE_M23_CC_PE1_DSE_CTRL_01_T                            pe1_dse_ctrl_01;	//0xCC4B1274
	PE_M23_CC_PE1_DSE_CTRL_02_T                            pe1_dse_ctrl_02;	//0xCC4B1278
	PE_M23_CC_PE1_DSE_IA_CTRL_T                            pe1_dse_ia_ctrl;	//0xCC4B127C
	PE_M23_CC_PE1_DSE_IA_DATA_T                            pe1_dse_ia_data;	//0xCC4B1280
	PE_M23_CC_PE1_DSE_CTRL_03_T                            pe1_dse_ctrl_03;	//0xCC4B1284
	PE_M23_CC_PE1_DSE_CTRL_04_T                            pe1_dse_ctrl_04;	//0xCC4B1288
	PE_M23_CC_PE_DSE_Y_REGION_PT0_T                    pe_dse_y_region_pt0;	//0xCC4B128C
	PE_M23_CC_PE_DSE_Y_REGION_PT1_T                    pe_dse_y_region_pt1;	//0xCC4B1290
	PE_M23_CC_PE_DSE_Y_REGION_PT2_T                    pe_dse_y_region_pt2;	//0xCC4B1294
	PE_M23_CC_PE_DSE_Y_REGION_PT3_T                    pe_dse_y_region_pt3;	//0xCC4B1298
	PE_M23_CC_PE_DSE_Y_REGION_PT4_T                    pe_dse_y_region_pt4;	//0xCC4B129C
	PE_M23_CC_PE_DSE_Y_REGION_PT5_T                    pe_dse_y_region_pt5;	//0xCC4B12A0
	PE_M23_CC_PE_DSE_Y_REGION_PT6_T                    pe_dse_y_region_pt6;	//0xCC4B12A4
	PE_M23_CC_PE_DSE_Y_REGION_PT7_T                    pe_dse_y_region_pt7;	//0xCC4B12A8
	PE_M23_CC_PE_DSE_H_REGION_PT0_T                    pe_dse_h_region_pt0;	//0xCC4B12AC
	PE_M23_CC_PE_DSE_H_REGION_PT1_T                    pe_dse_h_region_pt1;	//0xCC4B12B0
	PE_M23_CC_PE_DSE_H_REGION_PT2_T                    pe_dse_h_region_pt2;	//0xCC4B12B4
	PE_M23_CC_PE_DSE_H_REGION_PT3_T                    pe_dse_h_region_pt3;	//0xCC4B12B8
	PE_M23_CC_PE_DSE_H_REGION_PT4_T                    pe_dse_h_region_pt4;	//0xCC4B12BC
	PE_M23_CC_PE_DSE_H_REGION_PT5_T                    pe_dse_h_region_pt5;	//0xCC4B12C0
	PE_M23_CC_PE_DSE_H_REGION_PT6_T                    pe_dse_h_region_pt6;	//0xCC4B12C4
	PE_M23_CC_PE_DSE_H_REGION_PT7_T                    pe_dse_h_region_pt7;	//0xCC4B12C8
	UINT32                                                   reserved82;	//0xCC4B12CC
	UINT32                                                   reserved83;	//0xCC4B12D0
	UINT32                                                   reserved84;	//0xCC4B12D4
	UINT32                                                   reserved85;	//0xCC4B12D8
	UINT32                                                   reserved86;	//0xCC4B12DC
	PE_M23_CC_PE1_DRC_CTRL_00_T                            pe1_drc_ctrl_00;	//0xCC4B12E0
	PE_M23_CC_PE1_DRC_CTRL_01_T                            pe1_drc_ctrl_01;	//0xCC4B12E4
	PE_M23_CC_PE1_DRC_CTRL_02_T                            pe1_drc_ctrl_02;	//0xCC4B12E8
	PE_M23_CC_PE1_DRC_CTRL_03_T                            pe1_drc_ctrl_03;	//0xCC4B12EC
	PE_M23_CC_PE1_DRC_CTRL_04_T                            pe1_drc_ctrl_04;	//0xCC4B12F0
	PE_M23_CC_PE1_DRC_CTRL_05_T                            pe1_drc_ctrl_05;	//0xCC4B12F4
	PE_M23_CC_PE1_DRC_CTRL_06_T                            pe1_drc_ctrl_06;	//0xCC4B12F8
	PE_M23_CC_PE1_DRC_CTRL_07_T                            pe1_drc_ctrl_07;	//0xCC4B12FC
	PE_M23_CC_PE1_DRC_CTRL_08_T                            pe1_drc_ctrl_08;	//0xCC4B1300
	PE_M23_CC_PE1_DRC_CTRL_09_T                            pe1_drc_ctrl_09;	//0xCC4B1304
	PE_M23_CC_PE1_DRC_CTRL_10_T                            pe1_drc_ctrl_10;	//0xCC4B1308
	PE_M23_CC_PE1_DRC_CTRL_11_T                            pe1_drc_ctrl_11;	//0xCC4B130C
	PE_M23_CC_PE1_DRC_CTRL_12_T                            pe1_drc_ctrl_12;	//0xCC4B1310
	PE_M23_CC_PE1_DRC_CTRL_13_T                            pe1_drc_ctrl_13;	//0xCC4B1314
	PE_M23_CC_PE1_DRC_CTRL_14_T                            pe1_drc_ctrl_14;	//0xCC4B1318
	PE_M23_CC_PE1_DRC_CTRL_15_T                            pe1_drc_ctrl_15;	//0xCC4B131C
	UINT32                                                   reserved87;	//0xCC4B1320
	UINT32                                                   reserved88;	//0xCC4B1324
	UINT32                                                   reserved89;	//0xCC4B1328
	UINT32                                                   reserved90;	//0xCC4B132C
	PE_M23_CC_PE1_DRC_CTRL_20_T                            pe1_drc_ctrl_20;	//0xCC4B1330
	PE_M23_CC_PE1_DRC_CTRL_21_T                            pe1_drc_ctrl_21;	//0xCC4B1334
	PE_M23_CC_PE1_DRC_CTRL_22_T                            pe1_drc_ctrl_22;	//0xCC4B1338
	PE_M23_CC_PE1_DRC_CTRL_23_T                            pe1_drc_ctrl_23;	//0xCC4B133C
	PE_M23_CC_PE1_DRC_CTRL_24_T                            pe1_drc_ctrl_24;	//0xCC4B1340
	PE_M23_CC_PE1_DRC_CTRL_25_T                            pe1_drc_ctrl_25;	//0xCC4B1344
	PE_M23_CC_PE1_DRC_CTRL_26_T                            pe1_drc_ctrl_26;	//0xCC4B1348
	PE_M23_CC_PE1_DRC_CTRL_27_T                            pe1_drc_ctrl_27;	//0xCC4B134C
	PE_M23_CC_PE1_DRC_CTRL_28_T                            pe1_drc_ctrl_28;	//0xCC4B1350
	PE_M23_CC_PE1_DRC_CTRL_29_T                            pe1_drc_ctrl_29;	//0xCC4B1354
	PE_M23_CC_PE1_DRC_CTRL_30_T                            pe1_drc_ctrl_30;	//0xCC4B1358
	UINT32                                                   reserved91;	//0xCC4B135C
	UINT32                                                   reserved92;	//0xCC4B1360
	PE_M23_CC_PE1_DRC_CTRL_33_T                            pe1_drc_ctrl_33;	//0xCC4B1364
	PE_M23_CC_PE1_DRC_CTRL_34_T                            pe1_drc_ctrl_34;	//0xCC4B1368
	PE_M23_CC_PE1_DRC_CTRL_35_T                            pe1_drc_ctrl_35;	//0xCC4B136C
	UINT32                                                   reserved93;	//0xCC4B1370
	UINT32                                                   reserved94;	//0xCC4B1374
	UINT32                                                   reserved95;	//0xCC4B1378
	UINT32                                                   reserved96;	//0xCC4B137C
	UINT32                                                   reserved97;	//0xCC4B1380
	UINT32                                                   reserved98;	//0xCC4B1384
	UINT32                                                   reserved99;	//0xCC4B1388
	UINT32                                                  reserved100;	//0xCC4B138C
	UINT32                                                  reserved101;	//0xCC4B1390
	UINT32                                                  reserved102;	//0xCC4B1394
	UINT32                                                  reserved103;	//0xCC4B1398
	UINT32                                                  reserved104;	//0xCC4B139C
	UINT32                                                  reserved105;	//0xCC4B13A0
	UINT32                                                  reserved106;	//0xCC4B13A4
	UINT32                                                  reserved107;	//0xCC4B13A8
	UINT32                                                  reserved108;	//0xCC4B13AC
	UINT32                                                  reserved109;	//0xCC4B13B0
	UINT32                                                  reserved110;	//0xCC4B13B4
	UINT32                                                  reserved111;	//0xCC4B13B8
	UINT32                                                  reserved112;	//0xCC4B13BC
	UINT32                                                  reserved113;	//0xCC4B13C0
	UINT32                                                  reserved114;	//0xCC4B13C4
	UINT32                                                  reserved115;	//0xCC4B13C8
	UINT32                                                  reserved116;	//0xCC4B13CC
	UINT32                                                  reserved117;	//0xCC4B13D0
	UINT32                                                  reserved118;	//0xCC4B13D4
	UINT32                                                  reserved119;	//0xCC4B13D8
	UINT32                                                  reserved120;	//0xCC4B13DC
	UINT32                                                  reserved121;	//0xCC4B13E0
	UINT32                                                  reserved122;	//0xCC4B13E4
	UINT32                                                  reserved123;	//0xCC4B13E8
	UINT32                                                  reserved124;	//0xCC4B13EC
	UINT32                                                  reserved125;	//0xCC4B13F0
	UINT32                                                  reserved126;	//0xCC4B13F4
	UINT32                                                  reserved127;	//0xCC4B13F8
	UINT32                                                  reserved128;	//0xCC4B13FC
	UINT32                                                  reserved129;	//0xCC4B1400
	UINT32                                                  reserved130;	//0xCC4B1404
	UINT32                                                  reserved131;	//0xCC4B1408
	UINT32                                                  reserved132;	//0xCC4B140C
	PE_M23_CC_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC4B1410
	PE_M23_CC_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC4B1414
	PE_M23_CC_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC4B1418
	PE_M23_CC_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC4B141C
	PE_M23_CC_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC4B1420
	PE_M23_CC_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC4B1424
	PE_M23_CC_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC4B1428
	PE_M23_CC_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC4B142C
	PE_M23_CC_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC4B1430
}PE_CC_PE1_REG_M23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1500 RW 0x0200_0040
	UINT32 enable                           :1;	//(0,NA,0x0) //
	UINT32 graycolor_enable                 :1;	//(1,NA,0x0) //
	UINT32 color_only_enable                :1;	//(2,NA,0x0) //
	UINT32 cb_info                          :1;	//(3,NA,0x0) //
	UINT32 cr_info                          :1;	//(4,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_en                      :1;	//(6,NA,0x1) //
	UINT32 resvd1                           :1;
	UINT32 center_position                  :8;	//(15:8,NA,0x00) //center position for contrast control(Y domain)
	UINT32 contrast                         :10;	//(25:16,NA,0x200) //contrast control(Y domain)
	UINT32 resvd2                           :2;
	UINT32 reg_vspyc_debug                  :3;	//(30:28,NA,0x0) //1,2:object_gain, 3: saturation_alpha, others:vsp_yc_out
	UINT32 resvd3                           :1;
	};
}PE_M23_CC2_PE1_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1504 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
}PE_M23_CC2_PE1_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1550 RW 0x01F1_0000
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x1F1) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1554 RW 0x0200_00BE
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xBE) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1558 RW 0x020D_00F0
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xF0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x20D) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B155C RW 0x0214_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x214) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1560 RW 0x0228_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x228) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1564 RW 0x0230_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x230) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1568 RW 0x023F_00A0
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xA0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x23F) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B156C RW 0x024D_0000
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x24D) //
	UINT32 resvd1                           :6;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1570 RW 0x2D6E_2000
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x20) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0x6E) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x2D) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1574 RW 0x46FF_39C8
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xC8) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0x39) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x46) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1578 RW 0x66FF_53FF
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x53) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x66) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B157C RW 0x7FFF_7DFF
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x7D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x7F) //
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1580 RW 0x328C_0F00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0xF) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x32) //
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1584 RW 0x64FF_50FF
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x50) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x64) //
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1588 RW 0xD278_AFFF
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xAF) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0x78) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xD2) //
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B158C RO 0xE600_DC3C
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xDC) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xE6) //
	};
}PE_M23_CC2_PE1_VSP_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15A0 RW 0x0000_0000
	UINT32 enable_debug_mode                :1;	//(0,NA,0x0) //Enable debug mode
	UINT32 status_enable                    :1;	//(1,NA,0x0) //APL
	UINT32 debug_mode                       :1;	//(2,NA,0x0) //0' : status read(APL)	'1' : yc control
	UINT32 resvd0                           :17;
	UINT32 show_apl                         :1;	//(20,NA,0x0) //show apl( y, rgb, r,g,b)
	UINT32 resvd1                           :11;
	};
}PE_M23_CC2_PE1_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15A4 RW VNA
	UINT32 yc_debug_en                      :1;	//(0,NA,0x0) //
	UINT32 force_yy_enable                  :1;	//(1,NA,0x0) //forcing Y data enable
	UINT32 force_cb_enable                  :1;	//(2,NA,0x0) //forcing Cb data enable
	UINT32 force_cr_enable                  :1;	//(3,NA,0x0) //forcing Cr data enable
	UINT32 yc_debug_mode_sel                :3;	//(6:4,NA,0x0) //"000" : normal	"001" : show Y only(grayscale)	"010" : show CbCr only	"011" : show Cb data at Y channel	"100" : show Cr data at Y channel	others : normal
	UINT32 resvd                            :25;
	};
}PE_M23_CC2_PE1_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15A8 RW 0x0000_0000
	UINT32 force_yy                         :10;	//(9:0,NA,0x0) //
	UINT32 force_cb                         :10;	//(19:10,NA,0x0) //forcing Cb data
	UINT32 force_cr                         :10;	//(29:20,NA,0x0) //forcing Cr data
	UINT32 resvd                            :2;
	};
}PE_M23_CC2_PE1_DEBUG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15B0 RW 0x0000_0100
	UINT32 reg_cw_en                        :1;	//(0,NA,0x0) //
	UINT32 reg_cw_gain_sel                  :1;	//(1,NA,0x0) //0:external(from CEN) cr_gain, 1:internal cr_gain
	UINT32 resvd0                           :1;
	UINT32 reg_clock_gating_disable         :1;	//(3,NA,0x0) //
	UINT32 reg_cw_debug_view                :2;	//(5:4,NA,0x0) //0 := normal output	1 = final gain (R/G/B separate)	2 = cr_gain
	UINT32 resvd1                           :2;
	UINT32 reg_hsv_hsl_sel                  :1;	//(8,NA,0x1) //0:HSL, 1:HSV
	UINT32 reg_hsv_sat_sel                  :1;	//(9,NA,0x0) //0:(max(rgb)-min(rgb))/max(rgb), 1:max(rgb)-min(rgb)
	UINT32 resvd2                           :22;
	};
}PE_M23_CC2_PE1_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15B4 RW 0x00C0_C0C0
	UINT32 user_ctrl_g_gain                 :8;	//(7:0,NA,0xC0) //User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//(15:8,NA,0xC0) //User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//(23:16,NA,0xC0) //User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}PE_M23_CC2_PE1_CW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B15B8 RW 0x0040_0000
	UINT32 color_region0_sel                :1;	//(0,NA,0x0) //1' : enable Color Region 0 selection
	UINT32 color_region1_sel                :1;	//(1,NA,0x0) //1' : enable Color Region 1 selection
	UINT32 color_region2_sel                :1;	//(2,NA,0x0) //1' : enable Color Region 2 selection
	UINT32 color_region3_sel                :1;	//(3,NA,0x0) //1' : enable Color Region 3 selection
	UINT32 color_region4_sel                :1;	//(4,NA,0x0) //1' : enable Color Region 4 selection
	UINT32 color_region5_sel                :1;	//(5,NA,0x0) //1' : enable Color Region 5 selection
	UINT32 color_region6_sel                :1;	//(6,NA,0x0) //1' : enable Color Region 6 selection
	UINT32 color_region7_sel                :1;	//(7,NA,0x0) //1' : enable Color Region 7 selection
	UINT32 color_region8_sel                :1;	//(8,NA,0x0) //1' : enable Color Region 8 selection
	UINT32 color_region9_sel                :1;	//(9,NA,0x0) //1' : enable Color Region 9 selection
	UINT32 color_region10_sel               :1;	//(10,NA,0x0) //1' : enable Color Region 10 selection
	UINT32 color_region11_sel               :1;	//(11,NA,0x0) //1' : enable Color Region 11 selection
	UINT32 color_region12_sel               :1;	//(12,NA,0x0) //1' : enable Color Region 12 selection
	UINT32 color_region13_sel               :1;	//(13,NA,0x0) //1' : enable Color Region 13 selection
	UINT32 color_region14_sel               :1;	//(14,NA,0x0) //1' : enable Color Region 14 selection
	UINT32 color_region15_sel               :1;	//(15,NA,0x0) //1' : enable Color Region 15 selection
	UINT32 color_region_gain                :8;	//(23:16,NA,0x40) //default : "64"( 0 ~ 255(1~400%))
	UINT32 resvd                            :8;
	};
}PE_M23_CC2_PE1_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17E0 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17E4 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17E8 RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17EC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17F0 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17F4 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17F8 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B17FC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1800 RW VNA
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1804 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1808 RW 0x0000_0000
	UINT32 mux3d_en                         :1;	//(0,NA,0x0) //Mux 3D on/off	'0' = off	'1' = on
	UINT32 resvd0                           :3;
	UINT32 reg_out_mux                      :2;	//(5:4,NA,0x00) //output select	'00' = blend	'01' = R	'10' = L	'11' = line by line
	UINT32 start_parity                     :1;	//(6,NA,0x00) //start parity	'0' : start with Left	'1' : start with Right
	UINT32 resvd1                           :9;
	UINT32 alpha1_gain                      :8;	//(23:16,NA,0x0) //gain for L, R channel blend	255 : L output ~ 0 : R output
	UINT32 alpha0_gain                      :8;	//(31:24,NA,0x0) //gain for Back Ground Color and Blended Data	255 : BG Color output ~ 0 : Data output
	};
}PE_M23_CC2_PE1_MUTE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B180C RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_0              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_0              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_M23_CC2_PE1_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1810 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1814 RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_0              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_0              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_M23_CC2_PE1_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B1818 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4B181C RW 0x0000_0000
	UINT32 bg_color_r                       :8;	//(7:0,NA,0x0) //8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//(15:8,NA,0x0) //8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//(23:16,NA,0x0) //8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}PE_M23_CC2_PE1_MUTE_CTRL_15_T;

typedef struct {
	PE_M23_CC2_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xCC4B1500
	PE_M23_CC2_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xCC4B1504
	UINT32                                                    reserved0;	//0xCC4B1508
	UINT32                                                    reserved1;	//0xCC4B150C
	UINT32                                                    reserved2;	//0xCC4B1510
	UINT32                                                    reserved3;	//0xCC4B1514
	UINT32                                                    reserved4;	//0xCC4B1518
	UINT32                                                    reserved5;	//0xCC4B151C
	UINT32                                                    reserved6;	//0xCC4B1520
	UINT32                                                    reserved7;	//0xCC4B1524
	UINT32                                                    reserved8;	//0xCC4B1528
	UINT32                                                    reserved9;	//0xCC4B152C
	UINT32                                                   reserved10;	//0xCC4B1530
	UINT32                                                   reserved11;	//0xCC4B1534
	UINT32                                                   reserved12;	//0xCC4B1538
	UINT32                                                   reserved13;	//0xCC4B153C
	UINT32                                                   reserved14;	//0xCC4B1540
	UINT32                                                   reserved15;	//0xCC4B1544
	UINT32                                                   reserved16;	//0xCC4B1548
	UINT32                                                   reserved17;	//0xCC4B154C
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xCC4B1550
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xCC4B1554
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xCC4B1558
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xCC4B155C
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xCC4B1560
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xCC4B1564
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xCC4B1568
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xCC4B156C
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xCC4B1570
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xCC4B1574
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xCC4B1578
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xCC4B157C
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xCC4B1580
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xCC4B1584
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xCC4B1588
	PE_M23_CC2_PE1_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xCC4B158C
	UINT32                                                   reserved18;	//0xCC4B1590
	UINT32                                                   reserved19;	//0xCC4B1594
	UINT32                                                   reserved20;	//0xCC4B1598
	UINT32                                                   reserved21;	//0xCC4B159C
	PE_M23_CC2_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xCC4B15A0
	PE_M23_CC2_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xCC4B15A4
	PE_M23_CC2_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xCC4B15A8
	UINT32                                                   reserved22;	//0xCC4B15AC
	PE_M23_CC2_PE1_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xCC4B15B0
	PE_M23_CC2_PE1_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xCC4B15B4
	PE_M23_CC2_PE1_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xCC4B15B8
	UINT32                                                   reserved23;	//0xCC4B15BC
	UINT32                                                   reserved24;	//0xCC4B15C0
	UINT32                                                   reserved25;	//0xCC4B15C4
	UINT32                                                   reserved26;	//0xCC4B15C8
	UINT32                                                   reserved27;	//0xCC4B15CC
	UINT32                                                   reserved28;	//0xCC4B15D0
	UINT32                                                   reserved29;	//0xCC4B15D4
	UINT32                                                   reserved30;	//0xCC4B15D8
	UINT32                                                   reserved31;	//0xCC4B15DC
	UINT32                                                   reserved32;	//0xCC4B15E0
	UINT32                                                   reserved33;	//0xCC4B15E4
	UINT32                                                   reserved34;	//0xCC4B15E8
	UINT32                                                   reserved35;	//0xCC4B15EC
	UINT32                                                   reserved36;	//0xCC4B15F0
	UINT32                                                   reserved37;	//0xCC4B15F4
	UINT32                                                   reserved38;	//0xCC4B15F8
	UINT32                                                   reserved39;	//0xCC4B15FC
	UINT32                                                   reserved40;	//0xCC4B1600
	UINT32                                                   reserved41;	//0xCC4B1604
	UINT32                                                   reserved42;	//0xCC4B1608
	UINT32                                                   reserved43;	//0xCC4B160C
	UINT32                                                   reserved44;	//0xCC4B1610
	UINT32                                                   reserved45;	//0xCC4B1614
	UINT32                                                   reserved46;	//0xCC4B1618
	UINT32                                                   reserved47;	//0xCC4B161C
	UINT32                                                   reserved48;	//0xCC4B1620
	UINT32                                                   reserved49;	//0xCC4B1624
	UINT32                                                   reserved50;	//0xCC4B1628
	UINT32                                                   reserved51;	//0xCC4B162C
	UINT32                                                   reserved52;	//0xCC4B1630
	UINT32                                                   reserved53;	//0xCC4B1634
	UINT32                                                   reserved54;	//0xCC4B1638
	UINT32                                                   reserved55;	//0xCC4B163C
	UINT32                                                   reserved56;	//0xCC4B1640
	UINT32                                                   reserved57;	//0xCC4B1644
	UINT32                                                   reserved58;	//0xCC4B1648
	UINT32                                                   reserved59;	//0xCC4B164C
	UINT32                                                   reserved60;	//0xCC4B1650
	UINT32                                                   reserved61;	//0xCC4B1654
	UINT32                                                   reserved62;	//0xCC4B1658
	UINT32                                                   reserved63;	//0xCC4B165C
	UINT32                                                   reserved64;	//0xCC4B1660
	UINT32                                                   reserved65;	//0xCC4B1664
	UINT32                                                   reserved66;	//0xCC4B1668
	UINT32                                                   reserved67;	//0xCC4B166C
	UINT32                                                   reserved68;	//0xCC4B1670
	UINT32                                                   reserved69;	//0xCC4B1674
	UINT32                                                   reserved70;	//0xCC4B1678
	UINT32                                                   reserved71;	//0xCC4B167C
	UINT32                                                   reserved72;	//0xCC4B1680
	UINT32                                                   reserved73;	//0xCC4B1684
	UINT32                                                   reserved74;	//0xCC4B1688
	UINT32                                                   reserved75;	//0xCC4B168C
	UINT32                                                   reserved76;	//0xCC4B1690
	UINT32                                                   reserved77;	//0xCC4B1694
	UINT32                                                   reserved78;	//0xCC4B1698
	UINT32                                                   reserved79;	//0xCC4B169C
	UINT32                                                   reserved80;	//0xCC4B16A0
	UINT32                                                   reserved81;	//0xCC4B16A4
	UINT32                                                   reserved82;	//0xCC4B16A8
	UINT32                                                   reserved83;	//0xCC4B16AC
	UINT32                                                   reserved84;	//0xCC4B16B0
	UINT32                                                   reserved85;	//0xCC4B16B4
	UINT32                                                   reserved86;	//0xCC4B16B8
	UINT32                                                   reserved87;	//0xCC4B16BC
	UINT32                                                   reserved88;	//0xCC4B16C0
	UINT32                                                   reserved89;	//0xCC4B16C4
	UINT32                                                   reserved90;	//0xCC4B16C8
	UINT32                                                   reserved91;	//0xCC4B16CC
	UINT32                                                   reserved92;	//0xCC4B16D0
	UINT32                                                   reserved93;	//0xCC4B16D4
	UINT32                                                   reserved94;	//0xCC4B16D8
	UINT32                                                   reserved95;	//0xCC4B16DC
	UINT32                                                   reserved96;	//0xCC4B16E0
	UINT32                                                   reserved97;	//0xCC4B16E4
	UINT32                                                   reserved98;	//0xCC4B16E8
	UINT32                                                   reserved99;	//0xCC4B16EC
	UINT32                                                  reserved100;	//0xCC4B16F0
	UINT32                                                  reserved101;	//0xCC4B16F4
	UINT32                                                  reserved102;	//0xCC4B16F8
	UINT32                                                  reserved103;	//0xCC4B16FC
	UINT32                                                  reserved104;	//0xCC4B1700
	UINT32                                                  reserved105;	//0xCC4B1704
	UINT32                                                  reserved106;	//0xCC4B1708
	UINT32                                                  reserved107;	//0xCC4B170C
	UINT32                                                  reserved108;	//0xCC4B1710
	UINT32                                                  reserved109;	//0xCC4B1714
	UINT32                                                  reserved110;	//0xCC4B1718
	UINT32                                                  reserved111;	//0xCC4B171C
	UINT32                                                  reserved112;	//0xCC4B1720
	UINT32                                                  reserved113;	//0xCC4B1724
	UINT32                                                  reserved114;	//0xCC4B1728
	UINT32                                                  reserved115;	//0xCC4B172C
	UINT32                                                  reserved116;	//0xCC4B1730
	UINT32                                                  reserved117;	//0xCC4B1734
	UINT32                                                  reserved118;	//0xCC4B1738
	UINT32                                                  reserved119;	//0xCC4B173C
	UINT32                                                  reserved120;	//0xCC4B1740
	UINT32                                                  reserved121;	//0xCC4B1744
	UINT32                                                  reserved122;	//0xCC4B1748
	UINT32                                                  reserved123;	//0xCC4B174C
	UINT32                                                  reserved124;	//0xCC4B1750
	UINT32                                                  reserved125;	//0xCC4B1754
	UINT32                                                  reserved126;	//0xCC4B1758
	UINT32                                                  reserved127;	//0xCC4B175C
	UINT32                                                  reserved128;	//0xCC4B1760
	UINT32                                                  reserved129;	//0xCC4B1764
	UINT32                                                  reserved130;	//0xCC4B1768
	UINT32                                                  reserved131;	//0xCC4B176C
	UINT32                                                  reserved132;	//0xCC4B1770
	UINT32                                                  reserved133;	//0xCC4B1774
	UINT32                                                  reserved134;	//0xCC4B1778
	UINT32                                                  reserved135;	//0xCC4B177C
	UINT32                                                  reserved136;	//0xCC4B1780
	UINT32                                                  reserved137;	//0xCC4B1784
	UINT32                                                  reserved138;	//0xCC4B1788
	UINT32                                                  reserved139;	//0xCC4B178C
	UINT32                                                  reserved140;	//0xCC4B1790
	UINT32                                                  reserved141;	//0xCC4B1794
	UINT32                                                  reserved142;	//0xCC4B1798
	UINT32                                                  reserved143;	//0xCC4B179C
	UINT32                                                  reserved144;	//0xCC4B17A0
	UINT32                                                  reserved145;	//0xCC4B17A4
	UINT32                                                  reserved146;	//0xCC4B17A8
	UINT32                                                  reserved147;	//0xCC4B17AC
	UINT32                                                  reserved148;	//0xCC4B17B0
	UINT32                                                  reserved149;	//0xCC4B17B4
	UINT32                                                  reserved150;	//0xCC4B17B8
	UINT32                                                  reserved151;	//0xCC4B17BC
	UINT32                                                  reserved152;	//0xCC4B17C0
	UINT32                                                  reserved153;	//0xCC4B17C4
	UINT32                                                  reserved154;	//0xCC4B17C8
	UINT32                                                  reserved155;	//0xCC4B17CC
	UINT32                                                  reserved156;	//0xCC4B17D0
	UINT32                                                  reserved157;	//0xCC4B17D4
	UINT32                                                  reserved158;	//0xCC4B17D8
	UINT32                                                  reserved159;	//0xCC4B17DC
	PE_M23_CC2_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xCC4B17E0
	PE_M23_CC2_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xCC4B17E4
	PE_M23_CC2_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xCC4B17E8
	PE_M23_CC2_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xCC4B17EC
	PE_M23_CC2_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xCC4B17F0
	PE_M23_CC2_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xCC4B17F4
	PE_M23_CC2_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xCC4B17F8
	PE_M23_CC2_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xCC4B17FC
	PE_M23_CC2_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xCC4B1800
	PE_M23_CC2_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xCC4B1804
	PE_M23_CC2_PE1_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xCC4B1808
	PE_M23_CC2_PE1_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xCC4B180C
	PE_M23_CC2_PE1_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xCC4B1810
	PE_M23_CC2_PE1_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xCC4B1814
	PE_M23_CC2_PE1_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xCC4B1818
	PE_M23_CC2_PE1_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xCC4B181C
}PE_CC2_PE1_REG_M23_T;


typedef union {
	UINT32 udata32;
	struct {						//0xC9012200 RW
	UINT32 run_status                   :8;	//31:0	//
	UINT32 run_count                    :16;	//31:0	//
	UINT32 db_status                   	:8;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012204 RW
	UINT32 posd_w                   :16;	//15:0	//
	UINT32 posd_h                   :16;	//31:16	//
	};
}PE_M23_CCO_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012208 RW
	UINT32 reg_sys_veri_2                   :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901220C RW
	UINT32 reg_sys_veri_3                   :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012210 RW
	UINT32 reg_sys_veri_4                   :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012214 RW
	UINT32 reg_sys_veri_5                   :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012218 RW
	UINT32 head_apl                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 body_apl                   :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_M23_CCO_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901221C RW
	UINT32 head_map                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 depth_map                  :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_M23_CCO_VERI_SYS_VERI_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012220 RW
	UINT32 contrast                    :16;	//(15:0,RW,0x0000_0000) //
	UINT32 brightness                 :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_M23_CCO_VERI_SYS_VERI_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012224 RW
	UINT32 dce_cb_gain2 					:10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0							:6;
	UINT32 dce_cb_gain1 					:10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1							:2;
	UINT32 chroma_gain_enable				:1; //(28,NA,0x0) //enable
	UINT32 resvd2							:3;
	};
}PE_M23_CCO_VERI_SYS_VERI_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012228 RW 0x0000_0000
	UINT32 video_delay						:20;	//(19:0)	measured video delay (us resolution)
	UINT32 reserved  		                :2;		//(21:20)	
	UINT32 pic_init                         :1;		//(22)	    auto/fast pic init
	UINT32 vrr                              :1;		//(23)		vrr/gsync/freesync on/off
	UINT32 justscan  		                :1;		//(24)		justscan on/off
	UINT32 frc  			                :1;		//(25)		frn on/off
	UINT32 frame_delay	        	        :2;		//(27:26)	frame buffer delay (DE_IPC_SET_FRAME_DELAY) 
	UINT32 prew  			                :1;		//(28)		IPP pre-write on/off
	UINT32 skip_nd0  		                :1;		//(29)		skipND0 on/off
	UINT32 low_delay 		                :1;		//(30)		low delay on/off
	UINT32 dco_lock  		                :1;		//(31)		DCO lock status
	};
}PE_M23_CCO_VERI_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901222C RW 0x0000_0000
	UINT32 frate_in							:8;		//(7:0)		input frame rate
	UINT32 frate_out  		                :8;		//(15:8)	output frame rate
	UINT32 reserved  		                :16;	//(31:16)
	};
}PE_M23_CCO_VERI_SYS_VERI_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012230 RW
	UINT32 reg_sys_veri_12                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012234 RW
	UINT32 reg_sys_veri_13                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012238 RW
	UINT32 reg_sys_veri_14                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901223C RW
	UINT32 reg_sys_veri_15                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012240 RW
	UINT32 reg_sys_veri_16                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012244 RW
	UINT32 reg_sys_veri_17                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012248 RW
	UINT32 reg_sys_veri_18                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901224C RW
	UINT32 reg_sys_veri_19                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012250 RW
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012254 RW
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012258 RW
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901225C RW
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012260 RW
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012264 RW
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012268 RW
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901226C RW
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_M23_CCO_VERI_SYS_VERI_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012270 RW
	UINT32 reg_sys_veri_28                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012274 RW
	UINT32 reg_sys_veri_29                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012278 RW
	UINT32 reg_sys_veri_30                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901227C RW
	UINT32 reg_sys_veri_31                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012280 RW
	UINT32 reg_sys_veri_32                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012284 RW
	UINT32 reg_sys_veri_33                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012288 RW
	UINT32 reg_sys_veri_34                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901228C RW
	UINT32 reg_sys_veri_35                  :32;	//31:0	//
	};
}PE_M23_CCO_VERI_SYS_VERI_35_T;

typedef struct {
	PE_M23_CCO_VERI_SYS_VERI_0_T                                f20_status;	//0xC9012200
	PE_M23_CCO_VERI_SYS_VERI_1_T                                posd_wh;		//0xC9012204
	PE_M23_CCO_VERI_SYS_VERI_2_T                                posd_xy;		//0xC9012208
	PE_M23_CCO_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xC901220C
	PE_M23_CCO_VERI_SYS_VERI_4_T                                sys_veri_4;	//0xC9012210
	PE_M23_CCO_VERI_SYS_VERI_5_T                                sys_veri_5;	//0xC9012214
	PE_M23_CCO_VERI_SYS_VERI_6_T                                sys_veri_6;	//0xC9012218
	PE_M23_CCO_VERI_SYS_VERI_7_T                                sys_veri_7;	//0xC901221C
	PE_M23_CCO_VERI_SYS_VERI_8_T                                sys_veri_8;	//0xC9012220
	PE_M23_CCO_VERI_SYS_VERI_9_T                                sys_veri_9;	//0xC9012224
	PE_M23_CCO_VERI_SYS_VERI_10_T                         video_delay_sts0;	//0xC9012228
	PE_M23_CCO_VERI_SYS_VERI_11_T                         video_delay_sts1;	//0xC901222C
	PE_M23_CCO_VERI_SYS_VERI_12_T                              sys_veri_12;	//0xC9012230
	PE_M23_CCO_VERI_SYS_VERI_13_T                              sys_veri_13;	//0xC9012234
	PE_M23_CCO_VERI_SYS_VERI_14_T                              sys_veri_14;	//0xC9012238
	PE_M23_CCO_VERI_SYS_VERI_15_T                              sys_veri_15;	//0xC901223C
	PE_M23_CCO_VERI_SYS_VERI_16_T                              sys_veri_16;	//0xC9012240
	PE_M23_CCO_VERI_SYS_VERI_17_T                              sys_veri_17;	//0xC9012244
	PE_M23_CCO_VERI_SYS_VERI_18_T                              sys_veri_18;	//0xC9012248
	PE_M23_CCO_VERI_SYS_VERI_19_T                              sys_veri_19;	//0xC901224C
	PE_M23_CCO_VERI_SYS_VERI_20_T                              sys_veri_20;	//0xC9012250
	PE_M23_CCO_VERI_SYS_VERI_21_T                              sys_veri_21;	//0xC9012254
	PE_M23_CCO_VERI_SYS_VERI_22_T                              sys_veri_22;	//0xC9012258
	PE_M23_CCO_VERI_SYS_VERI_23_T                              sys_veri_23;	//0xC901225C
	PE_M23_CCO_VERI_SYS_VERI_24_T                              sys_veri_24;	//0xC9012260
	PE_M23_CCO_VERI_SYS_VERI_25_T                              sys_veri_25;	//0xC9012264
	PE_M23_CCO_VERI_SYS_VERI_26_T                              sys_veri_26;	//0xC9012268
	PE_M23_CCO_VERI_SYS_VERI_27_T                              sys_veri_27;	//0xC901226C
	PE_M23_CCO_VERI_SYS_VERI_28_T                              sys_veri_28;	//0xC9012270
	PE_M23_CCO_VERI_SYS_VERI_29_T                              sys_veri_29;	//0xC9012274
	PE_M23_CCO_VERI_SYS_VERI_30_T                              sys_veri_30;	//0xC9012278
	PE_M23_CCO_VERI_SYS_VERI_31_T                              sys_veri_31;	//0xC901227C
	PE_M23_CCO_VERI_SYS_VERI_32_T                              sys_veri_32;	//0xC9012280
	PE_M23_CCO_VERI_SYS_VERI_33_T                              sys_veri_33;	//0xC9012284
	PE_M23_CCO_VERI_SYS_VERI_34_T                              sys_veri_34;	//0xC9012288
	PE_M23_CCO_VERI_SYS_VERI_35_T                              sys_veri_35;	//0xC901228C
}PE_CCO_VERI_REG_M23_T;



#endif
