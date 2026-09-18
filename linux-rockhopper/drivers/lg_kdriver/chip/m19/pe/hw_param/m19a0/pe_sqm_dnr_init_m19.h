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

const UINT32 sqm_dnr_init_m19[] =
{
	{0xffc0c0c0},  //reg_mnr_master_gain
	{0x00002101},  //reg_dc_bnr_chromagain
	{0xC6804000},  //reg_dc_bnr_mastergain
	{0x06000000},  //reg_ac_master_c_gain
	{0x00002051},  //reg_ac_master_y_gain
	{0x00001810},  //reg_master_gain_h_y
	{0x00770841},  //reg_master_gain_h_c
	{0x00001409},  //reg_master_gain_v_y
	{0x00002101},  //reg_master_gain_v_c
	{0x40181818},  //sqm_mnr_reg_th_max
	{0x80808080},  //sqm_mnr_reg_mmd_scale
	{0x00002051},  //reg_temp_2
	{0x00001810},  //reg_temp_3
	{0x00770841},  //reg_temp_4
	{0x00001409},  //reg_temp_5
	{0x00002101},  //reg_temp_6
	{0xC6804000},  //reg_temp_7
	{0x06000000},  //reg_temp_8
	{0x00002051},  //reg_temp_9
};