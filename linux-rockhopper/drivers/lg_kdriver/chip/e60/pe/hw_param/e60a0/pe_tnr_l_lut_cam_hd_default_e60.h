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

const PE_REG_PARAM_T tnr_l_lut_cam_hd_default_e60[] =
{
	/* nd tnr lut */
	{0xE1D4, 0xFF20C020},	//x7y7 x6y6 [0000]	  Default
	{0xE1D4, 0xA0208020},	//x5y5 x4y4 [0001]
	{0xE1D4, 0x60204020},	//x3y3 x2y2 [0002]
	{0xE1D4, 0x1E2000C0},	//x1y1 x0y0 [0003]
	{0xE1D4, 0xFF00643C},	//x5y5 x4y4 [0004]	 Default
	{0xE1D4, 0x503C3C1D},	//x3y3 x2y2 [0005]
	{0xE1D4, 0x281D0000},	//x1y1 x0y0 [0006]
	{0xE1D4, 0xB0008000},	//x7y7 x6y6 [0007]	 Default
	{0xE1D4, 0x60004B00},	//x5y5 x4y4 [0008]
	{0xE1D4, 0x3C402C70},	//x3y3 x2y2 [0009]
	{0xE1D4, 0x20900A98},	//x1y1 x0y0 [0010]
	{0xE1D4, 0xB0008000},	//x7y7 x6y6 [0011]	 reg_detail_cir_pt
	{0xE1D4, 0x60004B00},	//x5y5 x4y4 [0012]
	{0xE1D4, 0x3C402C50},	//x3y3 x2y2 [0013]
	{0xE1D4, 0x14900A98},	//x1y1 x0y0 [0014]
	{0xE1D4, 0xB0008000},	//x7y7 x6y6 [0015]	 default
	{0xE1D4, 0x60004B00},	//x5y5 x4y4 [0016]
	{0xE1D4, 0x3C002C50},	//x3y3 x2y2 [0017]
	{0xE1D4, 0x14000A98},	//x1y1 x0y0 [0018]
	{0xE1D4, 0xB0008000},	//x7y7 x6y6 [0019]	 default
	{0xE1D4, 0x60004B00},	//x5y5 x4y4 [0020]
	{0xE1D4, 0x3C402C50},	//x3y3 x2y2 [0021]
	{0xE1D4, 0x14900A98},	//x1y1 x0y0 [0022]
	{0xE1D4, 0x40200080},	//x1y1 x0y0 [0023]	 reg_luma_gain_ctrl
	{0xE1D4, 0xF0E05010},	//x3x2x1x0	[0024]	 reg_skin_gain_ctrl_yy
	{0xE1D4, 0x7F756860},	//x3x2x1x0	[0025]	 reg_skin_gain_ctrl_cb
	{0xE1D4, 0xA8A08D81},	//x3x2x1x0	[0026]	 reg_skin_gain_ctrl_cr
	{0xE1D4, 0x12600010},	//x1y1x0y0	[0027]	 reg_skin_motion_ctrl
	{0xE1D4, 0x2B290049},	//x3x2x1x0	[0028]
	{0xE1D4, 0x80006000},	//x3y3 x2y2 [0029]	 default
	{0xE1D4, 0x40001AFF},	//x1y1 x0y0 [0030]
	{0xE1D4, 0xFF00643C},	//x5y5 x4y4 [0031]	 default
	{0xE1D4, 0x503C3C1D},	//x3y3 x2y2 [0032]
	{0xE1D4, 0x281D0000},	//x1y1 x0y0 [0033]
	{0xE1D4, 0xFF40FF40},	//x5y5 x4y4 [0034]
	{0xE1D4, 0xFF40FF40},	//x3y3 x2y2 [0035]
	{0xE1D4, 0xFF400040},	//x1y1 x0y0 [0036]
	{0xE1D4, 0xF0E05010},	//x3x2x1x0	[0024]	 reg_skin_gain_ctrl_yy
	{0xE1D4, 0x7F756860},	//x3x2x1x0	[0025]	 reg_skin_gain_ctrl_cb
	{0xE1D4, 0xA8A08D81},	//x3x2x1x0	[0026]	 reg_skin_gain_ctrl_cr
	{0xE1D4, 0x12600010},	//x1y1x0y0	[0027]	 reg_skin_motion_ctrl
	{0xE1D4, 0xB0008000},	//x7y7 x6y6 [0015]	 default
	{0xE1D4, 0x60004B00},	//x5y5 x4y4 [0016]
	{0xE1D4, 0x3C002C50},	//x3y3 x2y2 [0017]
	{0xE1D4, 0x14000A98},	//x1y1 x0y0 [0018]
};
