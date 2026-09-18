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
#ifndef _PE_HDR_REG_O26A0_H_
#define _PE_HDR_REG_O26A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif


typedef union {
	UINT32 udata32;
	struct {						//0xCC230800 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0:0,RW,0x00) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1:1,RW,0x00) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2:2,RW,0x00) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O26_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230804 RW 0x0870_0F00
	UINT32 width                            :16;	//(15:0,RW,0xF00) //width
	UINT32 height                           :16;	//(31:16,RW,0x870) //height
	};
}PE_O26_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230808 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,RW,0x0000_0014) //vdpulse position for register loading
	};
}PE_O26_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23080C RO 0x0000_0000
	UINT32 vcnt                             :16;	//(15:0,RO,0x0) //vertical line count
	UINT32 vcnt2                            :16;	//(31:16,RO,0x0) //vertical line number
	};
}PE_O26_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230810 RO 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,RO,0x0800) //apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//(30:30,RO,0x00) //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//(31:31,RO,0x00) //Vertical Active at PE1 output(Read only)
	};
}PE_O26_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230814 RW 0x0000_0000
	UINT32 reg_hue_sat_prsv_ref             :1;	//(0:0,RW,0x0) //0: hue/sat ref source from pcc32 output	1: hue/sat ref source from lg gamma output
	UINT32 resvd0                           :3;
	UINT32 reg_tcm_inp_src                  :1;	//(4:4,RW,0x0) //0: Tone Map input source = OETF Out 	1: Tone Map input source = OETF Input
	UINT32 resvd1                           :3;
	UINT32 reg_hdr10_cuva_gain_mode         :2;	//(9:8,RW,0x0) //0 : Saturation Mapping gain from HDR10+ Tone Mapping LUT	1 : Saturation Mapping gain from CUVA PQ SRC (in max rgb)	2 : Saturation Mapping gain from CUVA HLG SRC (pcc32 luma)	3 : Saturation Mapping gain from CUVA PQ SRC (in luma)
	UINT32 resvd2                           :6;
	UINT32 reg_hue_sat_prsv_src             :2;	//(17:16,RW,0x0) //(deprecated)
	UINT32 resvd3                           :2;
	UINT32 reg_hist_src                     :4;	//(23:20,RW,0x0) //1:R, 2:G, 3:B, 4:MAX(RGB)	5:Y, 6:Cb, 7:Cr	8:Technicolor G, 9: Technicolor B, 10 : Technicolor R	11: Technicolor MAX(RGB)	15: MAX(YCbCr) Others: Y
	UINT32 reg_eotf_en                      :1;	//(24:24,RW,0x0) //EOTF block enable
	UINT32 reg_oetf_en                      :1;	//(25:25,RW,0x0) //OETF block enable
	UINT32 resvd4                           :2;
	UINT32 reg_hdr10p_mode                  :1;	//(28:28,RW,0x00) //0: HDR10 Mode	1: HDR10+ Mode
	UINT32 reg_use_equal_llut_en            :1;	//(29:29,RW,0x00) //0:use luminanace LUT channel G hif, 	1:use own LUT hif(B/R)(WR only)
	UINT32 reg_hdr10_mode                   :1;	//(30:30,RW,0x0) //0: Bypass HDR10 Path	1: Run HDR10
	UINT32 resvd5                           :1;
	};
}PE_O26_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230818 RW 0x0000_0000
	UINT32 reg_hdr_eotf_120hz_mode          :1;	//(0:0,RW,0x00) //1: Nullify all settings about double buffer of EOTF
	UINT32 reg_eotf_same_write_mode         :1;	//(1:1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 EOTF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_eotf_dbuf_mode               :1;	//(4:4,RW,0x00) //1: use EOTF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_dbuf_wptr               :1;	//(8:8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_eotf_dbuf_rptr               :1;	//(12:12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_eotf_dbuf_ptr_imode          :1;	//(16:16,RW,0x00) //1: eotf_rptr = ~ eotf_wptr (ignore [12] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_eotf_ra_mode                 :1;	//(24:24,RW,0x00) //1: eotf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O26_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23081C RW 0x0000_0000
	UINT32 reg_hdr_oetf_120hz_mode          :1;	//(0:0,RW,0x00) //1: Nullify all settings about double buffer of OETF
	UINT32 reg_oetf_same_write_mode         :1;	//(1:1,RW,0x00) //1: Write Same LUT Entry in both HDR0/1 OETF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_oetf_dbuf_mode               :1;	//(4:4,RW,0x00) //1: use OETF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_oetf_dbuf_wptr               :1;	//(8:8,RW,0x00) //write pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_oetf_dbuf_rptr               :1;	//(12:12,RW,0x00) //read pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_oetf_dbuf_ptr_imode          :1;	//(16:16,RW,0x00) //1: oetf_rptr = ~ oetf_wptr (ignore [13] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_oetf_ra_mode                 :1;	//(24:24,RW,0x00) //1: oetf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O26_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230850 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0:0,RW,0x01) //
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230854 RW 0x12AF_7CFE
	UINT32 r_csc1st_coef1                   :15;	//(14:0,RW,0x7CFE) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230858 RW 0x7590_12AF
	UINT32 r_csc1st_coef3                   :15;	//(14:0,RW,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,RW,0x7590) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23085C RW 0x225F_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,RW,0x225F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230860 RW 0x12AF_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230864 RW 0x1AF0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,RW,0x1AF0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230868 RW 0x1F00_1800
	UINT32 r_csc1st_ofst1                   :13;	//(12:0,RW,0x1800) //
	UINT32 resvd0                           :3;
	UINT32 r_csc1st_ofst0                   :13;	//(28:16,RW,0x1F00) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23086C RW 0x1800_0000
	UINT32 r_csc1st_ofst3                   :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 r_csc1st_ofst2                   :13;	//(28:16,RW,0x1800) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230870 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :13;	//(12:0,RW,0x00) //
	UINT32 resvd0                           :3;
	UINT32 r_csc1st_ofst4                   :13;	//(28:16,RW,0x00) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230874 RW 0x0000_0000
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
}PE_O26_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230878 RO 0x0000_0000
	UINT32 ireg_csc_cnt_under               :16;	//(15:0,RO,0x0) //
	UINT32 ireg_csc_cnt_over                :16;	//(31:16,RO,0x0) //
	};
}PE_O26_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230880 RW 0x0000_FFFF
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
	UINT32 r_pxl_rd_mark_en                 :1;	//(24:24,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//(28:28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230884 RW 0x0000_0000
	UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230888 RO 0x0000_0000
	UINT32 pxl_read_rcr                     :12;	//(11:0,RO,0x00) //
	UINT32 resvd0                           :4;
	UINT32 pxl_read_bcb                     :12;	//(27:16,RO,0x00) //
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_PXL_RD_DATA0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23088C RO 0x0000_0000
	UINT32 pxl_read_gyy                     :12;	//(11:0,RO,0x00) //
	UINT32 resvd                            :20;
	};
}PE_O26_REG_H10_PXL_RD_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230890 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O26_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230894 RW 0x0000_0000
	UINT32 eotf_lut_data                    :32;	//(31:0,RW,0x0000_0000) //32 bit LUT data
	};
}PE_O26_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230898 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O26_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23089C RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :16;	//(15:0,RW,0x0) //16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//(31:16,RW,0x0) //16 bit even LUT data
	};
}PE_O26_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308A0 RW 0x0000_0001
	UINT32 reg_pcc_en                       :1;	//(0,RW,0x1) //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308A4 RW 0x1220_7FDE
	UINT32 r_pcc_coef1                      :15;	//(14:0,RW,0x7FDE) //PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//(30:16,RW,0x1220) //PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308A8 RW 0x7E02_7E64
	UINT32 r_pcc_coef3                      :15;	//(14:0,RW,0x7E64) //PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//(30:16,RW,0x7E02) //PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308AC RW 0x11E6_7FB6
	UINT32 r_pcc_coef5                      :15;	//(14:0,RW,0x7FB6) //PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//(30:16,RW,0x11E6) //PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308B0 RW 0x7F10_7ED6
	UINT32 r_pcc_coef7                      :15;	//(14:0,RW,0x7ED6) //PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//(30:16,RW,0x7F10) //PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308B4 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//(30:16,RW,0x1A91) //PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308D0 RW 0x0000_3FF3
	UINT32 reg_hue_prsv_en                  :1;	//(0,RW,0x1) //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//(1,RW,0x1) //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//(13:4,RW,0x3FF) //0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//(25:16,RW,0x000) //0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_O26_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308D4 NA 0x0000_1000
	UINT32 reg_inp_l_sel                    :1;	//(0,RW,0x0) //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//(4,RW,0x0) //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//(8,RW,0x0) //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//(12,RW,0x1) //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_O26_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308E0 RW 0x121F_7FDE
	UINT32 r_tone_map_rgb2y_coef1           :15;	//(14:0,RW,0x7FDE) //
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//(30:16,RW,0x121F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308E4 RW 0x7E02_0000
	UINT32 r_tone_map_rgbymax_sel           :3;	//(2:0,RW,0x0) //
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//(30:16,RW,0x7E02) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308E8 RW 0x0000_0000
	UINT32 ll_lut_addr                      :8;	//(7:0,RW,0x00) //indirect address
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd0                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :19;
	};
}PE_O26_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308EC RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,RW,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,RW,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308F0 RW 0x1000_03FF
	UINT32 reg_alpha_hue                    :10;	//(9:0,RW,0x3FF) //alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//(25:16,RW,0x00) //alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//(28,RW,0x01) //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308F4 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//(16,RW,0x0) //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2308F8 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(30:16,RW,0x0) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230900 RW 0x0000_0001
	UINT32 reg_ll_pcc_en                    :1;	//(0,RW,0x1) //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230904 RW 0x1220_7FDE
	UINT32 r_ll_pcc_coef1                   :15;	//(14:0,RW,0x7FDE) //PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//(30:16,RW,0x1220) //PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230908 RW 0x7E02_7E64
	UINT32 r_ll_pcc_coef3                   :15;	//(14:0,RW,0x7E64) //PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//(30:16,RW,0x7E02) //PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23090C RW 0x11E6_7FB6
	UINT32 r_ll_pcc_coef5                   :15;	//(14:0,RW,0x7FB6) //PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//(30:16,RW,0x11E6) //PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230910 RW 0x7F10_7ED6
	UINT32 r_ll_pcc_coef7                   :15;	//(14:0,RW,0x7ED6) //PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//(30:16,RW,0x7F10) //PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230914 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//(30:16,RW,0x1A91) //PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230918 RW 0x0000_0000
	UINT32 reg_ll_ab_en                     :1;	//(0:0,RW,0x0) //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23091C RW 0x0048_000A
	UINT32 r_ll_ab_lut_x2                   :10;	//(9:0,RW,0xA) //
	UINT32 r_ll_ab_lut_x1                   :10;	//(19:10,RW,0x200) //
	UINT32 r_ll_ab_lut_x0                   :10;	//(29:20,RW,0x4) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230920 RW 0x00BF_FFFF
	UINT32 r_ll_ab_lut_x5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x3                   :10;	//(29:20,RW,0xB) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230924 RW 0x0000_2600
	UINT32 r_ll_ab_lut_y2                   :10;	//(9:0,RW,0x200) //
	UINT32 r_ll_ab_lut_y1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_y0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230928 RW 0x3FFF_FFFF
	UINT32 r_ll_ab_lut_y5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y3                   :10;	//(29:20,RW,0x3FF) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230970 RW 0x0000_0000
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
}PE_O26_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230974 RW 0x0438_0780
	UINT32 tpg_size_x                       :14;	//(13:0,RW,0x780) //tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//(28:16,RW,0x438) //tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230978 RW 0x0000_0000
	UINT32 tpg_mask_flag                    :16;	//(15:0,RW,0x0000) //
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23097C RW 0x0000_0000
	UINT32 tpg_in_out_sel                   :16;	//(15:0,RW,0x0) //in_out_sel
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230980 RW 0x0000_0000
	UINT32 tpg_color_r                      :10;	//(9:0,RW,0x00) //tpg_color_r
	UINT32 tpg_color_b                      :10;	//(19:10,RW,0x00) //tpg_color_b
	UINT32 tpg_color_g                      :10;	//(29:20,RW,0x00) //tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230984 RW 0x0000_8000
	UINT32 hif_tpg_address                  :8;	//(7:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O26_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230988 RW 0x0000_0000
	UINT32 hif_tpg_wdata_y                  :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230990 RW 0x0000_0000
	UINT32 reg_clut_65th_data               :11;	//(10:0,NA,0x000) //65th_data
	UINT32 resvd                            :21;
	};
}PE_O26_REG_H10_CLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230994 RW 0x0000_0000
	UINT32 clut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 clut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 clut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_CLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230998 RW 0x0000_0000
	UINT32 clut_data                        :11;	//(10:0,RW,0x00) //data for CLUT
	UINT32 resvd                            :21;
	};
}PE_O26_REG_H10_CLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC23099C RW 0x0000_0000
	UINT32 reg_plut_65th_data               :14;	//(13:0,NA,0x000) //65th_data
	UINT32 resvd                            :18;
	};
}PE_O26_REG_H10_PLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309A0 RW 0x0000_0000
	UINT32 plut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 plut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 plut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_PLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309A4 RW 0x0000_0000
	UINT32 plut_data                        :14;	//(13:0,RW,0x0) //data for PLUT
	UINT32 resvd                            :18;
	};
}PE_O26_REG_H10_PLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309A8 RW 0x0000_0000
	UINT32 reg_slut_65th_data               :10;	//(9:0,NA,0x000) //65th_data
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_SLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309AC RW 0x0000_0000
	UINT32 slut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 slut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 slut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_SLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309B0 RW 0x0000_0000
	UINT32 slut_data                        :10;	//(9:0,RW,0x00) //data for SLUT
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_SLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309B4 RW 0x0000_0000
	UINT32 reg_ilut_65th_data               :8;	//(7:0,NA,0x000) //65th_data
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_ILUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309B8 RW 0x0000_0000
	UINT32 ilut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 ilut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 ilut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_ILUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309BC RW 0x0000_0000
	UINT32 ilut_data                        :8;	//(7:0,RW,0x0) //data for ILUT
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_ILUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309C0 RW 0x0000_0000
	UINT32 reg_dlut_65th_data               :12;	//(11:0,NA,0x000) //65th_data
	UINT32 resvd0                           :4;
	UINT32 reg_dlut_threshold_0             :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309C4 RW 0x0000_0000
	UINT32 reg_dlut_threshold_1             :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_dlut_threshold_2             :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309C8 RW 0x0000_0000
	UINT32 reg_dlut_step_0                  :4;	//(3:0,RW,0x00) //
	UINT32 reg_dlut_step_1                  :4;	//(7:4,RW,0x00) //
	UINT32 reg_dlut_step_2                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_dlut_step_3                  :4;	//(15:12,RW,0x00) //
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309CC RW 0x0000_0000
	UINT32 dlut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 dlut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 dlut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_DLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309D0 RW 0x0000_0000
	UINT32 dlut_data                        :8;	//(7:0,RW,0x0) //data for DLUT
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_DLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309D4 RW 0x0000_0001
	UINT32 reg_technicolor_detour_en        :1;	//(0,NA,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_range_sel                    :1;	//(4,NA,0x000) //0':limited range, '1':full range
	UINT32 resvd1                           :27;
	};
}PE_O26_REG_H10_TC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309D8 RW 0x1E00_1F00
	UINT32 reg_alpha_a                      :13;	//(12:0,RW,0x1F00) //default value : 7936
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_b                      :13;	//(28:16,RW,0x1E00) //default value : 7680
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_TC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309DC RW 0x0000_0000
	UINT32 reg_oct_0                        :6;	//(5:0,RW,0x0) //unsigned 6 bit
	UINT32 resvd0                           :4;
	UINT32 reg_oct_1                        :8;	//(17:10,RW,0x0) //signed 8 bit
	UINT32 resvd1                           :2;
	UINT32 reg_oct_2                        :9;	//(28:20,RW,0x00) //signed 9 bit
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_TC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309E0 RW 0x0000_0000
	UINT32 reg_oct_3                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 reg_oct_4                        :10;	//(19:10,RW,0x00) //signed 10 bit
	UINT32 reg_oct_5                        :10;	//(29:20,RW,0x00) //signed 10 bit
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_TC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC2309E4 RW 0x0000_0000
	UINT32 reg_oct_6                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_TC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A00 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A14 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A18 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A20 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A24 RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A30 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A34 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A38 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A3C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A40 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A44 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A48 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A50 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A54 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A60 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A64 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A68 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A6C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A70 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A74 RW 0xFFFF_FFFF
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A78 RW 0xFFFF_FFFF
	UINT32 hif_llut2_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A80 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A84 RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A90 RW 0x0000_0000
	UINT32 gamma045_enable                  :1;	//(0:0,RW,0x00) //gamma 0.45(1/2.2) enable
	UINT32 resvd0                           :3;
	UINT32 gamma045_mode                    :1;	//(4:4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 gamma045_mux                     :1;	//(8:8,RW,0x00) //
	UINT32 resvd2                           :23;
	};
}PE_O26_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A94 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0:0,RW,0x00) //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//(2:2,RW,0x00) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3:3,RW,0x00) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,RW,0x00) //"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O26_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A98 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0:0,RW,0x00) //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//(2:2,RW,0x00) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3:3,RW,0x00) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,RW,0x00) //"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O26_REG_H10_DITHER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230A9C RW 0x0000_0000
	UINT32 hif_pcc32_ygain_shift            :1;	//(0:0,RW,0x0) //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AA0 RW 0x0000_0001
	UINT32 reg_csc3rd_en                    :1;	//(0:0,RW,0x01) //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AA4 RW 0x094A_00D0
	UINT32 r_csc3rd_coef1                   :15;	//(14:0,RW,0x00D0) //CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//(30:16,RW,0x094A) //CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AA8 RW 0x0399_7AF3
	UINT32 r_csc3rd_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//(30:16,RW,0x0399) //CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AAC RW 0x0702_7E0B
	UINT32 r_csc3rd_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AB0 RW 0x798F_7F70
	UINT32 r_csc3rd_coef7                   :15;	//(14:0,RW,0x7F70) //CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//(30:16,RW,0x798F) //CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AB4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AB8 RW 0x0000_0000
	UINT32 r_csc3rd_ofst1                   :11;	//(10:0,RW,0x000) //CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//(26:16,RW,0x000) //CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230ABC RW 0x0200_0040
	UINT32 r_csc3rd_ofst3                   :11;	//(10:0,RW,0x040) //CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//(26:16,RW,0x200) //CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AC0 RW 0x0200_0200
	UINT32 r_csc3rd_ofst5                   :11;	//(10:0,RW,0x0200) //CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//(26:16,RW,0x0200) //CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AD0 RW 0x0000_0000
	UINT32 r_slut0_x0                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AD4 RW 0x0000_0000
	UINT32 r_slut0_x1                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AD8 RW 0x0000_0000
	UINT32 r_slut0_x2                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230ADC RW 0x0000_0000
	UINT32 r_slut0_x3                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AE0 RW 0x0000_0000
	UINT32 r_slut0_x4                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AE4 RW 0x0000_0000
	UINT32 r_slut0_x5                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AE8 RW 0x0000_0000
	UINT32 r_slut0_x6                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AEC RW 0x0000_0000
	UINT32 r_slut0_x7                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AF0 RW 0x0000_0000
	UINT32 r_slut0_y0                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y1                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y2                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y3                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AF4 RW 0x0000_0000
	UINT32 r_slut0_y4                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y5                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y6                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y7                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AF8 RW 0x0000_0000
	UINT32 reg_tm_m2020_coef13              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd                            :1;
	UINT32 reg_tm_m2020_coef22              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 sat_gain_en                      :1;	//(31:31,RW,0x00) //TM0 Saturation Gain Enable
	};
}PE_O26_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230AFC RW 0x0000_0000
	UINT32 reg_tm_m2020_coef23              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm_m2020_coef32              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B20 RW 0x0000_0000
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
}PE_O26_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B24 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B28 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B2C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B30 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B34 RW 0xFFFF_1000
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B38 RW 0x0000_8000
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
}PE_O26_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B3C RW 0x0000_0000
	UINT32 hif_ygain_lut_wdata_y            :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B40 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B44 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_O26_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B48 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B4C RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B60 RW 0x0000_0080
	UINT32 lgain_lut_y0                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of LGAIN LUT point 0
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B64 RW 0x2492_0080
	UINT32 lgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of LGAIN LUT point 1
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B68 RW 0x4924_0080
	UINT32 lgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of LGAIN LUT point 2
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B6C RW 0x6DB6_0080
	UINT32 lgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of LGAIN LUT point 3
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B70 RW 0x9248_0080
	UINT32 lgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of LGAIN LUT point 4
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B74 RW 0xB6DA_0080
	UINT32 lgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of LGAIN LUT point 5
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B78 RW 0xDB6C_0080
	UINT32 lgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of LGAIN LUT point 6
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B7C RW 0xFFFF_0080
	UINT32 lgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of LGAIN LUT point 7
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B80 RW 0x0000_0080
	UINT32 sgain_lut_y0                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of SGAIN LUT point 0
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B84 RW 0x2492_0080
	UINT32 sgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of SGAIN LUT point 1
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B88 RW 0x4924_0080
	UINT32 sgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of SGAIN LUT point 2
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B8C RW 0x6DB6_0080
	UINT32 sgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of SGAIN LUT point 3
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B90 RW 0x9248_0080
	UINT32 sgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of SGAIN LUT point 4
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B94 RW 0xB6DA_0080
	UINT32 sgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of SGAIN LUT point 5
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B98 RW 0xDB6C_0080
	UINT32 sgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of SGAIN LUT point 6
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230B9C RW 0xFFFF_0080
	UINT32 sgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of SGAIN LUT point 7
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BA0 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BA4 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB -> Y CSC Coefficient 0
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BA8 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BAC RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BB0 RW 0x0000_0000
	UINT32 reg_csc4th_en                    :1;	//(0:0,RW,0x00) //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BB4 RW 0x094A_00D0
	UINT32 r_csc4th_coef1                   :15;	//(14:0,RW,0x00D0) //CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//(30:16,RW,0x094A) //CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BB8 RW 0x0399_7AF3
	UINT32 r_csc4th_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//(30:16,RW,0x0399) //CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BBC RW 0x0702_7E0B
	UINT32 r_csc4th_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BC0 RW 0x798F_7F70
	UINT32 r_csc4th_coef7                   :15;	//(14:0,RW,0x7F70) //CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//(30:16,RW,0x798F) //CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BC4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BC8 RW 0x0000_0000
	UINT32 r_csc4th_ofst1                   :11;	//(10:0,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//(26:16,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BCC RW 0x0000_0100
	UINT32 r_csc4th_ofst3                   :13;	//(12:0,RW,0x100) //CSC 4th Y'U'V' -> YUV Offset 3 (Default : 256)
	UINT32 resvd0                           :3;
	UINT32 r_csc4th_ofst2                   :11;	//(26:16,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230BD0 RW 0x0800_0800
	UINT32 r_csc4th_ofst5                   :13;	//(12:0,RW,0x0800) //CSC 4th Y'U'V' -> YUV Offset 5 (Default : 2048)
	UINT32 resvd0                           :3;
	UINT32 r_csc4th_ofst4                   :13;	//(28:16,RW,0x0800) //CSC 4th Y'U'V' -> YUV Offset 4 (Default : 2048)
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_CSC4_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C00 RW 0x0000_0000
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
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C14 RW 0xFFFF_1000
	UINT32 hif_cuva_tmlut_lut_wdata_y_33rd  :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_cuva_tmlut_lut_wdata_x_33rd  :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C18 RW 0x0000_8000
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
}PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C1C RW 0x0000_0000
	UINT32 hif_cuva_tmlut_lut_wdata_y       :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_cuva_tmlut_lut_wdata_x       :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C20 RW 0x0000_0000
	UINT32 r_cglut_x1                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x0                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C24 RW 0x0000_0000
	UINT32 r_cglut_x3                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x2                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C28 RW 0x0000_0000
	UINT32 r_cglut_x5                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x4                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C2C RW 0x0000_0000
	UINT32 r_cglut_x7                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x6                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C30 RW 0x0000_0000
	UINT32 r_cglut_y3                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y2                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y1                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y0                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C34 RW 0x0000_0000
	UINT32 r_cglut_y7                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y6                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y5                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y4                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C40 RW 0x0000_0000
	UINT32 r_cuva_eotf_mux                  :2;	//(1:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 r_cuva_sat_gain_bit              :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_cuva_sat_gain_sel              :1;	//(8:8,RW,0x0) //
	UINT32 resvd2                           :23;
	};
}PE_O26_REG_H10_CUVA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C50 RW 0xFF00_FF00
	UINT32 reg_gfd_h_th0_a                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_h_th1_a                  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_gfd_h_th0_b                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_gfd_h_th1_b                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_REG_H10_FIM_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C54 RW 0x0000_0000
	UINT32 reg_gfd_s_th                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_v_th                     :8;	//(15:8,RW,0x00) //
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//(31:30,RW,0x0) //0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_O26_REG_H10_FIM_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C58 RO 0x0000_0000
	UINT32 reg_gfd_count_a01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Top
	};
}PE_O26_REG_H10_FIM_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C5C RO 0x0000_0000
	UINT32 reg_gfd_count_a11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_O26_REG_H10_FIM_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C60 RO 0x0000_0000
	UINT32 reg_gfd_count_b01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Top
	};
}PE_O26_REG_H10_FIM_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C64 RO 0x0000_0000
	UINT32 reg_gfd_count_b11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_O26_REG_H10_FIM_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C68 RW 0x0000_0000
	UINT32 reg_pcg_off                      :1;	//(0:0,NA,0x0) //
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_FIM_PCG_OFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C70 RW 0x00EC_1200
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
}PE_O26_REG_H10_FIM_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C74 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C78 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C7C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C80 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C84 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C88 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C8C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C90 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C94 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C98 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230C9C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CA0 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O26_REG_H10_FIM_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CA4 RW 0x0010_2000
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
}PE_O26_REG_H10_FIM_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CA8 RW 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RW,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CAC RW 0x0437_077F
	UINT32 x1                               :12;	//(11:0,RW,0x077F) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RW,0x0437) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CB0 RW 0x0000_8000
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
}PE_O26_REG_H10_FIM__HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CB4 RW 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RW,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O26_REG_H10_FIM__HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CC0 RO 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RO,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RO,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CC4 RO 0x01DF_02CF
	UINT32 x1                               :12;	//(11:0,RO,0x02CF) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RO,0x01DF) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CC8 RO 0x0000_0068
	UINT32 y_g_s_apl                        :10;	//(9:0,RO,0x068) //data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//(19:10,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//(29:20,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_FIM_APL_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CF0 RW 0x0000_0000
	UINT32 win0_enable                      :3;	//(2:0,RW,0x0) //window 0 enable
	UINT32 resvd0                           :1;
	UINT32 win1_enable                      :1;	//(4:4,RW,0x0) //window 1 enable
	UINT32 resvd1                           :3;
	UINT32 win2_enable                      :1;	//(8:8,RW,0x0) //window 2 enable
	UINT32 resvd2                           :3;
	UINT32 win3_enable                      :1;	//(12:12,RW,0x0) //window 3 enable
	UINT32 resvd3                           :3;
	UINT32 win4_enable                      :1;	//(16:16,RW,0x0) //window 4 enable
	UINT32 resvd4                           :3;
	UINT32 win5_enable                      :1;	//(20:20,RW,0x0) //window 5 enable
	UINT32 resvd5                           :11;
	};
}PE_O26_REG_H10_HIST_EN_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CF4 RW 0x0000_0000
	UINT32 w0_bin_mode                      :3;	//(2:0,RW,0x0) //128 bin mode activation of window 0 (default 32 bin)
	UINT32 resvd0                           :1;
	UINT32 w1_bin_mode                      :1;	//(4:4,RW,0x0) //128 bin mode activation of window 1 (default 32 bin)
	UINT32 resvd1                           :3;
	UINT32 w2_bin_mode                      :1;	//(8:8,RW,0x0) //128 bin mode activation of window 2 (default 32 bin)
	UINT32 resvd2                           :3;
	UINT32 win_only                         :1;	//(12:12,RW,0x0) //1: window mode enable(histogram of full screen)
	UINT32 resvd3                           :19;
	};
}PE_O26_REG_H10_HIST_MODE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CF8 RW 0x0000_0000
	UINT32 resvd0                           :4;
	UINT32 hist_win0_clear                  :1;	//(4:4,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd1                           :3;
	UINT32 hist_win1_clear                  :1;	//(8:8,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd2                           :3;
	UINT32 hist_win2_clear                  :1;	//(12:12,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd3                           :3;
	UINT32 hist_win3_clear                  :1;	//(16:16,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd4                           :3;
	UINT32 hist_win4_clear                  :1;	//(20:20,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd5                           :3;
	UINT32 hist_win5_clear                  :1;	//(24:24,RW,0x0) //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd6                           :7;
	};
}PE_O26_REG_H10_HIST_CLEAR_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230CFC RW 0x0000_0000
	UINT32 win0_acquire                     :1;	//(0:0,RW,0x0) //1: update window 0 size register
	UINT32 resvd0                           :3;
	UINT32 win1_acquire                     :1;	//(4:4,RW,0x0) //1: update window 1 size register
	UINT32 resvd1                           :3;
	UINT32 win2_acquire                     :1;	//(8:8,RW,0x0) //1: update window 2 size register
	UINT32 resvd2                           :3;
	UINT32 win3_acquire                     :1;	//(12:12,RW,0x0) //1: update window 3 size register
	UINT32 resvd3                           :3;
	UINT32 win4_acquire                     :1;	//(16:16,RW,0x0) //1: update window 4 size register
	UINT32 resvd4                           :3;
	UINT32 win5_acquire                     :1;	//(20:20,RW,0x0) //1: update window 5 size register
	UINT32 resvd5                           :11;
	};
}PE_O26_REG_H10_HIST_CTRL_ACQ_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D00 RW 0x0000_0000
	UINT32 hist_hold_frame                  :1;	//(0:0,RW,0x0) //histogram update trigger of all window	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd0                           :3;
	UINT32 hist_hold_win0                   :1;	//(4:4,RW,0x0) //histogram update trigger of window 0	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd1                           :3;
	UINT32 hist_hold_win1                   :1;	//(8:8,RW,0x0) //histogram update trigger of window 1	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd2                           :3;
	UINT32 hist_hold_win2                   :1;	//(12:12,RW,0x0) //histogram update trigger of window 2	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd3                           :3;
	UINT32 hist_hold_win3                   :1;	//(16:16,RW,0x0) //histogram update trigger of window 3	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd4                           :3;
	UINT32 hist_hold_win4                   :1;	//(20:20,RW,0x0) //histogram update trigger of window 4	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd5                           :3;
	UINT32 hist_hold_win5                   :1;	//(24:24,RW,0x0) //histogram update trigger of window 5	1'b0 : update 	1'b1 : hold(don't update)
	UINT32 resvd6                           :7;
	};
}PE_O26_REG_H10_HIST_HOLD_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D20 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D24 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D28 RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D2C RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D30 RW 0x0000_0000
	UINT32 win_w2_x0                        :16;	//(15:0,RW,0x0) //win_w2_x0
	UINT32 win_w2_y0                        :16;	//(31:16,RW,0x0) //win_w2_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D34 RW 0x086F_0EFF
	UINT32 win_w2_x1                        :16;	//(15:0,RW,0xEFF) //win_w2_x1
	UINT32 win_w2_y1                        :16;	//(31:16,RW,0x86F) //win_w2_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D38 RW 0x0000_0000
	UINT32 win_w3_x0                        :16;	//(15:0,RW,0x0) //win_w3_x0
	UINT32 win_w3_y0                        :16;	//(31:16,RW,0x0) //win_w3_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D3C RW 0x086F_0EFF
	UINT32 win_w3_x1                        :16;	//(15:0,RW,0xEFF) //win_w3_x1
	UINT32 win_w3_y1                        :16;	//(31:16,RW,0x86F) //win_w3_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D40 RW 0x0000_0000
	UINT32 win_w4_x0                        :16;	//(15:0,RW,0x0) //win_w4_x0
	UINT32 win_w4_y0                        :16;	//(31:16,RW,0x0) //win_w4_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D44 RW 0x086F_0EFF
	UINT32 win_w4_x1                        :16;	//(15:0,RW,0xEFF) //win_w4_x1
	UINT32 win_w4_y1                        :16;	//(31:16,RW,0x86F) //win_w4_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D48 RW 0x0000_0000
	UINT32 win_w5_x0                        :16;	//(15:0,RW,0x0) //win_w5_x0
	UINT32 win_w5_y0                        :16;	//(31:16,RW,0x0) //win_w5_y0
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D4C RW 0x086F_0EFF
	UINT32 win_w5_x1                        :16;	//(15:0,RW,0xEFF) //win_w5_x1
	UINT32 win_w5_y1                        :16;	//(31:16,RW,0x86F) //win_w5_y1
	};
}PE_O26_REG_H10_HIST_CTRL_WSIZE_51_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D50 RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D54 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W0_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D58 RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W0_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D5C RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D60 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W1_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D64 RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W1_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D68 RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D6C RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W2_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D70 RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W2_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D74 RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W3_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D78 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W3_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D7C RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W3_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D80 RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W4_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D84 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W4_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D88 RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W4_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D8C RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_W5_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D90 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,[22:0]hif_histogram_bin_read,) //
	};
}PE_O26_REG_H10_HIST_W5_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D94 RO 0x0000_0000
	UINT32 hist_min                         :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_max                         :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_W5_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230D9C RW 0x0000_0000
	UINT32 reg_dither_io_sel                :1;	//(0:0,RW,0x0) //0: Input-TPG 12bit, Output-CSC 12bit input	1: Input-CSC 4th 10.2bit, Output-Final HDR10+ output
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_SR_DITHER_MUX_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DA0 RW 0x0000_0000
	UINT32 reg_dither_detour                :1;	//(0,RW,0x0) //1: dither top detour (input = output)
	UINT32 resvd0                           :7;
	UINT32 reg_col_fmt                      :1;	//(8,RW,0x0) //input color format 	0: yuv, 1:rgb
	UINT32 resvd1                           :23;
	};
}PE_O26_REG_H10_SR_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DA4 RW 0x0F00_0870
	UINT32 reg_dither_height                :16;	//(15:0,NA,0x870) //dither input image height
	UINT32 reg_dither_width                 :16;	//(31:16,RW,0xF00) //dither input image width
	};
}PE_O26_REG_H10_SR_DITHER_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DA8 RW 0x00a0_9467
	UINT32 reg_err_diff_ker_dl              :5;	//(4:0,RW,7) //err_diff_ker input image dl
	UINT32 reg_err_diff_ker_ur              :5;	//(9:5,RW,3) //err_diff_ker input image ur
	UINT32 reg_err_diff_ker_um              :5;	//(14:10,RW,5) //err_diff_ker input image um
	UINT32 reg_err_diff_ker_ul              :5;	//(19:15,RW,1) //err_diff_ker input image ul
	UINT32 reg_err_th                       :4;	//(23:20,RW,10) //error diffusion threshold
	UINT32 reg_err_diff_debug_enable        :1;	//(24,RW,0x0) //error diffusion debug mode
	UINT32 resvd0                           :3;
	UINT32 reg_chroma_err_diable            :1;	//(28:28,RW,0) //chroma error diable 	1 : chroma 성분 무시
	UINT32 resvd1                           :2;
	UINT32 reg_err_diff_en                  :1;	//(31,RW,0) //err_diff input image en	0 : core bypass	1 : output = error diffusion result
	};
}PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DAC RW 0x0801_0040
	UINT32 reg_err_diff_out_y_wei_10b       :9;	//(8:0,RW,0x40) //
	UINT32 resvd0                           :1;
	UINT32 reg_err_diff_out_y_wei_9b        :9;	//(18:10,RW,0x40) //
	UINT32 resvd1                           :1;
	UINT32 reg_err_diff_out_y_wei_8b        :9;	//(28:20,RW,0x80) //
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DB0 RW 0x0801_0040
	UINT32 reg_err_diff_out_c_wei_10b       :9;	//(8:0,RW,0x40) //
	UINT32 resvd0                           :1;
	UINT32 reg_err_diff_out_c_wei_9b        :9;	//(18:10,RW,0x40) //
	UINT32 resvd1                           :1;
	UINT32 reg_err_diff_out_c_wei_8b        :9;	//(28:20,RW,0x80) //
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DB4 RW 0xf880_0880
	UINT32 resvd0                           :4;
	UINT32 reg_err_diff_debug_bg_cr         :4;	//(7:4,RW,8) //
	UINT32 reg_err_diff_debug_bg_cb         :4;	//(11:8,RW,8) //
	UINT32 reg_err_diff_debug_bg_yg         :4;	//(15:12,RW,0) //
	UINT32 resvd1                           :4;
	UINT32 reg_err_diff_debug_cr            :4;	//(23:20,RW,8) //
	UINT32 reg_err_diff_debug_cb            :4;	//(27:24,RW,8) //
	UINT32 reg_err_diff_debug_yg            :4;	//(31:28,RW,15) //
	};
}PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DB8 RW 0x0400_0000
	UINT32 resvd0                           :24;
	UINT32 reg_1st_out_rd_bit               :4;	//(27:24,RW,4) //1st_out_rd input image bit
	UINT32 resvd1                           :3;
	UINT32 reg_1st_out_rd_on                :1;	//(31,RW,0) //1st_out_rd input image on	0 : core bypass	1 : output = random diffusion result
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DBC RW 0x0000_0000
	UINT32 reg_1st_out_rd_min_pel_cb        :13;	//(12:0,RW,0x0) //1st_out_rd_min_pel input image cb
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_min_pel_yy        :13;	//(28:16,RW,0x0) //1st_out_rd_min_pel input image yy
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DC0 RW 0x0000_0fff
	UINT32 reg_1st_out_rd_max_pel_yy        :13;	//(12:0,RW,4095) //1st_out_rd_max_pel input image yy
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_min_pel_cr        :13;	//(28:16,RW,0x0) //1st_out_rd_min_pel input image cr
	UINT32 resvd1                           :2;
	UINT32 reg_init_rst_off                 :1;	//(31,RW,0x0) //1 : pic_init reset(initial register) off_x000D_	0: normal mode
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DC4 RW 0x0fff_0fff
	UINT32 reg_1st_out_rd_max_pel_cr        :13;	//(12:0,RW,4095) //1st_out_rd_max_pel input image cr
	UINT32 resvd0                           :3;
	UINT32 reg_1st_out_rd_max_pel_cb        :13;	//(28:16,RW,4095) //1st_out_rd_max_pel input image cb
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DC8 RW 0x1357_9753
	UINT32 reg_1st_out_rd_init_yy           :32;	//(31:0,RW,324507475) //1st_out_rd_init input image yy
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DCC RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cb           :32;	//(31:0,RW,610797668) //1st_out_rd_init input image cb
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DD0 RW 0x2468_0864
	UINT32 reg_1st_out_rd_init_cr           :32;	//(31:0,RW,610797668) //1st_out_rd_init input image cr
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DD4 RW 0x1200_0030
	UINT32 resvd0                           :4;
	UINT32 reg_1st_rd_roi_cut_out           :2;	//(5:4,NA,0x3) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 reg_1st_rd_roi_cut_in            :2;	//(7:6,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd1                           :8;
	UINT32 reg_rd_roi_en                    :1;	//(16,NA,0x0) //0: rd_roi off, 1: rd_roi on
	UINT32 resvd2                           :3;
	UINT32 reg_2nd_rd_luma_cut              :2;	//(21:20,NA,0x0) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd3                           :2;
	UINT32 reg_1st_rd_luma_cut              :2;	//(25:24,NA,2) //0: x1, 1: /2, 2: /4, 3: /8
	UINT32 resvd4                           :2;
	UINT32 reg_1st_rd_luma_en               :1;	//(28,NA,1) //0: 1st_rd_luma off, 1: 1st_rd_luma on
	UINT32 resvd5                           :3;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DD8 RW 0x005b_01b0
	UINT32 reg_rd_roi_x1                    :14;	//(13:0,NA,0x1B0) //rd_roi input image x1
	UINT32 resvd0                           :2;
	UINT32 reg_rd_roi_x0                    :14;	//(29:16,NA,0x5B) //rd_roi input image x0
	UINT32 resvd1                           :2;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DDC RW 0x006a_01b0
	UINT32 reg_rd_roi_y1                    :14;	//(13:0,NA,0x1B0) //rd_roi input image y1
	UINT32 resvd0                           :2;
	UINT32 reg_rd_roi_y0                    :14;	//(29:16,NA,0x6A) //rd_roi input image y0
	UINT32 resvd1                           :2;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DE0 RW 0x0000_2814
	UINT32 reg_1st_rd_luma_x1               :10;	//(9:0,NA,0x14) //1st_rd_luma input image x1
	UINT32 reg_1st_rd_luma_x0               :10;	//(19:10,NA,0xA) //1st_rd_luma input image x0
	UINT32 resvd                            :12;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DE4 RW 0x0000_a032
	UINT32 reg_1st_rd_luma_x3               :10;	//(9:0,NA,0x32) //1st_rd_luma input image x3
	UINT32 reg_1st_rd_luma_x2               :10;	//(19:10,NA,0x28) //1st_rd_luma input image x2
	UINT32 resvd                            :12;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DE8 RW 0x0003_c046
	UINT32 reg_1st_rd_luma_x5               :10;	//(9:0,NA,0x46) //1st_rd_luma input image x5
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x4               :10;	//(21:12,NA,0x3C) //1st_rd_luma input image x4
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DEC RW 0x0006_40c8
	UINT32 reg_1st_rd_luma_x7               :10;	//(9:0,NA,0xC8) //1st_rd_luma input image x7
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_x6               :10;	//(21:12,NA,0x64) //1st_rd_luma input image x6
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DF0 RW 0x0000_0000
	UINT32 reg_1st_rd_luma_y1               :10;	//(9:0,NA,0x0) //1st_rd_luma input image y1
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y0               :10;	//(21:12,NA,0x0) //1st_rd_luma input image y0
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DF4 RW 0x0000_400a
	UINT32 reg_1st_rd_luma_y3               :10;	//(9:0,NA,0xA) //1st_rd_luma input image y3
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y2               :10;	//(21:12,NA,0x4) //1st_rd_luma input image y2
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DF8 RW 0x0003_2064
	UINT32 reg_1st_rd_luma_y5               :10;	//(9:0,NA,0x64) //1st_rd_luma input image y5
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y4               :10;	//(21:12,NA,0x32) //1st_rd_luma input image y4
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCC230DFC RW 0x000c_83ff
	UINT32 reg_1st_rd_luma_y7               :10;	//(9:0,NA,0x3FF) //1st_rd_luma input image y7
	UINT32 resvd0                           :2;
	UINT32 reg_1st_rd_luma_y6               :10;	//(21:12,NA,0xC8) //1st_rd_luma input image y6
	UINT32 resvd1                           :10;
	};
}PE_O26_REG_H10_SR_DITHER_RND_DIFFU_17_T;

