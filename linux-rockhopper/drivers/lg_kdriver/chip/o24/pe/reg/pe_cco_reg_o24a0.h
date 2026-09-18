#ifndef _PE_CCO_REG_O24A0_H_
#define _PE_CCO_REG_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC861000 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,NA,0x0) //0' : load at vdpulse	'1' : load when reg. write
	UINT32 load_enable                      :1;	//(1,NA,0x0) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,NA,0x0) //0' : auto load:  load when reg. write	'1' : manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O24_CC_PE1_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861004 RW 0x10E0_0780
	UINT32 width                            :13;	//(12:0,NA,0x780) //width
	UINT32 resvd0                           :3;
	UINT32 height                           :13;	//(28:16,NA,0x10E0) //height
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861008 RW 0x0100_0A01
	UINT32 tpg_position                     :1;	//(0,NA,0x1) //0 := pe1 input	1  =  pe1 output
	UINT32 reg_pe1_cg_disable               :1;	//(1,NA,0x0) //clock gating disable
	UINT32 pe1_detour                       :1;	//(2,NA,0x0) //0': pe1 pass-through	'1': pe1 detour
	UINT32 resvd0                           :5;
	UINT32 vdpulse_pos                      :12;	//(19:8,NA,0xA) //vdpulse position for register loading
	UINT32 resvd1                           :4;
	UINT32 master_en                        :1;	//(24,NA,0x1) //PE1 master enable
	UINT32 resvd2                           :7;
	};
}PE_O24_CC_PE1_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86100C RO 0x0000_0000
	UINT32 vcnt                             :13;	//(12:0,NA,0x0) //vertical line count
	UINT32 va_pe1_in                        :1;	//(13,NA,0x0) //Vertical Active at PE1 input
	UINT32 va_pe1_out                       :1;	//(14,NA,0x0) //Vertical Active at PE1 output
	UINT32 resvd0                           :1;
	UINT32 vcnt2                            :13;	//(28:16,NA,0x0) //vertical line number
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861010 RW 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,NA,0x800) //apb time out count threshold
	UINT32 resvd                            :20;
	};
}PE_O24_CC_PE1_TOP_CTRL_04_T;

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
}PE_O24_CC_PE1_FSW_CTRL_00_T;

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
}PE_O24_CC_PE1_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861028 RW 0x0000_0000
	UINT32 reg_src_info                     :5;	//4:0	//Video Source Information	 2 : default/transition period	 3 : AV NTSC	 4 : AV PAL	 5 : HDMI_SD_i/p	 6 : HDMI_576_i/p	 7 : HDMI_HD_i	 8 : HDMI_HD_p	 9 : DTV_480_i	10 : DTV_576_i	11 : DTV_576_p	12 : DTV_HD_i	13 : DTV_HD_p	14 : RF_NTSC	15 : RF_PAL	16 : RF_PAL_M	17 : COMPONENT_1080_i	18 : COMPONENT_1080_p	19 : COMPONENT_480_i	20 : COMPONENT_480_p	21 : COMPONENT_576_i	22 : COMPONENT_576_p	23 : AV_SECAM	24 : RF_SECAM	25 : AV_ NTSC_443	26 : RF_NTSC_443	27 : AV_PAL_60	28 : SCART_RGB	29 : N.A.(abnormal) input	30 : NO SIG.
	UINT32 reg_src_freeze                   :1;	//5 //src freeze toggle '0' : normal '1' : freeze
	UINT32 reg_gsr_cpc_enable               :1;	//6 //gsr cpc enable
	UINT32 resvd                            :25;
	};
}PE_O24_CC_PE1_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86102C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_CC_PE1_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861030 RW 0x0000_0000
	UINT32 p_osd_addr_y                          :32;
	};
}PE_O24_CC_PE1_FSW_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861034 RW 0x0000_0000
	UINT32 p_osd_width                           :16;
	UINT32 p_osd_height							 :16;
	};
}PE_O24_CC_PE1_FSW_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861038 RW 0x0000_0000
	UINT32 p_osd_pos_x                           :16;
	UINT32 p_osd_valid							 :1;
	UINT32 resvd							 	 :15;
	};
}PE_O24_CC_PE1_FSW_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86103C RW 0x0000_0000
	UINT32 p_osd_update_cnt                       :32;
	};
}PE_O24_CC_PE1_FSW_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861050 RW 0x03C0_0000
	UINT32 tpg_enable                       :1;	//(0,NA,0x0) //TPG Enable
	UINT32 pattern_type                     :2;	//(2:1,NA,0x0) //Test Pattern Type	'00 := ColorPatch	'01 = Gradation
	UINT32 resvd0                           :1;
	UINT32 blend_alpha                      :4;	//(7:4,NA,0x0) //TPG Blend Alpha	0x0 ~ 0xF = SolidPattern ~ BypassBackgroundPicture
	UINT32 resvd1                           :8;
	UINT32 blt_size_x                       :13;	//(28:16,NA,0x3C0) //Pattern Blt Size X (1920d=>0x780)
	UINT32 resvd2                           :3;
	};
}PE_O24_CC_PE1_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861054 RW 0x10E0_0FA0
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
}PE_O24_CC_PE1_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861058 RW 0x0000_FFFF
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
}PE_O24_CC_PE1_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86105C RW 0x0000_0000
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
}PE_O24_CC_PE1_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861060 RW 0x0000_0000
	UINT32 bg_color_r                       :10;	//(9:0,NA,0x0) //outside color with RGB
	UINT32 bg_color_b                       :10;	//(19:10,NA,0x0) //
	UINT32 bg_color_g                       :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861064 WO 0x0000_0000
	UINT32 tpg_indir_addr                   :7;	//(6:0,NA,0x00) //TPG Indirect Address	0x00 ~ 0x0F = Patch Color	0x20 ~ 0x2F = Patch Start Position	0x40 ~ 0x4F = Patch End Position	0x60 ~ 0x63 = Gradation Start Color	0x64 ~ 0x67 = Gradation Step Color (signed)	0x68 ~ 0x6A = Gradation Region Size
	UINT32 resvd0                           :5;
	UINT32 tpg_indir_ai_en                  :1;	//(12,NA,0x0) //TPG Indirect Addressing Ctrl, AI Enable
	UINT32 resvd1                           :19;
	};
}PE_O24_CC_PE1_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861068 WO 0x0000_0000
	UINT32 tpg_indir_data                   :32;	//(31:0,NA,0x0) //TPG Indirect Access Data (Write Enable Triggered)	 When Addr is...	 0x00 ~ 0x0F = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x20 ~ 0x4F = (28:16):X_position, (12:0):Y_position	 0x60 ~ 0x67 = (29:20):G/Y, (19:10):B/Cb, (9:0):R/Cr	 0x68 ~ 0x6A = (12:0):position
	};
}PE_O24_CC_PE1_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861070 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_0                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0 for ch0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_0                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0 for ch0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861074 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_0                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_0                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861078 RW 0x0000_0000
	UINT32 apl_position                     :2;	//(1:0,NA,0x0) //00 := PE1 input(YC)	'01 = OCSC input(YC)	'10 = OCSC output(RGB)	'11 = PE1 output(RGB)
	UINT32 resvd0                           :2;
	UINT32 reg_apl_enable                   :1;	//(4,NA,0x1) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd1                           :3;
	UINT32 act_win_mode                     :1;	//(8,NA,0x0) //0  := manual active window setting	     See pe1_apl_ctrl_00 & pe1_apl_ctrl_01	1 = full active window by h/v active
	UINT32 resvd2                           :23;
	};
}PE_O24_CC_PE1_APL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86107C RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_1                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_1                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861080 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_1                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_1                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861084 RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_2                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_2                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861088 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_2                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_2                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86108C RW 0x0000_0000
	UINT32 apl_win_ctrl_x0_3                :13;	//(12:0,NA,0x000) //apl_win_ctrl_x0
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y0_3                :13;	//(28:16,NA,0x000) //apl_win_ctrl_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861090 RW 0x0437_03BF
	UINT32 apl_win_ctrl_x1_3                :13;	//(12:0,NA,0x3BF) //1919 = 1920-1
	UINT32 resvd0                           :3;
	UINT32 apl_win_ctrl_y1_3                :13;	//(28:16,NA,0x437) //1079 = 1080-1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_APL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610B4 RO 0x0000_0000
	UINT32 apl_cb                           :10;	//(9:0,NA,0x0) //APL Cb/B
	UINT32 apl_yg                           :10;	//(19:10,NA,0x0) //APL Y/G
	UINT32 apl_cr                           :10;	//(29:20,NA,0x0) //APL Cr/R
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610B8 RO 0x0000_0000
	UINT32 apl_cb_other_side                :10;	//(9:0,NA,0x0) //apl_cb(outside of apl_win)
	UINT32 apl_yg_other_side                :10;	//(19:10,NA,0x0) //apl_yg(outside of apl_win)
	UINT32 apl_cr_other_side                :10;	//(29:20,NA,0x0) //apl_cr(outside of apl_win)
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_APL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610C0 RW 0x0000_0000
	UINT32 r_2x3_coef1                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef0                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610C4 RW 0x0000_0000
	UINT32 r_2x3_coef3a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef2                      :15;	//(30:16,NA,0x0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610C8 RW 0x0000_0000
	UINT32 r_2x3_coef5a                     :15;	//(14:0,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4a                     :15;	//(30:16,NA,0x0) //when ( cb <= reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610CC RW 0x0000_0000
	UINT32 r_2x3_coef7a                     :15;	//(14:0,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610D0 RW 0x0000_0000
	UINT32 r_2x3_ofst0                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_coef8a                     :15;	//(30:16,NA,0x0) //when ( cr <= reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610D4 RW 0x0000_0000
	UINT32 r_2x3_ofst2                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst1                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610D8 RW 0x0000_0000
	UINT32 r_2x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_2x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610DC RW 0x0000_0100
	UINT32 r_2x3_en                         :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_degamma_en                     :1;	//(4,NA,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_1x3_en                         :1;	//(8,NA,0x1) //
	UINT32 resvd2                           :7;
	UINT32 r_2x3_ofst5                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd3                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610E0 RW 0x0000_0000
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
}PE_O24_CC_PE1_BT20_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610E4 RW 0x0000_0000
	UINT32 r_2x3_coef3b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 reg_csc_cb_th                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_BT20_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610E8 RW 0x0000_0000
	UINT32 r_2x3_coef5b                     :15;	//(14:0,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef4b                     :15;	//(30:16,NA,0x0) //when ( cb > reg_csc_cb_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610EC RW 0x0000_0000
	UINT32 r_2x3_coef7b                     :15;	//(14:0,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd0                           :1;
	UINT32 r_2x3_coef6b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610F0 RW 0x0000_0000
	UINT32 reg_csc_cr_th                    :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 r_2x3_coef8b                     :15;	//(30:16,NA,0x0) //when ( cr > reg_csc_cr_th )
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610F4 RW 0x12A0_7C98
	UINT32 r_1x3_coef1                      :15;	//(14:0,NA,0x7C98) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef0                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610F8 RW 0x7775_12A0
	UINT32 r_1x3_coef3                      :15;	//(14:0,NA,0x12A0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef2                      :15;	//(30:16,NA,0x7775) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8610FC RW 0x21D7_0000
	UINT32 r_1x3_coef5                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef4                      :15;	//(30:16,NA,0x21D7) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861100 RW 0x12A0_0000
	UINT32 r_1x3_coef7                      :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_1x3_coef6                      :15;	//(30:16,NA,0x12A0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861104 RW 0x1CB0_0000
	UINT32 resvd0                           :16;
	UINT32 r_1x3_coef8                      :15;	//(30:16,NA,0x1CB0) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_BT20_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861108 RW 0x07C0_0600
	UINT32 r_1x3_ofst1                      :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst0                      :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86110C RW 0x0600_0000
	UINT32 r_1x3_ofst3                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst2                      :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861110 RW 0x0000_0000
	UINT32 r_1x3_ofst5                      :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_1x3_ofst4                      :11;	//(26:16,NA,0x0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC_PE1_BT20_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861114 RW 0x0000_0000
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
}PE_O24_CC_PE1_BT20_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861118 RO 0x0000_0000
	UINT32 r_1x3_over_count_0               :16;	//(15:0,NA,0x0) //overflow count status for ch 0
	UINT32 r_1x3_under_count_0              :16;	//(31:16,NA,0x0) //underflow count status for ch 0
	};
}PE_O24_CC_PE1_BT20_CTRL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86111C RO 0x0000_0000
	UINT32 r_1x3_over_count_1               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_1              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O24_CC_PE1_BT20_CTRL_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861120 RO 0x0000_0000
	UINT32 r_1x3_over_count_2               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_2              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O24_CC_PE1_BT20_CTRL_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861124 RO 0x0000_0000
	UINT32 r_1x3_over_count_3               :16;	//(15:0,NA,0x0) //overflow count status
	UINT32 r_1x3_under_count_3              :16;	//(31:16,NA,0x0) //underflow count status
	};
}PE_O24_CC_PE1_BT20_CTRL_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861140 RW 0x0000_0000
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
}PE_O24_CC_PE1_WIN2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861144 RW 0x0000_0000
	UINT32 win_w0_x0_0                      :13;	//(12:0,NA,0x000) //win_w0_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_0                      :13;	//(28:16,NA,0x000) //win_w0_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861148 RW 0x0437_03BF
	UINT32 win_w0_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w0_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_0                      :13;	//(28:16,NA,0x437) //win_w0_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86114C RW 0x0000_0000
	UINT32 win_w1_x0_0                      :13;	//(12:0,NA,0x000) //win_w1_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_0                      :13;	//(28:16,NA,0x000) //win_w1_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861150 RW 0x0437_03BF
	UINT32 win_w1_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w1_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_0                      :13;	//(28:16,NA,0x437) //win_w1_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861154 RW 0x0000_0000
	UINT32 win_w0_x0_1                      :13;	//(12:0,NA,0x000) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_1                      :13;	//(28:16,NA,0x000) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861158 RW 0x0437_03BF
	UINT32 win_w0_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w0_x1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_1                      :13;	//(28:16,NA,0x437) //win_w0_y1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86115C RW 0x0000_0000
	UINT32 win_w1_x0_1                      :13;	//(12:0,NA,0x000) //win_w1_x0
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_1                      :13;	//(28:16,NA,0x000) //win_w1_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861160 RW 0x0437_03BF
	UINT32 win_w1_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w1_x1
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_1                      :13;	//(28:16,NA,0x437) //win_w1_y1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611D0 RW 0x0000_002C
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
}PE_O24_CC_PE1_CEN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611D4 RW 0xFFFF_0000
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
}PE_O24_CC_PE1_CEN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611D8 RW 0x0000_8080
	UINT32 ihsv_sgain                       :8;	//(7:0,NA,0x80) //reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//(15:8,NA,0x80) //reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
}PE_O24_CC_PE1_CEN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611DC RW 0x0080_8080
	UINT32 ihsv_hoffset                     :8;	//(7:0,NA,0x80) //reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//(15:8,NA,0x80) //reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//(23:16,NA,0x80) //reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
}PE_O24_CC_PE1_CEN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611E0 RW 0x8080_8080
	UINT32 reg_master_gain_cr0              :8;	//(7:0,NA,0x80) //Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//(15:8,NA,0x80) //Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//(23:16,NA,0x80) //Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//(31:24,NA,0x80) //Color region 3 master gain
	};
}PE_O24_CC_PE1_CEN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611E4 RW 0x8080_8080
	UINT32 reg_master_gain_cr4              :8;	//(7:0,NA,0x80) //Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//(15:8,NA,0x80) //Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//(23:16,NA,0x80) //Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//(31:24,NA,0x80) //Color region 7 master gain
	};
}PE_O24_CC_PE1_CEN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611E8 RW 0x8080_8080
	UINT32 reg_master_gain_cr8              :8;	//(7:0,NA,0x80) //Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//(15:8,NA,0x80) //Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//(23:16,NA,0x80) //Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//(31:24,NA,0x80) //Color region 11 master gain
	};
}PE_O24_CC_PE1_CEN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611EC RW 0x8080_8080
	UINT32 reg_master_gain_cr12             :8;	//(7:0,NA,0x80) //Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//(15:8,NA,0x80) //Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//(23:16,NA,0x80) //Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//(31:24,NA,0x80) //Color region 15 master gain
	};
}PE_O24_CC_PE1_CEN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8611F8 RW/RO 0x0000_0000
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
}PE_O24_CC_PE1_CEN_UPD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861200 WO 0x0000_0000
	UINT32 hif_cen_address                  :8;	//(7:0,NA,0x00) //hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//(10:8,NA,0x0) //reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//(14,NA,0x0) //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//(15,NA,0x0) //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
}PE_O24_CC_PE1_CEN_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861204 RO 0x0000_0000
	UINT32 hif_cen_y_wdata                  :10;	//(9:0,NA,0x000) //
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//(25:16,NA,0x000) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_CEN_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861208 WO 0x0000_0000
	UINT32 hif_cen_delta_address            :5;	//(4:0,NA,0x00) //hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//(12,NA,0x0) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//(15,NA,0x0) //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
}PE_O24_CC_PE1_CEN_DELTA_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86120C RO 0x0000_0000
	UINT32 hif_cen_vr_data                  :8;	//(7:0,NA,0x000) //Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//(15:8,NA,0x000) //Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//(23:16,NA,0x000) //Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
}PE_O24_CC_PE1_CEN_DELTA_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861220 RW 0x0000_0000
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
}PE_O24_CC_PE1_DCE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861224 RW 0x0080_001A
	UINT32 chroma_comp_color_region_gain    :8;	//(7:0,NA,0x1A) //default : "128" ( 1 ~ 255(1~400%))
	UINT32 resvd0                           :8;
	UINT32 color_region_gain                :8;	//(23:16,NA,0x80) //default : "128" ( 1 ~ 255(1~400%)) (forbidden 0 value))
	UINT32 resvd1                           :8;
	};
}PE_O24_CC_PE1_DCE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861228 RW 0x0000_0000
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
}PE_O24_CC_PE1_DCE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86122C RW 0x02D0_01E0
	UINT32 y_range_min                      :10;	//(9:0,NA,0x01E0) //default : 480
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x02D0) //default : 720
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861230 RW 0x02B4_0264
	UINT32 cb_range_min                     :10;	//(9:0,NA,0x0264) //default : 612
	UINT32 resvd0                           :6;
	UINT32 cb_range_max                     :10;	//(25:16,NA,0x02B4) //default : 692
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861234 RW 0x01FC_0134
	UINT32 cr_range_min                     :10;	//(9:0,NA,0x0134) //default : 308
	UINT32 resvd0                           :6;
	UINT32 cr_range_max                     :10;	//(25:16,NA,0x01FC) //default : 508
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861238 RW 0x0000_8000
	UINT32 hif_dyc_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dce_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dce_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dce_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 hif_dce_win_sel                  :2;	//(17,16) //
	UINT32 resvd3                           :14;
	};
}PE_O24_CC_PE1_DCE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86123C RO 0x0000_0000
	UINT32 hif_dyc_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861240 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861248 RW 0x0000_8000
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
}PE_O24_CC_PE1_DCE_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86124C RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O24_CC_PE1_DCE_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861250 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_O24_CC_PE1_DCE_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861254 RW 0x0200_0200
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_O24_CC_PE1_DCE_CHR_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861258 RW 0x0200_0200
	UINT32 dce_chr_alpha2                   :10;	//(9:0,NA,0x200) //alpha(0~512), y_dce_in < y_dce_out : 0 means no gain
	UINT32 resvd0                           :6;
	UINT32 dce_chr_alpha1                   :10;	//(25:16,NA,0x200) //alpha(0~512), y_dce_in >= y_dce_out : 0 means no gain
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CHR_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86125C RW 0x0200_0200
	UINT32 dce_cr_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CHR_GAIN2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861270 RW 0x0000_0000
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
}PE_O24_CC_PE1_DSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861274 RW 0x8000_0301
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
}PE_O24_CC_PE1_DSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861278 RW 0x03FF_03FF
	UINT32 hif_dse_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86127C RW 0x0000_8000
	UINT32 hif_dse_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
}PE_O24_CC_PE1_DSE_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861280 RO 0x0000_0000
	UINT32 hif_dse_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DSE_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861284 RW 0x028A_0238
	UINT32 y_range_min                      :10;	//(9:0,NA,0x0238) //default : 568
	UINT32 resvd0                           :6;
	UINT32 y_range_max                      :10;	//(25:16,NA,0x028A) //default : 650
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861288 RW 0x0061_0026
	UINT32 h_range_min                      :10;	//(9:0,NA,0x0026) //default : 38
	UINT32 resvd0                           :6;
	UINT32 h_range_max                      :10;	//(25:16,NA,0x0061) //default : 97
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86128C RW 0x0000_3C00
	UINT32 reg_y_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt0_x               :10;	//(17:8,NA,0x3C) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861290 RW 0x0000_C88C
	UINT32 reg_y_region_pt1_y               :8;	//(7:0,NA,0x8C) //
	UINT32 reg_y_region_pt1_x               :10;	//(17:8,NA,0xC8) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861294 RW 0x0001_40FF
	UINT32 reg_y_region_pt2_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt2_x               :10;	//(17:8,NA,0x140) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861298 RW 0x0001_90FF
	UINT32 reg_y_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt3_x               :10;	//(17:8,NA,0x190) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86129C RW 0x0002_BCFF
	UINT32 reg_y_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt4_x               :10;	//(17:8,NA,0x2BC) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612A0 RW 0x0003_4878
	UINT32 reg_y_region_pt5_y               :8;	//(7:0,NA,0x78) //
	UINT32 reg_y_region_pt5_x               :10;	//(17:8,NA,0x348) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612A4 RW 0x0003_703C
	UINT32 reg_y_region_pt6_y               :8;	//(7:0,NA,0x3C) //
	UINT32 reg_y_region_pt6_x               :10;	//(17:8,NA,0x370) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612A8 RW 0x0003_9800
	UINT32 reg_y_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt7_x               :10;	//(17:8,NA,0x398) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_Y_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612AC RW 0x0001_F100
	UINT32 reg_h_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt0_x               :10;	//(17:8,NA,0x1F1) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612B0 RW 0x0002_00BE
	UINT32 reg_h_region_pt1_y               :8;	//(7:0,NA,0xBE) //
	UINT32 reg_h_region_pt1_x               :10;	//(17:8,NA,0x200) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612B4 RW 0x0002_0DF0
	UINT32 reg_h_region_pt2_y               :8;	//(7:0,NA,0xF0) //
	UINT32 reg_h_region_pt2_x               :10;	//(17:8,NA,0x20D) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612B8 RW 0x0002_14FF
	UINT32 reg_h_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt3_x               :10;	//(17:8,NA,0x214) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612BC RW 0x0002_28FF
	UINT32 reg_h_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt4_x               :10;	//(17:8,NA,0x228) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612C0 RW 0x0002_30FF
	UINT32 reg_h_region_pt5_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt5_x               :10;	//(17:8,NA,0x230) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612C4 RW 0x0002_3FA0
	UINT32 reg_h_region_pt6_y               :8;	//(7:0,NA,0xA0) //
	UINT32 reg_h_region_pt6_x               :10;	//(17:8,NA,0x23F) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612C8 RW 0x0002_4000
	UINT32 reg_h_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt7_x               :10;	//(17:8,NA,0x240) //
	UINT32 resvd                            :14;
	};
}PE_O24_CC_PE_DSE_H_REGION_PT7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612E0 RW 0x0010_0100
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
}PE_O24_CC_PE1_DRC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612E4 RW 0x0000_0001
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x1) //selecet a,b gamma lut for register r/w	'0' : a gamma lut 	'1' : b gamma lut
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //selecet a,b gamma lut for operation	'0' : b gamma lut 	'1' : a gamma lut
	UINT32 resvd1                           :11;
	UINT32 reg_drc_gm_forced_sel            :1;	//(16,NA,0x0) //anytime rw_sel, op_sel transition
	UINT32 reg_drc_gm_protected_sel         :1;	//(17,NA,0x0) //Do not allow rw_sel, op_sel transition only in de active
	UINT32 resvd2                           :14;
	};
}PE_O24_CC_PE1_DRC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612E8 RW 0x0036_0060
	UINT32 reg_drc_bnh                      :7;	//(6:0,NA,0x60) //horizontal block size (min : 4, max : 96)
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bnv                      :6;	//(21:16,NA,0x36) //vertical block size (min : 3, max : 54)
	UINT32 resvd1                           :10;
	};
}PE_O24_CC_PE1_DRC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612EC RW 0x0050_0050
	UINT32 reg_drc_bsh                      :9;	//(8:0,NA,0x50) //
	UINT32 resvd0                           :7;
	UINT32 reg_drc_bsv                      :9;	//(24:16,NA,0x50) //
	UINT32 resvd1                           :7;
	};
}PE_O24_CC_PE1_DRC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612F0 RW 0x0321_912C
	UINT32 reg_drc_gm_apl2                  :10;	//(9:0,NA,0x12C) //apl for gamma lut 2
	UINT32 reg_drc_gm_apl1                  :10;	//(19:10,NA,0x64) //apl for gamma lut 1
	UINT32 reg_drc_gm_apl0                  :10;	//(29:20,NA,0x32) //apl for gamma lut 0
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612F4 RW 0x1F4A_F3B6
	UINT32 reg_drc_gm_apl5                  :10;	//(9:0,NA,0x3B6) //apl for gamma lut 5
	UINT32 reg_drc_gm_apl4                  :10;	//(19:10,NA,0x2BC) //apl for gamma lut 4
	UINT32 reg_drc_gm_apl3                  :10;	//(29:20,NA,0x1F4) //apl for gamma lut 3
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612F8 RW 0x0000_0030
	UINT32 reg_drc_blf_wei_cen              :8;	//(7:0,NA,0x30) //center pixel weight for blf
	UINT32 resvd                            :24;
	};
}PE_O24_CC_PE1_DRC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8612FC RW 0x00000000
	UINT32 reg_drc_apl_lut_x1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x0               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DRC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861300 RW 0x00000000
	UINT32 reg_drc_apl_lut_x3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x2               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DRC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861304 RW 0x00000000
	UINT32 reg_drc_apl_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_apl_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_apl_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_apl_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861308 RW 0x00000000
	UINT32 reg_drc_txt_lut_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_x0               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86130C RW 0x00000000
	UINT32 reg_drc_txt_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_y0               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861310 RW 0x00000000
	UINT32 reg_drc_dark_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861314 RW 0x00000000
	UINT32 reg_drc_dark_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861318 RW 0x00000000
	UINT32 reg_drc_bright_lut_x3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_x2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_x1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_x0            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86131C RW 0x00000000
	UINT32 reg_drc_bright_lut_y3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_y2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_y1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_y0            :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC_PE1_DRC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861320 RW 0x00000000
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
}PE_O24_CC_PE1_DRC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861330 RW 0x0000_0000
	UINT32 reg_drc_lut_addr_clr             :1;	//(0,NA,0x0) //lut address clear
	UINT32 resvd0                           :3;
	UINT32 reg_drc_hfc_rd_sel               :1;	//(4,NA,0x0) //blf h filter coefficient read select
	UINT32 resvd1                           :3;
	UINT32 reg_drc_vfc_rd_sel               :1;	//(8,NA,0x0) //blf v filter coefficient read select
	UINT32 resvd2                           :23;
	};
}PE_O24_CC_PE1_DRC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861334 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_hfc_data          :10;	//(9:0,NA,0x0) //blf h filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861338 WO 0x0000_0000
	UINT32 reg_drc_lk_blf_vfc_data          :10;	//(9:0,NA,0x0) //blf v filter coefficient write data
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86133C RW 0x0000_0000
	UINT32 reg_drc_hfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_hfc_rdata: blf h filter coefficient read data	WR  [0]reg_drc_hfc_re : blf h filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861340 RW 0x0000_0000
	UINT32 reg_drc_vfc_rdata                :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_vfc_rdata : blf v filter coefficient read data	WR  [0]reg_drc_vfc_re : blf v filter coefficient read enable
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861344 WO 0x0000_0000
	UINT32 reg_drc_blf_wei_wdata            :10;	//(9:0,NA,0x0) //blf photometric weight write data
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861348 RW 0x0000_0000
	UINT32 reg_drc_blf_wei_rdata            :10;	//(9:0,RW,0x0) //RD[9:0]reg_drc_blf_wei_rdata : blf photometric weight read data	WR  [0]reg_drc_blf_wei_re : blf photometric weight read enable
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86134C WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 0	[19:10] -> gamma lut 1	[ 9: 0] -> gamma lut 2
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861350 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 0,[19:10] -> gamma lut 1,[ 9: 0] -> gamma lut 2	WR [1:0]reg_drc_gm_re : gamma lut 0, 1, 2 read enable ("01")
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861354 WO 0x0000_0000
	UINT32 reg_drc_gm_wdata                 :30;	//(29:0,NA,0x0) //gamma lut write data	[29:20] -> gamma lut 3	[19:10] -> gamma lut 4	[ 9: 0] -> gamma lut 5
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861358 RW 0x0000_0000
	UINT32 reg_drc_gm_rdata                 :30;	//(29:0,RW,0x0) //RD[29:0]reg_drc_gm_rdata : gamma lut read data,[29:20] -> gamma lut 3,[19:10] -> gamma lut 4,[ 9: 0] -> gamma lut 5	WR [1:0]reg_drc_gm_re : gamma lut 3, 4, 5 read enable ("10")
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_DRC_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861364 RW 0x0000_0000
	UINT32 reg_drc_bl_apl_raddr_h           :7;	//(6:0,NA,0x0) //block apl read H address
	UINT32 resvd0                           :9;
	UINT32 reg_drc_bl_apl_raddr_v           :6;	//(21:16,NA,0x0) //block apl read V address
	UINT32 resvd1                           :10;
	};
}PE_O24_CC_PE1_DRC_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861368 RO 0x0000_0000
	UINT32 reg_drc_bl_apl_rdata             :10;	//(9:0,NA,0x0) //block apl read data
	UINT32 resvd                            :22;
	};
}PE_O24_CC_PE1_DRC_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86136C RO 0x0000_0000
	UINT32 reg_drc_gm_rw_sel                :1;	//(0,NA,0x0) //Read rw_sel
	UINT32 resvd0                           :3;
	UINT32 reg_drc_gm_op_sel                :1;	//(4,NA,0x0) //Read op_sel
	UINT32 resvd1                           :27;
	};
}PE_O24_CC_PE1_DRC_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861380 RW 0x0000_0C00
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
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861384 RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861388 RW 0x0011_001E
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x11) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86138C RW 0x0011_001E
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x11) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861390 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861394 RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861398 RW 0x0011_0078
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x78) //120=4x30
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x11) //17
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86139C RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613A0 RW 0x0000_0000
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
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613A4 RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613A8 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613AC RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613B0 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : (1920=7680/4p)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613B4 RW 0x0010_B8B8
	UINT32 reg_logo_blend_alpha_l7_delay    :8;	//(7:0,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 55 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blend_alpha_l3_delay    :8;	//(15:8,NA,0xB8) //16 : DCE_Y (9 -> 16 : chroma_gain added)  	 25 : VSP_YC                            	  2 : DEBUG_DISP                           	 16 : OCSC(BT20)                           	 54 : CEN(DCE, DSE)                        	 55 : DRC(Local Contrast) *                	 24 : CW                                   		-4 : logo gain scaler(1 for array)
	UINT32 reg_logo_blned_alpha_c5_delay    :5;	//(20:16,NA,0x10) //csr_gain delay : default 16, 0(-16T)~16(0T for logo_blend_top)~31(15T)
	UINT32 resvd                            :11;
	};
}PE_O24_CC_PE1_LOGO_L7SC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613B8 RW 0x0000_0011
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
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613BC RW 0x0000_0000
	UINT32 reg_in_hoffset                   :13;	//(12:0,NA,0x0) //input window offset
	UINT32 resvd0                           :3;
	UINT32 reg_in_voffset                   :13;	//(28:16,NA,0x0) //input window offset
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613C0 RW 0x010E_01E0
	UINT32 reg_in_hactive                   :13;	//(12:0,NA,0x1E0) //input window active size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vactive                   :13;	//(28:16,NA,0x10E) //input window active size
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613C4 RW 0x010E_01E0
	UINT32 reg_in_hsize                     :13;	//(12:0,NA,0x1E0) //input source total size
	UINT32 resvd0                           :3;
	UINT32 reg_in_vsize                     :13;	//(28:16,NA,0x10E) //input source total size
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613C8 RW 0x10E0_0780
	UINT32 reg_out_pic_width                :13;	//(12:0,NA,0x780) //width/4p, (1920=7680/4p)
	UINT32 resvd0                           :3;
	UINT32 reg_out_pic_height               :13;	//(28:16,NA,0x10E0) //height(4320)
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613CC RW 0x4000_1010
	UINT32 reg_phase_off_h                  :6;	//(5:0,NA,0x10) //horizontal offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd0                           :2;
	UINT32 reg_phase_off_v                  :6;	//(13:8,NA,0x10) //vertical offset of initial pixel position	(signed value)  	min  : -31	max  : +31
	UINT32 resvd1                           :13;
	UINT32 reg_vsc_1to2_last_sel            :1;	//(27:27,NA,0x0) //0' : input last	'1' : width
	UINT32 reg_vpadding_off                 :1;	//(28:28,NA,0x0) //0' : vpadding on	'1' : vpadding off
	UINT32 reg_mode_32p                     :1;	//(29:29,NA,0x0) //'0' : 256p	     '1' : 32p
	UINT32 reg_sampling_mode                :2;	//(31:30,NA,0x1) //'0' : normal-auto	     '1' : manual-set
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613D0 RW 0x010E_0780
	UINT32 reg_numerator_h                  :13;	//(12:0,NA,0x780) //1920=480x4
	UINT32 resvd0                           :3;
	UINT32 reg_numerator_v                  :13;	//(28:16,NA,0x10E) //270
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613D4 RW 0x10E0_1E00
	UINT32 reg_denominator_h                :13;	//(12:0,NA,0x1E00) //(default: 7680(1920(=7680/4p)x4)
	UINT32 resvd0                           :3;
	UINT32 reg_denominator_v                :13;	//(28:16,NA,0x10E0) //(default: 4320)
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613D8 RW 0x0000_0000
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
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613DC RW 0x0000_0000
	UINT32 win_w0_x0                        :13;	//(12:0,NA,0x0) //win_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0                        :13;	//(28:16,NA,0x0) //win_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613E0 RW 0x0000_0000
	UINT32 win_w0_x1                        :13;	//(12:0,NA,0x0) //win_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1                        :13;	//(28:16,NA,0x0) //win_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613E4 RW 0x0000_0000
	UINT32 reg_out_hoffset                  :13;	//(12:0,NA,0x0) //output window offset
	UINT32 reg_out_pixel_hoffset            :3;	//(15:13,NA,0x0) //4p hoffset
	UINT32 reg_out_voffset                  :13;	//(28:16,NA,0x0) //output window offset
	UINT32 resvd                            :3;
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613E8 RW 0x10E0_0780
	UINT32 reg_out_hactive                  :13;	//(12:0,NA,0x780) //output window active size : 1920(7680/4)
	UINT32 reg_out_havg_4x_mode             :3;	//(15:13,NA,0x0) //0 : avg 0 phase	1 : avg 1 phase	2 : avg 2 phase	3 : avg 3 phase	4 : repeat
	UINT32 reg_out_vactive                  :13;	//(28:16,NA,0x10E0) //output window active size
	UINT32 reg_out_havg_bnd_mode            :1;	//(29:29,NA,0) //0 : 0	1 : last pixel repeat
	UINT32 logo_l3sc_out_sel                :2;	//(31:30,NA,0x0) //0 : logo_l3sc_out	1 : 	2 : '0'	3 : '1'
	};
}PE_O24_CC_PE1_LOGO_L3SC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613EC RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O24_CC_PE1_LOGO_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613F0 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O24_CC_PE1_LOGO_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613F4 RO 0x0000_0000
	UINT32 ibuf_logo_gain_vcnt              :9;	//(8:0,NA,0x0) //
	UINT32 resvd                            :23;
	};
}PE_O24_CC_PE1_LOGO_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8613F8 RO 0x0000_0000
	UINT32 current_out_line                 :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 current_in_line                  :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_O24_CC_PE1_LOGO_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861410 RW 0x0000_0000
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
}PE_O24_CC_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}PE_O24_CC_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_CC_PE1_PCC_COEF7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861434 RW 0x0000_0000
	UINT32 oetf_addr                        :11;	//(10:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 oetf_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O24_CC_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861438 RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :12;	//(11:0,NA,0x0) //12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//(27:16,NA,0x0) //12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}PE_O24_CC_PE1_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86143C RW 0x0000_0000
	UINT32 eotf_wdata                       :15;	//(14:0,RW,0x0) //lut write data
	UINT32 resvd0                           :1;
	UINT32 eotf_waddr                       :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd1                           :2;
	UINT32 eotf_we                          :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}PE_O24_CC_PE1_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861440 RW/RO 0x0000_0000
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
}PE_O24_CC_PE1_EOTF_WDONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861444 RW/RO 0x0000_0000
	UINT32 eotf_rdata                       :15;	//(14:0,RO,0x0) //lut read data
	UINT32 resvd0                           :1;
	UINT32 eotf_raddr                       :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 eotf_re                          :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 eotf_rdata_sel                   :1;	//(31,RW,0x0) //lut read data sel 0:even, 1:odd
	};
}PE_O24_CC_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861448 RO 0x0000_0000
	UINT32 eotf_buf_rw_conflict             :1;	//(0,RO,0x00) //
	UINT32 eotf_lut_cpy_done                :1;	//(1,RO,0x00) //
	UINT32 eotf_lut_cpy_status              :2;	//(3:2,RO,0x0) //
	UINT32 resvd                            :28;
	};
}PE_O24_CC_PE1_EOTF_RSATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861450 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O24_CC_PE1_LLLUT_E_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861454 RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_LLLUT_E_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861458 RW 0x0000_0000
	UINT32 ll_lut_addr                      :6;	//(5:0,NA,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O24_CC_PE1_LLLUT_O_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86145C RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O24_CC_PE1_LLLUT_O_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861460 RW 0x0000_0100
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
}PE_O24_CC_PE1_LLCORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861464 RW 0x0000_1000
	UINT32 reg_llpcc_coef0                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef1                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 1
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861468 RW 0x0000_0000
	UINT32 reg_llpcc_coef2                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef3                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 3
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86146C RW 0x0000_0000
	UINT32 reg_llpcc_coef4                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef5                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 5
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861470 RW 0x0000_0000
	UINT32 reg_llpcc_coef6                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef7                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 7
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861474 RW 0x0AD9_1000
	UINT32 reg_llpcc_coef8                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 8
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(30:16,NA,0x0AD9) //alpha blendling RGB -> Y coef0
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861478 RW 0x0434_00F3
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(14:0,NA,0x00F3) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(30:16,NA,0x0434) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86147C RW 0x0000_0000
	UINT32 reg_llab_lut_y0                  :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x0                  :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861480 RW 0x0009_0009
	UINT32 reg_llab_lut_y1                  :10;	//(9:0,NA,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x1                  :10;	//(25:16,NA,0x9) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861484 RW 0x000A_0200
	UINT32 reg_llab_lut_y2                  :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x2                  :10;	//(25:16,NA,0xA) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861488 RW 0x000B_03FF
	UINT32 reg_llab_lut_y3                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x3                  :10;	//(25:16,NA,0xB) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86148C RW 0x03FF_03FF
	UINT32 reg_llab_lut_y4                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x4                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861490 RW 0x03FF_03FF
	UINT32 reg_llab_lut_y5                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x5                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861494 RW 0x0000_00FF
	UINT32 reg_hue_prsv_ratio               :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
}PE_O24_CC_PE1_LLCORE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614A0 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #1
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #1
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614A4 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #2
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #2
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614A8 RW 0x03FF_03FF
	UINT32 hif_dyc_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point window #3
	UINT32 resvd0                           :6;
	UINT32 hif_dyc_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point window #3
	UINT32 resvd1                           :6;
	};
}PE_O24_CC_PE1_DCE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614AC RW 0x0000EE44
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
}PE_O24_CC_PE1_HIST_WIN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614B0 RW 0x0000_8000
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
}PE_O24_CC_PE1_DCE_HIST1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614B4 RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O24_CC_PE1_DCE_HIST1_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614B8 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_CC_PE1_DCE_HIST1_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614BC RW 0x0000_8000
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
}PE_O24_CC_PE1_DCE_HIST2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614C0 RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O24_CC_PE1_DCE_HIST2_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614C4 RO 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_O24_CC_PE1_DCE_HIST2_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614C8 RW 0x0000_8000
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
}PE_O24_CC_PE1_DCE_HIST3_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614CC RO 0x0000_0000
	UINT32 hist_status0                     :25;	//(24:0,NA,0x0) //(24:0)hif_histogram_bin_read
	UINT32 resvd                            :7;
	};
}PE_O24_CC_PE1_DCE_HIST3_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614D0 RO 0x0000_0000
	UINT32 hist_status1                     :29;	//(28:0,NA,0x0) //when hif_status_address "1"	  : (25:16)hist_v_max	      Maximum V value for one frame	  : (9:0)hist_v_min	      Minimum V value for one frame	when hif_status_address "4"	  : (24:0)hist_detected_region_num	      Detected region number
	UINT32 resvd                            :3;
	};
}PE_O24_CC_PE1_DCE_HIST3_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614E0 RW 0x0000_0000
	UINT32 win_w2_x0_0                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w2_y0_0                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614E4 RW 0x0437_03BF
	UINT32 win_w2_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w2_y1_0                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614E8 RW 0x0000_0000
	UINT32 win_w3_x0_0                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w3_y0_0                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614EC RW 0x0437_03BF
	UINT32 win_w3_x1_0                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 0
	UINT32 resvd0                           :3;
	UINT32 win_w3_y1_0                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614F0 RW 0x0000_0000
	UINT32 win_w2_x0_1                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 1
	UINT32 resvd0                           :3;
	UINT32 win_w2_y0_1                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614F4 RW 0x0437_03BF
	UINT32 win_w2_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 1
	UINT32 resvd0                           :3;
	UINT32 win_w2_y1_1                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614F8 RW 0x0000_0000
	UINT32 win_w3_x0_1                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 1
	UINT32 resvd0                           :3;
	UINT32 win_w3_y0_1                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8614FC RW 0x0437_03BF
	UINT32 win_w3_x1_1                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 1
	UINT32 resvd0                           :3;
	UINT32 win_w3_y1_1                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861500 RW 0x0000_0000
	UINT32 win_w0_x0_2                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_2                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861504 RW 0x0437_03BF
	UINT32 win_w0_x1_2                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_2                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861508 RW 0x0000_0000
	UINT32 win_w1_x0_2                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_2                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86150C RW 0x0437_03BF
	UINT32 win_w1_x1_2                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_2                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861510 RW 0x0000_0000
	UINT32 win_w0_x0_3                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w0_y0_3                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861514 RW 0x0437_03BF
	UINT32 win_w0_x1_3                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w0_y1_3                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861518 RW 0x0000_0000
	UINT32 win_w1_x0_3                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w1_y0_3                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86151C RW 0x0437_03BF
	UINT32 win_w1_x1_3                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w1_y1_3                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861520 RW 0x0000_0000
	UINT32 win_w2_x0_2                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w2_y0_2                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861524 RW 0x0437_03BF
	UINT32 win_w2_x1_2                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w2_y1_2                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861528 RW 0x0000_0000
	UINT32 win_w3_x0_2                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w3_y0_2                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86152C RW 0x0437_03BF
	UINT32 win_w3_x1_2                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 2
	UINT32 resvd0                           :3;
	UINT32 win_w3_y1_2                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 2
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861530 RW 0x0000_0000
	UINT32 win_w2_x0_3                      :13;	//(12:0,NA,0x000) //win_w2_x0 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w2_y0_3                      :13;	//(28:16,NA,0x000) //win_w2_y0 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861534 RW 0x0437_03BF
	UINT32 win_w2_x1_3                      :13;	//(12:0,NA,0x3BF) //win_w2_x1 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w2_y1_3                      :13;	//(28:16,NA,0x437) //win_w2_y1 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861538 RW 0x0000_0000
	UINT32 win_w3_x0_3                      :13;	//(12:0,NA,0x000) //win_w3_x0 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w3_y0_3                      :13;	//(28:16,NA,0x000) //win_w3_y0 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86153C RW 0x0437_03BF
	UINT32 win_w3_x1_3                      :13;	//(12:0,NA,0x3BF) //win_w3_x1 for ch 3
	UINT32 resvd0                           :3;
	UINT32 win_w3_y1_3                      :13;	//(28:16,NA,0x437) //win_w3_y1 for ch 3
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PE1_WIN2_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861550 RW 0x0000_0000
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
}PE_O24_CC_PCC_WINCTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861554 RW 0x0000_0000
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
}PE_O24_CC_PCC_WINCTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861558 RW 0x0000_0000
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
}PE_O24_CC_PCC_WINCTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86155C RW 0x0000_0000
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
}PE_O24_CC_PCC_WINCTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861560 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861564 RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861568 RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86156C RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861570 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861574 RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861578 RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86157C RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861580 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861584 RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861588 RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86158C RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861590 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861594 RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861598 RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86159C RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}PE_O24_CC_PCC_WINCTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8615A0 RW 0x0000_0000
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest):win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}PE_O24_CC_PCC_WINCTRL_20_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC861600 RW 0x0200_0040
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
}PE_O24_CC2_PE1_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861604 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861608 RW 0x12AF_7C94
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,NA,0x7C94) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86160C RW 0x7773_12AF
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,NA,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,NA,0x7773) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861610 RW 0x21E6_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,NA,0x21E6) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861614 RW 0x12AF_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861618 RW 0x1CC5_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,NA,0x1CC5) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86161C RW 0x07C0_0600
	UINT32 r_yc2rgb_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861620 RW 0x0600_0000
	UINT32 r_yc2rgb_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861624 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst4                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSPYC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861630 RW 0x0000_0300
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
}PE_O24_CC2_PE1_VSP_CC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861644 RW 0x0000_2001
	UINT32 reg_vspyc_tap_mode               :1;	//(0,NA,0x1) //0:2tap mode(2p to 4p), 1:4tap mode(1p to 4p)
	UINT32 resvd0                           :3;
	UINT32 reg_vspyc_repeat_en              :1;	//(4,NA,0x0) //1:repeat(interpolation off)
	UINT32 resvd1                           :3;
	UINT32 reg_oai_vspyc_pel_dly            :2;	//(9:8,NA,VNA) //0:0 1:+1 2:+2 3:+3
	UINT32 resvd2                           :2;
	UINT32 reg_oai_yspyc_obj_dly            :2;	//(13:12,NA,VNA) //0:-2 1:-1 2:0 3:+1
	UINT32 resvd3                           :18;
	};
}PE_O24_CC2_PE1_VSP_CC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861650 RW 0x01F1_0000
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x1F1) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861654 RW 0x0200_00BE
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xBE) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861658 RW 0x020D_00F0
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xF0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x20D) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86165C RW 0x0214_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x214) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861660 RW 0x0228_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x228) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861664 RW 0x0230_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x230) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861668 RW 0x023F_00A0
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xA0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x23F) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86166C RW 0x024D_0000
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x24D) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861670 RW 0x2D6E_2000
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x20) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0x6E) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x2D) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861674 RW 0x46FF_39C8
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xC8) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0x39) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x46) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861678 RW 0x66FF_53FF
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x53) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x66) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86167C RW 0x7FFF_7DFF
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x7D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x7F) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861680 RW 0x328C_0F00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0xF) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x32) //
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861684 RW 0x64FF_50FF
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x50) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x64) //
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861688 RW 0xD278_AFFF
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xAF) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0x78) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xD2) //
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86168C RO 0xE600_DC3C
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xDC) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xE6) //
	};
}PE_O24_CC2_PE1_VSP_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616A0 RW 0x0000_0000
	UINT32 enable_debug_mode                :1;	//(0,NA,0x0) //Enable debug mode
	UINT32 status_enable                    :1;	//(1,NA,0x0) //APL
	UINT32 debug_mode                       :1;	//(2,NA,0x0) //0' : status read(APL)	'1' : yc control
	UINT32 resvd0                           :17;
	UINT32 show_apl                         :1;	//(20,NA,0x0) //show apl( y, rgb, r,g,b)
	UINT32 resvd1                           :11;
	};
}PE_O24_CC2_PE1_DEBUG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616A4 RW VNA
	UINT32 yc_debug_en                      :1;	//(0,NA,0x0) //
	UINT32 force_yy_enable                  :1;	//(1,NA,0x0) //forcing Y data enable
	UINT32 force_cb_enable                  :1;	//(2,NA,0x0) //forcing Cb data enable
	UINT32 force_cr_enable                  :1;	//(3,NA,0x0) //forcing Cr data enable
	UINT32 yc_debug_mode_sel                :3;	//(6:4,NA,0x0) //"000" : normal	"001" : show Y only(grayscale)	"010" : show CbCr only	"011" : show Cb data at Y channel	"100" : show Cr data at Y channel	others : normal
	UINT32 resvd                            :25;
	};
}PE_O24_CC2_PE1_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616A8 RW 0x0000_0000
	UINT32 force_yy                         :10;	//(9:0,NA,0x0) //
	UINT32 force_cb                         :10;	//(19:10,NA,0x0) //forcing Cb data
	UINT32 force_cr                         :10;	//(29:20,NA,0x0) //forcing Cr data
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_DEBUG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616B0 RW 0x0000_0100
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
}PE_O24_CC2_PE1_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616B4 RW 0x00C0_C0C0
	UINT32 user_ctrl_g_gain                 :8;	//(7:0,NA,0xC0) //User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//(15:8,NA,0xC0) //User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//(23:16,NA,0xC0) //User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}PE_O24_CC2_PE1_CW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616B8 RW 0x0040_0000
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
}PE_O24_CC2_PE1_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616C0 RW 0x0000_00FF
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616C4 RW 0x0064_00FF
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x64) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616C8 RW 0x011C_00FF
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x11C) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616CC RW 0x01AA_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x1AA) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616D0 RW 0x0238_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x238) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616D4 RW 0x02C6_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x2C6) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616D8 RW 0x0354_00FF
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x354) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616DC RW 0x03FF_00FF
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616E0 RW 0x06FF_00FF
	UINT32 reg_crgn_sat_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x0             :7;	//(14:8,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x1             :7;	//(30:24,NA,0x6) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616E4 RW 0x12FF_0DFF
	UINT32 reg_crgn_sat_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x2             :7;	//(14:8,NA,0xD) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_sat_gain_x3             :7;	//(30:24,NA,0x12) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616E8 RW 0x198C_14DC
	UINT32 reg_crgn_sat_gain_y4             :8;	//(7:0,NA,0xDC) //
	UINT32 reg_crgn_sat_gain_x4             :7;	//(14:8,NA,0x14) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_sat_gain_x5             :7;	//(30:24,NA,0x19) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616EC RW 0x2000_1D3C
	UINT32 reg_crgn_sat_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_sat_gain_x6             :7;	//(14:8,NA,0x1D) //
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_sat_gain_x7             :7;	//(30:24,NA,0x20) //
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616F0 RW 0x6464_3C00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0x3C) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x64) //
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616F4 RW 0x8CC8_7896
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0x96) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x78) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xC8) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x8C) //
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616F8 RW 0xBEFF_A0E6
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xE6) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xA0) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xBE) //
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8616FC RW 0xFFA0_FAFF
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xFA) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0xA0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xFF) //
	};
}PE_O24_CC2_PE1_CW_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861710 RW 0x1E00_10E0
	UINT32 display_height                   :13;	//(12:0,NA,0x10E0) //
	UINT32 resvd0                           :3;
	UINT32 display_width                    :13;	//(28:16,NA,0x1E00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LBLUR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861714 RW 0x0000_0000
	UINT32 reg_block_size_v                 :8;	//(7:0,NA,0x0) //
	UINT32 reg_block_size_h                 :8;	//(15:8,NA,0x0) //
	UINT32 reg_block_no_v                   :6;	//(21:16,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,NA,0x0) //
	};
}PE_O24_CC2_PE1_LBLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861718 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :8;	//(7:0,NA,0x0) //
	UINT32 reg_last_block_size_h            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O24_CC2_PE1_LBLUR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861720 RW 0x8000_0A40
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
}PE_O24_CC2_PE1_LOGO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861724 RW 0x12C2_5BFE
	UINT32 resvd                            :1;
	UINT32 bound_proc_logocheck             :1;	//(1,NA,0x1) //
	UINT32 bound_proc_gain                  :8;	//(9:2,NA,0xff) //
	UINT32 bound_proc_range_x               :11;	//(20:10,NA,0x96) //
	UINT32 bound_proc_range_y               :11;	//(31:21,NA,0x96) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861728 RW 0x0000_0000
	UINT32 boundary_position_x0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_x1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86172C RW 0x0000_0000
	UINT32 boundary_position_y0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_y1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861730 RW 0x03BF_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,NA,0x3BF) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861734 RW 0x10DF_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,NA,0x10DF) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861738 RW 0x0100_0080
	UINT32 reg_region_position_x1           :13;	//(12:0,NA,0x80) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,NA,0x100) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86173C RW 0x0200_0180
	UINT32 reg_region_position_x3           :13;	//(12:0,NA,0x180) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,NA,0x200) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861740 RW 0x0300_0280
	UINT32 reg_region_position_x5           :13;	//(12:0,NA,0x280) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,NA,0x300) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861744 RW 0x03A0_0380
	UINT32 reg_region_position_x7           :13;	//(12:0,NA,0x380) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,NA,0x3A0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861748 RW 0x0800_0400
	UINT32 reg_region_position_y1           :13;	//(12:0,NA,0x400) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,NA,0x800) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86174C RW 0x0E00_0C00
	UINT32 reg_region_position_y3           :13;	//(12:0,NA,0xC00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,NA,0xE00) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861750 RW 0x1000_0F00
	UINT32 reg_region_position_y5           :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,NA,0x1000) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861754 RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861758 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86175C RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861760 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861764 RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861768 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86176C RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861770 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861774 RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861778 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86177C RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861780 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861784 RW 0x0200_0310
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x310) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861788 RW 0x0080_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x80) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86178C RW 0x2040_80C4
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xC4) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x20) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861790 RW 0x0380_03FF
	UINT32 reg_drop_x7_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,NA,0x380) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861794 RW 0x0200_0300
	UINT32 reg_drop_x5_i                    :10;	//(9:0,NA,0x300) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861798 RW 0x0100_0200
	UINT32 reg_drop_x3_i                    :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,NA,0x100) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86179C RW 0x0000_0100
	UINT32 reg_drop_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617A0 RW 0x0200_0240
	UINT32 reg_drop_y7_i                    :10;	//(9:0,NA,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617A4 RW 0x0190_01C0
	UINT32 reg_drop_y5_i                    :10;	//(9:0,NA,0x1C0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,NA,0x190) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617A8 RW 0x00E0_0190
	UINT32 reg_drop_y3_i                    :10;	//(9:0,NA,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,NA,0xE0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617AC RW 0x0000_00E0
	UINT32 reg_drop_y1_i                    :10;	//(9:0,NA,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617B0 RW 0x0300_03FF
	UINT32 reg_sat_scon_x3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617B4 RW 0x0000_0200
	UINT32 reg_sat_scon_x1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617B8 RW 0x0300_03FF
	UINT32 reg_sat_scon_y3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617BC RW 0x0000_0200
	UINT32 reg_sat_scon_y1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617C0 RW 0x1080_1080
	UINT32 reg_l7_gain_drop                 :8;	//(7:0,NA,0x80) //
	UINT32 reg_l7_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l7_gain_b_contrast           :8;	//(23:16,NA,0x80) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l7_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617C4 RW 0x0840_1040
	UINT32 reg_l3_gain_drop                 :8;	//(7:0,NA,0x40) //
	UINT32 reg_l3_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l3_gain_b_contrast           :8;	//(23:16,NA,0x40) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l3_gain_saturation           :8;	//(31:24,NA,0x8) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617C8 RW 0x1060_20A4
	UINT32 reg_c5_gain_drop                 :8;	//(7:0,NA,0xA4) //
	UINT32 reg_c5_gain_w_contrast           :8;	//(15:8,NA,0x20) //white(bright) contrast gain(input level < output level)
	UINT32 reg_c5_gain_b_contrast           :8;	//(23:16,NA,0x60) //black(dark) contrast gain(input level > output level)
	UINT32 reg_c5_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617CC RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O24_CC2_PE1_LOGO_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617D0 RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617D4 RW 0x0000_0000
	UINT32 reg_merge_contrast_l7l3          :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_contrast_l7l3c5        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_drop_l7l3              :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617D8 RW 0x0000_0000
	UINT32 reg_merge_drop_l7l3c5            :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3c5      :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617DC RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable LOGO inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable LOGO outside window
	};
}PE_O24_CC2_PE1_LOGO_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617E0 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617F4 RW 0x0040_80FF
	UINT32 reg_txt_x3_i                     :8;	//(7:0,NA,0xFF) //texture gain LUT
	UINT32 reg_txt_x2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_x1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_x0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617F8 RW 0x0040_80FF
	UINT32 reg_txt_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_txt_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8617FC RW 0x0080_8080
	UINT32 reg_region_gain_contrast         :8;	//(7:0,NA,0x80) //1.0 = 128
	UINT32 reg_region_gain_drop             :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_saturation       :8;	//(23:16,NA,0x80) //
	UINT32 resvd                            :8;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861800 RW 0x0000_0140
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
}PE_O24_CC2_PE1_LOGO_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861804 RW 0x00000000
	UINT32 reg_refine_weight_lut_x3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_x2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_x1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_x0         :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861808 RW 0x00000000
	UINT32 reg_refine_weight_lut_y3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_y2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_y1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_y0         :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86180C RW 0x00000000
	UINT32 reg_refine_weight_gain_x3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_x2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_x1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_x0        :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861810 RW 0x00000000
	UINT32 reg_refine_weight_gain_y3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_y2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_y1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_y0        :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861820 RW 0x0000_0000
	UINT32 reg_gsr_blend_en                 :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//(7:4,NA,0x0) //0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//(25:16,NA,0x0) //
	UINT32 resvd2                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861824 RW 0x03B0_4200
	UINT32 reg_curr_peak_level              :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :2;
	UINT32 reg_crnt_resol_sel               :4;	//(15:12,NA,0x4) //left shift bit size, 0:8b, 1:7b, 2:6b, 3:5b, 4:4b, 5:3b, 6:2b, 7:1b, 8:0b
	UINT32 reg_wg_ratio                     :11;	//(26:16,NA,0x3B0) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC2_PE1_GSR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861828 RW 0x0478_031F
	UINT32 reg_wb_ratio                     :11;	//(10:0,NA,0x31F) //
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//(26:16,NA,0x478) //
	UINT32 resvd1                           :5;
	};
}PE_O24_CC2_PE1_GSR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86182C RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,NA,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,NA,0x326) //
	UINT32 resvd1                           :4;
	};
}PE_O24_CC2_PE1_GSR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861830 RW 0x0389_02A8
	UINT32 reg_b_crnt_wgt                   :12;	//(11:0,NA,0x2A8) //
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//(27:16,NA,0x389) //
	UINT32 resvd1                           :4;
	};
}PE_O24_CC2_PE1_GSR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861834 RW 0x0000_0000
	UINT32 reg_crnt_lut_y00                 :16;	//(15:0,NA,0x0) //
	UINT32 reg_crnt_lut_x00                 :10;	//(25:16,NA,0x0) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861838 RW 0x0044_0CF9
	UINT32 reg_crnt_lut_y01                 :16;	//(15:0,NA,0xCF9) //
	UINT32 reg_crnt_lut_x01                 :10;	//(25:16,NA,0x44) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86183C RW 0x0088_1BD0
	UINT32 reg_crnt_lut_y02                 :16;	//(15:0,NA,0x1BD0) //
	UINT32 reg_crnt_lut_x02                 :10;	//(25:16,NA,0x88) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861840 RW 0x00CC_2B72
	UINT32 reg_crnt_lut_y03                 :16;	//(15:0,NA,0x2B72) //
	UINT32 reg_crnt_lut_x03                 :10;	//(25:16,NA,0xCC) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861844 RW 0x0110_3B9F
	UINT32 reg_crnt_lut_y04                 :16;	//(15:0,NA,0x3B9F) //
	UINT32 reg_crnt_lut_x04                 :10;	//(25:16,NA,0x110) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861848 RW 0x0154_4C35
	UINT32 reg_crnt_lut_y05                 :16;	//(15:0,NA,0x4C35) //
	UINT32 reg_crnt_lut_x05                 :10;	//(25:16,NA,0x154) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86184C RW 0x0198_5D22
	UINT32 reg_crnt_lut_y06                 :16;	//(15:0,NA,0x5D22) //
	UINT32 reg_crnt_lut_x06                 :10;	//(25:16,NA,0x198) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861850 RW 0x01DC_6E57
	UINT32 reg_crnt_lut_y07                 :16;	//(15:0,NA,0x6E57) //
	UINT32 reg_crnt_lut_x07                 :10;	//(25:16,NA,0x1DC) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861854 RW 0x0220_7FCD
	UINT32 reg_crnt_lut_y08                 :16;	//(15:0,NA,0x7FCD) //
	UINT32 reg_crnt_lut_x08                 :10;	//(25:16,NA,0x220) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861858 RW 0x0264_917A
	UINT32 reg_crnt_lut_y09                 :16;	//(15:0,NA,0x917A) //
	UINT32 reg_crnt_lut_x09                 :10;	//(25:16,NA,0x264) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86185C RW 0x02A8_A35B
	UINT32 reg_crnt_lut_y10                 :16;	//(15:0,NA,0xA35B) //
	UINT32 reg_crnt_lut_x10                 :10;	//(25:16,NA,0x2A8) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861860 RW 0x02EC_B569
	UINT32 reg_crnt_lut_y11                 :16;	//(15:0,NA,0xB569) //
	UINT32 reg_crnt_lut_x11                 :10;	//(25:16,NA,0x2EC) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861864 RW 0x0330_C7A2
	UINT32 reg_crnt_lut_y12                 :16;	//(15:0,NA,0xC7A2) //
	UINT32 reg_crnt_lut_x12                 :10;	//(25:16,NA,0x330) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861868 RW 0x0374_DA02
	UINT32 reg_crnt_lut_y13                 :16;	//(15:0,NA,0xDA02) //
	UINT32 reg_crnt_lut_x13                 :10;	//(25:16,NA,0x374) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86186C RW 0x03B8_EC86
	UINT32 reg_crnt_lut_y14                 :16;	//(15:0,NA,0xEC86) //
	UINT32 reg_crnt_lut_x14                 :10;	//(25:16,NA,0x3B8) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861870 RW 0x03FF_FFFF
	UINT32 reg_crnt_lut_y15                 :16;	//(15:0,NA,0xFFFF) //
	UINT32 reg_crnt_lut_x15                 :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd                            :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861874 RW 0x0200_03FF
	UINT32 reg_crnt_x3_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x2_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861878 RW 0x0000_0100
	UINT32 reg_crnt_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86187C RW 0x0000_0000
	UINT32 reg_crnt_y3_i                    :8;	//(7:0,NA,0x0) //
	UINT32 reg_crnt_y2_i                    :8;	//(15:8,NA,0x0) //
	UINT32 reg_crnt_y1_i                    :8;	//(23:16,NA,0x0) //
	UINT32 reg_crnt_y0_i                    :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_GSR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861880 RW 0x0200_03FF
	UINT32 reg_value_x3_i                   :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x2_i                   :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861884 RW 0x0000_0100
	UINT32 reg_value_x1_i                   :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x0_i                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861888 RW 0x0000_0000
	UINT32 reg_value_y3_i                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_value_y2_i                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_value_y1_i                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_value_y0_i                   :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_GSR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86188C RW 0x0200_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861890 RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_GSR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861894 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_GSR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861898 RW 0x0000_0000
	UINT32 reg_pxl_x0_0                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_0             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_0                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_0            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O24_CC2_PE1_GSR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86189C RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_GSR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618A0 RW 0x0000_0000
	UINT32 reg_pxl_x0_1                     :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable_1             :1;	//(15,NA,0x0) //disable GSR inside window
	UINT32 reg_pxl_y0_1                     :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable_1            :1;	//(31,NA,0x0) //disable GSR outside window
	};
}PE_O24_CC2_PE1_GSR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618A4 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_GSR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618E0 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618E4 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618E8 RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618EC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618F0 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618F4 RW 0x0000_0000
	UINT32 pxl_rep_xpos_0                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_0                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_0                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_0                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618F8 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_0                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8618FC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861900 RW VNA
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861904 RW 0x0000_0000
	UINT32 reg_col_fil_g_valid              :1;	//(0,NA,0x0) //G Color filter selected rectangle
	UINT32 reg_col_fil_b_valid              :1;	//(1,NA,0x0) //B Color filter selected rectangle
	UINT32 reg_col_fil_r_valid              :1;	//(2,NA,0x0) //R Color filter selected rectangle
	UINT32 reg_col_fil_g_nvalid             :1;	//(3,NA,0x0) //G Color filter non-selected rectangle
	UINT32 reg_col_fil_b_nvalid             :1;	//(4,NA,0x0) //B Color filter non-selected rectangle
	UINT32 reg_col_fil_r_nvalid             :1;	//(5,NA,0x0) //R Color filter non-selected rectangle
	UINT32 resvd                            :26;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861908 RW 0x0000_0000
	UINT32 mux3d_en                         :1;	//(0,NA,0x0) //Mux 3D on/off	'0' = off	'1' = on
	UINT32 resvd0                           :3;
	UINT32 reg_out_mux                      :2;	//(5:4,NA,0x00) //output select	'00' = blend	'01' = R	'10' = L	'11' = line by line
	UINT32 start_parity                     :1;	//(6,NA,0x00) //start parity	'0' : start with Left	'1' : start with Right
	UINT32 resvd1                           :9;
	UINT32 alpha1_gain                      :8;	//(23:16,NA,0x0) //gain for L, R channel blend	255 : L output ~ 0 : R output
	UINT32 alpha0_gain                      :8;	//(31:24,NA,0x0) //gain for Back Ground Color and Blended Data	255 : BG Color output ~ 0 : Data output
	};
}PE_O24_CC2_PE1_MUTE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86190C RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_0              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_0              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O24_CC2_PE1_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861910 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861914 RW 0x0000_0000
	UINT32 x0_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_0              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_0              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O24_CC2_PE1_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861918 RW 0x0000_0000
	UINT32 x1_0                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_0                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86191C RW 0x0000_0000
	UINT32 bg_color_r                       :8;	//(7:0,NA,0x0) //8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//(15:8,NA,0x0) //8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//(23:16,NA,0x0) //8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861920 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861924 RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861928 RW 0x0000_0000
	UINT32 pxl_rep_xpos_1                   :13;	//(12:0,NA,0x0) //x position for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_ypos_1                   :13;	//(28:16,NA,0x0) //y position for pixel replacement
	UINT32 pxl_rep_in_1                     :1;	//(29,NA,0x0) //enable pixel replacement for inside rectangle
	UINT32 pxl_rep_out_1                    :1;	//(30,NA,0x0) //enable pixel replacement for outside rectangle
	UINT32 resvd1                           :1;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86192C RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :13;	//(12:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :3;
	UINT32 pxl_rep_height_1                 :13;	//(28:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861930 RW 0x0000_0000
	UINT32 x0_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_l_window_h_en_1              :1;	//(15,NA,0x0) //L channel (horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_l_window_v_en_1              :1;	//(31,NA,0x0) //L channel (vertical) window mode enable
	};
}PE_O24_CC2_PE1_MUTE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861934 RW 0x0000_0000
	UINT32 x1_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861938 RW 0x0000_0000
	UINT32 x0_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 mux_r_window_h_en_1              :1;	//(15,NA,0x0) //(horizontal) window mode enable	'0' = full screen	'1' = window by manual setting
	UINT32 y0_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 mux_r_window_v_en_1              :1;	//(31,NA,0x0) //(vertical) window mode enable
	};
}PE_O24_CC2_PE1_MUTE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86193C RW 0x0000_0000
	UINT32 x1_1                             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 y1_1                             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MUTE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A00 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A04 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A08 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A0C RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A10 RW 0x0000_0000
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
}PE_O24_CC2_PE1_LOGO_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A14 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A18 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A1C RW 0x0002_0028
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A20 RW 0x0002_0028
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A24 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A28 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A2C RW 0x0000_0000
	UINT32 reg_master_gain                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_l3_value_gain                :8;	//(15:8,RW,0x0) //
	UINT32 reg_master_en                    :1;	//(16,RW,0x0) //master en
	UINT32 resvd0                           :3;
	UINT32 reg_out_sel                      :2;	//(21:20,RW,0x0) //0:blend out 1:drop img 2:drop gain 3:s_gain
	UINT32 resvd1                           :2;
	UINT32 reg_l3_en                        :1;	//(24,RW,0x0) //l3 gain en
	UINT32 resvd2                           :7;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A30 RW 0x0000_0000
	UINT32 reg_sat_x3_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A34 RW 0x0000_0000
	UINT32 reg_sat_x1_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A38 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,RW,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A3C RW 0x0000_0000
	UINT32 reg_drop_x7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A40 RW 0x0000_0000
	UINT32 reg_drop_x5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A44 RW 0x0000_0000
	UINT32 reg_drop_x3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A48 RW 0x0000_0000
	UINT32 reg_drop_x1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A4C RW 0x0000_0000
	UINT32 reg_drop_y7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A50 RW 0x0000_0000
	UINT32 reg_drop_y5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A54 RW 0x0000_0000
	UINT32 reg_drop_y3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A58 RW 0x0000_0000
	UINT32 reg_drop_y1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A5C RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_out_disable              :1;	//(15,RW,0x0) //
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_in_disable               :1;	//(31,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A60 RW 0x0000_0000
	UINT32 reg_pxl_w                        :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A64 RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_out_disable              :1;	//(15,RW,0x0) //
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_in_disable               :1;	//(31,RW,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A68 RW 0x0000_0000
	UINT32 reg_pxl_w                        :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CC2_PE1_LOGO_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861A6C RW 0x0000_0000
	UINT32 reg_detour                       :1;	//(0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_use_extern_valid             :1;	//(4,NA,0x0) //logo refine dummy valid gen param
	UINT32 resvd1                           :3;
	UINT32 reg_use_blank_period_cnt         :1;	//(8,NA,0x1) //logo refine dummy valid gen param
	UINT32 resvd2                           :7;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,NA,0x0) //
	};
}PE_O24_CC2_PE1_LOGO_CTRL_88_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC861AA0 RW 0x0000_000F
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
}PE_O24_CC2_PE1_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AA4 NA 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AA8 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AAC RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AB0 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AB4 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AB8 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861ABC RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AC0 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AC4 RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AC8 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861ACC RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AD0 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AD4 RW 0x0000_000F
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
}PE_O24_CC2_PE1_MERGE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AD8 NA 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861ADC RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AE0 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AE4 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AE8 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AEC RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AF0 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AF4 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AF8 RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861AFC RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B00 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B04 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B08 RW 0x0000_000F
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
}PE_O24_CC2_PE1_MERGE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B0C NA 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B10 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B14 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B18 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B1C RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B20 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B24 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B28 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B2C RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B30 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B34 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B38 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B3C RW 0x0000_000F
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
}PE_O24_CC2_PE1_MERGE_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B40 NA 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B44 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B48 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B4C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B50 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B54 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B58 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B5C RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B60 RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B64 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B68 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B6C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B70 RW 0x8080_8007
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
}PE_O24_CC2_PE1_MERGE_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B74 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B78 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B7C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B80 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B84 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B88 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B8C RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B90 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B94 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B98 RW 0x0000_000F
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
}PE_O24_CC2_PE1_MERGE_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861B9C NA 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BA0 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BA4 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BA8 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BAC RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BB0 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BB4 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BB8 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BBC RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}PE_O24_CC2_PE1_MERGE_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BC0 RW 0x0000_0000
	UINT32 reg_pxl_x0                       :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15,NA,0x0) //disable merge_gain inside window
	UINT32 reg_pxl_y0                       :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31,NA,0x0) //disable merge_gain outside window
	};
}PE_O24_CC2_PE1_MERGE_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BC4 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //1
	UINT32 resvd1                           :3;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861BC8 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}PE_O24_CC2_PE1_MERGE_CTRL_74_T;


