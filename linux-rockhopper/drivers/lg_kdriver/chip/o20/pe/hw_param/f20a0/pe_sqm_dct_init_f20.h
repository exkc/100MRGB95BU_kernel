/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2013 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

const UINT32 sqm_dct_init_f20[] =
{
	0xA0A0A0A0,  //UINT32 reg_SQM_master_gain [4];
	0x20202020,  //UINT32 reg_decon_gain_min[4];
	0x80808080,  //UINT32 reg_decon_gain_max[4];
	0x02020202,  //UINT32 reg_decon_gain_inc[4];
	0x42424242,  //UINT32 reg_decon_gmv[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th0[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th1[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th2[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th3[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th4[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th5[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th6[4];
	0x50404040,  //UINT32 reg_decon_fw_luma_y_th7[4];
	0x00000000,  //sqm_dec_reg_diff_calc_mode
	0x00000000,  //sqm_dec_reg_alpha_blur_mode
	0x00000000,  //sqm_dec_reg_diff_shift
	0x00000000,  //sqm_dec_reg_diff_mul_new
	0x00000000,  //sqm_dec_reg_decon_diff_y_th3
	0x00000000,  //sqm_dec_reg_decon_diff_y_th2
	0x00000000,  //sqm_dec_reg_decon_diff_y_th1
	0x00000000,  //sqm_dec_reg_decon_diff_y_th0
	0x00000000,  //UINT32 reg_temp_8[4];
	0x00000000,  //UINT32 reg_temp_9[4];
};
