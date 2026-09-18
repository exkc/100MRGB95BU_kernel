#ifndef _PE_CCO_REG_O26A0_H_
#define _PE_CCO_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC881000 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0' : load at vdpulse	'1' : load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0' : auto load:  load when reg. write	'1' : manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O26_CC_PE1_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881004 RW 0x10E0_0780
	UINT32 width                            :14;	//(13:0,NA,0x780) //width
	UINT32 resvd0                           :2;
	UINT32 height                           :14;	//(29:16,NA,0x10E0) //height
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881008 RW 0x0100_0A01
	UINT32 tpg_position                     :1;	//(0,NA,0x1) //0 := pe1 input	1  =  pe1 output
	UINT32 reg_pe1_cg_disable               :1;	//(1,NA,0x0) //clock gating disable
	UINT32 pe1_detour                       :1;	//(2,NA,0x0) //0': pe1 pass-through	'1': pe1 detour
	UINT32 resvd0                           :5;
	UINT32 vdpulse_pos                      :12;	//(19:8,NA,0xA) //vdpulse position for register loading
	UINT32 resvd1                           :4;
	UINT32 master_en                        :1;	//(24,NA,0x1) //PE1 master enable
	UINT32 resvd2                           :7;
	};
}PE_O26_CC_PE1_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88100C RO 0x0000_0000
	UINT32 vcnt                             :14;	//(13:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(14,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(15,NA,0x0) //Vertical Active at PE1 output
	UINT32 vcnt2                            :14;	//(29:16,NA,0x0) //vertical line number
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881010 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O26_CC_PE1_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861020 RW 0x0000_0000
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
}PE_O26_CC_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861024 RW 0x0000_0000
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
}PE_O26_CC_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861028 RW 0x0000_0000
	UINT32 reg_src_info                     :5;	//4:0	//Video Source Information	 2 : default/transition period	 3 : AV NTSC	 4 : AV PAL	 5 : HDMI_SD_i/p	 6 : HDMI_576_i/p	 7 : HDMI_HD_i	 8 : HDMI_HD_p	 9 : DTV_480_i	10 : DTV_576_i	11 : DTV_576_p	12 : DTV_HD_i	13 : DTV_HD_p	14 : RF_NTSC	15 : RF_PAL	16 : RF_PAL_M	17 : COMPONENT_1080_i	18 : COMPONENT_1080_p	19 : COMPONENT_480_i	20 : COMPONENT_480_p	21 : COMPONENT_576_i	22 : COMPONENT_576_p	23 : AV_SECAM	24 : RF_SECAM	25 : AV_ NTSC_443	26 : RF_NTSC_443	27 : AV_PAL_60	28 : SCART_RGB	29 : N.A.(abnormal) input	30 : NO SIG.
	UINT32 reg_src_freeze                   :1;	//5 //src freeze toggle '0' : normal '1' : freeze
	UINT32 reg_gsr_cpc_enable               :1;	//6 //gsr cpc enable
	UINT32 resvd                            :25;
	};
}PE_O26_CC_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88102C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CC_PE1_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861030 RW 0x0000_0000
	UINT32 p_osd_addr_y                          :32;
	};
}PE_O26_CC_PE1_FSW_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861034 RW 0x0000_0000
	UINT32 p_osd_width                           :16;
	UINT32 p_osd_height							 :16;
	};
}PE_O26_CC_PE1_FSW_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861038 RW 0x0000_0000
	UINT32 p_osd_pos_x                           :16;
	UINT32 p_osd_valid							 :1;
	UINT32 resvd							 	 :15;
	};
}PE_O26_CC_PE1_FSW_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86103C RW 0x0000_0000
	UINT32 p_osd_update_cnt                       :32;
	};
}PE_O26_CC_PE1_FSW_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881050 RW 0x03C0_0000
	UINT32 tpg_enable                       :1;	//(0,NA,0x0) //TPG Enable
	UINT32 pattern_type                     :2;	//(2:1,NA,0x0) //Test Pattern Type	'00 := ColorPatch	'01 = Gradation
	UINT32 resvd0                           :1;
	UINT32 blend_alpha                      :4;	//(7:4,NA,0x0) //TPG Blend Alpha	0x0 ~ 0xF = SolidPattern ~ BypassBackgroundPicture
	UINT32 resvd1                           :8;
	UINT32 blt_size_x                       :14;	//(29:16,NA,0x3C0) //Pattern Blt Size X (1920d=>0x780)
	UINT32 resvd2                           :2;
	};
}PE_O26_CC_PE1_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881054 RW 0x10E0_0FA0
	UINT32 gradation_stride                 :7;	//(6:0,NA,0x20) //Gradation Stride
	UINT32 gradation_direction              :1;	//(7,NA,0x1) //Gradation Direction	'0 = Vertical Gradation	'1 := Horizontal Gradation
	UINT32 gradation_bar_0_en               :1;	//(8,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_1_en               :1;	//(9,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_2_en               :1;	//(10,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 gradation_bar_3_en               :1;	//(11,NA,0x1) //Gradation Bar Enable (Enable Ctrl for each Gradation Bar)
	UINT32 resvd0                           :4;
	UINT32 blt_size_y                       :14;	//(29:16,NA,0x10E0) //Pattern Blt Size Y (1080d=>0x438)
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881058 RW 0x0000_FFFF
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
}PE_O26_CC_PE1_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88105C RW 0x0000_0000
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
}PE_O26_CC_PE1_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881060 RW 0x0000_0000
	UINT32 bg_color_r                       :10;	//(9:0,NA,0x0) //outside color with RGB
	UINT32 bg_color_b                       :10;	//(19:10,NA,0x0) //
	UINT32 bg_color_g                       :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881064 WO 0x0000_0000
	UINT32 tpg_indir_addr                   :7;	//(6:0,NA,0x00) //TPG Indirect Address	0x00 ~ 0x0F = Patch Color	0x20 ~ 0x2F = Patch Start Position	0x40 ~ 0x4F = Patch End Position	0x60 ~ 0x63 = Gradation Start Color	0x64 ~ 0x67 = Gradation Step Color (signed)	0x68 ~ 0x6A = Gradation Region Size
	UINT32 resvd0                           :5;
	UINT32 tpg_indir_ai_en                  :1;	//(12,NA,0x0) //TPG Indirect Addressing Ctrl, AI Enable
	UINT32 resvd1                           :19;
	};
}PE_O26_CC_PE1_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881068 WO 0x0000_0000
	UINT32 tpg_indir_data                   :32;	//(31:0,NA,0x0) //TPG Indirect Access Data (Write Enable Triggered)	 When Addr is...	 0x00 ~ 0x0F = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x20 ~ 0x4F = (28:16):X_position, (12:0):Y_position	 0x60 ~ 0x67 = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x68 ~ 0x6A = (12:0):position
	};
}PE_O26_CC_PE1_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881070 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_0                :14;	//(13:0,NA,0x000) //apl_win_ctrl_x0 for ch0
	UINT32 resvd0                           :2;
	UINT32 apl_win_ctrl_y0_0                :14;	//(29:16,NA,0x000) //apl_win_ctrl_y0 for ch0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881074 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_0                :14;	//(13:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :2;
	UINT32 apl_win_ctrl_y1_0                :14;	//(29:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_APL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881078 RW 0x0000_0000
	UINT32 apl_position                     :2;	//(1:0,NA,0x0) //00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :2;
	UINT32 reg_apl_enable                   :1;	//(4,NA,0x0) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :3;
	UINT32 act_win_mode                     :1;	//(8,NA,0x0) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd2                           :23;
	};
}PE_O26_CC_PE1_APL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88107C RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_1                :14;	//(13:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :2;
	UINT32 apl_win_ctrl_y0_1                :14;	//(29:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_APL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881080 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_1                :14;	//(13:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :2;
	UINT32 apl_win_ctrl_y1_1                :14;	//(29:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_APL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810B4 RO 0x0000_0000
	UINT32 apl_cb                           :10;	//(9:0,NA,0x0) //APL Cb/B
	UINT32 apl_yg                           :10;	//(19:10,NA,0x0) //APL Y/G
	UINT32 apl_cr                           :10;	//(29:20,NA,0x0) //APL Cr/R
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810B8 RO 0x0000_0000
	UINT32 apl_cb_other_side                :10;	//(9:0,NA,0x0) //apl_cb(outside of apl_win)
	UINT32 apl_yg_other_side                :10;	//(19:10,NA,0x0) //apl_yg(outside of apl_win)
	UINT32 apl_cr_other_side                :10;	//(29:20,NA,0x0) //apl_cr(outside of apl_win)
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_APL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810C0 RW 0x0000_0000
	UINT32 r_2x3_coef1                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef0                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810C4 RW 0x0000_0000
	UINT32 r_2x3_coef3a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef2                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810C8 RW 0x0000_0000
	UINT32 r_2x3_coef5a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4a                     :15;	//(30:16,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810CC RW 0x0000_0000
	UINT32 r_2x3_coef7a                     :15;	//(14:0,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810D0 RW 0x0000_0000
	UINT32 r_2x3_ofst0                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_coef8a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810D4 RW 0x0000_0000
	UINT32 r_2x3_ofst2                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst1                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810D8 RW 0x0000_0000
	UINT32 r_2x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810DC RW 0x0000_0100
	UINT32 r_2x3_en                         :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_degamma_en                     :1;	//(4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_1x3_en                         :1;	//(8,NA,0x1) //
	UINT32 resvd2                           :7;
	UINT32 r_2x3_ofst5                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd3                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810E0 RW 0x0000_0000
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
}PE_O26_CC_PE1_BT20_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810E4 RW 0x0000_0000
	UINT32 r_2x3_coef3b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 reg_csc_cb_th                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_BT20_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810E8 RW 0x0000_0000
	UINT32 r_2x3_coef5b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4b                     :15;	//(30:16,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810EC RW 0x0000_0000
	UINT32 r_2x3_coef7b                     :15;	//(14:0,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810F0 RW 0x0000_0000
	UINT32 reg_csc_cr_th                    :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 r_2x3_coef8b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810F4 RW 0x12A0_7C98
	UINT32 r_1x3_coef1                      :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef0                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810F8 RW 0x7775_12A0
	UINT32 r_1x3_coef3                      :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef2                      :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8810FC RW 0x21D7_0000
	UINT32 r_1x3_coef5                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef4                      :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881100 RW 0x12A0_0000
	UINT32 r_1x3_coef7                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef6                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881104 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_1x3_coef8                      :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_BT20_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881108 RW 0x07C0_0600
	UINT32 r_1x3_ofst1                      :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst0                      :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88110C RW 0x0600_0000
	UINT32 r_1x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst2                      :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881110 RW 0x0000_0000
	UINT32 r_1x3_ofst5                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC_PE1_BT20_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881114 RW 0x0000_0000
	UINT32 reg_dither_enable                :1;	//(0,NA,0x00) //
	UINT32 resvd0                           :1;
	UINT32 reg_dither_freeze                :1;	//(2,NA,0x00) //
	UINT32 reg_dither_demo_tpg              :1;	//(3,NA,0x00) //
	UINT32 reg_bit_mode                     :2;	//(5:4,NA,0x00) //
	UINT32 reg_clock_gating_disable         :1;	//(6,NA,0x00) //
	UINT32 resvd1                           :1;
	UINT32 reg_max_delta_g                  :8;	//(15:8,NA,0x00) //
	UINT32 reg_max_delta_b                  :8;	//(23:16,NA,0x00) //
	UINT32 reg_max_delta_r                  :8;	//(31:24,NA,0x00) //
	};
}PE_O26_CC_PE1_BT20_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881118 RO 0x0000_0000
	UINT32 r_1x3_over_count_0               :16;	//(15:0,NA,0x0) //overflow count status for ch 0
	UINT32 r_1x3_under_count_0              :16;	//(31:16,NA,0x0) //underflow count status for ch 0
	};
}PE_O26_CC_PE1_BT20_CTRL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88111C RO 0x0000_0000
	UINT32 r_1x3_over_count_1               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_1              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O26_CC_PE1_BT20_CTRL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881120 RO 0x0000_0000
	UINT32 r_1x3_over_count_2               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_2              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O26_CC_PE1_BT20_CTRL_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881124 RO 0x0000_0000
	UINT32 r_1x3_over_count_3               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_3              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O26_CC_PE1_BT20_CTRL_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881140 RW 0x0000_0000
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
}PE_O26_CC_PE1_WIN2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881144 RW 0x0000_0000
	UINT32 win_w0_x0_0                      :14;	//(13:0,NA,0x000) //win_w0_x0 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w0_y0_0                      :14;	//(29:16,NA,0x000) //win_w0_y0 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881148 RW 0x0437_03BF
	UINT32 win_w0_x1_0                      :14;	//(13:0,NA,0x3BF) //win_w0_x1 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w0_y1_0                      :14;	//(29:16,NA,0x437) //win_w0_y1 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88114C RW 0x0000_0000
	UINT32 win_w1_x0_0                      :14;	//(13:0,NA,0x000) //win_w1_x0 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w1_y0_0                      :14;	//(29:16,NA,0x000) //win_w1_y0 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881150 RW 0x0437_03BF
	UINT32 win_w1_x1_0                      :14;	//(13:0,NA,0x3BF) //win_w1_x1 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w1_y1_0                      :14;	//(29:16,NA,0x437) //win_w1_y1 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881154 RW 0x0000_0000
	UINT32 win_w0_x0_1                      :14;	//(13:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win_w0_y0_1                      :14;	//(29:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881158 RW 0x0437_03BF
	UINT32 win_w0_x1_1                      :14;	//(13:0,NA,0x3BF) //win_w0_x1
	UINT32 resvd0                           :2;
	UINT32 win_w0_y1_1                      :14;	//(29:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88115C RW 0x0000_0000
	UINT32 win_w1_x0_1                      :14;	//(13:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :2;
	UINT32 win_w1_y0_1                      :14;	//(29:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881160 RW 0x0437_03BF
	UINT32 win_w1_x1_1                      :14;	//(13:0,NA,0x3BF) //win_w1_x1
	UINT32 resvd0                           :2;
	UINT32 win_w1_y1_1                      :14;	//(29:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811D0 RW 0x0000_002C
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
}PE_O26_CC_PE1_CEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811D4 RW 0xFFFF_0000
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
}PE_O26_CC_PE1_CEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811D8 RW 0x0000_8080
	UINT32 ihsv_sgain                       :8;	//(7:0,NA,0x80) //reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//(15:8,NA,0x80) //reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
}PE_O26_CC_PE1_CEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811DC RW 0x0080_8080
	UINT32 ihsv_hoffset                     :8;	//(7:0,NA,0x80) //reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//(15:8,NA,0x80) //reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//(23:16,NA,0x80) //reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
}PE_O26_CC_PE1_CEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811E0 RW 0x8080_8080
	UINT32 reg_master_gain_cr0              :8;	//(7:0,NA,0x80) //Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//(15:8,NA,0x80) //Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//(23:16,NA,0x80) //Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//(31:24,NA,0x80) //Color region 3 master gain
	};
}PE_O26_CC_PE1_CEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811E4 RW 0x8080_8080
	UINT32 reg_master_gain_cr4              :8;	//(7:0,NA,0x80) //Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//(15:8,NA,0x80) //Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//(23:16,NA,0x80) //Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//(31:24,NA,0x80) //Color region 7 master gain
	};
}PE_O26_CC_PE1_CEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811E8 RW 0x8080_8080
	UINT32 reg_master_gain_cr8              :8;	//(7:0,NA,0x80) //Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//(15:8,NA,0x80) //Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//(23:16,NA,0x80) //Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//(31:24,NA,0x80) //Color region 11 master gain
	};
}PE_O26_CC_PE1_CEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811EC RW 0x8080_8080
	UINT32 reg_master_gain_cr12             :8;	//(7:0,NA,0x80) //Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//(15:8,NA,0x80) //Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//(23:16,NA,0x80) //Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//(31:24,NA,0x80) //Color region 15 master gain
	};
}PE_O26_CC_PE1_CEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811F0 RW 0x00000000
	UINT32 reg_ai_gain_sel_0                :2;	//(1:0,NA,0x00) //
	UINT32 reg_ai_gain_sel_1                :2;	//(3:2,NA,0x00) //
	UINT32 reg_ai_gain_sel_2                :2;	//(5:4,NA,0x00) //
	UINT32 reg_ai_gain_sel_3                :2;	//(7:6,NA,0x00) //
	UINT32 reg_ai_gain_sel_4                :2;	//(9:8,NA,0x00) //
	UINT32 reg_ai_gain_sel_5                :2;	//(11:10,NA,0x00) //
	UINT32 reg_ai_gain_sel_6                :2;	//(13:12,NA,0x00) //
	UINT32 reg_ai_gain_sel_7                :2;	//(15:14,NA,0x00) //
	UINT32 reg_ai_gain_sel_8                :2;	//(17:16,NA,0x00) //
	UINT32 reg_ai_gain_sel_9                :2;	//(19:18,NA,0x00) //
	UINT32 reg_ai_gain_sel_10               :2;	//(21:20,NA,0x00) //
	UINT32 reg_ai_gain_sel_11               :2;	//(23:22,NA,0x00) //
	UINT32 reg_ai_gain_sel_12               :2;	//(25:24,NA,0x00) //
	UINT32 reg_ai_gain_sel_13               :2;	//(27:26,NA,0x00) //
	UINT32 reg_ai_gain_sel_14               :2;	//(29:28,NA,0x00) //
	UINT32 reg_ai_gain_sel_15               :2;	//(31:30,NA,0x00) //
	};
}PE_O26_CC_PE1_CEN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811F4 RW 0x00002001
	UINT32 reg_cen_tap_mode                 :1;	//(0,NA,0x1) //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_cen_repeat_en                :1;	//(4,NA,0x0) //1:repeat(interpolation off)
	UINT32 resvd1                           :3;
	UINT32 reg_oai_cen_pel_dly              :2;	//(9:8,NA,0x0) //0:0 1:+1 2:+2 3:+3
	UINT32 resvd2                           :2;
	UINT32 reg_oai_cen_obj_dly              :2;	//(13:12,NA,0x2) //0:-2 1:-1 2:0 3:+1
	UINT32 resvd3                           :2;
	UINT32 reg_oai_cen_in_sel               :1;	//(16,NA,0x0) //0:maxrgb 1:Y
	UINT32 resvd4                           :15;
	};
}PE_O26_CC_PE1_CEN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8811F8 RW/RO 0x0000_0000
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
}PE_O26_CC_PE1_CEN_UPD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881200 WO 0x0000_0000
	UINT32 hif_cen_address                  :8;	//(7:0,NA,0x00) //hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//(10:8,NA,0x0) //reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//(14,NA,0x0) //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//(15,NA,0x0) //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
}PE_O26_CC_PE1_CEN_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881204 RO 0x0000_0000
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_CEN_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881208 WO 0x0000_0000
	UINT32 hif_cen_delta_address            :5;	//(4:0,NA,0x00) //hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//(15,NA,0x0) //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
}PE_O26_CC_PE1_CEN_DELTA_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88120C RO 0x0000_0000
	UINT32 hif_cen_vr_data                  :8;	//(7:0,NA,0x000) //Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//(15:8,NA,0x000) //Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//(23:16,NA,0x000) //Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
}PE_O26_CC_PE1_CEN_DELTA_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881220 RW 0x0000_0000
	UINT32 dynamic_contrast_en              :1;	//(0,NA,0x0) //0' : disable	'1' : enable
	UINT32 hist_bin_mode                    :2;	//(2:1,NA,0x0) //00' : 32 bin mode	others : 16 bin mode
	UINT32 hist_clear                       :1;	//(3,NA,0x0) //Debugging purpose, force deleting for histogram memory.	'1' : clear
	UINT32 multiview_en                     :1;	//(4,NA,0x0) //individual hist/lut for each window
	UINT32 resvd0                           :2;
	UINT32 window_acquire                   :1;	//(7,NA,0x0) //1' : window0 size acquire (0x0038, 0x003C)	      window1 size acquire (0x0040, 0x0044)
	UINT32 window_mode_enable               :4;	//(11:8,NA,0x0) //[0] : window mode enable	[0]:window0 [1]: window1 [2]: window2 [3]: window3
	UINT32 window_enable                    :4;	//(15:12,NA,0x0) //[0] : window enable (dce_on/off)	[0]:window0 [1]: window1 [2]: window2 [3]: window3
	UINT32 window_priority0_sel             :2;	//(17:16,NA,0x0) //window priority0 selelction	0:window0 1: window1 2: window2 3: window3
	UINT32 window_priority1_sel             :2;	//(19:18,NA,0x0) //window priority1 selelction	0:window0 1: window1 2: window2 3: window3
	UINT32 window_priority2_sel             :2;	//(21:20,NA,0x0) //window priority2 selelction	0:window0 1: window1 2: window2 3: window3
	UINT32 window_priority3_sel             :2;	//(23:22,NA,0x0) //window priority3 selelction	0:window0 1: window1 2: window2 3: window3
	UINT32 resvd1                           :3;
	UINT32 window_outside_sel               :1;	//(27,NA,0x0) //0' : selected area by window0, window1		'1' : otherside
	UINT32 histogram_mode                   :2;	//(29:28,NA,0x0) //00' : Own side's histogram data use	'01' : Other side's histogram data use	'10' : Average between Own and Other side's histogram data use
	UINT32 resvd2                           :2;
	};
}PE_O26_CC_PE1_DCE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881224 RW 0x0080_001A
	UINT32 chroma_comp_color_region_gain    :8;	//(7:0,NA,0x1A) //default : "128" ( 1 ~ 255(1~400%))
	UINT32 resvd0                           :8;
	UINT32 color_region_gain                :8;	//(23:16,NA,0x80) //default : "128" ( 1 ~ 255(1~400%)) (forbidden 0 value))
	UINT32 resvd1                           :8;
	};
}PE_O26_CC_PE1_DCE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881228 RW 0x0000_0000
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
}PE_O26_CC_PE1_DCE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88122C RW 0x02D0_01E0
	UINT32 y_range_min                      :10;	//(9:0,NA,0x01E0) //default : 480
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x02D0) //default : 720
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881230 RW 0x02B4_0264
	UINT32 cb_range_min                     :10;	//(9:0,NA,0x0264) //default : 612
	UINT32 resvd0                           :6;
	UINT32 cb_range_max                     :10;	//(25:16,NA,0x02B4) //default : 692
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881234 RW 0x01FC_0134
	UINT32 cr_range_min                     :10;	//(9:0,NA,0x0134) //default : 308
	UINT32 resvd0                           :6;
	UINT32 cr_range_max                     :10;	//(25:16,NA,0x01FC) //default : 508
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881238 RW 0x0000_8000
	UINT32 hif_dyc_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dce_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dce_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dce_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 hif_dce_win_sel                  :2;	//(17:16,NA,0x0) //
	UINT32 resvd3                           :14;
	};
}PE_O26_CC_PE1_DCE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88123C RO 0x0000_0000
	UINT32 hif_dyc_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881240 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881248 RW 0x0000_8000
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
}PE_O26_CC_PE1_DCE_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88124C RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O26_CC_PE1_DCE_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881250 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_O26_CC_PE1_DCE_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881254 RW 0x0200_0200
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_O26_CC_PE1_DCE_CHR_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881258 RW 0x0200_0200
	UINT32 dce_chr_alpha2                   :10;	//(9:0,NA,0x200) //alpha(0~512), y_dce_in < y_dce_out : 0 means no gain
	UINT32 resvd0                           :6;
	UINT32 dce_chr_alpha1                   :10;	//(25:16,NA,0x200) //alpha(0~512), y_dce_in >= y_dce_out : 0 means no gain
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CHR_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88125C RW 0x0200_0200
	UINT32 dce_cr_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CHR_GAIN2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881270 RW 0x0000_0000
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
}PE_O26_CC_PE1_DSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881274 RW 0x8000_0301
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
}PE_O26_CC_PE1_DSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881278 RW 0x03FF_03FF
	UINT32 hif_dse_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88127C RW 0x0000_8000
	UINT32 hif_dse_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_O26_CC_PE1_DSE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881280 RO 0x0000_0000
	UINT32 hif_dse_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DSE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881284 RW 0x028A_0238
	UINT32 y_range_min                      :10;	//(9:0,NA,0x0238) //default : 568
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x028A) //default : 650
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881288 RW 0x0061_0026
	UINT32 h_range_min                      :10;	//(9:0,NA,0x0026) //default : 38
	UINT32 resvd0                           :6;
	UINT32 h_range_max                      :10;	//(25:16,NA,0x0061) //default : 97
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88128C RW 0x0000_3C00
	UINT32 reg_y_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt0_x               :10;	//(17:8,NA,0x3C) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881290 RW 0x0000_C88C
	UINT32 reg_y_region_pt1_y               :8;	//(7:0,NA,0x8C) //
	UINT32 reg_y_region_pt1_x               :10;	//(17:8,NA,0xC8) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881294 RW 0x0001_40FF
	UINT32 reg_y_region_pt2_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt2_x               :10;	//(17:8,NA,0x140) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881298 RW 0x0001_90FF
	UINT32 reg_y_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt3_x               :10;	//(17:8,NA,0x190) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88129C RW 0x0002_BCFF
	UINT32 reg_y_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt4_x               :10;	//(17:8,NA,0x2BC) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812A0 RW 0x0003_4878
	UINT32 reg_y_region_pt5_y               :8;	//(7:0,NA,0x78) //
	UINT32 reg_y_region_pt5_x               :10;	//(17:8,NA,0x348) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812A4 RW 0x0003_703C
	UINT32 reg_y_region_pt6_y               :8;	//(7:0,NA,0x3C) //
	UINT32 reg_y_region_pt6_x               :10;	//(17:8,NA,0x370) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812A8 RW 0x0003_9800
	UINT32 reg_y_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt7_x               :10;	//(17:8,NA,0x398) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_Y_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812AC RW 0x0001_F100
	UINT32 reg_h_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt0_x               :10;	//(17:8,NA,0x1F1) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812B0 RW 0x0002_00BE
	UINT32 reg_h_region_pt1_y               :8;	//(7:0,NA,0xBE) //
	UINT32 reg_h_region_pt1_x               :10;	//(17:8,NA,0x200) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812B4 RW 0x0002_0DF0
	UINT32 reg_h_region_pt2_y               :8;	//(7:0,NA,0xF0) //
	UINT32 reg_h_region_pt2_x               :10;	//(17:8,NA,0x20D) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812B8 RW 0x0002_14FF
	UINT32 reg_h_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt3_x               :10;	//(17:8,NA,0x214) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812BC RW 0x0002_28FF
	UINT32 reg_h_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt4_x               :10;	//(17:8,NA,0x228) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812C0 RW 0x0002_30FF
	UINT32 reg_h_region_pt5_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt5_x               :10;	//(17:8,NA,0x230) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812C4 RW 0x0002_3FA0
	UINT32 reg_h_region_pt6_y               :8;	//(7:0,NA,0xA0) //
	UINT32 reg_h_region_pt6_x               :10;	//(17:8,NA,0x23F) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8812C8 RW 0x0002_4000
	UINT32 reg_h_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt7_x               :10;	//(17:8,NA,0x240) //
	UINT32 resvd                            :14;
	};
}PE_O26_CC_PE_DSE_H_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881380 RW 0x0000_0C00
	UINT32 reg_pic_rptr_man                 :2;	//(1:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_pic_rptr_man_en              :1;	//(3,NA,0x0) //
	UINT32 reg_pic_wptr_man                 :2;	//(5:4,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_pic_wptr_man_en              :1;	//(7,NA,0x0) //
	UINT32 reg_pic_data_man                 :2;	//(9:8,NA,0x0) //0: test data off	1: 128	2: gradient	3: horizontal box
	UINT32 reg_pic_rptr_on                  :1;	//(10,NA,0x1) //
	UINT32 reg_pic_wptr_on                  :1;	//(11,NA,0x1) //
	UINT32 reg_pic_wd_man                   :4;	//(15:12,NA,0x0) //16배, {reg_pic_wd_man,4'd0}
	UINT32 reg_pic_wd_man_on                :1;	//(16,NA,0x0) //
	UINT32 reg_pic_rd_lsb_man               :2;	//(18:17,NA,0x0) //0 : [1:0] = 0	1 : [1:0] = 3	2 : [1:0] = [3:2]	3 : [1:0] = [9:8]
	UINT32 reg_ro_buf_wrcnt                 :10;	//(28:19,NA,0x0) //
	UINT32 reg_ro_buf_wrsel                 :1;	//(29,NA,0x0) //
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //Logo L7 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //Logo L7 de_clk clock gating
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881384 RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881388 RW 0x0011_001E
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x11) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88138C RW 0x0011_001E
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x11) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881390 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881394 RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881398 RW 0x0011_0078
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x78) //120=4x30
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x11) //17
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88139C RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813A0 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win01_en                         :1;	//(2:2,NA,0x0) //1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813A4 RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813A8 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813AC RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813B0 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : (1920=7680/4p)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813B4 RW 0x0010_B8B8
	UINT32 reg_logo_blend_alpha_l7_delay    :8;	//(7:0,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 55 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blend_alpha_l3_delay    :8;	//(15:8,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 55 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blned_alpha_c5_delay    :5;	//(20:16,NA,0x10) //csr_gain delay : default 16, 0(-16T)~16(0T for logo_blend_top)~31(15T)
	UINT32 resvd                            :11;
	};
}PE_O26_CC_PE1_LOGO_L7SC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813B8 RW 0x0000_0011
	UINT32 mif_r_logo_gain_line_inc         :2;	//(1:0,NA,0x01) //
	UINT32 mif_r_logo_gain_pf_flag_en       :1;	//(2:2,NA,0x00) //
	UINT32 mif_r_logo_gain_manual_en        :1;	//(3:3,NA,0x00) //
	UINT32 mif_r_logo_gain_en               :1;	//(4:4,NA,0x01) //
	UINT32 mif_r_logo_vreverse              :1;	//(5:5,NA,0x00) //
	UINT32 resvd0                           :2;
	UINT32 logo_l3sc_out_sel                :2;	//(9:8,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	UINT32 resvd1                           :6;
	UINT32 mif_r_logo_gain_voffset          :9;	//(24:16,NA,0x0) //MRD V offset
	UINT32 resvd2                           :5;
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //Logo L3 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //Logo L3 de_clk clock gating
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813BC RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813C0 RW 0x010E_01E0
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x10E) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813C4 RW 0x010E_01E0
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E0) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x10E) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813C8 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813CC RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813D0 RW 0x010E_0780
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x780) //1920=480x4
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x10E) //270
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813D4 RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813D8 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win01_en                         :1;	//(2:2,NA,0x0) //1:  select only window01 as active area
	UINT32 resvd                            :3;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813DC RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813E0 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813E4 RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813E8 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : 1920(7680/4)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O26_CC_PE1_LOGO_L3SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813EC RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O26_CC_PE1_LOGO_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813F0 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CC_PE1_LOGO_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813F4 RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O26_CC_PE1_LOGO_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8813F8 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CC_PE1_LOGO_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881410 RW 0x0000_0000
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
}PE_O26_CC_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}PE_O26_CC_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_CC_PE1_PCC_COEF7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881434 RW 0x0000_0000
	UINT32 oetf_addr                        :11;	//(10:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 oetf_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O26_CC_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881438 RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :12;	//(11:0,NA,0x0) //12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//(27:16,NA,0x0) //12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}PE_O26_CC_PE1_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88143C RW 0x0000_0000
	UINT32 eotf_wdata                       :15;	//(14:0,RW,0x0) //lut write data
	UINT32 resvd0                           :1;
	UINT32 eotf_waddr                       :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd1                           :2;
	UINT32 eotf_we                          :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}PE_O26_CC_PE1_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881440 RW/RO 0x0000_0000
	UINT32 eotf_wend                        :1;	//(0,RW,0x00) //eotf lut wdone flag for cpy protection
	UINT32 resvd0                           :3;
	UINT32 eotf_wstart                      :1;	//(4,RW,0x00) //eotf lut wstart flag for cpy protection
	UINT32 resvd1                           :15;
	UINT32 eotf_lut_direct_mode             :1;	//(20,RW,0x00) //lut direct access
	UINT32 resvd2                           :3;
	UINT32 eotf_lut_cpy_trig                :2;	//(25:24,RW,0x00) //lut update trigger sel
	UINT32 resvd3                           :2;
	UINT32 eotf_lut_update                  :1;	//(28,RW,0x00) //eotf lut update
	UINT32 resvd4                           :3;
	};
}PE_O26_CC_PE1_EOTF_WDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881444 RW/RO 0x0000_0000
	UINT32 eotf_rdata                       :15;	//(14:0,RO,0x0) //lut read data
	UINT32 resvd0                           :1;
	UINT32 eotf_raddr                       :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 eotf_re                          :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 eotf_rdata_sel                   :1;	//(31,RW,0x0) //lut read data sel 0:even, 1:odd
	};
}PE_O26_CC_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881448 RO 0x0000_0000
	UINT32 eotf_buf_rw_conflict             :1;	//(0,RO,0x00) //
	UINT32 eotf_lut_cpy_done                :1;	//(1,RO,0x00) //
	UINT32 eotf_lut_cpy_status              :2;	//(3:2,RO,0x0) //
	UINT32 resvd                            :28;
	};
}PE_O26_CC_PE1_EOTF_RSATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881450 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O26_CC_PE1_LLLUT_E_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881454 RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_LLLUT_E_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881458 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O26_CC_PE1_LLLUT_O_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88145C RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O26_CC_PE1_LLLUT_O_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881460 RW 0x0000_0100
	UINT32 reg_llctrl_enable                :1;	//(0,NA,0x0) //low level control enable
	UINT32 reg_llpcc_en                     :1;	//(1,NA,0x0) //PCC for low level control Enable
	UINT32 reg_llab_inp_sel                 :1;	//(2,NA,0x0) //low level alpha input sel 0:RGB2Y output, 1:max(RGB)
	UINT32 resvd0                           :5;
	UINT32 reg_hue_prsv_en                  :1;	//(8,NA,0x1) //hue preserving enable for low level alpha blending
	UINT32 reg_sat_prsv_en                  :1;	//(9,NA,0x0) //saturatione preserving enable for low level alpha blending
	UINT32 reg_hsp_en                       :1;	//(10,NA,0x0) //hue and saturatione preserving enable for low level alpha blending
	UINT32 resvd1                           :1;
	UINT32 reg_hue_prsv_cg_disable          :1;	//(12,NA,0x0) //clock gating disable
	UINT32 resvd2                           :19;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881464 RW 0x0000_1000
	UINT32 reg_llpcc_coef0                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef1                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881468 RW 0x0000_0000
	UINT32 reg_llpcc_coef2                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef3                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88146C RW 0x0000_0000
	UINT32 reg_llpcc_coef4                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef5                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881470 RW 0x0000_0000
	UINT32 reg_llpcc_coef6                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef7                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881474 RW 0x0AD9_1000
	UINT32 reg_llpcc_coef8                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 8
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(30:16,NA,0x0AD9) //alpha blendling RGB -> Y coef0
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881478 RW 0x0434_00F3
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(14:0,NA,0x00F3) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(30:16,NA,0x0434) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88147C RW 0x0000_0000
	UINT32 reg_llab_lut_y0                  :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x0                  :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881480 RW 0x0009_0009
	UINT32 reg_llab_lut_y1                  :10;	//(9:0,NA,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x1                  :10;	//(25:16,NA,0x9) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881484 RW 0x000A_0200
	UINT32 reg_llab_lut_y2                  :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x2                  :10;	//(25:16,NA,0xA) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881488 RW 0x000B_03FF
	UINT32 reg_llab_lut_y3                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x3                  :10;	//(25:16,NA,0xB) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88148C RW 0x03FF_03FF
	UINT32 reg_llab_lut_y4                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x4                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881490 RW 0x03FF_03FF
	UINT32 reg_llab_lut_y5                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x5                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881494 RW 0x0000_00FF
	UINT32 reg_hue_prsv_ratio               :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O26_CC_PE1_LLCORE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814A0 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #1
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #1
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814A4 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #2
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #2
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814A8 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #3
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #3
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_DCE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814AC RW 0x0000EE44
	UINT32 c0_hist0_win_sel                 :2;	//(1:0,NA,0x0) //
	UINT32 c0_hist1_win_sel                 :2;	//(3:2,NA,0x1) //
	UINT32 c1_hist0_win_sel                 :2;	//(5:4,NA,0x0) //
	UINT32 c1_hist1_win_sel                 :2;	//(7:6,NA,0x1) //
	UINT32 c2_hist0_win_sel                 :2;	//(9:8,NA,0x2) //
	UINT32 c2_hist1_win_sel                 :2;	//(11:10,NA,0x3) //
	UINT32 c3_hist0_win_sel                 :2;	//(13:12,NA,0x2) //
	UINT32 c3_hist1_win_sel                 :2;	//(15:14,NA,0x3) //
	UINT32 reg_4ch_merge                    :1;	//(16,NA,0x0) //8k 2 window
	UINT32 reg_c12_inp_swap                 :1;	//(17,NA,0x0) //8k 4 window
	UINT32 resvd0                           :2;
	UINT32 reg_2ch_merge_disable            :1;	//(20,NA,0x0) //1p mode
	UINT32 resvd1                           :3;
	UINT32 reg_4k_win_hist                  :1;	//(24,NA,0x0) //4K 4 window
	UINT32 resvd2                           :7;
	};
}PE_O26_CC_PE1_HIST_WIN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814B0 RW 0x0000_8000
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
}PE_O26_CC_PE1_DCE_HIST1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814B4 RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O26_CC_PE1_DCE_HIST1_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814B8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CC_PE1_DCE_HIST1_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814BC RW 0x0000_8000
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
}PE_O26_CC_PE1_DCE_HIST2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814C0 RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O26_CC_PE1_DCE_HIST2_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814C4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CC_PE1_DCE_HIST2_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814C8 RW 0x0000_8000
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
}PE_O26_CC_PE1_DCE_HIST3_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814CC RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O26_CC_PE1_DCE_HIST3_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814D0 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_O26_CC_PE1_DCE_HIST3_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814E0 RW 0x0000_0000
	UINT32 win_w2_x0_0                      :14;	//(13:0,NA,0x000) //win_w2_x0 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w2_y0_0                      :14;	//(29:16,NA,0x000) //win_w2_y0 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814E4 RW 0x0437_03BF
	UINT32 win_w2_x1_0                      :14;	//(13:0,NA,0x3BF) //win_w2_x1 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w2_y1_0                      :14;	//(29:16,NA,0x437) //win_w2_y1 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814E8 RW 0x0000_0000
	UINT32 win_w3_x0_0                      :14;	//(13:0,NA,0x000) //win_w3_x0 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w3_y0_0                      :14;	//(29:16,NA,0x000) //win_w3_y0 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814EC RW 0x0437_03BF
	UINT32 win_w3_x1_0                      :14;	//(13:0,NA,0x3BF) //win_w3_x1 for ch 0
	UINT32 resvd0                           :2;
	UINT32 win_w3_y1_0                      :14;	//(29:16,NA,0x437) //win_w3_y1 for ch 0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814F0 RW 0x0000_0000
	UINT32 win_w2_x0_1                      :14;	//(13:0,NA,0x000) //win_w2_x0 for ch 1
	UINT32 resvd0                           :2;
	UINT32 win_w2_y0_1                      :14;	//(29:16,NA,0x000) //win_w2_y0 for ch 1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814F4 RW 0x0437_03BF
	UINT32 win_w2_x1_1                      :14;	//(13:0,NA,0x3BF) //win_w2_x1 for ch 1
	UINT32 resvd0                           :2;
	UINT32 win_w2_y1_1                      :14;	//(29:16,NA,0x437) //win_w2_y1 for ch 1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814F8 RW 0x0000_0000
	UINT32 win_w3_x0_1                      :14;	//(13:0,NA,0x000) //win_w3_x0 for ch 1
	UINT32 resvd0                           :2;
	UINT32 win_w3_y0_1                      :14;	//(29:16,NA,0x000) //win_w3_y0 for ch 1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8814FC RW 0x0437_03BF
	UINT32 win_w3_x1_1                      :14;	//(13:0,NA,0x3BF) //win_w3_x1 for ch 1
	UINT32 resvd0                           :2;
	UINT32 win_w3_y1_1                      :14;	//(29:16,NA,0x437) //win_w3_y1 for ch 1
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PE1_WIN2_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881500 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2:2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3:3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PCC_WINCTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881504 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2:2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3:3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PCC_WINCTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881508 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2:2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3:3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PCC_WINCTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88150C RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0:0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1:1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2:2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3:3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6:6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7:7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CC_PCC_WINCTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881510 RW 0x0000_0000
	UINT32 win0_w0_x0                       :14;	//(13:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y0                       :14;	//(29:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881514 RW 0x0000_0000
	UINT32 win0_w0_x1                       :14;	//(13:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y1                       :14;	//(29:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881518 RW 0x0000_0000
	UINT32 win1_w0_x0                       :14;	//(13:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y0                       :14;	//(29:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88151C RW 0x0000_0000
	UINT32 win1_w0_x1                       :14;	//(13:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y1                       :14;	//(29:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881520 RW 0x0000_0000
	UINT32 win2_w0_x0                       :14;	//(13:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y0                       :14;	//(29:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881524 RW 0x0000_0000
	UINT32 win2_w0_x1                       :14;	//(13:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y1                       :14;	//(29:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881528 RW 0x0000_0000
	UINT32 win3_w0_x0                       :14;	//(13:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y0                       :14;	//(29:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88152C RW 0x0000_0000
	UINT32 win3_w0_x1                       :14;	//(13:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y1                       :14;	//(29:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881530 RW 0x0000_0000
	UINT32 win0_w0_x0                       :14;	//(13:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y0                       :14;	//(29:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881534 RW 0x0000_0000
	UINT32 win0_w0_x1                       :14;	//(13:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y1                       :14;	//(29:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881538 RW 0x0000_0000
	UINT32 win1_w0_x0                       :14;	//(13:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y0                       :14;	//(29:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88153C RW 0x0000_0000
	UINT32 win1_w0_x1                       :14;	//(13:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y1                       :14;	//(29:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881540 RW 0x0000_0000
	UINT32 win2_w0_x0                       :14;	//(13:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y0                       :14;	//(29:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881544 RW 0x0000_0000
	UINT32 win2_w0_x1                       :14;	//(13:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y1                       :14;	//(29:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881548 RW 0x0000_0000
	UINT32 win3_w0_x0                       :14;	//(13:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y0                       :14;	//(29:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88154C RW 0x0000_0000
	UINT32 win3_w0_x1                       :14;	//(13:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y1                       :14;	//(29:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}PE_O26_CC_PCC_WINCTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881550 RW 0x0000_00E4
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest):win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}PE_O26_CC_PCC_WINCTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881554 RW 0x0000_0000
	UINT32 reg_ppcc_en                      :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_satu_lut_in_sel              :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :11;
	UINT32 reg_sat_gain                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd2                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881558 RW 0x0000_0000
	UINT32 reg_hsp_en                       :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sat_prsv_en                  :1;	//(4,RW,0x0) //
	UINT32 reg_hue_prsv_en                  :1;	//(5,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :8;	//(15:8,RW,0x0) //
	UINT32 reg_hue_prsv_ratio               :8;	//(23:16,RW,0x0) //
	UINT32 reg_hue_prsv_cg_disable          :1;	//(24,RW,0x0) //
	UINT32 resvd2                           :7;
	};
}PE_O26_CC_PE1_PPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88155C RW 0x0000_0000
	UINT32 reg_luma0_lut_x1_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_luma0_lut_x0_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881560 RW 0x0000_0000
	UINT32 reg_luma0_lut_x3_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_luma0_lut_x2_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881564 RW 0x0000_0000
	UINT32 reg_luma0_lut_y1_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_luma0_lut_y0_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881568 RW 0x0000_0000
	UINT32 reg_luma0_lut_y3_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_luma0_lut_y2_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88156C RW 0x0000_0000
	UINT32 reg_satu0_lut_x1_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_satu0_lut_x0_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881570 RW 0x0000_0000
	UINT32 reg_satu0_lut_x3_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_satu0_lut_x2_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881574 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_satu0_lut_x4_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881578 RW 0x0000_0000
	UINT32 reg_satu0_lut_y1_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_satu0_lut_y0_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88157C RW 0x0000_0000
	UINT32 reg_satu0_lut_y3_i               :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_satu0_lut_y2_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881580 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_satu0_lut_y4_i               :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC_PE1_PPCC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815B0 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815B4 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815B8 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815BC RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815C0 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //
	UINT32 sync_i_h_sel                     :1;	//(16,RW,0x0) //
	UINT32 sync_i_v_sel                     :1;	//(17,RW,0x0) //
	UINT32 sync_i_inv_ha                    :1;	//(18,RW,0x0) //
	UINT32 sync_i_inv_va                    :1;	//(19,RW,0x0) //
	UINT32 sync_o_sel_ha                    :1;	//(20,RW,0x0) //
	UINT32 sync_o_sel_va                    :1;	//(21,RW,0x0) //
	UINT32 sync_o_sel_hs                    :1;	//(22,RW,0x0) //
	UINT32 sync_o_sel_vs                    :1;	//(23,RW,0x0) //
	UINT32 tp_update_hv_zero                :1;	//(24,RW,0x0) //
	UINT32 force_out_ha                     :1;	//(25,RW,0x0) //
	UINT32 force_out_va                     :1;	//(26,RW,0x0) //
	UINT32 force_out_hs                     :1;	//(27,RW,0x0) //
	UINT32 manual_cnt_h_value_en            :1;	//(28,RW,0x0) //
	UINT32 manual_cnt_v_value_en            :1;	//(29,RW,0x0) //
	UINT32 force_out_vs                     :1;	//(30,RW,0x0) //
	UINT32 update_force                     :1;	//(31,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815C4 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815C8 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815CC RW 0x0002_8127
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x127) //
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815D0 RW 0x0002_8127
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x127) //
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815D4 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O26_CC_PE1_SYNC_DLY_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8815D8 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC_PE1_SYNC_DLY_10_T;

