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

#ifndef _PE_DPE_REG_O24A0_H_
#define _PE_DPE_REG_O24A0_H_

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3800 RW 0x0F00_0870
	UINT32 reg_hei                          :12;	//(11:0,RW,0x870) //
	UINT32 resvd0                           :4;
	UINT32 reg_wid                          :12;	//(27:16,RW,0xF00) //
	UINT32 resvd1                           :3;
	UINT32 reg_decon_detour_en              :1;	//(31,RW,0x0) //1: detour
	};
}PE_O24_REG_LED_DECON_TOP_CTRL_T;

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
}PE_O24_REG_LED_DECON_CTRL_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3808 RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_yy        :12;	//(23:12,RW,0x0) //
	UINT32 reg_input_alpha                  :8;	//(31:24,RW,0x0) //
	};
}PE_O24_REG_LED_DECON_CTRL_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E380C RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_yy        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_min_pel_cr        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :7;
	UINT32 reg_init_rst_off                 :1;	//(31,RW,0x0) //1 : pic_init reset(initial register) off	0: normal mode
	};
}PE_O24_REG_LED_DECON_CTRL_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3810 RW 0x0000_0000
	UINT32 reg_1st_out_rd_max_pel_cr        :12;	//(11:0,RW,0x0) //
	UINT32 reg_1st_out_rd_max_pel_cb        :12;	//(23:12,RW,0x0) //
	UINT32 resvd                            :8;
	};
}PE_O24_REG_LED_DECON_CTRL_3_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3814 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,0x0) //
	};
}PE_O24_REG_LED_DECON_CTRL_4_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3818 RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,0x0) //
	};
}PE_O24_REG_LED_DECON_CTRL_5_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E381C RW 0x0000_0000
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,0x0) //
	};
}PE_O24_REG_LED_DECON_CTRL_6_T;

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
}PE_O24_REG_LED_DECON_CTRL_7_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3824 RW 0x0000_0000
	UINT32 reg_rd_roi_x1                    :12;	//(11:0,NA,0x1B0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_x0                    :12;	//(27:16,NA,0x5B) //
	UINT32 resvd1                           :4;
	};
}PE_O24_REG_LED_DECON_CTRL_8_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3828 RW 0x0000_0000
	UINT32 reg_rd_roi_y1                    :12;	//(11:0,NA,0x1B0) //
	UINT32 resvd0                           :4;
	UINT32 reg_rd_roi_y0                    :12;	//(27:16,NA,0x6A) //
	UINT32 resvd1                           :4;
	};
}PE_O24_REG_LED_DECON_CTRL_9_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E382C RW 0x01E0_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //
	UINT32 resvd                            :12;
	};
}PE_O24_REG_LED_DECON_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3830 RW 0x0280_A032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //
	UINT32 resvd                            :12;
	};
}PE_O24_REG_LED_DECON_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3834 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3838 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E383C RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3840 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3844 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC8E3848 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //
	UINT32 resvd1                           :10;
	};
}PE_O24_REG_LED_DECON_CTRL_17_T;

typedef struct {
	PE_O24_REG_LED_DECON_TOP_CTRL_T               reg_decon_top_ctrl;	//0xCC8E3800
	PE_O24_REG_LED_DECON_CTRL_0_T                   reg_decon_ctrl_0;	//0xCC8E3804
	PE_O24_REG_LED_DECON_CTRL_1_T                   reg_decon_ctrl_1;	//0xCC8E3808
	PE_O24_REG_LED_DECON_CTRL_2_T                   reg_decon_ctrl_2;	//0xCC8E380C
	PE_O24_REG_LED_DECON_CTRL_3_T                   reg_decon_ctrl_3;	//0xCC8E3810
	PE_O24_REG_LED_DECON_CTRL_4_T                   reg_decon_ctrl_4;	//0xCC8E3814
	PE_O24_REG_LED_DECON_CTRL_5_T                   reg_decon_ctrl_5;	//0xCC8E3818
	PE_O24_REG_LED_DECON_CTRL_6_T                   reg_decon_ctrl_6;	//0xCC8E381C
	PE_O24_REG_LED_DECON_CTRL_7_T                   reg_decon_ctrl_7;	//0xCC8E3820
	PE_O24_REG_LED_DECON_CTRL_8_T                   reg_decon_ctrl_8;	//0xCC8E3824
	PE_O24_REG_LED_DECON_CTRL_9_T                   reg_decon_ctrl_9;	//0xCC8E3828
	PE_O24_REG_LED_DECON_CTRL_10_T                 reg_decon_ctrl_10;	//0xCC8E382C
	PE_O24_REG_LED_DECON_CTRL_11_T                 reg_decon_ctrl_11;	//0xCC8E3830
	PE_O24_REG_LED_DECON_CTRL_12_T                 reg_decon_ctrl_12;	//0xCC8E3834
	PE_O24_REG_LED_DECON_CTRL_13_T                 reg_decon_ctrl_13;	//0xCC8E3838
	PE_O24_REG_LED_DECON_CTRL_14_T                 reg_decon_ctrl_14;	//0xCC8E383C
	PE_O24_REG_LED_DECON_CTRL_15_T                 reg_decon_ctrl_15;	//0xCC8E3840
	PE_O24_REG_LED_DECON_CTRL_16_T                 reg_decon_ctrl_16;	//0xCC8E3844
	PE_O24_REG_LED_DECON_CTRL_17_T                 reg_decon_ctrl_17;	//0xCC8E3848
}PE_LED_DCNT_REG_O24_T;

#endif

