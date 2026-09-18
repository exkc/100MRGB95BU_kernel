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

const PE_REG_PARAM_T obc_face_l_sd_default_f20[] =
{
	{0xB500, 0x08700F00},    // PSP_CTRL00		
	{0xB504, 0x44782020},    // PSP_CTRL01
	{0xB508, 0x00004002},    // PSP_CTRL02
	{0xB50C, 0x70600040},    // EDGE_TH
	{0xB510, 0x00000000},    // FG_POSITION
	{0xB514, 0x30000000},    // RESERVED0
	{0xB518, 0x90404840},    // RESERVED1
	{0xB51C, 0x7C47AFC0},    // RESERVED2
	{0xB520, 0x47572F1F},    // RESERVED3
	{0xB524, 0x00000000},    // RESERVED4
	{0xB528, 0x00000000},    // RESERVED5
	{0xB52C, 0x00000000},    // RESERVED6
	{0xB530, 0x00000000},    // RESERVED7
	{0xB534, 0x00435555},    // PROB_MAP
	{0xB538, 0x440030AE},    // ELLIPS_MAP
	{0xB53C, 0x0C40C400},    // PROB_DIFF_MAP
	{0xB540, 0x00000404},    // OBJECT_MAP
	{0xB544, 0x00000001},    // BLUR_MAP
	{0xB548, 0x00008000},    // DISPLAY_DEBUG_MAP
	{0xB54C, 0x0000003A},    // PSP_IIR
	{0xB550, 0x00000000},    // PSP_GAIN
	{0xB55C, 0xFF804000},    // VRTX_CPC_CTRL
	{0xB560, 0x00710071},    // BLUR_HCOEF01
	{0xB564, 0x00720072},    // BLUR_HCOEF23
	{0xB568, 0x00720074},    // BLUR_HCOEF45
	{0xB56C, 0x00710072},    // BLUR_HCOEF67
	{0xB570, 0x00000071},    // BLUR_HCOEF8
	{0xB574, 0x00CC00CC},    // BLUR_VCOEF01
	{0xB578, 0x00CC00D0},    // BLUR_VCOEF23
	{0xB57C, 0x000000CC},    // BLUR_VCOEF4
	{0xB600, 0x20200000},    // L5_GAIN_LUT1
	{0xB604, 0x3F3F3030},    // L5_GAIN_LUT2
	{0xB608, 0x40200000},    // L0_GAIN_LUT1
	{0xB60C, 0xFFFF8080},    // L0_GAIN_LUT2
	{0xB610, 0x064000C8},    // EDGE_WIN_H
	{0xB614, 0x03E80064},    // EDGE_WIN_V
	{0xB628, 0x0013F041},    // PSP_IIR1
	{0xB62C, 0x00201881},    // BG_MEASURE_CTRL
	{0xB644, 0x9F2F4757},    // FACE0_SET
	{0xB648, 0x00000000},    // FACE1_SET
	{0xB64C, 0x00000000},    // FACE2_SET
	{0xB650, 0x00000000},    // FACE3_SET
	{0xB654, 0x00400038},    // ELLIPS0_SET
	{0xB658, 0x00400038},    // ELLIPS1_SET
	{0xB65C, 0x00400038},    // ELLIPS2_SET
	{0xB660, 0x00400038},    // ELLIPS3_SET

};