typedef struct {
	PE_O24_CC_PE1_TOP_CTRL_00_T                            pe1_top_ctrl_00;	//0xCC861000
	PE_O24_CC_PE1_TOP_CTRL_01_T                            pe1_top_ctrl_01;	//0xCC861004
	PE_O24_CC_PE1_TOP_CTRL_02_T                            pe1_top_ctrl_02;	//0xCC861008
	PE_O24_CC_PE1_TOP_CTRL_03_T                            pe1_top_ctrl_03;	//0xCC86100C
	PE_O24_CC_PE1_TOP_CTRL_04_T                            pe1_top_ctrl_04;	//0xCC861010
	UINT32                                                    reserved0;	//0xCC861014
	UINT32                                                    reserved1;	//0xCC861018
	UINT32                                                    reserved2;	//0xCC86101C
	PE_O24_CC_PE1_FSW_CTRL_00_T                            pe1_fsw_ctrl_00;	//0xCC861020
	PE_O24_CC_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xCC861024
	PE_O24_CC_PE1_FSW_CTRL_02_T                            pe1_fsw_ctrl_02;	//0xCC861028
	PE_O24_CC_PE1_FSW_CTRL_03_T                            pe1_fsw_ctrl_03;	//0xCC86102C
	PE_O24_CC_PE1_FSW_CTRL_04_T                            pe1_fsw_ctrl_04;	//0xCC861030
	PE_O24_CC_PE1_FSW_CTRL_05_T                            pe1_fsw_ctrl_05;	//0xCC861034
	PE_O24_CC_PE1_FSW_CTRL_06_T                            pe1_fsw_ctrl_06;	//0xCC861038
	PE_O24_CC_PE1_FSW_CTRL_07_T                            pe1_fsw_ctrl_07;	//0xCC86103C
	UINT32                                                    reserved3;	//0xCC861040
	UINT32                                                    reserved4;	//0xCC861044
	UINT32                                                    reserved5;	//0xCC861048
	UINT32                                                    reserved6;	//0xCC86104C
	PE_O24_CC_PE1_TPG_CTRL_00_T                            pe1_tpg_ctrl_00;	//0xCC861050
	PE_O24_CC_PE1_TPG_CTRL_01_T                            pe1_tpg_ctrl_01;	//0xCC861054
	PE_O24_CC_PE1_TPG_CTRL_02_T                            pe1_tpg_ctrl_02;	//0xCC861058
	PE_O24_CC_PE1_TPG_CTRL_03_T                            pe1_tpg_ctrl_03;	//0xCC86105C
	PE_O24_CC_PE1_TPG_CTRL_04_T                            pe1_tpg_ctrl_04;	//0xCC861060
	PE_O24_CC_PE1_TPG_IA_CTRL_T                            pe1_tpg_ia_ctrl;	//0xCC861064
	PE_O24_CC_PE1_TPG_IA_DATA_T                            pe1_tpg_ia_data;	//0xCC861068
	UINT32                                                    reserved7;	//0xCC86106C
	PE_O24_CC_PE1_APL_CTRL_00_T                            pe1_apl_ctrl_00;	//0xCC861070
	PE_O24_CC_PE1_APL_CTRL_01_T                            pe1_apl_ctrl_01;	//0xCC861074
	PE_O24_CC_PE1_APL_CTRL_02_T                            pe1_apl_ctrl_02;	//0xCC861078
	PE_O24_CC_PE1_APL_CTRL_03_T                            pe1_apl_ctrl_03;	//0xCC86107C
	PE_O24_CC_PE1_APL_CTRL_04_T                            pe1_apl_ctrl_04;	//0xCC861080
	PE_O24_CC_PE1_APL_CTRL_05_T                            pe1_apl_ctrl_05;	//0xCC861084
	PE_O24_CC_PE1_APL_CTRL_06_T                            pe1_apl_ctrl_06;	//0xCC861088
	PE_O24_CC_PE1_APL_CTRL_07_T                            pe1_apl_ctrl_07;	//0xCC86108C
	PE_O24_CC_PE1_APL_CTRL_08_T                            pe1_apl_ctrl_08;	//0xCC861090
	UINT32                                                    reserved8;	//0xCC861094
	UINT32                                                    reserved9;	//0xCC861098
	UINT32                                                   reserved10;	//0xCC86109C
	UINT32                                                   reserved11;	//0xCC8610A0
	UINT32                                                   reserved12;	//0xCC8610A4
	UINT32                                                   reserved13;	//0xCC8610A8
	UINT32                                                   reserved14;	//0xCC8610AC
	UINT32                                                   reserved15;	//0xCC8610B0
	PE_O24_CC_PE1_APL_STAT_00_T                            pe1_apl_stat_00;	//0xCC8610B4
	PE_O24_CC_PE1_APL_STAT_01_T                            pe1_apl_stat_01;	//0xCC8610B8
	UINT32                                                   reserved16;	//0xCC8610BC
	PE_O24_CC_PE1_BT20_CTRL_00_T                          pe1_bt20_ctrl_00;	//0xCC8610C0
	PE_O24_CC_PE1_BT20_CTRL_01_T                          pe1_bt20_ctrl_01;	//0xCC8610C4
	PE_O24_CC_PE1_BT20_CTRL_02_T                          pe1_bt20_ctrl_02;	//0xCC8610C8
	PE_O24_CC_PE1_BT20_CTRL_03_T                          pe1_bt20_ctrl_03;	//0xCC8610CC
	PE_O24_CC_PE1_BT20_CTRL_04_T                          pe1_bt20_ctrl_04;	//0xCC8610D0
	PE_O24_CC_PE1_BT20_CTRL_05_T                          pe1_bt20_ctrl_05;	//0xCC8610D4
	PE_O24_CC_PE1_BT20_CTRL_06_T                          pe1_bt20_ctrl_06;	//0xCC8610D8
	PE_O24_CC_PE1_BT20_CTRL_07_T                          pe1_bt20_ctrl_07;	//0xCC8610DC
	PE_O24_CC_PE1_BT20_CTRL_08_T                          pe1_bt20_ctrl_08;	//0xCC8610E0
	PE_O24_CC_PE1_BT20_CTRL_09_T                          pe1_bt20_ctrl_09;	//0xCC8610E4
	PE_O24_CC_PE1_BT20_CTRL_10_T                          pe1_bt20_ctrl_10;	//0xCC8610E8
	PE_O24_CC_PE1_BT20_CTRL_11_T                          pe1_bt20_ctrl_11;	//0xCC8610EC
	PE_O24_CC_PE1_BT20_CTRL_12_T                          pe1_bt20_ctrl_12;	//0xCC8610F0
	PE_O24_CC_PE1_BT20_CTRL_13_T                          pe1_bt20_ctrl_13;	//0xCC8610F4
	PE_O24_CC_PE1_BT20_CTRL_14_T                          pe1_bt20_ctrl_14;	//0xCC8610F8
	PE_O24_CC_PE1_BT20_CTRL_15_T                          pe1_bt20_ctrl_15;	//0xCC8610FC
	PE_O24_CC_PE1_BT20_CTRL_16_T                          pe1_bt20_ctrl_16;	//0xCC861100
	PE_O24_CC_PE1_BT20_CTRL_17_T                          pe1_bt20_ctrl_17;	//0xCC861104
	PE_O24_CC_PE1_BT20_CTRL_18_T                          pe1_bt20_ctrl_18;	//0xCC861108
	PE_O24_CC_PE1_BT20_CTRL_19_T                          pe1_bt20_ctrl_19;	//0xCC86110C
	PE_O24_CC_PE1_BT20_CTRL_20_T                          pe1_bt20_ctrl_20;	//0xCC861110
	PE_O24_CC_PE1_BT20_CTRL_21_T                          pe1_bt20_ctrl_21;	//0xCC861114
	PE_O24_CC_PE1_BT20_CTRL_STAT_00_T                pe1_bt20_ctrl_stat_00;	//0xCC861118
	PE_O24_CC_PE1_BT20_CTRL_STAT_01_T                pe1_bt20_ctrl_stat_01;	//0xCC86111C
	PE_O24_CC_PE1_BT20_CTRL_STAT_02_T                pe1_bt20_ctrl_stat_02;	//0xCC861120
	PE_O24_CC_PE1_BT20_CTRL_STAT_03_T                pe1_bt20_ctrl_stat_03;	//0xCC861124
	UINT32                                                   reserved17;	//0xCC861128
	UINT32                                                   reserved18;	//0xCC86112C
	UINT32                                                   reserved19;	//0xCC861130
	UINT32                                                   reserved20;	//0xCC861134
	UINT32                                                   reserved21;	//0xCC861138
	UINT32                                                   reserved22;	//0xCC86113C
	PE_O24_CC_PE1_WIN2_CTRL_00_T                          pe1_win2_ctrl_00;	//0xCC861140
	PE_O24_CC_PE1_WIN2_CTRL_01_T                          pe1_win2_ctrl_01;	//0xCC861144
	PE_O24_CC_PE1_WIN2_CTRL_02_T                          pe1_win2_ctrl_02;	//0xCC861148
	PE_O24_CC_PE1_WIN2_CTRL_03_T                          pe1_win2_ctrl_03;	//0xCC86114C
	PE_O24_CC_PE1_WIN2_CTRL_04_T                          pe1_win2_ctrl_04;	//0xCC861150
	PE_O24_CC_PE1_WIN2_CTRL_05_T                          pe1_win2_ctrl_05;	//0xCC861154
	PE_O24_CC_PE1_WIN2_CTRL_06_T                          pe1_win2_ctrl_06;	//0xCC861158
	PE_O24_CC_PE1_WIN2_CTRL_07_T                          pe1_win2_ctrl_07;	//0xCC86115C
	PE_O24_CC_PE1_WIN2_CTRL_08_T                          pe1_win2_ctrl_08;	//0xCC861160
	UINT32                                                   reserved23;	//0xCC861164
	UINT32                                                   reserved24;	//0xCC861168
	UINT32                                                   reserved25;	//0xCC86116C
	UINT32                                                   reserved26;	//0xCC861170
	UINT32                                                   reserved27;	//0xCC861174
	UINT32                                                   reserved28;	//0xCC861178
	UINT32                                                   reserved29;	//0xCC86117C
	UINT32                                                   reserved30;	//0xCC861180
	UINT32                                                   reserved31;	//0xCC861184
	UINT32                                                   reserved32;	//0xCC861188
	UINT32                                                   reserved33;	//0xCC86118C
	UINT32                                                   reserved34;	//0xCC861190
	UINT32                                                   reserved35;	//0xCC861194
	UINT32                                                   reserved36;	//0xCC861198
	UINT32                                                   reserved37;	//0xCC86119C
	UINT32                                                   reserved38;	//0xCC8611A0
	UINT32                                                   reserved39;	//0xCC8611A4
	UINT32                                                   reserved40;	//0xCC8611A8
	UINT32                                                   reserved41;	//0xCC8611AC
	UINT32                                                   reserved42;	//0xCC8611B0
	UINT32                                                   reserved43;	//0xCC8611B4
	UINT32                                                   reserved44;	//0xCC8611B8
	UINT32                                                   reserved45;	//0xCC8611BC
	UINT32                                                   reserved46;	//0xCC8611C0
	UINT32                                                   reserved47;	//0xCC8611C4
	UINT32                                                   reserved48;	//0xCC8611C8
	UINT32                                                   reserved49;	//0xCC8611CC
	PE_O24_CC_PE1_CEN_CTRL_00_T                            pe1_cen_ctrl_00;	//0xCC8611D0
	PE_O24_CC_PE1_CEN_CTRL_01_T                            pe1_cen_ctrl_01;	//0xCC8611D4
	PE_O24_CC_PE1_CEN_CTRL_02_T                            pe1_cen_ctrl_02;	//0xCC8611D8
	PE_O24_CC_PE1_CEN_CTRL_03_T                            pe1_cen_ctrl_03;	//0xCC8611DC
	PE_O24_CC_PE1_CEN_CTRL_04_T                            pe1_cen_ctrl_04;	//0xCC8611E0
	PE_O24_CC_PE1_CEN_CTRL_05_T                            pe1_cen_ctrl_05;	//0xCC8611E4
	PE_O24_CC_PE1_CEN_CTRL_06_T                            pe1_cen_ctrl_06;	//0xCC8611E8
	PE_O24_CC_PE1_CEN_CTRL_07_T                            pe1_cen_ctrl_07;	//0xCC8611EC
	UINT32                                                   reserved50;	//0xCC8611F0
	UINT32                                                   reserved51;	//0xCC8611F4
	PE_O24_CC_PE1_CEN_UPD_CTRL_T                          pe1_cen_upd_ctrl;	//0xCC8611F8
	UINT32                                                   reserved52;	//0xCC8611FC
	PE_O24_CC_PE1_CEN_IA_CTRL_T                            pe1_cen_ia_ctrl;	//0xCC861200
	PE_O24_CC_PE1_CEN_IA_DATA_T                            pe1_cen_ia_data;	//0xCC861204
	PE_O24_CC_PE1_CEN_DELTA_IA_CTRL_T                pe1_cen_delta_ia_ctrl;	//0xCC861208
	PE_O24_CC_PE1_CEN_DELTA_IA_DATA_T                pe1_cen_delta_ia_data;	//0xCC86120C
	UINT32                                                   reserved53;	//0xCC861210
	UINT32                                                   reserved54;	//0xCC861214
	UINT32                                                   reserved55;	//0xCC861218
	UINT32                                                   reserved56;	//0xCC86121C
	PE_O24_CC_PE1_DCE_CTRL_00_T                            pe1_dce_ctrl_00;	//0xCC861220
	PE_O24_CC_PE1_DCE_CTRL_01_T                            pe1_dce_ctrl_01;	//0xCC861224
	PE_O24_CC_PE1_DCE_CTRL_02_T                            pe1_dce_ctrl_02;	//0xCC861228
	PE_O24_CC_PE1_DCE_CTRL_03_T                            pe1_dce_ctrl_03;	//0xCC86122C
	PE_O24_CC_PE1_DCE_CTRL_04_T                            pe1_dce_ctrl_04;	//0xCC861230
	PE_O24_CC_PE1_DCE_CTRL_05_T                            pe1_dce_ctrl_05;	//0xCC861234
	PE_O24_CC_PE1_DCE_IA_CTRL_T                            pe1_dce_ia_ctrl;	//0xCC861238
	PE_O24_CC_PE1_DCE_IA_DATA_T                            pe1_dce_ia_data;	//0xCC86123C
	PE_O24_CC_PE1_DCE_CTRL_08_T                            pe1_dce_ctrl_08;	//0xCC861240
	UINT32                                                   reserved57;	//0xCC861244
	PE_O24_CC_PE1_DCE_HIST_IA_CTRL_T                  pe1_dce_hist_ia_ctrl;	//0xCC861248
	PE_O24_CC_PE1_DCE_HIST_IA_DATA1_T                pe1_dce_hist_ia_data1;	//0xCC86124C
	PE_O24_CC_PE1_DCE_HIST_IA_DATA2_T                pe1_dce_hist_ia_data2;	//0xCC861250
	PE_O24_CC_PE1_DCE_CHR_GAIN_T                          pe1_dce_chr_gain;	//0xCC861254
	PE_O24_CC_PE1_DCE_CHR_ALPHA_T                        pe1_dce_chr_alpha;	//0xCC861258
	PE_O24_CC_PE1_DCE_CHR_GAIN2_T                        pe1_dce_chr_gain2;	//0xCC86125C
	UINT32                                                   reserved58;	//0xCC861260
	UINT32                                                   reserved59;	//0xCC861264
	UINT32                                                   reserved60;	//0xCC861268
	UINT32                                                   reserved61;	//0xCC86126C
	PE_O24_CC_PE1_DSE_CTRL_00_T                            pe1_dse_ctrl_00;	//0xCC861270
	PE_O24_CC_PE1_DSE_CTRL_01_T                            pe1_dse_ctrl_01;	//0xCC861274
	PE_O24_CC_PE1_DSE_CTRL_02_T                            pe1_dse_ctrl_02;	//0xCC861278
	PE_O24_CC_PE1_DSE_IA_CTRL_T                            pe1_dse_ia_ctrl;	//0xCC86127C
	PE_O24_CC_PE1_DSE_IA_DATA_T                            pe1_dse_ia_data;	//0xCC861280
	PE_O24_CC_PE1_DSE_CTRL_03_T                            pe1_dse_ctrl_03;	//0xCC861284
	PE_O24_CC_PE1_DSE_CTRL_04_T                            pe1_dse_ctrl_04;	//0xCC861288
	PE_O24_CC_PE_DSE_Y_REGION_PT0_T                    pe_dse_y_region_pt0;	//0xCC86128C
	PE_O24_CC_PE_DSE_Y_REGION_PT1_T                    pe_dse_y_region_pt1;	//0xCC861290
	PE_O24_CC_PE_DSE_Y_REGION_PT2_T                    pe_dse_y_region_pt2;	//0xCC861294
	PE_O24_CC_PE_DSE_Y_REGION_PT3_T                    pe_dse_y_region_pt3;	//0xCC861298
	PE_O24_CC_PE_DSE_Y_REGION_PT4_T                    pe_dse_y_region_pt4;	//0xCC86129C
	PE_O24_CC_PE_DSE_Y_REGION_PT5_T                    pe_dse_y_region_pt5;	//0xCC8612A0
	PE_O24_CC_PE_DSE_Y_REGION_PT6_T                    pe_dse_y_region_pt6;	//0xCC8612A4
	PE_O24_CC_PE_DSE_Y_REGION_PT7_T                    pe_dse_y_region_pt7;	//0xCC8612A8
	PE_O24_CC_PE_DSE_H_REGION_PT0_T                    pe_dse_h_region_pt0;	//0xCC8612AC
	PE_O24_CC_PE_DSE_H_REGION_PT1_T                    pe_dse_h_region_pt1;	//0xCC8612B0
	PE_O24_CC_PE_DSE_H_REGION_PT2_T                    pe_dse_h_region_pt2;	//0xCC8612B4
	PE_O24_CC_PE_DSE_H_REGION_PT3_T                    pe_dse_h_region_pt3;	//0xCC8612B8
	PE_O24_CC_PE_DSE_H_REGION_PT4_T                    pe_dse_h_region_pt4;	//0xCC8612BC
	PE_O24_CC_PE_DSE_H_REGION_PT5_T                    pe_dse_h_region_pt5;	//0xCC8612C0
	PE_O24_CC_PE_DSE_H_REGION_PT6_T                    pe_dse_h_region_pt6;	//0xCC8612C4
	PE_O24_CC_PE_DSE_H_REGION_PT7_T                    pe_dse_h_region_pt7;	//0xCC8612C8
	UINT32                                                   reserved62;	//0xCC8612CC
	UINT32                                                   reserved63;	//0xCC8612D0
	UINT32                                                   reserved64;	//0xCC8612D4
	UINT32                                                   reserved65;	//0xCC8612D8
	UINT32                                                   reserved66;	//0xCC8612DC
	PE_O24_CC_PE1_DRC_CTRL_00_T                            pe1_drc_ctrl_00;	//0xCC8612E0
	PE_O24_CC_PE1_DRC_CTRL_01_T                            pe1_drc_ctrl_01;	//0xCC8612E4
	PE_O24_CC_PE1_DRC_CTRL_02_T                            pe1_drc_ctrl_02;	//0xCC8612E8
	PE_O24_CC_PE1_DRC_CTRL_03_T                            pe1_drc_ctrl_03;	//0xCC8612EC
	PE_O24_CC_PE1_DRC_CTRL_04_T                            pe1_drc_ctrl_04;	//0xCC8612F0
	PE_O24_CC_PE1_DRC_CTRL_05_T                            pe1_drc_ctrl_05;	//0xCC8612F4
	PE_O24_CC_PE1_DRC_CTRL_06_T                            pe1_drc_ctrl_06;	//0xCC8612F8
	PE_O24_CC_PE1_DRC_CTRL_07_T                            pe1_drc_ctrl_07;	//0xCC8612FC
	PE_O24_CC_PE1_DRC_CTRL_08_T                            pe1_drc_ctrl_08;	//0xCC861300
	PE_O24_CC_PE1_DRC_CTRL_09_T                            pe1_drc_ctrl_09;	//0xCC861304
	PE_O24_CC_PE1_DRC_CTRL_10_T                            pe1_drc_ctrl_10;	//0xCC861308
	PE_O24_CC_PE1_DRC_CTRL_11_T                            pe1_drc_ctrl_11;	//0xCC86130C
	PE_O24_CC_PE1_DRC_CTRL_12_T                            pe1_drc_ctrl_12;	//0xCC861310
	PE_O24_CC_PE1_DRC_CTRL_13_T                            pe1_drc_ctrl_13;	//0xCC861314
	PE_O24_CC_PE1_DRC_CTRL_14_T                            pe1_drc_ctrl_14;	//0xCC861318
	PE_O24_CC_PE1_DRC_CTRL_15_T                            pe1_drc_ctrl_15;	//0xCC86131C
	PE_O24_CC_PE1_DRC_CTRL_16_T                            pe1_drc_ctrl_16;	//0xCC861320
	UINT32                                                   reserved67;	//0xCC861324
	UINT32                                                   reserved68;	//0xCC861328
	UINT32                                                   reserved69;	//0xCC86132C
	PE_O24_CC_PE1_DRC_CTRL_20_T                            pe1_drc_ctrl_20;	//0xCC861330
	PE_O24_CC_PE1_DRC_CTRL_21_T                            pe1_drc_ctrl_21;	//0xCC861334
	PE_O24_CC_PE1_DRC_CTRL_22_T                            pe1_drc_ctrl_22;	//0xCC861338
	PE_O24_CC_PE1_DRC_CTRL_23_T                            pe1_drc_ctrl_23;	//0xCC86133C
	PE_O24_CC_PE1_DRC_CTRL_24_T                            pe1_drc_ctrl_24;	//0xCC861340
	PE_O24_CC_PE1_DRC_CTRL_25_T                            pe1_drc_ctrl_25;	//0xCC861344
	PE_O24_CC_PE1_DRC_CTRL_26_T                            pe1_drc_ctrl_26;	//0xCC861348
	PE_O24_CC_PE1_DRC_CTRL_27_T                            pe1_drc_ctrl_27;	//0xCC86134C
	PE_O24_CC_PE1_DRC_CTRL_28_T                            pe1_drc_ctrl_28;	//0xCC861350
	PE_O24_CC_PE1_DRC_CTRL_29_T                            pe1_drc_ctrl_29;	//0xCC861354
	PE_O24_CC_PE1_DRC_CTRL_30_T                            pe1_drc_ctrl_30;	//0xCC861358
	UINT32                                                   reserved70;	//0xCC86135C
	UINT32                                                   reserved71;	//0xCC861360
	PE_O24_CC_PE1_DRC_CTRL_33_T                            pe1_drc_ctrl_33;	//0xCC861364
	PE_O24_CC_PE1_DRC_CTRL_34_T                            pe1_drc_ctrl_34;	//0xCC861368
	PE_O24_CC_PE1_DRC_CTRL_35_T                            pe1_drc_ctrl_35;	//0xCC86136C
	UINT32                                                   reserved72;	//0xCC861370
	UINT32                                                   reserved73;	//0xCC861374
	UINT32                                                   reserved74;	//0xCC861378
	UINT32                                                   reserved75;	//0xCC86137C
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_00_T                pe1_logo_l7sc_ctrl_00;	//0xCC861380
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_01_T                pe1_logo_l7sc_ctrl_01;	//0xCC861384
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_02_T                pe1_logo_l7sc_ctrl_02;	//0xCC861388
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_03_T                pe1_logo_l7sc_ctrl_03;	//0xCC86138C
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_04_T                pe1_logo_l7sc_ctrl_04;	//0xCC861390
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_05_T                pe1_logo_l7sc_ctrl_05;	//0xCC861394
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_06_T                pe1_logo_l7sc_ctrl_06;	//0xCC861398
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_07_T                pe1_logo_l7sc_ctrl_07;	//0xCC86139C
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_08_T                pe1_logo_l7sc_ctrl_08;	//0xCC8613A0
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_09_T                pe1_logo_l7sc_ctrl_09;	//0xCC8613A4
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_10_T                pe1_logo_l7sc_ctrl_10;	//0xCC8613A8
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_11_T                pe1_logo_l7sc_ctrl_11;	//0xCC8613AC
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_12_T                pe1_logo_l7sc_ctrl_12;	//0xCC8613B0
	PE_O24_CC_PE1_LOGO_L7SC_CTRL_13_T                pe1_logo_l7sc_ctrl_13;	//0xCC8613B4
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_00_T                pe1_logo_l3sc_ctrl_00;	//0xCC8613B8
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_01_T                pe1_logo_l3sc_ctrl_01;	//0xCC8613BC
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_02_T                pe1_logo_l3sc_ctrl_02;	//0xCC8613C0
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_03_T                pe1_logo_l3sc_ctrl_03;	//0xCC8613C4
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_04_T                pe1_logo_l3sc_ctrl_04;	//0xCC8613C8
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_05_T                pe1_logo_l3sc_ctrl_05;	//0xCC8613CC
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_06_T                pe1_logo_l3sc_ctrl_06;	//0xCC8613D0
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_07_T                pe1_logo_l3sc_ctrl_07;	//0xCC8613D4
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_08_T                pe1_logo_l3sc_ctrl_08;	//0xCC8613D8
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_09_T                pe1_logo_l3sc_ctrl_09;	//0xCC8613DC
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_10_T                pe1_logo_l3sc_ctrl_10;	//0xCC8613E0
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_11_T                pe1_logo_l3sc_ctrl_11;	//0xCC8613E4
	PE_O24_CC_PE1_LOGO_L3SC_CTRL_12_T                pe1_logo_l3sc_ctrl_12;	//0xCC8613E8
	PE_O24_CC_PE1_LOGO_STAT_00_T                          pe1_logo_stat_00;	//0xCC8613EC
	PE_O24_CC_PE1_LOGO_STAT_01_T                          pe1_logo_stat_01;	//0xCC8613F0
	PE_O24_CC_PE1_LOGO_STAT_02_T                          pe1_logo_stat_02;	//0xCC8613F4
	PE_O24_CC_PE1_LOGO_STAT_03_T                          pe1_logo_stat_03;	//0xCC8613F8
	UINT32                                                   reserved76;	//0xCC8613FC
	UINT32                                                   reserved77;	//0xCC861400
	UINT32                                                   reserved78;	//0xCC861404
	UINT32                                                   reserved79;	//0xCC861408
	UINT32                                                   reserved80;	//0xCC86140C
	PE_O24_CC_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC861410
	PE_O24_CC_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC861414
	PE_O24_CC_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC861418
	PE_O24_CC_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC86141C
	PE_O24_CC_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC861420
	PE_O24_CC_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC861424
	PE_O24_CC_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC861428
	PE_O24_CC_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC86142C
	PE_O24_CC_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC861430
	PE_O24_CC_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xCC861434
	PE_O24_CC_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xCC861438
	PE_O24_CC_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xCC86143C
	PE_O24_CC_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xCC861440
	PE_O24_CC_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xCC861444
	PE_O24_CC_PE1_EOTF_RSATUS_T                            pe1_eotf_rsatus;	//0xCC861448
	UINT32                                                   reserved81;	//0xCC86144C
	PE_O24_CC_PE1_LLLUT_E_IA_CTRL_T                    pe1_lllut_e_ia_ctrl;	//0xCC861450
	PE_O24_CC_PE1_LLLUT_E_IA_DATA_T                    pe1_lllut_e_ia_data;	//0xCC861454
	PE_O24_CC_PE1_LLLUT_O_IA_CTRL_T                    pe1_lllut_o_ia_ctrl;	//0xCC861458
	PE_O24_CC_PE1_LLLUT_O_IA_DATA_T                    pe1_lllut_o_ia_data;	//0xCC86145C
	PE_O24_CC_PE1_LLCORE_CTRL_00_T                      pe1_llcore_ctrl_00;	//0xCC861460
	PE_O24_CC_PE1_LLCORE_CTRL_01_T                      pe1_llcore_ctrl_01;	//0xCC861464
	PE_O24_CC_PE1_LLCORE_CTRL_02_T                      pe1_llcore_ctrl_02;	//0xCC861468
	PE_O24_CC_PE1_LLCORE_CTRL_03_T                      pe1_llcore_ctrl_03;	//0xCC86146C
	PE_O24_CC_PE1_LLCORE_CTRL_04_T                      pe1_llcore_ctrl_04;	//0xCC861470
	PE_O24_CC_PE1_LLCORE_CTRL_05_T                      pe1_llcore_ctrl_05;	//0xCC861474
	PE_O24_CC_PE1_LLCORE_CTRL_06_T                      pe1_llcore_ctrl_06;	//0xCC861478
	PE_O24_CC_PE1_LLCORE_CTRL_07_T                      pe1_llcore_ctrl_07;	//0xCC86147C
	PE_O24_CC_PE1_LLCORE_CTRL_08_T                      pe1_llcore_ctrl_08;	//0xCC861480
	PE_O24_CC_PE1_LLCORE_CTRL_09_T                      pe1_llcore_ctrl_09;	//0xCC861484
	PE_O24_CC_PE1_LLCORE_CTRL_10_T                      pe1_llcore_ctrl_10;	//0xCC861488
	PE_O24_CC_PE1_LLCORE_CTRL_11_T                      pe1_llcore_ctrl_11;	//0xCC86148C
	PE_O24_CC_PE1_LLCORE_CTRL_12_T                      pe1_llcore_ctrl_12;	//0xCC861490
	PE_O24_CC_PE1_LLCORE_CTRL_13_T                      pe1_llcore_ctrl_13;	//0xCC861494
	UINT32                                                   reserved82;	//0xCC861498
	UINT32                                                   reserved83;	//0xCC86149C
	PE_O24_CC_PE1_DCE_CTRL_10_T                            pe1_dce_ctrl_10;	//0xCC8614A0
	PE_O24_CC_PE1_DCE_CTRL_11_T                            pe1_dce_ctrl_11;	//0xCC8614A4
	PE_O24_CC_PE1_DCE_CTRL_12_T                            pe1_dce_ctrl_12;	//0xCC8614A8
	PE_O24_CC_PE1_HIST_WIN_SEL_T                          pe1_hist_win_sel;	//0xCC8614AC
	PE_O24_CC_PE1_DCE_HIST1_IA_CTRL_T                pe1_dce_hist1_ia_ctrl;	//0xCC8614B0
	PE_O24_CC_PE1_DCE_HIST1_IA_DATA1_T              pe1_dce_hist1_ia_data1;	//0xCC8614B4
	PE_O24_CC_PE1_DCE_HIST1_IA_DATA2_T              pe1_dce_hist1_ia_data2;	//0xCC8614B8
	PE_O24_CC_PE1_DCE_HIST2_IA_CTRL_T                pe1_dce_hist2_ia_ctrl;	//0xCC8614BC
	PE_O24_CC_PE1_DCE_HIST2_IA_DATA1_T              pe1_dce_hist2_ia_data1;	//0xCC8614C0
	PE_O24_CC_PE1_DCE_HIST2_IA_DATA2_T              pe1_dce_hist2_ia_data2;	//0xCC8614C4
	PE_O24_CC_PE1_DCE_HIST3_IA_CTRL_T                pe1_dce_hist3_ia_ctrl;	//0xCC8614C8
	PE_O24_CC_PE1_DCE_HIST3_IA_DATA1_T              pe1_dce_hist3_ia_data1;	//0xCC8614CC
	PE_O24_CC_PE1_DCE_HIST3_IA_DATA2_T              pe1_dce_hist3_ia_data2;	//0xCC8614D0
	UINT32                                                   reserved84;	//0xCC8614D4
	UINT32                                                   reserved85;	//0xCC8614D8
	UINT32                                                   reserved86;	//0xCC8614DC
	PE_O24_CC_PE1_WIN2_CTRL_09_T                          pe1_win2_ctrl_09;	//0xCC8614E0
	PE_O24_CC_PE1_WIN2_CTRL_10_T                          pe1_win2_ctrl_10;	//0xCC8614E4
	PE_O24_CC_PE1_WIN2_CTRL_11_T                          pe1_win2_ctrl_11;	//0xCC8614E8
	PE_O24_CC_PE1_WIN2_CTRL_12_T                          pe1_win2_ctrl_12;	//0xCC8614EC
	PE_O24_CC_PE1_WIN2_CTRL_13_T                          pe1_win2_ctrl_13;	//0xCC8614F0
	PE_O24_CC_PE1_WIN2_CTRL_14_T                          pe1_win2_ctrl_14;	//0xCC8614F4
	PE_O24_CC_PE1_WIN2_CTRL_15_T                          pe1_win2_ctrl_15;	//0xCC8614F8
	PE_O24_CC_PE1_WIN2_CTRL_16_T                          pe1_win2_ctrl_16;	//0xCC8614FC
	PE_O24_CC_PE1_WIN2_CTRL_17_T                          pe1_win2_ctrl_17;	//0xCC861500
	PE_O24_CC_PE1_WIN2_CTRL_18_T                          pe1_win2_ctrl_18;	//0xCC861504
	PE_O24_CC_PE1_WIN2_CTRL_19_T                          pe1_win2_ctrl_19;	//0xCC861508
	PE_O24_CC_PE1_WIN2_CTRL_20_T                          pe1_win2_ctrl_20;	//0xCC86150C
	PE_O24_CC_PE1_WIN2_CTRL_21_T                          pe1_win2_ctrl_21;	//0xCC861510
	PE_O24_CC_PE1_WIN2_CTRL_22_T                          pe1_win2_ctrl_22;	//0xCC861514
	PE_O24_CC_PE1_WIN2_CTRL_23_T                          pe1_win2_ctrl_23;	//0xCC861518
	PE_O24_CC_PE1_WIN2_CTRL_24_T                          pe1_win2_ctrl_24;	//0xCC86151C
	PE_O24_CC_PE1_WIN2_CTRL_25_T                          pe1_win2_ctrl_25;	//0xCC861520
	PE_O24_CC_PE1_WIN2_CTRL_26_T                          pe1_win2_ctrl_26;	//0xCC861524
	PE_O24_CC_PE1_WIN2_CTRL_27_T                          pe1_win2_ctrl_27;	//0xCC861528
	PE_O24_CC_PE1_WIN2_CTRL_28_T                          pe1_win2_ctrl_28;	//0xCC86152C
	PE_O24_CC_PE1_WIN2_CTRL_29_T                          pe1_win2_ctrl_29;	//0xCC861530
	PE_O24_CC_PE1_WIN2_CTRL_30_T                          pe1_win2_ctrl_30;	//0xCC861534
	PE_O24_CC_PE1_WIN2_CTRL_31_T                          pe1_win2_ctrl_31;	//0xCC861538
	PE_O24_CC_PE1_WIN2_CTRL_32_T                          pe1_win2_ctrl_32;	//0xCC86153C
	UINT32                                                   reserved87;	//0xCC861540
	UINT32                                                   reserved88;	//0xCC861544
	UINT32                                                   reserved89;	//0xCC861548
	UINT32                                                   reserved90;	//0xCC86154C
	PE_O24_CC_PCC_WINCTRL_00_T                              pcc_winctrl_00;	//0xCC861550
	PE_O24_CC_PCC_WINCTRL_01_T                              pcc_winctrl_01;	//0xCC861554
	PE_O24_CC_PCC_WINCTRL_02_T                              pcc_winctrl_02;	//0xCC861558
	PE_O24_CC_PCC_WINCTRL_03_T                              pcc_winctrl_03;	//0xCC86155C
	PE_O24_CC_PCC_WINCTRL_04_T                              pcc_winctrl_04;	//0xCC861560
	PE_O24_CC_PCC_WINCTRL_05_T                              pcc_winctrl_05;	//0xCC861564
	PE_O24_CC_PCC_WINCTRL_06_T                              pcc_winctrl_06;	//0xCC861568
	PE_O24_CC_PCC_WINCTRL_07_T                              pcc_winctrl_07;	//0xCC86156C
	PE_O24_CC_PCC_WINCTRL_08_T                              pcc_winctrl_08;	//0xCC861570
	PE_O24_CC_PCC_WINCTRL_09_T                              pcc_winctrl_09;	//0xCC861574
	PE_O24_CC_PCC_WINCTRL_10_T                              pcc_winctrl_10;	//0xCC861578
	PE_O24_CC_PCC_WINCTRL_11_T                              pcc_winctrl_11;	//0xCC86157C
	PE_O24_CC_PCC_WINCTRL_12_T                              pcc_winctrl_12;	//0xCC861580
	PE_O24_CC_PCC_WINCTRL_13_T                              pcc_winctrl_13;	//0xCC861584
	PE_O24_CC_PCC_WINCTRL_14_T                              pcc_winctrl_14;	//0xCC861588
	PE_O24_CC_PCC_WINCTRL_15_T                              pcc_winctrl_15;	//0xCC86158C
	PE_O24_CC_PCC_WINCTRL_16_T                              pcc_winctrl_16;	//0xCC861590
	PE_O24_CC_PCC_WINCTRL_17_T                              pcc_winctrl_17;	//0xCC861594
	PE_O24_CC_PCC_WINCTRL_18_T                              pcc_winctrl_18;	//0xCC861598
	PE_O24_CC_PCC_WINCTRL_19_T                              pcc_winctrl_19;	//0xCC86159C
	PE_O24_CC_PCC_WINCTRL_20_T                              pcc_winctrl_20;	//0xCC8615A0
}PE_CC_PE1_REG_O24_T;

