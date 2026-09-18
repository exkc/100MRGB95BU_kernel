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
 *  Header file of defining possible of output modes of O20 Ax
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
static LX_OVI_REG_T ovi_e60a0_disp_8k60_vx1_32lane[] = // Blended OSD
{
	// OIF
	{0xc90b0004, 0x00000020},
	{0xc90b000c, 0x00000008},
	{0xc90b001c, 0x00000094},	
	{0xc90b0090, 0x00000094}, // tcon_sgen_hbp
	{0xc90b0094, 0x0000002c}, // tcon_sgen_hs
	{0xc90b0098, 0x00000058}, // tcon_sgen_hfp
	{0xc90b009c, 0x00000018}, // tcon_sgen_vbp
	{0xc90b00a0, 0x00000014}, // tcon_sgen_vs
	{0xc90b00a4, 0x00000040}, // tcon_sgen_vfp
	{0xc90b00a8, 0x00000780}, // tcon_sgen_dewidth
	{0xc90b00b0, 0x000010e0}, // tcon_sgen_denum
	{0xc90b00b8, 0x00000060}, // tcon_vblank_width
	{0xc90b00bc, 0x00000004}, // tcon_vsync_width
	{0xc90b00d4, 0x00000000}, // tcon_pgen_ctl

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b0300, 0x00000000},
	{0xc90b0304, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b0308, 0x00001e00},	
	{0xc90b9008, 0x00000002},	

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b9094, 0x00000000}, // vx1_lane_sel0
	{0xc90b9098, 0x00000000}, // vx1_lane_sel1
	{0xc90b909c, 0x00000000}, // vx1_lane_sel2
	{0xc90b90a0, 0x00000000}, // vx1_lane_sel3
	{0xc90b90a4, 0x00000000}, // vx1_lane_sel4
	{0xc90b90a8, 0x00000000}, // vx1_lane_sel5
	{0xc90b90ac, 0x00000000}, // vx1_lane_sel6
	{0xc90b90b0, 0x00000000}, // vx1_lane_sel7

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b90d4, 0x00000010}, // vx1_apl_ctrl
	{0xc90b90d8, 0x00001010}, // vx1_info_ctrl0
	{0xc90b90dc, 0x00001019}, // vx1_info_ctrl1
	{0xc90b01dc, 0x00000003}, // init test
		
	// CTOP : CLK
	{0xC9243008, 0x00000000},
	{0xC980300C, 0x000004DC},
	
	// CTOP : C4TX
	// Default setting
	{0x00000001, 0x00000064}, // 100us delay 
	
	{0xc9243424, 0x00000000}, // ext_reg_rstb=0, reg_clk_sel=0, rstn_vtxlink=0, pdb=0
	{0xc9243424, 0x10000000}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=0

	// PLL setting
	{0xc924341c, 0x00000300}, // pll_ext_reg_en=1 , link*_ext_reg_en=0
	{0x00000001, 0x00000001}, // 1us delay 

	// CIH = 001(Default)
	{0xc9243418, 0x00000301}, // ext_reg_wren=0, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010301}, // ext_reg_wren=1, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 

	{0xc9243418, 0x00000805}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010805}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 

	// Channel setting
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 

	//// PEMP=010(50%)
	{0xc9243418, 0x00000022}, // ext_reg_wren=0, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010022}, // ext_reg_wren=1, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000122}, // ext_reg_wren=0, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010122}, // ext_reg_wren=1, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay

	//// DC_CAL=0111(default)
	{0xc9243418, 0x00000777}, // ext_reg_wren=0, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010777}, // ext_reg_wren=1, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000877}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010877}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay

	// Link setting
	{0xc9243418, 0x00001413}, // ext_reg_wren=0, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011413}, // ext_reg_wren=1, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001509}, // ext_reg_wren=0, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011509}, // ext_reg_wren=1, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001610}, // ext_reg_wren=0, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay  
	{0xc9243418, 0x00011610}, // ext_reg_wren=1, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001920}, // ext_reg_wren=0, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011920}, // ext_reg_wren=1, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001b03}, // ext_reg_wren=0, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011b03}, // ext_reg_wren=1, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a11}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
 	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a11}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
	{0x00000001, 0x00000001}, // 1us delay 

	// PDB = 1
	{0xc9243424, 0x10000003}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=1

	{0x00000001, 0x00000064}, // 100us delay

	// Link setting (
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a99}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a99}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000064}, // 100us delay 

	// RSTN_VTXLINK=1
	{0xc9243424, 0x10000013}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=1, pdb=1 

	{0x00000001, 0x0000000a}, // 10us delay

	// PDB_CH=1
	//{0xc9243420, 0xFFFFFFFF}, // pdb_ch=1 
};