typedef struct {
	PE_O26_REG_H10_TOP_CTRL_00_T                       hdr_top_ctrl_00;	//0xCC230800
	PE_O26_REG_H10_TOP_CTRL_01_T                       hdr_top_ctrl_01;	//0xCC230804
	PE_O26_REG_H10_TOP_CTRL_02_T                       hdr_top_ctrl_02;	//0xCC230808
	PE_O26_REG_H10_TOP_CTRL_03_T                       hdr_top_ctrl_03;	//0xCC23080C
	PE_O26_REG_H10_TOP_CTRL_04_T                       hdr_top_ctrl_04;	//0xCC230810
	PE_O26_REG_H10_TOP_CTRL_05_T                       hdr_top_ctrl_05;	//0xCC230814
	PE_O26_REG_H10_TOP_CTRL_06_T                       hdr_top_ctrl_06;	//0xCC230818
	PE_O26_REG_H10_TOP_CTRL_07_T                       hdr_top_ctrl_07;	//0xCC23081C
	UINT32                                                   reserved0;	//0xCC230820
	UINT32                                                   reserved1;	//0xCC230824
	UINT32                                                   reserved2;	//0xCC230828
	UINT32                                                   reserved3;	//0xCC23082C
	UINT32                                                   reserved4;	//0xCC230830
	UINT32                                                   reserved5;	//0xCC230834
	UINT32                                                   reserved6;	//0xCC230838
	UINT32                                                   reserved7;	//0xCC23083C
	UINT32                                                   reserved8;	//0xCC230840
	UINT32                                                   reserved9;	//0xCC230844
	UINT32                                                  reserved10;	//0xCC230848
	UINT32                                                  reserved11;	//0xCC23084C
	PE_O26_REG_H10_CSC1_CTRL_00_T                     hdr_csc1_ctrl_00;	//0xCC230850
	PE_O26_REG_H10_CSC1_CTRL_01_T                     hdr_csc1_ctrl_01;	//0xCC230854
	PE_O26_REG_H10_CSC1_CTRL_02_T                     hdr_csc1_ctrl_02;	//0xCC230858
	PE_O26_REG_H10_CSC1_CTRL_03_T                     hdr_csc1_ctrl_03;	//0xCC23085C
	PE_O26_REG_H10_CSC1_CTRL_04_T                     hdr_csc1_ctrl_04;	//0xCC230860
	PE_O26_REG_H10_CSC1_CTRL_05_T                     hdr_csc1_ctrl_05;	//0xCC230864
	PE_O26_REG_H10_CSC1_CTRL_06_T                     hdr_csc1_ctrl_06;	//0xCC230868
	PE_O26_REG_H10_CSC1_CTRL_07_T                     hdr_csc1_ctrl_07;	//0xCC23086C
	PE_O26_REG_H10_CSC1_CTRL_08_T                     hdr_csc1_ctrl_08;	//0xCC230870
	PE_O26_REG_H10_CSC1_CTRL_09_T                     hdr_csc1_ctrl_09;	//0xCC230874
	PE_O26_REG_H10_CSC1_ERR_CNT_T                     hdr_csc1_err_cnt;	//0xCC230878
	UINT32                                                  reserved12;	//0xCC23087C
	PE_O26_REG_H10_PXL_RD_CTRL0_T                     hdr_pxl_rd_ctrl0;	//0xCC230880
	PE_O26_REG_H10_PXL_RD_CTRL1_T                     hdr_pxl_rd_ctrl1;	//0xCC230884
	PE_O26_REG_H10_PXL_RD_DATA0_T                     hdr_pxl_rd_data0;	//0xCC230888
	PE_O26_REG_H10_PXL_RD_DATA1_T                     hdr_pxl_rd_data1;	//0xCC23088C
	PE_O26_REG_H10_EOTF_IA_CTRL_T                     hdr_eotf_ia_ctrl;	//0xCC230890
	PE_O26_REG_H10_EOTF_IA_DATA_T                     hdr_eotf_ia_data;	//0xCC230894
	PE_O26_REG_H10_OETF_IA_CTRL_T                     hdr_oetf_ia_ctrl;	//0xCC230898
	PE_O26_REG_H10_OETF_IA_DATA_T                     hdr_oetf_ia_data;	//0xCC23089C
	PE_O26_REG_H10_PCC_CTRL_00_T                       hdr_pcc_ctrl_00;	//0xCC2308A0
	PE_O26_REG_H10_PCC_CTRL_01_T                       hdr_pcc_ctrl_01;	//0xCC2308A4
	PE_O26_REG_H10_PCC_CTRL_02_T                       hdr_pcc_ctrl_02;	//0xCC2308A8
	PE_O26_REG_H10_PCC_CTRL_03_T                       hdr_pcc_ctrl_03;	//0xCC2308AC
	PE_O26_REG_H10_PCC_CTRL_04_T                       hdr_pcc_ctrl_04;	//0xCC2308B0
	PE_O26_REG_H10_PCC_CTRL_05_T                       hdr_pcc_ctrl_05;	//0xCC2308B4
	UINT32                                                  reserved13;	//0xCC2308B8
	UINT32                                                  reserved14;	//0xCC2308BC
	UINT32                                                  reserved15;	//0xCC2308C0
	UINT32                                                  reserved16;	//0xCC2308C4
	UINT32                                                  reserved17;	//0xCC2308C8
	UINT32                                                  reserved18;	//0xCC2308CC
	PE_O26_REG_H10_HUE_SAT_CTRL_T                     hdr_hue_sat_ctrl;	//0xCC2308D0
	PE_O26_REG_H10_HUE_SAT_ALPHA_CTRL_T         hdr_hue_sat_alpha_ctrl;	//0xCC2308D4
	UINT32                                                  reserved19;	//0xCC2308D8
	UINT32                                                  reserved20;	//0xCC2308DC
	PE_O26_REG_H10_TCM_PREP_00_T                       hdr_tcm_prep_00;	//0xCC2308E0
	PE_O26_REG_H10_TCM_PREP_01_T                       hdr_tcm_prep_01;	//0xCC2308E4
	PE_O26_REG_H10_LL_LUT_IA_CTRL_T                 hdr_ll_lut_ia_ctrl;	//0xCC2308E8
	PE_O26_REG_H10_LL_LUT_IA_DATA_T                 hdr_ll_lut_ia_data;	//0xCC2308EC
	PE_O26_REG_H10_LL_HUE_CTRL_00_T                 hdr_ll_hue_ctrl_00;	//0xCC2308F0
	PE_O26_REG_H10_LL_HUE_CTRL_01_T                 hdr_ll_hue_ctrl_01;	//0xCC2308F4
	PE_O26_REG_H10_LL_HUE_CTRL_02_T                 hdr_ll_hue_ctrl_02;	//0xCC2308F8
	UINT32                                                  reserved21;	//0xCC2308FC
	PE_O26_REG_H10_LLPCC_CTRL_00_T                   hdr_llpcc_ctrl_00;	//0xCC230900
	PE_O26_REG_H10_LLPCC_CTRL_01_T                   hdr_llpcc_ctrl_01;	//0xCC230904
	PE_O26_REG_H10_LLPCC_CTRL_02_T                   hdr_llpcc_ctrl_02;	//0xCC230908
	PE_O26_REG_H10_LLPCC_CTRL_03_T                   hdr_llpcc_ctrl_03;	//0xCC23090C
	PE_O26_REG_H10_LLPCC_CTRL_04_T                   hdr_llpcc_ctrl_04;	//0xCC230910
	PE_O26_REG_H10_LLPCC_CTRL_05_T                   hdr_llpcc_ctrl_05;	//0xCC230914
	PE_O26_REG_H10_LL_AB_CTRL_00_T                   hdr_ll_ab_ctrl_00;	//0xCC230918
	PE_O26_REG_H10_LL_AB_CTRL_01_T                   hdr_ll_ab_ctrl_01;	//0xCC23091C
	PE_O26_REG_H10_LL_AB_CTRL_02_T                   hdr_ll_ab_ctrl_02;	//0xCC230920
	PE_O26_REG_H10_LL_AB_CTRL_03_T                   hdr_ll_ab_ctrl_03;	//0xCC230924
	PE_O26_REG_H10_LL_AB_CTRL_04_T                   hdr_ll_ab_ctrl_04;	//0xCC230928
	UINT32                                                  reserved22;	//0xCC23092C
	UINT32                                                  reserved23;	//0xCC230930
	UINT32                                                  reserved24;	//0xCC230934
	UINT32                                                  reserved25;	//0xCC230938
	UINT32                                                  reserved26;	//0xCC23093C
	UINT32                                                  reserved27;	//0xCC230940
	UINT32                                                  reserved28;	//0xCC230944
	UINT32                                                  reserved29;	//0xCC230948
	UINT32                                                  reserved30;	//0xCC23094C
	UINT32                                                  reserved31;	//0xCC230950
	UINT32                                                  reserved32;	//0xCC230954
	UINT32                                                  reserved33;	//0xCC230958
	UINT32                                                  reserved34;	//0xCC23095C
	UINT32                                                  reserved35;	//0xCC230960
	UINT32                                                  reserved36;	//0xCC230964
	UINT32                                                  reserved37;	//0xCC230968
	UINT32                                                  reserved38;	//0xCC23096C
	PE_O26_REG_H10_TPG_CTRL_00_T                       hdr_tpg_ctrl_00;	//0xCC230970
	PE_O26_REG_H10_TPG_CTRL_01_T                       hdr_tpg_ctrl_01;	//0xCC230974
	PE_O26_REG_H10_TPG_CTRL_02_T                       hdr_tpg_ctrl_02;	//0xCC230978
	PE_O26_REG_H10_TPG_CTRL_03_T                       hdr_tpg_ctrl_03;	//0xCC23097C
	PE_O26_REG_H10_TPG_CTRL_04_T                       hdr_tpg_ctrl_04;	//0xCC230980
	PE_O26_REG_H10_TPG_IA_CTRL_T                       hdr_tpg_ia_ctrl;	//0xCC230984
	PE_O26_REG_H10_TPG_IA_DATA_T                       hdr_tpg_ia_data;	//0xCC230988
	UINT32                                                  reserved39;	//0xCC23098C
	PE_O26_REG_H10_CLUT_CTRL_00_T                     hdr_clut_ctrl_00;	//0xCC230990
	PE_O26_REG_H10_CLUT_IA_CTRL_T                     hdr_clut_ia_ctrl;	//0xCC230994
	PE_O26_REG_H10_CLUT_IA_DATA_T                     hdr_clut_ia_data;	//0xCC230998
	PE_O26_REG_H10_PLUT_CTRL_00_T                     hdr_plut_ctrl_00;	//0xCC23099C
	PE_O26_REG_H10_PLUT_IA_CTRL_T                     hdr_plut_ia_ctrl;	//0xCC2309A0
	PE_O26_REG_H10_PLUT_IA_DATA_T                     hdr_plut_ia_data;	//0xCC2309A4
	PE_O26_REG_H10_SLUT_CTRL_00_T                     hdr_slut_ctrl_00;	//0xCC2309A8
	PE_O26_REG_H10_SLUT_IA_CTRL_T                     hdr_slut_ia_ctrl;	//0xCC2309AC
	PE_O26_REG_H10_SLUT_IA_DATA_T                     hdr_slut_ia_data;	//0xCC2309B0
	PE_O26_REG_H10_ILUT_CTRL_00_T                     hdr_ilut_ctrl_00;	//0xCC2309B4
	PE_O26_REG_H10_ILUT_IA_CTRL_T                     hdr_ilut_ia_ctrl;	//0xCC2309B8
	PE_O26_REG_H10_ILUT_IA_DATA_T                     hdr_ilut_ia_data;	//0xCC2309BC
	PE_O26_REG_H10_DLUT_CTRL_00_T                     hdr_dlut_ctrl_00;	//0xCC2309C0
	PE_O26_REG_H10_DLUT_CTRL_01_T                     hdr_dlut_ctrl_01;	//0xCC2309C4
	PE_O26_REG_H10_DLUT_CTRL_02_T                     hdr_dlut_ctrl_02;	//0xCC2309C8
	PE_O26_REG_H10_DLUT_IA_CTRL_T                     hdr_dlut_ia_ctrl;	//0xCC2309CC
	PE_O26_REG_H10_DLUT_IA_DATA_T                     hdr_dlut_ia_data;	//0xCC2309D0
	PE_O26_REG_H10_TC_CTRL_00_T                         hdr_tc_ctrl_00;	//0xCC2309D4
	PE_O26_REG_H10_TC_CTRL_01_T                         hdr_tc_ctrl_01;	//0xCC2309D8
	PE_O26_REG_H10_TC_CTRL_02_T                         hdr_tc_ctrl_02;	//0xCC2309DC
	PE_O26_REG_H10_TC_CTRL_03_T                         hdr_tc_ctrl_03;	//0xCC2309E0
	PE_O26_REG_H10_TC_CTRL_04_T                         hdr_tc_ctrl_04;	//0xCC2309E4
	UINT32                                                  reserved40;	//0xCC2309E8
	UINT32                                                  reserved41;	//0xCC2309EC
	UINT32                                                  reserved42;	//0xCC2309F0
	UINT32                                                  reserved43;	//0xCC2309F4
	UINT32                                                  reserved44;	//0xCC2309F8
	UINT32                                                  reserved45;	//0xCC2309FC
	PE_O26_REG_H10_LLUT0_CTRL_00_T                   hdr_llut0_ctrl_00;	//0xCC230A00
	PE_O26_REG_H10_LLUT0_CTRL_01_T                   hdr_llut0_ctrl_01;	//0xCC230A04
	PE_O26_REG_H10_LLUT0_CTRL_02_T                   hdr_llut0_ctrl_02;	//0xCC230A08
	PE_O26_REG_H10_LLUT0_CTRL_03_T                   hdr_llut0_ctrl_03;	//0xCC230A0C
	PE_O26_REG_H10_LLUT0_CTRL_04_T                   hdr_llut0_ctrl_04;	//0xCC230A10
	PE_O26_REG_H10_LLUT0_CTRL_05_T                   hdr_llut0_ctrl_05;	//0xCC230A14
	PE_O26_REG_H10_LLUT0_CTRL_06_T                   hdr_llut0_ctrl_06;	//0xCC230A18
	UINT32                                                  reserved46;	//0xCC230A1C
	PE_O26_REG_H10_LLUT0_IA_CTRL_T                   hdr_llut0_ia_ctrl;	//0xCC230A20
	PE_O26_REG_H10_LLUT0_IA_DATA_T                   hdr_llut0_ia_data;	//0xCC230A24
	UINT32                                                  reserved47;	//0xCC230A28
	UINT32                                                  reserved48;	//0xCC230A2C
	PE_O26_REG_H10_LLUT1_CTRL_00_T                   hdr_llut1_ctrl_00;	//0xCC230A30
	PE_O26_REG_H10_LLUT1_CTRL_01_T                   hdr_llut1_ctrl_01;	//0xCC230A34
	PE_O26_REG_H10_LLUT1_CTRL_02_T                   hdr_llut1_ctrl_02;	//0xCC230A38
	PE_O26_REG_H10_LLUT1_CTRL_03_T                   hdr_llut1_ctrl_03;	//0xCC230A3C
	PE_O26_REG_H10_LLUT1_CTRL_04_T                   hdr_llut1_ctrl_04;	//0xCC230A40
	PE_O26_REG_H10_LLUT1_CTRL_05_T                   hdr_llut1_ctrl_05;	//0xCC230A44
	PE_O26_REG_H10_LLUT1_CTRL_06_T                   hdr_llut1_ctrl_06;	//0xCC230A48
	UINT32                                                  reserved49;	//0xCC230A4C
	PE_O26_REG_H10_LLUT1_IA_CTRL_T                   hdr_llut1_ia_ctrl;	//0xCC230A50
	PE_O26_REG_H10_LLUT1_IA_DATA_T                   hdr_llut1_ia_data;	//0xCC230A54
	UINT32                                                  reserved50;	//0xCC230A58
	UINT32                                                  reserved51;	//0xCC230A5C
	PE_O26_REG_H10_LLUT2_CTRL_00_T                   hdr_llut2_ctrl_00;	//0xCC230A60
	PE_O26_REG_H10_LLUT2_CTRL_01_T                   hdr_llut2_ctrl_01;	//0xCC230A64
	PE_O26_REG_H10_LLUT2_CTRL_02_T                   hdr_llut2_ctrl_02;	//0xCC230A68
	PE_O26_REG_H10_LLUT2_CTRL_03_T                   hdr_llut2_ctrl_03;	//0xCC230A6C
	PE_O26_REG_H10_LLUT2_CTRL_04_T                   hdr_llut2_ctrl_04;	//0xCC230A70
	PE_O26_REG_H10_LLUT2_CTRL_05_T                   hdr_llut2_ctrl_05;	//0xCC230A74
	PE_O26_REG_H10_LLUT2_CTRL_06_T                   hdr_llut2_ctrl_06;	//0xCC230A78
	UINT32                                                  reserved52;	//0xCC230A7C
	PE_O26_REG_H10_LLUT2_IA_CTRL_T                   hdr_llut2_ia_ctrl;	//0xCC230A80
	PE_O26_REG_H10_LLUT2_IA_DATA_T                   hdr_llut2_ia_data;	//0xCC230A84
	UINT32                                                  reserved53;	//0xCC230A88
	UINT32                                                  reserved54;	//0xCC230A8C
	PE_O26_REG_H10_GAMMA045_CTRL_00_T             hdr_gamma045_ctrl_00;	//0xCC230A90
	PE_O26_REG_H10_DITHER_CTRL_00_T                 hdr_dither_ctrl_00;	//0xCC230A94
	PE_O26_REG_H10_DITHER_CTRL_01_T                 hdr_dither_ctrl_01;	//0xCC230A98
	PE_O26_REG_H10_PCC32_GAIN_CTRL_T               hdr_pcc32_gain_ctrl;	//0xCC230A9C
	PE_O26_REG_H10_CSC3_CTRL_00_T                     hdr_csc3_ctrl_00;	//0xCC230AA0
	PE_O26_REG_H10_CSC3_CTRL_01_T                     hdr_csc3_ctrl_01;	//0xCC230AA4
	PE_O26_REG_H10_CSC3_CTRL_02_T                     hdr_csc3_ctrl_02;	//0xCC230AA8
	PE_O26_REG_H10_CSC3_CTRL_03_T                     hdr_csc3_ctrl_03;	//0xCC230AAC
	PE_O26_REG_H10_CSC3_CTRL_04_T                     hdr_csc3_ctrl_04;	//0xCC230AB0
	PE_O26_REG_H10_CSC3_CTRL_05_T                     hdr_csc3_ctrl_05;	//0xCC230AB4
	PE_O26_REG_H10_CSC3_CTRL_06_T                     hdr_csc3_ctrl_06;	//0xCC230AB8
	PE_O26_REG_H10_CSC3_CTRL_07_T                     hdr_csc3_ctrl_07;	//0xCC230ABC
	PE_O26_REG_H10_CSC3_CTRL_08_T                     hdr_csc3_ctrl_08;	//0xCC230AC0
	UINT32                                                  reserved55;	//0xCC230AC4
	UINT32                                                  reserved56;	//0xCC230AC8
	UINT32                                                  reserved57;	//0xCC230ACC
	PE_O26_REG_H10_TCM_SLUT0_00_T                     hdr_tcm_slut0_00;	//0xCC230AD0
	PE_O26_REG_H10_TCM_SLUT0_01_T                     hdr_tcm_slut0_01;	//0xCC230AD4
	PE_O26_REG_H10_TCM_SLUT0_02_T                     hdr_tcm_slut0_02;	//0xCC230AD8
	PE_O26_REG_H10_TCM_SLUT0_03_T                     hdr_tcm_slut0_03;	//0xCC230ADC
	PE_O26_REG_H10_TCM_SLUT0_04_T                     hdr_tcm_slut0_04;	//0xCC230AE0
	PE_O26_REG_H10_TCM_SLUT0_05_T                     hdr_tcm_slut0_05;	//0xCC230AE4
	PE_O26_REG_H10_TCM_SLUT0_06_T                     hdr_tcm_slut0_06;	//0xCC230AE8
	PE_O26_REG_H10_TCM_SLUT0_07_T                     hdr_tcm_slut0_07;	//0xCC230AEC
	PE_O26_REG_H10_TCM_SLUT0_08_T                     hdr_tcm_slut0_08;	//0xCC230AF0
	PE_O26_REG_H10_TCM_SLUT0_09_T                     hdr_tcm_slut0_09;	//0xCC230AF4
	PE_O26_REG_H10_SAT_MAP_CTRL_01_T               hdr_sat_map_ctrl_01;	//0xCC230AF8
	PE_O26_REG_H10_SAT_MAP_CTRL_02_T               hdr_sat_map_ctrl_02;	//0xCC230AFC
	UINT32                                                  reserved58;	//0xCC230B00
	UINT32                                                  reserved59;	//0xCC230B04
	UINT32                                                  reserved60;	//0xCC230B08
	UINT32                                                  reserved61;	//0xCC230B0C
	UINT32                                                  reserved62;	//0xCC230B10
	UINT32                                                  reserved63;	//0xCC230B14
	UINT32                                                  reserved64;	//0xCC230B18
	UINT32                                                  reserved65;	//0xCC230B1C
	PE_O26_REG_H10_YGAIN_LUT_CTRL_00_T           hdr_ygain_lut_ctrl_00;	//0xCC230B20
	PE_O26_REG_H10_YGAIN_LUT_CTRL_01_T           hdr_ygain_lut_ctrl_01;	//0xCC230B24
	PE_O26_REG_H10_YGAIN_LUT_CTRL_02_T           hdr_ygain_lut_ctrl_02;	//0xCC230B28
	PE_O26_REG_H10_YGAIN_LUT_CTRL_03_T           hdr_ygain_lut_ctrl_03;	//0xCC230B2C
	PE_O26_REG_H10_YGAIN_LUT_CTRL_04_T           hdr_ygain_lut_ctrl_04;	//0xCC230B30
	PE_O26_REG_H10_YGAIN_LUT_CTRL_05_T           hdr_ygain_lut_ctrl_05;	//0xCC230B34
	PE_O26_REG_H10_YGAIN_LUT_IA_CTRL_T           hdr_ygain_lut_ia_ctrl;	//0xCC230B38
	PE_O26_REG_H10_YGAIN_LUT_IA_DATA_T           hdr_ygain_lut_ia_data;	//0xCC230B3C
	PE_O26_REG_H10_RGB2Y_CTRL_00_T                   hdr_rgb2y_ctrl_00;	//0xCC230B40
	PE_O26_REG_H10_RGB2Y_CTRL_01_T                   hdr_rgb2y_ctrl_01;	//0xCC230B44
	PE_O26_REG_H10_RGB2Y_CTRL_02_T                   hdr_rgb2y_ctrl_02;	//0xCC230B48
	PE_O26_REG_H10_RGB2Y_CTRL_03_T                   hdr_rgb2y_ctrl_03;	//0xCC230B4C
	UINT32                                                  reserved66;	//0xCC230B50
	UINT32                                                  reserved67;	//0xCC230B54
	UINT32                                                  reserved68;	//0xCC230B58
	UINT32                                                  reserved69;	//0xCC230B5C
	PE_O26_REG_H10_LGAIN_LUT_CTRL_00_T           hdr_lgain_lut_ctrl_00;	//0xCC230B60
	PE_O26_REG_H10_LGAIN_LUT_CTRL_01_T           hdr_lgain_lut_ctrl_01;	//0xCC230B64
	PE_O26_REG_H10_LGAIN_LUT_CTRL_02_T           hdr_lgain_lut_ctrl_02;	//0xCC230B68
	PE_O26_REG_H10_LGAIN_LUT_CTRL_03_T           hdr_lgain_lut_ctrl_03;	//0xCC230B6C
	PE_O26_REG_H10_LGAIN_LUT_CTRL_04_T           hdr_lgain_lut_ctrl_04;	//0xCC230B70
	PE_O26_REG_H10_LGAIN_LUT_CTRL_05_T           hdr_lgain_lut_ctrl_05;	//0xCC230B74
	PE_O26_REG_H10_LGAIN_LUT_CTRL_06_T           hdr_lgain_lut_ctrl_06;	//0xCC230B78
	PE_O26_REG_H10_LGAIN_LUT_CTRL_07_T           hdr_lgain_lut_ctrl_07;	//0xCC230B7C
	PE_O26_REG_H10_SGAIN_LUT_CTRL_00_T           hdr_sgain_lut_ctrl_00;	//0xCC230B80
	PE_O26_REG_H10_SGAIN_LUT_CTRL_01_T           hdr_sgain_lut_ctrl_01;	//0xCC230B84
	PE_O26_REG_H10_SGAIN_LUT_CTRL_02_T           hdr_sgain_lut_ctrl_02;	//0xCC230B88
	PE_O26_REG_H10_SGAIN_LUT_CTRL_03_T           hdr_sgain_lut_ctrl_03;	//0xCC230B8C
	PE_O26_REG_H10_SGAIN_LUT_CTRL_04_T           hdr_sgain_lut_ctrl_04;	//0xCC230B90
	PE_O26_REG_H10_SGAIN_LUT_CTRL_05_T           hdr_sgain_lut_ctrl_05;	//0xCC230B94
	PE_O26_REG_H10_SGAIN_LUT_CTRL_06_T           hdr_sgain_lut_ctrl_06;	//0xCC230B98
	PE_O26_REG_H10_SGAIN_LUT_CTRL_07_T           hdr_sgain_lut_ctrl_07;	//0xCC230B9C
	PE_O26_REG_H10_RGB2Y2_CTRL_00_T                 hdr_rgb2y2_ctrl_00;	//0xCC230BA0
	PE_O26_REG_H10_RGB2Y2_CTRL_01_T                 hdr_rgb2y2_ctrl_01;	//0xCC230BA4
	PE_O26_REG_H10_RGB2Y2_CTRL_02_T                 hdr_rgb2y2_ctrl_02;	//0xCC230BA8
	PE_O26_REG_H10_RGB2Y2_CTRL_03_T                 hdr_rgb2y2_ctrl_03;	//0xCC230BAC
	PE_O26_REG_H10_CSC4_CTRL_00_T                     hdr_csc4_ctrl_00;	//0xCC230BB0
	PE_O26_REG_H10_CSC4_CTRL_01_T                     hdr_csc4_ctrl_01;	//0xCC230BB4
	PE_O26_REG_H10_CSC4_CTRL_02_T                     hdr_csc4_ctrl_02;	//0xCC230BB8
	PE_O26_REG_H10_CSC4_CTRL_03_T                     hdr_csc4_ctrl_03;	//0xCC230BBC
	PE_O26_REG_H10_CSC4_CTRL_04_T                     hdr_csc4_ctrl_04;	//0xCC230BC0
	PE_O26_REG_H10_CSC4_CTRL_05_T                     hdr_csc4_ctrl_05;	//0xCC230BC4
	PE_O26_REG_H10_CSC4_CTRL_06_T                     hdr_csc4_ctrl_06;	//0xCC230BC8
	PE_O26_REG_H10_CSC4_CTRL_07_T                     hdr_csc4_ctrl_07;	//0xCC230BCC
	PE_O26_REG_H10_CSC4_CTRL_08_T                     hdr_csc4_ctrl_08;	//0xCC230BD0
	UINT32                                                  reserved70;	//0xCC230BD4
	UINT32                                                  reserved71;	//0xCC230BD8
	UINT32                                                  reserved72;	//0xCC230BDC
	UINT32                                                  reserved73;	//0xCC230BE0
	UINT32                                                  reserved74;	//0xCC230BE4
	UINT32                                                  reserved75;	//0xCC230BE8
	UINT32                                                  reserved76;	//0xCC230BEC
	UINT32                                                  reserved77;	//0xCC230BF0
	UINT32                                                  reserved78;	//0xCC230BF4
	UINT32                                                  reserved79;	//0xCC230BF8
	UINT32                                                  reserved80;	//0xCC230BFC
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T hdr_cuva_tmlut_lut_ctrl_00;	//0xCC230C00
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T hdr_cuva_tmlut_lut_ctrl_01;	//0xCC230C04
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T hdr_cuva_tmlut_lut_ctrl_02;	//0xCC230C08
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T hdr_cuva_tmlut_lut_ctrl_03;	//0xCC230C0C
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T hdr_cuva_tmlut_lut_ctrl_04;	//0xCC230C10
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T hdr_cuva_tmlut_lut_ctrl_05;	//0xCC230C14
	PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T hdr_cuva_tmlut_lut_ia_ctrl;	//0xCC230C18
	PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T hdr_cuva_tmlut_lut_ia_data;	//0xCC230C1C
	PE_O26_REG_H10_CUVA_GLUT_00_T                     hdr_cuva_glut_00;	//0xCC230C20
	PE_O26_REG_H10_CUVA_GLUT_01_T                     hdr_cuva_glut_01;	//0xCC230C24
	PE_O26_REG_H10_CUVA_GLUT_02_T                     hdr_cuva_glut_02;	//0xCC230C28
	PE_O26_REG_H10_CUVA_GLUT_03_T                     hdr_cuva_glut_03;	//0xCC230C2C
	PE_O26_REG_H10_CUVA_GLUT_04_T                     hdr_cuva_glut_04;	//0xCC230C30
	PE_O26_REG_H10_CUVA_GLUT_05_T                     hdr_cuva_glut_05;	//0xCC230C34
	UINT32                                                  reserved81;	//0xCC230C38
	UINT32                                                  reserved82;	//0xCC230C3C
	PE_O26_REG_H10_CUVA_CTRL_T                           hdr_cuva_ctrl;	//0xCC230C40
	UINT32                                                  reserved83;	//0xCC230C44
	UINT32                                                  reserved84;	//0xCC230C48
	UINT32                                                  reserved85;	//0xCC230C4C
	PE_O26_REG_H10_FIM_GFD_CTRL_00_T               hdr_fim_gfd_ctrl_00;	//0xCC230C50
	PE_O26_REG_H10_FIM_GFD_CTRL_01_T               hdr_fim_gfd_ctrl_01;	//0xCC230C54
	PE_O26_REG_H10_FIM_GFD_STAT_00_T               hdr_fim_gfd_stat_00;	//0xCC230C58
	PE_O26_REG_H10_FIM_GFD_STAT_01_T               hdr_fim_gfd_stat_01;	//0xCC230C5C
	PE_O26_REG_H10_FIM_GFD_STAT_02_T               hdr_fim_gfd_stat_02;	//0xCC230C60
	PE_O26_REG_H10_FIM_GFD_STAT_03_T               hdr_fim_gfd_stat_03;	//0xCC230C64
	PE_O26_REG_H10_FIM_PCG_OFF_T                       hdr_fim_pcg_off;	//0xCC230C68
	UINT32                                                  reserved86;	//0xCC230C6C
	PE_O26_REG_H10_FIM_TPD_CTRL_00_T               hdr_fim_tpd_ctrl_00;	//0xCC230C70
	PE_O26_REG_H10_FIM_TPD_CTRL_01_T               hdr_fim_tpd_ctrl_01;	//0xCC230C74
	PE_O26_REG_H10_FIM_TPD_CTRL_02_T               hdr_fim_tpd_ctrl_02;	//0xCC230C78
	PE_O26_REG_H10_FIM_TPD_CTRL_03_T               hdr_fim_tpd_ctrl_03;	//0xCC230C7C
	PE_O26_REG_H10_FIM_TPD_CTRL_04_T               hdr_fim_tpd_ctrl_04;	//0xCC230C80
	PE_O26_REG_H10_FIM_TPD_CTRL_05_T               hdr_fim_tpd_ctrl_05;	//0xCC230C84
	PE_O26_REG_H10_FIM_TPD_CTRL_06_T               hdr_fim_tpd_ctrl_06;	//0xCC230C88
	PE_O26_REG_H10_FIM_TPD_CTRL_07_T               hdr_fim_tpd_ctrl_07;	//0xCC230C8C
	PE_O26_REG_H10_FIM_TPD_CTRL_08_T               hdr_fim_tpd_ctrl_08;	//0xCC230C90
	PE_O26_REG_H10_FIM_TPD_CTRL_09_T               hdr_fim_tpd_ctrl_09;	//0xCC230C94
	PE_O26_REG_H10_FIM_TPD_CTRL_0A_T               hdr_fim_tpd_ctrl_0a;	//0xCC230C98
	PE_O26_REG_H10_FIM_TPD_CTRL_0B_T               hdr_fim_tpd_ctrl_0b;	//0xCC230C9C
	PE_O26_REG_H10_FIM_TPD_STAT_00_T               hdr_fim_tpd_stat_00;	//0xCC230CA0
	PE_O26_REG_H10_FIM_BBD_CTRL_00_T               hdr_fim_bbd_ctrl_00;	//0xCC230CA4
	PE_O26_REG_H10_FIM_BBD_CTRL_01_T               hdr_fim_bbd_ctrl_01;	//0xCC230CA8
	PE_O26_REG_H10_FIM_BBD_CTRL_02_T               hdr_fim_bbd_ctrl_02;	//0xCC230CAC
	PE_O26_REG_H10_FIM__HIST_AI_CTRL_T           hdr_fim__hist_ai_ctrl;	//0xCC230CB0
	PE_O26_REG_H10_FIM__HIST_AI_DATA_T           hdr_fim__hist_ai_data;	//0xCC230CB4
	UINT32                                                  reserved87;	//0xCC230CB8
	UINT32                                                  reserved88;	//0xCC230CBC
	PE_O26_REG_H10_FIM_BBD_STAT_00_T               hdr_fim_bbd_stat_00;	//0xCC230CC0
	PE_O26_REG_H10_FIM_BBD_STAT_01_T               hdr_fim_bbd_stat_01;	//0xCC230CC4
	PE_O26_REG_H10_FIM_APL_STAT_00_T               hdr_fim_apl_stat_00;	//0xCC230CC8
	UINT32                                                  reserved89;	//0xCC230CCC
	UINT32                                                  reserved90;	//0xCC230CD0
	UINT32                                                  reserved91;	//0xCC230CD4
	UINT32                                                  reserved92;	//0xCC230CD8
	UINT32                                                  reserved93;	//0xCC230CDC
	UINT32                                                  reserved94;	//0xCC230CE0
	UINT32                                                  reserved95;	//0xCC230CE4
	UINT32                                                  reserved96;	//0xCC230CE8
	UINT32                                                  reserved97;	//0xCC230CEC
	PE_O26_REG_H10_HIST_EN_T                               hdr_hist_en;	//0xCC230CF0
	PE_O26_REG_H10_HIST_MODE_T                           hdr_hist_mode;	//0xCC230CF4
	PE_O26_REG_H10_HIST_CLEAR_T                         hdr_hist_clear;	//0xCC230CF8
	PE_O26_REG_H10_HIST_CTRL_ACQ_T                   hdr_hist_ctrl_acq;	//0xCC230CFC
	PE_O26_REG_H10_HIST_HOLD_CTRL_T                 hdr_hist_hold_ctrl;	//0xCC230D00
	UINT32                                                  reserved98;	//0xCC230D04
	UINT32                                                  reserved99;	//0xCC230D08
	UINT32                                                 reserved100;	//0xCC230D0C
	UINT32                                                 reserved101;	//0xCC230D10
	UINT32                                                 reserved102;	//0xCC230D14
	UINT32                                                 reserved103;	//0xCC230D18
	UINT32                                                 reserved104;	//0xCC230D1C
	PE_O26_REG_H10_HIST_CTRL_WSIZE_00_T         hdr_hist_ctrl_wsize_00;	//0xCC230D20
	PE_O26_REG_H10_HIST_CTRL_WSIZE_01_T         hdr_hist_ctrl_wsize_01;	//0xCC230D24
	PE_O26_REG_H10_HIST_CTRL_WSIZE_10_T         hdr_hist_ctrl_wsize_10;	//0xCC230D28
	PE_O26_REG_H10_HIST_CTRL_WSIZE_11_T         hdr_hist_ctrl_wsize_11;	//0xCC230D2C
	PE_O26_REG_H10_HIST_CTRL_WSIZE_20_T         hdr_hist_ctrl_wsize_20;	//0xCC230D30
	PE_O26_REG_H10_HIST_CTRL_WSIZE_21_T         hdr_hist_ctrl_wsize_21;	//0xCC230D34
	PE_O26_REG_H10_HIST_CTRL_WSIZE_30_T         hdr_hist_ctrl_wsize_30;	//0xCC230D38
	PE_O26_REG_H10_HIST_CTRL_WSIZE_31_T         hdr_hist_ctrl_wsize_31;	//0xCC230D3C
	PE_O26_REG_H10_HIST_CTRL_WSIZE_40_T         hdr_hist_ctrl_wsize_40;	//0xCC230D40
	PE_O26_REG_H10_HIST_CTRL_WSIZE_41_T         hdr_hist_ctrl_wsize_41;	//0xCC230D44
	PE_O26_REG_H10_HIST_CTRL_WSIZE_50_T         hdr_hist_ctrl_wsize_50;	//0xCC230D48
	PE_O26_REG_H10_HIST_CTRL_WSIZE_51_T         hdr_hist_ctrl_wsize_51;	//0xCC230D4C
	PE_O26_REG_H10_HIST_W0_IA_CTRL_T               hdr_hist_w0_ia_ctrl;	//0xCC230D50
	PE_O26_REG_H10_HIST_W0_IA_DATA1_T             hdr_hist_w0_ia_data1;	//0xCC230D54
	PE_O26_REG_H10_HIST_W0_IA_DATA2_T             hdr_hist_w0_ia_data2;	//0xCC230D58
	PE_O26_REG_H10_HIST_W1_IA_CTRL_T               hdr_hist_w1_ia_ctrl;	//0xCC230D5C
	PE_O26_REG_H10_HIST_W1_IA_DATA1_T             hdr_hist_w1_ia_data1;	//0xCC230D60
	PE_O26_REG_H10_HIST_W1_IA_DATA2_T             hdr_hist_w1_ia_data2;	//0xCC230D64
	PE_O26_REG_H10_HIST_W2_IA_CTRL_T               hdr_hist_w2_ia_ctrl;	//0xCC230D68
	PE_O26_REG_H10_HIST_W2_IA_DATA1_T             hdr_hist_w2_ia_data1;	//0xCC230D6C
	PE_O26_REG_H10_HIST_W2_IA_DATA2_T             hdr_hist_w2_ia_data2;	//0xCC230D70
	PE_O26_REG_H10_HIST_W3_IA_CTRL_T               hdr_hist_w3_ia_ctrl;	//0xCC230D74
	PE_O26_REG_H10_HIST_W3_IA_DATA1_T             hdr_hist_w3_ia_data1;	//0xCC230D78
	PE_O26_REG_H10_HIST_W3_IA_DATA2_T             hdr_hist_w3_ia_data2;	//0xCC230D7C
	PE_O26_REG_H10_HIST_W4_IA_CTRL_T               hdr_hist_w4_ia_ctrl;	//0xCC230D80
	PE_O26_REG_H10_HIST_W4_IA_DATA1_T             hdr_hist_w4_ia_data1;	//0xCC230D84
	PE_O26_REG_H10_HIST_W4_IA_DATA2_T             hdr_hist_w4_ia_data2;	//0xCC230D88
	PE_O26_REG_H10_HIST_W5_IA_CTRL_T               hdr_hist_w5_ia_ctrl;	//0xCC230D8C
	PE_O26_REG_H10_HIST_W5_IA_DATA1_T             hdr_hist_w5_ia_data1;	//0xCC230D90
	PE_O26_REG_H10_HIST_W5_IA_DATA2_T             hdr_hist_w5_ia_data2;	//0xCC230D94
	UINT32                                                 reserved105;	//0xCC230D98
	PE_O26_REG_H10_SR_DITHER_MUX_T                   hdr_sr_dither_mux;	//0xCC230D9C
	PE_O26_REG_H10_SR_DITHER_CTRL_00_T           hdr_sr_dither_ctrl_00;	//0xCC230DA0
	PE_O26_REG_H10_SR_DITHER_CTRL_01_T           hdr_sr_dither_ctrl_01;	//0xCC230DA4
	PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_00_T hdr_sr_dither_err_diffu_00;	//0xCC230DA8
	PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_01_T hdr_sr_dither_err_diffu_01;	//0xCC230DAC
	PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_02_T hdr_sr_dither_err_diffu_02;	//0xCC230DB0
	PE_O26_REG_H10_SR_DITHER_ERR_DIFFU_03_T hdr_sr_dither_err_diffu_03;	//0xCC230DB4
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_00_T hdr_sr_dither_rnd_diffu_00;	//0xCC230DB8
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_01_T hdr_sr_dither_rnd_diffu_01;	//0xCC230DBC
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_02_T hdr_sr_dither_rnd_diffu_02;	//0xCC230DC0
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_03_T hdr_sr_dither_rnd_diffu_03;	//0xCC230DC4
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_04_T hdr_sr_dither_rnd_diffu_04;	//0xCC230DC8
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_05_T hdr_sr_dither_rnd_diffu_05;	//0xCC230DCC
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_06_T hdr_sr_dither_rnd_diffu_06;	//0xCC230DD0
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_07_T hdr_sr_dither_rnd_diffu_07;	//0xCC230DD4
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_08_T hdr_sr_dither_rnd_diffu_08;	//0xCC230DD8
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_09_T hdr_sr_dither_rnd_diffu_09;	//0xCC230DDC
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_10_T hdr_sr_dither_rnd_diffu_10;	//0xCC230DE0
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_11_T hdr_sr_dither_rnd_diffu_11;	//0xCC230DE4
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_12_T hdr_sr_dither_rnd_diffu_12;	//0xCC230DE8
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_13_T hdr_sr_dither_rnd_diffu_13;	//0xCC230DEC
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_14_T hdr_sr_dither_rnd_diffu_14;	//0xCC230DF0
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_15_T hdr_sr_dither_rnd_diffu_15;	//0xCC230DF4
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_16_T hdr_sr_dither_rnd_diffu_16;	//0xCC230DF8
	PE_O26_REG_H10_SR_DITHER_RND_DIFFU_17_T hdr_sr_dither_rnd_diffu_17;	//0xCC230DFC
}PE_O26_REG_H10_T;

