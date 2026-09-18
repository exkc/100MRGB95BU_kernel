#ifndef _PE_CCO_REG_O22A0_H_
#define _PE_CCO_REG_O22A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC481000 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0' : load at vdpulse	'1' : load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0' : auto load:  load when reg. write	'1' : manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O22_CC_PE1_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481004 RW 0x10E0_0780
	UINT32 width                            :13;	//(12:0,NA,0x780) //width
	UINT32 resvd0                           :3;
	UINT32 height                           :13;	//(28:16,NA,0x10E0) //height
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481008 RW 0x0100_0A01
	UINT32 tpg_position                     :1;	//(0,NA,0x1) //0 := pe1 input	1  =  pe1 output
	UINT32 reg_pe1_cg_disable               :1;	//(1,NA,0x0) //clock gating disable
	UINT32 pe1_detour                       :1;	//(2,NA,0x0) //0': pe1 pass-through	'1': pe1 detour
	UINT32 resvd0                           :5;
	UINT32 vdpulse_pos                      :12;	//(19:8,NA,0xA) //vdpulse position for register loading
	UINT32 resvd1                           :4;
	UINT32 master_en                        :1;	//(24,NA,0x1) //PE1 master enable
	UINT32 resvd2                           :7;
	};
}PE_O22_CC_PE1_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48100C RO 0x0000_0000
	UINT32 vcnt                             :13;	//(12:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(13,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(14,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :1;
	UINT32 vcnt2                            :13;	//(28:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481010 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O22_CC_PE1_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481020 RW 0x0000_0000
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
}PE_O22_CC_PE1_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481024 RW 0x0000_0000
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
}PE_O22_CC_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481028 RW 0x0000_0000
	UINT32 reg_src_info                     :5;	//4:0	//Video Source Information	 2 : default/transition period	 3 : AV NTSC	 4 : AV PAL	 5 : HDMI_SD_i/p	 6 : HDMI_576_i/p	 7 : HDMI_HD_i	 8 : HDMI_HD_p	 9 : DTV_480_i	10 : DTV_576_i	11 : DTV_576_p	12 : DTV_HD_i	13 : DTV_HD_p	14 : RF_NTSC	15 : RF_PAL	16 : RF_PAL_M	17 : COMPONENT_1080_i	18 : COMPONENT_1080_p	19 : COMPONENT_480_i	20 : COMPONENT_480_p	21 : COMPONENT_576_i	22 : COMPONENT_576_p	23 : AV_SECAM	24 : RF_SECAM	25 : AV_ NTSC_443	26 : RF_NTSC_443	27 : AV_PAL_60	28 : SCART_RGB	29 : N.A.(abnormal) input	30 : NO SIG.
	UINT32 reg_src_freeze                   :1;	//5 //src freeze toggle '0' : normal '1' : freeze
	UINT32 reg_gsr_cpc_enable               :1;	//6 //gsr cpc enable
	UINT32 reserved				           : 1 ;  //	 7
	UINT32 ndskip  				           : 1 ;  //	 8
	UINT32 output_4k_mode   	           : 1 ;  //	 9 : 8k:0x0, 4k:0x1
	};
}PE_O22_CC_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48102C RW 0x0000_0000
	UINT32 picture_mode                           :32;
	};
}PE_O22_CC_PE1_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481030 RW 0x0000_0000
	UINT32 p_osd_addr_y                          :32;
	};
}PE_O22_CC_PE1_FSW_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481034 RW 0x0000_0000
	UINT32 p_osd_width                           :16;
	UINT32 p_osd_height							 :16;
	};
}PE_O22_CC_PE1_FSW_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481038 RW 0x0000_0000
	UINT32 p_osd_pos_x                           :16;
	UINT32 p_osd_valid							 :1;
	UINT32 resvd							 	 :15;
	};
}PE_O22_CC_PE1_FSW_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48103C RW 0x0000_0000
	UINT32 p_osd_update_cnt                       :32;
	};
}PE_O22_CC_PE1_FSW_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481050 RW 0x03C0_0000
	UINT32 tpg_enable                       :1;	//(0,NA,0x0) //TPG Enable
	UINT32 pattern_type                     :2;	//(2:1,NA,0x0) //Test Pattern Type	'00 := ColorPatch	'01 = Gradation
	UINT32 resvd0                           :1;
	UINT32 blend_alpha                      :4;	//(7:4,NA,0x0) //TPG Blend Alpha	0x0 ~ 0xF = SolidPattern ~ BypassBackgroundPicture
	UINT32 resvd1                           :8;
	UINT32 blt_size_x                       :13;	//(28:16,NA,0x3C0) //Pattern Blt Size X (1920d=>0x780)
	UINT32 resvd2                           :3;
	};
}PE_O22_CC_PE1_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481054 RW 0x10E0_0FA0
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
}PE_O22_CC_PE1_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481058 RW 0x0000_FFFF
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
}PE_O22_CC_PE1_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48105C RW 0x0000_0000
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
}PE_O22_CC_PE1_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481060 RW 0x0000_0000
	UINT32 bg_color_r                       :10;	//(9:0,NA,0x0) //outside color with RGB
	UINT32 bg_color_b                       :10;	//(19:10,NA,0x0) //
	UINT32 bg_color_g                       :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481064 WO 0x0000_0000
	UINT32 tpg_indir_addr                   :7;	//(6:0,NA,0x00) //TPG Indirect Address	0x00 ~ 0x0F = Patch Color	0x20 ~ 0x2F = Patch Start Position	0x40 ~ 0x4F = Patch End Position	0x60 ~ 0x63 = Gradation Start Color	0x64 ~ 0x67 = Gradation Step Color (signed)	0x68 ~ 0x6A = Gradation Region Size
	UINT32 resvd0                           :5;
	UINT32 tpg_indir_ai_en                  :1;	//(12,NA,0x0) //TPG Indirect Addressing Ctrl, AI Enable
	UINT32 resvd1                           :19;
	};
}PE_O22_CC_PE1_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481068 WO 0x0000_0000
	UINT32 tpg_indir_data                   :32;	//(31:0,NA,0x0) //TPG Indirect Access Data (Write Enable Triggered)	 When Addr is...	 0x00 ~ 0x0F = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x20 ~ 0x4F = (28:16):X_position, (12:0):Y_position	 0x60 ~ 0x67 = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x68 ~ 0x6A = (12:0):position
	};
}PE_O22_CC_PE1_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481070 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_0                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0 for ch0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_0                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0 for ch0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481074 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_0                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_0                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481078 RW 0x0000_0000
	UINT32 apl_position                     :2;	//(1:0,NA,0x0) //00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :2;
	UINT32 reg_apl_enable                   :1;	//(4,NA,0x1) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :3;
	UINT32 act_win_mode                     :1;	//(8,NA,0x0) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd2                           :23;
	};
}PE_O22_CC_PE1_APL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48107C RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_1                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_1                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481080 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_1                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_1                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481084 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_2                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_2                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481088 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_2                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_2                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48108C RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_3                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_3                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481090 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_3                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_3                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_APL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810B4 RO 0x0000_0000
	UINT32 apl_cb                           :10;	//(9:0,NA,0x0) //APL Cb/B
	UINT32 apl_yg                           :10;	//(19:10,NA,0x0) //APL Y/G
	UINT32 apl_cr                           :10;	//(29:20,NA,0x0) //APL Cr/R
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810B8 RO 0x0000_0000
	UINT32 apl_cb_other_side                :10;	//(9:0,NA,0x0) //apl_cb(outside of apl_win)
	UINT32 apl_yg_other_side                :10;	//(19:10,NA,0x0) //apl_yg(outside of apl_win)
	UINT32 apl_cr_other_side                :10;	//(29:20,NA,0x0) //apl_cr(outside of apl_win)
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_APL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810C0 RW 0x0000_0000
	UINT32 r_2x3_coef1                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef0                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810C4 RW 0x0000_0000
	UINT32 r_2x3_coef3a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef2                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810C8 RW 0x0000_0000
	UINT32 r_2x3_coef5a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4a                     :15;	//(30:16,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810CC RW 0x0000_0000
	UINT32 r_2x3_coef7a                     :15;	//(14:0,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810D0 RW 0x0000_0000
	UINT32 r_2x3_ofst0                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_coef8a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810D4 RW 0x0000_0000
	UINT32 r_2x3_ofst2                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst1                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810D8 RW 0x0000_0000
	UINT32 r_2x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810DC RW 0x0000_0100
	UINT32 r_2x3_en                         :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_degamma_en                     :1;	//(4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_1x3_en                         :1;	//(8,NA,0x1) //
	UINT32 resvd2                           :7;
	UINT32 r_2x3_ofst5                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd3                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810E0 RW 0x0000_0000
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
}PE_O22_CC_PE1_BT20_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810E4 RW 0x0000_0000
	UINT32 r_2x3_coef3b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 reg_csc_cb_th                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_BT20_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810E8 RW 0x0000_0000
	UINT32 r_2x3_coef5b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4b                     :15;	//(30:16,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810EC RW 0x0000_0000
	UINT32 r_2x3_coef7b                     :15;	//(14:0,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810F0 RW 0x0000_0000
	UINT32 reg_csc_cr_th                    :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 r_2x3_coef8b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810F4 RW 0x12A0_7C98
	UINT32 r_1x3_coef1                      :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef0                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810F8 RW 0x7775_12A0
	UINT32 r_1x3_coef3                      :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef2                      :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4810FC RW 0x21D7_0000
	UINT32 r_1x3_coef5                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef4                      :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481100 RW 0x12A0_0000
	UINT32 r_1x3_coef7                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef6                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481104 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_1x3_coef8                      :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_BT20_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481108 RW 0x07C0_0600
	UINT32 r_1x3_ofst1                      :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst0                      :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48110C RW 0x0600_0000
	UINT32 r_1x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst2                      :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481110 RW 0x0000_0000
	UINT32 r_1x3_ofst5                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC_PE1_BT20_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481114 RW 0x0000_0000
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
}PE_O22_CC_PE1_BT20_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481118 RO 0x0000_0000
	UINT32 r_1x3_over_count_0               :16;	//(15:0,NA,0x0) //overflow count status for ch 0
	UINT32 r_1x3_under_count_0              :16;	//(31:16,NA,0x0) //underflow count status for ch 0
	};
}PE_O22_CC_PE1_BT20_CTRL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48111C RO 0x0000_0000
	UINT32 r_1x3_over_count_1               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_1              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O22_CC_PE1_BT20_CTRL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481120 RO 0x0000_0000
	UINT32 r_1x3_over_count_2               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_2              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O22_CC_PE1_BT20_CTRL_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481124 RO 0x0000_0000
	UINT32 r_1x3_over_count_3               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_3              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O22_CC_PE1_BT20_CTRL_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481140 RW 0x0000_0000
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
}PE_O22_CC_PE1_WIN2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481144 RW 0x0000_0000
	UINT32 win_w0_x0_0                      :13;	//(12:0,NA,0x000) //win_w0_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_0                      :13;	//(28:16,NA,0x000) //win_w0_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481148 RW 0x0437_03BF
	UINT32 win_w0_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w0_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_0                      :13;	//(28:16,NA,0x437) //win_w0_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48114C RW 0x0000_0000
	UINT32 win_w1_x0_0                      :13;	//(12:0,NA,0x000) //win_w1_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_0                      :13;	//(28:16,NA,0x000) //win_w1_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481150 RW 0x0437_03BF
	UINT32 win_w1_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w1_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_0                      :13;	//(28:16,NA,0x437) //win_w1_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481154 RW 0x0000_0000
	UINT32 win_w0_x0_1                      :13;	//(12:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_1                      :13;	//(28:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481158 RW 0x0437_03BF
	UINT32 win_w0_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w0_x1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_1                      :13;	//(28:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48115C RW 0x0000_0000
	UINT32 win_w1_x0_1                      :13;	//(12:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_1                      :13;	//(28:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481160 RW 0x0437_03BF
	UINT32 win_w1_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w1_x1
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_1                      :13;	//(28:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_WIN2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811D0 RW 0x0000_002C
	UINT32 cen_detour                       :1;	//(0,NA,0x0) //cen_detour	'0' : normal path	'1' : CEN detour
	UINT32 dse_mode                         :1;	//(1,NA,0x0) //0:parallel, 1:serial(DSE->CEN)
	UINT32 select_hsv                       :1;	//(2,NA,0x1) //reg_select_hsv 	HSV total gain???ÅÏö© ?¨Î?	'1' : HSV total gain???êÎ≥∏ HSV?Ä ?©ÏÇ∞?òÏó¨ ?ÅÏö©	'0' : ?êÎ≥∏ HSVÎ•?Í∑∏Î?Î°??¨Ïö©
	UINT32 select_rgb                       :1;	//(3,NA,0x1) //reg_select_RGB 	RGB total gain???ÅÏö© ?¨Î?	'1' : RGB total gain???êÎ≥∏ RGB?Ä ?©ÏÇ∞?òÏó¨ ?ÅÏö©	'0' : ?êÎ≥∏ RGB??Í∑∏Î?Î°??¨Ïö©
	UINT32 resvd0                           :1;
	UINT32 vsp_sel                          :1;	//(5,NA,0x1) //reg_vsp_sel	'0' : HSL region	'1' : HSV region
	UINT32 resvd1                           :1;
	UINT32 reg_cen_bypass                   :1;	//(7,NA,0x0) //reg_cen_bypass : Color Enhance block??on/off 	'0' : CEN ?ÅÏö© ?òÏ? ?äÏùå ?ÖÎ†• RGBÍ∞Ä Ï∂úÎ†• RGBÎ°?bypass	'1' : CEN ?ÅÏö© ??
	UINT32 reg_cen_debug_mode               :1;	//(8,NA,0x0) //reg_cen_debug_mode	'0' : CR??Í∞ÅÍ∞Å???âÏúºÎ°?Ï±ÑÏÉâ	'1' : Debugging Color??PIXEL_GAIN Í∞íÏùÑ Gray levelÎ°??úÌòÑ
	UINT32 resvd2                           :1;
	UINT32 core_1st__gain_disable           :1;	//(10,NA,0x0) //1st Region core gain disable	1st Region core??gain??disable	'0' : Gain ?ÅÏö©	'1' : Gain ÎØ∏Ï†Å??
	UINT32 core_2nd_gain_disable            :1;	//(11,NA,0x0) //2nd core gain disable	2nd core??gain??disable	'0' : Gain ?ÅÏö©	'1' : Gain ÎØ∏Ï†Å??
	UINT32 resvd3                           :1;
	UINT32 debugging_mode_core              :2;	//(14:13,NA,0x0) //Debugging modeCore	Debugging mode???ÅÏö© Core	'01' : 1st Core??Debugging modeÍ∞Ä ?ÅÏö©	'10' : 2nd Core??Debugging modeÍ∞Ä ?ÅÏö©	others : 1st core??Debugging modeÍ∞Ä ?ÅÏö©(show_color_region0, show_color_region1 ?ºÎ°ú ?†ÌÉù???ÅÏó≠???úÌï¥??
	UINT32 resvd4                           :1;
	UINT32 demo_mode                        :8;	//(23:16,NA,0x0) //Demo Mode	'0111 1000' => 0x78	Algorithm ?ÅÏö© ?ÅÏÉÅÍ≥??êÎ≥∏?ÅÏÉÅ??Í≤ΩÍ≥Ñ ?ÑÏπòÎ•?control	?ÑÏ≤¥ ?îÎ©¥ ?¨Í∏∞ / 16 : (ex) 1920 => 0x780 => reg_cen_ctrl0(23:16) = 0x78	?îÎ©¥??Ï¢åÏ∏°?Ä ?êÎ≥∏?îÎ©¥, ?∞Ï∏°?Ä ?ÅÏö©?îÎ©¥?¥Î©∞ Ïª§Ïßà ?òÎ°ù ?êÎ≥∏ ?îÎ©¥???ÅÏó≠???ìÏñ¥Ïß?
	UINT32 resvd5                           :7;
	UINT32 win_control_mode                 :1;	//(31,NA,0x0) //'0' : window control enabled	 '1' : win mode is always disabled
	};
}PE_O22_CC_PE1_CEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811D4 RW 0xFFFF_0000
	UINT32 show_color_region0               :1;	//(0,NA,0x00) //Region 0??Region_debug_color0 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region1               :1;	//(1,NA,0x00) //Region 1??Region_debug_color1 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region2               :1;	//(2,NA,0x00) //Region 2??Region_debug_color2 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region3               :1;	//(3,NA,0x00) //Region 3??Region_debug_color3 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region4               :1;	//(4,NA,0x00) //Region 4??Region_debug_color4 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region5               :1;	//(5,NA,0x00) //Region 5??Region_debug_color5 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region6               :1;	//(6,NA,0x00) //Region 6??Region_debug_color6 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region7               :1;	//(7,NA,0x00) //Region 7??Region_debug_color7 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region8               :1;	//(8,NA,0x00) //Region 8??Region_debug_color8 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region9               :1;	//(9,NA,0x00) //Region 9??Region_debug_color9 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region10              :1;	//(10,NA,0x00) //Region 10??Region_debug_color10 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region11              :1;	//(11,NA,0x00) //Region 11??Region_debug_color11 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region12              :1;	//(12,NA,0x00) //Region 12??Region_debug_color12 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region13              :1;	//(13,NA,0x00) //Region 13??Region_debug_color13 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region14              :1;	//(14,NA,0x00) //Region 14??Region_debug_color14 Î°?Ï±ÑÏÉâ
	UINT32 show_color_region15              :1;	//(15,NA,0x00) //Region 15??Region_debug_color15 Î°?Ï±ÑÏÉâ
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
}PE_O22_CC_PE1_CEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811D8 RW 0x0000_8080
	UINT32 ihsv_sgain                       :8;	//(7:0,NA,0x80) //reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//(15:8,NA,0x80) //reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
}PE_O22_CC_PE1_CEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811DC RW 0x0080_8080
	UINT32 ihsv_hoffset                     :8;	//(7:0,NA,0x80) //reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//(15:8,NA,0x80) //reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//(23:16,NA,0x80) //reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
}PE_O22_CC_PE1_CEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811E0 RW 0x8080_8080
	UINT32 reg_master_gain_cr0              :8;	//(7:0,NA,0x80) //Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//(15:8,NA,0x80) //Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//(23:16,NA,0x80) //Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//(31:24,NA,0x80) //Color region 3 master gain
	};
}PE_O22_CC_PE1_CEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811E4 RW 0x8080_8080
	UINT32 reg_master_gain_cr4              :8;	//(7:0,NA,0x80) //Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//(15:8,NA,0x80) //Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//(23:16,NA,0x80) //Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//(31:24,NA,0x80) //Color region 7 master gain
	};
}PE_O22_CC_PE1_CEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811E8 RW 0x8080_8080
	UINT32 reg_master_gain_cr8              :8;	//(7:0,NA,0x80) //Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//(15:8,NA,0x80) //Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//(23:16,NA,0x80) //Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//(31:24,NA,0x80) //Color region 11 master gain
	};
}PE_O22_CC_PE1_CEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811EC RW 0x8080_8080
	UINT32 reg_master_gain_cr12             :8;	//(7:0,NA,0x80) //Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//(15:8,NA,0x80) //Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//(23:16,NA,0x80) //Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//(31:24,NA,0x80) //Color region 15 master gain
	};
}PE_O22_CC_PE1_CEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4811F8 RW/RO 0x0000_0000
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
}PE_O22_CC_PE1_CEN_UPD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481200 WO 0x0000_0000
	UINT32 hif_cen_address                  :8;	//(7:0,NA,0x00) //hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//(10:8,NA,0x0) //reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//(14,NA,0x0) //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//(15,NA,0x0) //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
}PE_O22_CC_PE1_CEN_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481204 RO 0x0000_0000
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_CEN_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481208 WO 0x0000_0000
	UINT32 hif_cen_delta_address            :5;	//(4:0,NA,0x00) //hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//(15,NA,0x0) //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
}PE_O22_CC_PE1_CEN_DELTA_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48120C RO 0x0000_0000
	UINT32 hif_cen_vr_data                  :8;	//(7:0,NA,0x000) //Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//(15:8,NA,0x000) //Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//(23:16,NA,0x000) //Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
}PE_O22_CC_PE1_CEN_DELTA_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481220 RW 0x0000_0000
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
}PE_O22_CC_PE1_DCE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481224 RW 0x0080_001A
	UINT32 chroma_comp_color_region_gain    :8;	//(7:0,NA,0x1A) //default : "128" ( 1 ~ 255(1~400%))
	UINT32 resvd0                           :8;
	UINT32 color_region_gain                :8;	//(23:16,NA,0x80) //default : "128" ( 1 ~ 255(1~400%)) (forbidden 0 value))
	UINT32 resvd1                           :8;
	};
}PE_O22_CC_PE1_DCE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481228 RW 0x0000_0000
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
}PE_O22_CC_PE1_DCE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48122C RW 0x02D0_01E0
	UINT32 y_range_min                      :10;	//(9:0,NA,0x01E0) //default : 480
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x02D0) //default : 720
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481230 RW 0x02B4_0264
	UINT32 cb_range_min                     :10;	//(9:0,NA,0x0264) //default : 612
	UINT32 resvd0                           :6;
	UINT32 cb_range_max                     :10;	//(25:16,NA,0x02B4) //default : 692
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481234 RW 0x01FC_0134
	UINT32 cr_range_min                     :10;	//(9:0,NA,0x0134) //default : 308
	UINT32 resvd0                           :6;
	UINT32 cr_range_max                     :10;	//(25:16,NA,0x01FC) //default : 508
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481238 RW 0x0000_8000
	UINT32 hif_dyc_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dce_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dce_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dce_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_O22_CC_PE1_DCE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48123C RO 0x0000_0000
	UINT32 hif_dyc_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481240 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481244 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 dce_ktd_csc_sel                  :1;	//(1,NA,0x0) //0' : KTD(default)	'1' : QTD
	UINT32 resvd1                           :30;
	};
}PE_O22_CC_PE1_DCE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481248 RW 0x0000_8000
	UINT32 hif_hist_address                 :7;	//(6:0,NA,0x00) //"0"   : 0th bin	"1'   : 1st bin	??"127" : 127st bin
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
}PE_O22_CC_PE1_DCE_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48124C RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O22_CC_PE1_DCE_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481250 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_O22_CC_PE1_DCE_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481254 RW 0x0200_0200
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_O22_CC_PE1_DCE_CHR_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481258 RW 0x0200_0200
	UINT32 dce_chr_alpha2                   :10;	//(9:0,NA,0x200) //alpha(0~512), y_dce_in < y_dce_out : 0 means no gain
	UINT32 resvd0                           :6;
	UINT32 dce_chr_alpha1                   :10;	//(25:16,NA,0x200) //alpha(0~512), y_dce_in >= y_dce_out : 0 means no gain
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CHR_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48125C RW 0x0200_0200
	UINT32 dce_cr_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DCE_CHR_GAIN2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481270 RW 0x0000_0000
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
}PE_O22_CC_PE1_DSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481274 RW 0x8000_0301
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
}PE_O22_CC_PE1_DSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481278 RW 0x03FF_03FF
	UINT32 hif_dse_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48127C RW 0x0000_8000
	UINT32 hif_dse_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_O22_CC_PE1_DSE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481280 RO 0x0000_0000
	UINT32 hif_dse_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DSE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481284 RW 0x028A_0238
	UINT32 y_range_min                      :10;	//(9:0,NA,0x0238) //default : 568
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x028A) //default : 650
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481288 RW 0x0061_0026
	UINT32 h_range_min                      :10;	//(9:0,NA,0x0026) //default : 38
	UINT32 resvd0                           :6;
	UINT32 h_range_max                      :10;	//(25:16,NA,0x0061) //default : 97
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48128C RW 0x0000_3C00
	UINT32 reg_y_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt0_x               :10;	//(17:8,NA,0x3C) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481290 RW 0x0000_C88C
	UINT32 reg_y_region_pt1_y               :8;	//(7:0,NA,0x8C) //
	UINT32 reg_y_region_pt1_x               :10;	//(17:8,NA,0xC8) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481294 RW 0x0001_40FF
	UINT32 reg_y_region_pt2_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt2_x               :10;	//(17:8,NA,0x140) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481298 RW 0x0001_90FF
	UINT32 reg_y_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt3_x               :10;	//(17:8,NA,0x190) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48129C RW 0x0002_BCFF
	UINT32 reg_y_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt4_x               :10;	//(17:8,NA,0x2BC) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812A0 RW 0x0003_4878
	UINT32 reg_y_region_pt5_y               :8;	//(7:0,NA,0x78) //
	UINT32 reg_y_region_pt5_x               :10;	//(17:8,NA,0x348) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812A4 RW 0x0003_703C
	UINT32 reg_y_region_pt6_y               :8;	//(7:0,NA,0x3C) //
	UINT32 reg_y_region_pt6_x               :10;	//(17:8,NA,0x370) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812A8 RW 0x0003_9800
	UINT32 reg_y_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt7_x               :10;	//(17:8,NA,0x398) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_Y_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812AC RW 0x0001_F100
	UINT32 reg_h_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt0_x               :10;	//(17:8,NA,0x1F1) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812B0 RW 0x0002_00BE
	UINT32 reg_h_region_pt1_y               :8;	//(7:0,NA,0xBE) //
	UINT32 reg_h_region_pt1_x               :10;	//(17:8,NA,0x200) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812B4 RW 0x0002_0DF0
	UINT32 reg_h_region_pt2_y               :8;	//(7:0,NA,0xF0) //
	UINT32 reg_h_region_pt2_x               :10;	//(17:8,NA,0x20D) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812B8 RW 0x0002_14FF
	UINT32 reg_h_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt3_x               :10;	//(17:8,NA,0x214) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812BC RW 0x0002_28FF
	UINT32 reg_h_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt4_x               :10;	//(17:8,NA,0x228) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812C0 RW 0x0002_30FF
	UINT32 reg_h_region_pt5_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt5_x               :10;	//(17:8,NA,0x230) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812C4 RW 0x0002_3FA0
	UINT32 reg_h_region_pt6_y               :8;	//(7:0,NA,0xA0) //
	UINT32 reg_h_region_pt6_x               :10;	//(17:8,NA,0x23F) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812C8 RW 0x0002_4000
	UINT32 reg_h_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt7_x               :10;	//(17:8,NA,0x240) //
	UINT32 resvd                            :14;
	};
}PE_O22_CC_PE_DSE_H_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812E0 RW 0x0010_0100
	UINT32 reg_drc_en                       :1;	//(0,NA,0x0) //drc enable	'0' : disable	'1' : enable
	UINT32 reg_drc_cg_disable               :1;	//(1,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_drc_txt_gain_en              :1;	//(4,NA,0x0) //texture,apl gaining en
	UINT32 resvd1                           :3;
	UINT32 reg_drc_rgb_sel                  :2;	//(9:8,NA,0x1) //"00" : luminance	"01" : MAX(r,g,b)	others : AVG(r,g,b)
	UINT32 resvd2                           :2;
	UINT32 reg_drc_gm_mode                  :3;	//(14:12,NA,0x0) //gamma lut enable	"01" : enable	others : disable
	UINT32 resvd3                           :1;
	UINT32 reg_drc_lk_blf_apf               :1;	//(16,NA,0x0) //use bypass spatial filter coefficient for debugging	'0' : disable 	'1' : enable
	UINT32 resvd4                           :3;
	UINT32 reg_dbg_disp_apl_gain            :1;	//(20,NA,0x0) //display apl gain for debuging	'0' : disable	'1' : enable
	UINT32 resvd5                           :3;
	UINT32 reg_dbg_apl_gain_sel             :2;	//(25:24,NA,0x0) //0:selected 1:dark 2:bright
	UINT32 resvd6                           :2;
	UINT32 reg_dbg_disp_blf                 :1;	//(28,NA,0x0) //display blf image for debuging	'0' : disable	'1' : enable
	UINT32 reg_dbg_disp_lcont               :1;	//(29,NA,0x0) //display local contrast image for debugging	'0' : disable	'1' : enable
	UINT32 reg_dbg_disp_texture             :1;	//(30,NA,0x0) //texture gain image for debugging (must set reg_dbg_disp_blf to 1)	'0' : disable	'1' : enable
	UINT32 resvd7                           :1;
	};
}PE_O22_CC_PE1_DRC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812E4 RW 0x0000_0001
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x1) //selecet a,b gamma lut for register r/w	'0' : a gamma lut 	'1' : b gamma lut
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //selecet a,b gamma lut for operation	'0' : b gamma lut 	'1' : a gamma lut
	UINT32 resvd1                           :11;
	UINT32 reg_drc_gm_forced_sel            :1;	//(16,NA,0x0) //anytime rw_sel, op_sel transition
	UINT32 reg_drc_gm_protected_sel         :1;	//(17,NA,0x0) //Do not allow rw_sel, op_sel transition only in de active
	UINT32 resvd2                           :14;
	};
}PE_O22_CC_PE1_DRC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812E8 RW 0x0036_0060
	UINT32 reg_drc_bnh                      :7;	//(6:0,NA,0x60) //horizontal block size (min : 4, max : 96)
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bnv                      :6;	//(21:16,NA,0x36) //vertical block size (min : 3, max : 54)
	UINT32 resvd1                           :10;
	};
}PE_O22_CC_PE1_DRC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812EC RW 0x0050_0050
	UINT32 reg_drc_bsh                      :9;	//(8:0,NA,0x50) //
	UINT32 resvd0                           :7;
	UINT32 reg_drc_bsv                      :9;	//(24:16,NA,0x50) //
	UINT32 resvd1                           :7;
	};
}PE_O22_CC_PE1_DRC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812F0 RW 0x0321_912C
	UINT32 reg_drc_gm_apl2                  :10;	//(9:0,NA,0x12C) //apl for gamma lut 2
	UINT32 reg_drc_gm_apl1                  :10;	//(19:10,NA,0x64) //apl for gamma lut 1
	UINT32 reg_drc_gm_apl0                  :10;	//(29:20,NA,0x32) //apl for gamma lut 0
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812F4 RW 0x1F4A_F3B6
	UINT32 reg_drc_gm_apl5                  :10;	//(9:0,NA,0x3B6) //apl for gamma lut 5
	UINT32 reg_drc_gm_apl4                  :10;	//(19:10,NA,0x2BC) //apl for gamma lut 4
	UINT32 reg_drc_gm_apl3                  :10;	//(29:20,NA,0x1F4) //apl for gamma lut 3
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812F8 RW 0x0000_0030
	UINT32 reg_drc_blf_wei_cen              :8;	//(7:0,NA,0x30) //center pixel weight for blf
	UINT32 resvd                            :24;
	};
}PE_O22_CC_PE1_DRC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4812FC RW 0x00000000
	UINT32 reg_drc_apl_lut_x1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x0               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DRC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481300 RW 0x00000000
	UINT32 reg_drc_apl_lut_x3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x2               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_DRC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481304 RW 0x00000000
	UINT32 reg_drc_apl_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_apl_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_apl_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_apl_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481308 RW 0x00000000
	UINT32 reg_drc_txt_lut_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48130C RW 0x00000000
	UINT32 reg_drc_txt_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481310 RW 0x00000000
	UINT32 reg_drc_dark_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481314 RW 0x00000000
	UINT32 reg_drc_dark_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481318 RW 0x00000000
	UINT32 reg_drc_bright_lut_x3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_x2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_x1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_x0            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48131C RW 0x00000000
	UINT32 reg_drc_bright_lut_y3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_y2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_y1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_y0            :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC_PE1_DRC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481320 RW 0x00000000
	UINT32 reg_vspyc_tap_mode               :1;	//(0,NA,0x0) //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_vspyc_repeat_en              :1;	//(4,NA,0x0) //1:repeat(interpolation off)
	UINT32 resvd1                           :3;
	UINT32 reg_oai_vspyc_pel_dly            :2;	//(9:8,NA,0x0) //0:0 1:+1 2:+2 3:+3
	UINT32 resvd2                           :2;
	UINT32 reg_oai_yspyc_obj_dly            :2;	//(13:12,NA,0x0) //0:-2 1:-1 2:0 3:+1
	UINT32 resvd3                           :2;
	UINT32 reg_oai_in_pel_sel               :1;	//(16,NA,0x0) //must be set to 0x1!!
	UINT32 resvd4                           :15;
	};
}PE_O22_CC_PE1_DRC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481334 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_hfc_data          :10;	//(9:0,NA,0x0) //blf h filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481338 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_vfc_data          :10;	//(9:0,NA,0x0) //blf v filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48133C RW 0x0000_0000
	UINT32 reg_drc_hfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_hfc_rdata: blf h filter coefficient read data	WR  [0]reg_drc_hfc_re : blf h filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481340 RW 0x0000_0000
	UINT32 reg_drc_vfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_vfc_rdata : blf v filter coefficient read data	WR  [0]reg_drc_vfc_re : blf v filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481344 WO 0x0000_0000
	UINT32 reg_drc_blf_wei_wdata            :10;	//(9:0,NA,0x0) //blf photometric weight write data
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481348 RW 0x0000_0000
	UINT32 reg_drc_blf_wei_rdata            :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_blf_wei_rdata : blf photometric weight read data	WR  [0]reg_drc_blf_wei_re : blf photometric weight read enable
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48134C WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 0	[19:10] -> gamma lut 1	[ 9: 0] -> gamma lut 2
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481350 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 0,[19:10] -> gamma lut 1,[ 9: 0] -> gamma lut 2	WR [1:0]reg_drc_gm_re : gamma lut 0, 1, 2 read enable ("01")
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481354 WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 3	[19:10] -> gamma lut 4	[ 9: 0] -> gamma lut 5
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481358 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 3,[19:10] -> gamma lut 4,[ 9: 0] -> gamma lut 5	WR [1:0]reg_drc_gm_re : gamma lut 3, 4, 5 read enable ("10")
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_DRC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481364 RW 0x0000_0000
	UINT32 reg_drc_bl_apl_raddr_h           :7;	//(6:0,NA,0x0) //block apl read H address
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bl_apl_raddr_v           :6;	//(21:16,NA,0x0) //block apl read V address
	UINT32 resvd1                           :10;
	};
}PE_O22_CC_PE1_DRC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481368 RO 0x0000_0000
	UINT32 reg_drc_bl_apl_rdata             :10;	//(9:0,NA,0x0) //block apl read data
	UINT32 resvd                            :22;
	};
}PE_O22_CC_PE1_DRC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48136C RO 0x0000_0000
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x0) //Read rw_sel
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //Read op_sel
	UINT32 resvd1                           :27;
	};
}PE_O22_CC_PE1_DRC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481380 RW 0x0000_0C00
	UINT32 reg_pic_rptr_man                 :2;	//(1:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_pic_rptr_man_en              :1;	//(3,NA,0x0) //
	UINT32 reg_pic_wptr_man                 :2;	//(5:4,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_pic_wptr_man_en              :1;	//(7,NA,0x0) //
	UINT32 reg_pic_data_man                 :2;	//(9:8,NA,0x0) //0: test data off	1: 128	2: gradient	3: horizontal box
	UINT32 reg_pic_rptr_on                  :1;	//(10,NA,0x1) //
	UINT32 reg_pic_wptr_on                  :1;	//(11,NA,0x1) //
	UINT32 reg_pic_wd_man                   :4;	//(15:12,NA,0x0) //16Î∞? {reg_pic_wd_man,4'd0}
	UINT32 reg_pic_wd_man_on                :1;	//(16,NA,0x0) //
	UINT32 reg_pic_rd_lsb_man               :2;	//(18:17,NA,0x0) //0 : [1:0] = 0	1 : [1:0] = 3	2 : [1:0] = [3:2]	3 : [1:0] = [9:8]
	UINT32 reg_ro_buf_wrcnt                 :10;	//(28:19,NA,0x0) //
	UINT32 reg_ro_buf_wrsel                 :1;	//(29,NA,0x0) //
	UINT32 disp_clk_cg_on                   :1;	//(30:30,NA,0x0) //Logo L7 disp_clk clock gating
	UINT32 de_clk_cg_on                     :1;	//(31:31,NA,0x0) //Logo L7 de_clk clock gating
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481384 RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481388 RW 0x0011_001E
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x11) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48138C RW 0x0011_001E
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x11) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481390 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481394 RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481398 RW 0x0011_0078
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x78) //120=4x30
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x11) //17
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48139C RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813A0 RW 0x0000_0000
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
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813A4 RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813A8 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813AC RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813B0 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : (1920=7680/4p)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813B4 RW 0x0010_B8B8
	UINT32 reg_logo_blend_alpha_l7_delay    :8;	//(7:0,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 51 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blend_alpha_l3_delay    :8;	//(15:8,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 51 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blned_alpha_c5_delay    :5;	//(20:16,NA,0x10) //csr_gain delay : default 16, 0(-16T)~16(0T for logo_blend_top)~31(15T)
	UINT32 resvd                            :11;
	};
}PE_O22_CC_PE1_LOGO_L7SC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813B8 RW 0x0000_0011
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
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813BC RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813C0 RW 0x010E_01E0
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x10E) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813C4 RW 0x010E_01E0
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E0) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x10E) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813C8 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813CC RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813D0 RW 0x010E_0780
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x780) //1920=480x4
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x10E) //270
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813D4 RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813D8 RW 0x0000_0000
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
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813DC RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813E0 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813E4 RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813E8 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : 1920(7680/4)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O22_CC_PE1_LOGO_L3SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813EC RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O22_CC_PE1_LOGO_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813F0 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O22_CC_PE1_LOGO_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813F4 RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O22_CC_PE1_LOGO_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4813F8 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O22_CC_PE1_LOGO_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481410 RW 0x0000_0000
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
}PE_O22_CC_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}PE_O22_CC_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_CC_PE1_PCC_COEF7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481434 RW 0x0000_0000
	UINT32 oetf_addr                        :11;	//(10:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 oetf_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O22_CC_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481438 RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :12;	//(11:0,NA,0x0) //12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//(27:16,NA,0x0) //12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}PE_O22_CC_PE1_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48143C RW 0x0000_0000
	UINT32 eotf_wdata                       :15;	//(14:0,RW,0x0) //lut write data
	UINT32 resvd0                           :1;
	UINT32 eotf_waddr                       :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd1                           :2;
	UINT32 eotf_we                          :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}PE_O22_CC_PE1_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481440 RW/RO 0x0000_0000
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
}PE_O22_CC_PE1_EOTF_WDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481444 RW/RO 0x0000_0000
	UINT32 eotf_rdata                       :15;	//(14:0,RO,0x0) //lut read data
	UINT32 resvd0                           :1;
	UINT32 eotf_raddr                       :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 eotf_re                          :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 eotf_rdata_sel                   :1;	//(31,RW,0x0) //lut read data sel 0:even, 1:odd
	};
}PE_O22_CC_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481448 RO 0x0000_0000
	UINT32 eotf_buf_rw_conflict             :1;	//(0,RO,0x00) //
	UINT32 eotf_lut_cpy_done                :1;	//(1,RO,0x00) //
	UINT32 eotf_lut_cpy_status              :2;	//(3:2,RO,0x0) //
	UINT32 resvd                            :28;
	};
}PE_O22_CC_PE1_EOTF_RSATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481450 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O22_CC_PE1_LLLUT_E_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481454 RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_LLLUT_E_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481458 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O22_CC_PE1_LLLUT_O_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48145C RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O22_CC_PE1_LLLUT_O_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481460 RW 0x0000_0100
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
}PE_O22_CC_PE1_LLCORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481464 RW 0x0000_1000
	UINT32 reg_llpcc_coef0                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef1                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481468 RW 0x0000_0000
	UINT32 reg_llpcc_coef2                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef3                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48146C RW 0x0000_0000
	UINT32 reg_llpcc_coef4                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef5                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481470 RW 0x0000_0000
	UINT32 reg_llpcc_coef6                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef7                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481474 RW 0x0AD9_1000
	UINT32 reg_llpcc_coef8                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 8
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(30:16,NA,0x0AD9) //alpha blendling RGB -> Y coef0
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481478 RW 0x0434_00F3
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(14:0,NA,0x00F3) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(30:16,NA,0x0434) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48147C RW 0x0000_0000
	UINT32 reg_llab_lut_y0                  :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x0                  :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481480 RW 0x0009_0009
	UINT32 reg_llab_lut_y1                  :10;	//(9:0,NA,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x1                  :10;	//(25:16,NA,0x9) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481484 RW 0x000A_0200
	UINT32 reg_llab_lut_y2                  :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x2                  :10;	//(25:16,NA,0xA) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481488 RW 0x000B_03FF
	UINT32 reg_llab_lut_y3                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x3                  :10;	//(25:16,NA,0xB) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48148C RW 0x03FF_03FF
	UINT32 reg_llab_lut_y4                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x4                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481490 RW 0x03FF_03FF
	UINT32 reg_llab_lut_y5                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x5                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481494 RW 0x0000_00FF
	UINT32 reg_hue_prsv_ratio               :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O22_CC_PE1_LLCORE_CTRL_13_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC481500 RW 0x0200_0040
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
}PE_O22_CC2_PE1_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481504 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481508 RW 0x12AF_7C94
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,NA,0x7C94) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48150C RW 0x7773_12AF
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,NA,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,NA,0x7773) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481510 RW 0x21E6_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,NA,0x21E6) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481514 RW 0x12AF_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481518 RW 0x1CC5_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,NA,0x1CC5) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48151C RW 0x07C0_0600
	UINT32 r_yc2rgb_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481520 RW 0x0600_0000
	UINT32 r_yc2rgb_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481524 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst4                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSPYC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481530 RW 0x0000_0300
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
}PE_O22_CC2_PE1_VSP_CC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481544 RW 0x0000_2001
	UINT32 reg_vspyc_tap_mode               :1;	//(0,NA,0x1) //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_vspyc_repeat_en              :1;	//(4,NA,0x0) //1:repeat(interpolation off)
	UINT32 resvd1                           :3;
	UINT32 reg_oai_vspyc_pel_dly            :2;	//(9:8,NA,VNA) //0:0 1:+1 2:+2 3:+3
	UINT32 resvd2                           :2;
	UINT32 reg_oai_yspyc_obj_dly            :2;	//(13:12,NA,VNA) //0:-2 1:-1 2:0 3:+1
	UINT32 resvd3                           :18;
	};
}PE_O22_CC2_PE1_VSP_CC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481550 RW 0x01F1_0000
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x1F1) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481554 RW 0x0200_00BE
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xBE) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481558 RW 0x020D_00F0
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xF0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x20D) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48155C RW 0x0214_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x214) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481560 RW 0x0228_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x228) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481564 RW 0x0230_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x230) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481568 RW 0x023F_00A0
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xA0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x23F) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48156C RW 0x024D_0000
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x24D) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481570 RW 0x2D6E_2000
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x20) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0x6E) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x2D) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481574 RW 0x46FF_39C8
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xC8) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0x39) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x46) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481578 RW 0x66FF_53FF
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x53) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x66) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48157C RW 0x7FFF_7DFF
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x7D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x7F) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481580 RW 0x328C_0F00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0xF) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x32) //
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481584 RW 0x64FF_50FF
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x50) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x64) //
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481588 RW 0xD278_AFFF
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xAF) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0x78) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xD2) //
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48158C RO 0xE600_DC3C
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xDC) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xE6) //
	};
}PE_O22_CC2_PE1_VSP_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815A0 RW 0x0000_0000
	UINT32 enable_debug_mode                :1;	//(0,NA,0x0) //Enable debug mode
	UINT32 status_enable                    :1;	//(1,NA,0x0) //APL
	UINT32 debug_mode                       :1;	//(2,NA,0x0) //0' : status read(APL)	'1' : yc control
	UINT32 resvd0                           :17;
	UINT32 show_apl                         :1;	//(20,NA,0x0) //show apl( y, rgb, r,g,b)
	UINT32 resvd1                           :11;
	};
}PE_O22_CC2_PE1_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815A4 RW VNA
	UINT32 yc_debug_en                      :1;	//(0,NA,0x0) //
	UINT32 force_yy_enable                  :1;	//(1,NA,0x0) //forcing Y data enable
	UINT32 force_cb_enable                  :1;	//(2,NA,0x0) //forcing Cb data enable
	UINT32 force_cr_enable                  :1;	//(3,NA,0x0) //forcing Cr data enable
	UINT32 yc_debug_mode_sel                :3;	//(6:4,NA,0x0) //"000" : normal	"001" : show Y only(grayscale)	"010" : show CbCr only	"011" : show Cb data at Y channel	"100" : show Cr data at Y channel	others : normal
	UINT32 resvd                            :25;
	};
}PE_O22_CC2_PE1_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815A8 RW 0x0000_0000
	UINT32 force_yy                         :10;	//(9:0,NA,0x0) //
	UINT32 force_cb                         :10;	//(19:10,NA,0x0) //forcing Cb data
	UINT32 force_cr                         :10;	//(29:20,NA,0x0) //forcing Cr data
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_DEBUG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815B0 RW 0x0000_0100
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
}PE_O22_CC2_PE1_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815B4 RW 0x00C0_C0C0
	UINT32 user_ctrl_g_gain                 :8;	//(7:0,NA,0xC0) //User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//(15:8,NA,0xC0) //User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//(23:16,NA,0xC0) //User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}PE_O22_CC2_PE1_CW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815B8 RW 0x0040_0000
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
}PE_O22_CC2_PE1_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815C0 RW 0x0000_00FF
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815C4 RW 0x0064_00FF
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x64) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815C8 RW 0x011C_00FF
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x11C) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815CC RW 0x01AA_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x1AA) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815D0 RW 0x0238_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x238) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815D4 RW 0x02C6_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x2C6) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815D8 RW 0x0354_00FF
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x354) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815DC RW 0x03FF_00FF
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815E0 RW 0x06FF_00FF
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x6) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815E4 RW 0x12FF_0DFF
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0xD) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x12) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815E8 RW 0x198C_14DC
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xDC) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x14) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x19) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815EC RW 0x2000_1D3C
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x1D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x20) //
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815F0 RW 0x6464_3C00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0x3C) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x64) //
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815F4 RW 0x8CC8_7896
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0x96) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x78) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xC8) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x8C) //
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815F8 RW 0xBEFF_A0E6
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xE6) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xA0) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xBE) //
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4815FC RW 0xFFA0_FAFF
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xFA) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0xA0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xFF) //
	};
}PE_O22_CC2_PE1_CW_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481610 RW 0x1E00_10E0
	UINT32 display_height                   :13;	//(12:0,NA,0x10E0) //
	UINT32 resvd0                           :3;
	UINT32 display_width                    :13;	//(28:16,NA,0x1E00) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LBLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481614 RW 0x0000_0000
	UINT32 reg_block_size_v                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_block_size_h                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_block_no_v                   :6;	//(21:16,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,NA,0x0) //
	};
}PE_O22_CC2_PE1_LBLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481618 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :8;	//(7:0,NA,0x0) //
	UINT32 reg_last_block_size_h            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O22_CC2_PE1_LBLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481620 RW 0x8000_0A40
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
}PE_O22_CC2_PE1_LOGO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481624 RW 0x12C2_5BFE
	UINT32 resvd                            :1;
	UINT32 bound_proc_logocheck             :1;	//(1,NA,0x1) //
	UINT32 bound_proc_gain                  :8;	//(9:2,NA,0xff) //
	UINT32 bound_proc_range_x               :11;	//(20:10,NA,0x96) //
	UINT32 bound_proc_range_y               :11;	//(31:21,NA,0x96) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481628 RW 0x0000_0000
	UINT32 boundary_position_x0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_x1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48162C RW 0x0000_0000
	UINT32 boundary_position_y0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_y1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481630 RW 0x03BF_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,NA,0x3BF) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481634 RW 0x10DF_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,NA,0x10DF) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481638 RW 0x0100_0080
	UINT32 reg_region_position_x1           :13;	//(12:0,NA,0x80) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,NA,0x100) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48163C RW 0x0200_0180
	UINT32 reg_region_position_x3           :13;	//(12:0,NA,0x180) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,NA,0x200) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481640 RW 0x0300_0280
	UINT32 reg_region_position_x5           :13;	//(12:0,NA,0x280) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,NA,0x300) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481644 RW 0x03A0_0380
	UINT32 reg_region_position_x7           :13;	//(12:0,NA,0x380) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,NA,0x3A0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481648 RW 0x0800_0400
	UINT32 reg_region_position_y1           :13;	//(12:0,NA,0x400) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,NA,0x800) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48164C RW 0x0E00_0C00
	UINT32 reg_region_position_y3           :13;	//(12:0,NA,0xC00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,NA,0xE00) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481650 RW 0x1000_0F00
	UINT32 reg_region_position_y5           :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,NA,0x1000) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481654 RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481658 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48165C RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481660 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481664 RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481668 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48166C RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481670 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481674 RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481678 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48167C RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481680 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481684 RW 0x0200_0310
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x310) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481688 RW 0x0080_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x80) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48168C RW 0x2040_80C4
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xC4) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x20) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481690 RW 0x0380_03FF
	UINT32 reg_drop_x7_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,NA,0x380) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481694 RW 0x0200_0300
	UINT32 reg_drop_x5_i                    :10;	//(9:0,NA,0x300) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481698 RW 0x0100_0200
	UINT32 reg_drop_x3_i                    :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,NA,0x100) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48169C RW 0x0000_0100
	UINT32 reg_drop_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816A0 RW 0x0200_0240
	UINT32 reg_drop_y7_i                    :10;	//(9:0,NA,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816A4 RW 0x0190_01C0
	UINT32 reg_drop_y5_i                    :10;	//(9:0,NA,0x1C0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,NA,0x190) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816A8 RW 0x00E0_0190
	UINT32 reg_drop_y3_i                    :10;	//(9:0,NA,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,NA,0xE0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816AC RW 0x0000_00E0
	UINT32 reg_drop_y1_i                    :10;	//(9:0,NA,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816B0 RW 0x0300_03FF
	UINT32 reg_sat_scon_x3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816B4 RW 0x0000_0200
	UINT32 reg_sat_scon_x1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816B8 RW 0x0300_03FF
	UINT32 reg_sat_scon_y3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816BC RW 0x0000_0200
	UINT32 reg_sat_scon_y1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816C0 RW 0x1080_1080
	UINT32 reg_l7_gain_drop                 :8;	//(7:0,NA,0x80) //
	UINT32 reg_l7_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l7_gain_b_contrast           :8;	//(23:16,NA,0x80) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l7_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816C4 RW 0x0840_1040
	UINT32 reg_l3_gain_drop                 :8;	//(7:0,NA,0x40) //
	UINT32 reg_l3_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l3_gain_b_contrast           :8;	//(23:16,NA,0x40) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l3_gain_saturation           :8;	//(31:24,NA,0x8) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816C8 RW 0x1060_20A4
	UINT32 reg_c5_gain_drop                 :8;	//(7:0,NA,0xA4) //
	UINT32 reg_c5_gain_w_contrast           :8;	//(15:8,NA,0x20) //white(bright) contrast gain(input level < output level)
	UINT32 reg_c5_gain_b_contrast           :8;	//(23:16,NA,0x60) //black(dark) contrast gain(input level > output level)
	UINT32 reg_c5_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816CC RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O22_CC2_PE1_LOGO_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816D0 RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816D4 RW 0x0000_0000
	UINT32 reg_merge_contrast_l7l3          :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_contrast_l7l3c5        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_drop_l7l3              :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816D8 RW 0x0000_0000
	UINT32 reg_merge_drop_l7l3c5            :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3c5      :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816DC RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O22_CC2_PE1_LOGO_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816E0 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816E4 RW 0x0000_0000
	UINT32 reg_pxl_x0_2                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_2             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_2                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_2            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O22_CC2_PE1_LOGO_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816E8 RW 0x0000_0000
	UINT32 reg_pxl_width_2                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_2                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816EC RW 0x0000_0000
	UINT32 reg_pxl_x0_3                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_3             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_3                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_3            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O22_CC2_PE1_LOGO_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816F0 RW 0x0000_0000
	UINT32 reg_pxl_width_3                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_3                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816F4 RW 0x0040_80FF
	UINT32 reg_txt_x3_i                     :8;	//(7:0,NA,0xFF) //texture gain LUT
	UINT32 reg_txt_x2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_x1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_x0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816F8 RW 0x0040_80FF
	UINT32 reg_txt_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_txt_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4816FC RW 0x0080_8080
	UINT32 reg_region_gain_contrast         :8;	//(7:0,NA,0x80) //1.0 = 128
	UINT32 reg_region_gain_drop             :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_saturation       :8;	//(23:16,NA,0x80) //
	UINT32 resvd                            :8;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481700 RW 0x0000_0140
	UINT32 reg_logo_tap_mode                :1;	//(0,NA,0x0) //logo texture interpolation 0:2tap, 1:4tap
	UINT32 reg_logo_repeat_en               :1;	//(1,NA,0x0) //logo texture interpolation 1:repeat
	UINT32 resvd0                           :2;
	UINT32 reg_disp_dbg_ref_l3              :1;	//(4,NA,0x0) //logo refine debug disp
	UINT32 reg_use_extern_valid             :1;	//(5,NA,0x0) //logo refine dummy valid gen param
	UINT32 reg_use_blank_period_cnt         :1;	//(6,NA,0x1) //logo refine dummy valid gen param
	UINT32 resvd1                           :1;
	UINT32 reg_refine_en                    :1;	//(8,NA,0x0) //logo refine en
	UINT32 resvd2                           :7;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481704 RW 0x00000000
	UINT32 reg_refine_weight_lut_x3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_x2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_x1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_x0         :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481708 RW 0x00000000
	UINT32 reg_refine_weight_lut_y3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_y2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_y1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_y0         :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48170C RW 0x00000000
	UINT32 reg_refine_weight_gain_x3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_x2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_x1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_x0        :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481710 RW 0x00000000
	UINT32 reg_refine_weight_gain_y3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_y2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_y1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_y0        :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481720 RW 0x0000_0000
	UINT32 reg_gsr_blend_en                 :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//(7:4,NA,0x0) //0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//(25:16,NA,0x0) //
	UINT32 resvd2                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481724 RW 0x03B0_4200
	UINT32 reg_curr_peak_level              :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :2;
	UINT32 reg_crnt_resol_sel               :4;	//(15:12,NA,0x4) //left shift bit size, 0:8b, 1:7b, 2:6b, 3:5b, 4:4b, 5:3b, 6:2b, 7:1b, 8:0b
	UINT32 reg_wg_ratio                     :11;	//(26:16,NA,0x3B0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC2_PE1_GSR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481728 RW 0x0478_031F
	UINT32 reg_wb_ratio                     :11;	//(10:0,NA,0x31F) //
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//(26:16,NA,0x478) //
	UINT32 resvd1                           :5;
	};
}PE_O22_CC2_PE1_GSR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48172C RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,NA,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,NA,0x326) //
	UINT32 resvd1                           :4;
	};
}PE_O22_CC2_PE1_GSR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481730 RW 0x0389_02A8
	UINT32 reg_b_crnt_wgt                   :12;	//(11:0,NA,0x2A8) //
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//(27:16,NA,0x389) //
	UINT32 resvd1                           :4;
	};
}PE_O22_CC2_PE1_GSR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481734 RW 0x0000_0000
	UINT32 reg_crnt_lut_y00                 :16;	//(15:0,NA,0x0) //
	UINT32 reg_crnt_lut_x00                 :10;	//(25:16,NA,0x0) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481738 RW 0x0044_0CF9
	UINT32 reg_crnt_lut_y01                 :16;	//(15:0,NA,0xCF9) //
	UINT32 reg_crnt_lut_x01                 :10;	//(25:16,NA,0x44) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48173C RW 0x0088_1BD0
	UINT32 reg_crnt_lut_y02                 :16;	//(15:0,NA,0x1BD0) //
	UINT32 reg_crnt_lut_x02                 :10;	//(25:16,NA,0x88) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481740 RW 0x00CC_2B72
	UINT32 reg_crnt_lut_y03                 :16;	//(15:0,NA,0x2B72) //
	UINT32 reg_crnt_lut_x03                 :10;	//(25:16,NA,0xCC) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481744 RW 0x0110_3B9F
	UINT32 reg_crnt_lut_y04                 :16;	//(15:0,NA,0x3B9F) //
	UINT32 reg_crnt_lut_x04                 :10;	//(25:16,NA,0x110) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481748 RW 0x0154_4C35
	UINT32 reg_crnt_lut_y05                 :16;	//(15:0,NA,0x4C35) //
	UINT32 reg_crnt_lut_x05                 :10;	//(25:16,NA,0x154) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48174C RW 0x0198_5D22
	UINT32 reg_crnt_lut_y06                 :16;	//(15:0,NA,0x5D22) //
	UINT32 reg_crnt_lut_x06                 :10;	//(25:16,NA,0x198) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481750 RW 0x01DC_6E57
	UINT32 reg_crnt_lut_y07                 :16;	//(15:0,NA,0x6E57) //
	UINT32 reg_crnt_lut_x07                 :10;	//(25:16,NA,0x1DC) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481754 RW 0x0220_7FCD
	UINT32 reg_crnt_lut_y08                 :16;	//(15:0,NA,0x7FCD) //
	UINT32 reg_crnt_lut_x08                 :10;	//(25:16,NA,0x220) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481758 RW 0x0264_917A
	UINT32 reg_crnt_lut_y09                 :16;	//(15:0,NA,0x917A) //
	UINT32 reg_crnt_lut_x09                 :10;	//(25:16,NA,0x264) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48175C RW 0x02A8_A35B
	UINT32 reg_crnt_lut_y10                 :16;	//(15:0,NA,0xA35B) //
	UINT32 reg_crnt_lut_x10                 :10;	//(25:16,NA,0x2A8) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481760 RW 0x02EC_B569
	UINT32 reg_crnt_lut_y11                 :16;	//(15:0,NA,0xB569) //
	UINT32 reg_crnt_lut_x11                 :10;	//(25:16,NA,0x2EC) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481764 RW 0x0330_C7A2
	UINT32 reg_crnt_lut_y12                 :16;	//(15:0,NA,0xC7A2) //
	UINT32 reg_crnt_lut_x12                 :10;	//(25:16,NA,0x330) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481768 RW 0x0374_DA02
	UINT32 reg_crnt_lut_y13                 :16;	//(15:0,NA,0xDA02) //
	UINT32 reg_crnt_lut_x13                 :10;	//(25:16,NA,0x374) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48176C RW 0x03B8_EC86
	UINT32 reg_crnt_lut_y14                 :16;	//(15:0,NA,0xEC86) //
	UINT32 reg_crnt_lut_x14                 :10;	//(25:16,NA,0x3B8) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481770 RW 0x03FF_FFFF
	UINT32 reg_crnt_lut_y15                 :16;	//(15:0,NA,0xFFFF) //
	UINT32 reg_crnt_lut_x15                 :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd                            :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481774 RW 0x0200_03FF
	UINT32 reg_crnt_x3_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x2_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481778 RW 0x0000_0100
	UINT32 reg_crnt_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48177C RW 0x0000_0000
	UINT32 reg_crnt_y3_i                    :8;	//(7:0,NA,0x0) //
	UINT32 reg_crnt_y2_i                    :8;	//(15:8,NA,0x0) //
	UINT32 reg_crnt_y1_i                    :8;	//(23:16,NA,0x0) //
	UINT32 reg_crnt_y0_i                    :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_GSR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481780 RW 0x0200_03FF
	UINT32 reg_value_x3_i                   :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x2_i                   :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481784 RW 0x0000_0100
	UINT32 reg_value_x1_i                   :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x0_i                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481788 RW 0x0000_0000
	UINT32 reg_value_y3_i                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_value_y2_i                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_value_y1_i                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_value_y0_i                   :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_GSR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48178C RW 0x0200_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481790 RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_GSR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481794 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_GSR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481798 RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O22_CC2_PE1_GSR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48179C RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_GSR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817A0 RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O22_CC2_PE1_GSR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817A4 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_GSR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817E0 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817E4 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817E8 RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817EC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817F0 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817F4 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817F8 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4817FC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481800 RW VNA
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481804 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481808 RW 0x0000_0000
	UINT32 mux3d_en                         :1;	//(0,NA,0x0) //Mux 3D on/off	'0' = off	'1' = on
	UINT32 resvd0                           :3;
	UINT32 reg_out_mux                      :2;	//(5:4,NA,0x00) //output select	'00' = blend	'01' = R	'10' = L	'11' = line by line
	UINT32 start_parity                     :1;	//(6,NA,0x00) //start parity	'0' : start with Left	'1' : start with Right
	UINT32 resvd1                           :9;
	UINT32 alpha1_gain                      :8;	//(23:16,NA,0x0) //gain for L, R channel blend	255 : L output ~ 0 : R output
	UINT32 alpha0_gain                      :8;	//(31:24,NA,0x0) //gain for Back Ground Color and Blended Data	255 : BG Color output ~ 0 : Data output
	};
}PE_O22_CC2_PE1_MUTE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48180C RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_0              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_0              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O22_CC2_PE1_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481810 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481814 RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_0              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_0              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O22_CC2_PE1_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481818 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48181C RW 0x0000_0000
	UINT32 bg_color_r                       :8;	//(7:0,NA,0x0) //8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//(15:8,NA,0x0) //8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//(23:16,NA,0x0) //8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481820 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481824 RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481828 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48182C RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481830 RW 0x0000_0000
	UINT32 x0_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_1              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_1              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O22_CC2_PE1_MUTE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481834 RW 0x0000_0000
	UINT32 x1_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481838 RW 0x0000_0000
	UINT32 x0_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_1              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_1              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O22_CC2_PE1_MUTE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48183C RW 0x0000_0000
	UINT32 x1_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MUTE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481910 RW 0x8080_8007
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
}PE_O22_CC2_PE1_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481914 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481918 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48191C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481920 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481924 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481928 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48192C RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O22_CC2_PE1_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481930 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481934 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481938 RW 0x8080_8007
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
}PE_O22_CC2_PE1_MERGE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48193C RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481940 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481944 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481948 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48194C RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481950 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481954 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O22_CC2_PE1_MERGE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481958 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48195C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481960 RW 0x8080_8007
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
}PE_O22_CC2_PE1_MERGE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481964 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481968 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48196C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481970 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481974 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481978 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48197C RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O22_CC2_PE1_MERGE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481980 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481984 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481988 RW 0x8080_8007
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
}PE_O22_CC2_PE1_MERGE_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48198C RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481990 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481994 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481998 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC48199C RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819A0 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819A4 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O22_CC2_PE1_MERGE_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819A8 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819AC RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819B0 RW 0x8080_8007
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
}PE_O22_CC2_PE1_MERGE_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819B4 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819B8 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819BC RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819C0 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819C4 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819C8 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O22_CC2_PE1_MERGE_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819CC RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O22_CC2_PE1_MERGE_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819D0 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819D4 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O22_CC2_PE1_MERGE_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819E0 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819E4 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819E8 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819EC RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819F0 RW 0x0000_0000
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
}PE_O22_CC2_PE1_LOGO_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819F4 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819F8 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC4819FC RW 0x0002_0028
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A00 RW 0x0002_0028
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A04 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A08 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A0C RW 0x0000_0000
	UINT32 reg_master_gain                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_l3_value_gain                :8;	//(15:8,RW,0x0) //
	UINT32 reg_master_en                    :1;	//(16,RW,0x0) //master en
	UINT32 resvd0                           :3;
	UINT32 reg_out_sel                      :2;	//(21:20,RW,0x0) //0:blend out 1:drop img 2:drop gain 3:s_gain
	UINT32 resvd1                           :2;
	UINT32 reg_l3_en                        :1;	//(24,RW,0x0) //l3 gain en
	UINT32 resvd2                           :7;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A10 RW 0x0000_0000
	UINT32 reg_sat_x3_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A14 RW 0x0000_0000
	UINT32 reg_sat_x1_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A18 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,RW,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A1C RW 0x0000_0000
	UINT32 reg_drop_x7_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A20 RW 0x0000_0000
	UINT32 reg_drop_x5_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A24 RW 0x0000_0000
	UINT32 reg_drop_x3_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A28 RW 0x0000_0000
	UINT32 reg_drop_x1_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A2C RW 0x0000_0000
	UINT32 reg_drop_y7_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A30 RW 0x0000_0000
	UINT32 reg_drop_y5_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A34 RW 0x0000_0000
	UINT32 reg_drop_y3_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A38 RW 0x0000_0000
	UINT32 reg_drop_y1_i                    :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A3C RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_out_disable              :1;	//(15,RW,0x0) //
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_in_disable               :1;	//(31,RW,0x0) //
	};
}PE_O22_CC2_PE1_LOGO_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC481A40 RW 0x0000_0000
	UINT32 reg_pxl_w                        :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O22_CC2_PE1_LOGO_CTRL_85_T;

