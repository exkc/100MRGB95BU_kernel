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

const PE_REG_PARAM_T vflt_y_l_hd_i_dtv_default_m17[] =
{
	{0x8180, 0x800C1730},    // VFILTER_CTRL_00
	{0x8184, 0x11110000},    // VFILTER_CTRL_01
	{0x8188, 0x00011101},    // VFILTER_CTRL_02
	{0x8338, 0x002000FF},    // VFILTER_CTRL_03
	{0x833C, 0x00020408},    // VFILTER_CTRL_04
	{0x8340, 0x002080FF},    // VFILTER_CTRL_05
	{0x8344, 0x00000000},    // VFILTER_CTRL_06
	{0x8348, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0x834C, 0x80A0C0F0},    // VFILTER_CTRL_08
	{0x8350, 0xFF802000},    // VFILTER_CTRL_09
	{0x8354, 0x10204080},    // VFILTER_CTRL_10
	{0x8358, 0xFF802000},    // VFILTER_CTRL_11
	{0x835C, 0x00102040},    // VFILTER_CTRL_12
	{0x8360, 0xFF802000},    // VFILTER_CTRL_13
};
