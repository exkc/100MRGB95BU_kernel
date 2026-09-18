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

const PE_REG_PARAM_T clc_l_sd_50_default_o26[] = 
{
	/* nd dnr1 clc, 0x4260~0x4278, 0x436C*/
	{0x290260, 0x78051030},	//CLC_CTRL_00
	{0x290264, 0xE012021A},	//CLC_CTRL_01
	{0x290268, 0x19000985},	//CLC_CTRL_02
	{0x29026C, 0xC1A08030},	//CLC_CTRL_03
	{0x290270, 0x00008020},	//CLC_CTRL_04
	{0x290274, 0x00008001},	//CLC_CTRL_05
	{0x290278, 0xC0007C00},	//CLC_CTRL_06
	{0x29036C, 0x20000700}	//CLC_CTRL_07
};
