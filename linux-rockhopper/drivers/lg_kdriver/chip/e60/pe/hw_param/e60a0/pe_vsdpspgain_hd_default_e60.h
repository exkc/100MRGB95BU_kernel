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

const PE_REG_PARAM_T vsdpspgain_hd_default_e60[] =
{	
	{0xB500, 0x08700F00},  // PSP_CTRL00
	{0xB504, 0x44782020},  // PSP_CTRL01
	{0xB508, 0x40400006},  // PSP_CTRL02
	{0xB50C, 0x584A0020},  // EDGE_TH
	{0xB510, 0x2D420F1E},  // FG_POSITION
	{0xB514, 0x04112233},  // PERSPECT_LUT_X0
	{0xB518, 0x44555F6E},  // PERSPECT_LUT_X1
	{0xB51C, 0x9199B1BB},  // PERSPECT_LUT_X2
	{0xB520, 0xCCDDEEFC},  // PERSPECT_LUT_X3
	{0xB524, 0x00224466},  // PERSPECT_LUT_Y0
	{0xB528, 0x88C8E6FF},  // PERSPECT_LUT_Y1
	{0xB52C, 0xFFE6C888},  // PERSPECT_LUT_Y2
	{0xB530, 0x66442200},  // PERSPECT_LUT_Y3
	{0xB534, 0x00434868},  // PROB_MAP
	{0xB538, 0x048050A4},  // ELLIPS_MAP
	{0xB53C, 0x0C00C000},  // PROB_DIFF_MAP
	{0xB540, 0x0000030D},  // OBJECT_MAP
	{0xB544, 0x00000001},  // BLUR_MAP
	{0xB548, 0x00000000},  // DISPLAY_DEBUG_MAP
	{0xB54C, 0x0000003C},  // PSP_IIR
	{0xB550, 0x00000000},  // PSP_GAIN
	{0xB55C, 0xFF804000},  // VRTX_CPC_CTRL
	{0xB560, 0x00710071},  // BLUR_HCOEF01
	{0xB564, 0x00720072},  // BLUR_HCOEF23
	{0xB568, 0x00720074},  // BLUR_HCOEFF45
	{0xB56C, 0x00710072},  // BLUR_HCOEFF67
	{0xB570, 0x00000071},  // BLUR_HCOEF8
	{0xB574, 0x00CC00CC},  // BLUR_VCOEF01
	{0xB578, 0x000000CC},  // BLUR_VCOEF23
	{0xB57C, 0x00CC00D0},  // BLUR_VCOEF4
};