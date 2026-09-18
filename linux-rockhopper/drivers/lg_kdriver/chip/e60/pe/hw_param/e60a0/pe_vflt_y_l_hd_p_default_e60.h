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

const PE_REG_PARAM_T vflt_y_l_hd_p_default_e60[] =
{
	{0xE580, 0x00000000},    // VFILTER_CTRL_00
	{0xE584, 0x11100000},    // VFILTER_CTRL_01
	{0xE588, 0x00000000},    // VFILTER_CTRL_02
	{0xE738, 0x002000FF},    // VFILTER_CTRL_03
	{0xE73C, 0x00020408},    // VFILTER_CTRL_04
	{0xE740, 0x002080FF},    // VFILTER_CTRL_05
	{0xE744, 0x00000000},    // VFILTER_CTRL_06
	{0xE748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0xE74C, 0x00040810},    // VFILTER_CTRL_08
	{0xE750, 0x002080FF},    // VFILTER_CTRL_09
	{0xE754, 0x00000000},    // VFILTER_CTRL_10
	{0xE758, 0xFFFFFFFF},    // VFILTER_CTRL_11
	{0xE75C, 0x00000000},    // VFILTER_CTRL_12
	{0xE760, 0xFFFFFFFF},    // VFILTER_CTRL_13
};
