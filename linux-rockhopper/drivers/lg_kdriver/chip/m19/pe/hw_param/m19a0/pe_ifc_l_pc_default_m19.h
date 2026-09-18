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
/* ifc off : all input except atv ntsc. */
const PE_REG_PARAM_T ifc_l_pc_default_m19[] =
{
	/* nd dnr ifc, 0x3614~0x3668 */
	{0x3614, 0x00E8D800}, // IFC_CTRL_0
	{0x3618, 0x0C003820}, // IFC_CTRL_1
	{0x361C, 0x00000000}, // IFC_CTRL_2
	{0x3620, 0x11006E20}, // IFC_CTRL_3
	{0x3624, 0x00031203}, // IFC_CTRL_4
	{0x3628, 0x00006616}, // IFC_CTRL_5
	{0x3634, 0x24000000}, // IFC_CTRL_8
	{0x3644, 0x80040000}, // IFC_CTRL_12
	{0x3650, 0x064011FF}, // IFC_CTRL_15
	{0x3654, 0x001002A2}, // IFC_CTRL_16
	{0x3658, 0x8500DCFF}, // IFC_CTRL_17
	{0x3660, 0x21000000}, // IFC_CTRL_19
	{0x3668, 0x0080B000}, // IFC_CTRL_21
};
