#ifndef _BE_CCO_REG_O26A0_H_
#define _BE_CCO_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

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
}BE_O26_CC2_VSPYC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881604 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_VSPYC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881608 RW 0x12AF_7C94
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,NA,0x7C94) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}BE_O26_CC2_VSPYC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88160C RW 0x7773_12AF
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,NA,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,NA,0x7773) //
	UINT32 resvd1                           :1;
	};
}BE_O26_CC2_VSPYC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881610 RW 0x21E6_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,NA,0x21E6) //
	UINT32 resvd1                           :1;
	};
}BE_O26_CC2_VSPYC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881614 RW 0x12AF_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,NA,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,NA,0x12AF) //
	UINT32 resvd1                           :1;
	};
}BE_O26_CC2_VSPYC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881618 RW 0x1CC5_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,NA,0x1CC5) //
	UINT32 resvd1                           :1;
	};
}BE_O26_CC2_VSPYC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88161C RW 0x07C0_0600
	UINT32 r_yc2rgb_ofst1                   :11;	//(10:0,NA,0x600) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst0                   :11;	//(26:16,NA,0x7C0) //
	UINT32 resvd1                           :5;
	};
}BE_O26_CC2_VSPYC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881620 RW 0x0600_0000
	UINT32 r_yc2rgb_ofst3                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst2                   :11;	//(26:16,NA,0x600) //
	UINT32 resvd1                           :5;
	};
}BE_O26_CC2_VSPYC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881624 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :11;	//(10:0,NA,0x0) //
	UINT32 resvd0                           :5;
	UINT32 r_yc2rgb_ofst4                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSPYC_CTRL_09_T;

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
}BE_O26_CC2_VSP_CC_CTRL_00_T;

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
}BE_O26_CC2_VSP_CC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881650 RW 0x01F1_0000
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x1F1) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881654 RW 0x0200_00BE
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xBE) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881658 RW 0x020D_00F0
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xF0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x20D) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88165C RW 0x0214_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x214) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881660 RW 0x0228_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x228) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881664 RW 0x0230_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x230) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881668 RW 0x023F_00A0
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xA0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x23F) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88166C RW 0x024D_0000
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x24D) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_VSP_CRGN_CTRL_07_T;

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
}BE_O26_CC2_VSP_CRGN_CTRL_08_T;

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
}BE_O26_CC2_VSP_CRGN_CTRL_09_T;

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
}BE_O26_CC2_VSP_CRGN_CTRL_10_T;

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
}BE_O26_CC2_VSP_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881680 RW 0x328C_0F00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0xF) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x8C) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x32) //
	};
}BE_O26_CC2_VSP_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881684 RW 0x64FF_50FF
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x50) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x64) //
	};
}BE_O26_CC2_VSP_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881688 RW 0xD278_AFFF
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xAF) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0x78) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xD2) //
	};
}BE_O26_CC2_VSP_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88168C RO 0xE600_DC3C
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0x3C) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xDC) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0x0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xE6) //
	};
}BE_O26_CC2_VSP_CRGN_CTRL_15_T;

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
}BE_O26_CC2_DEBUG_CTRL_00_T;

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
}BE_O26_CC2_DEBUG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816A8 RW 0x0000_0000
	UINT32 force_yy                         :10;	//(9:0,NA,0x0) //
	UINT32 force_cb                         :10;	//(19:10,NA,0x0) //forcing Cb data
	UINT32 force_cr                         :10;	//(29:20,NA,0x0) //forcing Cr data
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_DEBUG_CTRL_02_T;

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
}BE_O26_CC2_CW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816B4 RW 0x00C0_C0C0
	UINT32 user_ctrl_g_gain                 :8;	//(7:0,NA,0xC0) //User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//(15:8,NA,0xC0) //User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//(23:16,NA,0xC0) //User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
}BE_O26_CC2_CW_CTRL_01_T;

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
}BE_O26_CC2_CW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C0 RW 0x0000_00FF
	UINT32 reg_crgn_hue_gain_y0             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C4 RW 0x0064_00FF
	UINT32 reg_crgn_hue_gain_y1             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//(25:16,NA,0x64) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816C8 RW 0x011C_00FF
	UINT32 reg_crgn_hue_gain_y2             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//(25:16,NA,0x11C) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816CC RW 0x01AA_00FF
	UINT32 reg_crgn_hue_gain_y3             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//(25:16,NA,0x1AA) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D0 RW 0x0238_00FF
	UINT32 reg_crgn_hue_gain_y4             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//(25:16,NA,0x238) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D4 RW 0x02C6_00FF
	UINT32 reg_crgn_hue_gain_y5             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//(25:16,NA,0x2C6) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816D8 RW 0x0354_00FF
	UINT32 reg_crgn_hue_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//(25:16,NA,0x354) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816DC RW 0x03FF_00FF
	UINT32 reg_crgn_hue_gain_y7             :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_CW_CRGN_CTRL_07_T;

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
}BE_O26_CC2_CW_CRGN_CTRL_08_T;

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
}BE_O26_CC2_CW_CRGN_CTRL_09_T;

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
}BE_O26_CC2_CW_CRGN_CTRL_10_T;

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
}BE_O26_CC2_CW_CRGN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F0 RW 0x6464_3C00
	UINT32 reg_crgn_val_gain_y0             :8;	//(7:0,NA,0x0) //
	UINT32 reg_crgn_val_gain_x0             :8;	//(15:8,NA,0x3C) //
	UINT32 reg_crgn_val_gain_y1             :8;	//(23:16,NA,0x64) //
	UINT32 reg_crgn_val_gain_x1             :8;	//(31:24,NA,0x64) //
	};
}BE_O26_CC2_CW_CRGN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F4 RW 0x8CC8_7896
	UINT32 reg_crgn_val_gain_y2             :8;	//(7:0,NA,0x96) //
	UINT32 reg_crgn_val_gain_x2             :8;	//(15:8,NA,0x78) //
	UINT32 reg_crgn_val_gain_y3             :8;	//(23:16,NA,0xC8) //
	UINT32 reg_crgn_val_gain_x3             :8;	//(31:24,NA,0x8C) //
	};
}BE_O26_CC2_CW_CRGN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816F8 RW 0xBEFF_A0E6
	UINT32 reg_crgn_val_gain_y4             :8;	//(7:0,NA,0xE6) //
	UINT32 reg_crgn_val_gain_x4             :8;	//(15:8,NA,0xA0) //
	UINT32 reg_crgn_val_gain_y5             :8;	//(23:16,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x5             :8;	//(31:24,NA,0xBE) //
	};
}BE_O26_CC2_CW_CRGN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8816FC RW 0xFFA0_FAFF
	UINT32 reg_crgn_val_gain_y6             :8;	//(7:0,NA,0xFF) //
	UINT32 reg_crgn_val_gain_x6             :8;	//(15:8,NA,0xFA) //
	UINT32 reg_crgn_val_gain_y7             :8;	//(23:16,NA,0xA0) //
	UINT32 reg_crgn_val_gain_x7             :8;	//(31:24,NA,0xFF) //
	};
}BE_O26_CC2_CW_CRGN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881710 RW 0x1E00_10E0
	UINT32 display_height                   :13;	//(12:0,NA,0x10E0) //
	UINT32 resvd0                           :3;
	UINT32 display_width                    :13;	//(28:16,NA,0x1E00) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LBLUR_CTRL_00_T;

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
}BE_O26_CC2_LBLUR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881718 RW 0x0000_0000
	UINT32 reg_last_block_size_v            :8;	//(7:0,NA,0x0) //
	UINT32 reg_last_block_size_h            :8;	//(15:8,NA,0x0) //
	UINT32 resvd                            :16;
	};
}BE_O26_CC2_LBLUR_CTRL_02_T;

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
}BE_O26_CC2_LOGO_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881724 RW 0x12C2_5BFE
	UINT32 resvd                            :1;
	UINT32 bound_proc_logocheck             :1;	//(1,NA,0x1) //
	UINT32 bound_proc_gain                  :8;	//(9:2,NA,0xff) //
	UINT32 bound_proc_range_x               :11;	//(20:10,NA,0x96) //
	UINT32 bound_proc_range_y               :11;	//(31:21,NA,0x96) //
	};
}BE_O26_CC2_LOGO_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881728 RW 0x0000_0000
	UINT32 boundary_position_x0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_x1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88172C RW 0x0000_0000
	UINT32 boundary_position_y0             :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 boundary_position_y1             :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881730 RW 0x03BF_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,NA,0x3BF) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881734 RW 0x10DF_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,NA,0x10DF) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881738 RW 0x0100_0080
	UINT32 reg_region_position_x1           :13;	//(12:0,NA,0x80) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,NA,0x100) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88173C RW 0x0200_0180
	UINT32 reg_region_position_x3           :13;	//(12:0,NA,0x180) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,NA,0x200) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881740 RW 0x0300_0280
	UINT32 reg_region_position_x5           :13;	//(12:0,NA,0x280) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,NA,0x300) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881744 RW 0x03A0_0380
	UINT32 reg_region_position_x7           :13;	//(12:0,NA,0x380) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,NA,0x3A0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881748 RW 0x0800_0400
	UINT32 reg_region_position_y1           :13;	//(12:0,NA,0x400) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,NA,0x800) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88174C RW 0x0E00_0C00
	UINT32 reg_region_position_y3           :13;	//(12:0,NA,0xC00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,NA,0xE00) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881750 RW 0x1000_0F00
	UINT32 reg_region_position_y5           :13;	//(12:0,NA,0xF00) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,NA,0x1000) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881754 RW 0x8080_8080
	UINT32 reg_region_gain_11               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_21               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_31               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_41               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881758 RW 0x8080_8080
	UINT32 reg_region_gain_51               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_61               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_71               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_81               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88175C RW 0x8080_8080
	UINT32 reg_region_gain_12               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_22               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_32               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_42               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881760 RW 0x8080_8080
	UINT32 reg_region_gain_52               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_62               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_72               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_82               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881764 RW 0x8080_8080
	UINT32 reg_region_gain_13               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_23               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_33               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_43               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881768 RW 0x8080_8080
	UINT32 reg_region_gain_53               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_63               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_73               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_83               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88176C RW 0x8080_8080
	UINT32 reg_region_gain_14               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_24               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_34               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_44               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881770 RW 0x8080_8080
	UINT32 reg_region_gain_54               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_64               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_74               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_84               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881774 RW 0x8080_8080
	UINT32 reg_region_gain_15               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_25               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_35               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_45               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881778 RW 0x8080_8080
	UINT32 reg_region_gain_55               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_65               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_75               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_85               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88177C RW 0x8080_8080
	UINT32 reg_region_gain_16               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_26               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_36               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_46               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881780 RW 0x8080_8080
	UINT32 reg_region_gain_56               :8;	//(7:0,NA,0x80) //
	UINT32 reg_region_gain_66               :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_76               :8;	//(23:16,NA,0x80) //
	UINT32 reg_region_gain_86               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_LOGO_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881784 RW 0x0200_0310
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x310) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881788 RW 0x0080_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x80) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88178C RW 0x2040_80C4
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xC4) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x20) //
	};
}BE_O26_CC2_LOGO_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881790 RW 0x0380_03FF
	UINT32 reg_drop_x7_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,NA,0x380) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881794 RW 0x0200_0300
	UINT32 reg_drop_x5_i                    :10;	//(9:0,NA,0x300) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881798 RW 0x0100_0200
	UINT32 reg_drop_x3_i                    :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,NA,0x100) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88179C RW 0x0000_0100
	UINT32 reg_drop_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A0 RW 0x0200_0240
	UINT32 reg_drop_y7_i                    :10;	//(9:0,NA,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A4 RW 0x0190_01C0
	UINT32 reg_drop_y5_i                    :10;	//(9:0,NA,0x1C0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,NA,0x190) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817A8 RW 0x00E0_0190
	UINT32 reg_drop_y3_i                    :10;	//(9:0,NA,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,NA,0xE0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817AC RW 0x0000_00E0
	UINT32 reg_drop_y1_i                    :10;	//(9:0,NA,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B0 RW 0x0300_03FF
	UINT32 reg_sat_scon_x3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B4 RW 0x0000_0200
	UINT32 reg_sat_scon_x1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_x0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817B8 RW 0x0300_03FF
	UINT32 reg_sat_scon_y3_i                :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y2_i                :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817BC RW 0x0000_0200
	UINT32 reg_sat_scon_y1_i                :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_scon_y0_i                :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C0 RW 0x1080_1080
	UINT32 reg_l7_gain_drop                 :8;	//(7:0,NA,0x80) //
	UINT32 reg_l7_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l7_gain_b_contrast           :8;	//(23:16,NA,0x80) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l7_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}BE_O26_CC2_LOGO_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C4 RW 0x0840_1040
	UINT32 reg_l3_gain_drop                 :8;	//(7:0,NA,0x40) //
	UINT32 reg_l3_gain_w_contrast           :8;	//(15:8,NA,0x10) //white(bright) contrast gain(input level < output level)
	UINT32 reg_l3_gain_b_contrast           :8;	//(23:16,NA,0x40) //black(dark) contrast gain(input level > output level)
	UINT32 reg_l3_gain_saturation           :8;	//(31:24,NA,0x8) //
	};
}BE_O26_CC2_LOGO_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817C8 RW 0x1060_20A4
	UINT32 reg_c5_gain_drop                 :8;	//(7:0,NA,0xA4) //
	UINT32 reg_c5_gain_w_contrast           :8;	//(15:8,NA,0x20) //white(bright) contrast gain(input level < output level)
	UINT32 reg_c5_gain_b_contrast           :8;	//(23:16,NA,0x60) //black(dark) contrast gain(input level > output level)
	UINT32 reg_c5_gain_saturation           :8;	//(31:24,NA,0x10) //
	};
}BE_O26_CC2_LOGO_CTRL_42_T;

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
}BE_O26_CC2_LOGO_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D0 RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_0                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D4 RW 0x0000_0000
	UINT32 reg_merge_contrast_l7l3          :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_contrast_l7l3c5        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_drop_l7l3              :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_LOGO_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817D8 RW 0x0000_0000
	UINT32 reg_merge_drop_l7l3c5            :10;	//(9:0,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3        :10;	//(19:10,NA,0x0) //
	UINT32 reg_merge_saturation_l7l3c5      :10;	//(29:20,NA,0x0) //
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_LOGO_CTRL_46_T;

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
}BE_O26_CC2_LOGO_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817E0 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height_1                 :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_LOGO_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817F4 RW 0x0040_80FF
	UINT32 reg_txt_x3_i                     :8;	//(7:0,NA,0xFF) //texture gain LUT
	UINT32 reg_txt_x2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_x1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_x0_i                     :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817F8 RW 0x0040_80FF
	UINT32 reg_txt_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_txt_y2_i                     :8;	//(15:8,NA,0x80) //
	UINT32 reg_txt_y1_i                     :8;	//(23:16,NA,0x40) //
	UINT32 reg_txt_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8817FC RW 0x0080_8080
	UINT32 reg_region_gain_contrast         :8;	//(7:0,NA,0x80) //1.0 = 128
	UINT32 reg_region_gain_drop             :8;	//(15:8,NA,0x80) //
	UINT32 reg_region_gain_saturation       :8;	//(23:16,NA,0x80) //
	UINT32 resvd                            :8;
	};
}BE_O26_CC2_LOGO_CTRL_55_T;

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
}BE_O26_CC2_LOGO_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881804 RW 0x00000000
	UINT32 reg_refine_weight_lut_x3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_x2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_x1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_x0         :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881808 RW 0x00000000
	UINT32 reg_refine_weight_lut_y3         :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_lut_y2         :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_lut_y1         :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_lut_y0         :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88180C RW 0x00000000
	UINT32 reg_refine_weight_gain_x3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_x2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_x1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_x0        :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881810 RW 0x00000000
	UINT32 reg_refine_weight_gain_y3        :8;	//(7:0,NA,0x0) //
	UINT32 reg_refine_weight_gain_y2        :8;	//(15:8,NA,0x0) //
	UINT32 reg_refine_weight_gain_y1        :8;	//(23:16,NA,0x0) //
	UINT32 reg_refine_weight_gain_y0        :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_60_T;

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
}BE_O26_CC2_GSR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881824 RW 0x03B0_4200
	UINT32 reg_curr_peak_level              :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :2;
	UINT32 reg_crnt_resol_sel               :4;	//(15:12,NA,0x4) //left shift bit size, 0:8b, 1:7b, 2:6b, 3:5b, 4:4b, 5:3b, 6:2b, 7:1b, 8:0b
	UINT32 reg_wg_ratio                     :11;	//(26:16,NA,0x3B0) //
	UINT32 resvd1                           :5;
	};
}BE_O26_CC2_GSR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881828 RW 0x0478_031F
	UINT32 reg_wb_ratio                     :11;	//(10:0,NA,0x31F) //
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//(26:16,NA,0x478) //
	UINT32 resvd1                           :5;
	};
}BE_O26_CC2_GSR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88182C RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,NA,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,NA,0x326) //
	UINT32 resvd1                           :4;
	};
}BE_O26_CC2_GSR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881830 RW 0x0389_02A8
	UINT32 reg_b_crnt_wgt                   :12;	//(11:0,NA,0x2A8) //
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//(27:16,NA,0x389) //
	UINT32 resvd1                           :4;
	};
}BE_O26_CC2_GSR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881834 RW 0x0000_0000
	UINT32 reg_crnt_lut_y00                 :16;	//(15:0,NA,0x0) //
	UINT32 reg_crnt_lut_x00                 :10;	//(25:16,NA,0x0) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881838 RW 0x0044_0CF9
	UINT32 reg_crnt_lut_y01                 :16;	//(15:0,NA,0xCF9) //
	UINT32 reg_crnt_lut_x01                 :10;	//(25:16,NA,0x44) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88183C RW 0x0088_1BD0
	UINT32 reg_crnt_lut_y02                 :16;	//(15:0,NA,0x1BD0) //
	UINT32 reg_crnt_lut_x02                 :10;	//(25:16,NA,0x88) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881840 RW 0x00CC_2B72
	UINT32 reg_crnt_lut_y03                 :16;	//(15:0,NA,0x2B72) //
	UINT32 reg_crnt_lut_x03                 :10;	//(25:16,NA,0xCC) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881844 RW 0x0110_3B9F
	UINT32 reg_crnt_lut_y04                 :16;	//(15:0,NA,0x3B9F) //
	UINT32 reg_crnt_lut_x04                 :10;	//(25:16,NA,0x110) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881848 RW 0x0154_4C35
	UINT32 reg_crnt_lut_y05                 :16;	//(15:0,NA,0x4C35) //
	UINT32 reg_crnt_lut_x05                 :10;	//(25:16,NA,0x154) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88184C RW 0x0198_5D22
	UINT32 reg_crnt_lut_y06                 :16;	//(15:0,NA,0x5D22) //
	UINT32 reg_crnt_lut_x06                 :10;	//(25:16,NA,0x198) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881850 RW 0x01DC_6E57
	UINT32 reg_crnt_lut_y07                 :16;	//(15:0,NA,0x6E57) //
	UINT32 reg_crnt_lut_x07                 :10;	//(25:16,NA,0x1DC) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881854 RW 0x0220_7FCD
	UINT32 reg_crnt_lut_y08                 :16;	//(15:0,NA,0x7FCD) //
	UINT32 reg_crnt_lut_x08                 :10;	//(25:16,NA,0x220) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881858 RW 0x0264_917A
	UINT32 reg_crnt_lut_y09                 :16;	//(15:0,NA,0x917A) //
	UINT32 reg_crnt_lut_x09                 :10;	//(25:16,NA,0x264) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88185C RW 0x02A8_A35B
	UINT32 reg_crnt_lut_y10                 :16;	//(15:0,NA,0xA35B) //
	UINT32 reg_crnt_lut_x10                 :10;	//(25:16,NA,0x2A8) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881860 RW 0x02EC_B569
	UINT32 reg_crnt_lut_y11                 :16;	//(15:0,NA,0xB569) //
	UINT32 reg_crnt_lut_x11                 :10;	//(25:16,NA,0x2EC) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881864 RW 0x0330_C7A2
	UINT32 reg_crnt_lut_y12                 :16;	//(15:0,NA,0xC7A2) //
	UINT32 reg_crnt_lut_x12                 :10;	//(25:16,NA,0x330) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881868 RW 0x0374_DA02
	UINT32 reg_crnt_lut_y13                 :16;	//(15:0,NA,0xDA02) //
	UINT32 reg_crnt_lut_x13                 :10;	//(25:16,NA,0x374) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88186C RW 0x03B8_EC86
	UINT32 reg_crnt_lut_y14                 :16;	//(15:0,NA,0xEC86) //
	UINT32 reg_crnt_lut_x14                 :10;	//(25:16,NA,0x3B8) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881870 RW 0x03FF_FFFF
	UINT32 reg_crnt_lut_y15                 :16;	//(15:0,NA,0xFFFF) //
	UINT32 reg_crnt_lut_x15                 :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd                            :6;
	};
}BE_O26_CC2_GSR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881874 RW 0x0200_03FF
	UINT32 reg_crnt_x3_i                    :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x2_i                    :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881878 RW 0x0000_0100
	UINT32 reg_crnt_x1_i                    :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_crnt_x0_i                    :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88187C RW 0x0000_0000
	UINT32 reg_crnt_y3_i                    :8;	//(7:0,NA,0x0) //
	UINT32 reg_crnt_y2_i                    :8;	//(15:8,NA,0x0) //
	UINT32 reg_crnt_y1_i                    :8;	//(23:16,NA,0x0) //
	UINT32 reg_crnt_y0_i                    :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_GSR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881880 RW 0x0200_03FF
	UINT32 reg_value_x3_i                   :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x2_i                   :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881884 RW 0x0000_0100
	UINT32 reg_value_x1_i                   :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_value_x0_i                   :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881888 RW 0x0000_0000
	UINT32 reg_value_y3_i                   :8;	//(7:0,NA,0x0) //
	UINT32 reg_value_y2_i                   :8;	//(15:8,NA,0x0) //
	UINT32 reg_value_y1_i                   :8;	//(23:16,NA,0x0) //
	UINT32 reg_value_y0_i                   :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_GSR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88188C RW 0x0200_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881890 RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_GSR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881894 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_GSR_CTRL_29_T;

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
}BE_O26_CC2_GSR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88189C RW 0x0000_0000
	UINT32 reg_pxl_width_0                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_pxl_height_0                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_GSR_CTRL_31_T;

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
}BE_O26_CC2_GSR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818A4 RW 0x0000_0000
	UINT32 reg_pxl_width_1                  :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_pxl_height_1                 :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_GSR_CTRL_33_T;

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
}BE_O26_CC2_MUTE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818E4 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_0                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818E8 RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_MUTE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818EC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_MUTE_CTRL_03_T;

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
}BE_O26_CC2_MUTE_CTRL_04_T;

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
}BE_O26_CC2_MUTE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818F8 RW 0x0000_0000
	UINT32 pxl_rep_width_0                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_0                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8818FC RW 0x0000_0000
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_MUTE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881900 RW VNA
	UINT32 pxl_rep_value_g                  :10;	//(9:0,NA,0x0) //g value for pixel replacement
	UINT32 pxl_rep_value_b                  :10;	//(19:10,NA,0x0) //b value for pixel replacement
	UINT32 pxl_rep_value_r                  :10;	//(29:20,NA,0x0) //r value for pixel replacement
	UINT32 resvd                            :2;
	};
}BE_O26_CC2_MUTE_CTRL_08_T;

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
}BE_O26_CC2_MUTE_CTRL_09_T;

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
}BE_O26_CC2_MUTE_CTRL_10_T;

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
}BE_O26_CC2_MUTE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881910 RW 0x0000_0000
	UINT32 x1_0                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_0                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_12_T;

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
}BE_O26_CC2_MUTE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881918 RW 0x0000_0000
	UINT32 x1_0                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_0                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88191C RW 0x0000_0000
	UINT32 bg_color_r                       :8;	//(7:0,NA,0x0) //8 bit R value for pixel replacement
	UINT32 bg_color_b                       :8;	//(15:8,NA,0x0) //8 bit B value for pixel replacement
	UINT32 bg_color_g                       :8;	//(23:16,NA,0x0) //8 bit G value for pixel replacement
	UINT32 resvd                            :8;
	};
}BE_O26_CC2_MUTE_CTRL_15_T;

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
}BE_O26_CC2_MUTE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881924 RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_1                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_17_T;

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
}BE_O26_CC2_MUTE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88192C RW 0x0000_0000
	UINT32 pxl_rep_width_1                  :14;	//(13:0,NA,0x0) //width for pixel replacement
	UINT32 resvd0                           :2;
	UINT32 pxl_rep_height_1                 :14;	//(29:16,NA,0x0) //height for pixel replacement
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_19_T;

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
}BE_O26_CC2_MUTE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881934 RW 0x0000_0000
	UINT32 x1_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_21_T;

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
}BE_O26_CC2_MUTE_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88193C RW 0x0000_0000
	UINT32 x1_1                             :14;	//(13:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 y1_1                             :14;	//(29:16,NA,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26_CC2_MUTE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A00 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A04 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A08 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A0C RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_64_T;

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
}BE_O26_CC2_LOGO_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A14 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A18 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A1C RW 0x0002_8028
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x28) //
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A20 RW 0x0002_8028
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x28) //
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A24 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}BE_O26_CC2_LOGO_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A28 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_71_T;

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
}BE_O26_CC2_LOGO_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A30 RW 0x0000_0000
	UINT32 reg_sat_x3_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A34 RW 0x0000_0000
	UINT32 reg_sat_x1_i                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A38 RW 0x0000_0000
	UINT32 reg_sat_y3_i                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,RW,0x0) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,RW,0x0) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,RW,0x0) //
	};
}BE_O26_CC2_LOGO_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A3C RW 0x0000_0000
	UINT32 reg_drop_x7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A40 RW 0x0000_0000
	UINT32 reg_drop_x5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A44 RW 0x0000_0000
	UINT32 reg_drop_x3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A48 RW 0x0000_0000
	UINT32 reg_drop_x1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_x0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A4C RW 0x0000_0000
	UINT32 reg_drop_y7_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y6_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A50 RW 0x0000_0000
	UINT32 reg_drop_y5_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y4_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A54 RW 0x0000_0000
	UINT32 reg_drop_y3_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y2_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_82_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A58 RW 0x0000_0000
	UINT32 reg_drop_y1_i                    :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drop_y0_i                    :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_83_T;

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
}BE_O26_CC2_LOGO_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A60 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_85_T;

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
}BE_O26_CC2_LOGO_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881A68 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26_CC2_LOGO_CTRL_87_T;

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
}BE_O26_CC2_LOGO_CTRL_88_T;

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
}BE_O26_CC2_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AA4 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AA8 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AAC RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB0 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB4 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AB8 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ABC RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AC0 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiongain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiongain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiongain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AC4 RW 0x8080_FFFF
	UINT32 reg_motiongain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiongain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiongain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiongain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_09_T;

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
}BE_O26_CC2_MERGE_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ACC RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AD0 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_12_T;

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
}BE_O26_CC2_MERGE_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AD8 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881ADC RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE0 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE4 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AE8 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AEC RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF0 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF4 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiongain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiongain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiongain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881AF8 RW 0x8080_FFFF
	UINT32 reg_motiongain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiongain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiongain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiongain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_22_T;

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
}BE_O26_CC2_MERGE_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B00 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B04 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_25_T;

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
}BE_O26_CC2_MERGE_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B0C RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B10 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B14 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B18 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B1C RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B20 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B24 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B28 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B2C RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_35_T;

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
}BE_O26_CC2_MERGE_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B34 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B38 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_38_T;

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
}BE_O26_CC2_MERGE_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B40 RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B44 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B48 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B4C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B50 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B54 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B58 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B5C RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B60 RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_48_T;

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
}BE_O26_CC2_MERGE_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B68 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B6C RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_51_T;

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
}BE_O26_CC2_MERGE_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B74 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B78 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B7C RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B80 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B84 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B88 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_58_T;

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
}BE_O26_CC2_MERGE_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B90 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B94 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_61_T;

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
}BE_O26_CC2_MERGE_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881B9C RW 0x8080_8080
	UINT32 reg_motion_master_gain           :8;	//(7:0,NA,0x80) //
	UINT32 reg_text_master_gain             :8;	//(15:8,NA,0x80) //
	UINT32 reg_body_master_gain             :8;	//(23:16,NA,0x80) //
	UINT32 reg_head_master_gain             :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA0 RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA4 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BA8 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BAC RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB0 RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB4 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BB8 RW 0x0000_4040
	UINT32 reg_motiongain_y1_i              :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_motiogain_x1_i               :8;	//(15:8,NA,0x40) //
	UINT32 reg_motiogain_y0_i               :8;	//(23:16,NA,0x0) //
	UINT32 reg_motiogain_x0_i               :8;	//(31:24,NA,0x0) //
	};
}BE_O26_CC2_MERGE_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BBC RW 0x8080_FFFF
	UINT32 reg_motiogain_y3_i               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_motiogain_x3_i               :8;	//(15:8,NA,0xFF) //
	UINT32 reg_motiogain_y2_i               :8;	//(23:16,NA,0x80) //
	UINT32 reg_motiogain_x2_i               :8;	//(31:24,NA,0x80) //
	};
}BE_O26_CC2_MERGE_CTRL_71_T;

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
}BE_O26_CC2_MERGE_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BC4 RW 0x0000_0000
	UINT32 reg_pxl_width                    :13;	//(12:0,NA,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_height                   :13;	//(28:16,NA,0x0) //1
	UINT32 resvd1                           :3;
	};
}BE_O26_CC2_MERGE_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881BC8 RW 0x0000_0000
	UINT32 reg_win_in_objt_gain             :8;	//(7:0,NA,0x0) //inside window gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_out_objt_gain            :8;	//(23:16,NA,0x0) //outside window gain
	UINT32 resvd1                           :8;
	};
}BE_O26_CC2_MERGE_CTRL_74_T;