typedef struct {
	PE_O22_CC2_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xCC481500
	PE_O22_CC2_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xCC481504
	PE_O22_CC2_PE1_VSPYC_CTRL_02_T                       pe1_vspyc_ctrl_02;	//0xCC481508
	PE_O22_CC2_PE1_VSPYC_CTRL_03_T                       pe1_vspyc_ctrl_03;	//0xCC48150C
	PE_O22_CC2_PE1_VSPYC_CTRL_04_T                       pe1_vspyc_ctrl_04;	//0xCC481510
	PE_O22_CC2_PE1_VSPYC_CTRL_05_T                       pe1_vspyc_ctrl_05;	//0xCC481514
	PE_O22_CC2_PE1_VSPYC_CTRL_06_T                       pe1_vspyc_ctrl_06;	//0xCC481518
	PE_O22_CC2_PE1_VSPYC_CTRL_07_T                       pe1_vspyc_ctrl_07;	//0xCC48151C
	PE_O22_CC2_PE1_VSPYC_CTRL_08_T                       pe1_vspyc_ctrl_08;	//0xCC481520
	PE_O22_CC2_PE1_VSPYC_CTRL_09_T                       pe1_vspyc_ctrl_09;	//0xCC481524
	UINT32                                                    reserved0;	//0xCC481528
	UINT32                                                    reserved1;	//0xCC48152C
	PE_O22_CC2_PE1_VSP_CC_CTRL_00_T                     pe1_vsp_cc_ctrl_00;	//0xCC481530
	UINT32                                                    reserved2;	//0xCC481534
	UINT32                                                    reserved3;	//0xCC481538
	UINT32                                                    reserved4;	//0xCC48153C
	UINT32                                                    reserved5;	//0xCC481540
	PE_O22_CC2_PE1_VSP_CC_CTRL_05_T                     pe1_vsp_cc_ctrl_05;	//0xCC481544
	UINT32                                                    reserved6;	//0xCC481548
	UINT32                                                    reserved7;	//0xCC48154C
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xCC481550
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xCC481554
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xCC481558
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xCC48155C
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xCC481560
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xCC481564
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xCC481568
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xCC48156C
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xCC481570
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xCC481574
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xCC481578
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xCC48157C
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xCC481580
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xCC481584
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xCC481588
	PE_O22_CC2_PE1_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xCC48158C
	UINT32                                                    reserved8;	//0xCC481590
	UINT32                                                    reserved9;	//0xCC481594
	UINT32                                                   reserved10;	//0xCC481598
	UINT32                                                   reserved11;	//0xCC48159C
	PE_O22_CC2_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xCC4815A0
	PE_O22_CC2_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xCC4815A4
	PE_O22_CC2_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xCC4815A8
	UINT32                                                   reserved12;	//0xCC4815AC
	PE_O22_CC2_PE1_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xCC4815B0
	PE_O22_CC2_PE1_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xCC4815B4
	PE_O22_CC2_PE1_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xCC4815B8
	UINT32                                                   reserved13;	//0xCC4815BC
	PE_O22_CC2_PE1_CW_CRGN_CTRL_00_T                   pe1_cw_crgn_ctrl_00;	//0xCC4815C0
	PE_O22_CC2_PE1_CW_CRGN_CTRL_01_T                   pe1_cw_crgn_ctrl_01;	//0xCC4815C4
	PE_O22_CC2_PE1_CW_CRGN_CTRL_02_T                   pe1_cw_crgn_ctrl_02;	//0xCC4815C8
	PE_O22_CC2_PE1_CW_CRGN_CTRL_03_T                   pe1_cw_crgn_ctrl_03;	//0xCC4815CC
	PE_O22_CC2_PE1_CW_CRGN_CTRL_04_T                   pe1_cw_crgn_ctrl_04;	//0xCC4815D0
	PE_O22_CC2_PE1_CW_CRGN_CTRL_05_T                   pe1_cw_crgn_ctrl_05;	//0xCC4815D4
	PE_O22_CC2_PE1_CW_CRGN_CTRL_06_T                   pe1_cw_crgn_ctrl_06;	//0xCC4815D8
	PE_O22_CC2_PE1_CW_CRGN_CTRL_07_T                   pe1_cw_crgn_ctrl_07;	//0xCC4815DC
	PE_O22_CC2_PE1_CW_CRGN_CTRL_08_T                   pe1_cw_crgn_ctrl_08;	//0xCC4815E0
	PE_O22_CC2_PE1_CW_CRGN_CTRL_09_T                   pe1_cw_crgn_ctrl_09;	//0xCC4815E4
	PE_O22_CC2_PE1_CW_CRGN_CTRL_10_T                   pe1_cw_crgn_ctrl_10;	//0xCC4815E8
	PE_O22_CC2_PE1_CW_CRGN_CTRL_11_T                   pe1_cw_crgn_ctrl_11;	//0xCC4815EC
	PE_O22_CC2_PE1_CW_CRGN_CTRL_12_T                   pe1_cw_crgn_ctrl_12;	//0xCC4815F0
	PE_O22_CC2_PE1_CW_CRGN_CTRL_13_T                   pe1_cw_crgn_ctrl_13;	//0xCC4815F4
	PE_O22_CC2_PE1_CW_CRGN_CTRL_14_T                   pe1_cw_crgn_ctrl_14;	//0xCC4815F8
	PE_O22_CC2_PE1_CW_CRGN_CTRL_15_T                   pe1_cw_crgn_ctrl_15;	//0xCC4815FC
	UINT32                                                   reserved14;	//0xCC481600
	UINT32                                                   reserved15;	//0xCC481604
	UINT32                                                   reserved16;	//0xCC481608
	UINT32                                                   reserved17;	//0xCC48160C
	PE_O22_CC2_PE1_LBLUR_CTRL_00_T                       pe1_lblur_ctrl_00;	//0xCC481610
	PE_O22_CC2_PE1_LBLUR_CTRL_01_T                       pe1_lblur_ctrl_01;	//0xCC481614
	PE_O22_CC2_PE1_LBLUR_CTRL_02_T                       pe1_lblur_ctrl_02;	//0xCC481618
	UINT32                                                   reserved18;	//0xCC48161C
	PE_O22_CC2_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0xCC481620
	PE_O22_CC2_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0xCC481624
	PE_O22_CC2_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0xCC481628
	PE_O22_CC2_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0xCC48162C
	PE_O22_CC2_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0xCC481630
	PE_O22_CC2_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0xCC481634
	PE_O22_CC2_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0xCC481638
	PE_O22_CC2_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0xCC48163C
	PE_O22_CC2_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0xCC481640
	PE_O22_CC2_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0xCC481644
	PE_O22_CC2_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0xCC481648
	PE_O22_CC2_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0xCC48164C
	PE_O22_CC2_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0xCC481650
	PE_O22_CC2_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0xCC481654
	PE_O22_CC2_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0xCC481658
	PE_O22_CC2_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0xCC48165C
	PE_O22_CC2_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0xCC481660
	PE_O22_CC2_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0xCC481664
	PE_O22_CC2_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0xCC481668
	PE_O22_CC2_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0xCC48166C
	PE_O22_CC2_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0xCC481670
	PE_O22_CC2_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0xCC481674
	PE_O22_CC2_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0xCC481678
	PE_O22_CC2_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0xCC48167C
	PE_O22_CC2_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0xCC481680
	PE_O22_CC2_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0xCC481684
	PE_O22_CC2_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0xCC481688
	PE_O22_CC2_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0xCC48168C
	PE_O22_CC2_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0xCC481690
	PE_O22_CC2_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0xCC481694
	PE_O22_CC2_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0xCC481698
	PE_O22_CC2_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0xCC48169C
	PE_O22_CC2_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0xCC4816A0
	PE_O22_CC2_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0xCC4816A4
	PE_O22_CC2_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0xCC4816A8
	PE_O22_CC2_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0xCC4816AC
	PE_O22_CC2_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0xCC4816B0
	PE_O22_CC2_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0xCC4816B4
	PE_O22_CC2_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0xCC4816B8
	PE_O22_CC2_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0xCC4816BC
	PE_O22_CC2_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0xCC4816C0
	PE_O22_CC2_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0xCC4816C4
	PE_O22_CC2_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0xCC4816C8
	PE_O22_CC2_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0xCC4816CC
	PE_O22_CC2_PE1_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0xCC4816D0
	PE_O22_CC2_PE1_LOGO_CTRL_45_T                         pe1_logo_ctrl_45;	//0xCC4816D4
	PE_O22_CC2_PE1_LOGO_CTRL_46_T                         pe1_logo_ctrl_46;	//0xCC4816D8
	PE_O22_CC2_PE1_LOGO_CTRL_47_T                         pe1_logo_ctrl_47;	//0xCC4816DC
	PE_O22_CC2_PE1_LOGO_CTRL_48_T                         pe1_logo_ctrl_48;	//0xCC4816E0
	PE_O22_CC2_PE1_LOGO_CTRL_49_T                         pe1_logo_ctrl_49;	//0xCC4816E4
	PE_O22_CC2_PE1_LOGO_CTRL_50_T                         pe1_logo_ctrl_50;	//0xCC4816E8
	PE_O22_CC2_PE1_LOGO_CTRL_51_T                         pe1_logo_ctrl_51;	//0xCC4816EC
	PE_O22_CC2_PE1_LOGO_CTRL_52_T                         pe1_logo_ctrl_52;	//0xCC4816F0
	PE_O22_CC2_PE1_LOGO_CTRL_53_T                         pe1_logo_ctrl_53;	//0xCC4816F4
	PE_O22_CC2_PE1_LOGO_CTRL_54_T                         pe1_logo_ctrl_54;	//0xCC4816F8
	PE_O22_CC2_PE1_LOGO_CTRL_55_T                         pe1_logo_ctrl_55;	//0xCC4816FC
	PE_O22_CC2_PE1_LOGO_CTRL_56_T                         pe1_logo_ctrl_56;	//0xCC481700
	PE_O22_CC2_PE1_LOGO_CTRL_57_T                         pe1_logo_ctrl_57;	//0xCC481704
	PE_O22_CC2_PE1_LOGO_CTRL_58_T                         pe1_logo_ctrl_58;	//0xCC481708
	PE_O22_CC2_PE1_LOGO_CTRL_59_T                         pe1_logo_ctrl_59;	//0xCC48170C
	PE_O22_CC2_PE1_LOGO_CTRL_60_T                         pe1_logo_ctrl_60;	//0xCC481710
	UINT32                                                   reserved19;	//0xCC481714
	UINT32                                                   reserved20;	//0xCC481718
	UINT32                                                   reserved21;	//0xCC48171C
	PE_O22_CC2_PE1_GSR_CTRL_00_T                           pe1_gsr_ctrl_00;	//0xCC481720
	PE_O22_CC2_PE1_GSR_CTRL_01_T                           pe1_gsr_ctrl_01;	//0xCC481724
	PE_O22_CC2_PE1_GSR_CTRL_02_T                           pe1_gsr_ctrl_02;	//0xCC481728
	PE_O22_CC2_PE1_GSR_CTRL_03_T                           pe1_gsr_ctrl_03;	//0xCC48172C
	PE_O22_CC2_PE1_GSR_CTRL_04_T                           pe1_gsr_ctrl_04;	//0xCC481730
	PE_O22_CC2_PE1_GSR_CTRL_05_T                           pe1_gsr_ctrl_05;	//0xCC481734
	PE_O22_CC2_PE1_GSR_CTRL_06_T                           pe1_gsr_ctrl_06;	//0xCC481738
	PE_O22_CC2_PE1_GSR_CTRL_07_T                           pe1_gsr_ctrl_07;	//0xCC48173C
	PE_O22_CC2_PE1_GSR_CTRL_08_T                           pe1_gsr_ctrl_08;	//0xCC481740
	PE_O22_CC2_PE1_GSR_CTRL_09_T                           pe1_gsr_ctrl_09;	//0xCC481744
	PE_O22_CC2_PE1_GSR_CTRL_10_T                           pe1_gsr_ctrl_10;	//0xCC481748
	PE_O22_CC2_PE1_GSR_CTRL_11_T                           pe1_gsr_ctrl_11;	//0xCC48174C
	PE_O22_CC2_PE1_GSR_CTRL_12_T                           pe1_gsr_ctrl_12;	//0xCC481750
	PE_O22_CC2_PE1_GSR_CTRL_13_T                           pe1_gsr_ctrl_13;	//0xCC481754
	PE_O22_CC2_PE1_GSR_CTRL_14_T                           pe1_gsr_ctrl_14;	//0xCC481758
	PE_O22_CC2_PE1_GSR_CTRL_15_T                           pe1_gsr_ctrl_15;	//0xCC48175C
	PE_O22_CC2_PE1_GSR_CTRL_16_T                           pe1_gsr_ctrl_16;	//0xCC481760
	PE_O22_CC2_PE1_GSR_CTRL_17_T                           pe1_gsr_ctrl_17;	//0xCC481764
	PE_O22_CC2_PE1_GSR_CTRL_18_T                           pe1_gsr_ctrl_18;	//0xCC481768
	PE_O22_CC2_PE1_GSR_CTRL_19_T                           pe1_gsr_ctrl_19;	//0xCC48176C
	PE_O22_CC2_PE1_GSR_CTRL_20_T                           pe1_gsr_ctrl_20;	//0xCC481770
	PE_O22_CC2_PE1_GSR_CTRL_21_T                           pe1_gsr_ctrl_21;	//0xCC481774
	PE_O22_CC2_PE1_GSR_CTRL_22_T                           pe1_gsr_ctrl_22;	//0xCC481778
	PE_O22_CC2_PE1_GSR_CTRL_23_T                           pe1_gsr_ctrl_23;	//0xCC48177C
	PE_O22_CC2_PE1_GSR_CTRL_24_T                           pe1_gsr_ctrl_24;	//0xCC481780
	PE_O22_CC2_PE1_GSR_CTRL_25_T                           pe1_gsr_ctrl_25;	//0xCC481784
	PE_O22_CC2_PE1_GSR_CTRL_26_T                           pe1_gsr_ctrl_26;	//0xCC481788
	PE_O22_CC2_PE1_GSR_CTRL_27_T                           pe1_gsr_ctrl_27;	//0xCC48178C
	PE_O22_CC2_PE1_GSR_CTRL_28_T                           pe1_gsr_ctrl_28;	//0xCC481790
	PE_O22_CC2_PE1_GSR_CTRL_29_T                           pe1_gsr_ctrl_29;	//0xCC481794
	PE_O22_CC2_PE1_GSR_CTRL_30_T                           pe1_gsr_ctrl_30;	//0xCC481798
	PE_O22_CC2_PE1_GSR_CTRL_31_T                           pe1_gsr_ctrl_31;	//0xCC48179C
	PE_O22_CC2_PE1_GSR_CTRL_32_T                           pe1_gsr_ctrl_32;	//0xCC4817A0
	PE_O22_CC2_PE1_GSR_CTRL_33_T                           pe1_gsr_ctrl_33;	//0xCC4817A4
	UINT32                                                   reserved22;	//0xCC4817A8
	UINT32                                                   reserved23;	//0xCC4817AC
	UINT32                                                   reserved24;	//0xCC4817B0
	UINT32                                                   reserved25;	//0xCC4817B4
	UINT32                                                   reserved26;	//0xCC4817B8
	UINT32                                                   reserved27;	//0xCC4817BC
	UINT32                                                   reserved28;	//0xCC4817C0
	UINT32                                                   reserved29;	//0xCC4817C4
	UINT32                                                   reserved30;	//0xCC4817C8
	UINT32                                                   reserved31;	//0xCC4817CC
	UINT32                                                   reserved32;	//0xCC4817D0
	UINT32                                                   reserved33;	//0xCC4817D4
	UINT32                                                   reserved34;	//0xCC4817D8
	UINT32                                                   reserved35;	//0xCC4817DC
	PE_O22_CC2_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xCC4817E0
	PE_O22_CC2_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xCC4817E4
	PE_O22_CC2_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xCC4817E8
	PE_O22_CC2_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xCC4817EC
	PE_O22_CC2_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xCC4817F0
	PE_O22_CC2_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xCC4817F4
	PE_O22_CC2_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xCC4817F8
	PE_O22_CC2_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xCC4817FC
	PE_O22_CC2_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xCC481800
	PE_O22_CC2_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xCC481804
	PE_O22_CC2_PE1_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xCC481808
	PE_O22_CC2_PE1_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xCC48180C
	PE_O22_CC2_PE1_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xCC481810
	PE_O22_CC2_PE1_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xCC481814
	PE_O22_CC2_PE1_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xCC481818
	PE_O22_CC2_PE1_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xCC48181C
	PE_O22_CC2_PE1_MUTE_CTRL_16_T                         pe1_mute_ctrl_16;	//0xCC481820
	PE_O22_CC2_PE1_MUTE_CTRL_17_T                         pe1_mute_ctrl_17;	//0xCC481824
	PE_O22_CC2_PE1_MUTE_CTRL_18_T                         pe1_mute_ctrl_18;	//0xCC481828
	PE_O22_CC2_PE1_MUTE_CTRL_19_T                         pe1_mute_ctrl_19;	//0xCC48182C
	PE_O22_CC2_PE1_MUTE_CTRL_20_T                         pe1_mute_ctrl_20;	//0xCC481830
	PE_O22_CC2_PE1_MUTE_CTRL_21_T                         pe1_mute_ctrl_21;	//0xCC481834
	PE_O22_CC2_PE1_MUTE_CTRL_22_T                         pe1_mute_ctrl_22;	//0xCC481838
	PE_O22_CC2_PE1_MUTE_CTRL_23_T                         pe1_mute_ctrl_23;	//0xCC48183C
	UINT32                                                   reserved36;	//0xCC481840
	UINT32                                                   reserved37;	//0xCC481844
	UINT32                                                   reserved38;	//0xCC481848
	UINT32                                                   reserved39;	//0xCC48184C
	UINT32                                                   reserved40;	//0xCC481850
	UINT32                                                   reserved41;	//0xCC481854
	UINT32                                                   reserved42;	//0xCC481858
	UINT32                                                   reserved43;	//0xCC48185C
	UINT32                                                   reserved44;	//0xCC481860
	UINT32                                                   reserved45;	//0xCC481864
	UINT32                                                   reserved46;	//0xCC481868
	UINT32                                                   reserved47;	//0xCC48186C
	UINT32                                                   reserved48;	//0xCC481870
	UINT32                                                   reserved49;	//0xCC481874
	UINT32                                                   reserved50;	//0xCC481878
	UINT32                                                   reserved51;	//0xCC48187C
	UINT32                                                   reserved52;	//0xCC481880
	UINT32                                                   reserved53;	//0xCC481884
	UINT32                                                   reserved54;	//0xCC481888
	UINT32                                                   reserved55;	//0xCC48188C
	UINT32                                                   reserved56;	//0xCC481890
	UINT32                                                   reserved57;	//0xCC481894
	UINT32                                                   reserved58;	//0xCC481898
	UINT32                                                   reserved59;	//0xCC48189C
	UINT32                                                   reserved60;	//0xCC4818A0
	UINT32                                                   reserved61;	//0xCC4818A4
	UINT32                                                   reserved62;	//0xCC4818A8
	UINT32                                                   reserved63;	//0xCC4818AC
	UINT32                                                   reserved64;	//0xCC4818B0
	UINT32                                                   reserved65;	//0xCC4818B4
	UINT32                                                   reserved66;	//0xCC4818B8
	UINT32                                                   reserved67;	//0xCC4818BC
	UINT32                                                   reserved68;	//0xCC4818C0
	UINT32                                                   reserved69;	//0xCC4818C4
	UINT32                                                   reserved70;	//0xCC4818C8
	UINT32                                                   reserved71;	//0xCC4818CC
	UINT32                                                   reserved72;	//0xCC4818D0
	UINT32                                                   reserved73;	//0xCC4818D4
	UINT32                                                   reserved74;	//0xCC4818D8
	UINT32                                                   reserved75;	//0xCC4818DC
	UINT32                                                   reserved76;	//0xCC4818E0
	UINT32                                                   reserved77;	//0xCC4818E4
	UINT32                                                   reserved78;	//0xCC4818E8
	UINT32                                                   reserved79;	//0xCC4818EC
	UINT32                                                   reserved80;	//0xCC4818F0
	UINT32                                                   reserved81;	//0xCC4818F4
	UINT32                                                   reserved82;	//0xCC4818F8
	UINT32                                                   reserved83;	//0xCC4818FC
	UINT32                                                   reserved84;	//0xCC481900
	UINT32                                                   reserved85;	//0xCC481904
	UINT32                                                   reserved86;	//0xCC481908
	UINT32                                                   reserved87;	//0xCC48190C
	PE_O22_CC2_PE1_MERGE_CTRL_00_T                       pe1_merge_ctrl_00;	//0xCC481910
	PE_O22_CC2_PE1_MERGE_CTRL_01_T                       pe1_merge_ctrl_01;	//0xCC481914
	PE_O22_CC2_PE1_MERGE_CTRL_02_T                       pe1_merge_ctrl_02;	//0xCC481918
	PE_O22_CC2_PE1_MERGE_CTRL_03_T                       pe1_merge_ctrl_03;	//0xCC48191C
	PE_O22_CC2_PE1_MERGE_CTRL_04_T                       pe1_merge_ctrl_04;	//0xCC481920
	PE_O22_CC2_PE1_MERGE_CTRL_05_T                       pe1_merge_ctrl_05;	//0xCC481924
	PE_O22_CC2_PE1_MERGE_CTRL_06_T                       pe1_merge_ctrl_06;	//0xCC481928
	PE_O22_CC2_PE1_MERGE_CTRL_07_T                       pe1_merge_ctrl_07;	//0xCC48192C
	PE_O22_CC2_PE1_MERGE_CTRL_08_T                       pe1_merge_ctrl_08;	//0xCC481930
	PE_O22_CC2_PE1_MERGE_CTRL_09_T                       pe1_merge_ctrl_09;	//0xCC481934
	PE_O22_CC2_PE1_MERGE_CTRL_10_T                       pe1_merge_ctrl_10;	//0xCC481938
	PE_O22_CC2_PE1_MERGE_CTRL_11_T                       pe1_merge_ctrl_11;	//0xCC48193C
	PE_O22_CC2_PE1_MERGE_CTRL_12_T                       pe1_merge_ctrl_12;	//0xCC481940
	PE_O22_CC2_PE1_MERGE_CTRL_13_T                       pe1_merge_ctrl_13;	//0xCC481944
	PE_O22_CC2_PE1_MERGE_CTRL_14_T                       pe1_merge_ctrl_14;	//0xCC481948
	PE_O22_CC2_PE1_MERGE_CTRL_15_T                       pe1_merge_ctrl_15;	//0xCC48194C
	PE_O22_CC2_PE1_MERGE_CTRL_16_T                       pe1_merge_ctrl_16;	//0xCC481950
	PE_O22_CC2_PE1_MERGE_CTRL_17_T                       pe1_merge_ctrl_17;	//0xCC481954
	PE_O22_CC2_PE1_MERGE_CTRL_18_T                       pe1_merge_ctrl_18;	//0xCC481958
	PE_O22_CC2_PE1_MERGE_CTRL_19_T                       pe1_merge_ctrl_19;	//0xCC48195C
	PE_O22_CC2_PE1_MERGE_CTRL_20_T                       pe1_merge_ctrl_20;	//0xCC481960
	PE_O22_CC2_PE1_MERGE_CTRL_21_T                       pe1_merge_ctrl_21;	//0xCC481964
	PE_O22_CC2_PE1_MERGE_CTRL_22_T                       pe1_merge_ctrl_22;	//0xCC481968
	PE_O22_CC2_PE1_MERGE_CTRL_23_T                       pe1_merge_ctrl_23;	//0xCC48196C
	PE_O22_CC2_PE1_MERGE_CTRL_24_T                       pe1_merge_ctrl_24;	//0xCC481970
	PE_O22_CC2_PE1_MERGE_CTRL_25_T                       pe1_merge_ctrl_25;	//0xCC481974
	PE_O22_CC2_PE1_MERGE_CTRL_26_T                       pe1_merge_ctrl_26;	//0xCC481978
	PE_O22_CC2_PE1_MERGE_CTRL_27_T                       pe1_merge_ctrl_27;	//0xCC48197C
	PE_O22_CC2_PE1_MERGE_CTRL_28_T                       pe1_merge_ctrl_28;	//0xCC481980
	PE_O22_CC2_PE1_MERGE_CTRL_29_T                       pe1_merge_ctrl_29;	//0xCC481984
	PE_O22_CC2_PE1_MERGE_CTRL_30_T                       pe1_merge_ctrl_30;	//0xCC481988
	PE_O22_CC2_PE1_MERGE_CTRL_31_T                       pe1_merge_ctrl_31;	//0xCC48198C
	PE_O22_CC2_PE1_MERGE_CTRL_32_T                       pe1_merge_ctrl_32;	//0xCC481990
	PE_O22_CC2_PE1_MERGE_CTRL_33_T                       pe1_merge_ctrl_33;	//0xCC481994
	PE_O22_CC2_PE1_MERGE_CTRL_34_T                       pe1_merge_ctrl_34;	//0xCC481998
	PE_O22_CC2_PE1_MERGE_CTRL_35_T                       pe1_merge_ctrl_35;	//0xCC48199C
	PE_O22_CC2_PE1_MERGE_CTRL_36_T                       pe1_merge_ctrl_36;	//0xCC4819A0
	PE_O22_CC2_PE1_MERGE_CTRL_37_T                       pe1_merge_ctrl_37;	//0xCC4819A4
	PE_O22_CC2_PE1_MERGE_CTRL_38_T                       pe1_merge_ctrl_38;	//0xCC4819A8
	PE_O22_CC2_PE1_MERGE_CTRL_39_T                       pe1_merge_ctrl_39;	//0xCC4819AC
	PE_O22_CC2_PE1_MERGE_CTRL_40_T                       pe1_merge_ctrl_40;	//0xCC4819B0
	PE_O22_CC2_PE1_MERGE_CTRL_41_T                       pe1_merge_ctrl_41;	//0xCC4819B4
	PE_O22_CC2_PE1_MERGE_CTRL_42_T                       pe1_merge_ctrl_42;	//0xCC4819B8
	PE_O22_CC2_PE1_MERGE_CTRL_43_T                       pe1_merge_ctrl_43;	//0xCC4819BC
	PE_O22_CC2_PE1_MERGE_CTRL_44_T                       pe1_merge_ctrl_44;	//0xCC4819C0
	PE_O22_CC2_PE1_MERGE_CTRL_45_T                       pe1_merge_ctrl_45;	//0xCC4819C4
	PE_O22_CC2_PE1_MERGE_CTRL_46_T                       pe1_merge_ctrl_46;	//0xCC4819C8
	PE_O22_CC2_PE1_MERGE_CTRL_47_T                       pe1_merge_ctrl_47;	//0xCC4819CC
	PE_O22_CC2_PE1_MERGE_CTRL_48_T                       pe1_merge_ctrl_48;	//0xCC4819D0
	PE_O22_CC2_PE1_MERGE_CTRL_49_T                       pe1_merge_ctrl_49;	//0xCC4819D4
	UINT32                                                   reserved88;	//0xCC4819D8
	UINT32                                                   reserved89;	//0xCC4819DC
	PE_O22_CC2_PE1_LOGO_CTRL_61_T                         pe1_logo_ctrl_61;	//0xCC4819E0
	PE_O22_CC2_PE1_LOGO_CTRL_62_T                         pe1_logo_ctrl_62;	//0xCC4819E4
	PE_O22_CC2_PE1_LOGO_CTRL_63_T                         pe1_logo_ctrl_63;	//0xCC4819E8
	PE_O22_CC2_PE1_LOGO_CTRL_64_T                         pe1_logo_ctrl_64;	//0xCC4819EC
	PE_O22_CC2_PE1_LOGO_CTRL_65_T                         pe1_logo_ctrl_65;	//0xCC4819F0
	PE_O22_CC2_PE1_LOGO_CTRL_66_T                         pe1_logo_ctrl_66;	//0xCC4819F4
	PE_O22_CC2_PE1_LOGO_CTRL_67_T                         pe1_logo_ctrl_67;	//0xCC4819F8
	PE_O22_CC2_PE1_LOGO_CTRL_68_T                         pe1_logo_ctrl_68;	//0xCC4819FC
	PE_O22_CC2_PE1_LOGO_CTRL_69_T                         pe1_logo_ctrl_69;	//0xCC481A00
	PE_O22_CC2_PE1_LOGO_CTRL_70_T                         pe1_logo_ctrl_70;	//0xCC481A04
	PE_O22_CC2_PE1_LOGO_CTRL_71_T                         pe1_logo_ctrl_71;	//0xCC481A08
	PE_O22_CC2_PE1_LOGO_CTRL_72_T                         pe1_logo_ctrl_72;	//0xCC481A0C
	PE_O22_CC2_PE1_LOGO_CTRL_73_T                         pe1_logo_ctrl_73;	//0xCC481A10
	PE_O22_CC2_PE1_LOGO_CTRL_74_T                         pe1_logo_ctrl_74;	//0xCC481A14
	PE_O22_CC2_PE1_LOGO_CTRL_75_T                         pe1_logo_ctrl_75;	//0xCC481A18
	PE_O22_CC2_PE1_LOGO_CTRL_76_T                         pe1_logo_ctrl_76;	//0xCC481A1C
	PE_O22_CC2_PE1_LOGO_CTRL_77_T                         pe1_logo_ctrl_77;	//0xCC481A20
	PE_O22_CC2_PE1_LOGO_CTRL_78_T                         pe1_logo_ctrl_78;	//0xCC481A24
	PE_O22_CC2_PE1_LOGO_CTRL_79_T                         pe1_logo_ctrl_79;	//0xCC481A28
	PE_O22_CC2_PE1_LOGO_CTRL_80_T                         pe1_logo_ctrl_80;	//0xCC481A2C
	PE_O22_CC2_PE1_LOGO_CTRL_81_T                         pe1_logo_ctrl_81;	//0xCC481A30
	PE_O22_CC2_PE1_LOGO_CTRL_82_T                         pe1_logo_ctrl_82;	//0xCC481A34
	PE_O22_CC2_PE1_LOGO_CTRL_83_T                         pe1_logo_ctrl_83;	//0xCC481A38
	PE_O22_CC2_PE1_LOGO_CTRL_84_T                         pe1_logo_ctrl_84;	//0xCC481A3C
	PE_O22_CC2_PE1_LOGO_CTRL_85_T                         pe1_logo_ctrl_85;	//0xCC481A40
}PE_CC2_PE1_REG_O22_T;

