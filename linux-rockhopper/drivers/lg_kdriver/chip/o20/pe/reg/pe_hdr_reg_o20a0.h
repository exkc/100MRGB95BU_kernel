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
#ifndef _PE_HDR_REG_O20A0_H_
#define _PE_HDR_REG_O20A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC9003800 RW
	UINT32 load_time                        :1;	//0 //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//1 //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_O20_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003804 RW
	UINT32 width                            :16;	//15:0	//width
	UINT32 height                           :16;	//31:16	//height
	};
}PE_O20_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003808 RW
	UINT32 vdpulse_pos                      :32;	//31:0	//vdpulse position for register loading
	};
}PE_O20_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900380C RO
	UINT32 vcnt                             :16;	//15:0	//vertical line count
	UINT32 vcnt2                            :16;	//31:16	//vertical line number
	};
}PE_O20_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003810 RO
	UINT32 r_to_cnt                         :12;	//11:0	//apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//30 //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//31 //Vertical Active at PE1 output(Read only)
	};
}PE_O20_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003814 RW
	UINT32 reg_hue_sat_prsv_ref             :1;	//0 //0: hue/sat ref source from pcc32 output	1: hue/sat ref source from lg gamma output
	UINT32 resvd0                           :3;
	UINT32 reg_tcm_inp_src                  :1;	//4 //0: Tone Map input source = OETF Out 	1: Tone Map input source = OETF Input
	UINT32 resvd1                           :11;
	UINT32 reg_hue_sat_prsv_src             :2;	//17:16	//(deprecated)
	UINT32 resvd2                           :2;
	UINT32 reg_hist_src                     :4;	//23:20	//1:R, 2:G, 3:B, 4:MAX(RGB)	5:Y, 6:Cb, 7:Cr	8:Technicolor G, 9: Technicolor B, 10 : Technicolor R	11: Technicolor MAX(RGB)	15: MAX(YCbCr) Others: Y
	UINT32 reg_eotf_en                      :1;	//24 //EOTF block enable
	UINT32 reg_oetf_en                      :1;	//25 //OETF block enable
	UINT32 resvd3                           :2;
	UINT32 reg_hdr10p_mode                  :1;	//28 //0: HDR10 Mode	1: HDR10+ Mode
	UINT32 reg_use_equal_llut_en            :1;	//29 //0:use luminanace LUT channel G hif, 	1:use own LUT hif(B/R)(WR only)
	UINT32 reg_hdr10_mode                   :1;	//30 //0: Bypass HDR10 Path	1: Run HDR10
	UINT32 resvd4                           :1;
	};
}PE_O20_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003818 RW
	UINT32 reg_hdr_eotf_120hz_mode          :1;	//0 //1: Nullify all settings about double buffer of EOTF
	UINT32 reg_eotf_same_write_mode         :1;	//1 //1: Write Same LUT Entry in both HDR0/1 EOTF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_eotf_dbuf_mode               :1;	//4 //1: use EOTF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_eotf_dbuf_wptr               :1;	//8 //write pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_eotf_dbuf_rptr               :1;	//12 //read pointer of eotf double buffer (1: use HDR1 EOTF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_eotf_dbuf_ptr_imode          :1;	//16 //1: eotf_rptr = ~ eotf_wptr (ignore [12] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_eotf_ra_mode                 :1;	//24 //1: eotf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O20_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900381C RW
	UINT32 reg_hdr_oetf_120hz_mode          :1;	//0 //1: Nullify all settings about double buffer of OETF
	UINT32 reg_oetf_same_write_mode         :1;	//1 //1: Write Same LUT Entry in both HDR0/1 OETF mem(s)
	UINT32 resvd0                           :2;
	UINT32 reg_oetf_dbuf_mode               :1;	//4 //1: use OETF Double buffer mode
	UINT32 resvd1                           :3;
	UINT32 reg_oetf_dbuf_wptr               :1;	//8 //write pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd2                           :3;
	UINT32 reg_oetf_dbuf_rptr               :1;	//12 //read pointer of eotf double buffer (1: use HDR1 OETF mem)
	UINT32 resvd3                           :3;
	UINT32 reg_oetf_dbuf_ptr_imode          :1;	//16 //1: oetf_rptr = ~ oetf_wptr (ignore [13] bit)
	UINT32 resvd4                           :7;
	UINT32 reg_oetf_ra_mode                 :1;	//24 //1: oetf right access mode
	UINT32 resvd5                           :7;
	};
}PE_O20_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003850 RW
	UINT32 reg_csc1st_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003854 RW
	UINT32 r_csc1st_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003858 RW
	UINT32 r_csc1st_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900385C RW
	UINT32 r_csc1st_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003860 RW
	UINT32 r_csc1st_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003864 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003868 RW
	UINT32 r_csc1st_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900386C RW
	UINT32 r_csc1st_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003870 RW
	UINT32 r_csc1st_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003874 RW
	UINT32 r_csc1st_dbg_en                  :1;	//0:0	//
	UINT32 resvd0                           :3;
	UINT32 r_csc1st_dbg_ugy                 :4;	//7:4	//underflowed bit gy upper 4 bit
	UINT32 r_csc1st_dbg_ucb                 :4;	//11:8	//underflowed bit cb upper 4 bit
	UINT32 r_csc1st_dbg_ucr                 :4;	//15:12	//underflowed bit cr upper 4 bit
	UINT32 resvd1                           :4;
	UINT32 r_csc1st_dbg_ogy                 :4;	//23:20	//overflowed bit gy upper 4 bit
	UINT32 r_csc1st_dbg_ocb                 :4;	//27:24	//overflowed bit cb upper 4 bit
	UINT32 r_csc1st_dbg_ocr                 :4;	//31:28	//overflowed bit cr upper 4 bit
	};
}PE_O20_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003878 RO
	UINT32 ireg_csc_cnt_under               :16;	//15:0	//
	UINT32 ireg_csc_cnt_over                :16;	//31:16	//
	};
}PE_O20_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003880 RW
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//7:0	//
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//15:8	//
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//23:16	//
	UINT32 r_pxl_rd_mark_en                 :1;	//24 //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//28 //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003884 RW
	UINT32 r_pxl_rd_pos_x                   :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003888 RO
	UINT32 pxl_read_rcr                     :10;	//9:0	//
	UINT32 pxl_read_bcb                     :10;	//19:10	//
	UINT32 pxl_read_gyy                     :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_PXL_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003890 RW
	UINT32 lut_addr                         :10;	//9:0	//indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//27 //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//29:28	//0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O20_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003894 RW
	UINT32 eotf_lut_data                    :32;	//31:0	//32 bit LUT data
	};
}PE_O20_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003898 RW
	UINT32 lut_addr                         :10;	//9:0	//indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//27 //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//29:28	//0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_O20_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900389C RW
	UINT32 oetf_lut_data_o                  :16;	//15:0	//16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//31:16	//16 bit even LUT data
	};
}PE_O20_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038A0 RW
	UINT32 reg_pcc_en                       :1;	//0 //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038A4 RW
	UINT32 r_pcc_coef1                      :15;	//14:0	//PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//30:16	//PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038A8 RW
	UINT32 r_pcc_coef3                      :15;	//14:0	//PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//30:16	//PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038AC RW
	UINT32 r_pcc_coef5                      :15;	//14:0	//PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//30:16	//PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038B0 RW
	UINT32 r_pcc_coef7                      :15;	//14:0	//PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//30:16	//PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038B4 RW
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//30:16	//PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038D0 RW
	UINT32 reg_hue_prsv_en                  :1;	//0 //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//1 //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//13:4	//0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//25:16	//0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_O20_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038D4
	UINT32 reg_inp_l_sel                    :1;	//0 //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//4 //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//8 //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//12 //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_O20_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038E0 RW
	UINT32 r_tone_map_rgb2y_coef1           :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038E4 RW
	UINT32 r_tone_map_rgbymax_sel           :3;	//2:0	//
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038E8 RW
	UINT32 ll_lut_addr                      :7;	//6:0	//indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//8 //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//12 //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_O20_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038EC RW
	UINT32 ll_lut_dat_rcr                   :10;	//9:0	//Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//19:10	//Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//29:20	//Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038F0 RW
	UINT32 reg_alpha_hue                    :10;	//9:0	//alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//25:16	//alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//28 //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_O20_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038F4 RW
	UINT32 reg_alpha_ii_yy_coef0            :15;	//14:0	//alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//16 //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_O20_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90038F8 RW
	UINT32 reg_alpha_ii_yy_coef2            :15;	//14:0	//alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//30:16	//alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003900 RW
	UINT32 reg_ll_pcc_en                    :1;	//0 //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003904 RW
	UINT32 r_ll_pcc_coef1                   :15;	//14:0	//PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//30:16	//PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003908 RW
	UINT32 r_ll_pcc_coef3                   :15;	//14:0	//PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//30:16	//PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900390C RW
	UINT32 r_ll_pcc_coef5                   :15;	//14:0	//PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//30:16	//PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003910 RW
	UINT32 r_ll_pcc_coef7                   :15;	//14:0	//PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//30:16	//PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003914 RW
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//30:16	//PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003918 RW
	UINT32 reg_ll_ab_en                     :1;	//0 //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900391C RW
	UINT32 r_ll_ab_lut_x2                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_x1                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_x0                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003920 RW
	UINT32 r_ll_ab_lut_x5                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_x4                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_x3                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003924 RW
	UINT32 r_ll_ab_lut_y2                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_y1                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_y0                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003928 RW
	UINT32 r_ll_ab_lut_y5                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_y4                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_y3                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003970 RW
	UINT32 tpg_enable                       :1;	//0 //Test Pattern Gen. enable
	UINT32 tpg_type                         :2;	//2:1	//0: Patch 1: Gradient 2: CMYW 3: RGBW
	UINT32 tpg_cg_disable                   :1;	//3 //clock gating disable
	UINT32 tpg_blend_alpha                  :4;	//7:4	//0: Solid ~ 15 : Background
	UINT32 tpg_grad_en                      :4;	//11:8	//1: update window from CTRL_01~CTRL04
	UINT32 tpg_h_grad                       :1;	//12 //1: window mode enable
	UINT32 resvd0                           :3;
	UINT32 tpg_stride                       :7;	//22:16	//0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :9;
	};
}PE_O20_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003974 RW
	UINT32 tpg_size_x                       :14;	//13:0	//tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//28:16	//tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003978 RW
	UINT32 tpg_mask_flag                    :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900397C RW
	UINT32 tpg_in_out_sel                   :16;	//15:0	//in_out_sel
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003980 RW
	UINT32 tpg_color_r                      :10;	//9:0	//tpg_color_r
	UINT32 tpg_color_b                      :10;	//19:10	//tpg_color_b
	UINT32 tpg_color_g                      :10;	//29:20	//tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003984 RW
	UINT32 hif_tpg_address                  :8;	//7:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//12 //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003988 RW
	UINT32 hif_tpg_wdata_y                  :16;	//15:0	//Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003990 RW
	UINT32 reg_clut_65th_data               :11;	//10:0	//65th_data
	UINT32 resvd                            :21;
	};
}PE_O20_REG_H10_CLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003994 RW
	UINT32 clut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 clut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 clut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_O20_REG_H10_CLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003998 RW
	UINT32 clut_data                        :11;	//10:0	//data for CLUT
	UINT32 resvd                            :21;
	};
}PE_O20_REG_H10_CLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC900399C RW
	UINT32 reg_plut_65th_data               :14;	//13:0	//65th_data
	UINT32 resvd                            :18;
	};
}PE_O20_REG_H10_PLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039A0 RW
	UINT32 plut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 plut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 plut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_O20_REG_H10_PLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039A4 RW
	UINT32 plut_data                        :14;	//13:0	//data for PLUT
	UINT32 resvd                            :18;
	};
}PE_O20_REG_H10_PLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039A8 RW
	UINT32 reg_slut_65th_data               :10;	//9:0	//65th_data
	UINT32 resvd                            :22;
	};
}PE_O20_REG_H10_SLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039AC RW
	UINT32 slut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 slut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 slut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_O20_REG_H10_SLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039B0 RW
	UINT32 slut_data                        :10;	//9:0	//data for SLUT
	UINT32 resvd                            :22;
	};
}PE_O20_REG_H10_SLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039B4 RW
	UINT32 reg_ilut_65th_data               :8;	//7:0	//65th_data
	UINT32 resvd                            :24;
	};
}PE_O20_REG_H10_ILUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039B8 RW
	UINT32 ilut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 ilut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 ilut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_O20_REG_H10_ILUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039BC RW
	UINT32 ilut_data                        :8;	//7:0	//data for ILUT
	UINT32 resvd                            :24;
	};
}PE_O20_REG_H10_ILUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039C0 RW
	UINT32 reg_dlut_65th_data               :12;	//11:0	//65th_data
	UINT32 resvd0                           :4;
	UINT32 reg_dlut_threshold_0             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039C4 RW
	UINT32 reg_dlut_threshold_1             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_dlut_threshold_2             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039C8 RW
	UINT32 reg_dlut_step_0                  :4;	//3:0	//
	UINT32 reg_dlut_step_1                  :4;	//7:4	//
	UINT32 reg_dlut_step_2                  :4;	//11:8	//
	UINT32 reg_dlut_step_3                  :4;	//15:12	//
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039CC RW
	UINT32 dlut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 dlut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 dlut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_O20_REG_H10_DLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039D0 RW
	UINT32 dlut_data                        :8;	//7:0	//data for DLUT
	UINT32 resvd                            :24;
	};
}PE_O20_REG_H10_DLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039D4 RW
	UINT32 reg_technicolor_detour_en        :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_range_sel                    :1;	//4 //0':limited range, '1':full range
	UINT32 resvd1                           :27;
	};
}PE_O20_REG_H10_TC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039D8 RW
	UINT32 reg_alpha_a                      :13;	//12:0	//default value : 7936
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_b                      :13;	//28:16	//default value : 7680
	UINT32 resvd1                           :3;
	};
}PE_O20_REG_H10_TC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039DC RW
	UINT32 reg_oct_0                        :6;	//5:0	//unsigned 6 bit
	UINT32 resvd0                           :4;
	UINT32 reg_oct_1                        :8;	//17:10	//signed 8 bit
	UINT32 resvd1                           :2;
	UINT32 reg_oct_2                        :9;	//28:20	//signed 9 bit
	UINT32 resvd2                           :3;
	};
}PE_O20_REG_H10_TC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039E0 RW
	UINT32 reg_oct_3                        :10;	//9:0	//signed 10 bit
	UINT32 reg_oct_4                        :10;	//19:10	//signed 10 bit
	UINT32 reg_oct_5                        :10;	//29:20	//signed 10 bit
	UINT32 resvd                            :2;
	};
}PE_O20_REG_H10_TC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90039E4 RW
	UINT32 reg_oct_6                        :10;	//9:0	//signed 10 bit
	UINT32 resvd                            :22;
	};
}PE_O20_REG_H10_TC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A30 RW
	UINT32 hist_bin_mode                    :2;	//1:0	//"00" : 32 bin mode	others : 16 bin mode
	UINT32 histogram_mode                   :2;	//3:2	//"00" : Own side's histogram data use	"01" : Other side's histogram data use	"10" : Average between Own and Other side's histogram data use
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd0                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :6;
	UINT32 hist_clear                       :1;	//23 //1: clear(Debugging purpose, reset histogram memory)
	UINT32 resvd2                           :8;
	};
}PE_O20_REG_H10_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A34 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_H10_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A38 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_H10_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A3C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_H10_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A40 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_H10_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A44 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	"1'   : 1st bin	?	"31" : 31st bin
	UINT32 resvd0                           :7;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//18:16	//"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//28 //auto increment enable
	UINT32 hif_mask                         :1;	//29 //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_O20_REG_H10_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A48 RW
	UINT32 hist_status0                     :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_O20_REG_H10_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A4C RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O20_REG_H10_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A50 RW
	UINT32 luminance_lut0_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A54 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A58 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A5C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A60 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A64 RW
	UINT32 hif_llut0_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
}PE_O20_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A68 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A70 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A74 RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A80 RW
	UINT32 luminance_lut1_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A84 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A88 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A8C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A90 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A94 RW
	UINT32 hif_llut1_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
}PE_O20_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003A98 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AA0 RW
	UINT32 hif_llut1_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AA4 RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AB0 RW
	UINT32 luminance_lut2_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AB4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AB8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003ABC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AC0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AC4 RW
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_O20_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AC8 RW
	UINT32 hif_llut2_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AD0 RW
	UINT32 hif_llut2_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut2_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut2_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut2_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut2_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut2_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut2_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AD4 RW
	UINT32 hif_llut2_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AE0 RW
	UINT32 gamma045_enable                  :1;	//0 //gamma 0.45(1/2.2) enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AE8 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O20_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003AEC RW
	UINT32 hif_pcc32_ygain_shift            :1;	//0 //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B00 RW
	UINT32 reg_3d_lut_out_g_mux             :2;	//1:0	//0: B, 1: G, 2: R
	UINT32 resvd0                           :2;
	UINT32 reg_3d_lut_out_b_mux             :2;	//5:4	//0: B, 1: G, 2: R
	UINT32 resvd1                           :2;
	UINT32 reg_3d_lut_out_r_mux             :2;	//9:8	//0: B, 1: G, 2: R
	UINT32 resvd2                           :2;
	UINT32 reg_3d_lut_in_b_mux              :2;	//13:12	//0: R, 1: G, 2: B
	UINT32 resvd3                           :2;
	UINT32 reg_3d_lut_in_g_mux              :2;	//17:16	//0: R, 1: G, 2: B
	UINT32 resvd4                           :2;
	UINT32 reg_3d_lut_in_r_mux              :2;	//21:20	//0: R, 1: G, 2: B
	UINT32 resvd5                           :2;
	UINT32 reg_3d_lut_in_gb_lshft           :4;	//27:24	//left shift, 0 ~ 7
	UINT32 reg_3d_lut_input_mux             :2;	//29:28	//0:Hue/Sat preserving out, 1:PCC out, 2:EOTF out 3:dither out
	UINT32 resvd6                           :1;
	UINT32 reg_3d_lut_en                    :1;	//31 //0: disable, 1: enable 3d lut
	};
}PE_O20_REG_H10_3DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B04 RW
	UINT32 reg_3d_lut_th_min0               :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_O20_REG_H10_3DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B08 RW
	UINT32 reg_3d_lut_th_min1               :16;	//15:0	//
	UINT32 reg_3d_lut_th_min2               :16;	//31:16	//
	};
}PE_O20_REG_H10_3DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B0C RW
	UINT32 reg_3d_lut_th_max0               :16;	//15:0	//
	UINT32 reg_3d_lut_th_max1               :16;	//31:16	//
	};
}PE_O20_REG_H10_3DLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B10 RW
	UINT32 reg_3d_lut_diff_maxmin0          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_O20_REG_H10_3DLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B14 RW
	UINT32 reg_3d_lut_diff_maxmin1          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_O20_REG_H10_3DLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B18 RW
	UINT32 reg_3d_lut_diff_maxmin2          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_O20_REG_H10_3DLUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B1C RW
	UINT32 reg_3d_lut_manual_qtt            :21;	//20:0	//
	UINT32 resvd                            :11;
	};
}PE_O20_REG_H10_3DLUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B20 RW
	UINT32 luminance_lut2_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B24 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B28 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B2C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B30 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B34 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//15:0	//Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//31:16	//X coordinate of 33rd control point (Default : 65535)
	};
}PE_O20_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B38 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B3C RW
	UINT32 hif_ygain_lut_wdata_y            :16;	//15:0	//Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B40 RW
	UINT32 reg_rgb2yrd_en                   :1;	//0 //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//30:16	//RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B44 RW
	UINT32 r_rgb2yrd_coef1                  :15;	//14:0	//RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//31:16	//RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_O20_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B48 RW
	UINT32 r_rgb2yrd_ofst0                  :17;	//16:0	//RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O20_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B4C RW
	UINT32 r_rgb2yrd_ofst3                  :17;	//16:0	//RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_O20_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B60 RW
	UINT32 lgain_lut_y0                     :8;	//7:0	//y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//31:16	//x value of LGAIN LUT point 0
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B64 RW
	UINT32 lgain_lut_y1                     :8;	//7:0	//y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//31:16	//x value of LGAIN LUT point 1
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B68 RW
	UINT32 lgain_lut_y2                     :8;	//7:0	//y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//31:16	//x value of LGAIN LUT point 2
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B6C RW
	UINT32 lgain_lut_y3                     :8;	//7:0	//y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//31:16	//x value of LGAIN LUT point 3
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B70 RW
	UINT32 lgain_lut_y4                     :8;	//7:0	//y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//31:16	//x value of LGAIN LUT point 4
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B74 RW
	UINT32 lgain_lut_y5                     :8;	//7:0	//y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//31:16	//x value of LGAIN LUT point 5
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B78 RW
	UINT32 lgain_lut_y6                     :8;	//7:0	//y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//31:16	//x value of LGAIN LUT point 6
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B7C RW
	UINT32 lgain_lut_y7                     :8;	//7:0	//y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//31:16	//x value of LGAIN LUT point 7
	};
}PE_O20_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B80 RW
	UINT32 sgain_lut_y0                     :8;	//7:0	//y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//31:16	//x value of SGAIN LUT point 0
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B84 RW
	UINT32 sgain_lut_y1                     :8;	//7:0	//y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//31:16	//x value of SGAIN LUT point 1
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B88 RW
	UINT32 sgain_lut_y2                     :8;	//7:0	//y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//31:16	//x value of SGAIN LUT point 2
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B8C RW
	UINT32 sgain_lut_y3                     :8;	//7:0	//y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//31:16	//x value of SGAIN LUT point 3
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B90 RW
	UINT32 sgain_lut_y4                     :8;	//7:0	//y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//31:16	//x value of SGAIN LUT point 4
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B94 RW
	UINT32 sgain_lut_y5                     :8;	//7:0	//y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//31:16	//x value of SGAIN LUT point 5
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B98 RW
	UINT32 sgain_lut_y6                     :8;	//7:0	//y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//31:16	//x value of SGAIN LUT point 6
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003B9C RW
	UINT32 sgain_lut_y7                     :8;	//7:0	//y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//31:16	//x value of SGAIN LUT point 7
	};
}PE_O20_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BA0 RW
	UINT32 reg_rgb2yrd_en                   :1;	//0 //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//30:16	//RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BA4 RW
	UINT32 r_rgb2yrd_coef1                  :15;	//14:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//31:16	//RGB -> Y CSC Coefficient 0
	};
}PE_O20_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BA8 RW
	UINT32 r_rgb2yrd_ofst0                  :17;	//16:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O20_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BAC RW
	UINT32 r_rgb2yrd_ofst3                  :17;	//16:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_O20_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BB0 RW
	UINT32 reg_csc3rd_en                    :1;	//0 //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BB4 RW
	UINT32 r_csc3rd_coef1                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BB8 RW
	UINT32 r_csc3rd_coef3                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BBC RW
	UINT32 r_csc3rd_coef5                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BC0 RW
	UINT32 r_csc3rd_coef7                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BC4 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BC8 RW
	UINT32 r_csc3rd_ofst1                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BCC RW
	UINT32 r_csc3rd_ofst3                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003BD0 RW
	UINT32 r_csc3rd_ofst5                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC3_CTRL_08_T;