static LX_OVI_REG_T ovi_e60a0_disp_4k60_vx1_8lane[] = // Blended OSD
{ 
	// OIF
	{0xc90b0004, 0x00000020},
	{0xc90b000c, 0x00000088},
	{0xc90b001c, 0x00000094},
	{0xc90b0010, 0x00000001},
	{0xc90b0090, 0x00000094}, // tcon_sgen_hbp
	{0xc90b0094, 0x0000002c}, // tcon_sgen_hs
	{0xc90b0098, 0x00000058}, // tcon_sgen_hfp
	{0xc90b009c, 0x00000018}, // tcon_sgen_vbp
	{0xc90b00a0, 0x00000014}, // tcon_sgen_vs
	{0xc90b00a4, 0x00000040}, // tcon_sgen_vfp
	{0xc90b00a8, 0x00000780}, // tcon_sgen_dewidth
	{0xc90b00b0, 0x000010e0}, // tcon_sgen_denum
	{0xc90b00b8, 0x00000060}, // tcon_vblank_width
	{0xc90b00bc, 0x00000004}, // tcon_vsync_width
	{0xc90b00d4, 0x00000000}, // tcon_pgen_ctl
	
	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b0300, 0x00000000},
	{0xc90b0304, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b0308, 0x00001e00},	
	{0xc90b9008, 0x00000002},	

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b9094, 0x00000000}, // vx1_lane_sel0
	{0xc90b9098, 0x00000000}, // vx1_lane_sel1
	{0xc90b909c, 0x00000000}, // vx1_lane_sel2
	{0xc90b90a0, 0x00000000}, // vx1_lane_sel3
	{0xc90b90a4, 0x00000000}, // vx1_lane_sel4
	{0xc90b90a8, 0x00000000}, // vx1_lane_sel5
	{0xc90b90ac, 0x00000000}, // vx1_lane_sel6
	{0xc90b90b0, 0x00000000}, // vx1_lane_sel7

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b90d4, 0x00000010}, // vx1_apl_ctrl
	{0xc90b90d8, 0x00001010}, // vx1_info_ctrl0
	{0xc90b90dc, 0x00001019}, // vx1_info_ctrl1	
	{0xc90b01dc, 0x00000003}, // init test
		
	// CTOP : CLK
	{0xC9243008, 0x00000000},
	{0xC980300C, 0x000004DC},
	
	// CTOP : C4TX
	// Default setting
	{0x00000001, 0x00000064}, // 100us delay 
	
	{0xc9243424, 0x00000000}, // ext_reg_rstb=0, reg_clk_sel=0, rstn_vtxlink=0, pdb=0
	{0xc9243424, 0x10000000}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=0

	// PLL setting
	{0xc924341c, 0x00000300}, // pll_ext_reg_en=1 , link*_ext_reg_en=0
	{0x00000001, 0x00000001}, // 1us delay 

	// CIH = 001(Default)
	{0xc9243418, 0x00000301}, // ext_reg_wren=0, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010301}, // ext_reg_wren=1, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 

	{0xc9243418, 0x00000805}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010805}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 

	// Channel setting
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 

	//// PEMP=010(50%)
	{0xc9243418, 0x00000022}, // ext_reg_wren=0, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010022}, // ext_reg_wren=1, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000122}, // ext_reg_wren=0, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010122}, // ext_reg_wren=1, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay

	//// DC_CAL=0111(default)
	{0xc9243418, 0x00000777}, // ext_reg_wren=0, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010777}, // ext_reg_wren=1, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000877}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010877}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay

	// Link setting
	{0xc9243418, 0x00001413}, // ext_reg_wren=0, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011413}, // ext_reg_wren=1, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001509}, // ext_reg_wren=0, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011509}, // ext_reg_wren=1, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001610}, // ext_reg_wren=0, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay  
	{0xc9243418, 0x00011610}, // ext_reg_wren=1, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001920}, // ext_reg_wren=0, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011920}, // ext_reg_wren=1, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001b03}, // ext_reg_wren=0, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011b03}, // ext_reg_wren=1, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a11}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
 	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a11}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
	{0x00000001, 0x00000001}, // 1us delay 

	// PDB = 1
	{0xc9243424, 0x10000003}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=1

	{0x00000001, 0x00000064}, // 100us delay

	// Link setting (
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a99}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a99}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000064}, // 100us delay 

	// RSTN_VTXLINK=1
	{0xc9243424, 0x10000013}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=1, pdb=1 

	{0x00000001, 0x0000000a}, // 10us delay

	// PDB_CH=1
	//{0xc9243420, 0xFFFFFFFF}, // pdb_ch=1 
};

