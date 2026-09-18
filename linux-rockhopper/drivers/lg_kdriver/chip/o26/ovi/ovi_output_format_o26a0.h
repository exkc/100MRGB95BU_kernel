/*
	SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
	Copyright(c) 2019 by LG Electronics Inc.

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	version 2 as published by the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.
*/

/** @file
 *
 *  Header file of defining possible of output modes of O26 Ax
 *
 *  author      dj911.kim@lge.com
 *  version		1.0
 *  date		2017.06.07
 *  note		Additional information.
 *
 *  @addtogroup lg115x_ovi
 *	@{
 */

/*----------------------------------------------------------------------------------------
 *   Control Constants
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   File Inclusions
 *---------------------------------------------------------------------------------------*/
#include "ovi_kapi.h"

/*----------------------------------------------------------------------------------------
 *   Constant Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Macro Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   Type Definitions
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Function Prototype Declarations
 *---------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------
 *   External Variables
 *---------------------------------------------------------------------------------------*/
__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k60_vx1_8lane[] = // Blended OSD
{ // Blended OSD
	//4byte
	// OIF
	{0xcc910004, 0x00000020},
	{0xcc910010, 0x00000001},
	{0xcc91001C, 0x000004d4}, //path 설정 변경
	{0xcc910090, 0x00000094}, //tcon_sgen_hbp
	{0xcc910094, 0x0000002c}, //tcon_sgen_hs
	{0xcc910098, 0x00000058}, //tcon_sgen_hfp
	{0xcc91009c, 0x00000048}, //tcon_sgen_vbp
	{0xcc9100a0, 0x0000000a}, //tcon_sgen_vs
	{0xcc9100a4, 0x00000008}, //tcon_sgen_vfp
	{0xcc9100a8, 0x00000780}, //tcon_sgen_dewidth
	{0xcc9100b0, 0x00000870}, //tcon_sgen_denum
	{0xcc9100b8, 0x00000060}, //tcon_vblank_width
	{0xcc9100bc, 0x00000004}, //tcon_vsync_width
	{0xcc9100d4, 0x00000000}, //tcon_pgen_ctl
	{0xcc910300, 0x00101082},
	{0xcc910304, 0x00020004},
	{0xcc910308, 0x00000f00},

	{0xcc919008, 0x00000082}, //수정됨
	{0xcc919098, 0x00010203}, //vx1_lane_sel0
	{0xcc91909c, 0x04050607}, //vx1_lane_sel1

	{0xcc9190d4, 0x00000010}, //vx1_apl_ctrl
	{0xcc9190d8, 0x00001010}, //vx1_info_ctrl0
	{0xcc9190dc, 0x00001019}, //vx1_info_ctrl
	{0xcc9101dc, 0x00000003}, //init test

	// CTOP : CLK   CRG
	{0xcc920010, 0x00000001}, //60hz
	{0xcc920014, 0x00101100}, //60hz

	// CTOP : C4TX
	{0xCC933010, 0x01000000}, //reg_rstn=1
	
	{0xCC933014, 0x00000040}, //ctrl_ext_reg_en=1
	{0xCC933010, 0x01000013}, //VX1 4byte
	{0xCC933010, 0x01010013}, //
	{0xCC933010, 0x01000000}, //WR_EN CLR
	
	{0xCC933014, 0x0000003f}, //link_ext_reg_en=1 (all link)
	{0xCC933010, 0x01001602}, //tx_lock_fixen=0, sel_clkpix=010
	{0xCC933010, 0x01011602},
	{0xCC933010, 0x01001801}, //count_txlock=01
	{0xCC933010, 0x01011801},
	{0xCC933010, 0x01001d02}, //read_addr_offset=10
	{0xCC933010, 0x01011d02},
	{0xCC933010, 0x01000b77}, //vod_cal=0111
	{0xCC933010, 0x01010b77},
	{0xCC933010, 0x01000c77}, //vod_cal=0111
	{0xCC933010, 0x01010c77},
	{0xCC933010, 0x01000409}, //itune=01001
	{0xCC933010, 0x01010409}, //
	{0xCC933010, 0x01000509}, //itune=01001
	{0xCC933010, 0x01010509},
	{0xCC933010, 0x01000f09}, //itune=01001
	{0xCC933010, 0x01010f09},
	{0xCC933010, 0x01000609}, //itune=01001
	{0xCC933010, 0x01010609},
	{0xCC933010, 0x01001009}, //itune=01001
	{0xCC933010, 0x01011009},
	{0xCC933010, 0x01000709}, //itune=01001
	{0xCC933010, 0x01010709},
	{0xCC933010, 0x01002609}, //itune=01001
	{0xCC933010, 0x01012609},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933014, 0x00000039}, //link_ext_reg_en=1 (link0/3/4/5)
	{0xCC933010, 0x01001200}, //link_clk_en=0
	{0xCC933010, 0x01011200},
	{0xCC933010, 0x01001430}, //link rstb = 0
	{0xCC933010, 0x01011430},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933024, 0x01000000}, //pdb=1

	{0x00000001, 0x00000064}, //100us delay

	{0xCC933024, 0x01000ff0}, //pdb_ch4~11=1
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933000, 0x00000001}, //vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k120_vx1_16lane[] = // Blended OSD
{ // Blended OSD
	//4byte
	//o26
	// CTOP : CLK	CRG 
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정
	{0xCC930090, 0x00000094},// tcon_sgen_hbp
	{0xCC930094, 0x0000002C},// tcon_sgen_hs
	{0xCC930098, 0x00000058},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 4byte
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000002},// 4byte

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010 
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010 
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010 
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010 
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k120_vx1_24lane_5byte[] = // 16lane video + 8lane separated OSD
{ 
	//OIF
	{0xcc910004, 0x00000020},
	{0xcc910010, 0x00000001},
	{0xcc91001C, 0x030000d4}, //0x94 bypass. F22 연결시에는 94
	{0xcc910090, 0x00000094}, //tcon_sgen_hbp
	{0xcc910094, 0x0000002c}, //tcon_sgen_hs
	{0xcc910098, 0x00000058}, //tcon_sgen_hfp
	{0xcc91009c, 0x00000048}, //tcon_sgen_vbp
	{0xcc9100a0, 0x0000000a}, //tcon_sgen_vs
	{0xcc9100a4, 0x00000008}, //tcon_sgen_vfp
	{0xcc9100a8, 0x00000780}, //tcon_sgen_dewidth
	{0xcc9100b0, 0x00000870}, //tcon_sgen_denum
	{0xcc9100b8, 0x00000060}, //tcon_vblank_width
	{0xcc9100bc, 0x00000004}, //tcon_vsync_width
	{0xcc9100d4, 0x00000000}, //tcon_pgen_ctl
	{0xcc910300, 0x00101102},
	{0xcc910304, 0x00020004},
	{0xcc910308, 0x00000f00},

	{0xcc919004, 0x00000007},
	{0xcc919008, 0x00000002},

	{0xcc919094, 0x00010203}, //vx1_lane_sel0
	{0xcc919098, 0x04050607}, //vx1_lane_sel1
	{0xcc91909c, 0x08090a0b}, //vx1_lane_sel2
	{0xcc9190a0, 0x0c0d0e0f}, //vx1_lane_sel3
	{0xcc9190a4, 0x10111213}, //vx1_lane_sel4
	{0xcc9190a8, 0x14151617}, //vx1_lane_sel5
	{0xcc9190b0, 0x00003010},
	{0xcc9190b4, 0x00002020}, //vx1_apl_ctrl
	{0xcc9190b8, 0x00001010},
	{0xcc9190bc, 0x00002020},
	{0xcc9101dc, 0x00000003}, // init test

	// CTOP : CLK	CRG
	{0xcc920010, 0x00000001}, //120hz
	{0xcc920014, 0x00001000}, //120hz

	// CTOP : C4TX	(#4~#19 사용)
	{0xCC933010, 0x01000000}, //reg_rstn=1
	{0xCC933014, 0x00000040}, //ctrl_ext_reg_en=1
	{0xCC933010, 0x01000033}, //VX1 5byte
	{0xCC933010, 0x01010033},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933014, 0x0000003f}, //link_ext_reg_en=1 (all link)
	{0xCC933010, 0x01001603}, //tx_lock_fixen=0, sel_clkpix=011
	{0xCC933010, 0x01011603},
	{0xCC933010, 0x01001803}, //count_txlock=03
	{0xCC933010, 0x01011803},
	{0xCC933010, 0x01001d03}, //read_addr_offset=11
	{0xCC933010, 0x01011d03},
	{0xCC933010, 0x01000b77}, //vod_cal=0111
	{0xCC933010, 0x01010b77},
	{0xCC933010, 0x01000c77}, //vod_cal=0111
	{0xCC933010, 0x01010c77},
	{0xCC933010, 0x01000409}, //itune=01001
	{0xCC933010, 0x01010409},
	{0xCC933010, 0x01000509}, //itune=01001
	{0xCC933010, 0x01010509},
	{0xCC933010, 0x01000f09}, //itune=01001
	{0xCC933010, 0x01010f09},
	{0xCC933010, 0x01000609}, //itune=01001
	{0xCC933010, 0x01010609},
	{0xCC933010, 0x01001009}, //itune=01001
	{0xCC933010, 0x01011009},
	{0xCC933010, 0x01000709}, //itune=01001
	{0xCC933010, 0x01010709},
	{0xCC933010, 0x01002609}, //itune=01001
	{0xCC933010, 0x01012609},

	{0xCC933014, 0x0000003f}, //ID에서 link off 되어 있어서 신규 설정함
	{0xCC933010, 0x0100120f},
	{0xCC933010, 0x0101120f},
	{0xCC933010, 0x0100143f},
	{0xCC933010, 0x0101143f},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933024, 0x01000000}, //pdb=1

	{0x00000001, 0x00000064}, //100us delay

	{0xCC933024, 0x01ffffff}, //pdb_ch0~23=1
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933000, 0x00000001}, //vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k120_vx1_16lane_5byte[] = // Blended OSD
{ // Blended OSD
	//5byte
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정
	{0xCC930090, 0x00000094},// tcon_sgen_hbp
	{0xCC930094, 0x0000002C},// tcon_sgen_hs
	{0xCC930098, 0x00000058},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum 

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 5byte
	{0xCC930304, 0x00000004},//
	{0xCC930308, 0x00000F00},//
	{0xCC939008, 0x00000006},// 5byte

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 5byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000033},// VX1 5byte
	{0xCC974010, 0x01010033},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001613},// tx_lock_fixen=1, sel_clkpix=011
	{0xCC974010, 0x01011613},
	{0xCC974010, 0x01001800},// count_txlock=00
	{0xCC974010, 0x01011800},
	{0xCC974010, 0x01001d03},// read_addr_offset=101
	{0xCC974010, 0x01011d03},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k120_vx1_16lane_5byte_G4_97inch[] = { // Blended OSD
	//5byte
	// OIF
	{0xcc910004, 0x00000020},
	{0xcc910010, 0x00000001},
	{0xcc91001C, 0x030000d4},
	{0xcc910090, 0x00000094}, //tcon_sgen_hbp
	{0xcc910094, 0x0000002c}, //tcon_sgen_hs
	{0xcc910098, 0x00000058}, //tcon_sgen_hfp
	{0xcc91009c, 0x00000048}, //tcon_sgen_vbp
	{0xcc9100a0, 0x0000000a}, //tcon_sgen_vs
	{0xcc9100a4, 0x00000008}, //tcon_sgen_vfp
	{0xcc9100a8, 0x00000780}, //tcon_sgen_dewidth
	{0xcc9100b0, 0x00000870}, //tcon_sgen_denum
	{0xcc9100b8, 0x00000060}, //tcon_vblank_width
	{0xcc9100bc, 0x00000004}, //tcon_vsync_width
	{0xcc9100d4, 0x00000000}, //tcon_pgen_ctl
	{0xcc910300, 0x00101102},
	{0xcc910304, 0x00020004},
	{0xcc910308, 0x00000f00},

	{0xcc919008, 0x00000086},
	{0xcc919098, 0x00010203}, //vx1_lane_sel0
	{0xcc91909c, 0x04050607}, //vx1_lane_sel1
	{0xcc9190a0, 0x08090a0b}, //vx1_lane_sel2
	{0xcc9190a4, 0x0c0d0e0f}, //vx1_lane_sel3
							  //vx1_lane_sel4
	{0xcc9190ac, 0x00000010}, //vx1_lane_sel5
	{0xcc9190d8, 0x00001010}, //vx1_apl_ctrl
	{0xcc9190dc, 0x00001019}, //vx1_info_ctrl0
	{0xcc9101dc, 0x00000003}, //vx1_info_ctrl1

	// CTOP : CLK   CRG
	{0xcc920010, 0x00000001},// 120hz
	{0xcc920014, 0x00001000},// 120hz

	// CTOP : C4TX
	{0xCC933010, 0x01000000}, //reg_rstn=1

	{0xCC933014, 0x00000040}, //ctrl_ext_reg_en=1
	{0xCC933010, 0x01000033}, //VX1 5byte
	{0xCC933010, 0x01010033},
	{0xCC933010, 0x01000000}, //WR_EN CLR

	{0xCC933014, 0x0000003f}, //link_ext_reg_en=1 (all link)
	{0xCC933010, 0x01001603}, //tx_lock_fixen=0, sel_clkpix=011
	{0xCC933010, 0x01011603},
	{0xCC933010, 0x01001803}, //count_txlock=03
	{0xCC933010, 0x01011803},
	{0xCC933010, 0x01001d03}, //read_addr_offset=11
	{0xCC933010, 0x01011d03},
	{0xCC933010, 0x01000b77}, //vod_cal=0111
	{0xCC933010, 0x01010b77},
	{0xCC933010, 0x01000c77}, //vod_cal=0111
	{0xCC933010, 0x01010c77},

	{0xCC933014, 0x0000003f}, //swing level=20
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000414},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010414},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000514},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010514},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000f14},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010f14},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01001014},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01011014},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000714},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010714},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01002614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01012614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000000},
	{0x00000001, 0x00000064}, //100us delay

	{0xCC933014, 0x0000003f}, //pemp=6
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000006},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010006},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000106},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010106},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000206},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010206},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000306},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010306},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000000}, 

	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933014, 0x00000021}, //link_ext_reg_en=1 (link0/5)
	{0xCC933010, 0x01001200}, //link_clk_en=0
	{0xCC933010, 0x01011200},
	{0xCC933010, 0x01001430}, //link rstb = 0
	{0xCC933010, 0x01011430},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933024, 0x01000000}, //pdb=1

	{0x00000001, 0x00000064}, //100us delay

	{0xCC933024, 0x010ffff0}, //pdb_ch4~19=1
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933000, 0x00000001}, //vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k120_vx1_16lane_5byte_G4_97inch_wirelessAV[] = { // Blended OSD
	//5byte
	// OIF
	{0xcc910004, 0x00000020},
	{0xcc910010, 0x00000001},
	{0xcc91001C, 0x030000d4},
	{0xcc910090, 0x00000094}, //tcon_sgen_hbp
	{0xcc910094, 0x0000002c}, //tcon_sgen_hs
	{0xcc910098, 0x00000058}, //tcon_sgen_hfp
	{0xcc91009c, 0x00000048}, //tcon_sgen_vbp
	{0xcc9100a0, 0x0000000a}, //tcon_sgen_vs
	{0xcc9100a4, 0x00000008}, //tcon_sgen_vfp
	{0xcc9100a8, 0x00000780}, //tcon_sgen_dewidth
	{0xcc9100b0, 0x00000870}, //tcon_sgen_denum
	{0xcc9100b8, 0x00000060}, //tcon_vblank_width
	{0xcc9100bc, 0x00000004}, //tcon_vsync_width
	{0xcc9100d4, 0x00000000}, //tcon_pgen_ctl
	{0xcc910300, 0x00101102},
	{0xcc910304, 0x00020004},
	{0xcc910308, 0x00000f00},

	{0xcc919008, 0x00000086},
	{0xcc919098, 0x00010203}, //vx1_lane_sel0
	{0xcc91909c, 0x04050607}, //vx1_lane_sel1
	{0xcc9190a0, 0x08090a0b}, //vx1_lane_sel2
	{0xcc9190a4, 0x0c0d0e0f}, //vx1_lane_sel3
							  //vx1_lane_sel4
	{0xcc9190ac, 0x00000010}, //vx1_lane_sel5
	{0xcc9190d8, 0x00001010}, //vx1_apl_ctrl
	{0xcc9190dc, 0x00001019}, //vx1_info_ctrl0
	{0xcc9101dc, 0x00000003}, //vx1_info_ctrl1

	// CTOP : CLK   CRG
	{0xcc920010, 0x00000001},// 120hz
	{0xcc920014, 0x00001000},// 120hz

	// CTOP : C4TX
	{0xCC933010, 0x01000000}, //reg_rstn=1

	{0xCC933014, 0x00000040}, //ctrl_ext_reg_en=1
	{0xCC933010, 0x01000033}, //VX1 5byte
	{0xCC933010, 0x01010033},
	{0xCC933010, 0x01000000}, //WR_EN CLR

	{0xCC933014, 0x0000003f}, //link_ext_reg_en=1 (all link)
	{0xCC933010, 0x01001603}, //tx_lock_fixen=0, sel_clkpix=011
	{0xCC933010, 0x01011603},
	{0xCC933010, 0x01001803}, //count_txlock=03
	{0xCC933010, 0x01011803},
	{0xCC933010, 0x01001d03}, //read_addr_offset=11
	{0xCC933010, 0x01011d03},
	{0xCC933010, 0x01000b77}, //vod_cal=0111
	{0xCC933010, 0x01010b77},
	{0xCC933010, 0x01000c77}, //vod_cal=0111
	{0xCC933010, 0x01010c77},

	{0xCC933014, 0x0000003f}, //swing level=20
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000414},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010414},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000514},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010514},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000f14},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010f14},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01001014},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01011014},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000714},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010714},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01002614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01012614},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000000},
	{0x00000001, 0x00000064}, //100us delay

	{0xCC933014, 0x0000003f}, //pemp=6
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000006},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010006},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000106},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010106},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000206},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010206},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000306},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01010306},
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933010, 0x01000000}, 

	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933014, 0x00000021}, //link_ext_reg_en=1 (link0/5)
	{0xCC933010, 0x01001200}, //link_clk_en=0
	{0xCC933010, 0x01011200},
	{0xCC933010, 0x01001430}, //link rstb = 0
	{0xCC933010, 0x01011430},
	{0xCC933010, 0x01000000}, //WR_EN CLR
	{0xCC933024, 0x01000000}, //pdb=1

	{0x00000001, 0x00000064}, //100us delay

	{0xCC933024, 0x010ffff0}, //pdb_ch4~19=1
	{0x00000001, 0x00000064}, //100us delay
	{0xCC933000, 0x00000001}, //vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k144_vx1_16lane_5byte[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k144_vx1_16lane_5byte_55_65_77_83inch[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000404},// ITUNE=00100 (swing-4)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010404},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000704},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010704},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000005},// PEMP=00101 (pemp-5)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010005},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000305},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010305},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_120_16lane_LCD_4byte_KLD_8[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG 
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000070},// tcon_sgen_hbp
	{0xCC930094, 0x0000002C},// tcon_sgen_hs
	{0xCC930098, 0x000001D4},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum 

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110B},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000002},// 4byte

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k144_vx1_16lane_5byte_wirelessAV[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG 
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000070},// tcon_sgen_hbp
	{0xCC930094, 0x0000002C},// tcon_sgen_hs
	{0xCC930098, 0x000001D4},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum 

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000002},// 4byte

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_motion_boost[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000060},// tcon_sgen_hbp
	{0xCC930094, 0x00000010},// tcon_sgen_hs
	{0xCC930098, 0x00000030},// tcon_sgen_hfp
	{0xCC93009C, 0x00000024},// tcon_sgen_vbp
	{0xCC9300A0, 0x00000005},// tcon_sgen_vs
	{0xCC9300A4, 0x00000004},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000438},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000015},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000002},// 4byte10bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},// rf=1
	{0xCC974010, 0x01010803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_55_65_77_83inch[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0x00000001, 0x00000064},// 100us delay
	
	{0xCC974010, 0x01000404},// ITUNE=00100 (swing-4)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010404},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000704},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010704},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000005},// PEMP=00101 (pemp-5)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010005},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000305},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010305},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit[] = // Blended OSD
{ // Blended OSD
	//o26

	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000062},// 4byte 13bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},// rf=1
	{0xCC974010, 0x01010803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit_55_65_77_83inch[] = // Blended OSD
{ // Blended OSD
	//o26

	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x0000016A},// tcon_sgen_hbp
	{0xCC930094, 0x00000040},// tcon_sgen_hs
	{0xCC930098, 0x00000096},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000008},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000062},// 4byte 13bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},// rf=1
	{0xCC974010, 0x01010803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0x00000001, 0x00000064},// 100us delay
	
	{0xCC974010, 0x01000404},// ITUNE=00100 (swing-4)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010404},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000704},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010704},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000005},// PEMP=00101 (pemp-5)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010005},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000305},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010305},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit_6_2_vrr[] = // Blended OSD
{ // Blended OSD
	//o26

	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000010},// tcon_sgen_hbp
	{0xCC930094, 0x00000010},// tcon_sgen_hs
	{0xCC930098, 0x00000050},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000018},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},// rf=1
	{0xCC974010, 0x01010803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_13bit_6_2_vrr_55_65_77_83inch[] = // Blended OSD
{ // Blended OSD
	//o26

	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000010},// tcon_sgen_hbp
	{0xCC930094, 0x00000010},// tcon_sgen_hs
	{0xCC930098, 0x00000050},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000018},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},// rf=1
	{0xCC974010, 0x01010803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0x00000001, 0x00000064},// 100us delay
	
	{0xCC974010, 0x01000404},// ITUNE=00100 (swing-4)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010404},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000704},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010704},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000005},// PEMP=00101 (pemp-5)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010005},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000305},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010305},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000010},// tcon_sgen_hbp
	{0xCC930094, 0x00000010},// tcon_sgen_hs
	{0xCC930098, 0x00000050},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000018},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_4k165_vx1_16lane_4byte_5_1_vrr_55_65_77_83inch[] = // Blended OSD
{ // Blended OSD
	//o26
	// CTOP : CLK	CRG
	{0xCC940010, 0x00000303},// 120hz

	// OIF
	{0xCC930004, 0x00000020},
	{0xCC93001C, 0x00000000},// path 설정 (양산시)
	{0xCC930090, 0x00000010},// tcon_sgen_hbp
	{0xCC930094, 0x00000010},// tcon_sgen_hs
	{0xCC930098, 0x00000050},// tcon_sgen_hfp
	{0xCC93009C, 0x00000048},// tcon_sgen_vbp
	{0xCC9300A0, 0x0000000A},// tcon_sgen_vs
	{0xCC9300A4, 0x00000018},// tcon_sgen_vfp
	{0xCC9300A8, 0x00000780},// tcon_sgen_dewidth
	{0xCC9300B0, 0x00000870},// tcon_sgen_denum

	{0xCC9300D4, 0x00000000},// pattern off

	{0xCC9301DC, 0x00000003},// vx1 setting
	{0xCC930300, 0x0010110A},// 16 lane, 1 divi, lane, line delay 0
	{0xCC930304, 0x00000004},
	{0xCC930308, 0x00000F00},
	{0xCC939008, 0x00000022},// 4byte 11bit

	{0xCC93030C, 0x01234567},// vx1_lane_sel0
	{0xCC930310, 0x89ABCDEF},// vx1_lane_sel1

	// CTOP : C4TX	(#0~#15 사용) 4byte
	{0xCC974010, 0x01000000},// reg_rstn=1
	{0xCC974024, 0x01000000},// pdb=1 (ldo)(SICDTV-16228)

	{0xCC974014, 0x00000040},// ctrl_ext_reg_en=1
	{0xCC974010, 0x01000111},// sel_reg=01 (ldo)
	{0xCC974010, 0x01010111},// (ldo)
	{0xCC974010, 0x0100070c},// pdb_pll_reg=1(ldo)
	{0xCC974010, 0x0101070c},// (ldo)
	{0xCC974010, 0x01000013},// VX1 4byte
	{0xCC974010, 0x01010013},
	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974014, 0x0000000f},// link_ext_reg_en=1 (all link)
	{0xCC974010, 0x01000e99},// pdb_link_reg=1, sel_reg=01 (ldo)
	{0xCC974010, 0x01010e99},// (ldo)

	{0xCC974010, 0x01001612},// tx_lock_fixen=1, sel_clkpix=010
	{0xCC974010, 0x01011612},
	{0xCC974010, 0x01001801},// count_txlock=01
	{0xCC974010, 0x01011801},
	{0xCC974010, 0x01001d04},// read_addr_offset=100
	{0xCC974010, 0x01011d04},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000803},
	{0xCC974010, 0x01000402},// itune=00010
	{0xCC974010, 0x01010402},
	{0xCC974010, 0x01000502},// itune=00010
	{0xCC974010, 0x01010502},
	{0xCC974010, 0x01000602},// itune=00010
	{0xCC974010, 0x01010602},
	{0xCC974010, 0x01000702},// itune=00010
	{0xCC974010, 0x01010702},
	{0x00000001, 0x00000064},// 100us delay
	
	{0xCC974010, 0x01000404},// ITUNE=00100 (swing-4)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010404},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010504},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010604},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000704},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010704},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000005},// PEMP=00101 (pemp-5)
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010005},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010105},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010205},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01000305},
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974010, 0x01010305},
	{0x00000001, 0x00000064},// 100us delay

	{0xCC974010, 0x01000000},// WR_EN CLR

	{0xCC974024, 0x01000000},// pdb=1

	{0x00000001, 0x00000064},// 100us delay
	{0xCC974024, 0x0100FFFF},// pdb_ch0~15=1
	{0x00000001, 0x00000064},// 100us delay
	{0xCC974000, 0x00000001},// vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_2k60_lvds_2link[] = // Blended OSD
{
#if 0
	// OIF
	{0xc9070004, 0x00000000}, //tcon_control
	{0xc9070008, 0x00000000}, //tcon_test_ctl
	{0xc907000c, 0x00000008}, //tcon_sync_ctl
	{0xc907001c, 0x00000054}, //tcon_sync_ctl
	{0xc9070090, 0x0000004a}, //tcon_sgen_hbp
	{0xc9070094, 0x00000016}, //tcon_sgen_hs
	{0xc9070098, 0x0000002c}, //tcon_sgen_hfp
	{0xc907009c, 0x00000012}, //tcon_sgen_vbp
	{0xc90700a0, 0x00000005}, //tcon_sgen_vs
	{0xc90700a4, 0x00000016}, //tcon_sgen_vfp
	{0xc90700a8, 0x000003c0}, //tcon_sgen_dewidth
	{0xc90700b0, 0x00000438}, //tcon_sgen_denum
	{0xc90700b8, 0x00000060}, //tcon_vblank_width
	{0xc90700bc, 0x00000004}, //tcon_vsync_width
	{0xc90700d4, 0x00000000}, //tcon_pgen_ctrl
	{0xc9070228, 0x00000001}, //front dummy
	{0xc907022c, 0x0000000c}, //back dummy
	{0xc9070230, 0x00000438}, //vertical line
	{0xc9070234, 0x00000000}, //ltd mode
	{0xc9070238, 0x00000000}, //tcon_rgb_sel0
	{0xc907023C, 0x00000000}, //tcon_rgb_sel1
	{0xc9070240, 0x00000000}, //tcon_rgb_sel2
	{0xc9070244, 0x00000000}, //tcon_rgb_sel3
	{0xc9070248, 0x00000000}, //tcon_rgb_sel4
	{0xc907024C, 0x00000000}, //tcon_rgb_sel5
	{0xc9070250, 0x000003c0}, //horizontal mode
	{0xc9070300, 0x00101022}, //tcon_ddiv_mode
	{0xc9070304, 0x0002000b}, //tcon_ddiv_hblank
	{0xc9070308, 0x00000780}, //tcon_ddiv_hwidth
	{0xc9079008, 0x00000000}, //vx1_config0
	{0xc907900c, 0x00000000}, //vx1_config1
	{0xc9079010, 0x00000000}, //vx1_config2
	{0xc9079014, 0x00000000}, //vx1_config3
	{0xc9079018, 0x00000000}, //vx1_config4
	{0xc907901c, 0x0003814e}, //lvds_config0
	{0xc9079020, 0x00000000}, //lvds_config1
	{0xc9079024, 0x00000000}, //lvds_config2
	{0xc9079028, 0x00000000}, //lvds_config3
	{0xc90701dc, 0x00000003}, //init test
	
	// CTOP : CLK
	{0xC930F008, 0x00001A26}, //tcon_clock
	{0xC930C008, 0x000000CB}, //bnd_ctrl_cco
	{0xC930C00C, 0x00000002}, //bnd_ctrl_cco
	{0xC930D018, 0x00000003}, //bnd_ctrl_vsd
	{0xC930D01C, 0x00000000}, //bnd_ctrl_vsd
	{0xC930F020, 0x00000003}, //bnd_ctrl_dpe	

	// CTOP : C4TX
	{0xC930F808, 0x00000014},
	{0xC930F818, 0x00FFFFFF},
	{0xC930F82C, 0x00FFFFFF},
	{0xC930F830, 0x00000014},
	{0xC930F838, 0x00020010},
	{0xC930F83C, 0x00020010},
	{0xC930F840, 0x00020010},
	{0xC930F84C, 0x1557F000},
	{0xC930F89C, 0x00000111},
	{0xC930F8A0, 0x00102408},
	{0xC930F92C, 0x00000064},	 
	{0xC930F8A0, 0x00102409},
										 
	{0x00000001, 0x00000064}, // 100us delay

	//{0xC930F8A8, 0x00FFFFFF},

	//{0x00000001, 0x00000064}, // 100us delay
	
	//{0xC930F8A0, 0x0010240D},
#endif
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_2k120_lvds_4link[] = // Blended OSD
{
#if 0 
	// OIF
	{0xc9070004, 0x00000000}, //tcon_control
	{0xc9070008, 0x00000080}, //tcon_test_ctl
	{0xc907000c, 0x00000008}, //tcon_sync_ctl
	{0xc907001c, 0x00000054}, //tcon_sync_ctl
	{0xc9070090, 0x0000004a}, //tcon_sgen_hbp
	{0xc9070094, 0x00000016}, //tcon_sgen_hs
	{0xc9070098, 0x0000002c}, //tcon_sgen_hfp
	{0xc907009c, 0x00000012}, //tcon_sgen_vbp
	{0xc90700a0, 0x00000005}, //tcon_sgen_vs
	{0xc90700a4, 0x00000016}, //tcon_sgen_vfp
	{0xc90700a8, 0x000003c0}, //tcon_sgen_dewidth
	{0xc90700b0, 0x00000438}, //tcon_sgen_denum
	{0xc90700b8, 0x00000060}, //tcon_vblank_width
	{0xc90700bc, 0x00000004}, //tcon_vsync_width
	{0xc90700d4, 0x00000000}, //tcon_pgen_ctrl
	{0xc9070228, 0x00000001}, //front dummy
	{0xc907022c, 0x0000000c}, //back dummy
	{0xc9070230, 0x00000438}, //vertical line
	{0xc9070234, 0x00000000}, //ltd mode
	{0xc9070238, 0x00000000}, //tcon_rgb_sel0
	{0xc907023C, 0x00000000}, //tcon_rgb_sel1
	{0xc9070240, 0x00000000}, //tcon_rgb_sel2
	{0xc9070244, 0x00000000}, //tcon_rgb_sel3
	{0xc9070248, 0x00000000}, //tcon_rgb_sel4
	{0xc907024C, 0x00000000}, //tcon_rgb_sel5
	{0xc9070250, 0x000013c0}, //horizontal mode
	{0xc9070300, 0x00101042}, //tcon_ddiv_mode
	{0xc9070304, 0x00020012}, //tcon_ddiv_hblank
	{0xc9070308, 0x00000780}, //tcon_ddiv_hwidth
	{0xc9079004, 0x00000000}, //vx1_config0
	{0xc9079008, 0x00000002}, //vx1_config0
	{0xc907900c, 0x00000000}, //vx1_config1
	{0xc9079010, 0x00000000}, //vx1_config2
	{0xc9079014, 0x00000000}, //vx1_config3
	{0xc9079018, 0x00000000}, //vx1_config4
	{0xc907901c, 0x0002814e}, //lvds_config0
	{0xc9079020, 0x00000000}, //lvds_config1
	{0xc9079024, 0x00000000}, //lvds_config2
	{0xc9079028, 0x00000000}, //lvds_config3
	{0xc90701dc, 0x00000003}, //init test
	
	// CTOP : CLK
	{0xC930F008, 0x00001224}, //tcon_clock
	{0xC930C008, 0x0000008A}, //bnd_ctrl_cco
	{0xC930C00C, 0x00000002}, //bnd_ctrl_cco
	{0xC930D018, 0x00000002}, //bnd_ctrl_vsd
	{0xC930D01C, 0x00000000}, //bnd_ctrl_vsd
	{0xC930F020, 0x00000002}, //bnd_ctrl_dpe	
	
	// CTOP : C4TX
	{0xC930F808, 0x00000014},
	{0xC930F818, 0x00FFFFFF},
	{0xC930F82C, 0x00FFFFFF},
	{0xC930F830, 0x00000014},
	{0xC930F838, 0x00020010},
	{0xC930F83C, 0x00020010},
	{0xC930F840, 0x00020010},
	{0xC930F84C, 0x1557F000},
	{0xC930F89C, 0x00000111},
	{0xC930F8A0, 0x00102408},
	{0xC930F92C, 0x00000064},	 
	{0xC930F8A0, 0x00102409},
										 
	{0x00000001, 0x00000064}, // 100us delay

	//{0xC930F8A8, 0x00FFFFFF},

	//{0x00000001, 0x00000064}, // 100us delay
	
	//{0xC930F8A0, 0x0010240D},
#endif
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o26a0_disp_preEmp_swiLvl[] =
{
	{0x00000002, 0x00000001}, // OVI_HW_O26_REG_READ_START
	
	{0xC930F80C, 0x00000000},
	{0xC930F810, 0x00000000},
	{0xC930F814, 0x00000000},
	{0xC930F81C, 0x00000000},
	{0xC930F820, 0x00000000},
	{0xC930F824, 0x00000000},

	{0x00000002, 0x00000000} // OVI_HW_O26_REG_CHECK_END
};

/**  @} */