typedef struct {
	PE_O22_CC_PE1_TOP_CTRL_00_T                            pe1_top_ctrl_00;	//0xCC481000
	PE_O22_CC_PE1_TOP_CTRL_01_T                            pe1_top_ctrl_01;	//0xCC481004
	PE_O22_CC_PE1_TOP_CTRL_02_T                            pe1_top_ctrl_02;	//0xCC481008
	PE_O22_CC_PE1_TOP_CTRL_03_T                            pe1_top_ctrl_03;	//0xCC48100C
	PE_O22_CC_PE1_TOP_CTRL_04_T                            pe1_top_ctrl_04;	//0xCC481010
	UINT32                                                    reserved0;	//0xCC481014
	UINT32                                                    reserved1;	//0xCC481018
	UINT32                                                    reserved2;	//0xCC48101C
	PE_O22_CC_PE1_FSW_CTRL_00_T                            pe1_fsw_ctrl_00;	//0xCC481020
	PE_O22_CC_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xCC481024
	PE_O22_CC_PE1_FSW_CTRL_02_T                            pe1_fsw_ctrl_02;	//0xCC481028
	PE_O22_CC_PE1_FSW_CTRL_03_T                            pe1_fsw_ctrl_03;	//0xCC48102C
	PE_O22_CC_PE1_FSW_CTRL_04_T                            pe1_fsw_ctrl_04;	//0xCC481030
	PE_O22_CC_PE1_FSW_CTRL_05_T                            pe1_fsw_ctrl_05;	//0xCC481034
	PE_O22_CC_PE1_FSW_CTRL_06_T                            pe1_fsw_ctrl_06;	//0xCC481038
	PE_O22_CC_PE1_FSW_CTRL_07_T                            pe1_fsw_ctrl_07;	//0xCC48103C
	UINT32                                                    reserved3;	//0xCC481040
	UINT32                                                    reserved4;	//0xCC481044
	UINT32                                                    reserved5;	//0xCC481048
	UINT32                                                    reserved6;	//0xCC48104C
	PE_O22_CC_PE1_TPG_CTRL_00_T                            pe1_tpg_ctrl_00;	//0xCC481050
	PE_O22_CC_PE1_TPG_CTRL_01_T                            pe1_tpg_ctrl_01;	//0xCC481054
	PE_O22_CC_PE1_TPG_CTRL_02_T                            pe1_tpg_ctrl_02;	//0xCC481058
	PE_O22_CC_PE1_TPG_CTRL_03_T                            pe1_tpg_ctrl_03;	//0xCC48105C
	PE_O22_CC_PE1_TPG_CTRL_04_T                            pe1_tpg_ctrl_04;	//0xCC481060
	PE_O22_CC_PE1_TPG_IA_CTRL_T                            pe1_tpg_ia_ctrl;	//0xCC481064
	PE_O22_CC_PE1_TPG_IA_DATA_T                            pe1_tpg_ia_data;	//0xCC481068
	UINT32                                                    reserved7;	//0xCC48106C
	PE_O22_CC_PE1_APL_CTRL_00_T                            pe1_apl_ctrl_00;	//0xCC481070
	PE_O22_CC_PE1_APL_CTRL_01_T                            pe1_apl_ctrl_01;	//0xCC481074
	PE_O22_CC_PE1_APL_CTRL_02_T                            pe1_apl_ctrl_02;	//0xCC481078
	PE_O22_CC_PE1_APL_CTRL_03_T                            pe1_apl_ctrl_03;	//0xCC48107C
	PE_O22_CC_PE1_APL_CTRL_04_T                            pe1_apl_ctrl_04;	//0xCC481080
	PE_O22_CC_PE1_APL_CTRL_05_T                            pe1_apl_ctrl_05;	//0xCC481084
	PE_O22_CC_PE1_APL_CTRL_06_T                            pe1_apl_ctrl_06;	//0xCC481088
	PE_O22_CC_PE1_APL_CTRL_07_T                            pe1_apl_ctrl_07;	//0xCC48108C
	PE_O22_CC_PE1_APL_CTRL_08_T                            pe1_apl_ctrl_08;	//0xCC481090
	UINT32                                                    reserved8;	//0xCC481094
	UINT32                                                    reserved9;	//0xCC481098
	UINT32                                                   reserved10;	//0xCC48109C
	UINT32                                                   reserved11;	//0xCC4810A0
	UINT32                                                   reserved12;	//0xCC4810A4
	UINT32                                                   reserved13;	//0xCC4810A8
	UINT32                                                   reserved14;	//0xCC4810AC
	UINT32                                                   reserved15;	//0xCC4810B0
	PE_O22_CC_PE1_APL_STAT_00_T                            pe1_apl_stat_00;	//0xCC4810B4
	PE_O22_CC_PE1_APL_STAT_01_T                            pe1_apl_stat_01;	//0xCC4810B8
	UINT32                                                   reserved16;	//0xCC4810BC
	PE_O22_CC_PE1_BT20_CTRL_00_T                          pe1_bt20_ctrl_00;	//0xCC4810C0
	PE_O22_CC_PE1_BT20_CTRL_01_T                          pe1_bt20_ctrl_01;	//0xCC4810C4
	PE_O22_CC_PE1_BT20_CTRL_02_T                          pe1_bt20_ctrl_02;	//0xCC4810C8
	PE_O22_CC_PE1_BT20_CTRL_03_T                          pe1_bt20_ctrl_03;	//0xCC4810CC
	PE_O22_CC_PE1_BT20_CTRL_04_T                          pe1_bt20_ctrl_04;	//0xCC4810D0
	PE_O22_CC_PE1_BT20_CTRL_05_T                          pe1_bt20_ctrl_05;	//0xCC4810D4
	PE_O22_CC_PE1_BT20_CTRL_06_T                          pe1_bt20_ctrl_06;	//0xCC4810D8
	PE_O22_CC_PE1_BT20_CTRL_07_T                          pe1_bt20_ctrl_07;	//0xCC4810DC
	PE_O22_CC_PE1_BT20_CTRL_08_T                          pe1_bt20_ctrl_08;	//0xCC4810E0
	PE_O22_CC_PE1_BT20_CTRL_09_T                          pe1_bt20_ctrl_09;	//0xCC4810E4
	PE_O22_CC_PE1_BT20_CTRL_10_T                          pe1_bt20_ctrl_10;	//0xCC4810E8
	PE_O22_CC_PE1_BT20_CTRL_11_T                          pe1_bt20_ctrl_11;	//0xCC4810EC
	PE_O22_CC_PE1_BT20_CTRL_12_T                          pe1_bt20_ctrl_12;	//0xCC4810F0
	PE_O22_CC_PE1_BT20_CTRL_13_T                          pe1_bt20_ctrl_13;	//0xCC4810F4
	PE_O22_CC_PE1_BT20_CTRL_14_T                          pe1_bt20_ctrl_14;	//0xCC4810F8
	PE_O22_CC_PE1_BT20_CTRL_15_T                          pe1_bt20_ctrl_15;	//0xCC4810FC
	PE_O22_CC_PE1_BT20_CTRL_16_T                          pe1_bt20_ctrl_16;	//0xCC481100
	PE_O22_CC_PE1_BT20_CTRL_17_T                          pe1_bt20_ctrl_17;	//0xCC481104
	PE_O22_CC_PE1_BT20_CTRL_18_T                          pe1_bt20_ctrl_18;	//0xCC481108
	PE_O22_CC_PE1_BT20_CTRL_19_T                          pe1_bt20_ctrl_19;	//0xCC48110C
	PE_O22_CC_PE1_BT20_CTRL_20_T                          pe1_bt20_ctrl_20;	//0xCC481110
	PE_O22_CC_PE1_BT20_CTRL_21_T                          pe1_bt20_ctrl_21;	//0xCC481114
	PE_O22_CC_PE1_BT20_CTRL_STAT_00_T                pe1_bt20_ctrl_stat_00;	//0xCC481118
	PE_O22_CC_PE1_BT20_CTRL_STAT_01_T                pe1_bt20_ctrl_stat_01;	//0xCC48111C
	PE_O22_CC_PE1_BT20_CTRL_STAT_02_T                pe1_bt20_ctrl_stat_02;	//0xCC481120
	PE_O22_CC_PE1_BT20_CTRL_STAT_03_T                pe1_bt20_ctrl_stat_03;	//0xCC481124
	UINT32                                                   reserved17;	//0xCC481128
	UINT32                                                   reserved18;	//0xCC48112C
	UINT32                                                   reserved19;	//0xCC481130
	UINT32                                                   reserved20;	//0xCC481134
	UINT32                                                   reserved21;	//0xCC481138
	UINT32                                                   reserved22;	//0xCC48113C
	PE_O22_CC_PE1_WIN2_CTRL_00_T                          pe1_win2_ctrl_00;	//0xCC481140
	PE_O22_CC_PE1_WIN2_CTRL_01_T                          pe1_win2_ctrl_01;	//0xCC481144
	PE_O22_CC_PE1_WIN2_CTRL_02_T                          pe1_win2_ctrl_02;	//0xCC481148
	PE_O22_CC_PE1_WIN2_CTRL_03_T                          pe1_win2_ctrl_03;	//0xCC48114C
	PE_O22_CC_PE1_WIN2_CTRL_04_T                          pe1_win2_ctrl_04;	//0xCC481150
	PE_O22_CC_PE1_WIN2_CTRL_05_T                          pe1_win2_ctrl_05;	//0xCC481154
	PE_O22_CC_PE1_WIN2_CTRL_06_T                          pe1_win2_ctrl_06;	//0xCC481158
	PE_O22_CC_PE1_WIN2_CTRL_07_T                          pe1_win2_ctrl_07;	//0xCC48115C
	PE_O22_CC_PE1_WIN2_CTRL_08_T                          pe1_win2_ctrl_08;	//0xCC481160
	UINT32                                                   reserved23;	//0xCC481164
	UINT32                                                   reserved24;	//0xCC481168
	UINT32                                                   reserved25;	//0xCC48116C
	UINT32                                                   reserved26;	//0xCC481170
	UINT32                                                   reserved27;	//0xCC481174
	UINT32                                                   reserved28;	//0xCC481178
	UINT32                                                   reserved29;	//0xCC48117C
	UINT32                                                   reserved30;	//0xCC481180
	UINT32                                                   reserved31;	//0xCC481184
	UINT32                                                   reserved32;	//0xCC481188
	UINT32                                                   reserved33;	//0xCC48118C
	UINT32                                                   reserved34;	//0xCC481190
	UINT32                                                   reserved35;	//0xCC481194
	UINT32                                                   reserved36;	//0xCC481198
	UINT32                                                   reserved37;	//0xCC48119C
	UINT32                                                   reserved38;	//0xCC4811A0
	UINT32                                                   reserved39;	//0xCC4811A4
	UINT32                                                   reserved40;	//0xCC4811A8
	UINT32                                                   reserved41;	//0xCC4811AC
	UINT32                                                   reserved42;	//0xCC4811B0
	UINT32                                                   reserved43;	//0xCC4811B4
	UINT32                                                   reserved44;	//0xCC4811B8
	UINT32                                                   reserved45;	//0xCC4811BC
	UINT32                                                   reserved46;	//0xCC4811C0
	UINT32                                                   reserved47;	//0xCC4811C4
	UINT32                                                   reserved48;	//0xCC4811C8
	UINT32                                                   reserved49;	//0xCC4811CC
	PE_O22_CC_PE1_CEN_CTRL_00_T                            pe1_cen_ctrl_00;	//0xCC4811D0
	PE_O22_CC_PE1_CEN_CTRL_01_T                            pe1_cen_ctrl_01;	//0xCC4811D4
	PE_O22_CC_PE1_CEN_CTRL_02_T                            pe1_cen_ctrl_02;	//0xCC4811D8
	PE_O22_CC_PE1_CEN_CTRL_03_T                            pe1_cen_ctrl_03;	//0xCC4811DC
	PE_O22_CC_PE1_CEN_CTRL_04_T                            pe1_cen_ctrl_04;	//0xCC4811E0
	PE_O22_CC_PE1_CEN_CTRL_05_T                            pe1_cen_ctrl_05;	//0xCC4811E4
	PE_O22_CC_PE1_CEN_CTRL_06_T                            pe1_cen_ctrl_06;	//0xCC4811E8
	PE_O22_CC_PE1_CEN_CTRL_07_T                            pe1_cen_ctrl_07;	//0xCC4811EC
	UINT32                                                   reserved50;	//0xCC4811F0
	UINT32                                                   reserved51;	//0xCC4811F4
	PE_O22_CC_PE1_CEN_UPD_CTRL_T                          pe1_cen_upd_ctrl;	//0xCC4811F8
	UINT32                                                   reserved52;	//0xCC4811FC
	PE_O22_CC_PE1_CEN_IA_CTRL_T                            pe1_cen_ia_ctrl;	//0xCC481200
	PE_O22_CC_PE1_CEN_IA_DATA_T                            pe1_cen_ia_data;	//0xCC481204
	PE_O22_CC_PE1_CEN_DELTA_IA_CTRL_T                pe1_cen_delta_ia_ctrl;	//0xCC481208
	PE_O22_CC_PE1_CEN_DELTA_IA_DATA_T                pe1_cen_delta_ia_data;	//0xCC48120C
	UINT32                                                   reserved53;	//0xCC481210
	UINT32                                                   reserved54;	//0xCC481214
	UINT32                                                   reserved55;	//0xCC481218
	UINT32                                                   reserved56;	//0xCC48121C
	PE_O22_CC_PE1_DCE_CTRL_00_T                            pe1_dce_ctrl_00;	//0xCC481220
	PE_O22_CC_PE1_DCE_CTRL_01_T                            pe1_dce_ctrl_01;	//0xCC481224
	PE_O22_CC_PE1_DCE_CTRL_02_T                            pe1_dce_ctrl_02;	//0xCC481228
	PE_O22_CC_PE1_DCE_CTRL_03_T                            pe1_dce_ctrl_03;	//0xCC48122C
	PE_O22_CC_PE1_DCE_CTRL_04_T                            pe1_dce_ctrl_04;	//0xCC481230
	PE_O22_CC_PE1_DCE_CTRL_05_T                            pe1_dce_ctrl_05;	//0xCC481234
	PE_O22_CC_PE1_DCE_IA_CTRL_T                            pe1_dce_ia_ctrl;	//0xCC481238
	PE_O22_CC_PE1_DCE_IA_DATA_T                            pe1_dce_ia_data;	//0xCC48123C
	PE_O22_CC_PE1_DCE_CTRL_08_T                            pe1_dce_ctrl_08;	//0xCC481240
	PE_O22_CC_PE1_DCE_CTRL_09_T                            pe1_dce_ctrl_09;	//0xCC481244
	PE_O22_CC_PE1_DCE_HIST_IA_CTRL_T                  pe1_dce_hist_ia_ctrl;	//0xCC481248
	PE_O22_CC_PE1_DCE_HIST_IA_DATA1_T                pe1_dce_hist_ia_data1;	//0xCC48124C
	PE_O22_CC_PE1_DCE_HIST_IA_DATA2_T                pe1_dce_hist_ia_data2;	//0xCC481250
	PE_O22_CC_PE1_DCE_CHR_GAIN_T                          pe1_dce_chr_gain;	//0xCC481254
	PE_O22_CC_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0xCC481258
	PE_O22_CC_PE1_DCE_CHR_GAIN2_T                        pe1_dce_chr_gain2;	//0xCC48125C
	UINT32                                                   reserved57;	//0xCC481260
	UINT32                                                   reserved58;	//0xCC481264
	UINT32                                                   reserved59;	//0xCC481268
	UINT32                                                   reserved60;	//0xCC48126C
	PE_O22_CC_PE1_DSE_CTRL_00_T                            pe1_dse_ctrl_00;	//0xCC481270
	PE_O22_CC_PE1_DSE_CTRL_01_T                            pe1_dse_ctrl_01;	//0xCC481274
	PE_O22_CC_PE1_DSE_CTRL_02_T                            pe1_dse_ctrl_02;	//0xCC481278
	PE_O22_CC_PE1_DSE_IA_CTRL_T                            pe1_dse_ia_ctrl;	//0xCC48127C
	PE_O22_CC_PE1_DSE_IA_DATA_T                            pe1_dse_ia_data;	//0xCC481280
	PE_O22_CC_PE1_DSE_CTRL_03_T                            pe1_dse_ctrl_03;	//0xCC481284
	PE_O22_CC_PE1_DSE_CTRL_04_T                            pe1_dse_ctrl_04;	//0xCC481288
	PE_O22_CC_PE_DSE_Y_REGION_PT0_T                    pe_dse_y_region_pt0;	//0xCC48128C
	PE_O22_CC_PE_DSE_Y_REGION_PT1_T                    pe_dse_y_region_pt1;	//0xCC481290
	PE_O22_CC_PE_DSE_Y_REGION_PT2_T                    pe_dse_y_region_pt2;	//0xCC481294
	PE_O22_CC_PE_DSE_Y_REGION_PT3_T                    pe_dse_y_region_pt3;	//0xCC481298
	PE_O22_CC_PE_DSE_Y_REGION_PT4_T                    pe_dse_y_region_pt4;	//0xCC48129C
	PE_O22_CC_PE_DSE_Y_REGION_PT5_T                    pe_dse_y_region_pt5;	//0xCC4812A0
	PE_O22_CC_PE_DSE_Y_REGION_PT6_T                    pe_dse_y_region_pt6;	//0xCC4812A4
	PE_O22_CC_PE_DSE_Y_REGION_PT7_T                    pe_dse_y_region_pt7;	//0xCC4812A8
	PE_O22_CC_PE_DSE_H_REGION_PT0_T                    pe_dse_h_region_pt0;	//0xCC4812AC
	PE_O22_CC_PE_DSE_H_REGION_PT1_T                    pe_dse_h_region_pt1;	//0xCC4812B0
	PE_O22_CC_PE_DSE_H_REGION_PT2_T                    pe_dse_h_region_pt2;	//0xCC4812B4
	PE_O22_CC_PE_DSE_H_REGION_PT3_T                    pe_dse_h_region_pt3;	//0xCC4812B8
	PE_O22_CC_PE_DSE_H_REGION_PT4_T                    pe_dse_h_region_pt4;	//0xCC4812BC
	PE_O22_CC_PE_DSE_H_REGION_PT5_T                    pe_dse_h_region_pt5;	//0xCC4812C0
	PE_O22_CC_PE_DSE_H_REGION_PT6_T                    pe_dse_h_region_pt6;	//0xCC4812C4
	PE_O22_CC_PE_DSE_H_REGION_PT7_T                    pe_dse_h_region_pt7;	//0xCC4812C8
	UINT32                                                   reserved61;	//0xCC4812CC
	UINT32                                                   reserved62;	//0xCC4812D0
	UINT32                                                   reserved63;	//0xCC4812D4
	UINT32                                                   reserved64;	//0xCC4812D8
	UINT32                                                   reserved65;	//0xCC4812DC
	PE_O22_CC_PE1_DRC_CTRL_00_T                            pe1_drc_ctrl_00;	//0xCC4812E0
	PE_O22_CC_PE1_DRC_CTRL_01_T                            pe1_drc_ctrl_01;	//0xCC4812E4
	PE_O22_CC_PE1_DRC_CTRL_02_T                            pe1_drc_ctrl_02;	//0xCC4812E8
	PE_O22_CC_PE1_DRC_CTRL_03_T                            pe1_drc_ctrl_03;	//0xCC4812EC
	PE_O22_CC_PE1_DRC_CTRL_04_T                            pe1_drc_ctrl_04;	//0xCC4812F0
	PE_O22_CC_PE1_DRC_CTRL_05_T                            pe1_drc_ctrl_05;	//0xCC4812F4
	PE_O22_CC_PE1_DRC_CTRL_06_T                            pe1_drc_ctrl_06;	//0xCC4812F8
	PE_O22_CC_PE1_DRC_CTRL_07_T                            pe1_drc_ctrl_07;	//0xCC4812FC
	PE_O22_CC_PE1_DRC_CTRL_08_T                            pe1_drc_ctrl_08;	//0xCC481300
	PE_O22_CC_PE1_DRC_CTRL_09_T                            pe1_drc_ctrl_09;	//0xCC481304
	PE_O22_CC_PE1_DRC_CTRL_10_T                            pe1_drc_ctrl_10;	//0xCC481308
	PE_O22_CC_PE1_DRC_CTRL_11_T                            pe1_drc_ctrl_11;	//0xCC48130C
	PE_O22_CC_PE1_DRC_CTRL_12_T                            pe1_drc_ctrl_12;	//0xCC481310
	PE_O22_CC_PE1_DRC_CTRL_13_T                            pe1_drc_ctrl_13;	//0xCC481314
	PE_O22_CC_PE1_DRC_CTRL_14_T                            pe1_drc_ctrl_14;	//0xCC481318
	PE_O22_CC_PE1_DRC_CTRL_15_T                            pe1_drc_ctrl_15;	//0xCC48131C
	PE_O22_CC_PE1_DRC_CTRL_16_T                            pe1_drc_ctrl_16;	//0xCC481320
	UINT32                                                   reserved66;	//0xCC481324
	UINT32                                                   reserved67;	//0xCC481328
	UINT32                                                   reserved68;	//0xCC48132C
	UINT32                                                   reserved69;	//0xCC481330
	PE_O22_CC_PE1_DRC_CTRL_21_T                            pe1_drc_ctrl_21;	//0xCC481334
	PE_O22_CC_PE1_DRC_CTRL_22_T                            pe1_drc_ctrl_22;	//0xCC481338
	PE_O22_CC_PE1_DRC_CTRL_23_T                            pe1_drc_ctrl_23;	//0xCC48133C
	PE_O22_CC_PE1_DRC_CTRL_24_T                            pe1_drc_ctrl_24;	//0xCC481340
	PE_O22_CC_PE1_DRC_CTRL_25_T                            pe1_drc_ctrl_25;	//0xCC481344
	PE_O22_CC_PE1_DRC_CTRL_26_T                            pe1_drc_ctrl_26;	//0xCC481348
	PE_O22_CC_PE1_DRC_CTRL_27_T                            pe1_drc_ctrl_27;	//0xCC48134C
	PE_O22_CC_PE1_DRC_CTRL_28_T                            pe1_drc_ctrl_28;	//0xCC481350
	PE_O22_CC_PE1_DRC_CTRL_29_T                            pe1_drc_ctrl_29;	//0xCC481354
	PE_O22_CC_PE1_DRC_CTRL_30_T                            pe1_drc_ctrl_30;	//0xCC481358
	UINT32                                                   reserved70;	//0xCC48135C
	UINT32                                                   reserved71;	//0xCC481360
	PE_O22_CC_PE1_DRC_CTRL_33_T                            pe1_drc_ctrl_33;	//0xCC481364
	PE_O22_CC_PE1_DRC_CTRL_34_T                            pe1_drc_ctrl_34;	//0xCC481368
	PE_O22_CC_PE1_DRC_CTRL_35_T                            pe1_drc_ctrl_35;	//0xCC48136C
	UINT32                                                   reserved72;	//0xCC481370
	UINT32                                                   reserved73;	//0xCC481374
	UINT32                                                   reserved74;	//0xCC481378
	UINT32                                                   reserved75;	//0xCC48137C
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_00_T                pe1_logo_l7sc_ctrl_00;	//0xCC481380
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_01_T                pe1_logo_l7sc_ctrl_01;	//0xCC481384
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_02_T                pe1_logo_l7sc_ctrl_02;	//0xCC481388
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_03_T                pe1_logo_l7sc_ctrl_03;	//0xCC48138C
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_04_T                pe1_logo_l7sc_ctrl_04;	//0xCC481390
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_05_T                pe1_logo_l7sc_ctrl_05;	//0xCC481394
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_06_T                pe1_logo_l7sc_ctrl_06;	//0xCC481398
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_07_T                pe1_logo_l7sc_ctrl_07;	//0xCC48139C
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_08_T                pe1_logo_l7sc_ctrl_08;	//0xCC4813A0
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_09_T                pe1_logo_l7sc_ctrl_09;	//0xCC4813A4
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_10_T                pe1_logo_l7sc_ctrl_10;	//0xCC4813A8
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_11_T                pe1_logo_l7sc_ctrl_11;	//0xCC4813AC
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_12_T                pe1_logo_l7sc_ctrl_12;	//0xCC4813B0
	PE_O22_CC_PE1_LOGO_L7SC_CTRL_13_T                pe1_logo_l7sc_ctrl_13;	//0xCC4813B4
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_00_T                pe1_logo_l3sc_ctrl_00;	//0xCC4813B8
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_01_T                pe1_logo_l3sc_ctrl_01;	//0xCC4813BC
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_02_T                pe1_logo_l3sc_ctrl_02;	//0xCC4813C0
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_03_T                pe1_logo_l3sc_ctrl_03;	//0xCC4813C4
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_04_T                pe1_logo_l3sc_ctrl_04;	//0xCC4813C8
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_05_T                pe1_logo_l3sc_ctrl_05;	//0xCC4813CC
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_06_T                pe1_logo_l3sc_ctrl_06;	//0xCC4813D0
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_07_T                pe1_logo_l3sc_ctrl_07;	//0xCC4813D4
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_08_T                pe1_logo_l3sc_ctrl_08;	//0xCC4813D8
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_09_T                pe1_logo_l3sc_ctrl_09;	//0xCC4813DC
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_10_T                pe1_logo_l3sc_ctrl_10;	//0xCC4813E0
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_11_T                pe1_logo_l3sc_ctrl_11;	//0xCC4813E4
	PE_O22_CC_PE1_LOGO_L3SC_CTRL_12_T                pe1_logo_l3sc_ctrl_12;	//0xCC4813E8
	PE_O22_CC_PE1_LOGO_STAT_00_T                          pe1_logo_stat_00;	//0xCC4813EC
	PE_O22_CC_PE1_LOGO_STAT_01_T                          pe1_logo_stat_01;	//0xCC4813F0
	PE_O22_CC_PE1_LOGO_STAT_02_T                          pe1_logo_stat_02;	//0xCC4813F4
	PE_O22_CC_PE1_LOGO_STAT_03_T                          pe1_logo_stat_03;	//0xCC4813F8
	UINT32                                                   reserved76;	//0xCC4813FC
	UINT32                                                   reserved77;	//0xCC481400
	UINT32                                                   reserved78;	//0xCC481404
	UINT32                                                   reserved79;	//0xCC481408
	UINT32                                                   reserved80;	//0xCC48140C
	PE_O22_CC_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC481410
	PE_O22_CC_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC481414
	PE_O22_CC_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC481418
	PE_O22_CC_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC48141C
	PE_O22_CC_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC481420
	PE_O22_CC_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC481424
	PE_O22_CC_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC481428
	PE_O22_CC_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC48142C
	PE_O22_CC_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC481430
	PE_O22_CC_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xCC481434
	PE_O22_CC_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xCC481438
	PE_O22_CC_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xCC48143C
	PE_O22_CC_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xCC481440
	PE_O22_CC_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xCC481444
	PE_O22_CC_PE1_EOTF_RSATUS_T                            pe1_eotf_rsatus;	//0xCC481448
	UINT32                                                   reserved81;	//0xCC48144C
	PE_O22_CC_PE1_LLLUT_E_IA_CTRL_T                    pe1_lllut_e_ia_ctrl;	//0xCC481450
	PE_O22_CC_PE1_LLLUT_E_IA_DATA_T                    pe1_lllut_e_ia_data;	//0xCC481454
	PE_O22_CC_PE1_LLLUT_O_IA_CTRL_T                    pe1_lllut_o_ia_ctrl;	//0xCC481458
	PE_O22_CC_PE1_LLLUT_O_IA_DATA_T                    pe1_lllut_o_ia_data;	//0xCC48145C
	PE_O22_CC_PE1_LLCORE_CTRL_00_T                      pe1_llcore_ctrl_00;	//0xCC481460
	PE_O22_CC_PE1_LLCORE_CTRL_01_T                      pe1_llcore_ctrl_01;	//0xCC481464
	PE_O22_CC_PE1_LLCORE_CTRL_02_T                      pe1_llcore_ctrl_02;	//0xCC481468
	PE_O22_CC_PE1_LLCORE_CTRL_03_T                      pe1_llcore_ctrl_03;	//0xCC48146C
	PE_O22_CC_PE1_LLCORE_CTRL_04_T                      pe1_llcore_ctrl_04;	//0xCC481470
	PE_O22_CC_PE1_LLCORE_CTRL_05_T                      pe1_llcore_ctrl_05;	//0xCC481474
	PE_O22_CC_PE1_LLCORE_CTRL_06_T                      pe1_llcore_ctrl_06;	//0xCC481478
	PE_O22_CC_PE1_LLCORE_CTRL_07_T                      pe1_llcore_ctrl_07;	//0xCC48147C
	PE_O22_CC_PE1_LLCORE_CTRL_08_T                      pe1_llcore_ctrl_08;	//0xCC481480
	PE_O22_CC_PE1_LLCORE_CTRL_09_T                      pe1_llcore_ctrl_09;	//0xCC481484
	PE_O22_CC_PE1_LLCORE_CTRL_10_T                      pe1_llcore_ctrl_10;	//0xCC481488
	PE_O22_CC_PE1_LLCORE_CTRL_11_T                      pe1_llcore_ctrl_11;	//0xCC48148C
	PE_O22_CC_PE1_LLCORE_CTRL_12_T                      pe1_llcore_ctrl_12;	//0xCC481490
	PE_O22_CC_PE1_LLCORE_CTRL_13_T                      pe1_llcore_ctrl_13;	//0xCC481494
}PE_CC_PE1_REG_O22_T;


