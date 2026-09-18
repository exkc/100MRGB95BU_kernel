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
#ifndef _PE_HDR_REG_M23A0_H_
#define _PE_HDR_REG_M23A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCC620800 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0:0,RW,0x00) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1:1,RW,0x00) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2:2,RW,0x00) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_M23_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620804 RW 0x0870_0F00
	UINT32 width                            :16;	//(15:0,RW,0xF00) //width
	UINT32 height                           :16;	//(31:16,RW,0x870) //height
	};
}PE_M23_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620808 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,RW,0x0000_0014) //vdpulse position for register loading
	};
}PE_M23_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62080C RO 0x0000_0000
	UINT32 vcnt                             :16;	//(15:0,RO,0x0) //vertical line count
	UINT32 vcnt2                            :16;	//(31:16,RO,0x0) //vertical line number
	};
}PE_M23_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620810 RO 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,RO,0x0800) //apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//(30:30,RO,0x00) //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//(31:31,RO,0x00) //Vertical Active at PE1 output(Read only)
	};
}PE_M23_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620814 RW 0x0000_0000
	UINT32 reg_hue_sat_prsv_ref             :1;	//(0:0,RW,0x0) //0: hue/sat ref source from pcc32 output	1: hue/sat ref source from lg gamma output
	UINT32 resvd0                           :3;
	UINT32 reg_tcm_inp_src                  :1;	//(4:4,RW,0x0) //0: Tone Map input source = OETF Out 	1: Tone Map input source = OETF Input
	UINT32 resvd1                           :3;
	UINT32 reg_hdr10_cuva_gain_mode         :2;	//(9:8,RW,0x0) //0 : Saturation Mapping gain from HDR10+ Tone Mapping LUT	1 : Saturation Mapping gain from CUVA PQ SRC (in max rgb)	2 : Saturation Mapping gain from CUVA HLG SRC (pcc32 luma)	3 : Saturation Mapping gain from CUVA PQ SRC (in luma)
	UINT32 resvd2                           :6;
	UINT32 reg_hue_sat_prsv_src             :2;	//(17:16,RW,0x0) //(deprecated)
	UINT32 resvd3                           :2;
	UINT32 reg_hist_src                     :4;	//(23:20,RW,0x0) //1:R, 2:G, 3:B, 4:MAX(RGB)	5:Y, 6:Cb, 7:Cr	8:Technicolor G, 9: Technicolor B, 10 : Technicolor R	11: Technicolor MAX(RGB)	15: MAX(YCbCr) Others: Y
	UINT32 reg_eotf_en                      :1;	//(24:24,RW,0x1) //EOTF block enable
	UINT32 reg_oetf_en                      :1;	//(25:25,RW,0x0) //OETF block enable
	UINT32 resvd4                           :2;
	UINT32 reg_hdr10p_mode                  :1;	//(28:28,RW,0x00) //0: HDR10 Mode	1: HDR10+ Mode
	UINT32 reg_use_equal_llut_en            :1;	//(29:29,RW,0x00) //0:use luminanace LUT channel G hif, 	1:use own LUT hif(B/R)(WR only)
	UINT32 reg_hdr10_mode                   :1;	//(30:30,RW,0x0) //0: Bypass HDR10 Path	1: Run HDR10
	UINT32 resvd5                           :1;
	};
}PE_M23_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620818 RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 reg_eotf_same_write_mode         :1;	//(1:1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 EOTF mem(s)
	UINT32 resvd1                           :6;
	UINT32 reg_eotf_dbuf_wptr               :1;	//(8:8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_eotf_dbuf_rptr               :1;	//(12:12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_eotf_dbuf_ptr_imode          :1;	//(16:16,RW,0x00) //1: eotf_rptr = ~ eotf_wptr (ignore [12] bit)
	UINT32 resvd4                           :15;
	};
}PE_M23_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62081C RW 0x0000_0000
	UINT32 resvd0                           :1;
	UINT32 reg_oetf_same_write_mode         :1;	//(1:1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 OETF mem(s)
	UINT32 resvd1                           :6;
	UINT32 reg_oetf_dbuf_wptr               :1;	//(8:8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_oetf_dbuf_rptr               :1;	//(12:12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_oetf_dbuf_ptr_imode          :1;	//(16:16,RW,0x00) //1: oetf_rptr = ~ oetf_wptr (ignore [13] bit)
	UINT32 resvd4                           :15;
	};
}PE_M23_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620850 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0:0,RW,0x01) //
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620854 RW 0x12AF_7CFE
	UINT32 r_csc1st_coef1                   :15;	//(14:0,RW,0x7CFE) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620858 RW 0x7590_12AF
	UINT32 r_csc1st_coef3                   :15;	//(14:0,RW,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,RW,0x7590) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62085C RW 0x225F_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,RW,0x225F) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620860 RW 0x12AF_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620864 RW 0x1AF0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,RW,0x1AF0) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620868 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,RW,0x0600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,RW,0x07C0) //
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62086C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,RW,0x0600) //
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620870 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,RW,0x00) //
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620874 RW 0x0000_0000
	UINT32 r_csc1st_dbg_en                  :1;	//(0:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 r_csc1st_dbg_ugy                 :4;	//(7:4,RW,0x00) //underflowed bit gy upper 4 bit
	UINT32 r_csc1st_dbg_ucb                 :4;	//(11:8,RW,0x00) //underflowed bit cb upper 4 bit
	UINT32 r_csc1st_dbg_ucr                 :4;	//(15:12,RW,0x00) //underflowed bit cr upper 4 bit
	UINT32 resvd1                           :4;
	UINT32 r_csc1st_dbg_ogy                 :4;	//(23:20,RW,0x00) //overflowed bit gy upper 4 bit
	UINT32 r_csc1st_dbg_ocb                 :4;	//(27:24,RW,0x00) //overflowed bit cb upper 4 bit
	UINT32 r_csc1st_dbg_ocr                 :4;	//(31:28,RW,0x00) //overflowed bit cr upper 4 bit
	};
}PE_M23_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620878 RO 0x0000_0000
	UINT32 ireg_csc_cnt_under               :16;	//(15:0,RO,0x0) //
	UINT32 ireg_csc_cnt_over                :16;	//(31:16,RO,0x0) //
	};
}PE_M23_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620880 RW 0x0000_FFFF
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
	UINT32 r_pxl_rd_mark_en                 :1;	//(24:24,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//(28:28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_M23_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620884 RW 0x0000_0000
	UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_M23_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620888 RO 0x0000_0000
	UINT32 pxl_read_rcr                     :10;	//(9:0,RO,0x00) //
	UINT32 pxl_read_bcb                     :10;	//(19:10,RO,0x00) //
	UINT32 pxl_read_gyy                     :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_PXL_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620890 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_M23_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620894 RW 0x0000_0000
	UINT32 eotf_lut_data                    :32;	//(31:0,RW,0x0000_0000) //32 bit LUT data
	};
}PE_M23_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620898 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_M23_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62089C RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :16;	//(15:0,RW,0x0) //16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//(31:16,RW,0x0) //16 bit even LUT data
	};
}PE_M23_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208A0 RW 0x0000_0001
	UINT32 reg_pcc_en                       :1;	//(0,RW,0x1) //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208A4 RW 0x1220_7FDE
	UINT32 r_pcc_coef1                      :15;	//(14:0,RW,0x7FDE) //PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//(30:16,RW,0x1220) //PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208A8 RW 0x7E02_7E64
	UINT32 r_pcc_coef3                      :15;	//(14:0,RW,0x7E64) //PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//(30:16,RW,0x7E02) //PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208AC RW 0x11E6_7FB6
	UINT32 r_pcc_coef5                      :15;	//(14:0,RW,0x7FB6) //PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//(30:16,RW,0x11E6) //PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208B0 RW 0x7F10_7ED6
	UINT32 r_pcc_coef7                      :15;	//(14:0,RW,0x7ED6) //PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//(30:16,RW,0x7F10) //PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208B4 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//(30:16,RW,0x1A91) //PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208D0 RW 0x0000_3FF3
	UINT32 reg_hue_prsv_en                  :1;	//(0,RW,0x1) //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//(1,RW,0x1) //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//(13:4,RW,0x3FF) //0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//(25:16,RW,0x000) //0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_M23_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208D4 NA 0x0000_1000
	UINT32 reg_inp_l_sel                    :1;	//(0,RW,0x0) //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//(4,RW,0x0) //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//(8,RW,0x0) //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//(12,RW,0x1) //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_M23_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208E0 RW 0x121F_7FDE
	UINT32 r_tone_map_rgb2y_coef1           :15;	//(14:0,RW,0x7FDE) //
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//(30:16,RW,0x121F) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208E4 RW 0x7E02_0000
	UINT32 r_tone_map_rgbymax_sel           :3;	//(2:0,RW,0x0) //
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//(30:16,RW,0x7E02) //
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208E8 RW 0x0000_0000
	UINT32 ll_lut_addr                      :7;	//(6:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_M23_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208EC RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,RW,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,RW,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208F0 RW 0x1000_03FF
	UINT32 reg_alpha_hue                    :10;	//(9:0,RW,0x3FF) //alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//(25:16,RW,0x00) //alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//(28,RW,0x01) //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_M23_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208F4 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//(16,RW,0x0) //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_M23_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC6208F8 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(30:16,RW,0x0) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620900 RW 0x0000_0001
	UINT32 reg_ll_pcc_en                    :1;	//(0,RW,0x1) //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620904 RW 0x1220_7FDE
	UINT32 r_ll_pcc_coef1                   :15;	//(14:0,RW,0x7FDE) //PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//(30:16,RW,0x1220) //PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620908 RW 0x7E02_7E64
	UINT32 r_ll_pcc_coef3                   :15;	//(14:0,RW,0x7E64) //PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//(30:16,RW,0x7E02) //PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62090C RW 0x11E6_7FB6
	UINT32 r_ll_pcc_coef5                   :15;	//(14:0,RW,0x7FB6) //PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//(30:16,RW,0x11E6) //PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620910 RW 0x7F10_7ED6
	UINT32 r_ll_pcc_coef7                   :15;	//(14:0,RW,0x7ED6) //PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//(30:16,RW,0x7F10) //PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620914 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//(30:16,RW,0x1A91) //PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620918 RW 0x0000_0000
	UINT32 reg_ll_ab_en                     :1;	//(0:0,RW,0x0) //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62091C RW 0x0048_000A
	UINT32 r_ll_ab_lut_x2                   :10;	//(9:0,RW,0xA) //
	UINT32 r_ll_ab_lut_x1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_x0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620920 RW 0x00BF_FFFF
	UINT32 r_ll_ab_lut_x5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x3                   :10;	//(29:20,RW,0xB) //
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620924 RW 0x0000_2600
	UINT32 r_ll_ab_lut_y2                   :10;	//(9:0,RW,0x200) //
	UINT32 r_ll_ab_lut_y1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_y0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620928 RW 0x3FFF_FFFF
	UINT32 r_ll_ab_lut_y5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y3                   :10;	//(29:20,RW,0x3FF) //
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620940 RW 0x0000_0000
	UINT32 hist_bin_mode                    :2;	//(1:0,RW,0x00) //"00" : 32 bin mode	others : 16 bin mode
	UINT32 histogram_mode                   :2;	//(3:2,RW,0x00) //"00" : Own side's histogram data use	"01" : Other side's histogram data use	"10" : Average between Own and Other side's histogram data use
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd0                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :6;
	UINT32 hist_clear                       :1;	//(23:23,RW,0x00) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd2                           :8;
	};
}PE_M23_REG_H10_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620944 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620948 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62094C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620950 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620954 RW 0x0000_8000
	UINT32 hif_hist_address                 :7;	//(6:0,RW,0x0) //"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
	UINT32 resvd0                           :5;
	UINT32 hif_hist_ai                      :1;	//(12:12,RW,0x00) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//(15:15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//(18:16,RW,0x00) //"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//(28:28,RW,0x00) //auto increment enable
	UINT32 hif_mask                         :1;	//(29:29,RW,0x00) //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_M23_REG_H10_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620958 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,RW,0x0000_0000) //[22:0]hif_histogram_bin_read
	};
}PE_M23_REG_H10_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62095C RO 0x0000_0000
	UINT32 hist_v_min                       :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_M23_REG_H10_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620970 RW 0x0000_0000
	UINT32 tpg_enable                       :1;	//(0:0,RW,0x00) //Test Pattern Gen. enable
	UINT32 tpg_type                         :2;	//(2:1,RW,0x00) //0: Patch 1: Gradient 2: CMYW 3: RGBW
	UINT32 tpg_cg_disable                   :1;	//(3:3,RW,0x00) //clock gating disable
	UINT32 tpg_blend_alpha                  :4;	//(7:4,RW,0x00) //0: Solid ~ 15 : Background
	UINT32 tpg_grad_en                      :4;	//(11:8,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 tpg_h_grad                       :1;	//(12:12,RW,0x00) //1: window mode enable
	UINT32 resvd0                           :3;
	UINT32 tpg_stride                       :7;	//(22:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :9;
	};
}PE_M23_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620974 RW 0x0438_0780
	UINT32 tpg_size_x                       :14;	//(13:0,RW,0x780) //tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//(28:16,RW,0x438) //tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_M23_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620978 RW 0x0000_0000
	UINT32 tpg_mask_flag                    :16;	//(15:0,RW,0x0000) //
	UINT32 resvd                            :16;
	};
}PE_M23_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC62097C RW 0x0000_0000
	UINT32 tpg_in_out_sel                   :16;	//(15:0,RW,0x0) //in_out_sel
	UINT32 resvd                            :16;
	};
}PE_M23_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620980 RW 0x0000_0000
	UINT32 tpg_color_r                      :10;	//(9:0,RW,0x00) //tpg_color_r
	UINT32 tpg_color_b                      :10;	//(19:10,RW,0x00) //tpg_color_b
	UINT32 tpg_color_g                      :10;	//(29:20,RW,0x00) //tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_M23_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620984 RW 0x0000_8000
	UINT32 hif_tpg_address                  :8;	//(7:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_M23_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620988 RW 0x0000_0000
	UINT32 hif_tpg_wdata_y                  :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A00 RW 0x0000_0000
	UINT32 luminance_lut0_enable            :1;	//(0:0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_M23_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A14 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_M23_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A18 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_M23_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A20 RW 0x0000_8000
	UINT32 hif_llut0_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//(13:13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//(14:14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_M23_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A24 RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A30 RW 0x0000_0000
	UINT32 luminance_lut1_enable            :1;	//(0:0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_M23_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A34 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A38 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A3C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A40 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A44 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_M23_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A48 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_M23_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A50 RW 0x0000_8000
	UINT32 hif_llut1_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//(13:13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//(14:14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_M23_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A54 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A60 RW 0x0000_0000
	UINT32 luminance_lut2_enable            :1;	//(0:0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_M23_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A64 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A68 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A6C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A70 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A74 RW 0xFFFF_FFFF
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//(31:16,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_M23_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A78 RW 0xFFFF_FFFF
	UINT32 hif_llut2_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_M23_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A80 RW 0x0000_8000
	UINT32 hif_llut2_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load_en         :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut2_ai                     :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut2_write_x                :1;	//(13:13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut2_read_x                 :1;	//(14:14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut2_enable                 :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_M23_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A84 RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A90 RW 0x0000_0000
	UINT32 gamma045_enable                  :1;	//(0:0,RW,0x00) //gamma 0.45(1/2.2) enable
	UINT32 resvd0                           :3;
	UINT32 gamma045_mode                    :1;	//(4:4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 gamma045_mux                     :1;	//(8:8,RW,0x00) //
	UINT32 resvd2                           :23;
	};
}PE_M23_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A98 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0:0,RW,0x00) //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//(2:2,RW,0x00) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3:3,RW,0x00) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,RW,0x00) //"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_M23_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620A9C RW 0x0000_0000
	UINT32 hif_pcc32_ygain_shift            :1;	//(0:0,RW,0x0) //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AA0 RW 0x0000_0001
	UINT32 reg_csc3rd_en                    :1;	//(0:0,RW,0x01) //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AA4 RW 0x094A_00D0
	UINT32 r_csc3rd_coef1                   :15;	//(14:0,RW,0x00D0) //CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//(30:16,RW,0x094A) //CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AA8 RW 0x0399_7AF3
	UINT32 r_csc3rd_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//(30:16,RW,0x0399) //CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AAC RW 0x0702_7E0B
	UINT32 r_csc3rd_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AB0 RW 0x798F_7F70
	UINT32 r_csc3rd_coef7                   :15;	//(14:0,RW,0x7F70) //CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//(30:16,RW,0x798F) //CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AB4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AB8 RW 0x0000_0000
	UINT32 r_csc3rd_ofst1                   :11;	//(10:0,RW,0x000) //CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//(26:16,RW,0x000) //CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ABC RW 0x0000_0040
	UINT32 r_csc3rd_ofst3                   :11;	//(10:0,RW,0x040) //CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//(26:16,RW,0x200) //CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AC0 RW 0x0200_0200
	UINT32 r_csc3rd_ofst5                   :11;	//(10:0,RW,0x0200) //CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//(26:16,RW,0x0200) //CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AD0 RW 0x0000_0000
	UINT32 r_slut0_x0                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AD4 RW 0x0000_0000
	UINT32 r_slut0_x1                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AD8 RW 0x0000_0000
	UINT32 r_slut0_x2                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620ADC RW 0x0000_0000
	UINT32 r_slut0_x3                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AE0 RW 0x0000_0000
	UINT32 r_slut0_x4                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AE4 RW 0x0000_0000
	UINT32 r_slut0_x5                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AE8 RW 0x0000_0000
	UINT32 r_slut0_x6                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AEC RW 0x0000_0000
	UINT32 r_slut0_x7                       :32;	//(31:00,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AF0 RW 0x0000_0000
	UINT32 r_slut0_y0                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y1                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y2                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y3                       :8;	//(31:24,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AF4 RW 0x0000_0000
	UINT32 r_slut0_y4                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y5                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y6                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y7                       :8;	//(31:24,RW,0x0) //
	};
}PE_M23_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AF8 RW 0x0000_0000
	UINT32 reg_tm_m2020_coef13              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd                            :1;
	UINT32 reg_tm_m2020_coef22              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 sat_gain_en                      :1;	//(31:31,RW,0x00) //TM0 Saturation Gain Enable
	};
}PE_M23_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620AFC RW 0x0000_0000
	UINT32 reg_tm_m2020_coef23              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm_m2020_coef32              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B20 RW 0x0000_0000
	UINT32 luminance_lut2_enable            :1;	//(0:0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B24 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B28 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B2C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B30 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B34 RW 0xFFFF_1000
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_M23_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B38 RW 0x0000_8000
	UINT32 hif_ygain_lut_address            :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B3C RW 0x0000_0000
	UINT32 hif_ygain_lut_wdata_y            :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B40 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B44 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_M23_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B48 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_M23_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B4C RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_M23_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B60 RW 0x0000_0080
	UINT32 lgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of LGAIN LUT point 0
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B64 RW 0x2492_0080
	UINT32 lgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of LGAIN LUT point 1
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B68 RW 0x4924_0080
	UINT32 lgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of LGAIN LUT point 2
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B6C RW 0x6DB6_0080
	UINT32 lgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of LGAIN LUT point 3
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B70 RW 0x9248_0080
	UINT32 lgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of LGAIN LUT point 4
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B74 RW 0xB6DA_0080
	UINT32 lgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of LGAIN LUT point 5
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B78 RW 0xDB6C_0080
	UINT32 lgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of LGAIN LUT point 6
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B7C RW 0xFFFF_0080
	UINT32 lgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of LGAIN LUT point 7
	};
}PE_M23_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B80 RW 0x0000_0080
	UINT32 sgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of SGAIN LUT point 0
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B84 RW 0x2492_0080
	UINT32 sgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of SGAIN LUT point 1
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B88 RW 0x4924_0080
	UINT32 sgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of SGAIN LUT point 2
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B8C RW 0x6DB6_0080
	UINT32 sgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of SGAIN LUT point 3
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B90 RW 0x9248_0080
	UINT32 sgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of SGAIN LUT point 4
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B94 RW 0xB6DA_0080
	UINT32 sgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of SGAIN LUT point 5
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B98 RW 0xDB6C_0080
	UINT32 sgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of SGAIN LUT point 6
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620B9C RW 0xFFFF_0080
	UINT32 sgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of SGAIN LUT point 7
	};
}PE_M23_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BA0 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BA4 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB -> Y CSC Coefficient 0
	};
}PE_M23_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BA8 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_M23_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BAC RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_M23_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BB0 RW 0x0000_0000
	UINT32 reg_csc4th_en                    :1;	//(0:0,RW,0x00) //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_M23_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BB4 RW 0x094A_00D0
	UINT32 r_csc4th_coef1                   :15;	//(14:0,RW,0x00D0) //CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//(30:16,RW,0x094A) //CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BB8 RW 0x0399_7AF3
	UINT32 r_csc4th_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//(30:16,RW,0x0399) //CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BBC RW 0x0702_7E0B
	UINT32 r_csc4th_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BC0 RW 0x798F_7F70
	UINT32 r_csc4th_coef7                   :15;	//(14:0,RW,0x7F70) //CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//(30:16,RW,0x798F) //CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BC4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_M23_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BC8 RW 0x0000_0000
	UINT32 r_csc4th_ofst1                   :11;	//(10:0,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//(26:16,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BCC RW 0x0000_0040
	UINT32 r_csc4th_ofst3                   :11;	//(10:0,RW,0x040) //CSC 4th Y'U'V' -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst2                   :11;	//(26:16,RW,0x200) //CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620BD0 RW 0x0200_0200
	UINT32 r_csc4th_ofst5                   :11;	//(10:0,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst4                   :11;	//(26:16,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_M23_REG_H10_CSC4_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C00 RW 0x0000_0000
	UINT32 luminance_lut2_enable            :1;	//(0:0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4:4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5:5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6:6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7:7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8:8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C14 RW 0xFFFF_1000
	UINT32 hif_cuva_tmlut_lut_wdata_y_33rd  :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_cuva_tmlut_lut_wdata_x_33rd  :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C18 RW 0x0000_8000
	UINT32 hif_cuva_tmlut_lut_address       :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_cuva_tmlut_lut_load          :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_cuva_tmlut_lut_manual_load_en :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_cuva_tmlut_lut_ai            :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_cuva_tmlut_lut_enable        :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C1C RW 0x0000_0000
	UINT32 hif_cuva_tmlut_lut_wdata_y       :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_cuva_tmlut_lut_wdata_x       :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_M23_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C20 RW 0x0000_0000
	UINT32 r_cglut_x1                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x0                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C24 RW 0x0000_0000
	UINT32 r_cglut_x3                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x2                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C28 RW 0x0000_0000
	UINT32 r_cglut_x5                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x4                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C2C RW 0x0000_0000
	UINT32 r_cglut_x7                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x6                       :16;	//(31:16,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C30 RW 0x0000_0000
	UINT32 r_cglut_y3                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y2                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y1                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y0                       :8;	//(31:24,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C34 RW 0x0000_0000
	UINT32 r_cglut_y7                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y6                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y5                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y4                       :8;	//(31:24,RW,0x0) //
	};
}PE_M23_REG_H10_CUVA_GLUT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC620C40 RW 0x0000_0000
	UINT32 r_cuva_eotf_mux                  :2;	//(1:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 r_cuva_sat_gain_bit              :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_cuva_sat_gain_sel              :1;	//(8:8,RW,0x0) //
	UINT32 resvd2                           :23;
	};
}PE_M23_REG_H10_CUVA_CTRL_T;