typedef struct {
	PE_O24_CC2_PE1_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xCC861600
	PE_O24_CC2_PE1_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xCC861604
	PE_O24_CC2_PE1_VSPYC_CTRL_02_T                       pe1_vspyc_ctrl_02;	//0xCC861608
	PE_O24_CC2_PE1_VSPYC_CTRL_03_T                       pe1_vspyc_ctrl_03;	//0xCC86160C
	PE_O24_CC2_PE1_VSPYC_CTRL_04_T                       pe1_vspyc_ctrl_04;	//0xCC861610
	PE_O24_CC2_PE1_VSPYC_CTRL_05_T                       pe1_vspyc_ctrl_05;	//0xCC861614
	PE_O24_CC2_PE1_VSPYC_CTRL_06_T                       pe1_vspyc_ctrl_06;	//0xCC861618
	PE_O24_CC2_PE1_VSPYC_CTRL_07_T                       pe1_vspyc_ctrl_07;	//0xCC86161C
	PE_O24_CC2_PE1_VSPYC_CTRL_08_T                       pe1_vspyc_ctrl_08;	//0xCC861620
	PE_O24_CC2_PE1_VSPYC_CTRL_09_T                       pe1_vspyc_ctrl_09;	//0xCC861624
	UINT32                                                    reserved0;	//0xCC861628
	UINT32                                                    reserved1;	//0xCC86162C
	PE_O24_CC2_PE1_VSP_CC_CTRL_00_T                     pe1_vsp_cc_ctrl_00;	//0xCC861630
	UINT32                                                    reserved2;	//0xCC861634
	UINT32                                                    reserved3;	//0xCC861638
	UINT32                                                    reserved4;	//0xCC86163C
	UINT32                                                    reserved5;	//0xCC861640
	PE_O24_CC2_PE1_VSP_CC_CTRL_05_T                     pe1_vsp_cc_ctrl_05;	//0xCC861644
	UINT32                                                    reserved6;	//0xCC861648
	UINT32                                                    reserved7;	//0xCC86164C
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xCC861650
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xCC861654
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xCC861658
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xCC86165C
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xCC861660
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xCC861664
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xCC861668
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xCC86166C
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xCC861670
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xCC861674
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xCC861678
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xCC86167C
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xCC861680
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xCC861684
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xCC861688
	PE_O24_CC2_PE1_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xCC86168C
	UINT32                                                    reserved8;	//0xCC861690
	UINT32                                                    reserved9;	//0xCC861694
	UINT32                                                   reserved10;	//0xCC861698
	UINT32                                                   reserved11;	//0xCC86169C
	PE_O24_CC2_PE1_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xCC8616A0
	PE_O24_CC2_PE1_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xCC8616A4
	PE_O24_CC2_PE1_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xCC8616A8
	UINT32                                                   reserved12;	//0xCC8616AC
	PE_O24_CC2_PE1_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xCC8616B0
	PE_O24_CC2_PE1_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xCC8616B4
	PE_O24_CC2_PE1_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xCC8616B8
	UINT32                                                   reserved13;	//0xCC8616BC
	PE_O24_CC2_PE1_CW_CRGN_CTRL_00_T                   pe1_cw_crgn_ctrl_00;	//0xCC8616C0
	PE_O24_CC2_PE1_CW_CRGN_CTRL_01_T                   pe1_cw_crgn_ctrl_01;	//0xCC8616C4
	PE_O24_CC2_PE1_CW_CRGN_CTRL_02_T                   pe1_cw_crgn_ctrl_02;	//0xCC8616C8
	PE_O24_CC2_PE1_CW_CRGN_CTRL_03_T                   pe1_cw_crgn_ctrl_03;	//0xCC8616CC
	PE_O24_CC2_PE1_CW_CRGN_CTRL_04_T                   pe1_cw_crgn_ctrl_04;	//0xCC8616D0
	PE_O24_CC2_PE1_CW_CRGN_CTRL_05_T                   pe1_cw_crgn_ctrl_05;	//0xCC8616D4
	PE_O24_CC2_PE1_CW_CRGN_CTRL_06_T                   pe1_cw_crgn_ctrl_06;	//0xCC8616D8
	PE_O24_CC2_PE1_CW_CRGN_CTRL_07_T                   pe1_cw_crgn_ctrl_07;	//0xCC8616DC
	PE_O24_CC2_PE1_CW_CRGN_CTRL_08_T                   pe1_cw_crgn_ctrl_08;	//0xCC8616E0
	PE_O24_CC2_PE1_CW_CRGN_CTRL_09_T                   pe1_cw_crgn_ctrl_09;	//0xCC8616E4
	PE_O24_CC2_PE1_CW_CRGN_CTRL_10_T                   pe1_cw_crgn_ctrl_10;	//0xCC8616E8
	PE_O24_CC2_PE1_CW_CRGN_CTRL_11_T                   pe1_cw_crgn_ctrl_11;	//0xCC8616EC
	PE_O24_CC2_PE1_CW_CRGN_CTRL_12_T                   pe1_cw_crgn_ctrl_12;	//0xCC8616F0
	PE_O24_CC2_PE1_CW_CRGN_CTRL_13_T                   pe1_cw_crgn_ctrl_13;	//0xCC8616F4
	PE_O24_CC2_PE1_CW_CRGN_CTRL_14_T                   pe1_cw_crgn_ctrl_14;	//0xCC8616F8
	PE_O24_CC2_PE1_CW_CRGN_CTRL_15_T                   pe1_cw_crgn_ctrl_15;	//0xCC8616FC
	UINT32                                                   reserved14;	//0xCC861700
	UINT32                                                   reserved15;	//0xCC861704
	UINT32                                                   reserved16;	//0xCC861708
	UINT32                                                   reserved17;	//0xCC86170C
	PE_O24_CC2_PE1_LBLUR_CTRL_00_T                       pe1_lblur_ctrl_00;	//0xCC861710
	PE_O24_CC2_PE1_LBLUR_CTRL_01_T                       pe1_lblur_ctrl_01;	//0xCC861714
	PE_O24_CC2_PE1_LBLUR_CTRL_02_T                       pe1_lblur_ctrl_02;	//0xCC861718
	UINT32                                                   reserved18;	//0xCC86171C
	PE_O24_CC2_PE1_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0xCC861720
	PE_O24_CC2_PE1_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0xCC861724
	PE_O24_CC2_PE1_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0xCC861728
	PE_O24_CC2_PE1_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0xCC86172C
	PE_O24_CC2_PE1_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0xCC861730
	PE_O24_CC2_PE1_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0xCC861734
	PE_O24_CC2_PE1_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0xCC861738
	PE_O24_CC2_PE1_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0xCC86173C
	PE_O24_CC2_PE1_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0xCC861740
	PE_O24_CC2_PE1_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0xCC861744
	PE_O24_CC2_PE1_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0xCC861748
	PE_O24_CC2_PE1_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0xCC86174C
	PE_O24_CC2_PE1_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0xCC861750
	PE_O24_CC2_PE1_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0xCC861754
	PE_O24_CC2_PE1_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0xCC861758
	PE_O24_CC2_PE1_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0xCC86175C
	PE_O24_CC2_PE1_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0xCC861760
	PE_O24_CC2_PE1_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0xCC861764
	PE_O24_CC2_PE1_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0xCC861768
	PE_O24_CC2_PE1_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0xCC86176C
	PE_O24_CC2_PE1_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0xCC861770
	PE_O24_CC2_PE1_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0xCC861774
	PE_O24_CC2_PE1_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0xCC861778
	PE_O24_CC2_PE1_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0xCC86177C
	PE_O24_CC2_PE1_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0xCC861780
	PE_O24_CC2_PE1_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0xCC861784
	PE_O24_CC2_PE1_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0xCC861788
	PE_O24_CC2_PE1_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0xCC86178C
	PE_O24_CC2_PE1_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0xCC861790
	PE_O24_CC2_PE1_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0xCC861794
	PE_O24_CC2_PE1_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0xCC861798
	PE_O24_CC2_PE1_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0xCC86179C
	PE_O24_CC2_PE1_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0xCC8617A0
	PE_O24_CC2_PE1_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0xCC8617A4
	PE_O24_CC2_PE1_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0xCC8617A8
	PE_O24_CC2_PE1_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0xCC8617AC
	PE_O24_CC2_PE1_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0xCC8617B0
	PE_O24_CC2_PE1_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0xCC8617B4
	PE_O24_CC2_PE1_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0xCC8617B8
	PE_O24_CC2_PE1_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0xCC8617BC
	PE_O24_CC2_PE1_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0xCC8617C0
	PE_O24_CC2_PE1_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0xCC8617C4
	PE_O24_CC2_PE1_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0xCC8617C8
	PE_O24_CC2_PE1_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0xCC8617CC
	PE_O24_CC2_PE1_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0xCC8617D0
	PE_O24_CC2_PE1_LOGO_CTRL_45_T                         pe1_logo_ctrl_45;	//0xCC8617D4
	PE_O24_CC2_PE1_LOGO_CTRL_46_T                         pe1_logo_ctrl_46;	//0xCC8617D8
	PE_O24_CC2_PE1_LOGO_CTRL_47_T                         pe1_logo_ctrl_47;	//0xCC8617DC
	PE_O24_CC2_PE1_LOGO_CTRL_48_T                         pe1_logo_ctrl_48;	//0xCC8617E0
	UINT32                                                   reserved19;	//0xCC8617E4
	UINT32                                                   reserved20;	//0xCC8617E8
	UINT32                                                   reserved21;	//0xCC8617EC
	UINT32                                                   reserved22;	//0xCC8617F0
	PE_O24_CC2_PE1_LOGO_CTRL_53_T                         pe1_logo_ctrl_53;	//0xCC8617F4
	PE_O24_CC2_PE1_LOGO_CTRL_54_T                         pe1_logo_ctrl_54;	//0xCC8617F8
	PE_O24_CC2_PE1_LOGO_CTRL_55_T                         pe1_logo_ctrl_55;	//0xCC8617FC
	PE_O24_CC2_PE1_LOGO_CTRL_56_T                         pe1_logo_ctrl_56;	//0xCC861800
	PE_O24_CC2_PE1_LOGO_CTRL_57_T                         pe1_logo_ctrl_57;	//0xCC861804
	PE_O24_CC2_PE1_LOGO_CTRL_58_T                         pe1_logo_ctrl_58;	//0xCC861808
	PE_O24_CC2_PE1_LOGO_CTRL_59_T                         pe1_logo_ctrl_59;	//0xCC86180C
	PE_O24_CC2_PE1_LOGO_CTRL_60_T                         pe1_logo_ctrl_60;	//0xCC861810
	UINT32                                                   reserved23;	//0xCC861814
	UINT32                                                   reserved24;	//0xCC861818
	UINT32                                                   reserved25;	//0xCC86181C
	PE_O24_CC2_PE1_GSR_CTRL_00_T                           pe1_gsr_ctrl_00;	//0xCC861820
	PE_O24_CC2_PE1_GSR_CTRL_01_T                           pe1_gsr_ctrl_01;	//0xCC861824
	PE_O24_CC2_PE1_GSR_CTRL_02_T                           pe1_gsr_ctrl_02;	//0xCC861828
	PE_O24_CC2_PE1_GSR_CTRL_03_T                           pe1_gsr_ctrl_03;	//0xCC86182C
	PE_O24_CC2_PE1_GSR_CTRL_04_T                           pe1_gsr_ctrl_04;	//0xCC861830
	PE_O24_CC2_PE1_GSR_CTRL_05_T                           pe1_gsr_ctrl_05;	//0xCC861834
	PE_O24_CC2_PE1_GSR_CTRL_06_T                           pe1_gsr_ctrl_06;	//0xCC861838
	PE_O24_CC2_PE1_GSR_CTRL_07_T                           pe1_gsr_ctrl_07;	//0xCC86183C
	PE_O24_CC2_PE1_GSR_CTRL_08_T                           pe1_gsr_ctrl_08;	//0xCC861840
	PE_O24_CC2_PE1_GSR_CTRL_09_T                           pe1_gsr_ctrl_09;	//0xCC861844
	PE_O24_CC2_PE1_GSR_CTRL_10_T                           pe1_gsr_ctrl_10;	//0xCC861848
	PE_O24_CC2_PE1_GSR_CTRL_11_T                           pe1_gsr_ctrl_11;	//0xCC86184C
	PE_O24_CC2_PE1_GSR_CTRL_12_T                           pe1_gsr_ctrl_12;	//0xCC861850
	PE_O24_CC2_PE1_GSR_CTRL_13_T                           pe1_gsr_ctrl_13;	//0xCC861854
	PE_O24_CC2_PE1_GSR_CTRL_14_T                           pe1_gsr_ctrl_14;	//0xCC861858
	PE_O24_CC2_PE1_GSR_CTRL_15_T                           pe1_gsr_ctrl_15;	//0xCC86185C
	PE_O24_CC2_PE1_GSR_CTRL_16_T                           pe1_gsr_ctrl_16;	//0xCC861860
	PE_O24_CC2_PE1_GSR_CTRL_17_T                           pe1_gsr_ctrl_17;	//0xCC861864
	PE_O24_CC2_PE1_GSR_CTRL_18_T                           pe1_gsr_ctrl_18;	//0xCC861868
	PE_O24_CC2_PE1_GSR_CTRL_19_T                           pe1_gsr_ctrl_19;	//0xCC86186C
	PE_O24_CC2_PE1_GSR_CTRL_20_T                           pe1_gsr_ctrl_20;	//0xCC861870
	PE_O24_CC2_PE1_GSR_CTRL_21_T                           pe1_gsr_ctrl_21;	//0xCC861874
	PE_O24_CC2_PE1_GSR_CTRL_22_T                           pe1_gsr_ctrl_22;	//0xCC861878
	PE_O24_CC2_PE1_GSR_CTRL_23_T                           pe1_gsr_ctrl_23;	//0xCC86187C
	PE_O24_CC2_PE1_GSR_CTRL_24_T                           pe1_gsr_ctrl_24;	//0xCC861880
	PE_O24_CC2_PE1_GSR_CTRL_25_T                           pe1_gsr_ctrl_25;	//0xCC861884
	PE_O24_CC2_PE1_GSR_CTRL_26_T                           pe1_gsr_ctrl_26;	//0xCC861888
	PE_O24_CC2_PE1_GSR_CTRL_27_T                           pe1_gsr_ctrl_27;	//0xCC86188C
	PE_O24_CC2_PE1_GSR_CTRL_28_T                           pe1_gsr_ctrl_28;	//0xCC861890
	PE_O24_CC2_PE1_GSR_CTRL_29_T                           pe1_gsr_ctrl_29;	//0xCC861894
	PE_O24_CC2_PE1_GSR_CTRL_30_T                           pe1_gsr_ctrl_30;	//0xCC861898
	PE_O24_CC2_PE1_GSR_CTRL_31_T                           pe1_gsr_ctrl_31;	//0xCC86189C
	PE_O24_CC2_PE1_GSR_CTRL_32_T                           pe1_gsr_ctrl_32;	//0xCC8618A0
	PE_O24_CC2_PE1_GSR_CTRL_33_T                           pe1_gsr_ctrl_33;	//0xCC8618A4
	UINT32                                                   reserved26;	//0xCC8618A8
	UINT32                                                   reserved27;	//0xCC8618AC
	UINT32                                                   reserved28;	//0xCC8618B0
	UINT32                                                   reserved29;	//0xCC8618B4
	UINT32                                                   reserved30;	//0xCC8618B8
	UINT32                                                   reserved31;	//0xCC8618BC
	UINT32                                                   reserved32;	//0xCC8618C0
	UINT32                                                   reserved33;	//0xCC8618C4
	UINT32                                                   reserved34;	//0xCC8618C8
	UINT32                                                   reserved35;	//0xCC8618CC
	UINT32                                                   reserved36;	//0xCC8618D0
	UINT32                                                   reserved37;	//0xCC8618D4
	UINT32                                                   reserved38;	//0xCC8618D8
	UINT32                                                   reserved39;	//0xCC8618DC
	PE_O24_CC2_PE1_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xCC8618E0
	PE_O24_CC2_PE1_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xCC8618E4
	PE_O24_CC2_PE1_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xCC8618E8
	PE_O24_CC2_PE1_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xCC8618EC
	PE_O24_CC2_PE1_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xCC8618F0
	PE_O24_CC2_PE1_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xCC8618F4
	PE_O24_CC2_PE1_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xCC8618F8
	PE_O24_CC2_PE1_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xCC8618FC
	PE_O24_CC2_PE1_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xCC861900
	PE_O24_CC2_PE1_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xCC861904
	PE_O24_CC2_PE1_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xCC861908
	PE_O24_CC2_PE1_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xCC86190C
	PE_O24_CC2_PE1_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xCC861910
	PE_O24_CC2_PE1_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xCC861914
	PE_O24_CC2_PE1_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xCC861918
	PE_O24_CC2_PE1_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xCC86191C
	PE_O24_CC2_PE1_MUTE_CTRL_16_T                         pe1_mute_ctrl_16;	//0xCC861920
	PE_O24_CC2_PE1_MUTE_CTRL_17_T                         pe1_mute_ctrl_17;	//0xCC861924
	PE_O24_CC2_PE1_MUTE_CTRL_18_T                         pe1_mute_ctrl_18;	//0xCC861928
	PE_O24_CC2_PE1_MUTE_CTRL_19_T                         pe1_mute_ctrl_19;	//0xCC86192C
	PE_O24_CC2_PE1_MUTE_CTRL_20_T                         pe1_mute_ctrl_20;	//0xCC861930
	PE_O24_CC2_PE1_MUTE_CTRL_21_T                         pe1_mute_ctrl_21;	//0xCC861934
	PE_O24_CC2_PE1_MUTE_CTRL_22_T                         pe1_mute_ctrl_22;	//0xCC861938
	PE_O24_CC2_PE1_MUTE_CTRL_23_T                         pe1_mute_ctrl_23;	//0xCC86193C
	UINT32                                                   reserved40;	//0xCC861940
	UINT32                                                   reserved41;	//0xCC861944
	UINT32                                                   reserved42;	//0xCC861948
	UINT32                                                   reserved43;	//0xCC86194C
	UINT32                                                   reserved44;	//0xCC861950
	UINT32                                                   reserved45;	//0xCC861954
	UINT32                                                   reserved46;	//0xCC861958
	UINT32                                                   reserved47;	//0xCC86195C
	UINT32                                                   reserved48;	//0xCC861960
	UINT32                                                   reserved49;	//0xCC861964
	UINT32                                                   reserved50;	//0xCC861968
	UINT32                                                   reserved51;	//0xCC86196C
	UINT32                                                   reserved52;	//0xCC861970
	UINT32                                                   reserved53;	//0xCC861974
	UINT32                                                   reserved54;	//0xCC861978
	UINT32                                                   reserved55;	//0xCC86197C
	UINT32                                                   reserved56;	//0xCC861980
	UINT32                                                   reserved57;	//0xCC861984
	UINT32                                                   reserved58;	//0xCC861988
	UINT32                                                   reserved59;	//0xCC86198C
	UINT32                                                   reserved60;	//0xCC861990
	UINT32                                                   reserved61;	//0xCC861994
	UINT32                                                   reserved62;	//0xCC861998
	UINT32                                                   reserved63;	//0xCC86199C
	UINT32                                                   reserved64;	//0xCC8619A0
	UINT32                                                   reserved65;	//0xCC8619A4
	UINT32                                                   reserved66;	//0xCC8619A8
	UINT32                                                   reserved67;	//0xCC8619AC
	UINT32                                                   reserved68;	//0xCC8619B0
	UINT32                                                   reserved69;	//0xCC8619B4
	UINT32                                                   reserved70;	//0xCC8619B8
	UINT32                                                   reserved71;	//0xCC8619BC
	UINT32                                                   reserved72;	//0xCC8619C0
	UINT32                                                   reserved73;	//0xCC8619C4
	UINT32                                                   reserved74;	//0xCC8619C8
	UINT32                                                   reserved75;	//0xCC8619CC
	UINT32                                                   reserved76;	//0xCC8619D0
	UINT32                                                   reserved77;	//0xCC8619D4
	UINT32                                                   reserved78;	//0xCC8619D8
	UINT32                                                   reserved79;	//0xCC8619DC
	UINT32                                                   reserved80;	//0xCC8619E0
	UINT32                                                   reserved81;	//0xCC8619E4
	UINT32                                                   reserved82;	//0xCC8619E8
	UINT32                                                   reserved83;	//0xCC8619EC
	UINT32                                                   reserved84;	//0xCC8619F0
	UINT32                                                   reserved85;	//0xCC8619F4
	UINT32                                                   reserved86;	//0xCC8619F8
	UINT32                                                   reserved87;	//0xCC8619FC
	PE_O24_CC2_PE1_LOGO_CTRL_61_T                         pe1_logo_ctrl_61;	//0xCC861A00
	PE_O24_CC2_PE1_LOGO_CTRL_62_T                         pe1_logo_ctrl_62;	//0xCC861A04
	PE_O24_CC2_PE1_LOGO_CTRL_63_T                         pe1_logo_ctrl_63;	//0xCC861A08
	PE_O24_CC2_PE1_LOGO_CTRL_64_T                         pe1_logo_ctrl_64;	//0xCC861A0C
	PE_O24_CC2_PE1_LOGO_CTRL_65_T                         pe1_logo_ctrl_65;	//0xCC861A10
	PE_O24_CC2_PE1_LOGO_CTRL_66_T                         pe1_logo_ctrl_66;	//0xCC861A14
	PE_O24_CC2_PE1_LOGO_CTRL_67_T                         pe1_logo_ctrl_67;	//0xCC861A18
	PE_O24_CC2_PE1_LOGO_CTRL_68_T                         pe1_logo_ctrl_68;	//0xCC861A1C
	PE_O24_CC2_PE1_LOGO_CTRL_69_T                         pe1_logo_ctrl_69;	//0xCC861A20
	PE_O24_CC2_PE1_LOGO_CTRL_70_T                         pe1_logo_ctrl_70;	//0xCC861A24
	PE_O24_CC2_PE1_LOGO_CTRL_71_T                         pe1_logo_ctrl_71;	//0xCC861A28
	PE_O24_CC2_PE1_LOGO_CTRL_72_T                         pe1_logo_ctrl_72;	//0xCC861A2C
	PE_O24_CC2_PE1_LOGO_CTRL_73_T                         pe1_logo_ctrl_73;	//0xCC861A30
	PE_O24_CC2_PE1_LOGO_CTRL_74_T                         pe1_logo_ctrl_74;	//0xCC861A34
	PE_O24_CC2_PE1_LOGO_CTRL_75_T                         pe1_logo_ctrl_75;	//0xCC861A38
	PE_O24_CC2_PE1_LOGO_CTRL_76_T                         pe1_logo_ctrl_76;	//0xCC861A3C
	PE_O24_CC2_PE1_LOGO_CTRL_77_T                         pe1_logo_ctrl_77;	//0xCC861A40
	PE_O24_CC2_PE1_LOGO_CTRL_78_T                         pe1_logo_ctrl_78;	//0xCC861A44
	PE_O24_CC2_PE1_LOGO_CTRL_79_T                         pe1_logo_ctrl_79;	//0xCC861A48
	PE_O24_CC2_PE1_LOGO_CTRL_80_T                         pe1_logo_ctrl_80;	//0xCC861A4C
	PE_O24_CC2_PE1_LOGO_CTRL_81_T                         pe1_logo_ctrl_81;	//0xCC861A50
	PE_O24_CC2_PE1_LOGO_CTRL_82_T                         pe1_logo_ctrl_82;	//0xCC861A54
	PE_O24_CC2_PE1_LOGO_CTRL_83_T                         pe1_logo_ctrl_83;	//0xCC861A58
	PE_O24_CC2_PE1_LOGO_CTRL_84_T                         pe1_logo_ctrl_84;	//0xCC861A5C
	PE_O24_CC2_PE1_LOGO_CTRL_85_T                         pe1_logo_ctrl_85;	//0xCC861A60
	PE_O24_CC2_PE1_LOGO_CTRL_86_T                         pe1_logo_ctrl_86;	//0xCC861A64
	PE_O24_CC2_PE1_LOGO_CTRL_87_T                         pe1_logo_ctrl_87;	//0xCC861A68
	PE_O24_CC2_PE1_LOGO_CTRL_88_T                         pe1_logo_ctrl_88;	//0xCC861A6C
	UINT32                                                   reserved88;	//0xCC861A70
	UINT32                                                   reserved89;	//0xCC861A74
	UINT32                                                   reserved90;	//0xCC861A78
	UINT32                                                   reserved91;	//0xCC861A7C
	UINT32                                                   reserved92;	//0xCC861A80
	UINT32                                                   reserved93;	//0xCC861A84
	UINT32                                                   reserved94;	//0xCC861A88
	UINT32                                                   reserved95;	//0xCC861A8C
	UINT32                                                   reserved96;	//0xCC861A90
	UINT32                                                   reserved97;	//0xCC861A94
	UINT32                                                   reserved98;	//0xCC861A98
	UINT32                                                   reserved99;	//0xCC861A9C
	PE_O24_CC2_PE1_MERGE_CTRL_00_T                       pe1_merge_ctrl_00;	//0xCC861AA0
	PE_O24_CC2_PE1_MERGE_CTRL_01_T                       pe1_merge_ctrl_01;	//0xCC861AA4
	PE_O24_CC2_PE1_MERGE_CTRL_02_T                       pe1_merge_ctrl_02;	//0xCC861AA8
	PE_O24_CC2_PE1_MERGE_CTRL_03_T                       pe1_merge_ctrl_03;	//0xCC861AAC
	PE_O24_CC2_PE1_MERGE_CTRL_04_T                       pe1_merge_ctrl_04;	//0xCC861AB0
	PE_O24_CC2_PE1_MERGE_CTRL_05_T                       pe1_merge_ctrl_05;	//0xCC861AB4
	PE_O24_CC2_PE1_MERGE_CTRL_06_T                       pe1_merge_ctrl_06;	//0xCC861AB8
	PE_O24_CC2_PE1_MERGE_CTRL_07_T                       pe1_merge_ctrl_07;	//0xCC861ABC
	PE_O24_CC2_PE1_MERGE_CTRL_08_T                       pe1_merge_ctrl_08;	//0xCC861AC0
	PE_O24_CC2_PE1_MERGE_CTRL_09_T                       pe1_merge_ctrl_09;	//0xCC861AC4
	PE_O24_CC2_PE1_MERGE_CTRL_10_T                       pe1_merge_ctrl_10;	//0xCC861AC8
	PE_O24_CC2_PE1_MERGE_CTRL_11_T                       pe1_merge_ctrl_11;	//0xCC861ACC
	PE_O24_CC2_PE1_MERGE_CTRL_12_T                       pe1_merge_ctrl_12;	//0xCC861AD0
	PE_O24_CC2_PE1_MERGE_CTRL_13_T                       pe1_merge_ctrl_13;	//0xCC861AD4
	PE_O24_CC2_PE1_MERGE_CTRL_14_T                       pe1_merge_ctrl_14;	//0xCC861AD8
	PE_O24_CC2_PE1_MERGE_CTRL_15_T                       pe1_merge_ctrl_15;	//0xCC861ADC
	PE_O24_CC2_PE1_MERGE_CTRL_16_T                       pe1_merge_ctrl_16;	//0xCC861AE0
	PE_O24_CC2_PE1_MERGE_CTRL_17_T                       pe1_merge_ctrl_17;	//0xCC861AE4
	PE_O24_CC2_PE1_MERGE_CTRL_18_T                       pe1_merge_ctrl_18;	//0xCC861AE8
	PE_O24_CC2_PE1_MERGE_CTRL_19_T                       pe1_merge_ctrl_19;	//0xCC861AEC
	PE_O24_CC2_PE1_MERGE_CTRL_20_T                       pe1_merge_ctrl_20;	//0xCC861AF0
	PE_O24_CC2_PE1_MERGE_CTRL_21_T                       pe1_merge_ctrl_21;	//0xCC861AF4
	PE_O24_CC2_PE1_MERGE_CTRL_22_T                       pe1_merge_ctrl_22;	//0xCC861AF8
	PE_O24_CC2_PE1_MERGE_CTRL_23_T                       pe1_merge_ctrl_23;	//0xCC861AFC
	PE_O24_CC2_PE1_MERGE_CTRL_24_T                       pe1_merge_ctrl_24;	//0xCC861B00
	PE_O24_CC2_PE1_MERGE_CTRL_25_T                       pe1_merge_ctrl_25;	//0xCC861B04
	PE_O24_CC2_PE1_MERGE_CTRL_26_T                       pe1_merge_ctrl_26;	//0xCC861B08
	PE_O24_CC2_PE1_MERGE_CTRL_27_T                       pe1_merge_ctrl_27;	//0xCC861B0C
	PE_O24_CC2_PE1_MERGE_CTRL_28_T                       pe1_merge_ctrl_28;	//0xCC861B10
	PE_O24_CC2_PE1_MERGE_CTRL_29_T                       pe1_merge_ctrl_29;	//0xCC861B14
	PE_O24_CC2_PE1_MERGE_CTRL_30_T                       pe1_merge_ctrl_30;	//0xCC861B18
	PE_O24_CC2_PE1_MERGE_CTRL_31_T                       pe1_merge_ctrl_31;	//0xCC861B1C
	PE_O24_CC2_PE1_MERGE_CTRL_32_T                       pe1_merge_ctrl_32;	//0xCC861B20
	PE_O24_CC2_PE1_MERGE_CTRL_33_T                       pe1_merge_ctrl_33;	//0xCC861B24
	PE_O24_CC2_PE1_MERGE_CTRL_34_T                       pe1_merge_ctrl_34;	//0xCC861B28
	PE_O24_CC2_PE1_MERGE_CTRL_35_T                       pe1_merge_ctrl_35;	//0xCC861B2C
	PE_O24_CC2_PE1_MERGE_CTRL_36_T                       pe1_merge_ctrl_36;	//0xCC861B30
	PE_O24_CC2_PE1_MERGE_CTRL_37_T                       pe1_merge_ctrl_37;	//0xCC861B34
	PE_O24_CC2_PE1_MERGE_CTRL_38_T                       pe1_merge_ctrl_38;	//0xCC861B38
	PE_O24_CC2_PE1_MERGE_CTRL_39_T                       pe1_merge_ctrl_39;	//0xCC861B3C
	PE_O24_CC2_PE1_MERGE_CTRL_40_T                       pe1_merge_ctrl_40;	//0xCC861B40
	PE_O24_CC2_PE1_MERGE_CTRL_41_T                       pe1_merge_ctrl_41;	//0xCC861B44
	PE_O24_CC2_PE1_MERGE_CTRL_42_T                       pe1_merge_ctrl_42;	//0xCC861B48
	PE_O24_CC2_PE1_MERGE_CTRL_43_T                       pe1_merge_ctrl_43;	//0xCC861B4C
	PE_O24_CC2_PE1_MERGE_CTRL_44_T                       pe1_merge_ctrl_44;	//0xCC861B50
	PE_O24_CC2_PE1_MERGE_CTRL_45_T                       pe1_merge_ctrl_45;	//0xCC861B54
	PE_O24_CC2_PE1_MERGE_CTRL_46_T                       pe1_merge_ctrl_46;	//0xCC861B58
	PE_O24_CC2_PE1_MERGE_CTRL_47_T                       pe1_merge_ctrl_47;	//0xCC861B5C
	PE_O24_CC2_PE1_MERGE_CTRL_48_T                       pe1_merge_ctrl_48;	//0xCC861B60
	PE_O24_CC2_PE1_MERGE_CTRL_49_T                       pe1_merge_ctrl_49;	//0xCC861B64
	PE_O24_CC2_PE1_MERGE_CTRL_50_T                       pe1_merge_ctrl_50;	//0xCC861B68
	PE_O24_CC2_PE1_MERGE_CTRL_51_T                       pe1_merge_ctrl_51;	//0xCC861B6C
	PE_O24_CC2_PE1_MERGE_CTRL_52_T                       pe1_merge_ctrl_52;	//0xCC861B70
	PE_O24_CC2_PE1_MERGE_CTRL_53_T                       pe1_merge_ctrl_53;	//0xCC861B74
	PE_O24_CC2_PE1_MERGE_CTRL_54_T                       pe1_merge_ctrl_54;	//0xCC861B78
	PE_O24_CC2_PE1_MERGE_CTRL_55_T                       pe1_merge_ctrl_55;	//0xCC861B7C
	PE_O24_CC2_PE1_MERGE_CTRL_56_T                       pe1_merge_ctrl_56;	//0xCC861B80
	PE_O24_CC2_PE1_MERGE_CTRL_57_T                       pe1_merge_ctrl_57;	//0xCC861B84
	PE_O24_CC2_PE1_MERGE_CTRL_58_T                       pe1_merge_ctrl_58;	//0xCC861B88
	PE_O24_CC2_PE1_MERGE_CTRL_59_T                       pe1_merge_ctrl_59;	//0xCC861B8C
	PE_O24_CC2_PE1_MERGE_CTRL_60_T                       pe1_merge_ctrl_60;	//0xCC861B90
	PE_O24_CC2_PE1_MERGE_CTRL_61_T                       pe1_merge_ctrl_61;	//0xCC861B94
	PE_O24_CC2_PE1_MERGE_CTRL_62_T                       pe1_merge_ctrl_62;	//0xCC861B98
	PE_O24_CC2_PE1_MERGE_CTRL_63_T                       pe1_merge_ctrl_63;	//0xCC861B9C
	PE_O24_CC2_PE1_MERGE_CTRL_64_T                       pe1_merge_ctrl_64;	//0xCC861BA0
	PE_O24_CC2_PE1_MERGE_CTRL_65_T                       pe1_merge_ctrl_65;	//0xCC861BA4
	PE_O24_CC2_PE1_MERGE_CTRL_66_T                       pe1_merge_ctrl_66;	//0xCC861BA8
	PE_O24_CC2_PE1_MERGE_CTRL_67_T                       pe1_merge_ctrl_67;	//0xCC861BAC
	PE_O24_CC2_PE1_MERGE_CTRL_68_T                       pe1_merge_ctrl_68;	//0xCC861BB0
	PE_O24_CC2_PE1_MERGE_CTRL_69_T                       pe1_merge_ctrl_69;	//0xCC861BB4
	PE_O24_CC2_PE1_MERGE_CTRL_70_T                       pe1_merge_ctrl_70;	//0xCC861BB8
	PE_O24_CC2_PE1_MERGE_CTRL_71_T                       pe1_merge_ctrl_71;	//0xCC861BBC
	PE_O24_CC2_PE1_MERGE_CTRL_72_T                       pe1_merge_ctrl_72;	//0xCC861BC0
	PE_O24_CC2_PE1_MERGE_CTRL_73_T                       pe1_merge_ctrl_73;	//0xCC861BC4
	PE_O24_CC2_PE1_MERGE_CTRL_74_T                       pe1_merge_ctrl_74;	//0xCC861BC8
}PE_CC2_PE1_REG_O24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862300 RW 0x0000_0000
		UINT32				mRunStat	: 4;	// [0:3]	Main Status
		UINT32				mInfo		: 10;	// [4:13]	Main Info
		UINT32				sInfo		: 10;	// [14:23]	Sub Info
		UINT32				dbReq		: 4;	// [24:27]	DB Request
		UINT32				sRunStat	: 4;	// [28:31]	Sub Status
	};
}PE_O24_CCO_VERI_F22_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862304 RW 0x0000_0000
	UINT32 posd_w                   :16;	//15:0	//
	UINT32 posd_h                   :16;	//31:16	//
	};
}PE_O24_CCO_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862308 RW 0x0000_0000
	UINT32 bFbdevInitDone               :1;	//0:0
	UINT32 reserved0					:3;	//3:1
	UINT32 bOsdVReverseOn               :1;	//4:4
	UINT32 reserved1					:3;	//7:5
	UINT32 bEStreamerOn                 :1;	//8:8
	UINT32 reserved2					:3;	//11:9
	UINT32 bFw4KOSDOn                   :1;	//12:12
	UINT32 reserved3                    :19;	//31:13
	};
}PE_O24_OSDINFO_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86230C RW 0x0000_0000
	UINT32 bFwOsdOrbitInitDone          :1;	//0:0
	UINT32 reserved0					:3;	//3:1
	UINT32 bFwOsdSrInitDone             :1;	//4:4
	UINT32 reserved1					:27;	//31:5
	};
}PE_O24_OSDINFO_FW_TO_DRIVER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862310 RW 0x0000_0000
	UINT32 update                   :1;		//(0:0,RW,0x0000_0000) //
	UINT32 reserved                 :31;	//(31:1,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_WCG_UPDATE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862314 RW 0x0000_0000
	UINT32 retention_risk_second            :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_SYS_VERI_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862318 RW 0x0000_0000
	UINT32 head_apl                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 body_apl                   :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_SYS_VERI_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86231C RW 0x0000_0000
	UINT32 head_map                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 depth_map                  :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_SYS_VERI_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862320 RW 0x0000_0000
	UINT32 contrast                   :16;	//(15:0,RW,0x0000_0000) //
	UINT32 brightness                 :16;	//(31:16,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_SYS_VERI_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862324 RW 0x0000_0000
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
}PE_O24_CCO_VERI_SYS_VERI_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862328 RW 0x0000_0000
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
}PE_O24_CCO_VERI_SYS_VERI_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86232C RW 0x0000_0000
	UINT32 frate_in							:8;		//(7:0)		input frame rate
	UINT32 frate_out  		                :8;		//(15:8)	output frame rate
	UINT32 frate_vrr  		                :16;	//(31:16)	vrr input frame rate
	};
}PE_O24_CCO_VERI_SYS_VERI_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862330 RW 0x0000_0000
	UINT32 xoffset					:16; //  0:15
	UINT32 enable					:1;   // 16:16 
	UINT32 yoffset					:15;    // 17:31
	};
}PE_O24_ESTINFO0_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862334 RW 0x0000_0000
	UINT32 crop_x                   :16;	// 0:15
	UINT32 crop_y					:16;	// 31:16
	};
}PE_O24_ESTINFO1_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862338 RW 0x0000_0000
	UINT32 crop_w					:16;	// 0:15
	UINT32 crop_h					:16;	// 31:16
	};
}PE_O24_ESTINFO2_DRIVER_TO_FW_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86233C RW 0x0000_0000
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
}PE_O24_CCO_VERI_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862340 RW 0x0000_0000
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862344 RW 0x0000_0000
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862348 RW 0x0000_0000
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86234C RW 0x0000_0000
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862350 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x0        :16;	//
	UINT32 chroma_face_alpha_lut1_x1        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862354 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_x2        :16;	//
	UINT32 chroma_face_alpha_lut1_x3        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862358 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y0        :16;	//
	UINT32 chroma_face_alpha_lut1_y1        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86235C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut1_y2        :16;	//
	UINT32 chroma_face_alpha_lut1_y3        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862360 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x0        :16;	//
	UINT32 chroma_face_alpha_lut2_x1        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862364 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_x2        :16;	//
	UINT32 chroma_face_alpha_lut2_x3        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862368 RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y0        :16;	//
	UINT32 chroma_face_alpha_lut2_y1        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86236C RW 0x0000_0000
	UINT32 chroma_face_alpha_lut2_y2        :16;	//
	UINT32 chroma_face_alpha_lut2_y3        :16;	//
	};
}PE_O24_CCO_VERI_SYS_VERI_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862370 RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x0              :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CCO_VERI_SYS_VERI_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862374 RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_y0              :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CCO_VERI_SYS_VERI_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862378 RW 0x0000_0000
	UINT32 reg_irr_info                  	:32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O24_CCO_VERI_SYS_VERI_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86237C RW 0x0000_0000
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862380 RW 0x0000_0000
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862384 RW 0x0000_0000
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862388 RW 0x0000_0000
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}PE_O24_CCO_VERI_SYS_VERI_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86238C RW 0x0000_0000
	UINT32 phdr_pat_sat_lut_x7              :8;	//(7:0,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x6              :8;	//(15:8,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x5              :8;	//(23:16,NA,0x0) //
	UINT32 phdr_pat_sat_lut_x4              :8;	//(31:24,NA,0x0) //
	};
}PE_O24_CCO_VERI_SYS_VERI_35_T;

