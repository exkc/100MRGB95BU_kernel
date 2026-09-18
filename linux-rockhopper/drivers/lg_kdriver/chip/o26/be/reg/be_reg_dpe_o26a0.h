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

#ifndef _BE_REG_DPE_O26A0_H_
#define _BE_REG_DPE_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif


typedef union {
	UINT32 udata32;
	struct {						//0xCC900000 RW 0x0000_0000
	UINT32 bsh_bv_gen                       :12;	//(11:0,RW,0x00) //Horizontal size of a block
	UINT32 resvd0                           :4;
	UINT32 bsv_bv_gen                       :12;	//(27:16,RW,0x00) //Vertical size of a block
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_HV_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900004 RW 0x0000_0000
	UINT32 bnh_bv_gen                       :7;	//(6:0,RW,0x0) //number of Horizontal blocks
	UINT32 resvd0                           :9;
	UINT32 bnv_bv_gen                       :6;	//(21:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_BLK_NUM_HV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900008 RW 0x0870_0F00
	UINT32 hres                             :14;	//(13:0,RW,0x0F00) //
	UINT32 resvd0                           :2;
	UINT32 vres                             :14;	//(29:16,RW,0x0870) //
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_LED_AD_HV_RESOLUTION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90000C RW 0x0000_00FF
	UINT32 vs_out_neg                       :1;	//(0,RW,0x01) //
	UINT32 hs_out_neg                       :1;	//(1,RW,0x01) //
	UINT32 vs_in_neg                        :1;	//(2,RW,0x01) //
	UINT32 hs_in_neg                        :1;	//(3,RW,0x01) //
	UINT32 vs_lc_out_neg                    :1;	//(4,RW,0x01) //
	UINT32 hs_lc_out_neg                    :1;	//(5,RW,0x01) //
	UINT32 vs_lc_in_neg                     :1;	//(6,RW,0x01) //
	UINT32 hs_lc_in_neg                     :1;	//(7,RW,0x01) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_SYNC_POL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900010 RW 0x0000_0001
	UINT32 mode_2ch                         :1;	//(0,RW,0x01) //dual channel mode
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_VIN_CONFIG_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900014 RW 0x0000_0003
	UINT32 led_dly                          :4;	//(3:0,RW,0x03) //0x3:default normal LED output sync delay	0xB:defualt LED clock gated output
	UINT32 resvd                            :28;
	};
}BE_O26A0_REG_LED_AD_LED_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900018 RW 0x0000_0000
	UINT32 monitor_sel                      :1;	//(0,RW,0x00) //debug
	UINT32 monitor_en                       :1;	//(1,RW,0x00) //monitor enable
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_MONITOR_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90001C RW 0x0000_0000
	UINT32 func_dpath_order                 :1;	//(0,RW,0x00) //"0" : L/D -> Picture Enhance block	"1" : Picture Enhance block -> L/D
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_DPATH_ORDER_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900020 RW 0x0000_0000
	UINT32 rst_async_bridge_tcon            :1;	//(0,RW,0x00) //video to tcon
	UINT32 rst_async_bridge_info            :1;	//(1,RW,0x00) //Chininfo packet
	UINT32 rst_async_bridge_cco             :1;	//(2,RW,0x00) //video to cco
	UINT32 resvd                            :29;
	};
}BE_O26A0_REG_LED_AD_RST_ASYNC_BRIDGE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900024 RW 0x0000_0000
	UINT32 input_sync_sel                   :1;	//(0,RW,0x00) //"0" : even channel sync	"1" : odd channel sync
	UINT32 resvd0                           :3;
	UINT32 input_de_sel                     :1;	//(4,RW,0x00) //"0" : vactive & hactive	"1" : de
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_SYNC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900028 RW 0x0000_0000
	UINT32 bv_clg_en                        :1;	//(0,RW,0x00) //"0" : BV path clock gating enable	"1" : BV path clock gating disable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BV_CLG_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900040 RW 0x0000_0000
	UINT32 pbl_mode                         :2;	//(1:0,RW,0x00) //"0": normal	"1": display physical backlight image
	UINT32 apf                              :1;	//(2,RW,0x00) //display block value image
	UINT32 sbi2rgb                          :1;	//(3,RW,0x00) //display estimated backlight image
	UINT32 sbi_dis                          :1;	//(4,RW,0x00) //disable estimated backlight image
	UINT32 disp_mark                        :1;	//(5,RW,0x00) //display mark
	UINT32 apf_lres                         :1;	//(6,RW,0x00) //low resolution EBI all pass filter
	UINT32 resvd                            :25;
	};
}BE_O26A0_REG_LED_AD_DBG_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900044 RW 0x0000_03FF
	UINT32 lum                              :10;	//(9:0,RW,0x03FF) //Luminance value in Back light display mode
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900048 RW 0x0000_0000
	UINT32 blu_i2c_wdata                    :10;	//(9:0,RW,0x00) //write data
	UINT32 resvd0                           :6;
	UINT32 blu_i2c_waddr                    :13;	//(28:16,RW,0x00) //write address
	UINT32 resvd1                           :2;
	UINT32 blu_i2c_we                       :1;	//(31,RW,0x00) //write enable
	};
}BE_O26A0_REG_LED_AD_BLU_I2C_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90004C RW 0x0000_0000
	UINT32 sbi_sel                          :1;	//(0,RW,0x00) //SB value ( 0 : SBI 1 : I2C Value )
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_SB_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900050 RW 0x0000_0000
	UINT32 sbi_i2c                          :10;	//(9:0,RW,0x00) //I2C SB value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_SB_I2C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900054 RW/RO 0x0000_0000
	UINT32 bv_rdata                         :10;	//(9:0,RO,0x00) //read data
	UINT32 resvd0                           :6;
	UINT32 bv_raddr                         :13;	//(28:16,RW,0x00) //read address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BV_READ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900058 RW 0x0000_0000
	UINT32 bv_wdata                         :10;	//(9:0,RW,0x00) //write data
	UINT32 resvd0                           :6;
	UINT32 bv_waddr                         :13;	//(28:16,RW,0x00) //write address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BV_WRITE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90005C RO 0x0000_0000
	UINT32 bv_rw_done                       :1;	//(0,RO,0x00) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BV_RW_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900064 RW 0x0000_0000
	UINT32 led_detour                       :1;	//(0,RW,0x00) //"0" : normal operation	"1" : detour
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_LED_DETOUR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900080 RW 0x0000_0000
	UINT32 rectangular                      :1;	//(0,RW,0x00) //rectangular image
	UINT32 grid                             :1;	//(1,RW,0x00) //grid image
	UINT32 gradationr                       :1;	//(2,RW,0x00) //R component of gradation image
	UINT32 gradationg                       :1;	//(3,RW,0x00) //G component of gradation image
	UINT32 gradationb                       :1;	//(4,RW,0x00) //B component of gradation image
	UINT32 colorbar                         :1;	//(5,RW,0x00) //color bar image
	UINT32 fld_3dpattern                    :2;	//(7:6,RW,0x00) //"01" : LLRR	"10" : LRLR	"11" : External LR indicator ??
	UINT32 grayimage                        :1;	//(8,RW,0x00) //RGB Max??? RGB? ??
	UINT32 resvd                            :23;
	};
}BE_O26A0_REG_LED_AD_PAT_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900084 RW 0x3FFF_FFFF
	UINT32 comp_bvalue                      :10;	//(9:0,RW,0x03FF) //
	UINT32 comp_gvalue                      :10;	//(19:10,RW,0x03FF) //
	UINT32 comp_rvalue                      :10;	//(29:20,RW,0x03FF) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_PAT_VAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900088 RW 0x0167_0078
	UINT32 h_min                            :12;	//(11:0,RW,0x0078) //horizontal start position
	UINT32 resvd0                           :4;
	UINT32 h_max                            :12;	//(27:16,RW,0x0167) //horizontal end position
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_PAT_H_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90008C RW 0x0329_010E
	UINT32 v_min                            :12;	//(11:0,RW,0x010E) //vertical start position
	UINT32 resvd0                           :4;
	UINT32 v_max                            :12;	//(27:16,RW,0x0329) //vertical end position
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_PAT_V_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900090 RW 0x0000_0000
	UINT32 pat_h_ppf                        :8;	//(7:0,RW,0x0) //Horizontal Speed of the pattern in rectangular and gradation mode (4 pixels per frame)
	UINT32 pat_v_ppf                        :8;	//(15:8,RW,0x0) //Vertical speed of the pattern in rectangular mode (1 pixel per frame)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_PAT_HV_PPF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900094 RW 0x3FFF_FFFF
	UINT32 fld_3d_bvalue                    :10;	//(9:0,RW,0x03FF) //B Value in 3D Pattern
	UINT32 fld_3d_gvalue                    :10;	//(19:10,RW,0x03FF) //G Value in 3D Pattern
	UINT32 fld_3d_rvalue                    :10;	//(29:20,RW,0x03FF) //R Value in 3D Pattern
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_PAT_VAL_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900098 RW 0x0167_0078
	UINT32 fld_3d_h_min                     :11;	//(10:0,RW,0x0078) //h_min in 3D Pattern
	UINT32 resvd0                           :5;
	UINT32 fld_3d_h_max                     :11;	//(26:16,RW,0x0167) //h_max in 3D Pattern
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_LED_AD_PAT_H_MIN_MAX_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90009C RW 0x0329_010E
	UINT32 fld_3d_v_min                     :12;	//(11:0,RW,0x010E) //v_min in 3D Pattern
	UINT32 resvd0                           :4;
	UINT32 fld_3d_v_max                     :12;	//(27:16,RW,0x0329) //v_max in 3D Pattern
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_PAT_V_MIN_MAX_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000A0 RW 0x0000_0000
	UINT32 bg_bvalue                        :10;	//(9:0,RW,0x00) //Background B value in box pattern
	UINT32 bg_gvalue                        :10;	//(19:10,RW,0x00) //Background G value in box pattern
	UINT32 bg_rvalue                        :10;	//(29:20,RW,0x00) //Background R value in box pattern
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_PAT_BGVAL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000C0 RW 0x0000_0400
	UINT32 iwb_r_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_r_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_IWB_R_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000C4 RW 0x0000_0400
	UINT32 iwb_g_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_g_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_IWB_G_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000C8 RW 0x0000_0400
	UINT32 iwb_b_gain                       :11;	//(10:0,RW,0x0400) //
	UINT32 resvd0                           :5;
	UINT32 iwb_b_offset                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_IWB_B_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000E4 RO 0x0000_0000
	UINT32 info_crc_1                       :32;	//(31:0,RO,0x0) //Read LED CRC value
	};
}BE_O26A0_REG_LED_AD_CRC1_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000E8 RW 0x0000_0001
	UINT32 resvd0                           :1;
	UINT32 led_out_sel                      :4;	//(4:1,RW,0x0) //"000" : oled 13 bit	"001" : oled 12 bit, MSB align 	"010" : oled 11 bit, MSB align	"011" : oled 10 bit, MSB align	"100" : oled,led detour	others : oled 13 bit
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_HDMI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000EC RW 0x0000_0000
	UINT32 fbc_en                           :1;	//(0,RW,0x0) //"0" : fbc off	"1" : fbc on
	UINT32 fbc_20p                          :1;	//(1,RW,0x0) //"0" : 40% mode	"1" : 20% mode
	UINT32 resvd0                           :2;
	UINT32 fbc_dual_haar_th                 :4;	//(7:4,RW,0x0) //
	UINT32 resvd1                           :24;
	};
}BE_O26A0_REG_LED_AD_FBC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000F0 RW 0x0000_0000
	UINT32 dpcm_rest_step                   :2;	//(1:0,RW,0x0) //DPCM_REST_STEP
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_FBC_DPCM_REST_STEP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000F4 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_YC422_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000F8 RW 0x0000_0001
	UINT32 info_crc_en                      :4;	//(3:0,RW,0x1) //crc enable
	UINT32 info_crc_mux_dlatch              :4;	//(7:4,RW,0x0) //crc data latch	0: vsync falling edge	1: vsync rising edge
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_CRC_INFO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9000FC RO 0x0000_0000
	UINT32 info_crc_0                       :32;	//(31:0,RO,0x0) //Read LED RGB [59:0] CRC value
	};
}BE_O26A0_REG_LED_AD_CRC_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900100 RW 0x0000_0000
	UINT32 hist_mode                        :2;	//(1:0,RW,0x00) //"00"   : MAX(R,G,B) histogram	"01"   : LUM(R,G,B) histogram	others : AVG(R,G,B) histogram
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_HIST_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900104 WO/RO 0x0000_0000
	UINT32 wr_hist_raddr                    :6;	//(5:0,WO,0x0) //histogram read address
	UINT32 rd_hist_rdata                    :17;	//(22:6,RO,0x0000_0000) //histogram read data(??22:0?)
	UINT32 resvd0                           :1;
	UINT32 rd_hist_raddr                    :6;	//(29:24,RO,0x0) //histogram read address
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_LED_AD_HIST_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900108 RW 0x0000_0000
	UINT32 pwm_ext_sc_sel                   :1;	//(0,RW,0x00) //external scene change detection	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_sc_mode                      :3;	//(6:4,RW,0x00) //scene change detection mode 	"000"  : histogram | apl | block	"001"  : histogram	"010"  : apl	"011"  : block	others : histogram & apl & block
	UINT32 resvd1                           :25;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90010C RW 0x0000_0001
	UINT32 pwm_fr_max_only                  :1;	//(0,RW,0x01) //Operated histogram max only mode	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_ext_max_sel                  :1;	//(4,RW,0x00) //external max value	"0" : disable	"1" : enable
	UINT32 resvd1                           :3;
	UINT32 pwm_max_mode                     :2;	//(9:8,RW,0x00) //"00" : histogram max value	"01" : Weighted Sum ( histogram & block max ) 	"10" : MAX ( histogram & block max )	"11" : MIN ( histogram & block max )
	UINT32 resvd2                           :2;
	UINT32 pwm_bv_end_sel                   :1;	//(12,RW,0x00) //debug
	UINT32 resvd3                           :19;
	};
}BE_O26A0_REG_LED_AD_PWM_MAX_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900110 RW 0x0000_0000
	UINT32 sc_maf_iir_en                    :1;	//(0,RW,0x00) //Adaptive iir filtering using scene change for Local Dimming	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_sc_iir_en                    :1;	//(4,RW,0x00) //Adaptive iir filtering using scene change for PWM value	"0" : disable	"1" : enable
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_PWM_IIR_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900114 RW 0x0000_0000
	UINT32 ext_pwm_sel                      :1;	//(0,RW,0x00) //external PWM value	"0" : disable	"1" : enable
	UINT32 resvd0                           :3;
	UINT32 pwm_blu_en                       :1;	//(4,RW,0x00) //Local Dimming with PWM value	"0" : disable	"1" : enable
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_PWM_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900118 RW 0x0000_0000
	UINT32 pc_pwm_sel                       :1;	//(0,RW,0x00) //pixel compensation with sbi or pwm	"0" : sbi	"1" : pwm
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_PWM_PEL_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90011C RW 0x0000_0000
	UINT32 pwm_ext_sc                       :1;	//(0,RW,0x00) //external scene change input
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_PWM_EXT_SC_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900120 RW 0x00FF_FFFF
	UINT32 pwm_sc_hist_th                   :24;	//(23:0,RW,0x00FF_FFFF) //histogram difference threshold
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_HIST_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900124 RW 0x0000_03FF
	UINT32 pwm_sc_apl_th                    :10;	//(9:0,RW,0x03FF) //apl difference threshold
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_APL_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900128 RO 0x0000_0000
	UINT32 pwm_sc_detect                    :1;	//(0,RO,0x00) //Read scene change detection flag
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_DETECT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90012C RW 0x0000_0000
	UINT32 pwm_max_cdf                      :23;	//(22:0,RW,0x0000_0000) //CDF threshold for histogram max value decision
	UINT32 resvd                            :9;
	};
}BE_O26A0_REG_LED_AD_PWM_MAX_CDF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900130 RW 0x0000_03FF
	UINT32 pwm_ext_max                      :10;	//(9:0,RW,0x03FF) //external max value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_EXT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900134 RW 0x0000_0000
	UINT32 pwm_fr_max_wei                   :8;	//(7:0,RW,0x0) //Weight between histogram and block max value
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_PWM_FR_MAX_WEI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900138 RW 0x0000_0000
	UINT32 pwm_x2                           :10;	//(9:0,RW,0x00) //max value point2
	UINT32 resvd0                           :6;
	UINT32 pwm_x1                           :10;	//(25:16,RW,0x00) //max value point1
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90013C RW 0x0000_0000
	UINT32 pwm_x4                           :10;	//(9:0,RW,0x00) //max value point4
	UINT32 resvd0                           :6;
	UINT32 pwm_x3                           :10;	//(25:16,RW,0x00) //max value point3
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900140 RW 0x0000_0000
	UINT32 pwm_y1                           :10;	//(9:0,RW,0x00) //pwm value in point1
	UINT32 resvd0                           :6;
	UINT32 pwm_y0                           :10;	//(25:16,RW,0x00) //pwm value in 0
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900144 RW 0x0000_0000
	UINT32 pwm_y3                           :10;	//(9:0,RW,0x00) //pwm value in point3
	UINT32 resvd0                           :6;
	UINT32 pwm_y2                           :10;	//(25:16,RW,0x00) //pwm value in point2
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900148 RW 0x0000_0000
	UINT32 pwm_y5                           :10;	//(9:0,RW,0x00) //pwm value in 1023
	UINT32 resvd0                           :6;
	UINT32 pwm_y4                           :10;	//(25:16,RW,0x00) //pwm value in point4
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90014C RO 0x0000_0000
	UINT32 pwm_fr_max_value                 :10;	//(9:0,RO,0x00) //read histogram max value
	UINT32 resvd0                           :6;
	UINT32 pwm_bv_max_value                 :10;	//(25:16,RO,0x00) //read block max value
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_BV_FR_MAX_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900150 RO 0x0000_0000
	UINT32 pwm_max_value                    :10;	//(9:0,RO,0x00) //read max value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_MAX_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900154 RO 0x0000_0000
	UINT32 pwm_value_iir                    :10;	//(9:0,RO,0x00) //read iir filtered pwm value
	UINT32 resvd0                           :6;
	UINT32 pwm_value                        :10;	//(25:16,RO,0x00) //read pwm value
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_VALUE_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900158 RW 0x0000_0080
	UINT32 pwm_iir_wei                      :8;	//(7:0,RW,0x80) //PWM iir filter weight
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_PWM_IIR_WEI_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90015C RW 0x0000_0000
	UINT32 pwm_sc_iir_step_c                :18;	//(17:0,RW,0x0000_0000) //Smooth off step for PWM IIR filter with scene change
	UINT32 resvd                            :14;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_IIR_STEP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900160 RW 0x0000_0000
	UINT32 pwm_sc_iir_step_p                :18;	//(17:0,RW,0x0000_0000) //Smooth on step for PWM IIR filter with scene change
	UINT32 resvd                            :14;
	};
}BE_O26A0_REG_LED_AD_PWM_SC_IIR_STEP_P_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900164 RO 0x0000_0000
	UINT32 pwm_adj_iir_wei                  :8;	//(7:0,RO,0x0) //Read smooth on/off value for PWM IIR filter
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_PWM_ADJ_IIR_WEI_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900168 RW 0x0000_0000
	UINT32 sc_maf_iir_step_c                :20;	//(19:0,RW,0x0000_0000) //Smooth off step for BV IIR filter with scene change
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_LED_AD_PWM_MAF_IIR_STEP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90016C RW 0x0000_0000
	UINT32 sc_maf_iir_step_p                :20;	//(19:0,RW,0x0000_0000) //Smooth on step for BV IIR filter with scene change
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_LED_AD_PWM_MAF_IIR_STEP_P_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900170 RO 0x0000_0000
	UINT32 sc_maf_iir_mag                   :10;	//(9:0,RO,0x00) //Read smooth on/off value for BV IIR filter
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_MAF_IIR_MAG_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900174 RW 0x0000_0000
	UINT32 ext_pwm_pel                      :10;	//(9:0,RW,0x00) //external PWM value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_EXT_VAL_PEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900178 RW/RO 0x0000_0000
	UINT32 pwm_bl_tdif_avg_th               :10;	//(9:0,RW,0x00) //average block difference threshold
	UINT32 resvd0                           :6;
	UINT32 pwm_bl_tdif_avg                  :10;	//(25:16,RO,0x00) //average block difference
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_PWM_BL_TDIF_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900180 RW 0x0000_0002
	UINT32 max_opt                          :8;	//(7:0,RW,0x2) //MAX_OPT value
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900184 RW 0x0000_0000
	UINT32 blk_max_mode                     :1;	//(0,RW,0x00) //"0": BV = (? AVG( R, G, B))/N	"1": BV = (? Max (R, G, B)) / N	Where N: Number of Pixel in a block
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLK_MAX_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900188 RW 0x0000_0000
	UINT32 max_opt_mode                     :1;	//(0,RW,0x00) //"0" : normal operation using MAX_OPT register	"1" : adaptive operation using MAX_OPT0, MAX_OPT1 register
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90018C RW 0x0000_40FF
	UINT32 max_opt1                         :8;	//(7:0,RW,0xFF) //maximum MAX_OPT value
	UINT32 max_opt0                         :8;	//(15:8,RW,0x40) //minimum MAX_OPT value
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT0_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900190 RW 0x0000_0320
	UINT32 level_th                         :10;	//(9:0,RW,0x0320) //Pixel Level Threshold for Block Histogram
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LEVEL_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900194 RW 0x0000_03E8
	UINT32 number_th                        :12;	//(11:0,RW,0x03E8) //number threshold of Block Histogram
	UINT32 resvd0                           :4;
	UINT32 number_bit_sel                   :4;	//(19:16,RW,0x00) //select 12bits of total 19 bits (Block histogram)
	UINT32 resvd1                           :12;
	};
}BE_O26A0_REG_LED_AD_NUMBER_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900198 RO 0x0000_0000
	UINT32 avg_bv                           :10;	//(9:0,RO,0x00) //BLU ?? BV? ??
	UINT32 resvd0                           :6;
	UINT32 apl                              :10;	//(25:16,RO,0x00) //bv_gen block ?? ??? BV? ??
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_APL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90019C RW 0x00C8_0190
	UINT32 bv_gen_x2                        :10;	//(9:0,RW,0x0190) //x2 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x1                        :10;	//(25:16,RW,0x0C8) //x1 APL
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001A0 RW 0x0258_0320
	UINT32 bv_gen_x4                        :10;	//(9:0,RW,0x0320) //x4 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x3                        :10;	//(25:16,RW,0x0258) //x3 APL
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001A4 RW 0x0000_0000
	UINT32 bv_gen_y1                        :10;	//(9:0,RW,0x00) //y1 (x = x1)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y0                        :10;	//(25:16,RW,0x00) //y0 (x = 0)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001A8 RW 0x0000_0000
	UINT32 bv_gen_y3                        :10;	//(9:0,RW,0x00) //y3 (x = x3)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y2                        :10;	//(25:16,RW,0x00) //y2 (x = x2)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001AC RW 0x0000_0000
	UINT32 bv_gen_y5                        :10;	//(9:0,RW,0x00) //y5 (x = 1023)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y4                        :10;	//(25:16,RW,0x00) //y4 (x = x4)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001B0 RO 0x0000_0000
	UINT32 bvgen_max                        :10;	//(9:0,RO,0x00) //BV max value in bv_gen
	UINT32 resvd0                           :6;
	UINT32 bvgen_min                        :10;	//(25:16,RO,0x00) //BV min value in bv_gen
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_BV_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001B4 RO 0x0000_0000
	UINT32 max_bv                           :10;	//(9:0,RO,0x00) //BV max value in bv_ctrl
	UINT32 resvd0                           :6;
	UINT32 min_bv                           :10;	//(25:16,RO,0x00) //BV min value in bv_ctrl
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001B8 RO 0x0000_0000
	UINT32 bv_lut_max                       :10;	//(9:0,RO,0x00) //BV max value in bv_lut
	UINT32 resvd0                           :6;
	UINT32 bv_lut_min                       :10;	//(25:16,RO,0x00) //BV min value in bv_lut
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_LUT_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001BC RO 0x0000_0000
	UINT32 bv_final_max                     :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_final_min                     :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_final_avg                     :10;	//(29:20,RO,0x00) //BV avg value in blu_if(final)
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_BV_FINAL_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001C0 RW 0x0000_0000
	UINT32 rctrl_mode                       :4;	//(3:0,RW,0x00) //
	UINT32 resvd0                           :4;
	UINT32 vsout_mode                       :4;	//(11:8,RW,0x00) //
	UINT32 resvd1                           :4;
	UINT32 bdata_mode                       :4;	//(19:16,RW,0x00) //
	UINT32 resvd2                           :4;
	UINT32 tfout_mode                       :4;	//(27:24,RW,0x00) //
	UINT32 resvd3                           :4;
	};
}BE_O26A0_REG_LED_AD_BV_RCTRL_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001C4 RW/RO 0x0000_0000
	UINT32 pic_attr                         :1;	//(0,RW,0x00) //
	UINT32 black_mask                       :1;	//(1,RO,0x00) //Black mask for BLU	Output of bv_rctrl block
	UINT32 tf_pic_attr                      :1;	//(2,RO,0x00) //Pic_attr for temporal filter	Output of bv_rctrl block
	UINT32 resvd                            :29;
	};
}BE_O26A0_REG_LED_AD_PIC_ATTR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9001C8 RW 0x0000_0000
	UINT32 lr_sync_sel                      :1;	//(0,RW,0x00) //'0' : H/W Pin input	'1' : Register
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_LR_SYNC_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900240 RW 0x0000_0000
	UINT32 lut_mode                         :2;	//(1:0,RW,0x00) //?00?: bypass	?01?: s-curve mode based on internally calculated abv	?10?: s-curve mode using ex_abv
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_LUT_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900244 RW 0x0000_0000
	UINT32 ex_abv                           :10;	//(9:0,RW,0x00) //external abv
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_EX_ABV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90024C RW 0x0000_0000
	UINT32 lut_dbg_raddr                    :10;	//(9:0,RW,0x00) //read address
	UINT32 resvd0                           :6;
	UINT32 lut_dbg_rd_sel                   :1;	//(16,RW,0x00) //read selection
	UINT32 resvd1                           :15;
	};
}BE_O26A0_REG_LED_AD_DC_LUT_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900250 RO 0x0000_0000
	UINT32 lut1_dbg_rdata                   :10;	//(9:0,RO,0x00) //read lower LUT data
	UINT32 resvd0                           :6;
	UINT32 lut0_dbg_rdata                   :10;	//(25:16,RO,0x00) //read upper LUT data
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_DC_LUT_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900258 RW 0x0000_0000
	UINT32 lut_avg_sel                      :1;	//(0,RW,0x00) //Select average value to lut_block	'0' : apl by mean value block	'1' : bv average by bv_gen block
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_LUT_AVG_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90025C RW 0x0000_0000
	UINT32 bv_offset_en                     :3;	//(2:0,RW,0x00) //[0] : enable/disable	[2:1] : 00 - use bv_max from bv_gen	        01 - use bv_max from control reg.	        10 - use bv_max from lut_block
	UINT32 resvd                            :29;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900260 RW 0x00C8_0190
	UINT32 bv_offset_x2                     :10;	//(9:0,RW,0x0190) //bv max point 2
	UINT32 resvd0                           :6;
	UINT32 bv_offset_x1                     :10;	//(25:16,RW,0x0C8) //bv max point 1
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_X1_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900264 RW 0x0258_0320
	UINT32 bv_offset_x4                     :10;	//(9:0,RW,0x0320) //bv max point 4
	UINT32 resvd0                           :6;
	UINT32 bv_offset_x3                     :10;	//(25:16,RW,0x0258) //bv max point 3
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_X3_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900268 RW 0x0066_0066
	UINT32 bv_offset_y1                     :10;	//(9:0,RW,0x66) //offset value in point 1
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y0                     :10;	//(25:16,RW,0x66) //offset value in 0
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_Y0_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90026C RW 0x0066_0066
	UINT32 bv_offset_y3                     :10;	//(9:0,RW,0x66) //offset value in point 3
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y2                     :10;	//(25:16,RW,0x66) //offset value in point 2
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_Y2_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900270 RW 0x0066_0066
	UINT32 bv_offset_y5                     :10;	//(9:0,RW,0x66) //offset value in 1023
	UINT32 resvd0                           :6;
	UINT32 bv_offset_y4                     :10;	//(25:16,RW,0x66) //offset value in point 4
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_LUT_OFFSET_Y4_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900274 RW 0x0000_0000
	UINT32 smooth_off                       :1;	//(0,RW,0x00) //Local dimming smooth on/off
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_LD_SMOOTH_OFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900278 RW 0x0000_0000
	UINT32 smooth_off_step                  :10;	//(9:0,RW,0x00) //Smooth on/off step for Local dimming
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LD_SMOOTH_OFF_STEP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90027C RW 0x0000_0000
	UINT32 bv_ext_max                       :10;	//(9:0,RW,0x00) //external bv max value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LD_BV_EXT_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900280 RW 0x0000_0000
	UINT32 lsf_en                           :1;	//(0,RW,0x00) //Enable UMASK
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_UMASK_UM_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900284 RW 0x0000_0000
	UINT32 lsf_5x5_en                       :1;	//(0,RW,0x00) //5x5 UMASK
	UINT32 resvd0                           :3;
	UINT32 lsf_load                         :1;	//(4,RW,0x00) //lsf coeff. load
	UINT32 resvd1                           :3;
	UINT32 lsf_load_mode                    :1;	//(8,RW,0x00) //0 : vsync. load	1 : manual laod
	UINT32 resvd2                           :23;
	};
}BE_O26A0_REG_LED_AD_UMASK_5X5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900288 RW 0x000A_000A
	UINT32 lsf_coaring_n                    :10;	//(9:0,RW,0x0A) //Negative coaring for UMASK
	UINT32 resvd0                           :6;
	UINT32 lsf_coaring_p                    :10;	//(25:16,RW,0x0A) //Positive coaring for UMASK
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_UMASK_COARING_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90028C RW 0x0118_0118
	UINT32 lsf_gain_n                       :12;	//(11:0,RW,0x0118) //Negative gain for UMASK
	UINT32 resvd0                           :4;
	UINT32 lsf_gain_p                       :12;	//(27:16,RW,0x0118) //Positive gain for UMASK
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_UMASK_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900290 RW 0x0000_0000
	UINT32 lsf_coeff_wdata                  :12;	//(11:0,RW,0x00) //write data
	UINT32 resvd                            :20;
	};
}BE_O26A0_REG_LED_AD_UMASK_WR_COEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900294 RW/RO 0x0000_0000
	UINT32 lsf_coeff_rdata                  :12;	//(11:0,RO,0x00) //read data
	UINT32 resvd0                           :4;
	UINT32 lsf_coeff_raddr                  :7;	//(22:16,RW,0x0) //read address
	UINT32 resvd1                           :9;
	};
}BE_O26A0_REG_LED_AD_UMASK_RD_COEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9002C0 RW 0x03FF_03FF
	UINT32 t_sf                             :10;	//(9:0,RW,0x03FF) //threshold value for max/min
	UINT32 resvd0                           :6;
	UINT32 limit                            :10;	//(25:16,RW,0x03FF) //limit
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_T_SF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9002C4 RW 0x0000_0000
	UINT32 kmode                            :1;	//(0,RW,0x00) //"0" : MAX	"1" : MIN
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_KMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9002C8 RW 0x0000_0011
	UINT32 hkmask                           :4;	//(3:0,RW,0x01) //horizontal size of mask	00:off, 01:3x3, 11:5x5
	UINT32 vkmask                           :4;	//(7:4,RW,0x01) //vertical size of mask	00:off, 01:3x3, 11:5x5
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_HVKMASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9002CC RW 0x0000_03FF
	UINT32 reg_nlsf_alpha                   :10;	//(9:0,RW,0x3FF) //blend alpha
	UINT32 resvd0                           :6;
	UINT32 reg_blend_mode                   :1;	//(16,RW,0x00) //blend mode
	UINT32 resvd1                           :15;
	};
}BE_O26A0_REG_LED_AD_BLEND_ALPHA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900300 RW 0x0000_0000
	UINT32 tf_opmode                        :3;	//(2:0,RW,0x00) //used in 3D Mode(not used)
	UINT32 resvd                            :29;
	};
}BE_O26A0_REG_LED_AD_TF_OPMODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900304 RW 0x0000_001F
	UINT32 a_para                           :9;	//(8:0,RW,0x01F) //weighting factor for temporal filter	( w*current + (1-w)*previous )
	UINT32 resvd                            :23;
	};
}BE_O26A0_REG_LED_AD_A_PARA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900308 RW 0x0000_0000
	UINT32 sc_adj_en                        :1;	//(0,RW,0x00) //Enable scene change adjustment for temporal filter
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_SC_ADJ_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90030C RW 0x0000_0000
	UINT32 md_adj_en                        :1;	//(0,RW,0x00) //Enable temporal difference adjustment for temporal filter
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_MD_ADJ_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900310 RW 0x00C8_00C8
	UINT32 md_x1_n                          :10;	//(9:0,RW,0xC8) //x1_n
	UINT32 resvd0                           :6;
	UINT32 md_x1_p                          :10;	//(25:16,RW,0xC8) //x1_p
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_MD_X1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900314 RW 0x0190_0190
	UINT32 md_x2_n                          :10;	//(9:0,RW,0x190) //x2_n
	UINT32 resvd0                           :6;
	UINT32 md_x2_p                          :10;	//(25:16,RW,0x190) //x2_p
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_MD_X2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900318 RW 0x0258_0258
	UINT32 md_x3_n                          :10;	//(9:0,RW,0x258) //x3_n
	UINT32 resvd0                           :6;
	UINT32 md_x3_p                          :10;	//(25:16,RW,0x258) //x3_p
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_MD_X3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90031C RW 0x0320_0320
	UINT32 md_x4_n                          :10;	//(9:0,RW,0x320) //x4_n
	UINT32 resvd0                           :6;
	UINT32 md_x4_p                          :10;	//(25:16,RW,0x320) //x4_p
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_MD_X4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900320 RW 0x001F_001F
	UINT32 md_y0_n                          :9;	//(8:0,RW,0x1F) //y0_n (x = 0)
	UINT32 resvd0                           :7;
	UINT32 md_y0_p                          :9;	//(24:16,RW,0x1F) //y0_p (x = 0)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900324 RW 0x001F_001F
	UINT32 md_y1_n                          :9;	//(8:0,RW,0x1F) //y1 (x = x1_n)
	UINT32 resvd0                           :7;
	UINT32 md_y1_p                          :9;	//(24:16,RW,0x1F) //y1 (x = x1_p)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900328 RW 0x001F_001F
	UINT32 md_y2_n                          :9;	//(8:0,RW,0x1F) //y2 (x = x2_n)
	UINT32 resvd0                           :7;
	UINT32 md_y2_p                          :9;	//(24:16,RW,0x1F) //y2 (x = x2_p)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90032C RW 0x001F_001F
	UINT32 md_y3_n                          :9;	//(8:0,RW,0x1F) //y3 (x = x3_n)
	UINT32 resvd0                           :7;
	UINT32 md_y3_p                          :9;	//(24:16,RW,0x1F) //y3 (x = x3_p)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900330 RW 0x001F_001F
	UINT32 md_y4_n                          :9;	//(8:0,RW,0x1F) //y4 (x = x4_n)
	UINT32 resvd0                           :7;
	UINT32 md_y4_p                          :9;	//(24:16,RW,0x1F) //y4 (x = x4_p)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900334 RW 0x001F_001F
	UINT32 md_y5_n                          :9;	//(8:0,RW,0x1F) //y5 (x = 1023)
	UINT32 resvd0                           :7;
	UINT32 md_y5_p                          :9;	//(24:16,RW,0x1F) //y5 (x = 1023)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_MD_Y5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900338 RW 0x01FF_0000
	UINT32 avg_bv_iir_mode                  :1;	//(0,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd0                           :15;
	UINT32 avg_bv_iir_gain                  :9;	//(24:16,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd1                           :7;
	};
}BE_O26A0_REG_LED_AD_BV_FINAL_AVG_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90033C RW 0x1FF0_1FF0
	UINT32 m1_avg_bv_iir_mode               :1;	//(0,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd0                           :3;
	UINT32 m1_avg_bv_iir_gain               :9;	//(12:4,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd1                           :3;
	UINT32 m0_avg_bv_iir_mode               :1;	//(16,RW,0x0) //0:manual mode by avg_bv_iir_gain, 1:auto mode by BV temporal filter
	UINT32 resvd2                           :3;
	UINT32 m0_avg_bv_iir_gain               :9;	//(28:20,RW,0x1FF) //0:prev ~ 511:curr(IIR off)
	UINT32 resvd3                           :3;
	};
}BE_O26A0_REG_LED_AD_BV_MID_AVG_IIR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900340 RW 0x0000_0000
	UINT32 led_mode                         :2;	//(1:0,RW,0x00) //"00" : Direct	"01" : T/B Edge	"10" : L/R Edge	"11" : Hybrid
	UINT32 resvd0                           :6;
	UINT32 edge_mode                        :2;	//(9:8,RW,0x00) //"00" : 2-Edge	"10" : 1-Edge R/B	"11" : 1-Edge L/T
	UINT32 resvd1                           :6;
	UINT32 hybrid_mode                      :1;	//(16,RW,0x00) //"0" : hybrid edge T/B	"1" : hybrid edge L/R
	UINT32 resvd2                           :7;
	UINT32 hybrid_pattern                   :4;	//(27:24,RW,0x00) //[24] : even_H(V) T(L)_on/off	[25] : even_H(V) B(R)_on/off	[26] :  odd_H(V) T(L)_on/off	[27] :  odd_H(V) B(R)_on/off
	UINT32 resvd3                           :4;
	};
}BE_O26A0_REG_LED_AD_LED_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900344 RW 0x0000_0000
	UINT32 bnh_lres                         :6;	//(5:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :10;
	UINT32 bnv_lres                         :5;	//(20:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :11;
	};
}BE_O26A0_REG_LED_AD_LRES_BNH_BNV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900348 RW 0x0000_0000
	UINT32 bsh_lres                         :6;	//(5:0,RW,0x0) //Horizontal size of a block
	UINT32 resvd0                           :10;
	UINT32 bsv_lres                         :5;	//(20:16,RW,0x0) //Vertical size of a block
	UINT32 resvd1                           :11;
	};
}BE_O26A0_REG_LED_AD_LRES_BSH_BSV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90034C RW 0x0000_0000
	UINT32 sbi_bnh                          :8;	//(7:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :8;
	UINT32 sbi_bnv                          :7;	//(22:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :9;
	};
}BE_O26A0_REG_LED_AD_SBI_BNH_BNV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900350 RW 0x0000_0000
	UINT32 sbi_bsh                          :10;	//(9:0,RW,0x00) //Horizontal size of a block
	UINT32 resvd0                           :6;
	UINT32 sbi_bsv                          :10;	//(25:16,RW,0x00) //Vertical size of a block
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_SBI_BSH_BSV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900354 RW 0x0000_0000
	UINT32 tab1_rd_sel                      :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_TAB1_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900358 RO/WO 0x0000_0000
	UINT32 tab1_rdata                       :10;	//(9:0,WO,0x00) //read data
	UINT32 tab1_re                          :1;	//(10,RO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_TAB1_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90035C RW 0x0000_0000
	UINT32 tab5_rd_sel                      :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_TAB5_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900360 RO/WO 0x0000_0000
	UINT32 tab5_rdata                       :10;	//(9:0,RO,0x00) //read data
	UINT32 tab5_re                          :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_TAB5_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900364 RW 0x0000_0000
	UINT32 hfc_rd_sel                       :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_HFC_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900368 RO/WO 0x0000_0000
	UINT32 hfc_rdata                        :10;	//(9:0,RO,0x00) //read data
	UINT32 hfc_re                           :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_HFC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90036C RW 0x0000_0000
	UINT32 vfc_rd_sel                       :1;	//(0,RW,0x00) //read selection
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_VFC_RD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900370 RO/WO 0x0000_0000
	UINT32 vfc_rdata                        :10;	//(9:0,RO,0x00) //read data
	UINT32 vfc_re                           :1;	//(10,WO,0x00) //read enable
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_VFC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900374 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_POLARIS_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900380 RW 0x0000_0000
	UINT32 pixel_comp_en                    :1;	//(0,RW,0x00) //pixel compensation enable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_COMP_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900384 RW 0x0000_1200
	UINT32 const_gain                       :10;	//(9:0,RW,0x0200) //const gain for pixel compensation
	UINT32 resvd0                           :2;
	UINT32 const_gain_en                    :1;	//(12,RW,0x1) //const gain for pixel compensation_enable	1:const gain	0:BLE LUT
	UINT32 resvd1                           :3;
	UINT32 ble_com_gain_en                  :1;	//(16,RW,0x0) //smart gain enable 	1:ble_comp_gain	0:512
	UINT32 resvd2                           :15;
	};
}BE_O26A0_REG_LED_AD_CONT_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900388 RW 0x0000_0000
	UINT32 comp_in_sel                      :2;	//(1:0,RW,0x00) //"0" : Max rgb	"1" : Y  	"2" : APL
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_COMP_IN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90038C RW 0x0000_0000
	UINT32 pc_lut_raddr                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :9;
	UINT32 pc_lut_d_rden                    :1;	//(16,RW,0x00) //
	UINT32 pc_lut_c_rden                    :1;	//(17,RW,0x00) //
	UINT32 pc_lut_b_rden                    :1;	//(18,RW,0x00) //
	UINT32 pc_lut_a_rden                    :1;	//(19,RW,0x00) //
	UINT32 resvd1                           :12;
	};
}BE_O26A0_REG_LED_AD_PC_RADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900390 RO 0x0000_0000
	UINT32 pc_lut_rdata                     :10;	//(9:0,RO,0x00) //read pixel compensation LUT data
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PC_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900400 RW 0x0000_03FF
	UINT32 gbl                              :10;	//(9:0,RW,0x03FF) //BLU BV in Local dimming off mode
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_GBL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900408 RW 0x0000_0000
	UINT32 bv_dly_ble                       :2;	//(1:0,RW,0x00) //for ble
	UINT32 resvd0                           :6;
	UINT32 bv_dly_blu                       :2;	//(9:8,RW,0x00) //for blu
	UINT32 resvd1                           :22;
	};
}BE_O26A0_REG_LED_AD_BV_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90040C RW 0x0000_0000
	UINT32 blu_bv_sel                       :1;	//(0,RW,0x00) //Local dimming enable ?? ??	'0' : BV 	'1' : Average BV
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLU_BV_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900440 RW/RO 0x0000_0000
	UINT32 instr_wr_req                     :1;	//(0,RW,0x00) //instr_wr_reg
	UINT32 instr_wr_ack                     :1;	//(1,RO,0x00) //instr_wr_ack
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_INSTR_WR_REQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900444 RW 0x0000_0000
	UINT32 wdata_instr                      :11;	//(10:0,RW,0x00) //write data
	UINT32 resvd0                           :5;
	UINT32 waddr_instr                      :4;	//(19:16,RW,0x00) //write address
	UINT32 resvd1                           :12;
	};
}BE_O26A0_REG_LED_AD_INSTR_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900448 RW/RO 0x0000_0000
	UINT32 rdata_instr                      :11;	//(10:0,RO,0x00) //read data
	UINT32 resvd0                           :5;
	UINT32 raddr_instr                      :4;	//(19:16,RW,0x00) //read address
	UINT32 resvd1                           :12;
	};
}BE_O26A0_REG_LED_AD_INSTR_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90044C RW/RO 0x0000_0000
	UINT32 debug_instr                      :11;	//(10:0,RO,0x00) //
	UINT32 resvd0                           :5;
	UINT32 debug_pc                         :4;	//(19:16,RO,0x00) //
	UINT32 resvd1                           :10;
	UINT32 reg_bv_stuck_clr                 :1;	//(30,RW,0x00) //1:bv_ctrl_stuck_clr_enable
	UINT32 bv_ctrl_err                      :1;	//(31,RO,0x00) //
	};
}BE_O26A0_REG_LED_AD_INSTR_DGB_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900480 RW 0x0000_0000
	UINT32 blc_mode                         :2;	//(1:0,RW,0x00) //blc mode control
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_BLC_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900484 RW 0x0000_0100
	UINT32 bsf_c0                           :10;	//(9:0,RW,0x0100) //c0
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_C0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900488 RW 0x0000_0080
	UINT32 bsf_c1                           :10;	//(9:0,RW,0x080) //c1
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_C1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90048C RW 0x0000_0040
	UINT32 bsf_c2                           :10;	//(9:0,RW,0x040) //c2
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_C2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900490 RW 0x0000_03FF
	UINT32 bsf_ratio0                       :10;	//(9:0,RW,0x03FF) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_RATIO0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900494 RW 0x0000_0200
	UINT32 bsf_ratio1                       :10;	//(9:0,RW,0x0200) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_RATIO1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900498 RW 0x0000_0200
	UINT32 bsf_ratio2                       :10;	//(9:0,RW,0x0200) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BSF_RATIO2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90049C RW 0x0000_0000
	UINT32 a0_gn                            :8;	//(7:0,RW,0x0) //a0
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_A0_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004A0 RW 0x0000_0000
	UINT32 a1_gn                            :8;	//(7:0,RW,0x0) //a1
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_A1_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004A4 RW 0x0000_0000
	UINT32 a2_gn                            :8;	//(7:0,RW,0x0) //a2
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_A2_GN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004A8 RW 0x0000_00FF
	UINT32 a0_ratio                         :8;	//(7:0,RW,0xFF) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_A0_RATIO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004AC RW 0x0000_00FF
	UINT32 a1_ratio                         :8;	//(7:0,RW,0xFF) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_A1_RATIO_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004B0 RW 0x0000_03FF
	UINT32 drv_max                          :10;	//(9:0,RW,0x03FF) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_DRV_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004B4 RW 0x0000_0000
	UINT32 blc_en                           :1;	//(0,RW,0x00) //blc enable
	UINT32 blc_tempo_en                     :1;	//(1,RW,0x00) //blc tempo enable
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_BLC_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004B8 RW 0x0000_0000
	UINT32 blc_tempo_th                     :10;	//(9:0,RW,0x00) //blc tempo th
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BLC_TEMPO_TH_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004BC RW 0x0000_0000
	UINT32 blc_frame_num                    :10;	//(9:0,RW,0x00) //blc frame num
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_BLC_FRAME_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004C0 RO/WO 0x0000_0000
	UINT32 mem_dl_addr_clr                  :1;	//(0,WO,0x00) //clear bit
	UINT32 resvd0                           :15;
	UINT32 mem_dl_addr                      :12;	//(27:16,RO,0x00) //address
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_MEM_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004C4 WO 0x0000_0000
	UINT32 sbi_hcoeff                       :10;	//(9:0,WO,0x00) //EBI H coefficient
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_SBI_HCOEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004C8 WO 0x0000_0000
	UINT32 sbi_vcoeff                       :10;	//(9:0,WO,0x00) //EBI V coefficient
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_SBI_VCOEFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004CC WO 0x0000_0000
	UINT32 pc_lut_a                         :10;	//(9:0,WO,0x00) //pixel comp. LUT A
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004D0 WO 0x0000_0000
	UINT32 pc_lut_b                         :10;	//(9:0,WO,0x00) //pixel comp. LUT B
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004D4 WO 0x0000_0000
	UINT32 pc_lut_c                         :10;	//(9:0,WO,0x00) //pixel comp. LUT C
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_C_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004D8 WO 0x0000_0000
	UINT32 pc_lut_d                         :10;	//(9:0,WO,0x00) //pixel comp. LUT D
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_D_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004DC WO 0x0000_0000
	UINT32 dc_lut_upper                     :10;	//(9:0,WO,0x00) //upper LUT
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_UPPER_DC_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004E0 WO 0x0000_0000
	UINT32 dc_lut_lower                     :10;	//(9:0,WO,0x00) //lower LUT
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LOWER_DC_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004E4 WO 0x0000_0000
	UINT32 fc_tab1                          :10;	//(9:0,WO,0x00) //low resolution EBI 1tab coefficient
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_FC_TAB1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9004E8 WO 0x0000_0000
	UINT32 fc_tab5                          :10;	//(9:0,WO,0x00) //low resolution EBI 5tab coefficient
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_FC_TAB5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900500 RW 0x0000_0000
	UINT32 mean_in_sel                      :1;	//(0,RW,0x00) //'0' : Average of max(rgb)	'1' : Average of Y
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_MEAN_IN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900504 RO 0x0000_0000
	UINT32 pixel_mean                       :10;	//(9:0,RO,0x00) //Calculated by mean_value block
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_MEAN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900540 RW 0x0000_0000
	UINT32 rp_v_pos                         :12;	//(11:0,RW,0x00) //vertical pixel position
	UINT32 resvd0                           :4;
	UINT32 rp_h_pos                         :12;	//(27:16,RW,0x00) //horizontal pixel position
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_RP_HV_POS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900544 RW 0x0000_0000
	UINT32 mark_en                          :1;	//(0,RW,0x00) //mark enable for read a pixel
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_RP_MAKE_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900548 RO 0x0000_0000
	UINT32 rd_pixel_r                       :14;	//(13:0,RO,0x0) //R value for a pixel
	UINT32 resvd                            :18;
	};
}BE_O26A0_REG_LED_AD_RP_R_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90054C RO 0x0000_0000
	UINT32 rd_pixel_g                       :14;	//(13:0,RO,0x0) //G value for a pixel
	UINT32 resvd                            :18;
	};
}BE_O26A0_REG_LED_AD_RP_G_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900550 RO 0x0000_0000
	UINT32 rd_pixel_b                       :14;	//(13:0,RO,0x0) //B value for a pixel
	UINT32 resvd                            :18;
	};
}BE_O26A0_REG_LED_AD_RP_B_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900558 RW 0x0000_0000
	UINT32 alef2_en                         :1;	//(0,RW,0x00) //enable
	UINT32 resvd0                           :3;
	UINT32 alef2_gain_en                    :1;	//(4,RW,0x00) //gain
	UINT32 resvd1                           :3;
	UINT32 alef2_mode                       :1;	//(8,RW,0x00) //non-uniform blk L/D mode
	UINT32 resvd2                           :23;
	};
}BE_O26A0_REG_LED_AD_ALEF2_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90055C RW 0x0000_0010
	UINT32 alef2_block_num                  :5;	//(4:0,RW,0x10) //number of block
	UINT32 resvd                            :27;
	};
}BE_O26A0_REG_LED_AD_ALEF2_BLOCK_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900560 RW 0x0000_0000
	UINT32 alef2_addr_clr                   :1;	//(0,RW,0x00) //address clear
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_ALEF2_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900564 WO 0x0000_0000
	UINT32 alef2_height                     :6;	//(5:0,WO,0x0) //non-uniform blk height
	UINT32 resvd0                           :2;
	UINT32 alef2_width                      :7;	//(14:8,WO,0x0) //non-uniform blk width
	UINT32 resvd1                           :1;
	UINT32 alef2_v_srt                      :6;	//(21:16,WO,0x0) //non-uniform blk start v
	UINT32 resvd2                           :2;
	UINT32 alef2_h_srt                      :7;	//(30:24,WO,0x0) //non-uniform blk  start h
	UINT32 resvd3                           :1;
	};
}BE_O26A0_REG_LED_AD_ALEF2_CFG_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900568 RO/WO 0x0000_0000
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
}BE_O26A0_REG_LED_AD_ALEF2_CFG_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90056C WO 0x0000_0000
	UINT32 alef2_gain                       :10;	//(9:0,WO,0x00) //gain
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_ALEF2_GAIN_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900570 RO/WO 0x0000_0000
	UINT32 rd_alef2_gain                    :10;	//(9:0,RO,0x00) //read gain
	UINT32 resvd                            :21;
	UINT32 alef2_gain_re                    :1;	//(31,WO,0x00) //read enable
	};
}BE_O26A0_REG_LED_AD_ALEF2_GAIN_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900574 WO 0x0000_0000
	UINT32 alef2_maxopt                     :8;	//(7:0,WO,0x0) //max opt
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_ALEF2_MAXOPT_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900578 RO/WO 0x0000_0000
	UINT32 rd_alef2_maxopt                  :8;	//(7:0,RO,0x0) //read max opt
	UINT32 resvd                            :23;
	UINT32 alef2_maxopt_re                  :1;	//(31,WO,0x00) //
	};
}BE_O26A0_REG_LED_AD_ALEF2_MAXOPT_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90057C RW 0x0000_0000
	UINT32 alef2_maxvalue_en                :16;	//(15:0,RW,0x0) //enable max value
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_ALEF2_MAXVALUE_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900580 RW 0x0000_0000
	UINT32 display_bv_en                    :1;	//(0,RW,0x00) //display bv enable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_DISP_BV_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900584 RW 0x0000_0000
	UINT32 display_bv_addr                  :13;	//(12:0,RW,0x00) //address for display_bv
	UINT32 resvd                            :19;
	};
}BE_O26A0_REG_LED_AD_DSIP_BV_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005C0 RW 0x0000_0001
	UINT32 dither_en                        :1;	//(0,RW,0x01) //dither enable
	UINT32 dither_temp_en                   :1;	//(1,RW,0x00) //temporal dither enable
	UINT32 resvd                            :30;
	};
}BE_O26A0_REG_LED_AD_DITHER_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005C4 RW 0x0000_0001
	UINT32 dither2_en                       :1;	//(0,RW,0x01) //12to10 dither enable
	UINT32 dither_temp2_en                  :1;	//(1,RW,0x00) //temporal dither enable
	UINT32 resvd0                           :2;
	UINT32 dither_bypass                    :1;	//(4,RW,0x00) //12bit bypass
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_DITHER_EN_N2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005CC RW 0x0000_0000
	UINT32 ble_sld_sel                      :1;	//(0,RW,0x0) //sld sel for ble (optional) 0:same to blu 2:seperated
	UINT32 resvd0                           :3;
	UINT32 bpl_out_sel                      :1;	//(4,RW,0x00) //bpl_out_sel 0:hw mode 1: sw mode
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_BPL_SLD_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005D0 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_BLU_GAIN_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005D4 RW 0x0000_0000
	UINT32 blu_gain_addr_clr                :1;	//(0,RW,0x00) //blu gain lut r/w address clear
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLU_GAIN_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005D8 RW 0x0000_0000
	UINT32 blu_gain_wdata                   :10;	//(9:0,RW,0x00) //blu gain lut write data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_waddr                   :13;	//(28:16,RW,0x00) //blu gain lut write address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BLU_GAIN_WD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005DC RO 0x0000_0000
	UINT32 blu_gain_rdata                   :10;	//(9:0,RO,0x00) //blu gain lut read data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_raddr                   :13;	//(28:16,RO,0x00) //blu gain lut read address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BLU_GAIN_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005E0 RW 0x0000_0000
	UINT32 blu_bv_addr_clr                  :1;	//(0,RW,0x00) //blu bv r address clear
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLU_BV_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005E4 RO 0x0000_0000
	UINT32 blu_gain_rdata                   :10;	//(9:0,RO,0x00) //blu gain lut read data
	UINT32 resvd0                           :6;
	UINT32 blu_gain_raddr                   :11;	//(26:16,RO,0x00) //blu gain lut read address
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_LED_AD_BLU_BV_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005E8 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_BLE_GAIN_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005EC RW 0x0000_0000
	UINT32 ble_gain_addr_clr                :1;	//(0,RW,0x00) //ble gain lut r/w address clear
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLE_GAIN_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005F0 RW 0x0000_0000
	UINT32 ble_gain_wdata                   :10;	//(9:0,RW,0x00) //ble gain lut write data
	UINT32 resvd0                           :6;
	UINT32 ble_gain_waddr                   :13;	//(28:16,RW,0x00) //ble gain lut write address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BLE_GAIN_WD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9005F4 RO 0x0000_0000
	UINT32 ble_gain_rdata                   :10;	//(9:0,RO,0x00) //ble gain lut read data
	UINT32 resvd0                           :6;
	UINT32 ble_gain_raddr                   :13;	//(28:16,RO,0x00) //ble gain lut read address
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_BLE_GAIN_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900600 RW 0x0000_0000
	UINT32 dpg_en                           :1;	//(0,RW,0x00) //"0" : bypass	"1" : gamma enable
	UINT32 resvd0                           :3;
	UINT32 dpg_rd_sel                       :1;	//(4,RW,0x00) //Operation lut memory select for debugging	"0" : channel 0	"1" : channel 1
	UINT32 resvd1                           :3;
	UINT32 dpg_bit_extension_mode           :2;	//(9:8,RW,0x0) //10bit to 15bit extension option	"00" : data , 00000	"01" : data , data[9:5]	"10" : data , 11111
	UINT32 resvd2                           :22;
	};
}BE_O26A0_REG_LED_AD_DPG_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900604 RW/RO 0x0000_0000
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
}BE_O26A0_REG_LED_AD_DPG_LUT_WR_DONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900608 RW 0x0000_0000
	UINT32 dpg_wdata                        :15;	//(14:0,RW,0x0) //lut write data
	UINT32 resvd0                           :1;
	UINT32 dpg_waddr                        :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd1                           :2;
	UINT32 dpg_we                           :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd2                           :1;
	};
}BE_O26A0_REG_LED_AD_DPG_LUT_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90060C RW/RO 0x0000_0000
	UINT32 dpg_rdata                        :15;	//(14:0,RO,0x0) //lut read data
	UINT32 resvd0                           :1;
	UINT32 dpg_raddr                        :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 dpg_re                           :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 resvd2                           :1;
	};
}BE_O26A0_REG_LED_AD_DPG_LUT_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900610 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 obj_bypass_gain                  :8;	//(23:16,RW,0x0) //obj_bypass_gain
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900614 RW 0x0000_0000
	UINT32 bv_gain_x3                       :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x2                       :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900618 RW 0x0000_0000
	UINT32 bv_gain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90061C RW 0x0000_0000
	UINT32 bvgain_y3                        :8;	//(7:0,NA,0x0) //
	UINT32 bvgain_y2                        :8;	//(15:8,NA,0x0) //
	UINT32 bvgain_y1                        :8;	//(23:16,NA,0x0) //
	UINT32 bvgain_y0                        :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900620 RW 0x0000_0000
	UINT32 avggain_x3                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x2                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900624 RW 0x0000_0000
	UINT32 avggain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900628 RW 0x0000_0000
	UINT32 avggain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 avggain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 avggain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 avggain_y0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90062C RW 0x0000_0000
	UINT32 objgain_x3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_x2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_x1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_x0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900630 RW 0x0000_0000
	UINT32 objgain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_y0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900634 RW 0x0000_0000
	UINT32 bvgain_en                        :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900638 RW 0x0000_0000
	UINT32 bv_gain_x3                       :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x2                       :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90063C RW 0x0000_0000
	UINT32 bv_gain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_gain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900640 RW 0x0000_0000
	UINT32 bvgain_y3                        :8;	//(7:0,NA,0x0) //
	UINT32 bvgain_y2                        :8;	//(15:8,NA,0x0) //
	UINT32 bvgain_y1                        :8;	//(23:16,NA,0x0) //
	UINT32 bvgain_y0                        :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900644 RW 0x0000_0000
	UINT32 avggain_x3                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x2                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900648 RW 0x0000_0000
	UINT32 avggain_x1                       :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avggain_x0                       :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90064C RW 0x0000_0000
	UINT32 avggain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 avggain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 avggain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 avggain_y0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900650 RW 0x0000_0000
	UINT32 objgain_x3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_x2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_x1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_x0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900654 RW 0x0000_0000
	UINT32 objgain_y3                       :8;	//(7:0,NA,0x0) //
	UINT32 objgain_y2                       :8;	//(15:8,NA,0x0) //
	UINT32 objgain_y1                       :8;	//(23:16,NA,0x0) //
	UINT32 objgain_y0                       :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_LED_AD_BVGAIN_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900664 RO 0x0000_0000
	UINT32 bv_mid0_max                      :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_mid0_min                      :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_mid0_avg                      :10;	//(29:20,RO,0x00) //BV avg value in blu_if(mid0)
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_BV_MID0_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900680 RW 0x0000_0000
	UINT32 bv_bpl_en                        :1;	//(0,NA,0x00) //
	UINT32 resvd0                           :15;
	UINT32 luma_bypass_gain                 :10;	//(25:16,NA,0x00) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900684 RW 0x0000_0000
	UINT32 bv_alpha_x1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900688 RW 0x0000_0000
	UINT32 bv_alpha_x3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90068C RW 0x0000_0000
	UINT32 bv_alpha_x5                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x4                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900690 RW 0x0000_0000
	UINT32 bv_alpha_x7                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_x6                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900694 RW 0x0000_0000
	UINT32 bv_alpha_y1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900698 RW 0x0000_0000
	UINT32 bv_alpha_y3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90069C RW 0x0000_0000
	UINT32 bv_alpha_y5                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y4                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006A0 RW 0x0000_0000
	UINT32 bv_alpha_y7                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 bv_alpha_y6                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006A4 RW 0x0000_0000
	UINT32 avg_gain_x1                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avg_gain_x0                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006A8 RW 0x0000_0000
	UINT32 avg_gain_x3                      :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :6;
	UINT32 avg_gain_x2                      :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006AC RW 0x0000_0000
	UINT32 avg_gain_y1                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 avg_gain_y0                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006B0 RW 0x0000_0000
	UINT32 avg_gain_y3                      :12;	//(11:0,NA,0x0) //
	UINT32 resvd0                           :4;
	UINT32 avg_gain_y2                      :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_BVBPL_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006B4 RO 0x0000_0000
	UINT32 bv_mid1_max                      :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_mid1_min                      :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_mid1_avg                      :10;	//(29:20,RO,0x00) //BV avg value in blu_if(mid0)
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_BV_MID1_AVG_MIN_MAX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006B8 RW 0x0000_0000
	UINT32 bv_pattern_gen_en                :1;	//(0,RW,0x00) //gradation bv pattern gen for blu if
	UINT32 resvd0                           :3;
	UINT32 bv_pattern_mode                  :1;	//(4,RW,0x0) //gradation mode 1:decrease 0:increase
	UINT32 bv_toggle_en                     :1;	//(5,RW,0x0) //inc/dec toggle in every frame
	UINT32 resvd1                           :2;
	UINT32 inc_val                          :10;	//(17:8,RW,0x0) //increased value
	UINT32 resvd2                           :2;
	UINT32 ofs_val                          :10;	//(29:20,RW,0x0) //start value
	UINT32 resvd3                           :2;
	};
}BE_O26A0_REG_LED_AD_BV_PG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006C0 RW 0x0000_0000
	UINT32 wb2p_en                          :1;	//(0,RW,0x0) //enable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_WB2P_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006C4 RW 0x0000_0000
	UINT32 r_gain                           :16;	//(15:0,RW,0x0000_0000) //red gain (2.14)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_R_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006C8 RW 0x0000_0000
	UINT32 g_gain                           :16;	//(15:0,RW,0x0000_0000) //green gain (2.14)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_G_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006CC RW 0x0000_0000
	UINT32 b_gain                           :16;	//(15:0,RW,0x0000_0000) //blue gain (2.14)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_B_GAIN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006D0 RW 0x0000_0000
	UINT32 r_offset                         :16;	//(15:0,RW,0x0000_0000) //red offset (s13.3)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_R_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006D4 RW 0x0000_0000
	UINT32 g_offset                         :16;	//(15:0,RW,0x0000_0000) //green offset (s13.3)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_G_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006D8 RW 0x0000_0000
	UINT32 b_offset                         :16;	//(15:0,RW,0x0000_0000) //blue offset (s13.3)
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_WB2P_B_OFFSET_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9006E0 RW 0x0000_0000
	UINT32 reg_bv_dsc_en                    :1;	//(0:0,NA,0x00) //
	UINT32 resvd0                           :3;
	UINT32 reg_bv_gsc_gsc                   :1;	//(4:4,NA,0x00) //
	UINT32 resvd1                           :3;
	UINT32 reg_bv_dsc_init_sel_o            :1;	//(8:8,NA,0x00) //0:bv_gen_end 1:m3(TF)end
	UINT32 reg_bv_dsc_fifo_init_sel_o       :1;	//(9:9,NA,0x00) //0:bv_gen_end 1:m3(TF)end
	UINT32 resvd2                           :22;
	};
}BE_O26A0_REG_LED_AD_BV_GSC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900700 RW 0x0000_0000
	UINT32 out_crop_hs_width                :12;	//(11:0,RW,0x0000_0000) //hsync '0'? ?? width
	UINT32 resvd0                           :4;
	UINT32 out_crop_hs_offset               :12;	//(27:16,RW,0x0000_0000) //hsync '0'? ?? ?? offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_hs_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900704 RW 0x0000_0000
	UINT32 out_crop_ha_width                :12;	//(11:0,RW,0x0000_0000) //hactive '1'? ?? width
	UINT32 resvd0                           :4;
	UINT32 out_crop_ha_offset               :12;	//(27:16,RW,0x0000_0000) //hactive '1'? ?? ?? offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_ha_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900708 RW 0x0000_0000
	UINT32 out_crop_de_width                :12;	//(11:0,RW,0x0000_0000) //de '1'? ?? width
	UINT32 resvd0                           :4;
	UINT32 out_crop_de_offset               :12;	//(27:16,RW,0x0000_0000) //de '1'? ?? ?? offset
	UINT32 resvd1                           :3;
	UINT32 out_crop_de_en                   :1;	//(31:31,RW,0x0000_0000) //enalbe
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90070C RW 0x0000_0000
	UINT32 out_vs_ctrl                      :2;	//(1:0,RW,0x00) //0:normal 1:force '1' 2:force '4'
	UINT32 out_va_ctrl                      :2;	//(3:2,RW,0x00) //0:normal 1:force '1' 2:force '3'
	UINT32 out_hs_ctrl                      :2;	//(5:4,RW,0x00) //0:normal 1:force '1' 2:force '2'
	UINT32 out_ha_ctrl                      :2;	//(7:6,RW,0x00) //0:normal 1:force '1' 2:force '1'
	UINT32 out_de_ctrl                      :2;	//(9:8,RW,0x00) //0:normal 1:force '1' 2:force '0'
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900710 RW 0x0000_0001
	UINT32 read_en                          :1;	//(0,RW,0x1) //pixel read enable (8 pixel)
	UINT32 read_line                        :1;	//(1,RW,0x0) //cross hatch enable of pixel read start position
	UINT32 reg_patt_en                      :1;	//(2,RW,0x0) //rectangle pattern enable
	UINT32 reg_patt_fill                    :1;	//(3,RW,0x0) //rectangle pattern full fill enable
	UINT32 reg_line_alt                     :1;	//(4,RW,0x0) //line alternative pattern enable
	UINT32 reg_one_dot                      :1;	//(5,RW,0x0) //One Dot pattern enable
	UINT32 reg_pix_mode                     :2;	//(7:6,RW,0x0) //pixel mode	0 : 1p	1 : 2p	2 :=4p (fix)
	UINT32 reg_pattern_read                 :1;	//(8,RW,0x0) //0 := no use	1 :  read value = reg_yg/cb/cr_data8
	UINT32 ext_pic_init_en                  :1;	//(9,RW,0x0) //0 := pic_init = vsync	1 :  pic_init = 0
	UINT32 reg_update_disable               :1;	//(10,RW,0x0) //0 := reg_update	1 :  no reg_update
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900714 RW 0x0000_0000
	UINT32 reg_cb_white                     :12;	//(11:0,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_yg_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900718 RW 0x0000_0000
	UINT32 reg_yg_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cr_white                     :12;	//(27:16,RW,0x0000) //Main pattern color	1st color of one dot
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90071C RW 0x0000_0000
	UINT32 reg_cr_black                     :12;	//(11:0,RW,0x0000) //2nd color of one dot
	UINT32 resvd0                           :4;
	UINT32 reg_cb_black                     :12;	//(27:16,RW,0x0000) //2nd color of one dot
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900720 RW 0x0780_0870
	UINT32 y_size                           :16;	//(15:0,RW,0x870) //input vertical   size
	UINT32 x_size                           :16;	//(31:16,RW,0x780) //input horizontal size	actual hsize / 4
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900724 RW 0x0000_0000
	UINT32 y_read_pos                       :16;	//(15:0,RW,0x0000) //vertical read position
	UINT32 x_read_pos                       :16;	//(31:16,RW,0x0000) //horizontal read position
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900728 RW 0x0000_0000
	UINT32 x_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's horizontal end position
	UINT32 x_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's horizontal start position
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90072C RW 0x0000_0000
	UINT32 y_pat_pos_end                    :16;	//(15:0,RW,0x0000) //rectangle patten's vertical end position
	UINT32 y_pat_pos_str                    :16;	//(31:16,RW,0x0000) //rectangle patten's vertical start position
	};
}BE_O26A0_REG_LED_AD_OUT_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900740 RW 0x0000_0000
	UINT32 pix_read_g0                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_r0                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900744 RW 0x0000_0000
	UINT32 pix_read_r1                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_b0                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900748 RW 0x0000_0000
	UINT32 pix_read_b1                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_g1                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90074C RW 0x0000_0000
	UINT32 pix_read_g2                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_r2                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900750 RW 0x0000_0000
	UINT32 pix_read_r3                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_b2                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900754 RW 0x0000_0000
	UINT32 pix_read_b3                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_g3                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900758 RW 0x0000_0000
	UINT32 pix_read_g4                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_r4                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90075C RW 0x0000_0000
	UINT32 pix_read_r5                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_b4                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900760 RW 0x0000_0000
	UINT32 pix_read_b5                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_g5                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900764 RW 0x0000_0000
	UINT32 pix_read_g6                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_r6                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900768 RW 0x0000_0000
	UINT32 pix_read_r7                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_b6                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90076C RW 0x0000_0000
	UINT32 pix_read_b7                      :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 pix_read_g7                      :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_OUT_STAT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900770 RW 0x0000_0000
	UINT32 apl_mux_sel                      :1;	//(0,RW,0x0) //"0" : APL input = dpg data output	"1" : APL Input = odither output
	UINT32 resvd0                           :3;
	UINT32 apl_rgb_sel                      :1;	//(4,RW,0x0) //"0" : MAX RGB	"1" : Aver. RGB
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_APL_VALUE_OP_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900774 RO 0x0000_0000
	UINT32 apl_max_lr                       :10;	//(9:0,RO,0x000) //apl max(L, R)
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_APL_MAX_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900778 RO 0x0000_0000
	UINT32 apl_r                            :10;	//(9:0,RO,0x000) //right apl
	UINT32 resvd0                           :1;
	UINT32 apl_l                            :10;	//(20:11,RO,0x000) //left apl
	UINT32 resvd1                           :1;
	UINT32 apl_min_lr                       :10;	//(31:22,RO,0x000) //apl min(L, R)
	};
}BE_O26A0_REG_LED_AD_APL_DBG_OUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900780 RW/RO 0x0000_0000
	UINT32 oapl_eotf_wr_done                :1;	//(0,RW,0x00) //"1" : lut write done
	UINT32 resvd0                           :3;
	UINT32 oapl_eotf_wr_status              :1;	//(4,RO,0x00) //lut write status
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_OAPL_EOTF_WR_DONE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900784 RW 0x0000_0000
	UINT32 reg_oapl_eotf_wdata              :16;	//(15:0,RW,0x0) //lut write data
	UINT32 oapl_eotf_waddr                  :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd0                           :2;
	UINT32 oapl_eotf_we                     :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_LED_AD_OAPL_EOTF_WDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900788 RW/RO 0x0000_0000
	UINT32 oapl_eotf_rdata                  :16;	//(15:0,RO,0x0) //lut read data
	UINT32 oapl_eotf_raddr                  :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd0                           :2;
	UINT32 oapl_eotf_re                     :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_LED_AD_OAPL_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900800 RW 0x0000_0000
	UINT32 reg_sync_cnt_en                  :1;	//(0,RW,0x0) //enable sync_counter
	UINT32 reg_sync_cnt_vs_inv              :1;	//(1,RW,0x0) //vs inversion
	UINT32 reg_sync_cnt_hs_inv              :1;	//(2,RW,0x0) //hs inversion
	UINT32 resvd                            :29;
	};
}BE_O26A0_REG_LED_AD_MON_SYNC_IN_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900804 RO 0x0000_0000
	UINT32 reg_sync_cnt_vs_active           :16;	//(15:0,RO,0x0) //vs high ??? line ?
	UINT32 reg_sync_cnt_vs_total            :16;	//(31:16,RO,0x0) //vs total line ?(frame total)
	};
}BE_O26A0_REG_LED_AD_MON_SYNC_IN_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900808 RO 0x0000_0000
	UINT32 reg_sync_cnt_hs_active           :16;	//(15:0,RO,0x0) //hs high ??? width
	UINT32 reg_sync_cnt_hs_total            :16;	//(31:16,RO,0x0) //hs total width(line width)
	};
}BE_O26A0_REG_LED_AD_MON_SYNC_IN_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90080C RO 0x0000_0000
	UINT32 reg_sync_cnt_de_h_active         :16;	//(15:0,RO,0x0) //de width
	UINT32 reg_sync_cnt_de_v_active         :16;	//(31:16,RO,0x0) //de total line ?
	};
}BE_O26A0_REG_LED_AD_MON_SYNC_IN_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900900 RW 0x0000_0000
	UINT32 bnh_blu_disp                     :7;	//(6:0,RW,0x0) //
	UINT32 resvd0                           :9;
	UINT32 bnv_blu_disp                     :6;	//(21:16,RW,0x0) //
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_LED_AD_BLU_BLK_NUM_DISP_CLK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900904 RW 0x0000_0000
	UINT32 reverse                          :32;	//(31:0,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_REVERSE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900940 RW 0x0000_0002
	UINT32 max_opt_ai_illuminant            :8;	//(7:0,RW,0x2) //MAX_OPT value
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900944 RW 0x0000_0000
	UINT32 blk_max_mode_ai_illuminant       :1;	//(0,RW,0x00) //"0": BV = (? AVG( R, G, B))/N	"1": BV = (? Max (R, G, B)) / N	Where N: Number of Pixel in a block
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLK_MAX_MODE_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900948 RW 0x0000_0000
	UINT32 max_opt_mode_ai_illuminant       :1;	//(0,RW,0x00) //"0" : normal operation using MAX_OPT register	"1" : adaptive operation using MAX_OPT0, MAX_OPT1 register
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT_MODE_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90094C RW 0x0000_40FF
	UINT32 max_opt1_ai_illuminant           :8;	//(7:0,RW,0xFF) //maximum MAX_OPT value
	UINT32 max_opt0_ai_illuminant           :8;	//(15:8,RW,0x40) //minimum MAX_OPT value
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_MAX_OPT0_1_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900950 RW 0x0000_0320
	UINT32 level_th_ai_illuminant           :10;	//(9:0,RW,0x0320) //Pixel Level Threshold for Block Histogram
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_LEVEL_TH_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900954 RW 0x0000_03E8
	UINT32 number_th_ai_illuminant          :12;	//(11:0,RW,0x03E8) //number threshold of Block Histogram
	UINT32 resvd0                           :4;
	UINT32 number_bit_sel_ai_illuminant     :4;	//(19:16,RW,0x00) //select 12bits of total 19 bits (Block histogram)
	UINT32 resvd1                           :12;
	};
}BE_O26A0_REG_LED_AD_NUMBER_TH_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900958 RO 0x0000_0000
	UINT32 avg_bv_ai_illuminant             :10;	//(9:0,RO,0x00) //BLU ?? BV? ??
	UINT32 resvd0                           :6;
	UINT32 apl_ai_illuminant                :10;	//(25:16,RO,0x00) //bv_gen block ?? ??? BV? ??
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_APL_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90095C RW 0x00C8_0190
	UINT32 bv_gen_x2_ai_illuminant          :10;	//(9:0,RW,0x0190) //x2 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x1_ai_illuminant          :10;	//(25:16,RW,0x0C8) //x1 APL
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_X1_X2_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900960 RW 0x0258_0320
	UINT32 bv_gen_x4_ai_illuminant          :10;	//(9:0,RW,0x0320) //x4 APL
	UINT32 resvd0                           :6;
	UINT32 bv_gen_x3_ai_illuminant          :10;	//(25:16,RW,0x0258) //x3 APL
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_X3_X4_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900964 RW 0x0000_0000
	UINT32 bv_gen_y1_ai_illuminant          :10;	//(9:0,RW,0x00) //y1 (x = x1)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y0_ai_illuminant          :10;	//(25:16,RW,0x00) //y0 (x = 0)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y0_Y1_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900968 RW 0x0000_0000
	UINT32 bv_gen_y3_ai_illuminant          :10;	//(9:0,RW,0x00) //y3 (x = x3)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y2_ai_illuminant          :10;	//(25:16,RW,0x00) //y2 (x = x2)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y2_Y3_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90096C RW 0x0000_0000
	UINT32 bv_gen_y5_ai_illuminant          :10;	//(9:0,RW,0x00) //y5 (x = 1023)
	UINT32 resvd0                           :6;
	UINT32 bv_gen_y4_ai_illuminant          :10;	//(25:16,RW,0x00) //y4 (x = x4)
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_Y4_Y5_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900970 RO 0x0000_0000
	UINT32 bvgen_max_ai_illuminant          :10;	//(9:0,RO,0x00) //BV max value in bv_gen
	UINT32 resvd0                           :6;
	UINT32 bvgen_min_ai_illuminant          :10;	//(25:16,RO,0x00) //BV min value in bv_gen
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_GEN_BV_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900974 RO 0x0000_0000
	UINT32 max_bv_ai_illuminant             :10;	//(9:0,RO,0x00) //BV max value in bv_ctrl
	UINT32 resvd0                           :6;
	UINT32 min_bv_ai_illuminant             :10;	//(25:16,RO,0x00) //BV min value in bv_ctrl
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900978 RO 0x0000_0000
	UINT32 bv_lut_max_ai_illuminant         :10;	//(9:0,RO,0x00) //BV max value in bv_lut
	UINT32 resvd0                           :6;
	UINT32 bv_lut_min_ai_illuminant         :10;	//(25:16,RO,0x00) //BV min value in bv_lut
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_BV_LUT_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90097C RO 0x0000_0000
	UINT32 bv_final_max_ai_illuminant       :10;	//(9:0,RO,0x00) //BV max value in blu_if
	UINT32 bv_final_min_ai_illuminant       :10;	//(19:10,RO,0x00) //BV min value in blu_if
	UINT32 bv_final_avg_ai_illuminant       :10;	//(29:20,RO,0x00) //BV avg value in blu_if(final)
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_LED_AD_BV_FINAL_AVG_MIN_MAX_AI_ILLUMINANT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90098C RW 0x0000_0000
	UINT32 bpl_in_sel                       :1;	//(0:0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BPL_IN_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900990 RW 0x0000_0000
	UINT32 ai_illuminant_map_sel_o          :1;	//(0:0,RW,0x0) //reverse setting not use
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_AI_ILLUMINANT_MAP_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900994 RW 0x0000_0000
	UINT32 cc_ld_direct_path_sel_o          :1;	//(0:0,RW,0x0) //local contrast path sel
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_CC_LD_DIRECT_PATH_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900998 RW 0x0000_0000
	UINT32 reg_osd_lut_x3                   :8;	//(7:0,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_x2                   :8;	//(15:8,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_x1                   :8;	//(23:16,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_x0                   :8;	//(31:24,RW,0x0) //lut for osd adaptive ai map
	};
}BE_O26A0_REG_LED_AD_OSD_LUT0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90099C RW 0x0000_0000
	UINT32 reg_osd_lut_y3                   :8;	//(7:0,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_y2                   :8;	//(15:8,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_y1                   :8;	//(23:16,RW,0x0) //lut for osd adaptive ai map
	UINT32 reg_osd_lut_y0                   :8;	//(31:24,RW,0x0) //lut for osd adaptive ai map
	};
}BE_O26A0_REG_LED_AD_OSD_LUT1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009C0 RW 0xFF00_0044
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
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009C4 RW 0x0000_4040
	UINT32 reg_headgain_y1                  :8;	//(7:0,RW,0x40) //reg_headgain_y1
	UINT32 reg_headgain_x1                  :8;	//(15:8,RW,0x40) //reg_headgain_x1
	UINT32 reg_headgain_y0                  :8;	//(23:16,RW,0x00) //reg_headgain_y0
	UINT32 reg_headgain_x0                  :8;	//(31:24,RW,0x00) //reg_headgain_x0
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009C8 RW 0x8080_FFFF
	UINT32 reg_headgain_y3                  :8;	//(7:0,RW,0xFF) //reg_headgain_y3
	UINT32 reg_headgain_x3                  :8;	//(15:8,RW,0xFF) //reg_headgain_x3
	UINT32 reg_headgain_y2                  :8;	//(23:16,RW,0x80) //reg_headgain_y2
	UINT32 reg_headgain_x2                  :8;	//(31:24,RW,0x80) //reg_headgain_x2
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009CC RW 0x0000_4040
	UINT32 reg_bodygain_y1                  :8;	//(7:0,RW,0x40) //reg_bodygain_y1
	UINT32 reg_bodygain_x1                  :8;	//(15:8,RW,0x40) //reg_bodygain_x1
	UINT32 reg_bodygain_y0                  :8;	//(23:16,RW,0x00) //reg_bodygain_y0
	UINT32 reg_bodygain_x0                  :8;	//(31:24,RW,0x00) //reg_bodygain_x0
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009D0 RW 0x8080_FFFF
	UINT32 reg_bodygain_y3                  :8;	//(7:0,RW,0xFF) //reg_bodygain_y3
	UINT32 reg_bodygain_x3                  :8;	//(15:8,RW,0xFF) //reg_bodygain_x3
	UINT32 reg_bodygain_y2                  :8;	//(23:16,RW,0x80) //reg_bodygain_y2
	UINT32 reg_bodygain_x2                  :8;	//(31:24,RW,0x80) //reg_bodygain_x2
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009D4 RW 0x0000_4040
	UINT32 reg_textgain_y1                  :8;	//(7:0,RW,0x40) //reg_textgain_y1
	UINT32 reg_textgain_x1                  :8;	//(15:8,RW,0x40) //reg_textgain_x1
	UINT32 reg_textgain_y0                  :8;	//(23:16,RW,0x00) //reg_textgain_y0
	UINT32 reg_textgain_x0                  :8;	//(31:24,RW,0x00) //reg_textgain_x0
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009D8 RW 0x8080_FFFF
	UINT32 reg_textgain_y3                  :8;	//(7:0,RW,0xFF) //reg_textgain_y3
	UINT32 reg_textgain_x3                  :8;	//(15:8,RW,0xFF) //reg_textgain_x3
	UINT32 reg_textgain_y2                  :8;	//(23:16,RW,0x80) //reg_textgain_y2
	UINT32 reg_textgain_x2                  :8;	//(31:24,RW,0x80) //reg_textgain_x2
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009DC RW 0x0000_0000
	UINT32 reg_pxl_x                        :13;	//(12:0,RW,0x00) //reg_pxl_x
	UINT32 resvd0                           :2;
	UINT32 reg_win_in_disable               :1;	//(15:15,RW,0x00) //reg_win_in_disable
	UINT32 reg_pxl_y                        :13;	//(28:16,RW,0x00) //reg_pxl_y
	UINT32 resvd1                           :2;
	UINT32 reg_win_out_disable              :1;	//(31:31,RW,0x00) //reg_win_out_disable
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009E0 RW 0x0000_0000
	UINT32 reg_pxl_w                        :13;	//(12:0,NA,0x00) //reg_pxl_w
	UINT32 resvd0                           :3;
	UINT32 reg_pxl_h                        :13;	//(28:16,RW,0x00) //reg_pxl_h
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9009E4 RW 0x0000_0000
	UINT32 reg_win_out_objt_gain            :8;	//(7:0,NA,0x00) //reg_win_out_objt_gain
	UINT32 resvd0                           :8;
	UINT32 reg_win_in_objt_gain             :8;	//(23:16,RW,0x00) //reg_win_in_objt_gain
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A00 RW 0x0000_0200
	UINT32 reg_pixel_comp_lut_y_0           :10;	//(9:0,RW,0x0200) //reg_pixel_comp_lut_xy_0
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_0           :10;	//(25:16,RW,0x0000) //reg_pixel_comp_lut_xy_0
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A04 RW 0x0080_0200
	UINT32 reg_pixel_comp_lut_y_1           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_1
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_1           :10;	//(25:16,RW,0x0080) //reg_pixel_comp_lut_x_1
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A08 RW 0x0100_0200
	UINT32 reg_pixel_comp_lut_y_2           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_2
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_2           :10;	//(25:16,RW,0x0100) //reg_pixel_comp_lut_x_2
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A0C RW 0x0200_0200
	UINT32 reg_pixel_comp_lut_y_3           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_3
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_3           :10;	//(25:16,RW,0x0200) //reg_pixel_comp_lut_x_3
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A10 RW 0x0300_0200
	UINT32 reg_pixel_comp_lut_y_4           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_4
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_4           :10;	//(25:16,RW,0x0300) //reg_pixel_comp_lut_x_4
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A14 RW 0x0380_0200
	UINT32 reg_pixel_comp_lut_y_5           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_5
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_5           :10;	//(25:16,RW,0x0380) //reg_pixel_comp_lut_x_5
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A18 RW 0x03FF_0200
	UINT32 reg_pixel_comp_lut_y_6           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_6
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_6           :10;	//(25:16,RW,0x03FF) //reg_pixel_comp_lut_x_6
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900A1C RW 0x03FF_0200
	UINT32 reg_pixel_comp_lut_y_7           :10;	//(9:0,NA,0x0200) //reg_pixel_comp_lut_y_7
	UINT32 resvd0                           :6;
	UINT32 reg_pixel_comp_lut_x_7           :10;	//(25:16,RW,0x03FF) //reg_pixel_comp_lut_x_7
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC900AE4 RW 0x0000_0000
	UINT32 fps                              :8;	//(7:0,RW,0x0) //fps
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_FPS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902000 RW 0x0000_0000
	UINT32 bnh_blu_if                       :7;	//(6:0,RW,0x0) //number of horizontal blocks
	UINT32 resvd0                           :9;
	UINT32 bnv_blu_if                       :6;	//(21:16,RW,0x0) //number of vertical blocks
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_LED_AD_BLU_BLK_NUM_HV_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902004 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_VS_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902008 RW 0x0000_0000
	UINT32 blu_vs_num                       :3;	//(2:0,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs1_num                      :3;	//(5:3,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs2_num                      :3;	//(8:6,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 blu_vs3_num                      :3;	//(11:9,RW,0x00) //"00" : x1	"01" : x2	"10" : x3	"11" : x4
	UINT32 resvd                            :20;
	};
}BE_O26A0_REG_LED_AD_BLU_VS_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90200C RW 0x0000_0000
	UINT32 blu_vs_t0                        :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_BLU_VS_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902010 RW 0x0000_0000
	UINT32 vs_delay                         :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_VS_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902014 RW 0x0000_001E
	UINT32 i2c_slave_addr                   :8;	//(7:0,RW,0x1E) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_I2C_SLAVE_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902018 RW 0x007D_0000
	UINT32 time_out                         :8;	//(7:0,RW,0x0) //
	UINT32 resvd0                           :8;
	UINT32 hold_scl                         :8;	//(23:16,RW,0x7D) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_LED_AD_I2C_CONF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90201C RW 0x0000_0000
	UINT32 version                          :32;	//(31:0,RW,0x0000_0000) //version
	};
}BE_O26A0_REG_LED_AD_VERSION_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902020 RW 0x0000_0000
	UINT32 general_reg0                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}BE_O26A0_REG_LED_AD_GENERAL_REG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902024 RW 0x0000_0000
	UINT32 general_reg1                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}BE_O26A0_REG_LED_AD_GENERAL_REG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902028 RW 0x0000_0000
	UINT32 general_reg2                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}BE_O26A0_REG_LED_AD_GENERAL_REG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90202C RW 0x0000_0000
	UINT32 general_reg3                     :32;	//(31:0,RW,0x0000_0000) //general register
	};
}BE_O26A0_REG_LED_AD_GENERAL_REG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902030 RW 0x0000_0010
	UINT32 reg_led_ldim_cg_on               :1;	//(0,RW,0x0) //local dimming clock gating enable
	UINT32 resvd0                           :3;
	UINT32 reg_led_ldim_bypass_en           :1;	//(4,RW,0x1) //local dimming bypass enable
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_CG_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902040 RW 0x0000_0000
	UINT32 blu_i2c_rd_on                    :1;	//(0,RW,0x00) //read ON
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_ON_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902044 RW 0x0000_0000
	UINT32 blu_i2c_raddr                    :14;	//(13:0,RW,0x00) //read address
	UINT32 resvd                            :18;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902048 RO 0x0000_0000
	UINT32 blu_i2c_rdata                    :10;	//(9:0,RO,0x00) //read data
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90204C RW 0x0000_0000
	UINT32 blu_vs1_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_BLU_VS1_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902050 RW 0x0000_0000
	UINT32 vs1_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_VS1_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902054 RW 0x0000_0000
	UINT32 blu_vs2_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_BLU_VS2_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902058 RW 0x0000_0000
	UINT32 vs2_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_VS2_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90205C RW 0x0000_0000
	UINT32 blu_vs3_t0                       :24;	//(23:0,RW,0x0000_0000) //vsync to vsync time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_BLU_VS3_T0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902060 RW 0x0000_0000
	UINT32 vs3_delay                        :24;	//(23:0,RW,0x0000_0000) //vsync delay time
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_LED_AD_VS3_DLY_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902080 RW 0x0000_0000
	UINT32 spi_cpha                         :1;	//(0,RW,0x00) //Select the phase of the SPI clock
	UINT32 spi_cpol                         :1;	//(1,RW,0x00) //Select the polarity of the SPI clock
	UINT32 spi_16b                          :1;	//(2,RW,0x00) //16 bit data mode
	UINT32 spi_10b                          :1;	//(3,RW,0x00) //10 bit data mode
	UINT32 fld_16b_shift                    :3;	//(6:4,RW,0x00) //left shift (0~6) not use
	UINT32 spi_12b                          :1;	//(7,RW,0x00) //12 bit data mode
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_LED_AD_SPI_CFG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902084 RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_SPI_CMD_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902088 RW 0x0000_000F
	UINT32 mask_ch3                         :1;	//(0,RW,0x01) //
	UINT32 mask_ch2                         :1;	//(1,RW,0x01) //
	UINT32 mask_ch1                         :1;	//(2,RW,0x01) //
	UINT32 mask_ch0                         :1;	//(3,RW,0x01) //
	UINT32 resvd                            :28;
	};
}BE_O26A0_REG_LED_AD_M_SPI_CH_MASK_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90208C RW 0x00AB_00AA
	UINT32 spi_idc0                         :16;	//(15:0,RW,0xAA) //Channel ID for SPI Master Channel 0
	UINT32 spi_idc1                         :16;	//(31:16,RW,0xAB) //Channel ID for SPI Master Channel 1
	};
}BE_O26A0_REG_LED_AD_SPI_IDC01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902090 RW 0x00AD_00AC
	UINT32 spi_idc2                         :16;	//(15:0,RW,0xAC) //Channel ID for SPI Master Channel 2
	UINT32 spi_idc3                         :16;	//(31:16,RW,0xAD) //Channel ID for SPI Master Channel 3
	};
}BE_O26A0_REG_LED_AD_SPI_IDC23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902094 RW 0x0000_0000
	UINT32 spi_cmd0                         :16;	//(15:0,RW,0x0) //The first SPI Command
	UINT32 spi_cmd1                         :16;	//(31:16,RW,0x0) //The second SPI Command
	};
}BE_O26A0_REG_LED_AD_SPI_CMD01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902098 RW 0x0000_0000
	UINT32 spi_cmd2                         :16;	//(15:0,RW,0x0) //The third SPI Command
	UINT32 spi_cmd3                         :16;	//(31:16,RW,0x0) //The fourth SPI Command
	};
}BE_O26A0_REG_LED_AD_SPI_CMD23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90209C RW 0x0000_0052
	UINT32 sclk_t1                          :16;	//(15:0,RW,0x52) //Timing value T1 for the SPI clock
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_SCLK_T1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020A0 RW 0x0000_0028
	UINT32 sclk_t2                          :16;	//(15:0,RW,0x28) //Timing value T2 for the SPI clock
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_SCLK_T2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020A4 RW 0x0000_0029
	UINT32 sclk_t3                          :16;	//(15:0,RW,0x29) //Timing value T3 for the SPI clock
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_SCLK_T3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020A8 RW 0x0000_00CD
	UINT32 sclk_t4                          :16;	//(15:0,RW,0xCD) //Timing value T4 for the SPI clock
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_SCLK_T4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020AC RW 0x0000_0095
	UINT32 sclk_t5                          :16;	//(15:0,RW,0x95) //Pulse width of BLU vsync
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_LED_AD_SCLK_T5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020B0 RW 0x0000_0000
	UINT32 spi_cmd4                         :16;	//(15:0,RW,0x0) //The 5th SPI Command
	UINT32 spi_cmd5                         :16;	//(31:16,RW,0x0) //The 6th SPI Command
	};
}BE_O26A0_REG_LED_AD_SPI_CMD45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020C0 RW 0x0000_0000
	UINT32 blk_vsp0                         :6;	//(5:0,RW,0x00) //start ypoint of BV segment 0
	UINT32 resvd0                           :2;
	UINT32 blk_hsp0                         :7;	//(14:8,RW,0x00) //start xpoint of BV segment 0
	UINT32 resvd1                           :17;
	};
}BE_O26A0_REG_LED_AD_BLK_SP0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020C4 RW 0x0000_0000
	UINT32 blk_vsp1                         :6;	//(5:0,RW,0x00) //start ypoint of BV segment 1
	UINT32 resvd0                           :2;
	UINT32 blk_hsp1                         :7;	//(14:8,RW,0x00) //start xpoint of BV segment 1
	UINT32 resvd1                           :17;
	};
}BE_O26A0_REG_LED_AD_BLK_SP1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020C8 RW 0x0000_0000
	UINT32 blk_vsp2                         :6;	//(5:0,RW,0x00) //start ypoint of BV segment 2
	UINT32 resvd0                           :2;
	UINT32 blk_hsp2                         :7;	//(14:8,RW,0x00) //start xpoint of BV segment 2
	UINT32 resvd1                           :17;
	};
}BE_O26A0_REG_LED_AD_BLK_SP2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020CC RW 0x0000_0000
	UINT32 blk_vsp3                         :6;	//(5:0,RW,0x00) //start ypoint of BV segment 3
	UINT32 resvd0                           :2;
	UINT32 blk_hsp3                         :7;	//(14:8,RW,0x00) //start xpoint of BV segment 3
	UINT32 resvd1                           :17;
	};
}BE_O26A0_REG_LED_AD_BLK_SP3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020D0 RW 0x0000_0000
	UINT32 bnh_seg0                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 0
	UINT32 resvd                            :25;
	};
}BE_O26A0_REG_LED_AD_BNH_SEG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020D4 RW 0x0000_0000
	UINT32 bnh_seg1                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 1
	UINT32 resvd                            :25;
	};
}BE_O26A0_REG_LED_AD_BNH_SEG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020D8 RW 0x0000_0000
	UINT32 bnh_seg2                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 2
	UINT32 resvd                            :25;
	};
}BE_O26A0_REG_LED_AD_BNH_SEG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020DC RW 0x0000_0000
	UINT32 bnh_seg3                         :7;	//(6:0,RW,0x0) //horizontal block number of BV segment 3
	UINT32 resvd                            :25;
	};
}BE_O26A0_REG_LED_AD_BNH_SEG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020E0 RW 0x0000_0000
	UINT32 bnv_seg0                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 0
	UINT32 resvd                            :26;
	};
}BE_O26A0_REG_LED_AD_BNV_SEG0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020E4 RW 0x0000_0000
	UINT32 bnv_seg1                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 1
	UINT32 resvd                            :26;
	};
}BE_O26A0_REG_LED_AD_BNV_SEG1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020E8 RW 0x0000_0000
	UINT32 bnv_seg2                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 2
	UINT32 resvd                            :26;
	};
}BE_O26A0_REG_LED_AD_BNV_SEG2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9020EC RW 0x0000_0000
	UINT32 bnv_seg3                         :6;	//(5:0,RW,0x0) //Vertical block number of BV segment 3
	UINT32 resvd                            :26;
	};
}BE_O26A0_REG_LED_AD_BNV_SEG3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902100 RW 0x0000_03FF
	UINT32 spi_pwm_value                    :10;	//(9:0,RW,0x3FF) //PWM value
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_LED_AD_PWM_VALUE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902104 RW 0x0000_0000
	UINT32 blu_maxvalen                     :1;	//(0,RW,0x00) //"0" : disable	"1" : enable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_BLU_MAXVAL_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902108 RW 0x0000_0000
	UINT32 spi_alef2_en                     :1;	//(0,RW,0x00) //enable spi non uniform block L/D
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_SPI_ALEF2_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90210C RW 0x0000_0000
	UINT32 spi_alef2_clr                    :1;	//(0,RW,0x00) //clear
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_SPI_ALEF2_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902110 WO 0x0000_0000
	UINT32 spi0_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi0 read position
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_SPI0_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902114 RO/WO 0x0000_0000
	UINT32 rd_spi0_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi0 read position
	UINT32 resvd                            :20;
	UINT32 spi0_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}BE_O26A0_REG_LED_AD_SPI0_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902118 WO 0x0000_0000
	UINT32 spi1_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi1 read position
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_SPI1_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90211C RO/WO 0x0000_0000
	UINT32 rd_spi1_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi1 read position
	UINT32 resvd                            :20;
	UINT32 spi1_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}BE_O26A0_REG_LED_AD_SPI1_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902120 WO 0x0000_0000
	UINT32 spi2_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi2 read position
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_SPI2_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902124 RO/WO 0x0000_0000
	UINT32 rd_spi2_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi2 read position
	UINT32 resvd                            :20;
	UINT32 spi2_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}BE_O26A0_REG_LED_AD_SPI2_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902128 WO 0x0000_0000
	UINT32 spi3_alef2_rdpos                 :11;	//(10:0,WO,0x00) //write spi3 read position
	UINT32 resvd                            :21;
	};
}BE_O26A0_REG_LED_AD_SPI3_ALEF2_LUT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90212C RO/WO 0x0000_0000
	UINT32 rd_spi3_alef2_rdpos              :11;	//(10:0,RO,0x00) //read spi3 read position
	UINT32 resvd                            :20;
	UINT32 spi3_alef2_re                    :1;	//(31,WO,0x00) //read enable
	};
}BE_O26A0_REG_LED_AD_SPI3_ALEF2_LUT_RD_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902140 RW 0x0000_0000
	UINT32 line_intr_en                     :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_en                       :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_en                       :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_en                       :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_en          :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_en               :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_in_en                        :26;	//(31:6,RW,0x0000_0000) //external interrupt enable
	};
}BE_O26A0_REG_LED_AD_EXT_INT_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902144 RO/RW 0x0000_0000
	UINT32 line_intr_stat                   :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_stat                     :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_stat                     :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_stat                     :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_stat        :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_stat             :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_status                   :26;	//(31:6,RO,0x0000_0000) //external interrupt status
	};
}BE_O26A0_REG_LED_AD_EXT_INT_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902148 RO/RW 0x0000_0000
	UINT32 line_intr_stat                   :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_stat                     :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_stat                     :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_stat                     :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_stat        :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_stat             :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_raw_status               :26;	//(31:6,RO,0x0000_0000) //external interrupt raw status
	};
}BE_O26A0_REG_LED_AD_EXT_INT_RAW_STATUS_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90214C WO/RW 0x0000_0000
	UINT32 line_intr_clr                    :1;	//(0,RW,0x0000_0000) //
	UINT32 de_intr_clr                      :1;	//(1,RW,0x0000_0000) //
	UINT32 hs_intr_clr                      :1;	//(2,RW,0x0000_0000) //
	UINT32 vs_intr_clr                      :1;	//(3,RW,0x0000_0000) //
	UINT32 bv_final_wr_end_intr_clr         :1;	//(4,RW,0x0000_0000) //
	UINT32 bve_wr_end_intr_clr              :1;	//(5,RW,0x0000_0000) //
	UINT32 ext_int_clr                      :26;	//(31:6,WO,0x0000_0000) //external interrupt clear
	};
}BE_O26A0_REG_LED_AD_EXT_INT_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902150 RW 0x0000_0000
	UINT32 int_line_num                     :12;	//(11:0,RW,0x00) //
	UINT32 resvd                            :20;
	};
}BE_O26A0_REG_LED_AD_EXT_INT_LINE_NUM_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902220 RW 0x0000_0000
	UINT32 use_same_vs                      :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_VS_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902240 RW 0x0000_0000
	UINT32 bfi_manual_toggle                :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 bfi_en                           :1;	//(4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 abi_en                           :1;	//(8,RW,0x0) //
	UINT32 resvd2                           :23;
	};
}BE_O26A0_REG_LED_AD_ABI_BFI0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902244 RW 0x0000_0000
	UINT32 reg_abi_gain_3                   :7;	//(6:0,RW,0x0) //4th frame gain (64=1.0)
	UINT32 resvd0                           :1;
	UINT32 reg_abi_gain_2                   :7;	//(14:8,RW,0x0) //3nd frame gain (64=1.0)
	UINT32 resvd1                           :1;
	UINT32 reg_abi_gain_1                   :7;	//(22:16,RW,0x0) //2st frame gain (64=1.0)
	UINT32 resvd2                           :1;
	UINT32 reg_abi_gain_0                   :7;	//(30:24,RW,0x0) //1st frame gain (64=1.0)
	UINT32 resvd3                           :1;
	};
}BE_O26A0_REG_LED_AD_ABI_BFI1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902248 RW 0x0000_0000
	UINT32 reg_abi_gain_7                   :7;	//(6:0,RW,0x0) //8th frame gain (64=1.0)
	UINT32 resvd0                           :1;
	UINT32 reg_abi_gain_6                   :7;	//(14:8,RW,0x0) //7th frame gain (64=1.0)
	UINT32 resvd1                           :1;
	UINT32 reg_abi_gain_5                   :7;	//(22:16,RW,0x0) //6th frame gain (64=1.0)
	UINT32 resvd2                           :1;
	UINT32 reg_abi_gain_4                   :7;	//(30:24,RW,0x0) //5th frame gain (64=1.0)
	UINT32 resvd3                           :1;
	};
}BE_O26A0_REG_LED_AD_ABI_BFI2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90224C RW 0x0000_0000
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
}BE_O26A0_REG_LED_AD_ABI_BFI3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902280 RW 0x0001_0140
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
}BE_O26A0_REG_LED_AD_12BIT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902284 RW 0x0000_0000
	UINT32 reg_12b_wgt_p1_o                 :12;	//(11:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_12b_wgt_p2_o                 :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_12BIT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902288 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_12b_wgt_c_o                  :12;	//(27:16,RW,0x0) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_LED_AD_12BIT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90228C RW 0x0000_0004
	UINT32 reg_16b_alpha_x1_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_x0_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902290 RW 0x0008_000c
	UINT32 reg_16b_alpha_x3_o               :16;	//(15:0,RW,0xc) //
	UINT32 reg_16b_alpha_x2_o               :16;	//(31:16,RW,0x8) //
	};
}BE_O26A0_REG_LED_AD_12BIT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902294 RW 0x0000_0004
	UINT32 reg_16b_alpha_x5_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_x4_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902298 RW 0x0048_008c
	UINT32 reg_16b_alpha_x7_o               :16;	//(15:0,RW,0x8c) //
	UINT32 reg_16b_alpha_x6_o               :16;	//(31:16,RW,0x48) //
	};
}BE_O26A0_REG_LED_AD_12BIT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90229C RW 0x0000_0444
	UINT32 reg_16b_alpha_x9_o               :16;	//(15:0,RW,0x444) //
	UINT32 reg_16b_alpha_x8_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022A0 RW 0x0888_0ccc
	UINT32 reg_16b_alpha_x11_o              :16;	//(15:0,RW,0xccc) //
	UINT32 reg_16b_alpha_x10_o              :16;	//(31:16,RW,0x888) //
	};
}BE_O26A0_REG_LED_AD_12BIT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022A4 RW 0x0000_4444
	UINT32 reg_16b_alpha_x13_o              :16;	//(15:0,RW,0x4444) //
	UINT32 reg_16b_alpha_x12_o              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022A8 RW 0x8888_cccc
	UINT32 reg_16b_alpha_x15_o              :16;	//(15:0,RW,0xcccc) //
	UINT32 reg_16b_alpha_x14_o              :16;	//(31:16,RW,0x8888) //
	};
}BE_O26A0_REG_LED_AD_12BIT_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022AC RW 0x0000_0004
	UINT32 reg_16b_alpha_y1_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_y0_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022B0 RW 0x0008_000c
	UINT32 reg_16b_alpha_y3_o               :16;	//(15:0,RW,0xc) //
	UINT32 reg_16b_alpha_y2_o               :16;	//(31:16,RW,0x8) //
	};
}BE_O26A0_REG_LED_AD_12BIT_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022B4 RW 0x0000_0004
	UINT32 reg_16b_alpha_y5_o               :16;	//(15:0,RW,0x4) //
	UINT32 reg_16b_alpha_y4_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022B8 RW 0x0048_008c
	UINT32 reg_16b_alpha_y7_o               :16;	//(15:0,RW,0x8c) //
	UINT32 reg_16b_alpha_y6_o               :16;	//(31:16,RW,0x48) //
	};
}BE_O26A0_REG_LED_AD_12BIT_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022BC RW 0x0000_0444
	UINT32 reg_16b_alpha_y9_o               :16;	//(15:0,RW,0x444) //
	UINT32 reg_16b_alpha_y8_o               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022C0 RW 0x0888_0ccc
	UINT32 reg_16b_alpha_y11_o              :16;	//(15:0,RW,0xccc) //
	UINT32 reg_16b_alpha_y10_o              :16;	//(31:16,RW,0x888) //
	};
}BE_O26A0_REG_LED_AD_12BIT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022C4 RW 0x0000_4444
	UINT32 reg_16b_alpha_y13_o              :16;	//(15:0,RW,0x4444) //
	UINT32 reg_16b_alpha_y12_o              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_LED_AD_12BIT_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022C8 RW 0x8888_cccc
	UINT32 reg_16b_alpha_y15_o              :16;	//(15:0,RW,0xcccc) //
	UINT32 reg_16b_alpha_y14_o              :16;	//(31:16,RW,0x8888) //
	};
}BE_O26A0_REG_LED_AD_12BIT_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022CC RO 0x0000_0000
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
}BE_O26A0_REG_LED_AD_BLU_IF_DB_MEM_PAGE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022D0 RW 0x0000_0000
	UINT32 reg_direction                    :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :15;
	UINT32 reg_shift                        :5;	//(20:16,RW,0x00) //
	UINT32 resvd1                           :11;
	};
}BE_O26A0_REG_LED_AD_BLU_IF_SHIFT_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022D4 RW 0x0000_0000
	UINT32 reg_blu_i2c_rd_ai_addr_clr       :1;	//(0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_AI_ADDR_CLR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022D8 RO 0x0000_0000
	UINT32 reg_blu_i2c_rd_ai_rdata          :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_blu_i2c_rd_ai_raddr          :14;	//(29:16,RO,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_AI_ADDR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022DC RW 0x0000_0000
	UINT32 reg_blu_i2c_rd_mode              :1;	//(0,RW,0x0) //1:auto
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_LED_AD_I2C_RD_MODE_SEL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022E0 RW 0x0000_0010
	UINT32 reg_info_bv_en                   :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_info_bv_header_num           :1;	//(4,RW,0x1) //0:1 header 1:2header(default)
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_LED_AD_INFO_BV_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022E4 RW 0x0000_0000
	UINT32 reg_inf0_bv_header0              :32;	//(31:0,RW,0x0) //chip info packet header
	};
}BE_O26A0_REG_LED_AD_INFO_BV_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9022E8 RW 0x0000_0000
	UINT32 reg_inf0_bv_header1              :32;	//(31:0,RW,0x0) //chip info base address
	};
}BE_O26A0_REG_LED_AD_INFO_BV_CTRL_02_T;

typedef struct {
	BE_O26A0_REG_LED_AD_BV_GEN_HV_SIZE_T                       ad_bv_gen_hv_size;	//0xCC900000
	BE_O26A0_REG_LED_AD_BV_GEN_BLK_NUM_HV_T                 ad_bv_gen_blk_num_hv;	//0xCC900004
	BE_O26A0_REG_LED_AD_HV_RESOLUTION_T                         ad_hv_resolution;	//0xCC900008
	BE_O26A0_REG_LED_AD_SYNC_POL_T                                   ad_sync_pol;	//0xCC90000C
	BE_O26A0_REG_LED_AD_VIN_CONFIG_T                               ad_vin_config;	//0xCC900010
	BE_O26A0_REG_LED_AD_LED_DLY_T                                     ad_led_dly;	//0xCC900014
	BE_O26A0_REG_LED_AD_MONITOR_SEL_T                             ad_monitor_sel;	//0xCC900018
	BE_O26A0_REG_LED_AD_DPATH_ORDER_T                             ad_dpath_order;	//0xCC90001C
	BE_O26A0_REG_LED_AD_RST_ASYNC_BRIDGE_T                   ad_rst_async_bridge;	//0xCC900020
	BE_O26A0_REG_LED_AD_SYNC_SEL_T                                   ad_sync_sel;	//0xCC900024
	BE_O26A0_REG_LED_AD_BV_CLG_SEL_T                               ad_bv_clg_sel;	//0xCC900028
	UINT32                                                    reserved0;	//0xCC90002C
	UINT32                                                    reserved1;	//0xCC900030
	UINT32                                                    reserved2;	//0xCC900034
	UINT32                                                    reserved3;	//0xCC900038
	UINT32                                                    reserved4;	//0xCC90003C
	BE_O26A0_REG_LED_AD_DBG_CTRL_T                                   ad_dbg_ctrl;	//0xCC900040
	BE_O26A0_REG_LED_AD_LUM_T                                             ad_lum;	//0xCC900044
	BE_O26A0_REG_LED_AD_BLU_I2C_WDATA_T                         ad_blu_i2c_wdata;	//0xCC900048
	BE_O26A0_REG_LED_AD_SB_SEL_T                                       ad_sb_sel;	//0xCC90004C
	BE_O26A0_REG_LED_AD_SB_I2C_T                                       ad_sb_i2c;	//0xCC900050
	BE_O26A0_REG_LED_AD_BV_READ_T                                     ad_bv_read;	//0xCC900054
	BE_O26A0_REG_LED_AD_BV_WRITE_T                                   ad_bv_write;	//0xCC900058
	BE_O26A0_REG_LED_AD_BV_RW_STATUS_T                           ad_bv_rw_status;	//0xCC90005C
	UINT32                                                    reserved5;	//0xCC900060
	BE_O26A0_REG_LED_AD_LED_DETOUR_T                               ad_led_detour;	//0xCC900064
	UINT32                                                    reserved6;	//0xCC900068
	UINT32                                                    reserved7;	//0xCC90006C
	UINT32                                                    reserved8;	//0xCC900070
	UINT32                                                    reserved9;	//0xCC900074
	UINT32                                                   reserved10;	//0xCC900078
	UINT32                                                   reserved11;	//0xCC90007C
	BE_O26A0_REG_LED_AD_PAT_ON_T                                       ad_pat_on;	//0xCC900080
	BE_O26A0_REG_LED_AD_PAT_VAL_T                                     ad_pat_val;	//0xCC900084
	BE_O26A0_REG_LED_AD_PAT_H_MIN_MAX_T                         ad_pat_h_min_max;	//0xCC900088
	BE_O26A0_REG_LED_AD_PAT_V_MIN_MAX_T                         ad_pat_v_min_max;	//0xCC90008C
	BE_O26A0_REG_LED_AD_PAT_HV_PPF_T                               ad_pat_hv_ppf;	//0xCC900090
	BE_O26A0_REG_LED_AD_PAT_VAL_R_T                                 ad_pat_val_r;	//0xCC900094
	BE_O26A0_REG_LED_AD_PAT_H_MIN_MAX_R_T                     ad_pat_h_min_max_r;	//0xCC900098
	BE_O26A0_REG_LED_AD_PAT_V_MIN_MAX_R_T                     ad_pat_v_min_max_r;	//0xCC90009C
	BE_O26A0_REG_LED_AD_PAT_BGVAL_T                                 ad_pat_bgval;	//0xCC9000A0
	UINT32                                                   reserved12;	//0xCC9000A4
	UINT32                                                   reserved13;	//0xCC9000A8
	UINT32                                                   reserved14;	//0xCC9000AC
	UINT32                                                   reserved15;	//0xCC9000B0
	UINT32                                                   reserved16;	//0xCC9000B4
	UINT32                                                   reserved17;	//0xCC9000B8
	UINT32                                                   reserved18;	//0xCC9000BC
	BE_O26A0_REG_LED_AD_IWB_R_GAIN_T                               ad_iwb_r_gain;	//0xCC9000C0
	BE_O26A0_REG_LED_AD_IWB_G_GAIN_T                               ad_iwb_g_gain;	//0xCC9000C4
	BE_O26A0_REG_LED_AD_IWB_B_GAIN_T                               ad_iwb_b_gain;	//0xCC9000C8
	UINT32                                                   reserved19;	//0xCC9000CC
	UINT32                                                   reserved20;	//0xCC9000D0
	UINT32                                                   reserved21;	//0xCC9000D4
	UINT32                                                   reserved22;	//0xCC9000D8
	UINT32                                                   reserved23;	//0xCC9000DC
	UINT32                                                   reserved24;	//0xCC9000E0
	BE_O26A0_REG_LED_AD_CRC1_RD_T                                     ad_crc1_rd;	//0xCC9000E4
	BE_O26A0_REG_LED_AD_HDMI_CTRL_T                                 ad_hdmi_ctrl;	//0xCC9000E8
	BE_O26A0_REG_LED_AD_FBC_CTRL_T                                   ad_fbc_ctrl;	//0xCC9000EC
	BE_O26A0_REG_LED_AD_FBC_DPCM_REST_STEP_T               ad_fbc_dpcm_rest_step;	//0xCC9000F0
	BE_O26A0_REG_LED_AD_YC422_CTRL_T                               ad_yc422_ctrl;	//0xCC9000F4
	BE_O26A0_REG_LED_AD_CRC_INFO_T                                   ad_crc_info;	//0xCC9000F8
	BE_O26A0_REG_LED_AD_CRC_RD_T                                       ad_crc_rd;	//0xCC9000FC
	BE_O26A0_REG_LED_AD_HIST_MODE_T                                 ad_hist_mode;	//0xCC900100
	BE_O26A0_REG_LED_AD_HIST_RADDR_T                               ad_hist_raddr;	//0xCC900104
	BE_O26A0_REG_LED_AD_PWM_SC_MODE_T                             ad_pwm_sc_mode;	//0xCC900108
	BE_O26A0_REG_LED_AD_PWM_MAX_MODE_T                           ad_pwm_max_mode;	//0xCC90010C
	BE_O26A0_REG_LED_AD_PWM_IIR_MODE_T                           ad_pwm_iir_mode;	//0xCC900110
	BE_O26A0_REG_LED_AD_PWM_MODE_T                                   ad_pwm_mode;	//0xCC900114
	BE_O26A0_REG_LED_AD_PWM_PEL_MODE_T                           ad_pwm_pel_mode;	//0xCC900118
	BE_O26A0_REG_LED_AD_PWM_EXT_SC_T                               ad_pwm_ext_sc;	//0xCC90011C
	BE_O26A0_REG_LED_AD_PWM_SC_HIST_TH_T                       ad_pwm_sc_hist_th;	//0xCC900120
	BE_O26A0_REG_LED_AD_PWM_SC_APL_TH_T                         ad_pwm_sc_apl_th;	//0xCC900124
	BE_O26A0_REG_LED_AD_PWM_SC_DETECT_RD_T                   ad_pwm_sc_detect_rd;	//0xCC900128
	BE_O26A0_REG_LED_AD_PWM_MAX_CDF_T                             ad_pwm_max_cdf;	//0xCC90012C
	BE_O26A0_REG_LED_AD_PWM_EXT_MAX_T                             ad_pwm_ext_max;	//0xCC900130
	BE_O26A0_REG_LED_AD_PWM_FR_MAX_WEI_T                       ad_pwm_fr_max_wei;	//0xCC900134
	BE_O26A0_REG_LED_AD_PWM_X1_X2_T                                 ad_pwm_x1_x2;	//0xCC900138
	BE_O26A0_REG_LED_AD_PWM_X3_X4_T                                 ad_pwm_x3_x4;	//0xCC90013C
	BE_O26A0_REG_LED_AD_PWM_Y0_Y1_T                                 ad_pwm_y0_y1;	//0xCC900140
	BE_O26A0_REG_LED_AD_PWM_Y2_Y3_T                                 ad_pwm_y2_y3;	//0xCC900144
	BE_O26A0_REG_LED_AD_PWM_Y4_Y5_T                                 ad_pwm_y4_y5;	//0xCC900148
	BE_O26A0_REG_LED_AD_PWM_BV_FR_MAX_RD_T                   ad_pwm_bv_fr_max_rd;	//0xCC90014C
	BE_O26A0_REG_LED_AD_PWM_MAX_RD_T                               ad_pwm_max_rd;	//0xCC900150
	BE_O26A0_REG_LED_AD_PWM_VALUE_RD_T                           ad_pwm_value_rd;	//0xCC900154
	BE_O26A0_REG_LED_AD_PWM_IIR_WEI_T                             ad_pwm_iir_wei;	//0xCC900158
	BE_O26A0_REG_LED_AD_PWM_SC_IIR_STEP_C_T                 ad_pwm_sc_iir_step_c;	//0xCC90015C
	BE_O26A0_REG_LED_AD_PWM_SC_IIR_STEP_P_T                 ad_pwm_sc_iir_step_p;	//0xCC900160
	BE_O26A0_REG_LED_AD_PWM_ADJ_IIR_WEI_RD_T               ad_pwm_adj_iir_wei_rd;	//0xCC900164
	BE_O26A0_REG_LED_AD_PWM_MAF_IIR_STEP_C_T               ad_pwm_maf_iir_step_c;	//0xCC900168
	BE_O26A0_REG_LED_AD_PWM_MAF_IIR_STEP_P_T               ad_pwm_maf_iir_step_p;	//0xCC90016C
	BE_O26A0_REG_LED_AD_PWM_MAF_IIR_MAG_RD_T               ad_pwm_maf_iir_mag_rd;	//0xCC900170
	BE_O26A0_REG_LED_AD_PWM_EXT_VAL_PEL_T                     ad_pwm_ext_val_pel;	//0xCC900174
	BE_O26A0_REG_LED_AD_PWM_BL_TDIF_TH_T                       ad_pwm_bl_tdif_th;	//0xCC900178
	UINT32                                                   reserved25;	//0xCC90017C
	BE_O26A0_REG_LED_AD_MAX_OPT_T                                     ad_max_opt;	//0xCC900180
	BE_O26A0_REG_LED_AD_BLK_MAX_MODE_T                           ad_blk_max_mode;	//0xCC900184
	BE_O26A0_REG_LED_AD_MAX_OPT_MODE_T                           ad_max_opt_mode;	//0xCC900188
	BE_O26A0_REG_LED_AD_MAX_OPT0_1_T                               ad_max_opt0_1;	//0xCC90018C
	BE_O26A0_REG_LED_AD_LEVEL_TH_T                                   ad_level_th;	//0xCC900190
	BE_O26A0_REG_LED_AD_NUMBER_TH_T                                 ad_number_th;	//0xCC900194
	BE_O26A0_REG_LED_AD_APL_T                                             ad_apl;	//0xCC900198
	BE_O26A0_REG_LED_AD_BV_GEN_X1_X2_T                           ad_bv_gen_x1_x2;	//0xCC90019C
	BE_O26A0_REG_LED_AD_BV_GEN_X3_X4_T                           ad_bv_gen_x3_x4;	//0xCC9001A0
	BE_O26A0_REG_LED_AD_BV_GEN_Y0_Y1_T                           ad_bv_gen_y0_y1;	//0xCC9001A4
	BE_O26A0_REG_LED_AD_BV_GEN_Y2_Y3_T                           ad_bv_gen_y2_y3;	//0xCC9001A8
	BE_O26A0_REG_LED_AD_BV_GEN_Y4_Y5_T                           ad_bv_gen_y4_y5;	//0xCC9001AC
	BE_O26A0_REG_LED_AD_BV_GEN_BV_MAX_T                         ad_bv_gen_bv_max;	//0xCC9001B0
	BE_O26A0_REG_LED_AD_BV_MIN_MAX_T                               ad_bv_min_max;	//0xCC9001B4
	BE_O26A0_REG_LED_AD_BV_LUT_MIN_MAX_T                       ad_bv_lut_min_max;	//0xCC9001B8
	BE_O26A0_REG_LED_AD_BV_FINAL_AVG_MIN_MAX_T           ad_bv_final_avg_min_max;	//0xCC9001BC
	BE_O26A0_REG_LED_AD_BV_RCTRL_MODE_T                         ad_bv_rctrl_mode;	//0xCC9001C0
	BE_O26A0_REG_LED_AD_PIC_ATTR_T                                   ad_pic_attr;	//0xCC9001C4
	BE_O26A0_REG_LED_AD_LR_SYNC_SEL_T                             ad_lr_sync_sel;	//0xCC9001C8
	UINT32                                                   reserved26;	//0xCC9001CC
	UINT32                                                   reserved27;	//0xCC9001D0
	UINT32                                                   reserved28;	//0xCC9001D4
	UINT32                                                   reserved29;	//0xCC9001D8
	UINT32                                                   reserved30;	//0xCC9001DC
	UINT32                                                   reserved31;	//0xCC9001E0
	UINT32                                                   reserved32;	//0xCC9001E4
	UINT32                                                   reserved33;	//0xCC9001E8
	UINT32                                                   reserved34;	//0xCC9001EC
	UINT32                                                   reserved35;	//0xCC9001F0
	UINT32                                                   reserved36;	//0xCC9001F4
	UINT32                                                   reserved37;	//0xCC9001F8
	UINT32                                                   reserved38;	//0xCC9001FC
	UINT32                                                   reserved39;	//0xCC900200
	UINT32                                                   reserved40;	//0xCC900204
	UINT32                                                   reserved41;	//0xCC900208
	UINT32                                                   reserved42;	//0xCC90020C
	UINT32                                                   reserved43;	//0xCC900210
	UINT32                                                   reserved44;	//0xCC900214
	UINT32                                                   reserved45;	//0xCC900218
	UINT32                                                   reserved46;	//0xCC90021C
	UINT32                                                   reserved47;	//0xCC900220
	UINT32                                                   reserved48;	//0xCC900224
	UINT32                                                   reserved49;	//0xCC900228
	UINT32                                                   reserved50;	//0xCC90022C
	UINT32                                                   reserved51;	//0xCC900230
	UINT32                                                   reserved52;	//0xCC900234
	UINT32                                                   reserved53;	//0xCC900238
	UINT32                                                   reserved54;	//0xCC90023C
	BE_O26A0_REG_LED_AD_LUT_MODE_T                                   ad_lut_mode;	//0xCC900240
	BE_O26A0_REG_LED_AD_EX_ABV_T                                       ad_ex_abv;	//0xCC900244
	UINT32                                                   reserved55;	//0xCC900248
	BE_O26A0_REG_LED_AD_DC_LUT_RADDR_T                           ad_dc_lut_raddr;	//0xCC90024C
	BE_O26A0_REG_LED_AD_DC_LUT_RDATA_T                           ad_dc_lut_rdata;	//0xCC900250
	UINT32                                                   reserved56;	//0xCC900254
	BE_O26A0_REG_LED_AD_LUT_AVG_SEL_T                             ad_lut_avg_sel;	//0xCC900258
	BE_O26A0_REG_LED_AD_LUT_OFFSET_EN_T                         ad_lut_offset_en;	//0xCC90025C
	BE_O26A0_REG_LED_AD_LUT_OFFSET_X1_X2_T                   ad_lut_offset_x1_x2;	//0xCC900260
	BE_O26A0_REG_LED_AD_LUT_OFFSET_X3_X4_T                   ad_lut_offset_x3_x4;	//0xCC900264
	BE_O26A0_REG_LED_AD_LUT_OFFSET_Y0_Y1_T                   ad_lut_offset_y0_y1;	//0xCC900268
	BE_O26A0_REG_LED_AD_LUT_OFFSET_Y2_Y3_T                   ad_lut_offset_y2_y3;	//0xCC90026C
	BE_O26A0_REG_LED_AD_LUT_OFFSET_Y4_Y5_T                   ad_lut_offset_y4_y5;	//0xCC900270
	BE_O26A0_REG_LED_AD_LD_SMOOTH_OFF_T                         ad_ld_smooth_off;	//0xCC900274
	BE_O26A0_REG_LED_AD_LD_SMOOTH_OFF_STEP_T               ad_ld_smooth_off_step;	//0xCC900278
	BE_O26A0_REG_LED_AD_LD_BV_EXT_MAX_T                         ad_ld_bv_ext_max;	//0xCC90027C
	BE_O26A0_REG_LED_AD_UMASK_UM_EN_T                             ad_umask_um_en;	//0xCC900280
	BE_O26A0_REG_LED_AD_UMASK_5X5_T                                 ad_umask_5x5;	//0xCC900284
	BE_O26A0_REG_LED_AD_UMASK_COARING_T                         ad_umask_coaring;	//0xCC900288
	BE_O26A0_REG_LED_AD_UMASK_GAIN_T                               ad_umask_gain;	//0xCC90028C
	BE_O26A0_REG_LED_AD_UMASK_WR_COEFF_T                       ad_umask_wr_coeff;	//0xCC900290
	BE_O26A0_REG_LED_AD_UMASK_RD_COEFF_T                       ad_umask_rd_coeff;	//0xCC900294
	UINT32                                                   reserved57;	//0xCC900298
	UINT32                                                   reserved58;	//0xCC90029C
	UINT32                                                   reserved59;	//0xCC9002A0
	UINT32                                                   reserved60;	//0xCC9002A4
	UINT32                                                   reserved61;	//0xCC9002A8
	UINT32                                                   reserved62;	//0xCC9002AC
	UINT32                                                   reserved63;	//0xCC9002B0
	UINT32                                                   reserved64;	//0xCC9002B4
	UINT32                                                   reserved65;	//0xCC9002B8
	UINT32                                                   reserved66;	//0xCC9002BC
	BE_O26A0_REG_LED_AD_T_SF_T                                           ad_t_sf;	//0xCC9002C0
	BE_O26A0_REG_LED_AD_KMODE_T                                         ad_kmode;	//0xCC9002C4
	BE_O26A0_REG_LED_AD_HVKMASK_T                                     ad_hvkmask;	//0xCC9002C8
	BE_O26A0_REG_LED_AD_BLEND_ALPHA_T                             ad_blend_alpha;	//0xCC9002CC
	UINT32                                                   reserved67;	//0xCC9002D0
	UINT32                                                   reserved68;	//0xCC9002D4
	UINT32                                                   reserved69;	//0xCC9002D8
	UINT32                                                   reserved70;	//0xCC9002DC
	UINT32                                                   reserved71;	//0xCC9002E0
	UINT32                                                   reserved72;	//0xCC9002E4
	UINT32                                                   reserved73;	//0xCC9002E8
	UINT32                                                   reserved74;	//0xCC9002EC
	UINT32                                                   reserved75;	//0xCC9002F0
	UINT32                                                   reserved76;	//0xCC9002F4
	UINT32                                                   reserved77;	//0xCC9002F8
	UINT32                                                   reserved78;	//0xCC9002FC
	BE_O26A0_REG_LED_AD_TF_OPMODE_T                                 ad_tf_opmode;	//0xCC900300
	BE_O26A0_REG_LED_AD_A_PARA_T                                       ad_a_para;	//0xCC900304
	BE_O26A0_REG_LED_AD_SC_ADJ_EN_T                                 ad_sc_adj_en;	//0xCC900308
	BE_O26A0_REG_LED_AD_MD_ADJ_EN_T                                 ad_md_adj_en;	//0xCC90030C
	BE_O26A0_REG_LED_AD_MD_X1_T                                         ad_md_x1;	//0xCC900310
	BE_O26A0_REG_LED_AD_MD_X2_T                                         ad_md_x2;	//0xCC900314
	BE_O26A0_REG_LED_AD_MD_X3_T                                         ad_md_x3;	//0xCC900318
	BE_O26A0_REG_LED_AD_MD_X4_T                                         ad_md_x4;	//0xCC90031C
	BE_O26A0_REG_LED_AD_MD_Y0_T                                         ad_md_y0;	//0xCC900320
	BE_O26A0_REG_LED_AD_MD_Y1_T                                         ad_md_y1;	//0xCC900324
	BE_O26A0_REG_LED_AD_MD_Y2_T                                         ad_md_y2;	//0xCC900328
	BE_O26A0_REG_LED_AD_MD_Y3_T                                         ad_md_y3;	//0xCC90032C
	BE_O26A0_REG_LED_AD_MD_Y4_T                                         ad_md_y4;	//0xCC900330
	BE_O26A0_REG_LED_AD_MD_Y5_T                                         ad_md_y5;	//0xCC900334
	BE_O26A0_REG_LED_AD_BV_FINAL_AVG_IIR_T                   ad_bv_final_avg_iir;	//0xCC900338
	BE_O26A0_REG_LED_AD_BV_MID_AVG_IIR_T                       ad_bv_mid_avg_iir;	//0xCC90033C
	BE_O26A0_REG_LED_AD_LED_MODE_T                                   ad_led_mode;	//0xCC900340
	BE_O26A0_REG_LED_AD_LRES_BNH_BNV_T                           ad_lres_bnh_bnv;	//0xCC900344
	BE_O26A0_REG_LED_AD_LRES_BSH_BSV_T                           ad_lres_bsh_bsv;	//0xCC900348
	BE_O26A0_REG_LED_AD_SBI_BNH_BNV_T                             ad_sbi_bnh_bnv;	//0xCC90034C
	BE_O26A0_REG_LED_AD_SBI_BSH_BSV_T                             ad_sbi_bsh_bsv;	//0xCC900350
	BE_O26A0_REG_LED_AD_TAB1_RD_SEL_T                             ad_tab1_rd_sel;	//0xCC900354
	BE_O26A0_REG_LED_AD_TAB1_RDATA_T                               ad_tab1_rdata;	//0xCC900358
	BE_O26A0_REG_LED_AD_TAB5_RD_SEL_T                             ad_tab5_rd_sel;	//0xCC90035C
	BE_O26A0_REG_LED_AD_TAB5_RDATA_T                               ad_tab5_rdata;	//0xCC900360
	BE_O26A0_REG_LED_AD_HFC_RD_SEL_T                               ad_hfc_rd_sel;	//0xCC900364
	BE_O26A0_REG_LED_AD_HFC_RDATA_T                                 ad_hfc_rdata;	//0xCC900368
	BE_O26A0_REG_LED_AD_VFC_RD_SEL_T                               ad_vfc_rd_sel;	//0xCC90036C
	BE_O26A0_REG_LED_AD_VFC_RDATA_T                                 ad_vfc_rdata;	//0xCC900370
	BE_O26A0_REG_LED_AD_POLARIS_MODE_T                           ad_polaris_mode;	//0xCC900374
	UINT32                                                   reserved79;	//0xCC900378
	UINT32                                                   reserved80;	//0xCC90037C
	BE_O26A0_REG_LED_AD_COMP_EN_T                                     ad_comp_en;	//0xCC900380
	BE_O26A0_REG_LED_AD_CONT_GAIN_T                                 ad_cont_gain;	//0xCC900384
	BE_O26A0_REG_LED_AD_COMP_IN_T                                     ad_comp_in;	//0xCC900388
	BE_O26A0_REG_LED_AD_PC_RADDR_T                                   ad_pc_raddr;	//0xCC90038C
	BE_O26A0_REG_LED_AD_PC_RDATA_T                                   ad_pc_rdata;	//0xCC900390
	UINT32                                                   reserved81;	//0xCC900394
	UINT32                                                   reserved82;	//0xCC900398
	UINT32                                                   reserved83;	//0xCC90039C
	UINT32                                                   reserved84;	//0xCC9003A0
	UINT32                                                   reserved85;	//0xCC9003A4
	UINT32                                                   reserved86;	//0xCC9003A8
	UINT32                                                   reserved87;	//0xCC9003AC
	UINT32                                                   reserved88;	//0xCC9003B0
	UINT32                                                   reserved89;	//0xCC9003B4
	UINT32                                                   reserved90;	//0xCC9003B8
	UINT32                                                   reserved91;	//0xCC9003BC
	UINT32                                                   reserved92;	//0xCC9003C0
	UINT32                                                   reserved93;	//0xCC9003C4
	UINT32                                                   reserved94;	//0xCC9003C8
	UINT32                                                   reserved95;	//0xCC9003CC
	UINT32                                                   reserved96;	//0xCC9003D0
	UINT32                                                   reserved97;	//0xCC9003D4
	UINT32                                                   reserved98;	//0xCC9003D8
	UINT32                                                   reserved99;	//0xCC9003DC
	UINT32                                                  reserved100;	//0xCC9003E0
	UINT32                                                  reserved101;	//0xCC9003E4
	UINT32                                                  reserved102;	//0xCC9003E8
	UINT32                                                  reserved103;	//0xCC9003EC
	UINT32                                                  reserved104;	//0xCC9003F0
	UINT32                                                  reserved105;	//0xCC9003F4
	UINT32                                                  reserved106;	//0xCC9003F8
	UINT32                                                  reserved107;	//0xCC9003FC
	BE_O26A0_REG_LED_AD_GBL_T                                             ad_gbl;	//0xCC900400
	UINT32                                                  reserved108;	//0xCC900404
	BE_O26A0_REG_LED_AD_BV_DLY_T                                       ad_bv_dly;	//0xCC900408
	BE_O26A0_REG_LED_AD_BLU_BV_SEL_T                               ad_blu_bv_sel;	//0xCC90040C
	UINT32                                                  reserved109;	//0xCC900410
	UINT32                                                  reserved110;	//0xCC900414
	UINT32                                                  reserved111;	//0xCC900418
	UINT32                                                  reserved112;	//0xCC90041C
	UINT32                                                  reserved113;	//0xCC900420
	UINT32                                                  reserved114;	//0xCC900424
	UINT32                                                  reserved115;	//0xCC900428
	UINT32                                                  reserved116;	//0xCC90042C
	UINT32                                                  reserved117;	//0xCC900430
	UINT32                                                  reserved118;	//0xCC900434
	UINT32                                                  reserved119;	//0xCC900438
	UINT32                                                  reserved120;	//0xCC90043C
	BE_O26A0_REG_LED_AD_INSTR_WR_REQ_T                           ad_instr_wr_req;	//0xCC900440
	BE_O26A0_REG_LED_AD_INSTR_WDATA_T                             ad_instr_wdata;	//0xCC900444
	BE_O26A0_REG_LED_AD_INSTR_RDATA_T                             ad_instr_rdata;	//0xCC900448
	BE_O26A0_REG_LED_AD_INSTR_DGB_T                                 ad_instr_dgb;	//0xCC90044C
	UINT32                                                  reserved121;	//0xCC900450
	UINT32                                                  reserved122;	//0xCC900454
	UINT32                                                  reserved123;	//0xCC900458
	UINT32                                                  reserved124;	//0xCC90045C
	UINT32                                                  reserved125;	//0xCC900460
	UINT32                                                  reserved126;	//0xCC900464
	UINT32                                                  reserved127;	//0xCC900468
	UINT32                                                  reserved128;	//0xCC90046C
	UINT32                                                  reserved129;	//0xCC900470
	UINT32                                                  reserved130;	//0xCC900474
	UINT32                                                  reserved131;	//0xCC900478
	UINT32                                                  reserved132;	//0xCC90047C
	BE_O26A0_REG_LED_AD_BLC_MODE_T                                   ad_blc_mode;	//0xCC900480
	BE_O26A0_REG_LED_AD_BSF_C0_T                                       ad_bsf_c0;	//0xCC900484
	BE_O26A0_REG_LED_AD_BSF_C1_T                                       ad_bsf_c1;	//0xCC900488
	BE_O26A0_REG_LED_AD_BSF_C2_T                                       ad_bsf_c2;	//0xCC90048C
	BE_O26A0_REG_LED_AD_BSF_RATIO0_T                               ad_bsf_ratio0;	//0xCC900490
	BE_O26A0_REG_LED_AD_BSF_RATIO1_T                               ad_bsf_ratio1;	//0xCC900494
	BE_O26A0_REG_LED_AD_BSF_RATIO2_T                               ad_bsf_ratio2;	//0xCC900498
	BE_O26A0_REG_LED_AD_A0_GN_T                                         ad_a0_gn;	//0xCC90049C
	BE_O26A0_REG_LED_AD_A1_GN_T                                         ad_a1_gn;	//0xCC9004A0
	BE_O26A0_REG_LED_AD_A2_GN_T                                         ad_a2_gn;	//0xCC9004A4
	BE_O26A0_REG_LED_AD_A0_RATIO_T                                   ad_a0_ratio;	//0xCC9004A8
	BE_O26A0_REG_LED_AD_A1_RATIO_T                                   ad_a1_ratio;	//0xCC9004AC
	BE_O26A0_REG_LED_AD_DRV_MAX_T                                     ad_drv_max;	//0xCC9004B0
	BE_O26A0_REG_LED_AD_BLC_EN_T                                       ad_blc_en;	//0xCC9004B4
	BE_O26A0_REG_LED_AD_BLC_TEMPO_TH_T                           ad_blc_tempo_th;	//0xCC9004B8
	BE_O26A0_REG_LED_AD_BLC_FRAME_NUM_T                         ad_blc_frame_num;	//0xCC9004BC
	BE_O26A0_REG_LED_AD_MEM_ADDR_CLR_T                           ad_mem_addr_clr;	//0xCC9004C0
	BE_O26A0_REG_LED_AD_MEM_DL_SBI_HCOEFF_T                 ad_mem_dl_sbi_hcoeff;	//0xCC9004C4
	BE_O26A0_REG_LED_AD_MEM_DL_SBI_VCOEFF_T                 ad_mem_dl_sbi_vcoeff;	//0xCC9004C8
	BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_A_T             ad_mem_dl_pixel_comp_a;	//0xCC9004CC
	BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_B_T             ad_mem_dl_pixel_comp_b;	//0xCC9004D0
	BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_C_T             ad_mem_dl_pixel_comp_c;	//0xCC9004D4
	BE_O26A0_REG_LED_AD_MEM_DL_PIXEL_COMP_D_T             ad_mem_dl_pixel_comp_d;	//0xCC9004D8
	BE_O26A0_REG_LED_AD_UPPER_DC_LUT_T                           ad_upper_dc_lut;	//0xCC9004DC
	BE_O26A0_REG_LED_AD_LOWER_DC_LUT_T                           ad_lower_dc_lut;	//0xCC9004E0
	BE_O26A0_REG_LED_AD_FC_TAB1_T                                     ad_fc_tab1;	//0xCC9004E4
	BE_O26A0_REG_LED_AD_FC_TAB5_T                                     ad_fc_tab5;	//0xCC9004E8
	UINT32                                                  reserved133;	//0xCC9004EC
	UINT32                                                  reserved134;	//0xCC9004F0
	UINT32                                                  reserved135;	//0xCC9004F4
	UINT32                                                  reserved136;	//0xCC9004F8
	UINT32                                                  reserved137;	//0xCC9004FC
	BE_O26A0_REG_LED_AD_MEAN_IN_SEL_T                             ad_mean_in_sel;	//0xCC900500
	BE_O26A0_REG_LED_AD_MEAN_T                                           ad_mean;	//0xCC900504
	UINT32                                                  reserved138;	//0xCC900508
	UINT32                                                  reserved139;	//0xCC90050C
	UINT32                                                  reserved140;	//0xCC900510
	UINT32                                                  reserved141;	//0xCC900514
	UINT32                                                  reserved142;	//0xCC900518
	UINT32                                                  reserved143;	//0xCC90051C
	UINT32                                                  reserved144;	//0xCC900520
	UINT32                                                  reserved145;	//0xCC900524
	UINT32                                                  reserved146;	//0xCC900528
	UINT32                                                  reserved147;	//0xCC90052C
	UINT32                                                  reserved148;	//0xCC900530
	UINT32                                                  reserved149;	//0xCC900534
	UINT32                                                  reserved150;	//0xCC900538
	UINT32                                                  reserved151;	//0xCC90053C
	BE_O26A0_REG_LED_AD_RP_HV_POS_T                                 ad_rp_hv_pos;	//0xCC900540
	BE_O26A0_REG_LED_AD_RP_MAKE_EN_T                               ad_rp_make_en;	//0xCC900544
	BE_O26A0_REG_LED_AD_RP_R_VALUE_T                               ad_rp_r_value;	//0xCC900548
	BE_O26A0_REG_LED_AD_RP_G_VALUE_T                               ad_rp_g_value;	//0xCC90054C
	BE_O26A0_REG_LED_AD_RP_B_VALUE_T                               ad_rp_b_value;	//0xCC900550
	UINT32                                                  reserved152;	//0xCC900554
	BE_O26A0_REG_LED_AD_ALEF2_MODE_T                               ad_alef2_mode;	//0xCC900558
	BE_O26A0_REG_LED_AD_ALEF2_BLOCK_NUM_T                     ad_alef2_block_num;	//0xCC90055C
	BE_O26A0_REG_LED_AD_ALEF2_ADDR_CLR_T                       ad_alef2_addr_clr;	//0xCC900560
	BE_O26A0_REG_LED_AD_ALEF2_CFG_LUT_T                         ad_alef2_cfg_lut;	//0xCC900564
	BE_O26A0_REG_LED_AD_ALEF2_CFG_LUT_RD_T                   ad_alef2_cfg_lut_rd;	//0xCC900568
	BE_O26A0_REG_LED_AD_ALEF2_GAIN_LUT_T                       ad_alef2_gain_lut;	//0xCC90056C
	BE_O26A0_REG_LED_AD_ALEF2_GAIN_LUT_RD_T                 ad_alef2_gain_lut_rd;	//0xCC900570
	BE_O26A0_REG_LED_AD_ALEF2_MAXOPT_LUT_T                   ad_alef2_maxopt_lut;	//0xCC900574
	BE_O26A0_REG_LED_AD_ALEF2_MAXOPT_LUT_RD_T             ad_alef2_maxopt_lut_rd;	//0xCC900578
	BE_O26A0_REG_LED_AD_ALEF2_MAXVALUE_EN_T                 ad_alef2_maxvalue_en;	//0xCC90057C
	BE_O26A0_REG_LED_AD_DISP_BV_EN_T                               ad_disp_bv_en;	//0xCC900580
	BE_O26A0_REG_LED_AD_DSIP_BV_ADDR_T                           ad_dsip_bv_addr;	//0xCC900584
	UINT32                                                  reserved153;	//0xCC900588
	UINT32                                                  reserved154;	//0xCC90058C
	UINT32                                                  reserved155;	//0xCC900590
	UINT32                                                  reserved156;	//0xCC900594
	UINT32                                                  reserved157;	//0xCC900598
	UINT32                                                  reserved158;	//0xCC90059C
	UINT32                                                  reserved159;	//0xCC9005A0
	UINT32                                                  reserved160;	//0xCC9005A4
	UINT32                                                  reserved161;	//0xCC9005A8
	UINT32                                                  reserved162;	//0xCC9005AC
	UINT32                                                  reserved163;	//0xCC9005B0
	UINT32                                                  reserved164;	//0xCC9005B4
	UINT32                                                  reserved165;	//0xCC9005B8
	UINT32                                                  reserved166;	//0xCC9005BC
	BE_O26A0_REG_LED_AD_DITHER_EN_T                                 ad_dither_en;	//0xCC9005C0
	BE_O26A0_REG_LED_AD_DITHER_EN_N2_T                           ad_dither_en_n2;	//0xCC9005C4
	UINT32                                                  reserved167;	//0xCC9005C8
	BE_O26A0_REG_LED_AD_BPL_SLD_SEL_T                             ad_bpl_sld_sel;	//0xCC9005CC
	BE_O26A0_REG_LED_AD_BLU_GAIN_EN_T                             ad_blu_gain_en;	//0xCC9005D0
	BE_O26A0_REG_LED_AD_BLU_GAIN_ADDR_CLR_T                 ad_blu_gain_addr_clr;	//0xCC9005D4
	BE_O26A0_REG_LED_AD_BLU_GAIN_WD_T                             ad_blu_gain_wd;	//0xCC9005D8
	BE_O26A0_REG_LED_AD_BLU_GAIN_RD_T                             ad_blu_gain_rd;	//0xCC9005DC
	BE_O26A0_REG_LED_AD_BLU_BV_ADDR_CLR_T                     ad_blu_bv_addr_clr;	//0xCC9005E0
	BE_O26A0_REG_LED_AD_BLU_BV_RD_T                                 ad_blu_bv_rd;	//0xCC9005E4
	BE_O26A0_REG_LED_AD_BLE_GAIN_EN_T                             ad_ble_gain_en;	//0xCC9005E8
	BE_O26A0_REG_LED_AD_BLE_GAIN_ADDR_CLR_T                 ad_ble_gain_addr_clr;	//0xCC9005EC
	BE_O26A0_REG_LED_AD_BLE_GAIN_WD_T                             ad_ble_gain_wd;	//0xCC9005F0
	BE_O26A0_REG_LED_AD_BLE_GAIN_RD_T                             ad_ble_gain_rd;	//0xCC9005F4
	UINT32                                                  reserved168;	//0xCC9005F8
	UINT32                                                  reserved169;	//0xCC9005FC
	BE_O26A0_REG_LED_AD_DPG_EN_T                                       ad_dpg_en;	//0xCC900600
	BE_O26A0_REG_LED_AD_DPG_LUT_WR_DONE_T                     ad_dpg_lut_wr_done;	//0xCC900604
	BE_O26A0_REG_LED_AD_DPG_LUT_WDATA_T                         ad_dpg_lut_wdata;	//0xCC900608
	BE_O26A0_REG_LED_AD_DPG_LUT_RDATA_T                         ad_dpg_lut_rdata;	//0xCC90060C
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_00_T                       ad_bvgain_ctrl_00;	//0xCC900610
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_01_T                       ad_bvgain_ctrl_01;	//0xCC900614
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_02_T                       ad_bvgain_ctrl_02;	//0xCC900618
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_03_T                       ad_bvgain_ctrl_03;	//0xCC90061C
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_04_T                       ad_bvgain_ctrl_04;	//0xCC900620
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_05_T                       ad_bvgain_ctrl_05;	//0xCC900624
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_06_T                       ad_bvgain_ctrl_06;	//0xCC900628
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_07_T                       ad_bvgain_ctrl_07;	//0xCC90062C
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_08_T                       ad_bvgain_ctrl_08;	//0xCC900630
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_09_T                       ad_bvgain_ctrl_09;	//0xCC900634
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_10_T                       ad_bvgain_ctrl_10;	//0xCC900638
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_11_T                       ad_bvgain_ctrl_11;	//0xCC90063C
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_12_T                       ad_bvgain_ctrl_12;	//0xCC900640
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_13_T                       ad_bvgain_ctrl_13;	//0xCC900644
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_14_T                       ad_bvgain_ctrl_14;	//0xCC900648
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_15_T                       ad_bvgain_ctrl_15;	//0xCC90064C
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_16_T                       ad_bvgain_ctrl_16;	//0xCC900650
	BE_O26A0_REG_LED_AD_BVGAIN_CTRL_17_T                       ad_bvgain_ctrl_17;	//0xCC900654
	UINT32                                                  reserved170;	//0xCC900658
	UINT32                                                  reserved171;	//0xCC90065C
	UINT32                                                  reserved172;	//0xCC900660
	BE_O26A0_REG_LED_AD_BV_MID0_AVG_MIN_MAX_T             ad_bv_mid0_avg_min_max;	//0xCC900664
	UINT32                                                  reserved173;	//0xCC900668
	UINT32                                                  reserved174;	//0xCC90066C
	UINT32                                                  reserved175;	//0xCC900670
	UINT32                                                  reserved176;	//0xCC900674
	UINT32                                                  reserved177;	//0xCC900678
	UINT32                                                  reserved178;	//0xCC90067C
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_00_T                         ad_bvbpl_ctrl_00;	//0xCC900680
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_01_T                         ad_bvbpl_ctrl_01;	//0xCC900684
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_02_T                         ad_bvbpl_ctrl_02;	//0xCC900688
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_03_T                         ad_bvbpl_ctrl_03;	//0xCC90068C
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_04_T                         ad_bvbpl_ctrl_04;	//0xCC900690
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_05_T                         ad_bvbpl_ctrl_05;	//0xCC900694
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_06_T                         ad_bvbpl_ctrl_06;	//0xCC900698
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_07_T                         ad_bvbpl_ctrl_07;	//0xCC90069C
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_08_T                         ad_bvbpl_ctrl_08;	//0xCC9006A0
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_09_T                         ad_bvbpl_ctrl_09;	//0xCC9006A4
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_10_T                         ad_bvbpl_ctrl_10;	//0xCC9006A8
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_11_T                         ad_bvbpl_ctrl_11;	//0xCC9006AC
	BE_O26A0_REG_LED_AD_BVBPL_CTRL_12_T                         ad_bvbpl_ctrl_12;	//0xCC9006B0
	BE_O26A0_REG_LED_AD_BV_MID1_AVG_MIN_MAX_T             ad_bv_mid1_avg_min_max;	//0xCC9006B4
	BE_O26A0_REG_LED_AD_BV_PG_CTRL_00_T                         ad_bv_pg_ctrl_00;	//0xCC9006B8
	UINT32                                                  reserved179;	//0xCC9006BC
	BE_O26A0_REG_LED_AD_WB2P_EN_T                                     ad_wb2p_en;	//0xCC9006C0
	BE_O26A0_REG_LED_AD_WB2P_R_GAIN_T                             ad_wb2p_r_gain;	//0xCC9006C4
	BE_O26A0_REG_LED_AD_WB2P_G_GAIN_T                             ad_wb2p_g_gain;	//0xCC9006C8
	BE_O26A0_REG_LED_AD_WB2P_B_GAIN_T                             ad_wb2p_b_gain;	//0xCC9006CC
	BE_O26A0_REG_LED_AD_WB2P_R_OFFSET_T                         ad_wb2p_r_offset;	//0xCC9006D0
	BE_O26A0_REG_LED_AD_WB2P_G_OFFSET_T                         ad_wb2p_g_offset;	//0xCC9006D4
	BE_O26A0_REG_LED_AD_WB2P_B_OFFSET_T                         ad_wb2p_b_offset;	//0xCC9006D8
	UINT32                                                  reserved180;	//0xCC9006DC
	BE_O26A0_REG_LED_AD_BV_GSC_CTRL_00_T                       ad_bv_gsc_ctrl_00;	//0xCC9006E0
	UINT32                                                  reserved181;	//0xCC9006E4
	UINT32                                                  reserved182;	//0xCC9006E8
	UINT32                                                  reserved183;	//0xCC9006EC
	UINT32                                                  reserved184;	//0xCC9006F0
	UINT32                                                  reserved185;	//0xCC9006F4
	UINT32                                                  reserved186;	//0xCC9006F8
	UINT32                                                  reserved187;	//0xCC9006FC
	BE_O26A0_REG_LED_AD_OUT_CTRL_00_T                             ad_out_ctrl_00;	//0xCC900700
	BE_O26A0_REG_LED_AD_OUT_CTRL_01_T                             ad_out_ctrl_01;	//0xCC900704
	BE_O26A0_REG_LED_AD_OUT_CTRL_02_T                             ad_out_ctrl_02;	//0xCC900708
	BE_O26A0_REG_LED_AD_OUT_CTRL_03_T                             ad_out_ctrl_03;	//0xCC90070C
	BE_O26A0_REG_LED_AD_OUT_CTRL_04_T                             ad_out_ctrl_04;	//0xCC900710
	BE_O26A0_REG_LED_AD_OUT_CTRL_05_T                             ad_out_ctrl_05;	//0xCC900714
	BE_O26A0_REG_LED_AD_OUT_CTRL_06_T                             ad_out_ctrl_06;	//0xCC900718
	BE_O26A0_REG_LED_AD_OUT_CTRL_07_T                             ad_out_ctrl_07;	//0xCC90071C
	BE_O26A0_REG_LED_AD_OUT_CTRL_08_T                             ad_out_ctrl_08;	//0xCC900720
	BE_O26A0_REG_LED_AD_OUT_CTRL_09_T                             ad_out_ctrl_09;	//0xCC900724
	BE_O26A0_REG_LED_AD_OUT_CTRL_10_T                             ad_out_ctrl_10;	//0xCC900728
	BE_O26A0_REG_LED_AD_OUT_CTRL_11_T                             ad_out_ctrl_11;	//0xCC90072C
	UINT32                                                  reserved188;	//0xCC900730
	UINT32                                                  reserved189;	//0xCC900734
	UINT32                                                  reserved190;	//0xCC900738
	UINT32                                                  reserved191;	//0xCC90073C
	BE_O26A0_REG_LED_AD_OUT_STAT_00_T                             ad_out_stat_00;	//0xCC900740
	BE_O26A0_REG_LED_AD_OUT_STAT_01_T                             ad_out_stat_01;	//0xCC900744
	BE_O26A0_REG_LED_AD_OUT_STAT_02_T                             ad_out_stat_02;	//0xCC900748
	BE_O26A0_REG_LED_AD_OUT_STAT_03_T                             ad_out_stat_03;	//0xCC90074C
	BE_O26A0_REG_LED_AD_OUT_STAT_04_T                             ad_out_stat_04;	//0xCC900750
	BE_O26A0_REG_LED_AD_OUT_STAT_05_T                             ad_out_stat_05;	//0xCC900754
	BE_O26A0_REG_LED_AD_OUT_STAT_06_T                             ad_out_stat_06;	//0xCC900758
	BE_O26A0_REG_LED_AD_OUT_STAT_07_T                             ad_out_stat_07;	//0xCC90075C
	BE_O26A0_REG_LED_AD_OUT_STAT_08_T                             ad_out_stat_08;	//0xCC900760
	BE_O26A0_REG_LED_AD_OUT_STAT_09_T                             ad_out_stat_09;	//0xCC900764
	BE_O26A0_REG_LED_AD_OUT_STAT_10_T                             ad_out_stat_10;	//0xCC900768
	BE_O26A0_REG_LED_AD_OUT_STAT_11_T                             ad_out_stat_11;	//0xCC90076C
	BE_O26A0_REG_LED_AD_APL_VALUE_OP_T                           ad_apl_value_op;	//0xCC900770
	BE_O26A0_REG_LED_AD_APL_MAX_OUT_T                             ad_apl_max_out;	//0xCC900774
	BE_O26A0_REG_LED_AD_APL_DBG_OUT_T                             ad_apl_dbg_out;	//0xCC900778
	UINT32                                                  reserved192;	//0xCC90077C
	BE_O26A0_REG_LED_AD_OAPL_EOTF_WR_DONE_T                 ad_oapl_eotf_wr_done;	//0xCC900780
	BE_O26A0_REG_LED_AD_OAPL_EOTF_WDATA_T                     ad_oapl_eotf_wdata;	//0xCC900784
	BE_O26A0_REG_LED_AD_OAPL_EOTF_RDATA_T                     ad_oapl_eotf_rdata;	//0xCC900788
	UINT32                                                  reserved193;	//0xCC90078C
	UINT32                                                  reserved194;	//0xCC900790
	UINT32                                                  reserved195;	//0xCC900794
	UINT32                                                  reserved196;	//0xCC900798
	UINT32                                                  reserved197;	//0xCC90079C
	UINT32                                                  reserved198;	//0xCC9007A0
	UINT32                                                  reserved199;	//0xCC9007A4
	UINT32                                                  reserved200;	//0xCC9007A8
	UINT32                                                  reserved201;	//0xCC9007AC
	UINT32                                                  reserved202;	//0xCC9007B0
	UINT32                                                  reserved203;	//0xCC9007B4
	UINT32                                                  reserved204;	//0xCC9007B8
	UINT32                                                  reserved205;	//0xCC9007BC
	UINT32                                                  reserved206;	//0xCC9007C0
	UINT32                                                  reserved207;	//0xCC9007C4
	UINT32                                                  reserved208;	//0xCC9007C8
	UINT32                                                  reserved209;	//0xCC9007CC
	UINT32                                                  reserved210;	//0xCC9007D0
	UINT32                                                  reserved211;	//0xCC9007D4
	UINT32                                                  reserved212;	//0xCC9007D8
	UINT32                                                  reserved213;	//0xCC9007DC
	UINT32                                                  reserved214;	//0xCC9007E0
	UINT32                                                  reserved215;	//0xCC9007E4
	UINT32                                                  reserved216;	//0xCC9007E8
	UINT32                                                  reserved217;	//0xCC9007EC
	UINT32                                                  reserved218;	//0xCC9007F0
	UINT32                                                  reserved219;	//0xCC9007F4
	UINT32                                                  reserved220;	//0xCC9007F8
	UINT32                                                  reserved221;	//0xCC9007FC
	BE_O26A0_REG_LED_AD_MON_SYNC_IN_0_T                         ad_mon_sync_in_0;	//0xCC900800
	BE_O26A0_REG_LED_AD_MON_SYNC_IN_1_T                         ad_mon_sync_in_1;	//0xCC900804
	BE_O26A0_REG_LED_AD_MON_SYNC_IN_2_T                         ad_mon_sync_in_2;	//0xCC900808
	BE_O26A0_REG_LED_AD_MON_SYNC_IN_3_T                         ad_mon_sync_in_3;	//0xCC90080C
	UINT32                                                  reserved222;	//0xCC900810
	UINT32                                                  reserved223;	//0xCC900814
	UINT32                                                  reserved224;	//0xCC900818
	UINT32                                                  reserved225;	//0xCC90081C
	UINT32                                                  reserved226;	//0xCC900820
	UINT32                                                  reserved227;	//0xCC900824
	UINT32                                                  reserved228;	//0xCC900828
	UINT32                                                  reserved229;	//0xCC90082C
	UINT32                                                  reserved230;	//0xCC900830
	UINT32                                                  reserved231;	//0xCC900834
	UINT32                                                  reserved232;	//0xCC900838
	UINT32                                                  reserved233;	//0xCC90083C
	UINT32                                                  reserved234;	//0xCC900840
	UINT32                                                  reserved235;	//0xCC900844
	UINT32                                                  reserved236;	//0xCC900848
	UINT32                                                  reserved237;	//0xCC90084C
	UINT32                                                  reserved238;	//0xCC900850
	UINT32                                                  reserved239;	//0xCC900854
	UINT32                                                  reserved240;	//0xCC900858
	UINT32                                                  reserved241;	//0xCC90085C
	UINT32                                                  reserved242;	//0xCC900860
	UINT32                                                  reserved243;	//0xCC900864
	UINT32                                                  reserved244;	//0xCC900868
	UINT32                                                  reserved245;	//0xCC90086C
	UINT32                                                  reserved246;	//0xCC900870
	UINT32                                                  reserved247;	//0xCC900874
	UINT32                                                  reserved248;	//0xCC900878
	UINT32                                                  reserved249;	//0xCC90087C
	UINT32                                                  reserved250;	//0xCC900880
	UINT32                                                  reserved251;	//0xCC900884
	UINT32                                                  reserved252;	//0xCC900888
	UINT32                                                  reserved253;	//0xCC90088C
	UINT32                                                  reserved254;	//0xCC900890
	UINT32                                                  reserved255;	//0xCC900894
	UINT32                                                  reserved256;	//0xCC900898
	UINT32                                                  reserved257;	//0xCC90089C
	UINT32                                                  reserved258;	//0xCC9008A0
	UINT32                                                  reserved259;	//0xCC9008A4
	UINT32                                                  reserved260;	//0xCC9008A8
	UINT32                                                  reserved261;	//0xCC9008AC
	UINT32                                                  reserved262;	//0xCC9008B0
	UINT32                                                  reserved263;	//0xCC9008B4
	UINT32                                                  reserved264;	//0xCC9008B8
	UINT32                                                  reserved265;	//0xCC9008BC
	UINT32                                                  reserved266;	//0xCC9008C0
	UINT32                                                  reserved267;	//0xCC9008C4
	UINT32                                                  reserved268;	//0xCC9008C8
	UINT32                                                  reserved269;	//0xCC9008CC
	UINT32                                                  reserved270;	//0xCC9008D0
	UINT32                                                  reserved271;	//0xCC9008D4
	UINT32                                                  reserved272;	//0xCC9008D8
	UINT32                                                  reserved273;	//0xCC9008DC
	UINT32                                                  reserved274;	//0xCC9008E0
	UINT32                                                  reserved275;	//0xCC9008E4
	UINT32                                                  reserved276;	//0xCC9008E8
	UINT32                                                  reserved277;	//0xCC9008EC
	UINT32                                                  reserved278;	//0xCC9008F0
	UINT32                                                  reserved279;	//0xCC9008F4
	UINT32                                                  reserved280;	//0xCC9008F8
	UINT32                                                  reserved281;	//0xCC9008FC
	BE_O26A0_REG_LED_AD_BLU_BLK_NUM_DISP_CLK_T           ad_blu_blk_num_disp_clk;	//0xCC900900
	BE_O26A0_REG_LED_AD_REVERSE_T                                     ad_reverse;	//0xCC900904
	UINT32                                                  reserved282;	//0xCC900908
	UINT32                                                  reserved283;	//0xCC90090C
	UINT32                                                  reserved284;	//0xCC900910
	UINT32                                                  reserved285;	//0xCC900914
	UINT32                                                  reserved286;	//0xCC900918
	UINT32                                                  reserved287;	//0xCC90091C
	UINT32                                                  reserved288;	//0xCC900920
	UINT32                                                  reserved289;	//0xCC900924
	UINT32                                                  reserved290;	//0xCC900928
	UINT32                                                  reserved291;	//0xCC90092C
	UINT32                                                  reserved292;	//0xCC900930
	UINT32                                                  reserved293;	//0xCC900934
	UINT32                                                  reserved294;	//0xCC900938
	UINT32                                                  reserved295;	//0xCC90093C
	BE_O26A0_REG_LED_AD_MAX_OPT_AI_ILLUMINANT_T         ad_max_opt_ai_illuminant;	//0xCC900940
	BE_O26A0_REG_LED_AD_BLK_MAX_MODE_AI_ILLUMINANT_T  ad_blk_max_mode_ai_illuminant;	//0xCC900944
	BE_O26A0_REG_LED_AD_MAX_OPT_MODE_AI_ILLUMINANT_T  ad_max_opt_mode_ai_illuminant;	//0xCC900948
	BE_O26A0_REG_LED_AD_MAX_OPT0_1_AI_ILLUMINANT_T    ad_max_opt0_1_ai_illuminant;	//0xCC90094C
	BE_O26A0_REG_LED_AD_LEVEL_TH_AI_ILLUMINANT_T       ad_level_th_ai_illuminant;	//0xCC900950
	BE_O26A0_REG_LED_AD_NUMBER_TH_AI_ILLUMINANT_T     ad_number_th_ai_illuminant;	//0xCC900954
	BE_O26A0_REG_LED_AD_APL_AI_ILLUMINANT_T                 ad_apl_ai_illuminant;	//0xCC900958
	BE_O26A0_REG_LED_AD_BV_GEN_X1_X2_AI_ILLUMINANT_T  ad_bv_gen_x1_x2_ai_illuminant;	//0xCC90095C
	BE_O26A0_REG_LED_AD_BV_GEN_X3_X4_AI_ILLUMINANT_T  ad_bv_gen_x3_x4_ai_illuminant;	//0xCC900960
	BE_O26A0_REG_LED_AD_BV_GEN_Y0_Y1_AI_ILLUMINANT_T  ad_bv_gen_y0_y1_ai_illuminant;	//0xCC900964
	BE_O26A0_REG_LED_AD_BV_GEN_Y2_Y3_AI_ILLUMINANT_T  ad_bv_gen_y2_y3_ai_illuminant;	//0xCC900968
	BE_O26A0_REG_LED_AD_BV_GEN_Y4_Y5_AI_ILLUMINANT_T  ad_bv_gen_y4_y5_ai_illuminant;	//0xCC90096C
	BE_O26A0_REG_LED_AD_BV_GEN_BV_MAX_AI_ILLUMINANT_T ad_bv_gen_bv_max_ai_illuminant;	//0xCC900970
	BE_O26A0_REG_LED_AD_BV_MIN_MAX_AI_ILLUMINANT_T    ad_bv_min_max_ai_illuminant;	//0xCC900974
	BE_O26A0_REG_LED_AD_BV_LUT_MIN_MAX_AI_ILLUMINANT_T ad_bv_lut_min_max_ai_illuminant;	//0xCC900978
	BE_O26A0_REG_LED_AD_BV_FINAL_AVG_MIN_MAX_AI_ILLUMINANT_T ad_bv_final_avg_min_max_ai_illuminant;	//0xCC90097C
	UINT32                                                  reserved296;	//0xCC900980
	UINT32                                                  reserved297;	//0xCC900984
	UINT32                                                  reserved298;	//0xCC900988
	BE_O26A0_REG_LED_AD_BPL_IN_SEL_T                               ad_bpl_in_sel;	//0xCC90098C
	BE_O26A0_REG_LED_AD_AI_ILLUMINANT_MAP_SEL_T         ad_ai_illuminant_map_sel;	//0xCC900990
	BE_O26A0_REG_LED_AD_CC_LD_DIRECT_PATH_SEL_T         ad_cc_ld_direct_path_sel;	//0xCC900994
	BE_O26A0_REG_LED_AD_OSD_LUT0_T                                   ad_osd_lut0;	//0xCC900998
	BE_O26A0_REG_LED_AD_OSD_LUT1_T                                   ad_osd_lut1;	//0xCC90099C
	UINT32                                                  reserved299;	//0xCC9009A0
	UINT32                                                  reserved300;	//0xCC9009A4
	UINT32                                                  reserved301;	//0xCC9009A8
	UINT32                                                  reserved302;	//0xCC9009AC
	UINT32                                                  reserved303;	//0xCC9009B0
	UINT32                                                  reserved304;	//0xCC9009B4
	UINT32                                                  reserved305;	//0xCC9009B8
	UINT32                                                  reserved306;	//0xCC9009BC
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_00_T       ad_aibvgain_merge_ctrl_00;	//0xCC9009C0
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_01_T       ad_aibvgain_merge_ctrl_01;	//0xCC9009C4
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_02_T       ad_aibvgain_merge_ctrl_02;	//0xCC9009C8
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_03_T       ad_aibvgain_merge_ctrl_03;	//0xCC9009CC
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_04_T       ad_aibvgain_merge_ctrl_04;	//0xCC9009D0
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_05_T       ad_aibvgain_merge_ctrl_05;	//0xCC9009D4
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_06_T       ad_aibvgain_merge_ctrl_06;	//0xCC9009D8
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_07_T       ad_aibvgain_merge_ctrl_07;	//0xCC9009DC
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_08_T       ad_aibvgain_merge_ctrl_08;	//0xCC9009E0
	BE_O26A0_REG_LED_AD_AIBVGAIN_MERGE_CTRL_09_T       ad_aibvgain_merge_ctrl_09;	//0xCC9009E4
	UINT32                                                  reserved307;	//0xCC9009E8
	UINT32                                                  reserved308;	//0xCC9009EC
	UINT32                                                  reserved309;	//0xCC9009F0
	UINT32                                                  reserved310;	//0xCC9009F4
	UINT32                                                  reserved311;	//0xCC9009F8
	UINT32                                                  reserved312;	//0xCC9009FC
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_00_T                   ad_comp_lut_ctrl_00;	//0xCC900A00
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_01_T                   ad_comp_lut_ctrl_01;	//0xCC900A04
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_02_T                   ad_comp_lut_ctrl_02;	//0xCC900A08
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_03_T                   ad_comp_lut_ctrl_03;	//0xCC900A0C
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_04_T                   ad_comp_lut_ctrl_04;	//0xCC900A10
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_05_T                   ad_comp_lut_ctrl_05;	//0xCC900A14
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_06_T                   ad_comp_lut_ctrl_06;	//0xCC900A18
	BE_O26A0_REG_LED_AD_COMP_LUT_CTRL_07_T                   ad_comp_lut_ctrl_07;	//0xCC900A1C
	UINT32                                                  reserved313;	//0xCC900A20
	UINT32                                                  reserved314;	//0xCC900A24
	UINT32                                                  reserved315;	//0xCC900A28
	UINT32                                                  reserved316;	//0xCC900A2C
	UINT32                                                  reserved317;	//0xCC900A30
	UINT32                                                  reserved318;	//0xCC900A34
	UINT32                                                  reserved319;	//0xCC900A38
	UINT32                                                  reserved320;	//0xCC900A3C
	UINT32                                                  reserved321;	//0xCC900A40
	UINT32                                                  reserved322;	//0xCC900A44
	UINT32                                                  reserved323;	//0xCC900A48
	UINT32                                                  reserved324;	//0xCC900A4C
	UINT32                                                  reserved325;	//0xCC900A50
	UINT32                                                  reserved326;	//0xCC900A54
	UINT32                                                  reserved327;	//0xCC900A58
	UINT32                                                  reserved328;	//0xCC900A5C
	UINT32                                                  reserved329;	//0xCC900A60
	UINT32                                                  reserved330;	//0xCC900A64
	UINT32                                                  reserved331;	//0xCC900A68
	UINT32                                                  reserved332;	//0xCC900A6C
	UINT32                                                  reserved333;	//0xCC900A70
	UINT32                                                  reserved334;	//0xCC900A74
	UINT32                                                  reserved335;	//0xCC900A78
	UINT32                                                  reserved336;	//0xCC900A7C
	UINT32                                                  reserved337;	//0xCC900A80
	UINT32                                                  reserved338;	//0xCC900A84
	UINT32                                                  reserved339;	//0xCC900A88
	UINT32                                                  reserved340;	//0xCC900A8C
	UINT32                                                  reserved341;	//0xCC900A90
	UINT32                                                  reserved342;	//0xCC900A94
	UINT32                                                  reserved343;	//0xCC900A98
	UINT32                                                  reserved344;	//0xCC900A9C
	UINT32                                                  reserved345;	//0xCC900AA0
	UINT32                                                  reserved346;	//0xCC900AA4
	UINT32                                                  reserved347;	//0xCC900AA8
	UINT32                                                  reserved348;	//0xCC900AAC
	UINT32                                                  reserved349;	//0xCC900AB0
	UINT32                                                  reserved350;	//0xCC900AB4
	UINT32                                                  reserved351;	//0xCC900AB8
	UINT32                                                  reserved352;	//0xCC900ABC
	UINT32                                                  reserved353;	//0xCC900AC0
	UINT32                                                  reserved354;	//0xCC900AC4
	UINT32                                                  reserved355;	//0xCC900AC8
	UINT32                                                  reserved356;	//0xCC900ACC
	UINT32                                                  reserved357;	//0xCC900AD0
	UINT32                                                  reserved358;	//0xCC900AD4
	UINT32                                                  reserved359;	//0xCC900AD8
	UINT32                                                  reserved360;	//0xCC900ADC
	UINT32                                                  reserved361;	//0xCC900AE0
	BE_O26A0_REG_LED_AD_FPS_T                                             ad_fps;	//0xCC900AE4
	UINT32                                                  reserved362;	//0xCC900AE8
	UINT32                                                  reserved363;	//0xCC900AEC
	UINT32                                                  reserved364;	//0xCC900AF0
	UINT32                                                  reserved365;	//0xCC900AF4
	UINT32                                                  reserved366;	//0xCC900AF8
	UINT32                                                  reserved367;	//0xCC900AFC
	UINT32                                                  reserved368;	//0xCC900B00
	UINT32                                                  reserved369;	//0xCC900B04
	UINT32                                                  reserved370;	//0xCC900B08
	UINT32                                                  reserved371;	//0xCC900B0C
	UINT32                                                  reserved372;	//0xCC900B10
	UINT32                                                  reserved373;	//0xCC900B14
	UINT32                                                  reserved374;	//0xCC900B18
	UINT32                                                  reserved375;	//0xCC900B1C
	UINT32                                                  reserved376;	//0xCC900B20
	UINT32                                                  reserved377;	//0xCC900B24
	UINT32                                                  reserved378;	//0xCC900B28
	UINT32                                                  reserved379;	//0xCC900B2C
	UINT32                                                  reserved380;	//0xCC900B30
	UINT32                                                  reserved381;	//0xCC900B34
	UINT32                                                  reserved382;	//0xCC900B38
	UINT32                                                  reserved383;	//0xCC900B3C
	UINT32                                                  reserved384;	//0xCC900B40
	UINT32                                                  reserved385;	//0xCC900B44
	UINT32                                                  reserved386;	//0xCC900B48
	UINT32                                                  reserved387;	//0xCC900B4C
	UINT32                                                  reserved388;	//0xCC900B50
	UINT32                                                  reserved389;	//0xCC900B54
	UINT32                                                  reserved390;	//0xCC900B58
	UINT32                                                  reserved391;	//0xCC900B5C
	UINT32                                                  reserved392;	//0xCC900B60
	UINT32                                                  reserved393;	//0xCC900B64
	UINT32                                                  reserved394;	//0xCC900B68
	UINT32                                                  reserved395;	//0xCC900B6C
	UINT32                                                  reserved396;	//0xCC900B70
	UINT32                                                  reserved397;	//0xCC900B74
	UINT32                                                  reserved398;	//0xCC900B78
	UINT32                                                  reserved399;	//0xCC900B7C
	UINT32                                                  reserved400;	//0xCC900B80
	UINT32                                                  reserved401;	//0xCC900B84
	UINT32                                                  reserved402;	//0xCC900B88
	UINT32                                                  reserved403;	//0xCC900B8C
	UINT32                                                  reserved404;	//0xCC900B90
	UINT32                                                  reserved405;	//0xCC900B94
	UINT32                                                  reserved406;	//0xCC900B98
	UINT32                                                  reserved407;	//0xCC900B9C
	UINT32                                                  reserved408;	//0xCC900BA0
	UINT32                                                  reserved409;	//0xCC900BA4
	UINT32                                                  reserved410;	//0xCC900BA8
	UINT32                                                  reserved411;	//0xCC900BAC
	UINT32                                                  reserved412;	//0xCC900BB0
	UINT32                                                  reserved413;	//0xCC900BB4
	UINT32                                                  reserved414;	//0xCC900BB8
	UINT32                                                  reserved415;	//0xCC900BBC
	UINT32                                                  reserved416;	//0xCC900BC0
	UINT32                                                  reserved417;	//0xCC900BC4
	UINT32                                                  reserved418;	//0xCC900BC8
	UINT32                                                  reserved419;	//0xCC900BCC
	UINT32                                                  reserved420;	//0xCC900BD0
	UINT32                                                  reserved421;	//0xCC900BD4
	UINT32                                                  reserved422;	//0xCC900BD8
	UINT32                                                  reserved423;	//0xCC900BDC
	UINT32                                                  reserved424;	//0xCC900BE0
	UINT32                                                  reserved425;	//0xCC900BE4
	UINT32                                                  reserved426;	//0xCC900BE8
	UINT32                                                  reserved427;	//0xCC900BEC
	UINT32                                                  reserved428;	//0xCC900BF0
	UINT32                                                  reserved429;	//0xCC900BF4
	UINT32                                                  reserved430;	//0xCC900BF8
	UINT32                                                  reserved431;	//0xCC900BFC
	UINT32                                                  reserved432;	//0xCC900C00
	UINT32                                                  reserved433;	//0xCC900C04
	UINT32                                                  reserved434;	//0xCC900C08
	UINT32                                                  reserved435;	//0xCC900C0C
	UINT32                                                  reserved436;	//0xCC900C10
	UINT32                                                  reserved437;	//0xCC900C14
	UINT32                                                  reserved438;	//0xCC900C18
	UINT32                                                  reserved439;	//0xCC900C1C
	UINT32                                                  reserved440;	//0xCC900C20
	UINT32                                                  reserved441;	//0xCC900C24
	UINT32                                                  reserved442;	//0xCC900C28
	UINT32                                                  reserved443;	//0xCC900C2C
	UINT32                                                  reserved444;	//0xCC900C30
	UINT32                                                  reserved445;	//0xCC900C34
	UINT32                                                  reserved446;	//0xCC900C38
	UINT32                                                  reserved447;	//0xCC900C3C
	UINT32                                                  reserved448;	//0xCC900C40
	UINT32                                                  reserved449;	//0xCC900C44
	UINT32                                                  reserved450;	//0xCC900C48
	UINT32                                                  reserved451;	//0xCC900C4C
	UINT32                                                  reserved452;	//0xCC900C50
	UINT32                                                  reserved453;	//0xCC900C54
	UINT32                                                  reserved454;	//0xCC900C58
	UINT32                                                  reserved455;	//0xCC900C5C
	UINT32                                                  reserved456;	//0xCC900C60
	UINT32                                                  reserved457;	//0xCC900C64
	UINT32                                                  reserved458;	//0xCC900C68
	UINT32                                                  reserved459;	//0xCC900C6C
	UINT32                                                  reserved460;	//0xCC900C70
	UINT32                                                  reserved461;	//0xCC900C74
	UINT32                                                  reserved462;	//0xCC900C78
	UINT32                                                  reserved463;	//0xCC900C7C
	UINT32                                                  reserved464;	//0xCC900C80
	UINT32                                                  reserved465;	//0xCC900C84
	UINT32                                                  reserved466;	//0xCC900C88
	UINT32                                                  reserved467;	//0xCC900C8C
	UINT32                                                  reserved468;	//0xCC900C90
	UINT32                                                  reserved469;	//0xCC900C94
	UINT32                                                  reserved470;	//0xCC900C98
	UINT32                                                  reserved471;	//0xCC900C9C
	UINT32                                                  reserved472;	//0xCC900CA0
	UINT32                                                  reserved473;	//0xCC900CA4
	UINT32                                                  reserved474;	//0xCC900CA8
	UINT32                                                  reserved475;	//0xCC900CAC
	UINT32                                                  reserved476;	//0xCC900CB0
	UINT32                                                  reserved477;	//0xCC900CB4
	UINT32                                                  reserved478;	//0xCC900CB8
	UINT32                                                  reserved479;	//0xCC900CBC
	UINT32                                                  reserved480;	//0xCC900CC0
	UINT32                                                  reserved481;	//0xCC900CC4
	UINT32                                                  reserved482;	//0xCC900CC8
	UINT32                                                  reserved483;	//0xCC900CCC
	UINT32                                                  reserved484;	//0xCC900CD0
	UINT32                                                  reserved485;	//0xCC900CD4
	UINT32                                                  reserved486;	//0xCC900CD8
	UINT32                                                  reserved487;	//0xCC900CDC
	UINT32                                                  reserved488;	//0xCC900CE0
	UINT32                                                  reserved489;	//0xCC900CE4
	UINT32                                                  reserved490;	//0xCC900CE8
	UINT32                                                  reserved491;	//0xCC900CEC
	UINT32                                                  reserved492;	//0xCC900CF0
	UINT32                                                  reserved493;	//0xCC900CF4
	UINT32                                                  reserved494;	//0xCC900CF8
	UINT32                                                  reserved495;	//0xCC900CFC
	UINT32                                                  reserved496;	//0xCC900D00
	UINT32                                                  reserved497;	//0xCC900D04
	UINT32                                                  reserved498;	//0xCC900D08
	UINT32                                                  reserved499;	//0xCC900D0C
	UINT32                                                  reserved500;	//0xCC900D10
	UINT32                                                  reserved501;	//0xCC900D14
	UINT32                                                  reserved502;	//0xCC900D18
	UINT32                                                  reserved503;	//0xCC900D1C
	UINT32                                                  reserved504;	//0xCC900D20
	UINT32                                                  reserved505;	//0xCC900D24
	UINT32                                                  reserved506;	//0xCC900D28
	UINT32                                                  reserved507;	//0xCC900D2C
	UINT32                                                  reserved508;	//0xCC900D30
	UINT32                                                  reserved509;	//0xCC900D34
	UINT32                                                  reserved510;	//0xCC900D38
	UINT32                                                  reserved511;	//0xCC900D3C
	UINT32                                                  reserved512;	//0xCC900D40
	UINT32                                                  reserved513;	//0xCC900D44
	UINT32                                                  reserved514;	//0xCC900D48
	UINT32                                                  reserved515;	//0xCC900D4C
	UINT32                                                  reserved516;	//0xCC900D50
	UINT32                                                  reserved517;	//0xCC900D54
	UINT32                                                  reserved518;	//0xCC900D58
	UINT32                                                  reserved519;	//0xCC900D5C
	UINT32                                                  reserved520;	//0xCC900D60
	UINT32                                                  reserved521;	//0xCC900D64
	UINT32                                                  reserved522;	//0xCC900D68
	UINT32                                                  reserved523;	//0xCC900D6C
	UINT32                                                  reserved524;	//0xCC900D70
	UINT32                                                  reserved525;	//0xCC900D74
	UINT32                                                  reserved526;	//0xCC900D78
	UINT32                                                  reserved527;	//0xCC900D7C
	UINT32                                                  reserved528;	//0xCC900D80
	UINT32                                                  reserved529;	//0xCC900D84
	UINT32                                                  reserved530;	//0xCC900D88
	UINT32                                                  reserved531;	//0xCC900D8C
	UINT32                                                  reserved532;	//0xCC900D90
	UINT32                                                  reserved533;	//0xCC900D94
	UINT32                                                  reserved534;	//0xCC900D98
	UINT32                                                  reserved535;	//0xCC900D9C
	UINT32                                                  reserved536;	//0xCC900DA0
	UINT32                                                  reserved537;	//0xCC900DA4
	UINT32                                                  reserved538;	//0xCC900DA8
	UINT32                                                  reserved539;	//0xCC900DAC
	UINT32                                                  reserved540;	//0xCC900DB0
	UINT32                                                  reserved541;	//0xCC900DB4
	UINT32                                                  reserved542;	//0xCC900DB8
	UINT32                                                  reserved543;	//0xCC900DBC
	UINT32                                                  reserved544;	//0xCC900DC0
	UINT32                                                  reserved545;	//0xCC900DC4
	UINT32                                                  reserved546;	//0xCC900DC8
	UINT32                                                  reserved547;	//0xCC900DCC
	UINT32                                                  reserved548;	//0xCC900DD0
	UINT32                                                  reserved549;	//0xCC900DD4
	UINT32                                                  reserved550;	//0xCC900DD8
	UINT32                                                  reserved551;	//0xCC900DDC
	UINT32                                                  reserved552;	//0xCC900DE0
	UINT32                                                  reserved553;	//0xCC900DE4
	UINT32                                                  reserved554;	//0xCC900DE8
	UINT32                                                  reserved555;	//0xCC900DEC
	UINT32                                                  reserved556;	//0xCC900DF0
	UINT32                                                  reserved557;	//0xCC900DF4
	UINT32                                                  reserved558;	//0xCC900DF8
	UINT32                                                  reserved559;	//0xCC900DFC
	UINT32                                                  reserved560;	//0xCC900E00
	UINT32                                                  reserved561;	//0xCC900E04
	UINT32                                                  reserved562;	//0xCC900E08
	UINT32                                                  reserved563;	//0xCC900E0C
	UINT32                                                  reserved564;	//0xCC900E10
	UINT32                                                  reserved565;	//0xCC900E14
	UINT32                                                  reserved566;	//0xCC900E18
	UINT32                                                  reserved567;	//0xCC900E1C
	UINT32                                                  reserved568;	//0xCC900E20
	UINT32                                                  reserved569;	//0xCC900E24
	UINT32                                                  reserved570;	//0xCC900E28
	UINT32                                                  reserved571;	//0xCC900E2C
	UINT32                                                  reserved572;	//0xCC900E30
	UINT32                                                  reserved573;	//0xCC900E34
	UINT32                                                  reserved574;	//0xCC900E38
	UINT32                                                  reserved575;	//0xCC900E3C
	UINT32                                                  reserved576;	//0xCC900E40
	UINT32                                                  reserved577;	//0xCC900E44
	UINT32                                                  reserved578;	//0xCC900E48
	UINT32                                                  reserved579;	//0xCC900E4C
	UINT32                                                  reserved580;	//0xCC900E50
	UINT32                                                  reserved581;	//0xCC900E54
	UINT32                                                  reserved582;	//0xCC900E58
	UINT32                                                  reserved583;	//0xCC900E5C
	UINT32                                                  reserved584;	//0xCC900E60
	UINT32                                                  reserved585;	//0xCC900E64
	UINT32                                                  reserved586;	//0xCC900E68
	UINT32                                                  reserved587;	//0xCC900E6C
	UINT32                                                  reserved588;	//0xCC900E70
	UINT32                                                  reserved589;	//0xCC900E74
	UINT32                                                  reserved590;	//0xCC900E78
	UINT32                                                  reserved591;	//0xCC900E7C
	UINT32                                                  reserved592;	//0xCC900E80
	UINT32                                                  reserved593;	//0xCC900E84
	UINT32                                                  reserved594;	//0xCC900E88
	UINT32                                                  reserved595;	//0xCC900E8C
	UINT32                                                  reserved596;	//0xCC900E90
	UINT32                                                  reserved597;	//0xCC900E94
	UINT32                                                  reserved598;	//0xCC900E98
	UINT32                                                  reserved599;	//0xCC900E9C
	UINT32                                                  reserved600;	//0xCC900EA0
	UINT32                                                  reserved601;	//0xCC900EA4
	UINT32                                                  reserved602;	//0xCC900EA8
	UINT32                                                  reserved603;	//0xCC900EAC
	UINT32                                                  reserved604;	//0xCC900EB0
	UINT32                                                  reserved605;	//0xCC900EB4
	UINT32                                                  reserved606;	//0xCC900EB8
	UINT32                                                  reserved607;	//0xCC900EBC
	UINT32                                                  reserved608;	//0xCC900EC0
	UINT32                                                  reserved609;	//0xCC900EC4
	UINT32                                                  reserved610;	//0xCC900EC8
	UINT32                                                  reserved611;	//0xCC900ECC
	UINT32                                                  reserved612;	//0xCC900ED0
	UINT32                                                  reserved613;	//0xCC900ED4
	UINT32                                                  reserved614;	//0xCC900ED8
	UINT32                                                  reserved615;	//0xCC900EDC
	UINT32                                                  reserved616;	//0xCC900EE0
	UINT32                                                  reserved617;	//0xCC900EE4
	UINT32                                                  reserved618;	//0xCC900EE8
	UINT32                                                  reserved619;	//0xCC900EEC
	UINT32                                                  reserved620;	//0xCC900EF0
	UINT32                                                  reserved621;	//0xCC900EF4
	UINT32                                                  reserved622;	//0xCC900EF8
	UINT32                                                  reserved623;	//0xCC900EFC
	UINT32                                                  reserved624;	//0xCC900F00
	UINT32                                                  reserved625;	//0xCC900F04
	UINT32                                                  reserved626;	//0xCC900F08
	UINT32                                                  reserved627;	//0xCC900F0C
	UINT32                                                  reserved628;	//0xCC900F10
	UINT32                                                  reserved629;	//0xCC900F14
	UINT32                                                  reserved630;	//0xCC900F18
	UINT32                                                  reserved631;	//0xCC900F1C
	UINT32                                                  reserved632;	//0xCC900F20
	UINT32                                                  reserved633;	//0xCC900F24
	UINT32                                                  reserved634;	//0xCC900F28
	UINT32                                                  reserved635;	//0xCC900F2C
	UINT32                                                  reserved636;	//0xCC900F30
	UINT32                                                  reserved637;	//0xCC900F34
	UINT32                                                  reserved638;	//0xCC900F38
	UINT32                                                  reserved639;	//0xCC900F3C
	UINT32                                                  reserved640;	//0xCC900F40
	UINT32                                                  reserved641;	//0xCC900F44
	UINT32                                                  reserved642;	//0xCC900F48
	UINT32                                                  reserved643;	//0xCC900F4C
	UINT32                                                  reserved644;	//0xCC900F50
	UINT32                                                  reserved645;	//0xCC900F54
	UINT32                                                  reserved646;	//0xCC900F58
	UINT32                                                  reserved647;	//0xCC900F5C
	UINT32                                                  reserved648;	//0xCC900F60
	UINT32                                                  reserved649;	//0xCC900F64
	UINT32                                                  reserved650;	//0xCC900F68
	UINT32                                                  reserved651;	//0xCC900F6C
	UINT32                                                  reserved652;	//0xCC900F70
	UINT32                                                  reserved653;	//0xCC900F74
	UINT32                                                  reserved654;	//0xCC900F78
	UINT32                                                  reserved655;	//0xCC900F7C
	UINT32                                                  reserved656;	//0xCC900F80
	UINT32                                                  reserved657;	//0xCC900F84
	UINT32                                                  reserved658;	//0xCC900F88
	UINT32                                                  reserved659;	//0xCC900F8C
	UINT32                                                  reserved660;	//0xCC900F90
	UINT32                                                  reserved661;	//0xCC900F94
	UINT32                                                  reserved662;	//0xCC900F98
	UINT32                                                  reserved663;	//0xCC900F9C
	UINT32                                                  reserved664;	//0xCC900FA0
	UINT32                                                  reserved665;	//0xCC900FA4
	UINT32                                                  reserved666;	//0xCC900FA8
	UINT32                                                  reserved667;	//0xCC900FAC
	UINT32                                                  reserved668;	//0xCC900FB0
	UINT32                                                  reserved669;	//0xCC900FB4
	UINT32                                                  reserved670;	//0xCC900FB8
	UINT32                                                  reserved671;	//0xCC900FBC
	UINT32                                                  reserved672;	//0xCC900FC0
	UINT32                                                  reserved673;	//0xCC900FC4
	UINT32                                                  reserved674;	//0xCC900FC8
	UINT32                                                  reserved675;	//0xCC900FCC
	UINT32                                                  reserved676;	//0xCC900FD0
	UINT32                                                  reserved677;	//0xCC900FD4
	UINT32                                                  reserved678;	//0xCC900FD8
	UINT32                                                  reserved679;	//0xCC900FDC
	UINT32                                                  reserved680;	//0xCC900FE0
	UINT32                                                  reserved681;	//0xCC900FE4
	UINT32                                                  reserved682;	//0xCC900FE8
	UINT32                                                  reserved683;	//0xCC900FEC
	UINT32                                                  reserved684;	//0xCC900FF0
	UINT32                                                  reserved685;	//0xCC900FF4
	UINT32                                                  reserved686;	//0xCC900FF8
	UINT32                                                  reserved687;	//0xCC900FFC
	UINT32                                                  reserved688;	//0xCC901000
	UINT32                                                  reserved689;	//0xCC901004
	UINT32                                                  reserved690;	//0xCC901008
	UINT32                                                  reserved691;	//0xCC90100C
	UINT32                                                  reserved692;	//0xCC901010
	UINT32                                                  reserved693;	//0xCC901014
	UINT32                                                  reserved694;	//0xCC901018
	UINT32                                                  reserved695;	//0xCC90101C
	UINT32                                                  reserved696;	//0xCC901020
	UINT32                                                  reserved697;	//0xCC901024
	UINT32                                                  reserved698;	//0xCC901028
	UINT32                                                  reserved699;	//0xCC90102C
	UINT32                                                  reserved700;	//0xCC901030
	UINT32                                                  reserved701;	//0xCC901034
	UINT32                                                  reserved702;	//0xCC901038
	UINT32                                                  reserved703;	//0xCC90103C
	UINT32                                                  reserved704;	//0xCC901040
	UINT32                                                  reserved705;	//0xCC901044
	UINT32                                                  reserved706;	//0xCC901048
	UINT32                                                  reserved707;	//0xCC90104C
	UINT32                                                  reserved708;	//0xCC901050
	UINT32                                                  reserved709;	//0xCC901054
	UINT32                                                  reserved710;	//0xCC901058
	UINT32                                                  reserved711;	//0xCC90105C
	UINT32                                                  reserved712;	//0xCC901060
	UINT32                                                  reserved713;	//0xCC901064
	UINT32                                                  reserved714;	//0xCC901068
	UINT32                                                  reserved715;	//0xCC90106C
	UINT32                                                  reserved716;	//0xCC901070
	UINT32                                                  reserved717;	//0xCC901074
	UINT32                                                  reserved718;	//0xCC901078
	UINT32                                                  reserved719;	//0xCC90107C
	UINT32                                                  reserved720;	//0xCC901080
	UINT32                                                  reserved721;	//0xCC901084
	UINT32                                                  reserved722;	//0xCC901088
	UINT32                                                  reserved723;	//0xCC90108C
	UINT32                                                  reserved724;	//0xCC901090
	UINT32                                                  reserved725;	//0xCC901094
	UINT32                                                  reserved726;	//0xCC901098
	UINT32                                                  reserved727;	//0xCC90109C
	UINT32                                                  reserved728;	//0xCC9010A0
	UINT32                                                  reserved729;	//0xCC9010A4
	UINT32                                                  reserved730;	//0xCC9010A8
	UINT32                                                  reserved731;	//0xCC9010AC
	UINT32                                                  reserved732;	//0xCC9010B0
	UINT32                                                  reserved733;	//0xCC9010B4
	UINT32                                                  reserved734;	//0xCC9010B8
	UINT32                                                  reserved735;	//0xCC9010BC
	UINT32                                                  reserved736;	//0xCC9010C0
	UINT32                                                  reserved737;	//0xCC9010C4
	UINT32                                                  reserved738;	//0xCC9010C8
	UINT32                                                  reserved739;	//0xCC9010CC
	UINT32                                                  reserved740;	//0xCC9010D0
	UINT32                                                  reserved741;	//0xCC9010D4
	UINT32                                                  reserved742;	//0xCC9010D8
	UINT32                                                  reserved743;	//0xCC9010DC
	UINT32                                                  reserved744;	//0xCC9010E0
	UINT32                                                  reserved745;	//0xCC9010E4
	UINT32                                                  reserved746;	//0xCC9010E8
	UINT32                                                  reserved747;	//0xCC9010EC
	UINT32                                                  reserved748;	//0xCC9010F0
	UINT32                                                  reserved749;	//0xCC9010F4
	UINT32                                                  reserved750;	//0xCC9010F8
	UINT32                                                  reserved751;	//0xCC9010FC
	UINT32                                                  reserved752;	//0xCC901100
	UINT32                                                  reserved753;	//0xCC901104
	UINT32                                                  reserved754;	//0xCC901108
	UINT32                                                  reserved755;	//0xCC90110C
	UINT32                                                  reserved756;	//0xCC901110
	UINT32                                                  reserved757;	//0xCC901114
	UINT32                                                  reserved758;	//0xCC901118
	UINT32                                                  reserved759;	//0xCC90111C
	UINT32                                                  reserved760;	//0xCC901120
	UINT32                                                  reserved761;	//0xCC901124
	UINT32                                                  reserved762;	//0xCC901128
	UINT32                                                  reserved763;	//0xCC90112C
	UINT32                                                  reserved764;	//0xCC901130
	UINT32                                                  reserved765;	//0xCC901134
	UINT32                                                  reserved766;	//0xCC901138
	UINT32                                                  reserved767;	//0xCC90113C
	UINT32                                                  reserved768;	//0xCC901140
	UINT32                                                  reserved769;	//0xCC901144
	UINT32                                                  reserved770;	//0xCC901148
	UINT32                                                  reserved771;	//0xCC90114C
	UINT32                                                  reserved772;	//0xCC901150
	UINT32                                                  reserved773;	//0xCC901154
	UINT32                                                  reserved774;	//0xCC901158
	UINT32                                                  reserved775;	//0xCC90115C
	UINT32                                                  reserved776;	//0xCC901160
	UINT32                                                  reserved777;	//0xCC901164
	UINT32                                                  reserved778;	//0xCC901168
	UINT32                                                  reserved779;	//0xCC90116C
	UINT32                                                  reserved780;	//0xCC901170
	UINT32                                                  reserved781;	//0xCC901174
	UINT32                                                  reserved782;	//0xCC901178
	UINT32                                                  reserved783;	//0xCC90117C
	UINT32                                                  reserved784;	//0xCC901180
	UINT32                                                  reserved785;	//0xCC901184
	UINT32                                                  reserved786;	//0xCC901188
	UINT32                                                  reserved787;	//0xCC90118C
	UINT32                                                  reserved788;	//0xCC901190
	UINT32                                                  reserved789;	//0xCC901194
	UINT32                                                  reserved790;	//0xCC901198
	UINT32                                                  reserved791;	//0xCC90119C
	UINT32                                                  reserved792;	//0xCC9011A0
	UINT32                                                  reserved793;	//0xCC9011A4
	UINT32                                                  reserved794;	//0xCC9011A8
	UINT32                                                  reserved795;	//0xCC9011AC
	UINT32                                                  reserved796;	//0xCC9011B0
	UINT32                                                  reserved797;	//0xCC9011B4
	UINT32                                                  reserved798;	//0xCC9011B8
	UINT32                                                  reserved799;	//0xCC9011BC
	UINT32                                                  reserved800;	//0xCC9011C0
	UINT32                                                  reserved801;	//0xCC9011C4
	UINT32                                                  reserved802;	//0xCC9011C8
	UINT32                                                  reserved803;	//0xCC9011CC
	UINT32                                                  reserved804;	//0xCC9011D0
	UINT32                                                  reserved805;	//0xCC9011D4
	UINT32                                                  reserved806;	//0xCC9011D8
	UINT32                                                  reserved807;	//0xCC9011DC
	UINT32                                                  reserved808;	//0xCC9011E0
	UINT32                                                  reserved809;	//0xCC9011E4
	UINT32                                                  reserved810;	//0xCC9011E8
	UINT32                                                  reserved811;	//0xCC9011EC
	UINT32                                                  reserved812;	//0xCC9011F0
	UINT32                                                  reserved813;	//0xCC9011F4
	UINT32                                                  reserved814;	//0xCC9011F8
	UINT32                                                  reserved815;	//0xCC9011FC
	UINT32                                                  reserved816;	//0xCC901200
	UINT32                                                  reserved817;	//0xCC901204
	UINT32                                                  reserved818;	//0xCC901208
	UINT32                                                  reserved819;	//0xCC90120C
	UINT32                                                  reserved820;	//0xCC901210
	UINT32                                                  reserved821;	//0xCC901214
	UINT32                                                  reserved822;	//0xCC901218
	UINT32                                                  reserved823;	//0xCC90121C
	UINT32                                                  reserved824;	//0xCC901220
	UINT32                                                  reserved825;	//0xCC901224
	UINT32                                                  reserved826;	//0xCC901228
	UINT32                                                  reserved827;	//0xCC90122C
	UINT32                                                  reserved828;	//0xCC901230
	UINT32                                                  reserved829;	//0xCC901234
	UINT32                                                  reserved830;	//0xCC901238
	UINT32                                                  reserved831;	//0xCC90123C
	UINT32                                                  reserved832;	//0xCC901240
	UINT32                                                  reserved833;	//0xCC901244
	UINT32                                                  reserved834;	//0xCC901248
	UINT32                                                  reserved835;	//0xCC90124C
	UINT32                                                  reserved836;	//0xCC901250
	UINT32                                                  reserved837;	//0xCC901254
	UINT32                                                  reserved838;	//0xCC901258
	UINT32                                                  reserved839;	//0xCC90125C
	UINT32                                                  reserved840;	//0xCC901260
	UINT32                                                  reserved841;	//0xCC901264
	UINT32                                                  reserved842;	//0xCC901268
	UINT32                                                  reserved843;	//0xCC90126C
	UINT32                                                  reserved844;	//0xCC901270
	UINT32                                                  reserved845;	//0xCC901274
	UINT32                                                  reserved846;	//0xCC901278
	UINT32                                                  reserved847;	//0xCC90127C
	UINT32                                                  reserved848;	//0xCC901280
	UINT32                                                  reserved849;	//0xCC901284
	UINT32                                                  reserved850;	//0xCC901288
	UINT32                                                  reserved851;	//0xCC90128C
	UINT32                                                  reserved852;	//0xCC901290
	UINT32                                                  reserved853;	//0xCC901294
	UINT32                                                  reserved854;	//0xCC901298
	UINT32                                                  reserved855;	//0xCC90129C
	UINT32                                                  reserved856;	//0xCC9012A0
	UINT32                                                  reserved857;	//0xCC9012A4
	UINT32                                                  reserved858;	//0xCC9012A8
	UINT32                                                  reserved859;	//0xCC9012AC
	UINT32                                                  reserved860;	//0xCC9012B0
	UINT32                                                  reserved861;	//0xCC9012B4
	UINT32                                                  reserved862;	//0xCC9012B8
	UINT32                                                  reserved863;	//0xCC9012BC
	UINT32                                                  reserved864;	//0xCC9012C0
	UINT32                                                  reserved865;	//0xCC9012C4
	UINT32                                                  reserved866;	//0xCC9012C8
	UINT32                                                  reserved867;	//0xCC9012CC
	UINT32                                                  reserved868;	//0xCC9012D0
	UINT32                                                  reserved869;	//0xCC9012D4
	UINT32                                                  reserved870;	//0xCC9012D8
	UINT32                                                  reserved871;	//0xCC9012DC
	UINT32                                                  reserved872;	//0xCC9012E0
	UINT32                                                  reserved873;	//0xCC9012E4
	UINT32                                                  reserved874;	//0xCC9012E8
	UINT32                                                  reserved875;	//0xCC9012EC
	UINT32                                                  reserved876;	//0xCC9012F0
	UINT32                                                  reserved877;	//0xCC9012F4
	UINT32                                                  reserved878;	//0xCC9012F8
	UINT32                                                  reserved879;	//0xCC9012FC
	UINT32                                                  reserved880;	//0xCC901300
	UINT32                                                  reserved881;	//0xCC901304
	UINT32                                                  reserved882;	//0xCC901308
	UINT32                                                  reserved883;	//0xCC90130C
	UINT32                                                  reserved884;	//0xCC901310
	UINT32                                                  reserved885;	//0xCC901314
	UINT32                                                  reserved886;	//0xCC901318
	UINT32                                                  reserved887;	//0xCC90131C
	UINT32                                                  reserved888;	//0xCC901320
	UINT32                                                  reserved889;	//0xCC901324
	UINT32                                                  reserved890;	//0xCC901328
	UINT32                                                  reserved891;	//0xCC90132C
	UINT32                                                  reserved892;	//0xCC901330
	UINT32                                                  reserved893;	//0xCC901334
	UINT32                                                  reserved894;	//0xCC901338
	UINT32                                                  reserved895;	//0xCC90133C
	UINT32                                                  reserved896;	//0xCC901340
	UINT32                                                  reserved897;	//0xCC901344
	UINT32                                                  reserved898;	//0xCC901348
	UINT32                                                  reserved899;	//0xCC90134C
	UINT32                                                  reserved900;	//0xCC901350
	UINT32                                                  reserved901;	//0xCC901354
	UINT32                                                  reserved902;	//0xCC901358
	UINT32                                                  reserved903;	//0xCC90135C
	UINT32                                                  reserved904;	//0xCC901360
	UINT32                                                  reserved905;	//0xCC901364
	UINT32                                                  reserved906;	//0xCC901368
	UINT32                                                  reserved907;	//0xCC90136C
	UINT32                                                  reserved908;	//0xCC901370
	UINT32                                                  reserved909;	//0xCC901374
	UINT32                                                  reserved910;	//0xCC901378
	UINT32                                                  reserved911;	//0xCC90137C
	UINT32                                                  reserved912;	//0xCC901380
	UINT32                                                  reserved913;	//0xCC901384
	UINT32                                                  reserved914;	//0xCC901388
	UINT32                                                  reserved915;	//0xCC90138C
	UINT32                                                  reserved916;	//0xCC901390
	UINT32                                                  reserved917;	//0xCC901394
	UINT32                                                  reserved918;	//0xCC901398
	UINT32                                                  reserved919;	//0xCC90139C
	UINT32                                                  reserved920;	//0xCC9013A0
	UINT32                                                  reserved921;	//0xCC9013A4
	UINT32                                                  reserved922;	//0xCC9013A8
	UINT32                                                  reserved923;	//0xCC9013AC
	UINT32                                                  reserved924;	//0xCC9013B0
	UINT32                                                  reserved925;	//0xCC9013B4
	UINT32                                                  reserved926;	//0xCC9013B8
	UINT32                                                  reserved927;	//0xCC9013BC
	UINT32                                                  reserved928;	//0xCC9013C0
	UINT32                                                  reserved929;	//0xCC9013C4
	UINT32                                                  reserved930;	//0xCC9013C8
	UINT32                                                  reserved931;	//0xCC9013CC
	UINT32                                                  reserved932;	//0xCC9013D0
	UINT32                                                  reserved933;	//0xCC9013D4
	UINT32                                                  reserved934;	//0xCC9013D8
	UINT32                                                  reserved935;	//0xCC9013DC
	UINT32                                                  reserved936;	//0xCC9013E0
	UINT32                                                  reserved937;	//0xCC9013E4
	UINT32                                                  reserved938;	//0xCC9013E8
	UINT32                                                  reserved939;	//0xCC9013EC
	UINT32                                                  reserved940;	//0xCC9013F0
	UINT32                                                  reserved941;	//0xCC9013F4
	UINT32                                                  reserved942;	//0xCC9013F8
	UINT32                                                  reserved943;	//0xCC9013FC
	UINT32                                                  reserved944;	//0xCC901400
	UINT32                                                  reserved945;	//0xCC901404
	UINT32                                                  reserved946;	//0xCC901408
	UINT32                                                  reserved947;	//0xCC90140C
	UINT32                                                  reserved948;	//0xCC901410
	UINT32                                                  reserved949;	//0xCC901414
	UINT32                                                  reserved950;	//0xCC901418
	UINT32                                                  reserved951;	//0xCC90141C
	UINT32                                                  reserved952;	//0xCC901420
	UINT32                                                  reserved953;	//0xCC901424
	UINT32                                                  reserved954;	//0xCC901428
	UINT32                                                  reserved955;	//0xCC90142C
	UINT32                                                  reserved956;	//0xCC901430
	UINT32                                                  reserved957;	//0xCC901434
	UINT32                                                  reserved958;	//0xCC901438
	UINT32                                                  reserved959;	//0xCC90143C
	UINT32                                                  reserved960;	//0xCC901440
	UINT32                                                  reserved961;	//0xCC901444
	UINT32                                                  reserved962;	//0xCC901448
	UINT32                                                  reserved963;	//0xCC90144C
	UINT32                                                  reserved964;	//0xCC901450
	UINT32                                                  reserved965;	//0xCC901454
	UINT32                                                  reserved966;	//0xCC901458
	UINT32                                                  reserved967;	//0xCC90145C
	UINT32                                                  reserved968;	//0xCC901460
	UINT32                                                  reserved969;	//0xCC901464
	UINT32                                                  reserved970;	//0xCC901468
	UINT32                                                  reserved971;	//0xCC90146C
	UINT32                                                  reserved972;	//0xCC901470
	UINT32                                                  reserved973;	//0xCC901474
	UINT32                                                  reserved974;	//0xCC901478
	UINT32                                                  reserved975;	//0xCC90147C
	UINT32                                                  reserved976;	//0xCC901480
	UINT32                                                  reserved977;	//0xCC901484
	UINT32                                                  reserved978;	//0xCC901488
	UINT32                                                  reserved979;	//0xCC90148C
	UINT32                                                  reserved980;	//0xCC901490
	UINT32                                                  reserved981;	//0xCC901494
	UINT32                                                  reserved982;	//0xCC901498
	UINT32                                                  reserved983;	//0xCC90149C
	UINT32                                                  reserved984;	//0xCC9014A0
	UINT32                                                  reserved985;	//0xCC9014A4
	UINT32                                                  reserved986;	//0xCC9014A8
	UINT32                                                  reserved987;	//0xCC9014AC
	UINT32                                                  reserved988;	//0xCC9014B0
	UINT32                                                  reserved989;	//0xCC9014B4
	UINT32                                                  reserved990;	//0xCC9014B8
	UINT32                                                  reserved991;	//0xCC9014BC
	UINT32                                                  reserved992;	//0xCC9014C0
	UINT32                                                  reserved993;	//0xCC9014C4
	UINT32                                                  reserved994;	//0xCC9014C8
	UINT32                                                  reserved995;	//0xCC9014CC
	UINT32                                                  reserved996;	//0xCC9014D0
	UINT32                                                  reserved997;	//0xCC9014D4
	UINT32                                                  reserved998;	//0xCC9014D8
	UINT32                                                  reserved999;	//0xCC9014DC
	UINT32                                                 reserved1000;	//0xCC9014E0
	UINT32                                                 reserved1001;	//0xCC9014E4
	UINT32                                                 reserved1002;	//0xCC9014E8
	UINT32                                                 reserved1003;	//0xCC9014EC
	UINT32                                                 reserved1004;	//0xCC9014F0
	UINT32                                                 reserved1005;	//0xCC9014F4
	UINT32                                                 reserved1006;	//0xCC9014F8
	UINT32                                                 reserved1007;	//0xCC9014FC
	UINT32                                                 reserved1008;	//0xCC901500
	UINT32                                                 reserved1009;	//0xCC901504
	UINT32                                                 reserved1010;	//0xCC901508
	UINT32                                                 reserved1011;	//0xCC90150C
	UINT32                                                 reserved1012;	//0xCC901510
	UINT32                                                 reserved1013;	//0xCC901514
	UINT32                                                 reserved1014;	//0xCC901518
	UINT32                                                 reserved1015;	//0xCC90151C
	UINT32                                                 reserved1016;	//0xCC901520
	UINT32                                                 reserved1017;	//0xCC901524
	UINT32                                                 reserved1018;	//0xCC901528
	UINT32                                                 reserved1019;	//0xCC90152C
	UINT32                                                 reserved1020;	//0xCC901530
	UINT32                                                 reserved1021;	//0xCC901534
	UINT32                                                 reserved1022;	//0xCC901538
	UINT32                                                 reserved1023;	//0xCC90153C
	UINT32                                                 reserved1024;	//0xCC901540
	UINT32                                                 reserved1025;	//0xCC901544
	UINT32                                                 reserved1026;	//0xCC901548
	UINT32                                                 reserved1027;	//0xCC90154C
	UINT32                                                 reserved1028;	//0xCC901550
	UINT32                                                 reserved1029;	//0xCC901554
	UINT32                                                 reserved1030;	//0xCC901558
	UINT32                                                 reserved1031;	//0xCC90155C
	UINT32                                                 reserved1032;	//0xCC901560
	UINT32                                                 reserved1033;	//0xCC901564
	UINT32                                                 reserved1034;	//0xCC901568
	UINT32                                                 reserved1035;	//0xCC90156C
	UINT32                                                 reserved1036;	//0xCC901570
	UINT32                                                 reserved1037;	//0xCC901574
	UINT32                                                 reserved1038;	//0xCC901578
	UINT32                                                 reserved1039;	//0xCC90157C
	UINT32                                                 reserved1040;	//0xCC901580
	UINT32                                                 reserved1041;	//0xCC901584
	UINT32                                                 reserved1042;	//0xCC901588
	UINT32                                                 reserved1043;	//0xCC90158C
	UINT32                                                 reserved1044;	//0xCC901590
	UINT32                                                 reserved1045;	//0xCC901594
	UINT32                                                 reserved1046;	//0xCC901598
	UINT32                                                 reserved1047;	//0xCC90159C
	UINT32                                                 reserved1048;	//0xCC9015A0
	UINT32                                                 reserved1049;	//0xCC9015A4
	UINT32                                                 reserved1050;	//0xCC9015A8
	UINT32                                                 reserved1051;	//0xCC9015AC
	UINT32                                                 reserved1052;	//0xCC9015B0
	UINT32                                                 reserved1053;	//0xCC9015B4
	UINT32                                                 reserved1054;	//0xCC9015B8
	UINT32                                                 reserved1055;	//0xCC9015BC
	UINT32                                                 reserved1056;	//0xCC9015C0
	UINT32                                                 reserved1057;	//0xCC9015C4
	UINT32                                                 reserved1058;	//0xCC9015C8
	UINT32                                                 reserved1059;	//0xCC9015CC
	UINT32                                                 reserved1060;	//0xCC9015D0
	UINT32                                                 reserved1061;	//0xCC9015D4
	UINT32                                                 reserved1062;	//0xCC9015D8
	UINT32                                                 reserved1063;	//0xCC9015DC
	UINT32                                                 reserved1064;	//0xCC9015E0
	UINT32                                                 reserved1065;	//0xCC9015E4
	UINT32                                                 reserved1066;	//0xCC9015E8
	UINT32                                                 reserved1067;	//0xCC9015EC
	UINT32                                                 reserved1068;	//0xCC9015F0
	UINT32                                                 reserved1069;	//0xCC9015F4
	UINT32                                                 reserved1070;	//0xCC9015F8
	UINT32                                                 reserved1071;	//0xCC9015FC
	UINT32                                                 reserved1072;	//0xCC901600
	UINT32                                                 reserved1073;	//0xCC901604
	UINT32                                                 reserved1074;	//0xCC901608
	UINT32                                                 reserved1075;	//0xCC90160C
	UINT32                                                 reserved1076;	//0xCC901610
	UINT32                                                 reserved1077;	//0xCC901614
	UINT32                                                 reserved1078;	//0xCC901618
	UINT32                                                 reserved1079;	//0xCC90161C
	UINT32                                                 reserved1080;	//0xCC901620
	UINT32                                                 reserved1081;	//0xCC901624
	UINT32                                                 reserved1082;	//0xCC901628
	UINT32                                                 reserved1083;	//0xCC90162C
	UINT32                                                 reserved1084;	//0xCC901630
	UINT32                                                 reserved1085;	//0xCC901634
	UINT32                                                 reserved1086;	//0xCC901638
	UINT32                                                 reserved1087;	//0xCC90163C
	UINT32                                                 reserved1088;	//0xCC901640
	UINT32                                                 reserved1089;	//0xCC901644
	UINT32                                                 reserved1090;	//0xCC901648
	UINT32                                                 reserved1091;	//0xCC90164C
	UINT32                                                 reserved1092;	//0xCC901650
	UINT32                                                 reserved1093;	//0xCC901654
	UINT32                                                 reserved1094;	//0xCC901658
	UINT32                                                 reserved1095;	//0xCC90165C
	UINT32                                                 reserved1096;	//0xCC901660
	UINT32                                                 reserved1097;	//0xCC901664
	UINT32                                                 reserved1098;	//0xCC901668
	UINT32                                                 reserved1099;	//0xCC90166C
	UINT32                                                 reserved1100;	//0xCC901670
	UINT32                                                 reserved1101;	//0xCC901674
	UINT32                                                 reserved1102;	//0xCC901678
	UINT32                                                 reserved1103;	//0xCC90167C
	UINT32                                                 reserved1104;	//0xCC901680
	UINT32                                                 reserved1105;	//0xCC901684
	UINT32                                                 reserved1106;	//0xCC901688
	UINT32                                                 reserved1107;	//0xCC90168C
	UINT32                                                 reserved1108;	//0xCC901690
	UINT32                                                 reserved1109;	//0xCC901694
	UINT32                                                 reserved1110;	//0xCC901698
	UINT32                                                 reserved1111;	//0xCC90169C
	UINT32                                                 reserved1112;	//0xCC9016A0
	UINT32                                                 reserved1113;	//0xCC9016A4
	UINT32                                                 reserved1114;	//0xCC9016A8
	UINT32                                                 reserved1115;	//0xCC9016AC
	UINT32                                                 reserved1116;	//0xCC9016B0
	UINT32                                                 reserved1117;	//0xCC9016B4
	UINT32                                                 reserved1118;	//0xCC9016B8
	UINT32                                                 reserved1119;	//0xCC9016BC
	UINT32                                                 reserved1120;	//0xCC9016C0
	UINT32                                                 reserved1121;	//0xCC9016C4
	UINT32                                                 reserved1122;	//0xCC9016C8
	UINT32                                                 reserved1123;	//0xCC9016CC
	UINT32                                                 reserved1124;	//0xCC9016D0
	UINT32                                                 reserved1125;	//0xCC9016D4
	UINT32                                                 reserved1126;	//0xCC9016D8
	UINT32                                                 reserved1127;	//0xCC9016DC
	UINT32                                                 reserved1128;	//0xCC9016E0
	UINT32                                                 reserved1129;	//0xCC9016E4
	UINT32                                                 reserved1130;	//0xCC9016E8
	UINT32                                                 reserved1131;	//0xCC9016EC
	UINT32                                                 reserved1132;	//0xCC9016F0
	UINT32                                                 reserved1133;	//0xCC9016F4
	UINT32                                                 reserved1134;	//0xCC9016F8
	UINT32                                                 reserved1135;	//0xCC9016FC
	UINT32                                                 reserved1136;	//0xCC901700
	UINT32                                                 reserved1137;	//0xCC901704
	UINT32                                                 reserved1138;	//0xCC901708
	UINT32                                                 reserved1139;	//0xCC90170C
	UINT32                                                 reserved1140;	//0xCC901710
	UINT32                                                 reserved1141;	//0xCC901714
	UINT32                                                 reserved1142;	//0xCC901718
	UINT32                                                 reserved1143;	//0xCC90171C
	UINT32                                                 reserved1144;	//0xCC901720
	UINT32                                                 reserved1145;	//0xCC901724
	UINT32                                                 reserved1146;	//0xCC901728
	UINT32                                                 reserved1147;	//0xCC90172C
	UINT32                                                 reserved1148;	//0xCC901730
	UINT32                                                 reserved1149;	//0xCC901734
	UINT32                                                 reserved1150;	//0xCC901738
	UINT32                                                 reserved1151;	//0xCC90173C
	UINT32                                                 reserved1152;	//0xCC901740
	UINT32                                                 reserved1153;	//0xCC901744
	UINT32                                                 reserved1154;	//0xCC901748
	UINT32                                                 reserved1155;	//0xCC90174C
	UINT32                                                 reserved1156;	//0xCC901750
	UINT32                                                 reserved1157;	//0xCC901754
	UINT32                                                 reserved1158;	//0xCC901758
	UINT32                                                 reserved1159;	//0xCC90175C
	UINT32                                                 reserved1160;	//0xCC901760
	UINT32                                                 reserved1161;	//0xCC901764
	UINT32                                                 reserved1162;	//0xCC901768
	UINT32                                                 reserved1163;	//0xCC90176C
	UINT32                                                 reserved1164;	//0xCC901770
	UINT32                                                 reserved1165;	//0xCC901774
	UINT32                                                 reserved1166;	//0xCC901778
	UINT32                                                 reserved1167;	//0xCC90177C
	UINT32                                                 reserved1168;	//0xCC901780
	UINT32                                                 reserved1169;	//0xCC901784
	UINT32                                                 reserved1170;	//0xCC901788
	UINT32                                                 reserved1171;	//0xCC90178C
	UINT32                                                 reserved1172;	//0xCC901790
	UINT32                                                 reserved1173;	//0xCC901794
	UINT32                                                 reserved1174;	//0xCC901798
	UINT32                                                 reserved1175;	//0xCC90179C
	UINT32                                                 reserved1176;	//0xCC9017A0
	UINT32                                                 reserved1177;	//0xCC9017A4
	UINT32                                                 reserved1178;	//0xCC9017A8
	UINT32                                                 reserved1179;	//0xCC9017AC
	UINT32                                                 reserved1180;	//0xCC9017B0
	UINT32                                                 reserved1181;	//0xCC9017B4
	UINT32                                                 reserved1182;	//0xCC9017B8
	UINT32                                                 reserved1183;	//0xCC9017BC
	UINT32                                                 reserved1184;	//0xCC9017C0
	UINT32                                                 reserved1185;	//0xCC9017C4
	UINT32                                                 reserved1186;	//0xCC9017C8
	UINT32                                                 reserved1187;	//0xCC9017CC
	UINT32                                                 reserved1188;	//0xCC9017D0
	UINT32                                                 reserved1189;	//0xCC9017D4
	UINT32                                                 reserved1190;	//0xCC9017D8
	UINT32                                                 reserved1191;	//0xCC9017DC
	UINT32                                                 reserved1192;	//0xCC9017E0
	UINT32                                                 reserved1193;	//0xCC9017E4
	UINT32                                                 reserved1194;	//0xCC9017E8
	UINT32                                                 reserved1195;	//0xCC9017EC
	UINT32                                                 reserved1196;	//0xCC9017F0
	UINT32                                                 reserved1197;	//0xCC9017F4
	UINT32                                                 reserved1198;	//0xCC9017F8
	UINT32                                                 reserved1199;	//0xCC9017FC
	UINT32                                                 reserved1200;	//0xCC901800
	UINT32                                                 reserved1201;	//0xCC901804
	UINT32                                                 reserved1202;	//0xCC901808
	UINT32                                                 reserved1203;	//0xCC90180C
	UINT32                                                 reserved1204;	//0xCC901810
	UINT32                                                 reserved1205;	//0xCC901814
	UINT32                                                 reserved1206;	//0xCC901818
	UINT32                                                 reserved1207;	//0xCC90181C
	UINT32                                                 reserved1208;	//0xCC901820
	UINT32                                                 reserved1209;	//0xCC901824
	UINT32                                                 reserved1210;	//0xCC901828
	UINT32                                                 reserved1211;	//0xCC90182C
	UINT32                                                 reserved1212;	//0xCC901830
	UINT32                                                 reserved1213;	//0xCC901834
	UINT32                                                 reserved1214;	//0xCC901838
	UINT32                                                 reserved1215;	//0xCC90183C
	UINT32                                                 reserved1216;	//0xCC901840
	UINT32                                                 reserved1217;	//0xCC901844
	UINT32                                                 reserved1218;	//0xCC901848
	UINT32                                                 reserved1219;	//0xCC90184C
	UINT32                                                 reserved1220;	//0xCC901850
	UINT32                                                 reserved1221;	//0xCC901854
	UINT32                                                 reserved1222;	//0xCC901858
	UINT32                                                 reserved1223;	//0xCC90185C
	UINT32                                                 reserved1224;	//0xCC901860
	UINT32                                                 reserved1225;	//0xCC901864
	UINT32                                                 reserved1226;	//0xCC901868
	UINT32                                                 reserved1227;	//0xCC90186C
	UINT32                                                 reserved1228;	//0xCC901870
	UINT32                                                 reserved1229;	//0xCC901874
	UINT32                                                 reserved1230;	//0xCC901878
	UINT32                                                 reserved1231;	//0xCC90187C
	UINT32                                                 reserved1232;	//0xCC901880
	UINT32                                                 reserved1233;	//0xCC901884
	UINT32                                                 reserved1234;	//0xCC901888
	UINT32                                                 reserved1235;	//0xCC90188C
	UINT32                                                 reserved1236;	//0xCC901890
	UINT32                                                 reserved1237;	//0xCC901894
	UINT32                                                 reserved1238;	//0xCC901898
	UINT32                                                 reserved1239;	//0xCC90189C
	UINT32                                                 reserved1240;	//0xCC9018A0
	UINT32                                                 reserved1241;	//0xCC9018A4
	UINT32                                                 reserved1242;	//0xCC9018A8
	UINT32                                                 reserved1243;	//0xCC9018AC
	UINT32                                                 reserved1244;	//0xCC9018B0
	UINT32                                                 reserved1245;	//0xCC9018B4
	UINT32                                                 reserved1246;	//0xCC9018B8
	UINT32                                                 reserved1247;	//0xCC9018BC
	UINT32                                                 reserved1248;	//0xCC9018C0
	UINT32                                                 reserved1249;	//0xCC9018C4
	UINT32                                                 reserved1250;	//0xCC9018C8
	UINT32                                                 reserved1251;	//0xCC9018CC
	UINT32                                                 reserved1252;	//0xCC9018D0
	UINT32                                                 reserved1253;	//0xCC9018D4
	UINT32                                                 reserved1254;	//0xCC9018D8
	UINT32                                                 reserved1255;	//0xCC9018DC
	UINT32                                                 reserved1256;	//0xCC9018E0
	UINT32                                                 reserved1257;	//0xCC9018E4
	UINT32                                                 reserved1258;	//0xCC9018E8
	UINT32                                                 reserved1259;	//0xCC9018EC
	UINT32                                                 reserved1260;	//0xCC9018F0
	UINT32                                                 reserved1261;	//0xCC9018F4
	UINT32                                                 reserved1262;	//0xCC9018F8
	UINT32                                                 reserved1263;	//0xCC9018FC
	UINT32                                                 reserved1264;	//0xCC901900
	UINT32                                                 reserved1265;	//0xCC901904
	UINT32                                                 reserved1266;	//0xCC901908
	UINT32                                                 reserved1267;	//0xCC90190C
	UINT32                                                 reserved1268;	//0xCC901910
	UINT32                                                 reserved1269;	//0xCC901914
	UINT32                                                 reserved1270;	//0xCC901918
	UINT32                                                 reserved1271;	//0xCC90191C
	UINT32                                                 reserved1272;	//0xCC901920
	UINT32                                                 reserved1273;	//0xCC901924
	UINT32                                                 reserved1274;	//0xCC901928
	UINT32                                                 reserved1275;	//0xCC90192C
	UINT32                                                 reserved1276;	//0xCC901930
	UINT32                                                 reserved1277;	//0xCC901934
	UINT32                                                 reserved1278;	//0xCC901938
	UINT32                                                 reserved1279;	//0xCC90193C
	UINT32                                                 reserved1280;	//0xCC901940
	UINT32                                                 reserved1281;	//0xCC901944
	UINT32                                                 reserved1282;	//0xCC901948
	UINT32                                                 reserved1283;	//0xCC90194C
	UINT32                                                 reserved1284;	//0xCC901950
	UINT32                                                 reserved1285;	//0xCC901954
	UINT32                                                 reserved1286;	//0xCC901958
	UINT32                                                 reserved1287;	//0xCC90195C
	UINT32                                                 reserved1288;	//0xCC901960
	UINT32                                                 reserved1289;	//0xCC901964
	UINT32                                                 reserved1290;	//0xCC901968
	UINT32                                                 reserved1291;	//0xCC90196C
	UINT32                                                 reserved1292;	//0xCC901970
	UINT32                                                 reserved1293;	//0xCC901974
	UINT32                                                 reserved1294;	//0xCC901978
	UINT32                                                 reserved1295;	//0xCC90197C
	UINT32                                                 reserved1296;	//0xCC901980
	UINT32                                                 reserved1297;	//0xCC901984
	UINT32                                                 reserved1298;	//0xCC901988
	UINT32                                                 reserved1299;	//0xCC90198C
	UINT32                                                 reserved1300;	//0xCC901990
	UINT32                                                 reserved1301;	//0xCC901994
	UINT32                                                 reserved1302;	//0xCC901998
	UINT32                                                 reserved1303;	//0xCC90199C
	UINT32                                                 reserved1304;	//0xCC9019A0
	UINT32                                                 reserved1305;	//0xCC9019A4
	UINT32                                                 reserved1306;	//0xCC9019A8
	UINT32                                                 reserved1307;	//0xCC9019AC
	UINT32                                                 reserved1308;	//0xCC9019B0
	UINT32                                                 reserved1309;	//0xCC9019B4
	UINT32                                                 reserved1310;	//0xCC9019B8
	UINT32                                                 reserved1311;	//0xCC9019BC
	UINT32                                                 reserved1312;	//0xCC9019C0
	UINT32                                                 reserved1313;	//0xCC9019C4
	UINT32                                                 reserved1314;	//0xCC9019C8
	UINT32                                                 reserved1315;	//0xCC9019CC
	UINT32                                                 reserved1316;	//0xCC9019D0
	UINT32                                                 reserved1317;	//0xCC9019D4
	UINT32                                                 reserved1318;	//0xCC9019D8
	UINT32                                                 reserved1319;	//0xCC9019DC
	UINT32                                                 reserved1320;	//0xCC9019E0
	UINT32                                                 reserved1321;	//0xCC9019E4
	UINT32                                                 reserved1322;	//0xCC9019E8
	UINT32                                                 reserved1323;	//0xCC9019EC
	UINT32                                                 reserved1324;	//0xCC9019F0
	UINT32                                                 reserved1325;	//0xCC9019F4
	UINT32                                                 reserved1326;	//0xCC9019F8
	UINT32                                                 reserved1327;	//0xCC9019FC
	UINT32                                                 reserved1328;	//0xCC901A00
	UINT32                                                 reserved1329;	//0xCC901A04
	UINT32                                                 reserved1330;	//0xCC901A08
	UINT32                                                 reserved1331;	//0xCC901A0C
	UINT32                                                 reserved1332;	//0xCC901A10
	UINT32                                                 reserved1333;	//0xCC901A14
	UINT32                                                 reserved1334;	//0xCC901A18
	UINT32                                                 reserved1335;	//0xCC901A1C
	UINT32                                                 reserved1336;	//0xCC901A20
	UINT32                                                 reserved1337;	//0xCC901A24
	UINT32                                                 reserved1338;	//0xCC901A28
	UINT32                                                 reserved1339;	//0xCC901A2C
	UINT32                                                 reserved1340;	//0xCC901A30
	UINT32                                                 reserved1341;	//0xCC901A34
	UINT32                                                 reserved1342;	//0xCC901A38
	UINT32                                                 reserved1343;	//0xCC901A3C
	UINT32                                                 reserved1344;	//0xCC901A40
	UINT32                                                 reserved1345;	//0xCC901A44
	UINT32                                                 reserved1346;	//0xCC901A48
	UINT32                                                 reserved1347;	//0xCC901A4C
	UINT32                                                 reserved1348;	//0xCC901A50
	UINT32                                                 reserved1349;	//0xCC901A54
	UINT32                                                 reserved1350;	//0xCC901A58
	UINT32                                                 reserved1351;	//0xCC901A5C
	UINT32                                                 reserved1352;	//0xCC901A60
	UINT32                                                 reserved1353;	//0xCC901A64
	UINT32                                                 reserved1354;	//0xCC901A68
	UINT32                                                 reserved1355;	//0xCC901A6C
	UINT32                                                 reserved1356;	//0xCC901A70
	UINT32                                                 reserved1357;	//0xCC901A74
	UINT32                                                 reserved1358;	//0xCC901A78
	UINT32                                                 reserved1359;	//0xCC901A7C
	UINT32                                                 reserved1360;	//0xCC901A80
	UINT32                                                 reserved1361;	//0xCC901A84
	UINT32                                                 reserved1362;	//0xCC901A88
	UINT32                                                 reserved1363;	//0xCC901A8C
	UINT32                                                 reserved1364;	//0xCC901A90
	UINT32                                                 reserved1365;	//0xCC901A94
	UINT32                                                 reserved1366;	//0xCC901A98
	UINT32                                                 reserved1367;	//0xCC901A9C
	UINT32                                                 reserved1368;	//0xCC901AA0
	UINT32                                                 reserved1369;	//0xCC901AA4
	UINT32                                                 reserved1370;	//0xCC901AA8
	UINT32                                                 reserved1371;	//0xCC901AAC
	UINT32                                                 reserved1372;	//0xCC901AB0
	UINT32                                                 reserved1373;	//0xCC901AB4
	UINT32                                                 reserved1374;	//0xCC901AB8
	UINT32                                                 reserved1375;	//0xCC901ABC
	UINT32                                                 reserved1376;	//0xCC901AC0
	UINT32                                                 reserved1377;	//0xCC901AC4
	UINT32                                                 reserved1378;	//0xCC901AC8
	UINT32                                                 reserved1379;	//0xCC901ACC
	UINT32                                                 reserved1380;	//0xCC901AD0
	UINT32                                                 reserved1381;	//0xCC901AD4
	UINT32                                                 reserved1382;	//0xCC901AD8
	UINT32                                                 reserved1383;	//0xCC901ADC
	UINT32                                                 reserved1384;	//0xCC901AE0
	UINT32                                                 reserved1385;	//0xCC901AE4
	UINT32                                                 reserved1386;	//0xCC901AE8
	UINT32                                                 reserved1387;	//0xCC901AEC
	UINT32                                                 reserved1388;	//0xCC901AF0
	UINT32                                                 reserved1389;	//0xCC901AF4
	UINT32                                                 reserved1390;	//0xCC901AF8
	UINT32                                                 reserved1391;	//0xCC901AFC
	UINT32                                                 reserved1392;	//0xCC901B00
	UINT32                                                 reserved1393;	//0xCC901B04
	UINT32                                                 reserved1394;	//0xCC901B08
	UINT32                                                 reserved1395;	//0xCC901B0C
	UINT32                                                 reserved1396;	//0xCC901B10
	UINT32                                                 reserved1397;	//0xCC901B14
	UINT32                                                 reserved1398;	//0xCC901B18
	UINT32                                                 reserved1399;	//0xCC901B1C
	UINT32                                                 reserved1400;	//0xCC901B20
	UINT32                                                 reserved1401;	//0xCC901B24
	UINT32                                                 reserved1402;	//0xCC901B28
	UINT32                                                 reserved1403;	//0xCC901B2C
	UINT32                                                 reserved1404;	//0xCC901B30
	UINT32                                                 reserved1405;	//0xCC901B34
	UINT32                                                 reserved1406;	//0xCC901B38
	UINT32                                                 reserved1407;	//0xCC901B3C
	UINT32                                                 reserved1408;	//0xCC901B40
	UINT32                                                 reserved1409;	//0xCC901B44
	UINT32                                                 reserved1410;	//0xCC901B48
	UINT32                                                 reserved1411;	//0xCC901B4C
	UINT32                                                 reserved1412;	//0xCC901B50
	UINT32                                                 reserved1413;	//0xCC901B54
	UINT32                                                 reserved1414;	//0xCC901B58
	UINT32                                                 reserved1415;	//0xCC901B5C
	UINT32                                                 reserved1416;	//0xCC901B60
	UINT32                                                 reserved1417;	//0xCC901B64
	UINT32                                                 reserved1418;	//0xCC901B68
	UINT32                                                 reserved1419;	//0xCC901B6C
	UINT32                                                 reserved1420;	//0xCC901B70
	UINT32                                                 reserved1421;	//0xCC901B74
	UINT32                                                 reserved1422;	//0xCC901B78
	UINT32                                                 reserved1423;	//0xCC901B7C
	UINT32                                                 reserved1424;	//0xCC901B80
	UINT32                                                 reserved1425;	//0xCC901B84
	UINT32                                                 reserved1426;	//0xCC901B88
	UINT32                                                 reserved1427;	//0xCC901B8C
	UINT32                                                 reserved1428;	//0xCC901B90
	UINT32                                                 reserved1429;	//0xCC901B94
	UINT32                                                 reserved1430;	//0xCC901B98
	UINT32                                                 reserved1431;	//0xCC901B9C
	UINT32                                                 reserved1432;	//0xCC901BA0
	UINT32                                                 reserved1433;	//0xCC901BA4
	UINT32                                                 reserved1434;	//0xCC901BA8
	UINT32                                                 reserved1435;	//0xCC901BAC
	UINT32                                                 reserved1436;	//0xCC901BB0
	UINT32                                                 reserved1437;	//0xCC901BB4
	UINT32                                                 reserved1438;	//0xCC901BB8
	UINT32                                                 reserved1439;	//0xCC901BBC
	UINT32                                                 reserved1440;	//0xCC901BC0
	UINT32                                                 reserved1441;	//0xCC901BC4
	UINT32                                                 reserved1442;	//0xCC901BC8
	UINT32                                                 reserved1443;	//0xCC901BCC
	UINT32                                                 reserved1444;	//0xCC901BD0
	UINT32                                                 reserved1445;	//0xCC901BD4
	UINT32                                                 reserved1446;	//0xCC901BD8
	UINT32                                                 reserved1447;	//0xCC901BDC
	UINT32                                                 reserved1448;	//0xCC901BE0
	UINT32                                                 reserved1449;	//0xCC901BE4
	UINT32                                                 reserved1450;	//0xCC901BE8
	UINT32                                                 reserved1451;	//0xCC901BEC
	UINT32                                                 reserved1452;	//0xCC901BF0
	UINT32                                                 reserved1453;	//0xCC901BF4
	UINT32                                                 reserved1454;	//0xCC901BF8
	UINT32                                                 reserved1455;	//0xCC901BFC
	UINT32                                                 reserved1456;	//0xCC901C00
	UINT32                                                 reserved1457;	//0xCC901C04
	UINT32                                                 reserved1458;	//0xCC901C08
	UINT32                                                 reserved1459;	//0xCC901C0C
	UINT32                                                 reserved1460;	//0xCC901C10
	UINT32                                                 reserved1461;	//0xCC901C14
	UINT32                                                 reserved1462;	//0xCC901C18
	UINT32                                                 reserved1463;	//0xCC901C1C
	UINT32                                                 reserved1464;	//0xCC901C20
	UINT32                                                 reserved1465;	//0xCC901C24
	UINT32                                                 reserved1466;	//0xCC901C28
	UINT32                                                 reserved1467;	//0xCC901C2C
	UINT32                                                 reserved1468;	//0xCC901C30
	UINT32                                                 reserved1469;	//0xCC901C34
	UINT32                                                 reserved1470;	//0xCC901C38
	UINT32                                                 reserved1471;	//0xCC901C3C
	UINT32                                                 reserved1472;	//0xCC901C40
	UINT32                                                 reserved1473;	//0xCC901C44
	UINT32                                                 reserved1474;	//0xCC901C48
	UINT32                                                 reserved1475;	//0xCC901C4C
	UINT32                                                 reserved1476;	//0xCC901C50
	UINT32                                                 reserved1477;	//0xCC901C54
	UINT32                                                 reserved1478;	//0xCC901C58
	UINT32                                                 reserved1479;	//0xCC901C5C
	UINT32                                                 reserved1480;	//0xCC901C60
	UINT32                                                 reserved1481;	//0xCC901C64
	UINT32                                                 reserved1482;	//0xCC901C68
	UINT32                                                 reserved1483;	//0xCC901C6C
	UINT32                                                 reserved1484;	//0xCC901C70
	UINT32                                                 reserved1485;	//0xCC901C74
	UINT32                                                 reserved1486;	//0xCC901C78
	UINT32                                                 reserved1487;	//0xCC901C7C
	UINT32                                                 reserved1488;	//0xCC901C80
	UINT32                                                 reserved1489;	//0xCC901C84
	UINT32                                                 reserved1490;	//0xCC901C88
	UINT32                                                 reserved1491;	//0xCC901C8C
	UINT32                                                 reserved1492;	//0xCC901C90
	UINT32                                                 reserved1493;	//0xCC901C94
	UINT32                                                 reserved1494;	//0xCC901C98
	UINT32                                                 reserved1495;	//0xCC901C9C
	UINT32                                                 reserved1496;	//0xCC901CA0
	UINT32                                                 reserved1497;	//0xCC901CA4
	UINT32                                                 reserved1498;	//0xCC901CA8
	UINT32                                                 reserved1499;	//0xCC901CAC
	UINT32                                                 reserved1500;	//0xCC901CB0
	UINT32                                                 reserved1501;	//0xCC901CB4
	UINT32                                                 reserved1502;	//0xCC901CB8
	UINT32                                                 reserved1503;	//0xCC901CBC
	UINT32                                                 reserved1504;	//0xCC901CC0
	UINT32                                                 reserved1505;	//0xCC901CC4
	UINT32                                                 reserved1506;	//0xCC901CC8
	UINT32                                                 reserved1507;	//0xCC901CCC
	UINT32                                                 reserved1508;	//0xCC901CD0
	UINT32                                                 reserved1509;	//0xCC901CD4
	UINT32                                                 reserved1510;	//0xCC901CD8
	UINT32                                                 reserved1511;	//0xCC901CDC
	UINT32                                                 reserved1512;	//0xCC901CE0
	UINT32                                                 reserved1513;	//0xCC901CE4
	UINT32                                                 reserved1514;	//0xCC901CE8
	UINT32                                                 reserved1515;	//0xCC901CEC
	UINT32                                                 reserved1516;	//0xCC901CF0
	UINT32                                                 reserved1517;	//0xCC901CF4
	UINT32                                                 reserved1518;	//0xCC901CF8
	UINT32                                                 reserved1519;	//0xCC901CFC
	UINT32                                                 reserved1520;	//0xCC901D00
	UINT32                                                 reserved1521;	//0xCC901D04
	UINT32                                                 reserved1522;	//0xCC901D08
	UINT32                                                 reserved1523;	//0xCC901D0C
	UINT32                                                 reserved1524;	//0xCC901D10
	UINT32                                                 reserved1525;	//0xCC901D14
	UINT32                                                 reserved1526;	//0xCC901D18
	UINT32                                                 reserved1527;	//0xCC901D1C
	UINT32                                                 reserved1528;	//0xCC901D20
	UINT32                                                 reserved1529;	//0xCC901D24
	UINT32                                                 reserved1530;	//0xCC901D28
	UINT32                                                 reserved1531;	//0xCC901D2C
	UINT32                                                 reserved1532;	//0xCC901D30
	UINT32                                                 reserved1533;	//0xCC901D34
	UINT32                                                 reserved1534;	//0xCC901D38
	UINT32                                                 reserved1535;	//0xCC901D3C
	UINT32                                                 reserved1536;	//0xCC901D40
	UINT32                                                 reserved1537;	//0xCC901D44
	UINT32                                                 reserved1538;	//0xCC901D48
	UINT32                                                 reserved1539;	//0xCC901D4C
	UINT32                                                 reserved1540;	//0xCC901D50
	UINT32                                                 reserved1541;	//0xCC901D54
	UINT32                                                 reserved1542;	//0xCC901D58
	UINT32                                                 reserved1543;	//0xCC901D5C
	UINT32                                                 reserved1544;	//0xCC901D60
	UINT32                                                 reserved1545;	//0xCC901D64
	UINT32                                                 reserved1546;	//0xCC901D68
	UINT32                                                 reserved1547;	//0xCC901D6C
	UINT32                                                 reserved1548;	//0xCC901D70
	UINT32                                                 reserved1549;	//0xCC901D74
	UINT32                                                 reserved1550;	//0xCC901D78
	UINT32                                                 reserved1551;	//0xCC901D7C
	UINT32                                                 reserved1552;	//0xCC901D80
	UINT32                                                 reserved1553;	//0xCC901D84
	UINT32                                                 reserved1554;	//0xCC901D88
	UINT32                                                 reserved1555;	//0xCC901D8C
	UINT32                                                 reserved1556;	//0xCC901D90
	UINT32                                                 reserved1557;	//0xCC901D94
	UINT32                                                 reserved1558;	//0xCC901D98
	UINT32                                                 reserved1559;	//0xCC901D9C
	UINT32                                                 reserved1560;	//0xCC901DA0
	UINT32                                                 reserved1561;	//0xCC901DA4
	UINT32                                                 reserved1562;	//0xCC901DA8
	UINT32                                                 reserved1563;	//0xCC901DAC
	UINT32                                                 reserved1564;	//0xCC901DB0
	UINT32                                                 reserved1565;	//0xCC901DB4
	UINT32                                                 reserved1566;	//0xCC901DB8
	UINT32                                                 reserved1567;	//0xCC901DBC
	UINT32                                                 reserved1568;	//0xCC901DC0
	UINT32                                                 reserved1569;	//0xCC901DC4
	UINT32                                                 reserved1570;	//0xCC901DC8
	UINT32                                                 reserved1571;	//0xCC901DCC
	UINT32                                                 reserved1572;	//0xCC901DD0
	UINT32                                                 reserved1573;	//0xCC901DD4
	UINT32                                                 reserved1574;	//0xCC901DD8
	UINT32                                                 reserved1575;	//0xCC901DDC
	UINT32                                                 reserved1576;	//0xCC901DE0
	UINT32                                                 reserved1577;	//0xCC901DE4
	UINT32                                                 reserved1578;	//0xCC901DE8
	UINT32                                                 reserved1579;	//0xCC901DEC
	UINT32                                                 reserved1580;	//0xCC901DF0
	UINT32                                                 reserved1581;	//0xCC901DF4
	UINT32                                                 reserved1582;	//0xCC901DF8
	UINT32                                                 reserved1583;	//0xCC901DFC
	UINT32                                                 reserved1584;	//0xCC901E00
	UINT32                                                 reserved1585;	//0xCC901E04
	UINT32                                                 reserved1586;	//0xCC901E08
	UINT32                                                 reserved1587;	//0xCC901E0C
	UINT32                                                 reserved1588;	//0xCC901E10
	UINT32                                                 reserved1589;	//0xCC901E14
	UINT32                                                 reserved1590;	//0xCC901E18
	UINT32                                                 reserved1591;	//0xCC901E1C
	UINT32                                                 reserved1592;	//0xCC901E20
	UINT32                                                 reserved1593;	//0xCC901E24
	UINT32                                                 reserved1594;	//0xCC901E28
	UINT32                                                 reserved1595;	//0xCC901E2C
	UINT32                                                 reserved1596;	//0xCC901E30
	UINT32                                                 reserved1597;	//0xCC901E34
	UINT32                                                 reserved1598;	//0xCC901E38
	UINT32                                                 reserved1599;	//0xCC901E3C
	UINT32                                                 reserved1600;	//0xCC901E40
	UINT32                                                 reserved1601;	//0xCC901E44
	UINT32                                                 reserved1602;	//0xCC901E48
	UINT32                                                 reserved1603;	//0xCC901E4C
	UINT32                                                 reserved1604;	//0xCC901E50
	UINT32                                                 reserved1605;	//0xCC901E54
	UINT32                                                 reserved1606;	//0xCC901E58
	UINT32                                                 reserved1607;	//0xCC901E5C
	UINT32                                                 reserved1608;	//0xCC901E60
	UINT32                                                 reserved1609;	//0xCC901E64
	UINT32                                                 reserved1610;	//0xCC901E68
	UINT32                                                 reserved1611;	//0xCC901E6C
	UINT32                                                 reserved1612;	//0xCC901E70
	UINT32                                                 reserved1613;	//0xCC901E74
	UINT32                                                 reserved1614;	//0xCC901E78
	UINT32                                                 reserved1615;	//0xCC901E7C
	UINT32                                                 reserved1616;	//0xCC901E80
	UINT32                                                 reserved1617;	//0xCC901E84
	UINT32                                                 reserved1618;	//0xCC901E88
	UINT32                                                 reserved1619;	//0xCC901E8C
	UINT32                                                 reserved1620;	//0xCC901E90
	UINT32                                                 reserved1621;	//0xCC901E94
	UINT32                                                 reserved1622;	//0xCC901E98
	UINT32                                                 reserved1623;	//0xCC901E9C
	UINT32                                                 reserved1624;	//0xCC901EA0
	UINT32                                                 reserved1625;	//0xCC901EA4
	UINT32                                                 reserved1626;	//0xCC901EA8
	UINT32                                                 reserved1627;	//0xCC901EAC
	UINT32                                                 reserved1628;	//0xCC901EB0
	UINT32                                                 reserved1629;	//0xCC901EB4
	UINT32                                                 reserved1630;	//0xCC901EB8
	UINT32                                                 reserved1631;	//0xCC901EBC
	UINT32                                                 reserved1632;	//0xCC901EC0
	UINT32                                                 reserved1633;	//0xCC901EC4
	UINT32                                                 reserved1634;	//0xCC901EC8
	UINT32                                                 reserved1635;	//0xCC901ECC
	UINT32                                                 reserved1636;	//0xCC901ED0
	UINT32                                                 reserved1637;	//0xCC901ED4
	UINT32                                                 reserved1638;	//0xCC901ED8
	UINT32                                                 reserved1639;	//0xCC901EDC
	UINT32                                                 reserved1640;	//0xCC901EE0
	UINT32                                                 reserved1641;	//0xCC901EE4
	UINT32                                                 reserved1642;	//0xCC901EE8
	UINT32                                                 reserved1643;	//0xCC901EEC
	UINT32                                                 reserved1644;	//0xCC901EF0
	UINT32                                                 reserved1645;	//0xCC901EF4
	UINT32                                                 reserved1646;	//0xCC901EF8
	UINT32                                                 reserved1647;	//0xCC901EFC
	UINT32                                                 reserved1648;	//0xCC901F00
	UINT32                                                 reserved1649;	//0xCC901F04
	UINT32                                                 reserved1650;	//0xCC901F08
	UINT32                                                 reserved1651;	//0xCC901F0C
	UINT32                                                 reserved1652;	//0xCC901F10
	UINT32                                                 reserved1653;	//0xCC901F14
	UINT32                                                 reserved1654;	//0xCC901F18
	UINT32                                                 reserved1655;	//0xCC901F1C
	UINT32                                                 reserved1656;	//0xCC901F20
	UINT32                                                 reserved1657;	//0xCC901F24
	UINT32                                                 reserved1658;	//0xCC901F28
	UINT32                                                 reserved1659;	//0xCC901F2C
	UINT32                                                 reserved1660;	//0xCC901F30
	UINT32                                                 reserved1661;	//0xCC901F34
	UINT32                                                 reserved1662;	//0xCC901F38
	UINT32                                                 reserved1663;	//0xCC901F3C
	UINT32                                                 reserved1664;	//0xCC901F40
	UINT32                                                 reserved1665;	//0xCC901F44
	UINT32                                                 reserved1666;	//0xCC901F48
	UINT32                                                 reserved1667;	//0xCC901F4C
	UINT32                                                 reserved1668;	//0xCC901F50
	UINT32                                                 reserved1669;	//0xCC901F54
	UINT32                                                 reserved1670;	//0xCC901F58
	UINT32                                                 reserved1671;	//0xCC901F5C
	UINT32                                                 reserved1672;	//0xCC901F60
	UINT32                                                 reserved1673;	//0xCC901F64
	UINT32                                                 reserved1674;	//0xCC901F68
	UINT32                                                 reserved1675;	//0xCC901F6C
	UINT32                                                 reserved1676;	//0xCC901F70
	UINT32                                                 reserved1677;	//0xCC901F74
	UINT32                                                 reserved1678;	//0xCC901F78
	UINT32                                                 reserved1679;	//0xCC901F7C
	UINT32                                                 reserved1680;	//0xCC901F80
	UINT32                                                 reserved1681;	//0xCC901F84
	UINT32                                                 reserved1682;	//0xCC901F88
	UINT32                                                 reserved1683;	//0xCC901F8C
	UINT32                                                 reserved1684;	//0xCC901F90
	UINT32                                                 reserved1685;	//0xCC901F94
	UINT32                                                 reserved1686;	//0xCC901F98
	UINT32                                                 reserved1687;	//0xCC901F9C
	UINT32                                                 reserved1688;	//0xCC901FA0
	UINT32                                                 reserved1689;	//0xCC901FA4
	UINT32                                                 reserved1690;	//0xCC901FA8
	UINT32                                                 reserved1691;	//0xCC901FAC
	UINT32                                                 reserved1692;	//0xCC901FB0
	UINT32                                                 reserved1693;	//0xCC901FB4
	UINT32                                                 reserved1694;	//0xCC901FB8
	UINT32                                                 reserved1695;	//0xCC901FBC
	UINT32                                                 reserved1696;	//0xCC901FC0
	UINT32                                                 reserved1697;	//0xCC901FC4
	UINT32                                                 reserved1698;	//0xCC901FC8
	UINT32                                                 reserved1699;	//0xCC901FCC
	UINT32                                                 reserved1700;	//0xCC901FD0
	UINT32                                                 reserved1701;	//0xCC901FD4
	UINT32                                                 reserved1702;	//0xCC901FD8
	UINT32                                                 reserved1703;	//0xCC901FDC
	UINT32                                                 reserved1704;	//0xCC901FE0
	UINT32                                                 reserved1705;	//0xCC901FE4
	UINT32                                                 reserved1706;	//0xCC901FE8
	UINT32                                                 reserved1707;	//0xCC901FEC
	UINT32                                                 reserved1708;	//0xCC901FF0
	UINT32                                                 reserved1709;	//0xCC901FF4
	UINT32                                                 reserved1710;	//0xCC901FF8
	UINT32                                                 reserved1711;	//0xCC901FFC
	BE_O26A0_REG_LED_AD_BLU_BLK_NUM_HV_T                       ad_blu_blk_num_hv;	//0xCC902000
	BE_O26A0_REG_LED_AD_VS_MODE_T                                     ad_vs_mode;	//0xCC902004
	BE_O26A0_REG_LED_AD_BLU_VS_NUM_T                               ad_blu_vs_num;	//0xCC902008
	BE_O26A0_REG_LED_AD_BLU_VS_T0_T                                 ad_blu_vs_t0;	//0xCC90200C
	BE_O26A0_REG_LED_AD_VS_DLY_T                                       ad_vs_dly;	//0xCC902010
	BE_O26A0_REG_LED_AD_I2C_SLAVE_ADDR_T                       ad_i2c_slave_addr;	//0xCC902014
	BE_O26A0_REG_LED_AD_I2C_CONF_T                                   ad_i2c_conf;	//0xCC902018
	BE_O26A0_REG_LED_AD_VERSION_T                                     ad_version;	//0xCC90201C
	BE_O26A0_REG_LED_AD_GENERAL_REG0_T                           ad_general_reg0;	//0xCC902020
	BE_O26A0_REG_LED_AD_GENERAL_REG1_T                           ad_general_reg1;	//0xCC902024
	BE_O26A0_REG_LED_AD_GENERAL_REG2_T                           ad_general_reg2;	//0xCC902028
	BE_O26A0_REG_LED_AD_GENERAL_REG3_T                           ad_general_reg3;	//0xCC90202C
	BE_O26A0_REG_LED_AD_CG_CTRL_T                                     ad_cg_ctrl;	//0xCC902030
	UINT32                                                 reserved1712;	//0xCC902034
	UINT32                                                 reserved1713;	//0xCC902038
	UINT32                                                 reserved1714;	//0xCC90203C
	BE_O26A0_REG_LED_AD_I2C_RD_ON_T                                 ad_i2c_rd_on;	//0xCC902040
	BE_O26A0_REG_LED_AD_I2C_RD_ADDR_T                             ad_i2c_rd_addr;	//0xCC902044
	BE_O26A0_REG_LED_AD_I2C_RD_DATA_T                             ad_i2c_rd_data;	//0xCC902048
	BE_O26A0_REG_LED_AD_BLU_VS1_T0_T                               ad_blu_vs1_t0;	//0xCC90204C
	BE_O26A0_REG_LED_AD_VS1_DLY_T                                     ad_vs1_dly;	//0xCC902050
	BE_O26A0_REG_LED_AD_BLU_VS2_T0_T                               ad_blu_vs2_t0;	//0xCC902054
	BE_O26A0_REG_LED_AD_VS2_DLY_T                                     ad_vs2_dly;	//0xCC902058
	BE_O26A0_REG_LED_AD_BLU_VS3_T0_T                               ad_blu_vs3_t0;	//0xCC90205C
	BE_O26A0_REG_LED_AD_VS3_DLY_T                                     ad_vs3_dly;	//0xCC902060
	UINT32                                                 reserved1715;	//0xCC902064
	UINT32                                                 reserved1716;	//0xCC902068
	UINT32                                                 reserved1717;	//0xCC90206C
	UINT32                                                 reserved1718;	//0xCC902070
	UINT32                                                 reserved1719;	//0xCC902074
	UINT32                                                 reserved1720;	//0xCC902078
	UINT32                                                 reserved1721;	//0xCC90207C
	BE_O26A0_REG_LED_AD_SPI_CFG0_T                                   ad_spi_cfg0;	//0xCC902080
	BE_O26A0_REG_LED_AD_SPI_CMD_MODE_T                           ad_spi_cmd_mode;	//0xCC902084
	BE_O26A0_REG_LED_AD_M_SPI_CH_MASK_T                         ad_m_spi_ch_mask;	//0xCC902088
	BE_O26A0_REG_LED_AD_SPI_IDC01_T                                 ad_spi_idc01;	//0xCC90208C
	BE_O26A0_REG_LED_AD_SPI_IDC23_T                                 ad_spi_idc23;	//0xCC902090
	BE_O26A0_REG_LED_AD_SPI_CMD01_T                                 ad_spi_cmd01;	//0xCC902094
	BE_O26A0_REG_LED_AD_SPI_CMD23_T                                 ad_spi_cmd23;	//0xCC902098
	BE_O26A0_REG_LED_AD_SCLK_T1_T                                     ad_sclk_t1;	//0xCC90209C
	BE_O26A0_REG_LED_AD_SCLK_T2_T                                     ad_sclk_t2;	//0xCC9020A0
	BE_O26A0_REG_LED_AD_SCLK_T3_T                                     ad_sclk_t3;	//0xCC9020A4
	BE_O26A0_REG_LED_AD_SCLK_T4_T                                     ad_sclk_t4;	//0xCC9020A8
	BE_O26A0_REG_LED_AD_SCLK_T5_T                                     ad_sclk_t5;	//0xCC9020AC
	BE_O26A0_REG_LED_AD_SPI_CMD45_T                                 ad_spi_cmd45;	//0xCC9020B0
	UINT32                                                 reserved1722;	//0xCC9020B4
	UINT32                                                 reserved1723;	//0xCC9020B8
	UINT32                                                 reserved1724;	//0xCC9020BC
	BE_O26A0_REG_LED_AD_BLK_SP0_T                                     ad_blk_sp0;	//0xCC9020C0
	BE_O26A0_REG_LED_AD_BLK_SP1_T                                     ad_blk_sp1;	//0xCC9020C4
	BE_O26A0_REG_LED_AD_BLK_SP2_T                                     ad_blk_sp2;	//0xCC9020C8
	BE_O26A0_REG_LED_AD_BLK_SP3_T                                     ad_blk_sp3;	//0xCC9020CC
	BE_O26A0_REG_LED_AD_BNH_SEG0_T                                   ad_bnh_seg0;	//0xCC9020D0
	BE_O26A0_REG_LED_AD_BNH_SEG1_T                                   ad_bnh_seg1;	//0xCC9020D4
	BE_O26A0_REG_LED_AD_BNH_SEG2_T                                   ad_bnh_seg2;	//0xCC9020D8
	BE_O26A0_REG_LED_AD_BNH_SEG3_T                                   ad_bnh_seg3;	//0xCC9020DC
	BE_O26A0_REG_LED_AD_BNV_SEG0_T                                   ad_bnv_seg0;	//0xCC9020E0
	BE_O26A0_REG_LED_AD_BNV_SEG1_T                                   ad_bnv_seg1;	//0xCC9020E4
	BE_O26A0_REG_LED_AD_BNV_SEG2_T                                   ad_bnv_seg2;	//0xCC9020E8
	BE_O26A0_REG_LED_AD_BNV_SEG3_T                                   ad_bnv_seg3;	//0xCC9020EC
	UINT32                                                 reserved1725;	//0xCC9020F0
	UINT32                                                 reserved1726;	//0xCC9020F4
	UINT32                                                 reserved1727;	//0xCC9020F8
	UINT32                                                 reserved1728;	//0xCC9020FC
	BE_O26A0_REG_LED_AD_PWM_VALUE_T                                 ad_pwm_value;	//0xCC902100
	BE_O26A0_REG_LED_AD_BLU_MAXVAL_EN_T                         ad_blu_maxval_en;	//0xCC902104
	BE_O26A0_REG_LED_AD_SPI_ALEF2_EN_T                           ad_spi_alef2_en;	//0xCC902108
	BE_O26A0_REG_LED_AD_SPI_ALEF2_CLR_T                         ad_spi_alef2_clr;	//0xCC90210C
	BE_O26A0_REG_LED_AD_SPI0_ALEF2_LUT_T                       ad_spi0_alef2_lut;	//0xCC902110
	BE_O26A0_REG_LED_AD_SPI0_ALEF2_LUT_RD_T                 ad_spi0_alef2_lut_rd;	//0xCC902114
	BE_O26A0_REG_LED_AD_SPI1_ALEF2_LUT_T                       ad_spi1_alef2_lut;	//0xCC902118
	BE_O26A0_REG_LED_AD_SPI1_ALEF2_LUT_RD_T                 ad_spi1_alef2_lut_rd;	//0xCC90211C
	BE_O26A0_REG_LED_AD_SPI2_ALEF2_LUT_T                       ad_spi2_alef2_lut;	//0xCC902120
	BE_O26A0_REG_LED_AD_SPI2_ALEF2_LUT_RD_T                 ad_spi2_alef2_lut_rd;	//0xCC902124
	BE_O26A0_REG_LED_AD_SPI3_ALEF2_LUT_T                       ad_spi3_alef2_lut;	//0xCC902128
	BE_O26A0_REG_LED_AD_SPI3_ALEF2_LUT_RD_T                 ad_spi3_alef2_lut_rd;	//0xCC90212C
	UINT32                                                 reserved1729;	//0xCC902130
	UINT32                                                 reserved1730;	//0xCC902134
	UINT32                                                 reserved1731;	//0xCC902138
	UINT32                                                 reserved1732;	//0xCC90213C
	BE_O26A0_REG_LED_AD_EXT_INT_EN_T                               ad_ext_int_en;	//0xCC902140
	BE_O26A0_REG_LED_AD_EXT_INT_STATUS_T                       ad_ext_int_status;	//0xCC902144
	BE_O26A0_REG_LED_AD_EXT_INT_RAW_STATUS_T               ad_ext_int_raw_status;	//0xCC902148
	BE_O26A0_REG_LED_AD_EXT_INT_CLR_T                             ad_ext_int_clr;	//0xCC90214C
	BE_O26A0_REG_LED_AD_EXT_INT_LINE_NUM_T                   ad_ext_int_line_num;	//0xCC902150
	UINT32                                                 reserved1733;	//0xCC902154
	UINT32                                                 reserved1734;	//0xCC902158
	UINT32                                                 reserved1735;	//0xCC90215C
	UINT32                                                 reserved1736;	//0xCC902160
	UINT32                                                 reserved1737;	//0xCC902164
	UINT32                                                 reserved1738;	//0xCC902168
	UINT32                                                 reserved1739;	//0xCC90216C
	UINT32                                                 reserved1740;	//0xCC902170
	UINT32                                                 reserved1741;	//0xCC902174
	UINT32                                                 reserved1742;	//0xCC902178
	UINT32                                                 reserved1743;	//0xCC90217C
	UINT32                                                 reserved1744;	//0xCC902180
	UINT32                                                 reserved1745;	//0xCC902184
	UINT32                                                 reserved1746;	//0xCC902188
	UINT32                                                 reserved1747;	//0xCC90218C
	UINT32                                                 reserved1748;	//0xCC902190
	UINT32                                                 reserved1749;	//0xCC902194
	UINT32                                                 reserved1750;	//0xCC902198
	UINT32                                                 reserved1751;	//0xCC90219C
	UINT32                                                 reserved1752;	//0xCC9021A0
	UINT32                                                 reserved1753;	//0xCC9021A4
	UINT32                                                 reserved1754;	//0xCC9021A8
	UINT32                                                 reserved1755;	//0xCC9021AC
	UINT32                                                 reserved1756;	//0xCC9021B0
	UINT32                                                 reserved1757;	//0xCC9021B4
	UINT32                                                 reserved1758;	//0xCC9021B8
	UINT32                                                 reserved1759;	//0xCC9021BC
	UINT32                                                 reserved1760;	//0xCC9021C0
	UINT32                                                 reserved1761;	//0xCC9021C4
	UINT32                                                 reserved1762;	//0xCC9021C8
	UINT32                                                 reserved1763;	//0xCC9021CC
	UINT32                                                 reserved1764;	//0xCC9021D0
	UINT32                                                 reserved1765;	//0xCC9021D4
	UINT32                                                 reserved1766;	//0xCC9021D8
	UINT32                                                 reserved1767;	//0xCC9021DC
	UINT32                                                 reserved1768;	//0xCC9021E0
	UINT32                                                 reserved1769;	//0xCC9021E4
	UINT32                                                 reserved1770;	//0xCC9021E8
	UINT32                                                 reserved1771;	//0xCC9021EC
	UINT32                                                 reserved1772;	//0xCC9021F0
	UINT32                                                 reserved1773;	//0xCC9021F4
	UINT32                                                 reserved1774;	//0xCC9021F8
	UINT32                                                 reserved1775;	//0xCC9021FC
	UINT32                                                 reserved1776;	//0xCC902200
	UINT32                                                 reserved1777;	//0xCC902204
	UINT32                                                 reserved1778;	//0xCC902208
	UINT32                                                 reserved1779;	//0xCC90220C
	UINT32                                                 reserved1780;	//0xCC902210
	UINT32                                                 reserved1781;	//0xCC902214
	UINT32                                                 reserved1782;	//0xCC902218
	UINT32                                                 reserved1783;	//0xCC90221C
	BE_O26A0_REG_LED_AD_VS_SEL_T                                       ad_vs_sel;	//0xCC902220
	UINT32                                                 reserved1784;	//0xCC902224
	UINT32                                                 reserved1785;	//0xCC902228
	UINT32                                                 reserved1786;	//0xCC90222C
	UINT32                                                 reserved1787;	//0xCC902230
	UINT32                                                 reserved1788;	//0xCC902234
	UINT32                                                 reserved1789;	//0xCC902238
	UINT32                                                 reserved1790;	//0xCC90223C
	BE_O26A0_REG_LED_AD_ABI_BFI0_T                                   ad_abi_bfi0;	//0xCC902240
	BE_O26A0_REG_LED_AD_ABI_BFI1_T                                   ad_abi_bfi1;	//0xCC902244
	BE_O26A0_REG_LED_AD_ABI_BFI2_T                                   ad_abi_bfi2;	//0xCC902248
	BE_O26A0_REG_LED_AD_ABI_BFI3_T                                   ad_abi_bfi3;	//0xCC90224C
	UINT32                                                 reserved1791;	//0xCC902250
	UINT32                                                 reserved1792;	//0xCC902254
	UINT32                                                 reserved1793;	//0xCC902258
	UINT32                                                 reserved1794;	//0xCC90225C
	UINT32                                                 reserved1795;	//0xCC902260
	UINT32                                                 reserved1796;	//0xCC902264
	UINT32                                                 reserved1797;	//0xCC902268
	UINT32                                                 reserved1798;	//0xCC90226C
	UINT32                                                 reserved1799;	//0xCC902270
	UINT32                                                 reserved1800;	//0xCC902274
	UINT32                                                 reserved1801;	//0xCC902278
	UINT32                                                 reserved1802;	//0xCC90227C
	BE_O26A0_REG_LED_AD_12BIT_00_T                                   ad_12bit_00;	//0xCC902280
	BE_O26A0_REG_LED_AD_12BIT_01_T                                   ad_12bit_01;	//0xCC902284
	BE_O26A0_REG_LED_AD_12BIT_02_T                                   ad_12bit_02;	//0xCC902288
	BE_O26A0_REG_LED_AD_12BIT_03_T                                   ad_12bit_03;	//0xCC90228C
	BE_O26A0_REG_LED_AD_12BIT_04_T                                   ad_12bit_04;	//0xCC902290
	BE_O26A0_REG_LED_AD_12BIT_05_T                                   ad_12bit_05;	//0xCC902294
	BE_O26A0_REG_LED_AD_12BIT_06_T                                   ad_12bit_06;	//0xCC902298
	BE_O26A0_REG_LED_AD_12BIT_07_T                                   ad_12bit_07;	//0xCC90229C
	BE_O26A0_REG_LED_AD_12BIT_08_T                                   ad_12bit_08;	//0xCC9022A0
	BE_O26A0_REG_LED_AD_12BIT_09_T                                   ad_12bit_09;	//0xCC9022A4
	BE_O26A0_REG_LED_AD_12BIT_10_T                                   ad_12bit_10;	//0xCC9022A8
	BE_O26A0_REG_LED_AD_12BIT_11_T                                   ad_12bit_11;	//0xCC9022AC
	BE_O26A0_REG_LED_AD_12BIT_12_T                                   ad_12bit_12;	//0xCC9022B0
	BE_O26A0_REG_LED_AD_12BIT_13_T                                   ad_12bit_13;	//0xCC9022B4
	BE_O26A0_REG_LED_AD_12BIT_14_T                                   ad_12bit_14;	//0xCC9022B8
	BE_O26A0_REG_LED_AD_12BIT_15_T                                   ad_12bit_15;	//0xCC9022BC
	BE_O26A0_REG_LED_AD_12BIT_16_T                                   ad_12bit_16;	//0xCC9022C0
	BE_O26A0_REG_LED_AD_12BIT_17_T                                   ad_12bit_17;	//0xCC9022C4
	BE_O26A0_REG_LED_AD_12BIT_18_T                                   ad_12bit_18;	//0xCC9022C8
	BE_O26A0_REG_LED_AD_BLU_IF_DB_MEM_PAGE_T               ad_blu_if_db_mem_page;	//0xCC9022CC
	BE_O26A0_REG_LED_AD_BLU_IF_SHIFT_16_T                     ad_blu_if_shift_16;	//0xCC9022D0
	BE_O26A0_REG_LED_AD_I2C_RD_AI_ADDR_CLR_T               ad_i2c_rd_ai_addr_clr;	//0xCC9022D4
	BE_O26A0_REG_LED_AD_I2C_RD_AI_ADDR_T                       ad_i2c_rd_ai_addr;	//0xCC9022D8
	BE_O26A0_REG_LED_AD_I2C_RD_MODE_SEL_T                     ad_i2c_rd_mode_sel;	//0xCC9022DC
	BE_O26A0_REG_LED_AD_INFO_BV_CTRL_00_T                     ad_info_bv_ctrl_00;	//0xCC9022E0
	BE_O26A0_REG_LED_AD_INFO_BV_CTRL_01_T                     ad_info_bv_ctrl_01;	//0xCC9022E4
	BE_O26A0_REG_LED_AD_INFO_BV_CTRL_02_T                     ad_info_bv_ctrl_02;	//0xCC9022E8
}BE_O26A0_REG_LED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903000 RW 0x0000_0030
	UINT32 resvd0                           :4;
	UINT32 reg_init_sel                     :3;	//(6:4,RW,0x3) //0:vs_rising, 1:vs_falling, 2:va_rising, 3:va_falling, others:manual position from va_falling
	UINT32 resvd1                           :9;
	UINT32 reg_manual_init_pos              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903004 RW 0x0000_1000
	UINT32 reg_oled_phdr_cg_on              :1;	//(0:0,RW,0x0) //postHDR clock gating enable
	UINT32 resvd0                           :3;
	UINT32 reg_oled_decon_cg_on             :1;	//(4:4,RW,0x0) //RGB2YC, Decontour, YC2RGB clock gating enable
	UINT32 resvd1                           :3;
	UINT32 reg_oled_others_cg_on            :1;	//(8:8,RW,0x0) //OLED APL, CPC clock gating enable
	UINT32 resvd2                           :3;
	UINT32 reg_phdr_mem_sel                 :1;	//(12:12,RW,0x1) //shared mem use 0:boundary use 1:posthdr use
	UINT32 resvd3                           :19;
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903008 RW 0x0000_0030
	UINT32 reg_oapl_input_sel               :1;	//(0:0,RW,0x0) //0: cpc input, 1: cpc output
	UINT32 reg_oapl_led_input_use           :1;	//(1:1,RW,0x0) //0: oled input, 1: led input
	UINT32 resvd0                           :2;
	UINT32 reg_oapl_init_sel                :3;	//(6:4,RW,0x3) //0:out_vs_rising, 1:out_vs_falling, 2:out_va_rising, 3:out_va_falling, others:manual position from out_va_falling
	UINT32 resvd1                           :9;
	UINT32 reg_oapl_manual_init_pos         :16;	//(31:16,RW,0x0) //OLED APL, CPC clock gating enable
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903010 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_FSW_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903014 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_FSW_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903018 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_FSW_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90301C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_FSW_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903020 RW 0x0000_7F04
	UINT32 reg_cpc_en                       :1;	//(0:0,RW,0x0) //
	UINT32 reg_debug_mode_en                :1;	//(1:1,RW,0x0) //
	UINT32 reg_elps_lut_en                  :1;	//(2:2,RW,0x1) //ellipse gain lut enable
	UINT32 resvd0                           :1;
	UINT32 reg_cpc_debug_mode               :2;	//(5:4,RW,0x0) //0:final alpha, 1:ellipse gain, 2: vertex gain, 3:osd alpha
	UINT32 resvd1                           :2;
	UINT32 reg_cpc_master_gain              :8;	//(15:8,RW,0x7F) //min:0 ~ max:2.0(0x80 = 1.0)
	UINT32 resvd2                           :16;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903024 RW 0x0F00_0870
	UINT32 reg_disp_height                  :12;	//(11:0,RW,0x870) //displya height
	UINT32 resvd0                           :4;
	UINT32 reg_disp_width                   :12;	//(27:16,RW,0xF00) //display width(not channel image size)
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903028 RW 0x0B40_0654
	UINT32 reg_ellipse_b                    :12;	//(11:0,RW,0x654) //
	UINT32 reg_shift_y                      :2;	//(13:12,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_ellipse_a                    :12;	//(27:16,RW,0xB40) //
	UINT32 reg_shift_x                      :2;	//(29:28,RW,0x0) //
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90302C RW 0x0200_0200
	UINT32 reg_vrtx_gain_tr                 :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_vrtx_gain_tl                 :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903030 RW 0x03FF_03FF
	UINT32 reg_vrtx_gain_br                 :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_vrtx_gain_bl                 :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903034 RW 0x0064_0000
	UINT32 reg_elps_y0                      :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x0                      :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903038 RW 0x00C8_0040
	UINT32 reg_elps_y1                      :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x1                      :10;	//(25:16,RW,0xC8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90303C RW 0x012C_0096
	UINT32 reg_elps_y2                      :10;	//(9:0,RW,0x96) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x2                      :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903040 RW 0x0190_015E
	UINT32 reg_elps_y3                      :10;	//(9:0,RW,0x15E) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x3                      :10;	//(25:16,RW,0x190) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903044 RW 0x0258_0226
	UINT32 reg_elps_y4                      :10;	//(9:0,RW,0x226) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x4                      :10;	//(25:16,RW,0x258) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903048 RW 0x02BC_0280
	UINT32 reg_elps_y5                      :10;	//(9:0,RW,0x280) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x5                      :10;	//(25:16,RW,0x2BC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90304C RW 0x0320_02BC
	UINT32 reg_elps_y6                      :10;	//(9:0,RW,0x2BC) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x6                      :10;	//(25:16,RW,0x320) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903050 RW 0x03FF_02EE
	UINT32 reg_elps_y7                      :10;	//(9:0,RW,0x2EE) //
	UINT32 resvd0                           :6;
	UINT32 reg_elps_x7                      :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903054 RW 0x0080_ACFF
	UINT32 reg_osd_x3                       :8;	//(7:0,RW,0xff) //
	UINT32 reg_osd_x2                       :8;	//(15:8,RW,0xac) //
	UINT32 reg_osd_x1                       :8;	//(23:16,RW,0x80) //
	UINT32 reg_osd_x0                       :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903058 RW 0xFF00_0000
	UINT32 reg_osd_y3                       :8;	//(7:0,RW,0x0) //
	UINT32 reg_osd_y2                       :8;	//(15:8,RW,0x0) //
	UINT32 reg_osd_y1                       :8;	//(23:16,RW,0x0) //
	UINT32 reg_osd_y0                       :8;	//(31:24,RW,0xff) //
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90305C RW 0x0064_003C
	UINT32 reg_cpc_y0                       :10;	//(9:0,RW,0x3c) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x0                       :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903060 RW 0x00C8_0078
	UINT32 reg_cpc_y1                       :10;	//(9:0,RW,0x78) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x1                       :10;	//(25:16,RW,0xC8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903064 RW 0x012C_00B4
	UINT32 reg_cpc_y2                       :10;	//(9:0,RW,0xb4) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x2                       :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903068 RW 0x0190_00F0
	UINT32 reg_cpc_y3                       :10;	//(9:0,RW,0xf0) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x3                       :10;	//(25:16,RW,0x190) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90306C RW 0x0258_0168
	UINT32 reg_cpc_y4                       :10;	//(9:0,RW,0x168) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x4                       :10;	//(25:16,RW,0x258) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903070 RW 0x02BC_01A4
	UINT32 reg_cpc_y5                       :10;	//(9:0,RW,0x1a4) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x5                       :10;	//(25:16,RW,0x2BC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903074 RW 0x0320_01E0
	UINT32 reg_cpc_y6                       :10;	//(9:0,RW,0x1e0) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x6                       :10;	//(25:16,RW,0x320) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903078 RW 0x03FF_0258
	UINT32 reg_cpc_y7                       :10;	//(9:0,RW,0x258) //
	UINT32 resvd0                           :6;
	UINT32 reg_cpc_x7                       :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_CPC_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903080 RW 0x0870_0F00
	UINT32 reg_wid                          :16;	//(15:0,RW,0xF00) //display width(not channel image size)
	UINT32 reg_hei                          :16;	//(31:16,RW,0x870) //displya height
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_000_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903084 RW 0x0000_0000
	UINT32 reg_init_sel                     :3;	//(2:0,RW,0x0) //
	UINT32 resvd                            :13;
	UINT32 reg_manual_init_pos              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_001_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903088 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_002_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90308C RW 0x1818_2501
	UINT32 reg_tcm_inp_sel                  :1;	//(0:0,RW,0x1) //0:Y, 1:V
	UINT32 resvd0                           :1;
	UINT32 reg_l_gain_sel                   :2;	//(3:2,RW,0x0) //0:l_gain 1:max 2:sum 3:obj
	UINT32 reg_illuminant_map_sel           :1;	//(4:4,RW,0x0) //1:illuminant_map selected
	UINT32 resvd1                           :3;
	UINT32 reg_obj_out_dly                  :6;	//(13:8,RW,0x25) //1:illuminant_map selected
	UINT32 resvd2                           :2;
	UINT32 reg_oai_in_pel_dly               :5;	//(20:16,RW,0x18) //
	UINT32 resvd3                           :3;
	UINT32 reg_oai_in_obj_dly               :5;	//(28:24,RW,0x18) //
	UINT32 resvd4                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_003_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903090 RW 0x17B0_6680
	UINT32 reg_bst_gain_type_sel            :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_bst_gain_shift               :4;	//(7:4,RW,0x8) //
	UINT32 reg_bst_max_ratio                :10;	//(17:8,RW,0x66) //
	UINT32 resvd1                           :2;
	UINT32 reg_bst_max_value                :10;	//(29:20,RW,0x17B) //
	UINT32 resvd2                           :2;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_004_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903094 RW 0x4000_8011
	UINT32 reg_bst_osd_on                   :1;	//(0:0,RW,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_bst_lsr_on                   :1;	//(4:4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_bst_master_gain              :8;	//(15:8,RW,0x80) //
	UINT32 resvd2                           :12;
	UINT32 reg_bst_out_sel                  :4;	//(31:28,RW,0x4) //0: enable, 1:l_gain, 2:s_gain, 3:g_gain, 4:disable, 5:osd_gain, 6:lsr_gain
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_005_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903098 RW 0x0000_0000
	UINT32 reg_apl_run_mode                 :1;	//(0:0,RW,0x0) //0:from apl g/l gain lut, 1:from force gain
	UINT32 resvd                            :15;
	UINT32 reg_apl_force_g_gain             :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_force_l_gain             :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_006_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90309C RW 0x0000_0001
	UINT32 reg_use_blank_period_cnt         :1;	//(0:0,RW,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_use_extern_valid             :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :11;
	UINT32 reg_manual_blank_cnt             :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_007_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030A0 RW 0x8080_8010
	UINT32 reg_sat_sel                      :1;	//(0:0,RW,0x0) //0:(max-min)/max, 1:max-min
	UINT32 resvd0                           :3;
	UINT32 reg_hsv_hsl_sel                  :1;	//(4:4,RW,0x1) //0:HSL, 1:HSV
	UINT32 resvd1                           :3;
	UINT32 reg_ihsv_sgain                   :8;	//(15:8,RW,0x80) //
	UINT32 reg_ihsv_soffset                 :8;	//(23:16,RW,0x80) //
	UINT32 reg_ihsv_hoffset                 :8;	//(31:24,RW,0x80) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_008_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030A4 RW 0x0000_8080
	UINT32 reg_ihsv_vgain                   :8;	//(7:0,RW,0x80) //
	UINT32 reg_ihsv_voffset                 :8;	//(15:8,RW,0x80) //
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_009_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030A8 RW 0x03FF_0360
	UINT32 reg_s_lut_x6                     :10;	//(9:0,RW,0x360) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x7                     :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_010_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030AC RW 0x02D0_0240
	UINT32 reg_s_lut_x4                     :10;	//(9:0,RW,0x240) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x5                     :10;	//(25:16,RW,0x2D0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_011_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030B0 RW 0x01B0_0120
	UINT32 reg_s_lut_s2                     :10;	//(9:0,RW,0x120) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x3                     :10;	//(25:16,RW,0x1B0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_012_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030B4 RW 0x0090_0000
	UINT32 reg_s_lut_x0                     :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_x1                     :10;	//(25:16,RW,0x90) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_013_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030B8 RW 0x0000_0050
	UINT32 reg_s_lut_y6                     :10;	//(9:0,RW,0x50) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y7                     :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_014_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030BC RW 0x0098_00E0
	UINT32 reg_s_lut_y4                     :10;	//(9:0,RW,0xE0) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y5                     :10;	//(25:16,RW,0x98) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_015_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030C0 RW 0x0128_0170
	UINT32 reg_s_lut_y2                     :10;	//(9:0,RW,0x170) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y3                     :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_016_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030C4 RW 0x01B8_0200
	UINT32 reg_s_lut_y0                     :10;	//(9:0,RW,0x200) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_lut_y1                     :10;	//(25:16,RW,0x1B8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_017_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030C8 RW 0x0064_0000
	UINT32 reg_lg_bs_exp_y_ofs0             :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs1             :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_018_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030CC RW 0x012C_00C8
	UINT32 reg_lg_bs_exp_y_ofs2             :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs3             :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_019_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030D0 RW 0x01F4_0190
	UINT32 reg_lg_bs_exp_y_ofs4             :10;	//(9:0,RW,0x190) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_bs_exp_y_ofs5             :10;	//(25:16,RW,0x1F4) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_020_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030D4 RW 0x0000_0258
	UINT32 reg_lg_bs_exp_y_ofs6             :10;	//(9:0,RW,0x258) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_021_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030D8 RW 0xC808_0400
	UINT32 reg_lg_bs_exp_s_ofs0             :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_bs_exp_s_ofs1             :8;	//(15:8,RW,0x4) //
	UINT32 reg_lg_bs_exp_s_ofs2             :8;	//(23:16,RW,0x8) //
	UINT32 reg_lg_bs_exp_s_ofs3             :8;	//(31:24,RW,0xC8) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_022_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030DC RW 0x0019_1410
	UINT32 reg_lg_bs_exp_s_ofs4             :8;	//(7:0,RW,0x10) //
	UINT32 reg_lg_bs_exp_s_ofs5             :8;	//(15:8,RW,0x14) //
	UINT32 reg_lg_bs_exp_s_ofs6             :8;	//(23:16,RW,0x19) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_023_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030E0 RW 0x0073_3982
	UINT32 reg_lg_bs_exp_s_wei              :3;	//(2:0,RW,0x2) //
	UINT32 resvd0                           :1;
	UINT32 reg_lg_y_max                     :10;	//(13:4,RW,0x398) //
	UINT32 resvd1                           :2;
	UINT32 reg_lg_ybs_scale                 :8;	//(23:16,RW,0x73) //
	UINT32 resvd2                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_024_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030E4 RW 0xFFEE_DDCC
	UINT32 reg_lg_yy_lut_x12                :8;	//(7:0,RW,0xCC) //
	UINT32 reg_lg_yy_lut_x13                :8;	//(15:8,RW,0xDD) //
	UINT32 reg_lg_yy_lut_x14                :8;	//(23:16,RW,0xEE) //
	UINT32 reg_lg_yy_lut_x15                :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_025_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030E8 RW 0xBBAA_9988
	UINT32 reg_lg_yy_lut_x08                :8;	//(7:0,RW,0x88) //
	UINT32 reg_lg_yy_lut_x09                :8;	//(15:8,RW,0x99) //
	UINT32 reg_lg_yy_lut_x10                :8;	//(23:16,RW,0xAA) //
	UINT32 reg_lg_yy_lut_x11                :8;	//(31:24,RW,0xBB) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_026_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030EC RW 0x7766_5544
	UINT32 reg_lg_yy_lut_x04                :8;	//(7:0,RW,0x44) //
	UINT32 reg_lg_yy_lut_x05                :8;	//(15:8,RW,0x55) //
	UINT32 reg_lg_yy_lut_x06                :8;	//(23:16,RW,0x66) //
	UINT32 reg_lg_yy_lut_x07                :8;	//(31:24,RW,0x77) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_027_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030F0 RW 0x3322_1100
	UINT32 reg_lg_yy_lut_x00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_yy_lut_x01                :8;	//(15:8,RW,0x11) //
	UINT32 reg_lg_yy_lut_x02                :8;	//(23:16,RW,0x22) //
	UINT32 reg_lg_yy_lut_x03                :8;	//(31:24,RW,0x33) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_028_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030F4 RW 0xFFD9_B99E
	UINT32 reg_lg_yy_lut_y12                :8;	//(7:0,RW,0x9E) //
	UINT32 reg_lg_yy_lut_y13                :8;	//(15:8,RW,0xB9) //
	UINT32 reg_lg_yy_lut_y14                :8;	//(23:16,RW,0xD9) //
	UINT32 reg_lg_yy_lut_y15                :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_029_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030F8 RW 0x8673_6253
	UINT32 reg_lg_yy_lut_y08                :8;	//(7:0,RW,0x53) //
	UINT32 reg_lg_yy_lut_y09                :8;	//(15:8,RW,0x62) //
	UINT32 reg_lg_yy_lut_y10                :8;	//(23:16,RW,0x73) //
	UINT32 reg_lg_yy_lut_y11                :8;	//(31:24,RW,0x86) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_030_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9030FC RW 0x473C_332C
	UINT32 reg_lg_yy_lut_y04                :8;	//(7:0,RW,0x2C) //
	UINT32 reg_lg_yy_lut_y05                :8;	//(15:8,RW,0x33) //
	UINT32 reg_lg_yy_lut_y06                :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lg_yy_lut_y07                :8;	//(31:24,RW,0x47) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_031_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903100 RW 0x2520_1B17
	UINT32 reg_lg_yy_lut_y00                :8;	//(7:0,RW,0x17) //
	UINT32 reg_lg_yy_lut_y01                :8;	//(15:8,RW,0x1B) //
	UINT32 reg_lg_yy_lut_y02                :8;	//(23:16,RW,0x20) //
	UINT32 reg_lg_yy_lut_y03                :8;	//(31:24,RW,0x25) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_032_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903104 RW 0x0167_0167
	UINT32 reg_lg_h_lut_x30                 :10;	//(9:0,RW,0x167) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x31                 :10;	//(25:16,RW,0x167) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_033_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903108 RW 0x015C_0150
	UINT32 reg_lg_h_lut_x28                 :10;	//(9:0,RW,0x150) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x29                 :10;	//(25:16,RW,0x15C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_034_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90310C RW 0x0144_0138
	UINT32 reg_lg_h_lut_x26                 :10;	//(9:0,RW,0x138) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x27                 :10;	//(25:16,RW,0x144) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_035_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903110 RW 0x012C_0120
	UINT32 reg_lg_h_lut_x24                 :10;	//(9:0,RW,0x120) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x25                 :10;	//(25:16,RW,0x12C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_036_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903114 RW 0x0114_0108
	UINT32 reg_lg_h_lut_x22                 :10;	//(9:0,RW,0x108) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x23                 :10;	//(25:16,RW,0x114) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_037_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903118 RW 0x00FC_00F0
	UINT32 reg_lg_h_lut_x20                 :10;	//(9:0,RW,0xF0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x21                 :10;	//(25:16,RW,0xFC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_038_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90311C RW 0x00E4_00D8
	UINT32 reg_lg_h_lut_x18                 :10;	//(9:0,RW,0xD8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x19                 :10;	//(25:16,RW,0xE4) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_039_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903120 RW 0x00CC_00C0
	UINT32 reg_lg_h_lut_x16                 :10;	//(9:0,RW,0xC0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x17                 :10;	//(25:16,RW,0xCC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_040_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903124 RW 0x00B4_00A8
	UINT32 reg_lg_h_lut_x14                 :10;	//(9:0,RW,0xA8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x15                 :10;	//(25:16,RW,0xB4) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_041_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903128 RW 0x009C_0090
	UINT32 reg_lg_h_lut_x12                 :10;	//(9:0,RW,0x90) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x13                 :10;	//(25:16,RW,0x9C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_042_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90312C RW 0x0084_0078
	UINT32 reg_lg_h_lut_x10                 :10;	//(9:0,RW,0x78) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x11                 :10;	//(25:16,RW,0x84) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_043_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903130 RW 0x006C_0060
	UINT32 reg_lg_h_lut_x08                 :10;	//(9:0,RW,0x60) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x09                 :10;	//(25:16,RW,0x6C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_044_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903134 RW 0x0054_0048
	UINT32 reg_lg_h_lut_x06                 :10;	//(9:0,RW,0x48) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x07                 :10;	//(25:16,RW,0x54) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_045_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903138 RW 0x003C_0030
	UINT32 reg_lg_h_lut_x04                 :10;	//(9:0,RW,0x30) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x05                 :10;	//(25:16,RW,0x3C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_046_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90313C RW 0x0024_0018
	UINT32 reg_lg_h_lut_x02                 :10;	//(9:0,RW,0x18) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x03                 :10;	//(25:16,RW,0x24) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_047_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903140 RW 0x000C_0000
	UINT32 reg_lg_h_lut_x00                 :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_x01                 :10;	//(25:16,RW,0xC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_048_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903144 RW 0x0001_0001
	UINT32 reg_lg_h_lut_y30                 :10;	//(9:0,RW,0x1) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y31                 :10;	//(25:16,RW,0x1) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_049_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903148 RW 0x0003_0006
	UINT32 reg_lg_h_lut_y28                 :10;	//(9:0,RW,0x6) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y29                 :10;	//(25:16,RW,0x3) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_050_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90314C RW 0x0009_0009
	UINT32 reg_lg_h_lut_y26                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y27                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_051_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903150 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y24                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y25                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_052_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903154 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y22                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y23                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_053_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903158 RW 0x0009_0009
	UINT32 reg_lg_h_lut_y20                 :10;	//(9:0,RW,0x9) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y21                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_054_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90315C RW 0x0009_000A
	UINT32 reg_lg_h_lut_y18                 :10;	//(9:0,RW,0xA) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y19                 :10;	//(25:16,RW,0x9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_055_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903160 RW 0x000C_000F
	UINT32 reg_lg_h_lut_y16                 :10;	//(9:0,RW,0xF) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y17                 :10;	//(25:16,RW,0xC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_056_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903164 RW 0x0011_0014
	UINT32 reg_lg_h_lut_y14                 :10;	//(9:0,RW,0x14) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y15                 :10;	//(25:16,RW,0x11) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_057_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903168 RW 0x0017_001B
	UINT32 reg_lg_h_lut_y12                 :10;	//(9:0,RW,0x1B) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y13                 :10;	//(25:16,RW,0x17) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_058_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90316C RW 0x001E_0022
	UINT32 reg_lg_h_lut_y10                 :10;	//(9:0,RW,0x22) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y11                 :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_059_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903170 RW 0x0023_002D
	UINT32 reg_lg_h_lut_y08                 :10;	//(9:0,RW,0x2D) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y09                 :10;	//(25:16,RW,0x23) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_060_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903174 RW 0x0044_005E
	UINT32 reg_lg_h_lut_y06                 :10;	//(9:0,RW,0x5E) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y07                 :10;	//(25:16,RW,0x44) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_061_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903178 RW 0x0068_0058
	UINT32 reg_lg_h_lut_y04                 :10;	//(9:0,RW,0x58) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y05                 :10;	//(25:16,RW,0x68) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_062_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90317C RW 0x0038_001B
	UINT32 reg_lg_h_lut_y02                 :10;	//(9:0,RW,0x1B) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y03                 :10;	//(25:16,RW,0x38) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_063_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903180 RW 0x000A_0003
	UINT32 reg_lg_h_lut_y00                 :10;	//(9:0,RW,0x3) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_h_lut_y01                 :10;	//(25:16,RW,0xA) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_064_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903184 RW 0x0000_4000
	UINT32 reg_lg_brm_bs_cnt                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_lg_brm_exp_wei               :4;	//(15:12,RW,0x4) //
	UINT32 resvd1                           :16;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_065_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903188 RW 0x0398_037C
	UINT32 reg_lg_br_lut_x14                :10;	//(9:0,RW,0x37C) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x15                :10;	//(25:16,RW,0x398) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_066_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90318C RW 0x036D_035E
	UINT32 reg_lg_br_lut_x12                :10;	//(9:0,RW,0x35E) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x13                :10;	//(25:16,RW,0x36D) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_067_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903190 RW 0x034F_0340
	UINT32 reg_lg_br_lut_x10                :10;	//(9:0,RW,0x340) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x11                :10;	//(25:16,RW,0x34F) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_068_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903194 RW 0x0331_0322
	UINT32 reg_lg_br_lut_x08                :10;	//(9:0,RW,0x322) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x09                :10;	//(25:16,RW,0x331) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_069_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903198 RW 0x0313_0304
	UINT32 reg_lg_br_lut_x06                :10;	//(9:0,RW,0x304) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x07                :10;	//(25:16,RW,0x313) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_070_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90319C RW 0x02F5_02E6
	UINT32 reg_lg_br_lut_x04                :10;	//(9:0,RW,0x2E6) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x05                :10;	//(25:16,RW,0x2F5) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_071_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031A0 RW 0x02D7_02C8
	UINT32 reg_lg_br_lut_x02                :10;	//(9:0,RW,0x2C8) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x03                :10;	//(25:16,RW,0x2D7) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_072_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031A4 RW 0x02B9_02AA
	UINT32 reg_lg_br_lut_x00                :10;	//(9:0,RW,0x2AA) //
	UINT32 resvd0                           :6;
	UINT32 reg_lg_br_lut_x01                :10;	//(25:16,RW,0x2B9) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_073_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031A8 RW 0xFFC6_AB91
	UINT32 reg_lg_br_lut_y12                :8;	//(7:0,RW,0x91) //
	UINT32 reg_lg_br_lut_y13                :8;	//(15:8,RW,0xAB) //
	UINT32 reg_lg_br_lut_y14                :8;	//(23:16,RW,0xC6) //
	UINT32 reg_lg_br_lut_y15                :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_074_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031AC RW 0x7A65_5240
	UINT32 reg_lg_br_lut_y08                :8;	//(7:0,RW,0x40) //
	UINT32 reg_lg_br_lut_y09                :8;	//(15:8,RW,0x52) //
	UINT32 reg_lg_br_lut_y10                :8;	//(23:16,RW,0x65) //
	UINT32 reg_lg_br_lut_y11                :8;	//(31:24,RW,0x7A) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_075_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031B0 RW 0x3124_1910
	UINT32 reg_lg_br_lut_y04                :8;	//(7:0,RW,0x10) //
	UINT32 reg_lg_br_lut_y05                :8;	//(15:8,RW,0x19) //
	UINT32 reg_lg_br_lut_y06                :8;	//(23:16,RW,0x24) //
	UINT32 reg_lg_br_lut_y07                :8;	//(31:24,RW,0x31) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_076_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031B4 RW 0x0904_0100
	UINT32 reg_lg_br_lut_y00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_lg_br_lut_y01                :8;	//(15:8,RW,0x1) //
	UINT32 reg_lg_br_lut_y02                :8;	//(23:16,RW,0x4) //
	UINT32 reg_lg_br_lut_y03                :8;	//(31:24,RW,0x9) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_077_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031B8 RW 0x03FF_03E0
	UINT32 reg_tcm_lut_x30                  :10;	//(9:0,RW,0x3E0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x31                  :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_078_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031BC RW 0x03BC_039C
	UINT32 reg_tcm_lut_x28                  :10;	//(9:0,RW,0x39C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x29                  :10;	//(25:16,RW,0x3BC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_079_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031C0 RW 0x037C_035C
	UINT32 reg_tcm_lut_x26                  :10;	//(9:0,RW,0x35C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x27                  :10;	//(25:16,RW,0x37C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_080_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031C4 RW 0x0338_0318
	UINT32 reg_tcm_lut_x24                  :10;	//(9:0,RW,0x318) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x25                  :10;	//(25:16,RW,0x338) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_081_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031C8 RW 0x02F8_02D8
	UINT32 reg_tcm_lut_x22                  :10;	//(9:0,RW,0x2D8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x23                  :10;	//(25:16,RW,0x2F8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_082_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031CC RW 0x02B4_0294
	UINT32 reg_tcm_lut_x20                  :10;	//(9:0,RW,0x294) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x21                  :10;	//(25:16,RW,0x2B4) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_083_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031D0 RW 0x0274_0254
	UINT32 reg_tcm_lut_x18                  :10;	//(9:0,RW,0x254) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x19                  :10;	//(25:16,RW,0x274) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_084_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031D4 RW 0x0230_0210
	UINT32 reg_tcm_lut_x16                  :10;	//(9:0,RW,0x210) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x17                  :10;	//(25:16,RW,0x230) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_085_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031D8 RW 0x01F0_01D0
	UINT32 reg_tcm_lut_x14                  :10;	//(9:0,RW,0x1D0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x15                  :10;	//(25:16,RW,0x1F0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_086_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031DC RW 0x01AC_018C
	UINT32 reg_tcm_lut_x12                  :10;	//(9:0,RW,0x18C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x13                  :10;	//(25:16,RW,0x1AC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_087_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031E0 RW 0x016C_014C
	UINT32 reg_tcm_lut_x10                  :10;	//(9:0,RW,0x14C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x11                  :10;	//(25:16,RW,0x16C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_088_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031E4 RW 0x0128_0108
	UINT32 reg_tcm_lut_x08                  :10;	//(9:0,RW,0x108) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x09                  :10;	//(25:16,RW,0x128) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_089_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031E8 RW 0x00E8_00C8
	UINT32 reg_tcm_lut_x06                  :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x07                  :10;	//(25:16,RW,0xE8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_090_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031EC RW 0x00A4_0084
	UINT32 reg_tcm_lut_x04                  :10;	//(9:0,RW,0x84) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x05                  :10;	//(25:16,RW,0xA4) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_091_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031F0 RW 0x0064_0044
	UINT32 reg_tcm_lut_x02                  :10;	//(9:0,RW,0x44) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x03                  :10;	//(25:16,RW,0x64) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_092_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031F4 RW 0x0020_0000
	UINT32 reg_tcm_lut_x00                  :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_x01                  :10;	//(25:16,RW,0x20) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_093_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031F8 RW 0x03FF_03D8
	UINT32 reg_tcm_lut_y30                  :10;	//(9:0,RW,0x3D8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y31                  :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_094_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9031FC RW 0x03AC_0384
	UINT32 reg_tcm_lut_y28                  :10;	//(9:0,RW,0x384) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y29                  :10;	//(25:16,RW,0x3AC) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_095_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903200 RW 0x035C_0334
	UINT32 reg_tcm_lut_y26                  :10;	//(9:0,RW,0x334) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y27                  :10;	//(25:16,RW,0x35C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_096_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903204 RW 0x0308_02E0
	UINT32 reg_tcm_lut_y24                  :10;	//(9:0,RW,0x2E0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y25                  :10;	//(25:16,RW,0x308) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_097_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903208 RW 0x02B8_0290
	UINT32 reg_tcm_lut_y22                  :10;	//(9:0,RW,0x290) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y23                  :10;	//(25:16,RW,0x2B8) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_098_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90320C RW 0x0264_023C
	UINT32 reg_tcm_lut_y20                  :10;	//(9:0,RW,0x23C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y21                  :10;	//(25:16,RW,0x264) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_099_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903210 RW 0x0214_01EC
	UINT32 reg_tcm_lut_y18                  :10;	//(9:0,RW,0x1EC) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y19                  :10;	//(25:16,RW,0x214) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903214 RW 0x01C0_0198
	UINT32 reg_tcm_lut_y16                  :10;	//(9:0,RW,0x198) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y17                  :10;	//(25:16,RW,0x1C0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903218 RW 0x0178_0160
	UINT32 reg_tcm_lut_y14                  :10;	//(9:0,RW,0x160) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y15                  :10;	//(25:16,RW,0x178) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90321C RW 0x0144_012C
	UINT32 reg_tcm_lut_y12                  :10;	//(9:0,RW,0x12C) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y13                  :10;	//(25:16,RW,0x144) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903220 RW 0x0114_00FC
	UINT32 reg_tcm_lut_y10                  :10;	//(9:0,RW,0xFC) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y11                  :10;	//(25:16,RW,0x114) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_104_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903224 RW 0x00E0_00C8
	UINT32 reg_tcm_lut_y08                  :10;	//(9:0,RW,0xC8) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y09                  :10;	//(25:16,RW,0xE0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903228 RW 0x00B0_0098
	UINT32 reg_tcm_lut_y06                  :10;	//(9:0,RW,0x98) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y07                  :10;	//(25:16,RW,0xB0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90322C RW 0x007C_0064
	UINT32 reg_tcm_lut_y04                  :10;	//(9:0,RW,0x64) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y05                  :10;	//(25:16,RW,0x7C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903230 RW 0x004C_0034
	UINT32 reg_tcm_lut_y02                  :10;	//(9:0,RW,0x34) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y03                  :10;	//(25:16,RW,0x4C) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903234 RW 0x0018_0000
	UINT32 reg_tcm_lut_y00                  :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_tcm_lut_y01                  :10;	//(25:16,RW,0x18) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_109_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903238 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x14                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x15                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_110_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90323C RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x12                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x13                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_111_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903240 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x10                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x11                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_112_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903244 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x08                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x09                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_113_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903248 RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x06                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x07                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_114_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90324C RW 0x03FF_03FF
	UINT32 reg_apl_lut_g_x04                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x05                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_115_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903250 RW 0x0100_0066
	UINT32 reg_apl_lut_g_x02                :10;	//(9:0,RW,0x66) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x03                :10;	//(25:16,RW,0x100) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_116_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903254 RW 0x001E_0000
	UINT32 reg_apl_lut_g_x00                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_g_x01                :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_117_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903258 RW 0x0000_0000
	UINT32 reg_apl_lut_g_y12                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y13                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y14                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y15                :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_118_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90325C RW 0x0000_0000
	UINT32 reg_apl_lut_g_y08                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y09                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y10                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y11                :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_119_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903260 RW 0x0000_0000
	UINT32 reg_apl_lut_g_y04                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_g_y05                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_g_y06                :8;	//(23:16,RW,0x0) //
	UINT32 reg_apl_lut_g_y07                :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_120_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903264 RW 0x003C_5E5E
	UINT32 reg_apl_lut_g_y00                :8;	//(7:0,RW,0x5E) //
	UINT32 reg_apl_lut_g_y01                :8;	//(15:8,RW,0x5E) //
	UINT32 reg_apl_lut_g_y02                :8;	//(23:16,RW,0x3C) //
	UINT32 reg_apl_lut_g_y03                :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_121_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903268 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x14                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x15                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_122_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90326C RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x12                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x13                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_123_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903270 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x10                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x11                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_124_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903274 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x08                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x09                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_125_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903278 RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x06                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x07                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_126_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90327C RW 0x03FF_03FF
	UINT32 reg_apl_lut_l_x04                :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x05                :10;	//(25:16,RW,0x3FF) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_127_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903280 RW 0x0100_0066
	UINT32 reg_apl_lut_l_x02                :10;	//(9:0,RW,0x66) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x03                :10;	//(25:16,RW,0x100) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_128_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903284 RW 0x001E_0000
	UINT32 reg_apl_lut_l_x00                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_apl_lut_l_x01                :10;	//(25:16,RW,0x1E) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_129_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903288 RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y12                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y13                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y14                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y15                :8;	//(31:24,RW,0x2F) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_130_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90328C RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y08                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y09                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y10                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y11                :8;	//(31:24,RW,0x2F) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_131_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903290 RW 0x2F2F_2F2F
	UINT32 reg_apl_lut_l_y04                :8;	//(7:0,RW,0x2F) //
	UINT32 reg_apl_lut_l_y05                :8;	//(15:8,RW,0x2F) //
	UINT32 reg_apl_lut_l_y06                :8;	//(23:16,RW,0x2F) //
	UINT32 reg_apl_lut_l_y07                :8;	//(31:24,RW,0x2F) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_132_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903294 RW 0x2F11_0000
	UINT32 reg_apl_lut_l_y00                :8;	//(7:0,RW,0x0) //
	UINT32 reg_apl_lut_l_y01                :8;	//(15:8,RW,0x0) //
	UINT32 reg_apl_lut_l_y02                :8;	//(23:16,RW,0x11) //
	UINT32 reg_apl_lut_l_y03                :8;	//(31:24,RW,0x2F) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_133_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903298 RW 0xFFD8_B490
	UINT32 reg_osd_lut_x04                  :8;	//(7:0,RW,0x90) //
	UINT32 reg_osd_lut_x05                  :8;	//(15:8,RW,0xB4) //
	UINT32 reg_osd_lut_x06                  :8;	//(23:16,RW,0xD8) //
	UINT32 reg_osd_lut_x07                  :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_134_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90329C RW 0x6C48_2400
	UINT32 reg_osd_lut_x00                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_osd_lut_x01                  :8;	//(15:8,RW,0x24) //
	UINT32 reg_osd_lut_x02                  :8;	//(23:16,RW,0x48) //
	UINT32 reg_osd_lut_x03                  :8;	//(31:24,RW,0x6C) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_135_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032A0 RW 0x0014_2638
	UINT32 reg_osd_lut_y04                  :8;	//(7:0,RW,0x38) //
	UINT32 reg_osd_lut_y05                  :8;	//(15:8,RW,0x26) //
	UINT32 reg_osd_lut_y06                  :8;	//(23:16,RW,0x14) //
	UINT32 reg_osd_lut_y07                  :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_136_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032A4 RW 0x4A5C_6E80
	UINT32 reg_osd_lut_y00                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_osd_lut_y01                  :8;	//(15:8,RW,0x6E) //
	UINT32 reg_osd_lut_y02                  :8;	//(23:16,RW,0x5C) //
	UINT32 reg_osd_lut_y03                  :8;	//(31:24,RW,0x4A) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_137_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032A8 RW 0xFFD8_B490
	UINT32 reg_lsr_lut_x04                  :8;	//(7:0,RW,0x90) //
	UINT32 reg_lsr_lut_x05                  :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lsr_lut_x06                  :8;	//(23:16,RW,0xD8) //
	UINT32 reg_lsr_lut_x07                  :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_138_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032AC RW 0x6C48_2400
	UINT32 reg_lsr_lut_x00                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lsr_lut_x01                  :8;	//(15:8,RW,0x24) //
	UINT32 reg_lsr_lut_x02                  :8;	//(23:16,RW,0x48) //
	UINT32 reg_lsr_lut_x03                  :8;	//(31:24,RW,0x6C) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_139_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032B0 RW 0x0014_2638
	UINT32 reg_lsr_lut_y04                  :8;	//(7:0,RW,0x38) //
	UINT32 reg_lsr_lut_y05                  :8;	//(15:8,RW,0x26) //
	UINT32 reg_lsr_lut_y06                  :8;	//(23:16,RW,0x14) //
	UINT32 reg_lsr_lut_y07                  :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_140_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032B4 RW 0x4A5C_6E80
	UINT32 reg_lsr_lut_y00                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_lsr_lut_y01                  :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lsr_lut_y02                  :8;	//(23:16,RW,0x5C) //
	UINT32 reg_lsr_lut_y03                  :8;	//(31:24,RW,0x4A) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_141_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032B8 RW 0x09CD_0001
	UINT32 reg_csc_en                       :1;	//(0:0,RW,0x1) //
	UINT32 resvd0                           :15;
	UINT32 reg_csc_coef0                    :15;	//(30:16,RW,0x9CD) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_142_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032BC RW 0x02EA_00FD
	UINT32 reg_csc_coef1                    :15;	//(14:0,RW,0xFD) //
	UINT32 resvd0                           :1;
	UINT32 reg_csc_coef2                    :15;	//(30:16,RW,0x2EA) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_143_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032C0 RW 0x0000_0000
	UINT32 reg_csc_ofst0                    :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_csc_ofst1                    :11;	//(26:16,RW,0x0) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_144_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032C4 RW 0x0040_0000
	UINT32 reg_csc_ofst2                    :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_csc_ofst3                    :11;	//(26:16,RW,0x40) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_145_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032C8 RW 0x010C_0870
	UINT32 reg_lg_va_length                 :12;	//(11:0,RW,0x870) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt0                   :12;	//(27:16,RW,0x10C) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_146_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032CC RW 0x0328_021A
	UINT32 reg_lg_bs_cnt1                   :12;	//(11:0,RW,0x21A) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt2                   :12;	//(27:16,RW,0x328) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_147_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032D0 RW 0x0544_0436
	UINT32 reg_lg_bs_cnt3                   :12;	//(11:0,RW,0x436) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt4                   :12;	//(27:16,RW,0x544) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_148_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032D4 RW 0x086E_0652
	UINT32 reg_lg_bs_cnt5                   :12;	//(11:0,RW,0x652) //
	UINT32 resvd0                           :4;
	UINT32 reg_lg_bs_cnt6                   :12;	//(27:16,RW,0x86E) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_149_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032D8 RW 0x0000_0000
	UINT32 reg_info_diff_th1                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_info_diff_th0                :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_150_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032DC RW 0x0000_0000
	UINT32 reg_info_diff_th3                :10;	//(9:0,RW,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_info_diff_th2                :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_151_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032E0 RW 0x0000_0001
	UINT32 reg_osd_th                       :8;	//(7:0,RW,0x1) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_152_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032E4 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_153_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032E8 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_154_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032EC RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_155_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032F0 RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_156_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032F4 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //
	UINT32 sync_i_h_sel                     :1;	//(16:16,RW,0x0) //
	UINT32 sync_i_v_sel                     :1;	//(17:17,RW,0x0) //
	UINT32 sync_i_inv_ha                    :1;	//(18:18,RW,0x0) //
	UINT32 sync_i_inv_va                    :1;	//(19:19,RW,0x0) //
	UINT32 sync_o_sel_ha                    :1;	//(20:20,RW,0x0) //
	UINT32 sync_o_sel_va                    :1;	//(21:21,RW,0x0) //
	UINT32 sync_o_sel_hs                    :1;	//(22:22,RW,0x0) //
	UINT32 sync_o_sel_vs                    :1;	//(23:23,RW,0x0) //
	UINT32 tp_update_hv_zero                :1;	//(24:24,RW,0x0) //
	UINT32 force_out_ha                     :1;	//(25:25,RW,0x0) //
	UINT32 force_out_va                     :1;	//(26:26,RW,0x0) //
	UINT32 force_out_hs                     :1;	//(27:27,RW,0x0) //
	UINT32 manual_cnt_h_value_en            :1;	//(28:28,RW,0x0) //
	UINT32 manual_cnt_v_value_en            :1;	//(29:29,RW,0x0) //
	UINT32 force_out_vs                     :1;	//(30:30,RW,0x0) //
	UINT32 update_force                     :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_157_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032F8 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_158_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9032FC RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_159_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903300 RW 0x0002_802A
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_160_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903304 RW 0x0002_802A
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x2A) //
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_161_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903308 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_162_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90330C RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_163_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903310 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_164_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903314 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_165_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903318 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_166_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90331C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_167_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903320 RW 0x0000_0000
	UINT32 reg_phdr_repeat_en               :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_phdr_tap_mode                :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_168_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903324 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_169_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903328 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_yy_2ch             :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_pic_lg_max_luma              :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_170_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90332C RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt0               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_171_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903330 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt1               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_172_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903334 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt2               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_173_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903338 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt3               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_174_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90333C RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt4               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_175_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903340 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt5               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_176_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903344 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt6               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_177_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903348 RO 0x0000_0000
	UINT32 reg_pic_lg_bs_cnt7               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_178_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90334C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_179_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903350 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_180_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903354 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_181_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903358 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_182_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90335C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_183_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903360 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_184_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903364 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_185_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903368 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_gg_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_186_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90336C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th0_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_187_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903370 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th1_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_188_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903374 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th2_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_189_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903378 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_th3_cnt       :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_190_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90337C RO 0x0000_0000
	UINT32 reg_ro_pel_diff_rr_max           :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 reg_ro_pel_diff_gg_max           :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_191_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903380 RO 0x0000_0000
	UINT32 reg_ro_pel_diff_bb_max           :10;	//(9:0,RO,0x0) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_192_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903390 RW 0x0000_0000
	UINT32 r_rgb2yc_en                      :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_10bit_clip_en                  :1;	//(4:4,RW,0x0) //over 1023 value clip to 1023
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903394 RW 0x0B71_0128
	UINT32 r_rgb2yc_coef1                   :15;	//(14:0,RW,0x128) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef0                   :15;	//(30:16,RW,0xB71) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903398 RW 0x0367_79B1
	UINT32 r_rgb2yc_coef3                   :15;	//(14:0,RW,0x79B1) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef2                   :15;	//(30:16,RW,0x367) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90339C RW 0x082F_7E20
	UINT32 r_rgb2yc_coef5                   :15;	//(14:0,RW,0x7E20) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef4                   :15;	//(30:16,RW,0x82F) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033A0 RW 0x7891_7F40
	UINT32 r_rgb2yc_coef7                   :15;	//(14:0,RW,0x7F40) //
	UINT32 resvd0                           :1;
	UINT32 r_rgb2yc_coef6                   :15;	//(30:16,RW,0x7891) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033A4 RW 0x082F_0000
	UINT32 resvd0                           :16;
	UINT32 r_rgb2yc_coef8                   :15;	//(30:16,RW,0x82F) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033A8 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst0                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033AC RW 0x0000_0000
	UINT32 r_rgb2yc_ofst1                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033B0 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst2                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033B4 RW 0x0000_0000
	UINT32 r_rgb2yc_ofst3                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033B8 RW 0x0000_4000
	UINT32 r_rgb2yc_ofst4                   :17;	//(16:0,RW,0x4000) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033BC RW 0x0000_4000
	UINT32 r_rgb2yc_ofst5                   :17;	//(16:0,RW,0x4000) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033C0 RW 0x03FF_0000
	UINT32 r_yc2rgb_en                      :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_manual_clip_en                 :1;	//(4:4,RW,0x0) //over r_yc2rgb_clip_th value clip to r_yc2rgb_clip_th
	UINT32 resvd1                           :11;
	UINT32 r_yc2rgb_clip_th                 :13;	//(28:16,RW,0x3FF) //
	UINT32 resvd2                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033C4 RW 0x1000_7D12
	UINT32 r_yc2rgb_coef1                   :15;	//(14:0,RW,0x7D12) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef0                   :15;	//(30:16,RW,0x1000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033C8 RW 0x78AD_1000
	UINT32 r_yc2rgb_coef3                   :15;	//(14:0,RW,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef2                   :15;	//(30:16,RW,0x78AD) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033CC RW 0x1D07_0000
	UINT32 r_yc2rgb_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef4                   :15;	//(30:16,RW,0x1D07) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033D0 RW 0x1000_0000
	UINT32 r_yc2rgb_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_yc2rgb_coef6                   :15;	//(30:16,RW,0x1000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033D4 RW 0x18A2_0000
	UINT32 resvd0                           :16;
	UINT32 r_yc2rgb_coef8                   :15;	//(30:16,RW,0x18A2) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033D8 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst0                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033DC RW 0x0001_C000
	UINT32 r_yc2rgb_ofst1                   :17;	//(16:0,RW,0x1C000) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033E0 RW 0x0001_C000
	UINT32 r_yc2rgb_ofst2                   :17;	//(16:0,RW,0x1C000) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033E4 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst3                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033E8 RW 0x0000_0000
	UINT32 r_yc2rgb_ofst4                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9033EC RW 0x0000_0000
	UINT32 r_yc2rgb_ofst5                   :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903400 RW 0x0000_0030
	UINT32 reg_oled_apl_disable             :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_apl_out_mode_hdr             :3;	//(6:4,RW,0x3) //0:manual_apl, 1:na?ve_apl,2:na?ve_apl_avg_y,3:na?ve_apl_blended_y_v,4:filt_apl_hdr
	UINT32 resvd1                           :1;
	UINT32 reg_apl_out_mode_tcon            :3;	//(10:8,RW,0x0) //0:manual_apl, 1:na?ve_apl,2:na?ve_apl_avg_y,3:na?ve_apl_blended_y_v,4:filt_apl_tcon
	UINT32 resvd2                           :1;
	UINT32 reg_in_sel_apl_tcon              :2;	//(13:12,RW,0x0) //0:manual_apl, 1:na?ve_apl,2:avg_y,3:blended_y_v
	UINT32 reg_in_sel_apl_hdr               :2;	//(15:14,RW,0x0) //0:manual_apl, 1:na?ve_apl,2:avg_y,3:blended_y_v
	UINT32 resvd3                           :16;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903404 RW 0x0000_0000
	UINT32 reg_eotf_en                      :1;	//(0:0,RW,0x0) //note : apl_eotf lut wr/rd controled by led_hif(0x780~0x788)
	UINT32 resvd0                           :3;
	UINT32 reg_eotf_rdata_sel               :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_bit_extension_mode      :2;	//(9:8,RW,0x0) //
	UINT32 resvd2                           :22;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903408 RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 reg_manual_apl                   :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90340C RW 0x0478_031F
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3410 RW 0x0326_0116
	UINT32 reg_w_crnt_wgt                   :12;	//(11:0,RW,0x116) //
	UINT32 resvd0                           :4;
	UINT32 reg_g_crnt_wgt                   :12;	//(27:16,RW,0x326) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903414 RW 0x0389_02A8
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903418 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90341C RW 0x0044_0CF9
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903420 RW 0x0088_1BD0
	UINT32 oapl_eotf_wr_done                :1;	//(0:0,RW,0x00) //"1" : lut write done
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903424 RO 0x00CC_2B72
	UINT32 oapl_eotf_wr_status              :1;	//(0:0,RO,0x00) //lut write status
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903428 RW 0x0000_0000
	UINT32 reg_oapl_eotf_wdata              :16;	//(15:0,RW,0x0) //lut write data
	UINT32 oapl_eotf_waddr                  :10;	//(25:16,RW,0x00) //lut write address
	UINT32 resvd0                           :2;
	UINT32 oapl_eotf_we                     :3;	//(30:28,RW,0x00) //"001" : write enable (Blue)	"010" : write enable (Green)	"100" : write enable (Red)
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90342C RW 0x0000_0000
	UINT32 resvd0                           :16;
	UINT32 oapl_eotf_raddr                  :10;	//(25:16,RW,0x00) //lut read address
	UINT32 resvd1                           :2;
	UINT32 oapl_eotf_re                     :3;	//(30:28,RW,0x00) //"001" : read enable (Blue)	"010" : read enable (Green)	"100" : read enable (Red)
	UINT32 resvd2                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903430 RO 0x0000_0000
	UINT32 oapl_eotf_rdata                  :16;	//(15:0,RO,0x0) //lut read data
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903434 RW 0x01DC_6E57
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903438 RW 0x0220_7FCD
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90343C RW 0x0264_917A
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903440 RW 0x02A8_A35B
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903444 RW 0x02EC_B569
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903448 RW 0x0330_C7A2
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90344C RW 0x0374_DA02
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903450 RW 0x03B8_EC86
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903454 RW 0x03FF_FFFF
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903458 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90345C RW 0x07D0_4CC2
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903460 RW 0x0FA0_9984
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903464 RW 0x0000_0010
	UINT32 reg_apl_filt_init_tcon           :1;	//(0:0,RW,0x0) //note : set '1' at least 1 frame
	UINT32 resvd0                           :3;
	UINT32 reg_apl_filt_mode_tcon           :1;	//(4:4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_apl_filt_window_size_tcon    :3;	//(10:8,RW,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_apl_iir_gain_tcon            :8;	//(23:16,RW,0x0) //
	UINT32 resvd3                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903468 RW 0x0000_0010
	UINT32 reg_apl_filt_init_phdr           :1;	//(0:0,RW,0x0) //note : set '1' at least 1 frame
	UINT32 resvd0                           :3;
	UINT32 reg_apl_filt_mode_phdr           :1;	//(4:4,RW,0x1) //
	UINT32 resvd1                           :3;
	UINT32 reg_apl_filt_window_size_phdr    :3;	//(10:8,RW,0x0) //
	UINT32 resvd2                           :5;
	UINT32 reg_apl_iir_gain_phdr            :8;	//(23:16,RW,0x0) //
	UINT32 resvd3                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90346C RW 0x0000_0180
	UINT32 reg_s_apl_val                    :8;	//(7:0,RW,0x80) //
	UINT32 reg_s_apl_val_mux                :1;	//(8:8,RW,0x1) //0:manual 1: S_APL
	UINT32 resvd                            :23;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903470 RW 0x0000_0000
	UINT32 reg_s_apl_alpha_lut_y00          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x00          :8;	//(23:16,RW,0x00) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903474 RW 0x0024_0000
	UINT32 reg_s_apl_alpha_lut_y01          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x01          :8;	//(23:16,RW,0x24) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903478 RW 0x0048_0000
	UINT32 reg_s_apl_alpha_lut_y02          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x02          :8;	//(23:16,RW,0x48) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90347C RW 0x006C_0000
	UINT32 reg_s_apl_alpha_lut_y03          :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x03          :8;	//(23:16,RW,0x6c) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903480 RW 0x0090_00FF
	UINT32 reg_s_apl_alpha_lut_y04          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x04          :8;	//(23:16,RW,0x90) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903484 RW 0x00B4_00FF
	UINT32 reg_s_apl_alpha_lut_y05          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x05          :8;	//(23:16,RW,0xB4) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903488 RW 0x00D8_00FF
	UINT32 reg_s_apl_alpha_lut_y06          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x06          :8;	//(23:16,RW,0xD8) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90348C RW 0x00FF_00FF
	UINT32 reg_s_apl_alpha_lut_y07          :8;	//(7:0,RW,0xFF) //
	UINT32 resvd0                           :8;
	UINT32 reg_s_apl_alpha_lut_x07          :8;	//(23:16,RW,0xFF) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903490 RW 0x0596_00C8
	UINT32 reg_oapl_offset_phdr             :12;	//(11:0,RW,0x00C8) //
	UINT32 resvd0                           :4;
	UINT32 reg_oapl_offset_tcon             :12;	//(27:16,RW,0x0596) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903494 RW 0x05FC_00BD
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903498 RW 0x0662_00B3
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90349C RW 0x06C8_00AA
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034A0 RW 0x072E_00A3
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034A4 RW 0x0794_009C
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034A8 RW 0x07FF_0096
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034AC RW 0x0096_001E
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034B0 RW 0x0000_0001
	UINT32 reg_oapl_rgb2yc_en               :1;	//(0:0,RW,0x1) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034B4 RW 0x094A_00D0
	UINT32 reg_oapl_rgb2yc_coef1            :15;	//(14:0,RW,0x00D0) //
	UINT32 resvd0                           :1;
	UINT32 reg_oapl_rgb2yc_coef0            :15;	//(30:16,RW,0x094A) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034B8 RW 0x0399_0000
	UINT32 resvd0                           :16;
	UINT32 reg_oapl_rgb2yc_coef2            :15;	//(30:16,RW,0x0399) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034BC RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst0            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034C0 RW 0x0000_0000
	UINT32 reg_oapl_rgb2yc_ofst3            :17;	//(16:0,RW,0x0) //
	UINT32 resvd                            :15;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034C4 RW 0x0000_0000
	UINT32 reg_hsv_hsl_sel                  :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_sat_en                       :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :27;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034C8 RW 0x0080_0080
	UINT32 reg_ihsv_sgain                   :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_vgain                   :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034CC RW 0x0080_0080
	UINT32 reg_ihsv_soffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd0                           :8;
	UINT32 reg_ihsv_hoffset                 :8;	//(23:16,RW,0x80) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034D0 RW 0x0000_0080
	UINT32 reg_ihsv_voffset                 :8;	//(7:0,RW,0x80) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034D4 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034D8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034DC RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_55_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034E0 RW 0x0145_0332
	UINT32 reg_peak2apl_lut_y12             :11;	//(10:0,RW,0x332) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x12             :11;	//(26:16,RW,0x145) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034E4 RW 0x016F_02CC
	UINT32 reg_peak2apl_lut_y13             :11;	//(10:0,RW,0x2CC) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x13             :11;	//(26:16,RW,0x16F) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034E8 RW 0x01A6_0266
	UINT32 reg_peak2apl_lut_y14             :11;	//(10:0,RW,0x266) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x14             :11;	//(26:16,RW,0x1A6) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034EC RW 0x01F4_0200
	UINT32 reg_peak2apl_lut_y15             :11;	//(10:0,RW,0x200) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x15             :11;	//(26:16,RW,0x1F4) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034F0 RW 0x03E8_00CC
	UINT32 reg_peak2apl_lut_y16             :11;	//(10:0,RW,0xCC) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x16             :11;	//(26:16,RW,0x3E8) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034F4 RW 0x04B0_003C
	UINT32 reg_peak2apl_lut_y17             :11;	//(10:0,RW,0x3C) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x17             :11;	//(26:16,RW,0x4B0) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034F8 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y18             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x18             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9034FC RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y19             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x19             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903500 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y20             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x20             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903504 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y21             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x21             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903508 RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y22             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x22             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90350C RW 0x0578_0000
	UINT32 reg_peak2apl_lut_y23             :11;	//(10:0,RW,0x0) //
	UINT32 resvd0                           :5;
	UINT32 reg_peak2apl_lut_x23             :11;	//(26:16,RW,0x578) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903510 RO 0x0000_0000
	UINT32 s_apl_val                        :8;	//(7:0,NA,0x0) //
	UINT32 resvd0                           :8;
	UINT32 s_apl_alpha                      :8;	//(23:16,NA,0x0) //
	UINT32 resvd1                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_68_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903514 RO 0x0000_0000
	UINT32 oled_apl_tcon                    :10;	//(9:0,RO,0x0) //
	UINT32 resvd0                           :6;
	UINT32 oled_apl_hdr                     :10;	//(25:16,RO,0x0) //
	UINT32 resvd1                           :2;
	UINT32 oled_apl_de                      :1;	//(28:28,RO,0x0) //
	UINT32 resvd2                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903518 RO 0x0000_0000
	UINT32 naive_apl_tcon_mux               :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_tcon                    :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90351C RO 0x0000_0000
	UINT32 naive_apl_hdr_mux                :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 filt_apl_hdr                     :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903520 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903524 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903528 RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90352C RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903530 RW 0x0000_0000
	UINT32 line_start_pos                   :16;	//(15:0,RW,0x0) //
	UINT32 sync_i_h_sel                     :1;	//(16:16,RW,0x0) //
	UINT32 sync_i_v_sel                     :1;	//(17:17,RW,0x0) //
	UINT32 sync_i_inv_ha                    :1;	//(18:18,RW,0x0) //
	UINT32 sync_i_inv_va                    :1;	//(19:19,RW,0x0) //
	UINT32 sync_o_sel_ha                    :1;	//(20:20,RW,0x0) //
	UINT32 sync_o_sel_va                    :1;	//(21:21,RW,0x0) //
	UINT32 sync_o_sel_hs                    :1;	//(22:22,RW,0x0) //
	UINT32 sync_o_sel_vs                    :1;	//(23:23,RW,0x0) //
	UINT32 tp_update_hv_zero                :1;	//(24:24,RW,0x0) //
	UINT32 force_out_ha                     :1;	//(25:25,RW,0x0) //
	UINT32 force_out_va                     :1;	//(26:26,RW,0x0) //
	UINT32 force_out_hs                     :1;	//(27:27,RW,0x0) //
	UINT32 manual_cnt_h_value_en            :1;	//(28:28,RW,0x0) //
	UINT32 manual_cnt_v_value_en            :1;	//(29:29,RW,0x0) //
	UINT32 force_out_vs                     :1;	//(30:30,RW,0x0) //
	UINT32 update_force                     :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903534 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903538 RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90353C RW 0x0002_8058
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x58) //
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_ha_seamless                  :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903540 RW 0x0002_8058
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x58) //
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //
	UINT32 reg_hs_seamless                  :1;	//(31:31,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903544 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903548 RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90354C RW 0x0000_0030
	UINT32 resvd0                           :4;
	UINT32 reg_ocpk_init_sel                :3;	//(6:4,RW,0x3) //0:out_vs_rising, 1:out_vs_falling, 2:out_va_rising, 3:out_va_falling, others:manual position from out_va_falling
	UINT32 resvd1                           :9;
	UINT32 reg_ocpk_manual_init_pos         :16;	//(31:16,RW,0x0) //line cnt after va_fl
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903550 RW 0x00000008
	UINT32 reg_144hz_packet_fc              :3;	//(2:0,RW,0x0) //144hz control packet (assign to vx1 ctrl packet[5:3])	Frame count 	???? ??? HTOTAL ?? ?????? frame??
	UINT32 reserved                         :1;	//(3:3,RW,0x1) //[3]:must be '1' (assign to vx1 ctrl packet[0])
	UINT32 reg_144hz_packet_md              :2;	//(5:4,RW,0x0) //144hz control packet (assign to vx1 ctrl packet[2:1])	144 mode	0:120hz(DE/HTOTAL=248/330)	1:144hz VRR (DE/HTOTAL=248/275)	2:120hz(DE/HTOTAL=240/330)	3:144hz VRR (DE/HTOTAL=240/275)
	UINT32 resvd                            :26;
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903554 RW 0x0000_0000
	UINT32 reg_pg_width                     :16;	//(15:0,RW,0x0) //
	UINT32 resvd0                           :4;
	UINT32 reg_pg_ramp_pat_en               :1;	//(20:20,RW,0x0) //
	UINT32 resvd1                           :1;
	UINT32 reg_pg_o_color_sel               :2;	//(23:22,RW,0x0) //
	UINT32 resvd2                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903558 RW 0x0000_0000
	UINT32 reg_use_delayed_de               :1;	//(0,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 reg_use_delayed_ha               :1;	//(1,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 reg_use_delayed_va               :1;	//(2,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 reg_use_delayed_hs               :1;	//(3,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 reg_use_delayed_vs               :1;	//(4,RW,0x0) //0:use own sync/active, 1:use delayed sync/active
	UINT32 resvd                            :27;
	};
}BE_O26A0_REG_OLED_ADDR_OLED_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903560 RO 0x0000_0000
	UINT32 pel_diff_v_th0_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_193_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903564 RO 0x0000_0000
	UINT32 pel_diff_v_th1_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_194_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903568 RO 0x0000_0000
	UINT32 pel_diff_v_th2_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_195_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90356C RO 0x0000_0000
	UINT32 pel_diff_v_th3_cnt               :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_196_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903570 RO 0x0000_0000
	UINT32 pel_out_v_th0_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_197_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903574 RO 0x0000_0000
	UINT32 pel_out_v_th1_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_198_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903578 RO 0x0000_0000
	UINT32 pel_out_v_th2_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_199_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90357C RO 0x0000_0000
	UINT32 pel_out_v_th3_cnt                :24;	//(23:0,RO,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_200_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903580 RO 0x0000_0000
	UINT32 pel_in_v_max                     :11;	//(10:0,RO,0x0) //
	UINT32 resvd0                           :5;
	UINT32 pel_out_v_max                    :11;	//(26:16,RO,0x0) //
	UINT32 resvd1                           :5;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_201_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903584 RW 0x0000_0000
	UINT32 reg_text_gain_en                 :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_text_luma_sel                :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 reg_text_lsr_en                  :1;	//(8:8,RW,0x0) //
	UINT32 reg_text_osd_en                  :1;	//(9:9,RW,0x0) //
	UINT32 resvd2                           :6;
	UINT32 reg_text_master_gain             :8;	//(23:16,RW,0x00) //
	UINT32 resvd3                           :8;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_202_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903588 RW 0x0000_0000
	UINT32 reg_region_gain_ctrl             :32;	//(31:0,RW,0x0000_0000) //for debugging
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_203_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90358C RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y00       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x00       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_204_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903590 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y01       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x01       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_205_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903594 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y02       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x02       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_206_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903598 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y03       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x03       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_207_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90359C RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y04       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x04       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_208_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035A0 RW 0x0000_0000
	UINT32 reg_text_luma_gain_lut_y05       :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_luma_gain_lut_x05       :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_209_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035A4 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y00        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x00        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_210_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035A8 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y01        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x01        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_211_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035AC RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y02        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x02        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_212_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035B0 RW 0x0000_0000
	UINT32 reg_text_sat_gain_lut_y03        :8;	//(7:0,RW,0x00) //
	UINT32 resvd0                           :8;
	UINT32 reg_text_sat_gain_lut_x03        :10;	//(25:16,RW,0x0000) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_213_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035B4 RW 0x0000_0000
	UINT32 reg_bst_alpha_blend_en           :1;	//(0:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_text_gain_dbg_en             :1;	//(4:4,RW,0x0) //1:text_gain out
	UINT32 resvd1                           :11;
	UINT32 reg_region_gain_en               :1;	//(16:16,RW,0x0) //
	UINT32 resvd2                           :7;
	UINT32 reg_region_gain_gain             :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_214_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035B8 RW 0x0000_0000
	UINT32 reg_region_gain_wid              :13;	//(12:0,RW,0x00) //
	UINT32 resvd                            :19;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_215_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035BC RW 0x0000_0000
	UINT32 reg_region_gain_hei              :13;	//(12:0,RW,0x0) //
	UINT32 resvd                            :19;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_216_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035C0 RW 0x0000_0000
	UINT32 reg_region_gain_ctrl             :32;	//(31:0,RW,0x0000_0000) //for debugging
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_217_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035C4 RW 0x0000_0000
	UINT32 reg_region_bnd_x0                :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_x1                :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_218_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035C8 RW 0x0000_0000
	UINT32 reg_region_bnd_y0                :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_bnd_y1                :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_219_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035CC RW 0x0000_0000
	UINT32 reg_region_position_x1           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x2           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_220_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035D0 RW 0x0000_0000
	UINT32 reg_region_position_x3           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x4           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_221_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035D4 RW 0x0000_0000
	UINT32 reg_region_position_x5           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x6           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_222_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035D8 RW 0x0000_0000
	UINT32 reg_region_position_x7           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_x8           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_223_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035DC RW 0x0000_0000
	UINT32 reg_region_position_y1           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y2           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_224_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035E0 RW 0x0000_0000
	UINT32 reg_region_position_y3           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y4           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_225_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035E4 RW 0x0000_0000
	UINT32 reg_region_position_y5           :13;	//(12:0,RW,0x0000) //
	UINT32 resvd0                           :3;
	UINT32 reg_region_position_y6           :13;	//(28:16,RW,0x0000) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_226_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035E8 RW 0x0000_0000
	UINT32 reg_region_gain_11               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_21               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_31               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_41               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_227_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035EC RW 0x0000_0000
	UINT32 reg_region_gain_51               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_61               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_71               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_81               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_228_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035F0 RW 0x0000_0000
	UINT32 reg_region_gain_12               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_22               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_32               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_42               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_229_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035F4 RW 0x0000_0000
	UINT32 reg_region_gain_52               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_62               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_72               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_82               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_230_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035F8 RW 0x0000_0000
	UINT32 reg_region_gain_13               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_23               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_33               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_43               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_231_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9035FC RW 0x0000_0000
	UINT32 reg_region_gain_53               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_63               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_73               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_83               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_232_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903600 RW 0x0000_0000
	UINT32 reg_region_gain_14               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_24               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_34               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_44               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_233_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903604 RW 0x0000_0000
	UINT32 reg_region_gain_54               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_64               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_74               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_84               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_234_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903608 RW 0x0000_0000
	UINT32 reg_region_gain_15               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_25               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_35               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_45               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_235_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90360C RW 0x0000_0000
	UINT32 reg_region_gain_55               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_65               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_75               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_85               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_236_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903610 RW 0x0000_0000
	UINT32 reg_region_gain_16               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_26               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_36               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_46               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_237_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903614 RW 0x0000_0000
	UINT32 reg_region_gain_56               :8;	//(7:0,RW,0x00) //
	UINT32 reg_region_gain_66               :8;	//(15:8,RW,0x00) //
	UINT32 reg_region_gain_76               :8;	//(23:16,RW,0x00) //
	UINT32 reg_region_gain_86               :8;	//(31:24,RW,0x00) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_238_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903618 RW 0x80808080
	UINT32 osd_adap_x3                      :8;	//(7:0,RW,0x80) //
	UINT32 osd_adap_x2                      :8;	//(15:8,RW,0x80) //
	UINT32 osd_adap_x1                      :8;	//(23:16,RW,0x80) //
	UINT32 osd_adap_x0                      :8;	//(31:24,RW,0x80) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_239_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90361C RW 0x80808080
	UINT32 osd_adap_y3                      :8;	//(7:0,RW,0x80) //
	UINT32 osd_adap_y2                      :8;	//(15:8,RW,0x80) //
	UINT32 osd_adap_y1                      :8;	//(23:16,RW,0x80) //
	UINT32 osd_adap_y0                      :8;	//(31:24,RW,0x80) //
	};
}BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_240_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036A0 RW 0x00000000
	UINT32 reg_wb2p_en                      :1;	//(0:0,RW,0x0) //
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036A4 RW 0x40004000
	UINT32 reg_wb2p_rgain                   :16;	//(15:0,RW,0x4000) //
	UINT32 reg_wb2p_ggain                   :16;	//(31:16,RW,0x4000) //
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036A8 RW 0x00004000
	UINT32 reg_wb2p_bgain                   :16;	//(15:0,RW,0x4000) //
	UINT32 reg_wb2p_roffset                 :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036AC RW 0x00000000
	UINT32 reg_wb2p_goffset                 :16;	//(15:0,RW,0x0) //
	UINT32 reg_wb2p_boffset                 :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036B0 RW 0x00000040
	UINT32 mcc_luma_lut_x1                  :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_x0                  :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036B4 RW 0x00800100
	UINT32 mcc_luma_lut_x3                  :10;	//(9:0,RW,0x100) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_x2                  :10;	//(25:16,RW,0x80) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036B8 RW 0x02000300
	UINT32 mcc_luma_lut_x5                  :10;	//(9:0,RW,0x300) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_x4                  :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036BC RW 0x038003ff
	UINT32 mcc_luma_lut_x7                  :10;	//(9:0,RW,0x3ff) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_x6                  :10;	//(25:16,RW,0x380) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036C0 RW 0x00000040
	UINT32 mcc_luma_lut_y1                  :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_y0                  :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036C4 RW 0x00800100
	UINT32 mcc_luma_lut_y3                  :10;	//(9:0,RW,0x100) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_y2                  :10;	//(25:16,RW,0x80) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036C8 RW 0x02000300
	UINT32 mcc_luma_lut_y5                  :10;	//(9:0,RW,0x300) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_y4                  :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036CC RW 0x038003ff
	UINT32 mcc_luma_lut_y7                  :10;	//(9:0,RW,0x3ff) //
	UINT32 resvd0                           :6;
	UINT32 mcc_luma_lut_y6                  :10;	//(25:16,RW,0x380) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036D0 RW 0x00000040
	UINT32 mcc_satu_lut_x1                  :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_x0                  :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036D4 RW 0x00800100
	UINT32 mcc_satu_lut_x3                  :10;	//(9:0,RW,0x100) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_x2                  :10;	//(25:16,RW,0x80) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036D8 RW 0x02000300
	UINT32 mcc_satu_lut_x5                  :10;	//(9:0,RW,0x300) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_x4                  :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036DC RW 0x038003ff
	UINT32 mcc_satu_lut_x7                  :10;	//(9:0,RW,0x3ff) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_x6                  :10;	//(25:16,RW,0x380) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036E0 RW 0x00000040
	UINT32 mcc_satu_lut_y1                  :10;	//(9:0,RW,0x40) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_y0                  :10;	//(25:16,RW,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036E4 RW 0x00800100
	UINT32 mcc_satu_lut_y3                  :10;	//(9:0,RW,0x100) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_y2                  :10;	//(25:16,RW,0x80) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036E8 RW 0x02000300
	UINT32 mcc_satu_lut_y5                  :10;	//(9:0,RW,0x300) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_y4                  :10;	//(25:16,RW,0x200) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC9036EC RW 0x038003ff
	UINT32 mcc_satu_lut_y7                  :10;	//(9:0,RW,0x3ff) //
	UINT32 resvd0                           :6;
	UINT32 mcc_satu_lut_y6                  :10;	//(25:16,RW,0x380) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_OLED_ADDR_MCC_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903700 RW 0x0000_0100
	UINT32 reg_dither_detour                :1;	//(0:0,RW,0) //1: dither top detour (input = output)
	UINT32 resvd0                           :7;
	UINT32 reg_col_fmt                      :1;	//(8:8,RW,0x1) //input color format 	0: yuv, 1:rgb
	UINT32 resvd1                           :23;
	};
}BE_O26A0_REG_OLED_REG_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903704 RW 0x0F00_0870
	UINT32 reg_dither_height                :16;	//(15:0,NA,0x870) //dither input image height
	UINT32 reg_dither_width                 :16;	//(31:16,RW,0xF00) //dither input image width
	};
}BE_O26A0_REG_OLED_REG_DITHER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903708 RW 0x00a0_9467
	UINT32 reg_err_diff_ker_dl              :5;	//(4:0,RW,7) //err_diff_ker input image dl
	UINT32 reg_err_diff_ker_ur              :5;	//(9:5,RW,3) //err_diff_ker input image ur
	UINT32 reg_err_diff_ker_um              :5;	//(14:10,RW,5) //err_diff_ker input image um
	UINT32 reg_err_diff_ker_ul              :5;	//(19:15,RW,1) //err_diff_ker input image ul
	UINT32 reg_err_th                       :4;	//(23:20,RW,10) //error diffusion threshold
	UINT32 reg_err_diff_debug_enable        :1;	//(24:24,RW,0x0) //error diffusion debug mode
	UINT32 resvd0                           :3;
	UINT32 reg_chroma_err_diable            :1;	//(28:28,RW,0) //chroma error diable 	1 : chroma ?? ??
	UINT32 resvd1                           :2;
	UINT32 reg_err_diff_en                  :1;	//(31:31,RW,0) //err_diff input image en	0 : core bypass 	1 : output = error diffusion result
	};
}BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90370C RW 0x0801_0040
	UINT32 reg_err_diff_out_y_wei_10b       :9;	//(8:0,RW,64) //
	UINT32 resvd0                           :1;
	UINT32 reg_err_diff_out_y_wei_9b        :9;	//(18:10,RW,64) //
	UINT32 resvd1                           :1;
	UINT32 reg_err_diff_out_y_wei_8b        :9;	//(28:20,RW,128) //
	UINT32 resvd2                           :3;
	};
}BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903710 RW 0x0801_0040
	UINT32 reg_err_diff_out_c_wei_10b       :9;	//(8:0,RW,64) //
	UINT32 resvd0                           :1;
	UINT32 reg_err_diff_out_c_wei_9b        :9;	//(18:10,RW,64) //
	UINT32 resvd1                           :1;
	UINT32 reg_err_diff_out_c_wei_8b        :9;	//(28:20,RW,128) //
	UINT32 resvd2                           :3;
	};
}BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903714 RW 0xf880_0880
	UINT32 resvd0                           :4;
	UINT32 reg_err_diff_debug_bg_cr         :4;	//(7:4,RW,8) //
	UINT32 reg_err_diff_debug_bg_cb         :4;	//(11:8,RW,8) //
	UINT32 reg_err_diff_debug_bg_yg         :4;	//(15:12,RW,0) //
	UINT32 resvd1                           :4;
	UINT32 reg_err_diff_debug_cr            :4;	//(23:20,RW,8) //
	UINT32 reg_err_diff_debug_cb            :4;	//(27:24,RW,8) //
	UINT32 reg_err_diff_debug_yg            :4;	//(31:28,RW,15) //
	};
}BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903718 RW 0x0400_0000
	UINT32 resvd0                           :24;
	UINT32 reg_1st_out_rd_bit               :4;	//(27:24,RW,4) //1st_out_rd input image bit
	UINT32 resvd1                           :3;
	UINT32 reg_1st_out_rd_on                :1;	//(31:31,RW,0) //1st_out_rd input image on	0 : core bypass 	1 : output = random diffusion result
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90371C RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :13;	//(12:0,RW,0x0) //1st_out_rd_min_pel input image cb
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_min_pel_yy        :13;	//(28:16,RW,0x0) //1st_out_rd_min_pel input image yy
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903720 RW 0x0000_0fff
	UINT32 reg_1st_out_rd_max_pel_yy        :13;	//(12:0,RW,4095) //1st_out_rd_max_pel input image yy
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_min_pel_cr        :13;	//(28:16,RW,0x0) //1st_out_rd_min_pel input image cr
	UINT32 resvd1                           :2;
	UINT32 reg_init_rst_off                 :1;	//(31:31,RW,0x0) //1 : pic_init reset(initial register) off_x000D_	0: normal mode
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903724 RW 0x0fff_0fff
	UINT32 reg_1st_out_rd_max_pel_cr        :13;	//(12:0,RW,4095) //1st_out_rd_max_pel input image cr
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_max_pel_cb        :13;	//(28:16,RW,4095) //1st_out_rd_max_pel input image cb
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903728 RW 0x1357_9753
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,324507475) //1st_out_rd_init input image yy
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90372C RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,610797668) //1st_out_rd_init input image cb
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903730 RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,610797668) //1st_out_rd_init input image cr
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903734 RW 0x1200_0030
	UINT32 resvd0                           :4;
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd1                           :8;
	UINT32 reg_rd_roi_en                    :1;	//(16:16,NA,0x0) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_rd_luma_cut              :2;	//(21:20,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd3                           :2;
	UINT32 reg_1st_rd_luma_cut              :2;	//(25:24,NA,2) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd4                           :2;
	UINT32 reg_1st_rd_luma_en               :1;	//(28:28,NA,1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 resvd5                           :3;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903738 RW 0x005b_01b0
	UINT32 reg_rd_roi_x1                    :14;	//(13:0,NA,0x1B0) //rd_roi input image x1
	UINT32 resvd0                           :2;
	UINT32 reg_rd_roi_x0                    :14;	//(29:16,NA,0x5B) //rd_roi input image x0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90373C RW 0x006a_01b0
	UINT32 reg_rd_roi_y1                    :14;	//(13:0,NA,0x1B0) //rd_roi input image y1
	UINT32 resvd0                           :2;
	UINT32 reg_rd_roi_y0                    :14;	//(29:16,NA,0x6A) //rd_roi input image y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903740 RW 0x0000_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //1st_rd_luma input image x1
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //1st_rd_luma input image x0
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903744 RW 0x0000_a032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //1st_rd_luma input image x3
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //1st_rd_luma input image x2
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903748 RW 0x0003_c046
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //1st_rd_luma input image x5
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //1st_rd_luma input image x4
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90374C RW 0x0006_40c8
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //1st_rd_luma input image x7
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //1st_rd_luma input image x6
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903750 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //1st_rd_luma input image y1
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //1st_rd_luma input image y0
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903754 RW 0x0000_400a
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //1st_rd_luma input image y3
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //1st_rd_luma input image y2
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC903758 RW 0x0003_2064
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //1st_rd_luma input image y5
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //1st_rd_luma input image y4
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC90375C RW 0x000c_83ff
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //1st_rd_luma input image y7
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //1st_rd_luma input image y6
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_17_T;

typedef struct {
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_00_T                      addr_oled_ctrl_00;	//0xCC903000
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_01_T                      addr_oled_ctrl_01;	//0xCC903004
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_02_T                      addr_oled_ctrl_02;	//0xCC903008
	UINT32                                                    reserved0;	//0xCC90300C
	BE_O26A0_REG_OLED_ADDR_FSW_CTRL_00_T                        addr_fsw_ctrl_00;	//0xCC903010
	BE_O26A0_REG_OLED_ADDR_FSW_CTRL_01_T                        addr_fsw_ctrl_01;	//0xCC903014
	BE_O26A0_REG_OLED_ADDR_FSW_CTRL_02_T                        addr_fsw_ctrl_02;	//0xCC903018
	BE_O26A0_REG_OLED_ADDR_FSW_CTRL_03_T                        addr_fsw_ctrl_03;	//0xCC90301C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_00_T                        addr_cpc_ctrl_00;	//0xCC903020
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_01_T                        addr_cpc_ctrl_01;	//0xCC903024
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_02_T                        addr_cpc_ctrl_02;	//0xCC903028
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_03_T                        addr_cpc_ctrl_03;	//0xCC90302C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_04_T                        addr_cpc_ctrl_04;	//0xCC903030
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_05_T                        addr_cpc_ctrl_05;	//0xCC903034
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_06_T                        addr_cpc_ctrl_06;	//0xCC903038
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_07_T                        addr_cpc_ctrl_07;	//0xCC90303C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_08_T                        addr_cpc_ctrl_08;	//0xCC903040
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_09_T                        addr_cpc_ctrl_09;	//0xCC903044
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_10_T                        addr_cpc_ctrl_10;	//0xCC903048
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_11_T                        addr_cpc_ctrl_11;	//0xCC90304C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_12_T                        addr_cpc_ctrl_12;	//0xCC903050
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_13_T                        addr_cpc_ctrl_13;	//0xCC903054
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_14_T                        addr_cpc_ctrl_14;	//0xCC903058
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_15_T                        addr_cpc_ctrl_15;	//0xCC90305C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_16_T                        addr_cpc_ctrl_16;	//0xCC903060
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_17_T                        addr_cpc_ctrl_17;	//0xCC903064
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_18_T                        addr_cpc_ctrl_18;	//0xCC903068
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_19_T                        addr_cpc_ctrl_19;	//0xCC90306C
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_20_T                        addr_cpc_ctrl_20;	//0xCC903070
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_21_T                        addr_cpc_ctrl_21;	//0xCC903074
	BE_O26A0_REG_OLED_ADDR_CPC_CTRL_22_T                        addr_cpc_ctrl_22;	//0xCC903078
	UINT32                                                    reserved1;	//0xCC90307C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_000_T                    addr_phdr_ctrl_000;	//0xCC903080
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_001_T                    addr_phdr_ctrl_001;	//0xCC903084
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_002_T                    addr_phdr_ctrl_002;	//0xCC903088
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_003_T                    addr_phdr_ctrl_003;	//0xCC90308C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_004_T                    addr_phdr_ctrl_004;	//0xCC903090
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_005_T                    addr_phdr_ctrl_005;	//0xCC903094
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_006_T                    addr_phdr_ctrl_006;	//0xCC903098
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_007_T                    addr_phdr_ctrl_007;	//0xCC90309C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_008_T                    addr_phdr_ctrl_008;	//0xCC9030A0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_009_T                    addr_phdr_ctrl_009;	//0xCC9030A4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_010_T                    addr_phdr_ctrl_010;	//0xCC9030A8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_011_T                    addr_phdr_ctrl_011;	//0xCC9030AC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_012_T                    addr_phdr_ctrl_012;	//0xCC9030B0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_013_T                    addr_phdr_ctrl_013;	//0xCC9030B4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_014_T                    addr_phdr_ctrl_014;	//0xCC9030B8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_015_T                    addr_phdr_ctrl_015;	//0xCC9030BC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_016_T                    addr_phdr_ctrl_016;	//0xCC9030C0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_017_T                    addr_phdr_ctrl_017;	//0xCC9030C4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_018_T                    addr_phdr_ctrl_018;	//0xCC9030C8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_019_T                    addr_phdr_ctrl_019;	//0xCC9030CC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_020_T                    addr_phdr_ctrl_020;	//0xCC9030D0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_021_T                    addr_phdr_ctrl_021;	//0xCC9030D4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_022_T                    addr_phdr_ctrl_022;	//0xCC9030D8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_023_T                    addr_phdr_ctrl_023;	//0xCC9030DC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_024_T                    addr_phdr_ctrl_024;	//0xCC9030E0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_025_T                    addr_phdr_ctrl_025;	//0xCC9030E4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_026_T                    addr_phdr_ctrl_026;	//0xCC9030E8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_027_T                    addr_phdr_ctrl_027;	//0xCC9030EC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_028_T                    addr_phdr_ctrl_028;	//0xCC9030F0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_029_T                    addr_phdr_ctrl_029;	//0xCC9030F4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_030_T                    addr_phdr_ctrl_030;	//0xCC9030F8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_031_T                    addr_phdr_ctrl_031;	//0xCC9030FC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_032_T                    addr_phdr_ctrl_032;	//0xCC903100
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_033_T                    addr_phdr_ctrl_033;	//0xCC903104
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_034_T                    addr_phdr_ctrl_034;	//0xCC903108
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_035_T                    addr_phdr_ctrl_035;	//0xCC90310C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_036_T                    addr_phdr_ctrl_036;	//0xCC903110
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_037_T                    addr_phdr_ctrl_037;	//0xCC903114
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_038_T                    addr_phdr_ctrl_038;	//0xCC903118
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_039_T                    addr_phdr_ctrl_039;	//0xCC90311C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_040_T                    addr_phdr_ctrl_040;	//0xCC903120
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_041_T                    addr_phdr_ctrl_041;	//0xCC903124
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_042_T                    addr_phdr_ctrl_042;	//0xCC903128
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_043_T                    addr_phdr_ctrl_043;	//0xCC90312C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_044_T                    addr_phdr_ctrl_044;	//0xCC903130
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_045_T                    addr_phdr_ctrl_045;	//0xCC903134
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_046_T                    addr_phdr_ctrl_046;	//0xCC903138
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_047_T                    addr_phdr_ctrl_047;	//0xCC90313C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_048_T                    addr_phdr_ctrl_048;	//0xCC903140
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_049_T                    addr_phdr_ctrl_049;	//0xCC903144
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_050_T                    addr_phdr_ctrl_050;	//0xCC903148
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_051_T                    addr_phdr_ctrl_051;	//0xCC90314C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_052_T                    addr_phdr_ctrl_052;	//0xCC903150
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_053_T                    addr_phdr_ctrl_053;	//0xCC903154
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_054_T                    addr_phdr_ctrl_054;	//0xCC903158
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_055_T                    addr_phdr_ctrl_055;	//0xCC90315C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_056_T                    addr_phdr_ctrl_056;	//0xCC903160
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_057_T                    addr_phdr_ctrl_057;	//0xCC903164
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_058_T                    addr_phdr_ctrl_058;	//0xCC903168
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_059_T                    addr_phdr_ctrl_059;	//0xCC90316C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_060_T                    addr_phdr_ctrl_060;	//0xCC903170
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_061_T                    addr_phdr_ctrl_061;	//0xCC903174
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_062_T                    addr_phdr_ctrl_062;	//0xCC903178
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_063_T                    addr_phdr_ctrl_063;	//0xCC90317C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_064_T                    addr_phdr_ctrl_064;	//0xCC903180
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_065_T                    addr_phdr_ctrl_065;	//0xCC903184
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_066_T                    addr_phdr_ctrl_066;	//0xCC903188
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_067_T                    addr_phdr_ctrl_067;	//0xCC90318C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_068_T                    addr_phdr_ctrl_068;	//0xCC903190
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_069_T                    addr_phdr_ctrl_069;	//0xCC903194
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_070_T                    addr_phdr_ctrl_070;	//0xCC903198
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_071_T                    addr_phdr_ctrl_071;	//0xCC90319C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_072_T                    addr_phdr_ctrl_072;	//0xCC9031A0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_073_T                    addr_phdr_ctrl_073;	//0xCC9031A4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_074_T                    addr_phdr_ctrl_074;	//0xCC9031A8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_075_T                    addr_phdr_ctrl_075;	//0xCC9031AC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_076_T                    addr_phdr_ctrl_076;	//0xCC9031B0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_077_T                    addr_phdr_ctrl_077;	//0xCC9031B4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_078_T                    addr_phdr_ctrl_078;	//0xCC9031B8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_079_T                    addr_phdr_ctrl_079;	//0xCC9031BC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_080_T                    addr_phdr_ctrl_080;	//0xCC9031C0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_081_T                    addr_phdr_ctrl_081;	//0xCC9031C4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_082_T                    addr_phdr_ctrl_082;	//0xCC9031C8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_083_T                    addr_phdr_ctrl_083;	//0xCC9031CC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_084_T                    addr_phdr_ctrl_084;	//0xCC9031D0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_085_T                    addr_phdr_ctrl_085;	//0xCC9031D4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_086_T                    addr_phdr_ctrl_086;	//0xCC9031D8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_087_T                    addr_phdr_ctrl_087;	//0xCC9031DC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_088_T                    addr_phdr_ctrl_088;	//0xCC9031E0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_089_T                    addr_phdr_ctrl_089;	//0xCC9031E4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_090_T                    addr_phdr_ctrl_090;	//0xCC9031E8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_091_T                    addr_phdr_ctrl_091;	//0xCC9031EC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_092_T                    addr_phdr_ctrl_092;	//0xCC9031F0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_093_T                    addr_phdr_ctrl_093;	//0xCC9031F4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_094_T                    addr_phdr_ctrl_094;	//0xCC9031F8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_095_T                    addr_phdr_ctrl_095;	//0xCC9031FC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_096_T                    addr_phdr_ctrl_096;	//0xCC903200
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_097_T                    addr_phdr_ctrl_097;	//0xCC903204
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_098_T                    addr_phdr_ctrl_098;	//0xCC903208
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_099_T                    addr_phdr_ctrl_099;	//0xCC90320C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_100_T                    addr_phdr_ctrl_100;	//0xCC903210
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_101_T                    addr_phdr_ctrl_101;	//0xCC903214
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_102_T                    addr_phdr_ctrl_102;	//0xCC903218
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_103_T                    addr_phdr_ctrl_103;	//0xCC90321C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_104_T                    addr_phdr_ctrl_104;	//0xCC903220
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_105_T                    addr_phdr_ctrl_105;	//0xCC903224
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_106_T                    addr_phdr_ctrl_106;	//0xCC903228
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_107_T                    addr_phdr_ctrl_107;	//0xCC90322C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_108_T                    addr_phdr_ctrl_108;	//0xCC903230
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_109_T                    addr_phdr_ctrl_109;	//0xCC903234
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_110_T                    addr_phdr_ctrl_110;	//0xCC903238
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_111_T                    addr_phdr_ctrl_111;	//0xCC90323C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_112_T                    addr_phdr_ctrl_112;	//0xCC903240
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_113_T                    addr_phdr_ctrl_113;	//0xCC903244
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_114_T                    addr_phdr_ctrl_114;	//0xCC903248
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_115_T                    addr_phdr_ctrl_115;	//0xCC90324C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_116_T                    addr_phdr_ctrl_116;	//0xCC903250
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_117_T                    addr_phdr_ctrl_117;	//0xCC903254
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_118_T                    addr_phdr_ctrl_118;	//0xCC903258
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_119_T                    addr_phdr_ctrl_119;	//0xCC90325C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_120_T                    addr_phdr_ctrl_120;	//0xCC903260
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_121_T                    addr_phdr_ctrl_121;	//0xCC903264
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_122_T                    addr_phdr_ctrl_122;	//0xCC903268
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_123_T                    addr_phdr_ctrl_123;	//0xCC90326C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_124_T                    addr_phdr_ctrl_124;	//0xCC903270
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_125_T                    addr_phdr_ctrl_125;	//0xCC903274
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_126_T                    addr_phdr_ctrl_126;	//0xCC903278
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_127_T                    addr_phdr_ctrl_127;	//0xCC90327C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_128_T                    addr_phdr_ctrl_128;	//0xCC903280
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_129_T                    addr_phdr_ctrl_129;	//0xCC903284
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_130_T                    addr_phdr_ctrl_130;	//0xCC903288
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_131_T                    addr_phdr_ctrl_131;	//0xCC90328C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_132_T                    addr_phdr_ctrl_132;	//0xCC903290
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_133_T                    addr_phdr_ctrl_133;	//0xCC903294
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_134_T                    addr_phdr_ctrl_134;	//0xCC903298
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_135_T                    addr_phdr_ctrl_135;	//0xCC90329C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_136_T                    addr_phdr_ctrl_136;	//0xCC9032A0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_137_T                    addr_phdr_ctrl_137;	//0xCC9032A4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_138_T                    addr_phdr_ctrl_138;	//0xCC9032A8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_139_T                    addr_phdr_ctrl_139;	//0xCC9032AC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_140_T                    addr_phdr_ctrl_140;	//0xCC9032B0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_141_T                    addr_phdr_ctrl_141;	//0xCC9032B4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_142_T                    addr_phdr_ctrl_142;	//0xCC9032B8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_143_T                    addr_phdr_ctrl_143;	//0xCC9032BC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_144_T                    addr_phdr_ctrl_144;	//0xCC9032C0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_145_T                    addr_phdr_ctrl_145;	//0xCC9032C4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_146_T                    addr_phdr_ctrl_146;	//0xCC9032C8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_147_T                    addr_phdr_ctrl_147;	//0xCC9032CC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_148_T                    addr_phdr_ctrl_148;	//0xCC9032D0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_149_T                    addr_phdr_ctrl_149;	//0xCC9032D4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_150_T                    addr_phdr_ctrl_150;	//0xCC9032D8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_151_T                    addr_phdr_ctrl_151;	//0xCC9032DC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_152_T                    addr_phdr_ctrl_152;	//0xCC9032E0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_153_T                    addr_phdr_ctrl_153;	//0xCC9032E4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_154_T                    addr_phdr_ctrl_154;	//0xCC9032E8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_155_T                    addr_phdr_ctrl_155;	//0xCC9032EC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_156_T                    addr_phdr_ctrl_156;	//0xCC9032F0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_157_T                    addr_phdr_ctrl_157;	//0xCC9032F4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_158_T                    addr_phdr_ctrl_158;	//0xCC9032F8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_159_T                    addr_phdr_ctrl_159;	//0xCC9032FC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_160_T                    addr_phdr_ctrl_160;	//0xCC903300
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_161_T                    addr_phdr_ctrl_161;	//0xCC903304
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_162_T                    addr_phdr_ctrl_162;	//0xCC903308
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_163_T                    addr_phdr_ctrl_163;	//0xCC90330C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_164_T                    addr_phdr_ctrl_164;	//0xCC903310
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_165_T                    addr_phdr_ctrl_165;	//0xCC903314
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_166_T                    addr_phdr_ctrl_166;	//0xCC903318
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_167_T                    addr_phdr_ctrl_167;	//0xCC90331C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_168_T                    addr_phdr_ctrl_168;	//0xCC903320
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_169_T                    addr_phdr_ctrl_169;	//0xCC903324
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_170_T                    addr_phdr_ctrl_170;	//0xCC903328
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_171_T                    addr_phdr_ctrl_171;	//0xCC90332C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_172_T                    addr_phdr_ctrl_172;	//0xCC903330
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_173_T                    addr_phdr_ctrl_173;	//0xCC903334
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_174_T                    addr_phdr_ctrl_174;	//0xCC903338
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_175_T                    addr_phdr_ctrl_175;	//0xCC90333C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_176_T                    addr_phdr_ctrl_176;	//0xCC903340
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_177_T                    addr_phdr_ctrl_177;	//0xCC903344
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_178_T                    addr_phdr_ctrl_178;	//0xCC903348
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_179_T                    addr_phdr_ctrl_179;	//0xCC90334C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_180_T                    addr_phdr_ctrl_180;	//0xCC903350
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_181_T                    addr_phdr_ctrl_181;	//0xCC903354
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_182_T                    addr_phdr_ctrl_182;	//0xCC903358
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_183_T                    addr_phdr_ctrl_183;	//0xCC90335C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_184_T                    addr_phdr_ctrl_184;	//0xCC903360
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_185_T                    addr_phdr_ctrl_185;	//0xCC903364
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_186_T                    addr_phdr_ctrl_186;	//0xCC903368
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_187_T                    addr_phdr_ctrl_187;	//0xCC90336C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_188_T                    addr_phdr_ctrl_188;	//0xCC903370
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_189_T                    addr_phdr_ctrl_189;	//0xCC903374
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_190_T                    addr_phdr_ctrl_190;	//0xCC903378
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_191_T                    addr_phdr_ctrl_191;	//0xCC90337C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_192_T                    addr_phdr_ctrl_192;	//0xCC903380
	UINT32                                                    reserved2;	//0xCC903384
	UINT32                                                    reserved3;	//0xCC903388
	UINT32                                                    reserved4;	//0xCC90338C
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_00_T                  addr_rgb2yc_ctrl_00;	//0xCC903390
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_01_T                  addr_rgb2yc_ctrl_01;	//0xCC903394
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_02_T                  addr_rgb2yc_ctrl_02;	//0xCC903398
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_03_T                  addr_rgb2yc_ctrl_03;	//0xCC90339C
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_04_T                  addr_rgb2yc_ctrl_04;	//0xCC9033A0
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_05_T                  addr_rgb2yc_ctrl_05;	//0xCC9033A4
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_06_T                  addr_rgb2yc_ctrl_06;	//0xCC9033A8
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_07_T                  addr_rgb2yc_ctrl_07;	//0xCC9033AC
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_08_T                  addr_rgb2yc_ctrl_08;	//0xCC9033B0
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_09_T                  addr_rgb2yc_ctrl_09;	//0xCC9033B4
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_10_T                  addr_rgb2yc_ctrl_10;	//0xCC9033B8
	BE_O26A0_REG_OLED_ADDR_RGB2YC_CTRL_11_T                  addr_rgb2yc_ctrl_11;	//0xCC9033BC
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_00_T                  addr_yc2rgb_ctrl_00;	//0xCC9033C0
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_01_T                  addr_yc2rgb_ctrl_01;	//0xCC9033C4
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_02_T                  addr_yc2rgb_ctrl_02;	//0xCC9033C8
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_03_T                  addr_yc2rgb_ctrl_03;	//0xCC9033CC
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_04_T                  addr_yc2rgb_ctrl_04;	//0xCC9033D0
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_05_T                  addr_yc2rgb_ctrl_05;	//0xCC9033D4
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_06_T                  addr_yc2rgb_ctrl_06;	//0xCC9033D8
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_07_T                  addr_yc2rgb_ctrl_07;	//0xCC9033DC
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_08_T                  addr_yc2rgb_ctrl_08;	//0xCC9033E0
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_09_T                  addr_yc2rgb_ctrl_09;	//0xCC9033E4
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_10_T                  addr_yc2rgb_ctrl_10;	//0xCC9033E8
	BE_O26A0_REG_OLED_ADDR_YC2RGB_CTRL_11_T                  addr_yc2rgb_ctrl_11;	//0xCC9033EC
	UINT32                                                    reserved5;	//0xCC9033F0
	UINT32                                                    reserved6;	//0xCC9033F4
	UINT32                                                    reserved7;	//0xCC9033F8
	UINT32                                                    reserved8;	//0xCC9033FC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_00_T                      addr_oapl_ctrl_00;	//0xCC903400
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_01_T                      addr_oapl_ctrl_01;	//0xCC903404
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_02_T                      addr_oapl_ctrl_02;	//0xCC903408
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_03_T                      addr_oapl_ctrl_03;	//0xCC90340C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_04_T                      addr_oapl_ctrl_04;	//0xCC903410
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_05_T                      addr_oapl_ctrl_05;	//0xCC903414
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_06_T                      addr_oapl_ctrl_06;	//0xCC903418
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_07_T                      addr_oapl_ctrl_07;	//0xCC90341C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_08_T                      addr_oapl_ctrl_08;	//0xCC903420
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_09_T                      addr_oapl_ctrl_09;	//0xCC903424
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_10_T                      addr_oapl_ctrl_10;	//0xCC903428
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_11_T                      addr_oapl_ctrl_11;	//0xCC90342C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_12_T                      addr_oapl_ctrl_12;	//0xCC903430
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_13_T                      addr_oapl_ctrl_13;	//0xCC903434
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_14_T                      addr_oapl_ctrl_14;	//0xCC903438
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_15_T                      addr_oapl_ctrl_15;	//0xCC90343C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_16_T                      addr_oapl_ctrl_16;	//0xCC903440
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_17_T                      addr_oapl_ctrl_17;	//0xCC903444
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_18_T                      addr_oapl_ctrl_18;	//0xCC903448
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_19_T                      addr_oapl_ctrl_19;	//0xCC90344C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_20_T                      addr_oapl_ctrl_20;	//0xCC903450
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_21_T                      addr_oapl_ctrl_21;	//0xCC903454
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_22_T                      addr_oapl_ctrl_22;	//0xCC903458
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_23_T                      addr_oapl_ctrl_23;	//0xCC90345C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_24_T                      addr_oapl_ctrl_24;	//0xCC903460
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_25_T                      addr_oapl_ctrl_25;	//0xCC903464
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_26_T                      addr_oapl_ctrl_26;	//0xCC903468
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_27_T                      addr_oapl_ctrl_27;	//0xCC90346C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_28_T                      addr_oapl_ctrl_28;	//0xCC903470
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_29_T                      addr_oapl_ctrl_29;	//0xCC903474
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_30_T                      addr_oapl_ctrl_30;	//0xCC903478
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_31_T                      addr_oapl_ctrl_31;	//0xCC90347C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_32_T                      addr_oapl_ctrl_32;	//0xCC903480
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_33_T                      addr_oapl_ctrl_33;	//0xCC903484
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_34_T                      addr_oapl_ctrl_34;	//0xCC903488
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_35_T                      addr_oapl_ctrl_35;	//0xCC90348C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_36_T                      addr_oapl_ctrl_36;	//0xCC903490
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_37_T                      addr_oapl_ctrl_37;	//0xCC903494
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_38_T                      addr_oapl_ctrl_38;	//0xCC903498
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_39_T                      addr_oapl_ctrl_39;	//0xCC90349C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_40_T                      addr_oapl_ctrl_40;	//0xCC9034A0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_41_T                      addr_oapl_ctrl_41;	//0xCC9034A4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_42_T                      addr_oapl_ctrl_42;	//0xCC9034A8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_43_T                      addr_oapl_ctrl_43;	//0xCC9034AC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_44_T                      addr_oapl_ctrl_44;	//0xCC9034B0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_45_T                      addr_oapl_ctrl_45;	//0xCC9034B4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_46_T                      addr_oapl_ctrl_46;	//0xCC9034B8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_47_T                      addr_oapl_ctrl_47;	//0xCC9034BC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_48_T                      addr_oapl_ctrl_48;	//0xCC9034C0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_49_T                      addr_oapl_ctrl_49;	//0xCC9034C4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_50_T                      addr_oapl_ctrl_50;	//0xCC9034C8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_51_T                      addr_oapl_ctrl_51;	//0xCC9034CC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_52_T                      addr_oapl_ctrl_52;	//0xCC9034D0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_53_T                      addr_oapl_ctrl_53;	//0xCC9034D4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_54_T                      addr_oapl_ctrl_54;	//0xCC9034D8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_55_T                      addr_oapl_ctrl_55;	//0xCC9034DC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_56_T                      addr_oapl_ctrl_56;	//0xCC9034E0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_57_T                      addr_oapl_ctrl_57;	//0xCC9034E4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_58_T                      addr_oapl_ctrl_58;	//0xCC9034E8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_59_T                      addr_oapl_ctrl_59;	//0xCC9034EC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_60_T                      addr_oapl_ctrl_60;	//0xCC9034F0
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_61_T                      addr_oapl_ctrl_61;	//0xCC9034F4
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_62_T                      addr_oapl_ctrl_62;	//0xCC9034F8
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_63_T                      addr_oapl_ctrl_63;	//0xCC9034FC
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_64_T                      addr_oapl_ctrl_64;	//0xCC903500
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_65_T                      addr_oapl_ctrl_65;	//0xCC903504
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_66_T                      addr_oapl_ctrl_66;	//0xCC903508
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_67_T                      addr_oapl_ctrl_67;	//0xCC90350C
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_68_T                      addr_oapl_ctrl_68;	//0xCC903510
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_69_T                      addr_oapl_ctrl_69;	//0xCC903514
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_70_T                      addr_oapl_ctrl_70;	//0xCC903518
	BE_O26A0_REG_OLED_ADDR_OAPL_CTRL_71_T                      addr_oapl_ctrl_71;	//0xCC90351C
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_03_T                      addr_oled_ctrl_03;	//0xCC903520
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_04_T                      addr_oled_ctrl_04;	//0xCC903524
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_05_T                      addr_oled_ctrl_05;	//0xCC903528
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_06_T                      addr_oled_ctrl_06;	//0xCC90352C
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_07_T                      addr_oled_ctrl_07;	//0xCC903530
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_08_T                      addr_oled_ctrl_08;	//0xCC903534
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_09_T                      addr_oled_ctrl_09;	//0xCC903538
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_10_T                      addr_oled_ctrl_10;	//0xCC90353C
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_11_T                      addr_oled_ctrl_11;	//0xCC903540
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_12_T                      addr_oled_ctrl_12;	//0xCC903544
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_13_T                      addr_oled_ctrl_13;	//0xCC903548
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_14_T                      addr_oled_ctrl_14;	//0xCC90354C
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_15_T                      addr_oled_ctrl_15;	//0xCC903550
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_16_T                      addr_oled_ctrl_16;	//0xCC903554
	BE_O26A0_REG_OLED_ADDR_OLED_CTRL_17_T                      addr_oled_ctrl_17;	//0xCC903558
	UINT32                                                    reserved9;	//0xCC90355C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_193_T                    addr_phdr_ctrl_193;	//0xCC903560
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_194_T                    addr_phdr_ctrl_194;	//0xCC903564
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_195_T                    addr_phdr_ctrl_195;	//0xCC903568
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_196_T                    addr_phdr_ctrl_196;	//0xCC90356C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_197_T                    addr_phdr_ctrl_197;	//0xCC903570
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_198_T                    addr_phdr_ctrl_198;	//0xCC903574
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_199_T                    addr_phdr_ctrl_199;	//0xCC903578
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_200_T                    addr_phdr_ctrl_200;	//0xCC90357C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_201_T                    addr_phdr_ctrl_201;	//0xCC903580
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_202_T                    addr_phdr_ctrl_202;	//0xCC903584
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_203_T                    addr_phdr_ctrl_203;	//0xCC903588
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_204_T                    addr_phdr_ctrl_204;	//0xCC90358C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_205_T                    addr_phdr_ctrl_205;	//0xCC903590
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_206_T                    addr_phdr_ctrl_206;	//0xCC903594
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_207_T                    addr_phdr_ctrl_207;	//0xCC903598
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_208_T                    addr_phdr_ctrl_208;	//0xCC90359C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_209_T                    addr_phdr_ctrl_209;	//0xCC9035A0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_210_T                    addr_phdr_ctrl_210;	//0xCC9035A4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_211_T                    addr_phdr_ctrl_211;	//0xCC9035A8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_212_T                    addr_phdr_ctrl_212;	//0xCC9035AC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_213_T                    addr_phdr_ctrl_213;	//0xCC9035B0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_214_T                    addr_phdr_ctrl_214;	//0xCC9035B4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_215_T                    addr_phdr_ctrl_215;	//0xCC9035B8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_216_T                    addr_phdr_ctrl_216;	//0xCC9035BC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_217_T                    addr_phdr_ctrl_217;	//0xCC9035C0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_218_T                    addr_phdr_ctrl_218;	//0xCC9035C4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_219_T                    addr_phdr_ctrl_219;	//0xCC9035C8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_220_T                    addr_phdr_ctrl_220;	//0xCC9035CC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_221_T                    addr_phdr_ctrl_221;	//0xCC9035D0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_222_T                    addr_phdr_ctrl_222;	//0xCC9035D4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_223_T                    addr_phdr_ctrl_223;	//0xCC9035D8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_224_T                    addr_phdr_ctrl_224;	//0xCC9035DC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_225_T                    addr_phdr_ctrl_225;	//0xCC9035E0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_226_T                    addr_phdr_ctrl_226;	//0xCC9035E4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_227_T                    addr_phdr_ctrl_227;	//0xCC9035E8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_228_T                    addr_phdr_ctrl_228;	//0xCC9035EC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_229_T                    addr_phdr_ctrl_229;	//0xCC9035F0
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_230_T                    addr_phdr_ctrl_230;	//0xCC9035F4
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_231_T                    addr_phdr_ctrl_231;	//0xCC9035F8
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_232_T                    addr_phdr_ctrl_232;	//0xCC9035FC
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_233_T                    addr_phdr_ctrl_233;	//0xCC903600
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_234_T                    addr_phdr_ctrl_234;	//0xCC903604
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_235_T                    addr_phdr_ctrl_235;	//0xCC903608
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_236_T                    addr_phdr_ctrl_236;	//0xCC90360C
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_237_T                    addr_phdr_ctrl_237;	//0xCC903610
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_238_T                    addr_phdr_ctrl_238;	//0xCC903614
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_239_T                    addr_phdr_ctrl_239;	//0xCC903618
	BE_O26A0_REG_OLED_ADDR_PHDR_CTRL_240_T                    addr_phdr_ctrl_240;	//0xCC90361C
	UINT32                                                   reserved10;	//0xCC903620
	UINT32                                                   reserved11;	//0xCC903624
	UINT32                                                   reserved12;	//0xCC903628
	UINT32                                                   reserved13;	//0xCC90362C
	UINT32                                                   reserved14;	//0xCC903630
	UINT32                                                   reserved15;	//0xCC903634
	UINT32                                                   reserved16;	//0xCC903638
	UINT32                                                   reserved17;	//0xCC90363C
	UINT32                                                   reserved18;	//0xCC903640
	UINT32                                                   reserved19;	//0xCC903644
	UINT32                                                   reserved20;	//0xCC903648
	UINT32                                                   reserved21;	//0xCC90364C
	UINT32                                                   reserved22;	//0xCC903650
	UINT32                                                   reserved23;	//0xCC903654
	UINT32                                                   reserved24;	//0xCC903658
	UINT32                                                   reserved25;	//0xCC90365C
	UINT32                                                   reserved26;	//0xCC903660
	UINT32                                                   reserved27;	//0xCC903664
	UINT32                                                   reserved28;	//0xCC903668
	UINT32                                                   reserved29;	//0xCC90366C
	UINT32                                                   reserved30;	//0xCC903670
	UINT32                                                   reserved31;	//0xCC903674
	UINT32                                                   reserved32;	//0xCC903678
	UINT32                                                   reserved33;	//0xCC90367C
	UINT32                                                   reserved34;	//0xCC903680
	UINT32                                                   reserved35;	//0xCC903684
	UINT32                                                   reserved36;	//0xCC903688
	UINT32                                                   reserved37;	//0xCC90368C
	UINT32                                                   reserved38;	//0xCC903690
	UINT32                                                   reserved39;	//0xCC903694
	UINT32                                                   reserved40;	//0xCC903698
	UINT32                                                   reserved41;	//0xCC90369C
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_00_T                        addr_mcc_ctrl_00;	//0xCC9036A0
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_01_T                        addr_mcc_ctrl_01;	//0xCC9036A4
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_02_T                        addr_mcc_ctrl_02;	//0xCC9036A8
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_03_T                        addr_mcc_ctrl_03;	//0xCC9036AC
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_04_T                        addr_mcc_ctrl_04;	//0xCC9036B0
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_05_T                        addr_mcc_ctrl_05;	//0xCC9036B4
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_06_T                        addr_mcc_ctrl_06;	//0xCC9036B8
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_07_T                        addr_mcc_ctrl_07;	//0xCC9036BC
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_08_T                        addr_mcc_ctrl_08;	//0xCC9036C0
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_09_T                        addr_mcc_ctrl_09;	//0xCC9036C4
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_10_T                        addr_mcc_ctrl_10;	//0xCC9036C8
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_11_T                        addr_mcc_ctrl_11;	//0xCC9036CC
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_12_T                        addr_mcc_ctrl_12;	//0xCC9036D0
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_13_T                        addr_mcc_ctrl_13;	//0xCC9036D4
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_14_T                        addr_mcc_ctrl_14;	//0xCC9036D8
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_15_T                        addr_mcc_ctrl_15;	//0xCC9036DC
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_16_T                        addr_mcc_ctrl_16;	//0xCC9036E0
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_17_T                        addr_mcc_ctrl_17;	//0xCC9036E4
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_18_T                        addr_mcc_ctrl_18;	//0xCC9036E8
	BE_O26A0_REG_OLED_ADDR_MCC_CTRL_19_T                        addr_mcc_ctrl_19;	//0xCC9036EC
	UINT32                                                   reserved42;	//0xCC9036F0
	UINT32                                                   reserved43;	//0xCC9036F4
	UINT32                                                   reserved44;	//0xCC9036F8
	UINT32                                                   reserved45;	//0xCC9036FC
	BE_O26A0_REG_OLED_REG_DITHER_CTRL_00_T                    reg_dither_ctrl_00;	//0xCC903700
	BE_O26A0_REG_OLED_REG_DITHER_CTRL_01_T                    reg_dither_ctrl_01;	//0xCC903704
	BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_00_T          reg_dither_err_diffu_00;	//0xCC903708
	BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_01_T          reg_dither_err_diffu_01;	//0xCC90370C
	BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_02_T          reg_dither_err_diffu_02;	//0xCC903710
	BE_O26A0_REG_OLED_REG_DITHER_ERR_DIFFU_03_T          reg_dither_err_diffu_03;	//0xCC903714
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_00_T          reg_dither_rnd_diffu_00;	//0xCC903718
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_01_T          reg_dither_rnd_diffu_01;	//0xCC90371C
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_02_T          reg_dither_rnd_diffu_02;	//0xCC903720
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_03_T          reg_dither_rnd_diffu_03;	//0xCC903724
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_04_T          reg_dither_rnd_diffu_04;	//0xCC903728
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_05_T          reg_dither_rnd_diffu_05;	//0xCC90372C
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_06_T          reg_dither_rnd_diffu_06;	//0xCC903730
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_07_T          reg_dither_rnd_diffu_07;	//0xCC903734
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_08_T          reg_dither_rnd_diffu_08;	//0xCC903738
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_09_T          reg_dither_rnd_diffu_09;	//0xCC90373C
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_10_T          reg_dither_rnd_diffu_10;	//0xCC903740
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_11_T          reg_dither_rnd_diffu_11;	//0xCC903744
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_12_T          reg_dither_rnd_diffu_12;	//0xCC903748
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_13_T          reg_dither_rnd_diffu_13;	//0xCC90374C
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_14_T          reg_dither_rnd_diffu_14;	//0xCC903750
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_15_T          reg_dither_rnd_diffu_15;	//0xCC903754
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_16_T          reg_dither_rnd_diffu_16;	//0xCC903758
	BE_O26A0_REG_OLED_REG_DITHER_RND_DIFFU_17_T          reg_dither_rnd_diffu_17;	//0xCC90375C
}BE_O26A0_REG_OLED_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E00 RW 0x0000_0000
	UINT32 reg_ucr_en                       :1;	//(0,RW,0x00) //Uniformity Correction enable
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_UCR_REG_CORE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E04 RW 0x0000_000F
	UINT32 reg_ivsync_pol                   :1;	//(0,RW,0x1) //1 := input vsync inversion 	0 = input vsync bypass
	UINT32 reg_ihsync_pol                   :1;	//(1,RW,0x1) //1 := input hsync inversion 	0 = input hsync bypass
	UINT32 reg_ovsync_pol                   :1;	//(2,RW,0x1) //1 := output vsync inversion	0 = output vsync bypass
	UINT32 reg_ohsync_pol                   :1;	//(3,RW,0x1) //1 := output hsync inversion	0 = output hsync bypass
	UINT32 resvd                            :28;
	};
}BE_O26A0_REG_UCR_REG_CORE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E10 RW 0x0000_0000
	UINT32 reg_cg_disable                   :1;	//(0,RW,0x0) //clock gating disable (UNUSED)
	UINT32 resvd                            :31;
	};
}BE_O26A0_REG_UCR_REG_CG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E20 RW 0x0000_0000
	UINT32 addr_tm_ctrl_pts                 :3;	//(2:0,RW,0x0) //LUT control points (0~7)
	UINT32 resvd0                           :5;
	UINT32 addr_h                           :3;	//(10:8,RW,0x0) //Hozontal Block address (0~7)
	UINT32 addr_v                           :3;	//(13:11,RW,0x0) //Vertical Block address (0~7)
	UINT32 resvd1                           :17;
	UINT32 we_ai                            :1;	//(31,RW,0x0) //write auto increment
	};
}BE_O26A0_REG_UCR_REG_LUT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E24 RW 0x0000_0000
	UINT32 ctrl_r_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Red
	UINT32 resvd0                           :4;
	UINT32 ctrl_r_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Red
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_UCR_REG_LUT_DATA_R_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E28 RW 0x0000_0000
	UINT32 ctrl_g_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Green
	UINT32 resvd0                           :4;
	UINT32 ctrl_g_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Green
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_UCR_REG_LUT_DATA_G_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E2C RW 0x0000_0000
	UINT32 ctrl_b_out                       :12;	//(11:0,RW,0x0) //LUT output control point for Blue
	UINT32 resvd0                           :4;
	UINT32 ctrl_b_in                        :12;	//(27:16,RW,0x0) //LUT input control point for Blue
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_UCR_REG_LUT_DATA_B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E30 RW 0x0000_0000
	UINT32 xpos_01                          :13;	//(12:0,RW,0x0) //X position 1 of the block center
	UINT32 resvd0                           :3;
	UINT32 xpos_00                          :13;	//(28:16,RW,0x0) //X position 0 of the block center
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E34 RW 0x0000_0000
	UINT32 xpos_03                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_02                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E38 RW 0x0000_0000
	UINT32 xpos_05                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_04                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E3C RW 0x0000_0000
	UINT32 xpos_07                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_06                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E40 RW 0x0000_0000
	UINT32 xpos_09                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_08                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E44 RW 0x0000_0000
	UINT32 xpos_11                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_10                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E48 RW 0x0000_0000
	UINT32 xpos_13                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_12                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E4C RW 0x0000_0000
	UINT32 xpos_15                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 xpos_14                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_XPOS_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E50 RW 0x0000_0000
	UINT32 ypos_01                          :13;	//(12:0,RW,0x0) //Y position 1 of the block center
	UINT32 resvd0                           :3;
	UINT32 ypos_00                          :13;	//(28:16,RW,0x0) //Y position 0 of the block center
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E54 RW 0x0000_0000
	UINT32 ypos_03                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_02                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E58 RW 0x0000_0000
	UINT32 ypos_05                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_04                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E5C RW 0x0000_0000
	UINT32 ypos_07                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_06                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E60 RW 0x0000_0000
	UINT32 ypos_09                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_08                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E64 RW 0x0000_0000
	UINT32 ypos_11                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_10                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E68 RW 0x0000_0000
	UINT32 ypos_13                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_12                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC902E6C RW 0x0000_0000
	UINT32 ypos_15                          :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 ypos_14                          :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_UCR_REG_YPOS_07_T;

typedef struct {
	BE_O26A0_REG_UCR_REG_CORE_CTRL_00_T                         reg_core_ctrl_00;	//0xCC902E00
	BE_O26A0_REG_UCR_REG_CORE_CTRL_01_T                         reg_core_ctrl_01;	//0xCC902E04
	UINT32                                                    reserved0;	//0xCC902E08
	UINT32                                                    reserved1;	//0xCC902E0C
	BE_O26A0_REG_UCR_REG_CG_CTRL_00_T                             reg_cg_ctrl_00;	//0xCC902E10
	UINT32                                                    reserved2;	//0xCC902E14
	UINT32                                                    reserved3;	//0xCC902E18
	UINT32                                                    reserved4;	//0xCC902E1C
	BE_O26A0_REG_UCR_REG_LUT_CTRL_T                                 reg_lut_ctrl;	//0xCC902E20
	BE_O26A0_REG_UCR_REG_LUT_DATA_R_T                             reg_lut_data_r;	//0xCC902E24
	BE_O26A0_REG_UCR_REG_LUT_DATA_G_T                             reg_lut_data_g;	//0xCC902E28
	BE_O26A0_REG_UCR_REG_LUT_DATA_B_T                             reg_lut_data_b;	//0xCC902E2C
	BE_O26A0_REG_UCR_REG_XPOS_00_T                                   reg_xpos_00;	//0xCC902E30
	BE_O26A0_REG_UCR_REG_XPOS_01_T                                   reg_xpos_01;	//0xCC902E34
	BE_O26A0_REG_UCR_REG_XPOS_02_T                                   reg_xpos_02;	//0xCC902E38
	BE_O26A0_REG_UCR_REG_XPOS_03_T                                   reg_xpos_03;	//0xCC902E3C
	BE_O26A0_REG_UCR_REG_XPOS_04_T                                   reg_xpos_04;	//0xCC902E40
	BE_O26A0_REG_UCR_REG_XPOS_05_T                                   reg_xpos_05;	//0xCC902E44
	BE_O26A0_REG_UCR_REG_XPOS_06_T                                   reg_xpos_06;	//0xCC902E48
	BE_O26A0_REG_UCR_REG_XPOS_07_T                                   reg_xpos_07;	//0xCC902E4C
	BE_O26A0_REG_UCR_REG_YPOS_00_T                                   reg_ypos_00;	//0xCC902E50
	BE_O26A0_REG_UCR_REG_YPOS_01_T                                   reg_ypos_01;	//0xCC902E54
	BE_O26A0_REG_UCR_REG_YPOS_02_T                                   reg_ypos_02;	//0xCC902E58
	BE_O26A0_REG_UCR_REG_YPOS_03_T                                   reg_ypos_03;	//0xCC902E5C
	BE_O26A0_REG_UCR_REG_YPOS_04_T                                   reg_ypos_04;	//0xCC902E60
	BE_O26A0_REG_UCR_REG_YPOS_05_T                                   reg_ypos_05;	//0xCC902E64
	BE_O26A0_REG_UCR_REG_YPOS_06_T                                   reg_ypos_06;	//0xCC902E68
	BE_O26A0_REG_UCR_REG_YPOS_07_T                                   reg_ypos_07;	//0xCC902E6C
}BE_O26A0_REG_UCR_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_TOP_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882004 RW 200FF000
	UINT32 reg_1st_out_rd_use_osd_map       :1;	//(0,RW,0x0) //
	UINT32 reg_2nd_out_rd_out_clip          :1;	//(1,RW,0x0) //(not used in m16p3), 11b mode?? 10b ???, ?? ?.
	UINT32 reg_1st_out_rd_out_clip          :1;	//(2,RW,0x0) //(not used in m16p3), 11b mode?? 10b ???, ?? ?.
	UINT32 resvd                            :4;
	UINT32 reg_decon_dnr_motion_sel         :1;	//(7,RW,0x0) //0: input motion, 1: dnr_motion_blur (line align ? ??)
	UINT32 reg_11bit_debug_mode_en          :1;	//(8,RW,0x0) //not used in m16p3
	UINT32 reg_out_bit_opt                  :1;	//(9,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_out_bit_sel        :1;	//(10,RW,0x0) //not used in m16p3
	UINT32 reg_tnr_decon_in_bit_sel         :1;	//(11,RW,0x0) //0: 12-bit full	1: 1st_out_rd ?? /4
	UINT32 reg_1st_out_rd_max_alpha         :8;	//(19:12,RW,0xFF) //
	UINT32 reg_1st_out_rd_min_alpha         :8;	//(27:20,RW,0x0) //
	UINT32 reg_1st_out_rd_bit               :3;	//(30:28,RW,0x2) //
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882008 RW 0x0000_0001
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x1) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88200C RW 0x0000_0FFF
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882010 RW 0x00FF_FFFF
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882014 RW 0x1357_9753
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x1357_9753) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882018 RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x2468_0864) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88201C RW 0x1470_3692
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x1470_3692) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_6_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882024 RW 0x3000_0000
	UINT32 reg_2nd_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_2nd_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :4;
	UINT32 reg_2nd_out_rd_max_lsb_2b        :2;	//(29:28,RW,0x3) //
	UINT32 reg_2nd_out_rd_min_lsb_2b        :2;	//(31:30,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882028 RW 0x0000_0FFF
	UINT32 reg_2nd_out_rd_max_pel_yy        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88202C RW 0x00FF_FFFF
	UINT32 reg_2nd_out_rd_max_pel_cr        :12;	//(11:0,RW,0xFFF) //
	UINT32 reg_2nd_out_rd_max_pel_cb        :12;	//(23:12,RW,0xFFF) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882030 RW 0x1357_9753
	UINT32 reg_2nd_out_rd_init_yy           :32;	//(31:0,RW,0x1357_9753) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882034 RW 0x2468_0864
	UINT32 reg_2nd_out_rd_init_cb           :32;	//(31:0,RW,0x2468_0864) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882038 RW 0x1470_3692
	UINT32 reg_2nd_out_rd_init_cr           :32;	//(31:0,RW,0x1470_3692) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88203C RW 0x1357_9753
	UINT32 reg_err_out_rd_simple_init_yy    :32;	//(31:0,RW,0x1357_9753) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882040 RW 0x2468_0864
	UINT32 reg_err_out_rd_simple_init_cb    :32;	//(31:0,RW,0x2468_0864) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882044 RW 0x1470_3692
	UINT32 reg_err_out_rd_simple_init_cr    :32;	//(31:0,RW,0x1470_3692) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_16_T;

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
	UINT32 reg_rd_simple_clip               :1;	//(23,RW,0x0) //11b mode?? 10b ???, ?? ?.
	UINT32 reg_rd_clip                      :1;	//(24,RW,0x0) //11b mode?? 10b ???, ?? ?.
	UINT32 reg_input_csc_en                 :1;	//(25,RW,0x1) //default =1
	UINT32 reg_1st_debug_mode               :4;	//(29:26,RW,0x0) //0: final_gain	1: variance	2: variance_gain	3: diff_gain	4: luma gain	5: sel_diff	6: motion	7: motion_gain	8: 2x2 blur	9: 3x3 blur	10: L6_var_2x2	11: skin	12: face	13: face_skin	14: aux_luma	15: input_blur
	UINT32 reg_force_block_no_en            :1;	//(30,RW,0x0) //NOT IN USE in O26
	UINT32 reg_decon_1st_en                 :1;	//(31,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_17_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882050 RW 0x190F_0A07
	UINT32 reg_decon_diff_x_th0             :8;	//(7:0,RW,0x7) //
	UINT32 reg_decon_diff_x_th1             :8;	//(15:8,RW,0xA) //
	UINT32 reg_decon_diff_x_th2             :8;	//(23:16,RW,0xF) //
	UINT32 reg_decon_diff_x_th3             :8;	//(31:24,RW,0x19) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882054 RW 0x0020_80FF
	UINT32 reg_decon_diff_y_th0             :8;	//(7:0,RW,0xFF) //
	UINT32 reg_decon_diff_y_th1             :8;	//(15:8,RW,0x80) //
	UINT32 reg_decon_diff_y_th2             :8;	//(23:16,RW,0x20) //
	UINT32 reg_decon_diff_y_th3             :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882058 RW 0x0100_C080
	UINT32 reg_decon_var_x_th2              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_x_th1              :10;	//(19:10,RW,0x30) //
	UINT32 reg_decon_var_x_th0              :10;	//(29:20,RW,0x10) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88205C RW 0x1004_0080
	UINT32 reg_decon_var_y_th1              :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_var_y_th0              :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_var_x_th3              :10;	//(29:20,RW,0x100) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882060 RW 0x0200_003C
	UINT32 reg_decon_luma_x_th0             :10;	//(9:0,RW,0x3C) //
	UINT32 reg_decon_var_y_th3              :10;	//(19:10,RW,0x0) //
	UINT32 reg_decon_var_y_th2              :10;	//(29:20,RW,0x20) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882064 RW 0x0000_0000
	UINT32 vsync                            :16;	//(15:0,RW,0x0) //
	UINT32 vfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882068 RW 0x0000_0000
	UINT32 va                               :16;	//(15:0,RW,0x0) //
	UINT32 vbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88206C RW 0x0000_0000
	UINT32 hsync                            :16;	//(15:0,RW,0x0) //
	UINT32 hfp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882070 RW 0x0000_0000
	UINT32 ha                               :16;	//(15:0,RW,0x0) //
	UINT32 hbp                              :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL3_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882078 RW 0x0000_0000
	UINT32 sync_h_dly                       :16;	//(15:0,RW,0x0) //
	UINT32 sync_v_dly                       :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88207C RW 0x0000_0000
	UINT32 manual_cnt_h_value               :16;	//(15:0,RW,0x0) //
	UINT32 manual_cnt_v_value               :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882080 RW 0x00028000
	UINT32 reg_auto_ha_delay                :15;	//(14:0,RW,0x00) //CCO DEC delay control
	UINT32 reg_use_general_actv_dly         :1;	//(15:15,RW,0x1) //CCO DEC delay control
	UINT32 reg_auto_va_delay                :15;	//(30:16,RW,0x2) //CCO DEC delay control
	UINT32 reg_ha_seamless                  :1;	//(31:31,RW,0x0) //CCO DEC delay control
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882084 RW 0x00028000
	UINT32 reg_auto_hs_delay                :15;	//(14:0,RW,0x00) //CCO DEC delay control
	UINT32 reg_use_general_sync_dly         :1;	//(15:15,RW,0x1) //CCO DEC delay control
	UINT32 reg_auto_vs_delay                :15;	//(30:16,RW,0x2) //CCO DEC delay control
	UINT32 reg_hs_seamless                  :1;	//(31:31,RW,0x0) //CCO DEC delay control
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882088 RW 0x0000_0000
	UINT32 reg_normal_number                :16;	//(15:0,RW,0x0) //
	UINT32 resvd                            :16;
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88208C RW 0x0000_0000
	UINT32 rst_pos_cnt_h                    :16;	//(15:0,RW,0x0) //
	UINT32 rst_pos_cnt_v                    :16;	//(31:16,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRLA_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882094 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882098 RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88209C RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A0 RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A4 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820A8 RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820AC RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B0 RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B4 RW 0x0000_00E4
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820B8 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_3DLY_CTRLA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820BC RW 0x0643_212C
	UINT32 reg_decon_luma_x_th3             :10;	//(9:0,RW,0x12C) //
	UINT32 reg_decon_luma_x_th2             :10;	//(19:10,RW,0xC8) //
	UINT32 reg_decon_luma_x_th1             :10;	//(29:20,RW,0x64) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C0 RW 0x190C_8384
	UINT32 reg_decon_luma_x_th6             :10;	//(9:0,RW,0x384) //
	UINT32 reg_decon_luma_x_th5             :10;	//(19:10,RW,0x320) //
	UINT32 reg_decon_luma_x_th4             :10;	//(29:20,RW,0x190) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C4 RW 0x3E81_8080
	UINT32 reg_decon_luma_y_th1             :10;	//(9:0,RW,0x80) //
	UINT32 reg_decon_luma_y_th0             :10;	//(19:10,RW,0x60) //
	UINT32 reg_decon_luma_x_th7             :10;	//(29:20,RW,0x3E8) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820C8 RW 0x0A04_0200
	UINT32 reg_decon_luma_y_th4             :10;	//(9:0,RW,0x200) //
	UINT32 reg_decon_luma_y_th3             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th2             :10;	//(29:20,RW,0xA0) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820CC RW 0x1804_0080
	UINT32 reg_decon_luma_y_th7             :10;	//(9:0,RW,0x080) //
	UINT32 reg_decon_luma_y_th6             :10;	//(19:10,RW,0x100) //
	UINT32 reg_decon_luma_y_th5             :10;	//(29:20,RW,0x180) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_28_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_29_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820D8 RW 0xFF27_8064
	UINT32 reg_alpha_blur_l6_var_th1        :10;	//(9:0,RW,0x64) //
	UINT32 reg_alpha_blur_l6_var_th0        :10;	//(19:10,RW,0x1E0) //
	UINT32 reg_lb_var_cut_res               :4;	//(23:20,RW,0x2) //
	UINT32 reg_master_gain                  :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820DC RW 0xC002_0100
	UINT32 reg_l6_var_x_th2                 :10;	//(9:0,RW,0x100) //
	UINT32 reg_l6_var_x_th1                 :10;	//(19:10,RW,0x80) //
	UINT32 reg_l6_var_x_th0                 :10;	//(29:20,RW,0x0) //
	UINT32 reg_lb_var_opt                   :1;	//(30,RW,0x1) //cco_decon_variance opt
	UINT32 reg_lb_var_en                    :1;	//(31,RW,0x1) //cco_decon_variance enable
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820E0 RW 0xA000_0080
	UINT32 reg_l6_var_y_th1                 :10;	//(9:0,RW,0x80) //
	UINT32 reg_l6_var_y_th0                 :10;	//(19:10,RW,0x0) //
	UINT32 reg_l6_var_x_th3                 :10;	//(29:20,RW,0x200) //
	UINT32 resvd                            :1;
	UINT32 reg_lb_var_lut_bit               :1;	//(31,RW,0x1) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_33_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820E8 RW 0x1357_9753
	UINT32 reg_decon_rd_simple_init_yy      :32;	//(31:0,RW,0x1357_9753) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820EC RW 0x2468_0864
	UINT32 reg_decon_rd_simple_init_cb      :32;	//(31:0,RW,0x2468_0864) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F0 RW 0x1470_3692
	UINT32 reg_decon_rd_simple_init_cr      :32;	//(31:0,RW,0x1470_3692) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F4 RW 0xA004_0040
	UINT32 reg_rd_min_pel_cb                :12;	//(11:0,RW,0x40) //
	UINT32 reg_rd_min_pel_yy                :12;	//(23:12,RW,0x40) //
	UINT32 resvd                            :4;
	UINT32 reg_rd_bit                       :3;	//(30:28,RW,0x2) //
	UINT32 reg_decon_rd_on                  :1;	//(31,RW,0x1) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820F8 RW 0x0004_07FF
	UINT32 reg_rd_max_pel_yy                :12;	//(11:0,RW,0x7FF) //
	UINT32 reg_rd_min_pel_cr                :12;	//(23:12,RW,0x40) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8820FC RW 0x007F_F7FF
	UINT32 reg_rd_max_pel_cr                :12;	//(11:0,RW,0x7FF) //
	UINT32 reg_rd_max_pel_cb                :12;	//(23:12,RW,0x7FF) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882100 RW 0x1357_9753
	UINT32 reg_rd_init_yy                   :32;	//(31:0,RW,0x1357_9753) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882104 RW 0x2468_0864
	UINT32 reg_rd_init_cb                   :32;	//(31:0,RW,0x2468_0864) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882108 RW 0x1470_3692
	UINT32 reg_rd_init_cr                   :32;	//(31:0,RW,0x1470_3692) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88210C RW 0x0104_080F
	UINT32 reg_motion_gain_x3               :8;	//(7:0,RW,0xF) //
	UINT32 reg_motion_gain_x2               :8;	//(15:8,RW,0x8) //
	UINT32 reg_motion_gain_x1               :8;	//(23:16,RW,0x4) //
	UINT32 reg_motion_gain_x0               :8;	//(31:24,RW,0x1) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882110 RW 0xFF10_0500
	UINT32 reg_motion_gain_y3               :8;	//(7:0,RW,0x0) //
	UINT32 reg_motion_gain_y2               :8;	//(15:8,RW,0x5) //
	UINT32 reg_motion_gain_y1               :8;	//(23:16,RW,0x10) //
	UINT32 reg_motion_gain_y0               :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_45_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882118 RW 0x4871_B399
	UINT32 reg_bbd_y1                       :12;	//(11:0,RW,0x399) //
	UINT32 reg_bbd_x1                       :12;	//(23:12,RW,0x71B) //
	UINT32 resvd                            :2;
	UINT32 reg_blur3_sim_ratio              :3;	//(28:26,RW,0x2) //
	UINT32 reg_blur2_sim_ratio              :3;	//(31:29,RW,0x2) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88211C RW 0x1050_6478
	UINT32 reg_lut_blur_sim_x3              :8;	//(7:0,RW,0x78) //
	UINT32 reg_lut_blur_sim_x2              :8;	//(15:8,RW,0x64) //
	UINT32 reg_lut_blur_sim_x1              :8;	//(23:16,RW,0x50) //
	UINT32 reg_lut_blur_sim_x0              :8;	//(31:24,RW,0x10) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882120 RW 0xFF31_0A01
	UINT32 reg_lut_blur_sim_y3              :8;	//(7:0,RW,0x1) //
	UINT32 reg_lut_blur_sim_y2              :8;	//(15:8,RW,0xA) //
	UINT32 reg_lut_blur_sim_y1              :8;	//(23:16,RW,0x31) //
	UINT32 reg_lut_blur_sim_y0              :8;	//(31:24,RW,0xFF) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882124 RW 0x143C_6EC8
	UINT32 reg_lut_skin_yy_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_yy_x2               :8;	//(15:8,RW,0x6E) //
	UINT32 reg_lut_skin_yy_x1               :8;	//(23:16,RW,0x3C) //
	UINT32 reg_lut_skin_yy_x0               :8;	//(31:24,RW,0x14) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882128 RW 0x5064_788C
	UINT32 reg_lut_skin_cb_x3               :8;	//(7:0,RW,0x8C) //
	UINT32 reg_lut_skin_cb_x2               :8;	//(15:8,RW,0x78) //
	UINT32 reg_lut_skin_cb_x1               :8;	//(23:16,RW,0x64) //
	UINT32 reg_lut_skin_cb_x0               :8;	//(31:24,RW,0x50) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88212C RW 0x7882_B4C8
	UINT32 reg_lut_skin_cr_x3               :8;	//(7:0,RW,0xC8) //
	UINT32 reg_lut_skin_cr_x2               :8;	//(15:8,RW,0xB4) //
	UINT32 reg_lut_skin_cr_x1               :8;	//(23:16,RW,0x82) //
	UINT32 reg_lut_skin_cr_x0               :8;	//(31:24,RW,0x78) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_52_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882130 RW 0x00C8_C800
	UINT32 reg_lut_skin_y3                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_lut_skin_y2                  :8;	//(15:8,RW,0xC8) //
	UINT32 reg_lut_skin_y1                  :8;	//(23:16,RW,0xC8) //
	UINT32 reg_lut_skin_y0                  :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_53_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882134 RW 0x0020_4080
	UINT32 reg_lut_face_x3                  :8;	//(7:0,RW,0x80) //
	UINT32 reg_lut_face_x2                  :8;	//(15:8,RW,0x40) //
	UINT32 reg_lut_face_x1                  :8;	//(23:16,RW,0x20) //
	UINT32 reg_lut_face_x0                  :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_54_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882138 RW 0x0040_80FF
	UINT32 reg_lut_face_y3                  :8;	//(7:0,RW,0xFF) //
	UINT32 reg_lut_face_y2                  :8;	//(15:8,RW,0x80) //
	UINT32 reg_lut_face_y1                  :8;	//(23:16,RW,0x40) //
	UINT32 reg_lut_face_y0                  :8;	//(31:24,RW,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_55_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_56_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882140 RW 0x0000_0044
	UINT32 reg_l6_var_diff_dist_h           :4;	//(3:0,RW,0x4) //
	UINT32 reg_l6_var_diff_dist_w           :4;	//(7:4,RW,0x4) //
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_57_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882144 RW 0x00E0_380E
	UINT32 reg_l6_var_diff_th_cr            :10;	//(9:0,RW,0xE) //
	UINT32 reg_l6_var_diff_th_cb            :10;	//(19:10,RW,0xE) //
	UINT32 reg_l6_var_diff_th_yy            :10;	//(29:20,RW,0xE) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_58_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882148 RW 0x0000_C850
	UINT32 reg_l6_var_diff_th_yy3           :10;	//(9:0,RW,0x50) //
	UINT32 reg_l6_var_diff_th_yy2           :10;	//(19:10,RW,0x32) //
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_59_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88214C RW 0x01E0_780A
	UINT32 reg_l6_var_diff_th_min_yy3       :10;	//(9:0,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_yy2       :10;	//(19:10,RW,0x1E) //
	UINT32 reg_l6_var_diff_th_min_yy        :10;	//(29:20,RW,0x1E) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_60_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882150 RW 0x80A0_280A
	UINT32 reg_l6_var_diff_th_min_cc3       :10;	//(9:0,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_cc2       :10;	//(19:10,RW,0xA) //
	UINT32 reg_l6_var_diff_th_min_cc        :10;	//(29:20,RW,0xA) //
	UINT32 resvd                            :1;
	UINT32 reg_l6_var_reshape_en            :1;	//(31,RW,0x1) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_61_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882154 RW 0x2020_2080
	UINT32 reg_l6_var_v_yy_cond_cb_adj_ratio :8;	//(7:0,RW,0x80) //
	UINT32 reg_l6_var_v_yy_cond_yy_adj_ratio :8;	//(15:8,RW,0x20) //
	UINT32 reg_l6_var_h_diff_yy_cond_ratio  :8;	//(23:16,RW,0x20) //
	UINT32 reg_l6_var_v_diff_yy_cond_ratio  :8;	//(31:24,RW,0x20) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_62_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882158 RW 0x8020_8080
	UINT32 reg_l6_var_h_yy_cond_cr_adj_ratio :8;	//(7:0,RW,0x80) //
	UINT32 reg_l6_var_h_yy_cond_cb_adj_ratio :8;	//(15:8,RW,0x80) //
	UINT32 reg_l6_var_h_yy_cond_yy_adj_ratio :8;	//(23:16,RW,0x20) //
	UINT32 reg_l6_var_v_yy_cond_cr_adj_ratio :8;	//(31:24,RW,0x80) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_63_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88215C RW 0x80FF_FF00
	UINT32 resvd                            :8;
	UINT32 reg_l6_var_cc_cond_cr_adj_ratio  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_l6_var_cc_cond_cb_adj_ratio  :8;	//(23:16,RW,0xFF) //
	UINT32 reg_l6_var_cc_cond_yy_adj_ratio  :8;	//(31:24,RW,0x80) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_64_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882160 RW 0x0020_0200
	UINT32 reg_l6_var_v_diff_cut_value      :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_v_diff_th             :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_65_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882164 RW 0x0020_0200
	UINT32 reg_l6_var_h_diff_cut_value      :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_h_diff_th             :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_66_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882168 RW 0x0020_0200
	UINT32 reg_l6_var_total_diff_max_rep_value :12;	//(11:0,RW,0x200) //
	UINT32 reg_l6_var_total_diff_max_th     :12;	//(23:12,RW,0x200) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_67_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88216C RW 0x0003_2000
	UINT32 reg_l6_var_total_diff_low_rep_value :12;	//(11:0,RW,0x0) //
	UINT32 reg_l6_var_total_diff_low_th     :12;	//(23:12,RW,0x32) //
	UINT32 resvd                            :8;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_68_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_69_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882174 RW 0x0000_087F
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x87F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x0) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_70_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882178 RW 0x0029_083F
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x83F) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x29) //
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_71_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88217C RW 0x0001_0060
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x60) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0x40) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_72_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882180 RW 0x0002_00A0
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0xA0) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x80) //2nd rd?? ???? ??
	UINT32 resvd                            :12;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_73_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882184 RW 0x000C_0100
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0xC0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_74_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882188 RW 0x0012_0180
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0x180) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x120) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_75_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88218C RW 0x0000_0008
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_76_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882190 RW 0x0002_0080
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0x80) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x20) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_77_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882194 RW 0x000A_0180
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x180) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0xA0) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_78_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882198 RW 0x0020_03FF
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0x200) //2nd rd?? ???? ??
	UINT32 resvd1                           :10;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_79_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88219C RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_80_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821A0 RW 0x0000_0000
	UINT32 tdata0                           :32;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_81_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821A4 RW 0x0000_0000
	UINT32 reg_2nd_var_x_th1                :10;	//(9:0,RW,0x0) //
	UINT32 resvd                            :22;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_82_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_83_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821AC RW 0x4020_1008
	UINT32 reg_decon_low_diff_x_th0         :8;	//(7:0,NA,0x8) //
	UINT32 reg_decon_low_diff_x_th1         :8;	//(15:8,NA,0x10) //
	UINT32 reg_decon_low_diff_x_th2         :8;	//(23:16,NA,0x20) //
	UINT32 reg_decon_low_diff_x_th3         :8;	//(31:24,NA,0x40) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_84_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B0 RW 0x0080_A0C0
	UINT32 reg_decon_low_diff_y_th0         :8;	//(7:0,NA,0xC0) //
	UINT32 reg_decon_low_diff_y_th1         :8;	//(15:8,NA,0xA0) //
	UINT32 reg_decon_low_diff_y_th2         :8;	//(23:16,NA,0x80) //
	UINT32 reg_decon_low_diff_y_th3         :8;	//(31:24,NA,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_85_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B4 RW 0x0201_0060
	UINT32 reg_decon_low_var_x_th2          :10;	//(9:0,NA,0x60) //
	UINT32 reg_decon_low_var_x_th1          :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_low_var_x_th0          :10;	//(29:20,NA,0x20) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_86_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821B8 RW 0x0806_0100
	UINT32 reg_decon_low_var_y_th1          :10;	//(9:0,NA,0x100) //
	UINT32 reg_decon_low_var_y_th0          :10;	//(19:10,NA,0x180) //
	UINT32 reg_decon_low_var_x_th3          :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_87_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821BC RW 0x0801_0040
	UINT32 reg_decon_low_luma_x_th0         :10;	//(9:0,NA,0x40) //
	UINT32 reg_decon_low_var_y_th3          :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_low_var_y_th2          :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_88_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C0 RW 0x0501_C0A0
	UINT32 reg_decon_low_luma_x_th3         :10;	//(9:0,NA,0xA0) //
	UINT32 reg_decon_low_luma_x_th2         :10;	//(19:10,NA,0x70) //
	UINT32 reg_decon_low_luma_x_th1         :10;	//(29:20,NA,0x50) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_89_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C4 RW 0x0C04_0180
	UINT32 reg_decon_low_luma_x_th6         :10;	//(9:0,NA,0x180) //
	UINT32 reg_decon_low_luma_x_th5         :10;	//(19:10,NA,0x100) //
	UINT32 reg_decon_low_luma_x_th4         :10;	//(29:20,NA,0xC0) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_90_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821C8 RW 0x2000_2020
	UINT32 reg_decon_low_luma_y_th1         :10;	//(9:0,NA,0x20) //
	UINT32 reg_decon_low_luma_y_th0         :10;	//(19:10,NA,0x8) //
	UINT32 reg_decon_low_luma_x_th7         :10;	//(29:20,NA,0x200) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_91_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821CC RW 0x0402_00A0
	UINT32 reg_decon_low_luma_y_th4         :10;	//(9:0,NA,0xA0) //
	UINT32 reg_decon_low_luma_y_th3         :10;	//(19:10,NA,0x80) //
	UINT32 reg_decon_low_luma_y_th2         :10;	//(29:20,NA,0x40) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_92_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D0 RW 0x0FF6_03FF
	UINT32 reg_decon_low_luma_y_th7         :10;	//(9:0,NA,0x3FF) //
	UINT32 reg_decon_low_luma_y_th6         :10;	//(19:10,NA,0x180) //
	UINT32 reg_decon_low_luma_y_th5         :10;	//(29:20,NA,0xFF) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_93_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D4 RW 0xC401_8080
	UINT32 reg_decon_aux_luma_x_th2         :10;	//(9:0,NA,0x80) //
	UINT32 reg_decon_aux_luma_x_th1         :10;	//(19:10,NA,0x60) //
	UINT32 reg_decon_aux_luma_x_th0         :10;	//(29:20,NA,0x40) //
	UINT32 reg_low_aux_luma_en              :1;	//(30,NA,0x1) //
	UINT32 reg_aux_luma_en                  :1;	//(31,NA,0x1) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_94_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821D8 RW 0x0A03_00FF
	UINT32 reg_decon_aux_luma_x_th5         :10;	//(9:0,NA,0xFF) //
	UINT32 reg_decon_aux_luma_x_th4         :10;	//(19:10,NA,0xC0) //
	UINT32 reg_decon_aux_luma_x_th3         :10;	//(29:20,NA,0xA0) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_95_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821DC RW 0x1004_8010
	UINT32 reg_decon_aux_luma_y_th0         :10;	//(9:0,NA,0x10) //
	UINT32 reg_decon_aux_luma_x_th7         :10;	//(19:10,NA,0x120) //
	UINT32 reg_decon_aux_luma_x_th6         :10;	//(29:20,NA,0x100) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_96_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E0 RW 0x0202_00C0
	UINT32 reg_decon_aux_luma_y_th3         :10;	//(9:0,NA,0xC0) //
	UINT32 reg_decon_aux_luma_y_th2         :10;	//(19:10,NA,0x80) //
	UINT32 reg_decon_aux_luma_y_th1         :10;	//(29:20,NA,0x20) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_97_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E4 RW 0x1FFB_FF00
	UINT32 reg_decon_aux_luma_y_th6         :10;	//(9:0,NA,0x300) //
	UINT32 reg_decon_aux_luma_y_th5         :10;	//(19:10,NA,0x2FF) //
	UINT32 reg_decon_aux_luma_y_th4         :10;	//(29:20,NA,0x1FF) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_98_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821E8 RW 0x3FF1_0050
	UINT32 reg_decon_low_aux_luma_x_th1     :10;	//(9:0,NA,0x50) //
	UINT32 reg_decon_low_aux_luma_x_th0     :10;	//(19:10,NA,0x40) //
	UINT32 reg_decon_aux_luma_y_th7         :10;	//(29:20,NA,0x3FF) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_99_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821EC RW 0x0601_C080
	UINT32 reg_decon_low_aux_luma_x_th4     :10;	//(9:0,NA,0x80) //
	UINT32 reg_decon_low_aux_luma_x_th3     :10;	//(19:10,NA,0x70) //
	UINT32 reg_decon_low_aux_luma_x_th2     :10;	//(29:20,NA,0x60) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_100_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F0 RW 0x0902_80B0
	UINT32 reg_decon_low_aux_luma_x_th7     :10;	//(9:0,NA,0xB0) //
	UINT32 reg_decon_low_aux_luma_x_th6     :10;	//(19:10,NA,0xA0) //
	UINT32 reg_decon_low_aux_luma_x_th5     :10;	//(29:20,NA,0x90) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_101_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F4 RW 0x0100_8040
	UINT32 reg_decon_low_aux_luma_y_th2     :10;	//(9:0,NA,0x40) //
	UINT32 reg_decon_low_aux_luma_y_th1     :10;	//(19:10,NA,0x20) //
	UINT32 reg_decon_low_aux_luma_y_th0     :10;	//(29:20,NA,0x10) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_102_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821F8 RW 0x0802_C0FF
	UINT32 reg_decon_low_aux_luma_y_th5     :10;	//(9:0,NA,0xFF) //
	UINT32 reg_decon_low_aux_luma_y_th4     :10;	//(19:10,NA,0xB0) //
	UINT32 reg_decon_low_aux_luma_y_th3     :10;	//(29:20,NA,0x80) //
	UINT32 resvd                            :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_103_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8821FC RW 0x1FFB_FCFF
	UINT32 reg_low_master_gain              :8;	//(7:0,NA,0xFF) //
	UINT32 resvd0                           :2;
	UINT32 reg_decon_low_aux_luma_y_th7     :10;	//(19:10,NA,0x2FF) //
	UINT32 reg_decon_low_aux_luma_y_th6     :10;	//(29:20,NA,0x1FF) //
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_104_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_105_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882204 RW 0x2030_C4D8
	UINT32 reg_lut_blur_base_luma_x_3       :8;	//(7:0,NA,0xD8) //
	UINT32 reg_lut_blur_base_luma_x_2       :8;	//(15:8,NA,0xC4) //
	UINT32 reg_lut_blur_base_luma_x_1       :8;	//(23:16,NA,0x30) //
	UINT32 reg_lut_blur_base_luma_x_0       :8;	//(31:24,NA,0x20) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_106_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882208 RW 0x0408_0B10
	UINT32 reg_lut_blur_base_luma_y_3       :8;	//(7:0,NA,0x10) //
	UINT32 reg_lut_blur_base_luma_y_2       :8;	//(15:8,NA,0xB) //
	UINT32 reg_lut_blur_base_luma_y_1       :8;	//(23:16,NA,0x8) //
	UINT32 reg_lut_blur_base_luma_y_0       :8;	//(31:24,NA,0x4) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_107_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88220C RW 0x1100_0000
	UINT32 resvd0                           :24;
	UINT32 light_csc_mode_rd_2              :1;	//(24,NA,0x1) //light_csc_mode for random diffusion 2
	UINT32 resvd1                           :3;
	UINT32 light_csc_mode_rd_1              :1;	//(28,NA,0x1) //light_csc_mode for random diffusion 1
	UINT32 resvd2                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_108_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882210 RW 0x0000_0000
	UINT32 reserved                         :32;	//(31:0,NA,0x0) //
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_109_T;

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
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882218 RW 0x0000_0000
	UINT32 win0_w0_x0                       :13;	//(12:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y0                       :13;	//(28:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88221C RW 0x0000_0000
	UINT32 win0_w0_x1                       :13;	//(12:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win0_w0_y1                       :13;	//(28:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882220 RW 0x0000_0000
	UINT32 win1_w0_x0                       :13;	//(12:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y0                       :13;	//(28:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882224 RW 0x0000_0000
	UINT32 win1_w0_x1                       :13;	//(12:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win1_w0_y1                       :13;	//(28:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882228 RW 0x0000_0000
	UINT32 win2_w0_x0                       :13;	//(12:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y0                       :13;	//(28:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88222C RW 0x0000_0000
	UINT32 win2_w0_x1                       :13;	//(12:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win2_w0_y1                       :13;	//(28:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882230 RW 0x0000_0000
	UINT32 win3_w0_x0                       :13;	//(12:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y0                       :13;	//(28:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882234 RW 0x0000_0000
	UINT32 win3_w0_x1                       :13;	//(12:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :3;
	UINT32 win3_w0_y1                       :13;	//(28:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :3;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC882238 RW 0x0000_00E4
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest) 0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_9_T;

typedef struct {
	BE_O26A0_REG_CCO_DEC_REG_DECON_TOP_CTRL_T                 reg_decon_top_ctrl;	//0xCC882000
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_0_T                     reg_decon_ctrl_0;	//0xCC882004
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_1_T                     reg_decon_ctrl_1;	//0xCC882008
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_2_T                     reg_decon_ctrl_2;	//0xCC88200C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_3_T                     reg_decon_ctrl_3;	//0xCC882010
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_4_T                     reg_decon_ctrl_4;	//0xCC882014
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_5_T                     reg_decon_ctrl_5;	//0xCC882018
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_6_T                     reg_decon_ctrl_6;	//0xCC88201C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_7_T                     reg_decon_ctrl_7;	//0xCC882020
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_8_T                     reg_decon_ctrl_8;	//0xCC882024
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_9_T                     reg_decon_ctrl_9;	//0xCC882028
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_10_T                   reg_decon_ctrl_10;	//0xCC88202C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_11_T                   reg_decon_ctrl_11;	//0xCC882030
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_12_T                   reg_decon_ctrl_12;	//0xCC882034
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_13_T                   reg_decon_ctrl_13;	//0xCC882038
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_14_T                   reg_decon_ctrl_14;	//0xCC88203C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_15_T                   reg_decon_ctrl_15;	//0xCC882040
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_16_T                   reg_decon_ctrl_16;	//0xCC882044
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_17_T                   reg_decon_ctrl_17;	//0xCC882048
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_18_T                   reg_decon_ctrl_18;	//0xCC88204C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_19_T                   reg_decon_ctrl_19;	//0xCC882050
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_20_T                   reg_decon_ctrl_20;	//0xCC882054
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_21_T                   reg_decon_ctrl_21;	//0xCC882058
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_22_T                   reg_decon_ctrl_22;	//0xCC88205C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_23_T                   reg_decon_ctrl_23;	//0xCC882060
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL0_T       reg_dec_sync_2dly_ctrl0;	//0xCC882064
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL1_T       reg_dec_sync_2dly_ctrl1;	//0xCC882068
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL2_T       reg_dec_sync_2dly_ctrl2;	//0xCC88206C
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL3_T       reg_dec_sync_2dly_ctrl3;	//0xCC882070
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL4_T       reg_dec_sync_2dly_ctrl4;	//0xCC882074
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL5_T       reg_dec_sync_2dly_ctrl5;	//0xCC882078
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL6_T       reg_dec_sync_2dly_ctrl6;	//0xCC88207C
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL7_T       reg_dec_sync_2dly_ctrl7;	//0xCC882080
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL8_T       reg_dec_sync_2dly_ctrl8;	//0xCC882084
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRL9_T       reg_dec_sync_2dly_ctrl9;	//0xCC882088
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_2DLY_CTRLA_T       reg_dec_sync_2dly_ctrla;	//0xCC88208C
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_0_T       reg_decon_winctrl_odd_0;	//0xCC882090
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_1_T       reg_decon_winctrl_odd_1;	//0xCC882094
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_2_T       reg_decon_winctrl_odd_2;	//0xCC882098
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_3_T       reg_decon_winctrl_odd_3;	//0xCC88209C
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_4_T       reg_decon_winctrl_odd_4;	//0xCC8820A0
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_5_T       reg_decon_winctrl_odd_5;	//0xCC8820A4
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_6_T       reg_decon_winctrl_odd_6;	//0xCC8820A8
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_7_T       reg_decon_winctrl_odd_7;	//0xCC8820AC
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_8_T       reg_decon_winctrl_odd_8;	//0xCC8820B0
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_ODD_9_T       reg_decon_winctrl_odd_9;	//0xCC8820B4
	BE_O26A0_REG_CCO_DEC_REG_DEC_SYNC_3DLY_CTRLA_T       reg_dec_sync_3dly_ctrla;	//0xCC8820B8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_24_T                   reg_decon_ctrl_24;	//0xCC8820BC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_25_T                   reg_decon_ctrl_25;	//0xCC8820C0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_26_T                   reg_decon_ctrl_26;	//0xCC8820C4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_27_T                   reg_decon_ctrl_27;	//0xCC8820C8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_28_T                   reg_decon_ctrl_28;	//0xCC8820CC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_29_T                   reg_decon_ctrl_29;	//0xCC8820D0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_30_T                   reg_decon_ctrl_30;	//0xCC8820D4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_31_T                   reg_decon_ctrl_31;	//0xCC8820D8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_32_T                   reg_decon_ctrl_32;	//0xCC8820DC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_33_T                   reg_decon_ctrl_33;	//0xCC8820E0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_34_T                   reg_decon_ctrl_34;	//0xCC8820E4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_35_T                   reg_decon_ctrl_35;	//0xCC8820E8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_36_T                   reg_decon_ctrl_36;	//0xCC8820EC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_37_T                   reg_decon_ctrl_37;	//0xCC8820F0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_38_T                   reg_decon_ctrl_38;	//0xCC8820F4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_39_T                   reg_decon_ctrl_39;	//0xCC8820F8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_40_T                   reg_decon_ctrl_40;	//0xCC8820FC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_41_T                   reg_decon_ctrl_41;	//0xCC882100
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_42_T                   reg_decon_ctrl_42;	//0xCC882104
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_43_T                   reg_decon_ctrl_43;	//0xCC882108
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_44_T                   reg_decon_ctrl_44;	//0xCC88210C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_45_T                   reg_decon_ctrl_45;	//0xCC882110
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_46_T                   reg_decon_ctrl_46;	//0xCC882114
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_47_T                   reg_decon_ctrl_47;	//0xCC882118
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_48_T                   reg_decon_ctrl_48;	//0xCC88211C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_49_T                   reg_decon_ctrl_49;	//0xCC882120
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_50_T                   reg_decon_ctrl_50;	//0xCC882124
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_51_T                   reg_decon_ctrl_51;	//0xCC882128
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_52_T                   reg_decon_ctrl_52;	//0xCC88212C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_53_T                   reg_decon_ctrl_53;	//0xCC882130
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_54_T                   reg_decon_ctrl_54;	//0xCC882134
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_55_T                   reg_decon_ctrl_55;	//0xCC882138
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_56_T                   reg_decon_ctrl_56;	//0xCC88213C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_57_T                   reg_decon_ctrl_57;	//0xCC882140
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_58_T                   reg_decon_ctrl_58;	//0xCC882144
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_59_T                   reg_decon_ctrl_59;	//0xCC882148
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_60_T                   reg_decon_ctrl_60;	//0xCC88214C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_61_T                   reg_decon_ctrl_61;	//0xCC882150
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_62_T                   reg_decon_ctrl_62;	//0xCC882154
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_63_T                   reg_decon_ctrl_63;	//0xCC882158
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_64_T                   reg_decon_ctrl_64;	//0xCC88215C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_65_T                   reg_decon_ctrl_65;	//0xCC882160
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_66_T                   reg_decon_ctrl_66;	//0xCC882164
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_67_T                   reg_decon_ctrl_67;	//0xCC882168
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_68_T                   reg_decon_ctrl_68;	//0xCC88216C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_69_T                   reg_decon_ctrl_69;	//0xCC882170
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_70_T                   reg_decon_ctrl_70;	//0xCC882174
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_71_T                   reg_decon_ctrl_71;	//0xCC882178
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_72_T                   reg_decon_ctrl_72;	//0xCC88217C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_73_T                   reg_decon_ctrl_73;	//0xCC882180
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_74_T                   reg_decon_ctrl_74;	//0xCC882184
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_75_T                   reg_decon_ctrl_75;	//0xCC882188
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_76_T                   reg_decon_ctrl_76;	//0xCC88218C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_77_T                   reg_decon_ctrl_77;	//0xCC882190
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_78_T                   reg_decon_ctrl_78;	//0xCC882194
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_79_T                   reg_decon_ctrl_79;	//0xCC882198
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_80_T                   reg_decon_ctrl_80;	//0xCC88219C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_81_T                   reg_decon_ctrl_81;	//0xCC8821A0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_82_T                   reg_decon_ctrl_82;	//0xCC8821A4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_83_T                   reg_decon_ctrl_83;	//0xCC8821A8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_84_T                   reg_decon_ctrl_84;	//0xCC8821AC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_85_T                   reg_decon_ctrl_85;	//0xCC8821B0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_86_T                   reg_decon_ctrl_86;	//0xCC8821B4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_87_T                   reg_decon_ctrl_87;	//0xCC8821B8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_88_T                   reg_decon_ctrl_88;	//0xCC8821BC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_89_T                   reg_decon_ctrl_89;	//0xCC8821C0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_90_T                   reg_decon_ctrl_90;	//0xCC8821C4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_91_T                   reg_decon_ctrl_91;	//0xCC8821C8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_92_T                   reg_decon_ctrl_92;	//0xCC8821CC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_93_T                   reg_decon_ctrl_93;	//0xCC8821D0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_94_T                   reg_decon_ctrl_94;	//0xCC8821D4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_95_T                   reg_decon_ctrl_95;	//0xCC8821D8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_96_T                   reg_decon_ctrl_96;	//0xCC8821DC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_97_T                   reg_decon_ctrl_97;	//0xCC8821E0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_98_T                   reg_decon_ctrl_98;	//0xCC8821E4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_99_T                   reg_decon_ctrl_99;	//0xCC8821E8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_100_T                 reg_decon_ctrl_100;	//0xCC8821EC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_101_T                 reg_decon_ctrl_101;	//0xCC8821F0
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_102_T                 reg_decon_ctrl_102;	//0xCC8821F4
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_103_T                 reg_decon_ctrl_103;	//0xCC8821F8
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_104_T                 reg_decon_ctrl_104;	//0xCC8821FC
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_105_T                 reg_decon_ctrl_105;	//0xCC882200
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_106_T                 reg_decon_ctrl_106;	//0xCC882204
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_107_T                 reg_decon_ctrl_107;	//0xCC882208
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_108_T                 reg_decon_ctrl_108;	//0xCC88220C
	BE_O26A0_REG_CCO_DEC_REG_DECON_CTRL_109_T                 reg_decon_ctrl_109;	//0xCC882210
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_0_T       reg_decon_winctrl_evn_0;	//0xCC882214
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_1_T       reg_decon_winctrl_evn_1;	//0xCC882218
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_2_T       reg_decon_winctrl_evn_2;	//0xCC88221C
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_3_T       reg_decon_winctrl_evn_3;	//0xCC882220
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_4_T       reg_decon_winctrl_evn_4;	//0xCC882224
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_5_T       reg_decon_winctrl_evn_5;	//0xCC882228
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_6_T       reg_decon_winctrl_evn_6;	//0xCC88222C
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_7_T       reg_decon_winctrl_evn_7;	//0xCC882230
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_8_T       reg_decon_winctrl_evn_8;	//0xCC882234
	BE_O26A0_REG_CCO_DEC_REG_DECON_WINCTRL_EVN_9_T       reg_decon_winctrl_evn_9;	//0xCC882238
}BE_O26A0_REG_CCO_DEC_T;

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
}BE_O26A0_REG_CC_PE_PCC_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881414 RW 0x0000_1000
	UINT32 reg_pcc_coef0                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef1                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881418 RW 0x0000_0000
	UINT32 reg_pcc_coef2                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef3                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88141C RW 0x0000_1000
	UINT32 reg_pcc_coef4                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef5                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881420 RW 0x0000_0000
	UINT32 reg_pcc_coef6                    :15;	//(14:0,NA,0x0000) //
	UINT32 resvd0                           :1;
	UINT32 reg_pcc_coef7                    :15;	//(30:16,NA,0x0000) //
	UINT32 resvd1                           :1;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881424 RW 0x0000_1000
	UINT32 reg_pcc_coef8                    :15;	//(14:0,NA,0x1000) //
	UINT32 resvd                            :17;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881428 RW 0x0300_03FF
	UINT32 reg_sat_x3_i                     :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x2_i                     :10;	//(25:16,NA,0x300) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88142C RW 0x0000_0100
	UINT32 reg_sat_x1_i                     :10;	//(9:0,NA,0x100) //
	UINT32 resvd0                           :6;
	UINT32 reg_sat_x0_i                     :10;	//(25:16,NA,0x0) //
	UINT32 resvd1                           :6;
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF6_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881430 RW 0xFFFF_FFFF
	UINT32 reg_sat_y3_i                     :8;	//(7:0,NA,0xFF) //
	UINT32 reg_sat_y2_i                     :8;	//(15:8,NA,0xFF) //
	UINT32 reg_sat_y1_i                     :8;	//(23:16,NA,0xFF) //
	UINT32 reg_sat_y0_i                     :8;	//(31:24,NA,0xFF) //
	};
}BE_O26A0_REG_CC_PE1_PCC_COEF7_T;

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
}BE_O26A0_REG_CC_PE1_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881438 RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :12;	//(11:0,NA,0x0) //12 bit odd LUT data
	UINT32 resvd0                           :4;
	UINT32 oetf_lut_data_e                  :12;	//(27:16,NA,0x0) //12 bit even LUT data
	UINT32 resvd1                           :4;
	};
}BE_O26A0_REG_CC_PE1_OETF_IA_DATA_T;

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
}BE_O26A0_REG_CC_PE1_EOTF_WDATA_T;

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
}BE_O26A0_REG_CC_PE1_EOTF_WDONE_T;

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
}BE_O26A0_REG_CC_PE1_EOTF_RDATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881448 RO 0x0000_0000
	UINT32 eotf_buf_rw_conflict             :1;	//(0,RO,0x00) //
	UINT32 eotf_lut_cpy_done                :1;	//(1,RO,0x00) //
	UINT32 eotf_lut_cpy_status              :2;	//(3:2,RO,0x0) //
	UINT32 resvd                            :28;
	};
}BE_O26A0_REG_CC_PE1_EOTF_RSATUS_T;

typedef struct {
	BE_O26A0_REG_CC_PE_PCC_CTRL_T                                    pe_pcc_ctrl;	//0xCC881410
	BE_O26A0_REG_CC_PE1_PCC_COEF0_T                                pe1_pcc_coef0;	//0xCC881414
	BE_O26A0_REG_CC_PE1_PCC_COEF1_T                                pe1_pcc_coef1;	//0xCC881418
	BE_O26A0_REG_CC_PE1_PCC_COEF2_T                                pe1_pcc_coef2;	//0xCC88141C
	BE_O26A0_REG_CC_PE1_PCC_COEF3_T                                pe1_pcc_coef3;	//0xCC881420
	BE_O26A0_REG_CC_PE1_PCC_COEF4_T                                pe1_pcc_coef4;	//0xCC881424
	BE_O26A0_REG_CC_PE1_PCC_COEF5_T                                pe1_pcc_coef5;	//0xCC881428
	BE_O26A0_REG_CC_PE1_PCC_COEF6_T                                pe1_pcc_coef6;	//0xCC88142C
	BE_O26A0_REG_CC_PE1_PCC_COEF7_T                                pe1_pcc_coef7;	//0xCC881430
	BE_O26A0_REG_CC_PE1_OETF_IA_CTRL_T                          pe1_oetf_ia_ctrl;	//0xCC881434
	BE_O26A0_REG_CC_PE1_OETF_IA_DATA_T                          pe1_oetf_ia_data;	//0xCC881438
	BE_O26A0_REG_CC_PE1_EOTF_WDATA_T                              pe1_eotf_wdata;	//0xCC88143C
	BE_O26A0_REG_CC_PE1_EOTF_WDONE_T                              pe1_eotf_wdone;	//0xCC881440
	BE_O26A0_REG_CC_PE1_EOTF_RDATA_T                              pe1_eotf_rdata;	//0xCC881444
	BE_O26A0_REG_CC_PE1_EOTF_RSATUS_T                            pe1_eotf_rsatus;	//0xCC881448
}BE_O26A0_REG_CC_PE_PCC_T;

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
}BE_O26A0_REG_CC_PCC_WINCTRL_00_T;

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
}BE_O26A0_REG_CC_PCC_WINCTRL_01_T;

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
}BE_O26A0_REG_CC_PCC_WINCTRL_02_T;

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
}BE_O26A0_REG_CC_PCC_WINCTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881510 RW 0x0000_0000
	UINT32 win0_w0_x0                       :14;	//(13:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y0                       :14;	//(29:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881514 RW 0x0000_0000
	UINT32 win0_w0_x1                       :14;	//(13:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y1                       :14;	//(29:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881518 RW 0x0000_0000
	UINT32 win1_w0_x0                       :14;	//(13:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y0                       :14;	//(29:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88151C RW 0x0000_0000
	UINT32 win1_w0_x1                       :14;	//(13:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y1                       :14;	//(29:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881520 RW 0x0000_0000
	UINT32 win2_w0_x0                       :14;	//(13:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y0                       :14;	//(29:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881524 RW 0x0000_0000
	UINT32 win2_w0_x1                       :14;	//(13:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y1                       :14;	//(29:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881528 RW 0x0000_0000
	UINT32 win3_w0_x0                       :14;	//(13:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y0                       :14;	//(29:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88152C RW 0x0000_0000
	UINT32 win3_w0_x1                       :14;	//(13:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y1                       :14;	//(29:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881530 RW 0x0000_0000
	UINT32 win0_w0_x0                       :14;	//(13:0,NA,0x0) //win0_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y0                       :14;	//(29:16,NA,0x0) //win0_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881534 RW 0x0000_0000
	UINT32 win0_w0_x1                       :14;	//(13:0,NA,0x0) //win0_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win0_w0_y1                       :14;	//(29:16,NA,0x0) //win0_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881538 RW 0x0000_0000
	UINT32 win1_w0_x0                       :14;	//(13:0,NA,0x0) //win1_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y0                       :14;	//(29:16,NA,0x0) //win1_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88153C RW 0x0000_0000
	UINT32 win1_w0_x1                       :14;	//(13:0,NA,0x0) //win1_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win1_w0_y1                       :14;	//(29:16,NA,0x0) //win1_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881540 RW 0x0000_0000
	UINT32 win2_w0_x0                       :14;	//(13:0,NA,0x0) //win2_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y0                       :14;	//(29:16,NA,0x0) //win2_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881544 RW 0x0000_0000
	UINT32 win2_w0_x1                       :14;	//(13:0,NA,0x0) //win2_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win2_w0_y1                       :14;	//(29:16,NA,0x0) //win2_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881548 RW 0x0000_0000
	UINT32 win3_w0_x0                       :14;	//(13:0,NA,0x0) //win3_w0_x0
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y0                       :14;	//(29:16,NA,0x0) //win3_w0_y0
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC88154C RW 0x0000_0000
	UINT32 win3_w0_x1                       :14;	//(13:0,NA,0x0) //win3_w0_x1 : 1920(7680/4p)-1
	UINT32 resvd0                           :2;
	UINT32 win3_w0_y1                       :14;	//(29:16,NA,0x0) //win3_w0_y1 : 4320
	UINT32 resvd1                           :2;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC881550 RW 0x0000_00E4
	UINT32 reg_priority_sel0                :2;	//(1:0,NA,0x0) //win prioirty sel 0(highest~3(lowest):win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel1                :2;	//(3:2,NA,0x1) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel2                :2;	//(5:4,NA,0x2) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 reg_priority_sel3                :2;	//(7:6,NA,0x3) //win prioirty sel 0(highest~3(lowest)0:win0 1:win1 2:win2 3:win3
	UINT32 resvd                            :24;
	};
}BE_O26A0_REG_CC_PCC_WINCTRL_20_T;

typedef struct {
	BE_O26A0_REG_CC_PCC_WINCTRL_00_T                              pcc_winctrl_00;	//0xCC881500
	BE_O26A0_REG_CC_PCC_WINCTRL_01_T                              pcc_winctrl_01;	//0xCC881504
	BE_O26A0_REG_CC_PCC_WINCTRL_02_T                              pcc_winctrl_02;	//0xCC881508
	BE_O26A0_REG_CC_PCC_WINCTRL_03_T                              pcc_winctrl_03;	//0xCC88150C
	BE_O26A0_REG_CC_PCC_WINCTRL_04_T                              pcc_winctrl_04;	//0xCC881510
	BE_O26A0_REG_CC_PCC_WINCTRL_05_T                              pcc_winctrl_05;	//0xCC881514
	BE_O26A0_REG_CC_PCC_WINCTRL_06_T                              pcc_winctrl_06;	//0xCC881518
	BE_O26A0_REG_CC_PCC_WINCTRL_07_T                              pcc_winctrl_07;	//0xCC88151C
	BE_O26A0_REG_CC_PCC_WINCTRL_08_T                              pcc_winctrl_08;	//0xCC881520
	BE_O26A0_REG_CC_PCC_WINCTRL_09_T                              pcc_winctrl_09;	//0xCC881524
	BE_O26A0_REG_CC_PCC_WINCTRL_10_T                              pcc_winctrl_10;	//0xCC881528
	BE_O26A0_REG_CC_PCC_WINCTRL_11_T                              pcc_winctrl_11;	//0xCC88152C
	BE_O26A0_REG_CC_PCC_WINCTRL_12_T                              pcc_winctrl_12;	//0xCC881530
	BE_O26A0_REG_CC_PCC_WINCTRL_13_T                              pcc_winctrl_13;	//0xCC881534
	BE_O26A0_REG_CC_PCC_WINCTRL_14_T                              pcc_winctrl_14;	//0xCC881538
	BE_O26A0_REG_CC_PCC_WINCTRL_15_T                              pcc_winctrl_15;	//0xCC88153C
	BE_O26A0_REG_CC_PCC_WINCTRL_16_T                              pcc_winctrl_16;	//0xCC881540
	BE_O26A0_REG_CC_PCC_WINCTRL_17_T                              pcc_winctrl_17;	//0xCC881544
	BE_O26A0_REG_CC_PCC_WINCTRL_18_T                              pcc_winctrl_18;	//0xCC881548
	BE_O26A0_REG_CC_PCC_WINCTRL_19_T                              pcc_winctrl_19;	//0xCC88154C
	BE_O26A0_REG_CC_PCC_WINCTRL_20_T                              pcc_winctrl_20;	//0xCC881550
}BE_O26A0_REG_CC_PCC_WINCTRL_T;

//#define BE_BE_O26A0_REG_L3D_L3D_CORE_CTRL_T_BASE		0xCC880F00
typedef union {
	UINT32 udata32;
	struct {						//0xCC880F00 RW 0x0000_0110
	UINT32 reg_l3d_en                       :1;	//(0:0,NA,0) //3D-LUT on/off	0 : off	1 : on
	UINT32 reg_interp_mode                  :1;	//(1:1,NA,0) //Interpolation mode	0 : tetrahedral	1 : tri-linear
	UINT32 resvd0                           :2;
	UINT32 reg_run_core_sel                 :1;	//(4:4,NA,1) //L3D on: normal operation (normal read only)	0 : 33x33x33 (only 9x9x9 can HIF access)	1 : 9x9x9 (only 33x33x33 can HIF access)	L3D off: only HIF access	0 : 9x9x9 (if 1: HIF off)	1 : 33x33x33 (if 0: HIF off)
	UINT32 reg_lut_wr_core_sel              :1;	//(5:5,NA,0) //LUT write/read core selection	(Invalid if core is running in normal operation mode)	0 : 33x33x33	1 : 9x9x9
	UINT32 reg_lut_wr_sel                   :1;	//(6:6,NA,0) //LUT write/read selection	(Valid only if reg_lut_wr_toggle = 0)	0 : write	1 : read
	UINT32 reg_lut_wr_toggle                :1;	//(7:7,NA,0) //Auto clear (wr_sel toggle)
	UINT32 reg_lut_auto_mapping             :1;	//(8:8,NA,1) //9x9x9 core LUT write address auto mapping mode	0 : disable (for using 9x9x9 LUT rom)	1 : enable (for auto mapping 33x33x33 LUT rom to 9x9x9 LUT)
	UINT32 resvd1                           :23;
	};
}BE_O26A0_REG_L3D_L3D_CORE_CTRL_00_T;

typedef struct {
	BE_O26A0_REG_L3D_L3D_CORE_CTRL_00_T                         l3d_core_ctrl_00;	//0xCC880F00
}BE_O26A0_REG_L3D_L3D_CORE_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC880450 RW 0x0000_0000
	UINT32 reg_gsr_blend_en                 :1;	//(0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_gsr_debug_sel                :4;	//(7:4,RW,0x0) //0:debug off, 1:final_gain, 2:crnt_gain, 3:sat_gain, 4:val_gain, others:debug off
	UINT32 resvd1                           :8;
	UINT32 reg_gsr_master_gain              :10;	//(25:16,RW,0x0) //
	UINT32 resvd2                           :6;
	};
}BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL00_T;

typedef struct {
	BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL00_T          reg_osd0_gsr_ctrl00;	//0xCC860450
}BE_O26A0_REG_OSD_IMAGE0_1_REG_OSD0_GSR_CTRL_T;

#endif
