#ifndef _PE_CHPI_CCO_REG_O26F22A0_H_
#define _PE_CHPI_CCO_REG_O26F22A0_H_

#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060320 RW 0x0200_0040
		UINT32 contrast 				   :16; //(15:0,RW,0x0000_0000) //
		UINT32 brightness				  :16;	//(31:16,RW,0x0000_0000) //
	};
	};
}PE_O26F22_CCO_VERI_SYS_VERI_8_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061004 RW 0x0200_8080
	UINT32 saturation_target                :8;	//(7:0,NA,0x80) //
	UINT32 saturation                       :8;	//(15:8,NA,0x80) //
	UINT32 brightness                       :10;	//(25:16,NA,0x200) //
	UINT32 resvd                            :6;
	};
	};
}PE_O26F22_PE1_VSPYC_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606DC RW 0x0080_8080
	UINT32 ihsv_hoffset                     :8;	//(7:0,NA,0x80) //reg_ihsv_hoffset	Hue offset : 0[-15degree] ~ 128[0 degree] ~ 255[15 degree]
	UINT32 ihsv_soffset                     :8;	//(15:8,NA,0x80) //reg_ihsv_soffset	Saturation offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 ihsv_voffset                     :8;	//(23:16,NA,0x80) //reg_ihsv_voffset	Value offset : 0[-128] ~ 128[0] ~255[127]
	UINT32 resvd                            :8;
	};
	};
}PE_O26F22_PE1_CEN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606D0 RW
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
	};
}PE_O26F22_PE1_CEN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606D4 RW
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
	};
}PE_O26F22_PE1_CEN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606D8 RW
	UINT32 ihsv_sgain                       :8;	//7:0	//reg_ihsv_sgain	Saturation Gain  : Gain 0[0]~128[x1] ~255[x2]
	UINT32 ihsv_vgain                       :8;	//15:8	//reg_ihsv_vgain	Value Gain : Gain 0[0]~128[x1] ~255[x2]
	UINT32 resvd                            :16;
	};
	};
}PE_O26F22_PE1_CEN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606E0 RW
	UINT32 reg_master_gain_cr0              :8;	//7:0	//Color region 0 master gain
	UINT32 reg_master_gain_cr1              :8;	//15:8	//Color region 1 master gain
	UINT32 reg_master_gain_cr2              :8;	//23:16	//Color region 2 master gain
	UINT32 reg_master_gain_cr3              :8;	//31:24	//Color region 3 master gain
	};
	};
}PE_O26F22_PE1_CEN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606E4 RW
	UINT32 reg_master_gain_cr4              :8;	//7:0	//Color region 4 master gain
	UINT32 reg_master_gain_cr5              :8;	//15:8	//Color region 5 master gain
	UINT32 reg_master_gain_cr6              :8;	//23:16	//Color region 6 master gain
	UINT32 reg_master_gain_cr7              :8;	//31:24	//Color region 7 master gain
	};
	};
}PE_O26F22_PE1_CEN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606E8 RW
	UINT32 reg_master_gain_cr8              :8;	//7:0	//Color region 8 master gain
	UINT32 reg_master_gain_cr9              :8;	//15:8	//Color region 9 master gain
	UINT32 reg_master_gain_cr10             :8;	//23:16	//Color region 10 master gain
	UINT32 reg_master_gain_cr11             :8;	//31:24	//Color region 11 master gain
	};
	};
}PE_O26F22_PE1_CEN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606EC RW
	UINT32 reg_master_gain_cr12             :8;	//7:0	//Color region 12 master gain
	UINT32 reg_master_gain_cr13             :8;	//15:8	//Color region 13 master gain
	UINT32 reg_master_gain_cr14             :8;	//23:16	//Color region 14 master gain
	UINT32 reg_master_gain_cr15             :8;	//31:24	//Color region 15 master gain
	};
	};
}PE_O26F22_PE1_CEN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060700 WO
	UINT32 hif_cen_address                  :8;	//7:0	//hif_cen_address	0 ~ 127
	UINT32 hif_cen_ai_sel                   :3;	//10:8	//reg_cen_ai_sel	'000'  H Color region table  :  range of address 0 ~ 127	'001'  S Color region table  :  range of address 0 ~ 127	'010'  V Color region table  :  range of address 0 ~ 127	'011'  Color of Region  : range of address 0 ~ 15	'110'  Global Delta gain : range of address 0 ~ 5
	UINT32 resvd0                           :1;
	UINT32 hif_cen_ai                       :1;	//12 //auto increment enable
	UINT32 resvd1                           :1;
	UINT32 hif_mem_off                      :1;	//14 //0' : memory enable	'1' : memory disable
	UINT32 hif_cen_enable                   :1;	//15 //0' : host access	'1' : local access
	UINT32 resvd2                           :16;
	};
	};
}PE_O26F22_PE1_CEN_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060704 RO
	UINT32 hif_cen_y_wdata                  :10;	//9:0	//
	UINT32 resvd0                           :6;
	UINT32 hif_cen_x_wdata                  :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CEN_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40606F8 RW/RO 0x0000_0000
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
	};
}PE_O26F22_PE1_CEN_UPD_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060708 WO
	UINT32 hif_cen_delta_address            :5;	//4:0	//hif_cen_delta_address	0 ~ 31
	UINT32 resvd0                           :7;
	UINT32 hif_cen_delta_ai                 :1;	//12 //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_cen_delta_enable             :1;	//15 //0' : host access mode	'1' : normal mode
	UINT32 resvd2                           :16;
	};
	};
}PE_O26F22_PE1_CEN_DELTA_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406070C RO
	UINT32 hif_cen_vr_data                  :8;	//7:0	//Region Delta V/R gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_sb_data                  :8;	//15:8	//Region Delta S/B gain : range of address (0,1) ~ (30,31)
	UINT32 hif_cen_hg_data                  :8;	//23:16	//Region Delta H/G gain : range of address (0,1) ~ (30,31)
	UINT32 resvd                            :8;
	};
	};
}PE_O26F22_PE1_CEN_DELTA_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610B0 RW
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
	};
}PE_O26F22_PE1_CW_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610B4 RW
	UINT32 user_ctrl_g_gain                 :8;	//7:0	//User Control, G_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_b_gain                 :8;	//15:8	//User Control, B_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 user_ctrl_r_gain                 :8;	//23:16	//User Control, R_Gain  (resolution = 2^(-9))	0xC0 := maps to 1.00
	UINT32 resvd                            :8;
	};
	};
}PE_O26F22_PE1_CW_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610B8 RW
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
	};
}PE_O26F22_PE1_CW_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610C0 RW
	UINT32 reg_crgn_hue_gain_y0             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610C4 RW
	UINT32 reg_crgn_hue_gain_y1             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610C8 RW
	UINT32 reg_crgn_hue_gain_y2             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610CC RW
	UINT32 reg_crgn_hue_gain_y3             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610D0 RW
	UINT32 reg_crgn_hue_gain_y4             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610D4 RW
	UINT32 reg_crgn_hue_gain_y5             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610D8 RW
	UINT32 reg_crgn_hue_gain_y6             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610DC RW
	UINT32 reg_crgn_hue_gain_y7             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610E0 RW
	UINT32 reg_crgn_sat_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x0             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x1             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610E4 RW
	UINT32 reg_crgn_sat_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x2             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x3             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610E8 RW
	UINT32 reg_crgn_sat_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x4             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x5             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610EC RW
	UINT32 reg_crgn_sat_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x6             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x7             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610F0 RW
	UINT32 reg_crgn_val_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x0             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x1             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610F4 RW
	UINT32 reg_crgn_val_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x2             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x3             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610F8 RW
	UINT32 reg_crgn_val_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x4             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x5             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40610FC RW
	UINT32 reg_crgn_val_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x6             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x7             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_CW_CRGN_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061034 RW
	UINT32 reg_objt_gain_y0                 :8;	//7:0	//
	UINT32 reg_objt_gain_x0                 :8;	//15:8	//
	UINT32 reg_objt_gain_y1                 :8;	//23:16	//
	UINT32 reg_objt_gain_x1                 :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CC_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061038 RW
	UINT32 reg_objt_gain_y2                 :8;	//7:0	//
	UINT32 reg_objt_gain_x2                 :8;	//15:8	//
	UINT32 reg_objt_gain_y3                 :8;	//23:16	//
	UINT32 reg_objt_gain_x3                 :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CC_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406103C RO
	UINT32 reg_face_gain_y0                 :8;	//7:0	//
	UINT32 reg_face_gain_x0                 :8;	//15:8	//
	UINT32 reg_face_gain_y1                 :8;	//23:16	//
	UINT32 reg_face_gain_x1                 :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CC_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061040 RW
	UINT32 reg_face_gain_y2                 :8;	//7:0	//
	UINT32 reg_face_gain_x2                 :8;	//15:8	//
	UINT32 reg_face_gain_y3                 :8;	//23:16	//
	UINT32 reg_face_gain_x3                 :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CC_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061050 RW
	UINT32 reg_crgn_hue_gain_y0             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x0             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061054 RW
	UINT32 reg_crgn_hue_gain_y1             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x1             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061058 RW
	UINT32 reg_crgn_hue_gain_y2             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x2             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406105C RW
	UINT32 reg_crgn_hue_gain_y3             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x3             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061060 RW
	UINT32 reg_crgn_hue_gain_y4             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x4             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061064 RW
	UINT32 reg_crgn_hue_gain_y5             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x5             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061068 RW
	UINT32 reg_crgn_hue_gain_y6             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x6             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406106C RW
	UINT32 reg_crgn_hue_gain_y7             :8;	//7:0	//
	UINT32 resvd0                           :8;
	UINT32 reg_crgn_hue_gain_x7             :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061070 RW
	UINT32 reg_crgn_sat_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x0             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x1             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061074 RW
	UINT32 reg_crgn_sat_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x2             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x3             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061078 RW
	UINT32 reg_crgn_sat_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x4             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x5             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406107C RW
	UINT32 reg_crgn_sat_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_sat_gain_x6             :7;	//14:8	//
	UINT32 resvd0                           :1;
	UINT32 reg_crgn_sat_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_sat_gain_x7             :7;	//30:24	//
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061080 RW
	UINT32 reg_crgn_val_gain_y0             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x0             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y1             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x1             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061084 RW
	UINT32 reg_crgn_val_gain_y2             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x2             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y3             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x3             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061088 RW
	UINT32 reg_crgn_val_gain_y4             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x4             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y5             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x5             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406108C RO
	UINT32 reg_crgn_val_gain_y6             :8;	//7:0	//
	UINT32 reg_crgn_val_gain_x6             :8;	//15:8	//
	UINT32 reg_crgn_val_gain_y7             :8;	//23:16	//
	UINT32 reg_crgn_val_gain_x7             :8;	//31:24	//
	};
	};
}PE_O26F22_PE1_VSP_CRGN_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060774 RW 0x8000_0301
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
	};
}PE_O26F22_PE1_DSE_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060778 RW 0x03FF_03FF
	UINT32 hif_dse_wdata_y_32nd             :10;	//(9:0,NA,0x3FF) //Y coordinate of 32nd control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x_32nd             :10;	//(25:16,NA,0x3FF) //X coordinate of 32nd control point
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_DSE_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406077C RW 0x0000_8000
	UINT32 hif_dse_address                  :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_dse_load                     :1;	//(8,NA,0x0) //write done of dce register (auto cleared)
	UINT32 resvd1                           :3;
	UINT32 hif_dse_ai                       :1;	//(12,NA,0x0) //auto increment enable	'1' : enable
	UINT32 resvd2                           :2;
	UINT32 hif_dse_enable                   :1;	//(15,NA,0x1) //0' : host access(read/write)	'1' : normal operation
	UINT32 resvd3                           :16;
	};
	};
}PE_O26F22_PE1_DSE_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060780 RO 0x0000_0000
	UINT32 hif_dse_wdata_y                  :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_dse_wdata_x                  :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_DSE_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406078C RW 0x0000_3C00
	UINT32 reg_y_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt0_x               :10;	//(17:8,NA,0x3C) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060790 RW 0x0000_C88C
	UINT32 reg_y_region_pt1_y               :8;	//(7:0,NA,0x8C) //
	UINT32 reg_y_region_pt1_x               :10;	//(17:8,NA,0xC8) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060794 RW 0x0001_40FF
	UINT32 reg_y_region_pt2_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt2_x               :10;	//(17:8,NA,0x140) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060798 RW 0x0001_90FF
	UINT32 reg_y_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt3_x               :10;	//(17:8,NA,0x190) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406079C RW 0x0002_BCFF
	UINT32 reg_y_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_y_region_pt4_x               :10;	//(17:8,NA,0x2BC) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607A0 RW 0x0003_4878
	UINT32 reg_y_region_pt5_y               :8;	//(7:0,NA,0x78) //
	UINT32 reg_y_region_pt5_x               :10;	//(17:8,NA,0x348) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607A4 RW 0x0003_703C
	UINT32 reg_y_region_pt6_y               :8;	//(7:0,NA,0x3C) //
	UINT32 reg_y_region_pt6_x               :10;	//(17:8,NA,0x370) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607A8 RW 0x0003_9800
	UINT32 reg_y_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_y_region_pt7_x               :10;	//(17:8,NA,0x398) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_Y_REGION_PT7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607AC RW 0x0001_F100
	UINT32 reg_h_region_pt0_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt0_x               :10;	//(17:8,NA,0x1F1) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT0_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607B0 RW 0x0002_00BE
	UINT32 reg_h_region_pt1_y               :8;	//(7:0,NA,0xBE) //
	UINT32 reg_h_region_pt1_x               :10;	//(17:8,NA,0x200) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT1_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607B4 RW 0x0002_0DF0
	UINT32 reg_h_region_pt2_y               :8;	//(7:0,NA,0xF0) //
	UINT32 reg_h_region_pt2_x               :10;	//(17:8,NA,0x20D) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607B8 RW 0x0002_14FF
	UINT32 reg_h_region_pt3_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt3_x               :10;	//(17:8,NA,0x214) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT3_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607BC RW 0x0002_28FF
	UINT32 reg_h_region_pt4_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt4_x               :10;	//(17:8,NA,0x228) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT4_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607C0 RW 0x0002_30FF
	UINT32 reg_h_region_pt5_y               :8;	//(7:0,NA,0xFF) //
	UINT32 reg_h_region_pt5_x               :10;	//(17:8,NA,0x230) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT5_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607C4 RW 0x0002_3FA0
	UINT32 reg_h_region_pt6_y               :8;	//(7:0,NA,0xA0) //
	UINT32 reg_h_region_pt6_x               :10;	//(17:8,NA,0x23F) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT6_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607C8 RW 0x0002_4000
	UINT32 reg_h_region_pt7_y               :8;	//(7:0,NA,0x00) //
	UINT32 reg_h_region_pt7_x               :10;	//(17:8,NA,0x240) //
	UINT32 resvd                            :14;
	};
	};
}PE_O26F22_PE_DSE_H_REGION_PT7_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060754 RW 0x0200_0200
	UINT32 dce_cb_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cb_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :2;
	UINT32 chroma_gain_enable               :1;	//(28,NA,0x0) //enable
	UINT32 resvd2                           :3;
	};
	};
}PE_O26F22_PE1_DCE_CHR_GAIN_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060324 RW 0x0000_0000
	UINT32 dce_cb_gain2 					:10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0							:6;
	UINT32 dce_cb_gain1 					:10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1							:2;
	UINT32 chroma_gain_enable				:1; //(28,NA,0x0) //enable
	UINT32 resvd2							:3;
	};
	};
}PE_O26F22_PE1_CCO_VERI_SYS_VERI_9_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406075C RW 0x0200_0200
	UINT32 dce_cr_gain2                     :10;	//(9:0,NA,0x200) //gain, when y_dce_in < y_dce_out
	UINT32 resvd0                           :6;
	UINT32 dce_cr_gain1                     :10;	//(25:16,NA,0x200) //gain, when y_dce_in >= y_dce_out
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_DCE_CHR_GAIN2_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3020370 RW 0x0000_0000
	UINT32 DynamicContrastOnOffFromUI       :8;
	UINT32 sBlackStabilizerUI               :8;
	UINT32 sWhiteStabilizerUI               :8;
	UINT32 isGameOptimizationMode           :8;
	};
	};
}PE_O26F22_CCO1_VERI_28_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3020374 RW 0x0000_0000
	UINT32 gIsAiGenreEnable                 :8;
	UINT32 gIsAiSceneEnable                 :8;
	UINT32 gAiSceneValue                    :8;
	UINT32 gHdrType                         :8;
	};
	};
}PE_O26F22_CCO1_VERI_29_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3020378 RW 0x0000_0000
	UINT32 gGenreGain_DC                    :32;	//31:0	//
	};
	};
}PE_O26F22_CCO1_VERI_30_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF302037C RW 0x0000_0000
	UINT32 DynCont_Index                    :8;
	UINT32 Apl_Index                        :8;
	UINT32 AI_Gain_Index                    :8;
	UINT32 Stabilizer_Gain_Index            :8;
	};
	};
}PE_O26F22_CCO1_VERI_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3020380 RW 0x0000_0000
	UINT32 Depth_Dc_Bright_Gain             :32;
	};
	};
}PE_O26F22_CCO1_VERI_32_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3020384 RW 0x0000_0000
	UINT32 Depth_Dc_Dark_Gain             :32;
	};
	};
}PE_O26F22_CCO1_VERI_33_T;


typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3031070 RW 0x0000_0000
	UINT32 luminance_lut_enable             :1;	//(0,NA,0x0) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,NA,0x0) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,NA,0x0) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,NA,0x0) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,NA,0x0) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,NA,0x0) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,NA,0x0) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :3;
	UINT32 window_cg_disable                :1;	//(20,NA,0x0) //clock gating disable
	UINT32 resvd3                           :11;
	};
	};
}PE_O26F22_DTM_LLUT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3031084 RW 0x03FF_03FF
	UINT32 hif_llut_wdata_y_33rd            :10;	//(9:0,NA,0x3FF) //Y coordinate of 33rd control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut_wdata_x_33rd            :10;	//(25:16,NA,0x3FF) //X coordinate of 33rd control point
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_DTM_LLUT_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3031088 RW 0x0000_8000
	UINT32 hif_llut0_address                :5;	//(4:0,NA,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :3;
	UINT32 hif_llut0_load                   :1;	//(8,NA,0x0) //write done of hdr register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load            :1;	//(11,NA,0x0) //0 : LUT load at vactive falling, when hif_llut0_load = 1	1 : LUT load at "hif_llut0_load = 1"
	UINT32 hif_llut0_ai                     :1;	//(12,NA,0x0) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_llut0_enable                 :1;	//(15,NA,0x1) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
	};
}PE_O26F22_DTM_LLUT0_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF303108C RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :10;	//(9:0,NA,0x000) //Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_llut0_wdata_x                :10;	//(25:16,NA,0x000) //X coordinate of control point
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_DTM_LLUT0_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30310A0 RW 0x0000_0000
	UINT32 reg_lut_lum_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_lum_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_lum_x0                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_DTM_LUT_LUM_SAT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30310A4 RW 0x0000_0000
	UINT32 reg_lut_lum_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_lum_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_lum_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_lum_y0                   :8;	//(31:24,NA,0x80) //
	};
	};
}PE_O26F22_DTM_LUT_LUM_SAT_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30310A8 RW 0x0000_0000
	UINT32 reg_lut_sat_x3                   :8;	//(7:0,NA,0xFF) //
	UINT32 reg_lut_sat_x2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_x1                   :8;	//(23:16,NA,0x40) //
	UINT32 reg_lut_sat_x0                   :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_DTM_LUT_LUM_SAT_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30310AC RW 0x0000_0000
	UINT32 reg_lut_sat_y3                   :8;	//(7:0,NA,0x80) //
	UINT32 reg_lut_sat_y2                   :8;	//(15:8,NA,0x80) //
	UINT32 reg_lut_sat_y1                   :8;	//(23:16,NA,0x80) //
	UINT32 reg_lut_sat_y0                   :8;	//(31:24,NA,0x80) //
	};
	};
}PE_O26F22_DTM_LUT_LUM_SAT_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF30310E0 RW 0xFF00_0000
	UINT32 reg_hue_prsv_en                  :1;	//(0,NA,0x0) //enable pin for hue restoration
	UINT32 resvd0                           :3;
	UINT32 reg_sat_prsv_en                  :1;	//(4,NA,0x0) //enable pin for saturation preserving
	UINT32 reg_hue_prsv_detour              :1;	//(5,NA,0x0) //preserving detour
	UINT32 resvd1                           :6;
	UINT32 reg_hue_prsv_cg_disable          :1;	//(12,NA,0x0) //clock gating disable
	UINT32 resvd2                           :3;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //0:bypass, 255:restored sat
	UINT32 reg_hue_prsv_ratio               :8;	//(31:24,NA,0xFF) //0:bypass, 255:restored hue
	};
	};
}PE_O26F22_DTM_HUE_SAT_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060524 RW
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
	};
}PE_O26F22_PE1_FSW_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3410BF0 RW
	UINT32 drc_apb_write_cont			:2;		//1:0	drc curv update counter
	UINT32 dnr_decont					:1;
	UINT32 drc_write_cont				:2;		//4:3	drc curv update counter
	UINT32 reserved						:3;
	UINT32 reg_pre_norm					:8;		//15:8	IWP - iir weight prev norm
	UINT32 reg_cur_norm					:8;		//23:16	IWC - iir weight cur  norm
	UINT32 reg_pre_sc					:8;		//31:24	IWSP - iir weight scene change prev sc
	};
	};
}PE_O26F22_VSD1_SHP_FSW_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3410BF4 RW
	UINT32 reg_cur_sc						:8;		//7:0	IWSC - iir weight scene change cur sc
	UINT32 reg_ui_gain_w					:8;		//15:8	UGW - ui gain white
	UINT32 reg_ui_gain_b					:8;		//23:16 UGB - ui gain black
	UINT32 reg_vy_mode                      :8;		//31:24 ui rgb select
	};
	};
}PE_O26F22_VSD1_SHP_FSW_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3410BF5 RW
	UINT32 reg_obc_debug                    :2;		//1:0	0: shp result   1 : face map   2 : object map
	UINT32 resvd0							:30;
	};
	};
}PE_O26F22_VSD1_SHP_FSW_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030B00, 0xF0176868 RW
	UINT32 enable                           :1;	//0 //
	UINT32 resvd0                           :7;
	UINT32 center_position                  :8;	//15:8	//
	UINT32 contrast                         :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_VCP0_DISP_VSP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3030B04, 0xF017686C RW
	UINT32 resvd0                           :8;
	UINT32 saturation                       :8;	//15:8	//
	UINT32 brightness                       :10;	//25:16	//
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_VCP0_DISP_VSP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3410F00, 0xF0176868 RW
		UINT32 enable							:1; //0 //
		UINT32 resvd0							:3;
		UINT32 brightness						:10;	//13:4	//
		UINT32 resvd1							:2;
		UINT32 contrast 						:10;	//25:16 //
		UINT32 resvd2							:6;
	};
	};
}PE_O26F22_VCP1_DISP_VSP_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF3410F04, 0xF017686C RW
		UINT32 saturation_en				:1; //0 //
		UINT32 resvd0							:7;
		UINT32 saturation						:8; //15:8	//
		UINT32 brightness						:10;	//25:16 //
		UINT32 resvd1							:6;

	};
	};
}PE_O26F22_VCP1_DISP_VSP_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060950 RW 0x0000_0000
	UINT32 ll_lut_addr                      :7;	//(6:0,NA,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
	};
}PE_O26F22_PE1_LLLUT_E_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060954 RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
	};
}PE_O26F22_PE1_LLLUT_E_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060958 RW 0x0000_0000
	UINT32 ll_lut_addr                      :7;	//(6:0,NA,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,NA,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
	};
}PE_O26F22_PE1_LLLUT_O_IA_CTRL_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406095C RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,NA,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,NA,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
	};
}PE_O26F22_PE1_LLLUT_O_IA_DATA_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060960 RW 0x0000_0100
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
	};
}PE_O26F22_PE1_LLCORE_CTRL_00_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060964 RW 0x0000_1000
	UINT32 reg_llpcc_coef0                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 0
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef1                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 1
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_01_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060968 RW 0x0000_0000
	UINT32 reg_llpcc_coef2                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 2
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef3                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 3
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_02_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406096C RW 0x0000_0000
	UINT32 reg_llpcc_coef4                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 4
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef5                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 5
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_03_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060970 RW 0x0000_0000
	UINT32 reg_llpcc_coef6                  :15;	//(14:0,NA,0x0000) //PCC10 Coefficient 6
	UINT32 resvd0                           :1;
	UINT32 reg_llpcc_coef7                  :15;	//(30:16,NA,0x0000) //PCC10 Coefficient 7
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_04_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060974 RW 0x0AD9_1000
	UINT32 reg_llpcc_coef8                  :15;	//(14:0,NA,0x1000) //PCC10 Coefficient 8
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(30:16,NA,0x0AD9) //alpha blendling RGB -> Y coef0
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_05_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060978 RW 0x0434_00F3
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(14:0,NA,0x00F3) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(30:16,NA,0x0434) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_06_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406097C RW 0x0000_0000
	UINT32 reg_llab_lut_y0                  :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x0                  :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060980 RW 0x0009_0009
	UINT32 reg_llab_lut_y1                  :10;	//(9:0,NA,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x1                  :10;	//(25:16,NA,0x9) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060984 RW 0x000A_0200
	UINT32 reg_llab_lut_y2                  :10;	//(9:0,NA,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x2                  :10;	//(25:16,NA,0xA) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060988 RW 0x000B_03FF
	UINT32 reg_llab_lut_y3                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x3                  :10;	//(25:16,NA,0xB) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406098C RW 0x03FF_03FF
	UINT32 reg_llab_lut_y4                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x4                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060990 RW 0x03FF_03FF
	UINT32 reg_llab_lut_y5                  :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_llab_lut_x5                  :10;	//(25:16,NA,0x3FF) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060994 RW 0x0000_00FF
	UINT32 reg_hue_prsv_ratio               :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_sat_prsv_ratio               :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
	};
}PE_O26F22_PE1_LLCORE_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40607FC RW 0x00000000
	UINT32 reg_drc_apl_lut_x1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x0               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_07_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060800 RW 0x00000000
	UINT32 reg_drc_apl_lut_x3               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_drc_apl_lut_x2               :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_08_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060804 RW 0x00000000
	UINT32 reg_drc_apl_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_apl_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_apl_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_apl_lut_y0               :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_09_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060808 RW 0x00000000
	UINT32 reg_drc_txt_lut_x3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_x2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_x1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_x0               :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_10_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406080C RW 0x00000000
	UINT32 reg_drc_txt_lut_y3               :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_txt_lut_y2               :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_txt_lut_y1               :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_txt_lut_y0               :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_11_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060810 RW 0x00000000
	UINT32 reg_drc_dark_lut_x3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_x2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_x1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_x0              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_12_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060814 RW 0x00000000
	UINT32 reg_drc_dark_lut_y3              :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_dark_lut_y2              :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_dark_lut_y1              :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_dark_lut_y0              :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_13_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4060818 RW 0x00000000
	UINT32 reg_drc_bright_lut_x3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_x2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_x1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_x0            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_14_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406081C RW 0x00000000
	UINT32 reg_drc_bright_lut_y3            :8;	//(7:0,NA,0x0) //
	UINT32 reg_drc_bright_lut_y2            :8;	//(15:8,NA,0x0) //
	UINT32 reg_drc_bright_lut_y1            :8;	//(23:16,NA,0x0) //
	UINT32 reg_drc_bright_lut_y0            :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC_PE1_DRC_CTRL_15_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406148C RW 0x0000_4040
	UINT32 reg_headgain_y1_i                :8;	//(7:0,NA,0x40) //head gain LUT
	UINT32 reg_headgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_headgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_headgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_31_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061490 RW 0x8080_FFFF
	UINT32 reg_headgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_headgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_headgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_headgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_32_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061494 RW 0x0000_4040
	UINT32 reg_bodygain_y1_i                :8;	//(7:0,NA,0x40) //body gain LUT
	UINT32 reg_bodygain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_bodygain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_bodygain_x0_i                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_33_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF4061498 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_bodygain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_bodygain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_bodygain_x2_i                :8;	//(31:24,NA,0x80) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_34_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF406149C RW 0x0000_4040
	UINT32 reg_textgain_y1_i                :8;	//(7:0,NA,0x40) //texture gain LUT
	UINT32 reg_textgain_x1_i                :8;	//(15:8,NA,0x40) //
	UINT32 reg_textgain_y0_i                :8;	//(23:16,NA,0x0) //
	UINT32 reg_textgain_x0_i                :8;	//(31:24,NA,0x0) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_35_T;

