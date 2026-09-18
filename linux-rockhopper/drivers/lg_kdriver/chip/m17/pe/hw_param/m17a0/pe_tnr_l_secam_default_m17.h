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

const PE_REG_PARAM_T tnr_l_secam_default_m17[] =
{
	/* nd tnr */
	{0x4140, 0x0941CB91},   //TNR_CTRL_00
	{0x4144, 0x010CF410},   //TNR_CTRL_01
	{0x4148, 0x200C493F},   //TNR_CTRL_02
	{0x414C, 0x00000000},   //TNR_CTRL_03
	{0x4150, 0x00000000},   //TNR_CTRL_04
	{0x4154, 0x01FFFF11},   //TNR_CTRL_05
	{0x4158, 0xF4A20810},   //TNR_CTRL_06
	{0x415C, 0x00000000},   //TNR_CTRL_07
	{0x4160, 0x39105610},   //TNR_CTRL_08
	{0x4164, 0x01C81010},   //TNR_CTRL_09
	{0x4168, 0xFFD8D000},   //TNR_CTRL_10
	{0x416C, 0xC4801113},   //TNR_CTRL_11
	{0x4180, 0x00661060},   //TNR_CTRL_16
	{0x4184, 0x00780028},   //TNR_CTRL_17
	{0x4188, 0x95989519},   //TNR_CTRL_18
	{0x418C, 0x91000000},   //TNR_CTRL_19
	{0x4190, 0x20101008},   //TNR_CTRL_20
	{0x4194, 0x00000002},   //TNR_CTRL_21
	{0x41A0, 0x80403902},   //TNR_CTRL_24
	{0x41A4, 0x00000208},   //TNR_CTRL_25
	{0x41A8, 0x00008388},   //TNR_CTRL_26
	{0x41AC, 0x00008388},   //TNR_CTRL_27
	{0x41B0, 0x00008388},   //TNR_CTRL_28
	{0x41B4, 0x1458FF02},   //TNR_CTRL_29
	{0x41B8, 0x0020FF20},   //TNR_CTRL_30
	{0x41BC, 0x18E44438},   //TNR_CTRL_31
	{0x41E0, 0x00000900},   //TNR_CTRL_32
	{0x41E4, 0x00000000},   //TNR_CTRL_33 //same protection off
	{0x41E8, 0x00000208},   //TNR_CTRL_34
	{0x41EC, 0x00008388},   //TNR_CTRL_35
	{0x42E0, 0x00000032},	//MMD_CTRL
	{0x43D0, 0x0808006C},   //TNR_CTRL_40
	{0x43D4, 0x30108020},   //TNR_CTRL_41
	{0x43D8, 0x50901000},   //TNR_CTRL_42
	{0x43DC, 0x40FF1800},   //TNR_CTRL_43
	{0x43E0, 0xA0FF3C00},   //TNR_CTRL_44
	{0x43E4, 0xC8FF3000},   //TNR_CTRL_45
	{0x43E8, 0x70002000},   //TNR_CTRL_46
	{0x43EC, 0x70001800},   //TNR_CTRL_47
	{0x43F0, 0x00000000},   //TNR_CTRL_48
	{0x4490, 0x00000000},	//tnr_etc_ctrl_00
	{0x4494, 0x00000000},	//tnr_etc_ctrl_01
	{0x4498, 0x62460000},	//tnr_etc_ctrl_02
	{0x449C, 0x00000000},	//tnr_etc_ctrl_03
	{0x44A0, 0x80404000},   //TNR_CTRL_56
	{0x44A4, 0xFFFFC480},   //TNR_CTRL_57
	{0x44A8, 0x068000FF},   //TNR_CTRL_58
	{0x44AC, 0x14000C40},   //TNR_CTRL_59
	{0x44B0, 0x40FF00FF},   //TNR_CTRL_60
	{0x44B4, 0xFFFF80FF},   //TNR_CTRL_61
};
