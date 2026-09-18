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

const PE_REG_PARAM_T obc_objt_l_sd_default_f20[] =
{
	{0xB300, 0x08700F00},    // PSP_CTRL00
	{0xB304, 0x44782020},    // PSP_CTRL01
	{0xB308, 0x00004000},    // PSP_CTRL02
	{0xB30C, 0x70600040},    // EDGE_TH
	{0xB310, 0x00000000},    // FG_POSITION
	{0xB314, 0x04112233},    // RESERVED0
	{0xB318, 0x44555F6E},    // RESERVED1
	{0xB31C, 0x9199B1BB},    // RESERVED2
	{0xB320, 0xCCDDEEFC},    // RESERVED3
	{0xB324, 0x00224466},    // RESERVED4
	{0xB328, 0x88C8E6FF},    // RESERVED5
	{0xB32C, 0xFFE6C888},    // RESERVED6
	{0xB330, 0x66442200},    // RESERVED7
	{0xB334, 0x00435555},    // PROB_MAP
	{0xB338, 0x040030FF},    // ELLIPS_MAP
	{0xB33C, 0x0C40C400},    // PROB_DIFF_MAP
	{0xB340, 0x00000404},    // OBJECT_MAP
	{0xB344, 0x00000001},    // BLUR_MAP
	{0xB348, 0x06000000},    // DISPLAY_DEBUG_MAP
	{0xB34C, 0x00000000},    // PSP_IIR
	{0xB350, 0x00000000},    // PSP_GAIN
	{0xB35C, 0xFF804000},    // VRTX_CPC_CTRL
	{0xB360, 0x00710071},    // BLUR_HCOEF01
	{0xB364, 0x00720072},    // BLUR_HCOEF23
	{0xB368, 0x00720074},    // BLUR_HCOEF45
	{0xB36C, 0x00710072},    // BLUR_HCOEF67
	{0xB370, 0x00000071},    // BLUR_HCOEF8
	{0xB374, 0x00CC00CC},    // BLUR_VCOEF01
	{0xB378, 0x00CC00D0},    // BLUR_VCOEF23
	{0xB37C, 0x000000CC},    // BLUR_VCOEF4
	{0xB400, 0x20200000},    // L5_GAIN_LUT1
	{0xB404, 0x3F3F3030},    // L5_GAIN_LUT2
	{0xB408, 0x20200000},    // L0_GAIN_LUT1
	{0xB40C, 0xFFFF8080},    // L0_GAIN_LUT2
	{0xB410, 0x064000C8},    // EDGE_WIN_H
	{0xB414, 0x03E80064},    // EDGE_WIN_V
	{0xB428, 0x0013F041},    // PSP_IIR1
	{0xB42C, 0x00201881},    // BG_MEASURE_CTRL
	{0xB444, 0x00000000},    // FACE0_SET
	{0xB448, 0x00000000},    // FACE1_SET
	{0xB44C, 0x00000000},    // FACE2_SET
	{0xB450, 0x00000000},    // FACE3_SET
	{0xB454, 0x00500040},    // ELLIPS0_SET
	{0xB458, 0x00500040},    // ELLIPS1_SET
	{0xB45C, 0x00500040},    // ELLIPS2_SET
	{0xB460, 0x00500040},    // ELLIPS3_SET

};