typedef struct {
	UINT32 uaddr32;
	union {
	UINT32 udata32;
	struct {						//0xF40614A0 RW 0x8080_FFFF
	UINT32 reg_textgain_y3_i                :8;	//(7:0,NA,0xFF) //
	UINT32 reg_textgain_x3_i                :8;	//(15:8,NA,0xFF) //
	UINT32 reg_textgain_y2_i                :8;	//(23:16,NA,0x80) //
	UINT32 reg_textgain_x2_i                :8;	//(31:24,NA,0x80) //
	};
	};
}PE_O26F22_CC2_PE1_MERGE_CTRL_36_T;

typedef struct
{
	PE_O26F22_CCO_VERI_SYS_VERI_8_T                   cco_veri_sys_veri_8;	//0xF4060320
	PE_O26F22_PE1_VSPYC_CTRL_01_T                     pe1_vspyc_ctrl_01;	//0xF4061004
	PE_O26F22_PE1_CEN_CTRL_03_T                         pe1_cen_ctrl_03;	//0xF40606DC
}PE_CHPI_CMN0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_CEN_IA_CTRL_T                      pe1_cen_ia_ctrl_s0;	//0xF4060700
	PE_O26F22_PE1_CEN_IA_DATA_T                   pe1_cen_ia_data0[128];	//0xF4060704
	PE_O26F22_PE1_CEN_IA_CTRL_T                      pe1_cen_ia_ctrl_s1;	//0xF4060700
	PE_O26F22_PE1_CEN_IA_DATA_T                   pe1_cen_ia_data1[128];	//0xF4060704
	PE_O26F22_PE1_CEN_IA_CTRL_T                      pe1_cen_ia_ctrl_s2;	//0xF4060700
	PE_O26F22_PE1_CEN_IA_DATA_T                   pe1_cen_ia_data2[128];	//0xF4060704
	PE_O26F22_PE1_CEN_IA_CTRL_T                      pe1_cen_ia_ctrl_s3;	//0xF4060700
	PE_O26F22_PE1_CEN_IA_DATA_T                    pe1_cen_ia_data3[16];	//0xF4060704
	PE_O26F22_PE1_CEN_IA_CTRL_T                      pe1_cen_ia_ctrl_s6;	//0xF4060700
	PE_O26F22_PE1_CEN_IA_DATA_T                     pe1_cen_ia_data6[6];	//0xF4060704
	PE_O26F22_PE1_CEN_IA_CTRL_T                       pe1_cen_ia_ctrl_e;	//0xF4060700
	PE_O26F22_PE1_CEN_UPD_CTRL_T                       pe1_cen_upd_ctrl;	//0xF40606F8
}PE_CHPI_CEN0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_CEN_CTRL_00_T                         pe1_cen_ctrl_00;	//0xF40606D0
	PE_O26F22_PE1_CEN_CTRL_01_T                         pe1_cen_ctrl_01;	//0xF40606D4
	PE_O26F22_PE1_CEN_CTRL_02_T                         pe1_cen_ctrl_02;	//0xF40606D8
	PE_O26F22_PE1_CEN_CTRL_04_T                         pe1_cen_ctrl_04;	//0xF40606E0
	PE_O26F22_PE1_CEN_CTRL_05_T                         pe1_cen_ctrl_05;	//0xF40606E4
	PE_O26F22_PE1_CEN_CTRL_06_T                         pe1_cen_ctrl_06;	//0xF40606E8
	PE_O26F22_PE1_CEN_CTRL_07_T                         pe1_cen_ctrl_07;	//0xF40606EC
	PE_O26F22_PE1_CEN_DELTA_IA_CTRL_T           pe1_cen_delta_ia_ctrl_s;	//0xF4060708
	PE_O26F22_PE1_CEN_DELTA_IA_DATA_T         pe1_cen_delta_ia_data[32];	//0xF406070C
	PE_O26F22_PE1_CEN_DELTA_IA_CTRL_T           pe1_cen_delta_ia_ctrl_e;	//0xF4060708
}PE_CHPI_CEN1_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_CW_CTRL_00_T                           pe1_cw_ctrl_00;	//0xF40610B0
	PE_O26F22_PE1_CW_CTRL_01_T                           pe1_cw_ctrl_01;	//0xF40610B4
	PE_O26F22_PE1_CW_CTRL_02_T                           pe1_cw_ctrl_02;	//0xF40610B8
	PE_O26F22_PE1_CW_CRGN_CTRL_00_T                 pe1_cw_crgn_ctrl_00;	//0xF40610C0
	PE_O26F22_PE1_CW_CRGN_CTRL_01_T                 pe1_cw_crgn_ctrl_01;	//0xF40610C4
	PE_O26F22_PE1_CW_CRGN_CTRL_02_T                 pe1_cw_crgn_ctrl_02;	//0xF40610C8
	PE_O26F22_PE1_CW_CRGN_CTRL_03_T                 pe1_cw_crgn_ctrl_03;	//0xF40610CC
	PE_O26F22_PE1_CW_CRGN_CTRL_04_T                 pe1_cw_crgn_ctrl_04;	//0xF40610D0
	PE_O26F22_PE1_CW_CRGN_CTRL_05_T                 pe1_cw_crgn_ctrl_05;	//0xF40610D4
	PE_O26F22_PE1_CW_CRGN_CTRL_06_T                 pe1_cw_crgn_ctrl_06;	//0xF40610D8
	PE_O26F22_PE1_CW_CRGN_CTRL_07_T                 pe1_cw_crgn_ctrl_07;	//0xF40610DC
	PE_O26F22_PE1_CW_CRGN_CTRL_08_T                 pe1_cw_crgn_ctrl_08;	//0xF40610E0
	PE_O26F22_PE1_CW_CRGN_CTRL_09_T                 pe1_cw_crgn_ctrl_09;	//0xF40610E4
	PE_O26F22_PE1_CW_CRGN_CTRL_10_T                 pe1_cw_crgn_ctrl_10;	//0xF40610E8
	PE_O26F22_PE1_CW_CRGN_CTRL_11_T                 pe1_cw_crgn_ctrl_11;	//0xF40610EC
	PE_O26F22_PE1_CW_CRGN_CTRL_12_T                 pe1_cw_crgn_ctrl_12;	//0xF40610F0
	PE_O26F22_PE1_CW_CRGN_CTRL_13_T                 pe1_cw_crgn_ctrl_13;	//0xF40610F4
	PE_O26F22_PE1_CW_CRGN_CTRL_14_T                 pe1_cw_crgn_ctrl_14;	//0xF40610F8
	PE_O26F22_PE1_CW_CRGN_CTRL_15_T                 pe1_cw_crgn_ctrl_15;	//0xF40610FC
}PE_CHPI_CW0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_VSP_CC_CTRL_01_T                    pe1_vsp_cc_ctrl_01;	//0xF4061034
	PE_O26F22_PE1_VSP_CC_CTRL_02_T                    pe1_vsp_cc_ctrl_02;	//0xF4061038
	PE_O26F22_PE1_VSP_CC_CTRL_03_T                    pe1_vsp_cc_ctrl_03;	//0xF406103C
	PE_O26F22_PE1_VSP_CC_CTRL_04_T                    pe1_vsp_cc_ctrl_04;	//0xF4061040
	PE_O26F22_PE1_VSP_CRGN_CTRL_00_T                pe1_vsp_crgn_ctrl_00;	//0xF4061050
	PE_O26F22_PE1_VSP_CRGN_CTRL_01_T                pe1_vsp_crgn_ctrl_01;	//0xF4061054
	PE_O26F22_PE1_VSP_CRGN_CTRL_02_T                pe1_vsp_crgn_ctrl_02;	//0xF4061058
	PE_O26F22_PE1_VSP_CRGN_CTRL_03_T                pe1_vsp_crgn_ctrl_03;	//0xF406105C
	PE_O26F22_PE1_VSP_CRGN_CTRL_04_T                pe1_vsp_crgn_ctrl_04;	//0xF4061060
	PE_O26F22_PE1_VSP_CRGN_CTRL_05_T                pe1_vsp_crgn_ctrl_05;	//0xF4061064
	PE_O26F22_PE1_VSP_CRGN_CTRL_06_T                pe1_vsp_crgn_ctrl_06;	//0xF4061068
	PE_O26F22_PE1_VSP_CRGN_CTRL_07_T                pe1_vsp_crgn_ctrl_07;	//0xF406106C
	PE_O26F22_PE1_VSP_CRGN_CTRL_08_T                pe1_vsp_crgn_ctrl_08;	//0xF4061070
	PE_O26F22_PE1_VSP_CRGN_CTRL_09_T                pe1_vsp_crgn_ctrl_09;	//0xF4061074
	PE_O26F22_PE1_VSP_CRGN_CTRL_10_T                pe1_vsp_crgn_ctrl_10;	//0xF4061078
	PE_O26F22_PE1_VSP_CRGN_CTRL_11_T                pe1_vsp_crgn_ctrl_11;	//0xF406107C
	PE_O26F22_PE1_VSP_CRGN_CTRL_12_T                pe1_vsp_crgn_ctrl_12;	//0xF4061080
	PE_O26F22_PE1_VSP_CRGN_CTRL_13_T                pe1_vsp_crgn_ctrl_13;	//0xF4061084
	PE_O26F22_PE1_VSP_CRGN_CTRL_14_T                pe1_vsp_crgn_ctrl_14;	//0xF4061088
	PE_O26F22_PE1_VSP_CRGN_CTRL_15_T                pe1_vsp_crgn_ctrl_15;	//0xF406108C
}PE_CHPI_VSP0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_DSE_CTRL_01_T                           pe1_dse_ctrl_01;	//0xF4060774
	PE_O26F22_PE1_DSE_CTRL_02_T                           pe1_dse_ctrl_02;	//0xF4060778
	PE_O26F22_PE1_DSE_IA_CTRL_T                         pe1_dse_ia_ctrl_s;	//0xF406077C
	PE_O26F22_PE1_DSE_IA_DATA_T                       pe1_dse_ia_data[32];	//0xF4060780
	PE_O26F22_PE1_DSE_IA_CTRL_T                         pe1_dse_ia_ctrl_e;	//0xF406077C
	PE_O26F22_PE_DSE_Y_REGION_PT0_T                   pe_dse_y_region_pt0;	//0xF406078C
	PE_O26F22_PE_DSE_Y_REGION_PT1_T                   pe_dse_y_region_pt1;	//0xF4060790
	PE_O26F22_PE_DSE_Y_REGION_PT2_T                   pe_dse_y_region_pt2;	//0xF4060794
	PE_O26F22_PE_DSE_Y_REGION_PT3_T                   pe_dse_y_region_pt3;	//0xF4060798
	PE_O26F22_PE_DSE_Y_REGION_PT4_T                   pe_dse_y_region_pt4;	//0xF406079C
	PE_O26F22_PE_DSE_Y_REGION_PT5_T                   pe_dse_y_region_pt5;	//0xF40607A0
	PE_O26F22_PE_DSE_Y_REGION_PT6_T                   pe_dse_y_region_pt6;	//0xF40607A4
	PE_O26F22_PE_DSE_Y_REGION_PT7_T                   pe_dse_y_region_pt7;	//0xF40607A8
	PE_O26F22_PE_DSE_H_REGION_PT0_T                   pe_dse_h_region_pt0;	//0xF40607AC
	PE_O26F22_PE_DSE_H_REGION_PT1_T                   pe_dse_h_region_pt1;	//0xF40607B0
	PE_O26F22_PE_DSE_H_REGION_PT2_T                   pe_dse_h_region_pt2;	//0xF40607B4
	PE_O26F22_PE_DSE_H_REGION_PT3_T                   pe_dse_h_region_pt3;	//0xF40607B8
	PE_O26F22_PE_DSE_H_REGION_PT4_T                   pe_dse_h_region_pt4;	//0xF40607BC
	PE_O26F22_PE_DSE_H_REGION_PT5_T                   pe_dse_h_region_pt5;	//0xF40607C0
	PE_O26F22_PE_DSE_H_REGION_PT6_T                   pe_dse_h_region_pt6;	//0xF40607C4
	PE_O26F22_PE_DSE_H_REGION_PT7_T                   pe_dse_h_region_pt7;	//0xF40607C8
}PE_CHPI_DSE0_O26F22_T;