typedef struct {
	PE_M23_REG_H10_TOP_CTRL_00_T                         hdr_top_ctrl_00;	//0xCC620800
	PE_M23_REG_H10_TOP_CTRL_01_T                         hdr_top_ctrl_01;	//0xCC620804
	PE_M23_REG_H10_TOP_CTRL_02_T                         hdr_top_ctrl_02;	//0xCC620808
	PE_M23_REG_H10_TOP_CTRL_03_T                         hdr_top_ctrl_03;	//0xCC62080C
	PE_M23_REG_H10_TOP_CTRL_04_T                         hdr_top_ctrl_04;	//0xCC620810
	PE_M23_REG_H10_TOP_CTRL_05_T                         hdr_top_ctrl_05;	//0xCC620814
	PE_M23_REG_H10_TOP_CTRL_06_T                         hdr_top_ctrl_06;	//0xCC620818
	PE_M23_REG_H10_TOP_CTRL_07_T                         hdr_top_ctrl_07;	//0xCC62081C
	UINT32                                                    reserved0;	//0xCC620820
	UINT32                                                    reserved1;	//0xCC620824
	UINT32                                                    reserved2;	//0xCC620828
	UINT32                                                    reserved3;	//0xCC62082C
	UINT32                                                    reserved4;	//0xCC620830
	UINT32                                                    reserved5;	//0xCC620834
	UINT32                                                    reserved6;	//0xCC620838
	UINT32                                                    reserved7;	//0xCC62083C
	UINT32                                                    reserved8;	//0xCC620840
	UINT32                                                    reserved9;	//0xCC620844
	UINT32                                                   reserved10;	//0xCC620848
	UINT32                                                   reserved11;	//0xCC62084C
	PE_M23_REG_H10_CSC1_CTRL_00_T                       hdr_csc1_ctrl_00;	//0xCC620850
	PE_M23_REG_H10_CSC1_CTRL_01_T                       hdr_csc1_ctrl_01;	//0xCC620854
	PE_M23_REG_H10_CSC1_CTRL_02_T                       hdr_csc1_ctrl_02;	//0xCC620858
	PE_M23_REG_H10_CSC1_CTRL_03_T                       hdr_csc1_ctrl_03;	//0xCC62085C
	PE_M23_REG_H10_CSC1_CTRL_04_T                       hdr_csc1_ctrl_04;	//0xCC620860
	PE_M23_REG_H10_CSC1_CTRL_05_T                       hdr_csc1_ctrl_05;	//0xCC620864
	PE_M23_REG_H10_CSC1_CTRL_06_T                       hdr_csc1_ctrl_06;	//0xCC620868
	PE_M23_REG_H10_CSC1_CTRL_07_T                       hdr_csc1_ctrl_07;	//0xCC62086C
	PE_M23_REG_H10_CSC1_CTRL_08_T                       hdr_csc1_ctrl_08;	//0xCC620870
	PE_M23_REG_H10_CSC1_CTRL_09_T                       hdr_csc1_ctrl_09;	//0xCC620874
	PE_M23_REG_H10_CSC1_ERR_CNT_T                       hdr_csc1_err_cnt;	//0xCC620878
	UINT32                                                   reserved12;	//0xCC62087C
	PE_M23_REG_H10_PXL_RD_CTRL0_T                       hdr_pxl_rd_ctrl0;	//0xCC620880
	PE_M23_REG_H10_PXL_RD_CTRL1_T                       hdr_pxl_rd_ctrl1;	//0xCC620884
	PE_M23_REG_H10_PXL_RD_DATA_T                         hdr_pxl_rd_data;	//0xCC620888
	UINT32                                                   reserved13;	//0xCC62088C
	PE_M23_REG_H10_EOTF_IA_CTRL_T                       hdr_eotf_ia_ctrl;	//0xCC620890
	PE_M23_REG_H10_EOTF_IA_DATA_T                       hdr_eotf_ia_data;	//0xCC620894
	PE_M23_REG_H10_OETF_IA_CTRL_T                       hdr_oetf_ia_ctrl;	//0xCC620898
	PE_M23_REG_H10_OETF_IA_DATA_T                       hdr_oetf_ia_data;	//0xCC62089C
	PE_M23_REG_H10_PCC_CTRL_00_T                         hdr_pcc_ctrl_00;	//0xCC6208A0
	PE_M23_REG_H10_PCC_CTRL_01_T                         hdr_pcc_ctrl_01;	//0xCC6208A4
	PE_M23_REG_H10_PCC_CTRL_02_T                         hdr_pcc_ctrl_02;	//0xCC6208A8
	PE_M23_REG_H10_PCC_CTRL_03_T                         hdr_pcc_ctrl_03;	//0xCC6208AC
	PE_M23_REG_H10_PCC_CTRL_04_T                         hdr_pcc_ctrl_04;	//0xCC6208B0
	PE_M23_REG_H10_PCC_CTRL_05_T                         hdr_pcc_ctrl_05;	//0xCC6208B4
	UINT32                                                   reserved14;	//0xCC6208B8
	UINT32                                                   reserved15;	//0xCC6208BC
	UINT32                                                   reserved16;	//0xCC6208C0
	UINT32                                                   reserved17;	//0xCC6208C4
	UINT32                                                   reserved18;	//0xCC6208C8
	UINT32                                                   reserved19;	//0xCC6208CC
	PE_M23_REG_H10_HUE_SAT_CTRL_T                       hdr_hue_sat_ctrl;	//0xCC6208D0
	PE_M23_REG_H10_HUE_SAT_ALPHA_CTRL_T           hdr_hue_sat_alpha_ctrl;	//0xCC6208D4
	UINT32                                                   reserved20;	//0xCC6208D8
	UINT32                                                   reserved21;	//0xCC6208DC
	PE_M23_REG_H10_TCM_PREP_00_T                         hdr_tcm_prep_00;	//0xCC6208E0
	PE_M23_REG_H10_TCM_PREP_01_T                         hdr_tcm_prep_01;	//0xCC6208E4
	PE_M23_REG_H10_LL_LUT_IA_CTRL_T                   hdr_ll_lut_ia_ctrl;	//0xCC6208E8
	PE_M23_REG_H10_LL_LUT_IA_DATA_T                   hdr_ll_lut_ia_data;	//0xCC6208EC
	PE_M23_REG_H10_LL_HUE_CTRL_00_T                   hdr_ll_hue_ctrl_00;	//0xCC6208F0
	PE_M23_REG_H10_LL_HUE_CTRL_01_T                   hdr_ll_hue_ctrl_01;	//0xCC6208F4
	PE_M23_REG_H10_LL_HUE_CTRL_02_T                   hdr_ll_hue_ctrl_02;	//0xCC6208F8
	UINT32                                                   reserved22;	//0xCC6208FC
	PE_M23_REG_H10_LLPCC_CTRL_00_T                     hdr_llpcc_ctrl_00;	//0xCC620900
	PE_M23_REG_H10_LLPCC_CTRL_01_T                     hdr_llpcc_ctrl_01;	//0xCC620904
	PE_M23_REG_H10_LLPCC_CTRL_02_T                     hdr_llpcc_ctrl_02;	//0xCC620908
	PE_M23_REG_H10_LLPCC_CTRL_03_T                     hdr_llpcc_ctrl_03;	//0xCC62090C
	PE_M23_REG_H10_LLPCC_CTRL_04_T                     hdr_llpcc_ctrl_04;	//0xCC620910
	PE_M23_REG_H10_LLPCC_CTRL_05_T                     hdr_llpcc_ctrl_05;	//0xCC620914
	PE_M23_REG_H10_LL_AB_CTRL_00_T                     hdr_ll_ab_ctrl_00;	//0xCC620918
	PE_M23_REG_H10_LL_AB_CTRL_01_T                     hdr_ll_ab_ctrl_01;	//0xCC62091C
	PE_M23_REG_H10_LL_AB_CTRL_02_T                     hdr_ll_ab_ctrl_02;	//0xCC620920
	PE_M23_REG_H10_LL_AB_CTRL_03_T                     hdr_ll_ab_ctrl_03;	//0xCC620924
	PE_M23_REG_H10_LL_AB_CTRL_04_T                     hdr_ll_ab_ctrl_04;	//0xCC620928
	UINT32                                                   reserved23;	//0xCC62092C
	UINT32                                                   reserved24;	//0xCC620930
	UINT32                                                   reserved25;	//0xCC620934
	UINT32                                                   reserved26;	//0xCC620938
	UINT32                                                   reserved27;	//0xCC62093C
	PE_M23_REG_H10_HIST_CTRL_00_T                       hdr_hist_ctrl_00;	//0xCC620940
	PE_M23_REG_H10_HIST_CTRL_01_T                       hdr_hist_ctrl_01;	//0xCC620944
	PE_M23_REG_H10_HIST_CTRL_02_T                       hdr_hist_ctrl_02;	//0xCC620948
	PE_M23_REG_H10_HIST_CTRL_03_T                       hdr_hist_ctrl_03;	//0xCC62094C
	PE_M23_REG_H10_HIST_CTRL_04_T                       hdr_hist_ctrl_04;	//0xCC620950
	PE_M23_REG_H10_HIST_IA_CTRL_T                       hdr_hist_ia_ctrl;	//0xCC620954
	PE_M23_REG_H10_HIST_IA_DATA1_T                     hdr_hist_ia_data1;	//0xCC620958
	PE_M23_REG_H10_HIST_IA_DATA2_T                     hdr_hist_ia_data2;	//0xCC62095C
	UINT32                                                   reserved28;	//0xCC620960
	UINT32                                                   reserved29;	//0xCC620964
	UINT32                                                   reserved30;	//0xCC620968
	UINT32                                                   reserved31;	//0xCC62096C
	PE_M23_REG_H10_TPG_CTRL_00_T                         hdr_tpg_ctrl_00;	//0xCC620970
	PE_M23_REG_H10_TPG_CTRL_01_T                         hdr_tpg_ctrl_01;	//0xCC620974
	PE_M23_REG_H10_TPG_CTRL_02_T                         hdr_tpg_ctrl_02;	//0xCC620978
	PE_M23_REG_H10_TPG_CTRL_03_T                         hdr_tpg_ctrl_03;	//0xCC62097C
	PE_M23_REG_H10_TPG_CTRL_04_T                         hdr_tpg_ctrl_04;	//0xCC620980
	PE_M23_REG_H10_TPG_IA_CTRL_T                         hdr_tpg_ia_ctrl;	//0xCC620984
	PE_M23_REG_H10_TPG_IA_DATA_T                         hdr_tpg_ia_data;	//0xCC620988
	UINT32                                                   reserved32;	//0xCC62098C
	UINT32                                                   reserved33;	//0xCC620990
	UINT32                                                   reserved34;	//0xCC620994
	UINT32                                                   reserved35;	//0xCC620998
	UINT32                                                   reserved36;	//0xCC62099C
	UINT32                                                   reserved37;	//0xCC6209A0
	UINT32                                                   reserved38;	//0xCC6209A4
	UINT32                                                   reserved39;	//0xCC6209A8
	UINT32                                                   reserved40;	//0xCC6209AC
	UINT32                                                   reserved41;	//0xCC6209B0
	UINT32                                                   reserved42;	//0xCC6209B4
	UINT32                                                   reserved43;	//0xCC6209B8
	UINT32                                                   reserved44;	//0xCC6209BC
	UINT32                                                   reserved45;	//0xCC6209C0
	UINT32                                                   reserved46;	//0xCC6209C4
	UINT32                                                   reserved47;	//0xCC6209C8
	UINT32                                                   reserved48;	//0xCC6209CC
	UINT32                                                   reserved49;	//0xCC6209D0
	UINT32                                                   reserved50;	//0xCC6209D4
	UINT32                                                   reserved51;	//0xCC6209D8
	UINT32                                                   reserved52;	//0xCC6209DC
	UINT32                                                   reserved53;	//0xCC6209E0
	UINT32                                                   reserved54;	//0xCC6209E4
	UINT32                                                   reserved55;	//0xCC6209E8
	UINT32                                                   reserved56;	//0xCC6209EC
	UINT32                                                   reserved57;	//0xCC6209F0
	UINT32                                                   reserved58;	//0xCC6209F4
	UINT32                                                   reserved59;	//0xCC6209F8
	UINT32                                                   reserved60;	//0xCC6209FC
	PE_M23_REG_H10_LLUT0_CTRL_00_T                     hdr_llut0_ctrl_00;	//0xCC620A00
	PE_M23_REG_H10_LLUT0_CTRL_01_T                     hdr_llut0_ctrl_01;	//0xCC620A04
	PE_M23_REG_H10_LLUT0_CTRL_02_T                     hdr_llut0_ctrl_02;	//0xCC620A08
	PE_M23_REG_H10_LLUT0_CTRL_03_T                     hdr_llut0_ctrl_03;	//0xCC620A0C
	PE_M23_REG_H10_LLUT0_CTRL_04_T                     hdr_llut0_ctrl_04;	//0xCC620A10
	PE_M23_REG_H10_LLUT0_CTRL_05_T                     hdr_llut0_ctrl_05;	//0xCC620A14
	PE_M23_REG_H10_LLUT0_CTRL_06_T                     hdr_llut0_ctrl_06;	//0xCC620A18
	UINT32                                                   reserved61;	//0xCC620A1C
	PE_M23_REG_H10_LLUT0_IA_CTRL_T                     hdr_llut0_ia_ctrl;	//0xCC620A20
	PE_M23_REG_H10_LLUT0_IA_DATA_T                     hdr_llut0_ia_data;	//0xCC620A24
	UINT32                                                   reserved62;	//0xCC620A28
	UINT32                                                   reserved63;	//0xCC620A2C
	PE_M23_REG_H10_LLUT1_CTRL_00_T                     hdr_llut1_ctrl_00;	//0xCC620A30
	PE_M23_REG_H10_LLUT1_CTRL_01_T                     hdr_llut1_ctrl_01;	//0xCC620A34
	PE_M23_REG_H10_LLUT1_CTRL_02_T                     hdr_llut1_ctrl_02;	//0xCC620A38
	PE_M23_REG_H10_LLUT1_CTRL_03_T                     hdr_llut1_ctrl_03;	//0xCC620A3C
	PE_M23_REG_H10_LLUT1_CTRL_04_T                     hdr_llut1_ctrl_04;	//0xCC620A40
	PE_M23_REG_H10_LLUT1_CTRL_05_T                     hdr_llut1_ctrl_05;	//0xCC620A44
	PE_M23_REG_H10_LLUT1_CTRL_06_T                     hdr_llut1_ctrl_06;	//0xCC620A48
	UINT32                                                   reserved64;	//0xCC620A4C
	PE_M23_REG_H10_LLUT1_IA_CTRL_T                     hdr_llut1_ia_ctrl;	//0xCC620A50
	PE_M23_REG_H10_LLUT1_IA_DATA_T                     hdr_llut1_ia_data;	//0xCC620A54
	UINT32                                                   reserved65;	//0xCC620A58
	UINT32                                                   reserved66;	//0xCC620A5C
	PE_M23_REG_H10_LLUT2_CTRL_00_T                     hdr_llut2_ctrl_00;	//0xCC620A60
	PE_M23_REG_H10_LLUT2_CTRL_01_T                     hdr_llut2_ctrl_01;	//0xCC620A64
	PE_M23_REG_H10_LLUT2_CTRL_02_T                     hdr_llut2_ctrl_02;	//0xCC620A68
	PE_M23_REG_H10_LLUT2_CTRL_03_T                     hdr_llut2_ctrl_03;	//0xCC620A6C
	PE_M23_REG_H10_LLUT2_CTRL_04_T                     hdr_llut2_ctrl_04;	//0xCC620A70
	PE_M23_REG_H10_LLUT2_CTRL_05_T                     hdr_llut2_ctrl_05;	//0xCC620A74
	PE_M23_REG_H10_LLUT2_CTRL_06_T                     hdr_llut2_ctrl_06;	//0xCC620A78
	UINT32                                                   reserved67;	//0xCC620A7C
	PE_M23_REG_H10_LLUT2_IA_CTRL_T                     hdr_llut2_ia_ctrl;	//0xCC620A80
	PE_M23_REG_H10_LLUT2_IA_DATA_T                     hdr_llut2_ia_data;	//0xCC620A84
	UINT32                                                   reserved68;	//0xCC620A88
	UINT32                                                   reserved69;	//0xCC620A8C
	PE_M23_REG_H10_GAMMA045_CTRL_00_T               hdr_gamma045_ctrl_00;	//0xCC620A90
	UINT32                                                   reserved70;	//0xCC620A94
	PE_M23_REG_H10_DITHER_CTRL_00_T                   hdr_dither_ctrl_00;	//0xCC620A98
	PE_M23_REG_H10_PCC32_GAIN_CTRL_T                 hdr_pcc32_gain_ctrl;	//0xCC620A9C
	PE_M23_REG_H10_CSC3_CTRL_00_T                       hdr_csc3_ctrl_00;	//0xCC620AA0
	PE_M23_REG_H10_CSC3_CTRL_01_T                       hdr_csc3_ctrl_01;	//0xCC620AA4
	PE_M23_REG_H10_CSC3_CTRL_02_T                       hdr_csc3_ctrl_02;	//0xCC620AA8
	PE_M23_REG_H10_CSC3_CTRL_03_T                       hdr_csc3_ctrl_03;	//0xCC620AAC
	PE_M23_REG_H10_CSC3_CTRL_04_T                       hdr_csc3_ctrl_04;	//0xCC620AB0
	PE_M23_REG_H10_CSC3_CTRL_05_T                       hdr_csc3_ctrl_05;	//0xCC620AB4
	PE_M23_REG_H10_CSC3_CTRL_06_T                       hdr_csc3_ctrl_06;	//0xCC620AB8
	PE_M23_REG_H10_CSC3_CTRL_07_T                       hdr_csc3_ctrl_07;	//0xCC620ABC
	PE_M23_REG_H10_CSC3_CTRL_08_T                       hdr_csc3_ctrl_08;	//0xCC620AC0
	UINT32                                                   reserved71;	//0xCC620AC4
	UINT32                                                   reserved72;	//0xCC620AC8
	UINT32                                                   reserved73;	//0xCC620ACC
	PE_M23_REG_H10_TCM_SLUT0_00_T                       hdr_tcm_slut0_00;	//0xCC620AD0
	PE_M23_REG_H10_TCM_SLUT0_01_T                       hdr_tcm_slut0_01;	//0xCC620AD4
	PE_M23_REG_H10_TCM_SLUT0_02_T                       hdr_tcm_slut0_02;	//0xCC620AD8
	PE_M23_REG_H10_TCM_SLUT0_03_T                       hdr_tcm_slut0_03;	//0xCC620ADC
	PE_M23_REG_H10_TCM_SLUT0_04_T                       hdr_tcm_slut0_04;	//0xCC620AE0
	PE_M23_REG_H10_TCM_SLUT0_05_T                       hdr_tcm_slut0_05;	//0xCC620AE4
	PE_M23_REG_H10_TCM_SLUT0_06_T                       hdr_tcm_slut0_06;	//0xCC620AE8
	PE_M23_REG_H10_TCM_SLUT0_07_T                       hdr_tcm_slut0_07;	//0xCC620AEC
	PE_M23_REG_H10_TCM_SLUT0_08_T                       hdr_tcm_slut0_08;	//0xCC620AF0
	PE_M23_REG_H10_TCM_SLUT0_09_T                       hdr_tcm_slut0_09;	//0xCC620AF4
	PE_M23_REG_H10_SAT_MAP_CTRL_01_T                 hdr_sat_map_ctrl_01;	//0xCC620AF8
	PE_M23_REG_H10_SAT_MAP_CTRL_02_T                 hdr_sat_map_ctrl_02;	//0xCC620AFC
	UINT32                                                   reserved74;	//0xCC620B00
	UINT32                                                   reserved75;	//0xCC620B04
	UINT32                                                   reserved76;	//0xCC620B08
	UINT32                                                   reserved77;	//0xCC620B0C
	UINT32                                                   reserved78;	//0xCC620B10
	UINT32                                                   reserved79;	//0xCC620B14
	UINT32                                                   reserved80;	//0xCC620B18
	UINT32                                                   reserved81;	//0xCC620B1C
	PE_M23_REG_H10_YGAIN_LUT_CTRL_00_T             hdr_ygain_lut_ctrl_00;	//0xCC620B20
	PE_M23_REG_H10_YGAIN_LUT_CTRL_01_T             hdr_ygain_lut_ctrl_01;	//0xCC620B24
	PE_M23_REG_H10_YGAIN_LUT_CTRL_02_T             hdr_ygain_lut_ctrl_02;	//0xCC620B28
	PE_M23_REG_H10_YGAIN_LUT_CTRL_03_T             hdr_ygain_lut_ctrl_03;	//0xCC620B2C
	PE_M23_REG_H10_YGAIN_LUT_CTRL_04_T             hdr_ygain_lut_ctrl_04;	//0xCC620B30
	PE_M23_REG_H10_YGAIN_LUT_CTRL_05_T             hdr_ygain_lut_ctrl_05;	//0xCC620B34
	PE_M23_REG_H10_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl;	//0xCC620B38
	PE_M23_REG_H10_YGAIN_LUT_IA_DATA_T             hdr_ygain_lut_ia_data;	//0xCC620B3C
	PE_M23_REG_H10_RGB2Y_CTRL_00_T                     hdr_rgb2y_ctrl_00;	//0xCC620B40
	PE_M23_REG_H10_RGB2Y_CTRL_01_T                     hdr_rgb2y_ctrl_01;	//0xCC620B44
	PE_M23_REG_H10_RGB2Y_CTRL_02_T                     hdr_rgb2y_ctrl_02;	//0xCC620B48
	PE_M23_REG_H10_RGB2Y_CTRL_03_T                     hdr_rgb2y_ctrl_03;	//0xCC620B4C
	UINT32                                                   reserved82;	//0xCC620B50
	UINT32                                                   reserved83;	//0xCC620B54
	UINT32                                                   reserved84;	//0xCC620B58
	UINT32                                                   reserved85;	//0xCC620B5C
	PE_M23_REG_H10_LGAIN_LUT_CTRL_00_T             hdr_lgain_lut_ctrl_00;	//0xCC620B60
	PE_M23_REG_H10_LGAIN_LUT_CTRL_01_T             hdr_lgain_lut_ctrl_01;	//0xCC620B64
	PE_M23_REG_H10_LGAIN_LUT_CTRL_02_T             hdr_lgain_lut_ctrl_02;	//0xCC620B68
	PE_M23_REG_H10_LGAIN_LUT_CTRL_03_T             hdr_lgain_lut_ctrl_03;	//0xCC620B6C
	PE_M23_REG_H10_LGAIN_LUT_CTRL_04_T             hdr_lgain_lut_ctrl_04;	//0xCC620B70
	PE_M23_REG_H10_LGAIN_LUT_CTRL_05_T             hdr_lgain_lut_ctrl_05;	//0xCC620B74
	PE_M23_REG_H10_LGAIN_LUT_CTRL_06_T             hdr_lgain_lut_ctrl_06;	//0xCC620B78
	PE_M23_REG_H10_LGAIN_LUT_CTRL_07_T             hdr_lgain_lut_ctrl_07;	//0xCC620B7C
	PE_M23_REG_H10_SGAIN_LUT_CTRL_00_T             hdr_sgain_lut_ctrl_00;	//0xCC620B80
	PE_M23_REG_H10_SGAIN_LUT_CTRL_01_T             hdr_sgain_lut_ctrl_01;	//0xCC620B84
	PE_M23_REG_H10_SGAIN_LUT_CTRL_02_T             hdr_sgain_lut_ctrl_02;	//0xCC620B88
	PE_M23_REG_H10_SGAIN_LUT_CTRL_03_T             hdr_sgain_lut_ctrl_03;	//0xCC620B8C
	PE_M23_REG_H10_SGAIN_LUT_CTRL_04_T             hdr_sgain_lut_ctrl_04;	//0xCC620B90
	PE_M23_REG_H10_SGAIN_LUT_CTRL_05_T             hdr_sgain_lut_ctrl_05;	//0xCC620B94
	PE_M23_REG_H10_SGAIN_LUT_CTRL_06_T             hdr_sgain_lut_ctrl_06;	//0xCC620B98
	PE_M23_REG_H10_SGAIN_LUT_CTRL_07_T             hdr_sgain_lut_ctrl_07;	//0xCC620B9C
	PE_M23_REG_H10_RGB2Y2_CTRL_00_T                   hdr_rgb2y2_ctrl_00;	//0xCC620BA0
	PE_M23_REG_H10_RGB2Y2_CTRL_01_T                   hdr_rgb2y2_ctrl_01;	//0xCC620BA4
	PE_M23_REG_H10_RGB2Y2_CTRL_02_T                   hdr_rgb2y2_ctrl_02;	//0xCC620BA8
	PE_M23_REG_H10_RGB2Y2_CTRL_03_T                   hdr_rgb2y2_ctrl_03;	//0xCC620BAC
	PE_M23_REG_H10_CSC4_CTRL_00_T                       hdr_csc4_ctrl_00;	//0xCC620BB0
	PE_M23_REG_H10_CSC4_CTRL_01_T                       hdr_csc4_ctrl_01;	//0xCC620BB4
	PE_M23_REG_H10_CSC4_CTRL_02_T                       hdr_csc4_ctrl_02;	//0xCC620BB8
	PE_M23_REG_H10_CSC4_CTRL_03_T                       hdr_csc4_ctrl_03;	//0xCC620BBC
	PE_M23_REG_H10_CSC4_CTRL_04_T                       hdr_csc4_ctrl_04;	//0xCC620BC0
	PE_M23_REG_H10_CSC4_CTRL_05_T                       hdr_csc4_ctrl_05;	//0xCC620BC4
	PE_M23_REG_H10_CSC4_CTRL_06_T                       hdr_csc4_ctrl_06;	//0xCC620BC8
	PE_M23_REG_H10_CSC4_CTRL_07_T                       hdr_csc4_ctrl_07;	//0xCC620BCC
	PE_M23_REG_H10_CSC4_CTRL_08_T                       hdr_csc4_ctrl_08;	//0xCC620BD0
	UINT32                                                   reserved86;	//0xCC620BD4
	UINT32                                                   reserved87;	//0xCC620BD8
	UINT32                                                   reserved88;	//0xCC620BDC
	UINT32                                                   reserved89;	//0xCC620BE0
	UINT32                                                   reserved90;	//0xCC620BE4
	UINT32                                                   reserved91;	//0xCC620BE8
	UINT32                                                   reserved92;	//0xCC620BEC
	UINT32                                                   reserved93;	//0xCC620BF0
	UINT32                                                   reserved94;	//0xCC620BF4
	UINT32                                                   reserved95;	//0xCC620BF8
	UINT32                                                   reserved96;	//0xCC620BFC
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T   hdr_cuva_tmlut_lut_ctrl_00;	//0xCC620C00
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T   hdr_cuva_tmlut_lut_ctrl_01;	//0xCC620C04
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T   hdr_cuva_tmlut_lut_ctrl_02;	//0xCC620C08
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T   hdr_cuva_tmlut_lut_ctrl_03;	//0xCC620C0C
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T   hdr_cuva_tmlut_lut_ctrl_04;	//0xCC620C10
	PE_M23_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T   hdr_cuva_tmlut_lut_ctrl_05;	//0xCC620C14
	PE_M23_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T   hdr_cuva_tmlut_lut_ia_ctrl;	//0xCC620C18
	PE_M23_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T   hdr_cuva_tmlut_lut_ia_data;	//0xCC620C1C
	PE_M23_REG_H10_CUVA_GLUT_00_T                       hdr_cuva_glut_00;	//0xCC620C20
	PE_M23_REG_H10_CUVA_GLUT_01_T                       hdr_cuva_glut_01;	//0xCC620C24
	PE_M23_REG_H10_CUVA_GLUT_02_T                       hdr_cuva_glut_02;	//0xCC620C28
	PE_M23_REG_H10_CUVA_GLUT_03_T                       hdr_cuva_glut_03;	//0xCC620C2C
	PE_M23_REG_H10_CUVA_GLUT_04_T                       hdr_cuva_glut_04;	//0xCC620C30
	PE_M23_REG_H10_CUVA_GLUT_05_T                       hdr_cuva_glut_05;	//0xCC620C34
	UINT32                                                   reserved97;	//0xCC620C38
	UINT32                                                   reserved98;	//0xCC620C3C
	PE_M23_REG_H10_CUVA_CTRL_T                             hdr_cuva_ctrl;	//0xCC620C40
}PE_M23_REG_H10_T;

#endif

