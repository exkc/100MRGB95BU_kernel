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

const PE_REG_PARAM_T vflt_y_l_hd_p_default_o24[] =
{
	{0xC60580, 0x00000000},    // VFILTER_CTRL_00
	{0xC60584, 0x11100000},    // VFILTER_CTRL_01
	{0xC60588, 0x00000000},    // VFILTER_CTRL_02
	{0xC60738, 0x002000FF},    // VFILTER_CTRL_03
	{0xC6073C, 0x00020408},    // VFILTER_CTRL_04
	{0xC60740, 0x002080FF},    // VFILTER_CTRL_05
	{0xC60744, 0x00000000},    // VFILTER_CTRL_06
	{0xC60748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0xC6074C, 0x00040810},    // VFILTER_CTRL_08
	{0xC60750, 0x002080FF},    // VFILTER_CTRL_09
	{0xC60754, 0x00000000},    // VFILTER_CTRL_10
	{0xC60758, 0xFFFFFFFF},    // VFILTER_CTRL_11
	{0xC6075C, 0x00000000},    // VFILTER_CTRL_12
	{0xC60760, 0xFFFFFFFF},    // VFILTER_CTRL_13
};
