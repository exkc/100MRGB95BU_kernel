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

const PE_REG_PARAM_T dnr_l_atv_default_m19[] =
{	
    {0x3594, 0x01780223},        // DNR_MAX_CTRL
    {0x3598, 0x00000004},        // DNR_DBAR_CTRL
    {0x35A0, 0x1000C041},        // MNR_CTRL_0
    {0x35A4, 0x143214FF},        // MNR_CTRL_1
    {0x35A8, 0x00000000},        // MNR_CTRL_2
    {0x35AC, 0x80F03060},        // MNR_CTRL_3
    {0x35B0, 0x03040608},        // MNR_CTRL_4
    {0x35B4, 0x04060812},        // MNR_CTRL_5
    {0x35B8, 0x04090A40},        // DETAIL_CTRL
    {0x35BC, 0x10304101},        // DC_BNR_CTRL_0
    {0x35C0, 0x54710102},        // DC_BNR_CTRL_1
    {0x35C4, 0x10000109},        // DC_BNR_CTRL_2
    {0x35C8, 0x04081020},        // DC_BNR_CTRL_3
    {0x35CC, 0x00FFFF00},        // DC_BNR_CTRL_4
    {0x35D0, 0x004080FF},        // DC_BNR_CTRL_5
    {0x35D4, 0xC010108F},        // AC_BNR_CTRL_0
    {0x35D8, 0x0F60C000},        // AC_BNR_CTRL_1
    {0x35DC, 0x00051040},        // AC_BNR_CTRL_2
    {0x35E4, 0x00C0E0FF},        // AC_BNR_CTRL_3
    {0x35E8, 0x60E05000},        // AC_BNR_CTRL_4
    {0x35F0, 0xFA963201},        // AC_BNR_CTRL_5
    {0x35F4, 0x00FFC0A0},        // AC_BNR_CTRL_6
    {0x35F8, 0x80FFA080},        // AC_BNR_CTRL_7
    {0x3600, 0x40000F00},        // AC_BNR_CTRL_8
    {0x3604, 0x00100000},        // AC_BNR_CTRL_9
    {0x3608, 0xFF00FF00},        // AC_BNR_CTRL_10
    {0x360C, 0xFF00FF00},        // AC_BNR_CTRL_11
    {0x3610, 0x0A40FFFF},        // AC_BNR_CTRL_12
    {0x366C, 0x00000000},        // SC_BNR_CTRL_0
    {0x3670, 0x00000000},        // SC_BNR_CTRL_1
    {0x3674, 0x00000000},        // SC_BNR_CTRL_2
    {0x3678, 0x00000000},        // SC_BNR_CTRL_3
    {0x367C, 0x00000000},        // SC_BNR_CTRL_4
    {0x3680, 0x00000000},        // SC_BNR_CTRL_5
    {0x3684, 0x00000000},        // SC_BNR_CTRL_6
    {0x369C, 0x00000000},        // AC_BNR_CTRL_13
    {0x36A0, 0x00000000},        // AC_BNR_CTRL_14
    {0x36A4, 0x40200500},        // DC_BNR_CTRL_6
    {0x36A8, 0x05050505},        // DC_BNR_CTRL_7
    {0x3730, 0x05102030},        // AC_BNR_15
    {0x3734, 0x204060FF},        // AC_BNR_16
    {0x3790, 0x20304060},        // REG_DC_BNR_CTRL_8
    {0x3794, 0xFFFFFFFF},        // REG_DC_BNR_CTRL_9
    {0x3798, 0xFFC0B040},        // REG_DC_BNR_CTRL_10
    {0x379C, 0x40404040},        // REG_DC_BNR_CTRL_11
    {0x37A8, 0xF0002010},        // REG_MNR_CTRL_6
    {0x37AC, 0x01020408},        // REG_MNR_CTRL_7
    {0x37B0, 0xFFC0A080},        // REG_MNR_CTRL_8
    {0x37B4, 0x050A1428},        // REG_MNR_CTRL_9
    {0x37B8, 0xFFA08060},        // REG_MNR_CTRL_10
    {0x37BC, 0x004080FF},        // REG_MNR_CTRL_11
    {0x37C0, 0x004080FF},        // REG_MNR_CTRL_12
    {0x3764, 0x800FF000},        // REG_DECON_CTRL_0
    {0x3768, 0x00000000},        // REG_DECON_CTRL_1
    {0x376C, 0x00000FFF},        // REG_DECON_CTRL_2
    {0x3770, 0x00FFFFFF},        // REG_DECON_CTRL_3
    {0x3774, 0x13579753},        // REG_DECON_CTRL_4
    {0x3778, 0x24680864},        // REG_DECON_CTRL_5
    {0x377C, 0x14703692},        // REG_DECON_CTRL_6
    {0x3780, 0x800FF000},        // REG_DECON_CTRL_7
    {0x3784, 0x30000000},        // REG_DECON_CTRL_8
    {0x3788, 0x00000FFF},        // REG_DECON_CTRL_9
    {0x378C, 0x00FFFFFF},        // REG_DECON_CTRL_10
    {0x37C4, 0x13579753},        // REG_DECON_CTRL_11
    {0x37C8, 0x24680864},        // REG_DECON_CTRL_12
    {0x37CC, 0x14703692},        // REG_DECON_CTRL_13
    {0x37D0, 0x00000000},        // REG_DECON_CTRL_14
    {0x37D4, 0x00000000},        // REG_DECON_CTRL_15
    {0x37D8, 0x00000000},        // REG_DECON_CTRL_16
    {0x37DC, 0x80000000},        // REG_DECON_CTRL_17
    {0x37E0, 0x525010A5},        // REG_DECON_CTRL_18
    {0x37E4, 0x3018150C},        // REG_DECON_CTRL_19
    {0x37E8, 0x000480FF},        // REG_DECON_CTRL_20
    {0x37EC, 0x00C0783C},        // REG_DECON_CTRL_21
    {0x37F0, 0x08040080},        // REG_DECON_CTRL_22
    {0x37F4, 0x0200003C},        // REG_DECON_CTRL_23
    {0x37F8, 0x0643212C},        // REG_DECON_CTRL_24
    {0x37FC, 0x190C8384},        // REG_DECON_CTRL_25
    {0x3800, 0x3E840100},        // REG_DECON_CTRL_26
    {0x3804, 0x10040100},        // REG_DECON_CTRL_27
    {0x3808, 0x10040100},        // REG_DECON_CTRL_28
    {0x380C, 0x00000000},        // REG_DECON_CTRL_29
    {0x3810, 0xC6280000},        // REG_DECON_CTRL_30
    {0x3814, 0xC0000000},        // REG_DECON_CTRL_31
    {0x3818, 0x00000000},        // REG_DECON_CTRL_32
    {0x381C, 0x00000000},        // REG_DECON_CTRL_33
    {0x3820, 0x00000000},        // REG_DECON_CTRL_34
    {0x3824, 0x00000000},        // REG_DECON_CTRL_35
    {0x3828, 0x00000000},        // REG_DECON_CTRL_36
    {0x382C, 0x00000000},        // REG_DECON_CTRL_37
    {0x3830, 0x00000000},        // REG_DECON_CTRL_38
    {0x3834, 0x00000000},        // REG_DECON_CTRL_39
    {0x3838, 0x00000000},        // REG_DECON_CTRL_40
    {0x383C, 0x00000000},        // REG_DECON_CTRL_41
    {0x3840, 0x00000000},        // REG_DECON_CTRL_42
    {0x3844, 0x00000000},        // REG_DECON_CTRL_43
    {0x3848, 0x16304060},        // REG_DECON_CTRL_44
    {0x384C, 0xFF804000},        // REG_DECON_CTRL_45
    {0x3850, 0x35031040},        // REG_DECON_CTRL_46
    {0x3854, 0x0071B399},        // REG_DECON_CTRL_47
    {0x3858, 0x1020303F},        // REG_DECON_CTRL_48
    {0x385C, 0xFF802006},        // REG_DECON_CTRL_49
    {0x3860, 0x9ABC4085},        // REG_DECON_CTRL_50
    {0x3864, 0x03C190C8},        // REG_DECON_CTRL_51
    {0x3868, 0x99096320},        // REG_DECON_CTRL_52
    {0x386C, 0x384FA100},        // REG_DECON_CTRL_53
    {0x3870, 0x10040100},        // REG_DECON_CTRL_54
    {0x3874, 0x10040100},        // REG_DECON_CTRL_55
    {0x3878, 0x10001007},        // REG_DECON_CTRL_56
    {0x387C, 0x00A03900},        // REG_DECON_CTRL_57
    {0x3880, 0x0B408000},        // REG_DECON_CTRL_58
    {0x3884, 0x6030180C},        // REG_DECON_CTRL_59
    {0x3888, 0x002080FF},        // REG_DECON_CTRL_60
    {0x388C, 0x34567890},        // REG_DECON_CTRL_61
    {0x3890, 0x45678901},        // REG_DECON_CTRL_62
    {0x3894, 0x7FFFFFFF},        // REG_DECON_CTRL_63
};