#if 0	//org
typedef union {
	UINT32 udata32;
	struct {						//0xCCC10800 RW 0x0000_0000
	UINT32 load_time                        :1;	//(0:0,RW,0x00) //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//(1:1,RW,0x00) //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//(2:2,RW,0x00) //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O26_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10804 RW 0x0870_0F00
	UINT32 width                            :16;	//(15:0,RW,0xF00) //width
	UINT32 height                           :16;	//(31:16,RW,0x870) //height
	};
}PE_O26_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10808 RW 0x0000_0014
	UINT32 vdpulse_pos                      :32;	//(31:0,RW,0x0000_0014) //vdpulse position for register loading
	};
}PE_O26_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1080C RO 0x0000_0000
	UINT32 vcnt                             :16;	//(15:0,RO,0x0) //vertical line count
	UINT32 vcnt2                            :16;	//(31:16,RO,0x0) //vertical line number
	};
}PE_O26_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10810 RO 0x0000_0800
	UINT32 r_to_cnt                         :12;	//(11:0,RO,0x0800) //apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//(30:30,RO,0x00) //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//(31:31,RO,0x00) //Vertical Active at PE1 output(Read only)
	};
}PE_O26_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10814 RW 0x0000_0000
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
}PE_O26_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10818 RW 0x0000_0000
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
}PE_O26_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1081C RW 0x0000_0000
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
}PE_O26_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10850 RW 0x0000_0001
	UINT32 reg_csc1st_en                    :1;	//(0:0,RW,0x01) //
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10854 RW 0x12AF_7CFE
	UINT32 r_csc1st_coef1                   :15;	//(14:0,RW,0x7CFE) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10858 RW 0x7590_12AF
	UINT32 r_csc1st_coef3                   :15;	//(14:0,RW,0x12AF) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//(30:16,RW,0x7590) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1085C RW 0x225F_0000
	UINT32 r_csc1st_coef5                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//(30:16,RW,0x225F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10860 RW 0x12AF_0000
	UINT32 r_csc1st_coef7                   :15;	//(14:0,RW,0x0) //
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//(30:16,RW,0x12AF) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10864 RW 0x1AF0_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//(30:16,RW,0x1AF0) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10868 RW 0x07C0_0600
	UINT32 r_csc1st_ofst1                   :11;	//(10:0,RW,0x0600) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//(26:16,RW,0x07C0) //
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1086C RW 0x0600_0000
	UINT32 r_csc1st_ofst3                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//(26:16,RW,0x0600) //
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10870 RW 0x0000_0000
	UINT32 r_csc1st_ofst5                   :11;	//(10:0,RW,0x00) //
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//(26:16,RW,0x00) //
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10874 RW 0x0000_0000
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
}PE_O26_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10878 RO 0x0000_0000
	UINT32 ireg_csc_cnt_under               :16;	//(15:0,RO,0x0) //
	UINT32 ireg_csc_cnt_over                :16;	//(31:16,RO,0x0) //
	};
}PE_O26_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10880 RW 0x0000_FFFF
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//(7:0,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//(15:8,RW,0xFF) //
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//(23:16,RW,0x00) //
	UINT32 r_pxl_rd_mark_en                 :1;	//(24:24,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//(28:28,RW,0x0) //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10884 RW 0x0000_0000
	UINT32 r_pxl_rd_pos_x                   :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10888 RO 0x0000_0000
	UINT32 pxl_read_rcr                     :10;	//(9:0,RO,0x00) //
	UINT32 pxl_read_bcb                     :10;	//(19:10,RO,0x00) //
	UINT32 pxl_read_gyy                     :10;	//(29:20,RO,0x00) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_PXL_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10890 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O26_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10894 RW 0x0000_0000
	UINT32 eotf_lut_data                    :32;	//(31:0,RW,0x0000_0000) //32 bit LUT data
	};
}PE_O26_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10898 RW 0x0000_0000
	UINT32 lut_addr                         :10;	//(9:0,RW,0x00) //indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//(27,RW,0x00) //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//(29:28,RW,0x00) //0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O26_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1089C RW 0x0000_0000
	UINT32 oetf_lut_data_o                  :16;	//(15:0,RW,0x0) //16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//(31:16,RW,0x0) //16 bit even LUT data
	};
}PE_O26_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108A0 RW 0x0000_0001
	UINT32 reg_pcc_en                       :1;	//(0,RW,0x1) //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108A4 RW 0x1220_7FDE
	UINT32 r_pcc_coef1                      :15;	//(14:0,RW,0x7FDE) //PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//(30:16,RW,0x1220) //PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108A8 RW 0x7E02_7E64
	UINT32 r_pcc_coef3                      :15;	//(14:0,RW,0x7E64) //PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//(30:16,RW,0x7E02) //PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108AC RW 0x11E6_7FB6
	UINT32 r_pcc_coef5                      :15;	//(14:0,RW,0x7FB6) //PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//(30:16,RW,0x11E6) //PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108B0 RW 0x7F10_7ED6
	UINT32 r_pcc_coef7                      :15;	//(14:0,RW,0x7ED6) //PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//(30:16,RW,0x7F10) //PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108B4 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//(30:16,RW,0x1A91) //PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108D0 RW 0x0000_3FF3
	UINT32 reg_hue_prsv_en                  :1;	//(0,RW,0x1) //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//(1,RW,0x1) //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//(13:4,RW,0x3FF) //0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//(25:16,RW,0x000) //0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_O26_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108D4 NA 0x0000_1000
	UINT32 reg_inp_l_sel                    :1;	//(0,RW,0x0) //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//(4,RW,0x0) //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//(8,RW,0x0) //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//(12,RW,0x1) //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_O26_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108E0 RW 0x121F_7FDE
	UINT32 r_tone_map_rgb2y_coef1           :15;	//(14:0,RW,0x7FDE) //
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//(30:16,RW,0x121F) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108E4 RW 0x7E02_0000
	UINT32 r_tone_map_rgbymax_sel           :3;	//(2:0,RW,0x0) //
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//(30:16,RW,0x7E02) //
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108E8 RW 0x0000_0000
	UINT32 ll_lut_addr                      :7;	//(6:0,RW,0x00) //indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//(8,NA,0x0) //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O26_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108EC RW 0x0000_0000
	UINT32 ll_lut_dat_rcr                   :10;	//(9:0,RW,0x000) //Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//(19:10,NA,0x000) //Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//(29:20,RW,0x000) //Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108F0 RW 0x1000_03FF
	UINT32 reg_alpha_hue                    :10;	//(9:0,RW,0x3FF) //alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//(25:16,RW,0x00) //alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//(28,RW,0x01) //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108F4 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef0            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//(16,RW,0x0) //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC108F8 RW 0x0000_0000
	UINT32 reg_alpha_ii_yy_coef2            :15;	//(14:0,RW,0x0) //alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//(30:16,RW,0x0) //alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10900 RW 0x0000_0001
	UINT32 reg_ll_pcc_en                    :1;	//(0,RW,0x1) //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10904 RW 0x1220_7FDE
	UINT32 r_ll_pcc_coef1                   :15;	//(14:0,RW,0x7FDE) //PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//(30:16,RW,0x1220) //PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10908 RW 0x7E02_7E64
	UINT32 r_ll_pcc_coef3                   :15;	//(14:0,RW,0x7E64) //PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//(30:16,RW,0x7E02) //PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1090C RW 0x11E6_7FB6
	UINT32 r_ll_pcc_coef5                   :15;	//(14:0,RW,0x7FB6) //PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//(30:16,RW,0x11E6) //PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10910 RW 0x7F10_7ED6
	UINT32 r_ll_pcc_coef7                   :15;	//(14:0,RW,0x7ED6) //PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//(30:16,RW,0x7F10) //PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10914 RW 0x1A91_0000
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//(30:16,RW,0x1A91) //PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10918 RW 0x0000_0000
	UINT32 reg_ll_ab_en                     :1;	//(0:0,RW,0x0) //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1091C RW 0x0048_000A
	UINT32 r_ll_ab_lut_x2                   :10;	//(9:0,RW,0xA) //
	UINT32 r_ll_ab_lut_x1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_x0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10920 RW 0x00BF_FFFF
	UINT32 r_ll_ab_lut_x5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_x3                   :10;	//(29:20,RW,0xB) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10924 RW 0x0000_2600
	UINT32 r_ll_ab_lut_y2                   :10;	//(9:0,RW,0x200) //
	UINT32 r_ll_ab_lut_y1                   :10;	//(19:10,RW,0x9) //
	UINT32 r_ll_ab_lut_y0                   :10;	//(29:20,RW,0x0) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10928 RW 0x3FFF_FFFF
	UINT32 r_ll_ab_lut_y5                   :10;	//(9:0,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y4                   :10;	//(19:10,RW,0x3FF) //
	UINT32 r_ll_ab_lut_y3                   :10;	//(29:20,RW,0x3FF) //
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10940 RW 0x0000_0000
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
}PE_O26_REG_H10_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10944 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10948 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1094C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10950 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10954 RW 0x0000_8000
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
}PE_O26_REG_H10_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10958 RW 0x0000_0000
	UINT32 hist_status0                     :32;	//(31:0,RW,0x0000_0000) //[22:0]hif_histogram_bin_read
	};
}PE_O26_REG_H10_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1095C RO 0x0000_0000
	UINT32 hist_v_min                       :16;	//(15:0,RO,0x0000) //[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//(31:16,RO,0x0000) //[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O26_REG_H10_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10970 RW 0x0000_0000
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
}PE_O26_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10974 RW 0x0438_0780
	UINT32 tpg_size_x                       :14;	//(13:0,RW,0x780) //tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//(28:16,RW,0x438) //tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10978 RW 0x0000_0000
	UINT32 tpg_mask_flag                    :16;	//(15:0,RW,0x0000) //
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1097C RW 0x0000_0000
	UINT32 tpg_in_out_sel                   :16;	//(15:0,RW,0x0) //in_out_sel
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10980 RW 0x0000_0000
	UINT32 tpg_color_r                      :10;	//(9:0,RW,0x00) //tpg_color_r
	UINT32 tpg_color_b                      :10;	//(19:10,RW,0x00) //tpg_color_b
	UINT32 tpg_color_g                      :10;	//(29:20,RW,0x00) //tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10984 RW 0x0000_8000
	UINT32 hif_tpg_address                  :8;	//(7:0,RW,0x00) //cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//(8:8,RW,0x00) //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//(11:11,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//(12:12,RW,0x00) //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//(15:15,RW,0x01) //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O26_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10988 RW 0x0000_0000
	UINT32 hif_tpg_wdata_y                  :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10990 RW 0x0000_0000
	UINT32 reg_clut_65th_data               :11;	//(10:0,NA,0x000) //65th_data
	UINT32 resvd                            :21;
	};
}PE_O26_REG_H10_CLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10994 RW 0x0000_0000
	UINT32 clut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 clut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 clut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_CLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10998 RW 0x0000_0000
	UINT32 clut_data                        :11;	//(10:0,RW,0x00) //data for CLUT
	UINT32 resvd                            :21;
	};
}PE_O26_REG_H10_CLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC1099C RW 0x0000_0000
	UINT32 reg_plut_65th_data               :14;	//(13:0,NA,0x000) //65th_data
	UINT32 resvd                            :18;
	};
}PE_O26_REG_H10_PLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109A0 RW 0x0000_0000
	UINT32 plut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 plut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 plut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_PLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109A4 RW 0x0000_0000
	UINT32 plut_data                        :14;	//(13:0,RW,0x0) //data for PLUT
	UINT32 resvd                            :18;
	};
}PE_O26_REG_H10_PLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109A8 RW 0x0000_0000
	UINT32 reg_slut_65th_data               :10;	//(9:0,NA,0x000) //65th_data
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_SLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109AC RW 0x0000_0000
	UINT32 slut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 slut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 slut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_SLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109B0 RW 0x0000_0000
	UINT32 slut_data                        :10;	//(9:0,RW,0x00) //data for SLUT
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_SLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109B4 RW 0x0000_0000
	UINT32 reg_ilut_65th_data               :8;	//(7:0,NA,0x000) //65th_data
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_ILUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109B8 RW 0x0000_0000
	UINT32 ilut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 ilut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 ilut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_ILUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109BC RW 0x0000_0000
	UINT32 ilut_data                        :8;	//(7:0,RW,0x0) //data for ILUT
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_ILUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109C0 RW 0x0000_0000
	UINT32 reg_dlut_65th_data               :12;	//(11:0,NA,0x000) //65th_data
	UINT32 resvd0                           :4;
	UINT32 reg_dlut_threshold_0             :13;	//(28:16,NA,0x000) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109C4 RW 0x0000_0000
	UINT32 reg_dlut_threshold_1             :13;	//(12:0,RW,0x0) //
	UINT32 resvd0                           :3;
	UINT32 reg_dlut_threshold_2             :13;	//(28:16,RW,0x0) //
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109C8 RW 0x0000_0000
	UINT32 reg_dlut_step_0                  :4;	//(3:0,RW,0x00) //
	UINT32 reg_dlut_step_1                  :4;	//(7:4,RW,0x00) //
	UINT32 reg_dlut_step_2                  :4;	//(11:8,RW,0x00) //
	UINT32 reg_dlut_step_3                  :4;	//(15:12,RW,0x00) //
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109CC RW 0x0000_0000
	UINT32 dlut_addr                        :6;	//(5:0,RW,0x0) //indirect address
	UINT32 resvd0                           :6;
	UINT32 dlut_ai                          :1;	//(12,RW,0x00) //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 dlut_manual_load_en              :1;	//(29,RW,0x00) //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//(30,RW,0x00) //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//(31,RW,0x00) //assign '1' when LUT wr is done
	};
}PE_O26_REG_H10_DLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109D0 RW 0x0000_0000
	UINT32 dlut_data                        :8;	//(7:0,RW,0x0) //data for DLUT
	UINT32 resvd                            :24;
	};
}PE_O26_REG_H10_DLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109D4 RW 0x0000_0001
	UINT32 reg_technicolor_detour_en        :1;	//(0,NA,0x1) //
	UINT32 resvd0                           :3;
	UINT32 reg_range_sel                    :1;	//(4,NA,0x000) //0':limited range, '1':full range
	UINT32 resvd1                           :27;
	};
}PE_O26_REG_H10_TC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109D8 RW 0x1E00_1F00
	UINT32 reg_alpha_a                      :13;	//(12:0,RW,0x1F00) //default value : 7936
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_b                      :13;	//(28:16,RW,0x1E00) //default value : 7680
	UINT32 resvd1                           :3;
	};
}PE_O26_REG_H10_TC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109DC RW 0x0000_0000
	UINT32 reg_oct_0                        :6;	//(5:0,RW,0x0) //unsigned 6 bit
	UINT32 resvd0                           :4;
	UINT32 reg_oct_1                        :8;	//(17:10,RW,0x0) //signed 8 bit
	UINT32 resvd1                           :2;
	UINT32 reg_oct_2                        :9;	//(28:20,RW,0x00) //signed 9 bit
	UINT32 resvd2                           :3;
	};
}PE_O26_REG_H10_TC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109E0 RW 0x0000_0000
	UINT32 reg_oct_3                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 reg_oct_4                        :10;	//(19:10,RW,0x00) //signed 10 bit
	UINT32 reg_oct_5                        :10;	//(29:20,RW,0x00) //signed 10 bit
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_TC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC109E4 RW 0x0000_0000
	UINT32 reg_oct_6                        :10;	//(9:0,RW,0x00) //signed 10 bit
	UINT32 resvd                            :22;
	};
}PE_O26_REG_H10_TC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A00 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A14 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A18 RW 0xFFFF_FFFF
	UINT32 hif_llut0_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A20 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A24 RW 0x0000_0000
	UINT32 hif_llut0_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A30 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A34 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A38 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A3C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A40 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A44 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_x_33rd           :32;	//(31:0,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A48 RW 0xFFFF_FFFF
	UINT32 hif_llut1_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A50 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A54 RW 0x0000_0000
	UINT32 hif_llut1_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A60 RW 0x0000_0000
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
}PE_O26_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A64 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A68 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A6C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A70 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A74 RW 0xFFFF_FFFF
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//(31:16,RW,0xFFFFFFFF) //X coordinate of 33rd control point
	};
}PE_O26_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A78 RW 0xFFFF_FFFF
	UINT32 hif_llut2_wdata_y_33rd           :16;	//(15:0,RW,0xFFFF) //Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O26_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A80 RW 0x0000_8000
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
}PE_O26_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A84 RW 0x0000_0000
	UINT32 hif_llut2_wdata_y                :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A90 RW 0x0000_0000
	UINT32 gamma045_enable                  :1;	//(0:0,RW,0x00) //gamma 0.45(1/2.2) enable
	UINT32 resvd0                           :3;
	UINT32 gamma045_mode                    :1;	//(4:4,RW,0x00) //
	UINT32 resvd1                           :3;
	UINT32 gamma045_mux                     :1;	//(8:8,RW,0x00) //
	UINT32 resvd2                           :23;
	};
}PE_O26_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A98 RW 0x0000_0000
	UINT32 dither_en                        :1;	//(0:0,RW,0x00) //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//(2:2,RW,0x00) //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//(3:3,RW,0x00) //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//(5:4,RW,0x00) //"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O26_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10A9C RW 0x0000_0000
	UINT32 hif_pcc32_ygain_shift            :1;	//(0:0,RW,0x0) //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AA0 RW 0x0000_0001
	UINT32 reg_csc3rd_en                    :1;	//(0:0,RW,0x01) //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AA4 RW 0x094A_00D0
	UINT32 r_csc3rd_coef1                   :15;	//(14:0,RW,0x00D0) //CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//(30:16,RW,0x094A) //CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AA8 RW 0x0399_7AF3
	UINT32 r_csc3rd_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//(30:16,RW,0x0399) //CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AAC RW 0x0702_7E0B
	UINT32 r_csc3rd_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AB0 RW 0x798F_7F70
	UINT32 r_csc3rd_coef7                   :15;	//(14:0,RW,0x7F70) //CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//(30:16,RW,0x798F) //CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AB4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//(30:16,RW,0x0702) //CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AB8 RW 0x0000_0000
	UINT32 r_csc3rd_ofst1                   :11;	//(10:0,RW,0x000) //CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//(26:16,RW,0x000) //CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10ABC RW 0x0000_0040
	UINT32 r_csc3rd_ofst3                   :11;	//(10:0,RW,0x040) //CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//(26:16,RW,0x200) //CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AC0 RW 0x0200_0200
	UINT32 r_csc3rd_ofst5                   :11;	//(10:0,RW,0x0200) //CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//(26:16,RW,0x0200) //CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AD0 RW 0x0000_0000
	UINT32 r_slut0_x0                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AD4 RW 0x0000_0000
	UINT32 r_slut0_x1                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AD8 RW 0x0000_0000
	UINT32 r_slut0_x2                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10ADC RW 0x0000_0000
	UINT32 r_slut0_x3                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AE0 RW 0x0000_0000
	UINT32 r_slut0_x4                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AE4 RW 0x0000_0000
	UINT32 r_slut0_x5                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AE8 RW 0x0000_0000
	UINT32 r_slut0_x6                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AEC RW 0x0000_0000
	UINT32 r_slut0_x7                       :32;	//(31:00,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AF0 RW 0x0000_0000
	UINT32 r_slut0_y0                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y1                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y2                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y3                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AF4 RW 0x0000_0000
	UINT32 r_slut0_y4                       :8;	//(7:0,RW,0x0) //
	UINT32 r_slut0_y5                       :8;	//(15:8,RW,0x0) //
	UINT32 r_slut0_y6                       :8;	//(23:16,RW,0x0) //
	UINT32 r_slut0_y7                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AF8 RW 0x0000_0000
	UINT32 reg_tm_m2020_coef13              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd                            :1;
	UINT32 reg_tm_m2020_coef22              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 sat_gain_en                      :1;	//(31:31,RW,0x00) //TM0 Saturation Gain Enable
	};
}PE_O26_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10AFC RW 0x0000_0000
	UINT32 reg_tm_m2020_coef23              :15;	//(14:0,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm_m2020_coef32              :15;	//(30:16,RW,0x0000) //TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B20 RW 0x0000_0000
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
}PE_O26_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B24 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B28 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B2C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B30 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B34 RW 0xFFFF_1000
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_O26_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B38 RW 0x0000_8000
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
}PE_O26_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B3C RW 0x0000_0000
	UINT32 hif_ygain_lut_wdata_y            :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B40 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B44 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_O26_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B48 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B4C RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B60 RW 0x0000_0080
	UINT32 lgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of LGAIN LUT point 0
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B64 RW 0x2492_0080
	UINT32 lgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of LGAIN LUT point 1
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B68 RW 0x4924_0080
	UINT32 lgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of LGAIN LUT point 2
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B6C RW 0x6DB6_0080
	UINT32 lgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of LGAIN LUT point 3
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B70 RW 0x9248_0080
	UINT32 lgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of LGAIN LUT point 4
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B74 RW 0xB6DA_0080
	UINT32 lgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of LGAIN LUT point 5
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B78 RW 0xDB6C_0080
	UINT32 lgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of LGAIN LUT point 6
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B7C RW 0xFFFF_0080
	UINT32 lgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of LGAIN LUT point 7
	};
}PE_O26_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B80 RW 0x0000_0080
	UINT32 sgain_lut_y0                     :8;	//(7:0,RW,0x0800) //y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//(31:16,RW,0x0000) //x value of SGAIN LUT point 0
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B84 RW 0x2492_0080
	UINT32 sgain_lut_y1                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//(31:16,RW,0x2492) //x value of SGAIN LUT point 1
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B88 RW 0x4924_0080
	UINT32 sgain_lut_y2                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//(31:16,RW,0x4924) //x value of SGAIN LUT point 2
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B8C RW 0x6DB6_0080
	UINT32 sgain_lut_y3                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//(31:16,RW,0x6DB6) //x value of SGAIN LUT point 3
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B90 RW 0x9248_0080
	UINT32 sgain_lut_y4                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//(31:16,RW,0x9248) //x value of SGAIN LUT point 4
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B94 RW 0xB6DA_0080
	UINT32 sgain_lut_y5                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//(31:16,RW,0xB6DA) //x value of SGAIN LUT point 5
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B98 RW 0xDB6C_0080
	UINT32 sgain_lut_y6                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//(31:16,RW,0xDB6C) //x value of SGAIN LUT point 6
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10B9C RW 0xFFFF_0080
	UINT32 sgain_lut_y7                     :8;	//(7:0,RW,0x0080) //y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//(31:16,RW,0xFFFF) //x value of SGAIN LUT point 7
	};
}PE_O26_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BA0 RW 0x0AD9_0001
	UINT32 reg_rgb2yrd_en                   :1;	//(0:0,RW,0x1) //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//(30:16,RW,0x0AD9) //RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BA4 RW 0x0434_00F3
	UINT32 r_rgb2yrd_coef1                  :15;	//(14:0,RW,0x00F3) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//(31:16,RW,0x0434) //RGB -> Y CSC Coefficient 0
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BA8 RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst0                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BAC RW 0x0000_0000
	UINT32 r_rgb2yrd_ofst3                  :17;	//(16:0,RW,0x0) //RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O26_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BB0 RW 0x0000_0000
	UINT32 reg_csc4th_en                    :1;	//(0:0,RW,0x00) //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BB4 RW 0x094A_00D0
	UINT32 r_csc4th_coef1                   :15;	//(14:0,RW,0x00D0) //CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//(30:16,RW,0x094A) //CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BB8 RW 0x0399_7AF3
	UINT32 r_csc4th_coef3                   :15;	//(14:0,RW,0x7AF3) //CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//(30:16,RW,0x0399) //CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BBC RW 0x0702_7E0B
	UINT32 r_csc4th_coef5                   :15;	//(14:0,RW,0x7E0B) //CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BC0 RW 0x798F_7F70
	UINT32 r_csc4th_coef7                   :15;	//(14:0,RW,0x7F70) //CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//(30:16,RW,0x798F) //CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BC4 RW 0x0702_0000
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//(30:16,RW,0x0702) //CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O26_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BC8 RW 0x0000_0000
	UINT32 r_csc4th_ofst1                   :11;	//(10:0,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//(26:16,RW,0x000) //CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BCC RW 0x0000_0040
	UINT32 r_csc4th_ofst3                   :11;	//(10:0,RW,0x040) //CSC 4th Y'U'V' -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst2                   :11;	//(26:16,RW,0x200) //CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10BD0 RW 0x0200_0200
	UINT32 r_csc4th_ofst5                   :11;	//(10:0,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst4                   :11;	//(26:16,RW,0x0200) //CSC 4th Y'U'V' -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O26_REG_H10_CSC4_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C00 RW 0x0000_0000
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
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C04 RW 0x0000_0000
	UINT32 win_w0_x0                        :16;	//(15:0,RW,0x0) //win_w0_x0
	UINT32 win_w0_y0                        :16;	//(31:16,RW,0x0) //win_w0_y0
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C08 RW 0x086F_0EFF
	UINT32 win_w0_x1                        :16;	//(15:0,RW,0xEFF) //win_w0_x1
	UINT32 win_w0_y1                        :16;	//(31:16,RW,0x86F) //win_w0_y1
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C0C RW 0x0000_0000
	UINT32 win_w1_x0                        :16;	//(15:0,RW,0x0) //win_w1_x0
	UINT32 win_w1_y0                        :16;	//(31:16,RW,0x0) //win_w1_y0
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C10 RW 0x086F_0EFF
	UINT32 win_w1_x1                        :16;	//(15:0,RW,0xEFF) //win_w1_x1
	UINT32 win_w1_y1                        :16;	//(31:16,RW,0x86F) //win_w1_y1
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C14 RW 0xFFFF_1000
	UINT32 hif_cuva_tmlut_lut_wdata_y_33rd  :16;	//(15:0,RW,0x1000) //Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_cuva_tmlut_lut_wdata_x_33rd  :16;	//(31:16,RW,0xFFFF) //X coordinate of 33rd control point (Default : 65535)
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C18 RW 0x0000_8000
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
}PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C1C RW 0x0000_0000
	UINT32 hif_cuva_tmlut_lut_wdata_y       :16;	//(15:0,RW,0x0) //Y coordinate of control point
	UINT32 hif_cuva_tmlut_lut_wdata_x       :16;	//(31:16,RW,0x0) //X coordinate of control point
	};
}PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C20 RW 0x0000_0000
	UINT32 r_cglut_x1                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x0                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C24 RW 0x0000_0000
	UINT32 r_cglut_x3                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x2                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C28 RW 0x0000_0000
	UINT32 r_cglut_x5                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x4                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C2C RW 0x0000_0000
	UINT32 r_cglut_x7                       :16;	//(15:00,RW,0x0) //
	UINT32 r_cglut_x6                       :16;	//(31:16,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C30 RW 0x0000_0000
	UINT32 r_cglut_y3                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y2                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y1                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y0                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C34 RW 0x0000_0000
	UINT32 r_cglut_y7                       :8;	//(7:0,RW,0x0) //
	UINT32 r_cglut_y6                       :8;	//(15:8,RW,0x0) //
	UINT32 r_cglut_y5                       :8;	//(23:16,RW,0x0) //
	UINT32 r_cglut_y4                       :8;	//(31:24,RW,0x0) //
	};
}PE_O26_REG_H10_CUVA_GLUT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C40 RW 0x0000_0000
	UINT32 r_cuva_eotf_mux                  :2;	//(1:0,RW,0x0) //
	UINT32 resvd0                           :2;
	UINT32 r_cuva_sat_gain_bit              :1;	//(4:4,RW,0x0) //
	UINT32 resvd1                           :3;
	UINT32 r_cuva_sat_gain_sel              :1;	//(8:8,RW,0x0) //
	UINT32 resvd2                           :23;
	};
}PE_O26_REG_H10_CUVA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C50 RW 0xFF00_FF00
	UINT32 reg_gfd_h_th0_a                  :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_h_th1_a                  :8;	//(15:8,RW,0xFF) //
	UINT32 reg_gfd_h_th0_b                  :8;	//(23:16,RW,0x0) //
	UINT32 reg_gfd_h_th1_b                  :8;	//(31:24,RW,0xFF) //
	};
}PE_O26_REG_H10_FIM_GFD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C54 RW 0x0000_0000
	UINT32 reg_gfd_s_th                     :8;	//(7:0,RW,0x0) //
	UINT32 reg_gfd_v_th                     :8;	//(15:8,RW,0x00) //
	UINT32 resvd                            :14;
	UINT32 reg_scale                        :2;	//(31:30,RW,0x0) //0 := x1/64 (MSB 16bit)  for 4K input	1 = x1/16 for 2K input	2 = x1/4 for 1K input	3 = x1 for 1K input
	};
}PE_O26_REG_H10_FIM_GFD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C58 RO 0x0000_0000
	UINT32 reg_gfd_count_a01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Top
	UINT32 reg_gfd_count_a00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Top
	};
}PE_O26_REG_H10_FIM_GFD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C5C RO 0x0000_0000
	UINT32 reg_gfd_count_a11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region A, Right-Bottom
	UINT32 reg_gfd_count_a10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region A, Left-Bottom
	};
}PE_O26_REG_H10_FIM_GFD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C60 RO 0x0000_0000
	UINT32 reg_gfd_count_b01                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Top
	UINT32 reg_gfd_count_b00                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Top
	};
}PE_O26_REG_H10_FIM_GFD_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C64 RO 0x0000_0000
	UINT32 reg_gfd_count_b11                :16;	//(15:0,NA,0x0) //the number of pixels inside the HSV color region B, Right-Bottom
	UINT32 reg_gfd_count_b10                :16;	//(31:16,NA,0x0) //the number of pixels inside the HSV color region B, Left-Bottom
	};
}PE_O26_REG_H10_FIM_GFD_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C68 RW 0x0000_0000
	UINT32 reg_pcg_off                      :1;	//(0:0,NA,0x0) //
	UINT32 resvd                            :31;
	};
}PE_O26_REG_H10_FIM_PCG_OFF_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C70 RW 0x00EC_1200
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
}PE_O26_REG_H10_FIM_TPD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C74 RW 0x0000_0000
	UINT32 wina_x0                          :12;	//(11:0,RW,0x00) //winA_x0
	UINT32 resvd0                           :3;
	UINT32 reg_wina_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 wina_y0                          :12;	//(27:16,RW,0x00) //winA_y0
	UINT32 resvd1                           :3;
	UINT32 reg_wina_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C78 RW 0x4437_077F
	UINT32 wina_x1                          :12;	//(11:0,RW,0x077F) //winA_x1
	UINT32 resvd0                           :4;
	UINT32 wina_y1                          :12;	//(27:16,RW,0x0437) //winA_y1
	UINT32 resvd1                           :2;
	UINT32 reg_hist_hsv_hsl_sel             :1;	//(30,RW,0x01) //HSV/HSL selection for histogram	0 : HSL	1 : HSV
	UINT32 reg_hist_vscaling_en             :1;	//(31,RW,0x00) //HSV selection when HSV(reg_hist_hsv_hsl_sel = 0x1)	0 : HSV	1 : HSVs
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C7C RW 0x0000_0000
	UINT32 winb_x0                          :12;	//(11:0,RW,0x00) //winB_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winb_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winb_y0                          :12;	//(27:16,RW,0x00) //winB_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winb_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C80 RW 0x0437_077F
	UINT32 winb_x1                          :12;	//(11:0,RW,0x077F) //winB_x1
	UINT32 resvd0                           :4;
	UINT32 winb_y1                          :12;	//(27:16,RW,0x0437) //winB_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C84 RW 0x0000_0000
	UINT32 winc_x0                          :12;	//(11:0,RW,0x00) //winC_x0
	UINT32 resvd0                           :3;
	UINT32 reg_winc_hen                     :1;	//(15,RW,0x00) //(horizontal) window mode enable	0 := full screen	1 = window by manual setting
	UINT32 winc_y0                          :12;	//(27:16,RW,0x00) //winC_y0
	UINT32 resvd1                           :3;
	UINT32 reg_winc_ven                     :1;	//(31,RW,0x00) //(vertical) window mode enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C88 RW 0x0437_077F
	UINT32 winc_x1                          :12;	//(11:0,RW,0x077F) //winC_x1
	UINT32 resvd0                           :4;
	UINT32 winc_y1                          :12;	//(27:16,RW,0x0437) //winC_y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C8C RW 0x0000_0000
	UINT32 reg_force_y                      :10;	//(9:0,RW,0x00) //force Y value
	UINT32 reg_force_y_max_th               :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_y_min_th               :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_y_enable               :1;	//(31,RW,0x00) //force Y enable
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C90 RW 0x0000_0000
	UINT32 reg_force_cb                     :10;	//(9:0,RW,0x00) //force Cb value
	UINT32 reg_force_cb_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cb_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cb_enable              :1;	//(31,RW,0x00) //force Cb enable(with Y range)
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C94 RW 0x0000_0000
	UINT32 reg_force_cr                     :10;	//(9:0,RW,0x00) //force Cr value
	UINT32 reg_force_cr_max_th              :10;	//(19:10,RW,0x00) //forcing range max th
	UINT32 reg_force_cr_min_th              :10;	//(29:20,RW,0x00) //forcing range min th
	UINT32 resvd                            :1;
	UINT32 reg_force_cr_enable              :1;	//(31,RW,0x00) //force Cr enable(with Y range)
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C98 RW 0x0000_03FF
	UINT32 reg_s_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_s_th_min                     :10;	//(25:16,RW,0x00) //threshold for histogram input data control
	UINT32 resvd1                           :6;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_0A_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10C9C RW 0x0000_03FF
	UINT32 reg_y_th_max                     :10;	//(9:0,RW,0x3FF) //
	UINT32 resvd0                           :6;
	UINT32 reg_y_th_min                     :10;	//(25:16,RW,0x00) //
	UINT32 resvd1                           :6;
	};
}PE_O26_REG_H10_FIM_TPD_CTRL_0B_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CA0 RO 0x0000_0000
	UINT32 hist_pixel_count                 :22;	//(21:0,RO,0x0_0000) //histogram pixel count sum
	UINT32 resvd                            :10;
	};
}PE_O26_REG_H10_FIM_TPD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CA4 RW 0x0010_2000
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
}PE_O26_REG_H10_FIM_BBD_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CA8 RW 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RW,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RW,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CAC RW 0x0437_077F
	UINT32 x1                               :12;	//(11:0,RW,0x077F) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RW,0x0437) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CB0 RW 0x0000_8000
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
}PE_O26_REG_H10_FIM__HIST_AI_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CB4 RW 0x0000_0000
	UINT32 hist_status                      :22;	//(21:0,RW,0x0000_0000) //histogram bin data(0~31 bin)
	UINT32 resvd                            :10;
	};
}PE_O26_REG_H10_FIM__HIST_AI_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CC0 RO 0x0000_0000
	UINT32 x0                               :12;	//(11:0,RO,0x00) //x0
	UINT32 resvd0                           :4;
	UINT32 y0                               :12;	//(27:16,RO,0x00) //y0
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CC4 RO 0x01DF_02CF
	UINT32 x1                               :12;	//(11:0,RO,0x02CF) //x1
	UINT32 resvd0                           :4;
	UINT32 y1                               :12;	//(27:16,RO,0x01DF) //y1
	UINT32 resvd1                           :4;
	};
}PE_O26_REG_H10_FIM_BBD_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xCCC10CC8 RO 0x0000_0068
	UINT32 y_g_s_apl                        :10;	//(9:0,RO,0x068) //data APL(data selected by BBD_CTRL_00) (debug bar display with TPD_CTRL_06/07)
	UINT32 cb_b_s_apl                       :10;	//(19:10,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 cr_r_s_apl                       :10;	//(29:20,RO,0x00) //data APL(data selected by BBD_CTRL_00)
	UINT32 resvd                            :2;
	};
}PE_O26_REG_H10_FIM_APL_STAT_00_T;

