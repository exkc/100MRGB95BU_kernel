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

const PE_REG_PARAM_T cti_y_l_atv_default_m19[] =
{
	{0x358C, 0x00001001},    // CTI_CTRL_0
	{0x3590, 0x00003008},    // CTI_CTRL_0
	{0x37a0, 0xD8802000},
	{0x37a4, 0x80000000},
	{0xD550, 0x00001001},
	{0xD554, 0x00011810},
	{0xD558, 0x00880551},
};