typedef struct {
	PE_O26_CC_PE1_TOP_CTRL_00_T                            pe1_top_ctrl_00;	//0xCC881000
	PE_O26_CC_PE1_TOP_CTRL_01_T                            pe1_top_ctrl_01;	//0xCC881004
	PE_O26_CC_PE1_TOP_CTRL_02_T                            pe1_top_ctrl_02;	//0xCC881008
	PE_O26_CC_PE1_TOP_CTRL_03_T                            pe1_top_ctrl_03;	//0xCC88100C
	PE_O26_CC_PE1_TOP_CTRL_04_T                            pe1_top_ctrl_04;	//0xCC881010
	UINT32                                                       reserved0;	//0xCC881014
	UINT32                                                       reserved1;	//0xCC881018
	UINT32                                                       reserved2;	//0xCC88101C
	PE_O26_CC_PE1_FSW_CTRL_00_T                            pe1_fsw_ctrl_00;	//0xCC881020
	PE_O26_CC_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xCC881024
	PE_O26_CC_PE1_FSW_CTRL_02_T                            pe1_fsw_ctrl_02;	//0xCC881028
	PE_O26_CC_PE1_FSW_CTRL_03_T                            pe1_fsw_ctrl_03;	//0xCC88102C
	PE_O26_CC_PE1_FSW_CTRL_04_T                            pe1_fsw_ctrl_04;	//0xCC881030
	PE_O26_CC_PE1_FSW_CTRL_05_T                            pe1_fsw_ctrl_05;	//0xCC881034
	PE_O26_CC_PE1_FSW_CTRL_06_T                            pe1_fsw_ctrl_06;	//0xCC881038
	PE_O26_CC_PE1_FSW_CTRL_07_T                            pe1_fsw_ctrl_07;	//0xCC88103C
	UINT32                                                       reserved3;	//0xCC881040
	UINT32                                                       reserved4;	//0xCC881044
	UINT32                                                       reserved5;	//0xCC881048
	UINT32                                                       reserved6;	//0xCC88104C
	PE_O26_CC_PE1_TPG_CTRL_00_T                            pe1_tpg_ctrl_00;	//0xCC881050
	PE_O26_CC_PE1_TPG_CTRL_01_T                            pe1_tpg_ctrl_01;	//0xCC881054
	PE_O26_CC_PE1_TPG_CTRL_02_T                            pe1_tpg_ctrl_02;	//0xCC881058
	PE_O26_CC_PE1_TPG_CTRL_03_T                            pe1_tpg_ctrl_03;	//0xCC88105C
	PE_O26_CC_PE1_TPG_CTRL_04_T                            pe1_tpg_ctrl_04;	//0xCC881060
	PE_O26_CC_PE1_TPG_IA_CTRL_T                            pe1_tpg_ia_ctrl;	//0xCC881064
	PE_O26_CC_PE1_TPG_IA_DATA_T                            pe1_tpg_ia_data;	//0xCC881068
	UINT32                                                       reserved7;	//0xCC88106C
	PE_O26_CC_PE1_APL_CTRL_00_T                            pe1_apl_ctrl_00;	//0xCC881070
	PE_O26_CC_PE1_APL_CTRL_01_T                            pe1_apl_ctrl_01;	//0xCC881074
	PE_O26_CC_PE1_APL_CTRL_02_T                            pe1_apl_ctrl_02;	//0xCC881078
	PE_O26_CC_PE1_APL_CTRL_03_T                            pe1_apl_ctrl_03;	//0xCC88107C
	PE_O26_CC_PE1_APL_CTRL_04_T                            pe1_apl_ctrl_04;	//0xCC881080
	UINT32                                                       reserved8;	//0xCC881084
	UINT32                                                       reserved9;	//0xCC881088
	UINT32                                                      reserved10;	//0xCC88108C
	UINT32                                                      reserved11;	//0xCC881090
	UINT32                                                      reserved12;	//0xCC881094
	UINT32                                                      reserved13;	//0xCC881098
	UINT32                                                      reserved14;	//0xCC88109C
	UINT32                                                      reserved15;	//0xCC8810A0
	UINT32                                                      reserved16;	//0xCC8810A4
	UINT32                                                      reserved17;	//0xCC8810A8
	UINT32                                                      reserved18;	//0xCC8810AC
	UINT32                                                      reserved19;	//0xCC8810B0
	PE_O26_CC_PE1_APL_STAT_00_T                            pe1_apl_stat_00;	//0xCC8810B4
	PE_O26_CC_PE1_APL_STAT_01_T                            pe1_apl_stat_01;	//0xCC8810B8
	UINT32                                                      reserved20;	//0xCC8810BC
	PE_O26_CC_PE1_BT20_CTRL_00_T                          pe1_bt20_ctrl_00;	//0xCC8810C0
	PE_O26_CC_PE1_BT20_CTRL_01_T                          pe1_bt20_ctrl_01;	//0xCC8810C4
	PE_O26_CC_PE1_BT20_CTRL_02_T                          pe1_bt20_ctrl_02;	//0xCC8810C8
	PE_O26_CC_PE1_BT20_CTRL_03_T                          pe1_bt20_ctrl_03;	//0xCC8810CC
	PE_O26_CC_PE1_BT20_CTRL_04_T                          pe1_bt20_ctrl_04;	//0xCC8810D0
	PE_O26_CC_PE1_BT20_CTRL_05_T                          pe1_bt20_ctrl_05;	//0xCC8810D4
	PE_O26_CC_PE1_BT20_CTRL_06_T                          pe1_bt20_ctrl_06;	//0xCC8810D8
	PE_O26_CC_PE1_BT20_CTRL_07_T                          pe1_bt20_ctrl_07;	//0xCC8810DC
	PE_O26_CC_PE1_BT20_CTRL_08_T                          pe1_bt20_ctrl_08;	//0xCC8810E0
	PE_O26_CC_PE1_BT20_CTRL_09_T                          pe1_bt20_ctrl_09;	//0xCC8810E4
	PE_O26_CC_PE1_BT20_CTRL_10_T                          pe1_bt20_ctrl_10;	//0xCC8810E8
	PE_O26_CC_PE1_BT20_CTRL_11_T                          pe1_bt20_ctrl_11;	//0xCC8810EC
	PE_O26_CC_PE1_BT20_CTRL_12_T                          pe1_bt20_ctrl_12;	//0xCC8810F0
	PE_O26_CC_PE1_BT20_CTRL_13_T                          pe1_bt20_ctrl_13;	//0xCC8810F4
	PE_O26_CC_PE1_BT20_CTRL_14_T                          pe1_bt20_ctrl_14;	//0xCC8810F8
	PE_O26_CC_PE1_BT20_CTRL_15_T                          pe1_bt20_ctrl_15;	//0xCC8810FC
	PE_O26_CC_PE1_BT20_CTRL_16_T                          pe1_bt20_ctrl_16;	//0xCC881100
	PE_O26_CC_PE1_BT20_CTRL_17_T                          pe1_bt20_ctrl_17;	//0xCC881104
	PE_O26_CC_PE1_BT20_CTRL_18_T                          pe1_bt20_ctrl_18;	//0xCC881108
	PE_O26_CC_PE1_BT20_CTRL_19_T                          pe1_bt20_ctrl_19;	//0xCC88110C
	PE_O26_CC_PE1_BT20_CTRL_20_T                          pe1_bt20_ctrl_20;	//0xCC881110
	PE_O26_CC_PE1_BT20_CTRL_21_T                          pe1_bt20_ctrl_21;	//0xCC881114
	PE_O26_CC_PE1_BT20_CTRL_STAT_00_T                pe1_bt20_ctrl_stat_00;	//0xCC881118
	PE_O26_CC_PE1_BT20_CTRL_STAT_01_T                pe1_bt20_ctrl_stat_01;	//0xCC88111C
	PE_O26_CC_PE1_BT20_CTRL_STAT_02_T                pe1_bt20_ctrl_stat_02;	//0xCC881120
	PE_O26_CC_PE1_BT20_CTRL_STAT_03_T                pe1_bt20_ctrl_stat_03;	//0xCC881124
	UINT32                                                      reserved21;	//0xCC881128
	UINT32                                                      reserved22;	//0xCC88112C
	UINT32                                                      reserved23;	//0xCC881130
	UINT32                                                      reserved24;	//0xCC881134
	UINT32                                                      reserved25;	//0xCC881138
	UINT32                                                      reserved26;	//0xCC88113C
	PE_O26_CC_PE1_WIN2_CTRL_00_T                          pe1_win2_ctrl_00;	//0xCC881140
	PE_O26_CC_PE1_WIN2_CTRL_01_T                          pe1_win2_ctrl_01;	//0xCC881144
	PE_O26_CC_PE1_WIN2_CTRL_02_T                          pe1_win2_ctrl_02;	//0xCC881148
	PE_O26_CC_PE1_WIN2_CTRL_03_T                          pe1_win2_ctrl_03;	//0xCC88114C
	PE_O26_CC_PE1_WIN2_CTRL_04_T                          pe1_win2_ctrl_04;	//0xCC881150
	PE_O26_CC_PE1_WIN2_CTRL_05_T                          pe1_win2_ctrl_05;	//0xCC881154
	PE_O26_CC_PE1_WIN2_CTRL_06_T                          pe1_win2_ctrl_06;	//0xCC881158
	PE_O26_CC_PE1_WIN2_CTRL_07_T                          pe1_win2_ctrl_07;	//0xCC88115C
	PE_O26_CC_PE1_WIN2_CTRL_08_T                          pe1_win2_ctrl_08;	//0xCC881160
	UINT32                                                      reserved27;	//0xCC881164
	UINT32                                                      reserved28;	//0xCC881168
	UINT32                                                      reserved29;	//0xCC88116C
	UINT32                                                      reserved30;	//0xCC881170
	UINT32                                                      reserved31;	//0xCC881174
	UINT32                                                      reserved32;	//0xCC881178
	UINT32                                                      reserved33;	//0xCC88117C
	UINT32                                                      reserved34;	//0xCC881180
	UINT32                                                      reserved35;	//0xCC881184
	UINT32                                                      reserved36;	//0xCC881188
	UINT32                                                      reserved37;	//0xCC88118C
	UINT32                                                      reserved38;	//0xCC881190
	UINT32                                                      reserved39;	//0xCC881194
	UINT32                                                      reserved40;	//0xCC881198
	UINT32                                                      reserved41;	//0xCC88119C
	UINT32                                                      reserved42;	//0xCC8811A0
	UINT32                                                      reserved43;	//0xCC8811A4
	UINT32                                                      reserved44;	//0xCC8811A8
	UINT32                                                      reserved45;	//0xCC8811AC
	UINT32                                                      reserved46;	//0xCC8811B0
	UINT32                                                      reserved47;	//0xCC8811B4
	UINT32                                                      reserved48;	//0xCC8811B8
	UINT32                                                      reserved49;	//0xCC8811BC
	UINT32                                                      reserved50;	//0xCC8811C0
	UINT32                                                      reserved51;	//0xCC8811C4
	UINT32                                                      reserved52;	//0xCC8811C8
	UINT32                                                      reserved53;	//0xCC8811CC
	PE_O26_CC_PE1_CEN_CTRL_00_T                            pe1_cen_ctrl_00;	//0xCC8811D0
	PE_O26_CC_PE1_CEN_CTRL_01_T                            pe1_cen_ctrl_01;	//0xCC8811D4
	PE_O26_CC_PE1_CEN_CTRL_02_T                            pe1_cen_ctrl_02;	//0xCC8811D8
	PE_O26_CC_PE1_CEN_CTRL_03_T                            pe1_cen_ctrl_03;	//0xCC8811DC
	PE_O26_CC_PE1_CEN_CTRL_04_T                            pe1_cen_ctrl_04;	//0xCC8811E0
	PE_O26_CC_PE1_CEN_CTRL_05_T                            pe1_cen_ctrl_05;	//0xCC8811E4
	PE_O26_CC_PE1_CEN_CTRL_06_T                            pe1_cen_ctrl_06;	//0xCC8811E8
	PE_O26_CC_PE1_CEN_CTRL_07_T                            pe1_cen_ctrl_07;	//0xCC8811EC
	PE_O26_CC_PE1_CEN_CTRL_08_T                            pe1_cen_ctrl_08;	//0xCC8811F0
	PE_O26_CC_PE1_CEN_CTRL_09_T                            pe1_cen_ctrl_09;	//0xCC8811F4
	PE_O26_CC_PE1_CEN_UPD_CTRL_T                          pe1_cen_upd_ctrl;	//0xCC8811F8
	UINT32                                                      reserved54;	//0xCC8811FC
	PE_O26_CC_PE1_CEN_IA_CTRL_T                            pe1_cen_ia_ctrl;	//0xCC881200
	PE_O26_CC_PE1_CEN_IA_DATA_T                            pe1_cen_ia_data;	//0xCC881204
	PE_O26_CC_PE1_CEN_DELTA_IA_CTRL_T                pe1_cen_delta_ia_ctrl;	//0xCC881208
	PE_O26_CC_PE1_CEN_DELTA_IA_DATA_T                pe1_cen_delta_ia_data;	//0xCC88120C
	UINT32                                                      reserved55;	//0xCC881210
	UINT32                                                      reserved56;	//0xCC881214
	UINT32                                                      reserved57;	//0xCC881218
	UINT32                                                      reserved58;	//0xCC88121C
	PE_O26_CC_PE1_DCE_CTRL_00_T                            pe1_dce_ctrl_00;	//0xCC881220
	PE_O26_CC_PE1_DCE_CTRL_01_T                            pe1_dce_ctrl_01;	//0xCC881224
	PE_O26_CC_PE1_DCE_CTRL_02_T                            pe1_dce_ctrl_02;	//0xCC881228
	PE_O26_CC_PE1_DCE_CTRL_03_T                            pe1_dce_ctrl_03;	//0xCC88122C
	PE_O26_CC_PE1_DCE_CTRL_04_T                            pe1_dce_ctrl_04;	//0xCC881230
	PE_O26_CC_PE1_DCE_CTRL_05_T                            pe1_dce_ctrl_05;	//0xCC881234
	PE_O26_CC_PE1_DCE_IA_CTRL_T                            pe1_dce_ia_ctrl;	//0xCC881238
	PE_O26_CC_PE1_DCE_IA_DATA_T                            pe1_dce_ia_data;	//0xCC88123C
	PE_O26_CC_PE1_DCE_CTRL_08_T                            pe1_dce_ctrl_08;	//0xCC881240
	UINT32                                                      reserved59;	//0xCC881244
	PE_O26_CC_PE1_DCE_HIST_IA_CTRL_T                  pe1_dce_hist_ia_ctrl;	//0xCC881248
	PE_O26_CC_PE1_DCE_HIST_IA_DATA1_T                pe1_dce_hist_ia_data1;	//0xCC88124C
	PE_O26_CC_PE1_DCE_HIST_IA_DATA2_T                pe1_dce_hist_ia_data2;	//0xCC881250
	PE_O26_CC_PE1_DCE_CHR_GAIN_T                          pe1_dce_chr_gain;	//0xCC881254
	PE_O26_CC_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0xCC881258
	PE_O26_CC_PE1_DCE_CHR_GAIN2_T                        pe1_dce_chr_gain2;	//0xCC88125C
	UINT32                                                      reserved60;	//0xCC881260
	UINT32                                                      reserved61;	//0xCC881264
	UINT32                                                      reserved62;	//0xCC881268
	UINT32                                                      reserved63;	//0xCC88126C
	PE_O26_CC_PE1_DSE_CTRL_00_T                            pe1_dse_ctrl_00;	//0xCC881270
	PE_O26_CC_PE1_DSE_CTRL_01_T                            pe1_dse_ctrl_01;	//0xCC881274
	PE_O26_CC_PE1_DSE_CTRL_02_T                            pe1_dse_ctrl_02;	//0xCC881278
	PE_O26_CC_PE1_DSE_IA_CTRL_T                            pe1_dse_ia_ctrl;	//0xCC88127C
	PE_O26_CC_PE1_DSE_IA_DATA_T                            pe1_dse_ia_data;	//0xCC881280
	PE_O26_CC_PE1_DSE_CTRL_03_T                            pe1_dse_ctrl_03;	//0xCC881284
	PE_O26_CC_PE1_DSE_CTRL_04_T                            pe1_dse_ctrl_04;	//0xCC881288
	PE_O26_CC_PE_DSE_Y_REGION_PT0_T                    pe_dse_y_region_pt0;	//0xCC88128C
	PE_O26_CC_PE_DSE_Y_REGION_PT1_T                    pe_dse_y_region_pt1;	//0xCC881290
	PE_O26_CC_PE_DSE_Y_REGION_PT2_T                    pe_dse_y_region_pt2;	//0xCC881294
	PE_O26_CC_PE_DSE_Y_REGION_PT3_T                    pe_dse_y_region_pt3;	//0xCC881298
	PE_O26_CC_PE_DSE_Y_REGION_PT4_T                    pe_dse_y_region_pt4;	//0xCC88129C
	PE_O26_CC_PE_DSE_Y_REGION_PT5_T                    pe_dse_y_region_pt5;	//0xCC8812A0
	PE_O26_CC_PE_DSE_Y_REGION_PT6_T                    pe_dse_y_region_pt6;	//0xCC8812A4
	PE_O26_CC_PE_DSE_Y_REGION_PT7_T                    pe_dse_y_region_pt7;	//0xCC8812A8
	PE_O26_CC_PE_DSE_H_REGION_PT0_T                    pe_dse_h_region_pt0;	//0xCC8812AC
	PE_O26_CC_PE_DSE_H_REGION_PT1_T                    pe_dse_h_region_pt1;	//0xCC8812B0
	PE_O26_CC_PE_DSE_H_REGION_PT2_T                    pe_dse_h_region_pt2;	//0xCC8812B4
	PE_O26_CC_PE_DSE_H_REGION_PT3_T                    pe_dse_h_region_pt3;	//0xCC8812B8
	PE_O26_CC_PE_DSE_H_REGION_PT4_T                    pe_dse_h_region_pt4;	//0xCC8812BC
	PE_O26_CC_PE_DSE_H_REGION_PT5_T                    pe_dse_h_region_pt5;	//0xCC8812C0
	PE_O26_CC_PE_DSE_H_REGION_PT6_T                    pe_dse_h_region_pt6;	//0xCC8812C4
	PE_O26_CC_PE_DSE_H_REGION_PT7_T                    pe_dse_h_region_pt7;	//0xCC8812C8
	UINT32                                                      reserved64;	//0xCC8812CC
	UINT32                                                      reserved65;	//0xCC8812D0
	UINT32                                                      reserved66;	//0xCC8812D4
	UINT32                                                      reserved67;	//0xCC8812D8
	UINT32                                                      reserved68;	//0xCC8812DC
	UINT32                                                      reserved69;	//0xCC8812E0
	UINT32                                                      reserved70;	//0xCC8812E4
	UINT32                                                      reserved71;	//0xCC8812E8
	UINT32                                                      reserved72;	//0xCC8812EC
	UINT32                                                      reserved73;	//0xCC8812F0
	UINT32                                                      reserved74;	//0xCC8812F4
	UINT32                                                      reserved75;	//0xCC8812F8
	UINT32                                                      reserved76;	//0xCC8812FC
	UINT32                                                      reserved77;	//0xCC881300
	UINT32                                                      reserved78;	//0xCC881304
	UINT32                                                      reserved79;	//0xCC881308
	UINT32                                                      reserved80;	//0xCC88130C
	UINT32                                                      reserved81;	//0xCC881310
	UINT32                                                      reserved82;	//0xCC881314
	UINT32                                                      reserved83;	//0xCC881318
	UINT32                                                      reserved84;	//0xCC88131C
	UINT32                                                      reserved85;	//0xCC881320
	UINT32                                                      reserved86;	//0xCC881324
	UINT32                                                      reserved87;	//0xCC881328
	UINT32                                                      reserved88;	//0xCC88132C
	UINT32                                                      reserved89;	//0xCC881330
	UINT32                                                      reserved90;	//0xCC881334
	UINT32                                                      reserved91;	//0xCC881338
	UINT32                                                      reserved92;	//0xCC88133C
	UINT32                                                      reserved93;	//0xCC881340
	UINT32                                                      reserved94;	//0xCC881344
	UINT32                                                      reserved95;	//0xCC881348
	UINT32                                                      reserved96;	//0xCC88134C
	UINT32                                                      reserved97;	//0xCC881350
	UINT32                                                      reserved98;	//0xCC881354
	UINT32                                                      reserved99;	//0xCC881358
	UINT32                                                     reserved100;	//0xCC88135C
	UINT32                                                     reserved101;	//0xCC881360
	UINT32                                                     reserved102;	//0xCC881364
	UINT32                                                     reserved103;	//0xCC881368
	UINT32                                                     reserved104;	//0xCC88136C
	UINT32                                                     reserved105;	//0xCC881370
	UINT32                                                     reserved106;	//0xCC881374
	UINT32                                                     reserved107;	//0xCC881378
	UINT32                                                     reserved108;	//0xCC88137C
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_00_T                pe1_logo_l7sc_ctrl_00;	//0xCC881380
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_01_T                pe1_logo_l7sc_ctrl_01;	//0xCC881384
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_02_T                pe1_logo_l7sc_ctrl_02;	//0xCC881388
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_03_T                pe1_logo_l7sc_ctrl_03;	//0xCC88138C
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_04_T                pe1_logo_l7sc_ctrl_04;	//0xCC881390
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_05_T                pe1_logo_l7sc_ctrl_05;	//0xCC881394
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_06_T                pe1_logo_l7sc_ctrl_06;	//0xCC881398
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_07_T                pe1_logo_l7sc_ctrl_07;	//0xCC88139C
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_08_T                pe1_logo_l7sc_ctrl_08;	//0xCC8813A0
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_09_T                pe1_logo_l7sc_ctrl_09;	//0xCC8813A4
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_10_T                pe1_logo_l7sc_ctrl_10;	//0xCC8813A8
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_11_T                pe1_logo_l7sc_ctrl_11;	//0xCC8813AC
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_12_T                pe1_logo_l7sc_ctrl_12;	//0xCC8813B0
	PE_O26_CC_PE1_LOGO_L7SC_CTRL_13_T                pe1_logo_l7sc_ctrl_13;	//0xCC8813B4
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_00_T                pe1_logo_l3sc_ctrl_00;	//0xCC8813B8
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_01_T                pe1_logo_l3sc_ctrl_01;	//0xCC8813BC
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_02_T                pe1_logo_l3sc_ctrl_02;	//0xCC8813C0
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_03_T                pe1_logo_l3sc_ctrl_03;	//0xCC8813C4
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_04_T                pe1_logo_l3sc_ctrl_04;	//0xCC8813C8
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_05_T                pe1_logo_l3sc_ctrl_05;	//0xCC8813CC
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_06_T                pe1_logo_l3sc_ctrl_06;	//0xCC8813D0
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_07_T                pe1_logo_l3sc_ctrl_07;	//0xCC8813D4
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_08_T                pe1_logo_l3sc_ctrl_08;	//0xCC8813D8
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_09_T                pe1_logo_l3sc_ctrl_09;	//0xCC8813DC
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_10_T                pe1_logo_l3sc_ctrl_10;	//0xCC8813E0
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_11_T                pe1_logo_l3sc_ctrl_11;	//0xCC8813E4
	PE_O26_CC_PE1_LOGO_L3SC_CTRL_12_T                pe1_logo_l3sc_ctrl_12;	//0xCC8813E8
	PE_O26_CC_PE1_LOGO_STAT_00_T                          pe1_logo_stat_00;	//0xCC8813EC
	PE_O26_CC_PE1_LOGO_STAT_01_T                          pe1_logo_stat_01;	//0xCC8813F0
	PE_O26_CC_PE1_LOGO_STAT_02_T                          pe1_logo_stat_02;	//0xCC8813F4
	PE_O26_CC_PE1_LOGO_STAT_03_T                          pe1_logo_stat_03;	//0xCC8813F8
	UINT32                                                     reserved109;	//0xCC8813FC
	UINT32                                                     reserved110;	//0xCC881400
	UINT32                                                     reserved111;	//0xCC881404
	UINT32                                                     reserved112;	//0xCC881408
	UINT32                                                     reserved113;	//0xCC88140C
	PE_O26_CC_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC881410
	PE_O26_CC_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC881414
	PE_O26_CC_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC881418
	PE_O26_CC_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC88141C
	PE_O26_CC_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC881420
	PE_O26_CC_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC881424
	PE_O26_CC_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC881428
	PE_O26_CC_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC88142C
	PE_O26_CC_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC881430
	PE_O26_CC_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xCC881434
	PE_O26_CC_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xCC881438
	PE_O26_CC_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xCC88143C
	PE_O26_CC_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xCC881440
	PE_O26_CC_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xCC881444
	PE_O26_CC_PE1_EOTF_RSATUS_T                            pe1_eotf_rsatus;	//0xCC881448
	UINT32                                                     reserved114;	//0xCC88144C
	PE_O26_CC_PE1_LLLUT_E_IA_CTRL_T                    pe1_lllut_e_ia_ctrl;	//0xCC881450
	PE_O26_CC_PE1_LLLUT_E_IA_DATA_T                    pe1_lllut_e_ia_data;	//0xCC881454
	PE_O26_CC_PE1_LLLUT_O_IA_CTRL_T                    pe1_lllut_o_ia_ctrl;	//0xCC881458
	PE_O26_CC_PE1_LLLUT_O_IA_DATA_T                    pe1_lllut_o_ia_data;	//0xCC88145C
	PE_O26_CC_PE1_LLCORE_CTRL_00_T                      pe1_llcore_ctrl_00;	//0xCC881460
	PE_O26_CC_PE1_LLCORE_CTRL_01_T                      pe1_llcore_ctrl_01;	//0xCC881464
	PE_O26_CC_PE1_LLCORE_CTRL_02_T                      pe1_llcore_ctrl_02;	//0xCC881468
	PE_O26_CC_PE1_LLCORE_CTRL_03_T                      pe1_llcore_ctrl_03;	//0xCC88146C
	PE_O26_CC_PE1_LLCORE_CTRL_04_T                      pe1_llcore_ctrl_04;	//0xCC881470
	PE_O26_CC_PE1_LLCORE_CTRL_05_T                      pe1_llcore_ctrl_05;	//0xCC881474
	PE_O26_CC_PE1_LLCORE_CTRL_06_T                      pe1_llcore_ctrl_06;	//0xCC881478
	PE_O26_CC_PE1_LLCORE_CTRL_07_T                      pe1_llcore_ctrl_07;	//0xCC88147C
	PE_O26_CC_PE1_LLCORE_CTRL_08_T                      pe1_llcore_ctrl_08;	//0xCC881480
	PE_O26_CC_PE1_LLCORE_CTRL_09_T                      pe1_llcore_ctrl_09;	//0xCC881484
	PE_O26_CC_PE1_LLCORE_CTRL_10_T                      pe1_llcore_ctrl_10;	//0xCC881488
	PE_O26_CC_PE1_LLCORE_CTRL_11_T                      pe1_llcore_ctrl_11;	//0xCC88148C
	PE_O26_CC_PE1_LLCORE_CTRL_12_T                      pe1_llcore_ctrl_12;	//0xCC881490
	PE_O26_CC_PE1_LLCORE_CTRL_13_T                      pe1_llcore_ctrl_13;	//0xCC881494
	UINT32                                                     reserved115;	//0xCC881498
	UINT32                                                     reserved116;	//0xCC88149C
	PE_O26_CC_PE1_DCE_CTRL_10_T                            pe1_dce_ctrl_10;	//0xCC8814A0
	PE_O26_CC_PE1_DCE_CTRL_11_T                            pe1_dce_ctrl_11;	//0xCC8814A4
	PE_O26_CC_PE1_DCE_CTRL_12_T                            pe1_dce_ctrl_12;	//0xCC8814A8
	PE_O26_CC_PE1_HIST_WIN_SEL_T                          pe1_hist_win_sel;	//0xCC8814AC
	PE_O26_CC_PE1_DCE_HIST1_IA_CTRL_T                pe1_dce_hist1_ia_ctrl;	//0xCC8814B0
	PE_O26_CC_PE1_DCE_HIST1_IA_DATA1_T              pe1_dce_hist1_ia_data1;	//0xCC8814B4
	PE_O26_CC_PE1_DCE_HIST1_IA_DATA2_T              pe1_dce_hist1_ia_data2;	//0xCC8814B8
	PE_O26_CC_PE1_DCE_HIST2_IA_CTRL_T                pe1_dce_hist2_ia_ctrl;	//0xCC8814BC
	PE_O26_CC_PE1_DCE_HIST2_IA_DATA1_T              pe1_dce_hist2_ia_data1;	//0xCC8814C0
	PE_O26_CC_PE1_DCE_HIST2_IA_DATA2_T              pe1_dce_hist2_ia_data2;	//0xCC8814C4
	PE_O26_CC_PE1_DCE_HIST3_IA_CTRL_T                pe1_dce_hist3_ia_ctrl;	//0xCC8814C8
	PE_O26_CC_PE1_DCE_HIST3_IA_DATA1_T              pe1_dce_hist3_ia_data1;	//0xCC8814CC
	PE_O26_CC_PE1_DCE_HIST3_IA_DATA2_T              pe1_dce_hist3_ia_data2;	//0xCC8814D0
	UINT32                                                     reserved117;	//0xCC8814D4
	UINT32                                                     reserved118;	//0xCC8814D8
	UINT32                                                     reserved119;	//0xCC8814DC
	PE_O26_CC_PE1_WIN2_CTRL_09_T                          pe1_win2_ctrl_09;	//0xCC8814E0
	PE_O26_CC_PE1_WIN2_CTRL_10_T                          pe1_win2_ctrl_10;	//0xCC8814E4
	PE_O26_CC_PE1_WIN2_CTRL_11_T                          pe1_win2_ctrl_11;	//0xCC8814E8
	PE_O26_CC_PE1_WIN2_CTRL_12_T                          pe1_win2_ctrl_12;	//0xCC8814EC
	PE_O26_CC_PE1_WIN2_CTRL_13_T                          pe1_win2_ctrl_13;	//0xCC8814F0
	PE_O26_CC_PE1_WIN2_CTRL_14_T                          pe1_win2_ctrl_14;	//0xCC8814F4
	PE_O26_CC_PE1_WIN2_CTRL_15_T                          pe1_win2_ctrl_15;	//0xCC8814F8
	PE_O26_CC_PE1_WIN2_CTRL_16_T                          pe1_win2_ctrl_16;	//0xCC8814FC
	PE_O26_CC_PCC_WINCTRL_00_T                              pcc_winctrl_00;	//0xCC881500
	PE_O26_CC_PCC_WINCTRL_01_T                              pcc_winctrl_01;	//0xCC881504
	PE_O26_CC_PCC_WINCTRL_02_T                              pcc_winctrl_02;	//0xCC881508
	PE_O26_CC_PCC_WINCTRL_03_T                              pcc_winctrl_03;	//0xCC88150C
	PE_O26_CC_PCC_WINCTRL_04_T                              pcc_winctrl_04;	//0xCC881510
	PE_O26_CC_PCC_WINCTRL_05_T                              pcc_winctrl_05;	//0xCC881514
	PE_O26_CC_PCC_WINCTRL_06_T                              pcc_winctrl_06;	//0xCC881518
	PE_O26_CC_PCC_WINCTRL_07_T                              pcc_winctrl_07;	//0xCC88151C
	PE_O26_CC_PCC_WINCTRL_08_T                              pcc_winctrl_08;	//0xCC881520
	PE_O26_CC_PCC_WINCTRL_09_T                              pcc_winctrl_09;	//0xCC881524
	PE_O26_CC_PCC_WINCTRL_10_T                              pcc_winctrl_10;	//0xCC881528
	PE_O26_CC_PCC_WINCTRL_11_T                              pcc_winctrl_11;	//0xCC88152C
	PE_O26_CC_PCC_WINCTRL_12_T                              pcc_winctrl_12;	//0xCC881530
	PE_O26_CC_PCC_WINCTRL_13_T                              pcc_winctrl_13;	//0xCC881534
	PE_O26_CC_PCC_WINCTRL_14_T                              pcc_winctrl_14;	//0xCC881538
	PE_O26_CC_PCC_WINCTRL_15_T                              pcc_winctrl_15;	//0xCC88153C
	PE_O26_CC_PCC_WINCTRL_16_T                              pcc_winctrl_16;	//0xCC881540
	PE_O26_CC_PCC_WINCTRL_17_T                              pcc_winctrl_17;	//0xCC881544
	PE_O26_CC_PCC_WINCTRL_18_T                              pcc_winctrl_18;	//0xCC881548
	PE_O26_CC_PCC_WINCTRL_19_T                              pcc_winctrl_19;	//0xCC88154C
	PE_O26_CC_PCC_WINCTRL_20_T                              pcc_winctrl_20;	//0xCC881550
	PE_O26_CC_PE1_PPCC_CTRL_00_T                          pe1_ppcc_ctrl_00;	//0xCC881554
	PE_O26_CC_PE1_PPCC_CTRL_01_T                          pe1_ppcc_ctrl_01;	//0xCC881558
	PE_O26_CC_PE1_PPCC_CTRL_02_T                          pe1_ppcc_ctrl_02;	//0xCC88155C
	PE_O26_CC_PE1_PPCC_CTRL_03_T                          pe1_ppcc_ctrl_03;	//0xCC881560
	PE_O26_CC_PE1_PPCC_CTRL_04_T                          pe1_ppcc_ctrl_04;	//0xCC881564
	PE_O26_CC_PE1_PPCC_CTRL_05_T                          pe1_ppcc_ctrl_05;	//0xCC881568
	PE_O26_CC_PE1_PPCC_CTRL_06_T                          pe1_ppcc_ctrl_06;	//0xCC88156C
	PE_O26_CC_PE1_PPCC_CTRL_07_T                          pe1_ppcc_ctrl_07;	//0xCC881570
	PE_O26_CC_PE1_PPCC_CTRL_08_T                          pe1_ppcc_ctrl_08;	//0xCC881574
	PE_O26_CC_PE1_PPCC_CTRL_09_T                          pe1_ppcc_ctrl_09;	//0xCC881578
	PE_O26_CC_PE1_PPCC_CTRL_10_T                          pe1_ppcc_ctrl_10;	//0xCC88157C
	PE_O26_CC_PE1_PPCC_CTRL_11_T                          pe1_ppcc_ctrl_11;	//0xCC881580
	UINT32                                                     reserved120;	//0xCC881584
	UINT32                                                     reserved121;	//0xCC881588
	UINT32                                                     reserved122;	//0xCC88158C
	UINT32                                                     reserved123;	//0xCC881590
	UINT32                                                     reserved124;	//0xCC881594
	UINT32                                                     reserved125;	//0xCC881598
	UINT32                                                     reserved126;	//0xCC88159C
	UINT32                                                     reserved127;	//0xCC8815A0
	UINT32                                                     reserved128;	//0xCC8815A4
	UINT32                                                     reserved129;	//0xCC8815A8
	UINT32                                                     reserved130;	//0xCC8815AC
	PE_O26_CC_PE1_SYNC_DLY_00_T                            pe1_sync_dly_00;	//0xCC8815B0
	PE_O26_CC_PE1_SYNC_DLY_01_T                            pe1_sync_dly_01;	//0xCC8815B4
	PE_O26_CC_PE1_SYNC_DLY_02_T                            pe1_sync_dly_02;	//0xCC8815B8
	PE_O26_CC_PE1_SYNC_DLY_03_T                            pe1_sync_dly_03;	//0xCC8815BC
	PE_O26_CC_PE1_SYNC_DLY_04_T                            pe1_sync_dly_04;	//0xCC8815C0
	PE_O26_CC_PE1_SYNC_DLY_05_T                            pe1_sync_dly_05;	//0xCC8815C4
	PE_O26_CC_PE1_SYNC_DLY_06_T                            pe1_sync_dly_06;	//0xCC8815C8
	PE_O26_CC_PE1_SYNC_DLY_07_T                            pe1_sync_dly_07;	//0xCC8815CC
	PE_O26_CC_PE1_SYNC_DLY_08_T                            pe1_sync_dly_08;	//0xCC8815D0
	PE_O26_CC_PE1_SYNC_DLY_09_T                            pe1_sync_dly_09;	//0xCC8815D4
	PE_O26_CC_PE1_SYNC_DLY_10_T                            pe1_sync_dly_10;	//0xCC8815D8
}PE_CC_PE1_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881600 RW 0x0200_0040
	UINT32 enable                           :1;	//(0,NA,0x0) //
	UINT32 graycolor_enable                 :1;	//(1,NA,0x0) //
	UINT32 color_only_enable                :1;	//(2,NA,0x0) //
	UINT32 cb_info                          :1;	//(3,NA,0x0) //
	UINT32 cr_info                          :1;	//(4,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_en                      :1;	//(6,NA,0x1) //
	UINT32 resvd1                           :1;
	UINT32 center_position                  :8;	//(15:8,NA,0x00) //center position for contrast control(Y domain)
	UINT32 contrast                         :12;	//(27:16,NA,0x200) //contrast control(Y domain)
	UINT32 reg_vspyc_debug                  :3;	//(30:28,NA,0x0) //1,2:object_gain, 3: saturation_alpha, others:vsp_yc_out
	UINT32 resvd2                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881604 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881608 RW 0x12AF_7C94
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,NA,0x7C94) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88160C RW 0x7773_12AF
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,NA,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,NA,0x7773) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881610 RW 0x21E6_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,NA,0x21E6) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881614 RW 0x12AF_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881618 RW 0x1CC5_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,NA,0x1CC5) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88161C RW 0x07C0_0600
	UINT32 r_yc2rgb_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881620 RW 0x0600_0000
	UINT32 r_yc2rgb_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881624 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst4                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSPYC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881630 RW 0x0000_0300
	UINT32 resvd0                           :4;
	UINT32 reg_crgn_objt_sel                :2;	//(5:4,NA,0x0) //0:multi(objt,crgn) 1:max(objt,crgn), 2:crgn, 3:objt
	UINT32 resvd1                           :2;
	UINT32 reg_yy_vv_sel                    :1;	//(8,NA,0x1) //0:Y, 1:V
	UINT32 reg_hsv_hsl_sel                  :1;	//(9,NA,0x1) //0:HSL, 1:HSV
	UINT32 reg_hsv_sat_sel                  :1;	//(10,NA,0x0) //0:(max(rgb)-min(rgb))/max(rgb), 1:max(rgb)-min(rgb)
	UINT32 resvd2                           :1;
	UINT32 reg_clock_gating_disable         :1;	//(12,NA,0x0) //
	UINT32 resvd3                           :19;
	};
}PE_O26_CC2_PE1_VSP_CC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881644 RW 0x0000_2001
	UINT32 reg_vspyc_tap_mode               :1;	//(0,NA,0x1) //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_vspyc_repeat_en              :1;	//(4,NA,0x0) //1:repeat(interpolation off)
	UINT32 resvd1                           :3;
	UINT32 reg_oai_vspyc_pel_dly            :2;	//(9:8,NA,VNA) //0:0 1:+1 2:+2 3:+3
	UINT32 resvd2                           :2;
	UINT32 reg_oai_yspyc_obj_dly            :2;	//(13:12,NA,VNA) //0:-2 1:-1 2:0 3:+1
	UINT32 resvd3                           :18;
	};
}PE_O26_CC2_PE1_VSP_CC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881650 RW 0x01F1_0000
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x1F1) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881654 RW 0x0200_00BE
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xBE) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881658 RW 0x020D_00F0
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xF0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x20D) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88165C RW 0x0214_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x214) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881660 RW 0x0228_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x228) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881664 RW 0x0230_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x230) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881668 RW 0x023F_00A0
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xA0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x23F) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88166C RW 0x024D_0000
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x24D) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881670 RW 0x2D6E_2000
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x20) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0x6E) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x2D) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881674 RW 0x46FF_39C8
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xC8) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0x39) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x46) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881678 RW 0x66FF_53FF
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x53) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x66) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88167C RW 0x7FFF_7DFF
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x7D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x7F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881680 RW 0x328C_0F00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0xF) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x32) //
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881684 RW 0x64FF_50FF
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x50) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x64) //
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881688 RW 0xD278_AFFF
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xAF) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0x78) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xD2) //
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88168C RO 0xE600_DC3C
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xDC) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xE6) //
	};
}PE_O26_CC2_PE1_VSP_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816A0 RW 0x0000_0000
	UINT32 enable_debug_mode                :1;	//(0,NA,0x0) //Enable debug mode
	UINT32 status_enable                    :1;	//(1,NA,0x0) //APL
	UINT32 debug_mode                       :1;	//(2,NA,0x0) //0' : status read(APL)	'1' : yc control
	UINT32 resvd0                           :17;
	UINT32 show_apl                         :1;	//(20,NA,0x0) //show apl( y, rgb, r,g,b)
	UINT32 resvd1                           :11;
	};
}PE_O26_CC2_PE1_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816A4 RW VNA
	UINT32 yc_debug_en                      :1;	//(0,NA,0x0) //
	UINT32 force_yy_enable                  :1;	//(1,NA,0x0) //forcing Y data enable
	UINT32 force_cb_enable                  :1;	//(2,NA,0x0) //forcing Cb data enable
	UINT32 force_cr_enable                  :1;	//(3,NA,0x0) //forcing Cr data enable
	UINT32 yc_debug_mode_sel                :3;	//(6:4,NA,0x0) //"000" : normal	"001" : show Y only(grayscale)	"010" : show CbCr only	"011" : show Cb data at Y channel	"100" : show Cr data at Y channel	others : normal
	UINT32 resvd                            :25;
	};
}PE_O26_CC2_PE1_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816A8 RW 0x0000_0000
	UINT32 force_yy                         :10;	//(9:0,NA,0x0) //
	UINT32 force_cb                         :10;	//(19:10,NA,0x0) //forcing Cb data
	UINT32 force_cr                         :10;	//(29:20,NA,0x0) //forcing Cr data
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_DEBUG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816B0 RW 0x0000_0100
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
}PE_O26_CC2_PE1_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816B4 RW 0x00C0_C0C0
	UINT32 user_ctrl_g_gain                 :8;	//(7:0,NA,0xC0) //User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//(15:8,NA,0xC0) //User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//(23:16,NA,0xC0) //User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}PE_O26_CC2_PE1_CW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816B8 RW 0x0040_0000
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
}PE_O26_CC2_PE1_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C0 RW 0x0000_00FF
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C4 RW 0x0064_00FF
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x64) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C8 RW 0x011C_00FF
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x11C) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816CC RW 0x01AA_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x1AA) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D0 RW 0x0238_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x238) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D4 RW 0x02C6_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x2C6) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D8 RW 0x0354_00FF
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x354) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816DC RW 0x03FF_00FF
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816E0 RW 0x06FF_00FF
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x6) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816E4 RW 0x12FF_0DFF
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0xD) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x12) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816E8 RW 0x198C_14DC
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xDC) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x14) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x19) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816EC RW 0x2000_1D3C
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x1D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x20) //
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F0 RW 0x6464_3C00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0x3C) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x64) //
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F4 RW 0x8CC8_7896
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0x96) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x78) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xC8) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x8C) //
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F8 RW 0xBEFF_A0E6
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xE6) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xA0) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xBE) //
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816FC RW 0xFFA0_FAFF
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xFA) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0xA0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xFF) //
	};
}PE_O26_CC2_PE1_CW_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881710 RW 0x1E00_10E0
	UINT32 display_height                   :13;	//(12:0,NA,0x10E0) //
	UINT32 resvd0                           :3;
	UINT32 display_width                    :13;	//(28:16,NA,0x1E00) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LBLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881714 RW 0x0000_0000
	UINT32 reg_block_size_v                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_block_size_h                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_block_no_v                   :6;	//(21:16,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,NA,0x0) //
	};
}PE_O26_CC2_PE1_LBLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881718 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :8;	//(7:0,NA,0x0) //
	UINT32 reg_last_block_size_h            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O26_CC2_PE1_LBLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881720 RW 0x8000_0A40
	UINT32 reg_logo_blend_en                :1;	//(0,NA,0x0) //
	UINT32 reg_logo_blend_l7_disable        :1;	//(1,NA,0x0) //
	UINT32 reg_logo_blend_l3_disable        :1;	//(2,NA,0x0) //
	UINT32 reg_logo_blend_c5_disable        :1;	//(3,NA,0x0) //
	UINT32 reg_logo_master_gain             :8;	//(11:4,NA,0xA4) //
	UINT32 reg_logo_debug_sel               :4;	//(15:12,NA,0x0) //0:debug_off, 1:c5_crnt_map, 2:l7_logo_map, 3:l3_logo_map, 4:region_gain, 5:boundary_gain, 6:merged_contrast_gain, 7:luma_drop_image, 8:merged_drop_gain, 9:l6_blur_image, A:merged_saturation_gain, B:saturation_gain, C:saturation_control_gain, others:debug_off
	UINT32 reg_region_gain_en               :1;	//(16,NA,0x0) //
	UINT32 resvd                            :3;
	UINT32 reg_logo_map_out_sel             :3;	//(22:20,NA,0x0) //0:max(merged contrast/drop/saturation gain), 1:l7_logo_map, 2:l3_logo_map, 3:c5_crnt_map, 4:merged_contrast_gain, 5:merged_drop_gain, 6:merged_saturation_gain, 7:max(merged drop/saturation_gain), others:max(merged contrast/drop/saturation gain)
	UINT32 reg_bound_proc_en                :1;	//(23,NA,0x0) //
	UINT32 reg_region_bnd_gain              :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881724 RW 0x12C2_5BFE
	UINT32 resvd                            :1;
	UINT32 bound_proc_logocheck             :1;	//(1,NA,0x1) //
	UINT32 bound_proc_gain                  :8;	//(9:2,NA,0xff) //
	UINT32 bound_proc_range_x               :11;	//(20:10,NA,0x96) //
	UINT32 bound_proc_range_y               :11;	//(31:21,NA,0x96) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881728 RW 0x0000_0000
	UINT32 boundary_position_x0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_x1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88172C RW 0x0000_0000
	UINT32 boundary_position_y0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_y1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881730 RW 0x03BF_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,NA,0x3BF) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881734 RW 0x10DF_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,NA,0x10DF) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881738 RW 0x0100_0080
	UINT32 reg_region_position_x1           :13;	//(12:0,NA,0x80) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,NA,0x100) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88173C RW 0x0200_0180
	UINT32 reg_region_position_x3           :13;	//(12:0,NA,0x180) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,NA,0x200) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881740 RW 0x0300_0280
	UINT32 reg_region_position_x5           :13;	//(12:0,NA,0x280) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,NA,0x300) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881744 RW 0x03A0_0380
	UINT32 reg_region_position_x7           :13;	//(12:0,NA,0x380) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,NA,0x3A0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881748 RW 0x0800_0400
	UINT32 reg_region_position_y1           :13;	//(12:0,NA,0x400) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,NA,0x800) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88174C RW 0x0E00_0C00
	UINT32 reg_region_position_y3           :13;	//(12:0,NA,0xC00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,NA,0xE00) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881750 RW 0x1000_0F00
	UINT32 reg_region_position_y5           :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,NA,0x1000) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881754 RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881758 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88175C RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881760 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881764 RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881768 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88176C RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881770 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881774 RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881778 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88177C RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881780 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881784 RW 0x0200_0310
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x310) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881788 RW 0x0080_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x80) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88178C RW 0x2040_80C4
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xC4) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x20) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881790 RW 0x0380_03FF
	UINT32 reg_drop_x7_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,NA,0x380) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881794 RW 0x0200_0300
	UINT32 reg_drop_x5_i                    :10;	//(9:0,NA,0x300) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881798 RW 0x0100_0200
	UINT32 reg_drop_x3_i                    :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,NA,0x100) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88179C RW 0x0000_0100
	UINT32 reg_drop_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A0 RW 0x0200_0240
	UINT32 reg_drop_y7_i                    :10;	//(9:0,NA,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A4 RW 0x0190_01C0
	UINT32 reg_drop_y5_i                    :10;	//(9:0,NA,0x1C0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,NA,0x190) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A8 RW 0x00E0_0190
	UINT32 reg_drop_y3_i                    :10;	//(9:0,NA,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,NA,0xE0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817AC RW 0x0000_00E0
	UINT32 reg_drop_y1_i                    :10;	//(9:0,NA,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B0 RW 0x0300_03FF
	UINT32 reg_sat_scon_x3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B4 RW 0x0000_0200
	UINT32 reg_sat_scon_x1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B8 RW 0x0300_03FF
	UINT32 reg_sat_scon_y3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817BC RW 0x0000_0200
	UINT32 reg_sat_scon_y1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C0 RW 0x1080_1080
	UINT32 reg_l7_gain_drop                 :8;	//(7:0,NA,0x80) //
	UINT32 reg_l7_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l7_gain_b_contrast           :8;	//(23:16,NA,0x80) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l7_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C4 RW 0x0840_1040
	UINT32 reg_l3_gain_drop                 :8;	//(7:0,NA,0x40) //
	UINT32 reg_l3_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l3_gain_b_contrast           :8;	//(23:16,NA,0x40) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l3_gain_saturation           :8;	//(31:24,NA,0x8) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C8 RW 0x1060_20A4
	UINT32 reg_c5_gain_drop                 :8;	//(7:0,NA,0xA4) //
	UINT32 reg_c5_gain_w_contrast           :8;	//(15:8,NA,0x20) //white(bright) contrast gain(input level < output level)
	UINT32 reg_c5_gain_b_contrast           :8;	//(23:16,NA,0x60) //black(dark) contrast gain(input level > output level)
	UINT32 reg_c5_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817CC RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O26_CC2_PE1_LOGO_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D0 RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D4 RW 0x0000_0000
	UINT32 reg_merge_contrast_l7l3          :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_contrast_l7l3c5        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_drop_l7l3              :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D8 RW 0x0000_0000
	UINT32 reg_merge_drop_l7l3c5            :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3c5      :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817DC RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O26_CC2_PE1_LOGO_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817E0 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817F4 RW 0x0040_80FF
	UINT32 reg_txt_x3_i                     :8;	//(7:0,NA,0xFF) //texture gain LUT
	UINT32 reg_txt_x2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_x1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_x0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817F8 RW 0x0040_80FF
	UINT32 reg_txt_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_txt_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817FC RW 0x0080_8080
	UINT32 reg_region_gain_contrast         :8;	//(7:0,NA,0x80) //1.0 = 128
	UINT32 reg_region_gain_drop             :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_saturation       :8;	//(23:16,NA,0x80) //
	UINT32 resvd                            :8;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881800 RW 0x0000_0140
	UINT32 reg_logo_tap_mode                :1;	//(0,NA,0x0) //logo texture interpolation 0:2tap, 1:4tap
	UINT32 reg_logo_repeat_en               :1;	//(1,NA,0x0) //logo texture interpolation 1:repeat
	UINT32 resvd0                           :2;
	UINT32 reg_disp_dbg_ref_l3              :1;	//(4,NA,0x0) //logo refine debug disp
	UINT32 reg_use_extern_valid             :1;	//(5,NA,0x0) //logo refine dummy valid gen param
	UINT32 reg_use_blank_period_cnt         :1;	//(6,NA,0x1) //logo refine dummy valid gen param
	UINT32 resvd1                           :1;
	UINT32 reg_refine_en                    :1;	//(8,NA,0x1) //logo refine en
	UINT32 reg_refine_detour                :1;	//(9,NA,0x0) //logo refine detour(line delay 0)
	UINT32 resvd2                           :6;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881804 RW 0x00000000
	UINT32 reg_refine_weight_lut_x3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_x2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_x1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_x0         :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881808 RW 0x00000000
	UINT32 reg_refine_weight_lut_y3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_y2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_y1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_y0         :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88180C RW 0x00000000
	UINT32 reg_refine_weight_gain_x3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_x2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_x1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_x0        :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881810 RW 0x00000000
	UINT32 reg_refine_weight_gain_y3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_y2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_y1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_y0        :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881820 RW 0x0000_0000
	UINT32 reg_gsr_blend_en                 :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//(7:4,NA,0x0) //0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//(25:16,NA,0x0) //
	UINT32 resvd2                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881824 RW 0x03B0_4200
	UINT32 reg_curr_peak_level              :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :2;
	UINT32 reg_crnt_resol_sel               :4;	//(15:12,NA,0x4) //left shift bit size, 0:8b, 1:7b, 2:6b, 3:5b, 4:4b, 5:3b, 6:2b, 7:1b, 8:0b
	UINT32 reg_wg_ratio                     :11;	//(26:16,NA,0x3B0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC2_PE1_GSR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881828 RW 0x0478_031F
	UINT32 reg_wb_ratio                     :11;	//(10:0,NA,0x31F) //
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//(26:16,NA,0x478) //
	UINT32 resvd1                           :5;
	};
}PE_O26_CC2_PE1_GSR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88182C RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,NA,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,NA,0x326) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CC2_PE1_GSR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881830 RW 0x0389_02A8
	UINT32 reg_b_crnt_wgt                   :12;	//(11:0,NA,0x2A8) //
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//(27:16,NA,0x389) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CC2_PE1_GSR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881834 RW 0x0000_0000
	UINT32 reg_crnt_lut_y00                 :16;	//(15:0,NA,0x0) //
	UINT32 reg_crnt_lut_x00                 :10;	//(25:16,NA,0x0) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881838 RW 0x0044_0CF9
	UINT32 reg_crnt_lut_y01                 :16;	//(15:0,NA,0xCF9) //
	UINT32 reg_crnt_lut_x01                 :10;	//(25:16,NA,0x44) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88183C RW 0x0088_1BD0
	UINT32 reg_crnt_lut_y02                 :16;	//(15:0,NA,0x1BD0) //
	UINT32 reg_crnt_lut_x02                 :10;	//(25:16,NA,0x88) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881840 RW 0x00CC_2B72
	UINT32 reg_crnt_lut_y03                 :16;	//(15:0,NA,0x2B72) //
	UINT32 reg_crnt_lut_x03                 :10;	//(25:16,NA,0xCC) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881844 RW 0x0110_3B9F
	UINT32 reg_crnt_lut_y04                 :16;	//(15:0,NA,0x3B9F) //
	UINT32 reg_crnt_lut_x04                 :10;	//(25:16,NA,0x110) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881848 RW 0x0154_4C35
	UINT32 reg_crnt_lut_y05                 :16;	//(15:0,NA,0x4C35) //
	UINT32 reg_crnt_lut_x05                 :10;	//(25:16,NA,0x154) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88184C RW 0x0198_5D22
	UINT32 reg_crnt_lut_y06                 :16;	//(15:0,NA,0x5D22) //
	UINT32 reg_crnt_lut_x06                 :10;	//(25:16,NA,0x198) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881850 RW 0x01DC_6E57
	UINT32 reg_crnt_lut_y07                 :16;	//(15:0,NA,0x6E57) //
	UINT32 reg_crnt_lut_x07                 :10;	//(25:16,NA,0x1DC) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881854 RW 0x0220_7FCD
	UINT32 reg_crnt_lut_y08                 :16;	//(15:0,NA,0x7FCD) //
	UINT32 reg_crnt_lut_x08                 :10;	//(25:16,NA,0x220) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881858 RW 0x0264_917A
	UINT32 reg_crnt_lut_y09                 :16;	//(15:0,NA,0x917A) //
	UINT32 reg_crnt_lut_x09                 :10;	//(25:16,NA,0x264) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88185C RW 0x02A8_A35B
	UINT32 reg_crnt_lut_y10                 :16;	//(15:0,NA,0xA35B) //
	UINT32 reg_crnt_lut_x10                 :10;	//(25:16,NA,0x2A8) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881860 RW 0x02EC_B569
	UINT32 reg_crnt_lut_y11                 :16;	//(15:0,NA,0xB569) //
	UINT32 reg_crnt_lut_x11                 :10;	//(25:16,NA,0x2EC) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881864 RW 0x0330_C7A2
	UINT32 reg_crnt_lut_y12                 :16;	//(15:0,NA,0xC7A2) //
	UINT32 reg_crnt_lut_x12                 :10;	//(25:16,NA,0x330) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881868 RW 0x0374_DA02
	UINT32 reg_crnt_lut_y13                 :16;	//(15:0,NA,0xDA02) //
	UINT32 reg_crnt_lut_x13                 :10;	//(25:16,NA,0x374) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88186C RW 0x03B8_EC86
	UINT32 reg_crnt_lut_y14                 :16;	//(15:0,NA,0xEC86) //
	UINT32 reg_crnt_lut_x14                 :10;	//(25:16,NA,0x3B8) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881870 RW 0x03FF_FFFF
	UINT32 reg_crnt_lut_y15                 :16;	//(15:0,NA,0xFFFF) //
	UINT32 reg_crnt_lut_x15                 :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd                            :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881874 RW 0x0200_03FF
	UINT32 reg_crnt_x3_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x2_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881878 RW 0x0000_0100
	UINT32 reg_crnt_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88187C RW 0x0000_0000
	UINT32 reg_crnt_y3_i                    :8;	//(7:0,NA,0x0) //
	UINT32 reg_crnt_y2_i                    :8;	//(15:8,NA,0x0) //
	UINT32 reg_crnt_y1_i                    :8;	//(23:16,NA,0x0) //
	UINT32 reg_crnt_y0_i                    :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_GSR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881880 RW 0x0200_03FF
	UINT32 reg_value_x3_i                   :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x2_i                   :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881884 RW 0x0000_0100
	UINT32 reg_value_x1_i                   :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x0_i                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881888 RW 0x0000_0000
	UINT32 reg_value_y3_i                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_value_y2_i                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_value_y1_i                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_value_y0_i                   :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_GSR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88188C RW 0x0200_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881890 RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_GSR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881894 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_GSR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881898 RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O26_CC2_PE1_GSR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88189C RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_pxl_height_0                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_GSR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818A0 RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O26_CC2_PE1_GSR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818A4 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_pxl_height_1                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_GSR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818E0 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :14;	//(13:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :1;
	UINT32 pxl_rep_in_0                     :1;	//(15,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_ypos_0                   :14;	//(29:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818E4 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_0                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818E8 RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818EC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818F0 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818F4 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :14;	//(13:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :1;
	UINT32 pxl_rep_in_0                     :1;	//(15,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_ypos_0                   :14;	//(29:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818F8 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_0                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818FC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881900 RW VNA
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881904 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881908 RW 0x0000_0000
	UINT32 mux3d_en                         :1;	//(0,NA,0x0) //Mux 3D on/off	'0' = off	'1' = on
	UINT32 resvd0                           :3;
	UINT32 reg_out_mux                      :2;	//(5:4,NA,0x00) //output select	'00' = blend	'01' = R	'10' = L	'11' = line by line
	UINT32 start_parity                     :1;	//(6,NA,0x00) //start parity	'0' : start with Left	'1' : start with Right
	UINT32 resvd1                           :9;
	UINT32 alpha1_gain                      :8;	//(23:16,NA,0x0) //gain for L, R channel blend	255 : L output ~ 0 : R output
	UINT32 alpha0_gain                      :8;	//(31:24,NA,0x0) //gain for Back Ground Color and Blended Data	255 : BG Color output ~ 0 : Data output
	};
}PE_O26_CC2_PE1_MUTE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88190C RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_0              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_0              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O26_CC2_PE1_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881910 RW 0x0000_0000
	UINT32 x1_0                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_0                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881914 RW 0x0000_0000
	UINT32 x0_0                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 mux_r_window_h_en_0              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 mux_r_window_v_en_0              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O26_CC2_PE1_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881918 RW 0x0000_0000
	UINT32 x1_0                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_0                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88191C RW 0x0000_0000
	UINT32 bg_color_r                       :8;	//(7:0,NA,0x0) //8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//(15:8,NA,0x0) //8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//(23:16,NA,0x0) //8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881920 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :14;	//(13:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :1;
	UINT32 pxl_rep_in_1                     :1;	//(15,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_ypos_1                   :14;	//(29:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881924 RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_1                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881928 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :14;	//(13:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :1;
	UINT32 pxl_rep_in_1                     :1;	//(15,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_ypos_1                   :14;	//(29:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88192C RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_1                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881930 RW 0x0000_0000
	UINT32 x0_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 mux_l_window_h_en_1              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 mux_l_window_v_en_1              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O26_CC2_PE1_MUTE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881934 RW 0x0000_0000
	UINT32 x1_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881938 RW 0x0000_0000
	UINT32 x0_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 mux_r_window_h_en_1              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 mux_r_window_v_en_1              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O26_CC2_PE1_MUTE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88193C RW 0x0000_0000
	UINT32 x1_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CC2_PE1_MUTE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A00 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A04 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A08 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A0C RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A10 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //
	UINT32 sync_i_h_sel                     :1;	//(16,RW,0x0) //
	UINT32 sync_i_v_sel                     :1;	//(17,RW,0x0) //
	UINT32 sync_i_inv_ha                    :1;	//(18,RW,0x0) //
	UINT32 sync_i_inv_va                    :1;	//(19,RW,0x0) //
	UINT32 sync_o_sel_ha                    :1;	//(20,RW,0x0) //
	UINT32 sync_o_sel_va                    :1;	//(21,RW,0x0) //
	UINT32 sync_o_sel_hs                    :1;	//(22,RW,0x0) //
	UINT32 sync_o_sel_vs                    :1;	//(23,RW,0x0) //
	UINT32 tp_update_hv_zero                :1;	//(24,RW,0x0) //
	UINT32 force_out_ha                     :1;	//(25,RW,0x0) //
	UINT32 force_out_va                     :1;	//(26,RW,0x0) //
	UINT32 force_out_hs                     :1;	//(27,RW,0x0) //
	UINT32 manual_cnt_h_value_en            :1;	//(28,RW,0x0) //
	UINT32 manual_cnt_v_value_en            :1;	//(29,RW,0x0) //
	UINT32 force_out_vs                     :1;	//(30,RW,0x0) //
	UINT32 update_force                     :1;	//(31,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A14 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A18 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A1C RW 0x0002_8028
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x28) //
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A20 RW 0x0002_8028
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x28) //
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A24 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A28 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A2C RW 0x0000_0000
	UINT32 reg_master_gain                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_l3_value_gain                :8;	//(15:8,RW,0x0) //
	UINT32 reg_master_en                    :1;	//(16,RW,0x0) //master en
	UINT32 resvd0                           :3;
	UINT32 reg_out_sel                      :2;	//(21:20,RW,0x0) //0:blend out 1:drop img 2:drop gain 3:s_gain
	UINT32 resvd1                           :2;
	UINT32 reg_l3_en                        :1;	//(24,RW,0x0) //l3 gain en
	UINT32 resvd2                           :7;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A30 RW 0x0000_0000
	UINT32 reg_sat_x3_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A34 RW 0x0000_0000
	UINT32 reg_sat_x1_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A38 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,RW,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A3C RW 0x0000_0000
	UINT32 reg_drop_x7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A40 RW 0x0000_0000
	UINT32 reg_drop_x5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A44 RW 0x0000_0000
	UINT32 reg_drop_x3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A48 RW 0x0000_0000
	UINT32 reg_drop_x1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A4C RW 0x0000_0000
	UINT32 reg_drop_y7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A50 RW 0x0000_0000
	UINT32 reg_drop_y5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A54 RW 0x0000_0000
	UINT32 reg_drop_y3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A58 RW 0x0000_0000
	UINT32 reg_drop_y1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A5C RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_out_disable              :1;	//(15,RW,0x0) //
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_in_disable               :1;	//(31,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A60 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A64 RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_out_disable              :1;	//(15,RW,0x0) //
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_in_disable               :1;	//(31,RW,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A68 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CC2_PE1_LOGO_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A6C RW 0x0000_0100
	UINT32 reg_detour                       :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_use_extern_valid             :1;	//(4,NA,0x0) //logo refine dummy valid gen param
	UINT32 resvd1                           :3;
	UINT32 reg_use_blank_period_cnt         :1;	//(8,NA,0x1) //logo refine dummy valid gen param
	UINT32 resvd2                           :7;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,0x0) //
	};
}PE_O26_CC2_PE1_LOGO_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AA0 RW 0x0000_000F
	UINT32 reg_motiongain_en                :1;	//(0,NA,0x1) //
	UINT32 reg_textgain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(2,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(3,NA,0x1) //
	UINT32 reg_objt_motion_sel              :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd0                           :2;
	UINT32 reg_objt_text_sel                :2;	//(9:8,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd1                           :2;
	UINT32 reg_head_body_sel                :1;	//(12,NA,0x0) //0:max, 1:sum
	UINT32 resvd2                           :19;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AA4 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AA8 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AAC RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB0 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB4 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB8 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ABC RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AC0 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiongain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiongain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiongain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AC4 RW 0x8080_FFFF
	UINT32 reg_motiongain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiongain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiongain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiongain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AC8 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ACC RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AD0 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AD4 RW 0x0000_000F
	UINT32 reg_motiongain_en                :1;	//(0,NA,0x1) //
	UINT32 reg_textgain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(2,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(3,NA,0x1) //
	UINT32 reg_objt_motion_sel              :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd0                           :2;
	UINT32 reg_objt_text_sel                :2;	//(9:8,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd1                           :2;
	UINT32 reg_head_body_sel                :1;	//(12,NA,0x0) //0:max, 1:sum
	UINT32 resvd2                           :19;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AD8 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ADC RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE0 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE4 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE8 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AEC RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF0 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF4 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiongain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiongain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiongain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF8 RW 0x8080_FFFF
	UINT32 reg_motiongain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiongain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiongain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiongain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AFC RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B00 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B04 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B08 RW 0x0000_000F
	UINT32 reg_motiongain_en                :1;	//(0,NA,0x1) //
	UINT32 reg_textgain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(2,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(3,NA,0x1) //
	UINT32 reg_objt_motion_sel              :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd0                           :2;
	UINT32 reg_objt_text_sel                :2;	//(9:8,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd1                           :2;
	UINT32 reg_head_body_sel                :1;	//(12,NA,0x0) //0:max, 1:sum
	UINT32 resvd2                           :19;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B0C RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B10 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B14 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B18 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B1C RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B20 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B24 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B28 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B2C RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B30 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B34 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B38 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B3C RW 0x0000_000F
	UINT32 reg_motiongain_en                :1;	//(0,NA,0x1) //
	UINT32 reg_textgain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(2,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(3,NA,0x1) //
	UINT32 reg_objt_motion_sel              :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd0                           :2;
	UINT32 reg_objt_text_sel                :2;	//(9:8,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd1                           :2;
	UINT32 reg_head_body_sel                :1;	//(12,NA,0x0) //0:max, 1:sum
	UINT32 resvd2                           :19;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B40 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B44 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B48 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B4C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B50 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B54 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B58 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B5C RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B60 RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B64 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B68 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B6C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B70 RW 0x8080_8007
	UINT32 reg_textgain_en                  :1;	//(0,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(2,NA,0x1) //
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 reg_head_body_sel                :1;	//(6,NA,0x0) //0:max, 1:sum
	UINT32 resvd1                           :1;
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B74 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B78 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B7C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B80 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B84 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B88 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B8C RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B90 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B94 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B98 RW 0x0000_000F
	UINT32 reg_motiongain_en                :1;	//(0,NA,0x1) //
	UINT32 reg_textgain_en                  :1;	//(1,NA,0x1) //
	UINT32 reg_bodygain_en                  :1;	//(2,NA,0x1) //
	UINT32 reg_headgain_en                  :1;	//(3,NA,0x1) //
	UINT32 reg_objt_motion_sel              :2;	//(5:4,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd0                           :2;
	UINT32 reg_objt_text_sel                :2;	//(9:8,NA,0x0) //0:max, 1:sum 2:mul
	UINT32 resvd1                           :2;
	UINT32 reg_head_body_sel                :1;	//(12,NA,0x0) //0:max, 1:sum
	UINT32 resvd2                           :19;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B9C RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA0 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA4 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA8 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BAC RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB0 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB4 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB8 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BBC RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O26_CC2_PE1_MERGE_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BC0 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O26_CC2_PE1_MERGE_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BC4 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //1
	UINT32 resvd1                           :3;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BC8 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O26_CC2_PE1_MERGE_CTRL_74_T;

typedef struct {
	PE_O26_CC2_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xCC881600
	PE_O26_CC2_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xCC881604
	PE_O26_CC2_PE1_VSPYC_CTRL_02_T                       pe1_vspyc_ctrl_02;	//0xCC881608
	PE_O26_CC2_PE1_VSPYC_CTRL_03_T                       pe1_vspyc_ctrl_03;	//0xCC88160C
	PE_O26_CC2_PE1_VSPYC_CTRL_04_T                       pe1_vspyc_ctrl_04;	//0xCC881610
	PE_O26_CC2_PE1_VSPYC_CTRL_05_T                       pe1_vspyc_ctrl_05;	//0xCC881614
	PE_O26_CC2_PE1_VSPYC_CTRL_06_T                       pe1_vspyc_ctrl_06;	//0xCC881618
	PE_O26_CC2_PE1_VSPYC_CTRL_07_T                       pe1_vspyc_ctrl_07;	//0xCC88161C
	PE_O26_CC2_PE1_VSPYC_CTRL_08_T                       pe1_vspyc_ctrl_08;	//0xCC881620
	PE_O26_CC2_PE1_VSPYC_CTRL_09_T                       pe1_vspyc_ctrl_09;	//0xCC881624
	UINT32                                                       reserved0;	//0xCC881628
	UINT32                                                       reserved1;	//0xCC88162C
	PE_O26_CC2_PE1_VSP_CC_CTRL_00_T                     pe1_vsp_cc_ctrl_00;	//0xCC881630
	UINT32                                                       reserved2;	//0xCC881634
	UINT32                                                       reserved3;	//0xCC881638
	UINT32                                                       reserved4;	//0xCC88163C
	UINT32                                                       reserved5;	//0xCC881640
	PE_O26_CC2_PE1_VSP_CC_CTRL_05_T                     pe1_vsp_cc_ctrl_05;	//0xCC881644
	UINT32                                                       reserved6;	//0xCC881648
	UINT32                                                       reserved7;	//0xCC88164C
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xCC881650
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xCC881654
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xCC881658
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xCC88165C
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xCC881660
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xCC881664
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xCC881668
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xCC88166C
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xCC881670
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xCC881674
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xCC881678
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xCC88167C
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xCC881680
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xCC881684
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xCC881688
	PE_O26_CC2_PE1_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xCC88168C
	UINT32                                                       reserved8;	//0xCC881690
	UINT32                                                       reserved9;	//0xCC881694
	UINT32                                                      reserved10;	//0xCC881698
	UINT32                                                      reserved11;	//0xCC88169C
	PE_O26_CC2_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xCC8816A0
	PE_O26_CC2_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xCC8816A4
	PE_O26_CC2_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xCC8816A8
	UINT32                                                      reserved12;	//0xCC8816AC
	PE_O26_CC2_PE1_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xCC8816B0
	PE_O26_CC2_PE1_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xCC8816B4
	PE_O26_CC2_PE1_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xCC8816B8
	UINT32                                                      reserved13;	//0xCC8816BC
	PE_O26_CC2_PE1_CW_CRGN_CTRL_00_T                   pe1_cw_crgn_ctrl_00;	//0xCC8816C0
	PE_O26_CC2_PE1_CW_CRGN_CTRL_01_T                   pe1_cw_crgn_ctrl_01;	//0xCC8816C4
	PE_O26_CC2_PE1_CW_CRGN_CTRL_02_T                   pe1_cw_crgn_ctrl_02;	//0xCC8816C8
	PE_O26_CC2_PE1_CW_CRGN_CTRL_03_T                   pe1_cw_crgn_ctrl_03;	//0xCC8816CC
	PE_O26_CC2_PE1_CW_CRGN_CTRL_04_T                   pe1_cw_crgn_ctrl_04;	//0xCC8816D0
	PE_O26_CC2_PE1_CW_CRGN_CTRL_05_T                   pe1_cw_crgn_ctrl_05;	//0xCC8816D4
	PE_O26_CC2_PE1_CW_CRGN_CTRL_06_T                   pe1_cw_crgn_ctrl_06;	//0xCC8816D8
	PE_O26_CC2_PE1_CW_CRGN_CTRL_07_T                   pe1_cw_crgn_ctrl_07;	//0xCC8816DC
	PE_O26_CC2_PE1_CW_CRGN_CTRL_08_T                   pe1_cw_crgn_ctrl_08;	//0xCC8816E0
	PE_O26_CC2_PE1_CW_CRGN_CTRL_09_T                   pe1_cw_crgn_ctrl_09;	//0xCC8816E4
	PE_O26_CC2_PE1_CW_CRGN_CTRL_10_T                   pe1_cw_crgn_ctrl_10;	//0xCC8816E8
	PE_O26_CC2_PE1_CW_CRGN_CTRL_11_T                   pe1_cw_crgn_ctrl_11;	//0xCC8816EC
	PE_O26_CC2_PE1_CW_CRGN_CTRL_12_T                   pe1_cw_crgn_ctrl_12;	//0xCC8816F0
	PE_O26_CC2_PE1_CW_CRGN_CTRL_13_T                   pe1_cw_crgn_ctrl_13;	//0xCC8816F4
	PE_O26_CC2_PE1_CW_CRGN_CTRL_14_T                   pe1_cw_crgn_ctrl_14;	//0xCC8816F8
	PE_O26_CC2_PE1_CW_CRGN_CTRL_15_T                   pe1_cw_crgn_ctrl_15;	//0xCC8816FC
	UINT32                                                      reserved14;	//0xCC881700
	UINT32                                                      reserved15;	//0xCC881704
	UINT32                                                      reserved16;	//0xCC881708
	UINT32                                                      reserved17;	//0xCC88170C
	PE_O26_CC2_PE1_LBLUR_CTRL_00_T                       pe1_lblur_ctrl_00;	//0xCC881710
	PE_O26_CC2_PE1_LBLUR_CTRL_01_T                       pe1_lblur_ctrl_01;	//0xCC881714
	PE_O26_CC2_PE1_LBLUR_CTRL_02_T                       pe1_lblur_ctrl_02;	//0xCC881718
	UINT32                                                      reserved18;	//0xCC88171C
	PE_O26_CC2_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0xCC881720
	PE_O26_CC2_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0xCC881724
	PE_O26_CC2_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0xCC881728
	PE_O26_CC2_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0xCC88172C
	PE_O26_CC2_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0xCC881730
	PE_O26_CC2_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0xCC881734
	PE_O26_CC2_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0xCC881738
	PE_O26_CC2_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0xCC88173C
	PE_O26_CC2_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0xCC881740
	PE_O26_CC2_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0xCC881744
	PE_O26_CC2_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0xCC881748
	PE_O26_CC2_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0xCC88174C
	PE_O26_CC2_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0xCC881750
	PE_O26_CC2_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0xCC881754
	PE_O26_CC2_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0xCC881758
	PE_O26_CC2_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0xCC88175C
	PE_O26_CC2_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0xCC881760
	PE_O26_CC2_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0xCC881764
	PE_O26_CC2_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0xCC881768
	PE_O26_CC2_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0xCC88176C
	PE_O26_CC2_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0xCC881770
	PE_O26_CC2_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0xCC881774
	PE_O26_CC2_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0xCC881778
	PE_O26_CC2_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0xCC88177C
	PE_O26_CC2_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0xCC881780
	PE_O26_CC2_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0xCC881784
	PE_O26_CC2_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0xCC881788
	PE_O26_CC2_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0xCC88178C
	PE_O26_CC2_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0xCC881790
	PE_O26_CC2_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0xCC881794
	PE_O26_CC2_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0xCC881798
	PE_O26_CC2_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0xCC88179C
	PE_O26_CC2_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0xCC8817A0
	PE_O26_CC2_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0xCC8817A4
	PE_O26_CC2_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0xCC8817A8
	PE_O26_CC2_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0xCC8817AC
	PE_O26_CC2_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0xCC8817B0
	PE_O26_CC2_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0xCC8817B4
	PE_O26_CC2_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0xCC8817B8
	PE_O26_CC2_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0xCC8817BC
	PE_O26_CC2_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0xCC8817C0
	PE_O26_CC2_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0xCC8817C4
	PE_O26_CC2_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0xCC8817C8
	PE_O26_CC2_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0xCC8817CC
	PE_O26_CC2_PE1_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0xCC8817D0
	PE_O26_CC2_PE1_LOGO_CTRL_45_T                         pe1_logo_ctrl_45;	//0xCC8817D4
	PE_O26_CC2_PE1_LOGO_CTRL_46_T                         pe1_logo_ctrl_46;	//0xCC8817D8
	PE_O26_CC2_PE1_LOGO_CTRL_47_T                         pe1_logo_ctrl_47;	//0xCC8817DC
	PE_O26_CC2_PE1_LOGO_CTRL_48_T                         pe1_logo_ctrl_48;	//0xCC8817E0
	UINT32                                                      reserved19;	//0xCC8817E4
	UINT32                                                      reserved20;	//0xCC8817E8
	UINT32                                                      reserved21;	//0xCC8817EC
	UINT32                                                      reserved22;	//0xCC8817F0
	PE_O26_CC2_PE1_LOGO_CTRL_53_T                         pe1_logo_ctrl_53;	//0xCC8817F4
	PE_O26_CC2_PE1_LOGO_CTRL_54_T                         pe1_logo_ctrl_54;	//0xCC8817F8
	PE_O26_CC2_PE1_LOGO_CTRL_55_T                         pe1_logo_ctrl_55;	//0xCC8817FC
	PE_O26_CC2_PE1_LOGO_CTRL_56_T                         pe1_logo_ctrl_56;	//0xCC881800
	PE_O26_CC2_PE1_LOGO_CTRL_57_T                         pe1_logo_ctrl_57;	//0xCC881804
	PE_O26_CC2_PE1_LOGO_CTRL_58_T                         pe1_logo_ctrl_58;	//0xCC881808
	PE_O26_CC2_PE1_LOGO_CTRL_59_T                         pe1_logo_ctrl_59;	//0xCC88180C
	PE_O26_CC2_PE1_LOGO_CTRL_60_T                         pe1_logo_ctrl_60;	//0xCC881810
	UINT32                                                      reserved23;	//0xCC881814
	UINT32                                                      reserved24;	//0xCC881818
	UINT32                                                      reserved25;	//0xCC88181C
	PE_O26_CC2_PE1_GSR_CTRL_00_T                           pe1_gsr_ctrl_00;	//0xCC881820
	PE_O26_CC2_PE1_GSR_CTRL_01_T                           pe1_gsr_ctrl_01;	//0xCC881824
	PE_O26_CC2_PE1_GSR_CTRL_02_T                           pe1_gsr_ctrl_02;	//0xCC881828
	PE_O26_CC2_PE1_GSR_CTRL_03_T                           pe1_gsr_ctrl_03;	//0xCC88182C
	PE_O26_CC2_PE1_GSR_CTRL_04_T                           pe1_gsr_ctrl_04;	//0xCC881830
	PE_O26_CC2_PE1_GSR_CTRL_05_T                           pe1_gsr_ctrl_05;	//0xCC881834
	PE_O26_CC2_PE1_GSR_CTRL_06_T                           pe1_gsr_ctrl_06;	//0xCC881838
	PE_O26_CC2_PE1_GSR_CTRL_07_T                           pe1_gsr_ctrl_07;	//0xCC88183C
	PE_O26_CC2_PE1_GSR_CTRL_08_T                           pe1_gsr_ctrl_08;	//0xCC881840
	PE_O26_CC2_PE1_GSR_CTRL_09_T                           pe1_gsr_ctrl_09;	//0xCC881844
	PE_O26_CC2_PE1_GSR_CTRL_10_T                           pe1_gsr_ctrl_10;	//0xCC881848
	PE_O26_CC2_PE1_GSR_CTRL_11_T                           pe1_gsr_ctrl_11;	//0xCC88184C
	PE_O26_CC2_PE1_GSR_CTRL_12_T                           pe1_gsr_ctrl_12;	//0xCC881850
	PE_O26_CC2_PE1_GSR_CTRL_13_T                           pe1_gsr_ctrl_13;	//0xCC881854
	PE_O26_CC2_PE1_GSR_CTRL_14_T                           pe1_gsr_ctrl_14;	//0xCC881858
	PE_O26_CC2_PE1_GSR_CTRL_15_T                           pe1_gsr_ctrl_15;	//0xCC88185C
	PE_O26_CC2_PE1_GSR_CTRL_16_T                           pe1_gsr_ctrl_16;	//0xCC881860
	PE_O26_CC2_PE1_GSR_CTRL_17_T                           pe1_gsr_ctrl_17;	//0xCC881864
	PE_O26_CC2_PE1_GSR_CTRL_18_T                           pe1_gsr_ctrl_18;	//0xCC881868
	PE_O26_CC2_PE1_GSR_CTRL_19_T                           pe1_gsr_ctrl_19;	//0xCC88186C
	PE_O26_CC2_PE1_GSR_CTRL_20_T                           pe1_gsr_ctrl_20;	//0xCC881870
	PE_O26_CC2_PE1_GSR_CTRL_21_T                           pe1_gsr_ctrl_21;	//0xCC881874
	PE_O26_CC2_PE1_GSR_CTRL_22_T                           pe1_gsr_ctrl_22;	//0xCC881878
	PE_O26_CC2_PE1_GSR_CTRL_23_T                           pe1_gsr_ctrl_23;	//0xCC88187C
	PE_O26_CC2_PE1_GSR_CTRL_24_T                           pe1_gsr_ctrl_24;	//0xCC881880
	PE_O26_CC2_PE1_GSR_CTRL_25_T                           pe1_gsr_ctrl_25;	//0xCC881884
	PE_O26_CC2_PE1_GSR_CTRL_26_T                           pe1_gsr_ctrl_26;	//0xCC881888
	PE_O26_CC2_PE1_GSR_CTRL_27_T                           pe1_gsr_ctrl_27;	//0xCC88188C
	PE_O26_CC2_PE1_GSR_CTRL_28_T                           pe1_gsr_ctrl_28;	//0xCC881890
	PE_O26_CC2_PE1_GSR_CTRL_29_T                           pe1_gsr_ctrl_29;	//0xCC881894
	PE_O26_CC2_PE1_GSR_CTRL_30_T                           pe1_gsr_ctrl_30;	//0xCC881898
	PE_O26_CC2_PE1_GSR_CTRL_31_T                           pe1_gsr_ctrl_31;	//0xCC88189C
	PE_O26_CC2_PE1_GSR_CTRL_32_T                           pe1_gsr_ctrl_32;	//0xCC8818A0
	PE_O26_CC2_PE1_GSR_CTRL_33_T                           pe1_gsr_ctrl_33;	//0xCC8818A4
	UINT32                                                      reserved26;	//0xCC8818A8
	UINT32                                                      reserved27;	//0xCC8818AC
	UINT32                                                      reserved28;	//0xCC8818B0
	UINT32                                                      reserved29;	//0xCC8818B4
	UINT32                                                      reserved30;	//0xCC8818B8
	UINT32                                                      reserved31;	//0xCC8818BC
	UINT32                                                      reserved32;	//0xCC8818C0
	UINT32                                                      reserved33;	//0xCC8818C4
	UINT32                                                      reserved34;	//0xCC8818C8
	UINT32                                                      reserved35;	//0xCC8818CC
	UINT32                                                      reserved36;	//0xCC8818D0
	UINT32                                                      reserved37;	//0xCC8818D4
	UINT32                                                      reserved38;	//0xCC8818D8
	UINT32                                                      reserved39;	//0xCC8818DC
	PE_O26_CC2_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xCC8818E0
	PE_O26_CC2_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xCC8818E4
	PE_O26_CC2_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xCC8818E8
	PE_O26_CC2_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xCC8818EC
	PE_O26_CC2_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xCC8818F0
	PE_O26_CC2_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xCC8818F4
	PE_O26_CC2_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xCC8818F8
	PE_O26_CC2_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xCC8818FC
	PE_O26_CC2_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xCC881900
	PE_O26_CC2_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xCC881904
	PE_O26_CC2_PE1_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xCC881908
	PE_O26_CC2_PE1_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xCC88190C
	PE_O26_CC2_PE1_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xCC881910
	PE_O26_CC2_PE1_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xCC881914
	PE_O26_CC2_PE1_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xCC881918
	PE_O26_CC2_PE1_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xCC88191C
	PE_O26_CC2_PE1_MUTE_CTRL_16_T                         pe1_mute_ctrl_16;	//0xCC881920
	PE_O26_CC2_PE1_MUTE_CTRL_17_T                         pe1_mute_ctrl_17;	//0xCC881924
	PE_O26_CC2_PE1_MUTE_CTRL_18_T                         pe1_mute_ctrl_18;	//0xCC881928
	PE_O26_CC2_PE1_MUTE_CTRL_19_T                         pe1_mute_ctrl_19;	//0xCC88192C
	PE_O26_CC2_PE1_MUTE_CTRL_20_T                         pe1_mute_ctrl_20;	//0xCC881930
	PE_O26_CC2_PE1_MUTE_CTRL_21_T                         pe1_mute_ctrl_21;	//0xCC881934
	PE_O26_CC2_PE1_MUTE_CTRL_22_T                         pe1_mute_ctrl_22;	//0xCC881938
	PE_O26_CC2_PE1_MUTE_CTRL_23_T                         pe1_mute_ctrl_23;	//0xCC88193C
	UINT32                                                      reserved40;	//0xCC881940
	UINT32                                                      reserved41;	//0xCC881944
	UINT32                                                      reserved42;	//0xCC881948
	UINT32                                                      reserved43;	//0xCC88194C
	UINT32                                                      reserved44;	//0xCC881950
	UINT32                                                      reserved45;	//0xCC881954
	UINT32                                                      reserved46;	//0xCC881958
	UINT32                                                      reserved47;	//0xCC88195C
	UINT32                                                      reserved48;	//0xCC881960
	UINT32                                                      reserved49;	//0xCC881964
	UINT32                                                      reserved50;	//0xCC881968
	UINT32                                                      reserved51;	//0xCC88196C
	UINT32                                                      reserved52;	//0xCC881970
	UINT32                                                      reserved53;	//0xCC881974
	UINT32                                                      reserved54;	//0xCC881978
	UINT32                                                      reserved55;	//0xCC88197C
	UINT32                                                      reserved56;	//0xCC881980
	UINT32                                                      reserved57;	//0xCC881984
	UINT32                                                      reserved58;	//0xCC881988
	UINT32                                                      reserved59;	//0xCC88198C
	UINT32                                                      reserved60;	//0xCC881990
	UINT32                                                      reserved61;	//0xCC881994
	UINT32                                                      reserved62;	//0xCC881998
	UINT32                                                      reserved63;	//0xCC88199C
	UINT32                                                      reserved64;	//0xCC8819A0
	UINT32                                                      reserved65;	//0xCC8819A4
	UINT32                                                      reserved66;	//0xCC8819A8
	UINT32                                                      reserved67;	//0xCC8819AC
	UINT32                                                      reserved68;	//0xCC8819B0
	UINT32                                                      reserved69;	//0xCC8819B4
	UINT32                                                      reserved70;	//0xCC8819B8
	UINT32                                                      reserved71;	//0xCC8819BC
	UINT32                                                      reserved72;	//0xCC8819C0
	UINT32                                                      reserved73;	//0xCC8819C4
	UINT32                                                      reserved74;	//0xCC8819C8
	UINT32                                                      reserved75;	//0xCC8819CC
	UINT32                                                      reserved76;	//0xCC8819D0
	UINT32                                                      reserved77;	//0xCC8819D4
	UINT32                                                      reserved78;	//0xCC8819D8
	UINT32                                                      reserved79;	//0xCC8819DC
	UINT32                                                      reserved80;	//0xCC8819E0
	UINT32                                                      reserved81;	//0xCC8819E4
	UINT32                                                      reserved82;	//0xCC8819E8
	UINT32                                                      reserved83;	//0xCC8819EC
	UINT32                                                      reserved84;	//0xCC8819F0
	UINT32                                                      reserved85;	//0xCC8819F4
	UINT32                                                      reserved86;	//0xCC8819F8
	UINT32                                                      reserved87;	//0xCC8819FC
	PE_O26_CC2_PE1_LOGO_CTRL_61_T                         pe1_logo_ctrl_61;	//0xCC881A00
	PE_O26_CC2_PE1_LOGO_CTRL_62_T                         pe1_logo_ctrl_62;	//0xCC881A04
	PE_O26_CC2_PE1_LOGO_CTRL_63_T                         pe1_logo_ctrl_63;	//0xCC881A08
	PE_O26_CC2_PE1_LOGO_CTRL_64_T                         pe1_logo_ctrl_64;	//0xCC881A0C
	PE_O26_CC2_PE1_LOGO_CTRL_65_T                         pe1_logo_ctrl_65;	//0xCC881A10
	PE_O26_CC2_PE1_LOGO_CTRL_66_T                         pe1_logo_ctrl_66;	//0xCC881A14
	PE_O26_CC2_PE1_LOGO_CTRL_67_T                         pe1_logo_ctrl_67;	//0xCC881A18
	PE_O26_CC2_PE1_LOGO_CTRL_68_T                         pe1_logo_ctrl_68;	//0xCC881A1C
	PE_O26_CC2_PE1_LOGO_CTRL_69_T                         pe1_logo_ctrl_69;	//0xCC881A20
	PE_O26_CC2_PE1_LOGO_CTRL_70_T                         pe1_logo_ctrl_70;	//0xCC881A24
	PE_O26_CC2_PE1_LOGO_CTRL_71_T                         pe1_logo_ctrl_71;	//0xCC881A28
	PE_O26_CC2_PE1_LOGO_CTRL_72_T                         pe1_logo_ctrl_72;	//0xCC881A2C
	PE_O26_CC2_PE1_LOGO_CTRL_73_T                         pe1_logo_ctrl_73;	//0xCC881A30
	PE_O26_CC2_PE1_LOGO_CTRL_74_T                         pe1_logo_ctrl_74;	//0xCC881A34
	PE_O26_CC2_PE1_LOGO_CTRL_75_T                         pe1_logo_ctrl_75;	//0xCC881A38
	PE_O26_CC2_PE1_LOGO_CTRL_76_T                         pe1_logo_ctrl_76;	//0xCC881A3C
	PE_O26_CC2_PE1_LOGO_CTRL_77_T                         pe1_logo_ctrl_77;	//0xCC881A40
	PE_O26_CC2_PE1_LOGO_CTRL_78_T                         pe1_logo_ctrl_78;	//0xCC881A44
	PE_O26_CC2_PE1_LOGO_CTRL_79_T                         pe1_logo_ctrl_79;	//0xCC881A48
	PE_O26_CC2_PE1_LOGO_CTRL_80_T                         pe1_logo_ctrl_80;	//0xCC881A4C
	PE_O26_CC2_PE1_LOGO_CTRL_81_T                         pe1_logo_ctrl_81;	//0xCC881A50
	PE_O26_CC2_PE1_LOGO_CTRL_82_T                         pe1_logo_ctrl_82;	//0xCC881A54
	PE_O26_CC2_PE1_LOGO_CTRL_83_T                         pe1_logo_ctrl_83;	//0xCC881A58
	PE_O26_CC2_PE1_LOGO_CTRL_84_T                         pe1_logo_ctrl_84;	//0xCC881A5C
	PE_O26_CC2_PE1_LOGO_CTRL_85_T                         pe1_logo_ctrl_85;	//0xCC881A60
	PE_O26_CC2_PE1_LOGO_CTRL_86_T                         pe1_logo_ctrl_86;	//0xCC881A64
	PE_O26_CC2_PE1_LOGO_CTRL_87_T                         pe1_logo_ctrl_87;	//0xCC881A68
	PE_O26_CC2_PE1_LOGO_CTRL_88_T                         pe1_logo_ctrl_88;	//0xCC881A6C
	UINT32                                                      reserved88;	//0xCC881A70
	UINT32                                                      reserved89;	//0xCC881A74
	UINT32                                                      reserved90;	//0xCC881A78
	UINT32                                                      reserved91;	//0xCC881A7C
	UINT32                                                      reserved92;	//0xCC881A80
	UINT32                                                      reserved93;	//0xCC881A84
	UINT32                                                      reserved94;	//0xCC881A88
	UINT32                                                      reserved95;	//0xCC881A8C
	UINT32                                                      reserved96;	//0xCC881A90
	UINT32                                                      reserved97;	//0xCC881A94
	UINT32                                                      reserved98;	//0xCC881A98
	UINT32                                                      reserved99;	//0xCC881A9C
	PE_O26_CC2_PE1_MERGE_CTRL_00_T                       pe1_merge_ctrl_00;	//0xCC881AA0
	PE_O26_CC2_PE1_MERGE_CTRL_01_T                       pe1_merge_ctrl_01;	//0xCC881AA4
	PE_O26_CC2_PE1_MERGE_CTRL_02_T                       pe1_merge_ctrl_02;	//0xCC881AA8
	PE_O26_CC2_PE1_MERGE_CTRL_03_T                       pe1_merge_ctrl_03;	//0xCC881AAC
	PE_O26_CC2_PE1_MERGE_CTRL_04_T                       pe1_merge_ctrl_04;	//0xCC881AB0
	PE_O26_CC2_PE1_MERGE_CTRL_05_T                       pe1_merge_ctrl_05;	//0xCC881AB4
	PE_O26_CC2_PE1_MERGE_CTRL_06_T                       pe1_merge_ctrl_06;	//0xCC881AB8
	PE_O26_CC2_PE1_MERGE_CTRL_07_T                       pe1_merge_ctrl_07;	//0xCC881ABC
	PE_O26_CC2_PE1_MERGE_CTRL_08_T                       pe1_merge_ctrl_08;	//0xCC881AC0
	PE_O26_CC2_PE1_MERGE_CTRL_09_T                       pe1_merge_ctrl_09;	//0xCC881AC4
	PE_O26_CC2_PE1_MERGE_CTRL_10_T                       pe1_merge_ctrl_10;	//0xCC881AC8
	PE_O26_CC2_PE1_MERGE_CTRL_11_T                       pe1_merge_ctrl_11;	//0xCC881ACC
	PE_O26_CC2_PE1_MERGE_CTRL_12_T                       pe1_merge_ctrl_12;	//0xCC881AD0
	PE_O26_CC2_PE1_MERGE_CTRL_13_T                       pe1_merge_ctrl_13;	//0xCC881AD4
	PE_O26_CC2_PE1_MERGE_CTRL_14_T                       pe1_merge_ctrl_14;	//0xCC881AD8
	PE_O26_CC2_PE1_MERGE_CTRL_15_T                       pe1_merge_ctrl_15;	//0xCC881ADC
	PE_O26_CC2_PE1_MERGE_CTRL_16_T                       pe1_merge_ctrl_16;	//0xCC881AE0
	PE_O26_CC2_PE1_MERGE_CTRL_17_T                       pe1_merge_ctrl_17;	//0xCC881AE4
	PE_O26_CC2_PE1_MERGE_CTRL_18_T                       pe1_merge_ctrl_18;	//0xCC881AE8
	PE_O26_CC2_PE1_MERGE_CTRL_19_T                       pe1_merge_ctrl_19;	//0xCC881AEC
	PE_O26_CC2_PE1_MERGE_CTRL_20_T                       pe1_merge_ctrl_20;	//0xCC881AF0
	PE_O26_CC2_PE1_MERGE_CTRL_21_T                       pe1_merge_ctrl_21;	//0xCC881AF4
	PE_O26_CC2_PE1_MERGE_CTRL_22_T                       pe1_merge_ctrl_22;	//0xCC881AF8
	PE_O26_CC2_PE1_MERGE_CTRL_23_T                       pe1_merge_ctrl_23;	//0xCC881AFC
	PE_O26_CC2_PE1_MERGE_CTRL_24_T                       pe1_merge_ctrl_24;	//0xCC881B00
	PE_O26_CC2_PE1_MERGE_CTRL_25_T                       pe1_merge_ctrl_25;	//0xCC881B04
	PE_O26_CC2_PE1_MERGE_CTRL_26_T                       pe1_merge_ctrl_26;	//0xCC881B08
	PE_O26_CC2_PE1_MERGE_CTRL_27_T                       pe1_merge_ctrl_27;	//0xCC881B0C
	PE_O26_CC2_PE1_MERGE_CTRL_28_T                       pe1_merge_ctrl_28;	//0xCC881B10
	PE_O26_CC2_PE1_MERGE_CTRL_29_T                       pe1_merge_ctrl_29;	//0xCC881B14
	PE_O26_CC2_PE1_MERGE_CTRL_30_T                       pe1_merge_ctrl_30;	//0xCC881B18
	PE_O26_CC2_PE1_MERGE_CTRL_31_T                       pe1_merge_ctrl_31;	//0xCC881B1C
	PE_O26_CC2_PE1_MERGE_CTRL_32_T                       pe1_merge_ctrl_32;	//0xCC881B20
	PE_O26_CC2_PE1_MERGE_CTRL_33_T                       pe1_merge_ctrl_33;	//0xCC881B24
	PE_O26_CC2_PE1_MERGE_CTRL_34_T                       pe1_merge_ctrl_34;	//0xCC881B28
	PE_O26_CC2_PE1_MERGE_CTRL_35_T                       pe1_merge_ctrl_35;	//0xCC881B2C
	PE_O26_CC2_PE1_MERGE_CTRL_36_T                       pe1_merge_ctrl_36;	//0xCC881B30
	PE_O26_CC2_PE1_MERGE_CTRL_37_T                       pe1_merge_ctrl_37;	//0xCC881B34
	PE_O26_CC2_PE1_MERGE_CTRL_38_T                       pe1_merge_ctrl_38;	//0xCC881B38
	PE_O26_CC2_PE1_MERGE_CTRL_39_T                       pe1_merge_ctrl_39;	//0xCC881B3C
	PE_O26_CC2_PE1_MERGE_CTRL_40_T                       pe1_merge_ctrl_40;	//0xCC881B40
	PE_O26_CC2_PE1_MERGE_CTRL_41_T                       pe1_merge_ctrl_41;	//0xCC881B44
	PE_O26_CC2_PE1_MERGE_CTRL_42_T                       pe1_merge_ctrl_42;	//0xCC881B48
	PE_O26_CC2_PE1_MERGE_CTRL_43_T                       pe1_merge_ctrl_43;	//0xCC881B4C
	PE_O26_CC2_PE1_MERGE_CTRL_44_T                       pe1_merge_ctrl_44;	//0xCC881B50
	PE_O26_CC2_PE1_MERGE_CTRL_45_T                       pe1_merge_ctrl_45;	//0xCC881B54
	PE_O26_CC2_PE1_MERGE_CTRL_46_T                       pe1_merge_ctrl_46;	//0xCC881B58
	PE_O26_CC2_PE1_MERGE_CTRL_47_T                       pe1_merge_ctrl_47;	//0xCC881B5C
	PE_O26_CC2_PE1_MERGE_CTRL_48_T                       pe1_merge_ctrl_48;	//0xCC881B60
	PE_O26_CC2_PE1_MERGE_CTRL_49_T                       pe1_merge_ctrl_49;	//0xCC881B64
	PE_O26_CC2_PE1_MERGE_CTRL_50_T                       pe1_merge_ctrl_50;	//0xCC881B68
	PE_O26_CC2_PE1_MERGE_CTRL_51_T                       pe1_merge_ctrl_51;	//0xCC881B6C
	PE_O26_CC2_PE1_MERGE_CTRL_52_T                       pe1_merge_ctrl_52;	//0xCC881B70
	PE_O26_CC2_PE1_MERGE_CTRL_53_T                       pe1_merge_ctrl_53;	//0xCC881B74
	PE_O26_CC2_PE1_MERGE_CTRL_54_T                       pe1_merge_ctrl_54;	//0xCC881B78
	PE_O26_CC2_PE1_MERGE_CTRL_55_T                       pe1_merge_ctrl_55;	//0xCC881B7C
	PE_O26_CC2_PE1_MERGE_CTRL_56_T                       pe1_merge_ctrl_56;	//0xCC881B80
	PE_O26_CC2_PE1_MERGE_CTRL_57_T                       pe1_merge_ctrl_57;	//0xCC881B84
	PE_O26_CC2_PE1_MERGE_CTRL_58_T                       pe1_merge_ctrl_58;	//0xCC881B88
	PE_O26_CC2_PE1_MERGE_CTRL_59_T                       pe1_merge_ctrl_59;	//0xCC881B8C
	PE_O26_CC2_PE1_MERGE_CTRL_60_T                       pe1_merge_ctrl_60;	//0xCC881B90
	PE_O26_CC2_PE1_MERGE_CTRL_61_T                       pe1_merge_ctrl_61;	//0xCC881B94
	PE_O26_CC2_PE1_MERGE_CTRL_62_T                       pe1_merge_ctrl_62;	//0xCC881B98
	PE_O26_CC2_PE1_MERGE_CTRL_63_T                       pe1_merge_ctrl_63;	//0xCC881B9C
	PE_O26_CC2_PE1_MERGE_CTRL_64_T                       pe1_merge_ctrl_64;	//0xCC881BA0
	PE_O26_CC2_PE1_MERGE_CTRL_65_T                       pe1_merge_ctrl_65;	//0xCC881BA4
	PE_O26_CC2_PE1_MERGE_CTRL_66_T                       pe1_merge_ctrl_66;	//0xCC881BA8
	PE_O26_CC2_PE1_MERGE_CTRL_67_T                       pe1_merge_ctrl_67;	//0xCC881BAC
	PE_O26_CC2_PE1_MERGE_CTRL_68_T                       pe1_merge_ctrl_68;	//0xCC881BB0
	PE_O26_CC2_PE1_MERGE_CTRL_69_T                       pe1_merge_ctrl_69;	//0xCC881BB4
	PE_O26_CC2_PE1_MERGE_CTRL_70_T                       pe1_merge_ctrl_70;	//0xCC881BB8
	PE_O26_CC2_PE1_MERGE_CTRL_71_T                       pe1_merge_ctrl_71;	//0xCC881BBC
	PE_O26_CC2_PE1_MERGE_CTRL_72_T                       pe1_merge_ctrl_72;	//0xCC881BC0
	PE_O26_CC2_PE1_MERGE_CTRL_73_T                       pe1_merge_ctrl_73;	//0xCC881BC4
	PE_O26_CC2_PE1_MERGE_CTRL_74_T                       pe1_merge_ctrl_74;	//0xCC881BC8
}PE_CC2_PE1_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882300 RW 0x0000_0000
		UINT32				mRunStat	: 4;	// [0:3]	Main Status
		UINT32				mInfo		: 10;	// [4:13]	Main Info
		UINT32				sInfo		: 10;	// [14:23]	Sub Info
		UINT32				dbReq		: 4;	// [24:27]	DB Request
		UINT32				sRunStat	: 4;	// [28:31]	Sub Status
	};
}PE_O26_CCO_VERI_F22_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882304 RW 0x0000_0000
	UINT32 posd_w                   :16;	//15:0	//
	UINT32 posd_h                   :16;	//31:16	//
	};
}PE_O26_CCO_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882308 RW 0x0000_0000
	UINT32 bFbdevInitDone               :1;	//0:0
	UINT32 reserved0					:3;	//3:1
	UINT32 bOsdVReverseOn               :1;	//4:4
	UINT32 reserved1					:3;	//7:5
	UINT32 bEStreamerOn                 :1;	//8:8
	UINT32 reserved2					:3;	//11:9
	UINT32 bFw4KOSDOn                   :1;	//12:12
	UINT32 reserved3                    :19;	//31:13
	};
}PE_O26_OSDINFO_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88230C RW 0x0000_0000
	UINT32 bFwOsdOrbitInitDone          :1;	//0:0
	UINT32 reserved0					:3;	//3:1
	UINT32 bFwOsdSrInitDone             :1;	//4:4
	UINT32 reserved1					:27;	//31:5
	};
}PE_O26_OSDINFO_FW_TO_DRIVER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882310 RW 0x0000_0000
	UINT32 update                   :1;		//(0:0,RW,0x0000_0000) //
	UINT32 reserved                 :31;	//(31:1,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_WCG_UPDATE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882314 RW 0x0000_0000
	UINT32 retention_risk_second            :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882318 RW 0x0000_0000
	UINT32 head_apl                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 body_apl                   :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88231C RW 0x0000_0000
	UINT32 head_map                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 depth_map                  :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_SYS_VERI_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882320 RW 0x0000_0000
	UINT32 contrast                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 brightness                 :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_SYS_VERI_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882324 RW 0x0000_0000
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_O26_CCO_VERI_SYS_VERI_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882328 RW 0x0000_0000
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
}PE_O26_CCO_VERI_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88232C RW 0x0000_0000
	UINT32 frate_in							:8;		//(7:0)		input frame rate
	UINT32 frate_out  		                :8;		//(15:8)	output frame rate
	UINT32 frate_vrr  		                :16;	//(31:16)	vrr input frame rate
	};
}PE_O26_CCO_VERI_SYS_VERI_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882330 RW 0x0000_0000
	UINT32 xoffset					:16; //  0:15
	UINT32 enable					:1;   // 16:16 
	UINT32 yoffset					:15;    // 17:31
	};
}PE_O26_ESTINFO0_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882334 RW 0x0000_0000
	UINT32 crop_x                   :16;	// 0:15
	UINT32 crop_y					:16;	// 31:16
	};
}PE_O26_ESTINFO1_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882338 RW 0x0000_0000
	UINT32 crop_w					:16;	// 0:15
	UINT32 crop_h					:16;	// 31:16
	};
}PE_O26_ESTINFO2_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88233C RW 0x0000_0000
    UINT32 pcc_eotf_en                      :1;    //(0,NA,0x0) //
    UINT32 pcc_eotf_bit_extection_mode      :2;    //(2:1,NA,0x0) //
    UINT32 resvd0                           :2;
    UINT32 pcc_oetf_en                      :1;    //(5,NA,0x0) //
    UINT32 resvd1                           :2;
    UINT32 reg_pcc_en                       :1;    //(8,NA,0x0) //
    UINT32 resvd2                           :3;
    UINT32 reg_dither_en                    :1;    //(12,NA,0x0) //
    UINT32 resvd3                           :3;
    UINT32 reg_dither_temporal_en           :1;    //(16,NA,0x0) //
    UINT32 resvd4                           :3;
    UINT32 reg_sat_lut_in_mux               :1;    //(20,NA,0x0) //Saturatio alpha LUT input 0:pcc_input, 1:pcc_output
    UINT32 reg_l3d_in_mux                   :1;    //(21,NA,0x0) //3DLUT input 0:pcc_output, 1:pcc_input
    UINT32 reg_sat_blend_in_mux             :1;    //(22,NA,0x0) //Saturatio alpha blend input 0:pcc_output, 1:pcc_input
    UINT32 resvd5                           :1;
    UINT32 update_count						:8;
    };
}PE_O26_CCO_VERI_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882340 RW 0x0000_0000
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882344 RW 0x0000_0000
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882348 RW 0x0000_0000
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88234C RW 0x0000_0000
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882350 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882354 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882358 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88235C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882360 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882364 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882368 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88236C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_O26_CCO_VERI_SYS_VERI_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882370 RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CCO_VERI_SYS_VERI_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882374 RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CCO_VERI_SYS_VERI_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882378 RW 0x0000_0000
	UINT32 reg_irr_info                  	:32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O26_CCO_VERI_SYS_VERI_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88237C RW 0x0000_0000
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882380 RW 0x0000_0000
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882384 RW 0x0000_0000
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882388 RW 0x0000_0000
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}PE_O26_CCO_VERI_SYS_VERI_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88238C RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_x7              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x6              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x5              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x4              :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CCO_VERI_SYS_VERI_35_T;

