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

const PE_REG_PARAM_T vflt_y_l_ud_default_o26[] =
{
	{0x290580, 0x00041430},    // VFILTER_CTRL_00
	{0x290584, 0x11110000},    // VFILTER_CTRL_01
	{0x290588, 0x00111101},    // VFILTER_CTRL_02
	{0x290738, 0xFFFFFFFF},    // VFILTER_CTRL_03
	{0x29073C, 0x00020408},    // VFILTER_CTRL_04
	{0x290740, 0x002080FF},    // VFILTER_CTRL_05
	{0x290744, 0x00000000},    // VFILTER_CTRL_06
	{0x290748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0x29074C, 0x10204080},    // VFILTER_CTRL_08
	{0x290750, 0xFF802000},    // VFILTER_CTRL_09
	{0x290754, 0x10204080},    // VFILTER_CTRL_10
	{0x290758, 0xFF802000},    // VFILTER_CTRL_11
	{0x29075C, 0x00102040},    // VFILTER_CTRL_12
	{0x290760, 0xFF802000},    // VFILTER_CTRL_13
};