typedef struct {
	PE_O26_REG_H10_TOP_CTRL_00_T                       hdr_top_ctrl_00;	//0xCCC10800
	PE_O26_REG_H10_TOP_CTRL_01_T                       hdr_top_ctrl_01;	//0xCCC10804
	PE_O26_REG_H10_TOP_CTRL_02_T                       hdr_top_ctrl_02;	//0xCCC10808
	PE_O26_REG_H10_TOP_CTRL_03_T                       hdr_top_ctrl_03;	//0xCCC1080C
	PE_O26_REG_H10_TOP_CTRL_04_T                       hdr_top_ctrl_04;	//0xCCC10810
	PE_O26_REG_H10_TOP_CTRL_05_T                       hdr_top_ctrl_05;	//0xCCC10814
	PE_O26_REG_H10_TOP_CTRL_06_T                       hdr_top_ctrl_06;	//0xCCC10818
	PE_O26_REG_H10_TOP_CTRL_07_T                       hdr_top_ctrl_07;	//0xCCC1081C
	UINT32                                                    reserved0;	//0xCCC10820
	UINT32                                                    reserved1;	//0xCCC10824
	UINT32                                                    reserved2;	//0xCCC10828
	UINT32                                                    reserved3;	//0xCCC1082C
	UINT32                                                    reserved4;	//0xCCC10830
	UINT32                                                    reserved5;	//0xCCC10834
	UINT32                                                    reserved6;	//0xCCC10838
	UINT32                                                    reserved7;	//0xCCC1083C
	UINT32                                                    reserved8;	//0xCCC10840
	UINT32                                                    reserved9;	//0xCCC10844
	UINT32                                                   reserved10;	//0xCCC10848
	UINT32                                                   reserved11;	//0xCCC1084C
	PE_O26_REG_H10_CSC1_CTRL_00_T                     hdr_csc1_ctrl_00;	//0xCCC10850
	PE_O26_REG_H10_CSC1_CTRL_01_T                     hdr_csc1_ctrl_01;	//0xCCC10854
	PE_O26_REG_H10_CSC1_CTRL_02_T                     hdr_csc1_ctrl_02;	//0xCCC10858
	PE_O26_REG_H10_CSC1_CTRL_03_T                     hdr_csc1_ctrl_03;	//0xCCC1085C
	PE_O26_REG_H10_CSC1_CTRL_04_T                     hdr_csc1_ctrl_04;	//0xCCC10860
	PE_O26_REG_H10_CSC1_CTRL_05_T                     hdr_csc1_ctrl_05;	//0xCCC10864
	PE_O26_REG_H10_CSC1_CTRL_06_T                     hdr_csc1_ctrl_06;	//0xCCC10868
	PE_O26_REG_H10_CSC1_CTRL_07_T                     hdr_csc1_ctrl_07;	//0xCCC1086C
	PE_O26_REG_H10_CSC1_CTRL_08_T                     hdr_csc1_ctrl_08;	//0xCCC10870
	PE_O26_REG_H10_CSC1_CTRL_09_T                     hdr_csc1_ctrl_09;	//0xCCC10874
	PE_O26_REG_H10_CSC1_ERR_CNT_T                     hdr_csc1_err_cnt;	//0xCCC10878
	UINT32                                                   reserved12;	//0xCCC1087C
	PE_O26_REG_H10_PXL_RD_CTRL0_T                     hdr_pxl_rd_ctrl0;	//0xCCC10880
	PE_O26_REG_H10_PXL_RD_CTRL1_T                     hdr_pxl_rd_ctrl1;	//0xCCC10884
	PE_O26_REG_H10_PXL_RD_DATA_T                       hdr_pxl_rd_data;	//0xCCC10888
	UINT32                                                   reserved13;	//0xCCC1088C
	PE_O26_REG_H10_EOTF_IA_CTRL_T                     hdr_eotf_ia_ctrl;	//0xCCC10890
	PE_O26_REG_H10_EOTF_IA_DATA_T                     hdr_eotf_ia_data;	//0xCCC10894
	PE_O26_REG_H10_OETF_IA_CTRL_T                     hdr_oetf_ia_ctrl;	//0xCCC10898
	PE_O26_REG_H10_OETF_IA_DATA_T                     hdr_oetf_ia_data;	//0xCCC1089C
	PE_O26_REG_H10_PCC_CTRL_00_T                       hdr_pcc_ctrl_00;	//0xCCC108A0
	PE_O26_REG_H10_PCC_CTRL_01_T                       hdr_pcc_ctrl_01;	//0xCCC108A4
	PE_O26_REG_H10_PCC_CTRL_02_T                       hdr_pcc_ctrl_02;	//0xCCC108A8
	PE_O26_REG_H10_PCC_CTRL_03_T                       hdr_pcc_ctrl_03;	//0xCCC108AC
	PE_O26_REG_H10_PCC_CTRL_04_T                       hdr_pcc_ctrl_04;	//0xCCC108B0
	PE_O26_REG_H10_PCC_CTRL_05_T                       hdr_pcc_ctrl_05;	//0xCCC108B4
	UINT32                                                   reserved14;	//0xCCC108B8
	UINT32                                                   reserved15;	//0xCCC108BC
	UINT32                                                   reserved16;	//0xCCC108C0
	UINT32                                                   reserved17;	//0xCCC108C4
	UINT32                                                   reserved18;	//0xCCC108C8
	UINT32                                                   reserved19;	//0xCCC108CC
	PE_O26_REG_H10_HUE_SAT_CTRL_T                     hdr_hue_sat_ctrl;	//0xCCC108D0
	PE_O26_REG_H10_HUE_SAT_ALPHA_CTRL_T         hdr_hue_sat_alpha_ctrl;	//0xCCC108D4
	UINT32                                                   reserved20;	//0xCCC108D8
	UINT32                                                   reserved21;	//0xCCC108DC
	PE_O26_REG_H10_TCM_PREP_00_T                       hdr_tcm_prep_00;	//0xCCC108E0
	PE_O26_REG_H10_TCM_PREP_01_T                       hdr_tcm_prep_01;	//0xCCC108E4
	PE_O26_REG_H10_LL_LUT_IA_CTRL_T                 hdr_ll_lut_ia_ctrl;	//0xCCC108E8
	PE_O26_REG_H10_LL_LUT_IA_DATA_T                 hdr_ll_lut_ia_data;	//0xCCC108EC
	PE_O26_REG_H10_LL_HUE_CTRL_00_T                 hdr_ll_hue_ctrl_00;	//0xCCC108F0
	PE_O26_REG_H10_LL_HUE_CTRL_01_T                 hdr_ll_hue_ctrl_01;	//0xCCC108F4
	PE_O26_REG_H10_LL_HUE_CTRL_02_T                 hdr_ll_hue_ctrl_02;	//0xCCC108F8
	UINT32                                                   reserved22;	//0xCCC108FC
	PE_O26_REG_H10_LLPCC_CTRL_00_T                   hdr_llpcc_ctrl_00;	//0xCCC10900
	PE_O26_REG_H10_LLPCC_CTRL_01_T                   hdr_llpcc_ctrl_01;	//0xCCC10904
	PE_O26_REG_H10_LLPCC_CTRL_02_T                   hdr_llpcc_ctrl_02;	//0xCCC10908
	PE_O26_REG_H10_LLPCC_CTRL_03_T                   hdr_llpcc_ctrl_03;	//0xCCC1090C
	PE_O26_REG_H10_LLPCC_CTRL_04_T                   hdr_llpcc_ctrl_04;	//0xCCC10910
	PE_O26_REG_H10_LLPCC_CTRL_05_T                   hdr_llpcc_ctrl_05;	//0xCCC10914
	PE_O26_REG_H10_LL_AB_CTRL_00_T                   hdr_ll_ab_ctrl_00;	//0xCCC10918
	PE_O26_REG_H10_LL_AB_CTRL_01_T                   hdr_ll_ab_ctrl_01;	//0xCCC1091C
	PE_O26_REG_H10_LL_AB_CTRL_02_T                   hdr_ll_ab_ctrl_02;	//0xCCC10920
	PE_O26_REG_H10_LL_AB_CTRL_03_T                   hdr_ll_ab_ctrl_03;	//0xCCC10924
	PE_O26_REG_H10_LL_AB_CTRL_04_T                   hdr_ll_ab_ctrl_04;	//0xCCC10928
	UINT32                                                   reserved23;	//0xCCC1092C
	UINT32                                                   reserved24;	//0xCCC10930
	UINT32                                                   reserved25;	//0xCCC10934
	UINT32                                                   reserved26;	//0xCCC10938
	UINT32                                                   reserved27;	//0xCCC1093C
	PE_O26_REG_H10_HIST_CTRL_00_T                     hdr_hist_ctrl_00;	//0xCCC10940
	PE_O26_REG_H10_HIST_CTRL_01_T                     hdr_hist_ctrl_01;	//0xCCC10944
	PE_O26_REG_H10_HIST_CTRL_02_T                     hdr_hist_ctrl_02;	//0xCCC10948
	PE_O26_REG_H10_HIST_CTRL_03_T                     hdr_hist_ctrl_03;	//0xCCC1094C
	PE_O26_REG_H10_HIST_CTRL_04_T                     hdr_hist_ctrl_04;	//0xCCC10950
	PE_O26_REG_H10_HIST_IA_CTRL_T                     hdr_hist_ia_ctrl;	//0xCCC10954
	PE_O26_REG_H10_HIST_IA_DATA1_T                   hdr_hist_ia_data1;	//0xCCC10958
	PE_O26_REG_H10_HIST_IA_DATA2_T                   hdr_hist_ia_data2;	//0xCCC1095C
	UINT32                                                   reserved28;	//0xCCC10960
	UINT32                                                   reserved29;	//0xCCC10964
	UINT32                                                   reserved30;	//0xCCC10968
	UINT32                                                   reserved31;	//0xCCC1096C
	PE_O26_REG_H10_TPG_CTRL_00_T                       hdr_tpg_ctrl_00;	//0xCCC10970
	PE_O26_REG_H10_TPG_CTRL_01_T                       hdr_tpg_ctrl_01;	//0xCCC10974
	PE_O26_REG_H10_TPG_CTRL_02_T                       hdr_tpg_ctrl_02;	//0xCCC10978
	PE_O26_REG_H10_TPG_CTRL_03_T                       hdr_tpg_ctrl_03;	//0xCCC1097C
	PE_O26_REG_H10_TPG_CTRL_04_T                       hdr_tpg_ctrl_04;	//0xCCC10980
	PE_O26_REG_H10_TPG_IA_CTRL_T                       hdr_tpg_ia_ctrl;	//0xCCC10984
	PE_O26_REG_H10_TPG_IA_DATA_T                       hdr_tpg_ia_data;	//0xCCC10988
	UINT32                                                   reserved32;	//0xCCC1098C
	PE_O26_REG_H10_CLUT_CTRL_00_T                     hdr_clut_ctrl_00;	//0xCCC10990
	PE_O26_REG_H10_CLUT_IA_CTRL_T                     hdr_clut_ia_ctrl;	//0xCCC10994
	PE_O26_REG_H10_CLUT_IA_DATA_T                     hdr_clut_ia_data;	//0xCCC10998
	PE_O26_REG_H10_PLUT_CTRL_00_T                     hdr_plut_ctrl_00;	//0xCCC1099C
	PE_O26_REG_H10_PLUT_IA_CTRL_T                     hdr_plut_ia_ctrl;	//0xCCC109A0
	PE_O26_REG_H10_PLUT_IA_DATA_T                     hdr_plut_ia_data;	//0xCCC109A4
	PE_O26_REG_H10_SLUT_CTRL_00_T                     hdr_slut_ctrl_00;	//0xCCC109A8
	PE_O26_REG_H10_SLUT_IA_CTRL_T                     hdr_slut_ia_ctrl;	//0xCCC109AC
	PE_O26_REG_H10_SLUT_IA_DATA_T                     hdr_slut_ia_data;	//0xCCC109B0
	PE_O26_REG_H10_ILUT_CTRL_00_T                     hdr_ilut_ctrl_00;	//0xCCC109B4
	PE_O26_REG_H10_ILUT_IA_CTRL_T                     hdr_ilut_ia_ctrl;	//0xCCC109B8
	PE_O26_REG_H10_ILUT_IA_DATA_T                     hdr_ilut_ia_data;	//0xCCC109BC
	PE_O26_REG_H10_DLUT_CTRL_00_T                     hdr_dlut_ctrl_00;	//0xCCC109C0
	PE_O26_REG_H10_DLUT_CTRL_01_T                     hdr_dlut_ctrl_01;	//0xCCC109C4
	PE_O26_REG_H10_DLUT_CTRL_02_T                     hdr_dlut_ctrl_02;	//0xCCC109C8
	PE_O26_REG_H10_DLUT_IA_CTRL_T                     hdr_dlut_ia_ctrl;	//0xCCC109CC
	PE_O26_REG_H10_DLUT_IA_DATA_T                     hdr_dlut_ia_data;	//0xCCC109D0
	PE_O26_REG_H10_TC_CTRL_00_T                         hdr_tc_ctrl_00;	//0xCCC109D4
	PE_O26_REG_H10_TC_CTRL_01_T                         hdr_tc_ctrl_01;	//0xCCC109D8
	PE_O26_REG_H10_TC_CTRL_02_T                         hdr_tc_ctrl_02;	//0xCCC109DC
	PE_O26_REG_H10_TC_CTRL_03_T                         hdr_tc_ctrl_03;	//0xCCC109E0
	PE_O26_REG_H10_TC_CTRL_04_T                         hdr_tc_ctrl_04;	//0xCCC109E4
	UINT32                                                   reserved33;	//0xCCC109E8
	UINT32                                                   reserved34;	//0xCCC109EC
	UINT32                                                   reserved35;	//0xCCC109F0
	UINT32                                                   reserved36;	//0xCCC109F4
	UINT32                                                   reserved37;	//0xCCC109F8
	UINT32                                                   reserved38;	//0xCCC109FC
	PE_O26_REG_H10_LLUT0_CTRL_00_T                   hdr_llut0_ctrl_00;	//0xCCC10A00
	PE_O26_REG_H10_LLUT0_CTRL_01_T                   hdr_llut0_ctrl_01;	//0xCCC10A04
	PE_O26_REG_H10_LLUT0_CTRL_02_T                   hdr_llut0_ctrl_02;	//0xCCC10A08
	PE_O26_REG_H10_LLUT0_CTRL_03_T                   hdr_llut0_ctrl_03;	//0xCCC10A0C
	PE_O26_REG_H10_LLUT0_CTRL_04_T                   hdr_llut0_ctrl_04;	//0xCCC10A10
	PE_O26_REG_H10_LLUT0_CTRL_05_T                   hdr_llut0_ctrl_05;	//0xCCC10A14
	PE_O26_REG_H10_LLUT0_CTRL_06_T                   hdr_llut0_ctrl_06;	//0xCCC10A18
	UINT32                                                   reserved39;	//0xCCC10A1C
	PE_O26_REG_H10_LLUT0_IA_CTRL_T                   hdr_llut0_ia_ctrl;	//0xCCC10A20
	PE_O26_REG_H10_LLUT0_IA_DATA_T                   hdr_llut0_ia_data;	//0xCCC10A24
	UINT32                                                   reserved40;	//0xCCC10A28
	UINT32                                                   reserved41;	//0xCCC10A2C
	PE_O26_REG_H10_LLUT1_CTRL_00_T                   hdr_llut1_ctrl_00;	//0xCCC10A30
	PE_O26_REG_H10_LLUT1_CTRL_01_T                   hdr_llut1_ctrl_01;	//0xCCC10A34
	PE_O26_REG_H10_LLUT1_CTRL_02_T                   hdr_llut1_ctrl_02;	//0xCCC10A38
	PE_O26_REG_H10_LLUT1_CTRL_03_T                   hdr_llut1_ctrl_03;	//0xCCC10A3C
	PE_O26_REG_H10_LLUT1_CTRL_04_T                   hdr_llut1_ctrl_04;	//0xCCC10A40
	PE_O26_REG_H10_LLUT1_CTRL_05_T                   hdr_llut1_ctrl_05;	//0xCCC10A44
	PE_O26_REG_H10_LLUT1_CTRL_06_T                   hdr_llut1_ctrl_06;	//0xCCC10A48
	UINT32                                                   reserved42;	//0xCCC10A4C
	PE_O26_REG_H10_LLUT1_IA_CTRL_T                   hdr_llut1_ia_ctrl;	//0xCCC10A50
	PE_O26_REG_H10_LLUT1_IA_DATA_T                   hdr_llut1_ia_data;	//0xCCC10A54
	UINT32                                                   reserved43;	//0xCCC10A58
	UINT32                                                   reserved44;	//0xCCC10A5C
	PE_O26_REG_H10_LLUT2_CTRL_00_T                   hdr_llut2_ctrl_00;	//0xCCC10A60
	PE_O26_REG_H10_LLUT2_CTRL_01_T                   hdr_llut2_ctrl_01;	//0xCCC10A64
	PE_O26_REG_H10_LLUT2_CTRL_02_T                   hdr_llut2_ctrl_02;	//0xCCC10A68
	PE_O26_REG_H10_LLUT2_CTRL_03_T                   hdr_llut2_ctrl_03;	//0xCCC10A6C
	PE_O26_REG_H10_LLUT2_CTRL_04_T                   hdr_llut2_ctrl_04;	//0xCCC10A70
	PE_O26_REG_H10_LLUT2_CTRL_05_T                   hdr_llut2_ctrl_05;	//0xCCC10A74
	PE_O26_REG_H10_LLUT2_CTRL_06_T                   hdr_llut2_ctrl_06;	//0xCCC10A78
	UINT32                                                   reserved45;	//0xCCC10A7C
	PE_O26_REG_H10_LLUT2_IA_CTRL_T                   hdr_llut2_ia_ctrl;	//0xCCC10A80
	PE_O26_REG_H10_LLUT2_IA_DATA_T                   hdr_llut2_ia_data;	//0xCCC10A84
	UINT32                                                   reserved46;	//0xCCC10A88
	UINT32                                                   reserved47;	//0xCCC10A8C
	PE_O26_REG_H10_GAMMA045_CTRL_00_T             hdr_gamma045_ctrl_00;	//0xCCC10A90
	UINT32                                                   reserved48;	//0xCCC10A94
	PE_O26_REG_H10_DITHER_CTRL_00_T                 hdr_dither_ctrl_00;	//0xCCC10A98
	PE_O26_REG_H10_PCC32_GAIN_CTRL_T               hdr_pcc32_gain_ctrl;	//0xCCC10A9C
	PE_O26_REG_H10_CSC3_CTRL_00_T                     hdr_csc3_ctrl_00;	//0xCCC10AA0
	PE_O26_REG_H10_CSC3_CTRL_01_T                     hdr_csc3_ctrl_01;	//0xCCC10AA4
	PE_O26_REG_H10_CSC3_CTRL_02_T                     hdr_csc3_ctrl_02;	//0xCCC10AA8
	PE_O26_REG_H10_CSC3_CTRL_03_T                     hdr_csc3_ctrl_03;	//0xCCC10AAC
	PE_O26_REG_H10_CSC3_CTRL_04_T                     hdr_csc3_ctrl_04;	//0xCCC10AB0
	PE_O26_REG_H10_CSC3_CTRL_05_T                     hdr_csc3_ctrl_05;	//0xCCC10AB4
	PE_O26_REG_H10_CSC3_CTRL_06_T                     hdr_csc3_ctrl_06;	//0xCCC10AB8
	PE_O26_REG_H10_CSC3_CTRL_07_T                     hdr_csc3_ctrl_07;	//0xCCC10ABC
	PE_O26_REG_H10_CSC3_CTRL_08_T                     hdr_csc3_ctrl_08;	//0xCCC10AC0
	UINT32                                                   reserved49;	//0xCCC10AC4
	UINT32                                                   reserved50;	//0xCCC10AC8
	UINT32                                                   reserved51;	//0xCCC10ACC
	PE_O26_REG_H10_TCM_SLUT0_00_T                     hdr_tcm_slut0_00;	//0xCCC10AD0
	PE_O26_REG_H10_TCM_SLUT0_01_T                     hdr_tcm_slut0_01;	//0xCCC10AD4
	PE_O26_REG_H10_TCM_SLUT0_02_T                     hdr_tcm_slut0_02;	//0xCCC10AD8
	PE_O26_REG_H10_TCM_SLUT0_03_T                     hdr_tcm_slut0_03;	//0xCCC10ADC
	PE_O26_REG_H10_TCM_SLUT0_04_T                     hdr_tcm_slut0_04;	//0xCCC10AE0
	PE_O26_REG_H10_TCM_SLUT0_05_T                     hdr_tcm_slut0_05;	//0xCCC10AE4
	PE_O26_REG_H10_TCM_SLUT0_06_T                     hdr_tcm_slut0_06;	//0xCCC10AE8
	PE_O26_REG_H10_TCM_SLUT0_07_T                     hdr_tcm_slut0_07;	//0xCCC10AEC
	PE_O26_REG_H10_TCM_SLUT0_08_T                     hdr_tcm_slut0_08;	//0xCCC10AF0
	PE_O26_REG_H10_TCM_SLUT0_09_T                     hdr_tcm_slut0_09;	//0xCCC10AF4
	PE_O26_REG_H10_SAT_MAP_CTRL_01_T               hdr_sat_map_ctrl_01;	//0xCCC10AF8
	PE_O26_REG_H10_SAT_MAP_CTRL_02_T               hdr_sat_map_ctrl_02;	//0xCCC10AFC
	UINT32                                                   reserved52;	//0xCCC10B00
	UINT32                                                   reserved53;	//0xCCC10B04
	UINT32                                                   reserved54;	//0xCCC10B08
	UINT32                                                   reserved55;	//0xCCC10B0C
	UINT32                                                   reserved56;	//0xCCC10B10
	UINT32                                                   reserved57;	//0xCCC10B14
	UINT32                                                   reserved58;	//0xCCC10B18
	UINT32                                                   reserved59;	//0xCCC10B1C
	PE_O26_REG_H10_YGAIN_LUT_CTRL_00_T           hdr_ygain_lut_ctrl_00;	//0xCCC10B20
	PE_O26_REG_H10_YGAIN_LUT_CTRL_01_T           hdr_ygain_lut_ctrl_01;	//0xCCC10B24
	PE_O26_REG_H10_YGAIN_LUT_CTRL_02_T           hdr_ygain_lut_ctrl_02;	//0xCCC10B28
	PE_O26_REG_H10_YGAIN_LUT_CTRL_03_T           hdr_ygain_lut_ctrl_03;	//0xCCC10B2C
	PE_O26_REG_H10_YGAIN_LUT_CTRL_04_T           hdr_ygain_lut_ctrl_04;	//0xCCC10B30
	PE_O26_REG_H10_YGAIN_LUT_CTRL_05_T           hdr_ygain_lut_ctrl_05;	//0xCCC10B34
	PE_O26_REG_H10_YGAIN_LUT_IA_CTRL_T           hdr_ygain_lut_ia_ctrl;	//0xCCC10B38
	PE_O26_REG_H10_YGAIN_LUT_IA_DATA_T           hdr_ygain_lut_ia_data;	//0xCCC10B3C
	PE_O26_REG_H10_RGB2Y_CTRL_00_T                   hdr_rgb2y_ctrl_00;	//0xCCC10B40
	PE_O26_REG_H10_RGB2Y_CTRL_01_T                   hdr_rgb2y_ctrl_01;	//0xCCC10B44
	PE_O26_REG_H10_RGB2Y_CTRL_02_T                   hdr_rgb2y_ctrl_02;	//0xCCC10B48
	PE_O26_REG_H10_RGB2Y_CTRL_03_T                   hdr_rgb2y_ctrl_03;	//0xCCC10B4C
	UINT32                                                   reserved60;	//0xCCC10B50
	UINT32                                                   reserved61;	//0xCCC10B54
	UINT32                                                   reserved62;	//0xCCC10B58
	UINT32                                                   reserved63;	//0xCCC10B5C
	PE_O26_REG_H10_LGAIN_LUT_CTRL_00_T           hdr_lgain_lut_ctrl_00;	//0xCCC10B60
	PE_O26_REG_H10_LGAIN_LUT_CTRL_01_T           hdr_lgain_lut_ctrl_01;	//0xCCC10B64
	PE_O26_REG_H10_LGAIN_LUT_CTRL_02_T           hdr_lgain_lut_ctrl_02;	//0xCCC10B68
	PE_O26_REG_H10_LGAIN_LUT_CTRL_03_T           hdr_lgain_lut_ctrl_03;	//0xCCC10B6C
	PE_O26_REG_H10_LGAIN_LUT_CTRL_04_T           hdr_lgain_lut_ctrl_04;	//0xCCC10B70
	PE_O26_REG_H10_LGAIN_LUT_CTRL_05_T           hdr_lgain_lut_ctrl_05;	//0xCCC10B74
	PE_O26_REG_H10_LGAIN_LUT_CTRL_06_T           hdr_lgain_lut_ctrl_06;	//0xCCC10B78
	PE_O26_REG_H10_LGAIN_LUT_CTRL_07_T           hdr_lgain_lut_ctrl_07;	//0xCCC10B7C
	PE_O26_REG_H10_SGAIN_LUT_CTRL_00_T           hdr_sgain_lut_ctrl_00;	//0xCCC10B80
	PE_O26_REG_H10_SGAIN_LUT_CTRL_01_T           hdr_sgain_lut_ctrl_01;	//0xCCC10B84
	PE_O26_REG_H10_SGAIN_LUT_CTRL_02_T           hdr_sgain_lut_ctrl_02;	//0xCCC10B88
	PE_O26_REG_H10_SGAIN_LUT_CTRL_03_T           hdr_sgain_lut_ctrl_03;	//0xCCC10B8C
	PE_O26_REG_H10_SGAIN_LUT_CTRL_04_T           hdr_sgain_lut_ctrl_04;	//0xCCC10B90
	PE_O26_REG_H10_SGAIN_LUT_CTRL_05_T           hdr_sgain_lut_ctrl_05;	//0xCCC10B94
	PE_O26_REG_H10_SGAIN_LUT_CTRL_06_T           hdr_sgain_lut_ctrl_06;	//0xCCC10B98
	PE_O26_REG_H10_SGAIN_LUT_CTRL_07_T           hdr_sgain_lut_ctrl_07;	//0xCCC10B9C
	PE_O26_REG_H10_RGB2Y2_CTRL_00_T                 hdr_rgb2y2_ctrl_00;	//0xCCC10BA0
	PE_O26_REG_H10_RGB2Y2_CTRL_01_T                 hdr_rgb2y2_ctrl_01;	//0xCCC10BA4
	PE_O26_REG_H10_RGB2Y2_CTRL_02_T                 hdr_rgb2y2_ctrl_02;	//0xCCC10BA8
	PE_O26_REG_H10_RGB2Y2_CTRL_03_T                 hdr_rgb2y2_ctrl_03;	//0xCCC10BAC
	PE_O26_REG_H10_CSC4_CTRL_00_T                     hdr_csc4_ctrl_00;	//0xCCC10BB0
	PE_O26_REG_H10_CSC4_CTRL_01_T                     hdr_csc4_ctrl_01;	//0xCCC10BB4
	PE_O26_REG_H10_CSC4_CTRL_02_T                     hdr_csc4_ctrl_02;	//0xCCC10BB8
	PE_O26_REG_H10_CSC4_CTRL_03_T                     hdr_csc4_ctrl_03;	//0xCCC10BBC
	PE_O26_REG_H10_CSC4_CTRL_04_T                     hdr_csc4_ctrl_04;	//0xCCC10BC0
	PE_O26_REG_H10_CSC4_CTRL_05_T                     hdr_csc4_ctrl_05;	//0xCCC10BC4
	PE_O26_REG_H10_CSC4_CTRL_06_T                     hdr_csc4_ctrl_06;	//0xCCC10BC8
	PE_O26_REG_H10_CSC4_CTRL_07_T                     hdr_csc4_ctrl_07;	//0xCCC10BCC
	PE_O26_REG_H10_CSC4_CTRL_08_T                     hdr_csc4_ctrl_08;	//0xCCC10BD0
	UINT32                                                   reserved64;	//0xCCC10BD4
	UINT32                                                   reserved65;	//0xCCC10BD8
	UINT32                                                   reserved66;	//0xCCC10BDC
	UINT32                                                   reserved67;	//0xCCC10BE0
	UINT32                                                   reserved68;	//0xCCC10BE4
	UINT32                                                   reserved69;	//0xCCC10BE8
	UINT32                                                   reserved70;	//0xCCC10BEC
	UINT32                                                   reserved71;	//0xCCC10BF0
	UINT32                                                   reserved72;	//0xCCC10BF4
	UINT32                                                   reserved73;	//0xCCC10BF8
	UINT32                                                   reserved74;	//0xCCC10BFC
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_00_T hdr_cuva_tmlut_lut_ctrl_00;	//0xCCC10C00
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_01_T hdr_cuva_tmlut_lut_ctrl_01;	//0xCCC10C04
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_02_T hdr_cuva_tmlut_lut_ctrl_02;	//0xCCC10C08
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_03_T hdr_cuva_tmlut_lut_ctrl_03;	//0xCCC10C0C
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_04_T hdr_cuva_tmlut_lut_ctrl_04;	//0xCCC10C10
	PE_O26_REG_H10_CUVA_TMLUT_LUT_CTRL_05_T hdr_cuva_tmlut_lut_ctrl_05;	//0xCCC10C14
	PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_CTRL_T hdr_cuva_tmlut_lut_ia_ctrl;	//0xCCC10C18
	PE_O26_REG_H10_CUVA_TMLUT_LUT_IA_DATA_T hdr_cuva_tmlut_lut_ia_data;	//0xCCC10C1C
	PE_O26_REG_H10_CUVA_GLUT_00_T                     hdr_cuva_glut_00;	//0xCCC10C20
	PE_O26_REG_H10_CUVA_GLUT_01_T                     hdr_cuva_glut_01;	//0xCCC10C24
	PE_O26_REG_H10_CUVA_GLUT_02_T                     hdr_cuva_glut_02;	//0xCCC10C28
	PE_O26_REG_H10_CUVA_GLUT_03_T                     hdr_cuva_glut_03;	//0xCCC10C2C
	PE_O26_REG_H10_CUVA_GLUT_04_T                     hdr_cuva_glut_04;	//0xCCC10C30
	PE_O26_REG_H10_CUVA_GLUT_05_T                     hdr_cuva_glut_05;	//0xCCC10C34
	UINT32                                                   reserved75;	//0xCCC10C38
	UINT32                                                   reserved76;	//0xCCC10C3C
	PE_O26_REG_H10_CUVA_CTRL_T                           hdr_cuva_ctrl;	//0xCCC10C40
	UINT32                                                   reserved77;	//0xCCC10C44
	UINT32                                                   reserved78;	//0xCCC10C48
	UINT32                                                   reserved79;	//0xCCC10C4C
	PE_O26_REG_H10_FIM_GFD_CTRL_00_T               hdr_fim_gfd_ctrl_00;	//0xCCC10C50
	PE_O26_REG_H10_FIM_GFD_CTRL_01_T               hdr_fim_gfd_ctrl_01;	//0xCCC10C54
	PE_O26_REG_H10_FIM_GFD_STAT_00_T               hdr_fim_gfd_stat_00;	//0xCCC10C58
	PE_O26_REG_H10_FIM_GFD_STAT_01_T               hdr_fim_gfd_stat_01;	//0xCCC10C5C
	PE_O26_REG_H10_FIM_GFD_STAT_02_T               hdr_fim_gfd_stat_02;	//0xCCC10C60
	PE_O26_REG_H10_FIM_GFD_STAT_03_T               hdr_fim_gfd_stat_03;	//0xCCC10C64
	PE_O26_REG_H10_FIM_PCG_OFF_T                       hdr_fim_pcg_off;	//0xCCC10C68
	UINT32                                                   reserved80;	//0xCCC10C6C
	PE_O26_REG_H10_FIM_TPD_CTRL_00_T               hdr_fim_tpd_ctrl_00;	//0xCCC10C70
	PE_O26_REG_H10_FIM_TPD_CTRL_01_T               hdr_fim_tpd_ctrl_01;	//0xCCC10C74
	PE_O26_REG_H10_FIM_TPD_CTRL_02_T               hdr_fim_tpd_ctrl_02;	//0xCCC10C78
	PE_O26_REG_H10_FIM_TPD_CTRL_03_T               hdr_fim_tpd_ctrl_03;	//0xCCC10C7C
	PE_O26_REG_H10_FIM_TPD_CTRL_04_T               hdr_fim_tpd_ctrl_04;	//0xCCC10C80
	PE_O26_REG_H10_FIM_TPD_CTRL_05_T               hdr_fim_tpd_ctrl_05;	//0xCCC10C84
	PE_O26_REG_H10_FIM_TPD_CTRL_06_T               hdr_fim_tpd_ctrl_06;	//0xCCC10C88
	PE_O26_REG_H10_FIM_TPD_CTRL_07_T               hdr_fim_tpd_ctrl_07;	//0xCCC10C8C
	PE_O26_REG_H10_FIM_TPD_CTRL_08_T               hdr_fim_tpd_ctrl_08;	//0xCCC10C90
	PE_O26_REG_H10_FIM_TPD_CTRL_09_T               hdr_fim_tpd_ctrl_09;	//0xCCC10C94
	PE_O26_REG_H10_FIM_TPD_CTRL_0A_T               hdr_fim_tpd_ctrl_0a;	//0xCCC10C98
	PE_O26_REG_H10_FIM_TPD_CTRL_0B_T               hdr_fim_tpd_ctrl_0b;	//0xCCC10C9C
	PE_O26_REG_H10_FIM_TPD_STAT_00_T               hdr_fim_tpd_stat_00;	//0xCCC10CA0
	PE_O26_REG_H10_FIM_BBD_CTRL_00_T               hdr_fim_bbd_ctrl_00;	//0xCCC10CA4
	PE_O26_REG_H10_FIM_BBD_CTRL_01_T               hdr_fim_bbd_ctrl_01;	//0xCCC10CA8
	PE_O26_REG_H10_FIM_BBD_CTRL_02_T               hdr_fim_bbd_ctrl_02;	//0xCCC10CAC
	PE_O26_REG_H10_FIM__HIST_AI_CTRL_T           hdr_fim__hist_ai_ctrl;	//0xCCC10CB0
	PE_O26_REG_H10_FIM__HIST_AI_DATA_T           hdr_fim__hist_ai_data;	//0xCCC10CB4
	UINT32                                                   reserved81;	//0xCCC10CB8
	UINT32                                                   reserved82;	//0xCCC10CBC
	PE_O26_REG_H10_FIM_BBD_STAT_00_T               hdr_fim_bbd_stat_00;	//0xCCC10CC0
	PE_O26_REG_H10_FIM_BBD_STAT_01_T               hdr_fim_bbd_stat_01;	//0xCCC10CC4
	PE_O26_REG_H10_FIM_APL_STAT_00_T               hdr_fim_apl_stat_00;	//0xCCC10CC8
}PE_O26_REG_H10_T;
#endif//org

