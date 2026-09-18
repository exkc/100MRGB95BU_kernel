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
#ifndef _PE_HDR_REG_E60A0_H_
#define _PE_HDR_REG_E60A0_H_
#ifndef UINT32
typedef unsigned int UINT32;
#endif

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C00 RW
	UINT32 load_time                        :1;	//0 //0: load at vdpulse	1: load when reg. write
	UINT32 load_enable                      :1;	//1 //enable reg. loading to local block, auto-cleared
	UINT32 load_type                        :1;	//2 //0: auto load:  load when reg. write	1: manual load: load w/ load_enable = '1'
	UINT32 resvd                            :29;
	};
}PE_E60_REG_H10_TOP_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C04 RW
	UINT32 width                            :16;	//15:0	//width
	UINT32 height                           :16;	//31:16	//height
	};
}PE_E60_REG_H10_TOP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C08 RW
	UINT32 vdpulse_pos                      :32;	//31:0	//vdpulse position for register loading
	};
}PE_E60_REG_H10_TOP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C0C RO
	UINT32 vcnt                             :16;	//15:0	//vertical line count
	UINT32 vcnt2                            :16;	//31:16	//vertical line number
	};
}PE_E60_REG_H10_TOP_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C10 RO
	UINT32 r_to_cnt                         :12;	//11:0	//apb time out count threshold
	UINT32 resvd                            :18;
	UINT32 va_pe1_in                        :1;	//30 //Vertical Active at PE1 input(Read only)
	UINT32 va_pe1_out                       :1;	//31 //Vertical Active at PE1 output(Read only)
	};
}PE_E60_REG_H10_TOP_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C14 RW
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
}PE_E60_REG_H10_TOP_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C18 RW
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
}PE_E60_REG_H10_TOP_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C1C RW
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
}PE_E60_REG_H10_TOP_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C50 RW
	UINT32 reg_csc1st_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_CSC1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C54 RW
	UINT32 r_csc1st_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C58 RW
	UINT32 r_csc1st_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C5C RW
	UINT32 r_csc1st_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C60 RW
	UINT32 r_csc1st_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C64 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C68 RW
	UINT32 r_csc1st_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C6C RW
	UINT32 r_csc1st_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC1_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C70 RW
	UINT32 r_csc1st_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC1_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C74 RW
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
}PE_E60_REG_H10_CSC1_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C78 RO
	UINT32 ireg_csc_cnt_under               :16;	//15:0	//
	UINT32 ireg_csc_cnt_over                :16;	//31:16	//
	};
}PE_E60_REG_H10_CSC1_ERR_CNT_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C80 RW
	UINT32 r_pxl_rd_dbg_rcr                 :8;	//7:0	//
	UINT32 r_pxl_rd_dbg_bcb                 :8;	//15:8	//
	UINT32 r_pxl_rd_dbg_gyy                 :8;	//23:16	//
	UINT32 r_pxl_rd_mark_en                 :1;	//24 //
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_sel                     :1;	//28 //0: Input RGB Pixel / 1 : Output RGB Pixel
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_PXL_RD_CTRL0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C84 RW
	UINT32 r_pxl_rd_pos_x                   :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 r_pxl_rd_pos_y                   :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_PXL_RD_CTRL1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C88 RO
	UINT32 pxl_read_rcr                     :10;	//9:0	//
	UINT32 pxl_read_bcb                     :10;	//19:10	//
	UINT32 pxl_read_gyy                     :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_PXL_RD_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C90 RW
	UINT32 lut_addr                         :10;	//9:0	//indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//27 //assing '1' to set different LUT for each channel
	UINT32 eotf_lut_color_type              :2;	//29:28	//0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_E60_REG_H10_EOTF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C94 RW
	UINT32 eotf_lut_data                    :32;	//31:0	//32 bit LUT data
	};
}PE_E60_REG_H10_EOTF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C98 RW
	UINT32 lut_addr                         :10;	//9:0	//indirect address
	UINT32 resvd0                           :2;
	UINT32 lut_ai                           :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :14;
	UINT32 reg_use_own_lut_hif              :1;	//27 //assing '1' to set different LUT for each channel
	UINT32 oetf_lut_color_type              :2;	//29:28	//0: write G 1: write B 2: write R
	UINT32 resvd2                           :2;
	};
}PE_E60_REG_H10_OETF_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016C9C RW
	UINT32 oetf_lut_data_o                  :16;	//15:0	//16 bit odd LUT data
	UINT32 oetf_lut_data_e                  :16;	//31:16	//16 bit even LUT data
	};
}PE_E60_REG_H10_OETF_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CA0 RW
	UINT32 reg_pcc_en                       :1;	//0 //PCC32 Enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_PCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CA4 RW
	UINT32 r_pcc_coef1                      :15;	//14:0	//PCC32 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef0                      :15;	//30:16	//PCC32 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_PCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CA8 RW
	UINT32 r_pcc_coef3                      :15;	//14:0	//PCC32 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef2                      :15;	//30:16	//PCC32 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_PCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CAC RW
	UINT32 r_pcc_coef5                      :15;	//14:0	//PCC32 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef4                      :15;	//30:16	//PCC32 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_PCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CB0 RW
	UINT32 r_pcc_coef7                      :15;	//14:0	//PCC32 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_pcc_coef6                      :15;	//30:16	//PCC32 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_PCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CB4 RW
	UINT32 resvd0                           :16;
	UINT32 r_pcc_coef8                      :15;	//30:16	//PCC32 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_PCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CD0 RW
	UINT32 reg_hue_prsv_en                  :1;	//0 //enable pin for hue restoration
	UINT32 reg_sat_prsv_en                  :1;	//1 //enable pin for saturation preserving
	UINT32 resvd0                           :2;
	UINT32 reg_hue_prsv_ratio               :10;	//13:4	//0:bypass, 255:restored hue
	UINT32 resvd1                           :2;
	UINT32 reg_sat_prsv_ratio               :10;	//25:16	//0:bypass, 255:restored sat
	UINT32 resvd2                           :6;
	};
}PE_E60_REG_H10_HUE_SAT_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CD4
	UINT32 reg_inp_l_sel                    :1;	//0 //input hue select bit
	UINT32 resvd0                           :3;
	UINT32 reg_inp_s_sel                    :1;	//4 //input saturation select bit
	UINT32 resvd1                           :3;
	UINT32 reg_out_lgain_sel                :1;	//8 //output hue select bit
	UINT32 resvd2                           :3;
	UINT32 reg_out_sgain_sel                :1;	//12 //output saturation select bit
	UINT32 resvd3                           :19;
	};
}PE_E60_REG_H10_HUE_SAT_ALPHA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CE0 RW
	UINT32 r_tone_map_rgb2y_coef1           :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_tone_map_rgb2y_coef0           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_TCM_PREP_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CE4 RW
	UINT32 r_tone_map_rgbymax_sel           :3;	//2:0	//
	UINT32 resvd0                           :13;
	UINT32 r_tone_map_rgb2y_coef2           :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_TCM_PREP_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CE8 RW
	UINT32 ll_lut_addr                      :7;	//6:0	//indirect address
	UINT32 resvd0                           :1;
	UINT32 ll_lut_load                      :1;	//8 //indirect memory load enable
	UINT32 resvd1                           :3;
	UINT32 ll_lut_ai                        :1;	//12 //auto increment of indirect address
	UINT32 resvd2                           :19;
	};
}PE_E60_REG_H10_LL_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CEC RW
	UINT32 ll_lut_dat_rcr                   :10;	//9:0	//Low Level LUT R 10bit
	UINT32 ll_lut_dat_bcb                   :10;	//19:10	//Low Level LUT B 10bit
	UINT32 ll_lut_dat_gyy                   :10;	//29:20	//Low Level LUT G 10bit
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_LL_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CF0 RW
	UINT32 reg_alpha_hue                    :10;	//9:0	//alpha for hue
	UINT32 resvd0                           :6;
	UINT32 reg_alpha_sat                    :10;	//25:16	//alpha for saturation
	UINT32 resvd1                           :2;
	UINT32 hue_sat_10b_prsv_en              :1;	//28 //10 bit hue satuaration preserve enable
	UINT32 resvd2                           :3;
	};
}PE_E60_REG_H10_LL_HUE_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CF4 RW
	UINT32 reg_alpha_ii_yy_coef0            :15;	//14:0	//alpha blendling RGB -> Y coef
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_blend_lut_in_sel       :1;	//16 //alpha blending selection signal (0: RGB_MAX / 1 : Y)
	UINT32 resvd1                           :15;
	};
}PE_E60_REG_H10_LL_HUE_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016CF8 RW
	UINT32 reg_alpha_ii_yy_coef2            :15;	//14:0	//alpha blendling RGB -> Y coef2
	UINT32 resvd0                           :1;
	UINT32 reg_alpha_ii_yy_coef1            :15;	//30:16	//alpha blendling RGB -> Y coef1
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LL_HUE_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D00 RW
	UINT32 reg_ll_pcc_en                    :1;	//0 //PCC10 Enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_LLPCC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D04 RW
	UINT32 r_ll_pcc_coef1                   :15;	//14:0	//PCC10 Coefficient 1 (Default : -34)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef0                   :15;	//30:16	//PCC10 Coefficient 0 (Default :4640)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LLPCC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D08 RW
	UINT32 r_ll_pcc_coef3                   :15;	//14:0	//PCC10 Coefficient 3 (Default : -412)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef2                   :15;	//30:16	//PCC10 Coefficient 2 (Default : -510)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LLPCC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D0C RW
	UINT32 r_ll_pcc_coef5                   :15;	//14:0	//PCC10 Coefficient 5 (Default : -74)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef4                   :15;	//30:16	//PCC10 Coefficient 4 (Default : 4582)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LLPCC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D10 RW
	UINT32 r_ll_pcc_coef7                   :15;	//14:0	//PCC10 Coefficient 7 (Default : -298)
	UINT32 resvd0                           :1;
	UINT32 r_ll_pcc_coef6                   :15;	//30:16	//PCC10 Coefficient 6 (Default : -240)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LLPCC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D14 RW
	UINT32 resvd0                           :16;
	UINT32 r_ll_pcc_coef8                   :15;	//30:16	//PCC10 Coefficient 8 (Default : 6801)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_LLPCC_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D18 RW
	UINT32 reg_ll_ab_en                     :1;	//0 //Low Level Alpha Blend Enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_LL_AB_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D1C RW
	UINT32 r_ll_ab_lut_x2                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_x1                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_x0                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_LL_AB_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D20 RW
	UINT32 r_ll_ab_lut_x5                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_x4                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_x3                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_LL_AB_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D24 RW
	UINT32 r_ll_ab_lut_y2                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_y1                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_y0                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_LL_AB_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D28 RW
	UINT32 r_ll_ab_lut_y5                   :10;	//9:0	//
	UINT32 r_ll_ab_lut_y4                   :10;	//19:10	//
	UINT32 r_ll_ab_lut_y3                   :10;	//29:20	//
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_LL_AB_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D40 RW
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
}PE_E60_REG_H10_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D44 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_H10_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D48 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_H10_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D4C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_H10_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D50 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_H10_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D54 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
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
}PE_E60_REG_H10_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D58 RW
	UINT32 hist_status0                     :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_E60_REG_H10_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D5C RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_E60_REG_H10_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D60 RW
	UINT32 hif_hist_address                 :5;	//4:0	//"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
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
}PE_E60_REG_H10_C4_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D64 RW
	UINT32 c4_hist_status0                  :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_E60_REG_H10_C4_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D68 RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_E60_REG_H10_C4_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D70 RW
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
}PE_E60_REG_H10_TPG_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D74 RW
	UINT32 tpg_size_x                       :14;	//13:0	//tpg_size_x
	UINT32 resvd0                           :2;
	UINT32 tpg_size_y                       :13;	//28:16	//tpg_size_y
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_TPG_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D78 RW
	UINT32 tpg_mask_flag                    :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_TPG_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D7C RW
	UINT32 tpg_in_out_sel                   :16;	//15:0	//in_out_sel
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_TPG_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D80 RW
	UINT32 tpg_color_r                      :10;	//9:0	//tpg_color_r
	UINT32 tpg_color_b                      :10;	//19:10	//tpg_color_b
	UINT32 tpg_color_g                      :10;	//29:20	//tpg_color_g
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_TPG_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D84 RW
	UINT32 hif_tpg_address                  :8;	//7:0	//cp mode     	"0"   : 0th   X, Y	"1"   : 1st   X, Y	...	"31" : 31st X, Y
	UINT32 hif_tpg_load                     :1;	//8 //write done of dce register (auto cleared)
	UINT32 resvd0                           :2;
	UINT32 hif_tpg_manual_load_en           :1;	//11 //1: update immediately, 0: update when va is falling
	UINT32 hif_tpg_ai                       :1;	//12 //auto increment enable	1: enable
	UINT32 resvd1                           :2;
	UINT32 hif_tpg_enable                   :1;	//15 //0: host access(read/write)	1: normal operation
	UINT32 resvd2                           :16;
	};
}PE_E60_REG_H10_TPG_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D88 RW
	UINT32 hif_tpg_wdata_y                  :16;	//15:0	//Y coordinate of control point
	UINT32 hif_tpg_wdata_x                  :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_H10_TPG_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D90 RW
	UINT32 reg_clut_65th_data               :11;	//10:0	//65th_data
	UINT32 resvd                            :21;
	};
}PE_E60_REG_H10_CLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D94 RW
	UINT32 clut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 clut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 clut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_E60_REG_H10_CLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D98 RW
	UINT32 clut_data                        :11;	//10:0	//data for CLUT
	UINT32 resvd                            :21;
	};
}PE_E60_REG_H10_CLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016D9C RW
	UINT32 reg_plut_65th_data               :14;	//13:0	//65th_data
	UINT32 resvd                            :18;
	};
}PE_E60_REG_H10_PLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DA0 RW
	UINT32 plut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 plut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 plut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_E60_REG_H10_PLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DA4 RW
	UINT32 plut_data                        :14;	//13:0	//data for PLUT
	UINT32 resvd                            :18;
	};
}PE_E60_REG_H10_PLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DA8 RW
	UINT32 reg_slut_65th_data               :10;	//9:0	//65th_data
	UINT32 resvd                            :22;
	};
}PE_E60_REG_H10_SLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DAC RW
	UINT32 slut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 slut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 slut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_E60_REG_H10_SLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DB0 RW
	UINT32 slut_data                        :10;	//9:0	//data for SLUT
	UINT32 resvd                            :22;
	};
}PE_E60_REG_H10_SLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DB4 RW
	UINT32 reg_ilut_65th_data               :8;	//7:0	//65th_data
	UINT32 resvd                            :24;
	};
}PE_E60_REG_H10_ILUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DB8 RW
	UINT32 ilut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 ilut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 ilut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_E60_REG_H10_ILUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DBC RW
	UINT32 ilut_data                        :8;	//7:0	//data for ILUT
	UINT32 resvd                            :24;
	};
}PE_E60_REG_H10_ILUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DC0 RW
	UINT32 reg_dlut_65th_data               :12;	//11:0	//65th_data
	UINT32 resvd0                           :4;
	UINT32 reg_dlut_threshold_0             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DC4 RW
	UINT32 reg_dlut_threshold_1             :13;	//12:0	//
	UINT32 resvd0                           :3;
	UINT32 reg_dlut_threshold_2             :13;	//28:16	//
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DC8 RW
	UINT32 reg_dlut_step_0                  :4;	//3:0	//
	UINT32 reg_dlut_step_1                  :4;	//7:4	//
	UINT32 reg_dlut_step_2                  :4;	//11:8	//
	UINT32 reg_dlut_step_3                  :4;	//15:12	//
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DCC RW
	UINT32 dlut_addr                        :6;	//5:0	//indirect address
	UINT32 resvd0                           :6;
	UINT32 dlut_ai                          :1;	//12 //auto increment of indirect address
	UINT32 resvd1                           :16;
	UINT32 dlut_manual_load_en              :1;	//29 //1: update immediately, 0: update when va is falling
	UINT32 reg_write_mode_en                :1;	//30 //assing '1' before LUT wr
	UINT32 reg_lut_wr_done                  :1;	//31 //assign '1' when LUT wr is done
	};
}PE_E60_REG_H10_DLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DD0 RW
	UINT32 dlut_data                        :8;	//7:0	//data for DLUT
	UINT32 resvd                            :24;
	};
}PE_E60_REG_H10_DLUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DD4 RW
	UINT32 reg_technicolor_detour_en        :1;	//0 //
	UINT32 resvd0                           :3;
	UINT32 reg_range_sel                    :1;	//4 //0':limited range, '1':full range
	UINT32 resvd1                           :27;
	};
}PE_E60_REG_H10_TC_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DD8 RW
	UINT32 reg_alpha_a                      :13;	//12:0	//default value : 7936
	UINT32 resvd0                           :3;
	UINT32 reg_alpha_b                      :13;	//28:16	//default value : 7680
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_H10_TC_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DDC RW
	UINT32 reg_oct_0                        :6;	//5:0	//unsigned 6 bit
	UINT32 resvd0                           :4;
	UINT32 reg_oct_1                        :8;	//17:10	//signed 8 bit
	UINT32 resvd1                           :2;
	UINT32 reg_oct_2                        :9;	//28:20	//signed 9 bit
	UINT32 resvd2                           :3;
	};
}PE_E60_REG_H10_TC_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DE0 RW
	UINT32 reg_oct_3                        :10;	//9:0	//signed 10 bit
	UINT32 reg_oct_4                        :10;	//19:10	//signed 10 bit
	UINT32 reg_oct_5                        :10;	//29:20	//signed 10 bit
	UINT32 resvd                            :2;
	};
}PE_E60_REG_H10_TC_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016DE4 RW
	UINT32 reg_oct_6                        :10;	//9:0	//signed 10 bit
	UINT32 resvd                            :22;
	};
}PE_E60_REG_H10_TC_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E00 RW
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
}PE_E60_REG_H10_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E04 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_H10_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E08 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_H10_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E0C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_H10_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E10 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_H10_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E14 RW
	UINT32 hif_llut0_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
}PE_E60_REG_H10_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E18 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_LLUT0_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E20 RW
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
}PE_E60_REG_H10_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E24 RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_H10_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E30 RW
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
}PE_E60_REG_H10_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E34 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_H10_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E38 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_H10_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E3C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_H10_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E40 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_H10_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E44 RW
	UINT32 hif_llut1_wdata_x_33rd           :32;	//31:0	//X coordinate of 33rd control point
	};
}PE_E60_REG_H10_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E48 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_LLUT1_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E50 RW
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
}PE_E60_REG_H10_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E54 RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_H10_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E60 RW
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
}PE_E60_REG_H10_LLUT2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E64 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_H10_LLUT2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E68 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_H10_LLUT2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E6C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_H10_LLUT2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E70 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_H10_LLUT2_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E74 RW
	UINT32 resvd                            :16;
	UINT32 hif_llut2_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_E60_REG_H10_LLUT2_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E78 RW
	UINT32 hif_llut2_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_LLUT2_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E80 RW
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
}PE_E60_REG_H10_LLUT2_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E84 RW
	UINT32 hif_llut2_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut2_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_H10_LLUT2_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E90 RW
	UINT32 gamma045_enable                  :1;	//0 //gamma 0.45(1/2.2) enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_GAMMA045_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E98 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_E60_REG_H10_DITHER_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016E9C RW
	UINT32 hif_pcc32_ygain_shift            :1;	//0 //0: shift 12 bit / 1: shift 13 bit
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_PCC32_GAIN_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EA0 RW
	UINT32 reg_csc3rd_en                    :1;	//0 //CSC3rd RGB -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_CSC3_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EA4 RW
	UINT32 r_csc3rd_coef1                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef0                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC3_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EA8 RW
	UINT32 r_csc3rd_coef3                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef2                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC3_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EAC RW
	UINT32 r_csc3rd_coef5                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef4                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC3_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EB0 RW
	UINT32 r_csc3rd_coef7                   :15;	//14:0	//CSC3rd RGB -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc3rd_coef6                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC3_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EB4 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc3rd_coef8                   :15;	//30:16	//CSC3rd RGB -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC3_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EB8 RW
	UINT32 r_csc3rd_ofst1                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst0                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC3_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EBC RW
	UINT32 r_csc3rd_ofst3                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst2                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC3_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EC0 RW
	UINT32 r_csc3rd_ofst5                   :11;	//10:0	//CSC3rd RGB -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc3rd_ofst4                   :11;	//26:16	//CSC3rd RGB -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC3_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016ED0 RW
	UINT32 r_slut0_x0                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016ED4 RW
	UINT32 r_slut0_x1                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016ED8 RW
	UINT32 r_slut0_x2                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EDC RW
	UINT32 r_slut0_x3                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EE0 RW
	UINT32 r_slut0_x4                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EE4 RW
	UINT32 r_slut0_x5                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EE8 RW
	UINT32 r_slut0_x6                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EEC RW
	UINT32 r_slut0_x7                       :32;	//31:00	//
	};
}PE_E60_REG_H10_TCM_SLUT0_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EF0 RW
	UINT32 r_slut0_y0                       :8;	//7:0	//
	UINT32 r_slut0_y1                       :8;	//15:8	//
	UINT32 r_slut0_y2                       :8;	//23:16	//
	UINT32 r_slut0_y3                       :8;	//31:24	//
	};
}PE_E60_REG_H10_TCM_SLUT0_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EF4 RW
	UINT32 r_slut0_y4                       :8;	//7:0	//
	UINT32 r_slut0_y5                       :8;	//15:8	//
	UINT32 r_slut0_y6                       :8;	//23:16	//
	UINT32 r_slut0_y7                       :8;	//31:24	//
	};
}PE_E60_REG_H10_TCM_SLUT0_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EF8 RW
	UINT32 reg_tm_m2020_coef13              :15;	//14:0	//TM0 M2020 Coef 3x3 matrix (1,3) value
	UINT32 resvd                            :1;
	UINT32 reg_tm_m2020_coef22              :15;	//30:16	//TM0 M2020 Coef 3x3 matrix (2,2) value
	UINT32 sat_gain_en                      :1;	//31 //TM0 Saturation Gain Enable
	};
}PE_E60_REG_H10_SAT_MAP_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016EFC RW
	UINT32 reg_tm_m2020_coef23              :15;	//14:0	//TM0 M2020 Coef 3x3 matrix (2,3) value
	UINT32 resvd0                           :1;
	UINT32 reg_tm_m2020_coef32              :15;	//30:16	//TM0 M2020 Coef 3x3 matrix (3,2) value
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_SAT_MAP_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F00 RW
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
}PE_E60_REG_H10_3DLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F04 RW
	UINT32 reg_3d_lut_th_min0               :16;	//15:0	//
	UINT32 resvd                            :16;
	};
}PE_E60_REG_H10_3DLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F08 RW
	UINT32 reg_3d_lut_th_min1               :16;	//15:0	//
	UINT32 reg_3d_lut_th_min2               :16;	//31:16	//
	};
}PE_E60_REG_H10_3DLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F0C RW
	UINT32 reg_3d_lut_th_max0               :16;	//15:0	//
	UINT32 reg_3d_lut_th_max1               :16;	//31:16	//
	};
}PE_E60_REG_H10_3DLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F10 RW
	UINT32 reg_3d_lut_diff_maxmin0          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_E60_REG_H10_3DLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F14 RW
	UINT32 reg_3d_lut_diff_maxmin1          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_E60_REG_H10_3DLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F18 RW
	UINT32 reg_3d_lut_diff_maxmin2          :20;	//19:0	//
	UINT32 resvd                            :12;
	};
}PE_E60_REG_H10_3DLUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F1C RW
	UINT32 reg_3d_lut_manual_qtt            :21;	//20:0	//
	UINT32 resvd                            :11;
	};
}PE_E60_REG_H10_3DLUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F20 RW
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
}PE_E60_REG_H10_YGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F24 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_H10_YGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F28 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_H10_YGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F2C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_H10_YGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F30 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_H10_YGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F34 RW
	UINT32 hif_ygain_lut_wdata_y_33rd       :16;	//15:0	//Y coordinate of 33rd control point (Default : 4096)
	UINT32 hif_ygain_lut_wdata_x_33rd       :16;	//31:16	//X coordinate of 33rd control point (Default : 65535)
	};
}PE_E60_REG_H10_YGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F38 RW
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
}PE_E60_REG_H10_YGAIN_LUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F3C RW
	UINT32 hif_ygain_lut_wdata_y            :16;	//15:0	//Y coordinate of control point
	UINT32 hif_ygain_lut_wdata_x            :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_H10_YGAIN_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F40 RW
	UINT32 reg_rgb2yrd_en                   :1;	//0 //RGB2Y Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//30:16	//RGB2Y Coefficient 0 (Default : 2777)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_RGB2Y_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F44 RW
	UINT32 r_rgb2yrd_coef1                  :15;	//14:0	//RGB2Y Coefficient 1 (Default : 243)
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//31:16	//RGB2Y Coefficient 2 (Default : 1076)
	};
}PE_E60_REG_H10_RGB2Y_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F48 RW
	UINT32 r_rgb2yrd_ofst0                  :17;	//16:0	//RGB2Y Offset 0 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_E60_REG_H10_RGB2Y_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F4C RW
	UINT32 r_rgb2yrd_ofst3                  :17;	//16:0	//RGB2Y Offset 3 (Default : 0)
	UINT32 resvd                            :15;
	};
}PE_E60_REG_H10_RGB2Y_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F60 RW
	UINT32 lgain_lut_y0                     :8;	//7:0	//y value of LGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x0                     :16;	//31:16	//x value of LGAIN LUT point 0
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F64 RW
	UINT32 lgain_lut_y1                     :8;	//7:0	//y value of LGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x1                     :16;	//31:16	//x value of LGAIN LUT point 1
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F68 RW
	UINT32 lgain_lut_y2                     :8;	//7:0	//y value of LGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x2                     :16;	//31:16	//x value of LGAIN LUT point 2
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F6C RW
	UINT32 lgain_lut_y3                     :8;	//7:0	//y value of LGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x3                     :16;	//31:16	//x value of LGAIN LUT point 3
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F70 RW
	UINT32 lgain_lut_y4                     :8;	//7:0	//y value of LGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x4                     :16;	//31:16	//x value of LGAIN LUT point 4
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F74 RW
	UINT32 lgain_lut_y5                     :8;	//7:0	//y value of LGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x5                     :16;	//31:16	//x value of LGAIN LUT point 5
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F78 RW
	UINT32 lgain_lut_y6                     :8;	//7:0	//y value of LGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x6                     :16;	//31:16	//x value of LGAIN LUT point 6
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F7C RW
	UINT32 lgain_lut_y7                     :8;	//7:0	//y value of LGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 lgain_lut_x7                     :16;	//31:16	//x value of LGAIN LUT point 7
	};
}PE_E60_REG_H10_LGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F80 RW
	UINT32 sgain_lut_y0                     :8;	//7:0	//y value of SGAIN LUT point 0
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x0                     :16;	//31:16	//x value of SGAIN LUT point 0
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F84 RW
	UINT32 sgain_lut_y1                     :8;	//7:0	//y value of SGAIN LUT point 1
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x1                     :16;	//31:16	//x value of SGAIN LUT point 1
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F88 RW
	UINT32 sgain_lut_y2                     :8;	//7:0	//y value of SGAIN LUT point 2
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x2                     :16;	//31:16	//x value of SGAIN LUT point 2
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F8C RW
	UINT32 sgain_lut_y3                     :8;	//7:0	//y value of SGAIN LUT point 3
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x3                     :16;	//31:16	//x value of SGAIN LUT point 3
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F90 RW
	UINT32 sgain_lut_y4                     :8;	//7:0	//y value of SGAIN LUT point 4
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x4                     :16;	//31:16	//x value of SGAIN LUT point 4
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F94 RW
	UINT32 sgain_lut_y5                     :8;	//7:0	//y value of SGAIN LUT point 5
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x5                     :16;	//31:16	//x value of SGAIN LUT point 5
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F98 RW
	UINT32 sgain_lut_y6                     :8;	//7:0	//y value of SGAIN LUT point 6
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x6                     :16;	//31:16	//x value of SGAIN LUT point 6
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016F9C RW
	UINT32 sgain_lut_y7                     :8;	//7:0	//y value of SGAIN LUT point 7
	UINT32 resvd                            :8;
	UINT32 sgain_lut_x7                     :16;	//31:16	//x value of SGAIN LUT point 7
	};
}PE_E60_REG_H10_SGAIN_LUT_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FA0 RW
	UINT32 reg_rgb2yrd_en                   :1;	//0 //RGB -> Y CSC Enable
	UINT32 resvd0                           :15;
	UINT32 r_rgb2yrd_coef0                  :15;	//30:16	//RGB -> Y CSC Coefficient 0
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_RGB2Y2_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FA4 RW
	UINT32 r_rgb2yrd_coef1                  :15;	//14:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :1;
	UINT32 r_rgb2yrd_coef2                  :16;	//31:16	//RGB -> Y CSC Coefficient 0
	};
}PE_E60_REG_H10_RGB2Y2_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FA8 RW
	UINT32 r_rgb2yrd_ofst0                  :17;	//16:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_E60_REG_H10_RGB2Y2_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FAC RW
	UINT32 r_rgb2yrd_ofst3                  :17;	//16:0	//RGB -> Y CSC Coefficient 0
	UINT32 resvd                            :15;
	};
}PE_E60_REG_H10_RGB2Y2_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FB0 RW
	UINT32 reg_csc4th_en                    :1;	//0 //CSC 4th Y'U'V' -> YUV Enable
	UINT32 resvd                            :31;
	};
}PE_E60_REG_H10_CSC4_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FB4 RW
	UINT32 r_csc4th_coef1                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 1 (Default : 208)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef0                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 0 (Default : 2378)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC4_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FB8 RW
	UINT32 r_csc4th_coef3                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 3 (Default : -1293)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef2                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 2 (Default : 921)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC4_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FBC RW
	UINT32 r_csc4th_coef5                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 5 (Default : -501)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef4                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 4 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC4_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FC0 RW
	UINT32 r_csc4th_coef7                   :15;	//14:0	//CSC 4th Y'U'V' -> YUV Coef. 7 (Default : -144)
	UINT32 resvd0                           :1;
	UINT32 r_csc4th_coef6                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 6 (Default : -1649)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC4_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FC4 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc4th_coef8                   :15;	//30:16	//CSC 4th Y'U'V' -> YUV Coef. 8 (Default : 1794)
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_H10_CSC4_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FC8 RW
	UINT32 r_csc4th_ofst1                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 1 (Default : 0)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst0                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 0 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC4_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FCC RW
	UINT32 r_csc4th_ofst3                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 3 (Default : 64)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst2                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 2 (Default : 0)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC4_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9016FD0 RW
	UINT32 r_csc4th_ofst5                   :11;	//10:0	//CSC 4th Y'U'V' -> YUV Offset 5 (Default : 512)
	UINT32 resvd0                           :5;
	UINT32 r_csc4th_ofst4                   :11;	//26:16	//CSC 4th Y'U'V' -> YUV Offset 4 (Default : 512)
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_H10_CSC4_CTRL_08_T;