typedef struct {
	BE_O26_CC2_VSPYC_CTRL_00_T                       pe1_vspyc_ctrl_00;	//0xCC881600
	BE_O26_CC2_VSPYC_CTRL_01_T                       pe1_vspyc_ctrl_01;	//0xCC881604
	BE_O26_CC2_VSPYC_CTRL_02_T                       pe1_vspyc_ctrl_02;	//0xCC881608
	BE_O26_CC2_VSPYC_CTRL_03_T                       pe1_vspyc_ctrl_03;	//0xCC88160C
	BE_O26_CC2_VSPYC_CTRL_04_T                       pe1_vspyc_ctrl_04;	//0xCC881610
	BE_O26_CC2_VSPYC_CTRL_05_T                       pe1_vspyc_ctrl_05;	//0xCC881614
	BE_O26_CC2_VSPYC_CTRL_06_T                       pe1_vspyc_ctrl_06;	//0xCC881618
	BE_O26_CC2_VSPYC_CTRL_07_T                       pe1_vspyc_ctrl_07;	//0xCC88161C
	BE_O26_CC2_VSPYC_CTRL_08_T                       pe1_vspyc_ctrl_08;	//0xCC881620
	BE_O26_CC2_VSPYC_CTRL_09_T                       pe1_vspyc_ctrl_09;	//0xCC881624
	UINT32                                                       reserved0;	//0xCC881628
	UINT32                                                       reserved1;	//0xCC88162C
	BE_O26_CC2_VSP_CC_CTRL_00_T                     pe1_vsp_cc_ctrl_00;	//0xCC881630
	UINT32                                                       reserved2;	//0xCC881634
	UINT32                                                       reserved3;	//0xCC881638
	UINT32                                                       reserved4;	//0xCC88163C
	UINT32                                                       reserved5;	//0xCC881640
	BE_O26_CC2_VSP_CC_CTRL_05_T                     pe1_vsp_cc_ctrl_05;	//0xCC881644
	UINT32                                                       reserved6;	//0xCC881648
	UINT32                                                       reserved7;	//0xCC88164C
	BE_O26_CC2_VSP_CRGN_CTRL_00_T                 pe1_vsp_crgn_ctrl_00;	//0xCC881650
	BE_O26_CC2_VSP_CRGN_CTRL_01_T                 pe1_vsp_crgn_ctrl_01;	//0xCC881654
	BE_O26_CC2_VSP_CRGN_CTRL_02_T                 pe1_vsp_crgn_ctrl_02;	//0xCC881658
	BE_O26_CC2_VSP_CRGN_CTRL_03_T                 pe1_vsp_crgn_ctrl_03;	//0xCC88165C
	BE_O26_CC2_VSP_CRGN_CTRL_04_T                 pe1_vsp_crgn_ctrl_04;	//0xCC881660
	BE_O26_CC2_VSP_CRGN_CTRL_05_T                 pe1_vsp_crgn_ctrl_05;	//0xCC881664
	BE_O26_CC2_VSP_CRGN_CTRL_06_T                 pe1_vsp_crgn_ctrl_06;	//0xCC881668
	BE_O26_CC2_VSP_CRGN_CTRL_07_T                 pe1_vsp_crgn_ctrl_07;	//0xCC88166C
	BE_O26_CC2_VSP_CRGN_CTRL_08_T                 pe1_vsp_crgn_ctrl_08;	//0xCC881670
	BE_O26_CC2_VSP_CRGN_CTRL_09_T                 pe1_vsp_crgn_ctrl_09;	//0xCC881674
	BE_O26_CC2_VSP_CRGN_CTRL_10_T                 pe1_vsp_crgn_ctrl_10;	//0xCC881678
	BE_O26_CC2_VSP_CRGN_CTRL_11_T                 pe1_vsp_crgn_ctrl_11;	//0xCC88167C
	BE_O26_CC2_VSP_CRGN_CTRL_12_T                 pe1_vsp_crgn_ctrl_12;	//0xCC881680
	BE_O26_CC2_VSP_CRGN_CTRL_13_T                 pe1_vsp_crgn_ctrl_13;	//0xCC881684
	BE_O26_CC2_VSP_CRGN_CTRL_14_T                 pe1_vsp_crgn_ctrl_14;	//0xCC881688
	BE_O26_CC2_VSP_CRGN_CTRL_15_T                 pe1_vsp_crgn_ctrl_15;	//0xCC88168C
	UINT32                                                       reserved8;	//0xCC881690
	UINT32                                                       reserved9;	//0xCC881694
	UINT32                                                      reserved10;	//0xCC881698
	UINT32                                                      reserved11;	//0xCC88169C
	BE_O26_CC2_DEBUG_CTRL_00_T                       pe1_debug_ctrl_00;	//0xCC8816A0
	BE_O26_CC2_DEBUG_CTRL_01_T                       pe1_debug_ctrl_01;	//0xCC8816A4
	BE_O26_CC2_DEBUG_CTRL_02_T                       pe1_debug_ctrl_02;	//0xCC8816A8
	UINT32                                                      reserved12;	//0xCC8816AC
	BE_O26_CC2_CW_CTRL_00_T                             pe1_cw_ctrl_00;	//0xCC8816B0
	BE_O26_CC2_CW_CTRL_01_T                             pe1_cw_ctrl_01;	//0xCC8816B4
	BE_O26_CC2_CW_CTRL_02_T                             pe1_cw_ctrl_02;	//0xCC8816B8
	UINT32                                                      reserved13;	//0xCC8816BC
	BE_O26_CC2_CW_CRGN_CTRL_00_T                   pe1_cw_crgn_ctrl_00;	//0xCC8816C0
	BE_O26_CC2_CW_CRGN_CTRL_01_T                   pe1_cw_crgn_ctrl_01;	//0xCC8816C4
	BE_O26_CC2_CW_CRGN_CTRL_02_T                   pe1_cw_crgn_ctrl_02;	//0xCC8816C8
	BE_O26_CC2_CW_CRGN_CTRL_03_T                   pe1_cw_crgn_ctrl_03;	//0xCC8816CC
	BE_O26_CC2_CW_CRGN_CTRL_04_T                   pe1_cw_crgn_ctrl_04;	//0xCC8816D0
	BE_O26_CC2_CW_CRGN_CTRL_05_T                   pe1_cw_crgn_ctrl_05;	//0xCC8816D4
	BE_O26_CC2_CW_CRGN_CTRL_06_T                   pe1_cw_crgn_ctrl_06;	//0xCC8816D8
	BE_O26_CC2_CW_CRGN_CTRL_07_T                   pe1_cw_crgn_ctrl_07;	//0xCC8816DC
	BE_O26_CC2_CW_CRGN_CTRL_08_T                   pe1_cw_crgn_ctrl_08;	//0xCC8816E0
	BE_O26_CC2_CW_CRGN_CTRL_09_T                   pe1_cw_crgn_ctrl_09;	//0xCC8816E4
	BE_O26_CC2_CW_CRGN_CTRL_10_T                   pe1_cw_crgn_ctrl_10;	//0xCC8816E8
	BE_O26_CC2_CW_CRGN_CTRL_11_T                   pe1_cw_crgn_ctrl_11;	//0xCC8816EC
	BE_O26_CC2_CW_CRGN_CTRL_12_T                   pe1_cw_crgn_ctrl_12;	//0xCC8816F0
	BE_O26_CC2_CW_CRGN_CTRL_13_T                   pe1_cw_crgn_ctrl_13;	//0xCC8816F4
	BE_O26_CC2_CW_CRGN_CTRL_14_T                   pe1_cw_crgn_ctrl_14;	//0xCC8816F8
	BE_O26_CC2_CW_CRGN_CTRL_15_T                   pe1_cw_crgn_ctrl_15;	//0xCC8816FC
	UINT32                                                      reserved14;	//0xCC881700
	UINT32                                                      reserved15;	//0xCC881704
	UINT32                                                      reserved16;	//0xCC881708
	UINT32                                                      reserved17;	//0xCC88170C
	BE_O26_CC2_LBLUR_CTRL_00_T                       pe1_lblur_ctrl_00;	//0xCC881710
	BE_O26_CC2_LBLUR_CTRL_01_T                       pe1_lblur_ctrl_01;	//0xCC881714
	BE_O26_CC2_LBLUR_CTRL_02_T                       pe1_lblur_ctrl_02;	//0xCC881718
	UINT32                                                      reserved18;	//0xCC88171C
	BE_O26_CC2_LOGO_CTRL_00_T                         pe1_logo_ctrl_00;	//0xCC881720
	BE_O26_CC2_LOGO_CTRL_01_T                         pe1_logo_ctrl_01;	//0xCC881724
	BE_O26_CC2_LOGO_CTRL_02_T                         pe1_logo_ctrl_02;	//0xCC881728
	BE_O26_CC2_LOGO_CTRL_03_T                         pe1_logo_ctrl_03;	//0xCC88172C
	BE_O26_CC2_LOGO_CTRL_04_T                         pe1_logo_ctrl_04;	//0xCC881730
	BE_O26_CC2_LOGO_CTRL_05_T                         pe1_logo_ctrl_05;	//0xCC881734
	BE_O26_CC2_LOGO_CTRL_06_T                         pe1_logo_ctrl_06;	//0xCC881738
	BE_O26_CC2_LOGO_CTRL_07_T                         pe1_logo_ctrl_07;	//0xCC88173C
	BE_O26_CC2_LOGO_CTRL_08_T                         pe1_logo_ctrl_08;	//0xCC881740
	BE_O26_CC2_LOGO_CTRL_09_T                         pe1_logo_ctrl_09;	//0xCC881744
	BE_O26_CC2_LOGO_CTRL_10_T                         pe1_logo_ctrl_10;	//0xCC881748
	BE_O26_CC2_LOGO_CTRL_11_T                         pe1_logo_ctrl_11;	//0xCC88174C
	BE_O26_CC2_LOGO_CTRL_12_T                         pe1_logo_ctrl_12;	//0xCC881750
	BE_O26_CC2_LOGO_CTRL_13_T                         pe1_logo_ctrl_13;	//0xCC881754
	BE_O26_CC2_LOGO_CTRL_14_T                         pe1_logo_ctrl_14;	//0xCC881758
	BE_O26_CC2_LOGO_CTRL_15_T                         pe1_logo_ctrl_15;	//0xCC88175C
	BE_O26_CC2_LOGO_CTRL_16_T                         pe1_logo_ctrl_16;	//0xCC881760
	BE_O26_CC2_LOGO_CTRL_17_T                         pe1_logo_ctrl_17;	//0xCC881764
	BE_O26_CC2_LOGO_CTRL_18_T                         pe1_logo_ctrl_18;	//0xCC881768
	BE_O26_CC2_LOGO_CTRL_19_T                         pe1_logo_ctrl_19;	//0xCC88176C
	BE_O26_CC2_LOGO_CTRL_20_T                         pe1_logo_ctrl_20;	//0xCC881770
	BE_O26_CC2_LOGO_CTRL_21_T                         pe1_logo_ctrl_21;	//0xCC881774
	BE_O26_CC2_LOGO_CTRL_22_T                         pe1_logo_ctrl_22;	//0xCC881778
	BE_O26_CC2_LOGO_CTRL_23_T                         pe1_logo_ctrl_23;	//0xCC88177C
	BE_O26_CC2_LOGO_CTRL_24_T                         pe1_logo_ctrl_24;	//0xCC881780
	BE_O26_CC2_LOGO_CTRL_25_T                         pe1_logo_ctrl_25;	//0xCC881784
	BE_O26_CC2_LOGO_CTRL_26_T                         pe1_logo_ctrl_26;	//0xCC881788
	BE_O26_CC2_LOGO_CTRL_27_T                         pe1_logo_ctrl_27;	//0xCC88178C
	BE_O26_CC2_LOGO_CTRL_28_T                         pe1_logo_ctrl_28;	//0xCC881790
	BE_O26_CC2_LOGO_CTRL_29_T                         pe1_logo_ctrl_29;	//0xCC881794
	BE_O26_CC2_LOGO_CTRL_30_T                         pe1_logo_ctrl_30;	//0xCC881798
	BE_O26_CC2_LOGO_CTRL_31_T                         pe1_logo_ctrl_31;	//0xCC88179C
	BE_O26_CC2_LOGO_CTRL_32_T                         pe1_logo_ctrl_32;	//0xCC8817A0
	BE_O26_CC2_LOGO_CTRL_33_T                         pe1_logo_ctrl_33;	//0xCC8817A4
	BE_O26_CC2_LOGO_CTRL_34_T                         pe1_logo_ctrl_34;	//0xCC8817A8
	BE_O26_CC2_LOGO_CTRL_35_T                         pe1_logo_ctrl_35;	//0xCC8817AC
	BE_O26_CC2_LOGO_CTRL_36_T                         pe1_logo_ctrl_36;	//0xCC8817B0
	BE_O26_CC2_LOGO_CTRL_37_T                         pe1_logo_ctrl_37;	//0xCC8817B4
	BE_O26_CC2_LOGO_CTRL_38_T                         pe1_logo_ctrl_38;	//0xCC8817B8
	BE_O26_CC2_LOGO_CTRL_39_T                         pe1_logo_ctrl_39;	//0xCC8817BC
	BE_O26_CC2_LOGO_CTRL_40_T                         pe1_logo_ctrl_40;	//0xCC8817C0
	BE_O26_CC2_LOGO_CTRL_41_T                         pe1_logo_ctrl_41;	//0xCC8817C4
	BE_O26_CC2_LOGO_CTRL_42_T                         pe1_logo_ctrl_42;	//0xCC8817C8
	BE_O26_CC2_LOGO_CTRL_43_T                         pe1_logo_ctrl_43;	//0xCC8817CC
	BE_O26_CC2_LOGO_CTRL_44_T                         pe1_logo_ctrl_44;	//0xCC8817D0
	BE_O26_CC2_LOGO_CTRL_45_T                         pe1_logo_ctrl_45;	//0xCC8817D4
	BE_O26_CC2_LOGO_CTRL_46_T                         pe1_logo_ctrl_46;	//0xCC8817D8
	BE_O26_CC2_LOGO_CTRL_47_T                         pe1_logo_ctrl_47;	//0xCC8817DC
	BE_O26_CC2_LOGO_CTRL_48_T                         pe1_logo_ctrl_48;	//0xCC8817E0
	UINT32                                                      reserved19;	//0xCC8817E4
	UINT32                                                      reserved20;	//0xCC8817E8
	UINT32                                                      reserved21;	//0xCC8817EC
	UINT32                                                      reserved22;	//0xCC8817F0
	BE_O26_CC2_LOGO_CTRL_53_T                         pe1_logo_ctrl_53;	//0xCC8817F4
	BE_O26_CC2_LOGO_CTRL_54_T                         pe1_logo_ctrl_54;	//0xCC8817F8
	BE_O26_CC2_LOGO_CTRL_55_T                         pe1_logo_ctrl_55;	//0xCC8817FC
	BE_O26_CC2_LOGO_CTRL_56_T                         pe1_logo_ctrl_56;	//0xCC881800
	BE_O26_CC2_LOGO_CTRL_57_T                         pe1_logo_ctrl_57;	//0xCC881804
	BE_O26_CC2_LOGO_CTRL_58_T                         pe1_logo_ctrl_58;	//0xCC881808
	BE_O26_CC2_LOGO_CTRL_59_T                         pe1_logo_ctrl_59;	//0xCC88180C
	BE_O26_CC2_LOGO_CTRL_60_T                         pe1_logo_ctrl_60;	//0xCC881810
	UINT32                                                      reserved23;	//0xCC881814
	UINT32                                                      reserved24;	//0xCC881818
	UINT32                                                      reserved25;	//0xCC88181C
	BE_O26_CC2_GSR_CTRL_00_T                           pe1_gsr_ctrl_00;	//0xCC881820
	BE_O26_CC2_GSR_CTRL_01_T                           pe1_gsr_ctrl_01;	//0xCC881824
	BE_O26_CC2_GSR_CTRL_02_T                           pe1_gsr_ctrl_02;	//0xCC881828
	BE_O26_CC2_GSR_CTRL_03_T                           pe1_gsr_ctrl_03;	//0xCC88182C
	BE_O26_CC2_GSR_CTRL_04_T                           pe1_gsr_ctrl_04;	//0xCC881830
	BE_O26_CC2_GSR_CTRL_05_T                           pe1_gsr_ctrl_05;	//0xCC881834
	BE_O26_CC2_GSR_CTRL_06_T                           pe1_gsr_ctrl_06;	//0xCC881838
	BE_O26_CC2_GSR_CTRL_07_T                           pe1_gsr_ctrl_07;	//0xCC88183C
	BE_O26_CC2_GSR_CTRL_08_T                           pe1_gsr_ctrl_08;	//0xCC881840
	BE_O26_CC2_GSR_CTRL_09_T                           pe1_gsr_ctrl_09;	//0xCC881844
	BE_O26_CC2_GSR_CTRL_10_T                           pe1_gsr_ctrl_10;	//0xCC881848
	BE_O26_CC2_GSR_CTRL_11_T                           pe1_gsr_ctrl_11;	//0xCC88184C
	BE_O26_CC2_GSR_CTRL_12_T                           pe1_gsr_ctrl_12;	//0xCC881850
	BE_O26_CC2_GSR_CTRL_13_T                           pe1_gsr_ctrl_13;	//0xCC881854
	BE_O26_CC2_GSR_CTRL_14_T                           pe1_gsr_ctrl_14;	//0xCC881858
	BE_O26_CC2_GSR_CTRL_15_T                           pe1_gsr_ctrl_15;	//0xCC88185C
	BE_O26_CC2_GSR_CTRL_16_T                           pe1_gsr_ctrl_16;	//0xCC881860
	BE_O26_CC2_GSR_CTRL_17_T                           pe1_gsr_ctrl_17;	//0xCC881864
	BE_O26_CC2_GSR_CTRL_18_T                           pe1_gsr_ctrl_18;	//0xCC881868
	BE_O26_CC2_GSR_CTRL_19_T                           pe1_gsr_ctrl_19;	//0xCC88186C
	BE_O26_CC2_GSR_CTRL_20_T                           pe1_gsr_ctrl_20;	//0xCC881870
	BE_O26_CC2_GSR_CTRL_21_T                           pe1_gsr_ctrl_21;	//0xCC881874
	BE_O26_CC2_GSR_CTRL_22_T                           pe1_gsr_ctrl_22;	//0xCC881878
	BE_O26_CC2_GSR_CTRL_23_T                           pe1_gsr_ctrl_23;	//0xCC88187C
	BE_O26_CC2_GSR_CTRL_24_T                           pe1_gsr_ctrl_24;	//0xCC881880
	BE_O26_CC2_GSR_CTRL_25_T                           pe1_gsr_ctrl_25;	//0xCC881884
	BE_O26_CC2_GSR_CTRL_26_T                           pe1_gsr_ctrl_26;	//0xCC881888
	BE_O26_CC2_GSR_CTRL_27_T                           pe1_gsr_ctrl_27;	//0xCC88188C
	BE_O26_CC2_GSR_CTRL_28_T                           pe1_gsr_ctrl_28;	//0xCC881890
	BE_O26_CC2_GSR_CTRL_29_T                           pe1_gsr_ctrl_29;	//0xCC881894
	BE_O26_CC2_GSR_CTRL_30_T                           pe1_gsr_ctrl_30;	//0xCC881898
	BE_O26_CC2_GSR_CTRL_31_T                           pe1_gsr_ctrl_31;	//0xCC88189C
	BE_O26_CC2_GSR_CTRL_32_T                           pe1_gsr_ctrl_32;	//0xCC8818A0
	BE_O26_CC2_GSR_CTRL_33_T                           pe1_gsr_ctrl_33;	//0xCC8818A4
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
	BE_O26_CC2_MUTE_CTRL_00_T                         pe1_mute_ctrl_00;	//0xCC8818E0
	BE_O26_CC2_MUTE_CTRL_01_T                         pe1_mute_ctrl_01;	//0xCC8818E4
	BE_O26_CC2_MUTE_CTRL_02_T                         pe1_mute_ctrl_02;	//0xCC8818E8
	BE_O26_CC2_MUTE_CTRL_03_T                         pe1_mute_ctrl_03;	//0xCC8818EC
	BE_O26_CC2_MUTE_CTRL_04_T                         pe1_mute_ctrl_04;	//0xCC8818F0
	BE_O26_CC2_MUTE_CTRL_05_T                         pe1_mute_ctrl_05;	//0xCC8818F4
	BE_O26_CC2_MUTE_CTRL_06_T                         pe1_mute_ctrl_06;	//0xCC8818F8
	BE_O26_CC2_MUTE_CTRL_07_T                         pe1_mute_ctrl_07;	//0xCC8818FC
	BE_O26_CC2_MUTE_CTRL_08_T                         pe1_mute_ctrl_08;	//0xCC881900
	BE_O26_CC2_MUTE_CTRL_09_T                         pe1_mute_ctrl_09;	//0xCC881904
	BE_O26_CC2_MUTE_CTRL_10_T                         pe1_mute_ctrl_10;	//0xCC881908
	BE_O26_CC2_MUTE_CTRL_11_T                         pe1_mute_ctrl_11;	//0xCC88190C
	BE_O26_CC2_MUTE_CTRL_12_T                         pe1_mute_ctrl_12;	//0xCC881910
	BE_O26_CC2_MUTE_CTRL_13_T                         pe1_mute_ctrl_13;	//0xCC881914
	BE_O26_CC2_MUTE_CTRL_14_T                         pe1_mute_ctrl_14;	//0xCC881918
	BE_O26_CC2_MUTE_CTRL_15_T                         pe1_mute_ctrl_15;	//0xCC88191C
	BE_O26_CC2_MUTE_CTRL_16_T                         pe1_mute_ctrl_16;	//0xCC881920
	BE_O26_CC2_MUTE_CTRL_17_T                         pe1_mute_ctrl_17;	//0xCC881924
	BE_O26_CC2_MUTE_CTRL_18_T                         pe1_mute_ctrl_18;	//0xCC881928
	BE_O26_CC2_MUTE_CTRL_19_T                         pe1_mute_ctrl_19;	//0xCC88192C
	BE_O26_CC2_MUTE_CTRL_20_T                         pe1_mute_ctrl_20;	//0xCC881930
	BE_O26_CC2_MUTE_CTRL_21_T                         pe1_mute_ctrl_21;	//0xCC881934
	BE_O26_CC2_MUTE_CTRL_22_T                         pe1_mute_ctrl_22;	//0xCC881938
	BE_O26_CC2_MUTE_CTRL_23_T                         pe1_mute_ctrl_23;	//0xCC88193C
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
	BE_O26_CC2_LOGO_CTRL_61_T                         pe1_logo_ctrl_61;	//0xCC881A00
	BE_O26_CC2_LOGO_CTRL_62_T                         pe1_logo_ctrl_62;	//0xCC881A04
	BE_O26_CC2_LOGO_CTRL_63_T                         pe1_logo_ctrl_63;	//0xCC881A08
	BE_O26_CC2_LOGO_CTRL_64_T                         pe1_logo_ctrl_64;	//0xCC881A0C
	BE_O26_CC2_LOGO_CTRL_65_T                         pe1_logo_ctrl_65;	//0xCC881A10
	BE_O26_CC2_LOGO_CTRL_66_T                         pe1_logo_ctrl_66;	//0xCC881A14
	BE_O26_CC2_LOGO_CTRL_67_T                         pe1_logo_ctrl_67;	//0xCC881A18
	BE_O26_CC2_LOGO_CTRL_68_T                         pe1_logo_ctrl_68;	//0xCC881A1C
	BE_O26_CC2_LOGO_CTRL_69_T                         pe1_logo_ctrl_69;	//0xCC881A20
	BE_O26_CC2_LOGO_CTRL_70_T                         pe1_logo_ctrl_70;	//0xCC881A24
	BE_O26_CC2_LOGO_CTRL_71_T                         pe1_logo_ctrl_71;	//0xCC881A28
	BE_O26_CC2_LOGO_CTRL_72_T                         pe1_logo_ctrl_72;	//0xCC881A2C
	BE_O26_CC2_LOGO_CTRL_73_T                         pe1_logo_ctrl_73;	//0xCC881A30
	BE_O26_CC2_LOGO_CTRL_74_T                         pe1_logo_ctrl_74;	//0xCC881A34
	BE_O26_CC2_LOGO_CTRL_75_T                         pe1_logo_ctrl_75;	//0xCC881A38
	BE_O26_CC2_LOGO_CTRL_76_T                         pe1_logo_ctrl_76;	//0xCC881A3C
	BE_O26_CC2_LOGO_CTRL_77_T                         pe1_logo_ctrl_77;	//0xCC881A40
	BE_O26_CC2_LOGO_CTRL_78_T                         pe1_logo_ctrl_78;	//0xCC881A44
	BE_O26_CC2_LOGO_CTRL_79_T                         pe1_logo_ctrl_79;	//0xCC881A48
	BE_O26_CC2_LOGO_CTRL_80_T                         pe1_logo_ctrl_80;	//0xCC881A4C
	BE_O26_CC2_LOGO_CTRL_81_T                         pe1_logo_ctrl_81;	//0xCC881A50
	BE_O26_CC2_LOGO_CTRL_82_T                         pe1_logo_ctrl_82;	//0xCC881A54
	BE_O26_CC2_LOGO_CTRL_83_T                         pe1_logo_ctrl_83;	//0xCC881A58
	BE_O26_CC2_LOGO_CTRL_84_T                         pe1_logo_ctrl_84;	//0xCC881A5C
	BE_O26_CC2_LOGO_CTRL_85_T                         pe1_logo_ctrl_85;	//0xCC881A60
	BE_O26_CC2_LOGO_CTRL_86_T                         pe1_logo_ctrl_86;	//0xCC881A64
	BE_O26_CC2_LOGO_CTRL_87_T                         pe1_logo_ctrl_87;	//0xCC881A68
	BE_O26_CC2_LOGO_CTRL_88_T                         pe1_logo_ctrl_88;	//0xCC881A6C
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
	BE_O26_CC2_MERGE_CTRL_00_T                       pe1_merge_ctrl_00;	//0xCC881AA0
	BE_O26_CC2_MERGE_CTRL_01_T                       pe1_merge_ctrl_01;	//0xCC881AA4
	BE_O26_CC2_MERGE_CTRL_02_T                       pe1_merge_ctrl_02;	//0xCC881AA8
	BE_O26_CC2_MERGE_CTRL_03_T                       pe1_merge_ctrl_03;	//0xCC881AAC
	BE_O26_CC2_MERGE_CTRL_04_T                       pe1_merge_ctrl_04;	//0xCC881AB0
	BE_O26_CC2_MERGE_CTRL_05_T                       pe1_merge_ctrl_05;	//0xCC881AB4
	BE_O26_CC2_MERGE_CTRL_06_T                       pe1_merge_ctrl_06;	//0xCC881AB8
	BE_O26_CC2_MERGE_CTRL_07_T                       pe1_merge_ctrl_07;	//0xCC881ABC
	BE_O26_CC2_MERGE_CTRL_08_T                       pe1_merge_ctrl_08;	//0xCC881AC0
	BE_O26_CC2_MERGE_CTRL_09_T                       pe1_merge_ctrl_09;	//0xCC881AC4
	BE_O26_CC2_MERGE_CTRL_10_T                       pe1_merge_ctrl_10;	//0xCC881AC8
	BE_O26_CC2_MERGE_CTRL_11_T                       pe1_merge_ctrl_11;	//0xCC881ACC
	BE_O26_CC2_MERGE_CTRL_12_T                       pe1_merge_ctrl_12;	//0xCC881AD0
	BE_O26_CC2_MERGE_CTRL_13_T                       pe1_merge_ctrl_13;	//0xCC881AD4
	BE_O26_CC2_MERGE_CTRL_14_T                       pe1_merge_ctrl_14;	//0xCC881AD8
	BE_O26_CC2_MERGE_CTRL_15_T                       pe1_merge_ctrl_15;	//0xCC881ADC
	BE_O26_CC2_MERGE_CTRL_16_T                       pe1_merge_ctrl_16;	//0xCC881AE0
	BE_O26_CC2_MERGE_CTRL_17_T                       pe1_merge_ctrl_17;	//0xCC881AE4
	BE_O26_CC2_MERGE_CTRL_18_T                       pe1_merge_ctrl_18;	//0xCC881AE8
	BE_O26_CC2_MERGE_CTRL_19_T                       pe1_merge_ctrl_19;	//0xCC881AEC
	BE_O26_CC2_MERGE_CTRL_20_T                       pe1_merge_ctrl_20;	//0xCC881AF0
	BE_O26_CC2_MERGE_CTRL_21_T                       pe1_merge_ctrl_21;	//0xCC881AF4
	BE_O26_CC2_MERGE_CTRL_22_T                       pe1_merge_ctrl_22;	//0xCC881AF8
	BE_O26_CC2_MERGE_CTRL_23_T                       pe1_merge_ctrl_23;	//0xCC881AFC
	BE_O26_CC2_MERGE_CTRL_24_T                       pe1_merge_ctrl_24;	//0xCC881B00
	BE_O26_CC2_MERGE_CTRL_25_T                       pe1_merge_ctrl_25;	//0xCC881B04
	BE_O26_CC2_MERGE_CTRL_26_T                       pe1_merge_ctrl_26;	//0xCC881B08
	BE_O26_CC2_MERGE_CTRL_27_T                       pe1_merge_ctrl_27;	//0xCC881B0C
	BE_O26_CC2_MERGE_CTRL_28_T                       pe1_merge_ctrl_28;	//0xCC881B10
	BE_O26_CC2_MERGE_CTRL_29_T                       pe1_merge_ctrl_29;	//0xCC881B14
	BE_O26_CC2_MERGE_CTRL_30_T                       pe1_merge_ctrl_30;	//0xCC881B18
	BE_O26_CC2_MERGE_CTRL_31_T                       pe1_merge_ctrl_31;	//0xCC881B1C
	BE_O26_CC2_MERGE_CTRL_32_T                       pe1_merge_ctrl_32;	//0xCC881B20
	BE_O26_CC2_MERGE_CTRL_33_T                       pe1_merge_ctrl_33;	//0xCC881B24
	BE_O26_CC2_MERGE_CTRL_34_T                       pe1_merge_ctrl_34;	//0xCC881B28
	BE_O26_CC2_MERGE_CTRL_35_T                       pe1_merge_ctrl_35;	//0xCC881B2C
	BE_O26_CC2_MERGE_CTRL_36_T                       pe1_merge_ctrl_36;	//0xCC881B30
	BE_O26_CC2_MERGE_CTRL_37_T                       pe1_merge_ctrl_37;	//0xCC881B34
	BE_O26_CC2_MERGE_CTRL_38_T                       pe1_merge_ctrl_38;	//0xCC881B38
	BE_O26_CC2_MERGE_CTRL_39_T                       pe1_merge_ctrl_39;	//0xCC881B3C
	BE_O26_CC2_MERGE_CTRL_40_T                       pe1_merge_ctrl_40;	//0xCC881B40
	BE_O26_CC2_MERGE_CTRL_41_T                       pe1_merge_ctrl_41;	//0xCC881B44
	BE_O26_CC2_MERGE_CTRL_42_T                       pe1_merge_ctrl_42;	//0xCC881B48
	BE_O26_CC2_MERGE_CTRL_43_T                       pe1_merge_ctrl_43;	//0xCC881B4C
	BE_O26_CC2_MERGE_CTRL_44_T                       pe1_merge_ctrl_44;	//0xCC881B50
	BE_O26_CC2_MERGE_CTRL_45_T                       pe1_merge_ctrl_45;	//0xCC881B54
	BE_O26_CC2_MERGE_CTRL_46_T                       pe1_merge_ctrl_46;	//0xCC881B58
	BE_O26_CC2_MERGE_CTRL_47_T                       pe1_merge_ctrl_47;	//0xCC881B5C
	BE_O26_CC2_MERGE_CTRL_48_T                       pe1_merge_ctrl_48;	//0xCC881B60
	BE_O26_CC2_MERGE_CTRL_49_T                       pe1_merge_ctrl_49;	//0xCC881B64
	BE_O26_CC2_MERGE_CTRL_50_T                       pe1_merge_ctrl_50;	//0xCC881B68
	BE_O26_CC2_MERGE_CTRL_51_T                       pe1_merge_ctrl_51;	//0xCC881B6C
	BE_O26_CC2_MERGE_CTRL_52_T                       pe1_merge_ctrl_52;	//0xCC881B70
	BE_O26_CC2_MERGE_CTRL_53_T                       pe1_merge_ctrl_53;	//0xCC881B74
	BE_O26_CC2_MERGE_CTRL_54_T                       pe1_merge_ctrl_54;	//0xCC881B78
	BE_O26_CC2_MERGE_CTRL_55_T                       pe1_merge_ctrl_55;	//0xCC881B7C
	BE_O26_CC2_MERGE_CTRL_56_T                       pe1_merge_ctrl_56;	//0xCC881B80
	BE_O26_CC2_MERGE_CTRL_57_T                       pe1_merge_ctrl_57;	//0xCC881B84
	BE_O26_CC2_MERGE_CTRL_58_T                       pe1_merge_ctrl_58;	//0xCC881B88
	BE_O26_CC2_MERGE_CTRL_59_T                       pe1_merge_ctrl_59;	//0xCC881B8C
	BE_O26_CC2_MERGE_CTRL_60_T                       pe1_merge_ctrl_60;	//0xCC881B90
	BE_O26_CC2_MERGE_CTRL_61_T                       pe1_merge_ctrl_61;	//0xCC881B94
	BE_O26_CC2_MERGE_CTRL_62_T                       pe1_merge_ctrl_62;	//0xCC881B98
	BE_O26_CC2_MERGE_CTRL_63_T                       pe1_merge_ctrl_63;	//0xCC881B9C
	BE_O26_CC2_MERGE_CTRL_64_T                       pe1_merge_ctrl_64;	//0xCC881BA0
	BE_O26_CC2_MERGE_CTRL_65_T                       pe1_merge_ctrl_65;	//0xCC881BA4
	BE_O26_CC2_MERGE_CTRL_66_T                       pe1_merge_ctrl_66;	//0xCC881BA8
	BE_O26_CC2_MERGE_CTRL_67_T                       pe1_merge_ctrl_67;	//0xCC881BAC
	BE_O26_CC2_MERGE_CTRL_68_T                       pe1_merge_ctrl_68;	//0xCC881BB0
	BE_O26_CC2_MERGE_CTRL_69_T                       pe1_merge_ctrl_69;	//0xCC881BB4
	BE_O26_CC2_MERGE_CTRL_70_T                       pe1_merge_ctrl_70;	//0xCC881BB8
	BE_O26_CC2_MERGE_CTRL_71_T                       pe1_merge_ctrl_71;	//0xCC881BBC
	BE_O26_CC2_MERGE_CTRL_72_T                       pe1_merge_ctrl_72;	//0xCC881BC0
	BE_O26_CC2_MERGE_CTRL_73_T                       pe1_merge_ctrl_73;	//0xCC881BC4
	BE_O26_CC2_MERGE_CTRL_74_T                       pe1_merge_ctrl_74;	//0xCC881BC8
} BE_O26A0_REG_CC2_T;

#endif
