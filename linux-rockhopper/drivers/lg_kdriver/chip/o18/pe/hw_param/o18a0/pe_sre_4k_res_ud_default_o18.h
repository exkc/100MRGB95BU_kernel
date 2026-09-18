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

const PE_REG_PARAM_T sre_4k_res_ud_default_o18[] =
{
    {0xA4A0, 0x00000010},      // SHP_ESF_CTRL_00
    {0xA4A4, 0x3030C814},      // SHP_ESF_CTRL_01
    {0xA4A8, 0x00000819},      // SHP_ESF_CTRL_02
    {0xA500, 0x00000000},      // SHP_DP_CTRL_00
    {0xA510, 0x0174031B},      // SHP_FD_CTRL_00
    {0xA514, 0x0000300E},      // SHP_FD_CTRL_01
    {0xA518, 0x0C011004},      // SHP_FD_CTRL_02
    {0xA51C, 0x40FF1000},      // SHP_FD_CTRL_03
    {0xA520, 0x50FF1800},      // SHP_FD_CTRL_04
    {0xA524, 0x50FF1000},      // SHP_FD_CTRL_05
    {0xA528, 0xFFFF0000},      // SHP_FD_CTRL_06
    {0xA52C, 0xFF240008},      // SHP_FD_CTRL_07
    {0xA530, 0xFF100810},      // SHP_FD_CTRL_08
    {0xA534, 0x00000010},      // SHP_FD_CTRL_09
    {0xA538, 0x00200000},      // SHP_FD_CTRL_0A
    {0xA53C, 0x40002005},      // SHP_FD_CTRL_0B
    {0xA540, 0x06200000},      // SHP_FD_CTRL_0C
    {0xA544, 0x22800B40},      // SHP_FD_CTRL_0D
    {0xA548, 0xBBFF7DC4},      // SHP_FD_CTRL_0E
    {0xA54C, 0x00000003},      // SHP_FD_CTRL_0F
    {0xA550, 0x0000086E},      // SHP_FD_CTRL_10
    {0xA554, 0x40300801},      // SHP_FD_CTRL_11
    {0xA558, 0x2C3E0402},      // SHP_FD_CTRL_12
    {0xA560, 0x00000001},      // SHP_MP_CTRL_00
    {0xA564, 0x20202020},      // SHP_MP_CTRL_01
    {0xA568, 0x00004000},      // SHP_MP_CTRL_02
    {0xA56C, 0x42006420},      // SHP_MP_CTRL_03
    {0xA570, 0x00000000},      // SHP_MP_CTRL_04
    {0xA574, 0x00020100},      // SHP_MP_CTRL_05
    {0xA578, 0x00FF2008},      // SHP_MP_CTRL_06
    {0xA57C, 0xFF604000},      // SHP_MP_CTRL_07
    {0xA580, 0x20C06020},      // SHP_MP_CTRL_08
    {0xA584, 0x20FFC060},      // SHP_MP_CTRL_09
    {0xA588, 0x0000C060},      // SHP_MP_CTRL_0A
    {0xA58C, 0x00000007},      // SHP_MP_CTRL_0B
    {0xA590, 0x20202008},      // SHP_MP_CTRL_0C
    {0xA5A0, 0xFFFF4011},      // SHP_LC_CTRL_00
    {0xA5A4, 0x20204030},      // SHP_LC_CTRL_01
    {0xA5A8, 0xFF304000},      // SHP_LC_CTRL_02
    {0xA5AC, 0x00000007},      // SHP_LC_CTRL_03
    {0xA5B0, 0x10100100},      // SHP_LC_CTRL_04
    {0xA5C0, 0x1E040000},      // SHP_DER_CTRL_00
    {0xA5C4, 0x81000005},      // SHP_DER_CTRL_01
    {0xA5C8, 0x00020200},      // SHP_DER_CTRL_02
    {0xA5CC, 0x00065008},      // SHP_DER_CTRL_03
    {0xA5D0, 0x00000008},      // SHP_DER_CTRL_04
    {0xA5D4, 0x00000000},      // SHP_DER_CTRL_05
    {0xA5D8, 0x30042000},      // SHP_DER_CTRL_06
    {0xA5DC, 0xA0E05008},      // SHP_DER_CTRL_07
    {0xA5E0, 0x00000001},      // SHP_SP_CTRL_00
    {0xA5E4, 0x00202020},      // SHP_SP_CTRL_01
    {0xA5E8, 0x00004000},      // SHP_SP_CTRL_02
    {0xA5EC, 0x60000000},      // SHP_SP_CTRL_03
    {0xA5F0, 0x00000000},      // SHP_SP_CTRL_04
    {0xA5F4, 0x00020101},      // SHP_SP_CTRL_05
    {0xA5F8, 0x00801008},      // SHP_SP_CTRL_06
    {0xA5FC, 0xFF604000},      // SHP_SP_CTRL_07
    {0xA600, 0x20C06020},      // SHP_SP_CTRL_08
    {0xA604, 0x20FFC060},      // SHP_SP_CTRL_09
    {0xA608, 0x0000C060},      // SHP_SP_CTRL_0A
    {0xA60C, 0x00000007},      // SHP_SP_CTRL_0B
    {0xA610, 0x08081018},      // SHP_SP_CTRL_0C
    {0xA620, 0x00002069},      // SHP_PTI_CTRL_00
    {0xA624, 0x00004029},      // SHP_PTI_CTRL_01
    {0xA628, 0x00000007},      // SHP_PTI_CTRL_02
    {0xA62C, 0x10102020},      // SHP_PTI_CTRL_03
    {0xA630, 0x80002051},      // SHP_STI_CTRL_00
    {0xA640, 0x50000011},      // SHP_TGEN_CTRL_00
    {0xA644, 0x06400810},      // SHP_TGEN_CTRL_01
    {0xA648, 0x003F0580},      // SHP_TGEN_CTRL_02
    {0xA64C, 0x000048AB},      // SHP_CORE0_TGEN_CTRL_03
    {0xA650, 0x000048AB},      // SHP_CORE1_TGEN_CTRL_03
    {0xA654, 0x02021F04},      // SHP_TGEN_CTRL_04
    {0xA658, 0x00080050},      // SHP_TGEN_CTRL_05
    {0xA65C, 0x1A000800},      // SHP_TGEN_CTRL_06
    {0xA660, 0x1A000800},      // SHP_TGEN_CTRL_07
    {0xA664, 0x3F801F1F},      // SHP_TGEN_CTRL_08
    {0xA668, 0x48ABCDFF},      // SHP_TGEN_CTRL_09
    {0xA66C, 0x00000007},      // SHP_TGEN_CTRL_0A
    {0xA670, 0x10100000},      // SHP_TGEN_CTRL_0B
    {0xA674, 0x00000410},      // SHP_SNR_CTRL_00
    {0xA680, 0x00000001},      // SHP_DCTP_CTRL_00
    {0xA684, 0x0FED0F99},      // SHP_DCTP_CTRL_01
    {0xA688, 0x025B0046},      // SHP_DCTP_CTRL_02
    {0xA68C, 0x002B0FF1},      // SHP_DCTP_CTRL_03
    {0xA690, 0x0FDC0FE1},      // SHP_DCTP_CTRL_04
    {0xA694, 0x0F680050},      // SHP_DCTP_CTRL_05
    {0xA698, 0x04DD0EA8},      // SHP_DCTP_CTRL_06
    {0xA69C, 0x0FB10F17},      // SHP_DCTP_CTRL_07
    {0xA6A0, 0x0FF80002},      // SHP_DCTP_CTRL_08
    {0xA6A4, 0x0F630059},      // SHP_DCTP_CTRL_09
    {0xA6A8, 0x04FE0E92},      // SHP_DCTP_CTRL_0A
    {0xA6AC, 0x0FAE0F08},      // SHP_DCTP_CTRL_0B
    {0xA6B0, 0x0FFA0004},      // SHP_DCTP_CTRL_0C
    {0xA6B4, 0x0F580063},      // SHP_DCTP_CTRL_0D
    {0xA6B8, 0x05160E86},      // SHP_DCTP_CTRL_0E
    {0xA6BC, 0x0FA90F00},      // SHP_DCTP_CTRL_0F
    {0xA6C0, 0x0FFA0007},      // SHP_DCTP_CTRL_10
    {0xA6C4, 0x0F680050},      // SHP_DCTP_CTRL_11
    {0xA6C8, 0x04DD0EA8},      // SHP_DCTP_CTRL_12
    {0xA6CC, 0x0FB10F17},      // SHP_DCTP_CTRL_13
    {0xA6D0, 0x0FF80002},      // SHP_DCTP_CTRL_14
    {0xA6D4, 0x0FB50005},      // SHP_DCTP_CTRL_15
    {0xA6D8, 0x03940F62},      // SHP_DCTP_CTRL_16
    {0xA6DC, 0x0FD70F93},      // SHP_DCTP_CTRL_17
    {0xA6E0, 0x0FF30FF4},      // SHP_DCTP_CTRL_18
    {0xA6E4, 0x80402000},      // SHP_DCTP_CTRL_19
    {0xA6E8, 0x0000FFC4},      // SHP_DCTP_CTRL_1A
    {0xA6EC, 0x200008E0},      // SHP_DCTP_CTRL_1B
    {0xA6F0, 0xC0FF60C0},      // SHP_DCTP_CTRL_1C
    {0xA6F4, 0x000000C0},      // SHP_DCTP_CTRL_1D
    {0xA6F8, 0x00000005},      // SHP_DCTP_CTRL_1E
    {0xA6FC, 0x20201010},      // SHP_DCTP_CTRL_1F
    {0xA700, 0x00000000},      // SHP_NNTG_CTRL_00
    {0xA704, 0x0000159C},      // SHP_CORE0_NNTG_CTRL_01
    {0xA708, 0x2CA37199},      // SHP_CORE0_NNTG_CTRL_02
    {0xA70C, 0x32363B62},      // SHP_CORE0_NNTG_CTRL_03
    {0xA710, 0xFD1CD00A},      // SHP_CORE0_NNTG_CTRL_04
    {0xA714, 0x8C3C2327},      // SHP_CORE0_NNTG_CTRL_05
    {0xA718, 0xF2759828},      // SHP_CORE1_NNTG_CTRL_01
    {0xA71C, 0xFEEA5094},      // SHP_CORE1_NNTG_CTRL_02
    {0xA720, 0xECBEACAA},      // SHP_CORE1_NNTG_CTRL_03
    {0xA724, 0xD9C5DFEA},      // SHP_CORE1_NNTG_CTRL_04
    {0xA728, 0x23E8D99E},      // SHP_CORE1_NNTG_CTRL_05
    {0xA72C, 0x00FF308C},      // SHP_NNTG_CTRL_06
    {0xA730, 0x0E120145},      // SHP_NNTG_CTRL_07
    {0xA734, 0x01E00FEE},      // SHP_NNTG_CTRL_08
    {0xA738, 0x0E11011E},      // SHP_NNTG_CTRL_09
    {0xA73C, 0x02100100},      // SHP_NNTG_CTRL_0A
    {0xA740, 0x05000320},      // SHP_NNTG_CTRL_0B
    {0xA744, 0x04FF0200},      // SHP_NNTG_CTRL_0C
    {0xA748, 0x40003040},      // SHP_NNTG_CTRL_0D
    {0xA74C, 0x40100860},      // SHP_NNTG_CTRL_0E
    {0xA750, 0x00000004},      // SHP_NNTG_CTRL_0F
    {0xA754, 0x10100000},      // SHP_NNTG_CTRL_10
    {0xA760, 0x00000080},      // SHP_DP_SUM_CTRL_00
};

