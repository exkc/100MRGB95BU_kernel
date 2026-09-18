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

const PE_REG_PARAM_T amg_mtb_l_hd_default_o24[] =
{
	{0x825800, 0xffffc5c5},	   //CA_CTRL_00 
	{0x825804, 0x8b8b5050},	   //CA_CTRL_01 
	{0x825808, 0x19190000},	   //CA_CTRL_02 
	{0x82580C, 0xffc86400},	   //CA_CTRL_03 
	{0x825810, 0x3c003200},	   //CA_CTRL_04 
	{0x825814, 0x20001000},	   //CA_CTRL_05 
	{0x825818, 0xfffff7f7},	   //CA_CTRL_06 
	{0x82581C, 0xa9a95b5b},	   //CA_CTRL_07 
	{0x825820, 0x0e0e0000},	   //CA_CTRL_08 
	{0x825824, 0xffffc5c5},	   //CA_CTRL_09 
	{0x825828, 0x8b8b5050},	   //CA_CTRL_10 
	{0x82582C, 0x19190000},	   //CA_CTRL_11 
	{0x825830, 0xffc86400},	   //CA_CTRL_12 
	{0x825834, 0x3c003200},	   //CA_CTRL_13 
	{0x825838, 0x20001000},	   //CA_CTRL_14 
	{0x82583C, 0xfffff7f7},	   //CA_CTRL_15 
	{0x825840, 0xa9a95b5b},	   //CA_CTRL_16 
	{0x825844, 0x0e0e0000},	   //CA_CTRL_17 
	{0x825848, 0xffffc0c0},	   //CA_CTRL_18 
	{0x82584C, 0xa0a08080},	   //CA_CTRL_19 
	{0x825850, 0x40400000},	   //CA_CTRL_20 
	{0x825860, 0x00000000},	   //BLEND_CTRL_00 
	{0x825864, 0xff8046b0},	   //BLEND_CTRL_01 
	{0x825868, 0x32c01ee0},	   //BLEND_CTRL_02 
	{0x82586C, 0x05f000f0},	   //BLEND_CTRL_03 
	{0x825870, 0xff004600},	   //BLEND_CTRL_04 
	{0x825874, 0x32c01ee0},	   //BLEND_CTRL_05 
	{0x825878, 0x05f000f0},	   //BLEND_CTRL_06 
	{0x82587C, 0xffff46ff},	   //BLEND_CTRL_07 
	{0x825880, 0x32f01ee0},	   //BLEND_CTRL_08 
	{0x825884, 0x05c00080},	   //BLEND_CTRL_09 
	{0x825888, 0x00000001},	   //WARP_CTRL_00 
	{0x825890, 0x00001111},	   //BLF_CTRL_00 
	{0x825894, 0x3b3e3f3f},	   //BLF_CTRL_01 
	{0x825898, 0x2b303438},	   //BLF_CTRL_02 
	{0x82589C, 0x181d2126},	   //BLF_CTRL_03 
	{0x8258A0, 0x0b0d1114},	   //BLF_CTRL_04 
	{0x8258A4, 0x03050608},	   //BLF_CTRL_05 
	{0x8258A8, 0x01010202},	   //BLF_CTRL_06 
	{0x8258AC, 0x00000000},	   //BLF_CTRL_07 
	{0x8258B0, 0x00000000},	   //BLF_CTRL_08 
	{0x8258B4, 0x3b3e3f3f},	   //BLF_CTRL_09 
	{0x8258B8, 0x2b303438},	   //BLF_CTRL_10 
	{0x8258BC, 0x181d2126},	   //BLF_CTRL_11 
	{0x8258C0, 0x0b0d1114},	   //BLF_CTRL_12 
	{0x8258C4, 0x03050608},	   //BLF_CTRL_13 
	{0x8258C8, 0x01010202},	   //BLF_CTRL_14 
	{0x8258CC, 0x00000000},	   //BLF_CTRL_15 
	{0x8258D0, 0x00000000},	   //BLF_CTRL_16 
	{0x8258D4, 0x3b3e3f3f},	   //BLF_CTRL_17 
	{0x8258D8, 0x2b303438},	   //BLF_CTRL_18 
	{0x8258DC, 0x181d2126},	   //BLF_CTRL_19 
	{0x8258E0, 0x0b0d1114},	   //BLF_CTRL_20 
	{0x8258E4, 0x03050608},	   //BLF_CTRL_21 
	{0x8258E8, 0x01010202},	   //BLF_CTRL_22 
	{0x8258EC, 0x00000000},	   //BLF_CTRL_23 
	{0x8258F0, 0x00000000},	   //BLF_CTRL_24 
	{0x8258F4, 0x353b3e3f},	   //BLF_CTRL_25 
	{0x8258F8, 0x393d3e2e},	   //BLF_CTRL_26 
	{0x8258FC, 0x393b2d34},	   //BLF_CTRL_27 
	{0x825900, 0x002a3136},	   //BLF_CTRL_28 
	{0x825910, 0x00000001}	   //MEDIAN_CTRL_00 
};


	