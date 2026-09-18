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

const PE_REG_PARAM_T obc_head_l_ud_default_o22_toled[] =
{
	{0x460700, 0x04380780},    // PSP_CTRL00
	{0x460704, 0x44781010},    // PSP_CTRL01
	{0x460708, 0x00000002},    // PSP_CTRL02
	{0x460770, 0x12C00000},    // REFINE_CTRL0
	{0x460774, 0x20120400},    // REFINE_CTRL1
	{0x460778, 0xFFFFFFFF},    // REFINE_CTRL2
};