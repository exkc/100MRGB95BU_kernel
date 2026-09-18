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

const UINT32 sqm_tnr_init_o20[] =
{
	0x00001409,  //UINT32 reg_SQM_master_gain [4];
	0x96969090,  //UINT32 sqm_tnr_fw_gain_x_min[4];
	0xC4C4B0B0,  //UINT32 sqm_tnr_fw_gain_x_max[4];
	0x8C8C6060,  //UINT32 sqm_tnr_fw_gain_y_min[4];
	0xFFFF9C9C,  //UINT32 sqm_tnr_fw_gain_y_max[4];
	0x00001810,  //UINT32 reg_temp_4[4];
	0x00770841,  //UINT32 reg_temp_5[4];
	0x00001409,  //UINT32 reg_temp_6[4];
	0x00002101,  //UINT32 reg_temp_7[4];
	0xC6804000,  //UINT32 reg_temp_8[4];
	0x06000000,  //UINT32 reg_temp_9[4];
};