typedef struct {
	PE_O24_CCO_VERI_F22_STATUS_T                                f22_status;	//0xCC862300
	PE_O24_CCO_VERI_SYS_VERI_1_T                                   posd_wh;	//0xCC862304
	PE_O24_OSDINFO_DRIVER_TO_FW_T                     osdinfo_driver_to_fw;	//0xCC862308
	PE_O24_OSDINFO_FW_TO_DRIVER_T                     osdinfo_fw_to_driver;	//0xCC86230C
	PE_O24_CCO_VERI_WCG_UPDATE_T                                wcg_update;	//0xCC862310
	PE_O24_CCO_VERI_SYS_VERI_5_T                     retention_risk_second;	//0xCC862314
	PE_O24_CCO_VERI_SYS_VERI_6_T                             apl_upload_db;	//0xCC862318
	PE_O24_CCO_VERI_SYS_VERI_7_T                         map_apl_upload_db;	//0xCC86231C
	PE_O24_CCO_VERI_SYS_VERI_8_T                     contast_brightness_db;	//0xCC862320
	PE_O24_CCO_VERI_SYS_VERI_9_T                            dc_chroma_gain;	//0xCC862324
	PE_O24_CCO_VERI_SYS_VERI_10_T                         video_delay_sts0;	//0xCC862328
	PE_O24_CCO_VERI_SYS_VERI_11_T                         video_delay_sts1;	//0xCC86232C
	PE_O24_ESTINFO0_DRIVER_TO_FW_T                   estinfo0_driver_to_fw;	//0xCC862330
	PE_O24_ESTINFO1_DRIVER_TO_FW_T                   estinfo1_driver_to_fw;	//0xCC862334
	PE_O24_ESTINFO2_DRIVER_TO_FW_T                   estinfo2_driver_to_fw;	//0xCC862338
	PE_O24_CCO_VERI_PE_PCC_CTRL_T                              pe_pcc_ctrl;	//0xCC86233C
	PE_O24_CCO_VERI_SYS_VERI_16_T                          sat_phdr_gain_0;	//0xCC862340
	PE_O24_CCO_VERI_SYS_VERI_17_T                          sat_phdr_gain_1;	//0xCC862344
	PE_O24_CCO_VERI_SYS_VERI_18_T                          sat_phdr_gain_2;	//0xCC862348
	PE_O24_CCO_VERI_SYS_VERI_19_T                          sat_phdr_gain_3;	//0xCC86234C
	PE_O24_CCO_VERI_SYS_VERI_20_T                          acc_face_area_0;	//0xCC862350
	PE_O24_CCO_VERI_SYS_VERI_21_T                          acc_face_area_1;	//0xCC862354
	PE_O24_CCO_VERI_SYS_VERI_22_T                          acc_face_area_2;	//0xCC862358
	PE_O24_CCO_VERI_SYS_VERI_23_T                          acc_face_area_3;	//0xCC86235C
	PE_O24_CCO_VERI_SYS_VERI_24_T                          acc_face_area_4;	//0xCC862360
	PE_O24_CCO_VERI_SYS_VERI_25_T                          acc_face_area_5;	//0xCC862364
	PE_O24_CCO_VERI_SYS_VERI_26_T                          acc_face_area_6;	//0xCC862368
	PE_O24_CCO_VERI_SYS_VERI_27_T                          acc_face_area_7;	//0xCC86236C
	PE_O24_CCO_VERI_SYS_VERI_28_T                          sat_phdr_gain_8;	//0xCC862370
	PE_O24_CCO_VERI_SYS_VERI_29_T                          sat_phdr_gain_9;	//0xCC862374
	PE_O24_CCO_VERI_SYS_VERI_30_T                             reg_irr_info;	//0xCC862378
	PE_O24_CCO_VERI_SYS_VERI_31_T                          sat_phdr_gain_4;	//0xCC86237C
	PE_O24_CCO_VERI_SYS_VERI_32_T                          sat_phdr_gain_5;	//0xCC862380
	PE_O24_CCO_VERI_SYS_VERI_33_T                              sys_veri_33;	//0xCC862384
	PE_O24_CCO_VERI_SYS_VERI_34_T                              sys_veri_34;	//0xCC862388
	PE_O24_CCO_VERI_SYS_VERI_35_T                              sys_veri_35;	//0xCC86238C
}PE_CCO_VERI_REG_O24_T;