typedef struct {
	PE_E60_REG_H10_TOP_CTRL_00_T                         hdr_top_ctrl_00;	//0xC9016C00
	PE_E60_REG_H10_TOP_CTRL_01_T                         hdr_top_ctrl_01;	//0xC9016C04
	PE_E60_REG_H10_TOP_CTRL_02_T                         hdr_top_ctrl_02;	//0xC9016C08
	PE_E60_REG_H10_TOP_CTRL_03_T                         hdr_top_ctrl_03;	//0xC9016C0C
	PE_E60_REG_H10_TOP_CTRL_04_T                         hdr_top_ctrl_04;	//0xC9016C10
	PE_E60_REG_H10_TOP_CTRL_05_T                         hdr_top_ctrl_05;	//0xC9016C14
	PE_E60_REG_H10_TOP_CTRL_06_T                         hdr_top_ctrl_06;	//0xC9016C18
	PE_E60_REG_H10_TOP_CTRL_07_T                         hdr_top_ctrl_07;	//0xC9016C1C
	UINT32                                                     reserved0;	//0xC9016C20
	UINT32                                                     reserved1;	//0xC9016C24
	UINT32                                                     reserved2;	//0xC9016C28
	UINT32                                                     reserved3;	//0xC9016C2C
	UINT32                                                     reserved4;	//0xC9016C30
	UINT32                                                     reserved5;	//0xC9016C34
	UINT32                                                     reserved6;	//0xC9016C38
	UINT32                                                     reserved7;	//0xC9016C3C
	UINT32                                                     reserved8;	//0xC9016C40
	UINT32                                                     reserved9;	//0xC9016C44
	UINT32                                                    reserved10;	//0xC9016C48
	UINT32                                                    reserved11;	//0xC9016C4C
	PE_E60_REG_H10_CSC1_CTRL_00_T                       hdr_csc1_ctrl_00;	//0xC9016C50
	PE_E60_REG_H10_CSC1_CTRL_01_T                       hdr_csc1_ctrl_01;	//0xC9016C54
	PE_E60_REG_H10_CSC1_CTRL_02_T                       hdr_csc1_ctrl_02;	//0xC9016C58
	PE_E60_REG_H10_CSC1_CTRL_03_T                       hdr_csc1_ctrl_03;	//0xC9016C5C
	PE_E60_REG_H10_CSC1_CTRL_04_T                       hdr_csc1_ctrl_04;	//0xC9016C60
	PE_E60_REG_H10_CSC1_CTRL_05_T                       hdr_csc1_ctrl_05;	//0xC9016C64
	PE_E60_REG_H10_CSC1_CTRL_06_T                       hdr_csc1_ctrl_06;	//0xC9016C68
	PE_E60_REG_H10_CSC1_CTRL_07_T                       hdr_csc1_ctrl_07;	//0xC9016C6C
	PE_E60_REG_H10_CSC1_CTRL_08_T                       hdr_csc1_ctrl_08;	//0xC9016C70
	PE_E60_REG_H10_CSC1_CTRL_09_T                       hdr_csc1_ctrl_09;	//0xC9016C74
	PE_E60_REG_H10_CSC1_ERR_CNT_T                       hdr_csc1_err_cnt;	//0xC9016C78
	UINT32                                                    reserved12;	//0xC9016C7C
	PE_E60_REG_H10_PXL_RD_CTRL0_T                       hdr_pxl_rd_ctrl0;	//0xC9016C80
	PE_E60_REG_H10_PXL_RD_CTRL1_T                       hdr_pxl_rd_ctrl1;	//0xC9016C84
	PE_E60_REG_H10_PXL_RD_DATA_T                         hdr_pxl_rd_data;	//0xC9016C88
	UINT32                                                    reserved13;	//0xC9016C8C
	PE_E60_REG_H10_EOTF_IA_CTRL_T                       hdr_eotf_ia_ctrl;	//0xC9016C90
	PE_E60_REG_H10_EOTF_IA_DATA_T                       hdr_eotf_ia_data;	//0xC9016C94
	PE_E60_REG_H10_OETF_IA_CTRL_T                       hdr_oetf_ia_ctrl;	//0xC9016C98
	PE_E60_REG_H10_OETF_IA_DATA_T                       hdr_oetf_ia_data;	//0xC9016C9C
	PE_E60_REG_H10_PCC_CTRL_00_T                         hdr_pcc_ctrl_00;	//0xC9016CA0
	PE_E60_REG_H10_PCC_CTRL_01_T                         hdr_pcc_ctrl_01;	//0xC9016CA4
	PE_E60_REG_H10_PCC_CTRL_02_T                         hdr_pcc_ctrl_02;	//0xC9016CA8
	PE_E60_REG_H10_PCC_CTRL_03_T                         hdr_pcc_ctrl_03;	//0xC9016CAC
	PE_E60_REG_H10_PCC_CTRL_04_T                         hdr_pcc_ctrl_04;	//0xC9016CB0
	PE_E60_REG_H10_PCC_CTRL_05_T                         hdr_pcc_ctrl_05;	//0xC9016CB4
	UINT32                                                    reserved14;	//0xC9016CB8
	UINT32                                                    reserved15;	//0xC9016CBC
	UINT32                                                    reserved16;	//0xC9016CC0
	UINT32                                                    reserved17;	//0xC9016CC4
	UINT32                                                    reserved18;	//0xC9016CC8
	UINT32                                                    reserved19;	//0xC9016CCC
	PE_E60_REG_H10_HUE_SAT_CTRL_T                       hdr_hue_sat_ctrl;	//0xC9016CD0
	PE_E60_REG_H10_HUE_SAT_ALPHA_CTRL_T           hdr_hue_sat_alpha_ctrl;	//0xC9016CD4
	UINT32                                                    reserved20;	//0xC9016CD8
	UINT32                                                    reserved21;	//0xC9016CDC
	PE_E60_REG_H10_TCM_PREP_00_T                         hdr_tcm_prep_00;	//0xC9016CE0
	PE_E60_REG_H10_TCM_PREP_01_T                         hdr_tcm_prep_01;	//0xC9016CE4
	PE_E60_REG_H10_LL_LUT_IA_CTRL_T                   hdr_ll_lut_ia_ctrl;	//0xC9016CE8
	PE_E60_REG_H10_LL_LUT_IA_DATA_T                   hdr_ll_lut_ia_data;	//0xC9016CEC
	PE_E60_REG_H10_LL_HUE_CTRL_00_T                   hdr_ll_hue_ctrl_00;	//0xC9016CF0
	PE_E60_REG_H10_LL_HUE_CTRL_01_T                   hdr_ll_hue_ctrl_01;	//0xC9016CF4
	PE_E60_REG_H10_LL_HUE_CTRL_02_T                   hdr_ll_hue_ctrl_02;	//0xC9016CF8
	UINT32                                                    reserved22;	//0xC9016CFC
	PE_E60_REG_H10_LLPCC_CTRL_00_T                     hdr_llpcc_ctrl_00;	//0xC9016D00
	PE_E60_REG_H10_LLPCC_CTRL_01_T                     hdr_llpcc_ctrl_01;	//0xC9016D04
	PE_E60_REG_H10_LLPCC_CTRL_02_T                     hdr_llpcc_ctrl_02;	//0xC9016D08
	PE_E60_REG_H10_LLPCC_CTRL_03_T                     hdr_llpcc_ctrl_03;	//0xC9016D0C
	PE_E60_REG_H10_LLPCC_CTRL_04_T                     hdr_llpcc_ctrl_04;	//0xC9016D10
	PE_E60_REG_H10_LLPCC_CTRL_05_T                     hdr_llpcc_ctrl_05;	//0xC9016D14
	PE_E60_REG_H10_LL_AB_CTRL_00_T                     hdr_ll_ab_ctrl_00;	//0xC9016D18
	PE_E60_REG_H10_LL_AB_CTRL_01_T                     hdr_ll_ab_ctrl_01;	//0xC9016D1C
	PE_E60_REG_H10_LL_AB_CTRL_02_T                     hdr_ll_ab_ctrl_02;	//0xC9016D20
	PE_E60_REG_H10_LL_AB_CTRL_03_T                     hdr_ll_ab_ctrl_03;	//0xC9016D24
	PE_E60_REG_H10_LL_AB_CTRL_04_T                     hdr_ll_ab_ctrl_04;	//0xC9016D28
	UINT32                                                    reserved23;	//0xC9016D2C
	UINT32                                                    reserved24;	//0xC9016D30
	UINT32                                                    reserved25;	//0xC9016D34
	UINT32                                                    reserved26;	//0xC9016D38
	UINT32                                                    reserved27;	//0xC9016D3C
	PE_E60_REG_H10_HIST_CTRL_00_T                       hdr_hist_ctrl_00;	//0xC9016D40
	PE_E60_REG_H10_HIST_CTRL_01_T                       hdr_hist_ctrl_01;	//0xC9016D44
	PE_E60_REG_H10_HIST_CTRL_02_T                       hdr_hist_ctrl_02;	//0xC9016D48
	PE_E60_REG_H10_HIST_CTRL_03_T                       hdr_hist_ctrl_03;	//0xC9016D4C
	PE_E60_REG_H10_HIST_CTRL_04_T                       hdr_hist_ctrl_04;	//0xC9016D50
	PE_E60_REG_H10_HIST_IA_CTRL_T                       hdr_hist_ia_ctrl;	//0xC9016D54
	PE_E60_REG_H10_HIST_IA_DATA1_T                     hdr_hist_ia_data1;	//0xC9016D58
	PE_E60_REG_H10_HIST_IA_DATA2_T                     hdr_hist_ia_data2;	//0xC9016D5C
	PE_E60_REG_H10_C4_HIST_IA_CTRL_T                 hdr_c4_hist_ia_ctrl;	//0xC9016D60
	PE_E60_REG_H10_C4_HIST_IA_DATA1_T               hdr_c4_hist_ia_data1;	//0xC9016D64
	PE_E60_REG_H10_C4_HIST_IA_DATA2_T               hdr_c4_hist_ia_data2;	//0xC9016D68
	UINT32                                                    reserved28;	//0xC9016D6C
	PE_E60_REG_H10_TPG_CTRL_00_T                         hdr_tpg_ctrl_00;	//0xC9016D70
	PE_E60_REG_H10_TPG_CTRL_01_T                         hdr_tpg_ctrl_01;	//0xC9016D74
	PE_E60_REG_H10_TPG_CTRL_02_T                         hdr_tpg_ctrl_02;	//0xC9016D78
	PE_E60_REG_H10_TPG_CTRL_03_T                         hdr_tpg_ctrl_03;	//0xC9016D7C
	PE_E60_REG_H10_TPG_CTRL_04_T                         hdr_tpg_ctrl_04;	//0xC9016D80
	PE_E60_REG_H10_TPG_IA_CTRL_T                         hdr_tpg_ia_ctrl;	//0xC9016D84
	PE_E60_REG_H10_TPG_IA_DATA_T                         hdr_tpg_ia_data;	//0xC9016D88
	UINT32                                                    reserved29;	//0xC9016D8C
	PE_E60_REG_H10_CLUT_CTRL_00_T                       hdr_clut_ctrl_00;	//0xC9016D90
	PE_E60_REG_H10_CLUT_IA_CTRL_T                       hdr_clut_ia_ctrl;	//0xC9016D94
	PE_E60_REG_H10_CLUT_IA_DATA_T                       hdr_clut_ia_data;	//0xC9016D98
	PE_E60_REG_H10_PLUT_CTRL_00_T                       hdr_plut_ctrl_00;	//0xC9016D9C
	PE_E60_REG_H10_PLUT_IA_CTRL_T                       hdr_plut_ia_ctrl;	//0xC9016DA0
	PE_E60_REG_H10_PLUT_IA_DATA_T                       hdr_plut_ia_data;	//0xC9016DA4
	PE_E60_REG_H10_SLUT_CTRL_00_T                       hdr_slut_ctrl_00;	//0xC9016DA8
	PE_E60_REG_H10_SLUT_IA_CTRL_T                       hdr_slut_ia_ctrl;	//0xC9016DAC
	PE_E60_REG_H10_SLUT_IA_DATA_T                       hdr_slut_ia_data;	//0xC9016DB0
	PE_E60_REG_H10_ILUT_CTRL_00_T                       hdr_ilut_ctrl_00;	//0xC9016DB4
	PE_E60_REG_H10_ILUT_IA_CTRL_T                       hdr_ilut_ia_ctrl;	//0xC9016DB8
	PE_E60_REG_H10_ILUT_IA_DATA_T                       hdr_ilut_ia_data;	//0xC9016DBC
	PE_E60_REG_H10_DLUT_CTRL_00_T                       hdr_dlut_ctrl_00;	//0xC9016DC0
	PE_E60_REG_H10_DLUT_CTRL_01_T                       hdr_dlut_ctrl_01;	//0xC9016DC4
	PE_E60_REG_H10_DLUT_CTRL_02_T                       hdr_dlut_ctrl_02;	//0xC9016DC8
	PE_E60_REG_H10_DLUT_IA_CTRL_T                       hdr_dlut_ia_ctrl;	//0xC9016DCC
	PE_E60_REG_H10_DLUT_IA_DATA_T                       hdr_dlut_ia_data;	//0xC9016DD0
	PE_E60_REG_H10_TC_CTRL_00_T                           hdr_tc_ctrl_00;	//0xC9016DD4
	PE_E60_REG_H10_TC_CTRL_01_T                           hdr_tc_ctrl_01;	//0xC9016DD8
	PE_E60_REG_H10_TC_CTRL_02_T                           hdr_tc_ctrl_02;	//0xC9016DDC
	PE_E60_REG_H10_TC_CTRL_03_T                           hdr_tc_ctrl_03;	//0xC9016DE0
	PE_E60_REG_H10_TC_CTRL_04_T                           hdr_tc_ctrl_04;	//0xC9016DE4
	UINT32                                                    reserved30;	//0xC9016DE8
	UINT32                                                    reserved31;	//0xC9016DEC
	UINT32                                                    reserved32;	//0xC9016DF0
	UINT32                                                    reserved33;	//0xC9016DF4
	UINT32                                                    reserved34;	//0xC9016DF8
	UINT32                                                    reserved35;	//0xC9016DFC
	PE_E60_REG_H10_LLUT0_CTRL_00_T                     hdr_llut0_ctrl_00;	//0xC9016E00
	PE_E60_REG_H10_LLUT0_CTRL_01_T                     hdr_llut0_ctrl_01;	//0xC9016E04
	PE_E60_REG_H10_LLUT0_CTRL_02_T                     hdr_llut0_ctrl_02;	//0xC9016E08
	PE_E60_REG_H10_LLUT0_CTRL_03_T                     hdr_llut0_ctrl_03;	//0xC9016E0C
	PE_E60_REG_H10_LLUT0_CTRL_04_T                     hdr_llut0_ctrl_04;	//0xC9016E10
	PE_E60_REG_H10_LLUT0_CTRL_05_T                     hdr_llut0_ctrl_05;	//0xC9016E14
	PE_E60_REG_H10_LLUT0_CTRL_06_T                     hdr_llut0_ctrl_06;	//0xC9016E18
	UINT32                                                    reserved36;	//0xC9016E1C
	PE_E60_REG_H10_LLUT0_IA_CTRL_T                     hdr_llut0_ia_ctrl;	//0xC9016E20
	PE_E60_REG_H10_LLUT0_IA_DATA_T                     hdr_llut0_ia_data;	//0xC9016E24
	UINT32                                                    reserved37;	//0xC9016E28
	UINT32                                                    reserved38;	//0xC9016E2C
	PE_E60_REG_H10_LLUT1_CTRL_00_T                     hdr_llut1_ctrl_00;	//0xC9016E30
	PE_E60_REG_H10_LLUT1_CTRL_01_T                     hdr_llut1_ctrl_01;	//0xC9016E34
	PE_E60_REG_H10_LLUT1_CTRL_02_T                     hdr_llut1_ctrl_02;	//0xC9016E38
	PE_E60_REG_H10_LLUT1_CTRL_03_T                     hdr_llut1_ctrl_03;	//0xC9016E3C
	PE_E60_REG_H10_LLUT1_CTRL_04_T                     hdr_llut1_ctrl_04;	//0xC9016E40
	PE_E60_REG_H10_LLUT1_CTRL_05_T                     hdr_llut1_ctrl_05;	//0xC9016E44
	PE_E60_REG_H10_LLUT1_CTRL_06_T                     hdr_llut1_ctrl_06;	//0xC9016E48
	UINT32                                                    reserved39;	//0xC9016E4C
	PE_E60_REG_H10_LLUT1_IA_CTRL_T                     hdr_llut1_ia_ctrl;	//0xC9016E50
	PE_E60_REG_H10_LLUT1_IA_DATA_T                     hdr_llut1_ia_data;	//0xC9016E54
	UINT32                                                    reserved40;	//0xC9016E58
	UINT32                                                    reserved41;	//0xC9016E5C
	PE_E60_REG_H10_LLUT2_CTRL_00_T                     hdr_llut2_ctrl_00;	//0xC9016E60
	PE_E60_REG_H10_LLUT2_CTRL_01_T                     hdr_llut2_ctrl_01;	//0xC9016E64
	PE_E60_REG_H10_LLUT2_CTRL_02_T                     hdr_llut2_ctrl_02;	//0xC9016E68
	PE_E60_REG_H10_LLUT2_CTRL_03_T                     hdr_llut2_ctrl_03;	//0xC9016E6C
	PE_E60_REG_H10_LLUT2_CTRL_04_T                     hdr_llut2_ctrl_04;	//0xC9016E70
	PE_E60_REG_H10_LLUT2_CTRL_05_T                     hdr_llut2_ctrl_05;	//0xC9016E74
	PE_E60_REG_H10_LLUT2_CTRL_06_T                     hdr_llut2_ctrl_06;	//0xC9016E78
	UINT32                                                    reserved42;	//0xC9016E7C
	PE_E60_REG_H10_LLUT2_IA_CTRL_T                     hdr_llut2_ia_ctrl;	//0xC9016E80
	PE_E60_REG_H10_LLUT2_IA_DATA_T                     hdr_llut2_ia_data;	//0xC9016E84
	UINT32                                                    reserved43;	//0xC9016E88
	UINT32                                                    reserved44;	//0xC9016E8C
	PE_E60_REG_H10_GAMMA045_CTRL_00_T               hdr_gamma045_ctrl_00;	//0xC9016E90
	UINT32                                                    reserved45;	//0xC9016E94
	PE_E60_REG_H10_DITHER_CTRL_00_T                   hdr_dither_ctrl_00;	//0xC9016E98
	PE_E60_REG_H10_PCC32_GAIN_CTRL_T                 hdr_pcc32_gain_ctrl;	//0xC9016E9C
	PE_E60_REG_H10_CSC3_CTRL_00_T                       hdr_csc3_ctrl_00;	//0xC9016EA0
	PE_E60_REG_H10_CSC3_CTRL_01_T                       hdr_csc3_ctrl_01;	//0xC9016EA4
	PE_E60_REG_H10_CSC3_CTRL_02_T                       hdr_csc3_ctrl_02;	//0xC9016EA8
	PE_E60_REG_H10_CSC3_CTRL_03_T                       hdr_csc3_ctrl_03;	//0xC9016EAC
	PE_E60_REG_H10_CSC3_CTRL_04_T                       hdr_csc3_ctrl_04;	//0xC9016EB0
	PE_E60_REG_H10_CSC3_CTRL_05_T                       hdr_csc3_ctrl_05;	//0xC9016EB4
	PE_E60_REG_H10_CSC3_CTRL_06_T                       hdr_csc3_ctrl_06;	//0xC9016EB8
	PE_E60_REG_H10_CSC3_CTRL_07_T                       hdr_csc3_ctrl_07;	//0xC9016EBC
	PE_E60_REG_H10_CSC3_CTRL_08_T                       hdr_csc3_ctrl_08;	//0xC9016EC0
	UINT32                                                    reserved46;	//0xC9016EC4
	UINT32                                                    reserved47;	//0xC9016EC8
	UINT32                                                    reserved48;	//0xC9016ECC
	PE_E60_REG_H10_TCM_SLUT0_00_T                       hdr_tcm_slut0_00;	//0xC9016ED0
	PE_E60_REG_H10_TCM_SLUT0_01_T                       hdr_tcm_slut0_01;	//0xC9016ED4
	PE_E60_REG_H10_TCM_SLUT0_02_T                       hdr_tcm_slut0_02;	//0xC9016ED8
	PE_E60_REG_H10_TCM_SLUT0_03_T                       hdr_tcm_slut0_03;	//0xC9016EDC
	PE_E60_REG_H10_TCM_SLUT0_04_T                       hdr_tcm_slut0_04;	//0xC9016EE0
	PE_E60_REG_H10_TCM_SLUT0_05_T                       hdr_tcm_slut0_05;	//0xC9016EE4
	PE_E60_REG_H10_TCM_SLUT0_06_T                       hdr_tcm_slut0_06;	//0xC9016EE8
	PE_E60_REG_H10_TCM_SLUT0_07_T                       hdr_tcm_slut0_07;	//0xC9016EEC
	PE_E60_REG_H10_TCM_SLUT0_08_T                       hdr_tcm_slut0_08;	//0xC9016EF0
	PE_E60_REG_H10_TCM_SLUT0_09_T                       hdr_tcm_slut0_09;	//0xC9016EF4
	PE_E60_REG_H10_SAT_MAP_CTRL_01_T                 hdr_sat_map_ctrl_01;	//0xC9016EF8
	PE_E60_REG_H10_SAT_MAP_CTRL_02_T                 hdr_sat_map_ctrl_02;	//0xC9016EFC
	PE_E60_REG_H10_3DLUT_CTRL_00_T                     hdr_3dlut_ctrl_00;	//0xC9016F00
	PE_E60_REG_H10_3DLUT_CTRL_01_T                     hdr_3dlut_ctrl_01;	//0xC9016F04
	PE_E60_REG_H10_3DLUT_CTRL_02_T                     hdr_3dlut_ctrl_02;	//0xC9016F08
	PE_E60_REG_H10_3DLUT_CTRL_03_T                     hdr_3dlut_ctrl_03;	//0xC9016F0C
	PE_E60_REG_H10_3DLUT_CTRL_04_T                     hdr_3dlut_ctrl_04;	//0xC9016F10
	PE_E60_REG_H10_3DLUT_CTRL_05_T                     hdr_3dlut_ctrl_05;	//0xC9016F14
	PE_E60_REG_H10_3DLUT_CTRL_06_T                     hdr_3dlut_ctrl_06;	//0xC9016F18
	PE_E60_REG_H10_3DLUT_CTRL_07_T                     hdr_3dlut_ctrl_07;	//0xC9016F1C
	PE_E60_REG_H10_YGAIN_LUT_CTRL_00_T             hdr_ygain_lut_ctrl_00;	//0xC9016F20
	PE_E60_REG_H10_YGAIN_LUT_CTRL_01_T             hdr_ygain_lut_ctrl_01;	//0xC9016F24
	PE_E60_REG_H10_YGAIN_LUT_CTRL_02_T             hdr_ygain_lut_ctrl_02;	//0xC9016F28
	PE_E60_REG_H10_YGAIN_LUT_CTRL_03_T             hdr_ygain_lut_ctrl_03;	//0xC9016F2C
	PE_E60_REG_H10_YGAIN_LUT_CTRL_04_T             hdr_ygain_lut_ctrl_04;	//0xC9016F30
	PE_E60_REG_H10_YGAIN_LUT_CTRL_05_T             hdr_ygain_lut_ctrl_05;	//0xC9016F34
	PE_E60_REG_H10_YGAIN_LUT_IA_CTRL_T             hdr_ygain_lut_ia_ctrl;	//0xC9016F38
	PE_E60_REG_H10_YGAIN_LUT_IA_DATA_T             hdr_ygain_lut_ia_data;	//0xC9016F3C
	PE_E60_REG_H10_RGB2Y_CTRL_00_T                     hdr_rgb2y_ctrl_00;	//0xC9016F40
	PE_E60_REG_H10_RGB2Y_CTRL_01_T                     hdr_rgb2y_ctrl_01;	//0xC9016F44
	PE_E60_REG_H10_RGB2Y_CTRL_02_T                     hdr_rgb2y_ctrl_02;	//0xC9016F48
	PE_E60_REG_H10_RGB2Y_CTRL_03_T                     hdr_rgb2y_ctrl_03;	//0xC9016F4C
	UINT32                                                    reserved49;	//0xC9016F50
	UINT32                                                    reserved50;	//0xC9016F54
	UINT32                                                    reserved51;	//0xC9016F58
	UINT32                                                    reserved52;	//0xC9016F5C
	PE_E60_REG_H10_LGAIN_LUT_CTRL_00_T             hdr_lgain_lut_ctrl_00;	//0xC9016F60
	PE_E60_REG_H10_LGAIN_LUT_CTRL_01_T             hdr_lgain_lut_ctrl_01;	//0xC9016F64
	PE_E60_REG_H10_LGAIN_LUT_CTRL_02_T             hdr_lgain_lut_ctrl_02;	//0xC9016F68
	PE_E60_REG_H10_LGAIN_LUT_CTRL_03_T             hdr_lgain_lut_ctrl_03;	//0xC9016F6C
	PE_E60_REG_H10_LGAIN_LUT_CTRL_04_T             hdr_lgain_lut_ctrl_04;	//0xC9016F70
	PE_E60_REG_H10_LGAIN_LUT_CTRL_05_T             hdr_lgain_lut_ctrl_05;	//0xC9016F74
	PE_E60_REG_H10_LGAIN_LUT_CTRL_06_T             hdr_lgain_lut_ctrl_06;	//0xC9016F78
	PE_E60_REG_H10_LGAIN_LUT_CTRL_07_T             hdr_lgain_lut_ctrl_07;	//0xC9016F7C
	PE_E60_REG_H10_SGAIN_LUT_CTRL_00_T             hdr_sgain_lut_ctrl_00;	//0xC9016F80
	PE_E60_REG_H10_SGAIN_LUT_CTRL_01_T             hdr_sgain_lut_ctrl_01;	//0xC9016F84
	PE_E60_REG_H10_SGAIN_LUT_CTRL_02_T             hdr_sgain_lut_ctrl_02;	//0xC9016F88
	PE_E60_REG_H10_SGAIN_LUT_CTRL_03_T             hdr_sgain_lut_ctrl_03;	//0xC9016F8C
	PE_E60_REG_H10_SGAIN_LUT_CTRL_04_T             hdr_sgain_lut_ctrl_04;	//0xC9016F90
	PE_E60_REG_H10_SGAIN_LUT_CTRL_05_T             hdr_sgain_lut_ctrl_05;	//0xC9016F94
	PE_E60_REG_H10_SGAIN_LUT_CTRL_06_T             hdr_sgain_lut_ctrl_06;	//0xC9016F98
	PE_E60_REG_H10_SGAIN_LUT_CTRL_07_T             hdr_sgain_lut_ctrl_07;	//0xC9016F9C
	PE_E60_REG_H10_RGB2Y2_CTRL_00_T                   hdr_rgb2y2_ctrl_00;	//0xC9016FA0
	PE_E60_REG_H10_RGB2Y2_CTRL_01_T                   hdr_rgb2y2_ctrl_01;	//0xC9016FA4
	PE_E60_REG_H10_RGB2Y2_CTRL_02_T                   hdr_rgb2y2_ctrl_02;	//0xC9016FA8
	PE_E60_REG_H10_RGB2Y2_CTRL_03_T                   hdr_rgb2y2_ctrl_03;	//0xC9016FAC
	PE_E60_REG_H10_CSC4_CTRL_00_T                       hdr_csc4_ctrl_00;	//0xC9016FB0
	PE_E60_REG_H10_CSC4_CTRL_01_T                       hdr_csc4_ctrl_01;	//0xC9016FB4
	PE_E60_REG_H10_CSC4_CTRL_02_T                       hdr_csc4_ctrl_02;	//0xC9016FB8
	PE_E60_REG_H10_CSC4_CTRL_03_T                       hdr_csc4_ctrl_03;	//0xC9016FBC
	PE_E60_REG_H10_CSC4_CTRL_04_T                       hdr_csc4_ctrl_04;	//0xC9016FC0
	PE_E60_REG_H10_CSC4_CTRL_05_T                       hdr_csc4_ctrl_05;	//0xC9016FC4
	PE_E60_REG_H10_CSC4_CTRL_06_T                       hdr_csc4_ctrl_06;	//0xC9016FC8
	PE_E60_REG_H10_CSC4_CTRL_07_T                       hdr_csc4_ctrl_07;	//0xC9016FCC
	PE_E60_REG_H10_CSC4_CTRL_08_T                       hdr_csc4_ctrl_08;	//0xC9016FD0
}PE_E60_REG_H10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017000 RW
	UINT32 width                            :13;	//12:0	//width
	UINT32 resvd                            :3;
	UINT32 height                           :13;	//28:16	//height
	UINT32 reg_org_out                      :1;	//29 //Tour all path but output equals to original input
	UINT32 reg_sdr2hdr_enable               :1;	//30 //enable
	UINT32 reg_dbg_brm_map                  :1;	//31 //enable bright region debug map
	};
}PE_E60_REG_S2H_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017004 RW
	UINT32 reg_csc1st_en                    :1;	//0 //
	UINT32 resvd                            :31;
	};
}PE_E60_REG_S2H_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017008 RW
	UINT32 r_csc1st_coef1                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef0                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_S2H_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901700C RW
	UINT32 r_csc1st_coef3                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef2                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_S2H_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017010 RW
	UINT32 r_csc1st_coef5                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef4                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_S2H_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017014 RW
	UINT32 r_csc1st_coef7                   :15;	//14:0	//
	UINT32 resvd0                           :1;
	UINT32 r_csc1st_coef6                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_S2H_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017018 RW
	UINT32 resvd0                           :16;
	UINT32 r_csc1st_coef8                   :15;	//30:16	//
	UINT32 resvd1                           :1;
	};
}PE_E60_REG_S2H_CTRL_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901701C RW
	UINT32 r_csc1st_ofst1                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst0                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_S2H_CTRL_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017020 RW
	UINT32 r_csc1st_ofst3                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst2                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_S2H_CTRL_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017024 RW
	UINT32 r_csc1st_ofst5                   :11;	//10:0	//
	UINT32 resvd0                           :5;
	UINT32 r_csc1st_ofst4                   :11;	//26:16	//
	UINT32 resvd1                           :5;
	};
}PE_E60_REG_S2H_CTRL_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017028 RW
	UINT32 reg_ihsv_vgain                   :8;	//07:00	//RGB -> HSV V gain
	UINT32 reg_ihsv_sgain                   :8;	//15:08	//RGB -> HSV H gain
	UINT32 resvd                            :14;
	UINT32 reg_hsv_scaler_en                :1;	//30 //
	UINT32 reg_hsv_hsl_sel                  :1;	//31 //
	};
}PE_E60_REG_S2H_CTRL_10_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901702C RW
	UINT32 reg_ihsv_voffset                 :8;	//7:0	//RGB -> HSV V offset
	UINT32 reg_ihsv_soffset                 :8;	//15:8	//RGB -> HSV S offset
	UINT32 reg_ihsv_hoffset                 :8;	//23:16	//RGB -> HSV H offset
	UINT32 resvd                            :8;
	};
}PE_E60_REG_S2H_CTRL_11_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017030 RW
	UINT32 reg_cdt_dcp_mean                 :8;	//7:0	//Dark Threshold (Previous frame) mean
	UINT32 resvd                            :24;
	};
}PE_E60_REG_S2H_CTRL_12_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017034 RW
	UINT32 reg_fbs_y_max                    :10;	//9:0	//Find Bright Spot (Previous frame) luma max
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_ybs_scale                :7;	//22:16	//Find Bright Spot ybs scale
	UINT32 resvd1                           :5;
	UINT32 reg_fbs_bs_exp_s_wei             :3;	//30:28	//bs_exp weight (0~4)
	UINT32 resvd2                           :1;
	};
}PE_E60_REG_S2H_CTRL_13_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017038 RW
	UINT32 reg_fbs_yy_lut_x_00              :8;	//7:0	//reg_fbs_yy_lut point x_00
	UINT32 reg_fbs_yy_lut_y_00              :8;	//15:8	//reg_fbs_yy_lut point y_00
	UINT32 reg_fbs_yy_lut_x_01              :8;	//23:16	//reg_fbs_yy_lut point x_01
	UINT32 reg_fbs_yy_lut_y_01              :8;	//31:24	//reg_fbs_yy_lut point y_01
	};
}PE_E60_REG_S2H_CTRL_14_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901703C RW
	UINT32 reg_fbs_yy_lut_x_02              :8;	//7:0	//reg_fbs_yy_lut point x_02
	UINT32 reg_fbs_yy_lut_y_02              :8;	//15:8	//reg_fbs_yy_lut point y_02
	UINT32 reg_fbs_yy_lut_x_03              :8;	//23:16	//reg_fbs_yy_lut point x_03
	UINT32 reg_fbs_yy_lut_y_03              :8;	//31:24	//reg_fbs_yy_lut point y_03
	};
}PE_E60_REG_S2H_CTRL_15_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017040 RW
	UINT32 reg_fbs_yy_lut_x_04              :8;	//7:0	//reg_fbs_yy_lut point x_04
	UINT32 reg_fbs_yy_lut_y_04              :8;	//15:8	//reg_fbs_yy_lut point y_04
	UINT32 reg_fbs_yy_lut_x_05              :8;	//23:16	//reg_fbs_yy_lut point x_05
	UINT32 reg_fbs_yy_lut_y_05              :8;	//31:24	//reg_fbs_yy_lut point y_05
	};
}PE_E60_REG_S2H_CTRL_16_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017044 RW
	UINT32 reg_fbs_yy_lut_x_06              :8;	//7:0	//reg_fbs_yy_lut point x_06
	UINT32 reg_fbs_yy_lut_y_06              :8;	//15:8	//reg_fbs_yy_lut point y_06
	UINT32 reg_fbs_yy_lut_x_07              :8;	//23:16	//reg_fbs_yy_lut point x_07
	UINT32 reg_fbs_yy_lut_y_07              :8;	//31:24	//reg_fbs_yy_lut point y_07
	};
}PE_E60_REG_S2H_CTRL_17_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017048 RW
	UINT32 reg_fbs_yy_lut_x_08              :8;	//7:0	//reg_fbs_yy_lut point x_08
	UINT32 reg_fbs_yy_lut_y_08              :8;	//15:8	//reg_fbs_yy_lut point y_08
	UINT32 reg_fbs_yy_lut_x_09              :8;	//23:16	//reg_fbs_yy_lut point x_09
	UINT32 reg_fbs_yy_lut_y_09              :8;	//31:24	//reg_fbs_yy_lut point y_09
	};
}PE_E60_REG_S2H_CTRL_18_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901704C RW
	UINT32 reg_fbs_yy_lut_x_10              :8;	//7:0	//reg_fbs_yy_lut point x_10
	UINT32 reg_fbs_yy_lut_y_10              :8;	//15:8	//reg_fbs_yy_lut point y_10
	UINT32 reg_fbs_yy_lut_x_11              :8;	//23:16	//reg_fbs_yy_lut point x_11
	UINT32 reg_fbs_yy_lut_y_11              :8;	//31:24	//reg_fbs_yy_lut point y_11
	};
}PE_E60_REG_S2H_CTRL_19_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017050 RW
	UINT32 reg_fbs_yy_lut_x_12              :8;	//7:0	//reg_fbs_yy_lut point x_12
	UINT32 reg_fbs_yy_lut_y_12              :8;	//15:8	//reg_fbs_yy_lut point y_12
	UINT32 reg_fbs_yy_lut_x_13              :8;	//23:16	//reg_fbs_yy_lut point x_13
	UINT32 reg_fbs_yy_lut_y_13              :8;	//31:24	//reg_fbs_yy_lut point y_13
	};
}PE_E60_REG_S2H_CTRL_20_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017054 RW
	UINT32 reg_fbs_yy_lut_x_14              :8;	//7:0	//reg_fbs_yy_lut point x_14
	UINT32 reg_fbs_yy_lut_y_14              :8;	//15:8	//reg_fbs_yy_lut point y_14
	UINT32 reg_fbs_yy_lut_x_15              :8;	//23:16	//reg_fbs_yy_lut point x_15
	UINT32 reg_fbs_yy_lut_y_15              :8;	//31:24	//reg_fbs_yy_lut point y_15
	};
}PE_E60_REG_S2H_CTRL_21_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017058 RW
	UINT32 reg_fbs_bs_cnt0                  :13;	//12:0	//bs_cnt0 line offset
	UINT32 resvd0                           :3;
	UINT32 reg_fbs_bs_cnt1                  :13;	//28:16	//bs_cnt1 line offset
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_S2H_CTRL_22_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901705C RW
	UINT32 reg_fbs_bs_cnt2                  :13;	//12:0	//bs_cnt2 line offset
	UINT32 resvd0                           :3;
	UINT32 reg_fbs_bs_cnt3                  :13;	//28:16	//bs_cnt3 line offset
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_S2H_CTRL_23_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017060 RW
	UINT32 reg_fbs_bs_cnt4                  :13;	//12:0	//bs_cnt4 line offset
	UINT32 resvd0                           :3;
	UINT32 reg_fbs_bs_cnt5                  :13;	//28:16	//bs_cnt5 line offset
	UINT32 resvd1                           :3;
	};
}PE_E60_REG_S2H_CTRL_24_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017064 RW
	UINT32 reg_fbs_bs_cnt6                  :13;	//12:0	//bs_cnt6 line offset
	UINT32 resvd                            :19;
	};
}PE_E60_REG_S2H_CTRL_25_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017068 RW
	UINT32 reg_fbs_bs_exp_y_ofs_0           :10;	//9:0	//Find Bright Spot exp y offset 0
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_1           :10;	//25:16	//Find Bright Spot exp y offset 1
	UINT32 resvd1                           :6;
	};
}PE_E60_REG_S2H_CTRL_26_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901706C RW
	UINT32 reg_fbs_bs_exp_y_ofs_2           :10;	//9:0	//Find Bright Spot exp y offset 2
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_3           :10;	//25:16	//Find Bright Spot exp y offset 3
	UINT32 resvd1                           :6;
	};
}PE_E60_REG_S2H_CTRL_27_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017070 RW
	UINT32 reg_fbs_bs_exp_y_ofs_4           :10;	//9:0	//Find Bright Spot exp y offset 4
	UINT32 resvd0                           :6;
	UINT32 reg_fbs_bs_exp_y_ofs_5           :10;	//25:16	//Find Bright Spot exp y offset 5
	UINT32 resvd1                           :6;
	};
}PE_E60_REG_S2H_CTRL_28_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017074 RW
	UINT32 reg_fbs_bs_exp_y_ofs_6           :10;	//9:0	//Find Bright Spot exp y offset 6
	UINT32 resvd                            :22;
	};
}PE_E60_REG_S2H_CTRL_29_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017078 RW
	UINT32 reg_fbs_bs_exp_s_ofs_0           :8;	//7:0	//Find Bright Spot exp s offset 0
	UINT32 reg_fbs_bs_exp_s_ofs_1           :8;	//15:8	//Find Bright Spot exp s offset 1
	UINT32 reg_fbs_bs_exp_s_ofs_2           :8;	//23:16	//Find Bright Spot exp s offset 2
	UINT32 reg_fbs_bs_exp_s_ofs_3           :8;	//31:24	//Find Bright Spot exp s offset 3
	};
}PE_E60_REG_S2H_CTRL_30_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901707C RW
	UINT32 reg_fbs_bs_exp_s_ofs_4           :8;	//7:0	//Find Bright Spot exp s offset 4
	UINT32 reg_fbs_bs_exp_s_ofs_5           :8;	//15:8	//Find Bright Spot exp s offset 5
	UINT32 reg_fbs_bs_exp_s_ofs_6           :8;	//23:16	//Find Bright Spot exp s offset 6
	UINT32 resvd                            :8;
	};
}PE_E60_REG_S2H_CTRL_31_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017080 RW
	UINT32 resvd                            :28;
	UINT32 reg_brm_exp_wei                  :4;	//31:28	//brm_exp weight (0~8)
	};
}PE_E60_REG_S2H_CTRL_32_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017084 RW
	UINT32 reg_brm_br_lut_x_0               :10;	//9:0	//Bright Region Map lut x_0
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_0               :8;	//23:16	//Bright Region Map lut y_0
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_33_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017088 RW
	UINT32 reg_brm_br_lut_x_1               :10;	//9:0	//Bright Region Map lut x_1
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_1               :8;	//23:16	//Bright Region Map lut y_1
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_34_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901708C RW
	UINT32 reg_brm_br_lut_x_2               :10;	//9:0	//Bright Region Map lut x_2
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_2               :8;	//23:16	//Bright Region Map lut y_2
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_35_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017090 RW
	UINT32 reg_brm_br_lut_x_3               :10;	//9:0	//Bright Region Map lut x_3
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_3               :8;	//23:16	//Bright Region Map lut y_3
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_36_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017094 RW
	UINT32 reg_brm_br_lut_x_4               :10;	//9:0	//Bright Region Map lut x_4
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_4               :8;	//23:16	//Bright Region Map lut y_4
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_37_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017098 RW
	UINT32 reg_brm_br_lut_x_5               :10;	//9:0	//Bright Region Map lut x_5
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_5               :8;	//23:16	//Bright Region Map lut y_5
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_38_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901709C RW
	UINT32 reg_brm_br_lut_x_6               :10;	//9:0	//Bright Region Map lut x_6
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_6               :8;	//23:16	//Bright Region Map lut y_6
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_39_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170A0 RW
	UINT32 reg_brm_br_lut_x_7               :10;	//9:0	//Bright Region Map lut x_7
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_7               :8;	//23:16	//Bright Region Map lut y_7
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_40_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170A4 RW
	UINT32 reg_brm_br_lut_x_8               :10;	//9:0	//Bright Region Map lut x_8
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_8               :8;	//23:16	//Bright Region Map lut y_8
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_41_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170A8 RW
	UINT32 reg_brm_br_lut_x_9               :10;	//9:0	//Bright Region Map lut x_9
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_9               :8;	//23:16	//Bright Region Map lut y_9
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_42_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170AC RW
	UINT32 reg_brm_br_lut_x_10              :10;	//9:0	//Bright Region Map lut x_10
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_10              :8;	//23:16	//Bright Region Map lut y_10
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_43_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170B0 RW
	UINT32 reg_brm_br_lut_x_11              :10;	//9:0	//Bright Region Map lut x_11
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_11              :8;	//23:16	//Bright Region Map lut y_11
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_44_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170B4 RW
	UINT32 reg_brm_br_lut_x_12              :10;	//9:0	//Bright Region Map lut x_12
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_12              :8;	//23:16	//Bright Region Map lut y_12
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_45_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170B8 RW
	UINT32 reg_brm_br_lut_x_13              :10;	//9:0	//Bright Region Map lut x_13
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_13              :8;	//23:16	//Bright Region Map lut y_13
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_46_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170BC RW
	UINT32 reg_brm_br_lut_x_14              :10;	//9:0	//Bright Region Map lut x_14
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_14              :8;	//23:16	//Bright Region Map lut y_14
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_47_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170C0 RW
	UINT32 reg_brm_br_lut_x_15              :10;	//9:0	//Bright Region Map lut x_15
	UINT32 resvd0                           :6;
	UINT32 reg_brm_br_lut_y_15              :8;	//23:16	//Bright Region Map lut y_15
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_CTRL_48_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170C4 RW
	UINT32 cc_en                            :1;	//0:0	//0 : Chroma Compensation Disable	1 : Chroma Compensation Enable
	UINT32 resvd0                           :15;
	UINT32 reg_equal_lut                    :1;	//16 //llut equal lut
	UINT32 resvd1                           :15;
	};
}PE_E60_REG_S2H_CTRL_49_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170C8 RW
	UINT32 dither_en                        :1;	//0 //enable dither
	UINT32 resvd0                           :1;
	UINT32 dither_random_freeze_en          :1;	//2 //1' : freeze random number	'0' : use random number
	UINT32 demo_pattern_enable              :1;	//3 //gradation pattern enable for demo
	UINT32 bit_mode                         :2;	//5:4	//"00": 10 bit mode, "01": 8 bit mode, "10": 6 bit mode, "11": bypass
	UINT32 resvd1                           :26;
	};
}PE_E60_REG_S2H_CTRL_50_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170D0 RW
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
}PE_E60_REG_S2H_LLUT0_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170D4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_S2H_LLUT0_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170D8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_S2H_LLUT0_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170DC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_S2H_LLUT0_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170E0 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_S2H_LLUT0_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170E4 RW
	UINT32 hif_llut0_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_E60_REG_S2H_LLUT0_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170E8 RW
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
}PE_E60_REG_S2H_LLUT0_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170EC RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_S2H_LLUT0_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170F0 RW
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
}PE_E60_REG_S2H_LLUT1_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170F4 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_S2H_LLUT1_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170F8 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_S2H_LLUT1_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90170FC RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_S2H_LLUT1_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017100 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_S2H_LLUT1_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017104 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut1_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_E60_REG_S2H_LLUT1_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017108 RW
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
}PE_E60_REG_S2H_LLUT1_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901710C RW
	UINT32 hif_llut1_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut1_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_S2H_LLUT1_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017130 RW
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
}PE_E60_REG_S2H_HIST_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017134 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_S2H_HIST_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017138 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_S2H_HIST_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901713C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_S2H_HIST_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017140 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_S2H_HIST_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017144 RW
	UINT32 hif_hist_address                 :7;	//6:0	//"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
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
}PE_E60_REG_S2H_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017148 RW
	UINT32 hist_status0                     :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_E60_REG_S2H_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901714C RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_E60_REG_S2H_HIST_IA_DATA2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017150 RW
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
}PE_E60_REG_S2H_FBSLUT_CTRL_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017154 RW
	UINT32 win_w0_x0                        :16;	//15:0	//win_w0_x0
	UINT32 win_w0_y0                        :16;	//31:16	//win_w0_y0
	};
}PE_E60_REG_S2H_FBSLUT_CTRL_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017158 RW
	UINT32 win_w0_x1                        :16;	//15:0	//win_w0_x1
	UINT32 win_w0_y1                        :16;	//31:16	//win_w0_y1
	};
}PE_E60_REG_S2H_FBSLUT_CTRL_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901715C RW
	UINT32 win_w1_x0                        :16;	//15:0	//win_w1_x0
	UINT32 win_w1_y0                        :16;	//31:16	//win_w1_y0
	};
}PE_E60_REG_S2H_FBSLUT_CTRL_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017160 RW
	UINT32 win_w1_x1                        :16;	//15:0	//win_w1_x1
	UINT32 win_w1_y1                        :16;	//31:16	//win_w1_y1
	};
}PE_E60_REG_S2H_FBSLUT_CTRL_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017164 RW
	UINT32 hif_llut1_wdata_y_33rd           :16;	//15:0	//Y coordinate of 33rd control point
	UINT32 hif_llut0_wdata_x_33rd           :16;	//31:16	//X coordinate of 33rd control point
	};
}PE_E60_REG_S2H_FBSLUT_CTRL_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9017168 RW
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
}PE_E60_REG_S2H_FBSLUT_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901716C RW
	UINT32 hif_llut0_wdata_y                :16;	//15:0	//Y coordinate of control point
	UINT32 hif_llut0_wdata_x                :16;	//31:16	//X coordinate of control point
	};
}PE_E60_REG_S2H_FBS_LUT_IA_DATA_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171A0 RO
	UINT32 reg_st_max_luma                  :10;	//9:0	//Max luma in frame
	UINT32 resvd0                           :6;
	UINT32 dcp_out_mean                     :10;	//25:16	//Dark Channel Prior mean value
	UINT32 resvd1                           :6;
	};
}PE_E60_REG_S2H_STAT_00_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171A4 RO
	UINT32 reg_fbs_bb_yy                    :10;	//9:0	//Find Bright Spout luma value
	UINT32 resvd0                           :6;
	UINT32 reg_cdt_sdt                      :8;	//23:16	//Dark Vt standard deviation
	UINT32 resvd1                           :8;
	};
}PE_E60_REG_S2H_STAT_01_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171A8 RO
	UINT32 out_bs_cnt0                      :23;	//22:0	//Find Bright Spot bs_cnt0
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_02_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171AC RO
	UINT32 out_bs_cnt1                      :23;	//22:0	//Find Bright Spot bs_cnt1
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_03_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171B0 RO
	UINT32 out_bs_cnt2                      :23;	//22:0	//Find Bright Spot bs_cnt2
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_04_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171B4 RO
	UINT32 out_bs_cnt3                      :23;	//22:0	//Find Bright Spot bs_cnt3
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_05_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171B8 RO
	UINT32 out_bs_cnt4                      :23;	//22:0	//Find Bright Spot bs_cnt4
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_06_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171BC RO
	UINT32 out_bs_cnt5                      :23;	//22:0	//Find Bright Spot bs_cnt5
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_07_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171C0 RO
	UINT32 out_bs_cnt6                      :23;	//22:0	//Find Bright Spot bs_cnt6
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_08_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171C4 RO
	UINT32 out_bs_cnt7                      :23;	//22:0	//Find Bright Spot bs_cnt7
	UINT32 resvd                            :9;
	};
}PE_E60_REG_S2H_STAT_09_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171D0 RW
	UINT32 hif_hist_address                 :7;	//6:0	//"0"   : 0th bin	"1'   : 1st bin	…	"31" : 31st bin
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
}PE_E60_REG_S2H_C4_HIST_IA_CTRL_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171D4 RW
	UINT32 hist_status0                     :32;	//31:0	//[22:0]hif_histogram_bin_read
	};
}PE_E60_REG_S2H_C4_HIST_IA_DATA1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC90171D8 RO
	UINT32 hist_v_min                       :16;	//15:0	//[15:0]hist_v_min   : Minimum pixel value for one frame
	UINT32 hist_v_max                       :16;	//31:16	//[31:16]hist_v_max : Maximum pixel value for one frame
	};
}PE_E60_REG_S2H_C4_HIST_IA_DATA2_T;