static LX_OVI_REG_T ovi_e60a0_disp_4k120_vx1_24lane[] = // 16lane video + 8lane separated OSD( or 2lane s.osd + 2lane PIP)
{ 
	// OIF
	{0xC90b0004, 0x00000000},
	{0xC90b0010, 0x00000001},
	{0xc90b001c, 0x00000094},
	{0xc90b0090, 0x0000004a}, // tcon_sgen_hbp
	{0xc90b0094, 0x00000016}, // tcon_sgen_hs
	{0xc90b0098, 0x0000002c}, // tcon_sgen_hfp
	{0xc90b009c, 0x0000000c}, // tcon_sgen_vbp
	{0xc90b00a0, 0x0000000a}, // tcon_sgen_vs
	{0xc90b00a4, 0x00000020}, // tcon_sgen_vfp
	{0xc90b00a8, 0x000003c0}, // tcon_sgen_dewidth
	{0xc90b00b0, 0x00000870}, // tcon_sgen_denum
	{0xc90b00b8, 0x00000060}, // tcon_vblank_width
	{0xc90b00bc, 0x00000004}, // tcon_vsync_width
	{0xc90b00d4, 0x00000000}, // tcon_pgen_ctl

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b0300, 0x00000000},
	{0xc90b0304, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xC90b0308, 0x00000f00},

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xC90b9000, 0x00000000},
	{0xC90b9004, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xC90b9008, 0x00000002},	

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b9094, 0x00000000}, // vx1_lane_sel0
	{0xc90b9098, 0x00000000}, // vx1_lane_sel1
	{0xc90b909c, 0x00000000}, // vx1_lane_sel2
	{0xc90b90a0, 0x00000000}, // vx1_lane_sel3
	{0xc90b90a4, 0x00000000}, // vx1_lane_sel4
	{0xc90b90a8, 0x00000000}, // vx1_lane_sel5
	{0xc90b90ac, 0x00000000}, // vx1_lane_sel6
	{0xc90b90b0, 0x00000000}, // vx1_lane_sel7

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b90d4, 0x00000010}, // vx1_apl_ctrl
	{0xc90b90d8, 0x00003020}, // vx1_info_ctrl0
	{0xc90b90dc, 0x00001059}, // vx1_info_ctrl1
	{0xc90b01dc, 0x00000003}, // init test	
		
	// CTOP : CLK
	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xC9243008, 0x00000000},
	{0xC9245008, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	// CTOP : C4TX
	// Default setting
	{0x00000001, 0x00000064}, // 100us delay 
	
	{0xc9243424, 0x00000000}, // ext_reg_rstb=0, reg_clk_sel=0, rstn_vtxlink=0, pdb=0
	{0xc9243424, 0x10000000}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=0

	// PLL setting
	{0xc924341c, 0x00000300}, // pll_ext_reg_en=1 , link*_ext_reg_en=0
	{0x00000001, 0x00000001}, // 1us delay 

	// CIH = 001(Default)
	{0xc9243418, 0x00000301}, // ext_reg_wren=0, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010301}, // ext_reg_wren=1, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 

	{0xc9243418, 0x00000805}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010805}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 

	// Channel setting
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 

	//// PEMP=010(50%)
	{0xc9243418, 0x00000022}, // ext_reg_wren=0, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010022}, // ext_reg_wren=1, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000122}, // ext_reg_wren=0, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010122}, // ext_reg_wren=1, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay

	//// DC_CAL=0111(default)
	{0xc9243418, 0x00000777}, // ext_reg_wren=0, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010777}, // ext_reg_wren=1, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000877}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010877}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay

	// Link setting
	{0xc9243418, 0x00001413}, // ext_reg_wren=0, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011413}, // ext_reg_wren=1, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001509}, // ext_reg_wren=0, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011509}, // ext_reg_wren=1, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001610}, // ext_reg_wren=0, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay  
	{0xc9243418, 0x00011610}, // ext_reg_wren=1, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001920}, // ext_reg_wren=0, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011920}, // ext_reg_wren=1, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001b03}, // ext_reg_wren=0, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011b03}, // ext_reg_wren=1, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a11}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
 	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a11}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
	{0x00000001, 0x00000001}, // 1us delay 

	// PDB = 1
	{0xc9243424, 0x10000003}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=1

	{0x00000001, 0x00000064}, // 100us delay

	// Link setting (
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a99}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a99}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000064}, // 100us delay 

	// RSTN_VTXLINK=1
	{0xc9243424, 0x10000013}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=1, pdb=1 

	{0x00000001, 0x0000000a}, // 10us delay

	// PDB_CH=1
	//{0xc9243420, 0xFFFFFFFF}, // pdb_ch=1 
};

