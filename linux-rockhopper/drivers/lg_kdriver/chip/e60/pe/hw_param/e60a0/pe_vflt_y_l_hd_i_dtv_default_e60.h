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

const PE_REG_PARAM_T vflt_y_l_hd_i_dtv_default_e60[] =
{
	{0xE580, 0x80281730},    // VFILTER_CTRL_00
	{0xE584, 0x11111010},    // VFILTER_CTRL_01
	{0xE588, 0x00011101},    // VFILTER_CTRL_02
	{0xE738, 0x000000FF},    // VFILTER_CTRL_03
	{0xE73C, 0x00081018},    // VFILTER_CTRL_04
	{0xE740, 0x004080FF},    // VFILTER_CTRL_05
	{0xE744, 0x00000000},    // VFILTER_CTRL_06
	{0xE748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0xE74C, 0x80A0C0E0},    // VFILTER_CTRL_08
	{0xE750, 0xFF802000},    // VFILTER_CTRL_09
	{0xE754, 0x02040810},    // VFILTER_CTRL_10
	{0xE758, 0xFF802000},    // VFILTER_CTRL_11
	{0xE75C, 0x02040810},    // VFILTER_CTRL_12
	{0xE760, 0xFFC08000},    // VFILTER_CTRL_13
};