typedef union {
	UINT32 udata32;
	struct {						//0xC9012200 RW
	UINT32 run_status                   :8;	//31:0	//
	UINT32 run_count                    :16;	//31:0	//
	UINT32 db_status                   	:8;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012204 RW
	UINT32 posd_w                   :16;	//15:0	//
	UINT32 posd_h                   :16;	//31:16	//
	};
}PE_O22_CCO_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012208 RW
	UINT32 reg_sys_veri_2                   :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901220C RW
	UINT32 reg_sys_veri_3                   :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012210 RW
	UINT32 reg_sys_veri_4                   :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012214 RW
	UINT32 reg_sys_veri_5                   :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012218 RW
	UINT32 head_apl                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 body_apl                   :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O22_CCO_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901221C RW
	UINT32 head_map                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 depth_map                  :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O22_CCO_VERI_SYS_VERI_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012220 RW
	UINT32 contrast                    :16;	//(15:0,RW,0x0000_0000) //
	UINT32 brightness                 :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O22_CCO_VERI_SYS_VERI_8_T;

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
}PE_O22_CCO_VERI_SYS_VERI_9_T;

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
}PE_O22_CCO_VERI_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901222C RW 0x0000_0000
	UINT32 frate_in							:8;		//(7:0)		input frame rate
	UINT32 frate_out  		                :8;		//(15:8)	output frame rate
	UINT32 reserved  		                :16;	//(31:16)
	};
}PE_O22_CCO_VERI_SYS_VERI_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012230 RW
	UINT32 reg_sys_veri_12                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012234 RW
	UINT32 reg_sys_veri_13                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012238 RW
	UINT32 reg_sys_veri_14                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901223C RW
	UINT32 reg_sys_veri_15                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012240 RW
	UINT32 reg_sys_veri_16                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012244 RW
	UINT32 reg_sys_veri_17                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012248 RW
	UINT32 reg_sys_veri_18                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901224C RW
	UINT32 reg_sys_veri_19                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012250 RW
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012254 RW
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012258 RW
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901225C RW
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012260 RW
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012264 RW
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012268 RW
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901226C RW
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_O22_CCO_VERI_SYS_VERI_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012270 RW
	UINT32 reg_sys_veri_28                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012274 RW
	UINT32 reg_sys_veri_29                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012278 RW
	UINT32 reg_sys_veri_30                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901227C RW
	UINT32 reg_sys_veri_31                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012280 RW
	UINT32 reg_sys_veri_32                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012284 RW
	UINT32 reg_sys_veri_33                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9012288 RW
	UINT32 reg_sys_veri_34                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901228C RW
	UINT32 reg_sys_veri_35                  :32;	//31:0	//
	};
}PE_O22_CCO_VERI_SYS_VERI_35_T;