typedef struct {
	PE_O20_REG_H10_TOP_CTRL_00_T                       hdr_top_ctrl_00;	//0xC9003800
	PE_O20_REG_H10_TOP_CTRL_01_T                       hdr_top_ctrl_01;	//0xC9003804
	PE_O20_REG_H10_TOP_CTRL_02_T                       hdr_top_ctrl_02;	//0xC9003808
	PE_O20_REG_H10_TOP_CTRL_03_T                       hdr_top_ctrl_03;	//0xC900380C
	PE_O20_REG_H10_TOP_CTRL_04_T                       hdr_top_ctrl_04;	//0xC9003810
	PE_O20_REG_H10_TOP_CTRL_05_T                       hdr_top_ctrl_05;	//0xC9003814
	PE_O20_REG_H10_TOP_CTRL_06_T                       hdr_top_ctrl_06;	//0xC9003818
	PE_O20_REG_H10_TOP_CTRL_07_T                       hdr_top_ctrl_07;	//0xC900381C
	UINT32                                                   reserved0;	//0xC9003820
	UINT32                                                   reserved1;	//0xC9003824
	UINT32                                                   reserved2;	//0xC9003828
	UINT32                                                   reserved3;	//0xC900382C
	UINT32                                                   reserved4;	//0xC9003830
	UINT32                                                   reserved5;	//0xC9003834
	UINT32                                                   reserved6;	//0xC9003838
	UINT32                                                   reserved7;	//0xC900383C
	UINT32                                                   reserved8;	//0xC9003840
	UINT32                                                   reserved9;	//0xC9003844
	UINT32                                                  reserved10;	//0xC9003848
	UINT32                                                  reserved11;	//0xC900384C
	PE_O20_REG_H10_CSC1_CTRL_00_T                     hdr_csc1_ctrl_00;	//0xC9003850
	PE_O20_REG_H10_CSC1_CTRL_01_T                     hdr_csc1_ctrl_01;	//0xC9003854
	PE_O20_REG_H10_CSC1_CTRL_02_T                     hdr_csc1_ctrl_02;	//0xC9003858
	PE_O20_REG_H10_CSC1_CTRL_03_T                     hdr_csc1_ctrl_03;	//0xC900385C
	PE_O20_REG_H10_CSC1_CTRL_04_T                     hdr_csc1_ctrl_04;	//0xC9003860
	PE_O20_REG_H10_CSC1_CTRL_05_T                     hdr_csc1_ctrl_05;	//0xC9003864
	PE_O20_REG_H10_CSC1_CTRL_06_T                     hdr_csc1_ctrl_06;	//0xC9003868
	PE_O20_REG_H10_CSC1_CTRL_07_T                     hdr_csc1_ctrl_07;	//0xC900386C
	PE_O20_REG_H10_CSC1_CTRL_08_T                     hdr_csc1_ctrl_08;	//0xC9003870
	PE_O20_REG_H10_CSC1_CTRL_09_T                     hdr_csc1_ctrl_09;	//0xC9003874
	PE_O20_REG_H10_CSC1_ERR_CNT_T                     hdr_csc1_err_cnt;	//0xC9003878
	UINT32                                                  reserved12;	//0xC900387C
	PE_O20_REG_H10_PXL_RD_CTRL0_T                     hdr_pxl_rd_ctrl0;	//0xC9003880
	PE_O20_REG_H10_PXL_RD_CTRL1_T                     hdr_pxl_rd_ctrl1;	//0xC9003884
	PE_O20_REG_H10_PXL_RD_DATA_T                       hdr_pxl_rd_data;	//0xC9003888
	UINT32                                                  reserved13;	//0xC900388C
	PE_O20_REG_H10_EOTF_IA_CTRL_T                     hdr_eotf_ia_ctrl;	//0xC9003890
	PE_O20_REG_H10_EOTF_IA_DATA_T                     hdr_eotf_ia_data;	//0xC9003894
	PE_O20_REG_H10_OETF_IA_CTRL_T                     hdr_oetf_ia_ctrl;	//0xC9003898
	PE_O20_REG_H10_OETF_IA_DATA_T                     hdr_oetf_ia_data;	//0xC900389C
	PE_O20_REG_H10_PCC_CTRL_00_T                       hdr_pcc_ctrl_00;	//0xC90038A0
	PE_O20_REG_H10_PCC_CTRL_01_T                       hdr_pcc_ctrl_01;	//0xC90038A4
	PE_O20_REG_H10_PCC_CTRL_02_T                       hdr_pcc_ctrl_02;	//0xC90038A8
	PE_O20_REG_H10_PCC_CTRL_03_T                       hdr_pcc_ctrl_03;	//0xC90038AC
	PE_O20_REG_H10_PCC_CTRL_04_T                       hdr_pcc_ctrl_04;	//0xC90038B0
	PE_O20_REG_H10_PCC_CTRL_05_T                       hdr_pcc_ctrl_05;	//0xC90038B4
	UINT32                                                  reserved14;	//0xC90038B8
	UINT32                                                  reserved15;	//0xC90038BC
	UINT32                                                  reserved16;	//0xC90038C0
	UINT32                                                  reserved17;	//0xC90038C4
	UINT32                                                  reserved18;	//0xC90038C8
	UINT32                                                  reserved19;	//0xC90038CC
	PE_O20_REG_H10_HUE_SAT_CTRL_T                     hdr_hue_sat_ctrl;	//0xC90038D0
	PE_O20_REG_H10_HUE_SAT_ALPHA_CTRL_T         hdr_hue_sat_alpha_ctrl;	//0xC90038D4
	UINT32                                                  reserved20;	//0xC90038D8
	UINT32                                                  reserved21;	//0xC90038DC
	PE_O20_REG_H10_TCM_PREP_00_T                       hdr_tcm_prep_00;	//0xC90038E0
	PE_O20_REG_H10_TCM_PREP_01_T                       hdr_tcm_prep_01;	//0xC90038E4
	PE_O20_REG_H10_LL_LUT_IA_CTRL_T                 hdr_ll_lut_ia_ctrl;	//0xC90038E8
	PE_O20_REG_H10_LL_LUT_IA_DATA_T                 hdr_ll_lut_ia_data;	//0xC90038EC
	PE_O20_REG_H10_LL_HUE_CTRL_00_T                 hdr_ll_hue_ctrl_00;	//0xC90038F0
	PE_O20_REG_H10_LL_HUE_CTRL_01_T                 hdr_ll_hue_ctrl_01;	//0xC90038F4
	PE_O20_REG_H10_LL_HUE_CTRL_02_T                 hdr_ll_hue_ctrl_02;	//0xC90038F8
	UINT32                                                  reserved22;	//0xC90038FC
	PE_O20_REG_H10_LLPCC_CTRL_00_T                   hdr_llpcc_ctrl_00;	//0xC9003900
	PE_O20_REG_H10_LLPCC_CTRL_01_T                   hdr_llpcc_ctrl_01;	//0xC9003904
	PE_O20_REG_H10_LLPCC_CTRL_02_T                   hdr_llpcc_ctrl_02;	//0xC9003908
	PE_O20_REG_H10_LLPCC_CTRL_03_T                   hdr_llpcc_ctrl_03;	//0xC900390C
	PE_O20_REG_H10_LLPCC_CTRL_04_T                   hdr_llpcc_ctrl_04;	//0xC9003910
	PE_O20_REG_H10_LLPCC_CTRL_05_T                   hdr_llpcc_ctrl_05;	//0xC9003914
	PE_O20_REG_H10_LL_AB_CTRL_00_T                   hdr_ll_ab_ctrl_00;	//0xC9003918
	PE_O20_REG_H10_LL_AB_CTRL_01_T                   hdr_ll_ab_ctrl_01;	//0xC900391C
	PE_O20_REG_H10_LL_AB_CTRL_02_T                   hdr_ll_ab_ctrl_02;	//0xC9003920
	PE_O20_REG_H10_LL_AB_CTRL_03_T                   hdr_ll_ab_ctrl_03;	//0xC9003924
	PE_O20_REG_H10_LL_AB_CTRL_04_T                   hdr_ll_ab_ctrl_04;	//0xC9003928
	UINT32                                                  reserved23;	//0xC900392C
	UINT32                                                  reserved24;	//0xC9003930
	UINT32                                                  reserved25;	//0xC9003934
	UINT32                                                  reserved26;	//0xC9003938
	UINT32                                                  reserved27;	//0xC900393C
	UINT32                                                  reserved28;	//0xC9003940
	UINT32                                                  reserved29;	//0xC9003944
	UINT32                                                  reserved30;	//0xC9003948
	UINT32                                                  reserved31;	//0xC900394C
	UINT32                                                  reserved32;	//0xC9003950
	UINT32                                                  reserved33;	//0xC9003954
	UINT32                                                  reserved34;	//0xC9003958
	UINT32                                                  reserved35;	//0xC900395C
	UINT32                                                  reserved36;	//0xC9003960
	UINT32                                                  reserved37;	//0xC9003964
	UINT32                                                  reserved38;	//0xC9003968
	UINT32                                                  reserved39;	//0xC900396C
	PE_O20_REG_H10_TPG_CTRL_00_T                       hdr_tpg_ctrl_00;	//0xC9003970
	PE_O20_REG_H10_TPG_CTRL_01_T                       hdr_tpg_ctrl_01;	//0xC9003974
	PE_O20_REG_H10_TPG_CTRL_02_T                       hdr_tpg_ctrl_02;	//0xC9003978
	PE_O20_REG_H10_TPG_CTRL_03_T                       hdr_tpg_ctrl_03;	//0xC900397C
	PE_O20_REG_H10_TPG_CTRL_04_T                       hdr_tpg_ctrl_04;	//0xC9003980
	PE_O20_REG_H10_TPG_IA_CTRL_T                       hdr_tpg_ia_ctrl;	//0xC9003984
	PE_O20_REG_H10_TPG_IA_DATA_T                       hdr_tpg_ia_data;	//0xC9003988
	UINT32                                                  reserved40;	//0xC900398C
	PE_O20_REG_H10_CLUT_CTRL_00_T                     hdr_clut_ctrl_00;	//0xC9003990
	PE_O20_REG_H10_CLUT_IA_CTRL_T                     hdr_clut_ia_ctrl;	//0xC9003994
	PE_O20_REG_H10_CLUT_IA_DATA_T                     hdr_clut_ia_data;	//0xC9003998
	PE_O20_REG_H10_PLUT_CTRL_00_T                     hdr_plut_ctrl_00;	//0xC900399C
	PE_O20_REG_H10_PLUT_IA_CTRL_T                     hdr_plut_ia_ctrl;	//0xC90039A0
	PE_O20_REG_H10_PLUT_IA_DATA_T                     hdr_plut_ia_data;	//0xC90039A4
	PE_O20_REG_H10_SLUT_CTRL_00_T                     hdr_slut_ctrl_00;	//0xC90039A8
	PE_O20_REG_H10_SLUT_IA_CTRL_T                     hdr_slut_ia_ctrl;	//0xC90039AC
	PE_O20_REG_H10_SLUT_IA_DATA_T                     hdr_slut_ia_data;	//0xC90039B0
	PE_O20_REG_H10_ILUT_CTRL_00_T                     hdr_ilut_ctrl_00;	//0xC90039B4
	PE_O20_REG_H10_ILUT_IA_CTRL_T                     hdr_ilut_ia_ctrl;	//0xC90039B8
	PE_O20_REG_H10_ILUT_IA_DATA_T                     hdr_ilut_ia_data;	//0xC90039BC
	PE_O20_REG_H10_DLUT_CTRL_00_T                     hdr_dlut_ctrl_00;	//0xC90039C0
	PE_O20_REG_H10_DLUT_CTRL_01_T                     hdr_dlut_ctrl_01;	//0xC90039C4
	PE_O20_REG_H10_DLUT_CTRL_02_T                     hdr_dlut_ctrl_02;	//0xC90039C8
	PE_O20_REG_H10_DLUT_IA_CTRL_T                     hdr_dlut_ia_ctrl;	//0xC90039CC
	PE_O20_REG_H10_DLUT_IA_DATA_T                     hdr_dlut_ia_data;	//0xC90039D0
	PE_O20_REG_H10_TC_CTRL_00_T                         hdr_tc_ctrl_00;	//0xC90039D4
	PE_O20_REG_H10_TC_CTRL_01_T                         hdr_tc_ctrl_01;	//0xC90039D8
	PE_O20_REG_H10_TC_CTRL_02_T                         hdr_tc_ctrl_02;	//0xC90039DC
	PE_O20_REG_H10_TC_CTRL_03_T                         hdr_tc_ctrl_03;	//0xC90039E0
	PE_O20_REG_H10_TC_CTRL_04_T                         hdr_tc_ctrl_04;	//0xC90039E4
	UINT32                                                  reserved41;	//0xC90039E8
	UINT32                                                  reserved42;	//0xC90039EC
	UINT32                                                  reserved43;	//0xC90039F0
	UINT32                                                  reserved44;	//0xC90039F4
	UINT32                                                  reserved45;	//0xC90039F8
	UINT32                                                  reserved46;	//0xC90039FC
	UINT32                                                  reserved47;	//0xC9003A00
	UINT32                                                  reserved48;	//0xC9003A04
	UINT32                                                  reserved49;	//0xC9003A08
	UINT32                                                  reserved50;	//0xC9003A0C
	UINT32                                                  reserved51;	//0xC9003A10
	UINT32                                                  reserved52;	//0xC9003A14
	UINT32                                                  reserved53;	//0xC9003A18
	UINT32                                                  reserved54;	//0xC9003A1C
	UINT32                                                  reserved55;	//0xC9003A20
	UINT32                                                  reserved56;	//0xC9003A24
	UINT32                                                  reserved57;	//0xC9003A28
	UINT32                                                  reserved58;	//0xC9003A2C
	PE_O20_REG_H10_HIST_CTRL_00_T                     hdr_hist_ctrl_00;	//0xC9003A30
	PE_O20_REG_H10_HIST_CTRL_01_T                     hdr_hist_ctrl_01;	//0xC9003A34
	PE_O20_REG_H10_HIST_CTRL_02_T                     hdr_hist_ctrl_02;	//0xC9003A38
	PE_O20_REG_H10_HIST_CTRL_03_T                     hdr_hist_ctrl_03;	//0xC9003A3C
	PE_O20_REG_H10_HIST_CTRL_04_T                     hdr_hist_ctrl_04;	//0xC9003A40
	PE_O20_REG_H10_HIST_IA_CTRL_T                     hdr_hist_ia_ctrl;	//0xC9003A44
	PE_O20_REG_H10_HIST_IA_DATA1_T                   hdr_hist_ia_data1;	//0xC9003A48
	PE_O20_REG_H10_HIST_IA_DATA2_T                   hdr_hist_ia_data2;	//0xC9003A4C
	PE_O20_REG_H10_LLUT0_CTRL_00_T                   hdr_llut0_ctrl_00;	//0xC9003A50
	PE_O20_REG_H10_LLUT0_CTRL_01_T                   hdr_llut0_ctrl_01;	//0xC9003A54
	PE_O20_REG_H10_LLUT0_CTRL_02_T                   hdr_llut0_ctrl_02;	//0xC9003A58
	PE_O20_REG_H10_LLUT0_CTRL_03_T                   hdr_llut0_ctrl_03;	//0xC9003A5C
	PE_O20_REG_H10_LLUT0_CTRL_04_T                   hdr_llut0_ctrl_04;	//0xC9003A60
	PE_O20_REG_H10_LLUT0_CTRL_05_T                   hdr_llut0_ctrl_05;	//0xC9003A64
	PE_O20_REG_H10_LLUT0_CTRL_06_T                   hdr_llut0_ctrl_06;	//0xC9003A68
	UINT32                                                  reserved59;	//0xC9003A6C
	PE_O20_REG_H10_LLUT0_IA_CTRL_T                   hdr_llut0_ia_ctrl;	//0xC9003A70
	PE_O20_REG_H10_LLUT0_IA_DATA_T                   hdr_llut0_ia_data;	//0xC9003A74
	UINT32                                                  reserved60;	//0xC9003A78
	UINT32                                                  reserved61;	//0xC9003A7C
	PE_O20_REG_H10_LLUT1_CTRL_00_T                   hdr_llut1_ctrl_00;	//0xC9003A80
	PE_O20_REG_H10_LLUT1_CTRL_01_T                   hdr_llut1_ctrl_01;	//0xC9003A84
	PE_O20_REG_H10_LLUT1_CTRL_02_T                   hdr_llut1_ctrl_02;	//0xC9003A88
	PE_O20_REG_H10_LLUT1_CTRL_03_T                   hdr_llut1_ctrl_03;	//0xC9003A8C
	PE_O20_REG_H10_LLUT1_CTRL_04_T                   hdr_llut1_ctrl_04;	//0xC9003A90
	PE_O20_REG_H10_LLUT1_CTRL_05_T                   hdr_llut1_ctrl_05;	//0xC9003A94
	PE_O20_REG_H10_LLUT1_CTRL_06_T                   hdr_llut1_ctrl_06;	//0xC9003A98
	UINT32                                                  reserved62;	//0xC9003A9C
	PE_O20_REG_H10_LLUT1_IA_CTRL_T                   hdr_llut1_ia_ctrl;	//0xC9003AA0
	PE_O20_REG_H10_LLUT1_IA_DATA_T                   hdr_llut1_ia_data;	//0xC9003AA4
	UINT32                                                  reserved63;	//0xC9003AA8
	UINT32                                                  reserved64;	//0xC9003AAC
	PE_O20_REG_H10_LLUT2_CTRL_00_T                   hdr_llut2_ctrl_00;	//0xC9003AB0
	PE_O20_REG_H10_LLUT2_CTRL_01_T                   hdr_llut2_ctrl_01;	//0xC9003AB4
	PE_O20_REG_H10_LLUT2_CTRL_02_T                   hdr_llut2_ctrl_02;	//0xC9003AB8
	PE_O20_REG_H10_LLUT2_CTRL_03_T                   hdr_llut2_ctrl_03;	//0xC9003ABC
	PE_O20_REG_H10_LLUT2_CTRL_04_T                   hdr_llut2_ctrl_04;	//0xC9003AC0
	PE_O20_REG_H10_LLUT2_CTRL_05_T                   hdr_llut2_ctrl_05;	//0xC9003AC4
	PE_O20_REG_H10_LLUT2_CTRL_06_T                   hdr_llut2_ctrl_06;	//0xC9003AC8
	UINT32                                                  reserved65;	//0xC9003ACC
	PE_O20_REG_H10_LLUT2_IA_CTRL_T                   hdr_llut2_ia_ctrl;	//0xC9003AD0
	PE_O20_REG_H10_LLUT2_IA_DATA_T                   hdr_llut2_ia_data;	//0xC9003AD4
	UINT32                                                  reserved66;	//0xC9003AD8
	UINT32                                                  reserved67;	//0xC9003ADC
	PE_O20_REG_H10_GAMMA045_CTRL_00_T             hdr_gamma045_ctrl_00;	//0xC9003AE0
	UINT32                                                  reserved68;	//0xC9003AE4
	PE_O20_REG_H10_DITHER_CTRL_00_T                 hdr_dither_ctrl_00;	//0xC9003AE8
	PE_O20_REG_H10_PCC32_GAIN_CTRL_T               hdr_pcc32_gain_ctrl;	//0xC9003AEC
	UINT32                                                  reserved69;	//0xC9003AF0
	UINT32                                                  reserved70;	//0xC9003AF4
	UINT32                                                  reserved71;	//0xC9003AF8
	UINT32                                                  reserved72;	//0xC9003AFC
	PE_O20_REG_H10_3DLUT_CTRL_00_T                   hdr_3dlut_ctrl_00;	//0xC9003B00
	PE_O20_REG_H10_3DLUT_CTRL_01_T                   hdr_3dlut_ctrl_01;	//0xC9003B04
	PE_O20_REG_H10_3DLUT_CTRL_02_T                   hdr_3dlut_ctrl_02;	//0xC9003B08
	PE_O20_REG_H10_3DLUT_CTRL_03_T                   hdr_3dlut_ctrl_03;	//0xC9003B0C
	PE_O20_REG_H10_3DLUT_CTRL_04_T                   hdr_3dlut_ctrl_04;	//0xC9003B10
	PE_O20_REG_H10_3DLUT_CTRL_05_T                   hdr_3dlut_ctrl_05;	//0xC9003B14
	PE_O20_REG_H10_3DLUT_CTRL_06_T                   hdr_3dlut_ctrl_06;	//0xC9003B18
	PE_O20_REG_H10_3DLUT_CTRL_07_T                   hdr_3dlut_ctrl_07;	//0xC9003B1C
	PE_O20_REG_H10_YGAIN_LUT_CTRL_00_T           hdr_ygain_lut_ctrl_00;	//0xC9003B20
	PE_O20_REG_H10_YGAIN_LUT_CTRL_01_T           hdr_ygain_lut_ctrl_01;	//0xC9003B24
	PE_O20_REG_H10_YGAIN_LUT_CTRL_02_T           hdr_ygain_lut_ctrl_02;	//0xC9003B28
	PE_O20_REG_H10_YGAIN_LUT_CTRL_03_T           hdr_ygain_lut_ctrl_03;	//0xC9003B2C
	PE_O20_REG_H10_YGAIN_LUT_CTRL_04_T           hdr_ygain_lut_ctrl_04;	//0xC9003B30
	PE_O20_REG_H10_YGAIN_LUT_CTRL_05_T           hdr_ygain_lut_ctrl_05;	//0xC9003B34
	PE_O20_REG_H10_YGAIN_LUT_IA_CTRL_T           hdr_ygain_lut_ia_ctrl;	//0xC9003B38
	PE_O20_REG_H10_YGAIN_LUT_IA_DATA_T           hdr_ygain_lut_ia_data;	//0xC9003B3C
	PE_O20_REG_H10_RGB2Y_CTRL_00_T                   hdr_rgb2y_ctrl_00;	//0xC9003B40
	PE_O20_REG_H10_RGB2Y_CTRL_01_T                   hdr_rgb2y_ctrl_01;	//0xC9003B44
	PE_O20_REG_H10_RGB2Y_CTRL_02_T                   hdr_rgb2y_ctrl_02;	//0xC9003B48
	PE_O20_REG_H10_RGB2Y_CTRL_03_T                   hdr_rgb2y_ctrl_03;	//0xC9003B4C
	UINT32                                                  reserved73;	//0xC9003B50
	UINT32                                                  reserved74;	//0xC9003B54
	UINT32                                                  reserved75;	//0xC9003B58
	UINT32                                                  reserved76;	//0xC9003B5C
	PE_O20_REG_H10_LGAIN_LUT_CTRL_00_T           hdr_lgain_lut_ctrl_00;	//0xC9003B60
	PE_O20_REG_H10_LGAIN_LUT_CTRL_01_T           hdr_lgain_lut_ctrl_01;	//0xC9003B64
	PE_O20_REG_H10_LGAIN_LUT_CTRL_02_T           hdr_lgain_lut_ctrl_02;	//0xC9003B68
	PE_O20_REG_H10_LGAIN_LUT_CTRL_03_T           hdr_lgain_lut_ctrl_03;	//0xC9003B6C
	PE_O20_REG_H10_LGAIN_LUT_CTRL_04_T           hdr_lgain_lut_ctrl_04;	//0xC9003B70
	PE_O20_REG_H10_LGAIN_LUT_CTRL_05_T           hdr_lgain_lut_ctrl_05;	//0xC9003B74
	PE_O20_REG_H10_LGAIN_LUT_CTRL_06_T           hdr_lgain_lut_ctrl_06;	//0xC9003B78
	PE_O20_REG_H10_LGAIN_LUT_CTRL_07_T           hdr_lgain_lut_ctrl_07;	//0xC9003B7C
	PE_O20_REG_H10_SGAIN_LUT_CTRL_00_T           hdr_sgain_lut_ctrl_00;	//0xC9003B80
	PE_O20_REG_H10_SGAIN_LUT_CTRL_01_T           hdr_sgain_lut_ctrl_01;	//0xC9003B84
	PE_O20_REG_H10_SGAIN_LUT_CTRL_02_T           hdr_sgain_lut_ctrl_02;	//0xC9003B88
	PE_O20_REG_H10_SGAIN_LUT_CTRL_03_T           hdr_sgain_lut_ctrl_03;	//0xC9003B8C
	PE_O20_REG_H10_SGAIN_LUT_CTRL_04_T           hdr_sgain_lut_ctrl_04;	//0xC9003B90
	PE_O20_REG_H10_SGAIN_LUT_CTRL_05_T           hdr_sgain_lut_ctrl_05;	//0xC9003B94
	PE_O20_REG_H10_SGAIN_LUT_CTRL_06_T           hdr_sgain_lut_ctrl_06;	//0xC9003B98
	PE_O20_REG_H10_SGAIN_LUT_CTRL_07_T           hdr_sgain_lut_ctrl_07;	//0xC9003B9C
	PE_O20_REG_H10_RGB2Y2_CTRL_00_T                 hdr_rgb2y2_ctrl_00;	//0xC9003BA0
	PE_O20_REG_H10_RGB2Y2_CTRL_01_T                 hdr_rgb2y2_ctrl_01;	//0xC9003BA4
	PE_O20_REG_H10_RGB2Y2_CTRL_02_T                 hdr_rgb2y2_ctrl_02;	//0xC9003BA8
	PE_O20_REG_H10_RGB2Y2_CTRL_03_T                 hdr_rgb2y2_ctrl_03;	//0xC9003BAC
	PE_O20_REG_H10_CSC3_CTRL_00_T                     hdr_csc3_ctrl_00;	//0xC9003BB0
	PE_O20_REG_H10_CSC3_CTRL_01_T                     hdr_csc3_ctrl_01;	//0xC9003BB4
	PE_O20_REG_H10_CSC3_CTRL_02_T                     hdr_csc3_ctrl_02;	//0xC9003BB8
	PE_O20_REG_H10_CSC3_CTRL_03_T                     hdr_csc3_ctrl_03;	//0xC9003BBC
	PE_O20_REG_H10_CSC3_CTRL_04_T                     hdr_csc3_ctrl_04;	//0xC9003BC0
	PE_O20_REG_H10_CSC3_CTRL_05_T                     hdr_csc3_ctrl_05;	//0xC9003BC4
	PE_O20_REG_H10_CSC3_CTRL_06_T                     hdr_csc3_ctrl_06;	//0xC9003BC8
	PE_O20_REG_H10_CSC3_CTRL_07_T                     hdr_csc3_ctrl_07;	//0xC9003BCC
	PE_O20_REG_H10_CSC3_CTRL_08_T                     hdr_csc3_ctrl_08;	//0xC9003BD0
}PE_O20_REG_H10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E00 RW
	UINT32 r_tcm_org_sel                    :1;	//0:0	//
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_TCM_HDR10P_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E04 RW
	UINT32 r_slut0_x0                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E08 RW
	UINT32 r_slut0_x1                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E0C RW
	UINT32 r_slut0_x2                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E10 RW
	UINT32 r_slut0_x3                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E14 RW
	UINT32 r_slut0_x4                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E18 RW
	UINT32 r_slut0_x5                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E1C RW
	UINT32 r_slut0_x6                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E20 RW
	UINT32 r_slut0_x7                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E24 RW
	UINT32 r_slut0_y0                       :8;	//7:0	//
	UINT32 r_slut0_y1                       :8;	//15:8	//
	UINT32 r_slut0_y2                       :8;	//23:16	//
	UINT32 r_slut0_y3                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E28 RW
	UINT32 r_slut0_y4                       :8;	//7:0	//
	UINT32 r_slut0_y5                       :8;	//15:8	//
	UINT32 r_slut0_y6                       :8;	//23:16	//
	UINT32 r_slut0_y7                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E2C RW
	UINT32 r_slut1_x0                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E30 RW
	UINT32 r_slut1_x1                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E34 RW
	UINT32 r_slut1_x2                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E38 RW
	UINT32 r_slut1_x3                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E3C RW
	UINT32 r_slut1_x4                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E40 RW
	UINT32 r_slut1_x5                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E44 RW
	UINT32 r_slut1_x6                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E48 RW
	UINT32 r_slut1_x7                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT1_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E4C RW
	UINT32 r_slut1_y0                       :8;	//7:0	//
	UINT32 r_slut1_y1                       :8;	//15:8	//
	UINT32 r_slut1_y2                       :8;	//23:16	//
	UINT32 r_slut1_y3                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT1_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E50 RW
	UINT32 r_slut1_y4                       :8;	//7:0	//
	UINT32 r_slut1_y5                       :8;	//15:8	//
	UINT32 r_slut1_y6                       :8;	//23:16	//
	UINT32 r_slut1_y7                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT1_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E54 RW
	UINT32 r_slut2_x0                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E58 RW
	UINT32 r_slut2_x1                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E5C RW
	UINT32 r_slut2_x2                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E60 RW
	UINT32 r_slut2_x3                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E64 RW
	UINT32 r_slut2_x4                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E68 RW
	UINT32 r_slut2_x5                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E6C RW
	UINT32 r_slut2_x6                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E70 RW
	UINT32 r_slut2_x7                       :32;	//31:00	//
	};
}PE_O20_REG_H10_TCM_SLUT2_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E74 RW
	UINT32 r_slut2_y0                       :8;	//7:0	//
	UINT32 r_slut2_y1                       :8;	//15:8	//
	UINT32 r_slut2_y2                       :8;	//23:16	//
	UINT32 r_slut2_y3                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT2_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E78 RW
	UINT32 r_slut2_y4                       :8;	//7:0	//
	UINT32 r_slut2_y5                       :8;	//15:8	//
	UINT32 r_slut2_y6                       :8;	//23:16	//
	UINT32 r_slut2_y7                       :8;	//31:24	//
	};
}PE_O20_REG_H10_TCM_SLUT2_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E7C RW
	UINT32 tm1_dither_en                    :1;	//0 //TM1 enable dither
	UINT32 resvd0                           :1;
	UINT32 tm1_dither_random_freeze_en      :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 tm1_demo_pattern_enable          :1;	//3 //gradation pattern enable for demo
	UINT32 tm1_bit_mode                     :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :1;
	UINT32 tm1_gamma_en                     :1;	//7 //TM1 tone mapping gamma enable
	UINT32 resvd2                           :8;
	UINT32 tm2_dither_en                    :1;	//16 //TM2 enable dither
	UINT32 resvd3                           :1;
	UINT32 tm2_dither_random_freeze_en      :1;	//18 //1' : freeze random number	'0' : use random number
	UINT32 tm2_demo_pattern_enable          :1;	//19 //gradation pattern enable for demo
	UINT32 tm2_bit_mode                     :2;	//21:20	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd4                           :1;
	UINT32 tm2_gamma_en                     :1;	//23 //TM2 tone mapping gamma enable
	UINT32 win0_sat_gain_en                 :1;	//24 //TM0 Saturation Gain Enable
	UINT32 win1_sat_gain_en                 :1;	//25 //TM1 Saturation Gain Enable
	UINT32 win2_sat_gain_en                 :1;	//26 //TM2 Saturation Gain Enable
	UINT32 resvd5                           :1;
	UINT32 reg_win01_blend_en               :1;	//28 //Saturation Mapping Alpha Blend Enable (Win0 + Win1)
	UINT32 reg_win012_blend_en              :1;	//29 //Saturation Mapping Alpha Blend Enable (Win01 + Win2)
	UINT32 reg_win01_alpha_view_en          :1;	//30 //Saturation Mapping Alpha View Enable (Win0 + Win1)
	UINT32 reg_win012_alpha_view_en         :1;	//31 //Saturation Mapping Alpha View Enable (Win01 + Win2)
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E80 RW
	UINT32 reg_tm0_m2020_coef13             :15;	//14:0	//TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm0_m2020_coef22             :15;	//30:16	//TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E84 RW
	UINT32 reg_tm0_m2020_coef23             :15;	//14:0	//TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm0_m2020_coef32             :15;	//30:16	//TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E88 RW
	UINT32 reg_tm1_m2020_coef13             :15;	//14:0	//TM1 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm1_m2020_coef22             :15;	//30:16	//TM1 M2020 Coef 3x3 matrix (2,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E8C RW
	UINT32 reg_tm1_m2020_coef23             :15;	//14:0	//TM1 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm1_m2020_coef32             :15;	//30:16	//TM1 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E90 RW
	UINT32 reg_tm2_m2020_coef13             :15;	//14:0	//TM2 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm2_m2020_coef22             :15;	//30:16	//TM2 M2020 Coef 3x3 matrix (2,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003E94 RW
	UINT32 reg_tm2_m2020_coef23             :15;	//14:0	//TM2 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm2_m2020_coef32             :15;	//30:16	//TM2 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_SAT_MAP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EC0 RW
	UINT32 reg_ellipse_w1_y0                :16;	//15:0	//Ellipse Window 1 y0 (y for upper left)
	UINT32 reg_ellipse_w1_x0                :16;	//31:16	//Ellipse Window 1 x0 (x for upper left)
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EC4 RW
	UINT32 reg_ellipse_w1_y1                :16;	//15:0	//Ellipse Window 1 y1 (y for lower right)
	UINT32 reg_ellipse_w1_x1                :16;	//31:16	//Ellipse Window 1 x1 (x for lower right)
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EC8 RW
	UINT32 reg_ellipse_w2_y0                :16;	//15:0	//Ellipse Window 2 y0 (y for upper left)
	UINT32 reg_ellipse_w2_x0                :16;	//31:16	//Ellipse Window 2 x0 (x for upper left)
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003ECC RW
	UINT32 reg_ellipse_w2_y1                :16;	//15:0	//Ellipse Window 2 y1 (y for lower right)
	UINT32 reg_ellipse_w2_x1                :16;	//31:16	//Ellipse Window 2 x1 (x for lower right)
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003ED0 RW
	UINT32 reg_ellipse_w1_center_y          :16;	//15:0	//Ellipse Window 1 Center y position
	UINT32 reg_ellipse_w1_center_x          :16;	//31:16	//Ellipse Window 1 Center x position
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003ED4 RW
	UINT32 reg_ellipse_axis_internal        :16;	//15:0	//Ellipse Window 1 Semimajor Axis of internal Ellipse
	UINT32 reg_ellipse_w1_rotation_angle    :8;	//23:16	//Ellipse Window 1 rotation angle
	UINT32 reg_ellipse_w1_mode              :1;	//24 //Ellipse Window 1 mode ( 0: Rectangle / 1 : Ellipse)
	UINT32 resvd                            :7;
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003ED8 RW
	UINT32 reg_ellipse_w1_axis_ext_semiminor :16;	//15:0	//Ellipse Window 1 Semiminor Axis of external Ellipse
	UINT32 reg_ellipse_w1_axis_ext_semimajor :16;	//31:16	//Ellipse Window 1 Semimajor Axis of external Ellipse
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EDC RW
	UINT32 reg_ellipse_w2_center_y          :16;	//15:0	//Ellipse Window 2 Center y position
	UINT32 reg_ellipse_w2_center_x          :16;	//31:16	//Ellipse Window 2 Center x position
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EE0 RW
	UINT32 reg_ellipse_axis_internal        :16;	//15:0	//Ellipse Window 2 Semimajor Axis of internal Ellipse
	UINT32 reg_ellipse_w2_rotation_angle    :8;	//23:16	//Ellipse Window 2 rotation angle
	UINT32 reg_ellipse_w2_mode              :1;	//24 //Ellipse Window 2 mode ( 0: Rectangle / 1 : Ellipse)
	UINT32 resvd                            :7;
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003EE4 RW
	UINT32 reg_ellipse_w2_axis_ext_semiminor :16;	//15:0	//Ellipse Window 2 Semiminor Axis of external Ellipse
	UINT32 reg_ellipse_w2_axis_ext_semimajor :16;	//31:16	//Ellipse Window 2 Semimajor Axis of external Ellipse
	};
}PE_O20_REG_H10_ELLIPSE_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F00 RW
	UINT32 reg_csc_tm1_en                   :1;	//0 //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F04 RW
	UINT32 r_csc_tm1_coef1                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm1_coef0                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F08 RW
	UINT32 r_csc_tm1_coef3                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm1_coef2                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F0C RW
	UINT32 r_csc_tm1_coef5                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm1_coef4                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F10 RW
	UINT32 r_csc_tm1_coef7                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm1_coef6                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F14 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc_tm1_coef8                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F18 RW
	UINT32 r_csc_tm1_ofst1                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm1_ofst0                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F1C RW
	UINT32 r_csc_tm1_ofst3                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm1_ofst2                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F20 RW
	UINT32 r_csc_tm1_ofst5                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm1_ofst4                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F24 RW
	UINT32 reg_csc_tm2_en                   :1;	//0 //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F28 RW
	UINT32 r_csc_tm2_coef1                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm2_coef0                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F2C RW
	UINT32 r_csc_tm2_coef3                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm2_coef2                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F30 RW
	UINT32 r_csc_tm2_coef5                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm2_coef4                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F34 RW
	UINT32 r_csc_tm2_coef7                  :15;	//14:0	//CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc_tm2_coef6                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F38 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc_tm2_coef8                  :15;	//30:16	//CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F3C RW
	UINT32 r_csc_tm2_ofst1                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm2_ofst0                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F40 RW
	UINT32 r_csc_tm2_ofst3                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm2_ofst2                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F44 RW
	UINT32 r_csc_tm2_ofst5                  :11;	//10:0	//CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc_tm2_ofst4                  :11;	//26:16	//CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC_TM2_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F80 RW
	UINT32 reg_csc4th_en                    :1;	//0 //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F84 RW
	UINT32 r_csc4th_coef1                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F88 RW
	UINT32 r_csc4th_coef3                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F8C RW
	UINT32 r_csc4th_coef5                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F90 RW
	UINT32 r_csc4th_coef7                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F94 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F98 RW
	UINT32 r_csc4th_ofst1                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003F9C RW
	UINT32 r_csc4th_ofst3                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst2                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003FA0 RW
	UINT32 r_csc4th_ofst5                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst4                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_H10_CSC4_CTRL_08_T;