typedef union {
	UINT32 udata32;
	struct {						//0xCC862100 RW 0x0F00_0870
	UINT32 reg_hei                          :12;	//(11:0,RW,0x870) //
	UINT32 resvd0                           :1;
	UINT32 reg_mode_2ch                     :1;	//(13,RW,0x0) //
	UINT32 dither_temporal_en               :1;	//(14,RW,0x0) //
	UINT32 dither_en                        :1;	//(15,RW,0x0) //input dither enable for 11b -> 10b	processing order: (input dither: dither_en) --> (11b -> 10b : reg_decon_in_bit_opt)
	UINT32 reg_wid                          :12;	//(27:16,RW,0xF00) //
	UINT32 resvd1                           :1;
	UINT32 reg_decon_out_bit_opt            :1;	//(29,RW,0x0) //1: [10:0] , 0: {1'b0, [10:1]}
	UINT32 reg_decon_in_bit_opt             :1;	//(30,RW,0x0) //11b -> 10b ( 1: [10:1] , 0: [9:0] )	should be 1 when dither_en = 1
	UINT32 reg_decon_detour_en              :1;	//(31,RW,0x0) //1: detour
	};
}PE_CCO_DECON_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862104 RW 0x0000_0000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//(1,RW,0x0) //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //(not used in m16p3), 11b mode에서 10b 입력시, 켜야 됨.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align 안 맞음)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //0: 12-bit full	1: 1st_out_rd 입력 /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862108 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86210C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862110 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862114 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862118 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86211C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862120 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_2nd_out_rd_bit               :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_2nd_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_out_rd_on                :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862124 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862128 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86212C RW 0x0000_0000
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862130 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862134 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862138 RW 0x0000_0000
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86213C RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862140 RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862144 RW 0x0000_0000
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862148 RW 0x0000_0000
	UINT32 reg_blur_lb_var_cut_res          :4;	//(3:0,RW,0x0) //>> reg
	UINT32 resvd                            :2;
	UINT32 reg_blur_lb_var_en               :1;	//(6,RW,0x0) //
	UINT32 reg_l6_var_2x2_bit               :1;	//(7,RW,0x0) //1: [11:2], 0: [9:0] (w/ clipping)
	UINT32 reg_force_block_v                :6;	//(13:8,RW,0x0) //
	UINT32 reg_1st_debug_en                 :1;	//(14,RW,0x0) //
	UINT32 reg_l6_var_csc_en                :1;	//(15,RW,0x0) //ND에선 사용 안 함
	UINT32 reg_force_block_no_h             :6;	//(21:16,RW,0x0) //
	UINT32 reg_4k_5x3_mode_en               :1;	//(22,RW,0x0) //0: 5x5(u2, u1, cc, d1, d2) , 1: 5x5 repeat (u1, u1, cc, d1, d1)
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_rd_clip                      :1;	//(24,RW,0x0) //11b mode에서 10b 입력시, 켜야 됨.
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x0) //default = '0', not used in m16p3
	UINT32 reg_1st_debug_mode               :4;	//(29:26,RW,0x0) //0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: aux_luma	15: input_blur
	UINT32 reg_force_block_no_en            :1;	//(30,RW,0x0) //
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86214C RW 0x0000_0000
	UINT32 reg_var_chroma_en                :1;	//(0,RW,0x0) //
	UINT32 reg_low_gain_en                  :1;	//(1,RW,0x0) //O24 New	Low gain(var, diff, var, aux_luma) enable	Debug mode is same
	UINT32 reg_blur_final_size              :1;	//(2,RW,0x0) //0: new_2x2, 1: new_3x3
	UINT32 resvd0                           :1;
	UINT32 reg_blur_div_zero                :1;	//(4,RW,0x0) //0: L6, 1: curr_avg
	UINT32 reg_diff_hblur                   :2;	//(6:5,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_diff_vblur                   :2;	//(8:7,RW,0x0) //0: 1-tap , 1: 3-tap, 2: 5-tap
	UINT32 reg_motion_shft                  :3;	//(11:9,RW,0x0) //0: /8, 1: /4, 2: /2, 3: x1, 4: x2, 5: x4, 6: x8
	UINT32 reg_motion_en                    :1;	//(12,RW,0x0) //0: 255, 1: motion_gain
	UINT32 reg_led_10b_mode_blending        :1;	//(13,RW,0x0) //not used in O20
	UINT32 reg_led_10b_mode_diff_pel        :1;	//(14,RW,0x0) //not used in O20
	UINT32 resvd1                           :1;
	UINT32 reg_luma_bit_opt                 :1;	//(16,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_bit_opt                  :1;	//(17,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_var_bit_opt               :1;	//(18,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_l6_blur_bit_opt              :1;	//(19,RW,0x0) //0: lower 10bit w/ clipping, 1: higher 10bit
	UINT32 reg_var_v_gain                   :4;	//(23:20,RW,0x0) //
	UINT32 reg_var_h_gain                   :4;	//(27:24,RW,0x0) //
	UINT32 reg_var_cut_resolution           :4;	//(31:28,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862150 RW 0x0000_0000
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862154 RW 0x0000_0000
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x0) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x0) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862158 RW 0x0000_0000
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86215C RW 0x0000_0000
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862160 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862164 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862168 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86216C RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862170 RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862174 RW 0x0000_0000
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
}PE_CCO_DEC_SYNC_2DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862178 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86217C RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862180 RW 0x00020002
	UINT32 reg_ctrl_sync_actv_dly_7         :32;	//(31:0,RW,0x00020002) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862184 RW 0x00020002
	UINT32 reg_ctrl_sync_actv_dly_8         :32;	//(31:0,RW,0x00020002) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862188 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}PE_CCO_DEC_SYNC_2DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86218C RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}PE_CCO_DEC_SYNC_2DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862190 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862194 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862198 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86219C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621A4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621A8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621AC RW 0x0003_0002
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621B0 RW 0x0003_0002
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621B4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DEC_SYNC_3DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621BC RW 0x0000_0000
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621C0 RW 0x0000_0000
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621C4 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621C8 RW 0x0000_0000
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621CC RW 0x0000_0000
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x0) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621D0 RW 0x0000_0000
	UINT32 reg_block_size_v                 :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_block_size_h                 :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_block_no_v                   :6;	//(21:16,RW,0x0) //
	UINT32 resvd2                           :2;
	UINT32 reg_block_no_h                   :6;	//(29:24,RW,0x0) //
	UINT32 resvd3                           :1;
	UINT32 reg_block_info_force_en          :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621D4 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 reg_last_block_size_h            :7;	//(14:8,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_diff_mul_new                 :4;	//(19:16,RW,0x0) //
	UINT32 reg_diff_shift                   :3;	//(22:20,RW,0x0) //
	UINT32 reg_osd_run_mode                 :1;	//(23,RW,0x0) //
	UINT32 reg_alpha_blur_l6_var_sm         :1;	//(24,RW,0x0) //
	UINT32 reg_alpha_blur_mode              :2;	//(26:25,RW,0x0) //0: 1x1 blur, 1: 5x1 blur, 2: 9x1 blur, 3: use L6_var (not used in M16P3)
	UINT32 reg_blending_alpha_use_l6_var    :2;	//(28:27,RW,0x0) //
	UINT32 reg_diff_use_seldiff             :1;	//(29,RW,0x0) //
	UINT32 reg_diff_calc_mode               :2;	//(31:30,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621D8 RW 0x0000_0000
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x0) //
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x0) //
	UINT32 reg_lb_var_cut_res               :4;	//(23:20,RW,0x0) //
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621DC RW 0x0000_0000
	UINT32 reg_l6_var_x_th2                 :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_x_th1                 :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_x_th0                 :10;	//(29:20,RW,0x0) //
	UINT32 reg_lb_var_opt                   :1;	//(30,RW,0x0) //
	UINT32 reg_lb_var_en                    :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621E0 RW 0x0000_0000
	UINT32 reg_l6_var_y_th1                 :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_y_th0                 :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_x_th3                 :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621E4 RW 0x0000_0000
	UINT32 reg_l6_var_y_th3                 :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_y_th2                 :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_pel_trunc                 :2;	//(21:20,RW,0x0) //
	UINT32 reg_var_v_cut                    :2;	//(23:22,RW,0x0) //
	UINT32 reg_var_h_cut                    :2;	//(25:24,RW,0x0) //
	UINT32 reg_var_t7_offset                :2;	//(27:26,RW,0x0) //
	UINT32 reg_decon_rd_simple_bit          :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_simple_on           :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621E8 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621EC RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621F0 RW 0x0000_0000
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621F4 RW 0x0000_0000
	UINT32 reg_rd_min_pel_cb                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_min_pel_yy                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//(30:28,RW,0x0) //
	UINT32 reg_decon_rd_on                  :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621F8 RW 0x0000_0000
	UINT32 reg_rd_max_pel_yy                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_min_pel_cr                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8621FC RW 0x0000_0000
	UINT32 reg_rd_max_pel_cr                :12;	//(11:0,RW,0x0) //
	UINT32 reg_rd_max_pel_cb                :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862200 RW 0x0000_0000
	UINT32 reg_rd_init_yy                   :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862204 RW 0x0000_0000
	UINT32 reg_rd_init_cb                   :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862208 RW 0x0000_0000
	UINT32 reg_rd_init_cr                   :32;	//(31:0,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86220C RW 0x0000_0000
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862210 RW 0x0000_0000
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862214 RW 0x0000_0000
	UINT32 reg_bbd_y0                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x0                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_blur3_sim_en                 :1;	//(28,RW,0x0) //
	UINT32 reg_blur2_sim_en                 :1;	//(29,RW,0x0) //
	UINT32 reg_amf_lut_bit                  :1;	//(30,RW,0x0) //0: lower 8b, 1: higher 8b
	UINT32 reg_bbd_en                       :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862218 RW 0x0000_0000
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x0) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x0) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86221C RW 0x0000_0000
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862220 RW 0x0000_0000
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862224 RW 0x0000_0000
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862228 RW 0x0000_0000
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86222C RW 0x0000_0000
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862230 RW 0x0000_0000
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862234 RW 0x0000_0000
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862238 RW 0x0000_0000
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x0) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86223C RW 0x0000_0000
	UINT32 resvd                            :19;
	UINT32 reg_face_skin_opt                :1;	//(19,RW,0x0) //0: skin+face, 1: max(skin, face)
	UINT32 reg_face_master_gain             :8;	//(27:20,RW,0x0) //
	UINT32 reg_face_shft                    :2;	//(29:28,RW,0x0) //0: x1, 1: x2, 2: x4, 3: x8
	UINT32 reg_face_en                      :1;	//(30,RW,0x0) //
	UINT32 reg_skin_en                      :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862240 RW 0x0000_0000
	UINT32 reg_l6_var_diff_dist_h           :4;	//(3:0,RW,0x0) //
	UINT32 reg_l6_var_diff_dist_w           :4;	//(7:4,RW,0x0) //
	UINT32 resvd                            :24;
	};
}PE_CCO_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862244 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_cr            :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_cb            :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_yy            :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862248 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_yy3           :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_yy2           :10;	//(19:10,RW,0x0) //
	UINT32 resvd                            :12;
	};
}PE_CCO_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86224C RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862250 RW 0x0000_0000
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//(9:0,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//(31,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862254 RW 0x0000_0000
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//(7:0,RW,0x0) //
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862258 RW 0x0000_0000
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//(7:0,RW,0x0) //
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86225C RW 0x0000_0000
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//(15:8,RW,0x0) //
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//(23:16,RW,0x0) //
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//(31:24,RW,0x0) //
	};
}PE_CCO_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862260 RW 0x0000_0000
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_v_diff_th             :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862264 RW 0x0000_0000
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_h_diff_th             :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862268 RW 0x0000_0000
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_max_th     :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86226C RW 0x0000_0000
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_low_th     :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_CCO_DECON_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862270 RW 0x0000_0000
	UINT32 reg_2nd_rd_roi_cut_out           :2;	//(1:0,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_roi_cut_in            :2;	//(3:2,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_2nd_rd_luma_cut              :2;	//(9:8,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd0                           :16;
	UINT32 reg_2nd_rd_luma_en               :1;	//(28,NA,0x1) //0: 2nd_rd_luma off, 1: 2nd_rd_luma on
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x1) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd1                           :1;
	};
}PE_CCO_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862274 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}PE_CCO_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862278 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
}PE_CCO_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86227C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //2nd rd에도 동일하게 사용
	UINT32 resvd                            :12;
	};
}PE_CCO_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862280 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //2nd rd에도 동일하게 사용
	UINT32 resvd                            :12;
	};
}PE_CCO_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862284 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862288 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86228C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862290 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862294 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC862298 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //2nd rd에도 동일하게 사용
	UINT32 resvd1                           :10;
	};
}PE_CCO_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86229C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}PE_CCO_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622A4 RW 0x0000_0000
	UINT32 reg_2nd_var_x_th1                :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
}PE_CCO_DECON_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622A8 RW 0x0000_0000
	UINT32 reg_boundary_x_end               :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_boundary_x_start             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_boundary_side                :1;	//(30,NA,0x0) //0: left, 1: right
	UINT32 reg_boundary_en                  :1;	//(31,NA,0x0) //
	};
}PE_CCO_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622AC RW 0x0000_0000
	UINT32 reg_decon_low_diff_x_th0         :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th1         :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th2         :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_low_diff_x_th3         :8;	//(31:24,NA,0x0) //
	};
}PE_CCO_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622B0 RW 0x0000_0000
	UINT32 reg_decon_low_diff_y_th0         :8;	//(7:0,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th1         :8;	//(15:8,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th2         :8;	//(23:16,NA,0x0) //
	UINT32 reg_decon_low_diff_y_th3         :8;	//(31:24,NA,0x0) //
	};
}PE_CCO_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622B4 RW 0x0000_0000
	UINT32 reg_decon_low_var_x_th2          :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_x_th1          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_x_th0          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622B8 RW 0x0000_0000
	UINT32 reg_decon_low_var_y_th1          :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_y_th0          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_x_th3          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622BC RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th0         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_var_y_th3          :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_var_y_th2          :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622C0 RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th2         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th1         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622C4 RW 0x0000_0000
	UINT32 reg_decon_low_luma_x_th6         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th5         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th4         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622C8 RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th1         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th0         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_x_th7         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622CC RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th4         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th3         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th2         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622D0 RW 0x0000_0000
	UINT32 reg_decon_low_luma_y_th7         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th6         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_luma_y_th5         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622D4 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,NA,0x0) //
	UINT32 reg_low_aux_luma_en              :1;	//(30,NA,0x0) //
	UINT32 reg_aux_luma_en                  :1;	//(31,NA,0x0) //
	};
}PE_CCO_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622D8 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622DC RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622E0 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622E4 RW 0x0000_0000
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622E8 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th1     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th0     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622EC RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th4     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th3     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th2     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622F0 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_x_th7     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th6     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_x_th5     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622F4 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_y_th2     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th1     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th0     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622F8 RW 0x0000_0000
	UINT32 reg_decon_low_aux_luma_y_th5     :10;	//(9:0,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th4     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th3     :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}PE_CCO_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8622FC RW 0x0000_0000
	UINT32 reg_low_master_gain              :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_decon_low_aux_luma_y_th7     :10;	//(19:10,NA,0x0) //
	UINT32 reg_decon_low_aux_luma_y_th6     :10;	//(29:20,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}PE_CCO_DECON_CTRL_104_T;