typedef struct
{
	PE_O26F22_CCO1_VERI_28_T                                  sys_veri_28;	//0xF3020370
	PE_O26F22_CCO1_VERI_29_T                                  sys_veri_29;	//0xF3020374
	PE_O26F22_CCO1_VERI_30_T                                  sys_veri_30;	//0xF3020378
	PE_O26F22_CCO1_VERI_31_T                                  sys_veri_31;	//0xF302037C
	PE_O26F22_CCO1_VERI_32_T                                  sys_veri_32;	//0xF3020380
	PE_O26F22_CCO1_VERI_33_T                                  sys_veri_33;	//0xF3020384
}PE_CHPI_DCE0_O26F22_T;

typedef struct
{
	PE_O26F22_DTM_LLUT_CTRL_00_T                         dtm_llut_ctrl_00;	//0xF3031070
	PE_O26F22_DTM_LLUT_CTRL_05_T                         dtm_llut_ctrl_05;	//0xF3031084
	PE_O26F22_DTM_LLUT0_IA_CTRL_T                     dtm_llut0_ia_ctrl_s;	//0xF3031088
	PE_O26F22_DTM_LLUT0_IA_DATA_T                   dtm_llut0_ia_data[32];	//0xF303108C
	PE_O26F22_DTM_LLUT0_IA_CTRL_T                     dtm_llut0_ia_ctrl_e;	//0xF3031088
	PE_O26F22_DTM_LUT_LUM_SAT_CTRL_00_T           dtm_lut_lum_sat_ctrl_00;	//0xF30310A0
	PE_O26F22_DTM_LUT_LUM_SAT_CTRL_01_T           dtm_lut_lum_sat_ctrl_01;	//0xF30310A4
	PE_O26F22_DTM_LUT_LUM_SAT_CTRL_02_T           dtm_lut_lum_sat_ctrl_02;	//0xF30310A8
	PE_O26F22_DTM_LUT_LUM_SAT_CTRL_03_T           dtm_lut_lum_sat_ctrl_03;	//0xF30310AC
	PE_O26F22_DTM_HUE_SAT_CTRL_00_T                   dtm_hue_sat_ctrl_00;	//0xF30310E0
	PE_O26F22_PE1_CCO_VERI_SYS_VERI_9_T                  pe1_dce_chr_gain;	//0xF4060324
	PE_O26F22_PE1_DCE_CHR_GAIN2_T                       pe1_dce_chr_gain2;	//0xF406075C
}PE_CHPI_DTM0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_LLLUT_E_IA_CTRL_T                  pe1_lllut_e_ia_ctrl_s;	//0xF4060950
	PE_O26F22_PE1_LLLUT_O_IA_CTRL_T                  pe1_lllut_o_ia_ctrl_s;	//0xF4060958
	PE_O26F22_PE1_LLLUT_E_IA_DATA_T               pe1_lllut_e_ia_data[64];	//0xF4060954
	PE_O26F22_PE1_LLLUT_O_IA_DATA_T               pe1_lllut_o_ia_data[64];	//0xF406095C
	PE_O26F22_PE1_LLLUT_E_IA_CTRL_T                  pe1_lllut_e_ia_ctrl_e;	//0xF4060950
	PE_O26F22_PE1_LLLUT_O_IA_CTRL_T                  pe1_lllut_o_ia_ctrl_e;	//0xF4060958
	PE_O26F22_PE1_LLCORE_CTRL_00_T                      pe1_llcore_ctrl_00;	//0xF4060960
	PE_O26F22_PE1_LLCORE_CTRL_01_T                      pe1_llcore_ctrl_01;	//0xF4060964
	PE_O26F22_PE1_LLCORE_CTRL_02_T                      pe1_llcore_ctrl_02;	//0xF4060968
	PE_O26F22_PE1_LLCORE_CTRL_03_T                      pe1_llcore_ctrl_03;	//0xF406096C
	PE_O26F22_PE1_LLCORE_CTRL_04_T                      pe1_llcore_ctrl_04;	//0xF4060970
	PE_O26F22_PE1_LLCORE_CTRL_05_T                      pe1_llcore_ctrl_05;	//0xF4060974
	PE_O26F22_PE1_LLCORE_CTRL_06_T                      pe1_llcore_ctrl_06;	//0xF4060978
	PE_O26F22_PE1_LLCORE_CTRL_07_T                      pe1_llcore_ctrl_07;	//0xF406097C
	PE_O26F22_PE1_LLCORE_CTRL_08_T                      pe1_llcore_ctrl_08;	//0xF4060980
	PE_O26F22_PE1_LLCORE_CTRL_09_T                      pe1_llcore_ctrl_09;	//0xF4060984
	PE_O26F22_PE1_LLCORE_CTRL_10_T                      pe1_llcore_ctrl_10;	//0xF4060988
	PE_O26F22_PE1_LLCORE_CTRL_11_T                      pe1_llcore_ctrl_11;	//0xF406098C
	PE_O26F22_PE1_LLCORE_CTRL_12_T                      pe1_llcore_ctrl_12;	//0xF4060990
	PE_O26F22_PE1_LLCORE_CTRL_13_T                      pe1_llcore_ctrl_13;	//0xF4060994
}PE_CHPI_LLL0_O26F22_T;