typedef struct {
	PE_O20_REG_H10_TCM_HDR10P_CTRL_01_T         hdr_tcm_hdr10p_ctrl_01;	//0xC9003E00
	PE_O20_REG_H10_TCM_SLUT0_00_T                     hdr_tcm_slut0_00;	//0xC9003E04
	PE_O20_REG_H10_TCM_SLUT0_01_T                     hdr_tcm_slut0_01;	//0xC9003E08
	PE_O20_REG_H10_TCM_SLUT0_02_T                     hdr_tcm_slut0_02;	//0xC9003E0C
	PE_O20_REG_H10_TCM_SLUT0_03_T                     hdr_tcm_slut0_03;	//0xC9003E10
	PE_O20_REG_H10_TCM_SLUT0_04_T                     hdr_tcm_slut0_04;	//0xC9003E14
	PE_O20_REG_H10_TCM_SLUT0_05_T                     hdr_tcm_slut0_05;	//0xC9003E18
	PE_O20_REG_H10_TCM_SLUT0_06_T                     hdr_tcm_slut0_06;	//0xC9003E1C
	PE_O20_REG_H10_TCM_SLUT0_07_T                     hdr_tcm_slut0_07;	//0xC9003E20
	PE_O20_REG_H10_TCM_SLUT0_08_T                     hdr_tcm_slut0_08;	//0xC9003E24
	PE_O20_REG_H10_TCM_SLUT0_09_T                     hdr_tcm_slut0_09;	//0xC9003E28
	PE_O20_REG_H10_TCM_SLUT1_00_T                     hdr_tcm_slut1_00;	//0xC9003E2C
	PE_O20_REG_H10_TCM_SLUT1_01_T                     hdr_tcm_slut1_01;	//0xC9003E30
	PE_O20_REG_H10_TCM_SLUT1_02_T                     hdr_tcm_slut1_02;	//0xC9003E34
	PE_O20_REG_H10_TCM_SLUT1_03_T                     hdr_tcm_slut1_03;	//0xC9003E38
	PE_O20_REG_H10_TCM_SLUT1_04_T                     hdr_tcm_slut1_04;	//0xC9003E3C
	PE_O20_REG_H10_TCM_SLUT1_05_T                     hdr_tcm_slut1_05;	//0xC9003E40
	PE_O20_REG_H10_TCM_SLUT1_06_T                     hdr_tcm_slut1_06;	//0xC9003E44
	PE_O20_REG_H10_TCM_SLUT1_07_T                     hdr_tcm_slut1_07;	//0xC9003E48
	PE_O20_REG_H10_TCM_SLUT1_08_T                     hdr_tcm_slut1_08;	//0xC9003E4C
	PE_O20_REG_H10_TCM_SLUT1_09_T                     hdr_tcm_slut1_09;	//0xC9003E50
	PE_O20_REG_H10_TCM_SLUT2_00_T                     hdr_tcm_slut2_00;	//0xC9003E54
	PE_O20_REG_H10_TCM_SLUT2_01_T                     hdr_tcm_slut2_01;	//0xC9003E58
	PE_O20_REG_H10_TCM_SLUT2_02_T                     hdr_tcm_slut2_02;	//0xC9003E5C
	PE_O20_REG_H10_TCM_SLUT2_03_T                     hdr_tcm_slut2_03;	//0xC9003E60
	PE_O20_REG_H10_TCM_SLUT2_04_T                     hdr_tcm_slut2_04;	//0xC9003E64
	PE_O20_REG_H10_TCM_SLUT2_05_T                     hdr_tcm_slut2_05;	//0xC9003E68
	PE_O20_REG_H10_TCM_SLUT2_06_T                     hdr_tcm_slut2_06;	//0xC9003E6C
	PE_O20_REG_H10_TCM_SLUT2_07_T                     hdr_tcm_slut2_07;	//0xC9003E70
	PE_O20_REG_H10_TCM_SLUT2_08_T                     hdr_tcm_slut2_08;	//0xC9003E74
	PE_O20_REG_H10_TCM_SLUT2_09_T                     hdr_tcm_slut2_09;	//0xC9003E78
	PE_O20_REG_H10_SAT_MAP_CTRL_00_T               hdr_sat_map_ctrl_00;	//0xC9003E7C
	PE_O20_REG_H10_SAT_MAP_CTRL_01_T               hdr_sat_map_ctrl_01;	//0xC9003E80
	PE_O20_REG_H10_SAT_MAP_CTRL_02_T               hdr_sat_map_ctrl_02;	//0xC9003E84
	PE_O20_REG_H10_SAT_MAP_CTRL_03_T               hdr_sat_map_ctrl_03;	//0xC9003E88
	PE_O20_REG_H10_SAT_MAP_CTRL_04_T               hdr_sat_map_ctrl_04;	//0xC9003E8C
	PE_O20_REG_H10_SAT_MAP_CTRL_05_T               hdr_sat_map_ctrl_05;	//0xC9003E90
	PE_O20_REG_H10_SAT_MAP_CTRL_06_T               hdr_sat_map_ctrl_06;	//0xC9003E94
	UINT32                                                  reserved216;	//0xC9003E98
	UINT32                                                  reserved217;	//0xC9003E9C
	UINT32                                                  reserved218;	//0xC9003EA0
	UINT32                                                  reserved219;	//0xC9003EA4
	UINT32                                                  reserved220;	//0xC9003EA8
	UINT32                                                  reserved221;	//0xC9003EAC
	UINT32                                                  reserved222;	//0xC9003EB0
	UINT32                                                  reserved223;	//0xC9003EB4
	UINT32                                                  reserved224;	//0xC9003EB8
	UINT32                                                  reserved225;	//0xC9003EBC
	PE_O20_REG_H10_ELLIPSE_CTRL_00_T               hdr_ellipse_ctrl_00;	//0xC9003EC0
	PE_O20_REG_H10_ELLIPSE_CTRL_01_T               hdr_ellipse_ctrl_01;	//0xC9003EC4
	PE_O20_REG_H10_ELLIPSE_CTRL_02_T               hdr_ellipse_ctrl_02;	//0xC9003EC8
	PE_O20_REG_H10_ELLIPSE_CTRL_03_T               hdr_ellipse_ctrl_03;	//0xC9003ECC
	PE_O20_REG_H10_ELLIPSE_CTRL_04_T               hdr_ellipse_ctrl_04;	//0xC9003ED0
	PE_O20_REG_H10_ELLIPSE_CTRL_05_T               hdr_ellipse_ctrl_05;	//0xC9003ED4
	PE_O20_REG_H10_ELLIPSE_CTRL_06_T               hdr_ellipse_ctrl_06;	//0xC9003ED8
	PE_O20_REG_H10_ELLIPSE_CTRL_07_T               hdr_ellipse_ctrl_07;	//0xC9003EDC
	PE_O20_REG_H10_ELLIPSE_CTRL_08_T               hdr_ellipse_ctrl_08;	//0xC9003EE0
	PE_O20_REG_H10_ELLIPSE_CTRL_09_T               hdr_ellipse_ctrl_09;	//0xC9003EE4
	UINT32                                                  reserved226;	//0xC9003EE8
	UINT32                                                  reserved227;	//0xC9003EEC
	UINT32                                                  reserved228;	//0xC9003EF0
	UINT32                                                  reserved229;	//0xC9003EF4
	UINT32                                                  reserved230;	//0xC9003EF8
	UINT32                                                  reserved231;	//0xC9003EFC
	PE_O20_REG_H10_CSC_TM1_CTRL_00_T               hdr_csc_tm1_ctrl_00;	//0xC9003F00
	PE_O20_REG_H10_CSC_TM1_CTRL_01_T               hdr_csc_tm1_ctrl_01;	//0xC9003F04
	PE_O20_REG_H10_CSC_TM1_CTRL_02_T               hdr_csc_tm1_ctrl_02;	//0xC9003F08
	PE_O20_REG_H10_CSC_TM1_CTRL_03_T               hdr_csc_tm1_ctrl_03;	//0xC9003F0C
	PE_O20_REG_H10_CSC_TM1_CTRL_04_T               hdr_csc_tm1_ctrl_04;	//0xC9003F10
	PE_O20_REG_H10_CSC_TM1_CTRL_05_T               hdr_csc_tm1_ctrl_05;	//0xC9003F14
	PE_O20_REG_H10_CSC_TM1_CTRL_06_T               hdr_csc_tm1_ctrl_06;	//0xC9003F18
	PE_O20_REG_H10_CSC_TM1_CTRL_07_T               hdr_csc_tm1_ctrl_07;	//0xC9003F1C
	PE_O20_REG_H10_CSC_TM1_CTRL_08_T               hdr_csc_tm1_ctrl_08;	//0xC9003F20
	PE_O20_REG_H10_CSC_TM2_CTRL_00_T               hdr_csc_tm2_ctrl_00;	//0xC9003F24
	PE_O20_REG_H10_CSC_TM2_CTRL_01_T               hdr_csc_tm2_ctrl_01;	//0xC9003F28
	PE_O20_REG_H10_CSC_TM2_CTRL_02_T               hdr_csc_tm2_ctrl_02;	//0xC9003F2C
	PE_O20_REG_H10_CSC_TM2_CTRL_03_T               hdr_csc_tm2_ctrl_03;	//0xC9003F30
	PE_O20_REG_H10_CSC_TM2_CTRL_04_T               hdr_csc_tm2_ctrl_04;	//0xC9003F34
	PE_O20_REG_H10_CSC_TM2_CTRL_05_T               hdr_csc_tm2_ctrl_05;	//0xC9003F38
	PE_O20_REG_H10_CSC_TM2_CTRL_06_T               hdr_csc_tm2_ctrl_06;	//0xC9003F3C
	PE_O20_REG_H10_CSC_TM2_CTRL_07_T               hdr_csc_tm2_ctrl_07;	//0xC9003F40
	PE_O20_REG_H10_CSC_TM2_CTRL_08_T               hdr_csc_tm2_ctrl_08;	//0xC9003F44
	UINT32                                                  reserved232;	//0xC9003F48
	UINT32                                                  reserved233;	//0xC9003F4C
	UINT32                                                  reserved234;	//0xC9003F50
	UINT32                                                  reserved235;	//0xC9003F54
	UINT32                                                  reserved236;	//0xC9003F58
	UINT32                                                  reserved237;	//0xC9003F5C
	UINT32                                                  reserved238;	//0xC9003F60
	UINT32                                                  reserved239;	//0xC9003F64
	UINT32                                                  reserved240;	//0xC9003F68
	UINT32                                                  reserved241;	//0xC9003F6C
	UINT32                                                  reserved242;	//0xC9003F70
	UINT32                                                  reserved243;	//0xC9003F74
	UINT32                                                  reserved244;	//0xC9003F78
	UINT32                                                  reserved245;	//0xC9003F7C
	PE_O20_REG_H10_CSC4_CTRL_00_T                     hdr_csc4_ctrl_00;	//0xC9003F80
	PE_O20_REG_H10_CSC4_CTRL_01_T                     hdr_csc4_ctrl_01;	//0xC9003F84
	PE_O20_REG_H10_CSC4_CTRL_02_T                     hdr_csc4_ctrl_02;	//0xC9003F88
	PE_O20_REG_H10_CSC4_CTRL_03_T                     hdr_csc4_ctrl_03;	//0xC9003F8C
	PE_O20_REG_H10_CSC4_CTRL_04_T                     hdr_csc4_ctrl_04;	//0xC9003F90
	PE_O20_REG_H10_CSC4_CTRL_05_T                     hdr_csc4_ctrl_05;	//0xC9003F94
	PE_O20_REG_H10_CSC4_CTRL_06_T                     hdr_csc4_ctrl_06;	//0xC9003F98
	PE_O20_REG_H10_CSC4_CTRL_07_T                     hdr_csc4_ctrl_07;	//0xC9003F9C
	PE_O20_REG_H10_CSC4_CTRL_08_T                     hdr_csc4_ctrl_08;	//0xC9003FA0
}PE_O20_REG_H10_P_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C00 RW
	UINT32 width                            :12;	//11:0	//width
	UINT32 resvd0                           :4;
	UINT32 height                           :12;	//27:16	//height
	UINT32 reg_equal_lut                    :1;	//28 //llut equal lut
	UINT32 resvd1                           :1;
	UINT32 reg_sdr2hdr_enable               :1;	//30 //enable
	UINT32 reg_dbg_brm_map                  :1;	//31 //enable bright region debug map
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C04 RW
	UINT32 reg_csc1st_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C08 RW
	UINT32 r_csc1st_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C0C RW
	UINT32 r_csc1st_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C10 RW
	UINT32 r_csc1st_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C14 RW
	UINT32 r_csc1st_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C18 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C1C RW
	UINT32 r_csc1st_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C20 RW
	UINT32 r_csc1st_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C24 RW
	UINT32 r_csc1st_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C28 RW
	UINT32 reg_ihsv_vgain                   :8;	//07:00	//RGB -> HSV V gain
	UINT32 reg_ihsv_sgain                   :8;	//15:08	//RGB -> HSV H gain
	UINT32 resvd                            :14;
	UINT32 reg_hsv_scaler_en                :1;	//30 //
	UINT32 reg_hsv_hsl_sel                  :1;	//31 //
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C2C RW
	UINT32 reg_ihsv_voffset                 :8;	//7:0	//RGB -> HSV V offset
	UINT32 reg_ihsv_soffset                 :8;	//15:8	//RGB -> HSV S offset
	UINT32 reg_ihsv_hoffset                 :8;	//23:16	//RGB -> HSV H offset
	UINT32 resvd                            :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C30 RW
	UINT32 reg_cdt_dcp_mean                 :8;	//7:0	//Dark Threshold (Previous frame) mean
	UINT32 resvd                            :24;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C34 RW
	UINT32 reg_fbs_y_max                    :10;	//9:0	//Find Bright Spot (Previous frame) luma max
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_ybs_scale                :7;	//22:16	//Find Bright Spot ybs scale
	UINT32 resvd1                           :5;
	UINT32 reg_fbs_bs_exp_s_wei             :3;	//30:28	//bs_exp weight (0~4)
	UINT32 resvd2                           :1;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C38 RW
	UINT32 reg_fbs_yy_lut_x_00              :8;	//7:0	//reg_fbs_yy_lut point x_00
	UINT32 reg_fbs_yy_lut_y_00              :8;	//15:8	//reg_fbs_yy_lut point y_00
	UINT32 reg_fbs_yy_lut_x_01              :8;	//23:16	//reg_fbs_yy_lut point x_01
	UINT32 reg_fbs_yy_lut_y_01              :8;	//31:24	//reg_fbs_yy_lut point y_01
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C3C RW
	UINT32 reg_fbs_yy_lut_x_02              :8;	//7:0	//reg_fbs_yy_lut point x_02
	UINT32 reg_fbs_yy_lut_y_02              :8;	//15:8	//reg_fbs_yy_lut point y_02
	UINT32 reg_fbs_yy_lut_x_03              :8;	//23:16	//reg_fbs_yy_lut point x_03
	UINT32 reg_fbs_yy_lut_y_03              :8;	//31:24	//reg_fbs_yy_lut point y_03
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C40 RW
	UINT32 reg_fbs_yy_lut_x_04              :8;	//7:0	//reg_fbs_yy_lut point x_04
	UINT32 reg_fbs_yy_lut_y_04              :8;	//15:8	//reg_fbs_yy_lut point y_04
	UINT32 reg_fbs_yy_lut_x_05              :8;	//23:16	//reg_fbs_yy_lut point x_05
	UINT32 reg_fbs_yy_lut_y_05              :8;	//31:24	//reg_fbs_yy_lut point y_05
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C44 RW
	UINT32 reg_fbs_yy_lut_x_06              :8;	//7:0	//reg_fbs_yy_lut point x_06
	UINT32 reg_fbs_yy_lut_y_06              :8;	//15:8	//reg_fbs_yy_lut point y_06
	UINT32 reg_fbs_yy_lut_x_07              :8;	//23:16	//reg_fbs_yy_lut point x_07
	UINT32 reg_fbs_yy_lut_y_07              :8;	//31:24	//reg_fbs_yy_lut point y_07
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C48 RW
	UINT32 reg_fbs_yy_lut_x_08              :8;	//7:0	//reg_fbs_yy_lut point x_08
	UINT32 reg_fbs_yy_lut_y_08              :8;	//15:8	//reg_fbs_yy_lut point y_08
	UINT32 reg_fbs_yy_lut_x_09              :8;	//23:16	//reg_fbs_yy_lut point x_09
	UINT32 reg_fbs_yy_lut_y_09              :8;	//31:24	//reg_fbs_yy_lut point y_09
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C4C RW
	UINT32 reg_fbs_yy_lut_x_10              :8;	//7:0	//reg_fbs_yy_lut point x_10
	UINT32 reg_fbs_yy_lut_y_10              :8;	//15:8	//reg_fbs_yy_lut point y_10
	UINT32 reg_fbs_yy_lut_x_11              :8;	//23:16	//reg_fbs_yy_lut point x_11
	UINT32 reg_fbs_yy_lut_y_11              :8;	//31:24	//reg_fbs_yy_lut point y_11
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C50 RW
	UINT32 reg_fbs_yy_lut_x_12              :8;	//7:0	//reg_fbs_yy_lut point x_12
	UINT32 reg_fbs_yy_lut_y_12              :8;	//15:8	//reg_fbs_yy_lut point y_12
	UINT32 reg_fbs_yy_lut_x_13              :8;	//23:16	//reg_fbs_yy_lut point x_13
	UINT32 reg_fbs_yy_lut_y_13              :8;	//31:24	//reg_fbs_yy_lut point y_13
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C54 RW
	UINT32 reg_fbs_yy_lut_x_14              :8;	//7:0	//reg_fbs_yy_lut point x_14
	UINT32 reg_fbs_yy_lut_y_14              :8;	//15:8	//reg_fbs_yy_lut point y_14
	UINT32 reg_fbs_yy_lut_x_15              :8;	//23:16	//reg_fbs_yy_lut point x_15
	UINT32 reg_fbs_yy_lut_y_15              :8;	//31:24	//reg_fbs_yy_lut point y_15
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C58 RW
	UINT32 reg_fbs_bs_cnt0                  :12;	//11:0	//bs_cnt0 line offset
	UINT32 resvd0                           :4;
	UINT32 reg_fbs_bs_cnt1                  :12;	//27:16	//bs_cnt1 line offset
	UINT32 resvd1                           :4;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C5C RW
	UINT32 reg_fbs_bs_cnt2                  :12;	//11:0	//bs_cnt2 line offset
	UINT32 resvd0                           :4;
	UINT32 reg_fbs_bs_cnt3                  :12;	//27:16	//bs_cnt3 line offset
	UINT32 resvd1                           :4;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C60 RW
	UINT32 reg_fbs_bs_cnt4                  :12;	//11:0	//bs_cnt4 line offset
	UINT32 resvd0                           :4;
	UINT32 reg_fbs_bs_cnt5                  :12;	//27:16	//bs_cnt5 line offset
	UINT32 resvd1                           :4;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C64 RW
	UINT32 reg_fbs_bs_cnt6                  :12;	//11:0	//bs_cnt6 line offset
	UINT32 resvd                            :20;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C68 RW
	UINT32 reg_fbs_bs_exp_y_ofs_0           :10;	//9:0	//Find Bright Spot exp y offset 0
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_1           :10;	//25:16	//Find Bright Spot exp y offset 1
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C6C RW
	UINT32 reg_fbs_bs_exp_y_ofs_2           :10;	//9:0	//Find Bright Spot exp y offset 2
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_3           :10;	//25:16	//Find Bright Spot exp y offset 3
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C70 RW
	UINT32 reg_fbs_bs_exp_y_ofs_4           :10;	//9:0	//Find Bright Spot exp y offset 4
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_5           :10;	//25:16	//Find Bright Spot exp y offset 5
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C74 RW
	UINT32 reg_fbs_bs_exp_y_ofs_6           :10;	//9:0	//Find Bright Spot exp y offset 6
	UINT32 resvd                            :22;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C78 RW
	UINT32 reg_fbs_bs_exp_s_ofs_0           :8;	//7:0	//Find Bright Spot exp s offset 0
	UINT32 reg_fbs_bs_exp_s_ofs_1           :8;	//15:8	//Find Bright Spot exp s offset 1
	UINT32 reg_fbs_bs_exp_s_ofs_2           :8;	//23:16	//Find Bright Spot exp s offset 2
	UINT32 reg_fbs_bs_exp_s_ofs_3           :8;	//31:24	//Find Bright Spot exp s offset 3
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C7C RW
	UINT32 reg_fbs_bs_exp_s_ofs_4           :8;	//7:0	//Find Bright Spot exp s offset 4
	UINT32 reg_fbs_bs_exp_s_ofs_5           :8;	//15:8	//Find Bright Spot exp s offset 5
	UINT32 reg_fbs_bs_exp_s_ofs_6           :8;	//23:16	//Find Bright Spot exp s offset 6
	UINT32 resvd                            :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C80 RW
	UINT32 resvd                            :28;
	UINT32 reg_brm_exp_wei                  :4;	//31:28	//brm_exp weight (0~8)
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C84 RW
	UINT32 reg_brm_br_lut_x_0               :10;	//9:0	//Bright Region Map lut x_0
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_0               :8;	//23:16	//Bright Region Map lut y_0
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C88 RW
	UINT32 reg_brm_br_lut_x_1               :10;	//9:0	//Bright Region Map lut x_1
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_1               :8;	//23:16	//Bright Region Map lut y_1
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C8C RW
	UINT32 reg_brm_br_lut_x_2               :10;	//9:0	//Bright Region Map lut x_2
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_2               :8;	//23:16	//Bright Region Map lut y_2
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C90 RW
	UINT32 reg_brm_br_lut_x_3               :10;	//9:0	//Bright Region Map lut x_3
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_3               :8;	//23:16	//Bright Region Map lut y_3
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C94 RW
	UINT32 reg_brm_br_lut_x_4               :10;	//9:0	//Bright Region Map lut x_4
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_4               :8;	//23:16	//Bright Region Map lut y_4
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C98 RW
	UINT32 reg_brm_br_lut_x_5               :10;	//9:0	//Bright Region Map lut x_5
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_5               :8;	//23:16	//Bright Region Map lut y_5
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003C9C RW
	UINT32 reg_brm_br_lut_x_6               :10;	//9:0	//Bright Region Map lut x_6
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_6               :8;	//23:16	//Bright Region Map lut y_6
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CA0 RW
	UINT32 reg_brm_br_lut_x_7               :10;	//9:0	//Bright Region Map lut x_7
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_7               :8;	//23:16	//Bright Region Map lut y_7
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CA4 RW
	UINT32 reg_brm_br_lut_x_8               :10;	//9:0	//Bright Region Map lut x_8
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_8               :8;	//23:16	//Bright Region Map lut y_8
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CA8 RW
	UINT32 reg_brm_br_lut_x_9               :10;	//9:0	//Bright Region Map lut x_9
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_9               :8;	//23:16	//Bright Region Map lut y_9
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CAC RW
	UINT32 reg_brm_br_lut_x_10              :10;	//9:0	//Bright Region Map lut x_10
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_10              :8;	//23:16	//Bright Region Map lut y_10
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CB0 RW
	UINT32 reg_brm_br_lut_x_11              :10;	//9:0	//Bright Region Map lut x_11
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_11              :8;	//23:16	//Bright Region Map lut y_11
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CB4 RW
	UINT32 reg_brm_br_lut_x_12              :10;	//9:0	//Bright Region Map lut x_12
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_12              :8;	//23:16	//Bright Region Map lut y_12
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CB8 RW
	UINT32 reg_brm_br_lut_x_13              :10;	//9:0	//Bright Region Map lut x_13
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_13              :8;	//23:16	//Bright Region Map lut y_13
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CBC RW
	UINT32 reg_brm_br_lut_x_14              :10;	//9:0	//Bright Region Map lut x_14
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_14              :8;	//23:16	//Bright Region Map lut y_14
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CC0 RW
	UINT32 reg_brm_br_lut_x_15              :10;	//9:0	//Bright Region Map lut x_15
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_15              :8;	//23:16	//Bright Region Map lut y_15
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CC4 RW
	UINT32 cc_en                            :1;	//0:0	//0 : Chroma Compensation Disable	1 : Chroma Compensation Enable
	UINT32 resvd                            :31;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CC8 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CD0 RW
	UINT32 luminance_lut0_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CD4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CD8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CDC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CE0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CE4 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CE8 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CEC RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CF0 RW
	UINT32 luminance_lut1_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CF4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CF8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003CFC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D00 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D04 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut1_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D08 RW
	UINT32 hif_llut1_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut1_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut1_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut1_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut1_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut1_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut1_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D0C RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_S2H_SDR2HDR_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D30 RW
	UINT32 hist_bin_mode                    :2;	//1:0	//"00" : 32 bin mode	others : 16 bin mode
	UINT32 histogram_mode                   :2;	//3:2	//"00" : Own side's histogram data use	"01" : Other side's histogram data use	"10" : Average between Own and Other side's histogram data use
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd0                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd1                           :6;
	UINT32 hist_clear                       :1;	//23 //1: clear(Debugging purpose, reset histogram memory)
	UINT32 hist_brm_th                      :8;	//31:24	//Threshold for histogram calculation (BRM_MAP)
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D34 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D38 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D3C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D40 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D44 RW
	UINT32 hif_hist_address                 :7;	//6:0	//"0"   : 0th bin	"1'   : 1st bin	?	"31" : 31st bin
	UINT32 resvd0                           :5;
	UINT32 hif_hist_ai                      :1;	//12 //auto increment enable
	UINT32 resvd1                           :2;
	UINT32 hif_hist_enable                  :1;	//15 //0' : host access(read only)	'1' : normal operation
	UINT32 hif_status_address               :3;	//18:16	//"1" : Maximum/Minimum V value for one frame	"4" : Detected region number
	UINT32 resvd2                           :9;
	UINT32 hif_status_ai                    :1;	//28 //auto increment enable
	UINT32 hif_mask                         :1;	//29 //do not read histogram registers during this bit '1'	  : period of histogram calculation(read only)
	UINT32 resvd3                           :2;
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D48 RW
	UINT32 hist_status0                     :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D4C RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_O20_REG_S2H_SDR2HDR_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D50 RW
	UINT32 luminance_lut0_enable            :1;	//0 //luminance LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D54 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D58 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D5C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D60 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D64 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D68 RW
	UINT32 hif_llut0_address                :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_llut0_load                   :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_llut0_manual_load_en         :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_llut0_ai                     :1;	//12 //auto increment enable	1: enable
	UINT32 hif_llut0_write_x                :1;	//13 //0: Write X data 32bit / 1 : Write Y data 32bit
	UINT32 hif_llut0_read_x                 :1;	//14 //0: Read X data 32bit / 1 : Read Y data 32bit
	UINT32 hif_llut0_enable                 :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_O20_REG_S2H_SDR2HDR_FBSLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003D6C RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_O20_REG_S2H_HDR_FBS_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DA0 RO
	UINT32 reg_st_max_luma                  :10;	//9:0	//Max luma in frame
	UINT32 resvd0                           :6;
	UINT32 dcp_out_mean                     :10;	//25:16	//Dark Channel Prior mean value
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DA4 RO
	UINT32 reg_fbs_bb_yy                    :10;	//9:0	//Find Bright Spout luma value
	UINT32 resvd0                           :6;
	UINT32 reg_cdt_sdt                      :8;	//23:16	//Dark Vt standard deviation
	UINT32 resvd1                           :8;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DA8 RO
	UINT32 out_bs_cnt0                      :23;	//22:0	//Find Bright Spot bs_cnt0
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DAC RO
	UINT32 out_bs_cnt1                      :23;	//22:0	//Find Bright Spot bs_cnt1
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DB0 RO
	UINT32 out_bs_cnt2                      :23;	//22:0	//Find Bright Spot bs_cnt2
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DB4 RO
	UINT32 out_bs_cnt3                      :23;	//22:0	//Find Bright Spot bs_cnt3
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DB8 RO
	UINT32 out_bs_cnt4                      :23;	//22:0	//Find Bright Spot bs_cnt4
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DBC RO
	UINT32 out_bs_cnt5                      :23;	//22:0	//Find Bright Spot bs_cnt5
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DC0 RO
	UINT32 out_bs_cnt6                      :23;	//22:0	//Find Bright Spot bs_cnt6
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9003DC4 RO
	UINT32 out_bs_cnt7                      :23;	//22:0	//Find Bright Spot bs_cnt7
	UINT32 resvd                            :9;
	};
}PE_O20_REG_S2H_HDR_SDR2HDR_STAT_09_T;