typedef union {
	UINT32 udata32;
	struct {					//0xCC232100 RW 0x0000_0000
	UINT32 v_status             :10;//09:00 v_status
	UINT32 reserved0            :6; //15:10
	UINT32 h_status             :10;//25:16 h_status
	UINT32 reserved1            :6; //31:26
	};
}PE_O26_REG_HDR_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {					//0xCC232104 RW 0x0000_0000
	UINT32 v_status             :10;//09:00 v_status
	UINT32 reserved0            :6; //15:10
	UINT32 h_status             :10;//25:16 h_status
	UINT32 reserved1            :6; //31:26
	};
}PE_O26_REG_HDR_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {					//0xCC232108 RW 0x0000_0000
	UINT32 reg_full_yc_flag     :1;	//(0:0,RW,0x0000_0000) //
	UINT32 resvd                :31;//(31:1,0x0) //
	};
}PE_O26_REG_HDR_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {					//0xCC23210C RW 0x0000_0000
	UINT32 reg_sys_veri_3       :32;//(31:0,RW,0x0000_0000) //
	};
}PE_O26_REG_HDR_VERI_3_T;

typedef union {
	UINT32 udata32;
	struct {					//0xCC232110 RW 0x0000_0000
	UINT32 reg_sys_veri_4       :32;//(31:0,RW,0x0000_0000) //
	};
}PE_O26_REG_HDR_VERI_4_T;

typedef struct {
	PE_O26_REG_HDR_VERI_0_T     hdr0_veri; //0xCC232100
	PE_O26_REG_HDR_VERI_1_T     hdr1_veri; //0xCC232104
	PE_O26_REG_HDR_VERI_2_T     sys_veri_2;//0xCC232108
	PE_O26_REG_HDR_VERI_3_T     sys_veri_3;//0xCC23210C
	PE_O26_REG_HDR_VERI_4_T     sys_veri_4;//0xCC232110
}PE_O26_REG_HDR_VERI_T;

#endif

