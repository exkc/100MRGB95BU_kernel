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

const PE_REG_PARAM_T vsdpsptop_hd_default_o20[] =
{	
	{0xB28C, 0x00000004} ,    // REG_PSP_CTRL_00
	{0xB290, 0x000000FF} ,    // REG_PSP_CTRL_01
	{0xB294, 0x02000200} ,    // REG_PSP_CTRL_02
	{0xB2A0, 0x00000000} ,    // REG_PSP_CTRL_05
	{0xB300, 0x010000E0} ,    // REG_PSP_CTRL_06
	{0xB304, 0x01600180} ,    // REG_PSP_CTRL_07
	{0xB308, 0x02000240} ,    // REG_PSP_CTRL_08
	{0xB30C, 0x028002C0} ,    // REG_PSP_CTRL_09
	{0xB310, 0x03000360} ,    // REG_PSP_CTRL_10
	{0xB314, 0x036003C0} ,    // REG_PSP_CTRL_11
	{0xB318, 0x03FF03FF} ,    // REG_PSP_CTRL_12
	{0xB31C, 0x00000000} ,    // REG_PSP_CTRL_13
	{0xB320, 0x00920080} ,    // REG_PSP_CTRL_14
	{0xB324, 0x01240100} ,    // REG_PSP_CTRL_15
	{0xB328, 0x01B60140} ,    // REG_PSP_CTRL_16
	{0xB32C, 0x02480180} ,    // REG_PSP_CTRL_17
	{0xB330, 0x02DA01B0} ,    // REG_PSP_CTRL_18
	{0xB334, 0x036C01E0} ,    // REG_PSP_CTRL_19
	{0xB338, 0x03FF01FF} ,    // REG_PSP_CTRL_20
	{0xB33C, 0xFFA02000} ,    // REG_PSP_CTRL_21
	{0xB340, 0x80000040} ,    // REG_PSP_CTRL_22
};