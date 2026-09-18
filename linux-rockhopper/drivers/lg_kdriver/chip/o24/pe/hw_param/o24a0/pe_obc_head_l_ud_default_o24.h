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

const PE_REG_PARAM_T obc_head_l_ud_default_o24[] =
{
	{0xA20700, 0x08700F00},    // PSP_CTRL00
	{0xA20704, 0x00001010},    // PSP_CTRL01
	{0xA20708, 0x00000002},    // PSP_CTRL02
	{0xA20714, 0x008700F0},    // PSP_CTRL03
	{0xA20770, 0x06404040},    // REFINE_CTRL0
	{0xA20774, 0x20120400},    // REFINE_CTRL1
	{0xA20778, 0x021034FF},    // REFINE_CTRL2
};
