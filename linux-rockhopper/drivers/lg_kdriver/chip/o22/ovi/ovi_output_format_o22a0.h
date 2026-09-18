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
 *  Header file of defining possible of output modes of O22 Ax
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
__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k60_vx1_8lane[] = // Blended OSD
{
	// OIF
	{0xcc440004, 0x0000023f}, 
	{0xcc440010, 0x00000001}, 
	{0xcc44001c, 0x00000094}, 
	{0xcc440090, 0x0000004a}, // tcon_sgen_hbp
	{0xcc440094, 0x00000016}, // tcon_sgen_hs
	{0xcc440098, 0x0000002c}, // tcon_sgen_hfp
	{0xcc44009c, 0x0000000c}, // tcon_sgen_vbp
	{0xcc4400a0, 0x0000000a}, // tcon_sgen_vs
	{0xcc4400a4, 0x00000020}, // tcon_sgen_vfp
	{0xcc4400a8, 0x00000780}, // tcon_sgen_dewidth
	{0xcc4400b0, 0x00000870}, // tcon_sgen_denum
	{0xcc4400b8, 0x00000060}, // tcon_vblank_width
	{0xcc4400bc, 0x00000004}, // tcon_vsync_width
	{0xcc4400d4, 0x00000000}, // tcon_pgen_ctl
	{0xcc440300, 0x00101082}, 
	{0xcc440304, 0x00020004}, 
	{0xcc440308, 0x00000f00}, 
	{0xcc449008, 0x00000002}, 
	{0xcc449098, 0x00010203}, // vx1_lane_sel1
	{0xcc44909c, 0x04050607}, // vx1_lane_sel2
	{0xcc4490ac, 0x00000010}, // vx1_apl_ctrl
	{0xcc4401dc, 0x00000003}, // init test
		
	// CTOP : CLK
	{0xCC450010, 0x00000011}, // TCON
	{0xCC420010, 0x00000011}, // LED
	{0xCC490010, 0x00111100}, // CCO
	{0xCC470010, 0x00001120}, // VSD
	
	// CTOP : C4TX
	{0xCC432044, 0x00000003}, // vx1 mode
	{0xCC432014, 0x10000000}, // reg_rstn=1 
	{0xCC432014, 0x10000001}, // pdb=1
	{0xCC43200C, 0x00000040}, // ctrl_ext_reg_en=1
	{0xCC432008, 0x00000013}, // 4byte
	{0xCC432008, 0x00010013}, // 4byte
	{0xCC432008, 0x00000805}, // wt_clk_rf = 1
	{0xCC432008, 0x00010805}, // wt_clk_rf = 1
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x0000003f}, // LINK0~5  ext_reg_en = 1 
	{0xCC432008, 0x00001509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00011509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00001413}, // sel_clk_pix = 111
	{0xCC432008, 0x00011413}, // sel_clk_pix = 111
	{0xCC432008, 0x00000403}, // rf = 1
	{0xCC432008, 0x00010403}, // rf = 1
	{0xCC432008, 0x00001610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00011610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00001920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00011920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00001b03}, // 4byte read_addr offset = 2'b11
	{0xCC432008, 0x00011b03}, // 4byte read_addr offset = 2'b11
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x00000039}, // LINK0/3/4/5 ext_reg_en = 1 for lane0~3,12~23 off
	{0xCC432008, 0x00001000}, // LINK_CLK gating
	{0xCC432008, 0x00011000}, // LINK_CLK gating
	{0xCC432008, 0x00001200}, // LINK RST OFF
	{0xCC432008, 0x00011200}, // LINK RST OFF
	{0xCC432008, 0x000019a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x000119a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x00000000}, // WR_EN CLR

	{0x00000001, 0x00000064}, // 100us delay
	
	//{0xCC432010, 0x00000FF0}, // pdb_ch4~11=1
	//{0xCC432014, 0x10000011}, // vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k120_vx1_16lane[] = // Blended OSD
{
	// OIF						 
	{0xcc440004, 0x00000020}, 
	{0xcc440010, 0x00000001}, 
	{0xcc44001c, 0x00000094}, 
	{0xcc440090, 0x00000094}, // tcon_sgen_hbp
	{0xcc440094, 0x0000002c}, // tcon_sgen_hs
	{0xcc440098, 0x00000058}, // tcon_sgen_hfp
	{0xcc44009c, 0x00000048}, // tcon_sgen_vbp
	{0xcc4400a0, 0x0000000a}, // tcon_sgen_vs
	{0xcc4400a4, 0x00000008}, // tcon_sgen_vfp
	{0xcc4400a8, 0x00000780}, // tcon_sgen_dewidth
	{0xcc4400b0, 0x00000870}, // tcon_sgen_denum
	{0xcc4400b8, 0x00000060}, // tcon_vblank_width
	{0xcc4400bc, 0x00000004}, // tcon_vsync_width
	{0xcc4400d4, 0x00000000}, // tcon_pgen_ctl
	{0xcc440300, 0x00101102}, 
	{0xcc440304, 0x00020004}, 
	{0xcc440308, 0x00000f00}, 
	{0xcc449008, 0x00000002}, 
	{0xcc449098, 0x00010203}, // vx1_lane_sel1
	{0xcc44909c, 0x04050607}, // vx1_lane_sel2
	{0xcc4490a0, 0x08090a0b}, // vx1_lane_sel3
	{0xcc4490a4, 0x0c0d0e0f}, // vx1_lane_sel4
	{0xcc4490ac, 0x00000010}, // vx1_apl_ctrl
	{0xcc4401dc, 0x00000003}, // init test

	// CTOP : CLK
	{0xCC450010, 0x00000000},
	
	// CTOP : C4TX
	{0xCC432044, 0x00000003}, // vx1 mode
	{0xCC432014, 0x10000000}, // reg_rstn=1 
	{0xCC432014, 0x10000001}, // pdb=1
	{0xCC43200C, 0x00000040}, // ctrl_ext_reg_en=1
	{0xCC432008, 0x00000013}, // 4byte
	{0xCC432008, 0x00010013}, // 4byte
	{0xCC432008, 0x00000805}, // wt_clk_rf = 1
	{0xCC432008, 0x00010805}, // wt_clk_rf = 1
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x0000003f}, // LINK0~5  ext_reg_en = 1 
	{0xCC432008, 0x00001509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00011509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00001413}, // sel_clk_pix = 111
	{0xCC432008, 0x00011413}, // sel_clk_pix = 111
	{0xCC432008, 0x00000403}, // rf = 1
	{0xCC432008, 0x00010403}, // rf = 1
	{0xCC432008, 0x00001610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00011610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00001920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00011920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00001b03}, // 4byte read_addr offset = 2'b11
	{0xCC432008, 0x00011b03}, // 4byte read_addr offset = 2'b11
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x00000021}, // LINK0/5 ext_reg_en = 1 for lane0~3,20~23 off
	{0xCC432008, 0x00001000}, // LINK_CLK gating
	{0xCC432008, 0x00011000}, // LINK_CLK gating
	{0xCC432008, 0x00001200}, // LINK RST OFF
	{0xCC432008, 0x00011200}, // LINK RST OFF
	{0xCC432008, 0x000019a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x000119a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x00000000}, // WR_EN CLR

	{0x00000001, 0x00000064}, // 100us delay
	
	//{0xCC432010, 0x000FFFF0}, // pdb_ch4~19=1
	//{0xCC432014, 0x10000011}, // vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k120_vx1_24lane_5byte[] = // 16lane video + 8lane separated OSD
{ 
	// OIF
	{0xcc440004, 0x00000020}, 
	{0xcc440010, 0x00000001}, 
	{0xcc44001c, 0x00000094}, 
	{0xcc440090, 0x00000094}, // tcon_sgen_hbp
	{0xcc440094, 0x0000002c}, // tcon_sgen_hs
	{0xcc440098, 0x00000058}, // tcon_sgen_hfp
	{0xcc44009c, 0x00000048}, // tcon_sgen_vbp
	{0xcc4400a0, 0x0000000a}, // tcon_sgen_vs
	{0xcc4400a4, 0x00000008}, // tcon_sgen_vfp
	{0xcc4400a8, 0x00000780}, // tcon_sgen_dewidth
	{0xcc4400b0, 0x00000870}, // tcon_sgen_denum
	{0xcc4400b8, 0x00000060}, // tcon_vblank_width
	{0xcc4400bc, 0x00000004}, // tcon_vsync_width
	{0xcc4400d4, 0x00000000}, // tcon_pgen_ctl
	{0xcc440300, 0x00101102}, 
	{0xcc440304, 0x00020004}, 
	{0xcc440308, 0x00000f00}, 
	{0xcc449004, 0x00000007},
	//{0xcc449008, 0x00000006},
	{0xcc449008, 0x00000002},
	{0xcc449094, 0x00010203}, // vx1_lane_sel0
	{0xcc449098, 0x04050607}, // vx1_lane_sel1
	{0xcc44909c, 0x08090a0b}, // vx1_lane_sel2
	{0xcc4490a0, 0x0c0d0e0f}, // vx1_lane_sel3
	{0xcc4490a4, 0x10111213}, // vx1_lane_sel4
	{0xcc4490a8, 0x14151617}, // vx1_lane_sel5
	{0xcc4490ac, 0x00000010}, // vx1_apl_ctrl
	{0xcc4490b0, 0x00003010}, // vx1_info_ctrl0
	{0xcc4490b4, 0x00001050}, // vx1_info_ctrl1
	{0xcc4490b8, 0x00001010}, // vx1_osd_ctrl1
	{0xcc4490bc, 0x00002050}, // vx1_osd_ctrl1
	{0xcc4401dc, 0x00000003}, // init test

	// CTOP : CLK
	{0xCC450010, 0x00000000},
	{0xCC470010, 0X00000001},
	{0xCC490010, 0X00000001},

	// CTOP : C4TX
	{0xCC432044, 0x00000003}, // vx1 mode
	{0xCC432014, 0x10000000}, // reg_rstn=1 
	{0xCC432014, 0x10000001}, // pdb=1
	{0xCC43200C, 0x00000040}, // ctrl_ext_reg_en=1
	{0xCC432008, 0x00000033}, // 5byte
	{0xCC432008, 0x00010033}, // 5byte
	{0xCC432008, 0x00000805}, // wt_clk_rf = 1
	{0xCC432008, 0x00010805}, // wt_clk_rf = 1
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x0000003f}, // LINK0~5  ext_reg_en = 1 
	{0xCC432008, 0x00001509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00011509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00001413}, // sel_clk_pix = 111
	{0xCC432008, 0x00011413}, // sel_clk_pix = 111
	{0xCC432008, 0x00000403}, // rf = 1
	{0xCC432008, 0x00010403}, // rf = 1
	{0xCC432008, 0x00001610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00011610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00001920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00011920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00001b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00011b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00000000}, // WR_EN CLR

	{0x00000001, 0x00000064}, // 100us delay
	
	//{0xCC432010, 0x00FFFFFF}, // pdb_ch0~23=1
	//{0xCC432014, 0x10000011}, // vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k120_vx1_16lane_5byte[] = // Blended OSD
{
	// OIF
	{0xcc440004, 0x00000020}, 
	{0xcc440010, 0x00000001}, 
	{0xcc44001c, 0x00000094}, 
	{0xcc440090, 0x00000094}, // tcon_sgen_hbp
	{0xcc440094, 0x0000002c}, // tcon_sgen_hs
	{0xcc440098, 0x00000058}, // tcon_sgen_hfp
	{0xcc44009c, 0x00000048}, // tcon_sgen_vbp
	{0xcc4400a0, 0x0000000a}, // tcon_sgen_vs
	{0xcc4400a4, 0x00000008}, // tcon_sgen_vfp
	{0xcc4400a8, 0x00000780}, // tcon_sgen_dewidth
	{0xcc4400b0, 0x00000870}, // tcon_sgen_denum
	{0xcc4400b8, 0x00000060}, // tcon_vblank_width
	{0xcc4400bc, 0x00000004}, // tcon_vsync_width
	{0xcc4400d4, 0x00000000}, // tcon_pgen_ctl
	{0xcc440300, 0x00101102}, 
	{0xcc440304, 0x00020004}, 
	{0xcc440308, 0x00000f00}, 
	{0xcc449008, 0x00000006}, 
	{0xcc449098, 0x00010203}, // vx1_lane_sel1
	{0xcc44909c, 0x04050607}, // vx1_lane_sel2
	{0xcc4490a0, 0x08090a0b}, // vx1_lane_sel3
	{0xcc4490a4, 0x0c0d0e0f}, // vx1_lane_sel4
	{0xcc4490ac, 0x00000010}, // vx1_apl_ctrl
	{0xcc4401dc, 0x00000003}, // init test

	// CTOP : CLK
	{0xCC450010, 0x00000000},

	// CTOP : C4TX
	{0xCC432044, 0x00000003}, // vx1 mode
	{0xCC432014, 0x10000000}, // reg_rstn=1 
	{0xCC432014, 0x10000001}, // pdb=1
	{0xCC43200C, 0x00000040}, // ctrl_ext_reg_en=1
	{0xCC432008, 0x00000033}, // 5byte
	{0xCC432008, 0x00010033}, // 5byte
	{0xCC432008, 0x00000805}, // wt_clk_rf = 1
	{0xCC432008, 0x00010805}, // wt_clk_rf = 1
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x0000003f}, // LINK0~5  ext_reg_en = 1 
	{0xCC432008, 0x00001509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00011509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00001413}, // sel_clk_pix = 111
	{0xCC432008, 0x00011413}, // sel_clk_pix = 111
	{0xCC432008, 0x00000403}, // rf = 1
	{0xCC432008, 0x00010403}, // rf = 1
	{0xCC432008, 0x00001610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00011610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00001920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00011920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00001b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00011b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x00000021}, // LINK0/5 ext_reg_en = 1 for lane0~3,20~23 off
	{0xCC432008, 0x00001000}, // LINK_CLK gating
	{0xCC432008, 0x00011000}, // LINK_CLK gating
	{0xCC432008, 0x00001200}, // LINK RST OFF
	{0xCC432008, 0x00011200}, // LINK RST OFF
	{0xCC432008, 0x000019a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x000119a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x00000000}, // WR_EN CLR

	{0x00000001, 0x00000064}, // 100us delay

	//{0xCC432010, 0x000FFFF0}, // pdb_ch4~19=1
	//{0xCC432014, 0x10000011}, // vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_2k120_vx1_4lane_4byte[] = // Blended OSD
{
	// OIF
	{0xcc440004, 0x0000021f},
	{0xcc440010, 0x00000001},
	{0xcc44001c, 0x00000094},
	{0xcc440090, 0x0000004a},
	{0xcc440094, 0x00000016},
	{0xcc440098, 0x0000002c},
	{0xcc44009c, 0x00000024},
	{0xcc4400a0, 0x00000005},
	{0xcc4400a4, 0x00000004},
	{0xcc4400a8, 0x000003C0},
	{0xcc4400b0, 0x00000438},
	{0xcc4400b8, 0x00000060},
	{0xcc4400bc, 0x00000004},
	{0xcc4400d4, 0x00000000},
	{0xcc440300, 0x00101042},
	{0xcc440304, 0x00020004},
	{0xcc440308, 0x00000780},
	{0xcc449008, 0x00000002},
	{0xcc449098, 0x00010203},
	{0xcc44909c, 0x04050607},
	{0xcc4490ac, 0x00000010},
	{0xcc4401dc, 0x00000003},
	// CTOP : CLK
	{0xCC450010, 0x00000020},
	{0xCC420010, 0x00000011},
	{0xCC490010, 0x00111100},
	{0xCC470010, 0x00001120},
	// CTOP : C4TX
	{0xCC432044, 0x00000003},
	{0xCC432014, 0x10000000},
	{0xCC432014, 0x10000001},
	{0xCC43200C, 0x00000040},
	{0xCC432008, 0x00000013},
	{0xCC432008, 0x00010013},
	{0xCC432008, 0x00000805},
	{0xCC432008, 0x00010805},
	{0xCC432008, 0x00000000},
	{0xCC43200C, 0x0000003f},
	{0xCC432008, 0x00001509},
	{0xCC432008, 0x00011509},
	{0xCC432008, 0x00001413},
	{0xCC432008, 0x00011413},
	{0xCC432008, 0x00001610},
	{0xCC432008, 0x00011610},
	{0xCC432008, 0x00001920},
	{0xCC432008, 0x00011920},
	{0xCC432008, 0x00001b03},
	{0xCC432008, 0x00011b03},
	{0xCC432008, 0x00000000},
	{0xCC43200C, 0x00000039},
	{0xCC432008, 0x00001000},
	{0xCC432008, 0x00011000},
	{0xCC432008, 0x00001200},
	{0xCC432008, 0x00011200},
	{0xCC432008, 0x000019a0},
	{0xCC432008, 0x000119a0},
	{0xCC432008, 0x00000000},
	{0x00000001, 0x00000064},

	//{0xCC432010, 0x00000FF0},
	//{0xCC432014, 0x10000011},
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k144_vx1_16lane_5byte[] = // Blended OSD
{ // Blended OSD
	// OIF
	{0xcc440004, 0x00000020},
	{0xcc440010, 0x00000001},
	{0xcc44001c, 0x00000094},
	{0xcc440090, 0x00000094}, // tcon_sgen_hbp
	{0xcc440094, 0x0000002c}, // tcon_sgen_hs
	{0xcc440098, 0x00000058}, // tcon_sgen_hfp
	{0xcc44009c, 0x00000048}, // tcon_sgen_vbp
	{0xcc4400a0, 0x0000000a}, // tcon_sgen_vs
	{0xcc4400a4, 0x00000008}, // tcon_sgen_vfp
	{0xcc4400a8, 0x00000780}, // tcon_sgen_dewidth
	{0xcc4400b0, 0x00000870}, // tcon_sgen_denum
	{0xcc4400b8, 0x00000060}, // tcon_vblank_width
	{0xcc4400bc, 0x00000004}, // tcon_vsync_width
	{0xcc4400d4, 0x00000000}, // tcon_pgen_ctl
	{0xcc440300, 0x00101102},
	{0xcc440304, 0x00020004},
	{0xcc440308, 0x00000f00},
	{0xcc449008, 0x00000042}, // change 11bit
	{0xcc449098, 0x00010203}, // vx1_lane_sel1
	{0xcc44909c, 0x04050607}, // vx1_lane_sel2
	{0xcc4490a0, 0x08090a0b}, // vx1_lane_sel3
	{0xcc4490a4, 0x0c0d0e0f}, // vx1_lane_sel4
	{0xcc4490ac, 0x00000010}, // vx1_apl_ctrl
	{0xcc4401dc, 0x00000003}, // init test

	// CTOP : CLK
	{0xCC450010, 0x00000000},

	// CTOP : C4TX
	{0xCC432044, 0x00000003}, // vx1 mode
	{0xCC432014, 0x10000000}, // reg_rstn=1
	{0xCC432014, 0x10000001}, // pdb=1
	{0xCC43200C, 0x00000040}, // ctrl_ext_reg_en=1
	{0xCC432008, 0x00000013}, // 5byte --> 4byte
	{0xCC432008, 0x00010013}, // 5byte --> 4byte
	{0xCC432008, 0x00000805}, // wt_clk_rf = 1
	{0xCC432008, 0x00010805}, // wt_clk_rf = 1
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x0000003f}, // LINK0~5  ext_reg_en =
	{0xCC432008, 0x00001509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00011509}, // dual_reset_mode = 1 , main_clk_pix1x_rf =1
	{0xCC432008, 0x00001413}, // sel_clk_pix = 111
	{0xCC432008, 0x00011413}, // sel_clk_pix = 111
	{0xCC432008, 0x00000403}, // rf = 1
	{0xCC432008, 0x00010403}, // rf = 1
	{0xCC432008, 0x00001610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00011610}, // count_tx_lock = 8'h10
	{0xCC432008, 0x00001920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00011920}, // count_rx_lock = 8'h20
	{0xCC432008, 0x00001b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00011b00}, // 5byte read_addr offset = 2'b00
	{0xCC432008, 0x00000000}, // WR_EN CLR
	{0xCC43200C, 0x00000021}, // LINK0/5 ext_reg_en = 1 for lane0~3,20~23 off
	{0xCC432008, 0x00001000}, // LINK_CLK gating
	{0xCC432008, 0x00011000}, // LINK_CLK gating
	{0xCC432008, 0x00001200}, // LINK RST OFF
	{0xCC432008, 0x00011200}, // LINK RST OFF
	{0xCC432008, 0x000019a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x000119a0}, // man_lockn_tomain = 0, count_rx_lock = 8'h20
	{0xCC432008, 0x00000000}, // WR_EN CLR

	{0x00000001, 0x00000064}, // 100us delay

	//{0xCC432010, 0x000FFFF0}, // pdb_ch4~19=1
	//{0xCC432014, 0x10000011}, // vtx_link_rstn=1
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_4k144_vx1_16lane_5byte_lcd_wireless[] = // Blended OSD
{ // Blended OSD
	// OIF
	{0xcc440004, 0x00000020},
	{0xcc440010, 0x00000001},
	{0xcc44001c, 0x00000094},
	{0xcc440090, 0x00000044},
	{0xcc440094, 0x0000002c},
	{0xcc440098, 0x00000058},
	{0xcc44009c, 0x00000148},
	{0xcc4400a0, 0x0000001a},
	{0xcc4400a4, 0x000000ba},
	{0xcc4400a8, 0x00000780},
	{0xcc4400b0, 0x00000870},
	{0xcc4400b8, 0x00000060},
	{0xcc4400bc, 0x00000004},
	{0xcc4400d4, 0x00000000},
	{0xcc440300, 0x00101102},
	{0xcc440304, 0x00020004},
	{0xcc440308, 0x00000f00},

	{0xcc449008, 0x00000002}, //4byte 10bit
	{0xcc449098, 0x00010203},
	{0xcc44909c, 0x04050607},
	{0xcc4490a0, 0x08090a0b},
	{0xcc4490a4, 0x0c0d0e0f},

	{0xcc4490ac, 0x00000010},
	{0xcc4401dc, 0x00000003},
	{0xCC450010, 0x00000000},

	// CTOP : C4TX
	{0xCC432044, 0x00000003},
	{0xCC432014, 0x10000000},
	{0xCC432014, 0x10000001},
	{0xCC43200C, 0x00000040},
	{0xCC432008, 0x00000013},
	{0xCC432008, 0x00010013},
	{0xCC432008, 0x00000805},
	{0xCC432008, 0x00010805},
	{0xCC432008, 0x00000000},
	{0xCC43200C, 0x0000003f},
	{0xCC432008, 0x00001509},
	{0xCC432008, 0x00011509},
	{0xCC432008, 0x00001413},
	{0xCC432008, 0x00011413},
	{0xCC432008, 0x00000403},
	{0xCC432008, 0x00010403},
	{0xCC432008, 0x00001610},
	{0xCC432008, 0x00011610},
	{0xCC432008, 0x00001920},
	{0xCC432008, 0x00011920},
	{0xCC432008, 0x00001b03},
	{0xCC432008, 0x00011b03},
	{0xCC432008, 0x00000000},
	{0xCC43200C, 0x00000021},
	{0xCC432008, 0x00001000},
	{0xCC432008, 0x00011000},
	{0xCC432008, 0x00001200},
	{0xCC432008, 0x00011200},
	{0xCC432008, 0x000019a0},
	{0xCC432008, 0x000119a0},
	{0xCC432008, 0x00000000},

	{0x00000001, 0x00000064},
	{0xCC432010, 0x000FFFF0},
	{0xCC432014, 0x10000011},
};

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_2k60_lvds_2link[] = // Blended OSD
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

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_2k120_lvds_4link[] = // Blended OSD
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

__attribute__((unused)) static LX_OVI_REG_T ovi_o22a0_disp_preEmp_swiLvl[] =
{
	{0x00000002, 0x00000001}, // OVI_HW_O22_REG_READ_START
	
	{0xC930F80C, 0x00000000},
	{0xC930F810, 0x00000000},
	{0xC930F814, 0x00000000},
	{0xC930F81C, 0x00000000},
	{0xC930F820, 0x00000000},
	{0xC930F824, 0x00000000},

	{0x00000002, 0x00000000} // OVI_HW_O22_REG_CHECK_END
};

/**  @} */