typedef struct {
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_00_T             hdr_sdr2hdr_ctrl_00;	//0xC9003C00
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_01_T             hdr_sdr2hdr_ctrl_01;	//0xC9003C04
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_02_T             hdr_sdr2hdr_ctrl_02;	//0xC9003C08
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_03_T             hdr_sdr2hdr_ctrl_03;	//0xC9003C0C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_04_T             hdr_sdr2hdr_ctrl_04;	//0xC9003C10
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_05_T             hdr_sdr2hdr_ctrl_05;	//0xC9003C14
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_06_T             hdr_sdr2hdr_ctrl_06;	//0xC9003C18
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_07_T             hdr_sdr2hdr_ctrl_07;	//0xC9003C1C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_08_T             hdr_sdr2hdr_ctrl_08;	//0xC9003C20
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_09_T             hdr_sdr2hdr_ctrl_09;	//0xC9003C24
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_10_T             hdr_sdr2hdr_ctrl_10;	//0xC9003C28
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_11_T             hdr_sdr2hdr_ctrl_11;	//0xC9003C2C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_12_T             hdr_sdr2hdr_ctrl_12;	//0xC9003C30
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_13_T             hdr_sdr2hdr_ctrl_13;	//0xC9003C34
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_14_T             hdr_sdr2hdr_ctrl_14;	//0xC9003C38
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_15_T             hdr_sdr2hdr_ctrl_15;	//0xC9003C3C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_16_T             hdr_sdr2hdr_ctrl_16;	//0xC9003C40
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_17_T             hdr_sdr2hdr_ctrl_17;	//0xC9003C44
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_18_T             hdr_sdr2hdr_ctrl_18;	//0xC9003C48
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_19_T             hdr_sdr2hdr_ctrl_19;	//0xC9003C4C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_20_T             hdr_sdr2hdr_ctrl_20;	//0xC9003C50
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_21_T             hdr_sdr2hdr_ctrl_21;	//0xC9003C54
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_22_T             hdr_sdr2hdr_ctrl_22;	//0xC9003C58
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_23_T             hdr_sdr2hdr_ctrl_23;	//0xC9003C5C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_24_T             hdr_sdr2hdr_ctrl_24;	//0xC9003C60
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_25_T             hdr_sdr2hdr_ctrl_25;	//0xC9003C64
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_26_T             hdr_sdr2hdr_ctrl_26;	//0xC9003C68
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_27_T             hdr_sdr2hdr_ctrl_27;	//0xC9003C6C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_28_T             hdr_sdr2hdr_ctrl_28;	//0xC9003C70
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_29_T             hdr_sdr2hdr_ctrl_29;	//0xC9003C74
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_30_T             hdr_sdr2hdr_ctrl_30;	//0xC9003C78
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_31_T             hdr_sdr2hdr_ctrl_31;	//0xC9003C7C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_32_T             hdr_sdr2hdr_ctrl_32;	//0xC9003C80
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_33_T             hdr_sdr2hdr_ctrl_33;	//0xC9003C84
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_34_T             hdr_sdr2hdr_ctrl_34;	//0xC9003C88
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_35_T             hdr_sdr2hdr_ctrl_35;	//0xC9003C8C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_36_T             hdr_sdr2hdr_ctrl_36;	//0xC9003C90
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_37_T             hdr_sdr2hdr_ctrl_37;	//0xC9003C94
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_38_T             hdr_sdr2hdr_ctrl_38;	//0xC9003C98
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_39_T             hdr_sdr2hdr_ctrl_39;	//0xC9003C9C
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_40_T             hdr_sdr2hdr_ctrl_40;	//0xC9003CA0
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_41_T             hdr_sdr2hdr_ctrl_41;	//0xC9003CA4
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_42_T             hdr_sdr2hdr_ctrl_42;	//0xC9003CA8
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_43_T             hdr_sdr2hdr_ctrl_43;	//0xC9003CAC
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_44_T             hdr_sdr2hdr_ctrl_44;	//0xC9003CB0
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_45_T             hdr_sdr2hdr_ctrl_45;	//0xC9003CB4
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_46_T             hdr_sdr2hdr_ctrl_46;	//0xC9003CB8
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_47_T             hdr_sdr2hdr_ctrl_47;	//0xC9003CBC
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_48_T             hdr_sdr2hdr_ctrl_48;	//0xC9003CC0
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_49_T             hdr_sdr2hdr_ctrl_49;	//0xC9003CC4
	PE_O20_REG_S2H_HDR_SDR2HDR_CTRL_50_T             hdr_sdr2hdr_ctrl_50;	//0xC9003CC8
	UINT32                                                     reserved0;	//0xC9003CCC
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_00_T         sdr2hdr_llut0_ctrl_00;	//0xC9003CD0
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_01_T         sdr2hdr_llut0_ctrl_01;	//0xC9003CD4
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_02_T         sdr2hdr_llut0_ctrl_02;	//0xC9003CD8
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_03_T         sdr2hdr_llut0_ctrl_03;	//0xC9003CDC
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_04_T         sdr2hdr_llut0_ctrl_04;	//0xC9003CE0
	PE_O20_REG_S2H_SDR2HDR_LLUT0_CTRL_05_T         sdr2hdr_llut0_ctrl_05;	//0xC9003CE4
	PE_O20_REG_S2H_SDR2HDR_LLUT0_IA_CTRL_T         sdr2hdr_llut0_ia_ctrl;	//0xC9003CE8
	PE_O20_REG_S2H_SDR2HDR_LLUT0_IA_DATA_T         sdr2hdr_llut0_ia_data;	//0xC9003CEC
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_00_T         sdr2hdr_llut1_ctrl_00;	//0xC9003CF0
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_01_T         sdr2hdr_llut1_ctrl_01;	//0xC9003CF4
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_02_T         sdr2hdr_llut1_ctrl_02;	//0xC9003CF8
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_03_T         sdr2hdr_llut1_ctrl_03;	//0xC9003CFC
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_04_T         sdr2hdr_llut1_ctrl_04;	//0xC9003D00
	PE_O20_REG_S2H_SDR2HDR_LLUT1_CTRL_05_T         sdr2hdr_llut1_ctrl_05;	//0xC9003D04
	PE_O20_REG_S2H_SDR2HDR_LLUT1_IA_CTRL_T         sdr2hdr_llut1_ia_ctrl;	//0xC9003D08
	PE_O20_REG_S2H_SDR2HDR_LLUT1_IA_DATA_T         sdr2hdr_llut1_ia_data;	//0xC9003D0C
	UINT32                                                     reserved1;	//0xC9003D10
	UINT32                                                     reserved2;	//0xC9003D14
	UINT32                                                     reserved3;	//0xC9003D18
	UINT32                                                     reserved4;	//0xC9003D1C
	UINT32                                                     reserved5;	//0xC9003D20
	UINT32                                                     reserved6;	//0xC9003D24
	UINT32                                                     reserved7;	//0xC9003D28
	UINT32                                                     reserved8;	//0xC9003D2C
	PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_00_T           sdr2hdr_hist_ctrl_00;	//0xC9003D30
	PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_01_T           sdr2hdr_hist_ctrl_01;	//0xC9003D34
	PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_02_T           sdr2hdr_hist_ctrl_02;	//0xC9003D38
	PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_03_T           sdr2hdr_hist_ctrl_03;	//0xC9003D3C
	PE_O20_REG_S2H_SDR2HDR_HIST_CTRL_04_T           sdr2hdr_hist_ctrl_04;	//0xC9003D40
	PE_O20_REG_S2H_SDR2HDR_HIST_IA_CTRL_T           sdr2hdr_hist_ia_ctrl;	//0xC9003D44
	PE_O20_REG_S2H_SDR2HDR_HIST_IA_DATA1_T         sdr2hdr_hist_ia_data1;	//0xC9003D48
	PE_O20_REG_S2H_SDR2HDR_HIST_IA_DATA2_T         sdr2hdr_hist_ia_data2;	//0xC9003D4C
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_00_T       sdr2hdr_fbslut_ctrl_00;	//0xC9003D50
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_01_T       sdr2hdr_fbslut_ctrl_01;	//0xC9003D54
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_02_T       sdr2hdr_fbslut_ctrl_02;	//0xC9003D58
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_03_T       sdr2hdr_fbslut_ctrl_03;	//0xC9003D5C
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_04_T       sdr2hdr_fbslut_ctrl_04;	//0xC9003D60
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_CTRL_05_T       sdr2hdr_fbslut_ctrl_05;	//0xC9003D64
	PE_O20_REG_S2H_SDR2HDR_FBSLUT_IA_CTRL_T       sdr2hdr_fbslut_ia_ctrl;	//0xC9003D68
	PE_O20_REG_S2H_HDR_FBS_LUT_IA_DATA_T             hdr_fbs_lut_ia_data;	//0xC9003D6C
	UINT32                                                     reserved9;	//0xC9003D70
	UINT32                                                    reserved10;	//0xC9003D74
	UINT32                                                    reserved11;	//0xC9003D78
	UINT32                                                    reserved12;	//0xC9003D7C
	UINT32                                                    reserved13;	//0xC9003D80
	UINT32                                                    reserved14;	//0xC9003D84
	UINT32                                                    reserved15;	//0xC9003D88
	UINT32                                                    reserved16;	//0xC9003D8C
	UINT32                                                    reserved17;	//0xC9003D90
	UINT32                                                    reserved18;	//0xC9003D94
	UINT32                                                    reserved19;	//0xC9003D98
	UINT32                                                    reserved20;	//0xC9003D9C
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_00_T             hdr_sdr2hdr_stat_00;	//0xC9003DA0
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_01_T             hdr_sdr2hdr_stat_01;	//0xC9003DA4
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_02_T             hdr_sdr2hdr_stat_02;	//0xC9003DA8
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_03_T             hdr_sdr2hdr_stat_03;	//0xC9003DAC
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_04_T             hdr_sdr2hdr_stat_04;	//0xC9003DB0
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_05_T             hdr_sdr2hdr_stat_05;	//0xC9003DB4
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_06_T             hdr_sdr2hdr_stat_06;	//0xC9003DB8
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_07_T             hdr_sdr2hdr_stat_07;	//0xC9003DBC
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_08_T             hdr_sdr2hdr_stat_08;	//0xC9003DC0
	PE_O20_REG_S2H_HDR_SDR2HDR_STAT_09_T             hdr_sdr2hdr_stat_09;	//0xC9003DC4
}PE_O20_REG_S2H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017800 RW
	UINT32 pic_height                       :16;	//15:0	//Pic Height
	UINT32 pic_width                        :16;	//31:16	//Pic Width
	};
}PE_O20_REG_GAV_HDR_PIC_SIZE_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017804 RW
	UINT32 m_ics                            :2;	//1:0	//input color space.	0,1 : 420	2:422	3:444
	UINT32 resvd0                           :2;
	UINT32 m_ocs                            :2;	//5:4	//buffer out color space.(dolby mode? ?? 444, buffer mode? 420/422)	0,1 : 420	2:422	3:444(if m_bl_ics == 420or422, with set this, h repeat is on automatically)
	UINT32 resvd1                           :6;
	UINT32 m_y_add_hrepeat                  :1;	//12 //(for dolbyhdr 1:4 mode)	0:no hrepeat	1:h 1 repeat
	UINT32 m_c_add_hrepeat                  :1;	//13 //ics? ocs?? ??? ?? hrepeat? ???? ???.	? register? ?? ??? additional repeat???.(for dolbyhdr 1:4 mode)	0: no additional repeat	1: additonal repeat	ex) 422/420 to 444? ?? ?? hrepeat ?? ???. ??? ?? x2 repeat ?? ???? ??. ?, ? reg 1? setting?? ??? 422/420??? cb/cr? ? 4? repeat? ?? ??.
	UINT32 resvd2                           :2;
	UINT32 m_v2_flt_en                      :1;	//16 //0:repeat or bypass	1:420->422(v filtering)
	UINT32 resvd3                           :3;
	UINT32 m_h2_flt_en                      :1;	//20 //0:repeat or bypass	1:422->444(h filtering)
	UINT32 resvd4                           :3;
	UINT32 m_c_buf_vrepeat                  :2;	//25:24	//1:original+1line repeat(if input 420? set to this) 	2:original 	3:original+3line repeat	guide : 	OTT1:1 Mode. value = 1	OTT1:4 mode. value = 3
	UINT32 resvd5                           :2;
	UINT32 m_y_buf_vrepeat                  :2;	//29:28	//1:original+1line repeat,	3:original+3line repeat
	UINT32 resvd6                           :2;
	};
}PE_O20_REG_GAV_HDR_BUF_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017808 RW
	UINT32 buf_en                           :1;	//0 //0 : Buffer Off	1 : Buffer On
	UINT32 resvd0                           :3;
	UINT32 core_bypass                      :1;	//4 //0 : Path through core.	1 : Core bypass. Only buffer processing
	UINT32 resvd1                           :3;
	UINT32 top_det_bypass                   :1;	//8 //0 : Path through buffer & core.	1 : top detour
	UINT32 resvd2                           :23;
	};
}PE_O20_REG_GAV_BUF_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901780C RW
	UINT32 obuf_m_cs_type                   :2;	//1:0	//0: YUV420	2: YUV422	3: YUV444
	UINT32 resvd0                           :2;
	UINT32 obuf_m_vsample                   :1;	//4 //Vertical Sampling mode (0 : Even Line sample) / 1 : (Zigzag sample)
	UINT32 resvd1                           :3;
	UINT32 obuf_m_hsample                   :1;	//8 //Horizontal Sampling mode (0 : Even pel sample / 1 : Odd pel sample)
	UINT32 resvd2                           :23;
	};
}PE_O20_REG_GAV_OBUF_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017900 RW
	UINT32 reg_csc_in_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017904 RW
	UINT32 r_csc_in_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_in_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017908 RW
	UINT32 r_csc_in_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_in_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901790C RW
	UINT32 r_csc_in_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_in_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017910 RW
	UINT32 r_csc_in_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_in_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017914 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc_in_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017918 RW
	UINT32 r_csc_in_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_in_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901791C RW
	UINT32 r_csc_in_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_in_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017920 RW
	UINT32 r_csc_in_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_in_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_IN_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017940 RW
	UINT32 reg_csc_out_en                   :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017944 RW
	UINT32 r_csc_out_coef1                  :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_out_coef0                  :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017948 RW
	UINT32 r_csc_out_coef3                  :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_out_coef2                  :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901794C RW
	UINT32 r_csc_out_coef5                  :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_out_coef4                  :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017950 RW
	UINT32 r_csc_out_coef7                  :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc_out_coef6                  :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017954 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc_out_coef8                  :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017958 RW
	UINT32 r_csc_out_ofst1                  :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_out_ofst0                  :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901795C RW
	UINT32 r_csc_out_ofst3                  :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_out_ofst2                  :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017960 RW
	UINT32 r_csc_out_ofst5                  :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc_out_ofst4                  :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017970 RW
	UINT32 reg_alpha_hue                    :10;	//9:0	//Hue Alpha
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//25:16	//Saturation Alpha
	UINT32 resvd1                           :2;
	UINT32 reg_hue_sat_prsv_en              :1;	//28 //Hue / Saturation Preserve Enable
	UINT32 resvd2                           :3;
	};
}PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017974 RW
	UINT32 reg_alpha_ii_yy_coef0            :15;	//14:0	//alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//16 //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017978 RW
	UINT32 reg_alpha_ii_yy_coef2            :15;	//14:0	//alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//30:16	//alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017980 RW
	UINT32 reg_pcc_en                       :1;	//0 //PCC32 Enable
	UINT32 resvd0                           :3;
	UINT32 reg_pcc_gamma_en                 :1;	//4 //PCC32 gamma Enable
	UINT32 resvd1                           :3;
	UINT32 reg_pcc_degamma_en               :1;	//8 //PCC32 degamma Enable
	UINT32 resvd2                           :23;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017984 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017988 RW
	UINT32 r_pcc_coef1                      :15;	//14:0	//PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//30:16	//PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901798C RW
	UINT32 r_pcc_coef3                      :15;	//14:0	//PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//30:16	//PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017990 RW
	UINT32 r_pcc_coef5                      :15;	//14:0	//PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//30:16	//PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017994 RW
	UINT32 r_pcc_coef7                      :15;	//14:0	//PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//30:16	//PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017998 RW
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_O20_REG_GAV_HDR_PCC_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A00 RW
	UINT32 tcm00_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A04 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A08 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A0C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A10 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A14 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A18 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A1C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM00_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A20 RW
	UINT32 tcm01_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A24 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A28 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A2C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A30 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A34 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A38 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A3C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM01_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A40 RW
	UINT32 tcm02_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A44 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A48 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A4C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A50 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A54 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A58 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A5C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM02_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A60 RW
	UINT32 tcm10_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A64 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A68 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A6C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A70 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A74 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A78 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A7C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM10_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A80 RW
	UINT32 tcm11_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A84 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A88 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A8C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A90 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A94 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A98 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017A9C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM11_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AA0 RW
	UINT32 tcm12_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AA4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AA8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AAC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AB0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AB4 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AB8 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017ABC RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM12_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AC0 RW
	UINT32 tcm20_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AC4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AC8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017ACC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AD0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AD4 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AD8 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017ADC RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM20_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AE0 RW
	UINT32 tcm21_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AE4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AE8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AEC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AF0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AF4 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AF8 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017AFC RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM21_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B00 RW
	UINT32 tcm22_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B04 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B08 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B0C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B10 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B14 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B18 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B1C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM22_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B20 RW
	UINT32 tcm30_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B24 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B28 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B2C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B30 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B34 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B38 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B3C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM30_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B40 RW
	UINT32 tcm31_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B44 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B48 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B4C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B50 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B54 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B58 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B5C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM31_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B60 RW
	UINT32 tcm32_lut_enable                 :1;	//0 //LUT enable
	UINT32 resvd0                           :3;
	UINT32 window01_enable                  :1;	//4 //1: window0 and window1 area only
	UINT32 window0_enable                   :1;	//5 //1: window0 area only
	UINT32 window1_enable                   :1;	//6 //1: window1 area only
	UINT32 window_acquire                   :1;	//7 //1: update window from CTRL_01~CTRL04
	UINT32 window_mode_enable               :1;	//8 //1: window mode enable
	UINT32 resvd1                           :7;
	UINT32 window_inout_sel                 :1;	//16 //0: selected area by window0/window1, 1: outside
	UINT32 resvd2                           :15;
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B64 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B68 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B6C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B70 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B74 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :10;	//9:0	//Y coordinate of 33rd control point (Default : 512)
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x_33rd       :10;	//25:16	//X coordinate of 33rd control point (Default : 1023)
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B78 RW
	UINT32 hif_ygain_lut_address            :4;	//3:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 resvd0                           :4;
	UINT32 hif_ygain_lut_load               :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd1                           :2;
	UINT32 hif_ygain_lut_manual_load_en     :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_ygain_lut_ai                 :1;	//12 //auto increment enable	1: enable
	UINT32 resvd2                           :2;
	UINT32 hif_ygain_lut_enable             :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd3                           :16;
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017B7C RW
	UINT32 hif_ygain_lut_wdata_y            :10;	//9:0	//Y coordinate of control point
	UINT32 resvd0                           :6;
	UINT32 hif_ygain_lut_wdata_x            :10;	//25:16	//X coordinate of control point
	UINT32 resvd1                           :6;
	};
}PE_O20_REG_GAV_HDR_TCM32_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017BA0 RO
	UINT32 dbg_c_out_line_cnt               :16;	//15:0	//c out line count
	UINT32 dbg_y_out_line_cnt               :16;	//31:16	//y out line count
	};
}PE_O20_REG_GAV_HDR_DBG_LINE_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017BA4 RO
	UINT32 dbg_frame_cnt                    :8;	//7:0	//frame out count
	UINT32 resvd                            :24;
	};
}PE_O20_REG_GAV_HDR_DBG_FRAME_CNT_T;

