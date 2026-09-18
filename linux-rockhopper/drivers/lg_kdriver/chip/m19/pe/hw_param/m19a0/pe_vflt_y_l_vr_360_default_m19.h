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

const PE_REG_PARAM_T vflt_y_l_vr_360_default_m19[] =
{
	{0x3580, 0x00000000},    // VFILTER_CTRL_00
	{0x3584, 0x11110000},    // VFILTER_CTRL_01
	{0x3588, 0x00000000},    // VFILTER_CTRL_02
	{0x3738, 0x002000FF},    // VFILTER_CTRL_03
	{0x373C, 0x00020408},    // VFILTER_CTRL_04
	{0x3740, 0x002080FF},    // VFILTER_CTRL_05
	{0x3744, 0x00000000},    // VFILTER_CTRL_06
	{0x3748, 0xFFFFFFFF},    // VFILTER_CTRL_07
	{0x374C, 0x00040810},    // VFILTER_CTRL_08
	{0x3750, 0x002080FF},    // VFILTER_CTRL_09
	{0x3754, 0x00000000},    // VFILTER_CTRL_10
	{0x3758, 0xFFFFFFFF},    // VFILTER_CTRL_11
	{0x375C, 0x00000000},    // VFILTER_CTRL_12
	{0x3760, 0xFFFFFFFF},    // VFILTER_CTRL_13
};