typedef struct {
	PE_O26_CCO_VERI_F22_STATUS_T                                f22_status;	//0xCC882300
	PE_O26_CCO_VERI_SYS_VERI_1_T                                   posd_wh;	//0xCC882304
	PE_O26_OSDINFO_DRIVER_TO_FW_T                     osdinfo_driver_to_fw;	//0xCC882308
	PE_O26_OSDINFO_FW_TO_DRIVER_T                     osdinfo_fw_to_driver;	//0xCC88230C
	PE_O26_CCO_VERI_WCG_UPDATE_T                                wcg_update;	//0xCC882310
	PE_O26_CCO_VERI_SYS_VERI_5_T                     retention_risk_second;	//0xCC882314
	PE_O26_CCO_VERI_SYS_VERI_6_T                             apl_upload_db;	//0xCC882318
	PE_O26_CCO_VERI_SYS_VERI_7_T                         map_apl_upload_db;	//0xCC88231C
	PE_O26_CCO_VERI_SYS_VERI_8_T                     contast_brightness_db;	//0xCC882320
	PE_O26_CCO_VERI_SYS_VERI_9_T                            dc_chroma_gain;	//0xCC882324
	PE_O26_CCO_VERI_SYS_VERI_10_T                         video_delay_sts0;	//0xCC882328
	PE_O26_CCO_VERI_SYS_VERI_11_T                         video_delay_sts1;	//0xCC88232C
	PE_O26_ESTINFO0_DRIVER_TO_FW_T                   estinfo0_driver_to_fw;	//0xCC882330
	PE_O26_ESTINFO1_DRIVER_TO_FW_T                   estinfo1_driver_to_fw;	//0xCC882334
	PE_O26_ESTINFO2_DRIVER_TO_FW_T                   estinfo2_driver_to_fw;	//0xCC882338
	PE_O26_CCO_VERI_PE_PCC_CTRL_T                              pe_pcc_ctrl;	//0xCC88233C
	PE_O26_CCO_VERI_SYS_VERI_16_T                          sat_phdr_gain_0;	//0xCC882340
	PE_O26_CCO_VERI_SYS_VERI_17_T                          sat_phdr_gain_1;	//0xCC882344
	PE_O26_CCO_VERI_SYS_VERI_18_T                          sat_phdr_gain_2;	//0xCC882348
	PE_O26_CCO_VERI_SYS_VERI_19_T                          sat_phdr_gain_3;	//0xCC88234C
	PE_O26_CCO_VERI_SYS_VERI_20_T                          acc_face_area_0;	//0xCC882350
	PE_O26_CCO_VERI_SYS_VERI_21_T                          acc_face_area_1;	//0xCC882354
	PE_O26_CCO_VERI_SYS_VERI_22_T                          acc_face_area_2;	//0xCC882358
	PE_O26_CCO_VERI_SYS_VERI_23_T                          acc_face_area_3;	//0xCC88235C
	PE_O26_CCO_VERI_SYS_VERI_24_T                          acc_face_area_4;	//0xCC882360
	PE_O26_CCO_VERI_SYS_VERI_25_T                          acc_face_area_5;	//0xCC882364
	PE_O26_CCO_VERI_SYS_VERI_26_T                          acc_face_area_6;	//0xCC882368
	PE_O26_CCO_VERI_SYS_VERI_27_T                          acc_face_area_7;	//0xCC88236C
	PE_O26_CCO_VERI_SYS_VERI_28_T                          sat_phdr_gain_8;	//0xCC882370
	PE_O26_CCO_VERI_SYS_VERI_29_T                          sat_phdr_gain_9;	//0xCC882374
	PE_O26_CCO_VERI_SYS_VERI_30_T                             reg_irr_info;	//0xCC882378
	PE_O26_CCO_VERI_SYS_VERI_31_T                          sat_phdr_gain_4;	//0xCC88237C
	PE_O26_CCO_VERI_SYS_VERI_32_T                          sat_phdr_gain_5;	//0xCC882380
	PE_O26_CCO_VERI_SYS_VERI_33_T                              sys_veri_33;	//0xCC882384
	PE_O26_CCO_VERI_SYS_VERI_34_T                              sys_veri_34;	//0xCC882388
	PE_O26_CCO_VERI_SYS_VERI_35_T                              sys_veri_35;	//0xCC88238C
}PE_CCO_VERI_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882000 RW 0x6F00_0870
	UINT32 reg_hei                          :12;	//(11:0,RW,0x870) //4k: 2160
	UINT32 resvd0                           :1;
	UINT32 reg_mode_2ch                     :1;	//(13,RW,0x0) //
	UINT32 dither_temporal_en               :1;	//(14,RW,0x0) //
	UINT32 dither_en                        :1;	//(15,RW,0x0) //input dither enable for 11b -> 10b	processing order: (input dither: dither_en) --> (11b -> 10b : reg_decon_in_bit_opt)
	UINT32 reg_wid                          :12;	//(27:16,RW,0xF00) //4k: 3840
	UINT32 resvd1                           :1;
	UINT32 reg_decon_out_bit_opt            :1;	//(29,RW,0x1) //1: [10:0] , 0: {1'b0, [10:1]}
	UINT32 reg_decon_in_bit_opt             :1;	//(30,RW,0x1) //11b -> 10b ( 1: [10:1] , 0: [9:0] )	should be 1 when dither_en = 1
	UINT32 reg_decon_detour_en              :1;	//(31,RW,0x0) //1: detour
	};
}PE_O26_CCO_DECON_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882004 RW 200FF000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//(1,RW,0x0) //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0xFF) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x2) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882008 RW 0x0000_0001
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x1) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88200C RW 0x0000_0FFF
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882010 RW 0x00FF_FFFF
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882014 RW 0x1357_9753
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x1357_9753) //
	};
}PE_O26_CCO_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882018 RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x2468_0864) //
	};
}PE_O26_CCO_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88201C RW 0x1470_3692
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x1470_3692) //
	};
}PE_O26_CCO_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882020 RW 0x000F_F040
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x4) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0xFF) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882024 RW 0x3000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x3) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882028 RW 0x0000_0FFF
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88202C RW 0x00FF_FFFF
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882030 RW 0x1357_9753
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x1357_9753) //
	};
}PE_O26_CCO_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882034 RW 0x2468_0864
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x2468_0864) //
	};
}PE_O26_CCO_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882038 RW 0x1470_3692
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x1470_3692) //
	};
}PE_O26_CCO_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88203C RW 0x1357_9753
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//(31:0,RW,0x1357_9753) //
	};
}PE_O26_CCO_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882040 RW 0x2468_0864
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//(31:0,RW,0x2468_0864) //
	};
}PE_O26_CCO_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882044 RW 0x1470_3692
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//(31:0,RW,0x1470_3692) //
	};
}PE_O26_CCO_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882048 RW 0x0243_0042
	UINT32 reg_blur_lb_var_cut_res          :4;	//(3:0,RW,0x2) //>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//(6,RW,0x1) //
	UINT32 reg_l6_var_2x2_bit               :1;	//(7,RW,0x0) //1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//(13:8,RW,0x0) //NOT IN USE in O26
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 reg_l6_var_csc_en                :1;	//(15,RW,0x1) //default =1
	UINT32 reg_force_block_no_h             :6;	//(21:16,RW,0x0) //NOT IN USE in O26
	UINT32 reg_4k_5x3_mode_en               :1;	//(22,RW,0x1) //0: 5x5(u2, u1, cc, d1, d2)	1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//(24,RW,0x0) //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x1) //default =1
	UINT32 reg_1st_debug_mode               :4;	//(29:26,RW,0x0) //0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: aux_luma	15: input_blur
	UINT32 reg_force_block_no_en            :1;	//(30,RW,0x0) //NOT IN USE in O26
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88204C RW 0x3250_06A7
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x1) //
	UINT32 reg_low_gain_en                  :1;	//(1,RW,0x1) //Low gain(var, diff, var, aux_luma) enable	Debug mode is same
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x0) //NOT IN USE IN O26	always set to 0 (2x2 mode deleted)
	UINT32 resvd0                           :1;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x0) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x1) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x3) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20
	UINT32 resvd1                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //NOT IN USE in O26	0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //NOT IN USE in O26	0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //NOT IN USE in O26	0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //NOT IN USE in O26	0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x5) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x2) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x3) //
	};
}PE_O26_CCO_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882050 RW 0x190F_0A07
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x7) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0xA) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0xF) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x19) //
	};
}PE_O26_CCO_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882054 RW 0x0020_80FF
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0xFF) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x80) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x20) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882058 RW 0x0100_C080
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x30) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x10) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88205C RW 0x1004_0080
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882060 RW 0x0200_003C
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x20) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882064 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882068 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88206C RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882070 RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882074 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //
	UINT32 sync_i_h_sel                     :1;	//(16,RW,0x0) //
	UINT32 sync_i_v_sel                     :1;	//(17,RW,0x0) //
	UINT32 sync_i_inv_ha                    :1;	//(18,RW,0x0) //
	UINT32 sync_i_inv_va                    :1;	//(19,RW,0x0) //
	UINT32 sync_o_sel_ha                    :1;	//(20,RW,0x0) //
	UINT32 sync_o_sel_va                    :1;	//(21,RW,0x0) //
	UINT32 sync_o_sel_hs                    :1;	//(22,RW,0x0) //
	UINT32 sync_o_sel_vs                    :1;	//(23,RW,0x0) //
	UINT32 tp_update_hv_zero                :1;	//(24,RW,0x0) //
	UINT32 force_out_ha                     :1;	//(25,RW,0x0) //
	UINT32 force_out_va                     :1;	//(26,RW,0x0) //
	UINT32 force_out_hs                     :1;	//(27,RW,0x0) //
	UINT32 manual_cnt_h_value_en            :1;	//(28,RW,0x0) //
	UINT32 manual_cnt_v_value_en            :1;	//(29,RW,0x0) //
	UINT32 force_out_vs                     :1;	//(30,RW,0x0) //
	UINT32 update_force                     :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882078 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88207C RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882080 RW 0x00028000
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x00) //CCO DEC delay control
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //CCO DEC delay control
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //CCO DEC delay control
	UINT32 reg_ha_seamless                  :1;	//(31:31,RW,0x0) //CCO DEC delay control
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882084 RW 0x00028000
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x00) //CCO DEC delay control
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //CCO DEC delay control
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //CCO DEC delay control
	UINT32 reg_hs_seamless                  :1;	//(31:31,RW,0x0) //CCO DEC delay control
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882088 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88208C RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_O26_CCO_DEC_SYNC_2DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882090 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882094 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882098 RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88209C RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A0 RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A4 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A8 RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820AC RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B0 RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B4 RW 0x0000_0000
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}PE_O26_CCO_DECON_WINCTRL_ODD_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CCO_DEC_SYNC_3DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820BC RW 0x0643_212C
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x12C) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0xC8) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x64) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C0 RW 0x190C_8384
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x384) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x320) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x190) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C4 RW 0x3E81_8080
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x60) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x3E8) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C8 RW 0x0A04_0200
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x200) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0xA0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820CC RW 0x1804_0080
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x080) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x180) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820D0 RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,RW,0x0) //64 when 3440x144	(10'd32 for 1366x768)
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,RW,0x0) //64 when 3440x1440	(10'd32 for 1366x768)
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //3 when 3440x144	(10'd24 for 1366x768)
	UINT32 resvd2                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //(10'd54 when 3440x1440) 	(10'd43 for 1366x768)
	UINT32 resvd3                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //1 when abnormal size
	};
}PE_O26_CCO_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820D4 RW 0x4224_0000
	UINT32 reg_last_block_size_v            :7;	//(6:0,RW,0x0) //16 when 3440x144	(10'd32 for 1366x768)
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//(14:8,RW,0x0) //48 when 3440x1440	(10'd22 for 1366x768)
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//(19:16,RW,0x4) //
	UINT32 reg_diff_shift                   :3;	//(22:20,RW,0x2) //
	UINT32 reg_osd_run_mode                 :1;	//(23,RW,0x0) //
	UINT32 resvd2                           :1;
	UINT32 reg_alpha_blur_mode              :2;	//(26:25,RW,0x1) //0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 resvd3                           :2;
	UINT32 reg_diff_use_seldiff             :1;	//(29,RW,0x0) //dfault always set to 0, no in use in abnormal size
	UINT32 resvd4                           :2;
	};
}PE_O26_CCO_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820D8 RW 0xFF27_8064
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x64) //
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x1E0) //
	UINT32 reg_lb_var_cut_res               :4;	//(23:20,RW,0x2) //
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_CCO_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820DC RW 0xC002_0100
	UINT32 reg_l6_var_x_th2                 :10;	//(9:0,RW,0x100) //
	UINT32 reg_l6_var_x_th1                 :10;	//(19:10,RW,0x80) //
	UINT32 reg_l6_var_x_th0                 :10;	//(29:20,RW,0x0) //
	UINT32 reg_lb_var_opt                   :1;	//(30,RW,0x1) //cco_decon_variance opt
	UINT32 reg_lb_var_en                    :1;	//(31,RW,0x1) //cco_decon_variance enable
	};
}PE_O26_CCO_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820E0 RW 0xA000_0080
	UINT32 reg_l6_var_y_th1                 :10;	//(9:0,RW,0x80) //
	UINT32 reg_l6_var_y_th0                 :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_x_th3                 :10;	//(29:20,RW,0x200) //
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//(31,RW,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820E4 RW 0x2994_0200
	UINT32 reg_l6_var_y_th3                 :10;	//(9:0,RW,0x200) //
	UINT32 reg_l6_var_y_th2                 :10;	//(19:10,RW,0x100) //
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x1) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x2) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x1) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x2) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x2) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820E8 RW 0x1357_9753
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x1357_9753) //
	};
}PE_O26_CCO_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820EC RW 0x2468_0864
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x2468_0864) //
	};
}PE_O26_CCO_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F0 RW 0x1470_3692
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x1470_3692) //
	};
}PE_O26_CCO_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F4 RW 0x2004_0040
	UINT32 reg_rd_min_pel_cb                :12;	//(11:0,RW,0x40) //
	UINT32 reg_rd_min_pel_yy                :12;	//(23:12,RW,0x40) //
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//(30:28,RW,0x2) //
	UINT32 reg_decon_rd_on                  :1;	//(31,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F8 RW 0x0004_07FF
	UINT32 reg_rd_max_pel_yy                :12;	//(11:0,RW,0x7FF) //
	UINT32 reg_rd_min_pel_cr                :12;	//(23:12,RW,0x40) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820FC RW 0x007F_F7FF
	UINT32 reg_rd_max_pel_cr                :12;	//(11:0,RW,0x7FF) //
	UINT32 reg_rd_max_pel_cb                :12;	//(23:12,RW,0x7FF) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882100 RW 0x1357_9753
	UINT32 reg_rd_init_yy                   :32;	//(31:0,RW,0x1357_9753) //
	};
}PE_O26_CCO_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882104 RW 0x2468_0864
	UINT32 reg_rd_init_cb                   :32;	//(31:0,RW,0x2468_0864) //
	};
}PE_O26_CCO_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882108 RW 0x1470_3692
	UINT32 reg_rd_init_cr                   :32;	//(31:0,RW,0x1470_3692) //
	};
}PE_O26_CCO_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88210C RW 0x0104_080F
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0xF) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x8) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x4) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882110 RW 0xFF10_0500
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x5) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x10) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_CCO_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882114 RW 0xB003_1040
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x40) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x31) //
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x1) //
	UINT32 reg_blur2_sim_en                 :1;	//(29,RW,0x1) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882118 RW 0x4871_B399
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x399) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x71B) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x2) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x2) //
	};
}PE_O26_CCO_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88211C RW 0x1050_6478
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x78) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x64) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x50) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x10) //
	};
}PE_O26_CCO_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882120 RW 0xFF31_0A01
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x1) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0xA) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x31) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_CCO_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882124 RW 0x143C_6EC8
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x14) //
	};
}PE_O26_CCO_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882128 RW 0x5064_788C
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x8C) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x78) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x50) //
	};
}PE_O26_CCO_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88212C RW 0x7882_B4C8
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x82) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x78) //
	};
}PE_O26_CCO_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882130 RW 0x00C8_C800
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0xC8) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882134 RW 0x0020_4080
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x40) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x20) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882138 RW 0x0040_80FF
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0xFF) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x80) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x40) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88213C RW 0x8FF0_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0xFF) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882140 RW 0x0000_0044
	UINT32 reg_l6_var_diff_dist_h           :4;	//(3:0,RW,0x4) //
	UINT32 reg_l6_var_diff_dist_w           :4;	//(7:4,RW,0x4) //
	UINT32 resvd                            :24;
	};
}PE_O26_CCO_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882144 RW 0x00E0_380E
	UINT32 reg_l6_var_diff_th_cr            :10;	//(9:0,RW,0xE) //
	UINT32 reg_l6_var_diff_th_cb            :10;	//(19:10,RW,0xE) //
	UINT32 reg_l6_var_diff_th_yy            :10;	//(29:20,RW,0xE) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882148 RW 0x0000_C850
	UINT32 reg_l6_var_diff_th_yy3           :10;	//(9:0,RW,0x50) //
	UINT32 reg_l6_var_diff_th_yy2           :10;	//(19:10,RW,0x32) //
	UINT32 resvd                            :12;
	};
}PE_O26_CCO_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88214C RW 0x01E0_780A
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//(9:0,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//(19:10,RW,0x1E) //
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//(29:20,RW,0x1E) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882150 RW 0x80A0_280A
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//(9:0,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//(19:10,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//(29:20,RW,0xA) //
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//(31,RW,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882154 RW 0x2020_2080
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//(7:0,RW,0x80) //
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//(15:8,RW,0x20) //
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//(23:16,RW,0x20) //
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//(31:24,RW,0x20) //
	};
}PE_O26_CCO_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882158 RW 0x8020_8080
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//(7:0,RW,0x80) //
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//(15:8,RW,0x80) //
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//(23:16,RW,0x20) //
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//(31:24,RW,0x80) //
	};
}PE_O26_CCO_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88215C RW 0x80FF_FF00
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//(23:16,RW,0xFF) //
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//(31:24,RW,0x80) //
	};
}PE_O26_CCO_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882160 RW 0x0020_0200
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_v_diff_th             :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882164 RW 0x0020_0200
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_h_diff_th             :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882168 RW 0x0020_0200
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_total_diff_max_th     :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88216C RW 0x0003_2000
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_low_th     :12;	//(23:12,RW,0x32) //
	UINT32 resvd                            :8;
	};
}PE_O26_CCO_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882170 RW 0x7000_0033
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x1) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x1) //0: rd_roi off, 1: rd_roi on, also applies in 1ST_DECON_RD
	UINT32 resvd1                           :1;
	};
}PE_O26_CCO_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882174 RW 0x0000_087F
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CCO_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882178 RW 0x0029_083F
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
}PE_O26_CCO_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88217C RW 0x0001_0060
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x60) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0x40) //2nd rd에도 동일하게 사용
	UINT32 resvd                            :12;
	};
}PE_O26_CCO_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882180 RW 0x0002_00A0
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0xA0) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x80) //2nd rd에도 동일하게 사용
	UINT32 resvd                            :12;
	};
}PE_O26_CCO_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882184 RW 0x000C_0100
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0xC0) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882188 RW 0x0012_0180
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0x180) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x120) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88218C RW 0x0000_0008
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882190 RW 0x0002_0080
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0x80) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x20) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882194 RW 0x000A_0180
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x180) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0xA0) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882198 RW 0x0020_03FF
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0x200) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_O26_CCO_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88219C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CCO_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O26_CCO_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821A4 RW 0x0000_0000
	UINT32 reg_2nd_var_x_th1                :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
}PE_O26_CCO_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821A8 RW 0x0000_0000
	UINT32 reg_boundary_x_end               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_boundary_x_start             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_boundary_side                :1;	//(30,NA,0x0) //0: left, 1: right
	UINT32 reg_boundary_en                  :1;	//(31,NA,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821AC RW 0x4020_1008
	UINT32 reg_decon_low_diff_x_th0         :8;	//(7:0,NA,0x8) //
	UINT32 reg_decon_low_diff_x_th1         :8;	//(15:8,NA,0x10) //
	UINT32 reg_decon_low_diff_x_th2         :8;	//(23:16,NA,0x20) //
	UINT32 reg_decon_low_diff_x_th3         :8;	//(31:24,NA,0x40) //
	};
}PE_O26_CCO_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B0 RW 0x0080_A0C0
	UINT32 reg_decon_low_diff_y_th0         :8;	//(7:0,NA,0xC0) //
	UINT32 reg_decon_low_diff_y_th1         :8;	//(15:8,NA,0xA0) //
	UINT32 reg_decon_low_diff_y_th2         :8;	//(23:16,NA,0x80) //
	UINT32 reg_decon_low_diff_y_th3         :8;	//(31:24,NA,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B4 RW 0x0201_0060
	UINT32 reg_decon_low_var_x_th2          :10;	//(9:0,NA,0x60) //
	UINT32 reg_decon_low_var_x_th1          :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_low_var_x_th0          :10;	//(29:20,NA,0x20) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B8 RW 0x0806_0100
	UINT32 reg_decon_low_var_y_th1          :10;	//(9:0,NA,0x100) //
	UINT32 reg_decon_low_var_y_th0          :10;	//(19:10,NA,0x180) //
	UINT32 reg_decon_low_var_x_th3          :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821BC RW 0x0801_0040
	UINT32 reg_decon_low_luma_x_th0         :10;	//(9:0,NA,0x40) //
	UINT32 reg_decon_low_var_y_th3          :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_low_var_y_th2          :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C0 RW 0x0501_C0A0
	UINT32 reg_decon_low_luma_x_th3         :10;	//(9:0,NA,0xA0) //
	UINT32 reg_decon_low_luma_x_th2         :10;	//(19:10,NA,0x70) //
	UINT32 reg_decon_low_luma_x_th1         :10;	//(29:20,NA,0x50) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C4 RW 0x0C04_0180
	UINT32 reg_decon_low_luma_x_th6         :10;	//(9:0,NA,0x180) //
	UINT32 reg_decon_low_luma_x_th5         :10;	//(19:10,NA,0x100) //
	UINT32 reg_decon_low_luma_x_th4         :10;	//(29:20,NA,0xC0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C8 RW 0x2000_2020
	UINT32 reg_decon_low_luma_y_th1         :10;	//(9:0,NA,0x20) //
	UINT32 reg_decon_low_luma_y_th0         :10;	//(19:10,NA,0x8) //
	UINT32 reg_decon_low_luma_x_th7         :10;	//(29:20,NA,0x200) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821CC RW 0x0402_00A0
	UINT32 reg_decon_low_luma_y_th4         :10;	//(9:0,NA,0xA0) //
	UINT32 reg_decon_low_luma_y_th3         :10;	//(19:10,NA,0x80) //
	UINT32 reg_decon_low_luma_y_th2         :10;	//(29:20,NA,0x40) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D0 RW 0x0FF6_03FF
	UINT32 reg_decon_low_luma_y_th7         :10;	//(9:0,NA,0x3FF) //
	UINT32 reg_decon_low_luma_y_th6         :10;	//(19:10,NA,0x180) //
	UINT32 reg_decon_low_luma_y_th5         :10;	//(29:20,NA,0xFF) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D4 RW 0xC401_8080
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,NA,0x80) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,NA,0x60) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,NA,0x40) //
	UINT32 reg_low_aux_luma_en              :1;	//(30,NA,0x1) //
	UINT32 reg_aux_luma_en                  :1;	//(31,NA,0x1) //
	};
}PE_O26_CCO_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D8 RW 0x0A03_00FF
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,NA,0xFF) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,NA,0xC0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,NA,0xA0) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821DC RW 0x1004_8010
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,NA,0x10) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,NA,0x120) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,NA,0x100) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E0 RW 0x0202_00C0
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,NA,0xC0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,NA,0x80) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,NA,0x20) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E4 RW 0x1FFB_FF00
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,NA,0x300) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,NA,0x2FF) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,NA,0x1FF) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E8 RW 0x3FF1_0050
	UINT32 reg_decon_low_aux_luma_x_th1     :10;	//(9:0,NA,0x50) //
	UINT32 reg_decon_low_aux_luma_x_th0     :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(29:20,NA,0x3FF) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821EC RW 0x0601_C080
	UINT32 reg_decon_low_aux_luma_x_th4     :10;	//(9:0,NA,0x80) //
	UINT32 reg_decon_low_aux_luma_x_th3     :10;	//(19:10,NA,0x70) //
	UINT32 reg_decon_low_aux_luma_x_th2     :10;	//(29:20,NA,0x60) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F0 RW 0x0902_80B0
	UINT32 reg_decon_low_aux_luma_x_th7     :10;	//(9:0,NA,0xB0) //
	UINT32 reg_decon_low_aux_luma_x_th6     :10;	//(19:10,NA,0xA0) //
	UINT32 reg_decon_low_aux_luma_x_th5     :10;	//(29:20,NA,0x90) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F4 RW 0x0100_8040
	UINT32 reg_decon_low_aux_luma_y_th2     :10;	//(9:0,NA,0x40) //
	UINT32 reg_decon_low_aux_luma_y_th1     :10;	//(19:10,NA,0x20) //
	UINT32 reg_decon_low_aux_luma_y_th0     :10;	//(29:20,NA,0x10) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F8 RW 0x0802_C0FF
	UINT32 reg_decon_low_aux_luma_y_th5     :10;	//(9:0,NA,0xFF) //
	UINT32 reg_decon_low_aux_luma_y_th4     :10;	//(19:10,NA,0xB0) //
	UINT32 reg_decon_low_aux_luma_y_th3     :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}PE_O26_CCO_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821FC RW 0x1FFB_FCFF
	UINT32 reg_low_master_gain              :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :2;
	UINT32 reg_decon_low_aux_luma_y_th7     :10;	//(19:10,NA,0x2FF) //
	UINT32 reg_decon_low_aux_luma_y_th6     :10;	//(29:20,NA,0x1FF) //
	UINT32 resvd1                           :2;
	};
}PE_O26_CCO_DECON_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882200 RW 0x0100_0222
	UINT32 reg_rpi_diff_shift_cr            :2;	//(1:0,NA,0x2) //
	UINT32 resvd0                           :2;
	UINT32 reg_rpi_diff_shift_cb            :2;	//(5:4,NA,0x2) //
	UINT32 resvd1                           :2;
	UINT32 reg_rpi_diff_shift_yy            :2;	//(9:8,NA,0x2) //3x3 Replace-Pel-based-Interpolation difference calculation shift bit
	UINT32 resvd2                           :10;
	UINT32 reg_pel_diff_rgb2y_mode_en       :1;	//(20,NA,0x0) //
	UINT32 resvd3                           :3;
	UINT32 reg_avg_en                       :1;	//(24,NA,0x1) //average mode enable
	UINT32 resvd4                           :3;
	UINT32 reg_rpi_en                       :1;	//(28,NA,0x0) //Replace Pel based Interpolation enable
	UINT32 resvd5                           :3;
	};
}PE_O26_CCO_DECON_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882204 RW 0x2030_C4D8
	UINT32 reg_lut_blur_base_luma_x_3       :8;	//(7:0,NA,0xD8) //
	UINT32 reg_lut_blur_base_luma_x_2       :8;	//(15:8,NA,0xC4) //
	UINT32 reg_lut_blur_base_luma_x_1       :8;	//(23:16,NA,0x30) //
	UINT32 reg_lut_blur_base_luma_x_0       :8;	//(31:24,NA,0x20) //
	};
}PE_O26_CCO_DECON_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882208 RW 0x0408_0B10
	UINT32 reg_lut_blur_base_luma_y_3       :8;	//(7:0,NA,0x10) //
	UINT32 reg_lut_blur_base_luma_y_2       :8;	//(15:8,NA,0xB) //
	UINT32 reg_lut_blur_base_luma_y_1       :8;	//(23:16,NA,0x8) //
	UINT32 reg_lut_blur_base_luma_y_0       :8;	//(31:24,NA,0x4) //
	};
}PE_O26_CCO_DECON_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88220C RW 0x1100_0000
	UINT32 resvd0                           :24;
	UINT32 light_csc_mode_rd_2              :1;	//(24,NA,0x1) //light_csc_mode for random diffusion 2
	UINT32 resvd1                           :3;
	UINT32 light_csc_mode_rd_1              :1;	//(28,NA,0x1) //light_csc_mode for random diffusion 1
	UINT32 resvd2                           :3;
	};
}PE_O26_CCO_DECON_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882210 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,NA,0x0) //
	};
}PE_O26_CCO_DECON_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882214 RW 0x0000_0000
	UINT32 win0_en                          :1;	//(0,NA,0x0) //1:  select only window0 as active area
	UINT32 win1_en                          :1;	//(1,NA,0x0) //1:  select only window1 as active area
	UINT32 win2_en                          :1;	//(2,NA,0x0) //1:  select only window2 as active area
	UINT32 win3_en                          :1;	//(3,NA,0x0) //1:  select only window3 as active area
	UINT32 resvd                            :2;
	UINT32 win_outside                      :1;	//(6,NA,0x0) //0: use inside of selected area by win0 and win1	1: use the other side of selected area by win0 and win1
	UINT32 win_en                           :1;	//(7,NA,0x0) //0: active area = full screen	1: active area = specified by (window0 or window1)
	UINT32 bdr_alpha                        :5;	//(12:8,NA,0x0) //border alpha for alpha-blending
	UINT32 bdr_wid                          :2;	//(14:13,NA,0x0) //border width
	UINT32 bdr_en                           :1;	//(15:15,NA,0x0) //border enable
	UINT32 cr5                              :5;	//(20:16,NA,0x0) //border color : cr5
	UINT32 cb5                              :5;	//(25:21,NA,0x0) //border color : cb5
	UINT32 yy6                              :6;	//(31:26,NA,0x0) //border color : yy6
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882218 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88221C RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882220 RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882224 RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882228 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88222C RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882230 RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882234 RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882238 RW 0x0000_00E4
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}PE_O26_CCO_DECON_WINCTRL_EVN_9_T;

