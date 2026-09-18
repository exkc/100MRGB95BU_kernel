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

const PE_REG_PARAM_T vflt_y_l_hd_p_default_o22[] =
{
	{0x800580, 0x00000000},    // VFILTER_CTRL_00
	{0x800584, 0x11100000},    // VFILTER_CTRL_01
	{0x800588, 0x00000000},    // VFILTER_CTRL_02
	{0x800738, 0x002000FF},    // VFILTER_CTRL_03
	{0x80073C, 0x00020408},    // VFILTER_CTRL_04
	{0x800740, 0x002080FF},    // VFILTER_CTRL_05
	{0x800744, 0x00000000},    // VFILTER_CTRL_06
	{0x800748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0x80074C, 0x00040810},    // VFILTER_CTRL_08
	{0x800750, 0x002080FF},    // VFILTER_CTRL_09
	{0x800754, 0x00000000},    // VFILTER_CTRL_10
	{0x800758, 0xFFFFFFFF},    // VFILTER_CTRL_11
	{0x80075C, 0x00000000},    // VFILTER_CTRL_12
	{0x800760, 0xFFFFFFFF},    // VFILTER_CTRL_13
};
