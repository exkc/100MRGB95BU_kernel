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

const PE_REG_PARAM_T tnr_l_lut_hd_default_o20[] =
{
	/* nd tnr lut */
	{0x181D4, 0xFF20C020},	//x7y7 x6y6 [0000]    Default
	{0x181D4, 0xA0208020},	//x5y5 x4y4 [0001]
	{0x181D4, 0x60204020},	//x3y3 x2y2 [0002]
	{0x181D4, 0x1E2000C0},	//x1y1 x0y0 [0003]
	{0x181D4, 0xFF00643C},	//x5y5 x4y4 [0004]   Default
	{0x181D4, 0x503C3C1D},	//x3y3 x2y2 [0005]
	{0x181D4, 0x281D0000},	//x1y1 x0y0 [0006]
	{0x181D4, 0x80006000},	//x7y7 x6y6 [0007]   Default
	{0x181D4, 0x48005400},	//x5y5 x4y4 [0008]
	{0x181D4, 0x40432094},	//x3y3 x2y2 [0009]
	{0x181D4, 0x10A605A8},	//x1y1 x0y0 [0010]
	{0x181D4, 0xB0008000},	//x7y7 x6y6 [0011]   reg_detail_cir_pt
	{0x181D4, 0x60004800},	//x5y5 x4y4 [0012]
	{0x181D4, 0x30402060},	//x3y3 x2y2 [0013]
	{0x181D4, 0x0C8008AC},	//x1y1 x0y0 [0014]
	{0x181D4, 0x80006000},	//x7y7 x6y6 [0015]   default
	{0x181D4, 0x48005400},	//x5y5 x4y4 [0016]
	{0x181D4, 0x20431894},	//x3y3 x2y2 [0017]
	{0x181D4, 0x10A605A8},	//x1y1 x0y0 [0018]
	{0x181D4, 0xB0008000},	//x7y7 x6y6 [0019]   default
	{0x181D4, 0x60004800},	//x5y5 x4y4 [0020]
	{0x181D4, 0x30402060},	//x3y3 x2y2 [0021]
	{0x181D4, 0x0C8008AC},	//x1y1 x0y0 [0022]
	{0x181D4, 0x40200080},	//x1y1 x0y0 [0023]   reg_luma_gain_ctrl
	{0x181D4, 0xF0E05010},	//x3x2x1x0  [0024]   reg_skin_gain_ctrl_yy
	{0x181D4, 0x80786860},	//x3x2x1x0  [0025]   reg_skin_gain_ctrl_cb
	{0x181D4, 0xA8A08A80},	//x3x2x1x0  [0026]   reg_skin_gain_ctrl_cr
	{0x181D4, 0x12A00050},	//x1y1 x0y0 [0027]   reg_skin_motion_ctrl
	{0x181D4, 0x2B290049},	//x3x2x1x0  [0028]
	{0x181D4, 0x80006000},	//x3y3 x2y2 [0029]   default
	{0x181D4, 0x40001AFF},	//x1y1 x0y0 [0030]
	{0x181D4, 0xFF00643C},	//x5y5 x4y4 [0031]   default
	{0x181D4, 0x503C3C1D},	//x3y3 x2y2 [0032]
	{0x181D4, 0x281D0000},	//x1y1 x0y0 [0033]
	{0x181D4, 0xFFA0FFA0},	//x5y5 x4y4 [0034]
	{0x181D4, 0xFFA0FFA0},	//x3y3 x2y2 [0035]
	{0x181D4, 0xFFA00000},	//x1y1 x0y0 [0036]
	{0x181D4, 0x90605040},	//x3x2x1x0  [0037]  reg_color_gain_ctrl_yy
	{0x181D4, 0x90807060},	//x3x2x1x0  [0038]  reg_color_gain_ctrl_cb
	{0x181D4, 0x70605850},	//x3x2x1x0  [0039]  reg_color_gain_ctrl_cr
	{0x181D4, 0x10A00060},	//x1y1 x0y0 [0040]  reg_other_motion_ctrl
	{0x181D4, 0x80006000},	//x7y7 x6y6 [0041]
	{0x181D4, 0x48005400},	//x5y5 x4y4 [0042]
	{0x181D4, 0x40432084},	//x3y3 x2y2 [0043]
	{0x181D4, 0x10900594},	//x1y1 x0y0 [0044]
};