typedef struct
{
	PE_O26F22_PE1_FSW_CTRL_01_T                            pe1_fsw_ctrl_01;	//0xF4060524
	PE_O26F22_VSD1_SHP_FSW_CTRL_00_T                       shp_fsw_ctrl_00;	//0xF3410BF0
	PE_O26F22_VSD1_SHP_FSW_CTRL_01_T                       shp_fsw_ctrl_01;	//0xF3410BF4
	PE_O26F22_VSD1_SHP_FSW_CTRL_02_T                       shp_fsw_ctrl_02;	//0xF3410BF8
	PE_O26F22_VCP0_DISP_VSP_CTRL_00_T                      vsd0_veri_vsp_0;	//0xF3030B00
	PE_O26F22_VCP0_DISP_VSP_CTRL_01_T                      vsd0_veri_vsp_1;	//0xF3030B04
	PE_O26F22_VCP1_DISP_VSP_CTRL_00_T                      vsd1_veri_vsp_0;	//0xF3410F00
	PE_O26F22_VCP1_DISP_VSP_CTRL_01_T                      vsd1_veri_vsp_1;	//0xF3410F04
	PE_O26F22_CC_PE1_DRC_CTRL_07_T                         pe1_drc_ctrl_07;	//0xF40607FC
	PE_O26F22_CC_PE1_DRC_CTRL_08_T                         pe1_drc_ctrl_08;	//0xF4060800
	PE_O26F22_CC_PE1_DRC_CTRL_09_T                         pe1_drc_ctrl_09;	//0xF4060804
	PE_O26F22_CC_PE1_DRC_CTRL_10_T                         pe1_drc_ctrl_10;	//0xF4060808
	PE_O26F22_CC_PE1_DRC_CTRL_11_T                         pe1_drc_ctrl_11;	//0xF406080C
	PE_O26F22_CC_PE1_DRC_CTRL_12_T                         pe1_drc_ctrl_12;	//0xF4060810
	PE_O26F22_CC_PE1_DRC_CTRL_13_T                         pe1_drc_ctrl_13;	//0xF4060814
	PE_O26F22_CC_PE1_DRC_CTRL_14_T                         pe1_drc_ctrl_14;	//0xF4060818
	PE_O26F22_CC_PE1_DRC_CTRL_15_T                         pe1_drc_ctrl_15;	//0xF406081C
	PE_O26F22_CC2_PE1_MERGE_CTRL_31_T                      pe1_merge_ctrl_31;	//0xF406148C
	PE_O26F22_CC2_PE1_MERGE_CTRL_32_T                      pe1_merge_ctrl_32;	//0xF4061490
	PE_O26F22_CC2_PE1_MERGE_CTRL_33_T                      pe1_merge_ctrl_33;	//0xF4061494
	PE_O26F22_CC2_PE1_MERGE_CTRL_34_T                      pe1_merge_ctrl_34;	//0xF4061498
	PE_O26F22_CC2_PE1_MERGE_CTRL_35_T                      pe1_merge_ctrl_35;	//0xF406149C
	PE_O26F22_CC2_PE1_MERGE_CTRL_36_T                      pe1_merge_ctrl_36;	//0xF40614A0
}PE_CHPI_FSW0_O26F22_T;

#endif

