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

const PE_REG_PARAM_T dnr_l_sd_dtv_default_m17c0[] =
{
	/* dnr, 0x7194~0x7198, 0x71A0~0x71DC, 0x71E4~0x71E8, 0x71F0~0x71F8, 0x7200~0x7210, 0x726C~0x728C */
	{0x4594, 0x00B80201},    // DNR_MAX_CTRL
	{0x45A0, 0x3000ffE1},    // MNR_CTRL_0
	{0x45A4, 0x143214FF},    // MNR_CTRL_1
	{0x45A8, 0x08FF00F0},    // MNR_CTRL_2
	{0x45AC, 0x80f03061},    // MNR_CTRL_3
	{0x45B0, 0x03040608},    // MNR_CTRL_4
	{0x45B4, 0x04060812},    // MNR_CTRL_5
	{0x45BC, 0x10300001},    // DC_BNR_CTRL_0
	{0x45C0, 0x4d790102},    // DC_BNR_CTRL_1
	{0x45C4, 0x154c8009},    // DC_BNR_CTRL_2
	{0x45C8, 0x15254080},    // DC_BNR_CTRL_3
	{0x45CC, 0x00FFFF00},    // DC_BNR_CTRL_4
	{0x45D0, 0x004080FF},    // DC_BNR_CTRL_5
	{0x45D4, 0xC010108F},    // AC_BNR_CTRL_0
	{0x45D8, 0x0f208000},    // AC_BNR_CTRL_1
	{0x45DC, 0x00051040},    // AC_BNR_CTRL_2
	{0x45E4, 0x80c0e0ff},    // AC_BNR_CTRL_3
	{0x45E8, 0x00000000},    // AC_BNR_CTRL_4
	{0x45F0, 0xFA963201},    // AC_BNR_CTRL_5
	{0x45F4, 0x00FFD0C0},    // AC_BNR_CTRL_6
	{0x45F8, 0xA0FFC0A0},    // AC_BNR_CTRL_7
	{0x4600, 0x80000F20},    // AC_BNR_CTRL_8
	{0x4604, 0x00008000},    // AC_BNR_CTRL_9
	{0x4608, 0xFF00FF00},    // AC_BNR_CTRL_10
	{0x460C, 0xFF00FF00},    // AC_BNR_CTRL_11
	{0x4610, 0x0A40FFFF},    // AC_BNR_CTRL_12
	{0x466C, 0x00000000},    // SC_BNR_CTRL_0
	{0x4670, 0x00000000},    // SC_BNR_CTRL_1
	{0x4674, 0x00000000},    // SC_BNR_CTRL_2
	{0x4678, 0x00000000},    // SC_BNR_CTRL_3
	{0x467C, 0x00000000},    // SC_BNR_CTRL_4
	{0x4680, 0x00000000},    // SC_BNR_CTRL_5
	{0x4684, 0x00000000},    // SC_BNR_CTRL_6
	{0x46A4, 0x40200500},    // DC_BNR_CTRL_6
	{0x46A8, 0x05050510},    // DC_BNR_CTRL_7
	{0x4730, 0x05102040},    // AC_BNR_15
	{0x4734, 0x30406080},    // AC_BNR_16
	{0x4764, 0x80000003},    // REG_DECON_CTRL_0
	{0x4768, 0x52500001},    // REG_DECON_CTRL_1
	{0x476C, 0x70503018},    // REG_DECON_CTRL_2
	{0x4770, 0x00204080},    // REG_DECON_CTRL_3
	{0x4774, 0x10080402},    // REG_DECON_CTRL_4
	{0x4778, 0x004488FF},    // REG_DECON_CTRL_5
	{0x477C, 0x6432190F},    // REG_DECON_CTRL_6
	{0x4780, 0xFAE1C896},    // REG_DECON_CTRL_7
	{0x4784, 0x80808080},    // REG_DECON_CTRL_8
	{0x4788, 0x80808080},    // REG_DECON_CTRL_9
	{0x478C, 0x00000000},    // REG_DECON_CTRL_10
	{0x4790, 0x10203040},    // REG_DC_BNR_CTRL_8
	{0x4794, 0x60ffffff},    // REG_DC_BNR_CTRL_9
	{0x4798, 0x80605040},    // REG_DC_BNR_CTRL_10
	{0x479C, 0x40404040}     // REG_DC_BNR_CTRL_11	

};