typedef struct {
	PE_E60_REG_S2H_CTRL_00_T                   hdr_sdr2hdr_ctrl_00;	//0xC9017000
	PE_E60_REG_S2H_CTRL_01_T                   hdr_sdr2hdr_ctrl_01;	//0xC9017004
	PE_E60_REG_S2H_CTRL_02_T                   hdr_sdr2hdr_ctrl_02;	//0xC9017008
	PE_E60_REG_S2H_CTRL_03_T                   hdr_sdr2hdr_ctrl_03;	//0xC901700C
	PE_E60_REG_S2H_CTRL_04_T                   hdr_sdr2hdr_ctrl_04;	//0xC9017010
	PE_E60_REG_S2H_CTRL_05_T                   hdr_sdr2hdr_ctrl_05;	//0xC9017014
	PE_E60_REG_S2H_CTRL_06_T                   hdr_sdr2hdr_ctrl_06;	//0xC9017018
	PE_E60_REG_S2H_CTRL_07_T                   hdr_sdr2hdr_ctrl_07;	//0xC901701C
	PE_E60_REG_S2H_CTRL_08_T                   hdr_sdr2hdr_ctrl_08;	//0xC9017020
	PE_E60_REG_S2H_CTRL_09_T                   hdr_sdr2hdr_ctrl_09;	//0xC9017024
	PE_E60_REG_S2H_CTRL_10_T                   hdr_sdr2hdr_ctrl_10;	//0xC9017028
	PE_E60_REG_S2H_CTRL_11_T                   hdr_sdr2hdr_ctrl_11;	//0xC901702C
	PE_E60_REG_S2H_CTRL_12_T                   hdr_sdr2hdr_ctrl_12;	//0xC9017030
	PE_E60_REG_S2H_CTRL_13_T                   hdr_sdr2hdr_ctrl_13;	//0xC9017034
	PE_E60_REG_S2H_CTRL_14_T                   hdr_sdr2hdr_ctrl_14;	//0xC9017038
	PE_E60_REG_S2H_CTRL_15_T                   hdr_sdr2hdr_ctrl_15;	//0xC901703C
	PE_E60_REG_S2H_CTRL_16_T                   hdr_sdr2hdr_ctrl_16;	//0xC9017040
	PE_E60_REG_S2H_CTRL_17_T                   hdr_sdr2hdr_ctrl_17;	//0xC9017044
	PE_E60_REG_S2H_CTRL_18_T                   hdr_sdr2hdr_ctrl_18;	//0xC9017048
	PE_E60_REG_S2H_CTRL_19_T                   hdr_sdr2hdr_ctrl_19;	//0xC901704C
	PE_E60_REG_S2H_CTRL_20_T                   hdr_sdr2hdr_ctrl_20;	//0xC9017050
	PE_E60_REG_S2H_CTRL_21_T                   hdr_sdr2hdr_ctrl_21;	//0xC9017054
	PE_E60_REG_S2H_CTRL_22_T                   hdr_sdr2hdr_ctrl_22;	//0xC9017058
	PE_E60_REG_S2H_CTRL_23_T                   hdr_sdr2hdr_ctrl_23;	//0xC901705C
	PE_E60_REG_S2H_CTRL_24_T                   hdr_sdr2hdr_ctrl_24;	//0xC9017060
	PE_E60_REG_S2H_CTRL_25_T                   hdr_sdr2hdr_ctrl_25;	//0xC9017064
	PE_E60_REG_S2H_CTRL_26_T                   hdr_sdr2hdr_ctrl_26;	//0xC9017068
	PE_E60_REG_S2H_CTRL_27_T                   hdr_sdr2hdr_ctrl_27;	//0xC901706C
	PE_E60_REG_S2H_CTRL_28_T                   hdr_sdr2hdr_ctrl_28;	//0xC9017070
	PE_E60_REG_S2H_CTRL_29_T                   hdr_sdr2hdr_ctrl_29;	//0xC9017074
	PE_E60_REG_S2H_CTRL_30_T                   hdr_sdr2hdr_ctrl_30;	//0xC9017078
	PE_E60_REG_S2H_CTRL_31_T                   hdr_sdr2hdr_ctrl_31;	//0xC901707C
	PE_E60_REG_S2H_CTRL_32_T                   hdr_sdr2hdr_ctrl_32;	//0xC9017080
	PE_E60_REG_S2H_CTRL_33_T                   hdr_sdr2hdr_ctrl_33;	//0xC9017084
	PE_E60_REG_S2H_CTRL_34_T                   hdr_sdr2hdr_ctrl_34;	//0xC9017088
	PE_E60_REG_S2H_CTRL_35_T                   hdr_sdr2hdr_ctrl_35;	//0xC901708C
	PE_E60_REG_S2H_CTRL_36_T                   hdr_sdr2hdr_ctrl_36;	//0xC9017090
	PE_E60_REG_S2H_CTRL_37_T                   hdr_sdr2hdr_ctrl_37;	//0xC9017094
	PE_E60_REG_S2H_CTRL_38_T                   hdr_sdr2hdr_ctrl_38;	//0xC9017098
	PE_E60_REG_S2H_CTRL_39_T                   hdr_sdr2hdr_ctrl_39;	//0xC901709C
	PE_E60_REG_S2H_CTRL_40_T                   hdr_sdr2hdr_ctrl_40;	//0xC90170A0
	PE_E60_REG_S2H_CTRL_41_T                   hdr_sdr2hdr_ctrl_41;	//0xC90170A4
	PE_E60_REG_S2H_CTRL_42_T                   hdr_sdr2hdr_ctrl_42;	//0xC90170A8
	PE_E60_REG_S2H_CTRL_43_T                   hdr_sdr2hdr_ctrl_43;	//0xC90170AC
	PE_E60_REG_S2H_CTRL_44_T                   hdr_sdr2hdr_ctrl_44;	//0xC90170B0
	PE_E60_REG_S2H_CTRL_45_T                   hdr_sdr2hdr_ctrl_45;	//0xC90170B4
	PE_E60_REG_S2H_CTRL_46_T                   hdr_sdr2hdr_ctrl_46;	//0xC90170B8
	PE_E60_REG_S2H_CTRL_47_T                   hdr_sdr2hdr_ctrl_47;	//0xC90170BC
	PE_E60_REG_S2H_CTRL_48_T                   hdr_sdr2hdr_ctrl_48;	//0xC90170C0
	PE_E60_REG_S2H_CTRL_49_T                   hdr_sdr2hdr_ctrl_49;	//0xC90170C4
	PE_E60_REG_S2H_CTRL_50_T                   hdr_sdr2hdr_ctrl_50;	//0xC90170C8
	UINT32                                               reserved0;	//0xC90170CC
	PE_E60_REG_S2H_LLUT0_CTRL_00_T           sdr2hdr_llut0_ctrl_00;	//0xC90170D0
	PE_E60_REG_S2H_LLUT0_CTRL_01_T           sdr2hdr_llut0_ctrl_01;	//0xC90170D4
	PE_E60_REG_S2H_LLUT0_CTRL_02_T           sdr2hdr_llut0_ctrl_02;	//0xC90170D8
	PE_E60_REG_S2H_LLUT0_CTRL_03_T           sdr2hdr_llut0_ctrl_03;	//0xC90170DC
	PE_E60_REG_S2H_LLUT0_CTRL_04_T           sdr2hdr_llut0_ctrl_04;	//0xC90170E0
	PE_E60_REG_S2H_LLUT0_CTRL_05_T           sdr2hdr_llut0_ctrl_05;	//0xC90170E4
	PE_E60_REG_S2H_LLUT0_IA_CTRL_T           sdr2hdr_llut0_ia_ctrl;	//0xC90170E8
	PE_E60_REG_S2H_LLUT0_IA_DATA_T           sdr2hdr_llut0_ia_data;	//0xC90170EC
	PE_E60_REG_S2H_LLUT1_CTRL_00_T           sdr2hdr_llut1_ctrl_00;	//0xC90170F0
	PE_E60_REG_S2H_LLUT1_CTRL_01_T           sdr2hdr_llut1_ctrl_01;	//0xC90170F4
	PE_E60_REG_S2H_LLUT1_CTRL_02_T           sdr2hdr_llut1_ctrl_02;	//0xC90170F8
	PE_E60_REG_S2H_LLUT1_CTRL_03_T           sdr2hdr_llut1_ctrl_03;	//0xC90170FC
	PE_E60_REG_S2H_LLUT1_CTRL_04_T           sdr2hdr_llut1_ctrl_04;	//0xC9017100
	PE_E60_REG_S2H_LLUT1_CTRL_05_T           sdr2hdr_llut1_ctrl_05;	//0xC9017104
	PE_E60_REG_S2H_LLUT1_IA_CTRL_T           sdr2hdr_llut1_ia_ctrl;	//0xC9017108
	PE_E60_REG_S2H_LLUT1_IA_DATA_T           sdr2hdr_llut1_ia_data;	//0xC901710C
	UINT32                                               reserved1;	//0xC9017110
	UINT32                                               reserved2;	//0xC9017114
	UINT32                                               reserved3;	//0xC9017118
	UINT32                                               reserved4;	//0xC901711C
	UINT32                                               reserved5;	//0xC9017120
	UINT32                                               reserved6;	//0xC9017124
	UINT32                                               reserved7;	//0xC9017128
	UINT32                                               reserved8;	//0xC901712C
	PE_E60_REG_S2H_HIST_CTRL_00_T             sdr2hdr_hist_ctrl_00;	//0xC9017130
	PE_E60_REG_S2H_HIST_CTRL_01_T             sdr2hdr_hist_ctrl_01;	//0xC9017134
	PE_E60_REG_S2H_HIST_CTRL_02_T             sdr2hdr_hist_ctrl_02;	//0xC9017138
	PE_E60_REG_S2H_HIST_CTRL_03_T             sdr2hdr_hist_ctrl_03;	//0xC901713C
	PE_E60_REG_S2H_HIST_CTRL_04_T             sdr2hdr_hist_ctrl_04;	//0xC9017140
	PE_E60_REG_S2H_HIST_IA_CTRL_T             sdr2hdr_hist_ia_ctrl;	//0xC9017144
	PE_E60_REG_S2H_HIST_IA_DATA1_T           sdr2hdr_hist_ia_data1;	//0xC9017148
	PE_E60_REG_S2H_HIST_IA_DATA2_T           sdr2hdr_hist_ia_data2;	//0xC901714C
	PE_E60_REG_S2H_FBSLUT_CTRL_00_T         sdr2hdr_fbslut_ctrl_00;	//0xC9017150
	PE_E60_REG_S2H_FBSLUT_CTRL_01_T         sdr2hdr_fbslut_ctrl_01;	//0xC9017154
	PE_E60_REG_S2H_FBSLUT_CTRL_02_T         sdr2hdr_fbslut_ctrl_02;	//0xC9017158
	PE_E60_REG_S2H_FBSLUT_CTRL_03_T         sdr2hdr_fbslut_ctrl_03;	//0xC901715C
	PE_E60_REG_S2H_FBSLUT_CTRL_04_T         sdr2hdr_fbslut_ctrl_04;	//0xC9017160
	PE_E60_REG_S2H_FBSLUT_CTRL_05_T         sdr2hdr_fbslut_ctrl_05;	//0xC9017164
	PE_E60_REG_S2H_FBSLUT_IA_CTRL_T         sdr2hdr_fbslut_ia_ctrl;	//0xC9017168
	PE_E60_REG_S2H_FBS_LUT_IA_DATA_T           hdr_fbs_lut_ia_data;	//0xC901716C
	UINT32                                               reserved9;	//0xC9017170
	UINT32                                              reserved10;	//0xC9017174
	UINT32                                              reserved11;	//0xC9017178
	UINT32                                              reserved12;	//0xC901717C
	UINT32                                              reserved13;	//0xC9017180
	UINT32                                              reserved14;	//0xC9017184
	UINT32                                              reserved15;	//0xC9017188
	UINT32                                              reserved16;	//0xC901718C
	UINT32                                              reserved17;	//0xC9017190
	UINT32                                              reserved18;	//0xC9017194
	UINT32                                              reserved19;	//0xC9017198
	UINT32                                              reserved20;	//0xC901719C
	PE_E60_REG_S2H_STAT_00_T                   hdr_sdr2hdr_stat_00;	//0xC90171A0
	PE_E60_REG_S2H_STAT_01_T                   hdr_sdr2hdr_stat_01;	//0xC90171A4
	PE_E60_REG_S2H_STAT_02_T                   hdr_sdr2hdr_stat_02;	//0xC90171A8
	PE_E60_REG_S2H_STAT_03_T                   hdr_sdr2hdr_stat_03;	//0xC90171AC
	PE_E60_REG_S2H_STAT_04_T                   hdr_sdr2hdr_stat_04;	//0xC90171B0
	PE_E60_REG_S2H_STAT_05_T                   hdr_sdr2hdr_stat_05;	//0xC90171B4
	PE_E60_REG_S2H_STAT_06_T                   hdr_sdr2hdr_stat_06;	//0xC90171B8
	PE_E60_REG_S2H_STAT_07_T                   hdr_sdr2hdr_stat_07;	//0xC90171BC
	PE_E60_REG_S2H_STAT_08_T                   hdr_sdr2hdr_stat_08;	//0xC90171C0
	PE_E60_REG_S2H_STAT_09_T                   hdr_sdr2hdr_stat_09;	//0xC90171C4
	UINT32                                              reserved21;	//0xC90171C8
	UINT32                                              reserved22;	//0xC90171CC
	PE_E60_REG_S2H_C4_HIST_IA_CTRL_T       sdr2hdr_c4_hist_ia_ctrl;	//0xC90171D0
	PE_E60_REG_S2H_C4_HIST_IA_DATA1_T     sdr2hdr_c4_hist_ia_data1;	//0xC90171D4
	PE_E60_REG_S2H_C4_HIST_IA_DATA2_T     sdr2hdr_c4_hist_ia_data2;	//0xC90171D8
}PE_E60_REG_S2H_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9018500 RW
	UINT32 coremode0                 :4;	//3:0	//see PE_HDR_HW_E60_CORE_MODE_T
	UINT32 resvd0                   :28;	//31:4	//
	};
}PE_HDR_VERI_SYS_VERI_0_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9018504 RW
	UINT32 resvd0                   :32;	//31:0	//
	};
}PE_HDR_VERI_SYS_VERI_1_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC9018508 RW
	UINT32 resvd0                   :32;	//31:0	//
	};
}PE_HDR_VERI_SYS_VERI_2_T;

typedef union {
	UINT32 udata32;
	struct {						//0xC901850C RW
	UINT32 resvd0                   :32;	//31:0	//
	};
}PE_HDR_VERI_SYS_VERI_3_T;

typedef struct {
	PE_HDR_VERI_SYS_VERI_0_T                                info_0;	//0xC9018500
	PE_HDR_VERI_SYS_VERI_1_T                                info_1;	//0xC9018504
	PE_HDR_VERI_SYS_VERI_2_T                                info_2;	//0xC9018508
	PE_HDR_VERI_SYS_VERI_3_T                                info_3;	//0xC901850C
}PE_E60_REG_HDR_VERI_T;

#endif

