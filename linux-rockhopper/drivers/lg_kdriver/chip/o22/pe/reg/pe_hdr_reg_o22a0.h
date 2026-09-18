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
#ifndef _PE_HDR_REG_O22A0_H_
#define _PE_HDR_REG_O22A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0800 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0,RW,0x00) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1,RW,0x00) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2,RW,0x00) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O22_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0804 RW 0x0870_0F00
	UINT32 width                            :16;	//(15:0,RW,0xF00) //width
	UINT32 height                           :16;	//(31:16,RW,0x870) //height
	};
}PE_O22_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0808 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,RW,0x0000_0014) //vdpulse position for register loading
	};
}PE_O22_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC080C RO 0x0000_0000
	UINT32 vcnt                             :16;	//(15:0,RO,0x0) //vertical line count
	UINT32 vcnt2                            :16;	//(31:16,RO,0x0) //vertical line number
	};
}PE_O22_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0810 RO 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,RO,0x0800) //apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//(30,RO,0x00) //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//(31,RO,0x00) //Vertical Active at PE1 output(Read only)
	};
}PE_O22_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0814 RW 0x0000_0000
	UINT32 reg_hue_sat_prsv_ref             :1;	//(0,RW,0x0) //0: hue/sat ref source from pcc32 output	1: hue/sat ref source from lg gamma output
	UINT32 resvd0                           :3;
	UINT32 reg_tcm_inp_src                  :1;	//(4,RW,0x0) //0: Tone Map input source = OETF Out 	1: Tone Map input source = OETF Input
	UINT32 resvd1                           :11;
	UINT32 reg_hue_sat_prsv_src             :2;	//(17:16,RW,0x0) //(deprecated)
	UINT32 resvd2                           :2;
	UINT32 reg_hist_src                     :4;	//(23:20,RW,0x0) //1:R, 2:G, 3:B, 4:MAX(RGB)	5:Y, 6:Cb, 7:Cr	8:Technicolor G, 9: Technicolor B, 10 : Technicolor R	11: Technicolor MAX(RGB)	15: MAX(YCbCr) Others: Y
	UINT32 reg_eotf_en                      :1;	//(24,RW,0x1) //EOTF block enable
	UINT32 reg_oetf_en                      :1;	//(25,RW,0x0) //OETF block enable
	UINT32 resvd3                           :2;
	UINT32 reg_hdr10p_mode                  :1;	//(28,RW,0x00) //0: HDR10 Mode	1: HDR10+ Mode
	UINT32 reg_use_equal_llut_en            :1;	//(29,RW,0x00) //0:use luminanace LUT channel G hif, 	1:use own LUT hif(B/R)(WR only)
	UINT32 reg_hdr10_mode                   :1;	//(30,RW,0x0) //0: Bypass HDR10 Path	1: Run HDR10
	UINT32 resvd4                           :1;
	};
}PE_O22_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0818 RW 0x0000_0000
	UINT32 reg_hdr_eotf_120hz_mode          :1;	//(0,RW,0x00) //1: Nullify all settings about double buffer of EOTF
	UINT32 reg_eotf_same_write_mode         :1;	//(1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 EOTF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_eotf_dbuf_mode               :1;	//(4,RW,0x00) //1: use EOTF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_dbuf_wptr               :1;	//(8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_eotf_dbuf_rptr               :1;	//(12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_eotf_dbuf_ptr_imode          :1;	//(16,RW,0x00) //1: eotf_rptr = ~ eotf_wptr (ignore [12] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_eotf_ra_mode                 :1;	//(24,RW,0x00) //1: eotf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O22_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC081C RW 0x0000_0000
	UINT32 reg_hdr_oetf_120hz_mode          :1;	//(0,RW,0x00) //1: Nullify all settings about double buffer of OETF
	UINT32 reg_oetf_same_write_mode         :1;	//(1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 OETF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_oetf_dbuf_mode               :1;	//(4,RW,0x00) //1: use OETF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_oetf_dbuf_wptr               :1;	//(8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_oetf_dbuf_rptr               :1;	//(12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_oetf_dbuf_ptr_imode          :1;	//(16,RW,0x00) //1: oetf_rptr = ~ oetf_wptr (ignore [13] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_oetf_ra_mode                 :1;	//(24,RW,0x00) //1: oetf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O22_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0850 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0,RW,0x01) //
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0854 RW 0x12AF_7CFE
	UINT32 r_csc1st_coef1                   :15;	//(14:0,RW,0x7CFE) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0858 RW 0x7590_12AF
	UINT32 r_csc1st_coef3                   :15;	//(14:0,RW,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,RW,0x7590) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC085C RW 0x225F_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,RW,0x225F) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0860 RW 0x12AF_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0864 RW 0x1AF0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,RW,0x1AF0) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0868 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,RW,0x0600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,RW,0x07C0) //
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC086C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,RW,0x0600) //
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0870 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,RW,0x00) //
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0874 RW 0x0000_0000
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
}PE_O22_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0878 RO 0x0000_0000
	UINT32 ireg_csc_cnt_under               :16;	//(15:0,RO,0x0) //
	UINT32 ireg_csc_cnt_over                :16;	//(31:16,RO,0x0) //
	};
}PE_O22_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0880 RW 0x0000_FFFF
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
	UINT32 r_pxl_rd_mark_en                 :1;	//(24,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//(28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0884 RW 0x0000_0000
	UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0888 RO 0x0000_0000
	UINT32 pxl_read_rcr                     :10;	//(9:0,RO,0x00) //
	UINT32 pxl_read_bcb                     :10;	//(19:10,RO,0x00) //
	UINT32 pxl_read_gyy                     :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_PXL_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0890 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O22_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0894 RW 0x0000_0000
	UINT32 eotf_lut_data                    :32;	//(31:0,RW,0x0000_0000) //32 bit LUT data
	};
}PE_O22_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0898 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O22_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC089C RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :16;	//(15:0,RW,0x0) //16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//(31:16,RW,0x0) //16 bit even LUT data
	};
}PE_O22_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08A0 RW 0x0000_0001
	UINT32 reg_pcc_en                       :1;	//(0,RW,0x1) //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08A4 RW 0x1220_7FDE
	UINT32 r_pcc_coef1                      :15;	//(14:0,RW,0x7FDE) //PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//(30:16,RW,0x1220) //PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08A8 RW 0x7E02_7E64
	UINT32 r_pcc_coef3                      :15;	//(14:0,RW,0x7E64) //PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//(30:16,RW,0x7E02) //PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08AC RW 0x11E6_7FB6
	UINT32 r_pcc_coef5                      :15;	//(14:0,RW,0x7FB6) //PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//(30:16,RW,0x11E6) //PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08B0 RW 0x7F10_7ED6
	UINT32 r_pcc_coef7                      :15;	//(14:0,RW,0x7ED6) //PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//(30:16,RW,0x7F10) //PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08B4 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//(30:16,RW,0x1A91) //PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08D0 RW 0x0000_3FF3
	UINT32 reg_hue_prsv_en                  :1;	//(0,RW,0x1) //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//(1,RW,0x1) //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//(13:4,RW,0x3FF) //0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//(25:16,RW,0x000) //0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_O22_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08D4 NA 0x0000_1000
	UINT32 reg_inp_l_sel                    :1;	//(0,RW,0x0) //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//(4,RW,0x0) //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//(8,RW,0x0) //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//(12,RW,0x1) //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_O22_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08E0 RW 0x121F_7FDE
	UINT32 r_tone_map_rgb2y_coef1           :15;	//(14:0,RW,0x7FDE) //
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//(30:16,RW,0x121F) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08E4 RW 0x7E02_0000
	UINT32 r_tone_map_rgbymax_sel           :3;	//(2:0,RW,0x0) //
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//(30:16,RW,0x7E02) //
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08E8 RW 0x0000_0000
	UINT32 ll_lut_addr                      :7;	//(6:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O22_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08EC RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,RW,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,RW,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08F0 RW 0x1000_03FF
	UINT32 reg_alpha_hue                    :10;	//(9:0,RW,0x3FF) //alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//(25:16,RW,0x00) //alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//(28,RW,0x01) //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_O22_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08F4 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//(16,RW,0x0) //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_O22_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC08F8 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(30:16,RW,0x0) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0900 RW 0x0000_0001
	UINT32 reg_ll_pcc_en                    :1;	//(0,RW,0x1) //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0904 RW 0x1220_7FDE
	UINT32 r_ll_pcc_coef1                   :15;	//(14:0,RW,0x7FDE) //PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//(30:16,RW,0x1220) //PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0908 RW 0x7E02_7E64
	UINT32 r_ll_pcc_coef3                   :15;	//(14:0,RW,0x7E64) //PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//(30:16,RW,0x7E02) //PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC090C RW 0x11E6_7FB6
	UINT32 r_ll_pcc_coef5                   :15;	//(14:0,RW,0x7FB6) //PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//(30:16,RW,0x11E6) //PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0910 RW 0x7F10_7ED6
	UINT32 r_ll_pcc_coef7                   :15;	//(14:0,RW,0x7ED6) //PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//(30:16,RW,0x7F10) //PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0914 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//(30:16,RW,0x1A91) //PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0918 RW 0x0000_0001
	UINT32 reg_ll_ab_en                     :1;	//(0,RW,0x1) //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC091C RW 0x0048_000A
	UINT32 r_ll_ab_lut_x2                   :10;	//(9:0,RW,0xA) //
	UINT32 r_ll_ab_lut_x1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_x0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0920 RW 0x00BF_FFFF
	UINT32 r_ll_ab_lut_x5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x3                   :10;	//(29:20,RW,0xB) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0924 RW 0x0000_2600
	UINT32 r_ll_ab_lut_y2                   :10;	//(9:0,RW,0x200) //
	UINT32 r_ll_ab_lut_y1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_y0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0928 RW 0x3FFF_FFFF
	UINT32 r_ll_ab_lut_y5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y3                   :10;	//(29:20,RW,0x3FF) //
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0940 RW 0x0000_0000
	UINT32 hist_bin_mode                    :2;	//(1:0,RW,0x00) //"00" : 32 bin mode	others : 16 bin mode
	UINT32 histogram_mode                   :2;	//(3:2,RW,0x00) //"00" : Own side's histogram data use	"01" : Other side's histogram data use	"10" : Average between Own and Other side's histogram data use
	UINT32 window01_enable                  :1;	//(4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,RW,0x00) //1: window mode enable
	UINT32 resvd0                           :7;
	UINT32 window_inout_sel                 :1;	//(16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :6;
	UINT32 hist_clear                       :1;	//(23,RW,0x00) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd2                           :8;
	};
}PE_O22_REG_H10_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0944 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O22_REG_H10_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0948 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O22_REG_H10_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC094C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O22_REG_H10_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0950 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O22_REG_H10_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0954 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//(12,RW,0x00) //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//(15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//(18:16,RW,0x00) //"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//(28,RW,0x00) //auto increment enable
	UINT32 hif_mask                         :1;	//(29,RW,0x00) //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_O22_REG_H10_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0958 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,RW,0x0000_0000) //[22:0]hif_histogram_bin_read
	};
}PE_O22_REG_H10_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC095C RO 0x0000_0000
	UINT32 hist_v_min                       :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O22_REG_H10_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0970 RW 0x0000_0000
	UINT32 tpg_enable                       :1;	//(0,RW,0x00) //Test Pattern Gen. enable
	UINT32 tpg_type                         :2;	//(2:1,RW,0x00) //0: Patch 1: Gradient 2: CMYW 3: RGBW
	UINT32 tpg_cg_disable                   :1;	//(3,RW,0x00) //clock gating disable
	UINT32 tpg_blend_alpha                  :4;	//(7:4,RW,0x00) //0: Solid ~ 15 : Background
	UINT32 tpg_grad_en                      :4;	//(11:8,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 tpg_h_grad                       :1;	//(12,RW,0x00) //1: window mode enable
	UINT32 resvd0                           :3;
	UINT32 tpg_stride                       :7;	//(22:16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :9;
	};
}PE_O22_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0974 RW 0x0438_0780
	UINT32 tpg_size_x                       :14;	//(13:0,RW,0x780) //tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//(28:16,RW,0x438) //tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0978 RW 0x0000_0000
	UINT32 tpg_mask_flag                    :16;	//(15:0,RW,0x0000) //
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC097C RW 0x0000_0000
	UINT32 tpg_in_out_sel                   :16;	//(15:0,RW,0x0) //in_out_sel
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0980 RW 0x0000_0000
	UINT32 tpg_color_r                      :10;	//(9:0,RW,0x00) //tpg_color_r
	UINT32 tpg_color_b                      :10;	//(19:10,RW,0x00) //tpg_color_b
	UINT32 tpg_color_g                      :10;	//(29:20,RW,0x00) //tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0984 RW 0x0000_8000
	UINT32 hif_tpg_address                  :8;	//(7:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//(8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//(11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//(12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//(15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O22_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0988 RW 0x0000_0000
	UINT32 hif_tpg_wdata_y                  :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O22_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0990 RW 0x0000_0000
	UINT32 reg_clut_65th_data               :11;	//(10:0,NA,0x000) //65th_data
	UINT32 resvd                            :21;
	};
}PE_O22_REG_H10_CLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0994 RW 0x0000_0000
	UINT32 clut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 clut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 clut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O22_REG_H10_CLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0998 RW 0x0000_0000
	UINT32 clut_data                        :11;	//(10:0,RW,0x00) //data for CLUT
	UINT32 resvd                            :21;
	};
}PE_O22_REG_H10_CLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC099C RW 0x0000_0000
	UINT32 reg_plut_65th_data               :14;	//(13:0,NA,0x000) //65th_data
	UINT32 resvd                            :18;
	};
}PE_O22_REG_H10_PLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09A0 RW 0x0000_0000
	UINT32 plut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 plut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 plut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O22_REG_H10_PLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09A4 RW 0x0000_0000
	UINT32 plut_data                        :14;	//(13:0,RW,0x0) //data for PLUT
	UINT32 resvd                            :18;
	};
}PE_O22_REG_H10_PLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09A8 RW 0x0000_0000
	UINT32 reg_slut_65th_data               :10;	//(9:0,NA,0x000) //65th_data
	UINT32 resvd                            :22;
	};
}PE_O22_REG_H10_SLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09AC RW 0x0000_0000
	UINT32 slut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 slut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 slut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O22_REG_H10_SLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09B0 RW 0x0000_0000
	UINT32 slut_data                        :10;	//(9:0,RW,0x00) //data for SLUT
	UINT32 resvd                            :22;
	};
}PE_O22_REG_H10_SLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09B4 RW 0x0000_0000
	UINT32 reg_ilut_65th_data               :8;	//(7:0,NA,0x000) //65th_data
	UINT32 resvd                            :24;
	};
}PE_O22_REG_H10_ILUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09B8 RW 0x0000_0000
	UINT32 ilut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 ilut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 ilut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O22_REG_H10_ILUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09BC RW 0x0000_0000
	UINT32 ilut_data                        :8;	//(7:0,RW,0x0) //data for ILUT
	UINT32 resvd                            :24;
	};
}PE_O22_REG_H10_ILUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09C0 RW 0x0000_0000
	UINT32 reg_dlut_65th_data               :12;	//(11:0,NA,0x000) //65th_data
	UINT32 resvd0                           :4;
	UINT32 reg_dlut_threshold_0             :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09C4 RW 0x0000_0000
	UINT32 reg_dlut_threshold_1             :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_dlut_threshold_2             :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09C8 RW 0x0000_0000
	UINT32 reg_dlut_step_0                  :4;	//(3:0,RW,0x00) //
	UINT32 reg_dlut_step_1                  :4;	//(7:4,RW,0x00) //
	UINT32 reg_dlut_step_2                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_dlut_step_3                  :4;	//(15:12,RW,0x00) //
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09CC RW 0x0000_0000
	UINT32 dlut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 dlut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 dlut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O22_REG_H10_DLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09D0 RW 0x0000_0000
	UINT32 dlut_data                        :8;	//(7:0,RW,0x0) //data for DLUT
	UINT32 resvd                            :24;
	};
}PE_O22_REG_H10_DLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09D4 RW 0x0000_0001
	UINT32 reg_technicolor_detour_en        :1;	//(0,NA,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_range_sel                    :1;	//(4,NA,0x000) //0':limited range, '1':full range
	UINT32 resvd1                           :27;
	};
}PE_O22_REG_H10_TC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09D8 RW 0x1E00_1F00
	UINT32 reg_alpha_a                      :13;	//(12:0,RW,0x1F00) //default value : 7936
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_b                      :13;	//(28:16,RW,0x1E00) //default value : 7680
	UINT32 resvd1                           :3;
	};
}PE_O22_REG_H10_TC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09DC RW 0x0000_0000
	UINT32 reg_oct_0                        :6;	//(5:0,RW,0x0) //unsigned 6 bit
	UINT32 resvd0                           :4;
	UINT32 reg_oct_1                        :8;	//(17:10,RW,0x0) //signed 8 bit
	UINT32 resvd1                           :2;
	UINT32 reg_oct_2                        :9;	//(28:20,RW,0x00) //signed 9 bit
	UINT32 resvd2                           :3;
	};
}PE_O22_REG_H10_TC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09E0 RW 0x0000_0000
	UINT32 reg_oct_3                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 reg_oct_4                        :10;	//(19:10,RW,0x00) //signed 10 bit
	UINT32 reg_oct_5                        :10;	//(29:20,RW,0x00) //signed 10 bit
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_TC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC09E4 RW 0x0000_0000
	UINT32 reg_oct_6                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 resvd                            :22;
	};
}PE_O22_REG_H10_TC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A00 RW 0x0000_0000
	UINT32 luminance_lut0_enable            :1;	//(0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O22_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O22_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O22_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O22_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O22_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A14 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O22_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A18 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A20 RW 0x0000_8000
	UINT32 hif_llut0_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//(8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//(11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//(12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//(13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//(14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//(15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O22_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A24 RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O22_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A30 RW 0x0000_0000
	UINT32 luminance_lut1_enable            :1;	//(0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O22_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A34 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O22_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A38 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O22_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A3C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O22_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A40 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O22_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A44 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O22_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A48 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A50 RW 0x0000_8000
	UINT32 hif_llut1_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//(8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//(11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//(12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//(13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//(14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//(15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O22_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A54 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O22_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A60 RW 0x0000_0000
	UINT32 luminance_lut2_enable            :1;	//(0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O22_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A64 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O22_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A68 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O22_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A6C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O22_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A70 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O22_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A74 RW 0xFFFF_FFFF
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//(31:16,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O22_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A78 RW 0xFFFF_FFFF
	UINT32 hif_llut2_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O22_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A80 RW 0x0000_8000
	UINT32 hif_llut2_address                :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//(8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load_en         :1;	//(11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_llut2_ai                     :1;	//(12,RW,0x00) //auto increment enable	1: enable
	UINT32 hif_llut2_write_x                :1;	//(13,RW,0x0) //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut2_read_x                 :1;	//(14,RW,0x0) //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut2_enable                 :1;	//(15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O22_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A84 RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O22_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A90 RW 0x0000_0000
	UINT32 gamma045_enable                  :1;	//(0,RW,0x00) //gamma 0.45(1/2.2) enable
	UINT32 resvd0                           :3;
	UINT32 gamma045_mode                    :1;	//(4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 gamma045_mux                     :1;	//(8,RW,0x00) //
	UINT32 resvd2                           :23;
	};
}PE_O22_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A98 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0,RW,0x00) //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//(2,RW,0x00) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3,RW,0x00) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,RW,0x00) //"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O22_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0A9C RW 0x0000_0000
	UINT32 hif_pcc32_ygain_shift            :1;	//(0,RW,0x0) //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AA0 RW 0x0000_0001
	UINT32 reg_csc3rd_en                    :1;	//(0,RW,0x01) //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AA4 RW 0x094A_00D0
	UINT32 r_csc3rd_coef1                   :15;	//(14:0,RW,0x00D0) //CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//(30:16,RW,0x094A) //CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AA8 RW 0x0399_7AF3
	UINT32 r_csc3rd_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//(30:16,RW,0x0399) //CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AAC RW 0x0702_7E0B
	UINT32 r_csc3rd_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AB0 RW 0x798F_7F70
	UINT32 r_csc3rd_coef7                   :15;	//(14:0,RW,0x7F70) //CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//(30:16,RW,0x798F) //CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AB4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AB8 RW 0x0000_0000
	UINT32 r_csc3rd_ofst1                   :11;	//(10:0,RW,0x000) //CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//(26:16,RW,0x000) //CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0ABC RW 0x0000_0040
	UINT32 r_csc3rd_ofst3                   :11;	//(10:0,RW,0x040) //CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//(26:16,RW,0x200) //CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AC0 RW 0x0200_0200
	UINT32 r_csc3rd_ofst5                   :11;	//(10:0,RW,0x0200) //CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//(26:16,RW,0x0200) //CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AD0 RW 0x0000_0000
	UINT32 r_slut0_x0                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AD4 RW 0x0000_0000
	UINT32 r_slut0_x1                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AD8 RW 0x0000_0000
	UINT32 r_slut0_x2                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0ADC RW 0x0000_0000
	UINT32 r_slut0_x3                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AE0 RW 0x0000_0000
	UINT32 r_slut0_x4                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AE4 RW 0x0000_0000
	UINT32 r_slut0_x5                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AE8 RW 0x0000_0000
	UINT32 r_slut0_x6                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AEC RW 0x0000_0000
	UINT32 r_slut0_x7                       :32;	//(31:00,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AF0 RW 0x0000_0000
	UINT32 r_slut0_y0                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y1                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y2                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y3                       :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AF4 RW 0x0000_0000
	UINT32 r_slut0_y4                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y5                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y6                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y7                       :8;	//(31:24,RW,0x0) //
	};
}PE_O22_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AF8 RW 0x0000_0000
	UINT32 reg_tm_m2020_coef13              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd                            :1;
	UINT32 reg_tm_m2020_coef22              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 sat_gain_en                      :1;	//(31,RW,0x00) //TM0 Saturation Gain Enable
	};
}PE_O22_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0AFC RW 0x0000_0000
	UINT32 reg_tm_m2020_coef23              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm_m2020_coef32              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B20 RW 0x0000_0000
	UINT32 luminance_lut2_enable            :1;	//(0,RW,0x00) //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//(4,RW,0x00) //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//(5,RW,0x00) //1: window0 area only
	UINT32 window1_enable                   :1;	//(6,RW,0x00) //1: window1 area only
	UINT32 window_acquire                   :1;	//(7,RW,0x00) //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//(8,RW,0x00) //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//(16,RW,0x00) //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B24 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B28 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B2C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B30 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B34 RW 0xFFFF_1000
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_O22_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B38 RW 0x0000_8000
	UINT32 hif_ygain_lut_address            :4;	//(3:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//(8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//(11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//(12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//(15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O22_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B3C RW 0x0000_0000
	UINT32 hif_ygain_lut_wdata_y            :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O22_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B40 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0,RW,0x1) //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B44 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_O22_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B48 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O22_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B4C RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O22_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B60 RW 0x0000_0080
	UINT32 lgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of LGAIN LUT point 0
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B64 RW 0x2492_0080
	UINT32 lgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of LGAIN LUT point 1
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B68 RW 0x4924_0080
	UINT32 lgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of LGAIN LUT point 2
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B6C RW 0x6DB6_0080
	UINT32 lgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of LGAIN LUT point 3
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B70 RW 0x9248_0080
	UINT32 lgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of LGAIN LUT point 4
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B74 RW 0xB6DA_0080
	UINT32 lgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of LGAIN LUT point 5
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B78 RW 0xDB6C_0080
	UINT32 lgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of LGAIN LUT point 6
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B7C RW 0xFFFF_0080
	UINT32 lgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of LGAIN LUT point 7
	};
}PE_O22_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B80 RW 0x0000_0080
	UINT32 sgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of SGAIN LUT point 0
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B84 RW 0x2492_0080
	UINT32 sgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of SGAIN LUT point 1
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B88 RW 0x4924_0080
	UINT32 sgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of SGAIN LUT point 2
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B8C RW 0x6DB6_0080
	UINT32 sgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of SGAIN LUT point 3
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B90 RW 0x9248_0080
	UINT32 sgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of SGAIN LUT point 4
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B94 RW 0xB6DA_0080
	UINT32 sgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of SGAIN LUT point 5
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B98 RW 0xDB6C_0080
	UINT32 sgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of SGAIN LUT point 6
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0B9C RW 0xFFFF_0080
	UINT32 sgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of SGAIN LUT point 7
	};
}PE_O22_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BA0 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0,RW,0x1) //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BA4 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB -> Y CSC Coefficient 0
	};
}PE_O22_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BA8 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O22_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BAC RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O22_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BB0 RW 0x0000_0000
	UINT32 reg_csc4th_en                    :1;	//(0,RW,0x00) //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BB4 RW 0x094A_00D0
	UINT32 r_csc4th_coef1                   :15;	//(14:0,RW,0x00D0) //CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//(30:16,RW,0x094A) //CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BB8 RW 0x0399_7AF3
	UINT32 r_csc4th_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//(30:16,RW,0x0399) //CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BBC RW 0x0702_7E0B
	UINT32 r_csc4th_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BC0 RW 0x798F_7F70
	UINT32 r_csc4th_coef7                   :15;	//(14:0,RW,0x7F70) //CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//(30:16,RW,0x798F) //CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BC4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O22_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BC8 RW 0x0000_0000
	UINT32 r_csc4th_ofst1                   :11;	//(10:0,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//(26:16,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BCC RW 0x0000_0040
	UINT32 r_csc4th_ofst3                   :11;	//(10:0,RW,0x040) //CSC 4th Y'U'V' -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst2                   :11;	//(26:16,RW,0x200) //CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0BD0 RW 0x0200_0200
	UINT32 r_csc4th_ofst5                   :11;	//(10:0,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst4                   :11;	//(26:16,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O22_REG_H10_CSC4_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C00 RW 0xFF00_FF00
	UINT32 reg_gfd_h_th0_a                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_h_th1_a                  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_gfd_h_th0_b                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_gfd_h_th1_b                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O22_REG_H10_FIM_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C04 RW 0x0000_0000
	UINT32 reg_gfd_s_th                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_v_th                     :8;	//(15:8,RW,0x00) //
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//(31:30,RW,0x0) //0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_O22_REG_H10_FIM_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C08 RO 0x0000_0000
	UINT32 reg_gfd_count_a01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Top
	};
}PE_O22_REG_H10_FIM_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C0C RO 0x0000_0000
	UINT32 reg_gfd_count_a11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_O22_REG_H10_FIM_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C10 RO 0x0000_0000
	UINT32 reg_gfd_count_b01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Top
	};
}PE_O22_REG_H10_FIM_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C14 RO 0x0000_0000
	UINT32 reg_gfd_count_b11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_O22_REG_H10_FIM_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C18 RW 0x0000_0000
	UINT32 reg_pcg_off                      :1;	//(0:0,NA,0x0) //
	UINT32 resvd                            :31;
	};
}PE_O22_REG_H10_FIM_PCG_OFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C20 RW 0x00EC_1200
	UINT32 reg_show_scale                   :3;	//(2:0,RW,0x00) //
	UINT32 reg_bbd_show                     :1;	//(3,RW,0x00) //display BBD result
	UINT32 reg_show_bar_1                   :1;	//(4,RW,0x00) //
	UINT32 reg_show_bar_2                   :1;	//(5,RW,0x00) //
	UINT32 reg_show_bar_3                   :1;	//(6,RW,0x00) //
	UINT32 reg_bar1_data_mux                :2;	//(8:7,RW,0x00) //bar data selection	0 : APL_0	1 : APL_1	others : APL_2
	UINT32 reg_bar2_data_mux                :2;	//(10:9,RW,0x01) //
	UINT32 reg_bar3_data_mux                :2;	//(12:11,RW,0x02) //
	UINT32 reg_hist0_data_mux               :4;	//(16:13,RW,0x00) //bar data selection	0 : Y	1 : Cb	2 : Cr	3 : G	4 : B	5 : R	6 : H	7 : S	8 : V / L / Vs	others : Y
	UINT32 reg_hist1_data_mux               :4;	//(20:17,RW,0x06) //
	UINT32 reg_hist2_data_mux               :4;	//(24:21,RW,0x07) //
	UINT32 reg_hist0_win_sel                :2;	//(26:25,RW,0x00) //hist0 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist1_win_sel                :2;	//(28:27,RW,0x00) //hist1 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 reg_hist2_win_sel                :2;	//(30:29,RW,0x00) //hist2 window selection 0 : Win_A, 1 : Win_B, others : Win_C
	UINT32 hist_rd_en                       :1;	//(31,RW,0x00) //histogram read mode enable
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C24 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C28 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C2C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C30 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C34 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C38 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C3C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C40 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C44 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C48 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C4C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O22_REG_H10_FIM_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C50 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O22_REG_H10_FIM_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C54 RW 0x0010_2000
	UINT32 reg_bbd_en                       :1;	//(0,RW,0x00) //enable
	UINT32 reg_hys_mode                     :5;	//(5:1,RW,0x0) //frame count for temporal smoothing of BBD result
	UINT32 reg_op_mode                      :1;	//(6,RW,0x00) //BBD operation mode 0 : auto detection, 1 : manual setting
	UINT32 resvd                            :1;
	UINT32 reg_cnt_th                       :8;	//(15:8,RW,0x20) //continuous Black pixel's count threshold for recognizing Black Boundary
	UINT32 reg_diff_th                      :8;	//(23:16,RW,0x10) //threshold for Black decision
	UINT32 reg_bbd_mux                      :3;	//(26:24,RW,0x00) //data select for BBD, 0 : Max(RGB), 1 : Y, 2 : G, 3 : B, 4 : R, others : Y
	UINT32 reg_apl_mux                      :3;	//(29:27,RW,0x00) //data select for APL, 0 : YCbCr, 1 : GBR, 2 : HSV, 3 : YSV, others : YCbCr
	UINT32 reg_apl_win_sel                  :2;	//(31:30,RW,0x00) //apl window selection 0 : BBD status, 1 : Win_A, 2 : Win_B, 3 : Win_C
	};
}PE_O22_REG_H10_FIM_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C58 RW 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RW,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C5C RW 0x0437_077F
	UINT32 x1                               :12;	//(11:0,RW,0x077F) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RW,0x0437) //y1
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C60 RW 0x0000_8000
	UINT32 hif_hist_address                 :5;	//(4:0,RW,0x0) //"0"   : 0th bin	…	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//(12,RW,0x00) //auto increment enable
	UINT32 reg_read_hist_sel                :2;	//(14:13,RW,0x00) //histogram selection for host read	0 : hist0	1 : hist1	others : hist2
	UINT32 hif_hist_enable                  :1;	//(15,RW,0x01) //0' : host access(read only)	'1' : normal operation
	UINT32 resvd1                           :12;
	UINT32 hist_rd_available                :1;	//(28,RW,0x00) //MUST read histogram during this bit '1'	  : read only
	UINT32 resvd2                           :1;
	UINT32 hist_read_enable                 :1;	//(30,RW,0x00) //histogram read mode enable
	UINT32 hist_read_done                   :1;	//(31,RW,0x00) //MUST SET '1' -> '0' for histogram reset(3 histograms = hist0~2)
	};
}PE_O22_REG_H10_FIM__HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C64 RW 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RW,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O22_REG_H10_FIM__HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C70 RO 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RO,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RO,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C74 RO 0x01DF_02CF
	UINT32 x1                               :12;	//(11:0,RO,0x02CF) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RO,0x01DF) //y1
	UINT32 resvd1                           :4;
	};
}PE_O22_REG_H10_FIM_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC0C78 RO 0x0000_0068
	UINT32 y_g_s_apl                        :10;	//(9:0,RO,0x068) //data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//(19:10,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//(29:20,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_O22_REG_H10_FIM_APL_STAT_00_T;

