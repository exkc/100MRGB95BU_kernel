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

const UINT32 sqm_tnr_init_f20[] =
{
	0x00000000,  //UINT32 reg_SQM_master_gain [4];
	0x60606060,  //UINT32 sqm_tnr_fw_gain_x_min[4];
	0x80808080,  //UINT32 sqm_tnr_fw_gain_x_max[4];
	0x70707060,  //UINT32 sqm_tnr_fw_gain_y_min[4];
	0x80808070,  //UINT32 sqm_tnr_fw_gain_y_max[4];
	0x00000000,  //UINT32 reg_temp_4[4];
	0x00000000,  //UINT32 reg_temp_5[4];
	0x00000000,  //UINT32 reg_temp_6[4];
	0x00000000,  //UINT32 reg_temp_7[4];
	0x00000000,  //UINT32 reg_temp_8[4];
	0x00000000,  //UINT32 reg_temp_9[4];
};