typedef struct {
	PE_CCO_DECON_TOP_CTRL_T                   reg_decon_top_ctrl;	//0xCC862100
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
	PE_CCO_DEC_SYNC_2DLY_CTRL0_T         reg_dec_sync_2dly_ctrl0;	//0xCC862164
	PE_CCO_DEC_SYNC_2DLY_CTRL1_T         reg_dec_sync_2dly_ctrl1;	//0xCC862168
	PE_CCO_DEC_SYNC_2DLY_CTRL2_T         reg_dec_sync_2dly_ctrl2;	//0xCC86216C
	PE_CCO_DEC_SYNC_2DLY_CTRL3_T         reg_dec_sync_2dly_ctrl3;	//0xCC862170
	PE_CCO_DEC_SYNC_2DLY_CTRL4_T         reg_dec_sync_2dly_ctrl4;	//0xCC862174
	PE_CCO_DEC_SYNC_2DLY_CTRL5_T         reg_dec_sync_2dly_ctrl5;	//0xCC862178
	PE_CCO_DEC_SYNC_2DLY_CTRL6_T         reg_dec_sync_2dly_ctrl6;	//0xCC86217C
	PE_CCO_DEC_SYNC_2DLY_CTRL7_T         reg_dec_sync_2dly_ctrl7;	//0xCC862180
	PE_CCO_DEC_SYNC_2DLY_CTRL8_T         reg_dec_sync_2dly_ctrl8;	//0xCC862184
	PE_CCO_DEC_SYNC_2DLY_CTRL9_T         reg_dec_sync_2dly_ctrl9;	//0xCC862188
	PE_CCO_DEC_SYNC_2DLY_CTRLA_T         reg_dec_sync_2dly_ctrla;	//0xCC86218C
	PE_CCO_DEC_SYNC_3DLY_CTRL0_T         reg_dec_sync_3dly_ctrl0;	//0xCC862190
	PE_CCO_DEC_SYNC_3DLY_CTRL1_T         reg_dec_sync_3dly_ctrl1;	//0xCC862194
	PE_CCO_DEC_SYNC_3DLY_CTRL2_T         reg_dec_sync_3dly_ctrl2;	//0xCC862198
	PE_CCO_DEC_SYNC_3DLY_CTRL3_T         reg_dec_sync_3dly_ctrl3;	//0xCC86219C
	PE_CCO_DEC_SYNC_3DLY_CTRL4_T         reg_dec_sync_3dly_ctrl4;	//0xCC8621A0
	PE_CCO_DEC_SYNC_3DLY_CTRL5_T         reg_dec_sync_3dly_ctrl5;	//0xCC8621A4
	PE_CCO_DEC_SYNC_3DLY_CTRL6_T         reg_dec_sync_3dly_ctrl6;	//0xCC8621A8
	PE_CCO_DEC_SYNC_3DLY_CTRL7_T         reg_dec_sync_3dly_ctrl7;	//0xCC8621AC
	PE_CCO_DEC_SYNC_3DLY_CTRL8_T         reg_dec_sync_3dly_ctrl8;	//0xCC8621B0
	PE_CCO_DEC_SYNC_3DLY_CTRL9_T         reg_dec_sync_3dly_ctrl9;	//0xCC8621B4
	PE_CCO_DEC_SYNC_3DLY_CTRLA_T         reg_dec_sync_3dly_ctrla;	//0xCC8621B8
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
}PE_CCO_DECON_REG_O24_T;

#endif


