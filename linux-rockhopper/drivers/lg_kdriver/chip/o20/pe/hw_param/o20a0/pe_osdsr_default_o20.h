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

const PE_REG_PARAM_T osdsr_default_o20[] =
{
	/* C901XXXX */
	{0x11CA0, 0x00002011},      // SHP_LTI_CTRL_00
	{0x11CA4, 0x80FF1000},      // SHP_LTI_CTRL_01
	{0x11D00, 0xB01001E1},      // SHP_DJ_CTRL_00
	{0x11D04, 0x0040000A},      // SHP_DJ_CTRL_01
	{0x11D08, 0x00001203},      // SHP_DJ_CTRL_02
	{0x11D0C, 0x60301C28},      // SHP_DJ_CTRL_03
	{0x11D20, 0x00000000},      // SHP_DIR_BLUR_CTRL_00
	{0x11D24, 0x0040000A},      // SHP_DIR_BLUR_CTRL_01
	{0x11DC0, 0x00000001},      // SHP_CC_CTRL_00
	{0x11DC4, 0x80909060},      // SHP_CC_CTRL_01
};
