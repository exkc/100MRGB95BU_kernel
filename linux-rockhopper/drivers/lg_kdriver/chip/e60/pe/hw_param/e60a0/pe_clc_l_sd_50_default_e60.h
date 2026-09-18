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

const PE_REG_PARAM_T clc_l_sd_50_default_e60[] = 
{
	/* nd dnr1 clc, 0x4260~0x4278, 0x436C*/
	{0xE260, 0x78051030},	//CLC_CTRL_00
	{0xE264, 0xE012021A},	//CLC_CTRL_01
	{0xE268, 0x19000985},	//CLC_CTRL_02
	{0xE26C, 0xC1A08030},	//CLC_CTRL_03
	{0xE270, 0x00008020},	//CLC_CTRL_04
	{0xE274, 0x00008001},	//CLC_CTRL_05
	{0xE278, 0xC0007C00},	//CLC_CTRL_06
	{0xE36C, 0x20000700}	//CLC_CTRL_07
};