typedef struct {
	PE_O22_REG_H10_TOP_CTRL_00_T                       hdr_top_ctrl_00;	//0xCCCC0800
	PE_O22_REG_H10_TOP_CTRL_01_T                       hdr_top_ctrl_01;	//0xCCCC0804
	PE_O22_REG_H10_TOP_CTRL_02_T                       hdr_top_ctrl_02;	//0xCCCC0808
	PE_O22_REG_H10_TOP_CTRL_03_T                       hdr_top_ctrl_03;	//0xCCCC080C
	PE_O22_REG_H10_TOP_CTRL_04_T                       hdr_top_ctrl_04;	//0xCCCC0810
	PE_O22_REG_H10_TOP_CTRL_05_T                       hdr_top_ctrl_05;	//0xCCCC0814
	PE_O22_REG_H10_TOP_CTRL_06_T                       hdr_top_ctrl_06;	//0xCCCC0818
	PE_O22_REG_H10_TOP_CTRL_07_T                       hdr_top_ctrl_07;	//0xCCCC081C
	UINT32                                                    reserved0;	//0xCCCC0820
	UINT32                                                    reserved1;	//0xCCCC0824
	UINT32                                                    reserved2;	//0xCCCC0828
	UINT32                                                    reserved3;	//0xCCCC082C
	UINT32                                                    reserved4;	//0xCCCC0830
	UINT32                                                    reserved5;	//0xCCCC0834
	UINT32                                                    reserved6;	//0xCCCC0838
	UINT32                                                    reserved7;	//0xCCCC083C
	UINT32                                                    reserved8;	//0xCCCC0840
	UINT32                                                    reserved9;	//0xCCCC0844
	UINT32                                                   reserved10;	//0xCCCC0848
	UINT32                                                   reserved11;	//0xCCCC084C
	PE_O22_REG_H10_CSC1_CTRL_00_T                     hdr_csc1_ctrl_00;	//0xCCCC0850
	PE_O22_REG_H10_CSC1_CTRL_01_T                     hdr_csc1_ctrl_01;	//0xCCCC0854
	PE_O22_REG_H10_CSC1_CTRL_02_T                     hdr_csc1_ctrl_02;	//0xCCCC0858
	PE_O22_REG_H10_CSC1_CTRL_03_T                     hdr_csc1_ctrl_03;	//0xCCCC085C
	PE_O22_REG_H10_CSC1_CTRL_04_T                     hdr_csc1_ctrl_04;	//0xCCCC0860
	PE_O22_REG_H10_CSC1_CTRL_05_T                     hdr_csc1_ctrl_05;	//0xCCCC0864
	PE_O22_REG_H10_CSC1_CTRL_06_T                     hdr_csc1_ctrl_06;	//0xCCCC0868
	PE_O22_REG_H10_CSC1_CTRL_07_T                     hdr_csc1_ctrl_07;	//0xCCCC086C
	PE_O22_REG_H10_CSC1_CTRL_08_T                     hdr_csc1_ctrl_08;	//0xCCCC0870
	PE_O22_REG_H10_CSC1_CTRL_09_T                     hdr_csc1_ctrl_09;	//0xCCCC0874
	PE_O22_REG_H10_CSC1_ERR_CNT_T                     hdr_csc1_err_cnt;	//0xCCCC0878
	UINT32                                                   reserved12;	//0xCCCC087C
	PE_O22_REG_H10_PXL_RD_CTRL0_T                     hdr_pxl_rd_ctrl0;	//0xCCCC0880
	PE_O22_REG_H10_PXL_RD_CTRL1_T                     hdr_pxl_rd_ctrl1;	//0xCCCC0884
	PE_O22_REG_H10_PXL_RD_DATA_T                       hdr_pxl_rd_data;	//0xCCCC0888
	UINT32                                                   reserved13;	//0xCCCC088C
	PE_O22_REG_H10_EOTF_IA_CTRL_T                     hdr_eotf_ia_ctrl;	//0xCCCC0890
	PE_O22_REG_H10_EOTF_IA_DATA_T                     hdr_eotf_ia_data;	//0xCCCC0894
	PE_O22_REG_H10_OETF_IA_CTRL_T                     hdr_oetf_ia_ctrl;	//0xCCCC0898
	PE_O22_REG_H10_OETF_IA_DATA_T                     hdr_oetf_ia_data;	//0xCCCC089C
	PE_O22_REG_H10_PCC_CTRL_00_T                       hdr_pcc_ctrl_00;	//0xCCCC08A0
	PE_O22_REG_H10_PCC_CTRL_01_T                       hdr_pcc_ctrl_01;	//0xCCCC08A4
	PE_O22_REG_H10_PCC_CTRL_02_T                       hdr_pcc_ctrl_02;	//0xCCCC08A8
	PE_O22_REG_H10_PCC_CTRL_03_T                       hdr_pcc_ctrl_03;	//0xCCCC08AC
	PE_O22_REG_H10_PCC_CTRL_04_T                       hdr_pcc_ctrl_04;	//0xCCCC08B0
	PE_O22_REG_H10_PCC_CTRL_05_T                       hdr_pcc_ctrl_05;	//0xCCCC08B4
	UINT32                                                   reserved14;	//0xCCCC08B8
	UINT32                                                   reserved15;	//0xCCCC08BC
	UINT32                                                   reserved16;	//0xCCCC08C0
	UINT32                                                   reserved17;	//0xCCCC08C4
	UINT32                                                   reserved18;	//0xCCCC08C8
	UINT32                                                   reserved19;	//0xCCCC08CC
	PE_O22_REG_H10_HUE_SAT_CTRL_T                     hdr_hue_sat_ctrl;	//0xCCCC08D0
	PE_O22_REG_H10_HUE_SAT_ALPHA_CTRL_T         hdr_hue_sat_alpha_ctrl;	//0xCCCC08D4
	UINT32                                                   reserved20;	//0xCCCC08D8
	UINT32                                                   reserved21;	//0xCCCC08DC
	PE_O22_REG_H10_TCM_PREP_00_T                       hdr_tcm_prep_00;	//0xCCCC08E0
	PE_O22_REG_H10_TCM_PREP_01_T                       hdr_tcm_prep_01;	//0xCCCC08E4
	PE_O22_REG_H10_LL_LUT_IA_CTRL_T                 hdr_ll_lut_ia_ctrl;	//0xCCCC08E8
	PE_O22_REG_H10_LL_LUT_IA_DATA_T                 hdr_ll_lut_ia_data;	//0xCCCC08EC
	PE_O22_REG_H10_LL_HUE_CTRL_00_T                 hdr_ll_hue_ctrl_00;	//0xCCCC08F0
	PE_O22_REG_H10_LL_HUE_CTRL_01_T                 hdr_ll_hue_ctrl_01;	//0xCCCC08F4
	PE_O22_REG_H10_LL_HUE_CTRL_02_T                 hdr_ll_hue_ctrl_02;	//0xCCCC08F8
	UINT32                                                   reserved22;	//0xCCCC08FC
	PE_O22_REG_H10_LLPCC_CTRL_00_T                   hdr_llpcc_ctrl_00;	//0xCCCC0900
	PE_O22_REG_H10_LLPCC_CTRL_01_T                   hdr_llpcc_ctrl_01;	//0xCCCC0904
	PE_O22_REG_H10_LLPCC_CTRL_02_T                   hdr_llpcc_ctrl_02;	//0xCCCC0908
	PE_O22_REG_H10_LLPCC_CTRL_03_T                   hdr_llpcc_ctrl_03;	//0xCCCC090C
	PE_O22_REG_H10_LLPCC_CTRL_04_T                   hdr_llpcc_ctrl_04;	//0xCCCC0910
	PE_O22_REG_H10_LLPCC_CTRL_05_T                   hdr_llpcc_ctrl_05;	//0xCCCC0914
	PE_O22_REG_H10_LL_AB_CTRL_00_T                   hdr_ll_ab_ctrl_00;	//0xCCCC0918
	PE_O22_REG_H10_LL_AB_CTRL_01_T                   hdr_ll_ab_ctrl_01;	//0xCCCC091C
	PE_O22_REG_H10_LL_AB_CTRL_02_T                   hdr_ll_ab_ctrl_02;	//0xCCCC0920
	PE_O22_REG_H10_LL_AB_CTRL_03_T                   hdr_ll_ab_ctrl_03;	//0xCCCC0924
	PE_O22_REG_H10_LL_AB_CTRL_04_T                   hdr_ll_ab_ctrl_04;	//0xCCCC0928
	UINT32                                                   reserved23;	//0xCCCC092C
	UINT32                                                   reserved24;	//0xCCCC0930
	UINT32                                                   reserved25;	//0xCCCC0934
	UINT32                                                   reserved26;	//0xCCCC0938
	UINT32                                                   reserved27;	//0xCCCC093C
	PE_O22_REG_H10_HIST_CTRL_00_T                     hdr_hist_ctrl_00;	//0xCCCC0940
	PE_O22_REG_H10_HIST_CTRL_01_T                     hdr_hist_ctrl_01;	//0xCCCC0944
	PE_O22_REG_H10_HIST_CTRL_02_T                     hdr_hist_ctrl_02;	//0xCCCC0948
	PE_O22_REG_H10_HIST_CTRL_03_T                     hdr_hist_ctrl_03;	//0xCCCC094C
	PE_O22_REG_H10_HIST_CTRL_04_T                     hdr_hist_ctrl_04;	//0xCCCC0950
	PE_O22_REG_H10_HIST_IA_CTRL_T                     hdr_hist_ia_ctrl;	//0xCCCC0954
	PE_O22_REG_H10_HIST_IA_DATA1_T                   hdr_hist_ia_data1;	//0xCCCC0958
	PE_O22_REG_H10_HIST_IA_DATA2_T                   hdr_hist_ia_data2;	//0xCCCC095C
	UINT32                                                   reserved28;	//0xCCCC0960
	UINT32                                                   reserved29;	//0xCCCC0964
	UINT32                                                   reserved30;	//0xCCCC0968
	UINT32                                                   reserved31;	//0xCCCC096C
	PE_O22_REG_H10_TPG_CTRL_00_T                       hdr_tpg_ctrl_00;	//0xCCCC0970
	PE_O22_REG_H10_TPG_CTRL_01_T                       hdr_tpg_ctrl_01;	//0xCCCC0974
	PE_O22_REG_H10_TPG_CTRL_02_T                       hdr_tpg_ctrl_02;	//0xCCCC0978
	PE_O22_REG_H10_TPG_CTRL_03_T                       hdr_tpg_ctrl_03;	//0xCCCC097C
	PE_O22_REG_H10_TPG_CTRL_04_T                       hdr_tpg_ctrl_04;	//0xCCCC0980
	PE_O22_REG_H10_TPG_IA_CTRL_T                       hdr_tpg_ia_ctrl;	//0xCCCC0984
	PE_O22_REG_H10_TPG_IA_DATA_T                       hdr_tpg_ia_data;	//0xCCCC0988
	UINT32                                                   reserved32;	//0xCCCC098C
	PE_O22_REG_H10_CLUT_CTRL_00_T                     hdr_clut_ctrl_00;	//0xCCCC0990
	PE_O22_REG_H10_CLUT_IA_CTRL_T                     hdr_clut_ia_ctrl;	//0xCCCC0994
	PE_O22_REG_H10_CLUT_IA_DATA_T                     hdr_clut_ia_data;	//0xCCCC0998
	PE_O22_REG_H10_PLUT_CTRL_00_T                     hdr_plut_ctrl_00;	//0xCCCC099C
	PE_O22_REG_H10_PLUT_IA_CTRL_T                     hdr_plut_ia_ctrl;	//0xCCCC09A0
	PE_O22_REG_H10_PLUT_IA_DATA_T                     hdr_plut_ia_data;	//0xCCCC09A4
	PE_O22_REG_H10_SLUT_CTRL_00_T                     hdr_slut_ctrl_00;	//0xCCCC09A8
	PE_O22_REG_H10_SLUT_IA_CTRL_T                     hdr_slut_ia_ctrl;	//0xCCCC09AC
	PE_O22_REG_H10_SLUT_IA_DATA_T                     hdr_slut_ia_data;	//0xCCCC09B0
	PE_O22_REG_H10_ILUT_CTRL_00_T                     hdr_ilut_ctrl_00;	//0xCCCC09B4
	PE_O22_REG_H10_ILUT_IA_CTRL_T                     hdr_ilut_ia_ctrl;	//0xCCCC09B8
	PE_O22_REG_H10_ILUT_IA_DATA_T                     hdr_ilut_ia_data;	//0xCCCC09BC
	PE_O22_REG_H10_DLUT_CTRL_00_T                     hdr_dlut_ctrl_00;	//0xCCCC09C0
	PE_O22_REG_H10_DLUT_CTRL_01_T                     hdr_dlut_ctrl_01;	//0xCCCC09C4
	PE_O22_REG_H10_DLUT_CTRL_02_T                     hdr_dlut_ctrl_02;	//0xCCCC09C8
	PE_O22_REG_H10_DLUT_IA_CTRL_T                     hdr_dlut_ia_ctrl;	//0xCCCC09CC
	PE_O22_REG_H10_DLUT_IA_DATA_T                     hdr_dlut_ia_data;	//0xCCCC09D0
	PE_O22_REG_H10_TC_CTRL_00_T                         hdr_tc_ctrl_00;	//0xCCCC09D4
	PE_O22_REG_H10_TC_CTRL_01_T                         hdr_tc_ctrl_01;	//0xCCCC09D8
	PE_O22_REG_H10_TC_CTRL_02_T                         hdr_tc_ctrl_02;	//0xCCCC09DC
	PE_O22_REG_H10_TC_CTRL_03_T                         hdr_tc_ctrl_03;	//0xCCCC09E0
	PE_O22_REG_H10_TC_CTRL_04_T                         hdr_tc_ctrl_04;	//0xCCCC09E4
	UINT32                                                   reserved33;	//0xCCCC09E8
	UINT32                                                   reserved34;	//0xCCCC09EC
	UINT32                                                   reserved35;	//0xCCCC09F0
	UINT32                                                   reserved36;	//0xCCCC09F4
	UINT32                                                   reserved37;	//0xCCCC09F8
	UINT32                                                   reserved38;	//0xCCCC09FC
	PE_O22_REG_H10_LLUT0_CTRL_00_T                   hdr_llut0_ctrl_00;	//0xCCCC0A00
	PE_O22_REG_H10_LLUT0_CTRL_01_T                   hdr_llut0_ctrl_01;	//0xCCCC0A04
	PE_O22_REG_H10_LLUT0_CTRL_02_T                   hdr_llut0_ctrl_02;	//0xCCCC0A08
	PE_O22_REG_H10_LLUT0_CTRL_03_T                   hdr_llut0_ctrl_03;	//0xCCCC0A0C
	PE_O22_REG_H10_LLUT0_CTRL_04_T                   hdr_llut0_ctrl_04;	//0xCCCC0A10
	PE_O22_REG_H10_LLUT0_CTRL_05_T                   hdr_llut0_ctrl_05;	//0xCCCC0A14
	PE_O22_REG_H10_LLUT0_CTRL_06_T                   hdr_llut0_ctrl_06;	//0xCCCC0A18
	UINT32                                                   reserved39;	//0xCCCC0A1C
	PE_O22_REG_H10_LLUT0_IA_CTRL_T                   hdr_llut0_ia_ctrl;	//0xCCCC0A20
	PE_O22_REG_H10_LLUT0_IA_DATA_T                   hdr_llut0_ia_data;	//0xCCCC0A24
	UINT32                                                   reserved40;	//0xCCCC0A28
	UINT32                                                   reserved41;	//0xCCCC0A2C
	PE_O22_REG_H10_LLUT1_CTRL_00_T                   hdr_llut1_ctrl_00;	//0xCCCC0A30
	PE_O22_REG_H10_LLUT1_CTRL_01_T                   hdr_llut1_ctrl_01;	//0xCCCC0A34
	PE_O22_REG_H10_LLUT1_CTRL_02_T                   hdr_llut1_ctrl_02;	//0xCCCC0A38
	PE_O22_REG_H10_LLUT1_CTRL_03_T                   hdr_llut1_ctrl_03;	//0xCCCC0A3C
	PE_O22_REG_H10_LLUT1_CTRL_04_T                   hdr_llut1_ctrl_04;	//0xCCCC0A40
	PE_O22_REG_H10_LLUT1_CTRL_05_T                   hdr_llut1_ctrl_05;	//0xCCCC0A44
	PE_O22_REG_H10_LLUT1_CTRL_06_T                   hdr_llut1_ctrl_06;	//0xCCCC0A48
	UINT32                                                   reserved42;	//0xCCCC0A4C
	PE_O22_REG_H10_LLUT1_IA_CTRL_T                   hdr_llut1_ia_ctrl;	//0xCCCC0A50
	PE_O22_REG_H10_LLUT1_IA_DATA_T                   hdr_llut1_ia_data;	//0xCCCC0A54
	UINT32                                                   reserved43;	//0xCCCC0A58
	UINT32                                                   reserved44;	//0xCCCC0A5C
	PE_O22_REG_H10_LLUT2_CTRL_00_T                   hdr_llut2_ctrl_00;	//0xCCCC0A60
	PE_O22_REG_H10_LLUT2_CTRL_01_T                   hdr_llut2_ctrl_01;	//0xCCCC0A64
	PE_O22_REG_H10_LLUT2_CTRL_02_T                   hdr_llut2_ctrl_02;	//0xCCCC0A68
	PE_O22_REG_H10_LLUT2_CTRL_03_T                   hdr_llut2_ctrl_03;	//0xCCCC0A6C
	PE_O22_REG_H10_LLUT2_CTRL_04_T                   hdr_llut2_ctrl_04;	//0xCCCC0A70
	PE_O22_REG_H10_LLUT2_CTRL_05_T                   hdr_llut2_ctrl_05;	//0xCCCC0A74
	PE_O22_REG_H10_LLUT2_CTRL_06_T                   hdr_llut2_ctrl_06;	//0xCCCC0A78
	UINT32                                                   reserved45;	//0xCCCC0A7C
	PE_O22_REG_H10_LLUT2_IA_CTRL_T                   hdr_llut2_ia_ctrl;	//0xCCCC0A80
	PE_O22_REG_H10_LLUT2_IA_DATA_T                   hdr_llut2_ia_data;	//0xCCCC0A84
	UINT32                                                   reserved46;	//0xCCCC0A88
	UINT32                                                   reserved47;	//0xCCCC0A8C
	PE_O22_REG_H10_GAMMA045_CTRL_00_T             hdr_gamma045_ctrl_00;	//0xCCCC0A90
	UINT32                                                   reserved48;	//0xCCCC0A94
	PE_O22_REG_H10_DITHER_CTRL_00_T                 hdr_dither_ctrl_00;	//0xCCCC0A98
	PE_O22_REG_H10_PCC32_GAIN_CTRL_T               hdr_pcc32_gain_ctrl;	//0xCCCC0A9C
	PE_O22_REG_H10_CSC3_CTRL_00_T                     hdr_csc3_ctrl_00;	//0xCCCC0AA0
	PE_O22_REG_H10_CSC3_CTRL_01_T                     hdr_csc3_ctrl_01;	//0xCCCC0AA4
	PE_O22_REG_H10_CSC3_CTRL_02_T                     hdr_csc3_ctrl_02;	//0xCCCC0AA8
	PE_O22_REG_H10_CSC3_CTRL_03_T                     hdr_csc3_ctrl_03;	//0xCCCC0AAC
	PE_O22_REG_H10_CSC3_CTRL_04_T                     hdr_csc3_ctrl_04;	//0xCCCC0AB0
	PE_O22_REG_H10_CSC3_CTRL_05_T                     hdr_csc3_ctrl_05;	//0xCCCC0AB4
	PE_O22_REG_H10_CSC3_CTRL_06_T                     hdr_csc3_ctrl_06;	//0xCCCC0AB8
	PE_O22_REG_H10_CSC3_CTRL_07_T                     hdr_csc3_ctrl_07;	//0xCCCC0ABC
	PE_O22_REG_H10_CSC3_CTRL_08_T                     hdr_csc3_ctrl_08;	//0xCCCC0AC0
	UINT32                                                   reserved49;	//0xCCCC0AC4
	UINT32                                                   reserved50;	//0xCCCC0AC8
	UINT32                                                   reserved51;	//0xCCCC0ACC
	PE_O22_REG_H10_TCM_SLUT0_00_T                     hdr_tcm_slut0_00;	//0xCCCC0AD0
	PE_O22_REG_H10_TCM_SLUT0_01_T                     hdr_tcm_slut0_01;	//0xCCCC0AD4
	PE_O22_REG_H10_TCM_SLUT0_02_T                     hdr_tcm_slut0_02;	//0xCCCC0AD8
	PE_O22_REG_H10_TCM_SLUT0_03_T                     hdr_tcm_slut0_03;	//0xCCCC0ADC
	PE_O22_REG_H10_TCM_SLUT0_04_T                     hdr_tcm_slut0_04;	//0xCCCC0AE0
	PE_O22_REG_H10_TCM_SLUT0_05_T                     hdr_tcm_slut0_05;	//0xCCCC0AE4
	PE_O22_REG_H10_TCM_SLUT0_06_T                     hdr_tcm_slut0_06;	//0xCCCC0AE8
	PE_O22_REG_H10_TCM_SLUT0_07_T                     hdr_tcm_slut0_07;	//0xCCCC0AEC
	PE_O22_REG_H10_TCM_SLUT0_08_T                     hdr_tcm_slut0_08;	//0xCCCC0AF0
	PE_O22_REG_H10_TCM_SLUT0_09_T                     hdr_tcm_slut0_09;	//0xCCCC0AF4
	PE_O22_REG_H10_SAT_MAP_CTRL_01_T               hdr_sat_map_ctrl_01;	//0xCCCC0AF8
	PE_O22_REG_H10_SAT_MAP_CTRL_02_T               hdr_sat_map_ctrl_02;	//0xCCCC0AFC
	UINT32                                                   reserved52;	//0xCCCC0B00
	UINT32                                                   reserved53;	//0xCCCC0B04
	UINT32                                                   reserved54;	//0xCCCC0B08
	UINT32                                                   reserved55;	//0xCCCC0B0C
	UINT32                                                   reserved56;	//0xCCCC0B10
	UINT32                                                   reserved57;	//0xCCCC0B14
	UINT32                                                   reserved58;	//0xCCCC0B18
	UINT32                                                   reserved59;	//0xCCCC0B1C
	PE_O22_REG_H10_YGAIN_LUT_CTRL_00_T           hdr_ygain_lut_ctrl_00;	//0xCCCC0B20
	PE_O22_REG_H10_YGAIN_LUT_CTRL_01_T           hdr_ygain_lut_ctrl_01;	//0xCCCC0B24
	PE_O22_REG_H10_YGAIN_LUT_CTRL_02_T           hdr_ygain_lut_ctrl_02;	//0xCCCC0B28
	PE_O22_REG_H10_YGAIN_LUT_CTRL_03_T           hdr_ygain_lut_ctrl_03;	//0xCCCC0B2C
	PE_O22_REG_H10_YGAIN_LUT_CTRL_04_T           hdr_ygain_lut_ctrl_04;	//0xCCCC0B30
	PE_O22_REG_H10_YGAIN_LUT_CTRL_05_T           hdr_ygain_lut_ctrl_05;	//0xCCCC0B34
	PE_O22_REG_H10_YGAIN_LUT_IA_CTRL_T           hdr_ygain_lut_ia_ctrl;	//0xCCCC0B38
	PE_O22_REG_H10_YGAIN_LUT_IA_DATA_T           hdr_ygain_lut_ia_data;	//0xCCCC0B3C
	PE_O22_REG_H10_RGB2Y_CTRL_00_T                   hdr_rgb2y_ctrl_00;	//0xCCCC0B40
	PE_O22_REG_H10_RGB2Y_CTRL_01_T                   hdr_rgb2y_ctrl_01;	//0xCCCC0B44
	PE_O22_REG_H10_RGB2Y_CTRL_02_T                   hdr_rgb2y_ctrl_02;	//0xCCCC0B48
	PE_O22_REG_H10_RGB2Y_CTRL_03_T                   hdr_rgb2y_ctrl_03;	//0xCCCC0B4C
	UINT32                                                   reserved60;	//0xCCCC0B50
	UINT32                                                   reserved61;	//0xCCCC0B54
	UINT32                                                   reserved62;	//0xCCCC0B58
	UINT32                                                   reserved63;	//0xCCCC0B5C
	PE_O22_REG_H10_LGAIN_LUT_CTRL_00_T           hdr_lgain_lut_ctrl_00;	//0xCCCC0B60
	PE_O22_REG_H10_LGAIN_LUT_CTRL_01_T           hdr_lgain_lut_ctrl_01;	//0xCCCC0B64
	PE_O22_REG_H10_LGAIN_LUT_CTRL_02_T           hdr_lgain_lut_ctrl_02;	//0xCCCC0B68
	PE_O22_REG_H10_LGAIN_LUT_CTRL_03_T           hdr_lgain_lut_ctrl_03;	//0xCCCC0B6C
	PE_O22_REG_H10_LGAIN_LUT_CTRL_04_T           hdr_lgain_lut_ctrl_04;	//0xCCCC0B70
	PE_O22_REG_H10_LGAIN_LUT_CTRL_05_T           hdr_lgain_lut_ctrl_05;	//0xCCCC0B74
	PE_O22_REG_H10_LGAIN_LUT_CTRL_06_T           hdr_lgain_lut_ctrl_06;	//0xCCCC0B78
	PE_O22_REG_H10_LGAIN_LUT_CTRL_07_T           hdr_lgain_lut_ctrl_07;	//0xCCCC0B7C
	PE_O22_REG_H10_SGAIN_LUT_CTRL_00_T           hdr_sgain_lut_ctrl_00;	//0xCCCC0B80
	PE_O22_REG_H10_SGAIN_LUT_CTRL_01_T           hdr_sgain_lut_ctrl_01;	//0xCCCC0B84
	PE_O22_REG_H10_SGAIN_LUT_CTRL_02_T           hdr_sgain_lut_ctrl_02;	//0xCCCC0B88
	PE_O22_REG_H10_SGAIN_LUT_CTRL_03_T           hdr_sgain_lut_ctrl_03;	//0xCCCC0B8C
	PE_O22_REG_H10_SGAIN_LUT_CTRL_04_T           hdr_sgain_lut_ctrl_04;	//0xCCCC0B90
	PE_O22_REG_H10_SGAIN_LUT_CTRL_05_T           hdr_sgain_lut_ctrl_05;	//0xCCCC0B94
	PE_O22_REG_H10_SGAIN_LUT_CTRL_06_T           hdr_sgain_lut_ctrl_06;	//0xCCCC0B98
	PE_O22_REG_H10_SGAIN_LUT_CTRL_07_T           hdr_sgain_lut_ctrl_07;	//0xCCCC0B9C
	PE_O22_REG_H10_RGB2Y2_CTRL_00_T                 hdr_rgb2y2_ctrl_00;	//0xCCCC0BA0
	PE_O22_REG_H10_RGB2Y2_CTRL_01_T                 hdr_rgb2y2_ctrl_01;	//0xCCCC0BA4
	PE_O22_REG_H10_RGB2Y2_CTRL_02_T                 hdr_rgb2y2_ctrl_02;	//0xCCCC0BA8
	PE_O22_REG_H10_RGB2Y2_CTRL_03_T                 hdr_rgb2y2_ctrl_03;	//0xCCCC0BAC
	PE_O22_REG_H10_CSC4_CTRL_00_T                     hdr_csc4_ctrl_00;	//0xCCCC0BB0
	PE_O22_REG_H10_CSC4_CTRL_01_T                     hdr_csc4_ctrl_01;	//0xCCCC0BB4
	PE_O22_REG_H10_CSC4_CTRL_02_T                     hdr_csc4_ctrl_02;	//0xCCCC0BB8
	PE_O22_REG_H10_CSC4_CTRL_03_T                     hdr_csc4_ctrl_03;	//0xCCCC0BBC
	PE_O22_REG_H10_CSC4_CTRL_04_T                     hdr_csc4_ctrl_04;	//0xCCCC0BC0
	PE_O22_REG_H10_CSC4_CTRL_05_T                     hdr_csc4_ctrl_05;	//0xCCCC0BC4
	PE_O22_REG_H10_CSC4_CTRL_06_T                     hdr_csc4_ctrl_06;	//0xCCCC0BC8
	PE_O22_REG_H10_CSC4_CTRL_07_T                     hdr_csc4_ctrl_07;	//0xCCCC0BCC
	PE_O22_REG_H10_CSC4_CTRL_08_T                     hdr_csc4_ctrl_08;	//0xCCCC0BD0
	UINT32                                                   reserved64;	//0xCCCC0BD4
	UINT32                                                   reserved65;	//0xCCCC0BD8
	UINT32                                                   reserved66;	//0xCCCC0BDC
	UINT32                                                   reserved67;	//0xCCCC0BE0
	UINT32                                                   reserved68;	//0xCCCC0BE4
	UINT32                                                   reserved69;	//0xCCCC0BE8
	UINT32                                                   reserved70;	//0xCCCC0BEC
	UINT32                                                   reserved71;	//0xCCCC0BF0
	UINT32                                                   reserved72;	//0xCCCC0BF4
	UINT32                                                   reserved73;	//0xCCCC0BF8
	UINT32                                                   reserved74;	//0xCCCC0BFC
	PE_O22_REG_H10_FIM_GFD_CTRL_00_T               hdr_fim_gfd_ctrl_00;	//0xCCCC0C00
	PE_O22_REG_H10_FIM_GFD_CTRL_01_T               hdr_fim_gfd_ctrl_01;	//0xCCCC0C04
	PE_O22_REG_H10_FIM_GFD_STAT_00_T               hdr_fim_gfd_stat_00;	//0xCCCC0C08
	PE_O22_REG_H10_FIM_GFD_STAT_01_T               hdr_fim_gfd_stat_01;	//0xCCCC0C0C
	PE_O22_REG_H10_FIM_GFD_STAT_02_T               hdr_fim_gfd_stat_02;	//0xCCCC0C10
	PE_O22_REG_H10_FIM_GFD_STAT_03_T               hdr_fim_gfd_stat_03;	//0xCCCC0C14
	PE_O22_REG_H10_FIM_PCG_OFF_T                       hdr_fim_pcg_off;	//0xCCCC0C18
	UINT32                                                   reserved75;	//0xCCCC0C1C
	PE_O22_REG_H10_FIM_TPD_CTRL_00_T               hdr_fim_tpd_ctrl_00;	//0xCCCC0C20
	PE_O22_REG_H10_FIM_TPD_CTRL_01_T               hdr_fim_tpd_ctrl_01;	//0xCCCC0C24
	PE_O22_REG_H10_FIM_TPD_CTRL_02_T               hdr_fim_tpd_ctrl_02;	//0xCCCC0C28
	PE_O22_REG_H10_FIM_TPD_CTRL_03_T               hdr_fim_tpd_ctrl_03;	//0xCCCC0C2C
	PE_O22_REG_H10_FIM_TPD_CTRL_04_T               hdr_fim_tpd_ctrl_04;	//0xCCCC0C30
	PE_O22_REG_H10_FIM_TPD_CTRL_05_T               hdr_fim_tpd_ctrl_05;	//0xCCCC0C34
	PE_O22_REG_H10_FIM_TPD_CTRL_06_T               hdr_fim_tpd_ctrl_06;	//0xCCCC0C38
	PE_O22_REG_H10_FIM_TPD_CTRL_07_T               hdr_fim_tpd_ctrl_07;	//0xCCCC0C3C
	PE_O22_REG_H10_FIM_TPD_CTRL_08_T               hdr_fim_tpd_ctrl_08;	//0xCCCC0C40
	PE_O22_REG_H10_FIM_TPD_CTRL_09_T               hdr_fim_tpd_ctrl_09;	//0xCCCC0C44
	PE_O22_REG_H10_FIM_TPD_CTRL_0A_T               hdr_fim_tpd_ctrl_0a;	//0xCCCC0C48
	PE_O22_REG_H10_FIM_TPD_CTRL_0B_T               hdr_fim_tpd_ctrl_0b;	//0xCCCC0C4C
	PE_O22_REG_H10_FIM_TPD_STAT_00_T               hdr_fim_tpd_stat_00;	//0xCCCC0C50
	PE_O22_REG_H10_FIM_BBD_CTRL_00_T               hdr_fim_bbd_ctrl_00;	//0xCCCC0C54
	PE_O22_REG_H10_FIM_BBD_CTRL_01_T               hdr_fim_bbd_ctrl_01;	//0xCCCC0C58
	PE_O22_REG_H10_FIM_BBD_CTRL_02_T               hdr_fim_bbd_ctrl_02;	//0xCCCC0C5C
	PE_O22_REG_H10_FIM__HIST_AI_CTRL_T           hdr_fim__hist_ai_ctrl;	//0xCCCC0C60
	PE_O22_REG_H10_FIM__HIST_AI_DATA_T           hdr_fim__hist_ai_data;	//0xCCCC0C64
	UINT32                                                   reserved76;	//0xCCCC0C68
	UINT32                                                   reserved77;	//0xCCCC0C6C
	PE_O22_REG_H10_FIM_BBD_STAT_00_T               hdr_fim_bbd_stat_00;	//0xCCCC0C70
	PE_O22_REG_H10_FIM_BBD_STAT_01_T               hdr_fim_bbd_stat_01;	//0xCCCC0C74
	PE_O22_REG_H10_FIM_APL_STAT_00_T               hdr_fim_apl_stat_00;	//0xCCCC0C78
}PE_O22_REG_H10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC2100 RW 0x0000_0000
	UINT32 hdr0_sv                           :10; //(09:00), hdr0 symetric v (tb diff v) (SICDTV-15739)
	UINT32 resvd0                            :6;  //(15:10)
	UINT32 hdr0_sh                           :10; //(25:16), hdr0 symetric h (lr diff h)
	UINT32 resvd1                            :5;  //(30:26)
	UINT32 rd_available                      :1;  //(31:31), rd_available
	};
}PE_O22_REG_HDR_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC2104 RW 0x0000_0000
	UINT32 hdr1_sv                           :10; //(09:00), hdr1 symetric v (tb diff v)
	UINT32 resvd0                            :6;  //(15:10)
	UINT32 hdr1_sh                           :10; //(25:16), hdr1 symetric h (lr diff h)
	UINT32 resvd1                            :5;  //(30:26)
	UINT32 rd_available                      :1;  //(31:31), rd_available
	};
}PE_O22_REG_HDR_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC2108 RW 0x0000_0000
	UINT32 reg_sys_veri_2                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_REG_HDR_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCCC210C RW 0x0000_0000
	UINT32 reg_sys_veri_3                   :32;	//(31:0,RW,0x0000_0000) //
	};
}PE_O22_REG_HDR_VERI_3_T;

typedef struct {
	PE_O22_REG_HDR_VERI_0_T hdr_veri_0;	//0xCCCC2100
	PE_O22_REG_HDR_VERI_1_T hdr_veri_1;	//0xCCCC2104
	PE_O22_REG_HDR_VERI_2_T hdr_veri_2;	//0xCCCC2108
	PE_O22_REG_HDR_VERI_3_T hdr_veri_3;	//0xCCCC210C
}PE_O22_REG_HDR_VERI_T;

#endif