typedef struct {
	PE_O26_CCO_DECON_TOP_CTRL_T                 reg_decon_top_ctrl;	//0xCC882000
	PE_O26_CCO_DECON_CTRL_0_T                     reg_decon_ctrl_0;	//0xCC882004
	PE_O26_CCO_DECON_CTRL_1_T                     reg_decon_ctrl_1;	//0xCC882008
	PE_O26_CCO_DECON_CTRL_2_T                     reg_decon_ctrl_2;	//0xCC88200C
	PE_O26_CCO_DECON_CTRL_3_T                     reg_decon_ctrl_3;	//0xCC882010
	PE_O26_CCO_DECON_CTRL_4_T                     reg_decon_ctrl_4;	//0xCC882014
	PE_O26_CCO_DECON_CTRL_5_T                     reg_decon_ctrl_5;	//0xCC882018
	PE_O26_CCO_DECON_CTRL_6_T                     reg_decon_ctrl_6;	//0xCC88201C
	PE_O26_CCO_DECON_CTRL_7_T                     reg_decon_ctrl_7;	//0xCC882020
	PE_O26_CCO_DECON_CTRL_8_T                     reg_decon_ctrl_8;	//0xCC882024
	PE_O26_CCO_DECON_CTRL_9_T                     reg_decon_ctrl_9;	//0xCC882028
	PE_O26_CCO_DECON_CTRL_10_T                   reg_decon_ctrl_10;	//0xCC88202C
	PE_O26_CCO_DECON_CTRL_11_T                   reg_decon_ctrl_11;	//0xCC882030
	PE_O26_CCO_DECON_CTRL_12_T                   reg_decon_ctrl_12;	//0xCC882034
	PE_O26_CCO_DECON_CTRL_13_T                   reg_decon_ctrl_13;	//0xCC882038
	PE_O26_CCO_DECON_CTRL_14_T                   reg_decon_ctrl_14;	//0xCC88203C
	PE_O26_CCO_DECON_CTRL_15_T                   reg_decon_ctrl_15;	//0xCC882040
	PE_O26_CCO_DECON_CTRL_16_T                   reg_decon_ctrl_16;	//0xCC882044
	PE_O26_CCO_DECON_CTRL_17_T                   reg_decon_ctrl_17;	//0xCC882048
	PE_O26_CCO_DECON_CTRL_18_T                   reg_decon_ctrl_18;	//0xCC88204C
	PE_O26_CCO_DECON_CTRL_19_T                   reg_decon_ctrl_19;	//0xCC882050
	PE_O26_CCO_DECON_CTRL_20_T                   reg_decon_ctrl_20;	//0xCC882054
	PE_O26_CCO_DECON_CTRL_21_T                   reg_decon_ctrl_21;	//0xCC882058
	PE_O26_CCO_DECON_CTRL_22_T                   reg_decon_ctrl_22;	//0xCC88205C
	PE_O26_CCO_DECON_CTRL_23_T                   reg_decon_ctrl_23;	//0xCC882060
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL0_T       reg_dec_sync_2dly_ctrl0;	//0xCC882064
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL1_T       reg_dec_sync_2dly_ctrl1;	//0xCC882068
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL2_T       reg_dec_sync_2dly_ctrl2;	//0xCC88206C
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL3_T       reg_dec_sync_2dly_ctrl3;	//0xCC882070
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL4_T       reg_dec_sync_2dly_ctrl4;	//0xCC882074
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL5_T       reg_dec_sync_2dly_ctrl5;	//0xCC882078
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL6_T       reg_dec_sync_2dly_ctrl6;	//0xCC88207C
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL7_T       reg_dec_sync_2dly_ctrl7;	//0xCC882080
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL8_T       reg_dec_sync_2dly_ctrl8;	//0xCC882084
	PE_O26_CCO_DEC_SYNC_2DLY_CTRL9_T       reg_dec_sync_2dly_ctrl9;	//0xCC882088
	PE_O26_CCO_DEC_SYNC_2DLY_CTRLA_T       reg_dec_sync_2dly_ctrla;	//0xCC88208C
	PE_O26_CCO_DECON_WINCTRL_ODD_0_T       reg_decon_winctrl_odd_0;	//0xCC882090
	PE_O26_CCO_DECON_WINCTRL_ODD_1_T       reg_decon_winctrl_odd_1;	//0xCC882094
	PE_O26_CCO_DECON_WINCTRL_ODD_2_T       reg_decon_winctrl_odd_2;	//0xCC882098
	PE_O26_CCO_DECON_WINCTRL_ODD_3_T       reg_decon_winctrl_odd_3;	//0xCC88209C
	PE_O26_CCO_DECON_WINCTRL_ODD_4_T       reg_decon_winctrl_odd_4;	//0xCC8820A0
	PE_O26_CCO_DECON_WINCTRL_ODD_5_T       reg_decon_winctrl_odd_5;	//0xCC8820A4
	PE_O26_CCO_DECON_WINCTRL_ODD_6_T       reg_decon_winctrl_odd_6;	//0xCC8820A8
	PE_O26_CCO_DECON_WINCTRL_ODD_7_T       reg_decon_winctrl_odd_7;	//0xCC8820AC
	PE_O26_CCO_DECON_WINCTRL_ODD_8_T       reg_decon_winctrl_odd_8;	//0xCC8820B0
	PE_O26_CCO_DECON_WINCTRL_ODD_9_T       reg_decon_winctrl_odd_9;	//0xCC8820B4
	PE_O26_CCO_DEC_SYNC_3DLY_CTRLA_T       reg_dec_sync_3dly_ctrla;	//0xCC8820B8
	PE_O26_CCO_DECON_CTRL_24_T                   reg_decon_ctrl_24;	//0xCC8820BC
	PE_O26_CCO_DECON_CTRL_25_T                   reg_decon_ctrl_25;	//0xCC8820C0
	PE_O26_CCO_DECON_CTRL_26_T                   reg_decon_ctrl_26;	//0xCC8820C4
	PE_O26_CCO_DECON_CTRL_27_T                   reg_decon_ctrl_27;	//0xCC8820C8
	PE_O26_CCO_DECON_CTRL_28_T                   reg_decon_ctrl_28;	//0xCC8820CC
	PE_O26_CCO_DECON_CTRL_29_T                   reg_decon_ctrl_29;	//0xCC8820D0
	PE_O26_CCO_DECON_CTRL_30_T                   reg_decon_ctrl_30;	//0xCC8820D4
	PE_O26_CCO_DECON_CTRL_31_T                   reg_decon_ctrl_31;	//0xCC8820D8
	PE_O26_CCO_DECON_CTRL_32_T                   reg_decon_ctrl_32;	//0xCC8820DC
	PE_O26_CCO_DECON_CTRL_33_T                   reg_decon_ctrl_33;	//0xCC8820E0
	PE_O26_CCO_DECON_CTRL_34_T                   reg_decon_ctrl_34;	//0xCC8820E4
	PE_O26_CCO_DECON_CTRL_35_T                   reg_decon_ctrl_35;	//0xCC8820E8
	PE_O26_CCO_DECON_CTRL_36_T                   reg_decon_ctrl_36;	//0xCC8820EC
	PE_O26_CCO_DECON_CTRL_37_T                   reg_decon_ctrl_37;	//0xCC8820F0
	PE_O26_CCO_DECON_CTRL_38_T                   reg_decon_ctrl_38;	//0xCC8820F4
	PE_O26_CCO_DECON_CTRL_39_T                   reg_decon_ctrl_39;	//0xCC8820F8
	PE_O26_CCO_DECON_CTRL_40_T                   reg_decon_ctrl_40;	//0xCC8820FC
	PE_O26_CCO_DECON_CTRL_41_T                   reg_decon_ctrl_41;	//0xCC882100
	PE_O26_CCO_DECON_CTRL_42_T                   reg_decon_ctrl_42;	//0xCC882104
	PE_O26_CCO_DECON_CTRL_43_T                   reg_decon_ctrl_43;	//0xCC882108
	PE_O26_CCO_DECON_CTRL_44_T                   reg_decon_ctrl_44;	//0xCC88210C
	PE_O26_CCO_DECON_CTRL_45_T                   reg_decon_ctrl_45;	//0xCC882110
	PE_O26_CCO_DECON_CTRL_46_T                   reg_decon_ctrl_46;	//0xCC882114
	PE_O26_CCO_DECON_CTRL_47_T                   reg_decon_ctrl_47;	//0xCC882118
	PE_O26_CCO_DECON_CTRL_48_T                   reg_decon_ctrl_48;	//0xCC88211C
	PE_O26_CCO_DECON_CTRL_49_T                   reg_decon_ctrl_49;	//0xCC882120
	PE_O26_CCO_DECON_CTRL_50_T                   reg_decon_ctrl_50;	//0xCC882124
	PE_O26_CCO_DECON_CTRL_51_T                   reg_decon_ctrl_51;	//0xCC882128
	PE_O26_CCO_DECON_CTRL_52_T                   reg_decon_ctrl_52;	//0xCC88212C
	PE_O26_CCO_DECON_CTRL_53_T                   reg_decon_ctrl_53;	//0xCC882130
	PE_O26_CCO_DECON_CTRL_54_T                   reg_decon_ctrl_54;	//0xCC882134
	PE_O26_CCO_DECON_CTRL_55_T                   reg_decon_ctrl_55;	//0xCC882138
	PE_O26_CCO_DECON_CTRL_56_T                   reg_decon_ctrl_56;	//0xCC88213C
	PE_O26_CCO_DECON_CTRL_57_T                   reg_decon_ctrl_57;	//0xCC882140
	PE_O26_CCO_DECON_CTRL_58_T                   reg_decon_ctrl_58;	//0xCC882144
	PE_O26_CCO_DECON_CTRL_59_T                   reg_decon_ctrl_59;	//0xCC882148
	PE_O26_CCO_DECON_CTRL_60_T                   reg_decon_ctrl_60;	//0xCC88214C
	PE_O26_CCO_DECON_CTRL_61_T                   reg_decon_ctrl_61;	//0xCC882150
	PE_O26_CCO_DECON_CTRL_62_T                   reg_decon_ctrl_62;	//0xCC882154
	PE_O26_CCO_DECON_CTRL_63_T                   reg_decon_ctrl_63;	//0xCC882158
	PE_O26_CCO_DECON_CTRL_64_T                   reg_decon_ctrl_64;	//0xCC88215C
	PE_O26_CCO_DECON_CTRL_65_T                   reg_decon_ctrl_65;	//0xCC882160
	PE_O26_CCO_DECON_CTRL_66_T                   reg_decon_ctrl_66;	//0xCC882164
	PE_O26_CCO_DECON_CTRL_67_T                   reg_decon_ctrl_67;	//0xCC882168
	PE_O26_CCO_DECON_CTRL_68_T                   reg_decon_ctrl_68;	//0xCC88216C
	PE_O26_CCO_DECON_CTRL_69_T                   reg_decon_ctrl_69;	//0xCC882170
	PE_O26_CCO_DECON_CTRL_70_T                   reg_decon_ctrl_70;	//0xCC882174
	PE_O26_CCO_DECON_CTRL_71_T                   reg_decon_ctrl_71;	//0xCC882178
	PE_O26_CCO_DECON_CTRL_72_T                   reg_decon_ctrl_72;	//0xCC88217C
	PE_O26_CCO_DECON_CTRL_73_T                   reg_decon_ctrl_73;	//0xCC882180
	PE_O26_CCO_DECON_CTRL_74_T                   reg_decon_ctrl_74;	//0xCC882184
	PE_O26_CCO_DECON_CTRL_75_T                   reg_decon_ctrl_75;	//0xCC882188
	PE_O26_CCO_DECON_CTRL_76_T                   reg_decon_ctrl_76;	//0xCC88218C
	PE_O26_CCO_DECON_CTRL_77_T                   reg_decon_ctrl_77;	//0xCC882190
	PE_O26_CCO_DECON_CTRL_78_T                   reg_decon_ctrl_78;	//0xCC882194
	PE_O26_CCO_DECON_CTRL_79_T                   reg_decon_ctrl_79;	//0xCC882198
	PE_O26_CCO_DECON_CTRL_80_T                   reg_decon_ctrl_80;	//0xCC88219C
	PE_O26_CCO_DECON_CTRL_81_T                   reg_decon_ctrl_81;	//0xCC8821A0
	PE_O26_CCO_DECON_CTRL_82_T                   reg_decon_ctrl_82;	//0xCC8821A4
	PE_O26_CCO_DECON_CTRL_83_T                   reg_decon_ctrl_83;	//0xCC8821A8
	PE_O26_CCO_DECON_CTRL_84_T                   reg_decon_ctrl_84;	//0xCC8821AC
	PE_O26_CCO_DECON_CTRL_85_T                   reg_decon_ctrl_85;	//0xCC8821B0
	PE_O26_CCO_DECON_CTRL_86_T                   reg_decon_ctrl_86;	//0xCC8821B4
	PE_O26_CCO_DECON_CTRL_87_T                   reg_decon_ctrl_87;	//0xCC8821B8
	PE_O26_CCO_DECON_CTRL_88_T                   reg_decon_ctrl_88;	//0xCC8821BC
	PE_O26_CCO_DECON_CTRL_89_T                   reg_decon_ctrl_89;	//0xCC8821C0
	PE_O26_CCO_DECON_CTRL_90_T                   reg_decon_ctrl_90;	//0xCC8821C4
	PE_O26_CCO_DECON_CTRL_91_T                   reg_decon_ctrl_91;	//0xCC8821C8
	PE_O26_CCO_DECON_CTRL_92_T                   reg_decon_ctrl_92;	//0xCC8821CC
	PE_O26_CCO_DECON_CTRL_93_T                   reg_decon_ctrl_93;	//0xCC8821D0
	PE_O26_CCO_DECON_CTRL_94_T                   reg_decon_ctrl_94;	//0xCC8821D4
	PE_O26_CCO_DECON_CTRL_95_T                   reg_decon_ctrl_95;	//0xCC8821D8
	PE_O26_CCO_DECON_CTRL_96_T                   reg_decon_ctrl_96;	//0xCC8821DC
	PE_O26_CCO_DECON_CTRL_97_T                   reg_decon_ctrl_97;	//0xCC8821E0
	PE_O26_CCO_DECON_CTRL_98_T                   reg_decon_ctrl_98;	//0xCC8821E4
	PE_O26_CCO_DECON_CTRL_99_T                   reg_decon_ctrl_99;	//0xCC8821E8
	PE_O26_CCO_DECON_CTRL_100_T                 reg_decon_ctrl_100;	//0xCC8821EC
	PE_O26_CCO_DECON_CTRL_101_T                 reg_decon_ctrl_101;	//0xCC8821F0
	PE_O26_CCO_DECON_CTRL_102_T                 reg_decon_ctrl_102;	//0xCC8821F4
	PE_O26_CCO_DECON_CTRL_103_T                 reg_decon_ctrl_103;	//0xCC8821F8
	PE_O26_CCO_DECON_CTRL_104_T                 reg_decon_ctrl_104;	//0xCC8821FC
	PE_O26_CCO_DECON_CTRL_105_T                 reg_decon_ctrl_105;	//0xCC882200
	PE_O26_CCO_DECON_CTRL_106_T                 reg_decon_ctrl_106;	//0xCC882204
	PE_O26_CCO_DECON_CTRL_107_T                 reg_decon_ctrl_107;	//0xCC882208
	PE_O26_CCO_DECON_CTRL_108_T                 reg_decon_ctrl_108;	//0xCC88220C
	PE_O26_CCO_DECON_CTRL_109_T                 reg_decon_ctrl_109;	//0xCC882210
	PE_O26_CCO_DECON_WINCTRL_EVN_0_T       reg_decon_winctrl_evn_0;	//0xCC882214
	PE_O26_CCO_DECON_WINCTRL_EVN_1_T       reg_decon_winctrl_evn_1;	//0xCC882218
	PE_O26_CCO_DECON_WINCTRL_EVN_2_T       reg_decon_winctrl_evn_2;	//0xCC88221C
	PE_O26_CCO_DECON_WINCTRL_EVN_3_T       reg_decon_winctrl_evn_3;	//0xCC882220
	PE_O26_CCO_DECON_WINCTRL_EVN_4_T       reg_decon_winctrl_evn_4;	//0xCC882224
	PE_O26_CCO_DECON_WINCTRL_EVN_5_T       reg_decon_winctrl_evn_5;	//0xCC882228
	PE_O26_CCO_DECON_WINCTRL_EVN_6_T       reg_decon_winctrl_evn_6;	//0xCC88222C
	PE_O26_CCO_DECON_WINCTRL_EVN_7_T       reg_decon_winctrl_evn_7;	//0xCC882230
	PE_O26_CCO_DECON_WINCTRL_EVN_8_T       reg_decon_winctrl_evn_8;	//0xCC882234
	PE_O26_CCO_DECON_WINCTRL_EVN_9_T       reg_decon_winctrl_evn_9;	//0xCC882238
}PE_CCO_DECON_REG_O26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880480 RW 0x0808_8000
	UINT32 reg_ord_en                       :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_ord_rand_en                  :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_blend_alpha                  :8;	//(15:8,RW,0x80) //
	UINT32 reg_round_shift                  :4;	//(19:16,RW,0x8) //
	UINT32 resvd2                           :4;
	UINT32 reg_resi_max                     :6;	//(29:24,RW,0x8) //
	UINT32 resvd3                           :2;
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880484 RW 0x0411_1133
	UINT32 reg_v_shift                      :3;	//(2:0,RW,0x3) //
	UINT32 resvd0                           :1;
	UINT32 reg_h_shift                      :3;	//(6:4,RW,0x3) //
	UINT32 resvd1                           :1;
	UINT32 reg_resi_v_over                  :6;	//(13:8,RW,0x11) //
	UINT32 resvd2                           :2;
	UINT32 reg_resi_h_over                  :6;	//(21:16,RW,0x11) //
	UINT32 resvd3                           :2;
	UINT32 reg_rand_number                  :6;	//(29:24,RW,0x4) //
	UINT32 resvd4                           :2;
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880488 RW 0x0F10_3FF2
	UINT32 reg_gyy_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88048C RW 0x0990_05F8
	UINT32 reg_gyy_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880490 RW 0x150A_E7C7
	UINT32 reg_gyy_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880494 RW 0x2B1A_0426
	UINT32 reg_bcb_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880498 RW 0x2B1A_0426
	UINT32 reg_bcb_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88049C RW 0x26D7_2F18
	UINT32 reg_bcb_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804A0 RW 0x12FD_7D1F
	UINT32 reg_rcr_eve_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804A4 RW 0x15CB_6694
	UINT32 reg_rcr_eve_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804A8 RW 0x1598_773A
	UINT32 reg_rcr_eve_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804AC RW 0x103E_5A6C
	UINT32 reg_gyy_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804B0 RW 0x027B_52B8
	UINT32 reg_gyy_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804B4 RW 0x1217_8949
	UINT32 reg_gyy_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804B8 RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804BC RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804C0 RW 0x12E8_6FC8
	UINT32 reg_bcb_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804C4 RW 0x3371_F0CB
	UINT32 reg_rcr_odd_hpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804C8 RW 0x2198_B54E
	UINT32 reg_rcr_odd_vpel_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8804CC RW 0x0DEC_AFE2
	UINT32 reg_rcr_odd_rand_lsfr_seed       :32;	//(31:00,RW,VNA) //
	};
}PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL19_T;