typedef struct {
	PE_O20_REG_GAV_HDR_PIC_SIZE_T                             hdr_pic_size;	//0xC9017800
	PE_O20_REG_GAV_HDR_BUF_CTRL0_T                           hdr_buf_ctrl0;	//0xC9017804
	PE_O20_REG_GAV_BUF_CTRL1_T                                   buf_ctrl1;	//0xC9017808
	PE_O20_REG_GAV_OBUF_CTRL0_T                                 obuf_ctrl0;	//0xC901780C
	UINT32                                                       reserved0;	//0xC9017810
	UINT32                                                       reserved1;	//0xC9017814
	UINT32                                                       reserved2;	//0xC9017818
	UINT32                                                       reserved3;	//0xC901781C
	UINT32                                                       reserved4;	//0xC9017820
	UINT32                                                       reserved5;	//0xC9017824
	UINT32                                                       reserved6;	//0xC9017828
	UINT32                                                       reserved7;	//0xC901782C
	UINT32                                                       reserved8;	//0xC9017830
	UINT32                                                       reserved9;	//0xC9017834
	UINT32                                                      reserved10;	//0xC9017838
	UINT32                                                      reserved11;	//0xC901783C
	UINT32                                                      reserved12;	//0xC9017840
	UINT32                                                      reserved13;	//0xC9017844
	UINT32                                                      reserved14;	//0xC9017848
	UINT32                                                      reserved15;	//0xC901784C
	UINT32                                                      reserved16;	//0xC9017850
	UINT32                                                      reserved17;	//0xC9017854
	UINT32                                                      reserved18;	//0xC9017858
	UINT32                                                      reserved19;	//0xC901785C
	UINT32                                                      reserved20;	//0xC9017860
	UINT32                                                      reserved21;	//0xC9017864
	UINT32                                                      reserved22;	//0xC9017868
	UINT32                                                      reserved23;	//0xC901786C
	UINT32                                                      reserved24;	//0xC9017870
	UINT32                                                      reserved25;	//0xC9017874
	UINT32                                                      reserved26;	//0xC9017878
	UINT32                                                      reserved27;	//0xC901787C
	UINT32                                                      reserved28;	//0xC9017880
	UINT32                                                      reserved29;	//0xC9017884
	UINT32                                                      reserved30;	//0xC9017888
	UINT32                                                      reserved31;	//0xC901788C
	UINT32                                                      reserved32;	//0xC9017890
	UINT32                                                      reserved33;	//0xC9017894
	UINT32                                                      reserved34;	//0xC9017898
	UINT32                                                      reserved35;	//0xC901789C
	UINT32                                                      reserved36;	//0xC90178A0
	UINT32                                                      reserved37;	//0xC90178A4
	UINT32                                                      reserved38;	//0xC90178A8
	UINT32                                                      reserved39;	//0xC90178AC
	UINT32                                                      reserved40;	//0xC90178B0
	UINT32                                                      reserved41;	//0xC90178B4
	UINT32                                                      reserved42;	//0xC90178B8
	UINT32                                                      reserved43;	//0xC90178BC
	UINT32                                                      reserved44;	//0xC90178C0
	UINT32                                                      reserved45;	//0xC90178C4
	UINT32                                                      reserved46;	//0xC90178C8
	UINT32                                                      reserved47;	//0xC90178CC
	UINT32                                                      reserved48;	//0xC90178D0
	UINT32                                                      reserved49;	//0xC90178D4
	UINT32                                                      reserved50;	//0xC90178D8
	UINT32                                                      reserved51;	//0xC90178DC
	UINT32                                                      reserved52;	//0xC90178E0
	UINT32                                                      reserved53;	//0xC90178E4
	UINT32                                                      reserved54;	//0xC90178E8
	UINT32                                                      reserved55;	//0xC90178EC
	UINT32                                                      reserved56;	//0xC90178F0
	UINT32                                                      reserved57;	//0xC90178F4
	UINT32                                                      reserved58;	//0xC90178F8
	UINT32                                                      reserved59;	//0xC90178FC
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_00_T                 hdr_csc_in_ctrl_00;	//0xC9017900
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_01_T                 hdr_csc_in_ctrl_01;	//0xC9017904
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_02_T                 hdr_csc_in_ctrl_02;	//0xC9017908
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_03_T                 hdr_csc_in_ctrl_03;	//0xC901790C
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_04_T                 hdr_csc_in_ctrl_04;	//0xC9017910
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_05_T                 hdr_csc_in_ctrl_05;	//0xC9017914
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_06_T                 hdr_csc_in_ctrl_06;	//0xC9017918
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_07_T                 hdr_csc_in_ctrl_07;	//0xC901791C
	PE_O20_REG_GAV_HDR_CSC_IN_CTRL_08_T                 hdr_csc_in_ctrl_08;	//0xC9017920
	UINT32                                                      reserved60;	//0xC9017924
	UINT32                                                      reserved61;	//0xC9017928
	UINT32                                                      reserved62;	//0xC901792C
	UINT32                                                      reserved63;	//0xC9017930
	UINT32                                                      reserved64;	//0xC9017934
	UINT32                                                      reserved65;	//0xC9017938
	UINT32                                                      reserved66;	//0xC901793C
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_00_T               hdr_csc_out_ctrl_00;	//0xC9017940
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_01_T               hdr_csc_out_ctrl_01;	//0xC9017944
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_02_T               hdr_csc_out_ctrl_02;	//0xC9017948
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_03_T               hdr_csc_out_ctrl_03;	//0xC901794C
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_04_T               hdr_csc_out_ctrl_04;	//0xC9017950
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_05_T               hdr_csc_out_ctrl_05;	//0xC9017954
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_06_T               hdr_csc_out_ctrl_06;	//0xC9017958
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_07_T               hdr_csc_out_ctrl_07;	//0xC901795C
	PE_O20_REG_GAV_HDR_CSC_OUT_CTRL_08_T               hdr_csc_out_ctrl_08;	//0xC9017960
	UINT32                                                      reserved67;	//0xC9017964
	UINT32                                                      reserved68;	//0xC9017968
	UINT32                                                      reserved69;	//0xC901796C
	PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_00_T               hdr_hue_sat_ctrl_00;	//0xC9017970
	PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_01_T               hdr_hue_sat_ctrl_01;	//0xC9017974
	PE_O20_REG_GAV_HDR_HUE_SAT_CTRL_02_T               hdr_hue_sat_ctrl_02;	//0xC9017978
	UINT32                                                      reserved70;	//0xC901797C
	PE_O20_REG_GAV_HDR_PCC_CTRL_00_T                       hdr_pcc_ctrl_00;	//0xC9017980
	PE_O20_REG_GAV_HDR_PCC_CTRL_01_T                       hdr_pcc_ctrl_01;	//0xC9017984
	PE_O20_REG_GAV_HDR_PCC_CTRL_02_T                       hdr_pcc_ctrl_02;	//0xC9017988
	PE_O20_REG_GAV_HDR_PCC_CTRL_03_T                       hdr_pcc_ctrl_03;	//0xC901798C
	PE_O20_REG_GAV_HDR_PCC_CTRL_04_T                       hdr_pcc_ctrl_04;	//0xC9017990
	PE_O20_REG_GAV_HDR_PCC_CTRL_05_T                       hdr_pcc_ctrl_05;	//0xC9017994
	PE_O20_REG_GAV_HDR_PCC_CTRL_06_T                       hdr_pcc_ctrl_06;	//0xC9017998
	UINT32                                                      reserved71;	//0xC901799C
	UINT32                                                      reserved72;	//0xC90179A0
	UINT32                                                      reserved73;	//0xC90179A4
	UINT32                                                      reserved74;	//0xC90179A8
	UINT32                                                      reserved75;	//0xC90179AC
	UINT32                                                      reserved76;	//0xC90179B0
	UINT32                                                      reserved77;	//0xC90179B4
	UINT32                                                      reserved78;	//0xC90179B8
	UINT32                                                      reserved79;	//0xC90179BC
	UINT32                                                      reserved80;	//0xC90179C0
	UINT32                                                      reserved81;	//0xC90179C4
	UINT32                                                      reserved82;	//0xC90179C8
	UINT32                                                      reserved83;	//0xC90179CC
	UINT32                                                      reserved84;	//0xC90179D0
	UINT32                                                      reserved85;	//0xC90179D4
	UINT32                                                      reserved86;	//0xC90179D8
	UINT32                                                      reserved87;	//0xC90179DC
	UINT32                                                      reserved88;	//0xC90179E0
	UINT32                                                      reserved89;	//0xC90179E4
	UINT32                                                      reserved90;	//0xC90179E8
	UINT32                                                      reserved91;	//0xC90179EC
	UINT32                                                      reserved92;	//0xC90179F0
	UINT32                                                      reserved93;	//0xC90179F4
	UINT32                                                      reserved94;	//0xC90179F8
	UINT32                                                      reserved95;	//0xC90179FC
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_00_T           hdr_tcm00_lut_ctrl_00;	//0xC9017A00
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_01_T           hdr_tcm00_lut_ctrl_01;	//0xC9017A04
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_02_T           hdr_tcm00_lut_ctrl_02;	//0xC9017A08
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_03_T           hdr_tcm00_lut_ctrl_03;	//0xC9017A0C
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_04_T           hdr_tcm00_lut_ctrl_04;	//0xC9017A10
	PE_O20_REG_GAV_HDR_TCM00_LUT_CTRL_05_T           hdr_tcm00_lut_ctrl_05;	//0xC9017A14
	PE_O20_REG_GAV_HDR_TCM00_LUT_IA_CTRL_T           hdr_tcm00_lut_ia_ctrl;	//0xC9017A18
	PE_O20_REG_GAV_HDR_TCM00_LUT_IA_DATA_T           hdr_tcm00_lut_ia_data;	//0xC9017A1C
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_00_T           hdr_tcm01_lut_ctrl_00;	//0xC9017A20
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_01_T           hdr_tcm01_lut_ctrl_01;	//0xC9017A24
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_02_T           hdr_tcm01_lut_ctrl_02;	//0xC9017A28
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_03_T           hdr_tcm01_lut_ctrl_03;	//0xC9017A2C
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_04_T           hdr_tcm01_lut_ctrl_04;	//0xC9017A30
	PE_O20_REG_GAV_HDR_TCM01_LUT_CTRL_05_T           hdr_tcm01_lut_ctrl_05;	//0xC9017A34
	PE_O20_REG_GAV_HDR_TCM01_LUT_IA_CTRL_T           hdr_tcm01_lut_ia_ctrl;	//0xC9017A38
	PE_O20_REG_GAV_HDR_TCM01_LUT_IA_DATA_T           hdr_tcm01_lut_ia_data;	//0xC9017A3C
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_00_T           hdr_tcm02_lut_ctrl_00;	//0xC9017A40
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_01_T           hdr_tcm02_lut_ctrl_01;	//0xC9017A44
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_02_T           hdr_tcm02_lut_ctrl_02;	//0xC9017A48
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_03_T           hdr_tcm02_lut_ctrl_03;	//0xC9017A4C
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_04_T           hdr_tcm02_lut_ctrl_04;	//0xC9017A50
	PE_O20_REG_GAV_HDR_TCM02_LUT_CTRL_05_T           hdr_tcm02_lut_ctrl_05;	//0xC9017A54
	PE_O20_REG_GAV_HDR_TCM02_LUT_IA_CTRL_T           hdr_tcm02_lut_ia_ctrl;	//0xC9017A58
	PE_O20_REG_GAV_HDR_TCM02_LUT_IA_DATA_T           hdr_tcm02_lut_ia_data;	//0xC9017A5C
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_00_T           hdr_tcm10_lut_ctrl_00;	//0xC9017A60
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_01_T           hdr_tcm10_lut_ctrl_01;	//0xC9017A64
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_02_T           hdr_tcm10_lut_ctrl_02;	//0xC9017A68
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_03_T           hdr_tcm10_lut_ctrl_03;	//0xC9017A6C
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_04_T           hdr_tcm10_lut_ctrl_04;	//0xC9017A70
	PE_O20_REG_GAV_HDR_TCM10_LUT_CTRL_05_T           hdr_tcm10_lut_ctrl_05;	//0xC9017A74
	PE_O20_REG_GAV_HDR_TCM10_LUT_IA_CTRL_T           hdr_tcm10_lut_ia_ctrl;	//0xC9017A78
	PE_O20_REG_GAV_HDR_TCM10_LUT_IA_DATA_T           hdr_tcm10_lut_ia_data;	//0xC9017A7C
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_00_T           hdr_tcm11_lut_ctrl_00;	//0xC9017A80
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_01_T           hdr_tcm11_lut_ctrl_01;	//0xC9017A84
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_02_T           hdr_tcm11_lut_ctrl_02;	//0xC9017A88
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_03_T           hdr_tcm11_lut_ctrl_03;	//0xC9017A8C
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_04_T           hdr_tcm11_lut_ctrl_04;	//0xC9017A90
	PE_O20_REG_GAV_HDR_TCM11_LUT_CTRL_05_T           hdr_tcm11_lut_ctrl_05;	//0xC9017A94
	PE_O20_REG_GAV_HDR_TCM11_LUT_IA_CTRL_T           hdr_tcm11_lut_ia_ctrl;	//0xC9017A98
	PE_O20_REG_GAV_HDR_TCM11_LUT_IA_DATA_T           hdr_tcm11_lut_ia_data;	//0xC9017A9C
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_00_T           hdr_tcm12_lut_ctrl_00;	//0xC9017AA0
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_01_T           hdr_tcm12_lut_ctrl_01;	//0xC9017AA4
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_02_T           hdr_tcm12_lut_ctrl_02;	//0xC9017AA8
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_03_T           hdr_tcm12_lut_ctrl_03;	//0xC9017AAC
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_04_T           hdr_tcm12_lut_ctrl_04;	//0xC9017AB0
	PE_O20_REG_GAV_HDR_TCM12_LUT_CTRL_05_T           hdr_tcm12_lut_ctrl_05;	//0xC9017AB4
	PE_O20_REG_GAV_HDR_TCM12_LUT_IA_CTRL_T           hdr_tcm12_lut_ia_ctrl;	//0xC9017AB8
	PE_O20_REG_GAV_HDR_TCM12_LUT_IA_DATA_T           hdr_tcm12_lut_ia_data;	//0xC9017ABC
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_00_T           hdr_tcm20_lut_ctrl_00;	//0xC9017AC0
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_01_T           hdr_tcm20_lut_ctrl_01;	//0xC9017AC4
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_02_T           hdr_tcm20_lut_ctrl_02;	//0xC9017AC8
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_03_T           hdr_tcm20_lut_ctrl_03;	//0xC9017ACC
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_04_T           hdr_tcm20_lut_ctrl_04;	//0xC9017AD0
	PE_O20_REG_GAV_HDR_TCM20_LUT_CTRL_05_T           hdr_tcm20_lut_ctrl_05;	//0xC9017AD4
	PE_O20_REG_GAV_HDR_TCM20_LUT_IA_CTRL_T           hdr_tcm20_lut_ia_ctrl;	//0xC9017AD8
	PE_O20_REG_GAV_HDR_TCM20_LUT_IA_DATA_T           hdr_tcm20_lut_ia_data;	//0xC9017ADC
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_00_T           hdr_tcm21_lut_ctrl_00;	//0xC9017AE0
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_01_T           hdr_tcm21_lut_ctrl_01;	//0xC9017AE4
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_02_T           hdr_tcm21_lut_ctrl_02;	//0xC9017AE8
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_03_T           hdr_tcm21_lut_ctrl_03;	//0xC9017AEC
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_04_T           hdr_tcm21_lut_ctrl_04;	//0xC9017AF0
	PE_O20_REG_GAV_HDR_TCM21_LUT_CTRL_05_T           hdr_tcm21_lut_ctrl_05;	//0xC9017AF4
	PE_O20_REG_GAV_HDR_TCM21_LUT_IA_CTRL_T           hdr_tcm21_lut_ia_ctrl;	//0xC9017AF8
	PE_O20_REG_GAV_HDR_TCM21_LUT_IA_DATA_T           hdr_tcm21_lut_ia_data;	//0xC9017AFC
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_00_T           hdr_tcm22_lut_ctrl_00;	//0xC9017B00
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_01_T           hdr_tcm22_lut_ctrl_01;	//0xC9017B04
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_02_T           hdr_tcm22_lut_ctrl_02;	//0xC9017B08
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_03_T           hdr_tcm22_lut_ctrl_03;	//0xC9017B0C
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_04_T           hdr_tcm22_lut_ctrl_04;	//0xC9017B10
	PE_O20_REG_GAV_HDR_TCM22_LUT_CTRL_05_T           hdr_tcm22_lut_ctrl_05;	//0xC9017B14
	PE_O20_REG_GAV_HDR_TCM22_LUT_IA_CTRL_T           hdr_tcm22_lut_ia_ctrl;	//0xC9017B18
	PE_O20_REG_GAV_HDR_TCM22_LUT_IA_DATA_T           hdr_tcm22_lut_ia_data;	//0xC9017B1C
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_00_T           hdr_tcm30_lut_ctrl_00;	//0xC9017B20
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_01_T           hdr_tcm30_lut_ctrl_01;	//0xC9017B24
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_02_T           hdr_tcm30_lut_ctrl_02;	//0xC9017B28
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_03_T           hdr_tcm30_lut_ctrl_03;	//0xC9017B2C
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_04_T           hdr_tcm30_lut_ctrl_04;	//0xC9017B30
	PE_O20_REG_GAV_HDR_TCM30_LUT_CTRL_05_T           hdr_tcm30_lut_ctrl_05;	//0xC9017B34
	PE_O20_REG_GAV_HDR_TCM30_LUT_IA_CTRL_T           hdr_tcm30_lut_ia_ctrl;	//0xC9017B38
	PE_O20_REG_GAV_HDR_TCM30_LUT_IA_DATA_T           hdr_tcm30_lut_ia_data;	//0xC9017B3C
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_00_T           hdr_tcm31_lut_ctrl_00;	//0xC9017B40
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_01_T           hdr_tcm31_lut_ctrl_01;	//0xC9017B44
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_02_T           hdr_tcm31_lut_ctrl_02;	//0xC9017B48
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_03_T           hdr_tcm31_lut_ctrl_03;	//0xC9017B4C
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_04_T           hdr_tcm31_lut_ctrl_04;	//0xC9017B50
	PE_O20_REG_GAV_HDR_TCM31_LUT_CTRL_05_T           hdr_tcm31_lut_ctrl_05;	//0xC9017B54
	PE_O20_REG_GAV_HDR_TCM31_LUT_IA_CTRL_T           hdr_tcm31_lut_ia_ctrl;	//0xC9017B58
	PE_O20_REG_GAV_HDR_TCM31_LUT_IA_DATA_T           hdr_tcm31_lut_ia_data;	//0xC9017B5C
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_00_T           hdr_tcm32_lut_ctrl_00;	//0xC9017B60
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_01_T           hdr_tcm32_lut_ctrl_01;	//0xC9017B64
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_02_T           hdr_tcm32_lut_ctrl_02;	//0xC9017B68
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_03_T           hdr_tcm32_lut_ctrl_03;	//0xC9017B6C
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_04_T           hdr_tcm32_lut_ctrl_04;	//0xC9017B70
	PE_O20_REG_GAV_HDR_TCM32_LUT_CTRL_05_T           hdr_tcm32_lut_ctrl_05;	//0xC9017B74
	PE_O20_REG_GAV_HDR_TCM32_LUT_IA_CTRL_T           hdr_tcm32_lut_ia_ctrl;	//0xC9017B78
	PE_O20_REG_GAV_HDR_TCM32_LUT_IA_DATA_T           hdr_tcm32_lut_ia_data;	//0xC9017B7C
	UINT32                                                      reserved96;	//0xC9017B80
	UINT32                                                      reserved97;	//0xC9017B84
	UINT32                                                      reserved98;	//0xC9017B88
	UINT32                                                      reserved99;	//0xC9017B8C
	UINT32                                                     reserved100;	//0xC9017B90
	UINT32                                                     reserved101;	//0xC9017B94
	UINT32                                                     reserved102;	//0xC9017B98
	UINT32                                                     reserved103;	//0xC9017B9C
	PE_O20_REG_GAV_HDR_DBG_LINE_CNT_T                     hdr_dbg_line_cnt;	//0xC9017BA0
	PE_O20_REG_GAV_HDR_DBG_FRAME_CNT_T                   hdr_dbg_frame_cnt;	//0xC9017BA4
}PE_O20_REG_GAV_T;

#endif