static LX_OVI_REG_T ovi_e60a0_disp_4k120_vx1_16lane[] = // Blended OSD
{ 
	// OIF
	{0xC90b0004, 0x00000000},
	{0xC90b0010, 0x00000001},
	{0xc90b001c, 0x00000094},
	{0xc90b0090, 0x0000004a}, // tcon_sgen_hbp
	{0xc90b0094, 0x00000016}, // tcon_sgen_hs
	{0xc90b0098, 0x0000002c}, // tcon_sgen_hfp
	{0xc90b009c, 0x0000000c}, // tcon_sgen_vbp
	{0xc90b00a0, 0x0000000a}, // tcon_sgen_vs
	{0xc90b00a4, 0x00000020}, // tcon_sgen_vfp
	{0xc90b00a8, 0x000003c0}, // tcon_sgen_dewidth
	{0xc90b00b0, 0x00000870}, // tcon_sgen_denum
	{0xc90b00b8, 0x00000060}, // tcon_vblank_width
	{0xc90b00bc, 0x00000004}, // tcon_vsync_width
	{0xc90b00d4, 0x00000000}, // tcon_pgen_ctl

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b0300, 0x00000000},
	{0xc90b0304, 0x00000000},

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xC90b0308, 0x00000f00},	
	{0xC90b9008, 0x00000002},	

	{0x00000002, 0x00000001}, // OVI_HW_E60_REG_READ_START
	
	{0xc90b9094, 0x00000000}, // vx1_lane_sel0
	{0xc90b9098, 0x00000000}, // vx1_lane_sel1
	{0xc90b909c, 0x00000000}, // vx1_lane_sel2
	{0xc90b90a0, 0x00000000}, // vx1_lane_sel3
	{0xc90b90a4, 0x00000000}, // vx1_lane_sel4
	{0xc90b90a8, 0x00000000}, // vx1_lane_sel5
	{0xc90b90ac, 0x00000000}, // vx1_lane_sel6
	{0xc90b90b0, 0x00000000}, // vx1_lane_sel7

	{0x00000002, 0x00000000}, // OVI_HW_E60_REG_CHECK_END
	
	{0xc90b90d4, 0x00000010}, // vx1_apl_ctrl
	{0xc90b90d8, 0x00001010}, // vx1_info_ctrl0
	{0xc90b90dc, 0x00001019}, // vx1_info_ctrl1
	{0xc90b01dc, 0x00000003}, // init test	
		
	// CTOP : CLK
	{0xC9243008, 0x00000001},
	
	// CTOP : C4TX
	// Default setting
	{0x00000001, 0x00000064}, // 100us delay 
	
	{0xc9243424, 0x00000000}, // ext_reg_rstb=0, reg_clk_sel=0, rstn_vtxlink=0, pdb=0
	{0xc9243424, 0x10000000}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=0

	// PLL setting
	{0xc924341c, 0x00000300}, // pll_ext_reg_en=1 , link*_ext_reg_en=0
	{0x00000001, 0x00000001}, // 1us delay 

	// CIH = 001(Default)
	{0xc9243418, 0x00000301}, // ext_reg_wren=0, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010301}, // ext_reg_wren=1, ext_reg_addr=8'h03 , ext_reg_wrdata=8'h01(cih=001)
	{0x00000001, 0x00000001}, // 1us delay 

	{0xc9243418, 0x00000805}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010805}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h05(rstn_samp_en=1, rdclk_rf=0, wtclk_rf=1)
	{0x00000001, 0x00000001}, // 1us delay 

	// Channel setting
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 

	//// PEMP=010(50%)
	{0xc9243418, 0x00000022}, // ext_reg_wren=0, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010022}, // ext_reg_wren=1, ext_reg_addr=8'h00 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000122}, // ext_reg_wren=0, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010122}, // ext_reg_wren=1, ext_reg_addr=8'h01 , ext_reg_wrdata=8'h22(pemp=010)
	{0x00000001, 0x00000001}, // 1us delay

	//// DC_CAL=0111(default)
	{0xc9243418, 0x00000777}, // ext_reg_wren=0, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010777}, // ext_reg_wren=1, ext_reg_addr=8'h07 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00000877}, // ext_reg_wren=0, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00010877}, // ext_reg_wren=1, ext_reg_addr=8'h08 , ext_reg_wrdata=8'h77(dc_cal=0111)
	{0x00000001, 0x00000001}, // 1us delay

	// Link setting
	{0xc9243418, 0x00001413}, // ext_reg_wren=0, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011413}, // ext_reg_wren=1, ext_reg_addr=8'h14 , ext_reg_wrdata=8'h13(tx_lockn_fixen=01, sel_clkpix=011)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001509}, // ext_reg_wren=0, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011509}, // ext_reg_wren=1, ext_reg_addr=8'h15 , ext_reg_wrdata=8'h81(dual_rstn_mode_en=1, rstn_sync_main_rf=0, rstn_sync_pll_rf=0, main_clk_pix1x_rf=1)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001610}, // ext_reg_wren=0, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay  
	{0xc9243418, 0x00011610}, // ext_reg_wren=1, ext_reg_addr=8'h16 , ext_reg_wrdata=8'h10(count_txlock=8'h10)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001920}, // ext_reg_wren=0, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011920}, // ext_reg_wren=1, ext_reg_addr=8'h19 , ext_reg_wrdata=8'h20(man_lockn_tomain_en=0, man_lock_tomain=0, count_rxlock=6b'100000)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00001b03}, // ext_reg_wren=0, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay
	{0xc9243418, 0x00011b03}, // ext_reg_wren=1, ext_reg_addr=8'h1b , ext_reg_wrdata=8'h00(retimer_bypass_en=0, read_address_offset=11)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a11}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
 	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a11}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h11(PDB_REG_CLK=0 PDB_REG_P2S=0)
	{0x00000001, 0x00000001}, // 1us delay 

	// PDB = 1
	{0xc9243424, 0x10000003}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=0, pdb=1

	{0x00000001, 0x00000064}, // 100us delay

	// Link setting (
	{0xc924341c, 0x000000ff}, // pll_ext_reg_en=0 , link*_ext_reg_en=1
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00000a99}, // ext_reg_wren=0, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000001}, // 1us delay 
	{0xc9243418, 0x00010a99}, // ext_reg_wren=1, ext_reg_addr=8'h0a , ext_reg_wrdata=8'h99(PDB_REG_CLK=1 PDB_REG_P2S=1)
	{0x00000001, 0x00000064}, // 100us delay 

	// RSTN_VTXLINK=1
	{0xc9243424, 0x10000013}, // ext_reg_rstb=1, reg_clk_sel=0, rstn_vtxlink=1, pdb=1 

	{0x00000001, 0x0000000a}, // 10us delay

	// PDB_CH=1
	//{0xc9243420, 0xFFFFFFFF}, // pdb_ch=1 
};

static LX_OVI_REG_T ovi_e60a0_disp_preEmp_swiLvl[] =
{
	{0x00000002, 0x00000001}, // OVI_HW_O20_REG_READ_START
	
	{0xC930F80C, 0x00000000},
	{0xC930F810, 0x00000000},
	{0xC930F814, 0x00000000},
	{0xC930F81C, 0x00000000},
	{0xC930F820, 0x00000000},
	{0xC930F824, 0x00000000},

	{0x00000002, 0x00000000} // OVI_HW_O20_REG_CHECK_END
};

/**  @} */

