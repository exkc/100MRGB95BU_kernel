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

const PE_REG_PARAM_T tnr_l_lut_sd_default_m17[] =
{
	/* nd tnr lut */
	{0x41D4, 0xFF22C022},	//x7y7 x6y6 [0000]	  Default
	{0x41D4, 0xA0228022},	//x5y5 x4y4 [0001]
	{0x41D4, 0x60224022},	//x3y3 x2y2 [0002]
	{0x41D4, 0x1E2200CC},	//x1y1 x0y0 [0003]
	{0x41D4, 0xFF00643C},	//x5y5 x4y4 [0004]	 Default
	{0x41D4, 0x503C3C1D},	//x3y3 x2y2 [0005]
	{0x41D4, 0x281D0000},	//x1y1 x0y0 [0006]
	{0x41D4, 0xB0008000},	//x7y7 x6y6 [0007]	 Default
	{0x41D4, 0x60005000},	//x5y5 x4y4 [0008]
	{0x41D4, 0x40482890},	//x3y3 x2y2 [0009]
	{0x41D4, 0x14A00AB0},	//x1y1 x0y0 [0010]
	{0x41D4, 0xB0008000},	//x7y7 x6y6 [0011]	 reg_detail_cir_pt
	{0x41D4, 0x60005000},	//x5y5 x4y4 [0012]
	{0x41D4, 0x40482890},	//x3y3 x2y2 [0013]
	{0x41D4, 0x14A00AB0},	//x1y1 x0y0 [0014]
	{0x41D4, 0xB0008000},	//x7y7 x6y6 [0015]	 default
	{0x41D4, 0x60005000},	//x5y5 x4y4 [0016]
	{0x41D4, 0x40482890},	//x3y3 x2y2 [0017]
	{0x41D4, 0x14A00AB0},	//x1y1 x0y0 [0018]
	{0x41D4, 0xB0008000},	//x7y7 x6y6 [0019]	 default
	{0x41D4, 0x60005000},	//x5y5 x4y4 [0020]
	{0x41D4, 0x40482890},	//x3y3 x2y2 [0021]
	{0x41D4, 0x14A00AB0},	//x1y1 x0y0 [0022]
	{0x41D4, 0x40800080},	//x1y1 x0y0 [0023]	 reg_luma_gain_ctrl
	{0x41D4, 0xF0E05010 },	//x3x2x1x0	[0024]	 reg_skin_gain_ctrl_yy
	{0x41D4, 0x80786860 },	//x3x2x1x0	[0025]	 reg_skin_gain_ctrl_cb
	{0x41D4, 0xA8A08A80 },	//x3x2x1x0	[0026]	 reg_skin_gain_ctrl_cr
	{0x41D4, 0x10FF00A0 },	//x1y1x0y0	[0027]	 reg_skin_motion_ctrl
	{0x41D4, 0x2B290049},	//x3x2x1x0	[0028]
	{0x41D4, 0x80006000},	//x3y3 x2y2 [0029]	 default
	{0x41D4, 0x40001AFF},	//x1y1 x0y0 [0030]
	{0x41D4, 0xFF00643C},	//x5y5 x4y4 [0031]	 default
	{0x41D4, 0x503C3C1D},	//x3y3 x2y2 [0032]
	{0x41D4, 0x281D0000},	//x1y1 x0y0 [0033]
	{0x41D4, 0xFFA0FFA0},	//x5y5 x4y4 [0034]
	{0x41D4, 0xFFA0FFA0},	//x3y3 x2y2 [0035]
	{0x41D4, 0xFFA00000},	//x1y1 x0y0 [0036]
	{0x41D4, 0x90605040},	//x3x2x1x0	[0024]	 reg_skin_gain_ctrl_yy
	{0x41D4, 0x90807060},	//x3x2x1x0	[0025]	 reg_skin_gain_ctrl_cb
	{0x41D4, 0x70605850},	//x3x2x1x0	[0026]	 reg_skin_gain_ctrl_cr
	{0x41D4, 0x10FF00E0},	//x1y1x0y0	[0027]	 reg_skin_motion_ctrl
	{0x41D4, 0xB0008000},	//x7y7 x6y6 [0015]	 default
	{0x41D4, 0x60004000},	//x5y5 x4y4 [0016]
	{0x41D4, 0x20081020},	//x3y3 x2y2 [0017]
	{0x41D4, 0x04600480},	//x1y1 x0y0 [0018]
};