typedef struct {
	PE_O22_CCO_VERI_SYS_VERI_0_T                                f20_status;	//0xC9012200
	PE_O22_CCO_VERI_SYS_VERI_1_T                                posd_wh;		//0xC9012204
	PE_O22_CCO_VERI_SYS_VERI_2_T                                posd_xy;		//0xC9012208
	PE_O22_CCO_VERI_SYS_VERI_3_T                                sys_veri_3;	//0xC901220C
	PE_O22_CCO_VERI_SYS_VERI_4_T                                sys_veri_4;	//0xC9012210
	PE_O22_CCO_VERI_SYS_VERI_5_T                                sys_veri_5;	//0xC9012214
	PE_O22_CCO_VERI_SYS_VERI_6_T                                sys_veri_6;	//0xC9012218
	PE_O22_CCO_VERI_SYS_VERI_7_T                                sys_veri_7;	//0xC901221C
	PE_O22_CCO_VERI_SYS_VERI_8_T                                sys_veri_8;	//0xC9012220
	PE_O22_CCO_VERI_SYS_VERI_9_T                                sys_veri_9;	//0xC9012224
	PE_O22_CCO_VERI_SYS_VERI_10_T                         video_delay_sts0;	//0xC9012228
	PE_O22_CCO_VERI_SYS_VERI_11_T                         video_delay_sts1;	//0xC901222C
	PE_O22_CCO_VERI_SYS_VERI_12_T                              sys_veri_12;	//0xC9012230
	PE_O22_CCO_VERI_SYS_VERI_13_T                              sys_veri_13;	//0xC9012234
	PE_O22_CCO_VERI_SYS_VERI_14_T                              sys_veri_14;	//0xC9012238
	PE_O22_CCO_VERI_SYS_VERI_15_T                              sys_veri_15;	//0xC901223C
	PE_O22_CCO_VERI_SYS_VERI_16_T                              sys_veri_16;	//0xC9012240
	PE_O22_CCO_VERI_SYS_VERI_17_T                              sys_veri_17;	//0xC9012244
	PE_O22_CCO_VERI_SYS_VERI_18_T                              sys_veri_18;	//0xC9012248
	PE_O22_CCO_VERI_SYS_VERI_19_T                              sys_veri_19;	//0xC901224C
	PE_O22_CCO_VERI_SYS_VERI_20_T                              sys_veri_20;	//0xC9012250
	PE_O22_CCO_VERI_SYS_VERI_21_T                              sys_veri_21;	//0xC9012254
	PE_O22_CCO_VERI_SYS_VERI_22_T                              sys_veri_22;	//0xC9012258
	PE_O22_CCO_VERI_SYS_VERI_23_T                              sys_veri_23;	//0xC901225C
	PE_O22_CCO_VERI_SYS_VERI_24_T                              sys_veri_24;	//0xC9012260
	PE_O22_CCO_VERI_SYS_VERI_25_T                              sys_veri_25;	//0xC9012264
	PE_O22_CCO_VERI_SYS_VERI_26_T                              sys_veri_26;	//0xC9012268
	PE_O22_CCO_VERI_SYS_VERI_27_T                              sys_veri_27;	//0xC901226C
	PE_O22_CCO_VERI_SYS_VERI_28_T                              sys_veri_28;	//0xC9012270
	PE_O22_CCO_VERI_SYS_VERI_29_T                              sys_veri_29;	//0xC9012274
	PE_O22_CCO_VERI_SYS_VERI_30_T                              sys_veri_30;	//0xC9012278
	PE_O22_CCO_VERI_SYS_VERI_31_T                              sys_veri_31;	//0xC901227C
	PE_O22_CCO_VERI_SYS_VERI_32_T                              sys_veri_32;	//0xC9012280
	PE_O22_CCO_VERI_SYS_VERI_33_T                              sys_veri_33;	//0xC9012284
	PE_O22_CCO_VERI_SYS_VERI_34_T                              sys_veri_34;	//0xC9012288
	PE_O22_CCO_VERI_SYS_VERI_35_T                              sys_veri_35;	//0xC901228C
}PE_CCO_VERI_REG_O22_T;



#endif
