/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2021 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

#ifndef _BE_REG_DPE_O24A0_H_
#define _BE_REG_DPE_O24A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0000 RW 0x0000_0000
	UINT32 bsh_bv_gen                       :12;	//(11:0,RW,0x00) //Horizontal size of a block
	UINT32 resvd0                           :4;
	UINT32 bsv_bv_gen                       :12;	//(27:16,RW,0x00) //Vertical size of a block
	UINT32 resvd1                           :4;
	};
}O24A0_LED_BV_GEN_HV_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0004 RW 0x0000_0000
	UINT32 bnh_bv_gen                       :7;	//(6:0,RW,0x0) //number of Horizontal blocks
	UINT32 resvd0                           :9;
	UINT32 bnv_bv_gen                       :6;	//(21:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :10;
	};
}O24A0_LED_BV_GEN_BLK_NUM_HV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0008 RW 0x0870_0F00
	UINT32 hres                             :13;	//(12:0,RW,0x0F00) //
	UINT32 resvd0                           :3;
	UINT32 vres                             :12;	//(27:16,RW,0x0870) //
	UINT32 resvd1                           :4;
	};
}O24A0_LED_HV_RESOLUTION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E000C RW 0x0000_000F
	UINT32 vs_out_neg                       :1;	//(0,RW,0x01) //
	UINT32 hs_out_neg                       :1;	//(1,RW,0x01) //
	UINT32 vs_in_neg                        :1;	//(2,RW,0x01) //
	UINT32 hs_in_neg                        :1;	//(3,RW,0x01) //
	UINT32 resvd                            :28;
	};
}O24A0_LED_SYNC_POL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0010 RW 0x0000_0001
	UINT32 mode_2ch                         :1;	//(0,RW,0x01) //dual channel mode
	UINT32 resvd                            :31;
	};
}O24A0_LED_VIN_CONFIG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0014 RW 0x0000_0003
	UINT32 led_dly                          :4;	//(3:0,RW,0x03) //0x3:default normal LED output sync delay	0xB:defualt LED clock gated output
	UINT32 resvd                            :28;
	};
}O24A0_LED_LED_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0018 RW 0x0000_0000
	UINT32 monitor_sel                      :1;	//(0,RW,0x00) //debug
	UINT32 monitor_en                       :1;	//(1,RW,0x00) //monitor enable
	UINT32 resvd                            :30;
	};
}O24A0_LED_MONITOR_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E001C RW 0x0000_0000
	UINT32 func_dpath_order                 :1;	//(0,RW,0x00) //"0" : L/D -> Picture Enhance block	"1" : Picture Enhance block -> L/D
	UINT32 resvd                            :31;
	};
}O24A0_LED_DPATH_ORDER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0024 RW 0x0000_0000
	UINT32 input_sync_sel                   :1;	//(0,RW,0x00) //"0" : even channel sync	"1" : odd channel sync
	UINT32 resvd0                           :3;
	UINT32 input_de_sel                     :1;	//(4,RW,0x00) //"0" : vactive & hactive	"1" : de
	UINT32 resvd1                           :27;
	};
}O24A0_LED_SYNC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0028 RW 0x0000_0000
	UINT32 bv_clg_en                        :1;	//(0,RW,0x00) //"0" : BV path clock gating enable	"1" : BV path clock gating disable
	UINT32 resvd                            :31;
	};
}O24A0_LED_BV_CLG_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0040 RW 0x0000_0000
	UINT32 pbl_mode                         :2;	//(1:0,RW,0x00) //"0": normal	"1": display physical backlight image
	UINT32 apf                              :1;	//(2,RW,0x00) //display block value image
	UINT32 sbi2rgb                          :1;	//(3,RW,0x00) //display estimated backlight image
	UINT32 sbi_dis                          :1;	//(4,RW,0x00) //disable estimated backlight image
	UINT32 disp_mark                        :1;	//(5,RW,0x00) //display mark
	UINT32 apf_lres                         :1;	//(6,RW,0x00) //low resolution EBI all pass filter
	UINT32 resvd                            :25;
	};
}O24A0_LED_DBG_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0044 RW 0x0000_03FF
	UINT32 lum                              :10;	//(9:0,RW,0x03FF) //Luminance value in Back light display mode
	UINT32 resvd                            :22;
	};
}O24A0_LED_LUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0048 RW 0x0000_0000
	UINT32 blu_i2c_wdata                    :10;	//(9:0,RW,0x00) //write data
	UINT32 resvd0                           :6;
	UINT32 blu_i2c_waddr                    :13;	//(28:16,RW,0x00) //write address
	UINT32 resvd1                           :2;
	UINT32 blu_i2c_we                       :1;	//(31,RW,0x00) //write enable
	};
}O24A0_LED_BLU_I2C_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E004C RW 0x0000_0000
	UINT32 sbi_sel                          :1;	//(0,RW,0x00) //SB value ( 0 : SBI 1 : I2C Value )
	UINT32 resvd                            :31;
	};
}O24A0_LED_SB_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0050 RW 0x0000_0000
	UINT32 sbi_i2c                          :10;	//(9:0,RW,0x00) //I2C SB value
	UINT32 resvd                            :22;
	};
}O24A0_LED_SB_I2C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0054 RW/RO 0x0000_0000
	UINT32 bv_rdata                         :10;	//(9:0,RO,0x00) //read data
	UINT32 resvd0                           :6;
	UINT32 bv_raddr                         :13;	//(28:16,RW,0x00) //read address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BV_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0058 RW 0x0000_0000
	UINT32 bv_wdata                         :10;	//(9:0,RW,0x00) //write data
	UINT32 resvd0                           :6;
	UINT32 bv_waddr                         :13;	//(28:16,RW,0x00) //write address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BV_WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E005C RO 0x0000_0000
	UINT32 bv_rw_done                       :1;	//(0,RO,0x00) //
	UINT32 resvd                            :31;
	};
}O24A0_LED_BV_RW_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0064 RW 0x0000_0000
	UINT32 led_detour                       :1;	//(0,RW,0x00) //"0" : normal operation	"1" : detour
	UINT32 resvd                            :31;
	};
}O24A0_LED_LED_DETOUR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0080 RW 0x0000_0000
	UINT32 rectangular                      :1;	//(0,RW,0x00) //rectangular image
	UINT32 grid                             :1;	//(1,RW,0x00) //grid image
	UINT32 gradationr                       :1;	//(2,RW,0x00) //R component of gradation image
	UINT32 gradationg                       :1;	//(3,RW,0x00) //G component of gradation image
	UINT32 gradationb                       :1;	//(4,RW,0x00) //B component of gradation image
	UINT32 colorbar                         :1;	//(5,RW,0x00) //color bar image
	UINT32 fld_3dpattern                    :2;	//(7:6,RW,0x00) //"01" : LLRR	"10" : LRLR	"11" : External LR indicator ?�용
	UINT32 grayimage                        :1;	//(8,RW,0x00) //RGB Max값으�?RGB�?출력
	UINT32 resvd                            :23;
	};
}O24A0_LED_PAT_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0084 RW 0x3FFF_FFFF
	UINT32 comp_bvalue                      :10;	//(9:0,RW,0x03FF) //
	UINT32 comp_gvalue                      :10;	//(19:10,RW,0x03FF) //
	UINT32 comp_rvalue                      :10;	//(29:20,RW,0x03FF) //
	UINT32 resvd                            :2;
	};
}O24A0_LED_PAT_VAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0088 RW 0x0167_0078
	UINT32 h_min                            :12;	//(11:0,RW,0x0078) //horizontal start position
	UINT32 resvd0                           :4;
	UINT32 h_max                            :12;	//(27:16,RW,0x0167) //horizontal end position
	UINT32 resvd1                           :4;
	};
}O24A0_LED_PAT_H_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E008C RW 0x0329_010E
	UINT32 v_min                            :12;	//(11:0,RW,0x010E) //vertical start position
	UINT32 resvd0                           :4;
	UINT32 v_max                            :12;	//(27:16,RW,0x0329) //vertical end position
	UINT32 resvd1                           :4;
	};
}O24A0_LED_PAT_V_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0090 RW 0x0000_0000
	UINT32 pat_h_ppf                        :8;	//(7:0,RW,0x0) //Horizontal Speed of the pattern in rectangular and gradation mode (4 pixels per frame)
	UINT32 pat_v_ppf                        :8;	//(15:8,RW,0x0) //Vertical speed of the pattern in rectangular mode (1 pixel per frame)
	UINT32 resvd                            :16;
	};
}O24A0_LED_PAT_HV_PPF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0094 RW 0x3FFF_FFFF
	UINT32 fld_3d_bvalue                    :10;	//(9:0,RW,0x03FF) //B Value in 3D Pattern
	UINT32 fld_3d_gvalue                    :10;	//(19:10,RW,0x03FF) //G Value in 3D Pattern
	UINT32 fld_3d_rvalue                    :10;	//(29:20,RW,0x03FF) //R Value in 3D Pattern
	UINT32 resvd                            :2;
	};
}O24A0_LED_PAT_VAL_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0098 RW 0x0167_0078
	UINT32 fld_3d_h_min                     :11;	//(10:0,RW,0x0078) //h_min in 3D Pattern
	UINT32 resvd0                           :5;
	UINT32 fld_3d_h_max                     :11;	//(26:16,RW,0x0167) //h_max in 3D Pattern
	UINT32 resvd1                           :5;
	};
}O24A0_LED_PAT_H_MIN_MAX_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E009C RW 0x0329_010E
	UINT32 fld_3d_v_min                     :12;	//(11:0,RW,0x010E) //v_min in 3D Pattern
	UINT32 resvd0                           :4;
	UINT32 fld_3d_v_max                     :12;	//(27:16,RW,0x0329) //v_max in 3D Pattern
	UINT32 resvd1                           :4;
	};
}O24A0_LED_PAT_V_MIN_MAX_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00A0 RW 0x0000_0000
	UINT32 bg_bvalue                        :10;	//(9:0,RW,0x00) //Background B value in box pattern
	UINT32 bg_gvalue                        :10;	//(19:10,RW,0x00) //Background G value in box pattern
	UINT32 bg_rvalue                        :10;	//(29:20,RW,0x00) //Background R value in box pattern
	UINT32 resvd                            :2;
	};
}O24A0_LED_PAT_BGVAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00C0 RW 0x0000_0400
	UINT32 iwb_r_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_r_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_IWB_R_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00C4 RW 0x0000_0400
	UINT32 iwb_g_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_g_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_IWB_G_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00C8 RW 0x0000_0400
	UINT32 iwb_b_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_b_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_IWB_B_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00E4 RO 0x0000_0000
	UINT32 info_crc_1                       :32;	//(31:0,RO,0x0) //Read LED CRC value
	};
}O24A0_LED_CRC1_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00E8 RW 0x0000_0001
	UINT32 resvd0                           :1;
	UINT32 led_out_sel                      :4;	//(4:1,RW,0x0) //"000" : oled 10 bit [9:0]	"001" : oled 11 bit [10:0]	"010" : oled detour [9:0] : led out	"011" : 8k bypass, oled,led detour	"100" : hdmi420, oled,led detour	"101" : MPIP, oled,led detour	others : oled 10 bit [9:0]
	UINT32 resvd1                           :27;
	};
}O24A0_LED_HDMI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00EC RW 0x0000_0000
	UINT32 fbc_en                           :1;	//(0,RW,0x0) //"0" : fbc off	"1" : fbc on
	UINT32 fbc_20p                          :1;	//(1,RW,0x0) //"0" : 40% mode	"1" : 20% mode
	UINT32 resvd0                           :2;
	UINT32 fbc_dual_haar_th                 :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :24;
	};
}O24A0_LED_FBC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00F0 RW 0x0000_0000
	UINT32 dpcm_rest_step                   :2;	//(1:0,RW,0x0) //DPCM_REST_STEP
	UINT32 resvd                            :30;
	};
}O24A0_LED_FBC_DPCM_REST_STEP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00F4 RW 0x0000_0000
	UINT32 yc422_en                         :1;	//(0,RW,0x0) //"0" : YC422 disable	"1" : YC422 enable
	UINT32 resvd0                           :3;
	UINT32 sample_mode                      :1;	//(4,RW,0x0) //"0" : sub-sample with 3TAB average fiter	"1" : sub-sample without A/A filter
	UINT32 resvd1                           :3;
	UINT32 bit_extension_option             :2;	//(9:8,RW,0x0) //"00" : + 00	"01" : + MSB	"10" : + 11	"11" : + 00
	UINT32 resvd2                           :6;
	UINT32 y_delay                          :2;	//(17:16,RW,0x0) //for debug 	0 : no delay	1 : pre 1clk delay	2 : 1 clk delay
	UINT32 resvd3                           :2;
	UINT32 cb_delay                         :2;	//(21:20,RW,0x0) //for debug 	0 : no delay	1 : pre 1clk delay	2 : 1 clk delay
	UINT32 cr_delay                         :2;	//(23:22,RW,0x0) //for debug 	0 : no delay	1 : pre 1clk delay	2 : 1 clk delay
	UINT32 eo_swap                          :1;	//(24,RW,0x0) //for debug : Even / Odd data swap	0 : normal	1 : swap
	UINT32 c_o_swap                         :1;	//(25,RW,0x0) //color ouptut swap	0 : normal	1 : Cb/Cr swap
	UINT32 c_i_swap                         :1;	//(26,RW,0x0) //color input swap	0 : normal	1 : Cb/Cr swap
	UINT32 resvd4                           :1;
	UINT32 reg_420_en                       :1;	//(28,RW,0x0) //Enable of 420 block	0 : bypass	1 : Enable
	UINT32 reserved                         :3;	//(31:29,RW,0x0) //
	};
}O24A0_LED_YC422_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00F8 RW 0x0000_0001
	UINT32 info_crc_en                      :4;	//(3:0,RW,0x1) //crc enable
	UINT32 info_crc_mux_dlatch              :4;	//(7:4,RW,0x0) //crc data latch	0: vsync falling edge	1: vsync rising edge
	UINT32 resvd                            :24;
	};
}O24A0_LED_CRC_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E00FC RO 0x0000_0000
	UINT32 info_crc_0                       :32;	//(31:0,RO,0x0) //Read LED RGB [59:0] CRC value
	};
}O24A0_LED_CRC_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0100 RW 0x0000_0000
	UINT32 hist_mode                        :2;	//(1:0,RW,0x00) //"00"   : MAX(R,G,B) histogram	"01"   : LUM(R,G,B) histogram	others : AVG(R,G,B) histogram
	UINT32 resvd                            :30;
	};
}O24A0_LED_HIST_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0104 WO/RO 0x0000_0000
	UINT32 wr_hist_raddr                    :6;	//(5:0,WO,0x0) //histogram read address
	UINT32 rd_hist_rdata                    :17;	//(22:6,RO,0x0000_0000) //histogram read data(?�제22:0??
	UINT32 resvd0                           :1;
	UINT32 rd_hist_raddr                    :6;	//(29:24,RO,0x0) //histogram read address
	UINT32 resvd1                           :2;
	};
}O24A0_LED_HIST_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0108 RW 0x0000_0000
	UINT32 pwm_ext_sc_sel                   :1;	//(0,RW,0x00) //external scene change detection	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_sc_mode                      :3;	//(6:4,RW,0x00) //scene change detection mode 	"000"  : histogram | apl | block	"001"  : histogram	"010"  : apl	"011"  : block	others : histogram & apl & block
	UINT32 resvd1                           :25;
	};
}O24A0_LED_PWM_SC_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E010C RW 0x0000_0001
	UINT32 pwm_fr_max_only                  :1;	//(0,RW,0x01) //Operated histogram max only mode	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_ext_max_sel                  :1;	//(4,RW,0x00) //external max value	"0" : disable	"1" : enable
	UINT32 resvd1                           :3;
	UINT32 pwm_max_mode                     :2;	//(9:8,RW,0x00) //"00" : histogram max value	"01" : Weighted Sum ( histogram & block max ) 	"10" : MAX ( histogram & block max )	"11" : MIN ( histogram & block max )
	UINT32 resvd2                           :2;
	UINT32 pwm_bv_end_sel                   :1;	//(12,RW,0x00) //debug
	UINT32 resvd3                           :19;
	};
}O24A0_LED_PWM_MAX_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0110 RW 0x0000_0000
	UINT32 sc_maf_iir_en                    :1;	//(0,RW,0x00) //Adaptive iir filtering using scene change for Local Dimming	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_sc_iir_en                    :1;	//(4,RW,0x00) //Adaptive iir filtering using scene change for PWM value	"0" : disable	"1" : enable
	UINT32 resvd1                           :27;
	};
}O24A0_LED_PWM_IIR_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0114 RW 0x0000_0000
	UINT32 ext_pwm_sel                      :1;	//(0,RW,0x00) //external PWM value	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_blu_en                       :1;	//(4,RW,0x00) //Local Dimming with PWM value	"0" : disable	"1" : enable
	UINT32 resvd1                           :27;
	};
}O24A0_LED_PWM_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0118 RW 0x0000_0000
	UINT32 pc_pwm_sel                       :1;	//(0,RW,0x00) //pixel compensation with sbi or pwm	"0" : sbi	"1" : pwm
	UINT32 resvd                            :31;
	};
}O24A0_LED_PWM_PEL_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E011C RW 0x0000_0000
	UINT32 pwm_ext_sc                       :1;	//(0,RW,0x00) //external scene change input
	UINT32 resvd                            :31;
	};
}O24A0_LED_PWM_EXT_SC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0120 RW 0x00FF_FFFF
	UINT32 pwm_sc_hist_th                   :24;	//(23:0,RW,0x00FF_FFFF) //histogram difference threshold
	UINT32 resvd                            :8;
	};
}O24A0_LED_PWM_SC_HIST_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0124 RW 0x0000_03FF
	UINT32 pwm_sc_apl_th                    :10;	//(9:0,RW,0x03FF) //apl difference threshold
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_SC_APL_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0128 RO 0x0000_0000
	UINT32 pwm_sc_detect                    :1;	//(0,RO,0x00) //Read scene change detection flag
	UINT32 resvd                            :31;
	};
}O24A0_LED_PWM_SC_DETECT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E012C RW 0x0000_0000
	UINT32 pwm_max_cdf                      :23;	//(22:0,RW,0x0000_0000) //CDF threshold for histogram max value decision
	UINT32 resvd                            :9;
	};
}O24A0_LED_PWM_MAX_CDF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0130 RW 0x0000_03FF
	UINT32 pwm_ext_max                      :10;	//(9:0,RW,0x03FF) //external max value
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_EXT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0134 RW 0x0000_0000
	UINT32 pwm_fr_max_wei                   :8;	//(7:0,RW,0x0) //Weight between histogram and block max value
	UINT32 resvd                            :24;
	};
}O24A0_LED_PWM_FR_MAX_WEI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0138 RW 0x0000_0000
	UINT32 pwm_x2                           :10;	//(9:0,RW,0x00) //max value point2
	UINT32 resvd0                           :6;
	UINT32 pwm_x1                           :10;	//(25:16,RW,0x00) //max value point1
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E013C RW 0x0000_0000
	UINT32 pwm_x4                           :10;	//(9:0,RW,0x00) //max value point4
	UINT32 resvd0                           :6;
	UINT32 pwm_x3                           :10;	//(25:16,RW,0x00) //max value point3
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0140 RW 0x0000_0000
	UINT32 pwm_y1                           :10;	//(9:0,RW,0x00) //pwm value in point1
	UINT32 resvd0                           :6;
	UINT32 pwm_y0                           :10;	//(25:16,RW,0x00) //pwm value in 0
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0144 RW 0x0000_0000
	UINT32 pwm_y3                           :10;	//(9:0,RW,0x00) //pwm value in point3
	UINT32 resvd0                           :6;
	UINT32 pwm_y2                           :10;	//(25:16,RW,0x00) //pwm value in point2
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0148 RW 0x0000_0000
	UINT32 pwm_y5                           :10;	//(9:0,RW,0x00) //pwm value in 1023
	UINT32 resvd0                           :6;
	UINT32 pwm_y4                           :10;	//(25:16,RW,0x00) //pwm value in point4
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E014C RO 0x0000_0000
	UINT32 pwm_fr_max_value                 :10;	//(9:0,RO,0x00) //read histogram max value
	UINT32 resvd0                           :6;
	UINT32 pwm_bv_max_value                 :10;	//(25:16,RO,0x00) //read block max value
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_BV_FR_MAX_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0150 RO 0x0000_0000
	UINT32 pwm_max_value                    :10;	//(9:0,RO,0x00) //read max value
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_MAX_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0154 RO 0x0000_0000
	UINT32 pwm_value_iir                    :10;	//(9:0,RO,0x00) //read iir filtered pwm value
	UINT32 resvd0                           :6;
	UINT32 pwm_value                        :10;	//(25:16,RO,0x00) //read pwm value
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_VALUE_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0158 RW 0x0000_0080
	UINT32 pwm_iir_wei                      :8;	//(7:0,RW,0x80) //PWM iir filter weight
	UINT32 resvd                            :24;
	};
}O24A0_LED_PWM_IIR_WEI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E015C RW 0x0000_0000
	UINT32 pwm_sc_iir_step_c                :18;	//(17:0,RW,0x0000_0000) //Smooth off step for PWM IIR filter with scene change
	UINT32 resvd                            :14;
	};
}O24A0_LED_PWM_SC_IIR_STEP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0160 RW 0x0000_0000
	UINT32 pwm_sc_iir_step_p                :18;	//(17:0,RW,0x0000_0000) //Smooth on step for PWM IIR filter with scene change
	UINT32 resvd                            :14;
	};
}O24A0_LED_PWM_SC_IIR_STEP_P_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0164 RO 0x0000_0000
	UINT32 pwm_adj_iir_wei                  :8;	//(7:0,RO,0x0) //Read smooth on/off value for PWM IIR filter
	UINT32 resvd                            :24;
	};
}O24A0_LED_PWM_ADJ_IIR_WEI_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0168 RW 0x0000_0000
	UINT32 sc_maf_iir_step_c                :20;	//(19:0,RW,0x0000_0000) //Smooth off step for BV IIR filter with scene change
	UINT32 resvd                            :12;
	};
}O24A0_LED_PWM_MAF_IIR_STEP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E016C RW 0x0000_0000
	UINT32 sc_maf_iir_step_p                :20;	//(19:0,RW,0x0000_0000) //Smooth on step for BV IIR filter with scene change
	UINT32 resvd                            :12;
	};
}O24A0_LED_PWM_MAF_IIR_STEP_P_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0170 RO 0x0000_0000
	UINT32 sc_maf_iir_mag                   :10;	//(9:0,RO,0x00) //Read smooth on/off value for BV IIR filter
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_MAF_IIR_MAG_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0174 RW 0x0000_0000
	UINT32 ext_pwm_pel                      :10;	//(9:0,RW,0x00) //external PWM value
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_EXT_VAL_PEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0178 RW/RO 0x0000_0000
	UINT32 pwm_bl_tdif_avg_th               :10;	//(9:0,RW,0x00) //average block difference threshold
	UINT32 resvd0                           :6;
	UINT32 pwm_bl_tdif_avg                  :10;	//(25:16,RO,0x00) //average block difference
	UINT32 resvd1                           :6;
	};
}O24A0_LED_PWM_BL_TDIF_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0180 RW 0x0000_0002
	UINT32 max_opt                          :8;	//(7:0,RW,0x2) //MAX_OPT value
	UINT32 resvd                            :24;
	};
}O24A0_LED_MAX_OPT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0184 RW 0x0000_0000
	UINT32 blk_max_mode                     :1;	//(0,RW,0x00) //"0": BV = (Σ AVG( R, G, B))/N	"1": BV = (Σ Max (R, G, B)) / N	Where N: Number of Pixel in a block
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLK_MAX_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0188 RW 0x0000_0000
	UINT32 max_opt_mode                     :1;	//(0,RW,0x00) //"0" : normal operation using MAX_OPT register	"1" : adaptive operation using MAX_OPT0, MAX_OPT1 register
	UINT32 resvd                            :31;
	};
}O24A0_LED_MAX_OPT_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E018C RW 0x0000_40FF
	UINT32 max_opt1                         :8;	//(7:0,RW,0xFF) //maximum MAX_OPT value
	UINT32 max_opt0                         :8;	//(15:8,RW,0x40) //minimum MAX_OPT value
	UINT32 resvd                            :16;
	};
}O24A0_LED_MAX_OPT0_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0190 RW 0x0000_0320
	UINT32 level_th                         :10;	//(9:0,RW,0x0320) //Pixel Level Threshold for Block Histogram
	UINT32 resvd                            :22;
	};
}O24A0_LED_LEVEL_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0194 RW 0x0000_03E8
	UINT32 number_th                        :12;	//(11:0,RW,0x03E8) //number threshold of Block Histogram
	UINT32 resvd0                           :4;
	UINT32 number_bit_sel                   :4;	//(19:16,RW,0x00) //select 12bits of total 19 bits (Block histogram)
	UINT32 resvd1                           :12;
	};
}O24A0_LED_NUMBER_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0198 RO 0x0000_0000
	UINT32 avg_bv                           :10;	//(9:0,RO,0x00) //BLU 구동 BV???�균
	UINT32 resvd0                           :6;
	UINT32 apl                              :10;	//(25:16,RO,0x00) //bv_gen block ?�서 계산??BV???�균
	UINT32 resvd1                           :6;
	};
}O24A0_LED_APL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E019C RW 0x00C8_0190
	UINT32 bv_gen_x2                        :10;	//(9:0,RW,0x0190) //x2 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x1                        :10;	//(25:16,RW,0x0C8) //x1 APL
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01A0 RW 0x0258_0320
	UINT32 bv_gen_x4                        :10;	//(9:0,RW,0x0320) //x4 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x3                        :10;	//(25:16,RW,0x0258) //x3 APL
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01A4 RW 0x0000_0000
	UINT32 bv_gen_y1                        :10;	//(9:0,RW,0x00) //y1 (x = x1)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y0                        :10;	//(25:16,RW,0x00) //y0 (x = 0)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01A8 RW 0x0000_0000
	UINT32 bv_gen_y3                        :10;	//(9:0,RW,0x00) //y3 (x = x3)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y2                        :10;	//(25:16,RW,0x00) //y2 (x = x2)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01AC RW 0x0000_0000
	UINT32 bv_gen_y5                        :10;	//(9:0,RW,0x00) //y5 (x = 1023)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y4                        :10;	//(25:16,RW,0x00) //y4 (x = x4)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01B0 RO 0x0000_0000
	UINT32 bvgen_max                        :10;	//(9:0,RO,0x00) //BV max value in bv_gen
	UINT32 resvd0                           :6;
	UINT32 bvgen_min                        :10;	//(25:16,RO,0x00) //BV min value in bv_gen
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_BV_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01B4 RO 0x0000_0000
	UINT32 max_bv                           :10;	//(9:0,RO,0x00) //BV max value in bv_ctrl
	UINT32 resvd0                           :6;
	UINT32 min_bv                           :10;	//(25:16,RO,0x00) //BV min value in bv_ctrl
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01B8 RO 0x0000_0000
	UINT32 bv_lut_max                       :10;	//(9:0,RO,0x00) //BV max value in bv_lut
	UINT32 resvd0                           :6;
	UINT32 bv_lut_min                       :10;	//(25:16,RO,0x00) //BV min value in bv_lut
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_LUT_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01BC RO 0x0000_0000
	UINT32 bv_final_max                     :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_final_min                     :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_final_avg                     :10;	//(29:20,RO,0x00) //BV avg value in blu_if(final)
	UINT32 resvd                            :2;
	};
}O24A0_LED_BV_FINAL_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01C0 RW 0x0000_0000
	UINT32 rctrl_mode                       :4;	//(3:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 vsout_mode                       :4;	//(11:8,RW,0x00) //
	UINT32 resvd1                           :4;
	UINT32 bdata_mode                       :4;	//(19:16,RW,0x00) //
	UINT32 resvd2                           :4;
	UINT32 tfout_mode                       :4;	//(27:24,RW,0x00) //
	UINT32 resvd3                           :4;
	};
}O24A0_LED_BV_RCTRL_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01C4 RW/RO 0x0000_0000
	UINT32 pic_attr                         :1;	//(0,RW,0x00) //
	UINT32 black_mask                       :1;	//(1,RO,0x00) //Black mask for BLU	Output of bv_rctrl block
	UINT32 tf_pic_attr                      :1;	//(2,RO,0x00) //Pic_attr for temporal filter	Output of bv_rctrl block
	UINT32 resvd                            :29;
	};
}O24A0_LED_PIC_ATTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E01C8 RW 0x0000_0000
	UINT32 lr_sync_sel                      :1;	//(0,RW,0x00) //'0' : H/W Pin input	'1' : Register
	UINT32 resvd                            :31;
	};
}O24A0_LED_LR_SYNC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0240 RW 0x0000_0000
	UINT32 lut_mode                         :2;	//(1:0,RW,0x00) //??0?? bypass	??1?? s-curve mode based on internally calculated abv	??0?? s-curve mode using ex_abv
	UINT32 resvd                            :30;
	};
}O24A0_LED_LUT_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0244 RW 0x0000_0000
	UINT32 ex_abv                           :10;	//(9:0,RW,0x00) //external abv
	UINT32 resvd                            :22;
	};
}O24A0_LED_EX_ABV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E024C RW 0x0000_0000
	UINT32 lut_dbg_raddr                    :10;	//(9:0,RW,0x00) //read address
	UINT32 resvd0                           :6;
	UINT32 lut_dbg_rd_sel                   :1;	//(16,RW,0x00) //read selection
	UINT32 resvd1                           :15;
	};
}O24A0_LED_DC_LUT_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0250 RO 0x0000_0000
	UINT32 lut1_dbg_rdata                   :10;	//(9:0,RO,0x00) //read lower LUT data
	UINT32 resvd0                           :6;
	UINT32 lut0_dbg_rdata                   :10;	//(25:16,RO,0x00) //read upper LUT data
	UINT32 resvd1                           :6;
	};
}O24A0_LED_DC_LUT_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0258 RW 0x0000_0000
	UINT32 lut_avg_sel                      :1;	//(0,RW,0x00) //Select average value to lut_block	'0' : apl by mean value block	'1' : bv average by bv_gen block
	UINT32 resvd                            :31;
	};
}O24A0_LED_LUT_AVG_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E025C RW 0x0000_0000
	UINT32 bv_offset_en                     :3;	//(2:0,RW,0x00) //[0] : enable/disable	[2:1] : 00 - use bv_max from bv_gen	        01 - use bv_max from control reg.	        10 - use bv_max from lut_block
	UINT32 resvd                            :29;
	};
}O24A0_LED_LUT_OFFSET_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0260 RW 0x00C8_0190
	UINT32 bv_offset_x2                     :10;	//(9:0,RW,0x0190) //bv max point 2
	UINT32 resvd0                           :6;
	UINT32 bv_offset_x1                     :10;	//(25:16,RW,0x0C8) //bv max point 1
	UINT32 resvd1                           :6;
	};
}O24A0_LED_LUT_OFFSET_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0264 RW 0x0258_0320
	UINT32 bv_offset_x4                     :10;	//(9:0,RW,0x0320) //bv max point 4
	UINT32 resvd0                           :6;
	UINT32 bv_offset_x3                     :10;	//(25:16,RW,0x0258) //bv max point 3
	UINT32 resvd1                           :6;
	};
}O24A0_LED_LUT_OFFSET_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0268 RW 0x0066_0066
	UINT32 bv_offset_y1                     :10;	//(9:0,RW,0x66) //offset value in point 1
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y0                     :10;	//(25:16,RW,0x66) //offset value in 0
	UINT32 resvd1                           :6;
	};
}O24A0_LED_LUT_OFFSET_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E026C RW 0x0066_0066
	UINT32 bv_offset_y3                     :10;	//(9:0,RW,0x66) //offset value in point 3
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y2                     :10;	//(25:16,RW,0x66) //offset value in point 2
	UINT32 resvd1                           :6;
	};
}O24A0_LED_LUT_OFFSET_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0270 RW 0x0066_0066
	UINT32 bv_offset_y5                     :10;	//(9:0,RW,0x66) //offset value in 1023
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y4                     :10;	//(25:16,RW,0x66) //offset value in point 4
	UINT32 resvd1                           :6;
	};
}O24A0_LED_LUT_OFFSET_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0274 RW 0x0000_0000
	UINT32 smooth_off                       :1;	//(0,RW,0x00) //Local dimming smooth on/off
	UINT32 resvd                            :31;
	};
}O24A0_LED_LD_SMOOTH_OFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0278 RW 0x0000_0000
	UINT32 smooth_off_step                  :10;	//(9:0,RW,0x00) //Smooth on/off step for Local dimming
	UINT32 resvd                            :22;
	};
}O24A0_LED_LD_SMOOTH_OFF_STEP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E027C RW 0x0000_0000
	UINT32 bv_ext_max                       :10;	//(9:0,RW,0x00) //external bv max value
	UINT32 resvd                            :22;
	};
}O24A0_LED_LD_BV_EXT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0280 RW 0x0000_0000
	UINT32 lsf_en                           :1;	//(0,RW,0x00) //Enable UMASK
	UINT32 resvd                            :31;
	};
}O24A0_LED_UMASK_UM_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0284 RW 0x0000_0000
	UINT32 lsf_5x5_en                       :1;	//(0,RW,0x00) //5x5 UMASK
	UINT32 resvd0                           :3;
	UINT32 lsf_load                         :1;	//(4,RW,0x00) //lsf coeff. load
	UINT32 resvd1                           :3;
	UINT32 lsf_load_mode                    :1;	//(8,RW,0x00) //0 : vsync. load	1 : manual laod
	UINT32 resvd2                           :23;
	};
}O24A0_LED_UMASK_5X5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0288 RW 0x000A_000A
	UINT32 lsf_coaring_n                    :10;	//(9:0,RW,0x0A) //Negative coaring for UMASK
	UINT32 resvd0                           :6;
	UINT32 lsf_coaring_p                    :10;	//(25:16,RW,0x0A) //Positive coaring for UMASK
	UINT32 resvd1                           :6;
	};
}O24A0_LED_UMASK_COARING_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E028C RW 0x0118_0118
	UINT32 lsf_gain_n                       :12;	//(11:0,RW,0x0118) //Negative gain for UMASK
	UINT32 resvd0                           :4;
	UINT32 lsf_gain_p                       :12;	//(27:16,RW,0x0118) //Positive gain for UMASK
	UINT32 resvd1                           :4;
	};
}O24A0_LED_UMASK_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0290 RW 0x0000_0000
	UINT32 lsf_coeff_wdata                  :12;	//(11:0,RW,0x00) //write data
	UINT32 resvd                            :20;
	};
}O24A0_LED_UMASK_WR_COEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0294 RW/RO 0x0000_0000
	UINT32 lsf_coeff_rdata                  :12;	//(11:0,RO,0x00) //read data
	UINT32 resvd0                           :4;
	UINT32 lsf_coeff_raddr                  :7;	//(22:16,RW,0x0) //read address
	UINT32 resvd1                           :9;
	};
}O24A0_LED_UMASK_RD_COEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E02C0 RW 0x03FF_03FF
	UINT32 t_sf                             :10;	//(9:0,RW,0x03FF) //threshold value for max/min
	UINT32 resvd0                           :6;
	UINT32 limit                            :10;	//(25:16,RW,0x03FF) //limit
	UINT32 resvd1                           :6;
	};
}O24A0_LED_T_SF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E02C4 RW 0x0000_0000
	UINT32 kmode                            :1;	//(0,RW,0x00) //"0" : MAX	"1" : MIN
	UINT32 resvd                            :31;
	};
}O24A0_LED_KMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E02C8 RW 0x0000_0005
	UINT32 hkmask                           :4;	//(3:0,RW,0x01) //horizontal size of mask	00:off, 01:3x3, 11:5x5
	UINT32 vkmask                           :4;	//(7:4,RW,0x01) //vertical size of mask	00:off, 01:3x3, 11:5x5
	UINT32 resvd                            :24;
	};
}O24A0_LED_HVKMASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E02CC RW 0x0000_03FF
	UINT32 reg_nlsf_alpha                   :10;	//(9:0,RW,0x3FF) //blend alpha
	UINT32 resvd0                           :6;
	UINT32 reg_blend_mode                   :1;	//(16,RW,0x00) //blend mode
	UINT32 resvd1                           :15;
	};
}O24A0_LED_BLEND_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0300 RW 0x0000_0000
	UINT32 tf_opmode                        :3;	//(2:0,RW,0x00) //used in 3D Mode(not used)
	UINT32 resvd                            :29;
	};
}O24A0_LED_TF_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0304 RW 0x0000_001F
	UINT32 a_para                           :9;	//(8:0,RW,0x01F) //weighting factor for temporal filter	( w*current + (1-w)*previous )
	UINT32 resvd                            :23;
	};
}O24A0_LED_A_PARA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0308 RW 0x0000_0000
	UINT32 sc_adj_en                        :1;	//(0,RW,0x00) //Enable scene change adjustment for temporal filter
	UINT32 resvd                            :31;
	};
}O24A0_LED_SC_ADJ_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E030C RW 0x0000_0000
	UINT32 md_adj_en                        :1;	//(0,RW,0x00) //Enable temporal difference adjustment for temporal filter
	UINT32 resvd                            :31;
	};
}O24A0_LED_MD_ADJ_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0310 RW 0x00C8_00C8
	UINT32 md_x1_n                          :10;	//(9:0,RW,0xC8) //x1_n
	UINT32 resvd0                           :6;
	UINT32 md_x1_p                          :10;	//(25:16,RW,0xC8) //x1_p
	UINT32 resvd1                           :6;
	};
}O24A0_LED_MD_X1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0314 RW 0x0190_0190
	UINT32 md_x2_n                          :10;	//(9:0,RW,0x190) //x2_n
	UINT32 resvd0                           :6;
	UINT32 md_x2_p                          :10;	//(25:16,RW,0x190) //x2_p
	UINT32 resvd1                           :6;
	};
}O24A0_LED_MD_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0318 RW 0x0258_0258
	UINT32 md_x3_n                          :10;	//(9:0,RW,0x258) //x3_n
	UINT32 resvd0                           :6;
	UINT32 md_x3_p                          :10;	//(25:16,RW,0x258) //x3_p
	UINT32 resvd1                           :6;
	};
}O24A0_LED_MD_X3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E031C RW 0x0320_0320
	UINT32 md_x4_n                          :10;	//(9:0,RW,0x320) //x4_n
	UINT32 resvd0                           :6;
	UINT32 md_x4_p                          :10;	//(25:16,RW,0x320) //x4_p
	UINT32 resvd1                           :6;
	};
}O24A0_LED_MD_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0320 RW 0x001F_001F
	UINT32 md_y0_n                          :9;	//(8:0,RW,0x1F) //y0_n (x = 0)
	UINT32 resvd0                           :7;
	UINT32 md_y0_p                          :9;	//(24:16,RW,0x1F) //y0_p (x = 0)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0324 RW 0x001F_001F
	UINT32 md_y1_n                          :9;	//(8:0,RW,0x1F) //y1 (x = x1_n)
	UINT32 resvd0                           :7;
	UINT32 md_y1_p                          :9;	//(24:16,RW,0x1F) //y1 (x = x1_p)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0328 RW 0x001F_001F
	UINT32 md_y2_n                          :9;	//(8:0,RW,0x1F) //y2 (x = x2_n)
	UINT32 resvd0                           :7;
	UINT32 md_y2_p                          :9;	//(24:16,RW,0x1F) //y2 (x = x2_p)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E032C RW 0x001F_001F
	UINT32 md_y3_n                          :9;	//(8:0,RW,0x1F) //y3 (x = x3_n)
	UINT32 resvd0                           :7;
	UINT32 md_y3_p                          :9;	//(24:16,RW,0x1F) //y3 (x = x3_p)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0330 RW 0x001F_001F
	UINT32 md_y4_n                          :9;	//(8:0,RW,0x1F) //y4 (x = x4_n)
	UINT32 resvd0                           :7;
	UINT32 md_y4_p                          :9;	//(24:16,RW,0x1F) //y4 (x = x4_p)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0334 RW 0x001F_001F
	UINT32 md_y5_n                          :9;	//(8:0,RW,0x1F) //y5 (x = 1023)
	UINT32 resvd0                           :7;
	UINT32 md_y5_p                          :9;	//(24:16,RW,0x1F) //y5 (x = 1023)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_MD_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0338 RW 0x01FF_0000
	UINT32 avg_bv_iir_mode                  :1;	//(0,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd0                           :15;
	UINT32 avg_bv_iir_gain                  :9;	//(24:16,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd1                           :7;
	};
}O24A0_LED_BV_FINAL_AVG_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E033C RW 0x1FF0_1FF0
	UINT32 m1_avg_bv_iir_mode               :1;	//(0,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd0                           :3;
	UINT32 m1_avg_bv_iir_gain               :9;	//(12:4,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd1                           :3;
	UINT32 m0_avg_bv_iir_mode               :1;	//(16,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd2                           :3;
	UINT32 m0_avg_bv_iir_gain               :9;	//(28:20,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd3                           :3;
	};
}O24A0_LED_BV_MID_AVG_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0340 RW 0x0000_0000
	UINT32 led_mode                         :2;	//(1:0,RW,0x00) //"00" : Direct	"01" : T/B Edge	"10" : L/R Edge	"11" : Hybrid
	UINT32 resvd0                           :6;
	UINT32 edge_mode                        :2;	//(9:8,RW,0x00) //"00" : 2-Edge	"10" : 1-Edge R/B	"11" : 1-Edge L/T
	UINT32 resvd1                           :6;
	UINT32 hybrid_mode                      :1;	//(16,RW,0x00) //"0" : hybrid edge T/B	"1" : hybrid edge L/R
	UINT32 resvd2                           :7;
	UINT32 hybrid_pattern                   :4;	//(27:24,RW,0x00) //[24] : even_H(V) T(L)_on/off	[25] : even_H(V) B(R)_on/off	[26] :  odd_H(V) T(L)_on/off	[27] :  odd_H(V) B(R)_on/off
	UINT32 resvd3                           :4;
	};
}O24A0_LED_LED_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0344 RW 0x0000_0000
	UINT32 bnh_lres                         :6;	//(5:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :10;
	UINT32 bnv_lres                         :5;	//(20:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :11;
	};
}O24A0_LED_LRES_BNH_BNV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0348 RW 0x0000_0000
	UINT32 bsh_lres                         :6;	//(5:0,RW,0x0) //Horizontal size of a block
	UINT32 resvd0                           :10;
	UINT32 bsv_lres                         :5;	//(20:16,RW,0x0) //Vertical size of a block
	UINT32 resvd1                           :11;
	};
}O24A0_LED_LRES_BSH_BSV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E034C RW 0x0000_0000
	UINT32 sbi_bnh                          :8;	//(7:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :8;
	UINT32 sbi_bnv                          :7;	//(22:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :9;
	};
}O24A0_LED_SBI_BNH_BNV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0350 RW 0x0000_0000
	UINT32 sbi_bsh                          :10;	//(9:0,RW,0x00) //Horizontal size of a block
	UINT32 resvd0                           :6;
	UINT32 sbi_bsv                          :10;	//(25:16,RW,0x00) //Vertical size of a block
	UINT32 resvd1                           :6;
	};
}O24A0_LED_SBI_BSH_BSV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0354 RW 0x0000_0000
	UINT32 tab1_rd_sel                      :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}O24A0_LED_TAB1_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0358 RO/WO 0x0000_0000
	UINT32 tab1_rdata                       :10;	//(9:0,WO,0x00) //read data
	UINT32 tab1_re                          :1;	//(10,RO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}O24A0_LED_TAB1_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E035C RW 0x0000_0000
	UINT32 tab5_rd_sel                      :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}O24A0_LED_TAB5_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0360 RO/WO 0x0000_0000
	UINT32 tab5_rdata                       :10;	//(9:0,RO,0x00) //read data
	UINT32 tab5_re                          :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}O24A0_LED_TAB5_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0364 RW 0x0000_0000
	UINT32 hfc_rd_sel                       :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}O24A0_LED_HFC_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0368 RO/WO 0x0000_0000
	UINT32 hfc_rdata                        :10;	//(9:0,RO,0x00) //read data
	UINT32 hfc_re                           :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}O24A0_LED_HFC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E036C RW 0x0000_0000
	UINT32 vfc_rd_sel                       :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}O24A0_LED_VFC_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0370 RO/WO 0x0000_0000
	UINT32 vfc_rdata                        :10;	//(9:0,RO,0x00) //read data
	UINT32 vfc_re                           :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}O24A0_LED_VFC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0374 RW 0x0000_0000
	UINT32 polaris_en                       :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :7;
	UINT32 polaris_hx2_en                   :1;	//(8,RW,0x00) //
	UINT32 resvd1                           :7;
	UINT32 polaris_hsft_odd                 :3;	//(18:16,RW,0x00) //
	UINT32 polaris_hsft_odd_dir             :1;	//(19,RW,0x00) //
	UINT32 resvd2                           :4;
	UINT32 polaris_hsft_eve                 :3;	//(26:24,RW,0x00) //
	UINT32 polaris_hsft_eve_dir             :1;	//(27,RW,0x00) //
	UINT32 resvd3                           :4;
	};
}O24A0_LED_POLARIS_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0380 RW 0x0000_0000
	UINT32 pixel_comp_en                    :1;	//(0,RW,0x00) //pixel compensation enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_COMP_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0384 RW 0x0000_0200
	UINT32 const_gain                       :10;	//(9:0,RW,0x0200) //const gain for pixel compensation
	UINT32 resvd0                           :2;
	UINT32 const_gain_en                    :1;	//(12,RW,0x1) //const gain for pixel compensation_enable	1:const gain	0:BLE LUT
	UINT32 resvd1                           :3;
	UINT32 ble_com_gain_en                  :1;	//(16,RW,0x0) //smart gain enable 	1:ble_comp_gain	0:512
	UINT32 resvd2                           :15;
	};
}O24A0_LED_CONT_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0388 RW 0x0000_0000
	UINT32 comp_in_sel                      :2;	//(1:0,RW,0x00) //"0" : Max rgb	"1" : Y  	"2" : APL
	UINT32 resvd                            :30;
	};
}O24A0_LED_COMP_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E038C RW 0x0000_0000
	UINT32 pc_lut_raddr                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :9;
	UINT32 pc_lut_d_rden                    :1;	//(16,RW,0x00) //
	UINT32 pc_lut_c_rden                    :1;	//(17,RW,0x00) //
	UINT32 pc_lut_b_rden                    :1;	//(18,RW,0x00) //
	UINT32 pc_lut_a_rden                    :1;	//(19,RW,0x00) //
	UINT32 resvd1                           :12;
	};
}O24A0_LED_PC_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0390 RO 0x0000_0000
	UINT32 pc_lut_rdata                     :10;	//(9:0,RO,0x00) //read pixel compensation LUT data
	UINT32 resvd                            :22;
	};
}O24A0_LED_PC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0400 RW 0x0000_03FF
	UINT32 gbl                              :10;	//(9:0,RW,0x03FF) //BLU BV in Local dimming off mode
	UINT32 resvd                            :22;
	};
}O24A0_LED_GBL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0408 RW 0x0000_0000
	UINT32 bv_dly_ble                       :2;	//(1:0,RW,0x00) //for ble
	UINT32 resvd0                           :6;
	UINT32 bv_dly_blu                       :2;	//(9:8,RW,0x00) //for blu
	UINT32 resvd1                           :22;
	};
}O24A0_LED_BV_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E040C RW 0x0000_0000
	UINT32 blu_bv_sel                       :1;	//(0,RW,0x00) //Local dimming enable ?�서 ?�작	'0' : BV 	'1' : Average BV
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLU_BV_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0440 RW/RO 0x0000_0000
	UINT32 instr_wr_req                     :1;	//(0,RW,0x00) //instr_wr_reg
	UINT32 instr_wr_ack                     :1;	//(1,RO,0x00) //instr_wr_ack
	UINT32 resvd                            :30;
	};
}O24A0_LED_INSTR_WR_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0444 RW 0x0000_0000
	UINT32 wdata_instr                      :11;	//(10:0,RW,0x00) //write data
	UINT32 resvd0                           :5;
	UINT32 waddr_instr                      :4;	//(19:16,RW,0x00) //write address
	UINT32 resvd1                           :12;
	};
}O24A0_LED_INSTR_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0448 RW/RO 0x0000_0000
	UINT32 rdata_instr                      :11;	//(10:0,RO,0x00) //read data
	UINT32 resvd0                           :5;
	UINT32 raddr_instr                      :4;	//(19:16,RW,0x00) //read address
	UINT32 resvd1                           :12;
	};
}O24A0_LED_INSTR_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E044C RW/RO 0x0000_0000
	UINT32 debug_instr                      :11;	//(10:0,RO,0x00) //
	UINT32 resvd0                           :5;
	UINT32 debug_pc                         :4;	//(19:16,RO,0x00) //
	UINT32 resvd1                           :10;
	UINT32 reg_bv_stuck_clr                 :1;	//(30,RW,0x00) //1:bv_ctrl_stuck_clr_enable
	UINT32 bv_ctrl_err                      :1;	//(31,RO,0x00) //
	};
}O24A0_LED_INSTR_DGB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0480 RW 0x0000_0000
	UINT32 blc_mode                         :2;	//(1:0,RW,0x00) //blc mode control
	UINT32 resvd                            :30;
	};
}O24A0_LED_BLC_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0484 RW 0x0000_0100
	UINT32 bsf_c0                           :10;	//(9:0,RW,0x0100) //c0
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0488 RW 0x0000_0080
	UINT32 bsf_c1                           :10;	//(9:0,RW,0x080) //c1
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E048C RW 0x0000_0040
	UINT32 bsf_c2                           :10;	//(9:0,RW,0x040) //c2
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_C2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0490 RW 0x0000_03FF
	UINT32 bsf_ratio0                       :10;	//(9:0,RW,0x03FF) //
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_RATIO0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0494 RW 0x0000_0200
	UINT32 bsf_ratio1                       :10;	//(9:0,RW,0x0200) //
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_RATIO1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0498 RW 0x0000_0200
	UINT32 bsf_ratio2                       :10;	//(9:0,RW,0x0200) //
	UINT32 resvd                            :22;
	};
}O24A0_LED_BSF_RATIO2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E049C RW 0x0000_0000
	UINT32 a0_gn                            :8;	//(7:0,RW,0x0) //a0
	UINT32 resvd                            :24;
	};
}O24A0_LED_A0_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04A0 RW 0x0000_0000
	UINT32 a1_gn                            :8;	//(7:0,RW,0x0) //a1
	UINT32 resvd                            :24;
	};
}O24A0_LED_A1_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04A4 RW 0x0000_0000
	UINT32 a2_gn                            :8;	//(7:0,RW,0x0) //a2
	UINT32 resvd                            :24;
	};
}O24A0_LED_A2_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04A8 RW 0x0000_00FF
	UINT32 a0_ratio                         :8;	//(7:0,RW,0xFF) //
	UINT32 resvd                            :24;
	};
}O24A0_LED_A0_RATIO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04AC RW 0x0000_00FF
	UINT32 a1_ratio                         :8;	//(7:0,RW,0xFF) //
	UINT32 resvd                            :24;
	};
}O24A0_LED_A1_RATIO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04B0 RW 0x0000_03FF
	UINT32 drv_max                          :10;	//(9:0,RW,0x03FF) //
	UINT32 resvd                            :22;
	};
}O24A0_LED_DRV_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04B4 RW 0x0000_0000
	UINT32 blc_en                           :1;	//(0,RW,0x00) //blc enable
	UINT32 blc_tempo_en                     :1;	//(1,RW,0x00) //blc tempo enable
	UINT32 resvd                            :30;
	};
}O24A0_LED_BLC_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04B8 RW 0x0000_0000
	UINT32 blc_tempo_th                     :10;	//(9:0,RW,0x00) //blc tempo th
	UINT32 resvd                            :22;
	};
}O24A0_LED_BLC_TEMPO_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04BC RW 0x0000_0000
	UINT32 blc_frame_num                    :10;	//(9:0,RW,0x00) //blc frame num
	UINT32 resvd                            :22;
	};
}O24A0_LED_BLC_FRAME_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04C0 RO/WO 0x0000_0000
	UINT32 mem_dl_addr_clr                  :1;	//(0,WO,0x00) //clear bit
	UINT32 resvd0                           :15;
	UINT32 mem_dl_addr                      :12;	//(27:16,RO,0x00) //address
	UINT32 resvd1                           :4;
	};
}O24A0_LED_MEM_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04C4 WO 0x0000_0000
	UINT32 sbi_hcoeff                       :10;	//(9:0,WO,0x00) //EBI H coefficient
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_SBI_HCOEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04C8 WO 0x0000_0000
	UINT32 sbi_vcoeff                       :10;	//(9:0,WO,0x00) //EBI V coefficient
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_SBI_VCOEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04CC WO 0x0000_0000
	UINT32 pc_lut_a                         :10;	//(9:0,WO,0x00) //pixel comp. LUT A
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_PIXEL_COMP_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04D0 WO 0x0000_0000
	UINT32 pc_lut_b                         :10;	//(9:0,WO,0x00) //pixel comp. LUT B
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_PIXEL_COMP_B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04D4 WO 0x0000_0000
	UINT32 pc_lut_c                         :10;	//(9:0,WO,0x00) //pixel comp. LUT C
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_PIXEL_COMP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04D8 WO 0x0000_0000
	UINT32 pc_lut_d                         :10;	//(9:0,WO,0x00) //pixel comp. LUT D
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEM_DL_PIXEL_COMP_D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04DC WO 0x0000_0000
	UINT32 dc_lut_upper                     :10;	//(9:0,WO,0x00) //upper LUT
	UINT32 resvd                            :22;
	};
}O24A0_LED_UPPER_DC_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04E0 WO 0x0000_0000
	UINT32 dc_lut_lower                     :10;	//(9:0,WO,0x00) //lower LUT
	UINT32 resvd                            :22;
	};
}O24A0_LED_LOWER_DC_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04E4 WO 0x0000_0000
	UINT32 fc_tab1                          :10;	//(9:0,WO,0x00) //low resolution EBI 1tab coefficient
	UINT32 resvd                            :22;
	};
}O24A0_LED_FC_TAB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E04E8 WO 0x0000_0000
	UINT32 fc_tab5                          :10;	//(9:0,WO,0x00) //low resolution EBI 5tab coefficient
	UINT32 resvd                            :22;
	};
}O24A0_LED_FC_TAB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0500 RW 0x0000_0000
	UINT32 mean_in_sel                      :1;	//(0,RW,0x00) //'0' : Average of max(rgb)	'1' : Average of Y
	UINT32 resvd                            :31;
	};
}O24A0_LED_MEAN_IN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0504 RO 0x0000_0000
	UINT32 pixel_mean                       :10;	//(9:0,RO,0x00) //Calculated by mean_value block
	UINT32 resvd                            :22;
	};
}O24A0_LED_MEAN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0540 RW 0x0000_0000
	UINT32 rp_v_pos                         :12;	//(11:0,RW,0x00) //vertical pixel position
	UINT32 resvd0                           :4;
	UINT32 rp_h_pos                         :12;	//(27:16,RW,0x00) //horizontal pixel position
	UINT32 resvd1                           :4;
	};
}O24A0_LED_RP_HV_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0544 RW 0x0000_0000
	UINT32 mark_en                          :1;	//(0,RW,0x00) //mark enable for read a pixel
	UINT32 resvd                            :31;
	};
}O24A0_LED_RP_MAKE_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0548 RO 0x0000_0000
	UINT32 rd_pixel_r                       :14;	//(13:0,RO,0x0) //R value for a pixel
	UINT32 resvd                            :18;
	};
}O24A0_LED_RP_R_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E054C RO 0x0000_0000
	UINT32 rd_pixel_g                       :14;	//(13:0,RO,0x0) //G value for a pixel
	UINT32 resvd                            :18;
	};
}O24A0_LED_RP_G_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0550 RO 0x0000_0000
	UINT32 rd_pixel_b                       :14;	//(13:0,RO,0x0) //B value for a pixel
	UINT32 resvd                            :18;
	};
}O24A0_LED_RP_B_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0558 RW 0x0000_0000
	UINT32 alef2_en                         :1;	//(0,RW,0x00) //enable
	UINT32 resvd0                           :3;
	UINT32 alef2_gain_en                    :1;	//(4,RW,0x00) //gain
	UINT32 resvd1                           :3;
	UINT32 alef2_mode                       :1;	//(8,RW,0x00) //non-uniform blk L/D mode
	UINT32 resvd2                           :23;
	};
}O24A0_LED_ALEF2_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E055C RW 0x0000_0010
	UINT32 alef2_block_num                  :5;	//(4:0,RW,0x10) //number of block
	UINT32 resvd                            :27;
	};
}O24A0_LED_ALEF2_BLOCK_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0560 RW 0x0000_0000
	UINT32 alef2_addr_clr                   :1;	//(0,RW,0x00) //address clear
	UINT32 resvd                            :31;
	};
}O24A0_LED_ALEF2_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0564 WO 0x0000_0000
	UINT32 alef2_height                     :6;	//(5:0,WO,0x0) //non-uniform blk height
	UINT32 resvd0                           :2;
	UINT32 alef2_width                      :7;	//(14:8,WO,0x0) //non-uniform blk width
	UINT32 resvd1                           :1;
	UINT32 alef2_v_srt                      :6;	//(21:16,WO,0x0) //non-uniform blk start v
	UINT32 resvd2                           :2;
	UINT32 alef2_h_srt                      :7;	//(30:24,WO,0x0) //non-uniform blk  start h
	UINT32 resvd3                           :1;
	};
}O24A0_LED_ALEF2_CFG_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0568 RO/WO 0x0000_0000
	UINT32 rd_alef2_height                  :5;	//(4:0,RO,0x0) //read non-uniform blk height
	UINT32 resvd0                           :3;
	UINT32 rd_alef2_width                   :6;	//(13:8,RO,0x0) //read non-uniform blk width
	UINT32 resvd1                           :2;
	UINT32 rd_alef2_v_srt                   :5;	//(20:16,RO,0x0) //read non-uniform blk start v
	UINT32 resvd2                           :3;
	UINT32 rd_alef2_h_srt                   :6;	//(29:24,RO,0x0) //read non-uniform blk  start h
	UINT32 resvd3                           :1;
	UINT32 rd_alef2_cfg_re                  :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_ALEF2_CFG_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E056C WO 0x0000_0000
	UINT32 alef2_gain                       :10;	//(9:0,WO,0x00) //gain
	UINT32 resvd                            :22;
	};
}O24A0_LED_ALEF2_GAIN_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0570 RO/WO 0x0000_0000
	UINT32 rd_alef2_gain                    :10;	//(9:0,RO,0x00) //read gain
	UINT32 resvd                            :21;
	UINT32 alef2_gain_re                    :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_ALEF2_GAIN_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0574 WO 0x0000_0000
	UINT32 alef2_maxopt                     :8;	//(7:0,WO,0x0) //max opt
	UINT32 resvd                            :24;
	};
}O24A0_LED_ALEF2_MAXOPT_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0578 RO/WO 0x0000_0000
	UINT32 rd_alef2_maxopt                  :8;	//(7:0,RO,0x0) //read max opt
	UINT32 resvd                            :23;
	UINT32 alef2_maxopt_re                  :1;	//(31,WO,0x00) //
	};
}O24A0_LED_ALEF2_MAXOPT_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E057C RW 0x0000_0000
	UINT32 alef2_maxvalue_en                :16;	//(15:0,RW,0x0) //enable max value
	UINT32 resvd                            :16;
	};
}O24A0_LED_ALEF2_MAXVALUE_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0580 RW 0x0000_0000
	UINT32 display_bv_en                    :1;	//(0,RW,0x00) //display bv enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_DISP_BV_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0584 RW 0x0000_0000
	UINT32 display_bv_addr                  :13;	//(12:0,RW,0x00) //address for display_bv
	UINT32 resvd                            :19;
	};
}O24A0_LED_DSIP_BV_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05C0 RW 0x0000_0001
	UINT32 dither_en                        :1;	//(0,RW,0x01) //dither enable
	UINT32 dither_temp_en                   :1;	//(1,RW,0x00) //temporal dither enable
	UINT32 resvd                            :30;
	};
}O24A0_LED_DITHER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05C4 RW 0x0000_0001
	UINT32 dither2_en                       :1;	//(0,RW,0x01) //dither enable
	UINT32 dither_temp2_en                  :1;	//(1,RW,0x00) //temporal dither enable
	UINT32 resvd                            :30;
	};
}O24A0_LED_DITHER_EN_N2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05CC RW 0x0000_0000
	UINT32 ble_sld_sel                      :1;	//(0,RW,0x0) //sld sel for ble (optional) 0:same to blu 2:seperated
	UINT32 resvd0                           :3;
	UINT32 bpl_out_sel                      :1;	//(4,RW,0x00) //bpl_out_sel 0:hw mode 1: sw mode
	UINT32 resvd1                           :27;
	};
}O24A0_LED_BPL_SLD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05D0 RW 0x0000_0000
	UINT32 blu_gain_en                      :1;	//(0,RW,0x00) //blu gain enable
	UINT32 resvd0                           :3;
	UINT32 blu_gain_wr_mode                 :1;	//(4,RW,0x00) //blu gain lut r/w address mode	"0" : auto increment	"1" : manual
	UINT32 blu_rw_sel                       :1;	//(5,RW,0x0) //0:bpl 1:mura_comp
	UINT32 resvd1                           :2;
	UINT32 blu_gain_mode                    :2;	//(9:8,RW,0x00) //0:bv gain mode, 1:bv wr mode
	UINT32 resvd2                           :2;
	UINT32 blu_gain_lut_rd_sel              :1;	//(12,RW,0x00) //0:local/hif rd from mem0, 1:local/hif rd from mem1
	UINT32 blu_gain_lut_wr_sel              :1;	//(13,RW,0x00) //0:hif wr to mem0, 1:hif wr to mem1
	UINT32 resvd3                           :18;
	};
}O24A0_LED_BLU_GAIN_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05D4 RW 0x0000_0000
	UINT32 blu_gain_addr_clr                :1;	//(0,RW,0x00) //blu gain lut r/w address clear
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLU_GAIN_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05D8 RW 0x0000_0000
	UINT32 blu_gain_wdata                   :10;	//(9:0,RW,0x00) //blu gain lut write data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_waddr                   :13;	//(28:16,RW,0x00) //blu gain lut write address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BLU_GAIN_WD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05DC RO 0x0000_0000
	UINT32 blu_gain_rdata                   :10;	//(9:0,RO,0x00) //blu gain lut read data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_raddr                   :13;	//(28:16,RO,0x00) //blu gain lut read address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BLU_GAIN_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05E0 RW 0x0000_0000
	UINT32 blu_bv_addr_clr                  :1;	//(0,RW,0x00) //blu bv r address clear
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLU_BV_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05E4 RO 0x0000_0000
	UINT32 blu_gain_rdata                   :10;	//(9:0,RO,0x00) //blu gain lut read data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_raddr                   :11;	//(26:16,RO,0x00) //blu gain lut read address
	UINT32 resvd1                           :5;
	};
}O24A0_LED_BLU_BV_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05E8 RW 0x0000_0000
	UINT32 ble_gain_en                      :1;	//(0,RW,0x00) //ble gain enable
	UINT32 resvd0                           :3;
	UINT32 ble_gain_wr_mode                 :1;	//(4,RW,0x00) //ble gain lut r/w address mode	"0" : auto increment	"1" : manual
	UINT32 resvd1                           :3;
	UINT32 bld_gain_mode                    :2;	//(9:8,RW,0x00) //0:bv gain mode, 1:bv wr mode
	UINT32 resvd2                           :2;
	UINT32 ble_gain_lut_rd_sel              :1;	//(12,RW,0x00) //0:local/hif rd from mem0, 1:local/hif rd from mem1
	UINT32 ble_gain_lut_wr_sel              :1;	//(13,RW,0x00) //0:hif wr to mem0, 1:hif wr to mem1
	UINT32 resvd3                           :18;
	};
}O24A0_LED_BLE_GAIN_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05EC RW 0x0000_0000
	UINT32 ble_gain_addr_clr                :1;	//(0,RW,0x00) //ble gain lut r/w address clear
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLE_GAIN_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05F0 RW 0x0000_0000
	UINT32 ble_gain_wdata                   :10;	//(9:0,RW,0x00) //ble gain lut write data
	UINT32 resvd0                           :6;
	UINT32 ble_gain_waddr                   :13;	//(28:16,RW,0x00) //ble gain lut write address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BLE_GAIN_WD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E05F4 RO 0x0000_0000
	UINT32 ble_gain_rdata                   :10;	//(9:0,RO,0x00) //ble gain lut read data
	UINT32 resvd0                           :6;
	UINT32 ble_gain_raddr                   :13;	//(28:16,RO,0x00) //ble gain lut read address
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BLE_GAIN_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0600 RW 0x0000_0000
	UINT32 dpg_en                           :1;	//(0,RW,0x00) //"0" : bypass	"1" : gamma enable
	UINT32 resvd0                           :3;
	UINT32 dpg_rd_sel                       :1;	//(4,RW,0x00) //Operation lut memory select for debugging	"0" : channel 0	"1" : channel 1
	UINT32 resvd1                           :3;
	UINT32 dpg_bit_extension_mode           :2;	//(9:8,RW,0x0) //10bit to 15bit extension option	"00" : data , 00000	"01" : data , data[9:5]	"10" : data , 11111
	UINT32 resvd2                           :22;
	};
}O24A0_LED_DPG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0604 RW/RO 0x0000_0000
	UINT32 dpg_lut_update                   :1;	//(0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 dpg_wdone_o                      :1;	//(4,RW,0x00) //
	UINT32 dpg_wstart_o                     :1;	//(5,RW,0x00) //
	UINT32 resvd1                           :2;
	UINT32 dpg_lut_cpy_trig                 :2;	//(9:8,RW,0x00) //
	UINT32 resvd2                           :2;
	UINT32 dpg_lut_direct_mode              :1;	//(12,RW,0x00) //
	UINT32 resvd3                           :3;
	UINT32 dpg_lut_cpy_status               :2;	//(17:16,RO,0x00) //
	UINT32 resvd4                           :2;
	UINT32 dpg_lut_cpy_done                 :1;	//(20,RO,0x00) //
	UINT32 dpg_buf_rw_conflict              :1;	//(21,RO,0x00) //
	UINT32 resvd5                           :10;
	};
}O24A0_LED_DPG_LUT_WR_DONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0608 RW 0x0000_0000
	UINT32 dpg_wdata                        :15;	//(14:0,RW,0x0) //lut write data
	UINT32 resvd0                           :1;
	UINT32 dpg_waddr                        :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd1                           :2;
	UINT32 dpg_we                           :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}O24A0_LED_DPG_LUT_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E060C RW/RO 0x0000_0000
	UINT32 dpg_rdata                        :15;	//(14:0,RO,0x0) //lut read data
	UINT32 resvd0                           :1;
	UINT32 dpg_raddr                        :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 dpg_re                           :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 resvd2                           :1;
	};
}O24A0_LED_DPG_LUT_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0610 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 obj_bypass_gain                  :8;	//(23:16,RW,0x0) //obj_bypass_gain
	UINT32 resvd1                           :8;
	};
}O24A0_LED_BVGAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0614 RW 0x0000_0000
	UINT32 bv_gain_x3                       :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x2                       :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0618 RW 0x0000_0000
	UINT32 bv_gain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E061C RW 0x0000_0000
	UINT32 bvgain_y3                        :8;	//(7:0,NA,0x0) //
	UINT32 bvgain_y2                        :8;	//(15:8,NA,0x0) //
	UINT32 bvgain_y1                        :8;	//(23:16,NA,0x0) //
	UINT32 bvgain_y0                        :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0620 RW 0x0000_0000
	UINT32 avggain_x3                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x2                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0624 RW 0x0000_0000
	UINT32 avggain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0628 RW 0x0000_0000
	UINT32 avggain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 avggain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 avggain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 avggain_y0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E062C RW 0x0000_0000
	UINT32 objgain_x3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_x2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_x1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_x0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0630 RW 0x0000_0000
	UINT32 objgain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_y0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0634 RW 0x0000_0000
	UINT32 bvgain_en                        :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}O24A0_LED_BVGAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0638 RW 0x0000_0000
	UINT32 bv_gain_x3                       :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x2                       :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E063C RW 0x0000_0000
	UINT32 bv_gain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0640 RW 0x0000_0000
	UINT32 bvgain_y3                        :8;	//(7:0,NA,0x0) //
	UINT32 bvgain_y2                        :8;	//(15:8,NA,0x0) //
	UINT32 bvgain_y1                        :8;	//(23:16,NA,0x0) //
	UINT32 bvgain_y0                        :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0644 RW 0x0000_0000
	UINT32 avggain_x3                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x2                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0648 RW 0x0000_0000
	UINT32 avggain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVGAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E064C RW 0x0000_0000
	UINT32 avggain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 avggain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 avggain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 avggain_y0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0650 RW 0x0000_0000
	UINT32 objgain_x3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_x2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_x1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_x0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0654 RW 0x0000_0000
	UINT32 objgain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_y0                       :8;	//(31:24,NA,0x0) //
	};
}O24A0_LED_BVGAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0664 RO 0x0000_0000
	UINT32 bv_mid0_max                      :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_mid0_min                      :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_mid0_avg                      :10;	//(29:20,RO,0x00) //BV avg value in blu_if(mid0)
	UINT32 resvd                            :2;
	};
}O24A0_LED_BV_MID0_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0680 RW 0x0000_0000
	UINT32 bv_bpl_en                        :1;	//(0,NA,0x00) //
	UINT32 resvd0                           :15;
	UINT32 luma_bypass_gain                 :10;	//(25:16,NA,0x00) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0684 RW 0x0000_0000
	UINT32 bv_alpha_x1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0688 RW 0x0000_0000
	UINT32 bv_alpha_x3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E068C RW 0x0000_0000
	UINT32 bv_alpha_x5                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x4                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0690 RW 0x0000_0000
	UINT32 bv_alpha_x7                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x6                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0694 RW 0x0000_0000
	UINT32 bv_alpha_y1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0698 RW 0x0000_0000
	UINT32 bv_alpha_y3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E069C RW 0x0000_0000
	UINT32 bv_alpha_y5                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y4                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06A0 RW 0x0000_0000
	UINT32 bv_alpha_y7                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y6                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06A4 RW 0x0000_0000
	UINT32 avg_gain_x1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avg_gain_x0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06A8 RW 0x0000_0000
	UINT32 avg_gain_x3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avg_gain_x2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BVBPL_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06AC RW 0x0000_0000
	UINT32 avg_gain_y1                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 avg_gain_y0                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}O24A0_LED_BVBPL_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06B0 RW 0x0000_0000
	UINT32 avg_gain_y3                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 avg_gain_y2                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}O24A0_LED_BVBPL_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06B4 RO 0x0000_0000
	UINT32 bv_mid1_max                      :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_mid1_min                      :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_mid1_avg                      :10;	//(29:20,RO,0x00) //BV avg value in blu_if(mid0)
	UINT32 resvd                            :2;
	};
}O24A0_LED_BV_MID1_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06C0 RW 0x0000_0000
	UINT32 wb2p_en                          :1;	//(0,RW,0x0) //enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_WB2P_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06C4 RW 0x0000_0000
	UINT32 r_gain                           :16;	//(15:0,RW,0x0000_0000) //red gain (2.14)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_R_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06C8 RW 0x0000_0000
	UINT32 g_gain                           :16;	//(15:0,RW,0x0000_0000) //green gain (2.14)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_G_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06CC RW 0x0000_0000
	UINT32 b_gain                           :16;	//(15:0,RW,0x0000_0000) //blue gain (2.14)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_B_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06D0 RW 0x0000_0000
	UINT32 r_offset                         :16;	//(15:0,RW,0x0000_0000) //red offset (s13.3)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_R_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06D4 RW 0x0000_0000
	UINT32 g_offset                         :16;	//(15:0,RW,0x0000_0000) //green offset (s13.3)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_G_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06D8 RW 0x0000_0000
	UINT32 b_offset                         :16;	//(15:0,RW,0x0000_0000) //blue offset (s13.3)
	UINT32 resvd                            :16;
	};
}O24A0_LED_WB2P_B_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E06E0 RW 0x0000_0000
	UINT32 reg_bv_dsc_en                    :1;	//(0:0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_bv_gsc_gsc                   :1;	//(4:4,NA,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_bv_dsc_init_sel_o            :1;	//(8:8,NA,0x00) //0:bv_gen_end 1:m3(TF)end
	UINT32 reg_bv_dsc_fifo_init_sel_o       :1;	//(9:9,NA,0x00) //0:bv_gen_end 1:m3(TF)end
	UINT32 resvd2                           :22;
	};
}O24A0_LED_BV_GSC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0700 RW 0x0000_0000
	UINT32 out_crop_hs_width                :12;	//(11:0,RW,0x0000_0000) //hsync '0'??구간 width
	UINT32 resvd0                           :4;
	UINT32 out_crop_hs_offset               :12;	//(27:16,RW,0x0000_0000) //hsync '0'??구간 ?�작 offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_hs_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}O24A0_LED_OUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0704 RW 0x0000_0000
	UINT32 out_crop_ha_width                :12;	//(11:0,RW,0x0000_0000) //hactive '1'??구간 width
	UINT32 resvd0                           :4;
	UINT32 out_crop_ha_offset               :12;	//(27:16,RW,0x0000_0000) //hactive '1'??구간 ?�작 offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_ha_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}O24A0_LED_OUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0708 RW 0x0000_0000
	UINT32 out_crop_de_width                :12;	//(11:0,RW,0x0000_0000) //de '1'??구간 width
	UINT32 resvd0                           :4;
	UINT32 out_crop_de_offset               :12;	//(27:16,RW,0x0000_0000) //de '1'??구간 ?�작 offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_de_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}O24A0_LED_OUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E070C RW 0x0000_0000
	UINT32 o_3d_flag_en                     :1;	//(0:0,RW,0x00) //Enable 3D L/R Flag	 '0' := Disable	 '1'  = Enable
	UINT32 o_3d_flag_lr                     :1;	//(1:1,RW,0x00) //Frame L/R Flag
	UINT32 resvd0                           :1;
	UINT32 o_3d_flag_sel                    :1;	//(3:3,RW,0x00) //0' := VSD gen 3d flag	'1' := SW gen 3d flag
	UINT32 resvd1                           :28;
	};
}O24A0_LED_OUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0710 RW 0x0000_0000
	UINT32 top_led_pxl_clk_cg_ctrl          :16;	//(15:0,RW,0x0000_0000) //
	UINT32 top_led_pxl_clk_cg_on            :1;	//(16:16,RW,0x0000_0000) //
	UINT32 resvd                            :15;
	};
}O24A0_LED_OUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0714 RW 0x0000_0000
	UINT32 out_ctrl_05                      :32;	//(31:0,RW,0x0000_0000) //
	};
}O24A0_LED_OUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0718 RW 0x0000_0000
	UINT32 out_ctrl_06                      :32;	//(31:0,RW,0x0000_0000) //
	};
}O24A0_LED_OUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E071C RW 0x0000_0000
	UINT32 out_ctrl_07                      :32;	//(31:0,RW,0x0000_0000) //
	};
}O24A0_LED_OUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0770 RW 0x0000_0000
	UINT32 apl_mux_sel                      :1;	//(0,RW,0x0) //"0" : APL input = dpg data output	"1" : APL Input = odither output
	UINT32 resvd0                           :3;
	UINT32 apl_rgb_sel                      :1;	//(4,RW,0x0) //"0" : MAX RGB	"1" : Aver. RGB
	UINT32 resvd1                           :27;
	};
}O24A0_LED_APL_VALUE_OP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0774 RO 0x0000_0000
	UINT32 apl_max_lr                       :10;	//(9:0,RO,0x000) //apl max(L, R)
	UINT32 resvd                            :22;
	};
}O24A0_LED_APL_MAX_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0778 RO 0x0000_0000
	UINT32 apl_r                            :10;	//(9:0,RO,0x000) //right apl
	UINT32 resvd0                           :1;
	UINT32 apl_l                            :10;	//(20:11,RO,0x000) //left apl
	UINT32 resvd1                           :1;
	UINT32 apl_min_lr                       :10;	//(31:22,RO,0x000) //apl min(L, R)
	};
}O24A0_LED_APL_DBG_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0780 RW/RO 0x0000_0000
	UINT32 oapl_eotf_wr_done                :1;	//(0,RW,0x00) //"1" : lut write done
	UINT32 resvd0                           :3;
	UINT32 oapl_eotf_wr_status              :1;	//(4,RO,0x00) //lut write status
	UINT32 resvd1                           :27;
	};
}O24A0_LED_OAPL_EOTF_WR_DONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0784 RW 0x0000_0000
	UINT32 reg_oapl_eotf_wdata              :16;	//(15:0,RW,0x0) //lut write data
	UINT32 oapl_eotf_waddr                  :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd0                           :2;
	UINT32 oapl_eotf_we                     :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd1                           :1;
	};
}O24A0_LED_OAPL_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0788 RW/RO 0x0000_0000
	UINT32 oapl_eotf_rdata                  :16;	//(15:0,RO,0x0) //lut read data
	UINT32 oapl_eotf_raddr                  :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd0                           :2;
	UINT32 oapl_eotf_re                     :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 resvd1                           :1;
	};
}O24A0_LED_OAPL_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0800 RW 0x0000_0000
	UINT32 reg_sync_cnt_en                  :1;	//(0,RW,0x0) //enable sync_counter
	UINT32 reg_sync_cnt_vs_inv              :1;	//(1,RW,0x0) //vs inversion
	UINT32 reg_sync_cnt_hs_inv              :1;	//(2,RW,0x0) //hs inversion
	UINT32 resvd                            :29;
	};
}O24A0_LED_MON_SYNC_IN_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0804 RO 0x0000_0000
	UINT32 reg_sync_cnt_vs_active           :16;	//(15:0,RO,0x0) //vs high 구간??line ??
	UINT32 reg_sync_cnt_vs_total            :16;	//(31:16,RO,0x0) //vs total line ??frame total)
	};
}O24A0_LED_MON_SYNC_IN_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0808 RO 0x0000_0000
	UINT32 reg_sync_cnt_hs_active           :16;	//(15:0,RO,0x0) //hs high 구간??width
	UINT32 reg_sync_cnt_hs_total            :16;	//(31:16,RO,0x0) //hs total width(line width)
	};
}O24A0_LED_MON_SYNC_IN_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E080C RO 0x0000_0000
	UINT32 reg_sync_cnt_de_h_active         :16;	//(15:0,RO,0x0) //de width
	UINT32 reg_sync_cnt_de_v_active         :16;	//(31:16,RO,0x0) //de total line ??
	};
}O24A0_LED_MON_SYNC_IN_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0900 RW 0x0000_0000
	UINT32 bnh_blu_disp                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :9;
	UINT32 bnv_blu_disp                     :6;	//(21:16,RW,0x0) //
	UINT32 resvd1                           :10;
	};
}O24A0_LED_BLU_BLK_NUM_DISP_CLK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0904 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_REVERSE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0940 RW 0x0000_0002
	UINT32 max_opt_ai_illuminant            :8;	//(7:0,RW,0x2) //MAX_OPT value
	UINT32 resvd                            :24;
	};
}O24A0_LED_MAX_OPT_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0944 RW 0x0000_0000
	UINT32 blk_max_mode_ai_illuminant       :1;	//(0,RW,0x00) //"0": BV = (Σ AVG( R, G, B))/N	"1": BV = (Σ Max (R, G, B)) / N	Where N: Number of Pixel in a block
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLK_MAX_MODE_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0948 RW 0x0000_0000
	UINT32 max_opt_mode_ai_illuminant       :1;	//(0,RW,0x00) //"0" : normal operation using MAX_OPT register	"1" : adaptive operation using MAX_OPT0, MAX_OPT1 register
	UINT32 resvd                            :31;
	};
}O24A0_LED_MAX_OPT_MODE_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E094C RW 0x0000_40FF
	UINT32 max_opt1_ai_illuminant           :8;	//(7:0,RW,0xFF) //maximum MAX_OPT value
	UINT32 max_opt0_ai_illuminant           :8;	//(15:8,RW,0x40) //minimum MAX_OPT value
	UINT32 resvd                            :16;
	};
}O24A0_LED_MAX_OPT0_1_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0950 RW 0x0000_0320
	UINT32 level_th_ai_illuminant           :10;	//(9:0,RW,0x0320) //Pixel Level Threshold for Block Histogram
	UINT32 resvd                            :22;
	};
}O24A0_LED_LEVEL_TH_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0954 RW 0x0000_03E8
	UINT32 number_th_ai_illuminant          :12;	//(11:0,RW,0x03E8) //number threshold of Block Histogram
	UINT32 resvd0                           :4;
	UINT32 number_bit_sel_ai_illuminant     :4;	//(19:16,RW,0x00) //select 12bits of total 19 bits (Block histogram)
	UINT32 resvd1                           :12;
	};
}O24A0_LED_NUMBER_TH_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0958 RO 0x0000_0000
	UINT32 avg_bv_ai_illuminant             :10;	//(9:0,RO,0x00) //BLU 구동 BV???�균
	UINT32 resvd0                           :6;
	UINT32 apl_ai_illuminant                :10;	//(25:16,RO,0x00) //bv_gen block ?�서 계산??BV???�균
	UINT32 resvd1                           :6;
	};
}O24A0_LED_APL_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E095C RW 0x00C8_0190
	UINT32 bv_gen_x2_ai_illuminant          :10;	//(9:0,RW,0x0190) //x2 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x1_ai_illuminant          :10;	//(25:16,RW,0x0C8) //x1 APL
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_X1_X2_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0960 RW 0x0258_0320
	UINT32 bv_gen_x4_ai_illuminant          :10;	//(9:0,RW,0x0320) //x4 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x3_ai_illuminant          :10;	//(25:16,RW,0x0258) //x3 APL
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_X3_X4_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0964 RW 0x0000_0000
	UINT32 bv_gen_y1_ai_illuminant          :10;	//(9:0,RW,0x00) //y1 (x = x1)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y0_ai_illuminant          :10;	//(25:16,RW,0x00) //y0 (x = 0)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y0_Y1_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0968 RW 0x0000_0000
	UINT32 bv_gen_y3_ai_illuminant          :10;	//(9:0,RW,0x00) //y3 (x = x3)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y2_ai_illuminant          :10;	//(25:16,RW,0x00) //y2 (x = x2)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y2_Y3_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E096C RW 0x0000_0000
	UINT32 bv_gen_y5_ai_illuminant          :10;	//(9:0,RW,0x00) //y5 (x = 1023)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y4_ai_illuminant          :10;	//(25:16,RW,0x00) //y4 (x = x4)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_Y4_Y5_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0970 RO 0x0000_0000
	UINT32 bvgen_max_ai_illuminant          :10;	//(9:0,RO,0x00) //BV max value in bv_gen
	UINT32 resvd0                           :6;
	UINT32 bvgen_min_ai_illuminant          :10;	//(25:16,RO,0x00) //BV min value in bv_gen
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_GEN_BV_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0974 RO 0x0000_0000
	UINT32 max_bv_ai_illuminant             :10;	//(9:0,RO,0x00) //BV max value in bv_ctrl
	UINT32 resvd0                           :6;
	UINT32 min_bv_ai_illuminant             :10;	//(25:16,RO,0x00) //BV min value in bv_ctrl
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0978 RO 0x0000_0000
	UINT32 bv_lut_max_ai_illuminant         :10;	//(9:0,RO,0x00) //BV max value in bv_lut
	UINT32 resvd0                           :6;
	UINT32 bv_lut_min_ai_illuminant         :10;	//(25:16,RO,0x00) //BV min value in bv_lut
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BV_LUT_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E097C RO 0x0000_0000
	UINT32 bv_final_max_ai_illuminant       :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_final_min_ai_illuminant       :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_final_avg_ai_illuminant       :10;	//(29:20,RO,0x00) //BV avg value in blu_if(final)
	UINT32 resvd                            :2;
	};
}O24A0_LED_BV_FINAL_AVG_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0980 RW 0x0000_0001
	UINT32 mode_2ch_ai_illuminant           :1;	//(0,RW,0x01) //dual channel mode
	UINT32 resvd                            :31;
	};
}O24A0_LED_VIN_CONFIG_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0984 RW 0x0000_0000
	UINT32 bnh_bv_gen_ai_illuminant         :7;	//(6:0,RW,0x0) //number of Horizontal blocks
	UINT32 resvd0                           :9;
	UINT32 bnv_bv_gen_ai_illuminant         :6;	//(21:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :10;
	};
}O24A0_LED_BV_GEN_BLK_NUM_HV_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0988 RW 0x0000_0000
	UINT32 bsh_bv_gen_ai_illuminant         :13;	//(12:0,RW,0x00) //Horizontal size of a block
	UINT32 resvd0                           :3;
	UINT32 bsv_bv_gen_ai_illuminant         :12;	//(27:16,RW,0x00) //Vertical size of a block
	UINT32 resvd1                           :4;
	};
}O24A0_LED_BV_GEN_HV_SIZE_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E098C RW 0x0000_0000
	UINT32 bpl_in_sel                       :1;	//(0:0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}O24A0_LED_BPL_IN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0990 RW 0x0000_0000
	UINT32 ai_illuminant_map_sel_o          :1;	//(0:0,RW,0x0) //reverse setting not use
	UINT32 resvd                            :31;
	};
}O24A0_LED_AI_ILLUMINANT_MAP_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0994 RW 0x0000_0000
	UINT32 cc_ld_direct_path_sel_o          :1;	//(0:0,RW,0x0) //local contrast path sel
	UINT32 resvd                            :31;
	};
}O24A0_LED_CC_LD_DIRECT_PATH_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09C0 RW 0xFF00_0044
	UINT32 reg_textgain_en                  :1;	//(0:0,RW,0x00) //reg_textgain_en
	UINT32 reg_bodygain_en                  :1;	//(1:1,RW,0x00) //reg_bodygain_en
	UINT32 reg_headgain_en                  :1;	//(2:2,RW,0x01) //reg_headgain_en
	UINT32 resvd0                           :1;
	UINT32 reg_objt_text_sel                :2;	//(5:4,RW,0x00) //reg_objt_text_sel
	UINT32 reg_head_body_sel                :1;	//(6:6,RW,0x01) //reg_head_body_sel
	UINT32 resvd1                           :1;
	UINT32 reg_text_master_gain             :8;	//(15:8,RW,0x00) //reg_text_master_gain
	UINT32 reg_body_master_gain             :8;	//(23:16,RW,0x00) //reg_body_master_gain
	UINT32 reg_head_master_gain             :8;	//(31:24,RW,0xFF) //reg_head_master_gain
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09C4 RW 0x0000_4040
	UINT32 reg_headgain_y1                  :8;	//(7:0,RW,0x40) //reg_headgain_y1
	UINT32 reg_headgain_x1                  :8;	//(15:8,RW,0x40) //reg_headgain_x1
	UINT32 reg_headgain_y0                  :8;	//(23:16,RW,0x00) //reg_headgain_y0
	UINT32 reg_headgain_x0                  :8;	//(31:24,RW,0x00) //reg_headgain_x0
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09C8 RW 0x8080_FFFF
	UINT32 reg_headgain_y3                  :8;	//(7:0,RW,0xFF) //reg_headgain_y3
	UINT32 reg_headgain_x3                  :8;	//(15:8,RW,0xFF) //reg_headgain_x3
	UINT32 reg_headgain_y2                  :8;	//(23:16,RW,0x80) //reg_headgain_y2
	UINT32 reg_headgain_x2                  :8;	//(31:24,RW,0x80) //reg_headgain_x2
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09CC RW 0x0000_4040
	UINT32 reg_bodygain_y1                  :8;	//(7:0,RW,0x40) //reg_bodygain_y1
	UINT32 reg_bodygain_x1                  :8;	//(15:8,RW,0x40) //reg_bodygain_x1
	UINT32 reg_bodygain_y0                  :8;	//(23:16,RW,0x00) //reg_bodygain_y0
	UINT32 reg_bodygain_x0                  :8;	//(31:24,RW,0x00) //reg_bodygain_x0
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09D0 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3                  :8;	//(7:0,RW,0xFF) //reg_bodygain_y3
	UINT32 reg_bodygain_x3                  :8;	//(15:8,RW,0xFF) //reg_bodygain_x3
	UINT32 reg_bodygain_y2                  :8;	//(23:16,RW,0x80) //reg_bodygain_y2
	UINT32 reg_bodygain_x2                  :8;	//(31:24,RW,0x80) //reg_bodygain_x2
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09D4 RW 0x0000_4040
	UINT32 reg_textgain_y1                  :8;	//(7:0,RW,0x40) //reg_textgain_y1
	UINT32 reg_textgain_x1                  :8;	//(15:8,RW,0x40) //reg_textgain_x1
	UINT32 reg_textgain_y0                  :8;	//(23:16,RW,0x00) //reg_textgain_y0
	UINT32 reg_textgain_x0                  :8;	//(31:24,RW,0x00) //reg_textgain_x0
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09D8 RW 0x8080_FFFF
	UINT32 reg_textgain_y3                  :8;	//(7:0,RW,0xFF) //reg_textgain_y3
	UINT32 reg_textgain_x3                  :8;	//(15:8,RW,0xFF) //reg_textgain_x3
	UINT32 reg_textgain_y2                  :8;	//(23:16,RW,0x80) //reg_textgain_y2
	UINT32 reg_textgain_x2                  :8;	//(31:24,RW,0x80) //reg_textgain_x2
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09DC RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x00) //reg_pxl_x
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15:15,RW,0x00) //reg_win_in_disable
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x00) //reg_pxl_y
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31:31,RW,0x00) //reg_win_out_disable
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09E0 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,NA,0x00) //reg_pxl_w
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :13;	//(28:16,RW,0x00) //reg_pxl_h
	UINT32 resvd1                           :3;
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E09E4 RW 0x0000_0000
	UINT32 reg_win_out_objt_gain            :8;	//(7:0,NA,0x00) //reg_win_out_objt_gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_in_objt_gain             :8;	//(23:16,RW,0x00) //reg_win_in_objt_gain
	UINT32 resvd1                           :8;
	};
}O24A0_LED_AIBVGAIN_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A00 RW 0x0000_0000
	UINT32 reg_pixel_comp_lut_y_0           :10;	//(9:0,RW,0x0000) //reg_pixel_comp_lut_xy_0
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_0           :10;	//(25:16,RW,0x0000) //reg_pixel_comp_lut_xy_0
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A04 RW 0x0200_0200
	UINT32 reg_pixel_comp_lut_y_1           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_1
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_1           :10;	//(25:16,RW,0x0200) //reg_pixel_comp_lut_x_1
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A08 RW 0x0400_0400
	UINT32 reg_pixel_comp_lut_y_2           :10;	//(9:0,NA,0x0400) //reg_pixel_comp_lut_y_2
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_2           :10;	//(25:16,RW,0x0400) //reg_pixel_comp_lut_x_2
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A0C RW 0x0600_0600
	UINT32 reg_pixel_comp_lut_y_3           :10;	//(9:0,NA,0x0600) //reg_pixel_comp_lut_y_3
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_3           :10;	//(25:16,RW,0x0600) //reg_pixel_comp_lut_x_3
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A10 RW 0x0800_0800
	UINT32 reg_pixel_comp_lut_y_4           :10;	//(9:0,NA,0x0800) //reg_pixel_comp_lut_y_4
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_4           :10;	//(25:16,RW,0x0800) //reg_pixel_comp_lut_x_4
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A14 RW 0x0A00_0A00
	UINT32 reg_pixel_comp_lut_y_5           :10;	//(9:0,NA,0x0A00) //reg_pixel_comp_lut_y_5
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_5           :10;	//(25:16,RW,0x0A00) //reg_pixel_comp_lut_x_5
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A18 RW 0x0C00_0C00
	UINT32 reg_pixel_comp_lut_y_6           :10;	//(9:0,NA,0x0C00) //reg_pixel_comp_lut_y_6
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_6           :10;	//(25:16,RW,0x0C00) //reg_pixel_comp_lut_x_6
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A1C RW 0x0FFF_0FFF
	UINT32 reg_pixel_comp_lut_y_7           :10;	//(9:0,NA,0x0FFF) //reg_pixel_comp_lut_y_7
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_7           :10;	//(25:16,RW,0x0FFF) //reg_pixel_comp_lut_x_7
	UINT32 resvd1                           :6;
	};
}O24A0_LED_COMP_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A40 RW 0x0000_0000
	UINT32 reg_y_delay                      :2;	//(1:0,RW,0x0) //Yn    0 : no delay, 1: Pre, 2: Delay
	UINT32 resvd0                           :2;
	UINT32 reg_cb_delay                     :2;	//(5:4,RW,0x0) //Cb/Cr   0 : no delay, 1: Pre, 2: Delay
	UINT32 reg_cr_delay                     :2;	//(7:6,RW,0x0) //Yn+1    0 : no delay, 1: Pre, 2: Delay
	UINT32 reg_chroma_sample_eo             :1;	//(8:8,RW,0x0) //Even, Odd of data_in swap [19:10]=>[9:0], [9:0] => [19:10]
	UINT32 reg_yn1_swap                     :1;	//(9:9,RW,0x0) //Yn+1 out swap  0 : Yn+1(Cr), CbCr(Cb) 1 : Yn+1(Cb), CbCr(Cr)
	UINT32 reg_wr_swap                      :1;	//(10:10,RW,0x0) //Write memory port 0 : Cr  1 : Cb
	UINT32 resvd1                           :21;
	};
}O24A0_LED_OUT_PROC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A44 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A48 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A4C RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A50 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A54 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A58 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A5C RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A68 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_DISP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A6C RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_DISP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A70 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}O24A0_LED_OUT_PROC_CTRL_DISP_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A74 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_00              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A78 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_01              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A7C RO 0x0000_0000
	UINT32 reg_out_proc_dbg_02              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A80 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_03              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A84 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_04              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A88 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_05              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A8C RO 0x0000_0000
	UINT32 reg_out_proc_dbg_06              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A90 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_07              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A94 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_08              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A98 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_09              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0A9C RO 0x0000_0000
	UINT32 reg_out_proc_dbg_10              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AA0 RO 0x0000_0000
	UINT32 reg_out_proc_dbg_11              :32;	//(31:0,RO,0x0) //
	};
}O24A0_LED_OUT_PROC_DBG_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AA4 RW 0x0000_0000
	UINT32 hv_boundary_en                   :1;	//(0:0,RW,0x0) //1'b1 : hv boundary enable	1'b0 : hv boundary detour
	UINT32 resvd                            :31;
	};
}O24A0_LED_BOUNDARY_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AA8 RW 0x0000_0000
	UINT32 height_i                         :13;	//(12:0,RW,0x00) //input image height(2??배수)
	UINT32 resvd0                           :3;
	UINT32 width_i                          :13;	//(28:16,RW,0x00) //input image width (2??배수)
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BOUNDARY_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AAC RW 0x0000_0000
	UINT32 repeat_pixel_position            :13;	//(12:0,RW,0x00) //the pixel to repeat (the position of pixel 2??배수)
	UINT32 resvd                            :19;
	};
}O24A0_LED_BOUNDARY_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AB0 RW 0x0000_0000
	UINT32 hv_boundary_h_detect_insert_value_y_evn :10;	//(9:0,RW,0x00) //h detection y_evn value insert(y channel)
	UINT32 resvd0                           :6;
	UINT32 hv_boundary_h_detect_insert_value_en :1;	//(16,RW,0x0) //h detection value insert enable	0:disable	1:enable
	UINT32 resvd1                           :15;
	};
}O24A0_LED_BOUNDARY_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AB4 RW 0x0000_0000
	UINT32 hv_boundary_h_detect_insert_value_cbcr :10;	//(9:0,RW,0x00) //h detection detection cbcr value insert(cb channel)
	UINT32 resvd0                           :6;
	UINT32 hv_boundary_h_detect_insert_value_y_odd :10;	//(25:16,RW,0x00) //h detection detection y_odd value insert (cr channel)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BOUNDARY_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AB8 RW 0x0000_0000
	UINT32 hv_boundary_v_detect_insert_value_y_evn :10;	//(9:0,RW,0x00) //v detection y_evn value insert(y channel)
	UINT32 resvd0                           :6;
	UINT32 hv_boundary_v_detect_insert_value_en :1;	//(16,RW,0x0) //v detection value insert enable	0:disable	1:enable
	UINT32 resvd1                           :15;
	};
}O24A0_LED_BOUNDARY_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0ABC RW 0x0000_0000
	UINT32 hv_boundary_v_detect_insert_value_cbcr :10;	//(9:0,RW,0x00) //v detection cbcr value insert(cb channel)
	UINT32 resvd0                           :6;
	UINT32 hv_boundary_v_detect_insert_value_y_odd :10;	//(25:16,RW,0x00) //v detection y_odd value insert (cr channel)
	UINT32 resvd1                           :6;
	};
}O24A0_LED_BOUNDARY_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AC0 RO 0x0000_0000
	UINT32 c_line_cnt                       :13;	//(12:0,RO,0x00) //c line status
	UINT32 resvd0                           :3;
	UINT32 y_line_cnt                       :13;	//(28:16,RO,0x00) //y line status
	UINT32 resvd1                           :3;
	};
}O24A0_LED_BOUNDARY_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AC4 RW 0x1000_3210
	UINT32 ch0_sel                          :2;	//(1:0,RW,0x0) //ch0_sel	0:ch0	1:ch1	2:ch2	3:ch3
	UINT32 resvd0                           :2;
	UINT32 ch1_sel                          :2;	//(5:4,RW,0x1) //ch1_sel	0:ch0	1:ch1	2:ch2	3:ch3
	UINT32 resvd1                           :2;
	UINT32 ch2_sel                          :2;	//(9:8,RW,0x2) //ch2_sel	0:ch0	1:ch1	2:ch2	3:ch3
	UINT32 resvd2                           :2;
	UINT32 ch3_sel                          :2;	//(13:12,RW,0x3) //ch3_sel	0:ch0	1:ch1	2:ch2	3:ch3
	UINT32 resvd3                           :2;
	UINT32 mpip_ch_swap_enable              :1;	//(16,RW,0x0) //mpip_ch_swap_enable	0:ch_swap disable	1:ch_swap_enable
	UINT32 resvd4                           :7;
	UINT32 mpip_cbcr_swap                   :1;	//(24,RW,0x0) //mpip_cbcr_swap	0:cbcr_swap disable	1:cbcr_swap_enable
	UINT32 resvd5                           :3;
	UINT32 mpip_swap_enable                 :1;	//(28,RW,0x1) //mpip_swap_enable	0:disable	1:enable
	UINT32 mpip_swap_mpip_data_off          :1;	//(29,RW,0x0) //mpip_swap_data_off	0:mpip_data	1:0
	UINT32 resvd6                           :2;
	};
}O24A0_LED_MPIP_SWAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AC8 RW 0x0870_0780
	UINT32 mpip_swap_h_size                 :13;	//(12:0,RW,0x780) //mpip_swap_h_size
	UINT32 resvd0                           :3;
	UINT32 mpip_swap_v_size                 :13;	//(28:16,RW,0x870) //mpip_swap_v_size
	UINT32 resvd1                           :3;
	};
}O24A0_LED_MPIP_SWAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0ACC RW 0x0000_3210
	UINT32 inp_channel_mux_order_0          :4;	//(3:0,RW,0x0) //inp_channel_mux_order_0
	UINT32 inp_channel_mux_order_1          :4;	//(7:4,RW,0x1) //inp_channel_mux_order_1
	UINT32 inp_channel_mux_order_2          :4;	//(11:8,RW,0x2) //inp_channel_mux_order_2
	UINT32 inp_channel_mux_order_3          :4;	//(15:12,RW,0x3) //inp_channel_mux_order_3
	UINT32 resvd                            :16;
	};
}O24A0_LED_MPIP_SWAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AD0 RW 0x0000_3210
	UINT32 out_channel_mux_order_0          :4;	//(3:0,RW,0x0) //inp_channel_mux_order_0
	UINT32 out_channel_mux_order_1          :4;	//(7:4,RW,0x1) //inp_channel_mux_order_1
	UINT32 out_channel_mux_order_2          :4;	//(11:8,RW,0x2) //inp_channel_mux_order_2
	UINT32 out_channel_mux_order_3          :4;	//(15:12,RW,0x3) //inp_channel_mux_order_3
	UINT32 resvd                            :16;
	};
}O24A0_LED_MPIP_SWAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AD4 RW 0x0000_0001
	UINT32 inp_ha_align_check_enable        :1;	//(0,RW,0x1) //inp_ha_align_check_enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_MPIP_SWAP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AD8 RW 0x0000_0001
	UINT32 out_ha_align_check_enable        :1;	//(0,RW,0x1) //out_ha_align_check_enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_MPIP_SWAP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0ADC RO 0x0000_0000
	UINT32 inp_main_sub_diff_cnt            :13;	//(12:0,RO,0x00) //inp_main_sub_diff_cnt
	UINT32 resvd0                           :3;
	UINT32 inp_main_sub_ha_location_check   :2;	//(17:16,RO,0x00) //inp_main_sub_ha_location_check
	UINT32 resvd1                           :2;
	UINT32 inp_sub_diff_cnt                 :4;	//(23:20,RO,0x00) //inp_sub_diff_cnt
	UINT32 inp_main_diff_cnt                :4;	//(27:24,RO,0x00) //inp_main_diff_cnt
	UINT32 resvd2                           :4;
	};
}O24A0_LED_MPIP_STATUS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AE0 RO 0x0000_0000
	UINT32 out_main_sub_diff_cnt            :13;	//(12:0,RO,0x00) //out_main_sub_diff_cnt
	UINT32 resvd0                           :3;
	UINT32 out_main_sub_ha_location_check   :2;	//(17:16,RO,0x00) //out_main_sub_ha_location_check
	UINT32 resvd1                           :2;
	UINT32 out_sub_diff_cnt                 :4;	//(23:20,RO,0x00) //out_sub_diff_cnt
	UINT32 out_main_diff_cnt                :4;	//(27:24,RO,0x00) //out_main_diff_cnt
	UINT32 resvd2                           :4;
	};
}O24A0_LED_MPIP_STATUS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E0AE4 RW 0x0000_0000
	UINT32 fps                              :8;	//(7:0,RW,0x0) //fps
	UINT32 resvd                            :24;
	};
}O24A0_LED_FPS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2000 RW 0x0000_0000
	UINT32 bnh_blu_if                       :7;	//(6:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :9;
	UINT32 bnv_blu_if                       :6;	//(21:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :10;
	};
}O24A0_LED_BLU_BLK_NUM_HV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2004 RW 0x0000_0000
	UINT32 vs_mode                          :2;	//(1:0,RW,0x00) //"00" : every frame	"01" : frame
	UINT32 vs_neg                           :1;	//(2,RW,0x0) //vsync negation
	UINT32 va_mode                          :1;	//(3,RW,0x0) //0' : Internal vsync	'1' : External vsync
	UINT32 vs1_mode                         :2;	//(5:4,RW,0x00) //"00" : every frame	"01" : frame
	UINT32 vs1_neg                          :1;	//(6,RW,0x0) //vsync negation
	UINT32 va1_mode                         :1;	//(7,RW,0x0) //0' : Internal vsync	'1' : External vsync
	UINT32 vs2_mode                         :2;	//(9:8,RW,0x00) //"00" : every frame	"01" : frame
	UINT32 vs2_neg                          :1;	//(10,RW,0x0) //vsync negation
	UINT32 va2_mode                         :1;	//(11,RW,0x0) //0' : Internal vsync	'1' : External vsync
	UINT32 vs3_mode                         :2;	//(13:12,RW,0x00) //"00" : every frame	"01" : frame
	UINT32 vs3_neg                          :1;	//(14,RW,0x0) //vsync negation
	UINT32 va3_mode                         :1;	//(15,RW,0x0) //0' : Internal vsync	'1' : External vsync
	UINT32 resvd                            :16;
	};
}O24A0_LED_VS_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2008 RW 0x0000_0000
	UINT32 blu_vs_num                       :3;	//(2:0,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs1_num                      :3;	//(5:3,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs2_num                      :3;	//(8:6,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs3_num                      :3;	//(11:9,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 resvd                            :20;
	};
}O24A0_LED_BLU_VS_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E200C RW 0x0000_0000
	UINT32 blu_vs_t0                        :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}O24A0_LED_BLU_VS_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2010 RW 0x0000_0000
	UINT32 vs_delay                         :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}O24A0_LED_VS_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2014 RW 0x0000_001E
	UINT32 i2c_slave_addr                   :8;	//(7:0,RW,0x1E) //
	UINT32 resvd                            :24;
	};
}O24A0_LED_I2C_SLAVE_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2018 RW 0x007D_0000
	UINT32 time_out                         :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 hold_scl                         :8;	//(23:16,RW,0x7D) //
	UINT32 resvd1                           :8;
	};
}O24A0_LED_I2C_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E201C RW 0x0000_0000
	UINT32 version                          :32;	//(31:0,RW,0x0000_0000) //version
	};
}O24A0_LED_VERSION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2020 RW 0x0000_0000
	UINT32 general_reg0                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}O24A0_LED_GENERAL_REG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2024 RW 0x0000_0000
	UINT32 general_reg1                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}O24A0_LED_GENERAL_REG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2028 RW 0x0000_0000
	UINT32 general_reg2                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}O24A0_LED_GENERAL_REG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E202C RW 0x0000_0000
	UINT32 general_reg3                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}O24A0_LED_GENERAL_REG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2030 RW 0x0000_0000
	UINT32 reg_led_ldim_cg_on               :1;	//(0,RW,0x0) //local dimming clock gating enable
	UINT32 resvd0                           :3;
	UINT32 reg_led_ldim_bypass_en           :1;	//(4,RW,0x1) //local dimming bypass enable
	UINT32 resvd1                           :27;
	};
}O24A0_LED_CG_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2040 RW 0x0000_0000
	UINT32 blu_i2c_rd_on                    :1;	//(0,RW,0x00) //read ON
	UINT32 resvd                            :31;
	};
}O24A0_LED_I2C_RD_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2044 RW 0x0000_0000
	UINT32 blu_i2c_raddr                    :14;	//(13:0,RW,0x00) //read address
	UINT32 resvd                            :18;
	};
}O24A0_LED_I2C_RD_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2048 RO 0x0000_0000
	UINT32 blu_i2c_rdata                    :10;	//(9:0,RO,0x00) //read data
	UINT32 resvd                            :22;
	};
}O24A0_LED_I2C_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E204C RW 0x0000_0000
	UINT32 blu_vs1_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}O24A0_LED_BLU_VS1_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2050 RW 0x0000_0000
	UINT32 vs1_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}O24A0_LED_VS1_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2054 RW 0x0000_0000
	UINT32 blu_vs2_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}O24A0_LED_BLU_VS2_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2058 RW 0x0000_0000
	UINT32 vs2_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}O24A0_LED_VS2_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E205C RW 0x0000_0000
	UINT32 blu_vs3_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}O24A0_LED_BLU_VS3_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2060 RW 0x0000_0000
	UINT32 vs3_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}O24A0_LED_VS3_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2080 RW 0x0000_0000
	UINT32 spi_cpha                         :1;	//(0,RW,0x00) //Select the phase of the SPI clock
	UINT32 spi_cpol                         :1;	//(1,RW,0x00) //Select the polarity of the SPI clock
	UINT32 spi_16b                          :1;	//(2,RW,0x00) //16 bit data mode
	UINT32 spi_10b                          :1;	//(3,RW,0x00) //10 bit data mode
	UINT32 fld_16b_shift                    :3;	//(6:4,RW,0x00) //left shift (0~6) not use
	UINT32 spi_12b                          :1;	//(7,RW,0x00) //12 bit data mode
	UINT32 resvd                            :24;
	};
}O24A0_LED_SPI_CFG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2084 RW 0x0000_0000
	UINT32 spi_cmd_mod                      :3;	//(2:0,RW,0x00) //Number of Command
	UINT32 resvd0                           :1;
	UINT32 spi3_cmd1_bv_avg_mode            :1;	//(4,RW,0x00) //0:spi_cmd1 1:avg_final_bv
	UINT32 spi3_cmd2_bv_avg_mode            :1;	//(5,RW,0x00) //0:spi_cmd2 1:avg_final_bv
	UINT32 spi3_cmd3_bv_avg_mode            :1;	//(6,RW,0x00) //0:spi_cmd3 1:avg_final_bv
	UINT32 spi2_cmd1_bv_avg_mode            :1;	//(7,RW,0x00) //0:spi_cmd1 1:avg_final_bv
	UINT32 spi2_cmd2_bv_avg_mode            :1;	//(8,RW,0x00) //0:spi_cmd2 1:avg_final_bv
	UINT32 spi2_cmd3_bv_avg_mode            :1;	//(9,RW,0x00) //0:spi_cmd3 1:avg_final_bv
	UINT32 spi1_cmd1_bv_avg_mode            :1;	//(10,RW,0x00) //0:spi_cmd1 1:avg_final_bv
	UINT32 spi1_cmd2_bv_avg_mode            :1;	//(11,RW,0x00) //0:spi_cmd2 1:avg_final_bv
	UINT32 spi1_cmd3_bv_avg_mode            :1;	//(12,RW,0x00) //0:spi_cmd3 1:avg_final_bv
	UINT32 spi0_cmd1_bv_avg_mode            :1;	//(13,RW,0x00) //0:spi_cmd1 1:avg_final_bv
	UINT32 spi0_cmd2_bv_avg_mode            :1;	//(14,RW,0x00) //0:spi_cmd2 1:avg_final_bv
	UINT32 spi0_cmd3_bv_avg_mode            :1;	//(15,RW,0x00) //0:spi_cmd3 1:avg_final_bv
	UINT32 resvd1                           :16;
	};
}O24A0_LED_SPI_CMD_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2088 RW 0x0000_000F
	UINT32 mask_ch3                         :1;	//(0,RW,0x01) //
	UINT32 mask_ch2                         :1;	//(1,RW,0x01) //
	UINT32 mask_ch1                         :1;	//(2,RW,0x01) //
	UINT32 mask_ch0                         :1;	//(3,RW,0x01) //
	UINT32 resvd                            :28;
	};
}O24A0_LED_M_SPI_CH_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E208C RW 0x00AB_00AA
	UINT32 spi_idc0                         :16;	//(15:0,RW,0xAA) //Channel ID for SPI Master Channel 0
	UINT32 spi_idc1                         :16;	//(31:16,RW,0xAB) //Channel ID for SPI Master Channel 1
	};
}O24A0_LED_SPI_IDC01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2090 RW 0x00AD_00AC
	UINT32 spi_idc2                         :16;	//(15:0,RW,0xAC) //Channel ID for SPI Master Channel 2
	UINT32 spi_idc3                         :16;	//(31:16,RW,0xAD) //Channel ID for SPI Master Channel 3
	};
}O24A0_LED_SPI_IDC23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2094 RW 0x0000_0000
	UINT32 spi_cmd0                         :16;	//(15:0,RW,0x0) //The first SPI Command
	UINT32 spi_cmd1                         :16;	//(31:16,RW,0x0) //The second SPI Command
	};
}O24A0_LED_SPI_CMD01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2098 RW 0x0000_0000
	UINT32 spi_cmd2                         :16;	//(15:0,RW,0x0) //The third SPI Command
	UINT32 spi_cmd3                         :16;	//(31:16,RW,0x0) //The fourth SPI Command
	};
}O24A0_LED_SPI_CMD23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E209C RW 0x0000_0052
	UINT32 sclk_t1                          :16;	//(15:0,RW,0x52) //Timing value T1 for the SPI clock
	UINT32 resvd                            :16;
	};
}O24A0_LED_SCLK_T1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20A0 RW 0x0000_0028
	UINT32 sclk_t2                          :16;	//(15:0,RW,0x28) //Timing value T2 for the SPI clock
	UINT32 resvd                            :16;
	};
}O24A0_LED_SCLK_T2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20A4 RW 0x0000_0029
	UINT32 sclk_t3                          :16;	//(15:0,RW,0x29) //Timing value T3 for the SPI clock
	UINT32 resvd                            :16;
	};
}O24A0_LED_SCLK_T3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20A8 RW 0x0000_00CD
	UINT32 sclk_t4                          :16;	//(15:0,RW,0xCD) //Timing value T4 for the SPI clock
	UINT32 resvd                            :16;
	};
}O24A0_LED_SCLK_T4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20AC RW 0x0000_0095
	UINT32 sclk_t5                          :16;	//(15:0,RW,0x95) //Pulse width of BLU vsync
	UINT32 resvd                            :16;
	};
}O24A0_LED_SCLK_T5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20B0 RW 0x0000_0000
	UINT32 spi_cmd4                         :16;	//(15:0,RW,0x0) //The 5th SPI Command
	UINT32 spi_cmd5                         :16;	//(31:16,RW,0x0) //The 6th SPI Command
	};
}O24A0_LED_SPI_CMD45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20C0 RW 0x0000_0000
	UINT32 blk_sp0                          :13;	//(12:0,RW,0x00) //start point of BV segment 0
	UINT32 resvd                            :19;
	};
}O24A0_LED_BLK_SP0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20C4 RW 0x0000_0000
	UINT32 blk_sp1                          :13;	//(12:0,RW,0x00) //start point of BV segment 1
	UINT32 resvd                            :19;
	};
}O24A0_LED_BLK_SP1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20C8 RW 0x0000_0000
	UINT32 blk_sp2                          :13;	//(12:0,RW,0x00) //start point of BV segment 2
	UINT32 resvd                            :19;
	};
}O24A0_LED_BLK_SP2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20CC RW 0x0000_0000
	UINT32 blk_sp3                          :13;	//(12:0,RW,0x00) //start point of BV segment 3
	UINT32 resvd                            :19;
	};
}O24A0_LED_BLK_SP3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20D0 RW 0x0000_0000
	UINT32 bnh_seg0                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 0
	UINT32 resvd                            :25;
	};
}O24A0_LED_BNH_SEG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20D4 RW 0x0000_0000
	UINT32 bnh_seg1                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 1
	UINT32 resvd                            :25;
	};
}O24A0_LED_BNH_SEG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20D8 RW 0x0000_0000
	UINT32 bnh_seg2                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 2
	UINT32 resvd                            :25;
	};
}O24A0_LED_BNH_SEG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20DC RW 0x0000_0000
	UINT32 bnh_seg3                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 3
	UINT32 resvd                            :25;
	};
}O24A0_LED_BNH_SEG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20E0 RW 0x0000_0000
	UINT32 bnv_seg0                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 0
	UINT32 resvd                            :26;
	};
}O24A0_LED_BNV_SEG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20E4 RW 0x0000_0000
	UINT32 bnv_seg1                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 1
	UINT32 resvd                            :26;
	};
}O24A0_LED_BNV_SEG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20E8 RW 0x0000_0000
	UINT32 bnv_seg2                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 2
	UINT32 resvd                            :26;
	};
}O24A0_LED_BNV_SEG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E20EC RW 0x0000_0000
	UINT32 bnv_seg3                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 3
	UINT32 resvd                            :26;
	};
}O24A0_LED_BNV_SEG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2100 RW 0x0000_03FF
	UINT32 spi_pwm_value                    :10;	//(9:0,RW,0x3FF) //PWM value
	UINT32 resvd                            :22;
	};
}O24A0_LED_PWM_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2104 RW 0x0000_0000
	UINT32 blu_maxvalen                     :1;	//(0,RW,0x00) //"0" : disable	"1" : enable
	UINT32 resvd                            :31;
	};
}O24A0_LED_BLU_MAXVAL_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2108 RW 0x0000_0000
	UINT32 spi_alef2_en                     :1;	//(0,RW,0x00) //enable spi non uniform block L/D
	UINT32 resvd                            :31;
	};
}O24A0_LED_SPI_ALEF2_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E210C RW 0x0000_0000
	UINT32 spi_alef2_clr                    :1;	//(0,RW,0x00) //clear
	UINT32 resvd                            :31;
	};
}O24A0_LED_SPI_ALEF2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2110 WO 0x0000_0000
	UINT32 spi0_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi0 read position
	UINT32 resvd                            :21;
	};
}O24A0_LED_SPI0_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2114 RO/WO 0x0000_0000
	UINT32 rd_spi0_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi0 read position
	UINT32 resvd                            :20;
	UINT32 spi0_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_SPI0_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2118 WO 0x0000_0000
	UINT32 spi1_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi1 read position
	UINT32 resvd                            :21;
	};
}O24A0_LED_SPI1_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E211C RO/WO 0x0000_0000
	UINT32 rd_spi1_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi1 read position
	UINT32 resvd                            :20;
	UINT32 spi1_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_SPI1_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2120 WO 0x0000_0000
	UINT32 spi2_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi2 read position
	UINT32 resvd                            :21;
	};
}O24A0_LED_SPI2_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2124 RO/WO 0x0000_0000
	UINT32 rd_spi2_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi2 read position
	UINT32 resvd                            :20;
	UINT32 spi2_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_SPI2_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2128 WO 0x0000_0000
	UINT32 spi3_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi3 read position
	UINT32 resvd                            :21;
	};
}O24A0_LED_SPI3_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E212C RO/WO 0x0000_0000
	UINT32 rd_spi3_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi3 read position
	UINT32 resvd                            :20;
	UINT32 spi3_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}O24A0_LED_SPI3_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2140 RW 0x0000_0000
	UINT32 line_intr_en                     :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_en                       :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_en                       :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_en                       :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_en          :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_en               :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_in_en                        :26;	//(31:6,RW,0x0000_0000) //external interrupt enable
	};
}O24A0_LED_EXT_INT_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2144 RO/RW 0x0000_0000
	UINT32 line_intr_stat                   :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_stat                     :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_stat                     :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_stat                     :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_stat        :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_stat             :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_status                   :26;	//(31:6,RO,0x0000_0000) //external interrupt status
	};
}O24A0_LED_EXT_INT_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2148 RO/RW 0x0000_0000
	UINT32 line_intr_stat                   :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_stat                     :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_stat                     :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_stat                     :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_stat        :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_stat             :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_raw_status               :26;	//(31:6,RO,0x0000_0000) //external interrupt raw status
	};
}O24A0_LED_EXT_INT_RAW_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E214C WO/RW 0x0000_0000
	UINT32 line_intr_clr                    :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_clr                      :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_clr                      :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_clr                      :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_clr         :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_clr              :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_clr                      :26;	//(31:6,WO,0x0000_0000) //external interrupt clear
	};
}O24A0_LED_EXT_INT_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2150 RW 0x0000_0000
	UINT32 int_line_num                     :12;	//(11:0,RW,0x00) //
	UINT32 resvd                            :20;
	};
}O24A0_LED_EXT_INT_LINE_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2220 RW 0x0000_0000
	UINT32 use_same_vs                      :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}O24A0_LED_VS_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2240 RW 0x0000_0000
	UINT32 bfi_manual_toggle                :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 bfi_en                           :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 abi_en                           :1;	//(8,RW,0x0) //
	UINT32 resvd2                           :23;
	};
}O24A0_LED_ABI_BFI0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2244 RW 0x0000_0000
	UINT32 reg_abi_gain_3                   :7;	//(6:0,RW,0x0) //4th frame gain (64=1.0)
	UINT32 resvd0                           :1;
	UINT32 reg_abi_gain_2                   :7;	//(14:8,RW,0x0) //3nd frame gain (64=1.0)
	UINT32 resvd1                           :1;
	UINT32 reg_abi_gain_1                   :7;	//(22:16,RW,0x0) //2st frame gain (64=1.0)
	UINT32 resvd2                           :1;
	UINT32 reg_abi_gain_0                   :7;	//(30:24,RW,0x0) //1st frame gain (64=1.0)
	UINT32 resvd3                           :1;
	};
}O24A0_LED_ABI_BFI1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2248 RW 0x0000_0000
	UINT32 reg_abi_gain_7                   :7;	//(6:0,RW,0x0) //8th frame gain (64=1.0)
	UINT32 resvd0                           :1;
	UINT32 reg_abi_gain_6                   :7;	//(14:8,RW,0x0) //7th frame gain (64=1.0)
	UINT32 resvd1                           :1;
	UINT32 reg_abi_gain_5                   :7;	//(22:16,RW,0x0) //6th frame gain (64=1.0)
	UINT32 resvd2                           :1;
	UINT32 reg_abi_gain_4                   :7;	//(30:24,RW,0x0) //5th frame gain (64=1.0)
	UINT32 resvd3                           :1;
	};
}O24A0_LED_ABI_BFI2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E224C RW 0x0000_0000
	UINT32 bfi_mode_7                       :3;	//(2:0,RW,0x0) //4th frame gain (64=1.0)
	UINT32 resvd0                           :1;
	UINT32 bfi_mode_6                       :3;	//(6:4,RW,0x0) //3nd frame gain (64=1.0)
	UINT32 resvd1                           :1;
	UINT32 bfi_mode_5                       :3;	//(10:8,RW,0x0) //2st frame gain (64=1.0)
	UINT32 resvd2                           :1;
	UINT32 bfi_mode_4                       :3;	//(14:12,RW,0x0) //1st frame gain (64=1.0)
	UINT32 resvd3                           :1;
	UINT32 bfi_mode_3                       :3;	//(18:16,RW,0x0) //4th frame gain (64=1.0)
	UINT32 resvd4                           :1;
	UINT32 bfi_mode_2                       :3;	//(22:20,RW,0x0) //3nd frame gain (64=1.0)
	UINT32 resvd5                           :1;
	UINT32 bfi_mode_1                       :3;	//(26:24,RW,0x0) //2st frame gain (64=1.0)
	UINT32 resvd6                           :1;
	UINT32 bfi_mode_0                       :3;	//(30:28,RW,0x0) //1st frame gain (64=1.0)
	UINT32 resvd7                           :1;
	};
}O24A0_LED_ABI_BFI3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2280 RW 0x0001_0140
	UINT32 reg_10bto12b_en                  :1;	//(0,RW,0x0) //spi_master 10bit to 12 bit enable	1:12bit	0:10bit
	UINT32 resvd0                           :3;
	UINT32 reg_12b_filt_en                  :1;	//(4,RW,0x0) //
	UINT32 reg_12b_filt_bdn_off             :1;	//(5,RW,0x0) //
	UINT32 reg_12b_filt_except_en           :1;	//(6,RW,0x1) //
	UINT32 resvd1                           :1;
	UINT32 reg_10b_12bto16b_en              :1;	//(8,RW,0x1) //spi_master 10bit or 12 bit to 16 bit enable	1:16bit	0:10bit or 12 bit
	UINT32 resvd2                           :3;
	UINT32 reg_mcu_if_10bto12b_en           :1;	//(12,RW,0x0) //mcu_if 10bit to 12bit enable	1:12bit 	0:10 bit
	UINT32 resvd3                           :3;
	UINT32 reg_mcu_if_10b_12bto16b_en       :1;	//(16,RW,0x1) //mcu_if 10bit or 12bit to 16bit enable	1: 16bit 	0:10 bit or 12 bit
	UINT32 resvd4                           :15;
	};
}O24A0_LED_12BIT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2284 RW 0x0000_0000
	UINT32 reg_12b_wgt_p1_o                 :12;	//(11:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_12b_wgt_p2_o                 :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}O24A0_LED_12BIT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2288 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_12b_wgt_c_o                  :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}O24A0_LED_12BIT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E228C RW 0x0000_0004
	UINT32 reg_16b_alpha_x1_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_x0_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2290 RW 0x0008_000c
	UINT32 reg_16b_alpha_x3_o               :16;	//(15:0,RW,0xc) //
	UINT32 reg_16b_alpha_x2_o               :16;	//(31:16,RW,0x8) //
	};
}O24A0_LED_12BIT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2294 RW 0x0000_000c
	UINT32 reg_16b_alpha_x5_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_x4_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2298 RW 0x0048_008c
	UINT32 reg_16b_alpha_x7_o               :16;	//(15:0,RW,0x8c) //
	UINT32 reg_16b_alpha_x6_o               :16;	//(31:16,RW,0x48) //
	};
}O24A0_LED_12BIT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E229C RW 0x0000_0444
	UINT32 reg_16b_alpha_x9_o               :16;	//(15:0,RW,0x444) //
	UINT32 reg_16b_alpha_x8_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22A0 RW 0x0888_0ccc
	UINT32 reg_16b_alpha_x11_o              :16;	//(15:0,RW,0xccc) //
	UINT32 reg_16b_alpha_x10_o              :16;	//(31:16,RW,0x888) //
	};
}O24A0_LED_12BIT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22A4 RW 0x0000_4444
	UINT32 reg_16b_alpha_x13_o              :16;	//(15:0,RW,0x4444) //
	UINT32 reg_16b_alpha_x12_o              :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22A8 RW 0x8888_cccc
	UINT32 reg_16b_alpha_x15_o              :16;	//(15:0,RW,0xcccc) //
	UINT32 reg_16b_alpha_x14_o              :16;	//(31:16,RW,0x8888) //
	};
}O24A0_LED_12BIT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22AC RW 0x0000_0004
	UINT32 reg_16b_alpha_y1_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_y0_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22B0 RW 0x0008_000c
	UINT32 reg_16b_alpha_y3_o               :16;	//(15:0,RW,0xc) //
	UINT32 reg_16b_alpha_y2_o               :16;	//(31:16,RW,0x8) //
	};
}O24A0_LED_12BIT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22B4 RW 0x0000_000c
	UINT32 reg_16b_alpha_y5_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_y4_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22B8 RW 0x0048_008c
	UINT32 reg_16b_alpha_y7_o               :16;	//(15:0,RW,0x8c) //
	UINT32 reg_16b_alpha_y6_o               :16;	//(31:16,RW,0x48) //
	};
}O24A0_LED_12BIT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22BC RW 0x0000_0444
	UINT32 reg_16b_alpha_y9_o               :16;	//(15:0,RW,0x444) //
	UINT32 reg_16b_alpha_y8_o               :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22C0 RW 0x0888_0ccc
	UINT32 reg_16b_alpha_y11_o              :16;	//(15:0,RW,0xccc) //
	UINT32 reg_16b_alpha_y10_o              :16;	//(31:16,RW,0x888) //
	};
}O24A0_LED_12BIT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22C4 RW 0x0000_4444
	UINT32 reg_16b_alpha_y13_o              :16;	//(15:0,RW,0x4444) //
	UINT32 reg_16b_alpha_y12_o              :16;	//(31:16,RW,0x0) //
	};
}O24A0_LED_12BIT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22C8 RW 0x8888_cccc
	UINT32 reg_16b_alpha_y15_o              :16;	//(15:0,RW,0xcccc) //
	UINT32 reg_16b_alpha_y14_o              :16;	//(31:16,RW,0x8888) //
	};
}O24A0_LED_12BIT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22CC RO 0x0000_0000
	UINT32 reg_wpage_i                      :1;	//(0,RO,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_rpage_0_i                    :1;	//(4,RO,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_rpage_1_i                    :1;	//(8,RO,0x0) //
	UINT32 resvd2                           :3;
	UINT32 reg_rpage_2_i                    :1;	//(12,RO,0x0) //
	UINT32 resvd3                           :3;
	UINT32 reg_rpage_3_i                    :1;	//(16,RO,0x0) //
	UINT32 resvd4                           :15;
	};
}O24A0_LED_BLU_IF_DB_MEM_PAGE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22D0 RW 0x0000_0000
	UINT32 reg_direction                    :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_shift                        :5;	//(20:16,RW,0x00) //
	UINT32 resvd1                           :11;
	};
}O24A0_LED_BLU_IF_SHIFT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22D4 RW 0x0000_0000
	UINT32 reg_blu_i2c_rd_ai_addr_clr       :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}O24A0_LED_I2C_RD_AI_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22D8 RW 0x0000_0000
	UINT32 reg_blu_i2c_rd_ai_rdata          :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_blu_i2c_rd_ai_raddr          :14;	//(29:16,RO,0x0) //
	UINT32 resvd1                           :2;
	};
}O24A0_LED_I2C_RD_AI_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E22DC RW 0x0000_0000
	UINT32 reg_blu_i2c_rd_mode              :1;	//(0,RW,0x0) //1:auto
	UINT32 resvd                            :31;
	};
}O24A0_LED_I2C_RD_MODE_SEL_T;

typedef struct {
	O24A0_LED_BV_GEN_HV_SIZE_T                       ad_bv_gen_hv_size;	//0xCC8E0000
	O24A0_LED_BV_GEN_BLK_NUM_HV_T                 ad_bv_gen_blk_num_hv;	//0xCC8E0004
	O24A0_LED_HV_RESOLUTION_T                         ad_hv_resolution;	//0xCC8E0008
	O24A0_LED_SYNC_POL_T                                   ad_sync_pol;	//0xCC8E000C
	O24A0_LED_VIN_CONFIG_T                               ad_vin_config;	//0xCC8E0010
	O24A0_LED_LED_DLY_T                                     ad_led_dly;	//0xCC8E0014
	O24A0_LED_MONITOR_SEL_T                             ad_monitor_sel;	//0xCC8E0018
	O24A0_LED_DPATH_ORDER_T                             ad_dpath_order;	//0xCC8E001C
	UINT32                                                    reserved0;	//0xCC8E0020
	O24A0_LED_SYNC_SEL_T                                   ad_sync_sel;	//0xCC8E0024
	O24A0_LED_BV_CLG_SEL_T                               ad_bv_clg_sel;	//0xCC8E0028
	UINT32                                                    reserved1;	//0xCC8E002C
	UINT32                                                    reserved2;	//0xCC8E0030
	UINT32                                                    reserved3;	//0xCC8E0034
	UINT32                                                    reserved4;	//0xCC8E0038
	UINT32                                                    reserved5;	//0xCC8E003C
	O24A0_LED_DBG_CTRL_T                                   ad_dbg_ctrl;	//0xCC8E0040
	O24A0_LED_LUM_T                                             ad_lum;	//0xCC8E0044
	O24A0_LED_BLU_I2C_WDATA_T                         ad_blu_i2c_wdata;	//0xCC8E0048
	O24A0_LED_SB_SEL_T                                       ad_sb_sel;	//0xCC8E004C
	O24A0_LED_SB_I2C_T                                       ad_sb_i2c;	//0xCC8E0050
	O24A0_LED_BV_READ_T                                     ad_bv_read;	//0xCC8E0054
	O24A0_LED_BV_WRITE_T                                   ad_bv_write;	//0xCC8E0058
	O24A0_LED_BV_RW_STATUS_T                           ad_bv_rw_status;	//0xCC8E005C
	UINT32                                                    reserved6;	//0xCC8E0060
	O24A0_LED_LED_DETOUR_T                               ad_led_detour;	//0xCC8E0064
	UINT32                                                    reserved7;	//0xCC8E0068
	UINT32                                                    reserved8;	//0xCC8E006C
	UINT32                                                    reserved9;	//0xCC8E0070
	UINT32                                                   reserved10;	//0xCC8E0074
	UINT32                                                   reserved11;	//0xCC8E0078
	UINT32                                                   reserved12;	//0xCC8E007C
	O24A0_LED_PAT_ON_T                                       ad_pat_on;	//0xCC8E0080
	O24A0_LED_PAT_VAL_T                                     ad_pat_val;	//0xCC8E0084
	O24A0_LED_PAT_H_MIN_MAX_T                         ad_pat_h_min_max;	//0xCC8E0088
	O24A0_LED_PAT_V_MIN_MAX_T                         ad_pat_v_min_max;	//0xCC8E008C
	O24A0_LED_PAT_HV_PPF_T                               ad_pat_hv_ppf;	//0xCC8E0090
	O24A0_LED_PAT_VAL_R_T                                 ad_pat_val_r;	//0xCC8E0094
	O24A0_LED_PAT_H_MIN_MAX_R_T                     ad_pat_h_min_max_r;	//0xCC8E0098
	O24A0_LED_PAT_V_MIN_MAX_R_T                     ad_pat_v_min_max_r;	//0xCC8E009C
	O24A0_LED_PAT_BGVAL_T                                 ad_pat_bgval;	//0xCC8E00A0
	UINT32                                                   reserved13;	//0xCC8E00A4
	UINT32                                                   reserved14;	//0xCC8E00A8
	UINT32                                                   reserved15;	//0xCC8E00AC
	UINT32                                                   reserved16;	//0xCC8E00B0
	UINT32                                                   reserved17;	//0xCC8E00B4
	UINT32                                                   reserved18;	//0xCC8E00B8
	UINT32                                                   reserved19;	//0xCC8E00BC
	O24A0_LED_IWB_R_GAIN_T                               ad_iwb_r_gain;	//0xCC8E00C0
	O24A0_LED_IWB_G_GAIN_T                               ad_iwb_g_gain;	//0xCC8E00C4
	O24A0_LED_IWB_B_GAIN_T                               ad_iwb_b_gain;	//0xCC8E00C8
	UINT32                                                   reserved20;	//0xCC8E00CC
	UINT32                                                   reserved21;	//0xCC8E00D0
	UINT32                                                   reserved22;	//0xCC8E00D4
	UINT32                                                   reserved23;	//0xCC8E00D8
	UINT32                                                   reserved24;	//0xCC8E00DC
	UINT32                                                   reserved25;	//0xCC8E00E0
	O24A0_LED_CRC1_RD_T                                     ad_crc1_rd;	//0xCC8E00E4
	O24A0_LED_HDMI_CTRL_T                                 ad_hdmi_ctrl;	//0xCC8E00E8
	O24A0_LED_FBC_CTRL_T                                   ad_fbc_ctrl;	//0xCC8E00EC
	O24A0_LED_FBC_DPCM_REST_STEP_T               ad_fbc_dpcm_rest_step;	//0xCC8E00F0
	O24A0_LED_YC422_CTRL_T                               ad_yc422_ctrl;	//0xCC8E00F4
	O24A0_LED_CRC_INFO_T                                   ad_crc_info;	//0xCC8E00F8
	O24A0_LED_CRC_RD_T                                       ad_crc_rd;	//0xCC8E00FC
	O24A0_LED_HIST_MODE_T                                 ad_hist_mode;	//0xCC8E0100
	O24A0_LED_HIST_RADDR_T                               ad_hist_raddr;	//0xCC8E0104
	O24A0_LED_PWM_SC_MODE_T                             ad_pwm_sc_mode;	//0xCC8E0108
	O24A0_LED_PWM_MAX_MODE_T                           ad_pwm_max_mode;	//0xCC8E010C
	O24A0_LED_PWM_IIR_MODE_T                           ad_pwm_iir_mode;	//0xCC8E0110
	O24A0_LED_PWM_MODE_T                                   ad_pwm_mode;	//0xCC8E0114
	O24A0_LED_PWM_PEL_MODE_T                           ad_pwm_pel_mode;	//0xCC8E0118
	O24A0_LED_PWM_EXT_SC_T                               ad_pwm_ext_sc;	//0xCC8E011C
	O24A0_LED_PWM_SC_HIST_TH_T                       ad_pwm_sc_hist_th;	//0xCC8E0120
	O24A0_LED_PWM_SC_APL_TH_T                         ad_pwm_sc_apl_th;	//0xCC8E0124
	O24A0_LED_PWM_SC_DETECT_RD_T                   ad_pwm_sc_detect_rd;	//0xCC8E0128
	O24A0_LED_PWM_MAX_CDF_T                             ad_pwm_max_cdf;	//0xCC8E012C
	O24A0_LED_PWM_EXT_MAX_T                             ad_pwm_ext_max;	//0xCC8E0130
	O24A0_LED_PWM_FR_MAX_WEI_T                       ad_pwm_fr_max_wei;	//0xCC8E0134
	O24A0_LED_PWM_X1_X2_T                                 ad_pwm_x1_x2;	//0xCC8E0138
	O24A0_LED_PWM_X3_X4_T                                 ad_pwm_x3_x4;	//0xCC8E013C
	O24A0_LED_PWM_Y0_Y1_T                                 ad_pwm_y0_y1;	//0xCC8E0140
	O24A0_LED_PWM_Y2_Y3_T                                 ad_pwm_y2_y3;	//0xCC8E0144
	O24A0_LED_PWM_Y4_Y5_T                                 ad_pwm_y4_y5;	//0xCC8E0148
	O24A0_LED_PWM_BV_FR_MAX_RD_T                   ad_pwm_bv_fr_max_rd;	//0xCC8E014C
	O24A0_LED_PWM_MAX_RD_T                               ad_pwm_max_rd;	//0xCC8E0150
	O24A0_LED_PWM_VALUE_RD_T                           ad_pwm_value_rd;	//0xCC8E0154
	O24A0_LED_PWM_IIR_WEI_T                             ad_pwm_iir_wei;	//0xCC8E0158
	O24A0_LED_PWM_SC_IIR_STEP_C_T                 ad_pwm_sc_iir_step_c;	//0xCC8E015C
	O24A0_LED_PWM_SC_IIR_STEP_P_T                 ad_pwm_sc_iir_step_p;	//0xCC8E0160
	O24A0_LED_PWM_ADJ_IIR_WEI_RD_T               ad_pwm_adj_iir_wei_rd;	//0xCC8E0164
	O24A0_LED_PWM_MAF_IIR_STEP_C_T               ad_pwm_maf_iir_step_c;	//0xCC8E0168
	O24A0_LED_PWM_MAF_IIR_STEP_P_T               ad_pwm_maf_iir_step_p;	//0xCC8E016C
	O24A0_LED_PWM_MAF_IIR_MAG_RD_T               ad_pwm_maf_iir_mag_rd;	//0xCC8E0170
	O24A0_LED_PWM_EXT_VAL_PEL_T                     ad_pwm_ext_val_pel;	//0xCC8E0174
	O24A0_LED_PWM_BL_TDIF_TH_T                       ad_pwm_bl_tdif_th;	//0xCC8E0178
	UINT32                                                   reserved26;	//0xCC8E017C
	O24A0_LED_MAX_OPT_T                                     ad_max_opt;	//0xCC8E0180
	O24A0_LED_BLK_MAX_MODE_T                           ad_blk_max_mode;	//0xCC8E0184
	O24A0_LED_MAX_OPT_MODE_T                           ad_max_opt_mode;	//0xCC8E0188
	O24A0_LED_MAX_OPT0_1_T                               ad_max_opt0_1;	//0xCC8E018C
	O24A0_LED_LEVEL_TH_T                                   ad_level_th;	//0xCC8E0190
	O24A0_LED_NUMBER_TH_T                                 ad_number_th;	//0xCC8E0194
	O24A0_LED_APL_T                                             ad_apl;	//0xCC8E0198
	O24A0_LED_BV_GEN_X1_X2_T                           ad_bv_gen_x1_x2;	//0xCC8E019C
	O24A0_LED_BV_GEN_X3_X4_T                           ad_bv_gen_x3_x4;	//0xCC8E01A0
	O24A0_LED_BV_GEN_Y0_Y1_T                           ad_bv_gen_y0_y1;	//0xCC8E01A4
	O24A0_LED_BV_GEN_Y2_Y3_T                           ad_bv_gen_y2_y3;	//0xCC8E01A8
	O24A0_LED_BV_GEN_Y4_Y5_T                           ad_bv_gen_y4_y5;	//0xCC8E01AC
	O24A0_LED_BV_GEN_BV_MAX_T                         ad_bv_gen_bv_max;	//0xCC8E01B0
	O24A0_LED_BV_MIN_MAX_T                               ad_bv_min_max;	//0xCC8E01B4
	O24A0_LED_BV_LUT_MIN_MAX_T                       ad_bv_lut_min_max;	//0xCC8E01B8
	O24A0_LED_BV_FINAL_AVG_MIN_MAX_T           ad_bv_final_avg_min_max;	//0xCC8E01BC
	O24A0_LED_BV_RCTRL_MODE_T                         ad_bv_rctrl_mode;	//0xCC8E01C0
	O24A0_LED_PIC_ATTR_T                                   ad_pic_attr;	//0xCC8E01C4
	O24A0_LED_LR_SYNC_SEL_T                             ad_lr_sync_sel;	//0xCC8E01C8
	UINT32                                                   reserved27;	//0xCC8E01CC
	UINT32                                                   reserved28;	//0xCC8E01D0
	UINT32                                                   reserved29;	//0xCC8E01D4
	UINT32                                                   reserved30;	//0xCC8E01D8
	UINT32                                                   reserved31;	//0xCC8E01DC
	UINT32                                                   reserved32;	//0xCC8E01E0
	UINT32                                                   reserved33;	//0xCC8E01E4
	UINT32                                                   reserved34;	//0xCC8E01E8
	UINT32                                                   reserved35;	//0xCC8E01EC
	UINT32                                                   reserved36;	//0xCC8E01F0
	UINT32                                                   reserved37;	//0xCC8E01F4
	UINT32                                                   reserved38;	//0xCC8E01F8
	UINT32                                                   reserved39;	//0xCC8E01FC
	UINT32                                                   reserved40;	//0xCC8E0200
	UINT32                                                   reserved41;	//0xCC8E0204
	UINT32                                                   reserved42;	//0xCC8E0208
	UINT32                                                   reserved43;	//0xCC8E020C
	UINT32                                                   reserved44;	//0xCC8E0210
	UINT32                                                   reserved45;	//0xCC8E0214
	UINT32                                                   reserved46;	//0xCC8E0218
	UINT32                                                   reserved47;	//0xCC8E021C
	UINT32                                                   reserved48;	//0xCC8E0220
	UINT32                                                   reserved49;	//0xCC8E0224
	UINT32                                                   reserved50;	//0xCC8E0228
	UINT32                                                   reserved51;	//0xCC8E022C
	UINT32                                                   reserved52;	//0xCC8E0230
	UINT32                                                   reserved53;	//0xCC8E0234
	UINT32                                                   reserved54;	//0xCC8E0238
	UINT32                                                   reserved55;	//0xCC8E023C
	O24A0_LED_LUT_MODE_T                                   ad_lut_mode;	//0xCC8E0240
	O24A0_LED_EX_ABV_T                                       ad_ex_abv;	//0xCC8E0244
	UINT32                                                   reserved56;	//0xCC8E0248
	O24A0_LED_DC_LUT_RADDR_T                           ad_dc_lut_raddr;	//0xCC8E024C
	O24A0_LED_DC_LUT_RDATA_T                           ad_dc_lut_rdata;	//0xCC8E0250
	UINT32                                                   reserved57;	//0xCC8E0254
	O24A0_LED_LUT_AVG_SEL_T                             ad_lut_avg_sel;	//0xCC8E0258
	O24A0_LED_LUT_OFFSET_EN_T                         ad_lut_offset_en;	//0xCC8E025C
	O24A0_LED_LUT_OFFSET_X1_X2_T                   ad_lut_offset_x1_x2;	//0xCC8E0260
	O24A0_LED_LUT_OFFSET_X3_X4_T                   ad_lut_offset_x3_x4;	//0xCC8E0264
	O24A0_LED_LUT_OFFSET_Y0_Y1_T                   ad_lut_offset_y0_y1;	//0xCC8E0268
	O24A0_LED_LUT_OFFSET_Y2_Y3_T                   ad_lut_offset_y2_y3;	//0xCC8E026C
	O24A0_LED_LUT_OFFSET_Y4_Y5_T                   ad_lut_offset_y4_y5;	//0xCC8E0270
	O24A0_LED_LD_SMOOTH_OFF_T                         ad_ld_smooth_off;	//0xCC8E0274
	O24A0_LED_LD_SMOOTH_OFF_STEP_T               ad_ld_smooth_off_step;	//0xCC8E0278
	O24A0_LED_LD_BV_EXT_MAX_T                         ad_ld_bv_ext_max;	//0xCC8E027C
	O24A0_LED_UMASK_UM_EN_T                             ad_umask_um_en;	//0xCC8E0280
	O24A0_LED_UMASK_5X5_T                                 ad_umask_5x5;	//0xCC8E0284
	O24A0_LED_UMASK_COARING_T                         ad_umask_coaring;	//0xCC8E0288
	O24A0_LED_UMASK_GAIN_T                               ad_umask_gain;	//0xCC8E028C
	O24A0_LED_UMASK_WR_COEFF_T                       ad_umask_wr_coeff;	//0xCC8E0290
	O24A0_LED_UMASK_RD_COEFF_T                       ad_umask_rd_coeff;	//0xCC8E0294
	UINT32                                                   reserved58;	//0xCC8E0298
	UINT32                                                   reserved59;	//0xCC8E029C
	UINT32                                                   reserved60;	//0xCC8E02A0
	UINT32                                                   reserved61;	//0xCC8E02A4
	UINT32                                                   reserved62;	//0xCC8E02A8
	UINT32                                                   reserved63;	//0xCC8E02AC
	UINT32                                                   reserved64;	//0xCC8E02B0
	UINT32                                                   reserved65;	//0xCC8E02B4
	UINT32                                                   reserved66;	//0xCC8E02B8
	UINT32                                                   reserved67;	//0xCC8E02BC
	O24A0_LED_T_SF_T                                           ad_t_sf;	//0xCC8E02C0
	O24A0_LED_KMODE_T                                         ad_kmode;	//0xCC8E02C4
	O24A0_LED_HVKMASK_T                                     ad_hvkmask;	//0xCC8E02C8
	O24A0_LED_BLEND_ALPHA_T                             ad_blend_alpha;	//0xCC8E02CC
	UINT32                                                   reserved68;	//0xCC8E02D0
	UINT32                                                   reserved69;	//0xCC8E02D4
	UINT32                                                   reserved70;	//0xCC8E02D8
	UINT32                                                   reserved71;	//0xCC8E02DC
	UINT32                                                   reserved72;	//0xCC8E02E0
	UINT32                                                   reserved73;	//0xCC8E02E4
	UINT32                                                   reserved74;	//0xCC8E02E8
	UINT32                                                   reserved75;	//0xCC8E02EC
	UINT32                                                   reserved76;	//0xCC8E02F0
	UINT32                                                   reserved77;	//0xCC8E02F4
	UINT32                                                   reserved78;	//0xCC8E02F8
	UINT32                                                   reserved79;	//0xCC8E02FC
	O24A0_LED_TF_OPMODE_T                                 ad_tf_opmode;	//0xCC8E0300
	O24A0_LED_A_PARA_T                                       ad_a_para;	//0xCC8E0304
	O24A0_LED_SC_ADJ_EN_T                                 ad_sc_adj_en;	//0xCC8E0308
	O24A0_LED_MD_ADJ_EN_T                                 ad_md_adj_en;	//0xCC8E030C
	O24A0_LED_MD_X1_T                                         ad_md_x1;	//0xCC8E0310
	O24A0_LED_MD_X2_T                                         ad_md_x2;	//0xCC8E0314
	O24A0_LED_MD_X3_T                                         ad_md_x3;	//0xCC8E0318
	O24A0_LED_MD_X4_T                                         ad_md_x4;	//0xCC8E031C
	O24A0_LED_MD_Y0_T                                         ad_md_y0;	//0xCC8E0320
	O24A0_LED_MD_Y1_T                                         ad_md_y1;	//0xCC8E0324
	O24A0_LED_MD_Y2_T                                         ad_md_y2;	//0xCC8E0328
	O24A0_LED_MD_Y3_T                                         ad_md_y3;	//0xCC8E032C
	O24A0_LED_MD_Y4_T                                         ad_md_y4;	//0xCC8E0330
	O24A0_LED_MD_Y5_T                                         ad_md_y5;	//0xCC8E0334
	O24A0_LED_BV_FINAL_AVG_IIR_T                   ad_bv_final_avg_iir;	//0xCC8E0338
	O24A0_LED_BV_MID_AVG_IIR_T                       ad_bv_mid_avg_iir;	//0xCC8E033C
	O24A0_LED_LED_MODE_T                                   ad_led_mode;	//0xCC8E0340
	O24A0_LED_LRES_BNH_BNV_T                           ad_lres_bnh_bnv;	//0xCC8E0344
	O24A0_LED_LRES_BSH_BSV_T                           ad_lres_bsh_bsv;	//0xCC8E0348
	O24A0_LED_SBI_BNH_BNV_T                             ad_sbi_bnh_bnv;	//0xCC8E034C
	O24A0_LED_SBI_BSH_BSV_T                             ad_sbi_bsh_bsv;	//0xCC8E0350
	O24A0_LED_TAB1_RD_SEL_T                             ad_tab1_rd_sel;	//0xCC8E0354
	O24A0_LED_TAB1_RDATA_T                               ad_tab1_rdata;	//0xCC8E0358
	O24A0_LED_TAB5_RD_SEL_T                             ad_tab5_rd_sel;	//0xCC8E035C
	O24A0_LED_TAB5_RDATA_T                               ad_tab5_rdata;	//0xCC8E0360
	O24A0_LED_HFC_RD_SEL_T                               ad_hfc_rd_sel;	//0xCC8E0364
	O24A0_LED_HFC_RDATA_T                                 ad_hfc_rdata;	//0xCC8E0368
	O24A0_LED_VFC_RD_SEL_T                               ad_vfc_rd_sel;	//0xCC8E036C
	O24A0_LED_VFC_RDATA_T                                 ad_vfc_rdata;	//0xCC8E0370
	O24A0_LED_POLARIS_MODE_T                           ad_polaris_mode;	//0xCC8E0374
	UINT32                                                   reserved80;	//0xCC8E0378
	UINT32                                                   reserved81;	//0xCC8E037C
	O24A0_LED_COMP_EN_T                                     ad_comp_en;	//0xCC8E0380
	O24A0_LED_CONT_GAIN_T                                 ad_cont_gain;	//0xCC8E0384
	O24A0_LED_COMP_IN_T                                     ad_comp_in;	//0xCC8E0388
	O24A0_LED_PC_RADDR_T                                   ad_pc_raddr;	//0xCC8E038C
	O24A0_LED_PC_RDATA_T                                   ad_pc_rdata;	//0xCC8E0390
	UINT32                                                   reserved82;	//0xCC8E0394
	UINT32                                                   reserved83;	//0xCC8E0398
	UINT32                                                   reserved84;	//0xCC8E039C
	UINT32                                                   reserved85;	//0xCC8E03A0
	UINT32                                                   reserved86;	//0xCC8E03A4
	UINT32                                                   reserved87;	//0xCC8E03A8
	UINT32                                                   reserved88;	//0xCC8E03AC
	UINT32                                                   reserved89;	//0xCC8E03B0
	UINT32                                                   reserved90;	//0xCC8E03B4
	UINT32                                                   reserved91;	//0xCC8E03B8
	UINT32                                                   reserved92;	//0xCC8E03BC
	UINT32                                                   reserved93;	//0xCC8E03C0
	UINT32                                                   reserved94;	//0xCC8E03C4
	UINT32                                                   reserved95;	//0xCC8E03C8
	UINT32                                                   reserved96;	//0xCC8E03CC
	UINT32                                                   reserved97;	//0xCC8E03D0
	UINT32                                                   reserved98;	//0xCC8E03D4
	UINT32                                                   reserved99;	//0xCC8E03D8
	UINT32                                                  reserved100;	//0xCC8E03DC
	UINT32                                                  reserved101;	//0xCC8E03E0
	UINT32                                                  reserved102;	//0xCC8E03E4
	UINT32                                                  reserved103;	//0xCC8E03E8
	UINT32                                                  reserved104;	//0xCC8E03EC
	UINT32                                                  reserved105;	//0xCC8E03F0
	UINT32                                                  reserved106;	//0xCC8E03F4
	UINT32                                                  reserved107;	//0xCC8E03F8
	UINT32                                                  reserved108;	//0xCC8E03FC
	O24A0_LED_GBL_T                                             ad_gbl;	//0xCC8E0400
	UINT32                                                  reserved109;	//0xCC8E0404
	O24A0_LED_BV_DLY_T                                       ad_bv_dly;	//0xCC8E0408
	O24A0_LED_BLU_BV_SEL_T                               ad_blu_bv_sel;	//0xCC8E040C
	UINT32                                                  reserved110;	//0xCC8E0410
	UINT32                                                  reserved111;	//0xCC8E0414
	UINT32                                                  reserved112;	//0xCC8E0418
	UINT32                                                  reserved113;	//0xCC8E041C
	UINT32                                                  reserved114;	//0xCC8E0420
	UINT32                                                  reserved115;	//0xCC8E0424
	UINT32                                                  reserved116;	//0xCC8E0428
	UINT32                                                  reserved117;	//0xCC8E042C
	UINT32                                                  reserved118;	//0xCC8E0430
	UINT32                                                  reserved119;	//0xCC8E0434
	UINT32                                                  reserved120;	//0xCC8E0438
	UINT32                                                  reserved121;	//0xCC8E043C
	O24A0_LED_INSTR_WR_REQ_T                           ad_instr_wr_req;	//0xCC8E0440
	O24A0_LED_INSTR_WDATA_T                             ad_instr_wdata;	//0xCC8E0444
	O24A0_LED_INSTR_RDATA_T                             ad_instr_rdata;	//0xCC8E0448
	O24A0_LED_INSTR_DGB_T                                 ad_instr_dgb;	//0xCC8E044C
	UINT32                                                  reserved122;	//0xCC8E0450
	UINT32                                                  reserved123;	//0xCC8E0454
	UINT32                                                  reserved124;	//0xCC8E0458
	UINT32                                                  reserved125;	//0xCC8E045C
	UINT32                                                  reserved126;	//0xCC8E0460
	UINT32                                                  reserved127;	//0xCC8E0464
	UINT32                                                  reserved128;	//0xCC8E0468
	UINT32                                                  reserved129;	//0xCC8E046C
	UINT32                                                  reserved130;	//0xCC8E0470
	UINT32                                                  reserved131;	//0xCC8E0474
	UINT32                                                  reserved132;	//0xCC8E0478
	UINT32                                                  reserved133;	//0xCC8E047C
	O24A0_LED_BLC_MODE_T                                   ad_blc_mode;	//0xCC8E0480
	O24A0_LED_BSF_C0_T                                       ad_bsf_c0;	//0xCC8E0484
	O24A0_LED_BSF_C1_T                                       ad_bsf_c1;	//0xCC8E0488
	O24A0_LED_BSF_C2_T                                       ad_bsf_c2;	//0xCC8E048C
	O24A0_LED_BSF_RATIO0_T                               ad_bsf_ratio0;	//0xCC8E0490
	O24A0_LED_BSF_RATIO1_T                               ad_bsf_ratio1;	//0xCC8E0494
	O24A0_LED_BSF_RATIO2_T                               ad_bsf_ratio2;	//0xCC8E0498
	O24A0_LED_A0_GN_T                                         ad_a0_gn;	//0xCC8E049C
	O24A0_LED_A1_GN_T                                         ad_a1_gn;	//0xCC8E04A0
	O24A0_LED_A2_GN_T                                         ad_a2_gn;	//0xCC8E04A4
	O24A0_LED_A0_RATIO_T                                   ad_a0_ratio;	//0xCC8E04A8
	O24A0_LED_A1_RATIO_T                                   ad_a1_ratio;	//0xCC8E04AC
	O24A0_LED_DRV_MAX_T                                     ad_drv_max;	//0xCC8E04B0
	O24A0_LED_BLC_EN_T                                       ad_blc_en;	//0xCC8E04B4
	O24A0_LED_BLC_TEMPO_TH_T                           ad_blc_tempo_th;	//0xCC8E04B8
	O24A0_LED_BLC_FRAME_NUM_T                         ad_blc_frame_num;	//0xCC8E04BC
	O24A0_LED_MEM_ADDR_CLR_T                           ad_mem_addr_clr;	//0xCC8E04C0
	O24A0_LED_MEM_DL_SBI_HCOEFF_T                 ad_mem_dl_sbi_hcoeff;	//0xCC8E04C4
	O24A0_LED_MEM_DL_SBI_VCOEFF_T                 ad_mem_dl_sbi_vcoeff;	//0xCC8E04C8
	O24A0_LED_MEM_DL_PIXEL_COMP_A_T             ad_mem_dl_pixel_comp_a;	//0xCC8E04CC
	O24A0_LED_MEM_DL_PIXEL_COMP_B_T             ad_mem_dl_pixel_comp_b;	//0xCC8E04D0
	O24A0_LED_MEM_DL_PIXEL_COMP_C_T             ad_mem_dl_pixel_comp_c;	//0xCC8E04D4
	O24A0_LED_MEM_DL_PIXEL_COMP_D_T             ad_mem_dl_pixel_comp_d;	//0xCC8E04D8
	O24A0_LED_UPPER_DC_LUT_T                           ad_upper_dc_lut;	//0xCC8E04DC
	O24A0_LED_LOWER_DC_LUT_T                           ad_lower_dc_lut;	//0xCC8E04E0
	O24A0_LED_FC_TAB1_T                                     ad_fc_tab1;	//0xCC8E04E4
	O24A0_LED_FC_TAB5_T                                     ad_fc_tab5;	//0xCC8E04E8
	UINT32                                                  reserved134;	//0xCC8E04EC
	UINT32                                                  reserved135;	//0xCC8E04F0
	UINT32                                                  reserved136;	//0xCC8E04F4
	UINT32                                                  reserved137;	//0xCC8E04F8
	UINT32                                                  reserved138;	//0xCC8E04FC
	O24A0_LED_MEAN_IN_SEL_T                             ad_mean_in_sel;	//0xCC8E0500
	O24A0_LED_MEAN_T                                           ad_mean;	//0xCC8E0504
	UINT32                                                  reserved139;	//0xCC8E0508
	UINT32                                                  reserved140;	//0xCC8E050C
	UINT32                                                  reserved141;	//0xCC8E0510
	UINT32                                                  reserved142;	//0xCC8E0514
	UINT32                                                  reserved143;	//0xCC8E0518
	UINT32                                                  reserved144;	//0xCC8E051C
	UINT32                                                  reserved145;	//0xCC8E0520
	UINT32                                                  reserved146;	//0xCC8E0524
	UINT32                                                  reserved147;	//0xCC8E0528
	UINT32                                                  reserved148;	//0xCC8E052C
	UINT32                                                  reserved149;	//0xCC8E0530
	UINT32                                                  reserved150;	//0xCC8E0534
	UINT32                                                  reserved151;	//0xCC8E0538
	UINT32                                                  reserved152;	//0xCC8E053C
	O24A0_LED_RP_HV_POS_T                                 ad_rp_hv_pos;	//0xCC8E0540
	O24A0_LED_RP_MAKE_EN_T                               ad_rp_make_en;	//0xCC8E0544
	O24A0_LED_RP_R_VALUE_T                               ad_rp_r_value;	//0xCC8E0548
	O24A0_LED_RP_G_VALUE_T                               ad_rp_g_value;	//0xCC8E054C
	O24A0_LED_RP_B_VALUE_T                               ad_rp_b_value;	//0xCC8E0550
	UINT32                                                  reserved153;	//0xCC8E0554
	O24A0_LED_ALEF2_MODE_T                               ad_alef2_mode;	//0xCC8E0558
	O24A0_LED_ALEF2_BLOCK_NUM_T                     ad_alef2_block_num;	//0xCC8E055C
	O24A0_LED_ALEF2_ADDR_CLR_T                       ad_alef2_addr_clr;	//0xCC8E0560
	O24A0_LED_ALEF2_CFG_LUT_T                         ad_alef2_cfg_lut;	//0xCC8E0564
	O24A0_LED_ALEF2_CFG_LUT_RD_T                   ad_alef2_cfg_lut_rd;	//0xCC8E0568
	O24A0_LED_ALEF2_GAIN_LUT_T                       ad_alef2_gain_lut;	//0xCC8E056C
	O24A0_LED_ALEF2_GAIN_LUT_RD_T                 ad_alef2_gain_lut_rd;	//0xCC8E0570
	O24A0_LED_ALEF2_MAXOPT_LUT_T                   ad_alef2_maxopt_lut;	//0xCC8E0574
	O24A0_LED_ALEF2_MAXOPT_LUT_RD_T             ad_alef2_maxopt_lut_rd;	//0xCC8E0578
	O24A0_LED_ALEF2_MAXVALUE_EN_T                 ad_alef2_maxvalue_en;	//0xCC8E057C
	O24A0_LED_DISP_BV_EN_T                               ad_disp_bv_en;	//0xCC8E0580
	O24A0_LED_DSIP_BV_ADDR_T                           ad_dsip_bv_addr;	//0xCC8E0584
	UINT32                                                  reserved154;	//0xCC8E0588
	UINT32                                                  reserved155;	//0xCC8E058C
	UINT32                                                  reserved156;	//0xCC8E0590
	UINT32                                                  reserved157;	//0xCC8E0594
	UINT32                                                  reserved158;	//0xCC8E0598
	UINT32                                                  reserved159;	//0xCC8E059C
	UINT32                                                  reserved160;	//0xCC8E05A0
	UINT32                                                  reserved161;	//0xCC8E05A4
	UINT32                                                  reserved162;	//0xCC8E05A8
	UINT32                                                  reserved163;	//0xCC8E05AC
	UINT32                                                  reserved164;	//0xCC8E05B0
	UINT32                                                  reserved165;	//0xCC8E05B4
	UINT32                                                  reserved166;	//0xCC8E05B8
	UINT32                                                  reserved167;	//0xCC8E05BC
	O24A0_LED_DITHER_EN_T                                 ad_dither_en;	//0xCC8E05C0
	O24A0_LED_DITHER_EN_N2_T                           ad_dither_en_n2;	//0xCC8E05C4
	UINT32                                                  reserved168;	//0xCC8E05C8
	O24A0_LED_BPL_SLD_SEL_T                             ad_bpl_sld_sel;	//0xCC8E05CC
	O24A0_LED_BLU_GAIN_EN_T                             ad_blu_gain_en;	//0xCC8E05D0
	O24A0_LED_BLU_GAIN_ADDR_CLR_T                 ad_blu_gain_addr_clr;	//0xCC8E05D4
	O24A0_LED_BLU_GAIN_WD_T                             ad_blu_gain_wd;	//0xCC8E05D8
	O24A0_LED_BLU_GAIN_RD_T                             ad_blu_gain_rd;	//0xCC8E05DC
	O24A0_LED_BLU_BV_ADDR_CLR_T                     ad_blu_bv_addr_clr;	//0xCC8E05E0
	O24A0_LED_BLU_BV_RD_T                                 ad_blu_bv_rd;	//0xCC8E05E4
	O24A0_LED_BLE_GAIN_EN_T                             ad_ble_gain_en;	//0xCC8E05E8
	O24A0_LED_BLE_GAIN_ADDR_CLR_T                 ad_ble_gain_addr_clr;	//0xCC8E05EC
	O24A0_LED_BLE_GAIN_WD_T                             ad_ble_gain_wd;	//0xCC8E05F0
	O24A0_LED_BLE_GAIN_RD_T                             ad_ble_gain_rd;	//0xCC8E05F4
	UINT32                                                  reserved169;	//0xCC8E05F8
	UINT32                                                  reserved170;	//0xCC8E05FC
	O24A0_LED_DPG_EN_T                                       ad_dpg_en;	//0xCC8E0600
	O24A0_LED_DPG_LUT_WR_DONE_T                     ad_dpg_lut_wr_done;	//0xCC8E0604
	O24A0_LED_DPG_LUT_WDATA_T                         ad_dpg_lut_wdata;	//0xCC8E0608
	O24A0_LED_DPG_LUT_RDATA_T                         ad_dpg_lut_rdata;	//0xCC8E060C
	O24A0_LED_BVGAIN_CTRL_00_T                       ad_bvgain_ctrl_00;	//0xCC8E0610
	O24A0_LED_BVGAIN_CTRL_01_T                       ad_bvgain_ctrl_01;	//0xCC8E0614
	O24A0_LED_BVGAIN_CTRL_02_T                       ad_bvgain_ctrl_02;	//0xCC8E0618
	O24A0_LED_BVGAIN_CTRL_03_T                       ad_bvgain_ctrl_03;	//0xCC8E061C
	O24A0_LED_BVGAIN_CTRL_04_T                       ad_bvgain_ctrl_04;	//0xCC8E0620
	O24A0_LED_BVGAIN_CTRL_05_T                       ad_bvgain_ctrl_05;	//0xCC8E0624
	O24A0_LED_BVGAIN_CTRL_06_T                       ad_bvgain_ctrl_06;	//0xCC8E0628
	O24A0_LED_BVGAIN_CTRL_07_T                       ad_bvgain_ctrl_07;	//0xCC8E062C
	O24A0_LED_BVGAIN_CTRL_08_T                       ad_bvgain_ctrl_08;	//0xCC8E0630
	O24A0_LED_BVGAIN_CTRL_09_T                       ad_bvgain_ctrl_09;	//0xCC8E0634
	O24A0_LED_BVGAIN_CTRL_10_T                       ad_bvgain_ctrl_10;	//0xCC8E0638
	O24A0_LED_BVGAIN_CTRL_11_T                       ad_bvgain_ctrl_11;	//0xCC8E063C
	O24A0_LED_BVGAIN_CTRL_12_T                       ad_bvgain_ctrl_12;	//0xCC8E0640
	O24A0_LED_BVGAIN_CTRL_13_T                       ad_bvgain_ctrl_13;	//0xCC8E0644
	O24A0_LED_BVGAIN_CTRL_14_T                       ad_bvgain_ctrl_14;	//0xCC8E0648
	O24A0_LED_BVGAIN_CTRL_15_T                       ad_bvgain_ctrl_15;	//0xCC8E064C
	O24A0_LED_BVGAIN_CTRL_16_T                       ad_bvgain_ctrl_16;	//0xCC8E0650
	O24A0_LED_BVGAIN_CTRL_17_T                       ad_bvgain_ctrl_17;	//0xCC8E0654
	UINT32                                                  reserved171;	//0xCC8E0658
	UINT32                                                  reserved172;	//0xCC8E065C
	UINT32                                                  reserved173;	//0xCC8E0660
	O24A0_LED_BV_MID0_AVG_MIN_MAX_T             ad_bv_mid0_avg_min_max;	//0xCC8E0664
	UINT32                                                  reserved174;	//0xCC8E0668
	UINT32                                                  reserved175;	//0xCC8E066C
	UINT32                                                  reserved176;	//0xCC8E0670
	UINT32                                                  reserved177;	//0xCC8E0674
	UINT32                                                  reserved178;	//0xCC8E0678
	UINT32                                                  reserved179;	//0xCC8E067C
	O24A0_LED_BVBPL_CTRL_00_T                         ad_bvbpl_ctrl_00;	//0xCC8E0680
	O24A0_LED_BVBPL_CTRL_01_T                         ad_bvbpl_ctrl_01;	//0xCC8E0684
	O24A0_LED_BVBPL_CTRL_02_T                         ad_bvbpl_ctrl_02;	//0xCC8E0688
	O24A0_LED_BVBPL_CTRL_03_T                         ad_bvbpl_ctrl_03;	//0xCC8E068C
	O24A0_LED_BVBPL_CTRL_04_T                         ad_bvbpl_ctrl_04;	//0xCC8E0690
	O24A0_LED_BVBPL_CTRL_05_T                         ad_bvbpl_ctrl_05;	//0xCC8E0694
	O24A0_LED_BVBPL_CTRL_06_T                         ad_bvbpl_ctrl_06;	//0xCC8E0698
	O24A0_LED_BVBPL_CTRL_07_T                         ad_bvbpl_ctrl_07;	//0xCC8E069C
	O24A0_LED_BVBPL_CTRL_08_T                         ad_bvbpl_ctrl_08;	//0xCC8E06A0
	O24A0_LED_BVBPL_CTRL_09_T                         ad_bvbpl_ctrl_09;	//0xCC8E06A4
	O24A0_LED_BVBPL_CTRL_10_T                         ad_bvbpl_ctrl_10;	//0xCC8E06A8
	O24A0_LED_BVBPL_CTRL_11_T                         ad_bvbpl_ctrl_11;	//0xCC8E06AC
	O24A0_LED_BVBPL_CTRL_12_T                         ad_bvbpl_ctrl_12;	//0xCC8E06B0
	O24A0_LED_BV_MID1_AVG_MIN_MAX_T             ad_bv_mid1_avg_min_max;	//0xCC8E06B4
	UINT32                                                  reserved180;	//0xCC8E06B8
	UINT32                                                  reserved181;	//0xCC8E06BC
	O24A0_LED_WB2P_EN_T                                     ad_wb2p_en;	//0xCC8E06C0
	O24A0_LED_WB2P_R_GAIN_T                             ad_wb2p_r_gain;	//0xCC8E06C4
	O24A0_LED_WB2P_G_GAIN_T                             ad_wb2p_g_gain;	//0xCC8E06C8
	O24A0_LED_WB2P_B_GAIN_T                             ad_wb2p_b_gain;	//0xCC8E06CC
	O24A0_LED_WB2P_R_OFFSET_T                         ad_wb2p_r_offset;	//0xCC8E06D0
	O24A0_LED_WB2P_G_OFFSET_T                         ad_wb2p_g_offset;	//0xCC8E06D4
	O24A0_LED_WB2P_B_OFFSET_T                         ad_wb2p_b_offset;	//0xCC8E06D8
	UINT32                                                  reserved182;	//0xCC8E06DC
	O24A0_LED_BV_GSC_CTRL_00_T                       ad_bv_gsc_ctrl_00;	//0xCC8E06E0
	UINT32                                                  reserved183;	//0xCC8E06E4
	UINT32                                                  reserved184;	//0xCC8E06E8
	UINT32                                                  reserved185;	//0xCC8E06EC
	UINT32                                                  reserved186;	//0xCC8E06F0
	UINT32                                                  reserved187;	//0xCC8E06F4
	UINT32                                                  reserved188;	//0xCC8E06F8
	UINT32                                                  reserved189;	//0xCC8E06FC
	O24A0_LED_OUT_CTRL_00_T                             ad_out_ctrl_00;	//0xCC8E0700
	O24A0_LED_OUT_CTRL_01_T                             ad_out_ctrl_01;	//0xCC8E0704
	O24A0_LED_OUT_CTRL_02_T                             ad_out_ctrl_02;	//0xCC8E0708
	O24A0_LED_OUT_CTRL_03_T                             ad_out_ctrl_03;	//0xCC8E070C
	O24A0_LED_OUT_CTRL_04_T                             ad_out_ctrl_04;	//0xCC8E0710
	O24A0_LED_OUT_CTRL_05_T                             ad_out_ctrl_05;	//0xCC8E0714
	O24A0_LED_OUT_CTRL_06_T                             ad_out_ctrl_06;	//0xCC8E0718
	O24A0_LED_OUT_CTRL_07_T                             ad_out_ctrl_07;	//0xCC8E071C
	UINT32                                                  reserved190;	//0xCC8E0720
	UINT32                                                  reserved191;	//0xCC8E0724
	UINT32                                                  reserved192;	//0xCC8E0728
	UINT32                                                  reserved193;	//0xCC8E072C
	UINT32                                                  reserved194;	//0xCC8E0730
	UINT32                                                  reserved195;	//0xCC8E0734
	UINT32                                                  reserved196;	//0xCC8E0738
	UINT32                                                  reserved197;	//0xCC8E073C
	UINT32                                                  reserved198;	//0xCC8E0740
	UINT32                                                  reserved199;	//0xCC8E0744
	UINT32                                                  reserved200;	//0xCC8E0748
	UINT32                                                  reserved201;	//0xCC8E074C
	UINT32                                                  reserved202;	//0xCC8E0750
	UINT32                                                  reserved203;	//0xCC8E0754
	UINT32                                                  reserved204;	//0xCC8E0758
	UINT32                                                  reserved205;	//0xCC8E075C
	UINT32                                                  reserved206;	//0xCC8E0760
	UINT32                                                  reserved207;	//0xCC8E0764
	UINT32                                                  reserved208;	//0xCC8E0768
	UINT32                                                  reserved209;	//0xCC8E076C
	O24A0_LED_APL_VALUE_OP_T                           ad_apl_value_op;	//0xCC8E0770
	O24A0_LED_APL_MAX_OUT_T                             ad_apl_max_out;	//0xCC8E0774
	O24A0_LED_APL_DBG_OUT_T                             ad_apl_dbg_out;	//0xCC8E0778
	UINT32                                                  reserved210;	//0xCC8E077C
	O24A0_LED_OAPL_EOTF_WR_DONE_T                 ad_oapl_eotf_wr_done;	//0xCC8E0780
	O24A0_LED_OAPL_EOTF_WDATA_T                     ad_oapl_eotf_wdata;	//0xCC8E0784
	O24A0_LED_OAPL_EOTF_RDATA_T                     ad_oapl_eotf_rdata;	//0xCC8E0788
	UINT32                                                  reserved211;	//0xCC8E078C
	UINT32                                                  reserved212;	//0xCC8E0790
	UINT32                                                  reserved213;	//0xCC8E0794
	UINT32                                                  reserved214;	//0xCC8E0798
	UINT32                                                  reserved215;	//0xCC8E079C
	UINT32                                                  reserved216;	//0xCC8E07A0
	UINT32                                                  reserved217;	//0xCC8E07A4
	UINT32                                                  reserved218;	//0xCC8E07A8
	UINT32                                                  reserved219;	//0xCC8E07AC
	UINT32                                                  reserved220;	//0xCC8E07B0
	UINT32                                                  reserved221;	//0xCC8E07B4
	UINT32                                                  reserved222;	//0xCC8E07B8
	UINT32                                                  reserved223;	//0xCC8E07BC
	UINT32                                                  reserved224;	//0xCC8E07C0
	UINT32                                                  reserved225;	//0xCC8E07C4
	UINT32                                                  reserved226;	//0xCC8E07C8
	UINT32                                                  reserved227;	//0xCC8E07CC
	UINT32                                                  reserved228;	//0xCC8E07D0
	UINT32                                                  reserved229;	//0xCC8E07D4
	UINT32                                                  reserved230;	//0xCC8E07D8
	UINT32                                                  reserved231;	//0xCC8E07DC
	UINT32                                                  reserved232;	//0xCC8E07E0
	UINT32                                                  reserved233;	//0xCC8E07E4
	UINT32                                                  reserved234;	//0xCC8E07E8
	UINT32                                                  reserved235;	//0xCC8E07EC
	UINT32                                                  reserved236;	//0xCC8E07F0
	UINT32                                                  reserved237;	//0xCC8E07F4
	UINT32                                                  reserved238;	//0xCC8E07F8
	UINT32                                                  reserved239;	//0xCC8E07FC
	O24A0_LED_MON_SYNC_IN_0_T                         ad_mon_sync_in_0;	//0xCC8E0800
	O24A0_LED_MON_SYNC_IN_1_T                         ad_mon_sync_in_1;	//0xCC8E0804
	O24A0_LED_MON_SYNC_IN_2_T                         ad_mon_sync_in_2;	//0xCC8E0808
	O24A0_LED_MON_SYNC_IN_3_T                         ad_mon_sync_in_3;	//0xCC8E080C
	UINT32                                                  reserved240;	//0xCC8E0810
	UINT32                                                  reserved241;	//0xCC8E0814
	UINT32                                                  reserved242;	//0xCC8E0818
	UINT32                                                  reserved243;	//0xCC8E081C
	UINT32                                                  reserved244;	//0xCC8E0820
	UINT32                                                  reserved245;	//0xCC8E0824
	UINT32                                                  reserved246;	//0xCC8E0828
	UINT32                                                  reserved247;	//0xCC8E082C
	UINT32                                                  reserved248;	//0xCC8E0830
	UINT32                                                  reserved249;	//0xCC8E0834
	UINT32                                                  reserved250;	//0xCC8E0838
	UINT32                                                  reserved251;	//0xCC8E083C
	UINT32                                                  reserved252;	//0xCC8E0840
	UINT32                                                  reserved253;	//0xCC8E0844
	UINT32                                                  reserved254;	//0xCC8E0848
	UINT32                                                  reserved255;	//0xCC8E084C
	UINT32                                                  reserved256;	//0xCC8E0850
	UINT32                                                  reserved257;	//0xCC8E0854
	UINT32                                                  reserved258;	//0xCC8E0858
	UINT32                                                  reserved259;	//0xCC8E085C
	UINT32                                                  reserved260;	//0xCC8E0860
	UINT32                                                  reserved261;	//0xCC8E0864
	UINT32                                                  reserved262;	//0xCC8E0868
	UINT32                                                  reserved263;	//0xCC8E086C
	UINT32                                                  reserved264;	//0xCC8E0870
	UINT32                                                  reserved265;	//0xCC8E0874
	UINT32                                                  reserved266;	//0xCC8E0878
	UINT32                                                  reserved267;	//0xCC8E087C
	UINT32                                                  reserved268;	//0xCC8E0880
	UINT32                                                  reserved269;	//0xCC8E0884
	UINT32                                                  reserved270;	//0xCC8E0888
	UINT32                                                  reserved271;	//0xCC8E088C
	UINT32                                                  reserved272;	//0xCC8E0890
	UINT32                                                  reserved273;	//0xCC8E0894
	UINT32                                                  reserved274;	//0xCC8E0898
	UINT32                                                  reserved275;	//0xCC8E089C
	UINT32                                                  reserved276;	//0xCC8E08A0
	UINT32                                                  reserved277;	//0xCC8E08A4
	UINT32                                                  reserved278;	//0xCC8E08A8
	UINT32                                                  reserved279;	//0xCC8E08AC
	UINT32                                                  reserved280;	//0xCC8E08B0
	UINT32                                                  reserved281;	//0xCC8E08B4
	UINT32                                                  reserved282;	//0xCC8E08B8
	UINT32                                                  reserved283;	//0xCC8E08BC
	UINT32                                                  reserved284;	//0xCC8E08C0
	UINT32                                                  reserved285;	//0xCC8E08C4
	UINT32                                                  reserved286;	//0xCC8E08C8
	UINT32                                                  reserved287;	//0xCC8E08CC
	UINT32                                                  reserved288;	//0xCC8E08D0
	UINT32                                                  reserved289;	//0xCC8E08D4
	UINT32                                                  reserved290;	//0xCC8E08D8
	UINT32                                                  reserved291;	//0xCC8E08DC
	UINT32                                                  reserved292;	//0xCC8E08E0
	UINT32                                                  reserved293;	//0xCC8E08E4
	UINT32                                                  reserved294;	//0xCC8E08E8
	UINT32                                                  reserved295;	//0xCC8E08EC
	UINT32                                                  reserved296;	//0xCC8E08F0
	UINT32                                                  reserved297;	//0xCC8E08F4
	UINT32                                                  reserved298;	//0xCC8E08F8
	UINT32                                                  reserved299;	//0xCC8E08FC
	O24A0_LED_BLU_BLK_NUM_DISP_CLK_T           ad_blu_blk_num_disp_clk;	//0xCC8E0900
	O24A0_LED_REVERSE_T                                     ad_reverse;	//0xCC8E0904
	UINT32                                                  reserved300;	//0xCC8E0908
	UINT32                                                  reserved301;	//0xCC8E090C
	UINT32                                                  reserved302;	//0xCC8E0910
	UINT32                                                  reserved303;	//0xCC8E0914
	UINT32                                                  reserved304;	//0xCC8E0918
	UINT32                                                  reserved305;	//0xCC8E091C
	UINT32                                                  reserved306;	//0xCC8E0920
	UINT32                                                  reserved307;	//0xCC8E0924
	UINT32                                                  reserved308;	//0xCC8E0928
	UINT32                                                  reserved309;	//0xCC8E092C
	UINT32                                                  reserved310;	//0xCC8E0930
	UINT32                                                  reserved311;	//0xCC8E0934
	UINT32                                                  reserved312;	//0xCC8E0938
	UINT32                                                  reserved313;	//0xCC8E093C
	O24A0_LED_MAX_OPT_AI_ILLUMINANT_T         ad_max_opt_ai_illuminant;	//0xCC8E0940
	O24A0_LED_BLK_MAX_MODE_AI_ILLUMINANT_T  ad_blk_max_mode_ai_illuminant;	//0xCC8E0944
	O24A0_LED_MAX_OPT_MODE_AI_ILLUMINANT_T  ad_max_opt_mode_ai_illuminant;	//0xCC8E0948
	O24A0_LED_MAX_OPT0_1_AI_ILLUMINANT_T    ad_max_opt0_1_ai_illuminant;	//0xCC8E094C
	O24A0_LED_LEVEL_TH_AI_ILLUMINANT_T       ad_level_th_ai_illuminant;	//0xCC8E0950
	O24A0_LED_NUMBER_TH_AI_ILLUMINANT_T     ad_number_th_ai_illuminant;	//0xCC8E0954
	O24A0_LED_APL_AI_ILLUMINANT_T                 ad_apl_ai_illuminant;	//0xCC8E0958
	O24A0_LED_BV_GEN_X1_X2_AI_ILLUMINANT_T  ad_bv_gen_x1_x2_ai_illuminant;	//0xCC8E095C
	O24A0_LED_BV_GEN_X3_X4_AI_ILLUMINANT_T  ad_bv_gen_x3_x4_ai_illuminant;	//0xCC8E0960
	O24A0_LED_BV_GEN_Y0_Y1_AI_ILLUMINANT_T  ad_bv_gen_y0_y1_ai_illuminant;	//0xCC8E0964
	O24A0_LED_BV_GEN_Y2_Y3_AI_ILLUMINANT_T  ad_bv_gen_y2_y3_ai_illuminant;	//0xCC8E0968
	O24A0_LED_BV_GEN_Y4_Y5_AI_ILLUMINANT_T  ad_bv_gen_y4_y5_ai_illuminant;	//0xCC8E096C
	O24A0_LED_BV_GEN_BV_MAX_AI_ILLUMINANT_T ad_bv_gen_bv_max_ai_illuminant;	//0xCC8E0970
	O24A0_LED_BV_MIN_MAX_AI_ILLUMINANT_T    ad_bv_min_max_ai_illuminant;	//0xCC8E0974
	O24A0_LED_BV_LUT_MIN_MAX_AI_ILLUMINANT_T ad_bv_lut_min_max_ai_illuminant;	//0xCC8E0978
	O24A0_LED_BV_FINAL_AVG_MIN_MAX_AI_ILLUMINANT_T ad_bv_final_avg_min_max_ai_illuminant;	//0xCC8E097C
	O24A0_LED_VIN_CONFIG_AI_ILLUMINANT_T    ad_vin_config_ai_illuminant;	//0xCC8E0980
	O24A0_LED_BV_GEN_BLK_NUM_HV_AI_ILLUMINANT_T ad_bv_gen_blk_num_hv_ai_illuminant;	//0xCC8E0984
	O24A0_LED_BV_GEN_HV_SIZE_AI_ILLUMINANT_T ad_bv_gen_hv_size_ai_illuminant;	//0xCC8E0988
	O24A0_LED_BPL_IN_SEL_T                               ad_bpl_in_sel;	//0xCC8E098C
	O24A0_LED_AI_ILLUMINANT_MAP_SEL_T         ad_ai_illuminant_map_sel;	//0xCC8E0990
	O24A0_LED_CC_LD_DIRECT_PATH_SEL_T         ad_cc_ld_direct_path_sel;	//0xCC8E0994
	UINT32                                                  reserved314;	//0xCC8E0998
	UINT32                                                  reserved315;	//0xCC8E099C
	UINT32                                                  reserved316;	//0xCC8E09A0
	UINT32                                                  reserved317;	//0xCC8E09A4
	UINT32                                                  reserved318;	//0xCC8E09A8
	UINT32                                                  reserved319;	//0xCC8E09AC
	UINT32                                                  reserved320;	//0xCC8E09B0
	UINT32                                                  reserved321;	//0xCC8E09B4
	UINT32                                                  reserved322;	//0xCC8E09B8
	UINT32                                                  reserved323;	//0xCC8E09BC
	O24A0_LED_AIBVGAIN_MERGE_CTRL_00_T       ad_aibvgain_merge_ctrl_00;	//0xCC8E09C0
	O24A0_LED_AIBVGAIN_MERGE_CTRL_01_T       ad_aibvgain_merge_ctrl_01;	//0xCC8E09C4
	O24A0_LED_AIBVGAIN_MERGE_CTRL_02_T       ad_aibvgain_merge_ctrl_02;	//0xCC8E09C8
	O24A0_LED_AIBVGAIN_MERGE_CTRL_03_T       ad_aibvgain_merge_ctrl_03;	//0xCC8E09CC
	O24A0_LED_AIBVGAIN_MERGE_CTRL_04_T       ad_aibvgain_merge_ctrl_04;	//0xCC8E09D0
	O24A0_LED_AIBVGAIN_MERGE_CTRL_05_T       ad_aibvgain_merge_ctrl_05;	//0xCC8E09D4
	O24A0_LED_AIBVGAIN_MERGE_CTRL_06_T       ad_aibvgain_merge_ctrl_06;	//0xCC8E09D8
	O24A0_LED_AIBVGAIN_MERGE_CTRL_07_T       ad_aibvgain_merge_ctrl_07;	//0xCC8E09DC
	O24A0_LED_AIBVGAIN_MERGE_CTRL_08_T       ad_aibvgain_merge_ctrl_08;	//0xCC8E09E0
	O24A0_LED_AIBVGAIN_MERGE_CTRL_09_T       ad_aibvgain_merge_ctrl_09;	//0xCC8E09E4
	UINT32                                                  reserved324;	//0xCC8E09E8
	UINT32                                                  reserved325;	//0xCC8E09EC
	UINT32                                                  reserved326;	//0xCC8E09F0
	UINT32                                                  reserved327;	//0xCC8E09F4
	UINT32                                                  reserved328;	//0xCC8E09F8
	UINT32                                                  reserved329;	//0xCC8E09FC
	O24A0_LED_COMP_LUT_CTRL_00_T                   ad_comp_lut_ctrl_00;	//0xCC8E0A00
	O24A0_LED_COMP_LUT_CTRL_01_T                   ad_comp_lut_ctrl_01;	//0xCC8E0A04
	O24A0_LED_COMP_LUT_CTRL_02_T                   ad_comp_lut_ctrl_02;	//0xCC8E0A08
	O24A0_LED_COMP_LUT_CTRL_03_T                   ad_comp_lut_ctrl_03;	//0xCC8E0A0C
	O24A0_LED_COMP_LUT_CTRL_04_T                   ad_comp_lut_ctrl_04;	//0xCC8E0A10
	O24A0_LED_COMP_LUT_CTRL_05_T                   ad_comp_lut_ctrl_05;	//0xCC8E0A14
	O24A0_LED_COMP_LUT_CTRL_06_T                   ad_comp_lut_ctrl_06;	//0xCC8E0A18
	O24A0_LED_COMP_LUT_CTRL_07_T                   ad_comp_lut_ctrl_07;	//0xCC8E0A1C
	UINT32                                                  reserved330;	//0xCC8E0A20
	UINT32                                                  reserved331;	//0xCC8E0A24
	UINT32                                                  reserved332;	//0xCC8E0A28
	UINT32                                                  reserved333;	//0xCC8E0A2C
	UINT32                                                  reserved334;	//0xCC8E0A30
	UINT32                                                  reserved335;	//0xCC8E0A34
	UINT32                                                  reserved336;	//0xCC8E0A38
	UINT32                                                  reserved337;	//0xCC8E0A3C
	O24A0_LED_OUT_PROC_CTRL_00_T                   ad_out_proc_ctrl_00;	//0xCC8E0A40
	O24A0_LED_OUT_PROC_CTRL_01_T                   ad_out_proc_ctrl_01;	//0xCC8E0A44
	O24A0_LED_OUT_PROC_CTRL_02_T                   ad_out_proc_ctrl_02;	//0xCC8E0A48
	O24A0_LED_OUT_PROC_CTRL_03_T                   ad_out_proc_ctrl_03;	//0xCC8E0A4C
	O24A0_LED_OUT_PROC_CTRL_04_T                   ad_out_proc_ctrl_04;	//0xCC8E0A50
	O24A0_LED_OUT_PROC_CTRL_05_T                   ad_out_proc_ctrl_05;	//0xCC8E0A54
	O24A0_LED_OUT_PROC_CTRL_06_T                   ad_out_proc_ctrl_06;	//0xCC8E0A58
	O24A0_LED_OUT_PROC_CTRL_07_T                   ad_out_proc_ctrl_07;	//0xCC8E0A5C
	UINT32                                                  reserved338;	//0xCC8E0A60
	UINT32                                                  reserved339;	//0xCC8E0A64
	O24A0_LED_OUT_PROC_CTRL_DISP_00_T         ad_out_proc_ctrl_disp_00;	//0xCC8E0A68
	O24A0_LED_OUT_PROC_CTRL_DISP_01_T         ad_out_proc_ctrl_disp_01;	//0xCC8E0A6C
	O24A0_LED_OUT_PROC_CTRL_DISP_02_T         ad_out_proc_ctrl_disp_02;	//0xCC8E0A70
	O24A0_LED_OUT_PROC_DBG_00_T                     ad_out_proc_dbg_00;	//0xCC8E0A74
	O24A0_LED_OUT_PROC_DBG_01_T                     ad_out_proc_dbg_01;	//0xCC8E0A78
	O24A0_LED_OUT_PROC_DBG_02_T                     ad_out_proc_dbg_02;	//0xCC8E0A7C
	O24A0_LED_OUT_PROC_DBG_03_T                     ad_out_proc_dbg_03;	//0xCC8E0A80
	O24A0_LED_OUT_PROC_DBG_04_T                     ad_out_proc_dbg_04;	//0xCC8E0A84
	O24A0_LED_OUT_PROC_DBG_05_T                     ad_out_proc_dbg_05;	//0xCC8E0A88
	O24A0_LED_OUT_PROC_DBG_06_T                     ad_out_proc_dbg_06;	//0xCC8E0A8C
	O24A0_LED_OUT_PROC_DBG_07_T                     ad_out_proc_dbg_07;	//0xCC8E0A90
	O24A0_LED_OUT_PROC_DBG_08_T                     ad_out_proc_dbg_08;	//0xCC8E0A94
	O24A0_LED_OUT_PROC_DBG_09_T                     ad_out_proc_dbg_09;	//0xCC8E0A98
	O24A0_LED_OUT_PROC_DBG_10_T                     ad_out_proc_dbg_10;	//0xCC8E0A9C
	O24A0_LED_OUT_PROC_DBG_11_T                     ad_out_proc_dbg_11;	//0xCC8E0AA0
	O24A0_LED_BOUNDARY_CTRL_00_T                   ad_boundary_ctrl_00;	//0xCC8E0AA4
	O24A0_LED_BOUNDARY_CTRL_01_T                   ad_boundary_ctrl_01;	//0xCC8E0AA8
	O24A0_LED_BOUNDARY_CTRL_02_T                   ad_boundary_ctrl_02;	//0xCC8E0AAC
	O24A0_LED_BOUNDARY_CTRL_03_T                   ad_boundary_ctrl_03;	//0xCC8E0AB0
	O24A0_LED_BOUNDARY_CTRL_04_T                   ad_boundary_ctrl_04;	//0xCC8E0AB4
	O24A0_LED_BOUNDARY_CTRL_05_T                   ad_boundary_ctrl_05;	//0xCC8E0AB8
	O24A0_LED_BOUNDARY_CTRL_06_T                   ad_boundary_ctrl_06;	//0xCC8E0ABC
	O24A0_LED_BOUNDARY_STATUS_00_T               ad_boundary_status_00;	//0xCC8E0AC0
	O24A0_LED_MPIP_SWAP_CTRL_00_T                 ad_mpip_swap_ctrl_00;	//0xCC8E0AC4
	O24A0_LED_MPIP_SWAP_CTRL_01_T                 ad_mpip_swap_ctrl_01;	//0xCC8E0AC8
	O24A0_LED_MPIP_SWAP_CTRL_02_T                 ad_mpip_swap_ctrl_02;	//0xCC8E0ACC
	O24A0_LED_MPIP_SWAP_CTRL_03_T                 ad_mpip_swap_ctrl_03;	//0xCC8E0AD0
	O24A0_LED_MPIP_SWAP_CTRL_04_T                 ad_mpip_swap_ctrl_04;	//0xCC8E0AD4
	O24A0_LED_MPIP_SWAP_CTRL_05_T                 ad_mpip_swap_ctrl_05;	//0xCC8E0AD8
	O24A0_LED_MPIP_STATUS_00_T                       ad_mpip_status_00;	//0xCC8E0ADC
	O24A0_LED_MPIP_STATUS_01_T                       ad_mpip_status_01;	//0xCC8E0AE0
	O24A0_LED_FPS_T                                             ad_fps;	//0xCC8E0AE4
	UINT32                                                  reserved340;	//0xCC8E0AE8
	UINT32                                                  reserved341;	//0xCC8E0AEC
	UINT32                                                  reserved342;	//0xCC8E0AF0
	UINT32                                                  reserved343;	//0xCC8E0AF4
	UINT32                                                  reserved344;	//0xCC8E0AF8
	UINT32                                                  reserved345;	//0xCC8E0AFC
	UINT32                                                  reserved346;	//0xCC8E0B00
	UINT32                                                  reserved347;	//0xCC8E0B04
	UINT32                                                  reserved348;	//0xCC8E0B08
	UINT32                                                  reserved349;	//0xCC8E0B0C
	UINT32                                                  reserved350;	//0xCC8E0B10
	UINT32                                                  reserved351;	//0xCC8E0B14
	UINT32                                                  reserved352;	//0xCC8E0B18
	UINT32                                                  reserved353;	//0xCC8E0B1C
	UINT32                                                  reserved354;	//0xCC8E0B20
	UINT32                                                  reserved355;	//0xCC8E0B24
	UINT32                                                  reserved356;	//0xCC8E0B28
	UINT32                                                  reserved357;	//0xCC8E0B2C
	UINT32                                                  reserved358;	//0xCC8E0B30
	UINT32                                                  reserved359;	//0xCC8E0B34
	UINT32                                                  reserved360;	//0xCC8E0B38
	UINT32                                                  reserved361;	//0xCC8E0B3C
	UINT32                                                  reserved362;	//0xCC8E0B40
	UINT32                                                  reserved363;	//0xCC8E0B44
	UINT32                                                  reserved364;	//0xCC8E0B48
	UINT32                                                  reserved365;	//0xCC8E0B4C
	UINT32                                                  reserved366;	//0xCC8E0B50
	UINT32                                                  reserved367;	//0xCC8E0B54
	UINT32                                                  reserved368;	//0xCC8E0B58
	UINT32                                                  reserved369;	//0xCC8E0B5C
	UINT32                                                  reserved370;	//0xCC8E0B60
	UINT32                                                  reserved371;	//0xCC8E0B64
	UINT32                                                  reserved372;	//0xCC8E0B68
	UINT32                                                  reserved373;	//0xCC8E0B6C
	UINT32                                                  reserved374;	//0xCC8E0B70
	UINT32                                                  reserved375;	//0xCC8E0B74
	UINT32                                                  reserved376;	//0xCC8E0B78
	UINT32                                                  reserved377;	//0xCC8E0B7C
	UINT32                                                  reserved378;	//0xCC8E0B80
	UINT32                                                  reserved379;	//0xCC8E0B84
	UINT32                                                  reserved380;	//0xCC8E0B88
	UINT32                                                  reserved381;	//0xCC8E0B8C
	UINT32                                                  reserved382;	//0xCC8E0B90
	UINT32                                                  reserved383;	//0xCC8E0B94
	UINT32                                                  reserved384;	//0xCC8E0B98
	UINT32                                                  reserved385;	//0xCC8E0B9C
	UINT32                                                  reserved386;	//0xCC8E0BA0
	UINT32                                                  reserved387;	//0xCC8E0BA4
	UINT32                                                  reserved388;	//0xCC8E0BA8
	UINT32                                                  reserved389;	//0xCC8E0BAC
	UINT32                                                  reserved390;	//0xCC8E0BB0
	UINT32                                                  reserved391;	//0xCC8E0BB4
	UINT32                                                  reserved392;	//0xCC8E0BB8
	UINT32                                                  reserved393;	//0xCC8E0BBC
	UINT32                                                  reserved394;	//0xCC8E0BC0
	UINT32                                                  reserved395;	//0xCC8E0BC4
	UINT32                                                  reserved396;	//0xCC8E0BC8
	UINT32                                                  reserved397;	//0xCC8E0BCC
	UINT32                                                  reserved398;	//0xCC8E0BD0
	UINT32                                                  reserved399;	//0xCC8E0BD4
	UINT32                                                  reserved400;	//0xCC8E0BD8
	UINT32                                                  reserved401;	//0xCC8E0BDC
	UINT32                                                  reserved402;	//0xCC8E0BE0
	UINT32                                                  reserved403;	//0xCC8E0BE4
	UINT32                                                  reserved404;	//0xCC8E0BE8
	UINT32                                                  reserved405;	//0xCC8E0BEC
	UINT32                                                  reserved406;	//0xCC8E0BF0
	UINT32                                                  reserved407;	//0xCC8E0BF4
	UINT32                                                  reserved408;	//0xCC8E0BF8
	UINT32                                                  reserved409;	//0xCC8E0BFC
	UINT32                                                  reserved410;	//0xCC8E0C00
	UINT32                                                  reserved411;	//0xCC8E0C04
	UINT32                                                  reserved412;	//0xCC8E0C08
	UINT32                                                  reserved413;	//0xCC8E0C0C
	UINT32                                                  reserved414;	//0xCC8E0C10
	UINT32                                                  reserved415;	//0xCC8E0C14
	UINT32                                                  reserved416;	//0xCC8E0C18
	UINT32                                                  reserved417;	//0xCC8E0C1C
	UINT32                                                  reserved418;	//0xCC8E0C20
	UINT32                                                  reserved419;	//0xCC8E0C24
	UINT32                                                  reserved420;	//0xCC8E0C28
	UINT32                                                  reserved421;	//0xCC8E0C2C
	UINT32                                                  reserved422;	//0xCC8E0C30
	UINT32                                                  reserved423;	//0xCC8E0C34
	UINT32                                                  reserved424;	//0xCC8E0C38
	UINT32                                                  reserved425;	//0xCC8E0C3C
	UINT32                                                  reserved426;	//0xCC8E0C40
	UINT32                                                  reserved427;	//0xCC8E0C44
	UINT32                                                  reserved428;	//0xCC8E0C48
	UINT32                                                  reserved429;	//0xCC8E0C4C
	UINT32                                                  reserved430;	//0xCC8E0C50
	UINT32                                                  reserved431;	//0xCC8E0C54
	UINT32                                                  reserved432;	//0xCC8E0C58
	UINT32                                                  reserved433;	//0xCC8E0C5C
	UINT32                                                  reserved434;	//0xCC8E0C60
	UINT32                                                  reserved435;	//0xCC8E0C64
	UINT32                                                  reserved436;	//0xCC8E0C68
	UINT32                                                  reserved437;	//0xCC8E0C6C
	UINT32                                                  reserved438;	//0xCC8E0C70
	UINT32                                                  reserved439;	//0xCC8E0C74
	UINT32                                                  reserved440;	//0xCC8E0C78
	UINT32                                                  reserved441;	//0xCC8E0C7C
	UINT32                                                  reserved442;	//0xCC8E0C80
	UINT32                                                  reserved443;	//0xCC8E0C84
	UINT32                                                  reserved444;	//0xCC8E0C88
	UINT32                                                  reserved445;	//0xCC8E0C8C
	UINT32                                                  reserved446;	//0xCC8E0C90
	UINT32                                                  reserved447;	//0xCC8E0C94
	UINT32                                                  reserved448;	//0xCC8E0C98
	UINT32                                                  reserved449;	//0xCC8E0C9C
	UINT32                                                  reserved450;	//0xCC8E0CA0
	UINT32                                                  reserved451;	//0xCC8E0CA4
	UINT32                                                  reserved452;	//0xCC8E0CA8
	UINT32                                                  reserved453;	//0xCC8E0CAC
	UINT32                                                  reserved454;	//0xCC8E0CB0
	UINT32                                                  reserved455;	//0xCC8E0CB4
	UINT32                                                  reserved456;	//0xCC8E0CB8
	UINT32                                                  reserved457;	//0xCC8E0CBC
	UINT32                                                  reserved458;	//0xCC8E0CC0
	UINT32                                                  reserved459;	//0xCC8E0CC4
	UINT32                                                  reserved460;	//0xCC8E0CC8
	UINT32                                                  reserved461;	//0xCC8E0CCC
	UINT32                                                  reserved462;	//0xCC8E0CD0
	UINT32                                                  reserved463;	//0xCC8E0CD4
	UINT32                                                  reserved464;	//0xCC8E0CD8
	UINT32                                                  reserved465;	//0xCC8E0CDC
	UINT32                                                  reserved466;	//0xCC8E0CE0
	UINT32                                                  reserved467;	//0xCC8E0CE4
	UINT32                                                  reserved468;	//0xCC8E0CE8
	UINT32                                                  reserved469;	//0xCC8E0CEC
	UINT32                                                  reserved470;	//0xCC8E0CF0
	UINT32                                                  reserved471;	//0xCC8E0CF4
	UINT32                                                  reserved472;	//0xCC8E0CF8
	UINT32                                                  reserved473;	//0xCC8E0CFC
	UINT32                                                  reserved474;	//0xCC8E0D00
	UINT32                                                  reserved475;	//0xCC8E0D04
	UINT32                                                  reserved476;	//0xCC8E0D08
	UINT32                                                  reserved477;	//0xCC8E0D0C
	UINT32                                                  reserved478;	//0xCC8E0D10
	UINT32                                                  reserved479;	//0xCC8E0D14
	UINT32                                                  reserved480;	//0xCC8E0D18
	UINT32                                                  reserved481;	//0xCC8E0D1C
	UINT32                                                  reserved482;	//0xCC8E0D20
	UINT32                                                  reserved483;	//0xCC8E0D24
	UINT32                                                  reserved484;	//0xCC8E0D28
	UINT32                                                  reserved485;	//0xCC8E0D2C
	UINT32                                                  reserved486;	//0xCC8E0D30
	UINT32                                                  reserved487;	//0xCC8E0D34
	UINT32                                                  reserved488;	//0xCC8E0D38
	UINT32                                                  reserved489;	//0xCC8E0D3C
	UINT32                                                  reserved490;	//0xCC8E0D40
	UINT32                                                  reserved491;	//0xCC8E0D44
	UINT32                                                  reserved492;	//0xCC8E0D48
	UINT32                                                  reserved493;	//0xCC8E0D4C
	UINT32                                                  reserved494;	//0xCC8E0D50
	UINT32                                                  reserved495;	//0xCC8E0D54
	UINT32                                                  reserved496;	//0xCC8E0D58
	UINT32                                                  reserved497;	//0xCC8E0D5C
	UINT32                                                  reserved498;	//0xCC8E0D60
	UINT32                                                  reserved499;	//0xCC8E0D64
	UINT32                                                  reserved500;	//0xCC8E0D68
	UINT32                                                  reserved501;	//0xCC8E0D6C
	UINT32                                                  reserved502;	//0xCC8E0D70
	UINT32                                                  reserved503;	//0xCC8E0D74
	UINT32                                                  reserved504;	//0xCC8E0D78
	UINT32                                                  reserved505;	//0xCC8E0D7C
	UINT32                                                  reserved506;	//0xCC8E0D80
	UINT32                                                  reserved507;	//0xCC8E0D84
	UINT32                                                  reserved508;	//0xCC8E0D88
	UINT32                                                  reserved509;	//0xCC8E0D8C
	UINT32                                                  reserved510;	//0xCC8E0D90
	UINT32                                                  reserved511;	//0xCC8E0D94
	UINT32                                                  reserved512;	//0xCC8E0D98
	UINT32                                                  reserved513;	//0xCC8E0D9C
	UINT32                                                  reserved514;	//0xCC8E0DA0
	UINT32                                                  reserved515;	//0xCC8E0DA4
	UINT32                                                  reserved516;	//0xCC8E0DA8
	UINT32                                                  reserved517;	//0xCC8E0DAC
	UINT32                                                  reserved518;	//0xCC8E0DB0
	UINT32                                                  reserved519;	//0xCC8E0DB4
	UINT32                                                  reserved520;	//0xCC8E0DB8
	UINT32                                                  reserved521;	//0xCC8E0DBC
	UINT32                                                  reserved522;	//0xCC8E0DC0
	UINT32                                                  reserved523;	//0xCC8E0DC4
	UINT32                                                  reserved524;	//0xCC8E0DC8
	UINT32                                                  reserved525;	//0xCC8E0DCC
	UINT32                                                  reserved526;	//0xCC8E0DD0
	UINT32                                                  reserved527;	//0xCC8E0DD4
	UINT32                                                  reserved528;	//0xCC8E0DD8
	UINT32                                                  reserved529;	//0xCC8E0DDC
	UINT32                                                  reserved530;	//0xCC8E0DE0
	UINT32                                                  reserved531;	//0xCC8E0DE4
	UINT32                                                  reserved532;	//0xCC8E0DE8
	UINT32                                                  reserved533;	//0xCC8E0DEC
	UINT32                                                  reserved534;	//0xCC8E0DF0
	UINT32                                                  reserved535;	//0xCC8E0DF4
	UINT32                                                  reserved536;	//0xCC8E0DF8
	UINT32                                                  reserved537;	//0xCC8E0DFC
	UINT32                                                  reserved538;	//0xCC8E0E00
	UINT32                                                  reserved539;	//0xCC8E0E04
	UINT32                                                  reserved540;	//0xCC8E0E08
	UINT32                                                  reserved541;	//0xCC8E0E0C
	UINT32                                                  reserved542;	//0xCC8E0E10
	UINT32                                                  reserved543;	//0xCC8E0E14
	UINT32                                                  reserved544;	//0xCC8E0E18
	UINT32                                                  reserved545;	//0xCC8E0E1C
	UINT32                                                  reserved546;	//0xCC8E0E20
	UINT32                                                  reserved547;	//0xCC8E0E24
	UINT32                                                  reserved548;	//0xCC8E0E28
	UINT32                                                  reserved549;	//0xCC8E0E2C
	UINT32                                                  reserved550;	//0xCC8E0E30
	UINT32                                                  reserved551;	//0xCC8E0E34
	UINT32                                                  reserved552;	//0xCC8E0E38
	UINT32                                                  reserved553;	//0xCC8E0E3C
	UINT32                                                  reserved554;	//0xCC8E0E40
	UINT32                                                  reserved555;	//0xCC8E0E44
	UINT32                                                  reserved556;	//0xCC8E0E48
	UINT32                                                  reserved557;	//0xCC8E0E4C
	UINT32                                                  reserved558;	//0xCC8E0E50
	UINT32                                                  reserved559;	//0xCC8E0E54
	UINT32                                                  reserved560;	//0xCC8E0E58
	UINT32                                                  reserved561;	//0xCC8E0E5C
	UINT32                                                  reserved562;	//0xCC8E0E60
	UINT32                                                  reserved563;	//0xCC8E0E64
	UINT32                                                  reserved564;	//0xCC8E0E68
	UINT32                                                  reserved565;	//0xCC8E0E6C
	UINT32                                                  reserved566;	//0xCC8E0E70
	UINT32                                                  reserved567;	//0xCC8E0E74
	UINT32                                                  reserved568;	//0xCC8E0E78
	UINT32                                                  reserved569;	//0xCC8E0E7C
	UINT32                                                  reserved570;	//0xCC8E0E80
	UINT32                                                  reserved571;	//0xCC8E0E84
	UINT32                                                  reserved572;	//0xCC8E0E88
	UINT32                                                  reserved573;	//0xCC8E0E8C
	UINT32                                                  reserved574;	//0xCC8E0E90
	UINT32                                                  reserved575;	//0xCC8E0E94
	UINT32                                                  reserved576;	//0xCC8E0E98
	UINT32                                                  reserved577;	//0xCC8E0E9C
	UINT32                                                  reserved578;	//0xCC8E0EA0
	UINT32                                                  reserved579;	//0xCC8E0EA4
	UINT32                                                  reserved580;	//0xCC8E0EA8
	UINT32                                                  reserved581;	//0xCC8E0EAC
	UINT32                                                  reserved582;	//0xCC8E0EB0
	UINT32                                                  reserved583;	//0xCC8E0EB4
	UINT32                                                  reserved584;	//0xCC8E0EB8
	UINT32                                                  reserved585;	//0xCC8E0EBC
	UINT32                                                  reserved586;	//0xCC8E0EC0
	UINT32                                                  reserved587;	//0xCC8E0EC4
	UINT32                                                  reserved588;	//0xCC8E0EC8
	UINT32                                                  reserved589;	//0xCC8E0ECC
	UINT32                                                  reserved590;	//0xCC8E0ED0
	UINT32                                                  reserved591;	//0xCC8E0ED4
	UINT32                                                  reserved592;	//0xCC8E0ED8
	UINT32                                                  reserved593;	//0xCC8E0EDC
	UINT32                                                  reserved594;	//0xCC8E0EE0
	UINT32                                                  reserved595;	//0xCC8E0EE4
	UINT32                                                  reserved596;	//0xCC8E0EE8
	UINT32                                                  reserved597;	//0xCC8E0EEC
	UINT32                                                  reserved598;	//0xCC8E0EF0
	UINT32                                                  reserved599;	//0xCC8E0EF4
	UINT32                                                  reserved600;	//0xCC8E0EF8
	UINT32                                                  reserved601;	//0xCC8E0EFC
	UINT32                                                  reserved602;	//0xCC8E0F00
	UINT32                                                  reserved603;	//0xCC8E0F04
	UINT32                                                  reserved604;	//0xCC8E0F08
	UINT32                                                  reserved605;	//0xCC8E0F0C
	UINT32                                                  reserved606;	//0xCC8E0F10
	UINT32                                                  reserved607;	//0xCC8E0F14
	UINT32                                                  reserved608;	//0xCC8E0F18
	UINT32                                                  reserved609;	//0xCC8E0F1C
	UINT32                                                  reserved610;	//0xCC8E0F20
	UINT32                                                  reserved611;	//0xCC8E0F24
	UINT32                                                  reserved612;	//0xCC8E0F28
	UINT32                                                  reserved613;	//0xCC8E0F2C
	UINT32                                                  reserved614;	//0xCC8E0F30
	UINT32                                                  reserved615;	//0xCC8E0F34
	UINT32                                                  reserved616;	//0xCC8E0F38
	UINT32                                                  reserved617;	//0xCC8E0F3C
	UINT32                                                  reserved618;	//0xCC8E0F40
	UINT32                                                  reserved619;	//0xCC8E0F44
	UINT32                                                  reserved620;	//0xCC8E0F48
	UINT32                                                  reserved621;	//0xCC8E0F4C
	UINT32                                                  reserved622;	//0xCC8E0F50
	UINT32                                                  reserved623;	//0xCC8E0F54
	UINT32                                                  reserved624;	//0xCC8E0F58
	UINT32                                                  reserved625;	//0xCC8E0F5C
	UINT32                                                  reserved626;	//0xCC8E0F60
	UINT32                                                  reserved627;	//0xCC8E0F64
	UINT32                                                  reserved628;	//0xCC8E0F68
	UINT32                                                  reserved629;	//0xCC8E0F6C
	UINT32                                                  reserved630;	//0xCC8E0F70
	UINT32                                                  reserved631;	//0xCC8E0F74
	UINT32                                                  reserved632;	//0xCC8E0F78
	UINT32                                                  reserved633;	//0xCC8E0F7C
	UINT32                                                  reserved634;	//0xCC8E0F80
	UINT32                                                  reserved635;	//0xCC8E0F84
	UINT32                                                  reserved636;	//0xCC8E0F88
	UINT32                                                  reserved637;	//0xCC8E0F8C
	UINT32                                                  reserved638;	//0xCC8E0F90
	UINT32                                                  reserved639;	//0xCC8E0F94
	UINT32                                                  reserved640;	//0xCC8E0F98
	UINT32                                                  reserved641;	//0xCC8E0F9C
	UINT32                                                  reserved642;	//0xCC8E0FA0
	UINT32                                                  reserved643;	//0xCC8E0FA4
	UINT32                                                  reserved644;	//0xCC8E0FA8
	UINT32                                                  reserved645;	//0xCC8E0FAC
	UINT32                                                  reserved646;	//0xCC8E0FB0
	UINT32                                                  reserved647;	//0xCC8E0FB4
	UINT32                                                  reserved648;	//0xCC8E0FB8
	UINT32                                                  reserved649;	//0xCC8E0FBC
	UINT32                                                  reserved650;	//0xCC8E0FC0
	UINT32                                                  reserved651;	//0xCC8E0FC4
	UINT32                                                  reserved652;	//0xCC8E0FC8
	UINT32                                                  reserved653;	//0xCC8E0FCC
	UINT32                                                  reserved654;	//0xCC8E0FD0
	UINT32                                                  reserved655;	//0xCC8E0FD4
	UINT32                                                  reserved656;	//0xCC8E0FD8
	UINT32                                                  reserved657;	//0xCC8E0FDC
	UINT32                                                  reserved658;	//0xCC8E0FE0
	UINT32                                                  reserved659;	//0xCC8E0FE4
	UINT32                                                  reserved660;	//0xCC8E0FE8
	UINT32                                                  reserved661;	//0xCC8E0FEC
	UINT32                                                  reserved662;	//0xCC8E0FF0
	UINT32                                                  reserved663;	//0xCC8E0FF4
	UINT32                                                  reserved664;	//0xCC8E0FF8
	UINT32                                                  reserved665;	//0xCC8E0FFC
	UINT32                                                  reserved666;	//0xCC8E1000
	UINT32                                                  reserved667;	//0xCC8E1004
	UINT32                                                  reserved668;	//0xCC8E1008
	UINT32                                                  reserved669;	//0xCC8E100C
	UINT32                                                  reserved670;	//0xCC8E1010
	UINT32                                                  reserved671;	//0xCC8E1014
	UINT32                                                  reserved672;	//0xCC8E1018
	UINT32                                                  reserved673;	//0xCC8E101C
	UINT32                                                  reserved674;	//0xCC8E1020
	UINT32                                                  reserved675;	//0xCC8E1024
	UINT32                                                  reserved676;	//0xCC8E1028
	UINT32                                                  reserved677;	//0xCC8E102C
	UINT32                                                  reserved678;	//0xCC8E1030
	UINT32                                                  reserved679;	//0xCC8E1034
	UINT32                                                  reserved680;	//0xCC8E1038
	UINT32                                                  reserved681;	//0xCC8E103C
	UINT32                                                  reserved682;	//0xCC8E1040
	UINT32                                                  reserved683;	//0xCC8E1044
	UINT32                                                  reserved684;	//0xCC8E1048
	UINT32                                                  reserved685;	//0xCC8E104C
	UINT32                                                  reserved686;	//0xCC8E1050
	UINT32                                                  reserved687;	//0xCC8E1054
	UINT32                                                  reserved688;	//0xCC8E1058
	UINT32                                                  reserved689;	//0xCC8E105C
	UINT32                                                  reserved690;	//0xCC8E1060
	UINT32                                                  reserved691;	//0xCC8E1064
	UINT32                                                  reserved692;	//0xCC8E1068
	UINT32                                                  reserved693;	//0xCC8E106C
	UINT32                                                  reserved694;	//0xCC8E1070
	UINT32                                                  reserved695;	//0xCC8E1074
	UINT32                                                  reserved696;	//0xCC8E1078
	UINT32                                                  reserved697;	//0xCC8E107C
	UINT32                                                  reserved698;	//0xCC8E1080
	UINT32                                                  reserved699;	//0xCC8E1084
	UINT32                                                  reserved700;	//0xCC8E1088
	UINT32                                                  reserved701;	//0xCC8E108C
	UINT32                                                  reserved702;	//0xCC8E1090
	UINT32                                                  reserved703;	//0xCC8E1094
	UINT32                                                  reserved704;	//0xCC8E1098
	UINT32                                                  reserved705;	//0xCC8E109C
	UINT32                                                  reserved706;	//0xCC8E10A0
	UINT32                                                  reserved707;	//0xCC8E10A4
	UINT32                                                  reserved708;	//0xCC8E10A8
	UINT32                                                  reserved709;	//0xCC8E10AC
	UINT32                                                  reserved710;	//0xCC8E10B0
	UINT32                                                  reserved711;	//0xCC8E10B4
	UINT32                                                  reserved712;	//0xCC8E10B8
	UINT32                                                  reserved713;	//0xCC8E10BC
	UINT32                                                  reserved714;	//0xCC8E10C0
	UINT32                                                  reserved715;	//0xCC8E10C4
	UINT32                                                  reserved716;	//0xCC8E10C8
	UINT32                                                  reserved717;	//0xCC8E10CC
	UINT32                                                  reserved718;	//0xCC8E10D0
	UINT32                                                  reserved719;	//0xCC8E10D4
	UINT32                                                  reserved720;	//0xCC8E10D8
	UINT32                                                  reserved721;	//0xCC8E10DC
	UINT32                                                  reserved722;	//0xCC8E10E0
	UINT32                                                  reserved723;	//0xCC8E10E4
	UINT32                                                  reserved724;	//0xCC8E10E8
	UINT32                                                  reserved725;	//0xCC8E10EC
	UINT32                                                  reserved726;	//0xCC8E10F0
	UINT32                                                  reserved727;	//0xCC8E10F4
	UINT32                                                  reserved728;	//0xCC8E10F8
	UINT32                                                  reserved729;	//0xCC8E10FC
	UINT32                                                  reserved730;	//0xCC8E1100
	UINT32                                                  reserved731;	//0xCC8E1104
	UINT32                                                  reserved732;	//0xCC8E1108
	UINT32                                                  reserved733;	//0xCC8E110C
	UINT32                                                  reserved734;	//0xCC8E1110
	UINT32                                                  reserved735;	//0xCC8E1114
	UINT32                                                  reserved736;	//0xCC8E1118
	UINT32                                                  reserved737;	//0xCC8E111C
	UINT32                                                  reserved738;	//0xCC8E1120
	UINT32                                                  reserved739;	//0xCC8E1124
	UINT32                                                  reserved740;	//0xCC8E1128
	UINT32                                                  reserved741;	//0xCC8E112C
	UINT32                                                  reserved742;	//0xCC8E1130
	UINT32                                                  reserved743;	//0xCC8E1134
	UINT32                                                  reserved744;	//0xCC8E1138
	UINT32                                                  reserved745;	//0xCC8E113C
	UINT32                                                  reserved746;	//0xCC8E1140
	UINT32                                                  reserved747;	//0xCC8E1144
	UINT32                                                  reserved748;	//0xCC8E1148
	UINT32                                                  reserved749;	//0xCC8E114C
	UINT32                                                  reserved750;	//0xCC8E1150
	UINT32                                                  reserved751;	//0xCC8E1154
	UINT32                                                  reserved752;	//0xCC8E1158
	UINT32                                                  reserved753;	//0xCC8E115C
	UINT32                                                  reserved754;	//0xCC8E1160
	UINT32                                                  reserved755;	//0xCC8E1164
	UINT32                                                  reserved756;	//0xCC8E1168
	UINT32                                                  reserved757;	//0xCC8E116C
	UINT32                                                  reserved758;	//0xCC8E1170
	UINT32                                                  reserved759;	//0xCC8E1174
	UINT32                                                  reserved760;	//0xCC8E1178
	UINT32                                                  reserved761;	//0xCC8E117C
	UINT32                                                  reserved762;	//0xCC8E1180
	UINT32                                                  reserved763;	//0xCC8E1184
	UINT32                                                  reserved764;	//0xCC8E1188
	UINT32                                                  reserved765;	//0xCC8E118C
	UINT32                                                  reserved766;	//0xCC8E1190
	UINT32                                                  reserved767;	//0xCC8E1194
	UINT32                                                  reserved768;	//0xCC8E1198
	UINT32                                                  reserved769;	//0xCC8E119C
	UINT32                                                  reserved770;	//0xCC8E11A0
	UINT32                                                  reserved771;	//0xCC8E11A4
	UINT32                                                  reserved772;	//0xCC8E11A8
	UINT32                                                  reserved773;	//0xCC8E11AC
	UINT32                                                  reserved774;	//0xCC8E11B0
	UINT32                                                  reserved775;	//0xCC8E11B4
	UINT32                                                  reserved776;	//0xCC8E11B8
	UINT32                                                  reserved777;	//0xCC8E11BC
	UINT32                                                  reserved778;	//0xCC8E11C0
	UINT32                                                  reserved779;	//0xCC8E11C4
	UINT32                                                  reserved780;	//0xCC8E11C8
	UINT32                                                  reserved781;	//0xCC8E11CC
	UINT32                                                  reserved782;	//0xCC8E11D0
	UINT32                                                  reserved783;	//0xCC8E11D4
	UINT32                                                  reserved784;	//0xCC8E11D8
	UINT32                                                  reserved785;	//0xCC8E11DC
	UINT32                                                  reserved786;	//0xCC8E11E0
	UINT32                                                  reserved787;	//0xCC8E11E4
	UINT32                                                  reserved788;	//0xCC8E11E8
	UINT32                                                  reserved789;	//0xCC8E11EC
	UINT32                                                  reserved790;	//0xCC8E11F0
	UINT32                                                  reserved791;	//0xCC8E11F4
	UINT32                                                  reserved792;	//0xCC8E11F8
	UINT32                                                  reserved793;	//0xCC8E11FC
	UINT32                                                  reserved794;	//0xCC8E1200
	UINT32                                                  reserved795;	//0xCC8E1204
	UINT32                                                  reserved796;	//0xCC8E1208
	UINT32                                                  reserved797;	//0xCC8E120C
	UINT32                                                  reserved798;	//0xCC8E1210
	UINT32                                                  reserved799;	//0xCC8E1214
	UINT32                                                  reserved800;	//0xCC8E1218
	UINT32                                                  reserved801;	//0xCC8E121C
	UINT32                                                  reserved802;	//0xCC8E1220
	UINT32                                                  reserved803;	//0xCC8E1224
	UINT32                                                  reserved804;	//0xCC8E1228
	UINT32                                                  reserved805;	//0xCC8E122C
	UINT32                                                  reserved806;	//0xCC8E1230
	UINT32                                                  reserved807;	//0xCC8E1234
	UINT32                                                  reserved808;	//0xCC8E1238
	UINT32                                                  reserved809;	//0xCC8E123C
	UINT32                                                  reserved810;	//0xCC8E1240
	UINT32                                                  reserved811;	//0xCC8E1244
	UINT32                                                  reserved812;	//0xCC8E1248
	UINT32                                                  reserved813;	//0xCC8E124C
	UINT32                                                  reserved814;	//0xCC8E1250
	UINT32                                                  reserved815;	//0xCC8E1254
	UINT32                                                  reserved816;	//0xCC8E1258
	UINT32                                                  reserved817;	//0xCC8E125C
	UINT32                                                  reserved818;	//0xCC8E1260
	UINT32                                                  reserved819;	//0xCC8E1264
	UINT32                                                  reserved820;	//0xCC8E1268
	UINT32                                                  reserved821;	//0xCC8E126C
	UINT32                                                  reserved822;	//0xCC8E1270
	UINT32                                                  reserved823;	//0xCC8E1274
	UINT32                                                  reserved824;	//0xCC8E1278
	UINT32                                                  reserved825;	//0xCC8E127C
	UINT32                                                  reserved826;	//0xCC8E1280
	UINT32                                                  reserved827;	//0xCC8E1284
	UINT32                                                  reserved828;	//0xCC8E1288
	UINT32                                                  reserved829;	//0xCC8E128C
	UINT32                                                  reserved830;	//0xCC8E1290
	UINT32                                                  reserved831;	//0xCC8E1294
	UINT32                                                  reserved832;	//0xCC8E1298
	UINT32                                                  reserved833;	//0xCC8E129C
	UINT32                                                  reserved834;	//0xCC8E12A0
	UINT32                                                  reserved835;	//0xCC8E12A4
	UINT32                                                  reserved836;	//0xCC8E12A8
	UINT32                                                  reserved837;	//0xCC8E12AC
	UINT32                                                  reserved838;	//0xCC8E12B0
	UINT32                                                  reserved839;	//0xCC8E12B4
	UINT32                                                  reserved840;	//0xCC8E12B8
	UINT32                                                  reserved841;	//0xCC8E12BC
	UINT32                                                  reserved842;	//0xCC8E12C0
	UINT32                                                  reserved843;	//0xCC8E12C4
	UINT32                                                  reserved844;	//0xCC8E12C8
	UINT32                                                  reserved845;	//0xCC8E12CC
	UINT32                                                  reserved846;	//0xCC8E12D0
	UINT32                                                  reserved847;	//0xCC8E12D4
	UINT32                                                  reserved848;	//0xCC8E12D8
	UINT32                                                  reserved849;	//0xCC8E12DC
	UINT32                                                  reserved850;	//0xCC8E12E0
	UINT32                                                  reserved851;	//0xCC8E12E4
	UINT32                                                  reserved852;	//0xCC8E12E8
	UINT32                                                  reserved853;	//0xCC8E12EC
	UINT32                                                  reserved854;	//0xCC8E12F0
	UINT32                                                  reserved855;	//0xCC8E12F4
	UINT32                                                  reserved856;	//0xCC8E12F8
	UINT32                                                  reserved857;	//0xCC8E12FC
	UINT32                                                  reserved858;	//0xCC8E1300
	UINT32                                                  reserved859;	//0xCC8E1304
	UINT32                                                  reserved860;	//0xCC8E1308
	UINT32                                                  reserved861;	//0xCC8E130C
	UINT32                                                  reserved862;	//0xCC8E1310
	UINT32                                                  reserved863;	//0xCC8E1314
	UINT32                                                  reserved864;	//0xCC8E1318
	UINT32                                                  reserved865;	//0xCC8E131C
	UINT32                                                  reserved866;	//0xCC8E1320
	UINT32                                                  reserved867;	//0xCC8E1324
	UINT32                                                  reserved868;	//0xCC8E1328
	UINT32                                                  reserved869;	//0xCC8E132C
	UINT32                                                  reserved870;	//0xCC8E1330
	UINT32                                                  reserved871;	//0xCC8E1334
	UINT32                                                  reserved872;	//0xCC8E1338
	UINT32                                                  reserved873;	//0xCC8E133C
	UINT32                                                  reserved874;	//0xCC8E1340
	UINT32                                                  reserved875;	//0xCC8E1344
	UINT32                                                  reserved876;	//0xCC8E1348
	UINT32                                                  reserved877;	//0xCC8E134C
	UINT32                                                  reserved878;	//0xCC8E1350
	UINT32                                                  reserved879;	//0xCC8E1354
	UINT32                                                  reserved880;	//0xCC8E1358
	UINT32                                                  reserved881;	//0xCC8E135C
	UINT32                                                  reserved882;	//0xCC8E1360
	UINT32                                                  reserved883;	//0xCC8E1364
	UINT32                                                  reserved884;	//0xCC8E1368
	UINT32                                                  reserved885;	//0xCC8E136C
	UINT32                                                  reserved886;	//0xCC8E1370
	UINT32                                                  reserved887;	//0xCC8E1374
	UINT32                                                  reserved888;	//0xCC8E1378
	UINT32                                                  reserved889;	//0xCC8E137C
	UINT32                                                  reserved890;	//0xCC8E1380
	UINT32                                                  reserved891;	//0xCC8E1384
	UINT32                                                  reserved892;	//0xCC8E1388
	UINT32                                                  reserved893;	//0xCC8E138C
	UINT32                                                  reserved894;	//0xCC8E1390
	UINT32                                                  reserved895;	//0xCC8E1394
	UINT32                                                  reserved896;	//0xCC8E1398
	UINT32                                                  reserved897;	//0xCC8E139C
	UINT32                                                  reserved898;	//0xCC8E13A0
	UINT32                                                  reserved899;	//0xCC8E13A4
	UINT32                                                  reserved900;	//0xCC8E13A8
	UINT32                                                  reserved901;	//0xCC8E13AC
	UINT32                                                  reserved902;	//0xCC8E13B0
	UINT32                                                  reserved903;	//0xCC8E13B4
	UINT32                                                  reserved904;	//0xCC8E13B8
	UINT32                                                  reserved905;	//0xCC8E13BC
	UINT32                                                  reserved906;	//0xCC8E13C0
	UINT32                                                  reserved907;	//0xCC8E13C4
	UINT32                                                  reserved908;	//0xCC8E13C8
	UINT32                                                  reserved909;	//0xCC8E13CC
	UINT32                                                  reserved910;	//0xCC8E13D0
	UINT32                                                  reserved911;	//0xCC8E13D4
	UINT32                                                  reserved912;	//0xCC8E13D8
	UINT32                                                  reserved913;	//0xCC8E13DC
	UINT32                                                  reserved914;	//0xCC8E13E0
	UINT32                                                  reserved915;	//0xCC8E13E4
	UINT32                                                  reserved916;	//0xCC8E13E8
	UINT32                                                  reserved917;	//0xCC8E13EC
	UINT32                                                  reserved918;	//0xCC8E13F0
	UINT32                                                  reserved919;	//0xCC8E13F4
	UINT32                                                  reserved920;	//0xCC8E13F8
	UINT32                                                  reserved921;	//0xCC8E13FC
	UINT32                                                  reserved922;	//0xCC8E1400
	UINT32                                                  reserved923;	//0xCC8E1404
	UINT32                                                  reserved924;	//0xCC8E1408
	UINT32                                                  reserved925;	//0xCC8E140C
	UINT32                                                  reserved926;	//0xCC8E1410
	UINT32                                                  reserved927;	//0xCC8E1414
	UINT32                                                  reserved928;	//0xCC8E1418
	UINT32                                                  reserved929;	//0xCC8E141C
	UINT32                                                  reserved930;	//0xCC8E1420
	UINT32                                                  reserved931;	//0xCC8E1424
	UINT32                                                  reserved932;	//0xCC8E1428
	UINT32                                                  reserved933;	//0xCC8E142C
	UINT32                                                  reserved934;	//0xCC8E1430
	UINT32                                                  reserved935;	//0xCC8E1434
	UINT32                                                  reserved936;	//0xCC8E1438
	UINT32                                                  reserved937;	//0xCC8E143C
	UINT32                                                  reserved938;	//0xCC8E1440
	UINT32                                                  reserved939;	//0xCC8E1444
	UINT32                                                  reserved940;	//0xCC8E1448
	UINT32                                                  reserved941;	//0xCC8E144C
	UINT32                                                  reserved942;	//0xCC8E1450
	UINT32                                                  reserved943;	//0xCC8E1454
	UINT32                                                  reserved944;	//0xCC8E1458
	UINT32                                                  reserved945;	//0xCC8E145C
	UINT32                                                  reserved946;	//0xCC8E1460
	UINT32                                                  reserved947;	//0xCC8E1464
	UINT32                                                  reserved948;	//0xCC8E1468
	UINT32                                                  reserved949;	//0xCC8E146C
	UINT32                                                  reserved950;	//0xCC8E1470
	UINT32                                                  reserved951;	//0xCC8E1474
	UINT32                                                  reserved952;	//0xCC8E1478
	UINT32                                                  reserved953;	//0xCC8E147C
	UINT32                                                  reserved954;	//0xCC8E1480
	UINT32                                                  reserved955;	//0xCC8E1484
	UINT32                                                  reserved956;	//0xCC8E1488
	UINT32                                                  reserved957;	//0xCC8E148C
	UINT32                                                  reserved958;	//0xCC8E1490
	UINT32                                                  reserved959;	//0xCC8E1494
	UINT32                                                  reserved960;	//0xCC8E1498
	UINT32                                                  reserved961;	//0xCC8E149C
	UINT32                                                  reserved962;	//0xCC8E14A0
	UINT32                                                  reserved963;	//0xCC8E14A4
	UINT32                                                  reserved964;	//0xCC8E14A8
	UINT32                                                  reserved965;	//0xCC8E14AC
	UINT32                                                  reserved966;	//0xCC8E14B0
	UINT32                                                  reserved967;	//0xCC8E14B4
	UINT32                                                  reserved968;	//0xCC8E14B8
	UINT32                                                  reserved969;	//0xCC8E14BC
	UINT32                                                  reserved970;	//0xCC8E14C0
	UINT32                                                  reserved971;	//0xCC8E14C4
	UINT32                                                  reserved972;	//0xCC8E14C8
	UINT32                                                  reserved973;	//0xCC8E14CC
	UINT32                                                  reserved974;	//0xCC8E14D0
	UINT32                                                  reserved975;	//0xCC8E14D4
	UINT32                                                  reserved976;	//0xCC8E14D8
	UINT32                                                  reserved977;	//0xCC8E14DC
	UINT32                                                  reserved978;	//0xCC8E14E0
	UINT32                                                  reserved979;	//0xCC8E14E4
	UINT32                                                  reserved980;	//0xCC8E14E8
	UINT32                                                  reserved981;	//0xCC8E14EC
	UINT32                                                  reserved982;	//0xCC8E14F0
	UINT32                                                  reserved983;	//0xCC8E14F4
	UINT32                                                  reserved984;	//0xCC8E14F8
	UINT32                                                  reserved985;	//0xCC8E14FC
	UINT32                                                  reserved986;	//0xCC8E1500
	UINT32                                                  reserved987;	//0xCC8E1504
	UINT32                                                  reserved988;	//0xCC8E1508
	UINT32                                                  reserved989;	//0xCC8E150C
	UINT32                                                  reserved990;	//0xCC8E1510
	UINT32                                                  reserved991;	//0xCC8E1514
	UINT32                                                  reserved992;	//0xCC8E1518
	UINT32                                                  reserved993;	//0xCC8E151C
	UINT32                                                  reserved994;	//0xCC8E1520
	UINT32                                                  reserved995;	//0xCC8E1524
	UINT32                                                  reserved996;	//0xCC8E1528
	UINT32                                                  reserved997;	//0xCC8E152C
	UINT32                                                  reserved998;	//0xCC8E1530
	UINT32                                                  reserved999;	//0xCC8E1534
	UINT32                                                 reserved1000;	//0xCC8E1538
	UINT32                                                 reserved1001;	//0xCC8E153C
	UINT32                                                 reserved1002;	//0xCC8E1540
	UINT32                                                 reserved1003;	//0xCC8E1544
	UINT32                                                 reserved1004;	//0xCC8E1548
	UINT32                                                 reserved1005;	//0xCC8E154C
	UINT32                                                 reserved1006;	//0xCC8E1550
	UINT32                                                 reserved1007;	//0xCC8E1554
	UINT32                                                 reserved1008;	//0xCC8E1558
	UINT32                                                 reserved1009;	//0xCC8E155C
	UINT32                                                 reserved1010;	//0xCC8E1560
	UINT32                                                 reserved1011;	//0xCC8E1564
	UINT32                                                 reserved1012;	//0xCC8E1568
	UINT32                                                 reserved1013;	//0xCC8E156C
	UINT32                                                 reserved1014;	//0xCC8E1570
	UINT32                                                 reserved1015;	//0xCC8E1574
	UINT32                                                 reserved1016;	//0xCC8E1578
	UINT32                                                 reserved1017;	//0xCC8E157C
	UINT32                                                 reserved1018;	//0xCC8E1580
	UINT32                                                 reserved1019;	//0xCC8E1584
	UINT32                                                 reserved1020;	//0xCC8E1588
	UINT32                                                 reserved1021;	//0xCC8E158C
	UINT32                                                 reserved1022;	//0xCC8E1590
	UINT32                                                 reserved1023;	//0xCC8E1594
	UINT32                                                 reserved1024;	//0xCC8E1598
	UINT32                                                 reserved1025;	//0xCC8E159C
	UINT32                                                 reserved1026;	//0xCC8E15A0
	UINT32                                                 reserved1027;	//0xCC8E15A4
	UINT32                                                 reserved1028;	//0xCC8E15A8
	UINT32                                                 reserved1029;	//0xCC8E15AC
	UINT32                                                 reserved1030;	//0xCC8E15B0
	UINT32                                                 reserved1031;	//0xCC8E15B4
	UINT32                                                 reserved1032;	//0xCC8E15B8
	UINT32                                                 reserved1033;	//0xCC8E15BC
	UINT32                                                 reserved1034;	//0xCC8E15C0
	UINT32                                                 reserved1035;	//0xCC8E15C4
	UINT32                                                 reserved1036;	//0xCC8E15C8
	UINT32                                                 reserved1037;	//0xCC8E15CC
	UINT32                                                 reserved1038;	//0xCC8E15D0
	UINT32                                                 reserved1039;	//0xCC8E15D4
	UINT32                                                 reserved1040;	//0xCC8E15D8
	UINT32                                                 reserved1041;	//0xCC8E15DC
	UINT32                                                 reserved1042;	//0xCC8E15E0
	UINT32                                                 reserved1043;	//0xCC8E15E4
	UINT32                                                 reserved1044;	//0xCC8E15E8
	UINT32                                                 reserved1045;	//0xCC8E15EC
	UINT32                                                 reserved1046;	//0xCC8E15F0
	UINT32                                                 reserved1047;	//0xCC8E15F4
	UINT32                                                 reserved1048;	//0xCC8E15F8
	UINT32                                                 reserved1049;	//0xCC8E15FC
	UINT32                                                 reserved1050;	//0xCC8E1600
	UINT32                                                 reserved1051;	//0xCC8E1604
	UINT32                                                 reserved1052;	//0xCC8E1608
	UINT32                                                 reserved1053;	//0xCC8E160C
	UINT32                                                 reserved1054;	//0xCC8E1610
	UINT32                                                 reserved1055;	//0xCC8E1614
	UINT32                                                 reserved1056;	//0xCC8E1618
	UINT32                                                 reserved1057;	//0xCC8E161C
	UINT32                                                 reserved1058;	//0xCC8E1620
	UINT32                                                 reserved1059;	//0xCC8E1624
	UINT32                                                 reserved1060;	//0xCC8E1628
	UINT32                                                 reserved1061;	//0xCC8E162C
	UINT32                                                 reserved1062;	//0xCC8E1630
	UINT32                                                 reserved1063;	//0xCC8E1634
	UINT32                                                 reserved1064;	//0xCC8E1638
	UINT32                                                 reserved1065;	//0xCC8E163C
	UINT32                                                 reserved1066;	//0xCC8E1640
	UINT32                                                 reserved1067;	//0xCC8E1644
	UINT32                                                 reserved1068;	//0xCC8E1648
	UINT32                                                 reserved1069;	//0xCC8E164C
	UINT32                                                 reserved1070;	//0xCC8E1650
	UINT32                                                 reserved1071;	//0xCC8E1654
	UINT32                                                 reserved1072;	//0xCC8E1658
	UINT32                                                 reserved1073;	//0xCC8E165C
	UINT32                                                 reserved1074;	//0xCC8E1660
	UINT32                                                 reserved1075;	//0xCC8E1664
	UINT32                                                 reserved1076;	//0xCC8E1668
	UINT32                                                 reserved1077;	//0xCC8E166C
	UINT32                                                 reserved1078;	//0xCC8E1670
	UINT32                                                 reserved1079;	//0xCC8E1674
	UINT32                                                 reserved1080;	//0xCC8E1678
	UINT32                                                 reserved1081;	//0xCC8E167C
	UINT32                                                 reserved1082;	//0xCC8E1680
	UINT32                                                 reserved1083;	//0xCC8E1684
	UINT32                                                 reserved1084;	//0xCC8E1688
	UINT32                                                 reserved1085;	//0xCC8E168C
	UINT32                                                 reserved1086;	//0xCC8E1690
	UINT32                                                 reserved1087;	//0xCC8E1694
	UINT32                                                 reserved1088;	//0xCC8E1698
	UINT32                                                 reserved1089;	//0xCC8E169C
	UINT32                                                 reserved1090;	//0xCC8E16A0
	UINT32                                                 reserved1091;	//0xCC8E16A4
	UINT32                                                 reserved1092;	//0xCC8E16A8
	UINT32                                                 reserved1093;	//0xCC8E16AC
	UINT32                                                 reserved1094;	//0xCC8E16B0
	UINT32                                                 reserved1095;	//0xCC8E16B4
	UINT32                                                 reserved1096;	//0xCC8E16B8
	UINT32                                                 reserved1097;	//0xCC8E16BC
	UINT32                                                 reserved1098;	//0xCC8E16C0
	UINT32                                                 reserved1099;	//0xCC8E16C4
	UINT32                                                 reserved1100;	//0xCC8E16C8
	UINT32                                                 reserved1101;	//0xCC8E16CC
	UINT32                                                 reserved1102;	//0xCC8E16D0
	UINT32                                                 reserved1103;	//0xCC8E16D4
	UINT32                                                 reserved1104;	//0xCC8E16D8
	UINT32                                                 reserved1105;	//0xCC8E16DC
	UINT32                                                 reserved1106;	//0xCC8E16E0
	UINT32                                                 reserved1107;	//0xCC8E16E4
	UINT32                                                 reserved1108;	//0xCC8E16E8
	UINT32                                                 reserved1109;	//0xCC8E16EC
	UINT32                                                 reserved1110;	//0xCC8E16F0
	UINT32                                                 reserved1111;	//0xCC8E16F4
	UINT32                                                 reserved1112;	//0xCC8E16F8
	UINT32                                                 reserved1113;	//0xCC8E16FC
	UINT32                                                 reserved1114;	//0xCC8E1700
	UINT32                                                 reserved1115;	//0xCC8E1704
	UINT32                                                 reserved1116;	//0xCC8E1708
	UINT32                                                 reserved1117;	//0xCC8E170C
	UINT32                                                 reserved1118;	//0xCC8E1710
	UINT32                                                 reserved1119;	//0xCC8E1714
	UINT32                                                 reserved1120;	//0xCC8E1718
	UINT32                                                 reserved1121;	//0xCC8E171C
	UINT32                                                 reserved1122;	//0xCC8E1720
	UINT32                                                 reserved1123;	//0xCC8E1724
	UINT32                                                 reserved1124;	//0xCC8E1728
	UINT32                                                 reserved1125;	//0xCC8E172C
	UINT32                                                 reserved1126;	//0xCC8E1730
	UINT32                                                 reserved1127;	//0xCC8E1734
	UINT32                                                 reserved1128;	//0xCC8E1738
	UINT32                                                 reserved1129;	//0xCC8E173C
	UINT32                                                 reserved1130;	//0xCC8E1740
	UINT32                                                 reserved1131;	//0xCC8E1744
	UINT32                                                 reserved1132;	//0xCC8E1748
	UINT32                                                 reserved1133;	//0xCC8E174C
	UINT32                                                 reserved1134;	//0xCC8E1750
	UINT32                                                 reserved1135;	//0xCC8E1754
	UINT32                                                 reserved1136;	//0xCC8E1758
	UINT32                                                 reserved1137;	//0xCC8E175C
	UINT32                                                 reserved1138;	//0xCC8E1760
	UINT32                                                 reserved1139;	//0xCC8E1764
	UINT32                                                 reserved1140;	//0xCC8E1768
	UINT32                                                 reserved1141;	//0xCC8E176C
	UINT32                                                 reserved1142;	//0xCC8E1770
	UINT32                                                 reserved1143;	//0xCC8E1774
	UINT32                                                 reserved1144;	//0xCC8E1778
	UINT32                                                 reserved1145;	//0xCC8E177C
	UINT32                                                 reserved1146;	//0xCC8E1780
	UINT32                                                 reserved1147;	//0xCC8E1784
	UINT32                                                 reserved1148;	//0xCC8E1788
	UINT32                                                 reserved1149;	//0xCC8E178C
	UINT32                                                 reserved1150;	//0xCC8E1790
	UINT32                                                 reserved1151;	//0xCC8E1794
	UINT32                                                 reserved1152;	//0xCC8E1798
	UINT32                                                 reserved1153;	//0xCC8E179C
	UINT32                                                 reserved1154;	//0xCC8E17A0
	UINT32                                                 reserved1155;	//0xCC8E17A4
	UINT32                                                 reserved1156;	//0xCC8E17A8
	UINT32                                                 reserved1157;	//0xCC8E17AC
	UINT32                                                 reserved1158;	//0xCC8E17B0
	UINT32                                                 reserved1159;	//0xCC8E17B4
	UINT32                                                 reserved1160;	//0xCC8E17B8
	UINT32                                                 reserved1161;	//0xCC8E17BC
	UINT32                                                 reserved1162;	//0xCC8E17C0
	UINT32                                                 reserved1163;	//0xCC8E17C4
	UINT32                                                 reserved1164;	//0xCC8E17C8
	UINT32                                                 reserved1165;	//0xCC8E17CC
	UINT32                                                 reserved1166;	//0xCC8E17D0
	UINT32                                                 reserved1167;	//0xCC8E17D4
	UINT32                                                 reserved1168;	//0xCC8E17D8
	UINT32                                                 reserved1169;	//0xCC8E17DC
	UINT32                                                 reserved1170;	//0xCC8E17E0
	UINT32                                                 reserved1171;	//0xCC8E17E4
	UINT32                                                 reserved1172;	//0xCC8E17E8
	UINT32                                                 reserved1173;	//0xCC8E17EC
	UINT32                                                 reserved1174;	//0xCC8E17F0
	UINT32                                                 reserved1175;	//0xCC8E17F4
	UINT32                                                 reserved1176;	//0xCC8E17F8
	UINT32                                                 reserved1177;	//0xCC8E17FC
	UINT32                                                 reserved1178;	//0xCC8E1800
	UINT32                                                 reserved1179;	//0xCC8E1804
	UINT32                                                 reserved1180;	//0xCC8E1808
	UINT32                                                 reserved1181;	//0xCC8E180C
	UINT32                                                 reserved1182;	//0xCC8E1810
	UINT32                                                 reserved1183;	//0xCC8E1814
	UINT32                                                 reserved1184;	//0xCC8E1818
	UINT32                                                 reserved1185;	//0xCC8E181C
	UINT32                                                 reserved1186;	//0xCC8E1820
	UINT32                                                 reserved1187;	//0xCC8E1824
	UINT32                                                 reserved1188;	//0xCC8E1828
	UINT32                                                 reserved1189;	//0xCC8E182C
	UINT32                                                 reserved1190;	//0xCC8E1830
	UINT32                                                 reserved1191;	//0xCC8E1834
	UINT32                                                 reserved1192;	//0xCC8E1838
	UINT32                                                 reserved1193;	//0xCC8E183C
	UINT32                                                 reserved1194;	//0xCC8E1840
	UINT32                                                 reserved1195;	//0xCC8E1844
	UINT32                                                 reserved1196;	//0xCC8E1848
	UINT32                                                 reserved1197;	//0xCC8E184C
	UINT32                                                 reserved1198;	//0xCC8E1850
	UINT32                                                 reserved1199;	//0xCC8E1854
	UINT32                                                 reserved1200;	//0xCC8E1858
	UINT32                                                 reserved1201;	//0xCC8E185C
	UINT32                                                 reserved1202;	//0xCC8E1860
	UINT32                                                 reserved1203;	//0xCC8E1864
	UINT32                                                 reserved1204;	//0xCC8E1868
	UINT32                                                 reserved1205;	//0xCC8E186C
	UINT32                                                 reserved1206;	//0xCC8E1870
	UINT32                                                 reserved1207;	//0xCC8E1874
	UINT32                                                 reserved1208;	//0xCC8E1878
	UINT32                                                 reserved1209;	//0xCC8E187C
	UINT32                                                 reserved1210;	//0xCC8E1880
	UINT32                                                 reserved1211;	//0xCC8E1884
	UINT32                                                 reserved1212;	//0xCC8E1888
	UINT32                                                 reserved1213;	//0xCC8E188C
	UINT32                                                 reserved1214;	//0xCC8E1890
	UINT32                                                 reserved1215;	//0xCC8E1894
	UINT32                                                 reserved1216;	//0xCC8E1898
	UINT32                                                 reserved1217;	//0xCC8E189C
	UINT32                                                 reserved1218;	//0xCC8E18A0
	UINT32                                                 reserved1219;	//0xCC8E18A4
	UINT32                                                 reserved1220;	//0xCC8E18A8
	UINT32                                                 reserved1221;	//0xCC8E18AC
	UINT32                                                 reserved1222;	//0xCC8E18B0
	UINT32                                                 reserved1223;	//0xCC8E18B4
	UINT32                                                 reserved1224;	//0xCC8E18B8
	UINT32                                                 reserved1225;	//0xCC8E18BC
	UINT32                                                 reserved1226;	//0xCC8E18C0
	UINT32                                                 reserved1227;	//0xCC8E18C4
	UINT32                                                 reserved1228;	//0xCC8E18C8
	UINT32                                                 reserved1229;	//0xCC8E18CC
	UINT32                                                 reserved1230;	//0xCC8E18D0
	UINT32                                                 reserved1231;	//0xCC8E18D4
	UINT32                                                 reserved1232;	//0xCC8E18D8
	UINT32                                                 reserved1233;	//0xCC8E18DC
	UINT32                                                 reserved1234;	//0xCC8E18E0
	UINT32                                                 reserved1235;	//0xCC8E18E4
	UINT32                                                 reserved1236;	//0xCC8E18E8
	UINT32                                                 reserved1237;	//0xCC8E18EC
	UINT32                                                 reserved1238;	//0xCC8E18F0
	UINT32                                                 reserved1239;	//0xCC8E18F4
	UINT32                                                 reserved1240;	//0xCC8E18F8
	UINT32                                                 reserved1241;	//0xCC8E18FC
	UINT32                                                 reserved1242;	//0xCC8E1900
	UINT32                                                 reserved1243;	//0xCC8E1904
	UINT32                                                 reserved1244;	//0xCC8E1908
	UINT32                                                 reserved1245;	//0xCC8E190C
	UINT32                                                 reserved1246;	//0xCC8E1910
	UINT32                                                 reserved1247;	//0xCC8E1914
	UINT32                                                 reserved1248;	//0xCC8E1918
	UINT32                                                 reserved1249;	//0xCC8E191C
	UINT32                                                 reserved1250;	//0xCC8E1920
	UINT32                                                 reserved1251;	//0xCC8E1924
	UINT32                                                 reserved1252;	//0xCC8E1928
	UINT32                                                 reserved1253;	//0xCC8E192C
	UINT32                                                 reserved1254;	//0xCC8E1930
	UINT32                                                 reserved1255;	//0xCC8E1934
	UINT32                                                 reserved1256;	//0xCC8E1938
	UINT32                                                 reserved1257;	//0xCC8E193C
	UINT32                                                 reserved1258;	//0xCC8E1940
	UINT32                                                 reserved1259;	//0xCC8E1944
	UINT32                                                 reserved1260;	//0xCC8E1948
	UINT32                                                 reserved1261;	//0xCC8E194C
	UINT32                                                 reserved1262;	//0xCC8E1950
	UINT32                                                 reserved1263;	//0xCC8E1954
	UINT32                                                 reserved1264;	//0xCC8E1958
	UINT32                                                 reserved1265;	//0xCC8E195C
	UINT32                                                 reserved1266;	//0xCC8E1960
	UINT32                                                 reserved1267;	//0xCC8E1964
	UINT32                                                 reserved1268;	//0xCC8E1968
	UINT32                                                 reserved1269;	//0xCC8E196C
	UINT32                                                 reserved1270;	//0xCC8E1970
	UINT32                                                 reserved1271;	//0xCC8E1974
	UINT32                                                 reserved1272;	//0xCC8E1978
	UINT32                                                 reserved1273;	//0xCC8E197C
	UINT32                                                 reserved1274;	//0xCC8E1980
	UINT32                                                 reserved1275;	//0xCC8E1984
	UINT32                                                 reserved1276;	//0xCC8E1988
	UINT32                                                 reserved1277;	//0xCC8E198C
	UINT32                                                 reserved1278;	//0xCC8E1990
	UINT32                                                 reserved1279;	//0xCC8E1994
	UINT32                                                 reserved1280;	//0xCC8E1998
	UINT32                                                 reserved1281;	//0xCC8E199C
	UINT32                                                 reserved1282;	//0xCC8E19A0
	UINT32                                                 reserved1283;	//0xCC8E19A4
	UINT32                                                 reserved1284;	//0xCC8E19A8
	UINT32                                                 reserved1285;	//0xCC8E19AC
	UINT32                                                 reserved1286;	//0xCC8E19B0
	UINT32                                                 reserved1287;	//0xCC8E19B4
	UINT32                                                 reserved1288;	//0xCC8E19B8
	UINT32                                                 reserved1289;	//0xCC8E19BC
	UINT32                                                 reserved1290;	//0xCC8E19C0
	UINT32                                                 reserved1291;	//0xCC8E19C4
	UINT32                                                 reserved1292;	//0xCC8E19C8
	UINT32                                                 reserved1293;	//0xCC8E19CC
	UINT32                                                 reserved1294;	//0xCC8E19D0
	UINT32                                                 reserved1295;	//0xCC8E19D4
	UINT32                                                 reserved1296;	//0xCC8E19D8
	UINT32                                                 reserved1297;	//0xCC8E19DC
	UINT32                                                 reserved1298;	//0xCC8E19E0
	UINT32                                                 reserved1299;	//0xCC8E19E4
	UINT32                                                 reserved1300;	//0xCC8E19E8
	UINT32                                                 reserved1301;	//0xCC8E19EC
	UINT32                                                 reserved1302;	//0xCC8E19F0
	UINT32                                                 reserved1303;	//0xCC8E19F4
	UINT32                                                 reserved1304;	//0xCC8E19F8
	UINT32                                                 reserved1305;	//0xCC8E19FC
	UINT32                                                 reserved1306;	//0xCC8E1A00
	UINT32                                                 reserved1307;	//0xCC8E1A04
	UINT32                                                 reserved1308;	//0xCC8E1A08
	UINT32                                                 reserved1309;	//0xCC8E1A0C
	UINT32                                                 reserved1310;	//0xCC8E1A10
	UINT32                                                 reserved1311;	//0xCC8E1A14
	UINT32                                                 reserved1312;	//0xCC8E1A18
	UINT32                                                 reserved1313;	//0xCC8E1A1C
	UINT32                                                 reserved1314;	//0xCC8E1A20
	UINT32                                                 reserved1315;	//0xCC8E1A24
	UINT32                                                 reserved1316;	//0xCC8E1A28
	UINT32                                                 reserved1317;	//0xCC8E1A2C
	UINT32                                                 reserved1318;	//0xCC8E1A30
	UINT32                                                 reserved1319;	//0xCC8E1A34
	UINT32                                                 reserved1320;	//0xCC8E1A38
	UINT32                                                 reserved1321;	//0xCC8E1A3C
	UINT32                                                 reserved1322;	//0xCC8E1A40
	UINT32                                                 reserved1323;	//0xCC8E1A44
	UINT32                                                 reserved1324;	//0xCC8E1A48
	UINT32                                                 reserved1325;	//0xCC8E1A4C
	UINT32                                                 reserved1326;	//0xCC8E1A50
	UINT32                                                 reserved1327;	//0xCC8E1A54
	UINT32                                                 reserved1328;	//0xCC8E1A58
	UINT32                                                 reserved1329;	//0xCC8E1A5C
	UINT32                                                 reserved1330;	//0xCC8E1A60
	UINT32                                                 reserved1331;	//0xCC8E1A64
	UINT32                                                 reserved1332;	//0xCC8E1A68
	UINT32                                                 reserved1333;	//0xCC8E1A6C
	UINT32                                                 reserved1334;	//0xCC8E1A70
	UINT32                                                 reserved1335;	//0xCC8E1A74
	UINT32                                                 reserved1336;	//0xCC8E1A78
	UINT32                                                 reserved1337;	//0xCC8E1A7C
	UINT32                                                 reserved1338;	//0xCC8E1A80
	UINT32                                                 reserved1339;	//0xCC8E1A84
	UINT32                                                 reserved1340;	//0xCC8E1A88
	UINT32                                                 reserved1341;	//0xCC8E1A8C
	UINT32                                                 reserved1342;	//0xCC8E1A90
	UINT32                                                 reserved1343;	//0xCC8E1A94
	UINT32                                                 reserved1344;	//0xCC8E1A98
	UINT32                                                 reserved1345;	//0xCC8E1A9C
	UINT32                                                 reserved1346;	//0xCC8E1AA0
	UINT32                                                 reserved1347;	//0xCC8E1AA4
	UINT32                                                 reserved1348;	//0xCC8E1AA8
	UINT32                                                 reserved1349;	//0xCC8E1AAC
	UINT32                                                 reserved1350;	//0xCC8E1AB0
	UINT32                                                 reserved1351;	//0xCC8E1AB4
	UINT32                                                 reserved1352;	//0xCC8E1AB8
	UINT32                                                 reserved1353;	//0xCC8E1ABC
	UINT32                                                 reserved1354;	//0xCC8E1AC0
	UINT32                                                 reserved1355;	//0xCC8E1AC4
	UINT32                                                 reserved1356;	//0xCC8E1AC8
	UINT32                                                 reserved1357;	//0xCC8E1ACC
	UINT32                                                 reserved1358;	//0xCC8E1AD0
	UINT32                                                 reserved1359;	//0xCC8E1AD4
	UINT32                                                 reserved1360;	//0xCC8E1AD8
	UINT32                                                 reserved1361;	//0xCC8E1ADC
	UINT32                                                 reserved1362;	//0xCC8E1AE0
	UINT32                                                 reserved1363;	//0xCC8E1AE4
	UINT32                                                 reserved1364;	//0xCC8E1AE8
	UINT32                                                 reserved1365;	//0xCC8E1AEC
	UINT32                                                 reserved1366;	//0xCC8E1AF0
	UINT32                                                 reserved1367;	//0xCC8E1AF4
	UINT32                                                 reserved1368;	//0xCC8E1AF8
	UINT32                                                 reserved1369;	//0xCC8E1AFC
	UINT32                                                 reserved1370;	//0xCC8E1B00
	UINT32                                                 reserved1371;	//0xCC8E1B04
	UINT32                                                 reserved1372;	//0xCC8E1B08
	UINT32                                                 reserved1373;	//0xCC8E1B0C
	UINT32                                                 reserved1374;	//0xCC8E1B10
	UINT32                                                 reserved1375;	//0xCC8E1B14
	UINT32                                                 reserved1376;	//0xCC8E1B18
	UINT32                                                 reserved1377;	//0xCC8E1B1C
	UINT32                                                 reserved1378;	//0xCC8E1B20
	UINT32                                                 reserved1379;	//0xCC8E1B24
	UINT32                                                 reserved1380;	//0xCC8E1B28
	UINT32                                                 reserved1381;	//0xCC8E1B2C
	UINT32                                                 reserved1382;	//0xCC8E1B30
	UINT32                                                 reserved1383;	//0xCC8E1B34
	UINT32                                                 reserved1384;	//0xCC8E1B38
	UINT32                                                 reserved1385;	//0xCC8E1B3C
	UINT32                                                 reserved1386;	//0xCC8E1B40
	UINT32                                                 reserved1387;	//0xCC8E1B44
	UINT32                                                 reserved1388;	//0xCC8E1B48
	UINT32                                                 reserved1389;	//0xCC8E1B4C
	UINT32                                                 reserved1390;	//0xCC8E1B50
	UINT32                                                 reserved1391;	//0xCC8E1B54
	UINT32                                                 reserved1392;	//0xCC8E1B58
	UINT32                                                 reserved1393;	//0xCC8E1B5C
	UINT32                                                 reserved1394;	//0xCC8E1B60
	UINT32                                                 reserved1395;	//0xCC8E1B64
	UINT32                                                 reserved1396;	//0xCC8E1B68
	UINT32                                                 reserved1397;	//0xCC8E1B6C
	UINT32                                                 reserved1398;	//0xCC8E1B70
	UINT32                                                 reserved1399;	//0xCC8E1B74
	UINT32                                                 reserved1400;	//0xCC8E1B78
	UINT32                                                 reserved1401;	//0xCC8E1B7C
	UINT32                                                 reserved1402;	//0xCC8E1B80
	UINT32                                                 reserved1403;	//0xCC8E1B84
	UINT32                                                 reserved1404;	//0xCC8E1B88
	UINT32                                                 reserved1405;	//0xCC8E1B8C
	UINT32                                                 reserved1406;	//0xCC8E1B90
	UINT32                                                 reserved1407;	//0xCC8E1B94
	UINT32                                                 reserved1408;	//0xCC8E1B98
	UINT32                                                 reserved1409;	//0xCC8E1B9C
	UINT32                                                 reserved1410;	//0xCC8E1BA0
	UINT32                                                 reserved1411;	//0xCC8E1BA4
	UINT32                                                 reserved1412;	//0xCC8E1BA8
	UINT32                                                 reserved1413;	//0xCC8E1BAC
	UINT32                                                 reserved1414;	//0xCC8E1BB0
	UINT32                                                 reserved1415;	//0xCC8E1BB4
	UINT32                                                 reserved1416;	//0xCC8E1BB8
	UINT32                                                 reserved1417;	//0xCC8E1BBC
	UINT32                                                 reserved1418;	//0xCC8E1BC0
	UINT32                                                 reserved1419;	//0xCC8E1BC4
	UINT32                                                 reserved1420;	//0xCC8E1BC8
	UINT32                                                 reserved1421;	//0xCC8E1BCC
	UINT32                                                 reserved1422;	//0xCC8E1BD0
	UINT32                                                 reserved1423;	//0xCC8E1BD4
	UINT32                                                 reserved1424;	//0xCC8E1BD8
	UINT32                                                 reserved1425;	//0xCC8E1BDC
	UINT32                                                 reserved1426;	//0xCC8E1BE0
	UINT32                                                 reserved1427;	//0xCC8E1BE4
	UINT32                                                 reserved1428;	//0xCC8E1BE8
	UINT32                                                 reserved1429;	//0xCC8E1BEC
	UINT32                                                 reserved1430;	//0xCC8E1BF0
	UINT32                                                 reserved1431;	//0xCC8E1BF4
	UINT32                                                 reserved1432;	//0xCC8E1BF8
	UINT32                                                 reserved1433;	//0xCC8E1BFC
	UINT32                                                 reserved1434;	//0xCC8E1C00
	UINT32                                                 reserved1435;	//0xCC8E1C04
	UINT32                                                 reserved1436;	//0xCC8E1C08
	UINT32                                                 reserved1437;	//0xCC8E1C0C
	UINT32                                                 reserved1438;	//0xCC8E1C10
	UINT32                                                 reserved1439;	//0xCC8E1C14
	UINT32                                                 reserved1440;	//0xCC8E1C18
	UINT32                                                 reserved1441;	//0xCC8E1C1C
	UINT32                                                 reserved1442;	//0xCC8E1C20
	UINT32                                                 reserved1443;	//0xCC8E1C24
	UINT32                                                 reserved1444;	//0xCC8E1C28
	UINT32                                                 reserved1445;	//0xCC8E1C2C
	UINT32                                                 reserved1446;	//0xCC8E1C30
	UINT32                                                 reserved1447;	//0xCC8E1C34
	UINT32                                                 reserved1448;	//0xCC8E1C38
	UINT32                                                 reserved1449;	//0xCC8E1C3C
	UINT32                                                 reserved1450;	//0xCC8E1C40
	UINT32                                                 reserved1451;	//0xCC8E1C44
	UINT32                                                 reserved1452;	//0xCC8E1C48
	UINT32                                                 reserved1453;	//0xCC8E1C4C
	UINT32                                                 reserved1454;	//0xCC8E1C50
	UINT32                                                 reserved1455;	//0xCC8E1C54
	UINT32                                                 reserved1456;	//0xCC8E1C58
	UINT32                                                 reserved1457;	//0xCC8E1C5C
	UINT32                                                 reserved1458;	//0xCC8E1C60
	UINT32                                                 reserved1459;	//0xCC8E1C64
	UINT32                                                 reserved1460;	//0xCC8E1C68
	UINT32                                                 reserved1461;	//0xCC8E1C6C
	UINT32                                                 reserved1462;	//0xCC8E1C70
	UINT32                                                 reserved1463;	//0xCC8E1C74
	UINT32                                                 reserved1464;	//0xCC8E1C78
	UINT32                                                 reserved1465;	//0xCC8E1C7C
	UINT32                                                 reserved1466;	//0xCC8E1C80
	UINT32                                                 reserved1467;	//0xCC8E1C84
	UINT32                                                 reserved1468;	//0xCC8E1C88
	UINT32                                                 reserved1469;	//0xCC8E1C8C
	UINT32                                                 reserved1470;	//0xCC8E1C90
	UINT32                                                 reserved1471;	//0xCC8E1C94
	UINT32                                                 reserved1472;	//0xCC8E1C98
	UINT32                                                 reserved1473;	//0xCC8E1C9C
	UINT32                                                 reserved1474;	//0xCC8E1CA0
	UINT32                                                 reserved1475;	//0xCC8E1CA4
	UINT32                                                 reserved1476;	//0xCC8E1CA8
	UINT32                                                 reserved1477;	//0xCC8E1CAC
	UINT32                                                 reserved1478;	//0xCC8E1CB0
	UINT32                                                 reserved1479;	//0xCC8E1CB4
	UINT32                                                 reserved1480;	//0xCC8E1CB8
	UINT32                                                 reserved1481;	//0xCC8E1CBC
	UINT32                                                 reserved1482;	//0xCC8E1CC0
	UINT32                                                 reserved1483;	//0xCC8E1CC4
	UINT32                                                 reserved1484;	//0xCC8E1CC8
	UINT32                                                 reserved1485;	//0xCC8E1CCC
	UINT32                                                 reserved1486;	//0xCC8E1CD0
	UINT32                                                 reserved1487;	//0xCC8E1CD4
	UINT32                                                 reserved1488;	//0xCC8E1CD8
	UINT32                                                 reserved1489;	//0xCC8E1CDC
	UINT32                                                 reserved1490;	//0xCC8E1CE0
	UINT32                                                 reserved1491;	//0xCC8E1CE4
	UINT32                                                 reserved1492;	//0xCC8E1CE8
	UINT32                                                 reserved1493;	//0xCC8E1CEC
	UINT32                                                 reserved1494;	//0xCC8E1CF0
	UINT32                                                 reserved1495;	//0xCC8E1CF4
	UINT32                                                 reserved1496;	//0xCC8E1CF8
	UINT32                                                 reserved1497;	//0xCC8E1CFC
	UINT32                                                 reserved1498;	//0xCC8E1D00
	UINT32                                                 reserved1499;	//0xCC8E1D04
	UINT32                                                 reserved1500;	//0xCC8E1D08
	UINT32                                                 reserved1501;	//0xCC8E1D0C
	UINT32                                                 reserved1502;	//0xCC8E1D10
	UINT32                                                 reserved1503;	//0xCC8E1D14
	UINT32                                                 reserved1504;	//0xCC8E1D18
	UINT32                                                 reserved1505;	//0xCC8E1D1C
	UINT32                                                 reserved1506;	//0xCC8E1D20
	UINT32                                                 reserved1507;	//0xCC8E1D24
	UINT32                                                 reserved1508;	//0xCC8E1D28
	UINT32                                                 reserved1509;	//0xCC8E1D2C
	UINT32                                                 reserved1510;	//0xCC8E1D30
	UINT32                                                 reserved1511;	//0xCC8E1D34
	UINT32                                                 reserved1512;	//0xCC8E1D38
	UINT32                                                 reserved1513;	//0xCC8E1D3C
	UINT32                                                 reserved1514;	//0xCC8E1D40
	UINT32                                                 reserved1515;	//0xCC8E1D44
	UINT32                                                 reserved1516;	//0xCC8E1D48
	UINT32                                                 reserved1517;	//0xCC8E1D4C
	UINT32                                                 reserved1518;	//0xCC8E1D50
	UINT32                                                 reserved1519;	//0xCC8E1D54
	UINT32                                                 reserved1520;	//0xCC8E1D58
	UINT32                                                 reserved1521;	//0xCC8E1D5C
	UINT32                                                 reserved1522;	//0xCC8E1D60
	UINT32                                                 reserved1523;	//0xCC8E1D64
	UINT32                                                 reserved1524;	//0xCC8E1D68
	UINT32                                                 reserved1525;	//0xCC8E1D6C
	UINT32                                                 reserved1526;	//0xCC8E1D70
	UINT32                                                 reserved1527;	//0xCC8E1D74
	UINT32                                                 reserved1528;	//0xCC8E1D78
	UINT32                                                 reserved1529;	//0xCC8E1D7C
	UINT32                                                 reserved1530;	//0xCC8E1D80
	UINT32                                                 reserved1531;	//0xCC8E1D84
	UINT32                                                 reserved1532;	//0xCC8E1D88
	UINT32                                                 reserved1533;	//0xCC8E1D8C
	UINT32                                                 reserved1534;	//0xCC8E1D90
	UINT32                                                 reserved1535;	//0xCC8E1D94
	UINT32                                                 reserved1536;	//0xCC8E1D98
	UINT32                                                 reserved1537;	//0xCC8E1D9C
	UINT32                                                 reserved1538;	//0xCC8E1DA0
	UINT32                                                 reserved1539;	//0xCC8E1DA4
	UINT32                                                 reserved1540;	//0xCC8E1DA8
	UINT32                                                 reserved1541;	//0xCC8E1DAC
	UINT32                                                 reserved1542;	//0xCC8E1DB0
	UINT32                                                 reserved1543;	//0xCC8E1DB4
	UINT32                                                 reserved1544;	//0xCC8E1DB8
	UINT32                                                 reserved1545;	//0xCC8E1DBC
	UINT32                                                 reserved1546;	//0xCC8E1DC0
	UINT32                                                 reserved1547;	//0xCC8E1DC4
	UINT32                                                 reserved1548;	//0xCC8E1DC8
	UINT32                                                 reserved1549;	//0xCC8E1DCC
	UINT32                                                 reserved1550;	//0xCC8E1DD0
	UINT32                                                 reserved1551;	//0xCC8E1DD4
	UINT32                                                 reserved1552;	//0xCC8E1DD8
	UINT32                                                 reserved1553;	//0xCC8E1DDC
	UINT32                                                 reserved1554;	//0xCC8E1DE0
	UINT32                                                 reserved1555;	//0xCC8E1DE4
	UINT32                                                 reserved1556;	//0xCC8E1DE8
	UINT32                                                 reserved1557;	//0xCC8E1DEC
	UINT32                                                 reserved1558;	//0xCC8E1DF0
	UINT32                                                 reserved1559;	//0xCC8E1DF4
	UINT32                                                 reserved1560;	//0xCC8E1DF8
	UINT32                                                 reserved1561;	//0xCC8E1DFC
	UINT32                                                 reserved1562;	//0xCC8E1E00
	UINT32                                                 reserved1563;	//0xCC8E1E04
	UINT32                                                 reserved1564;	//0xCC8E1E08
	UINT32                                                 reserved1565;	//0xCC8E1E0C
	UINT32                                                 reserved1566;	//0xCC8E1E10
	UINT32                                                 reserved1567;	//0xCC8E1E14
	UINT32                                                 reserved1568;	//0xCC8E1E18
	UINT32                                                 reserved1569;	//0xCC8E1E1C
	UINT32                                                 reserved1570;	//0xCC8E1E20
	UINT32                                                 reserved1571;	//0xCC8E1E24
	UINT32                                                 reserved1572;	//0xCC8E1E28
	UINT32                                                 reserved1573;	//0xCC8E1E2C
	UINT32                                                 reserved1574;	//0xCC8E1E30
	UINT32                                                 reserved1575;	//0xCC8E1E34
	UINT32                                                 reserved1576;	//0xCC8E1E38
	UINT32                                                 reserved1577;	//0xCC8E1E3C
	UINT32                                                 reserved1578;	//0xCC8E1E40
	UINT32                                                 reserved1579;	//0xCC8E1E44
	UINT32                                                 reserved1580;	//0xCC8E1E48
	UINT32                                                 reserved1581;	//0xCC8E1E4C
	UINT32                                                 reserved1582;	//0xCC8E1E50
	UINT32                                                 reserved1583;	//0xCC8E1E54
	UINT32                                                 reserved1584;	//0xCC8E1E58
	UINT32                                                 reserved1585;	//0xCC8E1E5C
	UINT32                                                 reserved1586;	//0xCC8E1E60
	UINT32                                                 reserved1587;	//0xCC8E1E64
	UINT32                                                 reserved1588;	//0xCC8E1E68
	UINT32                                                 reserved1589;	//0xCC8E1E6C
	UINT32                                                 reserved1590;	//0xCC8E1E70
	UINT32                                                 reserved1591;	//0xCC8E1E74
	UINT32                                                 reserved1592;	//0xCC8E1E78
	UINT32                                                 reserved1593;	//0xCC8E1E7C
	UINT32                                                 reserved1594;	//0xCC8E1E80
	UINT32                                                 reserved1595;	//0xCC8E1E84
	UINT32                                                 reserved1596;	//0xCC8E1E88
	UINT32                                                 reserved1597;	//0xCC8E1E8C
	UINT32                                                 reserved1598;	//0xCC8E1E90
	UINT32                                                 reserved1599;	//0xCC8E1E94
	UINT32                                                 reserved1600;	//0xCC8E1E98
	UINT32                                                 reserved1601;	//0xCC8E1E9C
	UINT32                                                 reserved1602;	//0xCC8E1EA0
	UINT32                                                 reserved1603;	//0xCC8E1EA4
	UINT32                                                 reserved1604;	//0xCC8E1EA8
	UINT32                                                 reserved1605;	//0xCC8E1EAC
	UINT32                                                 reserved1606;	//0xCC8E1EB0
	UINT32                                                 reserved1607;	//0xCC8E1EB4
	UINT32                                                 reserved1608;	//0xCC8E1EB8
	UINT32                                                 reserved1609;	//0xCC8E1EBC
	UINT32                                                 reserved1610;	//0xCC8E1EC0
	UINT32                                                 reserved1611;	//0xCC8E1EC4
	UINT32                                                 reserved1612;	//0xCC8E1EC8
	UINT32                                                 reserved1613;	//0xCC8E1ECC
	UINT32                                                 reserved1614;	//0xCC8E1ED0
	UINT32                                                 reserved1615;	//0xCC8E1ED4
	UINT32                                                 reserved1616;	//0xCC8E1ED8
	UINT32                                                 reserved1617;	//0xCC8E1EDC
	UINT32                                                 reserved1618;	//0xCC8E1EE0
	UINT32                                                 reserved1619;	//0xCC8E1EE4
	UINT32                                                 reserved1620;	//0xCC8E1EE8
	UINT32                                                 reserved1621;	//0xCC8E1EEC
	UINT32                                                 reserved1622;	//0xCC8E1EF0
	UINT32                                                 reserved1623;	//0xCC8E1EF4
	UINT32                                                 reserved1624;	//0xCC8E1EF8
	UINT32                                                 reserved1625;	//0xCC8E1EFC
	UINT32                                                 reserved1626;	//0xCC8E1F00
	UINT32                                                 reserved1627;	//0xCC8E1F04
	UINT32                                                 reserved1628;	//0xCC8E1F08
	UINT32                                                 reserved1629;	//0xCC8E1F0C
	UINT32                                                 reserved1630;	//0xCC8E1F10
	UINT32                                                 reserved1631;	//0xCC8E1F14
	UINT32                                                 reserved1632;	//0xCC8E1F18
	UINT32                                                 reserved1633;	//0xCC8E1F1C
	UINT32                                                 reserved1634;	//0xCC8E1F20
	UINT32                                                 reserved1635;	//0xCC8E1F24
	UINT32                                                 reserved1636;	//0xCC8E1F28
	UINT32                                                 reserved1637;	//0xCC8E1F2C
	UINT32                                                 reserved1638;	//0xCC8E1F30
	UINT32                                                 reserved1639;	//0xCC8E1F34
	UINT32                                                 reserved1640;	//0xCC8E1F38
	UINT32                                                 reserved1641;	//0xCC8E1F3C
	UINT32                                                 reserved1642;	//0xCC8E1F40
	UINT32                                                 reserved1643;	//0xCC8E1F44
	UINT32                                                 reserved1644;	//0xCC8E1F48
	UINT32                                                 reserved1645;	//0xCC8E1F4C
	UINT32                                                 reserved1646;	//0xCC8E1F50
	UINT32                                                 reserved1647;	//0xCC8E1F54
	UINT32                                                 reserved1648;	//0xCC8E1F58
	UINT32                                                 reserved1649;	//0xCC8E1F5C
	UINT32                                                 reserved1650;	//0xCC8E1F60
	UINT32                                                 reserved1651;	//0xCC8E1F64
	UINT32                                                 reserved1652;	//0xCC8E1F68
	UINT32                                                 reserved1653;	//0xCC8E1F6C
	UINT32                                                 reserved1654;	//0xCC8E1F70
	UINT32                                                 reserved1655;	//0xCC8E1F74
	UINT32                                                 reserved1656;	//0xCC8E1F78
	UINT32                                                 reserved1657;	//0xCC8E1F7C
	UINT32                                                 reserved1658;	//0xCC8E1F80
	UINT32                                                 reserved1659;	//0xCC8E1F84
	UINT32                                                 reserved1660;	//0xCC8E1F88
	UINT32                                                 reserved1661;	//0xCC8E1F8C
	UINT32                                                 reserved1662;	//0xCC8E1F90
	UINT32                                                 reserved1663;	//0xCC8E1F94
	UINT32                                                 reserved1664;	//0xCC8E1F98
	UINT32                                                 reserved1665;	//0xCC8E1F9C
	UINT32                                                 reserved1666;	//0xCC8E1FA0
	UINT32                                                 reserved1667;	//0xCC8E1FA4
	UINT32                                                 reserved1668;	//0xCC8E1FA8
	UINT32                                                 reserved1669;	//0xCC8E1FAC
	UINT32                                                 reserved1670;	//0xCC8E1FB0
	UINT32                                                 reserved1671;	//0xCC8E1FB4
	UINT32                                                 reserved1672;	//0xCC8E1FB8
	UINT32                                                 reserved1673;	//0xCC8E1FBC
	UINT32                                                 reserved1674;	//0xCC8E1FC0
	UINT32                                                 reserved1675;	//0xCC8E1FC4
	UINT32                                                 reserved1676;	//0xCC8E1FC8
	UINT32                                                 reserved1677;	//0xCC8E1FCC
	UINT32                                                 reserved1678;	//0xCC8E1FD0
	UINT32                                                 reserved1679;	//0xCC8E1FD4
	UINT32                                                 reserved1680;	//0xCC8E1FD8
	UINT32                                                 reserved1681;	//0xCC8E1FDC
	UINT32                                                 reserved1682;	//0xCC8E1FE0
	UINT32                                                 reserved1683;	//0xCC8E1FE4
	UINT32                                                 reserved1684;	//0xCC8E1FE8
	UINT32                                                 reserved1685;	//0xCC8E1FEC
	UINT32                                                 reserved1686;	//0xCC8E1FF0
	UINT32                                                 reserved1687;	//0xCC8E1FF4
	UINT32                                                 reserved1688;	//0xCC8E1FF8
	UINT32                                                 reserved1689;	//0xCC8E1FFC
	O24A0_LED_BLU_BLK_NUM_HV_T                       ad_blu_blk_num_hv;	//0xCC8E2000
	O24A0_LED_VS_MODE_T                                     ad_vs_mode;	//0xCC8E2004
	O24A0_LED_BLU_VS_NUM_T                               ad_blu_vs_num;	//0xCC8E2008
	O24A0_LED_BLU_VS_T0_T                                 ad_blu_vs_t0;	//0xCC8E200C
	O24A0_LED_VS_DLY_T                                       ad_vs_dly;	//0xCC8E2010
	O24A0_LED_I2C_SLAVE_ADDR_T                       ad_i2c_slave_addr;	//0xCC8E2014
	O24A0_LED_I2C_CONF_T                                   ad_i2c_conf;	//0xCC8E2018
	O24A0_LED_VERSION_T                                     ad_version;	//0xCC8E201C
	O24A0_LED_GENERAL_REG0_T                           ad_general_reg0;	//0xCC8E2020
	O24A0_LED_GENERAL_REG1_T                           ad_general_reg1;	//0xCC8E2024
	O24A0_LED_GENERAL_REG2_T                           ad_general_reg2;	//0xCC8E2028
	O24A0_LED_GENERAL_REG3_T                           ad_general_reg3;	//0xCC8E202C
	O24A0_LED_CG_CTRL_T                                     ad_cg_ctrl;	//0xCC8E2030
	UINT32                                                 reserved1690;	//0xCC8E2034
	UINT32                                                 reserved1691;	//0xCC8E2038
	UINT32                                                 reserved1692;	//0xCC8E203C
	O24A0_LED_I2C_RD_ON_T                                 ad_i2c_rd_on;	//0xCC8E2040
	O24A0_LED_I2C_RD_ADDR_T                             ad_i2c_rd_addr;	//0xCC8E2044
	O24A0_LED_I2C_RD_DATA_T                             ad_i2c_rd_data;	//0xCC8E2048
	O24A0_LED_BLU_VS1_T0_T                               ad_blu_vs1_t0;	//0xCC8E204C
	O24A0_LED_VS1_DLY_T                                     ad_vs1_dly;	//0xCC8E2050
	O24A0_LED_BLU_VS2_T0_T                               ad_blu_vs2_t0;	//0xCC8E2054
	O24A0_LED_VS2_DLY_T                                     ad_vs2_dly;	//0xCC8E2058
	O24A0_LED_BLU_VS3_T0_T                               ad_blu_vs3_t0;	//0xCC8E205C
	O24A0_LED_VS3_DLY_T                                     ad_vs3_dly;	//0xCC8E2060
	UINT32                                                 reserved1693;	//0xCC8E2064
	UINT32                                                 reserved1694;	//0xCC8E2068
	UINT32                                                 reserved1695;	//0xCC8E206C
	UINT32                                                 reserved1696;	//0xCC8E2070
	UINT32                                                 reserved1697;	//0xCC8E2074
	UINT32                                                 reserved1698;	//0xCC8E2078
	UINT32                                                 reserved1699;	//0xCC8E207C
	O24A0_LED_SPI_CFG0_T                                   ad_spi_cfg0;	//0xCC8E2080
	O24A0_LED_SPI_CMD_MODE_T                           ad_spi_cmd_mode;	//0xCC8E2084
	O24A0_LED_M_SPI_CH_MASK_T                         ad_m_spi_ch_mask;	//0xCC8E2088
	O24A0_LED_SPI_IDC01_T                                 ad_spi_idc01;	//0xCC8E208C
	O24A0_LED_SPI_IDC23_T                                 ad_spi_idc23;	//0xCC8E2090
	O24A0_LED_SPI_CMD01_T                                 ad_spi_cmd01;	//0xCC8E2094
	O24A0_LED_SPI_CMD23_T                                 ad_spi_cmd23;	//0xCC8E2098
	O24A0_LED_SCLK_T1_T                                     ad_sclk_t1;	//0xCC8E209C
	O24A0_LED_SCLK_T2_T                                     ad_sclk_t2;	//0xCC8E20A0
	O24A0_LED_SCLK_T3_T                                     ad_sclk_t3;	//0xCC8E20A4
	O24A0_LED_SCLK_T4_T                                     ad_sclk_t4;	//0xCC8E20A8
	O24A0_LED_SCLK_T5_T                                     ad_sclk_t5;	//0xCC8E20AC
	O24A0_LED_SPI_CMD45_T                                 ad_spi_cmd45;	//0xCC8E20B0
	UINT32                                                 reserved1700;	//0xCC8E20B4
	UINT32                                                 reserved1701;	//0xCC8E20B8
	UINT32                                                 reserved1702;	//0xCC8E20BC
	O24A0_LED_BLK_SP0_T                                     ad_blk_sp0;	//0xCC8E20C0
	O24A0_LED_BLK_SP1_T                                     ad_blk_sp1;	//0xCC8E20C4
	O24A0_LED_BLK_SP2_T                                     ad_blk_sp2;	//0xCC8E20C8
	O24A0_LED_BLK_SP3_T                                     ad_blk_sp3;	//0xCC8E20CC
	O24A0_LED_BNH_SEG0_T                                   ad_bnh_seg0;	//0xCC8E20D0
	O24A0_LED_BNH_SEG1_T                                   ad_bnh_seg1;	//0xCC8E20D4
	O24A0_LED_BNH_SEG2_T                                   ad_bnh_seg2;	//0xCC8E20D8
	O24A0_LED_BNH_SEG3_T                                   ad_bnh_seg3;	//0xCC8E20DC
	O24A0_LED_BNV_SEG0_T                                   ad_bnv_seg0;	//0xCC8E20E0
	O24A0_LED_BNV_SEG1_T                                   ad_bnv_seg1;	//0xCC8E20E4
	O24A0_LED_BNV_SEG2_T                                   ad_bnv_seg2;	//0xCC8E20E8
	O24A0_LED_BNV_SEG3_T                                   ad_bnv_seg3;	//0xCC8E20EC
	UINT32                                                 reserved1703;	//0xCC8E20F0
	UINT32                                                 reserved1704;	//0xCC8E20F4
	UINT32                                                 reserved1705;	//0xCC8E20F8
	UINT32                                                 reserved1706;	//0xCC8E20FC
	O24A0_LED_PWM_VALUE_T                                 ad_pwm_value;	//0xCC8E2100
	O24A0_LED_BLU_MAXVAL_EN_T                         ad_blu_maxval_en;	//0xCC8E2104
	O24A0_LED_SPI_ALEF2_EN_T                           ad_spi_alef2_en;	//0xCC8E2108
	O24A0_LED_SPI_ALEF2_CLR_T                         ad_spi_alef2_clr;	//0xCC8E210C
	O24A0_LED_SPI0_ALEF2_LUT_T                       ad_spi0_alef2_lut;	//0xCC8E2110
	O24A0_LED_SPI0_ALEF2_LUT_RD_T                 ad_spi0_alef2_lut_rd;	//0xCC8E2114
	O24A0_LED_SPI1_ALEF2_LUT_T                       ad_spi1_alef2_lut;	//0xCC8E2118
	O24A0_LED_SPI1_ALEF2_LUT_RD_T                 ad_spi1_alef2_lut_rd;	//0xCC8E211C
	O24A0_LED_SPI2_ALEF2_LUT_T                       ad_spi2_alef2_lut;	//0xCC8E2120
	O24A0_LED_SPI2_ALEF2_LUT_RD_T                 ad_spi2_alef2_lut_rd;	//0xCC8E2124
	O24A0_LED_SPI3_ALEF2_LUT_T                       ad_spi3_alef2_lut;	//0xCC8E2128
	O24A0_LED_SPI3_ALEF2_LUT_RD_T                 ad_spi3_alef2_lut_rd;	//0xCC8E212C
	UINT32                                                 reserved1707;	//0xCC8E2130
	UINT32                                                 reserved1708;	//0xCC8E2134
	UINT32                                                 reserved1709;	//0xCC8E2138
	UINT32                                                 reserved1710;	//0xCC8E213C
	O24A0_LED_EXT_INT_EN_T                               ad_ext_int_en;	//0xCC8E2140
	O24A0_LED_EXT_INT_STATUS_T                       ad_ext_int_status;	//0xCC8E2144
	O24A0_LED_EXT_INT_RAW_STATUS_T               ad_ext_int_raw_status;	//0xCC8E2148
	O24A0_LED_EXT_INT_CLR_T                             ad_ext_int_clr;	//0xCC8E214C
	O24A0_LED_EXT_INT_LINE_NUM_T                   ad_ext_int_line_num;	//0xCC8E2150
	UINT32                                                 reserved1711;	//0xCC8E2154
	UINT32                                                 reserved1712;	//0xCC8E2158
	UINT32                                                 reserved1713;	//0xCC8E215C
	UINT32                                                 reserved1714;	//0xCC8E2160
	UINT32                                                 reserved1715;	//0xCC8E2164
	UINT32                                                 reserved1716;	//0xCC8E2168
	UINT32                                                 reserved1717;	//0xCC8E216C
	UINT32                                                 reserved1718;	//0xCC8E2170
	UINT32                                                 reserved1719;	//0xCC8E2174
	UINT32                                                 reserved1720;	//0xCC8E2178
	UINT32                                                 reserved1721;	//0xCC8E217C
	UINT32                                                 reserved1722;	//0xCC8E2180
	UINT32                                                 reserved1723;	//0xCC8E2184
	UINT32                                                 reserved1724;	//0xCC8E2188
	UINT32                                                 reserved1725;	//0xCC8E218C
	UINT32                                                 reserved1726;	//0xCC8E2190
	UINT32                                                 reserved1727;	//0xCC8E2194
	UINT32                                                 reserved1728;	//0xCC8E2198
	UINT32                                                 reserved1729;	//0xCC8E219C
	UINT32                                                 reserved1730;	//0xCC8E21A0
	UINT32                                                 reserved1731;	//0xCC8E21A4
	UINT32                                                 reserved1732;	//0xCC8E21A8
	UINT32                                                 reserved1733;	//0xCC8E21AC
	UINT32                                                 reserved1734;	//0xCC8E21B0
	UINT32                                                 reserved1735;	//0xCC8E21B4
	UINT32                                                 reserved1736;	//0xCC8E21B8
	UINT32                                                 reserved1737;	//0xCC8E21BC
	UINT32                                                 reserved1738;	//0xCC8E21C0
	UINT32                                                 reserved1739;	//0xCC8E21C4
	UINT32                                                 reserved1740;	//0xCC8E21C8
	UINT32                                                 reserved1741;	//0xCC8E21CC
	UINT32                                                 reserved1742;	//0xCC8E21D0
	UINT32                                                 reserved1743;	//0xCC8E21D4
	UINT32                                                 reserved1744;	//0xCC8E21D8
	UINT32                                                 reserved1745;	//0xCC8E21DC
	UINT32                                                 reserved1746;	//0xCC8E21E0
	UINT32                                                 reserved1747;	//0xCC8E21E4
	UINT32                                                 reserved1748;	//0xCC8E21E8
	UINT32                                                 reserved1749;	//0xCC8E21EC
	UINT32                                                 reserved1750;	//0xCC8E21F0
	UINT32                                                 reserved1751;	//0xCC8E21F4
	UINT32                                                 reserved1752;	//0xCC8E21F8
	UINT32                                                 reserved1753;	//0xCC8E21FC
	UINT32                                                 reserved1754;	//0xCC8E2200
	UINT32                                                 reserved1755;	//0xCC8E2204
	UINT32                                                 reserved1756;	//0xCC8E2208
	UINT32                                                 reserved1757;	//0xCC8E220C
	UINT32                                                 reserved1758;	//0xCC8E2210
	UINT32                                                 reserved1759;	//0xCC8E2214
	UINT32                                                 reserved1760;	//0xCC8E2218
	UINT32                                                 reserved1761;	//0xCC8E221C
	O24A0_LED_VS_SEL_T                                       ad_vs_sel;	//0xCC8E2220
	UINT32                                                 reserved1762;	//0xCC8E2224
	UINT32                                                 reserved1763;	//0xCC8E2228
	UINT32                                                 reserved1764;	//0xCC8E222C
	UINT32                                                 reserved1765;	//0xCC8E2230
	UINT32                                                 reserved1766;	//0xCC8E2234
	UINT32                                                 reserved1767;	//0xCC8E2238
	UINT32                                                 reserved1768;	//0xCC8E223C
	O24A0_LED_ABI_BFI0_T                                   ad_abi_bfi0;	//0xCC8E2240
	O24A0_LED_ABI_BFI1_T                                   ad_abi_bfi1;	//0xCC8E2244
	O24A0_LED_ABI_BFI2_T                                   ad_abi_bfi2;	//0xCC8E2248
	O24A0_LED_ABI_BFI3_T                                   ad_abi_bfi3;	//0xCC8E224C
	UINT32                                                 reserved1769;	//0xCC8E2250
	UINT32                                                 reserved1770;	//0xCC8E2254
	UINT32                                                 reserved1771;	//0xCC8E2258
	UINT32                                                 reserved1772;	//0xCC8E225C
	UINT32                                                 reserved1773;	//0xCC8E2260
	UINT32                                                 reserved1774;	//0xCC8E2264
	UINT32                                                 reserved1775;	//0xCC8E2268
	UINT32                                                 reserved1776;	//0xCC8E226C
	UINT32                                                 reserved1777;	//0xCC8E2270
	UINT32                                                 reserved1778;	//0xCC8E2274
	UINT32                                                 reserved1779;	//0xCC8E2278
	UINT32                                                 reserved1780;	//0xCC8E227C
	O24A0_LED_12BIT_00_T                                   ad_12bit_00;	//0xCC8E2280
	O24A0_LED_12BIT_01_T                                   ad_12bit_01;	//0xCC8E2284
	O24A0_LED_12BIT_02_T                                   ad_12bit_02;	//0xCC8E2288
	O24A0_LED_12BIT_03_T                                   ad_12bit_03;	//0xCC8E228C
	O24A0_LED_12BIT_04_T                                   ad_12bit_04;	//0xCC8E2290
	O24A0_LED_12BIT_05_T                                   ad_12bit_05;	//0xCC8E2294
	O24A0_LED_12BIT_06_T                                   ad_12bit_06;	//0xCC8E2298
	O24A0_LED_12BIT_07_T                                   ad_12bit_07;	//0xCC8E229C
	O24A0_LED_12BIT_08_T                                   ad_12bit_08;	//0xCC8E22A0
	O24A0_LED_12BIT_09_T                                   ad_12bit_09;	//0xCC8E22A4
	O24A0_LED_12BIT_10_T                                   ad_12bit_10;	//0xCC8E22A8
	O24A0_LED_12BIT_11_T                                   ad_12bit_11;	//0xCC8E22AC
	O24A0_LED_12BIT_12_T                                   ad_12bit_12;	//0xCC8E22B0
	O24A0_LED_12BIT_13_T                                   ad_12bit_13;	//0xCC8E22B4
	O24A0_LED_12BIT_14_T                                   ad_12bit_14;	//0xCC8E22B8
	O24A0_LED_12BIT_15_T                                   ad_12bit_15;	//0xCC8E22BC
	O24A0_LED_12BIT_16_T                                   ad_12bit_16;	//0xCC8E22C0
	O24A0_LED_12BIT_17_T                                   ad_12bit_17;	//0xCC8E22C4
	O24A0_LED_12BIT_18_T                                   ad_12bit_18;	//0xCC8E22C8
	O24A0_LED_BLU_IF_DB_MEM_PAGE_T               ad_blu_if_db_mem_page;	//0xCC8E22CC
	O24A0_LED_BLU_IF_SHIFT_16_T                     ad_blu_if_shift_16;	//0xCC8E22D0
	O24A0_LED_I2C_RD_AI_ADDR_CLR_T               ad_i2c_rd_ai_addr_clr;	//0xCC8E22D4
	O24A0_LED_I2C_RD_AI_ADDR_T                       ad_i2c_rd_ai_addr;	//0xCC8E22D8
	O24A0_LED_I2C_RD_MODE_SEL_T                     ad_i2c_rd_mode_sel;	//0xCC8E22DC
}DPE_LED_REG_O24A0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3000 RW 0x0000_0030
	UINT32 resvd0                           :4;
	UINT32 reg_init_sel                     :3;	//(6:4,RW,0x3) //0:vs_rising, 1:vs_falling, 2:va_rising, 3:va_falling, others:manual position from va_falling
	UINT32 resvd1                           :1;
	UINT32 reg_use_delayed_sync             :1;	//(8,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 resvd2                           :7;
	UINT32 reg_manual_init_pos              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3004 RW 0x0000_1000
	UINT32 reg_oled_phdr_cg_on              :1;	//(0,RW,0x0) //postHDR clock gating enable
	UINT32 resvd0                           :3;
	UINT32 reg_oled_decon_cg_on             :1;	//(4,RW,0x0) //RGB2YC, Decontour, YC2RGB clock gating enable
	UINT32 resvd1                           :3;
	UINT32 reg_oled_others_cg_on            :1;	//(8,RW,0x0) //OLED APL, CPC clock gating enable
	UINT32 resvd2                           :3;
	UINT32 reg_phdr_mem_sel                 :1;	//(12,RW,0x1) //shared mem use 0:boundary use 1:posthdr use
	UINT32 resvd3                           :19;
	};
}O24A0_OLED_OLED_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3008 RW 0x0000_0030
	UINT32 reg_oapl_input_sel               :1;	//(0,RW,0x0) //0: cpc input, 1: cpc output
	UINT32 reg_oapl_led_input_use           :1;	//(1,RW,0x0) //0: oled input, 1: led input
	UINT32 resvd0                           :2;
	UINT32 reg_oapl_init_sel                :3;	//(6:4,RW,0x3) //0:out_vs_rising, 1:out_vs_falling, 2:out_va_rising, 3:out_va_falling, others:manual position from out_va_falling
	UINT32 resvd1                           :9;
	UINT32 reg_oapl_manual_init_pos         :16;	//(31:16,RW,0x0) //OLED APL, CPC clock gating enable
	};
}O24A0_OLED_OLED_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3010 RW 0x0000_0000
	UINT32 reg_oled_11bit_wr_done           :1;		//0:0	
	UINT32 tdata0                     		:31;	//31:1
	};
}O24A0_OLED_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3014 RW 0x0000_0000
	UINT32 reg_osd_gain                     :8;	  //7:0
	UINT32 resvd0                           :23;  //30:8
	UINT32 reg_osd_gain_en                  :1;	  //31	
	};
}O24A0_OLED_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3018 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E301C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3020 RW 0x0000_7F04
	UINT32 reg_cpc_en                       :1;	//(0,RW,0x0) //
	UINT32 reg_debug_mode_en                :1;	//(1,RW,0x0) //
	UINT32 reg_elps_lut_en                  :1;	//(2,RW,0x1) //ellipse gain lut enable
	UINT32 resvd0                           :1;
	UINT32 reg_cpc_debug_mode               :2;	//(5:4,RW,0x0) //0:final alpha, 1:ellipse gain, 2: vertex gain, 3:osd alpha
	UINT32 resvd1                           :2;
	UINT32 reg_cpc_master_gain              :8;	//(15:8,RW,0x7F) //min:0 ~ max:2.0(0x80 = 1.0)
	UINT32 resvd2                           :16;
	};
}O24A0_OLED_CPC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3024 RW 0x0F00_0870
	UINT32 reg_disp_height                  :12;	//(11:0,RW,0x870) //displya height
	UINT32 resvd0                           :4;
	UINT32 reg_disp_width                   :12;	//(27:16,RW,0xF00) //display width(not channel image size)
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_CPC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3028 RW 0x0B40_0654
	UINT32 reg_ellipse_b                    :12;	//(11:0,RW,0x654) //
	UINT32 reg_shift_y                      :2;	//(13:12,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_ellipse_a                    :12;	//(27:16,RW,0xB40) //
	UINT32 reg_shift_x                      :2;	//(29:28,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}O24A0_OLED_CPC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E302C RW 0x0200_0200
	UINT32 reg_vrtx_gain_tr                 :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_vrtx_gain_tl                 :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3030 RW 0x03FF_03FF
	UINT32 reg_vrtx_gain_br                 :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_vrtx_gain_bl                 :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3034 RW 0x0064_0000
	UINT32 reg_elps_y0                      :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x0                      :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3038 RW 0x00C8_0040
	UINT32 reg_elps_y1                      :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x1                      :10;	//(25:16,RW,0xC8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E303C RW 0x012C_0096
	UINT32 reg_elps_y2                      :10;	//(9:0,RW,0x96) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x2                      :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3040 RW 0x0190_015E
	UINT32 reg_elps_y3                      :10;	//(9:0,RW,0x15E) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x3                      :10;	//(25:16,RW,0x190) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3044 RW 0x0258_0226
	UINT32 reg_elps_y4                      :10;	//(9:0,RW,0x226) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x4                      :10;	//(25:16,RW,0x258) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3048 RW 0x02BC_0280
	UINT32 reg_elps_y5                      :10;	//(9:0,RW,0x280) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x5                      :10;	//(25:16,RW,0x2BC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E304C RW 0x0320_02BC
	UINT32 reg_elps_y6                      :10;	//(9:0,RW,0x2BC) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x6                      :10;	//(25:16,RW,0x320) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3050 RW 0x03FF_02EE
	UINT32 reg_elps_y7                      :10;	//(9:0,RW,0x2EE) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x7                      :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3054 RW 0x0080_ACFF
	UINT32 reg_osd_x3                       :8;	//(7:0,RW,0xff) //
	UINT32 reg_osd_x2                       :8;	//(15:8,RW,0xac) //
	UINT32 reg_osd_x1                       :8;	//(23:16,RW,0x80) //
	UINT32 reg_osd_x0                       :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_CPC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3058 RW 0xFF00_0000
	UINT32 reg_osd_y3                       :8;	//(7:0,RW,0x0) //
	UINT32 reg_osd_y2                       :8;	//(15:8,RW,0x0) //
	UINT32 reg_osd_y1                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_osd_y0                       :8;	//(31:24,RW,0xff) //
	};
}O24A0_OLED_CPC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E305C RW 0x0064_003C
	UINT32 reg_cpc_y0                       :10;	//(9:0,RW,0x3c) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x0                       :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3060 RW 0x00C8_0078
	UINT32 reg_cpc_y1                       :10;	//(9:0,RW,0x78) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x1                       :10;	//(25:16,RW,0xC8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3064 RW 0x012C_00B4
	UINT32 reg_cpc_y2                       :10;	//(9:0,RW,0xb4) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x2                       :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3068 RW 0x0190_00F0
	UINT32 reg_cpc_y3                       :10;	//(9:0,RW,0xf0) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x3                       :10;	//(25:16,RW,0x190) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E306C RW 0x0258_0168
	UINT32 reg_cpc_y4                       :10;	//(9:0,RW,0x168) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x4                       :10;	//(25:16,RW,0x258) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3070 RW 0x02BC_01A4
	UINT32 reg_cpc_y5                       :10;	//(9:0,RW,0x1a4) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x5                       :10;	//(25:16,RW,0x2BC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3074 RW 0x0320_01E0
	UINT32 reg_cpc_y6                       :10;	//(9:0,RW,0x1e0) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x6                       :10;	//(25:16,RW,0x320) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3078 RW 0x03FF_0258
	UINT32 reg_cpc_y7                       :10;	//(9:0,RW,0x258) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x7                       :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_CPC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3080 RW 0x0870_0F00
	UINT32 reg_wid                          :16;	//(15:0,RW,0xF00) //display width(not channel image size)
	UINT32 reg_hei                          :16;	//(31:16,RW,0x870) //displya height
	};
}O24A0_OLED_PHDR_CTRL_000_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3084 RW 0x0000_0000
	UINT32 reg_init_sel                     :3;	//(2:0,RW,0x0) //
	UINT32 resvd                            :13;
	UINT32 reg_manual_init_pos              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3088 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E308C RW 0x0000_0001
	UINT32 reg_tcm_inp_sel                  :1;	//(0,RW,0x1) //0:Y, 1:V
	UINT32 resvd0                           :1;
	UINT32 reg_l_gain_sel                   :2;	//(3:2,RW,0x0) //0:l_gain 1:max 2:sum 3:obj
	UINT32 reg_illuminant_map_sel           :1;	//(4,RW,0x0) //1:illuminant_map selected
	UINT32 resvd1                           :27;
	};
}O24A0_OLED_PHDR_CTRL_003_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3090 RW 0x17B0_6680
	UINT32 reg_bst_gain_type_sel            :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_bst_gain_shift               :4;	//(7:4,RW,0x8) //
	UINT32 reg_bst_max_ratio                :10;	//(17:8,RW,0x66) //
	UINT32 resvd1                           :2;
	UINT32 reg_bst_max_value                :10;	//(29:20,RW,0x17B) //
	UINT32 resvd2                           :2;
	};
}O24A0_OLED_PHDR_CTRL_004_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3094 RW 0x4000_8011
	UINT32 reg_bst_osd_on                   :1;	//(0,RW,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_bst_lsr_on                   :1;	//(4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_bst_master_gain              :8;	//(15:8,RW,0x80) //
	UINT32 resvd2                           :12;
	UINT32 reg_bst_out_sel                  :4;	//(31:28,RW,0x4) //0: enable, 1:l_gain, 2:s_gain, 3:g_gain, 4:disable, 5:osd_gain, 6:lsr_gain
	};
}O24A0_OLED_PHDR_CTRL_005_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3098 RW 0x0000_0000
	UINT32 reg_apl_run_mode                 :1;	//(0,RW,0x0) //0:from apl g/l gain lut, 1:from force gain
	UINT32 resvd                            :15;
	UINT32 reg_apl_force_g_gain             :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_force_l_gain             :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_006_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E309C RW 0x0000_0001
	UINT32 reg_use_blank_period_cnt         :1;	//(0,RW,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_use_extern_valid             :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :11;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_007_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30A0 RW 0x8080_8010
	UINT32 reg_sat_sel                      :1;	//(0,RW,0x0) //0:(max-min)/max, 1:max-min
	UINT32 resvd0                           :3;
	UINT32 reg_hsv_hsl_sel                  :1;	//(4,RW,0x1) //0:HSL, 1:HSV
	UINT32 resvd1                           :3;
	UINT32 reg_ihsv_sgain                   :8;	//(15:8,RW,0x80) //
	UINT32 reg_ihsv_soffset                 :8;	//(23:16,RW,0x80) //
	UINT32 reg_ihsv_hoffset                 :8;	//(31:24,RW,0x80) //
	};
}O24A0_OLED_PHDR_CTRL_008_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30A4 RW 0x0000_8080
	UINT32 reg_ihsv_vgain                   :8;	//(7:0,RW,0x80) //
	UINT32 reg_ihsv_voffset                 :8;	//(15:8,RW,0x80) //
	UINT32 resvd                            :16;
	};
}O24A0_OLED_PHDR_CTRL_009_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30A8 RW 0x03FF_0360
	UINT32 reg_s_lut_x6                     :10;	//(9:0,RW,0x360) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x7                     :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_010_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30AC RW 0x02D0_0240
	UINT32 reg_s_lut_x4                     :10;	//(9:0,RW,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x5                     :10;	//(25:16,RW,0x2D0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_011_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30B0 RW 0x01B0_0120
	UINT32 reg_s_lut_s2                     :10;	//(9:0,RW,0x120) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x3                     :10;	//(25:16,RW,0x1B0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30B4 RW 0x0090_0000
	UINT32 reg_s_lut_x0                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x1                     :10;	//(25:16,RW,0x90) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_013_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30B8 RW 0x0000_0050
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_014_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30BC RW 0x0098_00E0
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_015_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30C0 RW 0x0128_0170
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_016_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30C4 RW 0x01B8_0200
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_017_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30C8 RW 0x0064_0000
	UINT32 reg_lg_bs_exp_y_ofs0             :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs1             :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_018_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30CC RW 0x012C_00C8
	UINT32 reg_lg_bs_exp_y_ofs2             :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs3             :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_019_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30D0 RW 0x01F4_0190
	UINT32 reg_lg_bs_exp_y_ofs4             :10;	//(9:0,RW,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs5             :10;	//(25:16,RW,0x1F4) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_020_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30D4 RW 0x0000_0258
	UINT32 reg_lg_bs_exp_y_ofs6             :10;	//(9:0,RW,0x258) //
	UINT32 resvd                            :22;
	};
}O24A0_OLED_PHDR_CTRL_021_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30D8 RW 0xC808_0400
	UINT32 reg_lg_bs_exp_s_ofs0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_bs_exp_s_ofs1             :8;	//(15:8,RW,0x4) //
	UINT32 reg_lg_bs_exp_s_ofs2             :8;	//(23:16,RW,0x8) //
	UINT32 reg_lg_bs_exp_s_ofs3             :8;	//(31:24,RW,0xC8) //
	};
}O24A0_OLED_PHDR_CTRL_022_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30DC RW 0x0019_1410
	UINT32 reg_lg_bs_exp_s_ofs4             :8;	//(7:0,RW,0x10) //
	UINT32 reg_lg_bs_exp_s_ofs5             :8;	//(15:8,RW,0x14) //
	UINT32 reg_lg_bs_exp_s_ofs6             :8;	//(23:16,RW,0x19) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_023_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30E0 RW 0x0073_3982
	UINT32 reg_lg_bs_exp_s_wei              :3;	//(2:0,RW,0x2) //
	UINT32 resvd0                           :1;
	UINT32 reg_lg_y_max                     :10;	//(13:4,RW,0x398) //
	UINT32 resvd1                           :2;
	UINT32 reg_lg_ybs_scale                 :8;	//(23:16,RW,0x73) //
	UINT32 resvd2                           :8;
	};
}O24A0_OLED_PHDR_CTRL_024_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30E4 RW 0xFFEE_DDCC
	UINT32 reg_lg_yy_lut_x12                :8;	//(7:0,RW,0xCC) //
	UINT32 reg_lg_yy_lut_x13                :8;	//(15:8,RW,0xDD) //
	UINT32 reg_lg_yy_lut_x14                :8;	//(23:16,RW,0xEE) //
	UINT32 reg_lg_yy_lut_x15                :8;	//(31:24,RW,0xFF) //
	};
}O24A0_OLED_PHDR_CTRL_025_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30E8 RW 0xBBAA_9988
	UINT32 reg_lg_yy_lut_x08                :8;	//(7:0,RW,0x88) //
	UINT32 reg_lg_yy_lut_x09                :8;	//(15:8,RW,0x99) //
	UINT32 reg_lg_yy_lut_x10                :8;	//(23:16,RW,0xAA) //
	UINT32 reg_lg_yy_lut_x11                :8;	//(31:24,RW,0xBB) //
	};
}O24A0_OLED_PHDR_CTRL_026_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30EC RW 0x7766_5544
	UINT32 reg_lg_yy_lut_x04                :8;	//(7:0,RW,0x44) //
	UINT32 reg_lg_yy_lut_x05                :8;	//(15:8,RW,0x55) //
	UINT32 reg_lg_yy_lut_x06                :8;	//(23:16,RW,0x66) //
	UINT32 reg_lg_yy_lut_x07                :8;	//(31:24,RW,0x77) //
	};
}O24A0_OLED_PHDR_CTRL_027_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30F0 RW 0x3322_1100
	UINT32 reg_lg_yy_lut_x00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_yy_lut_x01                :8;	//(15:8,RW,0x11) //
	UINT32 reg_lg_yy_lut_x02                :8;	//(23:16,RW,0x22) //
	UINT32 reg_lg_yy_lut_x03                :8;	//(31:24,RW,0x33) //
	};
}O24A0_OLED_PHDR_CTRL_028_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30F4 RW 0xFFD9_B99E
	UINT32 reg_lg_yy_lut_y12                :8;	//(7:0,RW,0x9E) //
	UINT32 reg_lg_yy_lut_y13                :8;	//(15:8,RW,0xB9) //
	UINT32 reg_lg_yy_lut_y14                :8;	//(23:16,RW,0xD9) //
	UINT32 reg_lg_yy_lut_y15                :8;	//(31:24,RW,0xFF) //
	};
}O24A0_OLED_PHDR_CTRL_029_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30F8 RW 0x8673_6253
	UINT32 reg_lg_yy_lut_y08                :8;	//(7:0,RW,0x53) //
	UINT32 reg_lg_yy_lut_y09                :8;	//(15:8,RW,0x62) //
	UINT32 reg_lg_yy_lut_y10                :8;	//(23:16,RW,0x73) //
	UINT32 reg_lg_yy_lut_y11                :8;	//(31:24,RW,0x86) //
	};
}O24A0_OLED_PHDR_CTRL_030_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E30FC RW 0x473C_332C
	UINT32 reg_lg_yy_lut_y04                :8;	//(7:0,RW,0x2C) //
	UINT32 reg_lg_yy_lut_y05                :8;	//(15:8,RW,0x33) //
	UINT32 reg_lg_yy_lut_y06                :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lg_yy_lut_y07                :8;	//(31:24,RW,0x47) //
	};
}O24A0_OLED_PHDR_CTRL_031_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3100 RW 0x2520_1B17
	UINT32 reg_lg_yy_lut_y00                :8;	//(7:0,RW,0x17) //
	UINT32 reg_lg_yy_lut_y01                :8;	//(15:8,RW,0x1B) //
	UINT32 reg_lg_yy_lut_y02                :8;	//(23:16,RW,0x20) //
	UINT32 reg_lg_yy_lut_y03                :8;	//(31:24,RW,0x25) //
	};
}O24A0_OLED_PHDR_CTRL_032_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3104 RW 0x0167_0167
	UINT32 reg_lg_h_lut_x30                 :10;	//(9:0,RW,0x167) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x31                 :10;	//(25:16,RW,0x167) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_033_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3108 RW 0x015C_0150
	UINT32 reg_lg_h_lut_x28                 :10;	//(9:0,RW,0x150) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x29                 :10;	//(25:16,RW,0x15C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_034_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E310C RW 0x0144_0138
	UINT32 reg_lg_h_lut_x26                 :10;	//(9:0,RW,0x138) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x27                 :10;	//(25:16,RW,0x144) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_035_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3110 RW 0x012C_0120
	UINT32 reg_lg_h_lut_x24                 :10;	//(9:0,RW,0x120) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x25                 :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_036_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3114 RW 0x0114_0108
	UINT32 reg_lg_h_lut_x22                 :10;	//(9:0,RW,0x108) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x23                 :10;	//(25:16,RW,0x114) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_037_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3118 RW 0x00FC_00F0
	UINT32 reg_lg_h_lut_x20                 :10;	//(9:0,RW,0xF0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x21                 :10;	//(25:16,RW,0xFC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_038_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E311C RW 0x00E4_00D8
	UINT32 reg_lg_h_lut_x18                 :10;	//(9:0,RW,0xD8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x19                 :10;	//(25:16,RW,0xE4) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_039_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3120 RW 0x00CC_00C0
	UINT32 reg_lg_h_lut_x16                 :10;	//(9:0,RW,0xC0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x17                 :10;	//(25:16,RW,0xCC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_040_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3124 RW 0x00B4_00A8
	UINT32 reg_lg_h_lut_x14                 :10;	//(9:0,RW,0xA8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x15                 :10;	//(25:16,RW,0xB4) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_041_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3128 RW 0x009C_0090
	UINT32 reg_lg_h_lut_x12                 :10;	//(9:0,RW,0x90) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x13                 :10;	//(25:16,RW,0x9C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_042_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E312C RW 0x0084_0078
	UINT32 reg_lg_h_lut_x10                 :10;	//(9:0,RW,0x78) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x11                 :10;	//(25:16,RW,0x84) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_043_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3130 RW 0x006C_0060
	UINT32 reg_lg_h_lut_x08                 :10;	//(9:0,RW,0x60) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x09                 :10;	//(25:16,RW,0x6C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_044_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3134 RW 0x0054_0048
	UINT32 reg_lg_h_lut_x06                 :10;	//(9:0,RW,0x48) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x07                 :10;	//(25:16,RW,0x54) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_045_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3138 RW 0x003C_0030
	UINT32 reg_lg_h_lut_x04                 :10;	//(9:0,RW,0x30) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x05                 :10;	//(25:16,RW,0x3C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_046_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E313C RW 0x0024_0018
	UINT32 reg_lg_h_lut_x02                 :10;	//(9:0,RW,0x18) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x03                 :10;	//(25:16,RW,0x24) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_047_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3140 RW 0x000C_0000
	UINT32 reg_lg_h_lut_x00                 :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x01                 :10;	//(25:16,RW,0xC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_048_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3144 RW 0x0001_0001
	UINT32 reg_lg_h_lut_y30                 :10;	//(9:0,RW,0x1) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y31                 :10;	//(25:16,RW,0x1) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_049_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3148 RW 0x0003_0006
	UINT32 reg_lg_h_lut_y28                 :10;	//(9:0,RW,0x6) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y29                 :10;	//(25:16,RW,0x3) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_050_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E314C RW 0x0009_0009
	UINT32 reg_lg_h_lut_y26                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y27                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_051_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3150 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y24                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y25                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_052_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3154 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y22                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y23                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_053_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3158 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y20                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y21                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_054_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E315C RW 0x0009_000A
	UINT32 reg_lg_h_lut_y18                 :10;	//(9:0,RW,0xA) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y19                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_055_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3160 RW 0x000C_000F
	UINT32 reg_lg_h_lut_y16                 :10;	//(9:0,RW,0xF) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y17                 :10;	//(25:16,RW,0xC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_056_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3164 RW 0x0011_0014
	UINT32 reg_lg_h_lut_y14                 :10;	//(9:0,RW,0x14) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y15                 :10;	//(25:16,RW,0x11) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_057_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3168 RW 0x0017_001B
	UINT32 reg_lg_h_lut_y12                 :10;	//(9:0,RW,0x1B) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y13                 :10;	//(25:16,RW,0x17) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_058_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E316C RW 0x001E_0022
	UINT32 reg_lg_h_lut_y10                 :10;	//(9:0,RW,0x22) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y11                 :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_059_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3170 RW 0x0023_002D
	UINT32 reg_lg_h_lut_y08                 :10;	//(9:0,RW,0x2D) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y09                 :10;	//(25:16,RW,0x23) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_060_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3174 RW 0x0044_005E
	UINT32 reg_lg_h_lut_y06                 :10;	//(9:0,RW,0x5E) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y07                 :10;	//(25:16,RW,0x44) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_061_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3178 RW 0x0068_0058
	UINT32 reg_lg_h_lut_y04                 :10;	//(9:0,RW,0x58) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y05                 :10;	//(25:16,RW,0x68) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_062_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E317C RW 0x0038_001B
	UINT32 reg_lg_h_lut_y02                 :10;	//(9:0,RW,0x1B) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y03                 :10;	//(25:16,RW,0x38) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_063_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3180 RW 0x000A_0003
	UINT32 reg_lg_h_lut_y00                 :10;	//(9:0,RW,0x3) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y01                 :10;	//(25:16,RW,0xA) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_064_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3184 RW 0x0000_4000
	UINT32 reg_lg_brm_bs_cnt                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_lg_brm_exp_wei               :4;	//(15:12,RW,0x4) //
	UINT32 resvd1                           :16;
	};
}O24A0_OLED_PHDR_CTRL_065_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3188 RW 0x0398_037C
	UINT32 reg_lg_br_lut_x14                :10;	//(9:0,RW,0x37C) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x15                :10;	//(25:16,RW,0x398) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_066_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E318C RW 0x036D_035E
	UINT32 reg_lg_br_lut_x12                :10;	//(9:0,RW,0x35E) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x13                :10;	//(25:16,RW,0x36D) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_067_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3190 RW 0x034F_0340
	UINT32 reg_lg_br_lut_x10                :10;	//(9:0,RW,0x340) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x11                :10;	//(25:16,RW,0x34F) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_068_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3194 RW 0x0331_0322
	UINT32 reg_lg_br_lut_x08                :10;	//(9:0,RW,0x322) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x09                :10;	//(25:16,RW,0x331) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_069_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3198 RW 0x0313_0304
	UINT32 reg_lg_br_lut_x06                :10;	//(9:0,RW,0x304) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x07                :10;	//(25:16,RW,0x313) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_070_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E319C RW 0x02F5_02E6
	UINT32 reg_lg_br_lut_x04                :10;	//(9:0,RW,0x2E6) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x05                :10;	//(25:16,RW,0x2F5) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_071_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31A0 RW 0x02D7_02C8
	UINT32 reg_lg_br_lut_x02                :10;	//(9:0,RW,0x2C8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x03                :10;	//(25:16,RW,0x2D7) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_072_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31A4 RW 0x02B9_02AA
	UINT32 reg_lg_br_lut_x00                :10;	//(9:0,RW,0x2AA) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x01                :10;	//(25:16,RW,0x2B9) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_073_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31A8 RW 0xFFC6_AB91
	UINT32 reg_lg_br_lut_y12                :8;	//(7:0,RW,0x91) //
	UINT32 reg_lg_br_lut_y13                :8;	//(15:8,RW,0xAB) //
	UINT32 reg_lg_br_lut_y14                :8;	//(23:16,RW,0xC6) //
	UINT32 reg_lg_br_lut_y15                :8;	//(31:24,RW,0xFF) //
	};
}O24A0_OLED_PHDR_CTRL_074_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31AC RW 0x7A65_5240
	UINT32 reg_lg_br_lut_y08                :8;	//(7:0,RW,0x40) //
	UINT32 reg_lg_br_lut_y09                :8;	//(15:8,RW,0x52) //
	UINT32 reg_lg_br_lut_y10                :8;	//(23:16,RW,0x65) //
	UINT32 reg_lg_br_lut_y11                :8;	//(31:24,RW,0x7A) //
	};
}O24A0_OLED_PHDR_CTRL_075_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31B0 RW 0x3124_1910
	UINT32 reg_lg_br_lut_y04                :8;	//(7:0,RW,0x10) //
	UINT32 reg_lg_br_lut_y05                :8;	//(15:8,RW,0x19) //
	UINT32 reg_lg_br_lut_y06                :8;	//(23:16,RW,0x24) //
	UINT32 reg_lg_br_lut_y07                :8;	//(31:24,RW,0x31) //
	};
}O24A0_OLED_PHDR_CTRL_076_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31B4 RW 0x0904_0100
	UINT32 reg_lg_br_lut_y00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_br_lut_y01                :8;	//(15:8,RW,0x1) //
	UINT32 reg_lg_br_lut_y02                :8;	//(23:16,RW,0x4) //
	UINT32 reg_lg_br_lut_y03                :8;	//(31:24,RW,0x9) //
	};
}O24A0_OLED_PHDR_CTRL_077_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31B8 RW 0x03FF_03E0
	UINT32 reg_tcm_lut_x30                  :10;	//(9:0,RW,0x3E0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x31                  :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_078_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31BC RW 0x03BC_039C
	UINT32 reg_tcm_lut_x28                  :10;	//(9:0,RW,0x39C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x29                  :10;	//(25:16,RW,0x3BC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_079_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31C0 RW 0x037C_035C
	UINT32 reg_tcm_lut_x26                  :10;	//(9:0,RW,0x35C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x27                  :10;	//(25:16,RW,0x37C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_080_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31C4 RW 0x0338_0318
	UINT32 reg_tcm_lut_x24                  :10;	//(9:0,RW,0x318) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x25                  :10;	//(25:16,RW,0x338) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_081_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31C8 RW 0x02F8_02D8
	UINT32 reg_tcm_lut_x22                  :10;	//(9:0,RW,0x2D8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x23                  :10;	//(25:16,RW,0x2F8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_082_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31CC RW 0x02B4_0294
	UINT32 reg_tcm_lut_x20                  :10;	//(9:0,RW,0x294) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x21                  :10;	//(25:16,RW,0x2B4) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_083_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31D0 RW 0x0274_0254
	UINT32 reg_tcm_lut_x18                  :10;	//(9:0,RW,0x254) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x19                  :10;	//(25:16,RW,0x274) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_084_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31D4 RW 0x0230_0210
	UINT32 reg_tcm_lut_x16                  :10;	//(9:0,RW,0x210) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x17                  :10;	//(25:16,RW,0x230) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_085_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31D8 RW 0x01F0_01D0
	UINT32 reg_tcm_lut_x14                  :10;	//(9:0,RW,0x1D0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x15                  :10;	//(25:16,RW,0x1F0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_086_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31DC RW 0x01AC_018C
	UINT32 reg_tcm_lut_x12                  :10;	//(9:0,RW,0x18C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x13                  :10;	//(25:16,RW,0x1AC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_087_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31E0 RW 0x016C_014C
	UINT32 reg_tcm_lut_x10                  :10;	//(9:0,RW,0x14C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x11                  :10;	//(25:16,RW,0x16C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_088_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31E4 RW 0x0128_0108
	UINT32 reg_tcm_lut_x08                  :10;	//(9:0,RW,0x108) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x09                  :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_089_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31E8 RW 0x00E8_00C8
	UINT32 reg_tcm_lut_x06                  :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x07                  :10;	//(25:16,RW,0xE8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_090_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31EC RW 0x00A4_0084
	UINT32 reg_tcm_lut_x04                  :10;	//(9:0,RW,0x84) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x05                  :10;	//(25:16,RW,0xA4) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_091_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31F0 RW 0x0064_0044
	UINT32 reg_tcm_lut_x02                  :10;	//(9:0,RW,0x44) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x03                  :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_092_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31F4 RW 0x0020_0000
	UINT32 reg_tcm_lut_x00                  :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x01                  :10;	//(25:16,RW,0x20) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_093_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31F8 RW 0x03FF_03D8
	UINT32 reg_tcm_lut_y30                  :10;	//(9:0,RW,0x3D8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y31                  :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_094_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E31FC RW 0x03AC_0384
	UINT32 reg_tcm_lut_y28                  :10;	//(9:0,RW,0x384) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y29                  :10;	//(25:16,RW,0x3AC) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_095_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3200 RW 0x035C_0334
	UINT32 reg_tcm_lut_y26                  :10;	//(9:0,RW,0x334) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y27                  :10;	//(25:16,RW,0x35C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_096_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3204 RW 0x0308_02E0
	UINT32 reg_tcm_lut_y24                  :10;	//(9:0,RW,0x2E0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y25                  :10;	//(25:16,RW,0x308) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_097_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3208 RW 0x02B8_0290
	UINT32 reg_tcm_lut_y22                  :10;	//(9:0,RW,0x290) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y23                  :10;	//(25:16,RW,0x2B8) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_098_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E320C RW 0x0264_023C
	UINT32 reg_tcm_lut_y20                  :10;	//(9:0,RW,0x23C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y21                  :10;	//(25:16,RW,0x264) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_099_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3210 RW 0x0214_01EC
	UINT32 reg_tcm_lut_y18                  :10;	//(9:0,RW,0x1EC) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y19                  :10;	//(25:16,RW,0x214) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3214 RW 0x01C0_0198
	UINT32 reg_tcm_lut_y16                  :10;	//(9:0,RW,0x198) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y17                  :10;	//(25:16,RW,0x1C0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3218 RW 0x0178_0160
	UINT32 reg_tcm_lut_y14                  :10;	//(9:0,RW,0x160) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y15                  :10;	//(25:16,RW,0x178) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E321C RW 0x0144_012C
	UINT32 reg_tcm_lut_y12                  :10;	//(9:0,RW,0x12C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y13                  :10;	//(25:16,RW,0x144) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3220 RW 0x0114_00FC
	UINT32 reg_tcm_lut_y10                  :10;	//(9:0,RW,0xFC) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y11                  :10;	//(25:16,RW,0x114) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3224 RW 0x00E0_00C8
	UINT32 reg_tcm_lut_y08                  :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y09                  :10;	//(25:16,RW,0xE0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3228 RW 0x00B0_0098
	UINT32 reg_tcm_lut_y06                  :10;	//(9:0,RW,0x98) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y07                  :10;	//(25:16,RW,0xB0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E322C RW 0x007C_0064
	UINT32 reg_tcm_lut_y04                  :10;	//(9:0,RW,0x64) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y05                  :10;	//(25:16,RW,0x7C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3230 RW 0x004C_0034
	UINT32 reg_tcm_lut_y02                  :10;	//(9:0,RW,0x34) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y03                  :10;	//(25:16,RW,0x4C) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3234 RW 0x0018_0000
	UINT32 reg_tcm_lut_y00                  :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y01                  :10;	//(25:16,RW,0x18) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3238 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x14                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x15                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E323C RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x12                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x13                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3240 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x10                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x11                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3244 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x08                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x09                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3248 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x06                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x07                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E324C RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x04                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x05                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3250 RW 0x0100_0066
	UINT32 reg_apl_lut_g_x02                :10;	//(9:0,RW,0x66) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x03                :10;	//(25:16,RW,0x100) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3254 RW 0x001E_0000
	UINT32 reg_apl_lut_g_x00                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x01                :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3258 RW 0x0000_0000
	UINT32 reg_apl_lut_g_y12                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y13                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y14                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y15                :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E325C RW 0x0000_0000
	UINT32 reg_apl_lut_g_y08                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y09                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y10                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y11                :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3260 RW 0x0000_0000
	UINT32 reg_apl_lut_g_y04                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y05                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y06                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y07                :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_120_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3264 RW 0x003C_5E5E
	UINT32 reg_apl_lut_g_y00                :8;	//(7:0,RW,0x5E) //
	UINT32 reg_apl_lut_g_y01                :8;	//(15:8,RW,0x5E) //
	UINT32 reg_apl_lut_g_y02                :8;	//(23:16,RW,0x3C) //
	UINT32 reg_apl_lut_g_y03                :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_121_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3268 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x14                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x15                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_122_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E326C RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x12                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x13                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_123_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3270 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x10                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x11                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_124_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3274 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x08                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x09                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_125_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3278 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x06                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x07                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E327C RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x04                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x05                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3280 RW 0x0100_0066
	UINT32 reg_apl_lut_l_x02                :10;	//(9:0,RW,0x66) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x03                :10;	//(25:16,RW,0x100) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3284 RW 0x001E_0000
	UINT32 reg_apl_lut_l_x00                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x01                :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3288 RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y12                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y13                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y14                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y15                :8;	//(31:24,RW,0x2F) //
	};
}O24A0_OLED_PHDR_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E328C RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y08                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y09                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y10                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y11                :8;	//(31:24,RW,0x2F) //
	};
}O24A0_OLED_PHDR_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3290 RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y04                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y05                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y06                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y07                :8;	//(31:24,RW,0x2F) //
	};
}O24A0_OLED_PHDR_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3294 RW 0x2F11_0000
	UINT32 reg_apl_lut_l_y00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_l_y01                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_l_y02                :8;	//(23:16,RW,0x11) //
	UINT32 reg_apl_lut_l_y03                :8;	//(31:24,RW,0x2F) //
	};
}O24A0_OLED_PHDR_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3298 RW 0xFFD8_B490
	UINT32 reg_osd_lut_x04                  :8;	//(7:0,RW,0x90) //
	UINT32 reg_osd_lut_x05                  :8;	//(15:8,RW,0xB4) //
	UINT32 reg_osd_lut_x06                  :8;	//(23:16,RW,0xD8) //
	UINT32 reg_osd_lut_x07                  :8;	//(31:24,RW,0xFF) //
	};
}O24A0_OLED_PHDR_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E329C RW 0x6C48_2400
	UINT32 reg_osd_lut_x00                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_osd_lut_x01                  :8;	//(15:8,RW,0x24) //
	UINT32 reg_osd_lut_x02                  :8;	//(23:16,RW,0x48) //
	UINT32 reg_osd_lut_x03                  :8;	//(31:24,RW,0x6C) //
	};
}O24A0_OLED_PHDR_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32A0 RW 0x0014_2638
	UINT32 reg_osd_lut_y04                  :8;	//(7:0,RW,0x38) //
	UINT32 reg_osd_lut_y05                  :8;	//(15:8,RW,0x26) //
	UINT32 reg_osd_lut_y06                  :8;	//(23:16,RW,0x14) //
	UINT32 reg_osd_lut_y07                  :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32A4 RW 0x4A5C_6E80
	UINT32 reg_osd_lut_y00                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_osd_lut_y01                  :8;	//(15:8,RW,0x6E) //
	UINT32 reg_osd_lut_y02                  :8;	//(23:16,RW,0x5C) //
	UINT32 reg_osd_lut_y03                  :8;	//(31:24,RW,0x4A) //
	};
}O24A0_OLED_PHDR_CTRL_137_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32A8 RW 0xFFD8_B490
	UINT32 reg_lsr_lut_x04                  :8;	//(7:0,RW,0x90) //
	UINT32 reg_lsr_lut_x05                  :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lsr_lut_x06                  :8;	//(23:16,RW,0xD8) //
	UINT32 reg_lsr_lut_x07                  :8;	//(31:24,RW,0xFF) //
	};
}O24A0_OLED_PHDR_CTRL_138_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32AC RW 0x6C48_2400
	UINT32 reg_lsr_lut_x00                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lsr_lut_x01                  :8;	//(15:8,RW,0x24) //
	UINT32 reg_lsr_lut_x02                  :8;	//(23:16,RW,0x48) //
	UINT32 reg_lsr_lut_x03                  :8;	//(31:24,RW,0x6C) //
	};
}O24A0_OLED_PHDR_CTRL_139_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32B0 RW 0x0014_2638
	UINT32 reg_lsr_lut_y04                  :8;	//(7:0,RW,0x38) //
	UINT32 reg_lsr_lut_y05                  :8;	//(15:8,RW,0x26) //
	UINT32 reg_lsr_lut_y06                  :8;	//(23:16,RW,0x14) //
	UINT32 reg_lsr_lut_y07                  :8;	//(31:24,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_140_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32B4 RW 0x4A5C_6E80
	UINT32 reg_lsr_lut_y00                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_lsr_lut_y01                  :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lsr_lut_y02                  :8;	//(23:16,RW,0x5C) //
	UINT32 reg_lsr_lut_y03                  :8;	//(31:24,RW,0x4A) //
	};
}O24A0_OLED_PHDR_CTRL_141_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32B8 RW 0x09CD_0001
	UINT32 reg_csc_en                       :1;	//(0,RW,0x1) //
	UINT32 resvd0                           :15;
	UINT32 reg_csc_coef0                    :15;	//(30:16,RW,0x9CD) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_PHDR_CTRL_142_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32BC RW 0x02EA_00FD
	UINT32 reg_csc_coef1                    :15;	//(14:0,RW,0xFD) //
	UINT32 resvd0                           :1;
	UINT32 reg_csc_coef2                    :15;	//(30:16,RW,0x2EA) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_PHDR_CTRL_143_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32C0 RW 0x0000_0000
	UINT32 reg_csc_ofst0                    :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_csc_ofst1                    :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_PHDR_CTRL_144_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32C4 RW 0x0040_0000
	UINT32 reg_csc_ofst2                    :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_csc_ofst3                    :11;	//(26:16,RW,0x40) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_PHDR_CTRL_145_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32C8 RW 0x010C_0870
	UINT32 reg_lg_va_length                 :12;	//(11:0,RW,0x870) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt0                   :12;	//(27:16,RW,0x10C) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_PHDR_CTRL_146_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32CC RW 0x0328_021A
	UINT32 reg_lg_bs_cnt1                   :12;	//(11:0,RW,0x21A) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt2                   :12;	//(27:16,RW,0x328) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_PHDR_CTRL_147_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32D0 RW 0x0544_0436
	UINT32 reg_lg_bs_cnt3                   :12;	//(11:0,RW,0x436) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt4                   :12;	//(27:16,RW,0x544) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_PHDR_CTRL_148_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32D4 RW 0x086E_0652
	UINT32 reg_lg_bs_cnt5                   :12;	//(11:0,RW,0x652) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt6                   :12;	//(27:16,RW,0x86E) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_PHDR_CTRL_149_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32D8 RW 0x0000_0000
	UINT32 reg_info_diff_th1                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_info_diff_th0                :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_150_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32DC RW 0x0000_0000
	UINT32 reg_info_diff_th3                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_info_diff_th2                :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_151_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32E0 RW 0x0000_0001
	UINT32 reg_osd_th                       :8;	//(7:0,RW,0x1) //
	UINT32 resvd                            :24;
	};
}O24A0_OLED_PHDR_CTRL_152_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32E4 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_153_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32E8 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_154_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32EC RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_155_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32F0 RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_156_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32F4 RW 0x0000_0000
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
}O24A0_OLED_PHDR_CTRL_157_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32F8 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_158_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E32FC RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_159_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3300 RW 0x0002_002A
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_160_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3304 RW 0x0002_002A
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_161_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3308 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}O24A0_OLED_PHDR_CTRL_162_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E330C RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_PHDR_CTRL_163_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3310 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_164_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3314 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_165_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3318 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_166_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E331C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_167_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3320 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_168_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3324 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_PHDR_CTRL_169_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3328 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_yy_2ch             :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_pic_lg_max_luma              :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_170_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E332C RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt0               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_171_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3330 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt1               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_172_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3334 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt2               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_173_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3338 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt3               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_174_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E333C RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt4               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_175_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3340 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt5               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_176_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3344 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt6               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_177_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3348 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt7               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_178_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E334C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_179_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3350 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_180_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3354 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_181_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3358 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_182_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E335C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_183_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3360 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_184_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3364 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_185_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3368 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_186_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E336C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_187_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3370 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_188_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3374 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_189_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3378 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_190_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E337C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_max           :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_ro_pel_diff_gg_max           :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_191_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3380 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_max           :10;	//(9:0,RO,0x0) //
	UINT32 resvd                            :22;
	};
}O24A0_OLED_PHDR_CTRL_192_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3390 RW 0x0000_0000
	UINT32 r_rgb2yc_en                      :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_10bit_clip_en                  :1;	//(4,RW,0x0) //over 1023 value clip to 1023
	UINT32 resvd1                           :27;
	};
}O24A0_OLED_RGB2YC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3394 RW 0x0B71_0128
	UINT32 r_rgb2yc_coef1                   :15;	//(14:0,RW,0x128) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef0                   :15;	//(30:16,RW,0xB71) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_RGB2YC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3398 RW 0x0367_79B1
	UINT32 r_rgb2yc_coef3                   :15;	//(14:0,RW,0x79B1) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef2                   :15;	//(30:16,RW,0x367) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_RGB2YC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E339C RW 0x082F_7E20
	UINT32 r_rgb2yc_coef5                   :15;	//(14:0,RW,0x7E20) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef4                   :15;	//(30:16,RW,0x82F) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_RGB2YC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33A0 RW 0x7891_7F40
	UINT32 r_rgb2yc_coef7                   :15;	//(14:0,RW,0x7F40) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef6                   :15;	//(30:16,RW,0x7891) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_RGB2YC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33A4 RW 0x082F_0000
	UINT32 resvd0                           :16;
	UINT32 r_rgb2yc_coef8                   :15;	//(30:16,RW,0x82F) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_RGB2YC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33A8 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst0                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33AC RW 0x0000_0000
	UINT32 r_rgb2yc_ofst1                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33B0 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst2                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33B4 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst3                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33B8 RW 0x0000_4000
	UINT32 r_rgb2yc_ofst4                   :17;	//(16:0,RW,0x4000) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33BC RW 0x0000_4000
	UINT32 r_rgb2yc_ofst5                   :17;	//(16:0,RW,0x4000) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_RGB2YC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33C0 RW 0x03FF_0000
	UINT32 r_yc2rgb_en                      :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_manual_clip_en                 :1;	//(4,RW,0x0) //over r_yc2rgb_clip_th value clip to r_yc2rgb_clip_th
	UINT32 resvd1                           :11;
	UINT32 r_yc2rgb_clip_th                 :11;	//(26:16,RW,0x3FF) //
	UINT32 resvd2                           :5;
	};
}O24A0_OLED_YC2RGB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33C4 RW 0x1000_7D12
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,RW,0x7D12) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,RW,0x1000) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_YC2RGB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33C8 RW 0x78AD_1000
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,RW,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,RW,0x78AD) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_YC2RGB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33CC RW 0x1D07_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,RW,0x1D07) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_YC2RGB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33D0 RW 0x1000_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,RW,0x1000) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_YC2RGB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33D4 RW 0x18A2_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,RW,0x18A2) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_YC2RGB_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33D8 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst0                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33DC RW 0x0001_C000
	UINT32 r_yc2rgb_ofst1                   :17;	//(16:0,RW,0x1C000) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33E0 RW 0x0001_C000
	UINT32 r_yc2rgb_ofst2                   :17;	//(16:0,RW,0x1C000) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33E4 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst3                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33E8 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst4                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E33EC RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_YC2RGB_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3400 RW 0x0000_003C
	UINT32 reg_oled_apl_disable             :1;	//(0,RW,0x0) //
//#if (SOC_DEVICE < O24A0)
//	UINT32 resvd0                           :1;
//	UINT32 reg_apl_out_mode_hdr             :2;	//(3:2,RW,0x3) //0:manual_apl, 1:na�ve_apl(pixel/current), 2: filtered_apl(IIR/FIR), 3:TPC_gained_apl
//	UINT32 reg_apl_out_mode_tcon            :2;	//(5:4,RW,0x3) //0:manual_apl, 1:na�ve_apl(pixel/current), 2: filtered_apl(IIR/FIR), 3:TPC_gained_apl
//	UINT32 reg_naive_apl_sel                :2;	//(7:6,RW,0x0) //0:pixel_apl, 1:current_apl
//	UINT32 resvd1                           :8;
//#else
	UINT32 resvd0                           :3;
	UINT32 reg_apl_out_mode_hdr             :3;	//(6:4,RW,0x3) //0:manual_apl, 1:na�ve_apl,2:na�ve_apl_avg_y,3:na�ve_apl_blended_y_v,4:filt_apl_hdr
	UINT32 resvd1                           :1;
	UINT32 reg_apl_out_mode_tcon            :3;	//(10:8,RW,0x3) //0:manual_apl, 1:na�ve_apl,2:na�ve_apl_avg_y,3:na�ve_apl_blended_y_v,4:filt_apl_tcon
	UINT32 resvd2                           :1;
	UINT32 reg_in_sel_apl_tcon              :2;	//(13:12,RW,0x0) //0:manual_apl, 1:na�ve_apl,2:avg_y,3:blended_y_v
	UINT32 reg_in_sel_apl_hdr               :2;	//(15:14,RW,0x0) //0:manual_apl, 1:na�ve_apl,2:avg_y,3:blended_y_v
//#endif
	UINT32 reg_manual_apl                   :10;	//(25:16,RW,0x0) //
	UINT32 resvd3                           :6;
	};
}O24A0_OLED_OAPL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3404 RW 0x0000_0000
	UINT32 reg_eotf_en                      :1;	//(0,RW,0x0) //note : apl_eotf lut wr/rd controled by led_hif(0x780~0x788)
	UINT32 resvd0                           :3;
	UINT32 reg_eotf_rdata_sel               :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_bit_extension_mode      :2;	//(9:8,RW,0x0) //
	UINT32 resvd2                           :22;
	};
}O24A0_OLED_OAPL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3408 RW 0x03B0_0200
	UINT32 reg_curr_peak_level              :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_wg_ratio                     :11;	//(26:16,RW,0x3B0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E340C RW 0x0478_031F
	UINT32 reg_wb_ratio                     :11;	//(10:0,RW,0x31F) //
	UINT32 resvd0                           :5;
	UINT32 reg_wr_ratio                     :11;	//(26:16,RW,0x478) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3410 RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,RW,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,RW,0x326) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_OAPL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3414 RW 0x0389_02A8
	UINT32 reg_b_crnt_wgt                   :12;	//(11:0,RW,0x2A8) //
	UINT32 resvd0                           :4;
	UINT32 reg_r_crnt_wgt                   :12;	//(27:16,RW,0x389) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_OAPL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3418 RW 0x0000_0000
	UINT32 reg_crnt_lut_y00                 :16;	//(15:0,RW,0x0) //
	UINT32 reg_crnt_lut_x00                 :10;	//(25:16,RW,0x0) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E341C RW 0x0044_0CF9
	UINT32 reg_crnt_lut_y01                 :16;	//(15:0,RW,0xCF9) //
	UINT32 reg_crnt_lut_x01                 :10;	//(25:16,RW,0x44) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3420 RW 0x0088_1BD0
	UINT32 reg_crnt_lut_y02                 :16;	//(15:0,RW,0x1BD0) //
	UINT32 reg_crnt_lut_x02                 :10;	//(25:16,RW,0x88) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3424 RW 0x00CC_2B72
	UINT32 reg_crnt_lut_y03                 :16;	//(15:0,RW,0x2B72) //
	UINT32 reg_crnt_lut_x03                 :10;	//(25:16,RW,0xCC) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3428 RW 0x0110_3B9F
	UINT32 reg_crnt_lut_y04                 :16;	//(15:0,RW,0x3B9F) //
	UINT32 reg_crnt_lut_x04                 :10;	//(25:16,RW,0x110) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E342C RW 0x0154_4C35
	UINT32 reg_crnt_lut_y05                 :16;	//(15:0,RW,0x4C35) //
	UINT32 reg_crnt_lut_x05                 :10;	//(25:16,RW,0x154) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3430 RW 0x0198_5D22
	UINT32 reg_crnt_lut_y06                 :16;	//(15:0,RW,0x5D22) //
	UINT32 reg_crnt_lut_x06                 :10;	//(25:16,RW,0x198) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3434 RW 0x01DC_6E57
	UINT32 reg_crnt_lut_y07                 :16;	//(15:0,RW,0x6E57) //
	UINT32 reg_crnt_lut_x07                 :10;	//(25:16,RW,0x1DC) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3438 RW 0x0220_7FCD
	UINT32 reg_crnt_lut_y08                 :16;	//(15:0,RW,0x7FCD) //
	UINT32 reg_crnt_lut_x08                 :10;	//(25:16,RW,0x220) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E343C RW 0x0264_917A
	UINT32 reg_crnt_lut_y09                 :16;	//(15:0,RW,0x917A) //
	UINT32 reg_crnt_lut_x09                 :10;	//(25:16,RW,0x264) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3440 RW 0x02A8_A35B
	UINT32 reg_crnt_lut_y10                 :16;	//(15:0,RW,0xA35B) //
	UINT32 reg_crnt_lut_x10                 :10;	//(25:16,RW,0x2A8) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3444 RW 0x02EC_B569
	UINT32 reg_crnt_lut_y11                 :16;	//(15:0,RW,0xB569) //
	UINT32 reg_crnt_lut_x11                 :10;	//(25:16,RW,0x2EC) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3448 RW 0x0330_C7A2
	UINT32 reg_crnt_lut_y12                 :16;	//(15:0,RW,0xC7A2) //
	UINT32 reg_crnt_lut_x12                 :10;	//(25:16,RW,0x330) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E344C RW 0x0374_DA02
	UINT32 reg_crnt_lut_y13                 :16;	//(15:0,RW,0xDA02) //
	UINT32 reg_crnt_lut_x13                 :10;	//(25:16,RW,0x374) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3450 RW 0x03B8_EC86
	UINT32 reg_crnt_lut_y14                 :16;	//(15:0,RW,0xEC86) //
	UINT32 reg_crnt_lut_x14                 :10;	//(25:16,RW,0x3B8) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3454 RW 0x03FF_FFFF
	UINT32 reg_crnt_lut_y15                 :16;	//(15:0,RW,0xFFFF) //
	UINT32 reg_crnt_lut_x15                 :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd                            :6;
	};
}O24A0_OLED_OAPL_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3458 RW 0x0000_0000
	UINT32 reg_crnt_tune_lut_y00            :16;	//(15:0,RW,0x0) //
	UINT32 reg_crnt_tune_lut_x00            :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OAPL_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E345C RW 0x07D0_4CC2
	UINT32 reg_crnt_tune_lut_y01            :16;	//(15:0,RW,0x4CC2) //
	UINT32 reg_crnt_tune_lut_x01            :16;	//(31:16,RW,0x7D0) //
	};
}O24A0_OLED_OAPL_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3460 RW 0x0FA0_9984
	UINT32 reg_crnt_tune_lut_y02            :16;	//(15:0,RW,0x9984) //
	UINT32 reg_crnt_tune_lut_x02            :16;	//(31:16,RW,0xFA0) //
	};
}O24A0_OLED_OAPL_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3464 RW 0x1A0E_FFFF
	UINT32 reg_crnt_tune_lut_y03            :16;	//(15:0,RW,0xFFFF) //
	UINT32 reg_crnt_tune_lut_x03            :16;	//(31:16,RW,0x1A0E) //
	};
}O24A0_OLED_OAPL_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3468 RW 0x0000_0010
	UINT32 reg_apl_filt_init                :1;	//(0,RW,0x0) //note : set '1' at least 1 frame
	UINT32 resvd0                           :3;
	UINT32 reg_apl_filt_mode                :1;	//(4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_apl_filt_window_size         :3;	//(10:8,RW,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_apl_iir_gain                 :8;	//(23:16,RW,0x0) //
	UINT32 resvd3                           :8;
	};
}O24A0_OLED_OAPL_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E346C RW 0x0000_0180
	UINT32 reg_s_apl_val                    :8;	//(7:0,RW,0x80) //
	UINT32 reg_s_apl_val_mux                :1;	//(8,RW,0x1) //0:manual 1: S_APL
	UINT32 resvd                            :23;
	};
}O24A0_OLED_OAPL_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3470 RW 0x0000_0000
	UINT32 reg_s_apl_alpha_lut_y00          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x00          :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3474 RW 0x0024_0000
	UINT32 reg_s_apl_alpha_lut_y01          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x01          :8;	//(23:16,RW,0x24) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3478 RW 0x0048_0000
	UINT32 reg_s_apl_alpha_lut_y02          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x02          :8;	//(23:16,RW,0x48) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E347C RW 0x006C_0000
	UINT32 reg_s_apl_alpha_lut_y03          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x03          :8;	//(23:16,RW,0x6c) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3480 RW 0x0090_00FF
	UINT32 reg_s_apl_alpha_lut_y04          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x04          :8;	//(23:16,RW,0x90) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3484 RW 0x00B4_00FF
	UINT32 reg_s_apl_alpha_lut_y05          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x05          :8;	//(23:16,RW,0xB4) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3488 RW 0x00D8_00FF
	UINT32 reg_s_apl_alpha_lut_y06          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x06          :8;	//(23:16,RW,0xD8) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E348C RW 0x00FF_00FF
	UINT32 reg_s_apl_alpha_lut_y07          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x07          :8;	//(23:16,RW,0xFF) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3490 RW 0x0596_00C8
	UINT32 reg_oapl_offset_phdr             :12;	//(11:0,RW,0x00C8) //
	UINT32 resvd0                           :4;
	UINT32 reg_oapl_offset_tcon             :12;	//(27:16,RW,0x0596) //
	UINT32 resvd1                           :4;
	};
}O24A0_OLED_OAPL_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3494 RW 0x05FC_00BD
	UINT32 reg_filt_peak_lut_y10            :11;	//(10:0,RW,0xBD) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x10            :11;	//(26:16,RW,0x5FC) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3498 RW 0x0662_00B3
	UINT32 reg_filt_peak_lut_y11            :11;	//(10:0,RW,0xB3) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x11            :11;	//(26:16,RW,0x662) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E349C RW 0x06C8_00AA
	UINT32 reg_filt_peak_lut_y12            :11;	//(10:0,RW,0xAA) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x12            :11;	//(26:16,RW,0x6C8) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34A0 RW 0x072E_00A3
	UINT32 reg_filt_peak_lut_y13            :11;	//(10:0,RW,0xA3) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x13            :11;	//(26:16,RW,0x72E) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34A4 RW 0x0794_009C
	UINT32 reg_filt_peak_lut_y14            :11;	//(10:0,RW,0x9C) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x14            :11;	//(26:16,RW,0x794) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34A8 RW 0x07FF_0096
	UINT32 reg_filt_peak_lut_y15            :11;	//(10:0,RW,0x96) //
	UINT32 resvd0                           :5;
	UINT32 reg_filt_peak_lut_x15            :11;	//(26:16,RW,0x7FF) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34AC RW 0x0096_001E
	UINT32 reg_tpc_alpha                    :16;	//(15:0,RW,0x1E) //signd 16b
	UINT32 reg_tpc_min_peak_level           :11;	//(26:16,RW,0x96) //
	UINT32 resvd                            :5;
	};
}O24A0_OLED_OAPL_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34B0 RW 0x0000_0001
	UINT32 reg_oapl_rgb2yc_en               :1;	//(0,RW,0x1) //
	UINT32 resvd                            :31;
	};
}O24A0_OLED_OAPL_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34B4 RW 0x094A_00D0
	UINT32 reg_oapl_rgb2yc_coef1            :15;	//(14:0,RW,0x00D0) //
	UINT32 resvd0                           :1;
	UINT32 reg_oapl_rgb2yc_coef0            :15;	//(30:16,RW,0x094A) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_OAPL_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34B8 RW 0x0399_0000
	UINT32 resvd0                           :16;
	UINT32 reg_oapl_rgb2yc_coef2            :15;	//(30:16,RW,0x0399) //
	UINT32 resvd1                           :1;
	};
}O24A0_OLED_OAPL_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34BC RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst0            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_OAPL_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34C0 RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst3            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}O24A0_OLED_OAPL_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34C4 RW 0x0000_0000
	UINT32 reg_hsv_hsl_sel                  :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sat_en                       :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :27;
	};
}O24A0_OLED_OAPL_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34C8 RW 0x0080_0080
	UINT32 reg_ihsv_sgain                   :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_vgain                   :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34CC RW 0x0080_0080
	UINT32 reg_ihsv_soffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_hoffset                 :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34D0 RW 0x0000_0080
	UINT32 reg_ihsv_voffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}O24A0_OLED_OAPL_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_OAPL_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_OAPL_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34DC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}O24A0_OLED_OAPL_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34E0 RW 0x0145_0332
	UINT32 reg_peak2apl_lut_y12             :11;	//(10:0,RW,0x332) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x12             :11;	//(26:16,RW,0x145) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34E4 RW 0x016F_02CC
	UINT32 reg_peak2apl_lut_y13             :11;	//(10:0,RW,0x2CC) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x13             :11;	//(26:16,RW,0x16F) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34E8 RW 0x01A6_0266
	UINT32 reg_peak2apl_lut_y14             :11;	//(10:0,RW,0x266) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x14             :11;	//(26:16,RW,0x1A6) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34EC RW 0x01F4_0200
	UINT32 reg_peak2apl_lut_y15             :11;	//(10:0,RW,0x200) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x15             :11;	//(26:16,RW,0x1F4) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34F0 RW 0x03E8_00CC
	UINT32 reg_peak2apl_lut_y16             :11;	//(10:0,RW,0xCC) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x16             :11;	//(26:16,RW,0x3E8) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34F4 RW 0x04B0_003C
	UINT32 reg_peak2apl_lut_y17             :11;	//(10:0,RW,0x3C) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x17             :11;	//(26:16,RW,0x4B0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34F8 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y18             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x18             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E34FC RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y19             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x19             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3500 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y20             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x20             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3504 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y21             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x21             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3508 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y22             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x22             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E350C RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y23             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x23             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3510 RO 0x0000_0000
	UINT32 s_apl_val                        :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 s_apl_alpha                      :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
}O24A0_OLED_OAPL_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3514 RO 0x0000_0000
	UINT32 oled_apl_tcon                    :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 oled_apl_hdr                     :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :2;
	UINT32 oled_apl_de                      :1;	//(28,RO,0x0) //
	UINT32 resvd2                           :3;
	};
}O24A0_OLED_OAPL_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3518 RO 0x0000_0000
	UINT32 naive_apl_tcon_mux               :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_tcon                    :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E351C RO 0x0000_0000
	UINT32 naive_apl_hdr_mux                :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_hdr                     :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_OAPL_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3520 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3524 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3528 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E352C RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3530 RW 0x0000_0000
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
}O24A0_OLED_OLED_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3534 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3538 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E353C RW 0x0005_0097
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x97) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x5) //
	UINT32 reg_ha_seamless                  :1;	//(31,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3540 RW 0x0005_0097
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x97) //
	UINT32 resvd                            :1;
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x5) //
	UINT32 reg_hs_seamless                  :1;	//(31,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3544 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}O24A0_OLED_OLED_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3548 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}O24A0_OLED_OLED_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E354C RW 0x0000_0030
	UINT32 resvd0                           :4;
	UINT32 reg_ocpk_init_sel                :3;	//(6:4,RW,0x3) //0:out_vs_rising, 1:out_vs_falling, 2:out_va_rising, 3:out_va_falling, others:manual position from out_va_falling
	UINT32 resvd1                           :9;
	UINT32 reg_ocpk_manual_init_pos         :16;	//(31:16,RW,0x0) //line cnt after va_fl
	};
}O24A0_OLED_OLED_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3550 RW 0x00000008
	UINT32 reg_144hz_packet_fc              :3;	//(2:0,RW,0x0) //144hz control packet (assign to vx1 ctrl packet[5:3])	Frame count 	?�작모드 ?�정??HTOTAL 값이 변?�기까�???frame개수
	UINT32 reserved                         :1;	//(3,RW,0x1) //[3]:must be '1' (assign to vx1 ctrl packet[0])
	UINT32 reg_144hz_packet_md              :2;	//(5:4,RW,0x0) //144hz control packet (assign to vx1 ctrl packet[2:1])	144 mode	0:120hz(DE/HTOTAL=248/330)	1:144hz VRR (DE/HTOTAL=248/275)	2:120hz(DE/HTOTAL=240/330)	3:144hz VRR (DE/HTOTAL=240/275)
	UINT32 resvd                            :26;
	};
}O24A0_OLED_OLED_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3554 RW 0x0000_0000
	UINT32 reg_pg_width                     :16;	//(15:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_pg_ramp_pat_en               :1;	//(20,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_pg_o_color_sel               :2;	//(23:22,RW,0x0) //
	UINT32 resvd2                           :8;
	};
}O24A0_OLED_OLED_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3560 RO 0x0000_0000
	UINT32 pel_diff_v_th0_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_193_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3564 RO 0x0000_0000
	UINT32 pel_diff_v_th1_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_194_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3568 RO 0x0000_0000
	UINT32 pel_diff_v_th2_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_195_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E356C RO 0x0000_0000
	UINT32 pel_diff_v_th3_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_196_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3570 RO 0x0000_0000
	UINT32 pel_out_v_th0_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_197_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3574 RO 0x0000_0000
	UINT32 pel_out_v_th1_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_198_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3578 RO 0x0000_0000
	UINT32 pel_out_v_th2_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_199_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E357C RO 0x0000_0000
	UINT32 pel_out_v_th3_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_OLED_PHDR_CTRL_200_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3580 RO 0x0000_0000
	UINT32 pel_in_v_max                     :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 pel_out_v_max                    :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}O24A0_OLED_PHDR_CTRL_201_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3584 RW 0x0000_0000
	UINT32 reg_text_gain_en                 :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_text_luma_sel                :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_text_lsr_en                  :1;	//(8,RW,0x0) //
	UINT32 reg_text_osd_en                  :1;	//(9,RW,0x0) //
	UINT32 resvd2                           :6;
	UINT32 reg_text_master_gain             :8;	//(23:16,RW,0x00) //
	UINT32 resvd3                           :8;
	};
}O24A0_OLED_PHDR_CTRL_202_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3588 RW 0x0000_0000
	UINT32 reg_region_gain_ctrl             :32;	//(31:0,RW,0x0000_0000) //for debugging
	};
}O24A0_OLED_PHDR_CTRL_203_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E358C RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y00       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x00       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_204_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3590 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y01       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x01       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_205_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3594 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y02       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x02       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_206_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3598 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y03       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x03       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_207_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E359C RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y04       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x04       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_208_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35A0 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y05       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x05       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_209_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35A4 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y00        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x00        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_210_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35A8 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y01        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x01        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_211_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35AC RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y02        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x02        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_212_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35B0 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y03        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x03        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}O24A0_OLED_PHDR_CTRL_213_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35B4 RW 0x0000_0000
	UINT32 reg_bst_alpha_blend_en           :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_text_gain_dbg_en             :1;	//(4,RW,0x0) //1:text_gain out
	UINT32 resvd1                           :11;
	UINT32 reg_region_gain_en               :1;	//(16,RW,0x0) //
	UINT32 resvd2                           :7;
	UINT32 reg_region_gain_gain             :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_214_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35B8 RW 0x0000_0000
	UINT32 reg_region_gain_wid              :13;	//(12:0,RW,0x00) //
	UINT32 resvd                            :19;
	};
}O24A0_OLED_PHDR_CTRL_215_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35BC RW 0x0000_0000
	UINT32 reg_region_gain_hei              :13;	//(12:0,RW,0x0) //
	UINT32 resvd                            :19;
	};
}O24A0_OLED_PHDR_CTRL_216_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35C0 RW 0x0000_0000
	UINT32 reg_region_gain_ctrl             :32;	//(31:0,RW,0x0000_0000) //for debugging
	};
}O24A0_OLED_PHDR_CTRL_217_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35C4 RW 0x0000_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_218_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35C8 RW 0x0000_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_219_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35CC RW 0x0000_0000
	UINT32 reg_region_position_x1           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_220_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35D0 RW 0x0000_0000
	UINT32 reg_region_position_x3           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_221_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35D4 RW 0x0000_0000
	UINT32 reg_region_position_x5           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_222_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35D8 RW 0x0000_0000
	UINT32 reg_region_position_x7           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_223_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35DC RW 0x0000_0000
	UINT32 reg_region_position_y1           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_224_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35E0 RW 0x0000_0000
	UINT32 reg_region_position_y3           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_225_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35E4 RW 0x0000_0000
	UINT32 reg_region_position_y5           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}O24A0_OLED_PHDR_CTRL_226_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35E8 RW 0x0000_0000
	UINT32 reg_region_gain_11               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_21               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_31               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_41               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_227_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35EC RW 0x0000_0000
	UINT32 reg_region_gain_51               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_61               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_71               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_81               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_228_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35F0 RW 0x0000_0000
	UINT32 reg_region_gain_12               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_22               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_32               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_42               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_229_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35F4 RW 0x0000_0000
	UINT32 reg_region_gain_52               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_62               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_72               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_82               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_230_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35F8 RW 0x0000_0000
	UINT32 reg_region_gain_13               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_23               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_33               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_43               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_231_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E35FC RW 0x0000_0000
	UINT32 reg_region_gain_53               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_63               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_73               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_83               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_232_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3600 RW 0x0000_0000
	UINT32 reg_region_gain_14               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_24               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_34               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_44               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_233_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3604 RW 0x0000_0000
	UINT32 reg_region_gain_54               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_64               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_74               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_84               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_234_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3608 RW 0x0000_0000
	UINT32 reg_region_gain_15               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_25               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_35               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_45               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_235_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E360C RW 0x0000_0000
	UINT32 reg_region_gain_55               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_65               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_75               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_85               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_236_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3610 RW 0x0000_0000
	UINT32 reg_region_gain_16               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_26               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_36               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_46               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_237_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3614 RW 0x0000_0000
	UINT32 reg_region_gain_56               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_66               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_76               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_86               :8;	//(31:24,RW,0x00) //
	};
}O24A0_OLED_PHDR_CTRL_238_T;

typedef struct {
	O24A0_OLED_OLED_CTRL_00_T                      addr_oled_ctrl_00;	//0xCC8E3000
	O24A0_OLED_OLED_CTRL_01_T                      addr_oled_ctrl_01;	//0xCC8E3004
	O24A0_OLED_OLED_CTRL_02_T                      addr_oled_ctrl_02;	//0xCC8E3008
	UINT32                                                    reserved0;	//0xCC8E300C
	O24A0_OLED_FSW_CTRL_00_T                        addr_fsw_ctrl_00;	//0xCC8E3010
	O24A0_OLED_FSW_CTRL_01_T                        addr_fsw_ctrl_01;	//0xCC8E3014
	O24A0_OLED_FSW_CTRL_02_T                        addr_fsw_ctrl_02;	//0xCC8E3018
	O24A0_OLED_FSW_CTRL_03_T                        addr_fsw_ctrl_03;	//0xCC8E301C
	O24A0_OLED_CPC_CTRL_00_T                        addr_cpc_ctrl_00;	//0xCC8E3020
	O24A0_OLED_CPC_CTRL_01_T                        addr_cpc_ctrl_01;	//0xCC8E3024
	O24A0_OLED_CPC_CTRL_02_T                        addr_cpc_ctrl_02;	//0xCC8E3028
	O24A0_OLED_CPC_CTRL_03_T                        addr_cpc_ctrl_03;	//0xCC8E302C
	O24A0_OLED_CPC_CTRL_04_T                        addr_cpc_ctrl_04;	//0xCC8E3030
	O24A0_OLED_CPC_CTRL_05_T                        addr_cpc_ctrl_05;	//0xCC8E3034
	O24A0_OLED_CPC_CTRL_06_T                        addr_cpc_ctrl_06;	//0xCC8E3038
	O24A0_OLED_CPC_CTRL_07_T                        addr_cpc_ctrl_07;	//0xCC8E303C
	O24A0_OLED_CPC_CTRL_08_T                        addr_cpc_ctrl_08;	//0xCC8E3040
	O24A0_OLED_CPC_CTRL_09_T                        addr_cpc_ctrl_09;	//0xCC8E3044
	O24A0_OLED_CPC_CTRL_10_T                        addr_cpc_ctrl_10;	//0xCC8E3048
	O24A0_OLED_CPC_CTRL_11_T                        addr_cpc_ctrl_11;	//0xCC8E304C
	O24A0_OLED_CPC_CTRL_12_T                        addr_cpc_ctrl_12;	//0xCC8E3050
	O24A0_OLED_CPC_CTRL_13_T                        addr_cpc_ctrl_13;	//0xCC8E3054
	O24A0_OLED_CPC_CTRL_14_T                        addr_cpc_ctrl_14;	//0xCC8E3058
	O24A0_OLED_CPC_CTRL_15_T                        addr_cpc_ctrl_15;	//0xCC8E305C
	O24A0_OLED_CPC_CTRL_16_T                        addr_cpc_ctrl_16;	//0xCC8E3060
	O24A0_OLED_CPC_CTRL_17_T                        addr_cpc_ctrl_17;	//0xCC8E3064
	O24A0_OLED_CPC_CTRL_18_T                        addr_cpc_ctrl_18;	//0xCC8E3068
	O24A0_OLED_CPC_CTRL_19_T                        addr_cpc_ctrl_19;	//0xCC8E306C
	O24A0_OLED_CPC_CTRL_20_T                        addr_cpc_ctrl_20;	//0xCC8E3070
	O24A0_OLED_CPC_CTRL_21_T                        addr_cpc_ctrl_21;	//0xCC8E3074
	O24A0_OLED_CPC_CTRL_22_T                        addr_cpc_ctrl_22;	//0xCC8E3078
	UINT32                                                    reserved1;	//0xCC8E307C
	O24A0_OLED_PHDR_CTRL_000_T                    addr_phdr_ctrl_000;	//0xCC8E3080
	O24A0_OLED_PHDR_CTRL_001_T                    addr_phdr_ctrl_001;	//0xCC8E3084
	O24A0_OLED_PHDR_CTRL_002_T                    addr_phdr_ctrl_002;	//0xCC8E3088
	O24A0_OLED_PHDR_CTRL_003_T                    addr_phdr_ctrl_003;	//0xCC8E308C
	O24A0_OLED_PHDR_CTRL_004_T                    addr_phdr_ctrl_004;	//0xCC8E3090
	O24A0_OLED_PHDR_CTRL_005_T                    addr_phdr_ctrl_005;	//0xCC8E3094
	O24A0_OLED_PHDR_CTRL_006_T                    addr_phdr_ctrl_006;	//0xCC8E3098
	O24A0_OLED_PHDR_CTRL_007_T                    addr_phdr_ctrl_007;	//0xCC8E309C
	O24A0_OLED_PHDR_CTRL_008_T                    addr_phdr_ctrl_008;	//0xCC8E30A0
	O24A0_OLED_PHDR_CTRL_009_T                    addr_phdr_ctrl_009;	//0xCC8E30A4
	O24A0_OLED_PHDR_CTRL_010_T                    addr_phdr_ctrl_010;	//0xCC8E30A8
	O24A0_OLED_PHDR_CTRL_011_T                    addr_phdr_ctrl_011;	//0xCC8E30AC
	O24A0_OLED_PHDR_CTRL_012_T                    addr_phdr_ctrl_012;	//0xCC8E30B0
	O24A0_OLED_PHDR_CTRL_013_T                    addr_phdr_ctrl_013;	//0xCC8E30B4
	O24A0_OLED_PHDR_CTRL_014_T                    addr_phdr_ctrl_014;	//0xCC8E30B8
	O24A0_OLED_PHDR_CTRL_015_T                    addr_phdr_ctrl_015;	//0xCC8E30BC
	O24A0_OLED_PHDR_CTRL_016_T                    addr_phdr_ctrl_016;	//0xCC8E30C0
	O24A0_OLED_PHDR_CTRL_017_T                    addr_phdr_ctrl_017;	//0xCC8E30C4
	O24A0_OLED_PHDR_CTRL_018_T                    addr_phdr_ctrl_018;	//0xCC8E30C8
	O24A0_OLED_PHDR_CTRL_019_T                    addr_phdr_ctrl_019;	//0xCC8E30CC
	O24A0_OLED_PHDR_CTRL_020_T                    addr_phdr_ctrl_020;	//0xCC8E30D0
	O24A0_OLED_PHDR_CTRL_021_T                    addr_phdr_ctrl_021;	//0xCC8E30D4
	O24A0_OLED_PHDR_CTRL_022_T                    addr_phdr_ctrl_022;	//0xCC8E30D8
	O24A0_OLED_PHDR_CTRL_023_T                    addr_phdr_ctrl_023;	//0xCC8E30DC
	O24A0_OLED_PHDR_CTRL_024_T                    addr_phdr_ctrl_024;	//0xCC8E30E0
	O24A0_OLED_PHDR_CTRL_025_T                    addr_phdr_ctrl_025;	//0xCC8E30E4
	O24A0_OLED_PHDR_CTRL_026_T                    addr_phdr_ctrl_026;	//0xCC8E30E8
	O24A0_OLED_PHDR_CTRL_027_T                    addr_phdr_ctrl_027;	//0xCC8E30EC
	O24A0_OLED_PHDR_CTRL_028_T                    addr_phdr_ctrl_028;	//0xCC8E30F0
	O24A0_OLED_PHDR_CTRL_029_T                    addr_phdr_ctrl_029;	//0xCC8E30F4
	O24A0_OLED_PHDR_CTRL_030_T                    addr_phdr_ctrl_030;	//0xCC8E30F8
	O24A0_OLED_PHDR_CTRL_031_T                    addr_phdr_ctrl_031;	//0xCC8E30FC
	O24A0_OLED_PHDR_CTRL_032_T                    addr_phdr_ctrl_032;	//0xCC8E3100
	O24A0_OLED_PHDR_CTRL_033_T                    addr_phdr_ctrl_033;	//0xCC8E3104
	O24A0_OLED_PHDR_CTRL_034_T                    addr_phdr_ctrl_034;	//0xCC8E3108
	O24A0_OLED_PHDR_CTRL_035_T                    addr_phdr_ctrl_035;	//0xCC8E310C
	O24A0_OLED_PHDR_CTRL_036_T                    addr_phdr_ctrl_036;	//0xCC8E3110
	O24A0_OLED_PHDR_CTRL_037_T                    addr_phdr_ctrl_037;	//0xCC8E3114
	O24A0_OLED_PHDR_CTRL_038_T                    addr_phdr_ctrl_038;	//0xCC8E3118
	O24A0_OLED_PHDR_CTRL_039_T                    addr_phdr_ctrl_039;	//0xCC8E311C
	O24A0_OLED_PHDR_CTRL_040_T                    addr_phdr_ctrl_040;	//0xCC8E3120
	O24A0_OLED_PHDR_CTRL_041_T                    addr_phdr_ctrl_041;	//0xCC8E3124
	O24A0_OLED_PHDR_CTRL_042_T                    addr_phdr_ctrl_042;	//0xCC8E3128
	O24A0_OLED_PHDR_CTRL_043_T                    addr_phdr_ctrl_043;	//0xCC8E312C
	O24A0_OLED_PHDR_CTRL_044_T                    addr_phdr_ctrl_044;	//0xCC8E3130
	O24A0_OLED_PHDR_CTRL_045_T                    addr_phdr_ctrl_045;	//0xCC8E3134
	O24A0_OLED_PHDR_CTRL_046_T                    addr_phdr_ctrl_046;	//0xCC8E3138
	O24A0_OLED_PHDR_CTRL_047_T                    addr_phdr_ctrl_047;	//0xCC8E313C
	O24A0_OLED_PHDR_CTRL_048_T                    addr_phdr_ctrl_048;	//0xCC8E3140
	O24A0_OLED_PHDR_CTRL_049_T                    addr_phdr_ctrl_049;	//0xCC8E3144
	O24A0_OLED_PHDR_CTRL_050_T                    addr_phdr_ctrl_050;	//0xCC8E3148
	O24A0_OLED_PHDR_CTRL_051_T                    addr_phdr_ctrl_051;	//0xCC8E314C
	O24A0_OLED_PHDR_CTRL_052_T                    addr_phdr_ctrl_052;	//0xCC8E3150
	O24A0_OLED_PHDR_CTRL_053_T                    addr_phdr_ctrl_053;	//0xCC8E3154
	O24A0_OLED_PHDR_CTRL_054_T                    addr_phdr_ctrl_054;	//0xCC8E3158
	O24A0_OLED_PHDR_CTRL_055_T                    addr_phdr_ctrl_055;	//0xCC8E315C
	O24A0_OLED_PHDR_CTRL_056_T                    addr_phdr_ctrl_056;	//0xCC8E3160
	O24A0_OLED_PHDR_CTRL_057_T                    addr_phdr_ctrl_057;	//0xCC8E3164
	O24A0_OLED_PHDR_CTRL_058_T                    addr_phdr_ctrl_058;	//0xCC8E3168
	O24A0_OLED_PHDR_CTRL_059_T                    addr_phdr_ctrl_059;	//0xCC8E316C
	O24A0_OLED_PHDR_CTRL_060_T                    addr_phdr_ctrl_060;	//0xCC8E3170
	O24A0_OLED_PHDR_CTRL_061_T                    addr_phdr_ctrl_061;	//0xCC8E3174
	O24A0_OLED_PHDR_CTRL_062_T                    addr_phdr_ctrl_062;	//0xCC8E3178
	O24A0_OLED_PHDR_CTRL_063_T                    addr_phdr_ctrl_063;	//0xCC8E317C
	O24A0_OLED_PHDR_CTRL_064_T                    addr_phdr_ctrl_064;	//0xCC8E3180
	O24A0_OLED_PHDR_CTRL_065_T                    addr_phdr_ctrl_065;	//0xCC8E3184
	O24A0_OLED_PHDR_CTRL_066_T                    addr_phdr_ctrl_066;	//0xCC8E3188
	O24A0_OLED_PHDR_CTRL_067_T                    addr_phdr_ctrl_067;	//0xCC8E318C
	O24A0_OLED_PHDR_CTRL_068_T                    addr_phdr_ctrl_068;	//0xCC8E3190
	O24A0_OLED_PHDR_CTRL_069_T                    addr_phdr_ctrl_069;	//0xCC8E3194
	O24A0_OLED_PHDR_CTRL_070_T                    addr_phdr_ctrl_070;	//0xCC8E3198
	O24A0_OLED_PHDR_CTRL_071_T                    addr_phdr_ctrl_071;	//0xCC8E319C
	O24A0_OLED_PHDR_CTRL_072_T                    addr_phdr_ctrl_072;	//0xCC8E31A0
	O24A0_OLED_PHDR_CTRL_073_T                    addr_phdr_ctrl_073;	//0xCC8E31A4
	O24A0_OLED_PHDR_CTRL_074_T                    addr_phdr_ctrl_074;	//0xCC8E31A8
	O24A0_OLED_PHDR_CTRL_075_T                    addr_phdr_ctrl_075;	//0xCC8E31AC
	O24A0_OLED_PHDR_CTRL_076_T                    addr_phdr_ctrl_076;	//0xCC8E31B0
	O24A0_OLED_PHDR_CTRL_077_T                    addr_phdr_ctrl_077;	//0xCC8E31B4
	O24A0_OLED_PHDR_CTRL_078_T                    addr_phdr_ctrl_078;	//0xCC8E31B8
	O24A0_OLED_PHDR_CTRL_079_T                    addr_phdr_ctrl_079;	//0xCC8E31BC
	O24A0_OLED_PHDR_CTRL_080_T                    addr_phdr_ctrl_080;	//0xCC8E31C0
	O24A0_OLED_PHDR_CTRL_081_T                    addr_phdr_ctrl_081;	//0xCC8E31C4
	O24A0_OLED_PHDR_CTRL_082_T                    addr_phdr_ctrl_082;	//0xCC8E31C8
	O24A0_OLED_PHDR_CTRL_083_T                    addr_phdr_ctrl_083;	//0xCC8E31CC
	O24A0_OLED_PHDR_CTRL_084_T                    addr_phdr_ctrl_084;	//0xCC8E31D0
	O24A0_OLED_PHDR_CTRL_085_T                    addr_phdr_ctrl_085;	//0xCC8E31D4
	O24A0_OLED_PHDR_CTRL_086_T                    addr_phdr_ctrl_086;	//0xCC8E31D8
	O24A0_OLED_PHDR_CTRL_087_T                    addr_phdr_ctrl_087;	//0xCC8E31DC
	O24A0_OLED_PHDR_CTRL_088_T                    addr_phdr_ctrl_088;	//0xCC8E31E0
	O24A0_OLED_PHDR_CTRL_089_T                    addr_phdr_ctrl_089;	//0xCC8E31E4
	O24A0_OLED_PHDR_CTRL_090_T                    addr_phdr_ctrl_090;	//0xCC8E31E8
	O24A0_OLED_PHDR_CTRL_091_T                    addr_phdr_ctrl_091;	//0xCC8E31EC
	O24A0_OLED_PHDR_CTRL_092_T                    addr_phdr_ctrl_092;	//0xCC8E31F0
	O24A0_OLED_PHDR_CTRL_093_T                    addr_phdr_ctrl_093;	//0xCC8E31F4
	O24A0_OLED_PHDR_CTRL_094_T                    addr_phdr_ctrl_094;	//0xCC8E31F8
	O24A0_OLED_PHDR_CTRL_095_T                    addr_phdr_ctrl_095;	//0xCC8E31FC
	O24A0_OLED_PHDR_CTRL_096_T                    addr_phdr_ctrl_096;	//0xCC8E3200
	O24A0_OLED_PHDR_CTRL_097_T                    addr_phdr_ctrl_097;	//0xCC8E3204
	O24A0_OLED_PHDR_CTRL_098_T                    addr_phdr_ctrl_098;	//0xCC8E3208
	O24A0_OLED_PHDR_CTRL_099_T                    addr_phdr_ctrl_099;	//0xCC8E320C
	O24A0_OLED_PHDR_CTRL_100_T                    addr_phdr_ctrl_100;	//0xCC8E3210
	O24A0_OLED_PHDR_CTRL_101_T                    addr_phdr_ctrl_101;	//0xCC8E3214
	O24A0_OLED_PHDR_CTRL_102_T                    addr_phdr_ctrl_102;	//0xCC8E3218
	O24A0_OLED_PHDR_CTRL_103_T                    addr_phdr_ctrl_103;	//0xCC8E321C
	O24A0_OLED_PHDR_CTRL_104_T                    addr_phdr_ctrl_104;	//0xCC8E3220
	O24A0_OLED_PHDR_CTRL_105_T                    addr_phdr_ctrl_105;	//0xCC8E3224
	O24A0_OLED_PHDR_CTRL_106_T                    addr_phdr_ctrl_106;	//0xCC8E3228
	O24A0_OLED_PHDR_CTRL_107_T                    addr_phdr_ctrl_107;	//0xCC8E322C
	O24A0_OLED_PHDR_CTRL_108_T                    addr_phdr_ctrl_108;	//0xCC8E3230
	O24A0_OLED_PHDR_CTRL_109_T                    addr_phdr_ctrl_109;	//0xCC8E3234
	O24A0_OLED_PHDR_CTRL_110_T                    addr_phdr_ctrl_110;	//0xCC8E3238
	O24A0_OLED_PHDR_CTRL_111_T                    addr_phdr_ctrl_111;	//0xCC8E323C
	O24A0_OLED_PHDR_CTRL_112_T                    addr_phdr_ctrl_112;	//0xCC8E3240
	O24A0_OLED_PHDR_CTRL_113_T                    addr_phdr_ctrl_113;	//0xCC8E3244
	O24A0_OLED_PHDR_CTRL_114_T                    addr_phdr_ctrl_114;	//0xCC8E3248
	O24A0_OLED_PHDR_CTRL_115_T                    addr_phdr_ctrl_115;	//0xCC8E324C
	O24A0_OLED_PHDR_CTRL_116_T                    addr_phdr_ctrl_116;	//0xCC8E3250
	O24A0_OLED_PHDR_CTRL_117_T                    addr_phdr_ctrl_117;	//0xCC8E3254
	O24A0_OLED_PHDR_CTRL_118_T                    addr_phdr_ctrl_118;	//0xCC8E3258
	O24A0_OLED_PHDR_CTRL_119_T                    addr_phdr_ctrl_119;	//0xCC8E325C
	O24A0_OLED_PHDR_CTRL_120_T                    addr_phdr_ctrl_120;	//0xCC8E3260
	O24A0_OLED_PHDR_CTRL_121_T                    addr_phdr_ctrl_121;	//0xCC8E3264
	O24A0_OLED_PHDR_CTRL_122_T                    addr_phdr_ctrl_122;	//0xCC8E3268
	O24A0_OLED_PHDR_CTRL_123_T                    addr_phdr_ctrl_123;	//0xCC8E326C
	O24A0_OLED_PHDR_CTRL_124_T                    addr_phdr_ctrl_124;	//0xCC8E3270
	O24A0_OLED_PHDR_CTRL_125_T                    addr_phdr_ctrl_125;	//0xCC8E3274
	O24A0_OLED_PHDR_CTRL_126_T                    addr_phdr_ctrl_126;	//0xCC8E3278
	O24A0_OLED_PHDR_CTRL_127_T                    addr_phdr_ctrl_127;	//0xCC8E327C
	O24A0_OLED_PHDR_CTRL_128_T                    addr_phdr_ctrl_128;	//0xCC8E3280
	O24A0_OLED_PHDR_CTRL_129_T                    addr_phdr_ctrl_129;	//0xCC8E3284
	O24A0_OLED_PHDR_CTRL_130_T                    addr_phdr_ctrl_130;	//0xCC8E3288
	O24A0_OLED_PHDR_CTRL_131_T                    addr_phdr_ctrl_131;	//0xCC8E328C
	O24A0_OLED_PHDR_CTRL_132_T                    addr_phdr_ctrl_132;	//0xCC8E3290
	O24A0_OLED_PHDR_CTRL_133_T                    addr_phdr_ctrl_133;	//0xCC8E3294
	O24A0_OLED_PHDR_CTRL_134_T                    addr_phdr_ctrl_134;	//0xCC8E3298
	O24A0_OLED_PHDR_CTRL_135_T                    addr_phdr_ctrl_135;	//0xCC8E329C
	O24A0_OLED_PHDR_CTRL_136_T                    addr_phdr_ctrl_136;	//0xCC8E32A0
	O24A0_OLED_PHDR_CTRL_137_T                    addr_phdr_ctrl_137;	//0xCC8E32A4
	O24A0_OLED_PHDR_CTRL_138_T                    addr_phdr_ctrl_138;	//0xCC8E32A8
	O24A0_OLED_PHDR_CTRL_139_T                    addr_phdr_ctrl_139;	//0xCC8E32AC
	O24A0_OLED_PHDR_CTRL_140_T                    addr_phdr_ctrl_140;	//0xCC8E32B0
	O24A0_OLED_PHDR_CTRL_141_T                    addr_phdr_ctrl_141;	//0xCC8E32B4
	O24A0_OLED_PHDR_CTRL_142_T                    addr_phdr_ctrl_142;	//0xCC8E32B8
	O24A0_OLED_PHDR_CTRL_143_T                    addr_phdr_ctrl_143;	//0xCC8E32BC
	O24A0_OLED_PHDR_CTRL_144_T                    addr_phdr_ctrl_144;	//0xCC8E32C0
	O24A0_OLED_PHDR_CTRL_145_T                    addr_phdr_ctrl_145;	//0xCC8E32C4
	O24A0_OLED_PHDR_CTRL_146_T                    addr_phdr_ctrl_146;	//0xCC8E32C8
	O24A0_OLED_PHDR_CTRL_147_T                    addr_phdr_ctrl_147;	//0xCC8E32CC
	O24A0_OLED_PHDR_CTRL_148_T                    addr_phdr_ctrl_148;	//0xCC8E32D0
	O24A0_OLED_PHDR_CTRL_149_T                    addr_phdr_ctrl_149;	//0xCC8E32D4
	O24A0_OLED_PHDR_CTRL_150_T                    addr_phdr_ctrl_150;	//0xCC8E32D8
	O24A0_OLED_PHDR_CTRL_151_T                    addr_phdr_ctrl_151;	//0xCC8E32DC
	O24A0_OLED_PHDR_CTRL_152_T                    addr_phdr_ctrl_152;	//0xCC8E32E0
	O24A0_OLED_PHDR_CTRL_153_T                    addr_phdr_ctrl_153;	//0xCC8E32E4
	O24A0_OLED_PHDR_CTRL_154_T                    addr_phdr_ctrl_154;	//0xCC8E32E8
	O24A0_OLED_PHDR_CTRL_155_T                    addr_phdr_ctrl_155;	//0xCC8E32EC
	O24A0_OLED_PHDR_CTRL_156_T                    addr_phdr_ctrl_156;	//0xCC8E32F0
	O24A0_OLED_PHDR_CTRL_157_T                    addr_phdr_ctrl_157;	//0xCC8E32F4
	O24A0_OLED_PHDR_CTRL_158_T                    addr_phdr_ctrl_158;	//0xCC8E32F8
	O24A0_OLED_PHDR_CTRL_159_T                    addr_phdr_ctrl_159;	//0xCC8E32FC
	O24A0_OLED_PHDR_CTRL_160_T                    addr_phdr_ctrl_160;	//0xCC8E3300
	O24A0_OLED_PHDR_CTRL_161_T                    addr_phdr_ctrl_161;	//0xCC8E3304
	O24A0_OLED_PHDR_CTRL_162_T                    addr_phdr_ctrl_162;	//0xCC8E3308
	O24A0_OLED_PHDR_CTRL_163_T                    addr_phdr_ctrl_163;	//0xCC8E330C
	O24A0_OLED_PHDR_CTRL_164_T                    addr_phdr_ctrl_164;	//0xCC8E3310
	O24A0_OLED_PHDR_CTRL_165_T                    addr_phdr_ctrl_165;	//0xCC8E3314
	O24A0_OLED_PHDR_CTRL_166_T                    addr_phdr_ctrl_166;	//0xCC8E3318
	O24A0_OLED_PHDR_CTRL_167_T                    addr_phdr_ctrl_167;	//0xCC8E331C
	O24A0_OLED_PHDR_CTRL_168_T                    addr_phdr_ctrl_168;	//0xCC8E3320
	O24A0_OLED_PHDR_CTRL_169_T                    addr_phdr_ctrl_169;	//0xCC8E3324
	O24A0_OLED_PHDR_CTRL_170_T                    addr_phdr_ctrl_170;	//0xCC8E3328
	O24A0_OLED_PHDR_CTRL_171_T                    addr_phdr_ctrl_171;	//0xCC8E332C
	O24A0_OLED_PHDR_CTRL_172_T                    addr_phdr_ctrl_172;	//0xCC8E3330
	O24A0_OLED_PHDR_CTRL_173_T                    addr_phdr_ctrl_173;	//0xCC8E3334
	O24A0_OLED_PHDR_CTRL_174_T                    addr_phdr_ctrl_174;	//0xCC8E3338
	O24A0_OLED_PHDR_CTRL_175_T                    addr_phdr_ctrl_175;	//0xCC8E333C
	O24A0_OLED_PHDR_CTRL_176_T                    addr_phdr_ctrl_176;	//0xCC8E3340
	O24A0_OLED_PHDR_CTRL_177_T                    addr_phdr_ctrl_177;	//0xCC8E3344
	O24A0_OLED_PHDR_CTRL_178_T                    addr_phdr_ctrl_178;	//0xCC8E3348
	O24A0_OLED_PHDR_CTRL_179_T                    addr_phdr_ctrl_179;	//0xCC8E334C
	O24A0_OLED_PHDR_CTRL_180_T                    addr_phdr_ctrl_180;	//0xCC8E3350
	O24A0_OLED_PHDR_CTRL_181_T                    addr_phdr_ctrl_181;	//0xCC8E3354
	O24A0_OLED_PHDR_CTRL_182_T                    addr_phdr_ctrl_182;	//0xCC8E3358
	O24A0_OLED_PHDR_CTRL_183_T                    addr_phdr_ctrl_183;	//0xCC8E335C
	O24A0_OLED_PHDR_CTRL_184_T                    addr_phdr_ctrl_184;	//0xCC8E3360
	O24A0_OLED_PHDR_CTRL_185_T                    addr_phdr_ctrl_185;	//0xCC8E3364
	O24A0_OLED_PHDR_CTRL_186_T                    addr_phdr_ctrl_186;	//0xCC8E3368
	O24A0_OLED_PHDR_CTRL_187_T                    addr_phdr_ctrl_187;	//0xCC8E336C
	O24A0_OLED_PHDR_CTRL_188_T                    addr_phdr_ctrl_188;	//0xCC8E3370
	O24A0_OLED_PHDR_CTRL_189_T                    addr_phdr_ctrl_189;	//0xCC8E3374
	O24A0_OLED_PHDR_CTRL_190_T                    addr_phdr_ctrl_190;	//0xCC8E3378
	O24A0_OLED_PHDR_CTRL_191_T                    addr_phdr_ctrl_191;	//0xCC8E337C
	O24A0_OLED_PHDR_CTRL_192_T                    addr_phdr_ctrl_192;	//0xCC8E3380
	UINT32                                                    reserved2;	//0xCC8E3384
	UINT32                                                    reserved3;	//0xCC8E3388
	UINT32                                                    reserved4;	//0xCC8E338C
	O24A0_OLED_RGB2YC_CTRL_00_T                  addr_rgb2yc_ctrl_00;	//0xCC8E3390
	O24A0_OLED_RGB2YC_CTRL_01_T                  addr_rgb2yc_ctrl_01;	//0xCC8E3394
	O24A0_OLED_RGB2YC_CTRL_02_T                  addr_rgb2yc_ctrl_02;	//0xCC8E3398
	O24A0_OLED_RGB2YC_CTRL_03_T                  addr_rgb2yc_ctrl_03;	//0xCC8E339C
	O24A0_OLED_RGB2YC_CTRL_04_T                  addr_rgb2yc_ctrl_04;	//0xCC8E33A0
	O24A0_OLED_RGB2YC_CTRL_05_T                  addr_rgb2yc_ctrl_05;	//0xCC8E33A4
	O24A0_OLED_RGB2YC_CTRL_06_T                  addr_rgb2yc_ctrl_06;	//0xCC8E33A8
	O24A0_OLED_RGB2YC_CTRL_07_T                  addr_rgb2yc_ctrl_07;	//0xCC8E33AC
	O24A0_OLED_RGB2YC_CTRL_08_T                  addr_rgb2yc_ctrl_08;	//0xCC8E33B0
	O24A0_OLED_RGB2YC_CTRL_09_T                  addr_rgb2yc_ctrl_09;	//0xCC8E33B4
	O24A0_OLED_RGB2YC_CTRL_10_T                  addr_rgb2yc_ctrl_10;	//0xCC8E33B8
	O24A0_OLED_RGB2YC_CTRL_11_T                  addr_rgb2yc_ctrl_11;	//0xCC8E33BC
	O24A0_OLED_YC2RGB_CTRL_00_T                  addr_yc2rgb_ctrl_00;	//0xCC8E33C0
	O24A0_OLED_YC2RGB_CTRL_01_T                  addr_yc2rgb_ctrl_01;	//0xCC8E33C4
	O24A0_OLED_YC2RGB_CTRL_02_T                  addr_yc2rgb_ctrl_02;	//0xCC8E33C8
	O24A0_OLED_YC2RGB_CTRL_03_T                  addr_yc2rgb_ctrl_03;	//0xCC8E33CC
	O24A0_OLED_YC2RGB_CTRL_04_T                  addr_yc2rgb_ctrl_04;	//0xCC8E33D0
	O24A0_OLED_YC2RGB_CTRL_05_T                  addr_yc2rgb_ctrl_05;	//0xCC8E33D4
	O24A0_OLED_YC2RGB_CTRL_06_T                  addr_yc2rgb_ctrl_06;	//0xCC8E33D8
	O24A0_OLED_YC2RGB_CTRL_07_T                  addr_yc2rgb_ctrl_07;	//0xCC8E33DC
	O24A0_OLED_YC2RGB_CTRL_08_T                  addr_yc2rgb_ctrl_08;	//0xCC8E33E0
	O24A0_OLED_YC2RGB_CTRL_09_T                  addr_yc2rgb_ctrl_09;	//0xCC8E33E4
	O24A0_OLED_YC2RGB_CTRL_10_T                  addr_yc2rgb_ctrl_10;	//0xCC8E33E8
	O24A0_OLED_YC2RGB_CTRL_11_T                  addr_yc2rgb_ctrl_11;	//0xCC8E33EC
	UINT32                                                    reserved5;	//0xCC8E33F0
	UINT32                                                    reserved6;	//0xCC8E33F4
	UINT32                                                    reserved7;	//0xCC8E33F8
	UINT32                                                    reserved8;	//0xCC8E33FC
	O24A0_OLED_OAPL_CTRL_00_T                      addr_oapl_ctrl_00;	//0xCC8E3400
	O24A0_OLED_OAPL_CTRL_01_T                      addr_oapl_ctrl_01;	//0xCC8E3404
	O24A0_OLED_OAPL_CTRL_02_T                      addr_oapl_ctrl_02;	//0xCC8E3408
	O24A0_OLED_OAPL_CTRL_03_T                      addr_oapl_ctrl_03;	//0xCC8E340C
	O24A0_OLED_OAPL_CTRL_04_T                      addr_oapl_ctrl_04;	//0xCC8E3410
	O24A0_OLED_OAPL_CTRL_05_T                      addr_oapl_ctrl_05;	//0xCC8E3414
	O24A0_OLED_OAPL_CTRL_06_T                      addr_oapl_ctrl_06;	//0xCC8E3418
	O24A0_OLED_OAPL_CTRL_07_T                      addr_oapl_ctrl_07;	//0xCC8E341C
	O24A0_OLED_OAPL_CTRL_08_T                      addr_oapl_ctrl_08;	//0xCC8E3420
	O24A0_OLED_OAPL_CTRL_09_T                      addr_oapl_ctrl_09;	//0xCC8E3424
	O24A0_OLED_OAPL_CTRL_10_T                      addr_oapl_ctrl_10;	//0xCC8E3428
	O24A0_OLED_OAPL_CTRL_11_T                      addr_oapl_ctrl_11;	//0xCC8E342C
	O24A0_OLED_OAPL_CTRL_12_T                      addr_oapl_ctrl_12;	//0xCC8E3430
	O24A0_OLED_OAPL_CTRL_13_T                      addr_oapl_ctrl_13;	//0xCC8E3434
	O24A0_OLED_OAPL_CTRL_14_T                      addr_oapl_ctrl_14;	//0xCC8E3438
	O24A0_OLED_OAPL_CTRL_15_T                      addr_oapl_ctrl_15;	//0xCC8E343C
	O24A0_OLED_OAPL_CTRL_16_T                      addr_oapl_ctrl_16;	//0xCC8E3440
	O24A0_OLED_OAPL_CTRL_17_T                      addr_oapl_ctrl_17;	//0xCC8E3444
	O24A0_OLED_OAPL_CTRL_18_T                      addr_oapl_ctrl_18;	//0xCC8E3448
	O24A0_OLED_OAPL_CTRL_19_T                      addr_oapl_ctrl_19;	//0xCC8E344C
	O24A0_OLED_OAPL_CTRL_20_T                      addr_oapl_ctrl_20;	//0xCC8E3450
	O24A0_OLED_OAPL_CTRL_21_T                      addr_oapl_ctrl_21;	//0xCC8E3454
	O24A0_OLED_OAPL_CTRL_22_T                      addr_oapl_ctrl_22;	//0xCC8E3458
	O24A0_OLED_OAPL_CTRL_23_T                      addr_oapl_ctrl_23;	//0xCC8E345C
	O24A0_OLED_OAPL_CTRL_24_T                      addr_oapl_ctrl_24;	//0xCC8E3460
	O24A0_OLED_OAPL_CTRL_25_T                      addr_oapl_ctrl_25;	//0xCC8E3464
	O24A0_OLED_OAPL_CTRL_26_T                      addr_oapl_ctrl_26;	//0xCC8E3468
	O24A0_OLED_OAPL_CTRL_27_T                      addr_oapl_ctrl_27;	//0xCC8E346C
	O24A0_OLED_OAPL_CTRL_28_T                      addr_oapl_ctrl_28;	//0xCC8E3470
	O24A0_OLED_OAPL_CTRL_29_T                      addr_oapl_ctrl_29;	//0xCC8E3474
	O24A0_OLED_OAPL_CTRL_30_T                      addr_oapl_ctrl_30;	//0xCC8E3478
	O24A0_OLED_OAPL_CTRL_31_T                      addr_oapl_ctrl_31;	//0xCC8E347C
	O24A0_OLED_OAPL_CTRL_32_T                      addr_oapl_ctrl_32;	//0xCC8E3480
	O24A0_OLED_OAPL_CTRL_33_T                      addr_oapl_ctrl_33;	//0xCC8E3484
	O24A0_OLED_OAPL_CTRL_34_T                      addr_oapl_ctrl_34;	//0xCC8E3488
	O24A0_OLED_OAPL_CTRL_35_T                      addr_oapl_ctrl_35;	//0xCC8E348C
	O24A0_OLED_OAPL_CTRL_36_T                      addr_oapl_ctrl_36;	//0xCC8E3490
	O24A0_OLED_OAPL_CTRL_37_T                      addr_oapl_ctrl_37;	//0xCC8E3494
	O24A0_OLED_OAPL_CTRL_38_T                      addr_oapl_ctrl_38;	//0xCC8E3498
	O24A0_OLED_OAPL_CTRL_39_T                      addr_oapl_ctrl_39;	//0xCC8E349C
	O24A0_OLED_OAPL_CTRL_40_T                      addr_oapl_ctrl_40;	//0xCC8E34A0
	O24A0_OLED_OAPL_CTRL_41_T                      addr_oapl_ctrl_41;	//0xCC8E34A4
	O24A0_OLED_OAPL_CTRL_42_T                      addr_oapl_ctrl_42;	//0xCC8E34A8
	O24A0_OLED_OAPL_CTRL_43_T                      addr_oapl_ctrl_43;	//0xCC8E34AC
	O24A0_OLED_OAPL_CTRL_44_T                      addr_oapl_ctrl_44;	//0xCC8E34B0
	O24A0_OLED_OAPL_CTRL_45_T                      addr_oapl_ctrl_45;	//0xCC8E34B4
	O24A0_OLED_OAPL_CTRL_46_T                      addr_oapl_ctrl_46;	//0xCC8E34B8
	O24A0_OLED_OAPL_CTRL_47_T                      addr_oapl_ctrl_47;	//0xCC8E34BC
	O24A0_OLED_OAPL_CTRL_48_T                      addr_oapl_ctrl_48;	//0xCC8E34C0
	O24A0_OLED_OAPL_CTRL_49_T                      addr_oapl_ctrl_49;	//0xCC8E34C4
	O24A0_OLED_OAPL_CTRL_50_T                      addr_oapl_ctrl_50;	//0xCC8E34C8
	O24A0_OLED_OAPL_CTRL_51_T                      addr_oapl_ctrl_51;	//0xCC8E34CC
	O24A0_OLED_OAPL_CTRL_52_T                      addr_oapl_ctrl_52;	//0xCC8E34D0
	O24A0_OLED_OAPL_CTRL_53_T                      addr_oapl_ctrl_53;	//0xCC8E34D4
	O24A0_OLED_OAPL_CTRL_54_T                      addr_oapl_ctrl_54;	//0xCC8E34D8
	O24A0_OLED_OAPL_CTRL_55_T                      addr_oapl_ctrl_55;	//0xCC8E34DC
	O24A0_OLED_OAPL_CTRL_56_T                      addr_oapl_ctrl_56;	//0xCC8E34E0
	O24A0_OLED_OAPL_CTRL_57_T                      addr_oapl_ctrl_57;	//0xCC8E34E4
	O24A0_OLED_OAPL_CTRL_58_T                      addr_oapl_ctrl_58;	//0xCC8E34E8
	O24A0_OLED_OAPL_CTRL_59_T                      addr_oapl_ctrl_59;	//0xCC8E34EC
	O24A0_OLED_OAPL_CTRL_60_T                      addr_oapl_ctrl_60;	//0xCC8E34F0
	O24A0_OLED_OAPL_CTRL_61_T                      addr_oapl_ctrl_61;	//0xCC8E34F4
	O24A0_OLED_OAPL_CTRL_62_T                      addr_oapl_ctrl_62;	//0xCC8E34F8
	O24A0_OLED_OAPL_CTRL_63_T                      addr_oapl_ctrl_63;	//0xCC8E34FC
	O24A0_OLED_OAPL_CTRL_64_T                      addr_oapl_ctrl_64;	//0xCC8E3500
	O24A0_OLED_OAPL_CTRL_65_T                      addr_oapl_ctrl_65;	//0xCC8E3504
	O24A0_OLED_OAPL_CTRL_66_T                      addr_oapl_ctrl_66;	//0xCC8E3508
	O24A0_OLED_OAPL_CTRL_67_T                      addr_oapl_ctrl_67;	//0xCC8E350C
	O24A0_OLED_OAPL_CTRL_68_T                      addr_oapl_ctrl_68;	//0xCC8E3510
	O24A0_OLED_OAPL_CTRL_69_T                      addr_oapl_ctrl_69;	//0xCC8E3514
	O24A0_OLED_OAPL_CTRL_70_T                      addr_oapl_ctrl_70;	//0xCC8E3518
	O24A0_OLED_OAPL_CTRL_71_T                      addr_oapl_ctrl_71;	//0xCC8E351C
	O24A0_OLED_OLED_CTRL_03_T                      addr_oled_ctrl_03;	//0xCC8E3520
	O24A0_OLED_OLED_CTRL_04_T                      addr_oled_ctrl_04;	//0xCC8E3524
	O24A0_OLED_OLED_CTRL_05_T                      addr_oled_ctrl_05;	//0xCC8E3528
	O24A0_OLED_OLED_CTRL_06_T                      addr_oled_ctrl_06;	//0xCC8E352C
	O24A0_OLED_OLED_CTRL_07_T                      addr_oled_ctrl_07;	//0xCC8E3530
	O24A0_OLED_OLED_CTRL_08_T                      addr_oled_ctrl_08;	//0xCC8E3534
	O24A0_OLED_OLED_CTRL_09_T                      addr_oled_ctrl_09;	//0xCC8E3538
	O24A0_OLED_OLED_CTRL_10_T                      addr_oled_ctrl_10;	//0xCC8E353C
	O24A0_OLED_OLED_CTRL_11_T                      addr_oled_ctrl_11;	//0xCC8E3540
	O24A0_OLED_OLED_CTRL_12_T                      addr_oled_ctrl_12;	//0xCC8E3544
	O24A0_OLED_OLED_CTRL_13_T                      addr_oled_ctrl_13;	//0xCC8E3548
	O24A0_OLED_OLED_CTRL_14_T                      addr_oled_ctrl_14;	//0xCC8E354C
	O24A0_OLED_OLED_CTRL_15_T                      addr_oled_ctrl_15;	//0xCC8E3550
	O24A0_OLED_OLED_CTRL_16_T                      addr_oled_ctrl_16;	//0xCC8E3554
	UINT32                                                    reserved9;	//0xCC8E3558
	UINT32                                                   reserved10;	//0xCC8E355C
	O24A0_OLED_PHDR_CTRL_193_T                    addr_phdr_ctrl_193;	//0xCC8E3560
	O24A0_OLED_PHDR_CTRL_194_T                    addr_phdr_ctrl_194;	//0xCC8E3564
	O24A0_OLED_PHDR_CTRL_195_T                    addr_phdr_ctrl_195;	//0xCC8E3568
	O24A0_OLED_PHDR_CTRL_196_T                    addr_phdr_ctrl_196;	//0xCC8E356C
	O24A0_OLED_PHDR_CTRL_197_T                    addr_phdr_ctrl_197;	//0xCC8E3570
	O24A0_OLED_PHDR_CTRL_198_T                    addr_phdr_ctrl_198;	//0xCC8E3574
	O24A0_OLED_PHDR_CTRL_199_T                    addr_phdr_ctrl_199;	//0xCC8E3578
	O24A0_OLED_PHDR_CTRL_200_T                    addr_phdr_ctrl_200;	//0xCC8E357C
	O24A0_OLED_PHDR_CTRL_201_T                    addr_phdr_ctrl_201;	//0xCC8E3580
	O24A0_OLED_PHDR_CTRL_202_T                    addr_phdr_ctrl_202;	//0xCC8E3584
	O24A0_OLED_PHDR_CTRL_203_T                    addr_phdr_ctrl_203;	//0xCC8E3588
	O24A0_OLED_PHDR_CTRL_204_T                    addr_phdr_ctrl_204;	//0xCC8E358C
	O24A0_OLED_PHDR_CTRL_205_T                    addr_phdr_ctrl_205;	//0xCC8E3590
	O24A0_OLED_PHDR_CTRL_206_T                    addr_phdr_ctrl_206;	//0xCC8E3594
	O24A0_OLED_PHDR_CTRL_207_T                    addr_phdr_ctrl_207;	//0xCC8E3598
	O24A0_OLED_PHDR_CTRL_208_T                    addr_phdr_ctrl_208;	//0xCC8E359C
	O24A0_OLED_PHDR_CTRL_209_T                    addr_phdr_ctrl_209;	//0xCC8E35A0
	O24A0_OLED_PHDR_CTRL_210_T                    addr_phdr_ctrl_210;	//0xCC8E35A4
	O24A0_OLED_PHDR_CTRL_211_T                    addr_phdr_ctrl_211;	//0xCC8E35A8
	O24A0_OLED_PHDR_CTRL_212_T                    addr_phdr_ctrl_212;	//0xCC8E35AC
	O24A0_OLED_PHDR_CTRL_213_T                    addr_phdr_ctrl_213;	//0xCC8E35B0
	O24A0_OLED_PHDR_CTRL_214_T                    addr_phdr_ctrl_214;	//0xCC8E35B4
	O24A0_OLED_PHDR_CTRL_215_T                    addr_phdr_ctrl_215;	//0xCC8E35B8
	O24A0_OLED_PHDR_CTRL_216_T                    addr_phdr_ctrl_216;	//0xCC8E35BC
	O24A0_OLED_PHDR_CTRL_217_T                    addr_phdr_ctrl_217;	//0xCC8E35C0
	O24A0_OLED_PHDR_CTRL_218_T                    addr_phdr_ctrl_218;	//0xCC8E35C4
	O24A0_OLED_PHDR_CTRL_219_T                    addr_phdr_ctrl_219;	//0xCC8E35C8
	O24A0_OLED_PHDR_CTRL_220_T                    addr_phdr_ctrl_220;	//0xCC8E35CC
	O24A0_OLED_PHDR_CTRL_221_T                    addr_phdr_ctrl_221;	//0xCC8E35D0
	O24A0_OLED_PHDR_CTRL_222_T                    addr_phdr_ctrl_222;	//0xCC8E35D4
	O24A0_OLED_PHDR_CTRL_223_T                    addr_phdr_ctrl_223;	//0xCC8E35D8
	O24A0_OLED_PHDR_CTRL_224_T                    addr_phdr_ctrl_224;	//0xCC8E35DC
	O24A0_OLED_PHDR_CTRL_225_T                    addr_phdr_ctrl_225;	//0xCC8E35E0
	O24A0_OLED_PHDR_CTRL_226_T                    addr_phdr_ctrl_226;	//0xCC8E35E4
	O24A0_OLED_PHDR_CTRL_227_T                    addr_phdr_ctrl_227;	//0xCC8E35E8
	O24A0_OLED_PHDR_CTRL_228_T                    addr_phdr_ctrl_228;	//0xCC8E35EC
	O24A0_OLED_PHDR_CTRL_229_T                    addr_phdr_ctrl_229;	//0xCC8E35F0
	O24A0_OLED_PHDR_CTRL_230_T                    addr_phdr_ctrl_230;	//0xCC8E35F4
	O24A0_OLED_PHDR_CTRL_231_T                    addr_phdr_ctrl_231;	//0xCC8E35F8
	O24A0_OLED_PHDR_CTRL_232_T                    addr_phdr_ctrl_232;	//0xCC8E35FC
	O24A0_OLED_PHDR_CTRL_233_T                    addr_phdr_ctrl_233;	//0xCC8E3600
	O24A0_OLED_PHDR_CTRL_234_T                    addr_phdr_ctrl_234;	//0xCC8E3604
	O24A0_OLED_PHDR_CTRL_235_T                    addr_phdr_ctrl_235;	//0xCC8E3608
	O24A0_OLED_PHDR_CTRL_236_T                    addr_phdr_ctrl_236;	//0xCC8E360C
	O24A0_OLED_PHDR_CTRL_237_T                    addr_phdr_ctrl_237;	//0xCC8E3610
	O24A0_OLED_PHDR_CTRL_238_T                    addr_phdr_ctrl_238;	//0xCC8E3614
}DPE_OLED_REG_O24A0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E00 RW 0x0000_0000
	UINT32 reg_ucr_en                       :1;	//(0,RW,0x00) //Uniformity Correction enable
	UINT32 resvd                            :31;
	};
}O24A0_UCR_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E04 RW 0x0000_000F
	UINT32 reg_ivsync_pol                   :1;	//(0,RW,0x1) //1 := input vsync inversion 	0 = input vsync bypass
	UINT32 reg_ihsync_pol                   :1;	//(1,RW,0x1) //1 := input hsync inversion 	0 = input hsync bypass
	UINT32 reg_ovsync_pol                   :1;	//(2,RW,0x1) //1 := output vsync inversion	0 = output vsync bypass
	UINT32 reg_ohsync_pol                   :1;	//(3,RW,0x1) //1 := output hsync inversion	0 = output hsync bypass
	UINT32 resvd                            :28;
	};
}O24A0_UCR_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E10 RW 0x0000_0000
	UINT32 reg_cg_disable                   :1;	//(0,RW,0x0) //clock gating disable (UNUSED)
	UINT32 resvd                            :31;
	};
}O24A0_UCR_CG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E20 RW 0x0000_0000
	UINT32 addr_tm_ctrl_pts                 :3;	//(2:0,RW,0x0) //LUT control points (0~7)
	UINT32 resvd0                           :5;
	UINT32 addr_h                           :3;	//(10:8,RW,0x0) //Hozontal Block address (0~7)
	UINT32 addr_v                           :3;	//(13:11,RW,0x0) //Vertical Block address (0~7)
	UINT32 resvd1                           :17;
	UINT32 we_ai                            :1;	//(31,RW,0x0) //write auto increment
	};
}O24A0_UCR_LUT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E24 RW 0x0000_0000
	UINT32 ctrl_r_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Red
	UINT32 resvd0                           :4;
	UINT32 ctrl_r_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Red
	UINT32 resvd1                           :4;
	};
}O24A0_UCR_LUT_DATA_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E28 RW 0x0000_0000
	UINT32 ctrl_g_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Green
	UINT32 resvd0                           :4;
	UINT32 ctrl_g_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Green
	UINT32 resvd1                           :4;
	};
}O24A0_UCR_LUT_DATA_G_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E2C RW 0x0000_0000
	UINT32 ctrl_b_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Blue
	UINT32 resvd0                           :4;
	UINT32 ctrl_b_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Blue
	UINT32 resvd1                           :4;
	};
}O24A0_UCR_LUT_DATA_B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E30 RW 0x0000_0000
	UINT32 xpos_01                          :13;	//(12:0,RW,0x0) //X position 1 of the block center
	UINT32 resvd0                           :3;
	UINT32 xpos_00                          :13;	//(28:16,RW,0x0) //X position 0 of the block center
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E34 RW 0x0000_0000
	UINT32 xpos_03                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_02                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E38 RW 0x0000_0000
	UINT32 xpos_05                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_04                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E3C RW 0x0000_0000
	UINT32 xpos_07                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_06                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E40 RW 0x0000_0000
	UINT32 xpos_09                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_08                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E44 RW 0x0000_0000
	UINT32 xpos_11                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_10                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E48 RW 0x0000_0000
	UINT32 xpos_13                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_12                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E4C RW 0x0000_0000
	UINT32 xpos_15                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_14                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_XPOS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E50 RW 0x0000_0000
	UINT32 ypos_01                          :13;	//(12:0,RW,0x0) //Y position 1 of the block center
	UINT32 resvd0                           :3;
	UINT32 ypos_00                          :13;	//(28:16,RW,0x0) //Y position 0 of the block center
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E54 RW 0x0000_0000
	UINT32 ypos_03                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_02                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E58 RW 0x0000_0000
	UINT32 ypos_05                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_04                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E5C RW 0x0000_0000
	UINT32 ypos_07                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_06                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E60 RW 0x0000_0000
	UINT32 ypos_09                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_08                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E64 RW 0x0000_0000
	UINT32 ypos_11                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_10                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E68 RW 0x0000_0000
	UINT32 ypos_13                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_12                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E2E6C RW 0x0000_0000
	UINT32 ypos_15                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_14                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}O24A0_UCR_YPOS_07_T;

typedef struct
{
	O24A0_UCR_CORE_CTRL_00_T                         reg_core_ctrl_00;	//0xCC8E2E00
	O24A0_UCR_CORE_CTRL_01_T                         reg_core_ctrl_01;	//0xCC8E2E04
	UINT32                                                    reserved0;	//0xCC8E2E08
	UINT32                                                    reserved1;	//0xCC8E2E0C
	O24A0_UCR_CG_CTRL_00_T                             reg_cg_ctrl_00;	//0xCC8E2E10
	UINT32                                                    reserved2;	//0xCC8E2E14
	UINT32                                                    reserved3;	//0xCC8E2E18
	UINT32                                                    reserved4;	//0xCC8E2E1C
	O24A0_UCR_LUT_CTRL_T                                 reg_lut_ctrl;	//0xCC8E2E20
	O24A0_UCR_LUT_DATA_R_T                             reg_lut_data_r;	//0xCC8E2E24
	O24A0_UCR_LUT_DATA_G_T                             reg_lut_data_g;	//0xCC8E2E28
	O24A0_UCR_LUT_DATA_B_T                             reg_lut_data_b;	//0xCC8E2E2C
	O24A0_UCR_XPOS_00_T                                   reg_xpos_00;	//0xCC8E2E30
	O24A0_UCR_XPOS_01_T                                   reg_xpos_01;	//0xCC8E2E34
	O24A0_UCR_XPOS_02_T                                   reg_xpos_02;	//0xCC8E2E38
	O24A0_UCR_XPOS_03_T                                   reg_xpos_03;	//0xCC8E2E3C
	O24A0_UCR_XPOS_04_T                                   reg_xpos_04;	//0xCC8E2E40
	O24A0_UCR_XPOS_05_T                                   reg_xpos_05;	//0xCC8E2E44
	O24A0_UCR_XPOS_06_T                                   reg_xpos_06;	//0xCC8E2E48
	O24A0_UCR_XPOS_07_T                                   reg_xpos_07;	//0xCC8E2E4C
	O24A0_UCR_YPOS_00_T                                   reg_ypos_00;	//0xCC8E2E50
	O24A0_UCR_YPOS_01_T                                   reg_ypos_01;	//0xCC8E2E54
	O24A0_UCR_YPOS_02_T                                   reg_ypos_02;	//0xCC8E2E58
	O24A0_UCR_YPOS_03_T                                   reg_ypos_03;	//0xCC8E2E5C
	O24A0_UCR_YPOS_04_T                                   reg_ypos_04;	//0xCC8E2E60
	O24A0_UCR_YPOS_05_T                                   reg_ypos_05;	//0xCC8E2E64
	O24A0_UCR_YPOS_06_T                                   reg_ypos_06;	//0xCC8E2E68
	O24A0_UCR_YPOS_07_T                                   reg_ypos_07;	//0xCC8E2E6C
}DPE_UCR_REG_O24A0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3800 RW 0x0F00_0870
	UINT32 reg_hei                          :12;	//(11:0,RW,0x870) //
	UINT32 resvd0                           :4;
	UINT32 reg_wid                          :12;	//(27:16,RW,0xF00) //
	UINT32 resvd1                           :3;
	UINT32 reg_decon_detour_en              :1;	//(31,RW,0x0) //1: detour
	};
}O24A0_REG_LED_DECON_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3804 RW 0x0000_0000
	UINT32 reg_rdf_osd_th                   :8;	//(7:0,RW,0x0) //
	UINT32 resvd                            :3;
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(11,RW,0x0) //
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0x0) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x0) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}O24A0_REG_LED_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3808 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 reg_input_alpha                  :8;	//(31:24,RW,0x0) //
	};
}O24A0_REG_LED_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E380C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 reg_init_rst_off                 :1;	//(31,RW,0x0) //1 : pic_init reset(initial register) off	0: normal mode
	};
}O24A0_REG_LED_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3810 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}O24A0_REG_LED_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3814 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}O24A0_REG_LED_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3818 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}O24A0_REG_LED_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E381C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}O24A0_REG_LED_DECON_CTRL_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3820 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd1                           :2;
	UINT32 reg_1st_rd_luma_cut              :2;	//(11:10,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd2                           :17;
	UINT32 reg_1st_rd_luma_en               :1;	//(29,NA,0x0) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 reg_rd_roi_en                    :1;	//(30,NA,0x0) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd3                           :1;
	};
}O24A0_REG_LED_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3824 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x1B0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x5B) //
	UINT32 resvd1                           :4;
	};
}O24A0_REG_LED_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3828 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x1B0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x6A) //
	UINT32 resvd1                           :4;
	};
}O24A0_REG_LED_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E382C RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //
	UINT32 resvd                            :12;
	};
}O24A0_REG_LED_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3830 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //
	UINT32 resvd                            :12;
	};
}O24A0_REG_LED_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3834 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3838 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E383C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3840 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3844 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3848 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //
	UINT32 resvd1                           :10;
	};
}O24A0_REG_LED_DECON_CTRL_17_T;

typedef struct {
	O24A0_REG_LED_DECON_TOP_CTRL_T               reg_decon_top_ctrl;	//0xCC8E3800
	O24A0_REG_LED_DECON_CTRL_0_T                   reg_decon_ctrl_0;	//0xCC8E3804
	O24A0_REG_LED_DECON_CTRL_1_T                   reg_decon_ctrl_1;	//0xCC8E3808
	O24A0_REG_LED_DECON_CTRL_2_T                   reg_decon_ctrl_2;	//0xCC8E380C
	O24A0_REG_LED_DECON_CTRL_3_T                   reg_decon_ctrl_3;	//0xCC8E3810
	O24A0_REG_LED_DECON_CTRL_4_T                   reg_decon_ctrl_4;	//0xCC8E3814
	O24A0_REG_LED_DECON_CTRL_5_T                   reg_decon_ctrl_5;	//0xCC8E3818
	O24A0_REG_LED_DECON_CTRL_6_T                   reg_decon_ctrl_6;	//0xCC8E381C
	O24A0_REG_LED_DECON_CTRL_7_T                   reg_decon_ctrl_7;	//0xCC8E3820
	O24A0_REG_LED_DECON_CTRL_8_T                   reg_decon_ctrl_8;	//0xCC8E3824
	O24A0_REG_LED_DECON_CTRL_9_T                   reg_decon_ctrl_9;	//0xCC8E3828
	O24A0_REG_LED_DECON_CTRL_10_T                 reg_decon_ctrl_10;	//0xCC8E382C
	O24A0_REG_LED_DECON_CTRL_11_T                 reg_decon_ctrl_11;	//0xCC8E3830
	O24A0_REG_LED_DECON_CTRL_12_T                 reg_decon_ctrl_12;	//0xCC8E3834
	O24A0_REG_LED_DECON_CTRL_13_T                 reg_decon_ctrl_13;	//0xCC8E3838
	O24A0_REG_LED_DECON_CTRL_14_T                 reg_decon_ctrl_14;	//0xCC8E383C
	O24A0_REG_LED_DECON_CTRL_15_T                 reg_decon_ctrl_15;	//0xCC8E3840
	O24A0_REG_LED_DECON_CTRL_16_T                 reg_decon_ctrl_16;	//0xCC8E3844
	O24A0_REG_LED_DECON_CTRL_17_T                 reg_decon_ctrl_17;	//0xCC8E3848
}DECON_CTRL_REG_O24A0_T;

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
}O24A0_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}O24A0_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}O24A0_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}O24A0_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}O24A0_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}O24A0_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}O24A0_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC86142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}O24A0_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}O24A0_PE1_PCC_COEF7_T;

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
}O24A0_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861438 RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :12;	//(11:0,NA,0x0) //12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//(27:16,NA,0x0) //12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}O24A0_PE1_OETF_IA_DATA_T;

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
}O24A0_PE1_EOTF_WDATA_T;

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
}O24A0_PE1_EOTF_WDONE_T;

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
}O24A0_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC861448 RO 0x0000_0000
	UINT32 eotf_buf_rw_conflict             :1;	//(0,RO,0x00) //
	UINT32 eotf_lut_cpy_done                :1;	//(1,RO,0x00) //
	UINT32 eotf_lut_cpy_status              :2;	//(3:2,RO,0x0) //
	UINT32 resvd                            :28;
	};
}O24A0_PE1_EOTF_RSATUS_T;

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

typedef struct
{
	O24A0_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC861410
	O24A0_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC861414
	O24A0_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC861418
	O24A0_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC86141C
	O24A0_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC861420
	O24A0_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC861424
	O24A0_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC861428
	O24A0_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC86142C
	O24A0_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC861430
	O24A0_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xCC861434
	O24A0_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xCC861438
	O24A0_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xCC86143C
	O24A0_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xCC861440
	O24A0_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xCC861444
	O24A0_PE1_EOTF_RSATUS_T                            pe1_eotf_rsatus;	//0xCC861448
}PE_PCC_REG_O24A0_T;

typedef struct {
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
}PE_CC_PE1_REG_O24A0_T;


typedef union {
	UINT32 udata32;
	struct {						//0xCC860F00 RW 0x0000_0110
	UINT32 reg_l3d_en                       :1;	//(0:0,NA,0) //3D-LUT on/off	- 0: off	- 1: on
	UINT32 reg_interp_mode                  :1;	//(1:1,NA,0) //Interpolation mode	- 0: tetrahedral	- 1: tri-linear
	UINT32 resvd0                           :2;
	UINT32 reg_run_core_sel                 :1;	//(4:4,NA,1) //L3D on: normal operation (normal read only)	- 0: 33x33x33 (only 9x9x9 can HIF access)	- 1: 9x9x9 (only 33x33x33 can HIF access)	L3D off: only HIF access	- 0: 9x9x9 (if 1: HIF off)	- 1: 33x33x33 (if 0: HIF off)
	UINT32 reg_lut_wr_core_sel              :1;	//(5:5,NA,0) //LUT write/read core selection	(Invalid if core is running in normal operation mode)	- 0: 33x33x33	- 1: 9x9x9
	UINT32 reg_lut_wr_sel                   :1;	//(6:6,NA,0) //LUT write/read selection	(Valid only if reg_lut_wr_toggle = 0)	- 0:write	- 1:read
	UINT32 reg_lut_wr_toggle                :1;	//(7:7,NA,0) //Auto clear (wr_sel toggle)
	UINT32 reg_lut_auto_mapping             :1;	//(8:8,NA,1) //9x9x9 core LUT write address auto mapping mode	- 0: disable (for using 9x9x9 LUT rom)	- 1: enable (for auto mapping 33x33x33 LUT rom to 9x9x9 LUT)
	UINT32 resvd1                           :23;
	};
}O24A0_L3D_CORE_CTRL_00_T;

typedef struct {
	O24A0_L3D_CORE_CTRL_00_T                         l3d_core_ctrl_00;	//0xCC860F00
}L3D_REG_O24A0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC860450 RW 0x0000_0000
	UINT32 reg_gsr_blend_en                 :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//(7:4,RW,0x0) //0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//(25:16,RW,0x0) //
	UINT32 resvd2                           :6;
	};
}O24A0_PE_OSD0_GSR_CTRL00_T;

typedef struct
{
	O24A0_PE_OSD0_GSR_CTRL00_T                   osd0_gsr_ctrl00;//0xCC860450
}PE_OSD0_IMAGE_REG_O24A0_T;
#endif