typedef struct {
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL00_T          reg_osd0_ord_ctrl00;	//0xCC880480
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL01_T          reg_osd0_ord_ctrl01;	//0xCC880484
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL02_T          reg_osd0_ord_ctrl02;	//0xCC880488
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL03_T          reg_osd0_ord_ctrl03;	//0xCC88048C
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL04_T          reg_osd0_ord_ctrl04;	//0xCC880490
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL05_T          reg_osd0_ord_ctrl05;	//0xCC880494
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL06_T          reg_osd0_ord_ctrl06;	//0xCC880498
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL07_T          reg_osd0_ord_ctrl07;	//0xCC88049C
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL08_T          reg_osd0_ord_ctrl08;	//0xCC8804A0
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL09_T          reg_osd0_ord_ctrl09;	//0xCC8804A4
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL10_T          reg_osd0_ord_ctrl10;	//0xCC8804A8
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL11_T          reg_osd0_ord_ctrl11;	//0xCC8804AC
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL12_T          reg_osd0_ord_ctrl12;	//0xCC8804B0
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL13_T          reg_osd0_ord_ctrl13;	//0xCC8804B4
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL14_T          reg_osd0_ord_ctrl14;	//0xCC8804B8
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL15_T          reg_osd0_ord_ctrl15;	//0xCC8804BC
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL16_T          reg_osd0_ord_ctrl16;	//0xCC8804C0
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL17_T          reg_osd0_ord_ctrl17;	//0xCC8804C4
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL18_T          reg_osd0_ord_ctrl18;	//0xCC8804C8
	PE_O26_OSD_IMAGE0_1_REG_OSD0_ORD_CTRL19_T          reg_osd0_ord_ctrl19;	//0xCC8804CC
}PE_OSD_ORD_REG_O26_T;

#endif
